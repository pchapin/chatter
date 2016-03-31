############################################################################
# FILE   : Makefile
# SUBJECT: Makefile for the Chatter library.
# AUTHOR : (C) Copyright 2013 by Peter C. Chapin
#
# Chatter is a simple instant messaging system built on Ice. See the documentation folder off
# the root of the Chatter distribution for more information.
############################################################################

CPPFLAGS = -Wall -g -I$(ICE_HOME)/include -I.

OBJS = Chatter.o     \
       NameService.o \
       ChatDisplay.o \
       ChatLogger.o  \
       ChatRoom.o    \
       RoomManager.o \
       TextSink.o

all:	Chatter.a

# The following dependencies are for the output of the slice compiler.
# =====
Chatter.h:	../../Chatter.ice
	slice2cpp ../../Chatter.ice

Chatter.cpp:	../../Chatter.ice
	slice2cpp ../../Chatter.ice

# The following dependency forces the compilation of the slice output.
# =====
Chatter.o:	 Chatter.cpp Chatter.h


# The following dependencies describe the chatter library object files.
# =====
NameService.o:	NameService.cpp NameService.h Chatter.h
ChatDisplay.o:	ChatDisplay.cpp ChatDisplay.h TextSink.h Chatter.h
ChatLogger.o:	ChatLogger.cpp ChatLogger.h TextSink.h Chatter.h
ChatRoom.o:	ChatRoom.cpp ChatRoom.h TextSink.h Chatter.h
RoomManager.o:	RoomManager.cpp RoomManager.h ChatRoom.h Chatter.h
TextSink.o:	TextSink.cpp TextSink.h Chatter.h

# The library build command
# =====
Chatter.a:	$(OBJS)
	ar -rc Chatter.a $(OBJS)


# Various utility targets
# =====
clean:
	rm -f *.o *.a Chatter.h Chatter.cpp
