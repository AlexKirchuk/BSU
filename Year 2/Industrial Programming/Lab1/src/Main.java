// myCos

//Input x: 4
//Input k: 9
//My cos: -0.654
//Standard cos: -0.654
//
//
//Process finished with exit code 0

import java.text.NumberFormat;
import java.util.Scanner;
import static java.lang.Math.*;

public class Main {
    public static double myCos(double x, int k) {
        final double PI = 3.141592;
        double seqMembCos, sumCos;
        int n = 1;
        while ((x >= 2 * PI) || (x < 0))
        {
            if (x < 0) x += 2 * PI;
            else x -= 2 * PI;
        }
        seqMembCos = sumCos = 1;
        while (abs(seqMembCos) > pow(10, -k))
        {
            seqMembCos = -(seqMembCos * x * x) / (n * (n + 1));
            sumCos += seqMembCos;
            n += 2;
        }
        return sumCos;
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int x, k;
        System.out.print("Input x: ");
        x = in.nextInt();
        System.out.print("Input k: ");
        k = in.nextInt();

        NumberFormat formatter = NumberFormat.getNumberInstance();
        formatter.setMaximumFractionDigits(3);

        System.out.println("My cos: " + formatter.format(myCos(x, k)));
        System.out.println("Standard cos: " + formatter.format(cos(x)));
    }
}