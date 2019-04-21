run: compile
	./PrimeTest.goodstuff

runFile: compile
	./PrimeTest.goodstuff premiers.txt

compile:
	gcc -O2 primeTest.c main.c -o PrimeTest.goodstuff -lgmp -Wno-unused-result

