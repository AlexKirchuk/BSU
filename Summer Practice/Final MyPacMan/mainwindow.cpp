#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(600, 400);
    setWindowIcon(QIcon(":/img/img/pacman.png"));
}

MainWindow::~MainWindow()
{ delete ui; }

void MainWindow::on_actionAuthor_triggered()
{
    QMessageBox::information(this, "Author",
                             "Created by Alex Kirchuk\n"
                             "Email: a.kirtchouk@gmail.com\n"
                             "Year: 2025");
}

void MainWindow::on_actionControls_triggered()
{
    QMessageBox::information(this, "Controls",
                             "Controls:\n\n"
                             "Move Pac-Man using:\n"
                             " - Arrow Keys (↑ ↓ ← →)\n"
                             " - or W A S D");
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "About MyPacMan",
                             "This project is a fan-made recreation of Pac-Man for educational and non-commercial purposes only.\n"
                             "All rights to the original Pac-Man game and characters belong to their respective owners.\n"
                             "No copyright infringement is intended.");
}

void MainWindow::on_startButton_clicked()
{
    if (ui->enterName->text().isEmpty())
        QMessageBox::warning(this, "Warning",
                             "Enter your name");
    else if (ui->enterName->text().size() > 13)
        QMessageBox::warning(this, "Warning",
                             "Max 13 characters!");
    else
    {
        username = ui->enterName->text();
        pacmanWindow = new PacMan(username);
        pacmanWindow->setAttribute(Qt::WA_DeleteOnClose);
        connect(pacmanWindow, &PacMan::destroyed, this, &MainWindow::show);
        pacmanWindow->show();
        this->hide();
    }
}

void MainWindow::on_leaderboardButton_clicked()
{
    QFile file("scores.txt");
    QString text;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        int rank = 1;
        while (!in.atEnd() and rank <= 10)
        {
            QString line = in.readLine();
            QStringList parts = line.split(',');
            if (parts.size() == 2)
            {
                QString name = parts[0];
                QString score = parts[1];
                text += QString::number(rank) + ". " + name + " - " + score + "\n";
                rank++;
            }
        }
        file.close();
    }
    else
    { text = "No scores found."; }

    QMessageBox::information(this, "Leaderboard", text);
}

void MainWindow::on_exitButton_clicked()
{
    this->close();
    qApp->quit();
}
