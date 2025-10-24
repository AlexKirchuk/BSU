import java.io.File;
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;
import java.text.DateFormat;
import java.text.NumberFormat;
import java.util.Locale;

public class Main {

    public static Necklace createNecklace() {
        Necklace necklace = new Necklace();
        necklace.addStone(new PreciousStone(AppLocale.getString(AppLocale.diamond), 2.5, 1000, 95));
        necklace.addStone(new SemiPreciousStone(AppLocale.getString(AppLocale.amethyst), 3.2, 200, 80));
        necklace.addStone(new PreciousStone(AppLocale.getString(AppLocale.ruby), 1.7, 850, 90));
        return necklace;
    }

    static void setupConsole(String[] args) {
        if (args.length >= 2) {
            if (args[0].equals("-encoding")) {
                try {
                    System.setOut(new PrintStream(System.out, true, args[1]));
                } catch (UnsupportedEncodingException ex) {
                    System.err.println("Unsupported encoding: " + args[1]);
                    System.exit(1);
                }
            }
        }
    }

    static Locale createLocale(String[] args) {
        if (args.length == 2) {
            return new Locale(args[0], args[1]);
        } else if (args.length == 4) {
            return new Locale(args[2], args[3]);
        }
        return null;
    }

    public static void main(String[] args) {
        try {
            setupConsole(args);
            Locale loc = createLocale(args);
            if (loc == null) {
                System.err.println("Invalid argument(s)\n"
                        + "Syntax: [-encoding ENCODING_ID] language country\n"
                        + "Example: -encoding UTF8 en GB");
                System.exit(1);
            }

            AppLocale.set(loc);

            NecklaceConnector connector = new NecklaceConnector(new File("necklace_stage2.dat"));
            connector.write(createNecklace());
            Necklace necklace = connector.read();

            System.out.println(AppLocale.getString(AppLocale.app_title));
            System.out.println(AppLocale.getString(AppLocale.current_locale) + " " + loc.getDisplayName(loc));

            DateFormat dateFormat = DateFormat.getDateTimeInstance(DateFormat.MEDIUM, DateFormat.MEDIUM, loc);
            NumberFormat numFormat = NumberFormat.getNumberInstance(loc);

            for (Stone s : necklace.getStones()) {
                System.out.printf("%s — %.2f ct, %.2f value, %s: %s%n",
                        s.getName(),
                        s.getWeight(),
                        s.getValue(),
                        AppLocale.getString(AppLocale.created_on),
                        dateFormat.format(s.getCreationDate()));
            }

            System.out.println(AppLocale.getString(AppLocale.total_weight) + ": " +
                    numFormat.format(necklace.getTotalWeight()));
            System.out.println(AppLocale.getString(AppLocale.total_value) + ": " +
                    numFormat.format(necklace.getTotalValue()));

        } catch (Exception e) {
            System.err.println(e);
        }
    }
}