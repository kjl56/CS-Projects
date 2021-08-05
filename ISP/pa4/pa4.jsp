<!-- to do: convert db-starter.php to jsp -->
<%@page import="java.sql.*"%>  
<html>
<head>
  <title> Database Programming With JSP </title>
  <style type = "text/css">
    td, th, table {border: thin solid black;}
  </style>
</head>
<body>
<p>
  <!-- get input data -->
  <% 
    String id = request.getParameter("id");
    String type = request.getParameter("type");
    String miles = request.getParameter("miles");
    String year = request.getParameter("year");
    String state = request.getParameter("state");
    String action = request.getParameter("action");
    String statement = request.getParameter("statement");
    String query = "";

    // If any of numerical values are blank, set them to zero
    if (id == "") id = "0";
    if (miles == "") miles = "0.0";
    if (year == "") year = "0";
    if (state == "") state = "0";
    
    // Connect to MySQL
    Connection con;
    Class.forName("com.mysql.jdbc.Driver").newInstance();
    try {
      // Open Database connection
      con = DriverManager.getConnection("jdbc:mysql://db1.cs.uakron.edu:3306/ISP_kjl56","kjl56","LugoKylesan00");

      // print "<b> The action is: </b> $action <br />";
      if(action == "display")
          query = "";
      else if (action == "insert")
          query = "insert into Corvettes values($id, '$type', $miles, $year, $state)";
      else if (action == "update")
          query = "update Corvettes set Body_style = '$type', Miles = $miles, Year = $year, State = $state where Vette_id = $id";
      else if (action == "delete")
          query = "delete from Corvettes where Vette_id = $id";
      else if (action == "user")
          query = statement;
      
      if (query != "") {
        query.trim();
        //String query_html = <c:out value="${myString}"/>
      }
      // Query Database (all queries use the same connection)

    }
    catch (Exception e) {
      out.println( e.toString() );  // Error message to display
    }

  %>
</p>
</body>
</html>