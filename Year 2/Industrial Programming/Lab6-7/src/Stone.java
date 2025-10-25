import java.io.Serializable;
import java.text.DateFormat;
import java.util.Date;
import java.util.Locale;

public abstract class Stone implements Serializable {
    private final String name;
    private final double weight;
    private final double pricePerCarat;
    private final double transparency;
    private final Date creationDate;
    private final Locale locale;

    public Stone(String name, double weight, double pricePerCarat, double transparency, Locale locale) {
        if (weight <= 0 || pricePerCarat <= 0 || transparency < 0 || transparency > 100)
            throw new IllegalArgumentException("Invalid stone parameters.");
        this.name = name;
        this.weight = weight;
        this.pricePerCarat = pricePerCarat;
        this.transparency = transparency;
        this.creationDate = new Date();
        this.locale = locale;
    }

    public String getName() { return name; }
    public double getWeight() { return weight; }
    public double getTransparency() { return transparency; }
    public Date getCreationDate() { return creationDate; }
    public double getValue() { return weight * pricePerCarat;}

    @Override
    public String toString() {
        DateFormat dateFormat = DateFormat.getDateTimeInstance(DateFormat.MEDIUM, DateFormat.MEDIUM, locale);
        return String.format(
                "%s (%s: %.2f %s %s: %.2f, %s: %.1f%%, %s: %.2f, %s%n))",
                name,
                AppLocale.getString(AppLocale.weight), weight, AppLocale.getString(AppLocale.ct),
                AppLocale.getString(AppLocale.pricePerCarat), pricePerCarat,
                AppLocale.getString(AppLocale.transparency), transparency,
                AppLocale.getString(AppLocale.value), getValue(),
                dateFormat.format(getCreationDate())
        );
    }
}