<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function repayment_fees_registation($form, &$form_state,$serviceid,$factory_typeid,$applicationid,$referenceno) {	
	global $base_root, $base_path, $user;
	
	
	$application_id 			= encryption_decryption_fun('decrypt', $applicationid);
	$service_id 				= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 			= encryption_decryption_fun('decrypt',$factory_typeid);
	$reference_no 				= encryption_decryption_fun('decrypt',$referenceno);
	$get_fa_cafa 				= get_fa_cafa($application_id);
    $reference_no 				= $get_fa_cafa['reference_number'];
	$date_of_amenability 		= $get_fa_cafa['date_of_amenability'];
	$recomended_date_of_amenability	= $gat_fa_cafe['recomended_date_of_amenability'];
	$period_for_application 	= $get_fa_cafa['period_for_application'];
	echo $previous_excess_paid		= $get_fa_cafa['previous_excess_paid'];
	$is_calculate				= $get_fa_cafa['is_calculate'];
	$application_status			= $get_fa_cafa['application_status'];
	$is_notesheet_amount		= $get_fa_cafa['is_notesheet_amount'];
	$factory_name				= $get_fa_cafa['factory_name'];
	echo $previous_payment_amount	= $get_fa_cafa['payment_amount'];
	$total_payment				= $previous_payment_amount+$previous_excess_paid;
	if($factory_type_id == 1){
		$section = 'Section-2m(i)';
	}if($factory_type_id == 2){
		$section = 'Section-2m(ii)';
	}if($factory_type_id == 3){
		$section = 'Section-85';
	}
	if($is_notesheet_amount == 1){
		drupal_goto('epayments_preview/'.$applicationid.'/'.$serviceid.'/'.$referenceno.'/'.$factory_typeid);
	}
	if(empty($recomended_date_of_amenability)){
		$recomended_date_of_amenability = $date_of_amenability;
	}
	if($recomended_date_of_amenability != $date_of_amenability){
		drupal_goto('applicant/re-payment/power-details/' .$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$referenceno);
	}
	
	
    $form = array();
	
	$form['#attributes'] 	= array('enctype' => "multipart/form-data");
	
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
		'#default_value' 	=> encryption_decryption_fun('encrypt',$total_payment),
	);
	$form['date_of_amenability_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> encryption_decryption_fun('encrypt',$date_of_amenability),
	);
	$form['period_for_application_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> encryption_decryption_fun('encrypt',$period_for_application),
	);
	
	
	
	

		
		
		if($factory_type_id == 1){
			
			$form['yearly_worker']['worker_year_table'] 	= array(
		 		'#prefix' 			=> '<div id="fees_details_div">',
			 	'#suffix' 			=> '</div>',
  				'#type'				=> 'markup',
				'#markup'			=> show_fees_registration($application_id,$service_id,$factory_type_id,$reference_no,$total_payment,$date_of_amenability)
			);
		}
    	if($factory_type_id == 2){
		$form['yearly_worker']['worker_year_table'] 	= array(
				'#prefix' 			=> '<div id="fees_details_div">',
			 	'#suffix' 			=> '</div>',
  				'#type'				=> 'markup',
				'#markup'			=> show_fees_registration_2mii($application_id,$service_id,$factory_type_id,$reference_no,$total_payment,$date_of_amenability)
			);
		}
    	if($factory_type_id == 3){
			$form['yearly_worker']['worker_year_table'] 	= array(
				'#prefix' 			=> '<div id="fees_details_div">',
			 	'#suffix' 			=> '</div>',
  				'#type'				=> 'markup',
				'#markup'			=> show_fees_registration_section_85($application_id,$service_id,$factory_type_id,$reference_no,$total_payment,$date_of_amenability)
			);
		}
		
		$form['yearly_worker']['fees_pay'] 	= array(
				'#prefix' 			=> '<div class="col-md-12">',
				'#suffix' 			=> '</div>',
				'#type' 			=> 'submit',
				'#value' 			=> t('Next'),
				'#attributes' 		=> array('class' => array('btn btn-success pull-right')),
			);
		
	
	
	
	$form['yearly_worker']['form_end'] = array(
		'#suffix' 			=> '</div></div>',
	);
	return $form;     
}
	
	 


