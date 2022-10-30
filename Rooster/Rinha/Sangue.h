
namespace Rooster {

	
		Texture star;
		Sprite estrelinha;
			
		
		void drawEstrelinhas(RenderWindow * window,Vector2f position) {
			star.loadFromFile("sprites\\estrelinhas.png");
			estrelinha.setTexture(star);
						
			static int frames = 0;
			frames++;
			if (frames > 60) {
				frames = 0;
			}
			int frameTime = frames % 11 - 5;
			if (frames == 5) {
				estrelinha.setScale(-10, 10);
				
			}
			else if(frames == -5) {
				estrelinha.setScale(10, 10);
			}
			
			estrelinha.setPosition(0, 0);
			window->draw(estrelinha);
			
			
		}
		
	
	class Particle {


	public:
		Vector2f position;

		float depthStart = 100;
		float depth = 100;
		float depthSpd = 0;

		float depthChange = 0.5;

		float hSpeed = 0;
		float vSpeed = 0;
		float vAcc = 0;
		float hAcc = 0;

		float maxHspd = 10;
		float maxVspd = 10;


		float ang = 0;
		float angSpeed = 0;
		float angAcc = 0;

		float angFriction = 0.999;

		float friction = 0.999;

		bool fixed = false;

		int maxLife = 500;
		int life = 500;

		float alpha = 1;

		bool fadeInAlpha = false;
		bool fadeOutAlpha = true;

		bool mortal = true;
		float active = false;



		bool hasSprite = false;


		float sprScl;
		Vector2f sprCenter;
		Sprite sprite;


		Color color;
		float radius = 10;

		CircleShape point;





		Particle(Color color) {
			point.setRadius(1);
			this->color = color;
			point.setFillColor(color);
			active = true;

		}
		Particle() {
			point.setRadius(10);
			color = Color::Red;
			point.setFillColor(color);
			active = true;

		}
		void setPosition(Vector2f position) {
			this->position = position;
		}
		void setPosition(float x, float y) {
			this->position.x = x;
			this->position.y = y;
		}
		Vector2f getPosition() {
			return position;
		}
		void setImpulse(float hSpeed, float vSpeed) {
			this->hSpeed = hSpeed;
			this->vSpeed = vSpeed;
		}

		void addImpulse(float hSpeed, float vSpeed) {
			this->hSpeed += hSpeed;
			this->vSpeed += vSpeed;
		}



		void update() {

			if (active) {

				if (!fixed) {
					hSpeed += hAcc;
					vSpeed += vAcc;
					ang += angSpeed;

					hSpeed *= friction;
					vSpeed *= friction;
					angSpeed *= angFriction;


					hSpeed = constrain(hSpeed, -maxHspd, maxHspd);
					vSpeed = constrain(vSpeed, -maxVspd, maxVspd);

					position.x += hSpeed;
					position.y += vSpeed;
					ang += angSpeed;


					depth -= depthSpd;

					if (depth <= 0) {
						depth = 0;
						fixed = true;
					} 

				}





				if (fadeInAlpha && life < maxLife/3) {
					alpha = minimum((float)life / ((float)maxLife / 3), 1);
				} else if (fadeOutAlpha && life > 2*maxLife/3) {
					alpha = 1 - minimum((float)life-(2*(float)maxLife/3) / ((float)maxLife / 3), 1);
				}
				else {
					alpha = 1;
				}

				Color col = color;
				col.a = 255 * alpha;

				if (hasSprite) {
					sprite.setColor(col);
					sprite.setPosition(position.x, position.y);
					sprite.setOrigin(sprCenter * sprScl);
					sprite.setRotation(ang);
					sprite.setScale(sprScl, sprScl);
				}
				else {

					float rad = radius *( 1+(depthChange * (1 - (depth / depthStart))));
					
					point.setFillColor(col);
					point.setPosition(position.x, position.y);
					point.setOrigin(rad, rad);
					point.setRadius(rad);
				}

				life -= mortal;

				if (life < 0) {
					active = false;
				}
			}

		}
		void draw(RenderWindow& window) {

			if (active) {
				if (hasSprite) {
					window.draw(sprite);
				}
				else {
					window.draw(point);
				}
			}
		}


		void draw(RenderWindow& window, Vector2f offset) {

			if (active) {
				if (hasSprite) {
					sprite.setPosition(sprite.getPosition().x + offset.x, sprite.getPosition().y + offset.y);

					window.draw(sprite);
				}
				else {
					point.setPosition(point.getPosition().x + offset.x, point.getPosition().y + offset.y);

					window.draw(point);
				}
			}
		}




	};


	class Effect {
	protected:
		std::vector <Particle> gotas;
		Vector2f position;
		Vector2f gravity;
		bool fadeOutAlpha = true;
		bool fadeInAlpha = false;
		


	public:

		bool active = true;
		int life = 100;
		float depth = 0;

		~Effect() {
			gotas.clear();
		}

		void setPosition(Vector2f position) {
			this->position = position;
		}
		void setPosition(float x, float y) {
			this->position.x = x;
			this->position.y = y;
		}

