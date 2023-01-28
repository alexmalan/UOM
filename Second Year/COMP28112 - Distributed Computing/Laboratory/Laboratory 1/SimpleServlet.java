import java.io.* ;

import javax.servlet.*;
import javax.servlet.http.*;

public class SimpleServlet extends HttpServlet {
    public static String initarg ;

  public void init(ServletConfig config)
	throws ServletException
    {
	super.init(config);
        initarg= config.getInitParameter("id") ;
        System.out.println("Initial parameter: id = " + initarg) ;
    }

  public void doPost(HttpServletRequest req, HttpServletResponse res)
	throws ServletException, IOException {
    res.setContentType("text/html");
    PrintWriter toClient = res.getWriter();
    String [] given = req.getParameterValues("input String");
    System.out.println("A client said: " + given[0]) ;
    toClient.println("<html><HEAD><TITLE>Simple Servlet Example</TITLE>") ;
    toClient.println("</HEAD><BODY BGCOLOR=\"white\">") ;
    toClient.println("<H1>This is output from the example Servlet</H1>");
    if(given[0].equals("whoRU"))
        toClient.println(initarg);
    else
        toClient.println("If you ask me nicely, I will tell you who I am");
    toClient.println("<p>");
    toClient.println("<HR></BODY></HTML>");
    toClient.close();
  }
}