function repayment_fees_registation_submit($form, &$form_state){
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
	$upload_chanal 						= file_load($val['upload_chanal']);
	if($val['op'] =="Next"){
		if($factory_type == 3){
			save_pay_amount_details_85($application_id,$service_id,$factory_type,$reference_no,$date_of_amenability,$previousexcess_paid_hidden);
		}if($factory_type == 1){
			save_apy_ment_details_2mi($application_id,$service_id,$factory_type,$reference_no,$date_of_amenability,$previousexcess_paid_hidden);
		}if($factory_type == 2){
			save_apy_ment_details_2mii($application_id,$service_id,$factory_type,$reference_no,$previousexcess_paid_hidden,$date_of_amenability);
		}
	
	}
	
}




function show_fees_registration($application_id,$service_id,$factory_type_id,$reference_no,$previous_excess_paid,$date_of_amenability){


	 $previous_amount_pre 				= $previous_excess_paid;
	$Registration_fees 					= 	0;
	$created_by 						=   $user->uid;
	$modifi_date 						=   date("Y-m-d",strtotime($date_of_amenability));
	$i									=	1;
	if($modifi_date>='2016-12-30'){
		$Registration_fees =1000;
	}
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
							<th>Transfer</th>
							<th>Previous Excess Paid(Rs.)</th>
							<th>Balance(Rs)</th>
							<th>Due Amount(Rs)</th>
						</tr>';
 
	$power_details		= yearly_power_worker_details($application_id,$factory_type_id,$service_id,$reference_no);
	
	$license_fees 		= 0;
	$late_fees			= 0;
	$current_year 		= date("Y");
	$fees 				= 0;
	$i					= 1;  
	$total_license_fees  = 0;
	$total_transfer_fees =0;
	
	foreach($power_details as $rows){	
		if($rows->type_power_station == "other"){	
				$power_hp_kw 			= $rows->installed_power_hp;
				$unit 		 			= 'Hp';
				$result_data 			= fees_calculation_registration($rows->installed_power_hp,$rows->worker_total,$rows->calculate_starting_year);
				
				$fees		 	 		= $result_data['fees']*$rows->valid_time_period;
				
				$late_fees_pay = 0;
				if(!empty($previous_amount_pre)){
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
								
								
								if($rows->calculate_starting_year > '2016-12-31'){
									$start_date				= date_create($rows->calculate_starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
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
											$late_fees_pay = $result_data['fees']*$fees_late_year; 
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 $late_fees_pay = $result_data['fees']*$fees_late_year;
										}
										}
										
										
										
									else{ 
									  $late_fees_pay = $result_data['fees'];
								}	
								}
										
								
								
						}
					}
				$payble_fees 	= $fees+$late_fees_pay+$total_transfer_fees+$Registration_fees; 
					if($previous_amount_pre>$payble_fees){
							$late_fees_pay 		= $late_fees_pay;
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
								$late_fees_pay 		= $late_fees_pay;
							
					}
				}
				if(empty($previous_amount_pre)){
						$datex 					= new DateTime($rows->calculate_starting_year);
						
						$datey 					= new DateTime('2015-12-31');
						$previous_amount_pre 	= 0;
					 	$late_fees_pay 			= 0;
					if($datex>$datey){
						 $datez = new DateTime(date('Y-m-d'));
					
						$date_valid_year = new DateTime($rows->valid_year);
						$dateamenability= new DateTime($date_of_amenability);
						
							 $late_fees_pay = 0;
							if($datez>$datex){
								
								
								if($rows->calculate_starting_year > '2016-12-31'){
									$start_date				= date_create($rows->calculate_starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
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
											$late_fees_pay = $result_data['fees']*$fees_late_year; 
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 $late_fees_pay = $result_data['fees']*$fees_late_year;
										}
										}
										
										
										
									else{ 
									  $late_fees_pay = $result_data['fees'];
								}	
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
						<td>'.$power_hp_kw.'('.$unit.')</td>
						<td>'.$rows->worker_total.'</td>
						<td>'.$Registration_fees.'</td>
						<td>'.$fees.'  ('.$result_data['fees'].'*'.$rows->valid_time_period.')</td>
						<td>'.$late_fees_pay.'</td>
						<td>'.$total_transfer_fees.'</td>
						<td>'.$previous_amount_pre.'</td>
						<td>'.$balance_amount.'</td>
						<td>'.$due_amount.'</td>';	
										
					
		$output .='</tr>';
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$Registration_fees 		=0;
		
	  }	
	    if($rows->type_power_station == "power_generating_station"){
							$power_hp_kw 			= $rows->installed_power;
				$unit 		 			= 'KW';
				$result_data 			= fees_calculation_registration_power_station($rows->installed_power,$rows->calculate_starting_year);
				$fees		 	 		= $result_data['fees']*$rows->valid_time_period;
				$max_payment_date 		= get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
				if(!empty($previous_amount_pre)){	
					$datex 				= new DateTime($rows->calculate_starting_year);
		 			$datey 				= new DateTime('2015-12-31');
					$datez 				= new DateTime(date('Y-m-d'));
					$late_fees 			= 0; 
					if($datex>$datey){
						$datez = new DateTime(date('Y-m-d'));
						if($datez>$datex){
									$start_date				= date_create($rows->calculate_starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
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
										
										
									
									else{
									  $late_fees = $fees;
								}	
								
										
								
								
						}
					}					 $payble_fees 	= $fees+$late_fees+$Registration_fees;
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
					$datex = new DateTime($rows->calculate_starting_year);
					$datey = new DateTime('2015-12-31');
					$previous_amount_pre =0;
					 $late_fees_pay = 0;
					if($datex>$datey){
						$datez 				= new DateTime(date('Y-m-d'));
						$late_fees_pay 		= 0;
							if($datez>$datex){
									$start_date				= date_create($rows->calculate_starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
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
											$late_fees_pay = $result_data['fees']*$fees_late_year; 
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 $late_fees_pay = $result_data['fees']*$fees_late_year;
										}
										}
										
										
									
									else{
									  $late_fees_pay = $result_data['fees'];
								}	
								
										
								
								
						}
					
				$due_amount 	= $fees+$late_fees_pay+$Registration_fees;
				$balance_amount = 0;
				
			}else{
				$due_amount 	= $fees+$total_transfer_fees+$Registration_fees;
				$balance_amount = 0;
				$late_fees_pay 	= 0;
			}
			
					
	}
		$output .='<tr>
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
										
					
		$output .='</tr>';
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$Registration_fees 		=0;
		$late_fees_pay =0;
	  }	
	   	$i= $i+1;
   }
	$output .='</table><strong><font color="#FF0000">Fees to be paid:-'.($fees_to_paid).'</font></strong>
				</div>';
		
	return $output;
	
}

