<?php 

define('CAMPFIRE_ALERTS_URL', getenv('CAMPFIRE_ALERTS_URL')); // Use full URL, http://[account].campfirenow.com
define('CAMPFIRE_ALERTS_AUTHTOKEN', getenv('CAMPFIRE_ALERTS_AUTHTOKEN')); 
define('CAMPFIRE_ALERTS_ROOM_ID', getenv('CAMPFIRE_ALERTS_ROOM_ID')); // To get room_id, login to your CF room and look in the address bar (after /room)

function campfire_alerts_run() {

  watchdog('Campfire Alerts!', t('Checking...'));
  $errors = array();
  campfire_alerts_check_cache($errors);
  campfire_alerts_check_css_preprocessning($errors);
  campfire_alerts_check_js_preprocessing($errors);
  campfire_alerts_check_error_reporting($errors);
  campfire_alerts_check_pending_updates($errors);
  campfire_alerts_check_default_favicon($errors);

  if (!empty($errors)) {
    campfire_alerts_campfire_post("Hey! Problems on " . variable_get('site_name', 'Mysteriously unnamed site') . ":");
    foreach ($errors as $error) {
      campfire_alerts_campfire_post($error);
      watchdog('Campfire Alerts!', $error);
    }
    campfire_alerts_campfire_post('horror', 'SoundMessage');
  }
  else watchdog('Campfire Alerts!', t('All is well!'));
}

function campfire_alerts_check_cache(&$errors) {
  $msg = t("Caching is turned off!");
  if (!variable_get('cache', NULL)) {
    $errors[] = $msg;
  }
}
function campfire_alerts_check_css_preprocessning(&$errors) {
  $msg = t("CSS optimization is turned off!");
  if (!variable_get('preprocess_css', NULL)) {
    $errors[] = $msg;
  }
}

function campfire_alerts_check_js_preprocessing(&$errors) {
  $msg = t("JavaScript optimization is turned off!");
  if (!variable_get('preprocess_js', NULL)) {
    $errors[] = $msg;
  }
}

function campfire_alerts_check_error_reporting(&$errors) {
  $msg = t("Error reporting is misconfigured, errors will be visible to users!");
  if (variable_get('error_level', NULL) == 1) {
    $errors[] = $msg;
  }
}

function campfire_alerts_check_pending_updates(&$errors) {
  $msg = t("There are pending database updates!");
  require_once DRUPAL_ROOT . '/includes/install.inc';
  require_once DRUPAL_ROOT . '/includes/update.inc';
  drupal_load_updates();
  $updates = update_get_update_list();
  if (!empty($updates)) {
    $errors[] = $msg;
  }
}

function campfire_alerts_check_default_favicon(&$errors) {
  $msg = t("The default Drupal favicon is enabled!");
  // Get the global theme settings.
  $theme_settings = variable_get('theme_settings', array());
  // // Get the settings of the default theme.
  $theme_settings = array_merge($theme_settings, variable_get('theme_' . variable_get('theme_default', 'bartik') . '_settings', array()));
  if ($theme_settings['toggle_favicon'] == 1 && $theme_settings['default_favicon'] == 1) {
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
  $error = curl_error($ch);
  if ($error) {
    drupal_set_message(t('Campfire Connection Error: @error', array('@error' => $error)), 'warning');
  }
  curl_close($ch);
}
