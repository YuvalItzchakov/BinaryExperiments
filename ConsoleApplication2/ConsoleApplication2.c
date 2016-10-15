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

	return returnStatus;
}


