<?php
 drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function worker_detials_data($ajax,$serviceid,$factory_typeid,$applicationid,$reference_no){
	if ($ajax) {
        		ctools_include('ajax');
    			ctools_include('modal');
				ctools_modal_add_js();
     			$form_state 	= array(
       									'ajax' 		=> TRUE,
       									'title' 	=> t('Worker Details'),
    								 );
	 
	  
      $output = ctools_modal_form_wrapper('worker_detials_preview',$form_state);
	  
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('worker_detials_preview');
   }
   }
function occuiper_detials_data($ajax,$serviceid,$factory_typeid,$applicationid,$reference_no){
	if ($ajax) {
        		ctools_include('ajax');
    			ctools_include('modal');
				ctools_modal_add_js();
     			$form_state 	= array(
       									'ajax' 		=> TRUE,
       									'title' 	=> t(''),
    								 );
	 
	  
      $output = ctools_modal_form_wrapper('occupier_detials_preview',$form_state);
	  
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('occupier_detials_preview');
   }
   }
function director_detials_data($ajax,$serviceid,$factory_typeid,$applicationid,$reference_no){
	if ($ajax) {
        		ctools_include('ajax');
    			ctools_include('modal');
				ctools_modal_add_js();
     			$form_state 	= array(
       									'ajax' 		=> TRUE,
       									'title' 	=> t(''),
    								 );
	 
	  
      $output = ctools_modal_form_wrapper('director_detials',$form_state);
	  
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('director_detials');
   }
   }
function manufacturing_detials_data($ajax,$serviceid,$factory_typeid,$applicationid,$reference_no){
	if ($ajax) {
        		ctools_include('ajax');
    			ctools_include('modal');
				ctools_modal_add_js();
     			$form_state 	= array(
       									'ajax' 		=> TRUE,
       									'title' 	=> t(''),
    								 );
	 
	  
      $output = ctools_modal_form_wrapper('manufacturing_detials',$form_state);
	  
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('manufacturing_detials');
   }
   }
function documents_detials_data($ajax,$serviceid,$factory_typeid,$applicationid,$reference_no){
	if ($ajax) {
        		ctools_include('ajax');
    			ctools_include('modal');
				ctools_modal_add_js();
     			$form_state 	= array(
       									'ajax' 		=> TRUE,
       									'title' 	=> t(''),
    								 );
	 
	  
      $output = ctools_modal_form_wrapper('documents_detials',$form_state);
	  
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('documents_detials');
   }
   } 
   
function documents_detials_caf_data($ajax,$serviceid,$factory_typeid,$applicationid,$reference_no){
	if ($ajax) {
        		ctools_include('ajax');
    			ctools_include('modal');
				ctools_modal_add_js();
     			$form_state 	= array(
       									'ajax' 		=> TRUE,
       									'title' 	=> t(''),
    								 );
	 
	  
      $output = ctools_modal_form_wrapper('documents_detials_uploaded_caf',$form_state);
	  
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('documents_detials_uploaded_caf');
   }
   }    
   
function managaer_details_data($ajax,$serviceid,$factory_typeid,$applicationid,$reference_no){
	if ($ajax) {
        		ctools_include('ajax');
    			ctools_include('modal');
				ctools_modal_add_js();
     			$form_state 	= array(
       									'ajax' 		=> TRUE,
       									'title' 	=> t(''),
    								 );
	 
	  
      $output = ctools_modal_form_wrapper('manager_detials',$form_state);
	  
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('manager_detials');
   }
   }    
function power_details_data($ajax,$serviceid,$factory_typeid,$applicationid,$reference_no){
	if ($ajax) {
        		ctools_include('ajax');
    			ctools_include('modal');
				ctools_modal_add_js();
     			$form_state 	= array(
       									'ajax' 		=> TRUE,
       									'title' 	=> t(''),
    								 );
	 
	  
      $output = ctools_modal_form_wrapper('power_detials',$form_state);
	  
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('power_detials');
   }
   } 
   
