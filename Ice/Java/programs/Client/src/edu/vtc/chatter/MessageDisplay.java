package edu.vtc.chatter;

import chatter.*;

/**
 * Class to handle messages being sent to this client. The current implementation just displays
 * incoming messages on the console. A future implementation could perhaps use a separate window.
 */
public class MessageDisplay extends _TextSinkDisp {

    /**
     * Displays a line of text from the client onto the standard output device.
     *
     * @param from The nickname of the client user.
     * @param line The line of text to display.
     * @param current Information about the current invocation.
     */
    @Override
    public void putLine(String from, String line, Ice.Current current)
    {
        // This is a little hackish. I reprint the prompt as a convenience.
        System.out.printf("\n%8s: %s\n chatter: ", from, line);
    }

    @Override
    public void endOfText(Ice.Current current)
    {
        // Nothing needs to be done here.
    }

    @Override
    public boolean isEnabled(Ice.Current current)
    {
        return true;
    }
}
