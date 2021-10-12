
CXX = g++
CPPFLAGS = -Wall -g
LDLIBS = -ldl -lglfw -lm

main: main.o glad.o shaderClass.o EBO.o VBO.o VAO.o
	g++ -o main main.o glad.o shaderClass.o EBO.o VBO.o VAO.o $(LDLIBS)

main.o: main.cpp shaderClass.hpp EBO.hpp VBO.hpp VAO.hpp
	g++ $(CPPFLAGS) -c main.cpp 

glad.o: glad.c
	gcc $(CPPFLAGS) -c glad.c

VAO.o: VAO.cpp VAO.hpp VBO.hpp	
	g++ $(CPPFLAGS) -c VAO.cpp

VBO.o: VBO.cpp VBO.hpp
	g++ $(CPPFLAGS) -c VBO.cpp

EBO.o: EBO.cpp EBO.hpp
	g++ $(CPPFLAGS) -c EBO.cpp

shaderClass.o: shaderClass.cpp shaderClass.hpp
	g++ $(CPPFLAGS) -c shaderClass.cpp

clean:
	rm *.o main