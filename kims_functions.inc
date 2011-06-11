<?php

function MainPage($message){
	global $pageref, $pageref1;
	$contents=<<<CONTENTS
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
	<td width=''>&nbsp;</td>
	 <td width="800" id='overall'>
		<div id='header'>kims personal page</div>
		<div>
			<div id='login'>
			<form method='POST' action="$pageref?page=login" name='form'>
			<div><label>Username</label>&nbsp;&nbsp;<input type='text' name='login' size='20' /></div>
			<div><label>Password</label>&nbsp;&nbsp;&nbsp;&nbsp;<input type='password' name='pass' size='15' /></div>
	$message
			<div style='float: left; padding-left: 80px;'><input class='en_button' type='submit' value='Login'></div>
			<div style='float: left;'><input class='en_button' type='button' value='Cancel' onClick="setAndSubmit(form,'cancel');"></div>
			</div>
			<input type='hidden' name='flag' id='flagid' value='' />
			</form>
		</div>
	</td>
	<td width=''>&nbsp;</td>
  </tr>
 </table>
CONTENTS;
	return $contents;
}
//================================================================================================================================

function Top(){
	$links=CreateLinks(12);
	$contents =<<<CONTENTS
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
	<td width=''>&nbsp;</td>
	 <td width="800" id='overall'>
		<div id='header'>kims personal page</div>
	$links
		<div id='inprogress'>slow down!!! solo at work...<br>
			Please try later. if you have any suggestions feel free to contact solo @ <span class='email'>soloincc@gmail.com.</span>
		</div>
	</td>
	<td width=''>&nbsp;</td>
  </tr>
 </table>
CONTENTS;
	return $contents;
}
//================================================================================================================================

function HomePage(){
	$sublinks='';
	$contents=<<<CONTENTS
	<br />
	<div id='sidelinks'>
		<span>side links</span><br />
		<span>go here</span>
	</div>
	<div id='bone'>Biography</div>
CONTENTS;
	return ProtoType($contents, 0, true,$sublinks);
}
//================================================================================================================================

function ProtoType($content, $id, $includeExtra,$sublinks){
	$links=CreateLinks($id);
	$sideinfo=($includeExtra)?ExtraInfo():'';

	$contents=<<<CONTENTS
<table width="90%" border="0" cellspacing="0" cellpadding="0" align='center'>
  <tr><td>&nbsp;</td>
	 <td width="800">
		<div id='header'>kims personal page</div>
	$links
		<div id='content'>{$sublinks}$content{$sideinfo}</div>
	</td>
	<td>&nbsp;</td></tr>
	<tr><td>&nbsp;</td><td>
		<div id='footer'>
			<span class='footerlinks' style='text-decoration: none;'>&copy; kims personal page</span>
			<a href='javascript:;' class='footerlinks'>about the developer</a>
			<a href='javascript:;' class='footerlinks'>about us</a>
		</div>
	</td><td>&nbsp;</td></tr>
  </table>
CONTENTS;
	return $contents;
}
//================================================================================================================================

function CreateLinks($id){
	global $pageref;
	$links=array('my page','docs','projects','whats up', 'hse keepin','family tree','wats happenin','planner','contacts','pics','videos','dont forget');
	$actions=array('mypage','docs','projs','wassup','settings','tree','hepi','plan','contacts','pics','videos','usisahau');
	$details="<div id='links'>";
	for($i=0;$i<5;$i++) $details.=($id==$i)?"<span class='currentlink'>".$links[$i]."</span>":"<a href='$pageref?page=".$actions[$i]."'>".$links[$i]."</a>";
	$details.="</div><div id='links'>";
	for($i=5;$i<12;$i++) $details.=($id==$i)?"<span class='currentlink'>".$links[$i]."</span>":"<a href='$pageref?page=".$actions[$i]."'>".$links[$i]."</a>";
	$details.="</div>";

	return $details;
}
//================================================================================================================================

function Documents(){
	$contents=<<<CONTENTS
CONTENTS;
	return $contents;
}
//================================================================================================================================

function Projects(){
	$contents=<<<CONTENTS
CONTENTS;
	return $contents;
}
//================================================================================================================================

function Wassup(){
	$contents=<<<CONTENTS
CONTENTS;
	return $contents;
}
//================================================================================================================================

function Tree(){
	$contents=<<<CONTENTS
CONTENTS;
	return $contents;
}
//================================================================================================================================

