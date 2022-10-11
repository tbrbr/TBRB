
int OptionMenuPrincipal = 0;
int OptionMenuIniciar = 0;
bool iniciar = false;

void makeGif(Sprite * vetor, RectangleShape videoBorder) {



}
void menuPrincipal(RenderWindow* window, int& option) {

	int mousex;
	int mousey;
	Event e;
	while (window->pollEvent(e))
	{

		mousex = e.mouseMove.x;
		mousey = e.mouseMove.x;

		if (e.type == Event::KeyPressed)
		{
			if (iniciar) {
				if (e.key.code == Keyboard::Escape)
				{
					window->close();
				}
				if (e.key.code == Keyboard::W)
				{
					OptionMenuIniciar--;
					if (OptionMenuIniciar < 0)
						OptionMenuIniciar = 2;
				}
				else if (e.key.code == Keyboard::S) {
					OptionMenuIniciar++;
					if (OptionMenuIniciar  > 2)
						OptionMenuIniciar = 0;
				}
				else if (e.key.code == Keyboard::Up)
				{
					OptionMenuIniciar--;
					if (OptionMenuIniciar < 0)
						OptionMenuIniciar = 2;
				}
				else if (e.key.code == Keyboard::Down) {
					OptionMenuIniciar++;
					if (OptionMenuIniciar > 2)
						OptionMenuIniciar = 0;
				}
				if (e.key.code == Keyboard::Enter) {
					switch (OptionMenuIniciar)
					{
					case 0:
					{
						
						break;
					}
					case 1:
					{
						option = 0;
						break;
					}
					case 2:
						option = 3;
					default:
						break;
					}
				}

			}
			else {
				if (e.key.code == Keyboard::Escape)
				{
					window->close();
				}
				if (e.key.code == Keyboard::W)
				{
					OptionMenuPrincipal--;
					if (OptionMenuPrincipal < 0)
						OptionMenuPrincipal = 2;
				}
				else if (e.key.code == Keyboard::S) {
					OptionMenuPrincipal++;
					if (OptionMenuPrincipal > 2)
						OptionMenuPrincipal = 0;
				}
				else if (e.key.code == Keyboard::Up)
				{
					OptionMenuPrincipal--;
					if (OptionMenuPrincipal < 0)
						OptionMenuPrincipal = 2;
				}
				else if (e.key.code == Keyboard::Down) {
					OptionMenuPrincipal++;
					if (OptionMenuPrincipal > 2)
						OptionMenuPrincipal = 0;
				}

				if (e.key.code == Keyboard::Enter) {
					switch (OptionMenuPrincipal)
					{
					case 0:
					{
						iniciar = true;
						break;
					}
					default:
						break;
					}
				}
			}
		}

	}

	RectangleShape fundo(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	//bakcground picture
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("sprites/background_menu.png");
	fundo.setTexture(&backgroundTexture);

	//title
	Color redText(205, 0, 0);

	Font fontTitle;
	fontTitle.loadFromFile("fonts/CloisterBlack.ttf");
	Text title;
	title.setFont(fontTitle);
	title.setString("Menu Principal");
	title.setCharacterSize(SCREEN_WIDTH / 16);
	title.setPosition(SCREEN_WIDTH / 1.4 - title.getGlobalBounds().width / 2, SCREEN_HEIGHT /9);
	title.setFillColor(redText);

	//options
	Color redOption(193, 0, 0);
	Font fontOption;
	fontOption.loadFromFile("fonts/blops.ttf");

	Text option1;
	option1.setFont(fontOption);
	option1.setString("Iniciar");
	option1.setCharacterSize(SCREEN_WIDTH / 48);
	option1.setPosition(SCREEN_WIDTH / 1.4 - option1.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2);
	option1.setFillColor(redOption);

	Text option2;
	option2.setFont(fontOption);
	option2.setString("Ajustes");
	option2.setCharacterSize(SCREEN_WIDTH / 48);
	option2.setPosition(SCREEN_WIDTH / 1.4 - option2.getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 + option1.getGlobalBounds().height * 2);

	option2.setFillColor(redOption);

	Text option3;
	option3.setFont(fontOption);
	option3.setString("sair do jogo");
	option3.setCharacterSize(SCREEN_WIDTH / 48);
	option3.setPosition(SCREEN_WIDTH / 1.4 - option3.getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 + option1.getGlobalBounds().height * 4);

	option3.setFillColor(redOption);

	//garrinha
	Texture garrinha;
	garrinha.loadFromFile("sprites/garra_menu.png");
	Sprite garra;
	garra.setTexture(garrinha);
	garra.setTextureRect(IntRect(0, 0, 420, 221));
	garra.setScale((float)SCREEN_WIDTH / 6400, (float)SCREEN_HEIGHT / 3600);


	//checking for garrinha

	int spaceBetween = garra.getGlobalBounds().width;

	
	switch (OptionMenuPrincipal)
	{
	case 0:
		garra.setPosition(SCREEN_WIDTH / 1.4 - option1.getGlobalBounds().width / 2 - spaceBetween,
			SCREEN_HEIGHT / 2);
		break;
	case 1:
		garra.setPosition(SCREEN_WIDTH / 1.4 - option2.getGlobalBounds().width / 2 - spaceBetween,
			SCREEN_HEIGHT / 2 + option1.getGlobalBounds().height * 2);
		break;
	case 2:
		garra.setPosition(SCREEN_WIDTH / 1.4 - option3.getGlobalBounds().width / 2 - spaceBetween,
			SCREEN_HEIGHT / 2 + option1.getGlobalBounds().height * 4);
		break;
	}

	

	window->draw(fundo);
	window->draw(title);
	window->draw(option1);
	window->draw(option2);
	window->draw(option3);
	

	if (iniciar) {
		RectangleShape borda;
		borda.setSize(Vector2f(SCREEN_WIDTH / 2,SCREEN_HEIGHT/2));
		borda.setPosition(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4,SCREEN_HEIGHT/2 - SCREEN_HEIGHT / 4);
		borda.setFillColor(Color::Black);
		borda.setOutlineThickness(SCREEN_WIDTH / 200);
		borda.setOutlineColor(redText);
		
		
		
		Text optionInit;
		optionInit.setFont(fontOption);
		optionInit.setString("Multiplayer");
		optionInit.setCharacterSize(SCREEN_WIDTH / 48);
		optionInit.setPosition(
			SCREEN_WIDTH / 2 - optionInit.getGlobalBounds().width / 2,
			SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4 + option1.getGlobalBounds().height
		);
		optionInit.setFillColor(redOption);

		int spaceYBetween = optionInit.getGlobalBounds().height;

		Text optionInit2;
		optionInit2.setFont(fontOption);
		optionInit2.setString("Singleplayer");
		optionInit2.setCharacterSize(SCREEN_WIDTH / 48);
		optionInit2.setPosition(
			SCREEN_WIDTH / 2 - optionInit2.getGlobalBounds().width / 2,
			SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4 + spaceYBetween*4
		);
		optionInit2.setFillColor(redOption);

		Text optionInit3;
		optionInit3.setFont(fontOption);
		optionInit3.setString("MiniGames");
		optionInit3.setCharacterSize(SCREEN_WIDTH / 48);
		optionInit3.setPosition(
			SCREEN_WIDTH / 2 - optionInit3.getGlobalBounds().width / 2,
			SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4 + spaceYBetween*7
		);
		optionInit3.setFillColor(redOption);

		window->draw(borda);
		window->draw(optionInit);
		window->draw(optionInit2);
		window->draw(optionInit3);

		//checking for garrinha

		int spaceBetween = garra.getGlobalBounds().width;

		switch (OptionMenuIniciar)
		{
		case 0:
			garra.setPosition(
				SCREEN_WIDTH / 2 - optionInit.getGlobalBounds().width / 2 - spaceBetween,
				SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4 + option1.getGlobalBounds().height
			);
			break;
		case 1:
			garra.setPosition(
				SCREEN_WIDTH / 2 - optionInit2.getGlobalBounds().width / 2 - spaceBetween,
				SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4 + spaceYBetween * 4
			);
			break;
		case 2:
			garra.setPosition(
				SCREEN_WIDTH / 2 - optionInit3.getGlobalBounds().width / 2 - spaceBetween,
				SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4 + spaceYBetween * 7
			);
			break;
		}


	}
	window->draw(garra);
	window->display();
}


void selectionsingleplayer() {
	int galos[NUMGALOS];
	RectangleShape recs[NUMGALOS];
	float squareSize = 50;
	for (int i = 0; i < NUMGALOS; i++)
	{
		recs[i].setSize(Vector2f(squareSize, squareSize));
	}
	//recs[0].setTexture(, true);

}