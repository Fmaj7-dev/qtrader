#include "plotting/plottingwidget.h"
#include "plotting/configtree.h"
#include "plotting/plotcontroller.h"

#include <QSplitter>
#include <QHBoxLayout>

using namespace gui;
using namespace gui::plotting;

PlottingWidget::PlottingWidget( SeriesRepository& repo )
: repo_( repo )
{
    // plotcontroller
    PlotController* plotController = new PlotController();
    
    // configTree
    ConfigTree* configTree = new ConfigTree( repo_ );
    configTree->setPlotController( plotController );

    QSplitter* splitter = new QSplitter( this );
    splitter->addWidget( configTree );
    splitter->addWidget( plotController );

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget( splitter );
    this->setLayout( layout );
}