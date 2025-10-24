import java.util.Locale;
import java.util.ResourceBundle;

public class AppLocale {
    private static ResourceBundle bundle;

    // Keys (for resource bundle)
    public static final String app_title = "app.title";
    public static final String current_locale = "language.selected";
    public static final String total_weight = "total.weight";
    public static final String total_value = "total.value";
    public static final String created_on = "stone.created";

    // Stone names
    public static final String diamond = "stone.diamond";
    public static final String ruby = "stone.ruby";
    public static final String amethyst = "stone.amethyst";

    public static void set(Locale locale) {
        bundle = ResourceBundle.getBundle("z6_7.stage2.resources.MessagesBundle", locale);
    }

    public static String getString(String key) {
        if (bundle == null) set(Locale.getDefault());
        return bundle.getString(key);
    }
}