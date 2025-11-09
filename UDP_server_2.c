#include &lt;stdio.h&gt;
#include &lt;string.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;
#include &lt;netinet/in.h&gt;
#define PORT 10137
#define BUF_SIZE 1024
int main() {
int sockfd;
struct sockaddr_in server, client;
char buffer[BUF_SIZE];
socklen_t len = sizeof(client);
sockfd = socket(AF_INET, SOCK_DGRAM, 0);
server.sin_family = AF_INET;
server.sin_port = htons(PORT);
server.sin_addr.s_addr = INADDR_ANY;
bind(sockfd, (struct sockaddr *)&amp;server, sizeof(server));
printf(&quot;UDP Echo Server listening on port %d...\n&quot;, PORT);
while (1) {
memset(buffer, 0, BUF_SIZE);
recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&amp;client,
&amp;len);
printf(&quot;Received: %s&quot;, buffer);
sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&amp;client,
len);
}
close(sockfd);
return 0;
}
