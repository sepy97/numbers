#include "colorpalette.h"
#include <QImage>
#include <QDebug>
#include <QBitmap>

ColorPalette::ColorPalette(QWidget *parent) :
    QLabel(parent)
{
    setAutoFillBackground(true);
    QPalette pal;
    QPixmap pix(":/palette.png");
    setMask(pix.mask());
    pal.setBrush(backgroundRole(), QBrush(pix));
    setPalette(pal);
    resize(pix.size());
}

void ColorPalette::mousePressEvent(QMouseEvent *e)
{
    QRect onePixRect(e->pos(), QSize(1,1));
    QPixmap pix = QPixmap::grabWidget(this, onePixRect);
    QImage img = pix.toImage();
    QColor color(img.pixel(0, 0));
    emit Color(color);
}
