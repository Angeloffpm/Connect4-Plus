#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Setup Board View's Scene:
    QGraphicsScene *boardScene = new QGraphicsScene(0, 0, ui->boardView->frameSize().width()-2, ui->boardView->frameSize().height()-2);
    ui->boardView->setScene(boardScene);
    // ui->boardView->setSceneRect(0, 0, ui->boardView->frameSize().width()-2, ui->boardView->frameSize().height()-2);
    qDebug() << boardScene->width();
    // Setup each Player's inventory Scene:
    QGraphicsScene *p1Scene = new QGraphicsScene(0, 0, ui->player1InventoryView->frameSize().width()-2, ui->player1InventoryView->frameSize().height()-2);
    QGraphicsScene *p2Scene = new QGraphicsScene(0, 0, ui->player2InventoryView->frameSize().width()-2, ui->player2InventoryView->frameSize().height()-2);
    ui->player1InventoryView->setScene(p1Scene);
    ui->player2InventoryView->setScene(p2Scene);
    // Setup GameDriver
    this->driver = new GameDriver(nullptr, boardScene, p1Scene, p2Scene);
    connect(driver, &GameDriver::closeGame, this, &MainWindow::closeGameSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Slot for close game, deletes the driver then closes.
void MainWindow::closeGameSlot() {
    delete driver;
    this->close();
}

