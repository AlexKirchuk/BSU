import java.io.*;
import java.util.zip.*;

public class Buffer {

    static final String ZIP_ENTRY_NAME = "z";

    static byte[] toByteArray(Serializable obj) throws IOException {
        ByteArrayOutputStream bout = new ByteArrayOutputStream();
        try (ObjectOutputStream oos = new ObjectOutputStream(bout)) {
            oos.writeObject(obj);
            oos.flush();
            return bout.toByteArray();
        }
    }

    static byte[] toZipByteArray(Serializable obj) throws IOException {
        ByteArrayOutputStream bout = new ByteArrayOutputStream();
        try (ZipOutputStream zos = new ZipOutputStream(bout)) {
            zos.putNextEntry(new ZipEntry(ZIP_ENTRY_NAME));
            zos.setLevel(Deflater.BEST_COMPRESSION);
            try (ObjectOutputStream oos = new ObjectOutputStream(zos)) {
                oos.writeObject(obj);
                oos.flush();
                zos.closeEntry();
                zos.flush();
                return bout.toByteArray();
            }
        }
    }

    static Object fromByteArray(byte[] arr) throws IOException, ClassNotFoundException {
        ByteArrayInputStream bin = new ByteArrayInputStream(arr);
        try (ObjectInputStream ois = new ObjectInputStream(bin)) {
            return ois.readObject();
        }
    }

    public static Object fromZipByteArray(byte[] arr) throws IOException, ClassNotFoundException {
        ByteArrayInputStream bin = new ByteArrayInputStream(arr);
        try (ZipInputStream zis = new ZipInputStream(bin)) {
            ZipEntry zen = zis.getNextEntry();
            if (zen == null || !zen.getName().equals(ZIP_ENTRY_NAME)) {
                throw new IOException("Invalid compressed data format");
            }
            ObjectInputStream ois = new ObjectInputStream(zis);
            return ois.readObject();
        }
    }

    public static long writeObject(RandomAccessFile file, Serializable obj, boolean zipped)
            throws IOException {

        long position = file.length();
        file.seek(position);

        byte[] data;
        if (zipped) {
            data = toZipByteArray(obj);
            file.writeByte(1);
        } else {
            data = toByteArray(obj);
            file.writeByte(0);
        }

        file.writeInt(data.length);
        file.write(data);
        file.setLength(file.getFilePointer());

        System.out.println("Written record at position " + position + " (" + (zipped ? "compressed" : "plain") + ")");
        return position;
    }

    public static Object readObject(RandomAccessFile file, long position, boolean[] wasZipped)
            throws IOException, ClassNotFoundException {

        file.seek(position);
        byte zipped = file.readByte();
        int length = file.readInt();

        byte[] data = new byte[length];
        file.readFully(data);

        if (wasZipped != null)
            wasZipped[0] = (zipped != 0);

        if (zipped == 0) {
            Object obj = fromByteArray(data);
            System.out.println(" read plain record from position " + position);
            return obj;
        } else if (zipped == 1) {
            Object obj = fromZipByteArray(data);
            System.out.println(" read compressed record from position " + position);
            return obj;
        } else {
            throw new IOException("Invalid data flag at position " + position);
        }
    }
}