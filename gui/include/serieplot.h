#ifndef SERIEPLOT_H
#define SERIEPLOT_H

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

class SeriePlot : public QtCharts::QChartView
{
public:
    SeriePlot();
private:
    QtCharts::QBarSet *set0;
    QtCharts::QBarSet *set1;
    QtCharts::QBarSet *set2;
    QtCharts::QBarSet *set3;
    QtCharts::QBarSet *set4;

    QtCharts::QBarSeries *series;
    QtCharts::QChart *chart;
    QtCharts::QBarCategoryAxis *axisX;
    QtCharts::QValueAxis *axisY;
};

#endif