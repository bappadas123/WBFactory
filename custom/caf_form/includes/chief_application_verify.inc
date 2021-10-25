<?php
//$applicationid
function chief_application_verify($form, &$form_state,$serviceid, $factory_typeid,$applicationid,$referenceid) { 

	global $base_root,$base_path,$user;
	
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');

	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$reference_no 		= encryption_decryption_fun('decrypt',$referenceid);
	$value_app ='';
	 
	$form = array();
	if (!empty($application_id)) {
        $get_fa_cafa           				= 	get_fa_cafa($application_id);

       	$application_status      			= 	$get_fa_cafa['application_status'];
		$factory_plan_identification_number	= 	$get_fa_cafa['plan_approve_identification_number'];
		$factory_referance_number			= 	$get_fa_cafa['reference_number'];	
		$applicant_users					= 	$get_fa_cafa['created_by'];	
    }
	
	$user_id ='';
	$user_id = $user->uid;

	$query_check_applicant = db_select('fa_cafa_remarks','remarks');
	$query_check_applicant->fields('remarks', array());
	$query_check_applicant->condition('remarks.app_id', $application_id, '=');
	$query_check_applicant->condition('remarks.app_reference_no', $reference_no, '=');
	$query_check_applicant->orderBy('remarks.id','DESC');
	$query_check_applicant->range(0, 1);
	$result = $query_check_applicant->execute();
	$content = $result->fetchAssoc();
	
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
	$form['application_id_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt', $application_id),
	);
	$form['applicant_id_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt', $applicant_users),
	);
	
	ctools_include('ajax');
	ctools_include('modal');
	ctools_modal_add_js();	 
	$tt=$base_root.$base_path.'notesheets/'.$application_id.'/'.$reference_no.'/nojs'; 	
	$link_t=ctools_modal_text_button(t('View Notesheet'), $tt ,t('View Notesheet')) ;

	$cc=$base_root.$base_path.'conditions/'.$application_id.'/'.$reference_no.'/nojs'; 	
	$link_c=ctools_modal_text_button(t('View Condition'), $cc ,t('View Condition')) ;

	$title = ($service_id=='4') ? 'Application for Approval of Plan' : 'Application for Extension of Existing Plan';
	
	$form['header'] = array(
		'#markup' 			=> t('<div class="cus-page-outer-view"><div class="content"><center class="verify-top-title-pad"><h3>'.$title.'</h3><p>All inputs are provided by applicant only</p><p>All inputs are to be verified by officials</p></center>'),
	);
	
	$form['application_verify']['link'] = array(
		'#markup' 			=> t('<h5 style="margin:0" class="pull-right"><i class="ace-icon fa fa-file-text-o bigger-130 text-blue" style="padding: 10px;"></i>'.$link_t.'<i class="ace-icon fa fa-file-text-o bigger-130 text-blue" style="padding:0 10px;"></i>'.$link_c.'</h5>'),
	);
	  
	$form['application_verify']['markup_appplication'] = array(
			'#type' 			=> 'markup',
			'#markup' 			=> get_verifing_data($application_id,$service_id,$factory_type_id,$reference_no),
			);
	
	$form['application_verify']['fieldname']	= array(
												'#title'				=> 'Field Name',
												'#type'					=> 'hidden',
												'#attributes'			=> array('id' => 'chief_verify'),
												'#default_value' 		=> !empty($content['verify_details']) ? $content['verify_details'] : '',
												);

	$form['application_doc_verify']['doc_fieldname']	= array(
												'#title'				=> 'Field Name',
												'#type'					=> 'hidden',
												'#attributes'			=> array('id' => 'chief_doc_verify'),
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

    // REMARKS/NOTESHEET
	if($get_fa_cafa['plan_approve_status']=='C')
	{
		$form['application_forward'] = array(
			'#type' 			=> 'fieldset',
			'#title' 			=> t('Action'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => FALSE // Added
		);
		
		$users_action= array(	
						'0'=>'Select',
						'1'=>'Back to Joint Chief',
						'2'=>'Approve & Foward to Inspector',
					);
		
		$form['application_forward']['forward_user'] 	= array(
				  '#prefix' 		=> '<div class="row"><div class="col-md-4 col-xs-12"><label class="select label-block">Necessary action to be taken:<span id=\'star\' class="form-required">*</span>',
				  '#suffix' 		=> '</label></div>',
				  '#type' 			=> 'select',
				  '#options' 		=> $users_action,
				  '#default_value' 	=> $value_app,
				  '#required' 		=> TRUE,
				  '#ajax' => array(
					'event' => 'change',
					'effect' => 'fade',
					'callback' => 'get_ajax_note',
					'progress' => array('type' => 'throbber','message' => t('loading')))
				);
		$form['application_forward']['application_remark'] = array(
			'#prefix' => '<div id="reverse_id">',
			'#suffix' => '</div>',
		);
		$form['application_forward']['application_note'] = array(
			'#prefix' => '<div id="notesheet_id">',
			'#suffix' => '</div>',
		);
		$form['application_forward']['conditions'] = array(
			'#prefix' => '<div id="condition_id">',
			'#suffix' => '</div>',
		);
	
		$action   = isset($form_state['values']['forward_user']) ? $form_state['values']['forward_user'] : $value_app;
		
		if($action == 1){
			$form['application_forward']['application_remark'] = array(
			'#prefix' => '<div id="reverse_id"><div class="col-md-8"><label class="input label-block">Back to Joint Chief: <span id=\'star\' class="form-required">*</span>',
			'#suffix' => '</label></div></div>',
			'#type' => 'text_format',
			'#required' => TRUE,
			//'#default_value'  => !empty($content['remarks']) ? $content['remarks'] : '',
			);	
		}
	
		if($action == 2){
			$form['application_forward']['application_note'] = array(
			'#prefix' => '<div id="notesheet_id"><div class="col-md-8"><label class="input label-block">Final Notesheet: <span id=\'star\' class="form-required">*</span>',
			'#suffix' => '</label></div></div>',
			'#type' => 'text_format',
			'#required' => TRUE,
			//'#default_value'  => !empty($content['remarks']) ? $content['remarks'] : '',
			);	
			
			
			// --------------- Add more text box starts  ------------------------------
	
			$form['application_forward']['conditions'] = array(
				'#type' => 'fieldset',
				'#title' => t('Enter Conditions <b style="font-size:15px;">'.$link_c.'</b>'),
				'#prefix' => '<div id="condition_id" class="col-lg-12 col-md-12 col-sm-12">',
				'#suffix' => '</div>',
			);
		
			if (empty($form_state['condition_no'])) {
				$form_state['condition_no'] = 1;
			}
		
			for ($i = 0; $i < $form_state['condition_no']; $i++) {
		
				$form['application_forward']['conditions']['condition_'.$i] = array(
					'#prefix' => '<div class="col-md-12"><label class="input label-block">',
					'#suffix' => '</label></div>',
					'#type' => 'textfield',
					'#title' => '',
					'#size' => 150,
					'#description' => t('Condition'),
					'#attributes' => array('multiple' => 'multiple'),
				);
			}
		
			$form['application_forward']['conditions']['add_conditions'] = array(
				'#prefix' => '<div class="col-md-12 col-xs-12">',
				'#suffix' => '</div>',
				'#attributes' => array('class' => array('btn btn-dark')),
				'#type' => 'submit',
				'#value' => t('Add more'),
				'#submit' => array('conditions_add_more_add_one'),
				'#ajax' => array(
					'callback' => 'conditions_add_more_callback',
					'wrapper' => 'condition_id',
				),
			 );	
		}
		
		// ---------------  Add more text box ends ---------------------------------
		
		$form['application_forward']['submit'] = array(
			'#prefix' => '<div class="col-md-12 col-xs-12">',
			'#suffix' => '</div>',
			'#attributes' => array('class' => array('btn btn-dark'), 'onclick' => 'if(!confirm("Are you sure to continue ?")){return false;}'),
			'#type' => 'submit',
			'#value' => 'Send'
		);
	}
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

// ---------------  AJAX CALLBACK FUNCTIONS FOR TEXT FIELD-----------------

function conditions_add_more_add_one($form, &$form_state) {
	
	if (!isset($form_state['condition_no'])) {
		$form_state['condition_no'] = 0;
		$form_state['condition_no']++;
	}

	$form_state['condition_no']++;
	$form_state['rebuild'] = TRUE;
}

function conditions_add_more_callback($form, $form_state) {
	return $form['application_forward']['conditions'];
}
	
// ---------------  AJAX CALLBACK  FUNCTIONS FOR TEXT FIELD-----------------
function get_verifing_data($application_id,$service_id,$factory_type_id,$reference_no){
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

			// CHECK STATUS AND BLOCK THE CHECKBOX ACCORDINGLY
			if($plan_approve_status != 'C')
			{ $disable = "disabled";} else { $disable = "";}

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
			$previous_factory_name = '<tr><td>Previous Factory Name</td><td>'.$veryfing_details[0]->factory_previous_name.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="factory_previous_name" class="chief_verify_check" '.$factory_previous_name_ck .'/><label for="factory_previous_name"></label></div></td></tr>';
		} else {$previous_factory_name = '';}

		$addrline = !empty($factory_address) ? '<br>'.$veryfing_details[0]->addrline : $veryfing_details[0]->addrline;
		$addrline_off = !empty($headoffice_address) ? '<br>'.$veryfing_details[0]->addrline_off : $veryfing_details[0]->addrline_off;
		$addrline_oprmntadr = !empty($permanent_address) ? '<br>'.$veryfing_details[0]->addrline_oprmntadr : $veryfing_details[0]->addrline_oprmntadr;
		$addrline_oprsntadr = !empty($present_address) ? '<br>'.$veryfing_details[0]->addrline_oprsntadr : $veryfing_details[0]->addrline_oprsntadr;
		$addrline_premises = !empty($owner_premises_address) ? '<br>'.$veryfing_details[0]->addrline_premises : $veryfing_details[0]->addrline_premises;
			
		$output .= '<table cellpadding="0" cellspacing="0" border="0" class="table no-margin custom-table-view-dashboard">';
		
		$output .= '<tr><th width="25%;">Parameter</th><th>Input</th><th width="11%;" class="center"><div class="checkbox"> <input type="checkbox" '.$disable.' id="selectall_chief" /><label for="selectall_chief">Verify </label></div></th></tr>
					<tr><td colspan="3"><b>FACTORY INFORMATION</b></td></tr>
					<tr><td>Factory Name</td><td>'.$veryfing_details[0]->factory_name.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="factory_name" class="chief_verify_check" '.$factory_name_ck .' /><label for="factory_name"></label></div></td></tr>'.$previous_factory_name;

		$output .= '<tr><td colspan="3"><b>LOCATION OF FACTORY</b></td></tr>
					<tr><td>Factory Zone</td><td>'.$veryfing_details[0]->zone_name.'<br><span style="color:green";>'.$veryfing_details[0]->zone_details.'</span></td><td rowspan="2" class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="factory_location" class="chief_verify_check" '.$zone_name_ck.'/><label for="factory_location"></label></div></td></tr>
					<tr><td>Factory Address</td><td colspan="2">'.$factory_address.''.$addrline.'</td></tr>';

		$output .= '<tr><td colspan="3"><b>ADDRESS OF THE REGISTERED / HEAD OFFICE </b><br><span class="text-red" style="font-size:10px;"> (N.B:- This address will be treated as communication address as per Section 7 of Factories Act, 1948)</span></td></tr>
					<tr><td>Registered / Head office Address</td><td>'.$headoffice_address.''.$addrline_off.'</td> <td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="factory_headoffice" class="chief_verify_check" '.$factory_headoffice_ck.'/><label for="factory_headoffice"></label></div></td></tr>
					<tr><td>Mobile</td><td colspan="2">'.$veryfing_details[0]->comm_mobile.'</td></tr>
					<tr><td>Telephone</td><td colspan="2">'.$veryfing_details[0]->comm_telephone.'</td></tr>
					<tr><td>Fax</td><td colspan="2">'.$veryfing_details[0]->comm_fax.'</td></tr>
					<tr><td>Email</td><td colspan="2">'.$veryfing_details[0]->comm_email.'</td></tr>';

		$output .= '<tr><td colspan="3"><b>PAN OF BUSINESS ESTABLISHMENT / FACTORY / COMPANY</b></td></tr>
					<tr><td>PAN</td><td>'.$veryfing_details[0]->factory_pan.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="factory_pan" class="chief_verify_check" '.$factory_pan_ck.'/><label for="factory_pan"></label></div></td></tr>';

		$output .= '<tr><td colspan="3"><b>DETAILS OF OCCUPIER</b></td></tr>
					<tr><td>Name</td><td>'.$veryfing_details[0]->occupier_name.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="occupier_name" class="chief_verify_check" '.$occupier_name_ck.'/><label for="occupier_name"></label></div></td></tr>
					<tr><td>Age</td><td>'.$veryfing_details[0]->occupier_age.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="occupier_age" class="chief_verify_check" '.$occupier_age_ck.'/><label for="occupier_age"></label></div></td></tr>
					<tr><td>Father\'s/Husband\'s name</td><td>'.$veryfing_details[0]->occupier_gurdian_name.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="occupier_gurdian_name" class="chief_verify_check" '.$occupier_gurdian_name_ck.'/><label for="occupier_gurdian_name"></label></div></td></tr>
					<tr><td>Telephone Number</td><td>'.$veryfing_details[0]->occupier_telephone.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="occupier_telephone" class="chief_verify_check" '.$occupier_telephone_ck.'/><label for="occupier_telephone"></label></div></td></tr>
					<tr><td>Fax No.</td><td>'.$veryfing_details[0]->occupier_fax_no.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="occupier_fax_no" class="chief_verify_check" '.$occupier_fax_no_ck.'/><label for="occupier_fax_no"></label></div></td></tr>
					<tr><td>Registered Mobile Number</td><td>'.$veryfing_details[0]->occupier_mobile.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="occupier_mobile" class="chief_verify_check" '.$occupier_mobile_ck.'/><label for="occupier_mobile"></label></div></td></tr>
					<tr><td>Email Id</td><td>'.$veryfing_details[0]->occupier_email_id.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="occupier_email_id" class="chief_verify_check" '.$occupier_email_id_ck.'/><label for="occupier_email_id"></label></div></td></tr>
					<tr><td>Occupier Type</td><td>'.$veryfing_details[0]->occupier_type.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="occupier_type" class="chief_verify_check" '.$occupier_type_ck.'/><label for="occupier_type"></label></div></td></tr>
					
					<tr><td>Nationality</td><td>'.$veryfing_details[0]->occupier_nationality.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="occupier_nationality" class="chief_verify_check" '.$occupier_nationality_ck.'/><label for="occupier_nationality"></label></div></td></tr>';
					
					if($veryfing_details[0]->occupier_nationality == 'Indian')
					{
						$output .= '<tr><td>Aadhaar No.</td><td colspan="2">'.$veryfing_details[0]->occupier_aadhaar.'</td></tr>';
					} else {
						$output .= '<tr><td>Passport No.</td><td colspan="2">'.$veryfing_details[0]->occupier_passport.'</td></tr>';
					}
					
		$output .= '<tr><td>Permanent Address</td><td colspan="2">'.$permanent_address.''.$addrline_oprmntadr.'</td></tr>
					
					<tr><td>Present Address</td><td>'.$present_address.''.$addrline_oprsntadr.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="occupier_present_address" class="chief_verify_check" '.$occupier_present_address_ck.'/><label for="occupier_present_address"></label></div></td></tr>';

		$output .= '<tr><td colspan="3"><b>DETAILS OF OWNER/LAND LORD/LESSOR OF THE PREMISES OCCUPIED AS A FACTORY</b></td></tr>
					<tr><td>Owner Name</td><td>'.$veryfing_details[0]->owner_name.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="owner_name" class="chief_verify_check" '.$owner_name_ck.'/><label for="owner_name"></label></div></td></tr>
					<tr><td>Owner Address</td><td>'.$owner_premises_address.''.$addrline_premises.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="owner_address" class="chief_verify_check" '.$owner_address_ck.'/><label for="owner_address"></label></div></td></tr>';

		$output .= '<tr><td colspan="3"><b>WORKER DETAILS</b></td></tr>
					<tr><td>No. of Male Worker</td><td>'.$worker_details[0]->worker_men.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="worker_men" class="chief_verify_check" '.$worker_men_ck.'/><label for="worker_men"></label></div></td></tr>
					<tr><td>No. of Female Worker</td><td>'.$worker_details[0]->worker_women.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="worker_women" class="chief_verify_check" '.$worker_women_ck.'/><label for="worker_women"></label></div></td></tr>			
					<tr><td>No. of Male Adolescents Worker <br><span class="text-red" style="font-size:10px;">(over 15 but under 18 years of age)</span></td><td>'.$worker_details[0]->adolescents_male.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="adolescents_male" class="chief_verify_check" '.$adolescents_male_ck.'/><label for="adolescents_male"></label></div></td></tr>
					<tr><td>No. of Female Adolescents Worker</td><td>'.$worker_details[0]->adolescents_female.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="adolescents_female" class="chief_verify_check" '.$adolescents_female_ck.'/><label for="adolescents_female"></label></div></td></tr>			
					<tr><td>No. of Male Children Worker <br><span class="text-red" style="font-size:10px;">(over 14 but under 15 years of age)</span></td><td>'.$worker_details[0]->children_male.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="children_male" class="chief_verify_check" '.$children_male_ck.'/><label for="children_male"></label></div></td></tr>
					<tr><td>No. of Female Children Worker</td><td>'.$worker_details[0]->children_female.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="children_female" class="chief_verify_check" '.$children_female_ck.'/><label for="children_female"></label></div></td></tr>';
				
	$documentList =  get_plan_document_lists($service_id,$factory_type_id);
	
	$output .= '<tr><td colspan="3"><b>DOCUMENT DETAILS</b></td></tr>
  					<tr>
						<td colspan="3"> 
							<table width="100%" cellpadding="0" cellspacing="0" border="0" class="table no-margin custom-table-view-dashboard">
								<tr>
									<th width="50%">Required Document</th>
									<th width="44%">Uploaded Document</th>
									<th class="center">Action</th>
								</tr>';
								$checked = get_verified_field($application_id, $reference_no, $plan_approve_status);
									$verify_details      = ($checked['doc_verify'])? $checked['doc_verify'] : ''; 
									$remark_field        = explode(',', trim($checked['doc_verify'],","));
																						
								for($i=0; $i< count($documentList); $i++) //{foreach($resultData as $val)
								{
									$doc_id = $documentList[$i]->id;
									$uploaded_documentList =  get_plan_uploaded_document_lists($service_id,$factory_type_id,$application_id,$doc_id);
													
									$uploaded_doc_name = $uploaded_documentList[0]->doc_name ? $uploaded_documentList[0]->doc_name : '--';
									$displayLink = l('<i class="ace-icon fa fa-file-pdf-o bigger-130 text-red"></i>',file_create_url($uploaded_documentList[0]->uri),array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_BLANK')));
									$uploaded_link = $uploaded_documentList[0]->uri ? $displayLink.' ' : '';
									
									if (in_array('document_details_'.$i, $remark_field)) { $verify_status ='checked="checked"';}
 									else { $verify_status ='';}
			
								$output.= '<tr>
										
									<td>'.$documentList[$i]->document_name.'</td>
									<td>'.$uploaded_link.' '.$uploaded_doc_name.'</td>
									<td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="document_details_'.$i.'" class="chief_doc_verify_check" '.$document_details_ck.' '.$verify_status.'/><label for="document_details_'.$i.'"></label></div></td>
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
									//  IF ALREADY VERIFIED
									    //$checked = get_verified_field($application_id, $reference_no, $plan_approve_status);
										//$verify_details      = ($checked['doc_verify'])? $checked['doc_verify'] : ''; 
										//$remark_field        = explode(',', trim($checked['doc_verify'],","));
										
									for($i=0; $i< count($other_documentList); $i++) //{foreach($resultData as $val)
									{
										$doc_id = $other_documentList[$i]->id;
										$uploaded_documentList =  get_plan_uploaded_document_lists($service_id,$factory_type_id,$application_id,$doc_id);
										$uploaded_doc_name = $uploaded_documentList[0]->doc_name ? $uploaded_documentList[0]->doc_name : '--';
										$displayLink = l('<i class="ace-icon fa fa-file-pdf-o bigger-130 text-red"></i>',file_create_url($uploaded_documentList[0]->uri),array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_BLANK')));
										$uploaded_link = $uploaded_documentList[0]->uri ? $displayLink.' ' : '';
										
										if (in_array('document_details_'.$i, $remark_field)) { $verify_status ='checked="checked"';}
										else { $verify_status ='';}
				
									$output.= '<tr>
											
										<td>'.$other_documentList[$i]->document_name.'</td>
										<td>'.$uploaded_link.' '.$uploaded_doc_name.'</td>
										<td><select id="document_details_'.$i.'" class="plansection_doc_verify_check" '.$document_details_ck.' '.$verify_status.'/>
										<option value="0">- Select -</option>
										<option value="uploaded">Document Uploaded</option>
										<option value="notuploaded">Document Not Uploaded</option>
										</select></td>
							</tr>';
				}
								$output.='</table>';*/
				
				$output.='</td>
						</tr>';
					
			 $output .= '</table>';		
		 return $output;
}

function chief_application_verify_submit($form, &$form_state){
	
	  global $user;
	  $uid = $user->uid;
	  $uname = $user->name;
	  $user_role = array_keys($user->roles);
	  $urole  = $user_role[1];
	  $current_application_status =   '';
	  $val   					= 	$form_state['values'];
	  
	  //echo "<pre>"; print_r($val); die;
	  
	  $service_id 				= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']); 
	  $factorytype_id 			= 	encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
	  $application_id 			= 	encryption_decryption_fun('decrypt',$val['application_id_hidden']);
	  $reference_no				=  	encryption_decryption_fun('decrypt',$val['referance_no_hidden']);
	  $applicant_id				=  	encryption_decryption_fun('decrypt',$val['applicant_id_hidden']);
	  
	  //----------------Remarks Table Insert -------------------
	   
			if($val['forward_user']=='0'){
				drupal_set_message('Please select an action','error');
			}
			else if(($val['forward_user']=='1') || ($val['forward_user']=='2'))
			{
				if($val['forward_user']=='1'){
					$current_application_status ='JCBk';
					$type='n';
					$details = $val['application_remark']['value'];
				}
				else if($val['forward_user']=='2'){
					$current_application_status ='App';
					$type ='n';
					$details = $val['application_note']['value'];
				}

						$cafa_remarks = array(
							'app_id'   			 => $application_id,
							'remark_by_uid' 	 => $uid,
							'remark_by_roleid' 	 => $urole,
							'remark_by_name' 	 => $uname,
							'sending_time' 		 => date('Y-m-d h:i:s'),
							'app_reference_no' 	 => $reference_no,
							'remarks' 	         => $details,
							'remark_type'		 => $type,
							'verify_details'	 => trim($val['fieldname'], ","),
							'doc_verify'	     => trim($val['doc_fieldname'], ","), 
							'plan_status' 		 => $current_application_status,
							);
							
						db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();

					//---------------- CAFA TABLE UPDATE -------------------
					$approval_status = 	array('plan_approve_status' => $current_application_status,'remark_by_user_id' => $uid,'remark_by_role_id' => $urole);
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
			
					$c = 0;
					while(!empty($val['condition_'.$c]))
					{
						$cafa_conditions =  array(
						'app_id'   			=> $application_id,
						'added_by_uid' 	    => $uid,
						'added_by_roleid'   => $urole,
						'added_by_name' 	=> $uname,
						'sending_time' 		=> date('Y-m-d h:i:s'),
						'app_reference_no' 	=> $reference_no,
						'conditions' 	    => $val['condition_'.$c],
						'status' 			=> 'active',
						);	
					
					db_insert('fa_cafa_conditions')->fields($cafa_conditions)->execute();
					
						$c++;
				}
				
				if($current_application_status=='JCBk'){
				drupal_set_message('Application has been successfully backed to Joint Chief');}
				elseif($current_application_status=='App'){
					{
						$lastapprovalno = plan_count();
						$last_approval_no = $lastapprovalno +1;
						$conditional_letter_no = 'WBF/OL/'.date('Y').'/'.$last_approval_no.'/C/P';
						
						$approval_number = 	array('factory_plan_approval_number' => $last_approval_no, 'plan_conditional_letter_no' => $conditional_letter_no);
						$queryapp 		 =	db_update('fa_cafa');
						$queryapp		 ->	fields($approval_number);
						$queryapp		 ->	condition('id',$application_id,'=');
						$queryapp		 ->	condition('service_id',$service_id,'=');
						$queryapp	     ->	condition('factory_typeid',$factorytype_id,'=');
						$queryapp		 ->	condition('reference_number',$reference_no,'=');
						$queryapp		 ->	execute();
					}
					drupal_set_message('Application has been approved by Chief and forwarded to Inspector.');
					}else{
						drupal_set_message('Application not send.','error');
						}
				//drupal_goto('chief-plan-list/');
				if($service_id == '4') { 
					drupal_goto('chief-plan-list/');
				} else {
					drupal_goto('chief-extension-list/');
				}
			}
}

 function plan_count(){
		$fetch_application = db_query("SELECT max(factory_plan_approval_number) as cnt from fa_cafa WHERE service_id = '4' AND date_part('year', modification_date) = ".date('Y'))->fetchObject()->cnt;
		return $fetch_application;
 }

?>	
