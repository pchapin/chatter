/****************************************************************************
FILE          : nameserver.cpp
LAST REVISION : 2006-07-13
SUBJECT       : Implementation of the Chatter nameserver.

Note that since the name services are actually provided by a Chatter
object, there is no reason why arbitrary client programs couldn't create
their own name servers. However, to be useful, the name server must be
"well known" and that suggests a stand alone program running 24/7.

Please send comments or bug reports to

     Peter C. Chapin
     Electrical and Computer Engineering Technology
     Vermont Technical College
     Randolph Center, VT 05061
     pchapin@ecet.vtc.edu
****************************************************************************/

#include <Ice/Ice.h>
#include "Chatter.h"
#include <NameService.h>

using namespace std;
using namespace chatter;

int main(int argc, char* argv[])
{
  int status = 0;
  Ice::CommunicatorPtr ic;
  try {
    ic = Ice::initialize(argc, argv);
    Ice::ObjectAdapterPtr adapter = ic->createObjectAdapterWithEndpoints(
      "ChatterAdapter", "tcp -p 9010");
    Ice::ObjectPtr object = new NameService_impl;
    adapter->add(object, ic->stringToIdentity("NameService"));
    adapter->activate();
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
