#include "configtree.h"
#include "treemodel.h"
#include "plotcontroller.h"

#include <QFile>
#include <QStringList>

#include <iostream>

ConfigTree::ConfigTree( )
{
    view = new QTreeView();
    view->setObjectName(QString::fromUtf8("view"));
    view->setAlternatingRowColors( true );

    const QStringList headers({tr("Title"), tr("Description")});
    QFile file("default.txt");
    file.open(QIODevice::ReadOnly);
    TreeModel *model = new TreeModel(headers, file.readAll());
    file.close();

    view->setModel(model);
    for (int column = 0; column < model->columnCount(); ++column)
        view->resizeColumnToContents(column);

    layout = new QVBoxLayout( this );
    layout->addWidget(view);
}

ConfigTree::~ConfigTree()
{
    
}

void ConfigTree::setPlotController(PlotController* plot)
{
    plot_ = plot;

    auto series = repo_.getSeries("live_btc");
    plot_->addLiveSeries( series );

    auto sma1 = repo_.getSMA("live_btc", 100);
    plot->addSimpleMovingAverage(sma1);

    auto sma2 = repo_.getSMA("live_btc", 20);
    plot->addSimpleMovingAverage(sma2);

}