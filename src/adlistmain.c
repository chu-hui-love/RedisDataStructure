
#include "serverlog.h"

int main(int argv,char ** argc){

	openlog("redisDataStru",LOG_PID | LOG_NDELAY | LOG_NOWAIT|LOG_CONS,LOG_LOCAL0);


	return 0;

}


