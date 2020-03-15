# Variables

CC = g++
OBJ_DIR = obj
OBJ_LIBRARY_DIR = $(OBJ_DIR)/SciPP
SRC_DIR = src
SRC_LIBRARY_DIR = $(SRC_DIR)/SciPP
INCLUDE_DIR = include
INCLUDE_LIBRARY_DIR = $(INCLUDE_DIR)/SciPP
LIBRARY_OBJS = $(OBJ_LIBRARY_DIR)/Int.o $(OBJ_LIBRARY_DIR)/Frac.o $(OBJ_LIBRARY_DIR)/Matrice.o $(OBJ_LIBRARY_DIR)/Interpreteur.o $(OBJ_LIBRARY_DIR)/Plot.o
PROJECT_OBJS = $(OBJ_DIR)/exemples.o $(OBJ_DIR)/simuPhysique.o $(OBJ_DIR)/jeuxArithmetiques.o

# Règles générales

all: folders SciPP exemples

exemples: $(INCLUDE_LIBRARY_DIR)/bin/SciPP.a $(PROJECT_OBJS)
	$(CC) $(PROJECT_OBJS) -o SciPPExamples $(INCLUDE_LIBRARY_DIR)/bin/SciPP.a -lsfml-graphics -lsfml-window -lsfml-system

SciPP: $(INCLUDE_LIBRARY_DIR)/bin/SciPP.a

clean:
	rm -rf $(OBJ_DIR)/*.o $(OBJ_LIBRARY_DIR)/*.o
	rm -rf SciPP

folders:
	rm -rf $(INCLUDE_DIR) $(OBJ_DIR)
	mkdir $(OBJ_DIR) $(OBJ_LIBRARY_DIR)
	mkdir $(INCLUDE_DIR) $(INCLUDE_LIBRARY_DIR) $(INCLUDE_LIBRARY_DIR)/bin

doxy:
	doxygen doc/doxygen

doxyClean:
	rm -rf doc/html

lineCount:
	git ls-files | xargs wc -l


# Compilation de la librairie

$(INCLUDE_LIBRARY_DIR)/bin/SciPP.a: $(LIBRARY_OBJS)
	rm -rf $(INCLUDE_LIBRARY_DIR)/*.h $(INCLUDE_LIBRARY_DIR)/*.hpp
	cp $(SRC_LIBRARY_DIR)/*.h $(INCLUDE_LIBRARY_DIR)
	cp $(SRC_LIBRARY_DIR)/*.hpp $(INCLUDE_LIBRARY_DIR)
	ar rcs $(INCLUDE_LIBRARY_DIR)/bin/SciPP.a $(LIBRARY_OBJS)

# Compilations spécifiques

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -o $@ -c $<
