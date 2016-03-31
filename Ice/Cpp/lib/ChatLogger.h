/****************************************************************************
FILE          : ChatLogger.h
LAST REVISION : 2006-04-09
SUBJECT       : Interface to class for logging chat messages.
PROGRAMMER    : (C) Copyright 2006 by Peter C. Chapin

Please send comments or bug reports to

     Peter C. Chapin
     Vermont Technical College
     Randolph Center, VT 05061
     pchapin@ecet.vtc.edu
****************************************************************************/

#ifndef CHATLOGGER_H
#define CHATLOGGER_H

#include <fstream>
#include "TextSink.h"

class ChatLogger : virtual public TextSink_impl {
 public:
  ChatLogger(const char *filename) : os(filename) { }

  virtual void
  putLine(const std::string &from,
          const std::string &line,
          const Ice::Current &);

  virtual bool
  isEnabled(const Ice::Current &);

 private:
  std::ofstream os;
};

#endif
