import components.simplereader.SimpleReader;
import components.simplereader.SimpleReader1L;
import components.simplewriter.SimpleWriter;
import components.simplewriter.SimpleWriter1L;
import components.xmltree.XMLTree;
import components.xmltree.XMLTree1;

/**
 * Program to convert an XML RSS (version 2.0) feed from a given URL into the
 * corresponding HTML output file.
 *
 * @author Matthew Rutan
 *
 */
public final class RSSReader {

    /**
     * Private constructor so this utility class cannot be instantiated.
     */
    private RSSReader() {
    }

    /**
     * Outputs the "opening" tags in the generated HTML file. These are the
     * expected elements generated by this method:
     *
     * <html> <head> <title>the channel tag title as the page
     * title</title> </head> <body>
     * <h1>the page title inside a link to the <channel> link
     * <h1>
     * <p>
     * the channel description
     * </p>
     * <table>
     * <tr>
     * <th>Date</th>
     * <th>Source</th>
     * <th>News</th>
     * </tr>
     *
     * @param channel
     *            the channel element XMLTree
     * @param out
     *            the output stream
     * @updates out.content
     * @requires [the root of channel is a <channel> tag] and out.is_open
     * @ensures out.content = #out.content * [the HTML "opening" tags]
     */
    private static void outputHeader(XMLTree channel, SimpleWriter out) {
        assert channel != null : "Violation of: channel is not null";
        assert out != null : "Violation of: out is not null";
        assert channel.isTag() && channel.label().equals("channel") : ""
                + "Violation of: the label root of channel is a <channel> tag";
        assert out.isOpen() : "Violation of: out.is_open";
        int title = 0, link = 0, description = 0;
        //local variables for children of channel tag

        out.println("<style>");
        out.println("table, th, td");
        out.println("{");
        out.println("border: 1px solid black;");
        out.println("}");
        out.println("</style>");
        out.println("<html> <head>");

        title = getChildElement(channel, "title");
        link = getChildElement(channel, "link");

        //prints linked title
        if (channel.child(title).numberOfChildren() > 0) {

            out.print("<h1><a href=\"" + channel.child(link).child(0) + "\">");
            out.println(channel.child(title).child(0) + "</a></h1>");
        } else {
            out.print("<h1><a href=\"" + channel.child(link).child(0) + "\">");
            out.println("No title</a></h1>");
        }

        out.println("</head>");

        description = getChildElement(channel, "description");

        //prints description below title, if available
        if (channel.child(description).numberOfChildren() > 0) {
            out.println("<p>" + channel.child(description).child(0) + "</p>");
        }

        out.println("<table>");
        out.println("<tr>");
        out.println("<th>Date</th>");
        out.println("<th>Source</th>");
        out.println("<th>News</th>");
        out.println("</tr>");
    }

    /**
     * Outputs the "closing" tags in the generated HTML file. These are the
     * expected elements generated by this method:
     *
     * </table>
     * </body> </html>
     *
     * @param out
     *            the output stream
     * @updates out.contents
     * @requires out.is_open
     * @ensures out.content = #out.content * [the HTML "closing" tags]
     */
    private static void outputFooter(SimpleWriter out) {
        assert out != null : "Violation of: out is not null";
        assert out.isOpen() : "Violation of: out.is_open";

        out.println("</table>");
        out.println("</body> </html>");
    }

    /**
     * Finds the first occurrence of the given tag among the children of the
     * given {@code XMLTree} and return its index; returns -1 if not found.
     *
     * @param xml
     *            the {@code XMLTree} to search
     * @param tag
     *            the tag to look for
     * @return the index of the first child of type tag of the {@code XMLTree}
     *         or -1 if not found
     * @requires [the label of the root of xml is a tag]
     * @ensures
     *
     *          <pre>
     * getChildElement =
     *  [the index of the first child of type tag of the {@code XMLTree} or
     *   -1 if not found]
     *          </pre>
     */
    private static int getChildElement(XMLTree xml, String tag) {
        assert xml != null : "Violation of: xml is not null";
        assert tag != null : "Violation of: tag is not null";
        assert xml.isTag() : "Violation of: the label root of xml is a tag";
        int childLabel = -1, j = 0;
        boolean isTheTag = false; //local variables

        while (!isTheTag && j < xml.numberOfChildren()) {
            if (xml.child(j).label().equals(tag)) {
                isTheTag = true;
                childLabel = j;
            }

            j++;
        }

        return childLabel;
    }

