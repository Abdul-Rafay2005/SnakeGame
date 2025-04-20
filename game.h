#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QVector>
#include <QPoint>
#include <QMessageBox>

class Game : public QWidget {
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateGame();

private:
    enum Direction { Up, Down, Left, Right };
    QVector<QPoint> snake;
    QPoint food;
    Direction dir;
    QTimer *timer;
    bool gameOver;
    int score;

    void move();
    void checkCollision();
    void generateFood();
    void resetGame();
    void showGameOverDialog();
};

#endif // GAME_H
