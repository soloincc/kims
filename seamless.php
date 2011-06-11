<?php
/*
This function is intended for getting calender info asynchronously.
We are not doing much of authentification
*/
session_start();
include_once('kims_functions.inc');
include_once('kims_dbase_functions.inc');

$pageref = $_SERVER['PHP_SELF'];
$paging=(isset($_REQUEST['page']))?$_REQUEST['page']:'';
$action=(isset($_POST['flag']))?$_POST['flag']:'';
$user=isset($_SESSION['user'])?$_SESSION['user']:'';
$pageref1='';
Connect();

//convert all the keys to actual variables
//reset($_POST);
//while(list($key, $val)=each($_POST)) {eval("${$key}='{$val}'"); echo $surname;}

if(!isset($action) || $action==''){
	die();
}
elseif($action=='getmonth'){
	//we retrieving a month's particulars
	$month=$_POST['month'];
	if(!isset($month) || $month=='') die();
 	$mon=CreateMonths($month);
	$cal=PopulateMonth($month);
	echo $mon.$cal;
}
elseif($action=='postevent'){
	$day=$_POST['day']; $mon=$_POST['mon']; $year=$_POST['year'];
	$type=$_POST['type'];
	//$=$_POST[]; $=$_POST[];
	$other=$_POST['other']; $text=$_POST['text']; $caption=$_POST['caption'];
	$errors=array();
	if(Checks($other,7) || Checks($other,11) || Checks($other, 12)) array_push($errors,'other');
	if(Checks($text,7) || Checks($text,11) || Checks($text, 12)) array_push($errors,'text');
	if(Checks($caption,7) || Checks($caption,11) || Checks($caption, 12)) array_push($errors,'caption');
	if(count($errors)){
		echo "true,there are errors".implode(', ',$errors);
	}else{
		$spes=($type=='other')?$other:'NONE';
		$type=GetSingleRowValue('event_type','id','name',$type);
		if($type==-2) die('true,Error!!');
		$cols=array('date','month','year','owner','caption','text','type','specified');
		$vals=array($day,$mon,$year,0,$caption,$text,$type,$spes);
		$results=InsertValues('events',$cols,$vals);
		if(is_string($results)) die($results);
		else echo 'false,Update Successful';
	}
}
elseif($action=='displayevent'){
    $id=$_POST['eventId'];
	 //add e small form for sending data
	 $pageref1="page=$paging";
	 $form="<form method='POST' action='$pageref?$pageref1' name='form'>"
		."<input type='hidden' id='flagid' name='flag' value=''>"
		."<input type='hidden' id='monthid' name='month' value=''>"
		."<input type='hidden' id='kindid' name='kind' value=''></form>";

	 echo Event($id).$form;
}
elseif($action=='noticeboard'){
    $kind=$_POST['kind'];
    if($kind==5){ // we want the calender
        $month=date('m');
        $mon=CreateMonths($month);
        $cal=PopulateMonth($month);
        $sublinks=SubLinks(-1,null);
        $sidelinks=SideLinks();
        $events=AddEvent();
        echo $sublinks.$sidelinks."<div id='bone'>{$mon}$cal</div>".$events;
    }
    else echo NoticeBoard($kind);
}
elseif($action=='postcontact'){
	//we have new contacts
	$owner=$_POST['owner']; $surname=$_POST['surname']; $fname=$_POST['fname']; $onames=$_POST['onames'];
 	$address=$_POST['address']; $tmobile=$_POST['tmobile']; $toffice=$_POST['toffice']; $thome=$_POST['thome'];
 	$epersonal=$_POST['epersonal']; $eoffice=$_POST['eoffice']; $website=$_POST['website']; $ims=$_POST['ims'];
 	$nims=$_POST['nims']; $iims=$_POST['iims'];
	//there will be a lot of empty values, so check out 4 these

	if($owner=='mine'){ 		//so dont insert a value in the users
  		$id=GetSingleRowValue('users','id','login',$user);
  		if($id==-2) die('error while fetching data');
 	}else{
 		$cols=array('sname','onames','login','pass','allowed');
 		$vals=array($surname,$fname,$surname.'.'.$fname,md5($surname),'1');
 		$results=InsertValues('users',$cols,$vals);
 		if(is_string($results)) die($results);
		$id=GetSingleRowValue('users','id','login',$surname.'.'.$fname);
  		if($id==-2) die('error while fetching data');
 	}
	$vals=array_merge(array($id),$tmobile,$toffice,$thome,array($address));
	$cols=array('user_id','mobile1','mobile2','mobile3','office1','office2','office3','home1','home2','home3','address');
	$results=InsertValues('telephones',$cols,$vals);
	if(is_string($results)) die($results);

	$vals=array_merge(array($id),$epersonal,$eoffice,$website);
	$cols=array('user_id','personal1','personal2','personal3','office1','office2','office3','per_page','off_page','blog');
	$results=InsertValues('emails_websites',$cols,$vals);
	if(is_string($results)) die($results);

	$vals=array_merge(array($id),$ims);
	$cols=array('user_id','gmail','yahoo','hotmail','facebook','aol');
	for($i=0;$i<count($nims);$i++){
		if($nims[$i]!=''){
			array_push($cols,$nims[$i]); array_push($vals,$iims[$i]);
		}
	}
	$results=InsertValues('ims',$cols,$vals);
	if(is_string($results)) die($results);
	echo 'the entries have been successful updated.';
}
elseif($action=='getContacts'){
	$view=$_POST['view']; $which=$_POST['which']; $cont=$_POST['cont'];
	if($cont=='links') echo SubLinks($which,$view).$paging;
	else echo PopulateContacts($view,$which);
}
?>