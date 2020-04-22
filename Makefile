
out: main.cpp
	g++ -o out main.cpp -std=c++17 -lglfw -framework OpenGL -g
clean:
	rm out 
all:
	make clean
	make
	./out