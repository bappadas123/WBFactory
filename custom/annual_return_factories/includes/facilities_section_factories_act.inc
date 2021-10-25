<?php
	
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
  	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	function facilities_section_factories_act($form, &$form_state, $annual_returnID = '', $factoryID = '') {
	
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
		
		$get_welfare_officers_details = get_welfare_officers($annual_return_ID);
		if($get_welfare_officers_details[0]->annual_return_id == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/factories-act-apply/welfare_officers/'.$annual_returnID.'/'.$factoryID) ;
		}
		
		
		$get_wages_paid_include_deduction = get_total_wages_paid_include_deduction($annual_return_ID);
		$get_disbursement_fine_funds = get_disbursement_fine_funds($annual_return_ID);
		$get_maternity_benefit_all_data = get_maternity_benefit_all_data($annual_return_ID);
		
		$get_facilities_section_details = get_facilities_section($annual_return_ID);
		
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
		
		$options = array("Yes" => "Yes","No" => "No");
		
		$form['ambulance_room'] = array(
		'#type' => 'fieldset',
		'#title' => t('Ambulance Room'),
		'#collapsible' => TRUE, // Added
		'#collapsed' => FALSE // Added 
		);
												
		$form['ambulance_room']['ambulance_room_in_factory']	=	array(	
			'#title' 			=> t('<strong>1. Is there an Ambulance Room provided in the factory as required under Section 45?</strong>'),
			'#type'				=> 'radios',
			'#options' 			=> $options,
			'#prefix'			=> '<div class="row"><div id="ambulance_room_in_factory_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></div>',
			'#default_value'	=> !empty($get_facilities_section_details->ambulance_room_in_factory) ? $get_facilities_section_details->ambulance_room_in_factory : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['canteen'] = array(
		'#type' => 'fieldset',
		'#title' => t('Canteen'),
		'#collapsible' => TRUE, // Added
		'#collapsed' => FALSE // Added 
		);
												
		$form['canteen']['no_canteen_in_factory']	=	array(
			'#title' 			=> t('<strong>2.(a) No. of Canteens provided in the factory as required under Section 46</strong>'),	
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div class="row"><div id="no_canteen_in_factory_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_facilities_section_details->no_canteen_in_factory) ? $get_facilities_section_details->no_canteen_in_factory : '', 
			'#attributes' 		=> array('class'=>array('form-control')),
			'#required' 		=> TRUE,
		);
		
		$options_managed_run = array("department" => "(i) Departmentally, or", "contractor" => "(ii) Through a Contractor");
		$form['canteen']['canteen_provided_managed_run']	=	array(
			'#title' 		=> t('<strong>(b) Is the Canteen provided managed/run:</strong>'),
			'#type'			=> 'radios',
			'#options' 		=> $options_managed_run,
			'#prefix'		=> '<div id="canteen_provided_managed_run_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
			'#suffix'		=> '</label></div></div>',
			'#default_value'	=> !empty($get_facilities_section_details->canteen_provided_managed_run) ? $get_facilities_section_details->canteen_provided_managed_run : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		
		$form['rest_room_lunch_room'] = array(
		'#type' => 'fieldset',
		'#title' => t('Shelters or Rest Rooms and Lunch Rooms'),
		'#collapsible' => TRUE, // Added
		'#collapsed' => FALSE // Added 
		);
												
		$form['rest_room_lunch_room']['no_of_shelters_rest_room']	=	array(
			'#title' 			=> t('<strong>3.(a) No. of Shelters or Rest Rooms provided in the factory as required under Section 47</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div class="row"><div id="no_of_shelters_rest_room_id"><div class="col-md-8 col-xs-8"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_facilities_section_details->no_of_shelters_rest_room) ? $get_facilities_section_details->no_of_shelters_rest_room : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['rest_room_lunch_room']['no_of_lunch_room']	=	array(	
			'#title' 			=> t('<strong>(b) No. of Lunch Rooms provided in the factory as required under Section 47</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="no_of_lunch_room_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div></div>',
			'#default_value'	=> !empty($get_facilities_section_details->no_of_lunch_room) ? $get_facilities_section_details->no_of_lunch_room : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['creches'] = array(
		'#type' => 'fieldset',
		'#title' => t('Creches'),
		'#collapsible' => TRUE, // Added
		'#collapsed' => FALSE // Added 
		);
												
		$form['creches']['no_of_creches_factory']	=	array(
			'#title' 			=> t('<strong>4.(a) No. of Creches provided in the factory as required under Section 48</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div class="row"><div id="no_of_creches_factory_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_facilities_section_details->no_of_creches_factory) ? $get_facilities_section_details->no_of_creches_factory : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['creches']['no_of_child_utilize_creche']	=	array(
			'#title' 			=> t('<strong>(b) No. of children utilizing the creche</strong>'),	
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="no_of_child_utilize_creche_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div></div>',
			'#default_value'	=> !empty($get_facilities_section_details->no_of_child_utilize_creche) ? $get_facilities_section_details->no_of_child_utilize_creche : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['facilities_section']['submit'] = array (
			'#prefix' 		=> '',  
			'#suffix' 		=> '',
			'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
			'#type' 		=> 'submit',
			'#value'		=> 'Save & Continue'
		);
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'applicant/factories-act-apply/welfare_officers/'.$annual_returnID.'/'.$factoryID, array(
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
	
	
	function facilities_section_factories_act_submit($form, &$form_state){
		//echo '<pre>'; print_r($form_state); die();
		
		global $base_root,$base_path,$user;
		$uid 							= $user->uid;
		
		$annual_return_ID = $form_state['values']['annual_return_id'];
		$factory_id = $form_state['values']['factory_id'];
		
		$val = $form_state['values'];
		
		
		$get_facilities_section_details = get_facilities_section($annual_return_ID);
		if($get_facilities_section_details->annual_return_id != NULL && count($get_facilities_section_details) > 0) {
			$facilities_section = array(
				'annual_return_id' => $val['annual_return_id'],
				
				'ambulance_room_in_factory' => $val['ambulance_room_in_factory'],
				'no_canteen_in_factory' => $val['no_canteen_in_factory'],
				'canteen_provided_managed_run' => $val['canteen_provided_managed_run'],
				'no_of_shelters_rest_room' => $val['no_of_shelters_rest_room'],
				'no_of_lunch_room' => $val['no_of_lunch_room'],
                'no_of_creches_factory' => $val['no_of_creches_factory'],
				'no_of_child_utilize_creche' => $val['no_of_child_utilize_creche'],
				
				'uid' => $uid,
				'modification_date'	   => date('Y-m-d H:i:s'),
			);
			db_update('fa_ar_facilities_factory_act')->fields($facilities_section)->condition('annual_return_id', $annual_return_ID, '=')->execute();	
		} else {
			$facilities_section = array(
				'annual_return_id' => $val['annual_return_id'],
				
				'ambulance_room_in_factory' => $val['ambulance_room_in_factory'],
				'no_canteen_in_factory' => $val['no_canteen_in_factory'],
				'canteen_provided_managed_run' => $val['canteen_provided_managed_run'],
				'no_of_shelters_rest_room' => $val['no_of_shelters_rest_room'],
				'no_of_lunch_room' => $val['no_of_lunch_room'],
                'no_of_creches_factory' => $val['no_of_creches_factory'],
				'no_of_child_utilize_creche' => $val['no_of_child_utilize_creche'],
								
				'uid' => $uid,
				'created_date'		   => date('Y-m-d'),
			);
			$facilities_section_id = db_insert('fa_ar_facilities_factory_act')->fields($facilities_section)->execute();	
		}

		drupal_goto('applicant/factories-act-apply/accidents/'.encryption_decryption_fun('encrypt', $annual_return_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));	
		
	}