function show_fees_registration_2mii($application_id,$service_id,$factory_type_id,$reference_no,$total_payment,$date_of_amenability){
	$i= 1;
		$output = '<div class="box-body">
						<table class="table table-bordered" width="100%">
							<tr>
				<th>SL</th>
  				<th>Application Period</th>
   				<th>Total Workers</th>
				<th>Registration Fees</th>
    			<th>Schedule Fees(Rs)<br>(calculated fess * total application year)</th>
				<th>Late Fees(Rs)</th>
				<th>Previous Excess Paid(Rs.)</th>
				<th>Balance(Rs)</th>
				<th>Due Amount(Rs)</th>
  	 		</tr>';
	$license_fees 			= 	0;
	$Registration_fees 	=	0;
	$fees 					=	0;
	
	$worker_detials 		= worker_detials_for_fees2mii($application_id,$reference_no,$factory_type_id,$service_id);

	$due_amount 			= 0;
	if(empty($total_payment)|| $total_payment == NULL){
		$previous_amount_pre 	= 0;
	}else{
		$previous_amount_pre 	= $total_payment;
	}
	

	$modifi_date 			=   date("Y-m-d",strtotime($date_of_amenability));

	if($modifi_date>='2016-12-30'){ 
			$Registration_fees =1000;
	}

	$max_payment_date 		= get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);

	foreach($worker_detials as $worker1){
	$schedule_fees 			= fees_calculation_registration_2mii($worker1->start_year,$worker1->total_worker);
	
	
	$fees1 					= $schedule_fees['fees']*$worker1->vaild_period;
	$datex 					= new DateTime($worker1->start_year);
	$datey 					= new DateTime('2015-12-31');
	$application_date 	    = date('Y-m-d');
	if(empty($previous_amount_pre)){
		 if($datex>$datey){
				 $datez = new DateTime(date('Y-m-d'));
				 $date_valid_year = new DateTime($worker1->valid_year);
						$dateamenability= new DateTime($date_of_amenability);
						
							 $late_fees_pay = 0;
							if($datez>$datex){
								
								if($worker1->vaild_period>1){
									if($worker1->start_year > '2016-12-31'){
									$start_date				= date_create($worker1->start_year);
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
											$late_fees_pay = $schedule_fees['fees']*$fees_late_year; 
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 $late_fees_pay = $schedule_fees['fees']*$fees_late_year;
										}
										
										
								}
								}
								
										
								else{ 
									  $late_fees_pay = $schedule_fees['fees'];
								}
								
								
								
						}
					
				 $due_amount 	= $fees1+$late_fees_pay+$total_transfer_fees+$Registration_fees;
				$balance_amount = 0;
				
			}else{
				$due_amount 	= $fees+$total_transfer_fees+$Registration_fees;
				$balance_amount = 0;
				$late_fees_pay 	= 0;
			}
	}
    if(!empty($previous_amount_pre)){
					$datex 				= new DateTime($worker1->start_year);
		 			$datey 				= new DateTime('2015-12-31');
					$datez 				= new DateTime(date('Y-m-d'));
					$dateamenability	= new DateTime($date_of_amenability);
					$late_fees 			= 0;
					if($datex>$datey){
						$datez = new DateTime(date('Y-m-d'));
						$date_valid_year = new DateTime($worker1->valid_year);
						$dateamenability= new DateTime($date_of_amenability);
							
							 $late_fees_pay = 0;
							if($datez>$datex){
								
								if($worker1->vaild_period>1){ 
									if($worker1->start_year > '2016-12-31'){
									$start_date				= date_create($worker1->start_year);
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
											$late_fees_pay = $schedule_fees['fees']*$fees_late_year; 
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 $late_fees_pay = $schedule_fees['fees']*$fees_late_year;
										}
										
										
								}
								}
										
								else{
									   $late_fees_pay = $schedule_fees['fees'];
								}
								
								
								
						}
					}
					else{
						$late_fees_pay = 0;
					}
					 $payble_fees 	= $fees1+$late_fees_pay+$total_transfer_fees+$Registration_fees;
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
				}
	
	$output .='<tr>
				<td>'.$i.'</td>
				<td>'.$worker1->application_period.'</td>
				<td>'.$worker1->total_worker.'</td>
				<td>'.$Registration_fees.'</td>
				<td>'.$fees1.'('.$schedule_fees['fees'].'*'.$worker1->vaild_period.')</td>
				<td>'.$late_fees_pay.'</td>
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
	
	$total_fees = $total_fees+$total_due_fees;
	$output .=' </table>
		<strong><font color="#FF0000">Fees to be paid (Total Due amount +  Registration fees + Total transfer fees) :-  '.$total_fees.'</font></strong>
				</div>';
				
	return $output;
	
	}


