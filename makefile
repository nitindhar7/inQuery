CXX= g++
CFLAGS=
SRCS= MinHeap.cpp Score.cpp Query.cpp QueryProcessor.cpp main.cpp
OBJS= MinHeap.o Score.o Query.o QueryProcessor.o main.o
HDRS= page_stats.h MinHeap.h Score.h QueryProcessor.h Query.h
BINS= inQuery

all: $(BINS) done

$(BINS): $(OBJS) $(HDRS)
	$(CXX) -o $@ $(CFLAGS) $(OBJS)

$(OBJS): $(SRCS) $(HDRS)
	$(CXX) -c $(CFLAGS) $(SRCS)

.PHONY: clean run done

clean:
	rm *.o $(BINS)

run:
	./$(BINS)

done:
	@echo "Done making: 'make run'"
