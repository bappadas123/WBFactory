<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
function caf_form_owner_registration($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$referenceno)
{ 
    global $base_root, $base_path, $user;
    $form            	= array();

    $service_id      	= encryption_decryption_fun('decrypt', $serviceid);
    $factory_type_id 	= encryption_decryption_fun('decrypt', $factory_typeid);
    $application_id  	= encryption_decryption_fun('decrypt', $applicationid);
	$reference_no  		= encryption_decryption_fun('decrypt', $referenceno);
    
	$remark_fetch 		= get_checking($application_id,$service_id,$factory_type_id,$reference_no);
	$verify_details 	= $remark_fetch['verify_details'];
	
	if(!empty($verify_details)){
		$remark_field 	= explode(',', $verify_details);
		//print_r($doc_verify_field);die;
		foreach ($remark_field as $fieldname){ 
			//echo $fieldname;
			if($fieldname == 'owner_details'){ $owner_details_ck = 1;}
		}

	}
	
	$form['applicationid_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $applicationid
    );
	$form['serviceid_hidden']     = array(
        '#type' => 'hidden',
        '#default_value' => $serviceid
    );
    $form['factorytypeid_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $factory_typeid
    );
	$form['referenceno_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $referenceno
    );
	/********** Factory Information - Start **********/
    
	$form['header']	= array(
		'#type'			=> 'markup',
		'#prefix'		=> '<div class="row"><h1><font color ="red">UNDER DEVELOPMENT</font></h1><h3>Application for Registration and Grant of Licence.
			All inputs are provided by applicant only.
			All inputs are to be verified by officials</h3>',
 	);
	
	/********** Details of owner of the Owner occupied as a factory - Start **********/

		
	$form['factory_part_owner']['view_owner'] = array(
		'#prefix'			=> '<div class="row"><div id="view_owner_details_id"><div class="col-md-10">',
		'#suffix' 		    => '</div></div>',
		'#type' 			=> 'markup',
		'#markup' 			=> view_owner_details($application_id,$service_id,$factory_type_id,$reference_no),
	);			
	$form['factory_part_owner']['owner_details'] = array(
		'#prefix'			=> '<div class="col-md-2 col-xs-2"><br/>',
		'#suffix' 			=> '</div></div>',
	  	'#type' 			=> 'checkbox',
	  	'#id'				=> 'owner_details',
	  	'#default_value' 	=> $owner_details_ck ,
	  	'#title' 			=> t('Is Owner Details Correct?'),
	);	



	// $identity_flag = 'owner_details';
	// $irregularities_details_owner =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factory_type_id,$service_id);
	// //print_r($irregularities_details_owner);die;	
	// 	$form['factory_part_owner']['owner_irregularities_table'] 	= array(
  	// 		'#type'		=> 'markup',
	// 		'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12"><div id="owner_chceking_id">
	// 						<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
	// 						<tr>							
	// 							<th>Irregularities for Scrutiny of Applications about Owner of the Factory </th>
	// 							<th >Action</th>
	// 						</tr>'
	// 	);
	
	// 	$irregularities_name = array('Agree'=>'Agree','NotAgree'=>'Not Agree');
	// 	if(!empty($irregularities_details_owner)){
	// 		foreach($irregularities_details_owner as $row_irregularities_details_owner){
	// 			$form['factory_part_owner']['owner_irregularities_'.$row_irregularities_details_owner->id] = array(
	// 			'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12"><div id="owner_irregularities_'.$row_irregularities_details_owner->id.'">',
	// 			'#suffix' 			=> '</td></div></div>',
	// 			'#type' 			=> 'textarea',
	// 			'#rows'			=> 2,
	// 			'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
	// 			'#default_value' 	=>$row_irregularities_details_owner->irregularities,
	// 			);
				
	// 			$form['factory_part_owner']['factory_adchk_'.$row_irregularities_details_owner->id] = array(
	// 				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12"><div id="factory_adchk_'.$row_irregularities_details_owner->id.'">',
	// 				'#suffix' 			=> '</div></tr></td></div>',
	// 				'#type' 			=> 'radios',
	// 				'#options'         => $irregularities_name,
	// 				'#default_value' 	=>$row_irregularities_details_owner->remark_by_ad,	
	// 			);
	// 		}
		
	// 	}else{

	// 		$form['factory_part_owner']['owner_irregularities_1'] = array(
	// 			'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
	// 			'#suffix' 			=> '</td></div>',
	// 			'#type' 			=> 'textfield',
	// 			'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
	// 			'#default_value' 	=>'1.Appropriate documents in support of Change of Name of the Factory have not been uploaded with the application',
	// 		);
				
	// 		$form['factory_part_owner']['owner_chk_1'] = array(
	// 			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
	// 			'#suffix' 			=> '</div></tr></td>',
	// 			'#type' 			=> 'radios',
	// 			'#options'         => $irregularities_name,
	// 			'#default_value' 	=>'NotAgree',
	// 		);
			
	// 		$form['factory_part_owner']['owner_irregularities_2'] = array(
	// 			'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
	// 			'#suffix' 			=> '</td></div>',
	// 			'#type' 			=> 'textarea',
	// 			'#rows'			=> 2,
	// 			'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
	// 			'#default_value' 	=>'2. The name of the Factory as mentioned in the Common Application Form does not match with that as per the supporting document– Memorandum & Articles of Association / Partnership Deed / Certificate of Proprietorship / Trade Licence* – uploaded with the application',
				
	// 		);
				
	// 		$form['factory_part_owner']['owner_chk_2'] = array(
	// 			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
	// 			'#suffix' 			=> '</div></tr></td>',
	// 			'#type' 			=> 'radios',
	// 			'#options'         => $irregularities_name,
	// 			'#default_value' 	=>'NotAgree',
	// 		);
	// 	}
			
	// 	$form['factory_part_owner']['owner_irregularities_end'] 	= array(
	// 		'#suffix' 	=> '</table><div></div>',
	// 	);


		
// 		$form['factory_part_a']['owner_details_factory'] 	= array(
	   
	
// 			'#type'		=> 'markup',
// 		  '#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12" id="worker_table_id">
// 						  <table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
// 						  <tr>							
// 							  <th>List of supported documents according to owner of factory </th>
// 							  <th >Action</th>
							  
// 						  </tr>
// 						  '
// 				  );
  
  
// 		$caf_upload_doc_owner =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'DOC', $factory_type_id,$reference_no, 'premises_address');
// 		//print_r($caf_upload_doc_all1);die;
		
// 	  foreach ($caf_upload_doc_owner as $record) {
		  
// 	  $fetch_document = fun_fetch_document_listid($record->doc_master_id);
// 	  $document_name = $fetch_document['document_name'];
// 	  $displayLink = l('<i>'.$document_name.'</i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $record->id).'/'.encryption_decryption_fun('encrypt', 'DOC').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
	  
	  
// 	  $form['factory_part_a']['owner_details_factory'.$record->id] = array(
// 		   '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
// 			  '#suffix' 			=> '</td></div>',
// 		   '#type' 			=> 'markup',
	  
// 		  '#markup' 	=>$displayLink,
		  
// 	  );
	  
// 	  if(!empty($doc_verify_field)){
// 		  if (in_array($record->id, $doc_verify_field)) {
// 			  $form['factory_part_a']['owner_details_factory_chk_'.$record->id] = array(
// 					  '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
// 					  '#suffix' 			=> '</div></tr></td>',
// 					'#type' 			=> 'checkbox',
// 					 '#default_value' 	=>'1',
		  
		  
// 				);
// 		  }else{
// 			   $form['factory_part_a']['owner_details_factory_chk_'.$record->id] = array(
// 					  '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
// 					  '#suffix' 			=> '</div></tr></td>',
// 					'#type' 			=> 'checkbox',
					 
		  
		  
// 				);
// 		  }
// 	  }else{
// 		   $form['factory_part_a']['owner_details_factory_chk_'.$record->id] = array(
// 					  '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
// 					  '#suffix' 			=> '</div></tr></td>',
// 					'#type' 			=> 'checkbox',
// 					 '#default_value' 	=>'1',
		  
		  
// 				);
// 	  }
	  
	  
// 	  }
//   $form['factory_part_a']['owner_details_factory_end'] 	= array(
// 	  '#suffix' 	=> '</table></div></div>',
//   );


	 $form['submit'] = array(
        '#prefix' => '<div class="col-md-1">',
        '#suffix' => '</div>',
        '#attributes' => array('class' => array('btn btn-success')),
        '#type' => 'submit',
        '#value' => 'Save'
    );
	
	 
    return $form;
}



