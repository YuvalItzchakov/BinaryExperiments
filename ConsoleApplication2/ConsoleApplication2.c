// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <winsock.h>

typedef struct mytype {
	char *name;
	int age;
} MyType;

int main()
{
	int thisSocket;
	struct sockaddr_in dest;

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);

	dest.sin_family = AF_INET;
	dest.sin_port = htons(80);
	dest.sin_addr.s_addr = INADDR_ANY;
	thisSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	int returnStatus;
	if (thisSocket < 0)
	{
		printf("\nFailed to create socket");
		returnStatus = 0;
	}
	else 
	{
		returnStatus = 1;
	}

	if (bind(thisSocket, (struct sockaddr *)&dest, sizeof(dest)) < 0) close_socket_with_error_num(thisSocket, "\nFailed to bind socket at port: %d\n", ntohs((u_short)dest.sin_port));

	printf("Listening on %u..", ntohs((u_short)dest.sin_port));
	if (listen(thisSocket, 1) < 0) close_socket_with_error(thisSocket, "\nFailed to listen to socket", "");

	struct sockaddr_in clientAddr;
	int clientSize = sizeof(clientAddr);
	thisSocket = accept(thisSocket, (struct socketaddr *)&clientAddr, (int *)&clientSize);

	if (thisSocket < 0) close_socket_with_error(thisSocket, "\nSocket Connection FAILED!\n", "");

	int newData;
	size_t BUFFERSIZE = sizeof(int) * 4;
	char* buffer = calloc(BUFFERSIZE, BUFFERSIZE);

	newData = recv(thisSocket, buffer, BUFFERSIZE, 0);

	printf("\nRecieved data: %s", buffer );

	WSACleanup();
	return returnStatus;
}

int close_socket_with_error_num(int socket, const char* message, const int num)
{
	char *buffer = calloc(sizeof(128), sizeof(128));
	sprintf(buffer, message, num);
	puts(buffer);
	exit(-1);
}

int close_socket_with_error(int socket, const char *message, const char *format)
{
	vprintf(message, format);
	if (socket) close(socket);
	exit(-1);
}


