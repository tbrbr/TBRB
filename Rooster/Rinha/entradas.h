
#ifndef  __entradas
#define __entradas


namespace Rooster {


	enum modos {

		UMJOGADORES,
		DOISJODADOR,
		MENU_PRINCIPAL,
		ISPATOTIME,
		SELECTION,
		INTRO,
		BOTAPRAARROCHAR
	};

	enum JoystickKeys {
		JOYUP,
		JOYRIGHT,
		JOYDOWN,
		JOYLEFT,
		JOYA,
		JOYB,
		JOYTOTAL
	};

	enum inputs {
		GOLEFT,
		GORIGHT,
		GODOWN,
		GOUP,
		LIGHT_ATTACK,
		STRONG_ATTACK,
		INPUTSTOTAL
	};

	enum hud {
		KEYBOARD,
		MOUSE_AND_KEYBOARD,
		JOYSTICK,
		HUDTOTAL
	};

	struct inputInfo {
		// 0 Keyboard 1 Mouse 2 Joystick
		int type = 0;
		int key = 0;

		struct inputInfo setKey(int key) {
			this->key = key;
			return *this;
		}
	};


	class input {

	public:
		hud hudselected;

		int p1Hud = 0;
		int p2Hud = 1;

		// Rapaz me explique o que é isso porfavor
		// Ahh to entendendo
		//because i can´t get the Key enum in made a matrix containing the keys
		/*
		int board[3][6] = { {0,3,18,22,9,10},
							{0,3,18,22,0,1},
							{0,0,0,0,0,0} };// i don´t know how to implement joystick
			*/


		bool keyboardState[sf::Keyboard::KeyCount][3];
		bool mouseState[sf::Mouse::ButtonCount][3];

		bool isJoystickConnected = false;
		bool joystickState[JOYTOTAL][3];

		struct inputInfo board[2][INPUTSTOTAL][HUDTOTAL];

		bool inputState[2][INPUTSTOTAL][HUDTOTAL];

		input() {


			for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
				keyboardState[i][0] = false;
				keyboardState[i][1] = false;
				keyboardState[i][2] = false;
			}

			for (int i = 0; i < sf::Mouse::ButtonCount; i++) {
				mouseState[i][0] = false;
				mouseState[i][1] = false;
				mouseState[i][2] = false;
			}

			for (int i = 0; i < JOYTOTAL; i++) {
				joystickState[i][0] = false;
				joystickState[i][1] = false;
				joystickState[i][2] = false;
			}

			
			for (int i = 0; i < 2; i++) {
				struct inputInfo inpInf;
				for (int j = 0; j < INPUTSTOTAL; j++) {
					for (int k = 0; k < HUDTOTAL; k++) {
						board[i][j][k] = inpInf;
						inputState[i][j][k] = false;
					}
				}
			}





			struct inputInfo mInput;
			struct inputInfo kInput;
			struct inputInfo jInput;

			kInput.type = 0;
			mInput.type = 1;
			jInput.type = 2;


			int player = 0;
			// Keyboard
			board[player][GOLEFT][KEYBOARD]        = kInput.setKey(Keyboard::A);
			board[player][GODOWN][KEYBOARD]        = kInput.setKey(Keyboard::S);
			board[player][GORIGHT][KEYBOARD]       = kInput.setKey(Keyboard::D);
			board[player][GOUP][KEYBOARD]          = kInput.setKey(Keyboard::W);
			board[player][LIGHT_ATTACK][KEYBOARD]  = kInput.setKey(Keyboard::F);
			board[player][STRONG_ATTACK][KEYBOARD] = kInput.setKey(Keyboard::G);


			// Keyboard
			board[player][GOLEFT][MOUSE_AND_KEYBOARD]  = kInput.setKey(Keyboard::A);
			board[player][GODOWN][MOUSE_AND_KEYBOARD]  = kInput.setKey(Keyboard::S);
			board[player][GORIGHT][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::D);
			board[player][GOUP][MOUSE_AND_KEYBOARD]    = kInput.setKey(Keyboard::W);
			// Mouse
			board[player][LIGHT_ATTACK][MOUSE_AND_KEYBOARD]  = mInput.setKey(Mouse::Button::Left);
			board[player][STRONG_ATTACK][MOUSE_AND_KEYBOARD] = mInput.setKey(Mouse::Button::Right);


			// Joystick
			board[player][GOLEFT][JOYSTICK] = jInput.setKey(JOYLEFT);
			board[player][GODOWN][JOYSTICK] = jInput.setKey(JOYDOWN);
			board[player][GORIGHT][JOYSTICK] = jInput.setKey(JOYRIGHT);
			board[player][GOUP][JOYSTICK] = jInput.setKey(JOYUP);
			board[player][LIGHT_ATTACK][JOYSTICK] = jInput.setKey(JOYA);
			board[player][STRONG_ATTACK][JOYSTICK] = jInput.setKey(JOYB);



			player++;
			//Keyboard

