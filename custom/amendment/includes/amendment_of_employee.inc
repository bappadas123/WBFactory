<?php
function amendment_of_employee($form, &$form_state,$applicationid,$serviceid,$factory_typeid,$referenceno) {	
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	global $base_root, $base_path, $user;
	$userid 			= $user->uid;
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	$reference_number 	= encryption_decryption_fun('decrypt', $referenceno);
	//echo $application_id;die;
	$get_fa_cafa 				= get_fa_cafa($application_id);
	$is_year_calculation_tab    = $get_fa_cafa['is_year_calculation_tab'];
	$ownership_type 			= $get_fa_cafa['factory_owershiptype'];
	$application_status			= $get_fa_cafa['application_status'];
	$lists 						= year_list($application_id,$factory_type_id,$userid);
	
	if ($get_fa_cafa['application_status']=='In') {
		
	$amendment_checking = get_amendment_checking($application_id,$service_id,$factory_type_id,$reference_number);
	$verify_details = !empty($amendment_checking['fieldname'])? $amendment_checking['fieldname'] : ''; 
	
	
	$str = "manager_details,director_details";
	$fields = removeFromString($str,$amendment_checking['fieldname']);
	$remark_field = explode(',', $fields);
	foreach ($remark_field as $fieldname){
			if($fieldname == 'manager_details'){ $manager_details_ck = "disabled";}
   			if($fieldname == 'director_details'){ $director_details_ck = "disabled";}
			
			}
		}
	if(in_array("manager_details", $remark_field)) { $manager_check_data = '<i class="fa fa-check text-green verified"></i>'; $manager_field_value= 'blank'; }
	else {  $manager_check_data = '<i class="fa fa-edit text-red verified"></i>'; $manager_field_value= "manager_details";}
		
	if(in_array("director_details", $remark_field)) { $director_check_data = '<i class="fa fa-check text-green verified"></i>'; $director_field_value= 'blank'; }
	else {  $director_check_data = '<i class="fa fa-edit text-red verified"></i>'; $director_field_value= "director_details";}
	
	
	$form 					= array();
	$form['serviceid'] 		= array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $serviceid,
	);
	$form['factorytypeid_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $factory_typeid
	);
	$form['application_reference_no'] = array(
		'#type' 		 	=> 'hidden',
		'#default_value' 	=> encryption_decryption_fun('encrypt', $reference_number)
	);
	$form['applicationid'] 	= array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $applicationid
	);	
	

	//////////////Start Form/////////////////////
	$form['header']	= array(
		'#markup'	=> t('<div class="content">')
	);	
	$form['manager_details'] = array(
		'#type' 		=> 'fieldset',
		'#title' 		=> t('K. Details of manager or Directors Permanent/Present Address '),
		'#collapsible' 	=> TRUE, // Added
		'#collapsed' 	=> FALSE,  // Added
	);	
	$form['manager_details']['manager_field_value'] = array(
		//'#type' 			=> 'textfield',
		//'#type' 			=> 'hidden',
		'#value' 			=> $manager_field_value,
		'#attributes' 		=> array('class' => array('')),
	);
	if(!empty($manager_details_ck)){
		$form['manager_details']['application_manager_amendment'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4"><label class="input label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t('Application Period'),
			'#type' 			=> 'select',
			'#required' 		=> TRUE,
			'#options' 			=> $lists,
			
		);
	}
	$form['manager_details']['employee_type'] 	= array(
		'#prefix'	=> '<div class="row"><div class="col-lg-4 col-md-4 col-sm-12 col-xs-12"><label class="select label-block">'.$manager_check_data.'(i).Employee Type<span id=\'star\' class="form-required">*</span>',
		'#suffix' 	=> '</label></div>',
		'#type' 	=> 'select',
		'#options' 	=> array(''=>'--SELECT--','1'=>'Director','2'=>'Manager'),
		'#attributes' 		=> array('class' => array(''),$manager_details_ck=>$manager_details_ck),
		'#ajax' 	=> array('event' => 'change','effect' => 'fade','callback' => 'get_ajax_ownership_type','progress' => array('type' => 'throbber','message' => t('loading')))
	);
	$form['manager_details']['ownership_type']  = array(
		'#type' => 'hidden',
		'#default_value' => $ownership_type
	);
	$form['manager_details']['name_manager'] 	= array(
		'#prefix' 	=> '<div class="col-lg-4 col-md-4 col-sm-12 col-xs-12"><label class="input label-block">(ii).Name of Directors/Partners/Proprietor/Manager<span id=\'star\' class="form-required">*</span>',
		'#suffix' 	=> '</label></div>',			 
		'#type' 	=> 'textfield', 
	);
	
	$form['manager_details']['director_din'] = array(
		'#prefix' 	=> '<div id="ld_show_din">',
		'#suffix'	=> '</div>',
	);
	$get_employee_type   = isset($form_state['values']['employee_type']) ? $form_state['values']['employee_type'] : '';
	if($get_employee_type == 1){
		if($ownership_type == 'pv' || $ownership_type == 'ltd'){
			$form['manager_details']['director_din'] 	= array(
			  '#prefix'	=> '<div class="col-lg-4 col-md-4 col-sm-12 col-xs-12" id="ld_show_din"><label class="input label-block">(ii)(a).DIN No.<span id=\'star\' class="form-required">*</span>',
			  '#suffix'	=> '</label></div>',			 
			  '#type' 	=> 'textfield', 
			);
		}
	}

	$form['manager_details']['age_manager'] 	= array(
		'#prefix' 	=> '<div class="col-md-4 col-xs-12"><label class="input label-block">(iii).Age<span id=\'star\' class="form-required">*</span>',
		'#suffix'	=> '</label></div>',
		'#type'		=> 'textfield',
	);
	$form['manager_details']['father_husband_type_manager'] 	= array(
		'#prefix'	=> '<div class="col-md-4 col-xs-12"><label class="select label-block">(iv).Relationship<span id=\'star\' class="form-required">*</span>',
		'#suffix' 	=> '</label></div>', 
		'#type' 	=> 'select',
		'#options' 	=> array(''=>'Select','1'=>'D/O','2'=>'S/0',3=>'W/O'), 
	);
	$form['manager_details']['father_husband_name_manager'] 	= array(
		'#prefix' 	=> '<div class="col-md-4 col-xs-12"><label class="input label-block">(v).Father / Husband Name<span id=\'star\' class="form-required">*</span>',
		'#suffix' 	=> '</label></div>',
		'#type' 	=> 'textfield',	   
	);
	$form['manager_details']['manager_residential_pincode'] 	= array(
		'#prefix' 				=> '<div class="col-md-4 col-xs-12"><label class="input label-block">(vi).Pincode<span id=\'star\' class="form-required">*</span>',
		'#suffix' 				=> '</label></div>',
		'#attributes' 			=> array('class'=>array(''), 'placeholder'=>'Pincode'),
		'#autocomplete_path' 	=> 'pinautocomplete',
		'#id'					=> 'pincode_res_manager_residential_autocomplete',
		'#maxlength' 			=> 6, 
		'#type' 				=> 'textfield',
		'#ajax'					=> array(
										'effect' 		=> 'fade',			
										'callback'		=> 'get_manager_residential_ajax_load',
										'progress'		=>	array(
										'type'			=>'throbber',
										'message'		=>t('loading'),
										),
									)
	);
	$form['manager_details']['manager_residential_state'] 	= array(
		'#prefix' 			=> '<div id="manager_residential_state_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(vii).State<span id=\'star\' class="form-required">*</span>',
		'#suffix' 			=> '</label></div></div>',
		'#type' 			=> 'select',
		'#options' 			=> array(''=>t('Select State')),
		'#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),		
	);
	$form['manager_details']['manager_residential_district'] 	= array(
		'#prefix' 			=> '<div id="manager_residential_dis_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(viii).District<span id=\'star\' class="form-required">*</span>',
		'#suffix' 			=> '</label></div></div>',
		'#type' 			=> 'select',
		'#attributes' 		=> array('class'=>array(''), 'placeholder'=>'District', 'readonly' => 'readonly'),
		'#options' 			=> array(''=>t('Select District')),	
	);
	$form['manager_details']['manager_residential_sub_division'] 	= array(
		'#prefix' 			=> '<div id="manager_residential_sub_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(ix).Sub-Division<span id=\'star\' class="form-required">*</span>',
		'#suffix' 			=> '</label></div></div>',
		'#type' 			=> 'select',
		'#attributes' 		=> array('class'=>array(''), 'placeholder'=>'Select Sub-Division', 'readonly' => 'readonly'),
		'#options' 			=> array(''=>t('Select Sub-Division')),	
	);
	$form['manager_details']['manager_residential_area_type'] 	= array(
		'#prefix' 			=> '<div id="manager_residential_area_type_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(x).Area Type<span id=\'star\' class="form-required">*</span>',
		'#suffix' 			=> '</label></div></div>',
		'#type' 			=> 'select',
		'#attributes' 		=> array('class'=>array(''), 'placeholder'=>'Select Area Type', 'readonly' => 'readonly'),
		'#options' 			=> array(''=>t('Select Area Type')),		
	);
	$form['manager_details']['manager_residential_area_details'] 	= array(
		'#prefix' 			=> '<div id="manager_residential_area_details_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(xi).Block / Municipality / Corporation / SEZ / Notified<span id=\'star\' class="form-required">*</span>',
		'#suffix' 			=> '</label></div></div>',
		'#type' 			=> 'select',
		'#attributes' 		=> array('class'=>array(''), 'placeholder'=>'Select Block / Municipality / Corporation / SEZ / Notified', 'readonly' => 'readonly'),
		'#options' 			=> array(''=>t('Select Block / Municipality / Corporation / SEZ / Notified')),  
	);
	$form['manager_details']['manager_residential_area_division'] 	= array(
		'#prefix' 			=> '<div id="manager_residential_area_division_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(xii).Gram Panchayat / Ward / Sector / Notified Area<span id=\'star\' class="form-required">*</span>',
		'#suffix' 			=> '</label></div></div>',
		'#type' 			=> 'select', 
		'#attributes' 		=> array('class'=>array(''), 'placeholder'=>'Select Gram Panchayat / Ward / Sector / Notified Area', 'readonly' => 'readonly'),
		'#options' 			=> array(''=>t('Select Gram Panchayat / Ward / Sector / Notified Area')),
	);
	$form['manager_details']['manager_residential_ps'] 	= array(
		'#prefix' 			=> '<div id="manager_residential_ps_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(xiii).Police Station<span id=\'star\' class="form-required">*</span>',
		'#suffix' 			=> '</label></div></div>',
		'#type' 			=> 'select',
		'#attributes' 		=> array('class'=>array(''), 'placeholder'=>'Select Police Station', 'readonly' => 'readonly'),
		'#options' 			=> array(''=>t('Select Police Station')),  
	);
	$form['manager_details']['manager_residential_postoffice'] 	= array(
		'#prefix' 			=> '<div id="manager_residential_po_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(xiv).Post Office<span id=\'star\' class="form-required">*</span>',
		'#suffix' 			=> '</label></div></div>',
		'#type' 			=> 'select',
		'#attributes' 		=> array('class'=>array(''), 'placeholder'=>'Post Office', 'readonly' => 'readonly'),	  
	);
	$value_manager_residential_pincode	= isset($form_state['values']['manager_residential_pincode'])? $form_state['values']['manager_residential_pincode'] : '';
	if(!empty($value_manager_residential_pincode)){
		$get_all_data_with_pincode 	= 	get_all_data_with_pincode($value_manager_residential_pincode);
		$state_res_code 			= 	$get_all_data_with_pincode['state_code'];
		$dis_res_code 				= 	$get_all_data_with_pincode['district_code'];
		$pin_id_po_res 				= 	$get_all_data_with_pincode['id'];
		$is_state_exists 			= 	is_state_exists($state_res_code);
		$is_po_exists 				= 	is_po_exists($value_manager_residential_pincode);
	
	if($is_state_exists>0){
		$form['manager_details']['manager_residential_state'] 	= array(
			 '#prefix' 			=> '<div id="manager_residential_state_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(vii).State<span id=\'star\' class="form-required">*</span>',
			  '#suffix' 		=> '</label></div></div>',
			  '#type' 			=> 'select',
			  '#options' 		=> get_all_statecode($state_res_code),
			  '#value'			=> !empty($state_res_code) ? $state_res_code	:'',
			  '#ajax'			=> array('effect' 		=> 'fade',			
										'callback'		=> 'get_manager_residential_ajax_load',
										'progress'		=>	array(
										'type'			=>'throbber',
										'message'		=>t('loading'),
										),
									)
		);
		$value_manager_residential_state_code = !isset($form_state['values']['manager_residential_state'])? $form_state['values']['manager_residential_state'] :$state_res_code;
		$is_dis_exists = is_dis_exists($value_manager_residential_state_code,$dis_res_code);
		if($is_dis_exists>0){
			$form['manager_details']['manager_residential_district'] 	= array(
				  '#prefix' 			=> '<div id="manager_residential_dis_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(viii).District<span id=\'star\' class="form-required">*</span>',
				  '#suffix' 			=> '</label></div></div>',
				  '#type' 				=> 'select',
				  '#options' 			=> get_all_districtcode_withstate($value_manager_residential_state_code,$dis_res_code),
				  '#value'			   	=> !empty($dis_res_code) ? $dis_res_code	:'',
				  '#ajax'				=> array(
												'effect' 		=> 'fade',			
												'callback'		=> 'get_manager_residential_ajax_load',
												'progress'		=>	array(
												'type'			=>'throbber',
												'message'		=>t('loading'),
												),
											)
			);
		$value_manager_residential_dis_code = !isset($form_state['values']['manager_residential_district'])? $form_state['values']['manager_residential_district'] :$dis_res_code;
		$is_sub_exists = 	is_sub_exists($value_manager_residential_dis_code);
		if($is_sub_exists>0){
			$form['manager_details']['manager_residential_sub_division'] 	= array(
				  '#prefix'		=> '<div id="manager_residential_sub_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(ix).Sub-Division<span id=\'star\' class="form-required">*</span>',
				  '#suffix' 	=> '</label></div></div>',
				  '#type' 		=> 'select',
				  '#options' 	=> get_all_subdivcode_withdis($value_manager_residential_dis_code),
				  '#ajax'		=> array('effect'	=> 'fade',			
										'callback'	=> 'get_manager_residential_ajax_load',
										'progress'	=>	array(
										'type'		=>'throbber',
										'message'	=>t('loading'),
										),
									)
			);
			$value_manager_residential_sub_code = isset($form_state['values']['manager_residential_sub_division'])? $form_state['values']['manager_residential_sub_division'] :'';
		 	$is_areatype_exists = is_areatype_exists($value_manager_residential_dis_code, $value_manager_residential_sub_code);
			if($is_areatype_exists>0){
				$form['manager_details']['manager_residential_area_type'] 	= array(
					'#prefix'	=> '<div id="manager_residential_area_type_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(x).Area Type<span id=\'star\' class="form-required">*</span>',
					'#suffix' 	=> '</label></div></div>',
					'#type' 	=> 'select',
					'#options' 	=> get_areatype_with_sub_dis($value_manager_residential_dis_code, $value_manager_residential_sub_code),
					'#ajax'		=> array('effect' 	=> 'fade',			
										'callback'	=> 'get_manager_residential_ajax_load',
										'progress'	=>	array(
										'type'		=>'throbber',
										'message'	=>t('loading'),
										),
									)
					  
				);
				$value_manager_residential_area_type_code = isset($form_state['values']['manager_residential_area_type'])? $form_state['values']['manager_residential_area_type']:'';
				if($value_manager_residential_area_type_code=='B'){
					$form['manager_details']['manager_residential_area_details'] 	= array(
						'#prefix'	=> '<div id="manager_residential_area_details_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(xi).Block<span id=\'star\' class="form-required">*</span>',
						'#suffix' 	=> '</label></div></div>',
						'#type' 	=> 'select',
						'#options'	=> get_block_municipality_other($value_manager_residential_sub_code, $value_manager_residential_area_type_code),   
						'#ajax'		=> array('effect' 		=> 'fade',			
											'callback'		=> 'get_manager_residential_ajax_load',
											'progress'		=>	array(
											'type'			=>'throbber',
											'message'		=>t('loading'),
											),
										)
					);
				}if($value_manager_residential_area_type_code=='C'){
					$form['manager_details']['manager_residential_area_details'] 	= array(
						  '#prefix'		=> '<div id="manager_residential_area_details_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(xi).Corporation<span id=\'star\' class="form-required">*</span>',
						  '#suffix' 	=> '</label></div></div>',
						  '#type' 		=> 'select',
						  '#options'	=> get_block_municipality_other($value_manager_residential_sub_code, $value_manager_residential_area_type_code),
						  '#ajax'		=> array(
													'effect' 		=> 'fade',			
													'callback'		=> 'get_manager_residential_ajax_load',
													'progress'		=>	array(
													'type'			=>'throbber',
													'message'		=>t('loading'),
													),
											)
					);
				}if($value_manager_residential_area_type_code=='M'){
					$form['manager_details']['manager_residential_area_details'] 	= array(
						  '#prefix'		=> '<div id="manager_residential_area_details_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(xi).Municipality<span id=\'star\' class="form-required">*</span>',
						  '#suffix' 	=> '</label></div></div>',
						  '#type' 		=> 'select',
						  '#options' 	=> get_block_municipality_other($value_manager_residential_sub_code, $value_manager_residential_area_type_code),
						  '#ajax'		=> array('effect' 		=> 'fade',			
												'callback'		=> 'get_manager_residential_ajax_load',
												'progress'		=>	array(
												'type'			=>'throbber',
												'message'		=>t('loading'),
												),
											)
					);
				}if($value_manager_residential_area_type_code=='S'){
					$form['manager_details']['manager_residential_area_details'] 	= array(
						  '#prefix'		=> '<div id="manager_residential_area_details_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(xi).SEZ<span id=\'star\' class="form-required">*</span>',
						  '#suffix' 	=> '</label></div></div>',
						  '#type' 		=> 'select',
						  '#options' 	=> get_block_municipality_other($value_manager_residential_sub_code, $value_manager_residential_area_type_code),
						  '#ajax'		=> array('effect' 		=> 'fade',			
												'callback'		=> 'get_manager_residential_ajax_load',
												'progress'		=>	array(
												'type'			=>'throbber',
												'message'		=>t('loading'),
												),
											)
					);
				}if($value_manager_residential_area_type_code=='N'){
					$form['manager_details']['manager_residential_area_details'] 	= array(
						  '#prefix'		=> '<div id="manager_residential_area_details_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(xi).Notified<span id=\'star\' class="form-required">*</span>',
						  '#suffix' 	=> '</label></div></div>',
						  '#type' 		=> 'select',
						  '#options' 	=> get_block_municipality_other($value_manager_residential_sub_code, $value_manager_residential_area_type_code),
						  '#ajax'		=> array('effect' 		=> 'fade',			
												'callback'		=> 'get_manager_residential_ajax_load',
												'progress'		=>	array(
												'type'			=>'throbber',
												'message'		=>t('loading'),
												),
											)
					);
				}
				$value_manager_residential_area_details_code = isset($form_state['values']['manager_residential_area_details'])? $form_state['values']['manager_residential_area_details'] :'';
				$is_block_mun_vill_exists = 1;
				if($is_block_mun_vill_exists>0){
					if($value_manager_residential_area_type_code == 'B'){
						$form['manager_details']['manager_residential_area_division'] 	= array(
							'#prefix' 			=> '<div id="manager_residential_area_division_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(xii).Gram Panchayat<span id=\'star\' class="form-required">*</span>',
							'#suffix' 			=> '</label></div></div>',  
							'#type' 			=> 'select', 
							'#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),		
							'#options'			=>  get_full_villward($value_manager_residential_area_details_code,'V'),
						);
					}if($value_manager_residential_area_type_code=='M'){
							$form['manager_details']['manager_residential_area_division'] 	= array(
								'#prefix' 		=> '<div id="manager_residential_area_division_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(xii).Ward<span id=\'star\' class="form-required">*</span>',
								'#suffix' 		=> '</label></div></div>',
								'#type' 		=> 'select', 
								'#attributes' 	=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),	
								'#options'		=>  get_full_villward($value_manager_residential_area_details_code,'W'),
							);
					}if($value_manager_residential_area_type_code == 'C'){
							$form['manager_details']['manager_residential_area_division'] 	= array(
									'#prefix' 			=> '<div id="manager_residential_area_division_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(xii).Ward<span id=\'star\' class="form-required">*</span>',
									'#suffix' 			=> '</label></div></div>',
									'#type' 			=> 'select', 
									'#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
									'#options'			=>  get_full_villward($value_manager_residential_area_details_code,'C'),
							);
					}if($value_manager_residential_area_type_code == 'S'){
							$form['manager_details']['manager_residential_area_division'] 	= array(
									'#prefix' 			=> '<div id="manager_residential_area_division_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(xii).Sector<span id=\'star\' class="form-required">*</span>',
									'#suffix' 			=> '</label></div></div>',
									'#type' 			=> 'select', 
									'#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
									'#options'			=>  get_full_villward($value_manager_residential_area_details_code,$value_manager_residential_area_type_code),
							);
					}if($value_manager_residential_area_type_code == 'N'){
							$form['manager_details']['manager_residential_area_division'] 	= array(
									'#prefix' 			=> '<div id="manager_residential_area_division_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(xii).Notified Area<span id=\'star\' class="form-required">*</span>',
									'#suffix' 			=> '</label></div></div>',
									'#type' 				=> 'select', 
									'#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
									'#options'			=>  get_full_villward($value_manager_residential_area_details_code,$value_manager_residential_area_type_code),
							);
						}
					}
			 	}
			}
			else{
				$form['manager_details']['manager_residential_sub_division'] 	= array(
		  			'#prefix' 			=> '<div id="manager_residential_sub_replace">',
		  			'#suffix' 			=> '</label></div>',
				);
				$form['manager_details']['manager_residential_area_type'] 	= array(
					  '#prefix' 		=> '<div id="manager_residential_area_type_replace">',
					  '#suffix' 		=> '</label></div>',
				);
				$form['manager_details']['manager_residential_area_details'] 	= array(
					  '#prefix' 		=> '<div id="manager_residential_area_details_replace">',
					  '#suffix' 		=> '</label></div>'
				);
				$form['manager_details']['manager_residential_area_division'] 	= array(
					  '#prefix' 		=> '<div id="manager_residential_area_division_replace">',
					  '#suffix' 		=> '</label></div>'
				);
			}
			$is_ps_exists = 	is_ps_exists($value_manager_residential_dis_code);
			if($is_ps_exists>0){
				$form['manager_details']['manager_residential_ps'] 	= array(
				  	'#prefix' 			=> '<div id="manager_residential_ps_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(xiii).Police station<span id=\'star\' class="form-required">*</span>',
				  	'#suffix' 			=> '</label></div></div>',
				  	'#type' 			=> 'select',
				  	'#options'			=> get_all_ps($value_manager_residential_dis_code),
				);
			}else{
				$form['manager_details']['manager_residential_ps'] 	= array(
				  	'#prefix' 			=> '<div id="manager_residential_ps_replace">',
				  	'#suffix' 			=> '</label></div>'
				);
			}
		}
		else{
			$form['manager_details']['manager_residential_district'] 	= array(
				'#prefix' 			=> '<div id="manager_residential_dis_replace">',
				'#suffix' 			=> '</label></div>',
			);
			$form['manager_details']['manager_residential_sub_division'] 	= array(
				'#prefix' 			=> '<div id="manager_residential_sub_replace">',
				'#suffix' 			=> '</label></div>',  
			);
			$form['manager_details']['manager_residential_area_type'] 	= array(
				'#prefix' 			=> '<div id="manager_residential_area_type_replace">',
				'#suffix' 			=> '</label></div>',	
			);
			$form['manager_details']['manager_residential_area_details'] 	= array(
				'#prefix' 			=> '<div id="manager_residential_area_details_replace">',
				'#suffix' 			=> '</label></div>'
			);
			$form['manager_details']['manager_residential_area_division'] 	= array(
				'#prefix' 			=> '<div id="manager_residential_area_division_replace">',
				'#suffix' 			=> '</label></div>'
			);
			$form['manager_details']['manager_residential_ps'] 	= array(
				'#prefix' 			=> '<div id="manager_residential_ps_replace">',
				'#suffix' 			=> '</label></div>'
			);
		}
	}
	else{
	$form['manager_details']['manager_residential_state'] 	= array(
			'#prefix' 			=> '<div id="manager_residential_state_replace">',
			'#suffix' 			=> '</label></div>',
		);
	$form['manager_details']['manager_residential_district'] 	= array(
		  '#prefix' 			=> '<div id="manager_residential_dis_replace">',
		  '#suffix' 			=> '</label></div>',
	);
	$form['manager_details']['manager_residential_sub_division'] 	= array(
		  '#prefix' 			=> '<div id="manager_residential_sub_replace">',
		  '#suffix' 			=> '</label></div>',
	);
	$form['manager_details']['manager_residential_area_type'] 	= array(
		  '#prefix' 			=> '<div id="manager_residential_area_type_replace">',
		  '#suffix' 			=> '</label></div>',
	);
	$form['manager_details']['manager_residential_area_details'] 	= array(
		  '#prefix' 			=> '<div id="manager_residential_area_details_replace">',
		  '#suffix' 			=> '</label></div>'
	);
	$form['manager_details']['manager_residential_area_division'] 	= array(
		  '#prefix' 			=> '<div id="manager_residential_area_division_replace">',
		  '#suffix' 			=> '</label></div>'
	);
	$form['manager_details']['manager_residential_ps'] 	= array(
		  '#prefix' 			=> '<div id="manager_residential_ps_replace">',
		  '#suffix' 			=> '</label></div>'
	);
	
	}
	if($is_po_exists>0){
		$form['manager_details']['manager_residential_postoffice'] 	= array(
			  '#prefix' 			=> '<div id="manager_residential_po_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">(xiii).Post office<span id=\'star\' class="form-required">*</span>',
			  '#suffix' 			=> '</label></div></div>',
			  '#type' 				=> 'select',
			  '#options'			=> get_all_po($value_manager_residential_pincode),	  
		);
		}else{
			$form['manager_details']['manager_residential_postoffice'] 	= array(
			  	'#prefix' 			=> '<div id="manager_residential_po_replace"',
			  	'#suffix' 			=> '</label></div>',
			);
		}
	}
	$form['manager_details']['manager_residential_address'] 	= array(
			  '#prefix' 			=> '<div class="col-md-12 col-xs-12"><label class="textarea label-block">Address Line<span id=\'star\' class="form-required">*</span>',
			  '#suffix' 			=> '</label></div>',
			   '#rows'				=> 3,
			  '#type' 				=> 'textarea',
			  '#attributes' 		=> array('placeholder'=>'Residential Address Line'),
	);	
	$form['manager_details']['manager_present_address'] 	= array(
			  '#prefix' 			=> '<div class="col-md-12 col-xs-12"><label class="textarea label-block">Present Address Line<span id=\'star\' class="form-required">*</span>',
			  '#suffix' 			=> '</label></div>',
			  '#rows'				=> 3,
			  '#type' 				=> 'textarea',
			  '#attributes' 		=> array('placeholder'=>'Present Address Line'),
	);
	/********** manager Details  - Start **********/
    $form['manager_details']['manager_telephone'] = array(
			'#prefix' 				=> '<div class="col-md-3"><label class="input label-block">Telephone No.',
			'#suffix' 				=> '</label></div>',
			'#type' 				=> 'textfield',
			'#default_value' 		=> ''
    );
	$form['manager_details']['manager_mobile'] = array(
			'#prefix' 				=> '<div class="col-md-3"><label class="input label-block">Mobile No.',
			'#suffix' 				=> '</label></div>',
			'#type' 				=> 'textfield',
			'#default_value' 		=> ''
    );
    $form['manager_details']['manager_fax'] = array(
			'#prefix' 				=> '<div class="col-md-3"><label class="input label-block">Fax No.',
			'#suffix' 				=> '</label></div>',
			'#type' 				=> 'textfield',
			'#default_value' 		=> ''
    );
    
	$form['manager_details']['manager_email'] = array(
			'#prefix' 				=> '<div class="col-md-3"><label class="input label-block">Email Id <span id=\'star\' class="form-required">*</span>',
			'#suffix' 				=> '</label></div></div>',
			'#type' 				=> 'textfield',
			'#default_value' 		=> ''
    );
