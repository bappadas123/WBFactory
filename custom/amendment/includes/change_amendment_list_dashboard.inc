<?php
drupal_add_js(drupal_get_path('module', 'amendment') . '/js/myfunction.js');
function change_amendment_list_dashboard($form, &$form_state,$applicationid,$serviceid, $factory_typeid,$referenceid) {
	
	global $base_root,$base_path,$user;
	
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
   	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
   	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
   	$reference_no 		= encryption_decryption_fun('decrypt',$referenceid);
//	$apply_service 		= encryption_decryption_fun('decrypt',$applyservice);

	//die($service_id.'---'.$factory_type_id.'---'.$application_id.'---'.$reference_no);
	
   	$user_id = $user->uid;
   	
   	if (!empty($application_id)) {
           	$get_fa_cafa           			= 	get_fa_cafa($application_id);
          	$application_status      		= 	$get_fa_cafa['application_status'];
   			$factory_identification_number	= 	$get_fa_cafa['factory_reg_identification_number'];
   			$factory_referance_number		= 	$get_fa_cafa['reference_number'];	
   			
			$applicant_users				= 	$get_fa_cafa['created_by'];	
   			$previous_excess_paid			=   $get_fa_cafa['previous_excess_paid'];
   			$is_calculate					=   $get_fa_cafa['is_calculate'];
   			$service_fees					=   $get_fa_cafa['service_fees'];	
   			$period_for_application 		=   $get_fa_cafa['period_for_application'];
			$registration_date 				=   $get_fa_cafa['registration_date'];
			$period_for_application 		=   $get_fa_cafa['period_for_application'];
   			$license_valid_upto				=   $get_fa_cafa['license_valid_upto'];
       }
	   //print_r($get_fa_cafa);die();
   			
   	$form = array();
   	$form['#attributes'] = array('enctype' => "multipart/form-data");		
   	$form['serviceid_hidden'] = array(
		'#type' 			=> 'hidden',
   		'#default_value' 	=> $serviceid
   	);	
   	$form['factorytype_hidden'] = array(
   		'#type' 			=> 'hidden',
   		'#default_value' 	=> $factory_typeid 
   	);		  	   
   	$form['referance_no_hidden'] = array(
   		'#type' 			=> 'hidden',
   		'#default_value' 	=> $referenceid, 
   	);
   	$form['application_id_hidden'] = array(
   		'#type' 			=> 'hidden',
   		'#default_value' 	=> $applicationid, 
   	);
	/*$form['factory_service_name'] = array(
   		'#type' 			=> 'hidden',
   		'#default_value' 	=> $applyservice	 
   	);*/
	
	$form['factory_identification_number_hidden'] = array(
   		'#type' 			=> 'hidden',
   		'#default_value' 	=> empty($factory_identification_number)?'':encryption_decryption_fun('encrypt',$factory_identification_number)	 
   	);
	
	
   	$form['applicant_id_hidden'] = array(
   		'#type' 			=> 'hidden',
   		'#default_value' 	=> encryption_decryption_fun('encrypt', $applicant_users), 
   	);
	$form['reg_number_hidden'] = array(
   		'#type' 			=> 'hidden',
   		'#default_value' 	=> encryption_decryption_fun('encrypt', $factory_registrstion_no), 
   	);
	$form['reg_date_hidden'] = array(
   		'#type' 			=> 'hidden',
   		'#default_value' 	=> encryption_decryption_fun('encrypt', $registration_date), 
   	);
   	
   	$form['applicantion_verify']['markup_appplication'] = array(
   		'#type' 			=> 'markup',
   		'#markup' 			=> get_verifing_data($application_id,$service_id,$factory_type_id,$reference_no),
	   );
	   
	   $query_check_applicant = db_select('fa_caf_check_point','ck');
	   $query_check_applicant->fields('ck', array());
	   $query_check_applicant->condition('ck.app_id', $application_id, '=');
	   $query_check_applicant->condition('ck.reference_no', $reference_no, '=');
	   $query_check_applicant->orderBy('ck.id','DESC');
	   $result = $query_check_applicant->execute();
	   $content = $result->fetchAssoc();
	
   	$form['applicantion_change']['fieldname']	= array(
		'#title'			=> 'Field Name',
   		'#type'				=> 'hidden',
   		'#attributes'		=> array('id' => 'list_check_data'),
   		'#default_value' 	=> !empty($content['fieldname']) ? $content['fieldname'] : '',
   	);
    
   	//echo $application_status;die;
   //	if($application_status == 'I' || $application_status == 'RP' ){
		
	
		
	
	
	
	$form['application_forword']['markup_start'] = array(
           '#prefix' => '<div class="row">',
           '#type' => 'markup',
	);
	
	$form['application_forword']['Registration_list']	 = array(
	   	 '#markup' 		=> l(t('Back'),'applicant-dashboard/', array('html' => TRUE,'attributes'=> array('class'=>array('btn bg-navy')))),
		 '#prefix' => '<div class="col-md-11  col-xs-11">',
		 '#suffix' => '</div>',
	);
	$form['application_forword']['submit'] = array(
           '#prefix' => '<div class="col-md-1  col-xs-1">',
           '#suffix' => '</div></div>',
           '#attributes' => array('class' => array('btn btn-success '), 'onclick' => 'if(!confirm("Are you sure to continue ?")){return false;}'),
           '#type' => 'submit',
           '#value' => 'Continue'
	);
	
	//}
	
   	return $form; 
}
   
   

