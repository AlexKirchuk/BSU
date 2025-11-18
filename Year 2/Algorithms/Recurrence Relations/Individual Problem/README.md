### Problem 63 — Ali-Baba and Coins

**Input file:** input.txt  
**Output file:** output.txt  
**Time limit:** 1 s  
**Memory limit:** no

On a road, there are gold coins scattered at certain positions. Each coin has a known position, given as an integer — the distance in meters from the starting point. All coins are located to the right of the starting point, at distinct distances.  

Ali-Baba runs along the road and collects coins, starting at time 0. He runs at a speed of **1 meter per second**. Each coin has a **deadline**, after which it disappears if not collected.  

Ali-Baba must collect all coins and minimize the total time spent. He can start at **any point**, collect coins in **any order**, but must collect all coins **before their deadlines**.

---

### Input

- The first line contains an integer `n` — the number of coins `(1 ≤ n ≤ 10,000)`.  
- Each of the next `n` lines contains two integers `d` and `t`:  
  - `d` — position of the coin `(1 ≤ d ≤ 10,000)`  
  - `t` — deadline in seconds `(1 ≤ t ≤ 10,000)`  

Coins are listed in **increasing order of distance**.

---

### Output

- Print a single integer — the **minimum time** needed for Ali-Baba to collect all coins.  
- If it is **impossible** to collect all coins before their deadlines, print: `No solution`.

---

### Example

<table>
  <tr>
    <th>input.txt</th>
    <th>output.txt</th>
  </tr>

  <tr>
    <td>
<pre>
5
1 3
3 1
5 8
8 19
10 15
</pre>
    </td>
    <td>
<pre>
11
</pre>
    </td>
  </tr>
</table>