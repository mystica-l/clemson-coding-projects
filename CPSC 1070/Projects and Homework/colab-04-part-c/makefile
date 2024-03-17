# CoLab-04-Part-C MakeFile
# Uses -std=c++98 flag as the instructions say to not use c++11
compile:
	make compileCard
	make compileDeckOfCards
	g++ -Wall Driver.cpp Card.o DeckOfCards.o -std=c++98 -o driver.out
compileCard:
	g++ -Wall Card.cpp -c -std=c++98
compileDeckOfCards:
	g++ -Wall DeckOfCards.cpp -c -std=c++98
run:
	./driver.out
clean:
	rm *.out
