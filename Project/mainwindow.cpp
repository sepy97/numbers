#include "mainwindow.h"
#include "GrammarTree.h"
#include "ui_mainwindow.h"
#include "jkqtmathtext.h"
#include <QGraphicsScene>
#include <stdlib.h>

//graph
bool rightemptyborder_x = true;
bool rightemptyborder_y = true;
int number_of_graphs = 0;
int numpercent;
QPen p3;
//end of graph

bool iswheel = false;
int firsttime = 0;
int secondtime = 0;

//bool enter_clicked = false;//галочка, которая показывает, по нажатию кнопки или клавиши enter сработало событие

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->inptxt->installEventFilter(this);//не трогать! это относится к нажатию клавиши enter
    ui->resPlot->installEventFilter(this);


    ui->plotWidget->hide();

    p3.setColor(Qt::black); //graph
    p3.setWidth(3);         //graph

    inputhistory.add(ui->inptxt);//инициализируем историю
    Form = new QDockWidget;

    ui->lineTypeBox->addItem("Solid  line");
    ui->lineTypeBox->addItem("Dashed line");
    ui->lineTypeBox->addItem("Dotted line");

    this->setFixedSize(this->size());

    ui->inptxt->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_enterbut_clicked()
{
    //input.remove(input.size()-1, 1);
    QString input;
    input = ui->inptxt->toPlainText();
    if(input.size()==0){
    }else if(input[input.size()-1]=='\n'){
        ui->inptxt->setText(input);
    }else if(input[input.size()-1]=='*'){
        ui->inptxt->setText(input);
    }else{
        //здесь обновляется история
        inputhistory.add(ui->inptxt);
        //здесь обновляем вводимое поле
        inputhistory.allhistory.push_back("\n**************************");
        inputhistory.allhistory.push_back("\n");
        ui->inptxt->setText(inputhistory.allhistory);
        ui->inptxt->moveCursor(QTextCursor::End);
        //здесь исполняется то, что находится в input
        //QString tmp = (QString)executor.execAll(inputhistory.inphistory[inputhistory.inphistory.size()-1]).c_str();


        QPainter painter;              //Здесь пытаемся наладить LaTeX
        JKQTmathText mathText;
        mathText.useXITS();
        mathText.set_fontSize(20);  //Здесь прерываемся на вычисление строки

        ui->restxt->setPlainText(executor.execAll(inputhistory.inphistory[inputhistory.inphistory.size()-1].toStdString()).c_str());

        QPixmap pix(ui->restxt->toPlainText().length() * 11 , 300);
        pix.fill(QColor("white"));


        mathText.parse(executor.execAll(inputhistory.inphistory[inputhistory.inphistory.size()-1].toStdString()).c_str()); //Здесь парсим итоговую строку
        painter.begin(&pix);
        mathText.draw(painter, Qt::AlignTop , QRectF(0,0,pix.width(), pix.height()), false);
        painter.end();
        QGraphicsScene * scen = new QGraphicsScene();
        scen->addPixmap(pix);
        ui->graphicsView->setScene(scen);           //Закончили налаживать LaTeX
        ui->graphicsView->resize(600, 320);

        inputhistory.result.push_back(ui->restxt->toPlainText()); //сохраняем результат
    }
}

void MainWindow::on_varbut_clicked()
{
    //здесь должны выводиться все переменные и их значения
    ui->restxt->setText(executor.execAll("$vars\n").c_str());
}

void MainWindow::on_clearbut_clicked()
{
    //здесь должно очищаться все!
    ui->inptxt->clear();
    ui->restxt->clear();
    inputhistory.fullclear();
    ui->restxt->setText(executor.execAll("$clear\n").c_str());
}

