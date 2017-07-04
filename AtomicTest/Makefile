ifeq	($(release),1)

FLG := -O3 -fPIC

else

FLG := -O3 -g -fPIC

endif
DIR_PWD := .
DIR_BIN := ../bin

PRG := $(DIR_BIN)/AtomicTest

SRC := $(wildcard *.cpp)

OBJ := $(patsubst %.cpp,%.o,$(SRC))

CC := g++

INC := -I./inc \
       -I../interface         \
	   -I../../DBUtils/interface/ \
	   -I../../utils/inc/ \
	   -I../../../../lib/cross/jsoncpp/inc/
	   
LIB := -L../bin/  -lAtomic  \
	   -L../../DBUtils/bin/  -lDBUtils \
	   -L../../utils/bin/  -lutils \
	   -L../../../../lib/linux/lib -liconv -lcconv \
	   -L../../../../lib/cross/jsoncpp/bin -ljsoncpp \
	   -L../../../../lib/cross/tinyxml/bin -ltinyxml \
	   -L../../../../lib/cross/ocilib-4.3.0/lib/linux/so -locilib  \
	   -L../../../../lib/cross/instantclient_12_1/sdk/lib/linux -lclntsh  -lclntshcore -lipc1 -lmql1 -lnnz12 -locci -lociei -lons \
	   -L../../../../lib/cross/boost/lib/linux/a -lboost_filesystem -lboost_system -lboost_thread
	   
.PHONY: clean

$(PRG): $(OBJ)
	$(CC) -o $@ $^ $(LIB)

%.o: %.cpp
	$(CC) $(FLG) -o $@ -c $< $(INC)

clean:
	rm -f $(OBJ) $(PRG)

copy:
	cp -f ../../DBUtils/bin/libDBUtils.so $(DIR_BIN)/
	cp -f ../../utils/bin/libutils.so $(DIR_BIN)/   
	cp -f ../../../../lib/linux/lib/libiconv.so.2 $(DIR_BIN)/   
	cp -f ../../../../lib/linux/lib/libcconv.so.0 $(DIR_BIN)/   
	cp -f ../../../../lib/cross/tinyxml/bin/libtinyxml.so $(DIR_BIN)/
	cp -f ../../../../lib/cross/jsoncpp/bin/libjsoncpp.so $(DIR_BIN)/   
	cp -f ../../../../lib/cross/ocilib-4.3.0/lib/linux/so/* $(DIR_BIN)/
	cp -f ../../../../lib/cross/instantclient_12_1/sdk/lib/linux/* $(DIR_BIN)/ 