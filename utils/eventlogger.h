#ifndef EVENT_LOGGER_H
#define EVENT_LOGGER_H

#include <iostream>

namespace DSA::Utils {

using SubSystemId = uint32_t;

enum class LogLevel {
    DEBUG,
    INFO,
    ERROR
};

enum class SubSystemId {

};

class EventLogger {
private:
    LogLevel m_LogLevel {};
    EventLogger* m_EventLoggerPtr {nullptr} ;

    EventLogger() { std::cout << std::format("EventLogger initialized at memory address %p", this) << std::endl; };
    virtual ~EventLogger() { delete m_EventLoggerPtr; };

public:
    void setLogLevel();
    static EventLogger* getInstance() {
        if (m_EventLoggerPtr == nullptr)
    }



};

}

#endif /* EVENT_LOGGER_H */