function WatsHappening(){
	//get all the events for today, and give a preview for kesho
	$sidelinks=SideLinks();
	$details=Event(1);
$contents=<<<CONTENTS
	$sidelinks
	<div id='bone'>
	$details
	</div>
CONTENTS;
	return ProtoType($contents,6,false,"<div>&nbsp;</div>");
}
//================================================================================================================================

function Event($id){
	$query="SELECT caption, text FROM events WHERE id=$id";
	$det=GetQueryValues($query,MYSQL_NUM);
	if(is_string($det)) return $det;
	$similarEvents=SimilarEvents($id, 5);
	if($similarEvents==-1) return "There was an error while fetching data from the dbase.";
	$capt=$det[0][0]; $text=$det[0][1];
	$text=str_replace("\n","<br>",$text);
	$contents=<<<CONTENTS
	<div>
		<div id='event_content'>
			<div>$capt</div>
			<div>$text</div>
		</div>
		<div id='similar_events'>
	$similarEvents
		</div>
	</div>
CONTENTS;
	return $contents;
}
//================================================================================================================================

function SimilarEvents($id, $number){
	//generate $number similar events b4 n after the event wit this id
	$query="SELECT B.id, B.name FROM events AS A INNER JOIN event_type AS B ON A.type=B.id WHERE A.id=$id";
	$eventId=GetQueryValues($query, MYSQL_NUM);
	if(is_string($eventId)) return -1;
	//print_r($eventId);
	$eventType=$eventId[0][1]; $eventid=$eventId[0][0];
	$contents="<div id='other_events_caption'>other $eventType events</div><div>";

	$compare=array('<','=','>');
	foreach($compare as $symbol){
		$query="SELECT id, caption FROM events WHERE id{$symbol}{$id} AND type=$eventid LIMIT 0,$number";
		//echo $query.'<br>';
		$res=GetQueryValues($query, MYSQL_NUM);
		if(is_string($res)) return -1;
		for($i=0; $i<count($res); $i++){
			if($symbol=='=') $contents.="<span>".$res[$i][1]."</span><br />";
			else $contents.="<a href='javascript:;' onClick='getEventContents(".$res[$i][0].")'>".$res[$i][1]."</a><br />";
		}
	}
	$contents.="<span><a href='javascript:;' onClick='getEvents(5)'>view calender</a></span><br /></div>";
	return $contents;
}
//================================================================================================================================

function Planner(){
	$mon=date('m');
	$months=CreateMonths($mon);
	$cal=PopulateMonth($mon);
	$addEvent=AddEvent();
	$sublinks=SubLinks(-1,null);
	$sidelinks=SideLinks();

	$contents=<<<CONTENTS
	$sidelinks
	<div id='bone'>
	$months
	$cal
	</div>
	$addEvent
CONTENTS;

	return ProtoType($contents,7,false,$sublinks);
}
//================================================================================================================================

function CreateMonths($displayMon){
	$months=array('jan','feb','mar','apr','may','jun','jul','aug','sep','oct','nov','dec');
	$mon=date('m');
	$content="<div id='months'>";
	if($displayMon==$mon || !isset($displayMon) || $displayMon=='') $content.="<span id='curmonth'>".$months[$mon-1]."</span>";
	else $content.="<a href='javascript:;' onClick='getMonth(\"$mon\");'>".$months[$mon-1]."</a>";
	for($i=$mon+1;$i<13;$i++){
		if($displayMon==$i) $content.="<span id='curmonth'>".$months[$i-1]."</span>";
		else $content.="<a href='javascript:;' onClick='getMonth(\"$i\");'>".$months[$i-1]."</a>";
	}
	$content.="<span class='year'>'".date('y')."</span>\n";
	for($i=1;$i<$mon;$i++){
		if($displayMon==$i) $content.="<span id='curmonth'>".$months[$i-1]."</span>";
		else $content.="<a href='javascript:;' onClick='getMonth(\"$i\");'>".$months[$i-1]."</a>";
	}
	$dat=date('y')+1;
	$nxtyr=(strlen($dat)==1)?"0{$dat}":$dat;
	$content.="<span class='year'>'$nxtyr</span></div>";
	return $content;
}
//================================================================================================================================

