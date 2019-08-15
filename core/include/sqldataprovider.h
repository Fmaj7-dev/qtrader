#ifndef SQLDATAPROVIDER_H
#define SQLDATAPROVIDER_H

#include <QSqlDatabase>

class DatabaseConnectionException: public std::exception
{
    const char* what() const noexcept override 
    {
        return "Error connecting to database";
    }
};

class SqlDataProvider
{
public:
    SqlDataProvider();

private:
    void connectToDb();

    QSqlDatabase db;
};

#endif