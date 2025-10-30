import java.io.*;
import java.util.*;
import java.util.zip.*;

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

    public void test(UtilityBill bill) throws KeyNotUniqueException {
        String hKey = String.valueOf(bill.houseNumber);
        if (houseNumbers.contains(hKey)) {
            throw new KeyNotUniqueException("House number already exists: " + bill.houseNumber);
        }
    }

    public void put(UtilityBill bill, long pos) throws KeyNotUniqueException {
        test(bill);
        houseNumbers.put(String.valueOf(bill.houseNumber), pos);
        apartments.put(String.valueOf(bill.apartmentNumber), pos);
        owners.put(bill.ownerName, pos);
        dates.put(bill.paymentDate, pos);
    }

    public static Index load(String name) throws IOException, ClassNotFoundException {
        Index idx;
        try {
            FileInputStream file = new FileInputStream(name);
            ZipInputStream zis = new ZipInputStream(file);
            ZipEntry entry = zis.getNextEntry();
            if (entry == null || !entry.getName().equals(Buffer.ZIP_ENTRY_NAME)) {
                zis.close();
                throw new IOException("Invalid index file format");
            }
            ObjectInputStream ois = new ObjectInputStream(zis);
            idx = (Index) ois.readObject();
            ois.close();
            zis.close();
        } catch (FileNotFoundException e) {
            idx = new Index();
        }
        if (idx != null) idx.save(name);
        return idx;
    }

    public void save(String name) { filename = name; }

    public void saveAs(String name) throws IOException {
        try (FileOutputStream fos = new FileOutputStream(name);
             ZipOutputStream zos = new ZipOutputStream(fos)) {
            zos.putNextEntry(new ZipEntry(Buffer.ZIP_ENTRY_NAME));
            zos.setLevel(ZipOutputStream.DEFLATED);
            ObjectOutputStream oos = new ObjectOutputStream(zos);
            oos.writeObject(this);
            zos.closeEntry();
        }
    }

    @Override
    public void close() throws IOException {
        if (filename != null) saveAs(filename);
    }
}