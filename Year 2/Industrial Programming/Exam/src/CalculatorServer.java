import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class CalculatorServer {

    private static final int PORT = 5000;

    public static void main(String[] args) {
        System.out.println("CalculatorServer started on port " + PORT);

        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            while (true) {
                Socket client = serverSocket.accept();
                new Thread(new ClientHandler(client)).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    static class ClientHandler implements Runnable {
        private final Socket socket;

        ClientHandler(Socket socket) {
            this.socket = socket;
        }

        @Override
        public void run() {
            try (
                    BufferedReader in = new BufferedReader(
                            new InputStreamReader(socket.getInputStream()));
                    PrintWriter out = new PrintWriter(
                            socket.getOutputStream(), true)
            ) {
                String line;
                while ((line = in.readLine()) != null) {
                    out.println(calculate(line));
                }
            } catch (IOException ignored) {
            }
        }

        private String calculate(String input) {
            try {
                String[] parts = input.trim().split("\\s+");
                if (parts.length != 3) {
                    return "format_error";
                }

                double a = Double.parseDouble(parts[0]);
                String op = parts[1];
                double b = Double.parseDouble(parts[2]);

                return switch (op) {
                    case "+" -> String.valueOf(a + b);
                    case "-" -> String.valueOf(a - b);
                    case "*" -> String.valueOf(a * b);
                    case "/" -> {
                        if (b == 0) yield "divide_by_zero";
                        yield String.valueOf(a / b);
                    }
                    default -> "unknown_operation";
                };
            } catch (Exception e) {
                return "calc_error";
            }
        }
    }
}