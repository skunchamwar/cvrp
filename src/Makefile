CC=g++
CFLAGS=-c -Wall
LDFLAGS=
LIBS=

SOURCES=main.cpp \
	cvrp_idataModel.cpp \
	cvrp_dataModel.cpp \
	cvrp_vehicleTrip.cpp \
	cvrp_solutionFinder.cpp \
	cvrp_util.cpp \
	jsoncpp.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=cvrp

all: $(SOURCES) $(EXECUTABLE)

clean :
	rm -f $(EXECUTABLE) *.o
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@