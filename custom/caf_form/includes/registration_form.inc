<?php
function applicant_registration_form($form, &$form_state) {	
	global $base_root, $base_path;
  	//drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/sky-forms.css');
	//drupal_add_css(drupal_get_path('theme', 'custom_dashboard') . '/css/factory.min.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	drupal_add_js('https://www.jqueryscript.net/demo/jQuery-Plugin-For-Auto-Tab-Form-Fields-autotab/js/jquery.autotab.js', 'external');
    
	$form = array();
	//$form['#attributes']['class'][] = 'sky-form# custom-form-main#';
	    
    $form['header']            = array(
        '#markup' => t('<h3>Applicant Registration</h3>'),
 );

	/*$form['profile_part_info']['firstRowStart'] = array(
		'#prefix' 			=> '<div class="row" >',
		'#suffix' 			=> ''
	);*/
	
	// GENERAL INFORMATION

		$form['profile_part_info'] = array(
			'#type' 			=> 'fieldset',
			'#title' 			=> t('General Information'),
			'#collapsible' 		=> FALSE, // Added
			'#collapsed' 		=> FALSE,  // Added
		);				
		$form['profile_part_info']['firstname'] 	= array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' 			=> '</label></div>',
			'#title'			=>	t('Enter Your First Name'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			'#attributes' 		=> array('class' => array('charField'))
		);
		$form['profile_part_info']['middlename'] 	= array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' 			=> '</label></div>',
			'#title'			=>	t('Enter Your Middle Name'),
			'#type' 			=> 'textfield',
			'#attributes' 		=> array('class' => array('charField'))
		);
		$form['profile_part_info']['lastname'] 	= array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' 			=> '</label></div>',
			'#title'			=>	t('Enter Your Last Name'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			'#attributes' 		=> array('class' => array('charField'))
		);
		$form['profile_part_info']['gurdian_name'] 	= array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' 			=> '</label></div>',
			'#title'			=>	t('Father’s/Husband’s Name'),
			'#type' 			=> 'textfield',
			'#attributes' 		=> array('class' => array('charField'))
		);
		$form['profile_part_info']['email'] 	= array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' 			=> '</label></div>',
			'#title'			=>	t('Enter Your Email Id'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
		);
		$form['profile_part_info']['mobile'] 	= array(
		  '#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">',
		  '#suffix' 			=> '</label></div>',
		  '#title'				=>	t('Enter Your Mobile No.'),
		  '#type' 				=> 'textfield',
		  '#required' 			=> TRUE,
		  '#attributes' 		=> array('class' => array('NoField')),
		  '#maxlength' 			=> 10
		);
		
		$form['profile_part_info']['username'] 	= array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' 			=> '</label></div>',
			'#title'			=>	t('Enter Username'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
		);
		$form['profile_part_info']['password'] 	= array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' 			=> '</label></div>',
			'#title'			=>	t('Enter Password'),
			'#type' 			=> 'password',
			'#required' 		=> TRUE,
		);
		$form['profile_part_info']['reenter_password'] 	= array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' 			=> '</label></div>',
			'#title'			=>	t('Re-Enter Password'),
			'#type' 			=> 'password',
			'#required' 		=> TRUE,
		);
	
		$form['profile_part_info']['sd'] = array(
			'#type' 			=> 'markup',
			'#prefix' 			=> '<div class="col-md-12" style="color:#da0000">',
			'#suffix' 			=> '</div>',
			'#markup' 			=> t('Password must contain minimum 8 characters with 1 Capital Letter, 1 Small Letter, 1 Special Character and 1 number'),
		);
	
		$form['profile_part_info']['dob'] 	= array(
		  '#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">',
		  '#suffix' 			=> '</label></div>',
		  '#title'				=>	t('Enter Your Date of Birth'),
		  '#type' 				=> 'textfield',
		  '#required' 			=> TRUE,
		  '#attributes' 		=> array('class'=>array('form-control# form-text datepicker_cls'),'title'=>'Enter Date of Birth.','readonly' => 'readonly'),
		);
		
		$form['profile_part_info']['gender'] 	= array(
			'#title'			=>	t('Gender'),
			'#type' 			=> 'select',
			'#options' 			=> array('male'=>'Male','female'=>'Female','thirdgender'=>'Third Gender'),
			'#required' 		=> TRUE,
			'#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="select label-block">',
			'#suffix' 			=> '</label></div>',
			'#required' 		=> TRUE,
		);
		
		$form['profile_part_info']['user_type'] 	= array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="select label-block">',
			'#suffix' 			=> '</label></div>',
			'#title'			=>	t('Identify yourself as'),
			'#type' 			=> 'select',
			'#required' 		=> TRUE,
			'#options' 			=> array('owner'=>'Owner','occupier'=>'Occupier','consultant'=>'Consultant'),
			'#ajax'				=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',			
										'callback'		=> 'get_ajax_load_ownership',
										//'wrapper' 		=> 'otherdetails_ow_div',
										'progress'		=>	array(
											'type'		=>'throbber',
											'message'	=>t('loading'),
										),
								)
		 );

	// ADDRESS INFORMATION
	
		$form['profile_address_info'] = array(
			'#type' 			=> 'fieldset',
			'#title' 			=> t('Address Details'),
			'#collapsible' 		=> FALSE, // Added
			'#collapsed' 		=> FALSE,  // Added
		);		
	
		$form['profile_address_info']['country'] 	= array(
			  '#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="select label-block">',
			  '#suffix' 			=> '</label></div>',
			  '#maxlength' 			=> 6, 
			  '#options' 			=> get_country_with_ph(),
			  '#default_value' 		=> '',
			  '#title'				=> t('Country'),
			  '#required' 			=> TRUE,
			  '#type' 				=> 'select',
			  '#ajax'				=> array(
											'event' 		=> 'change',
											'effect' 		=> 'fade',			
											'callback'		=> 'get_ajax_load_reg',
											'progress'		=>	array(
												'type'		=>'throbber',
												'message'	=>t('loading'),
											),
									)
			);

   if(isset($form_state['values']['country']) && trim($form_state['values']['country']) != '99')
	{
			$form['profile_address_info']['pincode'] = array(
				'#prefix' 	=> '<div id="ld_edit_emp_pincode_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['profile_address_info']['state'] = array(
				'#prefix' 	=> '<div id="ld_edit_emp_state_replace">',
				'#suffix' 	=> '</div>'
			);
		    $form['profile_address_info']['district'] = array(
				'#prefix' 	=> '<div id="ld_edit_emp_district_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['profile_address_info']['subdivision'] = array(
				'#prefix' 	=> '<div id="ld_empsubdv_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['profile_address_info']['areatype'] = array(
				'#prefix' 	=> '<div id="ld_emp_areatype_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['profile_address_info']['block'] = array(
				'#prefix' 	=> '<div id="ld_empareatype_name_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['profile_address_info']['panchayat'] = array(
				'#prefix' 	=> '<div id="ld_emp_vill_ward_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['profile_address_info']['policestation'] = array(
				'#prefix' 	=> '<div id="ld_empps_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['profile_address_info']['postoffice'] = array(
				'#prefix' 	=> '<div id="ld_post_office_div">',
				'#suffix' 	=> '</div>'
			);

			/*$form['profile_address_info']['mark_aadhar_start'] =array(
				'#type' 		=> 'markup',
				'#markup' 		=> 'Rima',
				'#prefix' 		=> '<div class="col-md-4 rr" id="ld_mark_aadhar_start_div">',
			);*/
			
			$form['profile_address_info']['user_aadhar_1'] = array(
			   '#prefix' 	=> '<div id="ld_user_aadhar_1_div">',
			   '#suffix' 	=> '</div>',
			);
			$form['profile_address_info']['user_aadhar_2'] = array(
			   '#prefix' 	=> '<div id="ld_user_aadhar_2_div">',
			   '#suffix' 	=> '</div>',
			);
			$form['profile_address_info']['user_aadhar_3'] = array(
			   '#prefix' 	=> '<div id="ld_user_aadhar_3_div">',
			   '#suffix' 	=> '</div>',
			);
			/*$form['profile_address_info']['mark_aadhar_end'] =array(
				'#type' 			=> 'markup',
				'#prefix' 		=> '</div>',
			);*/
			
			$form['profile_address_info']['user_passport'] 	= array(
				'#prefix' 			=> '<div id="ld_user_passport_div" class="col-md-4 col-xs-12"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Passport No.'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
			);
			$form['profile_address_info']['passport_date_of_issue'] 	= array(
				'#prefix' 			=> '<div id="ld_doi_div" class="col-md-4 col-xs-12"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Date of Issue'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class'=>array('form-control datepicker_cls'),'title'=>'Enter Date of Issue of passport.','readonly' => 'readonly'),
			);
			$form['profile_address_info']['passport_date_of_expiry'] 	= array(
				'#prefix' 			=> '<div id="ld_doe_div" class="col-md-4 col-xs-12"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Date of Expiry'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class'=>array('form-control datepicker_cls'),'title'=>'Enter Date of Expiry of passport.','readonly' => 'readonly'),
			);
			
			$form['profile_address_info']['street_name'] 	= array(
				'#prefix' 			=> '<div id="ld_streetname_div" class="col-md-4 col-xs-12"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Your Street Name / Road Name'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
			);
			$form['profile_address_info']['house_no'] 	= array(
				'#prefix' 			=> '<div class="col-md-4 col-xs-12" id="ld_houseno_div"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Your House No.'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
			);
			$form['profile_address_info']['police_station'] 	= array(
				'#prefix' 			=> '<div class="col-md-4 col-xs-12" id="ld_policestation_div"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Local Police Station'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
			);
			
	
	} else{
		
		$form['profile_address_info']['pincode'] 	= array(
		  '#prefix' 			=> '<div class="col-md-4 col-xs-12" id="ld_edit_emp_pincode_replace" ><label class="input">',
		  '#suffix' 			=> '</label></div>',
		  '#autocomplete_path' 	=> 'pinautocomplete',
		  '#id'					=> 'pincode_autocomplete',
		  '#maxlength' 			=> 6, 
		  '#title'				=>	t('Pincode'),
		  '#required' 			=> TRUE,
		  '#type' 				=> 'textfield',
		  '#attributes' 		=> array('class' => array('NoField')),
		  '#ajax'				=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',			
										'callback'		=> 'get_ajax_load_reg',
										'progress'		=>	array(
											'type'		=>'throbber',
											'message'	=>t('loading'),
										),
								)
		);
		$value_pincode				= isset($form_state['values']['pincode'])? $form_state['values']['pincode'] : '';
		
		if(!empty($value_pincode)){
			
			$query = db_select('fa_all_india_pin_code','p')
		->fields('p',array('districtname','statename','pincode','district_code','state_code','po_name'))
		->condition('p.pincode',trim($value_pincode),'=') ;
		
			$result = $query->execute();
	
			if($result->rowcount()>0){
				$final			= $result->fetchAssoc();
				$pincode_v 	= $value_pincode;
				$state_v		= $final['state_code'];
				$district_v	= $final['district_code'];
				$post_office 	= $final['po_name'];
			}
		} 
		
		if(!empty($state_v)){
			$form['profile_address_info']['state'] = array(
			   '#title'			=>	t('State'),
			   '#type' 			=> 'select',
			   '#id'			=>'state_name',
			   '#attributes' 	=> array('class'=>array(''), 'placeholder'=>'State'),
			   '#disabled' 		=> TRUE, 
			   '#required' 		=> TRUE,
			   '#options' 		=> get_all_state($state_v),
			   '#value' 		=> !empty($state_v) ? $state_v	:'',
			   '#prefix' 		=> '<div class="col-md-4" id="ld_edit_emp_state_replace" ><label class="select label-block">',
			   '#suffix' 		=> '</label></div>',
			   '#ajax'			=> array(
									'event' 		=> 'change',
									'effect' 		=> 'fade',			
									'callback'		=> 'get_ajax_load_reg',
									'progress'		=>	array(
										'type'		=>'throbber',
										'message'	=>t('loading'),
									),
					)
			);
		}else{
			$form['profile_address_info']['state'] = array(
			   '#title'			=> t('State'),
			   '#type' 			=> 'select',
			   '#id'			=>'state_name',
			   '#disabled' 		=> TRUE,
			   '#required' 		=> TRUE,
			   '#attributes' 	=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),

			   '#options' 		=> array(''=>t('Select State')),
			   '#prefix' 		=> '<div class="col-md-4" id="ld_edit_emp_state_replace" ><label class="select label-block">',
			   '#suffix' 		=> '</label></div>',
			   '#ajax'			=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',			
										'callback'		=> 'get_ajax_load_reg',
										'progress'		=>	array(
											'type'		=>'throbber',
											'message'	=>t('loading'),
										),
								)
			);
		}

		$value_state				= isset($form_state['values']['state'])? $form_state['values']['state'] : '';
		
		if(!empty($state_v)){	
			$form['profile_address_info']['district'] = array(
			   '#title'=> t('District'),
			   '#type' => 'select',
			   '#id'=>'district_name',
			   '#disabled' => TRUE,
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'District'),
			   '#options' => get_district_by_id($state_v),
			   '#value' => !empty($district_v) ? $district_v	:'',
			   '#prefix' => '<div class="col-md-4 clear-left" id="ld_edit_emp_district_replace"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#required' 		=> TRUE,
			   '#ajax'				=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',			
										'callback'		=> 'get_ajax_load_reg',
										'progress'		=>	array(
											'type'		=>'throbber',
											'message'	=>t('loading'),
										),
								)
			);
		}else{
			$form['profile_address_info']['district'] = array(
			   '#title'=>	t('District'),
			   '#type' => 'select',
			   '#id'=>'district_name',
			   '#disabled' => TRUE,
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'District'),
			   '#options' => array(''=>t('Select District')),
			   '#prefix' => '<div class="col-md-4" id="ld_edit_emp_district_replace"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#required' 		=> TRUE,
			);
		}
		
		$value_district	=	isset($form_state['values']['district']) ? $form_state['values']['district'] : '';
		
		if(!empty($district_v) && !empty($state_v) && $state_v == 1){
			
			$form['profile_address_info']['subdivision'] = array(
			   '#title'=>	t('Sub-Division'),
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'Sub Division' ),
			   '#required' 	=> TRUE,
			   '#options' => common_custom_user_subdivisionlist_list_new($district_v),
			   '#prefix' => '<div class="col-md-4" id="ld_empsubdv_replace"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#ajax'		=> array(
							'event' 		=> 'change',
							'effect' 		=> 'fade',			
							'callback'		=> 'get_ajax_load_reg',
							'progress'		=>	array(
								'type'		=>'throbber',
								'message'	=>t('loading'),
							),
					)
			);
		}else{ 
			
			$form['profile_address_info']['subdivision'] = array(
			   '#prefix' => '<div id="ld_empsubdv_replace">',
			   '#suffix' => '</div>',
			);
		}		
		$value_subdivision	=	isset($form_state['values']['subdivision']) ? $form_state['values']['subdivision'] : '';
		
		if(!empty($value_district) && !empty($value_state) && !empty($value_subdivision) && $state_v == 1){
			$form['profile_address_info']['areatype'] = array(
			   '#title'=> t('Area Type'),
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'Area Type'),
			   '#required' 		=> TRUE,
			   '#options' => common_custom_user_areatype_list_new($value_district, $value_subdivision),
			   '#prefix' => '<div class="col-md-4" id="ld_emp_areatype_replace"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#ajax'	=> array(
							'event' 		=> 'change',
							'effect' 		=> 'fade',			
							'callback'		=> 'get_ajax_load_reg',
							'progress'		=>	array(
								'type'		=>'throbber',
								'message'	=>t('loading'),
							),
					)
			);
		}else{
			
			$form['profile_address_info']['areatype'] = array(
			   '#prefix' => '<div id="ld_emp_areatype_replace">',
			   '#suffix' => '</div>',
			);
		}
		
		$value_areatype	=	isset($form_state['values']['areatype']) ? $form_state['values']['areatype'] : '';
	
		if(!empty($value_district) && !empty($value_state) && !empty($value_subdivision) && !empty($value_areatype) && $state_v == 1){
			
			if ( $value_areatype == 'B' ){
				$areatype_name	= 'Block';
			}elseif( $value_areatype == 'M'){
				$areatype_name	= 'Municipality';
			}elseif( $value_areatype == 'C'){
				$areatype_name	= 'Corporation';
			}elseif( $value_areatype == 'S'){
				$areatype_name	= 'SEZ';
			}elseif($value_areatype == 'N'){
				$areatype_name	= 'Notified Area';
			}
			
			$form['profile_address_info']['block'] = array(
			   '#title'=> $areatype_name,
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'subdivision'),
			   '#options' => common_custom_user_block_list_new($value_subdivision,$value_areatype),
			   '#prefix' => '<div class="col-md-4" id="ld_empareatype_name_replace"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#required' => TRUE,
			   '#ajax'	=> array(
							'event' 		=> 'change',
							'effect' 		=> 'fade',			
							'callback'		=> 'get_ajax_load_reg',
							'progress'		=>	array(
								'type'		=>'throbber',
								'message'	=>t('loading'),
							),
					)
			);
		}else{
			$form['profile_address_info']['block'] = array(
			   '#prefix' => '<div id="ld_empareatype_name_replace">',
			   '#suffix' => '</div>',
			);
		}
		
		$value_block 	= 	isset($form_state['values']['block']) ? $form_state['values']['block'] : '';
					
		if(!empty($value_district) && !empty($value_subdivision) && !empty($value_areatype)  && !empty($value_block) && !empty($value_state) && $state_v == 1){
			
			if ( $value_areatype == 'B' ){
				$area_name		= 'Gram Panchayat';
				$area_code 		= 'V';
			}elseif( $value_areatype == 'M'){
				$area_name		= 'Ward';
				$area_code 		= 'W';
			}elseif( $value_areatype == 'C'){
				$area_name		= 'Ward';
				$area_code 		= 'C';
			}elseif( $value_areatype == 'S'){
				$area_name		= 'Sector';
				$area_code 		= 'S';
			}elseif($value_areatype == 'N'){
				$area_name		= 'Notified Area';
				$area_code 		= 'N';
			}
					
		$form['profile_address_info']['panchayat'] = array(
		   '#title'=>$area_name,
		   '#type' => 'select',
		   '#attributes' => array('class'=>array(''), 'placeholder'=>'panchayat'),
		   '#options' => common_custom_user_villward_list_new($value_block,$area_code),
		   '#prefix' => '<div id="ld_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
		   '#suffix' => '</label></div></div>',
		   '#required' => TRUE,
		   '#ajax'=> array(
				'event' 		=> 'change',
				'effect' 		=> 'fade',			
				'callback'		=> 'get_ajax_load_reg',
				'progress'		=>	array(
					'type'		=>'throbber',
					'message'	=>t('loading'),
				),
				)
			);
		}else{
			
			$form['profile_address_info']['panchayat'] = array(
			   '#prefix' => '<div id="ld_emp_vill_ward_replace">',
			   '#suffix' => '</div>',
			);
		}
		
		$value_panchayat 	= 	isset($form_state['values']['panchayat']) ? $form_state['values']['panchayat'] : '';
		
		if(!empty($value_district) && !empty($value_subdivision) && !empty($value_areatype)  && !empty($value_block) && !empty($value_state) && !empty($value_panchayat) && $state_v == 1){
			$form['profile_address_info']['policestation'] = array(
			   '#title'=> t('Police Station'),
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'Police Station'),
			   '#required' 		=> TRUE,
			   '#options' => common_custom_user_ps_list_new($value_district),
			   '#prefix' => '<div id="ld_empps_replace"><div class="col-md-4"><label class="select label-block">',
			   '#suffix' => '</label></div></div>',
			);
		}else{
			$form['profile_address_info']['policestation'] = array(
			   '#prefix' => '<div id="ld_empps_replace">',
			   '#suffix' => '</div>',
			);
		}

			$form['profile_address_info']['postoffice'] = array(
			   '#title'=> t('Post Office'),
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'Post Office'),
			   '#options' => common_custom_post_office_list_new($pincode_v),
			   '#prefix' => '<div class="col-md-4" id="ld_post_office_div"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#required' 		=> TRUE,
			);
			
			/*$form['profile_address_info']['mark_aadhar_start'] =array(
				'#type' 		=> 'markup',
				'#prefix' 		=> '<div class="col-md-4 pp" id="mark_aadhar_start_div">',
			);*/
			
			$form['profile_address_info']['user_aadhar_1'] = array(
			   '#title'			=>	t('Aadhar No.'),
			   '#type' 			=> 'textfield',
			   '#prefix' 		=> '<div id="ld_user_aadhar_1_div" class="col-md-1 aadhar_no"><label class="input">',
			   '#suffix' 		=> '</label></div>',
			   '#attributes' => array('maxlength' => 4,'size' => '','id'=>'number1','class' => array('NoField')),
			);
			$form['profile_address_info']['user_aadhar_2'] = array(
			   '#title'			=>	t('&nbsp;'),
			   '#type' 			=> 'textfield',
			   '#prefix' 		=> '<div id="ld_user_aadhar_2_div" class="col-md-1 aadhar_no"><label class="input">',
			   '#suffix' 		=> '</label></div>',
			   '#attributes' => array('maxlength' => 4,'size' => '','id'=>'number2','class' => array('NoField')),
			);
			$form['profile_address_info']['user_aadhar_3'] = array(
			   '#title'			=>	t('&nbsp;'),
			   '#type' 			=> 'textfield',
			   '#prefix' 		=> '<div id="ld_user_aadhar_3_div" class="col-md-1 aadhar_no"><label class="input">',
			   '#suffix' 		=> '</label></div>',
			   '#attributes' => array('maxlength' => 4,'size' => '','id'=>'number3','class' => array('NoField')),
			);
			/*$form['profile_address_info']['mark_aadhar_end'] =array(
				'#type' 			=> 'markup',
				'#suffix' 		=> '</div>',
			);*/
			
		    $form['profile_address_info']['user_passport'] 	= array(
				'#prefix' 			=> '<div id="ld_user_passport_div">',
				'#suffix' 			=> '</div>',
			);
			$form['profile_address_info']['passport_date_of_issue'] 	= array(
				'#prefix' 			=> '<div id="ld_doi_div">',
				'#suffix' 			=> '</div>',
			);
			$form['profile_address_info']['passport_date_of_expiry'] 	= array(
				'#prefix' 			=> '<div id="ld_doe_div">',
				'#suffix' 			=> '</div>',
			);
			
			if(!empty($state_v) && $state_v == 1)
			{
				$form['profile_address_info']['street_name'] 	= array(
					'#prefix' 			=> '<div id="ld_streetname_div" class="col-md-4 col-xs-12"><label class="input">',
					'#suffix' 			=> '</label></div>',
					'#title'			=>	t('Enter Your Street Name / Road Name'),
					'#type' 			=> 'textfield',
					'#required' 		=> TRUE,
				);
				$form['profile_address_info']['house_no'] 	= array(
					'#prefix' 			=> '<div id="ld_houseno_div" class="col-md-4 col-xs-12"><label class="input">',
					'#suffix' 			=> '</label></div>',
					'#title'			=>	t('Enter Your House No.'),
					'#type' 			=> 'textfield',
					'#required' 		=> TRUE,
				);
				$form['profile_address_info']['police_station'] 	= array(
					'#prefix' 			=> '<div id="ld_policestation_div">',
					'#suffix' 			=> '</div>',
				);

			} else {
				$form['profile_address_info']['street_name'] 	= array(
					'#prefix' 			=> '<div id="ld_streetname_div" class="col-md-4 col-xs-12"><label class="input">',
					'#suffix' 			=> '</label></div>',
					'#title'			=>	t('Enter Your Street Name / Road Name'),
					'#type' 			=> 'textfield',
					'#required' 		=> TRUE,
				);
				$form['profile_address_info']['house_no'] 	= array(
					'#prefix' 			=> '<div id="ld_houseno_div" class="col-md-4 col-xs-12"><label class="input">',
					'#suffix' 			=> '</label></div>',
					'#title'			=>	t('Enter Your House No.'),
					'#type' 			=> 'textfield',
					'#required' 		=> TRUE,
				);
				$form['profile_address_info']['police_station'] 	= array(
					'#prefix' 			=> '<div id="ld_policestation_div" class="col-md-4 col-xs-12"><label class="input">',
					'#suffix' 			=> '</label></div>',
					'#title'			=>	t('Enter Local Police Station'),
					'#type' 			=> 'textfield',
					'#required' 		=> TRUE,
				);
			}	
			
			
	 
	 
	 }
	 
	$form['profile_address_info']['addrline'] = array(
		   '#title'=>'Address',
		   '#rows'=> 3,
		   '#type' => 'textarea',
		   '#required' => TRUE,
		   '#attributes' => array('class'=>array(''), 'placeholder'=>'Address Line'),
		   '#prefix'=> '<div class="col-md-12"><label class="textarea label-block">',
	   	   '#suffix' =>'</label></div>',
	);

	// OTHER INFORMATION
	
	 $user_type = isset($form_state['values']['user_type'])? $form_state['values']['user_type'] : '';	
	
		//if($user_type == 'occupier'){
			$form['profile_other_info'] = array(
				'#type' 			=> 'fieldset',
				'#title' 			=> t('Other Details (required for login credential)'),
				'#collapsible' 		=> FALSE, // Added
				'#collapsed' 		=> FALSE,  // Added
				//'#prefix'		 	=> '<div id="otherdetails_ow_div">',
				//'#suffix' 			=> '</div>',
			);
		//}
			
		$form['profile_other_info']['is_occupier'] = array(
			'#prefix'		 	=> '<div id="is_occupier_id">',
			'#suffix' 			=> '</div>',
		);
		$form['profile_other_info']['ownership_type'] = array(
			'#prefix'		 	=> '<div id="ownership_type_id">',
			'#suffix' 			=> '</div>',
		);
		$form['profile_other_info']['occupier_type'] = array(
			'#prefix' 			=> '<div id="occupier_type_id">',
			'#suffix' 			=> '</div>',
		);

		// OCCUPIER
		if($user_type == 'occupier')
		{
			$ownershiptype  = array(
					"0" => "Select",
					"pv" 			=> "Private Ltd Company",
					"ltd" 			=> "Public Ltd Company",
					"par_firm" 		=> "Partnership Firm",
					"pro_firm" 		=> "Proprietorship Firm",
					"llp" 			=> "Limited Liability Partnership",
					"cooperative" 	=> "Co-operative",
					"registered" 	=> "Registered Society under Society Register",
					"govt" 			=> "Government(State/Central)",
					"psu" 			=> "Public Sector Undertaking",
					"localbody" 	=> "Local Body",
					"others" 		=> "Others",
				);
				
				$form['profile_other_info']['ownership_type'] = array(
					'#prefix'		 	=> '<div id="ownership_type_id"><div class="col-md-6 col-xs-12"><label class="select label-block">',
					'#suffix' 			=> '</label></div>',
					'#title' 			=> t('Type of Ownership'),
					'#options'			=> $ownershiptype,
					'#type' 			=> 'select',
					'#required' 		=> TRUE,
					'#ajax' 			=> array(
												'event' => 'change',
												'effect' => 'fade',
												'callback' => 'get_ajax_load_ownership',
												'progress' => array(
													'type' => 'throbber',
													'message' => t('loading')
												)
										)
				);
				
			$value_ownership_type   = isset($form_state['values']['ownership_type']) ? $form_state['values']['ownership_type'] : '';
		
			if($value_ownership_type == 'par_firm' || $value_ownership_type == 'llp')
			{
				$form['profile_other_info']['occupier_type'] = array(
					'#prefix' => '<div id="occupier_type_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
					'#suffix' => '</label></div></div>',
					'#title' => t('Occupier Type'),
					'#type' => 'textfield',
					'#required' 		=> TRUE,
					'#value'        => 'Partner',
					'#attributes' 		=> array(
					   'readonly' => 'readonly'
					),
				);
		
			} elseif($value_ownership_type == 'cooperative' || $value_ownership_type == 'registered')
			{
				$form['profile_other_info']['occupier_type'] = array(
					'#prefix' => '<div id="occupier_type_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
					'#suffix' => '</label></div></div>',
					'#title' => t('Occupier Type'),
					'#required' 		=> TRUE,
					'#type' => 'textfield',
					'#value'        => 'Nominated Occupier',
					'#attributes' 		=> array(
					   'readonly' => 'readonly'
					),
				);
		
			} elseif($value_ownership_type == 'govt' || $value_ownership_type == 'psu' || $value_ownership_type == 'others' || $value_ownership_type == 'localbody')
			{
				$form['profile_other_info']['occupier_type'] = array(
					'#prefix' => '<div id="occupier_type_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
					'#suffix' => '</label></div></div>',
					'#title' => t('Occupier Type'),
					'#required' 		=> TRUE,
					'#type' => 'textfield',
					'#value'        => 'Nominated',
					'#attributes' 		=> array(
					   'readonly' => 'readonly'
					),
				);
		
			} elseif($value_ownership_type == 'pv' || $value_ownership_type == 'ltd')
			{
				$form['profile_other_info']['occupier_type'] = array(
					'#prefix' => '<div id="occupier_type_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
					'#suffix' => '</label></div></div>',
					'#title' => t('Occupier Type'),
					'#required' 		=> TRUE,
					'#type' => 'textfield',
					'#value'        => 'Director',
					'#attributes' 		=> array(
					   'readonly' => 'readonly'
					),
				);
		
			} elseif($value_ownership_type == 'pro_firm')
			{
				$form['profile_other_info']['occupier_type'] = array(
					'#prefix' => '<div id="occupier_type_id"><div class="col-md-6 col-xs-12"><label class="input label-block">',
					'#suffix' => '</label></div></div>',
					'#title' => t('Occupier Type'),
					'#required' 		=> TRUE,
					'#type' => 'textfield',
					'#value'        => 'Proprietor',
					'#attributes' 		=> array(
					   'readonly' => 'readonly'
					),
				);
		
			} else {
				
				$form['profile_other_info']['occupier_type'] = array(
					'#prefix' => '<div id="occupier_type_id">',
					'#suffix' => '</div>',
				);
			}
			
			}
			
		// OWNER
		if($user_type == 'owner')
		{
			$option  = array("Y" => "Yes","N" => "No");
				
				$form['profile_other_info']['is_occupier'] = array(
					'#prefix'		 	=> '<div id="is_occupier_id"><div class="col-md-4 col-xs-12">',
					'#suffix' 			=> '</div></div>',
					'#title'			=>	t('Are you occupier of factory ?'),
					'#options'			=> $option,
					'#type' 			=> 'radios',
					'#required' 		=> TRUE,
					'#ajax' 			=> array(
												'event' => 'change',
												'effect' => 'fade',
												'callback' => 'get_ajax_load_ownership',
												'progress' => array(
													'type' => 'throbber',
													'message' => t('loading')
												)
										)
				);
				
				$value_is_occupier = isset($form_state['values']['is_occupier'])? $form_state['values']['is_occupier'] : '';
				$value_firstname = isset($form_state['values']['firstname'])? $form_state['values']['firstname'] : '';
				$value_middlename = isset($form_state['values']['middlename'])? $form_state['values']['middlename'] : '';
				$value_lastname = isset($form_state['values']['lastname'])? $form_state['values']['lastname'] : '';
				$value_email = isset($form_state['values']['email'])? $form_state['values']['email'] : '';
				$value_mobile = isset($form_state['values']['mobile'])? $form_state['values']['mobile'] : '';

				if($value_is_occupier == 'Y')
				{
					$ownershiptype  = array(
						"0" => "Select",
						"pv" 			=> "Pvt Ltd Company",
						"ltd" 			=> "Ltd Company",
						"par_firm" 		=> "Partnership Firm",
						"pro_firm" 		=> "Proprietorship Firm",
						"llp" 			=> "Limited Liability Partnership",
						"cooperative" 	=> "Co-operative",
						"registered" 	=> "Registered Society under Society Register",
						"govt" 			=> "Government(State/Central)",
						"psu" 			=> "Public Sector Undertaking",
						"localbody" 	=> "Local Body",
						"others" 		=> "Others",
					);
				
					$form['profile_other_info']['ownership_type'] = array(
						'#prefix'		 	=> '<div id="ownership_type_id"><div class="col-md-4 col-xs-12"><label class="select label-block">',
						'#suffix' 			=> '</label></div>',
						'#title' 			=> t('Type of Ownership'),
						'#options'			=> $ownershiptype,
						'#type' 			=> 'select',
						'#required' 		=> TRUE,
						'#ajax' 			=> array(
													'event' => 'change',
													'effect' => 'fade',
													'callback' => 'get_ajax_load_ownership',
													'progress' => array(
														'type' => 'throbber',
														'message' => t('loading')
													)
											)
					);
				
					$value_ownership_type   = isset($form_state['values']['ownership_type']) ? $form_state['values']['ownership_type'] : '';
				
					if($value_ownership_type == 'par_firm' || $value_ownership_type == 'llp')
					{
						$form['profile_other_info']['occupier_type'] = array(
							'#prefix' => '<div id="occupier_type_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
							'#suffix' => '</label></div></div>',
							'#title' => t('Occupier Type'),
							'#type' => 'textfield',
							'#required' 		=> TRUE,
							'#value'        => 'Partner',
							'#attributes' 		=> array(
							   'readonly' => 'readonly'
							),
						);
				
					} elseif($value_ownership_type == 'cooperative' || $value_ownership_type == 'registered')
					{
						$form['profile_other_info']['occupier_type'] = array(
							'#prefix' => '<div id="occupier_type_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
							'#suffix' => '</label></div></div>',
							'#title' => t('Occupier Type'),
							'#required' 		=> TRUE,
							'#type' => 'textfield',
							'#value'        => 'Nominated Occupier',
							'#attributes' 		=> array(
							   'readonly' => 'readonly'
							),
						);
				
					} elseif($value_ownership_type == 'govt' || $value_ownership_type == 'psu' || $value_ownership_type == 'others' || $value_ownership_type == 'localbody')
					{
						$form['profile_other_info']['occupier_type'] = array(
							'#prefix' => '<div id="occupier_type_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
							'#suffix' => '</label></div></div>',
							'#title' => t('Occupier Type'),
							'#required' 		=> TRUE,
							'#type' => 'textfield',
							'#value'        => 'Nominated',
							'#attributes' 		=> array(
							   'readonly' => 'readonly'
							),
						);
				
					} elseif($value_ownership_type == 'pv' || $value_ownership_type == 'ltd')
					{
						$form['profile_other_info']['occupier_type'] = array(
							'#prefix' => '<div id="occupier_type_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
							'#suffix' => '</label></div></div>',
							'#title' => t('Occupier Type'),
							'#required' 		=> TRUE,
							'#type' => 'textfield',
							'#value'        => 'Director',
							'#attributes' 		=> array(
							   'readonly' => 'readonly'
							),
						);
				
					} elseif($value_ownership_type == 'pro_firm')
					{
						$form['profile_other_info']['occupier_type'] = array(
							'#prefix' => '<div id="occupier_type_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
		
							'#suffix' => '</label></div></div>',
							'#title' => t('Occupier Type'),
							'#required' 		=> TRUE,
							'#type' => 'textfield',
							'#value'        => 'Proprietor',
							'#attributes' 		=> array(
							   'readonly' => 'readonly'
							),
						);
				
					} else {
						
						$form['profile_other_info']['occupier_type'] = array(
							'#prefix' => '<div id="occupier_type_id">',
							'#suffix' => '</div>',
						);
					}
			
					$form['profile_other_info']['occupier_first_name_y'] = array(
						'#prefix'		 	=> '<div id="occupier_first_name_y_id"><div class="col-md-4 col-xs-12"><label class="input">',
						'#suffix' 			=> '</label></div></div>',
						'#title' 			=> t('Occupier First Name'),
						'#type' 			=> 'textfield',
						'#default_value' 	=> $value_firstname,
						'#attributes' 		=> array('disabled' => 'disabled')
					);
					$form['profile_other_info']['occupier_middle_name_y'] = array(
						'#prefix'		 	=> '<div id="occupier_middle_name_y_id"><div class="col-md-4 col-xs-12"><label class="input">',
						'#suffix' 			=> '</label></div></div>',
						'#title' 			=> t('Occupier Middle Name'),
						'#type' 			=> 'textfield',
						'#default_value' 	=> $value_middlename,
						'#attributes' 		=> array('disabled' => 'disabled')
					);
					$form['profile_other_info']['occupier_last_name_y'] = array(
						'#prefix'		 	=> '<div id="occupier_last_name_y_id"><div class="col-md-4 col-xs-12"><label class="input">',
						'#suffix' 			=> '</label></div></div>',
						'#title' 			=> t('Occupier Last Name'),
						'#type' 			=> 'textfield',
						'#default_value' 	=> $value_lastname,
						'#attributes' 		=> array('disabled' => 'disabled')
					);
					$form['profile_other_info']['occupier_email_y'] = array(
						'#prefix'		 	=> '<div id="occupier_email_y_id"><div class="col-md-4 col-xs-12"><label class="input">',
						'#suffix' 			=> '</label></div></div>',
						'#title' 			=> t('Occupier Email'),
						'#type' 			=> 'textfield',
						'#default_value' 	=> $value_email,
						'#attributes' 		=> array('disabled' => 'disabled')
					);
					$form['profile_other_info']['occupier_mobile_y'] = array(
						'#prefix'		 	=> '<div id="occupier_mobile_y_id"><div class="col-md-4 col-xs-12"><label class="input">',
						'#suffix' 			=> '</label></div></div>',
						'#title' 			=> t('Occupier Mobile'),
						'#type' 			=> 'textfield',
						'#default_value' 	=> $value_mobile,
						'#attributes' 		=> array('disabled' => 'disabled'),
		  				'#maxlength' 			=> 10
					);
				} else {
									
					$form['profile_other_info']['ownership_type'] = array(
						'#prefix'		 	=> '<div id="ownership_type_id">',
						'#suffix' 			=> '</div>',
					);
					$form['profile_other_info']['occupier_type'] = array(
						'#prefix' 			=> '<div id="occupier_type_id">',
						'#suffix' 			=> '</div>',
					);
					$form['profile_other_info']['occupier_first_name_y'] = array(
						'#prefix'		 	=> '<div id="occupier_first_name_y_id">',
						'#suffix' 			=> '</div>',
					);
					$form['profile_other_info']['occupier_middle_name_y'] = array(
						'#prefix'		 	=> '<div id="occupier_middle_name_y_id">',
						'#suffix' 			=> '</div>',
					);
					$form['profile_other_info']['occupier_last_name_y'] = array(
						'#prefix'		 	=> '<div id="occupier_last_name_y_id">',
						'#suffix' 			=> '</div>',
					);
					$form['profile_other_info']['occupier_email_y'] = array(
						'#prefix'		 	=> '<div id="occupier_email_y_id">',
						'#suffix' 			=> '</div>',
					);
					$form['profile_other_info']['occupier_mobile_y'] = array(
						'#prefix'		 	=> '<div id="occupier_mobile_y_id">',
						'#suffix' 			=> '</div>',
					);
				}
				
				if($value_is_occupier == 'N')
				{
					$form['profile_other_info']['occupier_first_name_n'] = array(
						'#prefix'		 	=> '<div id="occupier_first_name_n_id"><div class="col-md-4 col-xs-12"><label class="input">',
						'#suffix' 			=> '</label></div></div>',
						'#title' 			=> t('Occupier First Name'),
						'#type' 			=> 'textfield',
						'#required' 		=> TRUE,
						'#attributes' 		=> array('class' => array('charField'))
					);
					$form['profile_other_info']['occupier_middle_name_n'] = array(
						'#prefix'		 	=> '<div id="occupier_middle_name_n_id"><div class="col-md-4 col-xs-12"><label class="input">',
						'#suffix' 			=> '</label></div></div>',
						'#title' 			=> t('Occupier Middle Name'),
						'#type' 			=> 'textfield',
						'#attributes' 		=> array('class' => array('charField'))
					);
					$form['profile_other_info']['occupier_last_name_n'] = array(
						'#prefix'		 	=> '<div id="occupier_last_name_n_id"><div class="col-md-4 col-xs-12"><label class="input">',
						'#suffix' 			=> '</label></div></div>',
						'#title' 			=> t('Occupier Last Name'),
						'#type' 			=> 'textfield',
						'#required' 		=> TRUE,
						'#attributes' 		=> array('class' => array('charField'))
					);
					$form['profile_other_info']['occupier_email_n'] = array(
						'#prefix'		 	=> '<div id="occupier_email_n_id"><div class="col-md-4 col-xs-12"><label class="input">',
						'#suffix' 			=> '</label></div></div>',
						'#title' 			=> t('Occupier Email'),
						'#type' 			=> 'textfield',
						'#required' 		=> TRUE,
					);
					$form['profile_other_info']['occupier_mobile_n'] = array(
						'#prefix'		 	=> '<div id="occupier_mobile_n_id"><div class="col-md-4 col-xs-12"><label class="input">',
						'#suffix' 			=> '</label></div></div>',
						'#title' 			=> t('Occupier Mobile'),
						'#type' 			=> 'textfield',
						'#required' 		=> TRUE,
						'#attributes' 		=> array('class' => array('NoField')),
		  				'#maxlength' 		=> 10
					);
				} else {
									
					$form['profile_other_info']['occupier_first_name_n'] = array(
						'#prefix'		 	=> '<div id="occupier_first_name_n_id">',
						'#suffix' 			=> '</div>',
					);
					$form['profile_other_info']['occupier_middle_name_n'] = array(
						'#prefix'		 	=> '<div id="occupier_middle_name_n_id">',
						'#suffix' 			=> '</div>',
					);
					$form['profile_other_info']['occupier_last_name_n'] = array(
						'#prefix'		 	=> '<div id="occupier_last_name_n_id">',
						'#suffix' 			=> '</div>',
					);
					$form['profile_other_info']['occupier_email_n'] = array(
						'#prefix'		 	=> '<div id="occupier_email_n_id">',
						'#suffix' 			=> '</div>',
					);
					$form['profile_other_info']['occupier_mobile_n'] = array(
						'#prefix'		 	=> '<div id="occupier_mobile_n_id">',
						'#suffix' 			=> '</div>',
					);
				}
				
		} else {
				
				// IF YES
				$form['profile_other_info']['occupier_first_name_y'] = array(
					'#prefix'		 	=> '<div id="occupier_first_name_y_id">',
					'#suffix' 			=> '</div>',
				);
				$form['profile_other_info']['occupier_middle_name_y'] = array(
					'#prefix'		 	=> '<div id="occupier_middle_name_y_id">',
					'#suffix' 			=> '</div>',
				);
				$form['profile_other_info']['occupier_last_name_y'] = array(
					'#prefix'		 	=> '<div id="occupier_last_name_y_id">',
					'#suffix' 			=> '</div>',
				);
				$form['profile_other_info']['occupier_email_y'] = array(
					'#prefix'		 	=> '<div id="occupier_email_y_id">',
					'#suffix' 			=> '</div>',
				);
				$form['profile_other_info']['occupier_mobile_y'] = array(
					'#prefix'		 	=> '<div id="occupier_mobile_y_id">',
					'#suffix' 			=> '</div>',
				);
				
				// IF NO
				$form['profile_other_info']['occupier_first_name_n'] = array(
					'#prefix'		 	=> '<div id="occupier_first_name_n_id">',
					'#suffix' 			=> '</div>',
				);
				$form['profile_other_info']['occupier_middle_name_n'] = array(
					'#prefix'		 	=> '<div id="occupier_middle_name_n_id">',
					'#suffix' 			=> '</div>',
				);
				$form['profile_other_info']['occupier_last_name_n'] = array(
					'#prefix'		 	=> '<div id="occupier_last_name_n_id">',
					'#suffix' 			=> '</div>',
				);
				$form['profile_other_info']['occupier_email_n'] = array(
					'#prefix'		 	=> '<div id="occupier_email_n_id">',
					'#suffix' 			=> '</div>',
				);
				$form['profile_other_info']['occupier_mobile_n'] = array(
					'#prefix'		 	=> '<div id="occupier_mobile_n_id">',
					'#suffix' 			=> '</div>',
				);
		}

		// CONSULTANT
		if($user_type == 'consultant')
		{
			$form['profile_other_info']['occupier_first_name_c'] = array(
				'#prefix'		 	=> '<div id="occupier_first_name_c_id"><div class="col-md-4 col-xs-12"><label class="input rest">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('Occupier First Name'),
				'#type' 			=> 'textfield',
				'#required'         => TRUE,
				'#attributes' 		=> array('class' => array('charField'))
			);
			$form['profile_other_info']['occupier_middle_name_c'] = array(
				'#prefix'		 	=> '<div id="occupier_middle_name_c_id"><div class="col-md-4 col-xs-12"><label class="input">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('Occupier Middle Name'),
				'#type' 			=> 'textfield',
				'#attributes' 		=> array('class' => array('charField'))
			);
			$form['profile_other_info']['occupier_last_name_c'] = array(
				'#prefix'		 	=> '<div id="occupier_last_name_c_id"><div class="col-md-4 col-xs-12"><label class="input">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('Occupier Last Name'),
				'#type' 			=> 'textfield',
				'#required'         => TRUE,
				'#attributes' 		=> array('class' => array('charField'))
			);
			$form['profile_other_info']['occupier_email_c'] = array(
				'#prefix'		 	=> '<div id="occupier_email_c_id"><div class="col-md-4 col-xs-12"><label class="input">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('Occupier Email'),
				'#type' 			=> 'textfield',
				'#required'         => TRUE
			);
			$form['profile_other_info']['occupier_mobile_c'] = array(
				'#prefix'		 	=> '<div id="occupier_mobile_c_id"><div class="col-md-4 col-xs-12"><label class="input">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('Occupier Mobile'),
				'#type' 			=> 'textfield',
				'#required'         => TRUE,
				'#attributes' 		=> array('class' => array('NoField')),
		  		'#maxlength' 		=> 10
			);
				
		} else {
			
				$form['profile_other_info']['otherdetails_cn'] = array(
					'#prefix'		 	=> '<div id="otherdetails_cn_div">',
					'#suffix' 			=> '</div>',
				);
				$form['profile_other_info']['occupier_first_name_c'] = array(
					'#prefix'		 	=> '<div id="occupier_first_name_c_id">',
					'#suffix' 			=> '</div>',
				);
				$form['profile_other_info']['occupier_middle_name_c'] = array(
					'#prefix'		 	=> '<div id="occupier_middle_name_c_id">',
					'#suffix' 			=> '</div>',
				);
				$form['profile_other_info']['occupier_last_name_c'] = array(
					'#prefix'		 	=> '<div id="occupier_last_name_c_id">',
					'#suffix' 			=> '</div>',
				);
				$form['profile_other_info']['occupier_email_c'] = array(
					'#prefix'		 	=> '<div id="occupier_email_c_id">',
					'#suffix' 			=> '</div>',
				);
				$form['profile_other_info']['occupier_mobile_c'] = array(
					'#prefix'		 	=> '<div id="occupier_mobile_c_id">',
					'#suffix' 			=> '</div>',
				);
		}		

		$form['profile_declaration_info']['terms_accept'] = array(
			'#type' => 'checkbox',
			'#prefix' => '<div class="row"><div class="col-md-12">',
			'#suffix' => '</div>',
			'#title' => t('I/we hereby declare that I/we will be responsible for the authenticity of the information provided in this application and are completely accountable for the liability thereof. I will be responsible for consequences of misinformation / incorrect information as per the law'),
			'#required' => TRUE
		);

	$form['submit'] = array (
	  '#prefix'=> '<div class="col-md-12">',  
	  '#suffix' => '</div></div>',
	  '#attributes' => array('class'=>array('btn btn-success form-submit')),
	  '#type' => 'submit',
	  '#value' => 'Save & Continue'
	);
	return $form; 
 }

