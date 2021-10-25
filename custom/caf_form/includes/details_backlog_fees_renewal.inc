<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function details_backlog_fees_renewal($form, &$form_state,$serviceid,$factory_typeid,$applicationid,$number,$datevalidity,$flagmapp) {	
	global $base_root, $base_path, $user;
	
	
	$application_id 			= encryption_decryption_fun('decrypt', $applicationid);
	$service_id 				= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 			= encryption_decryption_fun('decrypt',$factory_typeid);
	$backlog_lic_reg_no 		= encryption_decryption_fun('decrypt', $number);
	$backlog_reg_lic_date 		= encryption_decryption_fun('decrypt', $datevalidity);
	$type_flag 					= encryption_decryption_fun('decrypt', $flagmapp);
	
	$get_fa_cafa 				= get_fa_cafa($application_id);
    $reference_no 				= $get_fa_cafa['reference_number'];
	$date_of_amenability 		= $get_fa_cafa['date_of_amenability'];
	$period_for_application 	= $get_fa_cafa['period_for_application'];
	$is_calculate				= $get_fa_cafa['is_calculate'];
	$application_status			= $get_fa_cafa['application_status'];
	$balance_amount				= $get_fa_cafa['balance_amount'];
	$previous_excess_paid		= $get_fa_cafa['previous_excess_paid']+$balance_amount;
	//echo 'Application no.--'.$application_id.'<br/>Service no.--'.$service_id.'<br/>Factory id.--'.$factory_type_id.'<br/>LICE OR REG NO.--'.$backlog_lic_reg_no.'<br/>DATE.--'.$backlog_reg_lic_date.'<br/>FLAG.--'.$type_flag;die();
    $form = array();
	$form['#attributes'] 	= array('enctype' => "multipart/form-data");
	$form['applicationid_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $applicationid
	);
	$form['serviceid_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $serviceid,
	);
	$form['factorytypeid_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $factory_typeid		 
	);
	$form['reference_no_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=>  encryption_decryption_fun('encrypt',$reference_no),	 
	);
	
	$form['previousexcesspaid_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> encryption_decryption_fun('encrypt',$previous_excess_paid),
	);
	$form['date_of_amenability_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> encryption_decryption_fun('encrypt',$date_of_amenability),
	);
	$form['period_for_application_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> encryption_decryption_fun('encrypt',$period_for_application),
	);
	
	$manual_payment = manual_payment_deatils($application_id,$service_id,$factory_type_id,$reference_no);
	foreach($manual_payment as $row_payment){
			$is_payment_mad 		= $row_payment->is_payment_mad;
			$brn_grn_challan_no 	= $row_payment->brn_grn_challan_no;
			$date_payment 			= $row_payment->date_payment;
			$payment_amount 		= $row_payment->payment_amount;
		 }
	$radios_options = array('Yes'=>"Yes",'No'=>"No");
	$manual_payment = manual_payment_deatils($application_id,$service_id,$factory_type_id,$reference_no);
	foreach($manual_payment as $row_payment){
			$payment_id = $row_payment->id;
	}
	 $form['yearly_worker']['form_start'] = array(
			'#prefix' 			=> '<div class = "box-body"><div class="box-header with-border">
              <h3 class="box-title">Fees Calculation for Renewal<br/> Amenability Date:-'.date("dS M Y",strtotime($date_of_amenability)).'<br/>Period of license:-'.$period_for_application.'Year(s)</h3>
			  </div>',
			
		   
		 );
	if(empty($payment_id)){
		$form['yearly_worker']['manual_payment']= array(
				'#prefix' 			=> '<div class="col-xs-12">',
		   		'#suffix' 			=> '</div></div><div></div>',
				'#type'		 		=> 'radios',
				'#title'			=>	t('Do you have any previous payment'),
				'#options'   		=> $radios_options,	
				'#default_value' 	=> !empty($is_payment_mad)?$is_payment_mad:'No',
				'#required'			=> TRUE,
			    '#ajax'				=> array(
											'event' 		=> 'change',
											'effect' 		=> 'fade',			
											'callback'		=> 'manual_ajax_payment',
											'progress'		=>	array(
											'type'			=>'throbber',
											'message'		=> t('loading'),
											),
				)
					
			   
	 );
	}else{
		$form['yearly_worker']['manual_payment']= array(
				'#prefix' 			=> '<div class = "box-body"><div class="col-xs-12">',
		   		'#suffix' 			=> '</div></div><div></div>',
				'#type'		 		=> 'radios',
				'#title'			=>	t('Do you have any previous payment'),
				'#options'   		=> $radios_options,	
				'#default_value' 	=> !empty($is_payment_mad)?$is_payment_mad:'No',
				'#disabled' 		=> 'disabled',
				'#required'			=> TRUE,
			    '#ajax'				=> array(
											'event' 		=> 'change',
											'effect' 		=> 'fade',			
											'callback'		=> 'manual_ajax_payment',
											'progress'		=>	array(
											'type'			=>'throbber',
											'message'		=> t('loading'),
											),
				)
					
			   
	 );
	}
	
	 
	 $form['yearly_worker']['challan_number'] = array(
			'#prefix' 			=> '<div class="row>"<div id="challan_number_div">',
			'#suffix' 			=> '</div>',
		   
		 );
	$form['yearly_worker']['payment_date'] = array(
			'#prefix' 			=> '<div id="payment_date_div">',
			'#suffix' 			=> '</div>',
		   
	);
	$form['yearly_worker']['payment_amount'] = array(
			'#prefix' 			=> '<div id="payment_amount_div">',
			'#suffix' 			=> '</div>',
		   
	);
	$form['yearly_worker']['upload_chanal'] = array(
			'#prefix' 			=> '<div id="edit-upload-chanal-ajax-wrapper">',
			'#suffix' 			=> '</div>',
		   
	);
	$form['yearly_worker']['add_payment'] = array(
			'#prefix' 			=> '<div id="add_payment_div">',
			'#suffix' 			=> '</div>',
		   
	);
	$form['yearly_worker']['del_payment'] 	= array(
			'#prefix'			 	=> '<div id="del_payment_div">',
			'#suffix' 				=> '</div>',
	);
	$form['yearly_worker']['payment_deatails'] = array(
			'#prefix' 			=> '<div id="payment_deatails_div">',
			'#suffix' 			=> '</div>',
		   
	);
	$form['yearly_worker']['worker_year_table'] = array(
			'#prefix' 			=> '<div id="fees_details_div">',
			'#suffix' 			=> '</div>',
		   
	);
	$form['yearly_worker']['fees_calculation'] = array(
			'#prefix' 			=> '<div id="fees_calculation_div">',
			'#suffix' 			=> '</div></div>',
		   
	);
	$form['yearly_worker']['fees_pay'] 	= array(
			'#prefix' 			=> '<div id="fees_pay_div">',
			'#suffix' 			=> '</div>',	
	);
	$manual_payment_decission = isset($form_state['values']['manual_payment'])? $form_state['values']['manual_payment'] : (!empty($is_payment_mad)?$is_payment_mad:'No');
	if($manual_payment_decission == 'Yes'){
		 $form['yearly_worker']['challan_number'] 	= array(
				 '#prefix' 			=> '<div id="challan_number_div"><div class="col-xs-4">',
				 '#suffix' 			=> '</div></div>',
				 '#attributes' 		=> array('class'=>array('form-control')),
				 '#title'			=>	t('GRN/BRN/Challan number'),
				 '#default_value'	=> !empty($brn_grn_challan_no) ? $brn_grn_challan_no	:'',
				 '#type' 			=> 'textfield',
				 '#required' 		=> TRUE,
		);
		$form['yearly_worker']['payment_date'] 	= array(
				 '#prefix' 			=> '<div id="payment_date_div"><div class="col-xs-4">',
				 '#suffix' 			=> '</div></div>',
				 '#attributes' 		=> array('class'=>array('form-control')),
				 '#title'			=>	t('Payment Date'),
				 '#default_value'	=> !empty($date_payment) ? $date_payment	:'',
				 '#type' 			=> 'textfield',
				 '#attributes' 		=> array('class'=>array('datepicker_cls')),
				 '#required' 		=> TRUE,
		);
		$form['yearly_worker']['payment_amount'] 	= array(
				 '#prefix' 			=> '<div id="payment_amount_div"><div class="col-xs-4">',
				 '#suffix' 			=> '</div>',
				 '#attributes' 		=> array('class'=>array('form-control')),
				 '#title'			=>	t('Payment Amount'),
				 '#default_value'	=> !empty($payment_amount) ? $payment_amount	:'',
				 '#type' 			=> 'textfield',
				 '#required' 		=> TRUE,
		);
		$form['yearly_worker']['markup_start'] 	= array(
				'#prefix' 			=> '<div id="edit-upload-chanal-ajax-wrapper"><div class="col-xs-4">',
				
				
		);
		$form['yearly_worker']['upload_chanal'] = array(
				'#type' 				 => 'managed_file',
				'#title'				 => 'Upload Challan',
				'#upload_validators' 	 => array('file_validate_extensions' => array('pdf'), 'file_validate_size' => array(50*1024*1024)),
				'#upload_location' 		 => 'public://upload/challan_doc/',
				'#process' 				 => array('import_my_file_element_process'),
				'#attributes' 			 => array('id' => '','autocomplete' => 'off','class'=>array('form-control')),
				
			  
					
		);
		$form['yearly_worker']['markup_end'] 	= array(
				'#suffix' 			=> '</div></div></div>',
				
		);
		if($is_calculate !=1){
			$form['yearly_worker']['add_payment'] 	= array(
				'#prefix'			 	=> '<div id="add_payment_div"><div class="col-xs-6">',
				'#suffix' 				=> '</div></div>',
				'#type' 				=> 'submit',
				'#value' 				=> t('Add payment'),
				'#attributes' 			=> array('class' => array('btn btn-info pull-right')),
			
			);
		}
		if($is_calculate !=1){
			$form['yearly_worker']['del_payment'] 	= array(
				'#prefix'			 	=> '<div id="del_payment_div"><div class="col-xs-6">',
				'#suffix' 				=> '</div></div>',
				'#type' 				=> 'submit',
				'#value' 				=> t('Delete payment'),
				'#attributes' 			=> array('class' => array('btn btn-info pull-right')),
			);
		}
		
	$form['yearly_worker']['payment_deatails'] = array(
			'#prefix' 			=> '<div id="payment_deatails_div"><div class="col-md-12">'.view_payment_deatils($application_id,$service_id,$factory_type_id,$reference_no),
			'#suffix' 			=> '</div></div>'
	);
		
	
	if(!empty($payment_id)){
		if($is_calculate !=1){
			$form['yearly_worker']['fees_calculation'] 	= array(
						'#prefix' 			=> '<div id="fees_calculation_div"><div class="col-xs-12">',
						'#suffix' 			=> '</div></div>',
						'#type' 				=> 'submit',
						'#submit'				=> array(),
						'#ajax' 				=> array(
														'callback' 		=> 'calculate_manuall_fees',
													),
						'#value' 				=> t('Fees Calculate'),
						'#attributes' 			=> array('class' => array('btn btn-info pull-right')),
			
					);
			}
			
		}

	if($is_calculate==1){
		if($application_status == 'F'){
			$form['yearly_worker']['fees_pay'] 	= array(
			'#prefix' 			=> '<div id="fees_pay_div"><div class="col-xs-12">',
			'#suffix' 			=> '</div></div>',
			'#type' 			=> 'submit',
			'#value' 			=> t('Pay now'),
			'#attributes' 		=> array('class' => array('btn btn-info pull-right')),
			
			);
		}
		
		if($factory_type_id == 1){
			$form['yearly_worker']['worker_year_table'] 	= array(
		 		'#prefix' 			=> '<div id="fees_details_div">',
			 	'#suffix' 			=> '</div>',
  				'#type'				=> 'markup',
				'#markup'			=> show_fees_registration($application_id,$service_id,$factory_type_id,$reference_no,$date_of_amenability,$period_for_application,$previous_excess_paid)
			);
		}
		
		if($factory_type_id == 2){
			$form['yearly_worker']['worker_year_table'] 	= array(
				'#prefix' 			=> '<div id="fees_details_div">',
			 	'#suffix' 			=> '</div>',
  				'#type'				=> 'markup',
				'#markup'			=> show_fees_registration_2mii($application_id,$service_id,$factory_type_id,$reference_no,$date_of_amenability,$period_for_application,$previous_excess_paid)
			);
		}
	
		if($factory_type_id == 3){
			$form['yearly_worker']['worker_year_table'] 	= array(
  				'#type'				=> 'markup',
				'#prefix' 			=> '<div id="fees_details_div">',
			 	'#suffix' 			=> '</div>',
				'#markup'			=> show_fees_registration_section_85($application_id,$service_id,$factory_type_id,$reference_no,$date_of_amenability,$period_for_application)
			);
		}
	}
	}
 	if($manual_payment_decission == 'No'){  
		  $form['yearly_worker']['challan_number'] = array(
			'#prefix' 			=> '<div id="challan_number_div">',
			'#suffix' 			=> '</div>',
		   
		 );
	$form['yearly_worker']['payment_date'] = array(
			'#prefix' 			=> '<div id="payment_date_div">',
			'#suffix' 			=> '</div>',
		   
		 );
	$form['yearly_worker']['payment_amount'] = array(
			'#prefix' 			=> '<div id="payment_amount_div">',
			'#suffix' 			=> '</div>',
		   
		 );
	$form['yearly_worker']['upload_chanal'] = array(
			'#prefix' 			=> '<div id="edit-upload-chanal-ajax-wrapper">',
			'#suffix' 			=> '</div>',
		   
		 );
	$form['yearly_worker']['add_payment'] = array(
			'#prefix' 			=> '<div id="add_payment_div">',
			'#suffix' 			=> '</div>',
		   
		 );
	$form['yearly_worker']['fees_calculation'] 	= array(
			'#prefix' 			=> '<div id="fees_calculation_div">',
			'#suffix' 			=> '</div></div>',
			);
	if($factory_type_id == 1){
		$form['yearly_worker']['worker_year_table'] 	= array(
		 		'#prefix' 			=> '<div id="fees_details_div">',
			 	'#suffix' 			=> '</div>',
  				'#type'				=> 'markup',
				'#markup'			=> show_fees_registration($application_id,$service_id,$factory_type_id,$reference_no,$date_of_amenability,$period_for_application,$previous_excess_paid)
				
  
			);
	}if($factory_type_id == 2){
		$form['yearly_worker']['worker_year_table'] 	= array(
				'#prefix' 			=> '<div id="fees_details_div">',
			 	'#suffix' 			=> '</div>',
  				'#type'				=> 'markup',
				'#markup'			=> show_fees_registration_2mii($application_id,$service_id,$factory_type_id,$reference_no,$date_of_amenability,$period_for_application)
				
  
			);
	}if($factory_type_id == 3){
		
		$form['yearly_worker']['worker_year_table'] 	= array(
  				'#type'				=> 'markup',
				'#prefix' 			=> '<div id="fees_details_div">',
			 	'#suffix' 			=> '</div>',
				'#markup'			=> show_fees_registration_section_85($application_id,$service_id,$factory_type_id,$reference_no,$date_of_amenability,$period_for_application)
				
  
			);
	}
	if($application_status == 'F'){
		$form['yearly_worker']['fees_pay'] 	= array(
			'#prefix' 			=> '<div id="fees_pay_div"><div class="col-xs-12">',
			'#suffix' 			=> '</div></div>',
			'#type' 			=> 'submit',
			'#value' 			=> t('Pay now'),
			'#attributes' 		=> array('class' => array('btn btn-info pull-right')),
			
	);
	}
		
			


		
	 }
	 
 	return $form; 
        
}
		 
