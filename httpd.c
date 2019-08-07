#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/sendfile.h>
#include <pthread.h>
#define MAX 1024
#define HOME_PAGE "index.html"
#define PAGE_301 "wwwroot/301.html"
#define PAGE_302 "wwwroot/302.html"
#define PAGE_307 "wwwroot/307.html"
#define PAGE_400 "wwwroot/400.html"
#define PAGE_404 "wwwroot/404.html"
#define PAGE_500 "wwwroot/500.html"
#define PAGE_503 "wwwroot/503.html"

static void usage(const char *proc)
{
	printf("Usage: %s [port]\n", proc);
}

static int startup(int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		perror("socket");
		exit(2);
	}

	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	local.sin_port = htons(port);

	if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){
		perror("bind");
		exit(3);
	}

	if(listen(sock, 5) < 0){
		perror("listen");
		exit(4);
	}
	return sock;
}

static int getLine(int sock, char line[], int size)
{
	//\r, \r\n, \n -> \n
	char c = 'a';
	int i = 0;
	while(c != '\n' && i < size - 1){
		ssize_t s = recv(sock, &c, 1, 0);
		if( c == '\r'){
			//read(); // c == '\n', c != '\n' , a, b, ..
			recv(sock, &c, 1, MSG_PEEK);
			if( c == '\n' ){
				recv(sock, &c, 1, 0);
			}else{
				c = '\n';
			}
		}
		//\r\n \r->\n
		line[i++] = c;
	}
	line[i] = '\0';
	return i;
}

static void clearHeaer(int sock)
{
	char line[MAX];
	do{
		getLine(sock, line, sizeof(line));
	}while(strcmp("\n", line));
}



void show_301(int sock)
{
	char line[MAX];
	struct stat st;
	sprintf(line, "HTTP/1.0 301 NOT FOUND\r\n");
	send(sock, line, strlen(line), 0);
	sprintf(line, "Content-Type: text/html;charset=utf-8\r\n");
	send(sock, line, strlen(line), 0);
	sprintf(line, "\r\n");
	send(sock, line, strlen(line), 0);
	int fd = open(PAGE_301, O_RDONLY);
	stat(PAGE_301, &st);
	sendfile(sock, fd, NULL, st.st_size);
  close(fd);
}

void show_302(int sock)
{
	char line[MAX];
	struct stat st;
	sprintf(line, "HTTP/1.0 302 NOT FOUND\r\n");
	send(sock, line, strlen(line), 0);
	sprintf(line, "Content-Type: text/html;charset=utf-8\r\n");
	send(sock, line, strlen(line), 0);
	sprintf(line, "\r\n");
	send(sock, line, strlen(line), 0);
	int fd = open(PAGE_302, O_RDONLY);
	stat(PAGE_302, &st);
	sendfile(sock, fd, NULL, st.st_size);
  close(fd);
}

void show_307(int sock)
{
	char line[MAX];
	struct stat st;
	sprintf(line, "HTTP/1.0 307 NOT FOUND\r\n");
	send(sock, line, strlen(line), 0);
	sprintf(line, "Content-Type: text/html;charset=utf-8\r\n");
	send(sock, line, strlen(line), 0);
	sprintf(line, "\r\n");
	send(sock, line, strlen(line), 0);
	int fd = open(PAGE_307, O_RDONLY);
	stat(PAGE_307, &st);
	sendfile(sock, fd, NULL, st.st_size);
  close(fd);
}

void show_400(int sock)
{
	char line[MAX];
	struct stat st;
	sprintf(line, "HTTP/1.0 400 NOT FOUND\r\n");
	send(sock, line, strlen(line), 0);
	sprintf(line, "Content-Type: text/html;charset=utf-8\r\n");
	send(sock, line, strlen(line), 0);
	sprintf(line, "\r\n");
	send(sock, line, strlen(line), 0);
	int fd = open(PAGE_400, O_RDONLY);
	stat(PAGE_400, &st);
	sendfile(sock, fd, NULL, st.st_size);
	close(fd);
}

  void show_404(int sock)
{
	char line[MAX];
	struct stat st;
	sprintf(line, "HTTP/1.0 404 NOT FOUND\r\n");
	send(sock, line, strlen(line), 0);
	sprintf(line, "Content-Type: text/html;charset=utf-8\r\n");
	send(sock, line, strlen(line), 0);
	sprintf(line, "\r\n");
	send(sock, line, strlen(line), 0);
	int fd = open(PAGE_404, O_RDONLY);
	stat(PAGE_404, &st);
	sendfile(sock, fd, NULL, st.st_size);
	close(fd);
}

  void show_500(int sock)
{
	char line[MAX];
	struct stat st;
	sprintf(line, "HTTP/1.0 500 NOT FOUND\r\n");
	send(sock, line, strlen(line), 0);
	sprintf(line, "Content-Type: text/html;charset=utf-8\r\n");
	send(sock, line, strlen(line), 0);
	sprintf(line, "\r\n");
	send(sock, line, strlen(line), 0);
	int fd = open(PAGE_500, O_RDONLY);
	stat(PAGE_500, &st);
	sendfile(sock, fd, NULL, st.st_size);
	close(fd);
}

