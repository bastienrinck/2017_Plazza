//
// Created by rectoria on 4/30/18.
//

#include <string>
#include <zconf.h>
#include <iostream>
#include "../Socket.hpp"

int main()
{
	/*
	 * Les sockets peuvent être créés de 2 façons : Soit une paire auto-générée,
	 * mais qui ne peut communiquer qu'entre eux deux, soit deux sockets à
	 * configurer à la main mais auquel on peut s'attacher comme on le souhaite.
	 *
	 * Le modèle client/serveur est maintenu (client = connect, server = accept)
	 * Pour l'instant en bloquant, à passer en non bloquant par la suite.
	 *
	 * True = Autogénérés, false = sockets à interconnecter à la main.
	 */
	Plazza::Socket s(true); //Je dispose ici de deux sockets opérationels
	std::string buf;
	int pid = fork();

	if (!pid) {
		// Le fork joue le role du client
		s.closeServer();
		// Close le serveur (on ne va pas/plus accepter de connection
		// Cast en client de l'objet TCPSocket que renvoit le getter pour appeler la fonction de reception des données recus.
		((Plazza::ClientSocket *)s.getClient())->receive(buf);
		std::cout << buf << std::endl;
		// Cast en client de l'objet TCPSocket que renvoit le getter pour appeler la fonction d'envoi de données.
		((Plazza::ClientSocket *)s.getClient())->send(
			"This is the reversed test\n");
		// Fin du fork, exit.
		exit(EXIT_SUCCESS);
	}
	// Serveur

	// Close du socket utiliser pour accepter les nouvelles connections (socket du serveur).
	s.closeServer();
	// Close du socket de la partie client du socket.
	// Ce fd sera en réalité toujours ouvert dans le serveur, comme étant un de ses clients.
	// C'est comme si le serveur avait déjà accepté une connexion. Il n'a plus besoin d'en accepter d'autre, il peut donc se fermer.
	// La partie client ne nous interessant pas ici, il peut donc être coupé. Cette partie est complêtement optionnelle.
	s.closeClient();
	// Cast en serveur de l'objet TCPSocket que renvoit le getter pour appeler la fonction d'envoi de données
	((Plazza::ServerSocket *)s.getServer())->send("This is a test\n");
	// Cast en serveur de l'objet TCPSocket que renvoit le getter pour appeler la fonction de reception de données
	((Plazza::ServerSocket *)s.getServer())->receive(buf);
	std::cout << buf << std::endl;

	// Exemple pour le cas ou l'on souhaite connecter plusieurs client au serveur.
	Plazza::Socket d(false);

	// Le socket serveur doit être configuré à la main. Ici on demande un port aléatoire (0).
	((Plazza::ServerSocket *)d.getServer())->setSocket(0);
	// Le socket client doit être configuré à la main. On recupère donc les infos du socket serveur pour le configurer.
	((Plazza::ClientSocket *)d.getClient())->setSocket(
		((Plazza::ServerSocket *)d.getServer())->getSocketIp(),
		((Plazza::ServerSocket *)d.getServer())->getSocketPort());

	// Nouveau fork
	pid = fork();

	if (!pid) {
		// Création d'un deuxième client qui pointe sur le serveur
		Plazza::ClientSocket client2;
		client2.setSocket(((Plazza::ServerSocket *)d.getServer())->getSocketIp(),
			((Plazza::ServerSocket *)d.getServer())->getSocketPort());
		// Les clients n'ont pas besoin du serveur, close().
		d.closeServer();
		// Connexion des sockets client au serveur, en utilisant les bons cast.
		((Plazza::ClientSocket *)d.getClient())->connect();
		client2.connect();
		// Début de la transmission, ici la réception client 1.
		((Plazza::ClientSocket *)d.getClient())->receive(buf);
		std::cout << buf << std::endl;
		// Début de la transmission, ici la réception client 2.
		client2.receive(buf);
		std::cout << buf << std::endl;
		// Envoi
		((Plazza::ClientSocket *)d.getClient())->send(
			"This is the reversed test\n");
		// Envoi
		client2.send("This is the second reversed test\n");
		exit(EXIT_SUCCESS);
	}

	// Ici le serveur a besoin d'accepter la connexion des clients
	((Plazza::ServerSocket *)d.getServer())->accept();
	((Plazza::ServerSocket *)d.getServer())->accept();
	// Plus besoin du serveur, pas besoin du client. On close().
	d.closeServer();
	d.closeClient();
	// Envoi client 1
	((Plazza::ServerSocket *)d.getServer())->send("This is a test\n", 0);
	// Envoi client 2, il faut ici préciser à quel client (par defaut le client à l'index 0).
	// Comme c'est le deuxième connecté, il faut inscrire 1
	((Plazza::ServerSocket *)d.getServer())->send("This is another test\n", 1);
	// Réception client 1
	((Plazza::ServerSocket *)d.getServer())->receive(buf, 0);
	std::cout << buf << std::endl;
	// Réception client 2, il faut ici préciser à quel client (par defaut le client à l'index 0).
	// Comme c'est le deuxième connecté, il faut inscrire 1
	((Plazza::ServerSocket *)d.getServer())->receive(buf, 1);
	std::cout << buf << std::endl;
	exit(EXIT_SUCCESS);

	// J'hésite encore à ajouter une couche d'encapsulation,
	// pour eviter d'avoir à faire les casting à la main. On verra à l'usage si c'est pertinent.
}