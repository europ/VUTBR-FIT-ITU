#ifndef __analyser_hpp
#define __analyser_hpp

#include <vector>
#include <string>

// one wifi network structure
struct wifi_network_ID {
    unsigned int UID; // unique id
    std::string SSID;
    std::string BSSID;
    std::string SSIDHEX;
    std::string CHAN;
    std::string FREQ;
    std::string RATE;
    std::string SIGNAL;
    std::string SECURITY;
    std::string RSNFLAGS;
} typedef wifi_network;

class Data {
    private:
        // all wifi networks
        std::vector<wifi_network> data;

    public:
        // constructor
        Data();

        // print all wifi networks
        std::string DEBUG();
};

#endif
