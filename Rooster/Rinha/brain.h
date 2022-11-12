#ifndef BURRICE_ARTIFICIAL
#define BURRICE_ARTIFICIAL

/*usando os inputs  da entradas.h vamos ver o que da pra fazer
a funcao update recebe o input e ja possue o galo e pode pegar
tais informações pra destruir seu inimigo*/


/*i dont really know what im doing*/
class Brain {
protected:
	//o input que enviamos
	int input;

	//nosso galinho
	Galo* galinho;

	/* o galo de outra pessoa
	para ver diversas informacoes*/	
	Galo* galo;
	
	
	//a nota que cada input vai receber
	float grade[INPUTSTOTAL];

public:
	Brain(Galo* galinho,Galo* galo) {
		this->galo = galo;
		this->galinho = galinho;
	}
	//perai
	virtual void think() = 0;

	//avalia se pular eh a melhor solucao
	virtual void jump() = 0;
	
	//avalia se bater eh a melhor solucao
	virtual void lightAtack() = 0;

	//avalia se golpe baixo eh a melhor solucao
	virtual void lowAtack() = 0;

	//avalia se socar com força eh a melhor solucao
	virtual void strongAtack() = 0;

	//avalia se a esquerda eh melhor solucao
	virtual void goLeft() = 0;

	//avalia se a direita eh a menos pior opcao
	virtual void goRight() = 0;

	//vai que ne 
	virtual void dance() = 0;

	//se defender é bom sempre ne
	virtual void defend() = 0;

	

	/*eh dando que se recebe*/
	int update() {
			
		think();
		return this->input;
	}
	

};

class SniperBrain : public Brain {

	//fstream* lastNotas;

	/*vamos ver o que a gente consegue fazer aqui*/
	float lastGrades[10];
	//leia essas notas pra ca

public:
	SniperBrain(Galo* galinho, Galo* galo) :Brain(galinho, galo) {

		/*
		const char* path = "Machine unlearning\\sniperGrades.txt";
		
		fstream* file = new fstream(path, ios::in);
		
		//Ele vai apagar e gravar por cima
		//Vou mudar de quarto aq
		//vão dormir aq
		for (int i = 0; i < 10; i++) { //são 9
			string line;
			getline(*file, line);

			println("_______________________PICA");
			lastGrades[i] = atof(line.c_str());//Foi na sorte
			println("PICA");
			println(atof(line.c_str()));
			//oq agora?//
			// 
			//isso ta certo???????????????
			//Ele vai gravar por cima do outro
			
		}
		
		file->close();
		println("apague pow o ponteiro");
		delete file;
		println("ta vendo");
		try {
			lastNotas = new fstream(path, ios::out | ios::app);
			// isso so nao ta mais errado pq naoo fuu eu que fix kkkkkkkkkkkk aprenda agr
		}
		catch (...) {
			//já entendi tudo
			//mds aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
			println("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");//vou tomar uma agua rapidao
		}
		println("quebrou aqui oh se kligue");
		*/
		int notas[10] = { 1,1,4,5,6,1,1,0.5,1,1 };
		for (int i = 0; i < 10; i++) {
			lastGrades[i] = notas[i];
		}
		
	}
	
