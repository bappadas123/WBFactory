<?php
//$applicationid
drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/sky-forms.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function details_worker_hp_yearly_new_registrtatoin($form, &$form_state, $serviceid, $factory_type_id,$applicationid,$linknumber,$flagmapp) {	
	global $base_root, $base_path, $user;
  
	$application_id = encryption_decryption_fun('decrypt', $applicationid);
	if(empty($application_id)){
		  	drupal_set_message(('At first you must be filled up the general information of factory then go to second tab'),'warning');
			drupal_goto('applicant/caf-reg/registrtatoin-license/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$linknumber.'/'.$flagmapp) ;
	 }else{
		 	$get_fa_cafa = get_fa_cafa($application_id);
		 	$reference_number 			= $get_fa_cafa['reference_number'];
			$value_factory_profile_type	= $get_fa_cafa['ownership_type'];
			//$date_of_amenability		= $get_fa_cafa['date_of_amenability'];
			$date_of_amenability		= '2008';
			function validateDate($date, $format = 'Y-m-d'){
				 $d = DateTime::createFromFormat($format, $date);
    			return $d && $d->format($format) == $date;
		   }
		   $r=validateDate($date_of_amenability, 'Y-m-d');
		   if($r==1){
			  		$previous_date= date("Y-d-m", strtotime("-12 months", strtotime($date_of_amenability)));
			}else{
				$previous_date = $date_of_amenability -1;
			}
   

			
			
	 }
	 
	  
	
	$service_id 	= encryption_decryption_fun('decrypt',$serviceid);
	$factory_typeid = encryption_decryption_fun('decrypt',$factory_type_id);
	//////////////////////////////occupier Type////////////////////////
	
	
	//////////////////////////////end occupier Type////////////////////////
	
	$worker_men =$worker_women = $worker_adolescents_men = $worker_adolescents_women = $worker_children_male = $worker_children_women = '';
	
    $form = array();
	$form['serviceid'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> $serviceid,
		);
	$form['factorytypeid'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $factory_type_id
			 
		);
	$form['application_reference_no'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> encryption_decryption_fun('encrypt', $reference_number)
			 
	);
	$form['applicationid'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $applicationid
	);	
	
	
	
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	$form['header'] = array(
			'#markup' 	=> t('<div class="content"><div class="sky-form"><h3><b> Horse power / workers and manager details</b></h3>'),
		);
	
	
	
		
	$form['nature_work'] = array(
			'#type' 		=> 'fieldset',
			'#title' 		=> t('Nature of Manufacturing process'),
			'#collapsible' 	=> TRUE, 
			'#collapsed' 	=> FALSE, 
	);
	$form['nature_work']['date_befor_twelve_month'] 	= array(
  				'#prefix' 	 => '<div class="row"><div class="col-md-6 col-xs-12"><label class="input">Date of preceding Twelve months<span id=\'star\'>*</span>',
  				'#suffix' 	 => '</label></div>',
  				'#type' 	 => 'textfield',
				'#default_value'=> $previous_date
  				
  
			);
	$form['nature_work']['carried_on_factory'] 	= array(
  				'#prefix' 	 	=> '<div class="col-md-6 col-xs-12"><label class="input">Carried on in the factory during the preceding Twelve months',
  				'#suffix' 	 	=> '</label></div></div>',
  				'#type' 	 	=> 'textfield',
				'#description' 	=> '<font color="#FF0000"><strong>N.B.:-If the factory was then in existence</strong></font>'
  				
  
			);
	  
	if($factory_typeid == 1 ||$factory_typeid == 2){
		 $form['nature_work']['nature_year'] 	= array(
  				'#prefix' 	  => '<div class="row"><div class="col-md-6 col-xs-12"><label class="select">Year<span id=\'star\'>*</span>',
  				'#suffix' 	  => '</label></div>',
  				'#type' 	  => 'select',
  				'#options' 	  =>  fetch_year($application_id,$service_id,$factory_typeid,$reference_number),
  
		);
		$form['nature_work']['nature_manufacturing'] 	= array(
				  '#prefix' 	 	=> '<div class="col-md-6 col-xs-12"><label class="input">Carried on the factory<span id=\'star\'>*</span>',
				  '#suffix' 	 	=> '</label></div>',
				   '#type' 	 		=> 'textfield',
			
			); 
	}
	 if($factory_typeid == 3){
	 }
	$form['nature_work']['add_more_nature'] 	= array(
		  '#type' 		=> 'submit',
		  '#submit'		=> array(),
		  '#ajax' 		=> array(
								'callback' => 'ajax_add_nature',
							),
			
		'#value' 		=> t('Add Manufacturing process'),
		'#attributes'   => array('class'=>array('btn btn-info')),
		'#prefix' 		=> '<div class="col-md-6 col-xs-12">',
		'#suffix' 		=> '</div></div>'
	);
	 
	$form['nature_work']['view_nature'] = array(
			 '#prefix' 		=> '<div class="row"><div id="view_nature_details_id"><div class="col-md-12 col-xs-12">',
			 '#type'		=> 'markup',
			 '#markup'		=>view_manufacturing_process_details($application_id,$service_id,$factory_typeid),
			 '#suffix' 		=> '</div></div></div>'
	);
	 
	$form['nature_work']['view_nature_error'] = array(
			 '#prefix' 		=> '<div class="row"><div id="view_nature_error_id"><div class="col-md-12 col-xs-12">',
			 '#type'		=> 'markup',
			 '#suffix' 		=> '</div></div></div>'
	);
	 
	$form['manager_details'] = array(
		'#type' => 'fieldset',
		'#title' => t('Details of manager & Permanent Address '),
		'#collapsible' => TRUE, // Added
		'#collapsed' => FALSE,  // Added
  		);	
		 $form['manager_details']['manager_year'] 	= array(
  				'#prefix' 	 => '<div class="row"><div class="col-md-4 col-xs-12"><label class="select">Year<span id=\'star\'>*</span>',
  				'#suffix' 	 => '</label></div>',
  				'#type' 	 => 'select',
  				'#options' 	 =>  fetch_year($application_id,$service_id,$factory_typeid,$reference_number),
  
			);
		
			
		$form['manager_details']['name_manager'] 	= array(
			  '#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">Name of manager<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div>',			 
			  '#type' 				=> 'textfield', 
	  	);
		$form['manager_details']['age_manager'] 	= array(
			  '#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">Age<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div>',
			 
			  '#type' 				=> 'textfield',
	  	);
		$form['manager_details']['father_husband_type_manager'] 	= array(
			  '#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="select">Relationship<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div>',
			 
			  '#type' 				=> 'select',
			  '#options' 			=> array(''=>'Select','1'=>'D/O','2'=>'S/0',3=>'W/O'), 
	  	);
		$form['manager_details']['father_husband_name_manager'] 	= array(
			  '#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">Father/Husband Name<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div>',
			 
			  '#type' 				=> 'textfield',
			   
	  	);
	
		
		
		$form['manager_details']['manager_residential_pincode'] 	= array(
		  '#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">Pincode<span id=\'star\'>*</span>',
		  '#suffix' 			=> '</label></div>',
		 
		  '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'Pincode'),
		  '#autocomplete_path' 	=> 'pinautocomplete',
		  '#id'					=>  'pincode_res_manager_residential_autocomplete',
		  '#maxlength' 			=> 6, 
		  '#type' 				=> 'textfield',
		  
		  '#ajax'				=> array(
											'effect' 		=> 'fade',			
											'callback'		=> 'get_manager_residential_ajax_load',
											'progress'		=>	array(
											'type'			=>'throbber',
											'message'		=>t('loading'),
											),
										)
	);
	$form['manager_details']['manager_residential_state'] 	= array(
			  '#prefix' 			=> '<div id = "manager_residential_state_replace"><div class="col-md-4 col-xs-12"><label class="select">State<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div></div>',
			  
			  '#type' 				=> 'select',
			   '#options' 			=> array(''=>t('Select State')),
			  '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
			 
			
	);
	$form['manager_details']['manager_residential_district'] 	= array(
		  '#prefix' 			=> '<div id = "manager_residential_dis_replace"><div class="col-md-4 col-xs-12"><label class="select">District<span id=\'star\'>*</span>',
		  '#suffix' 			=> '</label></div></div>',
		 
		  '#type' 				=> 'select',
		   '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'District', 'readonly' => 'readonly'),
		   '#options' 			=> array(''=>t('Select District')),
			
	);
	$form['manager_details']['manager_residential_sub_division'] 	= array(
		  '#prefix' 			=> '<div id = "manager_residential_sub_replace"><div class="col-md-4 col-xs-12"><label class="select">Sub-Division<span id=\'star\'>*</span>',
		  '#suffix' 			=> '</label></div></div>',
		
		  '#type' 				=> 'select',
		  '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
		  '#options' 			=> array(''=>t('Select Sub-Division')),
			
	);
	$form['manager_details']['manager_residential_area_type'] 	= array(
		  '#prefix' 			=> '<div id = "manager_residential_area_type_replace"><div class="col-md-4 col-xs-12"><label class="select">Area Type<span id=\'star\'>*</span>',
		  '#suffix' 			=> '</label></div></div>',
		 
		  '#type' 				=> 'select',
		   '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
			'#options' 			=> array(''=>t('Select Area Type')),
			
	);
	$form['manager_details']['manager_residential_area_details'] 	= array(
		  '#prefix' 			=> '<div id = "manager_residential_area_details_replace"><div class="col-md-4 col-xs-12"><label class="select">Block/Municipality/Corporation/SEZ/Notified<span id=\'star\'>*</span>',
		  '#suffix' 			=> '</label></div></div>',
		 
		  '#type' 				=> 'select',
		 '#attributes' 			=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
		 '#options' 			=> array(''=>t('Select Block/Municipality/Corporation/SEZ/Notified')),
		 
		  
	);
	$form['manager_details']['manager_residential_area_division'] 	= array(
		  '#prefix' 			=> '<div id = "manager_residential_area_division_replace"><div class="col-md-4 col-xs-12"><label class="select">Gram Panchayat/Ward/Sector/Notified Area<span id=\'star\'>*</span>',
		  '#suffix' 			=> '</label></div></div>',
		 
		  '#type' 				=> 'select', 
		   '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
		   '#options' 			=> array(''=>t('Select Gram Panchayat/Ward/Sector/Notified Area')),
			
	);
	$form['manager_details']['manager_residential_ps'] 	= array(
		  '#prefix' 			=> '<div id = "manager_residential_ps_replace"><div class="col-md-4 col-xs-12"><label class="select">Police Station<span id=\'star\'>*</span>',
		  '#suffix' 			=> '</label></div></div>',
		 
		  '#type' 				=> 'select',
		  '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
		  '#options' 			=> array(''=>t('Select Police Station')),
		  
	);
	$form['manager_details']['manager_residential_postoffice'] 	= array(
		  '#prefix' 			=> '<div id = "manager_residential_po_replace"><div class="col-md-4 col-xs-12"><label class="select">Post Office<span id=\'star\'>*</span>',
		  '#suffix' 			=> '</label></div></div>',
		  
		  '#type' 				=> 'select',
		  '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
		
		  
	);
	
	
	$value_manager_residential_pincode	= isset($form_state['values']['manager_residential_pincode'])? $form_state['values']['manager_residential_pincode'] : '';
	if(!empty($value_manager_residential_pincode)){
			 $get_all_data_with_pincode 	= 	get_all_data_with_pincode($value_manager_residential_pincode);
			 $state_res_code 				= 	$get_all_data_with_pincode['state_code'];
			 $dis_res_code 					= 	$get_all_data_with_pincode['district_code'];
			 $pin_id_po_res 				= 	$get_all_data_with_pincode['id'];
			 $is_state_exists 				= 	is_state_exists($state_res_code);
			 $is_po_exists 					= 	is_po_exists($value_manager_residential_pincode);
	
	
	if($is_state_exists>0){
		$form['manager_details']['manager_residential_state'] 	= array(
			  '#prefix' 			=> '<div id="manager_residential_state_replace"><div class="col-md-4 col-xs-12"><label class="select">State<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div></div>',
			   '#type' 				=> 'select',
			  '#options' 			=> get_all_statecode($state_res_code),
			  '#value'			   => !empty($state_res_code) ? $state_res_code	:'',
			  
				'#ajax'				=> array(
											'effect' 		=> 'fade',			
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
				  '#prefix' 			=> '<div id = "manager_residential_dis_replace"><div class="col-md-4 col-xs-12"><label class="select">District<span id=\'star\'>*</span>',
				  '#suffix' 			=> '</label></div></div>',
				  '#type' 				=> 'select',
				  '#options' 			=> get_all_districtcode_withstate($value_manager_residential_state_code,$dis_res_code),
				  '#value'			   => !empty($dis_res_code) ? $dis_res_code	:'',
	
				 
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
				  '#prefix' 			=> '<div id = "manager_residential_sub_replace"><div class="col-md-4 col-xs-12"><label class="select">Sub-Division<span id=\'star\'>*</span>',
				  '#suffix' 			=> '</label></div></div>',
				   '#type' 				=> 'select',
				  '#options' 			=> get_all_subdivcode_withdis($value_manager_residential_dis_code),
				
					'#ajax'				=> array(
													'effect' 		=> 'fade',			
													'callback'		=> 'get_manager_residential_ajax_load',
													'progress'		=>	array(
													'type'			=>'throbber',
													'message'		=>t('loading'),
													),
											)
			);
		$value_manager_residential_sub_code = isset($form_state['values']['manager_residential_sub_division'])? $form_state['values']['manager_residential_sub_division'] :'';
		 $is_areatype_exists = is_areatype_exists($value_manager_residential_dis_code, $value_manager_residential_sub_code);
		 if($is_areatype_exists>0){
			 $form['manager_details']['manager_residential_area_type'] 	= array(
					  '#prefix' 			=> '<div id = "manager_residential_area_type_replace"><div class="col-md-4 col-xs-12"><label class="select">Area Type<span id=\'star\'>*</span>',
					  '#suffix' 			=> '</label></div></div>',
					   '#type' 				=> 'select',
					  '#options' 			=> get_areatype_with_sub_dis($value_manager_residential_dis_code, $value_manager_residential_sub_code),
					   
					   '#ajax'				=> array(
													'effect' 		=> 'fade',			
													'callback'		=> 'get_manager_residential_ajax_load',
													'progress'		=>	array(
													'type'			=>'throbber',
													'message'		=>t('loading'),
													),
											)
					  
	);
				$value_manager_residential_area_type_code = isset($form_state['values']['manager_residential_area_type'])? $form_state['values']['manager_residential_area_type'] :'';
				if($value_manager_residential_area_type_code=='B'){
					$form['manager_details']['manager_residential_area_details'] 	= array(
						  '#prefix' 			=> '<div id = "manager_residential_area_details_replace"><div class="col-md-4 col-xs-12"><label class="select">Block<span id=\'star\'>*</span>',
						  '#suffix' 			=> '</label></div></div></div>',
						   '#type' 				=> 'select',
						  '#options' 			=> get_block_municipality_other($value_manager_residential_sub_code, $value_manager_residential_area_type_code),
						   
						'#ajax'				=> array(
													'effect' 		=> 'fade',			
													'callback'		=> 'get_manager_residential_ajax_load',
													'progress'		=>	array(
													'type'			=>'throbber',
													'message'		=>t('loading'),
													),
											)
					);
				}if($value_manager_residential_area_type_code=='C'){
					$form['manager_details']['manager_residential_area_details'] 	= array(
						  '#prefix' 			=> '<div id = "manager_residential_area_details_replace"><div class="col-md-4 col-xs-12"><label class="select">Corporation<span id=\'star\'>*</span>',
						  '#suffix' 			=> '</label></div></div>',
						   '#type' 				=> 'select',
						  '#options' 			=> get_block_municipality_other($value_manager_residential_sub_code, $value_manager_residential_area_type_code),
						  	'#ajax'=> array(
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
						  '#prefix' 			=> '<div id = "manager_residential_area_details_replace"><div class="col-md-4 col-xs-12"><label class="select">Municipality<span id=\'star\'>*</span>',
						  '#suffix' 			=> '</label></div></div>',
						   '#type' 				=> 'select',
						  '#options' 			=> get_block_municipality_other($value_manager_residential_sub_code, $value_manager_residential_area_type_code),
						  	'#ajax'=> array(
													'effect' 		=> 'fade',			
													'callback'		=> 'get_manager_residential_ajax_load',
													'progress'		=>	array(
													'type'			=>'throbber',
													'message'		=>t('loading'),
													),
											)
					);
				}if($value_manager_residential_area_type_code=='S'){
					$form['manager_details']['manager_residential_area_details'] 	= array(
						  '#prefix' 			=> '<div id = "manager_residential_area_details_replace"><div class="col-md-4 col-xs-12"><label class="select">SEZ<span id=\'star\'>*</span>',
						  '#suffix' 			=> '</label></div></div>',
						 
						  '#type' 				=> 'select',
						  '#options' 			=> get_block_municipality_other($value_manager_residential_sub_code, $value_manager_residential_area_type_code),
						  '#ajax'=> array(
													'effect' 		=> 'fade',			
													'callback'		=> 'get_manager_residential_ajax_load',
													'progress'		=>	array(
													'type'			=>'throbber',
													'message'		=>t('loading'),
													),
											)
					);
				}if($value_manager_residential_area_type_code=='N'){
					$form['manager_details']['manager_residential_area_details'] 	= array(
						  '#prefix' 			=> '<div id = "manager_residential_area_details_replace"><div class="col-md-4 col-xs-12"><label class="select">Notified<span id=\'star\'>*</span>',
						  '#suffix' 			=> '</label></div></div>',
						  '#type' 				=> 'select',
						  '#options' 			=> get_block_municipality_other($value_manager_residential_sub_code, $value_manager_residential_area_type_code),
						   '#ajax'=> array(
													'effect' 		=> 'fade',			
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
									  '#prefix' 			=> '<div id = "manager_residential_area_division_replace"><div class="col-md-4 col-xs-12"><label class="select">Gram Panchayat<span id=\'star\'>*</span>',
									  '#suffix' 			=> '</label></div></div>',
									  
									  '#type' 				=> 'select', 
									  '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
										
	'#options'			=>  get_full_villward($value_manager_residential_area_details_code,'V'),
							);
					}if($value_manager_residential_area_type_code=='M'){
							$form['manager_details']['manager_residential_area_division'] 	= array(
									  '#prefix' 			=> '<div id = "manager_residential_area_division_replace"><div class="col-md-4 col-xs-12"><label class="select">Ward<span id=\'star\'>*</span>',

									  '#suffix' 			=> '</label></div></div>',
									
									  '#type' 				=> 'select', 
									  '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
										
	'#options'			=>  get_full_villward($value_manager_residential_area_details_code,'W'),
							);
					}if($value_manager_residential_area_type_code == 'C'){
							$form['manager_details']['manager_residential_area_division'] 	= array(
									  '#prefix' 			=> '<div id = "manager_residential_area_division_replace"><div class="col-md-4 col-xs-12"><label class="select">Ward<span id=\'star\'>*</span>',
									  '#suffix' 			=> '</label></div></div>',
									 
									  '#type' 				=> 'select', 
									  '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
										
	'#options'			=>  get_full_villward($value_manager_residential_area_details_code,'C'),
							);
					}if($value_manager_residential_area_type_code == 'S'){
							$form['manager_details']['manager_residential_area_division'] 	= array(
									  '#prefix' 			=> '<div id = "manager_residential_area_division_replace"><div class="col-md-4 col-xs-12"><label class="select">Sector<span id=\'star\'>*</span>',
									  '#suffix' 			=> '</label></div></div>',
									  
									  '#type' 				=> 'select', 
									  '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
										
	'#options'			=>  get_full_villward($value_manager_residential_area_details_code,$value_manager_residential_area_type_code),
							);
					}if($value_manager_residential_area_type_code == 'N'){
							$form['manager_details']['manager_residential_area_division'] 	= array(
									  '#prefix' 			=> '<div id = "manager_residential_area_division_replace"><div class="col-md-4 col-xs-12"><label class="select">Notified Area<span id=\'star\'>*</span>',
									  '#suffix' 			=> '</label></div></div>',
									  
									  '#type' 				=> 'select', 
									  '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
										
	'#options'			=>  get_full_villward($value_manager_residential_area_details_code,$value_manager_residential_area_type_code),
							);
					}
				}
				
			 }
		}else{$form['manager_details']['manager_residential_sub_division'] 	= array(
		  '#prefix' 			=> '<div id = "manager_residential_sub_replace">',
	


		  '#suffix' 			=> '</label></div>',
		  
	);
	$form['manager_details']['manager_residential_area_type'] 	= array(
		  '#prefix' 			=> '<div id = "manager_residential_area_type_replace">',
		  '#suffix' 			=> '</label></div>',
		
	);
	$form['manager_details']['manager_residential_area_details'] 	= array(
		  '#prefix' 			=> '<div id = "manager_residential_area_details_replace">',
		  '#suffix' 			=> '</label></div>'
	);
	$form['manager_details']['manager_residential_area_division'] 	= array(
		  '#prefix' 			=> '<div id = "manager_residential_area_division_replace">',
		  '#suffix' 			=> '</label></div>'
	);
	
		}
		$is_ps_exists = 	is_ps_exists($value_manager_residential_dis_code);
		if($is_ps_exists>0){
			$form['manager_details']['manager_residential_ps'] 	= array(
				  '#prefix' 			=> '<div id = "manager_residential_ps_replace"><div class="col-md-4 col-xs-12"><label class="select">Police station<span id=\'star\'>*</span>',
				  '#suffix' 			=> '</label></div></div>',
				 
				  '#type' 				=> 'select',
				  '#options'			=> get_all_ps($value_manager_residential_dis_code),
				
	);
		}else{
			$form['manager_details']['manager_residential_ps'] 	= array(
				  '#prefix' 			=> '<div id = "manager_residential_ps_replace">',
				  '#suffix' 			=> '</label></div>'
			);
		}
	
		
	}
		else{
				$form['manager_details']['manager_residential_district'] 	= array(
					'#prefix' 			=> '<div id = "manager_residential_dis_replace">',
					'#suffix' 			=> '</label></div>',
		
					);
				$form['manager_details']['manager_residential_sub_division'] 	= array(
				  '#prefix' 			=> '<div id = "manager_residential_sub_replace">',
				  '#suffix' 			=> '</label></div>',
				  
			);
			$form['manager_details']['manager_residential_area_type'] 	= array(
				  '#prefix' 			=> '<div id = "manager_residential_area_type_replace">',
				  '#suffix' 			=> '</label></div>',
				
			);
			$form['manager_details']['manager_residential_area_details'] 	= array(
				  '#prefix' 			=> '<div id = "manager_residential_area_details_replace">',
				  '#suffix' 			=> '</label></div>'
			);
			$form['manager_details']['manager_residential_area_division'] 	= array(
				  '#prefix' 			=> '<div id = "manager_residential_area_division_replace">',
				  '#suffix' 			=> '</label></div>'
			);
			$form['manager_details']['manager_residential_ps'] 	= array(
				  '#prefix' 			=> '<div id = "manager_residential_ps_replace">',
				  '#suffix' 			=> '</label></div>'
			);
	}
	}else{
	$form['manager_details']['manager_residential_state'] 	= array(
			  '#prefix' 			=> '<div id = "manager_residential_state_replace">',
			  '#suffix' 			=> '</label></div>',
			 
		);
		$form['manager_details']['manager_residential_district'] 	= array(
		  '#prefix' 			=> '<div id = "manager_residential_dis_replace">',
		  '#suffix' 			=> '</label></div>',
		
	);
	$form['manager_details']['manager_residential_sub_division'] 	= array(
		  '#prefix' 			=> '<div id = "manager_residential_sub_replace">',
		  '#suffix' 			=> '</label></div>',
	);
	$form['manager_details']['manager_residential_area_type'] 	= array(
		  '#prefix' 			=> '<div id = "manager_residential_area_type_replace">',
		  '#suffix' 			=> '</label></div>',
	);
	$form['manager_details']['manager_residential_area_details'] 	= array(
		  '#prefix' 			=> '<div id = "manager_residential_area_details_replace">',
		  '#suffix' 			=> '</label></div>'
	);
	$form['manager_details']['manager_residential_area_division'] 	= array(
		  '#prefix' 			=> '<div id = "manager_residential_area_division_replace">',
		  '#suffix' 			=> '</label></div>'
	);
	$form['manager_details']['manager_residential_ps'] 	= array(
		  '#prefix' 			=> '<div id = "manager_residential_ps_replace">',
		  '#suffix' 			=> '</label></div>'
	);
	
	}
	if($is_po_exists>0){
		$form['manager_details']['manager_residential_postoffice'] 	= array(
			  '#prefix' 			=> '<div id = "manager_residential_po_replace"><div class="col-md-4 col-xs-12"><label class="select">Post office<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div></div>',
			
			  '#type' 				=> 'select',
			  '#options'			=> get_all_po($value_manager_residential_pincode),
			  
			  
	);
	}else{
		$form['manager_details']['manager_residential_postoffice'] 	= array(
			  '#prefix' 			=> '<div id = "manager_residential_po_replace"',
			  '#suffix' 			=> '</label></div>',
		);
	}
	}
	 $form['manager_details']['manager_residential_address'] 	= array(
			  '#prefix' 			=> '<div class="col-md-12 col-xs-12"><label class="textarea">Address Line 1<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div>',
			   '#rows'				=> 3,
			  '#type' 				=> 'textarea',
			  '#attributes' 		=> array('placeholder'=>'Residential Address Line'),
			
	  	);
		
	$form['manager_details']['manager_present_address'] 	= array(
			  '#prefix' 			=> '<div class="col-md-12 col-xs-12"><label class="textarea">Present Address Line<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div>',
			  '#rows'				=> 3,
			  '#type' 				=> 'textarea',
			  '#attributes' 		=> array('placeholder'=>'Present Address Line'),
			
	  	);
			/********** manager Details  - Start **********/
	
    $form['manager_details']['manager_telephone'] = array(
        '#prefix' => '<div class="col-md-3"><label class="input">',
        '#suffix' => '</label></div>',
        '#title' => t('Telephone No.'),
        '#type' => 'textfield',
        '#default_value' => ''
    );
	$form['manager_details']['manager_mobile'] = array(
		'#prefix' => '<div class="col-md-3"><label class="input">',
		'#suffix' => '</label></div>',
		'#title' => t('Mobile No.'),
		'#type' => 'textfield',
		'#default_value' => ''
    );
    $form['manager_details']['manager_fax'] = array(
        '#prefix' => '<div class="col-md-3"><label class="input">',
        '#suffix' => '</label></div>',
        '#title' => t('Fax No.'),
        '#type' => 'textfield',
        '#default_value' => ''
    );
    
	$form['manager_details']['manager_email'] = array(
		'#prefix' => '<div class="col-md-3"><label class="input">',
		'#suffix' => '</label></div></div>',
		'#title' => t('Email Id'),
		'#type' => 'textfield',
		'#default_value' => ''
    );
	
   
			
	$form['manager_details']['add_manager'] 			= array (
			'#type' 		=> 'submit',
			'#value' 		=> 'Add manager',
			'#prefix'		=> '<div class="row"><div class="col-md-12 col-xs-12">',
			'#suffix' 		=> '</div></div>',
			'#attributes'	=> array('class'=>array('btn btn-info')),
			//'#limit_validation_errors' 	=> array(),	
			'#ajax'			=> array('callback'=> 'add_manager_details'),
			);
			
	$form['manager_details']['manager_error'] = array(
		  
		   '#prefix' => '<div class="row"><div id="manager_error_replace_div"><div class="col-md-12 col-xs-12">',
		   '#suffix' => '</div></div></div>'	
		);
		
		$is_manager_exists =is_manager_exists();
		if($is_manager_exists>0){
			
			$form['manager_details']['view_manager'] = array(
				 '#prefix' 		=> '<div class="row"><div id="view_manager_details_id"><div class="col-md-12 col-xs-12">',
				 '#type'		=> 'markup',
				 '#markup'		=> view_manager_details(),
				 '#suffix' 		=> '</div></div></div>'
			);
			
		}else{
				$form['manager_details']['view_manager'] = array(
				 '#prefix' 		=> '<div class="row"><div id="view_manager_details_id"><div class="col-md-6 col-xs-12">',
				 '#type'		=> 'markup',
				
				 '#suffix' 		=> '</div</div></div>'
			);
		}	
		
		 /********** manager Details  - End **********/
	
		
	$form['director_details'] = array(
				'#type' => 'fieldset',
				'#title' => t('Details of Directors/Partners/Proprietor of the Factories '),
				'#collapsible' => TRUE, 
				'#collapsed' => FALSE,  
	);
	 $form['director_details']['director_year'] 	= array(
  				'#prefix' 	 => '<div class="row"><div class="col-md-4 col-xs-12"><label class="select">Year<span id=\'star\'>*</span>',
  				'#suffix' 	 => '</label></div>',
  				'#type' 	 => 'select',
  				'#options' 	 =>  fetch_year($application_id,$service_id,$factory_typeid,$reference_number),
  
			);
	////////////////////////////factory profile type////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	if($value_factory_profile_type == 'dir_firm' || $value_factory_profile_type == 'govt' || $value_factory_profile_type == 'psu')
	{
		$form['director_details']['type_data'] 	= array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="select">Type
			  						<span id=\'star\'>*</span>',
			'#suffix' 			=> '</label></div>',
			'#type' 			=> 'select',
			'#default_value'	=>'Directors',
			'#options' 			=> array('Director'=>'Directors'),
	  	); 
		if(!empty($value_factory_profile_type)){
		$form['director_details']['directors_din_no1'] 	= array(
			  '#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">
			  								DIN Number<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div>',
			  '#type' 				=> 'textfield', 
	  	);
		}
	}elseif($value_factory_profile_type == 'par_firm'){
		$form['director_details']['type_data'] 	= array(
			'#prefix' 			=> 'div class="col-md-4 col-xs-12"><label class="select">Type
			  							<span id=\'star\'>*</span>',
			'#suffix' 			=> '</label></div>',
			'#type' 			=> 'select',
			'#options' 			=> array('Partner'=>'Partners'),
			
	  	); 
		} elseif($value_factory_profile_type == 'pro_firm'){	
				$form['director_details']['type_data'] 	= array(
				'#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="select">Type
			  							<span id=\'star\'>*</span>',
			  	'#suffix' 			=> '</label></div>',
			  	'#type' 			=> 'select',
				'#options' 			=> array('Proprietor'=>'Proprietors'),
				
			);
		}
		elseif($value_factory_profile_type == 'others'){	
					$form['director_details']['type_data'] = array(
						'#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="select">',
						'#suffix' 			=> '</label></div>',
						'#title' 			=> t('Type'),
						'#options' 			=> array(''=>'Select','Director'=>'Directors','Partner'=>'Partners','Proprietor'=>'Proprietors'), 
						'#type' 			=> 'select',
						'#ajax' => array(
							'event' => 'change',
							'effect' => 'fade',
							'callback' => 'get_ajax_din',
							'progress' => array(
								'type' => 'throbber',
								'message' => t('loading')
							)
						)
					);
		}
	
    $form['director_details']['directors_din_no']     = array(
        '#prefix' => '<div id="ld_show_din">',
        '#suffix' => '</div>'
    );
	 $value_din   = isset($form_state['values']['type_data']) ? $form_state['values']['type_data'] : $type_data;
    if ($value_din == "Director") {
        $form['director_details']['directors_din_no']   = array(
            '#prefix' => '<div id="ld_show_din"><div class="col-md-4 col-xs-12"><label class="input">',
            '#suffix' => '</label></div></div>',
            '#title' => t('DIN Number'),
            '#type' => 'textfield',
            '#default_value' => '',
            '#required' => TRUE
        );
		}
///////////////////////////////////end ////////////////////////////
		
	$form['director_details']['name_directors'] 	= array(
			  '#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">
			  								Name of Directors/Partners/Proprietor<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div>',
			  '#type' 				=> 'textfield', 
			
	  	);
	$form['director_details']['age_directors'] 	= array(
			  '#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">Age<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div>',
			  '#type' 				=> 'textfield', 
			 
	  	);
	$form['director_details']['father_husband_type_directors'] 	= array(
			  '#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="select">Relationship<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div>',
			  '#type' 				=> 'select',
			  '#options' 			=> array(''=>'Select','1'=>'D/O','2'=>'S/0',3=>'W/O'), 
			 
	  	);
	$form['director_details']['father_husband_name_directors'] 	= array(
			  '#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">Father/Husband Name<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div></div>',
			  '#type' 				=> 'textfield', 
			 
	  	);	
	
	$form['director_details']['director_residential_pincode'] 	= array(
			  '#prefix' 			=> '<div class = "row"><div class = "col-md-4 col-xs-12"><label class="input">Pincode<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div>',
			  '#autocomplete_path' 	=> 'pinautocomplete',
	  		  '#maxlength' 			=> 6, 
			  '#type' 				=> 'textfield',
			  '#ajax'				=> array(
												'effect' 		=> 'fade',			
												'callback'		=> 'get_director_ajax_load',
												'progress'		=>	array(
												'type'			=>'throbber',
												'message'		=>t('loading'),
												),
											)
							
	
			  
	  	);	
		$form['director_details']['director_residential_state'] 	= array(
				  '#prefix' 			=> '<div id = "director_state_replace"><div class="col-md-4 col-xs-12"><label class="select">State<span id=\'star\'>*</span>',
				  '#suffix' 			=> '</label></div></div>',
				  '#type' 				=> 'select',
				  '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
				  '#options' 			=> array(),
				
	  	);
		$form['director_details']['director_residential_district'] 	= array(
			  '#prefix' 			=> '<div id = "director_dis_replace"><div class="col-md-4 col-xs-12"><label class="select">District<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div></div>',
			  '#type' 				=> 'select',
			   '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'District', 'readonly' => 'readonly'),
			   '#options' 			=> array(),
				
	  	);
		$form['director_details']['director_residential_sub_division'] 	= array(
			  '#prefix' 			=> '<div id = "director_sub_replace"><div class="col-md-4 col-xs-12"><label class="select">Sub-Division<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div></div>',
			 '#type' 				=> 'select',
			  
			  '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
			  '#options' 			=> array(),
				
	  	);
		$form['director_details']['director_residential_area_type'] 	= array(
			  '#prefix' 			=> '<div id = "director_area_type_replace"><div class="col-md-4 col-xs-12"><label class="select">Area Type<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div></div>',
			
			  '#type' 				=> 'select',
			   '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
			    '#options' 			=> array(),
			    
	  	);
		$form['director_details']['director_residential_area_details'] 	= array(
			  '#prefix' 			=> '<div id = "director_area_details_replace"><div class="col-md-4 col-xs-12"><label class="select">Block/Municipality/Corporation/SEZ/Notified<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div></div>',
			  
			  '#type' 				=> 'select',
			 '#attributes' 			=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
			 '#options' 			=> array(),
			 
			  
	  	);
		$form['director_details']['director_residential_area_division'] 	= array(
			  '#prefix' 			=> '<div id = "director_area_division_replace"><div class="col-md-4 col-xs-12"><label class="select">Gram Panchayat/Ward/Sector/Notified Area<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div></div>',
			  
			  '#type' 				=> 'select', 
			   '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
			   '#options' 			=> array(),
				
	  	);
		$form['director_details']['director_residential_ps'] 	= array(
			  '#prefix' 			=> '<div id = "director_ps_replace"><div class="col-md-4 col-xs-12"><label class="select">Police station<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div></div>',
			   '#type' 				=> 'select',
			  '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
			  '#options' 			=> array(),
			  );
		$form['director_details']['director_residential_postoffice'] 	= array(
			  '#prefix' 			=> '<div id = "director_po_replace"><div class="col-md-4 col-xs-12"><label class="select">Post office<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div></div></div>',
			  '#type' 				=> 'select',
			  '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
			  '#options' 			=> array(),
			  
	  	);
		$value_director_residential_pincode	= isset($form_state['values']['director_residential_pincode'])? $form_state['values']['director_residential_pincode'] : '';
		if(!empty($value_director_residential_pincode)){
				 $get_all_data_with_pincode 	= 	get_all_data_with_pincode($value_director_residential_pincode);
				 $state_res_code 				= 	$get_all_data_with_pincode['state_code'];
				 $dis_res_code 					= 	$get_all_data_with_pincode['district_code'];
				 $pin_id_po_res 				= 	$get_all_data_with_pincode['id'];
				 $is_state_exists 				= 	is_state_exists($state_res_code);
				 $is_po_exists 					= 	is_po_exists($value_director_residential_pincode);

	
	if($is_state_exists>0){
			$form['director_details']['director_residential_state'] 	= array(
				  '#prefix' 			=> '<div id="director_state_replace"><div class="col-md-4 col-xs-12"><label class="select">State<span id=\'star\'>*</span>',
				  '#suffix' 			=> '</label></div></div>',
				 
				  '#type' 				=> 'select',
				  '#options' 			=> get_all_statecode($state_res_code),
				  '#value'			   => !empty($state_res_code) ? $state_res_code	:'',
				  
	  				'#ajax'				=> array(
												'effect' 		=> 'fade',			
												'callback'		=> 'get_director_ajax_load',
												'progress'		=>	array(
												'type'			=>'throbber',
												'message'		=>t('loading'),
												),
											)
			);
			$value_director_state_code = !isset($form_state['values']['director_residential_state'])? $form_state['values']['director_residential_state'] :$state_res_code;
			$is_dis_exists = is_dis_exists($value_director_state_code,$dis_res_code);
			
			
			if($is_dis_exists>0){
				$form['director_details']['director_residential_district'] 	= array(
					  '#prefix' 			=> '<div id = "director_dis_replace"><div class="col-md-4 col-xs-12"><label class="select">District<span id=\'star\'>*</span>',
					  '#suffix' 			=> '</label></div></div>',
					  '#type' 				=> 'select',
					  '#options' 			=> get_all_districtcode_withstate($value_director_state_code,$dis_res_code),
					  '#value'			   => !empty($dis_res_code) ? $dis_res_code	:'',

					
	  				'#ajax'				=> array(
												'effect' 		=> 'fade',			
												'callback'		=> 'get_director_ajax_load',
												'progress'		=>	array(
												'type'			=>'throbber',
												'message'		=>t('loading'),
												),
											)
		  		);
			$value_director_dis_code = !isset($form_state['values']['director_residential_district'])? $form_state['values']['director_residential_district'] :$dis_res_code;
			$is_sub_exists = 	is_sub_exists($value_director_dis_code);
			if($is_sub_exists>0){
				$form['director_details']['director_residential_sub_division'] 	= array(
					  '#prefix' 			=> '<div id = "director_sub_replace"><div class="col-md-4 col-xs-12"><label class="select">Sub-Division<span id=\'star\'>*</span>',
					  '#suffix' 			=> '</label></div></div>',
					  '#type' 				=> 'select',
					  '#options' 			=> get_all_subdivcode_withdis($value_director_dis_code),
					  
	  					'#ajax'				=> array(
														'effect' 		=> 'fade',			
														'callback'		=> 'get_director_ajax_load',
														'progress'		=>	array(
														'type'			=>'throbber',
														'message'		=>t('loading'),
														),
												)
				);
			$value_director_sub_code = isset($form_state['values']['director_residential_sub_division'])? $form_state['values']['director_residential_sub_division'] :'';
			 $is_areatype_exists = is_areatype_exists($value_director_dis_code, $value_director_sub_code);
			 if($is_areatype_exists>0){
				 $form['director_details']['director_residential_area_type'] 	= array(
						  '#prefix' 			=> '<div id = "director_area_type_replace"><div class="col-md-4 col-xs-12"><label class="select">Area Type<span id=\'star\'>*</span>',
						  '#suffix' 			=> '</label></div></div>',
						 
						  '#type' 				=> 'select',
						  '#options' 			=> get_areatype_with_sub_dis($value_director_dis_code, $value_director_sub_code),
						  
						   '#ajax'				=> array(
														'effect' 		=> 'fade',			
														'callback'		=> 'get_director_ajax_load',
														'progress'		=>	array(
														'type'			=>'throbber',
														'message'		=>t('loading'),
														),
												)
						  
	  	);
					$value_director_area_type_code = isset($form_state['values']['director_residential_area_type'])? $form_state['values']['director_residential_area_type'] :'';
					if($value_director_area_type_code=='B'){
						$form['director_details']['director_residential_area_details'] 	= array(
							  '#prefix' 			=> '<div id = "director_area_details_replace"><div class="col-md-4 col-xs-12"><label class="select">Block<span id=\'star\'>*</span>',
							  '#suffix' 			=> '</label></div></div></div>',
							   '#type' 				=> 'select',
							  '#options' 			=> get_block_municipality_other($value_director_sub_code, $value_director_area_type_code),
							  
	  						'#ajax'				=> array(
														'effect' 		=> 'fade',			
														'callback'		=> 'get_director_ajax_load',
														'progress'		=>	array(
														'type'			=>'throbber',
														'message'		=>t('loading'),
														),
												)
						);
					}if($value_director_area_type_code=='C'){
						$form['director_details']['director_residential_area_details'] 	= array(
							  '#prefix' 			=> '<div id = "director_area_details_replace"><div class="col-md-4 col-xs-12"><label class="select">Corporation<span id=\'star\'>*</span>',
							  '#suffix' 			=> '</label></div></div>',
							  '#type' 				=> 'select',
							  '#options' 			=> get_block_municipality_other($value_director_sub_code, $value_director_area_type_code),
							  '#ajax'=> array(
														'effect' 		=> 'fade',			
														'callback'		=> 'get_director_ajax_load',
														'progress'		=>	array(
														'type'			=>'throbber',
														'message'		=>t('loading'),
														),
												)
						);
					}if($value_director_area_type_code=='M'){
						$form['director_details']['director_residential_area_details'] 	= array(
							  '#prefix' 			=> '<div id = "director_area_details_replace"><div class="col-md-4 col-xs-12"><label class="select">Municipality<span id=\'star\'>*</span>',
							  '#suffix' 			=> '</label></div></div>',
							 
							  '#type' 				=> 'select',
							  '#options' 			=> get_block_municipality_other($value_director_sub_code, $value_director_area_type_code),
							  '#ajax'=> array(
														'effect' 		=> 'fade',			
														'callback'		=> 'get_director_ajax_load',
														'progress'		=>	array(
														'type'			=>'throbber',
														'message'		=>t('loading'),
														),
												)
						);
					}if($value_director_area_type_code=='S'){
						$form['director_details']['director_residential_area_details'] 	= array(
							  '#prefix' 			=> '<div id = "director_area_details_replace"><div class="col-md-4 col-xs-12"><label class="select">SEZ<span id=\'star\'>*</span>',
							  '#suffix' 			=> '</label></div></div>',
							  
							  '#type' 				=> 'select',
							  '#options' 			=> get_block_municipality_other($value_director_sub_code, $value_director_area_type_code),
							 	'#ajax'=> array(
														'effect' 		=> 'fade',			
														'callback'		=> 'get_director_ajax_load',
														'progress'		=>	array(
														'type'			=>'throbber',
														'message'		=>t('loading'),
														),
												)
						);
					}if($value_director_area_type_code=='N'){
						$form['director_details']['director_residential_area_details'] 	= array(
							  '#prefix' 			=> '<div id = "director_area_details_replace"><div class="col-md-4 col-xs-12"><label class="select">Notified<span id=\'star\'>*</span>',
							  '#suffix' 			=> '</label></div></div>',
							  
							  '#type' 				=> 'select',
							  '#options' 			=> get_block_municipality_other($value_director_sub_code, $value_director_area_type_code),
							  '#ajax'=> array(
														'effect' 		=> 'fade',			
														'callback'		=> 'get_director_ajax_load',
														'progress'		=>	array(
														'type'			=>'throbber',
														'message'		=>t('loading'),
														),
												)
						);
					}
					
					$value_director_area_details_code = isset($form_state['values']['director_residential_area_details'])? $form_state['values']['director_residential_area_details'] :'';
					$is_block_mun_vill_exists = 1;
					if($is_block_mun_vill_exists>0){
						if($value_director_area_type_code == 'B'){
								$form['director_details']['director_residential_area_division'] 	= array(
										  '#prefix' 			=> '<div id = "director_area_division_replace"><div class="col-md-4 col-xs-12"><label class="select">Gram Panchayat<span id=\'star\'>*</span>',
										  '#suffix' 			=> '</label></div></div>',
										 '#type' 				=> 'select', 
										  '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
										   
	  '#options'			=>  get_full_villward($value_director_area_details_code,'V'),
								);
						}if($value_director_area_type_code=='M'){
								$form['director_details']['director_residential_area_division'] 	= array(
										  '#prefix' 			=> '<div id = "director_area_division_replace"><div class="col-md-4 col-xs-12"><label class="select">Ward<span id=\'star\'>*</span>',
										  '#suffix' 			=> '</label></div></div>',
										 
										  '#type' 				=> 'select', 
										  '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
										  
	  '#options'			=>  get_full_villward($value_director_area_details_code,'W'),
								);
						}if($value_director_area_type_code == 'C'){
								$form['director_details']['director_residential_area_division'] 	= array(
										  '#prefix' 			=> '<div id = "director_area_division_replace"><div class="col-md-4 col-xs-12"><label class="select">',
										  '#suffix' 			=> '</label></div></div>',
										  '#title'				=>	t('Ward'),
										  '#type' 				=> 'select', 
										  '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
										   
	  	'#options'			=>  get_full_villward($value_director_area_details_code,'C'),
								);
						}if($value_director_area_type_code == 'S'){
								$form['director_details']['director_residential_area_division'] 	= array(
										  '#prefix' 			=> '<div id = "director_area_division_replace"><div class="col-md-4 col-xs-12"><label class="select"Sector><span id=\'star\'>*</span>',
										  '#suffix' 			=> '</label></div></div>',
										 
										  '#type' 				=> 'select', 
										  '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
										   
	  	'#options'			=>  get_full_villward($value_director_area_details_code,$value_director_area_type_code),
								);
						}if($value_director_area_type_code == 'N'){
								$form['director_details']['director_residential_area_division'] 	= array(
										  '#prefix' 			=> '<div id = "director_area_division_replace"><div class="col-md-4 col-xs-12"><label class="select">Notified Area<span id=\'star\'>*</span>',
										  '#suffix' 			=> '</label></div></div>',
										 
										  '#type' 				=> 'select', 
										  '#attributes' 		=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),
										   
	  	'#options'			=>  get_full_villward($value_director_area_details_code,$value_director_area_type_code),
								);
						}
					}
					
				 }
			}else{$form['director_details']['director_residential_sub_division'] 	= array(
			  '#prefix' 			=> '<div id = "director_sub_replace">',
			  '#suffix' 			=> '</label></div>',
			  
	  	);
		$form['director_details']['director_residential_area_type'] 	= array(
			  '#prefix' 			=> '<div id = "director_area_type_replace">',
			  '#suffix' 			=> '</label></div>',
			
	  	);
		$form['director_details']['director_residential_area_details'] 	= array(
			  '#prefix' 			=> '<div id = "director_area_details_replace">',
			  '#suffix' 			=> '</label></div>'
	  	);
		$form['director_details']['director_residential_area_division'] 	= array(
			  '#prefix' 			=> '<div id = "director_area_division_replace">',
			  '#suffix' 			=> '</label></div>'
	  	);
		
			}
			$is_ps_exists = 	is_ps_exists($value_director_dis_code);
			if($is_ps_exists>0){
				$form['director_details']['director_residential_ps'] 	= array(
					  '#prefix' 			=> '<div id = "director_ps_replace"><div class="col-md-4 col-xs-12"><label class="select">Police station<span id=\'star\'>*</span>',
					  '#suffix' 			=> '</label></div></div>',
					  '#title'				=>	t(''),
					  '#type' 				=> 'select',
					  '#options'			=> get_all_ps($value_director_dis_code),
					
	  	);
			}else{
				$form['director_details']['director_residential_ps'] 	= array(
					  '#prefix' 			=> '<div id = "director_ps_replace">',
					  '#suffix' 			=> '</label></div>'
				);
			}
		
			
		}
			else{
					$form['director_details']['director_residential_district'] 	= array(
			  			'#prefix' 			=> '<div id = "director_dis_replace">',
			  			'#suffix' 			=> '</label></div>',
			
	  					);
					$form['director_details']['director_residential_sub_division'] 	= array(
					  '#prefix' 			=> '<div id = "director_sub_replace">',
					  '#suffix' 			=> '</label></div>',
					  
				);
				$form['director_details']['director_residential_area_type'] 	= array(
					  '#prefix' 			=> '<div id = "director_area_type_replace">',
					  '#suffix' 			=> '</label></div>',
					
				);
				$form['director_details']['director_residential_area_details'] 	= array(
					  '#prefix' 			=> '<div id = "director_area_details_replace">',
					  '#suffix' 			=> '</label></div>'
				);
				$form['director_details']['director_residential_area_division'] 	= array(
					  '#prefix' 			=> '<div id = "director_area_division_replace">',
					  '#suffix' 			=> '</label></div>'
				);
				$form['director_details']['director_residential_ps'] 	= array(
					  '#prefix' 			=> '<div id = "director_ps_replace">',
					  '#suffix' 			=> '</label></div>'
				);
		}
	}else{
		$form['director_details']['director_residential_state'] 	= array(
				  '#prefix' 			=> '<div id = "director_state_replace">',
				  '#suffix' 			=> '</label></div>',
				 
	  		);
			$form['director_details']['director_residential_district'] 	= array(
			  '#prefix' 			=> '<div id = "director_dis_replace">',
			  '#suffix' 			=> '</label></div>',
			
	  	);
		$form['director_details']['director_residential_sub_division'] 	= array(
			  '#prefix' 			=> '<div id = "director_sub_replace">',
			  '#suffix' 			=> '</label></div>',
			  
	  	);
		$form['director_details']['director_residential_area_type'] 	= array(
			  '#prefix' 			=> '<div id = "director_area_type_replace">',
			  '#suffix' 			=> '</label></div>',
			
	  	);
		$form['director_details']['director_residential_area_details'] 	= array(
			  '#prefix' 			=> '<div id = "director_area_details_replace">',
			  '#suffix' 			=> '</label></div>'
	  	);
		$form['director_details']['director_residential_area_division'] 	= array(
			  '#prefix' 			=> '<div id = "director_area_division_replace">',
			  '#suffix' 			=> '</label></div>'
	  	);
		$form['director_details']['director_residential_ps'] 	= array(
			  '#prefix' 			=> '<div id = "director_ps_replace">',
			  '#suffix' 			=> '</label></div>'
	  	);
		
	}
	if($is_po_exists>0){
			$form['director_details']['director_residential_postoffice'] 	= array(
				  '#prefix' 			=> '<div id = "director_po_replace"><div class="col-md-4 col-xs-12"><label class="select">Post office<span id=\'star\'>*</span>',
				  '#suffix' 			=> '</label></div></div>',
				 
				  '#type' 				=> 'select',
				  '#options'			=> get_all_po($value_director_residential_pincode),
				  
				  
	  	);
		}else{
			$form['director_details']['director_residential_postoffice'] 	= array(
				  '#prefix' 			=> '<div id = "director_po_replace"',
				  '#suffix' 			=> '</label></div>',
			);
		}
	}
	 $form['director_details']['director_residential_address'] 	= array(
			  '#prefix' 			=> '<div class="row"><div class="col-md-12 col-xs-12"><label class="textarea">Address Line 1<span id=\'star\'>*</span>',
			  '#suffix' 			=> '</label></div></div>',
			
			   '#rows'				=> 3,
			  '#type' 				=> 'textarea',
			  '#attributes' 		=> array('placeholder'=>'Address Line1'),
			
	  	);
		
		$form['director_details']['director_error'] = array(
		  
		   '#prefix' => '<div class="row"><div id="director_error_replace_div"><div class="col-md-12 col-xs-12">',
		   '#suffix' => '</div></div></div>'	
		);	
		
	$form['director_details']['view_director_gen'] 			= array (
			'#type' 				=> 'submit',
			'#value' 				=> 'Add more',
			'#prefix'				=> '<div class="row"><div class="col-md-6 col-xs-12">',
			'#suffix' 				=> '</div></div>',
			'#attributes'			=> array('class'=>array('btn btn-info')),
			//'#limit_validation_errors' 	=> array(),	
			'#ajax'						=> array(
														
											'callback'			=> 'add_director_details',
											
											),
			);
			
		
		$is_director_exists =is_director_exists();
		if($is_director_exists>0){
			
			$form['director_details']['view_director'] = array(
				 '#prefix' 		=> '<div class="row"><div id="view_director_details_id"><div class="col-md-12 col-xs-12">',
				 '#type'		=> 'markup',
				 '#markup'		=>view_director_proipietor_details(),
				 '#suffix' 		=> '</div></div></div>'
			);
			
		}else{
				$form['director_details']['view_director'] = array(
				 '#prefix' 		=> '<div class="row"><div id="view_director_details_id"><div class="col-md-6 col-xs-12">',
				 '#type'		=> 'markup',
				
				 '#suffix' 		=> '</div</div></div>'
			);
		}
		if($factory_typeid == 1 || $factory_typeid == 3){
		
			$form['power_details'] = array(
					'#type' => 'fieldset',
					'#title' => t('Details of Power to be  installed'),
					'#collapsible' => TRUE, // Added
					'#collapsed' => FALSE,  // Added
					);
			$form['power_details']['power_year'] 	= array(
  				'#prefix' 	 => '<div class="row"><div class="col-md-6 col-xs-12"><label class="select">Year<span id=\'star\'>*</span>',
  				'#suffix' 	 => '</label></div>',
  				'#type' 	 => 'select',
  				'#options' 	 =>  fetch_year($application_id,$service_id,$factory_typeid,$reference_number),
  
			);
			$form['power_details']['power_type'] 	= array(
						  '#prefix' 	 => '<div class="col-md-6 col-xs-12"><label class="select">
						  					Unit of power installed or proposed to be installed',
						  '#suffix' 	 => '</label></div>',
						  '#type' 		 => 'select',
						  '#options'	 => array('HP'=>'HP','KW'=>'KW'),
						  
			 );		
			
			$form['power_details']['installed_power'] 	= array(
						  '#prefix' 	 => '<div class="col-md-6 col-xs-12"><label class="input">
						  					Nature and total amount of power installed or proposed to be installed',
						  '#suffix' 	 => '</label></div></div>',
						  '#type' 		 => 'textfield', 
						  '#description' => t('<font color="#FF0000">(N.B.:-Total rated H. P. In all cases except electricity generating station)</font>'),
					
						);
						
			$form['power_details']['add_power'] 			= array (
						'#type' 		=> 'submit',
						'#value' 		=> 'Add Power',
						'#prefix'		=> '<div class="row"><div class="col-md-6 col-xs-12">',
						'#suffix' 		=> '</div></div>',
						'#attributes'	=> array('class'=>array('btn btn-info')),
						'#ajax'			=> array(
													'callback'			=> 'ajax_add_power',
														
												),
			);
		  	$form['power_details']['power_error'] 			= array (
						'#type' 		=> 'markup',
						
						'#prefix'		=> '<div class="row"><div id ="power_error_id"><div class="col-md-6 col-xs-12">',
						'#suffix' 		=> '</div></div>',
						
			);
			$form['power_details']['view_power'] = array(
						 '#prefix' 		=> '<div class="row"><div id="view_power_id"><div class="col-md-12 col-xs-12">',
						 '#type'		=> 'markup',
						 '#markup'		=> view_power_details($application_id,$service_id,$factory_typeid),
						 '#suffix' 		=> '</div></div></div>'
			);
	 
					/*$form['nature_details']['installed_state_date_change'] 	= array(
						  '#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">In case of change in power installed state the date of change<span id=\'star\'>*</span>',
						  '#suffix' 			=> '</label></div>',
						 
						  '#type' 				=> 'textfield', 
						 
					
					
						);*/
				/* $form['nature_details']['total_capacity'] 	= array(
						  '#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input">Total generating capacity in KW<span id=\'star\'>*</span>',
						  '#suffix' 			=> '</label></div></div>',
						 
						  '#type' 				=> 'textfield', 
						 
						  '#description'		=> t('<font color="#FF0000">(N.B.:-In case of generating station)</font>'),
					
						);*/
		}	
	
	$form['yearly_worker'] = array(
			'#type' 		=> 'fieldset',
			'#title' 		=> t('Workers Details'),
			'#collapsible' 	=> TRUE, 
			'#collapsed' 	=> FALSE, 
	  );	


	$form['yearly_worker']['sub_header_11'] = array(
			'#markup' 	 => t('<h7><b>Permanent :—</b></h5>'),
		);
	 $form['yearly_worker']['worker_year'] 	= array(
  				'#prefix' 	 => '<div class="row"><div class="col-md-6 col-xs-12"><label class="select">Year<span id=\'star\'>*</span>',
  				'#suffix' 	 => '</label></div>',
  				'#type' 	 => 'select',
  				'#options' 	 =>  fetch_year($application_id,$service_id,$factory_typeid,$reference_number),
  
			);	
	$form['yearly_worker']['permanent_male'] 	= array(
			  '#prefix' 	 	=> '<div class="col-md-4 col-xs-12"><label class="input">Male<span id=\'star\'>*</span>',
			  '#suffix' 	 	=> '</label></div>',
			  '#default_value' 	=> $worker_adolescents_men,
			  '#type' 	 		=> 'textfield',
	
		);
	$form['yearly_worker']['permanent_female'] 	= array(
			  '#prefix' 	 => '<div class="col-md-4 col-xs-12"><label class="input">Female<span id=\'star\'>*</span>',
			  '#suffix' 	 => '</label></div>',
			  '#type' 		 => 'textfield',
			  '#default_value' => $worker_adolescents_women,
		);

	$form['yearly_worker']['permanent_transgender'] 	= array(
				'#prefix' 	 	=> '<div class="col-md-4 col-xs-12"><label class="input">Transgender/Third Gender<span id=\'star\'>*</span>',
				'#suffix' 	 	=> '</label></div></div>',
				'#type' 		=> 'textfield',
				'#default_value' => $worker_adolescents_transgender,

		);	
	$form['yearly_worker']['sub_header_12'] = array(
			'#markup' 	 => t('<h7><b>Contractual :—</b></h5>'),
		);	
	$form['yearly_worker']['contractual_male'] 	= array(
			  '#prefix' 	 	=> '<div class="row"><div class="col-md-4 col-xs-12"><label class="input">Male<span id=\'star\'>*</span>',
			  '#suffix' 	 	=> '</label></div>',
			  '#default_value'	=> $worker_children_male,
			  '#type' 	 		=> 'textfield',
		
		);
	$form['yearly_worker']['contractual_female'] 	= array(
			  '#prefix' 	 	=> '<div class="col-md-4 col-xs-12"><label class="input">Female<span id=\'star\'>*</span>',
			  '#suffix' 	 	=> '</label></div>',
			  '#type' 	 		=> 'textfield',
			  '#default_value' => $worker_children_women,
	 
		);	

	$form['yearly_worker']['contractual_transgender'] 	= array(
			  '#prefix' 	 => '<div class="col-md-4 col-xs-12"><label class="input">',
			  '#suffix' 	 => '</label></div></div>',
			  '#title'	 =>	t('Transgender/Third Gender'),
			  '#type' 	 => 'textfield',
			  '#default_value' => $worker_children_transgender,
	
	  
	
	);
	$form['yearly_worker']['worker_error'] = array(
		  
			   '#prefix' => '<div class="row"><div id="ajax_error_replace_div"><div class="col-md-12 col-xs-12">',
			   '#suffix' => '</div></div></div>'	
	);
	$form['yearly_worker']['add_more_btn'] 	= array(
			  '#type' 		=> 'submit',
			  '#submit'		=> array(),
			  '#ajax' 		=> array(
						'callback' => 'ajax_add_more_callback',
						
					),
				
			'#value' 		=> t('Add Workers'),
			'#attributes'	=> array('class'=>array('btn btn-info')),
			'#prefix' 		=> '<div class="row"><div class="col-md-4 col-xs-12">',
			'#suffix' 		=> '</div></div>'
	);
	$form['yearly_worker']['view_worker'] = array(
			   '#type' => 'markup',
			   '#title' => t('Yearly Worker Details'),
			  
			   '#prefix' => '<div class="row"><div id="replace_div_worker"><div class="col-md-12 col-xs-12">'.get_worker_details_data($application_id),
			   '#suffix' => '</div></div></div>'	
		);
		
			
	$form['maximum_workers'] = array(
			'#type' 		=> 'fieldset',
			'#title' 		=> t('Previous worker Details'),
			'#collapsible' 	=> TRUE, 
			'#collapsed' 	=> FALSE, 
	  );	
				
	$form['maximum_workers']['pervious_total_worker'] 	= array(
			  '#prefix' 		=> '<div class="row"><div class="col-md-12 col-xs-12"><label class="input">',
			  '#suffix' 		=> '</label></div></div>',
			  '#title'	 		=>	t('Maximum number of workers employed in the factory on any day during the previous twelve months'),
			  '#type'       	=> 'textfield',
			  '#description'	=>  '<font color="#FF0000"><strong></strong>N.B.:- Including staff, officers, contract labour, etc. </font>',
			  '#default_value' 	=> $worker_children_transgender,
	);
	$form['maximum_workers']['sub_header_15'] = array(
			'#markup' 	 => t('<h7><b>In case of change :—</b></h5>'),
		);
		$form['maximum_workers']['change_total_worker'] 	= array(
			  '#prefix' 		=> '<div class="row"><div class="col-md-6 col-xs-12"><label class="input">',
			  '#suffix' 		=> '</label></div>',
			  '#title'	 		=>	t('Change in number of workers'),
			  '#type'       	=> 'textfield',
			  '#description'	=>  '<font color="#FF0000"><strong></strong>N.B.:- Including staff, officers, contract labour, etc. </font>',
			  '#default_value' 	=> $worker_children_transgender,
	);
	$form['maximum_workers']['change_date'] 	= array(
			  '#prefix' 		=> '<div class="col-md-6 col-xs-12"><label class="input">',
			  '#suffix' 		=> '</label></div></div>',
			  '#title'	 		=>	t('State the date of change'),
			  '#type'       	=> 'textfield',
			  '#attributes' 		=> array('class'=>array('datepicker'),'title'=>'Enter Date of approval of plan.'),
			  '#description'	=>  '<font color="#FF0000"><strong></strong>N.B.:- Including staff, officers, contract labour, etc. </font>',
			  '#default_value' 	=> $worker_children_transgender,
	);	
	$form['director_factory_statring_info'] = array(
			'#type' 		=> 'fieldset',
			'#title' 		=> t('Tenure Factory'),
			'#collapsible' 	=> TRUE,
			'#collapsed'	=> FALSE, 
		);	
	
	/*$form['director_factory_statring_info']['reference_no_approval_arrangments1'] 	= array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-12"><label class="input">whether arrangments for approval of disposal of trade waste and effluents<span id=\'star\'>*</span>',
			'#suffix' 			=> '</label></div>',
			'#type' 			=> 'textfield',
			'#description'		=> t('<font color="#FF0000">(N.B.:-If any,made fo disposal of trade waste and effluents. )</font>'),
		);	*/
	$form['director_factory_statring_info']['markup_start'] = array(
	     	 '#prefix' =>'<div class="row">'	
			);
	$form['director_factory_statring_info']['factory_pollution_type'] 	= array(
				'#prefix' 			=> '<div id ="pollution_type_id"><div class="col-md-6 col-xs-12"><label class="select">Categories of wbpcb<span id=\'star\'>*</span>',
				'#suffix' 			=> '</label></div></div>',
				'#type' 			=> 'select',
				'#options' 			=>  get_category_wbpcb(),
				'#ajax'				=> array(
												'effect' 		=> 'fade',			
												'callback'		=> 'get_pollution_ajax_load',
												'progress'		=>	array(
												'type'			=>'throbber',
												'message'		=>t('loading'),
											),
										)
			);	
	$form['director_factory_statring_info']['reference_no_approval_arrangments'] = array(
				'#prefix' 			=> '<div id ="reference_no_approval_id"><div class="col-md-6 col-xs-12"><label class="input">',
				'#suffix' 			=> '</label></div></div>',
				'#type' 			=> 'textfield',
				'#title'			=> t('Reference number of approval of arrangments'),
				'#description'		=> t('<font color="#FF0000">(N.B.:-If any,made fo disposal of trade waste and effluents. )</font>'),
				
			);	
	$form['director_factory_statring_info']['date_approval_arrangments'] = array(
				'#prefix' 			=> '<div id ="reference_date_approval_id"><div class="col-md-6 col-xs-12"><label class="input">',
				'#suffix' 			=> '</label></div></div>',
				'#title'			=> t('Date of approval of arrangments'),
				'#type' 			=> 'textfield',
				'#attributes' 		=> array('class'=>array('datepicker'),'title'=>'Enter Date of approval of plan.'),
				'#description'		=> t('<font color="#FF0000">(N.B.:-If any,made fo disposal of trade waste and effluents. )</font>'),
			
			);
			
	$form['director_factory_statring_info']['upload_intimation'] 	 = array(
				'#prefix'			=> '<div id="edit-upload-intimation-ajax-wrapper">',
				'#suffix' 			=> '</div>',
			 );

	 $value_pollution_type  =   isset($form_state['values']['factory_pollution_type']) ? $form_state['values']['factory_pollution_type'] : '';
	
	 
	 if($value_pollution_type == '1' || $value_pollution_type == '2' || $value_pollution_type == '3'){
		$form['director_factory_statring_info']['reference_no_approval_arrangments'] = array(
				'#prefix' 			=> '<div id ="reference_no_approval_id"><div class="col-md-6 col-xs-12"><label class="input">Reference number of approval of arrangments<span id=\'star\'>*</span>',
				'#suffix' 			=> '</label></div></div>',
				'#type' 			=> 'textfield',
				'#description'		=> t('<font color="#FF0000">(N.B.:-If any,made fo disposal of trade waste and effluents. )</font>'),
			);	
		$form['director_factory_statring_info']['date_approval_arrangments'] = array(
				'#prefix' 			=> '<div id ="reference_date_approval_id"><div class="col-md-6 col-xs-12"><label class="input">Date of approval of arrangments<span id=\'star\'>*</span>',
				'#suffix' 			=> '</label></div></div>',
				'#type' 			=> 'textfield',
				'#description'		=> t('<font color="#FF0000">(N.B.:-If any,made fo disposal of trade waste and effluents. )</font>'),
			);
			$form['director_factory_statring_info']['upload_intimation'] 	 = array(
				'#prefix'			=> '<div id="edit-upload-intimation-ajax-wrapper">',
				'#suffix' 			=> '</div>',
			 );
	 } if($value_pollution_type == 4){
		 	$form['director_factory_statring_info']['reference_no_approval_arrangments'] = array(
					'#prefix' 			=> '<div id ="reference_no_approval_id">',
					'#suffix' 			=> '</div>',
				
			);
			$form['director_factory_statring_info']['date_approval_arrangments'] = array(
					'#prefix' 			=> '<div id ="reference_date_approval_id">',
					'#suffix' 			=> '</div>',
				
			);
			$form['director_factory_statring_info']['upload_intimation'] 	 = array(
					'#prefix'				=> '<div id="edit-upload-intimation-ajax-wrapper"><div class="col-md-6 col-xs-12">
												<section><label class="input input-file"><span id=\'star\'>*</span>',
					'#suffix' 				=> '</label></section></div></div>',
					'#type' 				=> 'managed_file',
					'#title'				=>	'Letter of intimation of wbpcb',
					'#upload_validators' 	=> array('file_validate_extensions' => array('pdf')),
					'#upload_location' 		=> 'public://upload/intemation_letter_wbpcb/',
					
					'#attributes' 			=> array('id' => '','autocomplete' => 'off','class'=>array(''),'file_validate_size' => array(50*1024*1024)),
				
				
										  
				  );	
	 }if($value_pollution_type == 5){
		 $form['director_factory_statring_info']['reference_no_approval_arrangments'] = array(
				'#prefix' 			=> '<div id ="reference_no_approval_id">',
				'#suffix' 			=> '</div>',
				
			);
		 $form['director_factory_statring_info']['date_approval_arrangments'] = array(
				'#prefix' 			=> '<div id ="reference_date_approval_id">',
				'#suffix' 			=> '</div>',
				
			);	
		$form['director_factory_statring_info']['upload_intimation'] 	 = array(
				'#prefix'			=> '<div id="edit-upload-intimation-ajax-wrapper">',
				'#suffix' 			=> '</div>',
			 );
		
	 }
	 $form['director_factory_statring_info']['markup_11'] = array(
	     	 '#prefix' =>''	,
			 '#suffix' => '</div>'
			 
	);	
	 $form['director_factory_statring_info']['markup_000'] = array(
	     	 '#prefix' =>'<div class="row">'	
	);
	/* $form['director_factory_statring_info']['factor_amenablity_date'] = array(
			 '#prefix' 			=> 	'<div id="factor_amenablity_date_id"><div class="col-md-6 col-xs-12"><label class="input">Date from which the primises is occupied or been taken into use as factory<span id=\'star\'>*</span>',
			  '#suffix' 		=> 	'</label></div></div>',
			  //'#id'				=> 	'datepicker',
			  '#type' 			=> 	'textfield',
			  '#attributes' 	=> 	array('class' => array('datepicker'),'placeholder' => '','readonly' => 'readonly'),
		);
	$form['director_factory_statring_info']['how_many_year'] 	= array(
			  '#prefix' 		=> '<div id="how_many_year_id"><div class="col-md-6 col-xs-12"><label class="input">State the period of license required<span id=\'star\'>*</span>',
			  '#suffix' 		=> '</label></div></div>',
			  '#type' 			=> 'textfield', 
			  '#description'	=> t('<font color="#FF0000">(N.B.:-Maximun 15 years)</font>'),
	  );
	 $form['director_factory_statring_info']['service_year'] 	= array(
			  '#prefix' 		=> '<div id="service_year_id"><div class="col-md-4 col-xs-12"><label class="select">Year<span id=\'star\'>*</span>',
			  '#suffix' 		=> '</label></div></div>',
			  '#type' 			=> 'select',
			  '#options' 		=> array(),
			  
    	);

	$form['director_factory_statring_info']['check_year'] 		= 	array(	   
			'#prefix' 		=> 	'<div id="check_year_div_id">',
			'#suffix' 		=> 	'</div>',
																
	   	);
	 $get_year_id	= get_year_id($application_id,$service_id,$factory_typeid,$reference_number);	
	 if(empty($get_year_id)){
		 $form['director_factory_statring_info']['check_year'] 		= 	array(	   
					'#prefix' 			=> 	'<div id ="check_year_div_id"><div class="col-md-6 col-xs-12">',
					'#suffix' 			=> 	'</div></div>',
					'#type' 			=> 	'button',
					'#default_value' 	=> 	'Check Year',
					'#attributes' 		=>  array('class'=>array('btn btn-info')),
					'#ajax' 			=> 	array(
												'callback' 	=> 'check_availability_submit',
												'wrapper' 	=> '',
												'method' 	=> 'html',
												'effect' 	=> 'fade'
											)
			);
		 $value_how_many_year           =   isset($form_state['values']['how_many_year']) ? $form_state['values']['how_many_year'] : '';
		 $value_factor_amenablity_date  =   isset($form_state['values']['factor_amenablity_date']) ? $form_state['values']['factor_amenablity_date'] : '';
	if($value_how_many_year!="" && $value_factor_amenablity_date != ""){
			$form['director_factory_statring_info']['service_year'] 	= array(
					  '#prefix' 			=> '<div id="service_year_id"><div class="col-md-6 col-xs-12"><label class="select">Year<span id=\'star\'>*</span>',
					  '#suffix' 			=> '</label></div></div>',
					   '#type' 				=> 'select',
					  
					  '#options' 			=> create_validate_year($value_factor_amenablity_date,$value_how_many_year),
					  );
		}
	 }else{
		 $form['director_factory_statring_info']['check_year'] 	= array (
		 	'#prefix' 			=> 	'<div id ="check_year_div_id"><div class="col-md-6 col-xs-12">',
			'#suffix' 			=> 	'</div></div>',
			'#type' 			=>  'submit',
			'#default_value' 	=> 	'Reset Year',
			'#attributes'		=>   array('class'=>array('btn btn-info')),
			'#ajax'				=>   array(
											'callback'	=> 'reset_year',
											'wrapper' 	=> '',
											'method' 	=> 'html',
											'effect' 	=> 'fade'
											
										),
			);
			$form['director_factory_statring_info']['service_year'] 	= array(
				  '#prefix' 			=> '<div id="service_year_id"><div class="col-md-6 col-xs-12"><label class="select">Year'.$value_button.'<span id=\'star\'>*</span>',
				  '#suffix' 			=> '</label></div></div>',
				   '#type' 				=> 'select',
				  
				  '#options' 			=> array(),
					  );
		 
	 }
	 $value_button 			= 	isset($form_state['values']['check_year']) ? $form_state['values']['check_year'] : '';
	 if($value_button == "Check Year"){
		 $form['director_factory_statring_info']['check_year'] 	= array (
		 	'#prefix' 			=> 	'<div id ="check_year_div_id"><div class="col-md-6 col-xs-12">',
			'#suffix' 			=> 	'</div></div>',
			'#type' 			=>  'submit',
			'#default_value' 	=> 	'Reset Year',
			'#attributes'		=>   array('class'=>array('btn btn-info')),
			'#ajax'				=>   array(
											'callback'	=> 'reset_year',
											'wrapper' 	=> '',
											'method' 	=> 'html',
											'effect' 	=> 'fade'
											
										),
			);
	 }if($value_button == "Reset Year"){
		 $form['director_factory_statring_info']['check_year'] 		= 	array(	   
					'#prefix' 			=> 	'<div id ="check_year_div_id"><div class="col-md-6 col-xs-12">',
					'#suffix' 			=> 	'</div></div>',
					'#type' 			=> 	'button',
					'#default_value' 	=> 	'check_year',
					'#attributes' 		=>  array('class'=>array('btn btn-info')),
					'#ajax' 			=> 	array(
												'callback' 	=> 'check_availability_submit',
												'wrapper' 	=> '',
												'method' 	=> 'html',
												'effect' 	=> 'fade'
											)
			);
			
	 }
	 $value_button 					= 	isset($form_state['values']['check_year']) ? $form_state['values']['check_year'] : ''; 
	
	 $form['director_factory_statring_info']['markup_7'] = array(
		     '#suffix' => '</div>'	
		);	
	$form['director_factory_statring_info']['year_error'] = array(
		  
		   '#prefix' => '<div class="row"><div id="year_error_div"><div class="col-md-12 col-xs-12">',
		   '#suffix' => '</div></div></div>'	
		);*/	
				$form['back_link']	 = array(
					
				'#markup' 		=> l(t('Back'),'applicant/decission/', array('html' => TRUE,'attributes'=> array('class'=>array('button ')))),
			);
					
		$form['submit'] = array (
		  '#prefix' => '</div></div><div align="right">',  
		  '#suffix' => '</div>',
		  '#type' => 'submit',
		  '#value' => 'Save & Continue'
	); 

            return $form; 
        
         }
		 
