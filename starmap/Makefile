all:
	g++ -Wall -Wextra -Werror -std=c++17 StarMap.cpp main.cpp Helpers.cpp -o map
	./map data/uniform1k.tsv
clean:
	rm -f map