import i18n.I18n;

import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.net.Socket;

public class CalculatorClientGUI extends JFrame {

    private JTextField display;
    private JComboBox<String> langBox;

    private PrintWriter out;
    private BufferedReader in;

    private I18n i18n;

    private static final String HOST = "localhost";
    private static final int PORT = 5000;

    public CalculatorClientGUI() {
        i18n = new I18n("en");

        connect();
        initUI();
    }

    private void initUI() {
        setTitle(i18n.t("title"));
        setSize(300, 420);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        display = new JTextField();
        display.setFont(new Font("Consolas", Font.BOLD, 15));
        display.setEditable(false);
        display.setHorizontalAlignment(JTextField.RIGHT);
        add(display, BorderLayout.NORTH);

        langBox = new JComboBox<>(new String[]{
                "English",
                "Русский",
                "Беларуская"
        });

        langBox.addActionListener(_ -> {
            String lang = switch (langBox.getSelectedIndex()) {
                case 0 -> "en";
                case 1 -> "ru";
                case 2 -> "be";
                default -> "en";
            };
            i18n = new I18n(lang);
            setTitle(i18n.t("title"));
        });
        add(langBox, BorderLayout.SOUTH);

        JPanel panel = new JPanel(new GridLayout(5, 4, 5, 5));

        String[] buttons = {
                "7", "8", "9", "/",
                "4", "5", "6", "*",
                "1", "2", "3", "-",
                "0", ".", "C", "+",
                "=", "", "", ""
        };

        for (String text : buttons) {
            if (text.isEmpty()) {
                panel.add(new JLabel());
                continue;
            }

            JButton btn = new JButton(text);
            btn.setFont(new Font("Arial", Font.BOLD, 30));
            btn.addActionListener(_ -> onClick(text));
            panel.add(btn);
        }

        add(panel, BorderLayout.CENTER);
    }

    private void connect() {
        try {
            Socket socket = new Socket(HOST, PORT);
            out = new PrintWriter(socket.getOutputStream(), true);
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        } catch (IOException e) {
            JOptionPane.showMessageDialog(this,
                    i18n.t("connection_error"),
                    "Error",
                    JOptionPane.ERROR_MESSAGE);
        }
    }

    private void onClick(String text) {
        switch (text) {
            case "C" -> display.setText("");
            case "=" -> send();
            default -> display.setText(display.getText() + text);
        }
    }

    private void send() {
        try {
            String expr = display.getText();
            if (expr.isEmpty()) return;

            expr = expr.replaceAll("([+\\-*/])", " $1 ");
            out.println(expr);

            String response = in.readLine();

            if (response.matches("-?\\d+(\\.\\d+)?")) {
                display.setText(response);
            } else {
                display.setText(i18n.t(response));
            }
        } catch (IOException e) {
            display.setText(i18n.t("connection_error"));
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() ->
                new CalculatorClientGUI().setVisible(true)
        );
    }
}