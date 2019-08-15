#include "configtree.h"
#include "serieplot.h"

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

    /*SeriesRepository repo;

    for (auto& i: {"live_btc", "live_bch", "live_eth"})
    {
        auto series = repo.getSeries(i);
        for(auto& serie : series.values)
            std::cout<<serie.value<<" ";
        std::cout<<std::endl<<std::endl;
    }*/

    qDebug() << QCoreApplication::libraryPaths();

    QWidget* widget = new QWidget();
    window.setCentralWidget(widget);

    // add plot
    SeriePlot* plot = new SeriePlot();

    // add tree
    /* QFileSystemModel* model = new QFileSystemModel();
    model->setFilter( QDir::Dirs | QDir::NoDotAndDotDot );
    model->setRootPath("");
    QTreeView* tree = new QTreeView();
    tree->setModel(model);*/

    ConfigTree* configTree = new ConfigTree();

    // configure layout
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(configTree);
    layout->addWidget(plot);
    widget->setLayout(layout);

    window.resize(500, 300);
    window.show();

    return a.exec();
}
