<?php
 function details_of_director($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$linknumber,$linkdate,$flagmapp){
	global $base_root, $base_path, $user;
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	if(empty($application_id)){
		  	drupal_set_message(('At first you must be filled up the general information of factory then go to second tab'),'warning');
			drupal_goto('applicant/caf-reg/registrtatoin-license/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$linknumber.'/'.$linkdate.'/'.$flagmapp) ;
	}else{
			$get_fa_cafa 				= 	get_fa_cafa($application_id);
			$reference_number 			= 	$get_fa_cafa['reference_number'];
			$is_year_calculation_tab    =	$get_fa_cafa['is_year_calculation_tab'];
			$factory_owershiptype    	=	$get_fa_cafa['factory_owershiptype'];
			//echo $factory_owershiptype;die();
	}
	if(empty($is_year_calculation_tab)){
		  	drupal_set_message(('Please fill up the second tab than fill up the director information'),'warning');
			
			drupal_goto('applicant/caf-reg/details-applyingyear-registration/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$linknumber.'/'.$linkdate.'/'.$flagmapp) ;
	 }   
	$form 				= array();
	$form['serviceid'] 	= array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> $serviceid,
	);
	$form['factorytypeid'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $factory_typeid
	);
	$form['application_reference_no'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> encryption_decryption_fun('encrypt', $reference_number)
	);
	$form['applicationid'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $applicationid
	);	
	/********** Factory checking data **********/
	$checked 				=	get_checking($application_id,$service_id,$factory_type_id,$reference_number);
	$verify_details     	= 	($checked['verify_details'])? $checked['verify_details'] : ''; 
	$previous_details_view 	=   get_previous_details_view($application_id,$reference_number,$factory_type_id,$service_id);
	//print_r($previous_details_view);die();
	$remark_field 	= explode(',', $checked['verify_details']);
	foreach ($remark_field as $fieldname){ 
				if($fieldname == 'director_details'){ $director_details_ck = "hidden";}
	}
	
	$form['director_details'] 	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row"><div class="box box-info"><div class="box-header with-border">
              				<h3 class="box-title">K.Details of Directors/Partners/Proprietor of the Factories</h3>
			    			</div><div class = "box-body">',
						);
	
	$form['director_details']['director_year'] 	= array(
  			'#prefix' 	 	=> '<div class="row"><div class="col-md-4 col-xs-4">',
  			'#suffix' 	 	=> '</div>',
  			'#type' 	 	=> 'select',
			'#required' 	=> TRUE,
			'#title'		=>	t('(i).Select Application Period'),
			'#attributes' 	=> 	array('class' => array('form-control')),
  			'#options' 	 	=>  fetch_occupier_year($application_id,$service_id,$factory_type_id,$reference_number),
			'#ajax' 		=> array(
										'event' 	=> 'change',
										'effect' 	=> 'fade',
										'callback' 	=> 'get_ajax_occupier_type',
										'progress' 	=> array(
																'type' 		=> 'throbber',
																'message' 	=> t('loading')
            												)
       								)
		);
       $value_director_year   = isset($form_state['values']['director_year']) ? $form_state['values']['director_year'] : '';
	  
    $form['director_details']['occupier_type'] = array(
				'#prefix' 			=> '<div id="occupier_type_id"><div class="col-md-4 col-xs-4">',
				'#suffix' 			=> '</div></div>',
				'#title' 			=> t('(ii).Type'),
				'#type' 			=> 'textfield',
				//'#required' 		=> TRUE,
				'#attributes' 		=> array('readonly' => 'readonly','class' => array('form-control')),
		);
	$form['director_details']['din_director'] = array(
			'#prefix' 	=> '<div id="ld_show_din">',
			'#suffix'	=> '</div>',
	);
	//$factory_owershiptype = 'pv';
	// $get_ownership_type = get_previous_details_yearwise($application_id,$reference_number,$factory_type_id,$service_id,$value_director_year);print_r($get_ownership_type);//die();
	if(!empty($value_director_year)){   //echo $factory_owershiptype;die();
	 $get_ownership_type = get_previous_details_yearwise($application_id,$reference_number,$factory_type_id,$service_id,$value_director_year);
	 
	 foreach($get_ownership_type as $owner_occupier){
		 $ownership_type 	= $owner_occupier->conversation_ownership_type;
		
	} 
	$ownership_type =  !empty($ownership_type)?$ownership_type:$factory_owershiptype;
		
	 if($ownership_type == 'pv' || $ownership_type == 'ltd'){
		 $occupier_ownership_type 	= 'Director';
		 $form['director_details']['din_director'] = array(
				'#prefix' 			=> '<div id="ld_show_din"><div class="col-md-4 col-xs-4">',
				'#suffix' 			=> '</div></div>',
				'#title' 			=> t('(ii)(a).DIN'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class' => array('form-control')),
		); 
	 }if($ownership_type == 'par_firm'){
		 $occupier_ownership_type 	= 'Partner';
	 }if($ownership_type == 'pro_firm'){
		 $occupier_ownership_type 	= 'Proprietor';
	 }if($ownership_type == 'govt' || $ownership_type == 'psu' || $ownership_type == 'others'){
		 $occupier_ownership_type 	= 'Nominated Occupier';
	 }
	    $form['director_details']['occupier_type'] = array(
				'#prefix' 			=> '<div id="occupier_type_id"><div class="col-md-4 col-xs-4">',
				'#suffix' 			=> '</div></div>',
				'#title' 			=> t('(ii).Type'),
				'#type' 			=> 'textfield',
				'#value'			=> $occupier_ownership_type,
				'#required' 		=> TRUE,
				'#attributes' 		=> array('readonly' => 'readonly','class' => array('form-control')),
		); 
	   }
		
	$form['director_details']['name_directors'] 	= array(
			  '#prefix' 		=> '<div class="col-md-4 col-xs-4">',
			  '#suffix' 		=> '</div>',
			  '#title' 			=> t('(iii).Name of Directors/Partners/Proprietor'),
			  '#required' 		=> TRUE,
			  '#type' 			=> 'textfield', 
			  '#attributes' 	=> array('class' => array('form-control')),
			
	  	);
	$form['director_details']['age_directors'] 	= array(
			  '#prefix' 		=> '<div class="col-md-4 col-xs-4">',
			  '#suffix' 		=> '</div>',
			  '#title' 			=> t('(iv).Age'),
			  '#required' 		=> TRUE,
			  '#type' 			=> 'textfield',
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'), 
			  '#maxlength' 			=> 2, 
			  '#attributes' 	=> array('class' => array('form-control')),
			
	  	);
	$form['director_details']['father_husband_type_directors'] 	= array(
			  '#prefix' 		=> '<div class="col-md-4 col-xs-4">',
			  '#suffix' 		=> '</div>',
			  '#title' 			=> t('(v).Relationship'),
			  '#required' 		=> TRUE,
			  '#type' 			=> 'select',
			  '#options' 		=> array(''=>'Select','1'=>'D/O','2'=>'S/0',3=>'W/O'),  
			  '#attributes' 	=> array('class' => array('form-control')),
			
	  	);
	$form['director_details']['father_husband_name_directors'] 	= array(
			  '#prefix' 		=> '<div class="col-md-4 col-xs-4">',
			  '#suffix' 		=> '</div>',
			  '#title' 			=> t('(vi).Father/Husband Name'),
			  '#required' 		=> TRUE,
			  '#type' 			=> 'textfield',
			  '#attributes' 	=> array('class' => array('form-control')),
			
	  	);
	$form['director_details']['director_residential_pincode'] 	= array(
			  '#prefix' 			=> '<div class = "col-md-4 col-xs-12">',
			  '#suffix' 			=> '</div>',
			  '#title' 				=> t('(vii).Pincode'),
			  '#autocomplete_path' 	=> 'pinautocomplete',
	  		  '#maxlength' 			=> 6, 
			  '#required' 			=> TRUE,
			  '#type' 				=> 'textfield',
			  '#attributes' 		=> array('class' => array('form-control')),
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
				  '#prefix' 			=> '<div id = "director_state_replace"><div class="col-md-4 col-xs-12">',
				  '#suffix' 			=> '</div></div>',
				  '#title' 				=> t('(viii).State'),
				  '#type' 				=> 'select',
				  '#disabled' 			=> TRUE,
				  '#required' 			=> TRUE,
				  '#attributes' 		=> array('class'=>array('form-control')),
				  '#options' 			=> array(),
				
	  	);
	$form['director_details']['director_residential_district'] 	= array(
			  	'#prefix' 			=> '<div id = "director_dis_replace"><div class="col-md-4 col-xs-12">',
			  	'#suffix' 			=> '</div></div>',
			  	'#type' 			=> 'select',
				'#title' 			=> t('(ix).District'),
				'#required' 		=> TRUE,
				'#disabled' 		=> TRUE,
			   	'#attributes' 		=> array('class'=>array('form-control')),
			   	'#options' 			=> array(),
				
	  	);
	$form['director_details']['director_residential_sub_division'] 	= array(
			  '#prefix' 			=> '<div id = "director_sub_replace"><div class="col-md-4 col-xs-12">',
			  '#suffix' 			=> '</div></div>',
			  '#type' 				=> 'select',
			  '#title' 				=> t('(x).Sub division'),
			  '#required' 			=> TRUE,
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#options' 			=> array(),
				
	  );
	 $form['director_details']['director_residential_area_type'] 	= array(
			  '#prefix' 			=> '<div id = "director_area_type_replace"><div class="col-md-4 col-xs-12">',
			  '#suffix' 			=> '</div></div>',
			  '#type' 				=> 'select',
			  '#title' 				=> t('(xi).Area Type'),
			  '#required' 			=> TRUE,
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#options' 			=> array(),
			    
	  	);
	$form['director_details']['director_residential_area_details'] 	= array(
			  '#prefix' 			=> '<div id = "director_area_details_replace"><div class="col-md-4 col-xs-12">',
			  '#suffix' 			=> '</div></div>',
			  '#title' 				=> t('(xii).Block/Municipality/Corporation/SEZ/Notified'),
			  '#type' 				=> 'select',
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#required' 			=> TRUE,
			  '#options' 			=> array(),
			 
			  
	  	);
	$form['director_details']['director_residential_area_division'] 	= array(
			  '#prefix' 			=> '<div id = "director_area_division_replace"><div class="col-md-4 col-xs-12">',
			  '#suffix' 			=> '</div></div>',
			  '#title' 				=> t('(xiii).Gram Panchayat/Ward/Sector/Notified Area'),
			  '#type' 				=> 'select', 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#required' 			=> TRUE,
			  '#options' 			=> array(),
				
	 );
	 $form['director_details']['director_residential_ps'] 	= array(
			  '#prefix' 			=> '<div id = "director_ps_replace"><div class="col-md-4 col-xs-12">',
			  '#suffix' 			=> '</div></div>',
			  '#title' 				=> t('(xiv).Police station'),
			  '#type' 				=> 'select', 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#required' 			=> TRUE,
			  '#options' 			=> array(),
				
	 );
	 $form['director_details']['director_residential_postoffice'] 	= array(
			  '#prefix' 			=> '<div id = "director_po_replace"><div class="col-md-4 col-xs-12">',
			  '#suffix' 			=> '</div></div>',
			  '#title' 				=> t('(xv).Post office'),
			  '#type' 				=> 'select', 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#required' 			=> TRUE,
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
				  		'#prefix' 		=> '<div id="director_state_replace"><div class="col-md-4 col-xs-12">',
				 	    '#suffix' 		=> '</div></div>',
				 	    '#type' 		=> 'select',
						'#required' 	=> TRUE,
						'#title' 		=> t('(viii).State'),
						'#disabled' 	=> TRUE,
						'#attributes' 	=> array('class'=>array('form-control')),
				  		'#options' 		=> get_all_statecode($state_res_code),
				  		'#value'	    => !empty($state_res_code) ? $state_res_code	:'',
				  		'#ajax'			=> array(
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
					  '#prefix' 		=> '<div id = "director_dis_replace"><div class="col-md-4 col-xs-12">',
					  '#suffix' 		=> '</div></div>',
					  '#type' 			=> 'select',
					  '#required' 		=> TRUE,
					  '#title' 			=> t('(ix).District'),
					  '#disabled' 		=> TRUE,
					  '#attributes' 	=> array('class'=>array('form-control')),
					  '#options' 		=> get_all_districtcode_withstate($value_director_state_code,$dis_res_code),
					  '#value'			=> !empty($dis_res_code) ? $dis_res_code	:'',
  					  '#ajax'			=> array(
													'effect' 		=> 'fade',			
													'callback'		=> 'get_director_ajax_load',
													'progress'		=>	array(
																				'type'			=>'throbber',
																				'message'		=>t('loading'),
																			),
											)
		  		);
				$value_director_dis_code 	= !isset($form_state['values']['director_residential_district'])? $form_state['values']['director_residential_district'] :$dis_res_code;
				$is_sub_exists				= is_sub_exists($value_director_dis_code);
				if($is_sub_exists>0){
					$form['director_details']['director_residential_sub_division'] 	= array(
						  '#prefix' 			=> '<div id = "director_sub_replace"><div class="col-md-4 col-xs-12">',
						  '#suffix' 			=> '</div></div>',
						  '#type' 				=> 'select',
						  '#title' 				=> t('(x).Sub Division'),
						  '#required' 			=> TRUE,
						  '#attributes' 		=> array('class'=>array('form-control')),
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
						  '#prefix' 			=> '<div id = "director_area_type_replace"><div class="col-md-4 col-xs-12">',
						  '#suffix' 			=> '</div></div>',
						  '#title' 				=> t('(xi).Area Type'),
						  '#attributes' 		=> array('class'=>array('form-control')),
						  '#required' 			=> TRUE,
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
							   '#prefix' 			=> '<div id = "director_area_details_replace"><div class="col-md-4 col-xs-12">',
							   '#suffix' 			=> '</div></div></div>',
							   '#type' 				=> 'select',
							   '#title' 			=> t('(xii).Block'),
							   '#options' 			=> get_block_municipality_other($value_director_sub_code, $value_director_area_type_code),
							   '#required' 			=> TRUE,
							   '#attributes' 		=> array('class'=>array('form-control')),
	  						   '#ajax'				=>  array(
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
							  '#prefix' 			=> '<div id = "director_area_details_replace"><div class="col-md-4 col-xs-12">',
							  '#suffix' 			=> '</div></div>',
							  '#type' 				=> 'select',
							  '#title' 				=> t('(xii).Corporation'),
							  '#attributes' 		=> array('class'=>array('form-control')),
							   '#required' 			=> TRUE,
							  '#options' 			=> get_block_municipality_other($value_director_sub_code, $value_director_area_type_code),
							  '#ajax'=> array(
												 'effect' 		=> 'fade',			
												 'callback'		=> 'get_director_ajax_load',
												  'progress'	=>	array(
																				'type'			=>'throbber',
																				'message'		=>t('loading'),
																			),
												)
						);
					}if($value_director_area_type_code=='M'){
						$form['director_details']['director_residential_area_details'] 	= array(
							  '#prefix' 			=> '<div id = "director_area_details_replace"><div class="col-md-4 col-xs-12">',
							  '#suffix' 			=> '</div></div>',
							  '#type' 				=> 'select',
							  '#title' 				=> t('(xii).Municipality'),
							  '#attributes' 		=> array('class'=>array('form-control')),
							   '#required' 			=> TRUE,
							  '#options' 			=> get_block_municipality_other($value_director_sub_code, $value_director_area_type_code),
							  '#ajax'=> array(
												 'effect' 		=> 'fade',			
												 'callback'		=> 'get_director_ajax_load',
												  'progress'	=>	array(
																				'type'			=>'throbber',
																				'message'		=>t('loading'),
																			),
												)
						);
						
					}if($value_director_area_type_code=='S'){
						$form['director_details']['director_residential_area_details'] 	= array(
							  '#prefix' 			=> '<div id = "director_area_details_replace"><div class="col-md-4 col-xs-12">',
							  '#suffix' 			=> '</div></div>',
							  '#type' 				=> 'select',
							  '#title' 				=> t('(xii).SEZ'),
							  '#attributes' 		=> array('class'=>array('form-control')),
							  '#required' 			=> TRUE,
							  '#options' 			=> get_block_municipality_other($value_director_sub_code, $value_director_area_type_code),
							  '#ajax'=> array(
												 'effect' 		=> 'fade',			
												 'callback'		=> 'get_director_ajax_load',
												  'progress'	=>	array(
																				'type'			=>'throbber',
																				'message'		=>t('loading'),
																			),
												)
						);
						
					}if($value_director_area_type_code=='N'){
						$form['director_details']['director_residential_area_details'] 	= array(
							  '#prefix' 			=> '<div id = "director_area_details_replace"><div class="col-md-4 col-xs-12">',
							  '#suffix' 			=> '</div></div>',
							  '#type' 				=> 'select',
							  '#title' 				=> t('(xii).Notified'),
							  '#attributes' 		=> array('class'=>array('form-control')),
							  '#required' 			=> TRUE,
							  '#options' 			=> get_block_municipality_other($value_director_sub_code, $value_director_area_type_code),
							  '#ajax'=> array(
												 'effect' 		=> 'fade',			
												 'callback'		=> 'get_director_ajax_load',
												  'progress'	=>	array(
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
								  '#prefix' 			=> '<div id = "director_area_division_replace"><div class="col-md-4 col-xs-12">',
								  '#suffix' 			=> '</div></div>',
								  '#type' 				=> 'select',
								  '#title' 				=> t('(xii).Gram Panchayat'),
								  '#attributes' 		=> array('class'=>array('form-control')),
								  '#required' 			=> TRUE,
								  '#options'			=>  get_full_villward($value_director_area_details_code,'V'),
							  
						);
								
						}if($value_director_area_type_code=='M'){
							$form['director_details']['director_residential_area_division'] 	= array(
								  '#prefix' 			=> '<div id = "director_area_division_replace"><div class="col-md-4 col-xs-12">',
								  '#suffix' 			=> '</div></div>',
								  '#type' 				=> 'select',
								  '#title' 				=> t('(xii).Ward'),
								  '#attributes' 		=> array('class'=>array('form-control')),
								  '#required' 			=> TRUE,
								  '#options'			=>  get_full_villward($value_director_area_details_code,'W'),
							  
						);
								
						}if($value_director_area_type_code == 'C'){
							$form['director_details']['director_residential_area_division'] 	= array(
								  '#prefix' 			=> '<div id = "director_area_division_replace"><div class="col-md-4 col-xs-12">',
								  '#suffix' 			=> '</div></div>',
								  '#type' 				=> 'select',
								  '#title' 				=> t('(xii).Ward'),
								  '#attributes' 		=> array('class'=>array('form-control')),
								  '#required' 			=> TRUE,
								  '#options'			=>  get_full_villward($value_director_area_details_code,'C'),
							  
							);
								
						}if($value_director_area_type_code == 'S'){
							$form['director_details']['director_residential_area_division'] 	= array(
								  '#prefix' 			=> '<div id = "director_area_division_replace"><div class="col-md-4 col-xs-12">',
								  '#suffix' 			=> '</div></div>',
								  '#type' 				=> 'select',
								  '#title' 				=> t('(xii).Sector'),
								  '#attributes' 		=> array('class'=>array('form-control')),
								  '#required' 			=> TRUE,
								  '#options'			=>  get_full_villward($value_director_area_details_code,$value_director_area_type_code),
							  
							);
								
						}if($value_director_area_type_code == 'N'){
							$form['director_details']['director_residential_area_division'] 	= array(
								  '#prefix' 			=> '<div id = "director_area_division_replace"><div class="col-md-4 col-xs-12">',
								  '#suffix' 			=> '</div></div>',
								  '#type' 				=> 'select',
								  '#title' 				=> t('(xii).Notified Area'),
								  '#attributes' 		=> array('class'=>array('form-control')),
								  '#required' 			=> TRUE,
								  '#options'			=>  get_full_villward($value_director_area_details_code,$value_director_area_type_code),
								
								);
						}
					}
					
				 }
			}else{
				$form['director_details']['director_residential_sub_division'] 	= array(
					  '#prefix' 			=> '<div id = "director_sub_replace">',
					  '#suffix' 			=> '</div>',
					  
	  			);
				$form['director_details']['director_residential_area_type'] 	= array(
							  '#prefix' 			=> '<div id = "director_area_type_replace">',
							  '#suffix' 			=> '</div>',
					
						);
				$form['director_details']['director_residential_area_details'] 	= array(
							  '#prefix' 			=> '<div id = "director_area_details_replace">',
							  '#suffix' 			=> '</div>'
						);
				$form['director_details']['director_residential_area_division'] 	= array(
							  '#prefix' 			=> '<div id = "director_area_division_replace">',
							  '#suffix' 			=> '</div>'
						);
		
		}
		$is_ps_exists = 	is_ps_exists($value_director_dis_code);
		if($is_ps_exists>0){
				$form['director_details']['director_residential_ps'] 	= array(
								  '#prefix' 			=> '<div id = "director_ps_replace"><div class="col-md-4 col-xs-12">',
								  '#suffix' 			=> '</div></div>',
								  '#type' 				=> 'select',
								  '#title' 				=> t('(xiii).Police'),
								  '#attributes' 		=> array('class'=>array('form-control')),
								  '#required' 			=> TRUE,
								  '#options'			=>  get_all_ps($value_director_dis_code),
								
								);
				
			}else{
				$form['director_details']['director_residential_ps'] 	= array(
							  '#prefix' 			=> '<div id = "director_ps_replace">',
							  '#suffix' 			=> '</div>'
						);
			}
		
			
		}else{
					$form['director_details']['director_residential_district'] 	= array(
								'#prefix' 			=> '<div id = "director_dis_replace">',
								'#suffix' 			=> '</div>',
	  						);
					$form['director_details']['director_residential_sub_division'] 	= array(
							  '#prefix' 			=> '<div id = "director_sub_replace">',
							  '#suffix' 			=> '</div>',
							);
					$form['director_details']['director_residential_area_type'] 	= array(
							  '#prefix' 			=> '<div id = "director_area_type_replace">',
							  '#suffix' 			=> '</div>',
							);
					$form['director_details']['director_residential_area_details'] 	= array(
							  '#prefix' 			=> '<div id = "director_area_details_replace">',
							  '#suffix' 			=> '</div>'
							);
					$form['director_details']['director_residential_area_division'] 	= array(
						  '#prefix' 			=> '<div id = "director_area_division_replace">',
						  '#suffix' 			=> '</div>'
						);
					$form['director_details']['director_residential_ps'] 	= array(
						  '#prefix' 			=> '<div id = "director_ps_replace">',
						  '#suffix' 			=> '</div>'
						);
		}
	}else{
		$form['director_details']['director_residential_state'] 	= array(
				  '#prefix' 			=> '<div id = "director_state_replace">',
				  '#suffix' 			=> '</div>',
				 
	  		);
			$form['director_details']['director_residential_district'] 	= array(
			  '#prefix' 			=> '<div id = "director_dis_replace">',
			  '#suffix' 			=> '</div>',
			
	  	);
		$form['director_details']['director_residential_sub_division'] 	= array(
			  '#prefix' 			=> '<div id = "director_sub_replace">',
			  '#suffix' 			=> '</div>',
			  
	  	);
		$form['director_details']['director_residential_area_type'] 	= array(
			  '#prefix' 			=> '<div id = "director_area_type_replace">',
			  '#suffix' 			=> '</div>',
			
	  	);
		$form['director_details']['director_residential_area_details'] 	= array(
			  '#prefix' 			=> '<div id = "director_area_details_replace">',
			  '#suffix' 			=> '</div>'
	  	);
		$form['director_details']['director_residential_area_division'] 	= array(
			  '#prefix' 			=> '<div id = "director_area_division_replace">',
			  '#suffix' 			=> '</div>'
	  	);
		$form['director_details']['director_residential_ps'] 	= array(
			  '#prefix' 			=> '<div id = "director_ps_replace">',
			  '#suffix' 			=> '</div>'
	  	);
		
	}
	if($is_po_exists>0){
		$form['director_details']['director_residential_postoffice'] 	= array(
								  '#prefix' 			=> '<div id = "director_po_replace"><div class="col-md-4 col-xs-12">',
								  '#suffix' 			=> '</div></div>',
								  '#type' 				=> 'select',
								  '#title' 				=> t('(xv).Post office'),
								  '#attributes' 		=> array('class'=>array('form-control')),
								  '#required' 			=> TRUE,
								  '#options'			=>  get_all_po($value_director_residential_pincode),
								
								);
			

		}else{
			$form['director_details']['director_residential_postoffice'] 	= array(
				  '#prefix' 			=> '<div id = "director_po_replace"',
				  '#suffix' 			=> '</div>',
			);
		}
	}
	
		$form['director_details']['markup_1'] 	= array(
			  	'#suffix' => '</div>',
	
	  		);	
	$form['director_details']['director_residential_address'] 	= array(
								  '#prefix' 			=> '<div class="row"><div class="col-md-12 col-xs-12">',
								  '#suffix' 			=> '</div></div>',
								  '#type' 				=> 'textarea',
								   '#rows'				=> 3,
								  '#title' 				=> t('(xvi).Address'),
								  '#attributes' 		=> array('class'=>array('form-control')),
								  '#required' 			=> TRUE,
								 
								
								);
	
	
