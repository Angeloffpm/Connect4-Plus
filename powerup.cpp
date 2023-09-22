#include "powerup.h"

Powerup::Powerup(int x, int y)
    : x_(x),
      y_(y)
{
}

PowerupType Powerup::get_power() {
    return PowerupType::ColumnBomb;
}

QRectF Powerup::boundingRect() const {
    return QRectF(this->x_, this->y_, width_, width_);
}

void Powerup::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    qDebug() << "Powerup selected.";
    emit PowerupSelected(this);
}

// ColumnBomb Methods:

ColumnBomb::ColumnBomb(int x, int y)
    : Powerup(x, y)
{
}

ColumnBomb::~ColumnBomb(){}

PowerupType ColumnBomb::get_power() {
    return PowerupType::ColumnBomb;
}

void ColumnBomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(item);

    QBrush b = painter->brush();
    painter->setBrush(QBrush(Qt::gray));

    painter->drawEllipse(QRect(this->x_, this->y_, width_, width_));
    painter->setBrush(QBrush(Qt::black));
    painter->drawLine(this->x_ + (width_/2), this->y_ + (width_/5), this->x_ + (width_/2), this->y_ + (width_ - (width_/5)));
    painter->setBrush(b);
}

// RowBomb Methods

RowBomb::RowBomb(int x, int y)
    : Powerup(x, y)
{
}

RowBomb::~RowBomb(){}

PowerupType RowBomb::get_power() {
    return PowerupType::RowBomb;
}

void RowBomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(item);

    QBrush b = painter->brush();
    painter->setBrush(QBrush(Qt::gray));

    painter->drawEllipse(QRect(this->x_, this->y_, width_, width_));
    painter->setBrush(QBrush(Qt::black));
    painter->drawLine(this->x_ + (width_/5), this->y_ + (width_/2), this->x_ + (width_ - (width_/5)), this->y_ + (width_/2));
    painter->setBrush(b);
}

// SquareBomb Methods

SquareBomb::SquareBomb(int x, int y)
    : Powerup(x, y)
{
}

SquareBomb::~SquareBomb(){}

PowerupType SquareBomb::get_power() {
    return PowerupType::SquareBomb;
}

void SquareBomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(item);

    QBrush b = painter->brush();
    painter->setBrush(QBrush(Qt::gray));

    painter->drawEllipse(QRect(this->x_, this->y_, width_, width_));
    painter->setBrush(QBrush(Qt::black));
    int third = width_/3;
    painter->drawRect(this->x_ + third, this->y_ + third, third, third);
    painter->setBrush(b);
}
