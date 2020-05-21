#ifndef _HELPMENU_H__
#define _HELPMENU_H__

char helpString[] = "\
Usage: trShell [options] <revshell target> \n\
 Options available: \n\
  -c --clip               : Copy revshell payload to clipboard (uses xclip) \n\
  -t --target <IP>        : Use specified target IP (Default box.thm) \n\
  -h --lhost <IP>         : Use specified local IP \n\
  -a --ladapter <adapter> : Use specified local adapter to generate lhost (default tun0), may be unstable \n\
  -p --port <portNum>     : Use specified port (default 7762) \n\
 Revshell targets available: \n\
  -n --netcat             : Generate netcat revshell \n\
  -b --bash               : Generate bash revshell";

#endif //_HELPMENU_H__

