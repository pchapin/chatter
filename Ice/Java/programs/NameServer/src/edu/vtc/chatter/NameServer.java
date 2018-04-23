package edu.vtc.chatter;

import com.zeroc.Ice.*;
import java.lang.Exception;

/**
 * The main class of the Chatter name server program.
 */
public class NameServer {

    /**
     * The main method initializes Ice and creates an instance of an object that does the work
     * of the name service.
     *
     * @param args Command line arguments.
     */
    public static void main(String[] args)
    {
        int status = 0;
        Communicator ic = null;
        try {
            ic = Util.initialize(args);
            ObjectAdapter adapter =
                    ic.createObjectAdapterWithEndpoints("NameServerAdapter", "default -p 9100");
            NameServiceI object = new NameServiceI();
            adapter.add(object, Util.stringToIdentity("NameService"));
            adapter.activate();
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
