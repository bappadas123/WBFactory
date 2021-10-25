<?php

	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	function inspection_report_factory_info($form, &$form_state, $inspection_reportID = '', $factoryID = '', $param = '') {
	
		global $user;
		$uid = $user->uid;
		
		$inspection_report_id = encryption_decryption_fun('decrypt', $inspection_reportID);
		//$factory_type_id = encryption_decryption_fun('decrypt', $factory_typeID);
		$factory_id = encryption_decryption_fun('decrypt', $factoryID);
		
	//variable declaration
		$service_id = $application_id = $RegistrationNo = $RegistrationDate = $LicenceNo = $LicenceDate = $ClassificationNo = $FactoryTypeid = $ReferenceNumber = $FactoryName = 	
		$factory_pincode = $factory_state = $factory_district = $factory_subdivision = $factory_areatype = $factory_block = $factory_panchayat = $factory_policestation = 
		$factory_postoffice = $nearest_landmark = $factory_addrline = $nature_manufacturing = $factory_classification_type = $factory_sector_ownership_type = '';
	//end
	
		$value_factory_id = isset($form_state['values']['factory_id']) ? $form_state['values']['factory_id'] : $factory_id;
		
		if((!empty($value_factory_id)) && ($value_factory_id != 0)) {
			
			if($inspection_report_id != 0) {
				$get_factory_info = get_inspection_report_factory_information($inspection_report_id);	
			}
			
			$get_registration_value = get_reg_lic_no($value_factory_id);
		
			$service_id     = $get_registration_value['service_id'];
			$application_id = $value_factory_id;
			$FactoryTypeid  = $get_registration_value['factory_typeid'];
			
			/*$power_details = fa_power_details($application_id, $service_id, $FactoryTypeid);
			$installed_power = $power_details[0]->installed_power;
			$power_unit = $power_details[0]->power_unit;
			$installed_power_hp = $power_details[0]->installed_power_hp;*/
			
			/****************************** REGISTRATION NUMBER ******************************/
			if((!empty($get_registration_value['factory_registrstion_no'])) && (!empty($get_registration_value['backlog_registration_no'])) && (!empty($get_registration_value['tm_factory_registration_no'])))
			{
				$RegistrationNo = $get_registration_value['factory_registrstion_no'];
			}
			else if((!empty($get_registration_value['factory_registrstion_no'])) && (empty($get_registration_value['backlog_registration_no'])) && (empty($get_registration_value['tm_factory_registration_no'])))
			{
				$RegistrationNo = $get_registration_value['factory_registrstion_no'];
			} 
			else if((empty($get_registration_value['factory_registrstion_no'])) && (!empty($get_registration_value['backlog_registration_no'])) && (empty($get_registration_value['tm_factory_registration_no'])))
			{
				$RegistrationNo = $get_registration_value['backlog_registration_no'];
			}
			else if((empty($get_registration_value['factory_registrstion_no'])) && (empty($get_registration_value['backlog_registration_no'])) && (!empty($get_registration_value['tm_factory_registration_no'])))
			{
				$RegistrationNo = $get_registration_value['tm_factory_registration_no'];
			}
			
			/****************************** REGISTRATION DATE ******************************/
			if((!empty($get_registration_value['registration_date'])) && (!empty($get_registration_value['backlog_registration_date'])))
			{
				$RegistrationDate = $get_registration_value['registration_date'];
			}
			else if((!empty($get_registration_value['registration_date'])) && (empty($get_registration_value['backlog_registration_date'])))
			{
				$RegistrationDate = $get_registration_value['registration_date'];
			} 
			else if((empty($get_registration_value['registration_date'])) && (!empty($get_registration_value['backlog_registration_date'])))
			{
				$RegistrationDate = $get_registration_value['backlog_registration_date'];
			}
			
			/****************************** LICENCE NUMBER ******************************/
			if((!empty($get_registration_value['factory_license_no'])) && (!empty($get_registration_value['backlog_license_number'])))
			{
				$LicenceNo = $get_registration_value['factory_license_no'];
			} 
			else if((!empty($get_registration_value['factory_license_no'])) && (empty($get_registration_value['backlog_license_number'])))
			{
				$LicenceNo = $get_registration_value['factory_license_no'];
			} 
			else if((empty($get_registration_value['factory_license_no'])) && (!empty($get_registration_value['backlog_license_number'])))
			{
				$LicenceNo = $get_registration_value['backlog_license_number'];
			}
			
			/****************************** LICENCE DATE ******************************/
			if((!empty($get_registration_value['license_date'])) && (!empty($get_registration_value['backlog_license_date'])))
			{
				$LicenceDate = $get_registration_value['license_date'];
			} 
			else if((!empty($get_registration_value['license_date'])) && (empty($get_registration_value['backlog_license_date'])))
			{
				$LicenceDate = $get_registration_value['license_date'];
			} 
			else if((empty($get_registration_value['license_date'])) && (!empty($get_registration_value['backlog_license_date'])))
			{
				$LicenceDate = $get_registration_value['backlog_license_date'];
			}
			
			/****************************** PLAN APPROVAL NO ******************************/
			if((!empty($get_registration_value['factory_plan_approval_number'])) && (!empty($get_registration_value['backlog_plan_approval_no'])))
			{
				$plan_approvalNo = $get_registration_value['factory_plan_approval_number'];
			} 
			else if((!empty($get_registration_value['factory_plan_approval_number'])) && (empty($get_registration_value['backlog_plan_approval_no'])))
			{
				$plan_approvalNo = $get_registration_value['factory_plan_approval_number'];
			} 
			else if((empty($get_registration_value['factory_plan_approval_number'])) && (!empty($get_registration_value['backlog_plan_approval_no'])))
			{
				$plan_approvalNo = $get_registration_value['backlog_plan_approval_no'];
			}
			
			/****************************** PLAN APPROVAL DATE ******************************/
			if((!empty($get_registration_value['plan_approval_date'])) && (!empty($get_registration_value['backlog_plan_approval_date'])))
			{
				$plan_approvalDate = $get_registration_value['plan_approval_date'];
			} 
			else if((!empty($get_registration_value['plan_approval_date'])) && (empty($get_registration_value['backlog_plan_approval_date'])))
			{
				$plan_approvalDate = $get_registration_value['plan_approval_date'];
			} 
			else if((empty($get_registration_value['plan_approval_date'])) && (!empty($get_registration_value['backlog_plan_approval_date'])))
			{
				$plan_approvalDate = $get_registration_value['backlog_plan_approval_date'];
			}
			
			/*****************************Classification No****************************/
			if(!empty($get_registration_value['classification_no']))
			{
				$ClassificationNo = $get_registration_value['classification_no'];
			}
			
			$inspected_by = get_name($uid);
			
			$ReferenceNumber        		= $get_registration_value['reference_number'];
			$FactoryName            		= $get_registration_value['factory_name'];
			$nature_manufacturing 			= $get_registration_value['nature_manufacturing'];
			$factory_classification_type 	= $get_registration_value['type_hazardous'];
			
		//for factory	
			$factory_pincode        		= $get_registration_value['pincode'];
			$factory_state          		= $get_registration_value['state'];
			$factory_district 	    		= $get_registration_value['district'];
			$factory_subdivision    		= $get_registration_value['subdivision'];
			$factory_areatype       		= $get_registration_value['areatype'];
			$factory_block          		= $get_registration_value['block'];
			$factory_panchayat      		= $get_registration_value['panchayat'];
			$factory_policestation  		= $get_registration_value['policestation'];
			$factory_postoffice     		= $get_registration_value['postoffice'];
			$nearest_landmark      			= $get_registration_value['nearest_landmark'];
			$factory_addrline				= $get_registration_value['addrline'];
			
			$factory_sector_ownership_type	= $get_registration_value['factory_owershiptype'];
			
		//data from inspection report table
			$ir_factory_name 						= $get_factory_info->factory_name;
			$ir_reference_number					= $get_factory_info->reference_number;
			$ir_factory_typeid 						= $get_factory_info->factory_typeid;
			$ir_registration_number					= $get_factory_info->registration_number;
			$ir_registration_date					= $get_factory_info->registration_date;
			$ir_licence_number						= $get_factory_info->licence_number;
			$ir_licence_date						= $get_factory_info->licence_date;
			$ir_classification_no					= $get_factory_info->classification_no;
			$ir_factory_classification_type			= $get_factory_info->factory_classification_type;
			$ir_pincode								= $get_factory_info->pincode;
			$ir_state								= $get_factory_info->state;
			$ir_district							= $get_factory_info->district;
			$ir_subdivision							= $get_factory_info->subdivision;
			$ir_areatype							= $get_factory_info->areatype;
			$ir_block								= $get_factory_info->block;
			$ir_panchayat							= $get_factory_info->panchayat;
			$ir_policestation						= $get_factory_info->policestation;
			$ir_postoffice							= $get_factory_info->postoffice;
			$ir_factory_zone						= $get_factory_info->factory_zone;
			$ir_nearest_landmark					= $get_factory_info->nearest_landmark;
			$ir_addrline							= $get_factory_info->addrline;
			$ir_building_plan_no					= $get_factory_info->building_plan_no;
			$ir_building_plan_date					= $get_factory_info->building_plan_date;
			$ir_inspected_by						= $get_factory_info->inspected_by;
			$ir_person_during_inspection  			= $get_factory_info->person_during_inspection;
			$ir_nature_manufacturing     			= $get_factory_info->nature_manufacturing;
			$ir_factory_sector_ownership_type		= $get_factory_info->factory_sector_ownership_type;
			$ir_type_power_station  				= $get_factory_info->ir_type_power_station;
			$ir_power_unit     						= $get_factory_info->ir_power_unit;
			$ir_installed_power						= $get_factory_info->ir_installed_power;
			
		//end
		
		
		//this section is for uploaded document display
		
			$get_uploaded_doc_lic = get_caf_upload_doc_details($application_id, $service_id, 'LIC', $FactoryTypeid, $ReferenceNumber);
			$get_uploaded_doc_reg = get_caf_upload_doc_details($application_id, $service_id, 'REG', $FactoryTypeid, $ReferenceNumber);		
			$get_uploaded_doc_plan = get_caf_upload_doc_details($application_id, $service_id, 'APPROVAL LETTER', $FactoryTypeid, $ReferenceNumber);		
			$get_uploaded_doc_caf = get_caf_upload_doc_details($application_id, $service_id, 'CAF', $FactoryTypeid, $ReferenceNumber);				
			
			$licence_certificate = l('<i class="fa fa-download" aria-hidden="true"></i> Licence Certificate','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $get_uploaded_doc_lic->id).'/'.encryption_decryption_fun('encrypt', 'LIC').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
									
			$registration_certificate = l('<i class="fa fa-download" aria-hidden="true"></i> Registration Certificate','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $get_uploaded_doc_reg->id).'/'.encryption_decryption_fun('encrypt', 'REG').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
			
			$plan_approval_letter = l('<i class="fa fa-download" aria-hidden="true"></i> Plan Approval Letter','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $get_uploaded_doc_plan->id).'/'.encryption_decryption_fun('encrypt', 'APPROVAL LETTER').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
			
			$caf_application = l('<i class="fa fa-download" aria-hidden="true"></i> CAF Application','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $get_uploaded_doc_caf->id).'/'.encryption_decryption_fun('encrypt', 'CAF').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
			
			
		//end
			
		}
		
		
		$form = array();
		$form['factory_information'] = array(
			'#type' => 'fieldset',
			'#title' => t('A. Factory Information'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => FALSE // Added 
		);
		
		//this section is for add factory data from fact_mast table
		
		$add_new_factory = l('Add Registered Factory', 'add-new-factory', array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'font-weight: bold; font-size: 18px;')));
		$factory_list_admin = l('List of Factories 1', 'factory-list-admin/ACTIVE', array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'font-weight: bold; font-size: 18px;')));
		
		$form['factory_information']['add_new_factory'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12"><div style="color:#f00">If you didn\'t find Licence No. in the Factory Licence No. dropdown list then click on '.$add_new_factory.' or click on '.$factory_list_admin.'.</div>',
			'#suffix' 			=> '</div></div>',
		);
		
		//end
		  
		$form['factory_information']['factory_id'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-3 col-xs-6"><label class="select label-block">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t('Choose Factory Licence No.'),
			'#attributes' 		=> array('class' => array( '')),
			'#options' 			=> get_factory_licence_no(NULL),
			'#type' 			=> 'select',
			'#default_value'   	=> $value_factory_id,
			'#required' 		=> TRUE,
			'#ajax' 			=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',
										'callback' 		=> 'get_ajax_factory_info',
										'progress' 		=> array(
										'type' 			=> 'throbber',
										'message' 		=> t('loading')
									),
			),
			/*'#select2' => array(
				'width' => '500',
				//'placeholder' => '- Select -',
				'allowClear' => TRUE
        	)*/
		);
		
		if($inspection_report_id != 0) {
			$form['factory_information']['inspection_report_id'] = array(
				'#prefix' 			=> '<div id="inspection_report_id"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#type' 			=> 'hidden',
				'#default_value' 	=> !empty($inspection_report_id) ? $inspection_report_id : '',
			);
		} else {
			$form['factory_information']['inspection_report_id'] = array(
				'#prefix' 			=> '<div id="inspection_report_id"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#type' 			=> 'hidden',
				'#default_value' 	=> $inspection_report_id,
			);
		}
		
		
		if(!empty($value_factory_id) && ($value_factory_id != 0)) {
			
			$form['factory_information']['licence_certificate'] = array(
				'#prefix' 				=> '<div id="licence_certificate_id"><div class="col-md-2 col-xs-12"><label class="input label-block">'.$licence_certificate.'',
				'#suffix' 				=> '</label></div></div>',
			);
			
			$form['factory_information']['registration_certificate'] = array(
				'#prefix' 				=> '<div id="registration_certificate_id"><div class="col-md-3 col-xs-12"><label class="input label-block">'.$registration_certificate.'',
				'#suffix' 				=> '</label></div></div>',
			);
			
			$form['factory_information']['plan_approval_letter'] = array(
				'#prefix' 				=> '<div id="plan_approval_letter_id"><div class="col-md-2 col-xs-12"><label class="input label-block">'.$plan_approval_letter.'',
				'#suffix' 				=> '</label></div></div>',
			);
			
			$form['factory_information']['caf_application'] = array(
				'#prefix' 				=> '<div id="caf_application_id"><div class="col-md-2 col-xs-12"><label class="input label-block">'.$caf_application.'',
				'#suffix' 				=> '</label></div></div>',
			);
			
			$form['factory_information']['reference_number'] = array(
				'#prefix' 			=> '<div id="reference_number_id"><label class="select label-block">',
				'#suffix' 			=> '</label></div>',
				'#title' 			=> t('(i)a. Enter reference_number'),
				'#type' 			=> 'hidden',
				'#value' 			=> !empty($ir_reference_number) ? $ir_reference_number : $ReferenceNumber,
			);
		
	//factory name and address section
			
			$value_factory_name = !empty($ir_factory_name) ? $ir_factory_name : $FactoryName;
			
			$form['factory_information']['factory_name'] = array(
				'#prefix' 			=> '<div id="factory_name_id"><div class="col-md-10 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('1. Enter Registered Factory Name'),
				'#attributes' 		=> array('class' => array( ''),'placeholder' => 'Registered Factory Name','readonly' => 'readonly'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#value' 			=> $value_factory_name,
			);
			
			$form['factory_information']['factory_address_heading'] = array(
				'#prefix' 				=> '<div class="col-md-12 col-xs-12"><h4><b>2. Address of the Factory</b></h4>',
				'#suffix' 				=> '</div>',
			);
			
			$value_pincode = !empty($ir_pincode) ? $ir_pincode : $factory_pincode;
			
			$form['factory_information']['pincode']       = array(
				'#prefix' 				=> '<div id="pincode_id"><div class="col-md-4 col-xs-12"><label class="select label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Pincode','readonly' => 'readonly'),
				'#maxlength' 		 	=> 6,
				'#title' 			 	=> t('(i) Pincode'),
				'#value' 	 	        => $value_pincode,
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
				'#element_validate' 	=> array('element_validate_numeric_positive'),
			);
			
			$value_state = !empty($ir_state) ? $ir_state : $factory_state;
			
			$form['factory_information']['state'] = array(
				'#title' 		=> '(ii) State',
				'#type' 		=> 'select',
				'#id' 			=> 'state_name',
				'#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
				'#disabled' 	=> TRUE,
				'#options' 		=> get_all_state($value_state),
				'#value' 	 	=> $value_state,
				'#required' 	=> TRUE,
				'#prefix' 		=> '<div id="ld_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
			
			$value_district = !empty($ir_district) ? $ir_district : $factory_district;
			
			$form['factory_information']['district'] = array(
				'#title' => '(iii) District',
				'#type' => 'select',
				'#id' => 'district_name',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
				'#options' => get_district_by_id($value_state),
				'#value' 	=> $value_district,
				'#required' => TRUE,
				'#prefix' => '<div id="ld_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			$value_subdivision = !empty($ir_subdivision) ? $ir_subdivision : $factory_subdivision;
				
			$form['factory_information']['subdivision'] = array(
				'#title' => '(iv) Sub-Division',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'Sub Division','disabled' => 'disabled'),
				'#options' => common_custom_user_subdivisionlist_list_new($value_district),
				'#required' => TRUE,
				'#value' 	=> $value_subdivision,
				'#prefix' => '<div id="ld_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			$value_areatype = !empty($ir_areatype) ? $ir_areatype : $factory_areatype;
			
			$form['factory_information']['areatype'] = array(
				'#title' => '(v) Area Type',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'Area Type','disabled' => 'disabled'),
				'#options' => common_custom_user_areatype_list_new($value_district, $value_subdivision),
				'#required' => TRUE,
				'#value' 	=> $value_areatype,
				'#prefix' => '<div id="ld_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			if ($value_areatype == 'B') {
				$areatype_name = 'Block';
			} elseif ($value_areatype == 'M') {
				$areatype_name = 'Municipality';
			} elseif ($value_areatype == 'C') {
				$areatype_name = 'Corporation';
			} elseif ($value_areatype == 'S') {
				$areatype_name = 'SEZ';
			} elseif ($value_areatype == 'N') {
				$areatype_name = 'Notified Area';
			}
			
			$value_block = !empty($ir_block) ? $ir_block : $factory_block;
				
			$form['factory_information']['block'] = array(
				'#title' 		=> '(vi) '. $areatype_name,
				'#type'         => 'select',
				'#disabled' => TRUE,
				'#attributes'   => array('class' => array(''),'placeholder' => 'Block','disabled' => 'disabled'),
				'#options' 		=> common_custom_user_block_list_new($value_subdivision, $value_areatype),
				'#required' 	=> TRUE,
				'#value' 	    => $value_block,
				'#prefix' 		=> '<div id="ld_empareatype_name_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
			
			if ($value_areatype == 'B') {
				$area_name = 'Gram Panchayat';
				$area_code = 'V';
			} elseif ($value_areatype == 'M') {
				$area_name = 'Ward';
				$area_code = 'W';
			} elseif ($value_areatype == 'C') {
				$area_name = 'Ward';
				$area_code = 'C';
			} elseif ($value_areatype == 'S') {
				$area_name = 'Sector';
				$area_code = 'S';
			} elseif ($value_areatype == 'N') {
				$area_name = 'Notified Area';
				$area_code = 'N';
			}
			
			$value_panchayat = !empty($ir_panchayat) ? $ir_panchayat : $factory_panchayat;
				
			$form['factory_information']['panchayat'] = array(
				'#title' => '(vii) '.$area_name,
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'panchayat','disabled' => 'disabled'),
				'#options' => common_custom_user_villward_list_new($value_block, $area_code),
				'#value' 	    => $value_panchayat,
				'#prefix' => '<div id="ld_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
				'#required' => TRUE,
			);
			
			$value_policestation = !empty($ir_policestation) ? $ir_policestation : $factory_policestation;
			
			$form['factory_information']['policestation'] = array(
				'#title' => '(viii) Police Station',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array( ''),'placeholder' => 'Police Station','disabled' => 'disabled'),
				'#options' => common_custom_user_ps_list_new($value_district),
				'#required' => TRUE,
				'#value' 	    => $value_policestation,
				'#prefix' => '<div id="ld_empps_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$value_postoffice = !empty($ir_postoffice) ? $ir_postoffice : $factory_postoffice;
			
			$form['factory_information']['postoffice'] = array(
				'#title' => '(ix) Post Office',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''), 'placeholder' => 'Post Office','disabled' => 'disabled'),
				'#options' => common_custom_post_office_list_new($value_pincode),
				'#value' 	    => $value_postoffice,
				'#required' => TRUE,
				'#prefix' => '<div id="ld_post_office_div"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
		
			$factory_zone_name = get_zone_name($value_block, $value_panchayat);
		
			$form['factory_information']['factory_zone'] = array(
				'#value'   => $factory_zone_name[0]->zone_id,
				'#type' => 'hidden',
			);
			
			$form['factory_information']['factory_zone_name'] = array(
				'#prefix' => '<div id="factory_zone_div"><div class="col-md-4"><label class="input label-block">',
				'#suffix' => '</label></div></div>',
				'#title'  => t('(x) Factory Zone'),
				'#value' 	    => !empty($factory_zone_name[0]->zone_name) ? $factory_zone_name[0]->zone_name : '',
				'#type' => 'textfield',
				'#required' => TRUE,
				'#attributes'		=> array('class' => array( ''),'readonly' => 'readonly','placeholder' => 'Factory Zone'),
				'#element_validate' 	=> array('element_validate_hyphenfullstop'),
			);
			
			if(!empty($nearest_landmark)) {
				$form['factory_information']['nearest_landmark'] = array(
					'#prefix' => '<div id="nearest_landmark_id"><div class="col-md-4"><label class="input label-block">',
					'#suffix' => '</label></div></div>',
					'#title' => t('(xi) Nearest Landmark'),
					'#type' => 'textfield',
					'#value' 	    => !empty($ir_nearest_landmark) ? $ir_nearest_landmark : $nearest_landmark,
					'#attributes' => array('class' => array('charField'),'readonly' => 'readonly','placeholder' => 'Nearest Landmark'),
					'#element_validate' 	=> array('element_validate_alphabatic_text'),
					'#required' => TRUE,
				);
			} else {
				unset($form_state['input']['nearest_landmark']);
				$form['factory_information']['nearest_landmark'] = array(
					'#prefix' => '<div id="nearest_landmark_id"><div class="col-md-4"><label class="input label-block">',
					'#suffix' => '</label></div></div>',
					'#title' => t('(xi) Nearest Landmark'),
					'#type' => 'textfield',
					'#default_value' 	    => !empty($ir_nearest_landmark) ? $ir_nearest_landmark : $nearest_landmark,
					'#attributes' => array('class' => array('charField'),'placeholder' => 'Nearest Landmark'),
					'#element_validate' 	=> array('element_validate_alphabatic_text'),
					'#required' => TRUE,
				);
			}
		
			$form['factory_information']['addrline'] = array(
				'#prefix' => '<div id="addrline_id"><div class="col-md-12"><label class="textarea label-block">',
				'#suffix' => '</label></div></div>',
				'#title' => '(xii) Address',
				'#rows' => 3,
				'#type' => 'textarea',
				'#required' => TRUE,
				'#value' 	    => !empty($ir_addrline) ? $ir_addrline : $factory_addrline,
				'#attributes' => array('class' => array(''),'placeholder' => 'Address Line','readonly' => 'readonly'),
				'#element_validate' => array('element_validate_streetaddress'), 
			);
			
	//factory address section end
	
			//unset($form_state['input']['building_plan_no']);
			$form['factory_information']['building_plan_no'] = array(
				'#prefix' 			=> '<div id="building_plan_no_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('3. (i) Factory Building Plan No.'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'placeholder' => 'Factory Building Plan No. (Approval from CIF)','readonly' => 'readonly'),
				//'#default_value' 	=> !empty($ir_building_plan_no) ? $ir_building_plan_no : $plan_approvalNo,
				'#value' 	=> !empty($ir_building_plan_no) ? $ir_building_plan_no : $plan_approvalNo,
				'#element_validate' => array('element_validate_numeric_positive'),
			);
			
			$formated_plan_approvalDate = trim(implode('-', array_reverse(explode('-', $plan_approvalDate))));
			$formated_ir_building_plan_date = trim(implode('-', array_reverse(explode('-', $ir_building_plan_date))));
			//unset($form_state['input']['building_plan_date']);
			$form['factory_information']['building_plan_date'] = array(
				'#prefix' 			=> '<div id="building_plan_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(ii) Factory Building Plan Date'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'readonly' => 'readonly'),
				//'#default_value' 	=> !empty($formated_ir_building_plan_date) ? $formated_ir_building_plan_date : $formated_plan_approvalDate,
				'#value' 	=> !empty($formated_ir_building_plan_date) ? $formated_ir_building_plan_date : $formated_plan_approvalDate,
				'#element_validate' => array('element_validate_date'),
			);
			
			$form['factory_information']['licence_number'] = array(
				'#prefix' 			=> '<div id="licence_number_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('4. (i) Licence No.'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array('numeric_positive'),'readonly' => 'readonly'),
				'#value' 			=> !empty($ir_licence_number) ? $ir_licence_number : $LicenceNo,
				'#element_validate' => array('element_validate_numeric_positive'),
			);
			/*$form['factory_information']['licence_number'] = array(
				'#prefix' 			=> '<div id="licence_number_id"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				//'#title' 			=> t('4. (i) Licence No.'),
				'#type' 			=> 'hidden',
				'#value' 			=> !empty($ir_licence_number) ? $ir_licence_number : $LicenceNo,
			);*/
			
			$formated_LicenceDate = trim(implode('-', array_reverse(explode('-', $LicenceDate))));
			$formated_ir_licence_date = trim(implode('-', array_reverse(explode('-', $ir_licence_date))));
			$form['factory_information']['licence_date'] = array(
				'#prefix' 			=> '<div id="licence_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(ii) Licence Date'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'readonly' => 'readonly'),
				'#value' 			=> !empty($formated_ir_licence_date) ? $formated_ir_licence_date : $formated_LicenceDate,
				'#element_validate' => array('element_validate_date'),
			);
			
			$form['factory_information']['registration_number'] = array(
				'#prefix' 			=> '<div id="registration_number_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(iii) Registration No.'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'readonly' => 'readonly'),
				'#value' 			=> !empty($ir_registration_number) ? $ir_registration_number : $RegistrationNo,
				'#element_validate' => array('element_validate_factory_reg_no'),
			);
			
			$formated_RegistrationDate = trim(implode('-', array_reverse(explode('-', $RegistrationDate))));
			$formated_ir_registration_date = trim(implode('-', array_reverse(explode('-', $ir_registration_date))));
			$form['factory_information']['registration_date'] = array(
				'#prefix' 			=> '<div id="registration_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(iv) Registration Date'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'readonly' => 'readonly'),
				'#value' 			=> !empty($formated_ir_registration_date) ? $formated_ir_registration_date : $formated_RegistrationDate,
				'#element_validate' => array('element_validate_date'),
			);
			
			unset($form_state['input']['factory_sector_ownership_type']);
			$factory_sector_ownership_type_list = array("" => "-- Select Sector ? Ownership Type --", 
											"pv" 			=> "Pvt Ltd Company",
        									"ltd" 			=> "Ltd Company",
											"par_firm" 		=> "Partnership Firm",
											"pro_firm" 		=> "Proprietorship Firm",
											"llp" 			=> "Limited Liability Partnership",
											"cooperative" 	=> "Co-operative",
											"registered" 	=> "Registered Society under Society Register",
        									"govt" 			=> "Govt.",
											"psu" 			=> "PSU",
											"localbody" 	=> "Local Body",
											"others" 		=> "Others",
									);
			$value_factory_sector_ownership_type = !empty($ir_factory_sector_ownership_type) ? $ir_factory_sector_ownership_type : $factory_sector_ownership_type;
			$form['factory_information']['factory_sector_ownership_type'] = array(
				'#prefix' 			=> '<div id="factory_sector_ownership_type_id"><div class="col-md-4 col-xs-12" ><label class="select label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('5. Ownership Type/ Sector'),
				'#type' 			=> 'select',
				'#attributes' 		=> array('class' => array('')/*,'disabled' => 'disabled'*/),
				//'#disabled' 		=> TRUE,
				'#options' 			=> $factory_sector_ownership_type_list,
				'#required' 		=> TRUE,
				'#default_value' 	=> $value_factory_sector_ownership_type,
			);
			
			unset($form_state['input']['factory_typeid']);
			$factory_type_val = !empty($ir_factory_typeid) ? $ir_factory_typeid : $FactoryTypeid;
			$value_factory_type = isset($form_state['values']['factory_typeid']) ? $form_state['values']['factory_typeid'] : $factory_type_val;
			$form['factory_information']['factory_typeid'] = array(
				'#prefix' 			=> '<div id="factory_typeid_id"><div class="col-md-4 col-xs-12" ><label class="select label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('6. Category of the Factory'),
				'#type' 			=> 'select',
				'#attributes' 		=> array('class' => array('')),
				'#options' 			=> get_factory_type(NULL),
				'#required' 		=> TRUE,
				'#default_value' 	=> $factory_type_val,
				'#ajax' 			=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',
										'callback' 		=> 'get_ajax_power_details',
										'progress' 		=> array(
										'type' 			=> 'throbber',
										'message' 		=> t('loading')
									),
				),
			);
			
			unset($form_state['input']['classification_no']);
			$form['factory_information']['classification_no'] = array(
				'#prefix' 			=> '<div id="classification_no_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('7. (i) Classification No.'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'placeholder' => 'Classification No.'),
				'#autocomplete_path'=> 'nicautocomplete',
				'#id' 				=> 'niccode_autocomplete',
				'#default_value' 	=> !empty($ir_classification_no) ? $ir_classification_no : $ClassificationNo,
				'#element_validate' => array('element_validate_factory_classif_no'),
			);
			
			unset($form_state['input']['factory_classification_type']);
			$factory_classification_type_list = array("" => "-- Select Classification of the Factory --", "MAH" => "Major Accidents Hazards Unit(MAH)", "Hazardous Unit" => "Hazardous Unit", "Potentially Hazardous Unit" => "Potentially Hazardous Unit", "others" => "Others");
			$value_factory_classification_type = !empty($ir_factory_classification_type) ? $ir_factory_classification_type : $factory_classification_type;
			$form['factory_information']['factory_classification_type'] = array(
				'#prefix' 			=> '<div id="factory_classification_type_id"><div class="col-md-4 col-xs-12" ><label class="select label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(ii). Classification of the Factory'),
				'#type' 			=> 'select',
				'#attributes' 		=> array('class' => array('')/*,'disabled' => 'disabled'*/),
				//'#disabled' 		=> TRUE,
				'#options' 			=> $factory_classification_type_list,
				'#required' 		=> TRUE,
				'#default_value' 	=> $value_factory_classification_type,
			);
			
			$form['factory_information']['inspected_by'] = array(
				'#prefix' 			=> '<div id="inspected_by_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('8. Inspected by'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'placeholder' => 'Inspected by','readonly' => 'readonly'),
				'#value' 			=> !empty($ir_inspected_by) ? $ir_inspected_by : $inspected_by,
				'#element_validate' => array('element_validate_alphabatic_fullstop'),
			);
			
			unset($form_state['input']['person_during_inspection']);
			$form['factory_information']['person_during_inspection'] = array(
				'#prefix' 			=> '<div id="person_during_inspection_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('9. Responsible Person present during Inspection:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'placeholder' => 'Responsible Person present during Inspection'/*,'readonly' => 'readonly'*/),
				'#default_value' 	=> !empty($ir_person_during_inspection) ? $ir_person_during_inspection : '',
				'#element_validate' => array('element_validate_alphabatic_fullstop'),
			);
			
			$form['factory_information']['nature_manufacturing'] = array(
				'#prefix' 			=> '<div id="nature_manufacturing_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('10. Nature of manufacturing process'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array('charField'),'readonly' => 'readonly'),
				'#value' 			=> !empty($ir_nature_manufacturing) ? $ir_nature_manufacturing : $nature_manufacturing,
				'#element_validate' => array('element_validate_hyphen_fullstop_ampersand'),
			);
			
			if($value_factory_type == 1 || $value_factory_type == 3) {
				$power_details = get_power_generating_station($application_id,$ReferenceNumber,$value_factory_type,$service_id);
				foreach($power_details as $power){
					$type_power_station = $power->type_power_station;
					$power_unit 		= $power->power_unit;
					$installed_power	= $power->installed_power;
					$power_id			= $power->id; 
				}
				
				$form['power_details'] = array(
					'#type' 		=> 'fieldset',
					'#title' 		=> t('B. Power Details'),
					'#collapsible' 	=> TRUE, // Added
					'#collapsed' 	=> FALSE, // Added
					'#prefix' 		=> '<div id="reload_power_details">',
					'#suffix' 		=> '</div>',
				);
				
				unset($form_state['input']['is_generating']);
				$radios_options = array('power_generating_station'=>"Power generating station",'other'=>"Other");
				$form['power_details']['is_generating']= array(
					'#prefix' 			=> '<div class="row"><div id="is_generating_id"><div class="col-md-4 col-xs-4">',
					'#suffix'    		=> '</div></div>',
					'#type'		 		=> 'radios',
					'#title'			=>	t('Type of power generating station'),
					'#options'   		=> $radios_options,	
					'#default_value' 	=> !empty($ir_type_power_station) ? $ir_type_power_station : $type_power_station,
					'#attributes' 		=>  array('class'=>array('')),
					'#required'			=> TRUE,
				);
				
				unset($form_state['input']['power_type']);
				$form['power_details']['power_type'] = array(
					'#prefix' 				=> '<div id="power_type_id"><div class="col-md-4 col-xs-4">',
					'#suffix' 				=> '</div></div>',
					'#title'				=>	t('Unit of power'),
					'#type' 		 		=> 'select',
					'#default_value' 		=>  !empty($ir_power_unit) ? $ir_power_unit : $power_unit,
					'#options'	 			=>  array('' => '-- Select --', 'HP' => 'HP', 'KW' => 'KW'),
					'#attributes' 			=>  array('class'=>array('')),
					'#required' 			=>  TRUE,
				);
				
				unset($form_state['input']['installed_power']);
				$form['power_details']['installed_power'] = array(
					'#prefix' 				=> '<div id="installed_power_id"><div class="col-md-4 col-xs-4">',
					'#suffix' 				=> '</div></div></div>',
					'#title'				=>	t('Power'),
					'#type' 				=> 'textfield',
					'#element_validate'		=>  array('DOUBLE_FIELD_VALIDATION'),
					'#default_value' 		=>  !empty($ir_installed_power) ? $ir_installed_power : $installed_power,
					'#attributes' 			=>  array('class'=>array(''),'placeholder' => 'Power'),
					'#required' 			=>  TRUE,
				);
				
			} else if($value_factory_type == 2) {
				$form['power_details'] = array(
					'#prefix' 		=> '<div id="reload_power_details">',
					'#suffix' 		=> '</div>',
				);
				
				$form['power_details']['is_generating']= array(
					'#prefix' 			=> '<div class="row"><div id="is_generating_id"><div class="col-md-4 col-xs-4">',
					'#suffix'    		=> '</div></div>',
				);
				
				$form['power_details']['power_type'] = array(
					'#prefix' 				=> '<div id="power_type_id"><div class="col-md-4 col-xs-4">',
					'#suffix' 				=> '</div></div>',
				);
				
				$form['power_details']['installed_power'] = array(
					'#prefix' 				=> '<div id="installed_power_id"><div class="col-md-4 col-xs-4">',
					'#suffix' 				=> '</div></div></div>',
				);	
			} else {
				$form['power_details'] = array(
					'#type' 		=> 'fieldset',
					'#title' 		=> t('B. Power Details'),
					'#collapsible' 	=> TRUE, // Added
					'#collapsed' 	=> FALSE, // Added
					'#prefix' 		=> '<div id="reload_power_details">',
					'#suffix' 		=> '</div>',
				);
				
				$radios_options = array('power_generating_station'=>"Power generating station",'other'=>"Other");
				$form['power_details']['is_generating']= array(
					'#prefix' 			=> '<div class="row"><div id="is_generating_id"><div class="col-md-4 col-xs-4">',
					'#suffix'    		=> '</div></div>',
					'#type'		 		=> 'radios',
					'#attributes' 		=> array('class' => array('')),
					'#title'			=> t('Type of power generating station'),
					'#options'   		=> $radios_options,
					'#required'			=> TRUE,
					//'#value' 			=> '',
				);
				
				$form['power_details']['power_type'] = array(
					'#prefix' 				=> '<div id="power_type_id"><div class="col-md-4 col-xs-4">',
					'#suffix' 				=> '</div></div>',
					'#title'				=>	t('Unit of power'),
					'#type' 		 		=> 'select',
					'#options'	 			=> array('' => '-- Select --'),
					'#attributes' 			=> array('class'=>array('form-control')),
					'#required' 			=> TRUE,
					//'#value' 				=> '',
				);
				
				$form['power_details']['installed_power'] = array(
					'#prefix' 				=> '<div id="installed_power_id"><div class="col-md-4 col-xs-4">',
					'#suffix' 				=> '</div></div></div>',
					'#title'				=>	t('Power'),
					'#type' 				=> 'textfield',
					'#attributes' 			=>  array('class'=>array('form-control'),'placeholder' => 'Power'),
					'#required' 			=>  TRUE,
					//'#value' 				=> '',
				);	
			}
			
		} else {
			
			$form['factory_information']['licence_certificate'] = array(
				'#prefix' 				=> '<div id="licence_certificate_id"><div class="col-md-2 col-xs-12"><label class="input label-block">'.$licence_certificate.'',
				'#suffix' 				=> '</label></div></div>',
			);
			
			$form['factory_information']['registration_certificate'] = array(
				'#prefix' 				=> '<div id="registration_certificate_id"><div class="col-md-3 col-xs-12"><label class="input label-block">'.$registration_certificate.'',
				'#suffix' 				=> '</label></div></div>',
			);
			
			$form['factory_information']['plan_approval_letter'] = array(
				'#prefix' 				=> '<div id="plan_approval_letter_id"><div class="col-md-2 col-xs-12"><label class="input label-block">'.$plan_approval_letter.'',
				'#suffix' 				=> '</label></div></div>',
			);
			
			$form['factory_information']['caf_application'] = array(
				'#prefix' 				=> '<div id="caf_application_id"><div class="col-md-2 col-xs-12"><label class="input label-block">'.$caf_application.'',
				'#suffix' 				=> '</label></div></div>',
			);
			
			unset($form_state['input']);
			
			$form['factory_information']['reference_number'] = array(
				'#prefix' 			=> '<div id="reference_number_id">',
				'#suffix' 			=> '</div>',
				'#title' 			=> t('(i)a. Enter reference_number'),
				'#type' 			=> 'hidden',
				//'#value' 			=> '',
			);
			
		
	//factory name and address section
	
			$form['factory_information']['factory_name'] = array(
				'#prefix' 			=> '<div id="factory_name_id"><div class="col-md-10 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('1. Enter Registered Factory Name'),
				'#attributes' 		=> array('class' => array( ''),'placeholder' => 'Registered Factory Name'),
				'#type' 			=> 'textfield',
				//'#value' 			=> '',
				'#required' 		=> TRUE,
			);
			$form['factory_information']['factory_address_heading'] = array(
				'#prefix' 				=> '<div class="col-md-12 col-xs-12"><h4><b>2. Address of the Factory</b></h4>',
				'#suffix' 				=> '</div>',
			);
			$form['factory_information']['pincode']       = array(
				'#prefix' 				=> '<div id="pincode_id"><div class="col-md-4 col-xs-12"><label class="select label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Pincode'),
				'#maxlength' 		 	=> 6,
				'#title' 			 	=> t('(i) Pincode'),
				//'#value' 				=> '',
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
			);
			
			$form['factory_information']['state'] = array(
				'#title' => '(ii) State',
				'#type' => 'select',
				'#id' => 'state_name',
				'#disabled' => TRUE,
				'#attributes' => array(
					'class' => array(''),
					'placeholder' => 'State',
					'disabled' => 'disabled'
				),
				//'#value' 		=> '',
				'#required' => TRUE,
				'#options' => array('' => t('Select State')),
				'#prefix' => '<div id="ld_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			$form['factory_information']['district'] = array(
				'#title' => '(iii) District',
				'#type' => 'select',
				'#id' => 'district_name',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'District','disabled' => 'disabled'),
				'#required' => TRUE,
				'#options' => array(
					'' => t('Select District')
				),
				//'#value' 		=> '',
				'#prefix' => '<div id="ld_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
				
			$form['factory_information']['subdivision'] = array(
				'#title' => '(iv) Sub-Division',
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Sub Division'
				),
				'#required' => TRUE,
				'#options' => array(
					'' => t('Select Sub-Division')
				),
				//'#value' 		=> '',
				'#prefix' => '<div id="ld_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['areatype'] = array(
				'#title' => '(v) Area Type',
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
	
					'placeholder' => 'Area Type'
				),
				'#options' => array(
					'0' => t('Select Area Type')
				),
				//'#value' 		=> '',
				'#required' => TRUE,
				'#prefix' => '<div id="ld_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['block'] = array(
				'#title' => '(vi) Block / Municipality / Corporation /<br> Notified Area / SEZ',
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Block'
				),
				'#options' => array(
					'0' => t('Select Block / Municipality / Corporation / Notified Area / SEZ')
				),
				//'#value' 		=> '',
				'#required' => TRUE,
				'#prefix' => '<div id="ld_empareatype_name_replace"><div class="col-md-4"><label class="select label-block" title="Block / Municipality / Corporation / Notified Area / SEZ">',
				'#suffix' => '</label></div></div>'
			);
		   
			$form['factory_information']['panchayat'] = array(
				'#title' => '(vii) Gram Panchayat / Ward / Sector',
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'panchayat'
				),
				'#options' => array(
					'0' => t('Select Gram Panchayat / Ward / Sector / Notified Area')
				),
				//'#value' 		=> '',
				'#required' => TRUE,
				'#prefix' => '<div id="ld_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['policestation'] = array(
				'#title' => '(viii) Police Station',
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Police Station'
				),
				'#options' => array(
					'0' => t('Select Police Station')
				),
				//'#value' 		=> '',
				'#required' => TRUE,
				'#prefix' => '<div id="ld_empps_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['postoffice'] = array(
				'#title' => '(ix) Post Office',
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Post Office'
				),
				'#options' => array(
					'0' => t('Select Post Office')
				),
				//'#value' 		=> '',
				'#required' => TRUE,
				'#prefix' => '<div id="ld_post_office_div"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['factory_zone_name'] = array(
				'#prefix' => '<div id="factory_zone_div"><div class="col-md-4"><label class="input label-block">',
				'#suffix' => '</label></div></div>',
				'#title'  => t('(x) Factory Zone'),
				'#type' => 'textfield',
				'#required' => TRUE,
				//'#value' => '',
				'#attributes' => array('class' => array(''),'readonly' => 'readonly','placeholder' => 'Factory Zone'),
			);
			
			$form['factory_information']['nearest_landmark'] = array(
				'#prefix' => '<div id="nearest_landmark_id"><div class="col-md-4"><label class="input label-block">',
				'#suffix' => '</label></div></div>',
				'#title' => t('(xi) Nearest Landmark'),
				'#type' => 'textfield',
				//'#value' => '',
				'#required' => TRUE,
				'#attributes' => array('class' => array('charField'),'placeholder' => 'Nearest Landmark'),
				'#required' => TRUE,
			);		
		
			$form['factory_information']['addrline'] = array(
				'#title' => '(xii) Address',
				'#rows' => 3,
				'#type' => 'textarea',
				'#required' => TRUE,
				//'#value' => '',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Address Line',
				),
				'#prefix' => '<div id="addrline_id"><div class="col-md-12"><label class="textarea label-block">',
				'#suffix' => '</label></div></div>'
			);
			
	//factory address section end
	
			$form['factory_information']['building_plan_no'] = array(
				'#prefix' 			=> '<div id="building_plan_no_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('3. (i) Factory Building Plan No.'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'placeholder' => 'Factory Building Plan No. (Approval from CIF)'),
				//'#value' 			=> '',
			);
			$form['factory_information']['building_plan_date'] = array(
				'#prefix' 			=> '<div id="building_plan_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(ii) Factory Building Plan Date'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'placeholder' => 'Factory Building Plan Date (Approval from CIF)'),
				//'#value' 			=> '',
				//'#value' 			=> !empty($ir_registration_date) ? implode('/', array_reverse(explode('-', $ir_registration_date))) : $RegistrationDate,
			);
			
			$form['factory_information']['licence_number'] = array(
				'#prefix' 			=> '<div id="licence_number_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('4. (i) Licence No.'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'Licence No.','readonly' => 'readonly'),
				//'#value' 			=> '',
			);
			/*$form['factory_information']['licence_number'] = array(
				'#prefix' 			=> '<div id="licence_number_id"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				//'#title' 			=> t('4. (i) Licence No.'),
				'#type' 			=> 'hidden',
				//'#value' 			=> '',
			);*/
			$form['factory_information']['licence_date'] = array(
				'#prefix' 			=> '<div id="licence_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(ii) Licence Date'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				//'#value' 			=> '',
				//'#attributes' 		=> array('class'=>array('form-control datepicker_cls'),'title'=>'Enter Licence Date.','disabled' => 'disabled','placeholder' => 'Licence Date'),
				'#attributes' 		=> array('class'=>array(''),'readonly' => 'readonly','placeholder' => 'Licence Date'),
			);
			
			$form['factory_information']['registration_number'] = array(
				'#prefix' 			=> '<div id="registration_number_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(iii) Registration No.'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'Registration No.','readonly' => 'readonly'),
				//'#value' 			=> '',
			);
			$form['factory_information']['registration_date'] = array(
				'#prefix' 			=> '<div id="registration_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(iv) Registration Date'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				//'#value' 			=> '',
				//'#attributes' 		=> array('class'=>array('form-control datepicker_cls'),'title'=>'Enter Registration Date.','disabled' => 'disabled','placeholder' => 'Registration Date'),
				'#attributes' 		=> array('class'=>array(''),'readonly' => 'readonly','placeholder' => 'Registration Date'),
	
			);
			
			$form['factory_information']['factory_sector_ownership_type'] = array(
				'#prefix' 			=> '<div id="factory_sector_ownership_type_id"><div class="col-md-4 col-xs-12" ><label class="select label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('5. Ownership Type / Sector'),
				'#type' 			=> 'select',
				'#attributes' 		=> array('class' => array('')/*,'disabled' => 'disabled'*/),
				//'#disabled' 		=> TRUE,
				'#options' 			=> array('' => t('Select Sector')),
				'#required' 		=> TRUE,
				//'#value' 			=> '',
			);
			
			$form['factory_information']['factory_typeid'] = array(
				'#prefix' 			=> '<div id="factory_typeid_id"><div class="col-md-4 col-xs-12" ><label class="select label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('6. Category of the Factory'),
				'#type' 			=> 'select',
				'#attributes' 		=> array('class' => array('')/*,'disabled' => 'disabled'*/),
				//'#disabled' 		=> TRUE,
				'#options' 			=> array('' => t('Select Category of the Factory')),
				'#required' 		=> TRUE,
				//'#value' 			=> '',
			);
			
			$form['factory_information']['classification_no'] = array(
				'#prefix' 			=> '<div id="classification_no_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('7. (i) Classification No.'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'Classification No.'),
				//'#value' 			=> '',
			);
			
			$form['factory_information']['factory_classification_type'] = array(
				'#prefix' 			=> '<div id="factory_classification_type_id"><div class="col-md-4 col-xs-12" ><label class="select label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(ii). Classification of the Factory'),
				'#type' 			=> 'select',
				'#attributes' 		=> array('class' => array('')/*,'disabled' => 'disabled'*/),
				//'#disabled' 		=> TRUE,
				'#options' 			=> array('' => t('Select Classification of the Factory')),
				'#required' 		=> TRUE,
				//'#value' 			=> '',
			);
			
			$form['factory_information']['inspected_by'] = array(
				'#prefix' 			=> '<div id="inspected_by_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('8. Inspected by'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'placeholder' => 'Inspected by','readonly' => 'readonly'),
				//'#value' 			=> '',
			);
			
			$form['factory_information']['person_during_inspection'] = array(
				'#prefix' 			=> '<div id="person_during_inspection_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('9. Responsible Person present during Inspection'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'placeholder' => 'Responsible Person present during Inspection'/*,'readonly' => 'readonly'*/),
				//'#value' 			=> '',
			);
			
			$form['factory_information']['nature_manufacturing'] = array(
				'#prefix' 			=> '<div id="nature_manufacturing_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('10. Nature of manufacturing process'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'Nature of manufacturing process','readonly' => 'readonly'),
				//'#value' 			=> '',
			);
			
			$form['power_details'] = array(
				'#type' 		=> 'fieldset',
				'#title' 		=> t('B. Power Details'),
				'#collapsible' 	=> TRUE, // Added
				'#collapsed' 	=> FALSE, // Added
				'#prefix' 		=> '<div id="reload_power_details">',
				'#suffix' 		=> '</div>',
			);
			
			$radios_options = array('power_generating_station'=>"Power generating station",'other'=>"Other");
			$form['power_details']['is_generating']= array(
				'#prefix' 			=> '<div class="row"><div id="is_generating_id"><div class="col-md-4 col-xs-4">',
				'#suffix'    		=> '</div></div>',
				'#type'		 		=> 'radios',
				'#attributes' 		=> array('class' => array('')),
				'#title'			=> t('Type of power generating station'),
				'#options'   		=> $radios_options,
				'#required'			=> TRUE,
				//'#value' 			=> '',
			);
			
			$form['power_details']['power_type'] = array(
				'#prefix' 				=> '<div id="power_type_id"><div class="col-md-4 col-xs-4">',
				'#suffix' 				=> '</div></div>',
				'#title'				=>	t('Unit of power'),
				'#type' 		 		=> 'select',
				'#options'	 			=> array('' => '-- Select --'),
				'#attributes' 			=> array('class'=>array('form-control')),
				'#required' 			=> TRUE,
				//'#value' 				=> '',
			);
			
			$form['power_details']['installed_power'] = array(
				'#prefix' 				=> '<div id="installed_power_id"><div class="col-md-4 col-xs-4">',
				'#suffix' 				=> '</div></div></div>',
				'#title'				=>	t('Power'),
				'#type' 				=> 'textfield',
				'#attributes' 			=>  array('class'=>array('form-control'),'placeholder' => 'Power'),
				'#required' 			=>  TRUE,
				//'#value' 				=> '',
			);
			
		}
		
		
		
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'admin/inspection-report-list', array(
				'html' => TRUE,
				'attributes' => array('class' => array('btn btn-outline-dark pull-left'))
			))
		);
		
		$form['factory_information_submit']['submit'] = array (
			'#prefix' 		=> '',  
			'#suffix' 		=> '',
			'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
			'#type' 		=> 'submit',
			'#value'		=> 'Save & Continue'
		);
		
		return $form;
		
	}
	
	
	function inspection_report_factory_info_validate($form, &$form_state) {
		
		$inspection_report_id = $form_state['values']['inspection_report_id'];
		$factory_id = $form_state['values']['factory_id'];
		
		if((!empty($inspection_report_id)) && ($inspection_report_id != 0)) {
			
			$get_factory_info = get_inspection_report_factory_information($inspection_report_id);
			
			if($get_factory_info->cafa_id != $factory_id) {
				
				$query_ir_fact_info  = db_select('fa_inspection_report', 'ir');
				$query_ir_fact_info  ->fields('ir',array());
				$query_ir_fact_info  ->condition('ir.id', $inspection_report_id, '!=');
				$result_ir_fact_info = $query_ir_fact_info->execute();
		
				if($result_ir_fact_info->rowCount() > 0) {
					while($data_ir_fact_info = $result_ir_fact_info->fetchObject()) {
						if($data_ir_fact_info->cafa_id == $factory_id) {
							form_set_error('Factory Name', t('Inspection Report for this Factory has been already submitted!!!'));		
						}
					}
				}
			}
			
		} else {
			
			$query_ir_fact_info  = db_select('fa_inspection_report', 'ir');
			$query_ir_fact_info  ->fields('ir',array());
			$result_ir_fact_info = $query_ir_fact_info->execute();
	
			if($result_ir_fact_info->rowCount() > 0) {
				while($data_ir_fact_info = $result_ir_fact_info->fetchObject()) {
					if($data_ir_fact_info->cafa_id == $factory_id) {
						form_set_error('Factory Name', t('Inspection Report for this Factory has been already submitted!!!'));		
					}
				}
			}
			
		}	
		
	}
	
	
	function inspection_report_factory_info_submit($form, &$form_state){
		//echo '<pre>'; print_r($form_state); die();
		
		global $base_root,$base_path,$user;
		
		$uid 							= $user->uid;
		
		$inspection_report_id = $form_state['values']['inspection_report_id'];
		
		$factory_id = $form_state['values']['factory_id'];
		
		$service_name = 'Inspection Report';
		$service_details = get_service_details($service_name);
		
		$val = $form_state['values'];
		
		if($factory_id != 0) {
			
			if($inspection_report_id == 0) {
			
				$inspection_report = array(
					'cafa_id'              			=> $factory_id,
					'factory_name'         			=> $val['factory_name'],
					'service_id' 					=> $service_details->id,
					'reference_number'     			=> $val['reference_number'],
					'factory_typeid'				=> $val['factory_typeid'],
					'registration_number'  			=> $val['registration_number'],
					'registration_date'    			=> trim(implode('-', array_reverse(explode('-', $val['registration_date'])))),
					'licence_number'       			=> $val['licence_number'],
					'licence_date'         			=> trim(implode('-', array_reverse(explode('-', $val['licence_date'])))),
					'classification_no'    			=> $val['classification_no'],
					'factory_classification_type'  	=> $val['factory_classification_type'],
					'pincode'	  		   			=> $val['pincode'],
					'state'         	   			=> $val['state'],
					'district'             			=> $val['district'],
					'subdivision'     	   			=> $val['subdivision'],
					'areatype'        	   			=> $val['areatype'],
					'block' 			   			=> $val['block'],
					'panchayat'    		   			=> $val['panchayat'],
					'policestation'        			=> $val['policestation'],
					'postoffice'          			=> $val['postoffice'],
					'factory_zone'         			=> $val['factory_zone'],
					'nearest_landmark'	   			=> $val['nearest_landmark'],
					'addrline'    		   			=> $val['addrline'],
					'building_plan_no'	   			=> $val['building_plan_no'],
					'building_plan_date'    		=> trim(implode('-', array_reverse(explode('-', $val['building_plan_date'])))),
					'inspected_by'    				=> $val['inspected_by'],
					'person_during_inspection'      => $val['person_during_inspection'],
					'nature_manufacturing'        	=> $val['nature_manufacturing'],
					'factory_sector_ownership_type' => $val['factory_sector_ownership_type'],
					'type_power_station'        	=> $val['is_generating'],
					'power_unit'        			=> $val['power_type'],
					'installed_power' 				=> $val['installed_power'],
					'uid' 				   			=> $uid,
					'full_application_status'   	=> 'In',
					'created_date'		   			=> date('Y-m-d'),
					
				);
				
				$inspection_report_ID = db_insert('fa_inspection_report')->fields($inspection_report)->execute();			
				
			} else {
				
				$inspection_report_ID = $inspection_report_id;
				
				$inspection_report = array(
					'cafa_id'              			=> $factory_id,
					'factory_name'         			=> $val['factory_name'],
					'service_id' 					=> $service_details->id,
					'reference_number'     			=> $val['reference_number'],
					'factory_typeid'				=> $val['factory_typeid'],
					'registration_number'  			=> $val['registration_number'],
					'registration_date'    			=> trim(implode('-', array_reverse(explode('-', $val['registration_date'])))),
					'licence_number'       			=> $val['licence_number'],
					'licence_date'         			=> trim(implode('-', array_reverse(explode('-', $val['licence_date'])))),
					'classification_no'    			=> $val['classification_no'],
					'factory_classification_type'  	=> $val['factory_classification_type'],
					'pincode'	  		   			=> $val['pincode'],
					'state'         	   			=> $val['state'],
					'district'             			=> $val['district'],
					'subdivision'     	   			=> $val['subdivision'],
					'areatype'        	   			=> $val['areatype'],
					'block' 			   			=> $val['block'],
					'panchayat'    		   			=> $val['panchayat'],
					'policestation'        			=> $val['policestation'],
					'postoffice'          			=> $val['postoffice'],
					'factory_zone'         			=> $val['factory_zone'],
					'nearest_landmark'	   			=> $val['nearest_landmark'],
					'addrline'    		   			=> $val['addrline'],
					'building_plan_no'	   			=> $val['building_plan_no'],
					'building_plan_date'    		=> trim(implode('-', array_reverse(explode('-', $val['building_plan_date'])))),
					'inspected_by'    				=> $val['inspected_by'],
					'person_during_inspection'      => $val['person_during_inspection'],
					'nature_manufacturing'        	=> $val['nature_manufacturing'],
					'factory_sector_ownership_type' => $val['factory_sector_ownership_type'],
					'type_power_station'        	=> $val['is_generating'],
					'power_unit'        			=> $val['power_type'],
					'installed_power' 				=> $val['installed_power'],
					'uid' 				   			=> $uid,
					'full_application_status'   	=> 'In',
					'modification_date'	   			=> date('Y-m-d H:i:s'),
					
				);
				
				db_update('fa_inspection_report')->fields($inspection_report)->condition('id', $inspection_report_ID, '=')->execute();	
					
			}
			
		} 
		
		//die($inspection_report_ID);
		drupal_goto('admin/inspection-report-factories/workers-details/'.encryption_decryption_fun('encrypt', $inspection_report_ID).'/'.encryption_decryption_fun('encrypt', $factory_id).'/'.encryption_decryption_fun('encrypt', NULL));
	  
		$form_state['rebuild'] = true;
		
		
	}