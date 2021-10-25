<?php
function application_view_extn($serviceid ,$factorytype,$applicationid ,$referenceno){	
	
	global $base_root,$base_path,$user,$_SESSION;
	
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factorytype);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$reference_no 		= encryption_decryption_fun('decrypt',$referenceno);
	$uploaded_pdf_link  = '';
	$form = array();
	
   	$get_fa_cafa           			= 	get_application_withid($application_id); //get_fa_cafa($application_id);
	$get_fa_occupier           		= 	get_all_occupier_data($application_id,$service_id,$factory_type_id,$reference_no); //echo "<pre>";print_r($get_fa_occupier);exit;
	
	$plan_approve_status      		= 	$get_fa_cafa[0]->plan_approve_status;
	$identification_number			= 	$get_fa_cafa[0]->plan_approve_identification_number;

	if(($get_fa_cafa[0]->plan_approve_status == 'F') || ($get_fa_cafa[0]->plan_approve_status == 'RS'))
	{
		$uploaded_pdf_link	= l('<i class="fa fa-download text-blue" aria-hidden="true"></i> Download Application Form', 'download-pdf-new-plan/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$plan_approve_status), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_blank','class'=>array(''))));	
	}else
	{		 
		//$get_uploaded_doc = get_uploaded_document_url($get_fa_cafa[0]->uploaded_pdf);
		
		$get_uploaded_doc = get_caf_upload_doc_details($application_id, $service_id, 'CAF', $factory_type_id, $reference_no);		
									
		$uploaded_pdf_link1 = l('<i class="fa fa-download" aria-hidden="true"></i> View Uploaded Application with DSC ','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $get_uploaded_doc->id).'/'.encryption_decryption_fun('encrypt', 'CAF').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
	
		
		$uploaded_pdf_link2	= l('<i class="fa fa-download text-blue" aria-hidden="true"></i> View Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_blank','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	
		
		$uploaded_pdf_link = $uploaded_pdf_link2.$uploaded_pdf_link1;
	
	$application_no = 'Application No. :: '.$get_fa_cafa[0]->plan_approve_identification_number;
	}
		
	$form['header'] = array(
		'#markup' 			=> t('<div class="content"><div class="sky-form"><h3 style="text-align: center;"><b>Application for Approval of Plan</b><p style="text-align: right;">'.$uploaded_pdf_link.'</p><p style="font-size:15px;" class="text-green">'.$application_no.'</p></h3>'),
	);
	
	$getdata_factory_address =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address    = get_full_address('fa_cafa','sub-table',$get_fa_cafa[0]->id,$getdata_factory_address);
	
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

	$estate_type 	       = get_estate_type($get_fa_cafa[0]->estate_type);
	$final_estate_type     = !empty($estate_type) ? $estate_type[0]->estate_name : $get_fa_cafa[0]->estate_type_name;
 
 	//die($get_fa_cafa[0]->tm_appliction_id);
	
	if($get_fa_cafa[0]->tm_migrated_flag == 'N')
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
	//$get_document_data         = get_caf_upload_doc_all($service_id,$application_id,$factory_type_id,$reference_no);
	//$get_document_data_caf	   = get_caf_upload_doc_details($application_id, $service_id, 'CAF', $factory_type_id, $reference_no);	

    if($get_fa_occupier[0]->country_oprmntadr == 99) 
	  {	   
	  	$Occupier_Permanent_Address = '<tr><td>(ii) Aadhaar No</td><td>'.$get_fa_occupier[0]->aadhaar_oprmntadr.'</td></tr>
									  <tr><td>(iii) Address </td><td>'.$ocupier_permanent_address.'</td></tr>
									  <tr><td>(iv) Street Name</td><td>'.$get_fa_occupier[0]->street_name_oprmntadr.'</td></tr>
									  <tr><td>(v) House No.</td><td>'.$get_fa_occupier[0]->house_no_oprmntadr.'</td></tr>';
	  }
	  else{	  	
	  	$Occupier_Permanent_Address = '<tr><td>(ii) Passport No</td><td>'.$get_fa_occupier[0]->passport_oprmntadr.' <b>(DOI):</b>'.$get_fa_occupier[0]->passport_date_of_issue_oprmntadr.' <b>(DOE):</b>'.$get_fa_occupier[0]->passport_date_of_expiry_oprmntadr.'</td></tr>
									  <tr><td>(iii) Street Name</td><td>'.$get_fa_occupier[0]->street_name_oprmntadr.'</td></tr>
									  <tr><td>(iv) House No.</td><td>'.$get_fa_occupier[0]->house_no_oprmntadr.'</td></tr>
									  <tr><td>(v) Police Station</td><td>'.$get_fa_occupier[0]->police_station_oprmntadr.'</td></tr>';
	  }

	  if($get_fa_occupier[0]->country_oprsntadr == 99) 
	  {	  
	  	$Occupier_Present_Address = '<tr><td>(ii) Aadhaar No</td><td>'.$get_fa_occupier[0]->aadhaar_oprsntadr.'</td></tr>
								     <tr><td>(iii) Address</td><td>'.$ocupier_present_address.'</td></tr>
									 <tr><td>(iv) Street Name</td><td>'.$get_fa_occupier[0]->street_name_oprsntadr.'</td></tr>
									 <tr><td>(v) House No.</td><td>'.$get_fa_occupier[0]->house_no_oprsntadr.'</td></tr>';
	  }
	  else{	  	
	  	$Occupier_Present_Address = '<tr><td>(ii) Passport No</td><td>'.$get_fa_occupier[0]->passport_oprsntadr.' <b>(DOI):</b>'.$get_fa_occupier[0]->passport_date_of_issue_oprsntadr.' <b>(DOE):</b>'.$get_fa_occupier[0]->passport_date_of_expiry_oprsntadr.'</td></tr>
									  <tr><td>(iii) Street Name</td><td>'.$get_fa_occupier[0]->street_name_oprsntadr.'</td></tr>
									  <tr><td>(iv) House No.</td><td>'.$get_fa_occupier[0]->house_no_oprsntadr.'</td></tr>
									  <tr><td>(v) Police Station</td><td>'.$get_fa_occupier[0]->police_station_oprsntadr.'</td></tr>';
	  }

	  /*if($get_fa_cafa[0]->country_premises == 99) 
	  {	  
	  	$Owner_Address = '<tr><td>(iii) Aadhaar No</td><td>'.$get_fa_cafa[0]->aadhaar_premises.'</td></tr>
						  <tr><td>(iv) Address</td><td>'.$owner_address.'</td></tr>
						  <tr><td>(v) Street Name</td><td>'.$get_fa_cafa[0]->street_name_premises.'</td></tr>
						  <tr><td>(vi) House No.</td><td>'.$get_fa_cafa[0]->house_no_premises.'</td></tr>';
	  }
	  else{	  	
	  	$Owner_Address = '<tr><td>(iii) Passport No</td><td>'.$get_fa_cafa[0]->passport_premises.' <b>(DOI):</b>'.$get_fa_cafa[0]->passport_date_of_issue_premises.' <b>(DOE):</b>'.$get_fa_cafa[0]->passport_date_of_expiry_premises.'</td></tr>
						  <tr><td>(iv) Street Name</td><td>'.$get_fa_cafa[0]->street_name_premises.'</td></tr>
						  <tr><td>(v) House No.</td><td>'.$get_fa_cafa[0]->house_no_premises.'</td></tr>
						  <tr><td>(vi) Police Station</td><td>'.$get_fa_cafa[0]->police_station_premises.'</td></tr>';
	  }*/

		ctools_include('ajax');
		ctools_include('modal');
		ctools_modal_add_js();	
		 
	 $owner_details=$base_root.$base_path.'view-owner-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
	 $link_owner =ctools_modal_text_button(t('View Owner Details'), $owner_details ,t('View Details)')) ;

	$occupier_details=$base_root.$base_path.'view-occuiper-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
	$link_occuiper =ctools_modal_text_button(t('View Occupier(s)'), $occupier_details ,t('View Details)')) ;	


	$worker_link=$base_root.$base_path.'view-worker-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
	$link_worker =ctools_modal_text_button(t('View Workers'), $worker_link ,t('View Details)')) ;

	$documents_details=$base_root.$base_path.'view-documents-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
	$link_documents =ctools_modal_text_button(t('View Documents list'), $documents_details ,t('View Details)')) ;


 	$output .='<div class="row"><div class="box box-info"><div class="box-header with-border">
              <div class="col-lg-12 col-md-12 col-sm-12"><h3 class="box-title pull-left">Application Preview	(Application Number:- '.$get_fa_cafa[0]->plan_approve_identification_number.')</h3>
              <p class="pull-right" style="text-align:right;">'.$uploaded_pdf_link.'</p>
            </div></div>
			<div class="box-body"><div class="col-lg-12 col-md-12 col-sm-12">
			<table class="table table-bordered custom-table-view"> <tr>
   								<th width="40%">Parameters</th>
   								<th>Inputs</th>
								</tr>';

	$output .='<tr><td colspan="2" class="sub-title">A. Factory Information</td></tr>
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
				<tr><td>(i) Plant To be Installed</td><td>'.$get_fa_cafa[0]->plant_installed.'</td></tr>';

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


	 $output .='<tr><td colspan="2" class="sub-title">H. FACTORY IDENTIFICATION ACCORDING TO WBPCB</td></tr>
				<tr><td>(i) Categories of wbpcb</td><td>'.$consent.'</td></tr>
				<tr><td>(ii) Reference number of approval of arrangments</td><td>'.$wbpcb_reference_no.'</td></tr>
				<tr><td>(iii) Date of approval of arrangments</td><td>'.$wbpcb_ref_date.'</td></tr>
	 			
				<tr><td colspan="2" class="sub-title">I. No. Of Workers (Permanent)</td></tr>
				<tr style="font-weight: bold;"><td>Worker List View</td><td>'.$link_worker.'</td></tr>';

	$output .= '<tr><td colspan="2" class="sub-title">J. Plan Related Documents</td></tr>
				<tr style="font-weight: bold;"><td> Document List View</td><td>'.$link_documents.'</td></tr>';
				
	$output .= '</table></div></div></div></div>';
	return $output;

 }