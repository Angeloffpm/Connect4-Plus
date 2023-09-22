#include "piecefactory.h"

// Constructors:
// Default
PieceFactory::PieceFactory()
{
    common_data_.width_ = 50;
    common_data_.p1_color = QColor(Qt::red);
    common_data_.p2_color = QColor(Qt::blue);
}
// With Parameters
PieceFactory::PieceFactory(int width, QColor p1, QColor p2) {
    common_data_.width_ = width;
    common_data_.p1_color = p1;
    common_data_.p2_color = p2;
}

// Factory Method that returns Piece at x, y, of specified type. Passes the common data
Piece* PieceFactory::get_piece(int x, int y, PieceType type) {
    return new Piece(x, y, &common_data_, type);
}

// Setters
void PieceFactory::set_width(int w) { common_data_.width_ = w; }
void PieceFactory::set_p1_color(QColor c) { common_data_.p1_color = c; }
void PieceFactory::set_p2_color(QColor c) { common_data_.p2_color = c; }
