#ifndef CONFIGTREE_H
#define CONFIGTREE_H

#include "seriesrepository.h"

#include <QWidget>
#include <QTreeView>
#include <QLabel>
#include <QVBoxLayout>

class SeriesPlot;

class ConfigTree : public QWidget
{
    Q_OBJECT
public:
    ConfigTree();
    virtual ~ConfigTree();

    void setPlot( SeriesPlot* plot );

private:
    QTreeView* view;
    QLabel* label;
    QVBoxLayout* layout;

    // not owning pointer to SeriePlot
    SeriesPlot* plot_;

    // repository of series
    SeriesRepository repo_;
    
};

#endif