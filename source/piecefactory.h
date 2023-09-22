#ifndef PIECEFACTORY_H
#define PIECEFACTORY_H

#include "piece.h"

// Flyweight Factory Design for Creating Gameboard Pieces

class PieceFactory
{
public:

    // Constructor
    PieceFactory();
    PieceFactory(int width, QColor p1, QColor p2);

    // Factory Piece Making
    Piece* get_piece(int x, int y, PieceType type = PieceType::Empty); // Defaults to Empty Piece

    // Setters
    void set_width(int w);
    void set_p1_color(QColor c);
    void set_p2_color(QColor c);

private:

    CommonData common_data_;

};

#endif // PIECEFACTORY_H
