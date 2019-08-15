#include "sqldataprovider.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QMap>

#include <iostream>

SqlDataProvider::SqlDataProvider()
    :db (QSqlDatabase::addDatabase("QMYSQL3"))
{
    // parse .env file for credentials
    QMap<QString, QString> dbInfo;
    QFile file(".env");
    if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
        return;

    while ( !file.atEnd() ) 
    {
        QString line = file.readLine();
        QStringList list = line.split( "=" );
        dbInfo.insert( list[0], list[1] );
        std::cout<<list[0].toStdString()<<" "<<list[1].toStdString()<<std::endl;
    }
    
    // check values
    if ( dbInfo.find("SQL_HOST") == dbInfo.end() )
        std::cout<<"SQL_HOST not found in .env file"<<std::endl;

    if ( dbInfo.find("SQL_USER") == dbInfo.end() )
        std::cout<<"SQL_USER not found in .env file"<<std::endl;

    if ( dbInfo.find("SQL_PASS") == dbInfo.end() )
        std::cout<<"SQL_PASS not found in .env file"<<std::endl;

    db.setHostName( dbInfo["SQL_HOST"] );
    db.setDatabaseName("trading");
    db.setUserName( dbInfo["SQL_USER"] );
    db.setPassword( dbInfo["SQL_PASS"] );

    bool ok = db.open();
    if(!ok)
    {
        QSqlError error = db.lastError();
        std::cout<<error.databaseText().toStdString()<<std::endl;
        std::cout<<error.driverText().toStdString()<<std::endl;
        std::cout<<error.nativeErrorCode().toStdString()<<std::endl;

        //throw DatabaseConnectionException();
    }

    QSqlQuery query;
    query.exec("SELECT * FROM live_bch limit 10");

    while (query.next()) 
    {
        std::time_t t = query.value(1).toInt();
        QString htime = query.value(2).toString();
        float value = query.value(3).toFloat();
        std::cout<<t<<" "<<htime.toStdString()<<" "<<value<<std::endl;
        //std::cout.flush();
    }
    
    qDebug() << QSqlDatabase::drivers();        
}

void SqlDataProvider::connectToDb()
{
    // parse .env file for credentials
    QMap<QString, QString> dbInfo;
    QFile file(".env");
    if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
        return;

    while ( !file.atEnd() ) 
    {
        QString line = file.readLine();
        QStringList list = line.split( "=" );
        dbInfo.insert( list[0], list[1] );
    }
    
    // check values
    if ( dbInfo.find("SQL_HOST") == dbInfo.end() )
        std::cout<<"SQL_HOST not found in .env file"<<std::endl;

    if ( dbInfo.find("SQL_USER") == dbInfo.end() )
        std::cout<<"SQL_USER not found in .env file"<<std::endl;

    if ( dbInfo.find("SQL_PASS") == dbInfo.end() )
        std::cout<<"SQL_PASS not found in .env file"<<std::endl;

    db.setHostName( dbInfo["SQL_HOST"] );
    db.setDatabaseName("trading");
    db.setUserName( dbInfo["SQL_USER"] );
    db.setPassword( dbInfo["SQL_PASS"] );

    bool ok = db.open();

    if(!ok)
        //std::cout<<"error connecting to database"<<std::endl;
        throw DatabaseConnectionException();
}