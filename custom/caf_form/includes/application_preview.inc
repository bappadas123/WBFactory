<?php
function application_preview($form, &$form_state,$serviceid,$factorytype,$applicationid,$referenceno) {
	
	global $base_root,$base_path,$user,$_SESSION;
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factorytype);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$reference_no 		= encryption_decryption_fun('decrypt', $referenceno);
	
	if(empty($application_id) || $application_id==0 || $application_id == ''){
		  drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please Upload All required Documents.</h5>'),'alert alert-danger alert-dismissible');
		  drupal_goto('applicant/caf/cafb/'.$serviceid.'/'.$factorytype.'/'.$applicationid.'/'.$referenceno) ;
	}

	$get_fa_cafa           			= 	get_application_withid($application_id);
	$plan_approve_status      		= 	$get_fa_cafa[0]->plan_approve_status;
	//$reference_no 					=   $get_fa_cafa[0]->reference_number;
	$identification_number			= 	$get_fa_cafa[0]->plan_approve_identification_number;
    
	$get_fa_occupier           		= 	get_all_occupier_data($application_id,$service_id,$factory_type_id,$reference_no); //echo "<pre>";print_r($get_fa_occupier);exit;

	$form = array();
	
		$resultData = upload_document_data($application_id,$reference_no,$service_id,$factory_type_id);
		$a=0;
		$master = array();
		$upload = array();
		
		foreach($resultData as $res){
			$upload[$a] = $res->doc_master_id; 
			$a++;
		}
		
		$documents_master_details	= documents_master_data($service_id,$factory_type_id);
		$b=0;
		foreach($documents_master_details as $documents){
			if($documents->doc_listid!='7'){
				$master[$b] = $documents->doc_listid;
			}
			$b++;
		}
		
		$finalarr = array_intersect($master, array_unique($upload));

		if (count($master)!=count($finalarr)) {

    		drupal_set_message(('You must upload all required(*) Documents before go to next tab'),'warning');
			drupal_goto('applicant/caf/cafb/'.$serviceid.'/'.$factorytype.'/'.$applicationid.'/'.$referenceno) ;
		 
		}
		
	if($plan_approve_status == 'F' || $plan_approve_status == 'ABk'){ 
		$pdf_link	= l('Download Application Form', 'download-pdf-new-plan/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$plan_approve_status), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_blank','class'=>array('button'))));	
		//$form['application_documents']['markup_pdf'] = array (
