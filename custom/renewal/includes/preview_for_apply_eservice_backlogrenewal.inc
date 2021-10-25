<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function preview_for_apply_eservice_backlogrenewal($form, &$form_state,$serviceid, $factory_type_id,$applicationid,$referenceid) {
	global $base_root,$base_path,$user;
	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	
	  $service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	  $factory_typeid 	= encryption_decryption_fun('decrypt',$factory_type_id);
	  $application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	  $reference_number = encryption_decryption_fun('decrypt',$referenceid);
	  
	//die($service_id.'---'.$factory_typeid.'---'.$application_id.'---'.$reference_number);
	
	$form = array();
	  $form['serviceid_hidden']     = array(
        '#type' => 'hidden',
        '#default_value' => $serviceid
    );
    $form['factorytypeid_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $factory_type_id
    );
	$form['applicationid_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $applicationid
    );
	$form['refnumber_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $referenceid
    );
	
	
	$get_all_data 				=  get_fa_cafa($application_id);
	
	//echo "<pre>";print_r($get_all_data); exit;
	$plan_registration_date 	= !empty($get_all_data['registration_date'])? $get_all_data['registration_date']:$get_all_data['backlog_registration_date'];
	$plan_license_date 			= !empty($get_all_data['license_valid_upto'])? $get_all_data['license_valid_upto']:$get_all_data['backlog_license_date'];
	$period_for_renewal			= $get_all_data['period_for_renewal'];
	$telmak_migrated_flag		= $get_all_data['tm_migrated_flag'];
	
	$form['telmak_migrated_flag_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => encryption_decryption_fun('encrypt',$telmak_migrated_flag)
    );
	
	$form['application_preview'] 	= array(
  		'#type'		=> 'markup',
		'#markup'	=> view_deatils($application_id,$reference_number,$factory_typeid,$service_id),
	);	

	$form['renewal_ques']['submit'] = array (
	  		'#prefix' 	=> '<div id="submit_div">',
		 	'#suffix' 	=> '</div>',
	  		'#attributes' => array('class' => array('btn btn-success pull-right'), 'onclick' => 'if(!confirm("Are you sure to continue ?")){return false;}'),
	  		'#type' 	=> 'submit',
	 		'#value'	=> 'Continue'
	);
	$form['renewal_ques']['markup_end'] = array(
           '#suffix' => '</div></div></div>',
           '#type' => 'markup',
	);
	return $form;
	}

function view_deatils($application_id,$reference_number,$factory_typeid,$service_id){
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
		
		$license_details = $license_number .' ,dated on '.$license_date.' <br/> <font color="#FF0000">
		 License Expiring on dated '.$valid_upto.'</font>';
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
		
			
		
		$documents_details=$base_root.$base_path.'view-documents-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_documents=ctools_modal_text_button(t('View Documents list'), $documents_details ,t('View Details)')) ;
		
		$manager_details=$base_root.$base_path.'view-manager-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_manager=ctools_modal_text_button(t('View Manager(s)'), $manager_details ,t('View Details)')) ;
		
		
		$owner_details=$base_root.$base_path.'view-owner-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_owner =ctools_modal_text_button(t('View owner Details'), $owner_details ,t('View Details')) ;
		
		
		$factory_zone_date = get_factory_zone_name($get_all_data['factory_zone']);
		
		if(!empty($get_all_data['enargy_no'])){ $enargy_no = $get_all_data['enargy_no']; }else{$enargy_no =  'Nil';}
			if(!empty($get_all_data['cin_no'])){ $cin_no = $get_all_data['cin_no']; }else{$cin_no =  'Nil';}
			
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
				$wbpcb_reference_no = 'n/a'; 
				$wbpcb_ref_date = 'n/a';
				$file = $get_all_data['wbpcb_intimation_letter'];
				$file_url = '<a href='.file_create_url(get_uploaded_document_url($file)).' onclick = "popIt(this.href);return false;">View</a>';
				}
			if($get_all_data['wbpcb_category_name']==5){$consent ='Exempted'; $wbpcb_reference_no = 'n/a';$wbpcb_ref_date = 'n/a';}
		
		$details = $consent.'<br>WBPCB referance no. = '.$wbpcb_reference_no.'<br>WBPCB referance no = '.$wbpcb_ref_date.'<br>'.$file_url;
		if($plan_approval_no != 'NA'){
			$plan_details = $plan_approval_no.' dated on '.$plan_approval_date;
		}else{
			$plan_details = 'Not Avaliable';
		}
		
			 $type_of_application =' Plan Approval Number:-'.$plan_details.'<br/>Registration Number:-'.$reg_details.'<br/>'.'License Number:- '.$license_details.'<br/></span><h6><b>(N.B.-All inputs are provided by you only)</b></h6>';
		
	$output .='<div class="row">
				<div class="box box-info">
					<div class="box-header with-border"><center><h3 class="box-title">Application Preview<br/>'.$type_of_application.'</h3></center></div>
					<div class="box-body">
				<table class="table table-bordered"> <tr>
   								<th>Parameters</th>
   								<th>Inputs</th>
								</tr>';
	
	$output .='<tr><td colspan="2">A.Factory Information</td></tr>
				<tr><td>(i). Name of the factory</td><td>'.$get_all_data['factory_name'].'</td></tr>
				<tr><td>(ii). Ownership Type</td><td>'.$ownership_type.'</td></tr>
				<tr><td>(iii). PAN of the Business Establishment / Factory / Company </td><td>'.$get_all_data['factory_pan'].'</td></tr>
				<tr><td>(iv). Plan Approval number and Approval Date</td><td>'.$plan_details.'</td></tr>
				<tr><td>(v). Registration number and  Date </td><td>'.$reg_details.'</td></tr>
				<tr><td>(vi). License number and validupto Date </td><td>'.$license_details.'</td></tr>
				<tr><td>(vii). GSTIN No. </td><td>'.$get_all_data['gstin_no'].'</td></tr>
				<tr><td>(viii). Udyog Aadhaar No.</td><td>'.$get_all_data['udyog_aadhaar'].'</td></tr>
				<tr><td>(ix). Enargy Meter No. </td><td>'.$enargy_no.'</td></tr>
				<tr><td>(x). CIN No. </td><td>'.$cin_no.'</td></tr>
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
			
	$output .= '</table></div></div></div>';
	return $output;
	
}






