#include "simulation/scatterchart.h"

#include "utils/logger.h"

#include <QScatterSeries>
#include <QPoint>
#include <QPainter>
#include <QPainterPath>
#include <QtMath>

QT_CHARTS_USE_NAMESPACE

ScatterChart::ScatterChart( QWidget *parent )
  : QChartView( new QChart(), parent )
{
  drawResults(std::vector< std::vector< float > >(),
              1, 1);
}

ScatterChart::~ScatterChart()
{
}

void ScatterChart::drawResults( const std::vector< std::vector< float > >& results_, 
                                int minValue, 
                                int step )
{
  // fill fake results
  std::vector< std::vector< float > > results;

  for(int i = 0; i < 50; ++i)
  {
    std::vector< float > row;
    for(int j = 0; j < 50; ++j)
    {
      float balance = (rand()%1000) - 500;
      row.push_back(balance);
    } 
    results.push_back(row);
  }
  // end fill fake results

  // FIXME: calculate this
  float minBalance = -500;
  float maxBalance = 500;

  // num colors for positive + num colors for negative
  int numSeries = 10;

  // fill positive series ( greens )
  std::vector< QScatterSeries* > positiveSeries;
  for ( int i = 0; i < numSeries; ++i )
  {
    QScatterSeries *series0 = new QScatterSeries();
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(1.5*i + 5);

    int colorStep = 256/numSeries;
    series0->setColor(QColor(255 - i * colorStep, 255-4*i, 0));

    positiveSeries.push_back( series0 );
  }

  // fill negative series ( reds )
  std::vector< QScatterSeries* > negativeSeries;
  for ( int i = 0; i < numSeries; ++i )
  {
    QScatterSeries *series0 = new QScatterSeries();
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(1.5*i + 5);

    int colorStep = 256/numSeries;
    series0->setColor(QColor(255-4*i, 255 - i * colorStep, 0));

    negativeSeries.push_back( series0 );
  }

  // process each value, and assign it to a series
  int i = 0;
  for ( auto& row : results )
  {
    int j = 0;
    for ( auto& value: row )
    {
      if(value < 0)
        negativeSeries[(value/minBalance)*(numSeries-1)]->append(i, j);
      else
        positiveSeries[ (value/maxBalance)*(numSeries-1) ]->append(i, j);
      ++j;
    }
    ++i;
  }

  setRenderHint(QPainter::Antialiasing);

  for( auto& serie : negativeSeries )
    chart()->addSeries(serie);

  for( auto& serie : positiveSeries )
    chart()->addSeries(serie);

  chart()->setTitle("Simple scatterchart example");
  chart()->createDefaultAxes();
  chart()->setDropShadowEnabled(false);
}
