
struct TilesMusica {
	std::string soundPath;
	std::string notasPath;

	std::string name;

	sf::Sprite sprite;


};

// Variavel global com as informações das musicas
std::vector<struct TilesMusica> tilesMusicas;

void initTilesMusica() {
	struct TilesMusica musLindinho;
	musLindinho.soundPath = "PianoFiles/sounds/teclado lindinho.ogg";
	musLindinho.notasPath = "PianoFiles/tecladoLindinho.txt";
	musLindinho.name = "Teclado Lindinho";

	tilesMusicas.push_back(musLindinho);

	struct TilesMusica musMorango;
	musMorango.soundPath = "PianoFiles/sounds/morango.ogg";
	musMorango.notasPath = "PianoFiles/morango.txt";
	musMorango.name = "Morango";

	tilesMusicas.push_back(musMorango);

	struct TilesMusica musZe;
	musZe.soundPath = "PianoFiles/sounds/zerebolabola.ogg";
	musZe.notasPath = "PianoFiles/ze.txt";
	musZe.name = "Ze";

	tilesMusicas.push_back(musZe);

	struct TilesMusica musEscoces;
	musEscoces.soundPath = "PianoFiles/sounds/escoces.ogg";
	musEscoces.notasPath = "PianoFiles/mama.txt";
	musEscoces.name = "Escoces";

	tilesMusicas.push_back(musEscoces);

	struct TilesMusica musLatitude;
	musLatitude.soundPath = "PianoFiles/sounds/latitude.ogg";
	musLatitude.notasPath = "PianoFiles/latitude.txt";
	musLatitude.name = "Latitude";

	tilesMusicas.push_back(musLatitude);

	struct TilesMusica musPop100;
	musPop100.soundPath = "PianoFiles/sounds/napop.ogg";
	musPop100.notasPath = "PianoFiles/napop.txt";
	musPop100.name = "Pop 100";

	tilesMusicas.push_back(musPop100);

	struct TilesMusica musPopozuda;
	musPopozuda.soundPath = "PianoFiles/sounds/zepopozuda.ogg";
	musPopozuda.notasPath = "PianoFiles/popozuda.txt";
	musPopozuda.name = "Popozuda";

	tilesMusicas.push_back(musPopozuda);
}


