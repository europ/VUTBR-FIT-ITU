#include <cstdio>
#include <regex>
#include <iostream>

#include "analyser.hpp"
#include "constants.hpp"
#include "macros.hpp"


//#################################################################################################
// VARIABLES

std::regex regex_pattern (REGEX_HIDDEN_WIFI_NETWORK);

//#################################################################################################
// FUNCTIONS

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

bool execute_cmd(std::vector<std::string>& data, std::string cmd) {

    FILE* shell;
    shell = popen(cmd.c_str(), "r");
    if (shell == NULL)
        return false;

    std::string line;
    while(int c = fgetc(shell)) {
        if (c == EOF) {
            break;
        }
        else if (c == '\n') {
            data.push_back(line);
            line.clear();
        }
        else {
            line += c;
        }
    }

    return true;
}

std::string DEBUG_wifi_network(const wifi_network* ID) {
    std::string str;

    str += "UID:      " + uitos(ID->UID) + "\n";
    str += "SSID:     " + ((std::regex_match(ID->SSID,regex_pattern))    ? STRING_HIDDEN_WIFI_NETWORK : ID->SSID)    + "\n";
    str += "BSSID:    " + ID->BSSID      + "\n";
    str += "SSIDHEX:  " + ((std::regex_match(ID->SSIDHEX,regex_pattern)) ? STRING_HIDDEN_WIFI_NETWORK : ID->SSIDHEX) + "\n";
    str += "CHAN:     " + ID->CHAN       + "\n";
    str += "FREQ:     " + ID->FREQ       + "\n";
    str += "RATE:     " + ID->RATE       + "\n";
    str += "SIGNAL:   " + ID->SIGNAL     + "\n";
    str += "SECURITY: " + ID->SECURITY   + "\n";
    str += "RSNFLAGS: " + ID->RSNFLAGS   + "\n";
    return str;
}

//#################################################################################################
// CLASS DATA METHODS

Data::Data() { // Constructor
    count = 0;
    data.clear();
}

