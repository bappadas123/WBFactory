<?php
function inspector_dashboard($form, &$form_state) {
	global $base_root,$base_path,$user;
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	//drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
      $userid 			= 	$user->uid;
	  $remark_by_name											= get_name($userid);
	  $rid= get_role_id($userid);
	

   /****************************** Check IF Profile is Fillup or Not************************************************/
   $status = getUserProfileStatus($user->uid);
   if(empty($status['one_time_pass_flag']) || $status['one_time_pass_flag'] == '0') {
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
	// FOR ESCALLATION //
	//$escallation = get_applcation_escalate($zoneUserMap);

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
	
	$form['inspector_dashboard']['icon_regsection'] = array(
	 	'#prefix' 			=> '<div class="row">
       			 				<div class="col-md-3 col-sm-6 col-xs-12">
          						<div class="info-box"><span class="info-box-icon bg-aqua"><i class="fa fa-handshake-o" aria-hidden="true"></i></span>
            					<div class="info-box-content"><span class="info-box-text">Forward of Factory Registration</span><span class="info-box-number">90<small>%</small></span></div>',
		'#suffix' 			=> '</div></div>',
		'#type' 			=> 'markup',
		//'#markup' 			=> get_all_type_application(),
  	);	
		$form['inspector_dashboard']['icon_regsection2'] = array(
	 	'#prefix' 			=> '<div class="col-md-3 col-sm-6 col-xs-12">
          						<div class="info-box"><span class="info-box-icon bg-red"><i class="fa fa-address-book-o" aria-hidden="true"></i></span>
           						<div class="info-box-content"><span class="info-box-text">Registration and grant of Licence</span><span class="info-box-number">41,410</span></div>',
		'#suffix' 			=> '</div></div>',
		'#type' 			=> 'markup',
		//'#markup' 			=> get_all_type_application(),
  	);	
		$form['inspector_dashboard']['icon_regsection3'] = array(
	 	'#prefix' 			=> '<div class="col-md-3 col-sm-6 col-xs-12">
          						<div class="info-box"><span class="info-box-icon bg-green"><i class="fa fa-address-card-o" aria-hidden="true"></i></span>
            					<div class="info-box-content"><span class="info-box-text">Renewal of Factory Licence</span><span class="info-box-number">760</span></div>',
		'#suffix' 			=> '</div></div>',
		'#type' 			=> 'markup',
		//'#markup' 			=> get_all_type_application(),
  	);	
		$form['inspector_dashboard']['icon_regsection4'] = array(
	 	'#prefix' 			=> '<div class="col-md-3 col-sm-6 col-xs-12">
          						<div class="info-box"><span class="info-box-icon bg-yellow"><i class="fa fa-list-alt" aria-hidden="true"></i></span>
            					<div class="info-box-content"><span class="info-box-text">Directorate of Factories</span><span class="info-box-number">2,000</span></div>',
		'#suffix' 			=> '</div></div>',
		'#type' 			=> 'markup',
		//'#markup' 			=> get_all_type_application(),
  	);	
	
	$form['inspector_dashboard']['markup_regsection_details'] = array(
	'#prefix' 				=> '<div class="col-md-8"><div class="box box-primary"><div class="box-header with-border"><h3 class="box-title">Details</h3><div class="box-tools pull-right"><button type="button" class="btn btn-box-tool" data-widget="collapse"><i class="fa fa-minus"></i></button></div></div>
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
	
	'#suffix' 			=> '</div></div></div></div>',
	'#type' 			=> 'markup',
	//'#markup' 			=> get_all_type_application(),
	);
	
	$form['inspector_dashboard']['markup_regsection_Zone'] = array(
	'#prefix' 			=> '<div class="col-md-4"> <div class="box box-default# box-success"> <div class="box-header with-border"> <h3 class="box-title">Zone</h3> <div class="box-tools pull-right"><button type="button" class="btn btn-box-tool" data-widget="collapse"><i class="fa fa-minus"></i> </button><button type="button" class="btn btn-box-tool" data-widget="remove"><i class="fa fa-times"></i></button></div></div><div class="box-body"><div class="col-md-8 cus-img-width-100"><img src="'.$base_root.$base_path.'/sites/all/themes/custom_dashboard/images/wb.jpg"/>',
	
	'#suffix' 			=> '</div></div></div></div>',
	'#type' 			=> 'markup',
	//'#markup' 			=> get_all_type_application(),
	
	);
	$form['inspector_dashboard']['begin'] = array(
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
	
	$form['inspector_dashboard']['zone_id'] = array(
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
	
	$form['inspector_dashboard']['all_app'] = array(
		'#type'   => 'markup',
		'#markup' => get_all_application($zoneUserMap),
		'#prefix' => '<div id="table_app_replace_div"><div class="col-md-12">',
		'#suffix' => '</div></div>'
  	);	
	$form['inspector_dashboard']['end'] = array(
		'#prefix' => '',
		'#suffix' => '</div></div><div class="box-footer clearfix"> <a href="javascript:void(0)" class="btn btn-sm btn-default btn-flat# pull-right">View All</a> </div></div></div></div>'
	);	  		  
	return $form; 
  }
  function get_all_application($zoneUserMap){
	
	global $base_root,$base_path,$user;
	$applicant_id = $user->uid;
	 $remark_by_name = get_name($applicant_id);
	  $rid= get_role_id($applicant_id);
	$get_all_data = array();
	$rows[] = array();
	$type					='';
	$details				='';
	$relationship			='';
	$address_of_director	='';
	
	$get_all_data =  get_reg_application_list($zoneUserMap);
	
	//echo "<pre>"; print_r($get_all_data); die;
	
	$Wcounter		= 0;
	$per_page		= 10;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header 		= array(
					array('data'=> 'Sl. No.','width' => '6%'),
					array('data'=> 'Factory Details','width' => '13%'),								
					array('data'=> 'Plan Approval No. / License No. &amp; Date'),								
					array('data'=> 'e-Service','width' => '17%'),
					array('data'=> 'Application No. &amp; Date','width' => '17%'),
					array('data'=> 'Status &amp; Date','width' => '16%'),							
					array('data'=> 'Action','width' => '7%'),
							);
	if(!empty($get_all_data)){
		
		foreach($chunks[$current_page] as $details){ 
			$is_backlog =  $details->is_backlog ;
			$Wcounter++;
					 if($details->application_status == 'U'){
						 $reg_down			= 'Registration Certificate';
						$lic_down			= '';
						$licence_register	= 'Licence register';
						$notesheet			= 'Notesheet';
						  $status 			= '<b style="color:red;">Final submitted</b>';
						$license_valid 		= "";
						$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
						$ack_link 			= l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
					
						
					 }
					elseif($details->application_status == 'R'){
						 $reg_down			= 'Registration Certificate';
						$lic_down			= '';
						$licence_register	= '';
						$notesheet			= '';
						$status 			= '<b style="color:#000000">Application Rejected.</b>';
						$license_valid 		= '';
						$details_factor 	= '';
						$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
						$ack_link 			= l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
					
					 }
					elseif($details->application_status == 'RS'){
						 $reg_down			= 'Registration Certificate';
						$lic_down			= '';
						$licence_register	= '';
						$notesheet			= '';
						$status 			= '<b style="color:#0D67A2;">Application Re-submitted</b>';
						$license_valid 		= '';
						$details_factor 	= '';
						$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
						$ack_link 			= l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
					
					 }
					elseif($details->application_status == 'ABk'){
						   $reg_down			= 'Registration Certificate';
						$lic_down			= '';
						$licence_register	= '';
						$notesheet			= '';
						$status 			= '<b style="color:red">Backed to Inspector</b>';
						$license_valid 		= '';
						$details_factor 	= '';
						$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
						$ack_link 			= l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
					
					 }
					elseif($details->application_status == 'B'){
						 $reg_down			= 'Registration Certificate';
						$lic_down			= '';
						$licence_register	= '';
						$notesheet			= '';
						 $status 			= '<b style="color:#0008ff">Backed to Applicant</b>';
						$license_valid 		= '';
						$details_factor 	= '';
						$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
						$ack_link 			= l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
					
					 }
					elseif($details->application_status == 'DC'){
						 $reg_down			= 'Registration Certificate';
						$lic_down			= '';
						$licence_register	= '';
						$notesheet			= '';
						$status 			= '<b style="color:green">Forward to DY. CIF</b>';
						$license_valid 		= '';
						$details_factor 	= '';
						$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
						$ack_link 			= l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
					
					 }
					elseif($details->application_status == 'DCBk'){
						 $reg_down			= 'Registration Certificate';
						$lic_down			= '';
						$licence_register	= '';
						$notesheet			= '';
						$status 			= '<b style="color:#0D67A2;">Back to DY. CIF</b>';
						$license_valid 		= '';
						$details_factor 	= '';
						$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
						$ack_link 			= l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
					
					 }                                            
					elseif($details->application_status == 'JC'){
						 $reg_down			= 'Registration Certificate';
						$lic_down			= '';
						$licence_register	= '';
						$notesheet			= '';
						 $status 			= '<b style="color:green;">Forward to Jt. Chief</b>';
						$license_valid 		= '';
						$details_factor 	= '';
						$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
						$ack_link 			= l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
					
					 }
					elseif($details->application_status == 'RP'){
						 $status 			= '<b style="color:#0D67A2;">Re-payment</b>';
						$details_factor 	= '';
						$reg_down			= 'Registration Certificate';
						$lic_down			= '';
						$licence_register	= '';
						$notesheet			= '';
						$license_valid 		= '';
						$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
						$ack_link 			= l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
					
					 }
					 
					 $approve_dsc_reg_file_id		= 	$details->approve_dsc_reg_file_id;
					$approve_dsc_licence_file_id	= 	$details->approve_dsc_licence_file_id;
					$dsc_licence_register_file		= 	$details->approve_dsc_reg_licence_file_id;
					$period_for_application 		=	$details->period_for_application;
					if($rid==9){
						$preview_link	= l('<i class="fa fa-eye" aria-hidden="true"></i> View', '/admin/regsection/view-register-factory-information/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''))));  
					}if($rid==10){
						$preview_link	= l('<i class="fa fa-eye" aria-hidden="true"></i> View', '/admin/ddregistration/view-register-factory-information-dd/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''))));  
					}
					
					 
					if($details->application_status == 'I'){
						$status 			= '<b style="color:Green;">Issued</b>';
						$license_valid = !empty($details->license_valid_upto)?'<span style="color:red">Expire Date:-'.date('dS M Y', strtotime($details->license_valid_upto)).'</span>':"";
							 
				  if($details->tm_migrated_flag!='N')
					{
				//	echo 'LLLL'.$details->approve_dsc_reg_file;
						$reg_down	= l('Registration Certificate', $base_url.'/sites/default/files/uploads/factory_cert/'.$details->approve_dsc_reg_file, array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
							
						$lic_down	= l('Licence Certificate',$base_url.'/sites/default/files/uploads/factory_cert/'.$details->approve_dsc_licence_file, array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					}else{
						$reg_down	= l('Registration Certificate', file_create_url(get_uploaded_document_url($details->approve_dsc_reg_file_id)), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					//	$lic_down	= l('Licence Certificate',file_create_url(get_uploaded_document_url($details->approve_dsc_licence_file_id)), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
						}
					 
						$notesheet			= l('Notesheet', 'regsection/registration-view-notesheet/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View Notesheet', 'target' => '_BLANK','class'=>array(''))));
						$licence_register	= l('Licence Register', 'regsection/registration-licence-journal-genarate-file/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
						$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
						$ack_link 			= l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
					
				}
				
					$Identification = $details->factory_reg_identification_number;
						
				if(empty($Identification)){
						$Identification = 'Under Process';
				}
				if(!empty($details->created_date)){
						$created_date = date('dS M Y', strtotime($details->created_date));
				}else{
						$created_date = '';
				}
				
				if(!empty($details->plan_approval_date)){
						$plan_approval_date = date('dS M Y', strtotime($details->plan_approval_date));
				}else{
						$plan_approval_date = '';
				 }
				 
				if($is_backlog == 1){
					$plan_approval = $details->backlog_plan_approval_no.' <b>dated on </b>'.date('dS M Y', strtotime($details->backlog_plan_approval_date));
				}
				elseif(!empty($details->factory_plan_approval_number)){
						$plan_approval = $details->factory_plan_approval_number.'<b> dated on</b> '.$plan_approval_date;
				}
				else{
						$plan_approval = '--';
				}
				
				if(!empty($details->modification_date)){
						$modification_date = date('dS M Y', strtotime($details->modification_date));
					}else{
						$modification_date = '';
					}
				
				
				$regisration_date = !empty($details->registration_date)?date('dS M Y', strtotime($details->registration_date)):'';
				
				if(!empty($details->factory_registrstion_no)){
					$registration_number = $details->factory_registrstion_no.'<b>,Dated on - </b>'.$regisration_date;
				}else{
					if(!empty($details->backlog_registration_no)){
						$regisration_date = !empty($details->backlog_registration_date)?date('dS M Y', strtotime($details->backlog_registration_date)):$details->registration_date;
						$registration_number = $details->backlog_registration_no.'<b>,Dated on - </b>'.$regisration_date ;
					}else{
						$registration_number = 'Under Proess';
					}	
				}
				
				$license_date = !empty($details->license_date)?date('dS M Y', strtotime($details->license_date)):'';
					if(!empty($details->factory_license_no)){
						$license_number = $details->factory_license_no.'<b>,Dated on - </b>'.$license_date;
					}else{
						if(!empty($details->backlog_license_number)){
							$license_date = !empty($details->backlog_license_date)?date('dS M Y', strtotime($details->backlog_license_date)):$details->license_date;
							$license_number = $details->backlog_license_number.'<b>,Dated on - </b>'.$license_date ;
						}else{
							$license_number = 'Under Proess';
						}
					}
					if($details->application_status == 'I'){
					$details_factor = '<br><b>Reg. No.:-</b>'.$registration_number.'<br><b>License. No.:-</b>'.$license_number;
					
					}
					if($details->factory_typeid==3){
					 $plan_information = '<b>Under Section 85 (Plan not required.)</b>';
					}else{
						$plan_information = '<b>Plan Approval No:-</b>'.$plan_approval ;
					}
			
					$rows[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' =>$details->factory_name.'<br>['.$details->factory_type.']<br><b>Zone -</b>'.$details->zone_name,'class' => array('')),
							array('data' => $plan_information.$details_factor,'class' => array('')),
							array('data' =>$details->service_name ,'class' => array('')),
							array('data' =>$Identification.'<br><b>Date - </b>'.$created_date,'class' => array('')),
							array('data' =>$status.'<br><b>Date - </b>'.$modification_date.'<br>'.$license_valid,'class' => array('')),
							array('data' =>$preview_link.'<br/>'.$notesheet.'<br/>'.$reg_down.'<br/>'.$licence_register.'<br/>'.$lic_down.'<br/>'.$payment_deatils.'<br/>'.$ack_link,'class' => array('')),
						);
				}
		}
	
	$output = theme_table(
	array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('class' => array('table no-margin remove-odd-even# custom-table-view-dashboard')),
		 // 'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") 
		)
	).theme('pager');	
		 return $output;

	
}
  
  ?>