#include "configtree.h"
#include "seriesplot.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QHBoxLayout>
#include <QFileSystemModel>
#include <QTreeView>
#include <QDebug>

#include <iostream>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); 
    QMainWindow window;

    QWidget* widget = new QWidget();
    window.setCentralWidget(widget);

    // plot
    SeriesPlot* plot = new SeriesPlot();

    // configTree
    ConfigTree* configTree = new ConfigTree();
    configTree->setPlot( plot );

    // configure layout
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(configTree);
    layout->addWidget(plot);
    widget->setLayout(layout);

    window.resize(1024, 768);
    window.show();

    return a.exec();
}
