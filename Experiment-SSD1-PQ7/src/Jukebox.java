import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Jukebox extends HttpServlet {

	// Do calculations and update the form
	public void doPost(
		HttpServletRequest request,
		HttpServletResponse response)
		throws IOException, ServletException {

		/** 
		 * 	Build the collection of Song's
		 */
		int lCount; // loop counter

		Vector songList = new Vector();

		songList.add( new Song(
				"Pachchai Nirame",
				"2:15",
				"Tamil Pop",
				"Alai Payuthey (2000)",
				false,
				"TPS001",
				"http://www.raaga.com/channels/tamil/movie/T0000209.html") );
		songList.add( new Song(
				"Bombay (Children of Combodia)",
				"2:38",
				"Jazz",
				"Fred Andersen Quartet/1",
				false,
				"WCS002",
				"http://www.epitonic.com/artists/fredandersonquartet.html#tracks") );
		songList.add( new Song(
				"A Dios Le Pido",
				"1:50",
				"Latin Pop",
				"Juanes : Un Dia Normal/1",
				false,
				"SPS003",
				"http://es.artists.mp3s.com/artist_song/2515/2515448.html") );

		/** 
		 * 	Get user input  
		 * 	Update the collection of Song's for selection status
		 */
		for (lCount = 0; lCount < songList.size(); lCount++) {
			String titleChoice;
			titleChoice =
				(String) request.getParameter(((Song)songList.elementAt(lCount)).getSongID());

			if (titleChoice != null)
				((Song)songList.elementAt(lCount)).select(true);
		}

		/**
		 *	 Prepare the HTML and send it out
		 */
		displayHtml(songList, response);
	} //end doPost

	

	public void displayHtml(Vector sList, HttpServletResponse resp)
		throws IOException {
		/**
		 *  Indicate the content type (for example, text/html), 
		 *  being returned by the response
		 */
		resp.setContentType("text/html");
		

		/** 
		 * 	Retrieve an output stream to use to send data to the client 
		 */
		
		PrintWriter out1 = resp.getWriter();

		/** 
		 * 	Create an instance of the HtmlPage class 
		 */
		
		 HtmlPage  HtmlPageV2 = new HtmlPage();

		/** 
		 * 	Set the attributes of the HtmlPageV2 object 
		 */
		HtmlPageV2 .setTitle("CTE Jukebox");
        HtmlPageV2 .setBackgroundColor("fdf5e6");
        HtmlPageV2 .addText("<H1 align=\'center\'>CTE Jukebox</H1>");
        HtmlPageV2 .addText("<FORM action=\'Jukebox\' method=\'post\'>");
        HtmlPageV2 .addText("<P>Select titles for your playlist:-</P>");
        
		/** 
		 * 	Add the list of songs, using HtmlTable class and addText() method of HtmlPage class
		 */
		/**
		 * Heading first
		 */
		HtmlTable table2 = new HtmlTable(10);
		table2.startRow();
		table2.addCell("<B>Title</B>");
		table2.addCell("<B>Duration(min)</B>");
		table2.addCell("<B>Category</B>");
		table2.addCell("<B>Album/Track</B>");
		table2.endRow();


		/**
		 * Now the list of titles to choose from
		 */
		int lCount2;
		for(lCount2 = 0; lCount2 < sList.size(); ++lCount2) {
			table2.startRow();
			String checkbox = "<INPUT type=\'checkbox\' name=\'" + ((Song)sList.elementAt(lCount2)).getSongID() + "\' value=\'" + ((Song)sList.elementAt(lCount2)).getTitle() + "\'";
			if(((Song)sList.elementAt(lCount2)).isSelected()) {
				checkbox = checkbox + " checked>";
			} else {
				checkbox = checkbox + ">";
			}


		/**
		 *	Add any other HTML to be added as additional text to the body 
		 */
			HtmlAnchor link = new HtmlAnchor("play", ((Song)sList.elementAt(lCount2)).getSongLink());
			checkbox = checkbox + ((Song)sList.elementAt(lCount2)).getTitle();
			table2.addCell(checkbox);
			table2.addCell(((Song)sList.elementAt(lCount2)).getTime());
			table2.addCell(((Song)sList.elementAt(lCount2)).getCategory());
			table2.addCell(((Song)sList.elementAt(lCount2)).getAlbumTrack());
			table2.addCell(link.buildHtml());
			table2.endRow();
		}

		//Use the buildHtml method of HtmlTable to construct the HTML code for the table
		HtmlPageV2.addText(table2.buildHtml());

		HtmlPageV2.addText("<BR><BR><BR>");
		//Add the text that creates the Submit button. (Use the addText method.)
		HtmlPageV2.addText("<INPUT type=\'submit\' name=\'UserRequest\' value=\'My Playlist\'>");

		/**
		 * 	Display the playlist now; this is a TEXTAREA element for which
		 * 	must be built using  the addText method of HtmlPageV2 class
		 */

		HtmlPageV2.addText("<BR><BR><BR>");
		HtmlPageV2.addText("<TEXTAREA name=\'playList\' rows=\'10\' cols=\'80\' readonly>");

		//Display the songs that are selected
		for(lCount2 = 0; lCount2 < sList.size(); ++lCount2) {
			if(((Song)sList.elementAt(lCount2)).isSelected()) {
				HtmlPageV2.addText(((Song)sList.elementAt(lCount2)).getTitle() + "\t" + ((Song)sList.elementAt(lCount2)).getTime() + "\t" + ((Song)sList.elementAt(lCount2)).getCategory() + "\n" + ((Song)sList.elementAt(lCount2)).getAlbumTrack() + "\n\n");
			}
		}

		/**
		 *	Add any other HTML to be added as additional text to the body 
		 */

		HtmlPageV2.addText("</TEXTAREA>");
		HtmlPageV2.addText("</FORM>");

		/**
		 *	 Construct the HTML response
		 */
		out1.print(HtmlPageV2.buildHtml());
		out1.flush();//刷新printwriter流的缓冲区
		out1.close();//文件流用完之后必须及时通过close方法关闭，否则会一直处于打开状态，直至程序停止，增加系统负担。
	}
}