function preview_for_apply_eservice_backlogrenewal_submit($form, &$form_state){
	global $user;
    $userid 						= $user->uid;
    $val    						= $form_state['values'];
	
	$application_id 				= encryption_decryption_fun('decrypt', $val['applicationid_hidden']); 
	$service_id 					= encryption_decryption_fun('decrypt', $val['serviceid_hidden']); 
	$factorytype_id 				= encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']); 
	$reference_no 					= encryption_decryption_fun('decrypt', $val['refnumber_hidden']);
	$telmak_migrated_flag_hidden	= encryption_decryption_fun('decrypt', $val['telmak_migrated_flag_hidden']);
	$status 						=  'In';
		
	log_genaration_caf($application_id);
	$referenceno 		= created_referenceno();
	$serviceid 			= 3;
	$worker_details 	= get_worker_details_service($service_id,$factorytype_id,$application_id,$reference_no);
				
	 foreach($worker_details as $worker){
		 $workerid = $worker->id;
	 }
	 log_genaration_worker($workerid,$referenceno,$serviceid);
	 
	 $power_details = get_power_generating_station($application_id,$reference_no,$factorytype_id,$service_id);
	 foreach($power_details as $power){
		 $powerid = $power->id;
	 }
	log_genaration_power($powerid, $referenceno, $serviceid);
	$manager_details = get_all_manager_data($application_id,$service_id,$factorytype_id,$reference_no);
	foreach($manager_details as $manager){
		$managerid = $manager->id;
		log_genaration_manager($managerid, $referenceno, $serviceid);
	}
	$occupier_details = get_all_occupier_data($application_id,$service_id,$factorytype_id,$reference_no);
				 
	foreach($occupier_details as $occupier){
		$occupierid = $occupier->id;
		log_genaration_occupier($occupierid, $referenceno, $serviceid);
	}
	$director_details = get_director_details_service($application_id,$service_id,$factorytype_id,$reference_no);
	foreach($director_details as $director){
		$directorid = $director->id;
		log_genaration_director($directorid, $referenceno, $serviceid);
	}
				 
	$manufacturing_details = get_manufacturing($application_id,$service_id,$factorytype_id,$reference_no);
	foreach($manufacturing_details as $manufacturing){
		$manufacturingid = $manufacturing->id;
	 }
	 if(!empty($manufacturingid)){
	  log_genaration_manufacturing($manufacturingid, $referenceno, $serviceid);
	 }
	 
	 $doc_details = get_attached_filename($application_id,$reference_no,$factorytype_id,$service_id);
	 foreach($doc_details as $doc){
		 $docid = $doc->id;
		log_genaration_doc($docid, $referenceno, $serviceid);
	 }
	 $application_number = create_registration_application($serviceid);
				 
	  $approval_status 	= 	array('application_status' => $status,'service_id' => $serviceid,'reference_number' => $referenceno,'renewal_dim_appoved' =>0,'download_status'=>NULL);
				 $year_update = array('is_previous'=>1);
				 
				 $queryapp	=	db_update('fa_cafa');
				 $queryapp	->	fields($approval_status);
				 $queryapp	->	condition('id',$application_id,'=');
				 $queryapp	->	condition('factory_typeid',$factorytype_id,'=');
				 $queryapp	->	condition('reference_number',$reference_no,'=');
				 $queryapp	->	execute();
				 
				 $previous_year	=	db_update('fa_calculate_year');
				 $previous_year	->	fields($year_update);
				 $previous_year	->	condition('application_id',$application_id,'=');
				 $previous_year	->	condition('reference_no',$reference_no,'=');
				 $previous_year	->	condition('factory_id',$factorytype_id,'=');
				 $previous_year	->	condition('service_id',$service_id,'=');
				 $previous_year	->	execute();
				 
				
			  remark_input($referenceno,$application_id,'In','This application is applied for renewal with change from Add factory or telmac end')	;

			drupal_goto('applicant/caf-online-backrenew/default/'.encryption_decryption_fun('encrypt', $serviceid).'/'.$val['factorytypeid_hidden'].'/'.$val['applicationid_hidden'].'/'.encryption_decryption_fun('encrypt', $referenceno));
		
	
	
}

?>