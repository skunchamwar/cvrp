
GTEST_DIR = C:\googletest-release-1.8.0\googletest
GMOCK_DIR = C:\googletest-release-1.8.0\googlemock
USER_DIR = .

CPPFLAGS += -isystem $(GTEST_DIR)/include -isystem $(GMOCK_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread

LIBS=-lpthread

TESTS = cvrpUnittest

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

GMOCK_HEADERS = $(GMOCK_DIR)/include/gmock/*.h \
                $(GMOCK_DIR)/include/gmock/internal/*.h \
                $(GTEST_HEADERS)

SOURCES=../src/cvrp_util.cpp \
	../src/cvrp_idataModel.cpp \
	../src/cvrp_dataModel.cpp \
	../src/cvrp_vehicleTrip.cpp \
	../src/cvrp_solutionFinder.cpp \
	../src/jsoncpp.cpp \
	cvrp_dataModel.t.cpp \
	cvrp_util.t.cpp \
	cvrp_vehicleTrip.t.cpp \
	cvrp_solutionFinder.t.cpp \


OBJECTS=$(SOURCES:.cpp=.o) gmock_main.a

all : $(SOURCES) $(TESTS)


clean :
	rm -f $(TESTS) gtest.a gmock_main.a *.o

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GMOCK_HEADERS)
GMOCK_SRCS_ = $(GMOCK_DIR)/src/*.cc $(GMOCK_HEADERS)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) -I$(GMOCK_DIR) $(CXXFLAGS) \
            -c $(GTEST_DIR)/src/gtest-all.cc

gmock-all.o : $(GMOCK_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) -I$(GMOCK_DIR) $(CXXFLAGS) \
            -c $(GMOCK_DIR)/src/gmock-all.cc

gmock_main.o : $(GMOCK_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) -I$(GMOCK_DIR) $(CXXFLAGS) \
            -c $(GMOCK_DIR)/src/gmock_main.cc

gmock.a : gmock-all.o gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gmock_main.a : gmock-all.o gtest-all.o gmock_main.o
	$(AR) $(ARFLAGS) $@ $^

$(TESTS): $(OBJECTS) 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LIBS) $^ -o $@
