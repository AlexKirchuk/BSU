import java.io.*;
import java.util.Optional;

public class NecklaceConnector {

    public static void save(Necklace necklace, String filename) throws IOException {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(filename))) {
            oos.writeObject(necklace);
        }
    }

    public static Optional<Necklace> load(String filename) throws IOException, ClassNotFoundException {
        File file = new File(filename);
        if (!file.exists()) throw new FileNotFoundException("File not found: " + filename);
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(file))) {
            return Optional.of((Necklace) ois.readObject());
        }
    }
}