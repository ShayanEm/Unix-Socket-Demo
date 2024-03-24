/**
 * @file server.cpp
 * @author Shayan Eram
 * @brief the program to create a Unix socket server.
 */
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <string>
#include "../../build/generated/version.h"

using namespace std;

/**
 * @brief main
 * @param argc number of inputs
 * @param argv the socket path
*/
int main(int argc, char* argv[])
{
	// Check for correct input
	if (argc != 2) {
		cerr << "Usage " << argv[0] << "<socket_path>\n";
		return 1;
	}
	const char* socketPath = argv[1];
	
	// Create the socket
	int serverSocket = socket(AF_UNIX, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		cerr << "Error creating socket\n";
		return 1;
	}
	else
		cout << "Socket created" << endl;

	// Specify the address 
	struct sockaddr_un serverAddress;
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sun_family = AF_UNIX;
	strncpy(serverAddress.sun_path, socketPath, sizeof(serverAddress.sun_path) - 1);
	unlink(socketPath);

	// Bind the socket
	int bindResult = bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	if (bindResult == -1) {
		cerr << "Error binding socket\n";
		return 1;
	}
	else
		cout << "Socket Bound" << endl;

	// Listen on the socket 
	if (listen(serverSocket, 5) == -1) {
		cerr << "Error listening on server sucket\n";
		return 1;
	}

	while (true)
	{
		// Accept a connection request
		int clientSocket = accept(serverSocket, NULL, NULL);
		if (clientSocket == -1) {
			cerr << "Error accepting client socket\n";
			return 1;
		}
		else
			cout << "Accepted Client Connection: " << endl;

		// Receive data from client
		char message[1024] = { 0 };
		int bytesReceived = recv(clientSocket, message, sizeof(message), 0);
		if (bytesReceived < 0) {
			cerr << "Error receiving data form client\n";
			close(clientSocket);
			return 1;
		}
		else
			cout << "Message from client recieved : " << message << endl;
		
		// Null terminate the received data
		message[bytesReceived] = '\0';

		// Handle commands
		if (strcmp(message, "VERSION") == 0) {
			
			string version = GIT_COMMIT_HASH;
			if (send(clientSocket, version.c_str(), version.length(), 0) == -1) {
				cerr << "Error sending version to client\n";
			}
		}
		else {
			const char* errorMessage = "REJECTED";
			send(clientSocket, errorMessage, strlen(errorMessage), 0);
		}
		// Close the connected socket
		close(clientSocket);
		cout << "Session with the client finished" << endl;

	}

	// Close the listening socket
	close(serverSocket);
	
	return 0;
}
