<?php
function backlog_add_factory_preview($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$linknumber) {	

	global $base_root, $base_path,$user;
	$userid 			= $user->uid;
	$user_role 			= array_keys($user->roles);
    $urole  			= $user_role[1];

	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	

	
	if (!empty($application_id)) {
        $get_fa_cafa           				= 	get_fa_cafa($application_id);
       	$application_status      			= 	$get_fa_cafa['application_status'];
		$plan_approve_status      			= 	$get_fa_cafa['plan_approve_status'];
		$factory_identification_number		= 	$get_fa_cafa['factory_reg_identification_number'];
		$referance_number					= 	$get_fa_cafa['reference_number'];
		$is_basic_information_tab    		=   $get_fa_cafa['is_year_calculation_tab'];
		$created_by							= $get_fa_cafa['created_by'];
    }
	
	
	
	 if(empty($is_basic_information_tab)){
		  		drupal_set_message(('Please fill up the second tab than fill up the worker information'),'warning');			
			drupal_goto('applicant/backlog-factory-add/details-worker-renewal/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$referance_number) ;
	 } 

	$a=0;

	
	$form = array();
	//echo $referance_number;die();
	$form['serviceid_hidden'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> $serviceid,
	);
	$form['factorytypeid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $factory_typeid
	);
	$form['reference_no_hidden'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> encryption_decryption_fun('encrypt', $referance_number)
	);
	$form['applicationid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $applicationid
	);
	$form['linknumber_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $linknumber
	);
	$form['linkdate_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $linkdate
	);	
	$form['flagmapp_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $flagmapp
	);
	$form['application_preview'] = array(
        '#type' => 'fieldset',
        '#title' => t('A.Factory Details'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
	$form['application_preview']['application_preview_table'] 	= array(
  			'#type'		=> 'markup',
			'#markup'	=> renewal_application_preview($application_id,$service_id,$factory_type_id,$referance_number)	
	);	
	
	
	if($urole==4){
		 $form['factory_part_certificates'] = array(
        '#type' => 'fieldset',
        '#title' => t('B.Uplaod Your all documents'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
		
	
		$form['factory_part_certificates']['reg_file'] = array(
					'#type' 				 => 'managed_file',
					'#title'				 => '(i).Registration certificates:-'.$file_url,
					'#upload_validators' 	 => array('file_validate_extensions' => array('pdf'), 'file_validate_size' => array(50*1024*1024)),
					'#upload_location' 		 => 'public://upload/upload_pdf/',
					'#process' 				 => array('import_my_file_element_process'),
					'#attributes' 			 => array('id' => '','autocomplete' => 'off','class'=>array('form-control')),
					'#prefix' 				 => '<div class="row"><div class="col-md-4>',
			  		'#suffix' 				 => '</div>',
					'#required' 			 => TRUE,
			);
		$form['factory_part_certificates']['lic_file'] = array(
					'#type' 				 => 'managed_file',
					'#title'				 => '(ii).License certificates:-'.$file_url,
					'#upload_validators' 	 => array('file_validate_extensions' => array('pdf'), 'file_validate_size' => array(50*1024*1024)),
					'#upload_location' 		 => 'public://upload/upload_pdf/',
					'#process' 				 => array('import_my_file_element_process'),
					'#attributes' 			 => array('id' => '','autocomplete' => 'off','class'=>array('form-control')),
					'#prefix' 				 => '<div class="col-md-4>',
			  		'#suffix' 				 => '</div>',
					
			);
	$form['factory_part_certificates']['plan_file'] = array(
					'#type' 				 => 'managed_file',
					'#title'				 => '(iii).Plan Approval Letter:-'.$file_url,
					'#upload_validators' 	 => array('file_validate_extensions' => array('pdf'), 'file_validate_size' => array(50*1024*1024)),
					'#upload_location' 		 => 'public://upload/upload_pdf/',
					'#process' 				 => array('import_my_file_element_process'),
					'#attributes' 			 => array('id' => '','autocomplete' => 'off','class'=>array('form-control')),
					'#prefix' 				 => '<div class="col-md-4>',
			  		'#suffix' 				 => '</div</div>',
					
			);
	}
	
	
	
	$form['finalAgree'] 	= array(
			'#prefix' 		=> '<div class="col-md-12 col-xs-12">',	
			'#suffix' 		=> '</div>',
			'#type' 		=> 'checkbox',
			'#title' 		=> 'I hereby declare that the particulars given above are true the best of my knowledge and belief.',
			'#attributes'	=> array('id' => 'finalAgreeId','onchange' => 'return checkFinalAppCheckBox()'),
			'#required' 	=> TRUE,
	);
	/*$form['submit'] = array (
			'#type' 		=> 'submit',
			'#attributes' 	=> array('class' => array('btn btn-info'),'onclick' => 'if(!confirm("Are you sure to continue ?"){return false;}'),
			'#value' 		=> 'Save & Continue'										  
	);*/
	$form['back_link'] = array(
		'#prefix' => '<div class="row"><div class="col-md-1">',
		'#suffix' => '</div>',
		'#markup' => l(t('<i class="fa fa-angle-left" aria-hidden="true"></i> Back'), 'applicant/applicant-dasboard/', array('html' => TRUE,'attributes' => array('class' => array('btn btn-dark pull-left'))))
  	);
    if(($application_status == 'In'|| $created_by==NULL) ){
    $form['submit'] = array(
        '#prefix' => '<div class="col-md-1">',
        '#suffix' => '</div>',
        '#attributes' => array('class' => array('btn btn-success')),
        '#type' => 'submit',
        '#value' => 'Save'
    );
	if(!empty($application_id)){
	$form['preview_link'] = array(
		'#prefix' => '<div class="col-md-10">',
        '#suffix' => '</div>',
  	//'#markup' => l(t('Preview as PDF'), 'applicant/applicant-dasboard/', array('html' => TRUE,'attributes' => array('class' => array('btn btn-dark space-left') )))
		'#markup' => l('PRINT DRAFT COPY', 'regsection/preview-varse-all-information/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'Preview as PDF','class'=>array('btn btn-warning pull-right'))))
  		);
		}
	}else{
		$form['markup'] = array(
        '#suffix' => '</div></div>',
        '#type' => 'markup',
       
    );
	
	}     	
return $form;

}

function renewal_application_preview($application_id,$service_id,$factory_typeid,$reference_number){
	global $base_root,$base_path,$user;
	$output = "";
	$get_all_data =  get_fa_cafa($application_id);
	if($get_all_data['factory_owershiptype']=="pv"){
   			$ownership_type = "Pvt Ltd Company";
   		}if($get_all_data['factory_owershiptype']=="ltd"){
   				$ownership_type = "Ltd Company";
   		}if($get_all_data['factory_owershiptype']=="par_firm"){
   				$ownership_type = "Partnership Firm";
   		}if($get_all_data['factory_owershiptype']=="pro_firm"){
   				$ownership_type = "Proprietorship Firm";
   		}if($get_all_data['factory_owershiptype']=="govt"){
   				$ownership_type = "Govt";
   		}if($get_all_data['factory_owershiptype']=="psu"){
   				$ownership_type = "PSU";
   		}if($get_all_data['factory_owershiptype']=="llp"){
   				$ownership_type = "Limited Liability Partnership";
   		}if($get_all_data['factory_owershiptype']=="cooperative"){
   				$ownership_type = "Co-operative";
   		}if($get_all_data['factory_owershiptype']=="registered"){
   				$ownership_type = "Registered Society under Society Register";
   		}if($get_all_data['factory_owershiptype']=="localbody"){
   				$ownership_type = "Local Body";
   		}if($get_all_data['factory_owershiptype']=="others"){
   				$ownership_type = "Others";
   		}
	$is_backlog = $get_all_data['is_backlog'];
	if($is_backlog == 1){
		$plan_approval_no = !empty($get_all_data['backlog_plan_approval_no'])?$get_all_data['backlog_plan_approval_no']:'NA';
		$plan_approval_date =!empty($get_all_data['backlog_plan_approval_date'])?date('dS M Y', strtotime($get_all_data['backlog_plan_approval_date'])):'NA';
	}else{
		$plan_approval_no = !empty($get_all_data['factory_plan_approval_number'])?$get_all_data['factory_plan_approval_number']:'NA';
		$plan_approval_date = !empty($get_all_data['plan_approval_date'])?date('dS M Y', strtotime($get_all_data['plan_approval_date'])):'NA';
	}
	$reg_no  = !empty($get_all_data['backlog_registration_no'])?$get_all_data['backlog_registration_no']:'NA';
	$registration_date  = !empty($get_all_data['backlog_registration_date'])?date('dS M Y', strtotime($get_all_data['backlog_registration_date'])):'NA';
	
	if($reg_no!= 'NA'){
		
		$reg_details = $reg_no .' ,dated on '.$registration_date;
	}else{
		$reg_details ='NA' ;
	}
	
	$license_number  = !empty($get_all_data['backlog_license_number'])?$get_all_data['backlog_license_number']:'NA';
	$valid_upto  = !empty($get_all_data['license_valid_upto'])?date('dS M Y', strtotime($get_all_data['license_valid_upto'])):'NA';
	$license_date  = !empty($get_all_data['backlog_license_date'])?date('dS M Y', strtotime($get_all_data['backlog_license_date'])):'NA';
	
	if($license_number!= 'NA'){
		
		$license_details = $license_number .' ,dated on '.$license_date.' and validup to date '.$valid_upto;
	}else{
		$license_details ='NA' ;
	}
	
	
	$owner_address_details = !empty($get_all_data['addrline_premises'])?$get_all_data['addrline_premises'].',':'';
	$owner_address_details.= $get_all_data['owner_country_address'].',<br/>'.country_name($get_all_data['owner_country']);
	$getdata_factory_location	=  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address_location 	= $get_all_data['addrline'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_factory_location).'<br/>JL No: '.$get_all_data['jl_no'].'<br/>Mouza Nane: '.$get_all_data['mouza_name'];
	$getdata_headoffice_address =  array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
	$headoffice_address 		= $get_all_data['addrline_off'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_headoffice_address);
	$passport_details = !empty($get_all_data['occupier_passport_premises'])?'Passport No-'.$get_all_data['occupier_passport_premises'].',<br/>Passport Issue Date-'.$get_all_data['date_of_issue_premises'].',<br/>Passport Expiry date-'.$get_all_data['date_of_expiry_premises']:'';
	$getdata_owner_address 		=  array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
	$owner_address 				=	$owner_address_details.'<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_owner_address);
	$previous_details			=  get_previous_details_view($application_id,$reference_number,$factory_typeid,$service_id);
	foreach($previous_details as $pre_row){
		$is_previous		 	= $pre_row->is_previous;
		
		if($is_previous == "Yes"){
			$view = "";
		}
	}
	
		ctools_include('ajax');
        ctools_include('modal');
	    ctools_modal_add_js();	 
		$worker_link=$base_root.$base_path.'view-worker-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_t=ctools_modal_text_button(t('View Worker(s)'), $worker_link ,t('View Details)')) ;
		
		$amaned_link=$base_root.$base_path.'view-amend_power_worker/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_amend=ctools_modal_text_button(t('Amendment Notice'), $amaned_link ,t('Amendment Notice)')) ;
		
		$occupier_details=$base_root.$base_path.'view-occuiper-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_occuiper=ctools_modal_text_button(t('View Occupier(s)'), $occupier_details ,t('View Details)')) ;	
		
		$director_details=$base_root.$base_path.'view-director-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_director=ctools_modal_text_button(t('View Director(s)'), $director_details ,t('View Details)')) ;	
		
		//$manufacturing_details=$base_root.$base_path.'view-manufacturing-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		//$link_manufacturing=ctools_modal_text_button(t('View Manufacturing Process(s)'), $manufacturing_details ,t('View Details)')) ;	
		
		$documents_details=$base_root.$base_path.'view-documents-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_documents=ctools_modal_text_button(t('View Documents list'), $documents_details ,t('View Details)')) ;
		
		$manager_details=$base_root.$base_path.'view-manager-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_manager=ctools_modal_text_button(t('View Manager(s)'), $manager_details ,t('View Details)')) ;
		
		//$power_details=$base_root.$base_path.'view-power-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		//$link_power=ctools_modal_text_button(t('View Power Details'), $power_details ,t('View Details)')) ;
		$owner_details=$base_root.$base_path.'view-owner-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_owner =ctools_modal_text_button(t('View owner Details'), $owner_details ,t('View Details')) ;
		
		
		$factory_zone_date = get_factory_zone_name($get_all_data['factory_zone']);
		
		if(!empty($get_all_data['enargy_no'])){ $enargy_no = $get_all_data['enargy_no']; }else{$enargy_no =  'NA';}
			if(!empty($get_all_data['cin_no'])){ $cin_no = $get_all_data['cin_no']; }else{$cin_no =  'NA';}
			
		$power_generating_station 	= get_power_generating_station($application_id,$reference_number,$factory_typeid,$service_id);
		foreach($power_generating_station as $power){
			$power_details = $power->installed_power.'('.$power->power_unit.')';
		}
		$nature_details = get_manufacturing($application_id,$service_id,$factory_typeid,$reference_number);
		foreach($nature_details as $nature){
			$nature_work = $nature->nature_manufacturing;
		}
		if($get_all_data['wbpcb_category_name']==1){$consent ='Red'; $wbpcb_reference_no = $get_all_data['wbpcb_reference_no'];$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));}
			if($get_all_data['wbpcb_category_name']==2){$consent ='Green'; $wbpcb_reference_no = $get_all_data['wbpcb_reference_no'];$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));}
			if($get_all_data['wbpcb_category_name']==3){$consent ='Orange'; $wbpcb_reference_no = $get_all_data['wbpcb_reference_no'];$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));}
			
			if($get_all_data['wbpcb_category_name']== 4){
				$consent ='White'; 
				$wbpcb_reference_no = 'NA'; 
				$wbpcb_ref_date = 'NA';
			
				 $file_url =	'<a href='.$base_path.'document-list/view-appliction-form/'.encryption_decryption_fun('encrypt', $service_id).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt', $factory_typeid).'/'.encryption_decryption_fun('encrypt', $reference_number).'/'.encryption_decryption_fun('encrypt','INT').' target= "_BLANK" onclick = "popIt(this.href);return false;">Intimation Letter</a>';
				
				}
			if($get_all_data['wbpcb_category_name']==5){$consent ='Exempted'; $wbpcb_reference_no = 'NA';$wbpcb_ref_date = 'NA';}
		
		$details = $consent.'<br>WBPCB referance no. = '.$wbpcb_reference_no.'<br>WBPCB referance no = '.$wbpcb_ref_date.'<br>'.$file_url;
		if($plan_approval_no != 'NA'){
			$plan_details = $plan_approval_no.' dated on '.$plan_approval_date;
		}else{
			$plan_details = 'Not Avaliable';
		}
		
	$output .='<div class="row">
				<table class="table table-bordered"> <tr>
   								<th>Parameters</th>
   								<th>Inputs</th>
								</tr>';
	
	$output .='<tr><td colspan="2">A.Factory Information</td></tr>
				<tr><td>(i). Name of the factory</td><td>'.$get_all_data['factory_name'].'</td></tr>
				<tr><td>(ii). Ownership Type</td><td>'.$ownership_type.'</td></tr>
				<tr><td>(iii). PAN of the Business Establishment / Factory / Company </td><td>'.$get_all_data['factory_pan'].'</td></tr>
				<tr><td>(iv). Trade License No </td><td>'.$get_all_data['trade_license_no'].'</td></tr>
				<tr><td>(v). Plan Approval number and Approval Date</td><td>'.$plan_details.'</td></tr>
				<tr><td>(vi). Registration number and  Date </td><td>'.$reg_details.'</td></tr>
				<tr><td>(vii). License number and validupto Date </td><td>'.$license_details.'</td></tr>
				<tr><td>(viii). GSTIN No. </td><td>'.$get_all_data['gstin_no'].'</td></tr>
				<tr><td>(ix). Udyog Aadhaar No.</td><td>'.$get_all_data['udyog_aadhaar'].'</td></tr>
				<tr><td>(x). Enargy Meter No. </td><td>'.$enargy_no.'</td></tr>
				<tr><td>(xi). CIN No. </td><td>'.$cin_no.'</td></tr>
				<tr><td colspan="2">B.Location of Factory </td></tr>
				<tr><td>(i).Zone</td><td>'.$factory_zone_date['zone_name'].'<br/>('.$factory_zone_date['zone_details'].')</td></tr>
				<tr><td>(ii).Address</td><td>'.$factory_address_location.'</td></tr>
				<tr><td>(iii).Telephone No</td><td>'.$get_all_data['comm_telephone'].'</td></tr>
				<tr><td>(i).Mobile No</td><td>'.$get_all_data['comm_mobile'].'</td></tr>
				<tr><td>(v).Fax No</td><td>'.$get_all_data['comm_fax'].'</td></tr>
				<tr><td>(vi)..Email Id</td><td>'.$get_all_data['comm_email'].'</td></tr>
				<tr><td colspan="2">C.Address of the Registered office / Head office<br/><font color="#FF0000">(N.B:-This address will be treated as communication address as per Section 7 of Factories Act,1948 )</font> </td></tr>
				<tr><td>(i).Address</td><td>'.$headoffice_address.'</td></tr>
				<tr><td>D.Factory Identification according to WBPCB</td><td>'.$details.'</td></tr>
				
				<tr><td>E.Date from which the premises is occupied or been taken into use as factory </td><td>'.date('dS M Y', strtotime($get_all_data['date_of_amenability'])).'</td>
				
				
				<tr><td colspan="2">F.Worker Details</td></tr>
				<tr><td>(i).Maximum number of workers employed or to be employed in tha factory</td><td>'.$link_t.'</td></tr>
				<tr><td colspan="2">G.Power Details</td></tr>
				<tr><td>(i).Installed Power or to be installed power </td><td>'.$power_details.'</td></tr>
								
				<tr><td colspan="2">I.Manager Details</td></tr>
				<tr><td>(i).Manager Details</td><td>'.$link_manager.'</td></tr>
				<tr><td colspan="2">H.Occupier Details</td></tr>
				<tr><td>(i).View occupier details</td><td>'.$link_occuiper.'</td></tr>
				<tr><td colspan="2">J.Director Details</td></tr>
				<tr><td>(i).View director details</td><td>'.$link_director.'</td></tr><tr>
				<td colspan="2">K.Manufacturing process</td></tr>
				<tr><td>(i).Carried/to be carried on the factory</td><td>'.$nature_work.'</td></tr>';
			
	$output .= '</table></div>';
	return $output;
	
}
function backlog_add_factory_preview_submit($form, &$form_state){
	global $base_root, $base_path,$user;
	$val   						    =  $form_state['values'];
	$userid 						= $user->uid;
    $val    						= $form_state['values'];
	$user_role 						= array_keys($user->roles);
    $urole  						= $user_role[1];
	
	$service_id						=  encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$factorytype_id					=  encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$application_no 				=  encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$referance_no					=  encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	

	$get_fa_cafa 					= get_fa_cafa($application_no);
	$is_manager_tab					= $get_fa_cafa['is_manager_tab'];
	$is_occupier_tab				= $get_fa_cafa['is_occupier_tab'];
	$is_occupier_tab				= $get_fa_cafa['is_occupier_tab'];
	$created_by						= $get_fa_cafa['created_by'];
	$factory_name					= $get_fa_cafa['factory_name'];
	$ownership_type 			= $get_fa_cafa['factory_owershiptype'];
	
	
	if($is_manager_tab!=1){
		 drupal_set_message('Please add manager or diector details.','error');
	}if($is_occupier_tab!=1){
		 drupal_set_message('Please add occupier details.','error');
	}
	
	if(!empty($ownership_type)){
	 if($ownership_type == 'pv' || $ownership_type == 'ltd'){
		 $ownership_type_occupier 	= 'Director';
	 }elseif($ownership_type == 'par_firm'  || $ownership_type=='llp'){
		 $ownership_type_occupier 	= 'Partner';
	 }elseif($ownership_type == 'pro_firm'){
		 $ownership_type_occupier 	= 'Proprietor';
	 }elseif($ownership_type=='cooperative'|| $ownership_type=='registered'){
		 $ownership_type_occupier	= 'Nominated Occupier';
	 }elseif($ownership_type == 'govt' || $ownership_type == 'psu' || $ownership_type == 'others' || $ownership_type=='localbody' ){
		 $ownership_type_occupier	= 'Nominated ';
	 }
	}
	
	if($urole == 4){
		
		 $worker_status 			= 	array('worker_registration_status' => 'A','created_by'=> $userid);
		 $manufacturing_status 		= 	array('manufacturing_application_status' => 'A','created_by' => $userid);
		 $power_status 				= 	array('power_application_status' => 'A','created_by'=>$userid);
		 $director_status 			= 	array('application_status' => 'A','created_by'=> $userid,'type_director'=>$ownership_type);
		 $manager_status 			= 	array('application_status' => 'A','created_by'=>$userid);
		 $caf_update 				= 	array('application_status' => 'A','modification_date'=> date('Y-m-d'),'created_by'=>$userid);
		 $occupier_status 			= 	array('application_status' => 'A','type_occupier' =>$ownership_type_occupier ,'created_by'=>$userid);
		
	}else{
		
		 $factor_add_inspector_id	= 	$userid;
		 $factor_add_inspector		= 	1;
		 $worker_status 			= 	array('worker_registration_status' => 'A');
		 $manufacturing_status 		= 	array('manufacturing_application_status' => 'A');
		 $power_status 				= 	array('power_application_status' => 'A');
		 $director_status 			= 	array('application_status' => 'A','type_director'=>$ownership_type);
		 $manager_status 			= 	array('application_status' => 'A');
		 $caf_update 				= 	array('application_status' => 'A','modification_date'=> date('Y-m-d'),'factor_add_inspector_id'=>$factor_add_inspector_id,'factor_add_inspector'=>1);
		 $occupier_status 			= 	array('application_status' => 'A','type_occupier' =>$ownership_type_occupier );
	}
	
	
	
	if($is_manager_tab==1 && $is_occupier_tab==1 ){
		 //-----------Worker table update---------------------------
   
	$queryworker 	=	db_update('fa_worker_details');
	$queryworker	->	fields($worker_status);
	$queryworker	->	condition('application_id',$application_no,'=');
	$queryworker	->	condition('service_id',$service_id,'=');
	$queryworker	->	condition('factory_type',$factorytype_id,'=');
    $queryworker	->	condition('application_reference_no',$referance_no,'=');
	$queryworker    ->	execute();
	//-----------Manufacturing table update---------------------------
	 
	  $querymanufacturing 		=	db_update('fa_nature_manufacturing');
	  $querymanufacturing	    ->	fields($manufacturing_status);
	  $querymanufacturing		->	condition('application_id',$application_no,'=');
	  $querymanufacturing		->	condition('service_id',$service_id,'=');
	  $querymanufacturing	    ->	condition('factory_type',$factorytype_id,'=');
	  $querymanufacturing	    ->	condition('application_reference_no',$referance_no,'=');
	  $querymanufacturing		->	execute();
	//-----------Power table update---------------------------
	
	  $querypower 				=	db_update('fa_power_details');
	  $querypower				->	fields($power_status);
	  $querypower		    	->	condition('application_id',$application_no,'=');
	  $querypower		    	->	condition('service_id',$service_id,'=');
	  $querypower				->	condition('factory_type',$factorytype_id,'=');
	  $querypower				->	condition('application_reference_no',$referance_no,'=');
	  $querypower				->	execute();
	//-----------Director table update---------------------------
	 
	  $querydirector 			=	db_update('fa_director_details');
	  $querydirector			->	fields($director_status);
	  $querydirector		    ->	condition('application_director_id',$application_no,'=');
	  $querydirector		    ->	condition('director_service_id',$service_id,'=');
	  $querydirector			->	condition('factory_type_id',$factorytype_id,'=');
	  $querydirector			->	condition('application_reference_no',$referance_no,'=');
	  $querydirector			->	execute();
	//-----------Manager table update---------------------------
	
	  $querymanager 			=	db_update('fa_manager_details');
	  $querymanager				->	fields($manager_status);
	  $querymanager		    	->	condition('application_manager_id',$application_no,'=');
	  $querymanager		   		 ->	condition('manager_service_id',$service_id,'=');
	  $querymanager				->	condition('factory_type_id',$factorytype_id,'=');
	  $querymanager				->	condition('application_reference_no',$referance_no,'=');
	  $querymanager				->	execute();
	  
	  //-----------occupier table update---------------------------
	  
	  $querymanager 			=	db_update('fa_occupier_details');
	  $querymanager				->	fields($occupier_status);
	  $querymanager		    	->	condition('application_occupier_id',$application_no,'=');
	  $querymanager		   		 ->	condition('occupier_service_id',$service_id,'=');
	  $querymanager				->	condition('factory_type_id',$factorytype_id,'=');
	  $querymanager				->	condition('application_reference_no',$referance_no,'=');
	  $querymanager				->	execute();
	
	  
	   if(!empty($val['reg_file'])){
		   $document_name = 'Previous Registration Certificates';
			$document_listid_reg =  fun_fetch_document_listid($document_name);
		   $document_registration	= file_load($val['reg_file']);
		   if($document_registration != "" ){
            $path_category = pathinfo($document_registration->filename);
				
			
            $new_filename_reg = 'certificates_registration_'.date('Y').'_'.$factory_type_id.'_'.time().'.'.$path_category['extension'];
            $document_registration->filename = $new_filename_reg;
            file_save($document_registration);

            $filename_reg_arr = explode("/", $document_registration->uri);

            $filepathSave_reg 	= file_get_contents(escapefile_url('public://upload/upload_pdf/'.$filename_reg_arr[4]));
        
               $content_reg		= base64_encode($filepathSave_reg);

            $reg_doc_content_arr = array(
                'upload_doc_content' => $content_reg,
            );
          
					
			$get_reg_certificates = get_caf_upload_doc_details($application_no, $service_id, 'REG', $factorytype_id, $referance_no);
			
			
			if(!empty($get_reg_certificates)){
			
					$content_id = $get_reg_certificates->upload_doc_content_id;
					$queryabc = db_update('fa_caf_upload_doc_content');
        			$queryabc->fields($reg_doc_content_arr);
       				$queryabc->condition('id', $content_id, '=');
		        	$queryabc->execute();
					
					$cat_upload_doc = array(
					
					'file_name' 					=> $new_filename_reg,
					'created_date'				 	=> date('Y-m-d h:i:s'),
                
            	);
					$queryabc = db_update('fa_caf_upload_all_doc');
        			$queryabc->fields($cat_upload_doc);
       				$queryabc->condition('upload_doc_content_id', $content_id, '=');
		        	$queryabc->execute();
					
				 	
			}else{
				$id_reg_doc =  db_insert('fa_caf_upload_doc_content')->fields($reg_doc_content_arr)->execute();
                $reg_upload_doc_arr = array(
					'application_id' 				=> $application_no,
					'application_reference_no' 		=> $referance_no,
					'file_name' 					=> $new_filename_reg,
					'factory_typeid' 				=> $factorytype_id,
					'service_id' 					=> $service_id,
					'upload_doc_content_id' 		=> $id_reg_doc,
					'upload_doc_type' 				=> 'REG',
					'created_by'					=> $userid,
					'created_date'				 	=> date('Y-m-d h:i:s'),
					'doc_master_id'					=>$document_listid_reg
                
            	);
            	db_insert('fa_caf_upload_all_doc')->fields($reg_upload_doc_arr)->execute();
			}
			
           
        }
	   }
		 if(!empty($val['lic_file'])){
			 $document_name = 'Previous Licence';
			$document_listid_lic =  fun_fetch_document_listid($document_name);
			 $document_lic	= file_load($val['lic_file']);
			 if($document_lic != "" ){
            $path_lic = pathinfo($document_lic->filename);
				
			
            $new_filename_lic = 'certificates_license'.date('Y').'_'.$factory_type_id.'_'.time().'.'.$path_category['extension'];
            $document_lic->filename = $new_filename_lic;
            file_save($document_lic);

            $filename_lic_arr = explode("/", $document_lic->uri);

            $filepathSave_lic	= file_get_contents(escapefile_url('public://upload/upload_pdf/'.$filename_lic_arr[4]));
        
               $content_lic		= base64_encode($filepathSave_lic);

            $lic_doc_content_arr = array(
                'upload_doc_content' => $content_lic,
            );
          
					
			$get_lic_certificates = get_caf_upload_doc_details($application_no, $service_id, 'LIC', $factorytype_id, $referance_no);
			
			
			if(!empty($get_lic_certificates)){
			
					$content_id = $get_lic_certificates->upload_doc_content_id;
					$queryabc = db_update('fa_caf_upload_doc_content');
        			$queryabc->fields($lic_doc_content_arr);
       				$queryabc->condition('id', $content_id, '=');
		        	$queryabc->execute();
					
					$lic_upload_doc = array(
					
					'file_name' 					=> $new_filename_lic,
					'created_date'				 	=> date('Y-m-d h:i:s'),
                
            	);
					$queryabc = db_update('fa_caf_upload_all_doc');
        			$queryabc->fields($lic_upload_doc);
       				$queryabc->condition('upload_doc_content_id', $content_id, '=');
		        	$queryabc->execute();
					
				 	
			}else{
				$id_lic_doc =  db_insert('fa_caf_upload_doc_content')->fields($lic_doc_content_arr)->execute();
                $lic_upload_doc_arr = array(
					'application_id' 				=> $application_no,
					'application_reference_no' 		=> $referance_no,
					'file_name' 					=> $new_filename_reg,
					'factory_typeid' 				=> $factorytype_id,
					'service_id' 					=> $service_id,
					'upload_doc_content_id' 		=> $id_lic_doc,
					'upload_doc_type' 				=> 'LIC',
					'created_by'					=> $userid,
					'created_date'				 	=> date('Y-m-d h:i:s'),
					'doc_master_id'					=> $document_listid_lic
                
            	);
            	db_insert('fa_caf_upload_all_doc')->fields($lic_upload_doc_arr)->execute();
			}
			
           
        }
		}
		 if(!empty($val['plan_file'])){
			  $document_name = 'Previous Plan approval Letter';
			$document_listid_plan =  fun_fetch_document_listid($document_name);
			 $document_plan	= file_load($val['plan_file']);
		if($document_plan != "" ){
            $path_plan= pathinfo($document_plan->filename);
				
			
            $new_filename_plan = 'approval_letter'.date('Y').'_'.$factory_type_id.'_'.time().'.'.$path_category['extension'];
            $document_plan->filename = $new_filename_plan;
            file_save($document_plan);

            $filename_plan_arr = explode("/", $document_plan->uri);

            $filepathSave_plan	= file_get_contents(escapefile_url('public://upload/upload_pdf/'.$filename_plan_arr[4]));
        
               $content_plan	= base64_encode($filepathSave_plan);

            $plan_doc_content_arr = array(
                'upload_doc_content' => $content_plan,
            );
          
					
			$get_plan_approvalletter = get_caf_upload_doc_details($application_no, $service_id, 'APPROVAL LETTER', $factorytype_id, $referance_no);
			
			
			if(!empty($get_plan_approvalletter)){
			
					$content_id = $get_plan_approvalletter->upload_doc_content_id;
					$queryabc = db_update('fa_caf_upload_doc_content');
        			$queryabc->fields($plan_doc_content_arr);
       				$queryabc->condition('id', $content_id, '=');
		        	$queryabc->execute();
					
					$plan_upload_doc = array(
					
					'file_name' 					=> $new_filename_plan,
					'created_date'				 	=> date('Y-m-d h:i:s'),
                
            	);
					$queryabc = db_update('fa_caf_upload_all_doc');
        			$queryabc->fields($plan_upload_doc);
       				$queryabc->condition('upload_doc_content_id', $content_id, '=');
		        	$queryabc->execute();
					
				 	
			}else{
				$id_plan_doc =  db_insert('fa_caf_upload_doc_content')->fields($plan_doc_content_arr)->execute();
                $plan_upload_doc_arr = array(
					'application_id' 				=> $application_no,
					'application_reference_no' 		=> $referance_no,
					'file_name' 					=> $new_filename_reg,
					'factory_typeid' 				=> $factorytype_id,
					'service_id' 					=> $service_id,
					'upload_doc_content_id' 		=> $id_plan_doc,
					'upload_doc_type' 				=> 'APPROVAL LETTER',
					'created_by'					=> $userid,
					'created_date'				 	=> date('Y-m-d h:i:s'),
					'doc_master_id'					=> $document_listid_plan
                
            	);
            	db_insert('fa_caf_upload_all_doc')->fields($plan_upload_doc_arr)->execute();
			}
			
           
        }
		 }
		
		
	 
	  
	  
	  
	 
	  $queryabc 		=	db_update('fa_cafa');
	  $queryabc		    ->	fields($caf_update);
	  $queryabc			->	condition('id',$application_no,'=');
	  $queryabc	        ->	execute();
	  
	  
	if($urole == 4){
		remark_input($referance_no,$application_no,'A','backlog factory  is sucessfully added from Applicant')	;
		 drupal_goto('applicant-dashboard');	
	}else{
		remark_input($referance_no,$application_no,'A','backlog factory  is sucessfully added from AD')	;	
		drupal_goto('factory-list-admin/ACTIVE');	
	}
	  drupal_set_message(' Factory('.$factory_name.') has been successfully saved.');
	   
	 	
	}
	
   
	} 







?>