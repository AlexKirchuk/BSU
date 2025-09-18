import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

class CreditBook {
    private String lastName;
    private String firstName;
    private String patronymic;
    private int year;
    private String group;
    private ArrayList<Period> periods = new ArrayList<>();

    public CreditBook(String lastName, String firstName, String patronymic, int year, String group) {
        this.lastName = lastName;
        this.firstName = firstName;
        this.patronymic = patronymic;
        this.year = year;
        this.group = group;
    }

    public Period createPeriod(int periodNumber) {
        Period p = new Period(periodNumber);
        periods.add(p);
        return p;
    }

    public boolean isExcellent() {
        for (Period p : periods) {
            if (!p.allExamsExcellent() || !p.allCreditsPassed()) {
                return false;
            }
        }
        return true;
    }

    public String getFullName() {
        return lastName + " " + firstName + " " + patronymic;
    }

    public int getYear() {
        return year;
    }

    public String getGroup() {
        return group;
    }

    public ArrayList<Period> getPeriods() {
        return periods;
    }

    class Period {
        private int periodNumber;
        private ArrayList<Subject> subjects = new ArrayList<>();

        class Subject {
            String subjectName;
            boolean credit;
            int grade;

            Subject(String subjectName, boolean credit, int grade) {
                this.subjectName = subjectName;
                this.credit = credit;
                this.grade = grade;
            }
        }

        Period(int periodNumber) {
            this.periodNumber = periodNumber;
        }

        public void addExam(String subjectName, int grade) {
            subjects.add(new Subject(subjectName, false, grade));
        }

        public void addCredit(String subjectName) {
            subjects.add(new Subject(subjectName, true, 0));
        }

        public boolean allExamsExcellent() {
            for (Subject s : subjects) {
                if (!s.credit && s.grade < 9) {
                    return false;
                }
            }
            return true;
        }

        public boolean allCreditsPassed() {
            return true;
        }

        public ArrayList<Subject> getSubjects() {
            return subjects;
        }

        public int getPeriodNumber() {
            return periodNumber;
        }
    }
    void readFromFile(String filename) {
        BufferedReader br = null;
        try {
            br = new BufferedReader(new FileReader(filename));
            String line;
            while ((line = br.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.out.println("Error" + e);
        }
    }

}

public class Main {
    public static void main(String[] args) {

    }
}