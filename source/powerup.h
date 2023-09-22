#ifndef POWERUP_H
#define POWERUP_H

#include <QObject>
#include <QGraphicsItem>
#include <QtWidgets>

enum class PowerupType { ColumnBomb, RowBomb, SquareBomb };

// Powerup Parent class defines basic information & methods for powerups

class Powerup : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Powerup(int x, int y);

    virtual PowerupType get_power();

    QRectF boundingRect() const override;

signals:
    void PowerupSelected(Powerup *p);

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    static const int width_ = 100;

    int x_;
    int y_;

};

// Child classes, inherit from Powerup:

class ColumnBomb : public Powerup
{
    Q_OBJECT
public:
    ColumnBomb(int x, int y);
    ~ColumnBomb();

    PowerupType get_power() override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

};

class RowBomb : public Powerup
{
    Q_OBJECT
public:
    RowBomb(int x, int y);
    ~RowBomb();

    PowerupType get_power() override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
};

class SquareBomb : public Powerup
{
    Q_OBJECT
public:
    SquareBomb(int x, int y);
    ~SquareBomb();

    PowerupType get_power() override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
};

#endif // POWERUP_H
