/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket-serv.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:54:57 by rmechety          #+#    #+#             */
/*   Updated: 2022/05/27 17:30:56 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Server side C/C++ program to demonstrate Socket
// programming
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#define PORT 8080

void setupserv(int &server_fd, struct sockaddr_in &address)
{

	int opt = 1;
	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	};
}

int main(int argc, char const *argv[])
{
	int server_fd, new_socket, valread;
	char buffer[1024] = {0};
	char *pingmsg = "Ping from server";
	struct sockaddr_in address;
	int addrlen = sizeof(address);

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	setupserv(server_fd, address);
	fd_set readfds;

	std::vector<int> clientfd;

	while (true)
	{

		int maxfd = server_fd;
		FD_ZERO(&readfds);
		FD_SET(server_fd, &readfds);

		for (std::vector<int>::iterator it = clientfd.begin(); it != clientfd.end(); it++)
		{
			FD_SET(*it, &readfds);
			if (*it > maxfd)
				maxfd = *it;
		}

		int activity = select(maxfd + 1, &readfds, NULL, NULL, NULL);

		//
		//	watch the master socket
		//	si un socket est set alors un evenement a eu lieu donc :
		//	si master socket tentative de connection.
		//	si subsocket alors message recu.
		//
		//
		//	gestions des sockets a faire

		if (FD_ISSET(server_fd, &readfds))
		{
			if ((new_socket =
					 accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
			{
				perror("accept");
				exit(EXIT_FAILURE);
			};
			//	nouvelle connexion
			clientfd.push_back(new_socket);
			std::cout << "New connection : fd >" << new_socket << "<" << std::endl;
		}
		for (std::vector<int>::iterator it = clientfd.begin(); it != clientfd.end(); it++)
		{
			if (FD_ISSET(*it, &readfds))
			{
				valread = read(*it, buffer, 1024);
				if (valread != 0)
				{
					printf("FD: %d | >%s<\n", *it, buffer);
					send(*it, pingmsg, strlen(pingmsg), 0);
					printf("ping message sent\n");
					memset(buffer, 0, 1024);
				}
				else
				{
					close(*it);
					clientfd.erase(it);
				}
			}
		}
	}

	// closing the connected socket
	close(server_fd);
	// closing the listening socket
	shutdown(server_fd, SHUT_RDWR);
	return 0;
}