
#ifndef  __calvo
#define __calvo

namespace Rooster {

	enum modos {

		UMJOGADORES,
		DOISJODADOR,
		MENU_PRINCIPAL,
		ISPATOTIME,
		SELECTION,
		INTRO,
		BOTAPRAARROCHAR,
		MAPA_FALIDO_E_ACHE_RUIM_WALTER,
		MULTI_SELECT,
		JOIN,
		CREATE,
		GAMEMODE,
		MINIGAME,
		MULTI_MODE,
		CONFIG,
		MULTI,
		VERSUS,
		SELECTION_SINGLE_FALIDA
	};

	enum JoystickKeys {
		JOYUP,
		JOYRIGHT,
		JOYDOWN,
		JOYLEFT,
		JOYX,
		JOYY,
		JOYA,
		JOYB,
		JOYL1,
		JOYR1,
		JOYL2,
		JOYR2,
		JOYSELECT,
		JOYSTART,
		JOYMIDLEFT,
		JOYMIDRIGHT,
		JOYTOTAL
	};

	enum inputs {
		GOLEFT,
		GORIGHT,
		GODOWN,
		GOUP,
		LIGHT_ATTACK,
		STRONG_ATTACK,
		DANCE,
		TILES1,
		TILES2,
		TILES3,
		TILES4,
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
		int p2Hud = 0;

		// Rapaz me explique o que é isso porfavor
		// Ahh to entendendo
	
		bool keyboardState[sf::Keyboard::KeyCount][3];
		bool mouseState[sf::Mouse::ButtonCount][3];
		float mouseScroll = 0;

		Vector2f mousePos;

		bool isJoystickConnected = false;
		bool joystickState[JOYTOTAL][3];

		struct inputInfo board[2][INPUTSTOTAL][HUDTOTAL];

		bool inputState[2][INPUTSTOTAL][HUDTOTAL];

