
# 唯一的缺点就是需要将每一个.o文件写上
obj=main.o dict.o zmalloc.o serverlog.o localtime.o siphash.o sds.o adlist.o

CFLAGS=-g -Wall 

target=app

CC=gcc

$(target):$(obj)
	$(CC)  $(CFLAGS) $(obj) -o  $(target)

%.o:%.c
	$(CC) -c $(CFLAGS)  $< -o $@