///////////////////////////////////end ////////////////////////////
	$form['director_details']['same_data'] = array(
			'#type' 			=> 'checkbox',
			'#default_value' 	=> $same_data,
			'#attributes'		=> array('class' => array( '')),
			'#title' 			=> t('Same as all years Director'),
			'#prefix' 			=> '<div class="row"><div class="col-md-12 col-xs-12">',
			'#suffix'			=> '</div></div>'
    );
		
	$form['director_details']['director_error'] = array(
		  	   	'#prefix' 	=> '<div id="director_error_replace_div"><div class="col-md-12 col-xs-12">',
		   		'#suffix' 	=> '</div></div>'	
		);	

	$is_director_exists =is_director_exists();
		if($is_director_exists>0){
			
			$form['director_details']['view_director'] = array(
				 '#prefix' 		=> '<div id="view_director_details_id"><div class="col-md-12 col-xs-12">',
				 '#type'		=> 'markup',
				 '#markup'		=>	view_director_proipietor_details($application_id,$service_id,$factory_type_id,$reference_number),
				 '#suffix' 		=> '</div></div>'
			);
			
		}else{
				$form['director_details']['view_director'] = array(
				 '#prefix' 		=> '<div id="view_director_details_id"><div class="col-md-6 col-xs-12">',
				 '#type'		=> 'markup',
				 '#suffix' 		=> '</div></div>'
			);
		}
		
		$form['back_link']	 = array(
			'#prefix' 	=> '<div class="col-md-12 col-xs-12" align="left">',
			'#suffix' 	=> '</div>',
			'#markup' 	=> l(t('Back'),'applicant/decission/', array('html' => TRUE,'attributes'=> array('class'=>array('btn btn-info ')))),
		);
		
		if(!empty($director_details_ck)){	
				$form['continue_link']	 = array(
						'#prefix' 		=> '</div></div><div align="right">',  
						'#suffix' 		=> '</div>',	
						'#markup' 		=> l(t('Continue'),'applicant/caf-reg/details-worker-registration/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$linknumber.'/'.$flagmapp, array('html' => TRUE,'attributes'=> array('class'=>array('btn btn-info ')))),
				);
		  }else{
				 $form['submit'] = array (
					  '#prefix' 	=> '</div></div><div align="right">',  
					  '#suffix' 	=> '</div>',
					  '#attributes'	=> array('class'=>array('btn btn-info')),
					  '#type' 		=> 'submit',
					  '#value' 		=> 'Save'
				);
		  }
		   return $form; 
         }


		

