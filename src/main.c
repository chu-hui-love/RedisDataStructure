
#include "dict.h"
#include"serverlog.h"
#include<string.h>
#include"sds.h"
#include"adlist.h"

uint64_t hashCallback(const void *key) {
    return dictGenHashFunction((unsigned char*)key, sdslen((char*)key));
}

int compareCallback(void *privdata, const void *key1, const void *key2) {
    int l1,l2;
    DICT_NOTUSED(privdata);

    l1 = sdslen((sds)key1);
    l2 = sdslen((sds)key2);
    if (l1 != l2) return 0;
    return memcmp(key1, key2, l1) == 0;
}

void freeCallback(void *privdata, void *val) {
    DICT_NOTUSED(privdata);
}

dictType BenchmarkDictType = {
    hashCallback,
    NULL,
    NULL,
    compareCallback,
    freeCallback,
    NULL
};


#define start_benchmark() start = timeInMilliseconds()

#define end_benchmark(msg) do { \
    elapsed = timeInMilliseconds()-start; \
    printf(msg ": %ld items in %lld ms\n", count, elapsed); \
} while(0);





int main(int argv,char ** argc){
	int i=0;
	list *adlist = listCreate();

	int count=10;
	for( i=0;i<count;i++){
		listAddNodeHead(adlist,sdsfromlonglong(i));
	}
	count=20;
	for( i=11;i<count;i++){
		listAddNodeTail(adlist,sdsfromlonglong(i));
	}

	list *newlist = listDup(adlist);

     sds target=sdsfromlonglong(19);


	listNode * saearchKeyt=listSearchKey(newlist, target);
	




	return 0;

}


