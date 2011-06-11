<?php
/**
 * The main module for the kims system
 *
 * @category   KIMS
 * @package    General
 * @author     Kihara Absolomon <soloincc@movert.co.ke>
 * @since      v0.1
 */
class KimsGeneral extends DBase {

   /**
    * @var Object An object with the database functions and properties. Implemented here to avoid having a million & 1 database connections
    */
   public $Dbase;

   public $addinfo;

   public $links;

   public $mandatorySessionData = array('username', 'password', 'project', 'surname', 'onames', 'user_level');

   /**
    * @var  string   Just a string to show who is logged in
    */
   public $whoisme = '';

   public function  __construct() {
      //this looks so ugly...bt so far thats what I gat
      $this->Dbase = new DBase();
      if($this->Dbase->dbcon->connect_error || (isset($this->Dbase->dbcon->errno) && $this->Dbase->dbcon->errno!=0)) {
         die('Something wicked happened when connecting to the dbase.');
      }
      if(isset($this->Dbase)) {
//         echo '<pre>I am called again'.print_r($this, true).'</pre>';
         $this->Dbase->InitializeConnection();
         $this->Dbase->InitializeLogs();
      }
   }
   
   public function TrafficController(){
//      echo '<pre>'.print_r($_POST, true).'</pre>';
//      echo '<pre>'.print_r($_GET, true).'</pre>';
      if(OPTIONS_REQUESTED_MODULE == '' && OPTIONS_REQUESTED_SUB_MODULE == '') $this->LoginPage();
      elseif(OPTIONS_REQUESTED_MODULE == 'login') $this->ProcessLogin();
      elseif(OPTIONS_REQUESTED_MODULE == 'contacts') $this->ContactsPage('list',0);
   }
   
   /**
    * Creates the login page for the system
    * 
    * @param   string   $message    Any additional message that might need to be displayed on the home page
    */
   private function LoginPage($message = '', $username = ''){
?>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
	<td width=''>&nbsp;</td>
	 <td width="800" id='overall'>
		<div id='header'>kims personal page</div>
			<div id='login'>
            <form method='POST' action="?page=login" name='form'>
               <div><label>Username</label>&nbsp;&nbsp;<input type='text' name='username' size='20' /></div>
               <div><label>Password</label>&nbsp;&nbsp;&nbsp;&nbsp;<input type='password' name='pass' size='15' /></div>
               <?php echo $message; ?>
               <div style='float: left; padding-left: 80px;'><input class='en_button' type='submit' name='authenticate' value='Login'></div>
               <div style='float: left;'><input class='en_button' type='button' value='Cancel' onClick="alert('i am not yet set');"></div>
               <input type='hidden' name='flag' id='flagid' value='' />
            </form>
			</div>
	</td>
	<td width=''>&nbsp;</td>
  </tr>
 </table>
<?php
   }
   
   private function ProcessLogin(){
      //we should be having the username and passwords
      $username = $_POST['username'];
      $pass = $_POST['pass'];
      if($username == '' || $pass == ''){
         $message = '<i>Invalid username or password, please try again.</i>';
         $this->LoginPage($message, $username);
         $this->footerlinks = '';
      }
      else{    //we need to do the basic checks
         $res = $this->Dbase->Authenticate($username, $pass);
         if(is_string($res))
            $this->LoginPage("<i>$res</i>");
         elseif($res == 1)
            $this->LoginPage(OPTIONS_MSSG_LOGIN_ERROR);
         elseif($res == 0){   //we are in, lets get the other details
            $res = $this->FetchUserCredentials($username);
            if($res){
               $message = "<i>{$this->Dbase->lastError}</i>";
               $this->LoginPage($message, $username);
               $this->footerlinks = '';
            }
            else{
               
               $this->Home();
            }
//         echo '<pre>'.print_r($_SESSION, true).'</pre>';
         }
      }
   }
   
