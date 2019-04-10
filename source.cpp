#define GLEW_STATIC
#include <iostream>
#include <string>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Head.h"
#include "MakeTrueIntAndColor.cpp"
using namespace std;

int res = 0;
// Шейдеры на языке GLSL
// Вершинный шейдер
const GLchar* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
	"layout (location = 1) in vec3 color;\n"
	"out vec3 ourColor;\n"
	"uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "gl_Position = projection * view * model * vec4(position, 1.0f);\n"
	"ourColor = color;\n"
	"}\0";

// Фрагментный шейдер
const GLchar* fragmentShaderSource = "#version 330 core\n"
    "in vec3 ourColor;\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(ourColor, 1.0f);\n"
	"}\n\0";

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	// Когда пользователь нажимает клавишу, мы устанавливаем свойство WindowShouldClose в true
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		// и приложение после этого закроется
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_D) {res = 1;}
	if (key == GLFW_KEY_W) {res = 2;}
	if (key == GLFW_KEY_A) {res = 3;}
	if (key == GLFW_KEY_S) {res = 4;}
}

struct Point3D {
	GLfloat x;
	GLfloat y;
	GLfloat z;
};
int main(){
	//Инициализация GLFW
	glfwInit();
	//Настройка GLFW
	//Задается минимальная требуемая версия OpenGL. 
	//Мажорная 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//Минорная
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Установка профайла для которого создается контекст
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Выключение возможности изменения размера окна
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	string s;
	printf("You can open: TET.txt, OKT.txt, ICOSA.txt , CUBE.txt, DODECA.txt;\n");
	printf("Enter name file: ");
	std:: cin >> s;
	ifstream input(s);

	int Node, leng, count = 0, c = 0;
	input >> Node;
	Point3D *Point = new Point3D[Node], View; //точки и вектор взгляда
	for (int i = 0; i < Node; i++) {
		input >> Point[i].x >> Point[i].y >> Point[i].z;
	}
	input >> View.x >> View.y >> View.z;

	GLuint indices[1000];
	GLfloat colors[1000], vertices[1000];

	//Определяем порядок и цвета отрисовки
	makeTrueIndAndColor(Node, &leng, indices, colors);
	
	for (int i = 0; i < Node * 6; i+=6) {
		vertices[i]   = Point[count].x;
		vertices[i+1] = Point[count].y;
		vertices[i+2] = Point[count].z;
		count++;
		vertices[i+3] = colors[c++];
		vertices[i+4] = colors[c++];
		vertices[i+5] = colors[c++];
	}
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "Figure", nullptr, nullptr);
	if (window == nullptr){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, (GLFWkeyfun)key_callback);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);

	//Инициализация GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// Активация вершинного шейдера
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Проверяем успешность сборки шейдера
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success){
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	
	// Фрагментный шейдер
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	
	// Проверяем успешность сборки шейдера
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success){
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Линковка шейдеров
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	// Проверка удачности линковки
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Создаем буфера для точек
	GLuint VBO, VAO, EBO;
	GLuint colorbuffer;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO); 

	// Приязываем эти буфера:
	// Благодаря этому массиву не придется много раз добавлять точки в буфер
	glBindVertexArray(VAO);
	
	// Массив точек в буфер
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Копируем вершинные данные в буфер
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Устанавливаем указатели на вершинные атрибуты
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	
	// Отвязываем VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// Отвязываем VAO
	glBindVertexArray(0); 
	
	//Функция удаляющая лишние наложения цветов
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		/*формула преобразования координат вершины
		  позволяет 3D координаты преобразовывать в 2D изображение:
		  Vверш = M проекции * M камеры * M модели * V начальные 
		*/
		// Проверяем не были ли нажата какая-то кнопка
		glfwPollEvents();

		// Очистка поля
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Приминяем шейкерную программу
		glUseProgram(shaderProgram);
		
		GLfloat p = 3.14159265359;
		//модельная проекция
		glm::mat4 model;
		if (res == 3) {
			model = glm::rotate(model, (GLfloat)glfwGetTime() * -50.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (res == 2) {
			model = glm::rotate(model, (GLfloat)glfwGetTime() * -50.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (res == 1) {
			model = glm::rotate(model, (GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (res == 4) {
			model = glm::rotate(model, (GLfloat)glfwGetTime() * 50.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		
		//матрица вида
		glm::mat4 view;
		view = glm::lookAt(glm::vec3(View.x, View.y, View.z),
			   glm::vec3(0.0f, 0.0f, 0.0f),
			   glm::vec3(0.0f, 1.0f, 0.0f));

		//матрица перспективной проекции
		glm::mat4 projection;
		projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);
		
		//Подставляем матрицы в шейдер
		GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
		GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
		GLint projLoc = glGetUniformLocation(shaderProgram, "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE,  glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE,  glm::value_ptr(projection));
		
		// Рисуем примитив
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, leng, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	// Удаляем массивы
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	
	glfwTerminate();
	return 0;
}
