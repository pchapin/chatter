package edu.vtc.chatter;

import com.zeroc.Ice.*;
import chatter.*;

public class ChatRoomI implements ChatRoom {

    // We need a container that holds TextSinkPrx objects.

    @Override
    public void add(TextSinkPrx dest, Current current)
    {
        // Add 'dest' to the container of TextSinkPrx objects.
    }


    @Override
    public void addByName(String name, NameServicePrx ns, Current current)
    {
        // Use the NameService to look up 'name' and then add the resulting proxy.
    }


    @Override
    public void putLine(String from, String line, Current current)
    {
        // Loop over all TextSinkPrx objects and forward the 'from' and 'line' to them.
    }


    @Override
    public void endOfText(Current current)
    {
        // Forward a call to endOfText to all objects in this chat room.
    }


    @Override
    public boolean isEnabled(Current current)
    {
        return true;
    }
}
