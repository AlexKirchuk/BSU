
import java.util.ArrayList;

public class CreditBook {
    public class Period {
        public class Subject {
            public String getSubjectName() {
                return subjectName;
            }

            private String subjectName;
            private boolean credit;

            public int getGrade() {
                return grade;
            }

            private int grade;

            public boolean isCredit() {
                return credit;
            }

            Subject(String subjectName, boolean credit, int grade) {
                this.subjectName = subjectName;
                this.credit = credit;
                this.grade = grade;
            }
        }

        public ArrayList<Subject> getSubjects() {
            return subjects;
        }

        private ArrayList<Subject> subjects = new ArrayList<>();

        public double getAverageGradeThisPeriod() {
            double sum = 0;
            int count = 0;
            for (Subject s: subjects) {
                sum += s.grade;
                count++;
            }
            return sum / count;
        }
    }

    public ArrayList<Period> getPeriods() {
        return periods;
    }

    private ArrayList<Period> periods = new ArrayList<>();

    public boolean isExcellent() {
        for (Period p : periods) {
            for (Period.Subject s : p.subjects) {
                if (!s.credit || s.grade < 9) {
                    return false;
                }
            }
        }
        return true;
    }

    public boolean doesHaveFours() {
        for (Period p : periods) {
            for (Period.Subject s : p.subjects) {
                if (!s.credit || s.grade < 4) {
                    return false;
                }
            }
        }
        return true;
    }

}
