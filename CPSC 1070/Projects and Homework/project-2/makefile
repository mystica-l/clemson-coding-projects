# Makefile
# Compiles everything
compile:
	make date
	make pizzaWar
	make pizzaStore
	g++ -Wall driver.cpp Date.o MysteryMachine.o PizzaWars.o PizzaStore.o -o battle.out
# Compiles the date object file
date:
	g++ -Wall Date.cpp -c
# Compiles the pizza wars object file
pizzaWar:
	g++ -Wall PizzaWars.cpp -c
# Compiles the pizza store object file
pizzaStore:
	g++ -Wall PizzaStore.cpp -c
# Runs the .out
run:
	./battle.out
# Removes all .out
clean:
	rm *.out
