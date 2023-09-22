#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QGraphicsView>
#include <QDebug>

#include "piecefactory.h"

// Board class tracks the physical game board and interactions between the player and the board

class Board : public QObject
{
    Q_OBJECT
public:

    // Constructor, takes the Scene to draw on
    Board(QGraphicsScene *boardScene);

    // Reset Board method
    void resetBoard();

    // Methods
    bool can_place(int c);
    void place_piece(int c, int p);
    int check_for_win();
    void place_ColumnBomb(int c);
    void place_RowBomb(int c);
    void place_SquareBomb(int c);

signals:

private:

    int width_;
    int height_;
    QGraphicsScene *scene;

    // Board data [rows][columns]
        // top left is 0,0, bottom left is 5,0
        // top right is 0,6, bottom right is 5,6
    Piece* boardData[6][7];
    // Private helper functions to convert coordinates on 2d Array
    // to pixel coordinates on screen
    int get_x(int c) const;
    int get_y(int r) const;

    // Factory For Pieces:
    PieceFactory factory_;

    // Helper methods for checking for win:
    bool in_bounds(int r, int c) const;
    bool cfw_right(int r, int c, int streak, const PieceType &t);
    bool cfw_diag_right(int r, int c, int streak, const PieceType &t);
    bool cfw_up(int r, int c, int streak, const PieceType &t);
    bool cfw_diag_left(int r, int c, int streak, const PieceType &t);

    // Helper function for getting the top row from placing in a column:
    int get_row_from_col(int c) const;

};

#endif // BOARD_H
