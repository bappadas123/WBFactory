<?php
function plansection_application_verify($form, &$form_state,$serviceid ,$factory_typeid,$applicationid ,$referenceid){
	
	global $base_root,$base_path,$user;
	
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
 	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
 	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
 	$reference_no 	    = encryption_decryption_fun('decrypt',$referenceid);
	$value_app ='';
	
	$form = array();
	if (!empty($application_id)) {
        $get_fa_cafa           				= 	get_fa_cafa($application_id);

       	$application_status      			= 	$get_fa_cafa['application_status'];
		$factory_plan_identification_number	= 	$get_fa_cafa['plan_approve_identification_number'];
		$factory_referance_number			= 	$get_fa_cafa['reference_number'];	
		$applicant_users					= 	$get_fa_cafa['created_by'];	
		$get_created_date					= 	$get_fa_cafa['created_date'];
    }

	$form['serviceid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$service_id)
	);	
	$form['factorytype_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$factory_type_id)
	);		  
	$form['factory_identification_number_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> empty($factory_plan_identification_number)?'':encryption_decryption_fun('encrypt',$factory_plan_identification_number)
	);	   
	$form['referance_no_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$reference_no),
	);
	$form['applicationid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt', $application_id),
	);
	$form['applicant_id_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt', $applicant_users),
	);
	$form['created_date_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $get_created_date,
	);
	
	$title = ($service_id=='4') ? 'Application for Approval of Plan' : 'Application for Extension of Existing Plan';
	
	$form['header'] = array(
		'#markup' 			=> t('<div class="cus-page-outer-view"><div class="content"><center class="verify-top-title-pad"><h3>'.$title.'</h3><p>All inputs are provided by applicant only</p><p>All inputs are to be verified by officials</p></center>'),
	);
	  
	$form['applicantion_verify']['markup_appplication'] = array(
			'#type' 			=> 'markup',
			'#markup' 			=> get_verifing_data($application_id,$service_id,$factory_type_id,$reference_no),
			);
	
	/*$form['applicantion_verify']['fieldname']	= array(
												'#title'				=> 'Field Name',
												'#type'					=> 'hidden',
												'#attributes'			=> array('id' => 'plansection_verify'),
												'#default_value' 		=> !empty($content['verify_details']) ? $content['verify_details'] : '',
												);*/

	$form['applicantion_doc_verify']['doc_fieldname']	= array(
												'#title'				=> 'Field Name',
												'#type'					=> 'hidden',
												'#attributes'			=> array('id' => 'plansection_doc_verify'),
												'#default_value' 		=> !empty($content['doc_verify']) ? $content['doc_verify'] : '',
												);
	// DOWNLOAD DSC PDF
	$form['application_pdf'] = array(
        '#type' => 'fieldset',
        '#title' => t('Application Form'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
	
	$get_uploaded_doc = get_uploaded_document_url($get_fa_cafa['uploaded_pdf']);
	$pdf_link = l('<i class="ace-icon fa fa-file-pdf-o bigger-130 text-red"></i> Application Form',file_create_url($get_uploaded_doc),array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank','class'=>array('text-blue')))).'<br>';		

	$form['application_pdf']['download'] = array(
			'#prefix' => '<div class="col-md-12 col-xs-12">'.$pdf_link,
			'#suffix' => '</div>',
  	);
	
		/* REMARKS/NOTESHEET */
	$form['application_forward'] = array(
        '#type' => 'fieldset',
        '#title' => t('Action'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
	
	$users_action= array(	
					'0'=>'Select',
					'1'=>'Forward to Inspector',
				);
				
	$form['application_forward']['forward_user'] 	= array(
			  '#prefix' 		=> '<div class="row"><div class="col-md-4 col-xs-12"><label class="select">Necessary action to be taken:<span id=\'star\'>*</span>',
			  '#suffix' 		=> '</label></div>',
			  '#type' 			=> 'select',
			  '#options' 		=> $users_action,
			  '#default_value' 	=> $value_app,
			  '#required' 		=> TRUE,
			);

	$action   = isset($form_state['values']['forward_user']) ? $form_state['values']['forward_user'] : $value_app;
	
    // ---------------  Add more text box ends ---------------------------------
	
	$form['application_forward']['submit'] = array(
        '#prefix' => '<div class="col-md-12 col-xs-12">',
        '#suffix' => '</div>',
        '#attributes' => array('class' => array('btn btn-info margin'), 'onclick' => 'if(!confirm("Are you sure to continue ?")){return false;}'),
        '#type' => 'submit',
        '#value' => 'Send'
    );

    return $form;
        
   }

function get_ajax_note($form, &$form_state)
	{
		$commands   = array();
		$commands[] = ajax_command_replace('#reverse_id', drupal_render($form['application_forward']['application_remark']));
		$commands[] = ajax_command_replace('#notesheet_id', drupal_render($form['application_forward']['application_note']));
		$commands[] = ajax_command_replace('#condition_id', drupal_render($form['application_forward']['conditions']));
		return array('#type' => 'ajax', '#commands' => $commands);;
	}

function plansection_application_verify_validate($form, &$form_state) { 
  	 
  $val   					= 	$form_state['values'];
  
  $service_id 				= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']); 
  $factorytype_id 			= 	encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
	  
  $documentList =  get_plan_document_lists($service_id,$factorytype_id);
  $other_documentList =  get_other_plan_document_lists($service_id,$factorytype_id);
  
  for($j=0; $j< count($documentList); $j++)
	{
	   if($j=='0') 	   {$position = '1st';}
	   elseif($j=='1') {$position = '2nd';}
	   elseif($j=='2') {$position = '3rd';}
	   elseif($j=='3') {$position = '4th';}
	   elseif($j=='4') {$position = '5th';}
	   
	   if (isset($form_state['values']['verify'.$j]) && ($form_state['values']['verify'.$j]=='select'))
	   {
       	form_set_error('verify'.$j, 'Please check '.$position.' document!');    
	   }
  	}
	   if (isset($form_state['values']['forward_user']) && ($form_state['values']['forward_user']=='0'))
	   {
       	form_set_error('forward_user', 'Please select an action!');    
	   }
}

function plansection_application_verify_submit($form, &$form_state){
	  global $user;
	  $uid = $user->uid;
	  $uname = $user->name;
	  $user_role = array_keys($user->roles);
	  $urole  = $user_role[1];
	  $current_application_status =   '';
	  $doc_verify = array();
	  
	  $val   				= 	$form_state['values'];
	  //echo "<pre>"; print_r($val); die;
	  $service_id 			= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	  $factorytype_id 		= 	encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
	  //$plan_approve_status 	= 	encryption_decryption_fun('decrypt',$val['plan_approve_status_hidden']);
	  $application_id 		= 	encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	  $reference_no			=  	encryption_decryption_fun('decrypt',$val['referance_no_hidden']);
	   
	 /*$documentList =  get_plan_document_lists($service_id,$factorytype_id);
		for($i=0; $i< count($documentList); $i++)
		{
			//$doc_verify[]= $val['verify'.$i];
			$doc_verify[]= 'document_details_'.$i;
		}
	
	   $doc_verify = implode(",", $doc_verify);
	   echo "<pre>"; print_r($doc_verify); die;*/
	   // MANUAL FORWARDING
	   if($val['forward_user']=='0'){
				drupal_set_message('Please select an action','error');
			}
	   else if($val['forward_user']=='1')
			{
				$current_application_status = 'AI';
				$type='r';
				$details = $val['application_remark'];
	  
			  //---------------- CAFA TABLE UPDATE -------------------
			  
				$approval_status = 	array('plan_approve_status' => $current_application_status);
				$queryapp 		 =	db_update('fa_cafa');
				$queryapp		 ->	fields($approval_status);
				$queryapp		 ->	condition('id',$application_id,'=');
				$queryapp		 ->	condition('service_id',$service_id,'=');
				$queryapp	     ->	condition('factory_typeid',$factorytype_id,'=');
				$queryapp		 ->	condition('reference_number',$reference_no,'=');
				$queryapp		 ->	execute();
		
			  //----------- WORKER TABLE UPDATE ---------------------------
			  
				$worker_status 	= 	array('worker_plan_approval_status' => $current_application_status);
				$querywork 		=	db_update('fa_worker_details');
				$querywork		->	fields($worker_status);
				$querywork		->	condition('application_id',$application_id,'=');
				$querywork		->	condition('service_id',$service_id,'=');
				$querywork		->	condition('factory_type',$factorytype_id,'=');
				$querywork		->	condition('application_reference_no',$reference_no,'=');
				$querywork		->	execute();
			  
			  //----------------DOCUMENTS TABLE UPDATE-------------------
				$doc_status 	= 	array('plan_approval_status' => $current_application_status);
				$querydoc 		=	db_update('fa_caf_upload_doc');
				$querydoc		->	fields($doc_status);
				$querydoc		->	condition('app_id',$application_id,'=');
				$querydoc		->	condition('upload_documents_service_id',$service_id,'=');
				$querydoc	    ->	condition('upload_doc_factory_type_id',$factorytype_id,'=');
				$querydoc		->	condition('application_reference_no',$reference_no,'=');
				$querydoc		->	execute();
				
			  //----------------OCCUPIER DETAILS TABLE UPDATE-------------------
				$occupr_status 	= 	array('worker_plan_approval_status' => $current_application_status);
				$querydic 		=	db_update('fa_occupier_details');
				$querydic		->	fields($occupr_status);
				$querydic		->	condition('application_occupier_id',$application_id,'=');
				$querydic		->	condition('occupier_service_id',$service_id,'=');
				$querydic		->	condition('factory_type_id',$factorytype_id,'=');
				$querydic		->	condition('application_reference_no',$reference_no,'=');
				$querydic		->	execute();
		
			//----------------Remarks Table Insert -------------------
			
				$cafa_remarks = array(
					'app_id'   			 => $application_id,
					'remark_by_uid' 	 => $uid,
					'remark_by_roleid'   => $urole,
					'remark_by_name' 	 => $uname,
					'sending_time' 		 => date('Y-m-d h:i:s'),
					'app_reference_no' 	 => $reference_no,
					'doc_verify' 	     => trim(preg_replace("/,+/", ",", $val['doc_fieldname']), ","),
					'plan_status' 		 => 'AI',
				);	

				db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();
			   
				drupal_set_message('Application has been successfully forwarded to Inspector.');
				//drupal_goto('plansection-list/');
				if($service_id == '4') { 
					drupal_goto('plansection-list/');
				} else {
					drupal_goto('plan-extension-list/');
				}
				
			}
 }
 
	// ---------------  AJAX CALLBACK  FUNCTIONS FOR TEXT FIELD-----------------
function get_verifing_data($application_id,$service_id,$factory_type_id,$reference_no)
	{
		//echo $reference_no;
		global $base_root,$base_path,$user;		 
		$user_id = $user->uid;
			
		$veryfing_details 	= array();
		$veryfing_details 	= get_application_withid($application_id);
		
		$plan_approve_status  =   $veryfing_details[0]->plan_approve_status;
	
		$occupier_details 	= get_occupier_data($application_id);
		$worker_details 	= get_worker_details_service($service_id,$factory_type_id,$application_id,$reference_no);
		
		$getdata_director_paddress =  array('district_director','sub_division_director','area_type_director','block_mun_cor_sez_not_director','grm_ward_sector_not_director','police_station_director','pincode_director','state_director','post_office_director');
	
		/* FACTORY ADDRESS PART */
		$getdata_factory_address 	=  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
		$getdata_headoffice_address =  array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
		$getdata_owner_premises_address 	=  array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
		$getdata_occupier_permanent_address =  array('district_oprmntadr','subdivision_oprmntadr','areatype_oprmntadr','block_oprmntadr','panchayat_oprmntadr','policestation_oprmntadr','pincodeoprmntadr','state_oprmntadr','postoffice_oprmntadr');
		$getdata_occupier_present_address =  array('district_oprsntadr','subdivision_oprsntadr','areatype_oprsntadr','block_oprsntadr','panchayat_oprsntadr','policestation_oprsntadr','pincodeoprsntadr','state_oprsntadr','postoffice_oprsntadr');
	
		foreach($veryfing_details as $details_address_info){
			$factory_address 			= get_full_address('fa_cafa','sub-table',$details_address_info->id,$getdata_factory_address);
			$headoffice_address 		= get_full_address('fa_cafa','sub-table',$details_address_info->id,$getdata_headoffice_address);
			$permanent_address        	= get_full_address('fa_cafa','sub-table',$details_address_info->id,$getdata_occupier_permanent_address);
			$present_address          	= get_full_address('fa_cafa','sub-table',$details_address_info->id,$getdata_occupier_present_address);
			$owner_premises_address 	= get_full_address('fa_cafa','sub-table',$details_address_info->id,$getdata_owner_premises_address);		
			}
				$get_remark = db_select('fa_cafa_remarks', 'remarks');
				$get_remark->fields('remarks', array('verify_details'));
				$get_remark->condition('remarks.app_id', trim($application_id));
				//$get_remark->condition('remarks.remark_by_uid', trim($user_id), '=');
				$get_remark->orderBy('remarks.id','DESC');
				$get_remark->range(0, 1);
				$get_remark_result = $get_remark->execute();		
				$content = $get_remark_result->fetchAssoc();
				
				$remark_field = explode(',', $content['verify_details']);
				
				foreach ($remark_field as $fieldname){ 
					if($fieldname == 'factory_name'){ $factory_name_ck = "checked='checked'";}
					if($fieldname == 'factory_previous_name'){ $factory_previous_name_ck = "checked='checked'";}
					if($fieldname == 'factory_location'){ $zone_name_ck = "checked='checked'";}
					if($fieldname == 'factory_headoffice'){ $factory_headoffice_ck = "checked='checked'";}
					if($fieldname == 'factory_pan'){ $factory_pan_ck = "checked='checked'";}
					if($fieldname == 'occupier_name'){ $occupier_name_ck = "checked='checked'";}
					if($fieldname == 'occupier_age'){ $occupier_age_ck = "checked='checked'";}
					if($fieldname == 'occupier_gurdian_name'){ $occupier_gurdian_name_ck = "checked='checked'";}
					if($fieldname == 'occupier_telephone'){ $occupier_telephone_ck = "checked='checked'";}
					if($fieldname == 'occupier_fax_no'){ $occupier_fax_no_ck = "checked='checked'";}
					if($fieldname == 'occupier_mobile'){ $occupier_mobile_ck = "checked='checked'";}
					if($fieldname == 'occupier_email_id'){ $occupier_email_id_ck = "checked='checked'";}
					if($fieldname == 'occupier_type'){ $occupier_type_ck = "checked='checked'";}
					if($fieldname == 'occupier_nationality'){ $occupier_nationality_ck = "checked='checked'";}
					if($fieldname == 'occupier_present_address'){ $occupier_present_address_ck = "checked='checked'";}
					if($fieldname == 'owner_name'){ $owner_name_ck = "checked='checked'";}
					if($fieldname == 'owner_address'){ $owner_address_ck = "checked='checked'";}
					if($fieldname == 'worker_men'){ $worker_men_ck = "checked='checked'";}
					if($fieldname == 'worker_women'){ $worker_women_ck = "checked='checked'";}
					if($fieldname == 'adolescents_male'){ $adolescents_male_ck = "checked='checked'";}
					if($fieldname == 'adolescents_female'){ $adolescents_female_ck = "checked='checked'";}
					if($fieldname == 'children_male'){ $children_male_ck = "checked='checked'";}
					if($fieldname == 'children_female'){ $children_female_ck = "checked='checked'";}
				}
	
			if($service_id == '5')
			{
				$previous_factory_name = '<tr><td>Previous Factory Name</td><td>'.$veryfing_details[0]->factory_previous_name.'</td><td><input type="checkbox" disabled id="factory_previous_name" class="plansection_verify_check" '.$factory_previous_name_ck .'/></td></tr>';
			} else {$previous_factory_name = '';}
			
			$addrline = !empty($factory_address) ? '<br>'.$veryfing_details[0]->addrline : $veryfing_details[0]->addrline;
			$addrline_off = !empty($headoffice_address) ? '<br>'.$veryfing_details[0]->addrline_off : $veryfing_details[0]->addrline_off;
			$addrline_oprmntadr = !empty($permanent_address) ? '<br>'.$veryfing_details[0]->addrline_oprmntadr : $veryfing_details[0]->addrline_oprmntadr;
			$addrline_oprsntadr = !empty($present_address) ? '<br>'.$veryfing_details[0]->addrline_oprsntadr : $veryfing_details[0]->addrline_oprsntadr;
			$addrline_premises = !empty($owner_premises_address) ? '<br>'.$veryfing_details[0]->addrline_premises : $veryfing_details[0]->addrline_premises;
						
			$output .= '<table cellpadding="0" cellspacing="0" border="0" width="100%" class="table no-margin custom-table-view-dashboard">';
			
			$output .= '<tr><th width="25%">Parameter</th><th>Input</th><th width="11%" class="center">Verify </th></tr>
						<tr><td colspan="3"><b>FACTORY INFORMATION</b></td></tr>
						<tr><td>Factory Name</td><td>'.$veryfing_details[0]->factory_name.'</td> <td><input type="checkbox" disabled id="factory_name" class="plansection_verify_check" '.$factory_name_ck .' /></td></tr>'.$previous_factory_name;			
	
			$output .= '<tr><td colspan="3"><b>LOCATION OF FACTORY</b></td></tr>
						<tr><td>Factory Zone</td><td>'.$veryfing_details[0]->zone_name.'</td> <td rowspan="2"><input type="checkbox" disabled id="factory_location" class="plansection_verify_check" '.$zone_name_ck.'/></td></tr>
						<tr><td>Factory Address</td><td colspan="2">'.$factory_address.''.$addrline.'</td></tr>';
	
			$output .= '<tr><td colspan="3"><b>ADDRESS OF THE REGISTERED / HEAD OFFICE </b><br><span class="text-red" style="font-size:10px;"> (N.B:- This address will be treated as communication address as per Section 7 of Factories Act, 1948)</span></td></tr>
						<tr><td>Registered / Head office Address</td><td>'.$headoffice_address.''.$addrline_off.'</td> <td><input type="checkbox" disabled id="factory_headoffice" class="plansection_verify_check" '.$factory_headoffice_ck.'/></td></tr>
						<tr><td>Mobile</td><td colspan="2">'.$veryfing_details[0]->comm_mobile.'</td></tr>
						<tr><td>Telephone</td><td colspan="2">'.$veryfing_details[0]->comm_telephone.'</td></tr>
						<tr><td>Fax</td><td colspan="2">'.$veryfing_details[0]->comm_fax.'</td></tr>
						<tr><td>Email</td><td colspan="2">'.$veryfing_details[0]->comm_email.'</td></tr>';
	
			$output .= '<tr><td colspan="3"><b>PAN OF BUSINESS ESTABLISHMENT / FACTORY / COMPANY</b></td></tr>
						<tr><td>PAN</td><td>'.$veryfing_details[0]->factory_pan.'</td> <td><input type="checkbox" disabled id="factory_pan" class="plansection_verify_check" '.$factory_pan_ck.'/></td></tr>';
	
			$output .= '<tr><td colspan="3"><b>DETAILS OF OCCUPIER</b></td></tr>
						<tr><td>Name</td><td>'.$veryfing_details[0]->occupier_name.'</td> <td><input type="checkbox" disabled id="occupier_name" class="plansection_verify_check" '.$occupier_name_ck.'/></td></tr>
						<tr><td>Age</td><td>'.$veryfing_details[0]->occupier_age.'</td> <td><input type="checkbox" disabled id="occupier_age" class="plansection_verify_check" '.$occupier_age_ck.'/></td></tr>
						<tr><td>Father\'s/Husband\'s name</td><td>'.$veryfing_details[0]->occupier_gurdian_name.'</td> <td><input type="checkbox" disabled id="occupier_gurdian_name" class="plansection_verify_check" '.$occupier_gurdian_name_ck.'/></td></tr>
						<tr><td>Telephone Number</td><td>'.$veryfing_details[0]->occupier_telephone.'</td> <td><input type="checkbox" disabled id="occupier_telephone" class="plansection_verify_check" '.$occupier_telephone_ck.'/></td></tr>
						<tr><td>Fax No.</td><td>'.$veryfing_details[0]->occupier_fax_no.'</td> <td><input type="checkbox" disabled id="occupier_fax_no" class="plansection_verify_check" '.$occupier_fax_no_ck.'/></td></tr>
						<tr><td>Registered Mobile Number</td><td>'.$veryfing_details[0]->occupier_mobile.'</td> <td><input type="checkbox" disabled id="occupier_mobile" class="plansection_verify_check" '.$occupier_mobile_ck.'/></td></tr>
						<tr><td>Email Id</td><td>'.$veryfing_details[0]->occupier_email_id.'</td> <td><input type="checkbox" disabled id="occupier_email_id" class="plansection_verify_check" '.$occupier_email_id_ck.'/></td></tr>
						<tr><td>Occupier Type</td><td>'.$veryfing_details[0]->occupier_type.'</td><td><input type="checkbox" disabled id="occupier_type" class="plansection_verify_check" '.$occupier_type_ck.'/></td></tr>
						
						<tr><td>Nationality</td><td>'.$veryfing_details[0]->occupier_nationality.'</td> <td><input type="checkbox" disabled id="occupier_nationality" class="plansection_verify_check" '.$occupier_nationality_ck.'/></td></tr>';
						
						if($veryfing_details[0]->occupier_nationality == 'Indian')
						{
							$output .= '<tr><td>Aadhaar No.</td><td colspan="2">'.$veryfing_details[0]->occupier_aadhaar.'</td></tr>';
						} else {
							$output .= '<tr><td>Passport No.</td><td colspan="2">'.$veryfing_details[0]->occupier_passport.'</td></tr>';
						}
						
			$output .= '<tr><td>Permanent Address</td><td colspan="2">'.$permanent_address.''.$addrline_oprmntadr.'</td></tr>
						
						<tr><td>Present Address</td><td>'.$present_address.''.$addrline_oprsntadr.'</td><td><input type="checkbox" disabled id="occupier_present_address" class="plansection_verify_check" '.$occupier_present_address_ck.'/></td></tr>';
	
			$output .= '<tr><td colspan="3"><b>DETAILS OF OWNER/LAND LORD/LESSOR OF THE PREMISES OCCUPIED AS A FACTORY</b></td></tr>
						<tr><td>Owner Name</td><td>'.$veryfing_details[0]->owner_name.'</td><td><input type="checkbox" disabled id="owner_name" class="plansection_verify_check" '.$owner_name_ck.'/></td></tr>
						<tr><td>Owner Address</td><td>'.$owner_premises_address.''.$addrline_premises.'</td><td><input type="checkbox" disabled id="owner_address" class="plansection_verify_check" '.$owner_address_ck.'/></tr>';
	
			$output .= '<tr><td colspan="3"><b>WORKER DETAILS</b></td></tr>
						<tr><td>No. of Male Worker</td><td>'.$worker_details[0]->worker_men.'</td><td><input type="checkbox" disabled id="worker_men" class="plansection_verify_check" '.$worker_men_ck.'/></td></tr>
						<tr><td>No. of Female Worker</td><td>'.$worker_details[0]->worker_women.'</td><td><input type="checkbox" disabled id="worker_women" class="plansection_verify_check" '.$worker_women_ck.'/></td></tr>			
						<tr><td>No. of Male Adolescents Worker <br><span class="text-red" style="font-size:10px;">(over 15 but under 18 years of age)</span></td><td>'.$worker_details[0]->adolescents_male.'</td><td><input type="checkbox" disabled id="adolescents_male" class="plansection_verify_check" '.$adolescents_male_ck.'/></td></tr>
						<tr><td>No. of Female Adolescents Worker</td><td>'.$worker_details[0]->adolescents_female.'</td><td><input type="checkbox" disabled id="adolescents_female" class="plansection_verify_check" '.$adolescents_female_ck.'/></td></tr>			
						<tr><td>No. of Male Children Worker <br><span class="text-red" style="font-size:10px;">(over 14 but under 15 years of age)</span></td><td>'.$worker_details[0]->children_male.'</td><td><input type="checkbox" disabled id="children_male" class="plansection_verify_check" '.$children_male_ck.'/></td></tr>
						<tr><td>No. of Female Children Worker</td><td>'.$worker_details[0]->children_female.'</td><td><input type="checkbox" disabled id="children_female" class="plansection_verify_check" '.$children_female_ck.'/></td></tr>';
					
		$documentList =  get_plan_document_lists($service_id,$factory_type_id);

		$output .= '<tr><td colspan="3"><b>DOCUMENT DETAILS</b></td></tr>
						<tr>
							<td colspan="3">'; 
		$output .= 			'<table cellpadding="0" cellspacing="0" border="0" width="100%" class="table no-margin custom-table-view-dashboard">
									<tr>
										<th width="45%">Required Document</th>
										<th>Uploaded Document</th>
										<th width="6%">Action</th>
									</tr>';
									/*  IF ALREADY VERIFIED */
									    //$checked = get_verified_field($application_id, $reference_no, $plan_approve_status);
										//$verify_details      = ($checked['doc_verify'])? $checked['doc_verify'] : ''; 
										//$remark_field        = explode(',', trim($checked['doc_verify'],","));
										
									for($i=0; $i< count($documentList); $i++) //{foreach($resultData as $val)
									{
										$uploaded_documentList =  get_plan_uploaded_document_lists($service_id,$factory_type_id,$application_id,$doc_id);
										
										$uploaded_doc_name = $uploaded_documentList[0]->doc_name ? $uploaded_documentList[0]->doc_name : '--';
										$displayLink = l('<i class="ace-icon fa fa-file-pdf-o bigger-130 text-red"></i>',file_create_url($uploaded_documentList[0]->uri),array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_BLANK')));
										$uploaded_link = $uploaded_documentList[0]->uri ? $displayLink.' ' : '';
										
										if (in_array('document_details_'.$i, $remark_field)) { $verify_status ='checked="checked"';}
										else { $verify_status ='';}
				
									$output.= '<tr>
											
										<td>'.$documentList[$i]->document_name.'</td>
										<td>'.$uploaded_link.' '.$uploaded_doc_name.'</td>
										<td><select name="verify" id="document_details_'.$i.'" class="plansection_doc_verify_check" '.$document_details_ck.' '.$verify_status.'/>
										<option value="0">- Select -</option>
										<option value="uploaded">Document Uploaded</option>
										<option value="notuploaded">Document Not Uploaded</option>
										</select></td>
							</tr>';
				}
								$output.='</table>';

		/*$other_documentList =  get_other_plan_document_lists($service_id,$factory_type_id);
		
		$output .= 			'<table cellpadding="0" cellspacing="0" border="0" width="100%" class="table no-margin custom-table-view-dashboard">
									<tr>
										<th width="45%">Other Document</th>
										<th>Uploaded Document</th>
										<th width="6%">Action</th>
									</tr>';
										
									for($j= 0; $j< count($other_documentList); $j++) //{foreach($resultData as $val)
									{
										$doc_id_other = $other_documentList[$j]->id;
										$uploaded_documentList =  get_plan_uploaded_document_lists($service_id,$factory_type_id,$application_id,$doc_id_other);
										
										$uploaded_doc_name = $uploaded_documentList[0]->doc_name ? $uploaded_documentList[0]->doc_name : '--';
										$displayLink = l('<i class="ace-icon fa fa-file-pdf-o bigger-130 text-red"></i>',file_create_url($uploaded_documentList[0]->uri),array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_BLANK')));
										$uploaded_link = $uploaded_documentList[0]->uri ? $displayLink.' ' : '';
										
										if (in_array('document_details_'.$i, $remark_field)) { $verify_status ='checked="checked"';}
										else { $verify_status ='';}
				
									$output.= '<tr>
											
										<td>'.$other_documentList[$j]->document_name.'</td>
										<td>'.$uploaded_link.' '.$uploaded_doc_name.'</td>
										<td><select id="document_details_'.$j.'" class="plansection_doc_verify_check" '.$document_details_ck.' '.$verify_status.'/>
										<option value="0">- Select -</option>
										<option value="uploaded">Document Uploaded</option>
										<option value="notuploaded">Document Not Uploaded</option>
										</select></td>
							</tr>';
				}*/
								$output.='</table>';
				
				$output.='</td>
						</tr>';
					
			 $output .= '</table>';		
			 return $output;
	}

?>