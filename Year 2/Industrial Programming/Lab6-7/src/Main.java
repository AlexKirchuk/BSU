import java.io.PrintStream;
import java.io.UnsupportedEncodingException;
import java.text.DateFormat;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.Locale;

public class Main {

    public static Necklace createNecklace(Locale locale) {
        Necklace necklace = new Necklace();
        necklace.addStone(new PreciousStone(AppLocale.getString(AppLocale.diamond), 2.5, 1000, 95, locale));
        necklace.addStone(new SemiPreciousStone(AppLocale.getString(AppLocale.amethyst), 3.2, 200, 85, locale));
        necklace.addStone(new PreciousStone(AppLocale.getString(AppLocale.ruby), 1.7, 850, 90, locale));
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
        try {
            if (args.length == 2) {
                return Locale.of(args[0], args[1]);
            } else if (args.length == 4) {
                return Locale.of(args[2], args[3]);
            }
        } catch (IllegalArgumentException e) {
            System.err.println("Invalid locale: " + e.getMessage());
        }
        return null;
    }

    private static void printNecklace(Necklace necklace, Locale locale) {
        DateFormat dateFormat = DateFormat.getDateTimeInstance(DateFormat.MEDIUM, DateFormat.MEDIUM, locale);
        for (Stone s : necklace.getStones()) {
            System.out.printf("%s — %.2f " + AppLocale.getString(AppLocale.ct) + " " + AppLocale.getString(AppLocale.value) + " %.2f, %s: %s%n",
                    s.getName(),
                    s.getWeight(),
                    s.getValue(),
                    AppLocale.getString(AppLocale.created_on),
                    dateFormat.format(s.getCreationDate()));
        }
    }

    public static void main(String[] args) {
        try {
            setupConsole(args);
            Locale loc = createLocale(args);
            if (loc == null) {
                System.err.println("""
                        Invalid argument(s)
                        Syntax: [-encoding ENCODING_ID] language country
                        Example: -encoding UTF8 en GB""");
                System.exit(1);
            }

            AppLocale.set(loc);

            String filename = "necklace.dat";
            NecklaceConnector.save(createNecklace(loc), filename);
            Necklace necklace = NecklaceConnector.load(filename).orElseThrow();

            System.out.println("=== " + AppLocale.getString(AppLocale.app_title) + " ===");
            printNecklace(necklace, loc);

            System.out.println("=== " + AppLocale.getString(AppLocale.sort) + " ===");
            necklace.sortByValue();
            printNecklace(necklace, loc);

            final int MIN_TR = 84;
            final int MAX_TR = 92;
            System.out.println("=== " + AppLocale.getString(AppLocale.found) + " [" + MIN_TR + "; " + MAX_TR +  "] ===");
            ArrayList<Stone> filtered = necklace.findByTransparency(MIN_TR, MAX_TR);
            for (Stone s : filtered) {
                System.out.println(s);
            }

            System.out.println(AppLocale.getString(AppLocale.app_title));
            System.out.println(AppLocale.getString(AppLocale.current_locale) + " " + loc.getDisplayName(loc));

            NumberFormat numFormat = NumberFormat.getNumberInstance(loc);

            System.out.println(AppLocale.getString(AppLocale.total_weight) + ": " +
                    numFormat.format(necklace.getTotalWeight()));
            System.out.println(AppLocale.getString(AppLocale.total_value) + ": " +
                    numFormat.format(necklace.getTotalValue()));

        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}