#include "seriesplot.h"

#include <QDateTimeAxis>

QT_CHARTS_USE_NAMESPACE

SeriesPlot::SeriesPlot()
{
  
}

void SeriesPlot::addLiveSeries(const LiveSeries& liveSeries)
{
    QLineSeries *series = new QLineSeries();

    for(auto& item: liveSeries.values)
    {
        series->append(item.time*1000, item.value);
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