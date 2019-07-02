
#include "dict.h"
#include"serverlog.h"
#include<string.h>
#include"sds.h"

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


	   long j;
	   long long start,
	   	long long elapsed;
	   dict *dict = dictCreate(&BenchmarkDictType,NULL);
	   long count = 5000000;
	
	
	   start_benchmark();
	   for (j = 0; j < count; j++) {
		   int retval = dictAdd(dict,sdsfromlonglong(j),(void*)j);
	
	   }
	   end_benchmark("Inserting");
	
	   /* Wait for rehashing. */
	   while (dictIsRehashing(dict)) {
		   dictRehashMilliseconds(dict,100);
	   }
	
	   start_benchmark();
	   for (j = 0; j < count; j++) {
		   sds key = sdsfromlonglong(j);
		   dictEntry *de = dictFind(dict,key);
	
		   sdsfree(key);
	   }
	   end_benchmark("Linear access of existing elements");
	
	   start_benchmark();
	   for (j = 0; j < count; j++) {
		   sds key = sdsfromlonglong(j);
		   dictEntry *de = dictFind(dict,key);
		
		   sdsfree(key);
	   }
	   end_benchmark("Linear access of existing elements (2nd round)");
	
	   start_benchmark();
	   for (j = 0; j < count; j++) {
		   sds key = sdsfromlonglong(rand() % count);
		   dictEntry *de = dictFind(dict,key);
	
		   sdsfree(key);
	   }
	   end_benchmark("Random access of existing elements");
	
	   start_benchmark();
	   for (j = 0; j < count; j++) {
		   sds key = sdsfromlonglong(rand() % count);
		   key[0] = 'X';
		   dictEntry *de = dictFind(dict,key);
		
		   sdsfree(key);
	   }
	   end_benchmark("Accessing missing");
	
	   start_benchmark();
	   for (j = 0; j < count; j++) {
		   sds key = sdsfromlonglong(j);
		   int retval = dictDelete(dict,key);
   		key[0] += 17; /* Change first number to letter. */
		   retval = dictAdd(dict,key,(void*)j);
		
	   }
	   end_benchmark("Removing and adding");



	return 0;

}


