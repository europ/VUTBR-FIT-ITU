#ifndef __constants_hpp
#define __constants_hpp

#define STRING_EMPTY "" // every string is initialize as ""

#define UISL 20  // strlen(unsigned_int_max) == 10

#define SEPARATOR_LINE "==========================\n" // used in method Data::debug()

// hidden wifi stuff
#define REGEX_HIDDEN_WIFI_NETWORK "\\s*--\\s*" // matching regex of SSID and SSIDHEX to find hidden wifi
#define STRING_HIDDEN_WIFI_NETWORK "HIDDEN" // replacing string of SSID and SSIDHEX when wifi is hidden
#define STRING_WIFI_WITHOUT_SECURITY "NONE" // replacing string of SECURITY when wifi is nonsecure

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

#endif
