# Clementine Makefile
compile:
	make loan
	make retirement
	make register
	g++ -Wall Clementine.cpp Loan.o Retirement.o Register.o -o calculate.out
run:
	./calculate.out
clean:
	rm *.out
# Compiles all the included files into object files
loan:
	g++ -Wall Loan.cpp -c
retirement:
	g++ -Wall Retirement.cpp -c
register:
	g++ -Wall Register.cpp -c
