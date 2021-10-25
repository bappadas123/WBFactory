<?php
function employee_amendment_notice($form, &$form_state, $applicationid,$serviceid, $factory_typeid,$referenceno) {	
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	global $base_root, $base_path, $user;
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	$reference_no 		= encryption_decryption_fun('decrypt', $referenceno);
	
	$get_fa_cafa 				= get_fa_cafa($application_id);
	$userid						= $user->uid;
	$reference_number 			= $get_fa_cafa['reference_number'];
	$is_year_calculation_tab    = $get_fa_cafa['is_year_calculation_tab'];
	$ownership_type 			= $get_fa_cafa['factory_owershiptype'];
		

	// if(empty($is_year_calculation_tab)){
	//   drupal_set_message(('Please fill up the second tab than fill up the worker information'),'warning');			
	// 	 drupal_goto('applicant/caf-online-backrenew/details-worker-renewal/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$referenceno) ;
	// }  

	$lists = year_list($application_id,$factory_type_id,$reference_no,$userid);

	if ($get_fa_cafa['application_status']=='In') {
		
		$amendment_checking = get_amendment_checking($application_id,$service_id,$factory_type_id,$reference_no);
	   //print_r($amendment_checking);die;
		$verify_details = !empty($amendment_checking['fieldname'])? $amendment_checking['fieldname'] : ''; 
		
		$str = "factory_name,director_details";
		$fields = removeFromString($str,$verify_details);
		
		$remark_field = explode(',',$fields);
		//print_r($remark_field);die;
		foreach ($remark_field as $fieldname){ //echo $fieldname;
			
				if($fieldname == 'factory_name'){$factory_name_ck = "readonly";}
				if($fieldname == 'director_details'){ $director_type_ck = "disabled";}
				
				}
			
				
			if(in_array("factory_name", $remark_field)) { $factory_name_check_data = '<i class="fa fa-check text-green verified"></i>'; $factory_field_value= 'blank'; }
			else {  $factory_name_check_data = '<i class="fa fa-edit text-red verified"></i>'; $factory_field_value= "factory_name";}
			
			if(in_array("director_details", $remark_field)) { $director_check_data = '<i class="fa fa-check text-green verified"></i>'; $director_field_value= 'blank'; }
			else {  $director_check_data = '<i class="fa fa-edit text-red verified"></i>'; $director_field_value= "director_details";}
				
		}

	
	$form['serviceid'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $serviceid,
	);
	$form['factorytypeid_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $factory_typeid
	);
	$form['application_reference_no'] = array(
		'#type' 		 => 'hidden',
		'#default_value' => encryption_decryption_fun('encrypt', $reference_number)
	);
	$form['applicationid'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $applicationid
	);	
	
	//////////////Start Form/////////////////////
	$form['header']            = array(
        '#markup' => t('<div class="content"><h3>Details of director(s)</h3>')
    );
	$form['manager_details'] = array(
		'#type' 		=> 'fieldset',
		'#title' 		=> t('K. Details of  Directors Permanent/Present Address '),
		'#collapsible' 	=> TRUE, // Added
		'#collapsed' 	=> FALSE,  // Added
	);	
	$form['manager_details']['application_period_year'] 	= array(
		'#prefix' 	 		=> '<div class="row"><div class="col-md-4 col-xs-4">Application Period <span id=\'star\' class="form-required">*</span>'.$manager_check_data,
		'#suffix' 	 		=> '</div>',
		'#type' 			=> 'select',
		'#attributes' 		=> 	array('class' => array('form-control'),$manager_type_ck =>$manager_type_ck ),
		'#required'			=> TRUE,
		'#id'				=> 'dates',
		'#default_value' 	=> $service_year,
		'#options' 	 		=> $lists//($application_id,$service_id,$factory_type_id,$reference_number), 
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
		}else{
				$form['manager_details']['director_din'] 	= array(
				  '#prefix'	=> '<div id="ld_show_din">',			 
				  '#suffix'	=> '</div>',	
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
		'#prefix' 			=> '<div id="manager_residential_state_replace">
									<div class="col-md-4 col-xs-12">
									<label class="select label-block">(vii).State<span id=\'star\' class="form-required">*</span>',
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
		'#options' 			=> array(''=>t('Select Post office')),    
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
        '#value' => 'Save'
    );
	if(!empty($application_id)){
	$form['preview_link'] = array(
		'#prefix' => '<div class="col-md-10">',
        '#suffix' => '</div>',
  	//'#markup' => l(t('Preview as PDF'), 'applicant/applicant-dasboard/', array('html' => TRUE,'attributes' => array('class' => array('btn btn-dark space-left') )))
		'#markup' => l('DRAFT COPY', 'regsection/preview-varse-employee-information/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'Preview as PDF','class'=>array('btn btn-warning pull-right'))))
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

function view_director_proipietor_details($application_id,$service_id,$factory_typeid,$reference_number){
	$get_director_data = array();
	$type					= '';
	$details				='';
	$relationship			= '';
	$address_of_director	='';
	
	$get_director_data = get_director_details_service($application_id,$service_id,$factory_typeid,$reference_number);
	//print_r($get_director_data);die();
	
	$Wcounter		= 0;
	$per_page		= 2;
	$current_page 	= pager_default_initialize(count($get_director_data), $per_page);
	
	$chunks 		= array_chunk($get_director_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header			= array(
						array('data' => 'Sl. No'),
						array('data'=> 'Director Type'),
						array('data'=> 'Director Details'),
						array('data'=> 'Permanent Address'),
						array('data'=> 'Present Address & Contact'),
						array('data'=> 'Action'),		
					);
	if(!empty($get_director_data)){
		foreach($chunks[$current_page] as $details){ 
			$Wcounter++;
			if(!empty($details->din_director)){
				$din = 'DIN:-'.$details->din_director;
				}	
			$type =$details->type_director;
				 if($type == 'pv' || $type == 'ltd'){
					 $director_type 	= 'Director';
				}if($type == 'par_firm'){
					 $director_type 	= 'Partner';
				 }if($type == 'pro_firm'){
					 $director_type 	= 'Proprietor';
				 }if($type == 'govt' || $type == 'psu'){
					 $director_type 	= 'Nominated Occupier';
				 }if($type=="registered"){
					$director_type = "Registered Society under Society Register";
				}if($type=="cooperative"){
					$director_type = "Co-operative";
				}if($$type=="localbody"){
					$director_type = "Local Body";
				}if($type=="others"){
					$director_type = "Others";
				}if($type=="llp"){
					$director_type = "Limited Liability Partnership";
				}
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
			if($details->director_is_amended == NULL || $details->director_is_amended==0){
				$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
				else{
					$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/del-dir-amendment/'.encryption_decryption_fun('encrypt', $details->id).'/'.encryption_decryption_fun('encrypt', $details->application_director_id).'/'.encryption_decryption_fun('encrypt', $details->director_service_id).'/'.encryption_decryption_fun('encrypt', $details->factory_type_id).'/'.encryption_decryption_fun('encrypt', $details->application_reference_no).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
				}
				$fieldArr_director			 =  array('district_director','sub_division_director','area_type_director','block_mun_cor_sez_not_director','grm_ward_sector_not_director','police_station_director','pincode_director','state_director','post_office_director');
				$address_of_director	 =	$details->adress_line1_director.'<br>'.get_full_address('fa_director_details','sub-table',$details->id,$fieldArr_director);
				$year_data = fetch_year_details_withid($details->calculate_year_id);

			$rows[] 	= array( 
								array('data' =>$Wcounter,'class' => array('')),
								array('data' =>'Director('.$director_type.')' .'<br/>'.$year_data['calculate_year'].'','class' => array('')),
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

function delete_amendment_data($id,$application_id,$service_id,$factory_typeid,$reference_no){
			
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

function employee_amendment_notice_validate($form, &$form_state) {
	
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

function employee_amendment_notice_submit($form, &$form_state){
	
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
	$application_period_year_id			= $val['application_period_year'];	
	
	$ownership							= $val['ownership_type']; 
	
	 if($ownership == 'pv' || $ownership == 'ltd'){
		 $get_ownership_type 	= 'Director';
	}if($ownership_type == 'par_firm'){
		 $occupier_ownership_type 	= 'Partner';
	 }if($ownership_type == 'pro_firm'){
		 $occupier_ownership_type 	= 'Proprietor';
	 }if($ownership_type == 'govt' || $ownership_type == 'psu'){
		 $occupier_ownership_type 	= 'Nominated Occupier';
	 }if($ownership_type=="registered"){
   		$occupier_ownership_type = "Registered Society under Society Register";
   	}if($ownership_type=="cooperative"){
   		$occupier_ownership_type = "Co-operative";
   	}if($$ownership_type=="localbody"){
   		$occupier_ownership_type = "Local Body";
   	}if($ownership_type=="others"){
   		$occupier_ownership_type = "Others";
   	}if($ownership_type=="llp"){
   		$occupier_ownership_type = "Limited Liability Partnership";
   	}
	
	
		// if((!empty($name_manager)) && (!empty($age_manager))&& (!empty($father_husband_name_manager)) && (!empty($father_husband_type_manager)) && (!empty($pincode_manager)) && (!empty($state_manager)) && (!empty($district_manager)) && (!empty($sub_division_manager))  && (!empty($area_type_manager) ) && (!empty($block_mun_cor_sez_not_manager) )&& (!empty($grm_ward_sector_not_manager) )&& (!empty($police_station_manager) )&& (!empty($post_office_manager) )&& (!empty($adress_line1_manager) ) && (!empty($present_adress_manager) ) &&(!empty($telephone_no_manager) ) &&  (!empty($fax_no_manager) ) && (!empty($email_id_manager) )){
				
		// 		if((filter_var($age_manager, FILTER_VALIDATE_INT)== true)){
					
				
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
								'calculate_year_id'				 	=> $application_period_year_id,
								'director_mobile'					=> $mobile_no_manager,
								'director_fax_no'					=> $fax_no_manager,
								'director_telephone'				=> $telephone_no_manager,
								'director_email_id'					=> $email_id_manager,
								'addrline_oprsntadr'				=> $present_adress_manager,
								'director_is_amended'				=> 1
							);
							$id = db_insert('fa_director_details')->fields($director_propieter_details)->execute();
							if(!empty($id)){
								$cafa_Info = array(							
												'modification_date'		=> date('Y-m-d'),
												'is_manager_tab'			=>1
	    									);
								$queryabc 	= 	db_update('fa_cafa');
								$queryabc	->	fields($cafa_Info);
								$queryabc	->	condition('id', $application_id, '=');
								$queryabc	->	execute();
								

								if($manager_service_id==3){
									remark_input($application_reference_no,$application_id,'In','Director information for renewal is sucessfully save')	;
								}if($manager_service_id==8){
									remark_input($application_reference_no,$application_id,'In','Director information for amendment is sucessfully save')	;
								}
								drupal_set_message('Details of director has been saved successfully.');
							}
			$form_state['rebuild'] = true;
		
}

?>