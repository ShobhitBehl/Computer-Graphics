run : Controller.o main.o Model.o Parser.o Scene.o Shader.o Vertex.o View.o Texture.o stb_image.o
	g++ -std=c++11 -o bin/exe Controller.o main.o Model.o Parser.o Scene.o Shader.o Vertex.o View.o Texture.o stb_image.o -w -lGL -lglfw -lGLEW -lGLU
	./bin/exe

Controller.o : source/Controller.cpp include/View.h include/Scene.h
	g++ -std=c++11 -c source/Controller.cpp

main.o : source/main.cpp include/Controller.h
	g++ -std=c++11 -c source/main.cpp

Model.o : source/Model.cpp include/Shader.h include/Parser.h include/Texture.h
	g++ -std=c++11 -c source/Model.cpp

Parser.o : source/Parser.cpp include/Vertex.h
	g++ -std=c++11 -c source/Parser.cpp

Scene.o : source/Scene.cpp include/Model.h
	g++ -std=c++11 -c source/Scene.cpp

Shader.o : source/Shader.cpp
	g++ -std=c++11 -c source/Shader.cpp

Vertex.o : source/Vertex.cpp
	g++ -std=c++11 -c source/Vertex.cpp

View.o : source/View.cpp 
	g++ -std=c++11 -c source/View.cpp

Texture.o : source/Texture.cpp
	g++ -std=c++11 -c source/Texture.cpp

stb_image.o : source/stb_image.cpp
	g++ -std=c++11 -c source/stb_image.cpp

clean :
	rm *.o bin/exe