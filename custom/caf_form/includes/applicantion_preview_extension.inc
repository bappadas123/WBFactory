<?php
function applicantion_preview_extension($form, &$form_state,$serviceid,$factorytype,$applicationid) {

	global $base_root,$base_path,$user,$_SESSION;
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factorytype);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$form = array();
	
	if(empty($application_id) || $application_id==0 || $application_id == ''){
		  drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the previous tab.</h5>'),'alert alert-danger alert-dismissible');
		  drupal_goto('applicant/caf_extn/plan_extension/'.$serviceid.'/'.$factory_type_id.'/'.$applicationid) ;
	}
		
	$get_fa_cafa           			= 	get_application_withid($application_id);
	$plan_approve_status      		= 	$get_fa_cafa[0]->plan_approve_status;
	$reference_no 					=   $get_fa_cafa[0]->reference_number;
	$identification_number			= 	$get_fa_cafa[0]->plan_approve_identification_number;

	if($plan_approve_status == 'F'){
		$pdf_link	= l('Download Application Form', 'download-pdf-new-plan/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_blank','class'=>array('button'))));	
		//$form['applicantion_documents']['markup_pdf'] = array (
//				  #type' 			=> 'markup',
//				  #markup' 		=> $pdf_link
//		 );
	}
	
	$getdata_factory_address =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address    = get_full_address('fa_cafa','sub-table',$get_fa_cafa[0]->id,$getdata_factory_address);
	
	$getdata_headoffice_address =  array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
	$headoffice_address = get_full_address('fa_cafa','sub-table',$get_fa_cafa[0]->id,$getdata_headoffice_address);

	$getdata_occupier_permanent_address =  array('district_oprmntadr','subdivision_oprmntadr','areatype_oprmntadr','block_oprmntadr','panchayat_oprmntadr','policestation_oprmntadr','pincodeoprmntadr','state_oprmntadr','postoffice_oprmntadr');
	$permanent_address  = get_full_address('fa_cafa','sub-table',$get_fa_cafa[0]->id,$getdata_occupier_permanent_address);
	
	$getdata_occupier_present_address =  array('district_oprsntadr','subdivision_oprsntadr','areatype_oprsntadr','block_oprsntadr','panchayat_oprsntadr','policestation_oprsntadr','pincodeoprsntadr','state_oprsntadr','postoffice_oprsntadr');
	$present_address    = get_full_address('fa_cafa','sub-table',$get_fa_cafa[0]->id,$getdata_occupier_present_address);
	
	$ocupier_present_address = !empty($present_address) ? $present_address.', '.$get_fa_cafa[0]->addrline_oprsntadr : $get_fa_cafa[0]->addrline_oprsntadr;
	$ocupier_permanent_address = !empty($permanent_address) ? $permanent_address.', '.$get_fa_cafa[0]->addrline_oprmntadr : $get_fa_cafa[0]->addrline_oprmntadr;

	if($get_fa_cafa[0]->occupier_nationality == 'Indian')
	{  
		$identification = 'Aadhaar No';
		$identification_no = $get_fa_cafa[0]->occupier_aadhaar;
	}
	else{
		$identification = 'Passport No';
		$identification_no = $get_fa_cafa[0]->occupier_passport;
	}
    $get_worker = get_worker_detials($application_id);
	$get_document_data = get_uploaded_document_data($service_id,$factory_type_id,$application_id,$reference_no);

