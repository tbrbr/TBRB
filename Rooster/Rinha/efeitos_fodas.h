#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

void seFodaAiWalter(int i) {
	//Texture t
	sf::SoundBuffer buf;
	buf.loadFromFile("audio/audio.ogg");

	//Sprite
	sf::Sound sound(buf);

	sound.pause();
	sound.stop();
	sound.setPlayingOffset(sf::seconds(2.f)); //De onde a música vai começar
	sound.setLoop(true);
	sound.play();
	sound.setVolume(100);

	while (1);
}