function show_fees_registration_section_85($application_id,$service_id,$factory_type_id,$reference_no,$total_payment,$date_of_amenability){
	
	global $base_root, $base_path, $user;
	 $previous_amount_pre 				= 	$total_payment;
	$total_ownership_transfer_fees		=	0;
	$Registration_fees 					= 	0;
	$created_by 						=   $user->uid;
	$modifi_date 						=   date("Y-m-d",strtotime($date_of_amenability));
	$i									=	1;
	$remark 							=	'';
	$application_date					= date('Y-m-d');

	
	if($modifi_date>='2016-12-30'){
			$Registration_fees =1000;
	}
	
	$power_details			= yearly_power_worker_details($application_id,$factory_type_id,$service_id,$reference_no);
	
	

	$total_transfer_fees 	= 0;

					
	
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
	
	   $fees_fetach 			= fees_calculation_registration_2mii($worker1->calculate_starting_year,$worker1->total_worker);
		$remark			=  'Section-2m(ii)'	;
		
	}if($worker_total>=10 && $installed_power>0){//2m(i)
		if($rows->power_unit == 'HP'){
		
			
		$fees_fetach 			= fees_calculation_registration($rows->installed_power_hp,$rows->worker_total,$rows->calculate_starting_year);	
		}if($rows->power_unit == 'KW'){
			
			$fees_fetach 			= fees_calculation_registration_power_station($rows->installed_power,$rows->worker_total,$rows->calculate_starting_year);
			
		}
		$remark			=  'Section-2m(i)'	;
	
	}if($worker_total<=9 && $installed_power>=0){//section85
		 
		$fees_fetach 	=	fees_calculation_registration_section_85($rows->calculate_starting_year);
		$remark			=  'Section-85'	;
	}if($worker_total<=19 && $installed_power==0){//section85
		$fees_fetach 	=	fees_calculation_registration_section_85($rows->calculate_starting_year);
		$remark			=  'Section-85'	;
	}
	$fees				=   $fees_fetach['fees']*$rows->valid_time_period;
	
	if(!empty($previous_amount_pre)){
					$datex 				= new DateTime($rows->calculate_starting_year);
		 			$datey 				= new DateTime('2015-12-31');
					$datez 				= new DateTime(date('Y-m-d'));
					$dateamenability	= new DateTime($date_of_amenability);
					$late_fees 			= 0;
					
					if($datez>$datex){
								if($rows->valid_time_period>1){
									
									$start_date				= date_create($rows->calculate_starting_year);
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
										
										
								
								}
										
								else{
									   $late_fees_pay = $fees;
								}
						}
					$payble_fees 	= $fees+$late_fees_pay+$total_transfer_fees+$Registration_fees;
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
									
									$start_date				= date_create($rows->calculate_starting_year);
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
						<td>'.$rows->installed_power.'</td>
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
			<strong><font color="#FF0000">Fees to be paid(Total Due amount+Registration Fees):-'.($total_due_fees+$Registration_fees).'</font></strong></div></div>';
	return $output;			
	
}



