# Campfire Alerts for Drupal

A Drupal module and Drush command that alerts a Campfire room when something is
amiss configuration-wise on a site.

It can run either as a module with a hook_cron() implementation, or as a
separate drush command: campfire-alerts

## Installation

Campfire Alerts can be installed either as a module, in the usual way, or as a
Drush command, e.g. in `~/.drush`.

*Don't do both* though, or you will get fatal 'Cannot redeclare' errors.

## Configuration

Either add variables to settings.php:

    $conf['campfire_alerts_url'] = 'https://<subdomain>.campfirenow.com';
    $conf['campfire_alerts_authtoken'] = '<myauthtoken>';
    $conf['campfire_alerts_room_id'] = '<myroomid>';

Or add environment variables before running Drupal's cron, e.g. in a bash script
in `/etc/cron.daily/drupal`:

    #!/bin/bash

    export CAMPFIRE_ALERTS_URL=https://<subdomain>.campfirenow.com
    export CAMPFIRE_ALERTS_AUTHTOKEN=<myauthtoken>
    export CAMPFIRE_ALERTS_ROOM_ID=<myroomidnumber>

    /path/to/drush cron --uri=default --root=/path/to/site

## Usage

If installed as a module, it will automatically run on the site's cron runs.

You may also run it directly as a Drush command:

    /path/to/drush campfire-alerts --uri=default --root=/path/to/site

## HipChat

To use with HipChat, see https://www.hipchat.com/docs/api/campfire_compatibility
(section Updating to use HipChat). Simply use the URL, token and room_id
collected from following those instructions.
