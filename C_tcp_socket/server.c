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

int receiveall(int s, char *buf, size_t len, int max_packet_size)
{
/* s -> socket, buf -> the buffer to be send, len -> number of bytes to be send
 * max_packet_size -> a single packet size, default should be 16384 bytes */
    size_t total = 0;        // how many bytes we've sent
    size_t bytesleft = len; // how many we have left to send
    size_t n;

    // printf("Start receiveall\n");
    int counter = 0;

    while(total < len) {
        n = read(s, buf + total, bytesleft < max_packet_size? bytesleft : max_packet_size);
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
        // printf("The %dth iteration, bytesleft: %ld\n", counter++, bytesleft);
    }
    // printf("End receiveall\n");
    if (total != len) {
        printf("Inconsistent sending, should send: %d bytes, actually send: %d\n",
            len, total);
    }

    return n==-1?-1:0; // return -1 onm failure, 0 on success
}

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
    printf("Successfully built connection.");


    const float total_size = (float)PACKET_NUM * (float)BUF_SIZE;
    const int one_GB_size = 1024 * 1024 * 1024;  
    const int send_round_num = (int)(total_size / one_GB_size);
    printf("Send round: %d\n", send_round_num);

    char* one_GB_data = malloc(one_GB_size);

    // ////////////////   Data transfer   ////////////////
    int success;

    clock_t start = clock() ;
    for (int i = 0; i < send_round_num; i++) {
        success = receiveall(new_socket, one_GB_data, one_GB_size, BUF_SIZE);
        if (success == -1) {
            printf("Receiving 1 GB data UNSUCCESSFUL!");
        }
    }
    clock_t end = clock();

    char *msg = "success";
    int send_size = send(new_socket, msg, 32 , 0); 
    close(new_socket);

    printf("first bytes in buffer:\n");
    for (int i = 0; i < 100; i++) {
        printf("%c ", one_GB_data[i]);
    }

    float elapsed_time = (end-start) / (float)CLOCKS_PER_SEC;
    printf("\nConsumed time: %f seconds\n", elapsed_time);
    printf("Transfer Throughput: %f GB / sec\n", total_size / elapsed_time / 1024 / 1024 / 1024);

    return 0; 
} 

