#ifndef PLOTTINGWIDGET_H 
#define PLOTTINGWIDGET_H

#include "seriesrepository.h"

#include <QWidget>

namespace gui
{
namespace plotting
{

class PlottingWidget : public QWidget
{
  Q_OBJECT

public:
  PlottingWidget( SeriesRepository& repo );

private:
  SeriesRepository& repo_;
};

}
}

#endif
