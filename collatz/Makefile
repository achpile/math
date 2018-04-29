all: collatz oddity

collatz: collatz.cpp
	gcc collatz.cpp -lm -o collatz

oddity: oddity.cpp
	gcc oddity.cpp -lm -lsfml-system -lsfml-window -lsfml-graphics -lstdc++ -o oddity

clean:
	rm collatz
	rm oddity
