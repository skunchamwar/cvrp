CC=g++
CFLAGS=-c -Wall
LDFLAGS=
LIBS=

SOURCES=main.cpp cvrp_dataModel.cpp jsoncpp.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=cvrp

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@