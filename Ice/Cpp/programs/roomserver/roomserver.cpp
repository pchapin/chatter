/****************************************************************************
FILE          : server.cpp
LAST REVISION : 2007-04-26
SUBJECT       : Implementation of a room server.
PROGRAMMER    : (C) Copyright 2007 by Peter C. Chapin

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
#include <RoomManager.h>
using namespace chatter;

int main(int argc, char* argv[])
{
  int status = 0;
  Ice::CommunicatorPtr ic;
  try {
    ic = Ice::initialize(argc, argv);

    if (argc != 4) {
      cerr << "Usage: " << argv[0] << " servername NameService-host local-port\n";
      goto clean_up;
    }

    // Look up the name service.
    ostringstream ns_formatter;
    ns_formatter << "NameService:tcp -h " << argv[2] << " -p 9010";
    Ice::ObjectPrx base =
      ic->stringToProxy(ns_formatter.str().c_str());
    NameServicePrx ns = NameServicePrx::checkedCast(base);
    if (!ns)
      throw "Invalid NameService";

    // Create local chat display object and support infrastructure.
    ostringstream server_formatter;
    server_formatter << "tcp -p " << argv[3];
    Ice::ObjectAdapterPtr adapter = ic->createObjectAdapterWithEndpoints(
      "ChatterAdapter", server_formatter.str().c_str());
    Ice::ObjectPtr object = new RoomManager_impl(adapter);
    Ice::ObjectPrx server =
      adapter->add(object, ic->stringToIdentity("RoomManager"));
    adapter->activate();

    // Register object.
    // ns->registerName(argv[1], server);

    ic->waitForShutdown();
  }
  catch (const Ice::Exception& e) {
    cerr << e << endl;
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
