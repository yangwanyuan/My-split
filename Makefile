OPT ?= -g2 -O3
#OPT ?= -g2

SRC_DIR = ./src

INCLUDES = -I ${SRC_DIR} \

CXX = g++
CXX_FLAGS = --std=c++11 -Wall -fPIC ${OPT}

CORE_CXX_SRC = $(wildcard ${SRC_DIR}/*.cc)
CORE_CXX_OBJ = $(patsubst %.cc, %.o, ${CORE_CXX_SRC})

PROGNAME :=  my-split

.PHONY : all
all: ${PROGNAME}
	@echo 'Done'

${CORE_CXX_OBJ}: %.o: %.cc
	${CXX} ${CXX_FLAGS} ${INCLUDES} -c $< -o $@

my-split: my-split.cc ${CORE_CXX_OBJ}
	${CXX} ${CXX_FLAGS} ${INCLUDES} $^ -o $@ 

.PHONY : clean
clean:
	rm -fr ${CORE_CXX_OBJ}
	rm -fr ${PROGNAME}

