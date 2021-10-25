<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function details_of_occupier_registration($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$referenceno) {	
	
 	global $base_root, $base_path, $user;
	$userid 				= $user->uid;
	 $application_id	= encryption_decryption_fun('decrypt', $applicationid); 
	 $service_id 		= encryption_decryption_fun('decrypt', $serviceid); 
	 $factory_type_id 	= encryption_decryption_fun('decrypt', $factory_typeid); 
	 $reference_no 		= encryption_decryption_fun('decrypt', $referenceno);
	
	$form            	= array();
	
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

	
	$remark_fetch = get_checking($application_id,$service_id,$factory_type_id,$reference_no);

	$verify_details = $remark_fetch['verify_details'];
	
	if(!empty($verify_details)){
		$remark_field = explode(',', $verify_details);
		//print_r($remark_field);die;
		foreach ($remark_field as $fieldname){ 
			//echo $fieldname;
			if($fieldname == 'occupier_details'){ $occupier_details_ck = 1;}
			if($fieldname == 'director_details'){ $director_details_ck = 1;}
			if($fieldname == 'manager_details'){ $manager_details_ck = 1;}
		} 
	}

/********** Details of Occupier - Start **********/
    $form['header'] 				= array(
		'#type'						=> 'markup',
		'#prefix'					=> '<div class="row"><h1><font color ="red">UNDER DEVELOPMENT</font></h1><h3>Application for Registration and Grant of Licence.
All inputs are provided by applicant only.
All inputs are to be verified by officials</h3>',
 	);

	$form['details_occupier'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('A. Details of Occupier'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	$form['details_occupier']['row_start'] 	= array(
		'#prefix' 	 	=> '<div class="row">',
	);

	
	
		
	$form['details_occupier']['view_occupier'] = array(
			'#prefix'		=> '<div class="row"><div class="col-md-12 col-xs-12">',
			'#suffix' 		=> '</div></div>',
			'#type'			=> 'markup',
			'#markup'		=> view_occupier_details($application_id,$service_id,$factory_type_id,$reference_no),
	);
	
	$form['details_occupier']['occupier_details'] = array(
			'#prefix'			=> '<div class="row"><div class="col-md-2 col-xs-2"><br/>',
			'#suffix' 			=> '</div></div>',
			'#type' 			=> 'checkbox',
			'#id'				=> 'occupier_details',
			'#default_value' 	=> $occupier_details_ck ,
			'#title' 			=> t('Is occupier Details Correct?'),
	);	

	$form['manager_part_details'] = array(
		'#type' 		=> 'fieldset',
		'#title' 		=> t('Details of manager Permanent/Present Address '),
		'#collapsible' 	=> TRUE, // Added
		'#collapsed' 	=> FALSE,  // Added
	);
	
	$form['manager_part_details']['view_manager'] = array(
		'#prefix'		=> '<div class="row"><div class="col-md-12 col-xs-12">',
			'#suffix' 		=> '</div></div>',
		'#type'			=> 'markup',
		'#markup'		=> view_manager_details($application_id,$service_id,$factory_type_id,$reference_no),
	);

	$form['manager_part_details']['manager_details'] = array(
	'#prefix'			=> '<div class="row"><div class="col-md-2 col-xs-2"><br/>',
			'#suffix' 			=> '</div></div>',
	  	'#type' 			=> 'checkbox',
	  	'#id'				=> 'manager_details',
	  	'#default_value' 	=> $manager_details_ck ,
	  	'#title' 			=> t('Is manager Details Correct?'),
	);	

	$form['director_part_details'] = array(
		'#type' 		=> 'fieldset',
		'#title' 		=> t('Details of Directors Permanent/Present Address '),
		'#collapsible' 	=> TRUE, // Added
		'#collapsed' 	=> FALSE,  // Added
	);

	$form['director_part_details']['view_director'] = array(
		'#prefix'		=> '<div class="row"><div class="col-md-12 col-xs-12">',
			'#suffix' 		=> '</div></div>',
		'#type'		=> 'markup',
		'#markup'		=>	view_director_proipietor_details($application_id,$service_id,$factory_type_id,$reference_no),
	
	);
	$form['director_part_details']['director_details'] = array(
	'#prefix'			=> '<div class="row"><div class="col-md-2 col-xs-2"><br/>',
			'#suffix' 			=> '</div></div>',
	  	'#type' 			=> 'checkbox',
	  	'#id'				=> 'director_details',
	  	'#default_value' 	=> $director_details_ck ,
	  	'#title' 			=> t('Is director Details Correct?'),
	);	




	$identity_flag = 'occupier_details';
	$irregularities_details_occupier =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factory_type_id,$service_id);
	//print_r($irregularities_details_occupier);die;	
		$form['details_occupier_observation']['occupier_irregularities_table'] 	= array(
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12"><div id="occupier_chceking_id">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>Irregularities for Scrutiny of Applications about Occupier of the Factory </th>
								<th >Action</th>
								<th>Irregularities by DD</th>
								<th>Irregularities by JD</th>
							</tr>'
		);
	
		$irregularities_name = array('Agree'=>'Agree','NotAgree'=>'Not Agree');
		if(!empty($irregularities_details_occupier)){
			foreach($irregularities_details_occupier as $row_irregularities_details_occupier){
				$form['details_occupier_observation']['occupier_irregularities_'.$row_irregularities_details_occupier->id] = array(
				'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12"><div id="occupier_irregularities_'.$row_irregularities_details_occupier->id.'">',
				'#suffix' 			=> '</td></div></div>',
				'#type' 			=> 'textarea',
				'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
				'#default_value' 	=> $row_irregularities_details_occupier->irregularities,
				);
				
				$form['details_occupier_observation']['factory_adchk_'.$row_irregularities_details_occupier->id] = array(
					'#prefix' 			=> '<td><div class="col-md-12 col-xs-12"><div id="factory_adchk_'.$row_irregularities_details_occupier->id.'">',
					'#suffix' 			=> '</div></td></div>',
					'#type' 			=> 'radios',
					'#options'         => $irregularities_name,
					'#default_value' 	=>$row_irregularities_details_occupier->remark_by_ad,	
				);
				$form['details_occupier_observation']['factory_ddchk_'.$row_irregularities_details_occupier->id] = array(
					'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
					'#suffix' 			=> '</div></td>',
					'#type' 			=> 'radios',
					'#options'         => $irregularities_name,
					'#attributes' 		=> array('disabled' => TRUE),
					'#default_value' 	=>$row_irregularities_details_occupier->remark_by_dd,	
				);
				$form['details_occupier_observation']['factory_jdchk_'.$row_irregularities_details_occupier->id] = array(
					'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
					'#suffix' 			=> '</div></td></tr>',
					'#type' 			=> 'radios',
					'#options'         => $irregularities_name,
					'#attributes' 		=> array('disabled' => TRUE),
					'#default_value' 	=>$row_irregularities_details_occupier->remark_by_jd,	
				);
			}
		
		}else{

			$form['details_occupier_observation']['occupier_irregularities_1'] = array(
				'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</td></div>',
				'#type' 			=> 'textfield',
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
				'#default_value' 	=>'1.The particulars of the Occupier mentioned in the Common Application Form, does not match with the supporting documents.',
			);
				
			$form['details_occupier_observation']['occupier_chk_1'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=>'NotAgree',
			);
			$form['details_occupier_observation']['occupier_ddchk_1'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=>'NotAgree',
				'#attributes' 		=> array('disabled' => TRUE),
			);
			
			$form['details_occupier_observation']['occupier_jdchk_1'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td></tr>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=>'NotAgree',
				'#attributes' 		=> array('disabled' => TRUE),
			);
			



			$form['details_occupier_observation']['occupier_irregularities_2'] = array(
				'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</td></div>',
				'#type' 			=> 'textarea',
				'#rows'			=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
				'#default_value' 	=>'2.The name / particulars of the Directors / Partners / Proprietor mentioned in the Common Application Form, does not match with the supporting documents uploaded with the application',
				
			);
				
			$form['details_occupier_observation']['occupier_chk_2'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=>'NotAgree',
			);

			$form['details_occupier_observation']['occupier_ddchk_2'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=>'NotAgree',
				'#attributes' 		=> array('disabled' => TRUE),
			);
			
			$form['details_occupier_observation']['occupier_jdchk_2'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td></tr>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=>'NotAgree',
				'#attributes' 		=> array('disabled' => TRUE),
			);



			$form['details_occupier_observation']['occupier_irregularities_3'] = array(
				'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</td></div>',
				'#type' 			=> 'textarea',
				'#rows'			=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
				'#default_value' 	=>'3.Documents in support of change of Partners / change of Partnership status have not been uploaded with the application',
				
			);
				
			$form['details_occupier_observation']['occupier_chk_3'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=>'NotAgree',
			);
			$form['details_occupier_observation']['occupier_ddchk_3'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=>'NotAgree',
				'#attributes' 		=> array('disabled' => TRUE),
			);
			
			$form['details_occupier_observation']['occupier_jdchk_3'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td></tr>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=>'NotAgree',
				'#attributes' 		=> array('disabled' => TRUE),
			);
		}
			
		$form['details_occupier_observation']['occupier_irregularities_end'] 	= array(
			'#suffix' 	=> '</table><div></div>',
		);

		
		
// 		$form['details_occupier_observation']['documents_list_factory_adress'] 	= array(
	   
	
// 			'#type'		=> 'markup',
// 		  '#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12" id="worker_table_id">
// 						  <table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
// 						  <tr>							
// 							  <th>List of supported documents according to Occupier of factory </th>
// 							  <th >Action</th>
// 						  </tr>'
// 				  );
  
  
//   $caf_upload_doc_occupier =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'DOC', $factory_type_id,$reference_no, 'factory_name');
//   //print_r($caf_upload_doc_all1);die;
  
// 	  foreach ($caf_upload_doc_occupier as $record) {
		  
// 	  $fetch_document = fun_fetch_document_listid($record->doc_master_id);
// 	  $document_name = $fetch_document['document_name'];
// 	  $displayLink = l('<i>'.$document_name.'</i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $record->id).'/'.encryption_decryption_fun('encrypt', 'DOC').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
	  
	  
// 	  $form['details_occupier_observation']['occupier_details'.$record->id] = array(
// 		   '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
// 			  '#suffix' 			=> '</td></div>',
// 		   '#type' 			=> 'markup',
	  
// 		  '#markup' 	=>$displayLink,
		  
// 	  );
	  
// 	  if(!empty($doc_verify_field)){
// 		  if (in_array($record->id, $doc_verify_field)) {
// 			  $form['details_occupier_observation']['occupier_details_chk_'.$record->id] = array(
// 					  '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
// 					  '#suffix' 			=> '</div></tr></td>',
// 					'#type' 			=> 'checkbox',
// 					 '#default_value' 	=>'1',
		  
		  
// 				);
// 		  }else{
// 			   $form['details_occupier_observation']['occupier_details_chk_'.$record->id] = array(
// 					  '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
// 					  '#suffix' 			=> '</div></tr></td>',
// 					'#type' 			=> 'checkbox',
					 
		  
		  
// 				);
// 		  }
// 	  }else{
// 		   $form['details_occupier_observation']['occupier_details_chk_'.$record->id] = array(
// 					  '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
// 					  '#suffix' 			=> '</div></tr></td>',
// 					'#type' 			=> 'checkbox',
// 					 '#default_value' 	=>'1',
		  
		  
// 				);
// 	  }
	  
	  
	  
// 	  }
//   $form['details_occupier_observation']['occupier_details_end'] 	= array(
// 	  '#suffix' 	=> '</table></div></div>',
//   );



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




function details_of_occupier_registration_submit($form, &$form_state){

	global $user;

	$userid 			= $user->uid;
	$remark_by_name		= get_name($userid);
	$rid				= get_role_id($userid);
	$val    			= $form_state['values'];
	//print_r($val);die;
	$service_id			= encryption_decryption_fun('decrypt',$val['serviceid_hidden']); 
	$factorytype_id		= encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$application_id		= encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$reference_no		= encryption_decryption_fun('decrypt',$val['referenceno_hidden']);


	$occupier_details	 	=!empty($val['occupier_details'])?'occupier_details,':NULL;
	$manager_details	 	=!empty($val['manager_details'])?'manager_details,':NULL;
	$director_details	 	=!empty($val['director_details'])?'director_details,':NULL;


	$occupier_irregularities_1 		= $val['occupier_irregularities_1'];
	$occupier_chk_1 				= $val['occupier_chk_1'];
	$occupier_irregularities_2 		= $val['occupier_irregularities_2'];
	$occupier_chk_2 				= $val['occupier_chk_2'];
	$occupier_irregularities_3 		= $val['occupier_irregularities_3'];
	$occupier_chk_3 				= $val['occupier_chk_3'];



	$identity_flag_all = NULL;
	$irregularities_details = fun_fetch_irregularities_details($identity_flag_all,$application_id,$reference_no,$factorytype_id,$service_id); 

	$remark_details 	= get_remark_id($application_id,$reference_no,$userid,$rid);
	$verify_details 	= $remark_details['verify_details'];
	$remark_id			= $remark_details['id'];

 	if(!empty($irregularities_details)){
		foreach($irregularities_details as $row_irregularities_details){
			$remark_table_id = $row_irregularities_details->remark_table_id;
			$checklist_observations_ref_id = $row_irregularities_details->checklist_observations_ref_id;
		}
		
		//$remark_fetch = get_checking($application_id,$service_id,$factory_type_id,$reference_no);
		//$verify_details = $remark_fetch['verify_details'];
		//$doc_verify 	= $remark_fetch['doc_verify'];
		
		if(!empty($verify_details)){
			$remark_field = explode(',', $verify_details);
			//$doc_verify_field = explode(',', $doc_verify);
			//print_r($doc_verify_field);die;
			//echo $manager_details;print_r($remark_field);die('9');
			if(in_array("occupier_details", $remark_field)) {
				if(empty($occupier_details)){
					$verify_details = str_replace('occupier_details,', '' ,$verify_details); 
				}
			}
			if(in_array("manager_details", $remark_field)) {
				if(empty($manager_details)){
					$verify_details = str_replace('manager_details,', '' ,$verify_details); 
				}
			}
			if(in_array("director_details", $remark_field)) {
				if(empty($director_details)){
					$verify_details = str_replace('director_details,', '' ,$verify_details); 
				}
			}
		}
		$verify_duplicated_data = $verify_details . $occupier_details. $manager_details. $director_details;

		$verify_details = implode(',', array_unique(explode(',', $verify_duplicated_data)));
		//echo $verify_details;die;
		//echo $remark_table_id.'-'.$remark_id;die; 
	  	if($remark_table_id==$remark_id){
			$cafa_remarks = array(
				'sending_time' 	  	 => date('Y-m-d h:i'),
				'remark_type'	  	 => 'n',
				'verify_details'	 => $verify_details,
				//'doc_verify'		 => $documents_list,
			);
			$queryupdate_remarks	=	db_update('fa_cafa_remarks');
			$queryupdate_remarks	->	fields($cafa_remarks);
			$queryupdate_remarks	->	condition('id',$remark_id,'=');	
			$queryupdate_remarks	->	execute();
				
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
	
				$checklist_observations_ref = array('remark_table_id'=> $remark_id );
					
				$queryupdate_observations_ref		 =	db_update('fa_checklist_observations_ref');
				$queryupdate_observations_ref	 	->	fields($checklist_observations_ref);
				$queryupdate_observations_ref		 ->	condition('id',$checklist_observations_ref_id,'=');	
				$queryupdate_observations_ref		 ->	execute();
		}
	
	}
	

		$identity_flag = 'occupier_details';
		$irregularities_details_name =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factorytype_id,$service_id);
		if(!empty($irregularities_details_name)){
			foreach($irregularities_details_name as $row_irregularities_details_name){
				$irregularities_update = array(
					'remark_by_ad'			=> $val['factory_adchk_'.$row_irregularities_details_name->id],
					'modification_by'		=> $userid,
					'modification_date'		=> date('Y-m-d'),
				);
				$queryupdate_irregularities		 =	db_update('fa_checklist_observations');
				$queryupdate_irregularities		 ->	fields($irregularities_update);
				$queryupdate_irregularities		 ->	condition('id',$row_irregularities_details_name->id,'=');	
				$queryupdate_irregularities		 ->	execute();
			}
		
		}else{
		
		$irregularities_1 = array(
			'irregularities'				=> $occupier_irregularities_1,
			'remark_by_ad'					=> $occupier_chk_1,
			'ad_details'					=> $userid.','.$remark_by_name ,
			'checklist_observations_ref_id' => $checklist_observations_ref_id,
			'modification_by'				=> $userid,
			'modification_date'				=> date('Y-m-d'),
			'identity_flag'					=> 'occupier_details',
		);

		$irregularities_2 = array(
			'irregularities'				=> $occupier_irregularities_2,
			'remark_by_ad'					=> $occupier_chk_2,
			'ad_details'					=> $userid.','.$remark_by_name ,
			'checklist_observations_ref_id' => $checklist_observations_ref_id,
			'modification_by'				=> $userid,
			'modification_date'				=> date('Y-m-d'),
			'identity_flag'					=> 'occupier_details',
		);

		$irregularities_3 = array(
			'irregularities'				=> $occupier_irregularities_3,
			'remark_by_ad'					=> $occupier_chk_3,
			'ad_details'					=> $userid.','.$remark_by_name ,
			'checklist_observations_ref_id' => $checklist_observations_ref_id,
			'modification_by'				=> $userid,
			'modification_date'				=> date('Y-m-d'),
			'identity_flag'					=> 'occupier_details',
		);
   		$irregularities_1_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_1) ->	execute();
		$irregularities_2_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_2) ->	execute(); 
		$irregularities_3_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_3) ->	execute(); 
   }


	drupal_set_message('Your observation of application is successfully Saved');

}














