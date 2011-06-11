<?php
session_start();
include_once('kims_functions.inc');
include_once('kims_dbase_functions.inc');

$pageref = $_SERVER['PHP_SELF'];
$paging=(isset($_REQUEST['page']))?$_REQUEST['page']:'';
$action=(isset($_POST['flag']))?$_POST['flag']:'';
$user=isset($_SESSION['user'])?$_SESSION['user']:'';
$pageref1='';
Connect();

//echo $user;
if(!isset($paging) || $paging=='') $contents=MainPage(null);

//================================================================================================================================
function loggin(){}
if($paging=='login'){
	if($action=='' || !isset($action)){
		if($_POST['login']=='' || $_POST['pass']==''){
			$mess="<div class='error'>Please enter a username or a password to login.</div>";
			$contents=MainPage($mess);
		}else{
			$login=$_POST['login']; $pass=md5($_POST['pass']);
			$id=Login($login,$pass);
			if(!isset($id) || $id==''){
				$mess="<div class='error'>Access denied. Invalid username or password.</div>";
				$contents=MainPage($mess);
			}else{
				$_SESSION['user']=$login;
				$contents=HomePage();
			}
		}

	}
	elseif($action=='cancel') $contents=MainPage(null);
}
//================================================================================================================================

function docsf(){}
if($paging=='mypage'){
	$contents=HomePage();
}
//================================================================================================================================

function projsf(){}
if($paging=='projs'){
	$contents=Projects();
}
//================================================================================================================================

function wassupf(){}
if($paging=='wassup'){
	$contents=Wassup();
}
//================================================================================================================================

function treef(){}
if($paging=='tree'){
	$contents=Tree();
}
//================================================================================================================================

function helpf(){}
if($paging=='hepi'){
	$contents=WatsHappening();
}
//================================================================================================================================

function planf(){}
if($paging=='plan'){
	$contents=Planner();
}
//================================================================================================================================

function contactsf(){}
if($paging=='contacts'){
	$contents=Contacts('list',0);
}
//================================================================================================================================

function picsf(){}
if($paging=='pics'){
	$contents=Pictures();
}
//================================================================================================================================

function videosf(){}
if($paging=='videos'){
	$contents=Videos();
}
//================================================================================================================================

function usisahauf(){}
if($paging=='usisahau'){
	$contents=DontForget();
}
//================================================================================================================================

function settingsf(){}
if($paging=='settings'){
	$contents=Settings();
}
//================================================================================================================================

if(!isset($contents) || $contents==''){
	$contents=Top();
}
?>