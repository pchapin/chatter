/****************************************************************************
FILE          : ChatDisplay.h
LAST REVISION : 2006-04-09
SUBJECT       : Interface to class for displaying chat messages.
PROGRAMMER    : (C) Copyright 2006 by Peter C. Chapin

Please send comments or bug reports to

     Peter C. Chapin
     Vermont Technical College
     Randolph Center, VT 05061
     pchapin@ecet.vtc.edu
****************************************************************************/

#ifndef CHATDISPLAY_H
#define CHATDISPLAY_H

#include "TextSink.h"

class ChatDisplay : virtual public TextSink_impl {
 public:

  virtual void
  putLine(const std::string &from,
          const std::string &line,
          const Ice::Current &);

  virtual bool
  isEnabled(const Ice::Current &);

 private:
};

#endif
