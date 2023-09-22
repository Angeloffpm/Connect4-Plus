#ifndef GAMEDRIVER_H
#define GAMEDRIVER_H

#include <QObject>
#include <QGraphicsView>

#include "board.h"
#include "columnbutton.h"
#include "powerup.h"
#include "gameoverdialog.h"

// Main Driver Class

class GameDriver : public QObject
{
    Q_OBJECT
public:
    explicit GameDriver(QObject *parent = nullptr, QGraphicsScene *boardScene = nullptr, QGraphicsScene *player1c = nullptr, QGraphicsScene *player2c = nullptr);

    // Methods
    void restartGame();

signals:
    void closeGame();

private slots:
    void ColumnSignalSlot(int c);
    void PowerupSelectedSlot(Powerup *p);

private:

    // Board & Different scenes
    Board *board;
    QGraphicsScene *boardScene;
    QGraphicsScene *player1c;
    QGraphicsScene *player2c;

    // Tracks whos turn & game over:
    bool p1_turn;
    void nextTurn();
    bool game_over;

    // Vector of ColumnButtons:
    std::vector<ColumnButton*> c_buttons_;

    // Powerups
    std::vector<Powerup *> p1_powerups;
    std::vector<Powerup *> p2_powerups;
    Powerup *selected_powerup;
    // Helper method for giving powerups
    void give_pups();

    // Game Over Dialog
    GameOverDialog* game_od;

};

#endif // GAMEDRIVER_H
