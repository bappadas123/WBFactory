
<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function amenment_of_fees($form, &$form_state,$serviceid,$factory_typeid,$applicationid,$referenceno) {	
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
	$factory_license_no			= $get_fa_cafa['factory_license_no'];
    $form 						= array();
	if($factory_type_id == 1){
		$section = 'Section-2m(i)';
	}if($factory_type_id == 2){
		$section = 'Section-2m(ii)';
	}if($factory_type_id == 3){
			$section = 'Section-85';
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
             						<h3 class="box-title">Fees Calculation for Amendment of License<br/>
									<br/>Name:-'.$factory_name.'('.$section.')
									<br/>Licenae Number:-'.$factory_license_no.'  Validity upto:-'.date("dS M Y",strtotime($last_validlicensedate)).'
									<br/>Period for Amendment of license:-'.$period_for_application.'Year(s)</h3>
            
            						</div></div>',
			
		   
		 );
		 

	
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
			'#suffix' 			=> '</div></div>',
			
			
	);
	$manual_payment_decission = isset($form_state['values']['manual_payment'])? $form_state['values']['manual_payment'] : (!empty($is_payment_mad)?$is_payment_mad:'No');

	/*if($manual_payment_decission == 'No'){  
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
				'#markup'			=> show_fees_registration_2mii($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid)
				
  
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
				'#markup'			=> show_fees_registration_section_85($application_id,$service_id,$factory_type_id,$reference_no,$date_of_amenability,$period_for_application)
				
  
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
}*/

