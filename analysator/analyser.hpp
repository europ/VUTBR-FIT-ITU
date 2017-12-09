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

        void reset();

        /*
         * Method returns actual data (vector) size.
         */
        unsigned int size();
        
        /*
         * RESET is required BEFORE refresh()
         * return value:
         *     on ERROR false
         *     on SUCCESS true
         */
        bool refresh();

        /*
         * METHODS get_*(idx)
         * 
         * return value:
         *     on ERROR empty string
         *     on SUCCESS string
         */
        std::string get_SSID(unsigned int idx);
        std::string get_BSSID(unsigned int idx);
        std::string get_SSIDHEX(unsigned int idx);
        std::string get_CHAN(unsigned int idx);
        std::string get_FREQ(unsigned int idx);
        std::string get_RATE(unsigned int idx);
        std::string get_SIGNAL(unsigned int idx);
        std::string get_SECURITY(unsigned int idx);
        std::string get_RSNFLAGS(unsigned int idx);

        // print all wifi networks
        void debug();
};

#endif
