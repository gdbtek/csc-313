PGM = tree_main
OBJ = client.o tree_main.o

$(PGM): clean $(OBJ)
	g++ -Wall -g -o $(PGM) $(OBJ)
	rm -f $(OBJ)

run: $(PGM)
	./$(PGM)

clean:
	rm -f $(OBJ) $(PGM)

client.o: client.cpp
	g++ -Wall -c client.cpp

tree_main.o: tree_main.cpp
	g++ -Wall -c tree_main.cpp
