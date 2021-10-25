<?php
function applicant_worker_data_preview($ajax,$serviceid,$factory_typeid,$applicationid,$reference_no){
	if ($ajax) {
		ctools_include('ajax');
    	ctools_include('modal');
		ctools_modal_add_js();
     	$form_state = array(
					'ajax'	=> TRUE,
					'title' => t(''),
    	);
	  
      	$output = ctools_modal_form_wrapper('worker_details_preview',$form_state);
	  
   	 	if (!empty($form_state['ajax_commands'])) {
      		$output = $form_state['ajax_commands'];
		}
		print ajax_render($output);
    	drupal_exit();
		} 
	else {
     	return drupal_get_form('worker_details_preview');
   	}
}
function worker_details_preview($form, &$form_state) {	
	global $base_root,$base_path,$user;
	
	$link 			 = $_GET['q'];
	
	$link_arr 		 	= explode('/', $link);	
	$serviceid 			= encryption_decryption_fun('decrypt',$link_arr[2]);
	$factory_typeid 	= encryption_decryption_fun('decrypt',$link_arr[3]);
	$applicationid 		= encryption_decryption_fun('decrypt',$link_arr[4]);
	$reference_no 		= encryption_decryption_fun('decrypt',$link_arr[5]);
	
	$form = array();
	$form['yearly_worker']['worker_year'] 	= array(		 
			  '#type' 				=> 'markup',
			  '#markup'				=> view_worker_list($serviceid,$factory_typeid,$applicationid,$reference_no),
	);
	return $form;	

}
function view_worker_list($serviceid,$factory_typeid,$applicationid,$reference_no){
	$applicant_id 			= $user->uid;
	$worker_details 		= array();
	$type					= '';
	$details				= '';
	$relationship			= '';
	$address_of_director	= '';					
	/* WORKER DETAILS */
	$worker_details = get_worker_renewal_service($serviceid,$factory_typeid,$applicationid,$reference_no);
	//

//$worker_details = get_worker_details_service($serviceid,$factory_typeid,$applicationid,$reference_no);
//print_r($worker_details);die();
	
	$output = '<table class="renewal-table" >
							<tr>
							<th   colspan="6">Permanent</th>
							<th   colspan="6">Contactual</th>
							
							</tr>
							<tr>
								<th rowspan="2">Men</th>
								<th rowspan="2">Women</th>  
								<th colspan="2">Adolescents</th>
								<th colspan="2">Children </th>
        
   						
								<th rowspan="2">Men</th>
								<th rowspan="2">Women</th>  
								<th colspan="2">Adolescents</th>
								<th colspan="2">Children</th>
        
   						 </tr>
						 <tr>
						 <th >Men</th>
						<th >Women</th>  
						<th >Men</th>
						<th >Women</th>  
						 <th >Men</th>
						<th >Women</th>  
						<th >Men</th>
						<th >Women</th>  
							
						 </tr>
						 '
						 ;
		$worker_details = get_worker_details_service($serviceid,$factory_typeid,$applicationid,$reference_no);
	
	foreach($worker_details as $worker){
		$permanent_worker_men 			= $worker->permanent_worker_men;
		$permanent_worker_women 		= $worker->permanent_worker_women;
		$permanent_adolescents_male 	= $worker->permanent_adolescents_male;
		$permanent_adolescents_female 	= $worker->permanent_adolescents_female;
		$permanent_children_male 		= $worker->permanent_children_male;
		$permanent_children_female 		= $worker->permanent_children_female;
		$contactual_worker_men 			= $worker->contactual_worker_men;
		$contactual_worker_women 		= $worker->contactual_worker_women;
		$contactual_adolescents_male 	= $worker->contactual_adolescents_male;
		$contactual_adolescents_female 	= $worker->contactual_adolescents_female;
		$contactual_children_male 		= $worker->contactual_children_male;
		$contactual_children_female 	= $worker->contactual_children_female;
		$worker_total 					= $worker->worker_total;
		$worker_id 						= $worker->id;
		
	}
	
	$output .='<tr>
	<td>'.$permanent_worker_men.'</td>
	<td>'.$permanent_worker_women.'</td>
	<td>'.$permanent_adolescents_male.'</td>
	<td>'.$permanent_adolescents_female.'</td>
	<td>'.$permanent_children_male.'</td>
	<td>'.$permanent_children_female.'</td>
	<td>'.$contactual_worker_men.'</td>
	<td>'.$contactual_worker_women.'</td>
	<td>'.$contactual_adolescents_male.'</td>
	<td>'.$contactual_adolescents_female.'</td>
	<td>'.$contactual_children_male.'</td>
	<td>'.$contactual_children_female.'</td>
	
	</tr>
	<tfoot>
    <tr>
      <td colspan="12"><font color="#00498b">Total Worker(s)  :-</font>&nbsp;&nbsp;<strong>'.$worker_total.'</strong></td>
     
    </tr>
  </tfoot>
	</table>';
		return $output;
}
function get_worker_renewal_service($serviceid,$factory_typeid,$applicationid,$reference_no){
	$query_worker_details 	=  db_select('fa_worker_details', 'worker_data');
	$query_worker_details	-> fields('worker_data',array());
	$query_worker_details	-> condition('worker_data.application_id', $applicationid);
	$query_worker_details	-> condition('worker_data.service_id', $serviceid);
	$query_worker_details	-> condition('worker_data.factory_type', $factory_typeid);
	$query_worker_details	-> condition('worker_data.application_reference_no', $reference_no);
	//$query_worker_details	-> orderBy('worker_data.id', 'desc');
	$result_worker_details 	=  $query_worker_details->execute()->fetchAll();
	//print_r($query_worker_details->execute());die();
	return $result_worker_details;
}


