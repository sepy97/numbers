#ifndef FONTRENDERER_H
#define FONTRENDERER_H
#include <QWidget>
#include <QtGui>

//namespace Ui {
//    class FontRenderer;
//}

class FontRenderer :  public QWidget
{
//private:
    Q_OBJECT

public:
    struct elem {
        int xs, ys;
        int xe, ye;
    };
    explicit FontRenderer(QWidget *widget = 0); // : w(widget) {}
    ~FontRenderer(); // {}
    virtual void render(QPainter *qp, int unicode_code_of_symbol, int x, int y, int width, int height);
private:
    virtual void render_sym(QPainter *qp, elem const *q, int x, int y, int width, int height);
protected:
    virtual void paintEvent(QPaintEvent *on_pushButton_clicked);
//    virtual void dummy();
//    FontRenderer    *ui;
//    QWidget *w;
};

#endif // FONTRENDERER_H
