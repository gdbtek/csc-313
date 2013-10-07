PGM = graph_main
OBJ = graph.o graph_main.o

$(PGM): clean $(OBJ)
	g++ -Wall -g -o $(PGM) $(OBJ)
	rm -f $(OBJ)

run: $(PGM)
	./$(PGM)

clean:
	rm -f $(OBJ) $(PGM)

graph.o: graph.cpp
	g++ -Wall -c graph.cpp

graph_main.o: graph_main.cpp
	g++ -Wall -c graph_main.cpp
