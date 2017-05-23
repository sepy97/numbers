#ifndef COLORPALETTE_H
#define COLORPALETTE_H

#include <QWidget>
#include <QMouseEvent>
#include <QLabel>

class ColorPalette : public QLabel
{
    Q_OBJECT
public:
    explicit ColorPalette(QWidget *parent = 0);

signals:
    void Color(QColor color);

public slots:

protected:
    virtual void mousePressEvent(QMouseEvent *e);

};

#endif // COLORPALETTE_H
