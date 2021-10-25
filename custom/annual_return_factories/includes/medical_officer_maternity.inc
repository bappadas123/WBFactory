<?php

	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
  	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	function medical_officer_maternity($form, &$form_state, $annual_returnID = '', $factoryID = '') {
	
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
		
		$get_suggestion_scheme_details = get_suggestion_scheme($annual_return_ID);
		if($get_suggestion_scheme_details->annual_return_id == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/factories-act-apply/suggestion_scheme/'.$annual_returnID.'/'.$factoryID) ;
		}
		
		
		$get_wages_paid_include_deduction = get_total_wages_paid_include_deduction($annual_return_ID);
		$get_disbursement_fine_funds = get_disbursement_fine_funds($annual_return_ID);
		$get_factory_act_all_data = get_factory_act_all_data($annual_return_ID);
		
		$get_medical_officer = get_medical_officer($annual_return_ID);
		
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
		
		if($get_factory_info->factories_act_flag == 1 && $get_factory_act_all_data->ar_id != NULL) {
			$factories_act_edit = l('Factories Rules Edit', 'applicant/factories-act-apply/dangerous_operation/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		} else {
			$factories_act_edit = '';
		}
		
		$back_link = 'applicant/factories-act-apply/suggestion_scheme';
		
		$form['medical_officer'] = array(
		'#type' => 'fieldset',
		'#title' => t('Medical Officer Details'),
		'#collapsible' => TRUE, // Added
		'#collapsed' => FALSE // Added 
		);
		
		$options_medical_officer = array("Yes" => "Yes","No" => "No");										
		$form['medical_officer']['medical_officer_attached_factory']	=	array(
			'#title' 			=> t('<strong>1. Medical Officer, if any, attached to the factory</strong>'),
			'#type'				=> 'radios',
			'#options' 			=> $options_medical_officer,
			//'#default_value'	=> !empty($get_medical_officer_hospital_details->medical_officer_attached_factory) ?  $get_medical_officer_hospital_details->medical_officer_attached_factory : '',
			'#default_value'	=> $get_factory_info->medical_officer_attached_factory,
			'#prefix' 			=> '<div class="row"><div id="medical_officer_attached_factory_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
			'#suffix' 			=> '</label></div></div>', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
			'#ajax' 			=> array(
											'event' => 'change',
											'effect' => 'fade',
											'callback' => 'get_ajax_medical_officer_details',
											'progress' => array(
												'type' => 'throbber',
												'message' => t('loading')
											)
			)
		);
		$value_medical_officer_attached_factory = isset($form_state['values']['medical_officer_attached_factory']) ? $form_state['values']['medical_officer_attached_factory'] : '';
		
		if($value_medical_officer_attached_factory == 'Yes') {
			
			$form['medical_officer']['medical_officer_name']	=	array(
				'#title' 			=> t('<strong>(a) Name</strong>'),
				'#type'				=>	'textfield',
				'#prefix'			=>	'<div id="medical_officer_name_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
				'#suffix'			=>	'</label></div></div>',
				'#attributes' 		=> array('class'=>array('')),
				//'#required' 		=> TRUE,
			);
			
			$form['medical_officer']['medical_officer_qualification']	=	array(
				'#title' 			=> t('<strong>(b) Qualification</strong>'),
				'#type'				=>	'textfield',	
				'#prefix'			=>	'<div id="medical_officer_qualification_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
				'#suffix'			=>	'</label></div></div>',
				'#attributes' 		=> array('class'=>array('')),
				//'#required' 		=> TRUE,
			);
			
			
			$options_resident_doctor = array("Yes" => "Yes","No" => "No");
			$form['medical_officer']['medical_officer_resident_doctor']	=	array(
				'#title' 			=> t('<strong>(c) Is he a resident doctor?</strong>'),
				'#type'				=> 'radios',
				'#options' 			=> $options_resident_doctor,
				'#prefix' 			=> '<div id="medical_officer_resident_doctor_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
				'#suffix' 			=> '</label></div></div>', 
				'#attributes' 		=> array('class'=>array('')),
				//'#required' 		=> TRUE,
				'#ajax' 			=> array(
												'event' => 'change',
												'effect' => 'fade',
												'callback' => 'get_ajax_resident_doctor_or_not',
												'progress' => array(
													'type' => 'throbber',
													'message' => t('loading')
												)
				)
			);
			$value_medical_officer_resident_doctor = isset($form_state['values']['medical_officer_resident_doctor']) ? $form_state['values']['medical_officer_resident_doctor'] : '';
			
			if($value_medical_officer_resident_doctor == 'No') {
				
				$form['medical_officer']['medical_officer_parttime_pay']	=	array(
					'#title' 			=> t('<strong>(d) If a part-time employee, how often does he pay visits to the factory</strong>'),
					'#type'				=>	'textfield',
					'#prefix'			=>	'<div id="medical_officer_parttime_pay_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
					'#suffix'			=>	'</label></div></div>',
					'#attributes' 		=> array('class'=>array('')),
					//'#required' 		=> TRUE,
				);		
				
			} else {
				
				$form['medical_officer']['medical_officer_parttime_pay']	=	array(	
					'#prefix'		=>	'<div id="medical_officer_parttime_pay_id">',
					'#suffix'		=>	'</div>',
				);	
			}
			
			$form['medical_officer']['add_medical_officer'] = array(
				'#prefix' 			=> '<div id="add_medical_officer_id"><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></div>',
				'#attributes'       => array('class' => array('btn btn-dark'),'style'=>'float: right;'),
				'#type' 			=> 'submit',
				'#value' 			=> t("+ Add Medical Officer Details"),
			);	
				
			$form['medical_officer']['view_medical_officer'] = array(
				'#prefix'			=> '<div id="view_medical_officer_id"><div class="col-md-12">',
				'#suffix' 		    => '</div></div></div>',
				'#type' 			=> 'markup',
				'#markup' 			=> view_medical_officer_details($annual_return_ID, $factory_id),
			);
			
			// Enter Medical Officer Details //
			if(!empty($get_medical_officer))
			{
				$form['medical_officer_submit']['submit'] = array (
					'#prefix' 		=> '<div id="medical_officer_submit_id">',  
					'#suffix' 		=> '</div>',
					'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
					'#type' 		=> 'submit',
					'#value'		=> 'Save & Continue'
				);
			} else {
				$form['medical_officer_submit']['submit'] = array (
					'#prefix' 		=> '<div id="medical_officer_submit_id">',  
					'#suffix' 		=> '</div>',
				);	
			}
			
			
		} else if($value_medical_officer_attached_factory == 'No') {
			
			$form['medical_officer']['medical_officer_name']	=	array(	
				'#prefix'		=>	'<div id="medical_officer_name_id">',
				'#suffix'		=>	'</div>',
			);
					
			$form['medical_officer']['medical_officer_qualification']	=	array(	
				'#prefix'		=>	'<div id="medical_officer_qualification_id">',
				'#suffix'		=>	'</div>',
			);
			
			$form['medical_officer']['medical_officer_resident_doctor']	=	array(	
				'#prefix'		=>	'<div id="medical_officer_resident_doctor_id">',
				'#suffix'		=>	'</div>',
			);
			
			$form['medical_officer']['medical_officer_parttime_pay']	=	array(	
				'#prefix'		=>	'<div id="medical_officer_parttime_pay_id">',
				'#suffix'		=>	'</div>',
			);
			
			$form['medical_officer']['add_medical_officer'] = array(
				'#prefix' 			=> '<div id="add_medical_officer_id">',
				'#suffix' 			=> '</div>',
			);	
				
			$form['medical_officer']['view_medical_officer'] = array(
				'#prefix'			=> '<div id="view_medical_officer_id">',
				'#suffix' 		    => '</div>',
			);
			
			$form['medical_officer_submit']['submit'] = array (
				'#prefix' 		=> '<div id="medical_officer_submit_id">',  
				'#suffix' 		=> '</div>',
				'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
				'#type' 		=> 'submit',
				'#value'		=> 'Save & Continue'
			);
			
		} else {
			
			//if($get_medical_officer[0]->annual_return_id != NULL && $get_factory_info->medical_officer_attached_factory == 'Yes') {
			if($get_factory_info->medical_officer_attached_factory == 'Yes') {	
			
				$form['medical_officer']['medical_officer_name']	=	array(
					'#title' 			=> t('<strong>(a) Name</strong>'),
					'#type'				=>	'textfield',
					'#prefix'			=>	'<div id="medical_officer_name_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
					'#suffix'			=>	'</label></div></div>',
					'#attributes' 		=> array('class'=>array('')),
					//'#required' 		=> TRUE,
				);
				
				$form['medical_officer']['medical_officer_qualification']	=	array(
					'#title' 			=> t('<strong>(b) Qualification</strong>'),
					'#type'				=>	'textfield',	
					'#prefix'			=>	'<div id="medical_officer_qualification_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
					'#suffix'			=>	'</label></div></div>', 
					'#attributes' 		=> array('class'=>array('')),
					//'#required' 		=> TRUE,
				);
				
				$options_resident_doctor = array("Yes" => "Yes","No" => "No");
				$form['medical_officer']['medical_officer_resident_doctor']	=	array(
					'#title' 			=> t('<strong>(c) Is he a resident doctor?</strong>'),
					'#type'				=> 'radios',
					'#options' 			=> $options_resident_doctor,
					'#prefix' 			=> '<div id="medical_officer_resident_doctor_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
					'#suffix' 			=> '</label></div></div>', 
					'#attributes' 		=> array('class'=>array('')),
					//'#required' 		=> TRUE,
					'#ajax' 			=> array(
												'event' => 'change',
												'effect' => 'fade',
												'callback' => 'get_ajax_resident_doctor_or_not',
												'progress' => array(
													'type' => 'throbber',
													'message' => t('loading')
												)
					)
												
				
				);
				$medical_officer_resident_doctor = isset($form_state['values']['medical_officer_resident_doctor']) ? $form_state['values']['medical_officer_resident_doctor'] : '';
				
				//if($get_medical_officer[0]->annual_return_id != NULL && $get_medical_officer[0]->medical_officer_resident_doctor == 'No') {die;
				if($medical_officer_resident_doctor == 'No') {
						
					$form['medical_officer']['medical_officer_parttime_pay']	=	array(
						'#title' 			=> t('<strong>(d) If a part-time employee, how often does he pay visits to the factory</strong>'),
						'#type'				=>	'textfield',
						'#prefix'			=>	'<div id="medical_officer_parttime_pay_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
						'#suffix'			=>	'</label></div></div>',
						'#attributes' 		=> array('class'=>array('')),
						//'#required' 		=> TRUE,
					);	
					
				} else {
					
					$form['medical_officer']['medical_officer_parttime_pay']	=	array(	
						'#prefix'		=>	'<div id="medical_officer_parttime_pay_id">',
						'#suffix'		=>	'</div>',
					);
					
				}
				
				$form['medical_officer']['add_medical_officer'] = array(
					'#prefix' 			=> '<div id="add_medical_officer_id"><div class="col-md-12 col-xs-12">',
					'#suffix' 			=> '</div></div>',
					'#attributes'       => array('class' => array('btn btn-dark'),'style'=>'float: right;'),
					'#type' 			=> 'submit',
					'#value' 			=> t("+ Add Medical Officer Details"),
				);	
					
				$form['medical_officer']['view_medical_officer'] = array(
					'#prefix'			=> '<div id="view_medical_officer_id"><div class="col-md-12">',
					'#suffix' 		    => '</div></div></div>',
					'#type' 			=> 'markup',
					'#markup' 			=> view_medical_officer_details($annual_return_ID, $factory_id),
				);
				
				// Enter Medical Officer Details //
				if(!empty($get_medical_officer))
				{
					$form['medical_officer_submit']['submit'] = array (
						'#prefix' 		=> '<div id="medical_officer_submit_id">',  
						'#suffix' 		=> '</div>',
						'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
						'#type' 		=> 'submit',
						'#value'		=> 'Save & Continue'
					);
				} else {
					$form['medical_officer_submit']['submit'] = array (
						'#prefix' 		=> '<div id="medical_officer_submit_id">',  
						'#suffix' 		=> '</div>',
					);	
				}
				
				
			} else if($get_factory_info->medical_officer_attached_factory == 'No') {
			
				$form['medical_officer']['medical_officer_name']	=	array(	
					'#prefix'		=>	'<div id="medical_officer_name_id">',
					'#suffix'		=>	'</div>',
				);
						
				$form['medical_officer']['medical_officer_qualification']	=	array(	
					'#prefix'		=>	'<div id="medical_officer_qualification_id">',
					'#suffix'		=>	'</div>',
				);
				
				$form['medical_officer']['medical_officer_resident_doctor']	=	array(	
					'#prefix'		=>	'<div id="medical_officer_resident_doctor_id">',
					'#suffix'		=>	'</div>',
				);
				
				$form['medical_officer']['medical_officer_parttime_pay']	=	array(	
					'#prefix'		=>	'<div id="medical_officer_parttime_pay_id">',
					'#suffix'		=>	'</div>',
				);
				
				$form['medical_officer']['add_medical_officer'] = array(
					'#prefix' 			=> '<div id="add_medical_officer_id">',
					'#suffix' 			=> '</div>',
				);	
					
				$form['medical_officer']['view_medical_officer'] = array(
					'#prefix'			=> '<div id="view_medical_officer_id">',
					'#suffix' 		    => '</div>',
				);
				
				$form['medical_officer_submit']['submit'] = array (
					'#prefix' 		=> '<div id="medical_officer_submit_id">',  
					'#suffix' 		=> '</div>',
					'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
					'#type' 		=> 'submit',
					'#value'		=> 'Save & Continue'
				);
				
			} else {
				
				$form['medical_officer']['medical_officer_name']	=	array(	
					'#prefix'		=>	'<div id="medical_officer_name_id">',
					'#suffix'		=>	'</div>',
				);
						
				$form['medical_officer']['medical_officer_qualification']	=	array(	
					'#prefix'		=>	'<div id="medical_officer_qualification_id">',
					'#suffix'		=>	'</div>',
				);
				
				$form['medical_officer']['medical_officer_resident_doctor']	=	array(	
					'#prefix'		=>	'<div id="medical_officer_resident_doctor_id">',
					'#suffix'		=>	'</div>',
				);
				
				$form['medical_officer']['medical_officer_parttime_pay']	=	array(	
					'#prefix'		=>	'<div id="medical_officer_parttime_pay_id">',
					'#suffix'		=>	'</div>',
				);
				
				$form['medical_officer']['add_medical_officer'] = array(
					'#prefix' 			=> '<div id="add_medical_officer_id">',
					'#suffix' 			=> '</div>',
				);	
					
				$form['medical_officer']['view_medical_officer'] = array(
					'#prefix'			=> '<div id="view_medical_officer_id">',
					'#suffix' 		    => '</div>',
				);
				
				$form['medical_officer_submit']['submit'] = array (
					'#prefix' 		=> '<div id="medical_officer_submit_id">',  
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
		
		$form['maternity_benefit_link_markup'] = array(
				
				'#type'		=> 'markup',
				'#prefix'	=> '<div class="row">
									<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
									'.$common_section_edit.$payment_wages_edit.$factories_act_edit.'',
				'#suffix' => '		</div>
								</div>',
		);
		
		return $form;
	
	
	}
	
	function medical_officer_maternity_validate($form, &$form_state){
		
		$annual_return_ID = $form_state['values']['annual_return_id'];
		$get_medical_officer = get_medical_officer($annual_return_ID);
		
		if($form_state['values']['op'] == "+ Add Medical Officer Details") {
			if($form_state['values']['medical_officer_name'] == '') {
				form_set_error('Medical Officer Details', t('You have to enter Name of the Medical Officer!'));		
			} else {
				if($form_state['values']['medical_officer_qualification'] == '') {
					form_set_error('Medical Officer Details', t('You have to enter Qualification of the Medical Officer!'));		
				} else {
					if($form_state['values']['medical_officer_resident_doctor'] == '') {
						form_set_error('Medical Officer Details', t('You have to select whether the Medical Officer is a Resident Doctor or Not!'));		
					} else {
						if($form_state['values']['medical_officer_resident_doctor'] == 'No') {
							if($form_state['values']['medical_officer_parttime_pay'] == '') {
								form_set_error('Medical Officer Details', t('You have to enter pay visits to the factory of the part-time Medical Officer!'));		
							}
						}
					}
				}
			}
		}
		
		if($form_state['values']['op'] == 'Save & Continue') {
			if($form_state['values']['medical_officer_attached_factory'] == 'Yes' && count($get_medical_officer) < 1) {
				//drupal_set_message(t('You have to entered atleast 1 Dangerous Process or Operations!'), 'error');
				form_set_error('Medical Officer Details', t('You have to enter atleast 1 Medical Officer Details!'));	
			}
		}
		
	}
	
	function medical_officer_maternity_submit($form, &$form_state){
		//echo '<pre>'; print_r($form_state); die();
		
		global $base_root,$base_path,$user;
		$uid 							= $user->uid;
		
		$annual_return_ID = $form_state['values']['annual_return_id'];
		$factory_id = $form_state['values']['factory_id'];
		
		$val = $form_state['values'];
		
		$get_factory_info = get_annual_return_factory_information($annual_return_ID);
		
		$get_medical_officer = get_medical_officer($annual_return_ID);
		
		if($val['medical_officer_attached_factory'] == 'Yes') {
			
			$annual_return_update = array(
				'medical_officer_attached_factory' => $val['medical_officer_attached_factory'],
				'modification_date'	   => date('Y-m-d H:i:s'),
			);
			db_update('fa_annual_return')->fields($annual_return_update)->condition('id', $annual_return_ID, '=')->execute();
			
			if($val['op'] == "+ Add Medical Officer Details") {
			
				$medical_officer = array(
					'annual_return_id' => $val['annual_return_id'],
					
					'medical_officer_name' => $val['medical_officer_name'],
					'medical_officer_qualification' => $val['medical_officer_qualification'],
					'medical_officer_resident_doctor' => $val['medical_officer_resident_doctor'],
					'medical_officer_parttime_pay' => $val['medical_officer_parttime_pay'],
									
					'uid' => $uid,
					'created_date'		   => date('Y-m-d'),
				);
				$medical_officer_id = db_insert('fa_ar_medical_officer')->fields($medical_officer)->execute();
			}
			
			if($val['op'] == 'Save & Continue') {
				drupal_goto('applicant/maternity-benefit-apply/hospital_details/'.encryption_decryption_fun('encrypt', $annual_return_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));	
			}
		} else if($val['medical_officer_attached_factory'] == 'No') {
			
			if(!empty($get_medical_officer) && $get_factory_info->medical_officer_attached_factory == 'Yes'){
				$query = db_delete('fa_ar_medical_officer');
				$query->condition('annual_return_id', $annual_return_ID,'=');
				$query->execute();
			}
			
			$annual_return_update = array(
				'medical_officer_attached_factory' => $val['medical_officer_attached_factory'],
				'modification_date'	   => date('Y-m-d H:i:s'),
			);
			db_update('fa_annual_return')->fields($annual_return_update)->condition('id', $annual_return_ID, '=')->execute();
			
			drupal_goto('applicant/maternity-benefit-apply/hospital_details/'.encryption_decryption_fun('encrypt', $annual_return_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));	
		}
		
	}
	
	function view_medical_officer_details($annual_return_ID, $factory_id){ //echo 'A-'.$form_id.' B-'.$reference_id.' C-'.$factory_id; die;
		
		$get_factory_info = get_annual_return_factory_information($annual_return_ID);
		$get_medical_officer_details 			= array();
		$type					= '';
		$details				= '';
	
		$get_medical_officer_details 	= get_medical_officer($annual_return_ID);
		
		$Wcounter		= 0;
		$per_page		= 5;
		$current_page 	= pager_default_initialize(count($get_medical_officer_details), $per_page);
		$chunks 		= array_chunk($get_medical_officer_details, $per_page);
		if($current_page>0){
			$Wcounter 	= $current_page*$per_page;
		}
		$header			= array(
							array('data' => 'Sl. No'),
							array('data'=> 'Medical Officer Name'),
							array('data'=> 'Medical Officer Qualification'),
							array('data'=> 'Resident Doctor'),
							array('data'=> 'Pay visits to the factory of part-time Medical Officer'),
							array('data'=> 'Action'),	
						);
						
		if(!empty($get_medical_officer_details) && $get_factory_info->medical_officer_attached_factory == 'Yes'){
			
			foreach($chunks[$current_page] as $medical_officer_details){ 
				$Wcounter++;
				
				$onclick="return confirm('Are you sure you want to delete?')";
				
				$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/maternity-benefit-apply/del_medical_officer/'.encryption_decryption_fun('encrypt',  
				$medical_officer_details->id).'/'.encryption_decryption_fun('encrypt', $medical_officer_details->annual_return_id).'/'.encryption_decryption_fun('encrypt', 
				$factory_id),array('html' => TRUE, 'attributes'=>array('onclick' => $onclick, 'title' => 'Delete')));	//,'class'=>array('red','use-ajax')
				
				$rows[] 	= array( 
									array('data' =>$Wcounter,'class' => array('')),
									array('data' =>$medical_officer_details->medical_officer_name,'class' => array('')),
									array('data' =>$medical_officer_details->medical_officer_qualification,'class' => array('')),
									array('data' =>$medical_officer_details->medical_officer_resident_doctor,'class' => array('')),
									array('data' =>$medical_officer_details->medical_officer_parttime_pay,'class' => array('')),
									array('data' =>$delLink ,'class' => array('')),
									);
					} 
			}
			$output = theme_table(
				array(
					  'header' => $header,
					  'rows' => $rows,
					  'attributes' => array('id'=>'view_medical_officer_details_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
					  'sticky' => true,
					  'caption' => 'All Medical Officer List',
					  'colgroups' => array(),
					  'empty' => t("No data found!") // The message to be displayed if table is empty
					)
				).theme('pager');	
				return $output;	
	}
	
	function del_medical_officer($id, $annual_return_ID, $factory_id) {//die;
		//drupal_add_library('system', 'drupal.ajax');
	
		$medical_officer_id = encryption_decryption_fun('decrypt', $id);
		$annual_return_id  	= encryption_decryption_fun('decrypt', $annual_return_ID);
		
		if($medical_officer_id != 0) {
			$query = db_delete('fa_ar_medical_officer');
			$query->condition('id', $medical_officer_id,'=');
			$query->condition('annual_return_id', $annual_return_id,'=');
			$query->execute();
		}
		
		drupal_goto('applicant/maternity-benefit-apply/medical_officer/'.$annual_return_ID.'/'.$factory_id);

		/*$commands = array();
		$commands[] = ajax_command_replace('#view_dangerous_operation_id', "<div id ='view_dangerous_operation_id'><div class='col-md-12 col-xs-12'>".view_dangerous_operation_details($annual_return_ID, $factory_id).'</div></div>');
		$page = array('#type' => 'ajax', '#commands' => $commands);
		ajax_deliver($page);*/	
		
	}
	
	
	function get_ajax_medical_officer_details($form, $form_state){
	  
		$commands[] = ajax_command_replace('#medical_officer_name_id', drupal_render($form['medical_officer']['medical_officer_name']));
		$commands[] = ajax_command_replace('#medical_officer_qualification_id', drupal_render($form['medical_officer']['medical_officer_qualification']));
		$commands[] = ajax_command_replace('#medical_officer_resident_doctor_id', drupal_render($form['medical_officer']['medical_officer_resident_doctor']));
		$commands[] = ajax_command_replace('#medical_officer_parttime_pay_id', drupal_render($form['medical_officer']['medical_officer_parttime_pay']));
		
		$commands[] = ajax_command_replace('#add_medical_officer_id', drupal_render($form['medical_officer']['add_medical_officer']));
		$commands[] = ajax_command_replace('#view_medical_officer_id', drupal_render($form['medical_officer']['view_medical_officer']));
		
		$commands[] = ajax_command_replace('#medical_officer_submit_id', drupal_render($form['medical_officer_submit']['submit']));
	  
	 	return array('#type' => 'ajax', '#commands' => $commands);
	}
	
	function get_ajax_resident_doctor_or_not($form, $form_state){
	  
		$commands[] = ajax_command_replace('#medical_officer_parttime_pay_id', drupal_render($form['medical_officer']['medical_officer_parttime_pay']));
	  
	 	return array('#type' => 'ajax', '#commands' => $commands);
	}