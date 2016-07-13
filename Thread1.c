#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <arpa/inet.h>
#include<string.h>
int arr[10];
int n;
int read_in(int socket, char *buf, int len)
{
 char *s = buf;
 int slen = len;
 int c = recv(socket, s, slen, 0);
 while ((c > 0) && (s[c-1] != '\n')) {
 s += c; slen -= c;
 c = recv(socket, s, slen, 0);
 }
 if (c < 0)
 return c;
 else if (c == 0)
 buf[0] = '\0';
 else
 s[c-1]='\0';
 return len - slen;
}
void * thread_function(void * input)
{
		char  * msg="Hello  Client";
		int connect_d,i;
		int  *ptr=(void *)input;
		char *buff = (char *) malloc(sizeof(char)*20);
		while(1)
		{
			read(*ptr,buff,20);
			for(i=0;i<n;i++)
			if (send(arr[i], buff, strlen(msg), 0) == -1)
	 		{
				printf("\n Error in Sedning Message.");
			}
		}
		
			
}

int main()
{
	int listener_d,c;
	/*pthread_t * thread1;
	thread1=(pthread_t *)malloc(sizeof(pthread_t));
	pthread_create(thread1,0,thread_function,0);
	pthread_join(*thread1,0); */
	listener_d =socket (PF_INET, SOCK_STREAM, 0);
	struct sockaddr_in name;
	name.sin_family = PF_INET;
	name.sin_port = (in_port_t)htons(30000);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	c=bind (listener_d, (struct sockaddr *) &name, sizeof(name));
	listen(listener_d, 10);
	while(1)
	{
		int  *ptr=(int  *)malloc(sizeof(int));
		struct sockaddr_storage client_addr;
		unsigned int address_size = sizeof(client_addr);
		
		int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
		arr[n++]=connect_d;
		ptr=&connect_d;
		pthread_t * thread1;
		thread1=(pthread_t *)malloc(sizeof(pthread_t));
		pthread_create(thread1,0,thread_function,ptr);
		
	}


}
