import java.rmi.registry.* ;
import java.rmi.RemoteException ;
import java.rmi.server.UnicastRemoteObject ;

public class RMServer implements RemoteServer {
  public static String x;

      public String getId(String s) throws RemoteException {
        String s1 = "If you ask me nicely, I will tell you who I am";
        System.out.println("A client said: " + s) ;
        //return "Server replying" ;
        if(s.equals("whoRU"))
          return x;
        else
          return s1;
      }

      public static void main(String[] args) {
         try {
          x = args[0];
           RMServer ms = new RMServer() ;
           RemoteServer stub = (RemoteServer) UnicastRemoteObject.exportObject(ms, 0) ;

           Registry registry = LocateRegistry.getRegistry() ;
           registry.rebind("myIDserver", stub) ;
           System.out.println("Server is running") ;
         } catch (Exception e) {
           System.out.println("Server failed with exception " + e) ;
           System.exit(1) ;
         }
      }
}
