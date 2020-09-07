// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <unistd.h>
#include <time.h>

#include "constant.h"

int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char recv_buffer[BUF_SIZE] = {0}; 
    char *finish = "Finish receiving."; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
   // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)))
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
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
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 

    ////////////////   Data transfer   ////////////////
    int i = 0;
    float total_recv_bytes = 0.0;
    const float total_size = (float)PACKET_NUM * (float)BUF_SIZE;

    clock_t start = clock() ;
    while (total_recv_bytes < total_size) {
        int recv_bytes = read(new_socket , recv_buffer, BUF_SIZE < (total_size - total_recv_bytes)? BUF_SIZE : (total_size - total_recv_bytes) );
        total_recv_bytes += recv_bytes; 
        // i++;
        // if (recv_bytes !=BUF_SIZE) {
        //     printf("receive the %d th packet, size: %d bytes, total received: %f bytes\n", 
        //         i, recv_bytes, total_recv_bytes);
        // }
    }
    char *msg = "success";
    int send_size = send(total_size, msg, 32 , 0); 
    close(new_socket);
    clock_t end = clock();

    // printf("%s\n", recv_buffer); 
    if (total_recv_bytes != total_size) {
        printf("ERROR! should receive %f bytes, but actually received %f\n",
            total_size, total_recv_bytes);
    }
    else {
        float elapsed_time = (end-start) / (float)CLOCKS_PER_SEC;
        printf("\nConsumed time: %f seconds\n", elapsed_time);
        printf("Network Throughput: %f GB / sec\n", total_size / elapsed_time / 1024 / 1024 / 1024);
    }

    return 0; 
} 

