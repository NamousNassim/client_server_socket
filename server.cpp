#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main() {
    int server_fd, client_fd, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    const char* hello = "Hello from server";
    int opt = 1;
    int addrlen = sizeof(serv_addr);


    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(8080);


    if (bind(server_fd, (struct sockaddr *)&serv_addr,
             sizeof(serv_addr))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((client_fd = accept(server_fd, (struct sockaddr *)&serv_addr,
                             (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read(client_fd, buffer, 1024);
    printf("%s\n", buffer);
    send(client_fd, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    return 0;
}
