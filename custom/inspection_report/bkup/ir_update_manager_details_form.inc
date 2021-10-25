<?php

	function ir_update_manager_details_form_page($ajax, $value_factory_id = '', $inspection_reportID = '') {
		
		if ($ajax) {
			ctools_include('ajax');
			ctools_include('modal');
			
			$form_state = array(
				'ajax' => TRUE,
				'title' => t('Update Manager\'s Details'),
				'manager_factory_id' => $value_factory_id,
				'manager_ir_id' => $inspection_reportID,
			);
			
			// Use ctools to generate ajax instructions for the browser to create
			// a form in a modal popup.
			$output = ctools_modal_form_wrapper('ir_update_manager_details_form', $form_state);
			
			// If the form has been submitted, there may be additional instructions
			// such as dismissing the modal popup.
			if (!empty($form_state['ajax_commands'])) {
				$output = $form_state['ajax_commands'];
			}
			
			// Return the ajax instructions to the browser via ajax_render().
			print ajax_render($output);
			drupal_exit();
		}
		else {
			return drupal_get_form('ir_update_manager_details_form');
		}
		
	}
	
	function ir_update_manager_details_form($form, &$form_state) {
		
		$factory_id_encrypt_val = $form_state['manager_factory_id'];
		$factory_id = encryption_decryption_fun('decrypt', $factory_id_encrypt_val);
		
		$inspection_report_id_encrypt_val = $form_state['manager_ir_id'];
		$inspection_report_id = encryption_decryption_fun('decrypt', $inspection_report_id_encrypt_val);
		
		if((!empty($factory_id)) && ($factory_id != 0)) {
			
			$get_factory_info = get_inspection_report_factory_information($inspection_report_id);
			$get_manager_value = get_reg_factory_manager($factory_id);
			
			if($get_factory_info->cafa_id != NULL) {
				if($get_factory_info->cafa_id == $factory_id) {
					
					if(($get_factory_info->temp_cafa_id_occupier_data == NULL && $get_factory_info->temp_cafa_id_manager_data == NULL) || 
					($get_factory_info->cafa_id == $get_factory_info->temp_cafa_id_occupier_data && $get_factory_info->temp_cafa_id_manager_data == NULL) || 
					($get_factory_info->temp_cafa_id_occupier_data == NULL && $get_factory_info->cafa_id == $get_factory_info->temp_cafa_id_manager_data) ||
					($get_factory_info->cafa_id == $get_factory_info->temp_cafa_id_occupier_data && $get_factory_info->cafa_id == $get_factory_info->temp_cafa_id_manager_data)) {
						
						$get_ir_common_value = get_inspection_report_factory_information($inspection_report_id);
						
					}
					
				} else {
					if(($get_factory_info->temp_cafa_id_manager_data != NULL) && ($get_factory_info->temp_cafa_id_manager_data == $factory_id)) {
						$get_ir_common_value = get_inspection_report_manager_information($inspection_report_id);
					}	
				}
			} else {
				if(($get_factory_info->temp_cafa_id_manager_data != NULL) && ($get_factory_info->temp_cafa_id_manager_data == $factory_id)) {
					$get_ir_common_value = get_inspection_report_manager_information($inspection_report_id);
				}	
			}
			
			
			if(!empty($get_manager_value)) {
				$manager_name 								= $get_manager_value['name_manager'];
				$factory_pincode_manager        			= $get_manager_value['pincode_manager'];
				$factory_state_manager          			= $get_manager_value['state_manager'];
				$factory_district_manager 	    			= $get_manager_value['district_manager'];
				$factory_sub_division_manager    			= $get_manager_value['sub_division_manager'];
				$factory_area_type_manager       			= $get_manager_value['area_type_manager'];
				$factory_block_mun_cor_sez_not_manager      = $get_manager_value['block_mun_cor_sez_not_manager'];
				$factory_grm_ward_sector_not_manager      	= $get_manager_value['grm_ward_sector_not_manager'];
				$factory_police_station_manager  			= $get_manager_value['police_station_manager'];
				$factory_post_office_manager     			= $get_manager_value['post_office_manager'];
				$factory_adress_line1_manager				= $get_manager_value['adress_line1_manager'];
				$manager_telephone  						= $get_manager_value['manager_telephone'];
				$manager_fax_no     						= $get_manager_value['manager_fax'];
				$manager_email_id							= $get_manager_value['manager_email'];
				$manager_mobile								= $get_manager_value['manager_phone'];
			}
			
			if(!empty($get_ir_common_value)) {
				$ir_manager_name 							= $get_ir_common_value->manager_name;
				$ir_pincode_manager        					= $get_ir_common_value->pincode_manager;
				$ir_state_manager          					= $get_ir_common_value->state_manager;
				$ir_district_manager 	    				= $get_ir_common_value->district_manager;
				$ir_sub_division_manager    				= $get_ir_common_value->sub_division_manager;
				$ir_area_type_manager       				= $get_ir_common_value->area_type_manager;
				$ir_block_mun_cor_sez_not_manager          	= $get_ir_common_value->block_mun_cor_sez_not_manager;
				$ir_grm_ward_sector_not_manager      		= $get_ir_common_value->grm_ward_sector_not_manager;
				$ir_police_station_manager  				= $get_ir_common_value->police_station_manager;
				$ir_post_office_manager     				= $get_ir_common_value->post_office_manager;
				$ir_adress_line1_manager					= $get_ir_common_value->adress_line1_manager;
				$ir_manager_telephone      					= $get_ir_common_value->manager_telephone;
				$ir_manager_fax_no  						= $get_ir_common_value->manager_fax_no;
				$ir_manager_email_id     					= $get_ir_common_value->manager_email_id;
				$ir_manager_mobile		  					= $get_ir_common_value->manager_mobile;
			}
				
			$form['manager_information']['manager_details_heading_upd'] = array(
				'#prefix' 				=> '<div class="row"><div class="col-md-12 col-xs-12"><h4><b>Manager\'s Details</b></h4>',
				'#suffix' 				=> '</div></div>',
			);
			
			$form['manager_information']['manager_factory_id_upd'] = array(
				'#prefix' 			=> '<div id="manager_factory_upd_id"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#type' 			=> 'hidden',
				'#default_value' 	=> $factory_id,
			);
			
			$form['manager_information']['manager_inspection_report_id_upd'] = array(
				'#prefix' 			=> '<div id="manager_annual_return_id_upd"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#type' 			=> 'hidden',
				'#default_value' 	=> $inspection_report_id,
			);
			
			$form['manager_information']['manager_name_upd'] = array(
				'#prefix' 				=> '<div id="manager_name_upd_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array(),'placeholder' => 'Manager Name'),
				'#title' 			 	=> t('(i) Manager Name'),
				'#default_value' 	 	=> !empty($ir_manager_name) ? $ir_manager_name : $manager_name,
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
				'#element_validate' 	=> array('element_validate_alphabatic_fullstop'),
			);
			
	//manager address section
			
			$value_pincode_manager = isset($form_state['values']['pincode_manager_upd']) && !empty($form_state['values']['pincode_manager_upd']) ? $form_state['values']['pincode_manager_upd'] : (!empty($ir_pincode_manager) ? $ir_pincode_manager : $factory_pincode_manager);
			
			$form['manager_information']['pincode_manager_upd']       = array(
                '#prefix' 				=> '<div id="pincode_manager_upd_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
                '#suffix' 				=> '</label></div></div>',
                '#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Pincode'),
                '#autocomplete_path' 	=> 'pinautocomplete',
                '#id' 				 	=> 'pincode_autocomplete_manager_upd',
                '#maxlength' 		 	=> 6,
                '#title' 			 	=> t('(ii) Pincode'),
                '#default_value' 	 	=> !empty($ir_pincode_manager) ? $ir_pincode_manager : $factory_pincode_manager,
                '#required' 			=> TRUE,
                '#type' 				=> 'textfield',
				'#element_validate'	 	=> array('element_validate_numeric_positive'),
                '#ajax' 				=> array(
                                                    'effect' 	=> 'fade',
                                                    'callback' 	=> 'get_ajax_manager_details_for_ir_load',
                                                    'progress' 	=> array(
                                                     'type' 	=> 'throbber',
                                                    'message' 	=> t('loading')
                    )
                )
            );
			
			if(!empty($value_pincode_manager)) {
				
				$query_pin_manager = db_select('fa_all_india_pin_code', 'p')
									->fields('p', array('districtname','statename',  'pincode','district_code', 'state_code', 'po_name'))
									->condition('p.pincode', trim($value_pincode_manager), '=');
				
			   	$result_pin_manager = $query_pin_manager->execute();
				if ($result_pin_manager->rowcount() > 0) {
					$final_pin_manager       = $result_pin_manager->fetchAssoc();
					$pincode_v_manager   = $value_pincode_manager;
					$state_v_manager     = $final_pin_manager['state_code'];
					$district_v_manager  = $final_pin_manager['district_code'];
					$post_office_manager = $final_pin_manager['po_name'];
				}
			}
			
			$value_state_manager = isset($form_state['values']['state_manager_upd']) && !empty($form_state['values']['state_manager_upd']) ? $form_state['values']['state_manager_upd'] : (!empty($ir_state_manager) ? $ir_state_manager : $factory_state_manager);
			
			if(!empty($state_v_manager)) {;
                $form['manager_information']['state_manager_upd'] = array(
                    '#title' 		=> '(iii) State',
                    '#type' 		=> 'select',
                    '#id' 			=> 'state_manager_upd',
                    '#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
                    '#disabled' 	=> TRUE,
                    '#options' 		=> get_all_state($state_v_manager),
                    '#default_value' 	 	=> !empty($state_v_manager) ? $state_v_manager : '',
                    '#required' 	=> TRUE,
                    '#prefix' 		=> '<div id="state_manager_upd_id_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                    '#suffix' 		=> '</label></div></div>',
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_ajax_manager_details_for_ir_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );	
			} else {
                $form['manager_information']['state_manager_upd'] = array(
                    '#title' 		=> '(iii) State',
                    '#type' 		=> 'select',
                    '#id' 			=> 'state_manager_upd',
                    '#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
                    '#disabled' 	=> TRUE,
                    '#options' => array(
						'' => t('Select State')
					),
                    //'#value' 	 	=> '',
                    '#required' 	=> TRUE,
                    '#prefix' 		=> '<div id="state_manager_upd_id_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                    '#suffix' 		=> '</label></div></div>',
                );
			}
			
			$value_district_manager = isset($form_state['values']['district_manager_upd']) && !empty($form_state['values']['district_manager_upd']) ? $form_state['values']['district_manager_upd'] : (!empty($ir_district_manager) ? $ir_district_manager : $factory_district_manager);
			
			if(!empty($state_v_manager)) {
                $form['manager_information']['district_manager_upd'] = array(
                    '#title' => '(iv) District',
                    '#type' => 'select',
                    '#id' => 'district_manager_upd',
                    '#disabled' => TRUE,
                    '#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
                    '#options' => get_district_by_id($state_v_manager),
                    '#default_value' 	=> !empty($district_v_manager) ? $district_v_manager : '',
                    '#required' => TRUE,
                    '#prefix' => '<div id="district_manager_upd_id_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_ajax_manager_details_for_ir_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );	
			} else {
                $form['manager_information']['district_manager_upd'] = array(
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
                    '#prefix' => '<div id="district_manager_upd_id_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                );
			}
			
			$value_subdivision_manager = isset($form_state['values']['sub_division_manager_upd']) && !empty($form_state['values']['sub_division_manager_upd']) ? $form_state['values']['sub_division_manager_upd'] : (!empty($ir_sub_division_manager) ? $ir_sub_division_manager : $factory_sub_division_manager);
			
			if(!empty($state_v_manager) && !empty($district_v_manager)) {
                $form['manager_information']['sub_division_manager_upd'] = array(
                    '#title' => '(v) Sub-Division',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'Sub Division'),
                    '#options' => common_custom_user_subdivisionlist_list_new($district_v_manager),
                    '#required' => TRUE,
                    '#default_value' 	=> !empty($ir_sub_division_manager) ? $ir_sub_division_manager : $factory_sub_division_manager,
                    '#prefix' => '<div id="sub_division_manager_upd_id_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_ajax_manager_details_for_ir_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );	
			} else {
                $form['manager_information']['sub_division_manager_upd'] = array(
                    '#title' => '(v) Sub-Division',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'Sub Division'),
                    '#options' => array(
						'' => t('Select Sub-Division')
					),
                    '#required' => TRUE,
                    '#prefix' => '<div id="sub_division_manager_upd_id_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                );
			}
			
			$value_areatype_manager = isset($form_state['values']['area_type_manager_upd']) && !empty($form_state['values']['area_type_manager_upd']) ? $form_state['values']['area_type_manager_upd'] : (!empty($ir_area_type_manager) ? $ir_area_type_manager : $factory_area_type_manager);
			
			if(!empty($value_district_manager) && !empty($value_state_manager) && !empty($value_subdivision_manager)) {
                $form['manager_information']['area_type_manager_upd'] = array(
                    '#title' => '(vi) Area Type',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'Area Type'),
                    '#options' => common_custom_user_areatype_list_new($value_district_manager, $value_subdivision_manager),
                    '#required' => TRUE,
                    '#default_value' 	=> !empty($ir_area_type_manager) ? $ir_area_type_manager : $factory_area_type_manager,
                    '#prefix' => '<div id="area_type_manager_upd_id_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_ajax_manager_details_for_ir_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );	
				
			} else {
                $form['manager_information']['area_type_manager_upd'] = array(
                    '#title' => '(vi) Area Type',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'Area Type'),
                    '#options' => array(
                        '0' => t('Select Area Type')
                    ),
                    '#required' => TRUE,
                    '#prefix' => '<div id="area_type_manager_upd_id_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                );
			}
			
			$value_block_manager = isset($form_state['values']['block_mun_cor_sez_not_manager_upd']) && !empty($form_state['values']['block_mun_cor_sez_not_manager_upd']) ? $form_state['values']['block_mun_cor_sez_not_manager_upd'] : (!empty($ir_block_mun_cor_sez_not_manager) ? $ir_block_mun_cor_sez_not_manager : $factory_block_mun_cor_sez_not_manager);
			
			if(!empty($value_district_manager) && !empty($value_state_manager) && !empty($value_subdivision_manager) && !empty($value_areatype_manager)) {
				if ($value_areatype_manager == 'B') {
					$areatype_name_manager = 'Block';
				} elseif ($value_areatype_manager == 'M') {
					$areatype_name_manager = 'Municipality';
				} elseif ($value_areatype_manager == 'C') {
					$areatype_name_manager = 'Corporation';
				} elseif ($value_areatype_manager == 'S') {
					$areatype_name_manager = 'SEZ';
				} elseif ($value_areatype_manager == 'N') {
					$areatype_name_manager = 'Notified Area';
				}
				
				$form['manager_information']['block_mun_cor_sez_not_manager_upd'] = array(
					'#title' 		=> '(vii) '. $areatype_name_manager,
					'#type'         => 'select',
					'#attributes'   => array('class' => array(''),'placeholder' => 'Block'),
					'#options' 		=> common_custom_user_block_list_new($value_subdivision_manager, $value_areatype_manager),
					'#required' 	=> TRUE,
					'#default_value' 	    => !empty($ir_block_mun_cor_sez_not_manager) ? $ir_block_mun_cor_sez_not_manager : $factory_block_mun_cor_sez_not_manager,
					'#prefix' 		=> '<div id="block_mun_cor_sez_not_manager_upd_id_replace"><div class="col-md-6 col-xs-12"><label class="select label-block">',
					'#suffix' 		=> '</label></div></div>',
					'#ajax' => array(
										'event' => 'change',
										'effect' => 'fade',
										'callback' => 'get_ajax_manager_details_for_ir_load',
										'progress' => array(
															 'type' => 'throbber',
															 'message' => t('loading')
										)
					)
				);	
				
			} else {
					
                $form['manager_information']['block_mun_cor_sez_not_manager_upd'] = array(
                    '#title' 		=> '(vii) Block / Municipality / Corporation / Notified Area / SEZ',
                    '#type'         => 'select',
                    '#attributes'   => array('class' => array(''),'placeholder' => 'Block'),
                    '#options' => array(
						'0' => t('Select Block / Municipality / Corporation / Notified Area / SEZ')
					),
                    '#required' 	=> TRUE,
                    '#prefix' 		=> '<div id="block_mun_cor_sez_not_manager_upd_id_replace"><div class="col-md-6 col-xs-12"><label class="select label-block">',
                    '#suffix' 		=> '</label></div></div>',
                );
			}
			
			$value_panchayat_manager = isset($form_state['values']['grm_ward_sector_not_manager_upd']) && !empty($form_state['values']['grm_ward_sector_not_manager_upd']) ? $form_state['values']['grm_ward_sector_not_manager_upd'] : (!empty($ir_grm_ward_sector_not_manager) ? $ir_grm_ward_sector_not_manager : $factory_grm_ward_sector_not_manager);
			
			if(!empty($value_district_manager) && !empty($value_state_manager) && !empty($value_subdivision_manager) && !empty($value_areatype_manager) && !empty($value_block_manager)) {
			
				if ($value_areatype_manager == 'B') {
					$area_name_manager = 'Gram Panchayat';
					$area_code_manager = 'V';
				} elseif ($value_areatype_manager == 'M') {
					$area_name_manager = 'Ward';
					$area_code_manager = 'W';
				} elseif ($value_areatype_manager == 'C') {
					$area_name_manager = 'Ward';
					$area_code_manager = 'C';
				} elseif ($value_areatype_manager == 'S') {
					$area_name_manager = 'Sector';
					$area_code_manager = 'S';
				} elseif ($value_areatype_manager == 'N') {
					$area_name_manager = 'Notified Area';
					$area_code_manager = 'N';
				}
				
                $form['manager_information']['grm_ward_sector_not_manager_upd'] = array(
                    '#title' => '(viii) '.$area_name_manager,
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'panchayat'),
                    '#options' => common_custom_user_villward_list_new($value_block_manager, $area_code_manager),
                    '#default_value' 	    => !empty($ir_grm_ward_sector_not_manager) ? $ir_grm_ward_sector_not_manager : $factory_grm_ward_sector_not_manager,
                    '#prefix' => '<div id="grm_ward_sector_not_manager_upd_id_replace"><div class="col-md-6 col-xs-12""><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#required' => TRUE,
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_ajax_manager_details_for_ir_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );

				
			} else {
			
                $form['manager_information']['grm_ward_sector_not_manager_upd'] = array(
                    '#title' => '(viii) Gram Panchayat / Ward / Sector',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'panchayat'),
                    '#options' => array(
						'0' => t('Select Gram Panchayat / Ward / Sector / Notified Area')
					),
                    '#prefix' => '<div id="grm_ward_sector_not_manager_upd_id_replace"><div class="col-md-6 col-xs-12""><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#required' => TRUE,
                );
			}
			
			if(!empty($value_district_manager) && !empty($value_state_manager) && !empty($value_subdivision_manager) && !empty($value_areatype_manager) && !empty($value_block_manager) && !empty($value_panchayat_manager)) {
				
                $form['manager_information']['police_station_manager_upd'] = array(
                    '#title' => '(ix) Police Station',
                    '#type' => 'select',
                    '#attributes' => array('class' => array( ''),'placeholder' => 'Police Station'),
                    '#options' => common_custom_user_ps_list_new($value_district_manager),
                    '#required' => TRUE,
                    '#default_value' 	    => !empty($ir_police_station_manager) ? $ir_police_station_manager : $factory_police_station_manager,
                    '#prefix' => '<div id="police_station_manager_upd_id_replace"><div class="col-md-4 col-xs-12""><label class="select label-block">',
                    '#suffix' => '</label></div></div>'
                );	
				
			} else {
				
                $form['manager_information']['police_station_manager_upd'] = array(
                    '#title' => '(ix) Police Station',
                    '#type' => 'select',
                    '#attributes' => array('class' => array( ''),'placeholder' => 'Police Station'),
                    '#options' => array(
						'0' => t('Select Police Station')
					),
                    '#required' => TRUE,
                    '#prefix' => '<div id="police_station_manager_upd_id_replace"><div class="col-md-4 col-xs-12""><label class="select label-block">',
                    '#suffix' => '</label></div></div>'
                );
			}
			
			if(!empty($pincode_v_manager)) {
                $form['manager_information']['post_office_manager_upd'] = array(
                    '#title' => '(x) Post Office',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''), 'placeholder' => 'Post Office'),
                    '#options' => common_custom_post_office_list_new($pincode_v_manager),
                    '#default_value' 	    => !empty($ir_post_office_manager) ? $ir_post_office_manager : $factory_post_office_manager,
                    '#required' => TRUE,
                    '#prefix' => '<div id="post_office_manager_upd_id_replace"><div class="col-md-4 col-xs-12""><label class="select label-block">',
                    '#suffix' => '</label></div></div>'
                );	
				
			} else {
                $form['manager_information']['post_office_manager_upd'] = array(
                    '#title' => '(x) Post Office',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''), 'placeholder' => 'Post Office'),
                    '#options' => array(
						'0' => t('Select Post Office')
					),
                    '#required' => TRUE,
                    '#prefix' => '<div id="post_office_manager_upd_id_replace"><div class="col-md-4 col-xs-12""><label class="select label-block">',
                    '#suffix' => '</label></div></div>'
                );
			}
			
			 $form['manager_information']['adress_line1_manager_upd'] = array(
				'#prefix' => '<div id="adress_line1_manager_upd_id"><div class="col-md-12 col-xs-12""><label class="textarea label-block">',
				'#suffix' => '</label></div></div>',
				'#title' => '(xi) Address',
				'#rows' => 3,
				'#type' => 'textarea',
				'#required' => TRUE,
				'#default_value' 	    => !empty($ir_adress_line1_manager) ? $ir_adress_line1_manager : $factory_adress_line1_manager,
				'#attributes' => array('class' => array(''),'placeholder' => 'Address Line'),
				'#element_validate' => array('element_validate_streetaddress'),
			);
			
			$form['manager_information']['manager_telephone_upd'] = array(
				'#prefix' 				=> '<div id="manager_telephone_upd_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Manager Telephone No.'),
				'#title' 			 	=> t('(xii) Manager Telephone No.'),
				'#maxlength' 		 	=> 15,
				'#default_value' 	 	=> !empty($ir_manager_telephone) ? $ir_manager_telephone : $manager_telephone,
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
				'#element_validate' 	=> array('element_validate_telephoneno'),
			);
			
			$form['manager_information']['manager_fax_no_upd'] = array(
				'#prefix' 				=> '<div id="manager_fax_no_upd_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Manager Fax No.'),
				'#title' 			 	=> t('(xiii) Manager Fax No.'),
				'#maxlength' 		 	=> 15,
				'#default_value' 	 	=> !empty($ir_manager_fax_no) ? $ir_manager_fax_no : $manager_fax_no,
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
				'#element_validate' 	=> array('element_validate_telephoneno'),
			);
			
			$form['manager_information']['manager_email_id_upd'] = array(
				'#prefix' 				=> '<div id="manager_emailid_upd_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array(),'placeholder' => 'Manager Email ID'),
				'#title' 			 	=> t('(xiv) Manager Email ID'),
				'#default_value' 	 	=> !empty($ir_manager_email_id) ? $ir_manager_email_id : $manager_email_id,
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
				'#element_validate' 	=> array('element_validate_email'),
			);
			
			$form['manager_information']['manager_mobile_upd'] = array(
				'#prefix' 				=> '<div id="manager_mobile_upd_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 				=> '</label></div></div></div>',
				'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Manager Mobile No.'),
				'#title' 			 	=> t('(xv) Manager Mobile No.'),
				'#maxlength' 		 	=> 10,
				'#default_value' 	 	=> !empty($ir_manager_mobile) ? $ir_manager_mobile : $manager_mobile,
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
				'#element_validate' 	=> array('element_validate_mobile'),
			);
			
	//manager address section end
			
		}
		
		$form['manager_information']['submit'] = array (
			'#prefix' 		=> '',  
			'#suffix' 		=> '',
			'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
			'#type' 		=> 'submit',
			'#value'		=> 'Update'
		);
		
		
		return $form;
		
	}
	
	function ir_update_manager_details_form_validate($form, &$form_state) {
		$factory_id = $form_state['values']['manager_factory_id_upd'];
		$inspection_report_id = $form_state['values']['manager_inspection_report_id_upd'];
		
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
	
	
	function ir_update_manager_details_form_submit($form, &$form_state) {
		
		global $base_root, $base_path, $user;
		
		$uid = $user->uid;
		
		$factory_id = $form_state['values']['manager_factory_id_upd'];
		$inspection_report_id = $form_state['values']['manager_inspection_report_id_upd'];
		
		$val = $form_state['values'];
		
		if((!empty($factory_id)) && ($factory_id != 0)) {
			
			if($inspection_report_id == 0) {
				
				$inspection_report_manager = array(
					
					//'cafa_id' => $factory_id,
					
					'manager_name'   				=> $val['manager_name_upd'],
					'pincode_manager'				=> $val['pincode_manager_upd'],
					'state_manager'					=> $val['state_manager_upd'],
					'district_manager'				=> $val['district_manager_upd'],
					'sub_division_manager'			=> $val['sub_division_manager_upd'],
					'area_type_manager'				=> $val['area_type_manager_upd'],
					'block_mun_cor_sez_not_manager'	=> $val['block_mun_cor_sez_not_manager_upd'],
					'grm_ward_sector_not_manager'	=> $val['grm_ward_sector_not_manager_upd'],
					'police_station_manager'		=> $val['police_station_manager_upd'],
					'post_office_manager'			=> $val['post_office_manager_upd'],
					'adress_line1_manager'			=> $val['adress_line1_manager_upd'],
					'manager_telephone'				=> $val['manager_telephone_upd'],
					'manager_fax_no'				=> $val['manager_fax_no_upd'],
					'manager_email_id'				=> $val['manager_email_id_upd'],
					'manager_mobile'				=> $val['manager_mobile_upd'],
					'uid' 							=> $uid,
					'created_date' 					=> date('Y-m-d'),
					'temp_cafa_id_manager_data' 	=> $factory_id,
					
				);
				
				$inspection_report_id = db_insert('fa_inspection_report')->fields($inspection_report_manager)->execute();
					
			} else {
			
				$inspection_report_manager = array(
					
					//'cafa_id' => $factory_id,
					
					'manager_name'   				=> $val['manager_name_upd'],
					'pincode_manager'				=> $val['pincode_manager_upd'],
					'state_manager'					=> $val['state_manager_upd'],
					'district_manager'				=> $val['district_manager_upd'],
					'sub_division_manager'			=> $val['sub_division_manager_upd'],
					'area_type_manager'				=> $val['area_type_manager_upd'],
					'block_mun_cor_sez_not_manager'	=> $val['block_mun_cor_sez_not_manager_upd'],
					'grm_ward_sector_not_manager'	=> $val['grm_ward_sector_not_manager_upd'],
					'police_station_manager'		=> $val['police_station_manager_upd'],
					'post_office_manager'			=> $val['post_office_manager_upd'],
					'adress_line1_manager'			=> $val['adress_line1_manager_upd'],
					'manager_telephone'				=> $val['manager_telephone_upd'],
					'manager_fax_no'				=> $val['manager_fax_no_upd'],
					'manager_email_id'				=> $val['manager_email_id_upd'],
					'manager_mobile'				=> $val['manager_mobile_upd'],
					'uid' 							=> $uid,
					'modification_date'	   			=> date('Y-m-d H:i:s'),
					'temp_cafa_id_manager_data' 	=> $factory_id,
					
				);
				
				db_update('fa_inspection_report')->fields($inspection_report_manager)->condition('id', $inspection_report_id, '=')->execute();
					
			}
			
		}
		
		if($form_state['submitted']) {
			$commands[] = ctools_modal_command_dismiss();
			//$commands[] = ctools_ajax_command_reload();
			$commands[] = ctools_ajax_command_redirect('admin/inspection-report-factories/default/'.encryption_decryption_fun('encrypt', $inspection_report_id).'/'.	
														encryption_decryption_fun('encrypt', $factory_id));
			
			print ajax_render($commands);
			drupal_exit();
		}
		
		$form_state['rebuild'] = TRUE;
		
		drupal_set_message('Manager\'s details updated sucessfully.');
		
	}
	
	function get_ajax_manager_details_for_ir_load($form, $form_state) {
		
		$commands   = array();
		$commands[] = ajax_command_replace('#state_manager_upd_id_replace', drupal_render($form['manager_information']['state_manager_upd']));
		$commands[] = ajax_command_replace('#district_manager_upd_id_replace', drupal_render($form['manager_information']['district_manager_upd']));
		$commands[] = ajax_command_replace('#sub_division_manager_upd_id_replace', drupal_render($form['manager_information']['sub_division_manager_upd']));
		$commands[] = ajax_command_replace('#area_type_manager_upd_id_replace', drupal_render($form['manager_information']['area_type_manager_upd']));
		$commands[] = ajax_command_replace('#block_mun_cor_sez_not_manager_upd_id_replace', drupal_render($form['manager_information']['block_mun_cor_sez_not_manager_upd']));
		$commands[] = ajax_command_replace('#grm_ward_sector_not_manager_upd_id_replace', drupal_render($form['manager_information']['grm_ward_sector_not_manager_upd']));
		$commands[] = ajax_command_replace('#police_station_manager_upd_id_replace', drupal_render($form['manager_information']['police_station_manager_upd']));
		$commands[] = ajax_command_replace('#post_office_manager_upd_id_replace', drupal_render($form['manager_information']['post_office_manager_upd']));
		return array(
			'#type' => 'ajax',
			'#commands' => $commands
		);
	}