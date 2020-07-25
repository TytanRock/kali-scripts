#ifndef _SHELLWRAPPER_H__
#define _SHELLWRAPPER_H__

/* This section will wrap our netcat shell so that we can interact with it beyond the normal use */

enum trScripts {
	stabilize_python, // Spawn a PTY using python's -c and pty module
	stabilize_script, // Spawn a PTY using John Hammond's /bin/script method in the sweetrice video

	upload,		  // Upload a file using netcat
};

void startWrapper();

#endif //_SHELLWRAPPER_H__
