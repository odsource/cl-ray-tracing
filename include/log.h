#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define RESET           "\033[0m"
#define BOLD_MAGENTA    "\033[1m\033[35m"
#define BOLD_WHITE      "\033[1m\033[37m"
#define BOLD_YELLOW     "\033[1m\033[33m"
#define BOLD_RED        "\033[1m\033[31m"
#define BOLD_GREEN       "\033[1m\033[32m"

#ifndef NDEBUG
        #define LOG_DEBUG(msg) printf("%s[DEBUG]%s: %s.\n", BOLD_MAGENTA, RESET, msg)
#else
        #define LOG_D(msg) ((void)0)
#endif

#define LOG_INFO(msg)                   printf("%s[INFO:%s:%d]%s: %s.\n", BOLD_WHITE, __FILE__, __LINE__, RESET, msg)
#define LOG_ERROR(msg)                  printf("%s[INFO:%s:%d]%s: %s.\n", BOLD_RED, __FILE__, __LINE__, RESET, msg)
#define LOG_ACTION_SUCCESS(mod, act)    printf("%s[%s %s]: %s%s%s\n", BOLD_WHITE, mod, act, BOLD_GREEN, "ok.", RESET)
#define LOG_ACTION_ERROR(mod, act)      fprintf(stderr, "%s[%s %s]: %s%s%s\n", BOLD_WHITE, mod, act, BOLD_GREEN, "failed.", RESET)

#endif /* LOG_H */
