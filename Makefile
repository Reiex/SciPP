# Variables

CC = g++
OBJ_DIR = obj
OBJ_LIBRARY_DIR = obj/SciPP
SRC_DIR = src
LIBRARY_OBJS = $(OBJ_LIBRARY_DIR)/Int.o $(OBJ_LIBRARY_DIR)/Frac.o $(OBJ_LIBRARY_DIR)/Matrice.o $(OBJ_LIBRARY_DIR)/Interpreteur.o $(OBJ_LIBRARY_DIR)/Plot.o
PROJECT_OBJS = $(OBJ_DIR)/exemples.o $(OBJ_DIR)/simuPhysique.o $(OBJ_DIR)/jeuxArithmetiques.o $(OBJ_DIR)/projetGeom.o

# Règles générales

examples: $(OBJ_DIR)/SciPP.a $(PROJECT_OBJS)
	$(CC) $(PROJECT_OBJS) -o SciPP $(OBJ_DIR)/SciPP.a -lsfml-graphics -lsfml-window -lsfml-system

SciPP: $(OBJ_DIR)/SciPP.a

clean:
	rm -rf $(OBJ_DIR)/SciPP.a
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(OBJ_LIBRARY_DIR)/*.o
	rm -rf SciPP

doxy:
	doxygen doc/doxygen

doxyClean:
	rm -rf doc/html doc/latex

lineCount:
	git ls-files | xargs wc -l


# Build la librairie

$(OBJ_DIR)/SciPP.a: $(LIBRARY_OBJS)
	ar rcs $(OBJ_DIR)/SciPP.a $(LIBRARY_OBJS)

# Compilations spécifiques

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -o $@ -c $<
