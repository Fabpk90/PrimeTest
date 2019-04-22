run: compile
	./PrimeTest.goodstuff

runFile: compile
	./PrimeTest.goodstuff premiers.txt

compile:
	gcc -g3 primeTest.c main.c -o PrimeTest.goodstuff -lgmp -Wno-unused-result

