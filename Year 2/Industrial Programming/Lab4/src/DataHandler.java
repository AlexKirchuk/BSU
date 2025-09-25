import java.io.*;
import java.util.*;

public class DataLoader {

    /**
     * Читает список студентов и их зачёток из файла.
     * Формат файла:
     * Фамилия Имя Отчество;Курс;Группа
     * <номер_сессии>;<название_предмета>;<тип>;<оценка>
     * ...
     * END
     *
     * @param filename путь к файлу input.txt
     * @return список студентов
     */
    public static ArrayList<Student> readStudents(String filename) {
        ArrayList<Student> students = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String line;
            Student currentStudent = null;

            while ((line = br.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty()) continue;

                if (line.equalsIgnoreCase("END")) {
                    // Конец данных одного студента
                    currentStudent = null;
                    continue;
                }

                String[] parts = line.split(";");
                if (parts.length == 3) {
                    // Новая запись студента
                    String[] fullName = parts[0].trim().split(" ");
                    String lastName = fullName[0];
                    String firstName = fullName[1];
                    String patronymic = fullName.length > 2 ? fullName[2] : "";
                    int course = Integer.parseInt(parts[1].trim());
                    int group = Integer.parseInt(parts[2].trim());

                    currentStudent = new Student(lastName, firstName, patronymic, course, group);
                    students.add(currentStudent);
                } else if (parts.length == 4 && currentStudent != null) {
                    // Добавление предмета
                    int periodNum = Integer.parseInt(parts[0].trim());
                    String subjectName = parts[1].trim();
                    String type = parts[2].trim().toLowerCase();
                    int grade = Integer.parseInt(parts[3].trim());

                    // Ищем существующую сессию
                    CreditBook.Period period = null;
                    for (CreditBook.Period p : currentStudent.getCreditBook().getPeriods()) {
                        if (p.getPeriodNumber() == periodNum) {
                            period = p;
                            break;
                        }
                    }
                    if (period == null) {
                        period = currentStudent.getCreditBook().addPeriod(periodNum);
                    }

                    boolean isCredit = type.equals("credit");
                    period.addSubjectInformation(subjectName, isCredit, grade);
                } else {
                    System.out.println("Пропущена некорректная строка: " + line);
                }
            }

        } catch (IOException e) {
            System.out.println("Ошибка чтения файла: " + e.getMessage());
        } catch (NumberFormatException e) {
            System.out.println("Ошибка преобразования числа: " + e.getMessage());
        }

        return students;
    }
}
