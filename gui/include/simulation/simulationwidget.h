#ifndef SIMULATIONWIDGET_H
#define SIMULATIONWIDGET_H

#include "seriesrepository.h"
#include "simulation/scatterchart.h"
#include "simulation/simulator.h"

#include <QWidget>
#include <QVBoxLayout>

namespace gui
{
namespace simulation
{

class SimulationWidget : public QWidget
{
    Q_OBJECT
public:
    SimulationWidget( SeriesRepository& repo, QWidget *parent = 0 );
    virtual ~SimulationWidget();
    void resizeEvent(QResizeEvent *event);

private slots:
    void testSimulation();
    

private:
    QHBoxLayout* layout_;
    ScatterChart* scatterChart_;
    SeriesRepository& repo_;
    core::simulation::Simulator simulator_;
};

}
}
#endif
