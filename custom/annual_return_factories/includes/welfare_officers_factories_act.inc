<?php

	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
  	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	function welfare_officers_factories_act($form, &$form_state, $annual_returnID = '', $factoryID = '') {
	
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
		
		$get_safety_officers_details = get_safety_officers($annual_return_ID);
		if($get_safety_officers_details[0]->annual_return_id == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/factories-act-apply/safety_officers/'.$annual_returnID.'/'.$factoryID) ;
		}
		
		
		$get_wages_paid_include_deduction = get_total_wages_paid_include_deduction($annual_return_ID);
		$get_disbursement_fine_funds = get_disbursement_fine_funds($annual_return_ID);
		$get_maternity_benefit_all_data = get_maternity_benefit_all_data($annual_return_ID);
		
		$get_welfare_officers_details = get_welfare_officers($annual_return_ID);
		
		
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
		
		$form['welfare_officers'] = array(
		'#type' => 'fieldset',
		'#title' => t('1. Welfare Officers Details'),
		'#collapsible' => TRUE, // Added
		'#collapsed' => FALSE // Added 
		);
		
											
		$form['welfare_officers']['no_of_welfare_officers']	=	array(
			'#title' 			=> t('<strong>1. (a) Number of Welfare Officers to be appointed as required under Section 49</strong>'),
			'#type'				=>'textfield',
			'#prefix' 			=> '<div class="row"><div id="no_of_welfare_officers_id"><div class="col-md-7 col-xs-7"><label class="select label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#default_value'	=> !empty($get_factory_info->no_of_welfare_officers) ? $get_factory_info->no_of_welfare_officers : '',  
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,							
		
		);
		
			
		$form['welfare_officers']['welfare_officers_details']	=	array(
			'#prefix'		=>	'<div id="welfare_officers_details_id"><div class="col-md-12 col-xs-12"><label class="select label-block"><strong>(b) Details of Welfare Officers appointed</strong>',
			'#suffix'		=>	'</label></div></div>',
		);
		
		$form['welfare_officers']['welfare_officers_name']	=	array(
			'#title' 			=> t('<strong>(i) Name of Welfare Officer</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="welfare_officers_name_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#attributes' 		=> array('class'=>array('')),
			//'#required' 		=> TRUE,
		);
		
		$form['welfare_officers']['welfare_officers_date_of_appoitment']	=	array(
			'#title' 			=> t('<strong>(ii) Date of Appoitment</strong>'),
			'#type'				=>	'textfield',	
			'#prefix'			=>	'<div id="welfare_officers_date_of_appoitment_id"><div class="col-md-3 col-xs-3"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#attributes' 		=> array('class'=>array('form-control datepicker_retify')),
			//'#required' 		=> TRUE,
		);
		
		$form['welfare_officers']['welfare_officers_degree_institute_name']	=	array(
			'#title' 			=> t('<strong>(iii) Name of  the Institution from which he obtained a degree or diploma in Labour and Social Welfare or <br>when he passed the L.W.O. Training Course of the Govt. of West Bengal*</strong>'),
			'#type'				=>	'textfield',	
			'#prefix'			=>	'<div id="welfare_officers_degree_institute_name_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#attributes' 		=> array('class'=>array('')),
			//'#required' 		=> TRUE,
		);
		
		$form['welfare_officers']['welfare_officers_bengali_knowledge_institute']	=	array(
			'#title' 			=> t('<strong>**(iv) Name of  the Institution from which thorough knowledge in bengali was acquired and the examination passed</strong>'),
			'#type'				=>	'textfield',	
			'#prefix'			=>	'<div id="welfare_officers_bengali_knowledge_institute_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#attributes' 		=> array('class'=>array('')),
			//'#required' 		=> TRUE,
		);
		
		$form['welfare_officers']['welfare_officers_dop_viva_test']	=	array(
			'#title' 			=> t('<strong>(v) Date of passing the Viva Voice Test under Clause (d) of Rule 5<br> of the West Bengal Factories (Welfare Officers) Rules</strong>'),
			'#type'				=>	'textfield',	
			'#prefix'			=>	'<div id="welfare_officers_dop_viva_test_id"><div class="col-md-5 col-xs-5"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#attributes' 		=> array('class'=>array('form-control datepicker_retify')),
			//'#required' 		=> TRUE,
		);
		
		$form['welfare_officers']['welfare_officers_grade_scale']	=	array(
			'#title' 			=> t('<strong>**(vi) Grade and scale of pay</strong>'),
			'#type'				=>	'textfield',	
			'#prefix'			=>	'<div id="welfare_officers_grade_scale_id"><div class="col-md-8 col-xs-8"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#attributes' 		=> array('class'=>array('')),
			//'#required' 		=> TRUE,
		);
		
		
		$form['welfare_officers']['add_welfare_officers_details'] = array(
			'#prefix' 			=> '<div id="add_welfare_officers_details_id"><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></div>',
			'#attributes'       => array('class' => array('btn btn-dark'),'style'=>'float: right;'),
			'#type' 			=> 'submit',
			'#value' 			=> t("+ Add Welfare Officers Details"),
		);	
			
		$form['welfare_officers']['view_welfare_officers_details'] = array(
			'#prefix'			=> '<div id="view_welfare_officers_details_id"><div class="col-md-12">',
			'#suffix' 		    => '</div></div></div>',
			'#type' 			=> 'markup',
			'#markup' 			=> view_welfare_officers_details($annual_return_ID, $factory_id),
		);
		
		// Enter Safety Officers Details //
		if(!empty($get_welfare_officers_details))
		{
			$form['welfare_officers_submit']['submit'] = array (
				'#prefix' 		=> '',  
				'#suffix' 		=> '',
				'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
				'#type' 		=> 'submit',
				'#value'		=> 'Save & Continue'
			);
		}
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'applicant/factories-act-apply/safety_officers/'.$annual_returnID.'/'.$factoryID, array(
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
	
	function welfare_officers_factories_act_validate($form, &$form_state){
		
		$annual_return_ID = $form_state['values']['annual_return_id'];
		$get_factory_info = get_annual_return_factory_information($annual_return_ID);
		
		$get_welfare_officers_details = get_welfare_officers($annual_return_ID);
		
		if($form_state['values']['op'] == "+ Add Welfare Officers Details") {
			if($form_state['values']['no_of_welfare_officers'] != 0) {
				if($form_state['values']['welfare_officers_name'] == '') {
					form_set_error('Welfare Officers Details', t('You have to enter Name of Welfare Officer!'));		
				} else {
					if($form_state['values']['welfare_officers_date_of_appoitment'] == '') {
						form_set_error('Welfare Officers Details', t('You have to enter Date of Appoitment!'));		
					} else {
						if($form_state['values']['welfare_officers_degree_institute_name'] == '') {
							form_set_error('Welfare Officers Details', t('You have to enter Name of the Institution from which he obtained a degree or diploma in Labour and Social Welfare or 
	when he passed the L.W.O. Training Course of the Govt. of West Bengal!'));		
						} else {
							if($form_state['values']['welfare_officers_bengali_knowledge_institute'] == '') {
								form_set_error('Welfare Officers Details', t('You have to enter Name of the Institution from which thorough knowledge in bengali was acquired and the examination passed!'));		
							} else {
								if($form_state['values']['welfare_officers_dop_viva_test'] == '') {
									form_set_error('Welfare Officers Details', t('You have to enter Date of passing the Viva Voice Test under Clause (d) of Rule 5 of the West Bengal Factories (Welfare Officers) Rules!'));		
								} else {
									if($form_state['values']['welfare_officers_grade_scale'] == '') {
										form_set_error('Welfare Officers Details', t('You have to enter Grade and scale of pay!'));		
									}	
								}	
							}	
						}	
					}
				}
			} else {
				form_set_error('No of Welfare Officers', t('No of Welfare Officers can\'t be 0(Zero) or Blank!'));		
			}
		}
		
		if(!empty($get_welfare_officers_details) && $form_state['values']['op'] == '+ Add Welfare Officers Details') {
			if($form_state['values']['no_of_welfare_officers'] <= count($get_welfare_officers_details)) {
				//drupal_set_message(t('Welfare Officers Details cannot be less or greater than No of Welfare Officers entered!'), 'error');
				form_set_error('Welfare Officers Details', t('Welfare Officers Details cannot be greater than No of Welfare Officers entered!'));	
			}
		}
		
		if(!empty($get_welfare_officers_details) && $form_state['values']['op'] == 'Save & Continue') {
			if($form_state['values']['no_of_welfare_officers'] != count($get_welfare_officers_details)) {
				//drupal_set_message(t('Welfare Officers Details cannot be less or greater than No of Welfare Officers entered!'), 'error');
				form_set_error('Welfare Officers Details', t('Welfare Officers Details cannot be less or greater than No of Welfare Officers entered!'));	
			}
		}
		
	}
	
	function welfare_officers_factories_act_submit($form, &$form_state){
		//echo '<pre>'; print_r($form_state); die();
		
		global $base_root,$base_path,$user;
		$uid 							= $user->uid;
		
		$annual_return_ID = $form_state['values']['annual_return_id'];
		$factory_id = $form_state['values']['factory_id'];
		
		$val = $form_state['values'];
		
		$get_welfare_officers_details = get_welfare_officers($annual_return_ID);
		
			
		if($val['op'] == "+ Add Welfare Officers Details") {
			
			$annual_return_update = array(
				'no_of_welfare_officers' => $val['no_of_welfare_officers'],
				'modification_date'	   => date('Y-m-d H:i:s'),
			);
			db_update('fa_annual_return')->fields($annual_return_update)->condition('id', $annual_return_ID, '=')->execute();
		
			$welfare_officers = array(
				'annual_return_id' => $val['annual_return_id'],
				
				'welfare_officers_name' => $val['welfare_officers_name'],
				'welfare_officers_date_of_appoitment' => trim(implode('-', array_reverse(explode('-', $val['welfare_officers_date_of_appoitment'])))),
				'welfare_officers_degree_institute_name' => $val['welfare_officers_degree_institute_name'],
				'welfare_officers_bengali_knowledge_institute' => $val['welfare_officers_bengali_knowledge_institute'],
				'welfare_officers_dop_viva_test' => trim(implode('-', array_reverse(explode('-', $val['welfare_officers_dop_viva_test'])))),
				'welfare_officers_grade_scale' => $val['welfare_officers_grade_scale'],
								
				'uid' => $uid,
				'created_date'		   => date('Y-m-d'),
			);
			$welfare_officers_id = db_insert('fa_ar_welfare_officers_factory_act')->fields($welfare_officers)->execute();
		}
		
		if($val['op'] == 'Save & Continue') {
			$annual_return_update = array(
				'no_of_welfare_officers' => $val['no_of_welfare_officers'],
				'modification_date'	   => date('Y-m-d H:i:s'),
			);
			db_update('fa_annual_return')->fields($annual_return_update)->condition('id', $annual_return_ID, '=')->execute();
			
			drupal_goto('applicant/factories-act-apply/facilities_section/'.encryption_decryption_fun('encrypt', $annual_return_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));	
		}
		
		
		
		//$form_state['rebuild'] = true;		
		
		
		
		
	}
	
	
	function view_welfare_officers_details($annual_return_ID, $factory_id){ //echo 'A-'.$form_id.' B-'.$reference_id.' C-'.$factory_id; die;
		$get_welfare_officers_details 			= array();
		$type					= '';
		$details				= '';
	
		$get_welfare_officers_details 			= get_welfare_officers($annual_return_ID);
		
		$Wcounter		= 0;
		$per_page		= 5;
		$current_page 	= pager_default_initialize(count($get_welfare_officers_details), $per_page);
		$chunks 		= array_chunk($get_welfare_officers_details, $per_page);
		if($current_page>0){
			$Wcounter 	= $current_page*$per_page;
		}
		$header			= array(
							array('data' => 'Sl. No'),
							array('data'=> 'Welfare Officer Name'),
							array('data'=> 'Date of Appoitment'),
							array('data'=> 'Name of the degree Institution'),
							array('data'=> 'Name of the bengali knowledge Institution'),
							array('data'=> 'Viva Voice passing date'),
							array('data'=> 'Grade and Scale Pay'),
							array('data'=> 'Action'),	
						);
						
		if(!empty($get_welfare_officers_details)){	
			foreach($chunks[$current_page] as $welfare_officers_details){ 
				$Wcounter++;
				
				$onclick="return confirm('Are you sure you want to delete?')";
				
				$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/factories-act-apply/del_welfare_officers/'.encryption_decryption_fun('encrypt',  
				$welfare_officers_details->id).'/'.encryption_decryption_fun('encrypt', $welfare_officers_details->annual_return_id).'/'.encryption_decryption_fun('encrypt', 
				$factory_id),array('html' => TRUE, 'attributes'=>array('onclick' => $onclick, 'title' => 'Delete')));	//,'class'=>array('red','use-ajax')
				
				$formated_welfare_officers_date_of_appoitment = trim(implode('-', array_reverse(explode('-', $welfare_officers_details->welfare_officers_date_of_appoitment))));
				$formated_welfare_officers_dop_viva_test = trim(implode('-', array_reverse(explode('-', $welfare_officers_details->welfare_officers_dop_viva_test))));
				
				$rows[] 	= array( 
					array('data' =>$Wcounter,'class' => array('')),
					array('data' =>$welfare_officers_details->welfare_officers_name,'class' => array('')),
					array('data' =>$formated_welfare_officers_date_of_appoitment,'class' => array('')),
					array('data' =>$welfare_officers_details->welfare_officers_degree_institute_name,'class' => array('')),
					array('data' =>$welfare_officers_details->welfare_officers_bengali_knowledge_institute,'class' => array('')),
					array('data' =>$formated_welfare_officers_dop_viva_test,'class' => array('')),
					array('data' =>$welfare_officers_details->welfare_officers_grade_scale,'class' => array('')),
					array('data' =>$delLink ,'class' => array('')),
				);
			}
		}
		
		$output = theme_table(
			array(
				  'header' => $header,
				  'rows' => $rows,
				  'attributes' => array('id'=>'view_welfare_officers_details_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
				  'sticky' => true,
				  'caption' => 'All Welfare Officers Details List',
				  'colgroups' => array(),
				  'empty' => t("No data found!") // The message to be displayed if table is empty
				)
			).theme('pager');	
		
		return $output;		
	}
	
	function del_welfare_officers_details($id, $annual_return_ID, $factory_id) {//die;
		//drupal_add_library('system', 'drupal.ajax');
	
		$welfare_officers_id = encryption_decryption_fun('decrypt', $id);
		$annual_return_id  	= encryption_decryption_fun('decrypt', $annual_return_ID);
		
		if($welfare_officers_id != 0) {
			$query = db_delete('fa_ar_welfare_officers_factory_act');
			$query->condition('id', $welfare_officers_id,'=');
			$query->condition('annual_return_id', $annual_return_id,'=');
			$query->execute();
		}
		
		drupal_goto('applicant/factories-act-apply/welfare_officers/'.$annual_return_ID.'/'.$factory_id);

		/*$commands = array();
		$commands[] = ajax_command_replace('#view_dangerous_operation_id', "<div id ='view_dangerous_operation_id'><div class='col-md-12 col-xs-12'>".view_dangerous_operation_details($annual_return_ID, $factory_id).'</div></div>');
		$page = array('#type' => 'ajax', '#commands' => $commands);
		ajax_deliver($page);*/	
		
	}