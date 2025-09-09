#include "pacman.h"

PacMan::PacMan(QString username, QWidget *parent)
    : QGraphicsView(parent),
    username(username),
    scene(new QGraphicsScene(this)),
    moveTimer(new QTimer(this)),
    mouthTimer(new QTimer(this))
{
    setWindowIcon(QIcon(":/img/img/pacman.png"));

    prepareWindow();
    prepareTimers();
    placeWalls();
    placeTextures();
    placeFood();
    placeGhosts();

    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

PacMan::~PacMan()
{ clearScene(); }

void PacMan::keyPressEvent(QKeyEvent *event)
{
    if (!mouthTimer->isActive())
    { mouthTimer->start(5); }

    switch (event->key())
    {
    case Qt::Key_Left:  nextDirection = "left";     break;
    case Qt::Key_Right: nextDirection = "right";    break;
    case Qt::Key_Up:    nextDirection = "up";       break;
    case Qt::Key_Down:  nextDirection = "down";     break;
    case Qt::Key_A:     nextDirection = "left";     break;
    case Qt::Key_D:     nextDirection = "right";    break;
    case Qt::Key_W:     nextDirection = "up";       break;
    case Qt::Key_S:     nextDirection = "down";     break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void PacMan::movePacman()
{
    if (!circle) return;

    double x = circle->x();
    double y = circle->y();

    if (canMoveInDirection(nextDirection, x, y))
        currentDirection = nextDirection;

    if (!canMoveInDirection(currentDirection, x, y)) return;

    if (currentDirection == "left")
    {
        x -= speed;
        circle->setRotation(180);
    }
    else if (currentDirection == "right")
    {
        x += speed;
        circle->setRotation(0);
    }
    else if (currentDirection == "up")
    {
        y -= speed;
        circle->setRotation(270);
    }
    else if (currentDirection == "down")
    {
        y += speed;
        circle->setRotation(90);
    }

    QVector<QGraphicsItem*> collidedItems = scene->collidingItems(circle);
    for (QGraphicsItem* item : collidedItems)
    {
        QGraphicsEllipseItem* food = dynamic_cast<QGraphicsEllipseItem*>(item);
        if (food && foodItems.contains(food))
        {
            scene->removeItem(food);
            foodItems.removeOne(food);
            delete food;
            updateScore(10);
        }
    }

    if (foodItems.isEmpty())
    {
        bonus += 100;
        score += bonus;
        placeFood();
        QMessageBox::information(this, "Board is cleared", "Your bonus is " + QString::number(bonus));
    }

    circle->setPos(x, y);
}

void PacMan::moveGhosts()
{
    for (int i = 0; i < ghosts.size(); ++i)
    {
        QGraphicsEllipseItem* ghost = ghosts[i];
        QString currentDir = ghostsDirections[i];
        double x = ghost->x();
        double y = ghost->y();

        QVector<QString> directions = {"left", "right", "up", "down"};
        QVector<QString> possibleDirs;

        for (const QString &dir : directions)
        {
            if (canGhostMoveInDirection(ghost, dir, x, y))
            { possibleDirs.append(dir); }
        }

        QString opposite;
        if (currentDir == "left")  opposite = "right";
        if (currentDir == "right") opposite = "left";
        if (currentDir == "up")    opposite = "down";
        if (currentDir == "down")  opposite = "up";

        if (possibleDirs.size() >= 3)
        {
            possibleDirs.removeAll(opposite);
            if (!possibleDirs.isEmpty())
            { currentDir = possibleDirs[rand() % possibleDirs.size()]; }
        }
        else if (!possibleDirs.contains(currentDir))
        {
            if (possibleDirs.size() > 1)
            { possibleDirs.removeAll(opposite); }

            if (!possibleDirs.isEmpty())
            { currentDir = possibleDirs[rand() % possibleDirs.size()]; }
        }

        ghostsDirections[i] = currentDir;
        if (currentDir == "left")  ghost->moveBy(-speed, 0);
        if (currentDir == "right") ghost->moveBy(speed, 0);
        if (currentDir == "up")    ghost->moveBy(0, -speed);
        if (currentDir == "down")  ghost->moveBy(0, speed);

        if (circle && ghost->collidesWithItem(circle))
        {
            moveTimer->stop();
            mouthTimer->stop();
            saveScore();
            QMessageBox::StandardButton reply = QMessageBox::critical(this, "Game Over", "You were caught by a ghost!", QMessageBox::Ok);
            if (reply == QMessageBox::Ok)
            { this->close(); }
        }
    }
}

void PacMan::animateMouth()
{
    if (mouthOpening)
        mouthAngle += 2;
    else
        mouthAngle -= 2;

    if (mouthAngle >= 30)
        mouthOpening = false;
    else if (mouthAngle <= 5)
        mouthOpening = true;

    updatePacmanShape();
}

inline void PacMan::prepareWindow()
{
    // Scene
    setFixedSize(450, 500);
    setScene(scene);
    scene->setSceneRect(0, 0, 400, 450);
    setStyleSheet("background-color: black;");
    setRenderHint(QPainter::Antialiasing);
    // Circle
    circle = new QGraphicsPathItem();
    scene->addItem(circle);
    circle->setBrush(Qt::yellow);
    circle->setPen(Qt::NoPen);
    circle->setPos(70, 110);
    circle->setTransformOriginPoint(pacmansize / 2, pacmansize / 2);
    // Mouth
    mouthAngle = 0;
    mouthOpening = true;
    circle->setRotation(90);
    updatePacmanShape();
    // "Score" Text
    scoreText = scene->addText("Score: 0");
    scoreText->setDefaultTextColor(Qt::white);
    scoreText->setFont(QFont("Arial", 16));
    scoreText->setPos(10, 430);
    // Username Text
    usernameText = scene->addText(username);
    usernameText->setDefaultTextColor(Qt::white);
    usernameText->setFont(QFont("Arial", 16));
    usernameText->setPos(230, 430);
}

inline void PacMan::prepareTimers()
{
    // Move Timer
    connect(moveTimer, &QTimer::timeout, this, &PacMan::movePacman);
    connect(moveTimer, &QTimer::timeout, this, &PacMan::moveGhosts);
    moveTimer->start(30);
    // Mouth Timer
    mouthTimer = new QTimer(this);
    connect(mouthTimer, &QTimer::timeout, this, &PacMan::animateMouth);
}

inline void PacMan::placeWalls()
{
    // A
    addWall(50, 50, 20, 100);
    addWall(90, 50, 20, 100);
    addWall(50, 50, 60, 60);
    // L
    addWall(130, 50, 20, 100);
    addWall(130, 130, 60, 20);
    // E
    addWall(210, 50, 20, 100);
    addWall(210, 50, 60, 20);
    addWall(210, 90, 60, 20);
    addWall(210, 130, 60, 20);
    // X
    addWall(290, 50, 20, 40);
    addWall(290, 110, 20, 40);
    addWall(330, 50, 20, 40);
    addWall(330, 110, 20, 40);
    addWall(310, 90, 20, 20);
    // P
    addWall(50, 170, 20, 100);
    addWall(50, 170, 60, 60);
    // R
    addWall(130, 170, 60, 100);
    // O
    addWall(210, 170, 60, 100);
    // J
    addWall(330, 170, 20, 100);
    addWall(290, 170, 60, 20);
    addWall(310, 250, 40, 20);
    addWall(290, 210, 20, 60);
    // GG
    addWall(210, 290, 20, 100);
    addWall(250, 330, 20, 60);
    addWall(210, 290, 60, 20);
    addWall(210, 370, 60, 20);

    addWall(290, 290, 20, 100);
    addWall(330, 330, 20, 60);
    addWall(290, 290, 60, 20);
    addWall(290, 370, 60, 20);
    // Borders
    addWall(15, 15, 15, 410);
    addWall(370, 15, 15, 410);
    addWall(15, 15, 370, 15);
    addWall(15, 410, 370, 15);
    // Ghost House
    addWall(50, 290, 20, 120);
    addWall(170, 290, 20, 120);
    addWall(50, 290, 60, 20);
    addWall(130, 290, 60, 20);
    addWall(90, 330, 20, 80);
    addWall(130, 330, 20, 80);
    // Misc
    addWall(170, 30, 20, 80);
    addWall(90, 250, 20, 20);
}

inline void PacMan::placeTextures()
{
    // Textures
    // A
    textures.append(scene->addRect(55, 55, 10, 90, QPen(Qt::red), QBrush(Qt::black)));
    textures.append(scene->addRect(95, 55, 10, 90, QPen(Qt::red), QBrush(Qt::black)));
    textures.append(scene->addRect(55, 55, 50, 10, QPen(Qt::red), QBrush(Qt::black)));
    textures.append(scene->addRect(55, 95, 50, 10, QPen(Qt::red), QBrush(Qt::black)));
    // L
    textures.append(scene->addRect(135, 55, 10, 90, QPen(Qt::yellow), QBrush(Qt::black)));
    textures.append(scene->addRect(135, 135, 50, 10, QPen(Qt::yellow), QBrush(Qt::black)));
    // E
    textures.append(scene->addRect(215, 55, 10, 90, QPen(Qt::green), QBrush(Qt::black)));
    textures.append(scene->addRect(215, 55, 50, 10, QPen(Qt::green), QBrush(Qt::black)));
    textures.append(scene->addRect(215, 95, 50, 10, QPen(Qt::green), QBrush(Qt::black)));
    textures.append(scene->addRect(215, 135, 50, 10, QPen(Qt::green), QBrush(Qt::black)));
    // X
    textures.append(scene->addRect(310, 90, 20, 20, QPen(Qt::white), QBrush(Qt::black)));
    textures.append(scene->addRect(300, 55, 10, 35, QPen(Qt::white), QBrush(Qt::black)));
    textures.append(scene->addRect(300, 110, 10, 35, QPen(Qt::white), QBrush(Qt::black)));
    textures.append(scene->addRect(330, 55, 10, 35, QPen(Qt::white), QBrush(Qt::black)));
    textures.append(scene->addRect(330, 110, 10, 35, QPen(Qt::white), QBrush(Qt::black)));
    // P
    textures.append(scene->addRect(55, 175, 10, 90, QPen(Qt::red), QBrush(Qt::black)));
    textures.append(scene->addRect(95, 175, 10, 50, QPen(Qt::red), QBrush(Qt::black)));
    textures.append(scene->addRect(55, 175, 50, 10, QPen(Qt::red), QBrush(Qt::black)));
    textures.append(scene->addRect(55, 215, 50, 10, QPen(Qt::red), QBrush(Qt::black)));
    // R
    textures.append(scene->addRect(135, 175, 10, 90, QPen(Qt::yellow), QBrush(Qt::black)));
    textures.append(scene->addRect(175, 175, 10, 50, QPen(Qt::yellow), QBrush(Qt::black)));
    textures.append(scene->addRect(135, 175, 50, 10, QPen(Qt::yellow), QBrush(Qt::black)));
    textures.append(scene->addRect(135, 215, 50, 10, QPen(Qt::yellow), QBrush(Qt::black)));
    textures.append(scene->addRect(145, 225, 10, 10, QPen(Qt::yellow), QBrush(Qt::black)));
    textures.append(scene->addRect(155, 235, 10, 10, QPen(Qt::yellow), QBrush(Qt::black)));
    textures.append(scene->addRect(165, 245, 10, 10, QPen(Qt::yellow), QBrush(Qt::black)));
    textures.append(scene->addRect(175, 255, 10, 10, QPen(Qt::yellow), QBrush(Qt::black)));
    // O
    textures.append(scene->addRect(215, 175, 10, 90, QPen(Qt::green), QBrush(Qt::black)));
    textures.append(scene->addRect(255, 175, 10, 90, QPen(Qt::green), QBrush(Qt::black)));
    textures.append(scene->addRect(215, 175, 50, 10, QPen(Qt::green), QBrush(Qt::black)));
    textures.append(scene->addRect(215, 255, 50, 10, QPen(Qt::green), QBrush(Qt::black)));
    // J
    textures.append(scene->addRect(335, 175, 10, 80, QPen(Qt::white), QBrush(Qt::black)));
    textures.append(scene->addRect(295, 175, 50, 10, QPen(Qt::white), QBrush(Qt::black)));
    textures.append(scene->addRect(305, 255, 30, 10, QPen(Qt::white), QBrush(Qt::black)));
    textures.append(scene->addRect(295, 215, 10, 40, QPen(Qt::white), QBrush(Qt::black)));
    // GG
    textures.append(scene->addRect(215, 305, 10, 70, QPen(Qt::magenta), QBrush(Qt::black)));
    textures.append(scene->addRect(255, 335, 10, 50, QPen(Qt::magenta), QBrush(Qt::black)));
    textures.append(scene->addRect(225, 295, 40, 10, QPen(Qt::magenta), QBrush(Qt::black)));
    textures.append(scene->addRect(225, 375, 40, 10, QPen(Qt::magenta), QBrush(Qt::black)));

    textures.append(scene->addRect(295, 305, 10, 70, QPen(Qt::magenta), QBrush(Qt::black)));
    textures.append(scene->addRect(335, 335, 10, 50, QPen(Qt::magenta), QBrush(Qt::black)));
    textures.append(scene->addRect(305, 295, 40, 10, QPen(Qt::magenta), QBrush(Qt::black)));
    textures.append(scene->addRect(305, 375, 40, 10, QPen(Qt::magenta), QBrush(Qt::black)));
    // Borders
    textures.append(scene->addRect(15, 15, 10, 410, QPen(Qt::blue), QBrush(Qt::black)));
    textures.append(scene->addRect(375, 15, 10, 410, QPen(Qt::blue), QBrush(Qt::black)));
    textures.append(scene->addRect(15, 15, 370, 10, QPen(Qt::blue), QBrush(Qt::black)));
    textures.append(scene->addRect(15, 415, 370, 10, QPen(Qt::blue), QBrush(Qt::black)));
    // Ghost House
    textures.append(scene->addRect(55, 295, 10, 120, QPen(Qt::blue), QBrush(Qt::black)));
    textures.append(scene->addRect(175, 295, 10, 120, QPen(Qt::blue), QBrush(Qt::black)));
    textures.append(scene->addRect(55, 295, 50, 10, QPen(Qt::blue), QBrush(Qt::black)));
    textures.append(scene->addRect(135, 295, 50, 10, QPen(Qt::blue), QBrush(Qt::black)));
    textures.append(scene->addRect(95, 335, 10, 80, QPen(Qt::blue), QBrush(Qt::black)));
    textures.append(scene->addRect(135, 335, 10, 80, QPen(Qt::blue), QBrush(Qt::black)));
    // Misc
    textures.append(scene->addRect(175, 25, 10, 80, QPen(Qt::blue), QBrush(Qt::black)));
    textures.append(scene->addRect(95, 255, 10, 10, QPen(Qt::blue), QBrush(Qt::black)));

    // Fill
    // A
    textures.append(scene->addRect(56, 56, 8, 88, QPen(Qt::black), QBrush(Qt::black)));
    textures.append(scene->addRect(96, 56, 8, 88, QPen(Qt::black), QBrush(Qt::black)));
    // L
    textures.append(scene->addRect(136, 56, 8, 88, QPen(Qt::black), QBrush(Qt::black)));
    // E
    textures.append(scene->addRect(216, 56, 8, 88, QPen(Qt::black), QBrush(Qt::black)));
    // P
    textures.append(scene->addRect(56, 176, 8, 88, QPen(Qt::black), QBrush(Qt::black)));
    textures.append(scene->addRect(96, 176, 8, 48, QPen(Qt::black), QBrush(Qt::black)));
    // R
    textures.append(scene->addRect(136, 176, 8, 88, QPen(Qt::black), QBrush(Qt::black)));
    textures.append(scene->addRect(176, 176, 8, 48, QPen(Qt::black), QBrush(Qt::black)));
    // O
    textures.append(scene->addRect(336, 176, 8, 78, QPen(Qt::black), QBrush(Qt::black)));
    // J
    textures.append(scene->addRect(336, 176, 8, 78, QPen(Qt::black), QBrush(Qt::black)));
    // G
    textures.append(scene->addRect(256, 336, 8, 48, QPen(Qt::black), QBrush(Qt::black)));

    textures.append(scene->addRect(336, 336, 8, 48, QPen(Qt::black), QBrush(Qt::black)));
    // Borders
    textures.append(scene->addRect(16, 16, 8, 408, QPen(Qt::black), QBrush(Qt::black)));
    textures.append(scene->addRect(376, 16, 8, 408, QPen(Qt::black), QBrush(Qt::black)));
    // Ghost House
    textures.append(scene->addRect(176, 24, 8, 80, QPen(Qt::black), QBrush(Qt::black)));
    textures.append(scene->addRect(56, 296, 8, 120, QPen(Qt::black), QBrush(Qt::black)));
    textures.append(scene->addRect(176, 296, 8, 120, QPen(Qt::black), QBrush(Qt::black)));
    textures.append(scene->addRect(96, 336, 8, 80, QPen(Qt::black), QBrush(Qt::black)));
    textures.append(scene->addRect(136, 336, 8, 80, QPen(Qt::black), QBrush(Qt::black)));
}

inline void PacMan::placeFood()
{
    const int ROWS = 19;
    const int COLS = 17;
    const int STARTING_X = 37;
    const int STARTING_Y = 37;
    const int SPACE = 20;

    for (int row = 0; row < ROWS; ++row)
    {
        for (int col = 0; col < COLS; ++col)
        {
            int x = STARTING_X + col * SPACE;
            int y = STARTING_Y + row * SPACE;

            QRectF foodRect(x, y, 1, 1);
            bool intersectsWall = false;

            for (auto wall : walls)
            {
                if (wall->sceneBoundingRect().intersects(foodRect))
                {
                    intersectsWall = true;
                    break;
                }
            }

            if (!intersectsWall)
                addFood(x, y);
        }
    }
}

inline void PacMan::placeGhosts()
{
    addGhost(110, 270, Qt::red);
    addGhost(70, 390, Qt::cyan);
    addGhost(110, 390, Qt::magenta);
    addGhost(150, 390, "#FFA500");

    ghostsDirections.resize(ghosts.size());
    for (int i = 0; i < ghosts.size(); ++i)
    {
        ghostsDirections[i] = "up";
        ghosts[i]->setTransformOriginPoint(ghostsize / 2, ghostsize / 2);
    }
}

void PacMan::addWall(double x, double y, double w, double h)
{
    QGraphicsRectItem* rect = scene->addRect(x, y, w, h, QPen(wallBorderColor), QBrush(wallFillColor));
    walls.append(rect);
}

void PacMan::addFood(double x, double y)
{
    QGraphicsEllipseItem *dot = scene->addEllipse(x, y, 6.0, 6.0, QPen(Qt::NoPen), QBrush(Qt::white));
    foodItems.append(dot);
}

void PacMan::addGhost(int x, int y, const QColor& color)
{
    QGraphicsEllipseItem* ghost = scene->addEllipse(0, 0, ghostsize, ghostsize, QPen(Qt::NoPen), QBrush(color));
    ghost->setPos(x, y);
    ghost->setZValue(1);
    ghosts.append(ghost);
    ghostsDirections.append(getRandomDirection());
}

bool PacMan::canMoveInDirection(const QString &dir, double x, double y)
{
    double testX = x;
    double testY = y;

    if (dir == "left")  testX -= speed;
    if (dir == "right") testX += speed;
    if (dir == "up")    testY -= speed;
    if (dir == "down")  testY += speed;

    QRectF futureBounds(testX + 0.5, testY + 0.5, pacmansize - 1.0, pacmansize - 1.0);

    for (auto wall : walls)
    {
        QRectF wallRect = wall->mapRectToScene(wall->boundingRect());
        if (wallRect.intersects(futureBounds))
        { return false; }
    }
    return true;
}

bool PacMan::canGhostMoveInDirection(QGraphicsEllipseItem* ghost, const QString &dir, double x, double y)
{
    if (dir == "left")   x -= speed;
    if (dir == "right")  x += speed;
    if (dir == "up")     y -= speed;
    if (dir == "down")   y += speed;

    QRectF nextRect(x, y, ghostsize, ghostsize);

    for (auto wall : walls)
    {
        if (wall->rect().translated(wall->pos()).intersects(nextRect))
        { return false; }
    }
    return true;
}

void PacMan::updatePacmanShape()
{
    QPainterPath path;
    double offset = (pacmansize - visualsize) / 2.0;

    path.moveTo(pacmansize / 2, pacmansize / 2);
    path.arcTo(offset, offset, visualsize, visualsize, mouthAngle, 360 - 2 * mouthAngle);
    path.closeSubpath();

    circle->setPath(path);
}

void PacMan::updateScore(int points)
{
    score += points;
    scoreText->setPlainText("Score: " + QString::number(score));
}

QString PacMan::getRandomDirection()
{
    const QVector<QString> directions = {"left", "right", "up", "down"};
    int idx = QRandomGenerator::global()->bounded(directions.size());
    return directions[idx];
}

void PacMan::saveScore()
{
    QVector<QPair<QString, int>> players;

    QFile file("scores.txt");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList parts = line.split(',');
            if (parts.size() == 2)
            {
                QString name = parts[0];
                int s = parts[1].toInt();
                players.append(qMakePair(name, s));
            }
        }
        file.close();
    }

    bool found = false;
    for (auto &p : players)
    {
        if (p.first == username)
        {
            found = true;
            if (score > p.second)
            { p.second = score; }
            break;
        }
    }

    if (!found)
    { players.append(qMakePair(username, score)); }

    std::sort(players.begin(), players.end(), [](const QPair<QString,int> &a, const QPair<QString,int> &b){
        return a.second > b.second;
    });

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        for (const auto &p : players)
        { out << p.first << "," << p.second << "\n"; }
        file.close();
    }
}

void PacMan::clearScene()
{
    for (QGraphicsRectItem* wall : walls)
    {
        scene->removeItem(wall);
        delete wall;
    }
    walls.clear();

    for (QGraphicsEllipseItem* food : foodItems)
    {
        scene->removeItem(food);
        delete food;
    }
    foodItems.clear();

    for (QGraphicsEllipseItem* ghost : ghosts)
    {
        scene->removeItem(ghost);
        delete ghost;
    }
    ghosts.clear();
    ghostsDirections.clear();
}