//	$form['manager_details']['same_data'] = array(
//			'#type' 			=> 'checkbox',
//			'#default_value' 	=> $same_data,
//			'#attributes'		=> array('class' => array( '')),
//			'#title' 			=> t('Same as all years Manager'),
//			'#prefix' 			=> '<div class="row"><div class="col-md-12 col-xs-12">',
//			'#suffix'			=> '</div></div>'
//    );
		
//	$form['manager_details']['add_manager'] 			= array (
//			'#type' 		=> 'submit',
//			'#value' 		=> 'Add manager',
//			'#prefix'		=> '<div class="row"><div class="col-md-12 col-xs-12">',
//			'#suffix' 		=> '</div></div>',
//			'#attributes'	=> array('class'=>array('btn btn-info')),
//			'#limit_validation_errors' 	=> array(),	
//			'#ajax'			=> array('callback'=> 'add_manager_details'),
//			);

		$is_manager_exists = is_manager_exists();
		if($is_manager_exists>0){		
			$form['manager_details']['view_manager'] = array(
				'#prefix'		=> '<div class="row"><div id="view_manager_details_id"><div class="col-md-12">',
				'#suffix' 		=> '</div></div></div>',
				'#type'			=> 'markup',
				'#markup'		=> view_manager_details($application_id,$service_id,$factory_type_id,$reference_number),
			);
		}else{		
		$form['manager_details']['view_manager'] = array(
				 '#prefix' 		=> '<div id="view_manager_details_id"><div class="col-md-6 col-xs-12">',
				 '#type'		=> 'markup',		
				 '#suffix' 		=> '</div></div>'
			);
		}	
 		/***************** manager Details  - End *********************/
		$is_director_exists =is_director_exists();
		if($is_director_exists>0){
			
			$form['manager_details']['view_director'] = array(
				 '#prefix' 		=> '<div class="row"><div id="view_director_details_id"><div class="col-md-12">',
				 '#type'		=> 'markup',
				 '#markup'		=>	view_director_proipietor_details($application_id,$service_id,$factory_type_id,$reference_number),
				 '#suffix' 		=> '</div></div></div>'
			);
			
		}else{
				$form['manager_details']['view_director'] = array(
				 '#prefix' 		=> '<div id="view_director_details_id"><div class="col-md-6 col-xs-12">',
				 '#type'		=> 'markup',
				 '#suffix' 		=> '</div></div>'
			);
		}
		/***************** Director Details  - End *********************/
				
				
		$form['back_link'] = array(
		'#prefix' => '<div class="row"><div class="col-md-1">',
		'#suffix' => '</div>',
		'#markup' => l(t('<i class="fa fa-angle-left" aria-hidden="true"></i> Back'), 'applicant/applicant-dasboard/', array('html' => TRUE,'attributes' => array('class' => array('btn btn-dark pull-left'))))
  	);
	
    if($application_status == 'I' || $application_status == 'B' || empty($application_status) || $application_status == 'In'){
    $form['submit'] = array(
        '#prefix' => '<div class="col-md-1">',
        '#suffix' => '</div>',
        '#attributes' => array('class' => array('btn btn-success')),
        '#type' => 'submit',
        '#value' => 'Save & Continue'
    );
	if(!empty($application_id)){
	$form['preview_link'] = array(
		'#prefix' => '<div class="col-md-10">',
        '#suffix' => '</div>',
  	//'#markup' => l(t('Preview as PDF'), 'applicant/applicant-dasboard/', array('html' => TRUE,'attributes' => array('class' => array('btn btn-dark space-left') )))
		'#markup' => l('DRAFT COPY', 'regsection/preview-varse-employee-information/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_number), array('html' => TRUE,'attributes'=>array('title' => 'Preview as PDF','class'=>array('btn btn-warning pull-right'))))
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


function view_manager_details($application_id,$service_id,$factory_type_id,$reference_number){
	$get_manager_data 		= array();
	$type					= '';
	$details				= '';
	$relationship			= '';
	$address_of_manager		= '';
	$get_manager_data = get_all_manager_data($application_id,$service_id,$factory_type_id,$reference_number);
	//print_r($get_manager_data);die;
	$Wcounter		= 0;
	$per_page		= 2;
	$current_page 	= pager_default_initialize(count($get_manager_data), $per_page);
	$chunks 		= array_chunk($get_manager_data, $per_page);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header			= array(
						array('data' => 'Sl. No'),
						array('data'=> 'Employee Type'),
						array('data'=> 'Employee Details'),
						array('data'=> 'Permanent Address'),
						array('data'=> 'Present Address & Contact'),
						array('data'=> 'Action'),		
					);
	if(!empty($get_manager_data)){
		
		foreach($chunks[$current_page] as $manager_details){ 
			$Wcounter++;
			if($manager_details->relationship_manager == '1'){
				$relationship = 'D/O';
			}if($manager_details->relationship_manager == '2'){
				$relationship = 'S/O';
			}if($manager_details->relationship_manager == '3'){
				$relationship = 'W/O';
			}
			if($manager_details ->application_status == 'F'){
				$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
				else{
					$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/del-manager-registration/'.encryption_decryption_fun('encrypt', $manager_details->id).'/'.encryption_decryption_fun('encrypt', $manager_details->application_manager_id).'/'.encryption_decryption_fun('encrypt', $manager_details->manager_service_id).'/'.encryption_decryption_fun('encrypt', $manager_details->factory_type_id).'/'.encryption_decryption_fun('encrypt', $manager_details->application_reference_no).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
	}
	
	$fieldArr_manager	=  array('district_manager','sub_division_manager','area_type_manager','block_mun_cor_sez_not_manager','grm_ward_sector_not_manager','police_station_manager','pincode_manager','state_manager','post_office_manager');
	
	$address_of_manager	=	$manager_details->adress_line1_manager.'<br>'.get_full_address('fa_manager_details','sub-table',$manager_details->id,$fieldArr_manager);
	
	$manager_details_view = $manager_details->name_manager.'<br/>' .$relationship.'-'.$manager_details->father_husband_name_manager.'<br/>Age:-'.$manager_details->age_manager;
	$rows[]	= array(
				array('data' =>$Wcounter,'class' => array('')),
				array('data' =>'Manager' ,'class' => array('')),
				array('data' =>$manager_details_view,'class' => array('')),
				array('data' =>$address_of_manager ,'class' => array('')),	
				array('data' =>$manager_details->manager_present_address.'<br>'.'Telephone: '.$manager_details->manager_telephone.'<br>'.'Mobile: '.$manager_details->manager_phone.'<br>'.'FAX: '.$manager_details->manager_fax.'<br>'.'Email: '.$manager_details->manager_email ,'class' => array('')),
				array('data' => $delLink ,'class' => array('')),
			);
		}
	}
	$output = theme_table(
	array(	'header' => $header,
			'rows' => $rows,
			'attributes' => array('id'=>'view_manager_details_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
			'sticky' => true,
			'caption' => '(1). All Manager List',
			'colgroups' => array(),
			'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');
	return $output;	
}

function delete_uploaded_manager_data($id,$application_id,$service_id,$factory_typeid,$reference_no){
	drupal_add_library('system', 'drupal.ajax');
	if (trim(encryption_decryption_fun('decrypt', $id)) != 0) {
				$query = db_delete('fa_manager_details');
		 		$query->condition('id', trim(encryption_decryption_fun('decrypt', $id)),'=');
		 		$query->condition('application_reference_no',trim(encryption_decryption_fun('decrypt', $reference_no)),'=');
		 		$query->execute();
			}
	$commands = array();
	$commands[] = ajax_command_replace('#view_manager_details_id', "<div id ='view_manager_details_id'><div class='col-md-12 col-xs-12'>".view_manager_details(encryption_decryption_fun('decrypt', $application_id),encryption_decryption_fun('decrypt', $service_id),encryption_decryption_fun('decrypt', $factory_typeid),encryption_decryption_fun('decrypt', $reference_no)).'</div></div>');
	$page = array('#type' => 'ajax', '#commands' => $commands);
	ajax_deliver($page);	
}

function view_director_proipietor_details($application_id,$service_id,$factory_typeid,$reference_number){
	$get_all_data = array();
	$type					= '';
	$details				= '';
	$relationship			= '';
	$address_of_director	= '';
	
	$get_all_data = get_director_details_service($application_id,$service_id,$factory_typeid,$reference_number);
	//print_r($get_all_data);die();
	
	$Wcounter		= 0;
	$per_page		= 2;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header			= array(
						array('data' => 'Sl. No'),
						array('data'=> 'Employee Type'),
						array('data'=> 'Employee Details'),
						array('data'=> 'Permanent Address'),
						array('data'=> 'Present Address & Contact'),
						array('data'=> 'Action'),		
					);
	if(!empty($get_all_data)){
		foreach($chunks[$current_page] as $details){ 
			$Wcounter++;
			if(!empty($details->din_director)){
				$din = 'DIN:-'.$details->din_director;
				}	
			$type =$details->type_director;
			if($type=='ltd' || $type=='pv'){$director_type = 'Director';}
			if($type == 'par_firm'){$director_type 	= 'Partner';}
			if($type == 'pro_firm'){$director_type 	= 'Proprietor';}
			if($type == 'govt' || $type == 'psu' || $type == 'others'){$director_type 	= 'Nominated Occupier';}
			if(!empty($details->age_director)){
				$age = 'Age- '.$details->age_director;
				}
			$is_occupier =$details->is_occupier;
			
			$relation =$details->relationship_director;
			 if($relation == 1){
				$relationship = 'D/O';
			}
			 if($relation == 2){
				$relationship = 'S/O';
			}
			 if($relation == 3){
				$relationship = 'W/O';
			}
			if($is_occupier == 1){
				$occupier = '<br/>(Occupier)';
			}else{$occupier = '';}
			if($details->application_status == 'F'){
				$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
			else if($details->worker_plan_approval_status == 'F'){
				$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
			
				else{
					$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/del-dir-registration/'.encryption_decryption_fun('encrypt', $details->id).'/'.encryption_decryption_fun('encrypt', $details->application_director_id).'/'.encryption_decryption_fun('encrypt', $details->director_service_id).'/'.encryption_decryption_fun('encrypt', $details->factory_type_id).'/'.encryption_decryption_fun('encrypt', $details->application_reference_no).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
				}
		$fieldArr_director			 =  array('district_director','sub_division_director','area_type_director','block_mun_cor_sez_not_director','grm_ward_sector_not_director','police_station_director','pincode_director','state_director','post_office_director');
    $address_of_director	 =	$details->adress_line1_director.'<br>'.get_full_address('fa_director_details','sub-table',$details->id,$fieldArr_director);
			$rows[] 	= array( 
								array('data' =>$Wcounter,'class' => array('')),
								array('data' =>$director_type ,'class' => array('')),
								array('data' =>$details->name_director.'<br>'.$din.'<br>'.$relationship.'-'.$details->father_husband_name_director.'<br>'.$age,'class' => array('')),
								array('data' =>$address_of_director ,'class' => array('')),
								array('data' =>$details->addrline_oprsntadr.'<br>'.'Telephone: '.$details->director_telephone.'<br>'.'Mobile: '.$details->director_mobile.'<br>'.'FAX: '.$details->director_fax_no.'<br>'.'Email: '.$details->director_email_id ,'class' => array('')),
								array('data' =>$delLink ,'class' => array('')),
								//array('data' =>'View' ,'class' => array('')),
								);
		} 
		
	}
	$output = theme_table(
	array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'view_director_details_id1', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '(2). All Director List',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
	return $output;
}

function delete_uploaded_director_data($id,$application_id,$service_id,$factory_typeid,$reference_no){
			
			drupal_add_library('system', 'drupal.ajax');
			
			if (trim(encryption_decryption_fun('decrypt', $id)) != 0) {
				$query 	= db_delete('fa_director_details');
		 		$query	->condition('id', trim(encryption_decryption_fun('decrypt', $id)),'=');
		 		$query	->condition('application_reference_no',trim(encryption_decryption_fun('decrypt', $reference_no)),'=');
		 		$query	->execute();
			}
		 
		 	$commands 	= array();
			$commands[] = ajax_command_replace('#view_director_details_id', "<div id ='view_director_details_id'><div class='col-md-12 col-xs-12'>".view_director_proipietor_details(encryption_decryption_fun('decrypt', $application_id),encryption_decryption_fun('decrypt', $service_id),encryption_decryption_fun('decrypt', $factory_typeid),encryption_decryption_fun('decrypt', $reference_no)).'</div></div>');
		 	$page = array('#type' => 'ajax', '#commands' => $commands);
		 	ajax_deliver($page);
			//return array('#type' => 'ajax','#commands' => $commands);
	 		
	}


function get_manager_residential_ajax_load($form, $form_state){
	$commands = array();
	$commands[] = ajax_command_replace('#manager_residential_state_replace', drupal_render($form['manager_details']['manager_residential_state']));
	$commands[] = ajax_command_replace('#manager_residential_dis_replace', drupal_render($form['manager_details']['manager_residential_district']));
	$commands[] = ajax_command_replace('#manager_residential_sub_replace', drupal_render($form['manager_details']['manager_residential_sub_division']));
	$commands[] = ajax_command_replace('#manager_residential_area_details_replace', drupal_render($form['manager_details']['manager_residential_area_details']));
	$commands[] = ajax_command_replace('#manager_residential_area_type_replace', drupal_render($form['manager_details']['manager_residential_area_type']));
	$commands[] = ajax_command_replace('#manager_residential_area_division_replace', drupal_render($form['manager_details']['manager_residential_area_division']));
	$commands[] = ajax_command_replace('#manager_residential_ps_replace', drupal_render($form['manager_details']['manager_residential_ps']));
	$commands[] = ajax_command_replace('#manager_residential_po_replace', drupal_render($form['manager_details']['manager_residential_postoffice']));
	
	return array('#type' => 'ajax', '#commands' => $commands);
}

function get_ajax_ownership_type($form, &$form_state){
    $commands   		= array();
	$commands[] 		= ajax_command_replace('#ld_show_din', drupal_render($form['manager_details']['director_din']));
	return array('#type' => 'ajax','#commands' => $commands);
}

function amendment_of_employee_validate($form, &$form_state) {
	
  $name_manager = $form_state['values']['name_manager'];
	if (!preg_match('/[A-Za-z]+$/', $name_manager)) {  
    form_set_error('name_manager', t('Manager Name should be text only!!'));
  }	
   $father_husband_name_manager = $form_state['values']['father_husband_name_manager'];
	if (!preg_match('/[A-Za-z]+$/', $father_husband_name_manager)) {  
    form_set_error('father_husband_name_manager', t('Father Name should be text only!!'));
  }	
  
  $manager_telephone = $form_state['values']['manager_telephone'];
  if (!preg_match('/^[0-9]*$/', $manager_telephone)) {
    form_set_error('manager_telephone', t('Telephone should be numeric only!!'));
  }
  if ($form_state['values']['manager_telephone']!="" && (strlen($form_state['values']['manager_telephone'])<10 || strlen($form_state['values']['manager_telephone'])>10)) {
	form_set_error('manager_telephone', 'Telephone should be of 10 digit');    
  }

  $manager_mobile = $form_state['values']['manager_mobile'];
  if (!preg_match('/^[0-9]*$/', $manager_mobile)) {
    form_set_error('manager_mobile', t('Mobile should be numeric only!!'));
  }
 
  
  if ($form_state['values']['manager_mobile']!="" && (strlen($form_state['values']['manager_mobile'])<10 || strlen($form_state['values']['manager_mobile'])>10)) {
	form_set_error('manager_mobile', 'Mobile should be of 10 digit');    
  }

  $manager_fax = $form_state['values']['manager_fax'];
  if (!preg_match('/^[0-9]*$/', $manager_fax)) {
    form_set_error('manager_fax', t('Fax should be numeric only!!'));
  }
  
  $manager_email = $form_state['values']['manager_email'];
	if (!filter_var($manager_email, FILTER_VALIDATE_EMAIL)) {
	form_set_error('manager_email', t('Please enter a Valid Email Id!')); 
  }
   	  
}

function amendment_of_employee_submit($form, &$form_state){
	
	global $user;
	$uid 								= $user->uid;
	$val   								= $form_state['values'];
	$name_manager						= $val['name_manager'];
	$age_manager						= $val['age_manager'];
	$father_husband_name_manager		= $val['father_husband_name_manager'];
	$father_husband_type_manager		= $val['father_husband_type_manager'];
	$pincode_manager					= $val['manager_residential_pincode'];
	$state_manager						= $val['manager_residential_state'];
	$district_manager					= $val['manager_residential_district'];
	$sub_division_manager				= $val['manager_residential_sub_division'];
	$area_type_manager					= $val['manager_residential_area_type'];
	$block_mun_cor_sez_not_manager		= $val['manager_residential_area_details'];
	$grm_ward_sector_not_manager		= $val['manager_residential_area_division'];
	$police_station_manager				= $val['manager_residential_ps'];
	$post_office_manager				= $val['manager_residential_postoffice'];
	$adress_line1_manager				= $val['director_residential_address']; 
	$manager_service_id					= encryption_decryption_fun('decrypt',$val['serviceid']);	
	$application_id						= encryption_decryption_fun('decrypt',$val['applicationid']);
	$factory_type_id					= encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	//$add_year_manager					= $val['manager_year'];
	$application_reference_no			= encryption_decryption_fun('decrypt',$val['application_reference_no']);
	$adress_line1_manager             	= $val['manager_residential_address'];
	$present_adress_manager            	= $val['manager_present_address'];
	$telephone_no_manager	            = $val['manager_telephone'];
	$mobile_no_manager            		= $val['manager_mobile'];
	$fax_no_manager	           			= $val['manager_fax'];
	$email_id_manager            		= $val['manager_email'];	
	
	$ownership							= $val['ownership_type']; 
	
	 if($ownership == 'pv' || $ownership == 'ltd'){
		 $get_ownership_type 	= 'Director';
	}if($ownership_type == 'par_firm'){
		 $occupier_ownership_type 	= 'Partner';
	 }if($ownership_type == 'pro_firm'){
		 $occupier_ownership_type 	= 'Proprietor';
	 }if($ownership_type == 'govt' || $ownership_type == 'psu' || $ownership_type == 'others'){
		 $occupier_ownership_type 	= 'Nominated Occupier';
	 }
	
	if(empty($val['employee_type'])){
			drupal_set_message('Please select employee type','warning');
		}else{	
			if((!empty($name_manager)) && (!empty($age_manager))&& (!empty($father_husband_name_manager)) && (!empty($father_husband_type_manager)) && (!empty($pincode_manager)) && (!empty($state_manager)) && (!empty($district_manager)) && (!empty($sub_division_manager))  && (!empty($area_type_manager) ) && (!empty($block_mun_cor_sez_not_manager) )&& (!empty($grm_ward_sector_not_manager) )&& (!empty($police_station_manager) )&& (!empty($post_office_manager) )&& (!empty($adress_line1_manager) ) && (!empty($present_adress_manager) ) &&(!empty($telephone_no_manager) ) &&  (!empty($fax_no_manager) ) && (!empty($email_id_manager) )){
				
				if((filter_var($age_manager, FILTER_VALIDATE_INT)== true)){
					
					if($val['employee_type']== 1){
				
						$director_propieter_details = array(
								'type_director'   					=> $ownership, 
								'name_director'   					=> $name_manager, 
								'age_director' 						=> $age_manager,
								'father_husband_name_director' 		=> $father_husband_name_manager,
								'relationship_director' 			=> $father_husband_type_manager,
								'pincode_director'					=> $pincode_manager,
								'state_director'					=> $state_manager,
								'district_director'					=> $district_manager,
								'sub_division_director'				=> $sub_division_manager,
								'area_type_director'				=> $area_type_manager,
								'block_mun_cor_sez_not_director'	=> $block_mun_cor_sez_not_manager,
								'grm_ward_sector_not_director'		=> $grm_ward_sector_not_manager,
								'police_station_director'			=> $police_station_manager,
								'post_office_director'				=> $post_office_manager,
								'adress_line1_director'				=> $adress_line1_manager,
								'created_by'						=> $uid,
								'application_director_id'			=> $application_id,
								'factory_type_id'					=> $factory_type_id,
								'add_year_director'					=> '',
								'application_status'				=> 'In',
								'director_service_id'				=> $manager_service_id,
								'application_reference_no'			=> $application_reference_no,
								'din_director'						=> $val['director_din'],
								'active_inactive_director'			=> 1,
								'valid_year'					 	=> NULL,
								'valid_time_period'					=> NULL,
								'starting_year'	     			 	=> NULL,
								'calculate_year_id'				 	=> NULL,
								'director_mobile'					=> $mobile_no_manager,
								'director_fax_no'					=> $fax_no_manager,
								'director_telephone'				=> $telephone_no_manager,
								'director_email_id'					=> $email_id_manager,
								'addrline_oprsntadr'				=> $present_adress_manager
							);
							$id = db_insert('fa_director_details')->fields($director_propieter_details)->execute();
							if(!empty($id)){
								
								if(!empty($val['application_manager_amendment'] )){
									$check_data = 'director_details';
									$year_data = array(
										'year_id'		=> $val['application_manager_amendment'],
										'application_id'=> $application_id,
										'change_field'	=> $check_data,
									);
									$is_factor = get_period_id($application_id,$check_data,$val['application_manager_amendment']);
									if(empty($is_factor)){
										db_insert('fa_amendment_mapping')->fields($year_data)->execute();
									}else{
										$querya = db_update('fa_amendment_mapping');
										$querya->fields($year_data);
										$querya->condition('id', $is_factor, '=');
										$querya->execute();
									}
								}
								drupal_set_message('Details of director has been saved successfully.');
							}
						
					}elseif($val['employee_type']== 2){
						
							$manager_details = array(
								'name_manager'   	 				=> $name_manager, 
								'type_manager' 	 					=> '',
								'age_manager' 	 					=> $age_manager,
								'father_husband_name_manager' 		=> $father_husband_name_manager,
								'relationship_manager'				=> $father_husband_type_manager,
								'pincode_manager'					=> $pincode_manager,
								'state_manager'						=> $state_manager,
								'district_manager'					=> $district_manager,
								'sub_division_manager'				=> $sub_division_manager,
								'area_type_manager'					=> $area_type_manager,
								'block_mun_cor_sez_not_manager'		=> $block_mun_cor_sez_not_manager,
								'grm_ward_sector_not_manager'		=> $grm_ward_sector_not_manager,
								'police_station_manager'			=> $police_station_manager,
								'post_office_manager'				=> $post_office_manager,
								'adress_line1_manager'				=> $adress_line1_manager,
								'created_by'						=> $uid,
								'application_manager_id'			=> $application_id,
								'factory_type_id'					=> $factory_type_id,
								'add_year_manager'					=> '',
								'manager_service_id'				=> $manager_service_id,
								'active_inactive_manager'			=> 1,
								'application_status'				=> 'In',
								'application_reference_no'          => $application_reference_no,
								'worker_plan_approval_status'		=> '',
								'manager_present_address'			=> $present_adress_manager,
								'manager_telephone'					=> $telephone_no_manager,
								'manager_phone'						=> $mobile_no_manager,
								'manager_fax'						=> $fax_no_manager,
								'manager_email'						=> $email_id_manager,
								'valid_year'					 	=> NULL,
								'valid_time_period'					=> NULL,
								'starting_year'	     			 	=> NULL,
								'calculate_year_id'				 	=> NULL
							);
						$id =db_insert('fa_manager_details')->fields($manager_details)->execute();
						if(!empty($id)){
								if(!empty($val['application_manager_amendment'] )){
									$year_data = array(
										'year_id'		=> $val['application_manager_amendment'],
										'application_id'=> $application_id,
										'change_field'	=> $val['manager_checked_data'],
									);
									$is_factor = get_period_id($application_id,$val['manager_checked_data'],$val['application_manager_amendment']);
									if(empty($is_factor)){
										db_insert('fa_amendment_mapping')->fields($year_data)->execute();
									}else{
										$querya = db_update('fa_amendment_mapping');
										$querya->fields($year_data);
										$querya->condition('id', $is_factor, '=');
										$querya->execute();
									}
								}
								drupal_set_message('Details of manager has been saved successfully.');
							}
						}
				}
				else{
					drupal_set_message('Age fields under Details of Employee of the Factories should be integer.','warning');
				}
			}
			else{
				drupal_set_message('All fields under Details of Employee of the Factories should be mandatory.','warning');
			}
			$form_state['rebuild'] = true;
		}
	}

?>