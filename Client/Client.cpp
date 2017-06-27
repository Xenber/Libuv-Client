#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <uv.h>

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"libuv.lib")
#pragma comment(lib,"IPHLPAPI.lib")
#pragma comment(lib,"Psapi.lib")
#pragma comment(lib,"Userenv.lib")

int client_port = 7000;
uv_loop_t* loop;
uv_tcp_t tcpClient;
uv_connect_t* req;
void on_new_connection(uv_stream_t* server, int status);



void on_send(uv_udp_t *req, ssize_t nread, const uv_buf_t *buf, const struct sockaddr *addr, unsigned flags)
{

}



void on_new_connection(uv_stream_t *server, int status) {
	if (status < 0) {
		fprintf(stderr, "New connection error %s\n", uv_strerror(status));
		// error!
		return;
	}

	uv_tcp_t *client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
	uv_tcp_init(loop, client);
	
		//uv_read_start((uv_stream_t*)client, alloc_buffer, echo_read);
	printf("accept!\r\n");
	uv_udp_send_t send_req;
	uv_udp_t send_socket;
	ssize_t nread;
	const uv_buf_t buf;
	const struct sockaddr *addr;
	

	while (1)
	{
		uv_udp_send(&send_req, &send_socket, &buf, 1, (const struct sockaddr *)&addr, (uv_udp_send_cb)on_send);
	}

	Sleep(1000);
	
	
}

int tcp_listener()
{

	uv_tcp_t* socket = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
	uv_tcp_init(loop, socket);

	uv_connect_t* connect = (uv_connect_t*)malloc(sizeof(uv_connect_t));

	struct sockaddr_in dest;
	uv_ip4_addr("127.0.0.1", 7000, &dest);

	uv_tcp_connect(connect, socket, (const sockaddr*)&dest, (uv_connect_cb)on_new_connection);


	return 0;
}




int main() {
	loop = uv_default_loop();
	tcp_listener();
	return uv_run(loop, UV_RUN_DEFAULT);
}
