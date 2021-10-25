<?php

function application_status_details_view($form, &$form_state,$serviceid,$factory_typeid,$applicationid,$referenceno) {	
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
	$details =  'Name:-'.$factory_name.' ('.$section.')'.'<br/> ';
	
	 $form['yearly_worker']['form_start'] = array(
			'#prefix' 			=> '<div class = "box-body"><div class="box-header with-border">
			  <h3 class="box-title"><br/>
			 '.$details.'
            </div>',
			
		   
		 );
	$form['yearly_worker']['payment_deatails'] = array(
				'#type'				=> 'markup',
				'#markup' 			=> view_remark_deatils($application_id,$reference_no),
			
		);
	
	
 return $form; 
        
}
		 

function view_remark_deatils($application_id,$reference_no){
	
	global $user;
	  $uid = $user->uid;
		$output = '';
	$sl = 0;
	$header = array(
		array('data'=> 'SL No'),
		array('data'=> 'Action'),
		array('data'=> 'Action by'),
		array('data'=> 'Date'),
		
	);
		$rid= get_role_id($uid);
		
	
	$remark_deatils	=	remark_fetch($reference_no,$application_id,$rid);
	//print_r($remark_deatils);die();
	foreach($remark_deatils as $row_remark){
			if($row_remark->remark_by_uid == $uid){
				$remark_by_name = 'By own activity';
			}if($row_remark->remark_by_uid != $uid){
				$remark_by_name = $row_remark->remark_by_name;
			}
		$sl		 = $sl+1;	
		$rows [] = array(  
			array('data' => $sl), 	
			array('data' => t($row_remark->remarks)), 
			array('data' => t($remark_by_name)),
			array('data' => t(date("dS M Y",strtotime($row_remark->sending_time)))),
			
		
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




//-------------Fetch director------------------------
