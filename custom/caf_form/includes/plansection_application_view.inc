<?php
function plansection_application_view($form, &$form_state,$serviceid ,$factorytype,$applicationid ,$referenceid){
	
	global $base_root,$base_path,$user,$_SESSION;
	
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factorytype);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$reference_no 	    = encryption_decryption_fun('decrypt',$referenceid);
	$form = array();
	
	$get_fa_cafa           			= 	get_application_withid($application_id);
	$plan_approve_status      		= 	$get_fa_cafa[0]->plan_approve_status;
	$reference_no 					=   $get_fa_cafa[0]->reference_number;
	$identification_number			= 	$get_fa_cafa[0]->plan_approve_identification_number;

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

	$output .= '<tr><td colspan="2" style="text-transform: uppercase;">H. Plan Related Documents</td></tr>
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

		if($service_id == '5')
		{
			$previous_factory_name_and_pan = '<tr><td>(ii) Previous Factory Name</td><td>'.$get_fa_cafa[0]->factory_previous_name.'</td></tr>
			<tr><td>(iii) PAN of the Business Establishment / Factory / Company</td><td>'.$get_fa_cafa[0]->factory_pan.'</td></tr>';
		} else {			
			$previous_factory_name_and_pan = '<tr><td>(ii) PAN of the Business Establishment / Factory / Company</td><td>'.$get_fa_cafa[0]->factory_pan.'</td></tr>';
		}

		$form['header'] 		= array(
			'#markup' 			=> t('<div class="cus-page-outer-view"><div class="content">
              						<center class="verify-top-title-pad"><h3>Application Preview</h3></center>
									<div class="box-body">
									<table cellpadding="0" cellspacing="0" border="0" width="100%" class="table no-margin custom-table-view-dashboard">
									<tr><th width="40%">Parameters</th>
   									<th>Inputs</th></tr>
									<tr><td colspan="2" style="text-transform: uppercase;">A. Factory Information</td></tr>
				<tr><td>(i) Name of the factory</td><td>'.$get_fa_cafa[0]->factory_name.'</td></tr>'.$previous_factory_name_and_pan.'
				
				<tr><td colspan="2" style="text-transform: uppercase;">B. Location of the factory</td></tr>
				<tr><td>(i) Factory Zone</td><td>'.$get_fa_cafa[0]->zone_name.'<br/><span style="color:#319A31;">('.$get_fa_cafa[0]->zone_details.')</span></td></tr>
				<tr><td>(ii) Address</td><td>'.$factory_address.', '.$get_fa_cafa[0]->addrline.'</td></tr>
				
				<tr><td colspan="2">C. Address of the Registered office / Head office<br/><font color="#FF0000">(N.B:-This address will be treated as communication address as per Section 7 of Factories Act,1948 )</font> </td></tr>
				<tr><td>(i) Address</td><td>'.$headoffice_address.', '.$get_fa_cafa[0]->addrline_off.'</td></tr>
				<tr><td>(ii) Telephone No</td><td>'.$get_fa_cafa[0]->comm_telephone.'</td></tr>
				<tr><td>(iii) Mobile No</td><td>'.$get_fa_cafa[0]->comm_mobile.'</td></tr>
				<tr><td>(iv) Fax No</td><td>'.$get_fa_cafa[0]->comm_fax.'</td></tr>
				<tr><td>(iv) Email Id</td><td>'.$get_fa_cafa[0]->comm_email.'</td></tr>
				
				<tr><td colspan="2" style="text-transform: uppercase;">D. Details of Occupier</td></tr>
				<tr><td>(i) Occupier Type </td><td>'.$get_fa_cafa[0]->occupier_type.'</td></tr>
				<tr><td>(ii) Name</td><td>'.$get_fa_cafa[0]->occupier_name.'</td></tr>
				<tr><td>(iii) Age</td><td>'.$get_fa_cafa[0]->occupier_age.'</td></tr>
				<tr><td>(iv) Father\'s / Husband\'s name</td><td>'.$get_fa_cafa[0]->occupier_gurdian_name.'</td></tr>
				<tr><td>(v) Telephone Number </td><td>'.$get_fa_cafa[0]->occupier_telephone.'</td></tr>
				<tr><td>(vi) Mobile Number</td><td>'.$get_fa_cafa[0]->occupier_mobile.'</td></tr>
				<tr><td>(vii) Email id </td><td>'.$get_fa_cafa[0]->occupier_email_id.'</td></tr>
				<tr><td>(viii) Fax No. </td><td>'.$get_fa_cafa[0]->occupier_fax_no.'</td></tr>
				
				<tr><td colspan="2" style="text-transform: uppercase;">D(i). Occupier Permanent Address</td></tr>
				<tr><td>(i) Nationality </td><td>'.$get_fa_cafa[0]->occupier_nationality.'</td></tr>
				<tr><td>(ii) '.$identification.'</td><td>'.$identification_no.'</td></tr>
				<tr><td>(iii) Address</td><td>'.$ocupier_permanent_address.'</td></tr>

				<tr><td colspan="2" style="text-transform: uppercase;">D(ii). Occupier Present Address</td></tr>
				<tr><td>(i) Address</td><td>'.$ocupier_present_address.'</td></tr>

				<tr><td colspan="2" style="text-transform: uppercase;">E. DETAILS OF OWNER OF THE PREMISES OCCUPIED AS A FACTORY</td></tr>
				<tr><td>(i) Name of the Owner / Land Lord / Lessor of the premises</td><td>'.$get_fa_cafa[0]->owner_name.'</td></tr>	
				<tr><td>(ii) Address</td><td>'.$get_fa_cafa[0]->addrline_premises.'</td></tr>
				
				<tr><td colspan="2" style="text-transform: uppercase;">F. PARTICULAR OF PLAN TO BE INSTALLED</td></tr>
				<tr><td>(i) Plant To be Installed</td><td>'.$get_fa_cafa[0]->plant_installed.'</td></tr>
				<tr><td colspan="2" style="text-transform: uppercase;">G. No. Of Workers</td></tr>
				<tr><td>(i) Men</td><td>'.$get_worker[0]->worker_men.'</td></tr>
				<tr><td>(ii) Women</td><td>'.$get_worker[0]->worker_women.'</td></tr>
				<tr><td>(iii) Adolescents (over 15 but under 18 years of age) Male</td><td>'.$get_worker[0]->adolescents_male.'</td></tr>
				<tr><td>(iv) Female</td><td>'.$get_worker[0]->adolescents_female.'</td></tr>
				<tr><td>(v) Children (over 14 but under 15 years of age) Male</td><td>'.$get_worker[0]->children_male.'</td></tr>
				<tr><td>(vi) Female</td><td>'.$get_worker[0]->children_female.	'</td></tr>'.$output.'</table></div></div>'),
		);

	if($plan_approve_status == 'U'){
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
					 '#prefix' 		=> '</div></div><div class="col-md-12 col-xs-12">',	
					 '#suffix' => '</div>',
					 '#type' 		=> 'checkbox',
					 '#title' => ' I hereby declare that the particulars given above are true the best of my knowledge and belief.',
					 '#attributes'		=> array('id' => 'finalAgreeId','onchange' => 'return checkFinalAppCheckBox()'),
					 '#required' 		=> TRUE,
				);
		$form['submit'] = array (
				  '#type' 			=> 'submit',
				  '#attributes' 	=> array('class' => array('btn btn-dark')),
				  '#value' 			=> 'Save & Continue'										  
			   );
		
		}    

    return $form;
        
   }
?>