/**
 * @file Logger.h
 *
 * @brief This class provides basic logging functionality
 *
 * @author Lorenzo Arena
 *
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <utility>

class Logger
{
  public:
    template <typename Arg, typename... Args>
    static void Debug(Arg&& arg, Args&&... args)
    {
        std::cout << "[DEBUG] ";
        Logger::log(arg, args...);
    }

    template <typename Arg, typename... Args>
    static void Error(Arg&& arg, Args&&... args)
    {
        std::cout << "[ERROR] ";
        Logger::log(arg, args...);
    }

  private:
    template <typename Arg, typename... Args>
    static void log(Arg&& arg, Args&&... args)
    {
        std::cout << std::forward<Arg>(arg);
        using expander = int[];
        (void)expander{0, (void(std::cout << std::forward<Args>(args)), 0)...};
        std::cout << std::endl;
    }
};

#endif
