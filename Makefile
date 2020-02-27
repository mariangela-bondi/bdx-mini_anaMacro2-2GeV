CC = g++
LD = $(CC)
CFLAGS = -c -Wall -Os
IFLAGS =  -I./ -I$(BDXRECO_ROOT)/src/libraries -I$(BDXRECO_ROOT)/src/external/jana_0.7.7p1/src
ROOTINC := $(shell root-config --cflags)
ROOTLIB := $(shell root-config --glibs)
LIBS = -L$(BDXRECO_ROOT)/lib -lbdxReco -lbdxRecoExt -lJANA -lProof
LFLAGS = -Wl,-rpath $(BDXRECO_ROOT)/lib


SRC = $(wildcard *.cc)

TARGET = ana

OBJECTS = $(patsubst %.cc, %.o, $(wildcard *.cc))

all:   dict $(TARGET)

dict: BDXDSTSelector.h BDXDSTSelector1.h 
	@echo "Generating dictionary $@..."
	@rootcint -v -f BDXDSTSelector_Dict.cc -c -p $(IFLAGS) BDXDSTSelector.h	BDXDSTSelector_LinkDef.h
	@rootcint -v -f BDXDSTSelector1_Dict.cc -c -p $(IFLAGS) BDXDSTSelector1.h	BDXDSTSelector1_LinkDef.h
	

$(TARGET): $(OBJECTS)
	$(LD) -shared -fPIC -o libBDXDSTSelector.so $(LFLAGS) $(ROOTLIB) $(LIBS) $^
	$(LD) -o $@ $^ $(LFLAGS) $(ROOTLIB) $(LIBS)

%.o: %.cc
	$(CC) -fPIC -g $(CFLAGS) $(IFLAGS) $(ROOTINC) $^ -o $@

clean:
	rm $(TARGET) $(OBJECTS)
	rm libBDXDSTSelector.so