package i18n;

import java.util.Locale;
import java.util.ResourceBundle;

public class I18n {

    private final ResourceBundle bundle;

    public I18n(String lang) {
        Locale locale = switch (lang.toLowerCase()) {
            case "ru" -> new Locale("ru");
            case "be" -> new Locale("be");
            default -> Locale.ENGLISH;
        };

        bundle = ResourceBundle.getBundle("i18n.messages", locale);
    }

    public String t(String key) {
        return bundle.containsKey(key) ? bundle.getString(key) : key;
    }
}