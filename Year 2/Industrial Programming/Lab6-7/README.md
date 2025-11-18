# Lab 6-7 — Object Serialization, Localization, and File Handling

The assignment is completed in **two stages**. Both results are submitted and evaluated.

---

## Stage 1

1. **Design the classes** specified in the task.  
2. Define **constructors, fields, and methods** to represent the problem domain. Implement the classes in a **Java console application**.  
3. **Serialize objects** of the application into one or more files.  
   - Objects may include `static` and `transient` fields.  
4. Create a **connector class** for retrieving and modifying objects in the file, with all necessary methods.  
5. Implement **exception handling** for scenarios such as:  
   - Out-of-memory errors  
   - Missing required records (objects) in the file  
   - Invalid field values, etc.

---

## Stage 2

1. **Add a `Date` field** to every class representing the domain, storing the creation time of the object. Print this field during testing.  
2. **Localize the application** for at least the following languages and regions:  
   - Russian (Russia)  
   - Belarusian (Belarus)  
   - English (United Kingdom)  

   The language and region for testing are passed via **command-line parameters**.

---

## Variant 7 — "Gemstones" System

- Define a **hierarchy of precious and semi-precious stones**.  
- Select stones for a **necklace**.  
- Compute the **total weight (in carats)** and **total value**.  
- Sort the stones in the necklace based on **value**.  
- Find stones in the necklace that match a **given transparency range**.