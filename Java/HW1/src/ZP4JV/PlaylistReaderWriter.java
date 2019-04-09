package ZP4JV;

import java.io.InputStream;
import java.io.OutputStream;

public interface PlaylistReaderWriter {
    /**
     * Nacte ze streamu XML soubor a dle nej vytvori prislusny objekt reprezentujici playlist
     */
    public Playlist loadPlaylist(InputStream input) throws Exception;

    /**
     * Ulozi do prislusneho streamu XML soubor predstavujici dany playlist
     */
    public void storePlaylist(OutputStream output, Playlist playlist) throws Exception;

}