function payment_detials_previous_data($ajax,$serviceid,$factory_typeid,$applicationid,$reference_no){
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


function transfer_details_data($ajax,$serviceid,$factory_typeid,$applicationid,$reference_no){

	if ($ajax) {
        		ctools_include('ajax');
    			ctools_include('modal');
				ctools_modal_add_js();
     			$form_state 	= array(
       									'ajax' 		=> TRUE,
       									'title' 	=> t('Transfer Details'),
    								 );
	 
	  
      $output = ctools_modal_form_wrapper('transfer_details_preview',$form_state);
	  
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('transfer_details_preview');
   }
}
function transfer_details_preview($form, &$form_state) {	
	$link 			 = $_GET['q'];
	
	$link_arr 		 	= explode('/', $link);	
	$serviceid 			= $link_arr[2];
	$factory_typeid 	= $link_arr[3];
	$applicationid 		= $link_arr[4];
	$reference_no 		= $link_arr[5];
	
	global $base_root,$base_path,$user;
	
	  $form = array();
	  $form['yearly_worker']['worker_year'] 	= array(
			 
			  '#type' 				=> 'markup',
			  '#markup'				=> view_transer_details($applicationid,$reference_no,$factory_typeid,$serviceid),
			);
		 
		  return $form;	
	
	}

	function view_transer_details($application_id,$reference_number,$factory_type_id,$service_id){
	
		$output = '';
		$sl = 0;
	
		$pre_view	=	get_previous_details_view($application_id,$reference_number,$factory_type_id,$service_id);
		//print_r($pre_view);die($pre_view[0]->id);
	//	$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/transfer-delete-year-renew/'.encryption_decryption_fun('encrypt', $pre_view[0]->id).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt', $reference_number).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$service_id),array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
		
		if(!empty($pre_view)){
		//print_r($pre_view);die();
			$header = array(
			array('data'=> 'Sl. No.','width'=> '8%'),
			array('data'=> 'Application Period','width'=> '20%'),
			array('data'=> 'Change Date','width'=> '20%'),
			array('data'=> 'Previous Name','width'=> '34%'),
			array('data'=> 'Conversion Name','width'=> '34%'),
			array('data'=> 'Transfer Fees','width'=> '20%'),
			//array('data'=> 'Action','width'=> '10%'),
			
		);
		foreach($pre_view as $view){
			$sl= $sl+1;	
			if($view->conversation_ownership_type=="pv"){
				$conversation_ownership_type = "Pvt Ltd Company";
			}if($view->conversation_ownership_type=="ltd"){
				$conversation_ownership_type = "Ltd Company";
			}if($view->conversation_ownership_type=="par_firm"){
				$conversation_ownership_type = "Partnership Firm";
			}if($view->conversation_ownership_type=="pro_firm"){
				$conversation_ownership_type = "Proprietorship Firm";
				
			}if($view->previous_ownership=="pv"){
				$previous_ownership_type = "Pvt Ltd Company";
			}if($view->previous_ownership=="ltd"){
				$previous_ownership_type = "Ltd Company";
			}if($view->previous_ownership=="par_firm"){
				$previous_ownership_type = "Partnership Firm";
			}if($view->previous_ownership=="pro_firm"){
				$previous_ownership_type = "Proprietorship Firm";
			}
			$change_date =  date('dS M Y', strtotime($view->change_date));
			
			$rows [] = array(  
				array('data' => $sl), 	
				array('data' => t($view->service_year)),
				array('data' =>	$change_date),
				array('data' => t($view->pervious_factory_name)),
				array('data' => t($view->conversation_name)),
				array('data' => t($view->transfer_fees)),
				//array('data' => $delLink),	
			);
			
		}
		$output = theme_table(
		array(
			  'header' 		=> $header,
			  'rows' 		=> $rows,
			  'attributes' 	=> array('id'=>'table_div_replace', 'class' => array('table', 'no-margin', 'custom-table-view-dashboard')),
			  'sticky' 		=> true,
			  'caption' 	=> '',
			  'colgroups' 	=> array(),
			  'empty' 		=> t("No data found!") // The message to be displayed if table is empty
			)
		).theme('pager');	
		  
		return $output;	
		}
	}
	







function worker_detials_preview($form, &$form_state) {	
$link 			 = $_GET['q'];

$link_arr 		 	= explode('/', $link);	
$serviceid 			= $link_arr[2];
$factory_typeid 	= $link_arr[3];
$applicationid 		= $link_arr[4];
$reference_no 		= $link_arr[5];

global $base_root,$base_path,$user;

  $form = array();
  $form['yearly_worker']['worker_year'] 	= array(
		 
		  '#type' 				=> 'markup',
		  '#markup'				=> view_details($serviceid,$factory_typeid,$applicationid,$reference_no),
		);
	 
	  return $form;	

}
function view_details($serviceid,$factory_typeid,$applicationid,$reference_no){
	$applicant_id 			= $user->uid;
	$worker_details 		= array();
	$type					= '';
	$details				='';
	$relationship			='';
	$address_of_director	='';					
	/* WORKER DETAILS */
	$worker_details = get_worker_details_service($serviceid,$factory_typeid,$applicationid,$reference_no);
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
		$recomended_total_worker		= $worker->recomended_total_worker;
		
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
      <td colspan="12"><font color="#00498b">Total Worker(s)  :-</font>&nbsp;&nbsp;<strong>'.$worker_total.'</strong></td></tr>';
	  if(!empty($recomended_total_worker)|| $recomended_total_worker!=0 || $recomended_total_worker!=NULL){
		  $output .=' <tr><td colspan="12"><font color="red">Recommanded Total Worker(s)by AD  :-</font>&nbsp;&nbsp;<strong>'.$recomended_total_worker.'</strong></td></tr>';
	  }
	 
     
     $output .='
  </tfoot>
	</table>';
		return $output;
	/*$header = array(
		array('data'=> 'SL No'),
		array('data'=> 'Permanent',array('colspan' => 6)),
		array('data'=> 'Contactual',array('colspan' => 6)),
		array('data'=> 'Adolescents Male'),
		array('data'=> 'Adolescents Female'),
		array('data'=> 'Children Male'),
		array('data'=> 'Children Female'),
		array('data'=> 'Total Worker'),
		array('data'=> 'Recommanded Worker'),
		
		//array('data'=> 'Act')
	);
								
	if(!empty($worker_details)){
		$i=1;
			foreach($worker_details as $worker){ 
			$recomended_total_worker = !empty($worker->recomended_total_worker)?$worker->recomended_total_worker:0;
			
					$rows[] = array( 
								array('data' => t($i)), 
								array('data' =>$worker->permanent_worker_men ,'class' => array('')),
								array('data' =>$worker->permanent_worker_women ,'class' => array('')),
								array('data' =>$worker->permanent_adolescents_male ,'class' => array('')),
								array('data' =>$worker->permanent_adolescents_female ,'class' => array('')),
								array('data' =>$worker->permanent_children_male ,'class' => array('')),
								array('data' =>$worker->permanent_children_female ,'class' => array('')),	
								array('data' =>$worker->contactual_worker_men ,'class' => array('')),
								array('data' =>$worker->contactual_worker_women ,'class' => array('')),
								array('data' =>$worker->contactual_adolescents_male ,'class' => array('')),
								array('data' =>$worker->contactual_adolescents_female ,'class' => array('')),
								array('data' =>$worker->contactual_children_male ,'class' => array('')),
								array('data' =>$worker->contactual_children_female ,'class' => array('')),
								array('data' =>$worker->worker_total ,'class' => array('')),
								//array('data' =>$recomended_total_worker ,'class' => array('')),
								
								//array('data' =>get_service_name($worker->service_id) ,'class' => array('')),
								
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
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
		 return $output;*/	
	//$variables=
	/*$variables = array(
	  		'attributes' => array('class' => array('table', 'pretty', 'table-bordered table-hover')),
	  		'header' 		=> $header,
	  		'rows'			=> $rows,
	  		);
		
	$output = theme('datatable', $variables);	
	return $output;*/
}

function occupier_detials_preview($form, &$form_state) {	
$link 			 = $_GET['q'];


$link_arr 		 	= explode('/', $link);	
$serviceid 			= $link_arr[2];
$factory_typeid 	= $link_arr[3];
$applicationid 		= $link_arr[4];
$reference_no 		= $link_arr[5];

global $base_root,$base_path,$user;

  $form = array();
  $form['yearly_worker']['worker_year'] 	= array(
		 
		  '#type' 				=> 'markup',
		  '#markup'				=> view_occupier_details($applicationid,$serviceid,$factory_typeid,$reference_no),
		);
	 
	  return $form;	

}
function director_detials($form, &$form_state) {	
$link 			 = $_GET['q'];


$link_arr 		 	= explode('/', $link);	
$serviceid 			= $link_arr[2];
$factory_typeid 	= $link_arr[3];
$applicationid 		= $link_arr[4];
$reference_no 		= $link_arr[5];

global $base_root,$base_path,$user;

  $form = array();
  $form['yearly_worker']['worker_year'] 	= array(
		 
		  '#type' 				=> 'markup',
		  '#markup'				=> view_director_proipietor_details($applicationid,$serviceid,$factory_typeid,$reference_no),
		);
	 
	  return $form;	

}
function view_occupier_details($applicationid,$serviceid,$factory_typeid,$reference_no){
	$get_all_data = array();
	$type					= '';
	$details				='';
	$relationship			='';
	$address_of_director	='';
	
	$get_all_data = get_all_occupier_data($applicationid,$serviceid,$factory_typeid,$reference_no);
	
	
	$Wcounter		= 0;
	$per_page		= 5;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header 		= array(
									array('data' => 'Sl. No'),
									array('data'=> 'Details of Occupier'),
									array('data'=> 'Present Address'),
									array('data'=> 'Premanant Address'),
									//array('data'=> 'Service Name'),
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
			
			$rows[] 	= array( 
								array('data' =>$Wcounter,'class' => array('')),
								array('data' =>$details_occupier,'class' => array('')),
								array('data' =>$occupier_permanent_address ,'class' => array('')),
								array('data' =>$occupier_present_address ,'class' => array('')),
							
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

function view_director_proipietor_details($applicationid,$serviceid,$factory_typeid,$reference_no){
	$get_all_data = array();
	$type					= '';
	$details				='';
	$relationship			= '';
	$address_of_director	='';
	
	$get_all_data = get_director_details_service($applicationid,$serviceid,$factory_typeid,$reference_no);
	//print_r($get_all_data);die();
	
	$Wcounter		= 0;
	$per_page		= 5;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header			= array(
						array('data' => 'Sl. No'),
						array('data'=> 'Employee Type'),
						array('data'=> 'Employee Details'),
						array('data'=> 'Permanent Address'),
						array('data'=> 'Present Address & Contact'),
						//array('data'=> 'Action'),		
					);
	if(!empty($get_all_data)){
		foreach($chunks[$current_page] as $details){ 
			$Wcounter++;
			if(!empty($details->din_director)){
				$din = 'DIN:-'.$details->din_director;
				}	
			$type =$details->type_director;
			if($type=='ltd' || $type=='pv'){$director_type = 'Director';}
			if($type == 'par_firm'){$director_type 	= 'Partner';}
			if($type == 'pro_firm'){$director_type 	= 'Proprietor';}
			if($type == 'govt' || $type == 'psu' || $type == 'others'){$director_type 	= 'Nominated Occupier';}
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
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
		 return $output;
	
	
}
function manufacturing_detials($form, &$form_state) {	
$link 			 = $_GET['q'];


$link_arr 		 	= explode('/', $link);	
$serviceid 			= $link_arr[2];
$factory_typeid 	= $link_arr[3];
$applicationid 		= $link_arr[4];
$reference_no 		= $link_arr[5];

global $base_root,$base_path,$user;

  $form = array();
  $form['yearly_worker']['worker_year'] 	= array(
		 
		  '#type' 				=> 'markup',
		  '#markup'				=> get_nature_manufacturing_data($applicationid,$serviceid,$factory_typeid,$reference_no),
		);
	 
	  return $form;	

}
function get_nature_manufacturing_data($applicationid,$serviceid,$factory_typeid,$reference_no){
	global $base_root,$base_path,$user;
	$applicant_id = $user->uid;
	$nature_details = array();
	
	/* Nature Details */
	$nature_details = get_manufacturing($applicationid,$serviceid,$factory_typeid,$reference_no);
	//print_r($nature_details);die;
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
function documents_detials($form, &$form_state) {	
$link 			 = $_GET['q'];

$link_arr 		 	= explode('/', $link);	
$serviceid 			= $link_arr[2];
$factory_typeid 	= $link_arr[3];
$applicationid 		= $link_arr[4];
$reference_no 		= $link_arr[5];

global $base_root,$base_path,$user;

  $form = array();
  $form['yearly_worker']['worker_year'] 	= array(
		 
		  '#type' 				=> 'markup',
		  '#markup'				=> view_list_documents($serviceid,$factory_typeid,$applicationid,$reference_no),
		);
	 
	  return $form;	

}

function documents_detials_uploaded_caf($form, &$form_state) {	
$link 			 = $_GET['q'];

$link_arr 		 	= explode('/', $link);	

$applicationid 		= $link_arr[2];
$reference_no 		= $link_arr[3];
$tm_appln_id 		= $link_arr[4];

global $base_root,$base_path,$user;

  $form = array();
  $form['yearly_worker']['worker_year'] 	= array(
		 
		  '#type' 				=> 'markup',
		  '#markup'				=> view_uploaded_caf_list_documents($applicationid,$reference_no,$tm_appln_id ),
		);
	 
	  return $form;	

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
  $form['yearly_worker']['worker_year'] 	= array(
		 
		  '#type' 				=> 'markup',
		  '#markup'				=> view_prepayment_history($serviceid,$factory_typeid,$applicationid,$reference_no),
		);
	 
	  return $form;	

}

function view_list_documents($serviceid,$factory_typeid,$applicationid,$reference_no){
	global $base_url;
	$get_data 			=  get_fa_cafa($applicationid);
	$tm_migrated_flag 	= $get_data['tm_migrated_flag'];

	if($tm_migrated_flag != 'N' && $tm_migrated_flag != 'S'){

		$output = '';
		$output .= '<table border="1" width="100%">
				<tr><td colspan="4">&nbsp;</td></tr>
				<tr align="center" style="font-weight:bold;font-size:16px;">
					<td width="5%">SL No</td>
					<td width="50%">DOCUMENT NAME</td>
					<td width="30%">UPLOADED DOCUMENT</td>
				</tr>';
		//print_r($documents_master_list);
    	$sl = 1;
		$resultData 	= get_uploaded_document_data($serviceid,$factory_typeid,$applicationid,$reference_no);
		// print_r($resultData);die;
		$displayLink =	'<a href='.$base_url.'/feesmigrate/display-file/'.$val->caf_file_name.' target= "_BLANK" onclick = "popIt(this.href);return false;">Click to View</a>';
		 foreach($resultData as $val)
		{
				
		$output .= '<tr>
						<td width="5%" align="center" >'.$sl.'</td>
						<td width="50%" style="padding-left: 5px;">'.$val->doc_name.'</td>
						<td width="50%" style="padding-left: 5px;">'.$displayLink.'</td>
						<td width="45%">&nbsp;</td>
					</tr>';

		 $sl++;	
		}
		$output .= '<tr><td colspan="4">&nbsp;</td></tr>';
		
		$output .= '</table>';	

	}else{
		$output = '';
		$output .= '<table border="1" width="100%">
				<tr><td colspan="4">&nbsp;</td></tr>
				<tr align="center" style="font-weight:bold;font-size:16px;">
					<td width="5%">SL No</td>
					<td width="50%">DOCUMENT NAME</td>
					<td width="45%">UPLOADED DOCUMENT</td>
					
				</tr>';

		$documents_master_list	= documents_master_data($serviceid,$factory_typeid);
		
		$sl = 1;
		foreach($documents_master_list as $documents){
		$documents_type = NULL;
		  $resultData 	= get_caf_upload_doc_all($applicationid, $serviceid, $documents_type, $factory_typeid, $reference_no,$documents->doc_listid);
		 //print_r($resultData);die;
		  $rowspan = count($resultData)+1;
		 
			
			$output .= '<tr>
							<td width="5%" align="center" rowspan="'.$rowspan.'">'.$sl.'</td>
							<td width="50%" style="padding-left: 5px;" rowspan="'.$rowspan.'">'.file_name($documents->id).'</td>
							<td width="45%">&nbsp;</td>
							
						</tr>';

			foreach($resultData as $val)
			{
				
				$displayLink = l('<i class="ace-icon fa fa-file-pdf-o bigger-130"></i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $val->id).'/'.encryption_decryption_fun('encrypt', 'DOC').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
				
				$output .= '<tr>
								<td width="30%" style="padding-left: 10px;">'.$displayLink.'&nbsp;'.$val->file_name.'</td>
							</tr>';

			}
			$output .= '<tr><td colspan="4">&nbsp;</td></tr>';			
			
     	$sl++;
		}
				
		$output .= '</table>';
		
	}
	return $output;	
	
}

function view_uploaded_caf_list_documents($applicationid,$reference_no,$tm_appln_id ){

	$query 	=  db_select('fa_caf_upload_doc_tm_yearwise', 'fcudt');
	
	$query 	-> fields('fcudt', array());
	
	$query	-> condition('fcudt.tm_appln_id', $tm_appln_id );
	
	$result = $query->execute();
	
	$resultData = $result->fetchAll();
	
	$header = array(
		array('data'=> 'SL No'),
		array('data'=> 'Related Documents'),
		array('data'=> 'Uploaded Documents'),
		
		
	);
	$i=1; 
	global $base_url;
	foreach($resultData as $documents){
		
	
		
		$displayLink =	'<a href='.$base_url.'/feesmigrate/display-file/'.$documents->caf_file_name.' target= "_BLANK" onclick = "popIt(this.href);return false;">Click to View</a>';
		
		$rows[] = array( 
						array('data' =>$i,'class' => array('')),
						//array('data' =>file_name($documents->id_doc_master) ,'class' => array('')),
						array('data' =>$documents->tm_year_description ,'class' => array('')),
						array('data' =>$displayLink,'class' => array('')),
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

function manager_detials($form, &$form_state) {	
$link 			 = $_GET['q'];

$link_arr 		 	= explode('/', $link);	
$serviceid 			= $link_arr[2];
$factory_typeid 	= $link_arr[3];
$applicationid 		= $link_arr[4];
$reference_no 		= $link_arr[5];

global $base_root,$base_path,$user;

  $form = array();
  $form['yearly_worker']['worker_year'] 	= array(
		 
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
	
	//echo $factory_typeid;
	
	$get_all_data = get_all_manager_data($applicationid,$serviceid,$factory_typeid,$reference_no);
	//print_r($get_all_data);
	//die();
	
	$Wcounter		= 0;
	$per_page		= 5;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page);
	
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header			= array(
						array('data' => 'Sl. No'),
						array('data'=> 'Employee Type'),
						array('data'=> 'Employee Details'),
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
								array('data' =>'Manager' ,'class' => array('')),
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
				  'caption' => '',
				  'colgroups' => array(),
				  'empty' => t("No data found!") // The message to be displayed if table is empty
				)
			).theme('pager');	
		 	return $output;	
	}
	
function power_detials($form, &$form_state) {	
$link 			 = $_GET['q'];

$link_arr 		 	= explode('/', $link);	
$serviceid 			= $link_arr[2];
$factory_typeid 	= $link_arr[3];
$applicationid 		= $link_arr[4];
$reference_no 		= $link_arr[5];

global $base_root,$base_path,$user;

  $form = array();
  $form['yearly_worker']['worker_year'] 	= array(
		 
		  '#type' 				=> 'markup',
		  '#markup'				=> view_power_details($serviceid,$factory_typeid,$applicationid,$reference_no),
		);
	 
	  return $form;	

}

function view_power_details($serviceid,$factory_typeid,$applicationid,$reference_no){
	 $power_generating_station 	= get_power_generating_station($applicationid,$reference_no,$factory_typeid,$serviceid);
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


function owner_details_data($ajax,$serviceid,$factory_typeid,$applicationid,$reference_no){
	if ($ajax) {
        		ctools_include('ajax');
    			ctools_include('modal');
				ctools_modal_add_js();
     			$form_state 	= array(
       									'ajax' 		=> TRUE,
       									'title' 	=> t('Owner Details'),
    								 );
	 
	  
      $output = ctools_modal_form_wrapper('owner_data_preview',$form_state);
	  
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('owner_data_preview');
   }
}

function owner_data_preview($form, &$form_state) {	
	$link 			 = $_GET['q'];
	
	$link_arr 		 	= explode('/', $link);	
	$serviceid 			= $link_arr[2];
	$factory_typeid 	= $link_arr[3];
	$applicationid 		= $link_arr[4];
	$reference_no 		= $link_arr[5];
	
	global $base_root,$base_path,$user;
	
	  $form = array();
	  $form['yearly_owner']['owner_year'] 	= array(
			  '#type' 				=> 'markup',
			  '#markup'				=> view_owner_details_list($serviceid,$factory_typeid,$applicationid,$reference_no),
			);
		 
		  return $form;	
	
	}

function view_owner_details_list($serviceid,$factory_typeid,$applicationid,$reference_no){
	$get_all_data 			= array();
	$type					= '';
	$details				= '';

	$get_all_data 			= get_all_owner_data($applicationid,$serviceid,$factory_typeid,$reference_no);
	
	$Wcounter		= 0;
	$per_page		= 10;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	$chunks 		= array_chunk($get_all_data, $per_page);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header			= array(
						array('data' => 'Sl. No','width' => '6%'),
						array('data'=> 'Owner Name','width' => '20%'),
						array('data'=> 'Address','width' => '60%'),
						//array('data'=> 'Action','width' => '10%'),	
					);
	if(!empty($get_all_data)){
		
		foreach($chunks[$current_page] as $owner_details){ 
			$Wcounter++;
			
			$getdata_owner_address =  array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
	$owner_address    = $owner_details->addrline_premises. '<br/>'.get_full_address('fa_owner_details','sub-table',$owner_details->id,$getdata_owner_address).'<br/>'.country_name($owner_details->country_premises);


			$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/del-owner-details/'.encryption_decryption_fun('encrypt', $owner_details->id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_typeid).'/'.encryption_decryption_fun('encrypt',$reference_number),array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));


	$owner_full_name = $owner_details->owner_name.' '.$owner_details->owner_mname.' '.$owner_details->owner_lname;

			$rows[] 	= array( 
								array('data' =>$Wcounter,'class' => array('')),
								array('data' =>$owner_full_name ,'class' => array('')),
								array('data' =>$owner_address,'class' => array('')),
								//array('data' =>$delLink ,'class' => array('')),
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