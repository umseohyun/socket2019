#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

#define PORT 9000
#define IPADDR "127.0.0.1"
#define BUFSIZE 100

int main(){
	int c_socket; 
	struct sockaddr_in c_addr;
	int n;
	int i;
	char rcvBuffer[BUFSIZE];//서버에서 보내준 메세지를 저장하는 변수
	char sndBuffer[BUFSIZE];
	//1. 클라이언트 소켓 생성
	c_socket = socket(PF_INET, SOCK_STREAM, 0); //서버와 동일한 설정으로 생성
	//2.소켓 정보 초기화
	memset(&c_addr, 0, sizeof(c_addr));
	c_addr.sin_addr.s_addr = inet_addr(IPADDR); //접속할 IP 설정 (127.0.0.1)
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(PORT);

	//3. 서버에 접속
	if(connect(c_socket, (struct sockaddr *) &c_addr, sizeof(c_addr)) == -1){
		//서버 접속에 실패하면 
		printf("Cannot Connect\n"); //Cannot connect 메세지 출력
		close(c_socket); //자원 회수
		return -1;  //프로세스 종료
	}
	//4. 서버에 메세지 보내기
	//입력받기
	while(1){
		printf("Me : ");
		fgets(sndBuffer, sizeof(sndBuffer), stdin);
		//서버로 메세지 전송
		sndBuffer[strlen(sndBuffer)-1] = '\0';  //Delete '\n' in String
	 	write(c_socket,sndBuffer,strlen(sndBuffer));
		if(strncasecmp(sndBuffer,"quit",4) == 0 || strncasecmp(sndBuffer,"kill server",11) == 0)
			break;
		//서버에서 보낸 메시지 읽기 
		n = read(c_socket, rcvBuffer, sizeof(rcvBuffer)); 
		//서버에서 보내준 메세지를 rcvBuffer에 저장하고, 메세지의 길이를 리턴
		//만약 read에 실패하면, -1을 리턴
		if (n < 0){ //read() 함수 실패 
			printf("Read Failed\n");
			return -1;
		}
		rcvBuffer[n] = '\0';
		printf("ChatBot : %s\n", rcvBuffer);
		for(i=0;i<BUFSIZE;i++)
			rcvBuffer[i] = '\0';
	}
	printf("Client Quited!\n");
	close(c_socket);
	return 0;	
}
