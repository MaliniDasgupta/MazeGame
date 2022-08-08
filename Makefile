#Used ECS32C lecture slides for reference
all: maze

maze: maze.cpp
	g++ -Wall -Werror -std=c++14 maze.cpp -o maze

.PHONY: clean
clean:
	rm -f maze