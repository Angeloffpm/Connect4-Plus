#ifndef PIECE_H
#define PIECE_H

#include <QObject>
#include <QColor>
#include <QtWidgets>
#include <QGraphicsItem>

// Enum class to each different type of piece
enum PieceType { Empty, P1, P2, Neutral };

// Common Data used by Flyweight Factory, defined here
// so Pieces recognize it.
struct CommonData {
    QColor p1_color;
    QColor p2_color;
    int width_;
};

// Pieces on the game board

class Piece : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Piece(int x, int y, CommonData *data, PieceType type = PieceType::Empty);

    // Getters
    PieceType get_type() const { return this->type_; };

    // Setters
    void set_type(PieceType t);
    void set_x(int x);
    void set_y(int y);

    // Painting
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    QRectF boundingRect() const override;


signals:

private:

    PieceType type_;
    QColor get_color_from_type();

    int x_;
    int y_;
    CommonData *common_data_;

};

#endif // PIECE_H
