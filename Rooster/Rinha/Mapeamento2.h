#pragma once


string keybindToText(struct inputInfo keybind) {
	
	if (keybind.type == 0) {

		//println("Com todo Respeito, ja peço desculpa adiantado");

		string keyNames[101] = {
			  "A", "B", "C",
			  "D", "E", "F", "G",
			  "H", "I", "J", "K",
			  "L", "M", "N", "O",
			  "P", "Q", "R", "S",
			  "T", "U", "V", "W",
			  "X", "Y", "Z", "Num0",
			  "Num1", "Num2", "Num3", "Num4",
			  "Num5", "Num6", "Num7", "Num8",
			  "Num9", "Escape", "LControl", "LShift",
			  "LAlt", "LSystem", "RControl", "RShift",
			  "RAlt", "RSystem", "Menu", "LBracket",
			  "RBracket", "Semicolon", "Comma", "Period",
			  "Quote", "Slash", "Backslash", "Tilde",
			  "Equal", "Hyphen", "Space", "Enter",
			  "Backspace", "Tab", "PageUp", "PageDown",
			  "End", "Home", "Insert", "Delete",
			  "Add", "Subtract", "Multiply", "Divide",
			  "Left", "Right", "Up", "Down",
			  "Numpad0", "Numpad1", "Numpad2", "Numpad3",
			  "Numpad4", "Numpad5", "Numpad6", "Numpad7",
			  "Numpad8", "Numpad9", "F1", "F2",
			  "F3", "F4", "F5", "F6",
			  "F7", "F8", "F9", "F10",
			  "F11", "F12", "F13", "F14",
			  "F15", "Pause"
		};


		//println("Vai se arrombar");


		if (keybind.key >= 0) {
			return keyNames[keybind.key];
		}

		return "Keyboard Unnamed";
	}
	else if (keybind.type == 1) {
		if (keybind.key == sf::Mouse::Button::Left) {
			return "Mouse Left";
		}
		else if (keybind.key == sf::Mouse::Button::Right) {
			return "Mouse Right";
		}
		else if (keybind.key == sf::Mouse::Button::Middle) {
			return "Mouse Middle";
		}
		else if (keybind.key == sf::Mouse::Button::XButton1) {
			return "Mouse XButton1";
		}
		else if (keybind.key == sf::Mouse::Button::XButton2) {
			return "Mouse XButton2";
		}
		return "Mouse Unnamed";
	} else if (keybind.type == 2){
		string joyNames[] = { "JOYUP",
							"JOYRIGHT",
							"JOYDOWN",
							"JOYLEFT",
							"JOYX",
							"JOYY",
							"JOYA",
							"JOYB",
							"JOYL1",
							"JOYR1",
							"JOYL2",
							"JOYR2",
							"JOYSELECT",
							"JOYSTART",
							"JOYMIDLEFT",
							"JOYMIDRIGHT" };
		if (keybind.key < 0 && keybind.key >= 0) {
			return "JOY Unnamed";
		}

		string result = joyNames[keybind.key];
		result += "_";
		result += std::to_string(keybind.deviceId);
		return result;
	}
	
	return "Undefined Device";

}

string inputTypeToText(int input) {

	switch (input) {
	case 0:
		return "Left";
		break;
	case 1:
		return "Right";
		break;
	case 2:
		return "Down";
		break;
	case 3:
		return "Up";
		break;
	case 4:
		return "Light Attack";
		break;
	case 5:
		return "Strong Attack";
		break;
	case 6:
		return "Dance";
		break;
	case 7:
		return "Tiles1";
		break;
	case 8:
		return "Tiles2";
		break;
	case 9:
		return "Tiles3";
		break;
	case 10:
		return "Tiles4";
		break;
	}
}



