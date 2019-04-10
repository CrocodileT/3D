#include "Head.h"

void makeGLint(GLuint *a, GLuint *b, GLuint g) {
	for (int i = 0; i < g; i++) {
		a[i] = b[i];
	}
}
void makeGLfloat(GLfloat *a, GLfloat *b, GLuint g) {
	for (int i = 0; i < g; i++) {
		a[i] = b[i];
	}
}
//В зависимости от фигуры будут различные цвета и последовательности отрисовки вершин(массив индексов)
//Эта функция обрабатывает 5 правильных фигур и создает последовательность отрисовки
void makeTrueIndAndColor(int Node, int *leng, GLuint* indices, GLfloat* colors) {
	if (Node == 4) {// набор индексов и цветов дл¤ правильных фигур
		*leng = 4 * 3;
		GLuint ind[] = {
			0, 1, 2,
			0, 1, 3,
			0, 2, 3,
			2, 3, 1,
		};
		GLfloat Color[] = {
			0.0f,  0.0f,  0.0f,
			1.0f,  0.0f,  0.0f,
			0.0f,  1.0f,  0.0f,
			0.0f,  0.0f,  1.0f,
		};
		makeGLint(indices, ind, *leng);
		makeGLfloat(colors, Color, Node * 3);
	}
	if (Node == 6) {
		*leng = 8 * 3;
		GLuint ind[] = {
			0, 1, 2,
			0, 1, 5,
			0, 2, 4,
			0, 5, 4,
			3, 1, 2,
			3, 1, 5,
			3, 2, 4,
			3, 5, 4,
		};
		GLfloat Color[] = {
			0.0f,  0.0f,  0.0f,
			1.0f,  0.0f,  0.0f,
			0.0f,  1.0f,  0.0f,
			0.0f,  0.0f,  1.0f,
			0.0f,  1.0f,  1.0f,
			1.0f,  0.0f,  1.0f,
		};
		makeGLint(indices, ind, *leng);
		makeGLfloat(colors, Color, Node * 3);
	}
	if (Node == 8) {
		*leng = 6 * 6;
		GLuint ind[] = {
			0, 1, 2,
			2, 3, 0,
			0, 1, 5,
			5, 4, 0,
			4, 5, 6,
			6, 7, 4,
			2, 3, 6,
			6, 7, 3,
			1, 2, 5,
			5, 6, 2,
			7, 4, 0,
			0, 3, 7,
		};
		GLfloat Color[] = {
			0.0,  0.0,  0.0,
			1.0,  0.0,  0.0,
			0.0,  1.0,  0.0,
			0.0,  0.0,  1.0,
			1.0,  1.0,  0.0,
			0.0,  1.0,  1.0,
			1.0,  0.0,  0.1,
			1.0,  1.0,  1.0,
		};

		makeGLint(indices, ind, *leng);
		makeGLfloat(colors, Color, Node * 3);
	}
	if (Node == 12) {
		*leng = 20 * 3;
		GLuint ind[] = {
			9, 2, 6,
			1, 5, 11,
			11, 1, 8,
			0, 11, 4,
			3, 7, 1,
			3, 1, 8,
			9, 3, 7,
			0, 2, 6,
			4, 6, 10,
			1, 7, 5,
			7, 2, 5,
			8, 10, 3,
			4, 11, 8,
			9, 2, 7,
			10, 6, 9,
			0, 11, 5,
			0, 2, 5,
			8, 10, 4,
			3, 9, 10,
			6, 4, 0, };
		GLfloat Color[] = {
			0.0,  0.0,  0.0,
			1.0,  0.0,  0.0,
			0.0,  1.0,  0.0,
			0.0,  0.0,  1.0,
			1.0,  1.0,  0.0,
			0.0,  1.0,  1.0,
			1.0,  0.0,  0.1,
			1.0,  1.0,  1.0,
			0.359f,  0.583f,  0.152f,
			0.483f,  0.596f,  0.789f,
			0.559f,  0.861f,  0.639f,
			0.0f,  0.0f,  0.0f,
		};
		makeGLint(indices, ind, *leng);
		makeGLfloat(colors, Color, Node * 3);
	}
	if (Node == 20) {
		*leng = 12 * 9;
		GLuint ind[] = {
			9, 13, 7,
			7, 1, 15,
			9, 7, 15,
			6, 4, 14,
			14, 19, 8,
			6, 14, 8,
			12, 5, 13,
			13, 9, 2,
			12, 13, 2,
			6, 2, 12,
			12, 17, 4 ,
			6, 12, 4,
			16, 10, 11,
			11, 18, 3 ,
			16, 11, 3,
			19, 8, 15,
			15, 1, 0,
			19, 15, 0,
			16, 7, 1,
			1, 0, 3,
			16, 1, 3,
			5, 12, 17,
			17, 11, 10,
			5, 17, 10,
			18, 14, 4,
			4, 17, 11,
			18, 4, 11,
			16, 10, 5,
			5, 13, 7,
			16, 5, 7,
			2, 6, 8,
			8, 15, 9,
			2, 8, 9,
			19, 0, 3,
			3, 18, 14,
			19, 3, 14,
		};
		GLfloat Color[] = {
			0.0,  0.0,  0.0,
			1.0,  0.0,  0.0,
			0.0,  1.0,  0.0,
			0.0,  0.0,  1.0,
			1.0,  1.0,  0.0,
			0.0,  1.0,  1.0,
			1.0,  0.0,  0.1,
			1.0,  1.0,  1.0,
			0.359f,  0.583f,  0.152f,
			0.483f,  0.596f,  0.789f,
			0.559f,  0.861f,  0.639f,
			0.195f,  0.548f,  0.859f,
			0.014f,  0.184f,  0.576f,
			0.771f,  0.328f,  0.970f,
			0.406f,  0.615f,  0.116f,
			0.676f,  0.977f,  0.133f,
			0.971f,  0.572f,  0.833f,
			0.140f,  0.616f,  0.489f,
			0.055f,  0.953f,  0.042f,
			0.0f,  0.0f,  0.0f,
		};
		makeGLint(indices, ind, *leng);
		makeGLfloat(colors, Color, Node * 3);
	}
}