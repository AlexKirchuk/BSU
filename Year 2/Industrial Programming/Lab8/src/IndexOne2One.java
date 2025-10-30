import java.io.Serial;
import java.io.Serializable;
import java.util.Arrays;
import java.util.Comparator;
import java.util.TreeMap;

public class IndexOne2One implements Serializable, IndexBase {
    @Serial
    private static final long serialVersionUID = 1L;
    private final TreeMap<String, Long> map = new TreeMap<>();

    public String[] getKeys(Comparator<String> comp) {
        String[] keys = map.keySet().toArray(new String[0]);
        Arrays.sort(keys, comp);
        return keys;
    }

    public void put(String key, long value) { map.put(key, value); }

    public boolean contains(String key) { return map.containsKey(key); }

    public Long[] get(String key) {
        Long pos = map.get(key);
        return (pos == null) ? new Long[0] : new Long[]{pos};
    }
}