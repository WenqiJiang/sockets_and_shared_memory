#define PORT 8080

//////// NOTE! TOTAL_TRANSFER_BYTE == BUF_SIZE * PACKET_NUM
//////// NOTE! BUF_SIZE * PACKET_NUM MUST BE integar X of 1 GB!
#define BUF_SIZE (1024 * 1024 * 4)
size_t PACKET_NUM = 1024 * 4; //1024;// * 4;
// #define PACKET_NUM (1024 * 64)
// float TOTAL_TRANSFER_BYTES = (float) BUF_SIZE * PACKET_NUM;