//creates a calender for a given month and all the events of that month
function PopulateMonth($displayMon){
	//we need to determine the number of days, which year we dealing with, the first day of e mon
	global $pageref, $pageref1;
	$curMon=date('m'); $curDay=date('d');
	$yr=($displayMon>=$curMon)?date('Y'):date('Y')+1; //year we interested with
	$timing=mktime(0,0,0,$displayMon,1,$yr);	//get the timestamp 4 e day in qst
	$noDays=cal_days_in_month(CAL_JULIAN,$displayMon,$yr);	//no of days in e month in qst
	$wkNum=date('W',$timing);
	$temp=date('w',$timing);
	$wkday=($temp==0)?7:$temp;		//numeric day of e day in a wk
	$temp=date('d',$timing);
	$firstDay=($temp<7)?(($wkday-$temp)%7):(($temp-$wkday)%7);	//numeric first day of e month
	$endPad=(35-($firstDay+$noDays)>0)?array_fill($firstDay+$noDays,35-($firstDay+$noDays),'&nbsp;'):array();
	if($firstDay!=0 && ($firstDay+$noDays)!=0)
	$monthDays=array_merge(array_fill(0,$firstDay,''),range(1,$noDays),$endPad);
	elseif($firstDay==0 && ($firstDay+$noDays)!=0) $monthDays=array_merge(range(1,$noDays),$endPad);
	elseif($firstDay!=0 && ($firstDay+$noDays)==0) $monthDays=array_merge(array_fill(0,$firstDay,'&nbsp;'),range(1,$noDays));
	reset($monthDays);
	$eventful_days=GetSingleColumnValues('events','date','date',array(array('month'),array($displayMon)));
	if(is_string($eventful_days)) $eventful_days=array();

	//code 4 a date with an event
	//$temp="<div id='eventday'><span class='date' $temp1>".current($monthDays)."</span>"
	//."<span class='event'><a href='javascript:;'>kim's bday</a> <a href='javascript:;'>mag's bday</a></span></div>";
	$contents="<div id='calender'>"; $content=array();
	$days=array('wk. no.','monday','tuesday','wed.','thur.','friday','sato','sunday');
	for($i=0;$i<6;$i++){
		for($j=0;$j<8;$j++){
			$dayid=($j==0)?'firstday':'day';
			$events='';
			if($i==0){
				$contents.="<div class='dayofwk'>".$days[$j]."</div>";
			}
			elseif($j==0) array_push($content,"<div class='$dayid'>".($wkNum+$i-1)."</div>");
			else{
				if(in_array(current($monthDays),$eventful_days)){
					$result=GetColumnValues('events',array('id','caption'),array(array('date','month'),array(current($monthDays),$displayMon)),'AND','');
					if(!is_string($result)){ $events=$result; $count=count($events);}
				}

				if($j>5)   $class='wknd';  //we dealing wit wknds
				else   $class='day';   //normal days

				$style=($displayMon>=$curMon && current($monthDays)==$curDay)?"style='text-decoration: underline;'":'';

				if($events!=''){ //eventful day
					if($count!=0) $class=($class=='wknd')?'wknd_date':'date';
					if($count<3){
						if($count==0) array_push($content,"<div class='$class' $style>".current($monthDays)."</div>");
						else{   //we have less than 3 events
							$temp="<div id='eventday'><span class='$class' $style>".current($monthDays)."</span>";
							$temp.="<span class='event'><a href='javascript:;' onClick='getEventContents(".$events[0][0].")'>".$events[0][1]."</a>";
							$temp.=(count($events)==2)?" <a href='javascript:;' onClick='getEventContents(".$events[1][0].")'>".$events[1][1]."</a></span></div>":"</span></div>";
						}
					}else{  //if we have more than three events
						$temp="<div id='eventday'><span class='$class' $style>".current($monthDays)."</span>";
						$temp.="<span class='event'><a href='javascript:;' onClick='getDateEvents(".current($monthDays).",$displayMon)'>all events</a></span></div>";
					}
					array_push($content,$temp);
				}
				else{
					array_push($content,"<div class='$class' $style>".current($monthDays)."</div>"); //kawa siku
				}
				next($monthDays);
			}
		}
	}

	if(current($monthDays)!=null){
		//we have some days which didnt fit to the calender, so put em at e top
		$j=1;
		while(current($monthDays)){
			$content[$j]="<div class='$dayid'>".current($monthDays)."</div>";
			$j++; next($monthDays);
		}
	}
	$contents.=implode("\n",$content);
	//create a kasmall form to be used for passing data

	$contents.=<<<CONTENTS
	</div>
	<form method='POST' action="$pageref?$pageref1" name='form'>
		<input type='hidden' id='flagid' name='flag' value=''>
		<input type='hidden' id='monthid' name='month' value=''>
		<input type='hidden' id='kindid' name='kind' value=''>
	</form>
CONTENTS;
	return $contents;
}
//================================================================================================================================

