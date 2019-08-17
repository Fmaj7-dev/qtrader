#ifndef CONFIGTREE_H
#define CONFIGTREE_H

#include "seriesrepository.h"

#include <QWidget>
#include <QTreeView>
#include <QLabel>
#include <QVBoxLayout>

class PlotController;

class ConfigTree : public QWidget
{
    Q_OBJECT
public:
    ConfigTree();
    virtual ~ConfigTree();

    void setPlotController( PlotController* plot );

private:
    QTreeView* view;
    QLabel* label;
    QVBoxLayout* layout;

    // not owning pointer to SeriePlot
    PlotController* plot_;

    // repository of series
    SeriesRepository repo_;
    
};

#endif