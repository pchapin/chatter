/****************************************************************************
FILE      : Chatter.ice
SUBJECT   : Interface to Chatter objects
PROGRAMMER: (C) Copyright 2018 by Peter C. Chapin

Please send comments or bug reports to

     Peter C. Chapin
     Computer Information Systems
     Vermont Technical College
     Williston, VT 05495
     pchapin@vtc.edu
****************************************************************************/

module chatter {

    // TextSink objects accept lines of text and process them in some way.
    interface TextSink {

        // Send a line of text. The line should not be '\n' terminated. The 'from' string
        // specifies the nickname of the entity that sent the line. The name should not be
        // trusted as there is currently no provision for security; any string could be used.
        //
        void putLine(string from, string line);

        // Inform this object that no more text will be coming. Some TextSink objects won't care
        // about this, but others might so it is polite to call endOfText() when appropriate.
        //
        void endOfText();

        // Return true if object accepting text normally. If isEnabled() returns false, lines
        // sent to the object are likely to be ignored and lost.
        //
        bool isEnabled();
    };


    // TextSource objects produce lines of text. They can be pointed at specific destination
    // objects either by name or by reference.
    //
    interface TextSource {

        // Point this source at the specified sink.
        void setDestinationRef(TextSink *dest);

        // Point this source at the named sink.
        void setDestinationName(string name);
    };


    // Used by the name service to indicate invalid nicknames.
    exception BadNameException { };

    // NameService objects hold registered (nickname, Object) pairs. The name service is very
    // general and allows one to associate a name to any Ice object.
    //
    // TODO: This interface should eventually allow a way for users to enumerate names. In
    // addition some sort of security should eventually be added so that only name owners can
    // unregister their names. This implies also the addition of methods to allow dead names to
    // be forcibly unregistered, etc, by a user with an appropriate role.
    //
    // TODO: The name server should enforce some sort of notion of name lifetimes. If a user
    // registers a name, that name should eventually expire and be automatically unregistered.
    //
    interface NameService {

        // Register the given TextSink instance under the given name. Return a possibly cleaned
        // up version of the name. The caller should store the return value and use it when
        // unregistering. If the name can not be cleaned up, this method throws an exception.
        //
        string registerName(string name, TextSink *instance) throws BadNameException;

        // Remove the registration for a particular name. If the name does not exist there is no
        // effect.
        //
        void unregisterName(string name);

        // Look up the TextSink represented by a particular name. If the name does not exist,
        // this method returns a null proxy. The caller should check for that.
        //
        TextSink *lookupName(string name);
    };


    // =====
    // Interfaces derived from above.
    // =====

    // TextFilter objects can play the role of both a sink and a source.
    interface TextFilter extends TextSink, TextSource { };


    // ChatRoom objects can be pointed at many destinations. Each line they accept is forwarded
    // to all of their destinations.
    //
    // TODO: Add a facility for removing destinations.
    //
    interface ChatRoom extends TextSink {

        // Add another destination to this room. All text sent to the room is copied to all
        // destinations.
        //
        void add(TextSink *dest);

        // Add another destination to this room using the name of that destination instead of
        // the proxy. This method also requires the name service used to resolve the name be
        // provided.
        //
        void addByName(string name, NameService *ns);
    };

    // =====
    // High level interfaces.
    // =====

    sequence<string> RoomList;

    // A room manager is a container for a collection of chat rooms. The room manager should be
    // named in some name server, but the individual rooms only need names relative to the room
    // manager that controls them.
    //
    interface RoomManager {

        // Return a sequence containing the names of all the rooms known to this RoomManager.
        RoomList  listRooms();

        // Create a room with the given name. There is no indication of failure.
        void createRoom(string name);

        // Return a proxy to a room with a given name. If there is no such room a null proxy is
        // returned. The caller should check for that.
        //
        ChatRoom *lookupRoom(string name);
    };

};
