#include "configtree.h"
//#include "seriesplot.h"
#include "plotcontroller.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QHBoxLayout>
#include <QFileSystemModel>
#include <QTreeView>
#include <QDebug>
#include <QSplitter>

#include <iostream>

//QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); 
    QMainWindow window;

    QWidget* widget = new QWidget();
    window.setCentralWidget(widget);

    // plot
    PlotController* plotController = new PlotController();
    
    // configTree
    ConfigTree* configTree = new ConfigTree();
    configTree->setPlotController( plotController );

    // add splitter
    QSplitter* splitter = new QSplitter(widget);
    splitter->addWidget( configTree );
    splitter->addWidget( plotController );

    // configure layout
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget( splitter );
    widget->setLayout( layout );

    // show window
    window.resize(1800, 900);
    window.show();

    return a.exec();
}
