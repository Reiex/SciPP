# Règles générales

SciPP: obj/exemples.o obj/simuPhysique.o obj/jeuxArithmetiques.o obj/Entier.o obj/Interpreteur.o obj/Plot.o obj/SpecFunc.o
	g++ obj/exemples.o obj/simuPhysique.o obj/jeuxArithmetiques.o obj/Entier.o obj/Interpreteur.o obj/Plot.o obj/SpecFunc.o -o SciPP -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm obj/*
	rm SciPP


# Exemples

obj/exemples.o: src/exemples.cpp
	g++ -c src/exemples.cpp -o obj/exemples.o

obj/simuPhysique.o: src/simuPhysique.cpp
	g++ -c src/simuPhysique.cpp -o obj/simuPhysique.o
	
obj/jeuxArithmetiques.o: src/jeuxArithmetiques.cpp
	g++ -c src/jeuxArithmetiques.cpp -o obj/jeuxArithmetiques.o


# Bibliothèque

obj/Entier.o: src/Entier.cpp
	g++ -c src/Entier.cpp -o obj/Entier.o
	
obj/Interpreteur.o: src/Interpreteur.cpp
	g++ -c src/Interpreteur.cpp -o obj/Interpreteur.o
	
obj/Plot.o: src/Plot.cpp
	g++ -c src/Plot.cpp -o obj/Plot.o
	
obj/SpecFunc.o: src/SpecFunc.cpp
	g++ -c src/SpecFunc.cpp -o obj/SpecFunc.o
