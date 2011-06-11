<?php
$config = array();
$config["user"] = 'root'; //database username
$config["pass"] = 'admin'; //database password
$config["dbase"] = 'kims'; //database name
$config["dbloc"] = 'localhost'; //database location

$dbcon = NULL;

function Connect(){
	global $dbcon, $config;
	$dbcon = mysql_connect($config["dbloc"], $config["user"], $config["pass"]) OR die ('Cannot connect to the database.');
	$results=mysql_query("SET NAMES 'utf8'", $dbcon) or die ('error while setting charset '. mysql_error());
   mysql_select_db($config['dbase'],$dbcon);
   return true;
}
//================================================================================================================================

function Login($login, $pass){
	$query="SELECT id FROM users WHERE login='$login' AND pass='$pass' AND allowed=1";
	$result=mysql_query($query) or die('Error while connecting to the dbase.'.mysql_error());
	$row=mysql_fetch_array($result);
	return $row[0];
}
//================================================================================================================================

function GetSingleColumnValues($table,$col,$order,$criteria){
//this function is just like GetAllColumnValues only that it gets values from a single column only n dont support linked tables
global $dbcon;
   $ordering=($order)?" ORDER BY $col":'';
   if($criteria){
   	$cols=$criteria[0]; $col_vals=$criteria[1];
   	$temp='WHERE ';
   	for($i=0;$i<count($cols);$i++)
   		$temp.=($i==0)?$cols[$i].'='.$col_vals[$i]:' AND '.$cols[$i].'='.$col_vals[$i];
   }
   else $temp='';
   $query="SELECT $col FROM $table $temp $ordering";
   //echo $query.'<br>';
   $result=mysql_query($query, $dbcon);
   if(!$result) return "There was an error while fetching the values from the $table table. ".mysql_error();
   $results=array();
   while($row=mysql_fetch_array($result)) array_push($results,$row[0]);
   return $results;
}
//================================================================================================================================

function GetColumnValues($table,$cols,$criteria,$glue,$order){
//we use this function to select specified columns from the table and using the search specified
//search_criteria is somethin like 'WHERE id=10', cols is an array of columns to select
//criteria is an array consisting of 2 arrays.array0 is e column names while array1 is e correspondin col values
global $dbcon;
	if(is_array($criteria)){
		$columns=$criteria[0]; $vals=$criteria[1];
		$criteria='';
		for($i=0;$i<count($columns);$i++){
			$criteria.=($i==0)?'WHERE '.$columns[$i]."='".$vals[$i]."'":" $glue ".$columns[$i]."='".$vals[$i]."'";
		}
	}
	if(is_array($order)) $order="ORDER BY ".implode(',',$order);
	$query="SELECT ".implode(',',$cols)." FROM $table $criteria $order";
   //echo $query.'<br>';
   $result=mysql_query($query, $dbcon);
   if(!$result) return "There was an error while fetching the values from the $table table. ".mysql_error();
   $results=array();
   while($row=mysql_fetch_array($result)) array_push($results,$row);
   return $results;
}
//================================================================================================================================

//inserts a record into the dbase
function InsertValues($table, $cols, $colvals){
global $dbcon;
	$col_vals="'".implode("', '",$colvals)."'";
   $query="INSERT INTO $table(".implode(",",$cols).") VALUES($col_vals)";
   //echo $query.'<br>';
   $result=mysql_query($query, $dbcon);
   if(!$result) return "There was an error while adding data into the $table table. ".mysql_error();
   else return 0;
}
//================================================================================================================================

//returns a single col value from a record
function GetSingleRowValue($table,$toreturn,$col,$colval){
global $dbcon;
   $query="SELECT $toreturn FROM $table WHERE $col='$colval'";
   //echo $query.'<br>';
   $result=mysql_query($query, $dbcon);
   if(!$result) return -2;
   $row=mysql_fetch_array($result);
   return $row[0];        //this is being returned as a string even if its an integer
}
//================================================================================================================================

function GetQueryValues($query, $type){
   //echo $query.'<br>';
global $dbcon;
   $result=mysql_query($query, $dbcon);
   if(!$result) return "There was an error while fetching the values from the database. ".mysql_error();
   $results=array();
   while($row=mysql_fetch_array($result, $type)) array_push($results,$row);
   //echo count($results).' '.count($results[0]).'<br>';
   return $results;
}
//================================================================================================================================
?>