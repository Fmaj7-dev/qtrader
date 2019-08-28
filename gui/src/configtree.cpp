#include "configtree.h"
#include "treemodel.h"
#include "plotcontroller.h"
#include "utils/logger.h"
#include "treeview.h"

#include "ui_smaconfig.h"

#include <QFile>
#include <QStringList>
#include <QMenu>
#include <QAction>
#include <QSpinBox>

#include "utils/logger.h"

using namespace core;
using namespace core::analysis;


ConfigTree::ConfigTree( SeriesRepository& repo )
: repo_( repo )
{
    view = new TreeView();
    view->setObjectName(QString::fromUtf8("view"));

    const QStringList headers({tr("Title"), tr("Description")});
    model = new TreeModel(headers, "");

    // fill with series
    auto series = repo_.getAvailableSeries();
    for( auto& i : series)
    {
        QVector< QVariant > data;
        data<<i.c_str();
        model->addRow( data );
    }

    view->setModel(model);
    for (int column = 0; column < model->columnCount(); ++column)
        view->resizeColumnToContents(column);

    layout = new QVBoxLayout( this );
    layout->addWidget(view);

    // connect
    view->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(view, SIGNAL(customContextMenuRequested(const QPoint &)), 
        this, SLOT(ShowContextMenu(const QPoint &)));

    connect(view, SIGNAL(valueChanged(const QItemSelection&, const QItemSelection&)), 
            this, SLOT(plotSelected(const QItemSelection&,const QItemSelection&)));        

}

ConfigTree::~ConfigTree()
{
    
}

void ConfigTree::plotSelected(const QItemSelection&, const QItemSelection&)
{
    QModelIndexList selectedList = view->selectionModel()->selectedIndexes();
    QModelIndex selected = selectedList[0];
    QString name = model->data( model->index(selected.row(), 0), Qt::DisplayRole).toString();

    auto series = repo_.getSeries( name.toStdString() );
    plot_->addLiveSeries( series );

    // FIXME: get children and add SMA's
}

void ConfigTree::setPlotController(PlotController* plot)
{
    plot_ = plot;
}

void ConfigTree::ShowContextMenu(const QPoint &pos) 
{
    QModelIndexList selectedList = view->selectionModel()->selectedIndexes();
    QModelIndex selected = selectedList[0];
    QString name = model->data( model->index(selected.row(), 0), Qt::DisplayRole).toString();
    
    if( name.startsWith("live_") )
    {
        QMenu contextMenu(tr("Context menu"), this);

        QAction action1("Add Simple Moving Average", this);
        connect(&action1, SIGNAL(triggered()), this, SLOT(addSMA()));
        contextMenu.addAction(&action1);

        QAction action2("Add Exponential Moving Average", this);
        connect(&action2, SIGNAL(triggered()), this, SLOT(addEMA()));
        contextMenu.addAction(&action2);

        contextMenu.exec(mapToGlobal(pos));
    }
}

void ConfigTree::addSMA()
{
    QDialog dialog;
    Ui::SMAConfig config;
    config.setupUi(&dialog);
    int ret = dialog.exec();

    if ( ret == QDialog::Rejected )
        return;

    QModelIndexList selectedList = view->selectionModel()->selectedIndexes();
    QModelIndex selected = selectedList[0];
    QString name = model->data( model->index(selected.row(), 0), Qt::DisplayRole).toString();
    
    int value = config.spinBox->value();
    auto sma2 = repo_.getSMA(name.toStdString(), value);
    plot_->addSimpleMovingAverage(sma2);

    // insert sma item in tree
    QVector< QVariant > data;
    data<<name+" SMA "+QString::number(value);
    model->addChild( selected, data );
    view->update();

}

void ConfigTree::addEMA()
{

}