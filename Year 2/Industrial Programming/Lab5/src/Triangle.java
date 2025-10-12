import java.util.*;
import java.util.Iterator;

abstract class Triangle implements Iterable<Object> {
    protected double sideA;
    protected double sideB;
    protected double angle;

    public Triangle(double sideA, double sideB, double angle) {
        this.sideA = sideA;
        this.sideB = sideB;
        this.angle = angle;
    }

    public abstract double getArea();
    public abstract double getPerimeter();

    @Override
    public String toString() {
        return String.format(Locale.US, "%.2f;%.2f;%.2f", sideA, sideB, angle);
    }

    public Triangle(String text) {
        String[] parts = text.split(";");
        this.sideA = Double.parseDouble(parts[0]);
        this.sideB = Double.parseDouble(parts[1]);
        this.angle = Double.parseDouble(parts[2]);
    }

    @Override
    public Iterator<Object> iterator() {
        return new Iterator<>() {
            private int index = 0;
            private final Object[] fields = { sideA, sideB, angle };

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