void show_503(int sock)
{
	char line[MAX];
	struct stat st;
	sprintf(line, "HTTP/1.0 503 NOT FOUND\r\n");
	send(sock, line, strlen(line), 0);
	sprintf(line, "Content-Type: text/html;charset=ISO-8859-1\r\n");
	send(sock, line, strlen(line), 0);
	sprintf(line, "\r\n");
	send(sock, line, strlen(line), 0);
	int fd = open(PAGE_503, O_RDONLY);
	stat(PAGE_503, &st);
	sendfile(sock, fd, NULL, st.st_size);
	close(fd);
}

static void echoErrMsg(int sock, int status_code)
{
	switch(status_code){
		case 301:
			show_301(sock);
			break;
		case 302:
			show_302(sock);
			break;
		case 307:
			show_307(sock);
			break;
		case 400:
			show_400(sock);
			break;
		case 404:
			show_404(sock);
			break;
		case 500:
			show_500(sock);
			break;
		case 503:
			show_503(sock);
			break;
		default:
			break;
	}
}

int exe_cgi(int sock, char *method, char *path, char *query_string)
{
	char line[MAX];
	int content_length = -1;
	char method_env[MAX/32];
	char query_string_env[MAX];
	char content_length_env[MAX/8];

	if(strcasecmp(method, "GET") == 0){
		clearHeaer(sock);
	}else{//POST
		do{
			getLine(sock, line, sizeof(line));
			//Content-Length: XXX
			if(strncasecmp(line, "Content-Length: ", 16) == 0){
				content_length = atoi(line + 16);
			}
		}while(strcmp(line, "\n"));
		if(content_length == -1){
			return 400;
		}
	}

	int input[2];
	int output[2];

	pipe(input);
	pipe(output);

	pid_t id = fork();
	if(id < 0){
		return 500;
	}
	else if(id == 0){//child
		close(input[1]);
		close(output[0]);

		dup2(input[0], 0);
		dup2(output[1], 1);


		sprintf(method_env, "METHOD=%s", method);
		putenv(method_env);
		if(strcasecmp(method, "GET") == 0){
			sprintf(query_string_env, "QUERY_STRING=%s", query_string);
			putenv(query_string_env);
		}
		else{
			sprintf(content_length_env, "CONTENT_LENGTH=%d", content_length);
			putenv(content_length_env);
		}
		//exec*
		execl(path, path, NULL);
		exit(1);
	}
	else{
		close(input[0]);
		close(output[1]);

	    sprintf(line, "HTTP/1.0 200 OK\r\n");
	    send(sock, line, strlen(line), 0);
	    sprintf(line, "Content-Type: text/html;charset=utf-8\r\n");
	    send(sock, line, strlen(line), 0);
	    sprintf(line, "\r\n");
	    send(sock, line, strlen(line), 0);

		int i = 0;
		char c;
		if(strcasecmp(method, "POST") == 0){
			for(; i < content_length; i++){
				recv(sock, &c, 1, 0);
				write(input[1], &c, 1);
			}
		}

		while(read(output[0], &c, 1) > 0){
			send(sock, &c, 1, 0);
		}

		waitpid(id, NULL, 0);
		close(input[1]);
		close(output[0]);
	}
	return 200;
}

