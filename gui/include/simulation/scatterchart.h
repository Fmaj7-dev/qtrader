#ifndef SCATTERCHART_H
#define SCATTERCHART_H

#include <QWidget>
#include <QtCharts/QChartView>

#include <vector>
#include <tuple>

namespace gui
{
namespace simulation
{

using Results = std::vector< std::tuple< int, int, float > >;

class ScatterChart : public QtCharts::QChartView
{
    Q_OBJECT
public:
    ScatterChart( QWidget *parent = 0 );
    virtual ~ScatterChart();

    void drawResults( const Results& results );

private slots:

private:

};

}
}

#endif
