all: main.cpp routing_algo.cpp node.h
	g++ -std=c++11 main.cpp routing_algo.cpp -o rip
	./rip < sampleinput.txt