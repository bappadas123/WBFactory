<?php

function view_payment_data_details($form, &$form_state,$serviceid, $factory_typeid,$applicationid,$referenceno) {	
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

	$fees_details = toatl_fees_breakup($application_id,$service_id,$factory_type_id,$reference_no);
	//print_r($fees_details);die;
	
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

	$form['header']            = array(
        '#markup' => t('<div class="content"><h1><font color ="red">UNDER DEVELOPMENT</font></h1><h3>Application for Registration and Grant of Licence.All inputs are provided by applicant only.
						All inputs are to be verified by officials</h3>')
    );
	$form['factory_part_payment'] = array(
		'#type' 		=> 'fieldset',
		'#title' 		=> t('Details of Payment'),
		'#collapsible' 	=> TRUE, // Added
		'#collapsed' 	=> FALSE,  // Added
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
	

	$form['factory_part_payment']['form_start'] = array(
			'#prefix' 	=> '<div class = "row"><div class="box-header with-border">'.$details.' </div>',
	);

	$form['factory_part_payment']['payment_deatails'] = array(
		'#type'		=> 'markup',
		'#markup' 	=> view_payment_deatils($application_id,$service_id,$factory_type_id,$reference_no),
			
	);
	if($factory_type_id ==1 || $factory_type_id == 3){
		if($application_status == 'RP' && $factory_type_id ==1){
			save_apy_ment_details_2mi($application_id,$service_id,$factory_type_id,$reference_no,$date_of_amenability,$period_for_application,$total_payment);
		}
		
		$form['factory_part_payment']['worker_year_table'] 	= array(
		 		'#type'				=> 'markup',
				'#markup'			=> fee_details_breakup($application_id,$service_id,$factory_type_id,$reference_no,$service_fees,$total_payment)
			);
	}if($factory_type_id==2){
			$form['factory_part_payment']['worker_year_table_2mii'] 	= array(
		 		'#type'				=> 'markup',
				'#markup'			=> fee_details_breakup_2mii($application_id,$service_id,$factory_type_id,$reference_no,$service_fees,$total_payment)
			);
	}if($factory_type_id == 3){
		$form['factory_part_payment']['worker_year_table'] 	= array(
		 		'#type'				=> 'markup',
				'#markup'			=> fee_details_breakup_85($application_id,$service_id,$factory_type_id,$reference_no,$service_fees,$total_payment)
			);
	}
			
	
	$form['factory_part_payment']['payment_details'] = array(
				'#prefix'			=> '<div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div>',
				'#type' 			=> 'checkbox',
				'#id'				=> 'payment_details',
				'#default_value' 	=> $director_details_ck ,
				'#title' 			=> t('Is Payment Details Correct?'),
			);


			$identity_flag = 'payment_details';
			$irregularities_details_payment =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factory_type_id,$service_id);
			//print_r($irregularities_details_payment);die;	
				$form['factory_part_payment']['payment_irregularities_table'] 	= array(
					  '#type'		=> 'markup',
					'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12"><div id="payment_chceking_id">
									<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
									<tr>							
										<th>Irregularities for Scrutiny of Applications about Fees Calculation</th>
										<th >Action</th>
									</tr>'
				);
			
				$irregularities_name = array('Agree'=>'Agree','NotAgree'=>'Not Agree');
				if(!empty($irregularities_details_payment)){
					foreach($irregularities_details_payment as $row_irregularities_details_payment){
						$form['factory_part_payment']['payment_irregularities_'.$row_irregularities_details_payment->id] = array(
						'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12"><div id="payment_irregularities_'.$row_irregularities_details_payment->id.'">',
						'#suffix' 			=> '</td></div></div>',
						'#type' 			=> 'textarea',
						'#rows'			=> 2,
						'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
						'#default_value' 	=>$row_irregularities_details_payment->irregularities,
						);
						
						$form['factory_part_payment']['factory_adchk_'.$row_irregularities_details_payment->id] = array(
							'#prefix' 			=> '<td><div class="col-md-12 col-xs-12"><div id="factory_adchk_'.$row_irregularities_details_payment->id.'">',
							'#suffix' 			=> '</div></tr></td></div>',
							'#type' 			=> 'radios',
							'#options'         => $irregularities_name,
							'#default_value' 	=>$row_irregularities_details_payment->remark_by_ad,	
						);
					}
				
				}else{
		
					$form['factory_part_payment']['payment_irregularities_1'] = array(
						'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</td></div>',
						'#type' 			=> 'textarea',
						'#rows'				=> 3,
						'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
						'#default_value' 	=>'1. The Licence Fees paid with the application do not match with the category (max. nos. of Workers likely to be employed on any day and total installed Machinery capacity) of Licence for which the application has been made.',
					);
						
					$form['factory_part_payment']['payment_chk_1'] = array(
						'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</div></tr></td>',
						'#type' 			=> 'radios',
						'#options'         => $irregularities_name,
						'#default_value' 	=>'NotAgree',
					);
					
					$form['factory_part_payment']['payment_irregularities_2'] = array(
						'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</td></div>',
						'#type' 			=> 'textarea',
						'#rows'				=> 5,
						'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
						'#default_value' 	=>'2. As the application for Registration & Grant of Licence was not submitted prior to the declared date of Amenability of / Commencement of business in* the premises as a ‘Factory’, as under The Factories Act 1948, additional Licence Fee @ 100% of the Scheduled Fees for the Year(s) '.$fees_details[0]->feesyear.', '.$fees_details[0]->schedule_fees.'-/ for the period from dd1/mm1/yyyy1 to dd1/mm1/yyyy1, for which the premises constituted a Factory as under the said Act (but for which Licence was neither obtained nor applied for), will be required to be paid.',
						
					);

						
					$form['factory_part_payment']['payment_chk_2'] = array(
						'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</div></tr></td>',
						'#type' 			=> 'radios',
						'#options'         => $irregularities_name,
						'#default_value' 	=>'NotAgree',
					);
					$form['factory_part_payment']['payment_irregularities_3'] = array(
						'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</td></div>',
						'#type' 			=> 'textarea',
						'#rows'				=> 3,
						'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
						'#default_value' 	=>'3. As the application for Renewal of Licence was not submitted before the expiry of validity, but within ninety days after the said expiry – Late fee @ 50% is required to be paid.',
						
					);
					
						
					$form['factory_part_payment']['payment_chk_3'] = array(
						'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</div></tr></td>',
						'#type' 			=> 'radios',
						'#options'         => $irregularities_name,
						'#default_value' 	=>'NotAgree',
					);

					$form['factory_part_payment']['payment_irregularities_4'] = array(
						'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</td></div>',
						'#type' 			=> 'textarea',
						'#rows'				=> 3,
						'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
						'#default_value' 	=>'4. As the application for Renewal of Licence was not submitted before the expiry of validity, but beyond ninety days after the said expiry – Late fee @ 100% is required to be paid.',
						
					);

					$form['factory_part_payment']['payment_chk_4'] = array(
						'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</div></tr></td>',
						'#type' 			=> 'radios',
						'#options'         => $irregularities_name,
						'#default_value' 	=>'NotAgree',
					);
				}
					
				$form['factory_part_payment']['payment_irregularities_end'] 	= array(
					'#suffix' 	=> '</table><div></div>',
				);
				

				$caf_upload_doc_payment_details =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'REC', $factory_type_id,$reference_no, 'previous_payment_id');
				//if(!empty){

					$form['payment_details']['documents_list_factory_payment_details'] 	= array(
					'#type'		=> 'markup',
				  	'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12" id="worker_table_id">
								  <table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
								  <tr>							
									  <th>Supportive Documents According to Payment details </th>
									  <th >Action</th>
								  </tr> '
					);
				//}
				
		
		  		
		  
		  //echo $application_id;die;
			  	foreach ($caf_upload_doc_payment_details as $record) {
				  
					$fetch_document = fun_fetch_document_listid($record->doc_master_id);
					$document_name = $fetch_document['document_name'];
					$displayLink = l('<i>'.$document_name.'</i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $record->id).'/'.encryption_decryption_fun('encrypt', $record->upload_doc_type).'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
				
				
					$form['payment_details']['documents_list_factory_payment_details'.$record->id] = array(
						'#prefix' 	=> '<tr><td><div class="col-md-12 col-xs-12">',
						'#suffix' 	=> '</td></div>',
						'#type' 	=> 'markup',
						'#markup' 	=>$displayLink,
					);

					if(!empty($doc_verify_field)){
						if (in_array($record->id, $doc_verify_field)) {
						  	$form['payment_details']['documents_list_factory_payment_details_chk_'.$record->id] = array(
								'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
								'#suffix' 			=> '</div></tr></td>',
								'#type' 			=> 'checkbox',
								'#default_value' 	=> '1',
							);
					  	}else{
						  	$form['payment_details']['documents_list_factory_payment_details_chk_'.$record->id] = array(
								'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
								'#suffix' 			=> '</div></tr></td>',
								'#type' 			=> 'checkbox',
							);
					  	}
				  
			   		}else{
				   			$form['payment_details']['documents_list_factory_payment_details_chk_'.$record->id] = array(
								'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
								'#suffix' 			=> '</div></tr></td>',
								'#type' 			=> 'checkbox',
								'#default_value' 	=>'1',
							);
					}
				  
				}
				$form['payment_details']['documents_list_factory_payment_details_end'] 	= array(
					'#suffix' 	=> '</table></div>',
				);

		if($application_status == 'U'){	
			$form['submit'] = array(
				'#prefix' => '<div class="col-md-1">',
				'#suffix' => '</div>',
				'#attributes' => array('class' => array('btn btn-success')),
				'#type' => 'submit',
				'#value' => 'Save'
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
