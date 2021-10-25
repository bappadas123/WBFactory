<?php
function deputychief_dashboard($form, &$form_state) {
global $base_root,$base_path,$user;
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	//drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');

   /****************************** Check IF Profile is Fillup or Not************************************************/
   $status = getUserProfileStatus($user->uid);
   if($status['one_time_pass_flag'] == '0') {
		drupal_goto('profileupdate');
		exit;
   }
	
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
			}
			
		}
	
	$form = array();
	
	$form['regsection_dashboard']['icon_regsection'] = array(
	 	'#prefix' 			=> '<div class="row">
       			 				<div class="col-md-3 col-sm-6 col-xs-12">
          						<div class="info-box"><span class="info-box-icon bg-aqua"><i class="fa fa-handshake-o" aria-hidden="true"></i></span>
            					<div class="info-box-content"><span class="info-box-text">Forward of Factory Registration</span><span class="info-box-number">90<small>%</small></span></div>',
		'#suffix' 			=> '</div></div>',
		'#type' 			=> 'markup',
		//'#markup' 			=> get_all_type_application(),
  	);	
		$form['regsection_dashboard']['icon_regsection2'] = array(
	 	'#prefix' 			=> '<div class="col-md-3 col-sm-6 col-xs-12">
          						<div class="info-box"><span class="info-box-icon bg-red"><i class="fa fa-address-book-o" aria-hidden="true"></i></span>
           						<div class="info-box-content"><span class="info-box-text">Registration and grant of Licence</span><span class="info-box-number">41,410</span></div>',
		'#suffix' 			=> '</div></div>',
		'#type' 			=> 'markup',
		//'#markup' 			=> get_all_type_application(),
  	);	
		$form['regsection_dashboard']['icon_regsection3'] = array(
	 	'#prefix' 			=> '<div class="col-md-3 col-sm-6 col-xs-12">
          						<div class="info-box"><span class="info-box-icon bg-green"><i class="fa fa-address-card-o" aria-hidden="true"></i></span>
            					<div class="info-box-content"><span class="info-box-text">Renewal of Factory Licence</span><span class="info-box-number">760</span></div>',
		'#suffix' 			=> '</div></div>',
		'#type' 			=> 'markup',
		//'#markup' 			=> get_all_type_application(),
  	);	
		$form['regsection_dashboard']['icon_regsection4'] = array(
	 	'#prefix' 			=> '<div class="col-md-3 col-sm-6 col-xs-12">
          						<div class="info-box"><span class="info-box-icon bg-yellow"><i class="fa fa-list-alt" aria-hidden="true"></i></span>
            					<div class="info-box-content"><span class="info-box-text">Directorate of Factories</span><span class="info-box-number">2,000</span></div>',
		'#suffix' 			=> '</div></div>',
		'#type' 			=> 'markup',
		//'#markup' 			=> get_all_type_application(),
  	);	
	
	$form['regsection_dashboard']['markup_regsection_details'] = array(
	'#prefix' 				=> '<div class="col-md-8"><div class="box box-primary"><div class="box-header with-border"><h3 class="box-title">Details</h3><div class="box-tools pull-right"><button type="button" class="btn btn-box-tool" data-widget="collapse"><i class="fa fa-minus"></i></button></div></div>
		 <div class="box-body">
           <div class="row">
              <div class="col-md-8">
                  <p class="text-left"><strong>Name: '.$fname.'</strong></p>
				   <p class="text-left"><strong>Zone:  '.$zone_list.'</strong></p>
				    <p class="text-left"><strong>Designation:  '.$role.'</strong></p>
					</div>
                	<div class="col-md-4">
                  	<p class="text-left"> <strong>Total Application: ' .$total.'</strong> </p> 
                	</div>',	
	'#suffix' 			=> '</div></div></div></div>',
	'#type' 			=> 'markup',
	//'#markup' 			=> get_all_type_application(),
	);
	
	$form['regsection_dashboard']['markup_regsection_Zone'] = array(
	'#prefix' 			=> '<div class="col-md-4"><div class="box box-default# box-success"><div class="box-header with-border"><h3 class="box-title">Zone</h3> <div class="box-tools pull-right"><button type="button" class="btn btn-box-tool" data-widget="collapse"><i class="fa fa-minus"></i></button><button type="button" class="btn btn-box-tool" data-widget="remove"><i class="fa fa-times"></i></button></div></div><div class="box-body"><div class="col-md-8 cus-img-width-100"><img src="'.$base_root.$base_path.'/sites/all/themes/custom_dashboard/images/wb.jpg"/>',
	
	'#suffix' 			=> ' </div></div></div></div>',
	'#type' 			=> 'markup',
	//'#markup' 			=> get_all_type_application(),
	
	);
	$form['regsection_dashboard']['begin'] = array(
		'#prefix' => '<div class="col-md-12"><div class="box box-info">
            <div class="box-header with-border">
              <h3 class="box-title"><b>SERVICE:</b> Factory Registration and grant of license</h3>
              <div class="box-tools pull-right">
                <button type="button" class="btn btn-box-tool" data-widget="collapse"><i class="fa fa-minus"></i> </button>
                <button type="button" class="btn btn-box-tool" data-widget="remove"><i class="fa fa-times"></i></button>
              </div>
            </div>
            <!-- /.box-header -->
            <div class="box-body">
              <div class="table-responsive">',
		'#suffix' => ''
	);
	
	$form['regsection_dashboard']['zone_id'] = array(
		'#title' => t('Zone'),	
		'#type' => 'select',
		'#ajax' => array(
				'callback' => 'ajax_zone_callback',
			),
		 
		//'#required' => TRUE,
		'#options' => $zoneDropDown,
		//'#default_value' => !empty($resultData)? $resultData['pid'] : '',
		'#attributes' => array('class'=>array('form-control')),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
		);
	
	$form['regsection_dashboard']['all_app'] = array(
		'#type'   => 'markup',
		'#markup' => get_all_application($zoneUserMap),
		'#prefix' => '<div id="table_app_replace_div"><div class="col-md-12">',
		'#suffix' => '</div></div>'
  	);	
	$form['regsection_dashboard']['end'] = array(
		'#prefix' => '',
		'#suffix' => '</div></div></div></div></div>'
	);	  		  
	return $form; 
  }
