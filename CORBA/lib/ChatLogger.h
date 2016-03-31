/****************************************************************************
FILE          : ChatLogger.h
LAST REVISION : 2004-04-20
SUBJECT       : Interface to class for logging chat messages.
PROGRAMMER    : (C) Copyright 2004 by Peter C. Chapin

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

class ChatLogger : public TextSink_impl {
 public:
  ChatLogger(const char *filename) : os(filename) { }

  virtual CORBA::Boolean is_enabled()
    throw(CORBA::SystemException);

  virtual void put_line(const char *from, const char *line)
    throw(CORBA::SystemException);

 private:
  std::ofstream os;
};

#endif
