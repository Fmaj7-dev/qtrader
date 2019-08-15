#ifndef SQLDATAPROVIDER_H
#define SQLDATAPROVIDER_H

#include "liveseries.h"

#include <QSqlDatabase>

class DatabaseConnectionException: public std::exception
{
    const char* what() const noexcept override 
    {
        return "Error connecting to database";
    }
};

using Tables = std::vector< std::string >;


class SqlDataProvider
{
public:
    SqlDataProvider();
    ~SqlDataProvider();
    
    Tables getAvailableTables();
    void fillLiveSeries( LiveSeries& series, std::string name );

private:
    void connectToDb();

    QSqlDatabase db;
};

#endif