/*function check_availability_submit($form, &$form_state){
		global $user;
	  	$uid 							= $user->uid;
		$commands 						= array();
	 	$val   							= $form_state['values'];
	 	$amanabilty_date 				=  $val['factor_amenablity_date'];
	 	$application_period 			=  $val['how_many_year'];
	 	$calculate_year 				=  create_validate_year1($amanabilty_date,$application_period);
	 	$service_id						= encryption_decryption_fun('decrypt',$val['serviceid']);	
	 	$application_id					= encryption_decryption_fun('decrypt',$val['applicationid']);
	 	$reference_no					= encryption_decryption_fun('decrypt',$val['application_reference_no']);
	 	$factory_id						= encryption_decryption_fun('decrypt',$val['factorytypeid']);

		$commands[] = ajax_command_replace('#service_year_id', drupal_render($form['director_factory_statring_info']['service_year']));
	
	// $commands[] = ajax_command_replace('#how_many_year_id', drupal_render($form['director_factory_statring_info']['how_many_year']));
	  if(empty($val['factor_amenablity_date'])){
		 $commands[] = ajax_command_replace('#year_error_div', '<div id="year_error_div" style="color:#F00"><div class="col-md-12">Please select the date </div></div>');
		

	 }if(empty($val['how_many_year'])){
		 $commands[] = ajax_command_replace('#year_error_div', '<div id="year_error_div" style="color:#F00"><div class="col-md-12">State the period of license require</div></div>');
	
	
	 } if(!empty($val['factor_amenablity_date']) && !empty($val['how_many_year'])){
		 $year_calclation = array(
			'amanabilty_date' 				=> $amanabilty_date,
			'application_period' 			=> $application_period,
			'calculate_year'				=> $calculate_year,
			'service_id' 					=> $service_id,
			'application_id' 				=> $application_id,
			'reference_no' 					=> $reference_no,
			'factory_id'					=> $factory_id,
			'created_by'					=> $uid
			
		);
	$id = db_insert('fa_calculate_year')->fields($year_calclation)->execute();
	 }
	  $commands[] = ajax_command_replace('#year_div_id', drupal_render($form['director_factory_statring_info']['yearid']));
	  
	  	//$commands[] = ajax_command_replace('#year_div_id', '<div id="year_div_id"><div class="col-md-4 col-xs-12">'.get_year_id($application_id,$service_id,$factory_id,$reference_no).'</div></div>');
	
	 $commands[] = ajax_command_replace('#check_year_div_id', drupal_render($form['director_factory_statring_info']['check_year']));
  	return array('#type' => 'ajax', '#commands' => $commands);
}

function reset_year($form, &$form_state){
	 $val   							= $form_state['values'];
	 $service_id						= encryption_decryption_fun('decrypt',$val['serviceid']);	
	  $application_id					= encryption_decryption_fun('decrypt',$val['applicationid']);
	 $reference_no						= encryption_decryption_fun('decrypt',$val['application_reference_no']);
	 $factory_id						= encryption_decryption_fun('decrypt',$val['factorytypeid']);
	  db_delete('fa_calculate_year')->condition('application_id',$application_id)->condition('reference_no',$reference_no)->condition('factory_id',$factory_id)->condition('service_id',$service_id)->execute();
	  $commands[] = ajax_command_replace('#year_div_id', drupal_render($form['director_factory_statring_info']['yearid']));
	
	 $commands[] = ajax_command_replace('#check_year_div_id', drupal_render($form['director_factory_statring_info']['check_year']));
	 return array('#type' => 'ajax', '#commands' => $commands);
}*/
/*function get_ajax_load($form, $form_state){
	$commands 	= array();	
	 $val   							= $form_state['values'];
	
	 if(empty($val['factor_amenablity_date'])){
		 $commands[] = ajax_command_replace('#year_error_div', '<div id="year_error_div" style="color:#F00"><div class="col-md-12">Please select the date </div></div>');
		return array('#type' => 'ajax', '#commands' => $commands);

	 }
	 if(empty($val['how_many_year'])){
		 $commands[] = ajax_command_replace('#year_error_div', '<div id="year_error_div" style="color:#F00"><div class="col-md-12">State the period of license require</div></div>');
	
	return array('#type' => 'ajax', '#commands' => $commands);
	 }else{
		  $commands[] = ajax_command_replace('#year_error_div', '<div id="year_error_div" style="color:#F00"><div class="col-md-12"></div></div>');
	 $commands[] = ajax_command_replace('#service_year_id', drupal_render($form['director_factory_statring_info']['service_year']));
	return array('#type' => 'ajax', '#commands' => $commands);
	 }
	
		
		
}*/


