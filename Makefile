# Règles générales

SciPP: obj/exemples.o obj/simuPhysique.o obj/jeuxArithmetiques.o obj/Entier.o obj/Interpreteur.o obj/Plot.o obj/SpecFunc.o
	g++ obj/exemples.o obj/simuPhysique.o obj/jeuxArithmetiques.o obj/Entier.o obj/Interpreteur.o obj/Plot.o obj/SpecFunc.o -o SciPP -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -r obj
	rm SciPP


# Règles d'aide

obj/:
	mkdir obj


# Exemples

obj/exemples.o: src/exemples.cpp obj/
	g++ -c src/exemples.cpp -o obj/exemples.o

obj/simuPhysique.o: src/simuPhysique.cpp obj/
	g++ -c src/simuPhysique.cpp -o obj/simuPhysique.o
	
obj/jeuxArithmetiques.o: src/jeuxArithmetiques.cpp obj/
	g++ -c src/jeuxArithmetiques.cpp -o obj/jeuxArithmetiques.o


# Bibliothèque

obj/Entier.o: src/Entier.cpp obj/
	g++ -c src/Entier.cpp -o obj/Entier.o
	
obj/Interpreteur.o: src/Interpreteur.cpp obj/
	g++ -c src/Interpreteur.cpp -o obj/Interpreteur.o
	
obj/Plot.o: src/Plot.cpp obj/
	g++ -c src/Plot.cpp -o obj/Plot.o
	
obj/SpecFunc.o: src/SpecFunc.cpp obj/
	g++ -c src/SpecFunc.cpp -o obj/SpecFunc.o
