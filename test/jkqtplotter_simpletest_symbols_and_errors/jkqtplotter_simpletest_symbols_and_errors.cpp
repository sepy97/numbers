#include <QApplication>
#include "jkqtplotter.h"

// number of datapoints:
#define Ndata 10

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // 1. create a plotter window and get a pointer to the internal datastore (for convenience)
    JKQtPlotter plot;
    JKQTPdatastore* ds=plot.getDatastore();

    // 2. now we create data for a simple plot (a sine curve with lin. increasing errors)
    double X[Ndata], Y[Ndata], YERROR[Ndata];
    for (int i=0; i<Ndata; i++) {
        X[i]=double(i)/double(Ndata)*2.0*M_PI;
        Y[i]=sin(X[i]);
        YERROR[i]=0.2+double(i)/double(Ndata)*0.25;
    }

    // 3. make data available to JKQtPlotter by adding it to the internal datastore.
    //    Note: In this step the data is copied (of not specified otherwise), so you can
    //          reuse X and Y afterwards!
    //    the variables columnX and columnY will contain the internal column ID of the newly
    //    created columns with names "x" and "y" and the (copied) data from X and Y.
    size_t columnX=ds->addCopiedColumn(X, Ndata, "x");
    size_t columnY=ds->addCopiedColumn(Y, Ndata, "y");
    size_t columnYE=ds->addCopiedColumn(YERROR, Ndata, "y-error");

    // 4. create a graph in the plot, which plots the dataset X/Y:
    JKQTPxyLineErrorGraph* graph1=new JKQTPxyLineErrorGraph(&plot);
    graph1->set_xColumn(columnX);
    graph1->set_yColumn(columnY);
    graph1->set_yErrorColumn(columnYE);
    graph1->set_symbol(JKQTPfilledStar); // set symbol style
    graph1->set_yErrorStyle(JKQTPerrorBars); // set error indicator type
    graph1->set_drawLine(false); // don't draw a line
    graph1->set_title(QObject::tr("sine graph"));

    // 5. add the graph to the plot, so it is actually displayed
    plot.addGraph(graph1);

    // 6. hide 0-lines
    plot.getXAxis()->set_showZeroAxis(false);
    plot.getYAxis()->set_showZeroAxis(false);

    // 7. set some axis properties (we use LaTeX for nice equation rendering)
    plot.getXAxis()->set_axisLabel(QObject::tr("x-axis $x$ [mm]"));
    plot.getYAxis()->set_axisLabel(QObject::tr("\\textbf{\\color{red}{y-axis} $\\left(y=\\sin(x)\\pm(0.2+0.25\\cdot x)\\right)$ [A.U.]}"));
    plot.getXAxis()->set_labelFont("Arial");
    plot.getYAxis()->set_labelFont("Times New Roman");
    plot.getYAxis()->set_labelFontSize(12); // large x-axis label
    plot.getYAxis()->set_tickLabelFontSize(10); // and larger y-axis tick labels

    // 8. autoscale the plot so the graph is contained
    plot.zoomToFit();

    // show plotter and make it a decent size
    plot.show();
    plot.resize(600,400);

    return app.exec();
}
