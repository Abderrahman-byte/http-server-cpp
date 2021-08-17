CC = g++
SRC_DIR := $(shell readlink -f ./src)
BUILD_DIR := $(shell readlink -f ./build)
INCLUDE_PATH := $(shell readlink -f ./include)
SHARED_LIBS := -pthread
LIBRARIES = ${BUILD_DIR}/lib/http_parser/parser.o\
	${BUILD_DIR}/lib/response/response.o \
	${BUILD_DIR}/lib/mime-types/mime.o
OBJECT_FILES = ${BUILD_DIR}/main.o ${BUILD_DIR}/utils.o ${BUILD_DIR}/server.o \
	${BUILD_DIR}/handleThread.o ${BUILD_DIR}/pool.o ${BUILD_DIR}/config.o \
	${BUILD_DIR}/handleRequest.o ${BUILD_DIR}/connection.o ${LIBRARIES} \
	${BUILD_DIR}/MainThread.o
APP_NAME = simple_http_server

${APP_NAME} : clean ${BUILD_DIR} ${OBJECT_FILES}
	${CC} ${SHARED_LIBS} -o ${BUILD_DIR}/${APP_NAME} ${OBJECT_FILES}
	@rm -f ${OBJECT_FILES}
	@if [ -e ${BUILD_DIR}/lib ] ; then rm -r ${BUILD_DIR}/lib ; fi

${BUILD_DIR}/lib/%.o : ${INCLUDE_PATH}/%.cpp
	@if [ ! -e $(shell dirname $@) ] ; then mkdir -p $(shell dirname $@) ; fi
	${CC} -c -o $@ $^

${BUILD_DIR}/%.o: ${SRC_DIR}/%.cpp
	${CC} -I ${INCLUDE_PATH} -c -o $@ $^

${BUILD_DIR} :
	@mkdir -p $@

clean :
	@rm -f ${OBJECT_FILES} ${BUILD_DIR}/${APP_NAME}
	@if [ -e ${BUILD_DIR}/lib ] ; then rm -r ${BUILD_DIR}/lib ; fi

default : ${APP_NAME}