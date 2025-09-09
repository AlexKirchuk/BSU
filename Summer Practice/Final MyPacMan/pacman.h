#ifndef PACMAN_H
#define PACMAN_H

#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsPathItem>
#include <QKeyEvent>
#include <QTimer>
#include <QBrush>

class PacMan : public QGraphicsView
{
    Q_OBJECT

public:
    PacMan(QString username, QWidget *parent = nullptr);
    ~PacMan();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void movePacman();
    void moveGhosts();
    void animateMouth();

private:
    inline void prepareWindow();
    inline void prepareTimers();
    inline void placeWalls();
    inline void placeTextures();
    inline void placeFood();
    inline void placeGhosts();

    void addWall(double x, double y, double w, double h);
    void addFood(double x, double y);
    void addGhost(int x, int y, const QColor& color);

    bool canMoveInDirection(const QString &dir, double x, double y);
    bool canGhostMoveInDirection(QGraphicsEllipseItem* ghost, const QString &dir, double x, double y);
    void updatePacmanShape();
    void updateScore(int points);
    QString getRandomDirection();
    void saveScore();
    void clearScene();

    QGraphicsScene *scene;
    QGraphicsPathItem *circle;
    int dx = 0;
    int dy = 0;
    double speed = 2.0;
    double visualsize = 16.0;
    double pacmansize = 20.0;
    int mouthAngle = 30;
    bool mouthOpening = false;

    QTimer *moveTimer;
    QTimer *mouthTimer;

    QString currentDirection;
    QString nextDirection;

    QVector<QGraphicsRectItem*> walls;
    QColor wallBorderColor = Qt::black;
    QColor wallFillColor = Qt::black;
    QVector<QGraphicsRectItem*> textures;

    QVector<QGraphicsEllipseItem*> foodItems;

    QVector<QGraphicsEllipseItem*> ghosts;
    QVector<QString> ghostsDirections;
    double ghostsize = 20.0;

    QString username;
    int score = -10;
    int bonus = 0;
    QGraphicsTextItem *usernameText = nullptr;
    QGraphicsTextItem *scoreText = nullptr;
};

#endif // PACMAN_H
