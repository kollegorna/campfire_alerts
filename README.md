# Hubot Alerts for Drupal

A Drupal module and Drush command that alerts a Campfire room when something 
is amiss configuration-wise on a site.

It can run either as a module with a hook_cron() implementation, or as a 
separate drush command: hubot-alerts

## Installation

Hubot Alerts can be installed either as a module, in the usual way, or as a 
Drush command, e.g. in `~/.drush`
*Don't do both* though, or you will get fatal 'Cannot redeclare' errors.

## Configuration

Add environment variables for Campfire in cron script, e.g.
in `/etc/cron.daily/drupal`:

    #!/bin/bash

    export HUBOT_ALERTS_URL=https://<subdomain>.campfirenow.com
    export HUBOT_ALERTS_AUTHTOKEN=<myauthtoken>
    export HUBOT_ALERTS_ROOM_ID=<myroomidnumber>

    /path/to/drush cron --uri=default --root=/path/to/site

Or, if installed as a Drush command:

    ...
    /path/to/drush hubot-alerts --uri=default --root=/path/to/site
