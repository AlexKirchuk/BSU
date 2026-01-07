# MyPacMan – Qt C++ Game Project

## Topic: Classic Pac-Man Game Implementation with Qt Graphics Framework

This project is a **Pac-Man–style 2D arcade game**, implemented in **C++17** using the **Qt framework**.
The goal of the project is to practice **event-driven programming**, **2D graphics**, and **game logic design** using the **Qt Graphics View Framework**.

The game is developed in **Qt Creator** using **QMake** and focuses on clean architecture, readable logic, and deterministic game behavior.

---

## Project Overview

The project implements the core mechanics of the classic **Pac-Man** game:

* Player-controlled Pac-Man movement
* Static maze built from wall segments
* Food placement with wall collision checks
* Randomly moving ghosts with constrained movement logic
* Score tracking and persistence
* Graphical interface using Qt Widgets

---

## Game Features

### Player (Pac-Man)

* Keyboard-controlled movement
* Collision detection with walls
* Food collection
* Score increase on food pickup

### Maze and Walls

* Maze constructed manually using `QGraphicsRectItem`
* Wall collision detection for both Pac-Man and ghosts
* Fixed game field size (17×19 logical grid)

### Food System

* Food is placed on a logical grid
* Food is not placed inside walls
* Each food item is represented as a simple point

### Ghosts

* Ghosts are represented as circles (`QGraphicsEllipseItem`)
* Movement is based on **random wandering**
* Direction changes occur only at **intersections**
* Ghosts cannot immediately reverse direction
* Wall collision checks prevent passing through walls

### Scoring

* Score increases when Pac-Man eats food
* Scores are saved to `scores.txt`

---

## Technologies Used

### Core Technologies

* **C++17**
* **Qt 5 / Qt 6** (Widgets + Graphics View)
* **QMake** build system
* **Qt Creator** IDE

### Qt Modules

* Qt Widgets
* Qt Graphics View Framework
* Qt Core
* Qt GUI

---

## Project Structure

```
Final MyPacMan/
│   appicon.rc
│   main.cpp
│   mainwindow.cpp
│   mainwindow.h
│   mainwindow.ui
│   MyPacMan.pro
│   MyPacMan.pro.user
│   pacman.cpp
│   pacman.h
│   pacman.ico
│   resource.qrc
│   scores.txt
│   ui_mainwindow.h
│
└───img/
        pacman.png
```

---

## Build Instructions

### Prebuilt Installer (Recommended)

A ready-to-use installer is available for this project.

* The installer contains a compiled version of the game
* No Qt or compiler installation is required
* Simply download, install, and run

The installer can be found in the **Releases** section of the GitHub repository.

---

### Requirements

* Qt Creator
* Qt 5 or Qt 6
* C++17-compatible compiler (MSVC / GCC / Clang)

### Build with Qt Creator

1. Open **Qt Creator**
2. Open `MyPacMan.pro`
3. Configure kit (Desktop)
4. Build and run the project

---

## Controls

| Key   | Action     |
| ----- | ---------- |
| W / ↑ | Move up    |
| S / ↓ | Move down  |
| A / ← | Move left  |
| D / → | Move right |

---

## Gameplay Logic Summary

* The game runs on a timer-based update loop
* Movement is processed per tick
* Collision detection uses `QGraphicsItem::collidesWithItem`
* Ghost AI is intentionally simple and non-deterministic

---

## Educational Purpose

This project is intended for:

* Learning Qt Graphics View Framework
* Practicing game loop logic
* Understanding collision detection
* Designing simple AI behaviors

---

## License

This project is intended for **educational purposes** and non-commercial use.

Inspired by the original **Pac-Man** game by Namco.