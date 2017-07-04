ifeq	($(release),1)

FLG := -O3 -fPIC 

else

FLG := -O0 -g -fPIC 

endif
#Makefile当前所在目录
DIR_PWD := .
#编译结果文件名
EXE_NAME := AtomicDemo
#编译类型，如果为执行文件，则为空，动态库则等于 -shared
EXE_TYPE :=  
#编译结果目录
EXE_DIR  :=$(DIR_PWD)
#源文件目录
DIR_CPP  :=$(DIR_PWD)

#开发库相关动态库和文件的目录
DIR_DEV_ROOT := $(DIR_PWD)/../../../..
DIR_LIB_linux        :=$(DIR_DEV_ROOT)/lib/linux
DIR_LIB_boost        :=$(DIR_DEV_ROOT)/lib/cross/boost
DIR_LIB_ocilib       :=$(DIR_DEV_ROOT)/lib/cross/ocilib-4.3.0
DIR_LIB_oracle       :=$(DIR_DEV_ROOT)/lib/cross/instantclient_12_1/sdk
DIR_LIB_jsoncpp      :=$(DIR_DEV_ROOT)/lib/cross/jsoncpp
DIR_LIB_log4cpp      :=$(DIR_DEV_ROOT)/lib/cross/log4cpp
DIR_LIB_tinyxml      :=$(DIR_DEV_ROOT)/lib/cross/tinyxml
DIR_LIB_zlib         :=$(DIR_DEV_ROOT)/lib/cross/zlib1
DIR_LIB_protcomm     :=$(DIR_DEV_ROOT)/lib_protcomm/sources/protcomm
DIR_LIB_tcpcomm2     :=$(DIR_DEV_ROOT)/lib_tcpcomm2/sources/tcpcomm2
DIR_LIB_utils        :=$(DIR_DEV_ROOT)/lib_libSelf/cross/utils
DIR_LIB_DBUtils      :=$(DIR_DEV_ROOT)/lib_libSelf/cross/DBUtils
DIR_LIB_Atomic       :=$(DIR_DEV_ROOT)/lib_libSelf/cross/Atomic
DIR_LIB_ServerFramed :=$(DIR_DEV_ROOT)/project_vmr/sources/ServerFramed

PRG := $(EXE_DIR)/$(EXE_NAME)

SRC := $(wildcard $(DIR_CPP)/*.c $(DIR_CPP)/*.cpp)

OBJ := $(patsubst %.cpp,%.o,$(SRC))

CC := g++

INC :=  -I$(DIR_PWD)/ \
        -I$(DIR_LIB_Atomic)/interface \
		-I$(DIR_LIB_DBUtils)/interface \
		-I$(DIR_LIB_utils)/inc \
		-I$(DIR_LIB_linux)/inc \
		-I$(DIR_LIB_boost)/include \
		-I$(DIR_LIB_oracle)/include \
		-I$(DIR_LIB_jsoncpp)/inc \
		-I$(DIR_LIB_tinyxml)/inc \
		-I$(DIR_LIB_ocilib)/include


LIB :=  -lpthread -lrt -lstdc++\
		-L$(DIR_LIB_DBUtils)/bin -lDBUtils \
		-L$(DIR_LIB_Atomic)/bin -lAtomic \
		-L$(DIR_LIB_utils)/bin -lutils \
		-L$(DIR_LIB_linux)/lib -liconv -lcconv \
		-L$(DIR_LIB_tinyxml)/bin -ltinyxml \
		-L$(DIR_LIB_boost)/lib/linux/a -lboost_filesystem -lboost_system -lboost_date_time -lboost_thread \
		-L$(DIR_LIB_oracle)/lib/linux -lclntsh  -lclntshcore -lipc1 -lmql1 -lnnz12 -locci -lociei -lons\
		-L$(DIR_LIB_jsoncpp)/bin -ljsoncpp \
		-L$(DIR_LIB_ocilib)/lib/linux/so -locilib 

.PHONY: clean

$(PRG): $(OBJ)
	$(CC) $(EXE_TYPE)-o $@ $^ $(LIB)

%.o: %.cpp
	$(CC) $(FLG) -o $@ -c $< $(INC)

#清理命令
clean:
	rm -f $(OBJ) $(PRG) $(DIR_CPP)/*.o
	
#拷贝命令
DIR_COPY_TO_DES :=$(EXE_DIR)
copy:
	cp -u $(DIR_LIB_DBUtils)/bin/libDBUtils.so $(DIR_COPY_TO_DES)/
	cp -u $(DIR_LIB_Atomic)/bin/libAtomic.so $(DIR_COPY_TO_DES)/
	cp -u $(DIR_LIB_utils)/bin/libutils.so $(DIR_COPY_TO_DES)/
	cp -u $(DIR_LIB_linux)/lib/libiconv.so.2 $(DIR_COPY_TO_DES)/
	cp -u $(DIR_LIB_linux)/lib/libcconv.so.0 $(DIR_COPY_TO_DES)/
	cp -u $(DIR_LIB_tinyxml)/bin/libtinyxml.so $(DIR_COPY_TO_DES)/
	cp -u $(DIR_LIB_jsoncpp)/bin/libjsoncpp.so $(DIR_COPY_TO_DES)/
	cp -u $(DIR_LIB_oracle)/lib/linux/* $(DIR_COPY_TO_DES)/
	cp -u $(DIR_LIB_ocilib)/lib/linux/so/* $(DIR_COPY_TO_DES)/
	cp -u $(DIR_LIB_Atomic)/bin/AtomicTest.DBUtils.xml $(DIR_COPY_TO_DES)/
	cp -u $(DIR_LIB_Atomic)/bin/AtomicTest.SQL.xml $(DIR_COPY_TO_DES)/

	

    
    
