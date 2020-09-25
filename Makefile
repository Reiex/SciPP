###############################################################################
# VARIABLES D'ENVIRONNEMENT                                                   #
###############################################################################


# Arborescence des sources

SRC_LIBRARY_DIR = src/SciPP
SRC_TESTS_DIR = tests
SRC_EXAMPLES_DIR = examples

# Arborescence des includes
INCLUDE_DIR = include

# Arborescence des .obj générés
OBJ_DIR = obj
OBJ_LIBRARY_DIR = $(OBJ_DIR)/SciPP
OBJ_TESTS_DIR = $(OBJ_DIR)/tests
OBJ_EXAMPLES_DIR = $(OBJ_DIR)/examples

# Arborescence des fichiers compilés
LIB_DIR = lib

# Fichiers compilés
LIBRARY_OBJS = $(OBJ_LIBRARY_DIR)/misc.o $(OBJ_LIBRARY_DIR)/Int.o
TESTS_OBJS = $(OBJ_TESTS_DIR)/main.o $(OBJ_TESTS_DIR)/Test.o $(OBJ_TESTS_DIR)/Int.o
EXAMPLES_OBJS = $(OBJ_EXAMPLES_DIR)/main.o


# Compilateur utilisé
CC = g++
# Parametres du compilateur
CFLAGS = -I$(INCLUDE_DIR)
# Parametres du linker
LDFLAGS = -L$(LIB_DIR) -Wl,-rpath=$(LIB_DIR)
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
	find $(OBJ_DIR) -type f -exec rm -rf \{\} \;
	find $(LIB_DIR) -type f -exec rm -rf \{\} \;
	rm -rf SciPPExamples SciPPTests


###############################################################################
# REGLES DE COMPILATIONS DE GROUPES                                           #
###############################################################################


SciPP: $(LIB_DIR)

examples: $(LIB_DIR) $(EXAMPLES_OBJS)
	$(CC) $(EXAMPLES_OBJS) -o SciPPExamples $(LDFLAGS) $(LDLIBS)

tests: $(LIB_DIR) $(TESTS_OBJS)
	$(CC) $(TESTS_OBJS) -o SciPPTests $(LDFLAGS) $(LDLIBS)

folders:
	-rm -rf $(LIB_DIR) $(OBJ_DIR)
	mkdir $(OBJ_DIR) $(OBJ_LIBRARY_DIR) $(OBJ_TESTS_DIR) $(OBJ_EXAMPLES_DIR)
	mkdir $(LIB_DIR)


###############################################################################
# COMPILATION DE LA BIBLIOTHEQUE CONSTRUITE                                   #
###############################################################################


$(LIB_DIR): $(LIBRARY_OBJS)
	-rm -rf $(LIB_DIR)/libSciPP.so
	$(CC) -shared -o $(LIB_DIR)/libSciPP.so $(LIBRARY_OBJS)

$(OBJ_LIBRARY_DIR)/%.o: $(SRC_LIBRARY_DIR)/%.cpp
	$(CC) $(CFLAGS) -fpic -c $< -o $@


###############################################################################
# COMPILATION DES EXEMPLES ET DES TESTS                                       #
###############################################################################


$(OBJ_TESTS_DIR)/%.o: $(SRC_TESTS_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_EXAMPLES_DIR)/%.o: $(SRC_EXAMPLES_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
