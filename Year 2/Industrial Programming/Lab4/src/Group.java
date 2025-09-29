import java.util.ArrayList;

public class Group {
    private final int year;

    public int getYear() {
        return year;
    }

    private final int groupNumber;

    public int getGroupNumber() {
        return groupNumber;
    }

    private final ArrayList<Student> students;

    public ArrayList<Student> getStudents() {
        return students;
    }

    public Group(int year, int groupNumber) {
        this.year = year;
        this.groupNumber = groupNumber;
        this.students = new ArrayList<>();
    }

    public double averageGradeOfGroupThisPeriod(int periodNumber) {
        double sum = 0;
        int count = 0;
        for (Student st : students) {
            sum += st.getCreditBook().getPeriods().get(periodNumber - 1).getAverageGradeThisPeriod();
            count++;
        }
        return sum / count;
    }

    public int countExcellentStudents() {
        int count = 0;
        for (Student st : students) {
            if (st.getCreditBook().isExcellent()) {
                count++;
            }
        }
        return count;
    }

    public int countStudentsWithFour() {
        int count = 0;
        for (Student st : students) {
            if (st.getCreditBook().doesHaveFours()) {
                count++;
            }
        }
        return count;
    }
}