function manual_ajax_payment($form, $form_state){
	$commands = array();
	$commands[] = ajax_command_replace('#challan_number_div', drupal_render($form['yearly_worker']['challan_number']));
	$commands[] = ajax_command_replace('#payment_date_div', drupal_render($form['yearly_worker']['payment_date']));
	$commands[] = ajax_command_replace('#payment_amount_div', drupal_render($form['yearly_worker']['payment_amount']));
	$commands[] = ajax_command_replace('#fees_details_div', drupal_render($form['yearly_worker']['worker_year_table']));
	$commands[] = ajax_command_replace('#add_payment_div', drupal_render($form['yearly_worker']['add_payment']));
	$commands[] = ajax_command_replace('#payment_deatails_div', drupal_render($form['yearly_worker']['payment_deatails']));
	$commands[] = ajax_command_replace('#fees_calculation_div', drupal_render($form['yearly_worker']['fees_calculation']));
	$commands[] = ajax_command_replace('#del_payment_div', drupal_render($form['yearly_worker']['del_payment']));
	$commands[] = ajax_command_replace('#fees_pay_div', drupal_render($form['yearly_worker']['fees_pay']));
	$commands[] = ajax_command_replace('#edit-upload-chanal-ajax-wrapper', drupal_render($form['yearly_worker']['upload_chanal']));
	return array('#type' => 'ajax', '#commands' => $commands);
}


