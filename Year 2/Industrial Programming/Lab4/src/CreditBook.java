import java.util.ArrayList;

public class CreditBook {
    public static class Period {
        public record Subject(String subjectName, boolean credit, int grade) {}

        private final ArrayList<Subject> subjects = new ArrayList<>();

        public ArrayList<Subject> getSubjects() {
            return subjects;
        }

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

    private final ArrayList<Period> periods = new ArrayList<>();

    public ArrayList<Period> getPeriods() {
        return periods;
    }

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
