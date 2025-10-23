import java.io.FileNotFoundException;

public class Main {
    public static void main(String[] args) {
        try {
            Necklace necklace = new Necklace();
            necklace.addStone(new PreciousStone("Diamond", 2.5, 1000, 95));
            necklace.addStone(new SemiPreciousStone("Amethyst", 3.2, 200, 80));
            necklace.addStone(new PreciousStone("Ruby", 1.7, 850, 90));

            System.out.println(necklace);

            necklace.sortByValue();
            System.out.println("After sorting by value:");
            System.out.println(necklace);

            System.out.println("Stones with transparency between 80–95%:");
            necklace.findByTransparency(80, 95).forEach(System.out::println);

            NecklaceConnector.save(necklace, "necklace.bin");

            System.out.println("\nLoading from file:");
            Necklace loaded = NecklaceConnector.load("necklace.bin").orElseThrow();
            System.out.println(loaded);

        } catch (IllegalArgumentException e) {
            System.err.println("Invalid data: " + e.getMessage());
        } catch (OutOfMemoryError e) {
            System.err.println("Error: Not enough memory!");
        } catch (FileNotFoundException e) {
            System.err.println("File not found!");
        } catch (Exception e) {
            System.err.println("An error occurred: " + e);
        }
    }
}