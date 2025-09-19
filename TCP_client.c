#include &lt;stdio.h&gt;
#include &lt;string.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;
#include &lt;netinet/in.h&gt;
#define PORT 10137
#define BUF_SIZE 1024
int main() {
int sock;
struct sockaddr_in server;
char buffer[BUF_SIZE];
// Create socket
sock = socket(AF_INET, SOCK_STREAM, 0);
server.sin_family = AF_INET;
server.sin_port = htons(PORT);
server.sin_addr.s_addr = INADDR_ANY;
connect(sock, (struct sockaddr *)&amp;server, sizeof(server));
while (1) {
printf(&quot;Enter message: &quot;);
fgets(buffer, BUF_SIZE, stdin);
send(sock, buffer, strlen(buffer), 0);
memset(buffer, 0, BUF_SIZE);
read(sock, buffer, BUF_SIZE);
printf(&quot;Echo from server: %s&quot;, buffer);
}
close(sock);
return 0;
}