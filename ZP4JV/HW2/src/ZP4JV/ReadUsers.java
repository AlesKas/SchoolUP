package ZP4JV;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.InputStream;
import java.util.ArrayList;

public class ReadUsers {
    ArrayList<User> usersPasswords = new ArrayList<User>();
    //tried Map<String,String> usersPasswords = new HashMap<String, String>(), but I decided to use custom class
    public ArrayList readUsers(InputStream input) throws Exception
    {
        SAXParserFactory parserFactory = SAXParserFactory.newInstance();
        SAXParser parser = parserFactory.newSAXParser();

        parser.parse(input, new DefaultHandler(){
            String element = "";
            public void startElement(String uri, String localName,
                                     String qName, Attributes attributes) throws SAXException {
                element = qName;
                if(element.equals("user"))
                {
                    String user = attributes.getValue("username");
                    String pass = attributes.getValue("password");
                    //System.out.println("user" + "\t" + user + "\t" + pass);
                    usersPasswords.add(new User(user, pass));

                }
            }

        });
        return usersPasswords;
    }
}
