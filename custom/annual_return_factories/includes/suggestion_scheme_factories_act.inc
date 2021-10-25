<?php

	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
  	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	function suggestion_scheme_factories_act($form, &$form_state, $annual_returnID = '', $factoryID = '') {
	
		global $user;
		$uid 						= $user->uid;
	  
	 	$annual_return_ID = encryption_decryption_fun('decrypt', $annual_returnID);
		//$factory_type_id = encryption_decryption_fun('decrypt', $factory_typeID);
    	$factory_id = encryption_decryption_fun('decrypt', $factoryID);


		$get_factory_info = get_annual_return_factory_information($annual_return_ID);

	//This section only for get factory_typeid for sending to annual-return-common
	
		$factory_typeID = encryption_decryption_fun('encrypt', $get_factory_info->factory_typeid);
	//end
		
		if(empty($annual_return_ID) || /*$factory_id == 0 ||*/ $annual_return_ID == '') {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Factory Information first.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/annual-return-common/'.$annual_returnID.'/'.$factory_typeID.'/'.$factoryID) ;
		}
		
		$get_accidents_details = get_accidents_details($annual_return_ID);
		if($get_accidents_details->annual_return_id == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/factories-act-apply/accidents/'.$annual_returnID.'/'.$factoryID) ;
		}
		
		
		$get_wages_paid_include_deduction = get_total_wages_paid_include_deduction($annual_return_ID);
		$get_disbursement_fine_funds = get_disbursement_fine_funds($annual_return_ID);
		$get_maternity_benefit_all_data = get_maternity_benefit_all_data($annual_return_ID);
		
		$get_suggestion_scheme_details = get_suggestion_scheme($annual_return_ID);
		
		$form = array();
		
		$form['annual_return_id'] = array(
				'#prefix' 			=> '<div id="annual_return_id"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#type' 			=> 'hidden',
				'#default_value' 	=> !empty($annual_return_ID) ? $annual_return_ID : '',
		);
		
		$form['factory_id'] = array(
				'#prefix' 			=> '<div id="factory_type_id"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#type' 			=> 'hidden',
				'#default_value' 	=> $factory_id,
		);
		
		$common_section_edit = l('Annual Return Common Section Edit', 'applicant/annual-return-common-apply/default/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		
		if($get_factory_info->payment_wages_flag == 1 && $get_wages_paid_include_deduction->annual_return_id != NULL && $get_disbursement_fine_funds->annual_return_id != NULL) {
			$payment_wages_edit = l('Payment of Wages Edit', 'applicant/payment-of-wages/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		} else {
			$payment_wages_edit = '';
		}
		
		if($get_factory_info->maternity_benefit_flag == 1 && $get_maternity_benefit_all_data->ar_id != NULL) {
			$maternity_benefit_edit = l('Maternity Benefit Edit', 'applicant/maternity-benefit-apply/medical_officer/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		} else {
			$maternity_benefit_edit = '';
		}
		
		
		$form['suggestion_scheme'] = array(
		'#type' => 'fieldset',
		'#title' => t('1. Suggestion Scheme'),
		'#collapsible' => TRUE, // Added
		'#collapsed' => FALSE // Added 
		);
												
		$value_suggestion_scheme_operation = isset($form_state['values']['suggestion_scheme_operation_in_factory']) ? $form_state['values']['suggestion_scheme_operation_in_factory'] : '';
		
		$options = array("Yes" => "Yes","No" => "No");										
		$form['suggestion_scheme']['suggestion_scheme_operation_in_factory']	=	array(
			'#title' 			=> t('<strong>1. (a) Is a Suggestion Scheme in operation in the factory</strong>'),
			'#type'				=>	'radios',
			'#options' 			=> $options,
			'#default_value'	=>!empty($get_suggestion_scheme_details->suggestion_scheme_operation_in_factory) ?  $get_suggestion_scheme_details->suggestion_scheme_operation_in_factory : '',
			'#prefix' 			=> '<div class="row"><div id="operation_in_factory_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
			'#suffix' 			=> '</label></div></div>', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
			'#ajax' 			=> array(
											'event' => 'change',
											'effect' => 'fade',
											'callback' => 'get_ajax_suggestion_scheme_operation',
											'progress' => array(
												'type' => 'throbber',
												'message' => t('loading')
											)
			)
										
		
		);
		
		
		if($value_suggestion_scheme_operation == 'Yes') {
			
			$form['suggestion_scheme']['suggestion_scheme_no_of_suggestion']	=	array(
				'#prefix'		=>	'<div id="no_of_suggestion_id"><div class="col-md-12 col-xs-12"><label class="select label-block"><strong>(b) If so, the number of suggestion:</strong>',
				'#suffix'		=>	'</label></div></div>',
			);
			
			$form['suggestion_scheme']['suggestion_scheme_received_during_year']	=	array(
				'#title' 			=> t('<strong>(i) Received during the year</strong>'),
				'#type'				=>	'textfield',
				'#prefix'			=>	'<div id="received_during_year_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
				'#suffix'			=>	'</label></div></div>',
				'#default_value'	=> !empty($get_suggestion_scheme_details->suggestion_scheme_received_during_year) ? $get_suggestion_scheme_details->suggestion_scheme_received_during_year : '', 
				'#attributes' 		=> array('class'=>array('')),
				'#required' 		=> TRUE,
			);
			
			$form['suggestion_scheme']['suggestion_scheme_accepted_during_year']	=	array(
				'#title' 			=> t('<strong>(ii) Accepted during the year</strong>'),
				'#type'				=>	'textfield',	
				'#prefix'			=>	'<div id="accepted_during_year_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
				'#suffix'			=>	'</label></div></div>',
				'#default_value'	=> !empty($get_suggestion_scheme_details->suggestion_scheme_accepted_during_year) ? $get_suggestion_scheme_details->suggestion_scheme_accepted_during_year : '', 
				'#attributes' 		=> array('class'=>array('')),
				'#required' 		=> TRUE,
			);
			
			$form['suggestion_scheme']['suggestion_scheme_amt_awarded_cash']	=	array(	
				'#prefix'		=>	'<div id="amt_awarded_cash_id"><div class="col-md-12 col-xs-12"><label class="select label-block"><strong>(c) Amount awared in cash prizes during the year:</strong>',
				'#suffix'		=>	'</label></div></div>',
			);
			
			$form['suggestion_scheme']['suggestion_scheme_tot_amt_awarded']	=	array(	
				'#title' 			=> t('<strong>(i) Total amount awared</strong>'),
				'#type'				=>	'textfield',
				'#prefix'			=>	'<div id="tot_amt_awarded_id"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix'			=>	'</label></div></div>',
				'#default_value'	=> !empty($get_suggestion_scheme_details->suggestion_scheme_tot_amt_awarded) ? $get_suggestion_scheme_details->suggestion_scheme_tot_amt_awarded : '', 
				'#attributes' 		=> array('class'=>array('form-control'), 'id'=>'tot_amt_awarded_id'),
				'#required' 		=> TRUE,
			);
			
			$form['suggestion_scheme']['suggestion_scheme_value_max_cash_prize']	=	array(	
				'#title' 			=> t('<strong>(ii) Value of the maximum cash prize awarded</strong>'),
				'#type'				=>	'textfield',
				'#prefix'			=>	'<div id="max_cash_prize_id"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix'			=>	'</label></div></div>',
				'#default_value'	=> !empty($get_suggestion_scheme_details->suggestion_scheme_value_max_cash_prize) ? $get_suggestion_scheme_details->suggestion_scheme_value_max_cash_prize : '', 
				'#attributes' 		=> array('class'=>array('form-control'), 'id'=>'value_max_cash_prize_id'),
				'#required' 		=> TRUE,
			);
			
			$form['suggestion_scheme']['suggestion_scheme_value_min_cash_prize']	=	array(	
				'#title' 			=> t('<strong>(iii) Value of the minimum cash prize awarded</strong>'),
				'#type'				=>	'textfield',
				'#prefix'			=>	'<div id="min_cash_prize_id"><div class="col-md-4 col-xs-4"><label class="select label-block">',
				'#suffix'			=>	'</label></div></div></div>',
				'#default_value'	=> !empty($get_suggestion_scheme_details->suggestion_scheme_value_min_cash_prize) ? $get_suggestion_scheme_details->suggestion_scheme_value_min_cash_prize : '', 
				'#attributes' 		=> array('class'=>array('form-control'), 'id'=>'value_min_cash_prize_id'),
				'#required' 		=> TRUE,
			);
			
			$form['suggestion_scheme_submit']['submit'] = array (
				'#prefix' 		=> '<div id="suggestion_scheme_submit_id">',  
				'#suffix' 		=> '</div>',
				'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
				'#type' 		=> 'submit',
				'#value'		=> 'Save & Continue'
			);
			
		} else if($value_suggestion_scheme_operation == 'No') {
			
			$form['suggestion_scheme']['suggestion_scheme_no_of_suggestion']	=	array(	
				'#prefix'		=>	'<div id="no_of_suggestion_id">',
				'#suffix'		=>	'</div>',
			);
					
			$form['suggestion_scheme']['suggestion_scheme_received_during_year']	=	array(	
				'#prefix'		=>	'<div id="received_during_year_id">',
				'#suffix'		=>	'</div>',
			);
			
			$form['suggestion_scheme']['suggestion_scheme_accepted_during_year']	=	array(	
				'#prefix'		=>	'<div id="accepted_during_year_id">',
				'#suffix'		=>	'</div>',
			);
			
			$form['suggestion_scheme']['suggestion_scheme_amt_awarded_cash']	=	array(	
				'#prefix'		=>	'<div id="amt_awarded_cash_id">',
				'#suffix'		=>	'</div>',
			);
					
			$form['suggestion_scheme']['suggestion_scheme_tot_amt_awarded']	=	array(	
				'#prefix'		=>	'<div id="tot_amt_awarded_id">',
				'#suffix'		=>	'</div>',
			);
			
			$form['suggestion_scheme']['suggestion_scheme_value_max_cash_prize']	=	array(	
				'#prefix'		=>	'<div id="max_cash_prize_id">',
				'#suffix'		=>	'</div>',
			);
			
			$form['suggestion_scheme']['suggestion_scheme_value_min_cash_prize']	=	array(	
				'#prefix'		=>	'<div id="min_cash_prize_id">',
				'#suffix'		=>	'</div>',
			);
			
			$form['suggestion_scheme_submit']['submit'] = array (
				'#prefix' 		=> '<div id="suggestion_scheme_submit_id">',  
				'#suffix' 		=> '</div>',
				'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
				'#type' 		=> 'submit',
				'#value'		=> 'Save & Continue'
			);
			
		} else {
			
			if($get_suggestion_scheme_details->annual_return_id != NULL && $get_suggestion_scheme_details->suggestion_scheme_operation_in_factory == 'Yes') {
				
				$form['suggestion_scheme']['suggestion_scheme_no_of_suggestion']	=	array(
					'#prefix'		=>	'<div id="no_of_suggestion_id"><div class="col-md-12 col-xs-12"><label class="select label-block"><strong>(b) If so, the number of suggestion:</strong>',
					'#suffix'		=>	'</label></div></div>',
				);
				
				$form['suggestion_scheme']['suggestion_scheme_received_during_year']	=	array(
					'#title' 			=> t('<strong>(i) Received during the year</strong>'),
					'#type'				=>	'textfield',
					'#prefix'			=>	'<div id="received_during_year_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
					'#suffix'			=>	'</label></div></div>',
					'#default_value'	=> !empty($get_suggestion_scheme_details->suggestion_scheme_received_during_year) ? $get_suggestion_scheme_details->suggestion_scheme_received_during_year : '', 
					'#attributes' 		=> array('class'=>array('')),
					'#required' 		=> TRUE,
				);
				
				$form['suggestion_scheme']['suggestion_scheme_accepted_during_year']	=	array(
					'#title' 			=> t('<strong>(ii) Accepted during the year</strong>'),
					'#type'				=>	'textfield',	
					'#prefix'			=>	'<div id="accepted_during_year_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
					'#suffix'			=>	'</label></div></div>',
					'#default_value'	=> !empty($get_suggestion_scheme_details->suggestion_scheme_accepted_during_year) ? $get_suggestion_scheme_details->suggestion_scheme_accepted_during_year : '', 
					'#attributes' 		=> array('class'=>array('')),
					'#required' 		=> TRUE,
				);
				
				$form['suggestion_scheme']['suggestion_scheme_amt_awarded_cash']	=	array(	
					'#prefix'		=>	'<div id="amt_awarded_cash_id"><div class="col-md-12 col-xs-12"><label class="select label-block"><strong>(c) Amount awared in cash prizes during the year:</strong>',
					'#suffix'		=>	'</label></div></div>',
				);
				
				$form['suggestion_scheme']['suggestion_scheme_tot_amt_awarded']	=	array(	
					'#title' 			=> t('<strong>(i) Total amount awared</strong>'),
					'#type'				=>	'textfield',
					'#prefix'			=>	'<div id="tot_amt_awarded_id"><div class="col-md-4 col-xs-4"><label class="select label-block">',
					'#suffix'			=>	'</label></div></div>',
					'#default_value'	=> !empty($get_suggestion_scheme_details->suggestion_scheme_tot_amt_awarded) ? $get_suggestion_scheme_details->suggestion_scheme_tot_amt_awarded : '', 
					'#attributes' 		=> array('class'=>array('form-control'), 'id'=>'tot_amt_awarded_id'),
					'#required' 		=> TRUE,
				);
				
				$form['suggestion_scheme']['suggestion_scheme_value_max_cash_prize']	=	array(	
					'#title' 			=> t('<strong>(ii) Value of the maximum cash prize awarded</strong>'),
					'#type'				=>	'textfield',
					'#prefix'			=>	'<div id="max_cash_prize_id"><div class="col-md-4 col-xs-4"><label class="select label-block">',
					'#suffix'			=>	'</label></div></div>',
					'#default_value'	=> !empty($get_suggestion_scheme_details->suggestion_scheme_value_max_cash_prize) ? $get_suggestion_scheme_details->suggestion_scheme_value_max_cash_prize : '', 
					'#attributes' 		=> array('class'=>array('form-control'), 'id'=>'value_max_cash_prize_id'),
					'#required' 		=> TRUE,
				);
				
				$form['suggestion_scheme']['suggestion_scheme_value_min_cash_prize']	=	array(	
					'#title' 			=> t('<strong>(iii) Value of the minimum cash prize awarded</strong>'),
					'#type'				=>	'textfield',
					'#prefix'			=>	'<div id="min_cash_prize_id"><div class="col-md-4 col-xs-4"><label class="select label-block">',
					'#suffix'			=>	'</label></div></div></div>',
					'#default_value'	=> !empty($get_suggestion_scheme_details->suggestion_scheme_value_min_cash_prize) ? $get_suggestion_scheme_details->suggestion_scheme_value_min_cash_prize : '', 
					'#attributes' 		=> array('class'=>array('form-control'), 'id'=>'value_min_cash_prize_id'),
					'#required' 		=> TRUE,
				);
				
				$form['suggestion_scheme_submit']['submit'] = array (
					'#prefix' 		=> '<div id="suggestion_scheme_submit_id">',  
					'#suffix' 		=> '</div>',
					'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
					'#type' 		=> 'submit',
					'#value'		=> 'Save & Continue'
				);	
				
			} else if($get_suggestion_scheme_details->annual_return_id != NULL && $get_suggestion_scheme_details->suggestion_scheme_operation_in_factory == 'No') {
			
				$form['suggestion_scheme']['suggestion_scheme_no_of_suggestion']	=	array(	
					'#prefix'		=>	'<div id="no_of_suggestion_id">',
					'#suffix'		=>	'</div>',
				);
						
				$form['suggestion_scheme']['suggestion_scheme_received_during_year']	=	array(	
					'#prefix'		=>	'<div id="received_during_year_id">',
					'#suffix'		=>	'</div>',
				);
				
				$form['suggestion_scheme']['suggestion_scheme_accepted_during_year']	=	array(	
					'#prefix'		=>	'<div id="accepted_during_year_id">',
					'#suffix'		=>	'</div>',
				);
				
				$form['suggestion_scheme']['suggestion_scheme_amt_awarded_cash']	=	array(	
					'#prefix'		=>	'<div id="amt_awarded_cash_id">',
					'#suffix'		=>	'</div>',
				);
						
				$form['suggestion_scheme']['suggestion_scheme_tot_amt_awarded']	=	array(	
					'#prefix'		=>	'<div id="tot_amt_awarded_id">',
					'#suffix'		=>	'</div>',
				);
				
				$form['suggestion_scheme']['suggestion_scheme_value_max_cash_prize']	=	array(	
					'#prefix'		=>	'<div id="max_cash_prize_id">',
					'#suffix'		=>	'</div>',
				);
				
				$form['suggestion_scheme']['suggestion_scheme_value_min_cash_prize']	=	array(	
					'#prefix'		=>	'<div id="min_cash_prize_id">',
					'#suffix'		=>	'</div>',
				);
				
				$form['suggestion_scheme_submit']['submit'] = array (
					'#prefix' 		=> '<div id="suggestion_scheme_submit_id">',  
					'#suffix' 		=> '</div>',
					'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
					'#type' 		=> 'submit',
					'#value'		=> 'Save & Continue'
				);
				
			} else {
				
				$form['suggestion_scheme']['suggestion_scheme_no_of_suggestion']	=	array(	
					'#prefix'		=>	'<div id="no_of_suggestion_id">',
					'#suffix'		=>	'</div>',
				);
						
				$form['suggestion_scheme']['suggestion_scheme_received_during_year']	=	array(	
					'#prefix'		=>	'<div id="received_during_year_id">',
					'#suffix'		=>	'</div>',
				);
				
				$form['suggestion_scheme']['suggestion_scheme_accepted_during_year']	=	array(	
					'#prefix'		=>	'<div id="accepted_during_year_id">',
					'#suffix'		=>	'</div>',
				);
				
				$form['suggestion_scheme']['suggestion_scheme_amt_awarded_cash']	=	array(	
					'#prefix'		=>	'<div id="amt_awarded_cash_id">',
					'#suffix'		=>	'</div>',
				);
						
				$form['suggestion_scheme']['suggestion_scheme_tot_amt_awarded']	=	array(	
					'#prefix'		=>	'<div id="tot_amt_awarded_id">',
					'#suffix'		=>	'</div>',
				);
				
				$form['suggestion_scheme']['suggestion_scheme_value_max_cash_prize']	=	array(	
					'#prefix'		=>	'<div id="max_cash_prize_id">',
					'#suffix'		=>	'</div>',
				);
				
				$form['suggestion_scheme']['suggestion_scheme_value_min_cash_prize']	=	array(	
					'#prefix'		=>	'<div id="min_cash_prize_id">',
					'#suffix'		=>	'</div>',
				);
				
				$form['suggestion_scheme_submit']['submit'] = array (
					'#prefix' 		=> '<div id="suggestion_scheme_submit_id">',  
					'#suffix' 		=> '</div>',
					/*'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
					'#type' 		=> 'submit',
					'#value'		=> 'Save & Continue'*/
				);
				
			}
			
		}
		
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'applicant/factories-act-apply/accidents/'.$annual_returnID.'/'.$factoryID, array(
				'html' => TRUE,
				'attributes' => array('class' => array('btn btn-outline-dark pull-left'))
			))
		);
		
		$form['factory_act_link_markup'] = array(
				'#type'		=> 'markup',
				'#prefix'	=> '<div class="row">
									<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
									'.$common_section_edit.$payment_wages_edit.$maternity_benefit_edit.'',
				'#suffix' => '		</div>
								</div>',
		);
		
		return $form;
	
	
	}
	
	function suggestion_scheme_factories_act_submit($form, &$form_state){
		//echo '<pre>'; print_r($form_state); die();
		
		global $base_root,$base_path,$user;
		$uid 							= $user->uid;
		
		$annual_return_ID = $form_state['values']['annual_return_id'];
		$factory_id = $form_state['values']['factory_id'];
		
		$val = $form_state['values'];
		
		if($val['suggestion_scheme_operation_in_factory'] == 'Yes') {
			$suggestion_scheme_received_during_year = $val['suggestion_scheme_received_during_year'];
			$suggestion_scheme_accepted_during_year = $val['suggestion_scheme_accepted_during_year'];
		} else if($val['suggestion_scheme_operation_in_factory'] == 'No') {
			$suggestion_scheme_received_during_year = NULL;
			$suggestion_scheme_accepted_during_year = NULL;	
		}
		
		
		$get_suggestion_scheme_details = get_suggestion_scheme($annual_return_ID);
		if($get_suggestion_scheme_details->annual_return_id != NULL && count($get_suggestion_scheme_details) > 0) {
			$suggestion_scheme = array(
				'annual_return_id' => $val['annual_return_id'],
				
				'suggestion_scheme_operation_in_factory' => $val['suggestion_scheme_operation_in_factory'],
				'suggestion_scheme_received_during_year' => $suggestion_scheme_received_during_year,
				'suggestion_scheme_accepted_during_year' => $suggestion_scheme_accepted_during_year,
				'suggestion_scheme_tot_amt_awarded' 	 => $val['suggestion_scheme_tot_amt_awarded'],
				'suggestion_scheme_value_max_cash_prize' => $val['suggestion_scheme_value_max_cash_prize'],
				'suggestion_scheme_value_min_cash_prize' => $val['suggestion_scheme_value_min_cash_prize'],
				
				'uid' => $uid,
				'modification_date'	   => date('Y-m-d H:i:s'),
			);
			db_update('fa_ar_suggestion_scheme')->fields($suggestion_scheme)->condition('annual_return_id', $annual_return_ID, '=')->execute();	
		} else {
			$suggestion_scheme = array(
				'annual_return_id' => $val['annual_return_id'],
				
				'suggestion_scheme_operation_in_factory' => $val['suggestion_scheme_operation_in_factory'],
				'suggestion_scheme_received_during_year' => $suggestion_scheme_received_during_year,
				'suggestion_scheme_accepted_during_year' => $suggestion_scheme_accepted_during_year,
				'suggestion_scheme_tot_amt_awarded'  	 => $val['suggestion_scheme_tot_amt_awarded'],
				'suggestion_scheme_value_max_cash_prize' => $val['suggestion_scheme_value_max_cash_prize'],
				'suggestion_scheme_value_min_cash_prize' => $val['suggestion_scheme_value_min_cash_prize'],
								
				'uid' => $uid,
				'created_date'		   => date('Y-m-d'),
			);
			$suggestion_scheme_id = db_insert('fa_ar_suggestion_scheme')->fields($suggestion_scheme)->execute();	
		}
		
		$get_factory_info = get_annual_return_factory_information($annual_return_ID);
		if($get_factory_info->maternity_benefit_flag == 1) {
			drupal_goto('applicant/maternity-benefit-apply/medical_officer/'.encryption_decryption_fun('encrypt', $annual_return_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));	
		} else {
			drupal_goto('applicant/ar-application-preview/ar_common_app_preview/'.encryption_decryption_fun('encrypt', $annual_return_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));	
		}
		
		
	}
	
	
	function get_ajax_suggestion_scheme_operation($form, $form_state){
	  
		$commands[] = ajax_command_replace('#no_of_suggestion_id', drupal_render($form['suggestion_scheme']['suggestion_scheme_no_of_suggestion']));
		$commands[] = ajax_command_replace('#received_during_year_id', drupal_render($form['suggestion_scheme']['suggestion_scheme_received_during_year']));
		$commands[] = ajax_command_replace('#accepted_during_year_id', drupal_render($form['suggestion_scheme']['suggestion_scheme_accepted_during_year']));
		
		$commands[] = ajax_command_replace('#amt_awarded_cash_id', drupal_render($form['suggestion_scheme']['suggestion_scheme_amt_awarded_cash']));
		$commands[] = ajax_command_replace('#tot_amt_awarded_id', drupal_render($form['suggestion_scheme']['suggestion_scheme_tot_amt_awarded']));
		$commands[] = ajax_command_replace('#max_cash_prize_id', drupal_render($form['suggestion_scheme']['suggestion_scheme_value_max_cash_prize']));
		$commands[] = ajax_command_replace('#min_cash_prize_id', drupal_render($form['suggestion_scheme']['suggestion_scheme_value_min_cash_prize']));
		
		$commands[] = ajax_command_replace('#suggestion_scheme_submit_id', drupal_render($form['suggestion_scheme_submit']['submit']));
	  
	 	return array('#type' => 'ajax', '#commands' => $commands);
	}