void Data::debug() {
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


unsigned int Data::size() {
    return count;
}

void Data::reset() {
    count = 0;
    data.clear();
}

bool Data::refresh() {

    this->reset();

    std::vector<std::string>
        VEC_SSID,
        VEC_BSSID,
        VEC_SSIDHEX,
        VEC_CHAN,
        VEC_FREQ,
        VEC_RATE,
        VEC_SIGNAL,
        VEC_SECURITY,
        VEC_RSNFLAGS
    ;

    // vectors initialization
    if ( !execute_cmd(VEC_SSID,     CMD_SSID    ) ) return false;
    if ( !execute_cmd(VEC_BSSID,    CMD_BSSID   ) ) return false;
    if ( !execute_cmd(VEC_SSIDHEX,  CMD_SSIDHEX ) ) return false;
    if ( !execute_cmd(VEC_CHAN,     CMD_CHAN    ) ) return false;
    if ( !execute_cmd(VEC_FREQ,     CMD_FREQ    ) ) return false;
    if ( !execute_cmd(VEC_RATE,     CMD_RATE    ) ) return false;
    if ( !execute_cmd(VEC_SIGNAL,   CMD_SIGNAL  ) ) return false;
    if ( !execute_cmd(VEC_SECURITY, CMD_SECURITY) ) return false;
    if ( !execute_cmd(VEC_RSNFLAGS, CMD_RSNFLAGS) ) return false;

    // pass only if every vector has the same size
    count = VEC_SSID.size();
    //if (count != VEC_SSID.size()) return false; // useless check
    if ( count != VEC_BSSID.size()    ) return false;
    if ( count != VEC_SSIDHEX.size()  ) return false;
    if ( count != VEC_CHAN.size()     ) return false;
    if ( count != VEC_FREQ.size()     ) return false;
    if ( count != VEC_RATE.size()     ) return false;
    if ( count != VEC_SIGNAL.size()   ) return false;
    if ( count != VEC_SECURITY.size() ) return false;
    if ( count != VEC_RSNFLAGS.size() ) return false;

    // loop variable
    wifi_network tmp;

    for (unsigned int i=0; i<count; ++i) {

        // tmp initialization
        tmp.UID      = i;
        tmp.SSID     = VEC_SSID.front();
        tmp.BSSID    = VEC_BSSID.front();
        tmp.SSIDHEX  = VEC_SSIDHEX.front();
        tmp.CHAN     = VEC_CHAN.front();
        tmp.FREQ     = VEC_FREQ.front();
        tmp.RATE     = VEC_RATE.front();
        tmp.SIGNAL   = VEC_SIGNAL.front();
        tmp.SECURITY = VEC_SECURITY.front();
        tmp.RSNFLAGS = VEC_RSNFLAGS.front();

        // save network
        data.push_back(tmp);

        // pop first element from every vector
        VEC_SSID.erase(VEC_SSID.begin());
        VEC_BSSID.erase(VEC_BSSID.begin());
        VEC_SSIDHEX.erase(VEC_SSIDHEX.begin());
        VEC_CHAN.erase(VEC_CHAN.begin());
        VEC_FREQ.erase(VEC_FREQ.begin());
        VEC_RATE.erase(VEC_RATE.begin());
        VEC_SIGNAL.erase(VEC_SIGNAL.begin());
        VEC_SECURITY.erase(VEC_SECURITY.begin());
        VEC_RSNFLAGS.erase(VEC_RSNFLAGS.begin());
    }

    return true;
}

std::string Data::get_SSID(unsigned int idx) {
    std::string str = STRING_EMPTY;
    if ((!data.empty()) && (idx <= count)) {
        if (std::regex_match(data[idx].SSID,regex_pattern)) {
            str = STRING_HIDDEN_WIFI_NETWORK;
        }
        else {
            str = data[idx].SSID;
        }
    }
    return str;
}

std::string Data::get_BSSID(unsigned int idx) {
    std::string str = STRING_EMPTY;
    if ((!data.empty()) && (idx <= count)) {
        str = data[idx].BSSID;
    }
    return str;
}

std::string Data::get_SSIDHEX(unsigned int idx) {
    std::string str = STRING_EMPTY;
    if ((!data.empty()) && (idx <= count)) {
        if (std::regex_match(data[idx].SSIDHEX,regex_pattern)) {
            str = STRING_HIDDEN_WIFI_NETWORK;
        }
        else {
            str = data[idx].SSIDHEX;
        }
    }
    return str;
}

std::string Data::get_CHAN(unsigned int idx) {
    std::string str = STRING_EMPTY;
    if ((!data.empty()) && (idx <= count)) {
        str = data[idx].CHAN;
    }
    return str;
}

std::string Data::get_FREQ(unsigned int idx) {
    std::string str = STRING_EMPTY;
    if ((!data.empty()) && (idx <= count)) {
        str = data[idx].FREQ;
    }
    return str;
}

std::string Data::get_RATE(unsigned int idx) {
    std::string str = STRING_EMPTY;
    if ((!data.empty()) && (idx <= count)) {
        str = data[idx].RATE;
    }
    return str;
}

std::string Data::get_SIGNAL(unsigned int idx) {
    std::string str = STRING_EMPTY;
    if ((!data.empty()) && (idx <= count)) {
        str = data[idx].SIGNAL;
    }
    return str;
}

std::string Data::get_SECURITY(unsigned int idx) {
    std::string str = STRING_EMPTY;
   // if ((!data.empty()) && (idx <= count)) {
   //    str = data[idx].SECURITY;
   // }

    if ((!data.empty()) && (idx <= count)) {
        if (std::regex_match(data[idx].SECURITY,regex_pattern)) {
            str = "NONE";
        }
        else {
            str = data[idx].SECURITY;
        }
    }

    return str;
}

std::string Data::get_RSNFLAGS(unsigned int idx) {
    std::string str = STRING_EMPTY;
    if ((!data.empty()) && (idx <= count)) {
        str = data[idx].RSNFLAGS;
    }
    return str;
}
