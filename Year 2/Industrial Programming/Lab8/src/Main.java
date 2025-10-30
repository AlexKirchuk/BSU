import java.io.*;
import java.util.*;

public class Main {
    private static final String FILENAME = "Bills.dat";
    private static final String FILENAME_BAK = "Bills.~dat";
    private static final String INDEX_NAME = "Bills.idx";
    private static final String INDEX_NAME_BAK = "Bills.~idx";

    private static String encoding = "UTF-8";
    private static PrintStream billOut = System.out;

    public static void main(String[] args) {
        try {
            if (args.length == 0) {
                System.err.println("Nothing to do! Use -? for help.");
                return;
            }

            switch (args[0]) {
                case "-?":
                case "-h":
                    printHelp();
                    break;
                case "-a":
                    appendFile(args, false);
                    break;
                case "-az":
                    appendFile(args, true);
                    break;
                case "-p":
                    printFile();
                    break;
                case "-ps":
                    printFileSorted(args, false);
                    break;
                case "-psr":
                    printFileSorted(args, true);
                    break;
                case "-d":
                    deleteAll();
                    break;
                case "-dk":
                    deleteByKey(args);
                    break;
                case "-f":
                    findByKey(args, null);
                    break;
                case "-fr":
                    findByKey(args, new KeyComp());
                    break;
                case "-fl":
                    findByKey(args, new KeyCompReverse());
                    break;
                default:
                    System.err.println("Unknown command: " + args[0]);
                    printHelp();
            }
        } catch (Exception e) {
            System.err.println("Runtime error: " + e.getMessage());
        }
    }

    // ================== HELP ==================
    private static void printHelp() {
        System.out.println(
                """
                        Usage:
                          -a  [file [encoding]]     Append data (normal)
                          -az [file [encoding]]     Append data (compressed)
                          -p                        Print all records (unsorted)
                          -psr {h|a|o|d}            Print sorted descending by index
                          -ps  {h|a|o|d}            Print sorted ascending by index
                          -f   {h|a|o|d} key        Find record(s) by key
                          -fr  {h|a|o|d} key        Find record(s) with key greater
                          -fl  {h|a|o|d} key        Find record(s) with key less
                          -d                        Delete all data
                          -dk  {h|a|o|d} key        Delete record(s) by key
                          -?                        Show this help
                        
                        Index keys: h - house, a - apartment, o - owner, d - date"""
        );
    }

    // ================== APPEND ==================
    private static UtilityBill readBill(Scanner fin) throws IOException {
        return UtilityBill.nextRead(fin, billOut)
                ? UtilityBill.read(fin, billOut)
                : null;
    }

    private static void appendFile(String[] args, boolean zipped)
            throws IOException, ClassNotFoundException, KeyNotUniqueException {

        if (args.length >= 2) {
            FileInputStream input = new FileInputStream(args[1]);
            System.setIn(input);
            if (args.length == 3) encoding = args[2];
            billOut = new PrintStream(OutputStream.nullOutputStream());
        }

        Scanner fin = new Scanner(System.in, encoding);
        billOut.println("Enter utility bill data:");

        try (Index idx = Index.load(INDEX_NAME);
             RandomAccessFile raf = new RandomAccessFile(FILENAME, "rw")) {

            while (true) {
                UtilityBill bill = readBill(fin);
                if (bill == null) break;

                idx.test(bill);
                long pos = Buffer.writeObject(raf, bill, zipped);
                idx.put(bill, pos);
            }
        }
    }

    // ================== PRINT ==================
    private static void printFile() throws IOException, ClassNotFoundException {
        try (RandomAccessFile raf = new RandomAccessFile(FILENAME, "r")) {
            long pos;
            int i = 0;
            while ((pos = raf.getFilePointer()) < raf.length()) {
                System.out.print("#" + (++i));
                printRecord(raf, pos);
            }
        }
    }

    private static void printFileSorted(String[] args, boolean reverse)
            throws IOException, ClassNotFoundException {
        if (args.length != 2) {
            System.err.println("Invalid arguments. Expected index key (h|a|o|d).");
            return;
        }

        try (Index idx = Index.load(INDEX_NAME);
             RandomAccessFile raf = new RandomAccessFile(FILENAME, "r")) {

            IndexBase base = indexByArg(args[1], idx);
            if (base == null) return;

            String[] keys = base.getKeys(reverse ? new KeyCompReverse() : new KeyComp());
            for (String key : keys)
                printRecord(raf, key, base);
        }
    }