		input() {

			Joystick::update();

			if (Joystick::isConnected(0)) {
				p2Hud = 2;
				println("olha esta conectado :)");
			}
			else {
				println("nao esta conectado :(");
			}

			mousePos = Vector2f(0, 0);

			if (p1Hud == 1 && p2Hud == 1) {
				p2Hud = 0;
			}



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
			board[player][GOLEFT][KEYBOARD] = kInput.setKey(Keyboard::A);
			board[player][GODOWN][KEYBOARD] = kInput.setKey(Keyboard::S);
			board[player][GORIGHT][KEYBOARD] = kInput.setKey(Keyboard::D);
			board[player][GOUP][KEYBOARD] = kInput.setKey(Keyboard::W);
			board[player][LIGHT_ATTACK][KEYBOARD] = kInput.setKey(Keyboard::F);
			board[player][STRONG_ATTACK][KEYBOARD] = kInput.setKey(Keyboard::G);
			board[player][DANCE][KEYBOARD] = kInput.setKey(Keyboard::Q);

			board[player][TILES1][KEYBOARD] = kInput.setKey(Keyboard::A);
			board[player][TILES2][KEYBOARD] = kInput.setKey(Keyboard::S);
			board[player][TILES3][KEYBOARD] = kInput.setKey(Keyboard::D);
			board[player][TILES4][KEYBOARD] = kInput.setKey(Keyboard::F);


			// Keyboard
			board[player][GOLEFT][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::A);
			board[player][GODOWN][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::S);
			board[player][GORIGHT][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::D);
			board[player][GOUP][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::W);
			board[player][DANCE][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::Q);

			board[player][TILES1][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::A);
			board[player][TILES2][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::S);
			board[player][TILES3][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::D);
			board[player][TILES4][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::F);

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
			board[player][DANCE][JOYSTICK] = jInput.setKey(JOYX);

			board[player][TILES1][JOYSTICK] = jInput.setKey(JOYB);
			board[player][TILES2][JOYSTICK] = jInput.setKey(JOYL1);
			board[player][TILES3][JOYSTICK] = jInput.setKey(JOYR1);
			board[player][TILES4][JOYSTICK] = jInput.setKey(JOYY);



			player++;
			//Keyboard

			board[player][GOLEFT][KEYBOARD] = kInput.setKey(Keyboard::Left);
			board[player][GODOWN][KEYBOARD] = kInput.setKey(Keyboard::Down);
			board[player][GORIGHT][KEYBOARD] = kInput.setKey(Keyboard::Right);
			board[player][GOUP][KEYBOARD] = kInput.setKey(Keyboard::Up);
			board[player][LIGHT_ATTACK][KEYBOARD] = kInput.setKey(Keyboard::K);
			board[player][STRONG_ATTACK][KEYBOARD] = kInput.setKey(Keyboard::L);
			board[player][DANCE][KEYBOARD] = kInput.setKey(Keyboard::P);

			board[player][TILES1][KEYBOARD] = kInput.setKey(Keyboard::V);
			board[player][TILES2][KEYBOARD] = kInput.setKey(Keyboard::B);
			board[player][TILES3][KEYBOARD] = kInput.setKey(Keyboard::N);
			board[player][TILES4][KEYBOARD] = kInput.setKey(Keyboard::M);


			// Keyboard
			board[player][GOLEFT][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::Left);
			board[player][GODOWN][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::Down);
			board[player][GORIGHT][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::Right);
			board[player][GOUP][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::Up);
			board[player][DANCE][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::P);

			board[player][TILES1][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::V);
			board[player][TILES2][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::B);
			board[player][TILES3][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::N);
			board[player][TILES4][MOUSE_AND_KEYBOARD] = kInput.setKey(Keyboard::M);

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
			board[player][DANCE][JOYSTICK] = jInput.setKey(JOYX);

			board[player][TILES1][JOYSTICK] = jInput.setKey(JOYA);
			board[player][TILES2][JOYSTICK] = jInput.setKey(JOYX);
			board[player][TILES3][JOYSTICK] = jInput.setKey(JOYY);
			board[player][TILES4][JOYSTICK] = jInput.setKey(JOYB);

		}


		void setKeybind(int player, int inputSlot, int actualHud, struct inputInfo keybindInfo) {
			board[player][inputSlot][actualHud] = keybindInfo;
		}

		bool getJoystickState(int button, int joystickId = 0) {


			if (!sf::Joystick::isConnected(joystickId)) {
				return false;
			}

			float val = 0;

			switch (button) {
			case JOYDOWN:
				return sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Y) > 50;
			case JOYUP:
				return sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Y) < -50;
			case JOYLEFT:
				return sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X) < -50;
			case JOYRIGHT:
				return sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X) > 50;
			case JOYX:
				return sf::Joystick::isButtonPressed(joystickId, 0);

			case JOYY:
				return sf::Joystick::isButtonPressed(joystickId, 1);

			case JOYA:
				return sf::Joystick::isButtonPressed(joystickId, 2);

			case JOYB:
				return sf::Joystick::isButtonPressed(joystickId, 3);
			case JOYL1:
				return sf::Joystick::isButtonPressed(joystickId, 4);

			case JOYL2:
				return sf::Joystick::isButtonPressed(joystickId, 6);

			case JOYR1:
				return sf::Joystick::isButtonPressed(joystickId, 5);

			case JOYR2:
				return sf::Joystick::isButtonPressed(joystickId, 7);

			case JOYSTART:
				return sf::Joystick::isButtonPressed(joystickId, 9);

			case JOYSELECT:
				return sf::Joystick::isButtonPressed(joystickId, 8);

			case JOYMIDLEFT:
				return sf::Joystick::isButtonPressed(joystickId, 10);

			case JOYMIDRIGHT:
				return sf::Joystick::isButtonPressed(joystickId, 11);


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

			mouseScroll = 0;

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

#endif // ! __calvo
