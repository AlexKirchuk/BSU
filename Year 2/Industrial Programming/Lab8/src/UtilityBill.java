import java.io.*;
import java.util.*;

public class UtilityBill implements Serializable {
    @Serial
    private static final long serialVersionUID = 1L;

    int houseNumber;
    static final String P_houseNumber = "House number";

    int apartmentNumber;
    static final String P_apartmentNumber = "Apartment number";

    String address;
    static final String P_address = "Address";

    String ownerName;
    static final String P_ownerName = "Owner name";

    String paymentDate;
    static final String P_paymentDate = "Payment date (YYYY-MM-DD)";

    double amount;
    static final String P_amount = "Payment amount";

    double penaltyPercent;
    static final String P_penaltyPercent = "Penalty percent";

    int overdueDays;
    static final String P_overdueDays = "Overdue days";

    static Boolean validNumber(int value) {
        return value > 0;
    }

    static Boolean validAmount(double value) {
        return value >= 0.0;
    }

    static Boolean validDate(String str) {
        return str.matches("\\d{4}-\\d{2}-\\d{2}");
    }

    public static boolean nextRead(Scanner fin, PrintStream out) {
        return nextRead(P_houseNumber, fin, out);
    }

    static boolean nextRead(final String prompt, Scanner fin, PrintStream out) {
        out.print(prompt);
        out.print(": ");
        return fin.hasNextLine();
    }

    public static UtilityBill read(Scanner fin, PrintStream out)
            throws IOException, NumberFormatException {
        String str;
        UtilityBill bill = new UtilityBill();

        str = fin.nextLine().trim();
        bill.houseNumber = Integer.parseInt(str);
        if (!validNumber(bill.houseNumber)) {
            throw new IOException("Invalid house number: " + bill.houseNumber);
        }

        if (!nextRead(P_apartmentNumber, fin, out)) return null;
        str = fin.nextLine().trim();
        bill.apartmentNumber = Integer.parseInt(str);
        if (!validNumber(bill.apartmentNumber)) {
            throw new IOException("Invalid apartment number: " + bill.apartmentNumber);
        }

        if (!nextRead(P_address, fin, out)) return null;
        bill.address = fin.nextLine();

        if (!nextRead(P_ownerName, fin, out)) return null;
        bill.ownerName = fin.nextLine();

        if (!nextRead(P_paymentDate, fin, out)) return null;
        bill.paymentDate = fin.nextLine().trim();
        if (!validDate(bill.paymentDate)) {
            throw new IOException("Invalid date format: " + bill.paymentDate);
        }

        if (!nextRead(P_amount, fin, out)) return null;
        str = fin.nextLine();
        bill.amount = Double.parseDouble(str);
        if (!validAmount(bill.amount)) {
            throw new IOException("Invalid amount: " + bill.amount);
        }

        if (!nextRead(P_penaltyPercent, fin, out)) return null;
        str = fin.nextLine();
        bill.penaltyPercent = Double.parseDouble(str);

        if (!nextRead(P_overdueDays, fin, out)) return null;
        str = fin.nextLine();
        bill.overdueDays = Integer.parseInt(str);

        return bill;
    }

    public UtilityBill() {}

    @Override
    public String toString() {
        return String.format(
                "House: %d, Apt: %d, Address: %s, Owner: %s, Date: %s, Amount: %.2f, Penalty: %.2f%%, Overdue: %d",
                houseNumber, apartmentNumber, address, ownerName, paymentDate,
                amount, penaltyPercent, overdueDays
        );
    }
}