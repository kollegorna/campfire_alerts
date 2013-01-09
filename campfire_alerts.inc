<?php 

define('CAMPFIRE_ALERTS_URL', getenv('CAMPFIRE_ALERTS_URL')); // Use full URL, http://[account].campfirenow.com
define('CAMPFIRE_ALERTS_AUTHTOKEN', getenv('CAMPFIRE_ALERTS_AUTHTOKEN')); 
define('CAMPFIRE_ALERTS_ROOM_ID', getenv('CAMPFIRE_ALERTS_ROOM_ID')); // To get room_id, login to your CF room and look in the address bar (after /room)

function campfire_alerts_run() {

  watchdog('Campfire Alerts!', 'Checking...');
  $errors = array();
  campfire_alerts_check_cache($errors);
  campfire_alerts_check_css_preprocessning($errors);
  campfire_alerts_check_js_preprocessing($errors);
  campfire_alerts_check_error_reporting($errors);

  if (!empty($errors)) {
    campfire_alerts_campfire_post("Hey! Problems on " . variable_get('site_name', 'Mysteriously unnamed site') . ":");
    foreach ($errors as $error) {
      campfire_alerts_campfire_post($error);
      watchdog('Campfire Alerts!', $error);
    }
    campfire_alerts_campfire_post('horror', 'SoundMessage');
  }
  else watchdog('Campfire Alerts!', 'All is well!');
}

function campfire_alerts_check_cache(&$errors) {
  $msg = "Caching is turned off!";
  if (!variable_get('cache', NULL)) {
    $errors[] = $msg;
  }
}
function campfire_alerts_check_css_preprocessning(&$errors) {
  $msg = "CSS optimization is turned off!";
  if (!variable_get('preprocess_css', NULL)) {
    $errors[] = $msg;
  }
}

function campfire_alerts_check_js_preprocessing(&$errors) {
  $msg = "JavaScript optimization is turned off!";
  if (!variable_get('preprocess_js', NULL)) {
    $errors[] = $msg;
  }
}

function campfire_alerts_check_error_reporting(&$errors) {
  $msg = "Error reporting is misconfigured, errors will be visible to users!";
  if (variable_get('error_level', NULL) == 1) {
    $errors[] = $msg;
  }
}

function campfire_alerts_campfire_post($message, $type = 'TextMessage') {
  $data = array(
    'message' => array (
      'body' => $message,
      'type' => $type,
    ),
  );
  $url = CAMPFIRE_ALERTS_URL . '/room/' . CAMPFIRE_ALERTS_ROOM_ID . '/speak.json';
  $json = json_encode($data);

  // cURL init & config
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_USERPWD, CAMPFIRE_ALERTS_AUTHTOKEN . ':x'); 
  curl_setopt($ch, CURLOPT_HTTPHEADER, array("Content-Type: application/json"));
  curl_setopt($ch, CURLOPT_POST, TRUE);
  curl_setopt($ch, CURLOPT_POSTFIELDS, $json);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
  $output = curl_exec($ch);
  curl_close($ch);
}
