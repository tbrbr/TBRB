#ifndef  CHECK
#define CHECK


#include "Math2.h"

class ButtonCheck {

public:
    static int hasBarInMouseX(RectangleShape rec, int mousex, int size) {
        for (int i = 0; i < size; i++) {
            if (mousex >= rec.getPosition().x && mousex <= rec.getSize().x + rec.getPosition().x) {
                return i;
            }
        }
        return -1;
    }

    static inline bool isButtonComMouseNele(RectangleShape rec, int mousex, int mousey) {
        return mousex >= rec.getPosition().x && mousex <= rec.getSize().x + rec.getPosition().x
            && mousey >= rec.getPosition().y - 3 && mousey <= rec.getSize().y + rec.getPosition().y + 2;

    }

    static int checkButtonHover(RectangleShape* rec, int mousex, int mousey, int i, int __finalCondition) {
        if (mousey == -1) {
            if (hasBarInMouseX(rec[i], mousex, i + 1)) {
                return i;
            }
            else {
                return i == __finalCondition ? -1 : hasBarInMouseX(rec[i], mousex, i + 1);
            }
        }
        if (isButtonComMouseNele(rec[i], mousex, mousey)) {
            return i;
        }
        return i == __finalCondition ? -1 : checkButtonHover(rec, mousex, mousey, i + 1, __finalCondition);
    }

    static bool checkCircleHover(CircleShape circle, int mousex, int mousey) {
       return pointDistance(Vector2f(mousex, mousey), Vector2f(  circle.getPosition().x + circle.getRadius(),  circle.getPosition().y + circle.getRadius())) < circle.getRadius();
 
    }
};

#endif // ! CHECK