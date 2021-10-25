<?php

	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
  	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	function safety_officers_factories_act($form, &$form_state, $annual_returnID = '', $factoryID = '') {
	
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
		
		
		$get_wages_paid_include_deduction = get_total_wages_paid_include_deduction($annual_return_ID);
		$get_disbursement_fine_funds = get_disbursement_fine_funds($annual_return_ID);
		$get_maternity_benefit_all_data = get_maternity_benefit_all_data($annual_return_ID);
		
		$get_safety_officers_details = get_safety_officers($annual_return_ID);
		
		$get_dangerous_operation_details = get_dangerous_operation($annual_return_ID);
		if($get_factory_info->dangerous_operation_process_in_factory == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/factories-act-apply/dangerous_operation/'.$annual_returnID.'/'.$factoryID) ;
		} else {
			if($get_factory_info->dangerous_operation_process_in_factory == 'Yes') {
				if($get_dangerous_operation_details[0]->annual_return_id == NULL) {
					drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
					drupal_goto('applicant/factories-act-apply/dangerous_operation/'.$annual_returnID.'/'.$factoryID) ;
				}
			}
		}
		
		
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
		
		$form['safety_officers'] = array(
		'#type' => 'fieldset',
		'#title' => t('1. Safety Officers Details'),
		'#collapsible' => TRUE, // Added
		'#collapsed' => FALSE // Added 
		);
		
												
		$form['safety_officers']['no_of_safety_officers']	=	array(
			'#title' 			=> t('<strong>1. (a) Number of Safety Officers required to be appointed as per Notification under Section 40B</strong>'),
			'#type'				=>'textfield',
			'#prefix' 			=> '<div class="row"><div id="no_of_safety_officers_id"><div class="col-md-8 col-xs-8"><label class="select label-block">',
			'#suffix' 			=> '</label></div></div>', 
			'#default_value'	=> !empty($get_factory_info->no_of_safety_officers) ? $get_factory_info->no_of_safety_officers : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,							
		
		);
		
			
		$form['safety_officers']['safety_officers_details']	=	array(
			'#prefix'		=>	'<div id="safety_officers_details_id"><div class="col-md-12 col-xs-12"><label class="select label-block"><strong>(b) Details of Safety Officers appointed</strong>',
			'#suffix'		=>	'</label></div></div>',
		);
		
		$form['safety_officers']['safety_officers_name']	=	array(
			'#title' 			=> t('<strong>(i) Name of Safety Officer</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="safety_officers_name_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#attributes' 		=> array('class'=>array('')),
			//'#required' 		=> TRUE,
		);
		
		$form['safety_officers']['safety_officers_date_of_appoitment']	=	array(
			'#title' 			=> t('<strong>(ii) Date of Appoitment</strong>'),
			'#type'				=>	'textfield',	
			'#prefix'			=>	'<div id="safety_officers_date_of_appoitment_id"><div class="col-md-3 col-xs-3"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#attributes' 		=> array('class'=>array('form-control datepicker_retify')),
			//'#required' 		=> TRUE,
		);
		
		$form['safety_officers']['safety_officers_qualification']	=	array(
			'#title' 			=> t('<strong>(iii) Qualification</strong>'),
			'#type'				=>	'textfield',	
			'#prefix'			=>	'<div id="safety_officers_qualification_id"><div class="col-md-3 col-xs-3"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#attributes' 		=> array('class'=>array('')),
			//'#required' 		=> TRUE,
		);
		
		$form['safety_officers']['safety_officers_degree_institute_name']	=	array(
			'#title' 			=> t('<strong>(iv) Name of  the Institution from which he obtained a degree or diploma or a certificate in Industrial Safety</strong>'),
			'#type'				=>	'textfield',	
			'#prefix'			=>	'<div id="safety_officers_degree_institute_name_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#attributes' 		=> array('class'=>array('')),
			//'#required' 		=> TRUE,
		);
		
		$form['safety_officers']['safety_officers_bengali_knowledge_institute']	=	array(
			'#title' 			=> t('<strong>**(v) Name of  the Institution from which thorough knowledge in bengali was acquired and the examination passed</strong>'),
			'#type'				=>	'textfield',	
			'#prefix'			=>	'<div id="safety_officers_bengali_knowledge_institute_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#attributes' 		=> array('class'=>array('')),
			//'#required' 		=> TRUE,
		);
		
		$form['safety_officers']['safety_officers_dop_viva_test']	=	array(
			'#title' 			=> t('<strong>(vi) Date of passing the Viva Voice Test under Clause (d) of Rule 4<br> of the West Bengal Factories (Safety Officers) Rules</strong>'),
			'#type'				=>	'textfield',	
			'#prefix'			=>	'<div id="safety_officers_dop_viva_test_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#attributes' 		=> array('class'=>array('form-control datepicker_retify')),
			//'#required' 		=> TRUE,
		);
		
		
		$form['safety_officers']['add_safety_officers_details'] = array(
			'#prefix' 			=> '<div id="add_safety_officers_details_id"><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></div>',
			'#attributes'       => array('class' => array('btn btn-dark'),'style'=>'float: right;'),
			'#type' 			=> 'submit',
			'#value' 			=> t("+ Add Safety Officers Details"),
		);	
			
		$form['safety_officers']['view_safety_officers_details'] = array(
			'#prefix'			=> '<div id="view_safety_officers_details_id"><div class="col-md-12">',
			'#suffix' 		    => '</div></div></div>',
			'#type' 			=> 'markup',
			'#markup' 			=> view_safety_officers_details($annual_return_ID, $factory_id),
		);
		
		// Enter Safety Officers Details //
		if(!empty($get_safety_officers_details))
		{
			$form['safety_officers_submit']['submit'] = array (
				'#prefix' 		=> '',  
				'#suffix' 		=> '',
				'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
				'#type' 		=> 'submit',
				'#value'		=> 'Save & Continue'
			);
		}
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'applicant/factories-act-apply/dangerous_operation/'.$annual_returnID.'/'.$factoryID, array(
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
	
	function safety_officers_factories_act_validate($form, &$form_state){
		
		$annual_return_ID = $form_state['values']['annual_return_id'];
		$get_factory_info = get_annual_return_factory_information($annual_return_ID);
		
		$get_safety_officers_details = get_safety_officers($annual_return_ID);
		
			
		
		
		if($form_state['values']['op'] == "+ Add Safety Officers Details") {
			if($form_state['values']['no_of_safety_officers'] != 0) {
				if($form_state['values']['safety_officers_name'] == '') {
					form_set_error('Safety Officers Details', t('You have to enter Name of Safety Officer!'));		
				} else {
					if($form_state['values']['safety_officers_date_of_appoitment'] == '') {
						form_set_error('Safety Officers Details', t('You have to enter Date of Appoitment!'));		
					} else {
						if($form_state['values']['safety_officers_qualification'] == '') {
							form_set_error('Safety Officers Details', t('You have to enter Qualification!'));		
						} else {
							if($form_state['values']['safety_officers_degree_institute_name'] == '') {
								form_set_error('Safety Officers Details', t('You have to enter Name of the Institution from which he obtained a degree or diploma or a certificate in Industrial Safety!'));		
							} else {
								if($form_state['values']['safety_officers_bengali_knowledge_institute'] == '') {
									form_set_error('Safety Officers Details', t('You have to enter Name of the Institution from which thorough knowledge in bengali was acquired and the examination passed!'));		
								} else {
									if($form_state['values']['safety_officers_dop_viva_test'] == '') {
										form_set_error('Safety Officers Details', t('You have to enter Date of passing the Viva Voice Test under Clause (d) of Rule 4 of the West Bengal Factories (Safety Officers) Rules!'));		
									}	
								}	
							}	
						}	
					}
				}
			} else {
				form_set_error('No of Safety Officers', t('No of Safety Officers can\'t be 0(Zero) or Blank!'));	
			}
		}
		
		if(!empty($get_safety_officers_details) && $form_state['values']['op'] == '+ Add Safety Officers Details') {
			if($form_state['values']['no_of_safety_officers'] <= count($get_safety_officers_details)) {
				//drupal_set_message(t('Safety Officers Details cannot be less or greater than No of Safety Officers entered!'), 'error');
				form_set_error('Safety Officers Details', t('Safety Officers Details cannot be greater than No of Safety Officers entered!'));	
			}
		}
		
		if(!empty($get_safety_officers_details) && $form_state['values']['op'] == 'Save & Continue') {
			if($form_state['values']['no_of_safety_officers'] != count($get_safety_officers_details)) {
				//drupal_set_message(t('Safety Officers Details cannot be less or greater than No of Safety Officers entered!'), 'error');
				form_set_error('Safety Officers Details', t('Safety Officers Details cannot be less or greater than No of Safety Officers entered!'));	
			}
		}
		
	}
	
	function safety_officers_factories_act_submit($form, &$form_state){
		//echo '<pre>'; print_r($form_state); die();
		
		global $base_root,$base_path,$user;
		$uid 							= $user->uid;
		
		$annual_return_ID = $form_state['values']['annual_return_id'];
		$factory_id = $form_state['values']['factory_id'];
		
		$val = $form_state['values'];
		
		$get_safety_officers_details = get_safety_officers($annual_return_ID);
		
			
		if($val['op'] == "+ Add Safety Officers Details") {
			
			$annual_return_update = array(
				'no_of_safety_officers' => $val['no_of_safety_officers'],
				'modification_date'	   => date('Y-m-d H:i:s'),
			);
			db_update('fa_annual_return')->fields($annual_return_update)->condition('id', $annual_return_ID, '=')->execute();
		
			$safety_officers = array(
				'annual_return_id' => $val['annual_return_id'],
				
				'safety_officers_name' => $val['safety_officers_name'],
				'safety_officers_date_of_appoitment' => trim(implode('-', array_reverse(explode('-', $val['safety_officers_date_of_appoitment'])))),
				'safety_officers_qualification' => $val['safety_officers_qualification'],
				'safety_officers_degree_institute_name' => $val['safety_officers_degree_institute_name'],
				'safety_officers_bengali_knowledge_institute' => $val['safety_officers_bengali_knowledge_institute'],
				'safety_officers_dop_viva_test' => trim(implode('-', array_reverse(explode('-', $val['safety_officers_dop_viva_test'])))),
								
				'uid' => $uid,
				'created_date'		   => date('Y-m-d'),
			);
			$safety_officers_id = db_insert('fa_ar_safety_officers_factory_act')->fields($safety_officers)->execute();
		}
		
		if($val['op'] == 'Save & Continue') {
			$annual_return_update = array(
				'no_of_safety_officers' => $val['no_of_safety_officers'],
				'modification_date'	   => date('Y-m-d H:i:s'),
			);
			db_update('fa_annual_return')->fields($annual_return_update)->condition('id', $annual_return_ID, '=')->execute();
			
			drupal_goto('applicant/factories-act-apply/welfare_officers/'.encryption_decryption_fun('encrypt', $annual_return_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));	
		}
		
		//$form_state['rebuild'] = true;
		
	}
	
	
	function view_safety_officers_details($annual_return_ID, $factory_id){ //echo 'A-'.$form_id.' B-'.$reference_id.' C-'.$factory_id; die;
		$get_safety_officers_details 			= array();
		$type					= '';
		$details				= '';
	
		$get_safety_officers_details 			= get_safety_officers($annual_return_ID);
		
		$Wcounter		= 0;
		$per_page		= 5;
		$current_page 	= pager_default_initialize(count($get_safety_officers_details), $per_page);
		$chunks 		= array_chunk($get_safety_officers_details, $per_page);
		if($current_page>0){
			$Wcounter 	= $current_page*$per_page;
		}
		$header			= array(
							array('data' => 'Sl. No'),
							array('data'=> 'Safety Officer Name'),
							array('data'=> 'Date of Appoitment'),
							array('data'=> 'Qualification'),
							array('data'=> 'Name of the degree Institution'),
							array('data'=> 'Name of the bengali knowledge Institution'),
							array('data'=> 'Viva Voice passing date'),
							array('data'=> 'Action'),	
						);
						
		if(!empty($get_safety_officers_details)){	
			foreach($chunks[$current_page] as $safety_officers_details){ 
				$Wcounter++;
				
				$onclick="return confirm('Are you sure you want to delete?')";
				
				$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/factories-act-apply/del_safety_officers/'.encryption_decryption_fun('encrypt',  
				$safety_officers_details->id).'/'.encryption_decryption_fun('encrypt', $safety_officers_details->annual_return_id).'/'.encryption_decryption_fun('encrypt', 
				$factory_id),array('html' => TRUE, 'attributes'=>array('onclick' => $onclick, 'title' => 'Delete')));	//,'class'=>array('red','use-ajax')
				
				$formated_safety_officers_date_of_appoitment = trim(implode('-', array_reverse(explode('-', $safety_officers_details->safety_officers_date_of_appoitment))));
				$formated_safety_officers_dop_viva_test = trim(implode('-', array_reverse(explode('-', $safety_officers_details->safety_officers_dop_viva_test))));
				
				$rows[] 	= array( 
					array('data' =>$Wcounter,'class' => array('')),
					array('data' =>$safety_officers_details->safety_officers_name,'class' => array('')),
					array('data' =>$formated_safety_officers_date_of_appoitment,'class' => array('')),
					array('data' =>$safety_officers_details->safety_officers_qualification,'class' => array('')),
					array('data' =>$safety_officers_details->safety_officers_degree_institute_name,'class' => array('')),
					array('data' =>$safety_officers_details->safety_officers_bengali_knowledge_institute,'class' => array('')),
					array('data' =>$formated_safety_officers_dop_viva_test,'class' => array('')),
					array('data' =>$delLink ,'class' => array('')),
				);
			}
		}
		
		$output = theme_table(
			array(
				  'header' => $header,
				  'rows' => $rows,
				  'attributes' => array('id'=>'view_safety_officers_details_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
				  'sticky' => true,
				  'caption' => 'All Safety Officers Details List',
				  'colgroups' => array(),
				  'empty' => t("No data found!") // The message to be displayed if table is empty
				)
			).theme('pager');	
		
		return $output;	
	}
	
	function del_safety_officers_details($id, $annual_return_ID, $factory_id) {//die;
		//drupal_add_library('system', 'drupal.ajax');
	
		$safety_officers_id = encryption_decryption_fun('decrypt', $id);
		$annual_return_id  	= encryption_decryption_fun('decrypt', $annual_return_ID);
		
		if($safety_officers_id != 0) {
			$query = db_delete('fa_ar_safety_officers_factory_act');
			$query->condition('id', $safety_officers_id,'=');
			$query->condition('annual_return_id', $annual_return_id,'=');
			$query->execute();
		}
		
		drupal_goto('applicant/factories-act-apply/safety_officers/'.$annual_return_ID.'/'.$factory_id);

		/*$commands = array();
		$commands[] = ajax_command_replace('#view_dangerous_operation_id', "<div id ='view_dangerous_operation_id'><div class='col-md-12 col-xs-12'>".view_dangerous_operation_details($annual_return_ID, $factory_id).'</div></div>');
		$page = array('#type' => 'ajax', '#commands' => $commands);
		ajax_deliver($page);*/	
		
	}