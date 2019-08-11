#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QHBoxLayout>
#include <QFileSystemModel>
#include <QTreeView>

#include "serieplot.h"

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;

    QWidget* widget = new QWidget();
    window.setCentralWidget(widget);

    // add plot
    SeriePlot* plot = new SeriePlot();

    // add tree
    /* QLabel* label = new QLabel();
    label->setText("label");*/
    QFileSystemModel* model = new QFileSystemModel();
    model->setFilter( QDir::Dirs | QDir::NoDotAndDotDot );
    model->setRootPath("");
    QTreeView* tree = new QTreeView();
    tree->setModel(model);

    // configure layout
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(tree);
    layout->addWidget(plot);
    widget->setLayout(layout);

    window.resize(500, 300);
    window.show();

    return a.exec();
}
