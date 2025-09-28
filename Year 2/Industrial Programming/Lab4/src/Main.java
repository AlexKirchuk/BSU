import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        ArrayList<Group> groups = readInput("Input.txt");
        writeExcellentStudents("output.txt", groups);
    }

    public static ArrayList<Group> readInput(String filename) {
        ArrayList<Group> groups = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader("Input.txt"))) {
            String line;
            Group currentGroup = null;
            Student currentStudent = null;
            CreditBook.Period currentPeriod = null;

            while ((line = br.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty() || line.startsWith("#")) continue;

                if (line.startsWith("YEAR")) {
                    String[] parts = line.split(" ");
                    int year = Integer.parseInt(parts[0].split("=")[1]);
                    int groupNumber = Integer.parseInt(parts[1].split("=")[1]);
                    currentGroup = new Group(year, groupNumber);
                    groups.add(currentGroup);
                } else if (line.startsWith("STUDENT")) {
                    String[] parts = line.split("=")[1].split(" ");
                    String lastName = parts[0];
                    String firstName = parts[1];
                    String patronymic = parts[2];
                    currentStudent = new Student(lastName, firstName, patronymic, 0, 0);
                    if (currentGroup != null) {
                        currentGroup.getStudents().add(currentStudent);
                    }
                } else if (line.startsWith("PERIOD")) {
                    currentPeriod = currentStudent.getCreditBook().new Period();
                    currentStudent.getCreditBook().getPeriods().add(currentPeriod);
                } else if (line.startsWith("SUBJECT")) {
                    String[] parts = line.split(" ");
                    String subjectName = parts[0].split("=")[1];
                    int grade = Integer.parseInt(parts[1].split("=")[1]);
                    boolean credit = Integer.parseInt(parts[2].split("=")[1]) == 1;

                    CreditBook.Period.Subject subject =
                            currentPeriod.new Subject(subjectName, credit, grade);
                    currentPeriod.getSubjects().add(subject);
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

        return groups;
    }

    public static void writeExcellentStudents(String filename, ArrayList<Group> groups) {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(filename))) {
            for (Group g : groups) {
                for (Student st : g.getStudents()) {
                    if (st.getCreditBook().isExcellent()) {
                        int periodNum = 1;
                        for (CreditBook.Period p : st.getCreditBook().getPeriods()) {
                            for (CreditBook.Period.Subject s : p.getSubjects()) {
                                bw.write(st.getLastName() + " " + st.getFirstName() + " " + st.getPatronymic()
                                        + ", Year=" + g.getYear()
                                        + ", Group=" + g.getGroupNumber()
                                        + ", Period=" + periodNum
                                        + ", Subject=" + s.getSubjectName()
                                        + ", Grade=" + s.getGrade());
                                bw.newLine();
                            }
                            periodNum++;
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
