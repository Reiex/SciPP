# Variables

CC = g++
OBJ_DIR = obj
SRC_DIR = src
LIBRARY_OBJS = $(OBJ_DIR)/Int.o $(OBJ_DIR)/Frac.o $(OBJ_DIR)/Matrice.o $(OBJ_DIR)/Interpreteur.o $(OBJ_DIR)/Plot.o
PROJECT_OBJS = $(OBJ_DIR)/exemples.o $(OBJ_DIR)/simuPhysique.o $(OBJ_DIR)/jeuxArithmetiques.o

# Règles générales

SciPP: $(LIBRARY_OBJS) $(PROJECT_OBJS)
	$(CC) $(LIBRARY_OBJS) $(PROJECT_OBJS) -o SciPP -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf SciPP

lineCount:
	git ls-files | xargs wc -l


# Règles spécifiques

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -o $@ -c $<
