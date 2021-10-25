<?php

	function update_occupier_details_form_page($ajax, $value_factory_id = '', $annual_returnID = '', $custom_path_POSTWO = '') {
		
		if ($ajax) {
			ctools_include('ajax');
			ctools_include('modal');
			
			$form_state = array(
				'ajax' => TRUE,
				'title' => t('Update Occupier\'s Details'),
				'occupier_factory_id' => $value_factory_id,
				'occupier_ar_id' => $annual_returnID,
				'occupier_cust_path_pos_two' => $custom_path_POSTWO,
			);
			
			// Use ctools to generate ajax instructions for the browser to create
			// a form in a modal popup.
			$output = ctools_modal_form_wrapper('update_occupier_details_form', $form_state);
			
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
			return drupal_get_form('update_occupier_details_form');
		}
		
	}
	
	function update_occupier_details_form($form, &$form_state) {
		
		$factory_id_encrypt_val = $form_state['occupier_factory_id'];
		$factory_id = encryption_decryption_fun('decrypt', $factory_id_encrypt_val);
		
		$annual_return_id_encrypt_val = $form_state['occupier_ar_id'];
		$annual_return_id = encryption_decryption_fun('decrypt', $annual_return_id_encrypt_val);
		
		$custom_path_pos_two_encrypt_val = $form_state['occupier_cust_path_pos_two'];
		$custom_path_pos_two = encryption_decryption_fun('decrypt', $custom_path_pos_two_encrypt_val);
		
		if((!empty($factory_id)) && ($factory_id != 0)) {
			
			$get_factory_info = get_annual_return_factory_information($annual_return_id);
			$get_occupier_value = get_reg_factory_occupier($factory_id);
			
			if($get_factory_info->cafa_id != NULL) {
				if($get_factory_info->cafa_id == $factory_id) {
					
					if(($get_factory_info->temp_cafa_id_occupier_data == NULL && $get_factory_info->temp_cafa_id_manager_data == NULL) || 
					($get_factory_info->cafa_id == $get_factory_info->temp_cafa_id_occupier_data && $get_factory_info->temp_cafa_id_manager_data == NULL) || 
					($get_factory_info->temp_cafa_id_occupier_data == NULL && $get_factory_info->cafa_id == $get_factory_info->temp_cafa_id_manager_data) ||
					($get_factory_info->cafa_id == $get_factory_info->temp_cafa_id_occupier_data && $get_factory_info->cafa_id == $get_factory_info->temp_cafa_id_manager_data)) {
						
						//$get_ar_common_value = get_annual_return_common_details($factory_id);
						$get_ar_common_value = get_annual_return_factory_information($annual_return_id);
						
					}
					
				} else {
					if(($get_factory_info->temp_cafa_id_occupier_data != NULL) && ($get_factory_info->temp_cafa_id_occupier_data == $factory_id)) {
						$get_ar_common_value = get_annual_return_occupier_information($annual_return_id);	
					}	
				}
			} else {
				if(($get_factory_info->temp_cafa_id_occupier_data != NULL) && ($get_factory_info->temp_cafa_id_occupier_data == $factory_id)) {
					$get_ar_common_value = get_annual_return_occupier_information($annual_return_id);	
				}		
			}

			
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
			
			if(!empty($get_ar_common_value)) {
				$ar_occupier_name 					  = $get_ar_common_value->name_occupier;
				$ar_pincodeoprmntadr_occupier         = $get_ar_common_value->pincodeoprmntadr;
				$ar_state_oprmntadr_occupier          = $get_ar_common_value->state_oprmntadr;
				$ar_district_oprmntadr_occupier 	  = $get_ar_common_value->district_oprmntadr;
				$ar_subdivision_oprmntadr_occupier    = $get_ar_common_value->subdivision_oprmntadr;
				$ar_areatype_oprmntadr_occupier       = $get_ar_common_value->areatype_oprmntadr;
				$ar_block_oprmntadr_occupier          = $get_ar_common_value->block_oprmntadr;
				$ar_panchayat_oprmntadr_occupier      = $get_ar_common_value->panchayat_oprmntadr;
				$ar_policestation_oprmntadr_occupier  = $get_ar_common_value->policestation_oprmntadr;
				$ar_postoffice_oprmntadr_occupier     = $get_ar_common_value->postoffice_oprmntadr;
				$ar_addrline_oprmntadr_occupier		  = $get_ar_common_value->addrline_oprmntadr;
			}
				
			$form['occupier_information']['occupier_details_heading'] = array(
				'#prefix' 				=> '<div class="row"><div class="col-md-12 col-xs-12"><h4><b>Occupier\'s Details</b></h4>',
				'#suffix' 				=> '</div></div>',
			);
			
			$form['occupier_information']['occupier_factory_id_upd'] = array(
				'#prefix' 			=> '<div id="occupier_factory_upd_id"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#type' 			=> 'hidden',
				'#default_value' 	=> $factory_id,
			);
			
			$form['occupier_information']['occupier_annual_return_id_upd'] = array(
				'#prefix' 			=> '<div id="occupier_annual_return_id_upd"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#type' 			=> 'hidden',
				'#default_value' 	=> $annual_return_id,
			);
			
			$form['occupier_information']['occupier_cust_path_pos_two_upd'] = array(
				'#prefix' 			=> '<div id="occupier_cust_path_pos_two_upd"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#type' 			=> 'hidden',
				'#default_value' 	=> $custom_path_pos_two,
			);
			
			$form['occupier_information']['occupier_name_upd'] = array(
				'#prefix' 				=> '<div id="occupier_name_upd_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
				'#suffix' 				=> '</label></div></div>',
				'#attributes' 			=> array('class' => array(),'placeholder' => 'Occupier Name'),
				'#title' 			 	=> t('(xx) Occupier Name'),
				'#default_value' 	 	=> !empty($ar_occupier_name) ? $ar_occupier_name : $occupier_name,
				'#required' 			=> TRUE,
				'#type' 				=> 'textfield',
				'#element_validate' 	=> array('element_validate_alphabatic_fullstop'),
			);
			
	//occupier address section
			
			$form['occupier_information']['pincodeoprmntadr_upd']       = array(
                '#prefix' 				=> '<div id="pincodeoprmntadr_occupier_upd_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
                '#suffix' 				=> '</label></div></div>',
                '#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Pincode'),
                '#autocomplete_path' 	=> 'pinautocomplete',
                '#id' 				 	=> 'pincode_autocomplete_occupier_upd',
                '#maxlength' 		 	=> 6,
                '#title' 			 	=> t('(xxi) Pincode'),
                '#default_value' 	 	=> !empty($ar_pincodeoprmntadr_occupier) ? $ar_pincodeoprmntadr_occupier : $factory_pincodeoprmntadr_occupier,
                '#required' 			=> TRUE,
                '#type' 				=> 'textfield',
				'#element_validate' 	=> array('element_validate_numeric_positive'),
                '#ajax' 				=> array(
                                                    'effect' 	=> 'fade',
                                                    'callback' 	=> 'get_ajax_occupier_details_load',
                                                    'progress' 	=> array(
                                                     'type' 	=> 'throbber',
                                                    'message' 	=> t('loading')
                    )
                )
            );
				
			$value_pincode_occupier = isset($form_state['values']['pincodeoprmntadr_upd']) && !empty($form_state['values']['pincodeoprmntadr_upd']) ? $form_state['values']['pincodeoprmntadr_upd'] : (!empty($ar_pincodeoprmntadr_occupier) ? $ar_pincodeoprmntadr_occupier : $factory_pincodeoprmntadr_occupier);
			
			if(!empty($value_pincode_occupier)) {
				
				$query_pin_occupier = db_select('fa_all_india_pin_code', 'p')
									->fields('p', array('districtname','statename',  'pincode','district_code', 'state_code', 'po_name'))
									->condition('p.pincode', trim($value_pincode_occupier), '=');
				
			   	$result_pin_occupier = $query_pin_occupier->execute();
				if ($result_pin_occupier->rowcount() > 0) {
					$final_pin_occupier       = $result_pin_occupier->fetchAssoc();
					$pincode_v_occupier   = $value_pincode_occupier;
					$state_v_occupier     = $final_pin_occupier['state_code'];
					$district_v_occupier  = $final_pin_occupier['district_code'];
					$post_office_occupier = $final_pin_occupier['po_name'];
				}
			}
			
			if(!empty($state_v_occupier)) {;
                $form['occupier_information']['state_oprmntadr_upd'] = array(
					'#title' 		=> '(xxii) State',
					'#type' 		=> 'select',
					'#id' 			=> 'state_occupier_name',
                    '#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
                    '#disabled' 	=> TRUE,
                    '#options' 		=> get_all_state($state_v_occupier),
                    '#default_value' 	 	=> !empty($state_v_occupier) ? $state_v_occupier : '',
                    '#required' 	=> TRUE,
                    '#prefix' 		=> '<div id="state_oprmntadr_occupier_upd_id_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                    '#suffix' 		=> '</label></div></div>',
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_ajax_occupier_details_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );	
			} else {
               $form['occupier_information']['state_oprmntadr_upd'] = array(
					'#title' 		=> '(xxii) State',
					'#type' 		=> 'select',
					'#id' 			=> 'state_occupier_name',
                    '#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
                    '#disabled' 	=> TRUE,
                    '#options' => array(
						'' => t('Select State')
					),
                    //'#value' 	 	=> '',
                    '#required' 	=> TRUE,
                    '#prefix' 		=> '<div id="state_oprmntadr_occupier_upd_id_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                    '#suffix' 		=> '</label></div></div>',
                );
			}
			
			$value_state_occupier = isset($form_state['values']['state_oprmntadr_upd']) && !empty($form_state['values']['state_oprmntadr_upd']) ? $form_state['values']['state_oprmntadr_upd'] : (!empty($ar_state_oprmntadr_occupier) ? $ar_state_oprmntadr_occupier : $factory_state_oprmntadr_occupier);
			
			if(!empty($state_v_occupier)) {
                $form['occupier_information']['district_oprmntadr_upd'] = array(
					'#title' => '(xxiii) District',
					'#type' => 'select',
					'#id' => 'district_occupier_name',
                    '#disabled' => TRUE,
                    '#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
                    '#options' => get_district_by_id($state_v_occupier),
                    '#default_value' 	=> !empty($district_v_occupier) ? $district_v_occupier : '',
                    '#required' => TRUE,
                    '#prefix' => '<div id="district_oprmntadr_occupier_upd_id_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_ajax_occupier_details_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );	
			} else {
               $form['occupier_information']['district_oprmntadr_upd'] = array(
					'#title' => '(xxiii) District',
					'#type' => 'select',
					'#id' => 'district_occupier_name',
                    '#disabled' => TRUE,
                    '#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
                    '#options' => array(
						'' => t('Select District')
					),
					//'#value' 	 	=> '',
                    '#required' => TRUE,
                    '#prefix' => '<div id="district_oprmntadr_occupier_upd_id_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                );
			}
			
			$value_district_occupier = isset($form_state['values']['district_oprmntadr_upd']) && !empty($form_state['values']['district_oprmntadr_upd']) ? $form_state['values']['district_oprmntadr_upd'] : (!empty($ar_district_oprmntadr_occupier) ? $ar_district_oprmntadr_occupier : $factory_district_oprmntadr_occupier);
			
			if(!empty($state_v_occupier) && !empty($district_v_occupier)) {
                $form['occupier_information']['subdivision_oprmntadr_upd'] = array(
					'#title' => '(xxiv) Sub-Division',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'Sub Division'),
                    '#options' => common_custom_user_subdivisionlist_list_new($district_v_occupier),
                    '#required' => TRUE,
                    '#default_value' 	=> !empty($ar_subdivision_oprmntadr_occupier) ? $ar_subdivision_oprmntadr_occupier : $factory_subdivision_oprmntadr_occupier,
                    '#prefix' => '<div id="subdivision_oprmntadr_occupier_upd_id_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_ajax_occupier_details_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );	
			} else {
                $form['occupier_information']['subdivision_oprmntadr_upd'] = array(
					'#title' => '(xxiv) Sub-Division',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'Sub Division'),
                    '#options' => array(
						'' => t('Select Sub-Division')
					),
                    '#required' => TRUE,
                    '#prefix' => '<div id="subdivision_oprmntadr_occupier_upd_id_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                );
			}
			
			$value_subdivision_occupier = isset($form_state['values']['subdivision_oprmntadr_upd']) && !empty($form_state['values']['subdivision_oprmntadr_upd']) ? $form_state['values']['subdivision_oprmntadr_upd'] : (!empty($ar_subdivision_oprmntadr_occupier) ? $ar_subdivision_oprmntadr_occupier : $factory_subdivision_oprmntadr_occupier);
			
			if(!empty($value_district_occupier) && !empty($value_state_occupier) && !empty($value_subdivision_occupier)) {
                $form['occupier_information']['areatype_oprmntadr_upd'] = array(
					'#title' => '(xxv) Area Type',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'Area Type'),
                    '#options' => common_custom_user_areatype_list_new($value_district_occupier, $value_subdivision_occupier),
                    '#required' => TRUE,
                    '#default_value' 	=> !empty($ar_areatype_oprmntadr_occupier) ? $ar_areatype_oprmntadr_occupier : $factory_areatype_oprmntadr_occupier,
                    '#prefix' => '<div id="areatype_oprmntadr_occupier_upd_id_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_ajax_occupier_details_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );	
				
			} else {
                $form['occupier_information']['areatype_oprmntadr_upd'] = array(
                    '#title' => '(xxv) Area Type',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'Area Type'),
                    '#options' => array(
                        '0' => t('Select Area Type')
                    ),
                    '#required' => TRUE,
                    '#prefix' => '<div id="areatype_oprmntadr_occupier_upd_id_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                );
			}
			
			$value_areatype_occupier = isset($form_state['values']['areatype_oprmntadr_upd']) && !empty($form_state['values']['areatype_oprmntadr_upd']) ? $form_state['values']['areatype_oprmntadr_upd'] : (!empty($ar_areatype_oprmntadr_occupier) ? $ar_areatype_oprmntadr_occupier : $factory_areatype_oprmntadr_occupier);
			
			if(!empty($value_district_occupier) && !empty($value_state_occupier) && !empty($value_subdivision_occupier) && !empty($value_areatype_occupier)) {
				if ($value_areatype_occupier == 'B') {
					$areatype_name_occupier = 'Block';
				} elseif ($value_areatype_occupier == 'M') {
					$areatype_name_occupier = 'Municipality';
				} elseif ($value_areatype_occupier == 'C') {
					$areatype_name_occupier = 'Corporation';
				} elseif ($value_areatype_occupier == 'S') {
					$areatype_name_occupier = 'SEZ';
				} elseif ($value_areatype_occupier == 'N') {
					$areatype_name_occupier = 'Notified Area';
				}
				
				$form['occupier_information']['block_oprmntadr_upd'] = array(
					'#title' 		=> '(xxvi) '. $areatype_name_occupier,
					'#type'         => 'select',
					'#attributes'   => array('class' => array(''),'placeholder' => 'Block'),
					'#options' 		=> common_custom_user_block_list_new($value_subdivision_occupier, $value_areatype_occupier),
					'#required' 	=> TRUE,
					'#default_value' 	    => !empty($ar_block_oprmntadr_occupier) ? $ar_block_oprmntadr_occupier : $factory_block_oprmntadr_occupier,
					'#prefix' 		=> '<div id="block_oprmntadr_occupier_upd_id_replace"><div class="col-md-6 col-xs-12"><label class="select label-block">',
					'#suffix' 		=> '</label></div></div>',
					'#ajax' => array(
										'event' => 'change',
										'effect' => 'fade',
										'callback' => 'get_ajax_occupier_details_load',
										'progress' => array(
															 'type' => 'throbber',
															 'message' => t('loading')
										)
					)
				);	
				
			} else {
					
                $form['occupier_information']['block_oprmntadr_upd'] = array(
                    '#title' 		=> '(xxvi) Block / Municipality / Corporation / Notified Area / SEZ',
                    '#type'         => 'select',
                    '#attributes'   => array('class' => array(''),'placeholder' => 'Block'),
                    '#options' => array(
						'0' => t('Select Block / Municipality / Corporation / Notified Area / SEZ')
					),
                    '#required' 	=> TRUE,
                    '#prefix' 		=> '<div id="block_oprmntadr_occupier_upd_id_replace"><div class="col-md-6 col-xs-12"><label class="select label-block">',
                    '#suffix' 		=> '</label></div></div>',
                );
			}
			
			$value_block_occupier = isset($form_state['values']['block_oprmntadr_upd']) && !empty($form_state['values']['block_oprmntadr_upd']) ? $form_state['values']['block_oprmntadr_upd'] : (!empty($ar_block_oprmntadr_occupier) ? $ar_block_oprmntadr_occupier : $factory_block_oprmntadr_occupier);
			
			if(!empty($value_district_occupier) && !empty($value_state_occupier) && !empty($value_subdivision_occupier) && !empty($value_areatype_occupier) && !empty($value_block_occupier)) {
			
				if ($value_areatype_occupier == 'B') {
					$area_name_occupier = 'Gram Panchayat';
					$area_code_occupier = 'V';
				} elseif ($value_areatype_occupier == 'M') {
					$area_name_occupier = 'Ward';
					$area_code_occupier = 'W';
				} elseif ($value_areatype_occupier == 'C') {
					$area_name_occupier = 'Ward';
					$area_code_occupier = 'C';
				} elseif ($value_areatype_occupier == 'S') {
					$area_name_occupier = 'Sector';
					$area_code_occupier = 'S';
				} elseif ($value_areatype_occupier == 'N') {
					$area_name_occupier = 'Notified Area';
					$area_code_occupier = 'N';
				}
				
                $form['occupier_information']['panchayat_oprmntadr_upd'] = array(
                    '#title' => '(xxvii) '.$area_name_occupier,
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'panchayat'),
                    '#options' => common_custom_user_villward_list_new($value_block_occupier, $area_code_occupier),
                    '#default_value' 	    => !empty($ar_panchayat_oprmntadr_occupier) ? $ar_panchayat_oprmntadr_occupier : $factory_panchayat_oprmntadr_occupier,
                    '#prefix' => '<div id="panchayat_oprmntadr_occupier_upd_id_replace"><div class="col-md-6 col-xs-12"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#required' => TRUE,
                    '#ajax' => array(
                                        'event' => 'change',
                                        'effect' => 'fade',
                                        'callback' => 'get_ajax_occupier_details_load',
                                        'progress' => array(
                                                             'type' => 'throbber',
                                                             'message' => t('loading')
                                        )
                    )
                );

				
			} else {
			
                $form['occupier_information']['panchayat_oprmntadr_upd'] = array(
                    '#title' => '(xxvii) Gram Panchayat / Ward / Sector',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''),'placeholder' => 'panchayat'),
                    '#options' => array(
						'0' => t('Select Gram Panchayat / Ward / Sector / Notified Area')
					),
                    '#prefix' => '<div id="panchayat_oprmntadr_occupier_upd_id_replace"><div class="col-md-6 col-xs-12"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#required' => TRUE,
                );
			}
			
			$value_panchayat_occupier = isset($form_state['values']['panchayat_oprmntadr_upd']) && !empty($form_state['values']['panchayat_oprmntadr_upd']) ? $form_state['values']['panchayat_oprmntadr_upd'] : (!empty($ar_panchayat_oprmntadr_occupier) ? $ar_panchayat_oprmntadr_occupier : $factory_panchayat_oprmntadr_occupier);
			
			if(!empty($value_district_occupier) && !empty($value_state_occupier) && !empty($value_subdivision_occupier) && !empty($value_areatype_occupier) && !empty($value_block_occupier) && !empty($value_panchayat_occupier)) {
				
                $form['occupier_information']['policestation_oprmntadr_upd'] = array(
                    '#title' => '(xxviii) Police Station',
                    '#type' => 'select',
                    '#attributes' => array('class' => array( ''),'placeholder' => 'Police Station'),
                    '#options' => common_custom_user_ps_list_new($value_district_occupier),
                    '#required' => TRUE,
                    '#default_value' 	    => !empty($ar_policestation_oprmntadr_occupier) ? $ar_policestation_oprmntadr_occupier : $factory_policestation_oprmntadr_occupier,
                    '#prefix' => '<div id="policestation_oprmntadr_occupier_upd_id_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                    '#suffix' => '</label></div></div>'
                );	
				
			} else {
				
                $form['occupier_information']['policestation_oprmntadr_upd'] = array(
                    '#title' => '(xxviii) Police Station',
                    '#type' => 'select',
                    '#attributes' => array('class' => array( ''),'placeholder' => 'Police Station'),
                    '#options' => array(
						'0' => t('Select Police Station')
					),
                    '#required' => TRUE,
                    '#prefix' => '<div id="policestation_oprmntadr_occupier_upd_id_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                    '#suffix' => '</label></div></div>'
                );
			}
			
			if(!empty($pincode_v_occupier)) {
                $form['occupier_information']['postoffice_oprmntadr_upd'] = array(
                    '#title' => '(xxix) Post Office',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''), 'placeholder' => 'Post Office'),
                    '#options' => common_custom_post_office_list_new($pincode_v_occupier),
                    '#default_value' 	    => !empty($ar_postoffice_oprmntadr_occupier) ? $ar_postoffice_oprmntadr_occupier : $factory_postoffice_oprmntadr_occupier,
                    '#required' => TRUE,
                    '#prefix' => '<div id="postoffice_oprmntadr_occupier_upd_id_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                    '#suffix' => '</label></div></div>'
                );	
				
			} else {
                $form['occupier_information']['postoffice_oprmntadr_upd'] = array(
                    '#title' => '(xxix) Post Office',
                    '#type' => 'select',
                    '#attributes' => array('class' => array(''), 'placeholder' => 'Post Office'),
                    '#options' => array(
						'0' => t('Select Post Office')
					),
                    '#required' => TRUE,
                    '#prefix' => '<div id="postoffice_oprmntadr_occupier_upd_id_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                    '#suffix' => '</label></div></div>'
                );
			}
			
			 $form['occupier_information']['addrline_oprmntadr_upd'] = array(
				'#prefix' => '<div id="addrline_oprmntadr_occupier_upd_id"><div class="col-md-12 col-xs-12"><label class="textarea label-block">',
				'#suffix' => '</label></div></div></div>',
				'#title' => '(xxx) Address',
				'#rows' => 3,
				'#type' => 'textarea',
				'#required' => TRUE,
				'#default_value' 	    => !empty($ar_addrline_oprmntadr_occupier) ? $ar_addrline_oprmntadr_occupier : $factory_addrline_oprmntadr_occupier,
				'#attributes' => array('class' => array(''),'placeholder' => 'Address Line'),
				'#element_validate' => array('element_validate_streetaddress'),
			);
			
	//manager address section end
			
		}
		
		$form['occupier_information']['submit'] = array (
			'#prefix' 		=> '',  
			'#suffix' 		=> '',
			'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
			'#type' 		=> 'submit',
			'#value'		=> 'Save & Continue'
		);
		
		
		return $form;
		
	}
	
	function update_occupier_details_form_validate($form, &$form_state) {
		$factory_id = $form_state['values']['occupier_factory_id_upd'];
		$annual_return_id = $form_state['values']['occupier_annual_return_id_upd'];
		$cust_path_pos_two = $form_state['values']['occupier_cust_path_pos_two_upd'];
		
		if($cust_path_pos_two == 'annual-return-common') {
			$query_ar_common 	= db_select('fa_annual_return', 'ar');
			$query_ar_common	->fields('ar',array());
			$result_ar_common 	= $query_ar_common->execute();
			
			if($result_ar_common->rowCount() > 0) {
				while($data_ar_common = $result_ar_common->fetchObject()) {
					if($data_ar_common->cafa_id == $factory_id) {
						form_set_error('Factory Name', t('Annual Return for this Factory already submitted!'));		
					}
				}
			}
			
		} else if($cust_path_pos_two == 'annual-return-common-apply') {
			$query_ar_common 	= db_select('fa_annual_return', 'ar');
			$query_ar_common	->fields('ar',array());
			$query_ar_common	->condition('ar.id', $annual_return_id, '!=');
			$result_ar_common 	= $query_ar_common->execute();
			
			$get_factory_info = get_annual_return_factory_information($annual_return_id);
			
			if($get_factory_info->cafa_id != $factory_id) {
				if($result_ar_common->rowCount() > 0) {
					while($data_ar_common = $result_ar_common->fetchObject()) {
						if($data_ar_common->cafa_id == $factory_id) {
							form_set_error('Factory Name', t('Annual Return for this Factory already submitted!'));		
						}
					}
				}
			}
		}	
	}
	
	
	function update_occupier_details_form_submit($form, &$form_state) {
		
		global $base_root, $base_path, $user;
		
		$uid = $user->uid;
		
		$factory_id = $form_state['values']['occupier_factory_id_upd'];
		$annual_return_id = $form_state['values']['occupier_annual_return_id_upd'];
		$cust_path_pos_two = $form_state['values']['occupier_cust_path_pos_two_upd'];
		
		$factory_type_id = encryption_decryption_fun('encrypt', 0);
		
		if((!empty($factory_id)) && ($factory_id != 0)) {
			
			if($annual_return_id == 0) {
				
				$annual_return_occupier = array(
					'uid' => $uid,
					//'cafa_id' => $factory_id,
					'created_date' => date('Y-m-d'),
					'name_occupier' => $form_state['values']['occupier_name_upd'],
					'pincodeoprmntadr' => $form_state['values']['pincodeoprmntadr_upd'],
					'state_oprmntadr' => $form_state['values']['state_oprmntadr_upd'],
					'district_oprmntadr' => $form_state['values']['district_oprmntadr_upd'],
					'subdivision_oprmntadr' => $form_state['values']['subdivision_oprmntadr_upd'],
					'areatype_oprmntadr' => $form_state['values']['areatype_oprmntadr_upd'],
					'block_oprmntadr' => $form_state['values']['block_oprmntadr_upd'],
					'panchayat_oprmntadr' => $form_state['values']['panchayat_oprmntadr_upd'],
					'policestation_oprmntadr' => $form_state['values']['policestation_oprmntadr_upd'],
					'postoffice_oprmntadr' => $form_state['values']['postoffice_oprmntadr_upd'], 
					'addrline_oprmntadr' => $form_state['values']['addrline_oprmntadr_upd'],
					'temp_cafa_id_occupier_data' => $factory_id,
					
				);
				
				$annual_return_id = db_insert('fa_annual_return')->fields($annual_return_occupier)->execute();
					
			} else {
			
				$annual_return_occupier = array(
					'uid' => $uid,
					//'cafa_id' => $factory_id,
					'modification_date'	   => date('Y-m-d H:i:s'),
					'name_occupier' => $form_state['values']['occupier_name_upd'],
					'pincodeoprmntadr' => $form_state['values']['pincodeoprmntadr_upd'],
					'state_oprmntadr' => $form_state['values']['state_oprmntadr_upd'],
					'district_oprmntadr' => $form_state['values']['district_oprmntadr_upd'],
					'subdivision_oprmntadr' => $form_state['values']['subdivision_oprmntadr_upd'],
					'areatype_oprmntadr' => $form_state['values']['areatype_oprmntadr_upd'],
					'block_oprmntadr' => $form_state['values']['block_oprmntadr_upd'],
					'panchayat_oprmntadr' => $form_state['values']['panchayat_oprmntadr_upd'],
					'policestation_oprmntadr' => $form_state['values']['policestation_oprmntadr_upd'],
					'postoffice_oprmntadr' => $form_state['values']['postoffice_oprmntadr_upd'], 
					'addrline_oprmntadr' => $form_state['values']['addrline_oprmntadr_upd'],
					'temp_cafa_id_occupier_data' => $factory_id,
					
				);
				
				db_update('fa_annual_return')->fields($annual_return_occupier)->condition('id', $annual_return_id, '=')->execute();	
				
			}
			
		}
		
		if($cust_path_pos_two == 'annual-return-common') {
			if($form_state['submitted']) {
				$commands[] = ctools_modal_command_dismiss();
				//$commands[] = ctools_ajax_command_reload();
				$commands[] = ctools_ajax_command_redirect('applicant/annual-return-common/'.encryption_decryption_fun('encrypt', $annual_return_id).'/'.$factory_type_id.'/'.
															encryption_decryption_fun('encrypt', $factory_id)
														);
				print ajax_render($commands);
				drupal_exit();
			}
		} else if($cust_path_pos_two == 'annual-return-common-apply') {
			if($form_state['submitted']) {
				$commands[] = ctools_modal_command_dismiss();
				//$commands[] = ctools_ajax_command_reload();
				$commands[] = ctools_ajax_command_redirect('applicant/annual-return-common-apply/default/'.encryption_decryption_fun('encrypt', $annual_return_id).'/'.	
															encryption_decryption_fun('encrypt', $factory_id)
														);
				print ajax_render($commands);
				drupal_exit();
			}
		}
		
		$form_state['rebuild'] = TRUE;
		
		drupal_set_message('Occupier\'s details updated sucessfully.');
		
	}
	
	function get_ajax_occupier_details_load($form, $form_state) {
		
		$commands   = array();
		$commands[] = ajax_command_replace('#state_oprmntadr_occupier_upd_id_replace', drupal_render($form['occupier_information']['state_oprmntadr_upd']));
		$commands[] = ajax_command_replace('#district_oprmntadr_occupier_upd_id_replace', drupal_render($form['occupier_information']['district_oprmntadr_upd']));
		$commands[] = ajax_command_replace('#subdivision_oprmntadr_occupier_upd_id_replace', drupal_render($form['occupier_information']['subdivision_oprmntadr_upd']));
		$commands[] = ajax_command_replace('#areatype_oprmntadr_occupier_upd_id_replace', drupal_render($form['occupier_information']['areatype_oprmntadr_upd']));
		$commands[] = ajax_command_replace('#block_oprmntadr_occupier_upd_id_replace', drupal_render($form['occupier_information']['block_oprmntadr_upd']));
		$commands[] = ajax_command_replace('#panchayat_oprmntadr_occupier_upd_id_replace', drupal_render($form['occupier_information']['panchayat_oprmntadr_upd']));
		$commands[] = ajax_command_replace('#policestation_oprmntadr_occupier_upd_id_replace', drupal_render($form['occupier_information']['policestation_oprmntadr_upd']));
		$commands[] = ajax_command_replace('#postoffice_oprmntadr_occupier_upd_id_replace', drupal_render($form['occupier_information']['postoffice_oprmntadr_upd']));
		return array(
			'#type' => 'ajax',
			'#commands' => $commands
		);
	}