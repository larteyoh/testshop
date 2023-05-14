#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace neroshop {

class Node; // forward declaration

namespace msgpack {
    std::vector<uint8_t> process(const std::vector<uint8_t>& request);
    std::vector<uint8_t> process(const std::vector<uint8_t>& request, Node& node);

    std::string generate_transaction_id();
    std::string generate_token(const std::string& node_id, const std::string& info_hash, const std::string& secret);
    std::string generate_secret(int length);

    bool send_data(int sockfd, const std::vector<uint8_t>& packed);
    std::string receive_data(int sockfd);
}

}