function AddEvent(){
	//creates an input form for adding an event
	global $pageref, $pageref1;
	$days=Populate_Combo(range(1,31),range(1,31),'day','day',date('d'),true,false);
	$years=Populate_Combo(range(1940,2015),range(1940,2015),'year','year',date('Y'),true,false);
	$mon=array('jan','feb','mar','apr','may','jun','jul','aug','sep','oct','nov','dec');
	$months=Populate_Combo($mon,range(1,12),'month','mon',date('m'),true,false);
	$temp=GetSingleColumnValues('event_type','name','name',null);
	$type=Populate_Combo($temp,$temp,'type','type',0,true,false);

	$sample="<div id='eventday'><span class='date'>28'jan</span>"
	."<span class='event'><a href='javascript:;'>kim's bday</a> <a href='javascript:;'>mag's bday</a></span></div>";

	$contents=<<<CONTENTS
<div id='events'>
<span style='float:right; margin: 10px 50px 5px 0px; font-size: 13px;'><a href='javascript:showHide("addevent");'>show/hide add event</a></span>
<div id='addevent' class='collapsed'>
	<div id='errmessageid' class='normal' align='center'>enter the event details.</div>
	<form method='POST' action="$pageref?$pageref1" name='addingevent'>
	<div id='eventday'><label id='datelabel' class='norm'>date</label><span>$days</span><span>$months</span><span>$years</span>
	<label id='typelabel' class='norm'>event type</label>$type
	<label id='otherlabel' class='norm'>if other</label><input type='text' name='other' id='otherid' size='15' value='specify'></div>
	<div id='eventcaption' style='width: auto;'><label id='captionlabel' class='norm'>caption</label>
	<input type='text' name='caption' id='captionid' size='15' value=''><br>
		<label id='textlabel' class='norm'>details (max. 1000 chars.)</label><br><textarea name='text' id='textid' cols='60' rows='6'></textarea>
	</div>
	<div id='links'><a href='javascript:postEvent();'>post</a><a href='javascript:;'>cancel</a></div>
	<input type='hidden' id='eventflagid' name='flag' value=''>
	</form>
</div></div>
CONTENTS;
	return $contents;
}
//================================================================================================================================

function NoticeBoard($kind){
	//will cater for all types of notice boards ie all, anniversaries, bdays, bashes, others
	global $pageref, $pageref1;
	$addEvent=AddEvent();
	$sublinks=SubLinks($kind,null);
	$sideinfo=ExtraInfo();
	$sidelinks=SideLinks();
	if($kind==0 || $kind==4){
		if($kind==0) $criteria=null;
		else{
			$results=GetColumnValues('event_type',array('id'),array(array('name','name'),array('other','social')),'OR','');
			if(is_string($results)) die($results);
			$vals=array($results[0][0],$results[1][0]);
			$cols=array('type','type');
			$criteria=array($cols,$vals);
		}
	}
	else{
		if($kind==1) $type='anniversary';
		elseif($kind==2) $type='bday';
		elseif($kind==3) $type='bash';
		$typeid=GetSingleRowValue('event_type','id','name',$type);
		if($typeid==-2) die('We have an error.');
		$criteria=array(array('type'),array($typeid));
	}
	$results=GetColumnValues('events',array('date','month','year','caption','type','id'),$criteria,'OR',array('month','date'));
	if(is_string($results)) die($results);
	$mon=array('jan','feb','mar','apr','may','jun','jul','aug','sep','oct','nov','dec');
	$bone="<div id='eventslist'><table width='100%'>";
	if(count($results)==0) $bone.="<th class='header'>there are no events in this group.</th>";
	else $bone.="<th class='header'>there are ".count($results)." upcoming events</th>";
	for($i=0;$i<count($results); $i++){
		$row=$results[$i];
		$yr=($kind<3)?'':$row[2];
		if($kind==0 || $kind==4){
			$type=GetSingleRowValue('event_type','name','id',$row[4]);
			if($type==-2) die('we have an error.');
			$type="[$type]";
		}
		else $type='';
		$class=(($i%2))?'odd':'even';
		$rem=($row[0]%10);
		if($rem>3) $pr='th';
		elseif($rem==3) $pr='rd';
		elseif($rem==2) $pr='nd';
		elseif($rem==1) $pr='st';
		$bone.="<tr><td class='$class'><a href='javascript:;' onClick='getEventContents($row[5])'>".$row[3].'</a> on '.$row[0]."$pr ".$mon[$row[1]-1].' '.$yr." $type</td></tr>";
	}
	$bone.='</table></div>';

	$contents=<<<CONTENTS
	$sublinks
	$sidelinks
	<div id='bone'>
	$bone
	</div>
	$sideinfo
	<form method='POST' action="$pageref?$pageref1" name='form'>
		<input type='hidden' id='flagid' name='flag' value=''>
		<input type='hidden' id='monthid' name='month' value=''>
		<input type='hidden' id='kindid' name='kind' value=''>
	</form>
	$addEvent
CONTENTS;

	return $contents;
}
//================================================================================================================================

