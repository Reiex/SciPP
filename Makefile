###############################################################################
# VARIABLES D'ENVIRONNEMENT                                                   #
###############################################################################


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
WIN_LIB_DIR = vs/SciPP/Release

# Fichiers compilés
LIBRARY_OBJS = $(OBJ_LIBRARY_DIR)/Int.o $(OBJ_LIBRARY_DIR)/Frac.o $(OBJ_LIBRARY_DIR)/Matrice.o $(OBJ_LIBRARY_DIR)/Interpreteur.o $(OBJ_LIBRARY_DIR)/Plot.o $(OBJ_LIBRARY_DIR)/Random.o
TESTS_OBJS = $(OBJ_TESTS_DIR)/main.o $(OBJ_TESTS_DIR)/Test.o $(OBJ_TESTS_DIR)/Int.o $(OBJ_TESTS_DIR)/Frac.o $(OBJ_TESTS_DIR)/Vect.o $(OBJ_TESTS_DIR)/Polynome.o $(OBJ_TESTS_DIR)/Matrice.o $(OBJ_TESTS_DIR)/List.o
EXAMPLES_OBJS = $(OBJ_EXAMPLES_DIR)/examples.o $(OBJ_EXAMPLES_DIR)/simuPhysique.o $(OBJ_EXAMPLES_DIR)/jeuxArithmetiques.o


# Compilateur utilisé
CC = g++
# Parametres du linker
LDFLAGS = -L$(LIB_BINARIES_DIR) -Wl,-rpath=$(LIB_BINARIES_DIR)
# Librairies liées
LDLIBS = -lSciPP -lsfml-graphics -lsfml-window -lsfml-system


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
	$(CC) $(CFLAGS) $(EXAMPLES_OBJS) -o SciPPExamples $(LDFLAGS) $(LDLIBS)

tests: $(LIB_DIR) $(TESTS_OBJS)
	$(CC) $(CFLAGS) $(TESTS_OBJS) -o SciPPTests $(LDFLAGS) $(LDLIBS)

folders:
	-rm -rf $(LIB_DIR) $(OBJ_DIR)
	mkdir $(OBJ_DIR) $(OBJ_LIBRARY_DIR) $(OBJ_TESTS_DIR) $(OBJ_EXAMPLES_DIR)
	mkdir $(LIB_DIR) $(LIB_HEADERS_DIR) $(LIB_BINARIES_DIR)


###############################################################################
# COMPILATION DE LA BIBLIOTHEQUE CONSTRUITE                                   #
###############################################################################


$(LIB_DIR): $(LIBRARY_OBJS)
	find include -type f -exec rm -rf \{\} \;
	cp $(SRC_LIBRARY_DIR)/*.h $(SRC_LIBRARY_DIR)/*.hpp $(LIB_HEADERS_DIR)
	$(CC) -shared -o $(LIB_BINARIES_DIR)/libSciPP.so $(LIBRARY_OBJS)
	-cp $(WIN_LIB_DIR)/SciPP.lib $(LIB_BINARIES_DIR)

$(OBJ_LIBRARY_DIR)/%.o: $(SRC_LIBRARY_DIR)/%.cpp
	$(CC) -fpic -c $< -o $@


###############################################################################
# COMPILATION DES EXEMPLES ET DES TESTS                                       #
###############################################################################


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -I$(LIB_DIR) -c $< -o $@
