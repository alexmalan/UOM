import java.io.* ;
import java.net.* ;

class SocketServer {
/* Sets up a server on port 8181 which you can telnet to.
 * If you send a message, it will reply and then disconnect.
*/
public static String x;

public static void main(String [] args) throws IOException {
  x = args[0];
  final int port = 8181 ;
  ServerSocket listener = new ServerSocket(port) ;
  System.out.println("Server is running") ;
  // Listen for clients ....
  while (true) {
    Socket client = listener.accept() ;
    new SessionHandler(client).start() ;
    }
  }
}

class SessionHandler extends Thread {
// an instance created by the server for each client 

private BufferedReader in ;
private PrintWriter out ;
private Socket client ;

  SessionHandler(Socket s) {
    client = s ; 
    }

  public void run() {
    try {
      in = new BufferedReader(new InputStreamReader(
         client.getInputStream())) ;
      out = new PrintWriter(client.getOutputStream(), true) ;
      String temp = in.readLine();
      System.out.println("A client said: " + temp) ;
      //out.println("Server replying") ;
      if(temp.equals("whoRU"))
        out.println(SocketServer.x);
      else
        out.println("If you ask me nicely, I will tell you who I am");
    } catch (Exception e) { System.out.println("Server error " + e) ; }
    try { client.close() ; }
    catch (Exception e) {;}
  }
}

