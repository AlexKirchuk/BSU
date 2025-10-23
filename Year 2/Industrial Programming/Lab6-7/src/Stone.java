import java.io.Serializable;

public abstract class Stone implements Serializable {
    private String name;
    private double weight;
    private double pricePerCarat;
    private double transparency;

    public Stone(String name, double weight, double pricePerCarat, double transparency) {
        if (weight <= 0 || pricePerCarat <= 0 || transparency < 0 || transparency > 100)
            throw new IllegalArgumentException("Invalid stone parameters.");
        this.name = name;
        this.weight = weight;
        this.pricePerCarat = pricePerCarat;
        this.transparency = transparency;
    }

    public double getValue() {
        return weight * pricePerCarat;
    }

    public String getName() { return name; }
    public double getWeight() { return weight; }
    public double getPricePerCarat() { return pricePerCarat; }
    public double getTransparency() { return transparency; }

    @Override
    public String toString() {
        return String.format("%s (weight: %.2f ct, price/car: %.2f, transparency: %.1f%%, value: %.2f)",
                name, weight, pricePerCarat, transparency, getValue());
    }
}
