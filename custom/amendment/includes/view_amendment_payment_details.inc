<?php

function view_amendment_payment_details($form, &$form_state,$serviceid,$factory_typeid,$applicationid,$referenceno) {	
	global $base_root, $base_path, $user;
	//echo 'dd';die;
	
	$application_id 			= encryption_decryption_fun('decrypt', $applicationid);
	$service_id 				= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 			= encryption_decryption_fun('decrypt',$factory_typeid);
	$reference_no 				= encryption_decryption_fun('decrypt',$referenceno);
	$get_fa_cafa 				= get_fa_cafa($application_id);
    $reference_no 				= $get_fa_cafa['reference_number'];
	$date_of_amenability 		= $get_fa_cafa['date_of_amenability'];
	$period_for_application 	= $get_fa_cafa['period_for_application'];
	$previous_excess_paid		= $get_fa_cafa['previous_excess_paid'];
	$is_calculate				= $get_fa_cafa['is_calculate'];
	$service_fees				= $get_fa_cafa['service_fees'];
	$previous_payment_amount	= $get_fa_cafa['payment_amount'];
	$application_status			= $get_fa_cafa['application_status'];
	$total_payment				= $previous_payment_amount+$previous_excess_paid;
	
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
			'#prefix' 			=> '<div class = "box-body"><div class="box-header with-border">
              <h3 class="box-title">Fees Calculation for Amendment<br/> Amenability Date:-'.date("dS M Y",strtotime($date_of_amenability)).'<br/>Period of license:-'.$period_for_application.'Year(s)<br/>Amendment Fees:-'.$service_fees.'</h3>
            </div>',
	);
	$form['yearly_worker']['payment_deatails'] = array(
				'#type'				=> 'markup',
				'#markup' 			=> view_payment_deatils($application_id,$service_id,$factory_type_id,$reference_no),
			
		);
	if($factory_type_id ==1 || $factory_type_id == 3){
		if($application_status == 'RP' && $factory_type_id ==1){
			save_apy_ment_details_2mi($application_id,$service_id,$factory_type_id,$reference_no,$date_of_amenability,$period_for_application,$total_payment);
		}
		$form['yearly_worker']['worker_year_table'] 	= array(
		 		'#type'			=> 'markup',
				'#markup'		=> fee_details_breakup($application_id,$service_id,$factory_type_id,$reference_no,$service_fees)
			);
	}
	if($factory_type_id==2){
			$form['yearly_worker']['worker_year_table_2mii'] 	= array(
		 		'#type'			=> 'markup',
				'#markup'		=> fee_details_breakup_2mii($application_id,$service_id,$factory_type_id,$reference_no,$service_fees)
			);
	}
	if($factory_type_id == 3){
		$form['yearly_worker']['worker_year_table'] 	= array(
		 		'#type'			=> 'markup',
				'#markup'		=> fee_details_breakup_85($application_id,$service_id,$factory_type_id,$reference_no,$service_fees)
			);
	}
 return $form; 
        
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
	//print_r($manual_payment_deatils);die();
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
			array('data' => t(date("dS M Y",strtotime($history->date_payment)))),
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
function fee_details_breakup($application_id,$service_id,$factory_typeid,$reference_number,$service_fees){
	$get_fa_cafa 	= get_fa_cafa($application_id);
	$payment_date 	= date("dS M Y",strtotime($get_fa_cafa['payment_date']));
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
				<th>Registration Fees</th>
    			<th>Schedule Fees(Rs)</th>
				<th>Late Fees(Rs)</th>
				<th>Transfer Fees</th>
  				<th>Previous Excess Paid(Rs.)</th>
				<th>Balance(Rs)</th>
				
				<th>Due Amount(Rs)</th>
  	 			
 			</tr>';

$toatl_fees_breakup = toatl_fees_breakup($application_id,$service_id,$factory_typeid,$reference_number);
$sl=0;
$total_schedule_fees = 0;
$total_due_fees 	= 0;
$total_late_fees 	= 0;
$total_fees_to_paid 	= 0;

//echo $application_id.'----'.$service_id.'----'.$factory_typeid.'----'.$reference_number."NNNN<pre>";print_r($toatl_fees_breakup);exit;
foreach($toatl_fees_breakup as $total){
	$sl=$sl+1;
	$output.='<tr>
						<td>'.$sl.'</td>
		             	<td>'.$total->service_year.'</td>
						<td>'.$total->power.'</td>
						<td>'.$total->worker.'</td>
						<td>'.$total->service_fees.'</td>
						<td>'.$total->schedule_fees.'</td>
						<td>'.$total->late_fees.'</td>
						<td>'.$total->transfer_fees.'</td>
						<td>'.$total->previous_paid_fees.'</td>
						<td>'.$total->balance_amount.'</td>
						
						<td>'.$total->due_fees.'</td>';
						
										
			$total_schedule_fees 	= $total_schedule_fees+$total->schedule_fees ;
			$total_due_fees 		= $total_due_fees+$total->due_fees	;
			$total_late_fees 		= $total_late_fees+$total->late_fees ;
			
		$output.='</tr>';
	
}
$total_fees_to_paid = $total_due_fees	;
$output .=' 	
				</table> 
				<strong><font color="#FF0000">Paid Fees(Due fees):-'.$total_fees_to_paid.' ,Dated on '.$payment_date.' </font></strong>
				</div></div>'
				;
			
						
return $output;	
}
function fee_details_breakup_2mii($application_id,$service_id,$factory_typeid,$reference_number,$service_fees){
	$get_fa_cafa 	= get_fa_cafa($application_id);
	$payment_date 	= date("dS M Y",strtotime($get_fa_cafa['payment_date']));
	$output = '<div class="box-header with-border">
               </div>
			 <div class="box-body"><div class="table-responsive">
			<table class="table table-bordered" width="100%">
			<thead>
			<tr>
				<th colspan="10">License Fess Calculation</th>
			</tr>
			<tr>
				<th>SL</th>
  				<th>Application Period</th>
   				<th>Total Workers</th>
				<th>Registration Fees</th>
    			<th>Schedule Fees(Rs)</th>
				<th>Late Fees(Rs)</th>
				<th>Transfer</th>
  				<th>Previous Excess Paid(Rs.)</th>
				<th>Balance(Rs)</th>
				<th>Due Amount(Rs)</th>
  	 			
 			</tr>';

$toatl_fees_breakup = toatl_fees_breakup($application_id,$service_id,$factory_typeid,$reference_number);
$sl=0;
$total_schedule_fees = 0;
$total_due_fees 	= 0;
$total_late_fees 	= 0;
$total_fees_to_paid 	= 0;
foreach($toatl_fees_breakup as $total){
	$sl=$sl+1;
	$output.='<tr>
						<td>'.$sl.'</td>
		             	<td>'.$total->service_year.'</td>
						<td>'.$total->worker.'</td>
						<td>'.$total->service_fees.'</td>
						<td>'.$total->schedule_fees.'</td>
						<td>'.$total->late_fees.'</td>
						<td>'.$total->transfer_fees.'</td>
						<td>'.$total->previous_paid_fees.'</td>
						<td>'.$total->balance_amount.'</td>
						<td>'.$total->due_fees.'</td>';
						
										
			$total_schedule_fees = $total_schedule_fees+$total->schedule_fees	;
			$total_due_fees = $total_due_fees+$total->due_fees	;
			$total_late_fees = $total_late_fees+$total->late_fees	;
			
		$output.='</tr>';
	
}
$total_fees_to_paid = $total_fees_to_paid+$total_due_fees+$service_fees	;
$output .='</table>
				<strong><font color="#FF0000">Paid Fees(Due fees + Registration Fees):-'.$total_fees_to_paid.' ,Dated on '.$payment_date.' </font></strong>
				</div></div>'
				;
			
						
return $output;	
}
function fee_details_breakup_85($application_id,$service_id,$factory_typeid,$reference_number,$service_fees){
	$get_fa_cafa 	= get_fa_cafa($application_id);
	$payment_date 	= date("dS M Y",strtotime($get_fa_cafa['payment_date']));
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
				<th>Registration Fees</th>
    			<th>Schedule Fees(Rs)</th>
				<th>Late Fees(Rs)</th>
				<th>Transfer Fees</th>
  				<th>Previous Excess Paid(Rs.)</th>
				<th>Balance(Rs)</th>
				
				<th>Due Amount(Rs)</th>
				<th>Remark</th>
  	 			
 			</tr>';

$toatl_fees_breakup = toatl_fees_breakup($application_id,$service_id,$factory_typeid,$reference_number);
$sl=0;
$total_schedule_fees = 0;
$total_due_fees 	= 0;
$total_late_fees 	= 0;
$total_fees_to_paid 	= 0;
foreach($toatl_fees_breakup as $total){
	$sl=$sl+1;
	$output.='<tr>
						<td>'.$sl.'</td>
		             	<td>'.$total->service_year.'</td>
						<td>'.$total->power.'</td>
						<td>'.$total->worker.'</td>
						<td>'.$total->service_fees.'</td>
						<td>'.$total->schedule_fees.'</td>
						<td>'.$total->late_fees.'</td>
						<td>'.$total->transfer_fees.'</td>
						<td>'.$total->previous_paid_fees.'</td>
						<td>'.$total->balance_amount.'</td>
						
						<td>'.$total->due_fees.'</td>
						<td>'.$total->remark.'</td>';
						
										
			$total_schedule_fees = $total_schedule_fees+$total->schedule_fees	;
			$total_due_fees = $total_due_fees+$total->due_fees	;
			$total_late_fees = $total_late_fees+$total->late_fees	;
			
		$output.='</tr>';
	
}
$total_fees_to_paid = $total_fees_to_paid+$total_due_fees+$service_fees	;
$output .=' 	
				</table>
				<strong><font color="#FF0000">Paid Fees(Due fees + Registration Fees):-'.$total_fees_to_paid.' ,Dated on '.$payment_date.' </font></strong>
				</div></div>'
				;
			
						
return $output;	
}
function save_apy_ment_details_2mi($application_id,$service_id,$factory_typeid,$reference_number,$date_of_amenability,$period_for_application,$previous_excess_paid){
	global $base_root, $base_path, $user;
	$created_by 						=   $user->uid;
	$previous_amount_pre 				=   $previous_excess_paid;
	$Registration_fees 					= 	0;
	$amendment_fees 					= 	0;
	$created_by 						=   $user->uid;
	$modifi_date 						=   date("Y-m-d",strtotime($date_of_amenability));
	$i									=	1;
	if($modifi_date>='2016-12-30'){
		$Registration_fees =0;
	}
	$output = '<div class="box-header with-border">
              <h3 class="box-title">Fees Calculation for Amendment<br/> Amenability Date:-'.date("dS M Y",strtotime($date_of_amenability)).'<br/>Period of license:-'.$period_for_application.'Year(s)<br/>Amendment Fees:-'.$amendment_fees.'</h3>
              </div>
			 <div class="box-body"><div class="table-responsive">';
			
 	$power_details		= yearly_data_fees($application_id,$factory_typeid,$service_id,$reference_number);
	
	$license_fees 		= 0;
	$late_fees			= 0;
	$current_year 		= date("Y");
	$fees 				= 0;
	$i					= 1;

	$total_license_fees  = 0;
	$late_year =  0;  
	foreach($power_details as $rows){
		if($rows->type_power_station == "other"){
			$power_hp_kw 	= $rows->installed_power_hp;
			$unit 		 	= 'Hp';
			$result_data 	= fees_calculation_registration($rows->installed_power_hp,$rows->worker_total,$rows->calculate_starting_year);
			$fees		 	= $result_data['fees']*$rows->valid_time_period;
			
			if($rows->calculate_starting_year>='2016-12-30'){
				 $current_date = date('Y-m-d');
				if($rows->calculate_starting_year<$current_date){
					if($current_date>$rows->calculate_end_year){
						 $diff =($current_date-$rows->calculate_starting_year);
						if($diff == 0){
							$late_year = 1;
						}else{
							$late_year = $diff;
						}
					
					}
					if($current_date<$rows->calculate_end_year){
						$diff =($current_date-$rows->calculate_starting_year);
						if($diff == 0){
							$late_year = 1;
						}else{
							$late_year = $diff+1;
						}
					}
				}else{//echo 'hi';
					$late_year = 0;
				}
		
				$late_fees		 	= $result_data['fees']*$late_year;
			 	$payble_fees 		= $fees+$late_fees+$Registration_fees+$amendment_fees;
				
			 	if($previous_amount_pre>$payble_fees){
						$late_fees_pay 		= $late_fees;
						$balance_amount  	= ($previous_amount_pre+$row->fees_paid)-$payble_fees;
						$due_amount 		= 0;
					}
				if($previous_amount_pre<$payble_fees){
						$due_amount  		= $payble_fees-($previous_amount_pre+$row->fees_paid);
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
			 	if($previous_amount_pre<$fees){
					if($rows->calculate_starting_year>date('Y-m-d')){
							$due_amount  		= $fees-($previous_amount_pre+$row->fees_paid);
							$previous_amount 	= 0 ;
							$balance_amount 	= 0;
							$late_fees 			= 0;
					}
					if($rows->calculate_starting_year<date('Y-m-d')){
							$due_amount  		= ($fees-($previous_amount_pre+$row->fees_paid))+$fees;
							$late_fees_pay 		= $late_fees;
							$previous_amount 	= 0 ;
							$balance_amount 	= 0;
			   		}
				}
				if($previous_amount_pre==$fees){
						$previous_amount 	=	0 ;
						$balance_amount 	= 	0;
						$late_fees_pay 		= 	$late_fees;
						$due_amount 		= 	$fees;
				}	
			}
			
			if($rows->calculate_starting_year<'2016-12-30'){ 
				$payble_fees 	= $fees+$Registration_fees+$amendment_fees;
				if($previous_amount_pre>$payble_fees){
					$balance_amount 		= 	($previous_amount_pre+$row->fees_paid)-$fees;
					$previous_amount 		=	$balance_amount ;
					$late_fees_pay 			=	0;
					$due_amount 			=	0;
					
				}
				if($previous_amount_pre<$payble_fees){
						$due_amount  			= $payble_fees-($previous_amount_pre+$row->fees_paid);
						$previous_amount 		= 0 ;
						$balance_amount 		= 0 ;
						$late_fees_pay 			= 0 ;
						$due_amount 			= 0;
				}
				if($previous_amount_pre == $payble_fees){
						$previous_amount 	=0 ;
						$balance_amount 	= 0;
						$late_fees_pay 		= 0;
						$due_amount 		= 0;
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
			'service_fees'				 => $amendment_fees
		);
		//print_r($calculate_fees_details);
		//die();
		$id = db_insert('fa_calculates_license_fees')->fields($calculate_fees_details)->execute();
		
		$previous_amount_pre 	= $balance_amount;
		$total_license_fees 	= $fees+$total_license_fees;
		$total_late_fees 		= $late_fees+$total_late_fees;
	    $total_due_fees 		= $due_amount+$total_due_fees;
		$Registration_fees 		= 0;
		$amendment_fees			= 0;
		if($balance_amount!=0){
			 $fees_to_paid		= 0 ;
		}else{
			 $fees_to_paid		= $total_due_fees;
		}
			$i= $i+1;
		}
	}

	
			
		
	if(empty($previous_excess_paid) || $previous_excess_paid==NULL || $previous_excess_paid==0){
	
		$fees_deatils = array('service_fees'=>$Registration_fees1,'payment_amount'=>$fees_to_paid,'application_status'=>'RS','is_previous_payment'=>$is_payment_mad,'balance_amount'=>$balance_amount);
	}else{//echo $previous_excess_paid;die();	
			$fees_deatils = array('service_fees'=>$Registration_fees1,'previous_excess_paid'=>$previous_excess_paid,'payment_amount'=>$fees_to_paid,'application_status'=>'RS','is_previous_payment'=>$is_payment_mad,'balance_amount'=>$balance_amount);
}
	//print_r($fees_deatils);die();
				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		->	fields($fees_deatils);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc		->	execute();
					
	return $output;
	
}
//-------------Fetch director------------------------
