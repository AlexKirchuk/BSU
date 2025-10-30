import java.io.Serial;
import java.io.Serializable;
import java.util.Arrays;
import java.util.Comparator;
import java.util.TreeMap;
import java.util.Vector;

public class IndexOne2N implements Serializable, IndexBase {
    @Serial
    private static final long serialVersionUID = 1L;
    private final TreeMap<String, Vector<Long>> map = new TreeMap<>();

    public String[] getKeys(Comparator<String> comp) {
        String[] keys = map.keySet().toArray(new String[0]);
        Arrays.sort(keys, comp);
        return keys;
    }

    public void put(String key, long value) {
        Vector<Long> list = map.get(key);
        if (list == null) list = new Vector<>();
        list.add(value);
        map.put(key, list);
    }

    public boolean contains(String key) { return map.containsKey(key); }

    public Long[] get(String key) {
        Vector<Long> list = map.get(key);
        return (list == null) ? new Long[0] : list.toArray(new Long[0]);
    }
}