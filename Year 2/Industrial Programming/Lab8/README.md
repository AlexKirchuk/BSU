# Lab 8 — Random Access File, Serialization, and Indexing

Design the classes specified in your individual assignment.  
Implement **exception handling** and validate input data.

Use **serialization** to store objects in a **binary random access file (RandomAccessFile)**.  
Organize **indexed and sequential access** to the file and implement the following operations (via command-line arguments and `System.in/out`):

1. **Populate the file** with test data.  
2. **Sequentially display all objects** without sorting.  
3. **Indexing** by one of the fields (assume the index fits in memory).  
   - Use **collections** to store the in-memory index.  
4. **Display all objects** in ascending or descending order of the index.  
5. **Search and display objects** by index, by index greater than a specified value, or by index less than a specified value.  
6. **Delete an object** by its index.

---

## Variant 7 — Utility Bills

Each utility bill object has the following attributes:

- House number  
- Apartment number  
- Address  
- Owner’s full name  
- Payment date  
- Payment amount  
- Penalty rate (%)  
- Number of days the payment is overdue

**Index the records** by:

- House number  
- Apartment number  
- Owner  
- Payment date