#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>
 
#define MAXRCVLEN 1024
#define PORTNUM 5555
 
int main(int argc, char *argv[])
{
   char* msg;
   msg = malloc(256);
   char buffer[MAXRCVLEN + 1]; /* +1 so we can add null terminator */
   int len, mysocket;
   struct sockaddr_in dest; 
   int numrv;
   int opt;
 
   mysocket = socket(AF_INET, SOCK_STREAM, 0);
  
   //memset(, 0, sizeof(dest)); 
   memset(&dest, 0, sizeof(dest));                /* zero the struct */
   dest.sin_family = AF_INET;
   dest.sin_addr.s_addr = INADDR_ANY;//htonl((in_addr_t)0xc0a889fd); 
   dest.sin_port = htons(PORTNUM);                /* set destination port number */
 
   printf("Client/destination add:%s\n", inet_ntoa(dest.sin_addr));

   int consocket = connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr));
 
    printf("Press\t 1 - VOIP\n\t 2 - CHAT\n");
    scanf("%d", &opt);

    if (opt == 1)
    {
   while(1){
   len = recv(mysocket, buffer, MAXRCVLEN, 0);

   /* We have to null terminate the received data ourselves */
   buffer[len] = '\0';
   printf("::: %s\n", buffer);
   
   printf("\n:");
   scanf("%s",msg);
   //   sendto(mysocket, msg, strlen(msg), 0, (in_addr_t)0xc0a889fd, sizeof(struct sockaddr));

   send(mysocket, msg, strlen(msg), 0);
   //printf("message sent :%s\n\n", msg);
   //break;
    }
    }
    else{
      while(1){
      printf("Recieving File...\n");
      filerecv(consocket);
      //printf("Waititng\n");
      wait(5000);
      }
    }
   close(mysocket);
   return EXIT_SUCCESS;
}


int filerecv(mysocket){
   
   int bytesReceived = 0;
   char recvBuff[256];
   memset(recvBuff, '0', sizeof(recvBuff));

   FILE *fp;
    fp = fopen("sample_text.txt", "ab"); 
    if(NULL == fp)
    {
        printf("Error opening file");
        return 1;
    }

    
    while((bytesReceived = read(mysocket, recvBuff, 256)) > 0)
    {
        printf("Bytes received %d\n",bytesReceived);    
           fwrite(recvBuff, 1,bytesReceived,fp);
        printf("re writting\n");
    }

    if(bytesReceived < 0)
    {
        printf("\n Read Error \n");
    }


    return 0;
}
