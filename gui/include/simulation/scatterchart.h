#ifndef SCATTERCHART_H
#define SCATTERCHART_H

#include <QWidget>
#include <QtCharts/QChartView>

#include <vector>

namespace gui
{
namespace simulation
{

class ScatterChart : public QtCharts::QChartView
{
    Q_OBJECT
public:
    ScatterChart( QWidget *parent = 0 );
    virtual ~ScatterChart();

    void drawResults( const std::vector< std::vector< float > >& results, 
                      int minValue, 
                      int step);

private slots:

private:

};

}
}

#endif
