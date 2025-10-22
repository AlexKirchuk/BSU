/*
Задано бинарное дерево. Необходимо проверить,
является ли оно поисковым.Будем предполагать,
что в бинарном поисковом дереве могут быть вершины
с одинаковыми ключами. Тогда, для того,
чтобы дерево было поисковым, должно выполняться
следующее требование: для каждой вершины x
все ключи в левом поддереве вершины x меньше
ключа вершины x, а все ключи в правом поддереве
больше либо равны ключу вершины x.

Input
Первая строка входного файла содержит единственное целое число n
(1 <= n <= 8 * 10^5) – количество вершин в дереве.
Следующая строка содержит одно целое число m (-2^31 <= m <= 2^31 - 1)
– значение в корневой вершине дерева.
В каждой из последующих n - 1 строк через пробелы перечисляются
три параметра m, p и c, которые задают
какую-либо вершину дерева.
m – целое число
(-2^31 <= m <= 2^31 - 1),
значение, записанное в вершине.
p – целое число (1 <= p <= n - 1),
номер строки входного файла, в которой
был задан родитель текущей вершины (нумерация строк с нуля).
Гарантируется, что p меньше, чем номер текущей строки.
c может принимать одно из двух значений `L' или `R'.
Значение `L' указывает на то, что текущая вершина
присоединена к родительской слева, `R' – справа.
Гарантируется, что совокупность всех строк задает
корректное бинарное дерево.

Output
В единственной строке выведите `YES',
если заданное дерево является бинарным деревом поиска,
и `NO' в противном случае.
*/

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