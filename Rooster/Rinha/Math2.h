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
float maximum(float val, float val2) {
	if (val > val2) {
		return val;
	}
	return val2;
}

float minimum(float val, float val2) {
	if (val < val2) {
		return val;
	}
	return val2;
}


float constrain(float val, float min, float max) {
	return maximum(minimum(val, max), min);
}


float ruleOfThree(float val, float valMin, float valMax, float outMin, float outMax) {
	float perc = (val - valMin) / (valMax - valMin);
	return outMin + (outMax - outMin) * perc;
}
float ruleOfThree(float val, float valMax, float val2Max) {
	return (val / valMax) * val2Max;
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



bool pointInside(Vector2f point, float x, float y, float wid, float hei) {
	return (point.x > x && point.x < x + wid && point.y > y && point.y < y + hei);
}

bool pointInside(Vector2f point, FloatRect rect) {
	return pointInside(point, rect.left, rect.top, rect.width, rect.height);
}


/*
void printIntVec(std::vector<int> vec) {
	std::cout << "[ ";
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i];
		if (i == vec.size() - 1) {
			std::cout << " ]";

		}
		else {
			std::cout << ", ";
		}
	}
}

std::string streamIntVec(std::vector<int> vec) {
	std::stringstream a;
	a << "[ ";
	for (int i = 0; i < vec.size(); i++) {
		a << vec[i];
		if (i == vec.size() - 1) {


		}
		else {
			a << ", ";
		}
	}
	a << " ]";

	return a.str();
}
*/




#endif // !JUNIOTELES