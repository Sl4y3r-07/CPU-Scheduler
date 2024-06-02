all:
	g++ -std=c++11 -Wall -o cpu_scheduler main.cpp scheduling_algo.cpp

clean:
	rm -f cpu_scheduler

.PHONY: all clean
