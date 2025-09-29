public class Student {
    private final String lastName;

    public String getLastName() {
        return lastName;
    }

    private final String firstName;

    public String getFirstName() {
        return firstName;
    }

    private final String patronymic;

    public String getPatronymic() {
        return patronymic;
    }

    private final CreditBook creditBook;

    public CreditBook getCreditBook() {
        return creditBook;
    }

    public Student(String lastName, String firstName, String patronymic) {
        this.lastName = lastName;
        this.firstName = firstName;
        this.patronymic = patronymic;
        this.creditBook = new CreditBook();
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