if($factory_type_id == 1){
	
			
			$form['yearly_worker']['worker_amand_fees'] 	= array(
		 		
				'#prefix' 			=> '<div id="amand_fees_details_div">',
				'#suffix' 			=> '</div>',
		   		'#type'				=> 'markup',
				'#markup'			=> show_fees_registration_amand($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid)
			);
			
	}if($factory_type_id == 2){
	
		$form['yearly_worker']['worker_amand_fees'] 	= array(
		 		
				'#prefix' 			=> '<div id="amand_fees_details_div">',
				'#suffix' 			=> '</div>',
		   		'#type'				=> 'markup',
				'#markup'			=> show_fees_registration_amand_2mii($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid)
			);
			
	}if($factory_type_id == 3){
		
		
		
			
			$form['yearly_worker']['worker_amand_fees'] 	= array(
		 		
				'#prefix' 			=> '<div id="amand_fees_details_div">',
				'#suffix' 			=> '</div>',
		   		'#type'				=> 'markup',
				'#markup'			=> show_fees_registration_amand($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid)
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
return $form;

		 
}


/*function manual_ajax_payment($form, $form_state){
	
	
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
}*/

/*
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
}*/
function amenment_of_fees_submit($form, &$form_state){
	global $user;
	$val   								= 	$form_state['values'];

	
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
	$upload_chanal 						= file_load($val['upload_chanal']);

	
	if($val['op'] =="Pay now"){
		
		if($factory_type == 3){
			save_pay_amount_details_85($application_id,$service_id,$factory_type,$reference_no,$date_of_amenability,$period_for_application,$previousexcess_paid_hidden,$is_payment_mad,$previous_excess_paid);
			
		}if($factory_type == 1){
			
			//save_fees_registration_2mi($application_id,$service_id,$factory_type,$reference_no,$previousexcess_paid_hidden,$last_validlicensedate,$previous_excess_paid);
			
		save_fees_registration_amand($application_id,$service_id,$factory_type,$reference_no,$previousexcess_paid_hidden);	
			
		}if($factory_type == 2){
			save_fees_registration_amand_2mii($application_id,$service_id,$factory_type,$reference_no,$previousexcess_paid_hidden);
			
		}
	
	}
	
}

function show_fees_registration_amand($application_id,$service_id,$factory_typeid,$reference_number,$previous_excess_paid){
$transfer_fess = 0;	
$fees_flag=0;

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
	
$content = fun_check_point($application_id,$service_id,$factory_typeid,$reference_number);
  $fieldname = explode(',', $content['fieldname']);
  foreach ($fieldname as $row_fieldname){
	  if($row_fieldname == 'factory_name'){
	  $get_previous_details= get_previous_details($application_id,$reference_number,$factory_typeid,$service_id); 
	  foreach($get_previous_details as $row_fees){
		  $transfer_fess = $transfer_fess+$row_fees->transfer_fees;
		  
	  } 
  }
  	  if($row_fieldname == 'worker_details'){
		  $fees_flag = 1;
	  }if($row_fieldname == 'power_details'){
		  $fees_flag = 1;
	  }if($row_fieldname == 'nature_details'){
		  $transfer_fess = $transfer_fess+100;
	  }
  }
  

if($fees_flag == 1){
	$amandment_fess = $transfer_fess+1000;
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
				
				
				$last_validity					=   date("Y-m-d",strtotime($amand_valid_year));
				 $last_validity_year  			= 	date('Y',strtotime($amand_valid_year));
				if($present_installed_power_unit == "HP"){
					 $fees_previous  				= fees_calculation_registration($previous_power,$previous_worker,$amand_starting_year);
					 $fees_previous_paid 			= ($fees_previous['fees']*$amand_valid_time_period);
					 $fees_previous_paid			= $fees_previous_paid+$previous_excess_paid;
						if($last_validity == '2018-12-31'){
				  					$application_date 		= date('Y-m-d');
									$power_hp_kw  			= $present_power;
				 					$unit 		  			= 'Hp';
				 					$previous_amount_pre	= $fees_previous_paid;
				 					$payment 				= 0;
				 					$result_data  			= fees_calculation_registration($present_power,$present_totalworker,$amand_starting_year);
						    		$license_fees			= $license_fees_1 = $result_data['fees']*$amand_valid_time_period;
						   			$license_start_date 	= $amand_starting_year;
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
					 
			
				 
				 
				 					
				
				
			}
						if($last_validity_year > '2018'){//echo 'hi';
				           		
							$power_hp_kw 			= $present_power;
							$unit 		 			= 'Hp';
							$result_data  			= fees_calculation_registration($present_power,$present_totalworker,$amand_starting_year);
							$license_fees			=$license_fees_1 = $result_data['fees']*$amand_valid_time_period;
					  	    $license_start_date 	= $amand_starting_year;
							$application_date1		= date_create($application_date);
							$late_fees 				= 0;
							if($amand_starting_year < $application_date1){ 
									$start_date		= date_create($amand_starting_year);
									$diff			= date_diff($start_date,$application_date1);
									 $big_diff  		= $diff->days;
										
										 
										 
							}
					
							if($big_diff>=1 && $big_diff<=90){
									$late_fees_pay = ($license_fees)*(50/100);
													
							}if($big_diff>91){
									$late_fees_pay = $license_fees;
							}
							$total_show_due = $license_fees+$late_fees_pay;
					//echo $late_fees_pay.'----'.$license_fees;die;
							 $payblefess = $license_fees+$late_fees_pay+$amandment_fess;
							if($payblefess>$previous_excess_paid){
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
						<td>'.$total_show_due.'</td>
						
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';
					
		$output.='</tr>';
		$sl++;	
		
			
	}
						if($last_validity_year <= '2015'){
						
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
							}
					
							if($big_diff>=1 && $big_diff<=90){
									$late_fees = ($license_fees)*(50/100);
													
							}if($big_diff>91){
									$late_fees = $license_fees;
							}
					
				
							 $payblefess = $license_fees+$late_fees+$amandment_fess;
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
						<td>'.$payblefess.'</td>
						
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';
					
		$output.='</tr>';
		$sl++;	
		
				}
				           		
				$amandment_fess=0;
				$total_amand_fees = $total_amand_fees+$due_amount;		
			}
			
			    if($present_installed_power_unit == "KW"){//echo $balance_amount;die();
					$fees_previous  				= fees_calculation_registration_power_station($previous_power,$previous_worker,$amand_starting_year);
					  $fees_previous_paid 			= ($fees_previous['fees']*$amand_valid_time_period);
					 $fees_previous_paid				= $fees_previous_paid+$balance_amount;
						if($last_validity == '2018-12-31'){
				  					$application_date 		= date('Y-m-d');
									$power_hp_kw  			= $present_power;
				 					$unit 		  			= 'Hp';
				 					$previous_amount_pre	= $fees_previous_paid;
				 					$payment 				= 0;
				 
				
					
					  
						   $result_data  = fees_calculation_registration_power_station($present_power,$present_totalworker,$amand_starting_year);
						  
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
		$total_amand_fees = $total_amand_fees+$due_amount;		 
				
				 
				 }
			
				
				
			
						if($last_validity_year > '2018'){
				           		
							$power_hp_kw 			= $present_power;
							$unit 		 			= 'Hp';
							$result_data  			= fees_calculation_registration($present_power,$present_totalworker,$amand_starting_year);
							$license_fees		=$license_fees_1 = $result_data['fees']*$amand_valid_time_period;
					  	    $license_start_date 	= $amand_starting_year;
							$application_date1		= date_create($application_date);
							$late_fees 				= 0;
							if($amand_starting_year < $application_date){ //echo 'hi';
									$start_date		= date_create($amand_starting_year);
									$application_date1		= date_create($application_date);
										
										$diff			= date_diff($start_date,$application_date1);
										$big_diff  		= $diff->days;
										if($late_year>0){
											$fees_late_year = $late_year;
											if($late_month>0){
												$fees_late_year = $late_year+1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = $late_year+1;
											}
											 $late_fees = $schedule_fees['fees']*$fees_late_year;
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 $late_fees = $schedule_fees['fees']*$fees_late_year;
										}
										 
							}
					
							if($big_diff>=1 && $big_diff<=90){
									$late_fees_pay = ($late_fees)*(50/100);
													
							}if($big_diff>91){
									$late_fees_pay = $late_fees;
							}
					echo $late_fees_pay;die();
				
							 $payblefess = $license_fees+$late_fees_pay;
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
						<td>'.$payblefess.'</td>
						
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';
					
		$output.='</tr>';
		$sl++;		
			
	}
				
  		 
				
				if($last_validity_year <= '2015'){
				}
				           		
				$amandment_fess=0;
			}
			   
	}	
				
				  
	   	$i= $i+1;
		
   
 
	$output .='</table>
	
				<strong><font color="#FF0000">Fees to be paid For Amandment:-'.($total_amand_fees).'</font></strong><br/>
			
				</div></div>'
				;
	
}
else{
		$amandment_fess = $transfer_fess;
	if($previous_excess_paid>$amandment_fess){
		$due_amount  = $previous_excess_paid-$amandment_fess;
	}if($previous_excess_paid==$amandment_fess){
		$due_amount  = $amandment_fess-$previous_excess_paid;
	}if($previous_excess_paid<$amandment_fess){
		$due_amount  = $amandment_fess-$previous_excess_paid;
	}

	$output .='
	
				<strong><font color="#FF0000">Fees to be paid For Amandment:-'.($due_amount).'</font></strong><br/>
			
				'
				;
}
	
	
	
	
	return $output;
}




