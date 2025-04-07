build:
	mkdir -p dist/
	cc ./src/triangle.c ./src/includes/gles2.c -o ./dist/triangle -lglfw -lGL

run: ./dist/triangle
	./dist/triangle

