<?php
function  deputy_renewal_list($form, &$form_state) {	
	global $base_root,$base_path,$user;

  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/sky-forms.css');
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
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
		'#prefix' => '<div class="row"><div class="box box-info"><div class="box-header with-border">
              <h3 class="box-title">Final Submitted Application List</h3>
              <div class="box-tools pull-right">
                <button type="button" class="btn btn-box-tool" data-widget="collapse"><i class="fa fa-minus"></i> </button>
                <button type="button" class="btn btn-box-tool" data-widget="remove"><i class="fa fa-times"></i></button>
              </div>
            </div>
			<div class="box-body"><div class="table-responsive">',
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
	$applicant_id = $user->uid;
	$get_all_data = array();
	$rows[] = array();
	$type					='';
	$details				='';
	$relationship			='';
	$address_of_director	='';
	
	$current_status = array('DC','DCBk');
	$get_all_data =  get_renewal_application_list($zoneUserMap,$current_status);
	//echo "<pre>"; print_r($get_all_data); die;
	
	$Wcounter		= 0;
	$per_page		= 10;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header	= array(
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
			$is_backlog =  $details->is_backlog ;
			$Wcounter++;
				if($details->application_status == 'In'){
						$status 			= '<b style="color:blue">Apply For Renewal.</b>';
						$notesheet 			= "Notesheet";
						$licence_register 	= "Licence Register";
						$reg_down			= "Registration Certificate";
						$lic_down			= "";
						$ren_down 			= "Renewal Certificate";
						$details_factor		= "";
						$license_valid		= "";
					 }
				 	 elseif($details->application_status == 'R'){
						$status 			= '<b style="color:#000000">Application Rejected.</b>';
						$notesheet 			= "Notesheet";
						$licence_register 	= "Licence Register";
						$reg_down			= "Registration Certificate";
						$lic_down			= "";
						$ren_down 			= "Renewal Certificate";
						$details_factor		= "";
						$license_valid		= "";
					 }
					 elseif($details->application_status == 'RS'){
						$status 			= '<b style="color:#0D67A2;">Application Re-submitted</b>';
						$notesheet 			= "Notesheet";
						$licence_register 	= "Licence Register";
						$reg_down			= "Registration Certificate";
						$lic_down			= "";
						$ren_down 			= "Renewal Certificate";
						$details_factor		= "";
						$license_valid		= "";
					 }
					 elseif($details->application_status == 'DC'){
					 	$status 			= '<b style="color:red;">Pending</b>';
						$notesheet 			= "Notesheet";
						$licence_register 	= "Licence Register";
						$reg_down			= "Registration Certificate";
						$lic_down			= "";
						$ren_down 			= "Renewal Certificate";
						$details_factor		= "";
						$license_valid		= "";
					 }
					 elseif($details->application_status == 'U'){
					 	$status 			= '<b style="color:#0008ff;">Forworded to Assistance Director</b>';
						$notesheet 			= "Notesheet";
						$licence_register	= "Licence Register";
						$reg_down			= "Registration Certificate";
						$lic_down			= "";
						$ren_down 			= "Renewal Certificate";
						$details_factor		= "";
						$license_valid		= "";
					 }
					  elseif($details->application_status == 'DCBk'){
						$status 			= '<b style="color:red">Backed to Assistance Director</b>';
						$notesheet 			= "Notesheet";
						$licence_register 	= "Licence Register";
						$reg_down			= "Registration Certificate";
						$lic_down			= "";
						$ren_down 			= "Renewal Certificate";
						$details_factor		= "";
						$license_valid		= "";
					 }
					 elseif($details->application_status == 'B'){
					 	$status 			= '<b style="color:#0008ff">Backed to Applicant</b>';
						$notesheet 			= "Notesheet";
						$licence_register 	= "Licence Register";
						$reg_down			= "Registration Certificate";
						$lic_down			= "";
						$ren_down 			= "Renewal Certificate";
						$details_factor		= "";
						$license_valid		= "";
					 }
					
					 
					
					  elseif($details->application_status == 'RP'){
					 	$status 			= '<b style="color:#0D67A2;">Re-payment</b>';
						$notesheet 			= "Notesheet";
						$licence_register 	= "Licence Register";
						$reg_down			= "Registration Certificate";
						$lic_down			= "Licence Certificate";
						$ren_down 			= "Renewal Certificate";
						$details_factor		= "";
						$license_valid		= "";
					 }
					  elseif($details->application_status == 'I'){
						  $status 		= '<b style="color:Green;">Approve Licence & Registration Issue</b>';
					
						  if($details->tm_migrated_flag!='N')
							{
								if($details->approve_dsc_licence_file!=NULL){
									$reg_down	= l('Registration Certificate', $base_url.'/sites/default/files/uploads/factory_cert/'.$details->approve_dsc_reg_file, array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
									$lic_down	= l('Licence Certificate',$base_url.'/sites/default/files/uploads/factory_cert/'.$details->approve_dsc_licence_file, array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
								}else{
									$reg_down	= l('Registration Certificate', file_create_url(get_uploaded_document_url($details->approve_dsc_reg_file_id)), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
									$lic_down	= l('Licence Certificate',file_create_url(get_uploaded_document_url($details->approve_dsc_licence_file_id)), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
								}
							//die($details->approve_dsc_licence_file);	
							
							}else{
								$reg_down	= l('Registration Certificate', file_create_url(get_uploaded_document_url($details->approve_dsc_reg_file_id)), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
								
								$ren_down	= l('Renewal Certificate', file_create_url(get_uploaded_document_url($details->approve_dsc_licence_file_id)), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
								//$ren_down	= l('Renewal Certificate','applicant/apply-online-renewal-licence-generate/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number),array('html' => TRUE,'attributes'=>array('title' => 'Renewal Certificate')));
								}
						
						   
						   $notesheet	= l('Notesheet', 'regsection/registration-view-notesheet/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View Notesheet', 'target' => '_BLANK','class'=>array(''))));
						   
						   $licence_register	= l('Licence Register', 'regsection/registration-licence-journal-genarate-file/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
						   
						   $license_valid = !empty($details->license_valid_upto)?'<span style="color:red">Expire Date:-'.date('dS M Y', strtotime($details->license_valid_upto)).'</span>':"";
						   }
						   
						   $preview_link	= l('<i class="fa fa-eye" aria-hidden="true"></i> View', 'admin/deputyrenewal/view-renewal-deputy/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''))));
						   
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
		
							if($is_backlog == 1){
								if(!empty($details->backlog_plan_approval_dates)){
									$plan_approval = $details->backlog_plan_approval_no.'<b>Dated on - </b>'.$details->backlog_plan_approval_dates;
								}else{
									$plan_approval = $details->backlog_plan_approval_no.'<b>Dated on - </b>';
									}
							}
							elseif(!empty($details->factory_plan_approval_number)){
								$plan_approval = $details->factory_plan_approval_number.'<b>Date - </b>'.$modification_date;
							}else{
								 $plan_approval = '--';
							}
							$regisration_date = !empty($details->registration_date)?date('dS M Y', strtotime($details->registration_date)):"";
							if(!empty($details->factory_registrstion_no)){
								$registration_number = $details->factory_registrstion_no.'<b>,Dated on - </b>'.$regisration_date;
							}else{
								if(!empty($details->backlog_registration_no)){
									$regisration_date = !empty($details->backlog_registration_date)?date('dS M Y', strtotime($details->backlog_registration_date)):"";
									$registration_number = $details->backlog_registration_no.'<b>,Dated on - </b>'.$regisration_date ;
								}else{
									$registration_number = 'Under Process';
								}
								
							}
							$license_date = !empty($details->license_date)?date('dS M Y', strtotime($details->license_date)):"";
							if(!empty($details->factory_license_no)){
								$license_number = $details->factory_license_no.'<b>,Dated on - </b>'.$license_date;
							}else{
								if(!empty($details->backlog_license_number)){
									$license_date = !empty($details->backlog_license_date)?date('dS M Y', strtotime($details->backlog_license_date)):"";
									$license_number = $details->backlog_license_number.'<b>,Dated on - </b>'.$license_date ;
								}else{
									$license_number = 'Under Process';
								}
							}
							
							$factory_type = explode(' ',$details->factory_type);
							if($details->application_status == 'I'){
								$details_factor = '<b>Reg. No.:-</b>'.$registration_number.'<br/><b>License. No.:-</b>'.$license_number;
							}
			
							$rows[] = array( 
								array('data' =>$Wcounter,'class' => array('')),
								array('data' =>$details->factory_name.'<br/>['.$details->factory_type.']<br><b>Zone - </b>'.$details->zone_name,'class' => array('')),
								array('data' =>'<b>Approval No:-</b>'.$plan_approval.'<br/>'.$details_factor,'class' => array('')),
								array('data' =>$details->service_name ,'class' => array('')),
								array('data' =>$Identification.'<br><b>Date - </b>'.$created_date,'class' => array('')),
								array('data' =>$status.'<br><b>Date - </b>'.$modification_date.'<br>'.$license_valid,'class' => array('')),
								array('data' =>$preview_link.'<br/>'.$licence_register.'<br/>'.$notesheet.'<br/>'.$reg_down.'<br/>'.$lic_down.'<br/>'.$ren_down,
									'class' => array('')),
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
function get_renewal_application_list($zoneUserMap){
	
	$fetch_application	= db_select('fa_cafa ', 'cafa');
	$fetch_application->InnerJoin('fa_service_master', 'service_master', 'service_master.id=cafa.service_id');
	$fetch_application->InnerJoin('fa_factory_type_master', 'factory_type', 'factory_type.id=cafa.factory_typeid');
	$fetch_application->InnerJoin('fa_zone', 'zone', 'zone.zone_id=cafa.factory_zone');
	$fetch_application->fields('cafa', array('plan_approve_status','modification_date','application_status','service_id','factory_name','factory_reg_identification_number','id','created_date','factory_typeid','reference_number','plan_approve_identification_number','backlog_plan_approval_no','backlog_plan_approval_date','factory_registrstion_no','factory_license_no','license_date','backlog_license_number','backlog_license_date','backlog_registration_no','backlog_registration_date','factory_plan_approval_number','is_backlog','tm_migrated_flag','approve_dsc_licence_file','approve_dsc_reg_file','license_valid_upto','approve_dsc_reg_file_id','registration_date','approve_dsc_licence_file_id'));
	$fetch_application->fields('service_master', array('service_name'));
	$fetch_application->fields('factory_type', array('factory_type'));
	$fetch_application->fields('zone', array('zone_name'));
	$fetch_application->condition('cafa.factory_zone',$zoneUserMap,'in');
	$fetch_application->condition('cafa.application_status','In','!=');
	$fetch_application->condition('cafa.application_status','F','!=');
	$fetch_application->condition('cafa.application_status','P','!=');
	$fetch_application->condition('cafa.service_id',3);
	$fetch_application	-> orderBy('cafa.id', 'desc');
	$application_result = $fetch_application->execute()->fetchAll(); 
	return $application_result;
	
	}

?>