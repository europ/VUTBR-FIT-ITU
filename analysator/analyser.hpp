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
        unsigned int count;
        std::vector<wifi_network> data;

    public:

        Data();

        unsigned int size();
        bool reset();
        bool refresh();

        // print all wifi networks
        void DEBUG();
};

#endif
