<?php

	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	function inspection_report_occupier_details($form, &$form_state, $inspection_reportID = '', $factoryID = '', $param = '') {
	
		global $user;
		$uid = $user->uid;
		
		$inspection_report_id = encryption_decryption_fun('decrypt', $inspection_reportID);
		//$factory_type_id = encryption_decryption_fun('decrypt', $factory_typeID);
		$factory_id = encryption_decryption_fun('decrypt', $factoryID);
		
		if(empty($inspection_report_id) || $inspection_report_id == '') {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Worker Details first.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('admin/inspection-report-factories/workers-details/'.$inspection_reportID.'/'.$factoryID.'/'.encryption_decryption_fun('encrypt', NULL)) ;
		}
		
	//variable declaration
		$occupier_type = $occupier_name = $factory_pincodeoprmntadr_occupier = $factory_state_oprmntadr_occupier = $factory_district_oprmntadr_occupier = 
		$factory_subdivision_oprmntadr_occupier = $factory_areatype_oprmntadr_occupier = $factory_block_oprmntadr_occupier = $factory_panchayat_oprmntadr_occupier = 
		$factory_policestation_oprmntadr_occupier = $factory_postoffice_oprmntadr_occupier = $factory_addrline_oprmntadr_occupier = $occupier_telephone = $occupier_fax_no = 
		$occupier_email_id = $occupier_mobile = '';
	//end
		
		$get_fa_cafa 				= get_fa_cafa($factory_id);
		$factory_owershiptype		= $get_fa_cafa['factory_owershiptype'];
		
		$get_factory_info 				= get_inspection_report_factory_information($inspection_report_id);
		$factory_sector_ownership_type  = $get_factory_info->factory_sector_ownership_type;
		
		$ownership_type = !empty($factory_sector_ownership_type) ? $factory_sector_ownership_type : $factory_owershiptype;
			
		$get_occupier_value = get_reg_factory_occupier($factory_id);
		
		if($inspection_report_id != 0) {
			$get_factory_occupier_info = get_inspection_report_occupier_information($inspection_report_id);	
		}
		
	//for occupier
		if(!empty($get_occupier_value)) {
			$occupier_type								= $get_occupier_value['type_occupier'];
			$occupier_name 								= $get_occupier_value['name_occupier'];
			$factory_pincodeoprmntadr_occupier        	= $get_occupier_value['pincodeoprmntadr'];
			$factory_state_oprmntadr_occupier          	= $get_occupier_value['state_oprmntadr'];
			$factory_district_oprmntadr_occupier 	    = $get_occupier_value['district_oprmntadr'];
			$factory_subdivision_oprmntadr_occupier   	= $get_occupier_value['subdivision_oprmntadr'];
			$factory_areatype_oprmntadr_occupier       	= $get_occupier_value['areatype_oprmntadr'];
			$factory_block_oprmntadr_occupier          	= $get_occupier_value['block_oprmntadr'];
			$factory_panchayat_oprmntadr_occupier      	= $get_occupier_value['panchayat_oprmntadr'];
			$factory_policestation_oprmntadr_occupier  	= $get_occupier_value['policestation_oprmntadr'];
			$factory_postoffice_oprmntadr_occupier     	= $get_occupier_value['postoffice_oprmntadr'];
			$factory_addrline_oprmntadr_occupier		= $get_occupier_value['addrline_oprmntadr'];
			$occupier_telephone  						= $get_occupier_value['occupier_telephone'];
			$occupier_fax_no     						= $get_occupier_value['occupier_fax_no'];
			$occupier_email_id							= $get_occupier_value['occupier_email_id'];
			$occupier_mobile							= $get_occupier_value['occupier_mobile'];
		}
		
		
	//data from inspection report table
		
		if(!empty($get_factory_occupier_info)) {
			$ir_occupier_type						= $get_factory_occupier_info->occupier_type;
			$ir_occupier_name 						= $get_factory_occupier_info->occupier_name;
			$ir_pincodeoprmntadr_occupier         	= $get_factory_occupier_info->pincodeoprmntadr;
			$ir_state_oprmntadr_occupier          	= $get_factory_occupier_info->state_oprmntadr;
			$ir_district_oprmntadr_occupier 	  	= $get_factory_occupier_info->district_oprmntadr;
			$ir_subdivision_oprmntadr_occupier    	= $get_factory_occupier_info->subdivision_oprmntadr;
			$ir_areatype_oprmntadr_occupier       	= $get_factory_occupier_info->areatype_oprmntadr;
			$ir_block_oprmntadr_occupier          	= $get_factory_occupier_info->block_oprmntadr;
			$ir_panchayat_oprmntadr_occupier      	= $get_factory_occupier_info->panchayat_oprmntadr;
			$ir_policestation_oprmntadr_occupier  	= $get_factory_occupier_info->policestation_oprmntadr;
			$ir_postoffice_oprmntadr_occupier     	= $get_factory_occupier_info->postoffice_oprmntadr;
			$ir_addrline_oprmntadr_occupier		  	= $get_factory_occupier_info->addrline_oprmntadr;			
			$ir_occupier_telephone      			= $get_factory_occupier_info->occupier_telephone;
			$ir_occupier_fax_no  					= $get_factory_occupier_info->occupier_fax_no;
			$ir_occupier_email_id     				= $get_factory_occupier_info->occupier_email_id;
			$ir_occupier_mobile		  				= $get_factory_occupier_info->occupier_mobile;	
		}
		
		
		$form = array();
		
		$form['occupier_details'] = array(
			'#type' => 'fieldset',
			'#title' => t('E. Occupier Details'),
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
		
		if(!empty($ownership_type)) {
			if($ownership_type == 'pv' || $ownership_type == 'ltd') {
				$ownership_type_occupier = 'Director';
			} elseif($ownership_type == 'par_firm' || $ownership_type=='llp') {
				$ownership_type_occupier = 'Partner';
			} elseif($ownership_type == 'pro_firm') {
				$ownership_type_occupier = 'Proprietor';
			} elseif($ownership_type=='cooperative'|| $ownership_type=='registered') {
				$ownership_type_occupier = 'Nominated Occupier';
			} elseif($ownership_type == 'govt' || $ownership_type == 'psu' || $ownership_type == 'others' || $ownership_type=='localbody' ) {
				$ownership_type_occupier = 'Nominated ';
			}
		}
		
		$val_occupier_type = !empty($ir_occupier_type) ? $ir_occupier_type : $occupier_type;	
		$form['occupier_details']['occupier_type'] = array(
			'#prefix' 				=> '<div class="row"><div id="occupier_type_id"><div class="col-md-6 col-xs-4"><label class="input label-block">',
			'#suffix' 				=> '</label></div></div>',
			'#attributes' 			=> array('class' => array(),'placeholder' => 'Occupier Type','readonly' => 'readonly'),
			'#title' 			 	=> t('(i) Occupier Type'),
			'#value' 	 			=> !empty($ownership_type_occupier) ? $ownership_type_occupier : $val_occupier_type,
			'#required' 			=> TRUE,
			'#type' 				=> 'textfield',
			'#element_validate' 	=> array('element_validate_alphabatic_text'),
		);
		
		$form['occupier_details']['occupier_name'] = array(
			'#prefix' 				=> '<div id="occupier_name_id"><div class="col-md-6 col-xs-4"><label class="input label-block">',
			'#suffix' 				=> '</label></div></div>',
			'#attributes' 			=> array('class' => array(),'placeholder' => 'Occupier Name'),
			'#title' 			 	=> t('(ii) Occupier Name'),
			'#default_value' 	 	=> !empty($ir_occupier_name) ? $ir_occupier_name : $occupier_name,
			'#required' 			=> TRUE,
			'#type' 				=> 'textfield',
			'#element_validate' 	=> array('element_validate_alphabatic_fullstop'),
		);
		
	//occupier address section
		
		$pincode_oprmntadr_val = !empty($ir_pincodeoprmntadr_occupier) ? $ir_pincodeoprmntadr_occupier : $factory_pincodeoprmntadr_occupier;
		$value_pincode_oprmntadr = isset($form_state['values']['pincodeoprmntadr']) ? $form_state['values']['pincodeoprmntadr'] : $pincode_oprmntadr_val;
		$form['occupier_details']['pincodeoprmntadr']       = array(
			'#prefix' 				=> '<div id="pincodeoprmntadr_occupier_id"><div class="col-md-4 col-xs-4"><label class="input label-block">',
			'#suffix' 				=> '</label></div></div>',
			'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Pincode'),
			'#autocomplete_path' 	=> 'pinautocomplete',
			'#id' 				 	=> 'pincode_autocomplete_occupier',
			'#maxlength' 		 	=> 6,
			'#title' 			 	=> t('(iii) Pincode'),
			'#default_value' 	 	=> $pincode_oprmntadr_val,
			'#required' 			=> TRUE,
			'#type' 				=> 'textfield',
			'#element_validate' 	=> array('element_validate_numeric_positive'),
			'#ajax' 				=> array(
                                                    'effect' 	=> 'fade',
                                                    'callback' 	=> 'get_ajax_occupier_details_load_ir',
                                                    'progress' 	=> array(
                                                     'type' 	=> 'throbber',
                                                    'message' 	=> t('loading')
                    )
             )
		);
		
		if(!empty($value_pincode_oprmntadr)) {
				
			$query_pin_oprmntadr = db_select('fa_all_india_pin_code', 'p')
											->fields('p', array('districtname', 'statename', 'pincode', 'district_code', 'state_code', 'po_name'))
											->condition('p.pincode', trim($value_pincode_oprmntadr), '=');
			
			$result_pin_oprmntadr = $query_pin_oprmntadr->execute();
			if($result_pin_oprmntadr->rowcount() > 0) {
				$final_pin_oprmntadr   = $result_pin_oprmntadr->fetchAssoc();
				$pincode_v_oprmntadr   = $value_pincode_oprmntadr;
				$state_v_oprmntadr     = $final_pin_oprmntadr['state_code'];
				$district_v_oprmntadr  = $final_pin_oprmntadr['district_code'];
				$post_office_oprmntadr = $final_pin_oprmntadr['po_name'];
			}
		}
		
		$state_oprmntadr_val = !empty($ir_state_oprmntadr_occupier) ? $ir_state_oprmntadr_occupier : $factory_state_oprmntadr_occupier;
		$value_state_oprmntadr = isset($form_state['values']['state_oprmntadr']) ? $form_state['values']['state_oprmntadr'] : $state_oprmntadr_val;
		if(!empty($state_v_oprmntadr)) {
			$form['occupier_details']['state_oprmntadr'] = array(
				'#title' 		=> '(iv) State',
				'#type' 		=> 'select',
				'#id' 			=> 'state_occupier_name',
				'#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
				'#disabled' 	=> TRUE,
				'#options' 		=> get_all_state($state_v_oprmntadr),
				'#default_value'=> !empty($state_v_oprmntadr) ? $state_v_oprmntadr : $state_oprmntadr_val,
				'#required' 	=> TRUE,
				'#prefix' 		=> '<div id="state_oprmntadr_occupier_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
				'#ajax' 				=> array(
														'effect' 	=> 'fade',
														'callback' 	=> 'get_ajax_occupier_details_load_ir',
														'progress' 	=> array(
														 'type' 	=> 'throbber',
														'message' 	=> t('loading')
						)
				 )
			);
		} else {
			$form['occupier_details']['state_oprmntadr'] = array(
				'#title' 		=> '(iv) State',
				'#type' 		=> 'select',
				'#id' 			=> 'state_occupier_name',
				'#attributes' 	=> array('class' => array(''),'placeholder' => 'State','disabled' => 'disabled'),
				'#disabled' 	=> TRUE,
				'#options' => array(
					'' => t('Select State')
				),
				//'#value' 	 	=> '',
				'#required' 	=> TRUE,
				'#prefix' 		=> '<div id="state_oprmntadr_occupier_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);
		}
		
		$district_oprmntadr_val = !empty($ir_district_oprmntadr_occupier) ? $ir_district_oprmntadr_occupier : $factory_district_oprmntadr_occupier;
		$value_district_oprmntadr = isset($form_state['values']['district_oprmntadr']) ? $form_state['values']['district_oprmntadr'] : $district_oprmntadr_val;
		if(!empty($state_v_oprmntadr)) {
			$form['occupier_details']['district_oprmntadr'] = array(
				'#title' => '(v) District',
				'#type' => 'select',
				'#id' => 'district_occupier_name',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
				'#options' => get_district_by_id($state_v_oprmntadr),
				'#value' 	=> !empty($district_v_oprmntadr) ? $district_v_oprmntadr : $district_oprmntadr_val,
				'#required' => TRUE,
				'#prefix' => '<div id="district_oprmntadr_occupier_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
				'#ajax' 				=> array(
															'effect' 	=> 'fade',
															'callback' 	=> 'get_ajax_occupier_details_load_ir',
															'progress' 	=> array(
															 'type' 	=> 'throbber',
															'message' 	=> t('loading')
							)
				 )
			);
		} else {
			$form['occupier_details']['district_oprmntadr'] = array(
				'#title' => '(v) District',
				'#type' => 'select',
				'#id' => 'district_occupier_name',
				'#disabled' => TRUE,
				'#attributes' => array('class' => array('' ),'placeholder' => 'District','disabled' => 'disabled'),
				'#options' => array(
					'' => t('Select District')
				),
				//'#value' 	 	=> '',
				'#required' => TRUE,
				'#prefix' => '<div id="district_oprmntadr_occupier_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);
		}
		
		$sub_division_oprmntadr_val = !empty($ir_subdivision_oprmntadr_occupier) ? $ir_subdivision_oprmntadr_occupier : $factory_subdivision_oprmntadr_occupier;
		$value_subdivision_oprmntadr = isset($form_state['values']['subdivision_oprmntadr']) ? $form_state['values']['subdivision_oprmntadr'] : $sub_division_oprmntadr_val;
		if(!empty($district_v_oprmntadr) && !empty($state_v_oprmntadr)) {
			$form['occupier_details']['subdivision_oprmntadr'] = array(
				'#title' => '(vi) Sub-Division',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'Sub Division'),
				'#options' => common_custom_user_subdivisionlist_list_new($district_v_oprmntadr),
				'#required' => TRUE,
				'#default_value' 	=> $sub_division_oprmntadr_val,
				'#prefix' => '<div id="subdivision_oprmntadr_occupier_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
				'#ajax' 				=> array(
															'effect' 	=> 'fade',
															'callback' 	=> 'get_ajax_occupier_details_load_ir',
															'progress' 	=> array(
															 'type' 	=> 'throbber',
															'message' 	=> t('loading')
							)
				 )
			);
		} else {
			$form['occupier_details']['subdivision_oprmntadr'] = array(
				'#title' => '(vi) Sub-Division',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'Sub Division'),
				'#options' => array(
					'' => t('Select Sub-Division')
				),
				'#required' => TRUE,
				'#prefix' => '<div id="subdivision_oprmntadr_occupier_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);	
		}
		
		$area_type_oprmntadr_val = !empty($ir_areatype_oprmntadr_occupier) ? $ir_areatype_oprmntadr_occupier : $factory_areatype_oprmntadr_occupier;
		$value_areatype_oprmntadr = isset($form_state['values']['areatype_oprmntadr']) ? $form_state['values']['areatype_oprmntadr'] : $area_type_oprmntadr_val;
		if(!empty($value_district_oprmntadr) && !empty($value_state_oprmntadr) && !empty($value_subdivision_oprmntadr)) {
			$form['occupier_details']['areatype_oprmntadr'] = array(
				'#title' => '(vii) Area Type',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'Area Type'),
				'#options' => common_custom_user_areatype_list_new($value_district_oprmntadr, $value_subdivision_oprmntadr),
				'#required' => TRUE,
				'#default_value' 	=> $area_type_oprmntadr_val,
				'#prefix' => '<div id="areatype_oprmntadr_occupier_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
				'#ajax' 				=> array(
																'effect' 	=> 'fade',
																'callback' 	=> 'get_ajax_occupier_details_load_ir',
																'progress' 	=> array(
																 'type' 	=> 'throbber',
																'message' 	=> t('loading')
								)
				 )
			);
		} else {
			$form['occupier_details']['areatype_oprmntadr'] = array(
				'#title' => '(vii) Area Type',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'Area Type'),
				'#options' => array(
					'0' => t('Select Area Type')
				),
				'#required' => TRUE,
				'#prefix' => '<div id="areatype_oprmntadr_occupier_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
			);	
		}
		
		if(!empty($value_district_oprmntadr) && !empty($value_state_oprmntadr) && !empty($value_subdivision_oprmntadr) && !empty($value_areatype_oprmntadr)) {
			if($value_areatype_oprmntadr == 'B') {
				$areatype_name_oprmntadr = 'Block';
			} elseif($value_areatype_oprmntadr == 'M') {
				$areatype_name_oprmntadr = 'Municipality';
			} elseif($value_areatype_oprmntadr == 'C') {
				$areatype_name_oprmntadr = 'Corporation';
			} elseif($value_areatype_oprmntadr == 'S') {
				$areatype_name_oprmntadr = 'SEZ';
			} elseif($value_areatype_oprmntadr == 'N') {
				$areatype_name_oprmntadr = 'Notified Area';
			}
		
			$block_oprmntadr_val = !empty($ir_block_oprmntadr_occupier) ? $ir_block_oprmntadr_occupier : $factory_block_oprmntadr_occupier;
			$value_block_oprmntadr = isset($form_state['values']['block_oprmntadr']) ? $form_state['values']['block_oprmntadr'] : $block_oprmntadr_val;		
			$form['occupier_details']['block_oprmntadr'] = array(
				'#title' 		=> '(viii) '. $areatype_name_oprmntadr,
				'#type'         => 'select',
				'#attributes'   => array('class' => array(''),'placeholder' => 'Block'),
				'#options' 		=> common_custom_user_block_list_new($value_subdivision_oprmntadr, $value_areatype_oprmntadr),
				'#required' 	=> TRUE,
				'#default_value'=> $block_oprmntadr_val,
				'#prefix' 		=> '<div id="block_oprmntadr_occupier_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
				'#ajax' 		=> array(
											'effect' 	=> 'fade',
											'callback' 	=> 'get_ajax_occupier_details_load_ir',
											'progress' 	=> array(
											 'type' 	=> 'throbber',
											'message' 	=> t('loading')
								)
				 )
			);
		} else {
			$form['occupier_details']['block_oprmntadr'] = array(
				'#title' 		=> '(viii) Block / Municipality / Corporation / Notified Area / SEZ',
				'#type'         => 'select',
				'#attributes'   => array('class' => array(''),'placeholder' => 'Block'),
				'#options' => array(
					'0' => t('Select Block / Municipality / Corporation / Notified Area / SEZ')
				),
				'#required' 	=> TRUE,
				'#prefix' 		=> '<div id="block_oprmntadr_occupier_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
			);	
		}
		
		if(!empty($value_district_oprmntadr) && !empty($value_subdivision_oprmntadr) && !empty($value_areatype_oprmntadr) && !empty($value_block_oprmntadr) && !empty($value_state_oprmntadr)) {
			
			if ($value_areatype_oprmntadr == 'B') {
				$areatype_name_oprmntadr = 'Gram Panchayat';
				$area_code_oprmntadr = 'V';
			} elseif($value_areatype_oprmntadr == 'M') {
				$areatype_name_oprmntadr = 'Ward';
				$area_code_oprmntadr = 'W';
			} elseif($value_areatype_oprmntadr == 'C') {
				$areatype_name_oprmntadr = 'Ward';
				$area_code_oprmntadr = 'C';
			} elseif($value_areatype_oprmntadr == 'S') {
				$areatype_name_oprmntadr = 'Sector';
				$area_code_oprmntadr = 'S';
			} elseif($value_areatype_oprmntadr == 'N') {
				$areatype_name_oprmntadr = 'Notified Area';
				$area_code_oprmntadr = 'N';
			}
			
			$panchayat_oprmntadr_val = !empty($ir_panchayat_oprmntadr_occupier) ? $ir_panchayat_oprmntadr_occupier : $factory_panchayat_oprmntadr_occupier;
			$value_panchayat_oprmntadr = isset($form_state['values']['panchayat_oprmntadr']) ? $form_state['values']['panchayat_oprmntadr'] : $panchayat_oprmntadr_val;
			$form['occupier_details']['panchayat_oprmntadr'] = array(
				'#title' => '(ix) '.$areatype_name_oprmntadr,
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'panchayat'),
				'#options' => common_custom_user_villward_list_new($value_block_oprmntadr, $area_code_oprmntadr),
				'#default_value' 	    => $panchayat_oprmntadr_val,
				'#prefix' => '<div id="panchayat_oprmntadr_occupier_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
				'#required' => TRUE,
				'#ajax' 		=> array(
											'effect' 	=> 'fade',
											'callback' 	=> 'get_ajax_occupier_details_load_ir',
											'progress' 	=> array(
											 'type' 	=> 'throbber',
											'message' 	=> t('loading')
								)
				 )
			);
		} else {
			$form['occupier_details']['panchayat_oprmntadr'] = array(
				'#title' => '(ix) Gram Panchayat / Ward / Sector',
				'#type' => 'select',
				'#attributes' => array('class' => array(''),'placeholder' => 'panchayat'),
				'#options' => array(
					'0' => t('Select Gram Panchayat / Ward / Sector / Notified Area')
				),
				'#prefix' => '<div id="panchayat_oprmntadr_occupier_id_replace"><div class="col-md-6 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>',
				'#required' => TRUE,
			);	
		}
		
		if(!empty($value_district_oprmntadr)) {
			$form['occupier_details']['policestation_oprmntadr'] = array(
				'#title' => '(x) Police Station',
				'#type' => 'select',
				'#attributes' => array('class' => array( ''),'placeholder' => 'Police Station'),
				'#options' => common_custom_user_ps_list_new($value_district_oprmntadr),
				'#required' => TRUE,
				'#default_value' 	    => !empty($ir_policestation_oprmntadr_occupier) ? $ir_policestation_oprmntadr_occupier : $factory_policestation_oprmntadr_occupier,
				'#prefix' => '<div id="policestation_oprmntadr_occupier_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
		} else {
			$form['occupier_details']['policestation_oprmntadr'] = array(
				'#title' => '(x) Police Station',
				'#type' => 'select',
				'#attributes' => array('class' => array( ''),'placeholder' => 'Police Station'),
				'#options' => array(
					'0' => t('Select Police Station')
				),
				'#required' => TRUE,
				'#prefix' => '<div id="policestation_oprmntadr_occupier_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);	
		}
		
		if(!empty($value_pincode_oprmntadr)) {
			$form['occupier_details']['postoffice_oprmntadr'] = array(
				'#title' => '(xi) Post Office',
				'#type' => 'select',
				'#attributes' => array('class' => array(''), 'placeholder' => 'Post Office'),
				'#options' => common_custom_post_office_list_new($value_pincode_oprmntadr),
				'#default_value' 	    => !empty($ir_postoffice_oprmntadr_occupier) ? $ir_postoffice_oprmntadr_occupier : $factory_postoffice_oprmntadr_occupier,
				'#required' => TRUE,
				'#prefix' => '<div id="postoffice_oprmntadr_occupier_id_replace"><div class="col-md-4 col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
		} else {
			$form['occupier_details']['postoffice_oprmntadr'] = array(
				'#title' => '(xi) Post Office',
				'#type' => 'select',
				'#attributes' => array('class' => array(''), 'placeholder' => 'Post Office'),
				'#options' => array(
					'0' => t('Select Post Office')
				),
				'#required' => TRUE,
				'#prefix' => '<div id="postoffice_oprmntadr_occupier_id_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);	
		}
		
		$form['occupier_details']['addrline_oprmntadr'] = array(
			'#prefix' => '<div id="addrline_oprmntadr_occupier_id"><div class="col-md-12 col-xs-4"><label class="textarea label-block">',
			'#suffix' => '</label></div></div>',
			'#title' => '(xii) Address',
			'#rows' => 3,
			'#type' => 'textarea',
			'#required' => TRUE,
			'#default_value' 	    => !empty($ir_addrline_oprmntadr_occupier) ? $ir_addrline_oprmntadr_occupier : $factory_addrline_oprmntadr_occupier,
			'#attributes' => array('class' => array(''),'placeholder' => 'Address Line'),
			'#element_validate' => array('element_validate_streetaddress'), 
		);
		
		$form['occupier_details']['occupier_telephone'] = array(
			'#prefix' 				=> '<div id="occupier_telephone_id"><div class="col-md-4 col-xs-4"><label class="input label-block">',
			'#suffix' 				=> '</label></div></div>',
			'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Occupier Telephone No.'),
			'#title' 			 	=> t('(xiii) Occupier Telephone No.'),
			'#maxlength' 		 	=> 15,
			'#default_value' 	 	=> !empty($ir_occupier_telephone) ? $ir_occupier_telephone : $occupier_telephone,
			'#required' 			=> TRUE,
			'#type' 				=> 'textfield',
			'#element_validate' 	=> array('element_validate_telephoneno'),
		);
		
		$form['occupier_details']['occupier_fax_no'] = array(
			'#prefix' 				=> '<div id="occupier_fax_no_id"><div class="col-md-4 col-xs-4"><label class="input label-block">',
			'#suffix' 				=> '</label></div></div>',
			'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Occupier Fax No.'),
			'#title' 			 	=> t('(xiv) Occupier Fax No.'),
			'#maxlength' 		 	=> 15,
			'#default_value' 	 	=> !empty($ir_occupier_fax_no) ? $ir_occupier_fax_no : $occupier_fax_no,
			//'#required' 			=> TRUE,
			'#type' 				=> 'textfield',
			'#element_validate' 	=> array('element_validate_telephoneno'),
		);
		
		$form['occupier_details']['occupier_email_id'] = array(
			'#prefix' 				=> '<div id="occupier_emailid_id"><div class="col-md-4 col-xs-4"><label class="input label-block">',
			'#suffix' 				=> '</label></div></div>',
			'#attributes' 			=> array('class' => array(),'placeholder' => 'Occupier Email ID'),
			'#title' 			 	=> t('(xv) Occupier Email ID'),
			'#default_value' 	 	=> !empty($ir_occupier_email_id) ? $ir_occupier_email_id : $occupier_email_id,
			'#required' 			=> TRUE,
			'#type' 				=> 'textfield',
			'#element_validate' 	=> array('element_validate_email'),
		);
		
		$form['occupier_details']['occupier_mobile'] = array(
			'#prefix' 				=> '<div id="occupier_mobile_id"><div class="col-md-4 col-xs-4"><label class="input label-block">',
			'#suffix' 				=> '</label></div></div></div>',
			'#attributes' 			=> array('class' => array('numeric_positive'),'placeholder' => 'Occupier Mobile No.'),
			'#title' 			 	=> t('(xvi) Occupier Mobile No.'),
			'#maxlength' 		 	=> 10,
			'#default_value' 	 	=> !empty($ir_occupier_mobile) ? $ir_occupier_mobile : $occupier_mobile,
			'#required' 			=> TRUE,
			'#type' 				=> 'textfield',
			'#element_validate' 	=> array('element_validate_mobile'),
		);
			
//occupier address section end
		
		
		
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'admin/inspection-report-factories/workers-details/'.$inspection_reportID.'/'.$factoryID.'/'.encryption_decryption_fun('encrypt', NULL), array(
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
	
	
	function inspection_report_occupier_details_validate($form, &$form_state) {
		
		
		
	}
	
	
	function inspection_report_occupier_details_submit($form, &$form_state){
		//echo '<pre>'; print_r($form_state); die();
		
		global $base_root,$base_path,$user;
		
		$uid 							= $user->uid;
		
		$inspection_report_id = $form_state['values']['inspection_report_id'];
		
		$factory_id = $form_state['values']['factory_id'];
		
		$val = $form_state['values'];
		
		if($factory_id != 0) {
			
			if($inspection_report_id != 0) {
				
				$inspection_report_ID = $inspection_report_id;
				
				$inspection_report_occupier = array(
					
					'occupier_type'   				=> $val['occupier_type'],
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
					'occupier_telephone'			=> $val['occupier_telephone'],
					'occupier_fax_no'				=> $val['occupier_fax_no'],
					'occupier_email_id'				=> $val['occupier_email_id'],
					'occupier_mobile'				=> $val['occupier_mobile'],
					
					'uid' 							=> $uid,
					'modification_date'	   			=> date('Y-m-d H:i:s'),
					
				);
				
				db_update('fa_inspection_report')->fields($inspection_report_occupier)->condition('id', $inspection_report_ID, '=')->execute();	
					
			}
			
		} 
		
		//die($inspection_report_ID);
		drupal_goto('admin/inspection-report-factories/manager-details/'.encryption_decryption_fun('encrypt', $inspection_report_ID).'/'.encryption_decryption_fun('encrypt', $factory_id).'/'.encryption_decryption_fun('encrypt', NULL));
	  
		$form_state['rebuild'] = true;
		
		
	}