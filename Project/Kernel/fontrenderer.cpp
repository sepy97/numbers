#include "fontrenderer.h"
#include <QPainter>
#include "mainwindow.h"

FontRenderer::FontRenderer(QWidget *widget) : QWidget(widget)
{
}

FontRenderer::~FontRenderer()
{

}

FontRenderer::elem sym_x[] =
{
    {10, 20, 20, 10},
    {20, 30, 30, 20}
};

FontRenderer::elem sym_y[] =
{
    {10, 20, 20, 10},
    {20, 30, 30, 20}
};

struct sym {
    int code;
    int width;
    int height;
    FontRenderer::elem *body;
} sym_table[] = {

{'x', 40, 50, sym_x},
{'y', 40, 50, sym_y}
};



void
FontRenderer::render_sym(QPainter *t, elem const *q, int x, int y, int height, int width)
{
    t->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    double mx = (double) width/40;
    double my = (double) height/50;
    QPoint p1, p2;
    for (int i = 0; q[i].xs != -1; i++)
    {
        p1.setX(x+q[i].xs*mx);
        p1.setY(y+q[i].ys*my);
        p2.setX(x+q[i].xe*mx);
        p2.setY(y+q[i].ye*my);
        t->drawLine(p1, p2);
    }
}

void FontRenderer::render(QPainter *t, int unicode_code_of_symbol, int x, int y, int height, int width)
{
    for (size_t i = 0; i < sizeof sym_table / sizeof sym_table[0]; i++) {
        if (unicode_code_of_symbol == sym_table[i].code) {
            render_sym(t, sym_table[i].body, x, y, width, height);
        }
    }
}

void FontRenderer::paintEvent(QPaintEvent * /*on_pushButton_clicked*/)
{
    QPainter qp(this);
    render(&qp, 'x', 5, 5, 40, 50);
}

