############################################################################
# FILE   : Makefile
# SUBJECT: Makefile for the roomserver application.
# AUTHOR : Copyright (C) 2013 by Peter C. Chapin
#
# This program manages chat rooms.
############################################################################

ICE_LIBS     = -L$(ICE_HOME)/lib -lIce -lIceUtil
CHATTER_LIBD = ../../lib
CHATTER_LIB  = $(CHATTER_LIBD)/Chatter.a
CPPFLAGS     = -Wall -g -I$(ICE_HOME)/include -I. -I$(CHATTER_LIBD)

all:		roomserver

Chatter.h:	../../../Chatter.ice
		slice2cpp ../../../Chatter.ice

Chatter.cpp:	../../../Chatter.ice
		slice2cpp ../../../Chatter.ice

roomserver:	roomserver.o Chatter.o $(CHATTER_LIB)
		g++ -o roomserver roomserver.o Chatter.o $(ICE_LIBS) $(CHATTER_LIB)

roomserver.o:	roomserver.cpp Chatter.h $(CHATTER_LIBD)/RoomManager.h
Chatter.o:	Chatter.cpp Chatter.h

clean:
	rm -f *.o roomserver Chatter.h Chatter.cpp
