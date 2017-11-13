#include <cstdio>
#include <iostream>

#include "analyser.hpp"
#include "constants.hpp"

#define PRINT_VEC(vector) for (auto i = vector.begin(); i != vector.end(); ++i) std::cout << *i << std::endl;
#define PRINT(data) std::cout << data << std::endl;
#define ECHO() std::cout << std::endl;

#define SEPARATOR_LINE "==========================\n"
#define STRING_EMPTY ""

//#################################################################################################

std::string uitos(unsigned int num) {
    char str[UISL];
    sprintf (str, "%u", num);
    return str;
}

void wifi_network_init(wifi_network* ID) {
    ID->UID      = 0;
    ID->SSID     = STRING_EMPTY;
    ID->BSSID    = STRING_EMPTY;
    ID->SSIDHEX  = STRING_EMPTY;
    ID->CHAN     = STRING_EMPTY;
    ID->FREQ     = STRING_EMPTY;
    ID->RATE     = STRING_EMPTY;
    ID->SIGNAL   = STRING_EMPTY;
    ID->SECURITY = STRING_EMPTY;
    ID->RSNFLAGS = STRING_EMPTY;
}

//#################################################################################################

Data::Data() { // Constructor
    count = 0;
    data.clear();
}

unsigned int Data::size() {
    return count;
}

bool Data::reset() {
    count = 0;
    data.clear();   
}

bool Data::refresh() {

    Data:data.clear();

    wifi_network ID;
    wifi_network_init(&ID);
    
    std::string cmd = CMD_SSID;
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
    std::string str;
    str += "UID:      " + uitos(ID->UID) + "\n";
    str += "SSID:     " + ID->SSID       + "\n";
    str += "BSSID:    " + ID->BSSID      + "\n";
    str += "SSIDHEX:  " + ID->SSIDHEX    + "\n";
    str += "CHAN:     " + ID->CHAN       + "\n";
    str += "FREQ:     " + ID->FREQ       + "\n";
    str += "RATE:     " + ID->RATE       + "\n";
    str += "SIGNAL:   " + ID->SIGNAL     + "\n";
    str += "SECURITY: " + ID->SECURITY   + "\n";
    str += "RSNFLAGS: " + ID->RSNFLAGS   + "\n";
    return str;
}

void Data::DEBUG() {
    if (data.empty()) {
        std::cout << "NO DATA\n" << std::endl;
    }
    else {
        std::string output;
        for (std::vector<wifi_network>::const_iterator i = data.begin(); i != data.end(); ++i) {
            output += SEPARATOR_LINE + DEBUG_wifi_network(&(*i)); // convert structure of wifi_network to string
        }
        output += SEPARATOR_LINE;        
        std::cout << output;
    }
}