bool MainWindow::eventFilter(QObject *target, QEvent *event){
    if (target == ui->inptxt){
        if (event->type() == QEvent::KeyPress ){//@@
            QKeyEvent *keyEvent = (QKeyEvent *)event;
            if (keyEvent->key() == Qt::Key_Return){   //не трогать! отправляет нажатие кнопки enter по нажатию клавиши return
                ui->enterbut->click();
            }else if(keyEvent->key() == Qt::Key_Up){  //не трогать! гуляет по истории от нажатия кнопки up
                if (inputhistory.pointer > 0){
                    inputhistory.pointer--;
                    QString tmpkeystr = ui->inptxt->toPlainText();
                    int i = tmpkeystr.size()-1;
                    QChar tmpkey = tmpkeystr[i];
                    while(tmpkey!='*'){
                        tmpkeystr.remove(i, 1);
                        i--;
                        tmpkey = tmpkeystr[i];
                    }
                    tmpkeystr.push_back('\n');
                    tmpkeystr.push_back(inputhistory.inphistory[inputhistory.pointer]);
                    ui->inptxt->setText(tmpkeystr);
                }
            }else if(keyEvent->key() == Qt::Key_Down){  //не трогать! гуляет по истории от нажатия кнопки down
                if (inputhistory.pointer < inputhistory.inphistory.size()-1){
                    inputhistory.pointer++;
                    QString tmpkeystr = ui->inptxt->toPlainText();
                    int i = tmpkeystr.size()-1;
                    QChar tmpkey;
                    while(tmpkey!='*'){
                        tmpkeystr.remove(i, 1);
                        i--;
                        tmpkey = tmpkeystr[i];
                    }
                    tmpkeystr.push_back('\n');
                    tmpkeystr.push_back(inputhistory.inphistory[inputhistory.pointer]);
                    ui->inptxt->setText(tmpkeystr);
                }
            }
        }else if (event->type()==QEvent::KeyRelease){
            QKeyEvent *keyEvent = (QKeyEvent *)event;
            if (keyEvent->key() == Qt::Key_Return){
                QString tmp = ui->inptxt->toPlainText();
                tmp.remove(tmp.size()-1, 1);
                ui->inptxt->setText(tmp);
            }
        }
    }
    if (target == ui->resPlot )
    {
        if (number_of_graphs > 0)
        {
            if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonRelease)
            {
                number_of_graphs--;
                makePlot(ui->inpLine->text(), ui->resPlot->xAxis->range().lower  , ui->resPlot->xAxis->range().upper , ui->resPlot->yAxis->range().lower , ui->resPlot->yAxis->range().upper );
            }
            else if (event->type() == QEvent::Wheel)
            {
                if (iswheel && ((secondtime-firsttime) >= 1000))
                {
                    number_of_graphs--;
                    makePlot(ui->inpLine->text(), ui->resPlot->xAxis->range().lower  , ui->resPlot->xAxis->range().upper , ui->resPlot->yAxis->range().lower , ui->resPlot->yAxis->range().upper );
                    iswheel = false;
                    firsttime = 0;
                    secondtime = 0;
                }
                else if (!iswheel)
                {
                    iswheel = true;
                    firsttime = clock();
                }
                else
                {
                    secondtime = clock();
                }
                //сюда поставить таймер для колесика мышки, чтобы обновлял при скроллинге через определенное время
            }
        }
    }
    if (target == Form)
    {
        if (event->type() == QEvent::Close )
        {
            on_clearPlotButton_clicked();
        }
    }
    return false;
}

//graph

void MainWindow::makePlot (QString inpformula, double range_x_left, double range_x_right, double range_y_left, double range_y_right )
{
    //QString inpformula = ui->inp_formula->toPlainText();
    double range_x = range_x_right - range_x_left;
    // Получи строку!
    GrammarTree gt(inpformula.toStdString());
    Tree t = gt.getTree();
    double step = range_x/10000;
    QVector<double> x;
    QVector<double> y;
    double i = range_x_left;
    for (long counter = 0; i < range_x_right; counter++)
    {
        x.push_back(i);
        Number dt(x[counter]);
        y.push_back(t.evaluate(&dt).toDouble());
        i+=step;
    }
    ui->resPlot->addGraph();
    numpercent = number_of_graphs%10;

    ui->resPlot->graph(numpercent)->setPen(p3);
        ui->resPlot->graph(numpercent)->setData(x,y);
        ui->resPlot->xAxis->setLabel("x");
        ui->resPlot->yAxis->setLabel("y");
        ui->resPlot->xAxis->setRange(range_x_left, range_x_right);
        ui->resPlot->yAxis->setRange(range_y_left, range_y_right);
    QVector<double> Ticks_x, Ticks_y;  // вектор с шагом в 30 градусов
    double in = range_x_left;
    double tik;
    tik = range_x/10;
    while(in<=range_x_right) {
        Ticks_x << in;
        in+=tik;
    }
    double tik1;
    double out = range_y_left;
    tik1 = range_y_right-range_y_left;
    tik1 /= 10;
    while(out<=range_y_right) {
        Ticks_y << out;
        out+=tik1;
        if (out <= 0.0001 && out >= -0.0001)
        {
            out = 0;
        }
    }
    ui->resPlot->xAxis->setAutoTicks(true); // выключаем автоматические отсчеты
    ui->resPlot->yAxis->setAutoTicks(true); // выключаем автоматические отсчеты
    ui->resPlot->xAxis->setTickVector(Ticks_x);  // задаем созданный нами вектор
    ui->resPlot->yAxis->setTickVector(Ticks_y);  // задаем созданный нами вектор
    ui->resPlot->replot();
    number_of_graphs++;
}

