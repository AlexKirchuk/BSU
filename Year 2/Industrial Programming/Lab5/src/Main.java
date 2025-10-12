import java.util.*;

public class Main {
    public static void main(String[] args) {
        try {
            List<EquilateralTriangle> list = new ArrayList<>();
            list.add(new EquilateralTriangle(5.0, "Red", "Yellow"));
            list.add(new EquilateralTriangle(3.0, "Blue", "Green"));
            list.add(new EquilateralTriangle(7.0, "Black", "White"));

            System.out.println("Original list:");
            list.forEach(System.out::println);

            Collections.sort(list);
            System.out.println("\nSorted by side:");
            list.forEach(System.out::println);

            EquilateralTriangle comparator = new EquilateralTriangle(1.0, "tmp", "tmp");
            comparator.setCompareField("area");
            list.sort(comparator);

            System.out.println("\nSorted by area:");
            list.forEach(System.out::println);

            System.out.println("\nFields of the first triangle using iterator:");
            for (Object field : list.getFirst()) {
                System.out.println(field);
            }

            String serialized = list.getFirst().toString();
            EquilateralTriangle restored = new EquilateralTriangle(serialized);
            System.out.println("\nRestored object from string:");
            System.out.println(restored);

            assert restored.getSideA() == list.getFirst().getSideA()
                    : "Restored triangle side mismatch!";
            assert restored.getFillColor().equals(list.getFirst().getFillColor())
                    : "Restored triangle color mismatch!";

            System.out.println("\nAssertions passed successfully.");

            try {
                new EquilateralTriangle(-5.0, "Red", "Blue");
                System.out.println("Error: exception was expected but not thrown!");
            } catch (IllegalArgumentException ex) {
                System.out.println("\nException test passed: " + ex.getMessage());
            }

        } catch (AssertionError ae) {
            System.err.println("Assertion failed: " + ae.getMessage());
        } catch (Exception e) {
            System.err.println("Exception caught: " + e.getMessage());
        }
    }
}