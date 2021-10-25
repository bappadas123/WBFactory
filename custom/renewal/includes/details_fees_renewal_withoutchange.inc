
<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function details_fees_renewal_withoutchange($form, &$form_state,$serviceid,$factory_typeid,$applicationid,$referenceno) {	
//echo 'hi';die();

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
	$payment_amount				= $get_fa_cafa['payment_amount'];
	$previous_excess_paid		= $balance_amount;
	//$previous_excess_paid		= $balance_amount;
	$last_validlicensedate		= $get_fa_cafa['license_valid_upto'];
	$factory_name				= $get_fa_cafa['factory_name'];
	//$factory_name				= $get_fa_cafa['license_valid_upto'];
	
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
	$form['date_of_amenability_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$date_of_amenability),
	);
	$form['period_for_application_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$period_for_application),
	);
	

	$form['yearly_worker']['form_start'] = array(
			'#prefix' 			=> '<div class = "box-body">
									<div class="box-header with-border">
             						<h3 class="box-title">Fees Calculation for Renewal of License <br/><br/>
									Name:-'.$factory_name.' ('.$section.')'.'
									<br/> Last Validity Date:-'.date("dS M Y",strtotime($last_validlicensedate)).'
									<br/>Period for renewal of license:-'.$period_for_application.'Year(s)</h3>
            
            						</div>',
			
		   
		 );
		 

	  
		
	if($factory_type_id == 1){
		$form['yearly_worker']['worker_year_table'] 	= array(
		 		'#prefix' 			=> '<div id="fees_details_div">',
			 	'#suffix' 			=> '</div>',
  				'#type'				=> 'markup',
				'#markup'			=> show_fees_registration($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid,$last_validlicensedate)
				
  
			);
			
			
			
	}if($factory_type_id == 2){
		$form['yearly_worker']['worker_year_table'] 	= array(
				'#prefix' 			=> '<div id="fees_details_div">',
			 	'#suffix' 			=> '</div>',
  				'#type'				=> 'markup',
				'#markup'			=> show_fees_registration_2mii($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid,$last_validlicensedate)
				
  
			);
		
			
	}if($factory_type_id == 3){
		
		$form['yearly_worker']['worker_year_table'] 	= array(
  				'#type'				=> 'markup',
				'#prefix' 			=> '<div id="fees_details_div">',
			 	'#suffix' 			=> '</div>',
				'#markup'			=> show_fees_registration_85($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid,$last_validlicensedate)
				
  
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



function details_fees_renewal_withoutchange_submit($form, &$form_state){
	global $user;
	$val   								= 	$form_state['values'];

	
	$factory_type						= 	encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$service_id							= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$application_id						= 	encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$reference_no						= 	encryption_decryption_fun('decrypt',$val['reference_no_hidden']);	
	$previousexcess_paid_hidden			= 	encryption_decryption_fun('decrypt',$val['previousexcesspaid_hidden']);
	$date_of_amenability				= 	encryption_decryption_fun('decrypt',$val['date_of_amenability_hidden']);
	$period_for_application				= 	encryption_decryption_fun('decrypt',$val['period_for_application_hidden']);
	
	
	if($val['op'] =="Pay now"){
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


	$output = '<div class="box-header with-border">
              
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
				<th>Schedule Fees(Rs)<br>(calculated fess * total application year)</th>
				<th>Late Fees(Rs)</th>   
				
				<th>Previous Excess Paid(Rs.)</th>
				<th>Balance(Rs)</th>
				<th>Due Amount(Rs)</th>
  	 		</tr>';
 
	$power_details		= yearly_power_worker_details($application_id,$factory_type_id,$service_id,$reference_no);
	foreach($power_details as $rows){
		$other = $rows->power_unit;
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
	if($other == "HP"){
			if($date_convert >='2020'){
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
							 $late_year = $diff->y;
							  $late_month = $diff->m;
							$late_day = $diff->d ;
							$big_diff   = $diff->days;
							
							if($rows->valid_time_period>1){//echo 444;
											if($late_year>0){
											$fees_late_year = $late_year;
											if($late_month>0){
												$fees_late_year = $late_year+1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = $late_year+1;
											}
											
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 
										}
							}else{
								$fees_late_year = 1;
							}
				}
					
					if($big_diff>=1 && $big_diff<=90){
									$late_fees = ($license_fees*$fees_late_year)*(50/100);
													
					}if($big_diff>91){
									$late_fees = ($license_fees*$fees_late_year);
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
	}	
	if($other == "KW"){
	if($date_convert >'2018'){
				foreach($power_details as $rows){		
						$power_hp_kw 			= $rows->installed_power;
					$result_data 			= fees_calculation_registration_power_station($rows->installed_power,$rows->calculate_starting_year);
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
				
				if($rows->valid_time_period>1){//echo 444;
											if($late_year>0){
											$fees_late_year = $late_year;
											if($late_month>0){
												$fees_late_year = $late_year+1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = $late_year+1;
											}
											
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 
										}
							}else{
								$fees_late_year = 1;
							}
				
				if($big_diff>=1 && $big_diff<=90){
									$late_fees = (($license_fees)*(50/100))*$fees_late_year;
													
					}if($big_diff>91){
									$late_fees = ($license_fees)*$fees_late_year;
					}
					
					if(!empty($previous_excess_paid)){
						$payble_fees = $license_fees+$late_fees;
						if($payble_fees>$previous_excess_paid){
							$due_amount =$payble_fees- $previous_excess_paid;
							$late_fees_pay 		= $late_fees;
							$balance_amount 	= 0;
						}if($payble_fees<$previous_excess_paid){
							$due_amount 		=0;
							$late_fees_pay 		= $late_fees;
							$balance_amount 	= $previous_excess_paid-$payble_fees;
						}if($payble_fees==$previous_excess_paid){
							$due_amount 		=0;
							$late_fees_pay 		= $late_fees;
							$balance_amount 	= 0;
						}
					}
				
				if(empty($previous_excess_paid)){
					$late_fees_pay 	= $late_fees;
					$due_amount 	= $license_fees+$late_fees_pay;
					$balance_amount = 0;
					
			
			
					
	}
				$output.='<tr>
						<td>'.$i.'</td>
		             	<td>'.$rows->calculate_year.'</td>
						<td>'.$power_hp_kw.'('.$other.')</td>
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
	}
	   	$i= $i+1;
   
	$output .='</table>
	
				<strong><font color="#FF0000">Fees to be paid for Licence:-'.($fees_to_paid).'</font></strong>
				</div></div>'
				;
			
		 $total_fees_paid_to_end = $fees_to_paid;
		
	return $output;
	
}

function show_fees_registration_2mii($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid,$last_validlicensedate){
	

	 $previous_amount_pre 				=   $previous_excess_paid;
	$Registration_fees 					= 	0;
	$created_by 						=   $user->uid;
	$modifi_date 						=   date("Y-m-d",strtotime($date_of_amenability));
	$last_validity						=   date("Y-m-d",strtotime($last_validlicensedate));
	$i									=	1;
	

 $date = date_create($last_validlicensedate);
$date_convert = date_format($date, "Y");

 $date_convert1 = date_format($date, "Y-m-d");	


	$output = '<div class="box-header with-border">
              
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
   				<th>Total Workers</th>
				<th>Schedule Fees(Rs)<br>(calculated fess * total application year)</th>
				<th>Late Fees(Rs)</th>   
				
				<th>Previous Excess Paid(Rs.)</th>
				<th>Balance(Rs)</th>
				<th>Due Amount(Rs)</th>
  	 		</tr>';
 
	$power_details		= worker_detials_for_fees2mii($application_id,$reference_no,$factory_type_id,$service_id);
	//print_r($power_details);die();
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
	$payment 				= 0;
	$late_flag 				= 0;
	$flag_balance 			= 0;
	$fees_to_paid 			=0;
	$due_flag 				= 0;
	$previous_amount_flag =0;
	
	if($date_convert >='2020'){//echo 999;
				foreach($power_details as $rows){		
				//fees_calculation_registration_2mii($worker1->start_year,$worker1->total_worker)
					$result_data 			= fees_calculation_registration_2mii($rows->start_year,$rows->total_worker);
					//print_r($result_data);
					$license_fees		 	= $result_data['fees']*$rows->vaild_period;
					$max_payment_date 		= get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
					$start_date				= date_create($rows->start_year);
		 			$application_date 		= date('Y-m-d');
					$application_date1		= date_create($application_date);
					$late_fees 				= 0;
				if($rows->start_year < $application_date){ 
							$diff 		= date_diff($start_date,$application_date1);
							 $late_year = $diff->y;
							  $late_month = $diff->m;
							$late_day = $diff->d ;
							$big_diff   = $diff->days;
							
							if($rows->valid_time_period>1){//echo 444;
											if($late_year>0){
											$fees_late_year = $late_year;
											if($late_month>0){
												$fees_late_year = $late_year+1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = $late_year+1;
											}
											
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 
										}
							}else{
								$fees_late_year = 1;
							}
				}
					
					if($big_diff>=1 && $big_diff<=90){
									$late_fees = ($license_fees*$fees_late_year)*(50/100);
													
					}if($big_diff>91){
									$late_fees = ($license_fees*$fees_late_year);
					}
					
				if(!empty($previous_amount_pre)){
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
				if(empty($previous_amount_pre)){
					$late_fees_pay 	= $late_fees;
					$due_amount 	= $license_fees+$late_fees_pay;
					$balance_amount = 0;
					
			
			
					
	}
				$output.='<tr>
						<td>'.$i.'</td>
		             	<td>'.$rows->application_period.'</td>
						<td>'.$rows->total_worker.'</td>
						<td>'.$license_fees.'  ('.$result_data['fees']*$rows->vaild_period.')</td>
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
	
	
	   	$i= $i+1;
   
	$output .='</table>
	
				<strong><font color="#FF0000">Fees to be paid for Licence:-'.($fees_to_paid).'</font></strong>
				</div></div>'
				;
			
		 $total_fees_paid_to_end = $fees_to_paid;
		
	return $output;
	
}

function show_fees_registration_85($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid,$last_validlicensedate){
	
	global $base_root, $base_path, $user;
	 $previous_amount_pre 				= 	$previous_excess_paid;
	$total_ownership_transfer_fees		=	0;
	$Registration_fees 					= 	0;
	$created_by 						=   $user->uid;
	
	$i									=	1;
	$remark 							=	'';

	//echo $application_id.','.$factory_typeid.','.$service_id.','.$reference_number;die;

	$power_details			= yearly_power_worker_details($application_id,$factory_type_id,$service_id,$reference_no);
	
	


					
	//print_r($power_details);die();
	$output = '<div class="box-body">
						<table class="table table-bordered" width="100%">
						<tr>
							<th>SL</th>
							<th>Application Period</th>
							<th>Category(KW/HP)</th>
							<th>Total Workers</th>
							<th>Registration Fees</th>
							<th>Schedule Fees(Rs)<br>(calculated fess * total application year)</th>
							<th>Late Fees(Rs)</th>
							<th>Previous Excess Paid(Rs.)</th>
							<th>Balance(Rs)</th>
							<th>Due Amount(Rs)</th>
							<th>Remark</th>
						</tr>';
	foreach($power_details as $rows){
		$installed_power 	=   $rows->installed_power;
		$worker_total 		=   $rows->worker_total;
		

	if($worker_total>=20 && $installed_power==0){//2m(ii)
	   // $fees_fetach 	=  fees_calculation_registration_2mii($rows->calculate_starting_year,$rows->worker_total);
	   $fees_fetach 			= fees_calculation_registration_2mii($worker1->calculate_starting_year,$worker1->total_worker);
		$remark			=  'Section-2m(ii)'	;
		
	}if($worker_total>=10 && $installed_power>0){//2m(i)
		if($rows->power_unit == 'HP'){
		
			$view = show_fees_registration($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid,$last_validlicensedate);
		//$fees_fetach 			= fees_calculation_registration($rows->installed_power_hp,$rows->worker_total,$rows->calculate_starting_year);	
		}if($rows->power_unit == 'KW'){
			$view = show_fees_registration($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid,$last_validlicensedate);
			//$fees_fetach 			= fees_calculation_registration_power_station($rows->installed_power,$rows->worker_total,$rows->calculate_starting_year);
			
		}
		$remark			=  'Section-2m(i)'	;
	
	}if($worker_total<=9 && $installed_power>=0){//section85
		//echo $worker_total.'---'.$installed_power;die; 
		$fees_fetach 	=	fees_calculation_registration_section_85($rows->calculate_starting_year);
		$remark			=  'Section-85'	;
	}if($worker_total<=19 && $installed_power==0){//section85
		$fees_fetach 	=	fees_calculation_registration_section_85($rows->calculate_starting_year);
		$remark			=  'Section-85'	;
	}
	$fees				=   $fees_fetach['fees']*$rows->valid_time_period;
	$max_payment_date	=	get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
	if(!empty($previous_excess_paid)){
					$datex 				= new DateTime($rows->calculate_starting_year);
		 			$datey 				= new DateTime('2015-12-31');
					$datez 				= new DateTime(date('Y-m-d'));
					$dateamenability	= new DateTime($date_of_amenability);
					$late_fees 			= 0;
					if($datex>$datey){
						$datez 				= new DateTime(date('Y-m-d'));
						$date_valid_year 	= new DateTime($rows->valid_year);
						 if($datez>$datex){ //echo $rows->valid_time_period;
								if($rows->valid_time_period>1){
									//echo 9999;
									$start_date				= date_create($rows->starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
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
											$late_fees = $fees_fetach['fees']*$fees_late_year; 
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 $late_fees = $fees_fetach['fees']*$fees_late_year;
										}
										
										
								
								}
										
								else{
									   $late_fees = $fees_fetach['fees'];
								}
						}
					}
					$payble_fees 	= $fees+$late_fees;
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
	if(empty($previous_excess_paid)){
				$datex 					= new DateTime($rows->calculate_starting_year);
				$datey 					= new DateTime('2015-12-31');
				$previous_amount_pre 	= 0;
				$late_fees_pay 			= 0;
				if($datex>$datey){//echo 999;
						 $datez 			= new DateTime(date('Y-m-d'));
						 $date_valid_year 	= new DateTime($rows->calculate_end_year);
						 $late_fees_pay 	= 0;
						 if($datez>$datex){ //echo $rows->valid_time_period;
								if($rows->valid_time_period>1){
									if($rows->starting_year > '2016-12-31'){//echo 9999;
									$start_date				= date_create($rows->starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
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
											
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											
										}
										
										//print_r($start_date);
										///die();
								}
								}
										
								else{
									   $late_fees_pay = $fees_fetach['fees'];
								}
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
						<td>'.$rows->installed_power.'('.$rows->power_unit.')</td>
						<td>'.$rows->worker_total.'</td>
						<td>'.$Registration_fees.'</td>
						<td>'.$fees.'</td>
						<td>'.$late_fees_pay.'</td>
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
			<strong><font color="#FF0000">Fees to be paid(Total Due amount):-'.($total_due_fees).'</font></strong></div></div>';
				
	return $output;	

	
	}


function save_fees_registration_2mi($application_id,$service_id,$factory_typeid,$reference_number,$previous_excess_paid,$last_validlicensedate){
	
global $base_root, $base_path, $user;
	$previous_amount_pre 				=   $previous_excess_paid;
	$Registration_fees 					= 	0;
	$created_by 						=   $user->uid;
	$modifi_date 						=   date("Y-m-d",strtotime($date_of_amenability));
	$last_validity						=   date("Y-m-d",strtotime($last_validlicensedate));
	$i									=	1;
	

 $date = date_create($last_validlicensedate);
$date_convert = date_format($date, "Y");

 $date_convert1 = date_format($date, "Y-m-d");	


	
 
	$power_details		= yearly_power_worker_details($application_id,$factory_typeid,$service_id,$reference_number);
	//print_r($power_details);die();
	foreach($power_details as $rows){
		$other = $rows->power_unit;
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
	$application_date 		= date('Y-m-d');
	$previous_amount_flag =0;
	if($other == "HP"){
			if($date_convert >='2020'){//echo 99;
				foreach($power_details as $rows){		
					$power_hp_kw 			= $rows->installed_power_hp;
					$unit 		 			= 'Hp';
					$result_data 			= fees_calculation_registration($rows->installed_power_hp,$rows->worker_total,$rows->calculate_starting_year);
					//print_r($result_data);die();
					$license_fees		 	= $result_data['fees']*$rows->valid_time_period;
					$max_payment_date 		= get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
					$start_date				= date_create($rows->calculate_starting_year);
		 			$application_date 		= date('Y-m-d');
					$application_date1		= date_create($application_date);
					$late_fees 				= 0;
				if($rows->calculate_starting_year < $application_date){ 
							$diff 		= date_diff($start_date,$application_date1);
							 $late_year = $diff->y;
							  $late_month = $diff->m;
							$late_day = $diff->d ;
							$big_diff   = $diff->days;
							
							if($rows->valid_time_period>1){//echo 444;
											if($late_year>0){
											$fees_late_year = $late_year;
											if($late_month>0){
												$fees_late_year = $late_year+1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = $late_year+1;
											}
											
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 
										}
							}else{
								$fees_late_year = 1;
							}
				}
					
					if($big_diff>=1 && $big_diff<=90){
									$late_fees = ($license_fees*$fees_late_year)*(50/100);
													
					}if($big_diff>91){
									$late_fees = ($license_fees*$fees_late_year);
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
			if($result_data['workers_end_to'] == -1){
		$max_worker = $rows->worker_total." and onwords";
	}else{
		$max_worker = $result_data['workers_end_to'];
	}if($result_data['power_range_end_kw'] == -1){
		$max_power = $rows->installed_power." and onwords";
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
			'factory_type'				 => $factory_typeid,
			'application_reference_no'	 => $reference_number,
			'created_by'				 => $user->uid,
			'application_status'	     => 'N',
			'due_fees'    				 => $due_amount,
			'balance_amount'			 => $balance_amount,
			'previous_paid_fees'   	 	 => !empty($previous_amount_pre)?$previous_amount_pre:0,
			'max_worker'				 => $max_worker,
			'max_power'					 => $max_power.'(HP)',
			'worker'					 => $rows->worker_total,
			'power'					 	 => $rows->installed_power.'(HP)',
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
			
	  	   	
  		 }
				
				
				
			}
	}	
	if($other == "KW"){
	if($date_convert >'2018'){
				foreach($power_details as $rows){		
						$power_hp_kw 			= $rows->installed_power;
					$result_data 			= fees_calculation_registration_power_station($rows->installed_power,$rows->calculate_starting_year);
					$license_fees		 	= $result_data['fees']*$rows->valid_time_period;
					$max_payment_date 		= get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
					$start_date				= date_create($rows->calculate_starting_year);
		 			$application_date 		= date('Y-m-d');
					$application_date1		= date_create($application_date);
					$late_fees 				= 0;
				if($rows->calculate_starting_year < $application_date){ 
							$diff 		= date_diff($start_date,$application_date1);
							$big_diff   = $diff->days;
							  $late_month = $diff->m;
							$late_day = $diff->d ;
							$big_diff   = $diff->days;
				}
				
				if($rows->valid_time_period>1){//echo 444;
											if($late_year>0){
											$fees_late_year = $late_year;
											if($late_month>0){
												$fees_late_year = $late_year+1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = $late_year+1;
											}
											
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 
										}
							}else{
								$fees_late_year = 1;
							}
				
				if($big_diff>=1 && $big_diff<=90){
									$late_fees = (($license_fees)*(50/100))*$fees_late_year;
													
					}if($big_diff>91){
									$late_fees = ($license_fees)*$fees_late_year;
					}
					
					if(!empty($previous_excess_paid)){
						$payble_fees = $license_fees+$late_fees;
						if($payble_fees>$previous_excess_paid){
							$due_amount =$payble_fees- $previous_excess_paid;
							$late_fees_pay 		= $late_fees;
							$balance_amount 	= 0;
						}if($payble_fees<$previous_excess_paid){
							$due_amount 		=0;
							$late_fees_pay 		= $late_fees;
							$balance_amount 	= $previous_excess_paid-$payble_fees;
						}if($payble_fees==$previous_excess_paid){
							$due_amount 		=0;
							$late_fees_pay 		= $late_fees;
							$balance_amount 	= 0;
						}
					}
				
				if(empty($previous_excess_paid)){
					$late_fees_pay 	= $late_fees;
					$due_amount 	= $license_fees+$late_fees_pay;
					$balance_amount = 0;
					
			
			
					
	}
					if($result_data['workers_end_to'] == -1){
		$max_worker = $rows->worker_total." and onwords";
	}else{
		$max_worker = $result_data['workers_end_to'];
	}if($result_data['power_range_end_kw'] == -1){
		$max_power = $rows->installed_power." and onwords";
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
			'factory_type'				 => $factory_typeid,
			'application_reference_no'	 => $reference_number,
			'created_by'				 => $user->uid,
			'application_status'	     => 'N',
			'due_fees'    				 => $due_amount,
			'balance_amount'			 => $balance_amount,
			'previous_paid_fees'   	 	 => !empty($previous_amount_pre)?$previous_amount_pre:0,
			'max_worker'				 => $max_worker,
			'max_power'					 => $max_power.'(HP)',
			'worker'					 => $rows->worker_total,
			'power'					 	 => $rows->installed_power.'(HP)',
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
	}
	   
   
	if(empty($previous_excess_paid) || $previous_excess_paid==NULL || $previous_excess_paid==0){
	
	$fees_deatils = array('service_fees'=>$Registration_fees1,'payment_amount'=>$fees_to_paid,'is_previous_payment'=>'No','balance_amount'=>$balance_amount,'is_notesheet_amount'=> 0,'application_status' => 'P');
}
else{
	$fees_deatils = array('service_fees'=>$Registration_fees1,'previous_excess_paid'=>$previous_excess_paid,'payment_amount'=>$fees_to_paid,'is_previous_payment'=>'Yes','balance_amount'=>$balance_amount,'is_notesheet_amount'=> 0,'application_status' => 'P');
}

//print_r($fees_deatils);die();
	
				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		->	fields($fees_deatils);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc		->	execute();
				
remark_input($reference_number,$application_id,'P','Payment proecess id successfully completed')	;
fun_grip_input($fees_to_paid,$application_id,$service_id,$reference_number,$factory_typeid);

	drupal_goto('applicant/view-payment-breakup/' .encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_typeid).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_number));
	
	
}


function save_fees_registration_2mii($application_id,$service_id,$factory_type,$reference_no,$previousexcess_paid_hidden,$last_validlicensedate){
	global $base_root, $base_path, $user;

	$previous_amount_pre 				=   $previousexcess_paid_hidden;
	$Registration_fees 					= 	0;
	$created_by 						=   $user->uid;
	$modifi_date 						=   date("Y-m-d",strtotime($date_of_amenability));
	$last_validity						=   date("Y-m-d",strtotime($last_validlicensedate));
	$i									=	1;
	

 $date = date_create($last_validlicensedate);
$date_convert = date_format($date, "Y");

 $date_convert1 = date_format($date, "Y-m-d");	


	
	$power_details		= worker_detials_for_fees2mii($application_id,$reference_no,$factory_type,$service_id);
	//print_r($power_details);die();
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
	$payment 				= 0;
	$late_flag 				= 0;
	$flag_balance 			= 0;
	$fees_to_paid 			=0;
	$due_flag 				= 0;
	$previous_amount_flag =0;
	
	if($date_convert >='2020'){//echo 999;
				foreach($power_details as $rows){		
				//fees_calculation_registration_2mii($worker1->start_year,$worker1->total_worker)
					$result_data 			= fees_calculation_registration_2mii($rows->start_year,$rows->total_worker);
					//print_r($result_data);
					$license_fees		 	= $result_data['fees']*$rows->vaild_period;
					
					$start_date				= date_create($rows->start_year);
		 			$application_date 		= date('Y-m-d');
					$application_date1		= date_create($application_date);
					$late_fees 				= 0;
				if($rows->start_year < $application_date){ 
							$diff 		= date_diff($start_date,$application_date1);
							 $late_year = $diff->y;
							  $late_month = $diff->m;
							$late_day = $diff->d ;
							$big_diff   = $diff->days;
							
							if($rows->valid_time_period>1){//echo 444;
											if($late_year>0){
											$fees_late_year = $late_year;
											if($late_month>0){
												$fees_late_year = $late_year+1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = $late_year+1;
											}
											
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 
										}
							}else{
								$fees_late_year = 1;
							}
				}
					
					if($big_diff>=1 && $big_diff<=90){
									$late_fees = ($license_fees*$fees_late_year)*(50/100);
													
					}if($big_diff>91){
									$late_fees = ($license_fees*$fees_late_year);
					}
					
				if(!empty($previous_amount_pre)){
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
				if(empty($previous_amount_pre)){
					$late_fees_pay 	= $late_fees;
					$due_amount 	= $license_fees+$late_fees_pay;
					$balance_amount = 0;
					
			
			
					
	}
	
	   if($result_data['workers_end_to'] == -1){
			$max_worker = $rows->total_worker." and onwords";
		}else{
			$max_worker = $result_data['workers_end_to'];
		}
	
	$calculate_fees_details = array(
			'feesyear' 		             => $result_data['feesyear'],
			'schedule_fees' 		     => $license_fees,
			'late_fees'              	 => $late_fees_pay,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $rows->application_period,
			'factory_type'				 => $factory_type,
			'application_reference_no'	 => $reference_no,
			'created_by'				 => $user->uid,
			'application_status'	     => 'N',
			'due_fees'    				 => $due_amount,
			'balance_amount'			 => $balance_amount,
			'previous_paid_fees'   	 	 => !empty($previous_amount_pre)?$previous_amount_pre:0,
			'max_worker'				 => $max_worker,
			'worker'					 => $rows->total_worker,
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $Registration_fees,
			
			
			
		);
		//print_r($calculate_fees_details);
		//echo $due_amount;
	$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
			$previous_amount_pre 	= $balance_amount;
			$total_late_fees 		= $late_fees_pay+$total_late_fees;
			$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
			$total_due_fees 		= $due_amount+$total_due_fees;
			$fees_to_paid			= $total_due_fees;
			$Registration_fees 		=0;
			
	  	  
  		 }
				
				
				
			}
	
	if(empty($previousexcess_paid_hidden) || $previousexcess_paid_hidden==NULL || $previousexcess_paid_hidden==0){
	
	$fees_deatils = array('service_fees'=>$Registration_fees1,'payment_amount'=>$fees_to_paid,'is_previous_payment'=>'No','balance_amount'=>$balance_amount,'is_notesheet_amount'=> 0,'application_status'=>'P');
}
else{
	$fees_deatils = array('service_fees'=>$Registration_fees1,'previous_excess_paid'=>$previousexcess_paid_hidden,'payment_amount'=>$fees_to_paid,'is_previous_payment'=>'Yes','balance_amount'=>$balance_amount,'is_notesheet_amount'=> 0,'application_status'=>'P');
}
				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		->	fields($fees_deatils);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc		->	execute();
	//print_r($fees_deatils);die();			
remark_input($reference_no,$application_id,'P','Payment proecess id successfully completed')	;
fun_grip_input($fees_to_paid,$application_id,$service_id,$reference_no,$factory_type);
	drupal_goto('applicant/view-payment-breakup/' .encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_no));
	   	
	
	
}

function save_fees_registration_85($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid,$last_validlicensedate){
	
	global $base_root, $base_path, $user;
	 $previous_amount_pre 				= 	$previous_excess_paid;
	$total_ownership_transfer_fees		=	0;
	$Registration_fees 					= 	0;
	$created_by 						=   $user->uid;
	
	$i									=	1;
	$remark 							=	'';

	

	$power_details			= yearly_power_worker_details($application_id,$factory_type_id,$service_id,$reference_no);
	
	
	foreach($power_details as $rows){
		$installed_power 	=   $rows->installed_power;
		$worker_total 		=   $rows->worker_total;
		

	if($worker_total>=20 && $installed_power==0){
	
	   $fees_fetach 			= fees_calculation_registration_2mii($worker1->calculate_starting_year,$worker1->total_worker);
		$remark			=  'Section-2m(ii)'	;
		
	}if($worker_total>=10 && $installed_power>0){
		if($rows->power_unit == 'HP'){
		
			$view = show_fees_registration($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid,$last_validlicensedate);
			
		}if($rows->power_unit == 'KW'){
			$view = show_fees_registration($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid,$last_validlicensedate);
			
			
		}
		$remark			=  'Section-2m(i)'	;
	
	}if($worker_total<=9 && $installed_power>=0){
		
		$fees_fetach 	=	fees_calculation_registration_section_85($rows->calculate_starting_year);
		$remark			=  'Section-85'	;
	}if($worker_total<=19 && $installed_power==0){
		$fees_fetach 	=	fees_calculation_registration_section_85($rows->calculate_starting_year);
		$remark			=  'Section-85'	;
	}
	$fees				=   $fees_fetach['fees']*$rows->valid_time_period;
	$max_payment_date	=	get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
	if(!empty($previous_excess_paid)){
					$datex 				= new DateTime($rows->calculate_starting_year);
		 			$datey 				= new DateTime('2015-12-31');
					$datez 				= new DateTime(date('Y-m-d'));
					$dateamenability	= new DateTime($date_of_amenability);
					$late_fees 			= 0;
					if($datex>$datey){
						$datez 				= new DateTime(date('Y-m-d'));
						$date_valid_year 	= new DateTime($rows->valid_year);
						 if($datez>$datex){ 
								if($rows->valid_time_period>1){
									
									$start_date				= date_create($rows->starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
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
											$late_fees = $fees_fetach['fees']*$fees_late_year; 
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 $late_fees = $fees_fetach['fees']*$fees_late_year;
										}
										
										
								
								}
										
								else{
									   $late_fees = $fees_fetach['fees'];
								}
						}
					}
					$payble_fees 	= $fees+$late_fees;
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
	if(empty($previous_excess_paid)){
				$datex 					= new DateTime($rows->calculate_starting_year);
				$datey 					= new DateTime('2015-12-31');
				$previous_amount_pre 	= 0;
				$late_fees_pay 			= 0;
				if($datex>$datey){
						 $datez 			= new DateTime(date('Y-m-d'));
						 $date_valid_year 	= new DateTime($rows->calculate_end_year);
						 $late_fees_pay 	= 0;
						 if($datez>$datex){
								if($rows->valid_time_period>1){
									if($rows->starting_year > '2016-12-31'){
									$start_date				= date_create($rows->starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
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
											
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											
										}
										
									
								}
								}
										
								else{
									   $late_fees_pay = $fees_fetach['fees'];
								}
						}
					
				 $due_amount 	= $fees+$late_fees_pay+$total_transfer_fees+$Registration_fees;
				$balance_amount = 0;
				
			}else{
				$due_amount 	= $fees+$total_transfer_fees+$Registration_fees;
				$balance_amount = 0;
				$late_fees_pay 	= 0;
			}
			
					
	}

	
			
		$max_worker = $rows->worker_total." and onwords";
	
		$max_power = $rows->installed_power.'('.$rows->power_unit.')and onwords';
	
		$calculate_fees_details = array(
			'feesyear' 		             => $fees_fetach['feesyear'],
			'schedule_fees' 		     => $fees,
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
			'max_power'					 => $max_power,
			'worker'					 => $rows->worker_total,
			'power'					 	 => $rows->installed_power.'('.$rows->power_unit.')',
			'transfer_fees'				 => $total_transfer_fees,
			'service_fees'				 => $Registration_fees,
			'remark'					 => $remark
			
			
			
		);
		//print_r($calculate_fees_details);
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$Registration_fees 		=0;
		$late_fees_pay =0;
		$total_transfer_fees =0;
	}
	
if(empty($previous_excess_paid) || $previous_excess_paid==NULL || $previous_excess_paid==0){
	
	$fees_deatils = array('service_fees'=>0,'payment_amount'=>$fees_to_paid,'is_previous_payment'=>'No','balance_amount'=>$balance_amount,'is_notesheet_amount'=> 0,'application_status' => 'P');
}
else{
	$fees_deatils = array('service_fees'=>0,'previous_excess_paid'=>$previous_excess_paid,'payment_amount'=>$total_due_fees,'is_previous_payment'=>'Yes','balance_amount'=>$balance_amount,'is_notesheet_amount'=> 0,'application_status' => 'P');
}

//print_r($fees_deatils);die();
	
				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		->	fields($fees_deatils);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc		->	execute();
				
		remark_input($reference_no,$application_id,'P','Payment proecess id successfully completed')	;
		fun_grip_input($fees_to_paid,$application_id,$service_id,$reference_no,$factory_type_id);

	drupal_goto('applicant/view-payment-breakup/' .encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_no));
	
	}

?>


