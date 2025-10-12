import java.util.*;

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