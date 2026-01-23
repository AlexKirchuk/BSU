import i18n.I18n;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class CalculatorClient {

    private static final String HOST = "localhost";
    private static final int PORT = 5000;

    public static void main(String[] args) {
        String lang = args.length > 0 ? args[0] : "en";
        I18n i18n = new I18n(lang);

        try (
                Socket socket = new Socket(HOST, PORT);
                BufferedReader in = new BufferedReader(
                        new InputStreamReader(socket.getInputStream()));
                PrintWriter out = new PrintWriter(
                        socket.getOutputStream(), true);
                Scanner scanner = new Scanner(System.in)
        ) {
            System.out.println(i18n.t("connected"));

            while (true) {
                System.out.print("> ");
                String input = scanner.nextLine();
                if ("exit".equalsIgnoreCase(input)) break;

                out.println(input);
                String response = in.readLine();

                if (response.matches("-?\\d+(\\.\\d+)?")) {
                    System.out.println(response);
                } else {
                    System.out.println(i18n.t(response));
                }
            }
        } catch (IOException e) {
            System.out.println(i18n.t("connection_error"));
        }
    }
}