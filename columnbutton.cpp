#include "columnbutton.h"

QColor const ColumnButton::color_ = QColor(Qt::white);

// Constructor
ColumnButton::ColumnButton(int x, int y, int c)
    : x_(x),
      y_(y),
      column_(c)
{
}

// Painting Methods
QRectF ColumnButton::boundingRect() const {
    return QRectF(x_, y_, width_, height_);
}

void ColumnButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(item);

    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_));

    painter->drawRect(QRect(this->x_, this->y_, width_, height_));
    painter->setBrush(b);
}

// Mouse Pressed Event
void ColumnButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    emit ColumnSignal(this->column_);
    qDebug() << "Column " << this->column_ << " selected.";
}
