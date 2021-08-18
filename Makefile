CC = g++

INCLUDE_DIR := $(shell realpath ./include)
BUILD_DIR := $(shell realpath ./build)
SRC_DIR := $(shell realpath ./src)
libraries := $(shell ls ${INCLUDE_DIR})

SOURCE_FILES := $(shell ls ${SRC_DIR}/*.cpp)

OBJECTS := $(foreach source, ${SOURCE_FILES}, $(shell basename ${source}))
OBJECTS := $(OBJECTS:cpp=o)
OBJECTS := $(foreach object , ${OBJECTS}, ${BUILD_DIR}/obj/${object})
LINKFLAGS := $(foreach lib, ${libraries}, -l${lib})
LIBSFLAGS := -L${BUILD_DIR}/lib

APP_NAME = simple_http_server

${APP_NAME} : prepare ${libraries} ${OBJECTS}
	g++ ${LIBSFLAGS} ${OBJECTS} ${LINKFLAGS} -pthread -o ${BUILD_DIR}/${APP_NAME}

${BUILD_DIR}/obj/%.o : ${SRC_DIR}/%.cpp
	g++ -I ${INCLUDE_DIR} -c -o $@ $^

${libraries} : % : ${INCLUDE_DIR}/% 
	$(eval library_source_files := $(shell ls $^/*.cpp))
	$(eval library_basenames := $(foreach file, ${library_source_files}, $(shell basename ${file})))
	$(eval library_objects := $(foreach file, ${library_basenames}, $(file:cpp=o)))
	$(eval library_objects := $(foreach file, ${library_objects}, ${BUILD_DIR}/obj/$@_${file}))
	
	for library_file in ${library_source_files} ; do \
		filename=$$(basename $$library_file) ; \
		objectname=$$(echo $$filename | sed -E 's/(.*)\.cpp/\1.o/') ; \
		g++ -c -o ${BUILD_DIR}/obj/$@_$$objectname $$library_file  ;\
	done

	ar -cr ${BUILD_DIR}/lib/lib$@.a ${library_objects}

clean :
	if [ -e ${BUILD_DIR}/lib ] ; then rm -r ${BUILD_DIR}/lib/ ; fi
	if [ -e ${BUILD_DIR}/obj ] ; then rm -r ${BUILD_DIR}/obj/ ; fi
	if [ -e ${BUILD_DIR}/${APP_NAME} ] ; then rm ${BUILD_DIR}/${APP_NAME} ; fi

prepare : clean
	if [ ! -e ${BUILD_DIR} ] ; then mkdir -p ${BUILD_DIR} ; fi
	if [ ! -e ${BUILD_DIR}/lib ] ; then mkdir -p ${BUILD_DIR}/lib ; fi
	if [ ! -e ${BUILD_DIR}/obj ] ; then mkdir -p ${BUILD_DIR}/obj ; fi

all : ${APP_NAME} clean

.PHONY : ${APP_NAME} clean

default : ${APP_NAME}