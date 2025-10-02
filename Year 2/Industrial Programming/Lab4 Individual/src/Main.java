public class Main {
    public static void main(String[] args) {
        Interval a = new Interval(1, 5);
        Interval b = new Interval(3, 7);

        System.out.println("Interval A: " + a);
        System.out.println("Interval B: " + b);

        System.out.println("Length of A: " + a.length());
        System.out.println("Length of B: " + b.length());

        a.shift(2);
        System.out.println("A after shifting: " + a);

        b.scale(0.5);
        System.out.println("B after scaling: " + b);

        System.out.println("Comparison of A and B (by length): " + a.compareTo(b));
        if (a.compareTo(b) > 0)
            System.out.println("A is bigger than B");
        else
            System.out.println("B is bigger than A");

        System.out.println("Union (sum) of A and B: " + a.sum(b));

        System.out.print("Difference A - B: ");
        for (Interval d : a.difference(b)) {
            System.out.print(d + " ");
        }
    }
}