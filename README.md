# ping_win

Compilation:
root permissions are required for the socket to be created.
To build as root run:

sudo make

This will automatically set setuid and setgid so that it can be run as
not root. Or you can build without root, but will have to sudo every time
you run the program.

Usage:

./ping_win [-c count] [-t ttl] destination

Where destination is the host you want to connect to in hostname or ip
address format, for example:

./ping_win cloudflare.com
or
./ping_win 1.1.1.1

There are also two flags: -c for count and -t for time to live. Ex:

./ping_win -c 10
and
./ping_win -c10
Will only send 10 packets.

./ping_win -t 3
Will send the packet's time to live to 3

Thank you for your time, I documented some of my thoughts in the
process folder so feel free to look at that if you want to see more
about the development process of this program, I'll also be implementing
more features that I didn't get to implement here on my github:
https://github.com/rsilva42/ping_win
It may be private for a short time after my submission to respect
the coding challenge.
Happy to learn so much; and stay safe!
-Rodrigo Silva