function show_fees_registration_amand_2mii($application_id,$service_id,$factory_typeid,$reference_number,$previous_excess_paid){

	
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
	$content = fun_check_point($application_id,$service_id,$factory_typeid,$reference_number);
  $fieldname = explode(',', $content['fieldname']);
  //print_r($fieldname);die();
  foreach ($fieldname as $row_fieldname){
	  if($row_fieldname == 'factory_name'){
	  $get_previous_details= get_previous_details($application_id,$reference_number,$factory_typeid,$service_id); 
	  // print_r($get_previous_details);die();
	  foreach($get_previous_details as $row_fees){
		   $transfer_fess = $transfer_fess+$row_fees->transfer_fees;
		  
	  } 
  }
     if($row_fieldname == 'worker_details'){
		  $fees_flag = 1;
		 
	  }
	  if($row_fieldname == 'power_details'){
		  $fees_flag = 1;
	  }
	  if($row_fieldname == 'nature_details'){
		  $transfer_fess = $transfer_fess+1000;
	  }
  }
  if($fees_flag == 1){
	  $amandment_fess = $transfer_fess+1000;
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
							$late_fees_pay=0;	
							if($starting_year < $application_date){ 
									 $start_date			= date_create($starting_year);
									 $diff					= date_diff($start_date,$application_date1);
									 $big_diff  			= $diff->days;
									 if($big_diff>=1 && $big_diff<=90){
											$late_fees_pay = ($license_fees)*(50/100);
													
									}if($big_diff>91){
											$late_fees_pay = $license_fees;
									}

							}
					
							
					
				//echo $late_fees_pay;die();
					$payble_fees = $license_fees+$late_fees_pay+$amandment_fess;
					$payble_fees_show = $license_fees+$late_fees_pay;
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
						<td>'.$payble_fees_show.'('.$license_fees.'+'.$late_fees_pay.')</td>
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
		$output .='</table></div>
	
				<strong><font color="#FF0000">Fees to be paid For Amandment:-'.($total_amand_fees).'</font></strong><br/>
				
				</div></div>'
				;
  }else{
	  $amandment_fess = $transfer_fess;
	  if($previous_excess_paid>$amandment_fess){
		  $balance_amount = $previous_excess_paid-$amandment_fess;
		  $total_amand_fees 	  = 0;
	  }if($previous_excess_paid<$amandment_fess){
		  $total_amand_fees = $amandment_fess-$previous_excess_paid;
		  $balance_amount = 0;
	  }if($previous_excess_paid==$amandment_fess){
		   $balance_amount = 0;
		   $total_amand_fees 	  = 0;
	  }
	  
	  $output .='
	
				<strong><font color="#FF0000">Fees to be paid For Amandment:-'.($total_amand_fees).'</font></strong><br/>
				
				</div></div>';
	  
  }
  
	
	
		
   
  
	
	
	return $output;}
	
	


