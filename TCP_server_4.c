#include &lt;stdio.h&gt;
#include &lt;string.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;
#include &lt;netinet/in.h&gt;
#define PORT 10137
#define BUF_SIZE 1024
int main() {
int server_fd, new_socket;
struct sockaddr_in address;
char buffer[BUF_SIZE];
int addrlen = sizeof(address);
// Create TCP socket
server_fd = socket(AF_INET, SOCK_STREAM, 0);
// Prepare server address
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT);
// Bind
bind(server_fd, (struct sockaddr *)&amp;address, sizeof(address));
// Listen
listen(server_fd, 3);
printf(&quot;TCP Echo Server listening on port %d...\n&quot;, PORT);

// Accept
new_socket = accept(server_fd, (struct sockaddr *)&amp;address,
(socklen_t*)&amp;addrlen);
while (1) {
memset(buffer, 0, BUF_SIZE);
int bytes = read(new_socket, buffer, BUF_SIZE);
if (bytes &lt;= 0) break;
printf(&quot;Received: %s&quot;, buffer);
send(new_socket, buffer, bytes, 0); // echo back
}
close(new_socket);
close(server_fd);
return 0;
}