function caf_form_owner_registration_submit($form, &$form_state){

	global $user;

	$userid 			= $user->uid;
	$remark_by_name		= get_name($userid);
	$rid				= get_role_id($userid);
	$val    			= $form_state['values'];

	$service_id			= encryption_decryption_fun('decrypt',$val['serviceid_hidden']); 
	$factorytype_id		= encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$application_id		= encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$reference_no		= encryption_decryption_fun('decrypt',$val['referenceno_hidden']);


	$owner_details	 	=!empty($val['owner_details'])?'owner_details,':NULL;


	$identity_flag_all = NULL;
	$irregularities_details = fun_fetch_irregularities_details($identity_flag_all,$application_id,$reference_no,$factorytype_id,$service_id); 
 	$remark_id = get_remark_id($application_id,$reference_no,$userid,$rid);

 	if(!empty($irregularities_details)){
		foreach($irregularities_details as $row_irregularities_details){
			$remark_table_id = $row_irregularities_details->remark_table_id;
			$checklist_observations_ref_id = $row_irregularities_details->checklist_observations_ref_id;
		}
		
		
		$remark_fetch = get_checking($application_id,$service_id,$factory_type_id,$reference_no);
		$verify_details = $remark_fetch['verify_details'];
		//$doc_verify 	= $remark_fetch['doc_verify'];
		
		if(!empty($verify_details)){
			$remark_field = explode(',', $verify_details);
			//$doc_verify_field = explode(',', $doc_verify);
			//print_r($doc_verify_field);die;

			if(in_array("owner_details", $remark_field)) {
				if(empty($owner_details)){
					$verify_details = str_replace('owner_details,', '' ,$verify_details); 
				}
			}
			else {
				$verify_details = $verify_details .''. $owner_details;
			}
		}
		

	  	if($remark_table_id==$remark_id){


		$cafa_remarks = array(
			'sending_time' 	  	 => date('Y-m-d h:i'),
			'remark_type'	  	 => 'n',
			'verify_details'	 => $verify_details,
			//'doc_verify'		 => $documents_list,
		);
					
			$queryupdate_remarks		 =	db_update('fa_cafa_remarks');
			$queryupdate_remarks	 	->	fields($cafa_remarks);
			$queryupdate_remarks		 ->	condition('id',$remark_id,'=');	
				
			$queryupdate_remarks		 ->	execute();
				
	 	}else{
		 	$cafa_remarks = array(
								'app_id'   	  		 => $application_id,
								'remark_by_uid'  	 => $userid,
								'remark_by_roleid' 	 => $rid,
								'remark_to_roleid' 	 => 10,
								'sending_time' 	  	 => date('Y-m-d h:i'),
								'app_reference_no' 	 => $reference_no,
								'remark_by_name'	 => $remark_by_name,
								'remark_type'	  	 => 'n',
								'verify_details'	 => $verify_details,
								'remarks'			 => 'Notesheet processed is not completed',
								//'doc_verify'		 => $documents_list,
								'service_id'		 => $service_id
									
						);

		$remark_id = db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();
		}
	}
	
	//  	$checklist_observations_ref = array(
	// 							'remark_table_id'	 => $remark_id,
								
	// 					);
					
	// 			$queryupdate_observations_ref		 =	db_update('fa_checklist_observations_ref');
	// 			$queryupdate_observations_ref	 	->	fields($checklist_observations_ref);
	// 			$queryupdate_observations_ref		 ->	condition('id',$checklist_observations_ref_id,'=');	
	// 			$queryupdate_observations_ref		 ->	execute();
	
	
	//  	}
	// }
	 
	// $identity_flag = 'factory_name';
	// $irregularities_details_name =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factorytype_id,$service_id);
	// if(!empty($irregularities_details_name)){
	// 	foreach($irregularities_details_name as $row_irregularities_details_name){
	// 		$irregularities_update = array(
	  										
	// 										'remark_by_ad'					=> $val['factory_adchk_'.$row_irregularities_details_name->id],
	// 										'modification_by'				=> $userid,
	// 										'modification_date'				=> date('Y-m-d'),
											
											
	//   									);
	// 			$queryupdate_irregularities		 =	db_update('fa_checklist_observations');
	// 			$queryupdate_irregularities		 ->	fields($irregularities_update);
	// 			$queryupdate_irregularities		 ->	condition('id',$row_irregularities_details_name->id,'=');	
	// 			$queryupdate_irregularities		 ->	execute();
	// 	}
		
	// }else{
		
	// 	 $irregularities_1 = array(
	//   										'irregularities'				=> $factory_name_irregularities_1,
	// 										'remark_by_ad'					=> $factory_name_chk_1,
	// 										'ad_details'					=> $userid.','.$remark_by_name ,
	// 										'checklist_observations_ref_id' => $checklist_observations_ref_id,
	// 										'modification_by'				=> $userid,
	// 										'modification_date'				=> date('Y-m-d'),
	// 										'identity_flag'					=> 'factory_name',
											
	//   									);
	//  $irregularities_2 = array(
	//   										'irregularities'				=> $factory_name_irregularities_2,
	// 										'remark_by_ad'					=> $factory_name_chk_2,
	// 										'ad_details'					=> $userid.','.$remark_by_name ,
	// 										'checklist_observations_ref_id' => $checklist_observations_ref_id,
	// 										'modification_by'				=> $userid,
	// 										'modification_date'				=> date('Y-m-d'),
	// 										'identity_flag'					=> 'factory_name',
											
	//   									);
	// $irregularities_1_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_1) ->	execute();
	// $irregularities_2_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_2) ->	execute(); 
	// }

	//print_r($val);die;
	drupal_set_message('Your observation of application is successfully Saved.');





}


