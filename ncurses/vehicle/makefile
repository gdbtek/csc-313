PGM = p0
OBJ = vehicle.o car.o truck.o bus.o p0.o

$(PGM): clean $(OBJ)
	g++ -Wall -g -o $(PGM) $(OBJ) -lncurses

run: $(PGM)
	$(PGM)

clean:
	rm -f $(OBJ) $(PGM)

vehicle.o: vehicle.cpp
	g++ -Wall -c vehicle.cpp

car.o: car.cpp
	g++ -Wall -c car.cpp

truck.o: truck.cpp
	g++ -Wall -c truck.cpp

bus.o: bus.cpp
	g++ -Wall -c bus.cpp

p0.o: p0.cpp
	g++ -Wall -c p0.cpp
