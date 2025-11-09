#include &lt;stdio.h&gt;
#include &lt;string.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;
#include &lt;netinet/in.h&gt;
#define PORT 10137

#define BUF_SIZE 1024
int main() {
int sockfd;
struct sockaddr_in server;
char buffer[BUF_SIZE];
socklen_t len = sizeof(server);
sockfd = socket(AF_INET, SOCK_DGRAM, 0);
server.sin_family = AF_INET;
server.sin_port = htons(PORT);
server.sin_addr.s_addr = INADDR_ANY;
while (1) {
printf(&quot;Enter message: &quot;);
fgets(buffer, BUF_SIZE, stdin);
sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&amp;server,
len);
memset(buffer, 0, BUF_SIZE);
recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&amp;server,
&amp;len);
printf(&quot;Echo from server: %s&quot;, buffer);
}
close(sockfd);
return 0;
}
