/****************************************************************************
FILE          : RoomManager.h
LAST REVISION : 2007-04-25
SUBJECT       : Interface to class that implements a chat room manager.
PROGRAMMER    : (C) Copyright 2007 by Peter C. Chapin

Please send comments or bug reports to

     Peter C. Chapin
     Electrical and Computer Engineering Technology
     Vermont Technical College
     Randolph Center, VT 05061
     pchapin@ecet.vtc.edu
****************************************************************************/

#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include <string>
#include <vector>
#include <Ice/Ice.h>
#include "Chatter.h"

class RoomManager_impl : virtual public chatter::RoomManager {
 public:

    RoomManager_impl(Ice::ObjectAdapterPtr adptr);

    virtual chatter::RoomList
    listRooms(const Ice::Current &);

    virtual void
    createRoom(const std::string &name, const Ice::Current &);

    virtual chatter::ChatRoomPrx
    lookupRoom(const std::string &name, const Ice::Current &);

  private:
    chatter::RoomList                  room_names;
    std::vector<chatter::ChatRoomPrx>  room_proxies;
    Ice::ObjectAdapterPtr              adapter;
};

#endif