function get_all_application($zoneUserMap){
	
	global $base_root,$base_path,$user;
	$applicant_id 			= $user->uid;
	$get_all_data 			= array();
	$rows[] 				= array();
	$type					= '';
	$details				= '';
	$relationship			= '';
	$address_of_director	= '';
	$get_all_data			= get_reg_application_list($zoneUserMap);
	
	//echo "<pre>"; print_r($get_all_data); die;
	
	$Wcounter		= 0;
	$status 		= '';
	$per_page		= 10;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
		}
	$header 		= array(
								array('data'=> 'Sl. No'),
								array('data'=> 'Factory Details'),
								array('data'=> 'Plan Approval No./License No & Date'),
								array('data'=> 'e-Service'),
								array('data'=> 'Application Number & Date'),
								array('data'=> 'Status & Date'),
								array('data'=> 'Action'),
							);
	if(!empty($get_all_data)){
		
		foreach($chunks[$current_page] as $details){ 
			$Wcounter++;
				 if($details->application_status == 'U'){
					 	$status = '<b style="color:#0D67A2;">Final submitted</b>';
					 }
					 elseif($details->application_status == 'R'){
						$status = '<b style="color:#000000">Application Rejected.</b>';
					 }
					  elseif($details->application_status == 'RS'){
						$status = '<b style="color:#0D67A2;">Application Re-submitted</b>';
					 }
					 elseif($details->application_status == 'AI'){
					 	$status = '<b style="color:#0D67A2;">Forward to Inspector</b>';
					 }
					 elseif($details->application_status == 'B'){
					 	$status = '<b style="color:#0D67A2;">Backed to Applicant</b>';
					 }
					 elseif($details->application_status == 'AIBk'){
						$status = '<b style="color:#0008ff;">Backed to Inspector</b>';
					 }
					 elseif($details->application_status == 'DC'){
						$status = '<b style="color:#ff0000;">Pending</b>';
					 }
					  elseif($details->application_status == 'DCBk'){
						$status = '<b style="color:#ff0000;">Backed by  Jt. CIF</b>';
					 }
					 elseif($details->application_status == 'JC'){
					 	$status = '<b style="color:green;">Forward to Jt. CIF</b>';
					 }
					 elseif($details->application_status == 'JCBk'){
					 	$status = '<b style="color:#ff0000;">Back to Jt. CIF</b>';
					 }
					 elseif($details->application_status == 'CH'){
					 	$status = '<b style="color:#008000;">Forward to CIF</b>';
					 }
					 elseif($details->application_status == 'APP'){
					 	$status = '<b style="color:green;">Approve Licence</b>';
					 }
					 elseif($details->application_status == 'APP-REG'){
					 	$status = '<b style="color:red;">Approve Licence & Registration</b>';
					 }
					 elseif($details->application_status == 'I'){
					 	$status = '<b style="color:Green;">Approve Licence & Registration Issue</b>';
					 }
					 elseif($details->application_status == 'RP'){
					 	$status 			= '<b style="color:#0D67A2;">Re-payment</b>';
					 }
					 	$preview_link	= l('<i class="fa fa-eye" aria-hidden="true"></i> View', 'regsection/application-view-register-deputychief/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''))));
				 
			 	$Identification = $details->factory_reg_identification_number;	
					 if(empty($Identification)){
							$Identification = 'Under Process';
						}
					if(!empty($details->created_date)){
						$created_date = date('dS M Y', strtotime($details->created_date));
						}else{
							$created_date = '';
							}
				if(!empty($details->modification_date)){
					$modification_date = date('dS M Y', strtotime($details->modification_date));
					}else{
					$modification_date = '';
					}
		
				if(!empty($details->factory_plan_approval_number)){
					$plan_approval = $details->factory_plan_approval_number.'<br><b>Date - </b>'.$modification_date;
					}else{
						$plan_approval = '--';
					}
			
				$factory_type = explode(' ',$details->factory_type);
					
					$rows[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' =>$details->factory_name.' ['.$factory_type[1].']<br><b>Zone - </b>'.$details->zone_name,'class' => array('')),
							array('data' =>$plan_approval,$details->zone_name,'class' => array('')),
							array('data' =>$details->service_name ,'class' => array('')),
							array('data' =>$Identification.'<br><b>Date - </b>'.$created_date,'class' => array('')),
							array('data' =>$status.'<br><b>Date - </b>'.$modification_date,'class' => array('')),
							array('data' =>$preview_link.'<br/>','class' => array('')),
						);
						}
					}
	
				$output = theme_table(
				array(
		  			'header'	=> $header,
		  			'rows' 		=> $rows,
		  			'attributes'=> array('class' => array('table no-margin remove-odd-even# custom-table-view-dashboard')),
		 			// 'sticky' => true,
		  			'caption' 	=> '',
		  			'colgroups' => array(),
		  			'empty' 	=> t("No data found!"))
					).theme('pager');	
		 		return $output;
				}
?>