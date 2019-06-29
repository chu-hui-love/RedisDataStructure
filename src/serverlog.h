/*
 * 完全独立的日志
 */
#include <syslog.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>


#define LOG_MAX_LEN    1024 /* 系统日志默认最大长度.*/
/*日志级别*/
#define LL_DEBUG 0
#define LL_VERBOSE 1
#define LL_NOTICE 2
#define LL_WARNING 3
#define LL_RAW (1<<10) /* Modifier to log without timestamp */
#define CONFIG_DEFAULT_VERBOSITY LL_NOTICE


void serverLog(int level, const char *fmt, ...);

void serverLogRaw(int level, const char *msg);