///////////////////////////////////////POWER RENEWAL DATA LIST////////////////////////////////////////


function applicant_power_data_preview($ajax,$serviceid,$factory_typeid,$applicationid,$reference_no){
	if ($ajax) {
		ctools_include('ajax');
    	ctools_include('modal');
		ctools_modal_add_js();
     	$form_state 	= array(
			'ajax' 		=> TRUE,
			'title' 	=> t(''),
		);
		$output = ctools_modal_form_wrapper('view_power_list',$form_state);
	  
    	if (!empty($form_state['ajax_commands'])) {
			$output = $form_state['ajax_commands'];
    	}
		print ajax_render($output);
    	drupal_exit();  
   }else {
     	return drupal_get_form('view_power_list');
   }
} 

function view_power_list($form, &$form_state) {	

	$link 			 	= $_GET['q'];
	
	$link_arr 		 	= explode('/', $link);	
	$serviceid 			= $link_arr[2];
	$factory_typeid 	= $link_arr[3];
	$applicationid 		= $link_arr[4];
	$reference_no 		= $link_arr[5];
	
	global $base_root,$base_path,$user;

  	$form = array();
  	$form['yearly_power']['power_year'] 	= array(
		  '#type' 				=> 'markup',
		  '#markup'				=> view_power_details($serviceid,$factory_typeid,$applicationid,$reference_no),
		);
	return $form;	

}

function view_power_details($serviceid,$factory_typeid,$applicationid,$reference_no){
	
	 $power_generating_station 	= get_power_renewal_data($applicationid,$reference_no,$factory_typeid,$serviceid);
	 $Wcounter = 1;
	 $header = array(
							array('data' => 'Sl. No'),
							array('data'=> 'Application Period'),
							array('data'=> 'Date of change'),
							array('data'=> 'Unit'),
							array('data'=> 'Power'),
						);
	foreach($power_generating_station as $power){
		$rows[] 	= array( 
								array('data' =>$Wcounter,'class' => array('')),
								array('data' =>$power->service_year ,'class' => array('')),
								array('data' =>date('dS M Y', strtotime($power->change_date)) ,'class' => array('')),
								array('data' =>$power->type_power_station ,'class' => array('')),
								array('data' =>$power->installed_power.'('.$power->power_unit.')','class' => array('')),
							);
		$Wcounter = $Wcounter+1;
	}
	$output = theme_table(
			array(
				  'header' => $header,
				  'rows' => $rows,
				  'attributes' => array('class' => array('table', 'pretty', 'table-bordered table-hover')),
				  'sticky' => true,
				  'caption' => '',
				  'colgroups' => array(),
				  'empty' => t("No data found!") // The message to be displayed if table is empty
				)
			).theme('pager');	
		 	return $output;	
	}
	