/*
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
}*/



function save_fees_registration_amand($application_id,$service_id,$factory_typeid,$reference_number,$previous_excess_paid){
  global $base_root, $base_path, $user;
  $transfer_fess = 0;	
 $fees_flag=0;
 $total_payment_amount=0;
 $previous_excess_paid1 = $previous_excess_paid;
 $content = fun_check_point($application_id,$service_id,$factory_typeid,$reference_number);
  $fieldname = explode(',', $content['fieldname']);
  foreach ($fieldname as $row_fieldname){
	  if($row_fieldname == 'factory_name'){
	  $get_previous_details= get_previous_details($application_id,$reference_number,$factory_typeid,$service_id); 
	  foreach($get_previous_details as $row_fees){
		  $transfer_fess = $transfer_fess+$row_fees->transfer_fees;
		  
	  } if($row_fieldname == 'worker_details'){
		  $fees_flag = 1;
	  }if($row_fieldname == 'power_details'){
		  $fees_flag = 1;
	  }if($row_fieldname == 'nature_details'){
		  $transfer_fess = $transfer_fess+100;
	  }
  }
  }
  if($fees_flag==1){
	  $amandment_fess = $amandment_fess1=$transfer_fess+1000;

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
				/*$last_validity					=   date("Y-m-d",strtotime($amand_valid_year));
				$last_validity_year  			= 	date('Y',strtotime($amand_valid_year));*/
				//echo $present_installed_power_unit;
				$date_amand 							= date_create($amand_valid_year);
				$date_convert_amand 					= date_format($date_amand, "Y");

				$date_convert1_amand 					= date_format($date_amand, "Y-m-d");	
				
				
				
				if($present_installed_power_unit == "HP"){
					 $fees_previous  				= fees_calculation_registration($previous_power,$previous_worker,$amand_starting_year);
					 $fees_previous_paid 			= $fees_previous['fees']*$amand_valid_time_period;
					 $fees_previous_paid				= $fees_previous_paid+$previous_excess_paid;
					   if($date_convert1_amand == '2018-12-31'){
				  					$application_date 		= date('Y-m-d');
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
			
			
			
		);
		//print_r($calculate_fees_details);		
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
						 
			$total_payment_amount = 	$due_amount+$total_payment_amount;
				 
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
							if($amand_starting_year < $application_date1){ 
									$start_date		= date_create($amand_starting_year);
									$diff			= date_diff($start_date,$application_date1);
									$big_diff  		= $diff->days;
										
										 
										 
							}
					//echo $big_diff;
							if($big_diff>=1 && $big_diff<=90){
									$late_fees_pay = ($license_fees)*(50/100);
													
							}if($big_diff>91){
									$late_fees_pay = $license_fees;
							}
					
				//echo $late_fees_pay;
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
			
			
			
		);
		//print_r($calculate_fees_details);
		
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
			$total_payment_amount = 	$due_amount+$total_payment_amount;
			
			
	}
						if($date_convert_amand <= '2015'){
				}
				           		
						$amandment_fess=0;
						$total_amand_fees = $total_amand_fees+$due_amount;		
			}
			
			    if($present_installed_power_unit == "KW"){ 
					$fees_previous  				= fees_calculation_registration_power_station($previous_power,$previous_worker,$amand_starting_year);
					  $fees_previous_paid 			= $fees_previous['fees']*$amand_valid_time_period;
					 $fees_previous_paid				= $fees_previous_paid+$balance_amount;
						if($date_convert1_amand == '2018-12-31'){
				  					$application_date 		= date('Y-m-d');
									$power_hp_kw  			= $present_power;
				 					$unit 		  			= 'Hp';
				 					$previous_amount_pre	= $fees_previous_paid;
				 					$payment 				= 0;
				 
				 if(!empty($fees_previous_paid)){
					
					  
						   $result_data  = fees_calculation_registration_power_station($present_power,$present_totalworker,$amand_starting_year);
						  
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
			'worker'					 => $rows->worker_total,
			'power'					 	 => $rows->installed_power.'(KW)',
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $amandment_fess,
			
			
			
		);
		//echo'------------------------------';
		//print_r($calculate_fees_details);
		//$balance_amount =
			$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
			
		$balance_amount = 0;			
			$total_payment_amount = 	$due_amount+$total_payment_amount;	 
				
				 
				 }
			
				
				
			}
						elseif($date_convert_amand > '2018'){
				           		
							$power_hp_kw 			= $present_power;
							$unit 		 			= 'Hp';
							$result_data  			= fees_calculation_registration($present_power,$present_totalworker,$amand_starting_year);
							$license_fees		   =	$license_fees_1 = $result_data['fees']*$amand_valid_time_period;
					  	    $license_start_date 	= $amand_starting_year;
							$application_date1		= date_create($application_date);
							$late_fees 				= 0;
							if($amand_starting_year < $application_date){ 
									$start_date		= date_create($amand_starting_year);
									$application_date1		= date_create($application_date);
										
										 $diff			= date_diff($start_date,$application_date1);
										 $big_diff  		= $diff->days;
										 if($big_diff>=1 && $big_diff<=90){
											$late_fees = ($license_fees)*(50/100);
													
										}if($big_diff>91){
												$late_fees = $license_fees;
										}
					
							}
				
							
				
							 $payblefess = $license_fees+$late_fees;
							if($payblefess>$fees_previous_paid){
								$due_amount = $payblefess-$fees_previous_paid;
								$balance_amount = 0;	
							}else{
								$balance_amount = $fees_previous_paid-$payblefess;
								$due_amount = 0;
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
			'late_fees'              	 => $late_fees,
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
			'worker'					 => $rows->worker_total,
			'power'					 	 => $rows->installed_power.'(KW)',
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $amandment_fess,
			
			
			
		);
		//echo'------------------------------';
		//print_r($calculate_fees_details);
		//$balance_amount =
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
			$total_payment_amount = 	$due_amount+$total_payment_amount;
			
	}
				
  		 
				
				elseif($date_convert_amand <= '2015'){echo 'hi';
				}
				           		
				$amandment_fess=0;
			}
			
			$date_amand =NULL;
			$date_convert_amand =NULL;
			$date_convert1_amand = NULL;
			   
	}	
  }
  else{
	   $amandment_fess =$amandment_fess1= $transfer_fess;
	if($previous_excess_paid>$amandment_fess){
		$total_payment_amount  = 0;
		$balance_amount = $previous_excess_paid-$amandment_fess;
	}if($previous_excess_paid==$amandment_fess){
		$total_payment_amount  = $amandment_fess-$previous_excess_paid;
		$total_payment_amount  = 0;
	}if($previous_excess_paid<$amandment_fess){
		$total_payment_amount  = $amandment_fess-$previous_excess_paid;
		$balance_amount = 0;
	}
  }
  
				
	if(empty($previous_excess_paid1) || $previous_excess_paid1==NULL || $previous_excess_paid1=0){
	
	$fees_deatils = array('service_fees'=>$amandment_fess1,'payment_amount'=>$total_payment_amount,'is_previous_payment'=>'No','balance_amount'=>$balance_amount,'is_notesheet_amount'=> 0,'application_status'=>'P');
}
else{
	$fees_deatils = array('service_fees'=>$amandment_fess1,'previous_excess_paid'=>$previous_excess_paid1,'payment_amount'=>$total_payment_amount,'is_previous_payment'=>'Yes','balance_amount'=>$balance_amount,'is_notesheet_amount'=> 0,'application_status' =>'P');
}

	//print_r($fees_deatils);die();
				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		->	fields($fees_deatils);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc		->	execute();
				
 // session_unset();
 // session_destroy();
   
	drupal_goto('applicant/view-payment-breakup/' .encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_typeid).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_number));
	//echo $application_id;die();
	//drupal_goto('epayments_preview/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$reference_number).'/'.encryption_decryption_fun('encrypt',$factory_typeid));
	
	

	
	
}


