run: compile
	./PrimeTest.goodstuff

compile:
	gcc -O2 main.c -o PrimeTest.goodstuff -lgmp

