#include "plotcontroller.h"
#include "seriesplot.h"
#include "liveseries.h"
#include "analysis/simplemovingaverage.h"
#include "utils/logger.h"

QT_CHARTS_USE_NAMESPACE

PlotController::PlotController()
{
   
}

void PlotController::addLiveSeries( const LiveSeries& liveSeries )
{
    seriesPlot_ = new SeriesPlot();
    seriesPlot_->addLiveSeries( liveSeries );

    resetTransform_ = new QPushButton();
    resetTransform_->setText("Reset");
    QObject::connect(resetTransform_, SIGNAL( clicked() ),
                     this, SLOT( onResetTransform() ));

    layout_ = new QVBoxLayout( this );
    layout_->addWidget( seriesPlot_ );
    layout_->addWidget( resetTransform_ );
}

void PlotController::addSimpleMovingAverage( const SimpleMovingAverage& series )
{
    log("PlotController::addSimpleMovingAverage");
    seriesPlot_->addSimpleMovingAverage( series );
}

void PlotController::onResetTransform()
{
    seriesPlot_->chart()->zoomReset();
}