#include <iostream>

#define SFML_STATIC

#include <SFML/Network.hpp>
using namespace sf;

int main()
{
    TcpListener listener;

    std::cout << "use essa chave para conectar os clientes ao server:"
    << IpAddress::getLocalAddress() << std::endl;
   
    getchar();

    listener.listen(59000);
    listener.listen(59001);

    std::cout << "para parar a conexão digite 0" << std::endl;
 
    TcpSocket client1;
    TcpSocket client2;
    
    Packet pacote;

    while (1) {
        listener.accept(client1);
        listener.accept(client2);

        client1.receive(pacote);
        client2.send(pacote);

        client2.receive(pacote);
        client1.send(pacote);
    }
    
}

