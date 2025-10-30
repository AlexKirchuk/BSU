import java.io.*;
import java.util.*;
import java.util.zip.*;

// ===================== COMPARATORS =====================
class KeyComp implements Comparator<String> {
    public int compare(String o1, String o2) { return o1.compareTo(o2); }
}

class KeyCompReverse implements Comparator<String> {
    public int compare(String o1, String o2) { return o2.compareTo(o1); }
}

// ===================== INDEX BASE INTERFACE =====================
interface IndexBase {
    String[] getKeys(Comparator<String> comp);
    boolean contains(String key);
    Long[] get(String key);
}

// ===================== UNIQUE INDEX =====================
class IndexOne2One implements Serializable, IndexBase {
    @Serial
    private static final long serialVersionUID = 1L;
    private final TreeMap<String, Long> map = new TreeMap<>();

    public String[] getKeys(Comparator<String> comp) {
        String[] keys = map.keySet().toArray(new String[0]);
        Arrays.sort(keys, comp);
        return keys;
    }

    public void put(String key, long value) { map.put(key, value); }

    public boolean contains(String key) { return map.containsKey(key); }

    public Long[] get(String key) {
        Long pos = map.get(key);
        return (pos == null) ? new Long[0] : new Long[]{pos};
    }
}

// ===================== NON-UNIQUE INDEX =====================
class IndexOne2N implements Serializable, IndexBase {
    @Serial
    private static final long serialVersionUID = 1L;
    private final TreeMap<String, Vector<Long>> map = new TreeMap<>();

    public String[] getKeys(Comparator<String> comp) {
        String[] keys = map.keySet().toArray(new String[0]);
        Arrays.sort(keys, comp);
        return keys;
    }

    public void put(String key, long value) {
        Vector<Long> list = map.get(key);
        if (list == null) list = new Vector<>();
        list.add(value);
        map.put(key, list);
    }

    public boolean contains(String key) { return map.containsKey(key); }

    public Long[] get(String key) {
        Vector<Long> list = map.get(key);
        return (list == null) ? new Long[0] : list.toArray(new Long[0]);
    }
}

// ===================== MAIN INDEX CLASS =====================
public class Index implements Serializable, Closeable {
    @Serial
    private static final long serialVersionUID = 1L;

    public IndexOne2One houseNumbers;
    public IndexOne2N apartments;
    public IndexOne2N owners;
    public IndexOne2N dates;

    private transient String filename = null;

    public Index() {
        houseNumbers = new IndexOne2One();
        apartments = new IndexOne2N();
        owners = new IndexOne2N();
        dates = new IndexOne2N();
    }

    // ===================== UNIQUE KEY TEST =====================
    public void test(UtilityBill bill) throws KeyNotUniqueException {
        String hKey = String.valueOf(bill.houseNumber);
        if (houseNumbers.contains(hKey)) {
            throw new KeyNotUniqueException("House number already exists: " + bill.houseNumber);
        }
    }

    // ===================== INSERT RECORD =====================
    public void put(UtilityBill bill, long pos) throws KeyNotUniqueException {
        test(bill);
        houseNumbers.put(String.valueOf(bill.houseNumber), pos);
        apartments.put(String.valueOf(bill.apartmentNumber), pos);
        owners.put(bill.ownerName, pos);
        dates.put(bill.paymentDate, pos);
    }

    // ===================== LOAD INDEX =====================
    public static Index load(String name) throws IOException, ClassNotFoundException {
        Index idx;
        try {
            FileInputStream file = new FileInputStream(name);
            try (ZipInputStream zis = new ZipInputStream(file)) {
                ZipEntry entry = zis.getNextEntry();
                assert entry != null;
                if (!entry.getName().equals(Buffer.ZIP_ENTRY_NAME)) {
                    throw new IOException("Invalid index file format");
                }
                try (ObjectInputStream ois = new ObjectInputStream(zis)) {
                    idx = (Index) ois.readObject();
                }
            }
        } catch (FileNotFoundException e) {
            idx = new Index();
        }
        if (idx != null) idx.save(name);
        return idx;
    }

    // ===================== SAVE INDEX =====================
    public void save(String name) { filename = name; }

    public void saveAs(String name) throws IOException {
        try (FileOutputStream fos = new FileOutputStream(name);
             ZipOutputStream zos = new ZipOutputStream(fos)) {
            zos.putNextEntry(new ZipEntry(Buffer.ZIP_ENTRY_NAME));
            zos.setLevel(ZipOutputStream.DEFLATED);
            try (ObjectOutputStream oos = new ObjectOutputStream(zos)) {
                oos.writeObject(this);
            }
            zos.closeEntry();
        }
    }

    @Override
    public void close() throws IOException {
        if (filename != null) saveAs(filename);
    }
}