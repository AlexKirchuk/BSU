import java.io.Serializable;
import java.util.stream.Collectors;
import java.util.ArrayList;
import java.util.Comparator;

public class Necklace implements Serializable {
    private final ArrayList<Stone> stones = new ArrayList<>();

    public void addStone(Stone stone) {
        stones.add(stone);
    }

    public double getTotalWeight() {
        return stones.stream().mapToDouble(Stone::getWeight).sum();
    }

    public double getTotalValue() {
        return stones.stream().mapToDouble(Stone::getValue).sum();
    }

    public void sortByValue() {
        stones.sort(Comparator.comparingDouble(Stone::getValue));
    }

    public ArrayList<Stone> findByTransparency(double min, double max) {
        return stones.stream()
                .filter(s -> s.getTransparency() >= min && s.getTransparency() <= max)
                .collect(Collectors.toCollection(ArrayList::new));
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("Necklace:\n");
        stones.forEach(s -> sb.append("  ").append(s).append("\n"));
        sb.append(String.format("Total weight: %.2f carats\n", getTotalWeight()));
        sb.append(String.format("Total value: %.2f\n", getTotalValue()));
        return sb.toString();
    }
}