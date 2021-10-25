<?php

	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	function inspection_report_workers_details($form, &$form_state, $inspection_reportID = '', $factoryID = '', $param = '') {
	
		global $user;
		$uid = $user->uid;
		
		$inspection_report_id = encryption_decryption_fun('decrypt', $inspection_reportID);
		//$factory_type_id = encryption_decryption_fun('decrypt', $factory_typeID);
		$factory_id = encryption_decryption_fun('decrypt', $factoryID);
		
		if(empty($inspection_report_id) || $inspection_report_id == '') {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Factory Information first.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('admin/inspection-report-factories/default/'.$inspection_reportID.'/'.$factoryID.'/'.encryption_decryption_fun('encrypt', NULL)) ;
		}
		
		$get_total_no_workers = get_total_no_workers($inspection_report_id);
		$get_max_no_workers = get_max_no_workers_last_twelve_months($inspection_report_id);
		
		$form = array();
		
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
		
		$form['tot_no_of_workers'] = array(
			'#type' 		=> 'fieldset',
			'#title' 		=> t('C. Total number of workers employed'),
			'#collapsible' 	=> TRUE, // Added
			'#collapsed' 	=> FALSE // Added
		);
		
		$form['tot_no_of_workers']['tot_no_workers_previous_table'] 	= array(
				
			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row">
								<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
								
								<table class="custom-table-view-dashboard renewal-table">
									<tr>
										<th width="" rowspan="2" valign="top"></th>
										<th width="" colspan="2" valign="middle">Total Number of Workers</th>
										<th width="" rowspan="2" valign="middle">Nature of Work</th>
										<th width="" rowspan="2" valign="middle">Service since When</th>
										<th width="" rowspan="2" valign="middle">Whether of seasonal nature<br>(Yes/No)</th>
									</tr>
									<tr>
										<th width="" valign="middle" align="center">Male</th>
										<th width="" valign="middle" align="center">Female</th>
									</tr>
							'
		);
		
	//Permanent Workers
	
		$form['tot_no_of_workers']['per_workers'] = array(
					'#prefix' 			=> '<tr><td><div class="col-xs-12"><b>Permanent Workers</b>',
					'#suffix' 	 		=> '</div></td>',
		);
		$form['tot_no_of_workers']['per_workers_male'] = array(
				 '#prefix' 				=> '<td><div class="col-xs-12">',
				 '#suffix' 	 			=> '</div></td>',
				 '#title'				=>	t('Permanent Workers Male'),
				 '#type' 				=> 'textfield',
				 '#default_value'		=> !empty($get_total_no_workers->per_workers_male) ? $get_total_no_workers->per_workers_male : '',
				 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'per_workers_male_id'),
				 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				 '#required' 			=> TRUE,
				 '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['per_workers_female'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Permanent Workers Female'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->per_workers_female) ? $get_total_no_workers->per_workers_female : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'per_workers_female_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['per_workers_nature_of_work'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Permanent Workers Nature of Work'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->per_workers_nature_of_work) ? $get_total_no_workers->per_workers_nature_of_work : '',
				  '#attributes' 		=> array('class'=>array('form-control'), 'id'=>'per_workers_nature_of_work_id'),
				  '#element_validate'	=> array('element_validate_alphabatic_text'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		
		$formated_per_workers_service_since = trim(implode('-', array_reverse(explode('-', $get_total_no_workers->per_workers_service_since))));
		$form['tot_no_of_workers']['per_workers_service_since'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Permanent Workers Service since When'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($formated_per_workers_service_since) ? $formated_per_workers_service_since : '',
				  '#attributes' 		=> array('class'=>array('form-control form-control datepicker_retify'), 'id'=>'per_workers_service_since_work_id'),
				  '#element_validate'	=> array('element_validate_date'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['per_workers_seasonal_nature'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td></tr>',
				  '#title'				=>	t('Permanent Workers Whether of seasonal nature'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->per_workers_seasonal_nature) ? $get_total_no_workers->per_workers_seasonal_nature : '',
				  '#attributes' 		=> array('class'=>array('form-control'), 'id'=>'per_workers_seasonal_nature_id'),
				  '#element_validate'	=> array('element_validate_alphabatic_text'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		
	//end
		
	//Staff
	
		$form['tot_no_of_workers']['staff'] = array(
					'#prefix' 			=> '<tr><td><div class="col-xs-12"><b>Staff</b>',
					'#suffix' 	 		=> '</div></td>',
		);
		$form['tot_no_of_workers']['staff_male'] = array(
				'#prefix' 				=> '<td><div class="col-xs-12">',
				'#suffix' 	 			=> '</div></td>',
				'#title'				=>	t('Staff Male'),
				'#type' 				=> 'textfield',
				'#default_value'		=> !empty($get_total_no_workers->staff_male) ? $get_total_no_workers->staff_male : '',
				'#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'staff_male_id'),
				'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				'#required' 			=> TRUE,
				'#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['staff_female'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Staff Female'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->staff_female) ? $get_total_no_workers->staff_female : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'staff_female_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['staff_nature_of_work'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Staff Nature of Work'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->staff_nature_of_work) ? $get_total_no_workers->staff_nature_of_work : '',
				  '#attributes' 		=> array('class'=>array('form-control'), 'id'=>'staff_nature_of_work_id'),
				  '#element_validate'	=> array('element_validate_alphabatic_text'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		
		$formated_staff_service_since = trim(implode('-', array_reverse(explode('-', $get_total_no_workers->staff_service_since))));
		$form['tot_no_of_workers']['staff_service_since'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Staff Service since When'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($formated_staff_service_since) ? $formated_staff_service_since : '',
				  '#attributes' 		=> array('class'=>array('form-control form-control datepicker_retify'), 'id'=>'staff_service_since_work_id'),
				  '#element_validate'	=> array('element_validate_date'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['staff_seasonal_nature'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td></tr>',
				  '#title'				=>	t('Staff Whether of seasonal nature'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->staff_seasonal_nature) ? $get_total_no_workers->staff_seasonal_nature : '',
				  '#attributes' 		=> array('class'=>array('form-control'), 'id'=>'staff_seasonal_nature_id'),
				  '#element_validate'	=> array('element_validate_alphabatic_text'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		
	//end
	
	//Contract Workers
	
		$form['tot_no_of_workers']['con_workers'] = array(
					'#prefix' 			=> '<tr><td><div class="col-xs-12"><b>Contract Workers</b>',
					'#suffix' 	 		=> '</div></td>',
		);
		$form['tot_no_of_workers']['con_workers_male'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Contract Workers Male'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_total_no_workers->con_workers_male) ? $get_total_no_workers->con_workers_male : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'con_workers_male_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['con_workers_female'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Contract Workers Female'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->con_workers_female) ? $get_total_no_workers->con_workers_female : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'con_workers_female_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['con_workers_nature_of_work'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Contract Workers Nature of Work'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->con_workers_nature_of_work) ? $get_total_no_workers->con_workers_nature_of_work : '',
				  '#attributes' 		=> array('class'=>array('form-control'), 'id'=>'con_workers_nature_of_work_id'),
				  '#element_validate'	=> array('element_validate_alphabatic_text'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		
		$formated_con_workers_service_since = trim(implode('-', array_reverse(explode('-', $get_total_no_workers->con_workers_service_since))));
		$form['tot_no_of_workers']['con_workers_service_since'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Contract Workers Service since When'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($formated_con_workers_service_since) ? $formated_con_workers_service_since : '',
				  '#attributes' 		=> array('class'=>array('form-control form-control datepicker_retify'), 'id'=>'con_workers_service_since_work_id'),
				  '#element_validate'	=> array('element_validate_date'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['con_workers_seasonal_nature'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td></tr>',
				  '#title'				=>	t('Contract Workers Whether of seasonal nature'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->con_workers_seasonal_nature) ? $get_total_no_workers->con_workers_seasonal_nature : '',
				  '#attributes' 		=> array('class'=>array('form-control'), 'id'=>'con_workers_seasonal_nature_id'),
				  '#element_validate'	=> array('element_validate_alphabatic_text'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		
	//end
	
	//Daily Wages
	
		$form['tot_no_of_workers']['daily_wages'] = array(
					'#prefix' 			=> '<tr><td><div class="col-xs-12"><b>Daily Wages</b>',
					'#suffix' 	 		=> '</div></td>',
		);
		$form['tot_no_of_workers']['daily_wages_male'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Daily Wages Male'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_total_no_workers->daily_wages_male) ? $get_total_no_workers->daily_wages_male : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'daily_wages_male_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['daily_wages_female'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Daily Wages Female'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->daily_wages_female) ? $get_total_no_workers->daily_wages_female : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'daily_wages_female_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['daily_wages_nature_of_work'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Daily Wages Nature of Work'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->daily_wages_nature_of_work) ? $get_total_no_workers->daily_wages_nature_of_work : '',
				  '#attributes' 		=> array('class'=>array('form-control'), 'id'=>'daily_wages_nature_of_work_id'),
				  '#element_validate'	=> array('element_validate_alphabatic_text'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		
		$formated_daily_wages_service_since = trim(implode('-', array_reverse(explode('-', $get_total_no_workers->daily_wages_service_since))));
		$form['tot_no_of_workers']['daily_wages_service_since'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Daily Wages Service since When'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($formated_daily_wages_service_since) ? $formated_daily_wages_service_since : '',
				  '#attributes' 		=> array('class'=>array('form-control form-control datepicker_retify'), 'id'=>'daily_wages_service_since_work_id'),
				  '#element_validate'	=> array('element_validate_date'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['daily_wages_seasonal_nature'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td></tr>',
				  '#title'				=>	t('Daily Wages Whether of seasonal nature'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->daily_wages_seasonal_nature) ? $get_total_no_workers->daily_wages_seasonal_nature : '',
				  '#attributes' 		=> array('class'=>array('form-control'), 'id'=>'daily_wages_seasonal_nature_id'),
				  '#element_validate'	=> array('element_validate_alphabatic_text'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		
	//end
	
	//Temporary
	
		$form['tot_no_of_workers']['temporary'] = array(
					'#prefix' 			=> '<tr><td><div class="col-xs-12"><b>Temporary</b>',
					'#suffix' 	 		=> '</div></td>',
		);
		$form['tot_no_of_workers']['temporary_male'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Temporary Male'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_total_no_workers->temporary_male) ? $get_total_no_workers->temporary_male : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'temporary_male_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['temporary_female'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Temporary Female'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->temporary_female) ? $get_total_no_workers->temporary_female : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'temporary_female_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['temporary_nature_of_work'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Temporary Nature of Work'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->temporary_nature_of_work) ? $get_total_no_workers->temporary_nature_of_work : '',
				  '#attributes' 		=> array('class'=>array('form-control'), 'id'=>'temporary_nature_of_work_id'),
				  '#element_validate'	=> array('element_validate_alphabatic_text'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		
		$formated_temporary_service_since = trim(implode('-', array_reverse(explode('-', $get_total_no_workers->temporary_service_since))));
		$form['tot_no_of_workers']['temporary_service_since'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Temporary Service since When'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($formated_temporary_service_since) ? $formated_temporary_service_since : '',
				  '#attributes' 		=> array('class'=>array('form-control form-control datepicker_retify'), 'id'=>'temporary_service_since_work_id'),
				  '#element_validate'	=> array('element_validate_date'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['temporary_seasonal_nature'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td></tr>',
				  '#title'				=>	t('Temporary Whether of seasonal nature'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->temporary_seasonal_nature) ? $get_total_no_workers->temporary_seasonal_nature : '',
				  '#attributes' 		=> array('class'=>array('form-control'), 'id'=>'temporary_seasonal_nature_id'),
				  '#element_validate'	=> array('element_validate_alphabatic_text'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		
	//end
	
	//Watchman/Security
	
		$form['tot_no_of_workers']['security'] = array(
					'#prefix' 			=> '<tr><td><div class="col-xs-12"><b>Watchman/Security</b>',
					'#suffix' 	 		=> '</div></td>',
		);
		$form['tot_no_of_workers']['security_male'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Watchman/Security Male'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_total_no_workers->security_male) ? $get_total_no_workers->security_male : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'security_male_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['security_female'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Watchman/Security Female'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->security_female) ? $get_total_no_workers->security_female : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'security_female_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['security_nature_of_work'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Watchman/Security Nature of Work'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->security_nature_of_work) ? $get_total_no_workers->security_nature_of_work : '',
				  '#attributes' 		=> array('class'=>array('form-control'), 'id'=>'security_nature_of_work_id'),
				  '#element_validate'	=> array('element_validate_alphabatic_text'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		
		$formated_security_service_since = trim(implode('-', array_reverse(explode('-', $get_total_no_workers->security_service_since))));
		$form['tot_no_of_workers']['security_service_since'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Watchman/Security Service since When'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($formated_security_service_since) ? $formated_security_service_since : '',
				  '#attributes' 		=> array('class'=>array('form-control form-control datepicker_retify'), 'id'=>'security_service_since_work_id'),
				  '#element_validate'	=> array('element_validate_date'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['security_seasonal_nature'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td></tr>',
				  '#title'				=>	t('Watchman/Security Whether of seasonal nature'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->security_seasonal_nature) ? $get_total_no_workers->security_seasonal_nature : '',
				  '#attributes' 		=> array('class'=>array('form-control'), 'id'=>'security_seasonal_nature_id'),
				  '#element_validate'	=> array('element_validate_alphabatic_text'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		
	//end
	
	//Apprentice/Trainee
	
		$form['tot_no_of_workers']['trainee'] = array(
					'#prefix' 			=> '<tr><td><div class="col-xs-12"><b>Apprentice/Trainee</b>',
					'#suffix' 	 		=> '</div></td>',
		);
		$form['tot_no_of_workers']['trainee_male'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Apprentice/Trainee Male'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_total_no_workers->trainee_male) ? $get_total_no_workers->trainee_male : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'trainee_male_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['trainee_female'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Apprentice/Trainee Female'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->trainee_female) ? $get_total_no_workers->trainee_female : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'trainee_female_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['trainee_nature_of_work'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Apprentice/Trainee Nature of Work'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->trainee_nature_of_work) ? $get_total_no_workers->trainee_nature_of_work : '',
				  '#attributes' 		=> array('class'=>array('form-control'), 'id'=>'trainee_nature_of_work_id'),
				  '#element_validate'	=> array('element_validate_alphabatic_text'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		
		$formated_trainee_service_since = trim(implode('-', array_reverse(explode('-', $get_total_no_workers->trainee_service_since))));
		$form['tot_no_of_workers']['trainee_service_since'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Apprentice/Trainee Service since When'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($formated_trainee_service_since) ? $formated_trainee_service_since : '',
				  '#attributes' 		=> array('class'=>array('form-control form-control datepicker_retify'), 'id'=>'trainee_service_since_work_id'),
				  '#element_validate'	=> array('element_validate_date'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['trainee_seasonal_nature'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td></tr>',
				  '#title'				=>	t('Apprentice/Trainee Whether of seasonal nature'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->trainee_seasonal_nature) ? $get_total_no_workers->trainee_seasonal_nature : '',
				  '#attributes' 		=> array('class'=>array('form-control'), 'id'=>'trainee_seasonal_nature_id'),
				  '#element_validate'	=> array('element_validate_alphabatic_text'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		
	//end
	
	//Adolescent
	
		$form['tot_no_of_workers']['adolescent'] = array(
					'#prefix' 			=> '<tr><td><div class="col-xs-12"><b>Adolescent</b>',
					'#suffix' 	 		=> '</div></td>',
		);
		$form['tot_no_of_workers']['adolescent_male'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Adolescent Male'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_total_no_workers->adolescent_male) ? $get_total_no_workers->adolescent_male : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'adolescent_male_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['adolescent_female'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Adolescent Female'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->adolescent_female) ? $get_total_no_workers->adolescent_female : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'adolescent_female_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['adolescent_nature_of_work'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Adolescent Nature of Work'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->adolescent_nature_of_work) ? $get_total_no_workers->adolescent_nature_of_work : '',
				  '#attributes' 		=> array('class'=>array('form-control'), 'id'=>'adolescent_nature_of_work_id'),
				  '#element_validate'	=> array('element_validate_alphabatic_text'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		
		$formated_adolescent_service_since = trim(implode('-', array_reverse(explode('-', $get_total_no_workers->adolescent_service_since))));
		$form['tot_no_of_workers']['adolescent_service_since'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Adolescent Service since When'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($formated_adolescent_service_since) ? $formated_adolescent_service_since : '',
				  '#attributes' 		=> array('class'=>array('form-control form-control datepicker_retify'), 'id'=>'adolescent_service_since_work_id'),
				  '#element_validate'	=> array('element_validate_date'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['adolescent_seasonal_nature'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td></tr>',
				  '#title'				=>	t('Adolescent Whether of seasonal nature'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->adolescent_seasonal_nature) ? $get_total_no_workers->adolescent_seasonal_nature : '',
				  '#attributes' 		=> array('class'=>array('form-control'), 'id'=>'adolescent_seasonal_nature_id'),
				  '#element_validate'	=> array('element_validate_alphabatic_text'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		
	//end
	
		$form['tot_no_of_workers']['total'] = array(
					'#prefix' 			=> '<tr><td><div class="col-xs-12"><b>Total</b>',
					'#suffix' 	 		=> '</div></td>',
		);
		$form['tot_no_of_workers']['total_male'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Total Male'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_total_no_workers->total_male) ? $get_total_no_workers->total_male : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'tot_no_workers_total_male_id','readonly' => 'readonly'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['total_female'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Adolescent Female'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($get_total_no_workers->total_female) ? $get_total_no_workers->total_female : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'tot_no_workers_total_female_id','readonly' => 'readonly'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				  '#title_display' 		=> 'invisible',
		);
		$form['tot_no_of_workers']['total_nature_of_work'] = array(
					'#prefix' 			=> '<td><div class="col-xs-12">',
					'#suffix' 	 		=> '</div></td>',
		);
		$form['tot_no_of_workers']['total_service_since'] = array(
					'#prefix' 			=> '<td><div class="col-xs-12">',
					'#suffix' 	 		=> '</div></td>',
		);
		$form['tot_no_of_workers']['total_seasonal_nature'] = array(
					'#prefix' 			=> '<td><div class="col-xs-12">',
					'#suffix' 	 		=> '</div></td></tr>',
		);
		
		$form['tot_no_of_workers']['tot_no_workers_previous_table_end'] 	= array(
			'#suffix' => '
								</table>
								</div>
							</div>',
			'#type'	  => 'markup',
			'#markup' => '',	
		);
		
		
		
		$form['max_no_workers_emp_last_twelve'] = array(
			'#type' 		=> 'fieldset',
			'#title' 		=> t('D. Maximum no. of workers employed during last twelve months'),
			'#collapsible' 	=> TRUE, // Added
			'#collapsed' 	=> FALSE // Added
		);
		
		$form['max_no_workers_emp_last_twelve']['max_no_workers_emp_previous_table'] 	= array(
				
			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row">
								<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
								
								<table class="custom-table-view-dashboard renewal-table">
							'
		);

	//Male
			
		$form['max_no_workers_emp_last_twelve']['male'] = array(
					'#prefix' 			=> '<tr><td><div class="col-xs-12"><b>Male</b>',
					'#suffix' 	 		=> '</div></td>',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_male_month_one'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Male Month 1'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_male_month_one) ? $get_max_no_workers->max_no_workers_male_month_one : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_male_month_one_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_male_month_two'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Male Month 2'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_male_month_two) ? $get_max_no_workers->max_no_workers_male_month_two : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_male_month_two_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_male_month_three'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Male Month 3'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_male_month_three) ? $get_max_no_workers->max_no_workers_male_month_three : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_male_month_three_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_male_month_four'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Male Month 4'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_male_month_four) ? $get_max_no_workers->max_no_workers_male_month_four : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_male_month_four_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_male_month_five'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Male Month 5'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_male_month_five) ? $get_max_no_workers->max_no_workers_male_month_five : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_male_month_five_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_male_month_six'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Male Month 6'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_male_month_six) ? $get_max_no_workers->max_no_workers_male_month_six : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_male_month_six_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_male_month_seven'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Male Month 7'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_male_month_seven) ? $get_max_no_workers->max_no_workers_male_month_seven : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_male_month_seven_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_male_month_eight'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Male Month 8'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_male_month_eight) ? $get_max_no_workers->max_no_workers_male_month_eight : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_male_month_eight_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_male_month_nine'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Male Month 9'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_male_month_nine) ? $get_max_no_workers->max_no_workers_male_month_nine : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_male_month_nine_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_male_month_ten'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Male Month 10'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_male_month_ten) ? $get_max_no_workers->max_no_workers_male_month_ten : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_male_month_ten_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_male_month_eleven'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Male Month 11'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_male_month_eleven) ? $get_max_no_workers->max_no_workers_male_month_eleven : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_male_month_eleven_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_male_month_twelve'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Male Month 12'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_male_month_twelve) ? $get_max_no_workers->max_no_workers_male_month_twelve : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_male_month_twelve_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		
	//End
		
	//Female
	
		$form['max_no_workers_emp_last_twelve']['female'] = array(
					'#prefix' 			=> '<tr><td><div class="col-xs-12"><b>Female</b>',
					'#suffix' 	 		=> '</div></td>',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_female_month_one'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Female Month 1'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_female_month_one) ? $get_max_no_workers->max_no_workers_female_month_one : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_female_month_one_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_female_month_two'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Female Month 2'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_female_month_two) ? $get_max_no_workers->max_no_workers_female_month_two : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_female_month_two_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_female_month_three'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Female Month 3'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_female_month_three) ? $get_max_no_workers->max_no_workers_female_month_three : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_female_month_three_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_female_month_four'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Female Month 4'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_female_month_four) ? $get_max_no_workers->max_no_workers_female_month_four : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_female_month_four_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_female_month_five'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Female Month 5'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_female_month_five) ? $get_max_no_workers->max_no_workers_female_month_five : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_female_month_five_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_female_month_six'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Female Month 6'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_female_month_six) ? $get_max_no_workers->max_no_workers_female_month_six : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_female_month_six_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_female_month_seven'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Female Month 7'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_female_month_seven) ? $get_max_no_workers->max_no_workers_female_month_seven : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_female_month_seven_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_female_month_eight'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Female Month 8'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_female_month_eight) ? $get_max_no_workers->max_no_workers_female_month_eight : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_female_month_eight_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_female_month_nine'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Female Month 9'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_female_month_nine) ? $get_max_no_workers->max_no_workers_female_month_nine : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_female_month_nine_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_female_month_ten'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Female Month 10'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_female_month_ten) ? $get_max_no_workers->max_no_workers_female_month_ten : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_female_month_ten_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_female_month_eleven'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Female Month 11'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_female_month_eleven) ? $get_max_no_workers->max_no_workers_female_month_eleven : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_female_month_eleven_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		$form['max_no_workers_emp_last_twelve']['max_no_workers_female_month_twelve'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Female Month 12'),
					 '#type' 				=> 'textfield',
					 '#default_value'		=> !empty($get_max_no_workers->max_no_workers_female_month_twelve) ? $get_max_no_workers->max_no_workers_female_month_twelve : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'max_no_workers_female_month_twelve_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
					 '#title_display' 		=> 'invisible',
		);
		
	//End
		
		$form['max_no_workers_emp_last_twelve']['max_no_workers_emp_previous_table_end'] 	= array(
			'#suffix' => '
								</table>
								</div>
							</div>',
			'#type'	  => 'markup',
			'#markup' => '',	
		);
		
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'admin/inspection-report-factories/default/'.$inspection_reportID.'/'.$factoryID.'/'.encryption_decryption_fun('encrypt', NULL), array(
				'html' => TRUE,
				'attributes' => array('class' => array('btn btn-outline-dark pull-left'))
			))
		);
		
		$form['factory_information_submit']['submit'] = array (
			'#prefix' 		=> '',  
			'#suffix' 		=> '',
			'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
			'#type' 		=> 'submit',
			'#value'		=> 'Save & Continue'
		);
		
		return $form;
	}
	
	
	function inspection_report_workers_details_validate($form, &$form_state) {
		
		
	}
	
	
	function inspection_report_workers_details_submit($form, &$form_state){
		//echo '<pre>'; print_r($form_state); die();
		
		global $base_root,$base_path,$user;
		
		$uid 							= $user->uid;
		
		$inspection_report_id = $form_state['values']['inspection_report_id'];
		
		$factory_id = $form_state['values']['factory_id'];
		
		$val = $form_state['values'];
		
	//total no workers
		$get_total_no_workers = get_total_no_workers($inspection_report_id);
		if($get_total_no_workers != NULL && count($get_total_no_workers) > 0) {
			
			$total_no_workers = array(
				'inspection_report_id' => $val['inspection_report_id'],
				
				'per_workers_male' => $val['per_workers_male'],
				'per_workers_female' => $val['per_workers_female'],
				'per_workers_nature_of_work' => $val['per_workers_nature_of_work'],
				'per_workers_service_since' => trim(implode('-', array_reverse(explode('-', $val['per_workers_service_since'])))),
				'per_workers_seasonal_nature' => $val['per_workers_seasonal_nature'],
				
				'staff_male' => $val['staff_male'],
				'staff_female' => $val['staff_female'],
				'staff_nature_of_work' => $val['staff_nature_of_work'],
				'staff_service_since' => trim(implode('-', array_reverse(explode('-', $val['staff_service_since'])))),
				'staff_seasonal_nature' => $val['staff_seasonal_nature'],
				
				'con_workers_male' => $val['con_workers_male'],
				'con_workers_female' => $val['con_workers_female'],
				'con_workers_nature_of_work' => $val['con_workers_nature_of_work'],
				'con_workers_service_since' => trim(implode('-', array_reverse(explode('-', $val['con_workers_service_since'])))),
				'con_workers_seasonal_nature' => $val['con_workers_seasonal_nature'],
				
				'daily_wages_male' => $val['daily_wages_male'],
				'daily_wages_female' => $val['daily_wages_female'],
				'daily_wages_nature_of_work' => $val['daily_wages_nature_of_work'],
				'daily_wages_service_since' => trim(implode('-', array_reverse(explode('-', $val['daily_wages_service_since'])))),
				'daily_wages_seasonal_nature' => $val['daily_wages_seasonal_nature'],
				
				'temporary_male' => $val['temporary_male'],
				'temporary_female' => $val['temporary_female'],
				'temporary_nature_of_work' => $val['temporary_nature_of_work'],
				'temporary_service_since' => trim(implode('-', array_reverse(explode('-', $val['temporary_service_since'])))),
				'temporary_seasonal_nature' => $val['temporary_seasonal_nature'],
				
				'security_male' => $val['security_male'],
				'security_female' => $val['security_female'],
				'security_nature_of_work' => $val['security_nature_of_work'],
				'security_service_since' => trim(implode('-', array_reverse(explode('-', $val['security_service_since'])))),
				'security_seasonal_nature' => $val['security_seasonal_nature'],
				
				'trainee_male' => $val['trainee_male'],
				'trainee_female' => $val['trainee_female'],
				'trainee_nature_of_work' => $val['trainee_nature_of_work'],
				'trainee_service_since' => trim(implode('-', array_reverse(explode('-', $val['trainee_service_since'])))),
				'trainee_seasonal_nature' => $val['trainee_seasonal_nature'],
				
				'adolescent_male' => $val['adolescent_male'],
				'adolescent_female' => $val['adolescent_female'],
				'adolescent_nature_of_work' => $val['adolescent_nature_of_work'],
				'adolescent_service_since' => trim(implode('-', array_reverse(explode('-', $val['adolescent_service_since'])))),
				'adolescent_seasonal_nature' => $val['adolescent_seasonal_nature'],
				
				'total_male' => $val['total_male'],
				'total_female' => $val['total_female'],
								
				'uid' => $uid,
				'modification_date'	   => date('Y-m-d H:i:s'),
			);
			db_update('fa_ir_total_no_workers')->fields($total_no_workers)->condition('inspection_report_id', $inspection_report_id, '=')->execute();
				
		} else {
			
			$total_no_workers = array(
				'inspection_report_id' => $val['inspection_report_id'],
				
				'per_workers_male' => $val['per_workers_male'],
				'per_workers_female' => $val['per_workers_female'],
				'per_workers_nature_of_work' => $val['per_workers_nature_of_work'],
				'per_workers_service_since' => trim(implode('-', array_reverse(explode('-', $val['per_workers_service_since'])))),
				'per_workers_seasonal_nature' => $val['per_workers_seasonal_nature'],
				
				'staff_male' => $val['staff_male'],
				'staff_female' => $val['staff_female'],
				'staff_nature_of_work' => $val['staff_nature_of_work'],
				'staff_service_since' => trim(implode('-', array_reverse(explode('-', $val['staff_service_since'])))),
				'staff_seasonal_nature' => $val['staff_seasonal_nature'],
				
				'con_workers_male' => $val['con_workers_male'],
				'con_workers_female' => $val['con_workers_female'],
				'con_workers_nature_of_work' => $val['con_workers_nature_of_work'],
				'con_workers_service_since' => trim(implode('-', array_reverse(explode('-', $val['con_workers_service_since'])))),
				'con_workers_seasonal_nature' => $val['con_workers_seasonal_nature'],
				
				'daily_wages_male' => $val['daily_wages_male'],
				'daily_wages_female' => $val['daily_wages_female'],
				'daily_wages_nature_of_work' => $val['daily_wages_nature_of_work'],
				'daily_wages_service_since' => trim(implode('-', array_reverse(explode('-', $val['daily_wages_service_since'])))),
				'daily_wages_seasonal_nature' => $val['daily_wages_seasonal_nature'],
				
				'temporary_male' => $val['temporary_male'],
				'temporary_female' => $val['temporary_female'],
				'temporary_nature_of_work' => $val['temporary_nature_of_work'],
				'temporary_service_since' => trim(implode('-', array_reverse(explode('-', $val['temporary_service_since'])))),
				'temporary_seasonal_nature' => $val['temporary_seasonal_nature'],
				
				'security_male' => $val['security_male'],
				'security_female' => $val['security_female'],
				'security_nature_of_work' => $val['security_nature_of_work'],
				'security_service_since' => trim(implode('-', array_reverse(explode('-', $val['security_service_since'])))),
				'security_seasonal_nature' => $val['security_seasonal_nature'],
				
				'trainee_male' => $val['trainee_male'],
				'trainee_female' => $val['trainee_female'],
				'trainee_nature_of_work' => $val['trainee_nature_of_work'],
				'trainee_service_since' => trim(implode('-', array_reverse(explode('-', $val['trainee_service_since'])))),
				'trainee_seasonal_nature' => $val['trainee_seasonal_nature'],
				
				'adolescent_male' => $val['adolescent_male'],
				'adolescent_female' => $val['adolescent_female'],
				'adolescent_nature_of_work' => $val['adolescent_nature_of_work'],
				'adolescent_service_since' => trim(implode('-', array_reverse(explode('-', $val['adolescent_service_since'])))),
				'adolescent_seasonal_nature' => $val['adolescent_seasonal_nature'],
				
				'total_male' => $val['total_male'],
				'total_female' => $val['total_female'],
								
				'uid' => $uid,
				'created_date'		   => date('Y-m-d'),
			);
			$total_no_workers_id = db_insert('fa_ir_total_no_workers')->fields($total_no_workers)->execute();
			
		}
		
	//max no workers last twelve months
		$get_max_no_workers = get_max_no_workers_last_twelve_months($inspection_report_id);
		if($get_max_no_workers != NULL && count($get_max_no_workers) > 0) {
			
			$max_no_workers_last_twelve_months = array(
				'inspection_report_id' => $val['inspection_report_id'],
				
				'max_no_workers_male_month_one' => $val['max_no_workers_male_month_one'],
				'max_no_workers_male_month_two' => $val['max_no_workers_male_month_two'],
				'max_no_workers_male_month_three' => $val['max_no_workers_male_month_three'],
				'max_no_workers_male_month_four' => $val['max_no_workers_male_month_four'],
				'max_no_workers_male_month_five' => $val['max_no_workers_male_month_five'],
				'max_no_workers_male_month_six' => $val['max_no_workers_male_month_six'],
				'max_no_workers_male_month_seven' => $val['max_no_workers_male_month_seven'],
				'max_no_workers_male_month_eight' => $val['max_no_workers_male_month_eight'],
				'max_no_workers_male_month_nine' => $val['max_no_workers_male_month_nine'],
				'max_no_workers_male_month_ten' => $val['max_no_workers_male_month_ten'],
				'max_no_workers_male_month_eleven' => $val['max_no_workers_male_month_eleven'],
				'max_no_workers_male_month_twelve' => $val['max_no_workers_male_month_twelve'],
				
				'max_no_workers_female_month_one' => $val['max_no_workers_female_month_one'],
				'max_no_workers_female_month_two' => $val['max_no_workers_female_month_two'],
				'max_no_workers_female_month_three' => $val['max_no_workers_female_month_three'],
				'max_no_workers_female_month_four' => $val['max_no_workers_female_month_four'],
				'max_no_workers_female_month_five' => $val['max_no_workers_female_month_five'],
				'max_no_workers_female_month_six' => $val['max_no_workers_female_month_six'],
				'max_no_workers_female_month_seven' => $val['max_no_workers_female_month_seven'],
				'max_no_workers_female_month_eight' => $val['max_no_workers_female_month_eight'],
				'max_no_workers_female_month_nine' => $val['max_no_workers_female_month_nine'],
				'max_no_workers_female_month_ten' => $val['max_no_workers_female_month_ten'],
				'max_no_workers_female_month_eleven' => $val['max_no_workers_female_month_eleven'],
				'max_no_workers_female_month_twelve' => $val['max_no_workers_female_month_twelve'],
								
				'uid' => $uid,
				'modification_date'	   => date('Y-m-d H:i:s'),
			);
			db_update('fa_ir_max_no_workers_last_twelve_months')->fields($max_no_workers_last_twelve_months)->condition('inspection_report_id', $inspection_report_id, '=')->execute();
				
		} else {
			
			$max_no_workers_last_twelve_months = array(
				'inspection_report_id' => $val['inspection_report_id'],
				
				'max_no_workers_male_month_one' => $val['max_no_workers_male_month_one'],
				'max_no_workers_male_month_two' => $val['max_no_workers_male_month_two'],
				'max_no_workers_male_month_three' => $val['max_no_workers_male_month_three'],
				'max_no_workers_male_month_four' => $val['max_no_workers_male_month_four'],
				'max_no_workers_male_month_five' => $val['max_no_workers_male_month_five'],
				'max_no_workers_male_month_six' => $val['max_no_workers_male_month_six'],
				'max_no_workers_male_month_seven' => $val['max_no_workers_male_month_seven'],
				'max_no_workers_male_month_eight' => $val['max_no_workers_male_month_eight'],
				'max_no_workers_male_month_nine' => $val['max_no_workers_male_month_nine'],
				'max_no_workers_male_month_ten' => $val['max_no_workers_male_month_ten'],
				'max_no_workers_male_month_eleven' => $val['max_no_workers_male_month_eleven'],
				'max_no_workers_male_month_twelve' => $val['max_no_workers_male_month_twelve'],
				
				'max_no_workers_female_month_one' => $val['max_no_workers_female_month_one'],
				'max_no_workers_female_month_two' => $val['max_no_workers_female_month_two'],
				'max_no_workers_female_month_three' => $val['max_no_workers_female_month_three'],
				'max_no_workers_female_month_four' => $val['max_no_workers_female_month_four'],
				'max_no_workers_female_month_five' => $val['max_no_workers_female_month_five'],
				'max_no_workers_female_month_six' => $val['max_no_workers_female_month_six'],
				'max_no_workers_female_month_seven' => $val['max_no_workers_female_month_seven'],
				'max_no_workers_female_month_eight' => $val['max_no_workers_female_month_eight'],
				'max_no_workers_female_month_nine' => $val['max_no_workers_female_month_nine'],
				'max_no_workers_female_month_ten' => $val['max_no_workers_female_month_ten'],
				'max_no_workers_female_month_eleven' => $val['max_no_workers_female_month_eleven'],
				'max_no_workers_female_month_twelve' => $val['max_no_workers_female_month_twelve'],
								
				'uid' => $uid,
				'created_date'		   => date('Y-m-d'),
			);
			$max_no_workers_last_twelve_months_id = db_insert('fa_ir_max_no_workers_last_twelve_months')->fields($max_no_workers_last_twelve_months)->execute();
			
		}
		
		$inspection_report_ID = $inspection_report_id;
		
		//die($inspection_report_ID);
		drupal_goto('admin/inspection-report-factories/occupier-details/'.encryption_decryption_fun('encrypt', $inspection_report_ID).'/'.encryption_decryption_fun('encrypt', $factory_id).'/'.encryption_decryption_fun('encrypt', NULL));
	  
		$form_state['rebuild'] = true;
		
		
	}