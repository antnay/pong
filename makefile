CXX = g++
CXXFLAGS = -g -Wall -std=c++20 -I/opt/homebrew/opt/sdl2/include/SDL2 -I/users/anthony/Documents/programming/c++/metal-cpp -I/opt/homebrew/opt/sdl2_ttf/include/SDL2
LDFLAGS = -L/opt/homebrew/opt/sdl2/lib -lSDL2
SRC = src/main.cpp src/window.hpp src/game.hpp src/pong.hpp src/lib.hpp
TARGET = src/main.o src/window.o src/game.o src/pong.o src/lib.o

all: run main

run: main
	./target/main

#main: src/main.o
#	$(CXX) $(CXXFLAGS) -o target/$@ $^ $(LDFLAGS)

#main.o: src/ main.cpp src/game.h src/window.h src/pong.h
#	$(CXX) $(CXXFLAGS) -o target/$@ -c $< $(LDFLAGS)

main: $(TARGET)
	$(CXX) $(CXXFLAGS) -o target/$@ $^ $(LDFLAGS)

target/main.o: $(SRC)
	$(CXX) $(CXXFLAGS) -o target/$@ -c $< $(LDFLAGS)

#window.o: src/window.cpp
#	$(CXX) $(CXXFLAGS) -o target/$@ -c $< $(LDFLAGS)

#pong.o: src/pong.cpp
#	$(CXX) $(CXXFLAGS) -o target/$@ -c $< $(LDFLAGS)

#lib.o: src/lib.cpp
#	$(CXX) $(CXXFLAGS) -o target/$@ -c $< $(LDFLAGS)

#game.o: src/game.cpp src/window.h src/pong.h
#	$(CXX) $(CXXFLAGS) -o target/$@ -c $< $(LDFLAGS)

clean:
	rm -f src/*.o

full_clean:
	rm -f src/*.o target/main target/*.o