function SubLinks($id, $type){
	global $paging;
	//echo "$paging $id $type";
	if($paging=='plan'){
		$temp=array('notice board','anniversaries','bdays','bashes','others','view calender');
		$sublinks="<div class='sublinks'>";
		for($i=0;$i<count($temp);$i++){
			if($id==-1 && $i==5) continue;
			if($id==$i) $sublinks.="<span>".$temp[$i]."</span>";
			else $sublinks.="<a href='javascript:;' onClick='getEvents($i);'>".$temp[$i]."</a>";
		}
		$sublinks.="</div>";
	}
	elseif($paging=='contacts'){
		$temp=array('telephones','emails','sites n blogs','messengers','addresses');
		$sublinks="<div class='sublinks'>all: ";
		for($i=0;$i<count($temp);$i++){
			if($id==$i) $sublinks.="<span>".$temp[$i]."</span>";
			else $sublinks.="<a href='javascript:;' onClick='getContacts(1{$i});'>".$temp[$i]."</a>";
		}
		$sublinks.="</div>";

		$temp=array('as list','as cards');
		$sublinks.="<div class='sublinks' style='margin-bottom: 3px;'>view: ";
		for($i=0;$i<count($temp);$i++){
			if($temp[$i]=="as $type") $sublinks.="<span>".$temp[$i]."</span>";
			else $sublinks.="<a href='javascript:;' onClick='getContacts($i);'>".$temp[$i]."</a>";
		}
		$sublinks.="</div>";
	}
	else{
		$sublinks='';
	}
	return $sublinks;
}
//================================================================================================================================

function Contacts($view, $which){
	$sublinks="<div id='all_sublinks'>".SubLinks($which,$view)."</div>";		//leave the divs dere. ajax wont work if removed
	$addcontact=AddContacts();
	$contacts=PopulateContacts($view,$which);

	$contents=<<<CONTENTS
	<div id='bone'>
	$contacts
	</div>
	$addcontact
	<script>setType($which); setView('$view');</script>
CONTENTS;
	return ProtoType($contents,8,false,$sublinks);
}
//================================================================================================================================

function PopulateContacts($type,$which){
	//type--list or cards, which--0-tel, 1-emails,2-sites n blogs, 3-messengers, 4-addresses
	if($type=='list'){
		$width="width: 780px;";
		$margin="margin: 0px;";
		$data=ListContacts($which);
	}else{
		$width="width: 780px;";
		$margin="margin: 0px;";
		$data=CardContacts($which, 0);
	}
	$contents=<<<CONTENTS
<div id='contacts' style="$width $margin">
	$data
</div>
CONTENTS;
	return $contents;
}
//================================================================================================================================

function ListContacts($which){
	switch($which){
		case 0:
			$cols=array('name','mobile 1','mobile 2','mobile 3','office 1','office 2','home 1','home 2');
			$query="SELECT b.nick, b.onames, a.mobile1, a.mobile2, a.mobile3, a.office1, a.office2, a.home1, a.home2 "
			."FROM telephones AS a INNER JOIN users AS b ON a.user_id=b.id";
			$perc='13%';
			break;
		case 1:
			$perc='';
			$cols=array('name','personal1','personal2','personal3','office1','office2','office3');
			$query="SELECT b.nick, b.onames, a.personal1, a.personal2, a.personal3, a.office1, a.office2, a.office3 "
			."FROM emails_websites AS a INNER JOIN users AS b ON a.user_id=b.id";
			break;
		case 2:
			$perc='';
			$cols=array('name','personal site','office site','blog');
			$query="SELECT b.nick, b.onames, a.per_page, a.off_page, a.blog "
			."FROM emails_websites AS a INNER JOIN users AS b ON a.user_id=b.id";
			break;
		case 3:
			$cols=array('name','gmail','yahoo','hotmail','facebook','aol','other 1','other 2','other 3');
			$query="SELECT b.nick, b.onames, a.gmail, a.yahoo, a.hotmail, a.facebook, a.aol, a.other1, a.other2, a.other3 "
			."FROM ims AS a INNER JOIN users AS b ON a.user_id=b.id";
			$perc='11.3%';
			break;
		case 4:
			return CardContacts(4,0);
			break;
	}
	$contents="<table width='100%' border=0 align='center'><tr>";
	foreach($cols as $temp) $contents.="<th>$temp</th>";
	$contents.="</tr>";
	$results=GetQueryValues($query,MYSQL_NUM);
	if(is_string($results)) return array(true,$results);
	elseif(count($results)==0) return array(false,"There are no records for this data.");
	for($i=0;$i<count($results);$i++){
		$temp=$results[$i];
		$clas=(($i%2)==0)?'even':'odd';
		$contents.="\n<tr class='$clas'>";
		//echo count($temp);
		for($j=0;$j<count($temp);$j++){
			$tempval=$temp[$j];
			if($j==0){
				if($tempval!='none') $contents.="<td>$tempval</td>";
				else $contents.="<td width='8%;'>".$temp[1]."</td>";
				$j++; continue;
			}
			$tempval=($tempval=='')?'undefined':$tempval;
			$contents.="<td width='$perc'>$tempval</td>";
		}
		$contents.="</tr>";
	}
	$contents.="</table>";
	return $contents;
}
//================================================================================================================================

