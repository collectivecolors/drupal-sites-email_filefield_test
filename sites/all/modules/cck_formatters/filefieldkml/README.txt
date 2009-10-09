; $Id $
ABOUT

This module provides an additional formatter for CCK file fields to render a 
KML file using Google Maps.  The user should, of course, not apply this formatter
to a file that is not a valid KML file, as the results will be unpredictable.

This module leverages the GMap module for configuration options.  At this time,
there is no ability to customize formatters per-field.  Hopefully that will be
added at a later date as the GMap module matures and supports KML files natively.

REQUIREMENTS

- Drupal 5.x
- filefield module
- gmap module

CONFIGURATION

At this time, all file fields formatted as a GMap use the defaults set by the
GMap module at admin/settings/gmap.  In later versions that will, hopefully,
be more configurable.

AUTHOR AND CREDIT

Author and Maintainer:
Larry Garfield
http://www.palantir.net/

This module was initially developed by Palantir.net.