			board[player][GOLEFT][KEYBOARD] = kInput.setKey(Keyboard::Left);
			board[player][GODOWN][KEYBOARD] = kInput.setKey(Keyboard::Down);
			board[player][GORIGHT][KEYBOARD] = kInput.setKey(Keyboard::Right);
			board[player][GOUP][KEYBOARD] = kInput.setKey(Keyboard::Up);
			board[player][LIGHT_ATTACK][KEYBOARD] = kInput.setKey(Keyboard::K);
			board[player][STRONG_ATTACK][KEYBOARD] = kInput.setKey(Keyboard::L);


			// Keyboard
			board[player][GOLEFT][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::Left);
			board[player][GODOWN][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::Down);
			board[player][GORIGHT][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::Right);
			board[player][GOUP][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::Up);
			// Mouse
			board[player][LIGHT_ATTACK][MOUSE_AND_KEYBOARD] = mInput.setKey(Mouse::Button::Left);
			board[player][STRONG_ATTACK][MOUSE_AND_KEYBOARD] = mInput.setKey(Mouse::Button::Right);


			// Joystick
			board[player][GOLEFT][JOYSTICK] = jInput.setKey(JOYLEFT);
			board[player][GODOWN][JOYSTICK] = jInput.setKey(JOYDOWN);
			board[player][GORIGHT][JOYSTICK] = jInput.setKey(JOYRIGHT);
			board[player][GOUP][JOYSTICK] = jInput.setKey(JOYUP);
			board[player][LIGHT_ATTACK][JOYSTICK] = jInput.setKey(JOYA);
			board[player][STRONG_ATTACK][JOYSTICK] = jInput.setKey(JOYB);
		}

		bool getJoystickState(int button, int joystickId = 0) {


			if (!sf::Joystick::isConnected(joystickId)) {
				return false;
			}


			float val = 0;

			switch (button) {
			case JOYDOWN:
				val = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Y);
				if (val > 50) {
					return true;
				}
				return false;

			case JOYUP:
				val = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Y);
				if (val < -50) {
					return true;
				}
				return false;


			case JOYLEFT:
				val = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X);
				if (val < -50) {
					return true;
				}
				return false;

			case JOYRIGHT:
				val = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X);
				if (val > 50) {
					return true;
				}
				return false;


			case JOYA:
				return sf::Joystick::isButtonPressed(joystickId, 2);

			case JOYB:
				return sf::Joystick::isButtonPressed(joystickId, 3);

			}
			return false;
		}

		bool getInputState(struct inputInfo inputSpecs, int stateType) {
			switch (inputSpecs.type) {
			case 0:
				return keyboardState[inputSpecs.key][stateType];

			case 1:
				return mouseState[inputSpecs.key][stateType];

			case 2:
				return joystickState[inputSpecs.key][stateType];
			}
			return false;
		}

	
		void update() {

			for (int i = 0; i < sf::Keyboard::KeyCount; i++) {

				bool keyState = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i);

				if (!keyboardState[i][0] && keyState) {
					keyboardState[i][1] = true;
				}
				else {
					keyboardState[i][1] = false;
				}

				if (keyboardState[i][0] && !keyState) {
					keyboardState[i][2] = true;
				}
				else {
					keyboardState[i][2] = false;
				}

				keyboardState[i][0] = keyState;

			}

			for (int i = 0; i < sf::Mouse::ButtonCount; i++) {

				bool buttonState = sf::Mouse::isButtonPressed((sf::Mouse::Button)i);

				if (!mouseState[i][0] && buttonState) {
					mouseState[i][1] = true;
				}
				else {
					mouseState[i][1] = false;
				}

				if (mouseState[i][0] && !buttonState) {
					mouseState[i][2] = true;
				}
				else {
					mouseState[i][2] = false;
				}

				mouseState[i][0] = buttonState;

			}

			for (int i = 0; i < JOYTOTAL; i++) {

				bool buttonState = getJoystickState(i, 0);

				if (!joystickState[i][0] && buttonState) {
					joystickState[i][1] = true;
				}
				else {
					joystickState[i][1] = false;
				}

				if (joystickState[i][0] && !buttonState) {
					joystickState[i][2] = true;
				}
				else {
					joystickState[i][2] = false;
				}

				joystickState[i][0] = buttonState;

			}





			for (int i = 0; i < INPUTSTOTAL; i++) {
				inputState[0][i][0] = getInputState(board[0][i][p1Hud], 0);
				inputState[0][i][1] = getInputState(board[0][i][p1Hud], 1);
				inputState[0][i][2] = getInputState(board[0][i][p1Hud], 2);

				inputState[1][i][0] = getInputState(board[1][i][p2Hud], 0);
				inputState[1][i][1] = getInputState(board[1][i][p2Hud], 1);
				inputState[1][i][2] = getInputState(board[1][i][p2Hud], 2);
			}


		}

		hud gethudslected() {
			return hudselected;
		}
		void sethudselected(hud selection) {
			hudselected = selection;
		}
	};

};

#endif // ! __entradas
