#include <stdio.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> 

#include "includes/glad/gles2.h"

GLuint shader_program;
GLuint vbo = 0, vao = 0;

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	printf("Key %d pressed\n", key);
	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}		
}

void gl_info() {
	printf("Renderer: %s\nVersion supported: %s\n", (GLubyte*) glGetString(GL_RENDERER), (GLubyte*)glGetString(GL_VERSION));
}

void setup() {
	float triangle[] = {
		0, .5, 0,
		.5, -.5, 0,
		-.5, -.5, 0
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), triangle, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	const char *vshader =
		"#version 330\n"
		"in vec3 vp;"
		"void main() {"
		"gl_Position = vec4(vp, 1.0);"
		"}";
	const char *fshader =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main() {"
		"frag_colour = vec4(.5, 0.0, 0.0, 1.0);"
		"}";

	shader_program = glCreateProgram();
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vshader, NULL);
	glCompileShader(vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fshader, NULL);
	glCompileShader(fs);

	glAttachShader(shader_program, vs);
	glAttachShader(shader_program, fs);
	glLinkProgram(shader_program);
}

void draw_frame(GLFWwindow *window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shader_program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glfwSwapBuffers(window);
}

int main(void) {
	if (!glfwInit()) {
		fprintf(stderr, "failed glfwInit\n");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "Window", NULL, NULL);
	if (!window) {
		fprintf(stderr, "Failed to create gl window\n");
	}

	glfwMakeContextCurrent(window);
	gladLoadGLES2(glfwGetProcAddress);

	gl_info();
	setup();

	glfwSetKeyCallback(window, key_callback);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		draw_frame(window);
	}
	glfwTerminate();
	return 0;
}
