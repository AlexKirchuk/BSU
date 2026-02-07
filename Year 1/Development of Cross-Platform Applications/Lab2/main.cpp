#include <QCoreApplication>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QVector>

class MyException : public std::runtime_error
{
public:
    explicit MyException(const QString& message) : std::runtime_error(message.toStdString()) {}
    [[nodiscard]] QString whatAsQString() const
    {
        return QString::fromStdString(what());
    }
};

int findFirstOf(const QString& str, const QString& chars)
{
    for (int i = 0; i < str.size(); ++i)
    {
        if (chars.contains(str[i])) return i;
    }
    return -1;
}

void removeDuplicates(QVector <QChar>& input)
{
    QVector <QChar> result;
    QSet <QChar> seen;
    for (const QChar& ch : input)
    {
        if (!seen.contains(ch))
        {
            seen.insert(ch);
            result.append(ch);
        }
    }
    input = result;
}

void readFile(const QString& filename, QString& str)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw std::runtime_error("File cannot be open!");
    }
    if (QTextStream in(&file); !in.atEnd())
    {
        str = in.readLine();
    }
    file.close();
}

void writeToFile(const QString& filename, const QString& str)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        throw std::runtime_error("File cannot be open!");
    }
    QTextStream out(&file);
    out << "New String: " << Qt::endl << str;
    file.close();
}

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    const QString sep = ".,;!?/ ";
    QString str, newStr, temp;
    int max = 0;
    QVector <QString> words;
    QVector <QVector <QChar>> chars;

    const QString inputName = "Input.txt";
    QFile input(inputName);
    const QString outputName = "Output.txt";
    QFile output(outputName);

    QTextStream in(&input);
    QTextStream out(&output);

    readFile(inputName, str);
    try
    {
        if (str.isEmpty()) qDebug() << "str is empty!";
    }
    catch (const MyException& e)
    {
        qDebug() << "Exception: " << e.what();
    }

    str += ' ';
    while (!str.isEmpty())
    {
        const int ind = findFirstOf(str, sep);
        if (ind)
        {
            temp.clear();
            temp.append(str);
            temp.remove(ind, str.length() - ind);
            words.push_back(temp);
        }
        str.remove(0, ind + 1);
    }

    for (auto & word : words)
    {
        QVector <QChar> tChars;
        for (int j = 0; j < word.size(); j++)
        {
            QChar tChar = word[j];
            tChars.push_back(tChar);
        }
        removeDuplicates(tChars);
        chars.push_back(tChars);
    }

    for (const auto & obj : chars)
    {
        if (max < obj.size()) max = static_cast<int>(obj.size());
    }

    for (auto & obj : chars)
    {
        if (max == obj.size())
        {
            for (const auto ch : obj)
            {
                newStr += ch;
            }
            newStr += " ";
        }
    }

    writeToFile(outputName, newStr);
    qDebug() << "New String: " << newStr;

    return QCoreApplication::exec();
}