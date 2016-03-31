############################################################################
# FILE   : Makefile
# SUBJECT: Makefile for a basic Chat application using Chatter.
# AUTHOR : Copyright (C) 2013 by Peter C. Chapin
#
# This program is a basic, interactive instant messaging program.
############################################################################

ICE_LIBS     = -L$(ICE_HOME)/lib -lIce -lIceUtil
CHATTER_LIBD = ../../lib
CHATTER_LIB  = $(CHATTER_LIBD)/Chatter.a
CPPFLAGS     = -Wall -g -I$(ICE_HOME)/include -I. -I$(CHATTER_LIBD)

all:		client server

Chatter.h:	../../../Chatter.ice
		slice2cpp ../../../Chatter.ice

Chatter.cpp:	../../../Chatter.ice
		slice2cpp ../../../Chatter.ice

server:		server.o Chatter.o $(CHATTER_LIB)
		g++ -o server server.o Chatter.o $(ICE_LIBS) $(CHATTER_LIB)

client:		client.o Chatter.o $(CHATTER_LIB)
		g++ -o client client.o Chatter.o $(ICE_LIBS) $(CHATTER_LIB)

# Object file dependencies
##########################

server.o:	server.cpp Chatter.h \
		$(CHATTER_LIBD)/NameService.h \
		$(CHATTER_LIBD)/ChatDisplay.h \
		$(CHATTER_LIBD)/TextSink.h \

client.o:	client.cpp Chatter.h \
		$(CHATTER_LIBD)/NameService.h

Chatter.o:	Chatter.cpp Chatter.h


# Various utilities
###################
clean:
	rm -f *.o client server Chatter.h Chatter.cpp