function applicant_registration_form_validate($form, &$form_state) {
	
	//drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/sky-forms.css');	 
    
	$firstname = $form_state['values']['firstname'];
	if (!preg_match('/[A-Za-z]+$/', $firstname)) {  
		form_set_error('firstname', t('Your first name should be text only'));
	}

	$middlename = $form_state['values']['middlename'];
//	if (!preg_match('/[A-Za-z]+$/', $middlename)) {  
//		form_set_error('middlename', t('Your middle name should be text only'));
//	}
	$lastname = $form_state['values']['lastname'];
	if (!preg_match('/[A-Za-z]+$/', $lastname)) {  
		form_set_error('lastname', t('Your last name should be text only'));
	}
	
	if (!$form_state['values']['mobile']) {
    	form_set_error('mobile', 'Please enter your mobile number');    
  	}
  
  	if ($form_state['values']['mobile']!="" && (strlen($form_state['values']['mobile'])<10 || strlen($form_state['values']['mobile'])>10)) {
    	form_set_error('mobile', 'Mobile number should be of 10 digit');    
  	}
  
 	$mobile = $form_state['values']['mobile'];
	if (!preg_match('/^[6789][0-9]{9}$/', $mobile)) {  
    	form_set_error('mobile', t('Mobile number must start with the digit 6 or 7 or 8 or 9!'));
  	}	   
    
	$email = $form_state['values']['email'];
	if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
		form_set_error('email', t('Please enter a valid e-mail id')); 
	}  

	$password = $form_state['values']['password'];
	if (!preg_match('/^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=\S*[\W]).{8,10}$/', $password)) {  //(?=.*\d)=number //(?=.*[a-z])=smallest //(?=.*[A-Z])=largest //(?=\S*[\W])=special char
		form_set_error('password', t('Please enter a valid password'));
	}

	$re_password = $form_state['values']['reenter_password'];
	if ($password != $re_password) {  
		form_set_error('reenter_password', t('Please re-enter correct password'));
	}
	
	/*$aadhar1 =  $form_state['values']['user_aadhar_1'];
	$aadhar2 =  $form_state['values']['user_aadhar_2'];
	$aadhar3 =  $form_state['values']['user_aadhar_3'];
	if (($aadhar1 == '') || ($aadhar2 == '') || ($aadhar3 == '')) {  
		if ($aadhar1 == '') { 
			form_set_error('user_aadhar_1', t('Please enter correct Aadhar No.'));
		}elseif ($aadhar2 == '') { 
			form_set_error('user_aadhar_2', t('Please enter correct Aadhar No.'));
		}elseif ($aadhar3 == '') { 
			form_set_error('user_aadhar_3', t('Please enter correct Aadhar No.'));
		}
	}*/

	$qry_chk_username_result	= 	array();
	$qry_chk_username 			= 	db_select('users', 'U');
	$qry_chk_username			->	fields('U',  array('name'));
	$qry_chk_username			->	condition('U.name',trim($form_state['values']['username']),'=');
	$qry_chk_username_result 	= 	$qry_chk_username->execute()->fetchObject();
	if(!empty($qry_chk_username_result)){
		form_set_error('username', t( 'Username already exists'));
	}
	
	/*$qry_chk_email_result	= 	array();
	$qry_chk_email 			= 	db_select('users', 'U');
	$qry_chk_email			->	fields('U',  array('mail'));
	$qry_chk_email			->	condition('U.mail',trim($form_state['values']['email']),'=');
	$qry_chk_email_result 	= 	$qry_chk_email->execute()->fetchObject();
	if(!empty($qry_chk_email_result)){
		form_set_error('email', t( 'Email already exists'));
	}*/
  }  