function CardContacts($which, $subwhich){
	switch($which){
		case 0:
			if($subwhich==0){$query="SELECT b.nick, b.onames, a.mobile1, a.mobile2, a.mobile3 "; $cols=array('mob. 1','mob. 2','mob. 3');}
			elseif($subwhich==1){$query="SELECT b.nick, b.onames, a.office1, a.office2, a.office3 "; $cols=array('off. 1','off. 2','off. 3');}
			else{$query="SELECT b.nick, b.onames, a.home1, a.home2, a.home3 "; $cols=array('home 1','home 2','home 3');}
			$query.="FROM telephones AS a INNER JOIN users AS b ON a.user_id=b.id";
			break;
		case 1:
			if($subwhich==0){$query="SELECT b.nick, b.onames, a.personal1, a.personal2, a.personal3 ";  $cols=array('per. 1','per. 2','per. 3');}
			elseif($subwhich==1){$query="SELECT b.nick, b.onames, a.office1, a.office2, a.office3 "; $cols=array('off. 1','off. 2','off. 3');}
			$query.="FROM emails_websites AS a INNER JOIN users AS b ON a.user_id=b.id";
			break;
		case 2:
			$query="SELECT b.nick, b.onames, a.per_page, a.off_page, a.blog "
			."FROM emails_websites AS a INNER JOIN users AS b ON a.user_id=b.id";
			$cols=array('per.','off.','blog');
			break;
		case 3:
			$query="SELECT b.nick, b.onames, a.gmail, a.yahoo, a.hotmail, a.facebook, a.aol, a.other1, a.other2, a.other3 "
			."FROM ims AS a INNER JOIN users AS b ON a.user_id=b.id";
			$cols=array('name','gmail','yahoo','hotmail','facebook','aol','other 1','other 2','other 3');
			break;
		case 4:
			$query="SELECT b.nick, b.onames, a.address FROM telephones AS a INNER JOIN users AS b ON a.user_id=b.id";
			break;
	}
	$results=GetQueryValues($query,MYSQL_NUM);
	if(is_string($results)) return array(true,$results);
	elseif(count($results)==0) return array(false,"There are no records for this data.");
	$contents="<table width='100%' border=0 align='center'>";
	if($which<2){
		//create a small header
		if($which==0){
			$links=($subwhich==0)?"<span>mobile</span>&nbsp;&nbsp;":"<a href='javascript:;' onClick=''>mobile</a>&nbsp;&nbsp;";
			$links.=($subwhich==1)?"<span>office</span>&nbsp;&nbsp;":"<a href='javascript:;' onClick=''>office</a>&nbsp;&nbsp;";
			$links.=($subwhich==2)?"<span>home</span>&nbsp;&nbsp;":"<a href='javascript:;' onClick=''>home</a>&nbsp;&nbsp;";
		}
		else{
			$links=($subwhich==0)?"<span>personal</span>&nbsp;&nbsp;":"<a href='javascript:;' onClick=''>personal</a>&nbsp;&nbsp;";
			$links.=($subwhich==1)?"<span>office</span>&nbsp;&nbsp;":"<a href='javascript:;' onClick=''>office</a>&nbsp;&nbsp;";
		}
		$contents.="<tr><th colspan='5' align='center'>$links</th></tr>";
	}
	for($i=0;$i<count($results);$i++){
		$temp=$results[$i];
		$caption=($temp[0]!='none')?$temp[0]:$temp[1];
		if($i%5==0) $contents.="<tr>";
		if($which!=4){
			$temp1=($temp[2]=='')?'undefined':$temp[2];
			$temp2=($temp[3]=='')?'undefined':$temp[3];
			$temp3=($temp[4]=='')?'undefined':$temp[4];

			$contents.="<td><div id='contact_card'><table width='100%'>"
			."<th colspan='2' >$caption</th>"
			."<tr><td align='right' width='45%'>".$cols[0]."</td><td width='60%'>$temp1</td></tr>"
			."<tr><td align='right'>".$cols[1]."</td><td>$temp2</td></tr>"
			."<tr><td align='right'>".$cols[2]."</td><td>$temp3</td></tr>"
			."</table></div></td>";
		}
		else{
			$temp1=($temp[2]=='')?'undefined':$temp[2];
			$contents.="<td><div id='contact_card'><table width='100%'>"
			."<th colspan='2' >$caption</th>"
			."<tr><td>$temp1</td></tr></table></div></td>";
		}
		if($i%5==4) $contents.="</tr>";
	}
	$j=$i%5;
	if($j!=0){
		//padd the remaining divs
		for($i=$j;$i<5;$i++) $contents.="<td><div id='contact_empty'>&nbsp;</div></td>";
		$contents.="</tr>";
	}
	$contents.="</table>";
	return $contents;
}
//================================================================================================================================