		virtual void update() = 0;
		virtual void draw(RenderWindow& window) = 0;

	};



	class AreaEffect : public Effect {
		FloatRect area;

		Color color;

	public:

		AreaEffect(FloatRect area, Color cor) {
			this->area = area;

			color = cor;
		}

		void createParticle(){

			int diameter = randFloatRange(1, 3);

			life = 250;

			gravity.x = 0;
			gravity.y = Gravity / 40;

			Particle p(color);


			float pX = randIntRange(area.left, area.left + area.width);
			float pY = randIntRange(area.top, area.top + area.height);

			float pAngle = randFloatRange(0, 180);
			float pSpd = randFloatRange(2, 6);

			float pHspd = pSpd*cos(toRadiAnus(pAngle));
			float pVspd = -pSpd*sin(toRadiAnus(pAngle));

			p.setPosition(pX, pY);

			p.vAcc = gravity.y;
			p.hAcc = gravity.x;

			p.fadeOutAlpha = false;
			p.fadeInAlpha = true;

			p.mortal = true;

			p.life = randIntRange(100, 250);
			p.maxLife = p.life;

			p.maxHspd = 40;
			p.maxVspd = 40;

			p.radius = randFloatRange(1, 10);

			

			p.setImpulse(pHspd, pVspd);


			gotas.push_back(p);
			

		}



		void update() override {
			for (int i = 0; i < gotas.size(); i++) {
				gotas[i].update();
			}

		}

		void draw(RenderWindow& window) override {
			for (int i = 0; i < gotas.size(); i++) {
				gotas[i].draw(window);
			}
		}

	};





	class ExplosionEffect : public Effect {
		float radius;
		Vector2f center;
		Vector2f impact;

	public:


		ExplosionEffect(float radius, Vector2f center, Color cor, Vector2f impactForce, float explosionForce, float angle, float angleFocus) {
			int diameter = radius * 2;

			life = 100;

			gravity.x = 0;
			gravity.y = Gravity / 80;

			for (int i = 0; i < 500; i++) {


				Particle p(Color::Red);

				p.setPosition(center);

				p.vAcc = gravity.y;
				p.hAcc = gravity.x;

				p.fadeOutAlpha = false;
				p.fadeInAlpha = true;

				p.mortal = true;

				p.life = randIntRange(50, 150);
				p.maxLife = p.life;

				p.maxHspd = 40;
				p.maxVspd = 40;

				p.radius = randIntRange(1, 10);

				float ang = toRadiAnus(randFloatRangeNormal(angle - 180, angle + 180, angleFocus));


				float impact = randFloat(explosionForce);

				p.setImpulse(
					(cos(ang) * impact) + impactForce.x,
					(sin(ang) * impact) + impactForce.y
				);


				gotas.push_back(p);
			}

		}


		void setRadius(float radius) {
			this->radius = radius;
		}

		void update() override {
			for (int i = 0; i < gotas.size(); i++) {
				gotas[i].update();			}

		}

		void draw(RenderWindow& window) override {
			for (int i = 0; i < gotas.size(); i++) {
				gotas[i].draw(window);
			}
		}
	};


	class Explosion3DEffect : public Effect {
		float radius;
		Vector2f center;
		Vector2f impact;

	public:


		Explosion3DEffect(float radius, Vector2f center, Color cor, Vector2f impactForce, float explosionForce, float angle, float angleFocus) {
			int diameter = radius * 2;

			life = 100;

			gravity.x = 0;
			gravity.y = Gravity / 80;

			for (int i = 0; i < 500; i++) {


				Particle p(Color::Red);

				p.setPosition(center);

				p.vAcc = gravity.y;
				p.hAcc = gravity.x;

				p.fadeOutAlpha = false;
				p.fadeInAlpha = true;

				p.mortal = true;

				p.life = randIntRange(300, 600);
				p.maxLife = p.life;

				p.maxHspd = 40;
				p.maxVspd = 40;

				p.depthSpd = randFloatRange(-1, 4);

				p.radius = randIntRange(1, 10);

				float ang = toRadiAnus(randFloatRangeNormal(angle - 180, angle + 180, angleFocus));


				float impact = randFloat(explosionForce);

				p.setImpulse(
					(cos(ang) * impact) + impactForce.x,
					(sin(ang) * impact) + impactForce.y
				);


				gotas.push_back(p);
			}

		}


		void setRadius(float radius) {
			this->radius = radius;
		}

		void update() override {
			for (int i = 0; i < gotas.size(); i++) {
				gotas[i].update();
			}

		}

		void draw(RenderWindow& window) override {
			for (int i = 0; i < gotas.size(); i++) {
				gotas[i].draw(window);
			}
		}
	};














	class ParticleSystem {


	public:
		std::vector<Effect*> effects;

		ParticleSystem() {

		}

		void update() {
			for (int i = 0; i < effects.size(); i++) {
				effects[i]->update();
			}


			for (int i = 0; i < effects.size(); i++) {
				if (!effects[i]->active) {
					removeEffect(i);
				}
			}

		}


		void draw(RenderWindow& window) {
			for (int i = 0; i < effects.size(); i++) {
				effects[i]->draw(window);
			}
		}


