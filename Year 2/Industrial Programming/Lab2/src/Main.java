import java.util.Scanner;
import static java.lang.Math.*;

public class Main {

    public static void task3() {
        System.out.println("Task3: ");
        Scanner num = new Scanner(System.in);
        int n, m;
        System.out.print("Input n: ");
        n = num.nextInt();
        System.out.print("Input m: ");
        m = num.nextInt();
        int[][] matrix = inputMatrix(n, m);
        printMatrix(matrix);

        // Algorithm
        int count = 0;
        boolean isEven;
        System.out.print("Even columns: ");
        for (int i = 0; i < m; i++) {
            isEven = true;
            for (int j = 0; j < n; j++) {
                if (matrix[j][i] % 2 != 0) {
                    isEven = false;
                    break;
                }
            }
            if (isEven) {
                System.out.print((i + 1) + " ");
                count++;
            }
        }
        if (count > 0)
            System.out.println();
        else
            System.out.println("no such columns");

        count = 0;
        int sum, min = min(n, m);
        System.out.print("Specific columns: ");
        for (int i = 0; i < min; i++) {
            sum = 0;
           if (matrix[i][i] < 0) {
               System.out.print((i + 1) + " ");
               for (int j = 0; j < n; j++) {
                   sum += matrix[j][i];
               }
               System.out.println(", sum = " + sum);
               count++;
           }
        }
        if (count > 0)
            System.out.println();
        else
            System.out.println("no such columns");
    }

    public static void task17() {
        System.out.println("Task17: ");
        Scanner num = new Scanner(System.in);
        int n, m;
        System.out.print("Input n: ");
        n = num.nextInt();
        System.out.print("Input m: ");
        m = num.nextInt();
        int[][] matrix = inputMatrix(n, m);
        printMatrix(matrix);

        // Algorithm
        int sum, minSum = abs(matrix[0][0]);
        for (int k = 0; k <= n + m - 2; k++) {
            sum = 0;
            for (int i = 0; i < n; i++) {
                int j = k - i;
                if (j >= 0 && j < m)
                    sum += Math.abs(matrix[i][j]);
            }
            if (sum < minSum) {
                minSum = sum;
            }
        }
        System.out.println("Min: " + minSum + "\n");
    }

    public static void task31() {
        System.out.println("Task31: ");
        Scanner num = new Scanner(System.in);
        int n, m;
        System.out.print("Input n: ");
        n = num.nextInt();
        System.out.print("Input m: ");
        m = num.nextInt();
        int[][] matrix = inputMatrix(n, m);
        printMatrixWithSums(matrix);

        // Algorithm
        mergeSort(matrix, 0, matrix.length - 1);

        printMatrixWithSums(matrix);
    }

    private static int[][] inputMatrix(int n, int m) {
        Scanner num = new Scanner(System.in);
        int[][] matrix = new int[n][m];
        System.out.println("Input elements: ");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                matrix[i][j] = num.nextInt();
            }
        }
        return matrix;
    }

    private static void printMatrix(int[][] matrix) {
        for (int[] row : matrix) {
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
        System.out.println();
    }

    private static int rowSum(int[] row) {
        int sum = 0;
        for (int val : row) {
            sum += val;
        }
        return sum;
    }

    private static void mergeSort(int[][] matrix, int left, int right) {
        if (left < right) {
            int mid = (left + right) / 2;
            mergeSort(matrix, left, mid);
            mergeSort(matrix, mid + 1, right);
            merge(matrix, left, mid, right);
        }
    }

    private static void merge(int[][] matrix, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        int[][] L = new int[n1][];
        int[][] R = new int[n2][];

        System.arraycopy(matrix, left, L, 0, n1);
        for (int j = 0; j < n2; j++) R[j] = matrix[mid + 1 + j];

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (rowSum(L[i]) <= rowSum(R[j]))
                matrix[k++] = L[i++];
            else
                matrix[k++] = R[j++];
        }

        while (i < n1) matrix[k++] = L[i++];
        while (j < n2) matrix[k++] = R[j++];
    }

    private static void printMatrixWithSums(int[][] matrix) {
        for (int[] row : matrix) {
            int sum = 0;
            for (int val : row) {
                System.out.print(val + " ");
                sum += val;
            }
            System.out.println(" | sum = " + sum);
        }
        System.out.println();
    }

    public static void main(String[] args) {
        task3();
        task17();
        task31();
        }
}