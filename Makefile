build:
	gcc src/*.c -Wall -Wextra -pedantic -std=c99 -lm -lSDL2 -o game

run:
	./game

clean:
	rm game