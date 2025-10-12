import java.util.*;

class EquilateralTriangle extends Triangle implements Comparable<EquilateralTriangle>, Comparator<EquilateralTriangle> {

    private final String borderColor;

    private final String fillColor;

    public String getFillColor() {
        return fillColor;
    }

    public EquilateralTriangle(double side, String borderColor, String fillColor) {
        super(side, side, 60.0);
        this.borderColor = borderColor;
        this.fillColor = fillColor;
    }

    public EquilateralTriangle(String text) {
        super(1, 1, 60.0);
        String[] parts = text.split(";");
        this.sideA = this.sideB = Double.parseDouble(parts[0]);
        this.angle = 60.0;
        this.borderColor = parts[1];
        this.fillColor = parts[2];
    }

    @Override
    public double getArea() {
        return (Math.sqrt(3) / 4) * sideA * sideA;
    }

    @Override
    public double getPerimeter() {
        return 3 * sideA;
    }

    @Override
    public String toString() {
        return String.format(Locale.US, "%.2f;%s;%s", sideA, borderColor, fillColor);
    }

    @Override
    public int compareTo(EquilateralTriangle other) {
        return Double.compare(this.sideA, other.sideA);
    }

    private String compareField = "side";

    public void setCompareField(String field) {
        this.compareField = field.toLowerCase();
    }

    @Override
    public int compare(EquilateralTriangle t1, EquilateralTriangle t2) {
        return switch (compareField) {
            case "area" -> Double.compare(t1.getArea(), t2.getArea());
            case "perimeter" -> Double.compare(t1.getPerimeter(), t2.getPerimeter());
            case "bordercolor" -> t1.borderColor.compareToIgnoreCase(t2.borderColor);
            case "fillcolor" -> t1.fillColor.compareToIgnoreCase(t2.fillColor);
            default -> Double.compare(t1.sideA, t2.sideA);
        };
    }

    @Override
    public Iterator<Object> iterator() {
        return new Iterator<>() {
            private int index = 0;
            private final Object[] fields = { sideA, borderColor, fillColor, getArea(), getPerimeter() };

            @Override
            public boolean hasNext() {
                return index < fields.length;
            }

            @Override
            public Object next() {
                if (!hasNext()) throw new NoSuchElementException();
                return fields[index++];
            }
        };
    }
}