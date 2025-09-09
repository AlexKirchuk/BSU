#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pacman.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAuthor_triggered();
    void on_actionControls_triggered();
    void on_actionAbout_triggered();
    void on_startButton_clicked();
    void on_leaderboardButton_clicked();
    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
    PacMan* pacmanWindow = nullptr;
    QString username;
    int score;
};

#endif // MAINWINDOW_H
