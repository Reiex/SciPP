###############################################################################
# ENVIRONMENT VARIABLES                                                       #
###############################################################################


# Source directories
SRC_LIBRARY_DIR = src/SciPP
SRC_TESTS_DIR = tests
SRC_EXAMPLES_DIR = examples

# Include directory
INCLUDE_DIR = include

# .obj directories
OBJ_DIR = obj
OBJ_LIBRARY_DIR = $(OBJ_DIR)/SciPP
OBJ_TESTS_DIR = $(OBJ_DIR)/tests
OBJ_EXAMPLES_DIR = $(OBJ_DIR)/examples

# Compiled library directory
LIB_DIR = lib

# .obj lists
LIBRARY_OBJS = $(OBJ_LIBRARY_DIR)/misc.o \
			   $(OBJ_LIBRARY_DIR)/Int.o \
			   $(OBJ_LIBRARY_DIR)/Frac.o
TESTS_OBJS = $(OBJ_TESTS_DIR)/main.o \
			 $(OBJ_TESTS_DIR)/misc.o \
			 $(OBJ_TESTS_DIR)/Int.o \
			 $(OBJ_TESTS_DIR)/Quaternion.o \
			 $(OBJ_TESTS_DIR)/Frac.o \
			 $(OBJ_TESTS_DIR)/Vec.o \
			 $(OBJ_TESTS_DIR)/Polynomial.o \
			 $(OBJ_TESTS_DIR)/Mat.o
EXAMPLES_OBJS = $(OBJ_EXAMPLES_DIR)/main.o


# Compiler
CC = g++
# Compiler options
LIBRARY_CFLAGS = -I$(INCLUDE_DIR) -fpic
TESTS_CFLAGS = -I$(INCLUDE_DIR) -g
EXAMPLES_CFLAGS = -I$(INCLUDE_DIR)
# Linker options
LDFLAGS = -L$(LIB_DIR) -Wl,-rpath=$(LIB_DIR)
# Libraries linked
LIBRARY_LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system
TESTS_LDLIBS = -lSciPP $(LIBRARY_LDLIBS) -lgtest -lpthread
EXAMPLES_LDLIBS = -lSciPP $(LIBRARY_LDLIBS)


###############################################################################
# GENERAL TARGETS                                                             #
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
# GROUP TARGETS                                                               #
###############################################################################


SciPP: $(LIB_DIR)

examples: $(LIB_DIR) $(EXAMPLES_OBJS)
	$(CC) $(EXAMPLES_OBJS) -o SciPPExamples $(LDFLAGS) $(EXAMPLES_LDLIBS)

tests: $(LIB_DIR) $(TESTS_OBJS)
	$(CC) $(TESTS_OBJS) -o SciPPTests $(LDFLAGS) $(TESTS_LDLIBS)

folders:
	-rm -rf $(LIB_DIR) $(OBJ_DIR)
	mkdir $(OBJ_DIR) $(OBJ_LIBRARY_DIR) $(OBJ_TESTS_DIR) $(OBJ_EXAMPLES_DIR)
	mkdir $(LIB_DIR)


###############################################################################
# LIBRARY BUILDING TARGETS                                                    #
###############################################################################


$(LIB_DIR): $(LIBRARY_OBJS)
	-rm -rf $(LIB_DIR)/libSciPP.so
	$(CC) -shared -o $(LIB_DIR)/libSciPP.so $(LIBRARY_OBJS)

$(OBJ_LIBRARY_DIR)/%.o: $(SRC_LIBRARY_DIR)/%.cpp
	$(CC) $(LIBRARY_CFLAGS) -c $< -o $@


###############################################################################
# COMPILATION DES EXEMPLES ET DES TESTS                                       #
###############################################################################


$(OBJ_TESTS_DIR)/%.o: $(SRC_TESTS_DIR)/%.cpp
	$(CC) $(TESTS_CFLAGS) -c $< -o $@

$(OBJ_EXAMPLES_DIR)/%.o: $(SRC_EXAMPLES_DIR)/%.cpp
	$(CC) $(EXAMPLES_CFLAGS) -c $< -o $@
