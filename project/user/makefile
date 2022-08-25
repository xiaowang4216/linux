#目标文件名
target = my_pro

#编译工具链
cc := arm-linux-gcc

#链接库的文件路径、头文件路径与要链接的库
PI_LIB_PATH := -I ../public/head -I ../APP/inc -L ../LIB
LIB_NAME:=-lapi_v4l2_arm -lpthread -ljpeg

#.o文件存放路径
O_PATH = ../OBJ

#源文件路径
SUBDIR := ../public/source
SUBDIR2 := ../APP/src

#获取源文件路径下的所有.o文件名
GCC_SOURCE_PATH = $(foreach dir,$(SUBDIR),$(wildcard $(dir)/*.c))
GCC_OBJ_PATH = $(patsubst %.c,$(O_PATH)/%.o, $(notdir $(GCC_SOURCE_PATH)))

GCC_SOURCE_PATH2 = $(foreach dir,$(SUBDIR2),$(wildcard $(dir)/*.c))
GCC_OBJ_PATH2 = $(patsubst %.c,$(O_PATH)/%.o, $(notdir $(GCC_SOURCE_PATH2)))

#生成目标文件
$(O_PATH)/$(target) : $(GCC_OBJ_PATH) $(GCC_OBJ_PATH2) ../OBJ/main.o
	$(cc) $(GCC_OBJ_PATH) $(GCC_OBJ_PATH2) ../OBJ/main.o $(PI_LIB_PATH) -o $(O_PATH)/$(target) $(LIB_NAME)
	rm ../OBJ/*.o

#将生成的.o文件放到O_PATH目录下
$(O_PATH)/%.o: $(SUBDIR)/%.c
	$(cc) -c $(PI_LIB_PATH) $< -o $@
$(O_PATH)/%.o: $(SUBDIR2)/%.c
	$(cc) -c $(PI_LIB_PATH) $< -o $@
../OBJ/main.o: main.c
	$(cc) -c $(PI_LIB_PATH) main.c -o ../OBJ/main.o

#伪目标
.PHONY : clean clear
clean :
	rm ../OBJ/*.o
	rm $(O_PATH)/$(target)
clear :
	rm ../OBJ/*.o