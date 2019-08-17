#include "plotcontroller.h"
#include "seriesplot.h"
#include "iostream"

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

void PlotController::onResetTransform()
{
    seriesPlot_->chart()->zoomReset();
}