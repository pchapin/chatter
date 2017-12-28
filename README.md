
The Chatter Instant Messaging System
====================================

Overview
--------

This project contains an instant messaging system used as a vehicle for teaching distributed
applications and middleware technologies. Currently there are two implementations of Chatter:
one that uses CORBA and one that uses Ice (http://www.zeroc.com/). These implementations are
independent. They do not share any code.

Current Status
--------------

Both of the current implementations are rather minimal right now, however the Ice implementation
is significantly more advanced than the CORBA implementation.


Future Directions
-----------------

+ Refine the Chatter implementations by enhancing the existing interfaces or by adding new
  interfaces.

+ Improve the documentation.

+ Attempt to merge the CORBA and Ice code bases to create a single set of sources that can be
  compiled for either CORBA or Ice operation. (It is unclear if this would actually be a good
  idea or not).

+ Create a CORBA/Ice gateway so that the two Chatter implementations could interoperate.

+ Create implemenations in other languages (Java? C#?)

+ Create implementations for other middleware technologies (.NET? Web Services?)

Peter Chapin  
chapinp@acm.org
