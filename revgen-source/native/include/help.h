#ifndef _HELPMENU_H__
#define _HELPMENU_H__

char helpString[] = "\
Usage: revgen [options] <revshell target> \n\
 Options available: \n\
  -c --clip            : Copy revshell payload to clipboard \n\
  --target <IP>        : Use specified target IP (Default box.thm) \n\
  --lhost <IP>         : Use specified local IP \n\
  --ladapter <adapter> : Use specified local adapter to generate lhost (default tun0) \n\
 Revshell targets available: \n\
  --netcat             : Generate netcat revshell \n\
  --bash               : Generate bash revshell";

#endif //_HELPMENU_H__

