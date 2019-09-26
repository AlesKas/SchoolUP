package ZP4JV;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.bootstrap.DOMImplementationRegistry;
import org.w3c.dom.ls.DOMImplementationLS;
import org.w3c.dom.ls.LSOutput;
import org.w3c.dom.ls.LSSerializer;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;


public class DOMPlaylistReaderWriter implements PlaylistReaderWriter {

    @Override
    public Playlist loadPlaylist(InputStream input) throws Exception {
        DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance();
        DocumentBuilder documentBuilder = documentBuilderFactory.newDocumentBuilder();
        Document document = documentBuilder.parse(input);

        Element root = document.getDocumentElement();
        Node attr = root.getAttributes().getNamedItem("tracks");

        ArrayList<Track> tracklists = new ArrayList<>();
        for(int i = 0; i < document.getElementsByTagName("track").getLength(); i++)
        {
            Track track = new Track(
                    document.getElementsByTagName("track").item(i).getAttributes().getNamedItem("location").getTextContent(),
                    document.getElementsByTagName("track").item(i).getAttributes().getNamedItem("duration").getTextContent(),
                    document.getElementsByTagName("track").item(i).getTextContent()
            );
            tracklists.add(track);
        }

        Playlist playlist = new Playlist(
                root.getNodeName(),
                attr.getTextContent(),
                document.getElementsByTagName("name").item(0).getTextContent(),
                document.getElementsByTagName("genre").item(0).getTextContent(),
                tracklists
        );
        return playlist;
    }

    @Override
    public void storePlaylist(OutputStream output, Playlist playlist) throws Exception {
        DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance();
        DocumentBuilder documentBuilder = documentBuilderFactory.newDocumentBuilder();
        Document document = documentBuilder.newDocument();

        //Root Element
        Element rootElement = document.createElement("playlist");
        rootElement.setAttribute("tracks", "6");
        document.appendChild(rootElement);

        //Name Element
        Element nameNode = document.createElement("name");
        nameNode.setTextContent(playlist.getName());
        rootElement.appendChild(nameNode);

        //Genre Element
        Element genreNode = document.createElement("genre");
        genreNode.setTextContent(playlist.getGenre());
        rootElement.appendChild(genreNode);

        //Tracklist
        Element tracklistNode = document.createElement("trackList");
        rootElement.appendChild(tracklistNode);

        for(Track t : playlist.getTracklist())
        {
            Element trackNode = document.createElement("track");
            trackNode.setAttribute("location", t.getLocation());
            trackNode.setAttribute("duration", t.getDuration());
            trackNode.setTextContent(t.getText());
            tracklistNode.appendChild(trackNode);
        }

        DOMImplementationRegistry registry = DOMImplementationRegistry.newInstance();
        DOMImplementationLS impl = (DOMImplementationLS) registry.getDOMImplementation("LS");

        LSSerializer serializer = impl.createLSSerializer();
        LSOutput lsOutput = impl.createLSOutput();
        lsOutput.setByteStream(output);
        serializer.write(document, lsOutput);
    }

}
