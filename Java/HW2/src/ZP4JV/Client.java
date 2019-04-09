package ZP4JV;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class Client {

    public static void main(String[] args) throws IOException {
        String host = "localhost";
        Socket socket = new Socket(host, 4242);
        InputStream inpStream = socket.getInputStream();
        OutputStream outStream = socket.getOutputStream();
        BufferedReader rd = new BufferedReader(new InputStreamReader(inpStream));
        BufferedWriter wr = new BufferedWriter(new OutputStreamWriter(outStream));

        Scanner scanner = new Scanner(System.in);
        String login = scanner.nextLine();
        wr.write(login + "\n");
        wr.flush();
        String respond = "";
        while ((respond = rd.readLine()) != null) {
            System.out.println(respond);
            if (!rd.ready())
                break;
        }

        while (true) {

            String line = scanner.nextLine();

            wr.write(line + "\n");
            wr.flush();

            String output = "";
            while ((output = rd.readLine()) != null) {

                System.out.println(output);
                if (!rd.ready())
                    break;
            }

            if (line.equals("logout") || line.equalsIgnoreCase("stopServer")) {
                break;
            }
        }
        System.out.println("Disconnected from the server");
        scanner.close();
        inpStream.close();
        outStream.close();
        socket.close();
    }
}