$output .= '<tr><td colspan="2" class="sub-title">I. Plan Related Documents</td></tr>
				<tr><td><b> Document Name</b></td><td><b> List of Documents</b></td></tr>';
				if(!empty($get_document_data))
				{
					$i=1;
					foreach($get_document_data as $gdd){ 
					$output.='
					<tr>
						<td>'.$i.'. '.$gdd->file_name.'</td>
						<td>'.l('View', file_create_url(get_uploaded_document_url($gdd->fid)), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('button')))).'</td>
						
					</tr>';
					$i++;
					}
				} else {
					$output.='<tr><td colspan="2">No document Found</td></tr>';
				}
	//(Application Number:- '.$get_fa_cafa[0]->plan_approve_identification_number.')
	
	$classification_no = !empty($get_fa_cafa[0]->classification_no) ? $get_fa_cafa[0]->classification_no : $get_fa_cafa[0]->backlog_classification_no;	
	$factory_registrstion_no = !empty($get_fa_cafa[0]->factory_registrstion_no) ? $get_fa_cafa[0]->factory_registrstion_no : $get_fa_cafa[0]->backlog_registration_no;	
	$factory_license_no = !empty($get_fa_cafa[0]->factory_license_no) ? $get_fa_cafa[0]->factory_license_no : $get_fa_cafa[0]->backlog_license_number;	
	$registration_date = !empty($get_fa_cafa[0]->registration_date) ? $get_fa_cafa[0]->registration_date : $get_fa_cafa[0]->backlog_registration_date;	
			
	   
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
				<tr><td>(i) Previous name of the factory</td><td>'.$get_fa_cafa[0]->factory_previous_name.'</td></tr>
				<tr><td>(ii) PAN of the Business Establishment / Factory / Company</td><td>'.$get_fa_cafa[0]->factory_pan.'</td></tr>

				<tr><td colspan="2" class="sub-title">B. Location of the factory</td></tr>
				<tr><td>(i) Factory Zone</td><td>'.$get_fa_cafa[0]->zone_name.'<br/><span style="color:#319A31;">('.$get_fa_cafa[0]->zone_details.')</span></td></tr>
				<tr><td>(ii) Address</td><td>'.$factory_address.', '.$get_fa_cafa[0]->addrline.'</td></tr>
				
				<tr><td colspan="2" class="sub-title">C. Address of the Registered office / Head office<br/><font color="#FF0000" size="2">(N.B:- This address will be treated as communication address as per Section 7 of Factories Act, 1948)</font></td></tr>
				<tr><td>(i) Address</td><td>'.$headoffice_address.', '.$get_fa_cafa[0]->addrline_off.'</td></tr>
				<tr><td>(ii) Telephone No.</td><td>'.$get_fa_cafa[0]->comm_telephone.'</td></tr>
				<tr><td>(iii) Mobile No.</td><td>'.$get_fa_cafa[0]->comm_mobile.'</td></tr>
				<tr><td>(iv) Fax No.</td><td>'.$get_fa_cafa[0]->comm_fax.'</td></tr>
				<tr><td>(iv) Email Id</td><td>'.$get_fa_cafa[0]->comm_email.'</td></tr>
				
				<tr><td colspan="2" class="sub-title">D. Details of Occupier</td></tr>
				<tr><td>(i) Occupier Type </td><td>'.$get_fa_cafa[0]->occupier_type.'</td></tr>
				<tr><td>(ii) Name</td><td>'.$get_fa_cafa[0]->occupier_name.'</td></tr>
				<tr><td>(iii) Age</td><td>'.$get_fa_cafa[0]->occupier_age.'</td></tr>
				<tr><td>(iv) Father\'s / Husband\'s name</td><td>'.$get_fa_cafa[0]->occupier_gurdian_name.'</td></tr>
				<tr><td>(v) Telephone No. </td><td>'.$get_fa_cafa[0]->occupier_telephone.'</td></tr>
				<tr><td>(vi) Mobile No.</td><td>'.$get_fa_cafa[0]->occupier_mobile.'</td></tr>
				<tr><td>(vii) Email id </td><td>'.$get_fa_cafa[0]->occupier_email_id.'</td></tr>
				<tr><td>(viii) Fax No. </td><td>'.$get_fa_cafa[0]->occupier_fax_no.'</td></tr>
				
				<tr><td colspan="2" class="sub-title">D(i). Occupier Permanent Address</td></tr>
				<tr><td>(i) Nationality </td><td>'.$get_fa_cafa[0]->occupier_nationality.'</td></tr>
				<tr><td>(ii) '.$identification.'</td><td>'.$identification_no.'</td></tr>
				<tr><td>(iii) Address</td><td>'.$ocupier_permanent_address.'</td></tr>

				<tr><td colspan="2" class="sub-title">D(ii). Occupier Present Address</td></tr>
				<tr><td>(i) Address</td><td>'.$ocupier_present_address.'</td></tr>

				<tr><td colspan="2" class="sub-title">E. DETAILS OF OWNER/LAND LORD/LESSOR OF THE PREMISES OCCUPIED AS A FACTORY</td></tr>
				<tr><td>(i) Name of the Owner / Land Lord / Lessor of the premises</td><td>'.$get_fa_cafa[0]->owner_name.'</td></tr>	
				<tr><td>(ii) Address</td><td>'.$get_fa_cafa[0]->addrline_premises.'</td></tr>
				
				<tr><td colspan="2" class="sub-title">F. PARTICULAR OF PLAN TO BE INSTALLED</td></tr>
				<tr><td>(i) Plant To be Installed</td><td>'.$get_fa_cafa[0]->plant_installed.'</td></tr>

				<tr><td colspan="2" class="sub-title">G. DETAILS OF REGISTERED FACTORY</td></tr>
				<tr><td>(i) Classification No.</td><td>'.$classification_no.'</td></tr>
				<tr><td>(ii) Registration No.</td><td>'.$factory_registrstion_no.'</td></tr>
				<tr><td>(iii) Licence No.</td><td>'.$factory_license_no.'</td></tr>
				<tr><td>(iv) Date of Issue of Licence </td><td>'.$registration_date.'</td></tr>

				<tr><td colspan="2" class="sub-title">H. No. Of Workers</td></tr>
				<tr><td>(i) Men</td><td>'.$get_worker[0]->worker_men.'</td></tr>
				<tr><td>(ii) Women</td><td>'.$get_worker[0]->worker_women.'</td></tr>
				<tr><td>(iii) Adolescents (over 15 but under 18 years of age) Male</td><td>'.$get_worker[0]->adolescents_male.'</td></tr>
				<tr><td>(iv) Female</td><td>'.$get_worker[0]->adolescents_female.'</td></tr>
				<tr><td>(v) Children (over 14 but under 15 years of age) Male</td><td>'.$get_worker[0]->children_male.'</td></tr>
				<tr><td>(vi) Female</td><td>'.$get_worker[0]->children_female.	'</td></tr>'.$output.'</table></div></div>'),
				
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
				 '#default_value' 	=> empty($identification_number)?'':encryption_decryption_fun('encrypt',$identification_number)
		);	   
		$form['plan_approve_status_hidden'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> encryption_decryption_fun('encrypt', $plan_approve_status)
		);
		$form['applicantion_documents']['finalAgree'] 	= array(
					 '#prefix' 		=> '<div class="row"><div class="col-md-12 col-xs-12">',	
					 //'#suffix' 		=> '</div>',
					 '#type' 		=> 'checkbox',
					 '#title' 		=> ' I hereby declare that the particulars given above are true the best of my knowledge and belief.',
					 '#attributes'		=> array('id' => 'finalAgreeId','onchange' => 'return checkFinalAppCheckBox()'),
					 '#required' 		=> TRUE,
				);
		$form['submit'] = array (
				  '#type' 			=> 'submit',
					 '#suffix' 		=> '</div></div>',
				  '#attributes' 	=> array('class' => array('btn btn-dark')),
				  '#value' 			=> 'Save & Continue'										  
			   );
		
		}    
		
		return $form; 
   }

function applicantion_preview_extension_submit($form, &$form_state){
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
		else { drupal_set_message('Your application has been successfully submited. Click on <b>Donwload Application Form</b> button to download your application');}


		drupal_goto('applicant/application_upload_extension/'.$val['serviceid_hidden'].'/'.$val['factorytype_hidden'].'/'.$val['applicationid_hidden'].'/'.$val['reference_no_hidden']) ;
		
 }

?>