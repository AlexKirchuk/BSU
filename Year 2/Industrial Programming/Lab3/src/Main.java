// 7. Из текста удалить все символы,
// кроме пробелов, не являющиеся буквами.
// Между последовательностями подряд идущих букв
// оставить хотя бы один пробел.

//Enter your text:
//kgf4 34h4i 435h 435. -- .; rg/ eert -
//Variant 1 with StringTokenizer: kgf h i h rg eert
//Variant 2 with Regular Expressions: kgf h i h rg eert

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