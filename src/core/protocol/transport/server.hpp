#ifndef SERVER_HPP_NEROSHOP
#define SERVER_HPP_NEROSHOP

#if defined(_WIN32) && defined(NEROSHOP_USE_SYSTEM_SOCKETS)
#include <winsock2.h> // core header for Winsock2
#include <ws2tcpip.h> // header for TCP/IP protocols
#include <iphlpapi.h> // header for IP helper functions
#endif

#if defined(__gnu_linux__) && defined(NEROSHOP_USE_SYSTEM_SOCKETS)
#include <sys/socket.h> // for sockaddr_storage, AF_INET, AF_INET6
#include <netinet/in.h>
#include <arpa/inet.h> // for inet_pton
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
//#include <ifaddrs.h>
#include <errno.h>
#include <poll.h>
#endif

#if defined(NEROSHOP_USE_LIBZMQ)
#include <zmq.h>
#endif

#if defined(NEROSHOP_USE_LIBUV)
#include <uv.h>
#endif

#include <cstdlib>
extern "C" {
#include <raft.h>
}

#include <unordered_map> // std::unordered_map
#include <functional> // std::function
#include <any> // std::any (C++17)
#include <stdexcept> // std::runtime_error
#include <cstring> // memset
#include <random> // std::random_device
#include <vector>

#include "client.hpp" // Client, SocketType::

#define DEFAULT_TCP_PORT 57740 // Use ports between 49152-65535 that are not currently registered with IANA and are rarely used
#define DEFAULT_UDP_PORT 50881

#define DEFAULT_BACKLOG 511

namespace neroshop {
// Reminder: Use TCP for RPC server. UDP for DHT Node server. Maybe TCP for IPC server + client
class Server {
private:
    SocketType socket_type;
public:
    Server();
    Server(SocketType socket_type);
    //Server(unsigned int port);
	~Server();
	bool bind(unsigned int port);
	bool listen(int backlog = DEFAULT_BACKLOG);
	bool accept();
	bool accept_all();
	/*read and write are system calls used for performing I/O operations on file descriptors in Unix-like systems. They can be used for both TCP and UDP sockets, as well as other types of file descriptors such as pipes and regular files.
    For sockets, read and write can be used for both connection-oriented (TCP) and connectionless (UDP) protocols. However, they have some differences in behavior compared to recv and send, which are socket-specific functions. For example, read and write do not have flags like MSG_DONTWAIT or MSG_WAITALL, which can be useful in certain socket scenarios.*/
	void write(const std::string& message);
	std::string read();
	/* sendto() and recvfrom() are specific to UDP sockets. They are used to send and receive datagrams (packets) over a UDP socket.
    For TCP sockets, you would typically use send() and recv() instead. These functions provide a reliable, stream-oriented data transfer mechanism, rather than the packet-oriented mechanism provided by UDP.*/
    void send();
    std::string receive();
	void close(); // closes socket
	void shutdown(); // shuts down entire connection, ending receiving and sending
	
	int get_socket() const;
	const neroshop::Client& get_client(int index) const;
	
	void set_nonblocking(bool nonblocking); // it is recommended to use non-blocking sockets when implementing DHT (Distributed Hash Table) over UDP.

private:
    int sockfd;
    struct sockaddr_in addr;
    std::vector<std::unique_ptr<Client>> clients;
    //raft_server_t* raft;
    friend class Node; // node can now access the server's functions
};
}
#endif
