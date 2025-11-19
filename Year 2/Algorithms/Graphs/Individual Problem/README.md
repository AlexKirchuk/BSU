### Problem 19 — The Great Pyramid of Khufu

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 s  
**Memory limit:** no

Inside the Great Pyramid of Khufu there are **N rooms**, each containing **2M modules** forming **M devices**.  
Each device consists of two modules located in **two different rooms**, and it allows instant movement between these two rooms. The movement time is **0.5 time units**.

At time zero, all device modules enter **standby mode**.  
Each module has an individual **integer activation period**: after exactly this period expires, the module instantly turns on, then immediately returns to standby mode, repeatedly.

A device may be used **only at the moment when *both* of its modules are simultaneously active**.

Indiana Jones has entered the pharaoh’s tomb. After examining it, he activated all devices and prepared to leave — but at that moment, the tomb guardian awoke.  
Now Indiana must reach **room N** as quickly as possible, where the exit is located.  
Moving between rooms is possible **only via devices**, because the guardian has sealed all the doors.

The task is to compute the **minimum possible time** required to travel from **room 1** to **room N**, and output the sequence of devices that must be used.

---

### Input

- The first line contains an integer **N** — the number of rooms  
  **(2 ≤ N ≤ 10 000)**.
- The second line contains **M** — the number of devices  
  **(0 ≤ M ≤ 100 000)**.
- The next **M** lines contain the description of each device *i*:
  **R1,i** **T1,i** **R2,i** **T2,i**

Where:

- **R1,i**, **R2,i** — room numbers containing the two modules of device *i*  
- **T1,i**, **T2,i** — activation periods of the two modules  
  (the module in **R1,i** activates at times T1,i, 2·T1,i, 3·T1,i, …;  
  the module in **R2,i** activates at times T2,i, 2·T2,i, 3·T2,i, …)  
  **1 ≤ T1,i, T2,i ≤ 100 000**

Each device can be used **in both directions**, from either of its rooms.

---

### Output

- The first line must contain the **optimal minimal time**, with **absolute error ≤ 0.1**.
- The second line must contain the **sequence of device indices** to use in order to travel from room **1** to room **N** in minimal time.  
  If multiple solutions exist — output any.  
  A solution is guaranteed to exist.

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
5
1 6 2 4
2 1 3 7
3 1 4 1
4 2 5 8
2 2 4 9
</pre>
    </td>
    <td>
<pre>
16.5
1 2 3 4
</pre>
    </td>
  </tr>
</table>