
GTEST_DIR = C:\googletest-release-1.8.0\googletest
USER_DIR = .

CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread

LIBS=-lpthread

TESTS = cvrpUnittest

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

SOURCES=../cvrp_util.cpp \
	../cvrp_dataModel.cpp \
	../jsoncpp.cpp \
	cvrp_dataModel.t.cpp \
	cvrp_util.t.cpp

OBJECTS=$(SOURCES:.cpp=.o) gtest_main.a

all : $(SOURCES) $(TESTS)


clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^


$(TESTS): $(OBJECTS) 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LIBS) $^ -o $@