function save_pay_amount_details_85($application_id,$service_id,$factory_typeid,$reference_number,$date_of_amenability,$previousexcess_paid_hidden){
	global $base_root, $base_path, $user;
	
	$toatl_fees_breakup = toatl_fees_breakup($application_id,$service_id,$factory_typeid,$reference_number);
	foreach($toatl_fees_breakup as $row_fees){ $row_fees_id=$row_fees->id;
		$fees_deatils = array('fees_status'=>0);

				$queryabc 		 =	db_update('fa_calculates_license_fees');
				$queryabc		->	fields($fees_deatils);
				$queryabc		->	condition('id',$row_fees_id,'=');
				$queryabc		->	execute();
	}
	
	$previous_amount_pre				= 	$previousexcess_paid_hidden;
	$total_ownership_transfer_fees		=	0;
	$Registration_fees 					= 	0;
	$created_by 						=   $user->uid;
	$modifi_date 						=   date("Y-m-d",strtotime($date_of_amenability));
	$i									=	1;
	if($modifi_date>='2016-12-30'){
			$Registration_fees =$Registration_fees1=1000;
	}
	
	$power_details		= yearly_power_worker_details($application_id,$factory_typeid,$service_id,$reference_number);
	

	foreach($power_details as $rows){
		$installed_power 	=   $rows->installed_power;
		$worker_total 		=   $rows->worker_total;
		
	
	if($worker_total>=20 && $installed_power==0){//2m(ii)
	    $fees_fetach 	=  fees_calculation_registration_2mii($rows->calculate_starting_year,$rows->worker_total);
		$remark			=  'Section-2m(ii)'	;
				
	}if($worker_total>=10 && $installed_power>0){//2m(i)
		if($rows->power_unit == 'HP'){
			$fees_fetach  = fees_calculation_registration($rows->service_year,$rows->installed_power_hp,$rows->worker_total,$rows->calculate_starting_year);
		}if($rows->power_unit == 'KW'){
			
			$fees_fetach 			= fees_calculation_registration_power_station($rows->installed_power,$rows->worker_total,$rows->calculate_starting_year);
		}
		$remark			=  'Section-2m(i)'	;
	
	}if($worker_total<=9 && $installed_power>=0){//section85
		$fees_fetach 	=	fees_calculation_registration_section_85($rows->calculate_starting_year);
		
		$remark			=  'Section-85'	;
	}if($worker_total<=19 && $installed_power==0){//section85
		$fees_fetach 	=	fees_calculation_registration_section_85($rows->calculate_starting_year);
		$remark			=  'Section-85'	;
	}
	
	$fees				=   $fees_fetach['fees']*$rows->valid_time_period;
	
	
	if(!empty($previous_amount_pre)){
					$datex 				= new DateTime($rows->calculate_starting_year);
		 			$datey 				= new DateTime('2015-12-31');
					$datez 				= new DateTime(date('Y-m-d'));
					$dateamenability	= new DateTime($date_of_amenability);
					$late_fees 			= 0;
					if($datex>$datey){
						$datez 				= new DateTime(date('Y-m-d'));
						$date_valid_year 	= new DateTime($rows->calculate_end_year);
						 if($datez>$datex){ 
								if($rows->valid_time_period>1){
									
									$start_date				= date_create($rows->calculate_starting_year);
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
	if(empty($previous_amount_pre)){
				$datex 					= new DateTime($rows->calculate_starting_year);
				$datey 					= new DateTime('2015-12-31');
				$previous_amount_pre 	= 0;
				$late_fees_pay 			= 0;
				if($datex>$datey){
						$datez 				= new DateTime(date('Y-m-d'));
						$date_valid_year 	= new DateTime($rows->calculate_end_year);
						 if($datez>$datex){ 
								if($rows->valid_time_period>1){
									
									$start_date				= date_create($rows->calculate_starting_year);
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
										
										
								
								}
										
								else{
									   $late_fees_pay = $fees_fetach['fees'];
								}
						}
					}else{
				$due_amount 	= $fees+$total_transfer_fees+$Registration_fees+$late_fees;
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
			'service_year' 	             => $rows->calculate_year,
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
			'remark'					 => $remark,
			
			
			
		);
		
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
}
if(empty($fees_to_paid)){
	$fees_to_paid = 0;
}


	$fees_deatils = array('service_fees'=>$Registration_fees1,'previous_excess_paid'=>$previousexcess_paid_hidden,'payment_amount'=>$fees_to_paid,'is_previous_payment'=>'Yes','balance_amount'=>$balance_amount,'is_notesheet_amount'=> 0,'application_status'=>'P','modification_date'=>date('Y-m-d'));


//print_r($fees_deatils);die;
				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		->	fields($fees_deatils);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc		->	execute();
				
		remark_input($reference_number,$application_id,'P','Repayment sucessfully completed');
		fun_grip_input($fees_to_paid,$application_id,$service_id,$reference_number,$factory_typeid);				
drupal_goto('applicant/view-payment-breakup/' .encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_typeid).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_number));
}
function save_apy_ment_details_2mi($application_id,$service_id,$factory_type,$reference_no,$date_of_amenability,$previousexcess_paid_hidden){	
	global $base_root, $base_path, $user;
	 $previous_amount_pre 				= 	$previousexcess_paid_hidden;
	$Registration_fees 					= 	0;
	$created_by 						=   $user->uid;
	$modifi_date 						=   date("Y-m-d",strtotime($date_of_amenability));
	$i									=	1;
	$toatla_transfer_fees				=	0;
	if($modifi_date>='2016-12-30'){
		$Registration_fees =$Registration_fees1=1000;
	}
	
	
	
	$toatl_fees_breakup = toatl_fees_breakup($application_id,$service_id,$factory_type,$reference_no);
	foreach($toatl_fees_breakup as $row_fees){$row_fees_id=$row_fees->id;
				$fees_deatils = array('fees_status'=>0);

				$queryabc 		 =	db_update('fa_calculates_license_fees');
				$queryabc		->	fields($fees_deatils);
				$queryabc		->	condition('id',$row_fees_id,'=');
				$queryabc		->	execute();
	}
 
	$power_details		= yearly_power_worker_details($application_id,$factory_type,$service_id,$reference_no);
	
	$license_fees 		= 0;
	$late_fees			= 0;
	$current_year 		= date("Y");
	$fees 				= 0;
	$i					= 1;
	

	$total_license_fees  = 0;
	foreach($power_details as $rows){		
		$power_hp_kw = $rows->installed_power_hp;
		if($rows->type_power_station == "other"){
				$unit 		 	= 'Hp';
				$result_data 	= fees_calculation_registration($rows->installed_power_hp,$rows->worker_total,$rows->calculate_starting_year);
				$fees		 	= $result_data['fees']*$rows->valid_time_period;
				$max_payment_date = get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
				$late_fees_pay = 0;
				if(!empty($previous_amount_pre)){
					$datex 				= new DateTime($rows->calculate_starting_year);
		 			$datey 				= new DateTime('2015-12-31');
					$datez 				= new DateTime(date('Y-m-d'));
					$dateamenability	= new DateTime($date_of_amenability);
					
					if($datez>$datex){
								
								
								if($rows->calculate_starting_year > '2016-12-31'){
									$start_date				= date_create($rows->calculate_starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
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
											$late_fees_pay = $result_data['fees']*$fees_late_year; 
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 $late_fees_pay = $result_data['fees']*$fees_late_year;
										}
										}
										
										
										
									else{ 
									  $late_fees_pay = $result_data['fees'];
								}	
								}
										
								
								
						}
					$payble_fees 	= $fees+$late_fees_pay+$total_transfer_fees+$Registration_fees;
					if($previous_amount_pre>$payble_fees){
							$late_fees_pay 		= $late_fees_pay;
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
								$late_fees_pay 		= $late_fees_pay;
							
					}
				}
				if(empty($previous_amount_pre)){
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
								
								
								if($rows->calculate_starting_year > '2016-12-31'){
									$start_date				= date_create($rows->calculate_starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
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
											$late_fees_pay = $result_data['fees']*$fees_late_year; 
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 $late_fees_pay = $result_data['fees']*$fees_late_year;
										}
										}
										
										
										
									else{ 
									  $late_fees_pay = $result_data['fees'];
								}	
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
		
		$previous_amount_pre = $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$Registration_fees 		= 0;
		$late_fees				= 0;
		$total_transfer_fees 	= 0;
		
			
	  }
	   	if($rows->type_power_station == "power_generating_station"){
				$unit 		 			= 'KW';
				$result_data 			= fees_calculation_registration_power_station($rows->installed_power,$rows->calculate_starting_year);
				
				$fees		 			= $result_data['fees']*$rows->valid_time_period;
				$max_payment_date = get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
				if(!empty($previous_amount_pre)){
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
									$start_date				= date_create($rows->calculate_starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
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
										
										
									
									else{
									  $late_fees = $result_data['fees'];
								}	
								
										
								
								
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
				if(empty($previous_amount_pre)){
					$datex = new DateTime($rows->calculate_starting_year);
					$datey = new DateTime('2015-12-31');
					$previous_amount_pre =0;
					 $late_fees_pay = 0;
					if($datex>$datey){
						$datez = new DateTime(date('Y-m-d'));
						$dateamenability= new DateTime($date_of_amenability);
						
							 $late_fees_pay = 0;
							if($datez>$datex){
									$start_date				= date_create($rows->calculate_starting_year);
										$application_date1		= date_create($application_date);
										$diff					= date_diff($application_date1,$start_date);
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
											$late_fees_pay = $result_data['fees']*$fees_late_year; 
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 $late_fees_pay = $result_data['fees']*$fees_late_year;
										}
										}
										
										
									
									else{
									  $late_fees_pay = $result_data['fees'];
								}	
								
										
								
								
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
		//print_r($calculate_fees_details);
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
		
		$previous_amount_pre = $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$Registration_fees 		= 0;
			
	  }
	
}


if(empty($previousexcess_paid_hidden) || $previousexcess_paid_hidden==NULL || $previousexcess_paid_hidden==0){
	
	$fees_deatils = array('service_fees'=>$Registration_fees1,'payment_amount'=>$fees_to_paid,'is_previous_payment'=>'No','balance_amount'=>$balance_amount,'is_notesheet_amount'=> 0,'application_status' => 'P','modification_date'=>date('Y-m-d'));
}
else{
	$fees_deatils = array('service_fees'=>$Registration_fees1,'previous_excess_paid'=>$previousexcess_paid_hidden,'payment_amount'=>$fees_to_paid,'is_previous_payment'=>'Yes','balance_amount'=>$balance_amount,'is_notesheet_amount'=> 0,'application_status' => 'P','modification_date'=>date('Y-m-d'));
}
//print_r($fees_deatils);die();
	
				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		->	fields($fees_deatils);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc		->	execute();
	remark_input($reference_no,$application_id,'P','Repayment sucessfully completed');	
	fun_grip_input($fees_to_paid,$application_id,$service_id,$reference_no,$factory_type);		

	drupal_goto('applicant/view-payment-breakup/' .encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_no));

	//drupal_goto('epayments_preview/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$reference_number).'/'.encryption_decryption_fun('encrypt',$factory_typeid));
	
	
}
function save_apy_ment_details_2mii($application_id,$service_id,$factory_typeid,$reference_number,$previous_excess_paid,$date_of_amenability){
	
	global $base_root, $base_path, $user;
	$i= 1;
	$license_fees 			= 	0;
	$Registration_fees 		=	0;
	$fees 					=	0;
	
	$toatl_fees_breakup = toatl_fees_breakup($application_id,$service_id,$factory_typeid,$reference_number);
	foreach($toatl_fees_breakup as $row_fees){ $row_fees_id=$row_fees->id;
		$fees_deatils = array('fees_status'=>0);

				$queryabc 		 =	db_update('fa_calculates_license_fees');
				$queryabc		->	fields($fees_deatils);
				$queryabc		->	condition('id',$row_fees_id,'=');
				$queryabc		->	execute();
	}
	$worker_detials 		= worker_detials_for_fees2mii($application_id,$reference_number,$factory_typeid,$service_id);
		
	$due_amount 			= 0;
	if(empty($previous_excess_paid)|| $previous_excess_paid == NULL){
		$previous_amount_pre 	= 0;
	}else{
		$previous_amount_pre 	= $previous_excess_paid;
	}
	
$modifi_date 			=   date("Y-m-d",strtotime($date_of_amenability));

	if($modifi_date>='2016-12-30'){ 
			$Registration_fees=$Registration_fees1 =1000;
	}else{
		$Registration_fees=$Registration_fees1 = 0;
	}

	$max_payment_date 		= get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);

	foreach($worker_detials as $worker){
	$schedule_fees 			= fees_calculation_registration_2mii($worker->start_year,$worker->total_worker);
	
	
	$fees 					= $schedule_fees['fees']*$worker->vaild_period;
	$datex 					= new DateTime($worker->start_year);
	$datey 					= new DateTime('2015-12-31');
	$application_date 	    = date('Y-m-d');
	if(empty($previous_amount_pre)){
		 if($datex>$datey){
				 $datez = new DateTime(date('Y-m-d'));
				 $date_valid_year = new DateTime($rows->valid_year);
						
						
							 $late_fees_pay = 0;
							if($datez>$datex){
								
								if($worker->vaild_period>1){
									if($worker->start_year > '2016-12-31'){
									$start_date				= date_create($worker->start_year);
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
											 $late_fees_pay = $schedule_fees['fees']*$fees_late_year;
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 $late_fees_pay = $schedule_fees['fees']*$fees_late_year;
										}
										
										
								}
								}
								
										
								else{
									 $late_fees_pay = $schedule_fees['fees'];
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
	
	 if(!empty($previous_amount_pre)){
					$datex 				= new DateTime($worker->start_year);
		 			$datey 				= new DateTime('2015-12-31');
					$datez 				= new DateTime(date('Y-m-d'));
					$dateamenability	= new DateTime($date_of_amenability);
					$late_fees 			= 0;
					if($datex>$datey){
						$datez = new DateTime(date('Y-m-d'));
						$date_valid_year = new DateTime($worker->valid_year);
						$dateamenability= new DateTime($date_of_amenability);
											
							 $late_fees_pay = 0;
							if($datez>$datex){
								
								if($worker->vaild_period>1){
									
										$start_date				= date_create($worker->start_year);
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
											 $late_fees_pay = $schedule_fees['fees']*$fees_late_year;
										}if($late_year<0){
											$fees_late_year = 0;
											if($late_month>0){
												$fees_late_year = 1;
											}if($late_month<0 && $late_day >0){
												$fees_late_year = 1;
											}
											 $late_fees_pay = $schedule_fees['fees']*$fees_late_year;
										}
										
										
								
								}
								
										
								else{
									  $late_fees_pay = $schedule_fees['fees'];
								}
								
								
								
						}
					}
					else{
						$late_fees_pay = 0;
					}
					$payble_fees 	= $fees+$late_fees_pay+$total_transfer_fees+$Registration_fees;
				
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
				}
	  if($schedule_fees['workers_end_to'] == -1){
			$max_worker = $worker->total_worker." and onwords";
		}else{
			$max_worker = $schedule_fees['workers_end_to'];
		}
		
		$calculate_fees_details = array(
			'feesyear' 		             => $schedule_fees['feesyear'],
			'schedule_fees' 		     => $fees,
			'late_fees'              	 => $late_fees_pay,
			'service_id' 		     	 => $service_id,
			'application_id'             => $application_id,
			'service_year' 	             => $worker->application_period,
			'factory_type'				 => $factory_typeid,
			'application_reference_no'	 => $reference_number,
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
		//print_r($calculate_fees_details);
	
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
		$previous_amount_pre 	= $balance_amount;
		$total_late_fees 		= $late_fees_pay+$total_late_fees;
	 	$total_license_fees 	= ($fees+$total_late_fees)+$total_license_fees;
		$total_due_fees 		= $due_amount+$total_due_fees;
		$fees_to_paid			= $total_due_fees;
		$Registration_fees 		=0;
		$i = $i+1;
	}
	//die();	
	// $fees_to_paid = $fees_to_paid+$previous_excess_paid;
	

	if(empty($previous_excess_paid) || $previous_excess_paid==NULL || $previous_excess_paid==0){
	
	$fees_deatils = array('service_fees'=>$Registration_fees1,'payment_amount'=>$fees_to_paid,'is_previous_payment'=>'No','balance_amount'=>$balance_amount,'is_notesheet_amount'=> 0,'application_status'=>'P','modification_date'=>date('Y-m-d'));
}
else{
	$fees_deatils = array('service_fees'=>$Registration_fees1,'previous_excess_paid'=>$previous_excess_paid,'payment_amount'=>$fees_to_paid,'is_previous_payment'=>'Yes','balance_amount'=>$balance_amount,'is_notesheet_amount'=> 0,'application_status'=>'P','modification_date'=>date('Y-m-d'));
}
				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		->	fields($fees_deatils);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc		->	execute();
	//print_r($fees_deatils);die();			
remark_input($reference_number,$application_id,'P','Repayment sucessfully completed');
fun_grip_input($fees_to_paid,$application_id,$service_id,$reference_number,$factory_typeid);	
	drupal_goto('applicant/view-payment-breakup/' .encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_typeid).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_number));
				
	
	
	}
	