   private function Home($id = 0){
      $links = $this->CreateLinks($id);
?>
<table width="90%" border="0" cellspacing="0" cellpadding="0" align='center'>
  <tr><td>&nbsp;</td>
	 <td width="800">
		<div id='header'>kims personal page</div>
      <?php echo $links; ?>
		<div id='content'>
         <div id='whoisme'><?php echo "{$_SESSION['surname']} {$_SESSION['onames']}, {$_SESSION['user_level']}"; ?>&nbsp;&nbsp;<a href='?page=logout'>Log Out</a></div>
         <br />
         <div id='sidelinks'>
            <span>side links</span><br />
            <span>go here</span>
         </div>
         <div id='bone'>Biography</div>
         <div id='sideinfo'>
            <span>xtra info is pasted here</span>
         </div>
      </div>
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
<?php
   }
   
   private function CreateLinks($id){
	$links = array(
       'mypage' => 'mypage',
       'docs' => 'docs',
       'projs' => 'projects',
       'wassup' => 'wats up',
       'settings' => 'hse keepin',
       'tree' => 'family tree',
       'hepi' => 'wats happenin',
       'plan' => 'planner',
       'contacts' => 'contacts',
       'pics' => 'pics',
       'videos' => 'videos',
       'usisahau' => 'dont forget'
    );
	$links=array('my page','docs','projects','whats up', 'hse keepin','family tree','wats happenin','planner','contacts','pics','videos','dont forget');
	$actions=array('mypage','docs','projs','wassup','settings','tree','hepi','plan','contacts','pics','videos','usisahau');
	$details="<div id='links'>";
	for($i=0;$i<5;$i++) $details .= ($id==$i)?"<span class='currentlink'>".$links[$i]."</span>\n" : "<a href='$pageref?page=".$actions[$i]."'>".$links[$i]."</a>\n";
	$details.="</div><div id='links'>";
	for($i=5;$i<12;$i++) $details .= ($id==$i)?"<span class='currentlink'>".$links[$i]."</span>\n" : "<a href='$pageref?page=".$actions[$i]."'>".$links[$i]."</a>\n";
	$details.="</div>";

	return $details;
}/**
    * Fetches the user details from the database. This function has been carved out of @see Dbase#ConfirmUser. Should only be called after calling @see Dbase#ConfirmUser
    * 
    * @param   string   $username   The username whose additional details we want to fetch
    * @return  integer  Returns 0 when all is well, or 1 in case there was an error
    * @since   v0.1
    */
   public function FetchUserCredentials($username){
      if($username == ''){
         $this->Dbase->lastError = "There was an error while fetching data from the session database.<br />Please try again later.";
         return 1;
      }
      $username = $this->Dbase->dbcon->real_escape_string($username);
      $this->Dbase->query = "select sname, onames, email from users where login = '$username'";

      $result = $this->Dbase->ExecuteQuery(MYSQL_ASSOC);
//      echo '<pre>'.print_r($result, true).'</pre>';
      if($result == 1){
         $this->Dbase->CreateLogEntry("There was an error while fetching data from the database.", 'fatal', true);
         $this->Dbase->lastError = "There was an error while fetching data from the session database.<br />Please try again later.";
         return 1;
      }

      if(count($result) != 1){
         $this->Dbase->CreateLogEntry("There are multiple users with '$username' as login username.", 'fatal');
         $this->Dbase->lastError = "There was a fatal error while logging into the system.<br />{$this->contact}";
         return 1;
      }

      $userData = $result[0];
      //we ok, now initialize the session data
      $_SESSION['surname'] = $userData['sname']; $_SESSION['onames'] = $userData['onames']; $_SESSION['username'] = $username;
      $_SESSION['user_level'] = $userData['user_level'];
      return 0;
   }
   
