run: compile
	./yes.ha

compile:
	gcc  -g3 main.c -o yes.ha -lgmp