<?php
//$applicationid
function applicantion_preview_new_registration($form, &$form_state,$serviceid, $factory_typeid,$applicationid, $linknumber,$flagmapp) {	

	global $base_root,$base_path,$user,$_SESSION;
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/sky-forms.css');
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$form = array();
	if (!empty($application_id)) {
        $get_fa_cafa           			= 	get_fa_cafa($application_id);
       	$application_status      		= 	$get_fa_cafa['application_status'];
		$identification_number			= 	$get_fa_cafa['plan_approve_identification_number'];
		
    }
	$form['header'] = array(
		'#markup' 			=> t('<div class="content"><div class="sky-form"><h3><b>Application Preview</b></h3>'),
	);
		

   $form['applicantion_preview'] = array(
		'#type' 			=> 'fieldset',
		'#title' 			=> t('Factory Information'),
		'#collapsible' 		=> TRUE, // Added
		'#collapsed' 		=> FALSE,  // Added
  	);
	$form['applicantion_preview']['markup_appplication'] = array(
		'#type' 			=> 'markup',
		'#markup' 			=> get_all_aplication($service_id,$factory_type_id,$application_id),
		
  	);	
	$form['serviceid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $serviceid
			 
	);	
	$form['factorytype_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $factorytype
			 
	);		  
	$form['identification_number_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> empty($identification_number)?'':encryption_decryption_fun('encrypt',$identification_number)
			 
	);	   
	$form['applicantion_worker'] = array(
		'#type' 			=> 'fieldset',
		'#title' 			=> t('Workers Information'),
		'#collapsible' 		=> TRUE, // Added
		'#collapsed' 		=> FALSE,  // Added
  	); 
          
    $form['applicantion_worker']['markup_appplication'] = array(
		'#type' 			=> 'markup',
		'#markup' 			=> get_all_worker($service_id,$factory_type_id,$application_id),
		
  	);   
	
	$form['applicantion_manager'] = array(
			'#type' 			=> 'fieldset',
			'#title' 			=> t('Manager Information'),
			'#collapsible' 		=> TRUE, // Added
			'#collapsed' 		=> FALSE,  // Added
		); 
			  
		$form['applicantion_manager']['markup_appplication'] = array(
			'#type' 			=> 'markup',
			'#markup' 			=> get_all_manager($service_id,$factory_type_id,$application_id),
			
		);     
	$form['applicantion_documents'] = array(
		'#type' 			=> 'fieldset',
		'#title' 			=> t('Related Documents'),
		'#collapsible' 		=> TRUE, // Added
		'#collapsed' 		=> FALSE,  // Added
  	); 
          
    $form['applicantion_documents']['markup_appplication'] = array(
		'#type' 			=> 'markup',
		'#markup' 			=> get_uploaded_document_data($service_id,$factory_type_id,$application_id),
		
  	);   
	$form['submit'] = array (
					  '#prefix' 		=> '</div></div>',  
					 
					  '#type' 			=> 'submit',
					  '#attributes' 	=> array('class' => array('button')),
					  '#value' 			=> 'Save & Continue'										  
				   );  
            return $form; 
        
         }

