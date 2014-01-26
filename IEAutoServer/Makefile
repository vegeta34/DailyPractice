IEAuto_server :	main.o IEAuto_pthread.o
	g++ -o IEAuto_server IEAuto_pthread.o IEAuto_socket.o main.o -lpthread

main.o :
	g++ -o main.o -c main.cpp -lpthread

IEAuto_socket.o : unp.h
	g++ -o IEAuto_socket.o -c IEAuto_socket.cpp -lpthread

IEAuto_pthread.o : unp.h IEAuto_pthread.h
	g++ -o IEAuto_pthread.o -c IEAuto_pthread.cpp -lpthread

clean :
	rm *.o IEAuto_server
