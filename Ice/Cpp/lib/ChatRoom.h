/****************************************************************************
FILE          : ChatRoom.h
LAST REVISION : 2007-04-26
SUBJECT       : Interface to class that implements a chat room.
PROGRAMMER    : (C) Copyright 2007 by Peter C. Chapin

Please send comments or bug reports to

     Peter C. Chapin
     Electrical and Computer Engineering Technology
     Vermont Technical College
     Randolph Center, VT 05061
     pchapin@ecet.vtc.edu
****************************************************************************/

#ifndef CHATROOM_H
#define CHATROOM_H

#include <vector>
#include <Ice/Ice.h>
#include "Chatter.h"

class ChatRoom_impl : virtual public chatter::ChatRoom {
 public:

   ~ChatRoom_impl();

    virtual void putLine(const std::string &from,
                         const std::string &line,
                         const Ice::Current &);
    virtual void endOfText(const Ice::Current &);
    virtual bool isEnabled(const Ice::Current &);

    virtual void add(const chatter::TextSinkPrx &dest, const Ice::Current &);
    virtual void addByName(const std::string &name,
                           const chatter::NameServicePrx &ns,
                           const Ice::Current &);
  private:
    typedef std::vector<chatter::TextSinkPrx> member_vec;
    member_vec members;
};

#endif