function save_fees_registration_amand_2mii($application_id,$service_id,$factory_typeid,$reference_number,$previous_excess_paid){
global $base_root, $base_path, $user;
	$previous_excess_paid1 = $previous_excess_paid;
	$total_previous_paymnet = 0;
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
	$content = fun_check_point($application_id,$service_id,$factory_typeid,$reference_number);
  $fieldname = explode(',', $content['fieldname']);
  //print_r($fieldname);die();
  foreach ($fieldname as $row_fieldname){
	  if($row_fieldname == 'factory_name'){
	  $get_previous_details= get_previous_details($application_id,$reference_number,$factory_typeid,$service_id); 
	  // print_r($get_previous_details);die();
	  foreach($get_previous_details as $row_fees){
		   $transfer_fess = $transfer_fess+$row_fees->transfer_fees;
		  
	  } 
  }
     if($row_fieldname == 'worker_details'){
		  $fees_flag = 1;
		 
	  }
	  if($row_fieldname == 'power_details'){
		  $fees_flag = 1;
	  }
	  if($row_fieldname == 'nature_details'){
		  $transfer_fess = $transfer_fess+1000;
	  }
  }
  if($fees_flag == 1){
	  $amandment_fess=$amandment_fess1 = $transfer_fess+1000;
	 
			
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
			
			
			
		);
		
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
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
							$late_fees_pay=0;	
							if($starting_year < $application_date){ 
									 $start_date			= date_create($starting_year);
									 $diff					= date_diff($start_date,$application_date1);
									 $big_diff  			= $diff->days;
									 if($big_diff>=1 && $big_diff<=90){
											$late_fees_pay = ($license_fees)*(50/100);
													
									}if($big_diff>91){
											$late_fees_pay = $license_fees;
									}

							}
					
							
					
				//echo $late_fees_pay;die();
					$payble_fees = $license_fees+$late_fees_pay+$amandment_fess;
					$payble_fees_show = $license_fees+$late_fees_pay;
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
			
						
			  if($result_data['workers_end_to'] == -1){
			$max_worker = $Previous_Total_Worke." and onwords";
		}else{
			$max_worker = $result_data['workers_end_to'];
		}
				
			
		$calculate_fees_details = array(
			'feesyear' 		             => $result_data['feesyear'],
			'schedule_fees' 		     => $license_fees,
			'late_fees'              	 => $late_fees_pay,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $amand_row->service_year,
			'factory_type'				 => $factory_typeid,
			'application_reference_no'	 => $reference_number,
			'created_by'				 => $user->uid,
			'application_status'	     => 'N',
			'due_fees'    				 => $due_amount,
			'balance_amount'			 => $balance_amount,
			'previous_paid_fees'   	 	 => !empty($fees_previous_paid)?$fees_previous_paid:0,
			'max_worker'				 => $max_worker,
			'worker'					 => $amand_row->worker_total,
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $amandment_fess,
			
			
			
		);
		//print_r($calculate_fees_details);
		
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
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
			
			
			
		);
		
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
		$sl++;		
				}
				           		
				$amandment_fess=0;
				$total_amand_fees = $total_amand_fees+$due_amount;	
				$previous_excess_paid = 0;	
				$total_previous_paymnet = $fees_previous_paid+$total_previous_paymnet;
			
			
			 
			   
	}	
				
				  
	   	$i= $i+1;
		
  }else{
	  $amandment_fess=$amandment_fess1 = $transfer_fess;
	  if($previous_excess_paid>$amandment_fess){
		  $balance_amount = $previous_excess_paid-$amandment_fess;
		  $total_amand_fees 	  = 0;
	  }if($previous_excess_paid<$amandment_fess){
		  $total_amand_fees = $amandment_fess-$previous_excess_paid;
		  $balance_amount = 0;
	  }if($previous_excess_paid==$amandment_fess){
		   $balance_amount = 0;
		   $total_amand_fees 	  = 0;
	  }
	  
	if($result_data['workers_end_to'] == -1){
			$max_worker = $Previous_Total_Worke." and onwords";
		}else{
			$max_worker = $result_data['workers_end_to'];
		}
				
			
		
	  
  }
  
	
	$fees_deatils = array('service_fees'=>$amandment_fess1,'previous_excess_paid'=>$total_previous_paymnet,'payment_amount'=>$total_amand_fees,'is_previous_payment'=>'Yes','balance_amount'=> $balance_amount,'is_notesheet_amount'=> 0,'application_status'=>'P');

				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		->	fields($fees_deatils);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc		->	execute();
	//print_r($fees_deatils);die();			

	drupal_goto('applicant/view-payment-breakup/' .encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_typeid).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_number));
		
   
  
	
	
	}




?>


