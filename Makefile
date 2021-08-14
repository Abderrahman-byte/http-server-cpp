CC = g++
SRC_DIR := $(shell readlink -f ./src)
BUILD_DIR := $(shell readlink -f ./build)
INCLUDE_PATH := $(shell readlink -f ./include)
SHARED_LIBS := -pthread
LIBRARIES = ${BUILD_DIR}/lib/http_parser/parser.o
OBJECT_FILES = ${BUILD_DIR}/main.o \
	${BUILD_DIR}/server.o ${BUILD_DIR}/handleThread.o \
	${BUILD_DIR}/connection.o ${LIBRARIES}
APP_NAME = main

${APP_NAME} : clean ${OBJECT_FILES}
	@${CC} ${SHARED_LIBS} -o ${BUILD_DIR}/${APP_NAME} ${OBJECT_FILES}
	@rm -f ${OBJECT_FILES} ./main
	@if [ -e ${BUILD_DIR}/lib ] ; then rm -r ${BUILD_DIR}/lib ; fi

${BUILD_DIR}/lib/%.o : ${INCLUDE_PATH}/%.cpp
	@if [ ! -e $(shell dirname $@) ] ; then mkdir -p $(shell dirname $@) ; fi
	@${CC} -c -o $@ $^

${BUILD_DIR}/%.o: ${SRC_DIR}/%.cpp
	@${CC} -I ${INCLUDE_PATH} -c -o $@ $^

clean :
	@rm -f ${OBJECT_FILES} ./main
	@if [ -e ${BUILD_DIR}/lib ] ; then rm -r ${BUILD_DIR}/lib ; fi

default : main