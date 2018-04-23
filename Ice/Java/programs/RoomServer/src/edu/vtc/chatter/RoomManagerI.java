package edu.vtc.chatter;

import com.zeroc.Ice.*;
import chatter.*;

/**
 * An implementation of the Chatter RoomManager interface. This class deals with a collection of
 * chat rooms.
 */
public class RoomManagerI implements RoomManager {

    @Override
    public String[] listRooms(Current current)
    {
        return null;
    }


    @Override
    public void createRoom(String name, Current current)
    {

    }


    @Override
    public ChatRoomPrx lookupRoom(String name, Current current)
    {
        return null;
    }
}
