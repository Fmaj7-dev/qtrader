#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QHBoxLayout>
#include <QFileSystemModel>
#include <QTreeView>
#include <QDebug>

#include "configtree.h"
#include "serieplot.h"
#include "sqldataprovider.h"

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); 
    QMainWindow window;

    SqlDataProvider sql;
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
