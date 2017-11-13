#include "analyser.hpp"

#include <iostream>
#include <cstdio>
#include <sstream>

#define SEPARATOR_LINE "==========================\n"
#define STR_EMPTY "-e-"

Data::Data() {

    wifi_network ID;
    ID.UID       = 0;
    ID.SSID     = STR_EMPTY;
    ID.BSSID    = STR_EMPTY;
    ID.SSIDHEX  = STR_EMPTY;
    ID.CHAN     = STR_EMPTY;
    ID.FREQ     = STR_EMPTY;
    ID.RATE     = STR_EMPTY;
    ID.SIGNAL   = STR_EMPTY;
    ID.SECURITY = STR_EMPTY;
    ID.RSNFLAGS = STR_EMPTY;

    std::string cmd = "nmcli -f SSID dev wifi | tail -n +2";
    FILE* shell;
    shell = popen(cmd.c_str(), "r");
    std::string line;
    while(int c = fgetc(shell)) {
        if (c == EOF) {
            break;
        }
        else if (c == '\n') {
            ID.UID++;
            ID.SSID = line;
            Data::data.push_back(ID);
            line.clear();
        }
        else {
            line += c;
        }
    }
}

std::string DEBUG_wifi_network(const wifi_network* ID) {

    // std::to_string() error solved via stringstream
    std::stringstream ss;
    std::string uid_tmp;
    ss << ID->UID;
    ss >> uid_tmp;

    std::string str;
    str += "UID:      " + uid_tmp     + "\n";
    str += "SSID:     " + ID->SSID     + "\n" ;
    str += "BSSID:    " + ID->BSSID    + "\n" ;
    str += "SSIDHEX:  " + ID->SSIDHEX  + "\n" ;
    str += "CHAN:     " + ID->CHAN     + "\n" ;
    str += "FREQ:     " + ID->FREQ     + "\n" ;
    str += "RATE:     " + ID->RATE     + "\n" ;
    str += "SIGNAL:   " + ID->SIGNAL   + "\n" ;
    str += "SECURITY: " + ID->SECURITY + "\n" ;
    str += "RSNFLAGS: " + ID->RSNFLAGS + "\n" ;
    return str;
}

std::string Data::DEBUG() {
    std::string output;
    for (std::vector<wifi_network>::const_iterator i = Data::data.begin(); i != Data::data.end(); ++i) {
        output += SEPARATOR_LINE;
        output += DEBUG_wifi_network(&(*i)); // convert structure of wifi_network to string
    }
    output += SEPARATOR_LINE;
    return output;
}
