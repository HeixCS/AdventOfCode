all: Days

Days: Day1 Day2 Day3 Day4 Day5 Day6 Day7 Day8 Day9 Day10 Day11 Day12

Day1: ./Day1/main.cpp
	g++ ./Day1/main.cpp -o ExecDay1

Day2: ./Day2/main.cpp
	g++ ./Day2/main.cpp -o ExecDay2

Day3: ./Day3/main.cpp
	g++ ./Day3/main.cpp -o ExecDay3

Day4: ./Day4/main.cpp
	g++ ./Day4/main.cpp -o ExecDay4

Day5: ./Day5/main.cpp
	g++ ./Day5/main.cpp -o ExecDay5

Day6: ./Day6/main.cpp
	g++ -std=c++17 -Wall ./Day6/main.cpp -o ExecDay6

Day7: ./Day7/main.cpp
	g++ -std=c++17 ./Day7/main.cpp -o ExecDay7

Day8: ./Day8/main.cpp
	g++ -std=c++17 ./Day8/main.cpp -o ExecDay8

Day9: ./Day9/main.cpp
	g++ -std=c++17 ./Day9/main.cpp -o ExecDay9

Day10: ./Day10/main.cpp
	g++ -std=c++17 ./Day10/main.cpp -o ExecDay10

Day11: ./Day11/main.cpp
	g++ -std=c++17 ./Day11/main.cpp -o ExecDay11

Day12: ./Day12/main.cpp
	g++ -std=c++17 ./Day12/main.cpp -o ExecDay12
