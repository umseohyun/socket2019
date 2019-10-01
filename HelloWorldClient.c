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
	
	char rcvBuffer[BUFSIZE];

	int n;
	//1. 클라이언트 소켓 생성
	c_socket = socket(PF_INET, SOCK_STREAM, 0); //서버와 동일하게 설정(TCP는 TCP, UDP는 UDP)
	//2. 소켓 정보 초기화
	memset(&c_addr, 0, sizeof(c_addr));
	c_addr.sin_addr.s_addr = inet_addr(IPADDR); //접속할 IP 설정
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(PORT);
	
	//3. 서버에 접속
	if(connect(c_socket, (struct sockaddr *)&c_addr, sizeof(c_addr)) == -1){
		printf("CANNOT CONNECT\n"); //메세지 출력
		close(c_socket); //자원 회수
		return -1; //프로세스 종료
	}

	//4. 서버에서 보낸 메세지 읽기
	if((n = read(c_socket, rcvBuffer, sizeof(rcvBuffer))) < 0){
		//서버에서 보내준 메세지를 rcvBuffer에 저장하고, 메세지의 길이를 리턴
		//만약 read에 실패하면 -1 리턴
		printf("ROAD FAILED");
		return (-1);
	}
	rcvBuffer[n] = '\0'; //문자열 뒷 부분 깨짐 방지
	printf("received data : %s\n", rcvBuffer); //서버에서 받은 메세지 출력 
	printf("rcvBuffer lens : %d\n", strlen(rcvBuffer));
	close(c_socket);
}