//-------------Fetch director------------------------
function view_director_proipietor_details($application_id,$service_id,$factory_typeid,$reference_number){
	$get_all_data = array();
	$type					= '';
	$details				='';
	$relationship			= '';
	$address_of_director	='';
	
	$get_all_data = get_director_details_service($application_id,$service_id,$factory_typeid,$reference_number);
	//print_r($get_all_data);die();
	
	$Wcounter		= 0;
	$per_page		= 2;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header 		= array(
									array('data' => 'Sl. No'),
									array('data'=> 'Application period'),
									array('data'=> 'Name'),
									array('data'=> 'Father/Husband'),
									array('data'=> 'Age'),
									array('data'=> 'Residential Address'),
									array('data'=> 'Action'),
									//array('data'=> 'Action'),
								);
	if(!empty($get_all_data)){
		foreach($chunks[$current_page] as $details){ 
			$Wcounter++;
			if(!empty($details->din_director)){
				$din = 'DIN:-'.$details->din_director;
				}	
			$type =$details->type_director;
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
								array('data' =>$details->add_year_director ,'class' => array('')),
								array('data' =>$details->name_director.'('.$type.')<br>'.$din ,'class' => array('')),
								array('data' =>$relationship.'-'.$details->father_husband_name_director ,'class' => array('')),
								array('data' =>$details->age_director ,'class' => array('')),
								array('data' =>$address_of_director ,'class' => array('')),
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
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
		 return $output;
	
	
}
//------------delete director-----------/
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

function get_ajax_occupier_type($form, &$form_state){
    $commands   		= array();
	$commands[] 		= ajax_command_replace('#occupier_type_id', drupal_render($form['director_details']['occupier_type']));
	$commands[] 		= ajax_command_replace('#ld_show_din', drupal_render($form['director_details']['din_director']));
	return array('#type' => 'ajax','#commands' => $commands);
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


/*function get_director_details_ajax($form, $form_state){
	$commands 	= array();	
	$commands[] = ajax_command_replace('#view_director_details_id', drupal_render($form['director_details']['view_director']));
		
	return array('#type' => 'ajax', '#commands' => $commands);	
}
*/

function details_of_director_validate($form, &$form_state){
	$name_directors = $form_state['values']['name_directors'];
	if (!preg_match('/[A-Za-z]+$/', $name_directors)) {  
    form_set_error('name_directors', t('Director Name should be text only!!'));
  }	
  $father_husband_name_directors = $form_state['values']['father_husband_name_directors'];
	if (!preg_match('/[A-Za-z]+$/', $father_husband_name_directors)) {  
    form_set_error('father_husband_name_directors', t('Father Name should be text only!!'));
  }	
  
  
 // $occupier_passport = $form_state['values']['occupier_passport'];
//  if (!preg_match('/[a-zA-Z]{2}[0-9]{7}/', $occupier_passport)) {
//    form_set_error('occupier_passport', t('Passport Number should be Valid!'));
//  }
  
   	  
}


	
function details_of_director_submit($form, &$form_state){
	
	 global $user;
	 $uid 								= $user->uid;
	 $val   							= $form_state['values'];
	 $type_data 						= $val['occupier_type'];
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
	 
	 $directors_din_no					= $val['din_director'];
	 if(empty($directors_din_no)){
	 	$directors_din_no 				= NULL;
	 }
	 $application_reference_no			= encryption_decryption_fun('decrypt',$val['application_reference_no']);
	 $same_data            				= $val['same_data'];
	 //$year_data 						= fetch_year($application_id,$director_service_id,$factory_type_id,$application_reference_no);
	 //----change in new code
	$year_data	 						= fetch_occupier_director_year($application_id,$director_service_id,$factory_type_id,$application_reference_no);
	 	 if($same_data==1){
			
			 $i = 1;
			 foreach($year_data as $row){
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
							'add_year_director'					=> $row->calculate_year,
							'application_status'				=> 'In',
							'director_service_id'				=> $director_service_id,
							'application_reference_no'			=> $application_reference_no,
							'din_director'						=> $directors_din_no,
							'active_inactive_director'			=> $row->is_active_year,
							'valid_year'					 	=> $row->calculate_end_year,
							'valid_time_period'					=> $row->valid_time_period,
							'starting_year'	     			 	=> $row->calculate_starting_year,
							'calculate_year_id'				 	=>  $row->id
					);
				$id = db_insert('fa_director_details')->fields($director_propieter_details)->execute();
				$i= $i+1;
			}
		}else{
				$fetch_year_details = fetch_year_details($application_id,$director_service_id,$factory_type_id,$application_reference_no,$add_year_director);
				//print_r($fetch_year_details);die();
						$calculate_year_id				 	= $fetch_year_details['id'];
						$active_inactive_director			= $fetch_year_details['is_active_year'];
						$valid_year					 		= $fetch_year_details['calculate_end_year'];
						$valid_time_period					= $fetch_year_details['valid_time_period'];
						$starting_year	     			 	= $fetch_year_details['calculate_starting_year'];
					
			
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
						'din_director'						=> $directors_din_no,
						'active_inactive_director'			=> $active_inactive_director,
						'valid_year'					 	=> $valid_year,
						'valid_time_period'					=> $valid_time_period,
						'starting_year'	     			 	=> $starting_year,
						'calculate_year_id'				 	=> $calculate_year_id
					);
					if(!empty($val['director_year'])){
							$id = db_insert('fa_director_details')->fields($director_propieter_details)->execute();
							
						}
				
					if(!empty($id)){
								drupal_set_message('Details of director has been saved successfully.');
							}	
					}
				$form_state['rebuild'] = true;
			}
?> 