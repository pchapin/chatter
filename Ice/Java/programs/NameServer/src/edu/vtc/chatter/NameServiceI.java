package edu.vtc.chatter;

import java.util.HashMap;
import chatter.*;

/**
 * Implementation of the Chatter NameService interface. This class does the bulk of the work of
 * the name server. This implementation is simple in that it stores name to object mappings in
 * memory using a Java collections HashMap.
 */
public class NameServiceI extends _NameServiceDisp {

    HashMap<String, TextSinkPrx> objectMap = new HashMap<>();

    String[] badWordsArray = { "homework", "test", "quiz", "final" };

    /**
     * This method "cleans up" the name by ensuring that the proposed name is not being used. If
     * it is, then a new name is constructed by appending a count to the end of the proposed
     * name (myNick becomes myNick_1, etc). There is otherwise no filtering of names in this
     * implementation.
     *
     * @param name The name to clean up.
     * @return Either the proposed name or, if it was in use, the proposed name followed by a
     * count value.
     * @throws BadNameException if the name does not meet local acceptability standards.
     */
    private String cleanName(String name) throws BadNameException
    {
        int    count = 1;
        String adjustedName = name;

        // Check for acceptability.
        for (String word : badWordsArray) {
            // TODO: Should look at case insensitive substrings.
            // For example: "yourQuiz" is not acceptable.
            if (name.equals(word)) throw new BadNameException();
        }

        // Adjust name if it is in use.
        while (objectMap.get(adjustedName) != null) {
            adjustedName = name + "_" + count;
            count++;
        }
        return adjustedName;
    }


    @Override
    public String registerName(
            String name, TextSinkPrx instance, Ice.Current current) throws BadNameException
    {
        String cleanedName = cleanName(name);
        System.out.println("Adding   name: " + cleanedName);
        objectMap.put(cleanedName, instance);
        return cleanedName;
    }


    @Override
    public void unregisterName(String name, Ice.Current current)
    {
        System.out.println("Removing name: " + name);
        objectMap.remove(name);
    }


    @Override
    public TextSinkPrx lookupName(String name, Ice.Current current)
    {
        return objectMap.get(name);
    }
}
