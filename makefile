CXX= g++
CFLAGS= -O2 -Werror -Wall -Wextra -pedantic
SRCS= MinHeap.cpp Score.cpp Query.cpp QueryProcessor.cpp main.cpp
OBJS= MinHeap.o Score.o Query.o QueryProcessor.o main.o
HDRS= config.h page_stats.h MinHeap.h Score.h QueryProcessor.h Query.h
BINS= inQuery

what:
	@echo ""
	@echo "inQuery"
	@echo "-------------------------------------------------------------------"
	@echo "Authors: Nitin Dhar, Chintan Jain"
	@echo "Report bugs to [nitindhar7@yahoo.com] or [chintan_jain22@yahoo.com]"
	@echo "-------------------------------------------------------------------"
	@echo ""
	@echo "Please configure package to your system..."
	@echo "To configure, type:       \"chmod u+x config && ./config\""
	@echo "To build program, type:   \"make all\""
	@echo "To run, type:             \"make run\""
	@echo ""

all: $(BINS)

$(BINS): $(OBJS) $(HDRS)
	$(CXX) -o $@ $(CFLAGS) $(OBJS)

$(OBJS): $(SRCS) $(HDRS)
	$(CXX) -c $(CFLAGS) $(SRCS)

.PHONY: clean run done

clean:
	rm *.o $(BINS)

run:
	./$(BINS)
