package edu.vtc.chatter;

import chatter.*;

public class ChatRoomI extends _ChatRoomDisp {

    @Override
    public void add(TextSinkPrx dest, Ice.Current current)
    {

    }


    @Override
    public void addByName(String name, NameServicePrx ns, Ice.Current current)
    {

    }


    @Override
    public void putLine(String from, String line, Ice.Current current)
    {

    }


    @Override
    public void endOfText(Ice.Current current)
    {

    }


    @Override
    public boolean isEnabled(Ice.Current current)
    {
        return true;
    }
}
