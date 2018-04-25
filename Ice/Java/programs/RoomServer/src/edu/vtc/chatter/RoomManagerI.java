package edu.vtc.chatter;

import com.zeroc.Ice.*;
import chatter.*;

/**
 * An implementation of the Chatter RoomManager interface. This class deals with a collection of
 * chat rooms.
 */
public class RoomManagerI implements RoomManager {

    // We need a map (Map<String, ChatRoomPrx>) that maps the name of a chat room to its proxy.

    @Override
    public String[] listRooms(Current current)
    {
        return null;
    }


    @Override
    public void createRoom(String name, Current current)
    {
        // Create a new ChatRoom object and "connect" it to the object adaptor.
    }


    @Override
    public ChatRoomPrx lookupRoom(String name, Current current)
    {
        return null;
    }
}
