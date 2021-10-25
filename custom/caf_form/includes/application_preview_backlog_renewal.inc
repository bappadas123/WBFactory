<?php 
function application_preview_backlog_renewal($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$linknumber,$linkdate,$flagmapp)
{
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	global $base_root,$base_path,$user;
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	
	if (!empty($application_id)) {
        $get_fa_cafa           				= 	get_fa_cafa($application_id);
       	$application_status      			= 	$get_fa_cafa['application_status'];
		$plan_approve_status      			= 	$get_fa_cafa['plan_approve_status'];
		$factory_identification_number		= 	$get_fa_cafa['factory_reg_identification_number'];
		$referance_number					= 	$get_fa_cafa['reference_number'];
		$is_basic_information_tab    		=   $get_fa_cafa['is_year_calculation_tab'];
    }
	
	
	if(empty($application_id)){
		  	drupal_set_message(('At first you must be filled up the general information of factory then go to second tab'),'warning');
			drupal_goto('applicant/caf-backlog-renew/apply-backlog-renewal-service/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$linknumber.'/'.$linkdate.'/'.$flagmapp) ;
	 }
	 if(empty($is_basic_information_tab)){
		  	drupal_set_message(('Please fill up the second tab than fill up the basic information'),'warning');			
			drupal_goto('applicant/caf-backlog-renew/backlog-renewal-basic-service/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$linknumber.'/'.$linkdate.'/'.$flagmapp) ;
	 } 
	$resultData = upload_document_data($application_id,$referance_number,$service_id,$factory_type_id);
	$a=0;
	foreach($resultData as $res){
		$upload[$a] = $res->id_doc_master; 
		$a++;
	}
	$b=0;
	$documents_master_details	= documents_master_data($service_id,$factory_type_id);
	foreach($documents_master_details as $documents){
		$master[$b] = $documents->id; 
		$b++;
	}
	sort($master);
	sort($upload);
	if ($master != $upload) {
    	drupal_set_message(('You must upload your  Documents of factory then go to next tab'),'warning');
		drupal_goto('applicant/caf-backlog-renew/cafb_renewal-backlog/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$linknumber.'/'.$linkdate.'/'.$flagmapp) ; 
	}
	
	$form = array();
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
			'#suffix' 		=> '</div>',
			'#type' 		=> 'checkbox',
			'#title' 		=> 'I hereby declare that the particulars given above are true the best of my knowledge and belief.',
			'#attributes'	=> array('id' => 'finalAgreeId','onchange' => 'return checkFinalAppCheckBox()'),
			'#required' 	=> TRUE,
	);
	/*$form['submit'] = array (
			'#type' 		=> 'submit',
			'#attributes' 	=> array('class' => array('btn btn-info'),'onclick' => 'if(!confirm("Are you sure to continue ?"){return false;}'),
			'#value' 		=> 'Save & Continue'										  
	);*/
	$form['back_link'] = array(
		'#prefix' => '<div class="row"><div class="col-md-1">',
		'#suffix' => '</div>',
		'#markup' => l(t('<i class="fa fa-angle-left" aria-hidden="true"></i> Back'), 'applicant/applicant-dasboard/', array('html' => TRUE,'attributes' => array('class' => array('btn btn-dark pull-left'))))
  	);
    if($application_status == 'I' || $application_status == 'B' || empty($application_status) || $application_status == 'In'){
    $form['submit'] = array(
        '#prefix' => '<div class="col-md-1">',
        '#suffix' => '</div>',
        '#attributes' => array('class' => array('btn btn-success')),
        '#type' => 'submit',
        '#value' => 'Save & Continue'
    );
	if(!empty($application_id)){
	$form['preview_link'] = array(
		'#prefix' => '<div class="col-md-10">',
        '#suffix' => '</div>',
  	//'#markup' => l(t('Preview as PDF'), 'applicant/applicant-dasboard/', array('html' => TRUE,'attributes' => array('class' => array('btn btn-dark space-left') )))
		'#markup' => l('PRINT DRAFT COPY', 'regsection/preview-varse-all-information/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'Preview as PDF','class'=>array('btn btn-warning pull-right'))))
  		);
		}
	}else{
		$form['markup'] = array(
        '#suffix' => '</div></div>',
        '#type' => 'markup',
       
    );
	
	}     	
return $form;

}

function registration_application_preview($application_id,$service_id,$factory_typeid,$reference_number){
	global $base_root,$base_path,$user;
	$output = "";
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
   		}if($get_all_data['factory_owershiptype']=="llp"){
   				$ownership_type = "Limited Liability Partnership";
   		}if($get_all_data['factory_owershiptype']=="cooperative"){
   				$ownership_type = "Co-operative";
   		}if($get_all_data['factory_owershiptype']=="registered"){
   				$ownership_type = "Registered Society under Society Register";
   		}if($get_all_data['factory_owershiptype']=="localbody"){
   				$ownership_type = "Local Body";
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
	
	$owner_address_details = !empty($get_all_data['addrline_premises'])?$get_all_data['addrline_premises'].',':'';
	$owner_address_details.= $get_all_data['owner_country_address'].',<br/>'.country_name($get_all_data['owner_country']);
	$getdata_factory_location	=  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address_location 	= $get_all_data['addrline'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_factory_location);
	$getdata_headoffice_address =  array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
	$headoffice_address 		= $get_all_data['addrline_off'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_headoffice_address);
	$passport_details = !empty($get_all_data['occupier_passport_premises'])?'Passport No-'.$get_all_data['occupier_passport_premises'].',<br/>Passport Issue Date-'.$get_all_data['date_of_issue_premises'].',<br/>Passport Expiry date-'.$get_all_data['date_of_expiry_premises']:'';
	$getdata_owner_address 		=  array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
	$owner_address 				=	$owner_address_details.'<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_owner_address);
	$previous_details			=  get_previous_details_view($application_id,$reference_number,$factory_typeid,$service_id);
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
		
		//$manufacturing_details=$base_root.$base_path.'view-manufacturing-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		//$link_manufacturing=ctools_modal_text_button(t('View Manufacturing Process(s)'), $manufacturing_details ,t('View Details)')) ;	
		
		$documents_details=$base_root.$base_path.'view-documents-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_documents=ctools_modal_text_button(t('View Documents list'), $documents_details ,t('View Details)')) ;
		
		$manager_details=$base_root.$base_path.'view-manager-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_manager=ctools_modal_text_button(t('View Manager(s)'), $manager_details ,t('View Details)')) ;
		
		//$power_details=$base_root.$base_path.'view-power-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		//$link_power=ctools_modal_text_button(t('View Power Details'), $power_details ,t('View Details)')) ;
			
		$factory_zone_date = get_factory_zone_name($get_all_data['factory_zone']);
		
		if(!empty($get_all_data['enargy_no'])){ $enargy_no = $get_all_data['enargy_no']; }else{$enargy_no =  'Nil';}
			if(!empty($get_all_data['cin_no'])){ $cin_no = $get_all_data['cin_no']; }else{$cin_no =  'Nil';}
			
		$power_generating_station 	= get_power_generating_station($application_id,$reference_number,$factory_typeid,$service_id);
		foreach($power_generating_station as $power){
			$power_details = $power->installed_power.'('.$power->power_unit.')';
		}
		$nature_details = get_manufacturing($application_id,$service_id,$factory_typeid,$reference_number);
		foreach($nature_details as $nature){
			$nature_work = $nature->nature_manufacturing;
		}
		if($get_all_data['wbpcb_category_name']==1){$consent ='Red'; $wbpcb_reference_no = $get_all_data['wbpcb_reference_no'];$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));}
			if($get_all_data['wbpcb_category_name']==2){$consent ='Green'; $wbpcb_reference_no = $get_all_data['wbpcb_reference_no'];$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));}
			if($get_all_data['wbpcb_category_name']==3){$consent ='Orange'; $wbpcb_reference_no = $get_all_data['wbpcb_reference_no'];$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));}
			
			if($get_all_data['wbpcb_category_name']== 4){
				$consent ='White'; 
				$wbpcb_reference_no = 'n/a'; 
				$wbpcb_ref_date = 'n/a';
				$file = $get_all_data['wbpcb_intimation_letter'];
				$file_url = '<a href='.file_create_url(get_uploaded_document_url($file)).' onclick = "popIt(this.href);return false;">View</a>';
				}
			if($get_all_data['wbpcb_category_name']==5){$consent ='Exempted'; $wbpcb_reference_no = 'n/a';$wbpcb_ref_date = 'n/a';}
		
		$details = $consent.'<br>WBPCB referance no. = '.$wbpcb_reference_no.'<br>WBPCB referance no = '.$wbpcb_ref_date.'<br>'.$file_url;
		
	$output .='<div class="row"><div class="box box-info"><div class="box-header with-border">
              	<h3 class="box-title">Application Preview</h3>
              
            	</div><div class = "box-body">
				<table class="table table-bordered"> <tr>
   								<th>Parameters</th>
   								<th>Inputs</th>
								</tr>';
	$output .='<tr><td colspan="2">A.Factory Information</td></tr>
				<tr><td>(i). Name of the factory</td><td>'.$get_all_data['factory_name'].'</td></tr>
				<tr><td>(ii). Ownership Type</td><td>'.$ownership_type.'</td></tr>
				<tr><td>(iii). PAN of the Business Establishment / Factory / Company </td><td>'.$get_all_data['factory_pan'].'</td></tr>
				<tr><td>(iv). Plan Approval number </td><td>'.$plan_approval_no.'</td></tr>
				<tr><td>(iv). Plan Approval Date </td><td>'.$plan_approval_date.'</td></tr>
				<tr><td>(v). GSTIN No. </td><td>'.$get_all_data['gstin_no'].'</td></tr>
				<tr><td>(vi). Udyog Aadhaar No.</td><td>'.$get_all_data['udyog_aadhaar'].'</td></tr>
				<tr><td>(vii). Enargy Meter No. </td><td>'.$enargy_no.'</td></tr>
				<tr><td>(viii). CIN No. </td><td>'.$cin_no.'</td></tr>
				<tr><td colspan="2">B.Location of Factory </td></tr>
				<tr><td>(i).Zone</td><td>'.$factory_zone_date['zone_name'].'</td></tr>
				<tr><td>(ii).Address</td><td>'.$factory_address_location.'</td></tr>
				<tr><td colspan="2">C.Address of the Registered office / Head office<br/><font color="#FF0000">(N.B:-This address will be treated as communication address as per Section 7 of Factories Act,1948 )</font> </td></tr>
				<tr><td>(i).Address</td><td>'.$headoffice_address.'</td></tr>
				<tr><td>(ii).Telephone No</td><td>'.$get_all_data['comm_telephone'].'</td></tr>
				<tr><td>(iii).Mobile No</td><td>'.$get_all_data['comm_mobile'].'</td></tr>
				<tr><td>(iv).Fax No</td><td>'.$get_all_data['comm_fax'].'</td></tr>
				<tr><td>(iv)..Email Id</td><td>'.$get_all_data['comm_email'].'</td></tr>
				<tr><td colspan="2">D.Details of owner of the premises occupied as a factory</td></tr>
				<tr><td>(i).Name of the owner</td><td>'.$get_all_data['owner_name'].'&nbsp;'.$get_all_data['owner_mname'].'&nbsp;'.$get_all_data['owner_lname'].'</td></tr>
				<tr><td>(ii).Address</td><td>'.$owner_address.'<br>'.$passport_details.'</td></tr>
				<tr><td>E.Factory Identification according to WBPCB</td><td>'.$details.'</td></tr>
				<tr><td colspan="2">F.State the period of license</td></tr>
				<tr><td>(i).Date from which the premises is occupied or been taken into use as factory </td><td>'.date('dS M Y', strtotime($get_all_data['date_of_amenability'])).'</td>
				<tr><td>(ii).State the period of license required </td><td>'.$get_all_data['period_for_application'].'year(s)</td></tr>
				<tr><td>(iii).Whethere any changes name and ownership details of factory </td><td>'.$is_previous.$view.'</td></tr>
				<tr><td colspan="2">G.Worker Details</td></tr>
				<tr><td>(i).Maximum number of workers employed or to be employed in tha factory</td><td>'.$link_t.'</td></tr>
				<tr><td colspan="2">H.Power Details</td></tr>
				<tr><td>(i).Installed Power or to be installed power </td><td>'.$power_details.'</td></tr>
				<tr><td colspan="2">I.Manager Details</td></tr>
				<tr><td>(i).Manager Details</td><td>'.$link_manager.'</td></tr>
				<tr><td colspan="2">J.Occupier Details</td></tr>
				<tr><td>(i).View occupier details</td><td>'.$link_occuiper.'</td></tr>
				<tr><td colspan="2">K.Director Details</td></tr>
				<tr><td>(i).View director details</td><td>'.$link_director.'</td></tr><tr>
				<td colspan="2">L.Manufacturing process</td></tr>
				<tr><td>(i).Carried/to be carried on the factory</td><td>'.$nature_work.'</td></tr>
				<td colspan="2">M.Uploaded Documents</td></tr>
				<tr><td>(i).View uploaded documetns</td><td>'.$link_documents.'</td></tr>';
	$output .= '</table></div></div></div>';
	return $output;
	
}
function application_preview_backlog_renewal_submit($form, &$form_state){
	$val   						    =  $form_state['values'];
	$uid 			    			=  $user->uid;
	
	$application_no 				=  encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$service_id						=  encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$factorytype_id					=  encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$referance_no					=  encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	
	$get_fa_cafa 					= get_fa_cafa($application_no);
	if($get_fa_cafa['application_status'] =='B'){
		
		//-----------Worker table update---------------------------
    $worker_status 	= 	array('worker_registration_status' => 'RP');
	$queryworker 	=	db_update('fa_worker_details');
	$queryworker	->	fields($worker_status);
	$queryworker	->	condition('application_id',$application_no,'=');
	$queryworker	->	condition('service_id',$service_id,'=');
	$queryworker	->	condition('factory_type',$factorytype_id,'=');
    $queryworker	->	condition('application_reference_no',$referance_no,'=');
	$queryworker    ->	execute();
	//-----------Manufacturing table update---------------------------
	  $manufacturing_status 	= 	array('manufacturing_application_status' => 'RP');
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
	  //drupal_goto('applicant/fees_registration/'.$val['serviceid_hidden'].'/'.$val['factorytypeid_hidden'].'/'.$val['applicationid_hidden'].'/'.$val['reference_no_hidden']) ;
	  drupal_goto('applicant-dashboard/') ;
	
	}else{
	
    //-----------Worker table update---------------------------
    $worker_status 	= 	array('worker_registration_status' => 'F');
	$queryworker 	=	db_update('fa_worker_details');
	$queryworker	->	fields($worker_status);
	$queryworker	->	condition('application_id',$application_no,'=');
	$queryworker	->	condition('service_id',$service_id,'=');
	$queryworker	->	condition('factory_type',$factorytype_id,'=');
    $queryworker	->	condition('application_reference_no',$referance_no,'=');
	$queryworker    ->	execute();
	//-----------Manufacturing table update---------------------------
	  $manufacturing_status 	= 	array('manufacturing_application_status' => 'F');
	  $querymanufacturing 		=	db_update('fa_nature_manufacturing');
	  $querymanufacturing	    ->	fields($manufacturing_status);
	  $querymanufacturing		->	condition('application_id',$application_no,'=');
	  $querymanufacturing		->	condition('service_id',$service_id,'=');
	  $querymanufacturing	    ->	condition('factory_type',$factorytype_id,'=');
	  $querymanufacturing	    ->	condition('application_reference_no',$referance_no,'=');
	  $querymanufacturing		->	execute();
	//-----------Power table update---------------------------
	  $power_status 			= 	array('power_application_status' => 'F');
	  $querypower 				=	db_update('fa_power_details');
	  $querypower				->	fields($power_status);
	  $querypower		    	->	condition('application_id',$application_no,'=');
	  $querypower		    	->	condition('service_id',$service_id,'=');
	  $querypower				->	condition('factory_type',$factorytype_id,'=');
	  $querypower				->	condition('application_reference_no',$referance_no,'=');
	  $querypower				->	execute();
	//-----------Director table update---------------------------
	  $director_status 			= 	array('application_status' => 'F');
	  $querydirector 			=	db_update('fa_director_details');
	  $querydirector			->	fields($director_status);
	  $querydirector		    ->	condition('application_director_id',$application_no,'=');
	  $querydirector		    ->	condition('director_service_id',$service_id,'=');
	  $querydirector			->	condition('factory_type_id',$factorytype_id,'=');
	  $querydirector			->	condition('application_reference_no',$referance_no,'=');
	  $querydirector			->	execute();
	//-----------Manager table update---------------------------
	  $manager_status 			= 	array('application_status' => 'F');
	  $querymanager 			=	db_update('fa_manager_details');
	  $querymanager				->	fields($manager_status);
	  $querymanager		    	->	condition('application_manager_id',$application_no,'=');
	  $querymanager		   		 ->	condition('manager_service_id',$service_id,'=');
	  $querymanager				->	condition('factory_type_id',$factorytype_id,'=');
	  $querymanager				->	condition('application_reference_no',$referance_no,'=');
	  $querymanager				->	execute();
	  
	  //-----------occupier table update---------------------------
	  $occupier_status 			= 	array('application_status' => 'F');
	  $querymanager 			=	db_update('fa_occupier_details');
	  $querymanager				->	fields($occupier_status);
	  $querymanager		    	->	condition('application_occupier_id',$application_no,'=');
	  $querymanager		   		 ->	condition('occupier_service_id',$service_id,'=');
	  $querymanager				->	condition('factory_type_id',$factorytype_id,'=');
	  $querymanager				->	condition('application_reference_no',$referance_no,'=');
	  $querymanager				->	execute();
	 //----------------Documents Update-------------------
	  
	  $doc_status 		= 	array('application_status' => 'F');
	  $querydoc 		=	db_update('fa_caf_upload_doc');
	  $querydoc			->	fields($doc_status);
	  $querydoc		    ->	condition('app_id',$application_no,'=');
	  $querydoc		    ->	condition('upload_documents_service_id',$service_id,'=');
	  $querydoc			->	condition('upload_doc_factory_type_id',$factorytype_id,'=');
	  $querydoc			->	condition('application_reference_no',$referance_no,'=');
	  $querydoc			->	execute();
	  
	  $caf_update = 	array('application_status' => 'F');
	  $queryabc 		=	db_update('fa_cafa');
	  $queryabc		    ->	fields($caf_update);
	  $queryabc			->	condition('id',$application_no,'=');
	  $queryabc	        ->	execute();
	  
	  drupal_set_message('Your application has been successfully saved.');
	  
	  drupal_goto('applicant/fees_registration/'.$val['serviceid_hidden'].'/'.$val['factorytypeid_hidden'].'/'.$val['applicationid_hidden'].'/'.$val['reference_no_hidden']) ;
	} 
}


