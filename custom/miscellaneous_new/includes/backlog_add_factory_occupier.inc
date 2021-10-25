<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function backlog_add_factory_occupier($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$referenceno) {	
	
 	global $base_root, $base_path, $user;
	$userid 				= $user->uid;
	 $application_id			= encryption_decryption_fun('decrypt', $applicationid);
	 $service_id 			= encryption_decryption_fun('decrypt', $serviceid);
	 $factory_type_id 		= encryption_decryption_fun('decrypt', $factory_typeid);
	 $link_number 			= encryption_decryption_fun('decrypt', $referenceno);
	
	
	
		
	if(empty($application_id)){
			drupal_set_message(('At first you must be filled up the general information of factory then go to second tab'),'warning');
			drupal_goto('applicant/backlog-factory-add/details-worker-renewal/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$referenceno) ;
		 }
	else{
			$get_fa_cafa 				= get_fa_cafa($application_id);
			//print_r($get_fa_cafa );die;
			$reference_no 				= $get_fa_cafa['reference_number'];
			$ownership_type			    = $get_fa_cafa['factory_owershiptype'];
			$is_year_calculation_tab    = $get_fa_cafa['is_year_calculation_tab'];
			$application_status			= $get_fa_cafa['application_status'];
			$created_by					= $get_fa_cafa['created_by'];
		 }
		 
		 
	$reg_applicant  		= get_details_applicant($created_by);
	//print_r($reg_applicant);die('checked');
	$ownership_type_app_reg = $reg_applicant['ownership_type'];
	$user_type 				= $reg_applicant['user_type'];
	$is_occupier			= $reg_applicant['is_occupier'];
	$occupier_type_reg		= $reg_applicant['occupier_type'];
	if(($user_type == 'owner' && $is_occupier == 'Y')|| $user_type == 'occupier'){
			$firest_name_occupier_reg 	= $reg_applicant['firstname'];
			$middle_name_occupier_reg 	= $reg_applicant['middlename'];
			$last_name_occupier_reg 	= $reg_applicant['lastname'];
			$pincode_occupier_reg 		= $reg_applicant['pincode'];
			$state_occupier_reg 		= $reg_applicant['state'];
			$district_occupier_reg 		= $reg_applicant['district'];
			$subdivision_occupier_reg 	= $reg_applicant['subdivision'];
			$areatype_occupier_reg 		= $reg_applicant['areatype'];
			$block_occupier_reg 		= $reg_applicant['block'];
			$panchayat_occupier_reg 	= $reg_applicant['panchayat'];
			$policestation_occupier_reg = $reg_applicant['policestation'];
			$postoffice_occupier_reg 	= $reg_applicant['postoffice'];
			$addrline_occupier_reg 		= $reg_applicant['addrline'];
			$country_occupier_reg		= $reg_applicant['country'];
			$mobile_occupier_reg		= $reg_applicant['mobile'];
			$email_occupier_reg			= $reg_applicant['email'];
			$gurdian_name_occupier_reg	= $reg_applicant['gurdian_name'];
			$passport_reg				= $reg_applicant['user_passport'];
			$occupier_aadhaar_reg		= $reg_applicant['user_aadhar'];
			$occupier_date_of_issue_reg	= !empty($reg_applicant['passport_date_of_issue'])?$reg_applicant['passport_date_of_issue']:NULL;
			$occupier_date_of_expiry_reg= !empty($reg_applicant['passport_date_of_expiry'])?$reg_applicant['passport_date_of_issue']:NULL;
			$street_name_reg			= $reg_applicant['street_name'];
			$house_no_reg				= $reg_applicant['house_no'];
			$police_station_reg			= $reg_applicant['police_station'];
			
		}
	if(($user_type == 'owner' && $is_occupier == 'N')|| $user_type == 'consultant'){
			$firest_name_occupier_reg 	= $reg_applicant['occupier_first_name'];
			$middle_name_occupier_reg 	= $reg_applicant['occupier_middle_name'];
			$last_name_occupier_reg 	= $reg_applicant['occupier_last_name'];
			$email_occupier_reg 		= $reg_applicant['occupier_email'];
			$mobile_occupier_reg 		= $reg_applicant['occupier_mobile'];
			
		}	 
	if(empty($is_year_calculation_tab)){
		  	drupal_set_message(('Please fill up the second tab than fill up the worker information'),'warning');			
			drupal_goto('applicant/backlog-factory-add/details-worker-renewal/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$referenceno) ;
	 }  
	
	$form            				= array();
	
	$form['serviceid_hidden']     	= array(
			'#type' 				=> 'hidden',
			'#default_value' 		=> $serviceid
	);
	$form['factorytypeid_hidden'] 	= array(
			'#type' 				=> 'hidden',
			'#default_value' 		=> $factory_typeid
	);
	$form['applicationid_hidden'] 	= array(
			'#type' 				=> 'hidden',
			'#default_value' 		=> $applicationid
	);
	$form['linknumber_hidden'] 		= array(
			'#type' 		 		=> 'hidden',
			'#default_value' 		=> $linknumber
	);
	$form['flagmapp_hidden'] 		= array(
			'#type' 				=> 'hidden',
			'#default_value' 		=> $flagmapp
	);
	$form['application_reference_no'] = array(
			'#type' 				=> 'hidden',
			'#default_value' 		=> encryption_decryption_fun('encrypt',$reference_no)
	);


/********** Details of Occupier - Start **********/
    $form['header'] 				= array(
		'#type'						=> 'markup',
		'#prefix'					=> '<div class="row"><h3>Details of Occupier of the Factories</h3><div class="box-body">',
 	);

	$form['details_occupier']                         = array(
        '#type' 					=> 'fieldset',
        '#title' 					=> t('H. Details of Occupier'),
        '#collapsible' 				=> TRUE, // Added
        '#collapsed' 				=> FALSE // Added
    );
	$form['details_occupier']['row_start'] 	= array(
		'#prefix' 	 				=> '<div class="row">',
	);

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
	    $form['details_occupier']['occupier_type'] = array(
		'#prefix' 					=> '<div id="occupier_type_id" class="col-md-4 col-xs-4">',
		'#suffix' 					=> '</div>',
		'#title' 					=> t('(i). Type'),
		'#type' 					=> 'textfield',
		'#value'					=> !empty($ownership_type_occupier)?$ownership_type_occupier:$occupier_type_reg,
		'#attributes' 				=> array('readonly' => 'readonly','class' => array('form-control')),
		); 
	  }
	  
	  $occupier_name_reg = $firest_name_occupier_reg.' '. $middle_name_occupier_reg.' '.$last_name_occupier_reg;
	  $get_all_data = get_all_occupier_data($application_id,$service_id,$factory_type_id,$reference_no);
	  //print_r($get_all_data);
	 
      foreach($get_all_data as $occupier){
		  $type_occupier 			= $occupier->type_occupier;
		  $occupier_nationality	    = $occupier->country_oprmntadr;
		  $occupier_name 			= $occupier->name_occupier;
		  $occupier_name_middle 	= $occupier->occupier_name_middle;
		  $occupier_name_last 		= $occupier->occupier_name_last;
		  $occupier_age 			= $occupier->age_occupier;
		  $occupier_gurdian_name 	= $occupier->father_husband_name_occupier;
		  $occupier_pincode 		= $occupier->pincodeoprmntadr;
		  $occupier_state	 		= $occupier->state_oprmntadr;
		  $occupier_district		= $occupier->district_oprmntadr;
		  $occupier_sub_division	= $occupier->subdivision_oprmntadr;
		  $occupier_area_type				= $occupier->areatype_oprmntadr;
		  $occupier_block_mun_cor_sez_not	= $occupier->block_oprmntadr;
		  $occupier_grm_ward_sector_not	= $occupier->panchayat_oprmntadr;
		  $occupier_police_station		= $occupier->policestation_oprmntadr;
		  $occupier_post_office			= $occupier->postoffice_oprmntadr;
		  $occupier_adress_line1		= $occupier->addrline_oprmntadr;
		  $occupier_telephone			= $occupier->occupier_telephone;
		  $occupier_mobile				= $occupier->occupier_mobile;
		  $occupier_email_id			= $occupier->occupier_email_id;
		  $occupier_fax_no 				= $occupier->occupier_fax_no; 
		  $occupier_present_country		= $occupier->country_oprsntadr;
		  $pincode_present				= $occupier->pincodeoprsntadr;
		  $state_present				= $occupier->state_oprsntadr;
		  $district_present				= $occupier->district_oprsntadr;
		  $subdivision_present			= $occupier->subdivision_oprsntadr;
		  $areatype_present				= $occupier->areatype_oprsntadr;
		  $block_present				= $occupier->block_oprsntadr;
		  $panchayat_present 			= $occupier->panchayat_oprsntadr;
		  $post_office_present			= $occupier->postoffice_oprsntadr;
		  $police_station_present		= $occupier->policestation_oprsntadr;
		  
		  $occupier_nationality_oprsntadr = $occupier->country_oprsntadr;
		  
		  
		  $occupier_aadhaar				= $occupier->aadhaar_oprmntadr;
		  $occupier_passport			= $occupier->passport_oprmntadr;
		  $date_of_issue_oprmntadr		= $occupier->passport_date_of_issue_oprsntadr;
		  $date_of_expiry_oprmntadr		= $occupier->passport_date_of_expiry_oprsntadr;
		  
		  $street_name_oprsntadr 		= $occupier->street_name_oprsntadr;
		  $house_no_oprsntadr 			= $occupier->house_no_oprsntadr;
		  $police_station_oprsntadr 	= $occupier->police_station_oprsntadr;
		  
		  $street_name_oprmntadr 		= $occupier->street_name_oprmntadr;
		  $house_no_oprmntadr 			= $occupier->house_no_oprmntadr;
		  $police_station_oprmntadr 	= $occupier->police_station_oprmntadr;
		}

	 	$form['details_occupier']['occupier_name_first']      = array(
		'#prefix' 					=> '<div class="col-md-4 col-xs-4">',
		'#suffix' 					=> '</div>',
		'#title' 					=> t('(ii). First Name'),
		'#type' 					=> 'textfield',
		'#default_value' 			=> !empty($occupier_name) ? $occupier_name :$firest_name_occupier_reg,
		'#attributes' 				=> array('class' => array('form-control')),
		'#required' 				=> TRUE
		);
		$form['details_occupier']['occupier_name_middle']      = array(
		'#prefix' 					=> '<div class="col-md-4 col-xs-4">',
		'#suffix' 					=> '</div>',
		'#title' 					=> t('Middle Name'),
		'#type' 					=> 'textfield',
		'#default_value' 			=> !empty($occupier_name_middle) ? $occupier_name_middle :$middle_name_occupier_reg,
		'#attributes' 				=> array('class' => array('form-control')),
		
		);
		$form['details_occupier']['occupier_name_last']      = array(
		'#prefix' 					=> '<div class="col-md-4 col-xs-4">',
		'#suffix' 					=> '</div>',
		'#title' 					=> t('Last Name'),
		'#type' 					=> 'textfield',
		'#default_value' 			=> !empty($occupier_name_last) ? $occupier_name_last :$last_name_occupier_reg,
		'#attributes' 				=> array('class' => array('form-control')),
		'#required' 				=> TRUE
		);
		
		$form['details_occupier']['occupier_age']    = array(
		'#prefix'		 			=> '<div class="col-md-4 col-xs-4">',
		'#suffix' 					=> '</div>',
		'#title' 					=> t('(iii). Age'),
		'#type' 					=> 'textfield',
		'#attributes' 				=> array('class' => array('form-control')),
		'#default_value' 			=> !empty($occupier_age) ? $occupier_age :'',
		'#required' 				=> TRUE
		);
        $form['details_occupier']['occupier_gurdian_name']  = array(
		'#prefix'		 			=> '<div class="col-md-4 col-xs-4">',
		'#suffix' 					=> '</div>',
		'#title' 					=> t('(iv). Father\'s/Husband\'s name'),
		'#type' 					=> 'textfield',
		'#attributes' 				=> array('class' => array('form-control')),
		'#default_value' 			=> !empty($occupier_gurdian_name) ? $occupier_gurdian_name :$gurdian_name_occupier_reg,
		'#required' 				=> TRUE
		);
        $form['details_occupier']['occupier_telephone']  = array(
		'#prefix' 					=> '<div class="col-md-4 col-xs-4">',
		'#suffix' 					=> '</div>',
		'#title' 					=> t('(v). Telephone Number'),
		'#type' 					=> 'textfield',
		'#default_value' 			=> !empty($occupier_telephone) ? $occupier_telephone :$mobile_occupier_reg,
		'#attributes' 				=> array('class' => array('form-control')),
		'#required' 				=> TRUE
		);
        $form['details_occupier']['occupier_mobile']    = array(
		'#prefix' 					=> '<div class="col-md-4 col-xs-4">',
		'#suffix' 					=> '</div>',
		'#title' 					=> t('(vi). Mobile Number'),
		'#type' 					=> 'textfield',
		'#attributes' 				=> array('class' => array('form-control')),
		'#default_value' 			=> !empty($occupier_mobile) ? $occupier_mobile :$mobile_occupier_reg,
		'#required' 				=> TRUE
		);
        $form['details_occupier']['occupier_email_id']  = array(
		'#prefix' 					=> '<div class="col-md-4 col-xs-4">',
		'#suffix' 					=> '</div>',
		'#title' 					=> t('(vii). Email Id'),
		'#type' 					=> 'textfield',	
		'#attributes' 				=> array('class' => array('form-control')),
		'#default_value' 			=> !empty($occupier_email_id) ? $occupier_email_id :$email_occupier_reg,
		'#required' 				=> TRUE
		);
		$form['details_occupier']['occupier_fax_no']    = array(
		'#prefix' 					=> '<div class="col-md-4 col-xs-4">',
		'#suffix' 					=> '</div>',
		'#title' 					=> t('(viii). Fax No.'),
		'#type' 					=> 'textfield',
		'#attributes' 				=> array('class' => array('form-control')),
		'#default_value' 			=> !empty($occupier_fax_no) ? $occupier_fax_no :'',
		);
		
		$form['paddress_occupier']       = array(
		'#type' 					=> 'fieldset',
		'#title' 					=> t('I. Permanent Address'),
		'#collapsible' 				=> TRUE, // Added
		'#collapsed' 				=> FALSE // Added
		);
		 $form['paddress_occupier']['occupier_country'] = array(
		'#prefix' 					=> '<div class="row"><div class="col-md-4 col-xs-4">',
		'#suffix' 					=> '</div>',
		'#title' 					=> t('(i). Country'),
		'#options' 					=> get_country_with_ph(),
		'#type' 					=> 'select',
		'#attributes' 				=> array('class' => array('form-control')),
		'#default_value'    		=> !empty($occupier_nationality) ? $occupier_nationality :$country_occupier_reg,
		'#required' 				=> TRUE,
		'#ajax' 					=> array(
											'event' 		=> 'change',
											'effect' 		=> 'fade',
											'callback' 		=> 'get_ajax_nationality',
											'progress' 		=> array(
																	'type' 		=> 'throbber',
																	'message' 	=> t('loading')
																		)
								)
    	);
		
		$form['paddress_occupier']['occupier_passport']	= array(
        '#prefix'		=> '<div id="ld_show_passport">',
        '#suffix' 		=> '</div>'
    	);
		$form['paddress_occupier']['occupier_passport_issue_date'] = array(
		'#prefix' 		=> '<div id="ld_show_passport_issue_date">',
		'#suffix'		=> '</div>',
		);
		$form['paddress_occupier']['occupier_passport_exp_date'] = array(
		'#prefix' 		=> '<div id="ld_show_passport_exp_date">',
		'#suffix'		=> '</div>',
		);
		$form['paddress_occupier']['occupier_outstation_street_name'] = array(
		'#prefix' 		=> '<div id="ld_occupier_outstation_street_name">',
		'#suffix'		=> '</div>',
		);
		$form['paddress_occupier']['occupier_outstation_house_no'] = array(
		'#prefix' 		=> '<div id="ld_occupier_outstation_house_no">',
		'#suffix'		=> '</div>',
		);
		$form['paddress_occupier']['occupier_outstation_police_station'] = array(
		'#prefix' 		=> '<div id="ld_occupier_outstation_police_station">',
		'#suffix'		=> '</div>',
		);
		
		
		$form['paddress_occupier']['occupier_aadhaar']	= array(
        '#prefix'		=> '<div id="ld_show_aadhaar">',
        '#suffix' 		=> '</div>'
    	);
		 $form['paddress_occupier']['pincodeoprmntadr']	= array(
        '#prefix' 		=> '<div id="pincodeoprmntadr_id">',
        '#suffix' 		=> '</div>'
    	);
		$form['paddress_occupier']['state_oprmntadr']       = array(
        '#prefix' 		=> '<div id="oprmntadr_edit_emp_state_replace">',
        '#suffix' 		=> '</div>'
    	);
		$form['paddress_occupier']['district_oprmntadr'] = array(
		'#prefix' 		=> '<div id="oprmntadr_edit_emp_district_replace">',
		'#suffix' 		=> '</div>',
		);
		$form['paddress_occupier']['subdivision_oprmntadr'] = array(
		'#prefix' 		=> '<div id="oprmntadr_empsubdv_replace">',
		'#suffix' 		=> '</div>',
		);
		$form['paddress_occupier']['areatype_oprmntadr'] = array(
		'#prefix' 		=> '<div id="oprmntadr_emp_areatype_replace">',
		'#suffix' 		=> '</div>',
		);
		$form['paddress_occupier']['block_oprmntadr'] = array(
		'#prefix' 		=> '<div id="oprmntadr_empareatype_name_replace">',
		'#suffix' 		=> '</div>',
		);
		$form['paddress_occupier']['panchayat_oprmntadr'] = array(
	 	'#prefix' 		=> '<div id="oprmntadr_emp_vill_ward_replace">',
		'#suffix' 		=> '</div>',
		);
		$form['paddress_occupier']['policestation_oprmntadr'] = array(
		'#prefix' 		=> '<div id="oprmntadr_empps_replace">',
		'#suffix' 		=> '</div>',
		);
		$form['paddress_occupier']['postoffice_oprmntadr'] = array(
		'#prefix' 		=> '<div id="oprmntadr_post_office_div">',
		'#suffix' 		=> '</div>',
		);
		$form['paddress_occupier']['addrline_oprmntadr'] = array(
		'#prefix' 					=> '<div id="addrline_oprmntadr_div">',
		'#suffix' 					=> '</div>',
		);
		
		$nationality_value   = isset($form_state['values']['occupier_country']) ? $form_state['values']['occupier_country'] : (!empty($occupier_nationality)?$occupier_nationality:$country_occupier_reg);
	if($nationality_value == 99){
		$form['paddress_occupier']['occupier_aadhaar']  = array(
			'#prefix' 					=> '<div id="ld_show_aadhaar" class="col-md-4 col-xs-4">',
			'#suffix' 					=> '</div>',
			'#title'					=> t('(ii).Aadhaar Number'),
			'#type' 					=> 'textfield',
			'#attributes' 				=> array('class' => array('form-control adhaar-card'),'placeholder' => 'eg.2222-2222-2222'),
			'#default_value' 			=> !empty($occupier_aadhaar) ? $occupier_aadhaar :$occupier_aadhaar_reg,
		);
			
		$form['paddress_occupier']['pincodeoprmntadr']  = array(
       			 '#prefix' 					=> '<div id="pincodeoprmntadr_id" class="col-md-4 col-xs-4">',
        		'#suffix' 					=> '</div>',
				'#attributes' 				=> array('class' => array('form-control')),
				'#autocomplete_path' 		=> 'pinautocomplete',
				'#maxlength' 				=> 6,
				'#title' 					=> t('(iii).Pincode'),
				'#default_value'  			=> !empty($occupier_pincode) ? $occupier_pincode :$pincode_occupier_reg,
				'#required' 				=> TRUE,
				'#type' 					=> 'textfield',
				'#ajax' 					=> array(
												'effect' 	=> 'fade',
												'callback' 	=> 'get_ajax_nationality',
												'progress' 	=> array(
																	'type' 		=> 'throbber',
																	'message' 	=> t('loading')
																)
									)
			);
		$value_pincode_oprmntadr = isset($form_state['values']['pincodeoprmntadr']) ? $form_state['values']['pincodeoprmntadr'] : (!empty($occupier_pincode)?$occupier_pincode:$pincode_occupier_reg);
		if (!empty($value_pincode_oprmntadr)) {
		  	$query_oprmntadr = db_select('fa_all_india_pin_code', 'p')->fields('p', array('districtname','statename','pincode','district_code','state_code','po_name'))->condition('p.pincode', trim($value_pincode_oprmntadr), '=');
		  	$result_oprmntadr = $query_oprmntadr->execute();
			if ($result_oprmntadr->rowcount() > 0) {
					$final_oprmntadr       = $result_oprmntadr->fetchAssoc();
					$pincode_v_oprmntadr   = $value_pincode_oprmntadr;
					$state_v_oprmntadr     = $final_oprmntadr['state_code'];
					$district_v_oprmntadr  = $final_oprmntadr['district_code'];
					$post_office_oprmntadr = $final_oprmntadr['po_name'];
			}
		
		}
		$occupier_state = !empty($occupier_state)?$occupier_state:$state_occupier_reg;
		if (!empty($state_v_oprmntadr)) {
					$form['paddress_occupier']['state_oprmntadr'] = array(
					'#prefix' 					=> '<div id="oprmntadr_edit_emp_state_replace" class="col-md-4 col-xs-4">',
					'#suffix' 					=> '</div>',
					'#title' 					=> t('(iv). State'),
					'#type' 					=> 'select',
					'#attributes' 				=> array('class' => array('form-control')),
					'#disabled' 				=> TRUE,
					'#options' 					=> get_all_state($state_v_oprmntadr),
					'#required' 				=> TRUE,
					'#default_value' 			=> !empty($state_v_oprmntadr) ? $state_v_oprmntadr : $occupier_state,
			
					'#ajax' 					=> array(
												'event' 	=> 'change',
												'effect' 	=> 'fade',
												'callback' 	=> 'get_ajax_nationality',
												'progress' 	=> array(
																		'type' 		=> 'throbber',
																		'message' 	=> t('loading')
																)
											)
					);
        }else {
			 $form['paddress_occupier']['state_oprmntadr'] = array(
			 	'#prefix' 					=> '<div id="oprmntadr_edit_emp_state_replace" class="col-md-4 col-xs-4">',
				'#suffix' 					=> '</div>',
				'#title' 					=> t('(iv). State'),
				'#type' 					=> 'select',
				'#attributes' 				=> array('class' => array('form-control')),
				'#disabled' 				=> TRUE,
				'#options' 					=> array('' => t('Select State')),
				'#required' 				=> TRUE,
				
				
				);
        }
		
		$value_state_oprmntadr = isset($form_state['values']['state_oprmntadr']) ? $form_state['values']['state_oprmntadr'] : $occupier_state;
		$occupier_district = !empty($occupier_district) ? $occupier_district : $district_occupier_reg;
		 if (!empty($state_v_oprmntadr)) {
				$form['paddress_occupier']['district_oprmntadr'] = array(
						'#prefix' 					=> '<div id="oprmntadr_edit_emp_district_replace" class="col-md-4 col-xs-4">',
						'#suffix' 					=> '</div>',
						'#title' 					=> '(v). District',
						'#type' 					=> 'select',
						'#disabled' 				=> TRUE,
						'#attributes' 				=> array('class' => array('form-control')),
						'#options' 					=> get_district_by_id($state_v_oprmntadr),
						'#value' 					=> !empty($district_v_oprmntadr)?$district_v_oprmntadr:$occupier_district,
						'#required' 				=> TRUE,
						'#ajax' 					=> array(
															'event' 		=> 'change',
															'effect' 		=> 'fade',
															'callback' 		=> 'get_ajax_nationality',
															'progress' 		=> array(
																					'type' 		=> 'throbber',
																					'message' 	=> t('loading')
																				)
												 )
			);
            
            
    }else {
			$form['paddress_occupier']['district_oprmntadr'] = array(
				'#prefix' 					=> '<div id="oprmntadr_edit_emp_district_replace" class="col-md-4 col-xs-4">',
				'#suffix' 					=> '</div>',
				'#title' 					=> '(v). District',
				'#type' 					=> 'select',
				'#disabled' 				=> TRUE,
				'#attributes' 				=> array('class' => array('form-control')),
				'#options' 					=> array('' => t('Select District')),
				'#required' 				=> TRUE,
			); 
        }
		
		$value_district_oprmntadr = isset($form_state['values']['district_oprmntadr']) ? $form_state['values']['district_oprmntadr'] : $occupier_district;
		if (!empty($district_v_oprmntadr) && !empty($state_v_oprmntadr)) {
			$form['paddress_occupier']['subdivision_oprmntadr'] = array(
				'#prefix' 					=> '<div id="oprmntadr_empsubdv_replace" class="col-md-4 col-xs-4">',
				'#suffix' 					=> '</div>',
				'#title' 					=> '(vi). Sub Division',
				'#type' 					=> 'select',
				'#attributes' 				=> array('class' => array('form-control')),
				'#options' 					=> common_custom_user_subdivisionlist_list_new($district_v_oprmntadr),
				'#default_value' 			=>!empty($occupier_sub_division)?$occupier_sub_division:$subdivision_occupier_reg,
				'#required' 				=> TRUE,
				'#ajax' 					=> array(
													'event' 		=> 'change',
													'effect' 		=> 'fade',
													'callback' 		=> 'get_ajax_nationality',
													'progress' 		=> array(
																			'type' 		=> 'throbber',
																			'message' 	=> t('loading')
																		)
										 )
		);
          
    }else {
				$form['paddress_occupier']['subdivision_oprmntadr'] = array(
					'#prefix' 					=> '<div id="oprmntadr_empsubdv_replace" class="col-md-4 col-xs-4">',
					'#suffix' 					=> '</div>',
					'#title' 					=> '(vi). Sub Division',
					'#type' 					=> 'select',
					'#attributes' 				=> array('class' => array('form-control')),
					'#options' 					=> array('' => t('Select Sub-Division')),
					'#required' 				=> TRUE,
					
					
				);
            
            
        }
		
		$value_subdivision_oprmntadr = isset($form_state['values']['subdivision_oprmntadr']) ? $form_state['values']['subdivision_oprmntadr'] : (!empty($occupier_sub_division)?$occupier_sub_division:$subdivision_occupier_reg);
		if (!empty($value_district_oprmntadr) && !empty($value_state_oprmntadr) && !empty($value_subdivision_oprmntadr)) {
				$form['paddress_occupier']['areatype_oprmntadr'] = array(
					'#prefix' 					=> '<div id="oprmntadr_emp_areatype_replace" class="col-md-4 col-xs-4">',
					'#suffix' 					=> '</div>',
					'#title' 					=> '(vii). Area Type',
					'#type' 					=> 'select',
					'#attributes' 				=> array('class' => array('form-control')),
					'#options' 					=> common_custom_user_areatype_list_new($value_district_oprmntadr,$value_subdivision_oprmntadr),
					'#default_value' 			=> !empty($occupier_area_type)?$occupier_area_type:$areatype_occupier_reg,
					'#required' 				=> TRUE,
					'#ajax' 					=> array(
														'event' 	=> 'change',
														'effect' 	=> 'fade',
														'callback' 	=> 'get_ajax_nationality',
														'progress' 	=> array(
																				'type' 		=> 'throbber',
																				'message' 	=> t('loading')
																			)
											 )
				);
           
    }else {
		$form['paddress_occupier']['areatype_oprmntadr'] = array(
				'#prefix' 					=> '<div id="oprmntadr_emp_areatype_replace" class="col-md-4 col-xs-4">',
				'#suffix' 					=> '</div>',
				'#title' 					=> '(vii). Area Type',
				'#type' 					=> 'select',
				'#attributes' 				=> array('class' => array('form-control')),
				'#options' 					=> array('' => t('Select area type')),
				'#required' 				=> TRUE,
				
					
			);
           
        }
		
		$value_areatype_oprmntadr = isset($form_state['values']['areatype_oprmntadr']) ? $form_state['values']['areatype_oprmntadr'] : (!empty($occupier_area_type)?$occupier_area_type:$areatype_occupier_reg);
		if (!empty($value_district_oprmntadr) && !empty($value_state_oprmntadr) && $value_subdivision_oprmntadr != "" && !empty($value_areatype_oprmntadr)) {
            
            if ($value_areatype_oprmntadr == 'B') {
                $areatype_name_oprmntadr = 'Block';
            } elseif ($value_areatype_oprmntadr == 'M') {
                $areatype_name_oprmntadr = 'Municipality';
            } elseif ($value_areatype_oprmntadr == 'C') {
                $areatype_name_oprmntadr = 'Corporation';
            } elseif ($value_areatype_oprmntadr == 'S') {
                $areatype_name_oprmntadr = 'SEZ';
            } elseif ($value_areatype_oprmntadr == 'N') {
                $areatype_name_oprmntadr = 'Notified Area';
            }
            
	$form['paddress_occupier']['block_oprmntadr'] = array(
			'#prefix' 					=> '<div id="oprmntadr_empareatype_name_replace" class="col-md-4 col-xs-4">',
			'#suffix' 					=> '</div>',
			'#title' 					=> '(viii). '.$areatype_name_oprmntadr,
			'#type' 					=> 'select',
			'#attributes' 				=> array('class' => array('form-control')),
			'#options' 					=>  common_custom_user_block_list_new($value_subdivision_oprmntadr, $value_areatype_oprmntadr),
			'#default_value' 			=> !empty($occupier_block_mun_cor_sez_not)?$occupier_block_mun_cor_sez_not:$block_occupier_reg,
			'#required' 				=> TRUE,
			
			'#ajax' 					=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',
										'callback' 		=> 'get_ajax_nationality',
										'progress' 		=> array(
																'type' 		=> 'throbber',
																'message' 	=> t('loading')
															)
									 )
		);
                      
    } else {
		$form['paddress_occupier']['block_oprmntadr'] = array(
			'#prefix' 					=> '<div id="oprmntadr_empareatype_name_replace" class="col-md-4 col-xs-4">',
			'#suffix' 					=> '</div>',
			'#title' 					=> '(viii). Block / Municipality / Corporation / Notified Area / SEZ',
			'#type' 					=> 'select',
			'#attributes' 				=> array('class' => array('form-control')),
			'#options' 					=> array('' => t('select Block / Municipality / Corporation / Notified Area / SEZ')),
			'#required' 				=> TRUE,
			);
     	}
		
		$value_block_oprmntadr = isset($form_state['values']['block_oprmntadr']) ? $form_state['values']['block_oprmntadr'] : (!empty($occupier_block_mun_cor_sez_not)?$occupier_block_mun_cor_sez_not:$block_occupier_reg);

   		if (!empty($value_district_oprmntadr) && !empty($value_subdivision_oprmntadr) && !empty($value_areatype_oprmntadr) && !empty($value_block_oprmntadr) && !empty($value_state_oprmntadr)) {
            
            if ($value_areatype_oprmntadr == 'B') {
                $area_name_oprmntadr = 'Gram Panchayat';
                $area_code_oprmntadr = 'V';
            } elseif ($value_areatype_oprmntadr == 'M') {
                $area_name_oprmntadr = 'Ward';
                $area_code_oprmntadr = 'W';
            } elseif ($value_areatype_oprmntadr == 'C') {
                $area_name_oprmntadr = 'Ward';
                $area_code_oprmntadr = 'C';
            } elseif ($value_areatype_oprmntadr == 'S') {
                $area_name_oprmntadr = 'Sector';
                $area_code_oprmntadr = 'S';
            } elseif ($value_areatype_oprmntadr == 'N') {
                $area_name_oprmntadr = 'Notified Area';
                $area_code_oprmntadr = 'N';
            }
	$form['paddress_occupier']['panchayat_oprmntadr'] = array(
				'#prefix' 					=> '<div id="oprmntadr_emp_vill_ward_replace" class="col-md-4 col-xs-4">',
				'#suffix' 					=> '</div>',
				'#title' 					=> '(ix). '.$area_name_oprmntadr,
				'#type' 					=> 'select',
				'#attributes' 				=> array('class' => array('form-control')),
				'#options' 					=>  get_full_villward($value_block_oprmntadr, $area_code_oprmntadr),
				'#default_value' 			=> !empty($occupier_grm_ward_sector_not)?$occupier_grm_ward_sector_not:$panchayat_occupier_reg,
				'#required' 				=> TRUE,
				'#ajax' 					=> array(
													'event' 		=> 'change',
													'effect' 		=> 'fade',
													'callback' 		=> 'get_ajax_nationality',
													'progress' 		=> array(
																			'type' 		=> 'throbber',
																			'message' 	=> t('loading')
																		)
										 )
			);
    }else {
	 $form['paddress_occupier']['panchayat_oprmntadr'] = array(
	 			'#prefix' 					=> '<div id="oprmntadr_emp_vill_ward_replace" class="col-md-4 col-xs-4">',
				'#suffix' 					=> '</div>',
				'#title' 					=> '(ix). Select Gram Panchayat / Ward / Sector / Notified Area',
				'#type' 					=> 'select',
				'#attributes' 				=> array('class' => array('form-control')),
				'#options' 					=>  array('' => t('Select Gram Panchayat / Ward / Sector / Notified Area')),
				'#required' 				=> TRUE,
				
					
			);
           
        }
		
		$value_panchayat_oprmntadr1 = isset($form_state['values']['panchayat_oprmntadr']) ? $form_state['values']['panchayat_oprmntadr'] : (!empty($occupier_grm_ward_sector_not)?$occupier_grm_ward_sector_not:$panchayat_occupier_reg);
		if (!empty($value_district_oprmntadr)) {
			$form['paddress_occupier']['policestation_oprmntadr'] = array(
					'#prefix' 					=> '<div id="oprmntadr_empps_replace" class="col-md-4 col-xs-4">',
					'#suffix' 					=> '</div>',
					'#title' 					=> '(x). Police Station',
					'#type' 					=> 'select',
					'#attributes' 				=> array('class' => array('form-control')),
					'#options' 					=> common_custom_user_ps_list_new($value_district_oprmntadr),
					'#default_value' 			=> !empty($occupier_police_station)?$occupier_police_station:$policestation_occupier_reg,
					'#required' 				=> TRUE,
					
					
			);
    }else {
			$form['paddress_occupier']['policestation_oprmntadr'] = array(
				'#prefix' 					=> '<div id="oprmntadr_empps_replace" class="col-md-4 col-xs-4">',
				'#suffix' 					=> '</div>',
				'#title' 					=> '(x). Police Station',
				'#type' 					=> 'select',
				'#attributes' 				=> array('class' => array('form-control')),
				'#options' 					=> array('' => t('Select Police Station')),
				'#required' 				=> TRUE,
				
						
				);
    }
		if (!empty($value_pincode_oprmntadr)) {
			$form['paddress_occupier']['postoffice_oprmntadr'] = array(
				'#prefix' 					=> '<div id="oprmntadr_post_office_div" class="col-md-4 col-xs-4">',
				'#suffix' 					=> '</div>',
				'#title' 					=> '(x). Post Office',
				'#type' 					=> 'select',
				'#attributes' 				=> array('class' => array('form-control')),
				'#options' 					=> common_custom_post_office_list_new($value_pincode_oprmntadr),
				'#required' 				=> TRUE,
				'#default_value' 			=> !empty($occupier_post_office)?$occupier_post_office:$postoffice_occupier_reg,
			);
     }else {
				$form['paddress_occupier']['postoffice_oprmntadr'] = array(
					'#prefix' 					=> '<div id="oprmntadr_post_office_div" class="col-md-4 col-xs-4">',
					'#suffix' 					=> '</div>',
					'#title' 					=> '(x). Post Office',
					'#type' 					=> 'select',
					'#attributes' 				=> array('class' => array('form-control')),
					'#options' 					=> array('' => t('Select Post Office')),
					'#required' 				=> TRUE,
					
							
					);
           
     }
	 	$form['paddress_occupier']['addrline_oprmntadr'] = array(
		'#prefix' 					=> '<div id="addrline_oprmntadr_div" class="col-md-12 col-xs-4">',
		'#suffix' 					=> '</div>',
		'#title'					=> t('(xii). Address'),
		'#rows' 					=> 3,
		'#type' 					=> 'textarea',
		'#attributes' 				=> array('class' => array('form-control')),
		'#attributes' 				=> array('class' => array(''),'placeholder' => 'Address Line'),
		'#default_value' 			=> !empty($occupier_adress_line1)?$occupier_adress_line1:$addrline_occupier_reg
		);
		
	
		
	}
	if($nationality_value != 99){
		$form['paddress_occupier']['occupier_passport'] = array(
			'#prefix' 					=> '<div id="ld_show_passport" class="col-md-4 col-xs-12">',
			'#suffix'					=> '</label></div>',
			'#title' 					=> t('(ii). Passport Number'),
			'#type' 					=> 'textfield',
			'#attributes' 				=> array('class'=>array('form-control')),
			'#default_value'  			=> !empty($occupier_passport) ? $occupier_passport :$passport_reg,
			'#required' 				=> TRUE
		);
		$form['paddress_occupier']['occupier_passport_issue_date'] = array(
			'#prefix' 					=> '<div id="ld_show_passport_issue_date" class="col-md-4 col-xs-12">',
			'#suffix'					=> '</div>',
			'#title' 					=> t('(iii). Passport issue Date'),
			'#type' 					=> 'textfield',
			'#default_value'  			=> !empty($date_of_issue_oprmntadr) ? $date_of_issue_oprmntadr :$occupier_date_of_issue_reg,
			'#required' 				=> TRUE,
			'#attributes' 				=> array( 'class' => array('form-control datepicker_cls'),'readonly' => 'readonly')
		);
		$form['paddress_occupier']['occupier_passport_exp_date'] = array(
			'#prefix' 					=> '<div id="ld_show_passport_exp_date" class="col-md-4 col-xs-12">',
			'#suffix'					=> '</div>',
			'#title' 					=> t('(iv). Passport Expiry date'),
			'#type' 					=> 'textfield',
			'#default_value'  			=> !empty($date_of_expiry_oprmntadr) ? $date_of_expiry_oprmntadr :$occupier_date_of_expiry_reg,
			'#required' 				=> TRUE,
			'#attributes' 				=> array( 'class' => array('form-control datepicker_cls'),'readonly' => 'readonly')
		);
		$form['paddress_occupier']['occupier_outstation_street_name'] = array(
			'#prefix' 					=> '<div id="ld_occupier_outstation_street_name" class="col-md-4 col-xs-12">',
			'#suffix'					=> '</div>',
			'#title' 					=> t('(v). Enter Your Street Name / Road Name'),
			'#type' 					=> 'textfield',
			'#default_value'  			=> !empty($street_name_oprmntadr) ? $street_name_oprmntadr :$street_name_reg,
			'#required' 				=> TRUE,
			'#attributes' 				=> array( 'class' => array('form-control'))
		);
		$form['paddress_occupier']['occupier_outstation_house_no'] = array(
			'#prefix' 					=> '<div id="ld_occupier_outstation_house_no" class="col-md-4 col-xs-12">',
			'#suffix'					=> '</div>',
			'#title' 					=> t('(vi). Enter Your House No'),
			'#type' 					=> 'textfield',
			'#default_value'  			=> !empty($house_no_oprmntadr) ? $house_no_oprmntadr :$house_no_reg,
			'#required' 				=> TRUE,
			'#attributes' 				=> array( 'class' => array('form-control'))
		);
		$form['paddress_occupier']['occupier_outstation_police_station'] = array(
			'#prefix' 					=> '<div id="ld_occupier_outstation_police_station" class="col-md-4 col-xs-12">',
			'#suffix'					=> '</div>',
			'#title' 					=> t('(vii). Enter Local Police Station'),
			'#type' 					=> 'textfield',
			'#default_value'  			=> !empty($police_station_oprmntadr) ? $police_station_oprmntadr :$police_station_reg,
			'#required' 				=> TRUE,
			'#attributes' 				=> array( 'class' => array('form-control'))
		);
	}

   //////////////////////////////////Present Address////////////////////////////////////
	
	$form['factory_part_oprsntadr'] = array(
		'#type' 					=> 'fieldset',
		'#title' 					=> t('J. Present Address'),
		'#collapsible' 				=> TRUE, // Added
		'#collapsed' 				=> FALSE // Added
    );
	$form['factory_part_oprsntadr']['occupier_country_present'] = array(
		'#prefix' 					=> '<div class="row"><div class="col-md-4 col-xs-4">',
		'#suffix' 					=> '</div>',
		'#title' 					=> t('(i). Country'),
		'#options' 					=> get_country_with_ph(),
		'#type' 					=> 'select',
		'#attributes' 				=> array('class' => array('form-control')),
		'#default_value'    		=> !empty($occupier_nationality_oprsntadr) ? $occupier_nationality_oprsntadr :$country_occupier_reg,
		'#required' 				=> TRUE,
		'#ajax' 					=> array(
											'event' 		=> 'change',
											'effect' 		=> 'fade',
											'callback' 		=> 'get_ajax_load_present',
											'progress' 		=> array(
																	'type' 		=> 'throbber',
																	'message' 	=> t('loading')
																	)
								)
    );
	$form['factory_part_oprsntadr']['occupier_passport_present'] = array(
		'#prefix' 	=> '<div id="ld_occupier_passport_present">',
		'#suffix'	=> '</div>',
	);
	$form['factory_part_oprsntadr']['occupier_passport_issue_date_present'] = array(
		'#prefix' 	=> '<div id="ld_show_passport_issue_date_present">',
		'#suffix'	=> '</div>',
	);
	$form['factory_part_oprsntadr']['occupier_passport_exp_date_present'] = array(
		'#prefix' 	=> '<div id="ld_show_passport_exp_date_present">',
		'#suffix'	=> '</div>',
	);
	$form['factory_part_oprsntadr']['occupier_outstation_street_name_present'] = array(
		'#prefix' 	=> '<div id="ld_occupier_outstation_street_name_present">',
		'#suffix'	=> '</div>',
	);
	$form['factory_part_oprsntadr']['occupier_outstation_house_no_present'] = array(
		'#prefix' 	=> '<div id="ld_occupier_outstation_house_no_present">',
		'#suffix'	=> '</div>',
	);
	$form['factory_part_oprsntadr']['occupier_outstation_police_station_present'] = array(
		'#prefix' 	=> '<div id="ld_occupier_outstation_police_station_present">',
		'#suffix'	=> '</div>',
	);
	
	
	$form['factory_part_oprsntadr']['occupier_aadhaar_present']   = array(
		'#prefix' 	=> '<div id="ld_show_aadhaar_present">',
		'#suffix' 	=> '</div>',
	);
	$form['factory_part_oprsntadr']['pincode_present']  = array(
       	'#prefix' 	=> '<div id="pincode_present_id">',
        '#suffix' 	=> '</div>',
	);
	$form['factory_part_oprsntadr']['state_present'] = array(
		'#prefix' 	=> '<div id="state_present_id">',
		'#suffix' 	=> '</div>',
	);
	$form['factory_part_oprsntadr']['district_present'] = array(
		'#prefix' 	=> '<div id="district_present_id">',
		'#suffix' 	=> '</div>',
	);
	$form['factory_part_oprsntadr']['subdivision_present'] = array(
		'#prefix' 	=> '<div id="subdivision_present_id">',
		'#suffix'	=> '</div>',
	);
	$form['factory_part_oprsntadr']['areatype_present'] = array(
		'#prefix' 	=> '<div id="areatype_present_id">',
		'#suffix' 	=> '</div>',
	);
	$form['factory_part_oprsntadr']['block_present'] = array(
		'#prefix' 	=> '<div id="block_present_id">',
		'#suffix' 	=> '</div>',
	);
	$form['factory_part_oprsntadr']['panchayat_present'] = array(
	 	'#prefix' 	=> '<div id="panchayat_present_id">',
		'#suffix' 	=> '</div>',
	);
	$form['factory_part_oprsntadr']['policestation_present'] = array(
		'#prefix' 	=> '<div id="policestation_present_id">',
		'#suffix' 	=> '</div>',
	);
	$form['factory_part_oprsntadr']['postoffice_present'] = array(
		'#prefix' 	=> '<div id="postoffice_present_id">',
		'#suffix' 	=> '</div>',
	);
	$form['factory_part_oprsntadr']['addrline_present'] = array(
		'#prefix' 	=> '<div id="addrline_present_id">',
		'#suffix' 	=> '</div>',
	);

	
	$country_value   = isset($form_state['values']['occupier_country_present']) ? $form_state['values']['occupier_country_present'] : (!empty($occupier_nationality)?$occupier_nationality:$country_occupier_reg);
	
	if($country_value == 99){
		$form['factory_part_oprsntadr']['occupier_aadhaar_present']   = array(
			'#prefix' 					=> '<div id="ld_show_aadhaar_present" class="col-md-4 col-xs-4">',
			'#suffix' 					=> '</div>',
			'#title'					=> t('(ii). Aadhaar Number'),
			'#type' 					=> 'textfield',
			'#attributes' 				=> array('class' => array('form-control adhaar-card'),'placeholder' => 'eg.2222-2222-2222'),
			'#default_value' 			=> !empty($occupier_aadhaar) ? $occupier_aadhaar :$occupier_aadhaar_reg,
		);
		$form['factory_part_oprsntadr']['pincode_present']  = array(
       			'#prefix' 					=> '<div id="pincode_present_id" class="col-md-4 col-xs-4">',
        		'#suffix' 					=> '</div>',
				'#attributes' 				=> array('class' => array('form-control')),
				'#autocomplete_path' 		=> 'pinautocomplete',
				'#maxlength' 				=> 6,
				'#title' 					=> t('(iii).Pincode'),
				'#default_value'  			=> !empty($pincode_present) ? $pincode_present :$pincode_occupier_reg,
				'#required' 				=> TRUE,
				'#type' 					=> 'textfield',
				'#ajax' 					=> array(
												'effect' 	=> 'fade',
												'callback' 	=> 'get_ajax_load_present',
												'progress' 	=> array(
																	'type' 		=> 'throbber',
																	'message' 	=> t('loading')
																)
									)
			);
		$value_pincode_present = isset($form_state['values']['pincode_present']) ? $form_state['values']['pincode_present'] : (!empty($pincode_present) ? $pincode_present :$pincode_occupier_reg);
		 if (!empty($value_pincode_present)) {
		 		 $query_present = db_select('fa_all_india_pin_code', 'p')->fields('p', array('districtname','statename','pincode','district_code','state_code','po_name'))->condition('p.pincode', trim($value_pincode_present), '=');
		  		$result_prsent = $query_present->execute();
				if ($result_prsent->rowcount() > 0) {
					$final_present       = $result_prsent->fetchAssoc();
					$pincode_v_present   = $value_pincode_present;
					$state_v_present     = $final_present['state_code'];
					$district_v_present  = $final_present['district_code'];
					//$post_office_present = $final_present['po_name'];
			}
		
		}
		if (!empty($state_v_present)) {
					$form['factory_part_oprsntadr']['state_present'] = array(
					'#prefix' 					=> '<div id="state_present_id" class="col-md-4 col-xs-4">',
					'#suffix' 					=> '</div>',
					'#title' 					=> t('(iv). State'),
					'#type' 					=> 'select',
					'#attributes' 				=> array('class' => array('form-control'),),
					'#disabled' 				=> TRUE,
					'#options' 					=> get_all_state($state_v_present),
					'#required' 				=> TRUE,
					'#default_value' 			=> !empty($state_v_present) ? $state_v_present : (!empty($state_present)?$state_present:$state_occupier_reg),
					'#ajax' 					=> array(
																'event' 	=> 'change',
																'effect' 	=> 'fade',
																'callback' 	=> 'get_ajax_load_present',
																'progress' 	=> array(
																						'type' 		=> 'throbber',
																						'message' 	=> t('loading')
																					)
															)
					);
        }else {
					
					 $form['factory_part_oprsntadr']['state_present'] = array(
						'#prefix' 					=> '<div id="state_present_id" class="col-md-4 col-xs-4">',
						'#suffix' 					=> '</div>',
						'#title' 					=> t('(iv). State'),
						'#type' 					=> 'select',
						'#attributes' 				=> array('class' => array('form-control')),
						'#disabled' 				=> TRUE,
						'#options' 					=> array('' => t('Select State')),
						'#required' 				=> TRUE,
					);
        }
		
		$value_state_present = isset($form_state['values']['state_present']) ? $form_state['values']['state_present'] : (!empty($state_present)?$state_present:$state_occupier_reg);
		$occupier_district = !empty($district_present) ? $district_present : $district_occupier_reg;
		if (!empty($state_v_present)) {
				$form['factory_part_oprsntadr']['district_present'] = array(
						'#prefix' 					=> '<div id="district_present_id" class="col-md-4 col-xs-4">',
						'#suffix' 					=> '</div>',
						'#title' 					=> '(v). District',
						'#type' 					=> 'select',
						'#disabled' 				=> TRUE,
						'#attributes' 				=> array('class' => array('form-control')),
						'#options' 					=> get_district_by_id($state_v_present),
						'#value' 					=> !empty($district_v_present)?$district_v_present:$occupier_district,
						'#required' 				=> TRUE,
						'#ajax' 					=> array(
															'event' 		=> 'change',
															'effect' 		=> 'fade',
															'callback' 		=> 'get_ajax_load_present',
															'progress' 		=> array(
																					'type' 		=> 'throbber',
																					'message' 	=> t('loading')
																				)
												 )
			);
            
            
    }else {
			$form['factory_part_oprsntadr']['district_present'] = array(
				'#prefix' 					=> '<div id="district_present_id" class="col-md-4 col-xs-4">',
				'#suffix' 					=> '</div>',
				'#title' 					=> '(v). District',
				'#type' 					=> 'select',
				'#disabled' 				=> TRUE,
				'#attributes' 				=> array('class' => array('form-control')),
				'#options' 					=> array('' => t('Select District')),
				'#required' 				=> TRUE,
				
				
			);
            
        }
		
		$value_district_present = isset($form_state['values']['district_present']) ? $form_state['values']['district_present'] : $occupier_district;
		if (!empty($district_v_present) && !empty($state_v_present)) {
			$form['factory_part_oprsntadr']['subdivision_present'] = array(
				'#prefix' 					=> '<div id="subdivision_present_id" class="col-md-4 col-xs-4">',
				'#suffix' 					=> '</div>',
				'#title' 					=> '(vi). Sub Division',
				'#type' 					=> 'select',
				'#attributes' 				=> array('class' => array('form-control')),
				'#options' 					=> common_custom_user_subdivisionlist_list_new($district_v_present),
				'#default_value' 			=>!empty($subdivision_present)?$subdivision_present:$subdivision_occupier_reg,
				'#required' 				=> TRUE,
				'#ajax' 					=> array(
													'event' 		=> 'change',
													'effect' 		=> 'fade',
													'callback' 		=> 'get_ajax_load_present',
													'progress' 		=> array(
																			'type' 		=> 'throbber',
																			'message' 	=> t('loading')
																		)
										 )
		);
          
    }
		else {
				$form['factory_part_oprsntadr']['subdivision_present'] = array(
					'#prefix' 					=> '<div id="subdivision_present_id" class="col-md-4 col-xs-4">',
					'#suffix' 					=> '</div>',
					'#title' 					=> '(vi). Sub Division',
					'#type' 					=> 'select',
					'#attributes' 				=> array('class' => array('form-control')),
					'#options' 					=> array('' => t('Select Sub-Division')),
					'#required' 				=> TRUE,	
				);
            
            
        }
		
		$value_subdivision_present = isset($form_state['values']['subdivision_present']) ? $form_state['values']['subdivision_present'] :(!empty($subdivision_present)?$subdivision_present:$subdivision_occupier_reg);
		if (!empty($value_district_present) && !empty($value_state_present) && !empty($value_subdivision_present)) {
				$form['factory_part_oprsntadr']['areatype_present'] = array(
					'#prefix' 					=> '<div id="areatype_present_id" class="col-md-4 col-xs-4">',
					'#suffix' 					=> '</div>',
					'#title' 					=> '(vii). Area Type',
					'#type' 					=> 'select',
					'#attributes' 				=> array('class' => array('form-control')),
					'#options' 					=> common_custom_user_areatype_list_new($value_district_present,$value_subdivision_present),
					'#default_value' 			=> !empty($areatype_present)?$areatype_present:$areatype_occupier_reg,
					'#required' 				=> TRUE,
					'#ajax' 					=> array(
														'event' 	=> 'change',
														'effect' 	=> 'fade',
														'callback' 	=> 'get_ajax_load_present',
														'progress' 	=> array(
																				'type' 		=> 'throbber',
																				'message' 	=> t('loading')
																			)
											 )
				);
           
    }else {
		$form['factory_part_oprsntadr']['areatype_present'] = array(
				'#prefix' 					=> '<div id="areatype_present_id" class="col-md-4 col-xs-4">',
				'#suffix' 					=> '</div>',
				'#title' 					=> '(vii). Area Type',
				'#type' 					=> 'select',
				'#attributes' 				=> array('class' => array('form-control')),
				'#options' 					=> array('' => t('Select area type')),
				'#required' 				=> TRUE,	
			);
           
        }
		
		$value_areatype_present = isset($form_state['values']['areatype_present']) ? $form_state['values']['areatype_present'] : (!empty($areatype_present)?$areatype_present:$areatype_occupier_reg);
		if (!empty($value_district_present) && !empty($value_state_present) && $value_subdivision_present != "" && !empty($value_areatype_present)) {
            
            if ($value_areatype_present == 'B') {
                $areatype_name_present = 'Block';
            } elseif ($value_areatype_present == 'M') {
                $areatype_name_present = 'Municipality';
            } elseif ($value_areatype_present == 'C') {
                $areatype_name_present = 'Corporation';
            } elseif ($value_areatype_present == 'S') {
                $areatype_name_present = 'SEZ';
            } elseif ($value_areatype_present == 'N') {
                $areatype_name_present = 'Notified Area';
            }
            
	$form['factory_part_oprsntadr']['block_present'] = array(
			'#prefix' 					=> '<div id="block_present_id" class="col-md-4 col-xs-4">',
			'#suffix' 					=> '</div>',
			'#title' 					=> '(viii). '.$areatype_name_present,
			'#type' 					=> 'select',
			'#attributes' 				=> array('class' => array('form-control')),
			'#options' 					=>  common_custom_user_block_list_new($value_subdivision_present, $value_areatype_present),
			'#default_value' 			=> !empty($block_present)?$block_present:$block_occupier_reg,
			'#required' 				=> TRUE,
			
			'#ajax' 					=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',
										'callback' 		=> 'get_ajax_load_present',
										'progress' 		=> array(
																'type' 		=> 'throbber',
																'message' 	=> t('loading')
															)
									 )
		);
                      
    } else {
		$form['factory_part_oprsntadr']['block_present'] = array(
			'#prefix' 					=> '<div id="block_present_id" class="col-md-4 col-xs-4">',
			'#suffix' 					=> '</div>',
			'#title' 					=> '(viii). Block / Municipality / Corporation / Notified Area / SEZ',
			'#type' 					=> 'select',
			'#attributes' 				=> array('class' => array('form-control')),
			'#options' 					=> array('' => t('select Block / Municipality / Corporation / Notified Area / SEZ')),
			'#required' 				=> TRUE,		
			);
     	}
		
		 $value_block_presnt = isset($form_state['values']['block_present']) ? $form_state['values']['block_present'] : (!empty($block_present)?$block_present:$block_occupier_reg);
		  if (!empty($value_district_present) && !empty($value_subdivision_present) && !empty($value_areatype_present) && !empty($value_block_presnt) && !empty($value_state_present)) { 
            if ($value_areatype_present == 'B') {
                $area_name_presnt = 'Gram Panchayat';
                $area_code_presnt = 'V';
            } elseif ($value_areatype_present == 'M') {
                $area_name_presnt = 'Ward';
                $area_code_presnt = 'W';
            } elseif ($value_areatype_present == 'C') {
                $area_name_presnt = 'Ward';
                $area_code_presnt = 'C';
            } elseif ($value_areatype_present == 'S') {
                $area_name_presnt = 'Sector';
                $area_code_presnt = 'S';
            } elseif ($value_areatype_present == 'N') {
                $area_name_presnt = 'Notified Area';
                $area_code_presnt = 'N';
            }
	$form['factory_part_oprsntadr']['panchayat_present'] = array(
				'#prefix' 					=> '<div id="panchayat_present_id" class="col-md-4 col-xs-4">',
				'#suffix' 					=> '</div>',
				'#title' 					=> '(ix). '.$area_name_presnt,
				'#type' 					=> 'select',
				'#attributes' 				=> array('class' => array('form-control')),
				'#options' 					=>  get_full_villward($value_block_presnt, $area_code_presnt),
				'#default_value' 			=> !empty($panchayat_present)?$panchayat_present:$panchayat_occupier_reg,
				'#required' 				=> TRUE,
				
				'#ajax' 					=> array(
													'event' 		=> 'change',
													'effect' 		=> 'fade',
													'callback' 		=> 'get_ajax_load_present',
													'progress' 		=> array(
																			'type' 		=> 'throbber',
																			'message' 	=> t('loading')
																		)
										 )
			);
			//echo $value_block_oprmntadr.'----'.$area_code_oprmntadr.'</br>';
			//echo $value_block_presnt.'----'.$area_code_presnt.'</br>';
			
			//$r = get_full_villward($value_block_presnt, $area_code_presnt);
			//print_r($r);die;
    }else {
	$form['factory_part_oprsntadr']['panchayat_present'] = array(
	 		'#prefix' 					=> '<div id="panchayat_present_id" class="col-md-4 col-xs-4">',
			'#suffix' 					=> '</div>',
			'#title' 					=> '(ix). Select Gram Panchayat / Ward / Sector / Notified Area',
			'#type' 					=> 'select',
			'#attributes' 				=> array('class' => array('form-control')),
			'#options' 					=>  array('' => t('Select Gram Panchayat / Ward / Sector / Notified Area')),
			'#required' 				=> TRUE,	
		);
	}	
	//echo $occupier_police_station;die;
		if(!empty($value_district_present)) {
			$form['factory_part_oprsntadr']['policestation_present'] = array(
					'#prefix' 					=> '<div id="policestation_present_id" class="col-md-4 col-xs-4">',
					'#suffix' 					=> '</div>',
					'#title' 					=> '(x). Police Station',
					'#type' 					=> 'select',
					'#attributes' 				=> array('class' => array('form-control')),
					'#options' 					=> common_custom_user_ps_list_new($value_district_present),
					'#default_value' 			=> !empty($police_station_present)?$police_station_present:$policestation_occupier_reg,
					'#required' 				=> TRUE,
			);
			
    	}else {
			$form['factory_part_oprsntadr']['policestation_present'] = array(
				'#prefix' 					=> '<div id="policestation_present_id" class="col-md-4 col-xs-4">',
				'#suffix' 					=> '</div>',
				'#title' 					=> '(x). Police Station',
				'#type' 					=> 'select',
				'#attributes' 				=> array('class' => array('form-control')),
				'#options' 					=> array('' => t('Select Police Station')),
				'#required' 				=> TRUE,
			);
    	}
		if (!empty($value_pincode_present)) {
			$form['factory_part_oprsntadr']['postoffice_present'] = array(
				'#prefix' 					=> '<div id="postoffice_present_id" class="col-md-4 col-xs-4">',
				'#suffix' 					=> '</div>',
				'#title' 					=> '(x). Post Office',
				'#type' 					=> 'select',
				'#attributes' 				=> array('class' => array('form-control')),
				'#options' 					=> common_custom_post_office_list_new($value_pincode_present),
				'#required' 				=> TRUE,
				'#default_value' 			=> !empty($post_office_present)?$post_office_present:$postoffice_occupier_reg,
			);
     }else {
			$form['factory_part_present']['postoffice_present'] = array(
				'#prefix' 					=> '<div id="postoffice_present_id" class="col-md-4 col-xs-4">',
				'#suffix' 					=> '</div>',
				'#title' 					=> '(x). Post Office',
				'#type' 					=> 'select',
				'#attributes' 				=> array('class' => array('form-control')),
				'#options' 					=> array('' => t('Select Post Office')),
				'#required' 				=> TRUE,		
			);
           
     }
	 
	  	$form['factory_part_oprsntadr']['addrline_present'] = array(
			'#prefix' 					=> '<div id="addrline_present_id" class="col-md-12 col-xs-4">',
			'#suffix' 					=> '</div>',
			'#title'					=> t('(xii). Address'),
			'#rows' 					=> 3,
			'#type' 					=> 'textarea',
			'#attributes' 				=> array('class' => array(''),'placeholder' => 'Address Line'),
			'#default_value' 			=> !empty($occupier_adress_line1)?$occupier_adress_line1:$addrline_occupier_reg
		);	
	}
	if($country_value != 99){
		$form['factory_part_oprsntadr']['occupier_passport_present'] = array(
			'#prefix' 					=> '<div id="ld_occupier_passport_present" class="col-md-4 col-xs-4">',
			'#suffix'					=> '</div>',
			'#title' 					=> t('(ii). Passport Number'),
			'#type' 					=> 'textfield',
			'#attributes' 				=> array('class'=>array('form-control')),
			'#default_value'  			=> !empty($occupier_passport) ? $occupier_passport :$passport_reg,
			'#required' 				=> TRUE
		);
		$form['factory_part_oprsntadr']['occupier_passport_issue_date_present'] = array(
			'#prefix' 					=> '<div id="ld_show_passport_issue_date_present" class="col-md-4 col-xs-4">',
			'#suffix'					=> '</div>',
			'#title' 					=> t('(iii). Passport issue Date '),
			'#type' 					=> 'textfield',
			'#attributes' 				=> array('class'=>array('form-control datepicker_cls'),'readonly'=>'readonly'),
			'#default_value'  			=> !empty($date_of_issue_oprmntadr) ? $date_of_issue_oprmntadr :$occupier_date_of_issue_reg,
			'#required' 				=> TRUE
		);
		$form['factory_part_oprsntadr']['occupier_passport_exp_date_present'] = array(
			'#prefix' 					=> '<div id="ld_show_passport_exp_date_present" class="col-md-4 col-xs-4">',
			'#suffix'					=> '</div>',
			'#title' 					=> t('(iv). Passport Expire Date '),
			'#type' 					=> 'textfield',
			'#attributes' 				=> array('class'=>array('form-control datepicker_cls'),'readonly'=>'readonly'),
			'#default_value'  			=> !empty($date_of_expiry_oprmntadr) ? $date_of_expiry_oprmntadr :$occupier_date_of_expiry_reg,
			'#required' 				=> TRUE
		);
		$form['factory_part_oprsntadr']['occupier_outstation_street_name_present'] = array(
			'#prefix' 					=> '<div id="ld_occupier_outstation_street_name_present" class="col-md-4 col-xs-4">',
			'#suffix'					=> '</div>',
			'#title' 					=> t('(v). Enter Your Street Name / Road Name'),
			'#type' 					=> 'textfield',
			'#attributes' 				=> array('class'=>array('form-control')),
			'#default_value'  			=> !empty($street_name_oprsntadr) ? $street_name_oprsntadr :$street_name_reg,
		);
		$form['factory_part_oprsntadr']['occupier_outstation_house_no_present'] = array(
			'#prefix' 					=> '<div id="ld_occupier_outstation_house_no_present" class="col-md-4 col-xs-4">',
			'#suffix'					=> '</div>',
			'#title' 					=> t('(vi). Enter Your House No'),
			'#type' 					=> 'textfield',
			'#attributes' 				=> array('class'=>array('form-control')),
			'#default_value'  			=> !empty($house_no_oprsntadr) ? $house_no_oprsntadr :$house_no_reg,
		);
		$form['factory_part_oprsntadr']['occupier_outstation_police_station_present'] = array(
			'#prefix' 					=> '<div id="ld_occupier_outstation_police_station_present" class="col-md-4 col-xs-4">',
			'#suffix'					=> '</div>',
			'#title' 					=> t('(vii). Enter Local Police Station '),
			'#type' 					=> 'textfield',
			'#attributes' 				=> array('class'=>array('form-control')),
			'#default_value'  			=> !empty($police_station_oprsntadr) ? $police_station_oprsntadr :$police_station_reg,
		);
	}
	/********** Occupier Present Address - End **********/    
   
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
		'#markup' => l('DRAFT COPY', 'regsection/preview-varse-occupier-information/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'Preview as PDF', 'target' => '_BLANK','class'=>array('btn btn-warning pull-right'))))
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

function get_ajax_nationality($form, &$form_state){ 

    $commands   = array(); 
	$commands[] = ajax_command_replace('#ld_show_aadhaar', drupal_render($form['paddress_occupier']['occupier_aadhaar']));
	
	$commands[] = ajax_command_replace('#ld_show_passport', drupal_render($form['paddress_occupier']['occupier_passport']));
	$commands[] = ajax_command_replace('#ld_show_passport_issue_date', drupal_render($form['paddress_occupier']['occupier_passport_issue_date']));
	$commands[] = ajax_command_replace('#ld_show_passport_exp_date', drupal_render($form['paddress_occupier']['occupier_passport_exp_date']));
	$commands[] = ajax_command_replace('#ld_occupier_outstation_street_name', drupal_render($form['paddress_occupier']['occupier_outstation_street_name']));
	$commands[] = ajax_command_replace('#ld_occupier_outstation_house_no', drupal_render($form['paddress_occupier']['occupier_outstation_house_no']));
	$commands[] = ajax_command_replace('#ld_occupier_outstation_police_station', drupal_render($form['paddress_occupier']['occupier_outstation_police_station']));

	
    $commands[] = ajax_command_replace('#pincodeoprmntadr_id', drupal_render($form['paddress_occupier']['pincodeoprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_edit_emp_state_replace', drupal_render($form['paddress_occupier']['state_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_edit_emp_district_replace', drupal_render($form['paddress_occupier']['district_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_empsubdv_replace', drupal_render($form['paddress_occupier']['subdivision_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_emp_areatype_replace', drupal_render($form['paddress_occupier']['areatype_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_empareatype_name_replace', drupal_render($form['paddress_occupier']['block_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_emp_vill_ward_replace', drupal_render($form['paddress_occupier']['panchayat_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_empps_replace', drupal_render($form['paddress_occupier']['policestation_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_post_office_div', drupal_render($form['paddress_occupier']['postoffice_oprmntadr']));
	$commands[] = ajax_command_replace('#addrline_oprmntadr_div', drupal_render($form['paddress_occupier']['addrline_oprmntadr']));
    
    return array('#type' => 'ajax','#commands' => $commands);
}
function get_ajax_load_present($form, $form_state){
	$commands = array();
	
	$commands[] = ajax_command_replace('#ld_show_aadhaar_present', drupal_render($form['factory_part_oprsntadr']['occupier_aadhaar_present']));
	
	$commands[] = ajax_command_replace('#ld_occupier_passport_present', drupal_render($form['factory_part_oprsntadr']['occupier_passport_present']));
	$commands[] = ajax_command_replace('#ld_show_passport_issue_date_present', drupal_render($form['factory_part_oprsntadr']['occupier_passport_issue_date_present']));
	$commands[] = ajax_command_replace('#ld_show_passport_exp_date_present', drupal_render($form['factory_part_oprsntadr']['occupier_passport_exp_date_present']));
	$commands[] = ajax_command_replace('#ld_occupier_outstation_street_name_present', drupal_render($form['factory_part_oprsntadr']['occupier_outstation_street_name_present']));
	$commands[] = ajax_command_replace('#ld_occupier_outstation_house_no_present', drupal_render($form['factory_part_oprsntadr']['occupier_outstation_house_no_present']));
	$commands[] = ajax_command_replace('#ld_occupier_outstation_police_station_present',drupal_render($form['factory_part_oprsntadr']['occupier_outstation_police_station_present']));
	
	
	$commands[] = ajax_command_replace('#pincode_present_id', drupal_render($form['factory_part_oprsntadr']['pincode_present']));
	$commands[] = ajax_command_replace('#state_present_id', drupal_render($form['factory_part_oprsntadr']['state_present']));
	$commands[] = ajax_command_replace('#district_present_id', drupal_render($form['factory_part_oprsntadr']['district_present']));
	$commands[] = ajax_command_replace('#subdivision_present_id', drupal_render($form['factory_part_oprsntadr']['subdivision_present']));
	$commands[] = ajax_command_replace('#areatype_present_id', drupal_render($form['factory_part_oprsntadr']['areatype_present']));
	$commands[] = ajax_command_replace('#block_present_id', drupal_render($form['factory_part_oprsntadr']['block_present']));
	$commands[] = ajax_command_replace('#panchayat_present_id', drupal_render($form['factory_part_oprsntadr']['panchayat_present']));
	$commands[] = ajax_command_replace('#policestation_present_id', drupal_render($form['factory_part_oprsntadr']['policestation_present']));
	$commands[] = ajax_command_replace('#postoffice_present_id', drupal_render($form['factory_part_oprsntadr']['postoffice_present']));
	$commands[] = ajax_command_replace('#addrline_present_id', drupal_render($form['factory_part_oprsntadr']['addrline_present']));
	return array('#type' => 'ajax', '#commands' => $commands);
}




function details_of_occupier_validate($form, &$form_state){
	
	$occupier_name = $form_state['values']['occupier_name_first'];
	if (!preg_match('/[A-Za-z]+$/', $occupier_name)) {  
    form_set_error('occupier_name_first', t('Occupier Name should be text only!!'));
  }	
  	$occupier_gurdian_name = $form_state['values']['occupier_gurdian_name'];
	if (!preg_match('/[A-Za-z]+$/', $occupier_gurdian_name)) {  
    form_set_error('occupier_gurdian_name', t('Occupier Gurdian Name should be text only!!'));
  }	
  
  $occupier_telephone = $form_state['values']['occupier_telephone'];
  if (!preg_match('/^[0-9]*$/', $occupier_telephone)) {
    form_set_error('occupier_telephone', t('Telephone should be numeric only!!'));
  }
  if ($form_state['values']['occupier_telephone']!="" && (strlen($form_state['values']['occupier_telephone'])<10 || strlen($form_state['values']['occupier_telephone'])>10)) {
	form_set_error('occupier_telephone', 'Telephone should be of 10 digit');    
  }

  $occupier_mobile = $form_state['values']['occupier_mobile'];
  if (!preg_match('/^[0-9]*$/', $occupier_mobile)) {
    form_set_error('occupier_mobile', t('Mobile should be numeric only!!'));
  }
 
  
  if ($form_state['values']['occupier_mobile']!="" && (strlen($form_state['values']['occupier_mobile'])<10 || strlen($form_state['values']['occupier_mobile'])>10)) {
	form_set_error('occupier_mobile', 'Mobile should be of 10 digit');    
  }

  /*$occupier_fax = $form_state['values']['occupier_fax_no'];
  if (!preg_match('/^[0-9]*$/', $occupier_fax)) {
    form_set_error('occupier_fax_no', t('Fax should be numeric only!!'));
  }*/
  
  $occupier_email = $form_state['values']['occupier_email_id'];
	if (!filter_var($occupier_email, FILTER_VALIDATE_EMAIL)) {
	form_set_error('occupier_email_id', t('Please enter a Valid Email Id!')); 
  }
  
 /* $occupier_aadhaar = $form_state['values']['occupier_aadhaar'];
  if (!preg_match('/^[0-9\s]*$/', $occupier_aadhaar)) {
    form_set_error('occupier_aadhaar', t('Aadhaar should be numeric only!!'));
  }*/
  
  if ($form_state['values']['occupier_aadhaar']!="" && (strlen($form_state['values']['occupier_aadhaar'])<14 || strlen($form_state['values']['occupier_aadhaar'])>14)) {
	form_set_error('occupier_aadhaar', 'Aadhaar should be of 12 digit');    
  }
  
 // $occupier_passport = $form_state['values']['occupier_passport'];
//  if (!preg_match('/[a-zA-Z]{2}[0-9]{7}/', $occupier_passport)) {
//    form_set_error('occupier_passport', t('Passport Number should be Valid!'));
//  }
  
   	  
}

function backlog_add_factory_occupier_submit($form, &$form_state){
	global $user;
    $userid = $user->uid;
	$user_role = array_keys($user->roles);
    $urole  = $user_role[1];
    $val    = $form_state['values'];
	$application_id = empty($val['applicationid_hidden'])?'':encryption_decryption_fun('decrypt', $val['applicationid_hidden']);
	$service_id = encryption_decryption_fun('decrypt', $val['serviceid_hidden']);
	$factorytype_id = encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']);
	$application_reference_no = encryption_decryption_fun('decrypt',$val['application_reference_no']);
	
	
	$flagmapp  = encryption_decryption_fun('decrypt', $val['flagmapp_hidden']); 
	if($flagmapp == 'backlogplanapproval_no'){
		$backlog_plan_approval_no =  encryption_decryption_fun('decrypt', $val['linknumber_hidden']);
		$is_backlog = 1;
	}
	if($flagmapp == 'backlog_registrationno'){
		$backlog_registration_no =  encryption_decryption_fun('decrypt', $val['linknumber_hidden']);
		$is_backlog = 1;
	}
	if($flagmapp == 'planapproval_no'){
		$factory_plan_approval_number =  encryption_decryption_fun('decrypt', $val['linknumber_hidden']);
		
	}
	if($flagmapp == 'registration_number'){
		$factory_reg_number =  encryption_decryption_fun('decrypt', $val['linknumber_hidden']);
		
	}
if($urole == 4){
		 $created_by 			= $userid;
		 $factor_add_inspector 	= NULL;
	}else{
		 $created_by = NULL;
		
	}

  	$get_exists = get_all_occupier_data($application_id,$service_id,$factorytype_id,$application_reference_no);
  
   	$occupier_details = array(
		'type_occupier'   					=> $val['occupier_type'], 
		'name_occupier'   					=> $val['occupier_name_first'], 
		'occupier_name_middle'   			=> $val['occupier_name_middle'], 
		'occupier_name_last'   				=> $val['occupier_name_last'], 
		'age_occupier' 						=> $val['occupier_age'],
		'father_husband_name_occupier' 		=> $val['occupier_gurdian_name'],
		'occupier_mobile' 		    		=> $val['occupier_mobile'],
		'occupier_email_id' 	    		=> $val['occupier_email_id'],
		'occupier_fax_no'        			=> $val['occupier_fax_no'],
		'occupier_telephone'     			=> $val['occupier_telephone'],
		
		
		
		'aadhaar_oprmntadr' 		   		=> $val['occupier_aadhaar'],
		'passport_oprmntadr' 	    		=> $val['occupier_passport'],
		'passport_date_of_issue_oprmntadr'	=> !empty ($val['occupier_passport_issue_date'])?$val['occupier_passport_issue_date']:NULL,
		'passport_date_of_expiry_oprmntadr'	=> !empty ($val['occupier_passport_exp_date'])?$val['occupier_passport_exp_date']:NULL,
		
		
		'country_oprmntadr'					=> $val['occupier_country'],
		'pincodeoprmntadr'					=> $val['pincodeoprmntadr'],
		'state_oprmntadr'					=> $val['state_oprmntadr'],
		'district_oprmntadr'				=> $val['district_oprmntadr'],
		'subdivision_oprmntadr'				=> $val['subdivision_oprmntadr'],
		'areatype_oprmntadr'				=> $val['areatype_oprmntadr'],
		'block_oprmntadr'					=> $val['block_oprmntadr'],
		'panchayat_oprmntadr'				=> $val['panchayat_oprmntadr'],
		'policestation_oprmntadr'			=> $val['policestation_oprmntadr'],
		'postoffice_oprmntadr'				=> $val['postoffice_oprmntadr'],
		'addrline_oprmntadr'				=> $val['addrline_oprmntadr'],
		
		
					
		'created_by'						=> $created_by,
		'application_occupier_id'			=> $application_id,
		'application_status'				=> 'In',
		'factory_type_id'					=> $factorytype_id,
		'occupier_service_id'				=> $service_id,
		'application_reference_no'			=> $application_reference_no,
		
		'country_oprsntadr'					=> $val['occupier_country_present'],
		'pincodeoprsntadr' 					=> $val['pincode_present'],
  		'state_oprsntadr'					=> $val['state_present'],
  		'district_oprsntadr'				=> $val['district_present'],
  		'subdivision_oprsntadr'				=> $val['subdivision_present'],
  		'areatype_oprsntadr'				=> $val['areatype_present'],
  		'block_oprsntadr'					=> $val['block_present'],
  		'panchayat_oprsntadr'				=> $val['panchayat_present'],
		'policestation_oprsntadr'			=> $val['policestation_present'],
		'postoffice_oprsntadr'				=> $val['postoffice_present'],
		
  		'addrline_oprsntadr'				=> $val['addrline_present'],
		'aadhaar_oprsntadr' 		   		=> $val['occupier_aadhaar_present'],

		'street_name_oprmntadr' 			=> $val['occupier_outstation_street_name_present'],
  		'house_no_oprmntadr'				=> $val['occupier_outstation_house_no_present'],
		'police_station_oprsntadr'			=> $val['occupier_outstation_police_station_present'],
		
		'street_name_oprmntadr' 			=> $val['occupier_outstation_street_name'],
		'house_no_oprmntadr' 				=> $val['occupier_outstation_house_no'],
		'police_station_oprmntadr' 			=> $val['occupier_outstation_police_station'],
		
		
	);

	if(empty($get_exists)){
		$id = db_insert('fa_occupier_details')->fields($occupier_details)->execute();
		 $caf_update = 	array('application_status' => 'In','modification_date'=> date('Y-m-d'),'is_occupier_tab'=>1);
	  	 $queryabc 		=	db_update('fa_cafa');
	 	 $queryabc		    ->	fields($caf_update);
	 	 $queryabc			->	condition('id',$application_id,'=');
	  	$queryabc	        ->	execute();
		drupal_set_message('Occupier information successfully Updated.');
	}else{
		
		
		$occupier_update	=	db_update('fa_occupier_details');
		$occupier_update	->	fields($occupier_details);
		$occupier_update	->	condition('application_occupier_id',$application_id,'=');
		$occupier_update	->	condition('occupier_service_id',$service_id,'=');
		$occupier_update	->	condition('factory_type_id',$factorytype_id,'=');
		$occupier_update	->	condition('application_reference_no',$application_reference_no,'=');
		$occupier_update	->	execute();
		
		 $caf_update = 	array('application_status' => 'In','modification_date'=> date('Y-m-d'),'is_occupier_tab'=>1);
	  	 $queryabc 		=	db_update('fa_cafa');
	 	 $queryabc		    ->	fields($caf_update);
	 	 $queryabc			->	condition('id',$application_id,'=');
	  	$queryabc	        ->	execute();
		
		drupal_set_message('Occupier information successfully updated.');
		}
	
	remark_input($application_reference_no,$application_id,'In','Occupier information  of backlog factory is sucessfully added')	;	
	
	if($urole != 4){
			remark_input($application_reference_no,$application_id,'In','Occupier information edit from Applicant')	;	
		}else{
			remark_input($application_reference_no,$application_id,'In','Occupier information edit from AD')	;	
		}
		
	$form_state['rebuild'] = true;
}

?> 