CC= gcc
CXX= g++
CFLAGS=
SRCS= main.cpp Query.cpp QueryProcessor.cpp
OBJS= main.o Query.o QueryProcessor.o
HDRS= Query.h QueryProcessor.h boot.h util.h
BINS= inQuery

all: $(BINS) done

$(BINS): $(OBJS) $(HDRS)
	$(CXX) -o $@ $(CFLAGS) $(OBJS) -lz

$(OBJS): $(SRCS) $(HDRS)
	$(CXX) -c $(CFLAGS) $(SRCS)

.PHONY: clean run done

clean:
	rm *.o $(BINS)

run:
	./$(BINS)

done:
	echo "Done making\n"
