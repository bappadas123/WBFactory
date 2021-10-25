<?php

	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	function inspection_report_manager_details($form, &$form_state, $inspection_reportID = '', $factoryID = '', $param = '') {
	
		global $user;
		$uid = $user->uid;
		
		$inspection_report_id = encryption_decryption_fun('decrypt', $inspection_reportID);
		//$factory_type_id = encryption_decryption_fun('decrypt', $factory_typeID);
		$factory_id = encryption_decryption_fun('decrypt', $factoryID);
		
		if(empty($inspection_report_id) || $inspection_report_id == '') {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Occupier Details first.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('admin/inspection-report-factories/occupier-details/'.$inspection_reportID.'/'.$factoryID.'/'.encryption_decryption_fun('encrypt', NULL)) ;
		}
		
	//variable declaration
		$manager_name = $factory_pincode_manager = $factory_state_manager = $factory_district_manager = $factory_sub_division_manager = $factory_area_type_manager =
		$factory_block_mun_cor_sez_not_manager = $factory_grm_ward_sector_not_manager = $factory_police_station_manager = $factory_post_office_manager = 
		$factory_adress_line1_manager = $manager_telephone = $manager_fax_no = $manager_email_id = $manager_mobile ='';
	//end
			
		$get_manager_value = get_reg_factory_manager($factory_id);
		
		if($inspection_report_id != 0) {
			$get_factory_manager_info = get_inspection_report_manager_information($inspection_report_id);	
		}
		
	//for manager
		if(!empty($get_manager_value)) {
			$manager_name 								= $get_manager_value['name_manager'];
			$factory_pincode_manager        			= $get_manager_value['pincode_manager'];
			$factory_state_manager          			= $get_manager_value['state_manager'];
			$factory_district_manager 	    			= $get_manager_value['district_manager'];
			$factory_sub_division_manager    			= $get_manager_value['sub_division_manager'];
			$factory_area_type_manager       			= $get_manager_value['area_type_manager'];
			$factory_block_mun_cor_sez_not_manager		= $get_manager_value['block_mun_cor_sez_not_manager'];
			$factory_grm_ward_sector_not_manager      	= $get_manager_value['grm_ward_sector_not_manager'];
			$factory_police_station_manager  			= $get_manager_value['police_station_manager'];
			$factory_post_office_manager     			= $get_manager_value['post_office_manager'];
			$factory_adress_line1_manager				= $get_manager_value['adress_line1_manager'];
			$manager_telephone  						= $get_manager_value['manager_telephone'];
			$manager_fax_no     						= $get_manager_value['manager_fax'];
			$manager_email_id							= $get_manager_value['manager_email'];
			$manager_mobile								= $get_manager_value['manager_phone'];
		}
		
		
	//data from inspection report table
		
		if(!empty($get_factory_manager_info)) {
			$ir_manager_name 						= $get_factory_manager_info->manager_name;
			$ir_pincode_manager        				= $get_factory_manager_info->pincode_manager;
			$ir_state_manager          				= $get_factory_manager_info->state_manager;
			$ir_district_manager 	    			= $get_factory_manager_info->district_manager;
			$ir_sub_division_manager    			= $get_factory_manager_info->sub_division_manager;
			$ir_area_type_manager       			= $get_factory_manager_info->area_type_manager;
			$ir_block_mun_cor_sez_not_manager       = $get_factory_manager_info->block_mun_cor_sez_not_manager;
			$ir_grm_ward_sector_not_manager      	= $get_factory_manager_info->grm_ward_sector_not_manager;
			$ir_police_station_manager  			= $get_factory_manager_info->police_station_manager;
			$ir_post_office_manager     			= $get_factory_manager_info->post_office_manager;
			$ir_adress_line1_manager				= $get_factory_manager_info->adress_line1_manager;
			$ir_manager_telephone      				= $get_factory_manager_info->manager_telephone;
			$ir_manager_fax_no  					= $get_factory_manager_info->manager_fax_no;
			$ir_manager_email_id     				= $get_factory_manager_info->manager_email_id;
			$ir_manager_mobile		  				= $get_factory_manager_info->manager_mobile;			
		}
		
		
		$form = array();
		
		$form['manager_details'] = array(
			'#type' => 'fieldset',
			'#title' => t('F. Manager Details'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => FALSE // Added 
		);
		
		$form['inspection_report_id'] = array(
				'#prefix' 			=> '<div id="inspection_report_id"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#type' 			=> 'hidden',
				'#default_value' 	=> !empty($inspection_report_id) ? $inspection_report_id : '',
		);
		
		$form['factory_id'] = array(
				'#prefix' 			=> '<div id="factory_type_id"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#type' 			=> 'hidden',
				'#default_value' 	=> $factory_id,
		);
		
		
		$form['manager_details']['manager_name'] = array(
			'#prefix' 				=> '<div class="row"><div id="manager_name_id"><div class="col-md-6 col-xs-4"><label class="input label-block">',
			'#suffix' 				=> '</label></div></div>',
			'#attributes' 			=> array('class' => array(),'placeholder' => 'Manager Name'),
			'#title' 			 	=> t('(i) Manager Name'),
			'#default_value' 	 	=> !empty($ir_manager_name) ? $ir_manager_name : $manager_name,
			'#required' 			=> TRUE,
			'#type' 				=> 'textfield',
			'#element_validate' 	=> array('element_validate_alphabatic_fullstop'),
		);
		
	//manager address section
		
		$pincode_manager_val = !empty($ir_pincode_manager) ? $ir_pincode_manager : $factory_pincode_manager;
		$value_pincode_manager = isset($form_state['values']['pincode_manager']) ? $form_state['values']['pincode_manager'] : $pincode_manager_val;
		$form['manager_details']['pincode_manager']       = array(
			'#prefix' 				=> '<div id="pincode_manager_id"><div class="col-md-4 col-xs-4"><label class="input label-block">',
			'#suffix' 				=> '</label></div></div>',
			'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Pincode'),
			'#autocomplete_path' 	=> 'pinautocomplete',
			'#id' 				 	=> 'pincode_autocomplete_manager',
			'#maxlength' 		 	=> 6,
			'#title' 			 	=> t('(ii) Pincode'),
			'#default_value' 	 	=> $pincode_manager_val,
			'#required' 			=> TRUE,
			'#type' 				=> 'textfield',
			'#element_validate' 	=> array('element_validate_numeric_positive'),
			'#ajax' 				=> array(
                                                    'effect' 	=> 'fade',
                                                    'callback' 	=> 'get_ajax_manager_details_load_ir',
                                                    'progress' 	=> array(
                                                     'type' 	=> 'throbber',
                                                    'message' 	=> t('loading')
                    )
             )
		);
		
		if(!empty($value_pincode_manager)) {
				
			$query_pin_manager = db_select('fa_all_india_pin_code', 'p')
											->fields('p', array('districtname', 'statename', 'pincode', 'district_code', 'state_code', 'po_name'))
											->condition('p.pincode', trim($value_pincode_manager), '=');
			
			$result_pin_manager = $query_pin_manager->execute();
			if($result_pin_manager->rowcount() > 0) {
				$final_pin_manager   = $result_pin_manager->fetchAssoc();
				$pincode_v_manager   = $value_pincode_manager;
				$state_v_manager     = $final_pin_manager['state_code'];
				$district_v_manager  = $final_pin_manager['district_code'];
				$post_office_manager = $final_pin_manager['po_name'];
			}
		}
		
		$state_manager_val = !empty($ir_state_manager) ? $ir_state_manager : $factory_state_manager;
		$value_state_manager = isset($form_state['values']['state_manager']) ? $form_state['values']['state_manager'] : $state_manager_val;
		if(!empty($state_v_manager)) {
			$form['manager_details']['state_manager'] = array(
				'#title' 		=> '(iii) State',
				'#type' 		=> 'select',
				'#id' 			=> 'state_manager_name',
				'#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
				'#disabled' 	=> TRUE,
				'#options' 		=> get_all_state($state_v_manager),
				'#default_value'=> !empty($state_v_manager) ? $state_v_manager : $state_manager_val,
				'#required' 	=> TRUE,
				'#prefix' 		=> '<div id="state_manager_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
				'#ajax' 				=> array(
														'effect' 	=> 'fade',
														'callback' 	=> 'get_ajax_manager_details_load_ir',
														'progress' 	=> array(
														 'type' 	=> 'throbber',
														'message' 	=> t('loading')
						)
				 )
			);
		} else {
			$form['manager_details']['state_manager'] = array(
				'#title' 		=> '(iii) State',
				'#type' 		=> 'select',
				'#id' 			=> 'state_manager_name',
				'#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
				'#disabled' 	=> TRUE,
				'#options' => array(
					'' => t('Select State')
				),
				//'#value' 	 	=> '',
				'#required' 	=> TRUE,
				'#prefix' 		=> '<div id="state_manager_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
		}
		
		$district_manager_val = !empty($ir_district_manager) ? $ir_district_manager : $factory_district_manager;
		$value_district_manager = isset($form_state['values']['district_manager']) ? $form_state['values']['district_manager'] : $district_manager_val;
		if(!empty($state_v_manager)) {
			$form['manager_details']['district_manager'] = array(
				'#title' => '(iv) District',
				'#type' => 'select',
				'#id' => 'district_manager_name',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
				'#options' => get_district_by_id($state_v_manager),
				'#value' 	=> !empty($district_v_manager) ? $district_v_manager : $district_manager_val,
				'#required' => TRUE,
				'#prefix' => '<div id="district_manager_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
				'#ajax' 				=> array(
															'effect' 	=> 'fade',
															'callback' 	=> 'get_ajax_manager_details_load_ir',
															'progress' 	=> array(
															 'type' 	=> 'throbber',
															'message' 	=> t('loading')
							)
				 )
			);
		} else {
			$form['manager_details']['district_manager'] = array(
				'#title' => '(iv) District',
				'#type' => 'select',
				'#id' => 'district_manager_upd',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
				'#options' => array(
					'' => t('Select District')
				),
				//'#value' 	 	=> '',
				'#required' => TRUE,
				'#prefix' => '<div id="district_manager_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
		}
		
		$sub_division_manager_val = !empty($ir_sub_division_manager) ? $ir_sub_division_manager : $factory_sub_division_manager;
		$value_sub_division_manager = isset($form_state['values']['sub_division_manager']) ? $form_state['values']['sub_division_manager'] : $sub_division_manager_val;
		if(!empty($district_v_manager) && !empty($state_v_manager)) {
			$form['manager_details']['sub_division_manager'] = array(
				'#title' => '(v) Sub-Division',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'Sub Division'),
				'#options' => common_custom_user_subdivisionlist_list_new($district_v_manager),
				'#required' => TRUE,
				'#default_value' 	=> $sub_division_manager_val,
				'#prefix' => '<div id="sub_division_manager_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
				'#ajax' 				=> array(
															'effect' 	=> 'fade',
															'callback' 	=> 'get_ajax_manager_details_load_ir',
															'progress' 	=> array(
															 'type' 	=> 'throbber',
															'message' 	=> t('loading')
							)
				 )
			);
		} else {
			$form['manager_details']['sub_division_manager'] = array(
				'#title' => '(v) Sub-Division',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'Sub Division'),
				'#options' => array(
					'' => t('Select Sub-Division')
				),
				'#required' => TRUE,
				'#prefix' => '<div id="sub_division_manager_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);	
		}
		
		$area_type_manager_val = !empty($ir_area_type_manager) ? $ir_area_type_manager : $factory_area_type_manager;
		$value_area_type_manager = isset($form_state['values']['area_type_manager']) ? $form_state['values']['area_type_manager'] : $area_type_manager_val;
		if(!empty($value_district_manager) && !empty($value_state_manager) && !empty($value_sub_division_manager)) {
			$form['manager_details']['area_type_manager'] = array(
				'#title' => '(vi) Area Type',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'Area Type'),
				'#options' => common_custom_user_areatype_list_new($value_district_manager, $value_sub_division_manager),
				'#required' => TRUE,
				'#default_value' 	=> $area_type_manager_val,
				'#prefix' => '<div id="area_type_manager_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
				'#ajax' 				=> array(
																'effect' 	=> 'fade',
																'callback' 	=> 'get_ajax_manager_details_load_ir',
																'progress' 	=> array(
																 'type' 	=> 'throbber',
																'message' 	=> t('loading')
								)
				 )
			);
		} else {
			$form['manager_details']['area_type_manager'] = array(
				'#title' => '(vi) Area Type',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'Area Type'),
				'#options' => array(
					'0' => t('Select Area Type')
				),
				'#required' => TRUE,
				'#prefix' => '<div id="area_type_manager_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);	
		}
		
		if(!empty($value_district_manager) && !empty($value_state_manager) && !empty($value_sub_division_manager) && !empty($value_area_type_manager)) {
			if($value_area_type_manager == 'B') {
				$areatype_name_manager = 'Block';
			} elseif($value_area_type_manager == 'M') {
				$areatype_name_manager = 'Municipality';
			} elseif($value_area_type_manager == 'C') {
				$areatype_name_manager = 'Corporation';
			} elseif($value_area_type_manager == 'S') {
				$areatype_name_manager = 'SEZ';
			} elseif($value_area_type_manager == 'N') {
				$areatype_name_manager = 'Notified Area';
			}
		
			$block_mun_cor_sez_not_manager_val = !empty($ir_block_mun_cor_sez_not_manager) ? $ir_block_mun_cor_sez_not_manager : $factory_block_mun_cor_sez_not_manager;
			$value_block_mun_cor_sez_not_manager = isset($form_state['values']['block_mun_cor_sez_not_manager']) ? $form_state['values']['block_mun_cor_sez_not_manager'] : $block_mun_cor_sez_not_manager_val;		
			$form['manager_details']['block_mun_cor_sez_not_manager'] = array(
				'#title' 		=> '(vii) '. $areatype_name_manager,
				'#type'         => 'select',
				'#attributes'   => array('class' => array(''),'placeholder' => 'Block'),
				'#options' 		=> common_custom_user_block_list_new($value_sub_division_manager, $value_area_type_manager),
				'#required' 	=> TRUE,
				'#default_value'=> $block_mun_cor_sez_not_manager_val,
				'#prefix' 		=> '<div id="block_mun_cor_sez_not_manager_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
				'#ajax' 		=> array(
											'effect' 	=> 'fade',
											'callback' 	=> 'get_ajax_manager_details_load_ir',
											'progress' 	=> array(
											 'type' 	=> 'throbber',
											'message' 	=> t('loading')
								)
				 )
			);
		} else {
			$form['manager_details']['block_mun_cor_sez_not_manager'] = array(
				'#title' 		=> '(vii) Block / Municipality / Corporation / Notified Area / SEZ',
				'#type'         => 'select',
				'#attributes'   => array('class' => array(''),'placeholder' => 'Block'),
				'#options' => array(
					'0' => t('Select Block / Municipality / Corporation / Notified Area / SEZ')
				),
				'#required' 	=> TRUE,
				'#prefix' 		=> '<div id="block_mun_cor_sez_not_manager_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);	
		}
		
		if(!empty($value_district_manager) && !empty($value_sub_division_manager) && !empty($value_area_type_manager) && !empty($value_block_mun_cor_sez_not_manager) && !empty($value_state_manager)) {
			
			if ($value_area_type_manager == 'B') {
				$areatype_name_manager = 'Gram Panchayat';
				$area_code_manager = 'V';
			} elseif($value_area_type_manager == 'M') {
				$areatype_name_manager = 'Ward';
				$area_code_manager = 'W';
			} elseif($value_area_type_manager == 'C') {
				$areatype_name_manager = 'Ward';
				$area_code_manager = 'C';
			} elseif($value_area_type_manager == 'S') {
				$areatype_name_manager = 'Sector';
				$area_code_manager = 'S';
			} elseif($value_area_type_manager == 'N') {
				$areatype_name_manager = 'Notified Area';
				$area_code_manager = 'N';
			}
			
			$grm_ward_sector_not_manager_val = !empty($ir_grm_ward_sector_not_manager) ? $ir_grm_ward_sector_not_manager : $factory_grm_ward_sector_not_manager;
			$value_grm_ward_sector_not_manager = isset($form_state['values']['grm_ward_sector_not_manager']) ? $form_state['values']['grm_ward_sector_not_manager'] : $grm_ward_sector_not_manager_val;
			$form['manager_details']['grm_ward_sector_not_manager'] = array(
				'#title' => '(viii) '.$areatype_name_manager,
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'panchayat'),
				'#options' => common_custom_user_villward_list_new($value_block_mun_cor_sez_not_manager, $area_code_manager),
				'#default_value' 	    => $grm_ward_sector_not_manager_val,
				'#prefix' => '<div id="grm_ward_sector_not_manager_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
				'#required' => TRUE,
				'#ajax' 		=> array(
											'effect' 	=> 'fade',
											'callback' 	=> 'get_ajax_manager_details_load_ir',
											'progress' 	=> array(
											 'type' 	=> 'throbber',
											'message' 	=> t('loading')
								)
				 )
			);
		} else {
			$form['manager_details']['grm_ward_sector_not_manager'] = array(
				'#title' => '(viii) Gram Panchayat / Ward / Sector',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'panchayat'),
				'#options' => array(
					'0' => t('Select Gram Panchayat / Ward / Sector / Notified Area')
				),
				'#prefix' => '<div id="grm_ward_sector_not_manager_id_replace"><div class="col-md-6 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
				'#required' => TRUE,
			);	
		}
		
		if(!empty($value_district_manager)) {
			$form['manager_details']['police_station_manager'] = array(
				'#title' => '(ix) Police Station',
				'#type' => 'select',
				'#attributes' => array('class' => array( ''),'placeholder' => 'Police Station'),
				'#options' => common_custom_user_ps_list_new($value_district_manager),
				'#required' => TRUE,
				'#default_value' 	    => !empty($ir_police_station_manager) ? $ir_police_station_manager : $factory_police_station_manager,
				'#prefix' => '<div id="police_station_manager_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
		} else {
			$form['manager_details']['police_station_manager'] = array(
				'#title' => '(ix) Police Station',
				'#type' => 'select',
				'#attributes' => array('class' => array( ''),'placeholder' => 'Police Station'),
				'#options' => array(
					'0' => t('Select Police Station')
				),
				'#required' => TRUE,
				'#prefix' => '<div id="police_station_manager_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);	
		}
		
		if(!empty($value_pincode_manager)) {
			$form['manager_details']['post_office_manager'] = array(
				'#title' => '(x) Post Office',
				'#type' => 'select',
				'#attributes' => array('class' => array(''), 'placeholder' => 'Post Office'),
				'#options' => common_custom_post_office_list_new($value_pincode_manager),
				'#default_value' 	    => !empty($ir_post_office_manager) ? $ir_post_office_manager : $factory_post_office_manager,
				'#required' => TRUE,
				'#prefix' => '<div id="post_office_manager_id_replace"><div class="col-md-4 col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
		} else {
			$form['manager_details']['post_office_manager'] = array(
				'#title' => '(x) Post Office',
				'#type' => 'select',
				'#attributes' => array('class' => array(''), 'placeholder' => 'Post Office'),
				'#options' => array(
					'0' => t('Select Post Office')
				),
				'#required' => TRUE,
				'#prefix' => '<div id="post_office_manager_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);	
		}
		
		$form['manager_details']['adress_line1_manager'] = array(
			'#prefix' => '<div id="adress_line1_manager_id"><div class="col-md-12 col-xs-4"><label class="textarea label-block">',
			'#suffix' => '</label></div></div>',
			'#title' => '(xi) Address',
			'#rows' => 3,
			'#type' => 'textarea',
			'#required' => TRUE,
			'#default_value' 	    => !empty($ir_adress_line1_manager) ? $ir_adress_line1_manager : $factory_adress_line1_manager,
			'#attributes' => array('class' => array(''),'placeholder' => 'Address Line'),
			'#element_validate' => array('element_validate_streetaddress'), 
		);
		
		$form['manager_details']['manager_telephone'] = array(
			'#prefix' 				=> '<div id="manager_telephone_id"><div class="col-md-4 col-xs-4"><label class="input label-block">',
			'#suffix' 				=> '</label></div></div>',
			'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Manager Telephone No.'),
			'#title' 			 	=> t('(xii) Manager Telephone No.'),
			'#maxlength' 		 	=> 15,
			'#default_value' 	 	=> !empty($ir_manager_telephone) ? $ir_manager_telephone : $manager_telephone,
			'#required' 			=> TRUE,
			'#type' 				=> 'textfield',
			'#element_validate' 	=> array('element_validate_telephoneno'),
		);
		
		$form['manager_details']['manager_fax_no'] = array(
			'#prefix' 				=> '<div id="manager_fax_no_id"><div class="col-md-4 col-xs-4"><label class="input label-block">',
			'#suffix' 				=> '</label></div></div>',
			'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Manager Fax No.'),
			'#title' 			 	=> t('(xiii) Manager Fax No.'),
			'#maxlength' 		 	=> 15,
			'#default_value' 	 	=> !empty($ir_manager_fax_no) ? $ir_manager_fax_no : $manager_fax_no,
			//'#required' 			=> TRUE,
			'#type' 				=> 'textfield',
			'#element_validate' 	=> array('element_validate_telephoneno'),
		);
		
		$form['manager_details']['manager_email_id'] = array(
			'#prefix' 				=> '<div id="manager_emailid_id"><div class="col-md-4 col-xs-4"><label class="input label-block">',
			'#suffix' 				=> '</label></div></div>',
			'#attributes' 			=> array('class' => array(),'placeholder' => 'Manager Email ID'),
			'#title' 			 	=> t('(xiv) Manager Email ID'),
			'#default_value' 	 	=> !empty($ir_manager_email_id) ? $ir_manager_email_id : $manager_email_id,
			'#required' 			=> TRUE,
			'#type' 				=> 'textfield',
			'#element_validate' 	=> array('element_validate_email'),
		);
		
		$form['manager_details']['manager_mobile'] = array(
			'#prefix' 				=> '<div id="manager_mobile_id"><div class="col-md-4 col-xs-4"><label class="input label-block">',
			'#suffix' 				=> '</label></div></div></div>',
			'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Manager Mobile No.'),
			'#title' 			 	=> t('(xv) Manager Mobile No.'),
			'#maxlength' 		 	=> 10,
			'#default_value' 	 	=> !empty($ir_manager_mobile) ? $ir_manager_mobile : $manager_mobile,
			'#required' 			=> TRUE,
			'#type' 				=> 'textfield',
			'#element_validate' 	=> array('element_validate_mobile'),
		);
			
//occupier address section end
		
		
		
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'admin/inspection-report-factories/occupier-details/'.$inspection_reportID.'/'.$factoryID.'/'.encryption_decryption_fun('encrypt', NULL), array(
				'html' => TRUE,
				'attributes' => array('class' => array('btn btn-outline-dark pull-left'))
			))
		);
		
		$form['occupier_details_submit']['submit'] = array (
			'#prefix' 		=> '',  
			'#suffix' 		=> '',
			'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
			'#type' 		=> 'submit',
			'#value'		=> 'Save & Continue'
		);
		
		return $form;
		
	}
	
	
	function inspection_report_manager_details_validate($form, &$form_state) {
		
		
		
	}
	
	
	function inspection_report_manager_details_submit($form, &$form_state){
		//echo '<pre>'; print_r($form_state); die();
		
		global $base_root,$base_path,$user;
		
		$uid 							= $user->uid;
		
		$inspection_report_id = $form_state['values']['inspection_report_id'];
		
		$factory_id = $form_state['values']['factory_id'];
		
		$val = $form_state['values'];
		
		if($factory_id != 0) {
			
			if($inspection_report_id != 0) {
				
				$inspection_report_ID = $inspection_report_id;
				
				$inspection_report_manager = array(
					
					'manager_name'   					=> $val['manager_name'],
					'pincode_manager'					=> $val['pincode_manager'],
					'state_manager'						=> $val['state_manager'],
					'district_manager'					=> $val['district_manager'],
					'sub_division_manager'				=> $val['sub_division_manager'],
					'area_type_manager'					=> $val['area_type_manager'],
					'block_mun_cor_sez_not_manager'		=> $val['block_mun_cor_sez_not_manager'],
					'grm_ward_sector_not_manager'		=> $val['grm_ward_sector_not_manager'],
					'police_station_manager'			=> $val['police_station_manager'],
					'post_office_manager'				=> $val['post_office_manager'],
					'adress_line1_manager'				=> $val['adress_line1_manager'],
					'manager_telephone'					=> $val['manager_telephone'],
					'manager_fax_no'					=> $val['manager_fax_no'],
					'manager_email_id'					=> $val['manager_email_id'],
					'manager_mobile'					=> $val['manager_mobile'],
					
					'uid' 								=> $uid,
					'modification_date'	   				=> date('Y-m-d H:i:s'),
					
				);
				
				db_update('fa_inspection_report')->fields($inspection_report_manager)->condition('id', $inspection_report_ID, '=')->execute();	
					
			}
			
		} 
		
		//die($inspection_report_ID);
		drupal_goto('admin/inspection-report-factories/infringement-details/'.encryption_decryption_fun('encrypt', $inspection_report_ID).'/'.encryption_decryption_fun('encrypt', $factory_id).'/'.encryption_decryption_fun('encrypt', NULL));
		
		$form_state['rebuild'] = true;
		
		
	}