    /**
     * Processes one news item and outputs one table row. The row contains three
     * elements: the publication date, the source, and the title (or
     * description) of the item.
     *
     * @param item
     *            the news item
     * @param out
     *            the output stream
     * @updates out.content
     * @requires
     *
     *           <pre>
     * [the label of the root of item is an <item> tag] and out.is_open
     *           </pre>
     *
     * @ensures
     *
     *          <pre>
     * out.content = #out.content *
     *   [an HTML table row with publication date, source, and title of news item]
     *          </pre>
     */
    private static void processItem(XMLTree item, SimpleWriter out) {
        assert item != null : "Violation of: item is not null";
        assert out != null : "Violation of: out is not null";
        assert item.isTag() && item.label().equals("item") : ""
                + "Violation of: the label root of item is an <item> tag";
        assert out.isOpen() : "Violation of: out.is_open";
        int source = 0, description = 0, date = 0, title = 0, link = 0;
        //local variables for various children of item tag

        out.println("<tr>");
        date = getChildElement(item, "pubDate");

        //checks and outputs relevant date information for date column
        if (date != -1 && item.child(date).numberOfChildren() > 0) {
            out.println("<td>" + item.child(date).child(0) + "</td>");
        } else {
            out.println("<td>No Date Available</td>");
        }

        source = getChildElement(item, "source");

        //checks and outputs relevant source information for source column
        if (source != -1) {
            if (item.child(source).hasAttribute("url")
                    && !item.child(source).attributeValue("url").isEmpty()) {
                out.print("<td><a href=\""
                        + item.child(source).attributeValue("url") + "\">");
                if (item.child(source).numberOfChildren() > 0) {
                    out.println(item.child(source).child(0) + "</a></td>");
                } else {
                    out.println("No Source Name</a></td>");
                }
            } else if (item.child(source).numberOfChildren() > 0) {
                out.println("<td>" + item.child(source).child(0) + "</td>");
            } else {
                out.println("<td>No Source Available</td>");
            }
        } else {
            out.println("<td>No Source Available</td>");
        }

        link = getChildElement(item, "link");
        description = getChildElement(item, "description");
        title = getChildElement(item, "title");

        //checks and outputs relevant title and link information for news column
        if (link != -1 && item.child(link).numberOfChildren() > 0) {
            out.print("<td><a href=\"" + item.child(link).child(0) + "\">");
            if (title != -1 && item.child(title).numberOfChildren() > 0) {
                out.println(item.child(title).child(0) + "</a></td>");
            } else if (description != -1
                    && item.child(description).numberOfChildren() > 0) {
                out.println(item.child(description).child(0) + "</a></td>");
            } else {
                out.println("No Title</a></td>");
            }
        } else if (title != -1 && item.child(title).numberOfChildren() > 0) {
            out.println("<td>" + item.child(title).child(0) + "</td>");
        } else if (description != -1
                && item.child(description).numberOfChildren() > 0) {
            out.println("<td>" + item.child(description).child(0) + "</td>");
        } else {
            out.println("<td>No Title or Link</td>");
        }

        out.println("</tr>");
    }

    /**
     * Checks for a valid rss version, 2.0 and checks for the "rss" root tag.
     *
     * @param xml
     *            rss xml tree
     *
     * @return returns true if valid rss, false if not.
     */
    private static boolean validateRss(XMLTree xml) {
        boolean valid = false;
        if (xml.label().equals("rss")
                && xml.attributeValue("version").equals("2.0")) {
            valid = true;
        }

        return valid;
    }

    /**
     * Main method.
     *
     * @param args
     *            the command line arguments; unused here
     */
    public static void main(String[] args) {
        SimpleReader in = new SimpleReader1L();
        SimpleWriter out = new SimpleWriter1L();
        SimpleWriter outFile = new SimpleWriter1L("data/rss.html");
        String userURL; //string for user url input

        out.print("Enter an RSS URL: ");
        userURL = in.nextLine();

        XMLTree xml = new XMLTree1(userURL); //creates XMLTree
        while (!validateRss(xml)) {
            out.print("Please Enter a valid RSS URL: ");
            userURL = in.nextLine();
            xml = new XMLTree1(userURL);
        } //checks for valid RSS version and root tag label

        XMLTree channel = xml.child(0);
        outputHeader(channel, outFile);

        for (int i = 0; i < channel.numberOfChildren(); i++) {
            if (channel.child(i).label().equals("item")) {
                processItem(channel.child(i), outFile);
            }
        }

        outputFooter(outFile);

        in.close();
        out.close();
        outFile.close();
    }
}