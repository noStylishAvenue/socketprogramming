/*Jesus Alvarado
007948292
This is built upon the skeleton that was provided by the professor. 
*/
/* This code is an updated version of the sample code from "Computer Networks: A Systems
 * Approach," 5th Edition by Larry L. Peterson and Bruce S. Davis. Some code comes from
 * man pages, mostly getaddrinfo(3). */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

//#define SERVER_PORT "5432"
//#define MAX_LINE 256

/*
 * Lookup a host IP address and connect to it using service. Arguments match the first two
 * arguments to getaddrinfo(3).
 *
 * Returns a connected socket descriptor or -1 on error. Caller is responsible for closing
 * the returned socket.
 */
int lookup_and_connect( const char *host, const char *service );

int sendall(int s, char *buf, int *len);

int main( int argc, char *argv[] ) {
	const char *host = "www.ecst.csuchico.edu";
	const char *port = "80";
	char *msg = "GET /~kkredo/file.html HTTP/1.0\r\n\r\n";
	int chunk_size;
	int s;
	int len = strlen(msg);

	int bytes = 0;
	int tags = 0;
	int receive;

	/* Checks to for user chunk size*/
	if ( argc > 1 ) {
		chunk_size = atoi(argv[1]);
		if(chunk_size < 5 || chunk_size > 1000){
			fprintf(stderr, "Chunk size is invalid\n");
			exit(1);
		}
	}
	else {
		fprintf( stderr, "No chunk size provided: %s \n", argv[2] );
		exit( 1 );
	}

	/* Dynamic buffer */
	char *buf = malloc(chunk_size + 1);


	/* Lookup IP and connect to server */
	if ( ( s = lookup_and_connect( host,  port) ) < 0 ) {
		exit( 1 );
	}

	/* Sends the messages and checks if it was sent or not*/
/*	while(total_sent < len){
		sent = send(s, msg + total_sent, len - total_sent, 0);
		if(sent < 0){
			printf("Did not send package\n");
			break;
		}
		total_sent += sent;
	}*/

//	printf("Sending Get request: %s\n", msg);

	/* New partial send function*/
	if(sendall(s, msg, &len) == -1){
		perror("sendall");
		printf("We only sent %d bytes because of the error!\n", len);
	}



	/* Recieves the data and parses through it */
	while((receive = recv(s, buf, chunk_size, 0)) > 0){
//		printf("Received chunk: %d bytes\n", receive);
		bytes += receive;
		buf[receive] = '\0';
//		printf("Chunk data: \n%s\n", buf);
		char *scan = buf;

		while((scan = strstr(scan, "<h1>")) != NULL){
			tags++;
//			printf("Found <h1> tag. Total so far: %d\n", tags);
			scan += 4; //skip the tag and continue
		}

	}

	printf("Number of <h1> tags: %d\n", tags);
	printf("Number of bytes: %d\n", bytes);

	free(buf);
	close( s );

	return 0;
}

int lookup_and_connect( const char *host, const char *service ) {
	struct addrinfo hints;
	struct addrinfo *rp, *result;
	int s;

	/* Translate host name into peer's IP address */
	memset( &hints, 0, sizeof( hints ) );
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	hints.ai_protocol = 0;

	if ( ( s = getaddrinfo( host, service, &hints, &result ) ) != 0 ) {
		fprintf( stderr, "stream-talk-client: getaddrinfo: %s\n", gai_strerror( s ) );
		return -1;
	}

	/* Iterate through the address list and try to connect */
	for ( rp = result; rp != NULL; rp = rp->ai_next ) {
		if ( ( s = socket( rp->ai_family, rp->ai_socktype, rp->ai_protocol ) ) == -1 ) {
			continue;
		}

		if ( connect( s, rp->ai_addr, rp->ai_addrlen ) != -1 ) {
			break;
		}

		close( s );
	}
	if ( rp == NULL ) {
		perror( "stream-talk-client: connect" );
		return -1;
	}
	freeaddrinfo( result );

	return s;
}

int sendall(int s, char *buf, int *len){
	int s_total = 0;
	int bytesleft = *len;
	int n;

	while(s_total < *len){
		n = send(s, buf+s_total, bytesleft, 0);
		if(n == -1){
			break;
		}
		s_total += n;
		bytesleft -= n;
	}

	*len = s_total;
	return n==-1?-1:0;
}
