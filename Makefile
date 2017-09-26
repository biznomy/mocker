CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -std=c++11 
#export LD_LIBRARY_PATH=/usr/local/include/Poco:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH
BINDIR = ./bin

OBJS =	test.o

LIBS = -I poco/ -L poco/lib/Linux/x86_64 \
	-lPocoFoundation \
	-lPocoUtil \
	-lPocoNet \
	-lPocoJSON



TARGET =	$(BINDIR)/test

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

install:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)