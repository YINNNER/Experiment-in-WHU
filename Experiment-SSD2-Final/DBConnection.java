
// *DataBase Connectivity from the Servlet.
import java.io.*;
import java.util.*;
import javax.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class DBConnection extends HttpServlet {
    public void service(HttpServletRequest request,
                        HttpServletResponse response)
            throws IOException, ServletException{
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html>");
        out.println("<head><title>Servlet JDBC</title></head>");
        out.println("<body>");
        out.println("<h1>Servlet JDBC</h1>");
        out.println("</body></html>");
        // connecting to database
        Connection con = null;
        Statement stmt = null;
        ResultSet rs = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            con =DriverManager.getConnection
                    ("jdbc:mysql://10.132.3.37:3306/animals","root","");
            stmt = con.createStatement();
            rs = stmt.executeQuery("SELECT * FROM pet");
            // displaying records
            while(rs.next()){
                out.print(rs.getObject(1).toString());
                out.print("\t\t\t");
                out.print(rs.getObject(2).toString());
                out.print("\t\t\t");
                out.print(rs.getObject(3).toString());
                out.print("<br>");
            }
        } catch (SQLException e) {
            throw new ServletException("Servlet Could not display records.", e);
        } catch (ClassNotFoundException e) {
            throw new ServletException("JDBC Driver not found.", e);
        } finally {
            try {
                if(rs != null) {
                    rs.close();
                    rs = null;
                }
                if(stmt != null) {
                    stmt.close();
                    stmt = null;
                }
                if(con != null) {
                    con.close();
                    con = null;
                }
            } catch (SQLException e) {}
        }
        out.close();
    }
}