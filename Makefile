PROG          = apng2mng
SRC_FILES     = apng2mng.cpp main.cpp

CXX = g++
CC = $(CXX)

DEBUG_LEVEL   = -g
EXTRA_CCFLAGS = -Wall
CXXFLAGS      = $(DEBUG_LEVEL) $(EXTRA_CCFLAGS)
CCFLAGS       = $(CXXFLAGS)

COURSE_DIR    = /usr/include:/usr/local/include
LIBDIR        = /usr/lib:/usr/local/lib

CPPFLAGS      = -I./src/ \
                -I$(COURSE_DIR)
LDFLAGS       = -L./src/ \
                -L$(COURSE_DIR)

LDLIBS        = -lapngasm -lmng

O_FILES       = ./src/$(SRC_FILES:%.cpp=%.o)


all: $(PROG)
.PHONY: all

$(PROG): $(O_FILES)

clean:
	$(RM) $(O_FILES) $(PROG)
.PHONY: clean
