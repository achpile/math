all: collatz collatz2 oddity evenity csv csv2

csv: csv.cpp
	gcc csv.cpp -lm -o csv

csv2: csv2.cpp
	gcc csv2.cpp -lm -o csv2

collatz: collatz.cpp
	gcc collatz.cpp -lm -o collatz

collatz2: collatz2.cpp
	gcc collatz2.cpp -lm -o collatz2

oddity: oddity.cpp
	gcc oddity.cpp -lm -lsfml-system -lsfml-window -lsfml-graphics -lstdc++ -o oddity

evenity: evenity.cpp
	gcc evenity.cpp -lm -lsfml-system -lsfml-window -lsfml-graphics -lstdc++ -o evenity

clean:
	rm collatz
	rm collatz2
	rm oddity
	rm evenity
	rm csv
	rm csv2
