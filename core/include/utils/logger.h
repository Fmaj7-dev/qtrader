#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <QString>

// Simplest logger ever. Console output.
// FIXME: add TRACE, DEBUG, INFO, WARN, ERROR, FATAL
// and output to file

template<typename T>
void log(T v) 
{
  std::cout<< v <<std::endl;
}

template<>
void log(QString v) 
{
  std::cout<< v.toStdString() <<std::endl;
}

template<typename T, typename... Args>
void log(T first, Args... args) 
{
  std::cout<< first <<" ";
  log(args...);
}

template<typename... Args>
void log(QString first, Args... args) 
{
  std::cout<< first.toStdString() <<" ";
  log(args...);
}

#endif
