<?php
function details_of_manager_registration($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$referenceno) {	
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	global $base_root, $base_path, $user;
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	$reference_number 		= encryption_decryption_fun('decrypt', $referenceno);
	

	///echo $application_id.'--'.$service_id.'--'.$factory_type_id.'--'.$link_number.'--'.$link_number.'--'.$flag_mapp.'--'.$link_date;die;

	    
	$remark_fetch = get_checking($application_id,$service_id,$factory_type_id,$reference_number);

	$verify_details = $remark_fetch['verify_details'];
	
	if(!empty($verify_details)){
		$remark_field = explode(',', $verify_details);
		//print_r($doc_verify_field);die;
		foreach ($remark_field as $fieldname){ 
			//echo $fieldname;
			if($fieldname == 'director_details'){ $director_details_ck = 1;}
			if($fieldname == 'manager_details'){ $manager_details_ck = 1;}
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

	//////////////Start Form/////////////////////
	  $form['header']            = array(
        '#markup' => t('<div class="content"><h1><font color ="red">UNDER DEVELOPMENT</font></h1><h3>Application for Registration and Grant of Licence.All inputs are provided by applicant only.
						All inputs are to be verified by officials</h3>')
    );
	$form['manager_part_details'] = array(
		'#type' 		=> 'fieldset',
		'#title' 		=> t('Details of manager Permanent/Present Address '),
		'#collapsible' 	=> TRUE, // Added
		'#collapsed' 	=> FALSE,  // Added
	);
	
	$form['manager_part_details']['view_manager'] = array(
		'#prefix'		=> '<div class="row"><div id="view_manager_details_id"><div class="col-md-10">',
		'#suffix' 		=> '</div></div>',
		'#type'			=> 'markup',
		'#markup'		=> view_manager_details($application_id,$service_id,$factory_type_id,$reference_number),
	);

	$form['manager_part_details']['manager_details'] = array(
		'#prefix'			=> '<div class="col-md-2 col-xs-2"><br/>',
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
		'#prefix' 		=> '<div class="row"><div id="view_director_details_id"><div class="col-md-10">',
		'#type'		=> 'markup',
		'#markup'		=>	view_director_proipietor_details($application_id,$service_id,$factory_type_id,$reference_number),
		'#suffix' 		=> '</div></div>'
	);
	$form['director_part_details']['director_details'] = array(
		'#prefix'			=> '<div class="col-md-2 col-xs-2"><br/>',
		'#suffix' 			=> '</div></div>',
	  	'#type' 			=> 'checkbox',
	  	'#id'				=> 'director_details',
	  	'#default_value' 	=> $director_details_ck ,
	  	'#title' 			=> t('Is director Details Correct?'),
	);	
	
    $form['submit'] = array(
        '#prefix' => '<div class="col-md-1">',
        '#suffix' => '</div>',
        '#attributes' => array('class' => array('btn btn-success')),
        '#type' => 'submit',
        '#value' => 'Save'
    );
	
	
	return $form;
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



function details_of_manager_registration_submit($form, &$form_state){

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


	$manager_details_ck 	= $val['manager_details'];
	$director_details_ck 	= $val['director_details'];

	$manager_details	 	=!empty($val['manager_details'])?'manager_details,':NULL;
	$director_details	 	=!empty($val['director_details'])?'director_details,':NULL;

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
			else {
				$verify_details = $verify_details . $manager_details. $director_details;
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
	
	 	// $checklist_observations_ref = array(
		// 						'remark_table_id'	 => $remark_id,
								
		// 				);
					
		// 		$queryupdate_observations_ref		 =	db_update('fa_checklist_observations_ref');
		// 		$queryupdate_observations_ref	 	->	fields($checklist_observations_ref);
		// 		$queryupdate_observations_ref		 ->	condition('id',$checklist_observations_ref_id,'=');	
		// 		$queryupdate_observations_ref		 ->	execute();
	
	
		}

		drupal_set_message('Your observation of application is successfully Saved');
	}

}

?>