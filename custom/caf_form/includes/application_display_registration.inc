<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function application_display_registration($serviceid, $factory_type_id,$applicationid,$referenceid){
	global $base_root,$base_path,$base_url,$user;
	 $service_id 		= encryption_decryption_fun('decrypt',$serviceid);
 	$factory_typeid 	= encryption_decryption_fun('decrypt',$factory_type_id);
	  $application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	  $reference_number 	= encryption_decryption_fun('decrypt',$referenceid);



	$output ="";
	 $resultData 	= get_uploaded_document_data($service_id,$factory_typeid,$application_id,$reference_number);
		//  print_r($resultData);die;

	$get_all_data 				=  get_fa_cafa($application_id);
	$previous_name				= !empty($get_all_data['factory_previous_name'])?$get_all_data['factory_previous_name']:'NA';
	$renewal_dim_appoved		= $get_all_data['renewal_dim_appoved'];
	
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
		$plan_approval_date = date('dS M Y', strtotime($get_all_data['plan_approval_date']));
	}
	

	$plan_approval_no =  !empty($plan_approval_no)?$plan_approval_no:'NA';
	$gstin			  =	 !empty($get_all_data['gstin_no'])?$get_all_data['gstin_no']:'NA';

	
	$getdata_factory_location	=  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address_location 	= $get_all_data['addrline'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_factory_location).'<br/>Mouza Name:'.$get_all_data['mouza_name'].'<br/>JL No:'.$get_all_data['jl_no'];
	
	$getdata_headoffice_address =  array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
	$headoffice_address 		= $get_all_data['addrline_off'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_headoffice_address);
	
	$getdata_communication_address = array('district_comm','subdivision_comm','areatype_comm','block_comm','panchayat_comm','policestation_comm','pincodecomm','state_comm','postoffice_comm');
	$communication_address 		= $get_all_data['addrline_comm'].',
		<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_communication_address);
	
		
	$owner_address_details 	= !empty($get_all_data['addrline_premises'])?$get_all_data['addrline_premises'].',':'';
	 $owner_address_details	.= !empty($get_all_data['country_premises'])?country_name($get_all_data['country_premises']):'<br/>';
		
	$getdata_owner_address 		=  array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
	$owner_address 				=	$owner_address_details.'<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_owner_address);
	$passport_details = !empty($get_all_data['passport_premises'])?'Passport No-'.$get_all_data['passport_premises'].',<br/>Passport Issue Date-'.$get_all_data['passport_date_of_issue_premises'].',<br/>Passport Expiry date-'.$get_all_data['passport_date_of_expiry_premises']:'';
	
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

		$amaned_link=$base_root.$base_path.'view-amend_power_worker/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_amend=ctools_modal_text_button(t('Amendment Notice'), $amaned_link ,t('Amendment Notice)')) ;
		
		$occupier_details=$base_root.$base_path.'view-occuiper-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_occuiper=ctools_modal_text_button(t('View Occupier(s)'), $occupier_details ,t('View Details)')) ;	
		
		$director_details=$base_root.$base_path.'view-director-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_director=ctools_modal_text_button(t('View Director(s)'), $director_details ,t('View Details)')) ;	
		$owner_details=$base_root.$base_path.'view-owner-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_owner =ctools_modal_text_button(t('View owner Details'), $owner_details ,t('View Details)')) ;
		
		//$manufacturing_details=$base_root.$base_path.'view-manufacturing-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		//$link_manufacturing=ctools_modal_text_button(t('View Manufacturing Process(s)'), $manufacturing_details ,t('View Details)')) ;	
		
		$documents_details=$base_root.$base_path.'view-documents-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_documents=ctools_modal_text_button(t('View Documents list'), $documents_details ,t('View Details)')) ;
		
		
		
		$manager_details=$base_root.$base_path.'view-manager-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_manager=ctools_modal_text_button(t('View Manager(s)'), $manager_details ,t('View Details)')) ;
		
		//$power_details=$base_root.$base_path.'view-power-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 
		
		//$link_power=ctools_modal_text_button(t('View Power Details'), $power_details ,t('View Details)')) ;
				
		$factory_zone_date = get_factory_zone_name($get_all_data['factory_zone']);
		$udyog_aadhaar 	   = !empty($get_all_data['udyog_aadhaar'])?$get_all_data['udyog_aadhaar']:'NA';
		
		if(!empty($get_all_data['enargy_no'])){ $enargy_no = $get_all_data['enargy_no']; }else{$enargy_no =  'NA';}
		if(!empty($get_all_data['cin_no'])){ $cin_no = $get_all_data['cin_no']; }else{$cin_no =  'NA';}
		if(!empty($get_all_data['trade_license_no'])){ $trade_no = $get_all_data['trade_license_no']; }else{$trade_no =  'NA';}	
		$comm_fax = !empty($get_all_data['comm_fax'])?$get_all_data['comm_fax']:'NA';
		$owner_name	=!empty($get_all_data['owner_name'])?$get_all_data['owner_name'].' '.$get_all_data['owner_mname'].' '.$get_all_data['owner_lname']:'NA';
		
			
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
				$wbpcb_reference_no = 'NA'; 
				$wbpcb_ref_date = 'NA';
				$file = $get_all_data['wbpcb_intimation_letter'];
				$file_url =	'<a href='.$base_path.'document-list/view-appliction-form/'.encryption_decryption_fun('encrypt', $service_id).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt', $factory_typeid).'/'.encryption_decryption_fun('encrypt', $reference_number).'/'.encryption_decryption_fun('encrypt','INT').' target= "_BLANK" onclick = "popIt(this.href);return false;">Intimation Letter</a>';
				}
		if($get_all_data['wbpcb_category_name']==5){$consent ='Exempted'; $wbpcb_reference_no = 'NA';$wbpcb_ref_date = 'NA';}
		if(!empty($get_all_data['factory_reg_identification_number'])){
			$identification_number = 'Application Number:-'.$get_all_data['factory_reg_identification_number'].'';
			}
		$wbpcb_reference_no = !empty($wbpcb_reference_no)?$wbpcb_reference_no:'NA';
		$wbpcb_ref_date = !empty($wbpcb_ref_date)?$wbpcb_ref_date:'NA';
		$details = $consent.'<br>WBPCB referance no. = '.$wbpcb_reference_no.'<br>WBPCB referance date = '.$wbpcb_ref_date.'<br>'.$file_url;
		
		
			
			/****** ADDED BY SUBHAMAY ******/
		if($get_all_data['tm_migrated_flag']=='N'||$get_all_data['tm_migrated_flag']=='S')
		{
			        
			$application_from = l('Application Form', 'document-list/view-appliction-form/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$factory_typeid).'/'.encryption_decryption_fun('encrypt',$reference_number).'/'.encryption_decryption_fun('encrypt','CAF'), array('html' => TRUE,'attributes'=>array('title' => 'Application form', 'target' => '_BLANK','class'=>array(''))));
		}
		else
		{
			/* Added by subhamay*/
		$caf_doc_details=$base_root.$base_path.'view-documents-caf/nojs/'.$application_id.'/'.$reference_number.'/'.$get_all_data['tm_appliction_id']; 	
		$link_caf=ctools_modal_text_button(t('View CAF'), $caf_doc_details ,t('View Details)')) ;
		/**** ended by subhamay ******/
		    $application_from = $link_caf;
		}
		/****** ENDED BY SUBHAMAY ******/
		if($plan_approval_no != 'NA'){
			$plan_details = $plan_approval_no.' dated on '.$plan_approval_date;
		}else{
			$plan_details = 'Not Avaliable';
		}
		
		$reg_no  = !empty($get_all_data['factory_registrstion_no'])?$get_all_data['factory_registrstion_no']:(!empty($get_all_data['backlog_registration_no'])?$get_all_data['backlog_registration_no']:'NA');
	$registration_date  = !empty($get_all_data['registration_date'])?date('dS M Y', strtotime($get_all_data['registration_date'])):(!empty($get_all_data['backlog_registration_date'])?date('dS M Y', strtotime($get_all_data['backlog_registration_date'])):'NA');
	if($reg_no!= 'NA'){
		
		$reg_details = $reg_no .' ,dated on '.$registration_date;
	}else{
		$reg_details ='NA' ;
	}
		
	$license_number  = !empty($get_all_data['factory_license_no'])?$get_all_data['factory_license_no']:(!empty($get_all_data['backlog_license_number'])?$get_all_data['backlog_license_number']:'NA');
	$valid_upto  = !empty($get_all_data['license_valid_upto'])?date('dS M Y', strtotime($get_all_data['license_valid_upto'])):'NA';
	$license_date  = !empty($get_all_data['license_date'])?date('dS M Y', strtotime($get_all_data['license_date'])):!empty($get_all_data['backlog_license_date'])?date('dS M Y', strtotime($get_all_data['backlog_license_date'])):'NA';

	if($license_number!= 'NA'){
		
		$license_details = $license_number .' ,dated on '.$license_date.' and validup to date '.$valid_upto;
	}else{
		$license_details ='NA' ;
	}	
	$period_for_application = !empty($get_all_data['period_for_renewal'])?$get_all_data['period_for_renewal']:$get_all_data['period_for_application'];
	$application_status = $get_all_data['application_status'];
	
	if(!empty($identification_number)){
		$declration=$identification_number.'.<br/>(All inputs are provided by YOU)' ;
	}else{
		$declration="Your application is successfully saved.<br/>
Pay Application fees is the second step in completing your application process.<br/>
Complete this process by paying the application fees through Grips from our portal(

Please ignore who paid the fees)<br/>

Once payment is confirmed you can get an option in your dashboard.<br/>
 Once completed this step will be ready for services received from the  <b>DIRECTORATE OF FACTORIES</b> .<br/>N.B.:- Externally the payment process is not a grant.";
	}
	
	
		
	if($service_id==2){
		$apply_service = "Apply for Registration and grant of License";
	}if($service_id==3){
		$apply_service = "Apply for Renewal for the License";
	}if($service_id==8 || $service_id==9){
		$apply_service = "Apply for Amendement for the License";
	}
	
	$output .='<div class="row"><div class="box box-info"><div class="box-header with-border">
              	<h2>'.$apply_service.'</h2><h2 class="box-title"><b>Application Preview</b></h2><br/><h3>'.$declration.'
				</h3>
              
            	</div><div class = "box-body">
				<table class="table table-bordered"> <tr>
   								<th>Parameters</th>
   								<th>Inputs</th>
								</tr>';
	$output .='<tr><td colspan="2">A.Factory Information</td></tr>
				<tr><td>(i). Name of the factory</td><td>'.$get_all_data['factory_name'].'</td></tr>
				<tr><td>(ii). Ownership Type</td><td>'.$ownership_type.'</td></tr>
				<tr><td>(iii). PAN of the Business Establishment / Factory / Company </td><td>'.$get_all_data['factory_pan'].'</td></tr>
				<tr><td>(iv). Plan Approval number and Date </td><td>'.$plan_details.'</td></tr>
				<tr><td>(v). GSTIN No. </td><td>'.$get_all_data['gstin_no'].'</td></tr>
				<tr><td>(vi). Udyog Aadhaar No.</td><td>'.$get_all_data['udyog_aadhaar'].'</td></tr>
				<tr><td>(vii). Enargy Meter No. </td><td>'.$enargy_no.'</td></tr>
				<tr><td>(viii). CIN No. </td><td>'.$cin_no.'</td></tr>
				<tr><td>(ix). Trade License No. </td><td>'.$trade_no.'</td></tr>
				<tr><td colspan="2">B.Location of Factory </td></tr>
				<tr><td>(i).Zone</td><td>'.$factory_zone_date['zone_name'].'</td></tr>
				<tr><td>(ii).Address</td><td>'.$factory_address_location.'</td></tr>
				<tr><td>(iii).Telephone No</td><td>'.$get_all_data['comm_telephone'].'</td></tr>
				<tr><td>(iv).Mobile No</td><td>'.$get_all_data['comm_mobile'].'</td></tr>
				<tr><td>(v).Fax No</td><td>'.$get_all_data['comm_fax'].'</td></tr>
				<tr><td>(vi).Email Id</td><td>'.$get_all_data['comm_email'].'</td></tr>
				<tr><td colspan="2">C.Address of the Registered office / Head office</td></tr>
				<tr><td>(i).Address</td><td>'.$headoffice_address.'</td></tr>
				
				<tr><td colspan="2">D. Address to which communications relating to the factory may be sent</td></tr>
				<tr><td>(i).Address</td><td>'.$communication_address.'</td></tr>
				<tr><td colspan="2">E.Details of owner of the premises occupied as a factory</td></tr>
				<tr><td>(i).All owner list</td><td>'.$link_owner.'</td></tr>
				<tr><td>E.Factory Identification according to WBPCB</td><td>'.$details.'</td></tr>
				<tr><td colspan="2">F.State the period of license</td></tr>
				<tr><td>(i).Date from which the premises is occupied or been taken into use as factory </td><td>'.date('dS M Y', strtotime($get_all_data['date_of_amenability'])).'</td>
				
				<tr><td>(ii)Registration Number and date</td><td>'.$reg_details.'</td>
				<tr><td>(iii). License number and validupto Date </td><td>'.$license_details.'</td></tr>
				<tr><td>(iv).State the period of license required </td><td>'.$period_for_application.'year(s)</td></tr>';
				
				
				
				if(($service_id == 3 && $renewal_dim_appoved!=1)){
					$output .= '<tr><td colspan="2">G.Worker Details</td></tr>
				<tr><td>(i).Maximum number of workers employed or to be employed in tha factory</td><td>'.$link_t.'  '.$link_amend.'</td></tr>';
				
				}else{
				$output .= '<tr><td colspan="2">G.Worker Details</td></tr>
				<tr><td>(i).Maximum number of workers employed or to be employed in tha factory</td><td>'.$link_t.'</td></tr>';
}
               $output .=' <tr><td colspan="2">H.Power Details</td></tr>
				<tr><td>(i).Installed Power or to be installed power </td><td>'.$power_details.'</td></tr><tr><td colspan="2">I.Manager Details</td></tr>
				<tr><td>(i).Manager Details</td><td>'.$link_manager.'</td></tr>
				<tr><td colspan="2">J.Occupier Details</td></tr>
				<tr><td>(i).View occupier details</td><td>'.$link_occuiper.'</td></tr>
				<tr><td colspan="2">K.Director Details</td></tr>
				<tr><td>(i).View director details</td><td>'.$link_director.'</td></tr><tr>
				<td colspan="2">L.Manufacturing process</td></tr>
				<tr><td>(i).Carried/to be carried on the factory</td><td>'.$nature_work.'</td></tr>
				<td colspan="2">M.Uploaded Documents</td></tr>
				<tr><td>(i).View uploaded documetns</td><td>'.$link_documents.'</td></tr>
				<tr><td colspan="2">N. Application Forms</td></tr>
				<tr><td>Type Of Application</td><td>Form</td></tr>';
				//echo $get_all_data['application_status'];die;
				if($get_all_data['application_status']!=NULL && $get_all_data['application_status']!='In'){
					$output .= '<tr><td>COMMON APPLICATION FORM</td><td>'.$application_from.'</td></tr>';
					}else{
					$output .= '<tr><td>upload Application form.</td><td>Please Upload</td></tr>';
				}
				$output .= '</table></div></div></div>';
				
				
		return $output;
	
}


?>