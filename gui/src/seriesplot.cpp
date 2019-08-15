#include "seriesplot.h"

#include <QDateTimeAxis>

QT_CHARTS_USE_NAMESPACE

SeriesPlot::SeriesPlot()
{
    /* set0 = new QBarSet("Jane");
    set1 = new QBarSet("John");
    set2 = new QBarSet("Axel");
    set3 = new QBarSet("Mary");
    set4 = new QBarSet("Samantha");

    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
    *set4 << 9 << 7 << 5 << 3 << 1 << 2;

    series = new QBarSeries();

    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple barchart example");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY = new QValueAxis();
    axisY->setRange(0,15);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    this->setChart(chart);
    this->setRenderHint(QPainter::Antialiasing);*/
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