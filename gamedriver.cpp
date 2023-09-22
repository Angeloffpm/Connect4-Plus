#include "gamedriver.h"

GameDriver::GameDriver(QObject *parent, QGraphicsScene *boardScene, QGraphicsScene *player1c, QGraphicsScene *player2c)
    : QObject{parent},
      boardScene(boardScene),
      player1c(player1c),
      player2c(player2c)
{
    this->board = new Board(boardScene);
    this->p1_turn = true;
    this->player1c->setBackgroundBrush(QBrush(Qt::green));
    this->game_over = false;
    this->selected_powerup = nullptr;

    // Add Column Buttons to Scene, connect to slot:
    for (int c = 0; c < 7; c++) {
        ColumnButton *cb = new ColumnButton(c * 100, 0, c);
        this->c_buttons_.push_back(cb);
        connect(cb, &ColumnButton::ColumnSignal, this, &GameDriver::ColumnSignalSlot);
        boardScene->addItem(cb);
    }

    // Give powerups
    this->give_pups();
}

// Method to restart the game
void GameDriver::restartGame() {

    // Reset our board
    qDebug() << "Resetting board & variables.";
    board->resetBoard();

    // Reset variables
    this->p1_turn = true;
    this->game_over = false;
    this->selected_powerup = nullptr;
    this->give_pups();
    qDebug() << "Finished resetting game.";

}

/* ColumnSignalSlot is called when the player clicks on a column to
 * place a piece.
 *
 * Will attempt to place the piece and advance the turn
 * if so.
 *
 * @param c: target column
*/
void GameDriver::ColumnSignalSlot(int c) {
    if (this->game_over) {
        qDebug() << "Game is already over.";
        return;
    }
    if (this->board->can_place(c)) { // Make sure column is not full

        // Handle if a Powerup is selected
        if (this->selected_powerup != nullptr) {
            // Use powerup
            if (this->selected_powerup->get_power() == PowerupType::ColumnBomb) {
                qDebug() << "Using column bomb.";
                this->board->place_ColumnBomb(c);
            } else if (this->selected_powerup->get_power() == PowerupType::RowBomb) {
                this->board->place_RowBomb(c);
                qDebug() << "Using row bomb.";
            } else {
                this->board->place_SquareBomb(c);
                qDebug() << "Using square bomb.";
            }

            // Remove powerup from player inventory and delete it
            if (this->p1_turn) {
                for (auto pu : this->p1_powerups) {
                    if (pu == selected_powerup) {
                        this->player1c->removeItem(selected_powerup);
                        pu = nullptr;
                    }
                }
            } else {
                for (auto pu : this->p2_powerups) {
                    if (pu == selected_powerup) {
                        this->player2c->removeItem(selected_powerup);
                        pu = nullptr;
                    }
                }
            }
            delete this->selected_powerup;
            this->selected_powerup = nullptr;
        }

        // Normal turn
        else if (this->p1_turn) {
            this->board->place_piece(c, 1);
        } else {
            this->board->place_piece(c, 2);
        }

        // Check for win
        int win = this->board->check_for_win();
        if (win == -1) { // Advance turn if no win yet
            this->nextTurn();
        } else { // Game Over Handler:
            qDebug() << "Player" << win << "wins.";
            this->game_over = true;
            game_od = new GameOverDialog(win);
            game_od->setModal(true);
            game_od->exec();
            if (!game_od->get_startNewGame()) {
                emit closeGame();
            } else {
                qDebug() << "Restarting game.";
                this->restartGame();
                return;
            }
        }

    } else {
        qDebug() << "Column full.";
    }
}

/* PowerupSelectedSlot is called when the clicks on a powerup
 * in an inventory.
 *
 * Checks to make sure the right player clicked on the powerup,
 * and selects it unless it is already selected, in which case
 * it is unselected.
 *
 * @param p: The powerup object that was clicked
 */
void GameDriver::PowerupSelectedSlot(Powerup *p) {

    // If powerup is already selected, unselect it & return
    if (this->selected_powerup == p) {
        this->selected_powerup = nullptr;
        return;
    }

    // Make sure powerup was selected by correct player:
    bool valid = false;
    if (this->p1_turn) {
        for (auto pu : this->p1_powerups) {
            if (pu == p) {
                valid = true;
            }
        }
    } else {
        for (auto pu : this->p2_powerups) {
            if (pu == p) {
                valid = true;
            }
        }
    }
    if (!valid) { return; }

    this->selected_powerup = p;

}

// Advances the turn and changes the background of who's turn it is.
void GameDriver::nextTurn() {
    if (p1_turn) {
        this->player1c->setBackgroundBrush(QBrush(Qt::white));
        this->player2c->setBackgroundBrush(QBrush(Qt::green));
    } else {
        this->player1c->setBackgroundBrush(QBrush(Qt::green));
        this->player2c->setBackgroundBrush(QBrush(Qt::white));
    }
    this->p1_turn = !this->p1_turn;
}

// Helper method that gives players default powerups
void GameDriver::give_pups() {
    this->player1c->clear();
    this->player2c->clear();
    this->p1_powerups.clear();
    this->p2_powerups.clear();

    ColumnBomb *cb1 = new ColumnBomb(0,0);
    connect(cb1, &Powerup::PowerupSelected, this, &GameDriver::PowerupSelectedSlot);
    RowBomb *rb1 = new RowBomb(100,0);
    connect(rb1, &Powerup::PowerupSelected, this, &GameDriver::PowerupSelectedSlot);
    SquareBomb *sqb1 = new SquareBomb(200,0);
    connect(sqb1, &Powerup::PowerupSelected, this, &GameDriver::PowerupSelectedSlot);
    this->p1_powerups = {cb1, rb1, sqb1};
    for (auto p : p1_powerups) {
        this->player1c->addItem(p);
    }

    ColumnBomb *cb2 = new ColumnBomb(0,0);
    connect(cb2, &Powerup::PowerupSelected, this, &GameDriver::PowerupSelectedSlot);
    RowBomb *rb2 = new RowBomb(100,0);
    connect(rb2, &Powerup::PowerupSelected, this, &GameDriver::PowerupSelectedSlot);
    SquareBomb *sqb2 = new SquareBomb(200,0);
    connect(sqb2, &Powerup::PowerupSelected, this, &GameDriver::PowerupSelectedSlot);
    this->p2_powerups = {cb2, rb2, sqb2};
    for (auto p : p2_powerups) {
        this->player2c->addItem(p);
    }

}
