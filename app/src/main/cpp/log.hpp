#pragma once

#define LOG_TAG "GeodeLauncher-Fix"

#include <android/log.h>
#include <cstdio>
#include <string>

namespace log {
    template<typename... Args>
    void log_internal(android_LogPriority prio, const char* fmt, Args&&... args) {
        char buffer[1024];
        // If args are provided, we MUST use snprintf with fmt to process them.
        // The issue is the compiler wants the fmt to be a literal for security.
        // Since our fmt comes from calling log::warn("literal"), it IS a literal.
        // We can use a pragma to suppress this warning only for this line.
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wformat-security"
        snprintf(buffer, sizeof(buffer), fmt, std::forward<Args>(args)...);
        #pragma GCC diagnostic pop
        __android_log_write(prio, LOG_TAG, buffer);
    }

    template<typename... Args>
    inline void debug(const char* fmt, Args&&... args) {
        log_internal(ANDROID_LOG_DEBUG, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void info(const char* fmt, Args&&... args) {
        log_internal(ANDROID_LOG_INFO, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void warn(const char* fmt, Args&&... args) {
        log_internal(ANDROID_LOG_WARN, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void error(const char* fmt, Args&&... args) {
        log_internal(ANDROID_LOG_ERROR, fmt, std::forward<Args>(args)...);
    }
}
