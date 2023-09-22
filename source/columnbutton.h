#ifndef COLUMNBUTTON_H
#define COLUMNBUTTON_H

#include <QObject>
#include <QGraphicsItem>
#include <QtWidgets>

/* Invisible (White) Button above each column that players will click
 * to place their pieces on the board
 */
class ColumnButton : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    // Constructor
    ColumnButton(int x, int y, int c);

    // Painting
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

signals:
    void ColumnSignal(int c);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:

    int x_;
    int y_;
    int column_; // 0 thru 6
    static const QColor color_;
    static const int width_ = 100;
    static const int height_ = 100;

};

#endif // COLUMNBUTTON_H
