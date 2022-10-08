
int OptionMenuPrincipal = 0;

void menuPrincipal(RenderWindow * window,Event e,int& option) {
	

	RectangleShape fundo(Vector2f(SCREEN_WIDTH,SCREEN_HEIGHT));
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
	title.setPosition(SCREEN_WIDTH/1.4 - title.getGlobalBounds().width / 2,SCREEN_HEIGHT/6.9);
	title.setFillColor(redText);

	//options
	Color redOption(193, 0, 0);
	Font fontOption;
	fontOption.loadFromFile("fonts/blops.ttf");

	Text option1;
	option1.setFont(fontOption);
	option1.setString("Iniciar");
	option1.setCharacterSize(SCREEN_WIDTH / 48);
	option1.setPosition(SCREEN_WIDTH / 1.4 - option1.getGlobalBounds().width/2, SCREEN_HEIGHT / 2);
	option1.setFillColor(redOption);

	Text option2;
	option2.setFont(fontOption);
	option2.setString("Ajustes");
	option2.setCharacterSize(SCREEN_WIDTH / 48);
	option2.setPosition(SCREEN_WIDTH / 1.4  - option2.getGlobalBounds().width / 2,
						SCREEN_HEIGHT / 2 + option1.getGlobalBounds().height*2);

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
	garra.setScale((float)1 /(SCREEN_WIDTH /640), 1 / (float)(SCREEN_HEIGHT/360));
	

	//checking for garrinha
	int mousex;
	int mousey;
	

	
	mousex = e.mouseMove.x;
	mousey = e.mouseMove.x;
	
	int spaceBetween = garra.getGlobalBounds().width;
	if ((mousex > SCREEN_WIDTH / 1.4 - option1.getGlobalBounds().width / 2) &&
		(mousex < SCREEN_WIDTH / 1.4 + option1.getGlobalBounds().width) && (
		(mousey > SCREEN_HEIGHT / 2) && (mousey < SCREEN_HEIGHT / 2 + option1.getGlobalBounds().height)))
	{
		garra.setPosition(SCREEN_WIDTH / 1.4 - option1.getGlobalBounds().width / 2 - spaceBetween,
			SCREEN_HEIGHT / 2);
	}

	if (e.type == Event::KeyPressed)
	{
		if (e.key.code == Keyboard::W)
		{	
			OptionMenuPrincipal--;
			if (OptionMenuPrincipal < 0)
			OptionMenuPrincipal = 2;
		}
		else if (e.key.code == Keyboard::W) {
			OptionMenuPrincipal++;
			if (OptionMenuPrincipal > 2)
				OptionMenuPrincipal = 0;
		}
	}

	switch (OptionMenuPrincipal)
	{
	case 0:
		garra.setPosition(SCREEN_WIDTH / 1.4 - option1.getGlobalBounds().width / 2 - spaceBetween,
		SCREEN_HEIGHT / 2);
		break;
	case 1:
		garra.setPosition(SCREEN_WIDTH / 1.4 - option3.getGlobalBounds().width / 2 - spaceBetween,
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