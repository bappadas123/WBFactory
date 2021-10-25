<?php
function show_fees_registration($application_id,$service_id,$factory_typeid,$reference_number,$date_of_amenability,$period_for_application,$previous_excess_paid,$last_validlicensedate){
	//echo $last_validlicensedate;die(1);

	$previous_amount_pre 				=   $previous_excess_paid;
	$Registration_fees 					= 	0;
	$created_by 						=   $user->uid;
	$modifi_date 						=   date("Y-m-d",strtotime($date_of_amenability));
	$last_validity						=   date("Y-m-d",strtotime($last_validlicensedate));
	$i									=	1;
	/*if($modifi_date>='2016-12-30'){
		$Registration_fees =1000;
	}*/
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
 
	$power_details		= yearly_power_worker_details($application_id,$factory_typeid,$service_id,$reference_number);
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
	$last_validity_year  	= date('Y',strtotime($last_validity));
	//$last_validity_year  	= date('Y',strtotime('2015-12-31'));
	//$payment = 1;
	$flag_payment  			= '';
	$payment = 0;
	$late_flag = 0;
	$flag_balance = 0;
	$fees_to_paid =0;
	$due_flag = 0;
	$previous_amount_flag =0;
	if($other == "other"){
			if($last_validity == '2018-12-31'){
				 
				// $application_date 		= date('Y-m-d',strtotime(date("Y-m-d", strtotime('2019-01-15'))));
				 $application_date 		= date('Y-m-d');
				 $power_hp_kw  			= $rows->installed_power_hp;
				 $unit 		  			= 'Hp';
				 $previous_amount_pre	= 0;
				 $max_payment_date 		= get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_number);
				 $payment 				= 0;
				 
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
								//$previous_amount_pre = $previous_excess_paid;
								foreach($power_details as $rows){
									$result_data  = fees_calculation_registration($rows->installed_power_hp,$rows->worker_total,$rows->calculate_starting_year);
									$license_fees = $result_data['fees']*$rows->valid_time_period;
									/*if($application_date <= $datey_cuttoff){
										$payble_fees 	= $license_fees;
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
									
									}*///if{
										
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
			
			if($last_validity_year > '2018'){
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
			if($last_validity_year <= '2015'){ //echo 'hi';
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
									 	$due_amount 	= $late_fees_pay+$license_fees;
										$balance_amount = $balance_license_amount;
										$late_flag = 1;
						 			}if($manual_payment[$payment]->date_payment>$cut_off_date ){
										  $late_fees_pay 	= ($due_license_amount)*(50/100);
										  $due_amount 			= $late_fees_pay+$license_fees;
										  $balance_amount 		= $balance_license_amount;
										 $late_flag 			= 1;
										// echo 'late2(12c)<br>';echo 'due license amount'.$due_amount.'<br/>';	;
											
					 				}
								}
									
									
									if($due_amount>$manual_payment[$payment]->payment_amount){//echo 'pay(12d)<br>';
										//echo 'location---'.$payment.'<br/>';echo $previous_amount_pre.'<br/>';
										//echo 'due amount----'.$due_amount;	echo '<br/>';
										
										   //echo $previous_amount_pre 	= $previous_amount_pre+$manual_payment[$payment]->payment_amount;
										// echo $previous_amount_pre.'---'.$manual_payment[$payment]->payment_amount.'<br/>';
										//echo '<br/>';
										//  $due_amount 	= $due_amount - $manual_payment[$payment]->payment_amount;
										//echo '<br/>';
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
									 	$due_amount 		= $late_fees_pay+$license_fees;
										$balance_amount = $balance_license_amount;
										$late_flag = 1;
						 			}if($application_date>$cut_off_date ){
										 $late_fees_pay = ($due_license_amount)*(50/100);
										//echo '<br/>';
										 $due_amount 	= $late_fees_pay+$license_fees;
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
									$due_amount 	= $late_fees_pay+$license_fees;
									$balance_amount = $balance_license_amount;
						 		}if($application_date>$cut_off_date ){
									$late_fees_pay 	= ($due_license_amount)*(50/100);
									$due_amount 	= $late_fees_pay+$license_fees;
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
						// $r = '('.$late_fees_pay.'+'.$license_fees.')='.$late_fees_pay+$license_fees;
							$due_amount_paid = $due_amount+$due_amount_paid;
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
   //}//die();
	$output .='</table>
	
				<strong><font color="#FF0000">Fees to be paid:-'.($fees_to_paid).'</font></strong>
				</div></div>'
				;
			
		
	return $output;
	
}
function get_max_payment_date($application_id,$service_id,$factory_typeid,$reference_no){//echo 
	
	$query_payment 		= db_select('fa_manual_payment_history');
	$query_payment		-> addExpression('MAX(date_payment)');
	$query_payment	    -> condition('application_id', $application_id);
	$query_payment	 	-> condition('service_id', $service_id);
	$query_payment	 	-> condition('factory_type', $factory_typeid);
	$query_payment	 	-> condition('application_reference_no', $reference_no);
	$max_payment_date	= $query_payment->execute()->fetchField();
	return $max_payment_date;
}
function manual_payment_deatils($application_id,$service_id,$factory_typeid,$reference_no){//echo $application_id.'------------------'.$service_id.'--------------------'.$factory_typeid.'-------------------'.$reference_no;
	$query_payment 	=  db_select('fa_manual_payment_history', 'payment_history');
	$query_payment	    -> fields('payment_history',array('id','is_payment_mad','brn_grn_challan_no','date_payment','payment_amount','upload_challan_file'));
	$query_payment	    -> condition('payment_history.application_id', $application_id);
	$query_payment	 	-> condition('payment_history.service_id', $service_id);
	$query_payment	 	-> condition('payment_history.factory_type', $factory_typeid);
	$query_payment	 	-> condition('payment_history.application_reference_no', $reference_no);
	$query_payment_deatils  		=  $query_payment->execute()->fetchAll();

//print_r($query_payment->execute());die();
	return $query_payment_deatils;
	//print
}
function yearly_power_worker_details($application_id,$factory_type,$service_id,$application_reference_no){//echo 'hii';die();

//die($application_id.'-----'.$factory_type.'-----'.$service_id.'-----'.$application_reference_no);
	$query_power 			=  db_select('power_worker_yearly', 'power');
	$query_power			-> fields('power',array('installed_power_hp','calculate_year','worker_total','type_power_station','installed_power','valid_time_period','calculate_starting_year','calculate_end_year'));
	//$query_power			-> fields('power',array());
	$query_power			-> condition('power.application_id', $application_id);
	$query_power			-> condition('power.application_reference_no', $application_reference_no);
	$query_power			-> condition('power.factory_type', $factory_type);
	$query_power			-> condition('power.service_id', $service_id);
	$query_power   			-> orderBy('calculate_year', 'ASC');//ORDER BY created
	
	//echo $query_power;exit;
	$query_power_details 	=  $query_power->execute()->fetchAll();
	//print_r($query_power_details);die();
	//
	return $query_power_details;
}

?>