function applicant_registration_form_submit($form, &$form_state) {
	global $base_root, $base_path,$user;
	
	if($form_state['values']['user_type'] == 'owner')
	{
		if($form_state['values']['is_occupier'] == 'Y')
		{
			$occupier_first_name  = $form_state['values']['occupier_first_name_y'];
			$occupier_middle_name = $form_state['values']['occupier_middle_name_y'];
			$occupier_last_name   = $form_state['values']['occupier_last_name_y'];
			$occupier_email       = $form_state['values']['occupier_email_y'];
			$occupier_mobile      = $form_state['values']['occupier_mobile_y'];
			$ownership_type  	  = $form_state['values']['ownership_type'];
			$occupier_type        = $form_state['values']['occupier_type'];

		} else {
			$occupier_first_name  = $form_state['values']['occupier_first_name_n'];
			$occupier_middle_name = $form_state['values']['occupier_middle_name_n'];
			$occupier_last_name   = $form_state['values']['occupier_last_name_n'];
			$occupier_email       = $form_state['values']['occupier_email_n'];
			$occupier_mobile      = $form_state['values']['occupier_mobile_n'];
		}
	}
	elseif($form_state['values']['user_type'] == 'occupier')
	{
		$ownership_type  = $form_state['values']['ownership_type'];
		$occupier_type   = $form_state['values']['occupier_type'];
		$occupier_email       = $form_state['values']['email'];
		$occupier_mobile      = $form_state['values']['mobile'];
	}
	elseif($form_state['values']['user_type'] == 'consultant')
	{		
		$occupier_first_name  = $form_state['values']['occupier_first_name_c'];
		$occupier_middle_name = $form_state['values']['occupier_middle_name_c'];
		$occupier_last_name   = $form_state['values']['occupier_last_name_c'];
		$occupier_email       = $form_state['values']['occupier_email_c'];
		$occupier_mobile      = $form_state['values']['occupier_mobile_c'];
	}
	
	$dob = !empty($form_state['values']['dob']) ? date('Y-m-d', strtotime($form_state['values']['dob'])) : NULL;//'NULL'
	$passport_date_of_issue = !empty($form_state['values']['passport_date_of_issue']) ? date('Y-m-d', strtotime($form_state['values']['passport_date_of_issue'])) : NULL;//
	$passport_date_of_expiry = !empty($form_state['values']['passport_date_of_expiry']) ? date('Y-m-d', strtotime($form_state['values']['passport_date_of_expiry'])) : NULL;//'NULL'

	$find_email = find_existing_email($form_state['values']['email']);
	$find_mobile = find_existing_mobile($form_state['values']['mobile']);
	$find_occu_email = find_existing_email($occupier_email);
	$find_occu_mobile = find_existing_mobile($occupier_mobile); 
	
	if($find_email==1){
		drupal_set_message('Email Id. already exist.','error');
	} else if($find_mobile==1){
		drupal_set_message('Mobile No. already exist.','error');
	} else if($find_occu_email==1){
		drupal_set_message('Occupier Email Id. already exist.','error');
	} else if($find_occu_mobile==1){
		drupal_set_message('Occupier Mobile No. already exist.','error');
	} else {
		
		$newUser 	= 	array(
						'name' 		=> trim($form_state['values']['username']),
						'pass' 		=> trim($form_state['values']['password']),
						'mail' 		=> trim($form_state['values']['email']),
						'status' 	=> 1,
						'init' 		=> trim($form_state['values']['email']),
					);
		user_save(null, $newUser);
		$txtValue					=	trim($form_state['values']['username']); 
		$fetch_info_querys 			= 	db_select('users', 'U');
		$fetch_info_querys->fields('U',  array('uid'));
		$fetch_info_querys->condition('U.name',$txtValue);
		$fetch_info_querys_result 	= 	$fetch_info_querys->execute()->fetchObject();
		$lastId	            		=	$fetch_info_querys_result->uid;
		
		$middlename    				=	isset($form_state['values']['middlename']) ? $form_state['values']['middlename'].' ': '';
		$fullname        			=   $form_state['values']['firstname'].' '.$middlename.$form_state['values']['lastname'];
		
		$userRole 			= 	array(
									'uid' => $lastId,
									'rid' => '4'
								);
		db_insert('users_roles')->fields($userRole)->execute();
	
	$registrationInfo =	array(
				'uid'      				=> $lastId,
				'fullname' 				=> $fullname,
				'firstname' 			=> $form_state['values']['firstname'],
				'middlename' 			=> $form_state['values']['middlename'],
				'lastname' 				=> $form_state['values']['lastname'],
				'gurdian_name'			=> $form_state['values']['gurdian_name'],
				'email' 				=> $form_state['values']['email'],
				'mobile' 				=> $form_state['values']['mobile'],
				'username' 				=> $form_state['values']['username'],
				'password' 				=> $form_state['values']['password'],
				'dob' 					=> $dob,
				'gender' 				=> $form_state['values']['gender'],
				'country' 				=> $form_state['values']['country'],
				'pincode' 				=> !empty($form_state['values']['pincode'])? $form_state['values']['pincode'] : 0 ,
				'state' 				=> !empty($form_state['values']['state'])? $form_state['values']['state'] : 0 ,
				'district' 				=> !empty($form_state['values']['district'])? $form_state['values']['district'] : 0 ,
				'subdivision' 			=> !empty($form_state['values']['subdivision'])? $form_state['values']['subdivision'] : 0 ,
				'areatype' 				=> !empty($form_state['values']['areatype'])? $form_state['values']['areatype'] : 0 ,
				'block' 				=> !empty($form_state['values']['block'])? $form_state['values']['block'] : 0 ,
				'panchayat' 			=> !empty($form_state['values']['panchayat'])? $form_state['values']['panchayat'] : 0 ,
				'policestation' 		=> !empty($form_state['values']['policestation'])? $form_state['values']['policestation'] : 0 ,
				'postoffice' 			=> $form_state['values']['postoffice'],
				'street_name'			=> $form_state['values']['street_name'],
				'house_no'				=> $form_state['values']['house_no'],
				'police_station' 		=> $form_state['values']['police_station'],
				'addrline' 				=> $form_state['values']['addrline'],
				'terms_accept' 			=> $form_state['values']['terms_accept'],
				'user_type'				=> !empty($form_state['values']['user_type'])? $form_state['values']['user_type'] : 0,
				'is_occupier' 			=> !empty($form_state['values']['is_occupier'])? $form_state['values']['is_occupier'] : 0,
				'occupier_first_name' 	=> $occupier_first_name,
				'occupier_middle_name' 	=> $occupier_middle_name,
				'occupier_last_name' 	=> $occupier_last_name,
				'occupier_email' 		=> $occupier_email,
				'occupier_mobile' 		=> $occupier_mobile,
				'ownership_type' 		=> $ownership_type,
				'occupier_type' 		=> $occupier_type,
				'user_passport'			=> !empty($form_state['values']['user_passport'])? $form_state['values']['user_passport'] : 0,
				'passport_date_of_issue'			=> $passport_date_of_issue,
				'passport_date_of_expiry'		=> $passport_date_of_expiry,
				'user_aadhar'		    => $form_state['values']['user_aadhar_1'].'-'.$form_state['values']['user_aadhar_2'].'-'.$form_state['values']['user_aadhar_3'],									);
			
			//echo "<pre>"; print_r($registrationInfo);die;
			//echo db_insert('fa_user_details')->fields($registrationInfo); 
			//die;
					
		if(db_insert('fa_user_details')->fields($registrationInfo)->execute())
		{	
			drupal_set_message('Registration has been done successfully.');
			drupal_goto('/user/login');
		}	
	} 
}
function get_ajax_load_reg($form, $form_state){
	//echo $form_state['values']['country'];
	$commands = array();
	$commands[] = ajax_command_replace('#ld_edit_emp_pincode_replace', drupal_render($form['profile_address_info']['pincode']));
	$commands[] = ajax_command_replace('#ld_edit_emp_state_replace', drupal_render($form['profile_address_info']['state']));
	$commands[] = ajax_command_replace('#ld_edit_emp_district_replace', drupal_render($form['profile_address_info']['district']));
	$commands[] = ajax_command_replace('#ld_empsubdv_replace', drupal_render($form['profile_address_info']['subdivision']));
	$commands[] = ajax_command_replace('#ld_emp_areatype_replace', drupal_render($form['profile_address_info']['areatype']));
	$commands[] = ajax_command_replace('#ld_empareatype_name_replace', drupal_render($form['profile_address_info']['block']));
	$commands[] = ajax_command_replace('#ld_emp_vill_ward_replace', drupal_render($form['profile_address_info']['panchayat']));
	$commands[] = ajax_command_replace('#ld_empps_replace', drupal_render($form['profile_address_info']['policestation']));
	$commands[] = ajax_command_replace('#ld_post_office_div', drupal_render($form['profile_address_info']['postoffice']));
	
	//$commands[] = ajax_command_replace('#mark_aadhar_start_div', drupal_render($form['profile_address_info']['mark_aadhar_start']));
	$commands[] = ajax_command_replace('#ld_user_aadhar_1_div', drupal_render($form['profile_address_info']['user_aadhar_1']));
	$commands[] = ajax_command_replace('#ld_user_aadhar_2_div', drupal_render($form['profile_address_info']['user_aadhar_2']));
	$commands[] = ajax_command_replace('#ld_user_aadhar_3_div', drupal_render($form['profile_address_info']['user_aadhar_3']));
	
	$commands[] = ajax_command_replace('#ld_streetname_div', drupal_render($form['profile_address_info']['street_name']));
	$commands[] = ajax_command_replace('#ld_houseno_div', drupal_render($form['profile_address_info']['house_no']));
	$commands[] = ajax_command_replace('#ld_policestation_div', drupal_render($form['profile_address_info']['police_station']));
	
	$commands[] = ajax_command_replace('#ld_user_passport_div', drupal_render($form['profile_address_info']['user_passport']));
	$commands[] = ajax_command_replace('#ld_doi_div', drupal_render($form['profile_address_info']['passport_date_of_issue']));
	$commands[] = ajax_command_replace('#ld_doe_div', drupal_render($form['profile_address_info']['passport_date_of_expiry']));
	
	return array('#type' => 'ajax', '#commands' => $commands);
}
function get_ajax_load_ownership($form, $form_state){
	
	$commands = array();
	$commands[] = ajax_command_replace('#ownership_type_id', drupal_render($form['profile_other_info']['ownership_type']));
	$commands[] = ajax_command_replace('#occupier_type_id', drupal_render($form['profile_other_info']['occupier_type']));

	//$commands[] = ajax_command_replace('#otherdetails_ow_div', drupal_render($form['profile_other_info']['otherdetails_ow']));
	//$commands[] = ajax_command_replace('#otherdetails_oc_div', drupal_render($form['profile_other_info']['otherdetails_oc']));
	//$commands[] = ajax_command_replace('#otherdetails_cn_div', drupal_render($form['profile_other_info']['otherdetails_cn']));
	
	$commands[] = ajax_command_replace('#is_occupier_id', drupal_render($form['profile_other_info']['is_occupier']));
	
	$commands[] = ajax_command_replace('#occupier_first_name_c_id', drupal_render($form['profile_other_info']['occupier_first_name_c']));
	$commands[] = ajax_command_replace('#occupier_middle_name_c_id', drupal_render($form['profile_other_info']['occupier_middle_name_c']));
	$commands[] = ajax_command_replace('#occupier_last_name_c_id', drupal_render($form['profile_other_info']['occupier_last_name_c']));
	$commands[] = ajax_command_replace('#occupier_email_c_id', drupal_render($form['profile_other_info']['occupier_email_c']));
	$commands[] = ajax_command_replace('#occupier_mobile_c_id', drupal_render($form['profile_other_info']['occupier_mobile_c']));
	
	$commands[] = ajax_command_replace('#occupier_first_name_y_id', drupal_render($form['profile_other_info']['occupier_first_name_y']));
	$commands[] = ajax_command_replace('#occupier_middle_name_y_id', drupal_render($form['profile_other_info']['occupier_middle_name_y']));
	$commands[] = ajax_command_replace('#occupier_last_name_y_id', drupal_render($form['profile_other_info']['occupier_last_name_y']));
	$commands[] = ajax_command_replace('#occupier_email_y_id', drupal_render($form['profile_other_info']['occupier_email_y']));
	$commands[] = ajax_command_replace('#occupier_mobile_y_id', drupal_render($form['profile_other_info']['occupier_mobile_y']));

	$commands[] = ajax_command_replace('#occupier_first_name_n_id', drupal_render($form['profile_other_info']['occupier_first_name_n']));
	$commands[] = ajax_command_replace('#occupier_middle_name_n_id', drupal_render($form['profile_other_info']['occupier_middle_name_n']));
	$commands[] = ajax_command_replace('#occupier_last_name_n_id', drupal_render($form['profile_other_info']['occupier_last_name_n']));
	$commands[] = ajax_command_replace('#occupier_email_n_id', drupal_render($form['profile_other_info']['occupier_email_n']));
	$commands[] = ajax_command_replace('#occupier_mobile_n_id', drupal_render($form['profile_other_info']['occupier_mobile_n']));
	
	return array('#type' => 'ajax','#commands' => $commands);
}

function find_existing_email($email){
	$details	=  db_query("SELECT id FROM fa_user_details WHERE email = '".$email."' OR occupier_email = '".$email."'")->rowCount();
	return $details;
}

function find_existing_mobile($mobile){
	$details	=  db_query("SELECT id FROM fa_user_details WHERE mobile = '".$mobile."' OR occupier_mobile = '".$mobile."'" )->rowCount();
	return $details;
}

?>