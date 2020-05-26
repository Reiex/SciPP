###############################################################################
# VARIABLES D'ENVIRONNEMENT                                                   #
###############################################################################


# Compilateur utilisé
CC = g++

# Arborescence des sources
SRC_DIR = src
SRC_LIBRARY_DIR = $(SRC_DIR)/SciPP
SRC_TESTS_DIR = $(SRC_DIR)/tests
SRC_EXAMPLES_DIR = $(SRC_DIR)/examples

# Arborescence des .obj générés
OBJ_DIR = obj
OBJ_LIBRARY_DIR = $(OBJ_DIR)/SciPP
OBJ_TESTS_DIR = $(OBJ_DIR)/tests
OBJ_EXAMPLES_DIR = $(OBJ_DIR)/examples

# Arborescence de la bibliothèque construite
LIB_DIR = include
LIB_HEADERS_DIR = $(LIB_DIR)/SciPP
LIB_BINARIES_DIR = $(LIB_HEADERS_DIR)/bin

# Fichiers compilés
LIBRARY_OBJS = $(OBJ_LIBRARY_DIR)/Int.o $(OBJ_LIBRARY_DIR)/Frac.o $(OBJ_LIBRARY_DIR)/Matrice.o $(OBJ_LIBRARY_DIR)/Interpreteur.o $(OBJ_LIBRARY_DIR)/Plot.o $(OBJ_LIBRARY_DIR)/Random.o
TESTS_OBJS = $(OBJ_TESTS_DIR)/main.o $(OBJ_TESTS_DIR)/Test.o $(OBJ_TESTS_DIR)/Int.o $(OBJ_TESTS_DIR)/Frac.o $(OBJ_TESTS_DIR)/Vect.o $(OBJ_TESTS_DIR)/Polynome.o $(OBJ_TESTS_DIR)/Matrice.o $(OBJ_TESTS_DIR)/List.o
EXAMPLES_OBJS = $(OBJ_EXAMPLES_DIR)/examples.o $(OBJ_EXAMPLES_DIR)/simuPhysique.o $(OBJ_EXAMPLES_DIR)/jeuxArithmetiques.o


###############################################################################
# REGLES GENERALES                                                            #
###############################################################################


all: folders SciPP tests examples

check: tests
	valgrind ./SciPPTests

docs:
	doxygen doc/doxyfilerc

clean:
	find obj -type f -exec rm -rf \{\} \;
	rm -rf SciPPExamples SciPPTests


###############################################################################
# REGLES DE COMPILATIONS DE GROUPES                                           #
###############################################################################


SciPP: $(LIB_DIR)

examples: $(LIB_DIR) $(EXAMPLES_OBJS)
	$(CC) $(EXAMPLES_OBJS) -o SciPPExamples $(LIB_BINARIES_DIR)/SciPP.so -lsfml-graphics -lsfml-window -lsfml-system

tests: $(LIB_DIR) $(TESTS_OBJS)
	$(CC) $(TESTS_OBJS) -o SciPPTests $(LIB_BINARIES_DIR)/SciPP.so -lsfml-graphics -lsfml-window -lsfml-system

folders:
	rm -rf $(LIB_DIR) $(OBJ_DIR)
	mkdir $(OBJ_DIR) $(OBJ_LIBRARY_DIR) $(OBJ_TESTS_DIR) $(OBJ_EXAMPLES_DIR)
	mkdir $(LIB_DIR) $(LIB_HEADERS_DIR) $(LIB_BINARIES_DIR)


###############################################################################
# COMPILATION DE LA BIBLIOTHEQUE CONSTRUITE                                   #
###############################################################################


$(LIB_DIR): $(LIBRARY_OBJS)
	rm -rf $(LIB_HEADERS_DIR)/*.h $(LIB_HEADERS_DIR)/*.hpp $(LIB_BINARIES_DIR)/SciPP.so
	cp $(SRC_LIBRARY_DIR)/*.h $(SRC_LIBRARY_DIR)/*.hpp $(LIB_HEADERS_DIR)
	$(CC) -shared -o $(LIB_BINARIES_DIR)/SciPP.so $(LIBRARY_OBJS)

$(OBJ_LIBRARY_DIR)/%.o: $(SRC_LIBRARY_DIR)/%.cpp
	$(CC) -fpic -c $< -o $@


###############################################################################
# COMPILATION DES EXEMPLES ET DES TESTS                                       #
###############################################################################


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $< -o $@
