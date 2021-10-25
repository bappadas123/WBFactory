<?php
function receiving_dashboard($form, &$form_state) { 
	global $base_root,$base_path,$user;
	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	//drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
   /****************************** Check IF Profile is Fillup or Not************************************************/
   $status = getUserProfileStatus($user->uid);
   if(empty($status['one_time_pass_flag']) || $status['one_time_pass_flag'] == '0') {
		drupal_goto('profileupdate');
		exit;
   }
   /********************************** End Profile is Fillup Cheaking************************************************/
   	/*$zoneUserMap = array();
	$zoneUserMapResult = getZoneUserMap($user->uid);
	if(!empty($zoneUserMapResult)){
		foreach($zoneUserMapResult as $v){
			$zoneUserMap[] = $v->zone_id;
		}
	}*/
	// FOR ESCALLATION //
	//$escallation = get_applcation_escalate($zoneUserMap);
	
	/*$zoneDropDown = array();
	$zoneDropDown[] = '-Select-';
	if(!empty($zoneUserMapResult)){
		$zone_list='';
		foreach($zoneUserMapResult as $v){
			$zoneDropDown[$v->zone_id] = $v->zone_name;
			if ($v->zone_name) $v->zone_name .= ',';
   				$zone_list .= $v->zone_name;
		}
	}
		*/
		//$get_all_data =  get_regsection_application_list($zoneUserMap);echo "cvcv"; die;

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
	
	$form['receiving_dashboard']['icon_regsection'] = array(
	 	'#prefix' 			=> '<div class="row">
       			 				<div class="col-md-3 col-sm-6 col-xs-12">
          						<div class="info-box"><span class="info-box-icon bg-aqua"><i class="fa fa-handshake-o" aria-hidden="true"></i></span>
            					<div class="info-box-content"><span class="info-box-text">Forward of Factory Registration</span><span class="info-box-number">90<small>%</small></span></div>',
		'#suffix' 			=> '</div></div>',
		'#type' 			=> 'markup',
		//'#markup' 			=> get_all_type_application(),
  	);	
		$form['receiving_dashboard']['icon_regsection2'] = array(
	 	'#prefix' 			=> '<div class="col-md-3 col-sm-6 col-xs-12">
          						<div class="info-box"><span class="info-box-icon bg-red"><i class="fa fa-address-book-o" aria-hidden="true"></i></span>
           						<div class="info-box-content"><span class="info-box-text">Registration and grant of Licence</span><span class="info-box-number">41,410</span></div>',
		'#suffix' 			=> '</div></div>',
		'#type' 			=> 'markup',
		//'#markup' 			=> get_all_type_application(),
  	);	
		$form['receiving_dashboard']['icon_regsection3'] = array(
	 	'#prefix' 			=> '<div class="col-md-3 col-sm-6 col-xs-12">
          						<div class="info-box"><span class="info-box-icon bg-green"><i class="fa fa-address-card-o" aria-hidden="true"></i></span>
            					<div class="info-box-content"><span class="info-box-text">Renewal of Factory Licence</span> <span class="info-box-number">760</span></div>',
		'#suffix' 			=> '</div></div>',
		'#type' 			=> 'markup',
		//'#markup' 			=> get_all_type_application(),
  	);	
		$form['receiving_dashboard']['icon_regsection4'] = array(
	 	'#prefix' 			=> '<div class="col-md-3 col-sm-6 col-xs-12">
          						<div class="info-box"><span class="info-box-icon bg-yellow"><i class="fa fa-list-alt" aria-hidden="true"></i></span>
            					<div class="info-box-content"><span class="info-box-text">Directorate of Factories</span><span class="info-box-number">2,000</span></div>',
		'#suffix' 			=> '</div></div>',
		'#type' 			=> 'markup',
		//'#markup' 			=> get_all_type_application(),
  	);	
	
	$form['receiving_dashboard']['markup_regsection_details'] = array(
	'#prefix' 			=> '<div class="col-md-8">
								<div class="box box-primary">
									<div class="box-header with-border">
										<h3 class="box-title">Details</h3>
										<div class="box-tools pull-right">
											<button type="button" class="btn btn-box-tool" data-widget="collapse"><i class="fa fa-minus"></i></button>
										</div>
									</div>
		 					<div class="box-body">
                				<div class="col-md-8">
                  					<p class="text-left"> <strong>Name: '.$fname.'</strong> </p>
				   					<p class="text-left"> <strong>Zone:  '.$zone_list.'</strong> </p>
				    				<p class="text-left"> <strong>Designation:  '.$role.'</strong> </p>
								</div>
                			<div class="col-md-4">
                  				<p class="text-left"> <strong>Total Application: ' .$total.'</strong> </p> 
                			</div>',
	'#suffix' 			=> ' </div></div></div>',
	'#type' 			=> 'markup',
	//'#markup' 			=> get_all_type_application(),
	);
	
	$form['receiving_dashboard']['markup_regsection_Zone'] = array(
	'#prefix' 	 => '<div class="col-md-4">
						<div class="box box-default# box-success">
							<div class="box-header with-border">
							<h3 class="box-title">Zone</h3>
								<div class="box-tools pull-right">
									<button type="button" class="btn btn-box-tool" data-widget="collapse"><i class="fa fa-minus"></i></button>
									<button type="button" class="btn btn-box-tool" data-widget="remove"><i class="fa fa-times"></i></button>
								</div>
							</div>
					<div class="box-body">
							<div class="col-md-8 cus-img-width-100"><img src="'.$base_root.$base_path.'/sites/all/themes/custom_dashboard/images/wb.jpg"/>',
	'#suffix' 	=> ' </div></div></div></div>',
	'#type' 	=> 'markup',
	//'#markup' 			=> get_all_notice(),
	);
	
	$form['receiving_dashboard']['markup_appplication'] = array(
		'#prefix' 	=> '<div class="box-header with-border">
							<div class="col-lg-12 col-md-12 col-sm-12">
								<h3 class="box-title">All Received Notice List - (FORM-18/FORM-19/FORM-20)</h3>
							</div>
						</div>
						<div class="box-body">
							<div class="col-lg-12 col-md-12 col-sm-12">
								<div class="table-responsive">',
		'#suffix' 	=> '</div></div></div>',
		'#type' 	=> 'markup',
		'#markup' 	=> get_all_notice(),
  	);		  

	  		  
	return $form; 
  }
  
