#include "simulationwidget.h"

#include <QPushButton>

SimulationWidget::SimulationWidget(QWidget *parent)
:QWidget(parent)
{
    layout_ = new QHBoxLayout(this);
    scatterChart_ = new ScatterChart(this);
    scatterChart_->resize(600, 600);
    layout_->addWidget( scatterChart_ );
}

SimulationWidget::~SimulationWidget()
{
}