		void removeEffect(int effectId) {
			delete effects[effectId];
			effects.erase(effects.begin() + effectId);
		}

		void clear() {
			for (int i = 0; i < effects.size(); i++) {
				delete effects[i];
			}

			effects.clear();
		}


	};

	class corvo {
		Texture Corvo;
		Sprite sprite;
		float hspd;
		float vspd;
		Vector2f position;
		Vector2f scl;
	public:
		corvo(float hspd, float vspd, Vector2f position, Vector2f scl) {
			this->hspd = hspd;
			this->vspd = vspd;
			this->position = position;
			this->scl = scl;
			Corvo.loadFromFile("sprites/corvo.png");
			sprite.setTexture(Corvo);

		}
		void update() {

			int sizeCorvo[3] = { 500,748,643 };
			position.x += hspd;
			position.y += vspd;

			static int Frames = 0;
			Frames++;
			int sprSelected = (Frames / 600) % 3;
			int sprx = 0;

			if (sprSelected == 0) {
				sprx = 0;
			}
			else if (sprSelected == 1) {
				sprx = 500;
			}
			else if (sprSelected == 2) {
				sprx = 500 + 748;
			}

			sprite.setTextureRect(IntRect(sprx, 0, sizeCorvo[sprSelected], 829));
			if (hspd > 0) {
				if (scl.x > 0) {
					scl.x *= -1;
				}
			}
			sprite.setScale(scl);
			sprite.setRotation(-sin(vspd));

			sprite.setPosition(position);
		}
		void setColor(Color cor) {
			sprite.setColor(cor);
		}
		void draw(RenderWindow* window) {

			window->draw(sprite);
		}
	};

	class chuva {
		CircleShape gota;
		float hspd;
		float vspd;
		
	public:
		Vector2f position;
		chuva() {
			this->hspd = randFloatRange(0, 2);
			this->vspd = randFloatRange(1, 10);
			position.x = rand() % SCREEN_WIDTH;
			position.y = -10;
			gota.setRadius(1);
			gota.setFillColor(Color::Blue);

		}
		void update() {

			position.x += hspd;
			position.y += vspd;
			if (position.y > SCREEN_HEIGHT + 50) {
				position.y = -10;
			}
			else if (position.x > SCREEN_WIDTH + 50) {
				position.x = rand() % SCREEN_WIDTH;
			}
			gota.setPosition(position);

		}
		void draw(RenderWindow* window) {

			window->draw(gota);
		}
		
	};
	class effectsChuva {
		std::vector <chuva> chuvinha;
	public:
		effectsChuva() {
			for (int i = 0; i < 500; i++) {
				chuva *a = new chuva;
				chuvinha.push_back(*a);
			}
		}
		void update() {
			for (int i = 0; i < chuvinha.size(); i++) {
				chuvinha[i].update();			
			}
		}
		void draw(RenderWindow* window) {
			for (int i = 0; i < chuvinha.size(); i++) {
				chuvinha[i].draw(window);
			}
		}
	};
	class rato {
		Texture ratinho;
		Sprite sprite;
		float hspd;
		float vspd;
		Vector2f position;
		Vector2f scl;
	public:
		rato(float hspd, float vspd, Vector2f position, Vector2f scl) {
			this->hspd = hspd;
			this->vspd = vspd;
			this->position = position;
			this->scl = scl;
			ratinho.loadFromFile("sprites/rato.png");
			sprite.setTexture(ratinho);

		}
		void update() {

			int sizeRato[3] = {858,858,877 };
			position.x += hspd;
			position.y += vspd;

			static int Frames = 0;
			Frames++;
			int sprSelected = (Frames / 600) % 3;
			int sprx = 0;

			if (sprSelected == 0) {
				sprx = 0;
			}
			else if (sprSelected == 1) {
				sprx = 858;
			}
			else if (sprSelected == 2) {
				sprx = 858 + 858;
			}

			sprite.setTextureRect(IntRect(sprx, 0, sizeRato[sprSelected], 606));
			if (hspd > 0) {
				if (scl.x > 0) {
					scl.x *= -1;
				}
			}
			sprite.setScale(scl);
			sprite.setRotation(-sin(vspd));

			sprite.setPosition(position);
		}
		void setColor(Color cor) {
			sprite.setColor(cor);
		}
		void draw(RenderWindow* window) {

			window->draw(sprite);
		}
	};
	class effectsInfestacaoDeRatos {
		std::vector <rato> ratos;
	public:
		class effectsInfestacaoDeRatos(){
			for (int i = 0; i < 100; i++) {
				int right = rand() % 2;
//				rato* a = new rato(randIntRange(5,10) - right*15,0,Vector2f(right*SCREEN_WIDTH,floorY),Vector2f(0.2,0.2));
				//ratos.push_back(*a);
			}
		}
		void update() {
			for (int i = 0; i < ratos.size(); i++) {
				ratos[i].update();
			}
		}
		void draw(RenderWindow* window) {
			for (int i = 0; i < ratos.size(); i++) {
				ratos[i].draw(window);
			}
		}
	};
	
}