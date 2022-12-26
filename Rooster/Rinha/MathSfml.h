
#ifndef TBRB_MATH_SFML
#define TBRB_MATH_SFML



float pitagoras(Vector2f Catetos) {
	return pitagoras(Catetos.x, Catetos.y);
}
float pointDistance(Vector2f point1, Vector2f point2) {
	return pitagoras(point1 - point2);

}

void drawFibonacci(int a, RenderWindow* window) {
	CircleShape b(a);
	b.setFillColor(Color::Blue);
	b.setOutlineThickness(10);
	b.setTextureRect(IntRect(0, 0, a, a));
	b.setPosition(200, 200);

	window->draw(b);

	if (a < 10)
		drawFibonacci(a + (a - 1), window);
	else
		return;
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



// Função pra transformar retangulo em convexShape

ConvexShape rectToConvexShape(RectangleShape rect) {
	ConvexShape newShape(4);

	for (int i = 0; i < 4; i++) {
		Vector2f point(rect.getPoint(i).x + rect.getPosition().x, rect.getPoint(i).y + rect.getPosition().y);
		newShape.setPoint(i, point);
	}

	return newShape;
}

ConvexShape rectToConvexShape(float x, float y, float wid, float hei) {
	ConvexShape newShape(4);

	newShape.setPoint(0, Vector2f(x, y));
	newShape.setPoint(1, Vector2f(x + wid, y));
	newShape.setPoint(2, Vector2f(x + wid, y + hei));
	newShape.setPoint(3, Vector2f(x, y + hei));

	return newShape;
}

ConvexShape rectToConvexShape(float wid, float hei) {
	return rectToConvexShape(-wid / 2, -hei / 2, wid, hei);
}



// Bends points of a rectangular area to match a triangular area
// Top points bend inwards more than bottom points
Vector2f convertPointToTrap(Vector2f point, float base, float topBase, float height) {
	float x = point.x;

	if (base - topBase != 0) {
		float hSmall = topBase * height / (base - topBase);


		x = (hSmall + point.y) * (point.x / (hSmall + height));
	}

	return Vector2f(x, point.y);
}

// Converts an entire Convex shape with triangular transformation
ConvexShape convertShapeToTrap(ConvexShape& shape, float base, float topBase, float height) {

	ConvexShape newShape;
	newShape.setPointCount(shape.getPointCount());


	for (int i = 0; i < shape.getPointCount(); i++) {
		Vertex p = shape.getPoint(i);
		Vector2f point = p.position;

		//point = noteYPerspective(point, baseMenor);

		point = convertPointToTrap(point, base, topBase, height);

		newShape.setPoint(i, point);
	}

	return newShape;
}




#endif TBRB_MATH_SFML



