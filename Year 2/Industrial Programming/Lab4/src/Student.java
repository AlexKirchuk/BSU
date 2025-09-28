import java.util.ArrayList;

public class Student {
    private String lastName;

    public String getLastName() {
        return lastName;
    }

    private String firstName;

    public String getFirstName() {
        return firstName;
    }

    private String patronymic;

    public String getPatronymic() {
        return patronymic;
    }

    private CreditBook creditBook;

    public Student(String lastName, String firstName, String patronymic, int year, int groupName) {
        this.lastName = lastName;
        this.firstName = firstName;
        this.patronymic = patronymic;
        this.creditBook = new CreditBook();
    }

    public CreditBook getCreditBook() {
        return creditBook;
    }

    public double averageGradeOfStudentForAllTime() {
        double sum = 0;
        int count = 0;
        for (CreditBook.Period p : creditBook.getPeriods()) {
            sum += p.getAverageGradeThisPeriod();
            count++;
        }
        return sum / count;
    }
}
