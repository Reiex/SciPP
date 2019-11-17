# Variables

CC = g++
OBJ_DIR = obj
LIBRARY_OBJS = $(OBJ_DIR)/Int.o $(OBJ_DIR)/Frac.o $(OBJ_DIR)/Matrice.o $(OBJ_DIR)/Interpreteur.o $(OBJ_DIR)/Plot.o
PROJECT_OBJS = $(OBJ_DIR)/exemples.o $(OBJ_DIR)/simuPhysique.o $(OBJ_DIR)/jeuxArithmetiques.o

# Règles générales

SciPP: $(EXAMPLE_OBJS) $(PROJECT_OBJS)
	$(CC) $(EXAMPLE_OBJS) $(PROJECT_OBJS) -o SciPP -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -rf *.o
	rm -rf +SciPP

lineCount:
	git ls-files | xargs wc -l


# Règles spécifiques

%.o: %.cpp
	$(CC) -o $@ -c $<
