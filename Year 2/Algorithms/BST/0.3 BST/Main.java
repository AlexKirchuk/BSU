import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("bst.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("bst.out")));
        StringTokenizer st;

        int n = Integer.parseInt(br.readLine().trim());
        long[] key = new long[n];
        int[] parent = new int[n];
        boolean[] isLeft = new boolean[n];
        long[] low = new long[n];
        long[] high = new long[n];

        key[0] = Long.parseLong(br.readLine().trim());

        for (int i = 1; i < n; i++) {
            st = new StringTokenizer(br.readLine());
            key[i] = Long.parseLong(st.nextToken());
            int p = Integer.parseInt(st.nextToken());
            char c = st.nextToken().charAt(0);
            parent[i] = p - 1;
            isLeft[i] = (c == 'L');
        }

        final long INF = Long.MAX_VALUE;
        low[0] = -INF;
        high[0] = INF;

        boolean ok = true;

        for (int i = 1; i < n; i++) {
            int p = parent[i];
            if (isLeft[i]) {
                low[i] = low[p];
                high[i] = key[p];
            } else {
                low[i] = key[p];
                high[i] = high[p];
            }

            if (key[i] < low[i] || key[i] >= high[i]) {
                ok = false;
                break;
            }
        }

        out.println(ok ? "YES" : "NO");
        out.close();
        br.close();
    }
}