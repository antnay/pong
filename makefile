CXX = g++
CXXFLAGS = -g -Wall -std=c++20 -I/opt/homebrew/opt/sdl2/include/SDL2
LDFLAGS = -L/opt/homebrew/opt/sdl2/lib -lSDL2

all: run main

run: main
	./target/main


#main: src/main.o
#	$(CXX) $(CXXFLAGS) -o target/$@ $^ $(LDFLAGS)

#main.o: src/ main.cpp src/game.h src/window.h src/pong.h
#	$(CXX) $(CXXFLAGS) -o target/$@ -c $< $(LDFLAGS)

main: src/main.o src/window.o src/pong.o src/game.o
	$(CXX) $(CXXFLAGS) -o target/$@ $^ $(LDFLAGS)

main.o: src/src.cpp src/window.h
	$(CXX) $(CXXFLAGS) -o target/$@ -c $< $(LDFLAGS)

window.o: src/window.cpp
	$(CXX) $(CXXFLAGS) -o target/$@ -c $< $(LDFLAGS)

pong.o: src/pong.cpp
	$(CXX) $(CXXFLAGS) -o target/$@ -c $< $(LDFLAGS)

#game.o: src/game.cpp src/window.h src/pong.h
#	$(CXX) $(CXXFLAGS) -o target/$@ -c $< $(LDFLAGS)

clean:
	rm -f src/*.o target/main target/*.o
