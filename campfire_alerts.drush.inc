<?php

function campfire_alerts_drush_command() {
  $items = array();

  $items['campfire-alerts'] = array(
    'description' => 'Alert Campfire about possible issues.',
    'examples' => array(
      'drush campfire-alerts' => 'Checks a number of site parameters and alerts Campfire of potential issues.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );

  return $items;
}

function drush_campfire_alerts() {
  include_once 'campfire_alerts.inc';
  campfire_alerts_run();
}
