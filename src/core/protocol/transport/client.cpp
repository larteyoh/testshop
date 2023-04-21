#include "client.hpp"

#include "../../util/logger.hpp"

#include <cstring> // memset

neroshop::Client::Client() : sockfd(-1) {
    create();
}
////////////////////
neroshop::Client::Client(int sockfd, struct sockaddr_in client_addr) {
    this->sockfd = sockfd;
    this->addr = client_addr;
}
////////////////////
neroshop::Client::~Client() {
    if(sockfd > 0) {
        close();
        sockfd = -1;
    }
}
////////////////////
void neroshop::Client::create() {
    #if defined(__gnu_linux__) && defined(NEROSHOP_USE_SYSTEM_SOCKETS)
    if(sockfd > 0) return; // socket must be -1 before a new one can be created (if socket is not null then it means it was never closed)
	sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		neroshop::print("::socket: failed to create a socket", 1);
	}    
    #endif
}
////////////////////
bool neroshop::Client::connect(unsigned int port, std::string address) {
    #if defined(__gnu_linux__) && defined(NEROSHOP_USE_SYSTEM_SOCKETS)
	struct hostent * host = gethostbyname(address.c_str());
	if(host == nullptr) {
		std::cerr << "No host to connect to" << std::endl;
	}
	struct sockaddr_in socket_addr;	// IPv4 
	//struct sockaddr_in6 // IPv6	
	memset(&socket_addr, 0, sizeof(struct sockaddr_in));//bzero((char *) &socket_addr, sizeof(socket_addr));
    socket_addr.sin_family = AF_INET;
    bcopy((char *)host->h_addr, (char *)&socket_addr.sin_addr.s_addr, host->h_length);
    socket_addr.sin_port = htons(port);
	// connect to a server	
	if(::connect(sockfd, (struct sockaddr *)(&socket_addr), sizeof(socket_addr)) < 0) {
		std::cerr << "Could not connect to server" << std::endl; // port is closed
		close(); // kill socket // https://linux.die.net/man/3/connect => Application Usage
		return false;
	}
	return true;    
    #endif
    return false;
}
////////////////////
void neroshop::Client::write(const std::string& text) {
    #if defined(__gnu_linux__) && defined(NEROSHOP_USE_SYSTEM_SOCKETS)
	ssize_t write_result = ::write(sockfd, text.c_str(), text.length());
	if(write_result < 0) { // -1 = error
		std::cerr << "Could not write to server" << std::endl;
	}    
    #endif
}
////////////////////
std::string neroshop::Client::read()
{
    #if defined(__gnu_linux__) && defined(NEROSHOP_USE_SYSTEM_SOCKETS)
    char buffer[1024];
	memset(buffer, 0, 1024); // clear buffer (fills buffer with 0's) before reading into buffer//bzero(buffer, 1024); // bzero is deprecated
	ssize_t read_result = ::read(sockfd, buffer, 1023);
	if(read_result < 0) {
		std::cerr << "Could not read from server" << std::endl;	
	}
	return static_cast<std::string>(buffer);    
    #endif
    return "";
}
////////////////////	
void neroshop::Client::close() {
	::close(sockfd);
}
////////////////////
void neroshop::Client::shutdown() {
    ::shutdown(sockfd, SHUT_RDWR); // SHUT_RD, SHUT_WR, SHUT_RDWR
}
////////////////////
////////////////////
void neroshop::Client::disconnect() { // if only shutdown() is called, the client socket will still be alive which is why we must call close() as well
	shutdown();
	close();
}
////////////////////
bool neroshop::Client::reconnect(unsigned int port, std::string address) { // kill socket first before attempting to re-connect
    close();
    return connect(port, address);
}
////////////////////
neroshop::Client * neroshop::Client::get_main_client() {
    static neroshop::Client client_obj {};
    return &client_obj;
}
////////////////////
////////////////////
bool neroshop::Client::is_connected() const { // https://stackoverflow.com/a/4142038 // can only work when close() is called
    return true;
}
////////////////////
////////////////////
////////////////////