#include "simulationwidget.h"
#include "utils/logger.h"
#include "simulation/criteria.h"
#include "simulation/simulation.h"
#include "simulation/simulator.h"

#include <QPushButton>

using namespace gui;
using namespace gui::simulation;

SimulationWidget::SimulationWidget(SeriesRepository& repo, QWidget *parent)
:QWidget(parent),
repo_( repo ),
simulator_( repo )
{
    layout_ = new QHBoxLayout(this);

    // add button
    QPushButton* button = new QPushButton();
    button->setText("test");
    layout_->addWidget( button );
    connect(button, SIGNAL (clicked()),this, SLOT (testSimulation()));

    scatterChart_ = new ScatterChart(this);
    layout_->addWidget( scatterChart_ );
}

SimulationWidget::~SimulationWidget()
{
}

void SimulationWidget::testSimulation()
{
    using namespace core;
    using namespace core::utils;
    using namespace core::simulation;

    float max = 0;
    float min = 10000;
    int maxI, maxJ, minI, minJ;
    for( int i = 2; i < 400; ++i )
    {
        for( int j = 2; j < i/2; ++j )
        {
            Criteria::Subject btcSMA20( Criteria::Subject::Indicator::SMA,
                                        RepositoryDefinitions::Stock::LIVE_BTC,
                                        j );

            Criteria::Subject btcSMA100( Criteria::Subject::Indicator::SMA,
                                        RepositoryDefinitions::Stock::LIVE_BTC,
                                        i );
                                    

            Criteria::Condition buyCondition( btcSMA20, btcSMA100, Criteria::Verb::GET_AHEAD );
            Criteria::Condition sellCondition( btcSMA20, btcSMA100, Criteria::Verb::FALL_BEHIND );

            Criteria criteria;
            criteria.addBuyCondition( buyCondition );
            criteria.addSellCondition( sellCondition );

            Simulation sim( criteria, 10000, 0, 500 );

            Simulator simulator( repo_ );
            simulator.runSimulation( sim );
            simulator.sellStock( sim );

            float result = sim.getCapital();
            log(j, " ", i, " ", result );

            if( result > max )
            {
                maxI = i;
                maxJ = j;
                max = result;
            }
            if( result < min )
            {
                minI = i;
                minJ = j;
                min = result;
            }
        }
    }

    log("max: ", max, " ", maxI, " ", maxJ);
    log("min: ", min, " ", minI, " ", minJ);
}