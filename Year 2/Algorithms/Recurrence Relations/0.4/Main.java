import java.util.Scanner;

import static java.lang.Math.min;

public class Main {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        int[] dim = new int[n + 1];

        int rows, cols;
        for (int i = 0; i < n; i++)
        {
            rows = sc.nextInt();
            cols = sc.nextInt();
            if (i == 0) dim[i] = rows;
            dim[i + 1] = cols;
        }

        long[][] b = new long[n + 1][n + 1];

        long j, cost;
        for (int l = 2; l <= n; l++)
        {
            for (int i = 1; i <= n - l + 1; i++)
            {
                j = i + l - 1;
                b[i][(int)j] = Long.MAX_VALUE;
                for (int k = i; k < j; k++)
                {
                    cost = b[i][k] + b[k + 1][(int)j] + dim[i - 1] * dim[k] * dim[(int)j];
                    b[i][(int)j] = Math.min(b[i][(int)j], cost);
                }
            }
        }

        System.out.print(b[1][n]);
    }
}