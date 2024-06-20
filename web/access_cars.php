<!-- access_cars.php
    A PHP script to access the cars database
    through MysQL
    -->
<!DOCTYPE html>
<html lang = "en" >
<head>
<title> Access the cars database with MySQL</title>
<meta charset = "utf-8"/>
</head>

<body>
<?php
//Connect to MySQL
$db = mysqli_connect ("localhost" , "root", "", "cars") ;
if(mysqli_connect_errno ( )){
print "Connect failed: " . mysqli_connect_error ();
exit ( );
}
// Get the query and clean it up (delete leading and trailing
// whitespace and remove backslashes from magic_quotes_gpc)
$query = $_POST ['query'] ;
trim ($query);
$query = stripslashes ($query);
// Display the query, after fixing html characters
$query_html = htmlspecialchars ($query) ;
print "<p> The query is: " . $query_html . "</p>" ;

//Execute the query
$result = mysqli_query ($db, $query);
if (!$result) {
    print "Error - the query could not be executed" .
    mysqli_error();
    exit;
    }
    //Display the results in a table
    print "<table><caption> <h2> Query Results </h2> </caption>";
    print "<tr align = 'center'>" ;
    // Get the number of rows in the result
    $num_rows = mysqli_num_rows ($result);
    // If there are rows in the result, put them in an HTML table
    if ($num_rows > 0){
    $row = mysqli_fetch_assoc ($result) ;
    $num_fields = mysqli_num_fields ($result) ;
    //Produce the column labels
    $keys = array_keys ($row) ;
    for ($index = 0; $index < $num_fields; $index++)
    print "<th>" . $keys [$index] . "</th>" ;
    print "</tr>" ;
    // output the values of the fields in the rows
    for ($row_num = 0 ; $row_num < $num_rows; $row_num++){
    print "<tr>";
    $values = array_values ($row);
    for ($index = 0 ; $index < $num_fields; $index++) {
        $value = htmlspecialchars ($values [$index]) ;
    print "<td>" . $value . "</td>" ;
    }
    print "</tr>" ;
    $row = mysqli_fetch_assoc ($result) ;}
    }
    else {
        print "There were no such rows in the table <br />";
    }
    print "</table>" ;
    ?>
    </body>
    </html>