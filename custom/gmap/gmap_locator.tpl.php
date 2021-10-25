<?php
 global $base_root,$base_path;
 if(isset($_POST['submitmap']) && $_POST['submitmap']=='SaveValue'){
	 if($_POST['zone_id']==""){
		 echo "<script>alert('Please Select Zone')</script>";
	 }else{
		 $query = db_update('fa_zone');
		 $query->fields(array(
									'center_lat'	=> trim($_POST['txtLat']),
									'center_long' 	=> trim($_POST['txtLng']),
									'zoom_level' => trim($_POST['zoom'])
								));
		 $query->condition('zone_id', trim($_POST['zone_id']));
		 $rs = $query->execute();
		 
			 if($rs){
				 $myarr = rtrim($_POST['info'],'_');
				 $coordinates = explode("_",$myarr);
				 foreach($coordinates as $val){
					 $latlong = explode(",",$val); 
					 $latlongData	= 	array(
											'zone_id'	=> trim($_POST['zone_id']),
											'zone_lat' 	=> trim($latlong[0]),
											'zone_long' => trim($latlong[1])
										);
					db_insert('fa_zone_details')->fields($latlongData)->execute();
			 }
		 }
	 }
 }
?>
<!--<script src="js/jquery.min.js" type="text/javascript"></script>-->
<script async defer src="https://maps.googleapis.com/maps/api/js?v=3.exp&key=AIzaSyBbXEsoaFtph0_cu75lAZj2eIdq0GgZu54" type="text/javascript"></script>
<!--<script async defer src="https://maps.googleapis.com/maps/api/js?v=3.exp&sensor=false&key=AIzaSyBbXEsoaFtph0_cu75lAZj2eIdq0GgZu54&callback=initMap" type="text/javascript"></script>-->
<!--<script type="text/javascript" src="https://maps.googleapis.com/maps/api/js?v=3.exp&sensor=false"></script>-->



