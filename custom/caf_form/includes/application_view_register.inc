<?php
//$applicationid
function application_view_register($form, &$form_state,$serviceid, $factory_typeid,$applicationid,$referenceid) {	

	global $base_root,$base_path,$user;
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/sky-forms.css');
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$reference_no 		= encryption_decryption_fun('decrypt',$referenceid);
	$form = array();
	if (!empty($application_id)) {
        $get_fa_cafa           				= 	get_fa_cafa($application_id);
       	$application_status      			= 	$get_fa_cafa['application_status'];
		$plan_approve_status      			= 	$get_fa_cafa['plan_approve_status'];
		$factory_identification_number		= 	$get_fa_cafa['factory_reg_identification_number'];
		$factory_referance_number			= 	$get_fa_cafa['reference_number'];	
    }
	//print_r($get_fa_cafa);die;
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
		'#markup' 			=> get_all_application($service_id,$factory_type_id,$application_id,$reference_no),
		
  	);	
	$form['serviceid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$service_id)
			 
	);	
	$form['factorytype_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$factory_type_id)
			 
	);		  
	$form['factory_identification_number_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> empty($factory_identification_number)?'':encryption_decryption_fun('encrypt',$factory_identification_number)
			 
	);	   
	$form['referance_no_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$reference_no),
			 
	);
	
	$form['application_id_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt', $application_id),
			 
	);
	$form['applicantion_occupier'] = array(
		'#type' 			=> 'fieldset',
		'#title' 			=> t('Occupier Information'),
		'#collapsible' 		=> TRUE, // Added
		'#collapsed' 		=> FALSE,  // Added
  	); 
          
    $form['applicantion_occupier']['markup_appplication'] = array(
		'#type' 			=> 'markup',
		'#markup' 			=> get_all_occupier($service_id,$factory_type_id,$application_id,$reference_no),
		
  	);   
	$form['applicantion_worker'] = array(
		'#type' 			=> 'fieldset',
		'#title' 			=> t('Workers Information'),
		'#collapsible' 		=> TRUE, // Added
		'#collapsed' 		=> FALSE,  // Added
  	); 
          
    $form['applicantion_worker']['markup_appplication'] = array(
		'#type' 			=> 'markup',
		'#markup' 			=> get_all_worker_data($service_id,$factory_type_id,$application_id,$reference_no),
		
  	);   
		$form['applicantion_directors'] = array(
			'#type' 			=> 'fieldset',
			'#title' 			=> t('Details of Directors/Partners/Proprietor Information'),
			'#collapsible' 		=> TRUE, // Added
			'#collapsed' 		=> FALSE,  // Added
		); 
	$form['applicantion_directors']['markup_appplication'] = array(
			'#type' 			=> 'markup',
			'#markup' 			=> get_all_directors($service_id,$factory_type_id,$application_id,$reference_no),
			
			
		); 
		  
	$form['applicantion_manager'] = array(
			'#type' 			=> 'fieldset',
			'#title' 			=> t('Manager Information'),
			'#collapsible' 		=> TRUE, // Added
			'#collapsed' 		=> FALSE,  // Added
		); 
			  
	$form['applicantion_manager']['markup_appplication'] = array(
			'#type' 			=> 'markup',
			'#markup' 			=> get_all_manager($service_id,$factory_type_id,$application_id,$reference_no),
			
		);    
	$form['applicantion_power'] = array(
		'#type' 			=> 'fieldset',
		'#title' 			=> t('Factory Power'),
		'#collapsible' 		=> TRUE, // Added
		'#collapsed' 		=> FALSE,  // Added
  	); 
          
    $form['applicantion_power']['markup_appplication'] = array(
		'#type' 			=> 'markup',
		'#markup' 			=> get_uploaded_power_data($application_id,$service_id,$factory_type_id,$factory_referance_number),
		
  	); 
	$form['applicantion_nature'] = array(
		'#type' 			=> 'fieldset',
		'#title' 			=> t('Factory Nature Manufacturing'),
		'#collapsible' 		=> TRUE, // Added
		'#collapsed' 		=> FALSE,  // Added
  	); 
          
    $form['applicantion_nature']['markup_appplication'] = array(
		'#type' 			=> 'markup',
		'#markup' 			=> get_nature_manufacturing_data($application_id,$service_id,$factory_type_id,$factory_referance_number),
		
  	);     
	$form['applicantion_documents'] = array(
		'#type' 			=> 'fieldset',
		'#title' 			=> t('Related Documents'),
		'#collapsible' 		=> TRUE, // Added
		'#collapsed' 		=> FALSE,  // Added
  	); 
          
    $form['applicantion_documents']['markup_appplication'] = array(
		'#type' 			=> 'markup',
		'#markup' 			=> get_uploaded_document_data($service_id,$factory_type_id,$application_id,$factory_referance_number),
		
  	);   
	
	/* REMARKS NOTESHEET */
	$form['applicantion_remark'] = array(
		'#type' 			=> 'fieldset',
		'#title' 			=> t('Remark and Forword'),
		'#collapsible' 		=> TRUE, // Added
		'#collapsed' 		=> FALSE,  // Added
  	); 
	$form['applicantion_remark']['application_note'] = array(
        '#prefix' => '<div class="col-md-12"><label class="input">',
        '#suffix' => '</label></div>',
        '#type' => 'textarea',
        '#default_value' => $factory_name
    );
	
	$form['applicantion_remark']['submit'] = array(
        '#prefix' => '<div class="col-md-4">',
        '#suffix' => '</div></div></div></div>',
        '#attributes' => array('class' => array('btn btn-info')),
        '#type' => 'submit',
        '#value' => 'NOTESHEET'
    );
	
	/* REMARKS NOTESHEET */ 
            return $form; 
        
         }

