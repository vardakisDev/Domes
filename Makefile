CC = g++
CFLAGS = -I../headers


SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, obj/%.o, $(SRC))
EXEC = SimulationFinalCovid19

$(EXEC) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c  $< -o $@


clean:
	del obj\*.o
	del $(EXEC).exe