function view_occupier_details($application_id,$service_id,$factory_type_id,$reference_no){
	$get_occupier_data 		= array();
	$type					= '';
	$details				= '';
	$relationship			= '';
	$address_of_occupier		= '';
	$get_occupier_data = get_all_occupier_data($application_id,$service_id,$factory_type_id,$reference_no);

	//print_r($get_occupier_data);die;
	
	$Wcounter		= 0;
	$per_page		= 2;
	$current_page 	= pager_default_initialize(count($get_occupier_data), $per_page);
	$chunks 		= array_chunk($get_occupier_data, $per_page);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header			= array(
						array('data' => 'Sl. No'),
						array('data'=> 'Occupier Type/Application Year'),
						array('data'=> 'Occupier Details'),
						array('data'=> 'Permanent Address'),
						array('data'=> 'Present Address & Contact'),
						//array('data'=> 'Action'),		
					);
	if(!empty($get_occupier_data)){
		foreach($chunks[$current_page] as $details){ 
			$Wcounter++;
			if($details->occupier_is_amendment == NULL || $details->occupier_is_amendment == 0){
				$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
				else{
					$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/del-occupier-amended/'.encryption_decryption_fun('encrypt', $details->id).'/'.encryption_decryption_fun('encrypt', $details->application_occupier_id).'/'.encryption_decryption_fun('encrypt', $details->occupier_service_id).'/'.encryption_decryption_fun('encrypt', $details->factory_type_id).'/'.encryption_decryption_fun('encrypt', $details->application_reference_no).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
				}
				
				$details_occupier = $details->name_occupier.' '.$details->occupier_name_middle.' '.$details->occupier_name_last.'('.$details->type_occupier.')'.'<br/><b>Father/Husband :- </b> '.$details->father_husband_name_occupier.'<br/><b>Age :- </b> '.$details->age_occupier.'<br/><b>Telephone No. :- </b> '.$details->occupier_telephone.'<br/><b>Mobile No. :- </b> '.$details->occupier_mobile.'<br/><b>Email id :- </b> '.$details->occupier_email_id.'<br/><b>Fax No. :- </b> '.$details->occupier_fax_no;
	
				if($details->country_oprmntadr == 99)
				{
					$fieldArr_occupier			 =  array('district_oprmntadr','subdivision_oprmntadr','areatype_oprmntadr','block_oprmntadr','panchayat_oprmntadr','policestation_oprmntadr','pincodeoprmntadr','state_oprmntadr','postoffice_oprmntadr');
					$address_of_occupier	 =	$details->addrline_oprmntadr.'<br>'.get_full_address('fa_occupier_details','sub-table',$details->id,$fieldArr_occupier);
				
					$occupier_permanent_address = '<b>Aadhaar No :- </b> '.$details->aadhaar_oprmntadr.'<br/><b>Address :- </b> '.$address_of_occupier.'<br/><b>Street Name :- </b> '.$details->street_name_oprmntadr.'<br/><b>House No. :- </b> '.$details->house_no_oprmntadr;
				} else{
				
					$occupier_permanent_address = '<b>Passport No :- </b> '.$details->passport_oprmntadr.' <b>(DOI):</b>'.$details->passport_date_of_issue_oprmntadr.' <b>(DOE):</b>'.$details->passport_date_of_expiry_oprmntadr.'<br/><b>Street Name :- </b> '.$details->street_name_oprmntadr.'<br/><b>House No. :- </b> '.$details->house_no_oprmntadr.'<br/><b>Police Station :- </b> '.$details->police_station_oprmntadr;
				}

				if($details->country_oprsntadr == 99)
				{
					$fieldArr_occupier_presnt			 =  array('district_oprsntadr','subdivision_oprsntadr','areatype_oprsntadr','block_oprsntadr','panchayat_oprsntadr','policestation_oprsntadr','pincodeoprsntadr','state_oprsntadr','postoffice_oprsntadr');
					$address_of_occupier_presnt	 =	$details->addrline_oprsntadr.'<br>'.get_full_address('fa_occupier_details','sub-table',$details->id,$fieldArr_occupier_presnt);
				
					$occupier_present_address = '<b>Aadhaar No :- </b> '.$details->aadhaar_oprsntadr.'<br/><b>Address :- </b> '.$address_of_occupier.'<br/><b>Street Name :- </b> '.$details->street_name_oprsntadr.'<br/><b>House No. :- </b> '.$details->house_no_oprsntadr;

				} else{			
			
					$occupier_permanent_address = '<b>Passport No :- </b> '.$details->passport_oprsntadr.' <b>(DOI):</b>'.$details->passport_date_of_issue_oprsntadr.' <b>(DOE):</b>'.$details->passport_date_of_expiry_oprsntadr.'<br/><b>Street Name :- </b> '.$details->street_name_oprsntadr.'<br/><b>House No. :- </b> '.$details->house_no_oprsntadr.'<br/><b>Police Station :- </b> '.$details->police_station_oprsntadr;
				}
				$year_data = fetch_year_details_withid($details->calculate_year_id);


				$rows[] 	= array( 
									array('data' =>$Wcounter,'class' => array('')),
									array('data' =>$details->type_occupier.'<br/>'.$year_data['calculate_year'].'','class' => array('')),
									array('data' =>$details_occupier,'class' => array('')),
									array('data' =>$occupier_permanent_address ,'class' => array('')),
									array('data' =>$occupier_present_address ,'class' => array('')),
									//array('data' =>$delLink ,'class' => array('')),
							);
			}

		}
		$output = theme_table(
			array(
				  'header' 		=> $header,
				  'rows' 		=> $rows,
				  'attributes' 	=> array('id'=>'view_occupier_details_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
				  'sticky' 		=> true,
				  'caption' 	=> '',
				  'colgroups'	=> array(),
				  'empty'		=> t("No data found!") // The message to be displayed if table is empty
				)
			).theme('pager');	
	return $output;	
}
function view_director_proipietor_details($application_id,$service_id,$factory_typeid,$reference_number){
	$get_director_data = array();
	$type					= '';
	$details				='';
	$relationship			= '';
	$address_of_director	='';
	
	$get_director_data = get_director_details_service($application_id,$service_id,$factory_typeid,$reference_number);
	//print_r($get_director_data);die();
	
	$Wcounter		= 0;
	$per_page		= 2;
	$current_page 	= pager_default_initialize(count($get_director_data), $per_page);
	
	$chunks 		= array_chunk($get_director_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header			= array(
						array('data' => 'Sl. No'),
						array('data'=> 'Director Type'),
						array('data'=> 'Director Details'),
						array('data'=> 'Permanent Address'),
						array('data'=> 'Present Address & Contact'),
						//array('data'=> 'Action'),		
					);
	if(!empty($get_director_data)){
		foreach($chunks[$current_page] as $details){ 
			$Wcounter++;
			if(!empty($details->din_director)){
				$din = 'DIN:-'.$details->din_director;
				}	
			$type =$details->type_director;
				 if($type == 'pv' || $type == 'ltd'){
					 $director_type 	= 'Director';
				}if($type == 'par_firm'){
					 $director_type 	= 'Partner';
				 }if($type == 'pro_firm'){
					 $director_type 	= 'Proprietor';
				 }if($type == 'govt' || $type == 'psu'){
					 $director_type 	= 'Nominated Occupier';
				 }if($type=="registered"){
					$director_type = "Registered Society under Society Register";
				}if($type=="cooperative"){
					$director_type = "Co-operative";
				}if($$type=="localbody"){
					$director_type = "Local Body";
				}if($type=="others"){
					$director_type = "Others";
				}if($type=="llp"){
					$director_type = "Limited Liability Partnership";
				}
			if(!empty($details->age_director)){
				$age = 'Age- '.$details->age_director;
				}
			$is_occupier =$details->is_occupier;
			
			$relation =$details->relationship_director;
			 if($relation == 1){
				$relationship = 'D/O';
			}
			 if($relation == 2){
				$relationship = 'S/O';
			}
			 if($relation == 3){
				$relationship = 'W/O';
			}
			if($is_occupier == 1){
				$occupier = '<br/>(Occupier)';
			}else{$occupier = '';}
			if($details->application_status == 'F'){
				$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
			else if($details->worker_plan_approval_status == 'F'){
				$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
			
				else{
					$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/del-dir-registration/'.encryption_decryption_fun('encrypt', $details->id).'/'.encryption_decryption_fun('encrypt', $details->application_director_id).'/'.encryption_decryption_fun('encrypt', $details->director_service_id).'/'.encryption_decryption_fun('encrypt', $details->factory_type_id).'/'.encryption_decryption_fun('encrypt', $details->application_reference_no).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
				}
		$fieldArr_director			 =  array('district_director','sub_division_director','area_type_director','block_mun_cor_sez_not_director','grm_ward_sector_not_director','police_station_director','pincode_director','state_director','post_office_director');
    $address_of_director	 =	$details->adress_line1_director.'<br>'.get_full_address('fa_director_details','sub-table',$details->id,$fieldArr_director);
			$rows[] 	= array( 
								array('data' =>$Wcounter,'class' => array('')),
								array('data' =>$director_type ,'class' => array('')),
								array('data' =>$details->name_director.'<br>'.$din.'<br>'.$relationship.'-'.$details->father_husband_name_director.'<br>'.$age,'class' => array('')),
								array('data' =>$address_of_director ,'class' => array('')),
								array('data' =>$details->addrline_oprsntadr.'<br>'.'Telephone: '.$details->director_telephone.'<br>'.'Mobile: '.$details->director_mobile.'<br>'.'FAX: '.$details->director_fax_no.'<br>'.'Email: '.$details->director_email_id ,'class' => array('')),
								//array('data' =>$delLink ,'class' => array('')),
								//array('data' =>'View' ,'class' => array('')),
							);
		} 
		
	}
	$output = theme_table(
	array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'view_director_details_id1', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '(2). All Director List',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
		 return $output;
	
	
}

	

function view_manager_details($application_id,$service_id,$factory_type_id,$reference_number){
	$get_manager_data 		= array();
	$type					= '';
	$details				= '';
	$relationship			= '';
	$address_of_manager		= '';
	$get_manager_data = get_all_manager_data($application_id,$service_id,$factory_type_id,$reference_number);
	
	$Wcounter		= 0;
	$per_page		= 2;
	$current_page 	= pager_default_initialize(count($get_manager_data), $per_page);
	$chunks 		= array_chunk($get_manager_data, $per_page);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header			= array(
						array('data' => 'Sl. No'),
						
						array('data'=> 'Manager Details'),
						array('data'=> 'Permanent Address'),
						array('data'=> 'Present Address & Contact'),
						//array('data'=> 'Action'),		
					);
	if(!empty($get_manager_data)){
		
		foreach($chunks[$current_page] as $manager_details){ 
			$Wcounter++;
			
			if($manager_details->relationship_manager == '1'){
				$relationship = 'D/O';
			}if($manager_details->relationship_manager == '2'){
				$relationship = 'S/O';
			}if($manager_details->relationship_manager == '3'){
				$relationship = 'W/O';
			}
			if($manager_details ->application_status == 'F'){
				$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
				else{
					$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/del-manager-registration/'.encryption_decryption_fun('encrypt', $manager_details->id).'/'.encryption_decryption_fun('encrypt', $manager_details->application_manager_id).'/'.encryption_decryption_fun('encrypt', $manager_details->manager_service_id).'/'.encryption_decryption_fun('encrypt', $manager_details->factory_type_id).'/'.encryption_decryption_fun('encrypt', $manager_details->application_reference_no).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
				}
		
		$fieldArr_manager			 =  array('district_manager','sub_division_manager','area_type_manager','block_mun_cor_sez_not_manager','grm_ward_sector_not_manager','police_station_manager','pincode_manager','state_manager','post_office_manager');
   $address_of_manager	 =	$manager_details->adress_line1_manager.'<br>'.get_full_address('fa_manager_details','sub-table',$manager_details->id,$fieldArr_manager);
     $manager_details_view =$manager_details->name_manager.'<br/>' .$relationship.'-'.$manager_details->father_husband_name_manager.'<br/>Age:-'.$manager_details->age_manager;
			$rows[] 	= array( 
								array('data' =>$Wcounter,'class' => array('')),
								
								array('data' =>$manager_details_view,'class' => array('')),
								array('data' =>$address_of_manager ,'class' => array('')),	
								array('data' =>$manager_details->manager_present_address.'<br>'.'Telephone: '.$manager_details->manager_telephone.'<br>'.'Mobile: '.$manager_details->manager_phone.'<br>'.'FAX: '.$manager_details->manager_fax.'<br>'.'Email: '.$manager_details->manager_email ,'class' => array('')),
								//array('data' =>$delLink ,'class' => array('')),
								);
				} 
		
		}
		$output = theme_table(
			array(
				  'header' => $header,
				  'rows' => $rows,
				  'attributes' => array('id'=>'view_manager_details_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
				  'sticky' => true,
				  'caption' => '(1). All Manager List',
				  'colgroups' => array(),
				  'empty' => t("No data found!") // The message to be displayed if table is empty
				)
			).theme('pager');	
		 	return $output;	
}


?> 