// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <unistd.h>
#include <time.h>

#include "constant.h"


int sendall(int s, char *buf, int *len)
{
    int total = 0;        // how many bytes we've sent
    int bytesleft = *len; // how many we have left to send
    int n;

    printf("Here before send\n");
    while(total < *len) {
        n = send(s, buf+total, bytesleft, 0);
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
    }
    printf("Here after send\n");

    *len = total; // return number actually sent here

    return n==-1?-1:0; // return -1 onm failure, 0 on success
}

int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char send_buffer[BUF_SIZE]; 
    char* recv_msg;
    char* one_GB_data = malloc(1024 * 1024 * 1024);
    memset(one_GB_data, 1, 1024 * 1024 * 1024);

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
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    // if(inet_pton(AF_INET, "10.128.0.11", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 

    printf("Start sending data.\n");
    ////////////////   Data transfer   ////////////////
    int i = 0;
    float total_sent_bytes = 0.0;
    const float total_size = (float)PACKET_NUM * (float)BUF_SIZE;

    // clock_t start = clock();
    // int GB_len = 1024 * 1024 * 1024;
    // int success = sendall(sock, one_GB_data, &GB_len);
    // clock_t end = clock();
    // if (success == -1)
    //     printf("Sending 1 GB data UNSUCCESSFUL!");
    clock_t start = clock();
    while (total_sent_bytes < total_size) {
        int send_size = send(sock, send_buffer, BUF_SIZE , 0); 
        total_sent_bytes += send_size;
        // printf("sent the %d th packet, sent packet size: %d bytes, total sent: %f bytes\n", 
        //     i++, send_size, total_sent_bytes);
    }
    clock_t end = clock();

    // Should wait until the server said all the data was sent correctly,
    // otherwise the sender may send packets yet the server did not receive.
    char msg[32];
    int recv_bytes = read(sock, msg, 32);
    printf("received from server: %s\n", msg);

    if (total_sent_bytes != total_size) {
        printf("ERROR! should send %f bytes, but actually sent %f\n",
            total_size, total_sent_bytes);
    }
    else {
        printf("Data sent. Packet number:%d\tPacket size:%d bytes\tTotal data:%fGB\n",
            PACKET_NUM, BUF_SIZE, total_sent_bytes / (1024 * 1024 * 1024));   
        float elapsed_time = (end-start) / (float)CLOCKS_PER_SEC;
        printf("\nConsumed time: %f seconds\n", elapsed_time);
        printf("Memcpy Throughput: %f GB / sec\n", total_size / elapsed_time / 1024 / 1024 / 1024); 
    }

    return 0; 
} 