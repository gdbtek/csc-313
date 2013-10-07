PGM = hash_main
OBJ = widget.o hash.o hash_main.o

$(PGM): clean $(OBJ)
	g++ -Wall -g -o $(PGM) $(OBJ)
	rm -f $(OBJ)

run: $(PGM)
	./$(PGM)

clean:
	rm -f $(OBJ) $(PGM)

widget.o: widget.cpp
	g++ -Wall -c widget.cpp

hash.o: hash.cpp
	g++ -Wall -c hash.cpp

hash_main.o: hash_main.cpp
	g++ -Wall -c hash_main.cpp
