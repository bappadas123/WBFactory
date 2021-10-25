
<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function details_fees_renewal($form, &$form_state,$serviceid,$factory_typeid,$applicationid,$referenceno) {	


	global $base_root, $base_path, $user,$total_fees_paid_to_end;
		
	$application_id 			= encryption_decryption_fun('decrypt', $applicationid);
	$service_id 				= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 			= encryption_decryption_fun('decrypt',$factory_typeid);
	$reference_no 				= encryption_decryption_fun('decrypt',$referenceno);
	$get_fa_cafa 				= get_fa_cafa($application_id);
    $reference_no 				= $get_fa_cafa['reference_number'];
	$date_of_amenability 		= $get_fa_cafa['date_of_amenability'];
	$period_for_application 	= $get_fa_cafa['period_for_application'];
	$is_calculate				= $get_fa_cafa['is_calculate'];
	$application_status			= $get_fa_cafa['application_status'];
	$balance_amount				= $get_fa_cafa['balance_amount'];
	$previous_excess_paid		= $balance_amount;
    $last_validlicensedate		= $get_fa_cafa['license_valid_upto'];
	$factory_name				= $get_fa_cafa['factory_name'];
	$period_for_renewal			= $get_fa_cafa['period_for_renewal'];
	$factory_license_no			= $get_fa_cafa['factory_license_no'];
	$backlog_license_number		= $get_fa_cafa['backlog_license_number'];
	$factory_license_no			= !empty($factory_license_no)?$factory_license_no:$backlog_license_number;
    $form 						= array();
	if($factory_type_id==1){
		$section = 'Section2m(i)';
	}if($factory_type_id==2){
		$section = 'Section2m(ii)';
	}if($factory_type_id==3){
		$section = 'Section85';
	}
	
	
	
	
	$form['#attributes'] 		= array('enctype' => "multipart/form-data");
	
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
			'#default_value' 	=> $referenceno
			 
	);
	$form['applicationid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $applicationid
	);
	$form['previousexcesspaid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$previous_excess_paid),
	);
	$form['last_validlicensedate'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$last_validlicensedate),
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
			'#prefix' 			=> '<div class = "box-body">
									<div class="box-header with-border">
             						<h3 class="box-title">Fees Calculation for Renewal of License<br/>Name:-'.$factory_name.'('.$section.')
									<br/>License Number License:-'.$factory_license_no.' valid upto:-'.date("dS M Y",strtotime($last_validlicensedate)).'
									<br/>Period for apply for renewal of the license:-'.$period_for_renewal.'Year(s)<br/>
									You have to pay the application fees through GRIPS from our portal
									<br/>N.B.:- Externally the payment process is not a grant.</h3>',
			
		   
		 );
		 
	if(empty($payment_id)){
		$form['yearly_worker']['manual_payment']= array(
				'#prefix' 			=> '<div class="col-xs-12">',
		   		'#suffix' 			=> '</div>',
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
				'#prefix' 			=> '<div class="col-xs-12">',
		   		'#suffix' 			=> '</div>',
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
	$form['yearly_worker']['worker_amand_fees'] = array(
			'#prefix' 			=> '<div id="amand_fees_details_div">',
			'#suffix' 			=> '</div>',
		   
		 );
	$form['yearly_worker']['fees_calculation'] = array(
			'#prefix' 			=> '<div id="fees_calculation_div">',
			'#suffix' 			=> '</div>',
		   
		 );
	$form['yearly_worker']['fees_pay'] 	= array(
			'#prefix' 			=> '<div id="fees_pay_div">',
			'#suffix' 			=> '</div></div></div></div>',
			
			
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
				 '#suffix' 			=> '</div></div>',
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
				'#upload_location' 		 => 'public://upload/upload_pdf/',
				'#process' 				 => array('import_my_file_element_process'),
				'#attributes' 			 => array('id' => '','autocomplete' => 'off','class'=>array('form-control')),
				
			  
					
		);
		$form['yearly_worker']['markup_end'] 	= array(
				'#suffix' 			=> '</div></div>',
				
		);
		if($is_calculate !=1){
			$form['yearly_worker']['add_payment'] 	= array(
				'#prefix'			 	=> '<div id="add_payment_div"><div class="col-xs-6">',
				'#suffix' 				=> '</div></div>',
				'#type' 				=> 'submit',
				'#value' 				=> t('Add payment'),
				'#attributes' 			=> array('class' => array('btn btn-info pull-left')),
			
			);
			$form['yearly_worker']['del_payment'] 	= array(
				'#prefix'			 	=> '<div id="del_payment_div"><div class="col-xs-6">',
				'#suffix' 				=> '</div></div>',
				'#type' 				=> 'submit',
				'#value' 				=> t('Delete payment'),
				'#attributes' 			=> array('class' => array('btn btn-info pull-right')),
			);
		}
		
		
		
	$form['yearly_worker']['payment_deatails'] = array(
				'#prefix' 			=> '<div id="payment_deatails_div"><div class="col-xs-6 col-md-12">'.view_payment_deatils($application_id,$service_id,$factory_type_id,$reference_no),
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
		if($factory_type_id == 1){
			$form['yearly_worker']['worker_year_table'] 	= array(
		 		'#prefix' 			=> '<div id="fees_details_div">',
			 	'#suffix' 			=> '</div>',
  				'#type'				=> 'markup',
				'#markup'			=> show_fees_registration($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid,$last_validlicensedate)
				
			);
			
		$form['yearly_worker']['worker_amand_fees'] 	= array(
		 		
				'#prefix' 			=> '<div id="amand_fees_details_div">',
				'#suffix' 			=> '</div>',
		   		'#type'				=> 'markup',
				'#markup'			=> show_fees_registration_amand($application_id,$service_id,$factory_type_id,$reference_no)
			);
	}if($factory_type_id == 2){
			$form['yearly_worker']['worker_year_table'] 	= array(
				'#prefix' 			=> '<div id="fees_details_div">',
			 	'#suffix' 			=> '</div>',
  				'#type'				=> 'markup',
				'#markup'			=> show_fees_registration_2mii($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid,$last_validlicensedate),
			
			);
			
		$form['yearly_worker']['worker_amand_fees'] 	= array(
		 		
				'#prefix' 			=> '<div id="amand_fees_details_div">',
				'#suffix' 			=> '</div>',
		   		'#type'				=> 'markup',
				'#markup'			=> show_fees_registration_amand_2mii($application_id,$service_id,$factory_type_id,$reference_no)
			);
	}if($factory_type_id == 3){
			$form['yearly_worker']['worker_year_table'] 	= array(
  				'#type'				=> 'markup',
				'#prefix' 			=> '<div id="fees_details_div">',
			 	'#suffix' 			=> '</div>',
				'#markup'			=> show_fees_registration_section_85($application_id,$service_id,$factory_type_id,$reference_no,$last_validlicensedate)
				
  
			);
			
		$form['yearly_worker']['worker_amand_fees'] 	= array(
		 		
				'#prefix' 			=> '<div id="amand_fees_details_div">',
				'#suffix' 			=> '</div>',
		   		'#type'				=> 'markup',
				'#markup'			=> show_fees_registration_amand($application_id,$service_id,$factory_type_id,$reference_no)
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
				'#markup'			=> show_fees_registration($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid,$last_validlicensedate)
				
  
			);
			
			
			$form['yearly_worker']['worker_amand_fees'] 	= array(
		 		
				'#prefix' 			=> '<div id="amand_fees_details_div">',
				'#suffix' 			=> '</div>',
		   		'#type'				=> 'markup',
				'#markup'			=> show_fees_registration_amand($application_id,$service_id,$factory_type_id,$reference_no)
			);
			
	}if($factory_type_id == 2){
		$form['yearly_worker']['worker_year_table'] 	= array(
				'#prefix' 			=> '<div id="fees_details_div">',
			 	'#suffix' 			=> '</div>',
  				'#type'				=> 'markup',
				'#markup'			=> show_fees_registration_2mii($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid,$last_validlicensedate)
				
  
			);
		$form['yearly_worker']['worker_amand_fees'] 	= array(
		 		
				'#prefix' 			=> '<div id="amand_fees_details_div">',
				'#suffix' 			=> '</div>',
		   		'#type'				=> 'markup',
				'#markup'			=> show_fees_registration_amand_2mii($application_id,$service_id,$factory_type_id,$reference_no)
			);
			
	}if($factory_type_id == 3){
		
		$form['yearly_worker']['worker_year_table'] 	= array(
  				'#type'				=> 'markup',
				'#prefix' 			=> '<div id="fees_details_div">',
			 	'#suffix' 			=> '</div>',
				'#markup'			=> show_fees_registration_section_85($application_id,$service_id,$factory_type_id,$reference_no,$last_validlicensedate)
				
  
			);
			
			$form['yearly_worker']['worker_amand_fees'] 	= array(
		 		
				'#prefix' 			=> '<div id="amand_fees_details_div">',
				'#suffix' 			=> '</div>',
		   		'#type'				=> 'markup',
				'#markup'			=> show_fees_registration_amand($application_id,$service_id,$factory_type_id,$reference_no)
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
	$commands[] = ajax_command_replace('#amand_fees_details_div', drupal_render($form['yearly_worker']['worker_amand_fees']));
	
	return array('#type' => 'ajax', '#commands' => $commands);
}


function view_payment_deatils($application_id,$service_id,$factory_type_id,$reference_no){
	$output = '';
	$sl = 0;
	$header = array(
		array('data'=> 'SL No'),
		array('data'=> 'BRN/GRN/Challan Number'),
		array('data'=> 'Payment date'),
		array('data'=> 'Amount'),
		array('data'=> 'Challan')
	);
	$challanData = get_challan_doc_all($service_id,$application_id,$factory_type_id,$reference_no);
	
	foreach($challanData as $history){
	
		$displayLink = l('<i class="ace-icon fa fa-file-pdf-o bigger-130"></i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $history->id).'/'.encryption_decryption_fun('encrypt', 'REC').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));

		$sl		 = $sl+1;	
		$rows [] = array(  
			array('data' => $sl), 	
			array('data' => t($history->brn_grn_challan_no)), 
			array('data' => t(date('dS M Y', strtotime($history->date_payment)))),
			array('data' => t($history->payment_amount)),
			array('data' => $displayLink),	
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
function details_fees_renewal_submit($form, &$form_state){
	global $user;
	$val   								= 	$form_state['values'];

	$uid 			    			=  $user->uid;
	$factory_type						= 	encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$service_id							= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$application_id						= 	encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$reference_no						= 	encryption_decryption_fun('decrypt',$val['reference_no_hidden']);	
	$previousexcess_paid_hidden			= 	encryption_decryption_fun('decrypt',$val['previousexcesspaid_hidden']);
	$last_validlicensedate				= 	encryption_decryption_fun('decrypt',$val['last_validlicensedate']);
	$period_for_application				= 	encryption_decryption_fun('decrypt',$val['period_for_application_hidden']);
	$challan_number						= 	$val['challan_number'];
	$payment_date						= 	$val['payment_date'];
	$payment_amount						= 	$val['payment_amount'];
	$is_payment_mad						= 	$val['manual_payment'];
	$upload_chanal 						=   file_load($val['upload_chanal']);
	if($val['op'] =="Add payment"){
		if($upload_chanal != "" ){
			$gren_no_exists =fun_check_grn($challan_number);
			if(empty($gren_no_exists)|| $gren_no_exists==NULL || $gren_no_exists==0){

				$path_challan = pathinfo($upload_chanal->filename);

				$document_name = "Authenticated document regarding deposition of fees.";
				$document_listid =  fun_fetch_document_listid($document_name);
				
				$new_filename_challan = 'payment_receipt_'.date('Y').'_'.$challan_number.'_'.time().'.'.$path_challan['extension'];
				$upload_chanal->filename = $new_filename_challan;
				file_save($upload_chanal);

				$filename_challan_arr = explode("/", $upload_chanal->uri);
	
				$filepathSave_challan 	= file_get_contents(escapefile_url('public://upload/upload_pdf/'.$filename_challan_arr[4]));
			
				$content_challan		= base64_encode($filepathSave_challan);

				$challan_doc_content_arr = array(
					'upload_doc_content' => $content_challan,
				);
				
				db_insert('fa_caf_upload_doc_content')->fields($challan_doc_content_arr)->execute();
				$query_cha = db_select('fa_caf_upload_doc_content','cudc');
				$query_cha->addExpression('MAX(id)','max_id');
				$result_cha = $query_cha->execute();
				$data_cha = $result_cha->fetchObject();

				$challan_upload_doc_arr = array(
					'application_id' 			=> $application_id,
					'application_reference_no' 	=> $reference_no,
					'file_name' 				=> $new_filename_challan,
					'factory_typeid' 			=> $factory_type,
					'service_id' 				=> $service_id,
					'upload_doc_content_id' 	=> $data_cha->max_id,
					'upload_doc_type' 			=> 'REC',
					'created_by'				=> $uid,
					'created_date' 				=> date('Y-m-d h:i:s'),
					'doc_master_id'				=> $document_listid['id'],
					'identity_flag'				=> $document_listid['identity_flag']
				);

				$fid= db_insert('fa_caf_upload_all_doc')->fields($challan_upload_doc_arr)->execute();
					
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
					'upload_challan_file'			=> $fid
							
			);
				$id = db_insert('fa_manual_payment_history')->fields($add_payment_details)->execute();
			}
			else{
					drupal_set_message('This GRN/BREN('.$challan_number.') is already exists','error');
				}		
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
	}if($val['op'] =="Pay now"){
		if($factory_type == 3){
			save_fees_registration_85($application_id,$service_id,$factory_type,$reference_no,$previousexcess_paid_hidden,$last_validlicensedate);
			
		}if($factory_type == 1){
			save_fees_registration_2mi($application_id,$service_id,$factory_type,$reference_no,$previousexcess_paid_hidden,$last_validlicensedate);
			
		}if($factory_type == 2){
			save_fees_registration_2mii($application_id,$service_id,$factory_type,$reference_no,$previousexcess_paid_hidden,$last_validlicensedate);
			
		}
	
	}
	
}
function show_fees_registration($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid,$last_validlicensedate){
	

	 $previous_amount_pre 				=   $previous_excess_paid;
	$Registration_fees 					= 	0;
	$created_by 						=   $user->uid;
	$modifi_date 						=   date("Y-m-d",strtotime($date_of_amenability));
	$last_validity						=   date("Y-m-d",strtotime($last_validlicensedate));
	$i									=	1;
	


$date = date_create($last_validlicensedate);
$date_convert = date_format($date, "Y");

$date_convert1 = date_format($date, "Y-m-d");	

	$output = '
			<div class="box-body">
						<table class="table table-bordered" width="100%">
							<tr>
				
				<th>SL</th>
  				<th>Application Period</th>
   				<th>Category(KW/HP)</th>
   				<th>Total Workers</th>
				<th>Schedule Fees(Rs)<br>(calculated fess * total application year)</th>
				<th>Late Fees(Rs)</th>   
				
				<th>Previous Excess Paid(Rs.)</th>
				<th>Balance(Rs)</th>
				<th>Due Amount(Rs)</th>
  	 		</tr>';
 
	$power_details		= yearly_power_worker_details($application_id,$factory_type_id,$service_id,$reference_no);
	//print_r($power_details);die();
    foreach($power_details as $rows){
		$other = $rows->type_power_station;
	}
	$license_fees 			= 0;
	$late_fees				= 0;
	$current_year 			= date("Y");
	$fees 					= 0;
	$i						= 1;  
	$total_license_fees  	= 0;
	$total_transfer_fees 	= 0;
	$flag_adjust_balance 	= 0;
	$flag_late_calulate  	= 0;
	$flag_payment  			= '';
	$payment = 0;
	$late_flag = 0;
	$flag_balance = 0;
	$fees_to_paid =0;
	$due_flag = 0;
	$previous_amount_flag =0;
	$get_fa_cafa 				= 	get_fa_cafa($application_id);
 	$previous_amount_pre		= 	$get_fa_cafa['previous_excess_paid'];
	$balance_amount_preservice	= 	$get_fa_cafa['balance_amount'];
 
	 $previous_amount_pre= $balance_amount_preservice;
	if($other == "other"){
		if($date_convert1 == '2018-12-31'){
				 
				// $application_date 		= date('Y-m-d',strtotime(date("Y-m-d", strtotime('2019-01-15'))));
				 $application_date 		= date('Y-m-d');
				 $power_hp_kw  			= $rows->installed_power_hp;
				 $unit 		  			= 'Hp';
				
				 $max_payment_date 		= get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
				 $payment 				= 0;
				 
				 if(!empty($max_payment_date)){
					  $manual_payment =  manual_payment_deatils($application_id,$service_id,$factory_typeid,$reference_number); 
					 $manual_payment_count =  count($manual_payment); 
					  foreach($power_details as $rows){
						   $result_data  = fees_calculation_registration($rows->installed_power_hp,$rows->worker_total,$rows->calculate_starting_year);
						  $license_fees=$license_fees_1 = $result_data['fees']*$rows->valid_time_period;
						   if($previous_amount_pre>$license_fees_1){
							  $license_fees_1 = 0;
							  $balnce_amount = $previous_amount_pre-$license_fees_1;
							  $due_amount = 0;
							  $late_fees_pay = 0;
						  }if($previous_amount_pre<$license_fees_1){
							  $balnce_amount = 0;
							  $license_fees_1 = $license_fees_1-$previous_amount_pre;
							  $due_amount = 0;
						  }if($previous_amount_pre==$license_fees_1){
							  $balance_amount = 0;
							  $license_fees_1 = 0;
							  $due_amount = 0;
							  $late_fees_pay = 0;
						  }if($license_fees_1>0){ $license_start_date = $rows->calculate_starting_year;
						  if($license_start_date=='2019-01-01'){
							    	 $datey_cuttoff 		= '2019-01-15'; 
						}else{
							 		
									 	$year  			= date('Y',strtotime($license_start_date));
									  	$month 			= date('m',strtotime($license_start_date));
									   	$day  			= date('d',strtotime($license_start_date));
							 			$from_unix_time = mktime(0, 0, 0, $month, $day, $year);
										$day_before 	= strtotime("yesterday", $from_unix_time);
										$datey_cuttoff 	= date('Y-m-d', $day_before);
									
								
						}
						
						while(($payment < $manual_payment_count)&& ($flag_payment!= 'exhausted')){
							if($rows->calculate_starting_year > $manual_payment[$payment]->date_payment){
								 $previous_amount_pre = $previous_amount_pre+$manual_payment[$payment]->payment_amount;
							     if($license_fees_1 == $manual_payment[$payment]->payment_amount){
									 	$flag_payment = 'exhausted';
									  	$due_flag = 0;
								}if($license_fees_1 > $manual_payment[$payment]->payment_amount){
										 $due_amount_pre = ($license_fees_1-$manual_payment[$payment]->payment_amount);
									 	 $license_fees_1 = $due_amount_pre;
									 	$due_flag = 1;
								}if($license_fees < $manual_payment[$payment]->payment_amount){
									 $balance_amount = ($manual_payment[$payment]->payment_amount-$license_fees_1);
									 $due_flag = 0;
								}
							 }//echo $payment;
						if($rows->calculate_starting_year <=$manual_payment[$payment]->date_payment){
								 $previous_amount_pre = $previous_amount_pre+$manual_payment[$payment]->payment_amount;
							}
						 	$payment++;
						 
						
						
						}
							
				
				 
				 if($application_date < $datey_cuttoff){//echo 'hie';
						 $late_fees_pay = 0;
						$due_amount 	= $license_fees+$late_fees_pay;
					}if($application_date >= $datey_cuttoff){
										
							if($rows->calculate_starting_year < $application_date){
										$start_date				= date_create($rows->calculate_starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
										$days_differ_app  		= $diff->days; 
							}if($rows->calculate_starting_year < $datey_cuttoff){
										$start_date				= date_create($rows->calculate_starting_year);
										$datey_cuttoff1			= date_create($datey_cuttoff);
										$diff					= date_diff($datey_cuttoff1,$start_date);
										$days_differ_cutt 		= $diff->days;
							}if($days_differ_app>$days_differ_cutt){
										$big_diff = $days_differ_app;
							}else{
									    $big_diff = $days_differ_cutt;
							}
							if($rows->calculate_starting_year > $application_date){
										$start_date		= date_create($rows->calculate_starting_year);
										$application_date1		= date_create($application_date);
										
										$diff			= date_diff($start_date,$application_date1);
										$big_diff  		= $diff->days;
							}
						
							if($due_flag ==1){
								$license_fees_late = $due_amount_pre;
							}else{
								$license_fees_late = $license_fees;
							}
							
							if($big_diff>=1 && $big_diff<=90){
									$late_fees_pay = ($license_fees_late)*(50/100);
													
							}if($big_diff>91){
									$late_fees_pay = $license_fees_late;
							}
							
							$due_amount 	= $license_fees+$late_fees_pay;
							if($previous_amount_flag == 1){
							
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
										
									
				}
						  }else{
							  $previous_amount_pre = $balnce_amount;
						  }
						 
				$output.='<tr>
						<td>'.$i.'</td>
		             	<td>'.$rows->calculate_year.'</td>
						<td>'.$power_hp_kw.'('.$unit.')</td>
						<td>'.$rows->worker_total.'</td>
						<td>'.$license_fees.'  ('.$result_data['fees'].'*'.$rows->valid_time_period.')</td>
						<td>'.$late_fees_pay.'</td>
						<td>'.$previous_amount_pre.'</td>
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';	
						
					
										
					
		$output.='</tr>';
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$late_fees 			=0;
		$late_fees_pay = 0;
		$due_flag =0;
					 
				
				 }
				 }
				 if(empty($max_payment_date)){
					  
						if($license_start_date=='2019-01-01'){
							    	 $datey_cuttoff 		= '2019-01-15'; 
						}else{
							 		
									 	$year  			= date('Y',strtotime($license_start_date));
									  	$month 			= date('m',strtotime($license_start_date));
									   	$day  			= date('d',strtotime($license_start_date));
							 			$from_unix_time = mktime(0, 0, 0, $month, $day, $year);
										$day_before 	= strtotime("yesterday", $from_unix_time);
										$datey_cuttoff 	= date('Y-m-d', $day_before);
									
								
						}
								
								foreach($power_details as $rows){
									$result_data  = fees_calculation_registration($rows->installed_power_hp,$rows->worker_total,$rows->calculate_starting_year);
									$license_fees = $result_data['fees']*$rows->valid_time_period;
									
										
										if($rows->calculate_starting_year < $application_date){
											   		$start_date				= date_create($rows->calculate_starting_year);
													$application_date1		= date_create($application_date);
													$diff					= date_diff($application_date1,$start_date);
												    $days_differ_app  		= $diff->days; 
										}if($rows->calculate_starting_year < $datey_cuttoff){
													$start_date				= date_create($rows->calculate_starting_year);
													$datey_cuttoff1			= date_create($datey_cuttoff);
													$diff					= date_diff($datey_cuttoff1,$start_date);
												    $days_differ_cutt 		= $diff->days;
										}if($days_differ_app>$days_differ_cutt){
													$big_diff = $days_differ_app;
										}else{
													$big_diff = $days_differ_cutt;
										}
										if($rows->calculate_starting_year > $application_date){ 
													$start_date		= date_create($rows->calculate_starting_year);
													$application_date1		= date_create($application_date);
													$diff			= date_diff($start_date,$application_date);
												    $big_diff  		= $diff->days;
													
													
										
										if($big_diff>=1 && $big_diff<=90){
											$late_fees = ($license_fees)*(50/100);
													
										}if($big_diff>91){
													$late_fees = $license_fees;
										}
											
										$payble_fees 	= $license_fees+$late_fees;
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
											
										
									//}
									
								$output.='<tr>
						<td>'.$i.'</td>
		             	<td>'.$rows->calculate_year.'</td>
						<td>'.$power_hp_kw.'('.$unit.')</td>
						<td>'.$rows->worker_total.'</td>
						<td>'.$license_fees.'  ('.$result_data['fees'].'*'.$rows->valid_time_period.')</td>
						<td>'.$late_fees_pay.'</td>
						<td>'.$previous_amount_pre.'</td>
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';	
										
					
		$output.='</tr>';
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$late_fees 			=0;
		$late_fees_pay = 0;
		
	}
							
						}
						
					
				
				
			}
	}
	    if($date_convert >'2018'){
				$previous_amount_pre= $previous_excess_paid;
				foreach($power_details as $rows){		
					$power_hp_kw 			= $rows->installed_power_hp;
					$unit 		 			= 'Hp';
					$result_data 			= fees_calculation_registration($rows->installed_power_hp,$rows->worker_total,$rows->calculate_starting_year);
					$license_fees		 	= $result_data['fees']*$rows->valid_time_period;
					$max_payment_date 		= get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
					$start_date				= date_create($rows->calculate_starting_year);
		 			$application_date 		= date('Y-m-d');
					$application_date1		= date_create($application_date);
					$late_fees 				= 0;
				if($rows->calculate_starting_year < $application_date){ 
							$diff 		= date_diff($start_date,$application_date1);
							$big_diff   = $diff->days;
				}
					
					if($big_diff>=1 && $big_diff<=90){
									$late_fees = ($license_fees)*(50/100);
													
					}if($big_diff>91){
									$late_fees = $license_fees;
					}
					
				if(!empty($max_payment_date)){
					$payble_fees 	= $license_fees+$late_fees;
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
					$late_fees_pay 	= $late_fees;
					$due_amount 	= $license_fees+$late_fees_pay;
					$balance_amount = 0;
					
			
			
					
	}
				$output.='<tr>
						<td>'.$i.'</td>
		             	<td>'.$rows->calculate_year.'</td>
						<td>'.$power_hp_kw.'('.$unit.')</td>
						<td>'.$rows->worker_total.'</td>
						<td>'.$license_fees.'  ('.$result_data['fees'].'*'.$rows->valid_time_period.')</td>
						<td>'.$late_fees_pay.'</td>
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
			
	  	   	$i= $i+1;
  		 }
				
				
				
			}
		if($date_convert <= '2015'){ //echo 'hi';
				$max_payment_date = get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
				if(empty($max_payment_date)){
					$application_date 		= date('Y-m-d');
					foreach($power_details as $rows){
							//$application_date 	= '2016-03-31';
							$start_date 		= $rows->calculate_starting_year;
							$cut_off_date_year  = date('Y',strtotime($start_date));
						 	$cut_off_date 		= $cut_off_date_year.'-03-31';
							$power_hp_kw  		= $rows->installed_power_hp;
							$result_data 		= fees_calculation_registration($rows->installed_power_hp,$rows->worker_total,$rows->calculate_starting_year);
							$license_fees 		= $result_data['fees']*$rows->valid_time_period;
							$unit 		 		= 'Hp';
					 		if($application_date<=$cut_off_date ){
								$late_fees = ($license_fees)*(25/100);
						 
					 		}if($application_date>$cut_off_date ){
								$late_fees = ($license_fees)*(50/100);
						 
					 		}
							$late_fees_pay 	= $late_fees;
							$due_amount 	= $license_fees+$late_fees_pay;
							$balance_amount = 0;
							
						$output.='<tr>
						<td>'.$i.'</td>
		             	<td>'.$rows->calculate_year.'</td>
						<td>'.$power_hp_kw.'('.$unit.')</td>
						<td>'.$rows->worker_total.'</td>
						<td>'.$license_fees.'  ('.$result_data['fees'].'*'.$rows->valid_time_period.')</td>
						<td>'.$late_fees_pay.'</td>
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
		
	  	
	 
	   	$i= $i+1;
					}
					
				}
				if(!empty($max_payment_date)){
					$application_date 		= date('Y-m-d');
					$manual_payment			=  manual_payment_deatils($application_id,$service_id,$factory_typeid,$reference_number);
					//print_r($manual_payment);
					 $manual_payment_count 	=  count($manual_payment);// echo '<br/>'; 
					//die();
					//$payment = 0;
					foreach($power_details as $rows){
							$previous_amount_pre = 0;
							$application_date 	= date('Y-m-d');
							$start_date 		= $rows->calculate_starting_year;
							$cut_off_date_year  = date('Y',strtotime($start_date));
						 	$cut_off_date 		= $cut_off_date_year.'-03-31';
							$power_hp_kw  		= $rows->installed_power_hp;
							$result_data 		= fees_calculation_registration($rows->installed_power_hp,$rows->worker_total,$rows->calculate_starting_year);
							$license_fees 		= $result_data['fees']*$rows->valid_time_period;
							$unit 		 		= 'Hp';
							$due_license_amount = $license_fees; 
							 if($previous_amount_pre>$due_license_amount){
							  $due_license_amount = 0;
							  $balnce_amount = $previous_amount_pre-$due_license_amount;
							  $due_amount = 0;
							  $late_fees_pay = 0;
						  }if($previous_amount_pre<$due_license_amount){
							  $balnce_amount = 0;
							  $due_license_amount = $due_license_amount-$previous_amount_pre;
							  $due_amount = 0;
						  }if($previous_amount_pre==$due_license_amount){
							  $balance_amount = 0;
							  $due_license_amount = 0;
							  $due_amount = 0;
							  $late_fees_pay = 0;
						  }if($due_license_amount>0){
							  while($payment < $manual_payment_count) {
								lebel1: if(($start_date>$manual_payment[$payment]->date_payment)&& !empty($manual_payment[$payment]->date_payment)){echo 'run lebel1';	
											if(!empty($last_payment_date)){
												if($start_date>$last_payment_date){
													if($due_license_amount>$balance_license_amount){
																$previous_amount_pre = $balance_license_amount;
																$due_license_amount 	= $due_license_amount-$balance_license_amount;
																$balance_license_amount = 0;
																$last_payment_date 		= NULL;
													}
													if($due_license_amount<$balance_license_amount){
																$due_license_amount 	= 0;
																$balance_license_amount = $balance_license_amount-$due_license_amount;
																$previous_amount_pre = $balance_license_amount;
													}if($due_license_amount==$balance_license_amount){
																$due_license_amount 	= 0;
																$balance_license_amount = 0;
																$last_payment_date 		= NULL;
																$previous_amount_pre = $balance_license_amount;
													}
										}if($start_date<$last_payment_date){
												$previous_amount_pre = $balance_license_amount;
										}
									}
								
								if($due_license_amount>$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 	= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$due_license_amount 	= $due_license_amount - $manual_payment[$payment]->payment_amount;
											$payment				= $payment+1 ;
											$flag_payment 			= 'due';
									 		goto lebel1;
								}
								if($due_license_amount<$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$balance_license_amount 	=  $manual_payment[$payment]->payment_amount-$due_license_amount ;
											$last_payment_date  		= $manual_payment[$payment]->date_payment ;
											$payment					= $payment+1 ;
											$flag_payment  				= 'exhausted';
											$due_amount 				= 	0;
											$late_fees_pay 	 			=	0;
											$late_flag 					=	1;
											$balance_amount 			= 	$balance_license_amount;
											$manual_payment_date 		=  NULL;
											break;
								}
								if($due_license_amount==$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$balance_license_amount 	= 0;
											$last_payment_date  		= NULL;
											$payment					= $payment+1 ;
											$flag_payment  				= 'exhausted';
											$due_amount 				= 0;
											$late_fees_pay 	 			= 0;
											$late_flag 					= 1;
											$balance_amount 			= $balance_license_amount;
											$manual_payment_date 		=  NULL;
											break;
								}
								if($due_license_amount !=0 ||empty($due_license_amount) ){
									if($application_date<=$cut_off_date ){
							 				$late_fees_pay 		= ($due_license_amount)*(25/100);
									 		$due_amount 		= $late_fees_pay+$license_fees;
											$balance_amount 	= $balance_license_amount;
											$late_flag 			=1;
						 			}if($application_date>$cut_off_date ){
										 	$late_fees_pay 		= ($due_license_amount)*(50/100);
										 	$due_amount 		= $late_fees_pay+$license_fees;
											$balance_amount 	= $balance_license_amount;
											$late_flag 			=1;
											
					 				}
								}
								
							}
							    lebel2: if($start_date<$manual_payment[$payment]->date_payment){						
									if(!empty($last_payment_date)){//echo 'payment date is here(12)<br>';	
										if($start_date>$last_payment_date){//echo 'payment date is here(12a)<br>';echo 'due license amount'.$due_license_amount.'<br/>';	
										if($due_license_amount>$balance_license_amount){
											$previous_amount_pre 	= $balance_license_amount;
											$due_license_amount 	= $due_license_amount-$balance_license_amount;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
										}
										if($due_license_amount<$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = $balance_license_amount-$due_license_amount;
											$previous_amount_pre = $balance_license_amount;
										}if($due_license_amount==$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
											$previous_amount_pre = $balance_license_amount;
										}
									}
										if($start_date<$last_payment_date){//echo 'payment date is here(12b)<br>blance amount'.$balance_license_amount.'<br/>';
										if($balance_license_amount != 0){
											$previous_amount_pre = $balance_license_amount;
											$flag_balance = 1;
										}
											
											/*if($previous_amount_pre == 0 || empty($previous_amount_pre)){
												$flag_balance = 0;
											}else{
												
											}*/
											
										}
									}
									
									if($late_flag == 0 || empty($late_flag)){
										if($manual_payment[$payment]->date_payment<=$cut_off_date ){//echo 'late1(12c)<br>';
							 			$late_fees_pay 	= ($due_license_amount)*(25/100);
									 	$due_amount 	= $late_fees_pay+$due_license_amount;
										$balance_amount = $balance_license_amount;
										$late_flag = 1;
						 			}if($manual_payment[$payment]->date_payment>$cut_off_date ){
										  $late_fees_pay 	= ($due_license_amount)*(50/100);
										  $due_amount 			= $late_fees_pay+$due_license_amount;
										  $balance_amount 		= $balance_license_amount;
										 $late_flag 			= 1;
										// echo 'late2(12c)<br>';echo 'due license amount'.$due_amount.'<br/>';	;
											
					 				}
								}
									
									
									if($due_amount>$manual_payment[$payment]->payment_amount){//echo 'pay(12d)<br>';
										
										if($flag_balance == 1){// echo $flag_balance.'---'. $previous_amount_pre.'+'.$manual_payment[$payment]->payment_amount.'-----------';
												 $previous_amount_pre 	=  $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												//echo '----------due----';
											  	 $due_amount 			=  $due_amount-$previous_amount_pre ;
												$flag_balance = 0;
												//echo '<br/>';
											}else{//echo $flag_balance.'---'.$previous_amount_pre.'+'.$manual_payment[$payment]->payment_amount.'-----------';
												 $previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												 $due_amount 	= $due_amount - $manual_payment[$payment]->payment_amount;
												// echo '<br/>';
											}
											
										//echo '<br/>';
										
										$late_flag =1;
										$balance_license_amount = 0;
										$payment	= $payment+1 ;
										$flag_balance =0;
									 	goto lebel2;
									}
									if($due_amount<$manual_payment[$payment]->payment_amount){//echo 'pay1(12d)<br>';
										 	//$manual_payment[$payment]->payment_amount;
											
											if($flag_balance == 1){
												$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												 $balance_license_amount 	=  $previous_amount_pre-$due_amount ;
											}else{
												$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												 $balance_license_amount 	=  $manual_payment[$payment]->payment_amount-$due_amount ;
											}
											
											
										 	$last_payment_date  		= $manual_payment[$payment]->date_payment ;
											$due_amount 				= 0;
											$flag_payment  				= 'exhausted';
											$late_flag 					= 1;
											$payment					= $payment+1 ;
											$flag_balance = 0;
											break;
									}
									if($due_amount==$manual_payment[$payment]->payment_amount){//echo 'con1b---';
										$previous_amount_pre 	    = $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										$balance_license_amount 	=  0;
										$last_payment_date          = NULL;
										$flag_payment  				= 'exhausted';
										$late_flag 					=1;
										break;
									}
								}
								lebel3: if($start_date==$manual_payment[$payment]->date_payment){//echo 'run lebel3';	
									
									if(!empty($last_payment_date)){
										if($start_date>$last_payment_date){
										if($due_license_amount>$balance_license_amount){
											$previous_amount_pre 	= $balance_license_amount;
											$due_license_amount 	= $due_license_amount-$balance_license_amount;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
										}if($due_license_amount<$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = $balance_license_amount-$due_license_amount;
											$previous_amount_pre 	= $balance_license_amount;
										}if($due_license_amount==$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
											$previous_amount_pre 	= $balance_license_amount;
										}
									}
										if($start_date<$last_payment_date){
											$previous_amount_pre = $balance_license_amount;
										}
									}
									
								
									if($application_date<=$cut_off_date ){
							 			$late_fees_pay 	= ($due_license_amount)*(25/100);
									 	$due_amount 		= $late_fees_pay+$due_license_amount;
										$balance_amount = $balance_license_amount;
										$late_flag = 1;
						 			}if($application_date>$cut_off_date ){
										 $late_fees_pay = ($due_license_amount)*(50/100);
										//echo '<br/>';
										 $due_amount 	= $late_fees_pay+$due_license_amount;
										$balance_amount = $balance_license_amount;
										$late_flag = 1;
											
					 				}
									
									if($due_amount>$manual_payment[$payment]->payment_amount){
										 	$previous_amount_pre 	= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										 	$due_amount 			= $due_amount - $previous_amount_pre;
											$late_flag 				= 1;
											$payment				= $payment+1 ;
									 		goto lebel3;
									}
									if($due_amount<$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$balance_license_amount 	=  $manual_payment[$payment]->payment_amount-$due_amount ;

											$last_payment_date  		= $manual_payment[$payment]->date_payment ;
											$flag_payment  				= 'exhausted';
											$late_flag 					=1;
											break;
									}
									if($due_amount==$manual_payment[$payment]->payment_amount){
										$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										$balance_license_amount 	=  0;
										$last_payment_date 	 		= NULL ;
										$payment					= $payment+1 ;
										$flag_payment  		= 'exhausted';
										$late_flag =1;
										break;
									}
								}
								
							} 
						//echo $payment;die();
							if($late_flag ==0  ){
								if($application_date<=$cut_off_date ){
							 		$late_fees_pay 	= ($due_license_amount)*(25/100);
									$due_amount 	= $late_fees_pay+$due_license_amount;
									$balance_amount = $balance_license_amount;
						 		}if($application_date>$cut_off_date ){
									$late_fees_pay 	= ($due_license_amount)*(50/100);
									$due_amount 	= $late_fees_pay+$due_license_amount;
									$balance_amount = $balance_license_amount;
											
					 			}
								if($balance_license_amount>$due_amount){//echo $due_amount.'----'.$balance_license_amount;
									$previous_amount_pre 	= $balance_license_amount;
									 $balance_amount 		= $previous_amount_pre-$due_amount;
									$due_amount 			= 0;
									 $balance_license_amount = $balance_amount;
								}if($balance_license_amount<$due_amount){
									$previous_amount_pre 	= $balance_license_amount;
									$due_amount 			= $due_amount-$balance_license_amount;
									$balance_amount 		= 0;
									$balance_license_amount = $balance_amount;
								}if($balance_license_amount==$due_amount){
									$previous_amount_pre 	= 0;
									$due_amount 			= 0;
									$balance_amount 		= 0;
									$balance_license_amount = $balance_amount;
								}
							
							}
							 $balance_amount = $balance_license_amount;
						
							$due_amount_paid = $due_amount+$due_amount_paid;
						  }else{
							  $previous_amount_pre = $balnce_amount;
						  }
							
							
							
							 
						
						$output.='<tr>
									<td>'.$i.'</td>
		             				<td>'.$rows->calculate_year.'</td>
									<td>'.$power_hp_kw.'('.$unit.')</td>
									<td>'.$rows->worker_total.'</td>
									<td>'.$license_fees.'  ('.$result_data['fees'].'*'.$rows->valid_time_period.')</td>
									<td>'.$late_fees_pay.'</td>
								
									<td>'.$previous_amount_pre.'</td>
									<td>'.$balance_amount.'</td>
									<td>'.$due_amount.'</td>';	
						$output.='</tr>';	
						$late_fees_pay 			= 	0;
						$previous_amount_pre 	=	0;
						$due_amount 			= 	0;
						$late_flag 				=	0;
						$flag_payment 			=	'';
						$balance_amount =0;	
						$fees_to_paid = $due_amount_paid;
						$i++;
					}
				}
				
		}
}
	
	    if($rows->type_power_station == "power_generating_station"){
				$power_hp_kw 			= $rows->installed_power;
				$unit 		 			= 'KW';
				foreach($power_details as $rows){	
				$result_data 			= fees_calculation_registration_power_station($rows->installed_power,$rows->calculate_starting_year);
				
				$fees		 	 		= $result_data['fees']*$rows->valid_time_period;
				
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
				if(empty($max_payment_date)){//echo 'hi';die();
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
						
						<td>'.$fees.'  ('.$result_data['fees'].'*'.$rows->valid_time_period.')</td>
						<td>'.$late_fees_pay.'</td>
						
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
	
	   	$i= $i+1;
		
		}
		}
	$output .='</table>
	
				<strong><font color="#FF0000">Fees to be paid for Licence:-'.($fees_to_paid).'</font></strong>
				</div>'
				;
			
		 $total_fees_paid_to_end = $fees_to_paid;
		 session_start();
		 $_SESSION["renewal_fees"]=$fees_to_paid;
		 $_SESSION["balance_renewal"]=$balance_amount;
	return $output;
	
}

function show_fees_registration_amand($application_id,$service_id,$factory_type_id,$reference_number){
	$previous_excess_paid =$previous_excess_paid1=  $_SESSION["balance_renewal"];

	$amandment_fess = 1000;
	$sl = 1;
	$Registration_fees 					= 	0;
	$created_by 						=   $user->uid;
	$modifi_date 						=   date("Y-m-d",strtotime($date_of_amenability));
	
	$i									=	1;
	$license_fees 						= 	0;
	$late_fees							= 	0;
	$current_year 						= 	date("Y");
	$fees 								= 	0;
	$i									= 	1;  
	$total_license_fees  				= 	0;
	$total_transfer_fees 				= 	0;
	$flag_adjust_balance 				= 	0;
	$flag_late_calulate  				= 	0;
	
	$flag_payment  						= '';
	$payment							= 0;
	$late_flag = 0;
	$flag_balance = 0;
	$fees_to_paid =0;
	$due_flag = 0;
	$previous_amount_flag =0;
	$total_amand_fees =0;
	$application_date 		= date('Y-m-d');
		$late_fees 				= 0;
	$output = '
			 <div class="box-body"><div class="table-responsive">
			<table class="table table-bordered" width="100%">
			<thead>
			<tr>
				<th colspan="12">Amandement Fess Calculation</th>
			</tr>
			<tr>
				<th>SL</th>
  				<th>Application Period</th>


				<th>Amandment Fees</th>
				<th>Previous Power</th>
   				<th>Previous Total Workers</th>
				<th>Previous Paid(Rs.)</th>
   				<th>Category(KW/HP)</th>
   				<th>Total Workers</th>
				<th>Schedule Fees+Late Fess(Rs)<br></th>
				<th>Balance(Rs)</th>
				<th>Due Amount(Rs)</th>
			
  	 		</tr>';
			
			$amend_value = fetch_old_data($application_id,$service_id,$factory_type_id,$reference_number);
		//print_r($amend_value);die;
			foreach($amend_value as $amand_row){
				$present_totalworker 			= $amand_row->worker_total;
				$present_power 		 			= $amand_row->installed_power;
				$present_installed_power_unit 	= $amand_row->power_unit;
				$previous_worker 		 		= $amand_row->previous_worker;
				$amand_year 		 			= $amand_row->service_year;
				$amand_valid_time_period 		= $amand_row->valid_time_period;
				$amand_starting_year		 	= $amand_row->starting_year;
				$amand_valid_year		 		= $amand_row->valid_year;
				$previous_power		 			= $amand_row->previous_power;
				$previous_power_unit		 	= $amand_row->previous_power_unit;
				
				
				$last_validity					=   date("Y-m-d",strtotime($amand_valid_year));
				 $last_validity_year  			= 	date('Y',strtotime($amand_valid_year));
				if($present_installed_power_unit == "HP"){
					 $fees_previous  				= fees_calculation_registration($previous_power,$previous_worker,$amand_starting_year);
					 $fees_previous_paid 			= ($fees_previous['fees']*$amand_valid_time_period);
					 $fees_previous_paid				= $fees_previous_paid+$previous_excess_paid;
						if($last_validity == '2018-12-31'){
				  					
									$power_hp_kw  			= $present_power;
				 					$unit 		  			= 'Hp';
				 					$previous_amount_pre	= $fees_previous_paid;
				 					$payment 				= 0;
				 
				 					
									if(!empty($fees_previous_paid)){
					
					  
						   $result_data  = fees_calculation_registration($present_power,$present_totalworker,$amand_starting_year);
						  
						  $license_fees=$license_fees_1 = $result_data['fees']*$amand_valid_time_period;
						   $license_start_date = $amand_starting_year;
						  if($license_start_date=='2019-01-01'){
							    	 $datey_cuttoff 		= '2019-01-15'; 
						}else{
							 		
									 	$year  			= date('Y',strtotime($license_start_date));
									  	$month 			= date('m',strtotime($license_start_date));
									   	$day  			= date('d',strtotime($license_start_date));
							 			$from_unix_time = mktime(0, 0, 0, $month, $day, $year);
										$day_before 	= strtotime("yesterday", $from_unix_time);
										$datey_cuttoff 	= date('Y-m-d', $day_before);
									
								
						}
						
						
					
				 
				 if($application_date < $datey_cuttoff){
						 $late_fees_pay = 0;
						 if($license_fees>$fees_previous_paid){
							  $due_amount 	=(($license_fees-$fees_previous_paid)+$late_fees_pay);
						 } else{
							 $due_amount 	=(($fees_previous_paid-$license_fees)+$late_fees_pay);
						 }
						
					}if($application_date >= $datey_cuttoff){
										
							if($amand_starting_year < $application_date){
										$start_date				= date_create($amand_starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
										$days_differ_app  		= $diff->days; 
							}if($amand_starting_year < $datey_cuttoff){
										$start_date				= date_create($amand_starting_year);
										$datey_cuttoff1			= date_create($datey_cuttoff);
										$diff					= date_diff($datey_cuttoff1,$start_date);
										$days_differ_cutt 		= $diff->days;
							}if($days_differ_app>$days_differ_cutt){
										$big_diff = $days_differ_app;
							}else{
									    $big_diff = $days_differ_cutt;
							}
							if($amand_starting_year > $application_date){
										$start_date		= date_create($amand_starting_year);
										$application_date1		= date_create($application_date);
										
										$diff			= date_diff($start_date,$application_date1);
										$big_diff  		= $diff->days;
							}
						
						
						if($license_fees>$fees_previous_paid){
							   $license_fees_late 	=$license_fees-$fees_previous_paid;
						 } else{
							  $license_fees_late 	=$fees_previous_paid-$license_fees;
						 }
							
							if($big_diff>=1 && $big_diff<=90){
									 $late_fees_pay = ($license_fees_late)*(50/100);
													
							}if($big_diff>91){
									 $late_fees_pay = $license_fees_late;
							}
							
							  $due_amount = $license_fees_late+$late_fees_pay;
							$balance_amount = 0;			
										
									
				}
					
				$output.='<tr>
						<td>'.$sl.'</td>
		             	<td>'.$amand_year.'</td>
						<td>'.$amandment_fess.'</td>
						<td>'.$previous_power.'('.$previous_power_unit.')</td>
						<td>'.$previous_worker.'</td>	
						<td>'.$fees_previous_paid.'</td>
						<td>'.$present_power.'('.$present_installed_power_unit.')</td>
						<td>'.$present_totalworker.'</td>
						<td>'.$payblefess.'(('.$result_data['fees'].'*'.$amand_valid_time_period.')+'.$late_fees.')'.'</td>
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';
					
		$output.='</tr>';
		$sl++;		
		$balance_amount = 0;			
				 
				$_SESSION["renewal_amand_balance"]	=$balance_amount;
				 
				 }
				 					
				
				
			}
						if($last_validity_year > '2018'){
				           		
							$power_hp_kw 			= $present_power;
							$unit 		 			= 'Hp';
							$result_data  			= fees_calculation_registration($present_power,$present_totalworker,$amand_starting_year);
							$license_fees			=$license_fees_1 = $result_data['fees']*$amand_valid_time_period;
					  	    $license_start_date 	= $amand_starting_year;
							$application_date1		= date_create($application_date);
						
							if($amand_starting_year < $application_date){ //echo 'hi';
									$start_date		= date_create($amand_starting_year);
									$diff			= date_diff($start_date,$application_date1);
									$big_diff  		= $diff->days;
									 $late_year = $diff->y;
									 $late_month = $diff->m;
									 $late_day = $diff->d ;
									if($late_year>0){
										$fees_late_year = $late_year;
									if($late_month>0){
										$fees_late_year = $late_year+1;
									}if($late_month==0 && $late_day >0){
										$fees_late_year = $late_year+1;
									}
									$late_fees = $result_data['fees']*$fees_late_year;
									}if($late_year==0){
										$fees_late_year = 0;
									if($late_month>0){
										 $fees_late_year = 1;
									}if($late_month==0 && $late_day >0){
										$fees_late_year = 1;
									}
									$late_fees = $result_data['fees']*$fees_late_year;
									}
										
							}else{
								$late_fees = 0;
							}
				
							if($big_diff>=1 && $big_diff<=90){
									 $late_fees_pay = ($late_fees)*(50/100);
													
							}if($big_diff>91){
									$late_fees_pay = $late_fees;
							}
					
				//echo $late_fees_pay;die();
							 $payblefess = $license_fees+$late_fees_pay+$amandment_fess;
							  $calculated_fees = $license_fees+$late_fees_pay;
							if($payblefess>$fees_previous_paid){
								$due_amount = $payblefess-$fees_previous_paid;
								$balance_amount = 0;	
							}else{
								$balance_amount = $fees_previous_paid-$payblefess;
								$due_amount = 0;
							}
							
			
				$output.='<tr>
						<td>'.$sl.'</td>
		             	<td>'.$amand_year.'</td>
						<td>'.$amandment_fess.'</td>
						<td>'.$previous_power.'('.$previous_power_unit.')</td>
						<td>'.$previous_worker.'</td>	
						<td>'.$fees_previous_paid.'</td>
						<td>'.$present_power.'('.$present_installed_power_unit.')</td>
						<td>'.$present_totalworker.'</td>
						<td>(('.$result_data['fees'].'*'.$amand_valid_time_period.')+'.$late_fees_pay.')='.$calculated_fees.'</td>
					
						
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';
					
		$output.='</tr>';
		$sl++;	
		
		$_SESSION["renewal_amand_balance"]	=$balance_amount;
			
	}
						if($last_validity_year <= '2015'){
						
							$power_hp_kw 			= $present_power;
							$unit 		 			= 'Hp';
							$result_data  			= fees_calculation_registration($present_power,$present_totalworker,$amand_starting_year);
							$license_fees			= $license_fees_1 = $result_data['fees']*$amand_valid_time_period;
					  	    $license_start_date 	= $amand_starting_year;
							$application_date1		= date_create($application_date);
							$late_fees 				= 0;
							if($amand_starting_year < $application_date){ //echo 'hi';
									$start_date		= date_create($amand_starting_year);
									$diff			= date_diff($start_date,$application_date1);
									$big_diff  		= $diff->days;
									 $late_year = $diff->y;
									 $late_month = $diff->m;
									 $late_day = $diff->d ;
									if($late_year>0){
										$fees_late_year = $late_year;
									if($late_month>0){
										$fees_late_year = $late_year+1;
									}if($late_month==0 && $late_day >0){
										$fees_late_year = $late_year+1;
									}
									$late_fees = $result_data['fees']*$fees_late_year;
									}if($late_year==0){
										$fees_late_year = 0;
									if($late_month>0){
										 $fees_late_year = 1;
									}if($late_month==0 && $late_day >0){
										$fees_late_year = 1;
									}
									$late_fees = $result_data['fees']*$fees_late_year;
									}
										
							}else{
								$late_fees = 0;
							}
					
							if($big_diff>=1 && $big_diff<=90){
									$late_fees = ($late_fees)*(50/100);
													
							}if($big_diff>91){
									$late_fees = $late_fees;
							}
					
				
							 $payblefess = $license_fees+$late_fees+$amandment_fess;
							 $calculated_fees = $license_fees+$late_fees_pay;
							if($payblefess>$fees_previous_paid){
								$due_amount = $payblefess-$fees_previous_paid;
								$balance_amount = 0;	
							}else{
								$balance_amount = $fees_previous_paid-$payblefess;
								$due_amount = 0;
							}
							
			
				$output.='<tr>
						<td>'.$sl.'</td>
		             	<td>'.$amand_year.'</td>
						<td>'.$amandment_fess.'</td>
						<td>'.$previous_power.'('.$previous_power_unit.')</td>
						<td>'.$previous_worker.'</td>	
						<td>'.$fees_previous_paid.'</td>
						<td>'.$present_power.'('.$present_installed_power_unit.')</td>
						<td>'.$present_totalworker.'</td>
						<td>(('.$result_data['fees'].'*'.$amand_valid_time_period.')+'.$late_fees.')='.$calculated_fees.'</td>
						
						
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';
					
		$output.='</tr>';
		$sl++;
		
		$_SESSION["renewal_amand_balance"]	=$balance_amount;
				}
				           		
				$amandment_fess=0;
				$total_amand_fees = $total_amand_fees+$due_amount;		
			}
			
			    if($present_installed_power_unit == "KW"){
					$fees_previous  				= fees_calculation_registration_power_station($previous_power,$amand_starting_year);
					  $fees_previous_paid 			= ($fees_previous['fees']*$amand_valid_time_period);
					 $fees_previous_paid				= $fees_previous_paid+$previous_excess_paid1+$_SESSION["renewal_amand_balance"];
						if($last_validity == '2018-12-31'){
							
									$power_hp_kw  			= $present_power;
				 					$unit 		  			= 'Hp';
				 					$previous_amount_pre	= $fees_previous_paid;
				 					$payment 				= 0;
				 
				 if(!empty($fees_previous_paid)){
					
					  
						   $result_data  = fees_calculation_registration_power_station($present_power,$amand_starting_year);
						  
						  $license_fees=$license_fees_1 = $result_data['fees']*$amand_valid_time_period;
						   $license_start_date = $amand_starting_year;
						  if($license_start_date=='2019-01-01'){
							    	 $datey_cuttoff 		= '2019-01-15'; 
						}else{
							 		
									 	$year  			= date('Y',strtotime($license_start_date));
									  	$month 			= date('m',strtotime($license_start_date));
									   	$day  			= date('d',strtotime($license_start_date));
							 			$from_unix_time = mktime(0, 0, 0, $month, $day, $year);
										$day_before 	= strtotime("yesterday", $from_unix_time);
										$datey_cuttoff 	= date('Y-m-d', $day_before);
									
								
						}
						
						
					
				 
				 if($application_date < $datey_cuttoff){
						 $late_fees_pay = 0;
						 if($license_fees>$fees_previous_paid){
							  $due_amount 	=(($license_fees-$fees_previous_paid)+$late_fees_pay);
						 } else{
							 $due_amount 	=(($fees_previous_paid-$license_fees)+$late_fees_pay);
						 }
						
					}if($application_date >= $datey_cuttoff){
										
							if($amand_starting_year < $application_date){
										$start_date				= date_create($amand_starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
										$days_differ_app  		= $diff->days; 
							}if($amand_starting_year < $datey_cuttoff){
										$start_date				= date_create($amand_starting_year);
										$datey_cuttoff1			= date_create($datey_cuttoff);
										$diff					= date_diff($datey_cuttoff1,$start_date);
										$days_differ_cutt 		= $diff->days;
							}if($days_differ_app>$days_differ_cutt){
										$big_diff = $days_differ_app;
							}else{
									    $big_diff = $days_differ_cutt;
							}
							if($amand_starting_year > $application_date){
										$start_date		= date_create($amand_starting_year);
										$application_date1		= date_create($application_date);
										
										$diff			= date_diff($start_date,$application_date1);
										$big_diff  		= $diff->days;
							}
						
						
						if($license_fees>$fees_previous_paid){
							   $license_fees_late 	=$license_fees-$fees_previous_paid;
						 } else{
							  $license_fees_late 	=$fees_previous_paid-$license_fees;
						 }
							
							if($big_diff>=1 && $big_diff<=90){
									 $late_fees_pay = ($license_fees_late)*(50/100);
													
							}if($big_diff>91){
									 $late_fees_pay = $license_fees_late;
							}
							//echo $late_fees_pay;
							  $due_amount = $license_fees_late+$late_fees_pay+$amandment_fess;
							$balance_amount = 0;			
										
									
				}
					
				$output.='<tr>
						<td>'.$sl.'</td>
		             	<td>'.$amand_year.'</td>
						<td>'.$amandment_fess.'</td>
						<td>'.$previous_power.'('.$previous_power_unit.')</td>
						<td>'.$previous_worker.'</td>	
						<td>'.$fees_previous_paid.'</td>
						<td>'.$present_power.'('.$present_installed_power_unit.')</td>
						<td>'.$present_totalworker.'</td>
						<td>'.$due_amount.'</td>
						
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';
					
		$output.='</tr>';
		$sl++;		
		$balance_amount = 0;
		
			$_SESSION["renewal_amand_balance"]	=$balance_amount;		
		//$total_amand_fees = $total_amand_fees+$due_amount;		 
				
				 
				 }
			
				
				
			}
						if($last_validity_year > '2018'){
							
				           		
							$power_hp_kw 			= $present_power;
							$unit 		 			= 'KW';
							$result_data  			= fees_calculation_registration_power_station($present_power,$amand_starting_year);
							$license_fees			= $license_fees_1 = $result_data['fees']*$amand_valid_time_period;
					  	    $license_start_date 	= $amand_starting_year;
							$application_date1		= date_create($application_date);
							$late_fees 				= 0;
							if($amand_starting_year < $application_date){
									$start_date		= date_create($amand_starting_year);
									$application_date1		= date_create($application_date);
										$diff			= date_diff($start_date,$application_date1);
										$big_diff  		= $diff->days;
										$late_year = $diff->y;
										$late_month = $diff->m;
										$late_day = $diff->d ;
										if($amand_valid_time_period>1){
											if($late_year>0){
											$fees_late_year = $late_year;
											if($late_month>0){
												$fees_late_year = $late_year+1;
											}if($late_month==0 && $late_day >0){
												$fees_late_year = $late_year+1;
											}
											
											  $late_fees = $result_data['fees']*$fees_late_year;
										}if($late_year==0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month==0 && $late_day >0){
												$fees_late_year = 1;
											}
											 $late_fees = $result_data['fees']*$fees_late_year;
										}
										}
										
										 
							}
					
							if($big_diff>=1 && $big_diff<=90){
									$late_fees_pay = ($late_fees)*(50/100);
													
							}if($big_diff>91){
									 $late_fees_pay = $late_fees;
							}
					
				if(empty($big_diff)|| $big_diff==0 || $big_diff==NULL){
					$late_fees_pay = 0;
				}
							  $payblefess = $license_fees+$late_fees_pay+$amandment_fess;
							   $calculated_fees = $license_fees+$late_fees_pay;
							if($payblefess>$fees_previous_paid){
								$due_amount = $payblefess-$fees_previous_paid;
								$balance_amount = 0;	
							}else{
								$balance_amount = $fees_previous_paid-$payblefess;
								$due_amount = 0;
							}
							
			
				$output.='<tr>
						<td>'.$sl.'</td>
		             	<td>'.$amand_year.'</td>
						<td>'.$amandment_fess.'</td>
						<td>'.$previous_power.'('.$previous_power_unit.')</td>
						<td>'.$previous_worker.'</td>	
						<td>'.$fees_previous_paid.'</td>
						<td>'.$present_power.'('.$present_installed_power_unit.')</td>
						<td>'.$present_totalworker.'</td>
						<td>(('.$result_data['fees'].'*'.$amand_valid_time_period.')+'.$late_fees_pay.')='.$calculated_fees.'</td>
						
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';
					
		$output.='</tr>';
		$sl++;	
		
			$_SESSION["renewal_amand_balance"]	=$balance_amount;
			
	}
				    	if($last_validity_year <= '2015'){
							
								//$fees_previous  		= fees_calculation_registration_power_station($previous_power,$amand_starting_year);
					  			//$fees_previous_paid 	= (($fees_previous['fees']*$amand_valid_time_period))+$previous_excess_paid;
								
								$cut_off_date_year  	= date('Y',strtotime($amand_starting_year));
						 		$cut_off_date 			= $cut_off_date_year.'-03-31';
								$result_data  			= fees_calculation_registration_power_station($present_power,$amand_starting_year);
								$license_fees 			= $license_fees_1 = $result_data['fees']*$amand_valid_time_period;
								$unit 		 			= 'KW';
					 			if($application_date<=$cut_off_date ){
									
									if($fees_previous_paid>$license_fees){
										$late_fees_pay 		= 0; 
										$balance_amount = $fees_previous_paid-$license_fees;
										$due_amount 	= 0;
									}
									if($fees_previous_paid<$license_fees){
										$due_amount = $license_fees - $fees_previous_paid;
										$late_fees_pay = ($due_amount)*(25/100);
										$balance_amount = 0;
										$due_amount = $due_amount+$late_fees;
									}else{
										$late_fees 		= 0; 
										$balance_amount = 0;
										$due_amount 	= 0;
									}
									
									
						 
					 			}
								if($application_date>$cut_off_date ){
									
									if($fees_previous_paid>$license_fees){
										$late_fees_pay 		= 0; 
										$balance_amount 	= $fees_previous_paid-$license_fees;
										$due_amount 		= 0;
									}
									if($fees_previous_paid<$license_fees){
										$due_amount 	= $license_fees - $fees_previous_paid;
										$late_fees_pay 	= ($due_amount)*(50/100);
										$balance_amount = 0;
										$due_amount = $due_amount+$late_fees_pay;
									}else{
										$late_fees_pay 		= 0; 
										$balance_amount = 0;
										$due_amount 	= 0;
									}
									
									
						 
					 			}
								$payblefess =$license_fees+$late_fees_pay; 
								$output.='<tr>
										<td>'.$sl.'</td>
		             					<td>'.$amand_year.'</td>
										<td>'.$amandment_fess.'</td>
										<td>'.$previous_power.'('.$previous_power_unit.')</td>
										<td>'.$previous_worker.'</td>	
										<td>'.$fees_previous_paid.'</td>
										<td>'.$present_power.'('.$present_installed_power_unit.')</td>
										<td>'.$present_totalworker.'</td>
										<td>'.$payblefess.'('.$license_fees.'+'.$late_fees_pay.')</td>
										<td>'.$balance_amount.'</td>
										<td>'.$due_amount.'</td>';
					
							$output.='</tr>';
							$sl++;	
							$_SESSION["balance_renewal"] = NULL;
								$_SESSION["renewal_amand_balance"]	=$balance_amount;
							
						}
				           		
						$amandment_fess=0;
						$previous_excess_paid1 = $balance_amount;
						$total_amand_fees = $total_amand_fees+$due_amount;
						}
		 				$i= $i+1;	   
				}	
				
				  
	   	
		///echo $_SESSION['renewal_amand_balance'];die;
   $total_calculation = $_SESSION['renewal_fees'] + $total_amand_fees;
   if($total_calculation>$_SESSION["renewal_amand_balance"]){
	     $total_fees_paid_to_end =$total_calculation-$_SESSION["renewal_amand_balance"];
		 $_SESSION["renewal_amand_balance"] = 0;
   }  if($total_calculation<$_SESSION["renewal_amand_balance"]){
	     $_SESSION["renewal_amand_balance"] = $_SESSION["renewal_amand_balance"]-$total_calculation;
		 $total_fees_paid_to_end = 0;
   }if($total_calculation==$_SESSION["renewal_amand_balance"]){
	     $_SESSION["renewal_amand_balance"] = 0;
		 $total_fees_paid_to_end = 0;
   }
 
   
   
  
    $_SESSION["renewal_fees"] = $total_fees_paid_to_end;
	$output .='</table>
	
				<strong><font color="#FF0000">Fees to be paid For Amandment:-'.($total_amand_fees).'</font></strong><br/>
				<strong><font color="#FF0000">Total Fees to be paid:-'.($total_fees_paid_to_end).'</font></strong>
				</div></div>'
				;
	
	return $output;
	}


function show_fees_registration_2mii($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid,$last_validlicensedate){
	$i= 1;
	$output = '
			      <div class="box-body">
						<table class="table table-bordered" width="100%">
							<tr>
				<th>SL</th>
  				<th>Application Period</th>
   				<th>Total Workers</th>
				<th>Schedule Fees(Rs)<br>(calculated fess * total application year)</th>
				<th>Late Fees(Rs)</th>
				<th>Previous Excess Paid(Rs.)</th>
				<th>Balance(Rs)</th>
				<th>Due Amount(Rs)</th>
  	 		</tr>';
 $license_fees 				= 	0;
 $Registration_fees 		=	0;
 $fees 						=	0;
 $worker_detials 			= 	worker_detials_for_fees2mii($application_id,$reference_no,$factory_type_id,$service_id);
 $get_fa_cafa 				= 	get_fa_cafa($application_id);
 $previous_amount_pre		= 	$get_fa_cafa['previous_excess_paid'];
 $balance_amount_preservice	= 	$get_fa_cafa['balance_amount'];
  $previous_amount_pre		= $balance_amount_preservice;
 $date 						= 	date_create($last_validlicensedate);
 $date_convert 				= 	date_format($date, "Y");
 $date_convert1 			= 	date_format($date, "Y-m-d");	
 
 if($date_convert1 == '2018-12-31'){
				 
		$max_payment_date 		= get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
	    $payment 				= 0;
				 
		if(!empty($max_payment_date)){
					  $manual_payment =  manual_payment_deatils($application_id,$service_id,$factory_typeid,$reference_number); 
					 $manual_payment_count =  count($manual_payment); 
					  foreach($worker_detials as $worker){
						   $result_data  = fees_calculation_registration_2mii($worker->start_year,$worker->total_worker);
						  $license_fees=$license_fees_1 = $result_data['fees']*$worker->vaild_period;
						  $license_start_date = $worker->starting_year;
						  if($previous_amount_pre>$license_fees_1){
							  $license_fees_1 = 0;
							  $balnce_amount = $previous_amount_pre-$license_fees_1;
							  $due_amount = 0;
							  $late_fees_pay = 0;
						  }if($previous_amount_pre<$license_fees_1){
							  $balnce_amount = 0;
							  $license_fees_1 = $license_fees_1-$previous_amount_pre;
							  $due_amount = 0;
						  }if($previous_amount_pre==$license_fees_1){
							  $balance_amount = 0;
							  $license_fees_1 = 0;
							  $due_amount = 0;
							  $late_fees_pay = 0;
						  }
						  if($license_fees_1 >0){
							   if($license_start_date=='2019-01-01'){
							    	 $datey_cuttoff 		= '2019-01-15'; 
						}else{
							 		
									 	$year  			= date('Y',strtotime($license_start_date));
									  	$month 			= date('m',strtotime($license_start_date));
									   	$day  			= date('d',strtotime($license_start_date));
							 			$from_unix_time = mktime(0, 0, 0, $month, $day, $year);
										$day_before 	= strtotime("yesterday", $from_unix_time);
										$datey_cuttoff 	= date('Y-m-d', $day_before);
									
								
						}
						
							  while(($payment < $manual_payment_count)&& ($flag_payment!= 'exhausted')){
							if($rows->calculate_starting_year > $manual_payment[$payment]->date_payment){
								 $previous_amount_pre = $previous_amount_pre+$manual_payment[$payment]->payment_amount;
							     if($license_fees_1 == $manual_payment[$payment]->payment_amount){
									 	$flag_payment = 'exhausted';
									  	$due_flag = 0;
								}if($license_fees_1 > $manual_payment[$payment]->payment_amount){
										 $due_amount_pre = ($license_fees_1-$manual_payment[$payment]->payment_amount);
									 	 $license_fees_1 = $due_amount_pre;
									 	$due_flag = 1;
								}if($license_fees < $manual_payment[$payment]->payment_amount){
									 $balance_amount = ($manual_payment[$payment]->payment_amount-$license_fees_1);
									 $due_flag = 0;
								}
							 }//echo $payment;
						if($rows->calculate_starting_year <=$manual_payment[$payment]->date_payment){
								 $previous_amount_pre = $previous_amount_pre+$manual_payment[$payment]->payment_amount;
							}
						 	$payment++;
						 
						
						
						}
															 
				 			if($application_date < $datey_cuttoff){
						 $late_fees_pay = 0;
						$due_amount 	= $license_fees+$late_fees_pay;
					}
							if($application_date >= $datey_cuttoff){
										
							if($rows->calculate_starting_year < $application_date){
										$start_date				= date_create($rows->calculate_starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
										$days_differ_app  		= $diff->days; 
							}if($rows->calculate_starting_year < $datey_cuttoff){
										$start_date				= date_create($rows->calculate_starting_year);
										$datey_cuttoff1			= date_create($datey_cuttoff);
										$diff					= date_diff($datey_cuttoff1,$start_date);
										$days_differ_cutt 		= $diff->days;
							}if($days_differ_app>$days_differ_cutt){
										$big_diff = $days_differ_app;
							}else{
									    $big_diff = $days_differ_cutt;
							}
							if($rows->calculate_starting_year > $application_date){
										$start_date		= date_create($rows->calculate_starting_year);
										$application_date1		= date_create($application_date);
										
										$diff			= date_diff($start_date,$application_date1);
										$big_diff  		= $diff->days;
										
							}
						}
						
							if($due_flag ==1){
								$license_fees_late = $due_amount_pre;
							}else{
								$license_fees_late = $license_fees;
							}
							
							if($big_diff>=1 && $big_diff<=90){
									$late_fees_pay = ($license_fees_late)*(50/100);
													
							}if($big_diff>91){
									$late_fees_pay = $license_fees_late;
							}
							
							$due_amount 	= $license_fees+$late_fees_pay;
							if($previous_amount_flag == 1){
							
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
						  }
						  else{
							  $previous_amount_pre = $balnce_amount;
						  }
						 				
						
									
				
				$output.='<tr>
						<td>'.$i.'</td>
		             	<td>'.$worker->application_period.'</td>
						<td>'.$worker->total_worker.'</td>
						<td>'.$license_fees.'  ('.$result_data['fees'].'*'.$rows->vaild_period.')</td>
						<td>'.$late_fees_pay.'</td>
						<td>'.$previous_amount_pre.'</td>
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';	
										
					
		$output.='</tr>';
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$late_fees 			=0;
		$late_fees_pay = 0;
		$due_flag =0;
					 
		$i++;		
		}
	
		} if(empty($max_payment_date)){
			if($license_start_date=='2019-01-01'){
					$datey_cuttoff 		= '2019-01-15'; 
			}else{
							 		
						$year  			= date('Y',strtotime($license_start_date));
						$month 			= date('m',strtotime($license_start_date));
						$day  			= date('d',strtotime($license_start_date));
						$from_unix_time = mktime(0, 0, 0, $month, $day, $year);
						$day_before 	= strtotime("yesterday", $from_unix_time);
						$datey_cuttoff 	= date('Y-m-d', $day_before);
									
								
				}					
				foreach($worker_detials as $worker){
					 $result_data  = fees_calculation_registration_2mii($worker->start_year,$worker->total_worker);
					 $license_fees=$license_fees_1 = $result_data['fees']*$worker->vaild_period;
					 if($previous_amount_pre>$license_fees_1){
							  $license_fees_1 = 0;
							  $balnce_amount = $previous_amount_pre-$license_fees_1;
							  $due_amount = 0;
							  $late_fees_pay = 0;
						  }if($previous_amount_pre<$license_fees_1){
							  $balnce_amount = 0;
							  $license_fees_1 = $license_fees_1-$previous_amount_pre;
							  $due_amount = 0;
						  }if($previous_amount_pre==$license_fees_1){
							  $balance_amount = 0;
							  $license_fees_1 = 0;
							  $due_amount = 0;
							  $late_fees_pay = 0;
						  }
						  
				 if($license_fees_1 >0){
						  
										if($worker->starting_year < $application_date){
											   		$start_date				= date_create($rows->calculate_starting_year);
													$application_date1		= date_create($application_date);
													$diff					= date_diff($application_date1,$start_date);
												    $days_differ_app  		= $diff->days; 
										}if($worker->starting_year < $datey_cuttoff){
													$start_date				= date_create($rows->calculate_starting_year);
													$datey_cuttoff1			= date_create($datey_cuttoff);
													$diff					= date_diff($datey_cuttoff1,$start_date);
												    $days_differ_cutt 		= $diff->days;
										}if($days_differ_app>$days_differ_cutt){
													$big_diff = $days_differ_app;
										}else{
													$big_diff = $days_differ_cutt;
										}
										if($rows->starting_year > $application_date){ 
													$start_date		= date_create($rows->calculate_starting_year);
													$application_date1		= date_create($application_date);
													$diff			= date_diff($start_date,$application_date);
												    $big_diff  		= $diff->days;
													
												
													
													
										}
										
										if($big_diff>=1 && $big_diff<=90){
											$late_fees = ($late_fees_up)*(50/100);
													
										}if($big_diff>91){
													$late_fees = $late_fees_up;
										}
											
										$payble_fees 	= $license_fees+$late_fees;
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
							}else{
							  $previous_amount_pre = $balnce_amount;
						  }
						 		
										
									
									
								$output.='<tr>
						<td>'.$i.'</td>
		             	<td>'.$rows->calculate_year.'</td>
						<td>'.$power_hp_kw.'('.$unit.')</td>
						<td>'.$rows->worker_total.'</td>
						<td>'.$license_fees.'  ('.$result_data['fees'].'*'.$rows->valid_time_period.')</td>
						<td>'.$late_fees_pay.'</td>
						<td>'.$previous_amount_pre.'</td>
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';	
										
					
		$output.='</tr>';
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$late_fees 			=0;
		$late_fees_pay = 0;
		
	}
 		}
							
 }
 if($date_convert1>2018){
		$previous_amount_pre= $previous_excess_paid;
		
		foreach($worker_detials as $worker){
			$schedule_fees 			= fees_calculation_registration_2mii($worker->start_year,$worker->total_worker);
			$license_fees 			= $schedule_fees['fees']*$worker->vaild_period;
			$datex 					= new DateTime($worker->starting_year);
			$datey 					= new DateTime('2015-12-31');
			if($worker->starting_year < $application_date){ 
				$diff 		= date_diff($start_date,$application_date1);
				$big_diff   = $diff->days;
		
			}
					
	if($big_diff>=1 && $big_diff<=90){
			$late_fees = ($schedule_fees['fees']*$fees_late_year)*(50/100);
													
	}if($big_diff>91){
			$late_fees = $schedule_fees['fees']*$fees_late_year;
	}else{
		$late_fees = 0;
	}
	
	$payble_fees 		= ($license_fees+$late_fees_pay+$amandment_fess);
	if($previous_amount_pre>$payble_fees){
						
							$balance_amount  	= $previous_amount_pre-$payble_fees;
							$due_amount 		= 0;
						
					}
					if($previous_amount_pre<$payble_fees){
								$due_amount  		= $payble_fees-$previous_amount_pre;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
						
							
					}
					if($previous_amount_pre == $payble_fees){
								$due_amount  		= 0;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								
							
					}	

	
		
	$output .='<tr>
				<td>'.$i.'</td>
				<td>'.$worker->application_period.'</td>
				<td>'.$worker->total_worker.'</td>
				<td>'.$license_fees.'('.$schedule_fees['fees'].'*'.$worker->vaild_period.')</td>
				<td>'.$late_fees.'</td>
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
		$total_fees = $due_amount;
	}
	
	}
 if($date_convert <= '2015'){ 
				$max_payment_date = get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
				if(empty($max_payment_date)){
					$application_date 		= date('Y-m-d');
					foreach($power_details as $rows){
							
							$start_date 		= $worker->starting_year;
							$cut_off_date_year  = date('Y',strtotime($start_date));
						 	$cut_off_date 		= $cut_off_date_year.'-03-31';
							$result_data 		= fees_calculation_registration_2mii($worker->start_year,$worker->total_worker);
							$license_fees 		= $license_fees= $result_data['fees']*$rows->valid_time_period;
							 if($balance_amount_preservice>$license_fees){
							  $license_fees = 0;
							  $balnce_amount = $balance_amount_preservice-$license_fees_1;
							  $due_amount = 0;
							  $late_fees_pay = 0;
						  }if($balance_amount_preservice<$license_fees){
							  $balnce_amount = 0;
							  $license_fees = $license_fees-$balance_amount_preservice;
							  $due_amount = 0;
						  }if($balance_amount_preservice==$license_fees){
							  $balance_amount = 0;
							  $license_fees = 0;
							  $due_amount = 0;
							  $late_fees_pay = 0;
						  }  if($license_fees >0){
					 		if($application_date<=$cut_off_date ){
								$late_fees = ($license_fees)*(25/100);
						 
					 		}if($application_date>$cut_off_date ){
								$late_fees = ($license_fees)*(50/100);
						 
					 		}
							$late_fees_pay 	= $late_fees;
							$due_amount 	= $license_fees+$late_fees_pay;
							$balance_amount = 0;
						  }else{
							   $balance_amount_preservice = $balnce_amount;
						  }
						$output.='<tr>
						<td>'.$i.'</td>
		             	<td>'.$rows->calculate_year.'</td>
						<td>'.$power_hp_kw.'('.$unit.')</td>
						<td>'.$rows->worker_total.'</td>
						<td>'.$license_fees.'  ('.$result_data['fees'].'*'.$rows->valid_time_period.')</td>
						<td>'.$late_fees_pay.'</td>
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
		
	  	
	 
	   	$i= $i+1;
					}
					
				}
				if(!empty($max_payment_date)){
					$application_date 		= date('Y-m-d');
					$manual_payment			=  manual_payment_deatils($application_id,$service_id,$factory_typeid,$reference_number);
				
					 $manual_payment_count 	=  count($manual_payment);
					
					foreach($power_details as $rows){
							$previous_amount_pre = 0;
							$application_date 	= date('Y-m-d');
							$start_date 		= $$worker->starting_year;
							$cut_off_date_year  = date('Y',strtotime($start_date));
						 	$cut_off_date 		= $cut_off_date_year.'-03-31';
							$result_data 		= fees_calculation_registration_2mii($worker->start_year,$worker->total_worker);
							$license_fees 		= $result_data['fees']*$worker->vaild_period;
							$due_license_amount = $license_fees; 
							 if($balance_amount_preservice>$due_license_amount){
							  $due_license_amount = 0;
							  $balnce_amount = $balance_amount_preservice-$due_license_amount;
							  $due_amount = 0;
							  $late_fees_pay = 0;
						  }if($balance_amount_preservice<$due_license_amount){
							  $balnce_amount = 0;
							  $due_license_amount = $due_license_amount-$balance_amount_preservice;
							  $due_amount = 0;
						  }if($balance_amount_preservice==$due_license_amount){
							  $balance_amount = 0;
							  $due_license_amount = 0;
							  $due_amount = 0;
							  $late_fees_pay = 0;
						  }if($due_license_amount>0){
							  while($payment < $manual_payment_count) {
								lebel1: if(($start_date>$manual_payment[$payment]->date_payment)&& !empty($manual_payment[$payment]->date_payment)){echo 'run lebel1';	
											if(!empty($last_payment_date)){
												if($start_date>$last_payment_date){
													if($due_license_amount>$balance_license_amount){
																$previous_amount_pre = $balance_license_amount;
																$due_license_amount 	= $due_license_amount-$balance_license_amount;
																$balance_license_amount = 0;
																$last_payment_date 		= NULL;
													}
													if($due_license_amount<$balance_license_amount){
																$due_license_amount 	= 0;
																$balance_license_amount = $balance_license_amount-$due_license_amount;
																$previous_amount_pre = $balance_license_amount;
													}if($due_license_amount==$balance_license_amount){
																$due_license_amount 	= 0;
																$balance_license_amount = 0;
																$last_payment_date 		= NULL;
																$previous_amount_pre = $balance_license_amount;
													}
										}if($start_date<$last_payment_date){
												$previous_amount_pre = $balance_license_amount;
										}
									}
								
								if($due_license_amount>$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 	= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$due_license_amount 	= $due_license_amount - $manual_payment[$payment]->payment_amount;
											$payment				= $payment+1 ;
											$flag_payment 			= 'due';
									 		goto lebel1;
								}
								if($due_license_amount<$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$balance_license_amount 	=  $manual_payment[$payment]->payment_amount-$due_license_amount ;
											$last_payment_date  		= $manual_payment[$payment]->date_payment ;
											$payment					= $payment+1 ;
											$flag_payment  				= 'exhausted';
											$due_amount 				= 	0;
											$late_fees_pay 	 			=	0;
											$late_flag 					=	1;
											$balance_amount 			= 	$balance_license_amount;
											$manual_payment_date 		=  NULL;
											break;
								}
								if($due_license_amount==$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$balance_license_amount 	= 0;
											$last_payment_date  		= NULL;
											$payment					= $payment+1 ;
											$flag_payment  				= 'exhausted';
											$due_amount 				= 0;
											$late_fees_pay 	 			= 0;
											$late_flag 					= 1;
											$balance_amount 			= $balance_license_amount;
											$manual_payment_date 		=  NULL;
											break;
								}
								if($due_license_amount !=0 ||empty($due_license_amount) ){
									if($application_date<=$cut_off_date ){
							 				$late_fees_pay 		= ($due_license_amount)*(25/100);
									 		$due_amount 		= $late_fees_pay+$license_fees;
											$balance_amount 	= $balance_license_amount;
											$late_flag 			=1;
						 			}if($application_date>$cut_off_date ){
										 	$late_fees_pay 		= ($due_license_amount)*(50/100);
										 	$due_amount 		= $late_fees_pay+$license_fees;
											$balance_amount 	= $balance_license_amount;
											$late_flag 			=1;
											
					 				}
								}
								
							}
							    lebel2: if($start_date<$manual_payment[$payment]->date_payment){						
									if(!empty($last_payment_date)){
										if($start_date>$last_payment_date){
										if($due_license_amount>$balance_license_amount){
											$previous_amount_pre 	= $balance_license_amount;
											$due_license_amount 	= $due_license_amount-$balance_license_amount;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
										}
										if($due_license_amount<$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = $balance_license_amount-$due_license_amount;
											$previous_amount_pre = $balance_license_amount;
										}if($due_license_amount==$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
											$previous_amount_pre = $balance_license_amount;
										}
									}
										if($start_date<$last_payment_date){
										if($balance_license_amount != 0){
											$previous_amount_pre = $balance_license_amount;
											$flag_balance = 1;
										}
											
											
											
										}
									}
									
									if($late_flag == 0 || empty($late_flag)){
										if($manual_payment[$payment]->date_payment<=$cut_off_date ){
							 			$late_fees_pay 	= ($due_license_amount)*(25/100);
									 	$due_amount 	= $late_fees_pay+$due_license_amount;
										$balance_amount = $balance_license_amount;
										$late_flag = 1;
						 			}if($manual_payment[$payment]->date_payment>$cut_off_date ){
										  $late_fees_pay 	= ($due_license_amount)*(50/100);
										  $due_amount 			= $late_fees_pay+$due_license_amount;
										  $balance_amount 		= $balance_license_amount;
										 $late_flag 			= 1;
										
											
					 				}
								}
									
									
									if($due_amount>$manual_payment[$payment]->payment_amount){
										
										if($flag_balance == 1){
												 $previous_amount_pre 	=  $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												
											  	 $due_amount 			=  $due_amount-$previous_amount_pre ;
												$flag_balance = 0;
												
											}else{
												 $previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												 $due_amount 	= $due_amount - $manual_payment[$payment]->payment_amount;
												
											}
											
									
										
										$late_flag =1;
										$balance_license_amount = 0;
										$payment	= $payment+1 ;
										$flag_balance =0;
									 	goto lebel2;
									}
									if($due_amount<$manual_payment[$payment]->payment_amount){
										 
											
											if($flag_balance == 1){
												$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												 $balance_license_amount 	=  $previous_amount_pre-$due_amount ;
											}else{
												$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												 $balance_license_amount 	=  $manual_payment[$payment]->payment_amount-$due_amount ;
											}
											
											
										 	$last_payment_date  		= $manual_payment[$payment]->date_payment ;
											$due_amount 				= 0;
											$flag_payment  				= 'exhausted';
											$late_flag 					= 1;
											$payment					= $payment+1 ;
											$flag_balance = 0;
											break;
									}
									if($due_amount==$manual_payment[$payment]->payment_amount){
										$previous_amount_pre 	    = $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										$balance_license_amount 	=  0;
										$last_payment_date          = NULL;
										$flag_payment  				= 'exhausted';
										$late_flag 					=1;
										break;
									}
								}
								lebel3: if($start_date==$manual_payment[$payment]->date_payment){
									
									if(!empty($last_payment_date)){
										if($start_date>$last_payment_date){
										if($due_license_amount>$balance_license_amount){
											$previous_amount_pre 	= $balance_license_amount;
											$due_license_amount 	= $due_license_amount-$balance_license_amount;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
										}if($due_license_amount<$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = $balance_license_amount-$due_license_amount;
											$previous_amount_pre 	= $balance_license_amount;
										}if($due_license_amount==$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
											$previous_amount_pre 	= $balance_license_amount;
										}

									}
										if($start_date<$last_payment_date){
											$previous_amount_pre = $balance_license_amount;
										}
									}
									
								
									if($application_date<=$cut_off_date ){
							 			$late_fees_pay 	= ($due_license_amount)*(25/100);
									 	$due_amount 		= $late_fees_pay+$due_license_amount;
										$balance_amount = $balance_license_amount;
										$late_flag = 1;
						 			}if($application_date>$cut_off_date ){
										 $late_fees_pay = ($due_license_amount)*(50/100);
									
										 $due_amount 	= $late_fees_pay+$due_license_amount;
										$balance_amount = $balance_license_amount;
										$late_flag = 1;
											
					 				}
									
									if($due_amount>$manual_payment[$payment]->payment_amount){
										 	$previous_amount_pre 	= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										 	$due_amount 			= $due_amount - $previous_amount_pre;
											$late_flag 				= 1;
											$payment				= $payment+1 ;
									 		goto lebel3;
									}
									if($due_amount<$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$balance_license_amount 	=  $manual_payment[$payment]->payment_amount-$due_amount ;

											$last_payment_date  		= $manual_payment[$payment]->date_payment ;
											$flag_payment  				= 'exhausted';
											$late_flag 					=1;
											break;
									}
									if($due_amount==$manual_payment[$payment]->payment_amount){
										$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										$balance_license_amount 	=  0;
										$last_payment_date 	 		= NULL ;
										$payment					= $payment+1 ;
										$flag_payment  		= 'exhausted';
										$late_flag =1;
										break;
									}
								}
								
							} 
					
							if($late_flag ==0  ){
								if($application_date<=$cut_off_date ){
							 		$late_fees_pay 	= ($due_license_amount)*(25/100);
									$due_amount 	= $late_fees_pay+$due_license_amount;
									$balance_amount = $balance_license_amount;
						 		}if($application_date>$cut_off_date ){
									$late_fees_pay 	= ($due_license_amount)*(50/100);
									$due_amount 	= $late_fees_pay+$due_license_amount;
									$balance_amount = $balance_license_amount;
											
					 			}
								if($balance_license_amount>$due_amount){
									$previous_amount_pre 	= $balance_license_amount;
									 $balance_amount 		= $previous_amount_pre-$due_amount;
									$due_amount 			= 0;
									 $balance_license_amount = $balance_amount;
								}if($balance_license_amount<$due_amount){
									$previous_amount_pre 	= $balance_license_amount;
									$due_amount 			= $due_amount-$balance_license_amount;
									$balance_amount 		= 0;
									$balance_license_amount = $balance_amount;
								}if($balance_license_amount==$due_amount){
									$previous_amount_pre 	= 0;
									$due_amount 			= 0;
									$balance_amount 		= 0;
									$balance_license_amount = $balance_amount;
								}
							
							}
							
							
							 
						 $balance_amount = $balance_license_amount;
						
							$due_amount_paid = $due_amount+$due_amount_paid;
						  }else{
							   $balance_amount_preservice = $balnce_amount;
						  }
							
						$output.='<tr>
									<td>'.$i.'</td>
		             				<td>'.$rows->calculate_year.'</td>
									<td>'.$power_hp_kw.'('.$unit.')</td>
									<td>'.$rows->worker_total.'</td>
									<td>'.$license_fees.'  ('.$result_data['fees'].'*'.$rows->valid_time_period.')</td>
									<td>'.$late_fees_pay.'</td>
								
									<td>'.$previous_amount_pre.'</td>
									<td>'.$balance_amount.'</td>
									<td>'.$due_amount.'</td>';	
						$output.='</tr>';	
						$late_fees_pay 			= 	0;
						$previous_amount_pre 	=	0;
						$due_amount 			= 	0;
						$late_flag 				=	0;
						$flag_payment 			=	'';
						$balance_amount =0;	
						$fees_to_paid = $due_amount_paid;
						$i++;
					}
				}
				
		}
						
 

	
	$_SESSION['renewal_fees']=$total_fees;
	$_SESSION['balance_renewal']=$balance_amount;
	$output .=' </table>
		<strong><font color="#FF0000">Fees to be paid (Total Due amount +  Registration fees + Total transfer fees) :-  '.$total_fees.'</font></strong>
				</div>';
				
				
	return $output;
	
}

function show_fees_registration_amand_2mii($application_id,$service_id,$factory_type_id,$reference_no,$last_validlicensedate){
	$previous_excess_paid =  $_SESSION['balance_renewal'];
	$amandment_fess = 1000;
	$sl = 1;
	$Registration_fees 					= 	0;
	$created_by 						=   $user->uid;
	$modifi_date 						=   date("Y-m-d",strtotime($date_of_amenability));
	
	$i									=	1;
	$license_fees 						= 	0;
	$late_fees							= 	0;
	$current_year 						= 	date("Y");
	$fees 								= 	0;
	$i									= 	1;  
	$total_license_fees  				= 	0;
	$total_transfer_fees 				= 	0;
	$flag_adjust_balance 				= 	0;
	$flag_late_calulate  				= 	0;
	
	$flag_payment  						= '';
	$payment							= 0;
	$late_flag = 0;
	$flag_balance = 0;
	$fees_to_paid =0;
	$due_flag = 0;
	$previous_amount_flag =0;
	$total_amand_fees =0;
	$output = '	<div class="box-body">
					<table class="table table-bordered" width="100%">
					<th>SL</th>
  					<th>Application Period</th>
					<th>Amandment Fees</th>
					<th>Previous Total Workers</th>
					<th>Previous Fees</th>
					<th>Total Workers</th>
					<th>Schedule Fees+Late Fess(Rs)<br></th>
					<th>Balance(Rs)</th>
					<th>Due Amount(Rs)</th>
  	 		</tr>';
			
			$amend_value = fun_worker_detials_amendnotice($application_id,$service_id,$factory_typeid,$reference_number);
			foreach($amend_value as $amand_row){
					
					$Previous_Total_Worke 	= $amand_row->previous_worker;
					$Amendment_Worker		= $amand_row->worker_total;
					$amand_valid_year 		= $amand_row->valid_year;
					$valid_time_period		= $amand_row->valid_time_period;	
					$starting_year			= $amand_row->starting_year;
					$service_year			= $amand_row->service_year;	
					$last_validity			= date("Y-m-d",strtotime($amand_valid_year));
					$last_validity_year  	= date('Y',strtotime($amand_valid_year));
					$fees_previous 			= fees_calculation_registration_2mii($starting_year,$Previous_Total_Worke);
					$fees_previous_paid 	= ($fees_previous['fees']*$valid_time_period)+$previous_excess_paid;
					if($last_validity == '2018-12-31'){
				  			$application_date 		= date('Y-m-d');
							if(!empty($fees_previous_paid)){
							   $result_data  = fees_calculation_registration_2mii($starting_year,$Amendment_Worker);
						       $license_fees=$license_fees_1 = $result_data['fees']*$amand_valid_time_period;
						       $license_start_date = $starting_year;
						  if($license_start_date=='2019-01-01'){
							    	 $datey_cuttoff 		= '2019-01-15'; 
						}else{
							 		
									 	$year  			= date('Y',strtotime($license_start_date));
									  	$month 			= date('m',strtotime($license_start_date));
									   	$day  			= date('d',strtotime($license_start_date));
							 			$from_unix_time = mktime(0, 0, 0, $month, $day, $year);
										$day_before 	= strtotime("yesterday", $from_unix_time);
										$datey_cuttoff 	= date('Y-m-d', $day_before);
									
								
						}
						
							
				 
				  if($application_date < $datey_cuttoff){
						 $late_fees_pay = 0;
						 if($license_fees>$fees_previous_paid){
							  $due_amount 	=(($license_fees-$fees_previous_paid));
						 } else{
							 $due_amount 	=(($fees_previous_paid-$license_fees));
						 }
						
					}
					
				  if($application_date >= $datey_cuttoff){
										
				 if($amand_starting_year < $application_date){
										$start_date				= date_create($amand_starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
										$days_differ_app  		= $diff->days; 
							}if($amand_starting_year < $datey_cuttoff){
										$start_date				= date_create($amand_starting_year);
										$datey_cuttoff1			= date_create($datey_cuttoff);
										$diff					= date_diff($datey_cuttoff1,$start_date);
										$days_differ_cutt 		= $diff->days;
							}if($days_differ_app>$days_differ_cutt){
										$big_diff = $days_differ_app;
							}else{
									    $big_diff = $days_differ_cutt;
							}
							if($amand_starting_year > $application_date){
										$start_date		= date_create($amand_starting_year);
										$application_date1		= date_create($application_date);
										
										$diff			= date_diff($start_date,$application_date1);
										$big_diff  		= $diff->days;
										
								
								}
										
								if($big_diff>=1 && $big_diff<=90){
									 $late_fees_pay = ($result_data['fees'])*(50/100);
													
							}if($big_diff>91){
									 $late_fees_pay = $result_data['fees'];
							}
							//echo $late_fees_pay;
							$payble_fees = $license_fees+$late_fees_pay;
							 if($fees_previous_paid>$payble_fees){
							//$late_fees_pay 		= $;
							$balance_amount  	= $fees_previous_paid-$payble_fees;
							$due_amount 		= 0;
						
					}
					if($fees_previous_paid<$payble_fees){
								$due_amount  		= $payble_fees-$fees_previous_paid;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
							//	$late_fees_pay 		= $late_fees_pay;
							
					}
					if($fees_previous_paid == $payble_fees){
								$due_amount  		= 0;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								//$late_fees_pay 		= 0;
							
					}			
									
										
							}
						
							
									
				}
					
				$output.='<tr>
						<td>'.$sl.'</td>
		             	<td>'.$amand_year.'</td>
						<td>'.$amandment_fess.'</td>
						
						<td>'.$previous_worker.'</td>	
						<td>'.$fees_previous_paid.'</td>
						
						<td>'.$due_amount.'</td>
						
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';
					
		$output.='</tr>';
		$sl++;		
		$fees_previous_paid 	= $balance_amount;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;			
					 
				
				 
		 }
				 					
					if($last_validity_year > '2018'){
				           		
							 $result_data  = fees_calculation_registration_2mii($starting_year,$Amendment_Worker);
							 //print_r($result_data);die();
						   $license_fees=$license_fees_1 = $result_data['fees']*$valid_time_period;
					  	    $license_start_date 	= $starting_year;
							$application_date1		= date_create($application_date);
							$late_fees 				= 0;
							
							if($amand_starting_year < $application_date){ //echo 'hi';
									$start_date		= date_create($amand_starting_year);
									$diff			= date_diff($start_date,$application_date1);
									$big_diff  		= $diff->days;
									 $late_year = $diff->y;
									 $late_month = $diff->m;
									 $late_day = $diff->d ;
									if($late_year>0){
										$fees_late_year = $late_year;
									if($late_month>0){
										$fees_late_year = $late_year+1;
									}if($late_month<0 && $late_day >0){
										$fees_late_year = $late_year+1;
									}
									$late_fees = $result_data['fees']*$fees_late_year;
									}if($late_year==0){
										$fees_late_year = 0;
									if($late_month>0){
										 $fees_late_year = 1;
									}if($late_month==0 && $late_day >0){
										$fees_late_year = 1;
									}
									$late_fees = $result_data['fees']*$fees_late_year;
									}
										
							}else{
								$late_fees = 0;
							}
							
					
				//echo $late_fees_pay;die();
					$payble_fees = $license_fees+$late_fees_pay+$amandment_fess;
					if($fees_previous_paid>$payble_fees){
							//$late_fees_pay 		= $;
							$balance_amount  	= $fees_previous_paid-$payble_fees;
							$due_amount 		= 0;
						
					}
					if($fees_previous_paid<$payble_fees){
								$due_amount  		= $payble_fees-$fees_previous_paid;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
							//	$late_fees_pay 		= $late_fees_pay;
							
					}
					if($fees_previous_paid == $payble_fees){
								$due_amount  		= 0;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								//$late_fees_pay 		= 0;
							
					}			
						
					
					//echo $payble_fees;die();
			
				$output.='<tr>
						<td>'.$sl.'</td>
		             	<td>'.$service_year.'</td>
						<td>'.$amandment_fess.'</td>
						<td>'.$Previous_Total_Worke.'</td>	
						<td>'.$fees_previous_paid.'</td>
						<td>'.$Amendment_Worker.'</td>	
						<td>'.$payble_fees.'</td>
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';
					
		$output.='</tr>';
		$sl++;
		$previous_excess_paid = $balance_amount;		
			
	}
					if($last_validity_year <= '2015'){
						
							 $result_data  = fees_calculation_registration_2mii($starting_year,$Amendment_Worker);
						   $license_fees=$license_fees_1 = $result_data['fees']*$valid_time_period;
					  	    $license_start_date 	= $starting_year;
							$application_date1		= date_create($application_date);
							$late_fees 				= 0;
							if($amand_starting_year < $application_date){ //echo 'hi';
									$start_date		= date_create($amand_starting_year);
									$application_date1		= date_create($application_date);
										
										$diff			= date_diff($start_date,$application_date1);
										$big_diff  		= $diff->days;
										
										
							}
							
							if($fees_previous_paid>$license_fees){
								$late_fees_pay = 0;
								$balance_amount = $fees_previous_paid-$payblefess;
								$due_amoun = 0;
							}
							if($fees_previous_paid<$license_fees){
								$late_fees = $fees_previous_paid-$license_fees;
								
								if($big_diff>=1 && $big_diff<=90){
									$late_fees_pay = ($late_fees)*(25/100);
								$due_amoun = $late_fees+$late_fees_pay;
								$balance_amount=0;					
							}if($big_diff>91){
								
									$late_fees_pay = ($late_fees)*(50/100);
								$due_amoun = $late_fees+$late_fees_pay;
								$balance_amount=0;
									
							}
								
								
							}if($fees_previous_paid==$license_fees){
								
								if($big_diff>=1 && $big_diff<=90){
									$late_fees = ($result_data['fees']*$fees_late_year)*(25/100);
													
							}if($big_diff>91){
									$late_fees = ($result_data['fees']*$fees_late_year)*(50/100);
							}
								
								
								$late_pay = 0;
								$balance_amount = 0;
								$due_amoun = $license_fees-$fees_previous_paid;
							}
							
					
							
					
				
							
			
				$output.='<tr>
						<td>'.$sl.'</td>
		             	<td>'.$amand_year.'</td>
						<td>'.$amandment_fess.'</td>
						<td>'.$previous_power.'('.$previous_power_unit.')</td>
						<td>'.$previous_worker.'</td>	
						<td>'.$fees_previous_paid.'</td>
						<td>'.$present_power.'('.$present_installed_power_unit.')</td>
						<td>'.$present_totalworker.'</td>
						<td>'.$payblefess.'</td>
						
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';
					
		$output.='</tr>';
		$sl++;		
				}
				           		
				$amandment_fess=0;
				$total_amand_fees = $total_amand_fees+$due_amount;		
			
			
			 
			   
	}	
				
				  
	   	$i= $i+1;
		
   
   $total_fees_paid_to_end =$_SESSION['renewal_fees'] + $total_amand_fees;
   $_SESSION['renewal_fees'] = $total_fees_paid_to_end;
	$output .='</table></div>
	
				<strong><font color="#FF0000">Fees to be paid For Amandment:-'.($total_amand_fees).'</font></strong><br/>
				<strong><font color="#FF0000">Total Fees to be paid:-'.($total_fees_paid_to_end).'</font></strong>
				</div></div>'
				;
	
	return $output;}
	
	


function show_fees_registration_section_85($application_id,$service_id,$factory_type_id,$reference_no,$last_validlicensedate){
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
$power_details			= yearly_power_worker_details($application_id,$factory_type_id,$service_id,$reference_no);


$total_transfer_fees 	= 0;
$date 					= date_create($last_validlicensedate);
$date_convert 			= date_format($date, "Y");
$date_convert1 			= date_format($date, "Y-m-d");	
$application_date 		= date('Y-m-d');	
$application_date1 		= date_create($application_date);			

$output = '<div class="box-body">
						<table class="table table-bordered" width="100%">
		
				<th>SL</th>
  				<th>Application Period</th>
   				<th>Category(KW/HP)</th>
   				<th>Total Workers</th>
				
    			<th>Schedule Fees(Rs)<br>(calculated fess * total application year)</th>
				<th>Late Fees(Rs)</th>
				
  				<th>Previous Excess Paid(Rs.)</th>
				<th>Balance(Rs)</th>
				<th>Due Amount(Rs)</th>
				
  	 		</tr>';
foreach($power_details as $rows){
	$installed_power 	=   $rows->installed_power;
	$worker_total 		=   $rows->worker_total;
	
	
}
	
$remark				=  'Section-85'	;

	$previous_amount_pre = 0;
	$manual_payment_amount = 0;
	if($date_convert1 == '2018-12-31'){
	$max_payment_date 		= get_max_payment_date($application_id,$service_id,$factory_type_id,$reference_no);
	$max_payment_date		=	get_max_payment_date($application_id,$service_id,$factory_type_id,$reference_no);
	foreach($power_details as $rows){
	if(empty($max_payment_date)){
					 $license_start_date = $rows->calculate_starting_year;	
					if($license_start_date=='2019-01-01'){
						$datey_cuttoff 		= '2019-01-15'; 
						}
					else{
							 		
					
					$license_start_date  	= date_create($license_start_date);
					$year 					= date_format($license_start_date, "Y");
					$month 					= date_format($license_start_date, "m");
					$day 					= date_format($license_start_date, "d");
					$from_unix_time 		= mktime(0, 0, 0, $month, $day, $year);
					$day_before 			= strtotime("yesterday", $from_unix_time);
					 $datey_cuttoff 			= date('Y-m-d', $day_before);
									
								
					}
				   $fees_fetach 		=	fees_calculation_registration_section_85($rows->calculate_starting_year);
				   $license_fees 		=  $fees_fetach['fees']*$rows->valid_time_period;
				    $unit 		 		= $rows->power_unit;
					$power_hp_kw  		= $rows->installed_power_hp;
				 	$installed_power  	= $rows->installed_power;
				   if($rows->calculate_starting_year <= $application_date){
					   	$start_date				= date_create($rows->calculate_starting_year);
						$diff					= date_diff($application_date1,$start_date);
						$days_differ_app  		= $diff->days; 
						
				   } if($rows->calculate_starting_year <=$datey_cuttoff){
						   $start_date				= date_create($rows->calculate_starting_year);
						   $datey_cuttoff1			= date_create($datey_cuttoff);
						   $diff					= date_diff($datey_cuttoff1,$start_date);
						   $days_differ_cutt 		= $diff->days;
				}if($days_differ_app>$days_differ_cutt){
							$big_diff = $days_differ_app;
				}else{
							$big_diff = $days_differ_cutt;
				}
				if($rows->calculate_starting_year > $application_date){ 
							$big_diff = 0;
				}
				
				if($big_diff>=1 && $big_diff<=90){
							$late_fees = ($license_fees)*(50/100);
													
				}if($big_diff>91){
							$late_fees = $license_fees;
				}else{
					$late_fees = 0;
				}
				$payble_fees 	= $license_fees+$late_fees;
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
													
					$output.='<tr>
						<td>'.$i.'</td>
		             	<td>'.$rows->calculate_year.'</td>
						<td>'.$installed_power.'('.$unit.')</td>
						<td>'.$rows->worker_total.'</td>
						<td>'.$license_fees.'  ('.$fees_fetach['fees'].'*'.$rows->valid_time_period.')</td>
						<td>'.$late_fees_pay.'</td>
						<td>'.$previous_amount_pre.'</td>
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';	
										
					
		$output.='</tr>';
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$late_fees 			=0;
		$late_fees_pay = 0;	
		$days_differ_cutt = 0;
			}
	}
	if(!empty($max_payment_date)){
		$manual_payment				=  manual_payment_deatils($application_id,$service_id,$factory_type_id,$reference_no);
		$manual_payment_count 		=  count($manual_payment); 
		$payment			  		= 0;
		foreach($power_details as $rows){
				 $fees_fetach 		=	fees_calculation_registration_section_85($rows->calculate_starting_year);
				$license_fees=$license_fees_1 = $fees_fetach['fees']*$rows->valid_time_period;
				$unit 		 		= $rows->power_unit;
				$power_hp_kw  		= $rows->installed_power_hp;
				$installed_power  	= $rows->installed_power;
				if($previous_amount_pre>$license_fees_1){
					  $license_fees_1 = 0;
					  $balnce_amount = $previous_amount_pre-$license_fees_1;
					  $due_amount = 0;
					  $late_fees_pay = 0;
				}if($previous_amount_pre<$license_fees_1){
					  $balnce_amount = 0;
					  $license_fees_1 = $license_fees_1-$previous_amount_pre;
					  $due_amount = 0;
				}if($previous_amount_pre==$license_fees_1){
					  $balance_amount = 0;
					  $license_fees_1 = 0;
					  $due_amount = 0;
					  $late_fees_pay = 0;
				}if($license_fees_1>0){ 
					   $license_start_date = $rows->calculate_starting_year;
				
					if($license_start_date=='2019-01-01'){
						$datey_cuttoff 		= '2019-01-15'; 
						}
					else{
							 		
					
					$license_start_date  	= date_create($license_start_date);
					$year 					= date_format($license_start_date, "Y");
					$month 					= date_format($license_start_date, "m");
					$day 					= date_format($license_start_date, "d");
					$from_unix_time 		= mktime(0, 0, 0, $month, $day, $year);
					$day_before 			= strtotime("yesterday", $from_unix_time);
					 $datey_cuttoff 			= date('Y-m-d', $day_before);
									
								
					}
						
						while(($payment < $manual_payment_count)&& ($flag_payment!= 'exhausted')){
							if($rows->calculate_starting_year > $manual_payment[$payment]->date_payment){
								 $previous_amount_pre = $previous_amount_pre+$manual_payment[$payment]->payment_amount;
							     if($license_fees_1 == $manual_payment[$payment]->payment_amount){
									 	$flag_payment = 'exhausted';
									  	$due_flag = 0;
								}if($license_fees_1 > $manual_payment[$payment]->payment_amount){
										 $due_amount_pre = ($license_fees_1-$manual_payment[$payment]->payment_amount);
									 	 $license_fees_1 = $due_amount_pre;
									 	$due_flag = 1;
								}if($license_fees < $manual_payment[$payment]->payment_amount){
									 $balance_amount = ($manual_payment[$payment]->payment_amount-$license_fees_1);
									 $due_flag = 0;
								}
							 }
						if($rows->calculate_starting_year <=$manual_payment[$payment]->date_payment){
								 $previous_amount_pre = $previous_amount_pre+$manual_payment[$payment]->payment_amount;
							}
						 	$payment++;
						 
						
						
						}
			 
				 if($application_date < $datey_cuttoff){
						 $late_fees_pay = 0;
						$due_amount 	= $license_fees+$late_fees_pay;
					}if($application_date >= $datey_cuttoff){ 
										
							if($rows->calculate_starting_year < $application_date){
										$start_date				= date_create($rows->calculate_starting_year);
										$diff					= date_diff($application_date1,$start_date);
										$days_differ_app  		= $diff->days; 
							}if($rows->calculate_starting_year < $datey_cuttoff){
										$start_date				= date_create($rows->calculate_starting_year);
										$datey_cuttoff1			= date_create($datey_cuttoff);
										$diff					= date_diff($datey_cuttoff1,$start_date);
										$days_differ_cutt 		= $diff->days;
							}if($days_differ_app>$days_differ_cutt){
										$big_diff = $days_differ_app;
							}else{
									    $big_diff = $days_differ_cutt;
							}
							if($rows->calculate_starting_year > $application_date){
										$start_date		= date_create($rows->calculate_starting_year);
										$application_date1		= date_create($application_date);
										
										$diff			= date_diff($start_date,$application_date1);
										$big_diff  		= $diff->days;
							}
						
							if($due_flag ==1){
								$license_fees_late = $due_amount_pre;
							}else{
								$license_fees_late = $license_fees;
							}
							
							if($big_diff>=1 && $big_diff<=90){
									$late_fees_pay = ($license_fees_late)*(50/100);
													
							}if($big_diff>91){
									$late_fees_pay = $license_fees_late;
							}
							
							$due_amount 	= $license_fees+$late_fees_pay;
							
							
						
							
							if($previous_amount_pre>$due_amount){
									
									$balance_amount  	= $previous_amount_pre-$due_amount;
									$due_amount 		= 0;
							}
							if($previous_amount_pre<$due_amount){
									$due_amount  		= $due_amount-$previous_amount_pre;
									$previous_amount 	= 0 ;
									$balance_amount 	= 0;
									

							}
							if($previous_amount_pre == $due_amount){
									$due_amount  		= 0;
									$previous_amount 	= 0 ;
									$balance_amount 	= 0;
									
							}
									
						
									
				}
					 }else{
							  $due_amount = $license_fees;
							  
							  if($previous_amount_pre>$due_amount){
									
									$balance_amount  	= $previous_amount_pre-$due_amount;
									$due_amount 		= 0;
							}
							if($previous_amount_pre<$due_amount){
									$due_amount  		= $due_amount-$previous_amount_pre;
									$previous_amount 	= 0 ;
									$balance_amount 	= 0;
									

							}
							if($previous_amount_pre == $due_amount){
									$due_amount  		= 0;
									$previous_amount 	= 0 ;
									$balance_amount 	= 0;
									
							}
						  }
						
				$output.='<tr>
						<td>'.$i.'</td>
		             	<td>'.$rows->calculate_year.'</td>
						<td>'.$installed_power.'('.$unit.')</td>
						<td>'.$rows->worker_total.'</td>
						<td>'.$license_fees.'  ('.$fees_fetach['fees'].'*'.$rows->valid_time_period.')</td>
						<td>'.$late_fees_pay.'</td>
						<td>'.$previous_amount_pre.'</td>
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';	
						
					
										
					
		$output.='</tr>';
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$late_fees 			=0;
		$late_fees_pay = 0;
		$due_flag =0;
					 
				
		}
				 }
			
			
		
					
	
		
	}
  	if($date_convert <= '2015'){ 
		$max_payment_date		=		get_max_payment_date($application_id,$service_id,$factory_type_id,$reference_no);
		$payment				= 		0;
		if(empty($max_payment_date)){
					
					foreach($power_details as $rows){
						
							$start_date 		= $rows->calculate_starting_year;
							$cut_off_date_year  = date('Y',strtotime($start_date));
						 	$cut_off_date 		= $cut_off_date_year.'-03-31';
							$power_hp_kw  		= $rows->installed_power_hp;
							$installed_power  	= $rows->installed_power;
							$fees_fetach 		=	fees_calculation_registration_section_85($rows->calculate_starting_year);
							$license_fees 		= $fees_fetach['fees']*$rows->valid_time_period;
							$unit 		 		= $rows->power_unit;
							
							$cut_off_date1 = date_create($cut_off_date);
							
					 		if($application_date<$cut_off_date ){
								
								
								$diff			= date_diff($application_date1,$cut_off_date1);
								$big_diff  		= $diff->days;
								$late_year 		= $diff->year;
								 $late_year = $diff->y;
								$late_month = $diff->m;
								$late_day = $diff->d ;
								if($rows->valid_time_period>1){
											if($late_year>0){
											$fees_late_year = $late_year;
											if($late_month>0){
												$fees_late_year = $late_year+1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = $late_year+1;
											}
											$late_fees_pay = $fees_fetach['fees']*$fees_late_year; 
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 $late_fees_pay = $fees_fetach['fees']*$fees_late_year;
										}
									$late_fees = ($late_fees_pay)*(25/100);
							}else{
								$late_fees = ($license_fees)*(25/100);
							}
						 
					 		}if($application_date>$cut_off_date ){
								
								$diff			= date_diff($application_date1,$cut_off_date1);
								
								$big_diff  		= $diff->days;
								$late_year 		= $diff->year;
								 $late_year = $diff->y;
								$late_month = $diff->m;
								$late_day = $diff->d ;
								if($rows->valid_time_period>1){
											if($late_year>0){
											$fees_late_year = $late_year;
											if($late_month>0){
												$fees_late_year = $late_year+1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = $late_year+1;
											}
											$late_fees_pay = $fees_fetach['fees']*$fees_late_year; 
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 $late_fees_pay = $fees_fetach['fees']*$fees_late_year;
										}
									$late_fees = ($late_fees_pay)*(50/100);
							}else{
								$late_fees = ($license_fees)*(50/100);
							}
						 
					 		
						 
					 		}
							if($application_date==$cut_off_date ){
								$late_fees = ($fees_fetach['fees'])*(25/100);
								
								
							}
							$late_fees_pay 	= $late_fees;
							$due_amount 	= $license_fees+$late_fees_pay;
							$balance_amount = 0;
							$previous_amount_pre = !empty($previous_amount_pre)?$previous_amount_pre:0;
						$output.='<tr>
						<td>'.$i.'</td>
		             	<td>'.$rows->calculate_year.'</td>
						<td>'.$installed_power.'('.$unit.')</td>
						<td>'.$rows->worker_total.'</td>
						<td>'.$license_fees.'  ('.$fees_fetach['fees'].'*'.$rows->valid_time_period.')</td>
						<td>'.$late_fees_pay.'</td>
						<td>'.$previous_amount_pre.'</td>
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>
						';	
					
										
					
		$output.='</tr>';
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$Registration_fees 		=0;
		
	  	
	 
	   	$i= $i+1;
					}
					
				}
		if(!empty($max_payment_date)){
					$application_date 		= date('Y-m-d');
					$manual_payment			=  manual_payment_deatils($application_id,$service_id,$factory_type_id,$reference_no);
					 $manual_payment_count 	=  count($manual_payment);
					
					foreach($power_details as $rows){
							
							$application_date 	= date('Y-m-d');
							$start_date 		= $rows->calculate_starting_year;
							$cut_off_date_year  = date('Y',strtotime($start_date));
						 	$cut_off_date 		= $cut_off_date_year.'-03-31';
							$power_hp_kw  		= $rows->installed_power_hp;
							$installed_power  	= $rows->installed_power;
							$result_data 		=	fees_calculation_registration_section_85($rows->calculate_starting_year);
							$license_fees 		= $result_data['fees']*$rows->valid_time_period;
							$unit 		 		= $rows->power_unit;
							$due_license_amount = $license_fees; 
							 if($previous_amount_pre>$due_license_amount){
							  		$due_license_amount 		= 0;
							  		$balnce_amount 				= $previous_amount_pre-$due_license_amount;
							 		$due_amount 				= 0;
							  		$late_fees_pay 				= 0;
						  }if($previous_amount_pre<$due_license_amount){
							 		$balnce_amount 				= 0;
							 		$due_license_amount 		= $due_license_amount-$previous_amount_pre;
							  		$due_amount 				= 0;
						  }if($previous_amount_pre==$due_license_amount){
							  		$balance_amount 			= 0;
							  		$due_license_amount 		= 0;
							  		$due_amount 				= 0;
							  		$late_fees_pay 				= 0;
						  }if($due_license_amount>0){
							  while($payment < $manual_payment_count) {
								  
								  		  
								lebel1: if(($start_date>$manual_payment[$payment]->date_payment)&& !empty($manual_payment[$payment]->date_payment)){
											if(!empty($last_payment_date)){
												if($start_date>$last_payment_date){
													if($due_license_amount>$balance_license_amount){
																$previous_amount_pre = $balance_license_amount;
																$due_license_amount 	= $due_license_amount-$balance_license_amount;
																$balance_license_amount = 0;
																$last_payment_date 		= NULL;
													}
													if($due_license_amount<$balance_license_amount){
														$balance_license_amount1 = $balance_license_amount;
																$balance_license_amount =$balance_license_amount2= $balance_license_amount-$due_license_amount;
																$due_license_amount 	= 0;
																$previous_amount_pre = $balance_license_amount1;
																
													}if($due_license_amount==$balance_license_amount){
																$due_license_amount 	= 0;
																$balance_license_amount = 0;
																$last_payment_date 		= NULL;
																$previous_amount_pre = $balance_license_amount;
													}
										}
												if($start_date<$last_payment_date){
												$previous_amount_pre = $balance_license_amount;
										}
									}
								
								if($due_license_amount>$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 	= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$due_license_amount 	= $due_license_amount - $manual_payment[$payment]->payment_amount;
											$payment				= $payment+1 ;
											$flag_payment 			= 'due';
									 		goto lebel1;
								}
								if($due_license_amount<$manual_payment[$payment]->payment_amount){
										$previous_amount_pre 	= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										 $balance_license_amount 	=  $manual_payment[$payment]->payment_amount-$due_license_amount ;
											
											 if($due_license_amount==0){
												  $balance_license_amount = $balance_license_amount2+$manual_payment[$payment]->payment_amount;
											 }
											
											
											$last_payment_date  		= $manual_payment[$payment]->date_payment ;
											$payment					= $payment+1 ;
											$flag_payment  				= 'exhausted';
											$due_amount 				= 	0;
											$late_fees_pay 	 			=	0;
																	
											$manual_payment_date 		=  NULL;
											if(!empty($balance_license_amount) || $balance_license_amount != NULL || $balance_license_amount!=0){
												 $late_flag 					=	1;
												$balance_amount 			= 	$balance_license_amount;
												
												break;
											}else{
												$late_flag 					=	0;
												break;
											}
											
								}
								if($due_license_amount==$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$balance_license_amount 	= 0;
											$last_payment_date  		= NULL;
											$payment					= $payment+1 ;
											$flag_payment  				= 'exhausted';
											$due_amount 				= 0;
											$late_fees_pay 	 			= 0;
											$late_flag 					= 1;
											$balance_amount 			= $balance_license_amount;
											$manual_payment_date 		=  NULL;
											break;
								}
								if($due_license_amount !=0 ||empty($due_license_amount) ){
									if($application_date<=$cut_off_date ){
							 				$late_fees_pay 		= ($due_license_amount)*(25/100);
									 		$due_amount 		= $late_fees_pay+$license_fees;
											$balance_amount 	= $balance_license_amount;
											$late_flag 			=1;
						 			}if($application_date>$cut_off_date ){
										 	$late_fees_pay 		= ($due_license_amount)*(50/100);
										 	$due_amount 		= $late_fees_pay+$license_fees;
											$balance_amount 	= $balance_license_amount;
											$late_flag 			=1;
											
					 				}
								}
								
							}
							    lebel2: if($start_date<$manual_payment[$payment]->date_payment){					
									if(!empty($last_payment_date)){
										if($start_date>$last_payment_date){
										if($due_license_amount>$balance_license_amount){
											$previous_amount_pre 	= $balance_license_amount;
											$due_license_amount 	= $due_license_amount-$balance_license_amount;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
										}
										if($due_license_amount<$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = $balance_license_amount-$due_license_amount;
											$previous_amount_pre = $balance_license_amount;
										}if($due_license_amount==$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
											$previous_amount_pre = $balance_license_amount;

										}
									}
										if($start_date<$last_payment_date){
										if($balance_license_amount != 0){
											$previous_amount_pre = $balance_license_amount;
											$flag_balance = 1;
										}
											
											
											
										}
									}
									
									if($late_flag == 0 || empty($late_flag)){
										if($manual_payment[$payment]->date_payment<=$cut_off_date ){
							 			$late_fees_pay 	= ($due_license_amount)*(25/100);
									 	$due_amount 	= $late_fees_pay+$due_license_amount;
										$balance_amount = $balance_license_amount;
										$late_flag = 1;
						 			}if($manual_payment[$payment]->date_payment>$cut_off_date ){
										  $late_fees_pay 	= ($due_license_amount)*(50/100);
										  $due_amount 			= $late_fees_pay+$due_license_amount;
										  $balance_amount 		= $balance_license_amount;
										 $late_flag 			= 1;
									
											
					 				}
								}
									
									
									if($due_amount>$manual_payment[$payment]->payment_amount){
										
										if($flag_balance == 1){
												 $previous_amount_pre 	=  $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												
											  	 $due_amount 			=  $due_amount-$previous_amount_pre ;
												$flag_balance = 0;
												
											}else{
												 $previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												 $due_amount 	= $due_amount - $manual_payment[$payment]->payment_amount;
											
											}
											
										
										
										$late_flag =1;
										$balance_license_amount = 0;
										$payment	= $payment+1 ;
										$flag_balance =0;
									 	goto lebel2;
									}
									if($due_amount<$manual_payment[$payment]->payment_amount){
										 												
											if($flag_balance == 1){
												$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												 $balance_license_amount 	=  $previous_amount_pre-$due_amount ;
											}else{
												$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												 $balance_license_amount 	=  $manual_payment[$payment]->payment_amount-$due_amount ;
											}
											
											
										 	$last_payment_date  		= $manual_payment[$payment]->date_payment ;
											$due_amount 				= 0;
											$flag_payment  				= 'exhausted';
											$late_flag 					= 1;
											$payment					= $payment+1 ;
											$flag_balance = 0;
											break;
									}
									if($due_amount==$manual_payment[$payment]->payment_amount){
										$previous_amount_pre 	    = $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										$balance_license_amount 	=  0;
										$last_payment_date          = NULL;
										$flag_payment  				= 'exhausted';
										$late_flag 					=1;
										break;
									}
								}
								lebel3: if($start_date==$manual_payment[$payment]->date_payment){	
									
									if(!empty($last_payment_date)){
										if($start_date>$last_payment_date){
										if($due_license_amount>$balance_license_amount){
											$previous_amount_pre 	= $balance_license_amount;
											$due_license_amount 	= $due_license_amount-$balance_license_amount;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
										}if($due_license_amount<$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = $balance_license_amount-$due_license_amount;
											$previous_amount_pre 	= $balance_license_amount;
										}if($due_license_amount==$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
											$previous_amount_pre 	= $balance_license_amount;
										}
									}
										if($start_date<$last_payment_date){
											$previous_amount_pre = $balance_license_amount;
										}
									}
									
								
									if($application_date<=$cut_off_date ){
							 			$late_fees_pay 	= ($due_license_amount)*(25/100);
									 	$due_amount 		= $late_fees_pay+$due_license_amount;
										$balance_amount = $balance_license_amount;
										$late_flag = 1;
						 			}if($application_date>$cut_off_date ){
										 $late_fees_pay = ($due_license_amount)*(50/100);
										
										 $due_amount 	= $late_fees_pay+$due_license_amount;
										$balance_amount = $balance_license_amount;
										$late_flag = 1;
											
					 				}
									
									if($due_amount>$manual_payment[$payment]->payment_amount){
										 	$previous_amount_pre 	= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										 	$due_amount 			= $due_amount - $previous_amount_pre;
											$late_flag 				= 1;
											$payment				= $payment+1 ;
									 		goto lebel3;
									}
									if($due_amount<$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$balance_license_amount 	=  $manual_payment[$payment]->payment_amount-$due_amount ;

											$last_payment_date  		= $manual_payment[$payment]->date_payment ;
											$flag_payment  				= 'exhausted';
											$late_flag 					=1;
											break;
									}
									if($due_amount==$manual_payment[$payment]->payment_amount){
										$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										$balance_license_amount 	=  0;
										$last_payment_date 	 		= NULL ;
										$payment					= $payment+1 ;
										$flag_payment  		= 'exhausted';
										$late_flag =1;
										break;
									}
								}
						
							} 
			
							if($late_flag ==0  ){
								
								
							
							
								if($last_payment_date!=NULL || !empty($last_payment_date)){
									
								if($balance_license_amount>$due_license_amount){
									$previous_amount_pre 	= $balance_license_amount;
									 $balance_amount 		= $previous_amount_pre-$due_license_amount;
									$due_amount 			= 0;
									 $balance_license_amount = $balance_amount;
								}if($balance_license_amount<$due_license_amount){
									$previous_amount_pre 	= $balance_license_amount;
									$due_amount 	= $due_amount-$balance_license_amount;
									$balance_amount 		= 0;
									$last_payment_date		= NULL;
									$balance_license_amount = $balance_amount;
									
									if($last_payment_date<=$cut_off_date ){
							 			$late_fees_pay 	= ($due_amount)*(25/100);
										$due_amount 	= $late_fees_pay+$due_amount;
										$balance_amount = $balance_license_amount;
						 			}if($last_payment_date>$cut_off_date ){echo 88;
										$late_fees_pay 	= ($due_amount)*(50/100);
										$due_amount 	= $late_fees_pay+$due_amount;
										$balance_amount = $balance_license_amount;
											
					 				}
								
									
								}if($balance_license_amount==$due_license_amount){
									$previous_amount_pre 	= 0;
									$due_amount 			= 0;
									$balance_amount 		= 0;
									$balance_license_amount = $balance_amount;
								}
									
								}
							
							}
							 $balance_amount = $balance_license_amount;
						
							$due_amount_paid = $due_amount+$due_amount_paid;
						  }else{
							  $previous_amount_pre = $balnce_amount;
						  }
							
							
							
							 
						
						$output.='<tr>
									<td>'.$i.'</td>
		             				<td>'.$rows->calculate_year.'</td>
									<td>'.$installed_power.'('.$unit.')</td>
									<td>'.$rows->worker_total.'</td>
									<td>'.$license_fees.'  ('.$result_data['fees'].'*'.$rows->valid_time_period.')</td>
									<td>'.$late_fees_pay.'</td>
								
									<td>'.$previous_amount_pre.'</td>
									<td>'.$balance_amount.'</td>
									<td>'.$due_amount.'</td>';	
						$output.='</tr>';	
						$late_fees_pay 			= 	0;
						$previous_amount_pre 	=	0;
						$due_amount 			= 	0;
						$late_flag				= 0;
						$flag_payment 			=	'';
						$balance_amount =0;	
						$fees_to_paid = $due_amount_paid;
						$i++;
					}
				}
	   			
	}
	
	 if($date_convert >'2018'){
				
				$manual_payment			=  manual_payment_deatils($application_id,$service_id,$factory_type_id,$reference_no);
				foreach($manual_payment as $history){
					 $manual_payment_amount = $history->payment_amount+$manual_payment_amount;
					
				}
				$previous_amount_pre= $previous_excess_paid+$manual_payment_amount;
				foreach($power_details as $rows){		
					$power_hp_kw  			= $rows->installed_power_hp;
					$installed_power  		= $rows->installed_power;
					$unit 		 			= $rows->power_unit;
					$fees_fetach 			=	fees_calculation_registration_section_85($rows->calculate_starting_year);
					$license_fees		 	= $fees_fetach['fees']*$rows->valid_time_period;
					$max_payment_date		=	get_max_payment_date($application_id,$service_id,$factory_type_id,$reference_no);
					$start_date				= date_create($rows->calculate_starting_year);
		 			$application_date 		= date('Y-m-d');
					$application_date1		= date_create($application_date);
					$late_fees 				= 0;
				if($rows->calculate_starting_year < $application_date){ 
							$diff 		= date_diff($start_date,$application_date1);
							$big_diff   = $diff->days;
				}
					
					if($big_diff>=1 && $big_diff<=90){
									$late_fees = ($license_fees)*(50/100);
													
					}if($big_diff>91){
									$late_fees = $license_fees;
					}
					
				if(!empty($max_payment_date)){
					$payble_fees 	= $license_fees+$late_fees;
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
					$late_fees_pay 	= $late_fees;
					$due_amount 	= $license_fees+$late_fees_pay;
					$balance_amount = 0;
					
			
			
					
	}
				if(empty($previous_amount_pre)){
					$previous_amount_pre = 0;
				}
				$output.='<tr>
						<td>'.$i.'</td>
		             	<td>'.$rows->calculate_year.'</td>
						<td>'.$installed_power.'('.$unit.')</td>
						<td>'.$rows->worker_total.'</td>
						<td>'.$license_fees.'  ('.$fees_fetach['fees'].'*'.$rows->valid_time_period.')</td>
						<td>'.$late_fees_pay.'</td>
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
			
	  	   	$i= $i+1;
  		 }
				
				
				
			}	

$output .=' </table>
			<strong><font color="#FF0000">Fees to be paid(Total Due amount+Registration Fees):-'.($total_due_fees+$Registration_fees).'</font></strong></div></div>';
				
return $output;	
}

function calculate_manuall_fees($form, &$form_state){
	global $user;
	$val   								= 	$form_state['values'];
	$factory_type						= 	encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$service_id							= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$application_id						= 	encryption_decryption_fun('decrypt',$val['applicationid_hidden']);	
	$reference_no						= 	encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	$previousexcess_paid_hidden			= 	encryption_decryption_fun('decrypt',$val['previousexcesspaid_hidden']); 
	$last_validlicensedate				= 	encryption_decryption_fun('decrypt',$val['last_validlicensedate']); 
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
		$commands[] = ajax_command_replace('#fees_details_div', '<div id="fees_details_div"><div class="col-md-12">'.show_fees_registration_section_85($application_id,$service_id,$factory_type,$reference_no,$last_validlicensedate).'</div></div>');
		$commands[] = ajax_command_replace('#amand_fees_details_div', '<div id="amand_fees_details_div"><div class="col-md-12">'.show_fees_registration_amand($application_id,$service_id,$factory_type,$reference_no).'</div></div>');
		
	}
	
	if($factory_type==1){
		$commands[] = ajax_command_replace('#fees_details_div', '<div id="fees_details_div"><div class="col-md-12">'.show_fees_registration($application_id,$service_id,$factory_type,$reference_no,$total_previous_amount,$last_validlicensedate).'</div></div>');
		$commands[] = ajax_command_replace('#amand_fees_details_div', '<div id="amand_fees_details_div"><div class="col-md-12">'.show_fees_registration_amand($application_id,$service_id,$factory_type,$reference_no).'</div></div>');
	}if($factory_type==2){
		$commands[] = ajax_command_replace('#fees_details_div', '<div id="fees_details_div"><div class="col-md-12">'.show_fees_registration_2mii($application_id,$service_id,$factory_type,$reference_no,$total_previous_amount,$last_validlicensedate).'</div></div>');
		$commands[] = ajax_command_replace('#amand_fees_details_div', '<div id="amand_fees_details_div"><div class="col-md-12">'.show_fees_registration_amand_2mii($application_id,$service_id,$factory_type,$reference_no).'</div></div>');
	}
	$commands[] = ajax_command_replace('#add_payment_div', '<div id="add_payment_div"><div class="col-md-12"></div></div>');
	$commands[] = ajax_command_replace('#del_payment_div', '<div id="del_payment_div"><div class="col-md-12"></div></div>');
	$commands[] = ajax_command_replace('#fees_calculation_div', '<div id="fees_calculation_div"><div class="col-md-12"></div></div>');
	$commands[] = ajax_command_replace('#fees_pay_div', '<div id="fees_pay_div"><div class="col-xs-12"><input class="btn btn-info pull-right form-submit" id="edit-fees-pay" name="op" value="Pay now" type="submit"></div></div>');
	return array('#type' => 'ajax', '#commands' => $commands);
}


function save_fees_registration_2mi($application_id,$service_id,$factory_type,$reference_no,$previousexcess_paid_hidden,$last_validlicensedate){
	global $base_root, $base_path, $user,$total_fees_paid_to_end;
	$previous_amount_pre 				=   $previous_excess_paid;
	$Registration_fees 					= 	0;
	$created_by 						=   $user->uid;
	$modifi_date 						=   date("Y-m-d",strtotime($date_of_amenability));
	$last_validity						=   date("Y-m-d",strtotime($last_validlicensedate));
	$i									=	1;
	$date 								= 	date_create($last_validlicensedate);
	$date_convert 						= 	date_format($date, "Y");
	$date_convert1 						= 	date_format($date, "Y-m-d");	
	$power_details						= 	yearly_power_worker_details($application_id,$factory_type,$service_id,$reference_no);
	
    foreach($power_details as $rows){
		 $other = $rows->type_power_station;
	}
	$license_fees 			= 0;
	$late_fees				= 0;
	$current_year 			= date("Y");
	$fees 					= 0;
	$i						= 1;  
	$total_license_fees  	= 0;
	$total_transfer_fees 	= 0;
	$flag_adjust_balance 	= 0;
	$flag_late_calulate  	= 0;
	$flag_payment  			= '';
	$payment = 0;
	$late_flag = 0;
	$flag_balance = 0;
	$fees_to_paid =0;
	$due_flag = 0;
	$previous_amount_flag =0;
	if($other == "other"){
		 if($date_convert1 == '2018-12-31'){
			  $application_date 		= date('Y-m-d');
			  $power_hp_kw  			= $rows->installed_power_hp;
			  $unit 		  			= 'Hp';
			  $previous_amount_pre		= 0;
			  $max_payment_date 		= get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
			  $payment 					= 0;
			   if(!empty($max_payment_date)){
					  $manual_payment =  manual_payment_deatils($application_id,$service_id,$factory_typeid,$reference_number); 
					 $manual_payment_count =  count($manual_payment); 
					  foreach($power_details as $rows){
						   $result_data  = fees_calculation_registration($rows->installed_power_hp,$rows->worker_total,$rows->calculate_starting_year);
						  $license_fees=$license_fees_1 = $result_data['fees']*$rows->valid_time_period;
						  $license_start_date = $rows->calculate_starting_year;
						  if($license_start_date=='2019-01-01'){
							    	 $datey_cuttoff 		= '2019-01-15'; 
						}else{
							 		
									 	$year  			= date('Y',strtotime($license_start_date));
									  	$month 			= date('m',strtotime($license_start_date));
									   	$day  			= date('d',strtotime($license_start_date));
							 			$from_unix_time = mktime(0, 0, 0, $month, $day, $year);
										$day_before 	= strtotime("yesterday", $from_unix_time);
										$datey_cuttoff 	= date('Y-m-d', $day_before);
									
								
						}
						
						while(($payment < $manual_payment_count)&& ($flag_payment!= 'exhausted')){
							if($rows->calculate_starting_year > $manual_payment[$payment]->date_payment){
								 $previous_amount_pre = $previous_amount_pre+$manual_payment[$payment]->payment_amount;
							     if($license_fees_1 == $manual_payment[$payment]->payment_amount){
									 	$flag_payment = 'exhausted';
									  	$due_flag = 0;
								}if($license_fees_1 > $manual_payment[$payment]->payment_amount){
										 $due_amount_pre = ($license_fees_1-$manual_payment[$payment]->payment_amount);
									 	 $license_fees_1 = $due_amount_pre;
									 	$due_flag = 1;
								}if($license_fees < $manual_payment[$payment]->payment_amount){
									 $balance_amount = ($manual_payment[$payment]->payment_amount-$license_fees_1);
									 $due_flag = 0;
								}
							 }
						if($rows->calculate_starting_year <=$manual_payment[$payment]->date_payment){
								 $previous_amount_pre = $previous_amount_pre+$manual_payment[$payment]->payment_amount;
							}
						 	$payment++;
						 
						
						
						}
							
				
				 
				 if($application_date < $datey_cuttoff){//echo 'hie';
						 $late_fees_pay = 0;
						$due_amount 	= $license_fees+$late_fees_pay;
					}if($application_date >= $datey_cuttoff){
										
							if($rows->calculate_starting_year < $application_date){
										$start_date				= date_create($rows->calculate_starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
										$days_differ_app  		= $diff->days; 
							}if($rows->calculate_starting_year < $datey_cuttoff){
										$start_date				= date_create($rows->calculate_starting_year);
										$datey_cuttoff1			= date_create($datey_cuttoff);
										$diff					= date_diff($datey_cuttoff1,$start_date);
										$days_differ_cutt 		= $diff->days;
							}if($days_differ_app>$days_differ_cutt){
										$big_diff = $days_differ_app;
							}else{
									    $big_diff = $days_differ_cutt;
							}
							if($rows->calculate_starting_year > $application_date){
										$start_date		= date_create($rows->calculate_starting_year);
										$application_date1		= date_create($application_date);
										
										$diff			= date_diff($start_date,$application_date1);
										$big_diff  		= $diff->days;
							}
						
							if($due_flag ==1){
								$license_fees_late = $due_amount_pre;
							}else{
								$license_fees_late = $license_fees;
							}
							
							if($big_diff>=1 && $big_diff<=90){
									$late_fees_pay = ($license_fees_late)*(50/100);
													
							}if($big_diff>91){
									$late_fees_pay = $license_fees_late;
							}
							
							$due_amount 	= $license_fees+$late_fees_pay;
							if($previous_amount_flag == 1){
							
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
			'schedule_fees' 		     => $license_fees,
			'late_fees'              	 => $late_fees_pay,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $rows->calculate_year,
			'factory_type'				 => $factory_type,
			'application_reference_no'	 => $reference_no,
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
			'service_fees'				 => $Registration_fees,
			
			
			
		);
		//print_r($calculate_fees_details);
		
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
				
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$late_fees 			=0;
		$late_fees_pay = 0;
		$due_flag =0;
					 
				
		}
				 }
			   if(empty($max_payment_date)){
					  
						if($license_start_date=='2019-01-01'){
							    	 $datey_cuttoff 		= '2019-01-15'; 
						}else{
							 		
									 	$year  			= date('Y',strtotime($license_start_date));
									  	$month 			= date('m',strtotime($license_start_date));
									   	$day  			= date('d',strtotime($license_start_date));
							 			$from_unix_time = mktime(0, 0, 0, $month, $day, $year);
										$day_before 	= strtotime("yesterday", $from_unix_time);
										$datey_cuttoff 	= date('Y-m-d', $day_before);
									
								
						}
								
								foreach($power_details as $rows){
									$result_data  = fees_calculation_registration($rows->installed_power_hp,$rows->worker_total,$rows->calculate_starting_year);
									$license_fees = $result_data['fees']*$rows->valid_time_period;
									
										
										if($rows->calculate_starting_year < $application_date){
											   		$start_date				= date_create($rows->calculate_starting_year);
													$application_date1		= date_create($application_date);
													$diff					= date_diff($application_date1,$start_date);
												    $days_differ_app  		= $diff->days; 
										}if($rows->calculate_starting_year < $datey_cuttoff){
													$start_date				= date_create($rows->calculate_starting_year);
													$datey_cuttoff1			= date_create($datey_cuttoff);
													$diff					= date_diff($datey_cuttoff1,$start_date);
												    $days_differ_cutt 		= $diff->days;
										}if($days_differ_app>$days_differ_cutt){
													$big_diff = $days_differ_app;
										}else{
													$big_diff = $days_differ_cutt;
										}
										if($rows->calculate_starting_year > $application_date){ 
													$start_date		= date_create($rows->calculate_starting_year);
													$application_date1		= date_create($application_date);
													$diff			= date_diff($start_date,$application_date);
												    $big_diff  		= $diff->days;
										}
										
										if($big_diff>=1 && $big_diff<=90){
											$late_fees = ($license_fees)*(50/100);
													
										}if($big_diff>91){
													$late_fees = $license_fees;
										}
											
										$payble_fees 	= $license_fees+$late_fees;
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
											
										
									
									
		//print_r($result_data);
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
			'schedule_fees' 		     => $license_fees,
			'late_fees'              	 => $late_fees_pay,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $rows->calculate_year,
			'factory_type'				 => $factory_type,
			'application_reference_no'	 => $reference_no,
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
			'service_fees'				 => $Registration_fees,
			
			
			
		);
		//print_r($calculate_fees_details);
		
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
					
			
	}
		
	 	}
		 }
		if($date_convert >'2018'){
				foreach($power_details as $rows){		
					$power_hp_kw 			= $rows->installed_power_hp;
					$unit 		 			= 'Hp';
					$result_data 			= fees_calculation_registration($rows->installed_power_hp,$rows->worker_total,$rows->calculate_starting_year);
					$license_fees		 	= $result_data['fees']*$rows->valid_time_period;
					$max_payment_date 		= get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
					$start_date				= date_create($rows->calculate_starting_year);
		 			$application_date 		= date('Y-m-d');
					$application_date1		= date_create($application_date);
					$late_fees 				= 0;
					if($rows->calculate_starting_year < $application_date){ 
							$diff 		= date_diff($start_date,$application_date1);
							$big_diff   = $diff->days;
					}
					
					if($big_diff>=1 && $big_diff<=90){
									$late_fees = ($license_fees)*(50/100);
													
					}if($big_diff>91){
									$late_fees = $license_fees;
					}
					
				if(!empty($max_payment_date)){
					$payble_fees 	= $license_fees+$late_fees;
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
					$late_fees_pay 	= $late_fees;
					$due_amount 	= $license_fees+$late_fees_pay;
					$balance_amount = 0;
					
			
			
					
	}
	
	////echo'hssi';
	//($result_data);
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
			'schedule_fees' 		     => $license_fees,
			'late_fees'              	 => $late_fees_pay,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $rows->calculate_year,
			'factory_type'				 => $factory_type,
			'application_reference_no'	 => $reference_no,
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
			'service_fees'				 => $Registration_fees,
			
			
			
		);
		//print_r($calculate_fees_details);
		
	$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
				
			$previous_amount_pre 	= $balance_amount;
			$total_late_fees 		= $late_fees_pay+$total_late_fees;
			$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
			$total_due_fees 		= $due_amount+$total_due_fees;
			$fees_to_paid			= $total_due_fees;
			$Registration_fees 		=0;
			
	  	   	$i= $i+1;
  		 }//die();
				
				
				
			}
		if($date_convert <= '2015'){ 
				$max_payment_date = get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
				if(empty($max_payment_date)){
					$application_date 		= date('Y-m-d');
					foreach($power_details as $rows){
							//$application_date 	= '2016-03-31';
							$start_date 		= $rows->calculate_starting_year;
							$cut_off_date_year  = date('Y',strtotime($start_date));
						 	$cut_off_date 		= $cut_off_date_year.'-03-31';
							$power_hp_kw  		= $rows->installed_power_hp;
							$result_data 		= fees_calculation_registration($rows->installed_power_hp,$rows->worker_total,$rows->calculate_starting_year);
							$license_fees 		= $result_data['fees']*$rows->valid_time_period;
							$unit 		 		= 'Hp';
					 		if($application_date<=$cut_off_date ){
								$late_fees = ($license_fees)*(25/100);
						 
					 		}if($application_date>$cut_off_date ){
								$late_fees = ($license_fees)*(50/100);
						 
					 		}
							$late_fees_pay 	= $late_fees;
							$due_amount 	= $license_fees+$late_fees_pay;
			
							$balance_amount = 0;
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
			'service_fees'				 => $Registration_fees,
			
			
			
		);
	//print_r($calculate_fees_details);
		
	$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();			
		
					
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$Registration_fees 		=0;
		
	  	
	 
	   	$i= $i+1;
					}
					
				}
				if(!empty($max_payment_date)){
					$application_date 		= date('Y-m-d');
					$manual_payment			=  manual_payment_deatils($application_id,$service_id,$factory_typeid,$reference_number);
					//print_r($manual_payment);
					 $manual_payment_count 	=  count($manual_payment);// echo '<br/>'; 
					//die();
					//$payment = 0;
					foreach($power_details as $rows){
							$previous_amount_pre = 0;
							$application_date 	= date('Y-m-d');
							$start_date 		= $rows->calculate_starting_year;
							$cut_off_date_year  = date('Y',strtotime($start_date));
						 	$cut_off_date 		= $cut_off_date_year.'-03-31';
							$power_hp_kw  		= $rows->installed_power_hp;
							$result_data 		= fees_calculation_registration($rows->installed_power_hp,$rows->worker_total,$rows->calculate_starting_year);
							$license_fees 		= $result_data['fees']*$rows->valid_time_period;
							$unit 		 		= 'Hp';
							$due_license_amount = $license_fees; 
							while($payment < $manual_payment_count) {
								lebel1: if(($start_date>$manual_payment[$payment]->date_payment)&& !empty($manual_payment[$payment]->date_payment)){echo 'run lebel1';	
											if(!empty($last_payment_date)){
												if($start_date>$last_payment_date){
													if($due_license_amount>$balance_license_amount){
																$previous_amount_pre = $balance_license_amount;
																$due_license_amount 	= $due_license_amount-$balance_license_amount;
																$balance_license_amount = 0;
																$last_payment_date 		= NULL;
													}
													if($due_license_amount<$balance_license_amount){
																$due_license_amount 	= 0;
																$balance_license_amount = $balance_license_amount-$due_license_amount;
																$previous_amount_pre = $balance_license_amount;
													}if($due_license_amount==$balance_license_amount){
																$due_license_amount 	= 0;
																$balance_license_amount = 0;
																$last_payment_date 		= NULL;
																$previous_amount_pre = $balance_license_amount;
													}
										}if($start_date<$last_payment_date){
												$previous_amount_pre = $balance_license_amount;
										}
									}
								
								if($due_license_amount>$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 	= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$due_license_amount 	= $due_license_amount - $manual_payment[$payment]->payment_amount;
											$payment				= $payment+1 ;
											$flag_payment 			= 'due';
									 		goto lebel1;
								}
								if($due_license_amount<$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$balance_license_amount 	=  $manual_payment[$payment]->payment_amount-$due_license_amount ;
											$last_payment_date  		= $manual_payment[$payment]->date_payment ;
											$payment					= $payment+1 ;
											$flag_payment  				= 'exhausted';
											$due_amount 				= 	0;
											$late_fees_pay 	 			=	0;
											$late_flag 					=	1;
											$balance_amount 			= 	$balance_license_amount;
											$manual_payment_date 		=  NULL;
											break;
								}
								if($due_license_amount==$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$balance_license_amount 	= 0;
											$last_payment_date  		= NULL;
											$payment					= $payment+1 ;
											$flag_payment  				= 'exhausted';
											$due_amount 				= 0;
											$late_fees_pay 	 			= 0;
											$late_flag 					= 1;
											$balance_amount 			= $balance_license_amount;
											$manual_payment_date 		=  NULL;
											break;
								}
								if($due_license_amount !=0 ||empty($due_license_amount) ){
									if($application_date<=$cut_off_date ){
							 				$late_fees_pay 		= ($due_license_amount)*(25/100);
									 		$due_amount 		= $late_fees_pay+$license_fees;
											$balance_amount 	= $balance_license_amount;
											$late_flag 			=1;
						 			}if($application_date>$cut_off_date ){
										 	$late_fees_pay 		= ($due_license_amount)*(50/100);
										 	$due_amount 		= $late_fees_pay+$license_fees;
											$balance_amount 	= $balance_license_amount;
											$late_flag 			=1;
											
					 				}
								}
								
							}
							    lebel2: if($start_date<$manual_payment[$payment]->date_payment){						
									if(!empty($last_payment_date)){
										if($start_date>$last_payment_date){
										if($due_license_amount>$balance_license_amount){
											$previous_amount_pre 	= $balance_license_amount;
											$due_license_amount 	= $due_license_amount-$balance_license_amount;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
										}
										if($due_license_amount<$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = $balance_license_amount-$due_license_amount;
											$previous_amount_pre = $balance_license_amount;
										}if($due_license_amount==$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
											$previous_amount_pre = $balance_license_amount;
										}
									}
										if($start_date<$last_payment_date){
										if($balance_license_amount != 0){
											$previous_amount_pre = $balance_license_amount;
											$flag_balance = 1;
										}
											
											
											
										}
									}
									
									if($late_flag == 0 || empty($late_flag)){
										if($manual_payment[$payment]->date_payment<=$cut_off_date ){
							 			$late_fees_pay 	= ($due_license_amount)*(25/100);
									 	$due_amount 	= $late_fees_pay+$due_license_amount;
										$balance_amount = $balance_license_amount;
										$late_flag = 1;
						 			}if($manual_payment[$payment]->date_payment>$cut_off_date ){
										  $late_fees_pay 	= ($due_license_amount)*(50/100);
										  $due_amount 			= $late_fees_pay+$due_license_amount;
										  $balance_amount 		= $balance_license_amount;
										 $late_flag 			= 1;
										
											
					 				}
								}
									
									
									if($due_amount>$manual_payment[$payment]->payment_amount){
									
										if($flag_balance == 1){
												 $previous_amount_pre 	=  $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												
											  	 $due_amount 			=  $due_amount-$previous_amount_pre ;
												$flag_balance = 0;
												
											}else{
												 $previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												 $due_amount 	= $due_amount - $manual_payment[$payment]->payment_amount;
											
											}
											
									
										
										$late_flag =1;
										$balance_license_amount = 0;
										$payment	= $payment+1 ;
										$flag_balance =0;
									 	goto lebel2;
									}
									if($due_amount<$manual_payment[$payment]->payment_amount){
										 
											
											if($flag_balance == 1){
												$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												 $balance_license_amount 	=  $previous_amount_pre-$due_amount ;
											}else{
												$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												 $balance_license_amount 	=  $manual_payment[$payment]->payment_amount-$due_amount ;
											}
											
											
										 	$last_payment_date  		= $manual_payment[$payment]->date_payment ;
											$due_amount 				= 0;
											$flag_payment  				= 'exhausted';
											$late_flag 					= 1;
											$payment					= $payment+1 ;
											$flag_balance = 0;
											break;
									}
									if($due_amount==$manual_payment[$payment]->payment_amount){
										$previous_amount_pre 	    = $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										$balance_license_amount 	=  0;
										$last_payment_date          = NULL;
										$flag_payment  				= 'exhausted';
										$late_flag 					=1;
										break;
									}
								}
								lebel3: if($start_date==$manual_payment[$payment]->date_payment){
									
									if(!empty($last_payment_date)){
										if($start_date>$last_payment_date){
										if($due_license_amount>$balance_license_amount){
											$previous_amount_pre 	= $balance_license_amount;
											$due_license_amount 	= $due_license_amount-$balance_license_amount;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
										}if($due_license_amount<$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = $balance_license_amount-$due_license_amount;
											$previous_amount_pre 	= $balance_license_amount;
										}if($due_license_amount==$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
											$previous_amount_pre 	= $balance_license_amount;
										}
									}
										if($start_date<$last_payment_date){
											$previous_amount_pre = $balance_license_amount;
										}
									}
									
								
									if($application_date<=$cut_off_date ){
							 			$late_fees_pay 	= ($due_license_amount)*(25/100);
									 	$due_amount 		= $late_fees_pay+$due_license_amount;
										$balance_amount = $balance_license_amount;
										$late_flag = 1;
						 			}if($application_date>$cut_off_date ){
										 $late_fees_pay = ($due_license_amount)*(50/100);
										
										 $due_amount 	= $late_fees_pay+$due_license_amount;
										$balance_amount = $balance_license_amount;
										$late_flag = 1;
											
					 				}
									
									if($due_amount>$manual_payment[$payment]->payment_amount){
										 	$previous_amount_pre 	= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										 	$due_amount 			= $due_amount - $previous_amount_pre;
											$late_flag 				= 1;
											$payment				= $payment+1 ;
									 		goto lebel3;
									}
									if($due_amount<$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$balance_license_amount 	=  $manual_payment[$payment]->payment_amount-$due_amount ;
											$last_payment_date  		= $manual_payment[$payment]->date_payment ;
											$flag_payment  				= 'exhausted';
											$late_flag 					=1;
											break;
									}
									if($due_amount==$manual_payment[$payment]->payment_amount){
										$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										$balance_license_amount 	=  0;
										$last_payment_date 	 		= NULL ;
										$payment					= $payment+1 ;
										$flag_payment  		= 'exhausted';
										$late_flag =1;
										break;
									}
								}
								
							} 
						
							if($late_flag ==0  ){
								if($application_date<=$cut_off_date ){
							 		$late_fees_pay 	= ($due_license_amount)*(25/100);
									$due_amount 	= $late_fees_pay+$due_license_amount;
									$balance_amount = $balance_license_amount;
						 		}if($application_date>$cut_off_date ){
									$late_fees_pay 	= ($due_license_amount)*(50/100);
									$due_amount 	= $late_fees_pay+$due_license_amount;
									$balance_amount = $balance_license_amount;
											
					 			}
								if($balance_license_amount>$due_amount){
									$previous_amount_pre 	= $balance_license_amount;
									 $balance_amount 		= $previous_amount_pre-$due_amount;
									$due_amount 			= 0;
									 $balance_license_amount = $balance_amount;
								}if($balance_license_amount<$due_amount){
									$previous_amount_pre 	= $balance_license_amount;
									$due_amount 			= $due_amount-$balance_license_amount;
									$balance_amount 		= 0;
									$balance_license_amount = $balance_amount;
								}if($balance_license_amount==$due_amount){
									$previous_amount_pre 	= 0;
									$due_amount 			= 0;
									$balance_amount 		= 0;
									$balance_license_amount = $balance_amount;
								}
							
							}
							
							
							 
						 $balance_amount = $balance_license_amount;
						
						$due_amount_paid = $due_amount+$due_amount_paid;
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
			'schedule_fees' 		     => $license_fees,
			'late_fees'              	 => $late_fees_pay,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $rows->calculate_year,
			'factory_type'				 => $factory_type,
			'application_reference_no'	 => $reference_no,
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
			'service_fees'				 => $Registration_fees,
			
			
			
		);


		//print_r($calculate_fees_details);
		
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
							
		
						
						$late_fees_pay 			= 	0;
						$previous_amount_pre 	=	0;
						$due_amount 			= 	0;
						$late_flag 				=	0;
						$flag_payment 			=	'';
						$balance_amount =0;	
						$fees_to_paid = $due_amount_paid;
						$i++;
					}
				}
				
		}	

	}
	if($other == "power_generating_station"){
				$power_hp_kw 			= $rows->installed_power;
				$unit 		 			= 'KW';
				foreach($power_details as $rows){	
				$result_data 			= fees_calculation_registration_power_station($rows->installed_power,$rows->calculate_starting_year);
				
				$fees		 	 		= $result_data['fees']*$rows->valid_time_period;
				
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
				if(empty($max_payment_date)){//echo 'hi';die();
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
					'factory_type'				 => $factory_type,
					'application_reference_no'	 => $reference_no,
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
					'service_fees'				 => $Registration_fees,
			
			
			
			);


				
		
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
		//print_r($calculate_fees_details);
		
							
			$previous_amount_pre 	= $balance_amount;
			$total_late_fees 		= $late_fees_pay+$total_late_fees;
			$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
			$total_due_fees 		= $due_amount+$total_due_fees;
			$fees_to_paid			= $total_due_fees;
			$Registration_fees 		=0;
			$late_fees_pay =0;
	
	   	$i= $i+1;
		
	 }
}
	
      


save_fees_registration_amand($application_id,$service_id,$factory_type,$reference_no,$previous_excess_paid,$is_payment_mad);

}

function save_fees_registration_amand($application_id,$service_id,$factory_typeid,$reference_number,$previous_excess_paid,$is_payment_mad){
		global $base_root, $base_path, $user;
	$amandment_fess=$amandment_fess1 = 1000;
	$previous_excess_paid =  $_SESSION['balance_renewal'];

	$sl = 1;
	$Registration_fees 					= 	0;
	$created_by 						=   $user->uid;
	$modifi_date 						=   date("Y-m-d",strtotime($date_of_amenability));
	
	$i									=	1;
	$license_fees 						= 	0;
	$late_fees							= 	0;
	$current_year 						= 	date("Y");
	$fees 								= 	0;
	$i									= 	1;  
	$total_license_fees  				= 	0;
	$total_transfer_fees 				= 	0;
	$flag_adjust_balance 				= 	0;
	$flag_late_calulate  				= 	0;
	
	$flag_payment  						= '';
	$payment							= 0;
	$late_flag = 0;
	$flag_balance = 0;
	$fees_to_paid =0;
	$due_flag = 0;
	$previous_amount_flag =0;
	$total_amand_fees =0;
	$application_date 		= date('Y-m-d');
	$amend_value = fetch_old_data($application_id,$service_id,$factory_typeid,$reference_number);

	foreach($amend_value as $amand_row){
				$present_totalworker 			= $amand_row->worker_total;
				$present_power 		 			= $amand_row->installed_power;
				$present_installed_power_unit 	= $amand_row->power_unit;
				$previous_worker 		 		= $amand_row->previous_worker;
				$amand_year 		 			= $amand_row->service_year;
				$amand_valid_time_period 		= $amand_row->valid_time_period;
				$amand_starting_year		 	= $amand_row->starting_year;
				$amand_valid_year		 		= $amand_row->valid_year;
				$previous_power		 			= $amand_row->previous_power;
				$previous_power_unit		 	= $amand_row->previous_power_unit;
				$date_amand 					= date_create($amand_valid_year);
				$date_convert_amand 			= date_format($date_amand, "Y");

				$date_convert1_amand 			= date_format($date_amand, "Y-m-d");	
				
				
				
				if($present_installed_power_unit == "HP"){
					 $fees_previous  				= fees_calculation_registration($previous_power,$previous_worker,$amand_starting_year);
					 $fees_previous_paid 			= $fees_previous['fees']*$amand_valid_time_period;
					 $fees_previous_paid				= $fees_previous_paid+$previous_excess_paid;
					   if($date_convert1_amand == '2018-12-31'){
				  					
									$power_hp_kw  			= $present_power;
				 					$unit 		  			= 'Hp';
				 					$previous_amount_pre	= $fees_previous_paid;
				 					$payment 				= 0;
				 
				 if(!empty($fees_previous_paid)){
					
					  
						   $result_data  = fees_calculation_registration($present_power,$present_totalworker,$amand_starting_year);
						  
						  $license_fees=$license_fees_1 = $result_data['fees']*$amand_valid_time_period;
						   $license_start_date = $amand_starting_year;
						  if($license_start_date=='2019-01-01'){
							    	 $datey_cuttoff 		= '2019-01-15'; 
						}else{
							 		
									 	$year  			= date('Y',strtotime($license_start_date));
									  	$month 			= date('m',strtotime($license_start_date));
									   	$day  			= date('d',strtotime($license_start_date));
							 			$from_unix_time = mktime(0, 0, 0, $month, $day, $year);
										$day_before 	= strtotime("yesterday", $from_unix_time);
										$datey_cuttoff 	= date('Y-m-d', $day_before);
									
								
						}
						
						
					
				 
				 if($application_date < $datey_cuttoff){
						 $late_fees_pay = 0;
						 if($license_fees>$fees_previous_paid){
							  $due_amount 	=(($license_fees-$fees_previous_paid)+$late_fees_pay);
						 } else{
							 $due_amount 	=(($fees_previous_paid-$license_fees)+$late_fees_pay);
						 }
						
					}if($application_date >= $datey_cuttoff){
										
							if($amand_starting_year < $application_date){
										$start_date				= date_create($amand_starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
										$days_differ_app  		= $diff->days; 
							}if($amand_starting_year < $datey_cuttoff){
										$start_date				= date_create($amand_starting_year);
										$datey_cuttoff1			= date_create($datey_cuttoff);
										$diff					= date_diff($datey_cuttoff1,$start_date);
										$days_differ_cutt 		= $diff->days;
							}if($days_differ_app>$days_differ_cutt){
										$big_diff = $days_differ_app;
							}else{
									    $big_diff = $days_differ_cutt;
							}
							if($amand_starting_year > $application_date){
										$start_date		= date_create($amand_starting_year);
										$application_date1		= date_create($application_date);
										
										$diff			= date_diff($start_date,$application_date1);
										$big_diff  		= $diff->days;
							}
						
						
						if($license_fees>$fees_previous_paid){
							   $license_fees_late 	=$license_fees-$fees_previous_paid;
						 } else{
							  $license_fees_late 	=$fees_previous_paid-$license_fees;
						 }
							
							if($big_diff>=1 && $big_diff<=90){
									 $late_fees_pay = ($license_fees_late)*(50/100);
													
							}if($big_diff>91){
									 $late_fees_pay = $license_fees_late;
							}
							//echo $late_fees_pay;
							  $due_amount = $license_fees_late+$late_fees_pay;
							$balance_amount = 0;			
										
									
				}
					
				if($result_data['workers_end_to'] == -1){
		$max_worker = $present_totalworker." and onwords";
	}else{
		$max_worker = $result_data['workers_end_to'];
	}if($result_data['power_range_end_hp'] == -1){
		$max_power = $present_power." and onwords";
	}else{
		$max_power = $result_data['power_range_end_hp'];
	}	
						
		$calculate_fees_details = array(
			'feesyear' 		             => $result_data['feesyear'],
			'schedule_fees' 		     => $license_fees,
			'late_fees'              	 => $late_fees_pay,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $amand_year,
			'factory_type'				 => $factory_typeid,
			'application_reference_no'	 => $reference_number,
			'created_by'				 => $user->uid,
			'application_status'	     => 'N',
			'due_fees'    				 => $due_amount,
			'balance_amount'			 => $balance_amount,
			'previous_paid_fees'   	 	 => !empty($fees_previous_paid)?$fees_previous_paid:0,
			'max_worker'				 => $max_worker,
			'max_power'					 => $max_power.'(hp)',
			'worker'					 => $present_totalworker,
			'power'					 	 => $present_power.'(hp)',
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $amandment_fess,
			'previous_power'			 => $previous_power.'('.$previous_power_unit.')',
			'previous_worker'			 => $previous_worker,
			'remark'					 => 'Amendment',
			
			
		);
		
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
		$_SESSION["balance_renewal"] = NULL;					 
				
				 
				 }
			
				
				
			}
						if($date_convert_amand > '2018'){
				           		
							$power_hp_kw 			= $present_power;
							$unit 		 			= 'Hp';
							$result_data  			= fees_calculation_registration($present_power,$present_totalworker,$amand_starting_year);
							 $license_fees			=$license_fees_1 = $result_data['fees']*$amand_valid_time_period;
					  	    $license_start_date 	= $amand_starting_year;
							$application_date1		= date_create($application_date);
							$late_fees 				= 0;
							if($amand_starting_year < $application_date){ //echo 'hi';
									$start_date		= date_create($amand_starting_year);
									$application_date1		= date_create($application_date);
										
										$diff			= date_diff($start_date,$application_date1);
										$big_diff  		= $diff->days;
										$late_year = $diff->y;
										$late_month = $diff->m;
										$late_day = $diff->d ;
										if($late_year>0){
											$fees_late_year = $late_year;
											if($late_month>0){
												$fees_late_year = $late_year+1;
											}if($late_month==0 && $late_day >0){
												$fees_late_year = $late_year+1;
											}
											
											  $late_fees = $result_data['fees']*$fees_late_year;
										}if($late_year==0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month==0 && $late_day >0){
												$fees_late_year = 1;
											}
											 $late_fees = $result_data['fees']*$fees_late_year;
										}
										
							}
					
							if($big_diff>=1 && $big_diff<=90){
									$late_fees_pay = ($late_fees)*(50/100);
													
							}if($big_diff>91){
									$late_fees_pay = $late_fees;
							}
					
				
							 $payblefess = $license_fees+$late_fees_pay+$amandment_fess;
							if($payblefess>$fees_previous_paid){
								$due_amount = $payblefess-$fees_previous_paid;
								$balance_amount = 0;	
							}else{
								$balance_amount = $fees_previous_paid-$payblefess;
								$due_amount = 0;
							}
							
			
	if($result_data['workers_end_to'] == -1){
		$max_worker = $present_totalworker." and onwords";
	}else{
		$max_worker = $result_data['workers_end_to'];
	}if($result_data['power_range_end_hp'] == -1){
		$max_power = $present_power." and onwords";
	}else{
		$max_power = $result_data['power_range_end_hp'];
	}	
						
		$calculate_fees_details = array(
			'feesyear' 		             => $result_data['feesyear'],
			'schedule_fees' 		     => $license_fees,
			'late_fees'              	 => $late_fees_pay,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $amand_year,
			'factory_type'				 => $factory_typeid,
			'application_reference_no'	 => $reference_number,
			'created_by'				 => $user->uid,
			'application_status'	     => 'N',
			'due_fees'    				 => $due_amount,
			'balance_amount'			 => $balance_amount,
			'previous_paid_fees'   	 	 => !empty($fees_previous_paid)?$fees_previous_paid:0,
			'max_worker'				 => $max_worker,
			'max_power'					 => $max_power.'(hp)',
			'worker'					 => $present_totalworker,
			'power'					 	 => $present_power.'(hp)',
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $amandment_fess,
			'previous_power'			 => $previous_power.'('.$previous_power_unit.')',
			'previous_worker'			 => $previous_worker,
			'remark'					 => 'Amendment',
			
			
			
		);
	//print_r($calculate_fees_details);
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
		$_SESSION["balance_renewal"] = NULL;	
			
			
	}
						if($date_convert_amand <= '2015'){
				}
				           		
						
						$amandment_fess=0;
						$previous_excess_paid1 = $balance_amount;
						$total_amand_fees = $total_amand_fees+$due_amount;		
			}
			
			    if($present_installed_power_unit == "KW"){
					 $fees_previous  				= fees_calculation_registration_power_station($previous_power,$amand_starting_year);
					$fees_previous_paid 			= ($fees_previous['fees']*$amand_valid_time_period);
					 $fees_previous_paid				= $fees_previous_paid+$previous_excess_paid1;
						if($date_convert_amand == '2018-12-31'){
							
									$power_hp_kw  			= $present_power;
				 					$unit 		  			= 'Hp';
				 					$previous_amount_pre	= $fees_previous_paid;
				 					$payment 				= 0;
				 
						
					
					  
						   $result_data  = fees_calculation_registration_power_station($present_power,$amand_starting_year);
						  
						  $license_fees=$license_fees_1 = $result_data['fees']*$amand_valid_time_period;
						   $license_start_date = $amand_starting_year;
						  if($license_start_date=='2019-01-01'){
							    	 $datey_cuttoff 		= '2019-01-15'; 
						}else{
							 		
									 	$year  			= date('Y',strtotime($license_start_date));
									  	$month 			= date('m',strtotime($license_start_date));
									   	$day  			= date('d',strtotime($license_start_date));
							 			$from_unix_time = mktime(0, 0, 0, $month, $day, $year);
										$day_before 	= strtotime("yesterday", $from_unix_time);
										$datey_cuttoff 	= date('Y-m-d', $day_before);
									
								
						}
						
						
					
				 
				 if($application_date < $datey_cuttoff){
						 $late_fees_pay = 0;
						 if($license_fees>$fees_previous_paid){
							  $due_amount 	=(($license_fees-$fees_previous_paid)+$late_fees_pay);
						 } else{
							 $due_amount 	=(($fees_previous_paid-$license_fees)+$late_fees_pay);
						 }
						
					}if($application_date >= $datey_cuttoff){
										
							if($amand_starting_year < $application_date){
										$start_date				= date_create($amand_starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
										$days_differ_app  		= $diff->days; 
							}if($amand_starting_year < $datey_cuttoff){
										$start_date				= date_create($amand_starting_year);
										$datey_cuttoff1			= date_create($datey_cuttoff);
										$diff					= date_diff($datey_cuttoff1,$start_date);
										$days_differ_cutt 		= $diff->days;
							}if($days_differ_app>$days_differ_cutt){
										$big_diff = $days_differ_app;
							}else{
									    $big_diff = $days_differ_cutt;
							}
							if($amand_starting_year > $application_date){
										$start_date		= date_create($amand_starting_year);
										$application_date1		= date_create($application_date);
										
										$diff			= date_diff($start_date,$application_date1);
										$big_diff  		= $diff->days;
							}
						
						
						if($license_fees>$fees_previous_paid){
							   $license_fees_late 	=$license_fees-$fees_previous_paid;
						 } else{
							  $license_fees_late 	=$fees_previous_paid-$license_fees;
						 }
							
							if($big_diff>=1 && $big_diff<=90){
									 $late_fees_pay = ($license_fees_late)*(50/100);
													
							}if($big_diff>91){
									 $late_fees_pay = $license_fees_late;
							}
							
							  $due_amount = $license_fees_late+$late_fees_pay+$amandment_fess;
							$balance_amount = 0;			
										
									
				}
					
				if($result_data['workers_end_to'] == -1){
		$max_worker = $present_power." and onwords";
	}else{
		$max_worker = $result_data['workers_end_to'];
	}if($result_data['power_range_end_kw'] == -1){
		$max_power = $present_power." and onwords";
	}else{
		$max_power = $result_data['power_range_end_kw'];
	}
	
	
				$calculate_fees_details = array(
					'feesyear' 		             => $result_data['feesyear'],
					'schedule_fees' 		     => $license_fees,
					'late_fees'              	 => $late_fees_pay,
					'service_id' 		     	 => $service_id,
					'application_id'             => $application_id,
					'service_year' 	             => $amand_year,
					'factory_type'				 => $factory_typeid,
					'application_reference_no'	 => $reference_number,
					'created_by'				 => $user->uid,
					'application_status'	     => 'N',
					'due_fees'    				 => $due_amount,
					'balance_amount'			 => $balance_amount,
					'previous_paid_fees'   	 	 => !empty($previous_amount_pre)?$previous_amount_pre:0,
					'max_worker'				 => $max_worker,
					'max_power'					 => $max_power.'(KW)',
					'worker'					 => $present_totalworker,
					'power'					 	 => $present_power.'(KW)',
					'transfer_fees'				 => $total_transfer_fees,
					'service_fees'				 => $Registration_fees,
					'previous_power'			 => $previous_power.'('.$previous_power_unit.')',
					'previous_worker'			 => $previous_worker,
					'remark'					 => 'Amendment',
			
			
			
			);
$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
		$sl++;		
		$balance_amount = 0;	
		$_SESSION["balance_renewal"] = NULL;			
		 
				
				 
				 
			
				
				
		}
						if($date_convert_amand > '2018'){
				           		
							$power_hp_kw 			= $present_power;
							$unit 		 			= 'KW';
							$result_data  			= fees_calculation_registration_power_station($present_power,$amand_starting_year);
							$license_fees			= $license_fees_1 = $result_data['fees']*$amand_valid_time_period;
					  	    $license_start_date 	= $amand_starting_year;
							$application_date1		= date_create($application_date);
							$late_fees 				= 0;
							if($amand_starting_year < $application_date){
									$start_date		= date_create($amand_starting_year);
									$application_date1		= date_create($application_date);
										$diff			= date_diff($start_date,$application_date1);
										$big_diff  		= $diff->days;
										$late_year = $diff->y;
										$late_month = $diff->m;
										$late_day = $diff->d ;
										if($amand_valid_time_period>1){
											if($late_year>0){
											$fees_late_year = $late_year;
											if($late_month==0){
												$fees_late_year = $late_year+1;
											}if($late_month==0 && $late_day >0){
												$fees_late_year = $late_year+1;
											}
											
											  $late_fees = $result_data['fees']*$fees_late_year;
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 $late_fees = $result_data['fees']*$fees_late_year;
										}
										}
										
										 
							}
					
							if($big_diff>=1 && $big_diff<=90){
									$late_fees_pay = ($late_fees)*(50/100);
													
							}if($big_diff>91){
									 $late_fees_pay = $late_fees;
							}
					
				
							  $payblefess = $license_fees+$late_fees_pay;
							if($payblefess>$fees_previous_paid){
								$due_amount = $payblefess-$fees_previous_paid;
								$balance_amount = 0;	
							}else{
								$balance_amount = $fees_previous_paid-$payblefess;
								$due_amount = 0;
							}
							
			
	if($result_data['workers_end_to'] == -1){
		$max_worker = $present_power." and onwords";
	}else{
		$max_worker = $result_data['workers_end_to'];
	}if($result_data['power_range_end_kw'] == -1){
		$max_power = $present_power." and onwords";
	}else{
		$max_power = $result_data['power_range_end_kw'];
	}
	
	
				$calculate_fees_details = array(
					'feesyear' 		             => $result_data['feesyear'],
					'schedule_fees' 		     => $license_fees,
					'late_fees'              	 => $late_fees_pay,
					'service_id' 		     	 => $service_id,
					'application_id'             => $application_id,
					'service_year' 	             => $amand_year,
					'factory_type'				 => $factory_typeid,
					'application_reference_no'	 => $reference_number,
					'created_by'				 => $user->uid,
					'application_status'	     => 'N',
					'due_fees'    				 => $due_amount,
					'balance_amount'			 => $balance_amount,
					'previous_paid_fees'   	 	 => !empty($fees_previous_paid)?$fees_previous_paid:0,
					'max_worker'				 => $max_worker,
					'max_power'					 => $max_power.'(KW)',
					'worker'					 => $present_totalworker,
					'power'					 	 => $present_power.'(KW)',
					'transfer_fees'				 => $total_transfer_fees,
					'service_fees'				 => $Registration_fees,
					'previous_power'			 => $previous_power.'('.$previous_power_unit.')',
					'previous_worker'			 => $previous_worker,
					'remark'					 => 'Amendment',
			
			
			
			);
		//print_r($calculate_fees_details);
$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
		$_SESSION["balance_renewal"] = NULL;	
			
	}
				    	if($date_convert_amand <= '2015'){
							
								$cut_off_date_year  	= date('Y',strtotime($amand_starting_year));
						 		$cut_off_date 			= $cut_off_date_year.'-03-31';
								$result_data  			= fees_calculation_registration_power_station($present_power,$amand_starting_year);
								 $license_fees 			= $license_fees_1 = $result_data['fees']*$amand_valid_time_period;
								$unit 		 			= 'KW';
					 			if($application_date<=$cut_off_date ){
									
									if($fees_previous_paid>$license_fees){
										$late_fees_pay 		= 0; 
										$balance_amount = $fees_previous_paid-$license_fees;
										$due_amount 	= 0;
									}
									if($fees_previous_paid<$license_fees){
										$due_amount = $license_fees - $fees_previous_paid;
										$late_fees_pay = ($due_amount)*(25/100);
										$balance_amount = 0;
										$due_amount = $due_amount+$late_fees;
									}else{
										$late_fees 		= 0; 
										$balance_amount = 0;
										$due_amount 	= 0;
									}
									
									
						 
					 			}
								if($application_date>$cut_off_date ){
									
									if($fees_previous_paid>$license_fees){
										$late_fees_pay 		= 0; 
										$balance_amount 	= $fees_previous_paid-$license_fees;
										$due_amount 		= 0;
									}
									if($fees_previous_paid<$license_fees){
										$due_amount 	= $license_fees - $fees_previous_paid;
										$late_fees_pay 	= ($due_amount)*(50/100);
										$balance_amount = 0;
										$due_amount = $due_amount+$late_fees_pay;
									}else{
										$late_fees_pay 		= 0; 
										$balance_amount = 0;
										$due_amount 	= 0;
									}
									
									
						 
					 			}
								 $payblefess =$license_fees+$late_fees_pay;
								if($result_data['workers_end_to'] == -1){
		$max_worker = $present_power." and onwords";
	}else{
		$max_worker = $result_data['workers_end_to'];
	}if($result_data['power_range_end_kw'] == -1){
		$max_power = $present_power." and onwords";
	}else{
		$max_power = $result_data['power_range_end_kw'];
	}
	
				$calculate_fees_details = array(
					'feesyear' 		             => $result_data['feesyear'],
					'schedule_fees' 		     => $license_fees,
					'late_fees'              	 => $late_fees_pay,
					'service_id' 		     	 => $service_id,
					'application_id'             => $application_id,
					'service_year' 	             => $amand_year,
					'factory_type'				 => $factory_typeid,
					'application_reference_no'	 => $reference_number,
					'created_by'				 => $user->uid,
					'application_status'	     => 'N',
					'due_fees'    				 => $due_amount,
					'balance_amount'			 => $balance_amount,
					'previous_paid_fees'   	 	 => !empty($previous_amount_pre)?$previous_amount_pre:0,
					'max_worker'				 => $max_worker,
					'max_power'					 => $max_power.'(KW)',
					'worker'					 => $present_totalworker,
					'power'					 	 => $present_power.'(KW)',
					'transfer_fees'				 => $total_transfer_fees,
					'service_fees'				 => $Registration_fees,
					'previous_power'			 => $previous_power.'('.$previous_power_unit.')',
					'previous_worker'			 => $previous_worker,
					'remark'					 => 'Amendment',
			
			
			
			);
			
			//print_r($calculate_fees_details);
$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
						$_SESSION["balance_renewal"] = NULL;	
							
						}
				           		
						$amandment_fess=0;
						$previous_excess_paid1 = $balance_amount;
						$total_amand_fees = $total_amand_fees+$due_amount;
						}
			
						   
	}	
			
	if(empty($previous_excess_paid) || $previous_excess_paid==NULL || $previous_excess_paid==0){
	
	$fees_deatils = array('service_fees'=>$amandment_fess1,'payment_amount'=>$_SESSION["renewal_fees"],'is_previous_payment'=>'No','balance_amount'=>$_SESSION["renewal_amand_balance"],'is_notesheet_amount'=> 0,'application_status'=>'P');
}
else{
	$fees_deatils = array('service_fees'=>$amandment_fess1,'previous_excess_paid'=>$previous_excess_paid,'payment_amount'=>$_SESSION["renewal_fees"],'is_previous_payment'=>'Yes','balance_amount'=>$_SESSION["renewal_amand_balance"],'is_notesheet_amount'=> 0,'application_status' =>'P','modification_date'=>date('Y-m-d'));
}

	//print_r($fees_deatils);die();
				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		->	fields($fees_deatils);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc		->	execute();
				
 
   remark_input($reference_number,$application_id,'P','Payment process is sucessfully completed')	;	
	fun_grip_input($_SESSION["renewal_fees"],$application_id,$service_id,$reference_number,$factory_typeid);
	$_SESSION["renewal_fees"] = NULL;
	drupal_goto('applicant/view-payment-breakup/' .encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_typeid).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_number));
	
	
	
	

	
	
}



function save_fees_registration_2mii($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid,$last_validlicensedate){
	$i= 1;
	global $base_root, $base_path, $user;
 $license_fees 				= 	0;
 $Registration_fees 		=	0;
 $fees 						=	0;
 $worker_detials 			= 	worker_detials_for_fees2mii($application_id,$reference_no,$factory_type_id,$service_id);
 $get_fa_cafa 				= 	get_fa_cafa($application_id);
 $previous_amount_pre		= 	$get_fa_cafa['previous_excess_paid'];
 $balance_amount_preservice	= 	$get_fa_cafa['balance_amount'];
 $date 						= 	date_create($last_validlicensedate);
 $date_convert 				= 	date_format($date, "Y");
 $date_convert1 			= 	date_format($date, "Y-m-d");	
  $previous_amount_pre= $balance_amount_preservice;
 if($date_convert1 == '2018-12-31'){
				 
		$max_payment_date 		= get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
	    $payment 				= 0;
				 
		if(!empty($max_payment_date)){
					  $manual_payment =  manual_payment_deatils($application_id,$service_id,$factory_typeid,$reference_number); 
					 $manual_payment_count =  count($manual_payment); 
					  foreach($worker_detials as $worker){
						   $result_data  = fees_calculation_registration_2mii($worker->start_year,$worker->total_worker);
						  $license_fees=$license_fees_1 = $result_data['fees']*$worker->vaild_period;
						  $license_start_date = $worker->starting_year;
						  if($balance_amount_preservice>$license_fees_1){
							  $license_fees_1 = 0;
							  $balnce_amount = $balance_amount_preservice-$license_fees_1;
							  $due_amount = 0;
							  $late_fees_pay = 0;
						  }if($balance_amount_preservice<$license_fees_1){
							  $balnce_amount = 0;
							  $license_fees_1 = $license_fees_1-$balance_amount_preservice;
							  $due_amount = 0;
						  }if($balance_amount_preservice==$license_fees_1){
							  $balance_amount = 0;
							  $license_fees_1 = 0;
							  $due_amount = 0;
							  $late_fees_pay = 0;
						  }
						  if($license_fees_1 >0){
							   if($license_start_date=='2019-01-01'){
							    	 $datey_cuttoff 		= '2019-01-15'; 
						}else{
							 		
									 	$year  			= date('Y',strtotime($license_start_date));
									  	$month 			= date('m',strtotime($license_start_date));
									   	$day  			= date('d',strtotime($license_start_date));
							 			$from_unix_time = mktime(0, 0, 0, $month, $day, $year);
										$day_before 	= strtotime("yesterday", $from_unix_time);
										$datey_cuttoff 	= date('Y-m-d', $day_before);
									
								
						}
						
							  while(($payment < $manual_payment_count)&& ($flag_payment!= 'exhausted')){
							if($rows->calculate_starting_year > $manual_payment[$payment]->date_payment){
								 $previous_amount_pre = $previous_amount_pre+$manual_payment[$payment]->payment_amount;
							     if($license_fees_1 == $manual_payment[$payment]->payment_amount){
									 	$flag_payment = 'exhausted';
									  	$due_flag = 0;
								}if($license_fees_1 > $manual_payment[$payment]->payment_amount){
										 $due_amount_pre = ($license_fees_1-$manual_payment[$payment]->payment_amount);
									 	 $license_fees_1 = $due_amount_pre;
									 	$due_flag = 1;
								}if($license_fees < $manual_payment[$payment]->payment_amount){
									 $balance_amount = ($manual_payment[$payment]->payment_amount-$license_fees_1);
									 $due_flag = 0;
								}
							 }//echo $payment;
						if($rows->calculate_starting_year <=$manual_payment[$payment]->date_payment){
								 $previous_amount_pre = $previous_amount_pre+$manual_payment[$payment]->payment_amount;
							}
						 	$payment++;
						 
						
						
						}
															 
				 			if($application_date < $datey_cuttoff){
						 $late_fees_pay = 0;
						$due_amount 	= $license_fees+$late_fees_pay;
					}
							if($application_date >= $datey_cuttoff){
										
							if($rows->calculate_starting_year < $application_date){
										$start_date				= date_create($rows->calculate_starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
										$days_differ_app  		= $diff->days; 
							}if($rows->calculate_starting_year < $datey_cuttoff){
										$start_date				= date_create($rows->calculate_starting_year);
										$datey_cuttoff1			= date_create($datey_cuttoff);
										$diff					= date_diff($datey_cuttoff1,$start_date);
										$days_differ_cutt 		= $diff->days;
							}if($days_differ_app>$days_differ_cutt){
										$big_diff = $days_differ_app;
							}else{
									    $big_diff = $days_differ_cutt;
							}
							if($rows->calculate_starting_year > $application_date){
										$start_date		= date_create($rows->calculate_starting_year);
										$application_date1		= date_create($application_date);
										
										$diff			= date_diff($start_date,$application_date1);
										$big_diff  		= $diff->days;
										
							}
						}
						
							if($due_flag ==1){
								$license_fees_late = $due_amount_pre;
							}else{
								$license_fees_late = $license_fees;
							}
							
							if($big_diff>=1 && $big_diff<=90){
									$late_fees_pay = ($license_fees_late)*(50/100);
													
							}if($big_diff>91){
									$late_fees_pay = $license_fees_late;
							}
							
							$due_amount 	= $license_fees+$late_fees_pay;
							if($previous_amount_flag == 1){
							
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
						  }
						  else{
							  $balance_amount_preservice = $balnce_amount;
						  }
						 				
						
									
				
		$calculate_fees_details = array(
			'feesyear' 		             => $schedule_fees['feesyear'],
			'schedule_fees' 		     => $license_fees,
			'late_fees'              	 => $late_fees,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $worker->application_period,
			'factory_type'				 => $factory_type_id,
			'application_reference_no'	 => $reference_no,
			'created_by'				 => $user->uid,
			'application_status'	     => 'N',
			'due_fees'    				 => $due_amount,
			'balance_amount'			 => $balance_amount,
			'previous_paid_fees'   	 	 => !empty($previous_amount_pre)?$previous_amount_pre:0,
			'max_worker'				 => $max_worker,
			'worker'					 => $worker->total_worker,
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $Registration_fees,
			
			
			
		);
					
	$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
		print_r($calculate_fees_details);
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$late_fees 			=0;
		$late_fees_pay = 0;
		$due_flag =0;
					 
		$i++;		
		}
	
		} if(empty($max_payment_date)){
			if($license_start_date=='2019-01-01'){
					$datey_cuttoff 		= '2019-01-15'; 
			}else{
							 		
						$year  			= date('Y',strtotime($license_start_date));
						$month 			= date('m',strtotime($license_start_date));
						$day  			= date('d',strtotime($license_start_date));
						$from_unix_time = mktime(0, 0, 0, $month, $day, $year);

						$day_before 	= strtotime("yesterday", $from_unix_time);
						$datey_cuttoff 	= date('Y-m-d', $day_before);
									
								
				}					
				foreach($worker_detials as $worker){
					 $result_data  = fees_calculation_registration_2mii($worker->start_year,$worker->total_worker);
					 $license_fees=$license_fees_1 = $result_data['fees']*$worker->vaild_period;
					 if($previous_amount_pre>$license_fees_1){
							  $license_fees_1 = 0;
							  $balnce_amount = $previous_amount_pre-$license_fees_1;
							  $due_amount = 0;
							  $late_fees_pay = 0;
						  }if($previous_amount_pre<$license_fees_1){
							  $balnce_amount = 0;
							  $license_fees_1 = $license_fees_1-$previous_amount_pre;
							  $due_amount = 0;
						  }if($previous_amount_pre==$license_fees_1){
							  $balance_amount = 0;
							  $license_fees_1 = 0;
							  $due_amount = 0;
							  $late_fees_pay = 0;
						  }
						  
				 if($license_fees_1 >0){
						  
										if($worker->starting_year < $application_date){
											   		$start_date				= date_create($rows->calculate_starting_year);
													$application_date1		= date_create($application_date);
													$diff					= date_diff($application_date1,$start_date);
												    $days_differ_app  		= $diff->days; 
										}if($worker->starting_year < $datey_cuttoff){
													$start_date				= date_create($rows->calculate_starting_year);
													$datey_cuttoff1			= date_create($datey_cuttoff);
													$diff					= date_diff($datey_cuttoff1,$start_date);
												    $days_differ_cutt 		= $diff->days;
										}if($days_differ_app>$days_differ_cutt){
													$big_diff = $days_differ_app;
										}else{
													$big_diff = $days_differ_cutt;
										}
										if($rows->starting_year > $application_date){ 
													$start_date		= date_create($rows->calculate_starting_year);
													$application_date1		= date_create($application_date);
													$diff			= date_diff($start_date,$application_date);
												    $big_diff  		= $diff->days;
													
												
													
													
										}
										
										if($big_diff>=1 && $big_diff<=90){
											$late_fees = ($late_fees_up)*(50/100);
													
										}if($big_diff>91){
													$late_fees = $late_fees_up;
										}
											
										$payble_fees 	= $license_fees+$late_fees;
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
							}else{
							  $previous_amount_pre = $balnce_amount;
						  }
						 		
										
									
					$calculate_fees_details = array(
			'feesyear' 		             => $schedule_fees['feesyear'],
			'schedule_fees' 		     => $license_fees,
			'late_fees'              	 => $late_fees,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $worker->application_period,
			'factory_type'				 => $factory_type_id,
			'application_reference_no'	 => $reference_no,
			'created_by'				 => $user->uid,
			'application_status'	     => 'N',
			'due_fees'    				 => $due_amount,
			'balance_amount'			 => $balance_amount,
			'previous_paid_fees'   	 	 => !empty($previous_amount_pre)?$previous_amount_pre:0,
			'max_worker'				 => $max_worker,
			'worker'					 => $worker->total_worker,
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $Registration_fees,
			
			
			
		);
					
	$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
		//print_r($calculate_fees_details);
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$late_fees 			=0;
		$late_fees_pay = 0;
		
	}
 		}
							
 }
 if($date_convert1>2018){
		
	$previous_amount_pre= $previous_excess_paid;	
		foreach($worker_detials as $worker){
			$schedule_fees 			= fees_calculation_registration_2mii($worker->start_year,$worker->total_worker);
			$license_fees 			= $schedule_fees['fees']*$worker->vaild_period;
			$datex 					= new DateTime($worker->starting_year);
			$datey 					= new DateTime('2015-12-31');
			if($worker->starting_year < $application_date){ 
				$diff 		= date_diff($start_date,$application_date1);
				$big_diff   = $diff->days;
		
			}
					
	if($big_diff>=1 && $big_diff<=90){
			$late_fees = $license_fees*(50/100);
													
	}if($big_diff>91){
			$late_fees = $license_fees*$fees_late_year;
	}else{
		$late_fees = 0;
	}
	
	$payble_fees 		= ($license_fees+$late_fees_pay+$amandment_fess);
	if($previous_amount_pre>$payble_fees){
						
							$balance_amount  	= $previous_amount_pre-$payble_fees;
							$due_amount 		= 0;
						
					}
					if($previous_amount_pre<$payble_fees){
								$due_amount  		= $payble_fees-$previous_amount_pre;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
						
							
					}
					if($previous_amount_pre == $payble_fees){
								$due_amount  		= 0;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								
							
					}	

	
		
	  if($schedule_fees['workers_end_to'] == -1){
			$max_worker = $rows->total_worker." and onwords";
		}else{
			$max_worker = $schedule_fees['workers_end_to'];
		}
		
		$calculate_fees_details = array(
			'feesyear' 		             => $schedule_fees['feesyear'],
			'schedule_fees' 		     => $license_fees,
			'late_fees'              	 => $late_fees,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $worker->application_period,
			'factory_type'				 => $factory_type_id,
			'application_reference_no'	 => $reference_no,
			'created_by'				 => $user->uid,
			'application_status'	     => 'N',
			'due_fees'    				 => $due_amount,
			'balance_amount'			 => $balance_amount,
			'previous_paid_fees'   	 	 => !empty($previous_amount_pre)?$previous_amount_pre:0,
			'max_worker'				 => $max_worker,
			'worker'					 => $worker->total_worker,
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $Registration_fees,
			
			
			
		);
		
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
		//print_r($calculate_fees_details);
			$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$Registration_fees 		=0;
		$i = $i+1;
		$total_fees = $due_amount;
	}
	
	}
 if($date_convert <= '2015'){ 
				$max_payment_date = get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
				if(empty($max_payment_date)){
					$application_date 		= date('Y-m-d');
					foreach($power_details as $rows){
							
							$start_date 		= $worker->starting_year;
							$cut_off_date_year  = date('Y',strtotime($start_date));
						 	$cut_off_date 		= $cut_off_date_year.'-03-31';
							$result_data 		= fees_calculation_registration_2mii($worker->start_year,$worker->total_worker);
							$license_fees 		= $license_fees= $result_data['fees']*$rows->valid_time_period;
							 if($balance_amount_preservice>$license_fees){
							  $license_fees = 0;
							  $balnce_amount = $balance_amount_preservice-$license_fees_1;
							  $due_amount = 0;
							  $late_fees_pay = 0;
						  }if($balance_amount_preservice<$license_fees){
							  $balnce_amount = 0;
							  $license_fees = $license_fees-$balance_amount_preservice;
							  $due_amount = 0;
						  }if($balance_amount_preservice==$license_fees){
							  $balance_amount = 0;
							  $license_fees = 0;
							  $due_amount = 0;
							  $late_fees_pay = 0;
						  }  if($license_fees >0){
					 		if($application_date<=$cut_off_date ){
								$late_fees = ($license_fees)*(25/100);
						 
					 		}if($application_date>$cut_off_date ){
								$late_fees = ($license_fees)*(50/100);
						 
					 		}
							$late_fees_pay 	= $late_fees;
							$due_amount 	= $license_fees+$late_fees_pay;
							$balance_amount = 0;
						  }else{
							   $balance_amount_preservice = $balnce_amount;
						  }
						$output.='<tr>
						<td>'.$i.'</td>
		             	<td>'.$rows->calculate_year.'</td>
						<td>'.$power_hp_kw.'('.$unit.')</td>
						<td>'.$rows->worker_total.'</td>
						<td>'.$license_fees.'  ('.$result_data['fees'].'*'.$rows->valid_time_period.')</td>
						<td>'.$late_fees_pay.'</td>
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
		
	  	
	 
	   	$i= $i+1;
					}
					
				}
				if(!empty($max_payment_date)){
					$application_date 		= date('Y-m-d');
					$manual_payment			=  manual_payment_deatils($application_id,$service_id,$factory_typeid,$reference_number);
				
					 $manual_payment_count 	=  count($manual_payment);
					
					foreach($power_details as $rows){
							$previous_amount_pre = 0;
							$application_date 	= date('Y-m-d');
							$start_date 		= $$worker->starting_year;
							$cut_off_date_year  = date('Y',strtotime($start_date));
						 	$cut_off_date 		= $cut_off_date_year.'-03-31';
							$result_data 		= fees_calculation_registration_2mii($worker->start_year,$worker->total_worker);
							$license_fees 		= $result_data['fees']*$worker->vaild_period;
							$due_license_amount = $license_fees; 
							 if($balance_amount_preservice>$due_license_amount){
							  $due_license_amount = 0;
							  $balnce_amount = $balance_amount_preservice-$due_license_amount;
							  $due_amount = 0;
							  $late_fees_pay = 0;
						  }if($balance_amount_preservice<$due_license_amount){
							  $balnce_amount = 0;
							  $due_license_amount = $due_license_amount-$balance_amount_preservice;
							  $due_amount = 0;
						  }if($balance_amount_preservice==$due_license_amount){
							  $balance_amount = 0;
							  $due_license_amount = 0;
							  $due_amount = 0;
							  $late_fees_pay = 0;
						  }if($due_license_amount>0){
							  while($payment < $manual_payment_count) {
								lebel1: if(($start_date>$manual_payment[$payment]->date_payment)&& !empty($manual_payment[$payment]->date_payment)){echo 'run lebel1';	
											if(!empty($last_payment_date)){
												if($start_date>$last_payment_date){
													if($due_license_amount>$balance_license_amount){
																$previous_amount_pre = $balance_license_amount;
																$due_license_amount 	= $due_license_amount-$balance_license_amount;
																$balance_license_amount = 0;
																$last_payment_date 		= NULL;
													}
													if($due_license_amount<$balance_license_amount){
																$due_license_amount 	= 0;
																$balance_license_amount = $balance_license_amount-$due_license_amount;
																$previous_amount_pre = $balance_license_amount;
													}if($due_license_amount==$balance_license_amount){
																$due_license_amount 	= 0;
																$balance_license_amount = 0;
																$last_payment_date 		= NULL;
																$previous_amount_pre = $balance_license_amount;
													}
										}if($start_date<$last_payment_date){
												$previous_amount_pre = $balance_license_amount;
										}
									}
								
								if($due_license_amount>$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 	= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$due_license_amount 	= $due_license_amount - $manual_payment[$payment]->payment_amount;
											$payment				= $payment+1 ;
											$flag_payment 			= 'due';
									 		goto lebel1;
								}
								if($due_license_amount<$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$balance_license_amount 	=  $manual_payment[$payment]->payment_amount-$due_license_amount ;
											$last_payment_date  		= $manual_payment[$payment]->date_payment ;
											$payment					= $payment+1 ;
											$flag_payment  				= 'exhausted';
											$due_amount 				= 	0;
											$late_fees_pay 	 			=	0;
											$late_flag 					=	1;
											$balance_amount 			= 	$balance_license_amount;
											$manual_payment_date 		=  NULL;
											break;
								}
								if($due_license_amount==$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$balance_license_amount 	= 0;
											$last_payment_date  		= NULL;
											$payment					= $payment+1 ;
											$flag_payment  				= 'exhausted';
											$due_amount 				= 0;
											$late_fees_pay 	 			= 0;
											$late_flag 					= 1;
											$balance_amount 			= $balance_license_amount;
											$manual_payment_date 		=  NULL;
											break;
								}
								if($due_license_amount !=0 ||empty($due_license_amount) ){
									if($application_date<=$cut_off_date ){
							 				$late_fees_pay 		= ($due_license_amount)*(25/100);
									 		$due_amount 		= $late_fees_pay+$license_fees;
											$balance_amount 	= $balance_license_amount;
											$late_flag 			=1;
						 			}if($application_date>$cut_off_date ){
										 	$late_fees_pay 		= ($due_license_amount)*(50/100);
										 	$due_amount 		= $late_fees_pay+$license_fees;
											$balance_amount 	= $balance_license_amount;
											$late_flag 			=1;
											
					 				}
								}
								
							}
							    lebel2: if($start_date<$manual_payment[$payment]->date_payment){						
									if(!empty($last_payment_date)){
										if($start_date>$last_payment_date){
										if($due_license_amount>$balance_license_amount){
											$previous_amount_pre 	= $balance_license_amount;
											$due_license_amount 	= $due_license_amount-$balance_license_amount;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
										}
										if($due_license_amount<$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = $balance_license_amount-$due_license_amount;
											$previous_amount_pre = $balance_license_amount;
										}if($due_license_amount==$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
											$previous_amount_pre = $balance_license_amount;
										}
									}
										if($start_date<$last_payment_date){
										if($balance_license_amount != 0){
											$previous_amount_pre = $balance_license_amount;
											$flag_balance = 1;
										}
											
											
											
										}
									}
									
									if($late_flag == 0 || empty($late_flag)){
										if($manual_payment[$payment]->date_payment<=$cut_off_date ){
							 			$late_fees_pay 	= ($due_license_amount)*(25/100);
									 	$due_amount 	= $late_fees_pay+$due_license_amount;
										$balance_amount = $balance_license_amount;
										$late_flag = 1;
						 			}if($manual_payment[$payment]->date_payment>$cut_off_date ){
										  $late_fees_pay 	= ($due_license_amount)*(50/100);
										  $due_amount 			= $late_fees_pay+$due_license_amount;
										  $balance_amount 		= $balance_license_amount;
										 $late_flag 			= 1;
										
											
					 				}
								}
									
									
									if($due_amount>$manual_payment[$payment]->payment_amount){
										
										if($flag_balance == 1){
												 $previous_amount_pre 	=  $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												
											  	 $due_amount 			=  $due_amount-$previous_amount_pre ;
												$flag_balance = 0;
												
											}else{
												 $previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												 $due_amount 	= $due_amount - $manual_payment[$payment]->payment_amount;
												
											}
											
									
										
										$late_flag =1;
										$balance_license_amount = 0;
										$payment	= $payment+1 ;
										$flag_balance =0;
									 	goto lebel2;
									}
									if($due_amount<$manual_payment[$payment]->payment_amount){
										 
											
											if($flag_balance == 1){
												$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												 $balance_license_amount 	=  $previous_amount_pre-$due_amount ;
											}else{
												$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												 $balance_license_amount 	=  $manual_payment[$payment]->payment_amount-$due_amount ;
											}
											
											
										 	$last_payment_date  		= $manual_payment[$payment]->date_payment ;
											$due_amount 				= 0;
											$flag_payment  				= 'exhausted';
											$late_flag 					= 1;
											$payment					= $payment+1 ;
											$flag_balance = 0;
											break;
									}
									if($due_amount==$manual_payment[$payment]->payment_amount){
										$previous_amount_pre 	    = $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										$balance_license_amount 	=  0;
										$last_payment_date          = NULL;
										$flag_payment  				= 'exhausted';
										$late_flag 					=1;
										break;
									}
								}
								lebel3: if($start_date==$manual_payment[$payment]->date_payment){
									
									if(!empty($last_payment_date)){
										if($start_date>$last_payment_date){
										if($due_license_amount>$balance_license_amount){
											$previous_amount_pre 	= $balance_license_amount;
											$due_license_amount 	= $due_license_amount-$balance_license_amount;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
										}if($due_license_amount<$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = $balance_license_amount-$due_license_amount;
											$previous_amount_pre 	= $balance_license_amount;
										}if($due_license_amount==$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
											$previous_amount_pre 	= $balance_license_amount;
										}

									}
										if($start_date<$last_payment_date){
											$previous_amount_pre = $balance_license_amount;
										}
									}
									
								
									if($application_date<=$cut_off_date ){
							 			$late_fees_pay 	= ($due_license_amount)*(25/100);
									 	$due_amount 		= $late_fees_pay+$due_license_amount;
										$balance_amount = $balance_license_amount;
										$late_flag = 1;
						 			}if($application_date>$cut_off_date ){

										 $late_fees_pay = ($due_license_amount)*(50/100);
									
										 $due_amount 	= $late_fees_pay+$due_license_amount;
										$balance_amount = $balance_license_amount;
										$late_flag = 1;
											
					 				}
									
									if($due_amount>$manual_payment[$payment]->payment_amount){
										 	$previous_amount_pre 	= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										 	$due_amount 			= $due_amount - $previous_amount_pre;
											$late_flag 				= 1;
											$payment				= $payment+1 ;
									 		goto lebel3;
									}
									if($due_amount<$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$balance_license_amount 	=  $manual_payment[$payment]->payment_amount-$due_amount ;

											$last_payment_date  		= $manual_payment[$payment]->date_payment ;
											$flag_payment  				= 'exhausted';
											$late_flag 					=1;
											break;
									}
									if($due_amount==$manual_payment[$payment]->payment_amount){
										$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										$balance_license_amount 	=  0;
										$last_payment_date 	 		= NULL ;
										$payment					= $payment+1 ;
										$flag_payment  		= 'exhausted';
										$late_flag =1;
										break;
									}
								}
								
							} 
					
							if($late_flag ==0  ){
								if($application_date<=$cut_off_date ){
							 		$late_fees_pay 	= ($due_license_amount)*(25/100);
									$due_amount 	= $late_fees_pay+$due_license_amount;
									$balance_amount = $balance_license_amount;
						 		}if($application_date>$cut_off_date ){
									$late_fees_pay 	= ($due_license_amount)*(50/100);
									$due_amount 	= $late_fees_pay+$due_license_amount;
									$balance_amount = $balance_license_amount;
											
					 			}
								if($balance_license_amount>$due_amount){//echo $due_amount.'----'.$balance_license_amount;
									$previous_amount_pre 	= $balance_license_amount;
									 $balance_amount 		= $previous_amount_pre-$due_amount;
									$due_amount 			= 0;
									 $balance_license_amount = $balance_amount;
								}if($balance_license_amount<$due_amount){
									$previous_amount_pre 	= $balance_license_amount;
									$due_amount 			= $due_amount-$balance_license_amount;
									$balance_amount 		= 0;
									$balance_license_amount = $balance_amount;
								}if($balance_license_amount==$due_amount){
									$previous_amount_pre 	= 0;
									$due_amount 			= 0;
									$balance_amount 		= 0;
									$balance_license_amount = $balance_amount;
								}
							
							}
							
							
							 
						 $balance_amount = $balance_license_amount;
						
							$due_amount_paid = $due_amount+$due_amount_paid;
						  }else{
							   $balance_amount_preservice = $balnce_amount;
						  }
							
						$calculate_fees_details = array(
			'feesyear' 		             => $schedule_fees['feesyear'],
			'schedule_fees' 		     => $license_fees,
			'late_fees'              	 => $late_fees,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $worker->application_period,
			'factory_type'				 => $factory_type_id,
			'application_reference_no'	 => $reference_no,
			'created_by'				 => $user->uid,
			'application_status'	     => 'N',
			'due_fees'    				 => $due_amount,
			'balance_amount'			 => $balance_amount,
			'previous_paid_fees'   	 	 => !empty($previous_amount_pre)?$previous_amount_pre:0,
			'max_worker'				 => $max_worker,
			'worker'					 => $worker->total_worker,
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $Registration_fees,
			
			
			
		);
					
	$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
		//print_r($calculate_fees_details);
						$late_fees_pay 			= 	0;
						$previous_amount_pre 	=	0;
						$due_amount 			= 	0;
						$late_flag 				=	0;
						$flag_payment 			=	'';
						$balance_amount =0;	
						$fees_to_paid = $due_amount_paid;
						$i++;
					}
				}
				
		}
						
 
	
	save_fees_registration_amand_2mii($application_id,$service_id,$factory_type_id,$reference_no,$last_validlicensedate);
	
	
}
function save_fees_registration_amand_2mii($application_id,$service_id,$factory_type_id,$reference_no,$last_validlicensedate){
	global $base_root, $base_path, $user;
	$previous_excess_paid =  $_SESSION['balance_renewal'];		 
	$amandment_fess=$amandment_fess1 = 1000;
	$sl = 1;
	$Registration_fees 					= 	0;
	$created_by 						=   $user->uid;
	$modifi_date 						=   date("Y-m-d",strtotime($date_of_amenability));
	
	$i									=	1;
	$license_fees 						= 	0;
	$late_fees							= 	0;
	$current_year 						= 	date("Y");
	$fees 								= 	0;
	$i									= 	1;  
	$total_license_fees  				= 	0;
	$total_transfer_fees 				= 	0;
	$flag_adjust_balance 				= 	0;
	$flag_late_calulate  				= 	0;
	
	$flag_payment  						= '';
	$payment							= 0;
	$late_flag = 0;
	$flag_balance = 0;
	$fees_to_paid =0;
	$due_flag = 0;
	$previous_amount_flag =0;
	$total_amand_fees =0;
	$previous_amount_pre =  $_SESSION['balance_renewal'];
		
			$amend_value = fun_worker_detials_amendnotice($application_id,$service_id,$factory_type_id,$reference_no);
			///print_r($amend_value);die();
			foreach($amend_value as $amand_row){	
					
					$Previous_Total_Worke 	= $amand_row->previous_worker;
					$Amendment_Worker		= $amand_row->worker_total;
					$amand_valid_year 		= $amand_row->valid_year;
					$valid_time_period		= $amand_row->valid_time_period;	
					$starting_year			= $amand_row->starting_year;
					$service_year			= $amand_row->service_year;	
					$last_validity			= date("Y-m-d",strtotime($amand_valid_year));
					$last_validity_year  	= date('Y',strtotime($amand_valid_year));
					$fees_previous 			= fees_calculation_registration_2mii($starting_year,$Previous_Total_Worke);
					$fees_previous_paid 	= ($fees_previous['fees']*$valid_time_period)+$previous_excess_paid;
					if($last_validity == '2018-12-31'){
				  			$application_date 		= date('Y-m-d');
							if(!empty($fees_previous_paid)){
							   $result_data  = fees_calculation_registration_2mii($starting_year,$Amendment_Worker);
						       $license_fees=$license_fees_1 = $result_data['fees']*$amand_valid_time_period;
						       $license_start_date = $starting_year;
						  if($license_start_date=='2019-01-01'){
							    	 $datey_cuttoff 		= '2019-01-15'; 
						}else{
							 		
									 	$year  			= date('Y',strtotime($license_start_date));
									  	$month 			= date('m',strtotime($license_start_date));
									   	$day  			= date('d',strtotime($license_start_date));
							 			$from_unix_time = mktime(0, 0, 0, $month, $day, $year);
										$day_before 	= strtotime("yesterday", $from_unix_time);
										$datey_cuttoff 	= date('Y-m-d', $day_before);
									
								
						}
						
							
				 
				  if($application_date < $datey_cuttoff){
						 $late_fees_pay = 0;
						 if($license_fees>$fees_previous_paid){
							  $due_amount 	=(($license_fees-$fees_previous_paid));
						 } else{
							 $due_amount 	=(($fees_previous_paid-$license_fees));
						 }
						
					}
					
				  if($application_date >= $datey_cuttoff){
										
				 if($amand_starting_year < $application_date){
										$start_date				= date_create($amand_starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
										$days_differ_app  		= $diff->days; 
							}if($amand_starting_year < $datey_cuttoff){
										$start_date				= date_create($amand_starting_year);
										$datey_cuttoff1			= date_create($datey_cuttoff);
										$diff					= date_diff($datey_cuttoff1,$start_date);
										$days_differ_cutt 		= $diff->days;
							}if($days_differ_app>$days_differ_cutt){
										$big_diff = $days_differ_app;
							}else{
									    $big_diff = $days_differ_cutt;
							}
							if($amand_starting_year > $application_date){
										$start_date		= date_create($amand_starting_year);
										$application_date1		= date_create($application_date);
										
										$diff			= date_diff($start_date,$application_date1);
										$big_diff  		= $diff->days;
										
								
								}
										
								if($big_diff>=1 && $big_diff<=90){
									 $late_fees_pay = ($result_data['fees'])*(50/100);
													
							}if($big_diff>91){
									 $late_fees_pay = $result_data['fees'];
							}
							//echo $late_fees_pay;
							$payble_fees = $license_fees+$late_fees_pay;
							 if($fees_previous_paid>$payble_fees){
							//$late_fees_pay 		= $;
							$balance_amount  	= $fees_previous_paid-$payble_fees;
							$due_amount 		= 0;
						
					}
					if($fees_previous_paid<$payble_fees){
								$due_amount  		= $payble_fees-$fees_previous_paid;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
							//	$late_fees_pay 		= $late_fees_pay;
							
					}
					if($fees_previous_paid == $payble_fees){
								$due_amount  		= 0;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								//$late_fees_pay 		= 0;
							
					}			
									
										
							}
						
							
									
				}
					
				$output.='<tr>
						<td>'.$sl.'</td>
		             	<td>'.$amand_year.'</td>
						<td>'.$amandment_fess.'</td>
						
						<td>'.$previous_worker.'</td>	
						<td>'.$fees_previous_paid.'</td>
						
						<td>'.$due_amount.'</td>
						
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';
					
		$output.='</tr>';
		$sl++;		
		$fees_previous_paid 	= $balance_amount;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;			
					 
				
				 
		 }
				 					
					if($last_validity_year > '2018'){
				           		
							 $result_data  = fees_calculation_registration_2mii($starting_year,$Amendment_Worker);
							 //print_r($result_data);die();
						   $license_fees=$license_fees_1 = $result_data['fees']*$valid_time_period;
					  	    $license_start_date 	= $starting_year;
							$application_date1		= date_create($application_date);
							$late_fees 				= 0;
							if($amand_starting_year < $application_date){ //echo 'hi';
									$start_date				= date_create($amand_starting_year);
									$application_date1		= date_create($application_date);
									$diff					= date_diff($start_date,$application_date1);
									$big_diff  				= $diff->days;

							}
					
							if($big_diff>=1 && $big_diff<=90){
									$late_fees_pay = ($license_fees)*(50/100);
													
							}if($big_diff>91){
									$late_fees_pay = $license_fees;
							}
					
				//echo $late_fees_pay;die();
					$payble_fees = $license_fees+$late_fees_pay+$amandment_fess;
					if($fees_previous_paid>$payble_fees){
							//$late_fees_pay 		= $;
							$balance_amount  	= $fees_previous_paid-$payble_fees;
							$due_amount 		= 0;
						
					}
					if($fees_previous_paid<$payble_fees){
								$due_amount  		= $payble_fees-$fees_previous_paid;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
							//	$late_fees_pay 		= $late_fees_pay;
							
					}
					if($fees_previous_paid == $payble_fees){
								$due_amount  		= 0;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								//$late_fees_pay 		= 0;
							
					}			
						
					
			  if($result_data['workers_end_to'] == -1){
			$max_worker = $Previous_Total_Worke." and onwords";
		}else{
			$max_worker = $result_data['workers_end_to'];
		}
				
			
		$calculate_fees_details = array(
			'feesyear' 		             => $result_data['feesyear'],
			'schedule_fees' 		     => $license_fees,
			'late_fees'              	 => $late_fees,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $amand_row->service_year,
			'factory_type'				 => $factory_type_id,
			'application_reference_no'	 => $reference_no,
			'created_by'				 => $user->uid,
			'application_status'	     => 'N',
			'due_fees'    				 => $due_amount,
			'balance_amount'			 => $balance_amount,
			'previous_paid_fees'   	 	 => !empty($previous_amount_pre)?$previous_amount_pre:0,
			'max_worker'				 => $max_worker,
			'worker'					 => $amand_row->worker_total,
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $amandment_fess,
			'remark'					 => 'Amendment',
			
			
			
		);
		
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
		//print_r($calculate_fees_details);
		
		$previous_excess_paid = $balance_amount;		
			
	}	  
	  
					if($last_validity_year <= '2015'){
						
							 $result_data  = fees_calculation_registration_2mii($starting_year,$Amendment_Worker);
						   $license_fees=$license_fees_1 = $result_data['fees']*$valid_time_period;
					  	    $license_start_date 	= $starting_year;
							$application_date1		= date_create($application_date);
							$late_fees 				= 0;
							if($amand_starting_year < $application_date){ //echo 'hi';
									$start_date		= date_create($amand_starting_year);
									$application_date1		= date_create($application_date);
										
										$diff			= date_diff($start_date,$application_date1);
										$big_diff  		= $diff->days;
										
										
							}
							
							if($fees_previous_paid>$license_fees){
								$late_fees_pay = 0;
								$balance_amount = $fees_previous_paid-$payblefess;
								$due_amoun = 0;
							}
							if($fees_previous_paid<$license_fees){
								$late_fees = $fees_previous_paid-$license_fees;
								
								if($big_diff>=1 && $big_diff<=90){
									$late_fees_pay = ($late_fees)*(25/100);
								$due_amoun = $late_fees+$late_fees_pay;
								$balance_amount=0;					
							}if($big_diff>91){
								
									$late_fees_pay = ($late_fees)*(50/100);
								$due_amoun = $late_fees+$late_fees_pay;
								$balance_amount=0;
									
							}
								
								
							}if($fees_previous_paid==$license_fees){
								
								if($big_diff>=1 && $big_diff<=90){
									$late_fees = ($result_data['fees']*$fees_late_year)*(25/100);
													
							}if($big_diff>91){
									$late_fees = ($result_data['fees']*$fees_late_year)*(50/100);
							}
								
								
								$late_pay = 0;
								$balance_amount = 0;
								$due_amoun = $license_fees-$fees_previous_paid;
							}
							
					
							
					
				
							
			
				$output.='<tr>
						<td>'.$sl.'</td>
		             	<td>'.$amand_year.'</td>
						<td>'.$amandment_fess.'</td>
						<td>'.$previous_power.'('.$previous_power_unit.')</td>
						<td>'.$previous_worker.'</td>	
						<td>'.$fees_previous_paid.'</td>
						<td>'.$present_power.'('.$present_installed_power_unit.')</td>
						<td>'.$present_totalworker.'</td>
						<td>'.$payblefess.'</td>
						
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';
					
		$output.='</tr>';
		$sl++;		
				}
				           		
				$amandment_fess=0;
				$total_amand_fees = $total_amand_fees+$due_amount;		
			
			
			 
			   
	}
				
	
		if(empty($previous_excess_paid) || $previous_excess_paid==NULL || $previous_excess_paid==0){
	
	$fees_deatils = array('service_fees'=>$amandment_fess1,'payment_amount'=>$_SESSION['renewal_fees'],'is_previous_payment'=>'No','balance_amount'=>$balance_amount,'is_notesheet_amount'=> 0,'application_status'=>'P');
}
else{
	$fees_deatils = array('service_fees'=>$amandment_fess1,'previous_excess_paid'=>$_SESSION['balance_renewal'],'payment_amount'=>$_SESSION['renewal_fees'],'is_previous_payment'=>'Yes','balance_amount'=> $balance_amount,'is_notesheet_amount'=> 0,'application_status'=>'P');
}
				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		->	fields($fees_deatils);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc		->	execute();
	//print_r($fees_deatils);die();			
remark_input($reference_number,$application_id,'P','Payment process is sucessfully completed')	;	
	fun_grip_input($fees_to_paid,$application_id,$service_id,$reference_number,$factory_typeid);
	drupal_goto('applicant/view-payment-breakup/' .encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_no));
   
   
}


function save_fees_registration_85($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid,$last_validlicensedate){
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

$power_details			= yearly_power_worker_details($application_id,$factory_type_id,$service_id,$reference_no);


$total_transfer_fees 	= 0;
$date 					= date_create($last_validlicensedate);
$date_convert 			= date_format($date, "Y");
$date_convert1 			= date_format($date, "Y-m-d");	
$application_date 		= date('Y-m-d');	
$application_date1 		= date_create($application_date);			


foreach($power_details as $rows){
	$installed_power 	=   $rows->installed_power;
	$worker_total 		=   $rows->worker_total;
	
	
}
	
$remark					=  'Section-85'	;
$previous_amount_pre 	= 0;
$manual_payment_amount 	= 0;
if($date_convert1 == '2018-12-31'){
	$max_payment_date 		= get_max_payment_date($application_id,$service_id,$factory_type_id,$reference_no);
	$max_payment_date		=	get_max_payment_date($application_id,$service_id,$factory_type_id,$reference_no);
	foreach($power_details as $rows){
	if(empty($max_payment_date)){
		$license_start_date = $rows->calculate_starting_year;	
		if($license_start_date=='2019-01-01'){
						$datey_cuttoff 		= '2019-01-15'; 
		}
		else{
							 		
					
					$license_start_date  	= date_create($license_start_date);
					$year 					= date_format($license_start_date, "Y");
					$month 					= date_format($license_start_date, "m");
					$day 					= date_format($license_start_date, "d");
					$from_unix_time 		= mktime(0, 0, 0, $month, $day, $year);
					$day_before 			= strtotime("yesterday", $from_unix_time);
					 $datey_cuttoff 			= date('Y-m-d', $day_before);
									
								
					}
				   $fees_fetach 		=	fees_calculation_registration_section_85($rows->calculate_starting_year);
				   $license_fees 		=  $fees_fetach['fees']*$rows->valid_time_period;
				    $unit 		 		= $rows->power_unit;
					$power_hp_kw  		= $rows->installed_power_hp;
				 	$installed_power  	= $rows->installed_power;
				   if($rows->calculate_starting_year <= $application_date){
					   	$start_date				= date_create($rows->calculate_starting_year);
						$diff					= date_diff($application_date1,$start_date);
						$days_differ_app  		= $diff->days; 
						
				   } if($rows->calculate_starting_year <=$datey_cuttoff){
						   $start_date				= date_create($rows->calculate_starting_year);
						   $datey_cuttoff1			= date_create($datey_cuttoff);
						   $diff					= date_diff($datey_cuttoff1,$start_date);
						   $days_differ_cutt 		= $diff->days;
				}if($days_differ_app>$days_differ_cutt){
							$big_diff = $days_differ_app;
				}else{
							$big_diff = $days_differ_cutt;
				}
				if($rows->calculate_starting_year > $application_date){ 
							$big_diff = 0;
				}
				
				if($big_diff>=1 && $big_diff<=90){
							$late_fees = ($license_fees)*(50/100);
													
				}if($big_diff>91){
							$late_fees = $license_fees;
				}else{
					$late_fees = 0;
				}
				$payble_fees 	= $license_fees+$late_fees;
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
							
			if(empty($previous_amount_pre)){
					$previous_amount_pre = 0;
	}
													
					if($fees_fetach['workers_end_to'] == -1){
		$max_worker = $rows->worker_total." and onwords";
	}else{
		$max_worker = $rows->worker_total;
	}if($result_data['power_range_end_hp'] == -1){
		$max_power = $rows->installed_power." and onwords";
	}else{
		$max_power = $rows->installed_power;
	}
	$calculate_fees_details = array(
			'feesyear' 		             => $fees_fetach['feesyear'],
			'schedule_fees' 		     => $license_fees,
			'late_fees'              	 => $late_fees_pay,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $rows->calculate_year,
			'factory_type'				 => $factory_type,
			'application_reference_no'	 => $reference_no,
			'created_by'				 => $user->uid,
			'application_status'	     => 'N',
			'due_fees'    				 => $due_amount,
			'balance_amount'			 => $balance_amount,
			'previous_paid_fees'   	 	 => !empty($previous_amount_pre)?$previous_amount_pre:0,
			'max_worker'				 => $max_worker,
			'max_power'					 => $max_power.'('.$unit.')',
			'worker'					 => $rows->worker_total,
			'power'					 	 => $rows->installed_power_hp.'('.$unit.')',
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $Registration_fees,
			
			
			
		);


	
		
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$late_fees 			=0;
		$late_fees_pay = 0;	
		$days_differ_cutt = 0;
		$previous_amount_pre 	= $balance_amount;
			}
	}
	if(!empty($max_payment_date)){
		$manual_payment				=  manual_payment_deatils($application_id,$service_id,$factory_type_id,$reference_no);
		$manual_payment_count 		=  count($manual_payment); 
		$payment			  		= 0;
		foreach($power_details as $rows){
				 $fees_fetach 		=	fees_calculation_registration_section_85($rows->calculate_starting_year);
				$license_fees=$license_fees_1 = $fees_fetach['fees']*$rows->valid_time_period;
				$unit 		 		= $rows->power_unit;
				$power_hp_kw  		= $rows->installed_power_hp;
				$installed_power  	= $rows->installed_power;
				if($previous_amount_pre>$license_fees_1){
					  $license_fees_1 = 0;
					  $balnce_amount = $previous_amount_pre-$license_fees_1;
					  $due_amount = 0;
					  $late_fees_pay = 0;
				}if($previous_amount_pre<$license_fees_1){
					  $balnce_amount = 0;
					  $license_fees_1 = $license_fees_1-$previous_amount_pre;
					  $due_amount = 0;
				}if($previous_amount_pre==$license_fees_1){
					  $balance_amount = 0;
					  $license_fees_1 = 0;
					  $due_amount = 0;
					  $late_fees_pay = 0;
				}if($license_fees_1>0){ 
					   $license_start_date = $rows->calculate_starting_year;
				
					if($license_start_date=='2019-01-01'){
						$datey_cuttoff 		= '2019-01-15'; 
						}
					else{
							 		
					
					$license_start_date  	= date_create($license_start_date);
					$year 					= date_format($license_start_date, "Y");
					$month 					= date_format($license_start_date, "m");
					$day 					= date_format($license_start_date, "d");
					$from_unix_time 		= mktime(0, 0, 0, $month, $day, $year);
					$day_before 			= strtotime("yesterday", $from_unix_time);
					 $datey_cuttoff 			= date('Y-m-d', $day_before);
									
								
					}
						
						while(($payment < $manual_payment_count)&& ($flag_payment!= 'exhausted')){
							if($rows->calculate_starting_year > $manual_payment[$payment]->date_payment){
								 $previous_amount_pre = $previous_amount_pre+$manual_payment[$payment]->payment_amount;
							     if($license_fees_1 == $manual_payment[$payment]->payment_amount){
									 	$flag_payment = 'exhausted';
									  	$due_flag = 0;
								}if($license_fees_1 > $manual_payment[$payment]->payment_amount){
										 $due_amount_pre = ($license_fees_1-$manual_payment[$payment]->payment_amount);
									 	 $license_fees_1 = $due_amount_pre;
									 	$due_flag = 1;
								}if($license_fees < $manual_payment[$payment]->payment_amount){
									 $balance_amount = ($manual_payment[$payment]->payment_amount-$license_fees_1);
									 $due_flag = 0;
								}
							 }
						if($rows->calculate_starting_year <=$manual_payment[$payment]->date_payment){
								 $previous_amount_pre = $previous_amount_pre+$manual_payment[$payment]->payment_amount;
							}
						 	$payment++;
						 
						
						
						}
			 
				 if($application_date < $datey_cuttoff){
						 $late_fees_pay = 0;
						$due_amount 	= $license_fees+$late_fees_pay;
					}if($application_date >= $datey_cuttoff){ 
										
							if($rows->calculate_starting_year < $application_date){
										$start_date				= date_create($rows->calculate_starting_year);
										$diff					= date_diff($application_date1,$start_date);
										$days_differ_app  		= $diff->days; 
							}if($rows->calculate_starting_year < $datey_cuttoff){
										$start_date				= date_create($rows->calculate_starting_year);
										$datey_cuttoff1			= date_create($datey_cuttoff);
										$diff					= date_diff($datey_cuttoff1,$start_date);
										$days_differ_cutt 		= $diff->days;
							}if($days_differ_app>$days_differ_cutt){
										$big_diff = $days_differ_app;
							}else{
									    $big_diff = $days_differ_cutt;
							}
							if($rows->calculate_starting_year > $application_date){
										$start_date		= date_create($rows->calculate_starting_year);
										$application_date1		= date_create($application_date);
										
										$diff			= date_diff($start_date,$application_date1);
										$big_diff  		= $diff->days;
							}
						
							if($due_flag ==1){
								$license_fees_late = $due_amount_pre;
							}else{
								$license_fees_late = $license_fees;
							}
							
							if($big_diff>=1 && $big_diff<=90){
									$late_fees_pay = ($license_fees_late)*(50/100);
													
							}if($big_diff>91){
									$late_fees_pay = $license_fees_late;
							}
							
							$due_amount 	= $license_fees+$late_fees_pay;
							
							
						
							
							if($previous_amount_pre>$due_amount){
									
									$balance_amount  	= $previous_amount_pre-$due_amount;
									$due_amount 		= 0;
							}
							if($previous_amount_pre<$due_amount){
									$due_amount  		= $due_amount-$previous_amount_pre;
									$previous_amount 	= 0 ;
									$balance_amount 	= 0;
									

							}
							if($previous_amount_pre == $due_amount){
									$due_amount  		= 0;
									$previous_amount 	= 0 ;
									$balance_amount 	= 0;
									
							}
									
						
									
				}
					 }else{
							  $due_amount = $license_fees;
							  
							  if($previous_amount_pre>$due_amount){
									
									$balance_amount  	= $previous_amount_pre-$due_amount;
									$due_amount 		= 0;
							}
							if($previous_amount_pre<$due_amount){
									$due_amount  		= $due_amount-$previous_amount_pre;
									$previous_amount 	= 0 ;
									$balance_amount 	= 0;
									

							}
							if($previous_amount_pre == $due_amount){
									$due_amount  		= 0;
									$previous_amount 	= 0 ;
									$balance_amount 	= 0;
									
							}
						  }
						
			if(empty($previous_amount_pre)){
					$previous_amount_pre = 0;
	}
	if($fees_fetach['workers_end_to'] == -1){
		$max_worker = $rows->worker_total." and onwords";
	}else{
		$max_worker = $rows->worker_total;
	}if($fees_fetach['power_range_end_hp'] == -1){
		$max_power = $rows->installed_power." and onwords";
	}else{
		$max_power = $rows->installed_power;
	}
	$calculate_fees_details = array(
			'feesyear' 		             => $fees_fetach['feesyear'],
			'schedule_fees' 		     => $license_fees,
			'late_fees'              	 => $late_fees_pay,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $rows->calculate_year,
			'factory_type'				 => $factory_type_id,
			'application_reference_no'	 => $reference_no,
			'created_by'				 => $user->uid,
			'application_status'	     => 'N',
			'due_fees'    				 => $due_amount,
			'balance_amount'			 => $balance_amount,
			'previous_paid_fees'   	 	 => !empty($previous_amount_pre)?$previous_amount_pre:0,
			'max_worker'				 => $max_worker,
			'max_power'					 => $max_power.'('.$unit.')',
			'worker'					 => $rows->worker_total,
			'power'					 	 => $rows->installed_power.'('.$unit.')',
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $Registration_fees,
			
			
			
		);
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
		
		
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$late_fees 			=0;
		$late_fees_pay = 0;
		$due_flag =0;
		$previous_amount_pre 	= $balance_amount;
					 
				
		}
				 }
			
			
		
					
	
		
	}
if($date_convert <= '2015'){ 
		$max_payment_date			=		get_max_payment_date($application_id,$service_id,$factory_type_id,$reference_no);
		$payment					= 		0;
		if(empty($max_payment_date)){
					
					foreach($power_details as $rows){
						
							$start_date 		= $rows->calculate_starting_year;
							$cut_off_date_year  = date('Y',strtotime($start_date));
						 	$cut_off_date 		= $cut_off_date_year.'-03-31';
							$power_hp_kw  		= $rows->installed_power_hp;
							$installed_power  	= $rows->installed_power;
							$fees_fetach 		=	fees_calculation_registration_section_85($rows->calculate_starting_year);
							$license_fees 		= $fees_fetach['fees']*$rows->valid_time_period;
							$unit 		 		= $rows->power_unit;
							
							$cut_off_date1 = date_create($cut_off_date);
							
					 		if($application_date<$cut_off_date ){
								
								
								$diff			= date_diff($application_date1,$cut_off_date1);
								$big_diff  		= $diff->days;
								$late_year 		= $diff->year;
								 $late_year = $diff->y;
								$late_month = $diff->m;
								$late_day = $diff->d ;
								if($rows->valid_time_period>1){
											if($late_year>0){
											$fees_late_year = $late_year;
											if($late_month>0){
												$fees_late_year = $late_year+1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = $late_year+1;
											}
											$late_fees_pay = $fees_fetach['fees']*$fees_late_year; 
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 $late_fees_pay = $fees_fetach['fees']*$fees_late_year;
										}
									$late_fees = ($late_fees_pay)*(25/100);
							}else{
								$late_fees = ($license_fees)*(25/100);
							}
						 
					 		}if($application_date>$cut_off_date ){
								
								$diff			= date_diff($application_date1,$cut_off_date1);
								
								$big_diff  		= $diff->days;
								$late_year 		= $diff->year;
								 $late_year = $diff->y;
								$late_month = $diff->m;
								$late_day = $diff->d ;
								if($rows->valid_time_period>1){
											if($late_year>0){
											$fees_late_year = $late_year;
											if($late_month>0){
												$fees_late_year = $late_year+1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = $late_year+1;
											}
											$late_fees_pay = $fees_fetach['fees']*$fees_late_year; 
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 $late_fees_pay = $fees_fetach['fees']*$fees_late_year;
										}
									$late_fees = ($late_fees_pay)*(50/100);
							}else{
								$late_fees = ($license_fees)*(50/100);
							}
						 
					 		
						 
					 		}
							if($application_date==$cut_off_date ){
								$late_fees = ($fees_fetach['fees'])*(25/100);
								
								
							}
							$late_fees_pay 	= $late_fees;
							$due_amount 	= $license_fees+$late_fees_pay;
							$balance_amount = 0;
							$previous_amount_pre = !empty($previous_amount_pre)?$previous_amount_pre:0;
						if(empty($previous_amount_pre)){
					$previous_amount_pre = 0;
		}
		if($fees_fetach['workers_end_to'] == -1){
			$max_worker = $rows->worker_total." and onwords";
		}else{
			$max_worker = $rows->worker_total;
		}if($fees_fetach['power_range_end_hp'] == -1){
			$max_power = $rows->installed_power_hp." and onwords";
		}else{
			$max_power = $rows->installed_power;
		}
	$calculate_fees_details = array(
			'feesyear' 		             => $fees_fetach['feesyear'],
			'schedule_fees' 		     => $license_fees,
			'late_fees'              	 => $late_fees_pay,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $rows->calculate_year,
			'factory_type'				 => $factory_type_id,
			'application_reference_no'	 => $reference_no,
			'created_by'				 => $user->uid,
			'application_status'	     => 'N',
			'due_fees'    				 => $due_amount,
			'balance_amount'			 => $balance_amount,
			'previous_paid_fees'   	 	 => !empty($previous_amount_pre)?$previous_amount_pre:0,
			'max_worker'				 => $max_worker,
			'max_power'					 => $max_power.'('.$unit.')',
			'worker'					 => $rows->worker_total,
			'power'					 	 => $rows->installed_power.'('.$unit.')',
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $Registration_fees,
			
			
			
		);
		//print_r($calculate_fees_details);
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();	
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$Registration_fees 		=0;
		
	  	
	 
	   	$i= $i+1;
					}
					
				}
		if(!empty($max_payment_date)){
					$application_date 		= date('Y-m-d');
					$manual_payment			=  manual_payment_deatils($application_id,$service_id,$factory_type_id,$reference_no);
					 $manual_payment_count 	=  count($manual_payment);
					
					foreach($power_details as $rows){
						
							
							$application_date 	= date('Y-m-d');
							$start_date 		= $rows->calculate_starting_year;
							$cut_off_date_year  = date('Y',strtotime($start_date));
						 	$cut_off_date 		= $cut_off_date_year.'-03-31';
							$power_hp_kw  		= $rows->installed_power_hp;
							$installed_power  	= $rows->installed_power;
							$result_data 		=	fees_calculation_registration_section_85($rows->calculate_starting_year);
							//print_r($result_data);die;
							$license_fees 		= $result_data['fees']*$rows->valid_time_period;
							$unit 		 		= $rows->power_unit;
							$due_license_amount = $license_fees; 
							 if($previous_amount_pre>$due_license_amount){
							  		$due_license_amount 		= 0;
							  		$balnce_amount 				= $previous_amount_pre-$due_license_amount;
							 		$due_amount 				= 0;
							  		$late_fees_pay 				= 0;
						  }if($previous_amount_pre<$due_license_amount){
							 		$balnce_amount 				= 0;
							 		$due_license_amount 		= $due_license_amount-$previous_amount_pre;
							  		$due_amount 				= 0;
						  }if($previous_amount_pre==$due_license_amount){
							  		$balance_amount 			= 0;
							  		$due_license_amount 		= 0;
							  		$due_amount 				= 0;
							  		$late_fees_pay 				= 0;
						  }if($due_license_amount>0){
							  while($payment < $manual_payment_count) {
								  
								  		  
								lebel1: if(($start_date>$manual_payment[$payment]->date_payment)&& !empty($manual_payment[$payment]->date_payment)){
											if(!empty($last_payment_date)){
												if($start_date>$last_payment_date){
													if($due_license_amount>$balance_license_amount){
																$previous_amount_pre = $balance_license_amount;
																$due_license_amount 	= $due_license_amount-$balance_license_amount;
																$balance_license_amount = 0;
																$last_payment_date 		= NULL;
													}
													if($due_license_amount<$balance_license_amount){
														$balance_license_amount1 = $balance_license_amount;
																$balance_license_amount =$balance_license_amount2= $balance_license_amount-$due_license_amount;
																$due_license_amount 	= 0;
																$previous_amount_pre = $balance_license_amount1;
																
													}if($due_license_amount==$balance_license_amount){
																$due_license_amount 	= 0;
																$balance_license_amount = 0;
																$last_payment_date 		= NULL;
																$previous_amount_pre = $balance_license_amount;
													}
										}
												if($start_date<$last_payment_date){
												$previous_amount_pre = $balance_license_amount;
										}
									}
								
								if($due_license_amount>$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 	= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$due_license_amount 	= $due_license_amount - $manual_payment[$payment]->payment_amount;
											$payment				= $payment+1 ;
											$flag_payment 			= 'due';
									 		goto lebel1;
								}
								if($due_license_amount<$manual_payment[$payment]->payment_amount){
										$previous_amount_pre 	= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										 $balance_license_amount 	=  $manual_payment[$payment]->payment_amount-$due_license_amount ;
											
											 if($due_license_amount==0){
												  $balance_license_amount = $balance_license_amount2+$manual_payment[$payment]->payment_amount;
											 }
											
											
											$last_payment_date  		= $manual_payment[$payment]->date_payment ;
											$payment					= $payment+1 ;
											$flag_payment  				= 'exhausted';
											$due_amount 				= 	0;
											$late_fees_pay 	 			=	0;
																	
											$manual_payment_date 		=  NULL;
											if(!empty($balance_license_amount) || $balance_license_amount != NULL || $balance_license_amount!=0){
												 $late_flag 					=	1;
												$balance_amount 			= 	$balance_license_amount;
												
												break;
											}else{
												$late_flag 					=	0;
												break;
											}
											
								}
								if($due_license_amount==$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$balance_license_amount 	= 0;
											$last_payment_date  		= NULL;
											$payment					= $payment+1 ;
											$flag_payment  				= 'exhausted';
											$due_amount 				= 0;
											$late_fees_pay 	 			= 0;
											$late_flag 					= 1;
											$balance_amount 			= $balance_license_amount;
											$manual_payment_date 		=  NULL;
											break;
								}
								if($due_license_amount !=0 ||empty($due_license_amount) ){
									if($application_date<=$cut_off_date ){
							 				$late_fees_pay 		= ($due_license_amount)*(25/100);
									 		$due_amount 		= $late_fees_pay+$license_fees;
											$balance_amount 	= $balance_license_amount;
											$late_flag 			=1;
						 			}if($application_date>$cut_off_date ){
										 	$late_fees_pay 		= ($due_license_amount)*(50/100);
										 	$due_amount 		= $late_fees_pay+$license_fees;
											$balance_amount 	= $balance_license_amount;
											$late_flag 			=1;
											
					 				}
								}
								
							}
							    lebel2: if($start_date<$manual_payment[$payment]->date_payment){					
									if(!empty($last_payment_date)){
										if($start_date>$last_payment_date){
										if($due_license_amount>$balance_license_amount){
											$previous_amount_pre 	= $balance_license_amount;
											$due_license_amount 	= $due_license_amount-$balance_license_amount;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
										}
										if($due_license_amount<$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = $balance_license_amount-$due_license_amount;
											$previous_amount_pre = $balance_license_amount;
										}if($due_license_amount==$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
											$previous_amount_pre = $balance_license_amount;

										}
									}
										if($start_date<$last_payment_date){
										if($balance_license_amount != 0){
											$previous_amount_pre = $balance_license_amount;
											$flag_balance = 1;
										}
											
											
											
										}
									}
									
									if($late_flag == 0 || empty($late_flag)){
										if($manual_payment[$payment]->date_payment<=$cut_off_date ){
							 			$late_fees_pay 	= ($due_license_amount)*(25/100);
									 	$due_amount 	= $late_fees_pay+$due_license_amount;
										$balance_amount = $balance_license_amount;
										$late_flag = 1;
						 			}if($manual_payment[$payment]->date_payment>$cut_off_date ){
										  $late_fees_pay 	= ($due_license_amount)*(50/100);
										  $due_amount 			= $late_fees_pay+$due_license_amount;
										  $balance_amount 		= $balance_license_amount;
										 $late_flag 			= 1;
									
											
					 				}
								}
									
									
									if($due_amount>$manual_payment[$payment]->payment_amount){
										
										if($flag_balance == 1){
												 $previous_amount_pre 	=  $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												
											  	 $due_amount 			=  $due_amount-$previous_amount_pre ;
												$flag_balance = 0;
												
											}else{
												 $previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												 $due_amount 	= $due_amount - $manual_payment[$payment]->payment_amount;
											
											}
											
										
										
										$late_flag =1;
										$balance_license_amount = 0;
										$payment	= $payment+1 ;
										$flag_balance =0;
									 	goto lebel2;
									}
									if($due_amount<$manual_payment[$payment]->payment_amount){
										 												
											if($flag_balance == 1){
												$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												 $balance_license_amount 	=  $previous_amount_pre-$due_amount ;
											}else{
												$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
												 $balance_license_amount 	=  $manual_payment[$payment]->payment_amount-$due_amount ;
											}
											
											
										 	$last_payment_date  		= $manual_payment[$payment]->date_payment ;
											$due_amount 				= 0;
											$flag_payment  				= 'exhausted';
											$late_flag 					= 1;
											$payment					= $payment+1 ;
											$flag_balance = 0;
											break;
									}
									if($due_amount==$manual_payment[$payment]->payment_amount){
										$previous_amount_pre 	    = $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										$balance_license_amount 	=  0;
										$last_payment_date          = NULL;
										$flag_payment  				= 'exhausted';
										$late_flag 					=1;
										break;
									}
								}
								lebel3: if($start_date==$manual_payment[$payment]->date_payment){	
									
									if(!empty($last_payment_date)){
										if($start_date>$last_payment_date){
										if($due_license_amount>$balance_license_amount){
											$previous_amount_pre 	= $balance_license_amount;
											$due_license_amount 	= $due_license_amount-$balance_license_amount;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
										}if($due_license_amount<$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = $balance_license_amount-$due_license_amount;
											$previous_amount_pre 	= $balance_license_amount;
										}if($due_license_amount==$balance_license_amount){
											$due_license_amount 	= 0;
											$balance_license_amount = 0;
											$last_payment_date 		= NULL;
											$previous_amount_pre 	= $balance_license_amount;
										}
									}
										if($start_date<$last_payment_date){
											$previous_amount_pre = $balance_license_amount;
										}
									}
									
								
									if($application_date<=$cut_off_date ){
							 			$late_fees_pay 	= ($due_license_amount)*(25/100);
									 	$due_amount 		= $late_fees_pay+$due_license_amount;
										$balance_amount = $balance_license_amount;
										$late_flag = 1;
						 			}if($application_date>$cut_off_date ){
										 $late_fees_pay = ($due_license_amount)*(50/100);
										
										 $due_amount 	= $late_fees_pay+$due_license_amount;
										$balance_amount = $balance_license_amount;
										$late_flag = 1;
											
					 				}
									
									if($due_amount>$manual_payment[$payment]->payment_amount){
										 	$previous_amount_pre 	= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										 	$due_amount 			= $due_amount - $previous_amount_pre;
											$late_flag 				= 1;
											$payment				= $payment+1 ;
									 		goto lebel3;
									}
									if($due_amount<$manual_payment[$payment]->payment_amount){
											$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
											$balance_license_amount 	=  $manual_payment[$payment]->payment_amount-$due_amount ;

											$last_payment_date  		= $manual_payment[$payment]->date_payment ;
											$flag_payment  				= 'exhausted';
											$late_flag 					=1;
											break;
									}
									if($due_amount==$manual_payment[$payment]->payment_amount){
										$previous_amount_pre 		= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										$balance_license_amount 	=  0;
										$last_payment_date 	 		= NULL ;
										$payment					= $payment+1 ;
										$flag_payment  		= 'exhausted';
										$late_flag =1;
										break;
									}
								}
						
							} 
			
							if($late_flag ==0  ){
								
								
							
							
								if($last_payment_date!=NULL || !empty($last_payment_date)){
									
								if($balance_license_amount>$due_license_amount){
									$previous_amount_pre 	= $balance_license_amount;
									 $balance_amount 		= $previous_amount_pre-$due_license_amount;
									$due_amount 			= 0;
									 $balance_license_amount = $balance_amount;
								}if($balance_license_amount<$due_license_amount){
									$previous_amount_pre 	= $balance_license_amount;
									$due_amount 	= $due_amount-$balance_license_amount;
									$balance_amount 		= 0;
									$last_payment_date		= NULL;
									$balance_license_amount = $balance_amount;
									
									if($last_payment_date<=$cut_off_date ){
							 			$late_fees_pay 	= ($due_amount)*(25/100);
										$due_amount 	= $late_fees_pay+$due_amount;
										$balance_amount = $balance_license_amount;
						 			}if($last_payment_date>$cut_off_date ){echo 88;
										$late_fees_pay 	= ($due_amount)*(50/100);
										$due_amount 	= $late_fees_pay+$due_amount;
										$balance_amount = $balance_license_amount;
											
					 				}
								
									
								}if($balance_license_amount==$due_license_amount){
									$previous_amount_pre 	= 0;
									$due_amount 			= 0;
									$balance_amount 		= 0;
									$balance_license_amount = $balance_amount;
								}
									
								}
							
							}
							 $balance_amount = $balance_license_amount;
						
							$due_amount_paid = $due_amount+$due_amount_paid;
						  }else{
							  $previous_amount_pre = $balnce_amount;
						  }
							
							
							
							 
						
	if(empty($previous_amount_pre)){
					$previous_amount_pre = 0;
		}
		if($result_data['workers_end_to'] == -1){
			$max_worker = $rows->worker_total." and onwords";
		}else{
			$max_worker = $rows->worker_total;
		}if($result_data['power_range_end_hp'] == -1){
			$max_power = $rows->installed_power_hp." and onwords";
		}else{
			$max_power = $rows->installed_power;
		}
	$calculate_fees_details = array(
			'feesyear' 		             => $result_data['feesyear'],
			'schedule_fees' 		     => $license_fees,
			'late_fees'              	 => $late_fees_pay,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $rows->calculate_year,
			'factory_type'				 => $factory_type_id,
			'application_reference_no'	 => $reference_no,
			'created_by'				 => $user->uid,
			'application_status'	     => 'N',
			'due_fees'    				 => $due_amount,
			'balance_amount'			 => $balance_amount,
			'previous_paid_fees'   	 	 => !empty($previous_amount_pre)?$previous_amount_pre:0,
			'max_worker'				 => $max_worker,
			'max_power'					 => $max_power.'('.$unit.')',
			'worker'					 => $rows->worker_total,
			'power'					 	 => $rows->installed_power.'('.$unit.')',
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $Registration_fees,
			
			
			
		);
		//print_r($calculate_fees_details);
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();	
						$late_fees_pay 			= 	0;
						$previous_amount_pre 	=	0;
						$due_amount 			= 	0;
						$late_flag				= 0;
						$flag_payment 			=	'';
						$balance_amount =0;	
						$fees_to_paid = $due_amount_paid;
						$i++;
					}
				}
	   			
}if($date_convert >'2018'){
				
		$manual_payment			=  manual_payment_deatils($application_id,$service_id,$factory_type_id,$reference_no);
		foreach($manual_payment as $history){
					 $manual_payment_amount = $history->payment_amount+$manual_payment_amount;
					
		}
		$previous_amount_pre				= $previous_excess_paid+$manual_payment_amount;
		foreach($power_details as $rows){		
					$power_hp_kw  			= $rows->installed_power_hp;
					$installed_power  		= $rows->installed_power;
					$unit 		 			= $rows->power_unit;
					$fees_fetach 			= fees_calculation_registration_section_85($rows->calculate_starting_year);
					$license_fees		 	= $fees_fetach['fees']*$rows->valid_time_period;
					$max_payment_date		= get_max_payment_date($application_id,$service_id,$factory_type_id,$reference_no);
					$start_date				= date_create($rows->calculate_starting_year);
		 			$application_date 		= date('Y-m-d');
					$application_date1		= date_create($application_date);
					$late_fees 				= 0;
					if($rows->calculate_starting_year < $application_date){ 
							$diff 		= date_diff($start_date,$application_date1);
							$big_diff   = $diff->days;
			}if($big_diff>=1 && $big_diff<=90){
							$late_fees = ($license_fees)*(50/100);
													
			}if($big_diff>91){
							$late_fees = $license_fees;
			}if(!empty($max_payment_date)){
					$payble_fees 	= $license_fees+$late_fees;
					if($previous_amount_pre>$payble_fees){
							$late_fees_pay 		= $late_fees;
							$balance_amount  	= $previous_amount_pre-$payble_fees;
							$due_amount 		= 0;
						
			}if($previous_amount_pre<$payble_fees){
								$due_amount  		= $payble_fees-$previous_amount_pre;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								$late_fees_pay 		= $late_fees;
							
			}if($previous_amount_pre == $payble_fees){
								$due_amount  		= 0;
								$previous_amount 	= 0 ;
								$balance_amount 	= 0;
								$late_fees_pay 		= $late_fees;
							
			}
		}
		if(empty($max_payment_date)){
					$late_fees_pay 	= $late_fees;
					$due_amount 	= $license_fees+$late_fees_pay;
					$balance_amount = 0;
					
				
		}
		
		
		
		if(empty($previous_amount_pre)){
					$previous_amount_pre = 0;
		}
		if($fees_fetach['workers_end_to'] == -1){
			$max_worker = $rows->worker_total." and onwords";
		}else{
			$max_worker = $rows->worker_total;
		}if($fees_fetach['power_range_end_hp'] == -1){
			$max_power = $rows->installed_power_hp." and onwords";
		}else{
			$max_power = $rows->installed_power;
		}
		$calculate_fees_details = array(
			'feesyear' 		             => $fees_fetach['feesyear'],
			'schedule_fees' 		     => $license_fees,
			'late_fees'              	 => $late_fees_pay,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $rows->calculate_year,
			'factory_type'				 => $factory_type_id,
			'application_reference_no'	 => $reference_no,
			'created_by'				 => $user->uid,
			'application_status'	     => 'N',
			'due_fees'    				 => $due_amount,
			'balance_amount'			 => $balance_amount,
			'previous_paid_fees'   	 	 => !empty($previous_amount_pre)?$previous_amount_pre:0,
			'max_worker'				 => $max_worker,
			'max_power'					 => $max_power.'('.$unit.')',
			'worker'					 => $rows->worker_total,
			'power'					 	 => $rows->installed_power.'('.$unit.')',
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $Registration_fees,
	
		);


		//print_r($calculate_fees_details);
		
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
			$previous_amount_pre 	= $balance_amount;
			$total_late_fees 		= $late_fees_pay+$total_late_fees;
			$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
			$total_due_fees 		= $due_amount+$total_due_fees;
			$fees_to_paid			= $total_due_fees;
			$Registration_fees 		=0;
			
	  	   	$i= $i+1;
  		 }
				
				
				
	}
 		
if(empty($previous_excesspaid) || $previous_excesspaid==NULL || $previous_excesspaid==0){
	
		$fees_deatils = array('service_fees'=>$amandment_fess1,'payment_amount'=>$fees_to_paid,'is_previous_payment'=>'No','balance_amount'=>$_SESSION["renewal_amand_balance"],'is_notesheet_amount'=> 0,'application_status'=>'P');
	}else{
		$fees_deatils = array('service_fees'=>$amandment_fess1,'previous_excess_paid'=>$previous_excesspaid,'payment_amount'=>$fees_to_paid,'is_previous_payment'=>'Yes','balance_amount'=>$_SESSION["renewal_amand_balance"],'is_notesheet_amount'=> 0,'application_status' =>'P','modification_date'=>date('Y-m-d'));
}

	
				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		->	fields($fees_deatils);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc		->	execute();
				
 
   	remark_input($reference_no,$application_id,'P','Payment process is sucessfully completed for backog renewal')	;	
	fun_grip_input($fees_to_paid,$application_id,$service_id,$reference_no,$factory_type_id);
	drupal_goto('applicant/view-payment-breakup/' .encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_no));


}



?>


