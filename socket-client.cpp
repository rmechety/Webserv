/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket-client.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:54:32 by rmechety          #+#    #+#             */
/*   Updated: 2022/05/27 17:04:58 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys/socket.h"

// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
	int sock = 0, valread, client_fd;
	struct sockaddr_in serv_addr;
	std::string hello;
	char buffer[1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((client_fd = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}
	while (true)
	{
		std::cin >> hello;
		send(sock, hello.c_str(), hello.length(), 0);
		printf("Hello message sent\n");
		if (hello == "quit")
		{
			std::cout << "QUIT CMD" << std::endl;
			break;
		}
		valread = read(sock, buffer, 1024);
		printf("%s\n", buffer);
		memset(buffer, 0, 1024);
	}

	// closing the connected socket
	close(client_fd);
	return 0;
}