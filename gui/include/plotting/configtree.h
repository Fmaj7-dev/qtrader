#ifndef CONFIGTREE_H
#define CONFIGTREE_H

#include "seriesrepository.h"

#include <QWidget>
#include <QTreeView>
//#include <QLabel>
#include <QVBoxLayout>
#include <QPoint>

class PlotController;
class TreeModel;

namespace gui
{
namespace plotting
{

class PlotController;
class TreeModel;

class ConfigTree : public QWidget
{
    Q_OBJECT
public:
    ConfigTree( SeriesRepository& repo );
    virtual ~ConfigTree();

    void setPlotController( PlotController* plot );

private slots:
    void ShowContextMenu( const QPoint &pos );
    void addSMA();
    void addEMA();
    void plotSelected( const QItemSelection&, const QItemSelection& );

private:
    // model of series
    TreeModel* model;
    // tree view
    QTreeView* view;

    //QLabel* label;
    QVBoxLayout* layout;

    // not owning pointer to SeriePlot
    PlotController* plot_;

    // repository of series
    SeriesRepository& repo_;
};
}
}

#endif