//				  #type' 			=> 'markup',
//				  #markup' 		=> $pdf_link
//		 );
	}
	
	$getdata_factory_address =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address         = get_full_address('fa_cafa','sub-table',$get_fa_cafa[0]->id,$getdata_factory_address);
	
	$getdata_headoffice_address =  array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
	$headoffice_address = get_full_address('fa_cafa','sub-table',$get_fa_cafa[0]->id,$getdata_headoffice_address);

	$getdata_communication_address = array('district_comm','subdivision_comm','areatype_comm','block_comm','panchayat_comm','policestation_comm','pincodecomm','state_comm','postoffice_comm');
	$communication_address = get_full_address('fa_cafa','sub-table',$get_fa_cafa[0]->id,$getdata_communication_address);

	$getdata_occupier_permanent_address =  array('district_oprmntadr','subdivision_oprmntadr','areatype_oprmntadr','block_oprmntadr','panchayat_oprmntadr','policestation_oprmntadr','pincodeoprmntadr','state_oprmntadr','postoffice_oprmntadr');
	$permanent_address  = get_full_address('fa_occupier_details','sub-table',$get_fa_occupier[0]->id,$getdata_occupier_permanent_address);

	$getdata_occupier_present_address =  array('district_oprsntadr','subdivision_oprsntadr','areatype_oprsntadr','block_oprsntadr','panchayat_oprsntadr','policestation_oprsntadr','pincodeoprsntadr','state_oprsntadr','postoffice_oprsntadr');
	$present_address    = get_full_address('fa_occupier_details','sub-table',$get_fa_occupier[0]->id,$getdata_occupier_present_address);

	$getdata_owner_address =  array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
	$owner_address    = get_full_address('fa_cafa','sub-table',$get_fa_cafa[0]->id,$getdata_owner_address);

	$estate_type 		   = get_estate_type($get_fa_cafa[0]->estate_type);
	$final_estate_type     = !empty($estate_type) ? $estate_type[0]->estate_name : $get_fa_cafa[0]->estate_type_name;
	
	if($get_fa_cafa[0]->tm_appliction_id==NULL)
	{
		$country_name 		       = country_name($get_fa_occupier[0]->country_oprmntadr);
		$country_name_oprsntadr    = country_name($get_fa_occupier[0]->country_oprsntadr);
		$country_premises 		   = country_name($get_fa_cafa[0]->country_premises);
	}
	else
	{
		$country_name='INDIA'; $country_name_oprsntadr='INDIA'; $country_premises ='INDIA';
	}
	
	$ocupier_present_address   = !empty($present_address) ? $present_address.', '.$get_fa_occupier[0]->addrline_oprsntadr : $get_fa_occupier[0]->addrline_oprsntadr;
	$ocupier_permanent_address = !empty($permanent_address) ? $permanent_address.', '.$get_fa_occupier[0]->addrline_oprmntadr : $get_fa_occupier[0]->addrline_oprmntadr;
    $owner_address             = !empty($owner_address) ? $owner_address.', '.$get_fa_cafa[0]->addrline_premises : $get_fa_cafa[0]->addrline_premises;

    $get_worker                = get_worker_detials($application_id);
	
		ctools_include('ajax');
        ctools_include('modal');
	    ctools_modal_add_js();	 

	$occupier_details=$base_root.$base_path.'view-occuiper-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
	$link_occuiper =ctools_modal_text_button(t('View Occupier(s)'), $occupier_details ,t('View Details)')) ;	

	$owner_details=$base_root.$base_path.'view-owner-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
	$link_owner =ctools_modal_text_button(t('View Owner Details'), $owner_details ,t('View Details)')) ;

	$worker_link=$base_root.$base_path.'view-worker-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
	$link_worker =ctools_modal_text_button(t('View Workers'), $worker_link ,t('View Details)')) ;

	$documents_details=$base_root.$base_path.'view-documents-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
	$link_documents =ctools_modal_text_button(t('View Documents list'), $documents_details ,t('View Details)')) ;
	

	$output .= '<tr><td colspan="2" class="sub-title">H. Plan Related Documents</td></tr>
				<tr style="font-weight: bold;"><td> Document List View</td><td>'.$link_documents.'</td></tr>';
				
	//(Application Number:- '.$get_fa_cafa[0]->plan_approve_identification_number.')				
	   
	  //if($get_fa_occupier[0]->country_oprmntadr == 99) 