//-------------Add worker-----------------------------
function ajax_add_more_callback($form, &$form_state){

	global $user;
	$val   										= $form_state['values'];
	$uid 										= $user->uid;
	
	$commands   								= array();
	$worker_permanent_male						= $val['permanent_male'];
	$worker_permanent_female					= $val['permanent_female'];
	$worker_permanent_transgender				= $val['permanent_transgender'];
	$worker_contractual_male					= $val['contractual_male'];
	$worker_contractual_female				    = $val['contractual_female'];
	$worker_contractual_transgender				= $val['contractual_transgender'];
	$service_id									= encryption_decryption_fun('decrypt',$val['serviceid']);
	$service_year								= $val['worker_year'];
	$factory_type								= encryption_decryption_fun('decrypt',$val['factorytypeid']);
	$application_id								= encryption_decryption_fun('decrypt',$val['applicationid']);
	
	$worker_total								= $worker_permanent_male+$worker_permanent_female+$worker_permanent_transgender+$worker_contractual_male+$worker_contractual_female+$worker_contractual_transgender;

	 $application_reference_no			= encryption_decryption_fun('decrypt',$val['application_reference_no']);
	//if(!empty($service_year)){
	if(!empty($service_year)){
		
		if((filter_var($worker_permanent_male, FILTER_VALIDATE_INT)== true) && (filter_var($worker_permanent_female, FILTER_VALIDATE_INT)== true) && (filter_var($worker_permanent_transgender, FILTER_VALIDATE_INT)== true) && (filter_var($worker_contractual_male, FILTER_VALIDATE_INT)==true) && (filter_var($worker_contractual_female, FILTER_VALIDATE_INT)== true) &&  (filter_var($worker_contractual_transgender, FILTER_VALIDATE_INT)== true)){
	$is_worker = is_worker($application_id,$service_id,$factory_type,$service_year);
			if($is_worker>0){
					$commands[] = ajax_command_replace('#ajax_error_replace_div', '<div id="ajax_error_replace_div" style="color:#F00"><div class="col-md-12"> In '.$service_year.' Workers Details is already exists</div></div>');
					}else{
						if(($factory_type == 1 && $worker_total>9) ||($factory_type == 2 && $worker_total>19) || ($factory_type == 3 && $worker_total>10)){
			$worker_details_yearly = array(
				'worker_permanent_male' 				=> $worker_permanent_male,
				'worker_permanent_female' 				=> $worker_permanent_female,
				'worker_permanent_transgender'			=> $worker_permanent_transgender,
				'worker_contractual_male' 				=> $worker_contractual_male,
				'worker_contractual_transgender' 		=> $worker_contractual_transgender,
				'worker_contractual_female' 			=> $worker_contractual_female,
				'worker_total'							=> $worker_total,
				'service_year'							=> $service_year,
				'service_id'							=> $service_id,
				'factory_type'							=> $factory_type,
				'created_by'							=> $uid,
				'application_id'						=> $application_id,
				'worker_plan_approval_status'			=> 'In',
				'application_reference_no'				=> $application_reference_no
				);
		//print_r($worker_details_yearly);die();				
				$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
				if($id){
					$commands[] = ajax_command_replace('#replace_div_worker', drupal_render($form['yearly_worker']['view_worker']));
					$commands[] = ajax_command_replace('#replace_div_worker', '<div id="replace_div_worker"><div class="col-md-12">'.get_worker_details_data($application_id).'</div></div>');
					$commands[] = ajax_command_replace('#ajax_error_replace_div', drupal_render($form['yearly_worker']['worker_error']));
					$commands[] = ajax_command_replace('#ajax_error_replace_div', '<div id="ajax_error_replace_div" style="color:#F00"><div class="col-md-12"></div></div>');
					}
					
					return array('#type' => 'ajax', '#commands' => $commands);
					
					}else{
						if ($factory_type == 1){
							$factory_categories = "Your factory is 2m(i) type category. So workers shoud be more than 9 workres with aid of power ";
							
						}else if ($factory_type == 2){
							$factory_categories = "Your factory is 2m(iI) type category. So workers shoud be more than 19 workres";
							
						}else if ($factory_type == 3){
							$factory_categories = "Your factory is Section 85 type category. So workers shoud be more than 10 workres with or with out power";	
						}
					$commands[] = ajax_command_replace('#ajax_error_replace_div', '<div id="ajax_error_replace_div" style="color:#F00"><div class="col-md-12">'.$factory_categories.' </div></div>');
				}
			}
		}
		else{
			$commands[] = ajax_command_replace('#ajax_error_replace_div', '<div id="ajax_error_replace_div" style="color:#F00"><div class="col-md-12">All fields under workers details shoud be integer</div></div>');
			}
		}else{
			$commands[] = ajax_command_replace('#ajax_error_replace_div', '<div id="ajax_error_replace_div" style="color:#F00"><div class="col-md-12">Please select year</div></div>');
		}
	return array('#type' => 'ajax', '#commands' => $commands);	
}
//-----------------------ADD Nature-------------------------------
function ajax_add_nature($form, &$form_state){

	global $user;
	$val   	= $form_state['values'];
	$uid 	= $user->uid;
	
	$commands   				= array();
	$nature_manufacturing		= $val['nature_manufacturing'];
	$service_id					= encryption_decryption_fun('decrypt',$val['serviceid']);
	$service_year				= $val['nature_year'];
	$factory_type				= encryption_decryption_fun('decrypt',$val['factorytypeid']);
	$application_id				= encryption_decryption_fun('decrypt',$val['applicationid']);
	$application_reference_no	= encryption_decryption_fun('decrypt',$val['application_reference_no']);
	if(!empty($service_year)){
		$is_manufacturing = is_manufacturing($application_id,$service_id,$factory_type,$service_year);
		if($is_manufacturing>0){
			
			$commands[] = ajax_command_replace('#view_nature_error_id', '<div id="view_nature_error_id" style="color:#F00"><div class="col-md-12">In '.$service_year.' Manufacturing process carried on the factory is already exists</div></div>');
		}else{
			if(!empty($nature_manufacturing)){
			$manufacturing_details_yearly = array(
					'nature_manufacturing' 					=> $nature_manufacturing,
					'service_id'							=> $service_id,
					'factory_type'							=> $factory_type,
					'created_by'							=> $uid,
					'application_id'						=> $application_id,
					'application_reference_no'				=> $application_reference_no,
					'manufacturing_application_status'		=> 'In',
					'service_year'							=> $service_year
				);
							
					$id = db_insert('fa_nature_manufacturing')->fields($manufacturing_details_yearly)->execute();
					if($id){
						
						
						$commands[] = ajax_command_replace('#view_nature_details_id', '<div id="view_nature_details_id"><div class="col-md-12">'.view_manufacturing_process_details($application_id,$service_id,$factory_type).'</div></div>');
						$commands[] = ajax_command_replace('#view_nature_error_id', drupal_render($form['nature_work']['view_nature_error']));
						$commands[] = ajax_command_replace('#view_nature_error_id', '<div id="view_nature_error_id" style="color:#F00"><div class="col-md-12"></div></div>');
						
					}
		}else{
			$commands[] = ajax_command_replace('#view_nature_error_id', '<div id="view_nature_error_id" style="color:#F00"><div class="col-md-12">Carried on the factory should be required </div></div>');
		}
		}
		
		
	}
	
	
	else{
		$commands[] = ajax_command_replace('#view_nature_error_id', '<div id="view_nature_error_id" style="color:#F00"><div class="col-md-12">Please select year</div></div>');
	}
	
	return array('#type' => 'ajax', '#commands' => $commands);	
}
//--------------Add power----------------------
function ajax_add_power($form, &$form_state){

	global $user;
	$val   	= $form_state['values'];
	$uid 	= $user->uid;
	
	$commands   				= array();
	$power_type					= $val['power_type'];
	$installed_power			= $val['installed_power'];
	$service_id					= encryption_decryption_fun('decrypt',$val['serviceid']);
	$service_year				= $val['power_year'];
	$factory_type				= encryption_decryption_fun('decrypt',$val['factorytypeid']);
	$application_id				= encryption_decryption_fun('decrypt',$val['applicationid']);
	$application_reference_no	= encryption_decryption_fun('decrypt',$val['application_reference_no']);
	if($power_type == 'KW'){
		$installed_power_hp = $installed_power*1.34102;//(1Kw => 1.34102 Hp)
	}
	if($power_type == 'HP'){
		$installed_power_hp = $installed_power;
	}
	
	if(!empty($service_year)){
		$is_power = is_power($application_id,$service_id,$factory_type,$service_year);
		if($is_power>0){
			$commands[] = ajax_command_replace('#power_error_id', '<div id="power_error_id" style="color:#F00"><div class="col-md-12">In '.$service_year. ' Nature and total amount of power installed or proposed to be installed  is already exists</div></div>');
		}else{
			if(!empty($power_type)){
			if(!empty($installed_power)){
				$installed_power_yearly = array(
						'power_unit' 				=> $power_type,
						'installed_power'			=> $installed_power	,				
						'installed_power_hp'		=> $installed_power_hp,
						'service_id'				=> $service_id,
						'factory_type'				=> $factory_type,
						'created_by'				=> $uid,
						'application_id'			=> $application_id,
						'application_reference_no'	=> $application_reference_no,
						'power_application_status'	=> 'In',
						'service_year'				=> $service_year
					);
								
						$id = db_insert('fa_power_details')->fields($installed_power_yearly)->execute();
						if($id){
							
							
							$commands[] = ajax_command_replace('#view_power_id', '<div id="view_power_id"><div class="col-md-12">'.view_power_details($application_id,$service_id,$factory_type).'</div></div>');
							$commands[] = ajax_command_replace('#power_error_id', drupal_render($form['power_details']['power_error']));
							$commands[] = ajax_command_replace('#power_error_id', '<div id="ajax_error_replace_div" style="color:#F00"><div class="col-md-12"></div></div>');
							
						}
			}else{	
					$commands[] = ajax_command_replace('#power_error_id', '<div id="power_error_id" style="color:#F00"><div class="col-md-12">Nature and total amount of power installed or proposed to be installed should be required </div></div>');
			}
		}
			else{
			$commands[] = ajax_command_replace('#power_error_id', '<div id="power_error_id" style="color:#F00"><div class="col-md-12">Unit of power installed or proposed to be installed should be required </div></div>');
			}
		
	
		
		
	}
	
	
}else{
	$commands[] = ajax_command_replace('#power_error_id', '<div id="power_error_id" style="color:#F00"><div class="col-md-12">Please select year</div></div>');
}
return array('#type' => 'ajax', '#commands' => $commands);	
}
//-------------Add Director-------------------------------
function add_director_details($form, &$form_state){
	 global $user;
	 $uid 								= $user->uid;
	 $val   							= $form_state['values'];
	//print_r($val);die();
	 $type_data 						= $val['type_data'];
	 $name_directors					= $val['name_directors'];
	 $age_directors						= $val['age_directors'];
	 $father_husband_name_directors		= $val['father_husband_name_directors'];
	 $father_husband_type_directors		= $val['father_husband_type_directors'];
	 $pincode_director					= $val['director_residential_pincode'];
	 $state_director					= $val['director_residential_state'];
	 $district_director					= $val['director_residential_district'];
	 $sub_division_director				= $val['director_residential_sub_division'];
	 $area_type_director				= $val['director_residential_area_type'];
	 $block_mun_cor_sez_not_director	= $val['director_residential_area_details'];
	 $grm_ward_sector_not_director		= $val['director_residential_area_division'];
	 $police_station_director			= $val['director_residential_ps'];
	 $post_office_director				= $val['director_residential_postoffice'];
	 $adress_line1_director				= $val['director_residential_address'];
	 $director_service_id				= encryption_decryption_fun('decrypt',$val['serviceid']);	
	
	 $factory_type_id					= encryption_decryption_fun('decrypt',$val['factorytypeid']);
	 $add_year_director					= $val['director_year'];
	 $director_service_id				= encryption_decryption_fun('decrypt',$val['serviceid']);
	 $application_id					= encryption_decryption_fun('decrypt',$val['applicationid']);
	 $factory_type_id					= encryption_decryption_fun('decrypt',$val['factorytypeid']);
	 
	 $directors_din_no					= $val['directors_din_no'];
	 if(empty($directors_din_no)){
	 	$directors_din_no 				= $val['directors_din_no1'];
	 }
	 $application_reference_no			= encryption_decryption_fun('decrypt',$val['application_reference_no']);
	 
/////////////////////////////////check////////////////////////////////////////
////////////	 if(!empty($add_year_director)){
	
	 if(!empty($add_year_director)){
		 if((!empty($type_data)) && (!empty($name_directors)) && (!empty($age_directors)) && (!empty($father_husband_name_directors)) && (!empty($pincode_director)) && (!empty($state_director)) && (!empty($district_director)) && (!empty($sub_division_director))  && (!empty($sub_division_director) ) && (!empty($area_type_director) )&& (!empty($block_mun_cor_sez_not_director) )&& (!empty($grm_ward_sector_not_director) )&& (!empty($police_station_director) )&& (!empty($post_office_director) )&& (!empty($adress_line1_director) )&& (!empty($father_husband_type_directors) )){
			 
		if((filter_var($age_directors, FILTER_VALIDATE_INT)== true)){
			$director_propieter_details = array(
					'type_director'   					=> $type_data, 
					'name_director'   					=> $name_directors, 
					'age_director' 						=> $age_directors,
					'father_husband_name_director' 		=> $father_husband_name_directors,
					'relationship_director' 			=> $father_husband_type_directors,
					'pincode_director'					=> $pincode_director,
					'state_director'					=> $state_director,
					'district_director'					=> $district_director,
					'sub_division_director'				=> $sub_division_director,
					'area_type_director'				=> $area_type_director,
					'block_mun_cor_sez_not_director'	=> $block_mun_cor_sez_not_director,
					'grm_ward_sector_not_director'		=> $grm_ward_sector_not_director,
					'police_station_director'			=> $police_station_director,
					'post_office_director'				=> $post_office_director,
					'adress_line1_director'				=> $adress_line1_director,
					'created_by'						=> $uid,
					'application_director_id'			=> $application_id,
					'factory_type_id'					=> $factory_type_id,
					'add_year_director'					=> $add_year_director,
					'application_status'				=> 'In',
					'director_service_id'				=> $director_service_id,
					'application_reference_no'			=> $application_reference_no,
					'din_director'						=>  $directors_din_no
					
					
				);						
				
		$id =db_insert('fa_director_details')->fields($director_propieter_details)->execute();
		if($id){
					
				$commands[] = ajax_command_replace('#view_director_details_id', "<div id ='view_director_details_id'><div class='col-md-12 col-xs-12'>".view_director_proipietor_details().'</div></div>');
				$commands[] = ajax_command_replace('#director_error_replace_div', '<div id="director_error_replace_div" style="color:#F00"><div class="col-md-12">Directors/Partners/Proprietor of the factories has been saved successfully</div></div>');
				
		}
	}
	    else{
			$commands[] = ajax_command_replace('#director_error_replace_div', '<div id="director_error_replace_div" style="color:#F00"><div class="col-md-12">Age fields under Details of Directors/Partners/Proprietor of the Factories shoud be integer</div></div>');
		}
		 }
		 else{
			 $commands[] = ajax_command_replace('#director_error_replace_div', '<div id="director_error_replace_div" style="color:#F00"><div class="col-md-12">All fields under Details of Directors/Partners/Proprietor of the Factories  shoud be mandatory</div></div>');
			 
		 }
	 }else{
		 	
				$commands[] = ajax_command_replace('#director_error_replace_div', '<div id="director_error_replace_div" style="color:#F00"><div class="col-md-12">Please select year'.$add_year_director.'</div></div>');
	 }
	
	
			return array('#type' => 'ajax', '#commands' => $commands);	
}
//-------------Add Manager--------------------------------------
function add_manager_details($form, &$form_state){
	 	global $user;
		$uid 							= $user->uid;
	 	$val   							= $form_state['values'];
	//print_r($val);die();
	
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
	 $police_station_manager			= $val['manager_residential_ps'];
	 $post_office_manager				= $val['manager_residential_postoffice'];
	 $adress_line1_manager				= $val['director_residential_address'];
	 $manager_service_id				= encryption_decryption_fun('decrypt',$val['serviceid']);	
	 $application_id					= encryption_decryption_fun('decrypt',$val['applicationid']);
	
	 $factory_type_id					= encryption_decryption_fun('decrypt',$val['factorytypeid']);
	 $add_year_manager					= $val['manager_year'];
	
	 $application_reference_no			= encryption_decryption_fun('decrypt',$val['application_reference_no']);
	 $adress_line1_manager             	= $val['manager_residential_address'];
	 
	 $present_adress_manager            = $val['manager_present_address'];
	 $telephone_no_manager	            = $val['manager_telephone'];
	 $mobile_no_manager            		= $val['manager_mobile'];
	 $fax_no_manager	           		= $val['manager_fax'];
	 $email_id_manager            		= $val['manager_email'];
	 
	if(empty($add_year_manager)){
		 $commands[] = ajax_command_replace('#manager_error_replace_div', '<div id="manager_error_replace_div" style="color:#F00"><div class="col-md-12">Please select year'.$add_year_director.'</div></div>');
	 }else{
		  if((!empty($name_manager)) && (!empty($age_manager))&& (!empty($father_husband_name_manager)) && (!empty($father_husband_type_manager)) && (!empty($pincode_manager)) && (!empty($state_manager)) && (!empty($district_manager)) && (!empty($sub_division_manager))  && (!empty($area_type_manager) ) && (!empty($block_mun_cor_sez_not_manager) )&& (!empty($grm_ward_sector_not_manager) )&& (!empty($police_station_manager) )&& (!empty($post_office_manager) )&& (!empty($adress_line1_manager) ) && (!empty($present_adress_manager) ) &&(!empty($telephone_no_manager) ) &&  (!empty($fax_no_manager) ) && (!empty($email_id_manager) )){
			 if((filter_var($age_manager, FILTER_VALIDATE_INT)== true)){

$manager_details = array(
'name_manager'   	 => $name_manager, 
'type_manager' 	 => '',
'age_manager' 	 => $age_manager,
'father_husband_name_manager' 	 => $father_husband_name_manager,
'relationship_manager' 	 => $father_husband_type_manager,
'pincode_manager'	 => $pincode_manager,
'state_manager'	 => $state_manager,
'district_manager'	 => $district_manager,
'sub_division_manager'	 => $sub_division_manager,
'area_type_manager'	 => $area_type_manager,
'block_mun_cor_sez_not_manager'	 => $block_mun_cor_sez_not_manager,
'grm_ward_sector_not_manager'	 => $grm_ward_sector_not_manager,
'police_station_manager'	 => $police_station_manager,
'post_office_manager'	 => $post_office_manager,
'adress_line1_manager'	 => $adress_line1_manager,
'created_by'	 => $uid,
'application_manager_id'	 => $application_id,
'factory_type_id'	 => $factory_type_id,
'add_year_manager'	 => $add_year_manager,
'manager_service_id'	 => $manager_service_id,
'application_status'        	 => 'In',
'application_reference_no'          => $application_reference_no,
'worker_plan_approval_status'	 => '',

'manager_present_address'	 => $present_adress_manager,
'manager_telephone'	 => $telephone_no_manager,
'manager_phone'	 => $mobile_no_manager,
'manager_fax'	 => $fax_no_manager,
'manager_email'	 => $email_id_manager
);	
//print_r($manager_details);die();	

$id =db_insert('fa_manager_details')->fields($manager_details)->execute();

if($id){
$commands[] = ajax_command_replace('#view_manager_details_id', "<div id ='view_manager_details_id'><div class='col-md-12 col-xs-12'>".view_manager_details().'</div></div>');
$commands[] = ajax_command_replace('#manager_error_replace_div', '<div id="manager_error_replace_div" style="color:#F00"><div class="col-md-12">Details of manager Permanent Address & Present address details has been saved successfully.</div></div>');
}
			  }else{
				  $commands[] = ajax_command_replace('#manager_error_replace_div', '<div id="manager_error_replace_div" style="color:#F00"><div class="col-md-12">Age fields under Details of Manager of the Factories shoud be integer</div></div>');
			  }
		  }else{
			   $commands[] = ajax_command_replace('#manager_error_replace_div', '<div id="manager_error_replace_div" style="color:#F00"><div class="col-md-12">All fields under Details of Manager of the Factories  shoud be mandatory</div></div>');
		  }
	 }
	 
		
			return array('#type' => 'ajax', '#commands' => $commands);
		}
		
