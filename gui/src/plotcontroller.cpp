#include "plotcontroller.h"
#include "seriesplot.h"
#include "liveseries.h"
#include "analysis/simplemovingaverage.h"
#include "utils/logger.h"

QT_CHARTS_USE_NAMESPACE

PlotController::PlotController()
:layout_(nullptr)
{
   
}

void clearLayout(QLayout* layout, bool deleteWidgets = true)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}

void PlotController::addLiveSeries( const LiveSeries& liveSeries )
{
    seriesPlot_ = new SeriesPlot();
    seriesPlot_->addLiveSeries( liveSeries );

    resetTransform_ = new QPushButton();
    resetTransform_->setText("Reset");
    QObject::connect(resetTransform_, SIGNAL( clicked() ),
                     this, SLOT( onResetTransform() ));

    if ( layout_ )
    {
        clearLayout( layout_ );
        delete layout_;
        layout_ = nullptr;
    }

    layout_ = new QVBoxLayout( this );
    layout_->addWidget( seriesPlot_ );
    layout_->addWidget( resetTransform_ );
}

void PlotController::addSimpleMovingAverage( const SimpleMovingAverage& series )
{
    seriesPlot_->addSimpleMovingAverage( series );
}

void PlotController::onResetTransform()
{
    seriesPlot_->chart()->zoomReset();
}