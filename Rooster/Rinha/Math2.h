#ifndef JUNIOTELES
#define JUNIOTELES

#include <math.h>

#define Gravity 9.81
const long double PI  = 3.141592653589793;
#define EULER 2.71828



// Retorna o sinal de um numero
int sign(float val) {
	if (val > 0) {
		return 1;
	}
	else if (val < 0) {
		return -1;
	}
	return 0;
}
//minimo
float MIN(float x, float y) {
	return x > y ? y : x;
}
float MAX(float x, float y) {
	return x > y ? x : y;
}
void drawFibonacci(int a,RenderWindow * window) {
	CircleShape b(a);
	b.setFillColor(Color::Blue);
	b.setOutlineThickness(10);
	b.setTextureRect(IntRect(0, 0, a, a));
	b.setPosition(200, 200);

	window->draw(b);

	if(a < 10)
		drawFibonacci(a + (a - 1), window);
	else
		return;
}


// Maximo Minimo e Constrain que e os dois juntos
float maximum(float val, float max) {
	if (val > max) {
		return val;
	}
	return max;
}

float minimum(float val, float min) {
	if (val < min) {
		return val;
	}
	return min;
}


float constrain(float val, float min, float max) {
	return maximum(minimum(val, max), min);
}



// Random
int randInt(int max) {
	return rand() % max;
}

int randIntRange(int min, int max) {
	return min + randInt(max-min);
}

float randFloat(float max) {	
	return max * rand() / (RAND_MAX + 1.);
}

float randFloatRange(float min, float max) {
	return min + randFloat(max - min);
}

float randFloatRangeNormal(float min, float max, float desvio) {

	static std::default_random_engine generator;
	std::normal_distribution<double> distribution((max-min) / 2, desvio);

	return min + distribution(generator);

}







float pitagoras(float cateto1, float cateto2) {
	return sqrt(pow(cateto1, 2) + pow(cateto2, 2));
}

float pitagoras(Vector2f Catetos) {
	return pitagoras(Catetos.x, Catetos.y);
}
float pointDistance(Vector2f point1, Vector2f point2){
	return pitagoras(point1 - point2);

}
float toRadiAnus(int angle) {
	return (angle * PI) / 180;
}





Vector2f normalizar(Vector2f vec) {
	float dist = pitagoras(vec);

	if (dist == 0) {
		return Vector2f(0, 0);
	}

	return Vector2f(vec.x / dist, vec.y / dist);

}

float vecToAngle(Vector2f vec) {
	return atan2(vec.x, vec.y);
}




#endif // !JUNIOTELES