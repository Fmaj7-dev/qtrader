#ifndef SERIEPLOT_H
#define SERIEPLOT_H

#include "liveseries.h"

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>

class SeriesPlot : public QtCharts::QChartView
{
public:
    SeriesPlot();

    void addLiveSeries( const LiveSeries& series );

protected:
/* void wheelEvent( QWheelEvent *event ) Q_DECL_OVERRIDE
    {
        qreal factor = event->angleDelta().y() > 0? 0.9: 1.1;
        chart()->zoom(factor);
        event->accept();
        QChartView::wheelEvent(event);
    }*/
private:
};

#endif