/****************************************************************************
FILE          : RoomManger.cpp
LAST REVISION : 2007-04-25
SUBJECT       : Implementation of a RoomManager
PROGRAMMER    : (C) Copyright 2007 by Peter C. Chapin

Please send comments or bug reports to

     Peter C. Chapin
     Electrical and Computer Engineering Technology
     Vermont Technical College
     Randolph Center, VT 05061
     pchapin@ecet.vtc.edu
****************************************************************************/

#include <algorithm>
#include "ChatRoom.h"
#include "RoomManager.h"

RoomManager_impl::RoomManager_impl(Ice::ObjectAdapterPtr adptr)
{
  adapter = adptr;
}

chatter::RoomList
RoomManager_impl::listRooms(const Ice::Current &)
{
  return room_names;
}

void
RoomManager_impl::createRoom(const std::string &name, const Ice::Current &)
{
  Ice::ObjectPtr object = new ChatRoom_impl;
  Ice::ObjectPrx object_proxy = adapter->addWithUUID(object);
  chatter::ChatRoomPrx room_proxy =
    chatter::ChatRoomPrx::checkedCast(object_proxy);

  room_names.push_back(name);
  room_proxies.push_back(room_proxy);
}

chatter::ChatRoomPrx
RoomManager_impl::lookupRoom(const std::string &name, const Ice::Current &)
{
  chatter::RoomList::iterator p;
  p = std::find(room_names.begin(), room_names.end(), name);
  if (p != room_names.end()) {
    return room_proxies[p - room_names.begin()];
  }
  return 0;
}
