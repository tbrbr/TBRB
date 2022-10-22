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



// Maximo Minimo e Constrain que e os dois juntos
float maximum(float val, float max) {
	if (val > max) {
		return max;
	}
	return val;
}

float minimum(float val, float min) {
	if (val < min) {
		return min;
	}
	return val;
}


float constrain(float val, float min, float max) {
	return maximum(minimum(val, max), min);
}




//float randFloat(float max) {
	
//}






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



#endif // !JUNIOTELES