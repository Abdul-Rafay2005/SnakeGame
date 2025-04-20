#include "game.h"
#include <QPainter>
#include <QRandomGenerator>

const int GRID_SIZE = 20;
const int GRID_WIDTH = 30;
const int GRID_HEIGHT = 20;

Game::Game(QWidget *parent) : QWidget(parent), dir(Right), gameOver(false), score(0) {
    setFixedSize(GRID_WIDTH * GRID_SIZE, GRID_HEIGHT * GRID_SIZE + 40);  // Extra space for score
    setStyleSheet("background-color: #121212;");

    snake.append(QPoint(5, 5));
    generateFood();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Game::updateGame);
    timer->start(100);
}

Game::~Game() {}

void Game::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    // Snake
    painter.setBrush(QColor("#00FF00"));
    for (const QPoint &p : snake) {
        painter.drawRect(p.x() * GRID_SIZE, p.y() * GRID_SIZE, GRID_SIZE, GRID_SIZE);
    }

    // Food
    painter.setBrush(QColor("#FF5555"));
    painter.drawEllipse(food.x() * GRID_SIZE, food.y() * GRID_SIZE, GRID_SIZE, GRID_SIZE);

    // Score
    painter.setPen(Qt::white);
    painter.setFont(QFont("Segoe UI", 14));
    painter.drawText(10, height() - 10, QString("Score: %1").arg(score));
}

void Game::keyPressEvent(QKeyEvent *event) {
    if (gameOver) return;

    switch (event->key()) {
    case Qt::Key_Up: if (dir != Down) dir = Up; break;
    case Qt::Key_Down: if (dir != Up) dir = Down; break;
    case Qt::Key_Left: if (dir != Right) dir = Left; break;
    case Qt::Key_Right: if (dir != Left) dir = Right; break;
    }
}

void Game::updateGame() {
    if (gameOver) return;

    move();
    checkCollision();
    update();
}

void Game::move() {
    QPoint head = snake.first();

    switch (dir) {
    case Up: head.ry() -= 1; break;
    case Down: head.ry() += 1; break;
    case Left: head.rx() -= 1; break;
    case Right: head.rx() += 1; break;
    }

    snake.prepend(head);

    if (head == food) {
        score += 5;
        generateFood();
    } else {
        snake.removeLast();
    }
}

void Game::checkCollision() {
    QPoint head = snake.first();

    // Wall
    if (head.x() < 0 || head.y() < 0 || head.x() >= GRID_WIDTH || head.y() >= GRID_HEIGHT) {
        gameOver = true;
        showGameOverDialog();
        return;
    }

    // Self
    for (int i = 1; i < snake.size(); ++i) {
        if (snake[i] == head) {
            gameOver = true;
            showGameOverDialog();
            return;
        }
    }
}

void Game::generateFood() {
    while (true) {
        int x = QRandomGenerator::global()->bounded(GRID_WIDTH);
        int y = QRandomGenerator::global()->bounded(GRID_HEIGHT);
        QPoint newFood(x, y);
        if (!snake.contains(newFood)) {
            food = newFood;
            break;
        }
    }
}

void Game::resetGame() {
    snake.clear();
    snake.append(QPoint(5, 5));
    dir = Right;
    score = 0;
    gameOver = false;
    generateFood();
    timer->start(100);
    update();
}

void Game::showGameOverDialog() {
    timer->stop();

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Game Over");
    msgBox.setText(QString("Game Over!\nYour score: %1").arg(score));
    msgBox.setInformativeText("Do you want to play again?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setStyleSheet("QMessageBox { background-color: #222; color: white; font-size: 14px; }");

    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes) {
        resetGame();
    } else {
        close();  // Exit
    }
}
