OBJS = main.o IEAuto_pthread.o IEAuto_socket.o error.o
IEAuto_server :	$(OBJS)
	g++ -o IEAuto_server $(OBJS) -lpthread

main.o :
	g++ -c main.cpp -lpthread

IEAuto_socket.o : unp.h
	g++ -c IEAuto_socket.cpp -lpthread

IEAuto_pthread.o : unp.h
	g++ -c IEAuto_pthread.cpp -lpthread

error.o : unp.h

.PHONY : clean 

clean :
	rm IEAuto_server $(OBJS)
