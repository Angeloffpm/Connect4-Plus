#include "gameoverdialog.h"
#include "ui_gameoverdialog.h"

GameOverDialog::GameOverDialog(int p) :
    ui(new Ui::GameOverDialog)
{
    ui->setupUi(this);
    std::string winner = "Player " + std::to_string(p) + " wins!";
    this->ui->PlayerXWins_Label->setText(QString::fromStdString(winner));
    this->startNewGame = false;
}

GameOverDialog::~GameOverDialog()
{
    delete ui;
}

// Exit button clicked -> just close the window
void GameOverDialog::on_exit_Button_clicked()
{
    this->close();
}

// New game, set to true then close
void GameOverDialog::on_newGame_Button_clicked()
{
    this->startNewGame = true;
    this->close();
}