function details_fees_renewal_submit($form, &$form_state){
	global $user;
	$val   								= 	$form_state['values'];
	
	$factory_type						= 	encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$service_id							= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$application_id						= 	encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$reference_no						= 	encryption_decryption_fun('decrypt',$val['reference_no_hidden']);	
	$previousexcess_paid_hidden			= 	encryption_decryption_fun('decrypt',$val['previousexcesspaid_hidden']);
	$date_of_amenability				= 	encryption_decryption_fun('decrypt',$val['date_of_amenability_hidden']);
	$period_for_application				= 	encryption_decryption_fun('decrypt',$val['period_for_application_hidden']);
	$challan_number						= 	$val['challan_number'];
	$payment_date						= 	$val['payment_date'];
	$payment_amount						= 	$val['payment_amount'];
	$is_payment_mad						= 	$val['manual_payment'];
	$upload_chanal 						= 	file_load($val['upload_chanal']);
	
	if($val['op'] =="Add payment"){
		if($upload_chanal != "" ){
					$upload_chanal->status = FILE_STATUS_PERMANENT;
					file_save($upload_chanal);
					$upload_chanal_fid			=	$upload_chanal->fid;
					if(!empty($upload_chanal->fid)){
						$upload_application =array(
							'filename'	=> $upload_chanal->filename,
							'file_uri'	=> $upload_chanal->uri,
							'created_by'=> $upload_chanal->uid,
							'fid'		=> $upload_chanal->fid,
						);
					}
					$file_manage_id = db_insert('fa_file_managed_custom')->fields($upload_application)->execute();
					
					$add_payment_details = array(
					'brn_grn_challan_no' 			=> $challan_number,
					'date_payment'					=> $payment_date,
					'payment_amount' 				=> $payment_amount,
					'factory_type' 					=> $factory_type,
					'created_date' 					=> date("Y-m-d"),
					'created_by'   					=> $user->uid,
					'application_reference_no'    	=> $reference_no,
					'service_id'					=> $service_id,
					'application_id'				=> $application_id,
					'is_payment_mad'				=> $is_payment_mad,
					'upload_challan_file'			=> $file_manage_id
							
			);
	$id = db_insert('fa_manual_payment_history')->fields($add_payment_details)->execute();
	if($id){
		$commands[] = ajax_command_replace('#payment_deatails_div', '<div id="payment_deatails_div"><div class="col-md-12">'.view_payment_deatils($application_id,$service_id,$factory_type,$reference_no).'</div></div>');
		
		$commands[] = ajax_command_replace('#fees_calculation_div', '<div id="fees_calculation_div"><div class="col-md-12"><input class="btn btn-info form-submit" id="edit-submit" name="op" value="Save &amp; Continue" type="submit"></div></div>');
		
		return array('#type' => 'ajax', '#commands' => $commands);
	}
				}
				if(empty($upload_chanal)){
					drupal_set_message('Please upload the Challan','error');
				}
		
		}
	if($val['op'] =="Delete payment"){
		$manual_payment_deatils = manual_payment_deatils($application_id,$service_id,$factory_type,$reference_no);
		foreach($manual_payment_deatils as $history){
			$total_previous_amount = $total_previous_amount+$history->payment_amount;
		}
	
	if(!empty($previousexcess_paid_hidden)){
		if($previousexcess_paid_hidden>$total_previous_amount){
			$total_previous_amount = $previousexcess_paid_hidden - $total_previous_amount;
		}if($previousexcess_paid_hidden<$total_previous_amount){
			$total_previous_amount =  $total_previous_amount-$previousexcess_paid_hidden;
		}if($previousexcess_paid_hidden==$total_previous_amount){
			$total_previous_amount =  $total_previous_amount-$previousexcess_paid_hidden;
		}
	}
	$cafa_Info		= 	array('previous_excess_paid'=>$total_previous_amount);
	$queryabc 		= 	db_update('fa_cafa');
    $queryabc		->	fields($cafa_Info);
    $queryabc		->	condition('id', $application_id, '=');
    $queryabc		->	execute();
	$id = del_manual_payment($application_id,$service_id,$factory_type,$reference_no);
	}
	
	//die($application_id.'---'.$service_id.'---'.$factory_type.'---'.$reference_no.'---'.$date_of_amenability.'---'.$period_for_application.'---'.$previousexcess_paid_hidden.'---'.$is_payment_mad);
	if($val['op'] =="Pay now"){
		if($factory_type == 3){
			save_pay_amount_details_85($application_id,$service_id,$factory_type,$reference_no,$date_of_amenability,$period_for_application,$previousexcess_paid_hidden,$is_payment_mad);
		}if($factory_type == 1){
			save_apy_ment_details_2mi($application_id,$service_id,$factory_type,$reference_no,$date_of_amenability,$period_for_application,$previousexcess_paid_hidden,$is_payment_mad);
		}if($factory_type == 2){
			save_apy_ment_details_2mii($application_id,$service_id,$factory_type,$reference_no,$date_of_amenability,$period_for_application,$previousexcess_paid_hidden,$is_payment_mad);
		}
	
	}
	
}

