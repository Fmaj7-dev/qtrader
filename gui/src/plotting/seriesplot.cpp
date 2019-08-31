#include "plotting/seriesplot.h"
#include "liveseries.h"
#include "analysis/simplemovingaverage.h"

QT_CHARTS_USE_NAMESPACE

using namespace core;
using namespace core::analysis;
using namespace gui;
using namespace gui::plotting;

SeriesPlot::SeriesPlot()
{
}

void SeriesPlot::addLiveSeries(const LiveSeries& liveSeries)
{
    QLineSeries *series = new QLineSeries();

    int i = 0;
    for(auto& item: liveSeries.values)
    {
        series->append(item.time*1000, item.value);
        ++i;
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries( series );
    chart->setTitle( "series name" );
    chart->setAnimationOptions(QChart::SeriesAnimations);

    this->setChart( chart );
    this->setRenderHint(QPainter::Antialiasing);

    // X axis
    axisX = new QDateTimeAxis;
    axisX->setTickCount(16);
    axisX->setFormat("d MMM");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    
    //Y axis
    axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Value");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY); 

    QChartView::RubberBand rubber = QChartView::RectangleRubberBand;
    this->setRubberBand( rubber );
}

void SeriesPlot::addSimpleMovingAverage( const SimpleMovingAverage& sma )
{
    QChart *chart = this->chart();

    QLineSeries *series = new QLineSeries();

    int i = 0;
    for(const auto& item: sma.getValues())
    {
        series->append(item.time*1000, item.value);
        ++i;
    }

    chart->addSeries( series );

    series->attachAxis(axisX);
    series->attachAxis(axisY);
    
    chart->update();
}