<?php 
function  amendment_list($form, &$form_state) {	
	global $base_root,$base_path,$user;
  
   /********************************** End Profile is Fillup Cheaking************************************************/
  	drupal_add_css(drupal_get_path('module', 'amendment') . '/css/sky-forms.css');
  	drupal_add_css(drupal_get_path('module', 'amendment') . '/css/form-design.css');
	//drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	$form = array();
	
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
		foreach($zoneUserMapResult as $v){
			$zoneDropDown[$v->zone_id] = $v->zone_name;
		}
	}
	
	$form['begin'] = array(
		'#prefix' => '<div class="row">
						<div class="box box-info">
							<div class="box-header with-border">
             					<div class="box-tools pull-right">
                					<button type="button" class="btn btn-box-tool" data-widget="collapse"><i class="fa fa-minus"></i> </button>
                					<button type="button" class="btn btn-box-tool" data-widget="remove"><i class="fa fa-times"></i></button>
								</div>
							</div>
						<div class="box-body">
							<div class="table-responsive">',
		'#suffix' => ''
	);
	
	$form['zone_id'] = array(
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
	
	$form['all_app'] = array(
		'#type'   => 'markup',
		'#markup' => get_all_application($zoneUserMap),
		'#prefix' => '<div id="table_app_replace_div"><div class="col-md-12">',
		'#suffix' => '</div></div>'
  	);	
	$form['end'] = array(
		'#prefix' => '',
		'#suffix' => '</div></div></div></div>'
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
	
	$get_all_data =  get_amend_application_list($zoneUserMap);
	//print_r($get_all_data);die;
	$Wcounter		= 0;
	$per_page		= 10;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header 		= array(	array('data'=> 'Sl. No'),
								array('data'=> 'Factory Details'),
								array('data'=> 'Plan Approval No./License No & Date'),
								array('data'=> 'e-Service'),
								array('data'=> 'Application Number & Date'),
								array('data'=> 'Status & Date'),
								array('data'=> 'Action'),
							);
							
	if(!empty($get_all_data)){
		
		foreach($chunks[$current_page] as $details){  
		 $is_backlog =  $details->is_backlog ;
			$Wcounter++;
				 	if($details->application_status == 'U'){
				 		$reg_down			= '';
						$lic_down			= '';
						$amendment_certificate  = '';
					  	$status 			= '<b style="color:red;">Final submitted</b>';
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
					
						$notesheet	= l('Notesheet', 'amendment-section/amendment-view-notesheet/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View Notesheet', 'target' => '_BLANK','class'=>array(''))));
						$licence_register	= l('Licence Register', 'amendment-section/ledger-amendment-file/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				
					 }
					elseif($details->application_status == 'R'){
						$status 			= '<b style="color:#000000">Application Rejected.</b>';
						$amendment_certificate  = '';
					 }
					elseif($details->application_status == 'RS'){
						$status 			= '<b style="color:#0D67A2;">Application Re-submitted</b>';
						$amendment_certificate  = '';
					 }
					elseif($details->application_status == 'ABk'){
						$status 			= '<b style="color:red">Backed to Inspector</b>';
						$amendment_certificate  = '';
					 }
					elseif($details->application_status == 'B'){
					 	$status 			= '<b style="color:#0008ff">Backed to Applicant</b>';
						$amendment_certificate  = '';
					 }
					
					elseif($details->application_status == 'DC'){
					 	$status 			= '<b style="color:green">Forward to DY. CIF</b>';		
						$amendment_certificate  = '';
					 }
					elseif($details->application_status == 'DCBk'){
						$status 			= '<b style="color:#0D67A2;">Back to DY. CIF</b>';
						$amendment_certificate  = '';
					 }                                            
					elseif($details->application_status == 'JC'){
					 	$status 			= '<b style="color:green;">Forward to Jt. Chief</b>';
						$amendment_certificate  = '';
					 }
					elseif($details->application_status == 'RP'){
					 	$status 			= '<b style="color:#0D67A2;">Re-payment</b>';
						$amendment_certificate  = '';
					 }
					 
					$approve_dsc_reg_file_id		= 	$details->approve_dsc_reg_file_id;
					$approve_dsc_licence_file_id	= 	$details->approve_dsc_licence_file_id;
					$dsc_licence_register_file		= 	$details->approve_dsc_reg_licence_file_id;
					$period_for_application 		=	$details->period_for_application;
					
					$preview_link	= l('<i class="fa fa-eye" aria-hidden="true"></i> View', 'admin/inspectoramendment/view-amendment-inspector/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array('')))); 
					 
					if($details->application_status == 'I' ){
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
					
						$notesheet	= l('Notesheet', 'amendment-section/amendment-view-notesheet/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View Notesheet', 'target' => '_BLANK','class'=>array(''))));
						$licence_register	= l('Licence Register', 'amendment-section/ledger-amendment-file/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					
				if($details->service_id == 8){
						// die($details->service_id.'-------'.$details->approve_amendment_file_id);
						$amendment_certificate  =l('Amendment Certificate',file_create_url(get_uploaded_document_url($details->approve_amendment_file_id)), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				}
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
					$regisration_date = !empty($details->backlog_registration_date)?date('dS M Y', strtotime($details->backlog_registration_date)):"";
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
					$license_date = !empty($details->backlog_license_date)?date('dS M Y', strtotime($details->backlog_license_date)):"";
					$license_number = $details->backlog_license_number.'<b>,Dated on - </b>'.$license_date ;
				}else{
					$license_number = 'Under Proess';
				}
			}
			//echo $details->application_status;die;
			if($details->application_status == 'I' || $details->application_status == 'U'){
				$details_factor = '<br><b>Reg. No.:-</b>'.$registration_number.'<br><b>License. No.:-</b>'.$license_number;
			}

			$rows[] = array( 
				array('data' =>$Wcounter,'class' => array('')),
				array('data' =>$details->factory_name.'<br>['.$details->factory_type.']<br><b>Zone -</b>'.$details->zone_name,'class' => array('')),
				array('data' =>'<b>Plan Approval No:-</b>'.$plan_approval .$details_factor,'class' => array('')),
				array('data' =>$details->service_name ,'class' => array('')),
				array('data' =>$Identification.'<br><b>Date - </b>'.$created_date,'class' => array('')),
				array('data' =>$status.'<br><b>Date - </b>'.$modification_date.'<br>'.$license_valid,'class' => array('')),
				array('data' =>$preview_link.'<br/>'.$notesheet.'<br/>'.$reg_down.'<br/>'.$licence_register.'<br/>'.$lic_down.'<br/>'.$amendment_certificate,'class' => array('')),
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