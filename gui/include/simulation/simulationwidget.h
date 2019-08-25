#ifndef SIMULATIONWIDGET_H
#define SIMULATIONWIDGET_H

#include "seriesrepository.h"
#include "scatterchart.h"
#include "simulation/simulator.h"

#include <QWidget>
#include <QVBoxLayout>

class SimulationWidget : public QWidget
{
    Q_OBJECT
public:
    SimulationWidget( SeriesRepository& repo, QWidget *parent = 0 );
    virtual ~SimulationWidget();

private slots:
    void testSimulation();

private:
    QHBoxLayout* layout_;
    ScatterChart* scatterChart_;
    SeriesRepository& repo_;
    core::simulation::Simulator simulator_;
};

#endif
