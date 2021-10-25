<?php
//echo "----------------------------------------->".$parm;

$query = db_select('fa_zone_details','zd');
$query ->leftJoin('fa_zone', 'z', 'zd.zone_id = z.zone_id'); 
$query->fields('z',array('zone_name','center_lat','center_long','zoom_level'));
$query->fields('zd',array('zone_details_id','zone_id','zone_lat','zone_long'));
$query->condition('z.zone_id', $parm, '='); 
$query->orderBy('z.zone_name', 'ASC');
$result	= $query->execute(); 
$resultData = $result->fetchAll();
//echo "<pre>";
//print_r($resultData);

if(!empty($resultData)){
?>

<script async defer src="https://maps.googleapis.com/maps/api/js?v=3.exp&key=AIzaSyBbXEsoaFtph0_cu75lAZj2eIdq0GgZu54&callback=initialize" type="text/javascript"></script>
<!--<script type="text/javascript" src="https://maps.googleapis.com/maps/api/js?v=3.exp&sensor=false"></script>-->
<!--<script src="<?php print $base_root.$base_path?>sites/all/modules/custom/gmap/js/mapUtility.js" type="text/javascript"></script>-->
    <script type="text/javascript">
        var bermudaTriangle;
        function initialize() {
            var myLatLng = new google.maps.LatLng(<?php echo $resultData[0]->center_lat;?>, <?php echo $resultData[0]->center_long;?>);
            var mapOptions = {
                zoom: <?php echo $resultData[0]->zoom_level;?>,
                center: myLatLng,
                mapTypeId: google.maps.MapTypeId.RoadMap
            };

            var map = new google.maps.Map(document.getElementById('map-canvas'),
            mapOptions);
			
			// add marker
			var vMarker = new google.maps.Marker({
				position: new google.maps.LatLng(<?php echo $resultData[0]->center_lat;?>, <?php echo $resultData[0]->center_long;?>),
				title: "Click for more information",
				
				draggable: true
			});
			
			/*google.maps.event.addListener(vMarker, 'dragend', function (evt) {
				$("#txtLat").val(evt.latLng.lat().toFixed(6));
				$("#txtLng").val(evt.latLng.lng().toFixed(6));
		
				map.panTo(evt.latLng);
			});

			map.setCenter(vMarker.position);*/
			
            var triangleCoords = [
			<?php
			foreach($resultData as $val){
			?>
			new google.maps.LatLng(<?php echo $val->zone_lat;?>, <?php echo $val->zone_long;?>),
			<?php }?>
        ];
            // Construct the polygon 
            bermudaTriangle = new google.maps.Polygon({
                paths: triangleCoords,
                //draggable: true,
                //editable: true,
                strokeColor: '#FF0000',
                strokeOpacity: 0.8,
                strokeWeight: 2,
                fillColor: '#FF0000',
                fillOpacity: 0.35
            });

            bermudaTriangle.setMap(map);
			vMarker.setMap(map);
			
			var contentString = '<?php echo $resultData[0]->zone_name;?>';

			var infowindow = new google.maps.InfoWindow({
			  content: contentString
			});
			
			infowindow.open(map, vMarker);
			/*google.maps.event.addListener(vMarker, 'click', function () {
				infowindow.open(map, vMarker);
			});*/
 
        }

        
    </script>
</head>

<div id="map-canvas" style="height: 550px; width: auto;"></div>
<?php }?>