/*
 * ��ȫ��������־
 */
#include <syslog.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>


#define LOG_MAX_LEN    1024 /* ϵͳ��־Ĭ����󳤶�.*/
/*��־����*/
#define LL_DEBUG 0
#define LL_VERBOSE 1
#define LL_NOTICE 2
#define LL_WARNING 3
#define LL_RAW (1<<10) /* Modifier to log without timestamp */
#define CONFIG_DEFAULT_VERBOSITY LL_NOTICE


void serverLog(int level, const char *fmt, ...);

void serverLogRaw(int level, const char *msg);