function view_owner_details($application_id,$service_id,$factory_typeid,$reference_number){// echo 'A-'.$application_id.' B-'.$reference_number.' C-'.$service_id; die;
	$get_all_data 			= array();
	$type					= '';
	$details				= '';

	$get_all_data 			= get_all_owner_data($application_id,$service_id,$factory_typeid,$reference_number);
	
	$Wcounter		= 0;
	$per_page		= 10;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	$chunks 		= array_chunk($get_all_data, $per_page);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header			= array(
						array('data' => 'Sl. No','width' => '6%'),
						array('data'=> 'Owner Name','width' => '24%'),
						array('data'=> 'Address','width' => '60'),
					);
	if(!empty($get_all_data)){
		
		foreach($chunks[$current_page] as $owner_details){ 
			$Wcounter++;
			
			$getdata_owner_address =  array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
			$owner_address    = $owner_details->addrline_premises. '<br/>'.get_full_address('fa_owner_details','sub-table',$owner_details->id,$getdata_owner_address).'<br/>'.country_name($owner_details->country_premises);


			
			$owner_full_name = $owner_details->owner_name.' '.$owner_details->owner_mname.' '.$owner_details->owner_lname;

			$rows[] 	= array( 
								array('data' =>$Wcounter,'class' => array('')),
								array('data' =>$owner_full_name ,'class' => array('')),
								array('data' =>$owner_address,'class' => array('')),
								);
				} 
		}
		$output = theme_table(
			array(
				  'header' => $header,
				  'rows' => $rows,
				  'attributes' => array('id'=>'view_owner_details_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
				  'sticky' => true,
				  'caption' => 'All owner List',
				  'colgroups' => array(),
				  'empty' => t("No data found!") // The message to be displayed if table is empty
				)
			).theme('pager');	
		 	return $output;	
}

?> 