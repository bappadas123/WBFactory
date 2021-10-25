<?php

	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
  	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	function hospital_details_maternity($form, &$form_state, $annual_returnID = '', $factoryID = '') {
	
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
		$get_factory_act_all_data = get_factory_act_all_data($annual_return_ID);
		
		$get_hospital_details = get_hospital_details($annual_return_ID);
		
		$get_medical_officer = get_medical_officer($annual_return_ID);
		if($get_factory_info->medical_officer_attached_factory == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/maternity-benefit-apply/medical_officer/'.$annual_returnID.'/'.$factoryID) ;
		} else {
			if($get_factory_info->medical_officer_attached_factory == 'Yes') {
				if($get_medical_officer[0]->annual_return_id == NULL) {
					drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
					drupal_goto('applicant/maternity-benefit-apply/medical_officer/'.$annual_returnID.'/'.$factoryID) ;
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
		
		if($get_factory_info->factories_act_flag == 1 && $get_factory_act_all_data->ar_id != NULL) {
			$factories_act_edit = l('Factories Rules Edit', 'applicant/factories-act-apply/dangerous_operation/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		} else {
			$factories_act_edit = '';
		}
		
		
		$form['hospital_details'] = array(
		'#type' => 'fieldset',
		'#title' => t('Hospital Details'),
		'#collapsible' => TRUE, // Added
		'#collapsed' => FALSE // Added 
		);
												
		
		$options_hospital = array("Yes" => "Yes","No" => "No");
		$form['hospital_details']['hospital_attached_factory']	=	array(
			'#title' 			=> t('<strong>2. (a) Is there any hospital attached to the factory?</strong>'),
			'#type'				=>	'radios',
			'#options' 			=> $options_hospital,
			//'#default_value'	=> !empty($get_medical_officer_hospital_details->hospital_attached_factory) ?  $get_medical_officer_hospital_details->hospital_attached_factory : '',
			'#default_value'	=> $get_factory_info->hospital_attached_factory,
			'#prefix' 			=> '<div class="row"><div id="hospital_attached_factory_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
			'#suffix' 			=> '</label></div></div>', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
			'#ajax' 			=> array(
											'event' => 'change',
											'effect' => 'fade',
											'callback' => 'get_ajax_hospital_details',
											'progress' => array(
												'type' => 'throbber',
												'message' => t('loading')
											)
			)
										
		
		);
		$value_hospital_attached_factory = isset($form_state['values']['hospital_attached_factory']) ? $form_state['values']['hospital_attached_factory'] : '';
		
		if($value_hospital_attached_factory == 'Yes') {
			
			$form['hospital_details']['hospital_bed_for_women_emp']	=	array(
				'#title' 			=> t('<strong>(b) If so, how many beds are provided for women employees?</strong>'),
				'#type'				=>	'textfield',
				'#prefix'			=>	'<div id="hospital_bed_for_women_emp_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
				'#suffix'			=>	'</label></div></div>',
				'#attributes' 		=> array('class'=>array('')),
				//'#required' 		=> TRUE,
			);
			
			$options_lady_doctor = array("Yes" => "Yes","No" => "No");
			$form['hospital_details']['hospital_lady_doctor']	=	array(
				'#title' 			=> t('<strong>(c) Is there a lady doctor?</strong>'),
				'#type'				=> 'radios',
				'#options' 			=> $options_lady_doctor,
				'#prefix' 			=> '<div id="hospital_lady_doctor_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
				'#suffix' 			=> '</label></div></div>', 
				'#attributes' 		=> array('class'=>array('')),
				//'#required' 		=> TRUE,
				'#ajax' 			=> array(
												'event' => 'change',
												'effect' => 'fade',
												'callback' => 'get_ajax_lady_doctor',
												'progress' => array(
													'type' => 'throbber',
													'message' => t('loading')
												)
				)
											
			
			);
			$value_hospital_lady_doctor = isset($form_state['values']['hospital_lady_doctor']) ? $form_state['values']['hospital_lady_doctor'] : '';
			
			if($value_hospital_lady_doctor == 'Yes') {
				
				$form['hospital_details']['hospital_lady_doc_qualif']	=	array(
					'#title' 			=> t('<strong>(d) If so, what are her qualification?</strong>'),
					'#type'				=>	'textfield',
					'#prefix'			=>	'<div id="hospital_lady_doc_qualif_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
					'#suffix'			=>	'</label></div></div>',
					'#attributes' 		=> array('class'=>array('')),
					//'#required' 		=> TRUE,
				);
				
			} else {
				
				$form['hospital_details']['hospital_lady_doc_qualif']	=	array(	
					'#prefix'		=>	'<div id="hospital_lady_doc_qualif_id">',
					'#suffix'		=>	'</div>',
				);
				
			}
			
			$options_qualif_midwife = array("Yes" => "Yes","No" => "No");
			$form['hospital_details']['hospital_qualif_midwife']	=	array(
				'#title' 			=> t('<strong>(e) Is there a qualified midwife?</strong>'),
				'#type'				=> 'radios',
				'#options' 			=> $options_qualif_midwife,
				'#prefix' 			=> '<div id="hospital_qualif_midwife_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
				'#suffix' 			=> '</label></div></div>', 
				'#attributes' 		=> array('class'=>array('')),
				//'#required' 		=> TRUE,
			);
			
			$form['hospital_details']['add_hospital_details'] = array(
				'#prefix' 			=> '<div id="add_hospital_details_id"><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></div>',
				'#attributes'       => array('class' => array('btn btn-dark'),'style'=>'float: right;'),
				'#type' 			=> 'submit',
				'#value' 			=> t("+ Add Hospital Details"),
			);	
				
			$form['hospital_details']['view_hospital_details'] = array(
				'#prefix'			=> '<div id="view_hospital_details_id"><div class="col-md-12">',
				'#suffix' 		    => '</div></div></div>',
				'#type' 			=> 'markup',
				'#markup' 			=> view_hospital_details($annual_return_ID, $factory_id),
			);
			
			// Enter Hospital Details //
			if(!empty($get_hospital_details))
			{
				$form['hospital_details_submit']['submit'] = array (
					'#prefix' 		=> '<div id="hospital_details_submit_id">',  
					'#suffix' 		=> '</div>',
					'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
					'#type' 		=> 'submit',
					'#value'		=> 'Save & Continue'
				);
			} else {
				$form['hospital_details_submit']['submit'] = array (
					'#prefix' 		=> '<div id="hospital_details_submit_id">',  
					'#suffix' 		=> '</div>',
				);	
			}
			
			
		} else if($value_hospital_attached_factory == 'No') {
			
			$form['hospital_details']['hospital_bed_for_women_emp']	=	array(
				'#prefix'			=>	'<div id="hospital_bed_for_women_emp_id">',
				'#suffix'			=>	'</div>',
			);
			
			$form['hospital_details']['hospital_lady_doctor']	=	array(
				'#prefix' 			=> '<div id="hospital_lady_doctor_id">',
				'#suffix' 			=> '</div>',
			);
				
			$form['hospital_details']['hospital_lady_doc_qualif']	=	array(	
				'#prefix'		=>	'<div id="hospital_lady_doc_qualif_id">',
				'#suffix'		=>	'</div>',
			);
			
			$form['hospital_details']['hospital_qualif_midwife']	=	array(
				'#prefix' 			=> '<div id="hospital_qualif_midwife_id">',
				'#suffix' 			=> '</div>',
			);
			
			$form['hospital_details']['add_hospital_details'] = array(
				'#prefix' 			=> '<div id="add_hospital_details_id">',
				'#suffix' 			=> '</div>',
			);	
				
			$form['hospital_details']['view_hospital_details'] = array(
				'#prefix'			=> '<div id="view_hospital_details_id">',
				'#suffix' 		    => '</div>',
			);
			
			$form['hospital_details_submit']['submit'] = array (
				'#prefix' 		=> '<div id="hospital_details_submit_id">',  
				'#suffix' 		=> '</div>',
				'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
				'#type' 		=> 'submit',
				'#value'		=> 'Save & Continue'
			);
			
			
		} else {
			
			//if($get_hospital_details[0]->annual_return_id != NULL && $get_factory_info->hospital_attached_factory == 'Yes') {
			if($get_factory_info->hospital_attached_factory == 'Yes') {
				
				$form['hospital_details']['hospital_bed_for_women_emp']	=	array(
					'#title' 			=> t('<strong>(b) If so, how many beds are provided for women employees?</strong>'),
					'#type'				=>	'textfield',
					'#prefix'			=>	'<div id="hospital_bed_for_women_emp_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
					'#suffix'			=>	'</label></div></div>', 
					'#attributes' 		=> array('class'=>array('')),
					//'#required' 		=> TRUE,
				);
				
				$options_lady_doctor = array("Yes" => "Yes","No" => "No");
				$form['hospital_details']['hospital_lady_doctor']	=	array(
					'#title' 			=> t('<strong>(c) Is there a lady doctor?</strong>'),
					'#type'				=> 'radios',
					'#options' 			=> $options_lady_doctor,
					'#prefix' 			=> '<div id="hospital_lady_doctor_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
					'#suffix' 			=> '</label></div></div>', 
					'#attributes' 		=> array('class'=>array('')),
					//'#required' 		=> TRUE,
					'#ajax' 			=> array(
													'event' => 'change',
													'effect' => 'fade',
													'callback' => 'get_ajax_lady_doctor',
													'progress' => array(
														'type' => 'throbber',
														'message' => t('loading')
													)
					)
												
				
				);
				$value_hospital_lady_doctor = isset($form_state['values']['hospital_lady_doctor']) ? $form_state['values']['hospital_lady_doctor'] : '';
				
				//if($get_hospital_details[0]->annual_return_id != NULL && $get_hospital_details[0]->hospital_lady_doctor == 'Yes') {
				if($value_hospital_lady_doctor == 'Yes') {	
				
					$form['hospital_details']['hospital_lady_doc_qualif']	=	array(
						'#title' 			=> t('<strong>(d) If so, what are her qualification?</strong>'),
						'#type'				=>	'textfield',
						'#prefix'			=>	'<div id="hospital_lady_doc_qualif_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
						'#suffix'			=>	'</label></div></div>', 
						'#attributes' 		=> array('class'=>array('')),
						//'#required' 		=> TRUE,
					);
					
				} else {
					
					$form['hospital_details']['hospital_lady_doc_qualif']	=	array(	
						'#prefix'		=>	'<div id="hospital_lady_doc_qualif_id">',
						'#suffix'		=>	'</div>',
					);
					
				}
				
				$options_qualif_midwife = array("Yes" => "Yes","No" => "No");
				$form['hospital_details']['hospital_qualif_midwife']	=	array(
					'#title' 			=> t('<strong>(e) Is there a qualified midwife?</strong>'),
					'#type'				=> 'radios',
					'#options' 			=> $options_qualif_midwife,
					'#prefix' 			=> '<div id="hospital_qualif_midwife_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
					'#suffix' 			=> '</label></div></div>', 
					'#attributes' 		=> array('class'=>array('')),
					//'#required' 		=> TRUE,
				);
				
				$form['hospital_details']['add_hospital_details'] = array(
					'#prefix' 			=> '<div id="add_hospital_details_id"><div class="col-md-12 col-xs-12">',
					'#suffix' 			=> '</div></div>',
					'#attributes'       => array('class' => array('btn btn-dark'),'style'=>'float: right;'),
					'#type' 			=> 'submit',
					'#value' 			=> t("+ Add Hospital Details"),
				);	
					
				$form['hospital_details']['view_hospital_details'] = array(
					'#prefix'			=> '<div id="view_hospital_details_id"><div class="col-md-12">',
					'#suffix' 		    => '</div></div></div>',
					'#type' 			=> 'markup',
					'#markup' 			=> view_hospital_details($annual_return_ID, $factory_id),
				);
				
				// Enter Hospital Details //
				if(!empty($get_hospital_details))
				{
					$form['hospital_details_submit']['submit'] = array (
						'#prefix' 		=> '<div id="hospital_details_submit_id">',  
						'#suffix' 		=> '</div>',
						'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
						'#type' 		=> 'submit',
						'#value'		=> 'Save & Continue'
					);
				} else {
					$form['hospital_details_submit']['submit'] = array (
						'#prefix' 		=> '<div id="hospital_details_submit_id">',  
						'#suffix' 		=> '</div>',
					);	
				}
			
				
			} else if($get_factory_info->hospital_attached_factory == 'No') {
			
				$form['hospital_details']['hospital_bed_for_women_emp']	=	array(
					'#prefix'			=>	'<div id="hospital_bed_for_women_emp_id">',
					'#suffix'			=>	'</div>',
				);
				
				$form['hospital_details']['hospital_lady_doctor']	=	array(
					'#prefix' 			=> '<div id="hospital_lady_doctor_id">',
					'#suffix' 			=> '</div>',
				);
					
				$form['hospital_details']['hospital_lady_doc_qualif']	=	array(	
					'#prefix'		=>	'<div id="hospital_lady_doc_qualif_id">',
					'#suffix'		=>	'</div>',
				);
				
				$form['hospital_details']['hospital_qualif_midwife']	=	array(
					'#prefix' 			=> '<div id="hospital_qualif_midwife_id">',
					'#suffix' 			=> '</div>',
				);
				
				$form['hospital_details']['add_hospital_details'] = array(
					'#prefix' 			=> '<div id="add_hospital_details_id">',
					'#suffix' 			=> '</div>',
				);	
					
				$form['hospital_details']['view_hospital_details'] = array(
					'#prefix'			=> '<div id="view_hospital_details_id">',
					'#suffix' 		    => '</div>',
				);
				
				$form['hospital_details_submit']['submit'] = array (
					'#prefix' 		=> '<div id="hospital_details_submit_id">',  
					'#suffix' 		=> '</div>',
					'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
					'#type' 		=> 'submit',
					'#value'		=> 'Save & Continue'
				);
				
				
			} else {
				
				$form['hospital_details']['hospital_bed_for_women_emp']	=	array(
					'#prefix'			=>	'<div id="hospital_bed_for_women_emp_id">',
					'#suffix'			=>	'</div>',
				);
				
				$form['hospital_details']['hospital_lady_doctor']	=	array(
					'#prefix' 			=> '<div id="hospital_lady_doctor_id">',
					'#suffix' 			=> '</div>',
				);
					
				$form['hospital_details']['hospital_lady_doc_qualif']	=	array(	
					'#prefix'		=>	'<div id="hospital_lady_doc_qualif_id">',
					'#suffix'		=>	'</div>',
				);
				
				$form['hospital_details']['hospital_qualif_midwife']	=	array(
					'#prefix' 			=> '<div id="hospital_qualif_midwife_id">',
					'#suffix' 			=> '</div>',
				);
				
				$form['hospital_details']['add_hospital_details'] = array(
					'#prefix' 			=> '<div id="add_hospital_details_id">',
					'#suffix' 			=> '</div>',
				);	
					
				$form['hospital_details']['view_hospital_details'] = array(
					'#prefix'			=> '<div id="view_hospital_details_id">',
					'#suffix' 		    => '</div>',
				);
				
				$form['hospital_details_submit']['submit'] = array (
					'#prefix' 		=> '<div id="hospital_details_submit_id">',  
					'#suffix' 		=> '</div>',
					/*'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
					'#type' 		=> 'submit',
					'#value'		=> 'Save & Continue'*/
				);
				
			}
			
		}
		
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'applicant/maternity-benefit-apply/medical_officer/'.$annual_returnID.'/'.$factoryID, array(
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
	
	function hospital_details_maternity_validate($form, &$form_state){
		
		$annual_return_ID = $form_state['values']['annual_return_id'];
		$get_hospital_details = get_hospital_details($annual_return_ID);
		
		if($form_state['values']['op'] == "+ Add Hospital Details") {
			if($form_state['values']['hospital_bed_for_women_emp'] == '') {
				form_set_error('Hospital Details', t('You have to enter How many beds are provided for women employees!'));		
			} else {
				if($form_state['values']['hospital_lady_doctor'] == '') {
					form_set_error('Hospital Details', t('You have to select Whether there a Lady Doctor or Not!'));		
				} else {
					if($form_state['values']['hospital_lady_doctor'] == 'Yes') {
						if($form_state['values']['hospital_lady_doc_qualif'] == '') {
							form_set_error('Hospital Details', t('You have to enter Qualification of the Lady Doctor!'));		
						}
					}
					
					if($form_state['values']['hospital_qualif_midwife'] == '') {
						form_set_error('Hospital Details', t('You have to select Whether there a qualified Midwife or Not!'));		
					}
				}
			}
		}
		
		if($form_state['values']['op'] == 'Save & Continue') {
			if($form_state['values']['hospital_attached_factory'] == 'Yes' && count($get_hospital_details) < 1) {
				//drupal_set_message(t('You have to entered atleast 1 Dangerous Process or Operations!'), 'error');
				form_set_error('Hospital Details', t('You have to enter atleast 1 Hospital Details!'));	
			}
		}
		
	}
	
	function hospital_details_maternity_submit($form, &$form_state){
		//echo '<pre>'; print_r($form_state); die();
		
		global $base_root,$base_path,$user;
		$uid 							= $user->uid;
		
		$annual_return_ID = $form_state['values']['annual_return_id'];
		$factory_id = $form_state['values']['factory_id'];
		
		$val = $form_state['values'];
		
		$get_factory_info = get_annual_return_factory_information($annual_return_ID);
		
		$get_hospital_details = get_hospital_details($annual_return_ID);
		
		if($val['hospital_attached_factory'] == 'Yes') {
			
			$annual_return_update = array(
				'hospital_attached_factory' => $val['hospital_attached_factory'],
				'modification_date'	   => date('Y-m-d H:i:s'),
			);
			db_update('fa_annual_return')->fields($annual_return_update)->condition('id', $annual_return_ID, '=')->execute();
			
			if($val['op'] == "+ Add Hospital Details") {
			
				$hospital_details = array(
					'annual_return_id' => $val['annual_return_id'],
					
					'hospital_bed_for_women_emp' => $val['hospital_bed_for_women_emp'],
					'hospital_lady_doctor' => $val['hospital_lady_doctor'],
					'hospital_lady_doc_qualif' => $val['hospital_lady_doc_qualif'],
					'hospital_qualif_midwife' => $val['hospital_qualif_midwife'],
									
					'uid' => $uid,
					'created_date'		   => date('Y-m-d'),
				);
				$hospital_details_id = db_insert('fa_ar_hospital_details')->fields($hospital_details)->execute();
			}
			
			if($val['op'] == 'Save & Continue') {
				drupal_goto('applicant/maternity-benefit-apply/emplm_dism_pay_bonus_women/'.encryption_decryption_fun('encrypt', $annual_return_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));	
			}
		} else if($val['hospital_attached_factory'] == 'No') {
			
			if(!empty($get_hospital_details) && $get_factory_info->hospital_attached_factory == 'Yes'){
				$query = db_delete('fa_ar_hospital_details');
				$query->condition('annual_return_id', $annual_return_ID,'=');
				$query->execute();
			}
			
			$annual_return_update = array(
				'hospital_attached_factory' => $val['hospital_attached_factory'],
				'modification_date'	   => date('Y-m-d H:i:s'),
			);
			db_update('fa_annual_return')->fields($annual_return_update)->condition('id', $annual_return_ID, '=')->execute();
			
			drupal_goto('applicant/maternity-benefit-apply/emplm_dism_pay_bonus_women/'.encryption_decryption_fun('encrypt', $annual_return_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));	
		}
		
	}
	
	function view_hospital_details($annual_return_ID, $factory_id){ //echo 'A-'.$form_id.' B-'.$reference_id.' C-'.$factory_id; die;
		
		$get_factory_info = get_annual_return_factory_information($annual_return_ID);
		$get_hospital_details 			= array();
		$type					= '';
		$details				= '';
	
		$get_hospital_details 			= get_hospital_details($annual_return_ID);
		
		$Wcounter		= 0;
		$per_page		= 5;
		$current_page 	= pager_default_initialize(count($get_hospital_details), $per_page);
		$chunks 		= array_chunk($get_hospital_details, $per_page);
		if($current_page>0){
			$Wcounter 	= $current_page*$per_page;
		}
		$header			= array(
							array('data' => 'Sl. No'),
							array('data'=> 'How many beds are provided for women employees'),
							array('data'=> 'Lady Doctor'),
							array('data'=> 'Qualification of Lady Doctor'),
							array('data'=> 'Qualified Midwife'),
							array('data'=> 'Action'),	
						);
						
		if(!empty($get_hospital_details) && $get_factory_info->hospital_attached_factory == 'Yes'){
			
			foreach($chunks[$current_page] as $hospital_details){ 
				$Wcounter++;
				
				$onclick="return confirm('Are you sure you want to delete?')";
				
				$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/maternity-benefit-apply/del_hospital_details/'.encryption_decryption_fun('encrypt',  
				$hospital_details->id).'/'.encryption_decryption_fun('encrypt', $hospital_details->annual_return_id).'/'.encryption_decryption_fun('encrypt', 
				$factory_id),array('html' => TRUE, 'attributes'=>array('onclick' => $onclick, 'title' => 'Delete')));	//,'class'=>array('red','use-ajax')
				
				$rows[] 	= array( 
									array('data' =>$Wcounter,'class' => array('')),
									array('data' =>$hospital_details->hospital_bed_for_women_emp,'class' => array('')),
									array('data' =>$hospital_details->hospital_lady_doctor,'class' => array('')),
									array('data' =>$hospital_details->hospital_lady_doc_qualif,'class' => array('')),
									array('data' =>$hospital_details->hospital_qualif_midwife,'class' => array('')),
									array('data' =>$delLink ,'class' => array('')),
									);
					} 
			}
			$output = theme_table(
				array(
					  'header' => $header,
					  'rows' => $rows,
					  'attributes' => array('id'=>'view_hospital_details_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
					  'sticky' => true,
					  'caption' => 'All Hospital Details List',
					  'colgroups' => array(),
					  'empty' => t("No data found!") // The message to be displayed if table is empty
					)
				).theme('pager');	
				return $output;	
	}
	
	function del_hospital_details($id, $annual_return_ID, $factory_id) {//die;
		//drupal_add_library('system', 'drupal.ajax');
	
		$hospital_details_id = encryption_decryption_fun('decrypt', $id);
		$annual_return_id  	 = encryption_decryption_fun('decrypt', $annual_return_ID);
		
		if($hospital_details_id != 0) {
			$query = db_delete('fa_ar_hospital_details');
			$query->condition('id', $hospital_details_id,'=');
			$query->condition('annual_return_id', $annual_return_id,'=');
			$query->execute();
		}
		
		drupal_goto('applicant/maternity-benefit-apply/hospital_details/'.$annual_return_ID.'/'.$factory_id);

		/*$commands = array();
		$commands[] = ajax_command_replace('#view_dangerous_operation_id', "<div id ='view_dangerous_operation_id'><div class='col-md-12 col-xs-12'>".view_dangerous_operation_details($annual_return_ID, $factory_id).'</div></div>');
		$page = array('#type' => 'ajax', '#commands' => $commands);
		ajax_deliver($page);*/	
		
	}
	
	
	function get_ajax_hospital_details($form, $form_state){
	  
		$commands[] = ajax_command_replace('#hospital_bed_for_women_emp_id', drupal_render($form['hospital_details']['hospital_bed_for_women_emp']));
		$commands[] = ajax_command_replace('#hospital_lady_doctor_id', drupal_render($form['hospital_details']['hospital_lady_doctor']));
		$commands[] = ajax_command_replace('#hospital_lady_doc_qualif_id', drupal_render($form['hospital_details']['hospital_lady_doc_qualif']));
		$commands[] = ajax_command_replace('#hospital_qualif_midwife_id', drupal_render($form['hospital_details']['hospital_qualif_midwife']));
		
		$commands[] = ajax_command_replace('#add_hospital_details_id', drupal_render($form['hospital_details']['add_hospital_details']));
		$commands[] = ajax_command_replace('#view_hospital_details_id', drupal_render($form['hospital_details']['view_hospital_details']));
		
		$commands[] = ajax_command_replace('#hospital_details_submit_id', drupal_render($form['hospital_details_submit']['submit']));
	  
	 	return array('#type' => 'ajax', '#commands' => $commands);
	}
	
	function get_ajax_lady_doctor($form, $form_state){
	  
		$commands[] = ajax_command_replace('#hospital_lady_doc_qualif_id', drupal_render($form['hospital_details']['hospital_lady_doc_qualif']));
	  	
	 	return array('#type' => 'ajax', '#commands' => $commands);
	}