//	  {	   
//	  	$Occupier_Permanent_Address = '<tr><td>(ii) Aadhaar No</td><td>'.$get_fa_occupier[0]->aadhaar_oprmntadr.'</td></tr>
//									  <tr><td>(iii) Address </td><td>'.$ocupier_permanent_address.'</td></tr>
//									  <tr><td>(iv) Street Name</td><td>'.$get_fa_occupier[0]->street_name_oprmntadr.'</td></tr>
//									  <tr><td>(v) House No.</td><td>'.$get_fa_occupier[0]->house_no_oprmntadr.'</td></tr>';
//	  }
//	  else{	  	
//	  	$Occupier_Permanent_Address = '<tr><td>(ii) Passport No</td><td>'.$get_fa_occupier[0]->passport_oprmntadr.' <b>(DOI):</b>'.$get_fa_occupier[0]->passport_date_of_issue_oprmntadr.' <b>(DOE):</b>'.$get_fa_occupier[0]->passport_date_of_expiry_oprmntadr.'</td></tr>
//									  <tr><td>(iii) Street Name</td><td>'.$get_fa_occupier[0]->street_name_oprmntadr.'</td></tr>
//									  <tr><td>(iv) House No.</td><td>'.$get_fa_occupier[0]->house_no_oprmntadr.'</td></tr>
//									  <tr><td>(v) Police Station</td><td>'.$get_fa_occupier[0]->police_station_oprmntadr.'</td></tr>';
//	  }
//
//	  if($get_fa_occupier[0]->country_oprsntadr == 99) 
//	  {	  
//	  	$Occupier_Present_Address = '<tr><td>(ii) Aadhaar No</td><td>'.$get_fa_occupier[0]->aadhaar_oprsntadr.'</td></tr>
//								     <tr><td>(iii) Address</td><td>'.$ocupier_present_address.'</td></tr>
//									 <tr><td>(iv) Street Name</td><td>'.$get_fa_occupier[0]->street_name_oprsntadr.'</td></tr>
//									 <tr><td>(v) House No.</td><td>'.$get_fa_occupier[0]->house_no_oprsntadr.'</td></tr>';
//	  }
//	  else{	  	
//	  	$Occupier_Present_Address = '<tr><td>(ii) Passport No</td><td>'.$get_fa_occupier[0]->passport_oprsntadr.' <b>(DOI):</b>'.$get_fa_occupier[0]->passport_date_of_issue_oprsntadr.' <b>(DOE):</b>'.$get_fa_occupier[0]->passport_date_of_expiry_oprsntadr.'</td></tr>
//									  <tr><td>(iii) Street Name</td><td>'.$get_fa_occupier[0]->street_name_oprsntadr.'</td></tr>
//									  <tr><td>(iv) House No.</td><td>'.$get_fa_occupier[0]->house_no_oprsntadr.'</td></tr>
//									  <tr><td>(v) Police Station</td><td>'.$get_fa_occupier[0]->police_station_oprsntadr.'</td></tr>';
//	  }

	  /*if($get_fa_cafa[0]->country_premises == 99) 
	  {	  
	  	$Owner_Address = '<tr><td>(ii) Aadhaar No</td><td>'.$get_fa_cafa[0]->aadhaar_premises.'</td></tr>
						  <tr><td>(iii) Address</td><td>'.$owner_address.'</td></tr>
						  <tr><td>(iv) Street Name</td><td>'.$get_fa_cafa[0]->street_name_premises.'</td></tr>
						  <tr><td>(v) House No.</td><td>'.$get_fa_cafa[0]->house_no_premises.'</td></tr>';
	  }
	  else{	  	
	  	$Owner_Address = '<tr><td>(ii) Passport No</td><td>'.$get_fa_cafa[0]->passport_premises.' <b>(DOI):</b>'.$get_fa_cafa[0]->passport_date_of_issue_premises.' <b>(DOE):</b>'.$get_fa_cafa[0]->passport_date_of_expiry_premises.'</td></tr>
						  <tr><td>(iii) Street Name</td><td>'.$get_fa_cafa[0]->street_name_premises.'</td></tr>
						  <tr><td>(iv) House No.</td><td>'.$get_fa_cafa[0]->house_no_premises.'</td></tr>
						  <tr><td>(v) Police Station</td><td>'.$get_fa_cafa[0]->police_station_premises.'</td></tr>';
	  }*/
	  
	  if($get_fa_cafa[0]->wbpcb_category_name ==1){$consent ='Red'; $wbpcb_reference_no = $get_fa_cafa[0]->wbpcb_reference_no;$wbpcb_ref_date = date('dS M Y', strtotime($get_fa_cafa[0]->wbpcb_ref_date));}
				if($get_fa_cafa[0]->wbpcb_category_name ==2){$consent ='Green'; $wbpcb_reference_no = $get_fa_cafa[0]->wbpcb_reference_no;$wbpcb_ref_date = date('dS M Y', strtotime($get_fa_cafa[0]->wbpcb_ref_date));}
				if($get_fa_cafa[0]->wbpcb_category_name ==3){$consent ='Orange'; $wbpcb_reference_no = $get_fa_cafa[0]->wbpcb_reference_no;$wbpcb_ref_date = date('dS M Y', strtotime($get_fa_cafa[0]->wbpcb_ref_date));}
				
				if($get_fa_cafa[0]->wbpcb_category_name == 4){
				$consent ='White'; 
				$wbpcb_reference_no = 'n/a'; 
				$wbpcb_ref_date = 'n/a';
				$file = $get_fa_cafa[0]->wbpcb_intimation_letter;
				$file_url = '<a href='.file_create_url(get_uploaded_document_url($file)).' target= "_BLANK" onclick = "popIt(this.href);return false;">View</a>';
				}
				if($get_fa_cafa[0]->wbpcb_category_name==5){$consent ='Exempted'; $wbpcb_reference_no = 'n/a';$wbpcb_ref_date = 'n/a';}


	$form['header'] 		= array(
			'#markup' 			=> t('	<div class="row"><div class="box-header with-border">
              						  	<h3 class="box-title">Application Preview</h3>
										</div><div class="box-body">
				<table class="table table-bordered custom-table-view">
				<tr>
   				<th width="40%">Parameters</th>
   				<th>Inputs</th>
				</tr>
				<tr><td colspan="2" class="sub-title">A. Factory Information</td></tr>
				<tr><td>(i) Name of the factory</td><td>'.$get_fa_cafa[0]->factory_name.'</td></tr>
				<tr><td>(ii) Previous name of the factory</td><td>'.$get_fa_cafa[0]->factory_previous_name.'</td></tr>
				<tr><td>(iii) PAN of the Business Establishment / Factory / Company</td><td>'.$get_fa_cafa[0]->factory_pan.'</td></tr>
				<tr><td>(iv) GSTIN Number</td><td>'.$get_fa_cafa[0]->gstin_no.'</td></tr>
				<tr><td>(v) Udyog Aadhaar No</td><td>'.$get_fa_cafa[0]->udyog_aadhaar.'</td></tr>
				<tr><td>(vi) Trade License No</td><td>'.$get_fa_cafa[0]->trade_license_no.'</td></tr>
				<tr><td>(vii) Energy Meter No</td><td>'.$get_fa_cafa[0]->enargy_no.'</td></tr>
				<tr><td>(viii) CIN No</td><td>'.$get_fa_cafa[0]->cin_no.'</td></tr>

				<tr><td colspan="2" class="sub-title">B. Location of the factory</td></tr>
				<tr><td>(i) Factory Zone</td><td>'.$get_fa_cafa[0]->zone_name.'</td></tr>
				<tr><td>(ii) Address</td><td>'.$factory_address.', '.$get_fa_cafa[0]->addrline.'</td></tr>
				<tr><td>(iii) Nearest Landmark</td><td>'.$get_fa_cafa[0]->nearest_landmark.'</td></tr>
				<tr><td>(iv) Estate Type</td><td>'.$final_estate_type.'</td></tr>
				
			    <tr><td>(v) Telephone No.</td><td>'.$get_fa_cafa[0]->comm_telephone.'</td></tr>
				<tr><td>(vi) Mobile No.</td><td>'.$get_fa_cafa[0]->comm_mobile.'</td></tr>
				<tr><td>(vii) Alternate Mobile No.</td><td>'.$get_fa_cafa[0]->comm_alt_mobile.'</td></tr>
				<tr><td>(viii) Fax No.</td><td>'.$get_fa_cafa[0]->comm_fax.'</td></tr>
				<tr><td>(ix) Email Id</td><td>'.$get_fa_cafa[0]->comm_email.'</td></tr>
		
				<tr><td colspan="2" class="sub-title">C. Address of the Registered office / Head office</td></tr>
				<tr><td>(i) Address</td><td>'.$headoffice_address.', '.$get_fa_cafa[0]->addrline_off.'</td></tr>

				<tr><td colspan="2" class="sub-title">D. Communication Address</td></tr>
				<tr><td>(i) Address</td><td>'.$communication_address.', '.$get_fa_cafa[0]->addrline_comm.'</td></tr>
				
				<tr><td colspan="2" class="sub-title">E. Details of Occupier</td></tr>
				<tr style="font-weight: bold;"><td>View Details List</td><td>'.$link_occuiper.'</td></tr>
				
				<tr><td colspan="2" class="sub-title">F. DETAILS OF OWNER/LAND LORD/LESSOR OF THE PREMISES OCCUPIED AS A FACTORY</td></tr>
				<tr style="font-weight: bold;"><td>Details of the Owner / Land Lord / Lessor of the premises</td><td>'.$link_owner.'</td></tr>
				
				<tr><td colspan="2" class="sub-title">G. PARTICULAR OF PLAN TO BE INSTALLED</td></tr>
				<tr><td>(i) Plant To be Installed</td><td>'.$get_fa_cafa[0]->plant_installed.'</td></tr>
				
				<tr><td colspan="2" class="sub-title">H. FACTORY IDENTIFICATION ACCORDING TO WBPCB</td></tr>
				<tr><td>(i) Categories of wbpcb</td><td>'.$consent.'</td></tr>
				<tr><td>(ii) Reference number of approval of arrangments</td><td>'.$wbpcb_reference_no.'</td></tr>
				<tr><td>(iii) Date of approval of arrangments</td><td>'.$wbpcb_ref_date.'</td></tr>				

				<tr><td colspan="2" class="sub-title">I. No. Of Workers</td></tr>
				<tr style="font-weight: bold;"><td>Worker List View</td><td>'.$link_worker.'</td></tr>'.$output.'</table></div></div>'),
		);

	if($plan_approve_status != 'F'){
		$form['serviceid_hidden'] = array(
				 '#type' 			=> 'hidden',
				 '#default_value' 	=> $serviceid
		);	
		$form['factorytype_hidden'] = array(
				 '#type' 			=> 'hidden',
				 '#default_value' 	=> $factorytype
		);	
		$form['applicationid_hidden'] = array(
				 '#type' 			=> 'hidden',
				 '#default_value' 	=> $applicationid
		);	
		$form['reference_no_hidden'] = array(
				 '#type' 			=> 'hidden',
				 '#default_value' 	=> encryption_decryption_fun('encrypt',$reference_no),
		);		  
		$form['identification_number_hidden'] = array(
				 '#type' 			=> 'hidden',
				 '#default_value' 	=> empty($identification_number)?'':$identification_number//encryption_decryption_fun('encrypt',$identification_number)
		);	   
		$form['plan_approve_status_hidden'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> encryption_decryption_fun('encrypt', $plan_approve_status)
		);
		$form['application_documents']['finalAgree'] 	= array(
					 '#prefix' 		=> '<div class="row"><div class="col-md-12 col-xs-12">',	
					 //'#suffix' 		=> '</div>',
					 '#type' 		=> 'checkbox',
					 '#title' 		=> ' I hereby declare that the particulars given above are true the best of my knowledge and belief.',
					 '#attributes'		=> array('id' => 'finalAgreeId','onchange' => 'return checkFinalAppCheckBox()'),
					 '#required' 		=> TRUE,
				);
		
		
		$form['back_link'] = array(
			
			'#markup' => l(t('<i class="fa fa-fw fa-chevron-left"></i> Back'), 'applicant/caf/cafb/'.$serviceid.'/'.$factorytype.'/'.$applicationid.'/'.$referenceno, array(
				'html' => TRUE,
				'attributes' => array(
					'class' => array(
						'btn btn-dark pull-left '
					)
				)
			))
		);
		
		$form['submit'] = array (
				  '#type' 			=> 'submit',
				  '#suffix' 		=> '</div>',
				  '#attributes' 	=> array('class' => array('btn btn-success pull-right')),
				  '#value' 			=> 'Save'										  
			   );
		
			$form['pdf_link'] = array(
				'#markup' => l(t('Print Draft Copy'), 'download-pdf-new-plan/'.$applicationid.'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.$serviceid.'/'.$factorytype.'/'.encryption_decryption_fun('encrypt',$plan_approve_status), array(
					'html' => TRUE,
					'attributes' => array(
						'class' => array(
							'btn btn-warning pull-left', 'style'=> 'margin-left: 10px'
						)
					)
				))
			);
	}    
		
		return $form; 
   }

