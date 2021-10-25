<?php

function view_payment_Details($form, &$form_state,$serviceid,$factory_typeid,$applicationid,$referenceno) {	
	global $base_root, $base_path, $user;
		//echo 'dd';die;
	
	  $application_id 			= encryption_decryption_fun('decrypt', $applicationid);
	 $service_id 				= encryption_decryption_fun('decrypt',$serviceid);
	 $factory_type_id 			= encryption_decryption_fun('decrypt',$factory_typeid);
	 $reference_no 				= encryption_decryption_fun('decrypt',$referenceno);
	$get_fa_cafa 				= get_fa_cafa($application_id);
   // $reference_no 				= $get_fa_cafa['reference_number'];
	$date_of_amenability 		= $get_fa_cafa['date_of_amenability'];
	$period_for_application 	= $get_fa_cafa['period_for_application'];
	$previous_excess_paid		= $get_fa_cafa['previous_excess_paid'];
	$is_calculate				= $get_fa_cafa['is_calculate'];
	$service_fees				= $get_fa_cafa['service_fees'];
	$previous_payment_amount	= $get_fa_cafa['payment_amount'];
	$application_status			= $get_fa_cafa['application_status'];
	$total_payment				= $previous_payment_amount+$previous_excess_paid;
	$factory_name				= $get_fa_cafa['factory_name'];
	$factory_license_no			= $get_fa_cafa['factory_license_no'];
	$license_valid_upto			= $get_fa_cafa['license_valid_upto'];
	$license_valid_upto			= $get_fa_cafa['license_valid_upto'];
	
	if($factory_type_id == 1){
		$section = 'Section-2m(i)';
	}if($factory_type_id == 2){
		$section = 'Section-2m(ii)';
	}if($factory_type_id == 3){
		$section = 'Section-85';
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
	if($service_id == 2){
		$details =  '<h3 class="box-title">Fees Calculation for Registration and garant of License<br/> 
			Name:-'.$factory_name.' ('.$section.')'.'<br/>
		
			  Amenability Date:-'.date("dS M Y",strtotime($date_of_amenability)).'<br/>
			  Period of license:-'.$period_for_application.'Year(s)<br/>
			  Registration Fees:-'.$service_fees.'</h3>';
	}if($service_id == 3){
		$details =  '<h3 class="box-title">Fees Calculation for Renewal of the License<br/> Name:-'.$factory_name.' ('.$section.')'.'<br/> 
			 License Numer :- '.$factory_license_no.' License Vaild upto:-'.date("dS M Y",strtotime($license_valid_upto)).'<br/>
			  Period of license:-'.$period_for_application.'Year(s)<br/>';
			
	}if($service_id == 8 || $service_id == 8  ){
		$details =  '<h3 class="box-title">Fees Calculation for Amendment of the License<br/> Name:-'.$factory_name.' ('.$section.')'.'<br/> 
			 License Numer :- '.$factory_license_no.' License Vaild upto:-'.date("dS M Y",strtotime($license_valid_upto)).'<br/>
			  Period of license:-'.$period_for_application.'Year(s)<br/>';
			
	}
	
	
	 $form['yearly_worker']['form_start'] = array(
			'#prefix' 			=> '<div class = "box-body"><div class="box-header with-border">
			 
			 '.$details.'
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
		 		'#type'				=> 'markup',
				'#markup'			=> fee_details_breakup($application_id,$service_id,$factory_type_id,$reference_no,$service_fees,$total_payment)
			);
	}if($factory_type_id==2){
			$form['yearly_worker']['worker_year_table_2mii'] 	= array(
		 		'#type'				=> 'markup',
				'#markup'			=> fee_details_breakup_2mii($application_id,$service_id,$factory_type_id,$reference_no,$service_fees,$total_payment)
			);
	}if($factory_type_id == 3){
		$form['yearly_worker']['worker_year_table'] 	= array(
		 		'#type'				=> 'markup',
				'#markup'			=> fee_details_breakup_85($application_id,$service_id,$factory_type_id,$reference_no,$service_fees,$total_payment)
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


function fee_details_breakup($application_id,$service_id,$factory_typeid,$reference_number,$service_fees,$total_payment){
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
				<th>Registration<br/>/Amendment/<br/>Tranfer Fees</th>
    			<th>Schedule Fees(Rs)</th>
				<th>Late Fees(Rs)</th>
				
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
	$previous_paid_fees		= $total->previous_paid_fees;
	break;
}
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
					
						<td>'.$total->previous_paid_fees.'</td>
						<td>'.$total->balance_amount.'</td>
						
						<td>'.$total->due_fees.'</td>';
						
										
			$total_schedule_fees 	= $total_schedule_fees+$total->schedule_fees ;
			 $total_due_fees 		= $total_due_fees+$total->due_fees	;
			$total_late_fees 		= $total_late_fees+$total->late_fees ;
		
			
		$output.='</tr>';
	
}
$total_fees_to_paid = $total_due_fees+$previous_paid_fees	;
$output .=' 	
				</table> 
				<strong><font color="#FF0000">Paid Fees(Due fees):-'.$total_fees_to_paid.' ,Dated on '.$payment_date.' </font></strong>
				</div></div>'
				;
			
						
return $output;	
}

function fee_details_breakup_2mii($application_id,$service_id,$factory_typeid,$reference_number,$service_fees,$total_payment){
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
				<th>Registration<br/>/Amendment/<br/>Tranfer Fees</th>
    			<th>Schedule Fees(Rs)</th>
				<th>Late Fees(Rs)</th>
			
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
	$previous_paid_fees		= $total->previous_paid_fees;
	break;
}
foreach($toatl_fees_breakup as $total){
	$sl=$sl+1;
	$output.='<tr>
						<td>'.$sl.'</td>
		             	<td>'.$total->service_year.'</td>
						<td>'.$total->worker.'</td>
						<td>'.$total->service_fees.'</td>
						<td>'.$total->schedule_fees.'</td>
						<td>'.$total->late_fees.'</td>
					
						<td>'.$total->previous_paid_fees.'</td>
						<td>'.$total->balance_amount.'</td>
						<td>'.$total->due_fees.'</td>';
						
										
			$total_schedule_fees = $total_schedule_fees+$total->schedule_fees	;
			$total_due_fees = $total_due_fees+$total->due_fees	;
			$total_late_fees = $total_late_fees+$total->late_fees	;
			
		$output.='</tr>';
	
}
$total_fees_to_paid = $previous_paid_fees+$total_due_fees	;
$output .='</table>
				<strong><font color="#FF0000">Paid Fees(Due fees + Registration Fees):-'.$total_fees_to_paid.' ,Dated on '.$payment_date.' </font></strong>
				</div></div>'
				;
			
						
return $output;	
}
function fee_details_breakup_85($application_id,$service_id,$factory_typeid,$reference_number,$service_fees,$total_payment){
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
				<th>Registration<br/>/Amendment/<br/>Tranfer Fees</th>
    			<th>Schedule Fees(Rs)</th>
				<th>Late Fees(Rs)</th>
			
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
	$previous_paid_fees		= $total->previous_paid_fees;
	break;
}
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
						
						<td>'.$total->previous_paid_fees.'</td>
						<td>'.$total->balance_amount.'</td>
						
						<td>'.$total->due_fees.'</td>
						<td>'.$total->remark.'</td>';
						
										
			$total_schedule_fees = $total_schedule_fees+$total->schedule_fees	;
			$total_due_fees = $total_due_fees+$total->due_fees	;
			$total_late_fees = $total_late_fees+$total->late_fees	;
			
		$output.='</tr>';
	
}
$total_fees_to_paid = $previous_paid_fees+$total_due_fees	;
$output .=' 	
				</table>
				<strong><font color="#FF0000">Paid Fees(Due fees + Registration Fees):-'.$total_fees_to_paid.' ,Dated on '.$payment_date.' </font></strong>
				</div></div>'
				;
			
						
return $output;	
}

//-------------Fetch director------------------------
