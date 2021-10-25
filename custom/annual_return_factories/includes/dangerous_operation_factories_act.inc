<?php

	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
  	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	function dangerous_operation_factories_act($form, &$form_state, $annual_returnID = '', $factoryID = '') {
	
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
		
		$get_dangerous_operation_details = get_dangerous_operation($annual_return_ID);
		
		
		if($get_wages_paid_include_deduction->annual_return_id == NULL || $get_disbursement_fine_funds->annual_return_id == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/payment-of-wages/'.$annual_returnID.'/'.$factoryID) ;
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
		
		$back_link = 'applicant/payment-of-wages';
		
		$form['dangerous_operation'] = array(
		'#type' => 'fieldset',
		'#title' => t('1. Dangerous Process or Operation'),
		'#collapsible' => TRUE, // Added
		'#collapsed' => FALSE // Added 
		);
												
		$value_dangerous_operation_process = isset($form_state['values']['dangerous_operation_process_in_factory']) ? $form_state['values']['dangerous_operation_process_in_factory'] : '';
		
		$options = array("Yes" => "Yes","No" => "No");										
		$form['dangerous_operation']['dangerous_operation_process_in_factory']	=	array(
			'#title' 			=> t('<strong>1. (a) Does the factory carry on any process or operation declared as dangerous under Section 87?</strong>'),
			'#type'				=>'radios',
			'#options' 			=> $options,
			'#default_value'	=> !empty($get_factory_info->dangerous_operation_process_in_factory) ? $get_factory_info->dangerous_operation_process_in_factory : '',
			'#prefix' 			=> '<div class="row"><div id="dangerous_operation_process_in_factory_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
			'#suffix' 			=> '</label></div></div>', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
			'#ajax' 			=> array(
											'event' => 'change',
											'effect' => 'fade',
											'callback' => 'get_ajax_dangerous_operation_process',
											'progress' => array(
												'type' => 'throbber',
												'message' => t('loading')
											)
			)
										
		
		);
		
		if($value_dangerous_operation_process == 'Yes') {
			
			$form['dangerous_operation']['dangerous_operation_info']	=	array(
				'#prefix'		=>	'<div id="dangerous_operation_info_id"><div class="col-md-12 col-xs-12"><label class="select label-block"><strong>(b) If so, give the following information:</strong>',
				'#suffix'		=>	'</label></div></div>',
			);
			
			$form['dangerous_operation']['dangerous_operation_name']	=	array(
				'#title' 			=> t('<strong>(i) Name of the dangerous process or operations carried on</strong>'),
				'#type'				=>	'textfield',
				'#prefix'			=>	'<div id="dangerous_operation_name_id"><div class="col-md-7 col-xs-7"><label class="select label-block">',
				'#suffix'			=>	'</label></div></div>',
				'#attributes' 		=> array('class'=>array('')),
				//'#required' 		=> TRUE,
			);
			
			$form['dangerous_operation']['avg_persons_employed_daily_in_operation']	=	array(
				'#title' 			=> t('<strong>(ii) Average number of persons employed daily<br> in each of the processes or operations</strong>'),
				'#type'				=>	'textfield',	
				'#prefix'			=>	'<div id="avg_persons_employed_daily_in_operation_id"><div class="col-md-5 col-xs-5"><label class="select label-block">',
				'#suffix'			=>	'</label></div></div>',
				'#attributes' 		=> array('class'=>array('')),
				//'#required' 		=> TRUE,
			);
			
			
			$form['dangerous_operation']['add_dangerous_operation'] = array(
				'#prefix' 			=> '<div id="add_dangerous_operation_id"><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></div>',
				'#attributes'       => array('class' => array('btn btn-dark'),'style'=>'float: right;'),
				'#type' 			=> 'submit',
				'#value' 			=> t("+ Add Dangerous Process or Operation"),
			);	
				
			$form['dangerous_operation']['view_dangerous_operation'] = array(
				'#prefix'			=> '<div id="view_dangerous_operation_id"><div class="col-md-12">',
				'#suffix' 		    => '</div></div></div>',
				'#type' 			=> 'markup',
				'#markup' 			=> view_dangerous_operation_details($annual_return_ID, $factory_id),
			);
			
			// Enter Dangerous Operation Details //
			if(!empty($get_dangerous_operation_details))
			{
				$form['dangerous_operation_submit']['submit'] = array (
					'#prefix' 		=> '<div id="dangerous_operation_submit_id">',  
					'#suffix' 		=> '</div>',
					'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
					'#type' 		=> 'submit',
					'#value'		=> 'Save & Continue'
				);
			} else {
				$form['dangerous_operation_submit']['submit'] = array (
					'#prefix' 		=> '<div id="dangerous_operation_submit_id">',  
					'#suffix' 		=> '</div>',
				);	
			}
			
		} else if($value_dangerous_operation_process == 'No') {
			
			$form['dangerous_operation']['dangerous_operation_info']	=	array(
				'#prefix'		=>	'<div id="dangerous_operation_info_id">',
				'#suffix'		=>	'</div>',
			);
			
			$form['dangerous_operation']['dangerous_operation_name']	=	array(
				'#prefix'			=>	'<div id="dangerous_operation_name_id">',
				'#suffix'			=>	'</div>',
			);
			
			$form['dangerous_operation']['avg_persons_employed_daily_in_operation']	=	array(
				'#prefix'			=>	'<div id="avg_persons_employed_daily_in_operation_id">',
				'#suffix'			=>	'</div>',
			);
			
			$form['dangerous_operation']['add_dangerous_operation'] = array(
				'#prefix' 			=> '<div id="add_dangerous_operation_id">',
				'#suffix' 			=> '</div>',
			);	
				
			$form['dangerous_operation']['view_dangerous_operation'] = array(
				'#prefix'			=> '<div id="view_dangerous_operation_id">',
				'#suffix' 		    => '</div>',
			);
			
			$form['dangerous_operation_submit']['submit'] = array (
				'#prefix' 		=> '<div id="dangerous_operation_submit_id">',  
				'#suffix' 		=> '</div>',
				'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
				'#type' 		=> 'submit',
				'#value'		=> 'Save & Continue'
			);
			
		} else {
			
			//if($get_dangerous_operation_details[0]->annual_return_id != NULL && $get_factory_info->dangerous_operation_process_in_factory == 'Yes') {
			if($get_factory_info->dangerous_operation_process_in_factory == 'Yes') {
				
				$form['dangerous_operation']['dangerous_operation_info']	=	array(
					'#prefix'		=>	'<div id="dangerous_operation_info_id"><div class="col-md-12 col-xs-12"><label class="select label-block"><strong>(b) If so, give the following information:</strong>',
					'#suffix'		=>	'</label></div></div>',
				);
				
				$form['dangerous_operation']['dangerous_operation_name']	=	array(
					'#title' 			=> t('<strong>(i) Name of the dangerous process or operations carried on</strong>'),
					'#type'				=>	'textfield',
					'#prefix'			=>	'<div id="dangerous_operation_name_id"><div class="col-md-7 col-xs-7"><label class="select label-block">',
					'#suffix'			=>	'</label></div></div>', 
					'#attributes' 		=> array('class'=>array('')),
					//'#required' 		=> TRUE,
				);
				
				$form['dangerous_operation']['avg_persons_employed_daily_in_operation']	=	array(
					'#title' 			=> t('<strong>(ii) Average number of persons employed daily<br> in each of the processes or operations</strong>'),
					'#type'				=>	'textfield',	
					'#prefix'			=>	'<div id="avg_persons_employed_daily_in_operation_id"><div class="col-md-5 col-xs-5"><label class="select label-block">',
					'#suffix'			=>	'</label></div></div>',
					'#attributes' 		=> array('class'=>array('')),
					//'#required' 		=> TRUE,
				);
				
				
				$form['dangerous_operation']['add_dangerous_operation'] = array(
					'#prefix' 			=> '<div id="add_dangerous_operation_id"><div class="col-md-12 col-xs-12">',
					'#suffix' 			=> '</div></div>',
					'#attributes'       => array('class' => array('btn btn-dark'),'style'=>'float: right;'),
					'#type' 			=> 'submit',
					'#value' 			=> t("+ Add Dangerous Process or Operation"),
				);	
					
				$form['dangerous_operation']['view_dangerous_operation'] = array(
					'#prefix'			=> '<div id="view_dangerous_operation_id"><div class="col-md-12">',
					'#suffix' 		    => '</div></div></div>',
					'#type' 			=> 'markup',
					'#markup' 			=> view_dangerous_operation_details($annual_return_ID, $factory_id),
				);
				
				// Enter Dangerous Operation Details //
				if(!empty($get_dangerous_operation_details))
				{
					$form['dangerous_operation_submit']['submit'] = array (
						'#prefix' 		=> '<div id="dangerous_operation_submit_id">',  
						'#suffix' 		=> '</div>',
						'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
						'#type' 		=> 'submit',
						'#value'		=> 'Save & Continue'
					);
				} else {
					$form['dangerous_operation_submit']['submit'] = array (
						'#prefix' 		=> '<div id="dangerous_operation_submit_id">',  
						'#suffix' 		=> '</div>',
					);	
				}
				
			} else if($get_factory_info->dangerous_operation_process_in_factory == 'No') {
			
				$form['dangerous_operation']['dangerous_operation_info']	=	array(
					'#prefix'		=>	'<div id="dangerous_operation_info_id">',
					'#suffix'		=>	'</div>',
				);
				
				$form['dangerous_operation']['dangerous_operation_name']	=	array(
					'#prefix'			=>	'<div id="dangerous_operation_name_id">',
					'#suffix'			=>	'</div>',
				);
				
				$form['dangerous_operation']['avg_persons_employed_daily_in_operation']	=	array(
					'#prefix'			=>	'<div id="avg_persons_employed_daily_in_operation_id">',
					'#suffix'			=>	'</div>',
				);
				
				$form['dangerous_operation']['add_dangerous_operation'] = array(
					'#prefix' 			=> '<div id="add_dangerous_operation_id">',
					'#suffix' 			=> '</div>',
				);	
					
				$form['dangerous_operation']['view_dangerous_operation'] = array(
					'#prefix'			=> '<div id="view_dangerous_operation_id">',
					'#suffix' 		    => '</div>',
				);
				
				$form['dangerous_operation_submit']['submit'] = array (
					'#prefix' 		=> '<div id="dangerous_operation_submit_id">',  
					'#suffix' 		=> '</div>',
					'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
					'#type' 		=> 'submit',
					'#value'		=> 'Save & Continue'
				);
				
			} else {
				
				$form['dangerous_operation']['dangerous_operation_info']	=	array(
					'#prefix'		=>	'<div id="dangerous_operation_info_id">',
					'#suffix'		=>	'</div>',
				);
				
				$form['dangerous_operation']['dangerous_operation_name']	=	array(
					'#prefix'			=>	'<div id="dangerous_operation_name_id">',
					'#suffix'			=>	'</div>',
				);
				
				$form['dangerous_operation']['avg_persons_employed_daily_in_operation']	=	array(
					'#prefix'			=>	'<div id="avg_persons_employed_daily_in_operation_id">',
					'#suffix'			=>	'</div>',
				);
				
				$form['dangerous_operation']['add_dangerous_operation'] = array(
					'#prefix' 			=> '<div id="add_dangerous_operation_id">',
					'#suffix' 			=> '</div>',
				);	
					
				$form['dangerous_operation']['view_dangerous_operation'] = array(
					'#prefix'			=> '<div id="view_dangerous_operation_id">',
					'#suffix' 		    => '</div>',
				);
				
				$form['dangerous_operation_submit']['submit'] = array (
					'#prefix' 		=> '<div id="dangerous_operation_submit_id">',  
					'#suffix' 		=> '</div>',
					/*'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
					'#type' 		=> 'submit',
					'#value'		=> 'Save & Continue'*/
				);
				
			}
			
		}
					
		
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), ''.$back_link.'/'.$annual_returnID.'/'.$factoryID, array(
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
	
	function dangerous_operation_factories_act_validate($form, &$form_state){
		
		$annual_return_ID = $form_state['values']['annual_return_id'];
		$get_dangerous_operation_details = get_dangerous_operation($annual_return_ID);
		
		if($form_state['values']['op'] == "+ Add Dangerous Process or Operation") {
			if($form_state['values']['dangerous_operation_name'] == '') {
				form_set_error('Dangerous Process or Operations', t('You have to enter Name of the dangerous process or operations carried on!'));		
			} else {
				if($form_state['values']['avg_persons_employed_daily_in_operation'] == '') {
					form_set_error('Dangerous Process or Operations', t('You have to enter Average number of persons employed daily in each of the processes or operations!'));		
				}	
			}
		}
		
		if($form_state['values']['op'] == 'Save & Continue') {
			if($form_state['values']['dangerous_operation_process_in_factory'] == 'Yes' && count($get_dangerous_operation_details) < 1) {
				//drupal_set_message(t('You have to entered atleast 1 Dangerous Process or Operations!'), 'error');
				form_set_error('Dangerous Process or Operations', t('You have to enter atleast 1 Dangerous Process or Operations!'));	
			}
		}
		
	}
	
	function dangerous_operation_factories_act_submit($form, &$form_state){
		//echo '<pre>'; print_r($form_state); die();
		
		global $base_root,$base_path,$user;
		$uid 							= $user->uid;
		
		$annual_return_ID = $form_state['values']['annual_return_id'];
		$factory_id = $form_state['values']['factory_id'];
		
		$val = $form_state['values'];
		
		$get_factory_info = get_annual_return_factory_information($annual_return_ID);
		
		$get_dangerous_operation_details = get_dangerous_operation($annual_return_ID);
		
		if($val['dangerous_operation_process_in_factory'] == 'Yes') {
			$dangerous_operation_name = $val['dangerous_operation_name'];
			$avg_persons_employed_daily_in_operation = $val['avg_persons_employed_daily_in_operation'];
			
			$annual_return_update = array(
				'dangerous_operation_process_in_factory' => $val['dangerous_operation_process_in_factory'],
				'modification_date'	   => date('Y-m-d H:i:s'),
			);
			db_update('fa_annual_return')->fields($annual_return_update)->condition('id', $annual_return_ID, '=')->execute();
			
			if($val['op'] == "+ Add Dangerous Process or Operation") {
			
				$dangerous_operation = array(
					'annual_return_id' => $val['annual_return_id'],
					
					'dangerous_operation_name' => $dangerous_operation_name,
					'avg_persons_employed_daily_in_operation' => $avg_persons_employed_daily_in_operation,
									
					'uid' => $uid,
					'created_date'		   => date('Y-m-d'),
				);
				$dangerous_operation_id = db_insert('fa_ar_dangerous_operation_factory_act')->fields($dangerous_operation)->execute();
			}
			
			if($val['op'] == 'Save & Continue') {
				drupal_goto('applicant/factories-act-apply/safety_officers/'.encryption_decryption_fun('encrypt', $annual_return_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));	
			}
		} else if($val['dangerous_operation_process_in_factory'] == 'No') {
			
			if(!empty($get_dangerous_operation_details) && $get_factory_info->dangerous_operation_process_in_factory == 'Yes'){
				$query = db_delete('fa_ar_dangerous_operation_factory_act');
				$query->condition('annual_return_id', $annual_return_ID,'=');
				$query->execute();
			}
			
			$annual_return_update = array(
				'dangerous_operation_process_in_factory' => $val['dangerous_operation_process_in_factory'],
				'modification_date'	   => date('Y-m-d H:i:s'),
			);
			db_update('fa_annual_return')->fields($annual_return_update)->condition('id', $annual_return_ID, '=')->execute();
			
			drupal_goto('applicant/factories-act-apply/safety_officers/'.encryption_decryption_fun('encrypt', $annual_return_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));	
		}
		
		
		
		//$form_state['rebuild'] = true;		
		
		
		
		
	}
	
	
	function view_dangerous_operation_details($annual_return_ID, $factory_id){ //echo 'A-'.$form_id.' B-'.$reference_id.' C-'.$factory_id; die;
		
		$get_factory_info = get_annual_return_factory_information($annual_return_ID);
		$get_dangerous_operation_details 			= array();
		$type					= '';
		$details				= '';
	
		$get_dangerous_operation_details 			= get_dangerous_operation($annual_return_ID);
		
		$Wcounter		= 0;
		$per_page		= 5;
		$current_page 	= pager_default_initialize(count($get_dangerous_operation_details), $per_page);
		$chunks 		= array_chunk($get_dangerous_operation_details, $per_page);
		if($current_page>0){
			$Wcounter 	= $current_page*$per_page;
		}
		$header			= array(
							array('data' => 'Sl. No'),
							array('data'=> 'Dangerous Operation Name'),
							array('data'=> 'Avg Persons Employed Daily in Operation'),
							array('data'=> 'Action'),	
						);
						
		if(!empty($get_dangerous_operation_details) && $get_factory_info->dangerous_operation_process_in_factory == 'Yes'){
			
			foreach($chunks[$current_page] as $dangerous_operation_details){ 
				$Wcounter++;
				
				$onclick="return confirm('Are you sure you want to delete?')";
				
				$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/factories-act-apply/del_dangerous_operation/'.encryption_decryption_fun('encrypt',  
				$dangerous_operation_details->id).'/'.encryption_decryption_fun('encrypt', $dangerous_operation_details->annual_return_id).'/'.encryption_decryption_fun('encrypt', 
				$factory_id),array('html' => TRUE, 'attributes'=>array('onclick' => $onclick, 'title' => 'Delete')));	//,'class'=>array('red','use-ajax')
				
				$rows[] 	= array( 
									array('data' =>$Wcounter,'class' => array('')),
									array('data' =>$dangerous_operation_details->dangerous_operation_name,'class' => array('')),
									array('data' =>$dangerous_operation_details->avg_persons_employed_daily_in_operation,'class' => array('')),
									array('data' =>$delLink ,'class' => array('')),
									);
					} 
			}
			$output = theme_table(
				array(
					  'header' => $header,
					  'rows' => $rows,
					  'attributes' => array('id'=>'view_dangerous_operation_details_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
					  'sticky' => true,
					  'caption' => 'All Dangerous Operation List',
					  'colgroups' => array(),
					  'empty' => t("No data found!") // The message to be displayed if table is empty
					)
				).theme('pager');	
				return $output;	
	}
	
	function del_dangerous_operation_details($id, $annual_return_ID, $factory_id) {//die;
		//drupal_add_library('system', 'drupal.ajax');
	
		$dangerous_id 	  	= encryption_decryption_fun('decrypt', $id);
		$annual_return_id  	= encryption_decryption_fun('decrypt', $annual_return_ID);
		
		if($dangerous_id != 0) {
			$query = db_delete('fa_ar_dangerous_operation_factory_act');
			$query->condition('id', $dangerous_id,'=');
			$query->condition('annual_return_id', $annual_return_id,'=');
			$query->execute();
		}
		
		drupal_goto('applicant/factories-act-apply/dangerous_operation/'.$annual_return_ID.'/'.$factory_id);

		/*$commands = array();
		$commands[] = ajax_command_replace('#view_dangerous_operation_id', "<div id ='view_dangerous_operation_id'><div class='col-md-12 col-xs-12'>".view_dangerous_operation_details($annual_return_ID, $factory_id).'</div></div>');
		$page = array('#type' => 'ajax', '#commands' => $commands);
		ajax_deliver($page);*/	
		
	}
	
	function get_ajax_dangerous_operation_process($form, $form_state){
	  
		$commands[] = ajax_command_replace('#dangerous_operation_info_id', drupal_render($form['dangerous_operation']['dangerous_operation_info']));
		$commands[] = ajax_command_replace('#dangerous_operation_name_id', drupal_render($form['dangerous_operation']['dangerous_operation_name']));
		$commands[] = ajax_command_replace('#avg_persons_employed_daily_in_operation_id', drupal_render($form['dangerous_operation']['avg_persons_employed_daily_in_operation']));
		
		$commands[] = ajax_command_replace('#add_dangerous_operation_id', drupal_render($form['dangerous_operation']['add_dangerous_operation']));
		$commands[] = ajax_command_replace('#view_dangerous_operation_id', drupal_render($form['dangerous_operation']['view_dangerous_operation']));
	 
	 	$commands[] = ajax_command_replace('#dangerous_operation_submit_id', drupal_render($form['dangerous_operation_submit']['submit']));
	 	return array('#type' => 'ajax', '#commands' => $commands);
	}