function get_power_renewal_data($applicationid,$reference_no,$factory_typeid,$serviceid){
		$query_power_details 	=  db_select('fa_power_details', 'power_renewal_details');
		$query_power_details	-> fields('power_renewal_details',array());
		$query_power_details	-> condition('power_renewal_details.application_id', $applicationid);
		$query_power_details	-> condition('power_renewal_details.factory_type', $factory_typeid);
		$query_power_details	-> condition('power_renewal_details.application_reference_no', $reference_no);
		$query_power_details	-> condition('power_renewal_details.service_id', $serviceid);
		$result_power_details 	=  $query_power_details->execute()->fetchAll();
		return $result_power_details;
	}

////////////////////////////////////MANAGER RENEWAL DATA LIST//////////////////////////////////////
function applicant_manager_data_preview($ajax,$serviceid,$factory_typeid,$applicationid,$reference_no){

	if ($ajax) {
		ctools_include('ajax');
    	ctools_include('modal');
		ctools_modal_add_js();
     	$form_state 	= array('ajax'	=> TRUE,'title' => t(''),);
		
      	$output = ctools_modal_form_wrapper('view_manager_list',$form_state);
	 
    	if (!empty($form_state['ajax_commands'])) {
			$output = $form_state['ajax_commands'];
    	}
		print ajax_render($output);
    	drupal_exit();  
   }else {
     	return drupal_get_form('view_manager_list');
   }
} 

function view_manager_list($form, &$form_state){	
	$link 			 = $_GET['q'];
	
	$link_arr 		 	= explode('/', $link);	
	$serviceid 			= encryption_decryption_fun('decrypt',$link_arr[3]);
	$factory_typeid 	= encryption_decryption_fun('decrypt',$link_arr[4]);
	$applicationid 		= encryption_decryption_fun('decrypt',$link_arr[5]);
	$reference_no 		= encryption_decryption_fun('decrypt',$link_arr[6]);
	
	global $base_root,$base_path,$user;

  	$form = array();
  	$form['yearly_manager']['manager_year'] 	= array(
		  '#type' 				=> 'markup',
		  '#markup'				=> view_manager_details($serviceid,$factory_typeid,$applicationid,$reference_no),
		);
	  return $form;	

}

function view_manager_details($serviceid,$factory_typeid,$applicationid,$reference_no){
	$get_all_data 			= array();
	$type					= '';
	$details				= '';
	$relationship			= '';
	$address_of_manager		= '';
	
	$get_all_data = get_manager_renewal_data($applicationid,$serviceid,$factory_typeid,$reference_no);
	
	$Wcounter		= 0;
	$per_page		= 10;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page);
	
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header 		= array(array('data'=> 'Sl. No'),
							array('data'=> 'Application Period'),
							array('data'=> 'Details'),
							array('data'=> 'Permanent Address'),
							array('data'=> 'Present Address & Contact'),	
							//array('data'=> 'Action'),
						);
	if(!empty($get_all_data)){
		
		foreach($chunks[$current_page] as $manager_details){ 
			$Wcounter++;
			
			if($manager_details->relationship_manager == '1'){
				$relationship = 'D/O';
			}if($manager_details->relationship_manager == '2'){
				$relationship = 'S/O';
			}if($manager_details->relationship_manager == '3'){
				$relationship = 'W/O';
			}
			
		
		$fieldArr_manager			 =  array('district_manager','sub_division_manager','area_type_manager','block_mun_cor_sez_not_manager','grm_ward_sector_not_manager','police_station_manager','pincode_manager','state_manager','post_office_manager');
   $address_of_manager	 =	$manager_details->adress_line1_manager.'<br>'.get_full_address('fa_manager_details','sub-table',$manager_details->id,$fieldArr_manager);
   $manager_details_view = $manager_details->name_manager.'<br/>'.$relationship.':-'.$manager_details->father_husband_name_manager.'<br/>Age:-'.$manager_details->age_manager;
			$rows[] 	= array( 
								array('data' =>$Wcounter,'class' => array('')),
								array('data' =>$manager_details->add_year_manager ,'class' => array('')),
								array('data' =>$manager_details_view ,'class' => array('')),
								array('data' =>$address_of_manager ,'class' => array('')),	
								array('data' =>$manager_details->manager_present_address.'<br>'.'Telephone: '.$manager_details->manager_telephone.'<br>'.'Mobile: '.$manager_details->manager_phone.'<br>'.'FAX: '.$manager_details->manager_fax.'<br>'.'Email: '.$manager_details->manager_email ,'class' => array('')),
								);
				} 
		
		}
		$output = theme_table(
			array(
				  'header' => $header,
				  'rows' => $rows,
				  'attributes' => array('id'=>'view_manager_details_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
				  'sticky' => true,
				  'caption' => '',
				  'colgroups' => array(),
				  'empty' => t("No data found!") // The message to be displayed if table is empty
				)
			).theme('pager');	
		 	return $output;	
	}
	
