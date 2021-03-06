package edu.vtc.chatter;

import com.zeroc.Ice.*;
import java.lang.Exception;
import chatter.*;

/**
 * The main class of the Chatter client program. This class initializes Ice and sets up the
 * client for operation.
 */
public class Client {

    /**
     * The program entry point. Initialize Ice and create the objects that will interact with
     * the user and with other Chatter entities.
     *
     * @param args Command line arguments.
     */
    public static void main(String[] args) {
        int    status = 0;
        String nickname = "GoldenEye";
        String port = "9111";

        Communicator ic = null;
        try {
            ic = Util.initialize(args);

            if (args.length != 2) {
                System.out.println("Usage: Client nickname listening-port");
                System.exit(1);  // This seems a bit abrupt.
            }
            else {
                // TODO: Add some input validation.
                nickname = args[0];
                port     = args[1];
            }

            ObjectAdapter adapter =
                    ic.createObjectAdapterWithEndpoints("ClientAdapter", "default -p " + port);

            // Create and add a servant to deal with incoming messages.
            MessageDisplay displayObject = new MessageDisplay();
            ObjectPrx displayObjectProxy =
                    adapter.add(displayObject, Util.stringToIdentity("MessageDisplay"));
            TextSinkPrx displayProxy = TextSinkPrx.checkedCast(displayObjectProxy);
            adapter.activate();

            // Get a proxy to the "well known" name service.
            // TODO: The location of the name service should be configurable.
            ObjectPrx rawNameService =
                    ic.stringToProxy("NameService:tcp -h localhost -p 9100");
            NameServicePrx ns = NameServicePrx.checkedCast(rawNameService);

            // TODO: Use a better exception. This is an abuse of IllegalArgumentException.
            if (ns == null) throw new IllegalArgumentException("Invalid Name Service");

            String cleanedNickname = ns.registerName(nickname, displayProxy);

            // Create an object to process input by the user and run it in a separate thread.
            MessageInput inputObject = new MessageInput(ic, cleanedNickname, ns, displayProxy);
            inputObject.start();
            inputObject.join();

            ic.waitForShutdown();
        }
        catch (LocalException e) {
            e.printStackTrace();
            status = 1;
        }
        catch (Exception e) {
            System.err.println(e.getMessage());
            status = 1;
        }
        if (ic != null) {
            // Clean up
            try {
                ic.destroy();
            }
            catch (Exception e) {
                System.err.println(e.getMessage());
                status = 1;
            }
        }
        System.exit(status);
    }
}