// Função pra transformar retangulo em convexShape
ConvexShape rectToConvexShape(RectangleShape rect) {
	ConvexShape newShape(4);

	for (int i = 0; i < 4; i++) {
		newShape.setPoint(i, rect.getPoint(i));
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






class Nota {
public:
	int coluna = -1;
	float length = 1;
	float y = -1;

	int id = -1;

	float slided = 0;

	bool hitted = false;
	bool missed = false;
	bool holded = false;

	bool hovered = false;

	bool loose = false;


	int hoverQuality = 0;

	Nota() {
		coluna = -1;
		length = 0;
		y = 0;
		id = -1;
	}

	Nota(int c, float l, float yy, int id) {
		coluna = c;
		length = l;
		y = yy;
		this->id = id;
	}

	void resetState() {
		slided = 0;
		hitted = false;
		missed = false;
		holded = false;
		hovered = false;
		loose = false;
	}

	void update(float scrollY) {
		hovered = false;
		hoverQuality = 0;

		float yy = y + scrollY;
		if (yy < 0 && yy + length > 0) {
			hovered = true;

			if (yy + length - 1 < 0) {
				hoverQuality = 1 + (1 - (yy + (length - 1)))*3;
			}

		}

	}


};



struct YamahaAction {
	int actionType = -1;

	float valorAntes = 0;
	float valorDepois = 0;

	int valorIntAntes = 0;
	int valorIntDepois = 0;

	Nota notaAntes;
	Nota notaDepois;

	std::vector<Nota> notas;

};

class Yamaha {

	float base;
	float baseMenor;
	float altura;

	float bps;

	// Redundantes
	float notasPorYamaha = 4;
	float notaSize = 1;

	float xScl = 1;
	float yScl = 1;

	Vector2f pos;

	float scrollY = 0;
	float scrollSpd = 0.1;

	vector<Nota*> notas;

	ConvexShape rect;

	ConvexShape bars[4];

	Texture teclado;
	Texture trapezioTexture;
	Sprite teclas[4];


	int maxLife = 200;
	int life = 200;



	float teclaXScl = 1;
	float teclaYScl = 1;

	bool teclaPressed[4];
	bool teclaState[4];

	float finishLineY = 0;

	int fadeFrames = 100;
	int fadeFramesTotal = 100;

	int uniqueId = 0;

	sf::Clock autoSaveTimer;
	sf::Time autoSaveTime;
	const string autoSavePath = "PianoFiles/_tilesAutoSave.txt";



	// Armazenando as musicas

	Music musica;
	int musicaId = -1;




	std::vector<struct YamahaAction> actions;
	std::vector<struct YamahaAction> undoneActions;

	Nota holdingStartState;


	SoundBuffer excelentBuffer;
	SoundBuffer outstandingBuffer;
	SoundBuffer impressiveBuffer;
	Sound excelentSnd;
	Sound outstandingSnd;
	Sound impressiveSnd;


public:
	int combo = 0;
	int comboMax = 200;

	int missedNotes = 0;
	int totalNotes = -1;

	int score = 0;

	bool exit = false;
	bool finished = false;
	bool success = false;

	float bregaPower = 0;
	float bregaMax = 1500;
	bool editing = true;
	bool playing = false;

	int holdingNote = -1;
	int selectedNote = -1;

	//std::vector<int> selectedNotes;

	int holdingPart = 0;

	/*
	float holdingNoteLength = 0;
	float holdingNoteY = 0;
	*/
	float holdingY = 0;


	float roomWid = 1280;
	float roomHei = 720;



	vector<Rooster::AreaEffect*> slideEffects;
	Rooster::Effect* textEffects;



	~Yamaha() {
		for (int i = 0; i < slideEffects.size(); i++) {
			delete slideEffects[i];
		}
		slideEffects.clear();

		delete textEffects;

		musica.stop();
		//musTeste.music.~Music();
	}

	Yamaha(Vector2f roomSize) {

		roomWid = roomSize.x;
		roomHei = roomSize.y;



		// Ce ta procurando a lista de musicas do tiles, tá no inicio do TilesDoArrocha.h
		excelentBuffer.loadFromFile("sounds/exelente.ogg");
		excelentSnd.setBuffer(excelentBuffer);

		outstandingBuffer.loadFromFile("sounds/outstanding.ogg");
		outstandingSnd.setBuffer(outstandingBuffer);

		impressiveBuffer.loadFromFile("sounds/impressive.ogg");
		impressiveSnd.setBuffer(impressiveBuffer);



		//musica.openFromFile("PianoFiles/sounds/latitude.ogg");
		//loadNotas(autoSavePath);


		loadMusica(randInt(5));


		base = 400;
		altura = 600;

		notaSize = altura / notasPorYamaha;

		baseMenor = base;

		bps = 4;

		pos.x = roomWid / 2;
		pos.y = 40;





		rect = rectToConvexShape(-base / 2, 0, base, altura);



		// Autosave Timer
		autoSaveTimer.restart();
		autoSaveTime = sf::seconds(60);




		// TrackBars
		float baseQuart = base / 4;
		for (int i = 0; i < 4; i++) {
			float baseAdd = (baseQuart * (i - 2));
			bars[i] = rectToConvexShape(baseAdd, 0, baseQuart, altura);
		}



		teclado.loadFromFile("sprites/teclas.png");
		trapezioTexture.loadFromFile("");




		for (int i = 0; i < 4; i++) {
			teclas[i].setTexture(teclado);
			teclas[i].setTextureRect(IntRect(445 * i, 0, 445, 250));

			teclaXScl = (base / 4) / teclas[i].getLocalBounds().width;
			teclaYScl = teclaXScl;

			float baseQuart = base / 4;
			float baseAdd = (baseQuart * (i - 2));
			Vector2f tecPos(baseAdd + baseQuart / 2, altura + 20);


			tecPos = convertToTrap(tecPos, baseMenor);
			tecPos.x *= xScl;
			tecPos.y *= yScl;
			tecPos.x += pos.x;
			tecPos.y += pos.y;

			teclas[i].setPosition(tecPos);
			teclas[i].setScale(xScl * teclaXScl, yScl * teclaYScl);


			teclas[i].setOrigin(teclas[i].getLocalBounds().width / 2, teclas[i].getLocalBounds().height / 2);

			teclaPressed[i] = false;

			Color partColor;

			switch (i) {
			case 0:
				partColor = Color(255, 100, 100, 180);
				break;
			case 2:
				partColor = Color(100, 255, 100, 180);
				break;

			case 3:
				partColor = Color(255, 255, 100, 180);
				break;

			case 1:
				partColor = Color(100, 100, 255, 180);
				break;

			default:
				partColor = Color(100, 100, 100, 180);
			}


			FloatRect area(pos.x + baseAdd * xScl, pos.y + (altura + 20) * yScl, baseQuart * xScl, 20 * yScl);

			Rooster::AreaEffect* areaEffect = new Rooster::AreaEffect(area, partColor);
			areaEffect->tilesPreset();
			areaEffect->color = partColor;



			slideEffects.push_back(areaEffect);

		}

		textEffects = new Rooster::Effect();
		textEffects->tilesPreset();
		textEffects->gravity.y = 0;
		textEffects->sclMin = 1.4;
		textEffects->sclMax = 1.5;
		textEffects->hspeedMax = 0.1;
		textEffects->hspeedMin = -0.1;
		textEffects->vspeedMax = -2;
		textEffects->vspeedMin = -1.8;
		textEffects->friction = 0.95;
		textEffects->lifeMin = 350;
		textEffects->lifeMax = 350;
		textEffects->textPreset();
		textEffects->fadeOutAlpha = false;
		textEffects->fadeInAlpha = true;

		textEffects->mortal = false;






	}





	void convertNoteToTrap(ConvexShape& note, float baseMenor) {
		for (int i = 0; i < 4; i++) {
			Vertex p = note.getPoint(i);
			Vector2f point = p.position;


			//point = noteYPerspective(point, baseMenor);

			point = convertToTrap(point, baseMenor);

			note.setPoint(i, point);
		}

	}




	Vector2f convertToTrap(Vector2f point, float baseMenor) {



		float x = point.x;

		if (base - baseMenor != 0) {
			float hSmall = baseMenor * altura / (base - baseMenor);


			x = (hSmall + point.y) * (point.x / (hSmall + altura));
		}



		return Vector2f(x, point.y);
	}


	float getScroll() {
		return scrollY;
	}

	float getPlayingSeconds() {
		return musica.getPlayingOffset().asSeconds();
	}



	void hardClearNotas() {
		for (int i = 0; i < notas.size(); i++) {
			delete notas[i];
		}
		notas.clear();
		actions.clear();
	}




	void saveNotas(std::string str) {
		std::ofstream file(str);

		if (file.is_open()) {
			file << "BPS" << std::endl;
			file << bps << std::endl;
			for (int i = 0; i < notas.size(); i++) {
				file << "Nota " << i << std::endl;
				file << notas[i]->coluna << std::endl;
				file << notas[i]->y << std::endl;
				file << notas[i]->length << std::endl;
			}
			file << "End" << std::endl;

			println("Notas salvas com sucesso");
		}
		else {
			println("Falha ao salvar notas");
		}

		file.close();
	}

	void loadNotas(std::string str) {
		std::ifstream file(str);

		if (file.is_open()) {

			std::string line;
			std::getline(file, line);
			if (line == "BPS") {
				std::getline(file, line);
				bps = std::stof(line);

				hardClearNotas();
				setScroll(0);


				std::getline(file, line); // Nota 0
				while (line != "End" || file.eof() != 0) {



					std::getline(file, line);
					int coluna = std::stoi(line);

					std::getline(file, line);
					float y = std::stof(line);

					std::getline(file, line);
					float length = std::stof(line);

					if (length > 0) {
						Nota* nota = new Nota(coluna, length, y, uniqueId);

						uniqueId++;

						notas.push_back(nota);
					}

					std::getline(file, line); // Gets End or Nota X
				}

			}

			println("Notas carregadas com sucesso");


			// Calculando a linha de chegada para vitoria
			// Achando a ultima nota da musica
			float yMin = 0;
			for (int i = 0; i < notas.size(); i++) {
				Nota* nota = notas[i];

				if (nota->y < yMin) {
					yMin = nota->y;
				}
			}

			finishLineY = (-yMin) + 2;

		}
		else {
			println("Falha ao carregar notas");
		}





		file.close();
	}



	int getMusicaId() {
		return musicaId;
	}

	void loadMusica(int tilesMusicaIndex) {

		musica.openFromFile(tilesMusicas[tilesMusicaIndex].soundPath);
		loadNotas(tilesMusicas[tilesMusicaIndex].notasPath);
		musicaId = tilesMusicaIndex;
	}












	void clearNotasNoAction() {
		for (int i = 0; i < notas.size(); i++) {
			delete notas[i];
		}
		notas.clear();
	}

	void clearNotas() {
		struct YamahaAction action;
		action.actionType = 4;
		for (int i = 0; i < notas.size(); i++) {
			action.notas.push_back(*notas[i]);
		}

		clearNotasNoAction();

		actions.push_back(action);
	}

	void unClearNotasNoAction(struct YamahaAction& action) {
		for (int i = 0; i < action.notas.size(); i++) {
			Nota n = action.notas[i];
			createNotaNoAction(n.coluna, n.length, n.y, n.id);
		}
	}












	Nota* createNotaNoAction(int col, float len, float yy, int id) {
		Nota* n = new Nota(col, len, yy, id);

		notas.push_back(n);

		return n;
	}

	void createNota(int col, float len, float yy) {

		uniqueId++;
		Nota* n = createNotaNoAction(col, len, yy, uniqueId);

		struct YamahaAction action;
		action.actionType = 1;
		action.notaAntes = *n;
		action.notaDepois = *n;

		actions.push_back(action);

		println("NotaCreated");
	}

	void deleteNotaNoAction(int index) {
		if (index != -1) {
			delete notas[index];
			notas.erase(notas.begin() + index);
		}
	}

	void deleteNota(int index) {
		if (index != -1) {
			struct YamahaAction action;
			action.actionType = 2;
			action.notaAntes = *notas[index];
			action.notaDepois = *notas[index];

			actions.push_back(action);

			deleteNotaNoAction(index);

			println("NotaDeleted");
		}
	}

	void updateNotaNoAction(int index, int coluna, float length, float y) {
		notas[index]->coluna = coluna;
		notas[index]->length = length;
		notas[index]->y = y;
	}

	void updateNotaNoAction(int index, Nota nota) {
		updateNotaNoAction(index, nota.coluna, nota.length, nota.y);
	}

	void updateNota(int index, int coluna, float length, float y) {
		if (index != -1) {
			struct YamahaAction action;
			action.actionType = 0;
			action.notaAntes = *notas[index];
			//println("L antes " << action.notaAntes.length);

			updateNotaNoAction(index, coluna, length, y);



			action.notaDepois = *notas[index];

			//println("L depois " << action.notaDepois.length);

			actions.push_back(action);

			println("NotaUpdated");
		}
		else {
			println("Index Update Nota = -1");
		}


	}

	void updateNota(int index, Nota note) {
		updateNota(index, note.coluna, note.length, note.y);
	}


	void play() {
		musica.play();
		playing = true;
	}

	void pause() {
		musica.pause();

		resetNotesState();

		playing = false;
	}

	void setScroll(float amount) {
		scrollY = maximum(amount, 0);
		musica.setPlayingOffset(sf::seconds(scrollY / bps));
	}

	void moveScroll(float amount) {
		setScroll(scrollY + amount);
	}


	void setBPSNoAction(float beatsPerSecond) {
		bps = beatsPerSecond;
	}

	void setBPS(float beatsPerSecond) {

		struct YamahaAction action;
		action.actionType = 3;
		action.valorAntes = bps;

		setBPSNoAction(beatsPerSecond);

		action.valorDepois = bps;

		actions.push_back(action);

	}

	float getBPS() {
		return bps;
	}

	int getNotaIndexById(int id) {
		for (int i = 0; i < notas.size(); i++) {
			if (notas[i]->id == id) {
				return i;
			}
		}
		return -1;
	}

	void undo() {

		if (actions.size() > 0) {

			struct YamahaAction action = actions[actions.size() - 1];

			switch (action.actionType) {
			case 0:

				//println("Update Id " << action.notaAntes.id << "  Index " << getNotaIndexById(action.notaAntes.id));
				updateNotaNoAction(getNotaIndexById(action.notaAntes.id), action.notaAntes);
				println("Nota Unupdated");
				break;

			case 1:
				// Create Action  // Delete Undo
				deleteNotaNoAction(getNotaIndexById(action.notaAntes.id));
				println("Nota Uncreated");
				break;

			case 2:
				// Delete Action // Create Undo
				createNotaNoAction(action.notaDepois.coluna, action.notaDepois.length, action.notaDepois.y, action.notaDepois.id);
				println("Nota Undeleted");
				break;

			case 3:
				// Set BPS Action // Unset BPS Undo
				setBPSNoAction(action.valorAntes);
				println("Bps unsetted");
				break;

			case 4:
				// Clear Action // Unclear Undo
				unClearNotasNoAction(action);
				println("Notas unCleared");
				break;


			default:
				break;
			}

			actions.pop_back();

			undoneActions.push_back(action);

		}
	}

	void update(Vector2f mouse) {


		if (editing) {

			if (autoSaveTimer.getElapsedTime() > autoSaveTime) {
				saveNotas(autoSavePath);
				autoSaveTimer.restart();
				println("TILES AUTO-SAVE on " << autoSavePath);

			}


			if (holdingNote == -1) {

				if (mainInput.keyboardState[sf::Keyboard::LControl][0]) {
					if (mainInput.keyboardState[sf::Keyboard::Z][1]) {
						undo();
					}
				}


				if (selectedNote != -1) {
					if (mainInput.keyboardState[sf::Keyboard::Delete][1]) {
						deleteNota(selectedNote);
						selectedNote = -1;
					}
				}


				if (mainInput.mouseState[0][1]) {

					ConvexShape testRect = rect;
					testRect.setScale(xScl, yScl);
					testRect.setPosition(pos);

					Vector2f rectPos = Vector2f(testRect.getGlobalBounds().left, testRect.getGlobalBounds().top);
					Vector2f rectSize = Vector2f(testRect.getGlobalBounds().width, testRect.getGlobalBounds().height);



					if (pointInside(mouse, rectPos.x, rectPos.y, rectSize.x, rectSize.y)) {

						int coluna = ((float)(mouse.x - rectPos.x) / (rectSize.x)) * 4;

						float yy = (((mouse.y - rectPos.y) / altura) * notasPorYamaha) - notasPorYamaha - scrollY;


						bool achou = false;
						for (int i = 0; i < notas.size(); i++) {
							struct Nota* nota = notas[i];

							if (nota->coluna == coluna) {
								if (yy > nota->y && yy < nota->y + nota->length) {

									achou = true;

									float difY = yy - nota->y;
									int part = 1;
									if (difY < 0.25) {
										part = 0;
									}
									else if (difY > nota->length - 0.25) {
										part = 2;
									}


									holdingNote = i;
									selectedNote = i;
									holdingPart = part;
									//holdingNoteLength = nota->length;
									//holdingNoteY = nota->y;
									holdingY = yy;

									holdingStartState = *nota;


									i = notas.size();

								}
							}
						}

						if (!achou) {
							createNota(coluna, 1, (int)(yy - 1));
						}

					}




				}


			}
			else {
				if (mainInput.mouseState[0][2]) {
					//println("Soltou");

					// Oh gambiarrado satanas
					Nota n = *notas[holdingNote];
					*notas[holdingNote] = holdingStartState;
					updateNota(holdingNote, n);
					holdingNote = -1;
				}
				else {

					ConvexShape testRect = rect;
					testRect.setScale(xScl, yScl);
					testRect.setPosition(pos);

					Vector2f rectPos = Vector2f(testRect.getGlobalBounds().left, testRect.getGlobalBounds().top);
					Vector2f rectSize = Vector2f(testRect.getGlobalBounds().width, testRect.getGlobalBounds().height);


					struct Nota* nota = notas[holdingNote];
					float yy = (((mouse.y - rectPos.y) / altura) * notasPorYamaha) - notasPorYamaha - scrollY;

					float yDif = yy - holdingY;



					if (holdingPart == 0) {


						nota->length = maximum(holdingStartState.length - yDif, 0.25);
						float newDif = holdingStartState.length - nota->length;

						nota->y = holdingStartState.y + newDif;
					}
					else if (holdingPart == 1) {

						nota->y = holdingStartState.y + yDif;
					}
					else {
						nota->length = maximum(holdingStartState.length + yDif, 0.25);
					}



				}
			}
		}



		if (playing) {
			scrollY = bps * getPlayingSeconds();

			if (musica.getStatus() == sf::Music::Stopped) {
				musica.setPlayingOffset(musica.getDuration());
				musica.pause();
				scrollY = bps * getPlayingSeconds();
			}

			if (scrollY > finishLineY || musica.getStatus() == sf::Music::Stopped) {
				if (!finished && !editing) {
					finish();
				}
			}


			// Player 1 (Por enquanto) 
			teclaPressed[0] = mainInput.inputState[0][Rooster::TILES1][1];
			teclaPressed[1] = mainInput.inputState[0][Rooster::TILES2][1];
			teclaPressed[2] = mainInput.inputState[0][Rooster::TILES3][1];
			teclaPressed[3] = mainInput.inputState[0][Rooster::TILES4][1];

			teclaState[0] = mainInput.inputState[0][Rooster::TILES1][0];
			teclaState[1] = mainInput.inputState[0][Rooster::TILES2][0];
			teclaState[2] = mainInput.inputState[0][Rooster::TILES3][0];
			teclaState[3] = mainInput.inputState[0][Rooster::TILES4][0];




			bool teclaMissed[] = { true, true, true, true };

			for (int j = 0; j < notas.size(); j++) {


				struct Nota* nota = notas[j];

				float notaY = nota->y + scrollY;

				nota->update(scrollY);

				int coluna = nota->coluna;

				if (!nota->missed) {
					if (nota->hovered) {
						if (teclaState[coluna] && !nota->loose) {
							if (nota->hitted) {
								if (nota->length != 1) {
									nota->slided = 1 - constrain((-notaY) / (nota->length - 1), 0, 1);

									for (int k = 0; k < (nota->slided * 10) * nota->length / 5; k++) {
										slideEffects[coluna]->createParticle();
									}
									bregaPower += 1;

								}
							}
						}
						else {
							if (nota->hitted) {
								nota->loose = true;
							}
						}

						if (teclaPressed[coluna]) {
							if (!nota->hitted) {
								nota->hitted = true;

								slideEffects[coluna]->createMultipleParticles(30);

								if (nota->length > 1) {
									nota->holded = true;
								}
								teclaMissed[coluna] = false;


								score += nota->hoverQuality;

								comboAdd();
								bregaPower += 15 + (nota->hoverQuality-1)*2 + combo*0.5;
							}
						}
					}
				}

				if (notaY + (nota->length - 1) > 0) {
					if (!nota->missed && !nota->hitted) {
						nota->missed = true;
						life -= 5;

						missedNotes++;

						comboBreak();
						
						bregaPower -= 200;
					}
				}
			}

			for (int i = 0; i < 4; i++) {
				if (teclaPressed[i]) {
					if (teclaMissed[i]) {
						life -= 5;

						comboBreak();
						bregaPower -= 70;
					}
				}

				slideEffects[i]->update();
			}

			if (bregaPower > 0) {
				bregaPower -= 1 * (1 + (bregaPower / bregaMax));
			}
			else {
				bregaPower = 0;
			}

		}



		textEffects->update();

		if (finished) {

			if (fadeFrames <= 0) {
				exit = true;
			}
			else {

				fadeFrames--;

				musica.setVolume(100 * ((float)fadeFrames / fadeFramesTotal));
			}
		}
	}

	void comboBreak() {

		if (combo > 3) {
			std::string str = "ComboBreak ";

			float scl = textEffects->sclMax;

			str += std::to_string(combo);
			textEffects->position.x = randFloat(roomWid*0.75);
			textEffects->position.y = randFloat(roomHei);
			textEffects->color = Color::Red;
			textEffects->text.setString(str);
			textEffects->sclMax = scl * constrain(1 + ((float)combo / 200), 1, 3);
			textEffects->sclMin = scl * constrain(1 + ((float)combo / 200), 1, 3);
			textEffects->createParticle();
			textEffects->sclMax = scl ;
			textEffects->sclMin = scl ;

		}


		combo = 0;
	}





	void comboAdd() {

		combo++;

		if (combo > 3) {
			std::string str = "Combo ";
			str += std::to_string(combo);

			textEffects->position.x = roomWid * 0.75 + randFloat(roomWid / 10);
			textEffects->position.y = roomHei * 0.5 + randFloat(roomHei / 10);
			textEffects->color = Rooster::hsv(combo * 5, 1, 1);
			textEffects->text.setString(str);
			textEffects->createParticle();

			comboMerit();
		}



	}

	void comboMerit() {

		bool say = true;
		std::string str = "";
		Color col;

		switch (combo) {
		case 100:
			str = "EXCELENT";
			col = Color::Green;
			excelentSnd.play();
			break;

		case 200:
			str = "IMPRESSIVE";
			col = Color(100, 150, 250);
			impressiveSnd.play();
			break;

		case 250:
			str = "OUTSTANDING";
			col = Color(250, 150, 250);
			outstandingSnd.play();
			break;
		default:
			say = false;
			break;
		}

		
		if (say) {
			float scl = textEffects->sclMax;
			textEffects->position.x = randFloat(roomWid * 0.5);
			textEffects->position.y = randFloat(roomHei);
			textEffects->color = col;
			textEffects->text.setString(str);
			textEffects->sclMax = scl * constrain(1.5 + ((float)combo / 200), 1, 3);
			textEffects->sclMin = scl * constrain(1.5 + ((float)combo / 200), 1, 3);
			textEffects->createParticle();
			textEffects->sclMax = scl;
			textEffects->sclMin = scl;
		}
	}

	void finish() {
		finished = true;

		if (life > 0) {
			success = true;
		}


		std::string str = "Finished!";

		textEffects->position.x = roomWid * 0.75 + randFloat(roomWid / 10);
		textEffects->position.y = roomHei * 0.5 + randFloat(roomHei / 10);
		textEffects->color = Color::White;
		textEffects->text.setString(str);
		textEffects->createParticle();
	}


	void resetNotesState() {
		for (int i = 0; i < notas.size(); i++) {
			struct Nota* nota = notas[i];
			nota->resetState();
		}
		finished = false;
		success = false;
		exit = false;
		fadeFrames = 100;

		combo = 0;
		life = maxLife;
		score = 0;
		missedNotes = 0;
	}


	void draw(RenderWindow* window, int frames) {



		ConvexShape trap;



		trap.setPointCount(4);
		for (int i = 0; i < 4; i++) {
			trap.setPoint(i, convertToTrap(rect.getPoint(i), baseMenor));
		}




		trap.setFillColor(Color::Blue);
		trap.setScale(xScl, yScl);
		trap.setPosition(pos);

		window->draw(trap);


		for (int j = 0; j < 4; j++) {

			ConvexShape bar;

			bar.setPointCount(4);
			for (int i = 0; i < 4; i++) {
				bar.setPoint(i, convertToTrap(bars[j].getPoint(i), baseMenor));
			}




			bar.setFillColor(Color(0, 0, 255, 10));
			bar.setScale(xScl, yScl);
			bar.setPosition(pos);

			bar.setOutlineColor(Color::White);
			bar.setOutlineThickness(1);

			window->draw(bar);
		}


		sf::Text notaIndex;
		notaIndex.setFont(basicFont);
		notaIndex.setColor(Color::White);
		notaIndex.setCharacterSize(15);
		notaIndex.setScale(xScl, yScl);

		for (int i = 0; i < notas.size(); i++) {

			ConvexShape noteShape;

			noteShape.setPointCount(4);

			int coluna = notas[i]->coluna;


			float baseQuart = base / 4;
			float noteX = (baseQuart * (coluna - 2));

			float noteY = (notas[i]->y + scrollY) * notaSize + altura;
			float noteLen = notaSize * notas[i]->length;


			noteShape = rectToConvexShape(noteX, noteY, baseQuart, noteLen);

			convertNoteToTrap(noteShape, baseMenor);


			noteShape.setPosition(pos);
			noteShape.setScale(xScl, yScl);

			if (notas[i]->hitted) {
				noteShape.setFillColor(Color::Green);
			}
			else if (notas[i]->missed) {
				noteShape.setFillColor(Color::Red);
			}
			else if (notas[i]->hovered || i == selectedNote) {
				noteShape.setFillColor(Color(100, 100, 200));
			}
			else {
				noteShape.setFillColor(Color::Black);
			}

			noteShape.setOutlineColor(Color::White);
			noteShape.setOutlineThickness(2);

			window->draw(noteShape);



			if (notas[i]->length > 1) {
				ConvexShape lineShape;



				lineShape.setPointCount(4);


				float lineWid = baseQuart / 4;
				float lineX = noteX + baseQuart / 2 - lineWid / 2;

				lineShape = rectToConvexShape(lineX, noteY, lineWid, -notaSize + noteLen);


				convertNoteToTrap(lineShape, baseMenor);



				lineShape.setPosition(pos);
				lineShape.setScale(xScl, yScl);

				if (notas[i]->hitted) {
					lineShape.setFillColor(Color(0, 100, 0));
				}
				else if (notas[i]->missed) {
					lineShape.setFillColor(Color::Red);
				}
				else {
					lineShape.setFillColor(Color(20, 20, 20));
				}

				lineShape.setOutlineColor(Color::White);
				lineShape.setOutlineThickness(2);

				window->draw(lineShape);



				ConvexShape sliderShape;
				sliderShape.setPointCount(4);
				float sliderWid = baseQuart / 3;
				float sliderX = noteX + baseQuart / 2 - sliderWid / 2;

				float sliderHei = sliderWid;
				float sliderY = noteY - (sliderHei / 2) + (noteLen - notaSize) * (1 - notas[i]->slided);

				sliderShape = rectToConvexShape(sliderX, sliderY, sliderWid, sliderHei);



				convertNoteToTrap(sliderShape, baseMenor);

				sliderShape.setPosition(pos);
				sliderShape.setScale(xScl, yScl);

				if (notas[i]->hitted) {
					sliderShape.setFillColor(Color(100, 200, 100));
				}
				else if (notas[i]->missed) {
					sliderShape.setFillColor(Color::Red);
				}
				else {
					sliderShape.setFillColor(Color(230, 230, 230));
				}

				sliderShape.setOutlineColor(Color::White);
				sliderShape.setOutlineThickness(2);

				window->draw(sliderShape);




			}


			if (SHOWDEBUG) {
				notaIndex.setPosition(noteX + pos.x, noteY + pos.y);
				notaIndex.setString(std::to_string(i));
				window->draw(notaIndex);
			}






		}


		CircleShape c(20);

		c.setFillColor(Color(250, 100, 0, 100));

		for (int i = 0; i < 4; i++) {


			int texWid = teclas[i].getTexture()->getSize().x / 4;
			int texHei = teclas[i].getTexture()->getSize().y / 2;

			teclas[i].setTextureRect(IntRect(texWid * i, teclaState[i] * texHei, texWid, texHei));

			window->draw(teclas[i]);

			if (SHOWDEBUG) {
				float baseQuart = base / 4;
				float noteX = (baseQuart * (i - 2)) * xScl;
				c.setPosition(noteX + (baseQuart / 2), altura);
				window->draw(c);
			}

		}






		if (SHOWDEBUG) {
			RectangleShape r;
			r.setFillColor(Color(250, 200, 0, 100));

			for (int i = 0; i < notas.size(); i++) {

				float baseQuart = base / 4;
				float noteX = (baseQuart * (notas[i]->coluna - 2)) * xScl;

				r.setSize(Vector2f(baseQuart / 2, notas[i]->length * notaSize * yScl));
				c.setPosition(noteX + (baseQuart / 2), notas[i]->y + scrollY);
				r.setPosition(noteX + ((baseQuart / 2) - (baseQuart / 4)) * xScl, notas[i]->y + scrollY);

				window->draw(c);
				window->draw(r);

			}
		}


		RectangleShape rect;





		int outLine = 4;
		int offSet = 4;

		int wid = roomWid - 100;
		int hei = 40;

		int x = (roomWid - wid)/2;
		int y = 10;

		

		rect.setFillColor(Color(250, 250, 250, 255));
		rect.setSize(Vector2f(wid - 2 * outLine, hei - 2 * outLine));
		rect.setPosition(x + outLine, y + outLine);
		rect.setFillColor(Color(0, 0, 0, 0));
		rect.setOutlineColor(Color::White);
		rect.setOutlineThickness(outLine);

		window->draw(rect);

		rect.setOutlineThickness(0);
		rect.setFillColor(Color::Green);
		rect.setPosition(x + outLine + offSet, y + outLine + offSet);
		rect.setSize(Vector2f((wid - 2 * (outLine + offSet)) * constrain((float)life / maxLife, 0, 1), hei - 2 * (outLine + offSet)));
		window->draw(rect);

		sf::Text scoreText;
		std::string scoreStr = "SCORE ";
		scoreStr += std::to_string(score);
		scoreText.setScale(1, 1);
		scoreText.setString(scoreStr);
		scoreText.setFillColor(Color::White);
		scoreText.setFont(basicFont);
		scoreText.setPosition( x ,rect.getGlobalBounds().top + rect.getGlobalBounds().height + 20);
		window->draw(scoreText);









		for (int i = 0; i < 4; i++) {
			slideEffects[i]->draw(*window);
		}

		textEffects->draw(*window);

		if (finished) {
			RectangleShape fade(Vector2f(roomWid, roomHei));
			fade.setFillColor(Color(0, 0, 0, 255 * (1 - ((float)fadeFrames / fadeFramesTotal))));
			//println(fadeFrames);
			window->draw(fade);
		}

	}

};

class BregaMeter {

	Sprite sprite;

	float x;
	float y;
	float wid;
	float hei;

	float xScl;
	float yScl;

	float bregaSprWid;
	float bregaSprHei;

	Rooster::Effect* effect;

	int tick = 0;

	SoundBuffer sndBufExplosion;
	Sound sndExplosion;

	int pontBreakTimer = 250;

	bool pontBroken = false;
	float pontAngle = 0;
	float pontAngleSpeed = 0;

	Vector2f pontSize;
	Vector2f pontOrigin;


	Vector2f pontPos;
	Vector2f pontSpeed;


public:
	float percentage = 0;

	bool broken = false;

	BregaMeter(Texture& bregaMeterTex, Vector2f roomSize) {

		sprite.setTexture(bregaMeterTex);



		bregaSprWid = bregaMeterTex.getSize().x / 2;
		bregaSprHei = bregaMeterTex.getSize().y;

		wid = roomSize.x / 5;



		xScl = wid / bregaSprWid;
		yScl = xScl;

		sprite.setScale(xScl, yScl);


		hei = bregaSprHei * yScl;

		x = roomSize.x - wid;
		y = roomSize.y - (bregaSprHei * yScl);


		pontSize = Vector2f(wid * 0.4, yScl * 20);
		pontOrigin = Vector2f(wid * 0.4, xScl * 10);


		effect = new Rooster::Effect();





		effect->sanguePreset();
		effect->poeiraPreset();
		effect->gravity.y = -0.1;
		effect->lifeMin = 80;
		effect->lifeMax = 150;
		effect->sclMin = 1;
		effect->sclMax = 2.5;


		effect->vspeedMax = -2;
		effect->vspeedMin = -0.5;
		effect->hspeedMax = 1;
		effect->hspeedMin = -1;
		effect->hspeedLimit = 4;
		effect->vspeedLimit = 3;
		effect->friction = 0.96;
		effect->fadeInAlpha = false;
		effect->fadeOutAlpha = true;
		effect->satMax = 0;
		effect->satMin = 0;
		effect->mortal = false;

		effect->position.x = x + wid / 2;
		effect->position.y = y + hei / 2;


		effect->spreadPreset(wid / 1.5, hei / 1.5);


		sndBufExplosion.loadFromFile("sounds/Explosion.ogg");

		sndExplosion.setBuffer(sndBufExplosion);
	}

	void update() {
		if (broken) {



			if (!pontBroken) {
				if (pontBreakTimer > 0) {

					pontAngleSpeed += 0.5;

					pontBreakTimer--;
				}
				else {
					breakPointer();
				}
			}

			tick++;
			if (tick > 50) {

				effect->createMultipleParticles(randInt(4));
				tick = randInt(30);

			}

			if (pontBroken) {
				pontSpeed.y += 0.1;
			}


			pontAngle += pontAngleSpeed;
			pontPos += pontSpeed;

		}
		else {
			pontAngle = (-5 + 185 * percentage);
		}

		effect->update();
	}

	void explode() {
		broken = true;



		effect->createMultipleParticles(randIntRange(20, 30));

		pontAngleSpeed = 5;

		sndExplosion.play();
	}

	void breakPointer() {
		pontBroken = true;


		float rotX = pontSize.x * cos(toRadiAnus(pontAngle));
		float rotY = pontSize.y * sin(toRadiAnus(pontAngle));

		pontOrigin.x = pontSize.x / 2;

		pontPos.x -= rotX;
		pontPos.y -= rotY;

		pontSpeed.y = 0.25 * sin(toRadiAnus(pontAngle)) * toRadiAnus(pontAngleSpeed) * pontSize.x / 2;
		pontSpeed.x = 0.25 * cos(toRadiAnus(pontAngle)) * toRadiAnus(pontAngleSpeed) * pontSize.x / 2;

		pontAngleSpeed = constrain(pontAngleSpeed, -20, 20);

		effect->createMultipleParticles(randIntRange(5, 10));
	}



	void draw(RenderWindow& window) {


		sprite.setScale(xScl, yScl);
		sprite.setPosition(x, y);

		sprite.setTextureRect(IntRect(bregaSprWid * broken, 0, bregaSprWid, bregaSprHei));

		window.draw(sprite);






		RectangleShape ponteiro(pontSize);
		ponteiro.setFillColor(Color(0, 0, 0));




		ponteiro.setPosition(pontPos.x + x + wid / 2 + xScl * 18, pontPos.y + y + (sprite.getLocalBounds().height - 112) * xScl);
		ponteiro.setOrigin(pontOrigin);
		ponteiro.setRotation(pontAngle);

		window.draw(ponteiro);


		effect->draw(window);

	}




};



struct TilesInfo {
	Yamaha* alcides;

	int frames = 0;

	Rooster::Galo* galoPeste;
	Rooster::Galo* galoKalsa;
	Rooster::Galo* galoSniper;
	Rooster::Galo* galoBruxo;
	Rooster::Galo* galoBota;

	Texture fundao;
	Texture bregaMeterTex;

	BregaMeter* bregaMeter;

	RectangleShape rect;

	sf::View tilesView;

	Vector2f roomSize;

	int result = -1;

	void init() {

		roomSize = Vector2f(1280, 720);

		struct Rooster::GaloStats kalsaSt = { 100, 10, 10, 10, 5 };

		galoPeste = new Rooster::Peste(kalsaSt, Rooster::state::DANCING, false);
		galoKalsa = new Rooster::Kalsa(kalsaSt, Rooster::state::DANCING, true);
		galoSniper = new Rooster::Sniper(kalsaSt, Rooster::state::DANCING, false);
		galoBruxo = new Rooster::Bruxo(kalsaSt, Rooster::state::DANCING, false);
		galoBota = new Rooster::Bota(kalsaSt, Rooster::state::DANCING, false);

		galoKalsa->setPosition(Vector2f((float)roomSize.x * 0.3, roomSize.y * 0.9));
		galoPeste->setPosition(Vector2f((float)roomSize.x * 0.75, roomSize.y * 0.9));
		galoSniper->setPosition(Vector2f((float)roomSize.x * 0.95, roomSize.y * 0.9));
		galoBruxo->setPosition(Vector2f((float)roomSize.x * 0.18, roomSize.y * 0.9));
		galoBota->setPosition(Vector2f((float)roomSize.x * 0.03, roomSize.y * 0.9));

		galoKalsa->noCollision = true;
		galoSniper->noCollision = true;
		galoPeste->noCollision = true;
		galoBruxo->noCollision = true;
		galoBota->noCollision = true;

		galoKalsa->facingRight = true;
		galoBota->facingRight = true;
		galoBruxo->facingRight = true;

		fundao.loadFromFile("sprites/tiringa.png");

		bregaMeterTex.loadFromFile("sprites/medidorBrega.png");

		bregaMeter = new BregaMeter(bregaMeterTex, roomSize);

		rect.setSize(roomSize);
		rect.setTexture(&fundao);
		rect.setFillColor(Color(255, 0, 255, 255));

		alcides = new Yamaha(roomSize);


		galoPeste->update();

		galoKalsa->update();

		galoSniper->update();

		galoBruxo->update();

		galoBota->update();


		alcides->update(Vector2f(0, 0));

	}

	void clear() {
		delete galoPeste;
		delete galoKalsa;
		delete galoSniper;
		delete galoBruxo;
		delete galoBota;
		delete bregaMeter;
		delete alcides;
	}

	void draw(RenderWindow& window) {
		window.draw(rect);

		alcides->draw(&window, frames);

		galoPeste->show(window);
		galoKalsa->show(window);
		galoSniper->show(window);
		galoBruxo->show(window);
		galoBota->show(window);

		bregaMeter->draw(window);
	}

	void update(RenderWindow& window) {
		frames++;


		if (mainInput.keyboardState[sf::Keyboard::Down][0]) {
			alcides->moveScroll(-5);
		}
		if (mainInput.keyboardState[sf::Keyboard::Up][0]) {
			alcides->moveScroll(5);
		}

		if (mainInput.keyboardState[sf::Keyboard::Space][1]) {
			if (alcides->editing) {
				if (alcides->playing) {

					alcides->pause();
				}
				else {
					alcides->play();

				}
			}
		}


		Vector2f mousePos = window.mapPixelToCoords((Vector2i)mainInput.mousePos);
		alcides->update(mousePos);

		if (alcides->playing) {
			galoPeste->update();

			galoKalsa->update();

			galoSniper->update();

			galoBruxo->update();

			galoBota->update();
		}

		bregaMeter->percentage = (float)alcides->bregaPower / alcides->bregaMax;
		bregaMeter->update();


		if (!bregaMeter->broken) {
			if (bregaMeter->percentage > 1.25) {
				bregaMeter->explode();
			}
		}

		if (alcides->exit) {
			result = alcides->success;
		}

	}
};


bool pianoTiles(RenderWindow * window, int musicaSelecionada) {


	float roomWid = 1280;
	float roomHei = 720;

	struct TilesInfo info;
	info.roomSize.x = roomWid;
	info.roomSize.y = roomHei;
	info.init();
	info.alcides->editing = false;
	info.alcides->loadMusica(musicaSelecionada);
	info.alcides->play();


	bool flores = false;


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

	struct ValBox loadBox;
	loadBox.init(2, 0, 100, 300, 40, "loadPath");
	loadBox.label = "loadPath sem o .txt (Ctrl+L)";

	struct ValBox saveBox;
	saveBox.init(2, 0, 300, 300, 40, "savePath");
	saveBox.label = "savePath sem o .txt (Ctrl+P)";

	struct ValBox bpsBox;
	bpsBox.init(0, 0, 500, 60, 40, info.alcides->getBPS());
	bpsBox.label = "Batidas por segundo";

	struct Button playButton;
	playButton.init(0, roomHei - 40, 80, 20);
	playButton.color = Color(250, 100, 150);
	playButton.label = "play";

	struct Button restartButton;
	restartButton.init(100, roomHei - 40, 80, 20);
	restartButton.color = Color(100, 100, 255);
	restartButton.label = "restart";

	struct Button clearButton;
	clearButton.init(200, roomHei - 40, 60, 20);
	clearButton.color = Color(0, 0, 0);
	clearButton.label = "clear";


	int musicaId = info.alcides->getMusicaId();


	while (window->isOpen()) {

		inputType = -1;

		mainInput.update();


		Event e;
		while (window->pollEvent(e))
		{
			if (e.type == Event::KeyPressed)
			{
				if (e.key.code == Keyboard::Escape)
				{
					info.clear();

					window->setView(window->getDefaultView());

					return false;
				}
				else if (e.key.code == Keyboard::Enter) {
					inputType = 1;
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
			else if (e.type == Event::TextEntered) {
				if (e.text.unicode < 128) {

					if (e.text.unicode > 31) {
						lastChar = (static_cast<char>(e.text.unicode));
						inputType = 0;
					}
					else if (e.text.unicode == 3 || e.text.unicode == 8) {
						inputType = 2;
					}
				}
			}
		}



		window->clear();



		info.update(*window);
		info.draw(*window);

		if (info.alcides->editing) {

			Vector2f mouseViewPos = window->mapPixelToCoords((Vector2i)mainInput.mousePos);

			loadBox.update(mouseViewPos, inputType, lastChar);
			loadBox.draw(*window);

			saveBox.update(mouseViewPos, inputType, lastChar);
			saveBox.draw(*window);

			bpsBox.update(mouseViewPos, inputType, lastChar);

			if (bpsBox.confirmed) {
				info.alcides->setBPS(bpsBox.fVal);
			}
			if (!bpsBox.selected) {
				bpsBox.setValue(info.alcides->getBPS());
			}

			bpsBox.draw(*window);

			//playButton.color = info.alcides->playing ? Color(100, 100, 100) : Color(180, 180, 180);
			playButton.label = info.alcides->playing ? "pause" : "play";
			playButton.update(mouseViewPos);

			playButton.draw(*window);

			if (playButton.clicked) {
				if (info.alcides->playing) {
					info.alcides->pause();
				}
				else {
					info.alcides->play();
				}
			}

			restartButton.update(mouseViewPos);

			restartButton.draw(*window);

			if (restartButton.clicked) {
				info.alcides->setScroll(0);
			}

			clearButton.update(mouseViewPos);

			clearButton.draw(*window);

			if (clearButton.clicked) {
				info.alcides->clearNotas();
			}


			if (mainInput.mouseScroll != 0) {
				info.alcides->moveScroll(mainInput.mouseScroll);
			}

		}
		//window->setView(view);

		if (mainInput.keyboardState[sf::Keyboard::LControl][0]) {
			if (mainInput.keyboardState[sf::Keyboard::L][1]) {

				std::string str = loadBox.sVal;
				str = "PianoFiles/" + str + ".txt";


				info.alcides->loadNotas(str);
			}

			if (mainInput.keyboardState[sf::Keyboard::P][1]) {

				std::string str = saveBox.sVal;
				str = "PianoFiles/" + str + ".txt";

				info.alcides->saveNotas(str);
			}
		}



		switch(musicaId) {
		case 0:
			if (info.alcides->getPlayingSeconds() > 46 && !flores) {
				flores = true;

				FloatRect area(0, -1000, roomWid, 1000);

				Rooster::AreaEffect* effect = new Rooster::AreaEffect(area, Color::White);
				effect->floresPreset();
				//effect->color = Color(200, 250, 100);

				effect->createMultipleParticles(100);

				mainPartSystem.addEffect(effect);
			}
			break;

		case 1:
			break;
		} 

		mainPartSystem.update();
		mainPartSystem.draw(*window);

		if (info.result != -1) {
			return info.result;
		}

		window->display();
	}


	info.clear();
	return true;


}



void tilesMenu(RenderWindow * window) {

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

	float buttonWid = 400;
	float buttonHei = 60;
	float yOffset = 40;

	for (int i = 0; i < tilesMusicas.size(); i++) {
		struct Button playButton;
		playButton.init(roomWid / 2 - buttonWid / 2, roomHei / 2 - tilesMusicas.size() * (yOffset + buttonHei) / 2 + (buttonHei + yOffset) * i, buttonWid, buttonHei);
		playButton.color = Color(250, 100, 150);
		playButton.label = tilesMusicas[i].name;
		buttons.push_back(playButton);
	}







	while (window->isOpen()) {

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
					return;
				}
				else if (e.key.code == Keyboard::Enter) {
					inputType = 1;
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
			else if (e.type == Event::TextEntered) {
				if (e.text.unicode < 128) {

					if (e.text.unicode > 31) {
						lastChar = (static_cast<char>(e.text.unicode));
						inputType = 0;
					}
					else if (e.text.unicode == 3 || e.text.unicode == 8) {
						inputType = 2;
					}
				}
			}
		}



		window->clear();


		Vector2f mouseViewPos = window->mapPixelToCoords((Vector2i)mainInput.mousePos);

		for (int i = 0; i < buttons.size(); i++) {
			buttons[i].draw(*window);
			buttons[i].update(mouseViewPos);

			if (buttons[i].clicked) {
				pianoTiles(window, i);
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
			}
		}




		mainPartSystem.update();
		mainPartSystem.draw(*window);


		window->display();
	}

	return;
}