function get_manager_renewal_data($applicationid,$serviceid,$factory_typeid,$reference_no){
	
	$query_manager_details 	=  db_select('fa_manager_details', 'manager_details');
	$query_manager_details	-> fields('manager_details',array());
	$query_manager_details	-> condition('manager_details.application_manager_id', $applicationid);
	$query_manager_details	-> condition('manager_details.manager_service_id', $serviceid);
	$query_manager_details	-> condition('manager_details.factory_type_id', $factory_typeid);
	$query_manager_details	-> condition('manager_details.application_reference_no', $reference_no);
	//$query_manager_details	-> orderBy('manager_details.id', 'desc');
	$result_manager_details =  $query_manager_details->execute()->fetchAll();
	return $result_manager_details;
}

/////////////////////OCCUPIER RENEWAL DATA/////////////////////////////////////////////
function applicant_occupier_data_preview($ajax,$serviceid,$factory_typeid,$applicationid,$reference_no){
	if ($ajax) {
		ctools_include('ajax');
    	ctools_include('modal');
		ctools_modal_add_js();
     	$form_state 	= array('ajax'	=> TRUE,'title' => t(''),);
		
    	$output = ctools_modal_form_wrapper('view_occupier_list',$form_state);
    	if (!empty($form_state['ajax_commands'])) {
      		$output = $form_state['ajax_commands'];
   		}
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('view_occupier_list');
   }
}


