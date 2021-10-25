<?php

	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	function inspection_report_factory_info($form, &$form_state, $inspection_reportID = '', $factoryID = '') {
	
		global $user;
		$uid = $user->uid;
		
		$inspection_report_id = encryption_decryption_fun('decrypt', $inspection_reportID);
		//$factory_type_id = encryption_decryption_fun('decrypt', $factory_typeID);
		$factory_id = encryption_decryption_fun('decrypt', $factoryID);
		
	//variable declaration
		$service_id = $application_id = $RegistrationNo = $RegistrationDate = $LicenceNo = $LicenceDate = $ClassificationNo = $FactoryTypeid = $ReferenceNumber = $FactoryName = 	
		$factory_pincode = $factory_state = $factory_district = $factory_subdivision = $factory_areatype = $factory_block = $factory_panchayat = $factory_policestation = 
		$factory_postoffice = $nearest_landmark = $factory_addrline = $nature_manufacturing = $factory_classification_type = '';
		
		$occupier_name = $factory_pincodeoprmntadr_occupier = $factory_state_oprmntadr_occupier = $factory_district_oprmntadr_occupier = $factory_subdivision_oprmntadr_occupier = 
		$factory_areatype_oprmntadr_occupier = $factory_block_oprmntadr_occupier = $factory_panchayat_oprmntadr_occupier = $factory_policestation_oprmntadr_occupier = 
		$factory_postoffice_oprmntadr_occupier = $factory_addrline_oprmntadr_occupier = '';
		
		$manager_name = $factory_pincode_manager = $factory_state_manager = $factory_district_manager = $factory_sub_division_manager = $factory_area_type_manager =
		$factory_block_mun_cor_sez_not_manager = $factory_grm_ward_sector_not_manager = $factory_police_station_manager = $factory_post_office_manager = 
		$factory_adress_line1_manager = '';
	//end
	
		$value_factory_id = isset($form_state['values']['factory_id']) ? $form_state['values']['factory_id'] : $factory_id;
		
		if((!empty($value_factory_id)) && ($value_factory_id != 0)) {
			
			$query_ir_fact_info  = db_select('fa_inspection_report', 'ir');
			$query_ir_fact_info  ->fields('ir',array('id', 'cafa_id'));
			$query_ir_fact_info  ->condition('ir.id', $inspection_report_id, '=');
			$result_ir_fact_info = $query_ir_fact_info->execute();
			if($result_ir_fact_info->rowCount() > 0) {
				$data_ir_fact_info = $result_ir_fact_info->fetchObject();
			}
			
			if($data_ir_fact_info->cafa_id == $value_factory_id) {
				$get_factory_info = get_inspection_report_factory_information($inspection_report_id);
			}
			
			$get_registration_value = get_reg_lic_no($value_factory_id);
			$get_occupier_value = get_reg_factory_occupier($value_factory_id);
			$get_manager_value = get_reg_factory_manager($value_factory_id);
		
			$service_id     = $get_registration_value['service_id'];
			$application_id = $value_factory_id;
			$FactoryTypeid  = $get_registration_value['factory_typeid'];
			
			$power_details = fa_power_details($application_id, $service_id, $FactoryTypeid);
			$installed_power = $power_details[0]->installed_power;
			$power_unit = $power_details[0]->power_unit;
			$installed_power_hp = $power_details[0]->installed_power_hp;
			
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
			$factory_pincode        = $get_registration_value['pincode'];
			$factory_state          = $get_registration_value['state'];
			$factory_district 	    = $get_registration_value['district'];
			$factory_subdivision    = $get_registration_value['subdivision'];
			$factory_areatype       = $get_registration_value['areatype'];
			$factory_block          = $get_registration_value['block'];
			$factory_panchayat      = $get_registration_value['panchayat'];
			$factory_policestation  = $get_registration_value['policestation'];
			$factory_postoffice     = $get_registration_value['postoffice'];
			$nearest_landmark       = $get_registration_value['nearest_landmark'];
			$factory_addrline		= $get_registration_value['addrline'];
			
		//for occupier
			if(!empty($get_occupier_value)) {
				$occupier_name = $get_occupier_value['name_occupier'];
				$factory_pincodeoprmntadr_occupier        = $get_occupier_value['pincodeoprmntadr'];
				$factory_state_oprmntadr_occupier          = $get_occupier_value['state_oprmntadr'];
				$factory_district_oprmntadr_occupier 	    = $get_occupier_value['district_oprmntadr'];
				$factory_subdivision_oprmntadr_occupier    = $get_occupier_value['subdivision_oprmntadr'];
				$factory_areatype_oprmntadr_occupier       = $get_occupier_value['areatype_oprmntadr'];
				$factory_block_oprmntadr_occupier          = $get_occupier_value['block_oprmntadr'];
				$factory_panchayat_oprmntadr_occupier      = $get_occupier_value['panchayat_oprmntadr'];
				$factory_policestation_oprmntadr_occupier  = $get_occupier_value['policestation_oprmntadr'];
				$factory_postoffice_oprmntadr_occupier     = $get_occupier_value['postoffice_oprmntadr'];
				$factory_addrline_oprmntadr_occupier		= $get_occupier_value['addrline_oprmntadr'];
			}
			
		//for manager
			if(!empty($get_manager_value)) {
				$manager_name = $get_manager_value['name_manager'];
				$factory_pincode_manager        = $get_manager_value['pincode_manager'];
				$factory_state_manager          = $get_manager_value['state_manager'];
				$factory_district_manager 	    = $get_manager_value['district_manager'];
				$factory_sub_division_manager    = $get_manager_value['sub_division_manager'];
				$factory_area_type_manager       = $get_manager_value['area_type_manager'];
				$factory_block_mun_cor_sez_not_manager          = $get_manager_value['block_mun_cor_sez_not_manager'];
				$factory_grm_ward_sector_not_manager      = $get_manager_value['grm_ward_sector_not_manager'];
				$factory_police_station_manager  = $get_manager_value['police_station_manager'];
				$factory_post_office_manager     = $get_manager_value['post_office_manager'];
				$factory_adress_line1_manager		= $get_manager_value['adress_line1_manager'];
			}
			
			
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
			
			
			$ir_occupier_name 						= $get_factory_info->occupier_name;
			$ir_pincodeoprmntadr_occupier         	= $get_factory_info->pincodeoprmntadr;
			$ir_state_oprmntadr_occupier          	= $get_factory_info->state_oprmntadr;
			$ir_district_oprmntadr_occupier 	  	= $get_factory_info->district_oprmntadr;
			$ir_subdivision_oprmntadr_occupier    	= $get_factory_info->subdivision_oprmntadr;
			$ir_areatype_oprmntadr_occupier       	= $get_factory_info->areatype_oprmntadr;
			$ir_block_oprmntadr_occupier          	= $get_factory_info->block_oprmntadr;
			$ir_panchayat_oprmntadr_occupier      	= $get_factory_info->panchayat_oprmntadr;
			$ir_policestation_oprmntadr_occupier  	= $get_factory_info->policestation_oprmntadr;
			$ir_postoffice_oprmntadr_occupier     	= $get_factory_info->postoffice_oprmntadr;
			$ir_addrline_oprmntadr_occupier		  	= $get_factory_info->addrline_oprmntadr;
			
			
			$ir_manager_name 						= $get_factory_info->manager_name;
			$ir_pincode_manager        				= $get_factory_info->pincode_manager;
			$ir_state_manager          				= $get_factory_info->state_manager;
			$ir_district_manager 	    			= $get_factory_info->district_manager;
			$ir_sub_division_manager    			= $get_factory_info->sub_division_manager;
			$ir_area_type_manager       			= $get_factory_info->area_type_manager;
			$ir_block_mun_cor_sez_not_manager       = $get_factory_info->block_mun_cor_sez_not_manager;
			$ir_grm_ward_sector_not_manager      	= $get_factory_info->grm_ward_sector_not_manager;
			$ir_police_station_manager  			= $get_factory_info->police_station_manager;
			$ir_post_office_manager     			= $get_factory_info->post_office_manager;
			$ir_adress_line1_manager				= $get_factory_info->adress_line1_manager;
			
			$ir_person_during_inspection  			= $get_factory_info->person_during_inspection;
			$ir_nature_manufacturing     			= $get_factory_info->nature_manufacturing;
			$ir_installed_load						= $get_factory_info->installed_load;
			
		//end
			
		}
		
		
		$form = array();
		$form['factory_information'] = array(
			'#type' => 'fieldset',
			'#title' => t('Factory Information'),
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
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6"><label class="select label-block">',
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
			'#select2' => array(
				'width' => '500',
				//'placeholder' => '- Select -',
				'allowClear' => TRUE
        	)
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
				'#prefix' 			=> '<div id="factory_name_id"><div class="col-md-7 col-xs-12"><label class="input label-block">',
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
			
			
			$factory_pincode_value = !empty($ir_pincode) ? $ir_pincode : $factory_pincode;
			$value_pincode = isset($form_state['values']['pincode']) ? $form_state['values']['pincode'] : '';
			unset($form_state['input']['pincode']);
			$form['factory_information']['pincode']       = array(
				'#prefix' 				=> '<div id="pincode_id"><div class="col-md-4 col-xs-12"><label class="select label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Pincode'),
				'#autocomplete_path' 	=> 'pinautocomplete',
				'#id' 				 	=> 'pincode_autocomplete',
				'#maxlength' 		 	=> 6,
				'#title' 			 	=> t('(i) Pincode'),
				'#default_value' 	 	=> $factory_pincode_value,
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
				'#element_validate' 	=> array('element_validate_numeric_positive'),
				'#ajax' 				=> array(
													'effect' 	=> 'fade',
													'callback' 	=> 'get_ajax_factory_address_load',
													'progress' 	=> array(
													 'type' 	=> 'throbber',
													'message' 	=> t('loading')
					)
				)
			);
			
			if(!empty($value_pincode)) {
				
				$query = db_select('fa_all_india_pin_code', 'p')
									->fields('p', array('districtname', 'statename', 'pincode', 'district_code', 'state_code', 'po_name'))
									->condition('p.pincode', trim($value_pincode), '=');
				
				$result = $query->execute();
				if ($result->rowcount() > 0) {
					$final       = $result->fetchAssoc();
					$pincode_v   = $value_pincode;
					$state_v     = $final['state_code'];
					$district_v  = $final['district_code'];
					$post_office = $final['po_name'];
				}
			}
			
			
			$factory_state_value = !empty($ir_state) ? $ir_state : $factory_state;
			$value_state = isset($form_state['values']['state']) ? $form_state['values']['state'] : '';	
			if(!empty($state_v)) {
				$form['factory_information']['state'] = array(
					'#title' 		=> '(ii) State',
					'#type' 		=> 'select',
					'#id' 			=> 'state_name',
					'#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
					'#disabled' 	=> TRUE,
					'#options' 		=> get_all_state($state_v),
					'#value' 		=> !empty($state_v) ? $state_v : '',
					'#required' 	=> TRUE,
					'#prefix' 		=> '<div id="ld_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
					'#suffix' 		=> '</label></div></div>',
					'#ajax' 				=> array(
													'effect' 	=> 'fade',
													'callback' 	=> 'get_ajax_factory_address_load',
													'progress' 	=> array(
													 'type' 	=> 'throbber',
													'message' 	=> t('loading')
						)
					)
				);
			} else {
				if(!empty($factory_state_value)) {
					unset($form_state['input']['state']);
					$form['factory_information']['state'] = array(
						'#title' 		=> '(iii) State',
						'#type' 		=> 'select',
						'#id' 			=> 'state_name',
						'#disabled'	 	=> TRUE,
						'#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
						'#required' 	=> TRUE,
						'#options' 		=> get_all_state($factory_state_value),
						'#value' 		=> $factory_state_value,
						'#prefix' 		=> '<div id="ld_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
						'#suffix' 		=> '</label></div></div>',
						'#ajax' 				=> array(
														'effect' 	=> 'fade',
														'callback' 	=> 'get_ajax_factory_address_load',
														'progress' 	=> array(
														 'type' 	=> 'throbber',
														'message' 	=> t('loading')
							)
						)
					);
				} else {
					$form['factory_information']['state'] = array(
						'#title' => '(iii) State',
						'#type' => 'select',
						'#id' => 'state_name',
						'#disabled' => TRUE,
						'#attributes' => array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
						'#required' => TRUE,
						'#options' => array(
							'' => t('Select State')
						),
						'#prefix' => '<div id="ld_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
						'#suffix' => '</label></div></div>',
						'#ajax' 				=> array(
														'effect' 	=> 'fade',
														'callback' 	=> 'get_ajax_factory_address_load',
														'progress' 	=> array(
														 'type' 	=> 'throbber',
														'message' 	=> t('loading')
							)
						)
					);	
				}
			}
			
			
			$factory_district_value = !empty($ir_district) ? $ir_district : $factory_district;
			$value_district = isset($form_state['values']['district']) ? $form_state['values']['district'] : '';
			if(!empty($state_v)) {
				$form['factory_information']['district'] = array(
					'#title' => '(iv) District',
					'#type' => 'select',
					'#id' => 'district_name',
					'#disabled' => TRUE,
					'#attributes' => array('class' => array(''),'placeholder' => 'District','disabled' => 'disabled'),
					'#options' => get_district_by_id($state_v),
					'#value' => !empty($district_v) ? $district_v : '',
					'#required' => TRUE,
					'#prefix' => '<div id="ld_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
					'#suffix' => '</label></div></div>',
					'#ajax' => array(
						'event' => 'change',
						'effect' => 'fade',
						'callback' => 'get_ajax_factory_address_load',
						'progress' => array(
							'type' => 'throbber',
							'message' => t('loading')
						)
					)
				);
			} else {
				if(!empty($factory_district_value)) {
					unset($form_state['input']['district']);
					$form['factory_information']['district'] = array(
						'#title' => '(iii) District',
						'#type' => 'select',
						'#id' => 'district_name',
						'#disabled' => TRUE,
						'#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
						'#options' => get_district_by_id($factory_state_value),
						'#value' 	=> $factory_district_value,
						'#required' => TRUE,
						'#prefix' => '<div id="ld_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
						'#suffix' => '</label></div></div>',
						'#ajax' => array(
							'event' => 'change',
							'effect' => 'fade',
							'callback' => 'get_ajax_factory_address_load',
							'progress' => array(
								'type' => 'throbber',
								'message' => t('loading')
							)
						)
					);
				} else {
					$form['factory_information']['district'] = array(
						'#title' => '(iv) District',
						'#type' => 'select',
						'#id' => 'district_name',
						'#disabled' => TRUE,
						'#attributes' => array('class' => array(''),'placeholder' => 'District','disabled' => 'disabled'),
						'#required' => TRUE,
						'#options' => array(
							'' => t('Select District')
						),
						'#prefix' => '<div id="ld_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
						'#suffix' => '</label></div></div>',
						'#ajax' => array(
							'event' => 'change',
							'effect' => 'fade',
							'callback' => 'get_ajax_factory_address_load',
							'progress' => array(
								'type' => 'throbber',
								'message' => t('loading')
							)
						)
					);	
				}
			}
			
			
			$factory_subdivision_value = !empty($ir_subdivision) ? $ir_subdivision : $factory_subdivision;
			$value_subdivision = isset($form_state['values']['subdivision']) ? $form_state['values']['subdivision'] : '';
			if(!empty($district_v) && !empty($state_v)) {
				$form['factory_information']['subdivision'] = array(
					'#title' => '(v) Sub-Division',
					'#type' => 'select',
					'#attributes' => array(
						'class' => array(
							''
						),
						'placeholder' => 'Sub Division',
					),
					'#options' => common_custom_user_subdivisionlist_list_new($district_v),
					'#required' => TRUE,
					'#default_value' => '',
					'#prefix' => '<div id="ld_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
					'#suffix' => '</label></div></div>',
					'#ajax' => array(
						'event' => 'change',
						'effect' => 'fade',
						'callback' => 'get_ajax_factory_address_load',
						'progress' => array(
							'type' => 'throbber',
							'message' => t('loading')
						)
					)
				);
			} else {
				if(!empty($factory_subdivision_value)) {
					unset($form_state['input']['subdivision']);	
					$form['factory_information']['subdivision'] = array(
						'#title' => '(iv) Sub-Division',
						'#type' => 'select',
						'#disabled' => TRUE,
						'#attributes' => array('class' => array(''),'placeholder' => 'Sub Division','disabled' => 'disabled'),
						'#options' => common_custom_user_subdivisionlist_list_new($factory_district_value),
						'#required' => TRUE,
						'#value' 	=> $factory_subdivision_value,
						'#prefix' => '<div id="ld_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
						'#suffix' => '</label></div></div>',
						'#ajax' => array(
							'event' => 'change',
							'effect' => 'fade',
							'callback' => 'get_ajax_factory_address_load',
							'progress' => array(
								'type' => 'throbber',
								'message' => t('loading')
							)
						)
					);
				} else {
					$form['factory_information']['subdivision'] = array(
						'#title' => '(v) Sub-Division',
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
						'#prefix' => '<div id="ld_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
						'#suffix' => '</label></div></div>',
						'#ajax' => array(
							'event' => 'change',
							'effect' => 'fade',
							'callback' => 'get_ajax_factory_address_load',
							'progress' => array(
								'type' => 'throbber',
								'message' => t('loading')
							)
						)
					);	
				}
			}
			
			
			$factory_areatype_value = !empty($ir_areatype) ? $ir_areatype : $factory_areatype;
			$value_areatype = isset($form_state['values']['areatype']) ? $form_state['values']['areatype'] : '';
			if(!empty($value_district) && !empty($value_state) && !empty($value_subdivision)) {
				$form['factory_information']['areatype'] = array(
					'#title' => '(vi) Area Type',
					'#type' => 'select',
					'#attributes' => array(
						'class' => array(
							''
						),
						'placeholder' => 'Area Type',
					),
					'#options' => common_custom_user_areatype_list_new($value_district, $value_subdivision),
					'#required' => TRUE,
					'#default_value' => '',
					'#prefix' => '<div id="ld_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
					'#suffix' => '</label></div></div>',
					'#ajax' => array(
						'event' => 'change',
						'effect' => 'fade',
						'callback' => 'get_ajax_factory_address_load',
						'progress' => array(
							'type' => 'throbber',
							'message' => t('loading')
						)
					)
				);
			} else {
				if(!empty($factory_areatype_value)) {
					unset($form_state['input']['areatype']);
					$form['factory_information']['areatype'] = array(
						'#title' => '(v) Area Type',
						'#type' => 'select',
						'#disabled' => TRUE,
						'#attributes' => array('class' => array(''),'placeholder' => 'Area Type','disabled' => 'disabled'),
						'#options' => common_custom_user_areatype_list_new($factory_district_value, $factory_subdivision_value),
						'#required' => TRUE,
						'#value' 	=> $factory_areatype_value,
						'#prefix' => '<div id="ld_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
						'#suffix' => '</label></div></div>',
						'#ajax' => array(
							'event' => 'change',
							'effect' => 'fade',
							'callback' => 'get_ajax_factory_address_load',
							'progress' => array(
								'type' => 'throbber',
								'message' => t('loading')
							)
						)
					);
				} else {
					$form['factory_information']['areatype'] = array(
						'#title' => '(vi) Area Type',
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
						'#required' => TRUE,
						'#prefix' => '<div id="ld_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
						'#suffix' => '</label></div></div>',
						'#ajax' => array(
							'event' => 'change',
							'effect' => 'fade',
							'callback' => 'get_ajax_factory_address_load',
							'progress' => array(
								'type' => 'throbber',
								'message' => t('loading')
							)
						)
					);	
				}
			}
			
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
				'#prefix' 		=> '<div id="ld_empareatype_name_replace"><div class="col-md-6"><label class="select label-block">',
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
				'#prefix' => '<div id="ld_emp_vill_ward_replace"><div class="col-md-6"><label class="select label-block">',
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
	
			unset($form_state['input']['building_plan_no']);
			$form['factory_information']['building_plan_no'] = array(
				'#prefix' 			=> '<div id="building_plan_no_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('3. (i) Factory Building Plan No.'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'placeholder' => 'Factory Building Plan No. (Approval from CIF)'),
				'#default_value' 	=> !empty($ir_building_plan_no) ? $ir_building_plan_no : '',
				'#element_validate' => array('element_validate_numeric_positive'),
			);
			unset($form_state['input']['building_plan_date']);
			$form['factory_information']['building_plan_date'] = array(
				'#prefix' 			=> '<div id="building_plan_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(ii) Factory Building Plan Date'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array('form-control datepicker_cls'),'placeholder' => 'Factory Building Plan Date (Approval from CIF)'),
				'#default_value' 	=> !empty($ir_building_plan_date) ? $ir_building_plan_date : '',
				//'#value' 			=> !empty($ir_registration_date) ? implode('/', array_reverse(explode('-', $ir_registration_date))) : $RegistrationDate,
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
			$form['factory_information']['licence_date'] = array(
				'#prefix' 			=> '<div id="licence_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(ii) Licence Date'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'readonly' => 'readonly'),
				'#value' 			=> !empty($ir_licence_date) ? $ir_licence_date : $LicenceDate,
				//'#value' 			=> !empty($ir_licence_date) ? implode('/', array_reverse(explode('-', $ir_licence_date))) : $LicenceDate,
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
			$form['factory_information']['registration_date'] = array(
				'#prefix' 			=> '<div id="registration_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(iv) Registration Date'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'readonly' => 'readonly'),
				'#value' 			=> !empty($ir_registration_date) ? $ir_registration_date : $RegistrationDate,
				//'#value' 			=> !empty($ir_registration_date) ? implode('/', array_reverse(explode('-', $ir_registration_date))) : $RegistrationDate,
				'#element_validate' => array('element_validate_date'),
			);
			
			$value_factory_type = !empty($ir_factory_typeid) ? $ir_factory_typeid : $FactoryTypeid;
			$form['factory_information']['factory_typeid'] = array(
				'#prefix' 			=> '<div id="factory_typeid_id"><div class="col-md-4 col-xs-12" ><label class="select label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('5. Category of the Factory'),
				'#type' 			=> 'select',
				'#attributes' 		=> array('class' => array(''),'disabled' => 'disabled'),
				'#disabled' 		=> TRUE,
				'#options' 			=> get_factory_type(NULL),
				'#required' 		=> TRUE,
				'#value' 			=> $value_factory_type,
			);
			
			unset($form_state['input']['classification_no']);
			$form['factory_information']['classification_no'] = array(
				'#prefix' 			=> '<div id="classification_no_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('6. (i) Classification No.'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'placeholder' => 'Classification No.'),
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
				'#title' 			=> t('7. Inspected by'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'placeholder' => 'Inspected by','readonly' => 'readonly'),
				'#value' 			=> !empty($ir_inspected_by) ? $ir_inspected_by : $inspected_by,
				'#element_validate' => array('element_validate_alphabatic_fullstop'),
			);
			
			$form['factory_information']['occupier_details_heading'] = array(
				'#prefix' 				=> '<div class="col-md-12 col-xs-12"><h4><b>8. Occupier\'s Details</b></h4>',
				'#suffix' 				=> '</div>',
			);
			
			/*$form['factory_information']['occupier_details_update'] = array(
				'#prefix' 				=> '<div id="occupier_details_update_id"><div class="col-md-5 col-xs-12">'.$occupier_details_update_link,
				'#suffix' 				=> '</div></div>',
			);*/
			
			/*if(!empty($occupier_name)) {
				$form['factory_information']['occupier_name'] = array(
					'#prefix' 				=> '<div id="occupier_name_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
					'#suffix' 				=> '</label></div></div>',
					'#attributes' 			=> array('class' => array(),'placeholder' => 'Occupier Name','readonly' => 'readonly'),
					'#title' 			 	=> t('(xx) Occupier Name'),
					'#value' 	 	        => !empty($occupier_name) ? $occupier_name : '',
					'#required' 			=> TRUE,
					'#type' 				=> 'textfield',
				);
			} else {*/
			
			unset($form_state['input']['occupier_name']);
			$form['factory_information']['occupier_name'] = array(
				'#prefix' 				=> '<div id="occupier_name_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array(),'placeholder' => 'Occupier Name'/*,'readonly' => 'readonly'*/),
				'#title' 			 	=> t('(i) Occupier Name'),
				'#default_value' 	 	=> !empty($ir_occupier_name) ? $ir_occupier_name : $occupier_name,
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
				'#element_validate' => array('element_validate_alphabatic_fullstop'),
			);	
			//}
			
	//occupier address section
			
			$pincode_occupier_val = !empty($ir_pincodeoprmntadr_occupier) ? $ir_pincodeoprmntadr_occupier : $factory_pincodeoprmntadr_occupier;
			
			$form['factory_information']['pincodeoprmntadr']       = array(
				'#prefix' 				=> '<div id="pincodeoprmntadr_occupier_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Pincode','readonly' => 'readonly'),
				'#autocomplete_path' 	=> 'pinautocomplete',
				'#id' 				 	=> 'pincode_autocomplete_occupier',
				'#maxlength' 		 	=> 6,
				'#title' 			 	=> t('(ii) Pincode'),
				'#value' 	 			=> $pincode_occupier_val,
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
				'#element_validate' 	=> array('element_validate_numeric_positive'),
			);
			
			$state_occupier_val = !empty($ir_state_oprmntadr_occupier) ? $ir_state_oprmntadr_occupier : $factory_state_oprmntadr_occupier;
			
			$form['factory_information']['state_oprmntadr'] = array(
				'#title' 		=> '(iii) State',
				'#type' 		=> 'select',
				'#id' 			=> 'state_occupier_name',
				'#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
				'#disabled' 	=> TRUE,
				'#options' 		=> get_all_state($state_occupier_val),
				'#value' 	 	=> $state_occupier_val,
				'#required' 	=> TRUE,
				'#prefix' 		=> '<div id="state_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
			
			$district_occupier_val = !empty($ir_district_oprmntadr_occupier) ? $ir_district_oprmntadr_occupier : $factory_district_oprmntadr_occupier;
			
			$form['factory_information']['district_oprmntadr'] = array(
				'#title' => '(iv) District',
				'#type' => 'select',
				'#id' => 'district_occupier_name',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
				'#options' => get_district_by_id($state_occupier_val),
				'#value' 	=> $district_occupier_val,
				'#required' => TRUE,
				'#prefix' => '<div id="district_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			$sub_division_occupier_val = !empty($ir_subdivision_oprmntadr_occupier) ? $ir_subdivision_oprmntadr_occupier : $factory_subdivision_oprmntadr_occupier;
			
			$form['factory_information']['subdivision_oprmntadr'] = array(
				'#title' => '(v) Sub-Division',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'Sub Division','disabled' => 'disabled'),
				'#options' => common_custom_user_subdivisionlist_list_new($district_occupier_val),
				'#required' => TRUE,
				'#value' 	=> $sub_division_occupier_val,
				'#prefix' => '<div id="subdivision_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			$area_type_occupier_val = !empty($ir_areatype_oprmntadr_occupier) ? $ir_areatype_oprmntadr_occupier : $factory_areatype_oprmntadr_occupier;
			
			$form['factory_information']['areatype_oprmntadr'] = array(
				'#title' => '(vi) Area Type',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'Area Type','disabled' => 'disabled'),
				'#options' => common_custom_user_areatype_list_new($district_occupier_val, $sub_division_occupier_val),
				'#required' => TRUE,
				'#value' 	=> $area_type_occupier_val,
				'#prefix' => '<div id="areatype_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			if ($area_type_occupier_val == 'B') {
				$areatype_name_occupier = 'Block';
			} elseif ($area_type_occupier_val == 'M') {
				$areatype_name_occupier = 'Municipality';
			} elseif ($area_type_occupier_val == 'C') {
				$areatype_name_occupier = 'Corporation';
			} elseif ($area_type_occupier_val == 'S') {
				$areatype_name_occupier = 'SEZ';
			} elseif ($area_type_occupier_val == 'N') {
				$areatype_name_occupier = 'Notified Area';
			}
			
			$block_occupier_val = !empty($ir_block_oprmntadr_occupier) ? $ir_block_oprmntadr_occupier : $factory_block_oprmntadr_occupier;
					
			$form['factory_information']['block_oprmntadr'] = array(
				'#title' 		=> '(vii) '. $areatype_name_occupier,
				'#type'         => 'select',
				'#disabled' => TRUE,
				'#attributes'   => array('class' => array(''),'placeholder' => 'Block','disabled' => 'disabled'),
				'#options' 		=> common_custom_user_block_list_new($sub_division_occupier_val, $area_type_occupier_val),
				'#required' 	=> TRUE,
				'#value' 	    => $block_occupier_val,
				'#prefix' 		=> '<div id="block_oprmntadr_occupier_id_replace"><div class="col-md-6"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
			
			if ($area_type_occupier_val == 'B') {
				$area_name_occupier = 'Gram Panchayat';
				$area_code_occupier = 'V';
			} elseif ($area_type_occupier_val == 'M') {
				$area_name_occupier = 'Ward';
				$area_code_occupier = 'W';
			} elseif ($area_type_occupier_val == 'C') {
				$area_name_occupier = 'Ward';
				$area_code_occupier = 'C';
			} elseif ($area_type_occupier_val == 'S') {
				$area_name_occupier = 'Sector';
				$area_code_occupier = 'S';
			} elseif ($area_type_occupier_val == 'N') {
				$area_name_occupier = 'Notified Area';
				$area_code_occupier = 'N';
			}
				
			$form['factory_information']['panchayat_oprmntadr'] = array(
				'#title' => '(viii) '.$area_name_occupier,
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'panchayat','disabled' => 'disabled'),
				'#options' => common_custom_user_villward_list_new($block_occupier_val, $area_code_occupier),
				'#value' 	    => !empty($ir_panchayat_oprmntadr_occupier) ? $ir_panchayat_oprmntadr_occupier : $factory_panchayat_oprmntadr_occupier,
				'#prefix' => '<div id="panchayat_oprmntadr_occupier_id_replace"><div class="col-md-6"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
				'#required' => TRUE,
			);
			
			$form['factory_information']['policestation_oprmntadr'] = array(
				'#title' => '(ix) Police Station',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array( ''),'placeholder' => 'Police Station','disabled' => 'disabled'),
				'#options' => common_custom_user_ps_list_new($district_occupier_val),
				'#required' => TRUE,
				'#value' 	    => !empty($ir_policestation_oprmntadr_occupier) ? $ir_policestation_oprmntadr_occupier : $factory_policestation_oprmntadr_occupier,
				'#prefix' => '<div id="policestation_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['postoffice_oprmntadr'] = array(
				'#title' => '(x) Post Office',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''), 'placeholder' => 'Post Office','disabled' => 'disabled'),
				'#options' => common_custom_post_office_list_new($pincode_occupier_val),
				'#value' 	    => !empty($ir_postoffice_oprmntadr_occupier) ? $ir_postoffice_oprmntadr_occupier : $factory_postoffice_oprmntadr_occupier,
				'#required' => TRUE,
				'#prefix' => '<div id="postoffice_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['addrline_oprmntadr'] = array(
				'#prefix' => '<div id="addrline_oprmntadr_occupier_id"><div class="col-md-12"><label class="textarea label-block">',
				'#suffix' => '</label></div></div>',
				'#title' => '(xi) Address',
				'#rows' => 3,
				'#type' => 'textarea',
				'#required' => TRUE,
				'#value' 	    => !empty($ir_addrline_oprmntadr_occupier) ? $ir_addrline_oprmntadr_occupier : $factory_addrline_oprmntadr_occupier,
				'#attributes' => array('class' => array(''),'placeholder' => 'Address Line','readonly' => 'readonly'),
				'#element_validate' => array('element_validate_streetaddress'), 
			);
				
	//occupier address section end
	
			$form['factory_information']['manager_details_heading'] = array(
				'#prefix' 				=> '<div class="col-md-12 col-xs-12"><h4><b>9. Manager\'s Details</b></h4>',
				'#suffix' 				=> '</div>',
			);
			
			/*$form['factory_information']['manager_details_update'] = array(
				'#prefix' 				=> '<div id="manager_details_update_id"><div class="col-md-5 col-xs-12">'.$manager_details_update_link,
				'#suffix' 				=> '</div></div>',
			);*/
				
			/*if(!empty($manager_name)) {
				$form['factory_information']['manager_name'] = array(
					'#prefix' 				=> '<div id="manager_name_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
					'#suffix' 				=> '</label></div></div>',
					'#attributes' 			=> array('class' => array(),'placeholder' => 'Manager Name','readonly' => 'readonly'),
					'#title' 			 	=> t('(xxxi) Manager Name'),
					'#value' 	 	        => !empty($manager_name) ? $manager_name : '',
					'#required' 			=> TRUE,
					'#type' 				=> 'textfield',
				);
			} else {*/
			
			unset($form_state['input']['manager_name']);
			$form['factory_information']['manager_name'] = array(
				'#prefix' 				=> '<div id="manager_name_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array(),'placeholder' => 'Manager Name'/*,'readonly' => 'readonly'*/),
				'#title' 			 	=> t('(i) Manager Name'),
				'#default_value' 	 	=> !empty($ir_manager_name) ? $ir_manager_name : $manager_name,
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
				'#element_validate' => array('element_validate_alphabatic_fullstop'),
			);	
			//}
			
	//manager address section
			
			$pincode_manager_val = !empty($ir_pincode_manager) ? $ir_pincode_manager : $factory_pincode_manager;
			
			$form['factory_information']['pincode_manager']       = array(
				'#prefix' 				=> '<div id="pincode_manager_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Pincode','readonly' => 'readonly'),
				'#autocomplete_path' 	=> 'pinautocomplete',
				'#id' 				 	=> 'pincode_autocomplete_manager',
				'#maxlength' 		 	=> 6,
				'#title' 			 	=> t('(ii) Pincode'),
				'#value' 	 			=> $pincode_manager_val,
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
				'#element_validate' 	=> array('element_validate_numeric_positive'),
			);
			
			$state_manager_val = !empty($ir_state_manager) ? $ir_state_manager : $factory_state_manager;
			
			$form['factory_information']['state_manager'] = array(
				'#title' 		=> '(iii) State',
				'#type' 		=> 'select',
				'#id' 			=> 'state_manager_name',
				'#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
				'#disabled' 	=> TRUE,
				'#options' 		=> get_all_state($state_manager_val),
				'#value' 	 	=> $state_manager_val,
				'#required' 	=> TRUE,
				'#prefix' 		=> '<div id="state_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
			
			$district_manager_val = !empty($ir_district_manager) ? $ir_district_manager : $factory_district_manager;
			
			$form['factory_information']['district_manager'] = array(
				'#title' => '(iv) District',
				'#type' => 'select',
				'#id' => 'district_manager_name',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
				'#options' => get_district_by_id($state_manager_val),
				'#value' 	=> $district_manager_val,
				'#required' => TRUE,
				'#prefix' => '<div id="district_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			$sub_division_manager_val = !empty($ir_sub_division_manager) ? $ir_sub_division_manager : $factory_sub_division_manager;
			
			$form['factory_information']['sub_division_manager'] = array(

				'#title' => '(v) Sub-Division',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'Sub Division','disabled' => 'disabled'),
				'#options' => common_custom_user_subdivisionlist_list_new($district_manager_val),
				'#required' => TRUE,
				'#value' 	=> $sub_division_manager_val,
				'#prefix' => '<div id="sub_division_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			$area_type_manager_val = !empty($ir_area_type_manager) ? $ir_area_type_manager : $factory_area_type_manager;
			
			$form['factory_information']['area_type_manager'] = array(
				'#title' => '(vi) Area Type',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'Area Type','disabled' => 'disabled'),
				'#options' => common_custom_user_areatype_list_new($district_manager_val, $sub_division_manager_val),
				'#required' => TRUE,
				'#value' 	=> $area_type_manager_val,
				'#prefix' => '<div id="area_type_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			if ($area_type_manager_val == 'B') {
				$areatype_name_manager = 'Block';
			} elseif ($area_type_manager_val == 'M') {
				$areatype_name_manager = 'Municipality';
			} elseif ($area_type_manager_val == 'C') {
				$areatype_name_manager = 'Corporation';
			} elseif ($area_type_manager_val == 'S') {
				$areatype_name_manager = 'SEZ';
			} elseif ($area_type_manager_val == 'N') {
				$areatype_name_manager = 'Notified Area';
			}
			
			$block_mun_cor_sez_not_manager_val = !empty($ir_block_mun_cor_sez_not_manager) ? $ir_block_mun_cor_sez_not_manager : $factory_block_mun_cor_sez_not_manager;
					
			$form['factory_information']['block_mun_cor_sez_not_manager'] = array(
				'#title' 		=> '(vii) '. $areatype_name_manager,
				'#type'         => 'select',
				'#disabled' => TRUE,
				'#attributes'   => array('class' => array(''),'placeholder' => 'Block','disabled' => 'disabled'),
				'#options' 		=> common_custom_user_block_list_new($sub_division_manager_val, $area_type_manager_val),
				'#required' 	=> TRUE,
				'#value' 	    => $block_mun_cor_sez_not_manager_val,
				'#prefix' 		=> '<div id="block_mun_cor_sez_not_manager_id_replace"><div class="col-md-6"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
			
			if ($area_type_manager_val == 'B') {
				$area_name_manager = 'Gram Panchayat';
				$area_code_manager = 'V';
			} elseif ($area_type_manager_val == 'M') {
				$area_name_manager = 'Ward';
				$area_code_manager = 'W';
			} elseif ($area_type_manager_val == 'C') {
				$area_name_manager = 'Ward';
				$area_code_manager = 'C';
			} elseif ($area_type_manager_val == 'S') {
				$area_name_manager = 'Sector';
				$area_code_manager = 'S';
			} elseif ($area_type_manager_val == 'N') {
				$area_name_manager = 'Notified Area';
				$area_code_manager = 'N';
			}
				
			$form['factory_information']['grm_ward_sector_not_manager'] = array(
				'#title' => '(viii) '.$area_name_manager,
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'panchayat','disabled' => 'disabled'),
				'#options' => common_custom_user_villward_list_new($block_mun_cor_sez_not_manager_val, $area_code_manager),
				'#value' 	    => !empty($ir_grm_ward_sector_not_manager) ? $ir_grm_ward_sector_not_manager : $factory_grm_ward_sector_not_manager,
				'#prefix' => '<div id="grm_ward_sector_not_manager_id_replace"><div class="col-md-6"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
				'#required' => TRUE,
			);
				
			$form['factory_information']['police_station_manager'] = array(
				'#title' => '(ix) Police Station',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array( ''),'placeholder' => 'Police Station','disabled' => 'disabled'),
				'#options' => common_custom_user_ps_list_new($district_manager_val),
				'#required' => TRUE,
				'#value' 	    => !empty($ir_police_station_manager) ? $ir_police_station_manager : $factory_police_station_manager,
				'#prefix' => '<div id="police_station_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['post_office_manager'] = array(
				'#title' => '(x) Post Office',
				'#type' => 'select',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array(''), 'placeholder' => 'Post Office','disabled' => 'disabled'),
				'#options' => common_custom_post_office_list_new($pincode_manager_val),
				'#value' 	    => !empty($ir_post_office_manager) ? $ir_post_office_manager : $factory_post_office_manager,
				'#required' => TRUE,
				'#prefix' => '<div id="post_office_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
            
            $form['factory_information']['adress_line1_manager'] = array(
				'#prefix' => '<div id="adress_line1_manager_id"><div class="col-md-12"><label class="textarea label-block">',
				'#suffix' => '</label></div></div>',
				'#title' => '(xi) Address',
				'#rows' => 3,
				'#type' => 'textarea',
				'#required' => TRUE,
				'#value' 	    => !empty($ir_adress_line1_manager) ? $ir_adress_line1_manager : $factory_adress_line1_manager,
				'#attributes' => array('class' => array(''),'placeholder' => 'Address Line','readonly' => 'readonly'),
				'#element_validate' => array('element_validate_streetaddress'), 
			);
			
	//manager address section end
			
			unset($form_state['input']['person_during_inspection']);
			$form['factory_information']['person_during_inspection'] = array(
				'#prefix' 			=> '<div id="person_during_inspection_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('10. Responsible Person present during Inspection:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'placeholder' => 'Responsible Person present during Inspection'/*,'readonly' => 'readonly'*/),
				'#default_value' 	=> !empty($ir_person_during_inspection) ? $ir_person_during_inspection : '',
				'#element_validate' => array('element_validate_alphabatic_fullstop'),
			);
			
			$form['factory_information']['nature_manufacturing'] = array(
				'#prefix' 			=> '<div id="nature_manufacturing_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('11. Nature of manufacturing process'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array('charField'),'readonly' => 'readonly'),
				'#value' 			=> !empty($ir_nature_manufacturing) ? $ir_nature_manufacturing : $nature_manufacturing,
				'#element_validate' => array('element_validate_hyphen_fullstop_ampersand'),
			);
			
			$installed_load = $installed_power.' '.$power_unit;
			unset($form_state['input']['installed_load']);
			$form['factory_information']['installed_load'] = array(
				'#prefix' 			=> '<div id="installed_load_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div></div>',
				'#title' 			=> t('12. Installed load / Stand by power'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array('numeric_positive'),'placeholder' => 'Installed load / Stand by power'/*,'readonly' => 'readonly'*/),
				'#default_value' 	=> !empty($ir_installed_load) ? $ir_installed_load : $installed_load,
				'#element_validate' => array('element_validate_alphanumeric'),
			);
			
			
		} else {
			
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
				'#prefix' 			=> '<div id="factory_name_id"><div class="col-md-7 col-xs-12"><label class="input label-block">',
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
				'#title' => '(vi) Block / Municipality / Corporation / Notified Area / SEZ',
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
				'#prefix' => '<div id="ld_empareatype_name_replace"><div class="col-md-6"><label class="select label-block" title="Block / Municipality / Corporation / Notified Area / SEZ">',
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
				'#prefix' => '<div id="ld_emp_vill_ward_replace"><div class="col-md-6"><label class="select label-block">',
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
			
			$form['factory_information']['factory_typeid'] = array(
				'#prefix' 			=> '<div id="factory_typeid_id"><div class="col-md-4 col-xs-12" ><label class="select label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('5. Category of the Factory'),
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
				'#title' 			=> t('6. (i) Classification No.'),
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
				'#title' 			=> t('7. Inspected by'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'placeholder' => 'Inspected by','readonly' => 'readonly'),
				//'#value' 			=> '',
			);
			
			$form['factory_information']['occupier_details_heading'] = array(
				'#prefix' 				=> '<div class="col-md-12 col-xs-12"><h4><b>8. Occupier\'s Details</b></h4>',
				'#suffix' 				=> '</div>',
			);
			
			/*$form['factory_information']['occupier_details_update'] = array(
				'#prefix' 				=> '<div id="occupier_details_update_id"><div class="col-md-5 col-xs-12">'.$occupier_details_update_link,
				'#suffix' 				=> '</div></div>',
			);*/
			
			$form['factory_information']['occupier_name'] = array(
				'#prefix' 				=> '<div id="occupier_name_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array(),'placeholder' => 'Occupier Name'),
				'#title' 			 	=> t('(i) Occupier Name'),
				//'#value' 				=> '',
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
			);
				
		//occupier address section
			
			$form['factory_information']['pincodeoprmntadr']       = array(
				'#prefix' 				=> '<div id="pincodeoprmntadr_occupier_id"><div class="col-md-4 col-xs-12"><label class="select label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Pincode'),
				'#maxlength' 		 	=> 6,
				'#title' 			 	=> t('(ii) Pincode'),
				//'#value' 	 	        => '',
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
			);
			
			$form['factory_information']['state_oprmntadr'] = array(
				'#title' 		=> '(iii) State',
				'#type' 		=> 'select',
				'#id' 			=> 'state_occupier_name',
				'#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
				'#disabled' 	=> TRUE,
				'#options' => array('' => t('Select State')),
				//'#value' 	 	=> '',
				'#required' 	=> TRUE,
				'#prefix' 		=> '<div id="state_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
			
			$form['factory_information']['district_oprmntadr'] = array(
				'#title' => '(iv) District',
				'#type' => 'select',
				'#id' => 'district_occupier_name',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
				'#options' => array(
					'' => t('Select District')
				),
				//'#value' 	=> '',
				'#required' => TRUE,
				'#prefix' => '<div id="district_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
				
			$form['factory_information']['subdivision_oprmntadr'] = array(
				'#title' => '(v) Sub-Division',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'Sub Division'),
				'#options' => array(
					'' => t('Select Sub-Division')
				),
				'#required' => TRUE,
				//'#value' 	=> '',
				'#prefix' => '<div id="subdivision_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			$form['factory_information']['areatype_oprmntadr'] = array(
				'#title' => '(vi) Area Type',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'Area Type'),
				'#options' => array(
					'0' => t('Select Area Type')
				),
				'#required' => TRUE,
				//'#value' 	=> '',
				'#prefix' => '<div id="areatype_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
				
			$form['factory_information']['block_oprmntadr'] = array(
				'#title' 		=> '(vii) Block / Municipality / Corporation / Notified Area / SEZ',
				'#type'         => 'select',
				'#attributes'   => array('class' => array(''),'placeholder' => 'Block'),
				'#options' => array(
					'0' => t('Select Block / Municipality / Corporation / Notified Area / SEZ')
				),
				'#required' 	=> TRUE,
				//'#value' 	    => '',
				'#prefix' 		=> '<div id="block_oprmntadr_occupier_id_replace"><div class="col-md-6"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
				
			$form['factory_information']['panchayat_oprmntadr'] = array(
				'#title' => '(viii) Gram Panchayat / Ward / Sector',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'panchayat'),
				'#options' => array(
					'0' => t('Select Gram Panchayat / Ward / Sector / Notified Area')
				),
				//'#value' 	    => '',
				'#prefix' => '<div id="panchayat_oprmntadr_occupier_id_replace"><div class="col-md-6"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
				'#required' => TRUE,
			);
			
			$form['factory_information']['policestation_oprmntadr'] = array(
				'#title' => '(ix) Police Station',
				'#type' => 'select',
				'#attributes' => array('class' => array( ''),'placeholder' => 'Police Station'),
				'#options' => array(
					'0' => t('Select Police Station')
				),
				'#required' => TRUE,
				//'#value' 	    => '',
				'#prefix' => '<div id="policestation_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['postoffice_oprmntadr'] = array(
				'#title' => '(x) Post Office',
				'#type' => 'select',
				'#attributes' => array('class' => array(''), 'placeholder' => 'Post Office'),
				'#options' => array(
					'0' => t('Select Post Office')
				),
				//'#value' 	    => '',
				'#required' => TRUE,
				'#prefix' => '<div id="postoffice_oprmntadr_occupier_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['addrline_oprmntadr'] = array(
				'#prefix' => '<div id="addrline_oprmntadr_occupier_id"><div class="col-md-12"><label class="textarea label-block">',
				'#suffix' => '</label></div></div>',
				'#title' => '(xi) Address',
				'#rows' => 3,
				'#type' => 'textarea',
				'#required' => TRUE,
				//'#value' 	    => '',
				'#attributes' => array('class' => array(''),'placeholder' => 'Address Line'),
			);			
				
		//occupier address section end
		
			$form['factory_information']['manager_details_heading'] = array(
				'#prefix' 				=> '<div class="col-md-12 col-xs-12"><h4><b>9. Manager\'s Details</b></h4>',
				'#suffix' 				=> '</div>',
			);
			
			/*$form['factory_information']['manager_details_update'] = array(
				'#prefix' 				=> '<div id="manager_details_update_id"><div class="col-md-5 col-xs-12">'.$manager_details_update_link,
				'#suffix' 				=> '</div></div>',
			);*/
			
			$form['factory_information']['manager_name'] = array(
				'#prefix' 				=> '<div id="manager_name_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array(),'placeholder' => 'Manager Name'),
				'#title' 			 	=> t('(i) Manager Name'),
				//'#value' 				=> '',
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
			);
				
		//manager address section
				
			$form['factory_information']['pincode_manager']       = array(
				'#prefix' 				=> '<div id="pincode_manager_id"><div class="col-md-4 col-xs-12"><label class="select label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Pincode'),
				'#maxlength' 		 	=> 6,
				'#title' 			 	=> t('(ii) Pincode'),
				//'#value' 	 	        => '',
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
			);
			
			$form['factory_information']['state_manager'] = array(
				'#title' 		=> '(iii) State',
				'#type' 		=> 'select',
				'#id' 			=> 'state_manager_name',
				'#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
				'#disabled' 	=> TRUE,
				'#options' => array('' => t('Select State')),
				//'#value' 	 	=> '',
				'#required' 	=> TRUE,
				'#prefix' 		=> '<div id="state_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
			
			$form['factory_information']['district_manager'] = array(
				'#title' => '(iv) District',
				'#type' => 'select',
				'#id' => 'district_manager_name',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
				'#options' => array(
					'' => t('Select District')
				),
				//'#value' 	=> '',
				'#required' => TRUE,
				'#prefix' => '<div id="district_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
				
			$form['factory_information']['sub_division_manager'] = array(
				'#title' => '(v) Sub-Division',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'Sub Division'),
				'#options' => array(
					'' => t('Select Sub-Division')
				),
				'#required' => TRUE,
				//'#value' 	=> '',
				'#prefix' => '<div id="sub_division_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
			
			$form['factory_information']['area_type_manager'] = array(
				'#title' => '(vi) Area Type',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'Area Type'),
				'#options' => array(
					'0' => t('Select Area Type')
				),
				'#required' => TRUE,
				//'#value' 	=> '',
				'#prefix' => '<div id="area_type_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
				
			$form['factory_information']['block_mun_cor_sez_not_manager'] = array(
				'#title' 		=> '(vii) Block / Municipality / Corporation / Notified Area / SEZ',
				'#type'         => 'select',
				'#attributes'   => array('class' => array(''),'placeholder' => 'Block'),
				'#options' => array(
					'0' => t('Select Block / Municipality / Corporation / Notified Area / SEZ')
				),
				'#required' 	=> TRUE,
				//'#value' 	    => '',
				'#prefix' 		=> '<div id="block_mun_cor_sez_not_manager_id_replace"><div class="col-md-6"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
				
			$form['factory_information']['grm_ward_sector_not_manager'] = array(
				'#title' => '(viii) Gram Panchayat / Ward / Sector',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'panchayat'),
				'#options' => array(
					'0' => t('Select Gram Panchayat / Ward / Sector / Notified Area')
				),
				//'#value' 	    => '',
				'#prefix' => '<div id="grm_ward_sector_not_manager_id_replace"><div class="col-md-6"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
				'#required' => TRUE,
			);
			
			$form['factory_information']['police_station_manager'] = array(
				'#title' => '(ix) Police Station',
				'#type' => 'select',
				'#attributes' => array('class' => array( ''),'placeholder' => 'Police Station'),
				'#options' => array(
					'0' => t('Select Police Station')
				),
				'#required' => TRUE,
				//'#value' 	    => '',
				'#prefix' => '<div id="police_station_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['post_office_manager'] = array(
				'#title' => '(x) Post Office',
				'#type' => 'select',
				'#attributes' => array('class' => array(''), 'placeholder' => 'Post Office'),
				'#options' => array(
					'0' => t('Select Post Office')
				),
				//'#value' 	    => '',
				'#required' => TRUE,
				'#prefix' => '<div id="post_office_manager_id_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
			
			$form['factory_information']['adress_line1_manager'] = array(
				'#prefix' => '<div id="adress_line1_manager_id"><div class="col-md-12"><label class="textarea label-block">',
				'#suffix' => '</label></div></div>',
				'#title' => '(xi) Address',
				'#rows' => 3,
				'#type' => 'textarea',
				'#required' => TRUE,
				//'#value' 	    => '',
				'#attributes' => array('class' => array(''),'placeholder' => 'Address Line'),
			);
				
	//manager address section end
			
			$form['factory_information']['person_during_inspection'] = array(
				'#prefix' 			=> '<div id="person_during_inspection_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('10. Responsible Person present during Inspection'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array(''),'placeholder' => 'Responsible Person present during Inspection'/*,'readonly' => 'readonly'*/),
				//'#value' 			=> '',
			);
			
			$form['factory_information']['nature_manufacturing'] = array(
				'#prefix' 			=> '<div id="nature_manufacturing_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('11. Nature of manufacturing process'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' => array('class' => array(''),'placeholder' => 'Nature of manufacturing process','readonly' => 'readonly'),
				//'#value' 			=> '',
			);
			
			$form['factory_information']['installed_load'] = array(
				'#prefix' 			=> '<div id="installed_load_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div></div>',
				'#title' 			=> t('12. Installed load / Stand by power'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array('numeric_positive'),'placeholder' => 'Installed load / Stand by power'/*,'readonly' => 'readonly'*/),
				//'#value' 			=> '',
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
					'registration_date'    			=> $val['registration_date'],
					'licence_number'       			=> $val['licence_number'],
					'licence_date'         			=> $val['licence_date'],
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
					'building_plan_date'    		=> $val['building_plan_date'],
					'inspected_by'    				=> $val['inspected_by'],
					'occupier_name'   				=> $val['occupier_name'],
					'pincodeoprmntadr'				=> $val['pincodeoprmntadr'],
					'state_oprmntadr'				=> $val['state_oprmntadr'],
					'district_oprmntadr'			=> $val['district_oprmntadr'],
					'subdivision_oprmntadr'			=> $val['subdivision_oprmntadr'],
					'areatype_oprmntadr'			=> $val['areatype_oprmntadr'],
					'block_oprmntadr'				=> $val['block_oprmntadr'],
					'panchayat_oprmntadr'			=> $val['panchayat_oprmntadr'],
					'policestation_oprmntadr'		=> $val['policestation_oprmntadr'],
					'postoffice_oprmntadr'			=> $val['postoffice_oprmntadr'],
					'addrline_oprmntadr'			=> $val['addrline_oprmntadr'],
					'manager_name'   				=> $val['manager_name'],
					'pincode_manager'				=> $val['pincode_manager'],
					'state_manager'					=> $val['state_manager'],
					'district_manager'				=> $val['district_manager'],
					'sub_division_manager'			=> $val['sub_division_manager'],
					'area_type_manager'				=> $val['area_type_manager'],
					'block_mun_cor_sez_not_manager'	=> $val['block_mun_cor_sez_not_manager'],
					'grm_ward_sector_not_manager'	=> $val['grm_ward_sector_not_manager'],
					'police_station_manager'		=> $val['police_station_manager'],
					'post_office_manager'			=> $val['post_office_manager'],
					'adress_line1_manager'			=> $val['adress_line1_manager'],
					'person_during_inspection'      => $val['person_during_inspection'],
					'nature_manufacturing'        	=> $val['nature_manufacturing'],
					'installed_load'        		=> $val['installed_load'],
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
					'registration_date'    			=> $val['registration_date'],
					'licence_number'       			=> $val['licence_number'],
					'licence_date'         			=> $val['licence_date'],
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
					'building_plan_date'    		=> $val['building_plan_date'],
					'inspected_by'    				=> $val['inspected_by'],
					'occupier_name'   				=> $val['occupier_name'],
					'pincodeoprmntadr'				=> $val['pincodeoprmntadr'],
					'state_oprmntadr'				=> $val['state_oprmntadr'],
					'district_oprmntadr'			=> $val['district_oprmntadr'],
					'subdivision_oprmntadr'			=> $val['subdivision_oprmntadr'],
					'areatype_oprmntadr'			=> $val['areatype_oprmntadr'],
					'block_oprmntadr'				=> $val['block_oprmntadr'],
					'panchayat_oprmntadr'			=> $val['panchayat_oprmntadr'],
					'policestation_oprmntadr'		=> $val['policestation_oprmntadr'],
					'postoffice_oprmntadr'			=> $val['postoffice_oprmntadr'],
					'addrline_oprmntadr'			=> $val['addrline_oprmntadr'],
					'manager_name'   				=> $val['manager_name'],
					'pincode_manager'				=> $val['pincode_manager'],
					'state_manager'					=> $val['state_manager'],
					'district_manager'				=> $val['district_manager'],
					'sub_division_manager'			=> $val['sub_division_manager'],
					'area_type_manager'				=> $val['area_type_manager'],
					'block_mun_cor_sez_not_manager'	=> $val['block_mun_cor_sez_not_manager'],
					'grm_ward_sector_not_manager'	=> $val['grm_ward_sector_not_manager'],
					'police_station_manager'		=> $val['police_station_manager'],
					'post_office_manager'			=> $val['post_office_manager'],
					'adress_line1_manager'			=> $val['adress_line1_manager'],
					'person_during_inspection'      => $val['person_during_inspection'],
					'nature_manufacturing'        	=> $val['nature_manufacturing'],
					'installed_load'        		=> $val['installed_load'],
					'uid' 				   			=> $uid,
					'full_application_status'   	=> 'In',
					'modification_date'	   			=> date('Y-m-d H:i:s'),
					
				);
				
				db_update('fa_inspection_report')->fields($inspection_report)->condition('id', $inspection_report_ID, '=')->execute();	
					
			}
			
		} 
		
		//die($annual_return_ID);
		drupal_goto('admin/inspection-report-factories/workers-details/'.encryption_decryption_fun('encrypt', $inspection_report_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));
	  
		$form_state['rebuild'] = true;
		
		
	}