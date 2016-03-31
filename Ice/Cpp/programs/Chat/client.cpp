/****************************************************************************
FILE          : client.cpp
LAST REVISION : 2007-04-26
SUBJECT       : Implementation of an interactive chat client.
PROGRAMMER    : (C) Copyright 2007 by Peter C. Chapin

This program allows the user to send text to TextSink Chatter objects of
all kinds. The user must only know the name of the object in order to talk
to that object. This program is written for operation on a plain terminal.
More powerful graphical utilities could be imagined.

Please send comments or bug reports to

     Peter C. Chapin
     Electrical and Computer Engineering Technology
     Vermont Technical College
     Randolph Center, VT 05061
     pchapin@ecet.vtc.edu
****************************************************************************/

#include <sstream>
#include <string>
using namespace std;

#include <Ice/Ice.h>

#include "Chatter.h"
#include <NameService.h>
#include <RoomManager.h>
#include <TextSink.h>
using namespace chatter;

// The following function returns the (single) argument on the given command. A more general
// version of this function that splits the command line into an array of arguments should
// probably be written.
//
static std::string get_argument(const std::string &command)
{
  string::size_type delimiter = command.find_last_of(" ");
  return command.substr(delimiter + 1);
}


// The following function is the program's main loop. It prompts the user for a command and
// handles that command. Non-command input is taken to be text that should be sent to the
// currently selected destination.
//
void interactive_loop(NameServicePrx ns)
{
  string line;
  string my_name("*none*");
  TextSinkPrx destination;
  RoomManagerPrx room_server;

  cout << "Welcome to Chatter Interactive! Type /help for command help.\n\n";
  while (1) {
    cout << "chatter: " << flush;
    getline(cin, line);

    // Deal with commands, etc. It would be nice to introduce some general command line parsing
    // functions to make the command line handling more robust and more powerful. The solution
    // here is quick and dirty.
    //
    if (line.substr(0, 5) == "/help") {
      cout << "Commands...\n";
      cout << "  /create room  : Create 'room' on the current room server.\n";
      cout << "  /help         : Get command help.\n";
      cout << "  /join room    : Join 'room' on the current room server.\n";
      cout << "  /list         : List rooms on the current room server.\n";
      cout << "  /msg nickname : Select 'nickname' as target for messages.\n";
      cout << "  /name new_name: Set your name to 'new_name'\n";
      cout << "  /quit         : Exit Chatter Interactive.\n";
      cout << "  /rooms server : Select 'server' as the current room server.\n";
    }

    else if (line.substr(0, 4) == "/msg") {
      string nickname = get_argument(line);

      // Look up the object.
      TextSinkPrx chatter_object = ns->lookupName(nickname);
      if (!chatter_object) {
        cout << "ERROR: "
             << nickname << " does not specify a text receiver!\n";
        destination = 0;
      }
      else {
        cout << "You are now talking to " << nickname << ".\n";
        destination = chatter_object;
      }
    }

    else if (line.substr(0, 5) == "/name") {
      my_name = get_argument(line);
      cout << "You are now known as " << my_name << ".\n";
    }

    else if (line.substr(0, 6) == "/rooms") {
      string server_name = get_argument(line);

      // Look up the object and verify that it is a RoomManager of some kind.
      Ice::ObjectPrx chatter_base = ns->lookupName(server_name);
      RoomManagerPrx chatter_object = RoomManagerPrx::checkedCast(chatter_base);
      if (!chatter_object) {
        cout << "ERROR: "
             << server_name << " does not specify a room manager!\n";
        room_server = 0;
      }
      else {
        cout << "You have selected " << server_name << " as your room manager.\n";
        room_server = chatter_object;
      }
      
    }

    else if (line.substr(0, 5) == "/list") {
      RoomList room_names = room_server->listRooms();
      RoomList::iterator p;
      for (p = room_names.begin(); p != room_names.end(); ++p) {
        cout << *p << "\n";
      }
    }

    else if (line.substr(0, 7) == "/create") {
      string room_name = get_argument(line);
      room_server->createRoom(room_name);
    }

    else if (line.substr(0, 5) == "/join") {
      string room_name = get_argument(line);
      ChatRoomPrx room = room_server->lookupRoom(room_name);
      if (!room) {
        cout << "ERROR: "
             << room_name << " does not specify a room on the selected server.\n";
      }
      else {
        room->addByName(my_name, ns);
        destination = room;
      }
    }

    else if (line.substr(0, 5) == "/quit") {
      return;
    }

    else {
      destination->putLine(my_name, line);
    }
  }
}

//========================
//      Main Program 
//========================

// The main program initializes Ice and the application. It also contains top level exception
// handlers that probably should never get invoked.
//
int main(int argc, char *argv[])
{
  int status = 0;
  Ice::CommunicatorPtr ic;

  try {
    ic = Ice::initialize(argc, argv);

    if (argc != 2) {
      cerr << "Usage: " << argv[0] << " NameService-host\n";
      goto clean_up;
    }

    // Look up the name service.
    ostringstream formatter;
    formatter << "NameService:tcp -h " << argv[1] << " -p 9010";
    Ice::ObjectPrx base = ic->stringToProxy(formatter.str().c_str());
    NameServicePrx ns = NameServicePrx::checkedCast(base);
    if (!ns) throw "Invalid NameService";

    // Work with the user.
    interactive_loop(ns);
  }
  catch (const Ice::Exception& ex) {
    cerr << ex << endl;
    status = 1;
  }
  catch (const char* msg) {
    cerr << msg << endl;
    status = 1;
  }

 clean_up:
  // We must call ic->destroy() even if an exception is throw above.
  if (ic) {
    try {
      ic->destroy();
    }
    catch (const Ice::Exception& e) {
      cerr << e << endl;
      status = 1;
    }
  }

  return status;
}
