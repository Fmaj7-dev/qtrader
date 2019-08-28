#ifndef SERIESREPOSITORY_H
#define SERIESREPOSITORY_H

#include "liveseries.h"
#include "analysis/simplemovingaverage.h"
#include "sqldataprovider.h"

#include <string>
#include <map>

using LiveSeriesMap = std::map< std::string, LiveSeries >;
using SMAMap = std::map< std::string, core::analysis::SimpleMovingAverage >;

using SeriesList = std::vector< std::string >;

class SeriesRepository
{
public:
    SeriesRepository();
    
    void fillAllSeries();
    SeriesList getAvailableSeries();

    const LiveSeries& getSeries( std::string name );
    const core::analysis::SimpleMovingAverage& getSMA( std::string seriesName, int n );

private:
    SqlDataProvider sqlProvider_;

    LiveSeriesMap liveSeriesMap_;
    SMAMap SMAMap_;
};

#endif 