import java.util.*;

public class Main {
    public static void main(String[] args) {
        ArrayList<EquilateralTriangle> list = new ArrayList<>();
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
    }
}