#include "plotting/configtree.h"
#include "plotting/treemodel.h"
#include "plotting/treeitem.h"
#include "plotting/plotcontroller.h"
#include "plotting/treeview.h"
#include "utils/logger.h"

#include "ui_smaconfig.h"

#include <QFile>
#include <QStringList>
#include <QMenu>
#include <QAction>
#include <QSpinBox>

using namespace core;
using namespace core::analysis;
using namespace gui;
using namespace gui::plotting;


ConfigTree::ConfigTree( SeriesRepository& repo )
: repo_( repo )
{
    // create tree
    view = new TreeView();
    view->setObjectName(QString::fromUtf8("view"));

    const QStringList headers({tr("Series Name")/*, tr("Description")*/});
    model = new TreeModel(headers, "");

    // fill model with series
    auto series = repo_.getAvailableSeries();
    for( auto& i : series)
    {
        QVector < QVariant > data;
        data << i.c_str();
        model->addLiveSeries( data );
    }

    view->setModel( model );

    // resize to content
    for (int column = 0; column < model->columnCount(); ++column)
        view->resizeColumnToContents( column );

    // add view to layout
    layout = new QVBoxLayout( this );
    layout->addWidget( view );

    // connect
    view->setContextMenuPolicy(Qt::CustomContextMenu);

    connect( view, SIGNAL( customContextMenuRequested( const QPoint & ) ), 
        this, SLOT( ShowContextMenu( const QPoint & )));

    connect(view, SIGNAL( valueChanged( const QItemSelection&, const QItemSelection& )), 
            this, SLOT( plotSelected( const QItemSelection&, const QItemSelection& )));        

}

ConfigTree::~ConfigTree()
{
    
}

void ConfigTree::plotSelected( const QItemSelection&, const QItemSelection& )
{
    QModelIndexList selectedList = view->selectionModel()->selectedIndexes();
    QModelIndex selected = selectedList[0];
    

    // FIXME: get children and add SMA's
    TreeItemType type = model->getType( selected );
    /*if( type == TreeItemType::SMA )
        core::utils::log("SMA");*/

    using namespace core::utils;

    if ( type != TreeItemType::LIVE_SERIES )
        selected = model->parent( selected );

    //if ( type == TreeItemType::LIVE_SERIES )
    {
        QString name = model->data( model->index(selected.row(), 0), Qt::DisplayRole).toString();
        auto series = repo_.getSeries( name.toStdString() );
        plot_->addLiveSeries( series );

        int count = model->getChildCount( selected );

        for( int i = 0; i < count; ++i )
        {
            TreeItem* treeitem = model->getChild( selected, i );
            SMATreeItem* smaTreeItem = dynamic_cast<SMATreeItem*> ( treeitem );
            if( smaTreeItem )
            {
                int value = smaTreeItem->getSmaValue();

                auto sma2 = repo_.getSMA( name.toStdString(), value );
                plot_->addSimpleMovingAverage( sma2 );
            }
        }
    }
}

void ConfigTree::setPlotController( PlotController* plot )
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
    auto sma2 = repo_.getSMA( name.toStdString(), value );
    plot_->addSimpleMovingAverage( sma2 );

    // insert sma item in tree
    QVector< QVariant > data;
    data << name+" SMA "+QString::number( value );
    model->addSMA( selected, data, value );
    view->update();

}

void ConfigTree::addEMA()
{

}