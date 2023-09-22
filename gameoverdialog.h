#ifndef GAMEOVERDIALOG_H
#define GAMEOVERDIALOG_H

#include <QDialog>

namespace Ui {
class GameOverDialog;
}

// Dialog opens after the game is over, asks player if they want
// to exit or restart a new game

class GameOverDialog : public QDialog
{
    Q_OBJECT

public:
    GameOverDialog(int p);
    ~GameOverDialog();

    // Getter
    bool get_startNewGame() { return this->startNewGame; };

private slots:
    void on_exit_Button_clicked();

    void on_newGame_Button_clicked();

private:
    Ui::GameOverDialog *ui;

    bool startNewGame;

};

#endif // GAMEOVERDIALOG_H