function AddContacts(){
	global $pageref, $pageref1;

	$contents=<<<CONTENTS
<div id='events' style='margin-left: 180px;'>
<span style='float:right; margin: 10px 50px 5px 0px; font-size: 13px;'><a href='javascript:showHide("addevent");'>show/hide add contact</a></span>
<div id='addevent' class='collapsed' style='width: 500px;'>
	<div id='errmessageid' class='normal' align='center'>enter contact information.
		<input type='radio' name='whose' id='owner' value='mine' checked>mine&nbsp;&nbsp;<input type='radio' name='whose' id='owner' value='other'>sm1 else's
	</div>

	<form method='POST' action="$pageref?$pageref1" name='addingcontact'>

	<div id='data'>
		<label id='sname' class='norm'>surname</label><input type='text' name='sname' id='snameid' size='10' value=''>
		<label id='fname' class='norm'>first name</label><input type='text' name='fname' id='fnameid' size='10' value=''>
		<label id='onames' class='norm'>other names</label><input type='text' name='onames' id='onamesid' size='11' value=''>
	</div>

	<div id='tabs'>
		&nbsp;
	</div>

	<div id='tabcontent'>
		&nbsp;
	</div>
	<div id='links'><a href='javascript:postContact();'>post</a><a href='javascript:;'>cancel</a></div>
	<input type='hidden' id='flagid' name='flag' value=''>
	</form>
</div></div>
CONTENTS;
	return $contents;
}
//================================================================================================================================

function Pictures(){
	$contents=<<<CONTENTS
CONTENTS;
	return $contents;
}
//================================================================================================================================

function Videos(){
	$contents=<<<CONTENTS
CONTENTS;
	return $contents;
}
//================================================================================================================================

function DontForget(){
	$contents=<<<CONTENTS
CONTENTS;
	return $contents;
}
//================================================================================================================================

function Settings(){
	$contents=<<<CONTENTS
CONTENTS;
	return $contents;
}
//================================================================================================================================

function ExtraInfo(){
	$contents=<<<CONTENTS
	<div id='sideinfo'>
		<span>xtra info is pasted here</span>
	</div>
CONTENTS;
	return $contents;
}
//================================================================================================================================

function SideLinks(){
	$contents=<<<CONTENTS
<div id='sidelinks'>
		<span>side links</span>
		<span>go here</span>
	</div>
CONTENTS;
	return $contents;
}
//================================================================================================================================
//populates a combo box
//items(array)--e caption 2 display; values(array)-e values tied wit items; defvalue(char)--e 1st item; name(char)--e name of e combo
//selected(int)--e currently selected item; enabled(bool)--is it enabled;changewat(bool)--whether to call e submit function on change of item
function Populate_Combo($items,$values,$defval,$name,$selected,$enabled,$changewat){
	reset($items);reset($values);
	($enabled)?$dis="":$dis="disabled";
	$change=($changewat!=''  && isset($changewat))?"onChange=\"clickin(form,'".$changewat."');submitme(form)\"":'';
	(!isset($selected))?$selected=0:$selected;
	for($i=0;$i<count($items)+1;$i++){
		if($i==0){
			$combo="<select name='$name' id='{$name}id' $dis $change>\n\t\t\t<option value='0'";
			($selected==$i)?$combo.=" selected>":$combo.=">";
			$combo.=$defval;
		}else{
			$combo.="<option value='".current($values)."'";
			($selected==current($values))?$combo.=" selected>":$combo.=">";
			$combo .= current($items);
			next($items);next($values);
		}
	}
	$combo.="\n\t\t</select>";
	return $combo;
}
//===================================================================================================================================

