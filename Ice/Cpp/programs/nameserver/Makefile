############################################################################
# FILE   : Makefile
# SUBJECT: Makefile for the nameserver application.
# AUTHOR : Copyright (C) 2013 by Peter C. Chapin
#
# This program is needed for resolving nicknames to Object proxies.
############################################################################

ICE_LIBS     = -L$(ICE_HOME)/lib -lIce -lIceUtil
CHATTER_LIBD = ../../lib
CHATTER_LIB  = $(CHATTER_LIBD)/Chatter.a
CPPFLAGS     = -Wall -g -I$(ICE_HOME)/include -I. -I$(CHATTER_LIBD)

all:		nameserver

Chatter.h:	../../../Chatter.ice
		slice2cpp ../../../Chatter.ice

Chatter.cpp:	../../../Chatter.ice
		slice2cpp ../../../Chatter.ice

nameserver:	nameserver.o Chatter.o $(CHATTER_LIB)
		g++ -o nameserver nameserver.o Chatter.o $(ICE_LIBS) $(CHATTER_LIB)

nameserver.o:	nameserver.cpp Chatter.h $(CHATTER_LIBD)/NameService.h
Chatter.o:	Chatter.cpp Chatter.h

clean:
	rm -f *.o nameserver Chatter.h Chatter.cpp
