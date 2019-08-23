#ifndef SIMULATIONWIDGET_H
#define SIMULATIONWIDGET_H

#include "scatterchart.h"

#include <QWidget>
#include <QVBoxLayout>

class SimulationWidget : public QWidget
{
    Q_OBJECT
public:
    SimulationWidget( QWidget *parent = 0 );
    virtual ~SimulationWidget();

private slots:

private:
    QHBoxLayout* layout_;
    ScatterChart* scatterChart_;
};

#endif
