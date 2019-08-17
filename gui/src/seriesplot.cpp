#include "seriesplot.h"
#include "liveseries.h"
#include "analysis/simplemovingaverage.h"

#include <QDateTimeAxis>

#include <iostream>

QT_CHARTS_USE_NAMESPACE

SeriesPlot::SeriesPlot()
{
  
}

void SeriesPlot::addLiveSeries(const LiveSeries& liveSeries)
{
    QLineSeries *series = new QLineSeries();

    int i = 0;
    for(auto& item: liveSeries.values)
    {
        if (i < 10)
            std::cout<<"Live value"<<item.time<<" "<<item.value<<std::endl;
        series->append(item.time*1000, item.value);
        ++i;
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries( series );
    //chart->createDefaultAxes();
    chart->setTitle( "series name" );
    chart->setAnimationOptions(QChart::SeriesAnimations);

    this->setChart( chart );
    this->setRenderHint(QPainter::Antialiasing);

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(8);
    axisX->setFormat("d MMM");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
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
        if (i < 10)
            std::cout<<"SMA value"<<item.time<<" "<<item.value<<std::endl;

        series->append(item.time*1000, item.value);
        ++i;
    }
    chart->addSeries( series );
    chart->update();
}