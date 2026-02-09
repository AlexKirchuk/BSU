#include <QCoreApplication>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QVector>
#include <QSet>
#include <QRegularExpression>
#include <QDebug>

class MyException : public std::runtime_error
{
public:
    explicit MyException(const QString& message) : std::runtime_error(message.toStdString()) {}
    [[nodiscard]] QString whatAsQString() const
    {
        return QString::fromStdString(what());
    }
};

void readFile(const QString& filename, QString& str)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw MyException("File cannot be opened!");
    }
    QTextStream in(&file);
    str = in.readLine();
    file.close();
}

void writeToFile(const QString& filename, const QString& str)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        throw MyException("File cannot be opened!");
    }
    QTextStream out(&file);
    out << "New str: " << Qt::endl << str;
    file.close();
}

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    const QString inputName = "Input.txt";
    const QString outputName = "Output.txt";
    try
    {
        QString str;
        readFile(inputName, str);
        const QRegularExpression rx("[^\s.,;!?/ ]+");
        QRegularExpressionMatchIterator it = rx.globalMatch(str);
        QVector<QString> words;

        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            words.push_back(match.captured(0));
        }
        int maxUniqCount = 0;
        QVector<QString> maxWords;

        for (const QString& word : words)
        {
            QSet uniqChars(word.begin(), word.end());
            if (const int uniqueCount = static_cast<int>(uniqChars.size()); uniqueCount > maxUniqCount)
            {
                maxUniqCount = uniqueCount;
                maxWords.clear();
                maxWords.push_back(word);
            }
            else if (uniqueCount == maxUniqCount)
            {
                maxWords.push_back(word);
            }
        }
        const QString newStr = maxWords.join(" ");
        writeToFile(outputName, newStr);
        qDebug() << "New str: " << newStr;
    }
    catch (MyException& e)
    {
        qDebug() << "Exception: " << e.whatAsQString();
    }
    return QCoreApplication::exec();
}