function get_verifing_data($application_id,$service_id,$factory_type_id,$reference_no){
   	//echo $reference_no;
   	global $base_root,$base_path,$user;		 
   	$user_id 				=  $user->uid;
	$get_all_data 			=  get_fa_cafa($application_id);
	$application_status     =  $get_all_data['application_status'];
	$service_id_pre_application = $get_all_data['service_id'];
   	ctools_include('ajax');
   	ctools_include('modal');
   	ctools_modal_add_js();
	
	$worker_details=$base_root.$base_path.'view-worker-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
	   $link_worker=ctools_modal_text_button(t('View Worker(s)'), $worker_details ,t('View Details)')) ;

	   
   $occupier_details=$base_root.$base_path.'view-occuiper-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
	   $link_occuiper=ctools_modal_text_button(t('View Occupier(s)'), $occupier_details ,t('View Details)')) ;	
   $director_details=$base_root.$base_path.'view-director-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
	   $link_director=ctools_modal_text_button(t('View Director(s)'), $director_details ,t('View Details)')) ;		

   $documents_details=$base_root.$base_path.'view-documents-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
	   $link_documents=ctools_modal_text_button(t('View Documents list'), $documents_details ,t('View Details)')) ;	
   $manager_details=$base_root.$base_path.'view-manager-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
	   $link_manager=ctools_modal_text_button(t('View Manager(s)'), $manager_details ,t('View Details)')) ;	
   $pre_payment_details=$base_root.$base_path.'view-prepaymnet-history/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
	   $link_pre_payment=ctools_modal_text_button(t('View Previous Payment'), $pre_payment_details ,t('View Details)')) ;

	$owner_details=$base_root.$base_path.'view-owner-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
		$link_owner =ctools_modal_text_button(t('View owner Details'), $owner_details ,t('View Details')) ;
   	
   	
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
   		}if($get_all_data['factory_owershiptype']=="others"){
   				$ownership_type = "Others";
   		}
   		$is_backlog = $get_all_data['is_backlog'];
   		if($is_backlog == 1){
   			$plan_approval_no = $get_all_data['backlog_plan_approval_no'];
   			$plan_approval_date =date('dS M Y', strtotime($get_all_data['backlog_plan_approval_date']));
   		}else{
   			$plan_approval_no = $get_all_data['factory_plan_approval_number'];
   			$plan_approval_date = date('dS M Y', strtotime($get_all_data['modification_date']));
   		}
   		$factory_zone_date 			 =  get_factory_zone_name($get_all_data['factory_zone']);
   		$getdata_factory_location	 =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
   		$factory_address_location 	 =  $get_all_data['addrline'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_factory_location);
   		$getdata_headoffice_address  =  array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
   		$headoffice_address 		 =  $get_all_data['addrline_off'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_headoffice_address);
   		
		
		$owner_address_details = !empty($get_all_data['addrline_premises'])?$get_all_data['addrline_premises'].',':'';
		if($get_all_data['owner_country']==NULL){$get_all_data['owner_country'] = 99;}
		$owner_address_details.= $get_all_data['owner_country_address'].',<br/>'.country_name($get_all_data['owner_country']);
		$getdata_owner_address 		=  array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
		$owner_address 				=	$owner_address_details.'<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_owner_address);
		
		$nature_details = get_manufacturing($application_id,$service_id,$factory_type_id,$reference_no);
		   foreach($nature_details as $nature){
			   $nature_work = $nature->nature_manufacturing;
		   }
		$power_generating_station 	= get_power_generating_station($application_id,$reference_no,$factory_type_id,$service_id);
		foreach($power_generating_station as $power){
			$power_details = $power->installed_power.'('.$power->power_unit.')';
		}
   		$intimation_letter 			 =  get_uploaded_document_url($get_all_data['wbpcb_intimation_letter']);
   			if(!empty($intimation_letter)){ 
   					$url 		= explode('//',$intimation_letter);
   					$doc_url	= $url[1];
   					$view_intimation_letter	= '<a title = "Click here to view" href="'.$GLOBALS['base_url'].'/sites/default/files/'.$doc_url.'" target= "_BLANK" onclick = "popIt(this.href);return false;" ><i class="ace-icon fa fa-file-pdf-o bigger-130"></i></a>';
   			}else{
   				$view_intimation_letter = 'Not Applicable for above mention category';
   			}
   			$previous_details 			=  get_previous_details_view($application_id,$reference_no,$factory_type_id,$service_id);
   				foreach($previous_details as $pre_row){
   					$is_previous		 	= $pre_row->is_previous;
   					if($is_previous == "Yes"){
   						$view = "";
   					}if($is_previous == "No"){
   						$view = "";
   					}
   				}
   			/****** ADDED BY SUBHAMAY ******/
		if($get_all_data['tm_migrated_flag']=='N'||$get_all_data['tm_migrated_flag']=='S')
		{
			        
			$application_from = l('Application Form', 'document-list/view-appliction-form/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$factory_typeid).'/'.encryption_decryption_fun('encrypt',$reference_number).'/'.encryption_decryption_fun('encrypt','CAF'), array('html' => TRUE,'attributes'=>array('title' => 'Application form', 'target' => '_BLANK','class'=>array(''))));
		}
		else
		{
			/* Added by subhamay*/
		$caf_doc_details=$base_root.$base_path.'view-documents-caf/nojs/'.$application_id.'/'.$reference_number.'/'.$get_all_data['tm_appliction_id']; 	
		$link_caf=ctools_modal_text_button(t('View CAF'), $caf_doc_details ,t('View Details)')) ;
		/**** ended by subhamay ******/
		    $application_from = $link_caf;
		}
   					//echo $service_id_pre_application;die();
		$plan_approval_number	= !empty($get_all_data['factory_plan_approval_number'])? $get_all_data['factory_plan_approval_number']:$get_all_data['backlog_plan_approval_no'];
		$plan_approval_date 	= !empty($get_all_data['plan_approval_date'])? $get_all_data['plan_approval_date']:$get_all_data['backlog_plan_approval_date'];
		
		$plan_registration_number	= !empty($get_all_data['factory_registrstion_no'])? $get_all_data['factory_registrstion_no']:$get_all_data['backlog_registration_no'];
		$plan_registration_date 	= !empty($get_all_data['registration_date'])? $get_all_data['registration_date']:$get_all_data['backlog_registration_date'];
		
		
		$plan_licesne_number	= !empty($get_all_data['factory_license_no'])? $get_all_data['factory_license_no']:$get_all_data['backlog_license_number'];
		$plan_license_date 		= !empty($get_all_data['license_valid_upto'])? $get_all_data['license_valid_upto']:$get_all_data['license_valid_upto'];
		
		if($get_all_data['wbpcb_category_name']== 4){
			$consent ='White'; 
			$wbpcb_reference_no = 'NA'; 
			$wbpcb_ref_date = 'NA';
			$file = $get_all_data['wbpcb_intimation_letter'];
			$file_url	= l('Intimation Letter', 'document-list/view-appliction-form/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$factory_typeid).'/'.encryption_decryption_fun('encrypt',$reference_number).'/'.encryption_decryption_fun('encrypt','INT'), array('html' => TRUE,'attributes'=>array('title' => 'Intimation Letter', 'target' => '_BLANK','class'=>array(''))));
			}
		$details = $consent.'<br>WBPCB referance no. = '.$wbpcb_reference_no.'<br>WBPCB referance date = '.$wbpcb_ref_date.'<br>'.$file_url;

		/*if($service_id_pre_application == 4 || $service_id_pre_application == 5){
			$type_of_application ='Plan Approval Number:-'.$plan_approval_number.' dated on '.date('dS M Y', strtotime($plan_approval_date));
				$application_frm_id 	= 	$get_all_data['uploaded_pdf'];
				$application_form_url 	= 	get_uploaded_document_url($application_frm_id);
				
				if(!empty($application_form_url)){ 
						$url 						= explode('//',$application_form_url);
						$doc_url					= $url[1];
						$application_form_view		='<a title = "Click here to view" href="'.$GLOBALS['base_url'].'/sites/default/files/'.$doc_url.'" target="_blank"><i class="ace-icon fa fa-file-pdf-o bigger-130"></i></a>'; 
	
				}
		}*/

			if($service_id == 3 ){ $service_name ='Renewal of Licence';}
			if($service_id == 8 ){ $service_name ='Amendment of Licence';}
		
			
			 $type_of_application =' Plan Approval Number:-'.$plan_approval_number.' dated on '.date('dS M Y', strtotime($plan_approval_date)).'<br/>Registration Number:-'.$plan_registration_number.' dated on '.date('dS M Y', strtotime($plan_registration_date)).'<br/>'.'License Number:- '.$plan_licesne_number.' valid upto '.date('dS M Y', strtotime($plan_license_date));
			
   			$fetch_year	= fetch_year($application_id,$service_id,$factory_type_id,$reference_no);
			
   			$pre_view	= get_previous_details_view($application_id,$reference_no,$factory_type_id,$service_id);
			  
			  $data = fetch_checkpoint($application_id,$reference_no,$factory_type_id,$service_id);
			   $remark_field = explode(',', $data['fieldname']);
			   //print_r($remark_field);die;
   	
   			foreach ($remark_field as $fieldname){ 
   			//echo $fieldname;
   				if($fieldname == 'factory_name'){ $factory_name_ck = "checked='checked'";}
   				if($fieldname == 'ownership_type'){ $ownership_type_ck = "checked='checked'";}
   				if($fieldname == 'factory_pan'){ $factory_pan_ck = "checked='checked'";}
				if($fieldname == 'gstin_no'){ $gstin_no_ck = "checked='checked'";}
				if($fieldname == 'udyog_aadhaar'){ $udyog_aadhaar_ck = "checked='checked'";}
				if($fieldname == 'enargy_no'){ $enargy_no_ck = "checked='checked'";}
				if($fieldname == 'cin_no'){ $cin_no_ck = "checked='checked'";}
   				
   				if($fieldname == 'plan_approval_no'){ $plan_approval_ck = "checked='checked'";}
   				if($fieldname == 'plan_approval_date'){ $plan_approval_date_ck = "checked='checked'";}
   				
   				if($fieldname == 'zone_name'){ $zone_name_ck = "checked='checked'";}
   				
   				if($fieldname == 'factory_headoffice'){ $factory_headoffice_ck = "checked='checked'";}
   				
   				if($fieldname == 'telephone_no'){ $telephone_no_ck = "checked='checked'";}
   				if($fieldname == 'mobile_no'){ $mobile_no_ck 	= "checked='checked'";}
   				if($fieldname == 'fax_no'){ $fax_no_ck 	= "checked='checked'";}
   				if($fieldname == 'email_no'){ $email_no_ck 	= "checked='checked'";}
   				
   				if($fieldname == 'premises_address'){ $owner_name_ck = "checked='checked'";}
   				if($fieldname == 'premises_address'){ $premises_address_ck = "checked='checked'";}
   				
   				if($fieldname == 'wbpcb_id'){ $wbpcb_id_ck = "checked='checked'";}
   				if($fieldname == 'wbpcb_reference_id'){ $wbpcb_reference_id_ck = "checked='checked'";}
   				if($fieldname == 'wbpcb_reference_date'){ $wbpcb_reference_date_ck = "checked='checked'";}
   				if($fieldname == 'intimation_id'){ $intimation_id_ck = "checked='checked'";}
   				
   				if($fieldname == 'date_of_amenability_id'){ $date_of_amenability_id_ck = "checked='checked'";}
   				if($fieldname == 'period_for_application_id'){ $period_for_application_id_ck = "checked='checked'";}
   				if($fieldname == 'previous_name_id'){ $previous_name_id_ck = "checked='checked'";}
   				
   				if($fieldname == 'worker_details'){ $worker_details_ck = "checked='checked'";}
   				if($fieldname == 'power_details'){ $power_details_ck = "checked='checked'";}
   				if($fieldname == 'manager_details'){ $manager_details_ck = "checked='checked'";}
   				if($fieldname == 'occupier_details'){ $occupier_details_ck = "checked='checked'";}
   				if($fieldname == 'director_details'){ $director_details_ck = "checked='checked'";}
   				if($fieldname == 'nature_details'){ $nature_details_ck = "checked='checked'";}
   				if($fieldname == 'document_details'){ $document_details_ck = "checked='checked'";}
   				
   				if($fieldname == 'previous_payment_id'){ $previous_payment_ck = "checked='checked'";}
   				if($fieldname == 'payment_amount_id'){ $payment_amount_ck = "checked='checked'";}
   				if($fieldname == 'payment_date_id'){ $payment_date_ck = "checked='checked'";}
   				if($fieldname == 'applications_forms_id'){ $applications_forms_ck = "checked='checked'";}
   			}
			
   			if(!empty($get_all_data['enargy_no'])){ $meter = $get_all_data['enargy_no'];}else{$meter = 'n/a';}
			if(!empty($get_all_data['cin_no'])){ $cin = $get_all_data['cin_no'].'<a href="http://www.mca.gov.in/mcafoportal/findCIN.do" target="_blank" title="Ministry Of Corporate Affairs, About MCA, Ministry">(Verify CIN No.)</a>';}else{$cin = 'n/a';}
			if(!empty($get_all_data['factory_previous_name'])){ $previous_name = $get_all_data['factory_previous_name'];}else{$previous_name = 'n/a';}
			if(!empty($get_all_data['enargy_no'])){ $meter = $get_all_data['enargy_no'];}else{$meter = 'n/a';}
			if(!empty($get_all_data['trade_license_no'])){ $trade_no = $get_all_data['trade_license_no'];}else{$trade_no = 'n/a';}
	
   						
   		$output = '<div class="row">
   					<div class="box box-info">
   						<div class="box-header with-border">
                 				<center><h3 class="box-title"><b>Application for '.$service_name.'</b><br/>'.$type_of_application.'</center>
   						</div>
   					<div class = "box-body">
   					<table cellpadding="0" cellspacing="0" border="0" width="100%" class="table table-bordered custom-table-view"><tr>
   						<th width="30%">Parameters</th>
   						<th>Inputs</th>
   						<th width="8%" class="center"></th>
   					</tr>';
				
   		$output .= '<tr><td colspan="3">A.Factory Information</td></tr>
   					<tr>
   						<td>(i).Name of the factory</td>
   						<td>'.$get_all_data['factory_name'].'</td>
   						<td class="center"><input type="checkbox" id="factory_name" value="1" class="list_check_data" '.$factory_name_ck .' /></td>
   					</tr>
   					<tr>
   						<td>(ii).Ownership Type</td>
   						<td>'.$ownership_type.'</td>
   						<td class="center"></td>
   					</tr>
   					<tr>
   						<td>(iii).PAN of the Business Establishment / Factory / Company </td>
   						<td>'.$get_all_data['factory_pan'].'</td>
   						<td class="center"><input type="checkbox" id="factory_pan" class="list_check_data1" '.$factory_pan_ck.'disabled/></td>
   					</tr>
					<tr>
						<td>(iv).GSTIN No</td>
						<td>'.$get_all_data['gstin_no'].'</td>
						<td class="center"><input type="checkbox" id="gstin_no" class="list_check_data1" '.$gstin_no_ck.'disabled/></td>
					</tr>
					<tr>
						<td>(v).Udyog Adhaar No</td>
						<td>'.$get_all_data['udyog_aadhaar'].'</td>
						<td class="center"><input type="checkbox" id="udyog_aadhaar" class="list_check_data1" '.$udyog_aadhaar_ck.'disabled/></td>
					</tr>
					<tr>
						<td>(vii).Enargy Meter No</td>
						<td>'.$meter.'</td>
						<td class="center"><input type="checkbox" id="enargy_no" class="list_check_data1" '.$enargy_no_ck.'disabled/></td>
					</tr>
					<tr>
						<td>(vii).Trade License No</td>
						<td>'.$trade_no.'</td>
						<td class="center"><input type="checkbox" id="trade_no" class="list_check_data1" '.$trade_no_ck.'disabled/></td>
					</tr>
					<tr>
						<td>(ix).CIN No</td>
						<td>'.$cin.'</td>
						<td class="center"><input type="checkbox" id="cin_no" class="list_check_data1" '.$cin_no_ck.'disabled/></td>
					</tr>';
					if($factory_type_id==1 || $factory_type_id==2){
						$output .= '<tr>
							   <td>(x).Plan Approval number </td>
							   <td>'.$plan_approval_no.'</td>
							   <td class="center"><input type="checkbox" id="plan_approval_no" class="caf_verify_check1"'.$plan_approval_ck.' disabled/></td>
						   </tr>
						   <tr>
							   <td>(xi).Plan Approval Date </td>
							   <td>'.$plan_approval_date.'</td>
							   <td class="center"><input type="checkbox" id="plan_approval_date" class="caf_verify_check1" '.$plan_approval_date_ck.'disabled/></td>
						   </tr>';
						}else{
	
						$output .= '<tr>
							<td>(x).Plan Approval number </td>
							<td>NA</td>
							<td class="center"><input type="checkbox" id="plan_approval_no" class="caf_verify_check1"'.$plan_approval_ck.' disabled/></td>
						</tr>
						<tr>
							<td>(xi).Plan Approval Date </td>
							<td>NA</td>
							<td class="center"><input type="checkbox" id="plan_approval_date" class="caf_verify_check1" '.$plan_approval_date_ck.'disabled/></td>
						</tr>';
	
						}
						   
					$output .= '<tr><td colspan="3">B.Location of Factory </td></tr>
   					<tr>
   						<td>(i).Zone</td>
   						<td>'.$factory_zone_date['zone_name'].'</td>
   						<td rowspan="2" class="center"><input type="checkbox" id="zone_name" class="list_check_data1" '.$zone_name_ck.'disabled/></td>
   						</tr>
					<tr>
						<td>(ii) Nearest Landmark</td>
						<td colspan="2">'.$get_all_data['factory_location'].'</td>
					</tr>
   					<tr>
   						<td>(iii).Address</td>
   						<td>'.$factory_address_location.'</td>
					   </tr>
					   <tr>
   						<td>(ii).Telephone No</td>
   						<td>'.$get_all_data['comm_telephone'].'</td>
   						<td class="center"><input type="checkbox" id="telephone_no" class="list_check_data" '.$telephone_no_ck.' /></td>
   					</tr>
   					<tr>
   						<td>(iii).Mobile No</td>
   						<td>'.$get_all_data['comm_mobile'].'</td>
   						<td class="center"><input type="checkbox" id="mobile_no" class="list_check_data" '.$mobile_no_ck.'/></td>
   					</tr>
   					<tr>
   						<td>(iv).Fax No</td>
   						<td>'.$get_all_data['comm_fax'].'</td>
   						<td class="center"><input type="checkbox" id="fax_no" class="list_check_data" '.$fax_no_ck.'/></td>
   					</tr>
   					<tr>
   						<td>(iv).Email Id</td>
   						<td>'.$get_all_data['comm_email'].'</td>
   						<td class="center"><input type="checkbox" id="email_no" class="list_check_data" '.$email_no_ck.'/></td>
   					</tr>
   					<tr>
   						<td colspan="3">C.Address of the Registered office / Head office<br/><font color="#FF0000">(N.B:-This address will be treated as communication address as per Section 7 of Factories Act,1948 )</font> </td>
   					</tr>
   					<tr>
   						<td>(i).Address</td>
   						<td>'.$headoffice_address.'</td>
   						<td class="center"><input type="checkbox" id="factory_headoffice" class="list_check_data" '.$factory_headoffice_ck.'/></td>
   					</tr>
   					
   					<tr>
   						<td colspan="2">D.Details of owner of the premises occupied as a factory</td>
					</tr>
					<tr>
   						<td>(i)Owner list</td>
   						<td>'.$link_owner.'</td>
   						<td class="center"><input type="checkbox" id="premises_address" class="list_check_data1" '.$owner_name_ck.'disabled/></td>
   					</tr>
   					
   					<tr><td>E.Factory Identification according to WBPCB</td>
						<td>'.$details.'</td>
						<td class="center"><input type="checkbox" id="wbpcb_id" class="list_check_data1" '.$wbpcb_id_ck.'disabled/></td>
					</tr>

   					<tr><td colspan="3">F.State the period of licence</td></tr>
   					<tr>
   						<td>(i).Date from which the premises is occupied or been taken into use as factory </td>
   						<td>'.date('dS M Y', strtotime($get_all_data['date_of_amenability'])).'</td>
   						<td class="center"><input type="checkbox" id="date_of_amenability_id" class="list_check_data1" '.$date_of_amenability_id_ck.'disabled/></td>
   					<tr>
   						<td>(ii).State the period of license required </td>
   						<td>'.$get_all_data['period_for_application'].'year(s)</td>
   						<td class="center"><input type="checkbox" id="period_for_application_id" class="list_check_data1" '.$period_for_application_id_ck.'disabled/></td>
   			
					</tr>
					<tr><td>(ii)Registration Number and date</td>
					   <td>'.$reg_details.'</td>
					   <td class="center"><input type="checkbox" id="period_for_application_id" class="list_check_data1" '.$period_for_application_id_ck.'disabled/></td>
				   <tr><td>(iii). License number and validupto Date </td>
				   <td>'.$license_details.'</td>
				   <td class="center"><input type="checkbox" id="period_for_application_id" class="list_check_data1" '.$period_for_application_id_ck.'disabled/></td>
				   </tr>
				   <tr><td>(iv).State the period of license  </td>
				   <td>'.$period_for_application.'year(s)</td>
				   <td class="center"><input type="checkbox" id="period_for_application_id" class="list_check_data1" '.$period_for_application_id_ck.'disabled/></td>
				   </tr>';
					   if(!empty($is_previous)){
						$output .= '
						<tr>
							<td>(iii).Whethere any changes name and ownership details of factory </td>
							<td>'.$is_previous.$view.'</td>
							<td class="center"><input type="checkbox" id="previous_name_id" class="list_check_data1" '.$previous_name_id_ck.'disabled/></td>
						</tr>';

					   }
   					
   					$output .= '<tr>
   						<td colspan="3">G.Worker Details</td></tr>
   					<tr>
   						<td>(i).Maximum number of workers employed or to be employed in tha factory</td>
   						<td>'.$link_worker.'</td>
   						<td class="center"><input type="checkbox" id="worker_details" class="list_check_data" '.$worker_details_ck.'/>
   					</tr>
   					<tr>
   						<td colspan="3">H.Power Details</td>
   					</tr>
   					<tr>
   						<td>(i).Installed Power or to be installed power </td>
   						<td>'.$power_details.'</td>
   						<td class="center"><input type="checkbox" id="power_details" class="list_check_data" '.$power_details_ck.'/></td>
   					</tr>
   					<tr>
   						<td colspan="3">I.Manager Details</td>
   					</tr>
   					<tr>
   						<td>(i).Manager Details</td>
   						<td>'.$link_manager.'</td>
   						<td class="center"><input type="checkbox" id="manager_details" class="list_check_data" '.$manager_details_ck.'/></td>
   					</tr>
   					<tr>
   						<td colspan="3">J.Occupier Details</td>
   					</tr>
   					<tr>
   						<td>(i).View occupier details</td>
   						<td>'.$link_occuiper.'</td>
   						<td class="center"><input type="checkbox" id="occupier_details" class="list_check_data" '.$occupier_details_ck.'/></td>
   					</tr>
   					<tr>
   						<td colspan="3">K.Director Details</td>
   					</tr>
   					<tr>
   						<td>(i).View director details</td>
   						<td>'.$link_director.'</td>
   						<td class="center"><input type="checkbox" id="director_details" class="list_check_data"'.$director_details_ck.'/></td>
   				   </tr>
   				  <tr>
   						<td colspan="3">L.Manufacturing process</td>
   				</tr>
   				<tr>
   					<td>(i).Carried/to be carried on the factory</td>
   					<td>'.$nature_work.'</td>
   					<td class="center"><input type="checkbox" id="nature_details" class="list_check_data1" '.$nature_details_ck.' disabled/></td>
   				</tr>
   				<tr>
   					<td colspan="3">M.Uploaded Documents</td>
   				</tr>
   				<tr>
   					<td>(i).View uploaded documetns</td>
   					<td>'.$link_documents.'</td>
   					<td class="center"></td>
   				</tr>
   			
   				<tr><td>N. Common Application Forms</td>
					<td><b>'.$application_from.'</b></td>
					<td class="center"></td>
				</tr></table>';
				
			$output.='</div></div></div>';
   return $output;
}

function change_amendment_list_dashboard_submit($form, &$form_state){
	global 						$user;
	$uid 					=	$user->uid;
	$val   					= 	$form_state['values'];
	//print_r($val);die;
	$license_for_period		=	$val['license_for_period'];
	$vaild_license_date		=	$val['vaild_license_date'];
	$factorytype_id 		= 	encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
	$reference_no			=  	encryption_decryption_fun('decrypt',$val['referance_no_hidden']);
	$application_id 		= 	encryption_decryption_fun('decrypt',$val['application_id_hidden']);
	$service_id 			= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']); 
	$eservice_name			=  "amendment";
	if($val['fieldname'] =='' || $val['fieldname']== NULL || empty($val['fieldname'])){

		drupal_set_message('Please check any check box of go for Amendment without any change' ,'Warning');
		
	}else{
	
		$remark_data = explode(',', $val['fieldname']);
		if(in_array("factory_name", $remark_data)) {

			if(in_array("occupier_details", $remark_data) && in_array("director_details", $remark_data)){

				$cafa_field = array(
					'app_id'			=> $application_id,
					'factory_type' 		=> $factorytype_id,
					'reference_no' 	 	=> $reference_no,
					'service_id'		=> $service_id,
					'fieldname'			=> $val['fieldname'],
					'application_status'=> 'In',
					'created_by'		=> $uid,
				);
				//print_r($cafa_field);die;
				$check_point_id =  fun_check_check_point($application_id,$reference_no,$factorytype_id,$service_id);
				if(empty($check_point_id)|| ($check_point_id == NULL) ||($check_point_id==0)){
					db_insert('fa_caf_check_point')->fields($cafa_field)->execute();
				}else{
					$previous_year	=	db_update('fa_caf_check_point');
					$previous_year	->	fields($cafa_field);
					$previous_year	->	condition('app_id',$application_id,'=');
					$previous_year	->	condition('reference_no',$reference_no,'=');
					$previous_year	->	condition('factory_type',$factorytype_id,'=');
					$previous_year	->	condition('service_id',$service_id,'=');
					$previous_year	->	execute();
				}
				//echo $reference_no;die();
				drupal_goto('applicant/check-amendment-year/'.$val['application_id_hidden'].'/'.$val['serviceid_hidden'].'/'.$val['factorytype_hidden'].'/'.$val['referance_no_hidden']);
				
			}else{
				drupal_set_message('You mast need to notice of occupier.' ,'Warning');
			}
		}
        else {  

			$cafa_field = array(
				'app_id'			=> $application_id,
				'factory_type' 		=> $factorytype_id,
				'reference_no' 	 	=> $reference_no,
				'service_id'		=> $service_id,
				'fieldname'			=> $val['fieldname'],
				'application_status'=> 'In',
				'created_by'		=> $uid,
				
			);
			//print_r($cafa_field);die;
			$check_point_id =  fun_check_check_point($application_id,$reference_no,$factorytype_id,$service_id);
			if(empty($check_point_id)|| ($check_point_id == NULL) ||($check_point_id==0)){
				db_insert('fa_caf_check_point')->fields($cafa_field)->execute();
			}else{
				$previous_year	=	db_update('fa_caf_check_point');
				$previous_year	->	fields($cafa_field);
				$previous_year	->	condition('app_id',$application_id,'=');
				$previous_year	->	condition('reference_no',$reference_no,'=');
				$previous_year	->	condition('factory_type',$factorytype_id,'=');
				$previous_year	->	condition('service_id',$service_id,'=');
				$previous_year	->	execute();
			}
			//echo $reference_no;die();
			drupal_goto('applicant/check-amendment-year/'.$val['application_id_hidden'].'/'.$val['serviceid_hidden'].'/'.$val['factorytype_hidden'].'/'.$val['referance_no_hidden']);
		}

	}
	
}

?>