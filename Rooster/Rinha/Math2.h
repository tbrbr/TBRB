#include <math.h>

#define Gravity 9.81
#define PI 3.1415926563
#define EULER 2.71828


float pitagoras(float cateto1, float cateto2) {
	return sqrt(pow(cateto1, 2) + pow(cateto2, 2));
}

float pitagoras(Vector2f Catetos) {
	return pitagoras(Catetos.x, Catetos.y);
}
float pointDistance(Vector2f point1, Vector2f point2){
	return pitagoras(point1 - point2);

}