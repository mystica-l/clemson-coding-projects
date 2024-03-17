# CoLab-05-Part-C MakeFile
# Uses -std=c++98 flag as the instructions say to not use c++11
compile:
	make compileCard
	make compileAnalyzeHand
	make compileBlackJackRules
	make compilePokerRules
	g++ -Wall Dealer.cpp Card.o AnalyzeHand.o BlackjackRules.o PokerRules.o -std=c++98 -o driver.out
# Compiles all necessary object files
compileCard:
	g++ -Wall Card.cpp -c -std=c++98
compileAnalyzeHand:
	g++ -Wall AnalyzeHand.cpp -c -std=c++98
compileBlackJackRules:
	g++ -Wall BlackjackRules.cpp -c -std=c++98
compilePokerRules:
	g++ -Wall PokerRules.cpp -c -std=c++98
# Different run commands for different command line arguments
run:
	./driver.out
runBlackJack:
	./driver.out 0
runPoker:
	./driver.out 1
clean:
	rm *.out
