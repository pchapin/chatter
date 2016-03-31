package edu.vtc.chatter;

import chatter.*;

/**
 * An implementation of the Chatter RoomManager interface. This class deals with a collection of
 * chat rooms.
 */
public class RoomManagerI extends _RoomManagerDisp {

    @Override
    public String[] listRooms(Ice.Current current)
    {
        return null;
    }


    @Override
    public void createRoom(String name, Ice.Current current)
    {

    }


    @Override
    public ChatRoomPrx lookupRoom(String name, Ice.Current current)
    {
        return null;
    }
}