function get_all_application($service_id,$factory_type_id,$application_id,$reference_no){
	global $base_root,$base_path,$user;
	$applicant_id 			= $user->uid;
	$get_all_data 			= array();
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
									array('data' =>'<b>Zone:-</b> '.$details_general_info->zone_name ,'class' => array('')),
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

function get_all_occupier($service_id,$factory_type_id,$application_id,$reference_no){
	global $base_root,$base_path,$user;
	$applicant_id 			= $user->uid;
	$occupier_details 		= array();
	$type					= '';
	$details				='';
	$relationship			='';
	$address_of_director	='';					
	/* Occupier DETAILS */
	$occupier_details = get_occupier_data($application_id);
	$getdata_director_paddress =  array('district_director','sub_division_director','area_type_director','block_mun_cor_sez_not_director','grm_ward_sector_not_director','police_station_director','pincode_director','state_director','post_office_director');
	$header = array(
		array('data'=> 'SL No'),
		array('data'=> 'Occupier Name'),
		array('data'=> 'Occupier Type'),
		array('data'=> 'Nationality'),
		array('data'=> 'Adhaar/Passport'),
		array('data'=> 'Father/Husband Name'),
		array('data'=> 'Present address'),
		array('data'=> 'Permanent address'),
		array('data'=> 'Service Year'),
		array('data'=> 'Act')
	);
								
	if(!empty($occupier_details)){
		$i=1;
			foreach($occupier_details as $occupier){ 
			
			$permanent_address =	get_full_address('fa_director_details','sub-table',$occupier->id,$getdata_director_paddress);
			$present_address =	get_full_address('fa_director_details','sub-table',$occupier->id,array('district_oprsntadr','subdivision_oprsntadr','areatype_oprsntadr','block_oprsntadr','panchayat_oprsntadr','policestation_oprsntadr','pincodeoprsntadr','state_oprsntadr','postoffice_oprsntadr'));
			if(!empty($occupier->director_aadhaar)){
				$number = 'Aadhaar- '.$occupier->director_aadhaar;
				}
				if(!empty($occupier->director_passport)){
				$number = 'Passport- '.$occupier->director_passport;
				}
					$rows[] = array( 
								array('data' => t($i)), 	
								array('data' =>$occupier->name_director ,'class' => array('')),
								array('data' =>$occupier->type_director ,'class' => array('')),
								array('data' => $occupier->director_nationality ,'class' => array('')),
								array('data' =>$number ,'class' => array('')),
								array('data' =>$occupier->father_husband_name_director  ,'class' => array('')),
								array('data' =>$present_address ,'class' => array('')),
								array('data' =>$permanent_address.'<br>Phone:- '.$occupier->director_telephone.'<br>Mobile:- '.$occupier->director_mobile.'<br>Email:- '.$occupier->director_email_id.'<br>FAX:- '.$occupier->director_fax_no ,'class' => array('')),
								array('data' =>$occupier->add_year_director ,'class' => array('')),
								array('data' =>get_service_name($occupier->director_service_id) ,'class' => array('')),
								
							);
			$i++;
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


function get_all_worker_data($application_id,$service_id,$factory_typeid,$reference_no){
	global $base_root,$base_path,$user;
	$applicant_id 			= $user->uid;
	$worker_details 		= array();
	$type					= '';
	$details				='';
	$relationship			='';
	$address_of_director	='';					
	/* WORKER DETAILS */
	$worker_details = get_worker_details_service($application_id,$service_id,$factory_typeid,$reference_no);
	$header = array(
		array('data'=> 'SL No'),
		array('data'=> 'No. of Worker Male'),
		array('data'=> 'No. of Worker Male'),
		array('data'=> 'Adolescents Male'),
		array('data'=> 'Adolescents Female'),
		array('data'=> 'Children Male'),
		array('data'=> 'Children Female'),
		array('data'=> 'Total Worker'),
		array('data'=> 'Service Year'),
		array('data'=> 'Act')
	);
								
	if(!empty($worker_details)){
		$i=1;
			foreach($worker_details as $worker){ 
			
					$rows[] = array( 
								array('data' => t($i)), 	
								array('data' =>$worker->worker_men ,'class' => array('')),
								array('data' =>$worker->worker_women ,'class' => array('')),
								array('data' =>$worker->adolescents_male ,'class' => array('')),
								array('data' =>$worker->adolescents_female ,'class' => array('')),
								array('data' =>$worker->children_male ,'class' => array('')),
								array('data' =>$worker->children_female ,'class' => array('')),
								array('data' =>$worker->worker_total ,'class' => array('')),
								array('data' =>$worker->service_year ,'class' => array('')),
								array('data' =>get_service_name($worker->service_id) ,'class' => array('')),
								
							);
			$i++;
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


function get_all_directors($service_id,$factory_type_id,$application_id,$reference_no){
	global $base_root,$base_path,$user;
	$applicant_id 			= $user->uid;
	$occupier_details 		= array();
	$type					= '';
	$details				='';
	$relationship			='';
	$address_of_director	='';					
	/* Occupier DETAILS */
	$occupier_details = get_director_details_service($application_id,$service_id,$factory_type_id,$reference_no);
	$getdata_director_paddress =  array('district_director','sub_division_director','area_type_director','block_mun_cor_sez_not_director','grm_ward_sector_not_director','police_station_director','pincode_director','state_director','post_office_director');
	$header = array(
		array('data'=> 'SL No'),
		array('data'=> 'Director Name'),
		array('data'=> 'Director Type'),
		array('data'=> 'Father/Husband Name'),
		array('data'=> 'Address'),
		array('data'=> 'Service Year'),
		array('data'=> 'Act')
	);
								
	if(!empty($occupier_details)){
		$i=1;
			foreach($occupier_details as $occupier){ 
			
			$permanent_address =	get_full_address('fa_director_details','sub-table',$occupier->id,$getdata_director_paddress);
			$present_address =	get_full_address('fa_director_details','sub-table',$occupier->id,array('district_oprsntadr','subdivision_oprsntadr','areatype_oprsntadr','block_oprsntadr','panchayat_oprsntadr','policestation_oprsntadr','pincodeoprsntadr','state_oprsntadr','postoffice_oprsntadr'));
			
					$rows[] = array( 
								array('data' => t($i)), 	
								array('data' =>$occupier->name_director ,'class' => array('')),
								array('data' =>$occupier->type_director ,'class' => array('')),
								
								
								array('data' =>$occupier->father_husband_name_director  ,'class' => array('')),
								//array('data' =>$present_address ,'class' => array('')),
								array('data' =>$permanent_address.'<br>Phone:- '.$occupier->director_telephone.'<br>Mobile:- '.$occupier->director_mobile.'<br>Email:- '.$occupier->director_email_id.'<br>FAX:- '.$occupier->director_fax_no ,'class' => array('')),
								array('data' =>$occupier->add_year_director ,'class' => array('')),
								array('data' =>get_service_name($occupier->director_service_id) ,'class' => array('')),
								
							);
			$i++;
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

function get_all_manager($service_id,$factory_type_id,$application_id,$reference_no){
	global $base_root,$base_path,$user;
	$applicant_id = $user->uid;
	$worker_detials = array();
	$type					= '';
	$details				='';
	$relationship			='';
	$address_of_director	='';
	
							
	/* WORKER DETAILS */
	$manager_details = get_manager_details_service($application_id,$service_id,$factory_type_id,$reference_no);
	
	$getdata_manager_address =  array('district_manager','sub_division_manager','area_type_manager','block_mun_cor_sez_not_manager','grm_ward_sector_not_manager','police_station_manager','pincode_manager','state_manager','post_office_manager');

	$header = array(
		array('data'=> 'SL No'),
		array('data'=> 'Mananger Name'),
		array('data'=> 'Manager Age'),
		array('data'=> 'Father/Husband'),
		array('data'=> 'Present address'),
		array('data'=> 'Permanent address'),
		array('data'=> 'Service Year'),
		array('data'=> 'Act')
	);
				
						
	if(!empty($manager_details)){
		$i=1;
		
			foreach($manager_details as $manager){
				if($manager->relationship_manager == '1'){
				$relationship = 'D/O - ';
			}elseif($manager->relationship_manager == '2'){
				$relationship = 'S/O - ';
			}elseif($manager->relationship_manager == '3'){
				$relationship = 'W/O - ';
			} 
			$fieldArr_manager =  array('district_manager','sub_division_manager','area_type_manager','block_mun_cor_sez_not_manager','grm_ward_sector_not_manager','police_station_manager','pincode_manager','state_manager','post_office_manager');
   $address_of_manager	 =	$manager->adress_line1_manager.'<br>'.get_full_address('fa_manager_details','sub-table',$manager->id,$fieldArr_manager);
			  $owner_address =	get_full_address('fa_manager_details','sub-table',$manager->id,$getdata_manager_address);
					$rows[] = array( 
								array('data' =>$i ,'class' => array('')),
								array('data' =>$manager->name_manager ,'class' => array('')),
								array('data' =>$manager->age_manager ,'class' => array('')),
								array('data' =>$relationship. $manager->father_husband_name_manager ,'class' => array('')),
								array('data' =>$manager->manager_present_address .'<br>Phone:- '.$manager->manager_telephone.'<br>Mobile:- '.$manager->manager_phone.'<br>Fax:- '.$manager->manager_fax.'<br>Email:- '.$manager->manager_email ,'class' => array('')),
								array('data' =>$address_of_manager ,'class' => array('')),
								array('data' =>$manager->add_year_manager ,'class' => array('')),
								array('data' =>get_service_name($manager->manager_service_id) ,'class' => array('')),
							);
					
			$i++;
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
function get_uploaded_power_data($application_id,$service_id,$factory_type_id,$reference_no){
	global $base_root,$base_path,$user;
	$applicant_id = $user->uid;
	$power_details = array();
	
	/* Power Details */
	$power_details = get_power_data($application_id,$service_id,$factory_type_id,$reference_no);
	//print_r($power_details);die;
	$header = array(
		array('data'=> 'SL No'),
		array('data'=> 'Unit of power installed'),
		array('data'=> 'Nature and total amount of power installed '),
		array('data'=> 'Applied Year'),
		array('data'=> 'Act')
	);
				
						
	if(!empty($power_details)){
		$i=1;
			foreach($power_details as $power){
					$rows[] = array( 
								array('data' =>$i ,'class' => array('')),
								array('data' =>$power->power_unit ,'class' => array('')),
								array('data' =>$power->installed_power ,'class' => array('')),
								array('data' =>$power->service_year ,'class' => array('')),
								array('data' =>$power->service_name ,'class' => array('')),
							);
					
			$i++;
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
function get_nature_manufacturing_data($application_id,$service_id,$factory_type_id,$reference_no){
	global $base_root,$base_path,$user;
	$applicant_id = $user->uid;
	$nature_details = array();
	
	/* Nature Details */
	$nature_details = get_manufacturing($application_id,$service_id,$factory_type_id,$reference_no);
	//print_r($nature_details);die;
	$header = array(
		array('data'=> 'SL No'),
		array('data'=> 'Manufacturing process'),
		array('data'=> 'Applied Year'),
		array('data'=> 'Act')
	);
				
						
	if(!empty($nature_details)){
		$i=1;
			foreach($nature_details as $nature){
					$rows[] = array( 
								array('data' =>$i,'class' => array('')),
								
								array('data' =>$nature->nature_manufacturing,'class' => array('')),
								array('data' =>$nature->service_year ,'class' => array('')),
								array('data' =>get_service_name($nature->service_id) ,'class' => array('')),
							);
					
			$i++;
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

function application_view_register_submit($form, &$form_state){
	  global $user;
	  $uid = $user->uid;
	  $val   					= 	$form_state['values'];
	  $service_id 				= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']); 
	  $factorytype_id 			= 	encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
	  $plan_approve_status 		= 	encryption_decryption_fun('decrypt',$val['plan_approve_status_hidden']);
	  $application_id 			= 	encryption_decryption_fun('decrypt',$val['application_id_hidden']);
	  $reference_no				=  	encryption_decryption_fun('decrypt',$val['referance_no_hidden']);
	  
	  //---------------- CAFA TABLE UPDATE -------------------
	  
		$approval_status = 	array('application_status' => 'AI');
		$queryabc 		 =	db_update('fa_cafa');
		$queryabc		 ->	fields($approval_status);
		$queryabc		 ->	condition('id',$application_id,'=');
		$queryabc		 ->	condition('service_id',$service_id,'=');
		$queryabc	     ->	condition('factory_typeid',$factorytype_id,'=');
		$queryabc		 ->	condition('reference_number',$reference_no,'=');
		$queryabc		 ->	execute();

	  //-----------Worker table update---------------------------
		$worker_status 	= 	array('worker_registration_status' => 'AI');
		$queryabc 		 =	db_update('fa_worker_details');
		$queryabc			->	fields($worker_status);
		$queryabc		    ->	condition('application_id',$application_id,'=');
		$queryabc		    ->	condition('service_id',$service_id,'=');
		$queryabc			->	condition('factory_type',$factorytype_id,'=');
		$queryabc			->	condition('application_reference_no',$reference_no,'=');
		$queryabc			->	execute();
	  
	  //----------------Documents Update-------------------
		$doc_status 	= 	array('plan_approval_status' => 'AI');
		$queryabc 		=	db_update('fa_caf_upload_doc');
		$queryabc		->	fields($doc_status);
		$queryabc		->	condition('app_id',$application_id,'=');
		$queryabc		->	condition('upload_documents_service_id',$service_id,'=');
		$queryabc	    ->	condition('upload_doc_factory_type_id',$factorytype_id,'=');
		$queryabc		->	condition('application_reference_no',$reference_no,'=');
		$queryabc		->	execute();
		
		
		//-----------Manufacturing table update---------------------------
	  $manufacturing_status 	= 	array('manufacturing_application_status' => 'AI');
	  $querymanufacturing 		 		=	db_update('fa_nature_manufacturing');
	  $querymanufacturing			->	fields($manufacturing_status);
	  $querymanufacturing		    ->	condition('application_id',$application_id,'=');
	  $querymanufacturing		    ->	condition('service_id',$service_id,'=');
	  $querymanufacturing			->	condition('factory_type',$factorytype_id,'=');
	  $querymanufacturing			->	condition('application_reference_no',$reference_no,'=');
	  $querymanufacturing			->	execute();
	  
	  //-----------Power table update---------------------------
	  $power_status 	= 	array('power_application_status' => 'AI');
	  $querypower 		=	db_update('fa_power_details');
	  $querypower			->	fields($power_status);
	  $querypower		    ->	condition('application_id',$application_id,'=');
	  $querypower		    ->	condition('service_id',$service_id,'=');
	  $querypower			->	condition('factory_type',$factorytype_id,'=');
	  $querypower			->	condition('application_reference_no',$reference_no,'=');
	  $querypower			->	execute();
	  
	  //-----------Director table update---------------------------
	  $director_status 	= 	array('application_status' => 'AI');
	  $querydirector 		=	db_update('fa_director_details');
	  $querydirector			->	fields($director_status);
	  $querydirector		    ->	condition('application_director_id',$application_id,'=');
	  $querydirector		    ->	condition('director_service_id',$service_id,'=');
	  $querydirector			->	condition('factory_type_id',$factorytype_id,'=');
	  $querydirector			->	condition('application_reference_no',$reference_no,'=');
	  $querydirector			->	execute();
	  
	  //-----------Manager table update---------------------------
	  $manager_status 	= 	array('application_status' => 'AI');
	  $querymanager 		=	db_update('fa_manager_details');
	  $querymanager			->	fields($manager_status);
	  $querymanager		    ->	condition('application_manager_id',$application_id,'=');
	  $querymanager		    ->	condition('manager_service_id',$service_id,'=');
	  $querymanager			->	condition('factory_type_id',$factorytype_id,'=');
	  $querymanager			->	condition('application_reference_no',$reference_no,'=');
	  $querymanager			->	execute();

	//----------------Remarks Table Insert -------------------

		$cafa_remarks = array(
		'app_id'   			 => $application_id,
		'remark_by_uid' 	 => $uid,
        //'remark_by_roleid' => ,
		//'remark_by_name' 	 => ,
		'sending_time' 		 => date('Y-m-d h:i:s'),
		'app_reference_no' 	 => $reference_no,
		'remarks' 	         => $val['application_note'],
		'status' 			 => 'AI',
		);
		
		db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();
		drupal_set_message('Your remarks has been successfully forwarded to Area Inspector.');
		drupal_goto('regsection-dashboard/');
	
		}


?>