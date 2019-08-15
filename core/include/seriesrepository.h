#ifndef SERIESREPOSITORY_H
#define SERIESREPOSITORY_H

#include "liveseries.h"
#include "sqldataprovider.h"

#include <string>
#include <map>

using LiveSeriesMap = std::map< std::string, LiveSeries >;
using SeriesList = std::vector< std::string >;

class SeriesRepository
{
public:
    SeriesRepository();
    
    void fillAllSeries();
    SeriesList getAvailableSeries();
    const LiveSeries& getSeries( std::string name );

private:
    SqlDataProvider sqlProvider_;
    LiveSeriesMap liveSeriesMap_;
};

#endif 