   private function ContactsPage($view = '', $which = '', $id = 0){
	$sublinks = "<div id='all_sublinks'>".$this->SubLinks($which,$view)."</div>";		//leave the divs dere. ajax wont work if removed
   $links = $this->CreateLinks($id);
	$contacts = $this->PopulateContacts($view, $which);
?>
<script type='text/javascript' src='js/contacts.js'></script>
<table width="90%" border="0" cellspacing="0" cellpadding="0" align='center'>
  <tr><td>&nbsp;</td>
	 <td width="800">
		<div id='header'>kims personal page</div>
      <?php echo $links; ?>
		<div id='content'>
   <div id='bone'>
      <div id='events' style='margin-left: 180px;'>
         <span style='float:right; margin: 10px 50px 5px 0px; font-size: 13px;'><a href='javascript:showHide("addevent");'>show/hide add contact</a></span>
         <div id='addevent'>
            <div id='errmessageid' class='normal' align='center'>enter contact information.
               <input type='radio' name='whose' id='owner' value='mine' checked>mine&nbsp;&nbsp;<input type='radio' name='whose' id='owner' value='other'>sm1 else's
            </div>
            
            <form method='POST' action="?page=contacts" name='addingcontact'>
               <div id='data'>
                  <label id='sname' class='norm'>surname</label><input type='text' name='sname' id='snameid' size='10' value=''>
                  <label id='fname' class='norm'>first name</label><input type='text' name='fname' id='fnameid' size='10' value=''>
                  <label id='onames' class='norm'>other names</label><input type='text' name='onames' id='onamesid' size='11' value=''>
               </div>
               <div id='tabs'>&nbsp;</div>
               <div id='tabcontent'>&nbsp;</div>
               <div id='links'><a href='javascript:postContact();'>post</a><a href='javascript:;'>cancel</a></div>
               <input type='hidden' id='flagid' name='flag' value=''>
            </form>
         </div>
      </div>
      <script type='text/javascript'>
         Contacts.setType(<?php echo $which; ?>);
         Contacts.setView('<?php echo $view; ?>');
      </script>
   </div></div>
	</td>
	<td>&nbsp;</td></tr>
	<tr><td>&nbsp;</td><td>
		<div id='footer'>
			<span class='footerlinks' style='text-decoration: none;'>&copy; kims personal page</span>
			<a href='http://soloincc.movert.co.ke' target='_blank' class='footerlinks'>about the developer</a>
			<a href='javascript:;' class='footerlinks'>about us</a>
		</div>
	</td><td>&nbsp;</td></tr>
  </table>
<?php
   }
   
