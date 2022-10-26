#ifndef FREGUES__H
#define FREGUES__H

#include <SFML/Network.hpp>
using namespace sf;


TcpSocket suck;


Packet* inputToPacket(void* input) {

	Packet* pacote = new (Packet);
	*pacote << input;
	return pacote;

}

void inline connectToServer(IpAddress ip, unsigned short port) {
	suck.setBlocking(false);
	Socket::Status status = suck.connect(ip, port);
	if (status != Socket::Done) {
		throw "Falha na conexão com o servidor";
	}
}

void inline sendData(Packet pacotinho) {
	suck.send(pacotinho);
}

void inline receiveData(Packet& pacotinho) {
	suck.receive(pacotinho);
}


#endif