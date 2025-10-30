import java.util.Comparator;

public interface IndexBase {
    String[] getKeys(Comparator<String> comp);
    boolean contains(String key);
    Long[] get(String key);
}