function calculate_manuall_fees($form, &$form_state){
	global $user;
	$val   								= 	$form_state['values'];
	$factory_type						= 	encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$service_id							= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$application_id						= 	encryption_decryption_fun('decrypt',$val['applicationid_hidden']);	
	$reference_no						= 	encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	$previousexcess_paid_hidden			= 	encryption_decryption_fun('decrypt',$val['previousexcesspaid_hidden']); 
	$date_of_amenability				= 	encryption_decryption_fun('decrypt',$val['date_of_amenability_hidden']); 
	$period_for_application				= 	encryption_decryption_fun('decrypt',$val['period_for_application_hidden']); 
	$total_previous_amount				=	0;
	$manual_payment_deatils 			=   manual_payment_deatils($application_id,$service_id,$factory_type,$reference_no);
	foreach($manual_payment_deatils as $history){
		$total_previous_amount = $total_previous_amount+$history->payment_amount;
	}
	if(!empty($previousexcess_paid_hidden)){
		$total_previous_amount = $previousexcess_paid_hidden+$total_previous_amount;
	}
	$cafa_Info		= 	array('previous_excess_paid'=>$total_previous_amount,'is_calculate' => 1);
	$queryabc 		= 	db_update('fa_cafa');
    $queryabc		->	fields($cafa_Info);
    $queryabc		->	condition('id', $application_id, '=');
    $queryabc		->	execute();
	
	if($factory_type==3){
		$commands[] = ajax_command_replace('#fees_details_div', '<div id="fees_details_div"><div class="col-md-12">'.show_fees_registration_section_85($application_id,$service_id,$factory_type,$reference_no,$date_of_amenability,$period_for_application).'</div></div>');
	}
	
	if($factory_type==1){
		$commands[] = ajax_command_replace('#fees_details_div', '<div id="fees_details_div"><div class="col-md-12">'.show_fees_registration($application_id,$service_id,$factory_type,$reference_no,$date_of_amenability,$period_for_application,$total_previous_amount).'</div></div>');
	}if($factory_type==2){
		$commands[] = ajax_command_replace('#fees_details_div', '<div id="fees_details_div"><div class="col-md-12">'.show_fees_registration_2mii($application_id,$service_id,$factory_type,$reference_no,$date_of_amenability,$period_for_application,$total_previous_amount).'</div></div>');
	}
	$commands[] = ajax_command_replace('#add_payment_div', '<div id="add_payment_div"><div class="col-md-12"></div></div>');
	$commands[] = ajax_command_replace('#del_payment_div', '<div id="del_payment_div"><div class="col-md-12"></div></div>');
	$commands[] = ajax_command_replace('#fees_calculation_div', '<div id="fees_calculation_div"><div class="col-md-12"></div></div>');
	$commands[] = ajax_command_replace('#fees_pay_div', '<div id="fees_pay_div"><div class="col-xs-12"><input class="btn btn-info pull-right form-submit" id="edit-fees-pay" name="op" value="Pay now" type="submit"></div></div>');
	return array('#type' => 'ajax', '#commands' => $commands);
}
function view_payment_deatils($application_id,$service_id,$factory_typeid,$reference_no){
	$output = '';
	$sl = 0;
	$header = array(
		array('data'=> 'SL No'),
		array('data'=> 'BRN/GRN/Challan Number'),
		array('data'=> 'Payment date'),
		array('data'=> 'Amount'),
		array('data'=> 'Challan')
	);
	$manual_payment_deatils	=	manual_payment_deatils($application_id,$service_id,$factory_typeid,$reference_no);
	foreach($manual_payment_deatils as $history){
			$upload_challan_doc 	=  get_uploaded_document_url($history->upload_challan_file);
			if(!empty($upload_challan_doc)){ 
					$url 		= explode('//',$upload_challan_doc);
					$doc_url	= $url[1];
					$view		='<a title = "Click here to view" href="'.$GLOBALS['base_url'].'/sites/default/files/'.$doc_url.'" target="_blank"><i class="ace-icon fa fa-file-pdf-o bigger-130"></i></a>';

			}
		$sl		 = $sl+1;	
		$rows [] = array(  
			array('data' => $sl), 	
			array('data' => t($history->brn_grn_challan_no)), 
			array('data' => t(date('dS M Y', strtotime($history->date_payment)))),
			array('data' => t($history->payment_amount)),
			array('data' => $view),	
		);
		
	}
	$output = theme_table(
	array(
		  'header' 		=> $header,
		  'rows' 		=> $rows,
		  'attributes' 	=> array('id'=>'table_div_replace', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' 		=> true,
		  'caption' 	=> '',
		  'colgroups' 	=> array(),
		  'empty' 		=> t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
	  
	return $output;	
}



function show_fees_registration($application_id,$service_id,$factory_typeid,$reference_number,$date_of_amenability,$period_for_application,$previous_excess_paid){
	
	$previous_amount_pre 				= $previous_excess_paid;
	$Registration_fees 					= 0;
	$created_by 						= $user->uid;
	$modifi_date 						= date("Y-m-d",strtotime($date_of_amenability));
	$i									= 1;
	/*if($modifi_date>='2016-12-30'){
		$Registration_fees =1000;
	}*/
	
	//echo $application_id.'--'.$service_id.'--'.$factory_typeid.'--'.$reference_number.'--'.$date_of_amenability.'--'.$period_for_application.'--'.$previous_excess_paid;die();

	$output = '<div class="box-body">
				<div class="table-responsive">
					<table class="table table-bordered" width="100%">
						<thead>
							<tr>
								<th colspan="12">License Fess Calculation</th>
							</tr>
							<tr>
								<th>SL</th>
								<th>Application Period</th>
								<th>Category(KW/HP)</th>
								<th>Total Workers</th>
								<th>Schedule Fees(Rs)<br>(calculated fess * total application year)</th>
								<th>Late Fees(Rs)</th>
								<th>Transfer</th>
								<th>Previous Excess Paid(Rs.)</th>
								<th>Balance(Rs)</th>
								<th>Due Amount(Rs)</th>
							</tr>';
	$power_details		= yearly_power_worker_details($application_id,$factory_typeid,$service_id,$reference_number);
	//print_r($power_details);die();
	$license_fees 		= 0;
	$late_fees			= 0;
	$current_year 		= date("Y");
	$fees 				= 0;
	$i					= 1;  
	$total_license_fees  = 0;
	$total_transfer_fees =0;
	//$Registration_fees =1000;
	//print_r($power_details);die;
	foreach($power_details as $rows){		
		if($rows->type_power_station == "other"){
				$power_hp_kw 			= $rows->installed_power_hp;
				$unit 		 			= 'Hp';
				$result_data 			= fees_calculation_registration($rows->installed_power_hp,$rows->worker_total,$rows->calculate_starting_year);
				
				$fees		 	 		= $result_data['fees']*$rows->valid_time_period;
				$max_payment_date 		= get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
				if(!empty($max_payment_date)){
					$datex 				= new DateTime($rows->calculate_starting_year);
		 			$datey 				= new DateTime('2015-12-31');
					$datez 				= new DateTime(date('Y-m-d'));
					$dateamenability	= new DateTime($date_of_amenability);
					$late_fees 			= 0;
					if($datex>$datey){
						$datez = new DateTime(date('Y-m-d'));
						$date_valid_year = new DateTime($rows->valid_year);
						$dateamenability= new DateTime($date_of_amenability);
												
							if($datez>$datex){
								 $late_fees = $result_data['fees'];
								
						}
					}
					$payble_fees 	= $fees+$late_fees+$total_transfer_fees+$Registration_fees;
					if($previous_amount_pre>$payble_fees){
							$late_fees_pay 		= $late_fees;
							$balance_amount  	= $previous_amount_pre-$payble_fees;
							$due_amount 		= 0;
						
					}
					if($previous_amount_pre<$payble_fees){
								$due_amount  		= $payble_fees-$previous_amount_pre;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								$late_fees_pay 		= $late_fees;
							
					}
					if($previous_amount_pre == $payble_fees){
								$due_amount  		= 0;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								$late_fees_pay 		= $late_fees;
							
					}
				}
				if(empty($max_payment_date)){
						$datex 					= new DateTime($rows->calculate_starting_year);
						//print_r($datex);die();
						$datey 					= new DateTime('2015-12-31');
						$previous_amount_pre 	= 0;
					 	$late_fees_pay 			= 0;
					if($datex>$datey){
						 $datez = new DateTime(date('Y-m-d'));
						// print_r($datez);
						// echo 'hif';
						$date_valid_year = new DateTime($rows->valid_year);
						$dateamenability= new DateTime($date_of_amenability);
						
							 $late_fees_pay = 0;
							if($datez>$datex){//echo 'hi';die();
								
								
								 $late_fees_pay = $result_data['fees'];
								
						}
					
				 $due_amount 	= $fees+$late_fees_pay+$total_transfer_fees+$Registration_fees;
				$balance_amount = 0;
				
			}else{
				$due_amount 	= $fees+$total_transfer_fees+$Registration_fees;
				$balance_amount = 0;
				$late_fees_pay 	= 0;
			}
			
					
	}
		$output.='<tr>
						<td>'.$i.'</td>
		             	<td>'.$rows->calculate_year.'</td>
						<td>'.$power_hp_kw.'('.$unit.')</td>
						<td>'.$rows->worker_total.'</td>
						<td>'.$fees.'  ('.$result_data['fees'].'*'.$rows->valid_time_period.')</td>
						<td>'.$late_fees_pay.'</td>
						<td>'.$total_transfer_fees.'</td>
						<td>'.$previous_amount_pre.'</td>
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';	
										
					
		$output.='</tr>';
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$Registration_fees 		=0;
		//print_r($previous_details);
	  }	
	    if($rows->type_power_station == "power_generating_station"){//echo 'hi';die();
				$power_hp_kw 			= $rows->installed_power;
				$unit 		 			= 'KW';
				$result_data 			= fees_calculation_registration_power_station($rows->installed_power,$rows->worker_total,$rows->calculate_starting_year);
				$fees		 	 		= $result_data['fees']*$rows->valid_time_period;
				/*$previous_details 		= get_previous_details_yearwise($application_id,$reference_number,$factory_typeid,$service_id,$rows->service_year);
				$total_transfer_fees = 0;
			
				foreach($previous_details as $transfer){
					if(empty($transfer->transfer_fees)){
						$transfer_fees = 0;
					}else{
						$transfer_fees = $transfer->transfer_fees;
					}
					$total_transfer_fees = $transfer_fees+$total_transfer_fees;
					//$fees		   = $result_data['fees']*$rows->valid_time_period+$transfer_fees;
				}*/
				
				$max_payment_date 		= get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
				if(!empty($max_payment_date)){	
					$datex 				= new DateTime($rows->calculate_starting_year);
		 			$datey 				= new DateTime('2015-12-31');
					$datez 				= new DateTime(date('Y-m-d'));
					$late_fees 			= 0; 
					if($datex>$datey){
						$datez = new DateTime(date('Y-m-d'));
						if($datez>$datex){
								 $late_fees = $result_data['fees'];
								
						}
					}//die();
					 $payble_fees 	= $fees+$late_fees+$Registration_fees;
					if($previous_amount_pre>$payble_fees){
							$late_fees_pay 		= $late_fees_pay;
							$balance_amount  	= $previous_amount_pre-$payble_fees;
							$due_amount 		= 0;
						
					}
					if($previous_amount_pre<$payble_fees){
								$due_amount  		= $payble_fees-$previous_amount_pre;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								$late_fees_pay 		= $late_fees;
							
					}
					if($previous_amount_pre == $payble_fees){
								$due_amount  		= 0;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								$late_fees_pay 		= $late_fees;
							
					}
				}
				if(empty($max_payment_date)){
					$datex = new DateTime($rows->calculate_starting_year);
					$datey = new DateTime('2015-12-31');
					$previous_amount_pre =0;
					 $late_fees_pay = 0;
					if($datex>$datey){
						$datez 				= new DateTime(date('Y-m-d'));
						$late_fees_pay 		= 0;
							if($datez>$datex){
								 $late_fees_pay = $result_data['fees'];
								
						}
					
				$due_amount 	= $fees+$late_fees_pay+$Registration_fees;
				$balance_amount = 0;
				
			}else{
				$due_amount 	= $fees+$total_transfer_fees+$Registration_fees;
				$balance_amount = 0;
				$late_fees_pay 	= 0;
			}
			
					
	}
		$output.='<tr>
						<td>'.$i.'</td>
		             	<td>'.$rows->calculate_year.'</td>
						<td>'.$power_hp_kw.'('.$unit.')</td>
						<td>'.$rows->worker_total.'</td>
						<td>'.$Registration_fees.'</td>
						<td>'.$fees.'  ('.$result_data['fees'].'*'.$rows->valid_time_period.')</td>
						<td>'.$late_fees_pay.'</td>
						<td>'.$total_transfer_fees.'</td>
						<td>'.$previous_amount_pre.'</td>
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';	
										
					
		$output.='</tr>';
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$Registration_fees 		=0;
		$late_fees_pay =0;
	  }	
	   	$i= $i+1;
   }//die();
	$output .='</table>
				<strong><font color="#FF0000">Fees to be paid:-'.($fees_to_paid).'</font></strong>
				</div></div>';
			
		
	return $output;
	
}

function show_fees_registration_section_85($application_id,$service_id,$factory_typeid,$reference_number,$date_of_amenability,$period_for_application){
global $base_root, $base_path, $user;
$get_fa_cafa 						= 	get_fa_cafa($application_id);
$previous_excesspaid				= 	$get_fa_cafa['previous_excess_paid'];
$previous_amount_pre 				= 	$previous_excesspaid;
$total_ownership_transfer_fees		=	0;
$Registration_fees 					= 	0;
$created_by 						=   $user->uid;
$modifi_date 						=   date("Y-m-d",strtotime($date_of_amenability));
$i									=	1;
$remark 							=	'';
if($modifi_date>='2016-12-30'){
		$Registration_fees =1000;
}
$power_details			= yearly_power_worker_details($application_id,$factory_typeid,$service_id,$reference_number);

$total_transfer_fees 	= 0;

				
//print_r($power_details);die();
$output = '<div class="box-header with-border">
              <h3 class="box-title">Fees Calculation for Registration<br/> Amenability Date:-'.date("dS M Y",strtotime($date_of_amenability)).'<br/>Period of license:-'.$period_for_application.'Year(s)</h3>
              </div>
			 <div class="box-body"><div class="table-responsive">
			<table class="table table-bordered" width="100%">
			<thead>
			<tr>
				<th colspan="12">License Fess Calculation</th>
			</tr>
			<tr>
				<th>SL</th>
  				<th>Application Period</th>
   				<th>Category(KW/HP)</th>
   				<th>Total Workers</th>
				<th>Registration Fees</th>
    			<th>Schedule Fees(Rs)<br>(calculated fess * total application year)</th>
				<th>Late Fees(Rs)</th>
				<th>Transfer</th>
  				<th>Previous Excess Paid(Rs.)</th>
				<th>Balance(Rs)</th>
				<th>Due Amount(Rs)</th>
				<th>Remark</th>
  	 		</tr>';
foreach($power_details as $rows){
	$installed_power 	=   $rows->installed_power;
	$worker_total 		=   $rows->worker_total;
	$previous_details 		= get_previous_details_yearwise($application_id,$reference_number,$factory_typeid,$service_id,$rows->service_year);
	foreach($previous_details as $transfer){
if(empty($transfer->transfer_fees)){
		$transfer_fees = 0;
}else{
		$transfer_fees = $transfer->transfer_fees;
}
		$total_transfer_fees = $transfer_fees+$total_transfer_fees;
					//$fees		   = $result_data['fees']*$rows->valid_time_period+$transfer_fees;
}
	
	if($worker_total>=20 && $installed_power==0){//2m(ii)
	    $fees_fetach 	=  fees_calculation_registration_2mii($rows->starting_year,$rows->worker_total);
		$remark			=  'Section-2m(ii)'	;
		
	}if($worker_total>=10 && $installed_power>0){//2m(i)
		if($rows->power_unit == 'HP'){
			$fees_fetach  = fees_calculation_registration($rows->service_year,$rows->installed_power_hp,$rows->worker_total,$rows->starting_year);
		}if($rows->power_unit == 'KW'){
			$fees_fetach  = fees_calculation_registration_power_station($rows->service_year,$rows->installed_power,$rows->starting_year);
		}
		$remark			=  'Section-2m(i)'	;
	
	}if($worker_total<=9 && $installed_power>=0){//section85
		$fees_fetach 	=	fees_calculation_registration_section_85($rows->service_year,$rows->starting_year);
		$remark			=  'Section-85'	;
	}if($worker_total<=19 && $installed_power==0){//section85
		$fees_fetach 	=	fees_calculation_registration_section_85($rows->service_year,$rows->starting_year);
		$remark			=  'Section-85'	;
	}
	//print_r($fees_fetach);die();
	$fees				=   $fees_fetach['fees']*$rows->valid_time_period;
	$max_payment_date	=	get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
	if(!empty($max_payment_date)){
					$datex 				= new DateTime($rows->starting_year);
		 			$datey 				= new DateTime('2015-12-31');
					$datez 				= new DateTime(date('Y-m-d'));
					$dateamenability	= new DateTime($date_of_amenability);
					$late_fees 			= 0;
					if($datex>$datey){
						$datez 				= new DateTime(date('Y-m-d'));
						$date_valid_year 	= new DateTime($rows->valid_year);
						if($datez>$datex){
								$late_fees 	= $fees_fetach['fees'];
								
						}
					}
					$payble_fees 	= $fees+$late_fees+$total_transfer_fees+$Registration_fees;
					if($previous_amount_pre>$payble_fees){
							$late_fees_pay 		= $late_fees;
							$balance_amount  	= $previous_amount_pre-$payble_fees;
							$due_amount 		= 0;
						
					}
					if($previous_amount_pre<$payble_fees){
								$due_amount  		= $payble_fees-$previous_amount_pre;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								$late_fees_pay 		= $late_fees;
							
					}
					if($previous_amount_pre == $payble_fees){
								$due_amount  		= 0;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								$late_fees_pay 		= $late_fees;
							
					}
				}
	if(empty($max_payment_date)){
				$datex 					= new DateTime($rows->starting_year);
				$datey 					= new DateTime('2015-12-31');
				$previous_amount_pre 	= 0;
				$late_fees_pay 			= 0;
				if($datex>$datey){
						 $datez 			= new DateTime(date('Y-m-d'));
						 $date_valid_year 	= new DateTime($rows->valid_year);
						 $late_fees_pay 	= 0;
						 if($datez>$datex){
								$late_fees_pay = $fees_fetach['fees'];
						}
					
				 $due_amount 	= $fees+$late_fees_pay+$total_transfer_fees+$Registration_fees;
				$balance_amount = 0;
				
			}else{
				$due_amount 	= $fees+$total_transfer_fees+$Registration_fees;
				$balance_amount = 0;
				$late_fees_pay 	= 0;
			}
			
					
	}

	
		$output.='<tr>
						<td>'.$i.'</td>
		             	<td>'.$rows->service_year.'</td>
						<td>'.$rows->installed_power.'</td>
						<td>'.$rows->worker_total.'</td>
						<td>'.$Registration_fees.'</td>
						<td>'.$fees.'</td>
						<td>'.$late_fees_pay.'</td>
						<td>'.$total_transfer_fees.'</td>		
						<td>'.$previous_amount_pre.'</td>
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>
						<td>'.$remark.'</td>';
					
		$output.='</tr>';
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$Registration_fees 		=0;
		$late_fees_pay =0;
		$total_transfer_fees =0;
}
$output .=' </table>
			<strong><font color="#FF0000">Fees to be paid(Total Due amount+Registration Fees):-'.($total_due_fees+$Registration_fees).'</font></strong></div></div>';
				
return $output;	
}

function show_fees_registration_2mii($application_id,$service_id,$factory_typeid,$reference_number,$date_of_amenability,$period_for_application,$previous_excess_paid){
	$i= 1;
		$output = '<div class="row"><div class="box box-info"><div class="box-header with-border">
              			 	<h3 class="box-title">Fees Calculation for Registration<br/> 
								Amenability Date:-'.date("dS M Y",strtotime($date_of_amenability)).'<br/>
								Period of license:-'.$period_for_application.'Year(s)
					   		</h3>
                     </div>
			         	<div class="box-body"><div class="table-responsive">
						<table class="table table-bordered" width="100%">
							<tr>
				<th>SL</th>
  				<th>Application Period</th>
   				<th>Total Workers</th>
				<th>Registration Fees</th>
    			<th>Schedule Fees(Rs)<br>(calculated fess * total application year)</th>
				<th>Late Fees(Rs)</th>
				<th>Transfer</th>
  				<th>Previous Excess Paid(Rs.)</th>
				<th>Balance(Rs)</th>
				<th>Due Amount(Rs)</th>
  	 		</tr>';
 $license_fees 			= 	0;
 $Registration_fees 	=	0;
 $fees 					=	0;
 $worker_detials 		= worker_detials_for_fees($application_id,$reference_number,$factory_typeid,$service_id);
 
 
 $due_amount 			= 0;
 $previous_amount_pre 	= $previous_excess_paid;

 $modifi_date 			=   date("Y-m-d",strtotime($date_of_amenability));

 if($modifi_date>='2016-12-30'){ 
		$Registration_fees =1000;
 }

 $max_payment_date 		= get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);

foreach($worker_detials as $worker){
	$schedule_fees 			= fees_calculation_registration_2mii($worker->starting_year,$worker->worker_total);
	$previous_details 		= get_previous_details_yearwise($application_id,$reference_number,$factory_typeid,$service_id,$worker->service_year);
	//print_r($previous_details);
	 $total_transfer_fees 	= 0;
	foreach($previous_details as $transfer){
		if(empty($transfer->transfer_fees)){
				$transfer_fees = 0;
		}else{
				$transfer_fees = $transfer->transfer_fees;
		}
		
		$total_transfer_fees = $transfer_fees+$total_transfer_fees;
				
	}//echo $Registration_fees;die();
	$fees 					= $schedule_fees['fees']*$worker->valid_time_period;
	$datex 					= new DateTime($worker->starting_year);
	$datey 					= new DateTime('2015-12-31');
	if(empty($max_payment_date)){
		 if($datex>$datey){
				 $datez = new DateTime(date('Y-m-d'));
				 $date_valid_year = new DateTime($rows->valid_year);
						$dateamenability= new DateTime($date_of_amenability);
						
							 $late_fees_pay = 0;
							if($datez>$datex){//echo 'hi';die();
								//print_r($datex);
							
								 $late_fees_pay = $schedule_fees['fees'];
								
						}
					
				 $due_amount 	= $fees+$late_fees_pay+$total_transfer_fees+$Registration_fees;
				$balance_amount = 0;
				
			}else{
				$due_amount 	= $fees+$total_transfer_fees+$Registration_fees;
				$balance_amount = 0;
				$late_fees_pay 	= 0;
			}
	}
	//echo $due_amount;die();
	 if(!empty($max_payment_date)){
					$datex 				= new DateTime($worker->starting_year);
		 			$datey 				= new DateTime('2015-12-31');
					$datez 				= new DateTime(date('Y-m-d'));
					$dateamenability	= new DateTime($date_of_amenability);
					$late_fees 			= 0;
					if($datex>$datey){//echo 'hello';
						$datez = new DateTime(date('Y-m-d'));
						$date_valid_year = new DateTime($worker->valid_year);
						$dateamenability= new DateTime($date_of_amenability);
							//print_r($datez);	
							//print_r($datex);					
							if($datez>$datex){//echo 'hi';
								 $late_fees_pay = $schedule_fees['fees'];
								
						}else{
						
								$late_fees_pay 	= 0;
						}
					}
					$payble_fees 	= $fees+$late_fees_pay+$total_transfer_fees+$Registration_fees;
					if($previous_amount_pre>$payble_fees){
							$late_fees_pay 		= 0;
							$balance_amount  	= $previous_amount_pre-$payble_fees;
							$due_amount 		= 0;
						
					}
					if($previous_amount_pre<$payble_fees){
								$due_amount  		= $payble_fees-$previous_amount_pre;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								$late_fees_pay 		= $late_fees_pay;
							
					}
					if($previous_amount_pre == $payble_fees){
								$due_amount  		= 0;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								$late_fees_pay 		= 0;
							
					}
				}
	//echo $Registration_fees;die();
	$output .='<tr>
				<td>'.$i.'</td>
				<td>'.$worker->service_year.'</td>
				<td>'.$worker->worker_total.'</td>
				<td>'.$Registration_fees.'</td>
				<td>'.$fees.'('.$schedule_fees['fees'].'*'.$worker->valid_time_period.')</td>
				<td>'.$late_fees_pay.'</td>
				<td>'.$total_transfer_fees.'</td>
				<td>'.$previous_amount_pre.'</td>
				<td>'.$balance_amount.'</td>
				<td>'.$due_amount.'</td>
			</tr>';
			$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$Registration_fees 		=0;
		$i = $i+1;
}
//die();	
	$total_fees = $total_fees+$total_due_fees;
	$output .=' </table>
		<strong><font color="#FF0000">Fees to be paid (Total Due amount +  Registration fees + Total transfer fees) :-  '.$total_fees.'</font></strong>
				</div></div></div></div></div></div></div></div>';
				
				
	return $output;
	
}

function save_pay_amount_details_85($application_id,$service_id,$factory_typeid,$reference_number,$date_of_amenability,$period_for_application,$previous_excess_paid,$is_payment_mad){
global $base_root, $base_path, $user;
$get_fa_cafa 						= 	get_fa_cafa($application_id);
$previous_amount_pre 				= 	$previous_excess_paid;
$total_ownership_transfer_fees		=	0;
$Registration_fees 					= 	0;
$created_by 						=   $user->uid;
$modifi_date 						=   date("Y-m-d",strtotime($date_of_amenability));
$i									=	1;
if($modifi_date>='2016-12-30'){
		$Registration_fees =1000;
}
$power_details			= yearly_power_worker_details($application_id,$factory_typeid,$service_id,$reference_number);

foreach($power_details as $rows){
	$installed_power 	=   $rows->installed_power;
	$worker_total 		=   $rows->worker_total;
	$previous_details 		= get_previous_details_yearwise($application_id,$reference_number,$factory_typeid,$service_id,$rows->service_year);
	foreach($previous_details as $transfer){
if(empty($transfer->transfer_fees)){
		$transfer_fees = 0;
}else{
		$transfer_fees = $transfer->transfer_fees;
}
		$total_transfer_fees = $transfer_fees+$total_transfer_fees;
					
}
	
	if($worker_total>=20 && $installed_power==0){//2m(ii)
	    $fees_fetach 	=  fees_calculation_registration_2mii($rows->starting_year,$rows->worker_total);
		$remark			=  'Section-2m(ii)'	;
				
	}if($worker_total>=10 && $installed_power>0){//2m(i)
		if($rows->power_unit == 'HP'){
			$fees_fetach  = fees_calculation_registration($rows->service_year,$rows->installed_power_hp,$rows->worker_total,$rows->starting_year);
		}if($rows->power_unit == 'KW'){
			$fees_fetach  = fees_calculation_registration_power_station($rows->service_year,$rows->installed_power,$rows->starting_year);
		}
		$remark			=  'Section-2m(i)'	;
	
	}if($worker_total<=9 && $installed_power>=0){//section85
		$fees_fetach 	=	fees_calculation_registration_section_85($rows->service_year,$rows->starting_year);
		$remark			=  'Section-85'	;
	}if($worker_total<=19 && $installed_power==0){//section85
		$fees_fetach 	=	fees_calculation_registration_section_85($rows->service_year,$rows->starting_year);
		$remark			=  'Section-85'	;
	}
	//print_r($fees_fetach);die();
	$fees				=   $fees_fetach['fees']*$rows->valid_time_period;
	$max_payment_date	=	get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
	if(!empty($max_payment_date)){
					$datex 				= new DateTime($rows->starting_year);
		 			$datey 				= new DateTime('2015-12-31');
					$datez 				= new DateTime(date('Y-m-d'));
					$dateamenability	= new DateTime($date_of_amenability);
					$late_fees 			= 0;
					if($datex>$datey){
						$datez 				= new DateTime(date('Y-m-d'));
						$date_valid_year 	= new DateTime($rows->valid_year);
						if($datez>$datex){
								$late_fees 	= $fees_fetach['fees'];
								
						}
					}
					$payble_fees 	= $fees+$late_fees+$total_transfer_fees+$Registration_fees;
					if($previous_amount_pre>$payble_fees){
							$late_fees_pay 		= $late_fees;
							$balance_amount  	= $previous_amount_pre-$payble_fees;
							$due_amount 		= 0;
						
					}
					if($previous_amount_pre<$payble_fees){
								$due_amount  		= $payble_fees-$previous_amount_pre;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								$late_fees_pay 		= $late_fees;
							
					}
					if($previous_amount_pre == $payble_fees){
								$due_amount  		= 0;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								$late_fees_pay 		= $late_fees;
							
					}
				}
	if(empty($max_payment_date)){
				$datex 					= new DateTime($rows->starting_year);
				$datey 					= new DateTime('2015-12-31');
				$previous_amount_pre 	= 0;
				$late_fees_pay 			= 0;
				if($datex>$datey){
						 $datez 			= new DateTime(date('Y-m-d'));
						 $date_valid_year 	= new DateTime($rows->valid_year);
						 $late_fees_pay 	= 0;
						 if($datez>$datex){
								$late_fees_pay = $fees_fetach['fees'];
						}
					
				 $due_amount 	= $fees+$late_fees_pay+$total_transfer_fees+$Registration_fees;
				$balance_amount = 0;
				
			}else{
				$due_amount 	= $fees+$total_transfer_fees+$Registration_fees;
				$balance_amount = 0;
				$late_fees_pay 	= 0;
			}
			
					
	}
	
	if($fees_fetach['workers_end_to'] == -1){
		$max_worker = $rows->worker_total." and onwords";
	}else{
		$max_worker = $fees_fetach['workers_end_to'];
	}if($result_data['power_range_end_hp'] == -1){
		$max_power = $rows->installed_power_hp." and onwords";
	}else{
		$max_power = $fees_fetach['power_range_end_hp'];
	}
    if($remark == 'Section-85'){
		$max_worker = $rows->worker_total;
		$max_power = $rows->installed_power;
	}
	$calculate_fees_details = array(
			'feesyear' 		             => $fees_fetach['feesyear'],
			'schedule_fees' 		     => $fees,
			'late_fees'              	 => $late_fees_pay,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $rows->service_year,
			'factory_type'				 => $factory_typeid,
			'application_reference_no'	 => $reference_number,
			'created_by'				 => $user->uid,
			'application_status'	     => 'N',
			'due_fees'    				 => $due_amount,
			'balance_amount'			 => $balance_amount,
			'previous_paid_fees'   	 	 => !empty($previous_amount_pre)?$previous_amount_pre:0,
			'max_worker'				 => $max_worker,
			'max_power'					 => $max_power.'('.$rows->power_unit.')',
			'worker'					 => $rows->worker_total,
			'power'					 	 => $rows->installed_power.'('.$rows->power_unit.')',
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $Registration_fees,
			'remark'					 => $remark
			
			
		);
		//print_r($fees_fetach);
		//print_r($calculate_fees_details);
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$Registration_fees 		= 0;
		$late_fees_pay 			= 0;
		$total_transfer_fees 	= 0;
}//die();


if(empty($previous_excess_paid) || $previous_excess_paid==NULL || $previous_excess_paid=0){
	
	$fees_deatils = array('service_fees'=>$Registration_fees1,'payment_amount'=>$fees_to_paid,'application_status'=>'P','is_previous_payment'=>$is_payment_mad,'balance_amount'=>$balance_amount);
}
else{
	$fees_deatils = array('service_fees'=>$Registration_fees1,'previous_excess_paid'=>$previous_excess_paid,'payment_amount'=>$fees_to_paid,'application_status'=>'P','is_previous_payment'=>$is_payment_mad,'balance_amount'=>$balance_amount);
}


				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		->	fields($fees_deatils);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc		->	execute();
				
drupal_goto('applicant/view-payment-breakup/' .encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_typeid).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_number));
}
function save_apy_ment_details_2mi($application_id,$service_id,$factory_typeid,$reference_number,$date_of_amenability,$period_for_application,$previous_excess_paid,$is_payment_mad){
	
	global $base_root, $base_path, $user;
	$previous_amount_pre 				= 	$previous_excess_paid;
	$Registration_fees 					= 	0;
	$created_by 						=   $user->uid;
	$modifi_date 						=   date("Y-m-d",strtotime($date_of_amenability));
	$i									=	1;
	$toatla_transfer_fees				=	0;
	/*if($modifi_date>='2016-12-30'){
		$Registration_fees =1000;
	}
	$output = '<div class="box-header with-border">
              <h3 class="box-title">Fees Calculation for Registration<br/> Amenability Date:-'.date("dS M Y",strtotime($date_of_amenability)).'<br/>Period of license:-'.$period_for_application.'Year(s)<br/>Registration Fees:-'.$Registration_fees.'</h3>
              </div>
			 <div class="box-body"><div class="table-responsive">';
			
 */
	$power_details		= yearly_power_worker_details($application_id,$factory_typeid,$service_id,$reference_number);
	
	$license_fees 		= 0;
	$late_fees			= 0;
	$current_year 		= date("Y");
	$fees 				= 0;
	$i					= 1;
	//print_r($power_details);die();
	//$previous_amount_pre = $previous_excesspaid;
	$total_license_fees  = 0;
	foreach($power_details as $rows){		
		$power_hp_kw = $rows->installed_power_hp;
		if($rows->type_power_station == "other"){
				$unit 		 	= 'Hp';
				$result_data 	= fees_calculation_registration($rows->installed_power_hp,$rows->worker_total,$rows->calculate_starting_year);
				/*$previous_details 		= get_previous_details_yearwise($application_id,$reference_number,$factory_typeid,$service_id,$rows->service_year);
				$total_transfer_fees = 0;
				foreach($previous_details as $transfer){
					if(empty($transfer->transfer_fees)){
						$transfer_fees = 0;
					}else{
						$transfer_fees = $transfer->transfer_fees;
					}
					$total_transfer_fees = $transfer_fees+$total_transfer_fees;
					//$fees		   = $result_data['fees']*$rows->valid_time_period+$transfer_fees;
				}*/
				//print_r($result_data);die();
				$fees		 	= $result_data['fees']*$rows->valid_time_period;
				$max_payment_date = get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
				if(!empty($max_payment_date)){
					$datex 				= new DateTime($rows->calculate_starting_year);
		 			$datey 				= new DateTime('2015-12-31');
					$datez 				= new DateTime(date('Y-m-d'));
					$dateamenability	= new DateTime($date_of_amenability);
					//$late_fees 			= 0;
					if($datex>$datey){
						$datez = new DateTime(date('Y-m-d'));
						$date_valid_year = new DateTime($rows->valid_year);
						$dateamenability= new DateTime($date_of_amenability);
												
							if($datez>$datex){
								 $late_fees = $result_data['fees'];
								
						}
					}
					$payble_fees 	= $fees+$late_fees+$total_transfer_fees+$Registration_fees;
					if($previous_amount_pre>$payble_fees){
							$late_fees_pay 		= $late_fees;
							$balance_amount  	= $previous_amount_pre-$payble_fees;
							$due_amount 		= 0;
						
					}
					if($previous_amount_pre<$payble_fees){
								$due_amount  		= $payble_fees-$previous_amount_pre;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								$late_fees_pay 		= $late_fees;
							
					}
					if($previous_amount_pre == $payble_fees){
								$due_amount  		= 0;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								$late_fees_pay 		= $late_fees;
							
					}
				}
				if(empty($max_payment_date)){
					$datex = new DateTime($rows->calculate_starting_year);
					$datey = new DateTime('2015-12-31');
					$previous_amount_pre =0;
					 $late_fees_pay = 0;
					if($datex>$datey){
						$datez = new DateTime(date('Y-m-d'));
						$date_valid_year = new DateTime($rows->valid_year);
						$dateamenability= new DateTime($date_of_amenability);
						
							 $late_fees_pay = 0;
							if($datez>$datex){
								
								
								 $late_fees_pay = $result_data['fees'];
								
						}
					
				$due_amount 	= $fees+$late_fees_pay+$total_transfer_fees+$Registration_fees;
				$balance_amount = 0;
				
			}else{
				$due_amount 	= $fees+$total_transfer_fees+$Registration_fees;
				$balance_amount = 0;
				$late_fees_pay 	= 0;
			}
			
					
	}
	if($result_data['workers_end_to'] == -1){
		$max_worker = $rows->worker_total." and onwords";
	}else{
		$max_worker = $result_data['workers_end_to'];
	}if($result_data['power_range_end_hp'] == -1){
		$max_power = $rows->installed_power_hp." and onwords";
	}else{
		$max_power = $result_data['power_range_end_hp'];
	}
		$calculate_fees_details = array(
			'feesyear' 		             => $result_data['feesyear'],
			'schedule_fees' 		     => $fees,
			'late_fees'              	 => $late_fees_pay,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $rows->calculate_year,
			'factory_type'				 => $factory_typeid,
			'application_reference_no'	 => $reference_number,
			'created_by'				 => $user->uid,
			'application_status'	     => 'N',
			'due_fees'    				 => $due_amount,
			'balance_amount'			 => $balance_amount,
			'previous_paid_fees'   	 	 => !empty($previous_amount_pre)?$previous_amount_pre:0,
			'max_worker'				 => $max_worker,
			'max_power'					 => $max_power.'(hp)',
			'worker'					 => $rows->worker_total,
			'power'					 	 => $rows->installed_power_hp.'(hp)',
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $Registration_fees
			
			
		);
		//print_r($calculate_fees_details);
		
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
		
		$previous_amount_pre = $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$Registration_fees 		= 0;
		$late_fees				= 0;
		$total_transfer_fees 	= 0;
		
			
	  }//die();
	   	if($rows->type_power_station == "power_generating_station"){
				$unit 		 			= 'KW';
				$result_data 			= fees_calculation_registration_power_station($rows->installed_power,$rows->worker_total,$rows->calculate_starting_year);
				//print_r($result_data);die();
				$fees		 			= $result_data['fees']*$rows->valid_time_period;
				$max_payment_date = get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
				if(!empty($max_payment_date)){
					$datex 				= new DateTime($rows->calculate_starting_year);
		 			$datey 				= new DateTime('2015-12-31');
					$datez 				= new DateTime(date('Y-m-d'));
					$dateamenability	= new DateTime($date_of_amenability);
					$late_fees 			= 0;
					if($datex>$datey){
						$datez = new DateTime(date('Y-m-d'));
						$dateamenability= new DateTime($date_of_amenability);
						 $late_fees_pay = 0;
							if($datez>$datex){
								
								
								 $late_fees = $result_data['fees'];
								
						}
					}
					$payble_fees 	= $fees+$late_fees+$total_transfer_fees+$Registration_fees;
					if($previous_amount_pre>$payble_fees){
							$late_fees_pay 		= $late_fees;
							$balance_amount  	= $previous_amount_pre-$payble_fees;
							$due_amount 		= 0;
						
					}
					if($previous_amount_pre<$payble_fees){
								$due_amount  		= $payble_fees-$previous_amount_pre;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								$late_fees_pay 		= $late_fees;
							
					}
					if($previous_amount_pre == $payble_fees){
								$due_amount  		= 0;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								$late_fees_pay 		= $late_fees;
							
					}
				}
				if(empty($max_payment_date)){
					$datex = new DateTime($rows->calculate_starting_year);
					$datey = new DateTime('2015-12-31');
					$previous_amount_pre =0;
					 $late_fees_pay = 0;
					if($datex>$datey){
						$datez = new DateTime(date('Y-m-d'));
						$dateamenability= new DateTime($date_of_amenability);
						
							 $late_fees_pay = 0;
							if($datez>$datex){
								
								
								 $late_fees_pay = $result_data['fees'];
								
						}
					
				$due_amount 	= $fees+$late_fees_pay+$Registration_fees;
				$balance_amount = 0;
				
			}else{
				$due_amount 	= $fees+$total_transfer_fees+$Registration_fees;
				$balance_amount = 0;
				$late_fees_pay 	= 0;
			}
			
					
	}
	if($result_data['workers_end_to'] == -1){
		$max_worker = $rows->worker_total." and onwords";
	}else{
		$max_worker = $result_data['workers_end_to'];
	}if($result_data['power_range_end_kw'] == -1){
		$max_power = $rows->installed_power." and onwords";
	}else{
		$max_power = $result_data['power_range_end_kw'];
	}
		$calculate_fees_details = array(
			'feesyear' 		             => $result_data['feesyear'],
			'schedule_fees' 		     => $fees,
			'late_fees'              	 => $late_fees_pay,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $rows->calculate_year,
			'factory_type'				 => $factory_typeid,
			'application_reference_no'	 => $reference_number,
			'created_by'				 => $user->uid,
			'application_status'	     => 'N',
			'due_fees'    				 => $due_amount,
			'balance_amount'			 => $balance_amount,
			'previous_paid_fees'   	 	 => !empty($previous_amount_pre)?$previous_amount_pre:0,
			'max_worker'				 => $max_worker,
			'max_power'					 => $max_power.'(KW)',
			'worker'					 => $rows->worker_total,
			'power'					 	 => $rows->installed_power.'(KW)',
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $Registration_fees
			
			
		);
		//print_r($calculate_fees_details);
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
		
		$previous_amount_pre = $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$Registration_fees 		= 0;
			
	  }
	 // echo $fees_to_paid;
		//$i= $i+1;
}//die();

	
if(empty($previous_excess_paid) || $previous_excess_paid==NULL || $previous_excess_paid=0){
	
	$fees_deatils = array('service_fees'=>$Registration_fees1,'payment_amount'=>$fees_to_paid,'application_status'=>'P','is_previous_payment'=>$is_payment_mad,'balance_amount'=>$balance_amount);
}
else{
	$fees_deatils = array('service_fees'=>$Registration_fees1,'previous_excess_paid'=>$previous_excess_paid,'payment_amount'=>$fees_to_paid,'application_status'=>'P','is_previous_payment'=>$is_payment_mad,'balance_amount'=>$balance_amount);
}

	
				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		->	fields($fees_deatils);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc		->	execute();
				

	drupal_goto('applicant/view-payment-breakup/' .encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_typeid).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_number));
	
	
	
}
function save_apy_ment_details_2mii($application_id,$service_id,$factory_typeid,$reference_number,$date_of_amenability,$period_for_application,$previous_excess_paid,$is_payment_mad){
	global $base_root, $base_path, $user;
	$previous_amount_pre 				= 	$previous_excess_paid;
	$Registration_fees 					= 	0;
	$created_by 						=   $user->uid;
	$modifi_date 						=   date("Y-m-d",strtotime($date_of_amenability));
	$i									=	1;
	if($modifi_date>='2016-12-30'){
		$Registration_fees =1000;
	}
	
	$worker_detials 		= worker_detials_for_fees($application_id,$reference_number,$factory_typeid,$service_id);
	$max_payment_date 		= get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
	$license_fees 			= 0;
	$late_fees				= 0;
	$current_year 			= date("Y");
	$fees 					= 0;
	$i						= 1;
	$total_license_fees  	= 0;
	foreach($worker_detials as $rows){
			$schedule_fees 		= fees_calculation_registration_2mii($rows->starting_year,$rows->worker_total);
			$previous_details 	= get_previous_details_yearwise($application_id,$reference_number,$factory_typeid,$service_id,$rows->service_year);
	 $total_transfer_fees 	= 0;
	foreach($previous_details as $transfer){
		if(empty($transfer->transfer_fees)){
				$transfer_fees = 0;
		}else{
				$transfer_fees = $transfer->transfer_fees;
		}
		
		$total_transfer_fees = $transfer_fees+$total_transfer_fees;
				
	}
			$fees 			= $schedule_fees['fees']*$rows->valid_time_period;
	 	  $datex 			= new DateTime($rows->starting_year);
	 	  $datey 			= new DateTime('2015-12-31');
		  $datez 			 = new DateTime(date('Y-m-d'));
		 if(empty($max_payment_date)){
			  if($datex>$datey){
					$late_fees 	 	= 0;
					if($datez>$datex){
						$late_fees = $schedule_fees['fees'];
								
					}
		 }
					
		$due_amount 	= $fees+$late_fees+$total_transfer_fees+$Registration_fees;;
	 }
	 	 if(!empty($max_payment_date)){
		  if($datex>$datey){
			  	if($datez>$datex){
					$late_fees = $schedule_fees['fees'];
				}else{
					$late_fees =0;
				}
			
								
		}
		$payble_fess = $late_fees+$fees+$total_transfer_fees+$Registration_fees;;
		if($previous_amount_pre>$payble_fess){
			$balance_amount 		= $previous_amount_pre-$payble_fess;
			
			$due_amount 			= 0;
		}if($previous_amount_pre<$payble_fess){
			$balance_amount 		= 0;
		
			$due_amount 			= $payble_fess-$previous_amount_pre;
		}if($previous_amount_pre>$payble_fess){
			$balance_amount 		= $previous_amount_pre-$payble_fess;
			
			$due_amount 			= 0;
		}if($previous_amount_pre==$payble_fess){
			$balance_amount 		= 0;
			
			$due_amount 			= 0;
		}
		
	}
	     if($schedule_fees['workers_end_to'] == -1){
			$max_worker = $rows->worker_total." and onwords";
		}else{
			$max_worker = $schedule_fees['workers_end_to'];
		}
	    
		$calculate_fees_details = array(
			'feesyear' 		             => $schedule_fees['feesyear'],
			'schedule_fees' 		     => $fees,
			'late_fees'              	 => $late_fees,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $rows->service_year,
			'factory_type'				 => $factory_typeid,
			'application_reference_no'	 => $reference_number,
			'created_by'				 => $user->uid,
			'application_status'	     => 'N',
			'due_fees'    				 => $due_amount,
			'balance_amount'			 => $balance_amount,
			'previous_paid_fees'   	 	 => !empty($previous_amount_pre)?$previous_amount_pre:0,
			'max_worker'				 => $max_worker,
			'worker'					 => $rows->worker_total,
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $Registration_fees
			
			
		);
		//print_r($calculate_fees_details);
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
	   $previous_amount_pre = $balance_amount; 
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$Registration_fees 		= 0;
	
	}
/*if(empty($previous_amount_pre) || $previous_amount_pre==NULL || $previous_amount_pre=0){
	$previous_amount_pre = NULL;
	$fees_deatils = array('service_fees'=>$Registration_fees1,'payment_amount'=>$fees_to_paid,'application_status'=>'P','is_previous_payment'=>$is_payment_mad,'balance_amount'=>$balance_amount);
}
else{*/
	//$fees_deatils = array('service_fees'=>$Registration_fees1,'previous_excess_paid'=>$previous_excess_paid,'payment_amount'=>$fees_to_paid,'application_status'=>'P','is_previous_payment'=>$is_payment_mad,'balance_amount'=>$balance_amount);
//}

	if(empty($previous_excess_paid) || $previous_excess_paid==NULL || $previous_excess_paid=0){
	
	$fees_deatils = array('service_fees'=>$Registration_fees1,'payment_amount'=>$fees_to_paid,'application_status'=>'P','is_previous_payment'=>$is_payment_mad,'balance_amount'=>$balance_amount);
}
else{
	$fees_deatils = array('service_fees'=>$Registration_fees1,'previous_excess_paid'=>$previous_excess_paid,'payment_amount'=>$fees_to_paid,'application_status'=>'P','is_previous_payment'=>$is_payment_mad,'balance_amount'=>$balance_amount);
}
				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		->	fields($fees_deatils);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc		->	execute();
				

	drupal_goto('applicant/view-payment-breakup/' .encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_typeid).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_number));
	
	
	
}
//-------------Fetch director------------------------
