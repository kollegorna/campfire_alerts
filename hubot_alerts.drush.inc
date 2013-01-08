<?php

function hubot_alerts_drush_command() {
  $items = array();

  $items['hubot-alerts'] = array(
    'description' => 'Alert Campfire about possible issues.',
    'examples' => array(
      'drush hubot-alerts' => 'Checks a number of site parameters and alerts Campfire of potential issues.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );

  return $items;
}

function drush_hubot_alerts() {
  include_once 'hubot_alerts.inc';
  hubot_alerts_run();
}
