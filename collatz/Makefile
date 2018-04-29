all: collatz oddity evenity

collatz: collatz.cpp
	gcc collatz.cpp -lm -o collatz

oddity: oddity.cpp
	gcc oddity.cpp -lm -lsfml-system -lsfml-window -lsfml-graphics -lstdc++ -o oddity

evenity: evenity.cpp
	gcc evenity.cpp -lm -lsfml-system -lsfml-window -lsfml-graphics -lstdc++ -o evenity

clean:
	rm collatz
	rm oddity
	rm evenity