	//sem ele nao pega
	virtual void think() override {

		jump();

		if (galinho->atacking == NOT_ATTACK) {
			lightAtack();
			lowAtack();
			strongAtack();
		}
	
		goLeft();
		goRight();
		dance();
		defend();

		int bestGrade = 0;
		for (int i = 0; i < 8; i++) {
			if (grade[i] > bestGrade) {
				bestGrade = i;
			}
		}
		clearGrades();
		//updateGrades(bestGrade);
		input = bestGrade;

	}
	void clearGrades() {
		for (int i = 0; i < 10; i++) {
			grade[i] = 0;
		}
	}
	void updateGrades(int bestGrade) {
		if (galo->gethp() < galinho->gethp()) {
			switch (bestGrade)
			{
			case 0:
				lastGrades[0] += 0.01;
				lastGrades[1] += 0.01;
				break;
			case 1:
				lastGrades[2] += 0.01;				
			break;
			case 2:
				lastGrades[3] += 0.01;
				break;
			case 3:
				lastGrades[4] += 0.01;
				break;
			case 4:
				lastGrades[5] += 0.01;
				break;
			case 5:
				lastGrades[6] += 0.01;
				break;
			case 6:
				lastGrades[7] += 0.01;
				break;
			case 7:
				lastGrades[8] += 0.01;
				lastGrades[9] += 0.01;
				break;
			}
		}
		else {
			switch (bestGrade)
			{
			case 0:
				lastGrades[0] -= 0.01;
				lastGrades[1] -= 0.01;
				break;
			case 1:
				lastGrades[2] -= 0.01;
				break;
			case 2:
				lastGrades[3] -= 0.01;
				break;
			case 3:
				lastGrades[4] -= 0.01;
				break;
			case 4:
				lastGrades[5] -= 0.01;
				break;
			case 5:
				lastGrades[6] -= 0.01;
				break;
			case 6:
				lastGrades[7] -= 0.01;
				break;
			case 7:
				lastGrades[8] -= 0.01;
				lastGrades[9] -= 0.01;
				break;
			}
		}

		//lastNotas->seekp(0);
		for (int i = 0; i < 10; i++) {
			cout << lastGrades[i] << endl;
		}

		// ah mas tipo

	}

	//avalia se pular eh a melhor solucao
	virtual void jump() {
		for (int i = 0; i < galo->projectiles.size(); i++) {
			if (galo->projectiles[i].getVisibility() && abs(galinho->position.x - galo->projectiles[i].getPosition().x) < 500) {

				grade[0] += 3;

			}
		}
		if (galo->louKick->isAtacking) {
			grade[0] += 3;
		}
	}

	//avalia se bater eh a melhor solucao
	virtual void lightAtack() {
		if (abs(galo->position.x - galinho->position.x) < galinho->model.getBounds().width + 300) {
			grade[1] += 6;
		}
	}

	//avalia se golpe baixo eh a melhor solucao
	virtual void lowAtack() {
		if (abs(galo->position.x - galinho->position.x) < galinho->model.getBounds().width + 100) {
			grade[2] += 8;
		}
	}

	//avalia se socar com força eh a melhor solucao
	virtual void strongAtack() {
		if (abs(galo->position.x - galinho->position.x) > SCREEN_WIDTH / 3) {
			grade[3] += 10;
		}
	}

	//avalia se a esquerda eh melhor solucao
	virtual void goLeft() {
		if ((galo->position.x - galinho->position.x) < 0 && galinho->facingRight) {
			grade[4] += 12;
		}
		if ((galo->position.x - galinho->position.x) < SCREEN_WIDTH / 2) {
			grade[4] += 1;
		}

	}

	//avalia se a direita eh a menos pior opcao
	virtual void goRight() {
		if ((galo->position.x - galinho->position.x) > 0 && !galinho->facingRight) {
			grade[5] += 12;
		}

		if ((galo->position.x - galinho->position.x) > SCREEN_WIDTH / 2) {
			grade[5] += 1;
		}
	}

	virtual void dance() {
		if (galo->position.x - galinho->position.x > SCREEN_WIDTH / 1.2) {
			grade[6] += 0.5;
		}
	}

	virtual void defend() {
		if (galo->atacking != NOT_ATTACK) {
			grade[7] += 2;
		}

		for (int i = 0; i < galo->projectiles.size(); i++) {
			if (galo->projectiles[i].getVisibility() && abs(galinho->position.x - galo->projectiles[i].getPosition().x) < 500) {
				grade[7] += 2;
			}
		}
		
	}

};


#endif // BURRICE_ARTIFICIAL

