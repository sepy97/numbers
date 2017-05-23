#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <history.h>
#include "Executor.h"

#include <QTextLine>
#include "colorpicker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool eventFilter(QObject *target, QEvent *event);//не трогать! это относится к нажатию клавиши enter

    history inputhistory;//создаем историю

private slots:
    void on_enterbut_clicked();

    void on_varbut_clicked();

    void on_clearbut_clicked();

    void makePlot (QString inpformula, double range_x_left, double range_x_right, double range_y_left, double range_y_right );

    void on_inptxt_cursorPositionChanged();

    void on_plotbut_clicked();

    void on_addPlotButton_clicked();
    
    void on_clearPlotButton_clicked();

    void on_lineTypeBox_currentIndexChanged(int index);

    void on_savePlotButton_clicked();

private:
    Ui::MainWindow *ui;
    Executor executor;
    QDockWidget* Form;
};

#endif // MAINWINDOW_H
