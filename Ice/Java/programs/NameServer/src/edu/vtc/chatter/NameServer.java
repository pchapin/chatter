package edu.vtc.chatter;

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
        Ice.Communicator ic = null;
        try {
            ic = Ice.Util.initialize(args);
            Ice.ObjectAdapter adapter =
                    ic.createObjectAdapterWithEndpoints("NameServerAdapter", "default -p 9100");
            Ice.Object object = new NameServiceI();
            adapter.add(object, ic.stringToIdentity("NameService"));
            adapter.activate();
            ic.waitForShutdown();
        }
        catch (Ice.LocalException e) {
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
