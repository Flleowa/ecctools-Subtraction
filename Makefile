default:
	gcc -O3 -c gmpecc.c -o gmpecc.o
	gcc -O3 -c util.c -o util.o
	gcc -O3 -o Subtraction Subtraction.c -march=native -mtune=native gmpecc.c util.o -lgmp
	#rm *.o
clean:
	rm -r *.o
