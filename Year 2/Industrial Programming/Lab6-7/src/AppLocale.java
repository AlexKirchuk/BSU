import java.util.Locale;
import java.util.ResourceBundle;

public class AppLocale {
    private static final String strMsg = "resources.Msg";
    private static Locale locale = Locale.getDefault();
    private static ResourceBundle bundle = ResourceBundle.getBundle( AppLocale.strMsg, AppLocale.locale );

    public static final String app_title = "app.title";
    public static final String current_locale = "language.selected";

    public static final String total_weight = "total.weight";
    public static final String total_value = "total.value";

    public static final String sort = "necklace.sort";
    public static final String found = "necklace.found";

    public static final String diamond = "stone.diamond";
    public static final String ruby = "stone.ruby";
    public static final String amethyst = "stone.amethyst";

    public static final String created_on = "stone.created";
    public static final String ct = "stone.ct";
    public static final String value = "stone.value";
    public static final String weight = "stone.weight";
    public static final String pricePerCarat = "stone.pricePerCarat";
    public static final String transparency = "stone.transparency";

    static void set( Locale locale ) {
        AppLocale.locale = locale;
        bundle = ResourceBundle.getBundle( AppLocale.strMsg, AppLocale.locale );
    }

    public static String getString(String key) {
        if (bundle == null) set(Locale.getDefault());
        return bundle.getString(key);
    }
}