import QtQuick
import QtLocation
import QtPositioning

Item {
    id: mapItem
    anchors.fill: parent
    
    Plugin {
        id: mapPlugin
        name: "osm"  // OpenStreetMap plugin
    }
    
    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(-6.600, 106.806)  // Bogor
        zoomLevel: 14
        
        // Menambahkan kontrol zoom
        PinchHandler {
            id: pinch
            target: null
            onActiveChanged: if (active) {
                map.startCentroid = map.toCoordinate(pinch.centroid.position, false)
            }
            onScaleChanged: (delta) => {
                map.zoomLevel += Math.log2(delta)
                map.alignCoordinateToPoint(map.startCentroid, pinch.centroid.position)
            }
        }
        
        // Menambahkan kontrol drag
        DragHandler {
            id: drag
            target: null
            onTranslationChanged: (delta) => map.pan(-delta.x, -delta.y)
        }
        
        // Property untuk menyimpan posisi awal centroid
        property geoCoordinate startCentroid
    }
    
    // Fungsi yang bisa dipanggil dari C++
    function setCenter(lat, lng) {
        map.center = QtPositioning.coordinate(lat, lng);
    }
    
    function addMarker(lat, lng, title) {
        var component = Qt.createComponent("MapMarker.qml");
        if (component.status === Component.Ready) {
            var marker = component.createObject(map, {
                coordinate: QtPositioning.coordinate(lat, lng),
                title: title
            });
            map.addMapItem(marker);
            return true;
        }
        return false;
    }
}
