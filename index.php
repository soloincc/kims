<html>
	<head>
		<title>Kimemias Personal Page</title>
      <link rel='stylesheet' type='text/css' href='css/alertbox.css'>
      <link rel='stylesheet' type='text/css' href='css/kims.css'>
      <script type='text/javascript' src='../common/jquery-1.6.1.min.js'></script>
      <script type='text/javascript' src='js/kims.js'></script>
      <script type='text/javascript' src='js/alertbox.js'></script>
      <script type='text/javascript' src='../common/common.js'></script>
      <?php
         if(OPTIONS_REQUESTED_MODULE == 'plan') echo "<script type='text/javascript' src='js/planner.js'></script>";
         elseif(OPTIONS_REQUESTED_MODULE == 'contacts') echo "<script type='text/javascript' src='js/contacts.js'></script>";
      ?>
	</head>
	<body onLoad='Kims.init();'>
		<div id="wrapper">
         <?php require_once 'modules/mod_startup.php'; ?>
		</div>
	</body>
</html>