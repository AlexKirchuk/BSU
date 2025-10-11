import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        ArrayList<Group> groups = readInput("Input.txt");
        writeExcellentStudents("output.txt", groups);
        printExcellentStudents(groups);
        printMyResults(groups);
    }

    public static ArrayList<Group> readInput(String filename) {
        ArrayList<Group> groups = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String line;
            Group currentGroup = null;
            Student currentStudent = null;
            CreditBook.Period currentPeriod = null;

            while ((line = br.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty() || line.startsWith("#")) continue;

                if (line.startsWith("YEAR")) {
                    String[] parts = line.split(" ");
                    int year = Integer.parseInt(parts[0].split(":")[1]);
                    int groupNumber = Integer.parseInt(parts[1].split(":")[1]);
                    currentGroup = new Group(year, groupNumber);
                    groups.add(currentGroup);
                } else if (line.startsWith("STUDENT")) {
                    String[] parts = line.split(":")[1].split(" ");
                    String lastName = parts[0];
                    String firstName = parts[1];
                    String patronymic = parts[2];
                    currentStudent = new Student(lastName, firstName, patronymic);
                    if (currentGroup != null) {
                        currentGroup.getStudents().add(currentStudent);
                    }
                } else if (line.startsWith("PERIOD")) {
                    assert currentStudent != null;
                    currentPeriod = new CreditBook.Period();
                    currentStudent.getCreditBook().getPeriods().add(currentPeriod);
                } else if (line.startsWith("SUBJECT")) {
                    String[] parts = line.split(" ");
                    String subjectName = parts[0].split(":")[1];
                    int grade = Integer.parseInt(parts[1].split(":")[1]);
                    boolean credit = Integer.parseInt(parts[2].split(":")[1]) == 1;

                    assert currentPeriod != null;
                    CreditBook.Period.Subject subject =
                            new CreditBook.Period.Subject(subjectName, credit, grade);
                    currentPeriod.getSubjects().add(subject);
                }
            }

        } catch (IOException e) {
            System.out.println("Error" + e);
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
                                        + ", Year: " + g.getYear()
                                        + ", Group: " + g.getGroupNumber()
                                        + ", Period: " + periodNum
                                        + ", Subject: " + s.subjectName()
                                        + ", Grade: " + s.grade());
                                bw.newLine();
                            }
                            periodNum++;
                        }
                    }
                }
            }
        } catch (IOException e) {
            System.out.println("Error" + e);
        }
    }

    public static void printExcellentStudents(ArrayList<Group> groups) {
        for (Group g : groups) {
            for (Student st : g.getStudents()) {
                if (st.getCreditBook().isExcellent()) {
                    int periodNum = 1;
                    for (CreditBook.Period p : st.getCreditBook().getPeriods()) {
                        for (CreditBook.Period.Subject s : p.getSubjects()) {
                            System.out.println(
                                    st.getLastName() + " " + st.getFirstName() + " " + st.getPatronymic()
                                            + ", Year: " + g.getYear()
                                            + ", Group: " + g.getGroupNumber()
                                            + ", Period: " + periodNum
                                            + ", Subject: " + s.subjectName()
                                            + ", Grade: " + s.grade()
                            );
                        }
                        System.out.println("Average Grade of Group this period: " + g.averageGradeOfGroupThisPeriod(periodNum));
                        periodNum++;
                    }
                }
            }
            System.out.println("Group: " + g.getGroupNumber()
                    + ", Excellent students: " + g.countExcellentStudents()
                    + ", Students with four: " + g.countStudentsWithFour()
            );
        }
    }

    public static void printMyResults(ArrayList<Group> groups) {
        Student st = groups.getFirst().getStudents().getFirst();
        int periodNum = 1;
        for (CreditBook.Period p : st.getCreditBook().getPeriods()) {
            for (CreditBook.Period.Subject s : p.getSubjects()) {
                System.out.println(
                        st.getLastName() + " " + st.getFirstName() + " " + st.getPatronymic()
                                + ", Year: " + groups.getFirst().getYear()
                                + ", Group: " + groups.getFirst().getGroupNumber()
                                + ", Period: " + periodNum
                                + ", Subject: " + s.subjectName()
                                + ", Grade: " + s.grade()
                );
            }
            periodNum++;
        }
        System.out.println("My Average Grade: " + st.averageGradeOfStudentForAllTime());
    }
}