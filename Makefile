outpout: main.o song.o
	g++ -c main.o song.o -o main2

main.o: main.cpp linkedlist.h song.h
	g++ -c main.cpp
song.o: song.cpp song.h
	g++ -c song.cpp

