CXX= g++
CFLAGS=
SRCS= main.cpp QueryProcessor.cpp Query.cpp
OBJS= main.o QueryProcessor.o Query.o
HDRS= page_stats.h boot.h QueryProcessor.h Query.h
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
