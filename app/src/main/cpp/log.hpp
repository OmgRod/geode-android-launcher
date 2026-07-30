#pragma once

#define LOG_TAG "GeodeLauncher-Fix"

#include <android/log.h>
#include <fmt/core.h>

namespace log {
    template<typename... Args>
    void log_internal(android_LogPriority prio, fmt::string_view fmt, Args&&... args) {
        std::string str = fmt::format(fmt, std::forward<Args>(args)...);
        __android_log_write(prio, LOG_TAG, str.c_str());
    }

    template<typename... Args>
    inline void debug(fmt::format_string<Args...> fmt, Args&&... args) {
        log_internal(ANDROID_LOG_DEBUG, fmt.get(), std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void info(fmt::format_string<Args...> fmt, Args&&... args) {
        log_internal(ANDROID_LOG_INFO, fmt.get(), std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void warn(fmt::format_string<Args...> fmt, Args&&... args) {
        log_internal(ANDROID_LOG_WARN, fmt.get(), std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void error(fmt::format_string<Args...> fmt, Args&&... args) {
        log_internal(ANDROID_LOG_ERROR, fmt.get(), std::forward<Args>(args)...);
    }
}
