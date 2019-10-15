#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

#define PORT 9000
#define BUFSIZE 100
char hi[BUFSIZE] = "Hi, Nice to meet you!";
char name[BUFSIZE] = "My name is ChatBot!";
char age[BUFSIZE] = "I'm 20 years old";
char none[BUFSIZE] = "I don't know!";
char rcvBuffer[BUFSIZE];
char sndBuffer[BUFSIZE];
char cmp1[BUFSIZE];
char cmp2[BUFSIZE];
char fBuffer[BUFSIZE];
int main(){
	int c_socket, s_socket;
	struct sockaddr_in s_addr, c_addr;
	int stlen;
	int n;
	int i;
	int len;
	FILE *fp;
	
	
	// 1. 서버 소켓 생성
	//서버 소켓 = 클라이언트의 접속 요청을 처리(허용)해 주기 위한 소켓
	s_socket = socket(PF_INET, SOCK_STREAM, 0); //TCP/IP 통신을 위한 서버 소켓 생성
	
	//2. 서버 소켓 주소 설정
	memset(&s_addr, 0, sizeof(s_addr)); //s_addr의 값을 모두 0으로  초기화
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY); //IP 주소 설정
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(PORT);

	//3. 서버 소켓바인딩
	if(bind(s_socket,(struct sockaddr *) &s_addr, sizeof(s_addr)) == -1){ 
		//바인딩 작업 실패 시, Cannot Bind 메시지 출력 후 프로그램 종료
		printf("Cannot Bind\n");
		return -1;
	}
	
	//4.listen() 함수 실행
	if(listen(s_socket, 5) == -1){
		printf("listen Fail\n");
		return -1;
	}

	//5. 클라이언트 요청 처리
	while(1){ //무한 루프
		len = sizeof(c_addr);
		printf("클라이언트 접속을 기다리는 중....\n");
		c_socket = accept(s_socket, (struct sockaddr *)&c_addr, &len); 
		//클라이언트의 요청이 오면 허용(accept)해 주고, 해당 클라이언트와 통신할 수 있도록 클라이언트 소켓(c_socket)을 반환함.
		printf("/client is connected\n");
		printf("클라이언트 접속 허용\n");
		while(1){
			for(i=0;i<BUFSIZE;i++){ //initialize
				rcvBuffer[i]='\0';
				sndBuffer[i]='\0';
				cmp1[i]='\0';
				cmp2[i]='\0';
			}
			n = read(c_socket, rcvBuffer, sizeof(rcvBuffer));
			rcvBuffer[n]='\0';
			printf("received data : %s\n",rcvBuffer);
			if(strncasecmp(rcvBuffer, "quit", 4) == 0 || strncasecmp(rcvBuffer,"kill server",11) == 0)
				break;
			else if(strncasecmp(rcvBuffer, "Hi", 2) == 0)
				write(c_socket, hi, strlen(hi));
			else if(strncasecmp(rcvBuffer, "What's your name?", 17) == 0)
				write(c_socket, name, strlen(name));
			else if(strncasecmp(rcvBuffer, "How old are you?", 16) == 0)
				write(c_socket, age, strlen(age));
			else if(strncasecmp(rcvBuffer, "strlen", 6) == 0)
			{
				stlen = strlen(rcvBuffer)-7;
				sprintf(sndBuffer, "string length is %d", stlen);
				write(c_socket, sndBuffer, strlen(sndBuffer));
			}
			else if(strncasecmp(rcvBuffer, "strcmp", 6) == 0)
			{
				strtok(rcvBuffer," ");
				strcpy(cmp1, strtok(NULL," "));
				strcpy(cmp2, strtok(NULL," "));
				if(strcmp(cmp1, cmp2) == 0){
					sprintf(sndBuffer,"%s == %s(Same(%d))", cmp1, cmp2, strcmp(cmp1, cmp2));
				}
				else{
					sprintf(sndBuffer,"%s != %s(Not same(%d))", cmp1, cmp2, strcmp(cmp1, cmp2));
				}
				write(c_socket, sndBuffer, strlen(sndBuffer));
			}
			else if(strncasecmp(rcvBuffer, "readfile", 8) == 0){
				strtok(rcvBuffer," ");
				strcpy(fBuffer,strtok(NULL," "));
				fp = fopen(fBuffer,"r");
				if(fp){
					while(fgets(sndBuffer, 255, (FILE *)fp)){
						write(c_socket, sndBuffer, strlen(sndBuffer));
					}
					fclose(fp);
				}
				else
					write(c_socket, "Cannot Open File", 17);
			}
			else if(strncasecmp(rcvBuffer, "exec", 4) == 0){
				strtok(rcvBuffer," ");
				strcpy(fBuffer,strtok(NULL," "));
				system(fBuffer);
			}
			else
				write(c_socket, none, strlen(none));
		}
		close(c_socket);
		if(strncasecmp(rcvBuffer,"kill server",11) == 0)
			break;
	}
	printf("Server killed!\n");
	close(s_socket);
	return 0;	
}
