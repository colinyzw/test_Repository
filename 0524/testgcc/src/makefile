#version2.0 use var

TARGET=app #用于存储目标名
CC=gcc #用于存储编译器版本
INCLUDE_PATH=../include #用于存储头文件路径
INSTALL_PATH=/usr/bin#安装位置
LIBRARY_PATH=../library #存放共享库或静态库位置
CFLAGS=-I$(INCLUDE_PATH) -c -g -Wall #编译选项
CPPFLAGS=-D -L -l -01 -02 -03 #预处理选项，编译优化及库使用
RM=sudo rm -rf
COPY=sudo cp


SOURCE = $(wildcard *.c)
DFILE = $(patsubst %.c,%.o,$(SOURCE))


$(TARGET):$(DFILE)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) $<


clean:
	$(RM) $(DFILE) $(TARGET)

output:
	@echo $(INCLUDE_PATH)$(TARGET)

install:
	$(COPY) $(TARGET) $(INSTALL_PATH)

disclean:
	$(RM) $(INSTALL_PATH)$(TARGET)