void MainWindow::on_inptxt_cursorPositionChanged()
{
    if (ui->inptxt->textCursor().position() <= inputhistory.allhistory.size()){
        ui->inptxt->moveCursor(QTextCursor::End);
    }
}

void MainWindow::on_plotbut_clicked()
{
    QString input;
    input = ui->inptxt->toPlainText();
    if(input.size()==0){
    }else if(input[input.size()-1]=='\n'){
        ui->inptxt->setText(input);
    }else if(input[input.size()-1]=='*'){
        ui->inptxt->setText(input);
    }else{
        Form->installEventFilter(this);
        Form->setWidget(ui->plotWidget);
        Form->setGeometry(ui->plotWidget->geometry());
        Form->setFixedSize(Form->width(), Form->height());
        Form->show();

        inputhistory.add(ui->inptxt);
        //здесь обновляем вводимое поле
        inputhistory.allhistory.push_back("\n**************************");
        inputhistory.allhistory.push_back("\n");
        ui->resPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

        ui->inptxt->setText(inputhistory.allhistory);
        ui->inptxt->moveCursor(QTextCursor::End);
        ui->colorPlotPalette->setSelectedColor(QColor::fromRgb(255, 0, 0) );
        ui->inpLine->setText(inputhistory.inphistory[inputhistory.inphistory.size()-1]);
    }
}

void MainWindow::on_addPlotButton_clicked()
{
    rightemptyborder_x = false;
    rightemptyborder_y = false;
    p3.setColor(ui->colorPlotPalette->selectedColor() );

    makePlot(ui->inpLine->text(), -100, 100, -100, 100);


    ui->resPlot->replot();

    //ui->resPlot->graph(number_of_graphs-1)->rescaleAxes(true);
    //ui->resPlot->xAxis->setAutoTicks(true);
    //ui->resPlot->yAxis->setAutoTicks(true);
}

void MainWindow::on_clearPlotButton_clicked()
{
    ui->resPlot->clearGraphs();
    ui->resPlot->replot();
    number_of_graphs = 0;
    ui->inpLine->clear();
    ui->inpLine->setFocus();
/*    ui->border_x_txt_left->clear();
    ui->border_x_txt_right->clear();
    ui->border_y_txt_left->clear();
    ui->border_y_txt_right->clear();
    ui->inp_formula->clear();
    ui->inp_formula->setFocus();*/
    rightemptyborder_x = true;
    rightemptyborder_x = true;
}

void MainWindow::on_lineTypeBox_currentIndexChanged(int index)
{
    switch (index) {
        case 0: //SOLID
        {
            //ui->graph_wid->graph(number_of_graphs)->setLineStyle(Qt::SolidLine);
            p3.setStyle(Qt::SolidLine);
            break;
        }
        case 1: //DASH
        {
            //ui->graph_wid->graph(number_of_graphs)->setLineStyle(Qt::DashLine);
            p3.setStyle(Qt::DashLine);
            break;
        }
        case 2: //DOT
        {
            //ui->graph_wid->graph(number_of_graphs)->setLineStyle(Qt::DotLine);
            p3.setStyle(Qt::DotLine);
            break;
        }
        default:
            break;
    }
}

void MainWindow::on_savePlotButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("Choose a filename to save under"),
                                                        QString(),
                                                        tr("PNG(*.png);;JPG(*.jpg);;PDF(*.pdf);;BMP(*.bmp);;All Files(*)")
                                                        );
    if(!fileName.isEmpty())
    {
        if(fileName.endsWith(".png", Qt::CaseInsensitive))
        {
            ui->resPlot->savePng(fileName);
        }
        else if(fileName.endsWith(".jpg", Qt::CaseInsensitive))
        {
            ui->resPlot->saveJpg(fileName);
        }
        else if(fileName.endsWith(".pdf", Qt::CaseInsensitive))
        {
            ui->resPlot->savePdf(fileName);
        }
        else if(fileName.endsWith(".bmp", Qt::CaseInsensitive))
        {
            ui->resPlot->saveBmp(fileName);
        }
        else
        {
            fileName += ".png";
            ui->resPlot->savePng(fileName);
        }
    }
}

/*void QDockWidget::closeEvent(QCloseEvent *event)
{

}*/
