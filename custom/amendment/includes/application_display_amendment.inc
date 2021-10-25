<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function application_display_amendment($serviceid, $factory_type_id,$applicationid,$referenceid){

	global $base_root,$base_path,$base_url,$user;
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_typeid 	= encryption_decryption_fun('decrypt',$factory_type_id);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$reference_number 	= encryption_decryption_fun('decrypt',$referenceid);
	
	//die($service_id.'----'.$factory_typeid.'----'.$application_id.'----'.$reference_number);die();
	$output ="";
	$get_all_data 				=  get_fa_cafa($application_id);
	$previous_name				= !empty($get_all_data['factory_previous_name'])?$get_all_data['factory_previous_name']:'Nil';
	
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
	

	$plan_approval_no =  !empty($plan_approval_no)?$plan_approval_no:'Nil';
	$gstin			  =	 !empty($get_all_data['gstin_no'])?$get_all_data['gstin_no']:'Nil';

	
	$getdata_factory_location	=  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address_location 	= $get_all_data['addrline'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_factory_location);
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
	ctools_include('ajax');
	ctools_include('modal');
	ctools_modal_add_js();

	foreach($previous_details as $pre_row){
		$is_change	= $pre_row->is_change;
		if($is_change == 1){
			//$view = "";
			$previous_link = $base_root.$base_path.'view-preview-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
			$show_data = ctools_modal_text_button(t('View factory name(s)'), $previous_link ,t('View Name')) ;
		}else{
			$show_data = 'No';
		}
	} 
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
		
		$owner_details=$base_root.$base_path.'view-owner-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_owner =ctools_modal_text_button(t('View owner Details'), $owner_details ,t('View Details)')) ;
			;
				
		$factory_zone_date = get_factory_zone_name($get_all_data['factory_zone']);
		$udyog_aadhaar 	   = !empty($get_all_data['udyog_aadhaar'])?$get_all_data['udyog_aadhaar']:'Nil';
		
		if(!empty($get_all_data['enargy_no'])){ $enargy_no = $get_all_data['enargy_no']; }else{$enargy_no =  'Nil';}
		if(!empty($get_all_data['cin_no'])){ $cin_no = $get_all_data['cin_no']; }else{$cin_no =  'Nil';}
		if(!empty($get_all_data['trade_license_no'])){ $trade_no = $get_all_data['trade_license_no']; }else{$trade_no =  'Nil';}	
		$comm_fax = !empty($get_all_data['comm_fax'])?$get_all_data['comm_fax']:'Nil';
		$owner_name	=!empty($get_all_data['owner_name'])?$get_all_data['owner_name'].' '.$get_all_data['owner_mname'].' '.$get_all_data['owner_lname']:'Nil';
		
			
		$power_generating_station 	= get_power_generating_station($application_id,$reference_number,$factory_typeid,$service_id);
		foreach($power_generating_station as $power){
			$power_details = $power->installed_power.'('.$power->power_unit.')';
		}
		
		if($get_all_data['wbpcb_category_name']==1){$consent ='Red'; $wbpcb_reference_no = $get_all_data['wbpcb_reference_no'];$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));}
		if($get_all_data['wbpcb_category_name']==2){$consent ='Green'; $wbpcb_reference_no = $get_all_data['wbpcb_reference_no'];$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));}
		if($get_all_data['wbpcb_category_name']==3){$consent ='Orange'; $wbpcb_reference_no = $get_all_data['wbpcb_reference_no'];$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));}
			
		if(!empty($get_all_data['factory_reg_identification_number'])){
			$identification_number = '(Application Number:-'.$get_all_data['factory_reg_identification_number'].')';
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
				
					
					$file_url	= l('Intimation Letter', 'document-list/view-appliction-form/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$referance_number).'/'.encryption_decryption_fun('encrypt','INT'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					}
				if($get_all_data['wbpcb_category_name']==5){$consent ='Exempted'; $wbpcb_reference_no = 'NA';$wbpcb_ref_date = 'NA';}
			
				$details = $consent.'<br>WBPCB referance no. = '.$wbpcb_reference_no.'<br>WBPCB referance no = '.$wbpcb_ref_date.'<br>'.$file_url;
		
				/****** ADDED BY SUBHAMAY ******/
				if($get_all_data['tm_migrated_flag']=='N'||$get_all_data['tm_migrated_flag']=='S')
				{
							
					$application_from = l('Application Form', 'document-list/head-appliction-form/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$factory_typeid).'/'.encryption_decryption_fun('encrypt',$reference_number).'/'.encryption_decryption_fun('encrypt','CAF').'/'.encryption_decryption_fun('encrypt','24'), array('html' => TRUE,'attributes'=>array('title' => 'Application form', 'target' => '_BLANK','class'=>array(''))));
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
		
		
	$output .='<div class="row"><div class="box box-info"><div class="box-header with-border">
              	<h3 class="box-title">Application Preview'.$identification_number .'</h3>
              
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
				<tr><td>(ix). Trade License No. </td><td>'.$trade_no.'</td></tr>
				<tr><td colspan="2">B.Location of Factory </td></tr>
				<tr><td>(i).Zone</td><td>'.$factory_zone_date['zone_name'].'</td></tr>
				<tr><td>(ii).Address</td><td>'.$factory_address_location.'</td></tr>
				<tr><td colspan="2">C.Address of the Registered office / Head office</td></tr>
				<tr><td>(i).Address</td><td>'.$headoffice_address.'</td></tr>
				<tr><td>(ii).Telephone No</td><td>'.$get_all_data['comm_telephone'].'</td></tr>
				<tr><td>(iii).Mobile No</td><td>'.$get_all_data['comm_mobile'].'</td></tr>
				<tr><td>(iv).Fax No</td><td>'.$get_all_data['comm_fax'].'</td></tr>
				<tr><td>(iv).Email Id</td><td>'.$get_all_data['comm_email'].'</td></tr>
				<tr><td colspan="2">D. Address to which communications relating to the factory may be sent</td></tr>
				<tr><td>(i).Address</td><td>'.$communication_address.'</td></tr>
				<tr><td colspan="2">E.Details of owner of the premises occupied as a factory</td></tr>
				<tr><td>(i).View owners</td><td>'.$link_owner.'</td></tr>
				<tr><td>E.Factory Identification according to WBPCB</td><td>'.$details.'</td></tr>
				<tr><td colspan="2">F.State the period of license</td></tr>
				<tr><td>(i).Date from which the premises is occupied or been taken into use as factory </td><td>'.date('dS M Y', strtotime($get_all_data['date_of_amenability'])).'</td>
				<tr><td>(ii).State the period of license required </td><td>'.$get_all_data['period_for_application'].'year(s)</td></tr>
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
				<tr><td>(i).View uploaded documetns</td><td>'.$link_documents.'</td></tr>
				<tr><td colspan="2">N. Application Forms</td></tr>
				<tr><td>Type Of Application</td><td>Form</td></tr>
				<tr><td>COMMON APPLICATION FORM</td><td>'.$application_from.'</td></tr>
				
				</table></div></div></div>';
				
				
		return $output;
	
}


?>