    // ================== DELETE ==================
    private static void deleteAll() {
        File dataFile = new File(FILENAME);
        if (dataFile.delete()) {
            System.out.println(FILENAME + " deleted.");
        } else {
            System.out.println(FILENAME + " could not be deleted (maybe it does not exist).");
        }

        File indexFile = new File(INDEX_NAME);
        if (indexFile.delete()) {
            System.out.println(INDEX_NAME + " deleted.");
        } else {
            System.out.println(INDEX_NAME + " could not be deleted (maybe it does not exist).");
        }
    }

    private static void deleteByKey(String[] args)
            throws IOException, ClassNotFoundException, KeyNotUniqueException {

        if (args.length != 3) {
            System.err.println("Invalid arguments for delete.");
            return;
        }

        Long[] positions;
        try (Index idx = Index.load(INDEX_NAME)) {
            IndexBase base = indexByArg(args[1], idx);
            if (base == null) return;
            if (!base.contains(args[2])) {
                System.err.println("Key not found: " + args[2]);
                return;
            }
            positions = base.get(args[2]);
        }

        File dataFile = new File(FILENAME);
        File dataBak = new File(FILENAME_BAK);
        if (dataFile.renameTo(dataBak)) {
            System.out.println(FILENAME + " backed up to " + FILENAME_BAK);
        } else {
            System.out.println("Failed to backup " + FILENAME);
        }

        File indexFile = new File(INDEX_NAME);
        File indexBak = new File(INDEX_NAME_BAK);
        if (indexFile.renameTo(indexBak)) {
            System.out.println(INDEX_NAME + " backed up to " + INDEX_NAME_BAK);
        } else {
            System.out.println("Failed to backup " + INDEX_NAME);
        }

        try (Index idx = Index.load(INDEX_NAME);
             RandomAccessFile bak = new RandomAccessFile(FILENAME_BAK, "r");
             RandomAccessFile raf = new RandomAccessFile(FILENAME, "rw")) {

            boolean[] zipped = new boolean[]{false};
            long pos;
            while ((pos = bak.getFilePointer()) < bak.length()) {
                UtilityBill bill = (UtilityBill) Buffer.readObject(bak, pos, zipped);
                if (Arrays.binarySearch(positions, pos) < 0) {
                    long newPos = Buffer.writeObject(raf, bill, zipped[0]);
                    idx.put(bill, newPos);
                }
            }
        }

        System.out.println("Deleted record(s) with key: " + args[2]);
    }

    // ================== SEARCH ==================
    private static void findByKey(String[] args, Comparator<String> comp)
            throws IOException, ClassNotFoundException {

        if (args.length != 3) {
            System.err.println("Invalid arguments for search.");
            return;
        }

        try (Index idx = Index.load(INDEX_NAME);
             RandomAccessFile raf = new RandomAccessFile(FILENAME, "r")) {

            IndexBase base = indexByArg(args[1], idx);
            if (base == null) return;

            if (comp == null) { // exact match
                if (!base.contains(args[2])) {
                    System.err.println("Key not found: " + args[2]);
                    return;
                }
                printRecord(raf, args[2], base);
            } else {
                String[] keys = base.getKeys(comp);
                for (String key : keys) {
                    if (key.equals(args[2])) break;
                    printRecord(raf, key, base);
                }
            }
        }
    }

    // ================== PRINT HELPERS ==================
    private static void printRecord(RandomAccessFile raf, long pos)
            throws IOException, ClassNotFoundException {

        boolean[] zipped = new boolean[]{false};
        UtilityBill bill = (UtilityBill) Buffer.readObject(raf, pos, zipped);
        if (zipped[0]) System.out.print(" [compressed]");
        System.out.println(" Record at position " + pos + ":\n" + bill + "\n");
    }

    private static void printRecord(RandomAccessFile raf, String key, IndexBase base)
            throws IOException, ClassNotFoundException {

        Long[] positions = base.get(key);
        for (long pos : positions) {
            System.out.print("*** Key: " + key + " points to");
            printRecord(raf, pos);
        }
    }

    // ================== INDEX SELECTOR ==================
    private static IndexBase indexByArg(String arg, Index idx) {
        return switch (arg) {
            case "h" -> idx.houseNumbers;
            case "a" -> idx.apartments;
            case "o" -> idx.owners;
            case "d" -> idx.dates;
            default -> {
                System.err.println("Invalid index key: " + arg);
                yield null;
            }
        };
    }
}