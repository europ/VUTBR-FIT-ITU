#ifndef __constants_hpp
#define __constants_hpp

#define UISL 20  // strlen(unsigned_int_max) == 10

// shell commands
#define CMD_SSID     "nmcli -f SSID     dev wifi | tail -n +2"
#define CMD_BSSID    "nmcli -f BSSID    dev wifi | tail -n +2"
#define CMD_SSIDHEX  "nmcli -f SSIDHEX  dev wifi | tail -n +2"
#define CMD_CHAN     "nmcli -f CHAN     dev wifi | tail -n +2"
#define CMD_FREQ     "nmcli -f FREQ     dev wifi | tail -n +2"
#define CMD_RATE     "nmcli -f RATE     dev wifi | tail -n +2"
#define CMD_SIGNAL   "nmcli -f SIGNAL   dev wifi | tail -n +2"
#define CMD_SECURITY "nmcli -f SECURITY dev wifi | tail -n +2"
#define CMD_RSNFLAGS "nmcli -f RSNFLAGS dev wifi | tail -n +2"

#endif