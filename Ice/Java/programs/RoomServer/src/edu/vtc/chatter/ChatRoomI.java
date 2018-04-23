package edu.vtc.chatter;

import com.zeroc.Ice.*;
import chatter.*;

public class ChatRoomI implements ChatRoom {

    @Override
    public void add(TextSinkPrx dest, Current current)
    {

    }


    @Override
    public void addByName(String name, NameServicePrx ns, Current current)
    {

    }


    @Override
    public void putLine(String from, String line, Current current)
    {

    }


    @Override
    public void endOfText(Current current)
    {

    }


    @Override
    public boolean isEnabled(Current current)
    {
        return true;
    }
}