   private function SubLinks($id, $type){
      if(OPTIONS_REQUESTED_MODULE == 'plan'){
         $temp=array('notice board','anniversaries','bdays','bashes','others','view calender');
         $sublinks="<div class='sublinks'>";
         for($i=0;$i<count($temp);$i++){
            if($id==-1 && $i==5) continue;
            if($id==$i) $sublinks.="<span>".$temp[$i]."</span>";
            else $sublinks.="<a href='javascript:;' onClick='getEvents($i);'>".$temp[$i]."</a>";
         }
         $sublinks.="</div>";
      }
      elseif(OPTIONS_REQUESTED_MODULE == 'contacts'){
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
   
   private function PopulateContacts($type,$which){
      //type--list or cards, which--0-tel, 1-emails,2-sites n blogs, 3-messengers, 4-addresses
      if($type=='list'){
         $width="width: 780px;";
         $margin="margin: 0px;";
         $data = $this->ListContacts($which);
      }else{
         $width="width: 780px;";
         $margin="margin: 0px;";
         $data = $this->CardContacts($which, 0);
      }
$contents=<<<CONTENTS
   <div id='contacts' style="$width $margin">
      $data
   </div>
CONTENTS;
      return $contents;
   }
   
   private function ListContacts($which){
      switch($which){
         case 0:
            $cols=array('name','mobile 1','mobile 2','mobile 3','office 1','office 2','home 1','home 2');
            $this->Dbase->query="SELECT b.login, b.onames, a.mobile1, a.mobile2, a.mobile3, a.office1, a.office2, a.home1, a.home2 "
            ."FROM telephones AS a INNER JOIN users AS b ON a.user_id=b.id";
            $perc='13%';
            break;
         case 1:
            $perc='';
            $cols=array('name','personal1','personal2','personal3','office1','office2','office3');
            $this->Dbase->query="SELECT b.login, b.onames, a.personal1, a.personal2, a.personal3, a.office1, a.office2, a.office3 "
            ."FROM emails_websites AS a INNER JOIN users AS b ON a.user_id=b.id";
            break;
         case 2:
            $perc='';
            $cols=array('name','personal site','office site','blog');
            $this->Dbase->query="SELECT b.login, b.onames, a.per_page, a.off_page, a.blog "
            ."FROM emails_websites AS a INNER JOIN users AS b ON a.user_id=b.id";
            break;
         case 3:
            $cols=array('name','gmail','yahoo','hotmail','facebook','aol','other 1','other 2','other 3');
            $this->Dbase->query="SELECT b.login, b.onames, a.gmail, a.yahoo, a.hotmail, a.facebook, a.aol, a.other1, a.other2, a.other3 "
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
      $results=$this->Dbase->ExecuteQuery(MYSQLI_NUM);
      if($results == 1) return array(true, $this->Dbase->lastError);
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

   private function CardContacts($which, $subwhich){
      switch($which){
         case 0:
            if($subwhich == 0){
               $this->Dbase->query = "SELECT b.login, b.onames, a.mobile1, a.mobile2, a.mobile3 ";
               $cols = array('mob. 1', 'mob. 2', 'mob. 3');
            }
            elseif($subwhich == 1){
               $this->Dbase->query = "SELECT b.login, b.onames, a.office1, a.office2, a.office3 ";
               $cols = array('off. 1', 'off. 2', 'off. 3');
            }
            else{
               $this->Dbase->query = "SELECT b.login, b.onames, a.home1, a.home2, a.home3 ";
               $cols = array('home 1', 'home 2', 'home 3');
            }
            $this->Dbase->query.="FROM telephones AS a INNER JOIN users AS b ON a.user_id=b.id";
            break;
         case 1:
            if($subwhich == 0){
               $this->Dbase->query = "SELECT b.login, b.onames, a.personal1, a.personal2, a.personal3 ";
               $cols = array('per. 1', 'per. 2', 'per. 3');
            }
            elseif($subwhich == 1){
               $this->Dbase->query = "SELECT b.login, b.onames, a.office1, a.office2, a.office3 ";
               $cols = array('off. 1', 'off. 2', 'off. 3');
            }
            $this->Dbase->query.="FROM emails_websites AS a INNER JOIN users AS b ON a.user_id=b.id";
            break;
         case 2:
            $this->Dbase->query  = "SELECT b.login, b.onames, a.per_page, a.off_page, a.blog "
                    . "FROM emails_websites AS a INNER JOIN users AS b ON a.user_id=b.id";
            $cols = array('per.', 'off.', 'blog');
            break;
         case 3:
            $this->Dbase->query  = "SELECT b.login, b.onames, a.gmail, a.yahoo, a.hotmail, a.facebook, a.aol, a.other1, a.other2, a.other3 "
                    . "FROM ims AS a INNER JOIN users AS b ON a.user_id=b.id";
            $cols = array('name', 'gmail', 'yahoo', 'hotmail', 'facebook', 'aol', 'other 1', 'other 2', 'other 3');
            break;
         case 4:
            $this->Dbase->query="SELECT b.login, b.onames, a.address FROM telephones AS a INNER JOIN users AS b ON a.user_id=b.id";
            break;
      }
      $results = $this->Dbase->ExecuteQuery(MYSQLI_NUM);
      if($results == 1) return array(true, $this->lastError);
      elseif(count($results)==0) return array(false,"There are no records for this data.");
      $contents="<table width='100%' border=0 align='center'>";
      if($which<2){
         //create a small header
         if($which==0){
            $links = ($subwhich == 0) ? "<span>mobile</span>&nbsp;&nbsp;" : "<a href='javascript:;' onClick=''>mobile</a>&nbsp;&nbsp;";
            $links.= ( $subwhich == 1) ? "<span>office</span>&nbsp;&nbsp;" : "<a href='javascript:;' onClick=''>office</a>&nbsp;&nbsp;";
            $links.= ( $subwhich == 2) ? "<span>home</span>&nbsp;&nbsp;" : "<a href='javascript:;' onClick=''>home</a>&nbsp;&nbsp;";
         }
         else{
            $links =  ($subwhich == 0) ? "<span>personal</span>&nbsp;&nbsp;" : "<a href='javascript:;' onClick=''>personal</a>&nbsp;&nbsp;";
            $links.= ( $subwhich == 1) ? "<span>office</span>&nbsp;&nbsp;" : "<a href='javascript:;' onClick=''>office</a>&nbsp;&nbsp;";
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
}
?>
