<?php
/**
 * This is the worker who is never recognised. Includes all the necessary files. Initializes a session if need be. Processes the main GET or POST
 * elements and includes necessary files. Calls the necessary functions/methods
 * 
 * @author Kihara Absolomon <soloincc@movert.co.ke>
 * @since v0.1
 */
define('OPTIONS_COMMON_FOLDER_PATH', '/var/www/common/');

require_once OPTIONS_COMMON_FOLDER_PATH.'mod_general_v0.3.php';
require_once 'kims_config';
require_once OPTIONS_COMMON_FOLDER_PATH.'mod_objectbased_dbase_v0.6.php';
require_once 'mod_kims_general.php';

$Kims = new KimsGeneral();

//lets initiate the sessions
session_save_path($Kims->config['session_dbase']);
session_name('kims');
$Kims->SessionStart();

//get what the user wants
$server_name=$_SERVER['SERVER_NAME'];
$queryString=$_SERVER['QUERY_STRING'];
$paging = (isset($_GET['page']) && $_GET['page']!='') ? $_GET['page'] : '';
$action = (isset($_GET['do']) && $_GET['do']!='') ? $_GET['do'] : '';
$alt_action = (isset($_POST['flag']) && $_POST['flag']!='') ? $_POST['flag'] : '';


define('OPTIONS_HOME_PAGE', $_SERVER['PHP_SELF']);
define('OPTIONS_REQUESTED_MODULE', $paging);
/**
 * @var string    What the user wants
 */
define('OPTIONS_REQUESTED_SUB_MODULE', $action);
define('OPTIONS_REQUESTED_ACTION', $alt_action);
$t = pathinfo($_SERVER['SCRIPT_FILENAME']);
$request_type = ($t['basename']=='mod_ajax_calls.php')?'ajax':'normal';
define('OPTIONS_REQUESTED_TYPE', $request_type);

//messages
define('OPTIONS_MSSG_LOGIN_ERROR', '<i>Invalid username or password, please try again.<br> If your log in details are correct, you may not have sufficient rights to access the system.<br> Please contact the System Administrator.</i>');
define('OPTIONS_MSSG_FETCH_ERROR', "Well this is embarassing! There was an error while fetching data from the %s table.$contact");
define('OPTIONS_MSSG_SAVE_ERROR', "Ooops! There was an error while saving data to the %s table.$contact");
define('OPTIONS_MSSG_DELETE_ERROR', "There was an error while deleting the entry from the %s table.$contact");
define('OPTIONS_MSSG_INVALID_NAME', "Error! Please enter a valid %s.");
define('OPTIONS_MSSG_INVALID_VARIABLE', "Error! You have input an invalid value for '%s'. Epecting a(an) %s{$contact}");
define('OPTIONS_MSSG_CREATE_DIR_ERROR', "There was an error while creating the %s directory.$contact");
define('OPTIONS_MSSG_CREATE_FILE_ERROR', "There was an error while creating the %s file.$contact");
define('OPTIONS_MSSG_MISSING_FOLDER', "The %s folder does not exists.$contact");
define('OPTIONS_MSSG_FILE_WRITE_ERROR', "There was an error while saving the data to the %s file.$contact");
define('OPTIONS_MSSG_USERREPLY_SYSTEM_ERROR','Well this is embarassing! The system is currently experiencing some problems.');

$Kims->TrafficController();
?>