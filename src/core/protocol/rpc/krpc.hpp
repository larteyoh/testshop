#pragma once

#include "bencode.hpp"
// KRPC (Kademlia RPC) is considered an RPC (Remote Procedure Call) protocol. It is a protocol used by the Kademlia distributed hash table (DHT) to allow nodes in the network to communicate with each other and exchange data. KRPC allows nodes to send and receive messages containing method calls and their parameters, much like other RPC protocols such as XML-RPC or JSON-RPC. However, unlike those protocols, KRPC uses a binary message format that is optimized for efficiency and compactness.
namespace neroshop {

namespace rpc {

static const std::vector<std::string> query_types = {
    "ping",
    "find_node",
    "get_peers",
    "announce_peer",
    "get",
    "put",
};
 
std::string krpc_process(const std::string& request);

}

}