/* ECCE 446 02 - Spring 2024 */
/* Socket programming */
/* Jesus Alvarado & Frances Barker */



#include <stdio.h>
#include <sys/socket.h>
#include <sys.types.h>
#include <netdb.h>


#define socket int;

/* for addrinfo, call getaddrinfo() to initalize */

struct addrinfo {
    int ai_flags;                                                   // ai_numericalhost: no name look up. ai_passive: node = 0 and set as server
    int ai_family;                                                  // ipv4, 6 or both
    int ai_socktype;                                                // tcp or udp
    int ai_protocol;                                                // use 0 for any (whatever works best)
    size_t ai_addrlen;                                              // size of ai_addr in bytes
    struct sockaddr *ai_addr;                                       // struct sockaddr _in (ipv4?) OR _in6. This is the nitty-gritty
    char *ai_canonname;                                             // full canonical hostname

    struct addrinfo *ai_next;                                       // linked list, next node, can get back to previous node with reference
}

/* Holds socket address information for many types of sockets */
/* There are other structs in Beejs guide that can be cast for this structure instead, but when or how to use? unsure. 3.3 in guide */

struct sockaddr {
    unsigned short sa_family;                                      // IPv4 or IPv6
    char sa_data[14];                                              // Contains destination address and port number for socket (dont fill by hand!)         
}

// there a lot of the code he went over in class, (hints, socket, close) What else needs to be declared?
