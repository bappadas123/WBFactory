<?php
//$applicationid
function application_preview_repayment_service($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$referancenumber) {	

	global $base_root,$base_path,$user;
  	$service_id 						= 	encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 					= 	encryption_decryption_fun('decrypt',$factory_typeid);
	$application_id 					= 	encryption_decryption_fun('decrypt',$applicationid);
	$form 								= 	array();
	$get_fa_cafa           				= 	get_fa_cafa($application_id);
    $application_status      			= 	$get_fa_cafa['application_status'];
	$plan_approve_status      			= 	$get_fa_cafa['plan_approve_status'];
	$factory_identification_number		= 	$get_fa_cafa['factory_reg_identification_number'];
	$referance_number					= 	$get_fa_cafa['reference_number'];
		
   
	//echo $referance_number;die();
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
			'#default_value' 	=> encryption_decryption_fun('encrypt', $referance_number)
			 
	);
	$form['applicationid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $applicationid
	);
	$form['linknumber_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $linknumber
	);
	$form['linkdate_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $linkdate
	);	
	$form['flagmapp_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $flagmapp
	);
	$form['application_preview']['application_preview_table'] 	= array(
  			'#type'		=> 'markup',
			'#markup'	=> registration_application_preview($application_id,$service_id,$factory_type_id,$referance_number)
				
			
  
			);	
	$form['application_preview']['finalAgree'] 	= array(
					 '#prefix' 		=> '<div class="col-md-12 col-xs-12">',	
					 '#suffix' => '</div>',
					 '#type' 		=> 'checkbox',
					 '#title' => ' I hereby declare that the particulars given above are true the best of my knowledge and belief.',
				     '#attributes'		=> array('id' => 'finalAgreeId','onchange' => 'return checkFinalAppCheckBox()'),
					  '#required' 		=> TRUE,
				);
	/*$form['submit'] = array (
			'#type' 		=> 'submit',
			'#attributes' 	=> array('class' => array('btn btn-info'),'onclick' => 'if(!confirm("Are you sure to continue ?"){return false;}'),
			'#value' 		=> 'Save & Continue'										  
		);*/
		$form['application_preview']['submit'] = array(
'#prefix' => '<div class="col-md-12 col-xs-12">',
'#suffix' => '</div>',
'#attributes' => array('class' => array('btn btn-info'), 'onclick' => 'if(!confirm("Are you sure to continue ?")){return false;}'),
'#type' => 'submit',
'#value' 		=> 'Save & Continue'		
);
	//} 
	

           	
