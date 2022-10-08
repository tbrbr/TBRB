#ifndef FREGUES__H
#define FREGUES__H

#include <SFML/Network.hpp>
using namespace sf;

TcpSocket socket;


Packet& inputToPacket(void* input) {

	Packet pacote;
	pacote << input;
	return pacote;

}

void inline connectToServer(IpAddress ip, unsigned short port) {
	socket.setBlocking(false);
	Socket::Status status = socket.connect(ip, port);
	if (status != Socket::Done) {
		throw "Falha na conexão com o servidor";
	}
}

void inline sendData(Packet pacotinho) {
	socket.send(pacotinho);
}

void inline receiveData(Packet& pacotinho) {
	socket.receive(pacotinho);
}

void teste(char* data) {

	Packet pacotinho = inputToPacket(data);
	sendData(pacotinho);
	receiveData(pacotinho);
	data = (char*)pacotinho.getData();
}

#endif