void loadKeybinds() {
	std::ifstream file("keybinds.txt");

	if (file.is_open()) {
		std::string line;
		std::getline(file, line);
		for (int i = 0; i < 4; i++) {
			std::getline(file, line); // Player 1, 2, 3, 4
			for (int j = 0; j < INPUTSTOTAL; j++) {
				std::getline(file, line); // Input Name: Left, Right, Dance...
				struct inputInfo info;


				std::getline(file, line); // InputInfo: Type
				info.type = std::stoi(line);
			
				std::getline(file, line); // InputInfo: Key
				info.key = std::stoi(line);

				std::getline(file, line); // InputInfo: DeviceId
				info.deviceId = std::stoi(line);

				mainInput.board[i][j][0] = info;
			}
		}

		println("Keybinds loaded");
	}

	file.close();

}

void saveKeybinds() {
	std::ofstream file("keybinds.txt");

	if (file.is_open()) {
		file << "Keybinds" << std::endl;

		for (int i = 0; i < 4; i++) {
			file << "Player " << i << std::endl;
			for (int j = 0; j < INPUTSTOTAL; j++) {
				file << inputTypeToText(j) << std::endl;
				struct inputInfo info = mainInput.board[i][j][0];
				file << info.type << std::endl;
				file << info.key << std::endl;
				file << info.deviceId << std::endl;
			}
		}

		file << "End" << std::endl;

		println("Keybinds saved");
	}
	else {
		println("Falha ao salvar keybinds");
	}

	file.close();
}




