package ZP4JV;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class Server {

    private static boolean stopServer = false;
    private static ArrayList<Message> messages = new ArrayList<>();
    private static String user;


    public static void run() throws IOException {
        ServerSocket srvSocket = new ServerSocket(4242);

        while (isStopServer() == false) {
            Socket clientSocket = srvSocket.accept();
            Thread serverThread = new ServerThread(clientSocket);
            serverThread.start();
        }
        System.out.println("Server is shutting down");
        srvSocket.close();
    }


    private static class ServerThread extends Thread {

        private Socket clientSocket;

        public ServerThread(Socket clientSocket) {
            this.clientSocket = clientSocket;
        }

        public void run() {
            try (BufferedReader rd = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                 BufferedWriter wr = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()))) {

                wr.write("Please log in:");
                wr.write("\r\n");
                wr.flush();
                processRequests(rd, wr);
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                try {
                    clientSocket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    /*
    After many hours of trying to write messages to XML file via DOM, concating and adding new nodes to existing file,
    I decided to store messages in ArrayList.
       */
    private static void processRequests(BufferedReader rd, BufferedWriter wr) throws Exception {
        String lin = rd.readLine();

        if (lin.startsWith("connect"))
            if (logIn(lin, wr)) {
                dispatcher(wr, rd);
            } else {

                wr.write("ERR");
                wr.write("\r\n");
                wr.flush();
            }


    }

    private static void dispatcher(BufferedWriter wr, BufferedReader rd) throws IOException {
        while (true) {
            String line = rd.readLine();
            if (line == null) break;

            if (line.equalsIgnoreCase("logout")) {
                System.out.println("Disconnected " + user);
                wr.write("OK");
                wr.write("\r\n");
                wr.flush();
                break;

            } else if (line.startsWith("msg")) {
                sendMessage(line, wr);
            } else if (line.equalsIgnoreCase("read")) {
                readMessages(wr);
            } else {
                wr.write("Unknown command");
                wr.write("\r\n");
                wr.flush();
            }

        }
    }

    private static synchronized void readMessages(BufferedWriter wr) throws IOException {
        if (messages.size() != 0) {
            int i = 0;
            while (i < messages.size()) {
                Message msg = messages.get(i);
                if (msg.getForUser().equals(user)) {
                    wr.write("FROM " + msg.getFromUser() + ": " + msg.getText());
                    wr.write("\r\n");
                    messages.remove(i);
                } else {
                    i++;
                }
            }
            wr.write("OK");
            wr.write("\r\n");
            wr.flush();
        } else {
            wr.write("ERR");
            wr.write("\r\n");
            wr.flush();
        }
    }

    private static synchronized void sendMessage(String line, BufferedWriter wr) throws IOException {
        if (line.length() > 8) {
            String[] mess = line.substring(8).split(": ");
            Message message = new Message(mess[0], user, mess[1]);
            messages.add(message);
            wr.write("OK");
            wr.write("\r\n");
            wr.flush();
        } else {
            wr.write("ERR");
            wr.write("\r\n");
            wr.flush();
        }
    }

    private static boolean logIn(String line, BufferedWriter wr) throws Exception {
        String[] args = line.substring(8).split(" ");
        String username = args[0];
        String password = args[1];
        DataInputStream is = new DataInputStream(new FileInputStream("/D:/users.xml"));
        ArrayList<User> arrayList = new ReadUsers().readUsers(is);
        if (checkUsername(username, password, arrayList)) {
            System.out.println("Connected " + username);
            wr.write("OK");
            wr.write("\r\n");
            wr.flush();
            return true;
        }

        return false;

    }

    private static boolean checkUsername(String username, String password, ArrayList<User> arrayList) {
        boolean found = false;

        for (User u : arrayList) {
            if ((u.getUsername().equals(username)) && (u.getPassword().equals(password))) {
                found = true;
                user = u.getUsername();
            }

        }
        return found;
    }

    private static synchronized void setStopServer(boolean value) {
        stopServer = value;
    }

    private static synchronized boolean isStopServer() {
        return stopServer;
    }
}
