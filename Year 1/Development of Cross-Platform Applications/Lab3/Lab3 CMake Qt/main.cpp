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

    // email
    qDebug() << Qt::endl << "Email check:";
    QRegularExpression reg("(https?:\/\/)?([^-_\n][a-zA-Z0-9-][^-_\n]{2,}\.?[^-_\n][a-zA-Z0-9-][^-_\n]{2,}\.[a-zA-Z]{2,})(:[0-9]+)?(\/[^\s]*)?(\\?[^\s]*)?(#[^\s]*)?$");
    QVector<QString> URLs =
    {
        "http://www.zcontest.ru",
        "http://zcontest.ru",
        "http://zcontest.com",
        "https://zcontest.ru",
        "https://sub.zcontest-ru.com:8080",
        "http://zcontest.ru/dir%201/dir_2/program.ext?var1=x&var2=my%20value",
        "zcon.com/index.html#bookmark",
        "Just Text.",
        "http://a.com",
        "http://www.domain-.com",
    };
    for (const auto& url : URLs)
    {
        QRegularExpressionMatch match = reg.match(url);
        if (match.hasMatch()) qDebug() << "Valid URL: " << url;
        else qDebug() << "Invalid URL: " << url;
    }

    return QCoreApplication::exec();
}