#include "sqldataprovider.h"
#include "utils/logger.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QMap>

SqlDataProvider::SqlDataProvider()
    :db (QSqlDatabase::addDatabase("QMYSQL3"))
{
    connectToDb();
    //qDebug() << QSqlDatabase::drivers();        
}

SqlDataProvider::~SqlDataProvider()
{
    db.close();
}

void SqlDataProvider::connectToDb()
{
    using namespace core::utils;
    
    // parse .env file for credentials
    QMap<QString, QString> dbInfo;
    QFile file(".env");
    if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
        return;

    while ( !file.atEnd() ) 
    {
        QString line = file.readLine();
        QStringList list = line.split( "=" );
        dbInfo.insert( list[0].trimmed(), list[1].trimmed() );
    }
    
    // check values
    if ( dbInfo.find("SQL_HOST") == dbInfo.end() )
        log( "SQL_HOST not found in .env file" );

    if ( dbInfo.find("SQL_USER") == dbInfo.end() )
        log( "SQL_USER not found in .env file" );

    if ( dbInfo.find("SQL_PASS") == dbInfo.end() )
        log( "SQL_PASS not found in .env file" );

    db.setHostName( dbInfo["SQL_HOST"] );
    db.setDatabaseName("trading");
    db.setUserName( dbInfo["SQL_USER"] );
    db.setPassword( dbInfo["SQL_PASS"] );

    bool ok = db.open();
    if(!ok)
    {
        QSqlError error = db.lastError();
        log(error.databaseText().toStdString());
        log(error.driverText().toStdString());
        log(error.nativeErrorCode().toStdString());

        throw DatabaseConnectionException();
    }
}

Tables SqlDataProvider::getAvailableTables()
{
    QSqlQuery query;
    query.exec("show tables");
    Tables tables;

    while ( query.next() ) 
    {
        tables.push_back(query.value(0).toString().toStdString());
    }
    return tables;
}

void SqlDataProvider::fillLiveSeries( LiveSeries& series, std::string name )
{
    QSqlQuery query;
    QString queryStr = QString("SELECT * FROM ") + name.c_str();
    query.exec(queryStr);

    while ( query.next() ) 
    {
        unsigned int id = query.value(0).toInt();
        std::time_t t = query.value(1).toInt();
        QString htime = query.value(2).toString();
        float value = query.value(3).toFloat();

        series.values.push_back( {id, t, htime.toStdString(), value} );
    }
}