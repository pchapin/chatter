package edu.vtc.chatter;

import com.zeroc.Ice.*;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.lang.Exception;

import chatter.*;

/**
 * Class to handle the input of messages.
 */
public class MessageInput extends Thread {

    private Communicator ic;
    private String nickName;
    private NameServicePrx ns;            // Points at the currently selected name service.
    private RoomManagerPrx rm;            // Points at the currently selected room manager.
    private TextSinkPrx currentReceiver;  // Points at the receiver of our messages.
    private TextSinkPrx displayProxy;     // Points at the object receiving messages for me.

    public MessageInput(
            Communicator ic, String nickName, NameServicePrx ns, TextSinkPrx displayProxy)
    {
        this.ic       = ic;
        this.nickName = nickName;
        this.ns       = ns;
        this.displayProxy = displayProxy;
    }

    public void run()
    {
        boolean done = false;
        BufferedReader consoleInput = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("Commands...");
        System.out.println("   /help         : Get command help");
        System.out.println("   /create room  : Create the specified chat room.");
        System.out.println("   /join room    : Join the specified chat room.");
        System.out.println("   /list         : List all available chat rooms.");
        System.out.println("   /msg nickname : Select 'nickname' as target for messages");
        System.out.println("   /nick new_name: Set your nick name to 'new_name'");
        System.out.println("   /select rooms : Select the chat room server");
        System.out.println("   /quit         : Quit this program");
        System.out.println("Welcome to Chatter Interactive! Type /help for command help.\n");

        // Accept lines and send them.
        String line;
        while (!done) {
            try {
                System.out.print(" chatter: ");
                line = consoleInput.readLine();
                if (line == null) break;

                if (line.length() == 0 || line.charAt(0) != '/') {
                    // We are processing text intended for the receiver.
                    if (currentReceiver != null)
                        currentReceiver.putLine(nickName, line);
                }
                else {
                    // We are processing a command.
                    String[] command = line.split("\\s+");
                    switch (command[0]) {
                        case "/help":
                            System.out.println("Visualize useful help...");
                            break;

                        case "/create":
                            rm.createRoom(command[1]);
                            break;

                        case "/join":
                            ChatRoomPrx room = rm.lookupRoom(command[1]);
                            room.add(displayProxy);
                            currentReceiver = room;
                            break;

                        case "/list":
                            String[] rooms = rm.listRooms();
                            for (String roomName : rooms) {
                                System.out.println(roomName);
                            }
                            break;

                        case "/msg":
                            currentReceiver = ns.lookupName(command[1]);
                            break;

                        case "/nick":
                            ns.unregisterName(nickName);
                            nickName = ns.registerName(command[1], displayProxy);
                            break;

                        case "/select":
                            // TODO: Obtain host and port information from the command arguments.
                            ObjectPrx rawRoomManager =
                                    ic.stringToProxy("RoomManager:tcp -h localhost -p 9101");
                            rm = RoomManagerPrx.checkedCast(rawRoomManager);
                            break;

                        case "/quit":
                            System.out.println("MessageInput loop ending.");
                            done = true;
                            break;

                        default:
                            System.out.println("Unknown command: " + command[0]);
                            break;
                    }
                }
            }
            catch (Exception ex) {
                String message =
                        "Unhandled exception in MessageInput: " + ex.getClass() + ", message = " + ex.getMessage();
                System.out.println(message);
            }
        }
    }

}
