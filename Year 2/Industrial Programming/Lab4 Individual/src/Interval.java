public class Interval {
    private double left;
    private double right;

    public Interval() {
        this.left = 0;
        this.right = 1;
    }

    public Interval(double left, double right) {
        if (left > right) {
            throw new IllegalArgumentException("Left border cannot be bigger than right.");
        }
        this.left = left;
        this.right = right;
    }

    public Interval(Interval other) {
        this.left = other.left;
        this.right = other.right;
    }

    public double length() {
        return right - left;
    }

    public void shift(double value) {
        this.left += value;
        this.right += value;
    }

    public void scale(double k) {
        if (k <= 0) {
            throw new IllegalArgumentException("Coefficient must be more than 0");
        }
        double center = (left + right) / 2;
        double halfLength = length() * k / 2;
        this.left = center - halfLength;
        this.right = center + halfLength;
    }

    public int compareTo(Interval other) {
        return Double.compare(this.length(), other.length());
    }

    public Interval sum(Interval other) {
        double newLeft = Math.min(this.left, other.left);
        double newRight = Math.max(this.right, other.right);
        return new Interval(newLeft, newRight);
    }

    public Interval[] difference(Interval other) {
        if (other.right <= this.left || other.left >= this.right) {
            return new Interval[]{ new Interval(this) };
        }

        if (other.left <= this.left && other.right >= this.right) {
            return new Interval[]{};
        }

        if (other.left > this.left && other.right < this.right) {
            return new Interval[]{
                    new Interval(this.left, other.left),
                    new Interval(other.right, this.right)
            };
        }

        else if (other.left <= this.left) {
            return new Interval[]{ new Interval(other.right, this.right) };
        }

        else {
            return new Interval[]{ new Interval(this.left, other.left) };
        }
    }

    @Override
    public String toString() {
        return "(" + left + ", " + right + ")";
    }
}
