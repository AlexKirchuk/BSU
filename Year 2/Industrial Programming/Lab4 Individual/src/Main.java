public class Main {
    public static void main(String[] args) {
        Interval a = new Interval(1, 5);
        Interval b = new Interval(3, 7);

        assert a.length() == 4 : "Length of A should be 4";
        assert b.length() == 4 : "Length of B should be 4";

        System.out.println("Interval A: " + a);
        System.out.println("Interval B: " + b);

        System.out.println("Length of A: " + a.length());
        System.out.println("Length of B: " + b.length());

        a.shift(2);
        System.out.println("A after shifting: " + a);
        assert a.toString().equals("(3.0, 7.0)") : "After shift(2), A should be (3,7)";

        b.scale(0.5);
        System.out.println("B after scaling: " + b);
        assert Math.abs(b.length() - 2) < 1e-9 : "After scaling by 0.5, B's length should be 2";

        System.out.println("Comparison of A and B (by length): " + a.compareTo(b));
        if (a.compareTo(b) > 0)
            System.out.println("A is bigger than B");
        else
            System.out.println("B is bigger than A");

        Interval union = a.sum(b);
        System.out.println("Union (sum) of A and B: " + union);
        assert union.toString().equals("(3.0, 7.0)") : "Union should be (3,7)";

        System.out.print("Difference A - B: ");
        Interval[] diff = a.difference(b);
        for (Interval d : diff) {
            System.out.print(d + " ");
        }
        System.out.println();
        assert diff.length == 2 : "Difference should produce 2 intervals";
    }
}