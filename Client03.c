#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024

int main(int argc, char** argv) {

   SOCKET        	sd;
   struct sockaddr_in serv;
   char  		str[1024]="abcd";
   char  		str_r[1024];
   WSADATA 		wsadata;
   int n1,n2,i;

   WSAStartup(0x101,(LPWSADATA) &wsadata); // �I�s WSAStartup() ���U WinSock DLL ���ϥ�

   sd=socket(AF_INET, SOCK_STREAM, 0); //�}�Ҥ@�� TCP socket.

   serv.sin_family       = AF_INET;
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(5678);

   connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // �s���� echo server



   while(1){

    	n1=recv(sd, str_r, MAXLINE, 0); //����
	   if (n1 <= 1){

	   		break;
		   }
	   printf("recv: %s (%d bytes)\n",str_r,n1);

	   n2=recv(sd, str_r, MAXLINE, 0); //����
	   if (n2 <= 1){

	   		break;
		   }
	   printf("recv: %s (%d bytes)\n",str_r,n2);
   		//strcpy(str,"this message is for client 1");

		printf("3say:");
   		gets(str);

   		send(sd, str, strlen(str)+1, 0); //�ǰe
   		printf( "send: %s (%d bytes)\n" ,str,strlen(str)+1);


	}

	printf("Connection closed.\n");
   closesocket(sd); //����TCP socket

   WSACleanup();  // ���� WinSock DLL ���ϥ�
   system("pause");

   return 0;
}