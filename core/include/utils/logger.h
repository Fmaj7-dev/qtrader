#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <QString>

// Simplest logger ever. Console output.
// FIXME: add TRACE, DEBUG, INFO, WARN, ERROR, FATAL
// and output to file

namespace core
{
namespace utils
{
template<typename T>
inline void log(T v) 
{
  std::cout<< v <<std::endl;
}

template<>
inline void log(QString v) 
{
  std::cout<< v.toStdString() <<std::endl;
}

template<typename T, typename... Args>
inline void log(T first, Args... args) 
{
  std::cout<< first <<" ";
  log(args...);
}

template<typename... Args>
inline void log(QString first, Args... args) 
{
  std::cout<< first.toStdString() <<" ";
  log(args...);
}
}
}


#endif