<script src="<?php print $base_root.$base_path?>sites/all/modules/custom/gmap/js/mapUtility.js" type="text/javascript"></script>
    <script type="text/javascript">
        var bermudaTriangle;
        function initializeMyMap() {
            var myLatLng = new google.maps.LatLng(22.652361, 88.377252);
            var mapOptions = {
                zoom: 6,
                center: myLatLng,
                mapTypeId: google.maps.MapTypeId.RoadMap
            };

            var map = new google.maps.Map(document.getElementById('map-canvas'),
            mapOptions);
			
			// add marker
			var vMarker = new google.maps.Marker({
				position: new google.maps.LatLng(22.652361, 88.377252),
				title: "Click for more information",
				
				draggable: true
			});
			
			google.maps.event.addListener(vMarker, 'dragend', function (evt) {
				$("#txtLat").val(evt.latLng.lat().toFixed(6));
				$("#txtLng").val(evt.latLng.lng().toFixed(6));
		
				map.panTo(evt.latLng);
			});

			map.setCenter(vMarker.position);
			
            var triangleCoords = [
			
			
			new google.maps.LatLng(22.586405, 88.358210),
			new google.maps.LatLng(22.588465, 88.358671),
			new google.maps.LatLng(22.588485, 88.358704),
			new google.maps.LatLng(22.590149, 88.359369),
			new google.maps.LatLng(22.591447, 88.359905),
			new google.maps.LatLng(22.595597, 88.361718),
			new google.maps.LatLng(22.602154, 88.364272),
			new google.maps.LatLng(22.605462, 88.365752),
			new google.maps.LatLng(22.606869, 88.367448),
			new google.maps.LatLng(22.607126, 88.368703),
			new google.maps.LatLng(22.606849, 88.369583),
			new google.maps.LatLng(22.608236, 88.370140),
			new google.maps.LatLng(22.611326, 88.372093),
			new google.maps.LatLng(22.614277, 88.373295),
			new google.maps.LatLng(22.615802, 88.373413),
			new google.maps.LatLng(22.618833, 88.373220),
			new google.maps.LatLng(22.630014, 88.371192),
			new google.maps.LatLng(22.632440, 88.371031),
			new google.maps.LatLng(22.638629, 88.373831),
			new google.maps.LatLng(22.642164, 88.374829),
			new google.maps.LatLng(22.643679, 88.374443),
			new google.maps.LatLng(22.652273, 88.377146),
			
			new google.maps.LatLng(22.652749, 88.357759),
			new google.maps.LatLng(22.651759, 88.357899),
			new google.maps.LatLng(22.650303, 88.358467),
			new google.maps.LatLng(22.648244, 88.358993),
			new google.maps.LatLng(22.645243, 88.359573),
			new google.maps.LatLng(22.642659, 88.360409),
			new google.maps.LatLng(22.640976, 88.361289),
			new google.maps.LatLng(22.638411, 88.362180),
			new google.maps.LatLng(22.635104, 88.363113),
			new google.maps.LatLng(22.632297, 88.364004),
			new google.maps.LatLng(22.628950, 88.365302),
			new google.maps.LatLng(22.625029, 88.366900),
			new google.maps.LatLng(22.620899, 88.367898),
			new google.maps.LatLng(22.617769, 88.368456),
			new google.maps.LatLng(22.614779, 88.368756),
			new google.maps.LatLng(22.610500, 88.368123),
			new google.maps.LatLng(22.608192, 88.367372),
			new google.maps.LatLng(22.604874, 88.364733),
			new google.maps.LatLng(22.602824, 88.362287),
			new google.maps.LatLng(22.600477, 88.359058),
			new google.maps.LatLng(22.598129, 88.355238),
			new google.maps.LatLng(22.595732, 88.352856),
			new google.maps.LatLng(22.594157, 88.351794),
			new google.maps.LatLng(22.589779, 88.350410),
			new google.maps.LatLng(22.587748, 88.349831),
			new google.maps.LatLng(22.586975, 88.352942),
			new google.maps.LatLng(22.586341, 88.358210),


        ];
            // Construct the polygon 
            bermudaTriangle = new google.maps.Polygon({
                paths: triangleCoords,
                draggable: true,
                editable: true,
                strokeColor: '#FF0000',
                strokeOpacity: 0.8,
                strokeWeight: 2,
                fillColor: '#FF0000',
                fillOpacity: 0.35
            });

            bermudaTriangle.setMap(map);
			vMarker.setMap(map);
            google.maps.event.addListener(bermudaTriangle, "dragend", getPolygonCoords);
            google.maps.event.addListener(bermudaTriangle.getPath(), "insert_at", getPolygonCoords);
            google.maps.event.addListener(bermudaTriangle.getPath(), "remove_at", getPolygonCoords);
            google.maps.event.addListener(bermudaTriangle.getPath(), "set_at", getPolygonCoords);
			google.maps.event.addListener(map, 'zoom_changed', function() {
				//alert('hi');
				$('#zoom').val(map.getZoom());
			 });
			 
			 
			 var html = "<input type='text' id='pind' value='' onkeyup='saveData()'/>";
			 
			 var infowindow = new google.maps.InfoWindow({
				content: html
			});

			 
			google.maps.event.addListener(vMarker, 'click', function () {
				infowindow.open(map, vMarker);
			});
 
        }

        function getPolygonCoords() {
            var len = bermudaTriangle.getPath().getLength();
            var htmlStr = "";
            for (var i = 0; i < len; i++) {
                htmlStr += bermudaTriangle.getPath().getAt(i).toUrlValue(5) + "_";
            }
            document.getElementById('info').innerHTML = htmlStr;
        }  
		
		
		function saveData(){
			var x = document.getElementById("pind").value;
			//alert(x);
    		document.getElementById("pintxt").value = x;
		}
    </script>
</head>

<body onLoad="initializeMyMap()">
    <div id="map-canvas" style="height: 550px; width: auto;">
    </div>
    <?php
	$query = db_select('fa_zone','z');
	$query->fields('z',array('zone_id','zone_name'));
	$query->orderBy('z.zone_name', 'ASC');
	$result	= $query->execute(); 
	?>
    <form name="frm" method="post" action="">
    <textarea name="info" id="info" style="width:100%"></textarea><br />
    <!--<div id="info" style="position: absolute; font-family: Arial; font-size: 14px; border:1px solid red;">
    </div>-->
    <input name="txtLat" id="txtLat" type="text" value="28.47399" /><br />
    <input name="txtLng" id="txtLng" type="text" value="77.026489" /><br />
    <input name="zoom" id="zoom" type="text" value="6" /><br />
    <input type="text" id="pintxt" name="pintxt" value="">
    <select name="zone_id" id="zone_id">
    <option value="">-Select-</option>
    <?php 
	foreach($result as $rows) {?>
		<option value="<?php echo $rows->zone_id;?>"><?php echo  $rows->zone_name;?></option>
	<?php }	?>
    
    </select> 
    
    <input type="hidden" name="submitmap" value="SaveValue">
    <input type="submit" name="submit" value="Save">
    </form>
    
</body>
</html>