function application_preview_submit($form, &$form_state){
	  global $user;
	  $uid = $user->uid;
	  
	   $val   					= 	$form_state['values'];
	  
	   $service_id 				= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']); 
	   $factorytype_id 			= 	encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
	   $plan_approve_status 	= 	encryption_decryption_fun('decrypt',$val['plan_approve_status_hidden']);
	   $application_id 			= 	encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	   $reference_no			=  	encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	   $identificationnumber 	=   $val['identification_number_hidden'];
	  
	  	if($plan_approve_status == 'ABk') { $planstatus = 'RS';}
		else { $planstatus = 'F';}
	  
	  //-----------Worker table update---------------------------
		$worker_status 	= 	array('worker_plan_approval_status' => $planstatus);
		$querywork 		 =	db_update('fa_worker_details');
		$querywork			->	fields($worker_status);
		$querywork		    ->	condition('application_id',$application_id,'=');
		$querywork		    ->	condition('service_id',$service_id,'=');
		$querywork			->	condition('factory_type',$factorytype_id,'=');
		$querywork			->	condition('application_reference_no',$reference_no,'=');
		$querywork			->	execute();
	  
	  //----------------Documents Update-------------------
		$doc_status 	= 	array('plan_approval_status' => $planstatus);
		$querydoc 		=	db_update('fa_caf_upload_doc');
		$querydoc		->	fields($doc_status);
		$querydoc		->	condition('app_id',$application_id,'=');
		$querydoc		->	condition('upload_documents_service_id',$service_id,'=');
		$querydoc	    ->	condition('upload_doc_factory_type_id',$factorytype_id,'=');
		$querydoc		->	condition('application_reference_no',$reference_no,'=');
		$querydoc		->	execute();
		
	  //----------------Occupier Details Update-------------------
		$occupr_status 	= 	array('worker_plan_approval_status' => $planstatus);
		$querydic 		=	db_update('fa_occupier_details');
		$querydic		->	fields($occupr_status);
		$querydic		->	condition('application_occupier_id',$application_id,'=');
		$querydic		->	condition('occupier_service_id',$service_id,'=');
		$querydic		->	condition('factory_type_id',$factorytype_id,'=');
		$querydic		->	condition('application_reference_no',$reference_no,'=');
		$querydic		->	execute();
		
	   $caf_update 		= 	array('plan_approve_status' => $planstatus);
	   $queryapp 		=	db_update('fa_cafa');
	   $queryapp		->	fields($caf_update);
	   $queryapp		->	condition('id',$application_id,'=');
	   $queryapp	    ->	execute();
	   
	   //----------------Remarks Table Insert -------------------
	
		//$cafa_remarks = array(
//		'app_id'   			 => $application_id,
//		'remark_by_uid' 	 => $uid,
//        //'remark_by_roleid' => ,
//		//'remark_by_name' 	 => ,
//		'sending_time' 		 => date('Y-m-d h:i:s'),
//		'app_reference_no' 	 => $reference_no,
//		'plan_status' 			 => $planstatus,
//		);	
//		db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();
	   
		if($plan_approve_status == 'ABk')
			{ drupal_set_message('Your application has been successfully Re-submited. Click on <b>Donwload Application Form</b> button to download your application');}
		else { drupal_set_message('Your application has been successfully saved. Click on <b>Donwload Application Form</b> button to download your application');}


		drupal_goto('applicant/application_upload/'.$val['serviceid_hidden'].'/'.$val['factorytype_hidden'].'/'.$val['applicationid_hidden'].'/'.$val['reference_no_hidden']) ;
 }
 
 /*function documents_master_data($service_id,$factory_type_id){
	$query_factory_documents 	=  db_select('fa_documents_master', 'documents');
	$query_factory_documents	-> fields('documents',array('id'));
	$query_factory_documents	-> condition('documents.document_service_id', $service_id, '=');
	$query_factory_documents	-> condition('documents.document_factory_id', $factory_type_id, '=');
	$query_factory_documents	-> condition('documents.id',array(19), 'NOT IN');
	$query_factory_documents	-> orderBy('documents.id', 'ASC');
	$result_factory_documents 	= $query_factory_documents->execute()->fetchAll(); 
	return $result_factory_documents;
}

function upload_document_data($application_id,$referance_number,$service_id,$factory_type_id){
	$query 	=  db_select('fa_caf_upload_doc', 'fcud')->distinct();
	$query 	-> fields('fcud', array('doc_id'));
	$query	-> condition('fcud.app_id', $application_id);
	$query	-> condition('fcud.application_reference_no', $referance_number);
	$query	-> condition('fcud.upload_documents_service_id', $service_id);
	$query	-> condition('fcud.upload_doc_factory_type_id', $factory_type_id);
	$query	-> condition('fcud.doc_id',array(19), 'NOT IN');
	$resultData = $query->execute()->fetchAll();
	return $resultData;
}*/

?>