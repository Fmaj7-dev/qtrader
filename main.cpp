#include "seriesrepository.h"

/* #include "plotting/configtree.h"
#include "plotting/plotcontroller.h" */

#include "simulation/simulationwidget.h"
#include "plotting/plottingwidget.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QLabel>
//#include <QHBoxLayout>
#include <QFileSystemModel>
#include <QTreeView>
#include <QDebug>
//#include <QSplitter>
#include <QTabWidget>

#include <iostream>

//QT_CHARTS_USE_NAMESPACE
using namespace gui;
using namespace gui::simulation;
using namespace gui::plotting;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); 
    QMainWindow window;
    SeriesRepository repository;

    QTabWidget* tab = new QTabWidget();
    //QWidget* widget = new QWidget();

    //tab->addTab(widget, "Values");
    tab->addTab(new PlottingWidget( repository ), "Plotting");
    tab->addTab(new SimulationWidget( repository ), "Simulation");

    window.setCentralWidget(tab);

    // plot
    // PlotController* plotController = new PlotController();
    
    // configTree
    //ConfigTree* configTree = new ConfigTree( repository );
    // configTree->setPlotController( plotController ); 

    // add splitter
    /* QSplitter* splitter = new QSplitter(widget);
    splitter->addWidget( configTree );
    splitter->addWidget( plotController ); */

    // configure layout
    /* QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget( splitter );
    widget->setLayout( layout ); */

    // show window
    window.resize(1800, 900);
    window.show();

    return a.exec();
}
