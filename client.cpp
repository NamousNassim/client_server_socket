#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main(int argc, char const *argv[]) {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    int status = connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));

    if (status != 0) {
        cout << "Failed to connect to the server\n";
        return 1;
    }

    char message[256];
    cout << "Enter a message to send to the server: ";
    cin.getline(message, 256);

    send(clientSocket, message, strlen(message), 0);
    cout << "Message sent to the server: " << message << endl;

    char buffer[256];
    int bytesRead = recv(clientSocket, buffer, 256, 0);
    cout << "Received " << bytesRead << " bytes from server: " << buffer << endl;

    close(clientSocket);

    return 0;
}
