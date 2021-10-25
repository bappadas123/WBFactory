<?php
  drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
  drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
  
  function form18_injured_person_details($form, &$form_state,$formid ,$referenceid, $factorytypeid, $serviceid){
	  
	  global $base_root,$base_path,$user;
	  $uid 						= $user->uid;
	  $form = array();
	  
	  $form_id 	 	= encryption_decryption_fun('decrypt', $formid);
	  $reference_id = encryption_decryption_fun('decrypt', $referenceid);
	  $factory_typeid 	= encryption_decryption_fun('decrypt', $factorytypeid);
	$service_id 	= encryption_decryption_fun('decrypt', $serviceid);//echo $form_id.''.$reference_id.''.$factory_typeid.''.$service_id;

	  //PREVIOUS TAB FILL REDIRECTION
	  $get_previous_tab_data = db_query("SELECT count(*) FROM {fa_form18_notice_accident} where id = '$form_id' AND reference_number ='$reference_id' AND  factory_typeid ='$factory_typeid' AND accident_place !=''")->fetchObject()->count;
	 
	if($form_id == 0 && $reference_id == 0 && $factory_id == 0){
	  drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Factory Information Tab.</h5>'),'alert alert-danger alert-dismissible');
	  drupal_goto('applicant/form18/default/'.$formid.'/'.$referenceid.'/'.$factorytypeid.'/'.$serviceid) ;
	} else if($get_previous_tab_data == 0) {
	  drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Accident Details Tab.</h5>'),'alert alert-danger alert-dismissible');
	  drupal_goto('applicant/form18/accident-details/'.$formid.'/'.$referenceid.'/'.$factorytypeid.'/'.$serviceid) ;
	}
	//PREVIOUS TAB FILL REDIRECTION
	
	
		$get_all_data = get_accident_injured_person_data($form_id);
		//print_r($get_all_data);
	  
	 	$form['formid_hidden'] 		= array(
			'#type' 				=> 'hidden',
			'#default_value' 		=> $formid
		);	
	  	$form['referenceid_hidden'] = array(
			'#type' 				=> 'hidden',
			'#default_value' 		=> $referenceid
		);	
	  	$form['factorytypeid_hidden'] 	= array(
			'#type' 				=> 'hidden',
			'#default_value' 		=> $factorytypeid
		);
			
		$form['serviceid_hidden'] 	= array(
			'#type' 				=> 'hidden',
			'#default_value' 		=> $serviceid
		);

	 // Enter Patient Details //
	 
	 $form['notice_accident_injured_details'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('Details of Injured Person'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE, // Added
     );
	$form['notice_accident_injured_details']['accident_person_name'] = array(
		'#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-6"><label class="input label-block">',
		'#suffix' 			=> '</label></div>',
		'#title' 			=> t('(a). Name of the Injured Person'),
		'#type' 			=> 'textfield',
		'#required' 		=> TRUE,
		'#value' 			=> $get_all_data[0]->accident_person_name,
	);
	$form['notice_accident_injured_details']['age'] = array(
		'#prefix' 			=> '<div class="col-md-2 col-xs-6"><label class="input label-block">',
		'#suffix' 			=> '</label></div>',
		'#title' 			=> t('(b). Age'),
		'#type' 			=> 'textfield',
		'#required' 		=> TRUE,
		'#value' 			=> $get_all_data[0]->age,
	);
	
	$option = array( "Male" => "Male", "Female" => "Female");
	$form['notice_accident_injured_details']['gender'] = array(
		'#prefix'		 	=> '<div class="col-md-2 col-xs-12">',
		'#suffix' 			=> '</div>',
		'#title' 			=> t('(c). Sex'),
		'#options'			=> $option,
		'#type' 			=> 'radios',
		'#required' 		=> TRUE,
		'#default_value' 	=> $get_all_data[0]->gender,
	);
	$form['notice_accident_injured_details']['accident_person_occupation'] = array(
		'#prefix' 			=> '<div class="col-md-4 col-xs-6"><label class="input label-block">',
		'#suffix' 			=> '</label></div>',
		'#title' 			=> t('(d). Occupation of Injured Person'),
		'#type' 			=> 'textfield',
		'#required' 		=> TRUE,
		'#value' 			=> $get_all_data[0]->accident_person_occupation,
	);
	$form['notice_accident_injured_details']['accident_person_address'] = array(
		'#prefix' 			=> '<div class="col-md-12 col-xs-6"><label class="input label-block">',
		'#suffix' 			=> '</label></div>',
		'#title' 			=> t('(e). Injured person address'),
		'#type' 			=> 'textarea',
		'#required' 		=> TRUE,
		'#value' 			=> $get_all_data[0]->accident_person_address,
	);
	$form['notice_accident_injured_details']['insurance_number'] = array(
		'#prefix' 			=> '<div class="col-md-2 col-xs-6"><label class="input label-block">',
		'#suffix' 			=> '</label></div>',
		'#title' 			=> t("(g). E.S.I No."),
		'#type' 			=> 'textfield',
		'#required' 		=> TRUE,
		'#value' 			=> $get_all_data[0]->insurance_number,
	);
	$form['notice_accident_injured_details']['local_esi_office'] = array(
		'#prefix' 			=> '<div class="col-md-5 col-xs-6"><label class="input label-block">',
		'#suffix' 			=> '</label></div>',
		'#title' 			=> t("(h). Local E.S.I office to which the injured person is attched."),
		'#type' 			=> 'textfield',
		'#required' 		=> TRUE,
		'#value' 			=> $get_all_data[0]->local_esi_office,
	);
	
	$form['notice_accident_injured_details']['work_starting_time'] = array(
		'#prefix' 			=> '<div class="col-md-5 col-xs-12"><label class="input label-block">',
		'#suffix' 			=> '</label></div>',
		'#title' 			=> t("(i). Hour at which injured person statred work on day of accident"),
		'#type' 			=> 'textfield',
		'#required' 		=> TRUE,
		'#value' 			=> $get_all_data[0]->work_starting_time,
	);
	$form['notice_accident_injured_details']['wages_payable'] = array(
		'#prefix' 			=> '<div class="col-md-6 col-xs-12"><label class="input label-block">',
		'#suffix' 			=> '</label></div>',
		'#title' 			=> t("(j). Whether wages in full or part are payable to him for the day of accident"),
		'#type' 			=> 'textfield',
		'#required' 		=> TRUE,
		'#value' 			=> $get_all_data[0]->wages_payable,
	);
	$form['notice_accident_injured_details']['accident_person_activity'] = array(
		'#prefix' 			=> '<div class="col-md-6 col-xs-12"><label class="input label-block">',
		'#suffix' 			=> '</label></div>',
		'#title' 			=> t("(k). State exactly what the injured person was doing at the time of accident"),
		'#type' 			=> 'textfield',
		'#required' 		=> TRUE,
		'#value' 			=> $get_all_data[0]->accident_person_activity,
	);

	$form['notice_accident_injured_details']['your_opnion'] = array(
		'#prefix'		 	=> '<div class="col-md-12 col-xs-12">',
		'#suffix' 			=> '</div>',
		'#markup' 			=> t('(l). In your opinion, was the injured person at the time of accident -'),
		'#type' 			=> 'markup',
	);

	$option_is_law_applicable = array( "Yes" => "Yes","No" => "No");
	$form['notice_accident_injured_details']['is_law_applicable'] = array(
		'#prefix'		 	=> '<div id="is_law_applicable_id"><div class="col-md-12 col-xs-12" style="padding-left: 41px;">',
		'#suffix' 			=> '</div></div>',
		'#title' 			=> t('(i). acting in contravention of provisions of any law applicable to him'),
		'#options'			=> $option_is_law_applicable,
		'#type' 			=> 'radios',
		'#default_value' 	=> $get_all_data[0]->is_law_applicable,
		'#ajax' 			=> array(
									'event' 		=> 'change',
									'effect' 		=> 'fade',
									'callback' 		=> 'get_ajax_load',
									'progress' 		=> array(
									'type' 			=> 'throbber',
									'message' 		=> t('loading')
								)
       			 )
	);

	$option_is_order_given = array( "Yes" => "Yes","No" => "No");
	$form['notice_accident_injured_details']['is_order_given'] = array(
		'#prefix'		 	=> '<div id="is_order_given_id"><div class="col-md-12 col-xs-12" style="padding-left: 41px;">',
		'#suffix' 			=> '</div></div>',
		'#title' 			=> t('(ii). acting in contravention of  any orders given by or on behalf of his employer'),
		'#options'			=> $option_is_order_given,
		'#type' 			=> 'radios',
		'#default_value' 	=> $get_all_data[0]->is_order_given,
		'#ajax' 			=> array(
									'event' 		=> 'change',
									'effect' 		=> 'fade',
									'callback' 		=> 'get_ajax_load',
									'progress' 		=> array(
									'type' 			=> 'throbber',
									'message' 		=> t('loading')
								)
       			 )
	);
	
	$value_is_law_applicable = isset($form_state['values']['is_law_applicable']) ? $form_state['values']['is_law_applicable'] : $get_all_data[0]->is_law_applicable;		
	$value_is_order_given    = isset($form_state['values']['is_order_given']) ? $form_state['values']['is_order_given'] : $get_all_data[0]->is_order_given;
	
	if(($value_is_law_applicable == "Yes") || ($value_is_order_given == "Yes") || ($value_is_law_applicable == "Yes" && $value_is_order_given == "Yes"))
	{
		$form['notice_accident_injured_details']['state_act_done'] = array(
			'#prefix' 			=> '<div id="state_act_done_id"><div class="col-md-12 col-xs-6"><label class="input label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t("(m). State whether the act was done for the purpose of and in connection with the employer's trade or business"),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			'#default_value' 			=> $get_all_data[0]->state_act_done,
		);
	} else {
		$form['notice_accident_injured_details']['state_act_done'] = array(
			'#prefix' 			=> '<div id="state_act_done_id">',
			'#suffix' 			=> '</div>',
		);
	}
	
	$option_employer_transport = array( "Yes" => "Yes","No" => "No");
	$form['notice_accident_injured_details']['employer_transport'] = array(
		'#prefix' 			=> '<div id="employer_transport_id"><div class="col-md-12 col-xs-6"><label class="input label-block">',
		'#suffix' 			=> '</label></div></div>',
		'#title' 			=> t("(n). Whether the accident happened while travelling in the employer's transport -"),
		'#type' 			=> 'radios',
		'#options'			=> $option_employer_transport,
		'#default_value' 	=> $get_all_data[0]->employer_transport,
		'#ajax' 			=> array(
							'event' 		=> 'change',
							'effect' 		=> 'fade',
							'callback' 		=> 'get_ajax_load',
							'progress' 		=> array(
							'type' 			=> 'throbber',
							'message' 		=> t('loading')
						)
		 )
	);
	
	$value_employer_transport = isset($form_state['values']['employer_transport']) ? $form_state['values']['employer_transport'] : $get_all_data[0]->employer_transport;
	
	if($value_employer_transport == 'Yes')
	{
		$option_is_travelling_for_work = array( "Yes" => "Yes","No" => "No");
		$form['notice_accident_injured_details']['is_travelling_for_work'] = array(
			'#prefix'		 	=> '<div id="is_travelling_for_work_id"><div class="col-md-12 col-xs-12" style="padding-left: 41px;">',
			'#suffix' 			=> '</div></div>',
			'#title' 			=> t('(i). The injured person was travelling as a passenger to or from his place work'),
			'#options'			=> $option_is_travelling_for_work,
			'#type' 			=> 'radios',
			'#default_value' 	=> $get_all_data[0]->is_travelling_for_work,
		);
	
		$option_is_travelling_express_impiled = array( "Yes" => "Yes","No" => "No");
		$form['notice_accident_injured_details']['is_travelling_express_impiled'] = array(
			'#prefix'		 	=> '<div id="is_travelling_express_impiled_id"><div class="col-md-12 col-xs-12" style="padding-left: 41px;">',
			'#suffix' 			=> '</div></div>',
			'#title' 			=> t('(ii). The injured person was travelling with the express or implied permission of his employer'),
			'#options'			=> $option_is_travelling_express_impiled,
			'#type' 			=> 'radios',
			'#default_value' 	=> $get_all_data[0]->is_travelling_express_impiled,
		);
	
		$option_is_transport_provided = array( "Yes" => "Yes","No" => "No");
		$form['notice_accident_injured_details']['is_transport_provided'] = array(
			'#prefix'		 	=> '<div id="is_transport_provided_id"><div class="col-md-12 col-xs-12" style="padding-left: 41px;">',
			'#suffix' 			=> '</div></div>',
			'#title' 			=> t('(iii). The transport is being operated by/on behalf of the employer/some other person by whom it is provided in pursuance of arrangements made with the employer'),
			'#options'			=> $option_is_transport_provided,
			'#type' 			=> 'radios',
			'#default_value' 	=> $get_all_data[0]->is_transport_provided,
		);
	
		$option_is_course_of_transport_provided = array( "Yes" => "Yes","No" => "No");
		$form['notice_accident_injured_details']['is_course_of_transport_provided'] = array(
			'#prefix'		 	=> '<div id="is_course_of_transport_provided_id"><div class="col-md-12 col-xs-12" style="padding-left: 41px;">',
			'#suffix' 			=> '</div></div>',
			'#title' 			=> t('(iv). The vehicle was being/not being operated in the ordinary course of public transport vehicle'),
			'#options'			=> $option_is_course_of_transport_provided,
			'#type' 			=> 'radios',
			'#default_value' 	=> $get_all_data[0]->is_course_of_transport_provided,
		);
	} else {
		$form['notice_accident_injured_details']['is_travelling_for_work'] = array(
			'#prefix'		 	=> '<div id="is_travelling_for_work_id">',
			'#suffix' 			=> '</div>',
		);
		$form['notice_accident_injured_details']['is_travelling_express_impiled'] = array(
			'#prefix'		 	=> '<div id="is_travelling_express_impiled_id">',
			'#suffix' 			=> '</div>',
		);
		$form['notice_accident_injured_details']['is_transport_provided'] = array(
			'#prefix'		 	=> '<div id="is_transport_provided_id">',
			'#suffix' 			=> '</div>',
		);
		$form['notice_accident_injured_details']['is_course_of_transport_provided'] = array(
			'#prefix'		 	=> '<div id="is_course_of_transport_provided_id">',
			'#suffix' 			=> '</div>',
		);
	}

	$option_accident_happened_emergency = array( "Yes" => "Yes","No" => "No");
	$form['notice_accident_injured_details']['accident_happened_emergency'] = array(
		'#prefix' 			=> '<div id="accident_happened_emergency_id"><div class="col-md-12 col-xs-12"><label class="input label-block">',
		'#suffix' 			=> '</label></div></div>',
		'#title' 			=> t("(o). Whether the accident happened while meeting mergency -"),
		'#type' 			=> 'radios',
		'#options'			=> $option_accident_happened_emergency,
		'#default_value' 	=> $get_all_data[0]->accident_happened_emergency,
		'#ajax' 			=> array(
							'event' 		=> 'change',
							'effect' 		=> 'fade',
							'callback' 		=> 'get_ajax_load',
							'progress' 		=> array(
							'type' 			=> 'throbber',
							'message' 		=> t('loading')
						)
		 )
	);
	
	$value_accident_happened_emergency = isset($form_state['values']['accident_happened_emergency']) ? $form_state['values']['accident_happened_emergency'] : $get_all_data[0]->accident_happened_emergency;
	
	if($value_accident_happened_emergency == 'Yes')
	{
		$form['notice_accident_injured_details']['accident'] = array(
			'#prefix' 			=> '<div id="accident_id"><div class="col-md-12 col-xs-12" style="padding-left: 41px;"><label class="input label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t("(i). It's nature"),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			'#default_value' 			=> $get_all_data[0]->accident,
		);
		
		$option_accident_person_employed = array( "Yes" => "Yes","No" => "No");
		$form['notice_accident_injured_details']['accident_person_employed'] = array(
			'#prefix' 			=> '<div id="accident_person_employed_id"><div class="col-md-12 col-xs-12" style="padding-left: 41px;"><label class="input label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#options'			=> $option_accident_person_employed,
			'#title' 			=> t("(ii). If injured person at the time of accident was employed for the purpose of his employer's trade/business in/about the permises at which the accident took place?"),
			'#type' 			=> 'radios',
			'#required' 		=> TRUE,
			'#default_value' 	=> $get_all_data[0]->accident_person_employed,
		);
	} else {
		$form['notice_accident_injured_details']['accident'] = array(
			'#prefix' 			=> '<div id="accident_id">',
			'#suffix' 			=> '</div>',
		);
		$form['notice_accident_injured_details']['accident_person_employed'] = array(
			'#prefix' 			=> '<div id="accident_person_employed_id">',
			'#suffix' 			=> '</div>',
		);
	}

	$form['notice_accident_injured_details']['nature_of_injury'] = array(
		'#prefix' 			=> '<div class="col-md-6 col-xs-12"><label class="input label-block">',
		'#suffix' 			=> '</label><span style="color:red";>e.g. fatal, loss of finger, fracture of leg, scale of scratch and followed by sepsis</span></div>',
		'#title' 			=> t("(p). Nature and extent of injury"),
		'#type' 			=> 'textfield',
		'#required' 		=> TRUE,
		'#value' 			=> $get_all_data[0]->nature_of_injury,
	);
	$form['notice_accident_injured_details']['location_of_injury'] = array(
		'#prefix' 			=> '<div class="col-md-6 col-xs-12"><label class="input label-block">',
		'#suffix' 			=> '</label><span style="color:red";>right leg, left hand or left eye etc.</span></div>',
		'#title' 			=> t("(q). Location of injury"),
		'#type' 			=> 'textfield',
		'#required' 		=> TRUE,
		'#value' 			=> $get_all_data[0]->location_of_injury,
	);
	$form['notice_accident_injured_details']['treatment_location'] = array(
		'#title' 			=> t("(s). Physician, dispensary/hospital from which injured person received treatment"),
		'#prefix' 			=> '<div class="col-md-6 col-xs-12"><label class="input label-block">',
		'#suffix' 			=> '</label></div>',
		'#type' 			=> 'textfield',
		'#required' 		=> TRUE,
		'#value' 			=> $get_all_data[0]->treatment_location,
		'#attributes' 		=> array('class'=>array('form-control'), 'title' => 'Some Description for tooltip'),
	);
	$form['notice_accident_injured_details']['doctor_name'] = array(
		'#prefix' 			=> '<div class="col-md-6 col-xs-12"><label class="input label-block">',
		'#suffix' 			=> '</label></div>',
		'#title' 			=> t("(t). Name of dispensary/panel doctor selected by the injured person"),
		'#type' 			=> 'textfield',
		'#required' 		=> TRUE,
		'#value' 			=> $get_all_data[0]->doctor_name,
	);
	

		$option_fatal_accident = array( "F" => "Fatal", "M" => "Minor", "S" => "Serious");
		$form['notice_accident_injured_details']['fatal_accident'] = array(
			'#prefix'		 	=> '<div id="fatal_accident_id"><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></div>',
			'#title' 			=> t('(r). Type of Accident?'),
			'#options'			=> $option_fatal_accident,
			'#type' 			=> 'radios',
			'#required' 		=> TRUE,
			'#default_value' 	=> $get_all_data[0]->fatal_accident,
			'#ajax' 			=> array(
									'event' 		=> 'change',
									'effect' 		=> 'fade',
									'callback' 		=> 'get_ajax_load',
									'progress' 		=> array(
									'type' 			=> 'throbber',
									'message' 		=> t('loading')
								)
       			 )
		);
		
			$form['notice_accident_injured_details']['is_accident_person_died'] = array(
				'#prefix' 			=> '<div id="is_accident_person_died_id">',
				'#suffix' 			=> '</div>',
			);
			$form['notice_accident_injured_details']['date_of_death'] = array(
				'#prefix' 			=> '<div id="date_of_death_id">',
				'#suffix' 			=> '</div>',
			);
			$form['notice_accident_injured_details']['disabled_48hrs'] = array(
				'#prefix' 			=> '<div id="disabled_48hrs_id">',
				'#suffix' 			=> '</div>',
			);
			$form['notice_accident_injured_details']['return_to_work'] = array(
				'#prefix'		 	=> '<div id="return_to_work_id">',
				'#suffix' 			=> '</div>',
			);
			$form['notice_accident_injured_details']['return_to_work_date'] 	= array(
				'#prefix' 			=> '<div id="return_to_work_date_id">',
				'#suffix' 			=> '</div>',
			);
			$form['notice_accident_injured_details']['return_to_work_time'] 	= array(
				'#prefix' 			=> '<div id="return_to_work_time_id">',
				'#suffix' 			=> '</div>',
			);
			
		$value_fatal_accident = (isset($form_state['values']['fatal_accident'])) ? $form_state['values']['fatal_accident'] : $get_all_data[0]->fatal_accident;
		
		if($value_fatal_accident == 'F')
		{
			$form['notice_accident_injured_details']['date_of_death'] = array(
				'#prefix' 			=> '<div id="date_of_death_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t("(v). Date of Death"),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#default_value' 			=> trim(implode('-', array_reverse(explode('-',$get_all_data[0]->date_of_death)))),
				//'#default_value' 			=> $get_all_data[0]->date_of_death,
				'#attributes' 		=> array('class'=>array('form-control datepicker_retify')),
			);
		} 
		if($value_fatal_accident == 'M' || $value_fatal_accident == 'S')
		{
			$option_is_accident_person_died = array('Yes'=>'Yes', 'No'=>'No');
			$form['notice_accident_injured_details']['is_accident_person_died'] = array(
				'#prefix' 			=> '<div id="is_accident_person_died_id"><div class="col-md-3 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t("(u). Has the injured person died ?"),
				'#type' 			=> 'radios',
				'#required' 		=> TRUE,
				'#options' 			=> $option_is_accident_person_died,
				'#default_value' 	=> $get_all_data[0]->is_accident_person_died,
				'#ajax' 			=> array(
											'event' 		=> 'change',
											'effect' 		=> 'fade',
											'callback' 		=> 'get_ajax_load',
											'progress' 		=> array(
											'type' 			=> 'throbber',
											'message' 		=> t('loading')
										)
						 )
			);
			
			$value_is_accident_person_died = (isset($form_state['values']['is_accident_person_died'])) ? $form_state['values']['is_accident_person_died'] : $get_all_data[0]->is_accident_person_died;
		
			 if($value_is_accident_person_died == 'No')
			 {
				$option_disabled_48hrs = array('Yes'=>'Yes', 'No'=>'No');
				$form['notice_accident_injured_details']['disabled_48hrs'] = array(
					'#prefix'		 	=> '<div id="disabled_48hrs_id"><div class="col-md-5 col-xs-12"><label class="input label-block">',
					'#suffix' 			=> '</label></div></div>',
					'#title' 			=> t('(i). Whether the injured person was disabled for 48 hours or more ?'),
					'#default_value'    => !empty($get_all_data[0]->disabled_48hrs) ? $get_all_data[0]->disabled_48hrs : '',
					'#options'			=> $option_disabled_48hrs,
					'#type' 			=> 'radios',
					'#ajax' 			=> array(
											'event' 		=> 'change',
											'effect' 		=> 'fade',
											'callback' 		=> 'get_ajax_load',
											'progress' 		=> array(
											'type' 			=> 'throbber',
											'message' 		=> t('loading')
										)
						 )
				); 
				
				$value_disabled_48hrs = (isset($form_state['values']['disabled_48hrs'])) ? $form_state['values']['disabled_48hrs'] : $get_all_data[0]->disabled_48hrs;
				if($value_disabled_48hrs == 'Yes')
				{
					$option_return_to_work = array('Yes'=>'Yes', 'No'=>'No');
					$form['notice_accident_injured_details']['return_to_work'] = array(
						'#prefix'		 	=> '<div id="return_to_work_id"><div class="col-md-4 col-xs-12">',
						'#suffix' 			=> '</div></div>',
						'#title' 			=> t('(i). Whether the injured person return to work ?'),
						'#default_value'    => !empty($get_all_data[0]->return_to_work) ? $get_all_data[0]->return_to_work : '',
						'#options'			=> $option_return_to_work,
						'#type' 			=> 'radios',
						'#ajax' 			=> array(
												'event' 		=> 'change',
												'effect' 		=> 'fade',
												'callback' 		=> 'get_ajax_load',
												'progress' 		=> array(
												'type' 			=> 'throbber',
												'message' 		=> t('loading')
											)
							 )
					); 
					$value_option_return_to_work = (isset($form_state['values']['return_to_work'])) ? $form_state['values']['return_to_work'] : $get_all_data[0]->return_to_work;
					if($value_option_return_to_work == 'Yes')
					{
						$form['notice_accident_injured_details']['return_to_work_date'] 	= array(
							'#prefix' 			=> '<div id="return_to_work_date_id"><div class="col-md-3 col-xs-12"><label class="input">',
							'#suffix' 			=> '</label></div></div>',
							'#title'			=>	t('(ii). Date of return to work'),
							'#type' 			=> 'textfield',
							'#default_value'    => !empty($get_all_data[0]->return_to_work_date) ? trim(implode('-', array_reverse(explode('-',$get_all_data[0]->return_to_work_date)))) : '',
							//'#default_value'    => !empty($get_all_data[0]->return_to_work_date) ? $get_all_data[0]->return_to_work_date : '',
							'#required' 		=> TRUE,
							'#attributes' 		=> array('class'=>array('form-control datepicker_retify')),
						);
						$form['notice_accident_injured_details']['return_to_work_time'] 	= array(
							'#prefix' 			=> '<div id="return_to_work_time_id"><div class="col-md-3 col-xs-12"><label class="input">',
							'#suffix' 			=> '</label></div></div>',
							'#title'			=>	t('(iii). Time of return to work'),
							'#type' 			=> 'textfield',
							'#default_value'    => !empty($get_all_data[0]->return_to_work_time) ? $get_all_data[0]->return_to_work_time : '',
							'#required' 		=> TRUE,
							'#attributes' 		=> array('class'=>array('form-control')),
						);
					}
				}
				if($value_disabled_48hrs == 'No')
				{		
					$form['notice_accident_injured_details']['return_to_work_date'] 	= array(
						'#prefix' 			=> '<div id="return_to_work_date_id"><div class="col-md-3 col-xs-12"><label class="input">',
						'#suffix' 			=> '</label></div></div>',
						'#title'			=>	t('(ii). Date of return to work'),
						'#type' 			=> 'textfield',
						'#default_value'    => !empty($get_all_data[0]->return_to_work_date) ? trim(implode('-', array_reverse(explode('-',$get_all_data[0]->return_to_work_date)))) : '',
						//'#default_value'    => !empty($get_all_data[0]->return_to_work_date) ? $get_all_data[0]->return_to_work_date : '',
						'#required' 		=> TRUE,
						'#attributes' 		=> array('class'=>array('form-control datepicker_retify')),
					);
					$form['notice_accident_injured_details']['return_to_work_time'] 	= array(
						'#prefix' 			=> '<div id="return_to_work_time_id"><div class="col-md-3 col-xs-12"><label class="input">',
						'#suffix' 			=> '</label></div></div>',
						'#title'			=>	t('(iii). Time of return to work'),
						'#type' 			=> 'textfield',
						'#default_value'    => !empty($get_all_data[0]->return_to_work_time) ? $get_all_data[0]->return_to_work_time : '',
						'#required' 		=> TRUE,
						'#attributes' 		=> array('class'=>array('form-control')),
					);
				}
			 } 
			 if($value_is_accident_person_died == 'Yes')
			 {
				$form['notice_accident_injured_details']['date_of_death'] = array(
					'#prefix' 			=> '<div id="date_of_death_id"><div class="col-md-3 col-xs-12"><label class="input label-block">',
					'#suffix' 			=> '</label></div></div>',
					'#title' 			=> t("(v). Date of Death"),
					'#type' 			=> 'textfield',
					'#required' 		=> TRUE,
					'#default_value' 			=> trim(implode('-', array_reverse(explode('-',$get_all_data[0]->date_of_death)))),
					//'#default_value' 			=> $get_all_data[0]->date_of_death,
					'#attributes' 		=> array('class'=>array('form-control datepicker_retify')),
				);
			 } 
		}
		
	$form['notice_accident_injured_details']['end'] = array (
		'#prefix' 			=> '',
		'#suffix' 			=> '</div>',
	);

	$form['notice_accident_injured_details_end']['submit'] = array (
		'#attributes' 	=> array('class' => array('btn btn-success pull-right')),
		'#type' 		=> 'submit',
		'#value'		=> 'Save'
	);

	$form['notice_accident_injured_details_end']['back_link'] = array(
		'#markup' => l(t('Back'), 'applicant/form18/accident-details/'.$formid.'/'.$referenceid.'/'.$factorytypeid.'/'.$serviceid, array(
			'html' => TRUE,
			'attributes' => array(
				'class' => array('btn btn-outline-dark pull-left')
			)
		))
	);	
	

	  return $form;
  }
	
 	function form18_injured_person_details_submit($form, &$form_state){
		
		//echo '<pre>'; print_r($form_state); die();
		global $base_root,$base_path,$user,$_SESSION;
		
		$uid 						= $user->uid;
		$val   						= $form_state['input'];
		
		//echo "<pre>"; print_r($val);//die;
		$formid 	  = encryption_decryption_fun('decrypt', $val['formid_hidden']);
		$referenceid  = encryption_decryption_fun('decrypt', $val['referenceid_hidden']);
		$factorytypeid    = encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']);
		$serviceid    = encryption_decryption_fun('decrypt', $val['serviceid_hidden']);
		
		$accident_exist = db_query("SELECT count(*) FROM {fa_form18_injured_person_details} where accident_case_id = '$formid'")->fetchObject()->count;
		
		$injured_person_details = array(
				'accident_case_id' 		 	      => $formid,
				'accident_person_name' 		 	  => $val['accident_person_name'],
				'age' 						 	  => $val['age'],
				'gender' 					 	  => $val['gender'],
				'accident_person_occupation' 	  => $val['accident_person_occupation'],
				'accident_person_address'    	  => $val['accident_person_address'],
				'insurance_number' 			 	  => $val['insurance_number'],
				'local_esi_office' 			 	  => $val['local_esi_office'],
				'work_starting_time' 		 	  => $val['work_starting_time'],
				'wages_payable' 		 	 	  => $val['wages_payable'],
				'accident_person_activity'   	  => $val['accident_person_activity'],
				'is_law_applicable'   	  		  => $val['is_law_applicable'],
  				'is_order_given'   	              => $val['is_order_given'],
				'state_act_done' 			 	  => $val['state_act_done'],
				'employer_transport'   	          => $val['employer_transport'],
				'is_travelling_for_work' 	 	  => $val['is_travelling_for_work'],
				'is_travelling_express_impiled'   => $val['is_travelling_express_impiled'],
				'is_transport_provided' 		  => $val['is_transport_provided'],
				'is_course_of_transport_provided' => $val['is_course_of_transport_provided'],
				'accident_happened_emergency'     => $val['accident_happened_emergency'],
				'accident' 						  => $val['accident'],
				'accident_person_employed' 		  => $val['accident_person_employed'],
				'nature_of_injury' 				  => $val['nature_of_injury'],
				'location_of_injury' 			  => $val['location_of_injury'],
				'fatal_accident' 				  => $val['fatal_accident'],
				'disabled_48hrs' 				  => $val['disabled_48hrs'],
				'return_to_work'   	              => $val['return_to_work'],
				//'return_to_work_date'             => !empty($val['return_to_work_date']) ? trim(implode('-', array_reverse(explode('-',$val['return_to_work_date'])))) : '',
				'return_to_work_date' 			  => $val['return_to_work_date'],
				'return_to_work_time' 			  => $val['return_to_work_time'],
				'treatment_location' 			  => $val['treatment_location'],
				'doctor_name' 					  => $val['doctor_name'],
				'is_accident_person_died' 		  => $val['is_accident_person_died'],
				'date_of_death' 				  => $val['date_of_death'],
				//'date_of_death' 				  => !empty($val['date_of_death']) ? trim(implode('-', array_reverse(explode('-',$val['date_of_death'])))) : '',
			);
			
			//echo '<pre>'.print_r($injured_person_details);//die;
		if($accident_exist!=0)
		{
			$query_injured 	=	db_update('fa_form18_injured_person_details');
			$query_injured	->	fields($injured_person_details);
			$query_injured	->	condition('accident_case_id',$formid,'=');
			$query_injured	->	execute();
			
		} else {
			db_insert('fa_form18_injured_person_details')->fields($injured_person_details)->execute();
		}
		// UPDATE ACCIDENT DETAILS TABLE
			$query_notice 	=	db_update('fa_form18_notice_accident');
			$query_notice	->	fields(array('accident_type'=> $val['fatal_accident']));
			$query_notice	->	condition('id',$formid,'=');
			$query_notice	->	execute();
		
		drupal_goto('applicant/form18/witness-details/'.$val['formid_hidden'].'/'.$val['referenceid_hidden'].'/'.$val['factorytypeid_hidden'].'/'.$val['serviceid_hidden']);
		
		$form_state['rebuild'] = true;
	} 

	function get_ajax_load($form, $form_state)
	{
		$commands[] = ajax_command_replace('#disabled_48hrs_id', drupal_render($form['notice_accident_injured_details']['disabled_48hrs']));
		$commands[] = ajax_command_replace('#return_to_work_time_id', drupal_render($form['notice_accident_injured_details']['return_to_work_time']));
		$commands[] = ajax_command_replace('#return_to_work_date_id', drupal_render($form['notice_accident_injured_details']['return_to_work_date']));
		$commands[] = ajax_command_replace('#date_of_death_id', drupal_render($form['notice_accident_injured_details']['date_of_death']));
		$commands[] = ajax_command_replace('#is_law_applicable_id', drupal_render($form['notice_accident_injured_details']['is_law_applicable']));
		$commands[] = ajax_command_replace('#is_order_given_id', drupal_render($form['notice_accident_injured_details']['is_order_given']));
		$commands[] = ajax_command_replace('#state_act_done_id', drupal_render($form['notice_accident_injured_details']['state_act_done']));
		$commands[] = ajax_command_replace('#employer_transport_id', drupal_render($form['notice_accident_injured_details']['employer_transport']));
		$commands[] = ajax_command_replace('#is_travelling_for_work_id', drupal_render($form['notice_accident_injured_details']['is_travelling_for_work']));
		$commands[] = ajax_command_replace('#is_travelling_express_impiled_id', drupal_render($form['notice_accident_injured_details']['is_travelling_express_impiled']));
		$commands[] = ajax_command_replace('#is_transport_provided_id', drupal_render($form['notice_accident_injured_details']['is_transport_provided']));
		$commands[] = ajax_command_replace('#is_course_of_transport_provided_id', drupal_render($form['notice_accident_injured_details']['is_course_of_transport_provided']));
		$commands[] = ajax_command_replace('#accident_happened_emergency_id', drupal_render($form['notice_accident_injured_details']['accident_happened_emergency']));
		$commands[] = ajax_command_replace('#accident_id', drupal_render($form['notice_accident_injured_details']['accident']));
		$commands[] = ajax_command_replace('#accident_person_employed_id', drupal_render($form['notice_accident_injured_details']['accident_person_employed']));
		$commands[] = ajax_command_replace('#fatal_accident_id', drupal_render($form['notice_accident_injured_details']['fatal_accident']));
		//$commands[] = ajax_command_replace('#treatment_location_id', drupal_render($form['notice_accident_injured_details']['treatment_location']));
		$commands[] = ajax_command_replace('#doctor_name_id', drupal_render($form['notice_accident_injured_details']['doctor_name']));
		$commands[] = ajax_command_replace('#is_accident_person_died_id', drupal_render($form['notice_accident_injured_details']['is_accident_person_died']));
		$commands[] = ajax_command_replace('#return_to_work_id', drupal_render($form['notice_accident_injured_details']['return_to_work']));
		
		return array(
			'#type' => 'ajax',
			'#commands' => $commands
		);
	} 
