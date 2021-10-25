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
		'#prefix'			=> '<div class="row"><div class="col-md-12">',
		'#suffix' 		    => '</div></div>',
		'#type' 			=> 'markup',
		'#markup' 			=> view_owner_details($application_id,$service_id,$factory_type_id,$reference_no),
	);			
	$form['factory_part_owner']['owner_details'] = array(
		'#prefix'			=> '<div class="row"><div class="col-md-2 col-xs-2"><br/>',
		'#suffix' 			=> '</div></div>',
	  	'#type' 			=> 'checkbox',
	  	'#id'				=> 'owner_details',
	  	'#default_value' 	=> $owner_details_ck ,
	  	'#title' 			=> t('Is Owner Details Correct?'),
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
 	$remark_details 	= get_remark_id($application_id,$reference_no,$userid,$rid);
	$verify_details 	= $remark_details['verify_details'];
	$remark_id			= $remark_details['id'];

 	if(!empty($irregularities_details)){
		foreach($irregularities_details as $row_irregularities_details){
			$remark_table_id = $row_irregularities_details->remark_table_id;
			$checklist_observations_ref_id = $row_irregularities_details->checklist_observations_ref_id;
		}
		
		
	
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