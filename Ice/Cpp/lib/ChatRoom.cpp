/****************************************************************************
FILE          : ChatRoom.cpp
LAST REVISION : 2007-04-26
SUBJECT       : Implementation of a ChatRoom.
PROGRAMMER    : (C) Copyright 2007 by Peter C. Chapin

Please send comments or bug reports to

     Peter C. Chapin
     Electrical and Computer Engineering Technology
     Vermont Technical College
     Randolph Center, VT 05061
     pchapin@ecet.vtc.edu
****************************************************************************/

#include "ChatRoom.h"

ChatRoom_impl::~ChatRoom_impl()
{
  // Send end-of-text to every member of the chat room.
  member_vec::iterator p;
  for (p = members.begin(); p != members.end(); ++p) {
    (*p)->endOfText();
  }
}


void ChatRoom_impl::putLine(const std::string &from,
                            const std::string &line,
                            const Ice::Current &)
{
  // Pass the input text on to all the members.
  member_vec::iterator p;
  for (p = members.begin(); p != members.end(); ++p) {
    (*p)->putLine(from, line);
  }
}


void ChatRoom_impl::endOfText(const Ice::Current &)
{
  // Send end-of-text to every member of the chat room.
  member_vec::iterator p;
  for (p = members.begin(); p != members.end(); ++p) {
    (*p)->endOfText();
  }
}


bool ChatRoom_impl::isEnabled(const Ice::Current &)
{
  return true;
}


void ChatRoom_impl::add(const chatter::TextSinkPrx &dest,
                        const Ice::Current &)
{
  // Should we check for duplicates? I'm thinking no.
  members.push_back(dest);
}


void ChatRoom_impl::addByName(const std::string &name,
                              const chatter::NameServicePrx &ns,
                              const Ice::Current &)
{
  chatter::TextSinkPrx dest = ns->lookupName(name);
  members.push_back(dest);
}
