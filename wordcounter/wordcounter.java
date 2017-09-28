import java.util.Comparator;

import components.map.Map;
import components.map.Map.Pair;
import components.map.Map1L;
import components.queue.Queue;
import components.queue.Queue1L;
import components.simplereader.SimpleReader;
import components.simplereader.SimpleReader1L;
import components.simplewriter.SimpleWriter;
import components.simplewriter.SimpleWriter1L;

/**
 * Creates an html file with a table of counts of words in the user provided
 * input text file.
 *
 * @author Matthew Rutan
 *
 */
public final class WordCounter {
    /**
     * Creates a Comparator.
     *
     * @author Matthew Rutan
     *
     */
    private static class StringLT implements Comparator<String> {
        @Override
        public int compare(String o1, String o2) {
            int result = 0;

            if (o1.compareToIgnoreCase(o2) < 0) {
                result = -1;
            } else if (o1.compareToIgnoreCase(o2) > 0) {
                result = 1;
            }

            return result;
        }
    }

    /**
     * Private constructor so this utility class cannot be instantiated.
     */
    private WordCounter() {
    }

    /**
     * String of separators.
     */
    private static final String SEPARATORS = "<>\"\',.?/:;{[}]-_+=)(*&^%$#@!~`\\| ";

    /**
     * Sends the map's terms to a queue to be alphabetized.
     *
     * @param words
     *            map of words that will be alphabetized in a queue
     * @return returns a queue of alphabetized map terms
     * @requires words!=null
     * @ensures
     *
     *          <pre>
     * queue=alphabetized words
     *          </pre>
     */
    private static Queue<String> alphabetize(Map<String, Integer> words) {
        Comparator<String> order = new StringLT(); //comparator for sort
        Queue<String> wordsAZ = new Queue1L<>(); //queue for alphabetized words

        for (Pair<String, Integer> map : words) {
            wordsAZ.enqueue(map.key());
        }

        wordsAZ.sort(order);

        return wordsAZ;
    }

    /**
     * Creates an html file of users words and corresponding counts.
     *
     * @param outputFile
     *            the file to save the html file in
     * @param inputFile
     *            the user provided txt file name and folder
     * @param wordsAZ
     *            alphabetized words from map
     * @param wordsAndValues
     *            map of words and their values from the user txt file
     * @requires outputFolder!=null && !outputFolder.isEmpty() &&
     *           inputFile!=null && wordsAZ!=null && wordsAndValues!=null
     * @ensures
     *
     *          <pre>
     * html file=words and corresponding values
     *          </pre>
     */
    private static void writeWordsPage(String outputFile, String inputFile,
            Queue<String> wordsAZ, Map<String, Integer> wordsAndValues) {

        SimpleWriter output = new SimpleWriter1L(
                "data/" + outputFile + ".html"); //output file stream

        output.println("<!DOCTYPE html>");
        output.println("<html>");
        output.println("<head>");
        output.println("<h1>Words Counted in " + inputFile + "</h1>");
        output.println("</head>");
        output.println("<body>");
        output.println("<hr>");
        output.println("<table border=\"1\">");
        output.println("<tbody><tr>");
        output.println("<th>Word</th>");
        output.println("<th>Counts</th>");
        output.println("</tr>"); //creates header for html

        for (String word : wordsAZ) {
            output.println("<tr>");
            output.println("<td>" + word + "</td>");
            output.println("<td>" + Integer.toString(wordsAndValues.value(word))
                    + "</td>");
            output.println("</tr>");
        } //creates table of words and counts

        output.println("</table>");
        output.println("</body>");
        output.println("<hr>");
        output.print("</html>"); //footer

        output.close();
    }

    /**
     * Checks if the current index character is a separator or out of bounds.
     *
     * @param input
     *            the string from the input text file
     * @param index
     *            current character index of string being examined
     * @return returns 0 if the index is out of bounds of the string length,
     *         returns 1 if the current character is a separator, returns -1 if
     *         the current character is not a separator
     *
     * @requires input != null
     * @ensures
     *
     *          <pre>
     *         whether the index of input is a separator
     *          </pre>
     */
    private static int isSeparator(String input, int index) {
        int isSep = 0; //variable for return value

        if (index < input.length()) {
            if (SEPARATORS.lastIndexOf(input.charAt(index)) >= 0) {
                isSep = 1;
            } else {
                isSep = -1;
            }
        }

        return isSep;
    }

    /**
     * Scans through the string and separates the words from separators, adds
     * the words to the map or updates their count if they already exist in the
     * map.
     *
     * @param words
     *            the map to be filled with words and corresponding counted
     *            values
     * @param input
     *            the input string from txt file
     * @requires !input.isEmpty() && input!=null && words!=null
     *
     * @ensures
     *
     *          <pre>
     *          words = input - separators
     *          </pre>
     */
    private static void addCountWords(Map<String, Integer> words,
            String input) {

        String word = "";
        int i = 0, wordStart = 0;

        while (i < input.length()) {
            /*
             * Checks the i-th character for a separator and stops when a
             * non-separator character has been found or end of line has been
             * reached.
             */
            while (isSeparator(input, i) > 0) {
                i++;
            }
            /*
             * Checks the i-th character for a non-separator character and stops
             * when separator character has been found or end of line has been
             * reached.
             */
            if (i < input.length()) {
                wordStart = i;
                while (isSeparator(input, i) < 0) {
                    i++;
                }

                word = input.substring(wordStart, i);

                if (!word.isEmpty()) {
                    if (!words.hasKey(word)) {
                        words.add(word, 1);
                    } else {
                        int incrementValue = words.value(word) + 1;
                        words.replaceValue(word, incrementValue);
                    }
                }
            }
        }
    }

    /**
     * Main method.
     *
     * @param args
     *            the command line arguments
     */
    public static void main(String[] args) {
        SimpleReader input = new SimpleReader1L();
        SimpleWriter output = new SimpleWriter1L(); //output and input streams

        output.print("Enter input file directory name: ");
        String inputFile = input.nextLine();

        output.print("Enter output file name: ");
        String outputFile = input.nextLine();

        Map<String, Integer> words = new Map1L<>();
        //creates new map for words and associated counts

        input.close();
        input = new SimpleReader1L(inputFile);

        String inputLine = ""; //each line in text file

        while (!input.atEOS()) {
            inputLine = input.nextLine();
            if (!inputLine.isEmpty()) {
                addCountWords(words, inputLine);
            } //no need to count words if string is empty
        }

        if (words.size() > 0) {
            Queue<String> wordsAZ = alphabetize(words);
            writeWordsPage(outputFile, inputFile, wordsAZ, words);
        } else {
            output.println("No words to count. No file Created.");
        }

        input.close();
        output.close();
    }
}
