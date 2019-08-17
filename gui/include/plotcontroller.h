#ifndef PLOTCONTROLLER_H
#define PLOTCONTROLLER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class SeriesPlot;
class LiveSeries;
class SimpleMovingAverage;

class PlotController : public QWidget
{
    Q_OBJECT
public:
    PlotController();

    void addLiveSeries( const LiveSeries& series );
    void addSimpleMovingAverage( const SimpleMovingAverage& series );

public slots:
    void onResetTransform();

private:
    SeriesPlot* seriesPlot_;
    QPushButton* resetTransform_;

    QVBoxLayout* layout_;
};

#endif