function get_all_notice(){
	global $base_root,$base_path,$user;
	                                                                                                                                 
	$Wcounter				= 0;
	$per_page				= 2;
	
	//********************** FORM 18
	
	$get_all_data18 		= array();
	$rows18[] 				= array();
	$get_all_data18 		= get_form18_data();
	
	$current_page18 		= pager_default_initialize(count($get_all_data18), $per_page);
	
	$chunks 				= array_chunk($get_all_data18, $per_page, TRUE);
	if($current_page18>0){
		$Wcounter 			= $current_page18*$per_page;
	}
	$header18 				= array(
								array('data'=> 'Sl. No.','width' => '6%'),
								array('data'=> 'Factory Details','width' => '20%'),
								array('data'=> 'Accident Date','width' => '18%'),
								array('data'=> 'Type of Accident','width' => '12%'),
								array('data'=> 'Status','width'  => '18%'),
								array('data'=> 'Action','width' => '16%'),
							);
							
	if(!empty($get_all_data18)){
		foreach($chunks[$current_page18] as $details){ //echo "<pre>"; print_r($details);
			$Wcounter++;
			
			$get_uploaded_doc = get_uploaded_document_url($details->uploaded_pdf);
			
			$download_link	 = l('<i class="fa fa-download text-blue" aria-hidden="true"></i> Download', file_create_url($get_uploaded_doc), array('html' => TRUE,'attributes'=>array('title' => 'Download', 'class'=>array(''))));
			
			$view_link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> View', 'receiving-form18-view/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->factory_id), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''), 'target' => '_blank')));
			
		     if($details->notice_status == 'RC')
			 { $status = '<b class="text-red">Pending</b>';}
			 elseif($details->notice_status == 'SC')
			 { $status = '<b class="text-blue">Forwarded to Statistical Cell</b>';}
			 elseif($details->notice_status == 'DC')
			 { $status = '<b class="text-blue">Forwarded to Dy CIF</b>';}
			 elseif($details->notice_status == 'AI')
			 { $status = '<b class="text-blue">Forwarded to Inspector</b>';}	
			 
			if($details->accident_type == 'M')
				{	$accident_type = "Minor"; }	
			if($details->accident_type == 'S')
				{	$accident_type = "Serious"; }	
			if($details->accident_type == 'F')
				{	$accident_type = "Fatal"; }	

			$rows18[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' =>'<b>Name:</b> '.$details->factory_name.'<br><b>Place:</b> '.$details->accident_place,'class' => array('')),
							array('data' =>'<b>Date:</b> '.$details->accident_date.'<br><b>Shift:</b> '.$details->accident_shift,'class' => array('')),
							array('data' =>$accident_type,'class' => array('')),
							array('data' =>$status,'class' => array()),
							array('data' =>$download_link.' '.$view_link,'class' => array()),
						);
		} 
	}
	
	$output18 = theme_table(
	array(
		  'header' 			=> $header18,
		  'rows' 			=> $rows18,
		  'attributes' 	=> array('class' => array('table no-margin remove-odd-even# custom-table-view-dashboard')),
		  //'attributes' 		=> array('class' => array('table table-bordered custom-table-view')),
	      'caption' 		=> '',
		  'colgroups' 		=> array(),
		  'empty' 			=> t("No data found!") 
		)
	).theme('pager');


	//********************** FORM 19
	
	$get_all_data19 		= array();
	$rows19[] 				= array();
	$get_all_data19 		= get_form19_data();
	
	$current_page19 		= pager_default_initialize(count($get_all_data19), $per_page);
	
	$chunks 				= array_chunk($get_all_data19, $per_page, TRUE);
	if($current_page19>0){
		$Wcounter 			= $current_page19*$per_page;
	}
	$header19 				= array(
								array('data'=> 'Sl. No.','width' => '6%'),
								array('data'=> 'Factory Name','width' => '16%'),
								array('data'=> 'Branch Name','width' => '16%'),
								array('data'=> 'Date of occurrence','width' => '14%'),
								array('data'=> 'Time of occurrence','width' => '14%'),
								array('data'=> 'Status','width' => '14%'),
								array('data'=> 'Action','width' => '14%'),
							);
							
	if(!empty($get_all_data19)){
		foreach($chunks[$current_page19] as $details){ //echo "<pre>"; print_r($details);
			$Wcounter++;
			
			$get_uploaded_doc = get_uploaded_document_url($details->uploaded_pdf);
			
			$download_link	 = l('<i class="fa fa-download text-blue" aria-hidden="true"></i> Download', file_create_url($get_uploaded_doc), array('html' => TRUE,'attributes'=>array('title' => 'Download', 'class'=>array(''))));
			
			$view_link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> View', 'receiving-form19-view/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->factory_id), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''), 'target' => '_blank')));

		     if($details->notice_status == 'RC')
			 { $status = '<b class="text-red">Pending</b>';}
			 elseif($details->notice_status == 'SC')
			 { $status = '<b class="text-blue">Forwarded to Statistical Cell</b>';}
			 elseif($details->notice_status == 'DC')
			 { $status = '<b class="text-blue">Forwarded to Dy CIF</b>';}
			 elseif($details->notice_status == 'AI')
			 { $status = '<b class="text-blue">Forwarded to Inspector</b>';}	

			$rows19[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' =>$details->factory_name,'class' => array('')),
							array('data' =>$details->branch_name ,'class' => array('')),
							array('data' =>$details->date_occurrence,'class' => array('')),
							array('data' =>$details->time_occurrence,'class' => array('')),
							array('data' =>$status,'class' => array('color','red')),
							array('data' =>$download_link.' '.$view_link,'class' => array('')),
						);
		} 
	}
	
	$output19 = theme_table(
	array(
		  'header' 			=> $header19,
		  'rows' 			=> $rows19,
		  'attributes' 	=> array('class' => array('table no-margin remove-odd-even# custom-table-view-dashboard')),
		  //'attributes' 		=> array('class' => array('table table-bordered custom-table-view')),
	      'caption' 		=> '',
		  'colgroups' 		=> array(),
		  'empty' 			=> t("No data found!") 
		)
	).theme('pager');
	
	
	//********************** FORM 20
	
	$get_all_data20 		= array();
	$rows20[] 				= array();
	$get_all_data20 		= get_form20_data();
	
	$current_page20 		= pager_default_initialize(count($get_all_data20), $per_page);
	
	$chunks 				= array_chunk($get_all_data20, $per_page, TRUE);
	if($current_page20>0){
		$Wcounter 			= $current_page20*$per_page;
	}
	$header20 				= array(
								array('data'=> 'Sl. No.','width' => '6%'),
								array('data'=> 'Factory Name','width' => '22%'),
								array('data'=> 'Nature of Industry','width' => '22%'),
								array('data'=> 'No. of Patient','width'  => '13%'),
								array('data'=> 'Status','width' => '21%'),
								array('data'=> 'Action','width' => '14%'),
							);
							
	if(!empty($get_all_data20)){
		foreach($chunks[$current_page20] as $details){ //echo "<pre>"; print_r($details);
			$Wcounter++;
			
			$get_uploaded_doc = get_uploaded_document_url($details->uploaded_pdf);
			$patientCount     = db_query("SELECT count(*) FROM {fa_form20_patient_details} where notice_poisoning_id = '$details->id'")->fetchObject()->count;
			
			$download_link	 = l('<i class="fa fa-download text-blue" aria-hidden="true"></i> Download', file_create_url($get_uploaded_doc), array('html' => TRUE,'attributes'=>array('title' => 'Download', 'class'=>array(''))));
			
			$view_link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> View', 'receiving-form20-view/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->factory_id), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''), 'target' => '_blank')));

		     if($details->notice_status == 'RC')
			 { $status = '<b class="text-red">Pending</b>';}
			 elseif($details->notice_status == 'SC')
			 { $status = '<b class="text-blue">Forwarded to Statistical Cell</b>';}
			 elseif($details->notice_status == 'DC')
			 { $status = '<b class="text-blue">Forwarded to Dy CIF</b>';}
			 elseif($details->notice_status == 'AI')
			 { $status = '<b class="text-blue">Forwarded to Inspector</b>';}	

			$rows20[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' =>$details->factory_name,'class' => array('')),
							array('data' =>ucfirst($details->industry_nature),'class' => array('')),
							array('data' =>$patientCount,'class' => array('')),
							array('data' =>$status ,'class' => array('')),
							array('data' =>$download_link.' '.$view_link,'class' => array('')),
						);
		} 
	}
	
	$output20 = theme_table(
	array(
		  'header' 			=> $header20,
		  'rows' 			=> $rows20,
		  'attributes' 	=> array('class' => array('table no-margin remove-odd-even# custom-table-view-dashboard')),
		  //'attributes' 		=> array('class' => array('table table-bordered custom-table-view')),
	      'caption' 		=> '',
		  'colgroups' 		=> array(),
		  'empty' 			=> t("No data found!") 
		)
	).theme('pager');
		
		 return $output18.$output19.$output20;
} 
  
?>