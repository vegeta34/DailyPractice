IEAuto_server :	main.o IEAuto_pthread.o
	cc -o IEAuto_server main.o IEAuto_pthread.o

main.o :
	g++ -c -lpthread main.cpp

IEAuto_pthread.o :	IEAuto_pthread.h
	g++ -c -lpthread IEAuto_pthread.cpp