function documents_master_data($service_id,$factory_type_id){
	$query_factory_documents 	=  db_select('fa_documents_master', 'documents');
	$query_factory_documents	-> fields('documents',array('id'));
	$query_factory_documents	-> condition('documents.document_service_id', $service_id, '=');
	$query_factory_documents	-> condition('documents.document_factory_id', $factory_type_id, '=');
	$query_factory_documents	-> condition('documents.id',array(31), 'NOT IN');
	$query_factory_documents	-> orderBy('documents.id', 'ASC');
	$result_factory_documents 	= $query_factory_documents->execute()->fetchAll(); 
	return $result_factory_documents;
}


function upload_document_data($application_id,$referance_number,$service_id,$factory_type_id){
		$query 	=  db_select('fa_caf_upload_doc', 'fcud')->distinct();
		$query 	-> fields('fcud', array('id_doc_master'));
		$query	-> condition('fcud.app_id', $application_id);
		$query	-> condition('fcud.application_reference_no', $referance_number);
		$query	-> condition('fcud.upload_documents_service_id', $service_id);
		$query	-> condition('fcud.upload_doc_factory_type_id', $factory_type_id);
		$query	-> condition('fcud.id_doc_master',array(31), 'NOT IN');
		$resultData = $query->execute()->fetchAll();
		return $resultData;
}
?>