void mapeamento(RenderWindow* window) {

		float roomWid = 1280;
		float roomHei = 720;


		sf::View view;
		if (true) {

			Vector2f size = (Vector2f)window->getSize();

			float wid = roomWid;
			float hei = roomHei;
			float xScl = (float)size.x / wid;
			float yScl = (float)size.y / hei;

			if (xScl > yScl) {
				wid *= yScl;
				hei = size.y;
			}
			else {

				hei *= xScl;
				wid = size.x;
			}

			xScl = wid / (float)size.x;
			yScl = hei / (float)size.y;

			sf::FloatRect area(0.f, 0.f, 1280, 720);
			view.setSize(area.width, area.height);
			view.setCenter(area.width / 2, area.height / 2);
			view.setViewport(FloatRect((1 - xScl) / 2, (1 - yScl) / 2, xScl, yScl));
			window->setView(view);
		}




		// Detecta texto para o editor
		int inputType = -1;
		char lastChar = ' ';


		std::vector<struct Button> buttons;

		float butX = roomWid / 4;
		float butY = 100;

		float buttonWid = 180;
		float buttonHei = 40;
		float yOffset = 30;
		float xOffset = 90;

		
		for (int i = 0; i < INPUTSTOTAL; i++) {
			struct Button lAtkBut;

			int xx = i / 4;
			int yy = i % 4;

			lAtkBut.init(butX - (buttonWid-xOffset)/2 +(buttonWid + xOffset) * xx, butY + (buttonHei + yOffset) * yy, buttonWid, buttonHei);
			lAtkBut.color = Color(250, 100, 150);
			buttons.push_back(lAtkBut);
		}

		buttons[GOLEFT].subLabel = "Left";
		buttons[GORIGHT].subLabel = "Right";
		buttons[GOUP].subLabel = "Up";
		buttons[GODOWN].subLabel = "Down";
		buttons[LIGHT_ATTACK].subLabel = "Light Attack";
		buttons[STRONG_ATTACK].subLabel = "Heavy Attack";
		buttons[DANCE].subLabel = "Dance";
		buttons[TILES1].subLabel = "Tiles 1";
		buttons[TILES2].subLabel = "Tiles 2";
		buttons[TILES3].subLabel = "Tiles 3";
		buttons[TILES4].subLabel = "Tiles 4";


		struct DisplayBox playerIndicator;
		playerIndicator.init(roomWid/2, 20, 400, 40);
		playerIndicator.hAlign = 0;
		playerIndicator.textHAlign = 0;
		

		struct DisplayBox fpsDisplay;
		fpsDisplay.init(4, 4, 40, 30);
		fpsDisplay.textHAlign = 0;


		struct Button changePlayerButton;
		changePlayerButton.init(roomWid-200, 20, 200, 40);
		changePlayerButton.color = sf::Color(200, 100, 100);
		changePlayerButton.label = "Next Player";

		struct Button prevButton;
		prevButton.init(0, 20, 200, 40);
		prevButton.color = sf::Color(200, 100, 100);
		prevButton.label = "Prev Player";

		struct Button saveButton;
		saveButton.init(0, roomHei-40, 200, 40);
		saveButton.color = sf::Color(100, 200, 150);
		saveButton.label = "Save Changes";



		// Ghost Projectile
		sf::Texture ghostTex;
		if (!ghostTex.loadFromFile("sprites/botaProjectile.png")) {
			println("Could not load Ghost On Mapeamento2");
		}
	
		
		sf::Sprite ghostSpr(ghostTex);
		SpriteMap ghostSprMap;
		ghostSprMap.addImages(16, 16, 0, 0, 2, 1, (Vector2i)ghostSpr.getTexture()->getSize());
		ghostSpr.setTextureRect(ghostSprMap.images[0]);
		ghostSpr.setScale(5, 5);

		float ghostX = 0;
		float ghostY = 0;
		float ghostBaseY = roomHei / 2;
		float ghostSpd = 10;
		float dir = 1;


		// TEste
		/*
		Texture t;
		t.loadFromFile("sprites/galoSniper.png");

		std::vector<struct Model*> modelTest;
		*/
		



		int buttonSelected = -1;
		bool listeningForKeybind = false;

		int playerSelected = 0;

		

		bool updateLabels = true;



		float frames = 0;

		while (window->isOpen()) {

			frames++;

			inputType = -1;

			mainInput.update();


			Event e;
			while (window->pollEvent(e))
			{
				if (e.type == Event::KeyPressed)
				{
					if (e.key.code == Keyboard::Escape)
					{
						window->setView(window->getDefaultView());


						/*
						for (int i = 0; i < modelTest.size(); i++) {
							
						delete modelTest[i];
						}
						*/

						return;
					}
				}

				if (e.type == Event::MouseMoved) {
					mainInput.mousePos = Vector2f(e.mouseMove.x, e.mouseMove.y);
				}

				if (e.type == Event::MouseWheelScrolled) {
					mainInput.mouseScroll = e.mouseWheelScroll.delta;
				}

				if (e.type == Event::Closed)
				{
					window->close();
				}

				
				if (e.type == sf::Event::Resized)
				{
					float wid = roomWid;
					float hei = roomHei;
					float xScl = (float)e.size.width / wid;
					float yScl = (float)e.size.height / hei;

					if (xScl > yScl) {
						wid *= yScl;
						hei = e.size.height;
					}
					else {

						hei *= xScl;
						wid = e.size.width;
					}

					xScl = wid / (float)e.size.width;
					yScl = hei / (float)e.size.height;

					sf::FloatRect area(0.f, 0.f, roomWid, roomHei);
					view.setSize(area.width, area.height);
					view.setCenter(area.width / 2, area.height / 2);
					view.setViewport(FloatRect((1 - xScl) / 2, (1 - yScl) / 2, xScl, yScl));
					window->setView(view);
				
				}
				
			}



			window->clear();


			fpsDisplay.label = GetFrameRate();
			
			
			if (listeningForKeybind) {

				bool done = false;

				int connectedJoysticks = 1;

				struct inputInfo keyInfo;

				
				for (int j = 0; j < connectedJoysticks; j++) {
					for (int i = 0; i < JOYTOTAL; i++) {
						if (mainInput.joystickState[j][i][1]) {

							keyInfo.type = 2;
							keyInfo.key = i;
							keyInfo.deviceId = j;
							//j = connectedJoysticks;
							//i = JOYTOTAL;
							done = true;
						}
					}
				}

				if (!done) {
					for (int i = 0; i < sf::Mouse::ButtonCount; i++) {
						if (mainInput.mouseState[i][1]) {
							//struct inputInfo input;
							//input.type = 1;
							keyInfo.type = 1;
							keyInfo.key = i;
							//keyInfo.deviceId = j;

							//mainInput.board[0][buttonSelected][0] = input.setKey(i);
							//i = sf::Mouse::ButtonCount;
							done = true;
						}
					}
				}

				if (!done) {
					for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
						if (mainInput.keyboardState[i][1]) {
							//struct inputInfo input;
							//input.type = 0;

							keyInfo.type = 0;
							keyInfo.key = i;
							//keyInfo.deviceId = j;

							//mainInput.board[0][buttonSelected][0] = input.setKey(i);
							//i = sf::Keyboard::KeyCount;
							done = true;
						
						}
					}
				}
				
				
				if (done) {
					mainInput.setKeybind(playerSelected, buttonSelected, 0, keyInfo);
					listeningForKeybind = false;
					buttonSelected = -1;
					updateLabels = true;
				}
				

			}
			
			



			
			Vector2f mouseViewPos = window->mapPixelToCoords((Vector2i)mainInput.mousePos);
			
			for (int i = 0; i < buttons.size(); i++) {
				buttons[i].draw(*window); // Muito lagado, Concertei, era settar a fonte toda hora
				buttons[i].update(mouseViewPos);

				if (buttons[i].clicked) {

					buttonSelected = i;
					listeningForKeybind = true;

					updateLabels = true;
				}
			}
			

			playerIndicator.label = "Player ";
			playerIndicator.label += std::to_string(playerSelected+1);
			playerIndicator.draw(*window);

			changePlayerButton.draw(*window);
			changePlayerButton.update(mouseViewPos);
			if (changePlayerButton.clicked) {
				playerSelected = (playerSelected + 1) % 4;
				updateLabels = true;
			}

			prevButton.draw(*window);
			prevButton.update(mouseViewPos);
			if (prevButton.clicked) {
				playerSelected = playerSelected > 0 ? playerSelected - 1 : 3;
				updateLabels = true;
			}

			saveButton.draw(*window);
			saveButton.update(mouseViewPos);
			if (saveButton.clicked) {
				saveKeybinds();
			}


			if (updateLabels) {

				/*
				for (int i = 0; i < 200; i++) {
					struct Model* model = new Model();


					model->tex = &t;
					model->loadModel("models/SniperModel.txt");
					modelTest.push_back(model);
				}

				println("New Model");
				*/

				for (int i = 0; i < buttons.size(); i++) {
					if (i == buttonSelected) {

						buttons[i].label = "Press a Key";

					}
					else {
						buttons[i].label = keybindToText(mainInput.board[playerSelected][i][0]);
					}
				}
			}




			ghostSpr.setTextureRect(ghostSprMap.images[(int)(frames/10)%2]);
			if (dir > 0) {
				if (ghostX > roomWid * 3) {
					ghostX = roomWid * 3;
					dir = -1;
				}
				ghostX += dir*ghostSpd;
				ghostY = cos(frames / 10.f)*20;
			}
			else {
				if (ghostX < -roomWid * 2) {
					ghostX = -roomWid * 2;
					dir = 1;
				}
				ghostX += dir * ghostSpd;
				ghostY = cos(frames / 10.f) * 20;
			}
			ghostSpr.setPosition(ghostX, ghostY + ghostBaseY);
			
			window->draw(ghostSpr);

			fpsDisplay.draw(*window);

			mainPartSystem.update();
			mainPartSystem.draw(*window);


			window->display();

			updateLabels = false;
		}

		/*
		for (int i = 0; i < modelTest.size(); i++) {
			delete modelTest[i];
		}
		*/
		return;
	
}