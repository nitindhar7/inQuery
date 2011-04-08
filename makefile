CXX= g++
CFLAGS=
SRCS= Score.cpp Query.cpp QueryProcessor.cpp main.cpp
OBJS= Score.o Query.o QueryProcessor.o main.o
HDRS= page_stats.h Score.h QueryProcessor.h Query.h
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
