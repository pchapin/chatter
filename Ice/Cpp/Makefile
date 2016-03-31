############################################################################
# FILE        : Makefile
# LAST REVISED: 2013-03-18
# AUTHOR      : Copyright (C) 2013 by Peter C. Chapin
#
# This is the master makefile for the Chatter system.
############################################################################

MAKEFLAGS = -f Makefile

all:
	make -C lib $(MAKEFLAGS)
	make -C programs/nameserver $(MAKEFLAGS)
	make -C programs/roomserver $(MAKEFLAGS)
	make -C programs/Chat $(MAKEFLAGS)

clean:
	make -C lib $(MAKEFLAGS) clean
	make -C programs/nameserver $(MAKEFLAGS) clean
	make -C programs/roomserver $(MAKEFLAGS) clean
	make -C programs/Chat $(MAKEFLAGS) clean
