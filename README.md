# Hubot Alerts for Drupal

A Drupal module that alerts a Campfire room when something is amiss
configuration-wise on a site.

## Configuration

Add environment variables for Campfire in cron script, e.g.
in `/etc/cron.daily/drupal`:

    #!/bin/bash

    export HUBOT_ALERTS_URL=https://<subdomain>.campfirenow.com
    export HUBOT_ALERTS_AUTHTOKEN=<myauthtoken>
    export HUBOT_ALERTS_ROOM_ID=<myroomidnumber>

    /path/to/drush cron --uri=default --root=/path/to/site
