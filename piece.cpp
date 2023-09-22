#include "piece.h"

// Constructors
  // Defaults to Empty Piece:
Piece::Piece(int x, int y, CommonData *data, PieceType type)
    : type_(type),
      x_(x),
      y_(y),
      common_data_(data)
{
}

// Setters =============================
void Piece::set_type(PieceType t) {
    this->type_ = t;
    this->update();
}
void Piece::set_x(int x) { this->x_ = x; }
void Piece::set_y(int y) { this->y_ = y; }
// =====================================

// Paint method for drawing the piece on the board
void Piece::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    Q_UNUSED(widget);

    QColor color = this->get_color_from_type();
    QBrush b = painter->brush();
    painter->setBrush(QBrush(color));

    painter->drawEllipse(QRect(this->x_, this->y_, common_data_->width_, common_data_->width_));
    painter->setBrush(b);
}

QRectF Piece::boundingRect() const
{
    return QRectF(x_, y_, common_data_->width_, common_data_->width_);
}

// Private helper method that returns the color based on type of piece:
QColor Piece::get_color_from_type() {
    QColor r;
    switch(this->type_) {
    case PieceType::Empty:
        r = QColor(Qt::white);
        break;
    case PieceType::Neutral:
        r = QColor(Qt::gray);
        break;
    case PieceType::P1:
        r = common_data_->p1_color;
        break;
    case PieceType::P2:
        r = common_data_->p2_color;
        break;
    default: // Should never be black
        r = QColor(Qt::black);
        break;
    }
    return r;
}
