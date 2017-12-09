#ifndef __constants_hpp
#define __constants_hpp

#define STRING_EMPTY ""

#define UISL 20  // strlen(unsigned_int_max) == 10

// shell commands
#define CMD_SSID     "nmcli -f SSID      dev wifi | tail -n +2"
#define CMD_BSSID    "nmcli -f BSSID     dev wifi | tail -n +2"
#define CMD_SSIDHEX  "nmcli -f SSID-HEX  dev wifi | tail -n +2"
#define CMD_CHAN     "nmcli -f CHAN      dev wifi | tail -n +2"
#define CMD_FREQ     "nmcli -f FREQ      dev wifi | tail -n +2"
#define CMD_RATE     "nmcli -f RATE      dev wifi | tail -n +2"
#define CMD_SIGNAL   "nmcli -f SIGNAL    dev wifi | tail -n +2"
#define CMD_SECURITY "nmcli -f SECURITY  dev wifi | tail -n +2"
#define CMD_RSNFLAGS "nmcli -f RSN-FLAGS dev wifi | tail -n +2"


// DEBUG utilities
#define PRINT_VEC(vector) for (auto i = vector.begin(); i != vector.end(); ++i) std::cout << *i << std::endl;
#define PRINT(data) std::cout << data << std::endl;
#define ECHO() std::cout << std::endl;

#define SEPARATOR_LINE "==========================\n"

#endif