//checks for compatibility of fields. It does all the work. dependin on key checks out specific fields
function Checks($input,$key){
	//correspondin fields: 0-id/passport no, 1-surname/onames, 2-tel, 3-receipt no, 4-announceid, 5-message,
	//6-any combo
	$input=trim($input);
	switch($key){
		case 0:
			//id format:12345678, pass format:A123456/7
			$span_str='0123456789';
			if(eregi('^A[0-9]{6,7}$',$input) || strspn($input,$span_str)==8)
			return 0;   //atleast a match is found
			return 1;   //no match
			break;

		case 1:

			break;

		case 2:
			//format: 07 12123456 or 2547 12123456 or 020 1234567 or 254 20 1234567
			if(strlen($input)!=10 && strlen($input)!=12)
			return 1;   //lengths dont match
			if(eregi('^07[0-9]{8}$',$input))
			$subinput=substr($input,4,6);
			elseif(eregi('^2547[0-9]{8}$',$input))
			$subinput=substr($input,6,6);
			elseif(eregi('^25420[0-9]{7}$',$input))
			$subinput=substr($input,5,7);
			elseif(eregi('^020[0-9]{7}$',$input))
			$subinput=substr($input,3,7);
			else
			return 1;     //no match found so its error
			break;

		case 3:
			//format:AB12345
			if(!eregi('^[A-Z]{2}[0-9]{5}$',$input))
			return 1;
			return 0;
			break;

		case 4:
			//format:AB.12345.DD.MM.YYYY
			if(!eregi('^[A-Z]{2}\\.[0-9]{5}\\.[0-9]{2}\\.[0-9]{2}\\.[0-9]{4}$',$input))
			return 1;
			return 0;
			break;

		case 5:
			//shldnt contain 'href', 'script', <, >, *, ;.
			if($input=="")
			return 1;
			$span_str="<>*;";
			if(strspn($input,$span_str)==1)
			return 1;   //a name mst be at least 3 letters
			return 0;
			break;

		case 6:
			//index shldnt be 0
			if($input==0)
			return 1;
			return 0;
			break;

		//shld contain only chars,n '
		case 7:
			$span_str="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-_'.? ";
			if(strlen($input)==0)
			return 1;
			$input=stripslashes($input);
			if(strspn($input,$span_str)!=strlen($input))
			return 1;   //there are some of bad chars
			//echo 'all is well<br>';
			return 0;      //all is ok
			break;

		//ints only
		case 8:
			$span_str="0123456789";
			if(strspn($input,$span_str)!=strlen($input))
			return 1;
			return 0;
			break;

		//email
		case 9:
			//format: xxxxx@xxxx.xxx
			//'^[A-Z]{2}\\.[0-9]{5}\\.[0-9]{2}\\.[0-9]{2}\\.[0-9]{4}$'
			return (!eregi('^[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+@'.
						'[-!#$%&\'*+\\/0-9=?A-Z^_`a-z{|}~]+\.[A-Za-z]+$',$input));
			break;

		//illegal chars to refuse -- allows igbo characters to be present in the input.
		case 11:
			$span_str="!\"#$%&`()*+/0123456789:;<=>?@[\\]^{|}~";
			if (strspn($input,$span_str))		//if we have even one of the above trigger an error
			return 1;
			return 0;
			break;

		//check for illegal names
		case 12:
			if (eregi("^((root)|(bin)|(daemon)|(adm)|(lp)|(sync)|(shutdown)|
				(halt)|(mail)|(news)|(uucp)|(operator)|(games)|(mysql)|(href)|
				(httpd)|(nobody)|(dummy)|(www)|(cvs)|(shell)|(ftp)|(irc)|(script)|
				(debian)|(ns)|(download))$", $input)) {
				return 1;
			}
			if (eregi("^(anoncvs_)", $input))
			return 1;
			return 0;
			break;

		default:
			break;
}
}
//================================================================================================================================

?>