/**
 * @file client.cpp
 * @author Shayan Eram
 * @brief the program to send command to Unix socket server.
 */
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;

/**
 * @brief main
 * @param argc number of inputs
 * @param argv the socket path
*/
int main(int argc, char* argv[])
{
	// Check for correct input
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <socket_path> <command>\n";
		return 1;
	}
	const char* socketPath = argv[1];
	const char* command = argv[2];

	// Create the socket
	int clientSocket = socket(AF_UNIX, SOCK_STREAM, 0);
	if (clientSocket == -1) {
		cerr << "Error creating socket\n";
		return 1;
	}
	
	// Specify the address
	struct sockaddr_un serverAddress;
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sun_family = AF_UNIX;
	strncpy(serverAddress.sun_path, socketPath, sizeof(serverAddress.sun_path) - 1);

	// Send connection request 
	int connectResult = connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	if (connectResult == -1) {
		cerr << "Error connecting socket\n";
		close(clientSocket);
		return 1;
	}
	else
		cout << "Connected to server" << endl;

	// Send command to server
	if (send(clientSocket, command, strlen(command), 0) == -1) {
		cerr << "Error sending command to server\n";
		return 1;
	}

	// Receive and print response from the server
	char message[1024] = {0};
	int bytesReceived = recv(clientSocket, message, sizeof(message), 0);
	if (bytesReceived < 0) {
		cerr << "Error receiving response form server\n";
		return 1;
	}

	// Null terminate the received data
	message[bytesReceived] = '\0';

	// Print the message
	cout << "Response from the server: " << message << endl;
	
	// Close socket
	close(clientSocket);

	return 0;
}