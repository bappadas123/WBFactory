(function ($) {
	Drupal.behaviors.project_store = {
		attach: function(context) {
					var baseURL ="";
					if(window.location.host == "localhost"){
						baseURL = window.location.protocol + "//" + window.location.host + "/factories";
					}else{
						baseURL = window.location.protocol + "//" + window.location.host;
					}
					function initialize() {
						
						  google.maps.Polygon.prototype.Contains = function (point) {
							// ray casting alogrithm http://rosettacode.org/wiki/Ray-casting_algorithm
							var crossings = 0,
							path = this.getPath();
				
							// for each edge
							for (var i = 0; i < path.getLength(); i++) {
								var a = path.getAt(i),
								j = i + 1;
								if (j >= path.getLength()) {
									j = 0;
								}
								var b = path.getAt(j);
								if (rayCrossesSegment(point, a, b)) {
									crossings++;
								}
							}
				
							// odd number of crossings?
							return (crossings % 2 == 1);
				
							function rayCrossesSegment(point, a, b) {
								var px = point.lng(),
								py = point.lat(),
								ax = a.lng(),
								ay = a.lat(),
								bx = b.lng(),
								by = b.lat();
								if (ay > by) {
									ax = b.lng();
									ay = b.lat();
									bx = a.lng();
									by = a.lat();
								}
								if (py == ay || py == by) py += 0.00000001;
								if ((py > by || py < ay) || (px > Math.max(ax, bx))) return false;
								if (px < Math.min(ax, bx)) return true;
				
								var red = (ax != bx) ? ((by - ay) / (bx - ax)) : Infinity;
								var blue = (ax != px) ? ((py - ay) / (px - ax)) : Infinity;
								return (blue >= red);
							}
						};

						 
						
						
						
						
						  var mapOptions = {
							  center: new google.maps.LatLng(-33.8688, 151.2195),
							  zoom: 13,
							  mapTypeId: google.maps.MapTypeId.ROADMAP
						  };
						  var map = new google.maps.Map(document.getElementById('map_canvas'),
						  mapOptions);
				
						  var input = document.getElementById('searchTextField');
						  var autocomplete = new google.maps.places.Autocomplete(input);
				
						  autocomplete.bindTo('bounds', map);
				
						  var infowindow = new google.maps.InfoWindow();
						  var marker = new google.maps.Marker({
							  map: map
						  });
				
						  google.maps.event.addListener(autocomplete, 'place_changed', function () {
							  infowindow.close();
							  var place = autocomplete.getPlace();
				
							  /*if (place.geometry.viewport) {
								  map.fitBounds(place.geometry.viewport);
							  } else {
								  map.setCenter(place.geometry.location);
								  map.setZoom(17); // Why 17? Because it looks good.
							  }
				
							  var image = new google.maps.MarkerImage(
							  place.icon,
							  new google.maps.Size(71, 71),
							  new google.maps.Point(0, 0),
							  new google.maps.Point(17, 34),
							  new google.maps.Size(35, 35));
							  marker.setIcon(image);
							  marker.setPosition(place.geometry.location);*/
				
							  var address = '';
							  if (place.address_components) {
								  address = [(place.address_components[0] && place.address_components[0].short_name || ''), (place.address_components[1] && place.address_components[1].short_name || ''), (place.address_components[2] && place.address_components[2].short_name || '')].join(' ');
							  }
				
							  updateTextFields(place.geometry.location.lat(),place.geometry.location.lng());
							  
				
							  //infowindow.setContent('<div><strong>' + place.name + '</strong><br>' + address + "<br>" + place.geometry.location);
							  //infowindow.open(map, marker);
						  });
				
						  // Sets a listener on a radio button to change the filter type on Places
						  // Autocomplete.
						  /*function setupClickListener(id, types) {
							  var radioButton = document.getElementById(id);
							  google.maps.event.addDomListener(radioButton, 'click', function () {
								  autocomplete.setTypes(types);
							  });
						  }
				
						  setupClickListener('changetype-all', []);
						  setupClickListener('changetype-establishment', ['establishment']);
						  setupClickListener('changetype-geocode', ['geocode']);*/
					  }
					  google.maps.event.addDomListener(window, 'load', initialize);
					  
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
					  var triangleCoords = [];	
					  function updateTextFields(lat, lng) {
						  //alert(lat+"-->"+lng);
						  //$.get('/zonelist');
						   /*$.ajax({
								type: "POST",
								url: baseURL+"/sites/all/modules/custom/gmap/checklatlong",
								async: false,
								data: "lat="+lat+"long="+lng,
								success: function(data) {
									alert(data);
								}
							});*/
							
							/*$.ajax({
								type: "GET",
								url: baseURL+"/checklatlong/"+lat+"/"+lng,
								async: false,
								success: function(data) {
									alert(data);
								}
							});*/
						  
						  
						  	var point = new google.maps.LatLng(lat, lng);
							var polygon = new google.maps.Polygon({path:triangleCoords});
							if (polygon.Contains(point)) {
								// point is inside polygon
								alert('inside polygon');
							}else{
								alert('out side polygon');
							}
						  $('#lat_lng').html(lat+"-->"+lng);
						  //$('#lng').val(lng);
					  }
	  
	  
			
			}
	}
})(jQuery);