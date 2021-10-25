<?php

	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
  	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	function accidents_details_factories_act($form, &$form_state, $annual_returnID = '', $factoryID = '') {
	
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
		
		$get_facilities_section_details = get_facilities_section($annual_return_ID);
		if($get_facilities_section_details->annual_return_id == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/factories-act-apply/facilities_section/'.$annual_returnID.'/'.$factoryID) ;
		}
		
		
		$get_wages_paid_include_deduction = get_total_wages_paid_include_deduction($annual_return_ID);
		$get_disbursement_fine_funds = get_disbursement_fine_funds($annual_return_ID);
		$get_maternity_benefit_all_data = get_maternity_benefit_all_data($annual_return_ID);
		
		$get_accidents_details = get_accidents_details($annual_return_ID);
		
		$tot_no_accidents_fatal = db_query("select * from {fa_form18_notice_accident} where factory_id = :factory_id and accident_type = :accident_type", 
											array(':factory_id' => $factory_id, ':accident_type' => 'F'))->rowCount();
											
		$tot_no_accidents_nonfatal = db_query("select * from {fa_form18_notice_accident} where factory_id = :factory_id and accident_type in (:accident_type)", 
											array(':factory_id' => $factory_id, ':accident_type' => array('M', 'S')))->rowCount();
		
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
		
		$form['accident_details'] = array(
			'#type' => 'fieldset',
			'#title' => t('1. Accident Details'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => FALSE // Added 
		);
		
		$form['accident_details']['tot_no_accidents']	=	array(
			'#prefix'		=>	'<div class="row"><div id="tot_no_accidents_id"><div class="col-md-12 col-xs-12"><label class="select label-block"><strong>(a) Total number of accidents</strong>',
			'#suffix'		=>	'</label></div></div>',
		);
		
		if($tot_no_accidents_fatal != 0) {
		$form['accident_details']['tot_no_accidents_fatals']	=	array(
			'#title' 			=> t('<strong>(i) Fatal</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="tot_no_accidents_fatals_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_accidents_details->tot_no_accidents_fatals) ?  $get_accidents_details->tot_no_accidents_fatals : $tot_no_accidents_fatal,
			'#attributes' 		=> array('class'=>array(''), 'readonly' => 'readonly'),
			'#required' 		=> TRUE,
		);
		} else {
		$form['accident_details']['tot_no_accidents_fatals']	=	array(
			'#title' 			=> t('<strong>(i) Fatal</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="tot_no_accidents_fatals_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_accidents_details->tot_no_accidents_fatals) ?  $get_accidents_details->tot_no_accidents_fatals : '',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);	
		}
		
		if($tot_no_accidents_nonfatal != 0) {
		$form['accident_details']['tot_no_accidents_nonfatals']	=	array(
			'#title' 			=> t('<strong>(ii) Non-Fatal</strong>'),
			'#type'				=>	'textfield',	
			'#prefix'			=>	'<div id="tot_no_accidents_nonfatals_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_accidents_details->tot_no_accidents_nonfatals) ?  $get_accidents_details->tot_no_accidents_nonfatals : $tot_no_accidents_nonfatal,
			'#attributes' 		=> array('class'=>array(''), 'readonly' => 'readonly'),
			'#required' 		=> TRUE,
		);
		} else {
		$form['accident_details']['tot_no_accidents_nonfatals']	=	array(
			'#title' 			=> t('<strong>(ii) Non-Fatal</strong>'),
			'#type'				=>	'textfield',	
			'#prefix'			=>	'<div id="tot_no_accidents_nonfatals_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_accidents_details->tot_no_accidents_nonfatals) ?  $get_accidents_details->tot_no_accidents_nonfatals : '',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);	
		}
		
		$form['accident_details']['workers_returned_to_work']	=	array(
			'#prefix'		=>	'<div id="workers_returned_to_work_id"><div class="col-md-12 col-xs-12"><label class="select label-block"><strong>(b) Accidents in which workers returned to work during the year to which this return relates:</strong>',
			'#suffix'		=>	'</label></div></div>',
		);
		
		$form['accident_details']['accidents_occurring_during_the_year']	=	array(
			'#prefix'		=>	'<div id="accidents_occurring_during_the_year_id"><div class="col-md-12 col-xs-12"><label class="select label-block"><strong>(i) Accidents (workers injured) occurring during the year in which injured workers returned to work during the same year</strong>',
			'#suffix'		=>	'</label></div></div>',
		);
		
		$form['accident_details']['returnedtowork_during_year_no_of_accidents']	=	array(
			'#title' 			=> t('<strong>(aa) Number of accidents</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="returnedtowork_during_year_no_of_accidents_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_accidents_details->returnedtowork_during_year_no_of_accidents) ?  $get_accidents_details->returnedtowork_during_year_no_of_accidents : '',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['accident_details']['returnedtowork_during_year_mandays_lost']	=	array(
			'#title' 			=> t('<strong>(bb) Mandays lost</strong>'),
			'#type'				=>	'textfield',	
			'#prefix'			=>	'<div id="returnedtowork_during_year_mandays_lost_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_accidents_details->returnedtowork_during_year_mandays_lost) ?  $get_accidents_details->returnedtowork_during_year_mandays_lost : '',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['accident_details']['accidents_occurring_previous_year']	=	array(
			'#prefix'		=>	'<div id="accidents_occurring_previous_year_id"><div class="col-md-12 col-xs-12"><label class="select label-block"><strong>(ii) Accidents (workers injured) occurring in the previous year in which injured workers returned to work during the year to which this return relates</strong>',
			'#suffix'		=>	'</label></div></div>',
		);
		
		$form['accident_details']['returnedtowork_previous_year_no_of_accidents']	=	array(
			'#title' 			=> t('<strong>(aa) Number of accidents</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="returnedtowork_previous_year_no_of_accidents_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_accidents_details->returnedtowork_previous_year_no_of_accidents) ?  $get_accidents_details->returnedtowork_previous_year_no_of_accidents : '',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['accident_details']['returnedtowork_previous_year_mandays_lost']	=	array(
			'#title' 			=> t('<strong>(bb) Mandays lost</strong>'),
			'#type'				=>	'textfield',	
			'#prefix'			=>	'<div id="returnedtowork_previous_year_mandays_lost_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_accidents_details->returnedtowork_previous_year_mandays_lost) ?  $get_accidents_details->returnedtowork_previous_year_mandays_lost : '',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['accident_details']['workers_didnot_returned_to_work']	=	array(
			'#prefix'		=>	'<div id="workers_didnot_returned_to_work_id"><div class="col-md-12 col-xs-12"><label class="select label-block"><strong>(c) Accidents (workers injured) occurring during the year in which injured workers did not returned to work during the year to which this return relates</strong>',
			'#suffix'		=>	'</label></div></div>',
		);
		
		$form['accident_details']['didnot_returned_to_work_no_of_accidents']	=	array(
			'#title' 			=> t('<strong>(aa) Number of accidents</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="didnot_returned_to_work_no_of_accidents_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_accidents_details->didnot_returned_to_work_no_of_accidents) ?  $get_accidents_details->didnot_returned_to_work_no_of_accidents : '',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['accident_details']['didnot_returned_to_work_mandays_lost']	=	array(
			'#title' 			=> t('<strong>(bb) Mandays lost</strong>'),
			'#type'				=>	'textfield',	
			'#prefix'			=>	'<div id="didnot_returned_to_work_mandays_lost_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div></div>',
			'#default_value'	=> !empty($get_accidents_details->didnot_returned_to_work_mandays_lost) ?  $get_accidents_details->didnot_returned_to_work_mandays_lost : '',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['accident_details_submit']['submit'] = array (
			'#prefix' 		=> '',  
			'#suffix' 		=> '',
			'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
			'#type' 		=> 'submit',
			'#value'		=> 'Save & Continue'
		);
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'applicant/factories-act-apply/facilities_section/'.$annual_returnID.'/'.$factoryID, array(
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
	
	function accidents_details_factories_act_submit($form, &$form_state){
		//echo '<pre>'; print_r($form_state); die();
		
		global $base_root,$base_path,$user;
		$uid 							= $user->uid;
		
		$annual_return_ID = $form_state['values']['annual_return_id'];
		$factory_id = $form_state['values']['factory_id'];
		
		$val = $form_state['values'];
		
		
		$get_accidents_details = get_accidents_details($annual_return_ID);
		if($get_accidents_details->annual_return_id != NULL && count($get_accidents_details) > 0) {
			$accidents_details = array(
				'annual_return_id' => $val['annual_return_id'],
				
				'tot_no_accidents_fatals' => $val['tot_no_accidents_fatals'],
				'tot_no_accidents_nonfatals' => $val['tot_no_accidents_nonfatals'],
				'returnedtowork_during_year_no_of_accidents' => $val['returnedtowork_during_year_no_of_accidents'],
				'returnedtowork_during_year_mandays_lost' => $val['returnedtowork_during_year_mandays_lost'],
				'returnedtowork_previous_year_no_of_accidents' => $val['returnedtowork_previous_year_no_of_accidents'],
				'returnedtowork_previous_year_mandays_lost' => $val['returnedtowork_previous_year_mandays_lost'],
				'didnot_returned_to_work_no_of_accidents' => $val['didnot_returned_to_work_no_of_accidents'],
				'didnot_returned_to_work_mandays_lost' => $val['didnot_returned_to_work_mandays_lost'],
				
				'uid' => $uid,
				'modification_date'	   => date('Y-m-d H:i:s'),
			);
			db_update('fa_ar_accidents_details')->fields($accidents_details)->condition('annual_return_id', $annual_return_ID, '=')->execute();	
		} else {
			$accidents_details = array(
				'annual_return_id' => $val['annual_return_id'],
				
				'tot_no_accidents_fatals' => $val['tot_no_accidents_fatals'],
				'tot_no_accidents_nonfatals' => $val['tot_no_accidents_nonfatals'],
				'returnedtowork_during_year_no_of_accidents' => $val['returnedtowork_during_year_no_of_accidents'],
				'returnedtowork_during_year_mandays_lost' => $val['returnedtowork_during_year_mandays_lost'],
				'returnedtowork_previous_year_no_of_accidents' => $val['returnedtowork_previous_year_no_of_accidents'],
				'returnedtowork_previous_year_mandays_lost' => $val['returnedtowork_previous_year_mandays_lost'],
				'didnot_returned_to_work_no_of_accidents' => $val['didnot_returned_to_work_no_of_accidents'],
				'didnot_returned_to_work_mandays_lost' => $val['didnot_returned_to_work_mandays_lost'],
								
				'uid' => $uid,
				'created_date'		   => date('Y-m-d'),
			);
			$accidents_details_id = db_insert('fa_ar_accidents_details')->fields($accidents_details)->execute();	
		}
		
		drupal_goto('applicant/factories-act-apply/suggestion_scheme/'.encryption_decryption_fun('encrypt', $annual_return_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));	
		
	}