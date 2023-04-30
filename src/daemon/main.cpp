#include <iostream>
#include <string>
#include <future>
#include <thread>
// neroshop
#include "../core/crypto/sha3.hpp"
#include "../core/protocol/p2p/node.hpp" // server.hpp included here (hopefully)
#include "../core/protocol/p2p/routing_table.hpp" // uncomment if using routing_table
#include "../core/protocol/rpc/bencode.hpp"
#include "../core/protocol/rpc/krpc.hpp"
#include "../core/protocol/transport/ip_address.hpp"
#include "../core/protocol/rpc/json_rpc.hpp"
#include "../core/protocol/messages/msgpack.hpp"
#include "../core/database/database.hpp"
#include "../core/tools/logger.hpp"
#include "../core/version.hpp"

#include <cxxopts.hpp>

#define NEROMON_TAG "\033[1;95m[neromon]:\033[0m "

// Daemon will handle database server requests from the client

using namespace neroshop;

Server ipc_server;

std::mutex clients_mutex;
std::mutex server_mutex;
///////////////////
std::mutex response_mutex;
std::condition_variable response_cv;
///////////////////
void handle_requests() {
    // Lock the server mutex
    std::lock_guard<std::mutex> lock(server_mutex);

    // Read msgpack request object from client
	std::string request = neroshop::msgpack::receive_data( ipc_server.get_client(0).get_socket() );//(ipc_server.get_socket());////std::string request_data = ipc_server.read();
	
    // Build a response
    nlohmann::json response_object = {{"food", "bartender"}, {"back", 2}};
    std::vector<uint8_t> packed = nlohmann::json::to_msgpack(response_object);
    
	// Send msg-packed response to client
	neroshop::msgpack::send_data( ipc_server.get_client(0).get_socket(), packed );//ipc_server.write(response_data);
    {
        std::lock_guard<std::mutex> lock(response_mutex);
        response_cv.notify_one();
    }
}
///////////////////
void do_ipc_heartbeat()
{
    // Accept incoming connections and handle clients concurrently
    if(ipc_server.accept() != -1) {
        clients_mutex.lock();
        
        std::thread request_thread(handle_requests);
        request_thread.detach();
        
        clients_mutex.unlock();
    }	
}
// For security purposes, we don't allow any arguments to be passed into the daemon
int main(int argc, char** argv)
{
    //neroshop::Node dht_node("127.0.0.1", DEFAULT_PORT, true);//("0.0.0.0", DEFAULT_PORT);

    std::string daemon { "neromon" };
    std::string daemon_version { daemon + " v" + std::string(NEROSHOP_DAEMON_VERSION) };
    cxxopts::Options options(daemon, std::string(daemon_version));

    options.add_options()
        ("h,help", "Print usage")
        ("v,version", "Show version")
        ("b,bootstrap", "Run this node as a bootstrap node")////, cxxopts::value<std::string>())//("bl,bootstrap_lazy", "Run this node as a bootstrap node without specifying multiaddress")
        //("bl,bootstrap-lazy", "Run this node as a bootstrap node without specifying multiaddress")
        ("c,config", "Path to configuration file")
    ;
    
    auto result = options.parse(argc, argv);
    
    if(result.count("help")) {
        std::cout << options.help() << std::endl;
        exit(0);
    }
    if(result.count("version")) {
        std::cout << daemon << " version " << std::string(NEROSHOP_DAEMON_VERSION) << std::endl;
        exit(0);
    }       
    if(result.count("bootstrap")) { 
        /*std::string multiaddress = result["bootstrap"].as<std::string>(); // ./neromon --bootstrap /ip4/12.144.256.32/tcp/57740 ; ./neromon --bootstrap "/ip6/[2001:0db8:85a3:0000:0000:8a2e:0370:7334]/tcp/4001" // Note that IPv6 addresses are enclosed in square brackets
        std::string ip_address; int port;
        try {
            auto address = neroshop::parse_multiaddress(multiaddress);
            ip_address = std::get<0>(address);
            port = std::get<1>(address);
            std::cout << "IP address + port: " << ip_address << ":" << port << std::endl;
        } catch (std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << " ( Format is: /ip4/<ip_address>/tcp/<port> )" << std::endl;
            exit(1);
        }
        
        assert(port == DEFAULT_TCP_PORT && "Port is not the default value.");*/
        
        std::cout << "Switching to bootstrap mode ...\n";
        //dht_node.set_bootstrap(true);
        // TODO: bootstrap nodes will typically use both TCP and UDP
        // ALWAYS use public ip address for bootstrap nodes so that it is reachable by all nodes in the network, regardless of their location.
    }
    //-------------------------------------------------------
/*
    std::cout << "******************************************************\n";
    std::cout << "Node ID: " << dht_node.get_id() << "\n";
    std::cout << "IP address: " << dht_node.get_ip_address() << "\n";
    std::cout << "Port number: " << dht_node.get_port() << "\n\n";
    std::cout << "******************************************************\n";
    // Join the DHT network
    // ...
    
    std::mutex mutex;
    std::condition_variable cond_var;
    bool is_dht_node_joined = false;

    dht_node.join([&]() {
        // This callback will be called when the DHT node joins the network
        std::unique_lock<std::mutex> lock(mutex);
        is_dht_node_joined = true;
        cond_var.notify_all();
    });

    {
        std::unique_lock<std::mutex> lock(mutex);
        cond_var.wait(lock, [&](){ return is_dht_node_joined; });
    }
    
    std::thread udp_peer_thread([&dht_node](){ dht_node.loop(); });
    udp_peer_thread.detach(); // detach threads so that they run independently
    
*/
    //-------------------------------------------------------
    int port = DEFAULT_TCP_PORT;
	if(ipc_server.bind(port)) {
	    std::cout << NEROMON_TAG "\033[1;97mIPC Server (TCP) bound to port " + std::to_string(port) + "\033[0m\n";
	}
	
	ipc_server.listen();
	
    // Enter daemon loop (main thread)
    while(true) {
        // Execute daemon heartbeat in a new thread
        std::thread ipc_thread(do_ipc_heartbeat);

        // Join the heartbeat thread to wait for it to finish
        ipc_thread.join();        
    }
    //-------------------------------------------------------
	return 0;
}
