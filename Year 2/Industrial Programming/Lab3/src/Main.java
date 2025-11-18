import java.util.Scanner;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter your text:");
        String str = sc.nextLine();

        // Variant 1 with StringTokenizer
        StringTokenizer stringTokenizer = new StringTokenizer(str, " 1234567890,.!?/'\";:{}[]<>()+=-*&^%$#@");
        StringBuilder newStr = new StringBuilder();
        while (stringTokenizer.hasMoreTokens()) {
            newStr.append(stringTokenizer.nextToken()).append(" ");
        }
        System.out.println("Variant 1 with StringTokenizer: " + newStr);

        // Variant 2 with Regular Expressions
        str = str.replaceAll("[^a-zA-Zа-яА-ЯёЁ ]", " ");
        str = str.replaceAll("\\s+", " ").trim();

        System.out.println("Variant 2 with Regular Expressions: " + str);
    }
}