
namespace Rooster {


	struct PartTextures {
		Texture flower;
		//Texture dust;
		

		void init() {
			flower.loadFromFile("sprites/flowerSmall.png");
			//.loadFromFile("sprites/");
		}
	};

	struct PartTextures partTextures;



	// Credits to Tenry on https://en.sfml-dev.org/forums/index.php?topic=7313.0
	// hue: 0-360°; sat: 0.f-1.f; val: 0.f-1.f
	sf::Color hsv(int hue, float sat, float val)
	{
		hue %= 360;
		while (hue < 0) hue += 360;

		if (sat < 0.f) sat = 0.f;
		if (sat > 1.f) sat = 1.f;

		if (val < 0.f) val = 0.f;
		if (val > 1.f) val = 1.f;

		int h = hue / 60;
		float f = float(hue) / 60 - h;
		float p = val * (1.f - sat);
		float q = val * (1.f - sat * f);
		float t = val * (1.f - sat * (1 - f));

		switch (h)
		{
		default:
		case 0:
		case 6: return sf::Color(val * 255, t * 255, p * 255);
		case 1: return sf::Color(q * 255, val * 255, p * 255);
		case 2: return sf::Color(p * 255, val * 255, t * 255);
		case 3: return sf::Color(p * 255, q * 255, val * 255);
		case 4: return sf::Color(t * 255, p * 255, val * 255);
		case 5: return sf::Color(val * 255, p * 255, q * 255);
		}
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

		bool isHSV = false;
		float hue = 0;
		float sat = 0;
		float light = 0;


		bool fadeInAlpha = false;
		bool fadeOutAlpha = true;

		bool mortal = true;
		bool active = false;



		

		float scl = 1;

		bool hasSprite = false;
		Vector2f sprCenter;
		Sprite sprite;

		bool hasText = false;
		Text text;


		float radius = 10;

		Color color;

		CircleShape point;





		Particle(Color color) {
			this->color = color;
			point.setFillColor(color);
			active = true;

		}

		Particle() {
			color = Color::Red;
			point.setFillColor(color);
			active = true;

		}
		



		void update() {

			if (active) {

				if (isHSV) {
					color = hsv(hue, sat, light);
				}

				if (!fixed) {
					hSpeed += hAcc;
					vSpeed += vAcc;
					angSpeed += angAcc;

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



				float third = (float)1 / 3;
				float lifePerc = 1 - (float)life / maxLife;

				float alphaMult = 1;

				if (lifePerc <= third && fadeInAlpha) {
					alphaMult = ruleOfThree(lifePerc, 0, third, 0, 1);
				}
				
				if (lifePerc > 2*third && fadeOutAlpha) {
					alphaMult = ruleOfThree(lifePerc, 2*third, 1, 1, 0);
				}

			







				Color col = color;
				col.a = 255 * alpha * alphaMult;

				float depthFactor = (1 + (depthChange * (1 - (depth / depthStart))));

				float scale = scl * depthFactor;
				

				if (hasText) {
					text.setColor(col);
					text.setPosition(position.x, position.y);
					text.setRotation(ang);
					text.setScale(scale, scale);
				} else if (hasSprite) {

					

					sprite.setColor(col);
					sprite.setPosition(position.x, position.y);
					//sprite.setOrigin(sprCenter);
					sprite.setRotation(ang);
					sprite.setScale(scale, scale);

				}
				else {

					float rad = radius * scale;
					
					point.setFillColor(col);
					point.setPosition(position.x, position.y);
					point.setOrigin(rad, rad);
					point.setRadius(rad);
					//println(rad);
				}

				life -= mortal;

				if (life < 0) {
					active = false;
				}
			}

		}
		void draw(RenderWindow& window) {

			if (active) {

				if (hasText) {
					window.draw(text);
				} else if (hasSprite) {
					window.draw(sprite);
				}
				else {
					window.draw(point);
				}
			}
		}




	};


	class Effect {
	protected:
		std::vector <Particle> gotas;

	public:

		// Particle Creation vars
		Vector2f position;
		Vector2f gravity;

		float angleMin = 0;
		float angleMax = 0;

		float angleSpeedMin = 0;
		float angleSpeedMax = 0;

		float angleFriction = 1;

		float hspeedMin = 0;
		float hspeedMax = 0;

		float vspeedMin = 0;
		float vspeedMax = 0;

		float hspeedLimit = 10;
		float vspeedLimit = 10;

		float lifeMin = 10;
		float lifeMax = 10;

		float xOffsetMin = 0;
		float xOffsetMax = 0;

		float yOffsetMin = 0;
		float yOffsetMax = 0;


		bool partMortal = true;


		
		float sclMin = 1;
		float sclMax = 1;

		float friction = 1;

		float depthMin = 0;
		float depthMax = 0;

		float depthSpdMin = 0;
		float depthSpdMax = 0;


		bool isHSV = false;

		float hueMin = 0;
		float hueMax = 255;
		
		float lightMin = 0;
		float lightMax = 1;

		float satMin = 1;
		float satMax = 1;


		Color color;

		bool hasSprite = false;
		Sprite sprite;

		bool hasText = false;
		Text text;



		bool fadeOutAlpha = true;
		bool fadeInAlpha = false;


	


		// Effect Vars
		bool active = true;

		int life = 600;

		bool mortal = true;

		float depth = 0;

		


		~Effect() {
			
			gotas.clear();
		}


		void copyEffect(Effect e) {
			gravity = e.gravity;

			angleMin = e.angleMin;
			angleMax = e.angleMax;

			hspeedMin = e.hspeedMin;
			hspeedMax = e.hspeedMax;

			vspeedMin = e.vspeedMin;
			vspeedMax = e.vspeedMax;

			lifeMin = e.lifeMin;
			lifeMax = e.lifeMax;



			sclMin = e.sclMin;
			sclMax = e.sclMax;

			friction = e.friction;

			depthMin = e.depthMin;
			depthMax = e.depthMax;

			depthSpdMin = e.depthSpdMin;
			depthSpdMax = e.depthSpdMax;


			isHSV = e.isHSV;

			hueMin = e.hueMin;
			hueMax = e.hueMax;

			lightMin = e.lightMin;
			lightMax = e.lightMax;


			color = e.color;



			fadeOutAlpha = e.fadeOutAlpha;
			fadeInAlpha = e.fadeInAlpha;

		}

		void sanguePreset() {
			gravity = Vector2f(0, 0.2);

			angleMin = 0;
			angleMax = 0;

			hspeedMin = 0;
			hspeedMax = 0;

			vspeedMin = 0;
			vspeedMax = 0;

			lifeMin = 100;
			lifeMax = 350;



			sclMin = 0.5;
			sclMax = 2;

			friction = 0.98;

			depthMin = 100;
			depthMax = 100;

			depthSpdMin = 0;
			depthSpdMax = 0;


			isHSV = false;

			hueMin = 0;
			hueMax = 0;

			lightMin = 0;
			lightMax = 0;


			color = Color::Red;



			fadeOutAlpha = true;
			fadeInAlpha = false;

		}

		void tilesPreset() {
			sanguePreset();

			sclMax = 1.25;
			sclMin = 0.4;

			hspeedMin = -3;
			hspeedMax = 3;
			vspeedMin = -4;
			vspeedMax = 2;
		}

		void floresPreset() {
			tilesPreset();

			color = Color::White;

			hasSprite = true;
			sprite.setTexture(partTextures.flower);
			sclMin = 0.2;
			sclMax = 0.8;
			angleMin = 0;
			angleMax = 360;
			angleSpeedMin = -5;
			angleSpeedMax = 5;

			fadeInAlpha = true;
			fadeOutAlpha = true;

			angleFriction = 0.98;

			sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
		}

		void textPreset() {
			hasText = true;
			text.setString("Particle");
			text.setFont(basicFont);
		}

		void poeiraPreset() {
			tilesPreset();
			gravity.x = 0;
			gravity.y = 0;

			hspeedMin = -0.25;
			hspeedMax = 0.25;

			vspeedMin = -0.25;
			vspeedMax = 0.25;

			friction = 0.95;

			sclMax = 1.5;
			sclMin = 1;

			lifeMin = 20;
			lifeMax = 40;

			isHSV = true;
			hueMax = 54;
			hueMin = 54;
			satMax = 0.3;
			satMin = 0.2;
			lightMax = 1;
			lightMin = 0.8;
		}

		void spreadPreset(float xSpread, float ySpread) {
			xOffsetMax = xSpread / 2;
			xOffsetMin = -xOffsetMax;

			yOffsetMax = ySpread / 2;
			yOffsetMin = -yOffsetMax;

		}


		void addParticle(struct Particle p) {
			if (gotas.size() < 2000) {
				gotas.push_back(p);
			}
		}

		void createBaseParticle() {

			if (gotas.size() < 2000) {
				struct Particle p;
				p.position.x = position.x + randFloatRange(xOffsetMin, xOffsetMax);
				p.position.y = position.y + randFloatRange(yOffsetMin, yOffsetMax);

				p.scl = randFloatRange(sclMin, sclMax);
				

				p.alpha = 1;

				p.ang = randFloatRange(angleMin, angleMax);
				p.angSpeed = randFloatRange(angleSpeedMin, angleSpeedMax);
				p.angFriction = angleFriction;


				p.life = randFloatRange(lifeMin, lifeMax);
				p.maxLife = p.life;
				p.hSpeed = randFloatRange(hspeedMin, hspeedMax);
				p.vSpeed = randFloatRange(vspeedMin, vspeedMax);

				p.maxHspd = hspeedLimit;
				p.maxVspd = vspeedLimit;


				p.vAcc = gravity.y;
				p.hAcc = gravity.x;

				p.depth = randFloatRange(depthMin, depthMax);
				p.depthSpd = randFloatRange(depthSpdMin, depthSpdMax);

				p.fadeInAlpha = fadeInAlpha;
				p.fadeOutAlpha = fadeOutAlpha;

				if (isHSV) {
					p.hue = randFloatRange(hueMin, hueMax);
					p.sat = randFloatRange(satMin, satMax);
					p.light = randFloatRange(lightMin, lightMax);
					p.isHSV = true;
				}
				else {
					p.color = color;
					p.isHSV = false;
				}

				if (hasSprite) {
					p.sprite = sprite;
					p.hasSprite = true;
				}

				if (hasText) {
					p.text = text;
					p.hasText = true;
				}

				p.mortal = partMortal;

				p.active = true;

				gotas.push_back(p);
			}
		}

		virtual void createParticle() {
			createBaseParticle();
		}


		void createMultipleParticles(int particleNumber) {
			for (int i = 0; i < particleNumber; i++) {
				createParticle();
			}
		}

		void update(){
			for (int i = gotas.size()-1; i > -1; i--) {
				if (gotas[i].active) {
					gotas[i].update();
				}
				else {
					gotas.erase(gotas.begin() + i);
				}
				
			}

			// Morte do efeito
			if (mortal) {
				life--;
				if (life <= 0) {
					active = false;
				}
			}

		}

		virtual void draw(RenderWindow& window) {
			for (int i = 0; i < gotas.size(); i++) {
				gotas[i].draw(window);
			}
		}

	};



	class AreaEffect : public Effect {
		FloatRect area;


	public:

		AreaEffect(FloatRect area, Color cor) {
			this->area = area;

			this->color = cor;
		}

		void createParticle(Particle p) {

			float pX = randIntRange(area.left, area.left + area.width);
			float pY = randIntRange(area.top, area.top + area.height);

			p.position = Vector2f(pX, pY);

			gotas.push_back(p);
		}

		void createParticle() override{

			createBaseParticle();

			Particle& p = gotas[gotas.size() - 1];

			float pX = randIntRange(area.left, area.left + area.width);
			float pY = randIntRange(area.top, area.top + area.height);

			p.position = Vector2f(pX, pY);
		}




	};





	class ExplosionEffect : public Effect {

		float impactAngle;
		float impactForce;

		float radialForce;

		bool radialHasAngle;
		float radialAngle;
		float radialAngleVariation;


	public:


		ExplosionEffect(Vector2f explosionPosition, float radialForce, float radialAngle, float radialAngleVariation, float impactForce, float impactAngle) {
			
			position = explosionPosition;
			
			this->impactForce = impactForce;
			this->impactAngle = impactAngle;

			this->radialForce = radialForce;

			radialHasAngle = true;
			this->radialAngle = radialAngle;
			this->radialAngleVariation = radialAngleVariation;
		}

		ExplosionEffect(Vector2f explosionPosition, float radialForce, float impactForce, float impactAngle) {

			position = explosionPosition;

			this->impactForce = impactForce;
			this->impactAngle = impactAngle;

			this->radialForce = radialForce;

			radialHasAngle = false;
		}

		ExplosionEffect(Vector2f explosionPosition, float radialForce) {

			position = explosionPosition;

			this->radialForce = radialForce;

			radialHasAngle = false;
		}

		ExplosionEffect() {
			radialForce = 10;
			impactForce = 0;
			impactAngle = 0;
			radialHasAngle = false;
		}




		void createParticle() override {

			createBaseParticle();

			Particle& p = gotas[gotas.size() - 1];


			p.position = position;

			p.mortal = true;

			p.maxHspd = 40;
			p.maxVspd = 40;


			// Explosion Stuff

			float ang = toRadiAnus(randFloat(360));
			if (radialHasAngle) {
				ang = toRadiAnus(randFloatRangeNormal(radialAngle-radialAngleVariation/2, radialAngle + radialAngleVariation / 2, radialAngleVariation / 4));
			}

			float impAng = toRadiAnus(impactAngle);
			float impactHspd = cos(impAng) * impactForce;
			float impactVspd = sin(impAng) * impactForce;


			float radForce = randFloat(radialForce);

			p.hSpeed = (cos(ang) * radForce) + impactHspd;
			p.vSpeed = (sin(ang) * radForce) + impactVspd;
		}

	};




	class ParticleSystem {

	std::vector<Effect*> effects;

	public:

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

		void sortDepth() {

		}

		void addEffect(Effect* effect) {
			effects.push_back(effect);
			sortDepth();
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
		
		Sprite sprite;
		float hspd;
		float vspd;
		Vector2f position;
		Vector2f scl;
	public:
		corvo(float hspd, float vspd, Vector2f position, Vector2f scl,Texture &Corvo) {
			this->hspd = hspd;
			this->vspd = vspd;
			this->position = position;
			this->scl = scl;
			
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
		
		Sprite sprite;
		float hspd;
		float vspd;
		Vector2f position;
		Vector2f scl;
	public:
		rato(float hspd, float vspd, Vector2f position, Vector2f scl,Texture *t) {
			this->hspd = hspd;
			this->vspd = vspd;
			this->position = position;
			this->scl = scl;
			
			sprite.setTexture(*t);

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
			if (position.x > SCREEN_WIDTH + 100) {
				position.x = -10;
			}
			else if (position.x < -100) {
				position.x = SCREEN_WIDTH + 10;
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
		Texture *ratinho = new Texture;
	public:
		class effectsInfestacaoDeRatos(){
			ratinho->loadFromFile("sprites/rato.png");

			for (int i = 0; i < 100; i++) {
				int right = rand() % 2;
				rato* a = new rato(					
					randIntRange(5,10) - right*15,
					0,
					Vector2f(right*SCREEN_WIDTH, (float)SCREEN_HEIGHT / 1.1),
					Vector2f(0.2,0.2),
					ratinho
				);
				ratos.push_back(*a);
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