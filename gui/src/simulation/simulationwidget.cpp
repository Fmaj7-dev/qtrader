#include "simulationwidget.h"

#include <QPushButton>

SimulationWidget::SimulationWidget(SeriesRepository& repo, QWidget *parent)
:QWidget(parent),
repo_( repo ),
simulator_( repo )
{
    layout_ = new QHBoxLayout(this);
    scatterChart_ = new ScatterChart(this);
    scatterChart_->resize(600, 600);
    layout_->addWidget( scatterChart_ );
}

SimulationWidget::~SimulationWidget()
{
}
