# Variables

CC = g++

OBJ_DIR = obj
OBJ_LIBRARY_DIR = $(OBJ_DIR)/SciPP
OBJ_TESTS_DIR = $(OBJ_DIR)/tests
OBJ_EXAMPLES_DIR = $(OBJ_DIR)/examples

SRC_DIR = src
SRC_LIBRARY_DIR = $(SRC_DIR)/SciPP
SRC_TESTS_DIR = $(SRC_DIR)/tests
SRC_EXAMPLES_DIR = $(SRC_DIR)/examples

INCLUDE_DIR = include
INCLUDE_LIBRARY_DIR = $(INCLUDE_DIR)/SciPP

LIBRARY_OBJS = $(OBJ_LIBRARY_DIR)/Int.o $(OBJ_LIBRARY_DIR)/Frac.o $(OBJ_LIBRARY_DIR)/Matrice.o $(OBJ_LIBRARY_DIR)/Interpreteur.o $(OBJ_LIBRARY_DIR)/Plot.o
TESTS_OBJS = $(OBJ_TESTS_DIR)/main.o $(OBJ_TESTS_DIR)/Test.o $(OBJ_TESTS_DIR)/Int.o $(OBJ_TESTS_DIR)/Frac.o $(OBJ_TESTS_DIR)/Vect.o $(OBJ_TESTS_DIR)/Polynome.o $(OBJ_TESTS_DIR)/Matrice.o $(OBJ_TESTS_DIR)/List.o
EXAMPLES_OBJS = $(OBJ_EXAMPLES_DIR)/examples.o $(OBJ_EXAMPLES_DIR)/simuPhysique.o $(OBJ_EXAMPLES_DIR)/jeuxArithmetiques.o

# Règles générales

all: folders SciPP tests examples

check: tests
	valgrind ./SciPPTests

examples: $(INCLUDE_LIBRARY_DIR)/bin/SciPP.a $(EXAMPLES_OBJS)
	$(CC) $(EXAMPLES_OBJS) -o SciPPExamples $(INCLUDE_LIBRARY_DIR)/bin/SciPP.a -lsfml-graphics -lsfml-window -lsfml-system

tests: $(INCLUDE_LIBRARY_DIR)/bin/SciPP.a $(TESTS_OBJS)
	$(CC) $(TESTS_OBJS) -o SciPPTests $(INCLUDE_LIBRARY_DIR)/bin/SciPP.a -lsfml-graphics -lsfml-window -lsfml-system

SciPP: $(INCLUDE_LIBRARY_DIR)/bin/SciPP.a

clean:
	rm -rf $(OBJ_LIBRARY_DIR)/*.o $(OBJ_TESTS_DIR)/*.o $(OBJ_EXAMPLES_DIR)/*.o
	rm -rf SciPPExamples SciPPTests

folders:
	rm -rf $(INCLUDE_DIR) $(OBJ_DIR)
	mkdir $(OBJ_DIR) $(OBJ_LIBRARY_DIR) $(OBJ_TESTS_DIR) $(OBJ_EXAMPLES_DIR)
	mkdir $(INCLUDE_DIR) $(INCLUDE_LIBRARY_DIR) $(INCLUDE_LIBRARY_DIR)/bin

doxy:
	doxygen doc/doxygen

doxyClean:
	rm -rf doc/html

lineCount:
	git ls-files | xargs wc -l


# Compilation de la librairie

$(INCLUDE_LIBRARY_DIR)/bin/SciPP.a: $(LIBRARY_OBJS)
	rm -rf $(INCLUDE_LIBRARY_DIR)/*.h $(INCLUDE_LIBRARY_DIR)/*.hpp $(INCLUDE_LIBRARY_DIR)/bin/SciPP.a
	cp $(SRC_LIBRARY_DIR)/*.h $(SRC_LIBRARY_DIR)/*.hpp $(INCLUDE_LIBRARY_DIR)
	ar rcs $(INCLUDE_LIBRARY_DIR)/bin/SciPP.a $(LIBRARY_OBJS)

# Compilations spécifiques

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -o $@ -c $<
