#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace neroshop {

namespace msgpack {
    //process(const std::string&);

    bool send_data(int sockfd, const std::vector<uint8_t>& packed);
    std::string receive_data(int sockfd);
}

}