//--------------------fetchWorker----------------------------
function get_worker_details_data($application_id){
	$get_all_data = array();
	$type					= '';
	$details				= '';
	$relationship			= '';
	$address_of_director	= '';
	$Sl= 0;
	
	$get_all_data = get_worker_detials($application_id);
	
	$Wcounter		= 0;
	$per_page		= 2;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	
	
	$header 		= array(
									array('data' => 'Sl. No'),
									array('data'=> 'Year'),
									array('data'=> 'Permanent men worker'),
									array('data'=> 'Permanent female worker'),
									array('data'=> 'Permanent transgender worker'),
									
									array('data'=> 'Contractual men worker'),
									array('data'=> 'Contractual female worker'),
									array('data'=> 'Contractual transgender worker'),
									array('data'=> 'Total'),
									array('data'=> 'Act'),
									array('data'=> 'Status'),
									array('data'=> 'Action'),
									//array('data'=> 'Action'),
								);
	if(!empty($get_all_data)){
		
	
		foreach($chunks[$current_page] as $details){ 
		
		if($details ->worker_plan_approval_status == 'F'){
				$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
				else{
					$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/del-worker-registration/'.encryption_decryption_fun('encrypt', $details->id).'/'.encryption_decryption_fun('encrypt', $details->application_reference_no).'/'.encryption_decryption_fun('encrypt', $details->application_id).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
				}
				
		if($details ->worker_active_inactive == 1)
			$status = "Active";
		else
		 $status = "Inactive";
			
		$Sl = $Sl+1;
			
		
			$rows[] 	= array( 
								array('data' =>$Sl,'class' => array('')),
								array('data' =>$details->service_year ,'class' => array('')),
								array('data' =>$details->worker_permanent_male ,'class' => array('')),
								array('data' =>$details->worker_permanent_female ,'class' => array('')),
								array('data' =>$details->worker_permanent_transgender ,'class' => array('')),
								array('data' =>$details->worker_contractual_male ,'class' => array('')),
								array('data' =>$details->worker_contractual_female ,'class' => array('')),
								array('data' =>$details->worker_contractual_transgender ,'class' => array('')),
								array('data' =>$details->worker_total ,'class' => array('')),
								array('data' =>get_service_name($details->service_id) ,'class' => array('')),
								array('data' =>$status ,'class' => array('')),
								array('data' =>$delLink ,'class' => array('')),
								
								//array('data' =>'View' ,'class' => array('')),
								
								
								);
		} 
		
	}
	$output = theme_table(
	array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'replace_div_worker', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
		 return $output;
	
	
}
//-------------Fetch director------------------------
function view_director_proipietor_details(){
	$get_all_data = array();
	$type					= '';
	$details				='';
	$relationship			='';
	$address_of_director	='';
	
	$get_all_data = get_all_director_data();
	
	$Wcounter		= 0;
	$per_page		= 2;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header 		= array(
									array('data' => 'Sl. No'),
									array('data'=> 'Year'),
									array('data'=> 'Type'),
									array('data'=> 'Name'),
									array('data'=> 'Father/Husband'),
									array('data'=> 'Age'),
									array('data'=> 'Residential Address'),
									array('data'=> 'Act'),
									array('data'=> 'Action'),
									//array('data'=> 'Action'),
								);
	if(!empty($get_all_data)){
		foreach($chunks[$current_page] as $details){ 
			$Wcounter++;
			$type =$details->type_director;
			$is_occupier =$details->is_occupier;
			if($is_occupier == 1){
				$occupier = '<br/>(Occupier)';
			}
			if($details->application_status == 'F'){
				$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
			else if($details->worker_plan_approval_status == 'F'){
				$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
				
				else{
					$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/del-dir-registration/'.encryption_decryption_fun('encrypt', $details->id).'/'.encryption_decryption_fun('encrypt', $details->application_reference_no).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
				}
		$fieldArr_director			 =  array('district_director','sub_division_director','area_type_director','block_mun_cor_sez_not_director','grm_ward_sector_not_director','police_station_director','pincode_director','state_director','post_office_director');
    $address_of_director	 =	$details->adress_line1_director.'<br>'.get_full_address('fa_director_details','sub-table',$details->id,$fieldArr_director);
			$rows[] 	= array( 
								array('data' =>$Wcounter,'class' => array('')),
								array('data' =>$details->add_year_director ,'class' => array('')),
								array('data' =>$type.$occupier ,'class' => array('')),
								array('data' =>$details->name_director .'<br>Din:-'.$details->din_director ,'class' => array('')),
								array('data' =>$relationship.'-'.$details->father_husband_name_director ,'class' => array('')),
								array('data' =>$details->age_director ,'class' => array('')),
								array('data' =>$address_of_director ,'class' => array('')),
								array('data' =>get_service_name($details->director_service_id) ,'class' => array('')),
								array('data' =>$delLink ,'class' => array('')),
								//array('data' =>'View' ,'class' => array('')),
								
								
								);
		} 
		
	}
	$output = theme_table(
	array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'view_director_details_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
		 return $output;
	
	
}
//------------delete director-----------/
	function delete_uploaded_director_data($id,$reference_no){
			
			drupal_add_library('system', 'drupal.ajax');
			
			if (trim(encryption_decryption_fun('decrypt', $id)) != 0) {
				$query = db_delete('fa_director_details');
		 		$query->condition('id', trim(encryption_decryption_fun('decrypt', $id)),'=');
		 		$query->condition('application_reference_no',trim(encryption_decryption_fun('decrypt', $reference_no)),'=');
		 		$query->execute();
			}
		 
		 	$commands = array();
			$commands[] = ajax_command_replace('#view_director_details_id', "<div id ='view_director_details_id'><div class='col-md-12 col-xs-12'>".view_director_proipietor_details().'</div></div>');
		 	$page = array('#type' => 'ajax', '#commands' => $commands);
		 	ajax_deliver($page);
	 		
	}

//-------------Fetch manager------------------------
function view_manager_details(){
	$get_all_data 			= array();
	$type					= '';
	$details				= '';
	$relationship			= '';
	$address_of_manager	= '';
	
	$get_all_data = get_all_manager_data();
	
	$Wcounter		= 0;
	$per_page		= 2;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header 		= array(
									array('data' => 'Sl. No'),
									array('data'=> 'Year'),
									//array('data'=> 'Type'),
									array('data'=> 'Name'),
									array('data'=> 'Father/Husband'),
									array('data'=> 'Age'),
									array('data'=> 'Permanent Address'),
									array('data'=> 'Present Address & Contact'),
									array('data'=> 'Act'),
									array('data'=> 'Action'),
								);
	if(!empty($get_all_data)){
		
	
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
					$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/del-manager-registration/'.encryption_decryption_fun('encrypt', $manager_details->id).'/'.encryption_decryption_fun('encrypt', $manager_details->application_reference_no).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
				}
		$fieldArr_manager			 =  array('district_manager','sub_division_manager','area_type_manager','block_mun_cor_sez_not_manager','grm_ward_sector_not_manager','police_station_manager','pincode_manager','state_manager','post_office_manager');
   $address_of_manager	 =	$manager_details->adress_line1_manager.'<br>'.get_full_address('fa_manager_details','sub-table',$manager_details->id,$fieldArr_manager);
			$rows[] 	= array( 
								array('data' =>$Wcounter,'class' => array('')),
								array('data' =>$manager_details->add_year_manager ,'class' => array('')),
								//array('data' =>$type ,'class' => array('')),
								array('data' =>$manager_details->name_manager ,'class' => array('')),
								array('data' =>$relationship.'-'.$manager_details->father_husband_name_manager ,'class' => array('')),
								array('data' =>$manager_details->age_manager ,'class' => array('')),
								array('data' =>$address_of_manager ,'class' => array('')),	
								array('data' =>$manager_details->manager_present_address.'<br>'.'Telephone: '.$manager_details->manager_telephone.'<br>'.'Mobile: '.$manager_details->manager_phone.'<br>'.'FAX: '.$manager_details->manager_fax.'<br>'.'Email: '.$manager_details->manager_email ,'class' => array('')),
								array('data' =>get_service_name($manager_details->manager_service_id) ,'class' => array('')),
								array('data' =>$delLink ,'class' => array('')),
								
								);
		} 
		
	}
	$output = theme_table(
	array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'view_manager_details_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
		 return $output;
	
	
}
//------------delete director-----------/
	function delete_uploaded_manager_data($id,$reference_no){
			
			drupal_add_library('system', 'drupal.ajax');
			
			if (trim(encryption_decryption_fun('decrypt', $id)) != 0) {
				$query = db_delete('fa_manager_details');
		 		$query->condition('id', trim(encryption_decryption_fun('decrypt', $id)),'=');
		 		$query->condition('application_reference_no',trim(encryption_decryption_fun('decrypt', $reference_no)),'=');
		 		$query->execute();
			}
		 
		 	$commands = array();
			$commands[] = ajax_command_replace('#view_manager_details_id', "<div id ='view_manager_details_id'><div class='col-md-12 col-xs-12'>".view_manager_details().'</div></div>');
		 	$page = array('#type' => 'ajax', '#commands' => $commands);
		 	ajax_deliver($page);
	 		
	}

//-------------fetch process
function view_manufacturing_process_details($application_id,$service_id,$factory_typeid){
	$get_all_data = array();
	$type					= '';
	$details				='';
	$relationship			='';
	$address_of_director	='';
	
	$get_all_data = get_manufacturing($application_id,$service_id,$factory_typeid);
	
	$Wcounter		= 0;
	$per_page		= 2;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	
	
	$header 		= array(
									array('data' => 'Sl. No'),
									array('data'=> 'Year'),
									array('data'=> 'Manufacturing process'),
									array('data'=> 'Act'),
									array('data'=> 'Action'),
									
								);
	if(!empty($get_all_data)){
		
		foreach($chunks[$current_page] as $details){ 
			
			$Wcounter++;
			//////////////////////////Nature Delete link///////////////
			if($details ->manufacturing_application_status == 'F'){
				$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
				else{
					$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/del-manufacturing-registration/'.encryption_decryption_fun('encrypt', $details->id).'/'.encryption_decryption_fun('encrypt', $details->application_reference_no).'/'.encryption_decryption_fun('encrypt', $details->application_id).'/'.encryption_decryption_fun('encrypt', $details->service_id).'/'.encryption_decryption_fun('encrypt', $details->factory_type).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
				}
			//////////////////////////Nature Delete link end///////////////
			
			if($details ->manufacturing_active_inactive == 1)
				$status = "Active";
			else
		 		$status = "Inactive";
	
			$rows[] 	= array( 
								array('data' =>$Wcounter,'class' => array('')),
								array('data' =>$details->service_year ,'class' => array('')),
								array('data' =>$details->nature_manufacturing ,'class' => array('')),
								array('data' =>get_service_name($details->service_id) ,'class' => array('')),
								array('data' =>$delLink ,'class' => array('')),
									
								);
		} 
		
	}
	$output = theme_table(
	array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'view_nature_details_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
		 return $output;
}
//--------------------fetch Power-------------------------
function view_power_details($application_id,$service_id,$factory_typeid){
	$get_all_data = array();
	$type					= '';
	$details				= '';
	$relationship			= '';
	$address_of_director	= '';
	
	$get_all_data = fa_power_details($application_id,$service_id,$factory_typeid);
	
	$Wcounter		= 0;
	$per_page		= 2;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header 		= array(
									array('data' => 'Sl. No'),
									array('data'=> 'Year'),
									array('data'=> 'Installed Power'),
									array('data'=> 'Installed Power in HP'),
									array('data'=> 'Act'),
									array('data'=> 'Action'),
									
								);
								
	if(!empty($get_all_data)){
		
		foreach($chunks[$current_page] as $details){ 
			
			$Wcounter++;
			//////////////////////////Power Delete link///////////////
			if($details ->power_application_status == 'F'){
				$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
				else{
					$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/del-power-registration/'.encryption_decryption_fun('encrypt', $details->id).'/'.encryption_decryption_fun('encrypt', $details->application_reference_no).'/'.encryption_decryption_fun('encrypt', $details->application_id).'/'.encryption_decryption_fun('encrypt', $details->service_id).'/'.encryption_decryption_fun('encrypt', $details->factory_type).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
				}
			//////////////////////////Power Delete link end///////////////
			if($details ->power_active_inactive == 1)
				$status = "Active";
			else
		 		$status = "Inactive";
	
			$rows[] 	= array( 
								array('data' =>$Wcounter,'class' => array('')),
								array('data' =>$details->service_year ,'class' => array('')),
								array('data' =>$details->installed_power.'('.$details->power_unit.')' ,'class' => array('')),
								array('data' =>$details->installed_power_hp ,'class' => array('')),
								
								array('data' =>get_service_name($details->service_id) ,'class' => array('')),
								array('data' =>$delLink ,'class' => array('')),
									
								);
		} 
		
	}
	$output = theme_table(
	array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'view_power_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
		 return $output;	
}
function get_director_ajax_load($form, $form_state){
	$commands = array();
	$commands[] = ajax_command_replace('#director_state_replace', drupal_render($form['director_details']['director_residential_state']));
	$commands[] = ajax_command_replace('#director_dis_replace', drupal_render($form['director_details']['director_residential_district']));
	$commands[] = ajax_command_replace('#director_sub_replace', drupal_render($form['director_details']['director_residential_sub_division']));
	$commands[] = ajax_command_replace('#director_area_type_replace', drupal_render($form['director_details']['director_residential_area_type']));
	$commands[] = ajax_command_replace('#director_area_details_replace', drupal_render($form['director_details']['director_residential_area_details']));
	$commands[] = ajax_command_replace('#director_area_division_replace', drupal_render($form['director_details']['director_residential_area_division']));
	$commands[] = ajax_command_replace('#director_ps_replace', drupal_render($form['director_details']['director_residential_ps']));
	$commands[] = ajax_command_replace('#director_po_replace', drupal_render($form['director_details']['director_residential_postoffice']));
	
	return array('#type' => 'ajax', '#commands' => $commands);
}


function get_director_details_ajax($form, $form_state){
	$commands 	= array();	
	$commands[] = ajax_command_replace('#view_director_details_id', drupal_render($form['director_details']['view_director']));
		
	return array('#type' => 'ajax', '#commands' => $commands);	
}
function get_manager_details_ajax($form, $form_state){
	$commands 	= array();	
	$commands[] = ajax_command_replace('#view_manager_details_id', drupal_render($form['manager_details']['view_manager']));
		
	return array('#type' => 'ajax', '#commands' => $commands);	
}
function get_pollution_ajax_load($form, $form_state){
	$commands 	= array();	
	$commands[] = ajax_command_replace('#reference_no_approval_id', drupal_render($form['director_factory_statring_info']['reference_no_approval_arrangments']));
	$commands[] = ajax_command_replace('#reference_date_approval_id', drupal_render($form['director_factory_statring_info']['date_approval_arrangments']));
	
	$commands[] = ajax_command_replace('#pollution_type_id', drupal_render($form['director_factory_statring_info']['factory_pollution_type']));	

	$commands[] = ajax_command_replace('#edit-upload-intimation-ajax-wrapper', drupal_render($form['director_factory_statring_info']['upload_intimation']));		
	return array('#type' => 'ajax', '#commands' => $commands);	
}
function details_worker_hp_yearly_submit($form, &$form_state){
	
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

function get_ajax_din($form, &$form_state)
{
    $commands   = array();
    $commands[] = ajax_command_replace('#ld_show_din', drupal_render($form['director_details']['directors_din_no']));
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}
function delete_uploaded_worker_data($id,$reference_no,$application_id){
			
			drupal_add_library('system', 'drupal.ajax');
			$applicationid = encryption_decryption_fun('decrypt', $application_id);
			
			if (trim(encryption_decryption_fun('decrypt', $id)) != 0) {
				$query = db_delete('fa_worker_details');
		 		$query->condition('id', trim(encryption_decryption_fun('decrypt', $id)),'=');
		 		$query->condition('application_reference_no',trim(encryption_decryption_fun('decrypt', $reference_no)),'=');
		 		$query->execute();
			}
		 
		 	$commands = array();
			$commands[] = ajax_command_replace('#replace_div_worker', "<div id ='replace_div_worker'><div class='col-md-12 col-xs-12'>".get_worker_details_data($applicationid).'</div></div>');
		 	$page = array('#type' => 'ajax', '#commands' => $commands);
		 	ajax_deliver($page);
	 		
	}
	

function delete_uploaded_power_data($id,$reference_no,$application_id,$service_id,$factory_typeid){
			
			drupal_add_library('system', 'drupal.ajax');
			$applicationid = encryption_decryption_fun('decrypt', $application_id);
			$serviceid = encryption_decryption_fun('decrypt', $service_id);
			$factorytype_id = encryption_decryption_fun('decrypt', $factory_typeid);
			
			if (trim(encryption_decryption_fun('decrypt', $id)) != 0) {
				$query = db_delete('fa_power_details');
		 		$query->condition('id', trim(encryption_decryption_fun('decrypt', $id)),'=');
				$query->condition('application_id',trim(encryption_decryption_fun('decrypt', $application_id)),'=');
		 		$query->condition('application_reference_no',trim(encryption_decryption_fun('decrypt', $reference_no)),'=');
		 		$query->execute();
			}
		 
		 	$commands = array();
			$commands[] = ajax_command_replace('#view_power_id', "<div id ='view_power_id'><div class='col-md-12 col-xs-12'>".view_power_details($applicationid,$serviceid,$factorytype_id).'</div></div>');
		 	$page = array('#type' => 'ajax', '#commands' => $commands);
		 	ajax_deliver($page);
	 		
	}
		function delete_uploaded_manufacturing_data($id,$reference_no,$application_id,$service_id,$factory_typeid){
			
			drupal_add_library('system', 'drupal.ajax');
			$applicationid = encryption_decryption_fun('decrypt', $application_id);
			$serviceid = encryption_decryption_fun('decrypt', $service_id);
			$factorytype_id = encryption_decryption_fun('decrypt', $factory_typeid);
			
			if (trim(encryption_decryption_fun('decrypt', $id)) != 0) {
				$query = db_delete('fa_nature_manufacturing');
		 		$query->condition('id', trim(encryption_decryption_fun('decrypt', $id)),'=');
				$query->condition('application_id',trim(encryption_decryption_fun('decrypt', $application_id)),'=');
		 		$query->condition('application_reference_no',trim(encryption_decryption_fun('decrypt', $reference_no)),'=');
		 		$query->execute();
			}
		 
		 	$commands = array();
			$commands[] = ajax_command_replace('#view_nature_details_id', "<div id ='view_nature_details_id'><div class='col-md-12 col-xs-12'>".view_manufacturing_process_details($applicationid,$serviceid,$factorytype_id).'</div></div>');
		 	$page = array('#type' => 'ajax', '#commands' => $commands);
		 	ajax_deliver($page);
	 		
	}
?>