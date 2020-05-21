#ifndef _GLOBAL_H__
#define _GLOBAL_H__

/* Available targets to generate revshell code for */
typedef enum _reverse_target {
	target_Unknown,
	target_Netcat,
	target_Bash,
} reverse_target;

/* Global struct to hold important data */
struct {
	char *target; 	// Target ip for things like upload
	char *lhost;	// Local host IP for reverse shell generation, if set use this instead of ladapter
	char *ladapter; // Adapter, try to find lhost based on adapter
	int port;

	reverse_target revTarget; // Target to generate reverse shell for

	unsigned clip : 1; // Send reverse shell code to clipboard using xclip
} _global;

#endif //_GLOBAL_H__