int echo_www(int sock, char *path, int size)
{
	char line[MAX];
  char* Path = path;
	clearHeaer(sock);

	int fd = open(path, O_RDONLY);
	if(fd < 0){
		return 404;
	}

	sprintf(line, "HTTP/1.0 200 OK\r\n");
	send(sock, line, strlen(line), 0);
  

  while(*Path != '.')
  {
    Path++;

  }
  if(*(Path+1) == 'p'&&*(Path+2) == 'd' &&*(Path+3) == 'f')
  {
	sprintf(line, "Content-Type:application/pdf;charset=utf-8\r\n");
  }
  
  else if(*(Path+1) == 'j'&&*(Path+2) == 's')
  {
	printf("执行了js");
    sprintf(line, "Content-Type: application/x-javascript;charset=utf-8\r\n");   
  }

  else  if(*(Path+1) == 'c'&&*(Path+2) == 's' &&*(Path+3) == 's')
  {
	printf("执行了css");
        sprintf(line, "Content-Type:text/css;charset=utf-8\r\n");
  }

   else  if(*(Path+1) == 'd'&&*(Path+2) == 'o' &&*(Path+3) == 'c')
  {
        printf("执行了word");
        sprintf(line, "Content-Type:application/msword;charset=utf-8\r\n");
  }
  
  else  if(*(Path+1) == 'x'&&*(Path+2) == 'l' &&*(Path+3) == 's')
  {
        printf("执行了word");
        sprintf(line, "Content-Type:application/vnd.ms-excel;charset=utf-8\r\n");
  }

  else 
  {

	sprintf(line, "Content-Type: text/html;charset=utf-8\r\n");
  }
	
	send(sock, line, strlen(line), 0);
	sprintf(line, "\r\n");
	send(sock, line, strlen(line), 0);

	sendfile(sock, fd, NULL, size);

	close(fd);

	return 200;
}

void *handlerRequest(void *arg)
{
	int sock = (int)arg;
	int status_code = 200;
	char line[MAX];
	char method[MAX/16];
	char url[MAX];
	char path[MAX];
	int cgi = 0;
	char *query_string = NULL;

	getLine(sock, line, sizeof(line));
	printf("%s", line);
	int i = 0;
	int j = 0;
	while(i < sizeof(method)-1 && j < sizeof(line) && !isspace(line[j])){
		method[i] = line[j];
		i++, j++;
	}
	method[i] = '\0';

	while(j < sizeof(line) && isspace(line[j])){
		j++;
	}
	//line[] = GET /a/b/c.html HTTP/1.1
	i = 0;
	while( i < sizeof(url) - 1 && j < sizeof(line) && !isspace(line[j])){
		url[i] = line[j];
		i++, j++;
	}
	url[i] = '\0';

	printf("method: %s, url: %s\n", method, url);

  

	if(strcasecmp(method, "GET") == 0){
	}
	else if(strcasecmp(method, "POST") == 0){
		cgi = 1;
	}
	else{
		//method error
    
		status_code = 400;//
		clearHeaer(sock);
		goto end;
	}

	if(strcasecmp(method, "GET") == 0){
		query_string = url;
		while(*query_string){
			if(*query_string == '?'){
				cgi = 1;
				*query_string = '\0';
				query_string++;
				break;
			}
			query_string++;
		}
	}
  

	sprintf(path, "wwwroot%s", url);
	if(path[strlen(path)-1] == '/'){
		strcat(path, HOME_PAGE);
	}
  
    
	struct stat st;
	if(stat(path, &st) < 0){
  perror("error");

  
		status_code = 404;//
		clearHeaer(sock);
		goto end;
	}
	else{
		//  [wwwroot]   /a/b/c   \0x=100&y=200
		if(S_ISDIR(st.st_mode)){
			strcat(path, "/");
			strcat(path, HOME_PAGE);
		}else if((st.st_mode & S_IXUSR) || \
				(st.st_mode & S_IXGRP) || \
				(st.st_mode & S_IXOTH)){
			cgi = 1;
		}else{
			//Do Nothing
		}

		//method, path, cgi, get->query_string
    printf("马上进入cgi");
		if(cgi)
    
   {
      printf("进入了cgi");
			status_code = exe_cgi(sock, method, path, query_string);
		}else{
    
			status_code = echo_www(sock, path, st.st_size);
		}
	}

end:
	if(status_code != 200){
		echoErrMsg(sock, status_code);
	}
	close(sock);
}

int main(int argc, char *argv[])
{
	if(argc != 2){
		usage(argv[0]);
		return 1;
	}

	int listen_sock = startup(atoi(argv[1]));
	for( ; ; ){
		struct sockaddr_in client;
		socklen_t len = sizeof(client);
		int sock = accept(listen_sock, (struct sockaddr*)&client, &len);
		if(sock < 0){
			perror("accept");
			continue;
		}

		pthread_t tid;
		pthread_create(&tid, NULL, handlerRequest, (void *)sock);
		pthread_detach(tid);
		//pthread_join(tid, NULL);
	}
}


















