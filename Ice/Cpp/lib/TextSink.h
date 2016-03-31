/****************************************************************************
FILE          : TextSink.h
LAST REVISION : 2013-04-08
SUBJECT       : Interface to base implementation of a TextSink servant.
PROGRAMMER    : (C) Copyright 2013 by Peter C. Chapin

This class is intended to server as a base for "real" TextSink objects. Classes derived from
this base eat all endOfText() calls and are always enabled (unless, of course, they override the
appropriate methods). It is only necessary for each such class to overrride the putLine()
method.

Please send comments or bug reports to

     Peter C. Chapin
     Computer Information Systems Department
     Vermont Technical College
     Williston, VT 05495
     PChapin@vtc.vsc.edu
****************************************************************************/

#ifndef TEXTSINK_H
#define TEXTSINK_H

#include <string>
#include "Chatter.h"

#include <Ice/Ice.h>

class TextSink_impl : virtual public chatter::TextSink {
public:

    virtual void
    putLine(const std::string &from,
            const std::string &line,
            const Ice::Current &) = 0;

    virtual void endOfText(const Ice::Current &);

    virtual bool isEnabled(const Ice::Current &);

 protected:
};

#endif
