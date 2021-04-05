all: labyrinth.cpp
	g++ -c labyrinth.cpp
	g++ -o run labyrinth.o
clean:
	rm -rf labyrinth.o
