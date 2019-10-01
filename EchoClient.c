#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

#define PORT 9000
#define IPADDR "127.0.0.1"
#define BUFSIZE 100

main(){
	int c_socket;
	struct sockaddr_in c_addr;
	
	char buffer[BUFSIZE];
	char quit[BUFSIZE] = "quit";
	int n,run;
	//1. 클라이언트 소켓 생성
	c_socket = socket(PF_INET, SOCK_STREAM, 0); //서버와 동일하게 설정(TCP는 TCP, UDP는 UDP)
	//2. 소켓 정보 초기화
	memset(&c_addr, 0, sizeof(c_addr));
	c_addr.sin_addr.s_addr = inet_addr(IPADDR); //접속할 IP 설정
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(PORT);
	//3. 서버에 접속
	while(1){
		printf("Input : ");
		connect(c_socket, (struct sockaddr *)&c_addr, sizeof(c_addr));
		fgets(buffer, BUFSIZE, stdin);
		run = strcmp(buffer, quit);
		if(run==10){
			close(c_socket);
		}
		write(c_socket, buffer, strlen(buffer));
		//4. 서버에서 보낸 메세지 읽기
		n = read(c_socket, buffer, sizeof(buffer));
		printf("received data : %s\n", buffer); //서버에서 받은 메세지 출력 
		printf("rcvBuffer lens : %d\n", strlen(buffer)-1);
	}
	close(c_socket);
}
