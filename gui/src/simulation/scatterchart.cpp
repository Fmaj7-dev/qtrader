#include "simulation/scatterchart.h"

#include "utils/logger.h"

#include <QScatterSeries>
#include <QPoint>
#include <QPainter>
#include <QPainterPath>
#include <QtMath>
#include <QPixmap>

QT_CHARTS_USE_NAMESPACE
using namespace core;
using namespace utils;
using namespace gui;
using namespace gui::simulation;

ScatterChart::ScatterChart( QWidget *parent )
  : QChartView( new QChart(), parent )
{
  /*drawResults(std::vector< std::vector< float > >(),
              1, 1);*/
}

ScatterChart::~ScatterChart()
{
}

void ScatterChart::clear()
{
  chart()->removeAllSeries();
}

void ScatterChart::drawResults( const Results& results )
{
  // calculate min and max Balances
  float minBalance = 100000;
  float maxBalance = -100000;
  int maxI = 0;

  for ( auto& item: results )
  {
    float value = std::get<2>( item );
    int i = std::get<0>( item );

    if ( i > maxI )
      maxI = i;

    if( value > maxBalance )
      maxBalance = value;
    else if ( value < minBalance )
      minBalance = value;
  }

  QSize size = this->maximumSize();
  float maxCircleSize = float(size.rheight()*1.)/maxI -3;
  log("maxSize: ", maxCircleSize );

  // num colors circles for positive + num colors for negative
  int numSeries = 10;
  float circleStep = maxCircleSize/numSeries;

  log("Current max size: ", 1.5*numSeries + 5);

  // fill positive series ( greens )
  std::vector< QScatterSeries* > positiveSeries;
  for ( int i = 0; i < numSeries; ++i )
  {
    QScatterSeries *series0 = new QScatterSeries();
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(/*1.5*i + 5*/ i*circleStep+3);

    int colorStep = 256/numSeries;
    series0->setColor(QColor(255 - i * colorStep, 255-4*i, 0));
    series0->setBorderColor(QColor(255 - i * colorStep, 255-4*i, 0));

    positiveSeries.push_back( series0 );
  }

  // fill negative series ( reds )
  std::vector< QScatterSeries* > negativeSeries;
  for ( int i = 0; i < numSeries; ++i )
  {
    QScatterSeries *series0 = new QScatterSeries();
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(/*1.5*i + 5*/ i*circleStep+3);

    int colorStep = 256/numSeries;
    series0->setColor(QColor(255-4*i, 255 - i * colorStep, 0));
    series0->setBorderColor(QColor(255-4*i, 255 - i * colorStep, 0));

    negativeSeries.push_back( series0 );
  }

  // process each value, and assign it to a series
  for ( auto& item: results )
  {
    float value = std::get<2>( item );

    if(value < 0)
      negativeSeries[(value/minBalance)*(numSeries-1)]->append( std::get<0>(item), std::get<1>(item) );
    else
      positiveSeries[ (value/maxBalance)*(numSeries-1) ]->append( std::get<0>(item), std::get<1>(item) );
  }

  setRenderHint(QPainter::Antialiasing);

  for( auto& serie : negativeSeries )
    chart()->addSeries(serie);

  for( auto& serie : positiveSeries )
    chart()->addSeries(serie);

  chart()->setTitle("Strategies optimizer");
  chart()->createDefaultAxes();
  chart()->setDropShadowEnabled(false);
}

void ScatterChart::savePng(const QString& path)
{
  QPixmap p = this->grab();
  p.save( path, "PNG");
}