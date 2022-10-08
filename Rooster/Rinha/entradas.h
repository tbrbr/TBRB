
namespace Rooster {


	enum modos {

		UMJOGADORES,
		DOISJODADOR
	};

	enum inputs {
		GOLEFT,
		GORIGHT,
		GODOWN,
		GOUP,
		LIGHT_ATTACK,
		STRONG_ATTACK
	};

	enum hud {
		KEYBOARD,
		MOUSE_AND_KEYBOARD,
		JOYSTICK
	};

	class input {

	public:
		hud hudselected;
		//because i can´t get the Key enum in made a matrix containing the keys
		int board[3][6] = { {0,3,18,22,9,10},
							{0,3,18,22,0,1},
							{0,0,0,0,0,0} };// i don´t know how to implement joystick

		hud gethudslected() {
			return hudselected;
		}
		void sethudselected(hud selection) {
			hudselected = selection;
		}
	};

};