return $form;
}
function registration_application_preview($application_id,$service_id,$factory_typeid,$reference_number){
	global $base_root,$base_path,$user;
	$output ="";
	$get_all_data =  get_fa_cafa($application_id);
	if($get_all_data['factory_owershiptype']=="pv"){
			$ownership_type = "Pvt Ltd Company";
	}if($get_all_data['factory_owershiptype']=="ltd"){
			$ownership_type = "Ltd Company";
	}if($get_all_data['factory_owershiptype']=="par_firm"){
			$ownership_type = "Partnership Firm";
	}if($get_all_data['factory_owershiptype']=="pro_firm"){
			$ownership_type = "Proprietorship Firm";
	}if($get_all_data['factory_owershiptype']=="govt"){
			$ownership_type = "Govt";
	}if($get_all_data['factory_owershiptype']=="psu"){
			$ownership_type = "PSU";
	}if($get_all_data['factory_owershiptype']=="others"){
			$ownership_type = "Others";
	}
	$is_backlog = $get_all_data['is_backlog'];
	if($is_backlog == 1){
		$plan_approval_no = $get_all_data['backlog_plan_approval_no'];
		$plan_approval_date =date('dS M Y', strtotime($get_all_data['backlog_plan_approval_date']));
	}else{
		$plan_approval_no = $get_all_data['factory_plan_approval_number'];
		$plan_approval_date = date('dS M Y', strtotime($get_all_data['modification_date']));
	}
	$getdata_factory_location	 =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address_location 	 = $get_all_data['addrline'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_factory_location);
	$getdata_headoffice_address  =  array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
	$headoffice_address 		 = $get_all_data['addrline_off'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_headoffice_address);
	$getdata_owner_address 		 =  array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
	$owner_address 				 =	$get_all_data['addrline_premises'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_owner_address);
	$previous_details 			=  get_previous_details_view($application_id,$reference_number,$factory_typeid,$service_id);
	foreach($previous_details as $pre_row){
		$is_previous		 	= $pre_row->is_previous;
		if($is_previous == "Yes"){
			$view = "";
		}
	}
	ctools_include('ajax');
        ctools_include('modal');
	    ctools_modal_add_js();	 
		$worker_link=$base_root.$base_path.'view-worker-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_t=ctools_modal_text_button(t('View Worker(s)'), $worker_link ,t('View Details)')) ;
		
		$occupier_details=$base_root.$base_path.'view-occuiper-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_occuiper=ctools_modal_text_button(t('View Occupier(s)'), $occupier_details ,t('View Details)')) ;	
		
		$director_details=$base_root.$base_path.'view-director-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_director=ctools_modal_text_button(t('View Director(s)'), $director_details ,t('View Details)')) ;	
		
		$manufacturing_details=$base_root.$base_path.'view-manufacturing-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_manufacturing=ctools_modal_text_button(t('View Manufacturing Process(s)'), $manufacturing_details ,t('View Details)')) ;	
		
		$documents_details=$base_root.$base_path.'view-documents-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_documents=ctools_modal_text_button(t('View Documents list'), $documents_details ,t('View Details)')) ;
		
		$manager_details=$base_root.$base_path.'view-manager-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_manager=ctools_modal_text_button(t('View Manager(s)'), $manager_details ,t('View Details)')) ;
		
		$power_details=$base_root.$base_path.'view-power-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_power=ctools_modal_text_button(t('View Power Details'), $power_details ,t('View Details)')) ;
			
		$factory_zone_date = get_factory_zone_name($get_all_data['factory_zone']);
		
	$output .='<div class="row"><div class="box box-info"><div class="box-header with-border">
              <h3 class="box-title">Application Preview</h3>
              
            </div><div class = "box-body">
			<table class="table table-bordered"> <tr>
   								<th>Parameters</th>
   								<th>Inputs</th>
								</tr>';
	$output .='<tr><td colspan="2">A.Factory Information</td></tr>
				<tr><td>(i).Name of the factory</td><td>'.$get_all_data['factory_name'].'</td></tr>
				<tr><td>(ii).Ownership Type</td><td>'.$ownership_type.'</td></tr>
				<tr><td>(iii).PAN of the Business Establishment / Factory / Company </td><td>'.$get_all_data['factory_pan'].'</td></tr>
				<tr><td>(iv).Plan Approval number </td><td>'.$plan_approval_no.'</td></tr>
				<tr><td>(iv).Plan Approval Date </td><td>'.$plan_approval_date.'</td></tr>
				<tr><td colspan="2">B.Location of Factory </td></tr>
				<tr><td>(i).Zone</td><td>'.$factory_zone_date['zone_name'].'<br/>('.$factory_zone_date['zone_details'].')</td></tr>
				<tr><td>(ii).Address</td><td>'.$factory_address_location.'</td></tr>
				<tr><td colspan="2">C.Address of the Registered office / Head office<br/><font color="#FF0000">(N.B:-This address will be treated as communication address as per Section 7 of Factories Act,1948 )</font> </td></tr>
				<tr><td>(i).Address</td><td>'.$headoffice_address.'</td></tr>
				<tr><td>(ii).Telephone No</td><td>'.$get_all_data['comm_telephone'].'</td></tr>
				<tr><td>(iii).Mobile No</td><td>'.$get_all_data['comm_mobile'].'</td></tr>
				<tr><td>(iv).Fax No</td><td>'.$get_all_data['comm_fax'].'</td></tr>
				<tr><td>(iv)..Email Id</td><td>'.$get_all_data['comm_email'].'</td></tr>
				<tr><td colspan="2">D.Details of owner of the premises occupied as a factory</td></tr>
				<tr><td>(i).Name of the owner</td><td>'.$get_all_data['owner_name'].'</td></tr>
				<tr><td>(ii).Address</td><td>'.$owner_address.'</td></tr>
				<tr><td colspan="2">E.Factory Identification according to WBPCB</td></tr>
				<tr><td colspan="2">F.State the period of license</td></tr>
				<tr><td>(i).Date from which the premises is occupied or been taken into use as factory </td><td>'.date('dS M Y', strtotime($get_all_data['date_of_amenability'])).'</td>
				<tr><td>(ii).State the period of license required </td><td>'.$get_all_data['period_for_application'].'year(s)</td></tr>
				<tr><td>(iii).Whethere any changes name and ownership details of factory </td><td>'.$is_previous.$view.'</td></tr>
				<tr><td colspan="2">G.Worker Details</td></tr>
				<tr><td>(i).Maximum number of workers employed or to be employed in tha factory</td><td>'.$link_t.'</td></tr>
				<tr><td colspan="2">H.Power Details</td></tr>
				<tr><td>(i).Installed Power or to be installed power </td><td>'.$link_power.'</td></tr>
				<tr><td colspan="2">I.Manager Details</td></tr>
				<tr><td>(i).Manager Details</td><td>'.$link_manager.'</td></tr>
				<tr><td colspan="2">J.Occupier Details</td></tr>
				<tr><td>(i).View occupier details</td><td>'.$link_occuiper.'</td></tr>
				<tr><td colspan="2">K.Director Details</td></tr>
				<tr><td>(i).View director details</td><td>'.$link_director.'</td></tr><tr>
				<td colspan="2">L.Manufacturing process</td></tr>
				<tr><td>(i).Carried/to be carried on the factory</td><td>'.$link_manufacturing.'</td></tr>
				<td colspan="2">M.Uploaded Documents</td></tr>
				<tr><td>(i).View uploaded documetns</td><td>'.$link_documents.'</td></tr>';
	$output .= '</table></div></div></div>';
	return $output;
	
}
function application_preview_repayment_service_submit($form, &$form_state){
		$val   						    =  $form_state['values'];
	$uid 			    			=  $user->uid;
	$service_id						=  encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$factorytype_id				=  encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$application_no 				=  encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$referance_no				=  encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	
    //-----------Worker table update---------------------------
    $worker_status 	= 	array('worker_registration_status' => 'RS');
	$queryworker 	=	db_update('fa_worker_details');
	$queryworker	->	fields($worker_status);
	$queryworker	->	condition('application_id',$application_no,'=');
	$queryworker	->	condition('service_id',$service_id,'=');
	$queryworker	->	condition('factory_type',$factorytype_id,'=');
    $queryworker	->	condition('application_reference_no',$referance_no,'=');
	$queryworker    ->	execute();
	//-----------Manufacturing table update---------------------------
	  $manufacturing_status 	= 	array('manufacturing_application_status' => 'RS');
	  $querymanufacturing 		=	db_update('fa_nature_manufacturing');
	  $querymanufacturing	    ->	fields($manufacturing_status);
	  $querymanufacturing		->	condition('application_id',$application_no,'=');
	  $querymanufacturing		->	condition('service_id',$service_id,'=');
	  $querymanufacturing	    ->	condition('factory_type',$factorytype_id,'=');
	  $querymanufacturing	    ->	condition('application_reference_no',$referance_no,'=');
	  $querymanufacturing		->	execute();
	//-----------Power table update---------------------------
	  $power_status 			= 	array('power_application_status' => 'RS');
	  $querypower 				=	db_update('fa_power_details');
	  $querypower				->	fields($power_status);
	  $querypower		    	->	condition('application_id',$application_no,'=');
	  $querypower		    	->	condition('service_id',$service_id,'=');
	  $querypower				->	condition('factory_type',$factorytype_id,'=');
	  $querypower				->	condition('application_reference_no',$referance_no,'=');
	  $querypower				->	execute();
	//-----------Director table update---------------------------
	  $director_status 			= 	array('application_status' => 'RS');
	  $querydirector 			=	db_update('fa_director_details');
	  $querydirector			->	fields($director_status);
	  $querydirector		    ->	condition('application_director_id',$application_no,'=');
	  $querydirector		    ->	condition('director_service_id',$service_id,'=');
	  $querydirector			->	condition('factory_type_id',$factorytype_id,'=');
	  $querydirector			->	condition('application_reference_no',$referance_no,'=');
	  $querydirector			->	execute();
	//-----------Manager table update---------------------------
	  $manager_status 			= 	array('application_status' => 'RS');
	  $querymanager 			=	db_update('fa_manager_details');
	  $querymanager				->	fields($manager_status);
	  $querymanager		    	->	condition('application_manager_id',$application_no,'=');
	  $querymanager		   		 ->	condition('manager_service_id',$service_id,'=');
	  $querymanager				->	condition('factory_type_id',$factorytype_id,'=');
	  $querymanager				->	condition('application_reference_no',$referance_no,'=');
	  $querymanager				->	execute();
	  
	  //-----------occupier table update---------------------------
	  $occupier_status 			= 	array('application_status' => 'RS');
	  $querymanager 			=	db_update('fa_occupier_details');
	  $querymanager				->	fields($occupier_status);
	  $querymanager		    	->	condition('application_occupier_id',$application_no,'=');
	  $querymanager		   		 ->	condition('occupier_service_id',$service_id,'=');
	  $querymanager				->	condition('factory_type_id',$factorytype_id,'=');
	  $querymanager				->	condition('application_reference_no',$referance_no,'=');
	  $querymanager				->	execute();
	 //----------------Documents Update-------------------
	  
	  $doc_status 		= 	array('application_status' => 'RS');
	  $querydoc 		=	db_update('fa_caf_upload_doc');
	  $querydoc			->	fields($doc_status);
	  $querydoc		    ->	condition('app_id',$application_no,'=');
	  $querydoc		    ->	condition('upload_documents_service_id',$service_id,'=');
	  $querydoc			->	condition('upload_doc_factory_type_id',$factorytype_id,'=');
	  $querydoc			->	condition('application_reference_no',$referance_no,'=');
	  $querydoc			->	execute();
	  $caf_update = 	array('application_status' => 'RS');
	  $queryabc 		=	db_update('fa_cafa');
	  $queryabc		    ->	fields($caf_update);
	  $queryabc			->	condition('id',$application_no,'=');
	  $queryabc	        ->	execute();
	  drupal_set_message('Your application has been successfully saved.');
	  drupal_goto('applicant/fees_registration/'.$val['serviceid_hidden'].'/'.$val['factorytypeid_hidden'].'/'.$val['applicationid_hidden'].'/'.$val['reference_no_hidden']) ;
}   
?>