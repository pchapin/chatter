############################################################################
# FILE        : Makefile
# LAST REVISED: 2004-04-29
# AUTHOR      : Peter C. Chapin; modified by John Oleen.
#
# This is the makefile for the Chatter library. Chatter is a simple
# instant messaging system built on CORBA. See ChatterDoc in the top
# level directory for more information.
############################################################################

EXTRAINCDIR=/usr/local/include
EXTRALIBDIR=/usr/local/lib
LIBS=-lOB -lJTC -pthread -ldl
CXXFLAGS=-c -I . -I$(EXTRAINCDIR) -Wall

OBJS = chatter.o chatter_skel.o CosNaming.o \
  ChatDisplay.o ChatLogger.o ChatRoom.o TextSink.o

all:		chatter.a

#
# These rules tell make how to generate stubs & skeletons. Is there a
# cleaner way to do this? I would think so.
#
chatter.h:	../chatter.idl
	idl -I/usr/local/idl/OB/ ../chatter.idl

chatter.cpp:	../chatter.idl
	idl -I/usr/local/idl/OB/ ../chatter.idl

chatter_skel.h:	../chatter.idl
	idl -I/usr/local/idl/OB/ ../chatter.idl

chatter_skel.cpp:	../chatter.idl
	idl -I/usr/local/idl/OB/ ../chatter.idl

CosNaming.h:	/usr/local/idl/OB/CosNaming.idl
	idl /usr/local/idl/OB/CosNaming.idl

CosNaming.cpp:	/usr/local/idl/OB/CosNaming.idl
	idl /usr/local/idl/OB/CosNaming.idl

CosNaming_skel.h:	/usr/local/idl/OB/CosNaming.idl
	idl /usr/local/idl/OB/CosNaming.idl

CosNaming_skel.cpp:	/usr/local/idl/OB/CosNaming.idl
	idl /usr/local/idl/OB/CosNaming.idl

#
# These rules tell make how to build the executable code.
#

chatter.o:	chatter.cpp chatter.h CosNaming.h
	g++ $(CXXFLAGS) chatter.cpp

chatter_skel.o:	chatter_skel.cpp chatter_skel.h chatter.h CosNaming.h
	g++ $(CXXFLAGS) chatter_skel.cpp

CosNaming.o:	CosNaming.cpp CosNaming.h
	g++ $(CXXFLAGS) CosNaming.cpp

ChatDisplay.o: ChatDisplay.cpp ChatDisplay.h TextSink.h chatter_skel.h CosNaming.h
	g++ $(CXXFLAGS) ChatDisplay.cpp

ChatLogger.o: ChatLogger.cpp ChatLogger.h TextSink.h chatter_skel.h CosNaming.h
	g++ $(CXXFLAGS) ChatLogger.cpp

ChatRoom.o: ChatRoom.cpp ChatRoom.h TextSink.h chatter_skel.h CosNaming.h
	g++ $(CXXFLAGS) ChatRoom.cpp

TextSink.o: TextSink.cpp TextSink.h chatter_skel.h CosNaming.h
	g++ $(CXXFLAGS) TextSink.cpp


# Client and Server builds need revision. Old commands for future reference.
# =====
#client.o:	client.cpp chatter.h CosNaming.h
#	g++ $(CXXFLAGS) client.cpp
#
#server.o:	server.cpp chatter_skel.h chatter.h CosNaming.h
#	g++ $(CXXFLAGS) server.cpp
#
#client:		client.o chatter.o CosNaming.o
#	g++ -o client client.o chatter.o CosNaming.o \
#		-L $(EXTRALIBDIR) $(LIBS)
#
#server:		server.o chatter_skel.o chatter.o CosNaming.o
#	g++ -o server server.o chatter_skel.o chatter.o CosNaming.o \
#		-L $(EXTRALIBDIR) $(LIBS)

chatter.a:	$(OBJS)
	ar -r chatter.a $(OBJS)

#
# Generic clean-up rules
#

clean:
	rm -f chatter.a *.o core

distclean:
	rm -f chatter.a *.o core chatter.cpp chatter.h chatter_skel.* \
              CosNaming.cpp CosNaming.h CosNaming_skel.*
