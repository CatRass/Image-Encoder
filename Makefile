all: compile

compile: 
	g++ -Wall -Werror main.cpp -std=c++23 -o ./build/main.exe

clean:
	rm main.o build/main.exe

assembly:
	g++ -S main.cpp

run:
	./build/main.exe