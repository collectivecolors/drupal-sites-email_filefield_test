Drupal.filefieldkml = {};

Drupal.filefieldkml.init = function() {
  
  var kmlSettings = Drupal.settings.filefieldkml;
  
  for(var mapId in kmlSettings) {
    var map;
    var gx;

    gx = new GGeoXml(kmlSettings[mapId].kmlFile, function() {
      if (kmlSettings[mapId].behavior.autozoom) {
        // Center/zoom the map to account for this KML file.
        gx.gotoDefaultViewport(map);
      }
    });
    
    map = new GMap2(document.getElementById(mapId));

    // We have to set a center to begin with, or the map malfunctions.
    // This will get overridden as soon as the KML file loads anyway.
    var latlong = kmlSettings[mapId].latlong.split(',');
    map.setCenter(new GLatLng(latlong[0], latlong[1]), kmlSettings[mapId].zoom);
    
    // Set various map configuration options based on the settings provided.
    
    switch (kmlSettings[mapId].maptype) {
      case 'Satellite':
        map.setMapType(G_SATELLITE_MAP);
        break;
      case 'Hybrid':
        map.setMapType(G_HYBRID_MAP);
        break;
      case 'Map':
      default:
        map.setMapType(G_NORMAL_MAP);
        break;
    }
    
    if (kmlSettings[mapId].behavior.overview) {
      map.addControl(new GOverviewMapControl());
    }
    
    switch (kmlSettings[mapId].controltype) {
      case 'Large':
        map.addControl(new GLargeMapControl());
        break;
      case 'Small':
        map.addControl(new GSmallMapControl());
        break;
    }
    
    if (kmlSettings[mapId].behavior.nodrag) {
      map.disableDragging();
    }
    else {
      map.enableDragging();
    }
    
    if (kmlSettings[mapId].behavior.nomousezoom) {
      map.disableScrollWheelZoom();
    }
    else {
      map.enableScrollWheelZoom();
    }
    
    if (kmlSettings[mapId].behavior.nomousezoom) {
      map.disableScrollWheelZoom();
    }
    else {
      map.enableScrollWheelZoom();
      map.enableContinuousZoom();
    }
    
    // Finally, add the KML file.
    map.addOverlay(gx);
  }
  
};

$(document).ready(function () {
  Drupal.filefieldkml.init();
});
