// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <unistd.h>
#include <time.h>

#include "constant.h"

int sendall(int s, char *buf, size_t len, int max_packet_size)
{
/* s -> socket, buf -> the buffer to be send, len -> number of bytes to be send
 * max_packet_size -> a single packet size, default should be 16384 bytes */
    size_t total = 0;        // how many bytes we've sent
    size_t bytesleft = len; // how many we have left to send
    size_t n;

    // printf("Start sendall\n");
    int counter = 0;
    while(total < len) {
        n = send(s, buf + total, bytesleft < max_packet_size? bytesleft : max_packet_size, 0);
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
        // printf("The %dth iteration, bytesleft: %ld\n", counter++, bytesleft);
    }
    // printf("End sendall\n");
    if (total != len) {
        printf("Inconsistent sending, should send: %d bytes, actually send: %d\n",
            len, total);
    }

    return n==-1?-1:0; // return -1 onm failure, 0 on success
}

int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char send_buffer[BUF_SIZE]; 
    char* recv_msg;

    const float total_size = (float)PACKET_NUM * (float)BUF_SIZE;
    const int one_GB_size = 1024 * 1024 * 1024;  
    const int send_round_num = (int)(total_size / one_GB_size);
    printf("Send round: %d\n", send_round_num);

    char* one_GB_data = malloc(one_GB_size);
    memset(one_GB_data, 'a', one_GB_size);

    for (int i = 0; i < BUF_SIZE; i++)
        send_buffer[i] = 'a';

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    // if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    if(inet_pton(AF_INET, "10.128.0.11", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 

    printf("Start sending data.\n");
    ////////////////   Data transfer   ////////////////
    int i = 0;
    float total_sent_bytes = 0.0;

    clock_t start = clock();
    int success;
    for (int i = 0; i < send_round_num; i++) {
        success = sendall(sock, one_GB_data, one_GB_size, BUF_SIZE);
        if (success == -1) {
            printf("Sending 1 GB data UNSUCCESSFUL!");
        }
    }
    clock_t end = clock();

    // Should wait until the server said all the data was sent correctly,
    // otherwise the sender may send packets yet the server did not receive.
    char msg[32];
    int recv_bytes = read(sock, msg, 32);
    printf("received from server: %s\n", msg);

    printf("Data sent. Packet number:%d\tPacket size:%d bytes\tTotal data:%fGB\n",
        PACKET_NUM, BUF_SIZE, total_sent_bytes / (1024 * 1024 * 1024));   
    float elapsed_time = (end-start) / (float)CLOCKS_PER_SEC;
    printf("\nConsumed time: %f seconds\n", elapsed_time);
    printf("Transfer Throughput: %f GB / sec\n", total_size / elapsed_time / 1024 / 1024 / 1024); 


    return 0; 
} 