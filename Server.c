#include <stdio.h>
#include <string.h>
#include <winsock.h>
#define MAXLINE 1024    /* �r��w�İϪ��� */

void main()
{
	SOCKET	serv_sd, cli_sd1,cli_sd2,cli_sd3;        /* socket �y�z�l */
  	int   	cli_len, n,i;
  	char  	str[MAXLINE],str_r[MAXLINE];

  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;

    WSAStartup(0x101, &wsadata); //�I�s WSAStartup() ���U WinSock DLL ���ϥ�

  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// �}�� TCP socket

   	//���w socket �� IP ��}�M port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// ���wport

    //bind(serv_sd, &serv, sizeof(serv)) ;
    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));

   	listen(serv_sd, 5) ; //�I�s listen() �� socket �i�J�u��ť�v���A

   	cli_len = sizeof(cli);
	printf("server waits for the first client\n");
	cli_sd1=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);

	struct  sockaddr_in   tAddr;
 	int lentAddr;
 	lentAddr=sizeof(tAddr);
 	getpeername(cli_sd1, (LPSOCKADDR)&tAddr, &lentAddr);
 	printf("Client 1'IP:%s, port:%d\n",
		inet_ntoa(tAddr.sin_addr), ntohs(tAddr.sin_port));


	printf("server waits for the second client\n");
	cli_sd2=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);


 	lentAddr=sizeof(tAddr);
 	getpeername(cli_sd2, (LPSOCKADDR)&tAddr, &lentAddr);
 	printf("Client 2'IP:%s, port:%d\n",
		inet_ntoa(tAddr.sin_addr), ntohs(tAddr.sin_port));
   	printf("server waits for the third client\n");
	cli_sd3=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);


 	lentAddr=sizeof(tAddr);
 	getpeername(cli_sd3, (LPSOCKADDR)&tAddr, &lentAddr);
 	printf("Client 3'IP:%s, port:%d\n",
		inet_ntoa(tAddr.sin_addr), ntohs(tAddr.sin_port));

   	while(1){

	    sleep(1);
	    //1�ǰe
	   	n=recv(cli_sd1, str_r, MAXLINE, 0); //��server����
	   	printf("server recv: from client 2: %s (%d bytes)\n",str_r,n);
	   	if(n<1)
	   	{
	   		send(cli_sd2, str_r, strlen(str)+1, 0);
	   		send(cli_sd3, str_r, strlen(str)+1, 0);
	   		break;
		}
	    printf("server recv: from client 1: %s (%d bytes)\n",str_r,n);
	    strcpy(str,str_r);
	    //strcpy(str,"this message is for client 1");
	    send(cli_sd2, str, strlen(str)+1, 0); //�ǰe��echo server
	    printf("server sends to client 2: %s (%d bytes)\n" ,str,strlen(str)+1);
	    send(cli_sd3, str, strlen(str)+1, 0); //�ǰe��echo server
	    printf("server sends to client 3: %s (%d bytes)\n" ,str,strlen(str)+1);
	    strcpy(str_r,"");
	    //2�ǰe
	    n=recv(cli_sd2, str_r, MAXLINE, 0); //��server����
	    printf("server recv: from client 2: %s (%d bytes)\n",str_r,n);
	    if(n<1)
	   	{
	   		send(cli_sd1, str_r, strlen(str)+1, 0);
	   		send(cli_sd3, str_r, strlen(str)+1, 0);
	   		break;
		}

	    strcpy(str,str_r);
	    //strcpy(str,"this message is for client 2");
	    send(cli_sd1, str, strlen(str)+1, 0); //�ǰe��echo server
	    printf("server sends to client 1: %s (%d bytes)\n" ,str,strlen(str)+1);
	    send(cli_sd3, str, strlen(str)+1, 0); //�ǰe��echo server
	    printf("server sends to client 3: %s (%d bytes)\n" ,str,strlen(str)+1);
	     strcpy(str_r,"");

	    //3�ǰe
	    n=recv(cli_sd3, str_r, MAXLINE, 0); //��server����
	    if(n<1)
	   	{
	   		send(cli_sd1, str_r, strlen(str)+1, 0);
	   		send(cli_sd2, str_r, strlen(str)+1, 0);
	   		break;
		}
	    strcpy(str,str_r);
	    //strcpy(str,"this message is for client 2");
	    send(cli_sd1, str, strlen(str)+1, 0); //�ǰe��echo server
	    printf("server sends to client 1: %s (%d bytes)\n" ,str,strlen(str)+1);
	    send(cli_sd2, str, strlen(str)+1, 0); //�ǰe��echo server
	    printf("server sends to client 2: %s (%d bytes)\n" ,str,strlen(str)+1);
    	strcpy(str_r,"");
	}
	printf("All connect closed.\n");
	//���� WinSock DLL ���ϥ�
   	closesocket(serv_sd);
   	closesocket(cli_sd1);
   	closesocket(cli_sd2);
   	closesocket(cli_sd3);
   	WSACleanup();
   	system("pause");
}