function get_all_aplication($service_id,$factory_type_id,$application_id){
	global $base_root,$base_path,$user,$_SESSION;
	$applicant_id = $user->uid;
	$get_all_data = array();
	$type					= '';
	$details				='';
	$relationship			='';
	$address_of_director	='';

	/* GENERAL INFO */
	$get_all_data =  get_application_withid($application_id);
	//echo "<pre>"; print_r($get_all_data);//die();
	
	
	$header_general_info = array(
								array('data' => 'Genaral Information', 'colspan' => 3),
						);
	if(!empty($get_all_data)){
			foreach($get_all_data as $details_general_info){ 
					
			 		$rows_general_info[] = array( 
									array('data' =>'<b>Factory Name:- </b> '.$details_general_info->factory_name ,'class' => array('')),
									//array('data' =>'<b>Previous Name:-</b>  '.$details_general_info->factory_previous_name ,'class' => array('')),
									array('data' =>'<b>Type:-</b> '.$details_general_info->factory_type ,'class' => array('')),
									array('data' =>'<b>PAN:-</b> '.$details_general_info->factory_pan ,'class' => array('')),
								);
		} 
		
	}
	$output_general_info = theme_table(
	array(
		  'header' => $header_general_info,
		  'rows' => $rows_general_info,
		  'attributes' => array('class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") 
		)
	);	
	
	/* FACTORY ADDRESS PART */
	$getdata_factory_address =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$getdata_headoffice_address =  array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
	
	$header_address_info = array(
								array('data' => 'Factory Address ', 'colspan' => 2),
						   );
						
	if(!empty($get_all_data)){
			foreach($get_all_data as $details_address_info){ 
			
				    $factory_address =	get_full_address('fa_cafa','sub-table',$details_address_info->id,$getdata_factory_address);
					$headoffice_address = get_full_address('fa_cafa','sub-table',$details_address_info->id,$getdata_headoffice_address);
					
					$rows_address_info[] = array( 
								array('data' =>'<b>Location of Factory:-</b> '.$factory_address.'<br>'.$details_general_info->addrline ,'class' => array('')),
								array('data' =>'<b>Registered office / Head office:-</b> '.$headoffice_address.'<br>'.$details_general_info->addrline_off ,'class' => array('')),
							);
			}
	}
	$output_address_info = theme_table(
	array(
		  'header' => $header_address_info,
		  'rows' => $rows_address_info,
		  'attributes' => array('class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") 
		)
	);
	
	
	/* OCCUPIER INFO */
	$getdata_occupier_present_address =  array('district_oprsntadr','subdivision_oprsntadr','areatype_oprsntadr','block_oprsntadr','panchayat_oprsntadr','policestation_oprsntadr','pincodeoprsntadr','state_oprsntadr','postoffice_oprsntadr');
	
	$header_occupier_info = array(
									array('data' => 'Occupier Details', 'colspan' => 5),
							);
	if(!empty($get_all_data)){
			foreach($get_all_data as $details_occupier_info){ 
			
			 		$rows_occupier_info[] = array( 
									array('data' =>'<b>Nationailty:- </b> '.$details_occupier_info->occupier_nationality ,'class' => array('')),
									array('data' =>'<b>Aadhaar No:-</b>  '.$details_occupier_info->occupier_aadhaar ,'class' => array('')),
									array('data' =>'<b>Mobile No:- </b> '.$details_occupier_info->occupier_mobile ,'class' => array('')),
									
								);
			}
			foreach($get_all_data as $details_occupier_info){ 
			
				    $present_address =	get_full_address('fa_cafa','sub-table',$details_occupier_info->id,$getdata_occupier_present_address);
					
					$rows_occupier_info[] = array( 
									array('data' =>'<b>Name:- </b> '.$details_occupier_info->occupier_name ,'class' => array('')),
									array('data' =>'<b>Email:- </b> '.$details_occupier_info->occupier_email_id ,'class' => array('')),
									array('data' =>'<b>Address:-</b> '.$present_address.'<br>'.$details_occupier_info->addrline_oprsntadr ,'class' => array('')),
							);
			}
	}
	
	$output_occupier_info = theme_table(
	array(
		  'header' => $header_occupier_info,
		  'rows' => $rows_occupier_info,
		  'attributes' => array('class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") 
		)
	);
	
	/* OWNER ADDRESS PART */
	$getdata_owner_address =  array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
	
	$header_owner_address = array(
								array('data' => 'Details of owner of the premises', 'colspan' => 2),
						   );
						
	if(!empty($get_all_data)){
			foreach($get_all_data as $details_owner_address){ 
			
				    $owner_address =	get_full_address('fa_cafa','sub-table',$details_owner_address->id,$getdata_owner_address);
					
					$rows_owner_address[] = array( 
								array('data' =>'<b>Name:- </b> '.$details_owner_address->owner_name ,'class' => array('')),
								array('data' =>'<b>Address:-</b> '.$owner_address.'<br>'.$details_owner_address->addrline_premises ,'class' => array('')),
							);
			}
	}
	$output_owner_address = theme_table(
	array(
		  'header' => $header_owner_address,
		  'rows' => $rows_owner_address,
		  'attributes' => array('class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") 
		)
	);

		 return $output_general_info.$output_address_info.$output_occupier_info.$output_owner_address;	 
}

function get_all_worker($service_id,$factory_type_id,$application_id){
	global $base_root,$base_path,$user,$_SESSION;
	$applicant_id = $user->uid;
	$worker_detials = array();
	$type					= '';
	$details				='';
	$relationship			='';
	$address_of_director	='';
	
							
	/* WORKER DETAILS */
	$worker_detials = get_worker_detials_service($application_id,$service_id,$factory_type_id);
	

	$header = array(
						array('data' => 'Total Workers (Permanent & Contractual) : '.$worker_detials[0]->worker_total, 'colspan' => 5),
				);
				
						
	if(!empty($worker_detials)){
			foreach($worker_detials as $worker){ 
			
					$rows[] = array( 
								array('data' =>'<b>Permanent Male:- </b> '.$worker->worker_permanent_male ,'class' => array('')),
								array('data' =>'<b>Permanent Female:- </b>'.$worker->worker_permanent_female ,'class' => array('')),
								array('data' =>'<b>Permanent Transgender/Third Gender:- </b>'.$worker->worker_permanent_transgender ,'class' => array('')),
								array('data' =>'<b>Service Year:- </b>'.$worker->service_year ,'class' => array('')),
								array('data' =>'<b>Act:- </b>'.get_service_name($worker->service_id) ,'class' => array('')),
							);
					$rows[] = array( 
								array('data' =>'<b>Contractual Male:- </b> '.$worker->worker_contractual_male ,'class' => array('')),
								array('data' =>'<b>Contractual Female:- </b>'.$worker->worker_contractual_female ,'class' => array('')),
								array('data' =>'<b>Contractual Transgender/Third Gender:- </b>'.$worker->worker_contractual_transgender ,'class' => array('')),
								array('data' =>'<b>Service Year:- </b>'.$worker->service_year ,'class' => array('')),
								array('data' =>'<b>Act:- </b>'.get_service_name($worker->service_id) ,'class' => array('')),
							);		
			}
	}
	
	$output = theme_table(
	array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") 
		)
	);	
		 return $output;
}

function get_uploaded_document_data($service_id,$factory_type_id){
	
	$output = '';
	$header = array(
		array('data'=> 'SL No'),
		array('data'=> 'Uploaded Document Of'),
		array('data'=> 'Document Name'),
		array('data'=> 'Action')
	);

	$rows = array();
	
	$query = db_select('fa_caf_upload_doc', 'fcud');
	$query ->fields('fcud', array( 'id', 'app_id', 'uid', 'fid', 'doc_name', 'file_name'));
	$query	-> condition('fcud.app_id', $_SESSION['application_id']);
	$query	-> condition('fcud.upload_documents_service_id', $service_id);
	$query	-> condition('fcud.upload_doc_factory_type_id', $factory_type_id);
	$result = $query->execute();
	$resultData = $result->fetchAll();

	$i=1;
	foreach($resultData as $val)
	{				
		$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','cafapp/del/'.$val->id.'/'.$val->fid,array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
		
		$rows [] = array(  
			array('data' => t($val->id)), 	
			array('data' => t($val->doc_name)), 
			array('data' => t($val->file_name)),
			array('data' => $delLink),	
		);
	$i++;	
	}
	
	$output = theme_table(
	array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'table_div_replace', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	);	
	  
	return $output;	
} 
 function applicantion_preview_submit($form, &$form_state){
	  $val   					= 	$form_state['values'];
	  $service_id 				= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']); 
	  $factorytype_id 			= 	encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
	  $plan_approve_status 		= 	encryption_decryption_fun('decrypt',$val['plan_approve_status_hidden']);
	  $identification_number 	=   $val['identification_number_hidden'];
	  if($service_id == 4 || $service_id == 5){
	  //-----------Worker table update---------------------------
	  $worker_status 	= 	array('worker_plan_approval_status' => 'F');
	  $queryabc 		 =	db_update('fa_worker_details');
	  $queryabc			->	fields($worker_status);
	  $queryabc		    ->	condition('application_id',$_SESSION['application_id'],'=');
	  $queryabc		    ->	condition('service_id',$service_id,'=');
	  $queryabc			->	condition('factory_type',$factorytype_id,'=');
	  $queryabc			->	condition('application_reference_no',$_SESSION['reference_no'],'=');
	  $queryabc			->	execute();
	  //----------------Documents Update-------------------
	  
	   	$doc_status 		= 	array('plan_approval_status' => 'F');
		  $queryabc 		 =	db_update('fa_caf_upload_doc');
		  $queryabc			->	fields($doc_status);
		  $queryabc		    ->	condition('app_id',$_SESSION['application_id'],'=');
		  $queryabc		    ->	condition('upload_documents_service_id',$service_id,'=');
		  $queryabc			->	condition('upload_doc_factory_type_id',$factorytype_id,'=');
		   $queryabc		->	condition('application_reference_no',$_SESSION['reference_no'],'=');
		  $queryabc			->	execute();
		  
		  if(empty($identification_number)){
		 $identification_number = created_identification();
		 $caf_update 			= 	array('plan_approve_identification_number' => $identification_number,'plan_approve_status' => 'F');	
		 
	  }else{
		  $caf_update 			= 	array('plan_approve_status' => 'F');
	  }
	   $queryabc 		=	db_update('fa_cafa');
	   $queryabc		->	fields($caf_update);
	   $queryabc		->	condition('id',$_SESSION['application_id'],'=');
	   $queryabc	    ->	execute();
	    unset($_SESSION['serviceid']);
		unset($_SESSION['application_id']);
		unset($_SESSION['reference_no']);
		unset($_SESSION['reference_no']);
		drupal_set_message('Your application has been successfully submited. Your application number is :-'.encryption_decryption_fun('decrypt',$identification_number));
		drupal_goto('applicant/applicant-dasboard/');
	  }
	  
	 
		
 }
function get_all_manager($service_id,$factory_type_id,$application_id){
	global $base_root,$base_path,$user,$_SESSION;
	$applicant_id = $user->uid;
	$worker_detials = array();
	$type					= '';
	$details				='';
	$relationship			='';
	$address_of_director	='';
	
							
	/* WORKER DETAILS */
	$manager_detials = get_manager_detials_service($application_id,$service_id,$factory_type_id);
	
	$getdata_manager_address =  array('district_manager','sub_division_manager','area_type_manager','block_mun_cor_sez_not_manager','grm_ward_sector_not_manager','police_station_manager','pincode_manager','state_manager','post_office_manager');

	$header = array(
						array('data' => 'Manager Details : ', 'colspan' => 5),
				);
				
						
	if(!empty($manager_detials)){
			foreach($manager_detials as $manager){ 
			  $owner_address =	get_full_address('fa_manager_details','sub-table',$manager->id,$getdata_manager_address);
					$rows[] = array( 
								array('data' =>'<b>Name:- </b> '.$manager->name_manager ,'class' => array('')),
								array('data' =>'<b>Address:-</b> '.$manager->adress_line1_manager.'<br>'.$getdata_manager_address->addrline_premises ,'class' => array('')),
								array('data' =>'<b>Service Year:- </b>'.$manager->add_year_manager ,'class' => array('')),
								array('data' =>'<b>Act:- </b>'.get_service_name($manager->manager_service_id) ,'class' => array('')),
							);
					
			}
	}
	
	$output = theme_table(
	array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") 
		)
	);	
		 return $output;
}


?>