function view_occupier_list($form, &$form_state) {
	$link 			= $_GET['q'];
	$link_arr 		= explode('/', $link);	
	$serviceid 		= $link_arr[2];
	$factory_typeid = $link_arr[3];
	$applicationid 	= $link_arr[4];
	$reference_no 	= $link_arr[5];
	global $base_root,$base_path,$user;

  $form = array();
  $form['yearly_occupier']['occupier_year'] = array(
		  '#type'	=> 'markup',
		  '#markup'	=> view_occupier_details($applicationid,$serviceid,$factory_typeid,$reference_no),
		);
	  return $form;
}
function view_occupier_details($applicationid,$serviceid,$factory_typeid,$reference_no){
	
	$get_all_data = array();
	$type					='';
	$details				='';
	$relationship			='';
	$address_of_director	='';
	$get_all_data = get_occupier_renewal_data($applicationid,$serviceid,$factory_typeid,$reference_no);
	
	
	$Wcounter		= 0;
	$per_page		= 10;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header 		= array(
									array('data' => 'Sl. No'),
									array('data'=> 'Application Period'),
									array('data'=> 'Details'),
									array('data'=> 'Present Address'),
									array('data'=> 'Premanent Address'),
								
									//array('data'=> 'Action'),
								);
	if(!empty($get_all_data)){
		foreach($chunks[$current_page] as $details){ 
			$Wcounter++;
			if($details->application_status == 'F'){
				$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
			else if($details->worker_plan_approval_status == 'F'){
				$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
			else{
					$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/del-occupier-registration/'.encryption_decryption_fun('encrypt', $details->id).'/'.encryption_decryption_fun('encrypt', $details->reference_number).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
				}
				
		$fieldpermanent_occupier =  array('district_oprmntadr','subdivision_oprmntadr','areatype_oprmntadr','block_oprmntadr','panchayat_oprmntadr','policestation_oprmntadr','pincodeoprmntadr','state_oprmntadr','postoffice_oprmntadr');
		$fieldpresent_occupier =  array('district_oprsntadr','subdivision_oprsntadr','areatype_oprsntadr','block_oprsntadr','panchayat_oprsntadr','policestation_oprsntadr','pincodeoprsntadr','state_oprsntadr','postoffice_oprsntadr');
		
	$details_occupier = $details->name_occupier.'('.$details->type_occupier.')'.'<br/>Father/Husband:-'.$details->father_husband_name_occupier.'<br/>Age:-'.$details->age_occupier.'<br/>Nationality:-'.country_name($details->country_oprmntadr).'<br/>Passport/Aadhaar Number:-'.$details->aadhaar_oprmntadr.$details->passport_oprmntadr;
			$rows[] = array( array('data' =>$Wcounter,'class' => array('')),
							 array('data' =>$details->add_year_occupier ,'class' => array('')),
							 array('data' =>$details_occupier,'class' => array('')),
							 array('data' =>$details->addrline_oprsntadr.'<br>'.get_full_address('fa_occupier_details','sub-table',$details->id,$fieldpresent_occupier) ,'class' => array('')),
							 array('data' =>$details->addrline_oprmntadr.'<br>'.get_full_address('fa_occupier_details','sub-table',$details->id,$fieldpermanent_occupier) ,'class' => array('')),
							//array('data' =>get_service_name($details->service_id) ,'class' => array('')),
							);
		} 
		
	}
	$output = theme_table(
	array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'view_occupier_details_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
		 return $output;	
}

function get_occupier_renewal_data($applicationid,$serviceid,$factory_typeid,$reference_no){
	
	$query_data 	=  db_select('fa_occupier_details', 'od');
	$query_data	    -> fields('od',array());
	$query_data	    -> condition('od.application_occupier_id', $applicationid);
	$query_data	    -> condition('od.occupier_service_id', $serviceid);
	$query_data	    -> condition('od.factory_type_id', $factory_typeid);
	$query_data		-> condition('od.application_reference_no', $reference_no);
	//$query_data		-> orderBy('od.id', 'desc');
	$occupier_data  =  $query_data->execute()->fetchAll();
	//print_r($occupier_data);die;
	return $occupier_data;
}

function applicant_director_data_preview($ajax,$serviceid,$factory_typeid,$applicationid,$reference_no){
	if ($ajax) {
		ctools_include('ajax');
    	ctools_include('modal');
		ctools_modal_add_js();
     	$form_state 	= array('ajax' => TRUE,'title' 	=> t(''),);
      	$output = ctools_modal_form_wrapper('view_director_list',$form_state);
	  
    	if (!empty($form_state['ajax_commands'])) {
      		$output = $form_state['ajax_commands'];
    	}
    
		print ajax_render($output);
    	drupal_exit();
     
   } else {
     return drupal_get_form('view_director_list');
   }
}
function view_director_list($form, &$form_state) {	
	$link 			 = $_GET['q'];
	$link_arr 		 	= explode('/', $link);	
	$serviceid 			= $link_arr[2];
	$factory_typeid 	= $link_arr[3];
	$applicationid 		= $link_arr[4];
	$reference_no 		= $link_arr[5];

	global $base_root,$base_path,$user;

  $form = array();
  $form['yearly_director']['director_year'] 	= array(
		 
		  '#type' 	=> 'markup',
		  '#markup'	=> view_director_details($applicationid,$serviceid,$factory_typeid,$reference_no),
		);
	 
	  return $form;	

}

function view_director_details($applicationid,$serviceid,$factory_typeid,$reference_no){
	$get_all_data = array();
	$type					= '';
	$details				='';
	$relationship			= '';
	$address_of_director	='';
	
	$get_all_data = get_director_renewal_data($applicationid,$serviceid,$factory_typeid,$reference_no);
	//print_r($get_all_data);die();
	
	$Wcounter		= 0;
	$per_page		= 10;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header 		= array(
									array('data' => 'Sl. No'),
									array('data'=> 'Application period'),
									array('data'=> 'Name'),
									array('data'=> 'Father/Husband'),
									array('data'=> 'Age'),
									array('data'=> 'Residential Address'),
									
									//array('data'=> 'Action'),
								);
	if(!empty($get_all_data)){
		foreach($chunks[$current_page] as $details){ 
			$Wcounter++;
			if(!empty($details->din_director)){
				$din = 'DIN:-'.$details->din_director;
				}	
			$type =$details->type_director;
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
								array('data' =>$details->add_year_director ,'class' => array('')),
								array('data' =>$details->name_director.'('.$type.')<br>'.$din ,'class' => array('')),
								array('data' =>$relationship.'-'.$details->father_husband_name_director ,'class' => array('')),
								array('data' =>$details->age_director ,'class' => array('')),
								array('data' =>$address_of_director ,'class' => array('')),
								
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
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
		 return $output;
}

function get_director_renewal_data($applicationid,$serviceid,$factory_typeid,$reference_no){
	$query_director_details 	=  db_select('fa_director_details', 'director_details');
	$query_director_details	-> fields('director_details',array());
	$query_director_details	-> condition('director_details.application_director_id', $applicationid);
	$query_director_details	-> condition('director_details.director_service_id', $serviceid);
	$query_director_details	-> condition('director_details.factory_type_id', $factory_typeid);
	$query_director_details	-> condition('director_details.application_reference_no', $reference_no);
	$result_director_details 	=  $query_director_details->execute()->fetchAll();
	return $result_director_details;
}

function applicant_manufacturing_data_preview($ajax,$serviceid,$factory_typeid,$applicationid,$reference_no){
	if ($ajax) {
        ctools_include('ajax');
    	ctools_include('modal');
		ctools_modal_add_js();
				$form_state = array('ajax'	=> TRUE,'title'=> t(''));
		$output = ctools_modal_form_wrapper('view_manufacturing_list',$form_state);
	  
   	 if (!empty($form_state['ajax_commands'])) {
      	$output = $form_state['ajax_commands'];
    	}
		print ajax_render($output);
    	drupal_exit();
	}else{
     return drupal_get_form('view_manufacturing_list');
   }
}


function view_manufacturing_list($form, &$form_state) {	
	$link 			= $_GET['q'];
	$link_arr 		= explode('/', $link);	
	$serviceid 		= $link_arr[2];
	$factory_typeid = $link_arr[3];
	$applicationid 	= $link_arr[4];
	$reference_no 	= $link_arr[5];
	
	global $base_root,$base_path,$user;

  	$form = array();
  	$form['yearly_worker']['worker_year'] 	= array(
		  '#type' 				=> 'markup',
		  '#markup'				=> get_manufacturing_details($applicationid,$serviceid,$factory_typeid,$reference_no),
		);
	return $form;	

}

function get_manufacturing_details($applicationid,$serviceid,$factory_typeid,$reference_no){
	global $base_root,$base_path,$user;
	$applicant_id = $user->uid;
	$nature_details = array();
	
	$nature_details = get_manufacturing_renewal_data($applicationid,$serviceid,$factory_typeid,$reference_no);
	$header = array(
		array('data'=> 'SL No'),
		array('data'=> 'Application period'),
		array('data'=> 'Manufacturing process'),
		//array('data'=> 'Act')
	);
				
						
	if(!empty($nature_details)){
		$i=1;
			foreach($nature_details as $nature){
					$rows[] = array( 
								array('data' =>$i,'class' => array('')),
								array('data' =>$nature->service_year ,'class' => array('')),
								array('data' =>$nature->nature_manufacturing,'class' => array('')),
								//array('data' =>get_service_name($nature->service_id) ,'class' => array('')),
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

function get_manufacturing_renewal_data($applicationid,$serviceid,$factory_typeid,$reference_no){
	$query_manufacturing 	=  db_select('fa_nature_manufacturing', 'manufacturing');
	$query_manufacturing	-> fields('manufacturing',array());
	$query_manufacturing	-> condition('manufacturing.application_id', $applicationid);
	$query_manufacturing	-> condition('manufacturing.service_id', $serviceid);
	$query_manufacturing	-> condition('manufacturing.factory_type', $factory_typeid);
	$query_manufacturing	-> condition('manufacturing.application_reference_no', $reference_no);
	$query_manufacturing_details 	=  $query_manufacturing->execute()->fetchAll();
	return $query_manufacturing_details;
}

////////////////////////////////////DOCUMENT RENEWAL DETAILS//////////////////////////

function applicant_document_data_preview($ajax,$serviceid,$factory_typeid,$applicationid,$reference_no){
	if ($ajax) {
		ctools_include('ajax');
    	ctools_include('modal');
		ctools_modal_add_js();
     	$form_state = array('ajax'	=> TRUE,'title' => t(''));
      	$output = ctools_modal_form_wrapper('view_document_list',$form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('view_document_list');
   }
}	

function view_document_list($form, &$form_state){
	$link 			 = $_GET['q'];
	$link_arr 		 	= explode('/', $link);	
	$serviceid 			= $link_arr[2];
	$factory_typeid 	= $link_arr[3];
	$applicationid 		= $link_arr[4];
	$reference_no 		= $link_arr[5];
	
	global $base_root,$base_path,$user;

  $form = array();
  $form['yearly_document']['document_year'] 	= array(
		  '#type' 	=> 'markup',
		  '#markup'	=> view_documents_details($serviceid,$factory_typeid,$applicationid,$reference_no),
		);
	  return $form;
}

function view_documents_details($serviceid,$factory_typeid,$applicationid,$reference_no){
	$documents_master_details	= documents_master_details($serviceid,$factory_typeid);
	
	$header = array(
		array('data'=> 'SL No'),
		array('data'=> 'Related Documents'),
		array('data'=> 'Uploaded Documents'),
	);
	$i=1;
	foreach($documents_master_details as $documents){
		
		$view_fid			= view_attached_filename($applicationid,$reference_no,$factory_typeid,$documents->id,$serviceid);
		$upoladed_doc 		= get_uploaded_document_url($view_fid['fid']);
		
		if(!empty($upoladed_doc)){ 
				$url 		= explode('//',$upoladed_doc);
				$doc_url	= $url[1];
				$view		='<a title = "Click here to view '.$documents->document_name.'" href="'.$GLOBALS['base_url'].'/sites/default/files/'.$doc_url.'" target="_blank"><i class="ace-icon fa fa-file-pdf-o bigger-130"></i></a>';
				
			
		}else{
			$view = "Not Found";
		}
		
		$rows[] = array( 
						array('data' =>$i,'class' => array('')),
						array('data' =>$documents->document_name ,'class' => array('')),
						array('data' =>$view,'class' => array('')),
						//array('data' =>get_service_name($nature->service_id) ,'class' => array('')),
				);
					
			$i++;
		
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
function applicant_payment_data_preview($ajax,$serviceid,$factory_typeid,$applicationid,$reference_no){
	if ($ajax) {
        		ctools_include('ajax');
    			ctools_include('modal');
				ctools_modal_add_js();
     			$form_state 	= array(
       									'ajax' 		=> TRUE,
       									'title' 	=> t(''),
    								 );
	 
	  
      $output = ctools_modal_form_wrapper('pre_payment_detials',$form_state);
	  
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }

    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('pre_payment_detials');
   }
} 
function pre_payment_detials($form, &$form_state) {	
	$link 			 = $_GET['q'];
	
	$link_arr 		 	= explode('/', $link);	
	$serviceid 			= $link_arr[2];
	$factory_typeid 	= $link_arr[3];
	$applicationid 		= $link_arr[4];
	$reference_no 		= $link_arr[5];
	
	global $base_root,$base_path,$user;
	
	  $form = array();
	  $form['yearly_payment']['payment_year'] 	= array(
			 
			  '#type' 				=> 'markup',
			  '#markup'				=> view_prepayment_history($serviceid,$factory_typeid,$applicationid,$reference_no),
			);
		 
		  return $form;	
}

function view_prepayment_history($serviceid,$factory_typeid,$applicationid,$reference_no){
	$output = '';
	$sl = 0;
	$header = array(
		array('data'=> 'SL No'),
		array('data'=> 'BRN/GRN/Challan Number'),
		array('data'=> 'Payment date'),
		array('data'=> 'Amount'),
		array('data'=> 'Challan')
	);
	$manual_payment_deatils	=	manual_payment_deatils($applicationid,$serviceid,$factory_typeid,$reference_no);
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
			array('data' => t($history->date_payment)),
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
?>