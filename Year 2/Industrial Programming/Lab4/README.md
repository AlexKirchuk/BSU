# Lab 4 — Inner Classes and Collections

Develop a **Java console application** with the following tasks:

1. **Create a class `GradeBook`** with an inner class that stores information about sessions, credits, and exams.

2. **Implement a test program** to verify the functionality of the application.  
   Store student grade book information in a **collection**. For example, read student data from `input.txt` and write to `output.txt` information about students who:  
   - Are top students with all exam grades ≥ 9, and  
   - Have passed all credits.  

   For each student, the output should include:  
   - Last name, first name, middle name  
   - Course, group  
   - Session number (1–9)  
   - Subject name  
   - Exam grade

3. **Define a class `Student`** and attributes for "grades obtained by students in a session."  
   Use `assert` and exceptions where appropriate for error handling.  
   Implement methods to determine:  
   - The **average grade of a study group** for a session (use the `Group` class)  
   - The **average grade of students**  
   - The **number of top students**  
   - The **number of students with grade 4**

4. **Create a Makefile** with the following targets:  
   - `clean` — remove intermediate files  
   - `build` — recompile all classes and create an executable JAR  
   - `run` — execute the JAR file