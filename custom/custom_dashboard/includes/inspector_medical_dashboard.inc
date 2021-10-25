<?php
function inspector_medical_dashboard($form, &$form_state) {
	global $base_root,$base_path,$user;

  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/sky-forms.css');
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	//drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');

   /****************************** Check IF Profile is Fillup or Not************************************************/
   $status = getUserProfileStatus($user->uid);
   if(empty($status['one_time_pass_flag']) || $status['one_time_pass_flag'] == '0') {
		drupal_goto('profileupdate');
		exit;
   }
   /********************************** End Profile is Fillup Cheaking************************************************/
   
   	$zoneUserMap = array();
	$zoneUserMapResult = getZoneUserMap($user->uid);
	if(!empty($zoneUserMapResult)){
		foreach($zoneUserMapResult as $v){
			$zoneUserMap[] = $v->zone_id;
		}
	}
	$zoneDropDown = array();
	$zoneDropDown[] = '-Select-';
	if(!empty($zoneUserMapResult)){
		$zone_list='';
		foreach($zoneUserMapResult as $v){
			$zoneDropDown[$v->zone_id] = $v->zone_name;
			if ($v->zone_name) $v->zone_name .= ',';
   				$zone_list .= $v->zone_name;
		}
	}
		
		$get_all_data =  get_reg_application_list($zoneUserMap);
		$total = count($get_all_data);
		$userData = get_details_employee($user->uid);
		if(!empty($userData)){
			if($userData['fname']!=""){
				$fname = $userData['fname'];
			}else{
				$fname = $userData['name'];
			} 
			if(array_key_exists(5, $user->roles)){
				$role = 'Plan Section';
			}elseif(array_key_exists(7, $user->roles)){
				$role = 'Cms Manager';
			}elseif(array_key_exists(8, $user->roles)){
				$role = 'Registration Section';
			}elseif(array_key_exists(9, $user->roles)){
				$role = 'Factory Inspector';
			}elseif(array_key_exists(10, $user->roles)){
				$role = 'Deputy Chief Inspector';
			}elseif(array_key_exists(11, $user->roles)){
				$role = 'Joint Chief Inspector';
			}elseif(array_key_exists(12, $user->roles)){
				$role = 'Chief Inspector';
			}elseif(array_key_exists(14, $user->roles)){
				$role = 'Factory Inspector Chemical';
			}elseif(array_key_exists(13, $user->roles)){
				$role = 'Deputy Chief Inspector Chemical';
			}elseif(array_key_exists(17, $user->roles)){
				$role = 'Joint Chief Inspector Chemical';
			}elseif(array_key_exists(30, $user->roles)){
				$role = 'Statistical Cell Incharge';
			}elseif(array_key_exists(31, $user->roles)){
				$role = 'Receiving Cell';
			}			
		}
	
	$form = array();
	
	$form['inspector_medical_dashboard']['icon_regsection'] = array(
	 	'#prefix' 			=> '<div class="row">
       			 				<div class="col-md-3 col-sm-6 col-xs-12">
          						<div class="info-box"> <span class="info-box-icon bg-aqua"><i class="fa fa-handshake-o" aria-hidden="true"></i></span>
            					<div class="info-box-content"> <span class="info-box-text">Forword of Factory Registration</span> <span class="info-box-number">90<small>%</small></span> </div>',
		'#suffix' 			=> '</div></div>',
		'#type' 			=> 'markup',
		//'#markup' 			=> get_all_type_application(),
  	);	
		$form['inspector_medical_dashboard']['icon_regsection2'] = array(
	 	'#prefix' 			=> '<div class="row">
       			 				<div class="col-md-3 col-sm-6 col-xs-12">
          						 <div class="info-box"> <span class="info-box-icon bg-red"><i class="fa fa-address-book-o" aria-hidden="true"></i></span>
           						 <div class="info-box-content"> <span class="info-box-text">Registration and grant of Licence</span> <span class="info-box-number">41,410</span> </div>',
		'#suffix' 			=> '</div></div>',
		'#type' 			=> 'markup',
		//'#markup' 			=> get_all_type_application(),
  	);	
		$form['inspector_medical_dashboard']['icon_regsection3'] = array(
	 	'#prefix' 			=> '<div class="row">
       			 				<div class="col-md-3 col-sm-6 col-xs-12">
          						<div class="info-box"> <span class="info-box-icon bg-green"><i class="fa fa-address-card-o" aria-hidden="true"></i></span>
            <div class="info-box-content"> <span class="info-box-text">Renewal of Factory Licence</span> <span class="info-box-number">760</span> </div>',
		'#suffix' 			=> '</div></div>',
		'#type' 			=> 'markup',
		//'#markup' 			=> get_all_type_application(),
  	);	
		$form['inspector_medical_dashboard']['icon_regsection4'] = array(
	 	'#prefix' 			=> '<div class="row">
       			 				<div class="col-md-3 col-sm-6 col-xs-12">
          						 <div class="info-box"> <span class="info-box-icon bg-yellow"><i class="fa fa-list-alt" aria-hidden="true"></i></span>
            <div class="info-box-content"> <span class="info-box-text">Directorate of Factories</span> <span class="info-box-number">2,000</span> </div>',
		'#suffix' 			=> '</div></div></div>',
		'#type' 			=> 'markup',
		//'#markup' 			=> get_all_type_application(),
  	);	
	
	$form['inspector_medical_dashboard']['markup_regsection_details'] = array(
	'#prefix' 			=> '<div class="col-md-8"><div class="box"><div class="box-header with-border"><h3 class="box-title">Details</h3><div class="box-tools pull-right"><button type="button" class="btn btn-box-tool" data-widget="collapse"><i class="fa fa-minus"></i> </button></div></div>
		 <div class="box-body">
              <div class="row">
                <div class="col-md-8">
                  <p class="text-left"> <strong>Name: '.$fname.'</strong> </p>
				   <p class="text-left"> <strong>Zone:  '.$zone_list.'</strong> </p>
				    <p class="text-left"> <strong>Designation:  '.$role.'</strong> </p>
					</div>
                <div class="col-md-4">
                  <p class="text-left"> <strong>Total Application: ' .$total.'</strong> </p> 
                </div>',
	
	'#suffix' 			=> ' </div></div></div></div>',
	'#type' 			=> 'markup',
	//'#markup' 			=> get_all_type_application(),
	);
	
	$form['inspector_medical_dashboard']['markup_regsection_Zone'] = array(
	'#prefix' 			=> '<div class="col-md-4"> <div class="box box-default"> <div class="box-header with-border"> <h3 class="box-title">Zone</h3> <div class="box-tools pull-right"><button type="button" class="btn btn-box-tool" data-widget="collapse"><i class="fa fa-minus"></i> </button><button type="button" class="btn btn-box-tool" data-widget="remove"><i class="fa fa-times"></i></button></div></div><div class="box-body"> <div class="row"> <div class="col-md-8"><img src="'.$base_root.$base_path.'/sites/all/themes/custom_dashboard/images/wb.jpg"/>',
	
	'#suffix' 			=> ' </div></div></div></div></div>',
	'#type' 			=> 'markup',
	//'#markup' 			=> get_all_type_application(),
	
	);
	  		  
	return $form; 
  
}

?>