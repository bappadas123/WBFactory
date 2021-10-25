<?php
//$applicationid
function application_view_register_inspector($form, &$form_state,$serviceid, $factory_typeid,$applicationid,$referenceid) {	

	global $base_root,$base_path,$user;
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');

	$userid 			= 	$user->uid;

	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$reference_no 		= encryption_decryption_fun('decrypt',$referenceid);
	$form = array();
	if (!empty($application_id)) {
        $get_fa_cafa           			= get_fa_cafa($application_id);
       	$application_status      		= $get_fa_cafa['application_status'];
		$factory_identification_number	= $get_fa_cafa['factory_reg_identification_number'];
		$factory_referance_number		= $get_fa_cafa['reference_number'];	
		$applicant_users				= $get_fa_cafa['created_by'];	
		$previous_excess_paid			= $get_fa_cafa['previous_excess_paid'];
		$is_calculate					= $get_fa_cafa['is_calculate'];
		$service_fees					= $get_fa_cafa['service_fees'];	
		$period_for_application 		= $get_fa_cafa['period_for_application'];
	}

	$rid	= get_role_id($userid);
	$query_check_applicant = db_select('fa_cafa_remarks','remarks');
	$query_check_applicant->fields('remarks', array());
	$query_check_applicant->condition('remarks.app_id', $application_id, '=');
	$query_check_applicant->condition('remarks.app_reference_no', $reference_no, '=');
	$query_check_applicant->orderBy('remarks.id','DESC');
	$query_check_applicant->range(0, 1);
	$result = $query_check_applicant->execute();
	$content = $result->fetchAssoc();
	
	
	$form['#attributes'] = array('enctype' => "multipart/form-data");
	$form['serviceid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$service_id)
			 
	);	
	$form['factorytype_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$factory_type_id)
			 
	);		  
	$form['factory_identification_number_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> empty($factory_identification_number)?'':encryption_decryption_fun('encrypt',$factory_identification_number)
			 
	);	   
	$form['referance_no_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$reference_no),
			 
	);
	$form['application_id_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt', $application_id),
			 
	);
	$form['applicant_id_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt', $applicant_users),
			 
	);

	$irregularities_obsevation_ref = fun_fetch_observations_ref($application_id,$reference_no,$factory_type_id,$service_id); 
	//print_r($irregularities_obsevation_ref);die;

	$form['applicantion_verify']['markup_appplication'] = array(
			'#prefix' 		=> '<div class="row">',
			'#suffix'		=> '</div>',
			'#type' 		=> 'markup',
			'#markup' 		=> get_verifing_data($application_id,$service_id,$factory_type_id,$reference_no),
	);
	$form['applicantion_verify']['fieldname']	= array(
												'#title'			=> 'Field Name',
												'#type'				=> 'hidden',
												'#attributes'		=> array('id' => 'inspector_verify'),
												'#default_value' 	=> !empty($content['verify_details']) ? $content['verify_details'] : '',
												);

		$form['applicantion_verify']['Registration_list']	 = array(
			'#prefix' 		=> '<div class="col-md-12 col-xs-12">',
			'#suffix' 		=> '</div>',
			'#markup' 		=> l(t('Back to list'),'inspector-registration-list/', array('html' => TRUE,'attributes'=> array('class'=>array('btn bg-navy margin')))),
	);


//	if($application_status == 'U' || $application_status == 'DC' || $application_status == 'DC'){

		if(($rid==9 && $application_status == 'U') || ($rid==10 && $application_status == 'DC') || ($rid==11 && $application_status == 'JC') ){
			$form['application_forword']['submit'] = array(
				'#prefix' 			=> '<div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div>',
				'#attributes' 		=> array('class' => array('btn btn-dark margin#'), 'onclick' => 'if(!confirm("Are you sure to continue ?")){return false;}'),
				'#type' 			=> 'submit',
				'#value' 			=> 'Save'
			);
		}
		
	//}
	
	
	return $form;
}
	 
function get_ajax_note($form, &$form_state){
		
			$commands   = array();
			$commands[] = ajax_command_replace('#remark_id', drupal_render($form['application_forword']['application_remark']));
			$commands[] = ajax_command_replace('#notesheet_id', drupal_render($form['application_forword']['application_note']));
			$commands[] = ajax_command_replace('#reject_id', drupal_render($form['application_forword']['application_reject']));
			$commands[] = ajax_command_replace('#register_id', drupal_render($form['application_forword']['application_register']));
			$commands[] = ajax_command_replace('#zone_change_id', drupal_render($form['application_forword']['application_zone_change']));
			$commands[] = ajax_command_replace('#zone_remark', drupal_render($form['application_forword']['application_zone_change_note']));
			$commands[] = ajax_command_replace('#edit-doc-file-ajax-wrapper', drupal_render($form['application_forword']['doc_file']));
			$commands[] = ajax_command_replace('#download_registration', drupal_render($form['application_forword']['download_registration']));
			$commands[] = ajax_command_replace('#repay_id', drupal_render($form['application_forword']['application_repay']));
    		return array('#type' => 'ajax', '#commands' => $commands);;
		}
		
function get_verifing_data($application_id,$service_id,$factory_type_id,$reference_no){
		global $base_root,$base_path,$user;		 
		$user_id 			= 	$user->uid;
		$get_all_data 		=   get_fa_cafa($application_id);
		$application_status = 	$get_all_data['application_status'];
		ctools_include('ajax');
		ctools_include('modal');
		ctools_modal_add_js();
		$worker_link=$base_root.$base_path.'view-worker-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
			$link_worker=ctools_modal_text_button(t('View Worker(s)'), $worker_link ,t('View Details)')) ;
			
		$recommanded_worker_link	=	$base_root.$base_path.'view-worker-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
		$recommanded_link_worker	=	ctools_modal_text_button(t('Worker(s)list recommanded by AD'), $recommanded_worker_link ,t('View Details)')) ;	
			
	//	$power_details=$base_root.$base_path.'view-power-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
			//$link_power=ctools_modal_text_button(t('View Power Details'), $power_details ,t('View Details)')) ;
		$occupier_details=$base_root.$base_path.'view-occuiper-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
			$link_occuiper=ctools_modal_text_button(t('View Occupier(s)'), $occupier_details ,t('View Details)')) ;	
		$director_details=$base_root.$base_path.'view-director-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
			$link_director=ctools_modal_text_button(t('View Director(s)'), $director_details ,t('View Details)')) ;		
		//$manufacturing_details=$base_root.$base_path.'view-manufacturing-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
		//	$link_manufacturing=ctools_modal_text_button(t('View Manufacturing Process(s)'), $manufacturing_details ,t('View Details)')) ;		
		$documents_details=$base_root.$base_path.'view-documents-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
			$link_documents=ctools_modal_text_button(t('View Documents list'), $documents_details ,t('View Details)')) ;	
		$manager_details=$base_root.$base_path.'view-manager-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
			$link_manager=ctools_modal_text_button(t('View Manager(s)'), $manager_details ,t('View Details)')) ;	
		$pre_payment_details=$base_root.$base_path.'view-prepaymnet-history/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
			$link_pre_payment=ctools_modal_text_button(t('View Previous Payment'), $pre_payment_details ,t('View Details)')) ;
		
		$owner_details=$base_root.$base_path.'view-owner-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
			$link_owner =ctools_modal_text_button(t('View owner Details'), $owner_details ,t('View Details')) ;

			$irregularities_details = fun_fetch_irregularities_details($identity_flag_all,$application_id,$reference_no,$factory_type_id,$service_id);
			
			if(!empty($irregularities_details)){
		
				foreach($irregularities_details as $row_irregularities_details){
					 $noteshotsheet_type 				= $row_irregularities_details->is_approval_notesheet;
					$checklist_observations_ref_id 	= $row_irregularities_details->checklist_observations_ref_id;
				}
			}
			if($noteshotsheet_type==1){
			$link_t = l('Not Recomended Notesheet', 'regsection/registration-not-view-notesheet/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'View Notesheet', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));
			}

		if($noteshotsheet_type != '1'){
			$link_t	= l('View Notesheet', 'regsection/registration-view-notesheet/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'View Notesheet', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));
		}elseif($application_status == 'DC'){
			//$lnk=$base_root.$base_path.'regsection/deputy-note-list/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/nojs';
			//$link_t=ctools_modal_text_button(t('Details Notesheet list View'), $lnk ,t('Details Notesheet list View')) ;
			//$remarks=$base_root.$base_path.'regsection/remarks-list/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/nojs'; 	
		//	$remarks_ls=ctools_modal_text_button(t('Details Remarks list View'), $remarks ,t('Details Remarks list View')) ;
		}
		 
		
		
		$approve_dsc_reg_file_id			= 	$get_all_data['approve_dsc_reg_file_id'];
		$approve_dsc_licence_file_id		= 	$get_all_data['approve_dsc_licence_file_id'];	
		$licence_register_journal			= 	$get_all_data['approve_dsc_reg_licence_file_id'];
		$upload_application_form_id			= 	$get_all_data['uploaded_pdf'];
		
		$dsc_reg_file = get_uploaded_document_url($approve_dsc_reg_file_id);
		$dsc_lic_file = get_uploaded_document_url($approve_dsc_licence_file_id);
		$licence_register_file = get_uploaded_document_url($licence_register_journal);
		$upload_application_form = get_uploaded_document_url($upload_application_form_id);
	
		if(!empty($approve_dsc_reg_file_id)){
		$reg_down	= l('Download Registration Certificate', file_create_url($dsc_reg_file), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));
		}
		if(!empty($approve_dsc_licence_file_id)){
		$lic_down	= l('Download Licence Certificate',file_create_url($dsc_lic_file), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));}
		if(!empty($licence_register_file)){
		$lic_register_file	= l('Download Licence Register',file_create_url($licence_register_file), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));}
	
		
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
		$factory_zone_date = get_factory_zone_name($get_all_data['factory_zone']);
		$getdata_factory_location	 =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
		$factory_address_location 	 = $get_all_data['addrline'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_factory_location);
		$getdata_headoffice_address  =  array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
		$headoffice_address 		 = $get_all_data['addrline_off'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_headoffice_address);
		$passport_details = !empty($get_all_data['occupier_passport_premises'])?'Passport No-'.$get_all_data['occupier_passport_premises'].',<br/>Passport Issue Date-'.$get_all_data['date_of_issue_premises'].',<br/>Passport Expiry date-'.$get_all_data['date_of_expiry_premises']:'';
		
		$owner_address_details = !empty($get_all_data['addrline_premises'])?$get_all_data['addrline_premises'].',':'';
		 $owner_address_details	.= !empty($get_all_data['country_premises'])?country_name($get_all_data['country_premises']):'<br/>';
		$getdata_owner_address 		=  array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
		$owner_address 				=	$owner_address_details.'<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_owner_address);
	
		$getdata_communication_address = array('district_comm','subdivision_comm','areatype_comm','block_comm','panchayat_comm','policestation_comm','pincodecomm','state_comm','postoffice_comm');
		$communication_address 		= $get_all_data['addrline_comm'].',
		<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_communication_address);
		
		if($get_all_data['wbpcb_category_name']== 4){
			$consent ='White'; 
			$wbpcb_reference_no = 'NA'; 
			$wbpcb_ref_date = 'NA';
			$file = $get_all_data['wbpcb_intimation_letter'];
			$file_url	= l('View', 'document-list/view-appliction-form/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.encryption_decryption_fun('encrypt','CAT'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
			}
		elseif($get_all_data['wbpcb_category_name']==5){
			$consent ='Exempted'; 
			$wbpcb_reference_no = 'NA';
			$wbpcb_ref_date = 'NA';
		}
		else{
			$consent= $get_all_data['wbpcb_category_name'];
			$file_url	= 'Not Applicable for above mention category';
			$wbpcb_reference_no = !empty($wbpcb_reference_no)?$wbpcb_reference_no:'Nil';
			$wbpcb_ref_date = !empty($wbpcb_ref_date)?date('dS M Y', strtotime($wbpcb_ref_date)):'Nil';
		}
		
		if(!empty($get_all_data['factory_reg_identification_number'])){
			$identification_number = '(Application Number:-'.$get_all_data['factory_reg_identification_number'].')';
			}
		$previous_details	=  get_previous_details_view($application_id,$reference_no,$factory_type_id,$service_id);
			foreach($previous_details as $pre_row){
				$is_previous		 	= $pre_row->is_previous;
				if($is_previous == "Yes"){
					$view = "";
				}if($is_previous == "No"){
					$view = "";
				}
			}

		$pdfs_files = get_application_form_pdf($application_id,$reference_no,$factory_type_id,$service_id);
		$fetch_year	= fetch_year($application_id,$service_id,$factory_type_id,$reference_no);
		$pre_view	= get_previous_details_view($application_id,$reference_no,$factory_type_id,$service_id);
		
		$query_check_applicant = db_select('fa_cafa_remarks','remarks');
		$query_check_applicant->fields('remarks', array());
		$query_check_applicant->condition('remarks.app_id', $application_id, '=');
		$query_check_applicant->condition('remarks.app_reference_no', $reference_no, '=');
		$query_check_applicant->orderBy('remarks.id','DESC');
		$query_check_applicant->range(0, 1);
		$result = $query_check_applicant->execute();
		$data = $result->fetchAssoc();
		$remark_field = explode(',', $data['verify_details']);
	
		foreach ($remark_field as $fieldname){ 
			//echo $fieldname;
			if($fieldname == 'factory_name'){ $factory_name_ck = "checked='checked'";}
			if($fieldname == 'ownership_type'){ $ownership_type_ck = "checked='checked'";}
			if($fieldname == 'factory_pan'){ $factory_pan_ck = "checked='checked'";}
			if($fieldname == 'gstin_no'){ $gstin_no_ck = "checked='checked'";}
			if($fieldname == 'udyog_aadhaar'){ $udyog_aadhaar_ck = "checked='checked'";}
			if($fieldname == 'enargy_no'){ $enargy_no_ck = "checked='checked'";}
			if($fieldname == 'cin_no'){ $cin_no_ck = "checked='checked'";}
			if($fieldname == 'trade_no'){ $trade_no_ck = "checked='checked'";}
			
			if($fieldname == 'plan_approval_no'){ $plan_approval_ck = "checked='checked'";}
			if($fieldname == 'plan_approval_date'){ $plan_approval_date_ck = "checked='checked'";}
			
			if($fieldname == 'zone_name'){ $zone_name_ck = "checked='checked'";}
			
			if($fieldname == 'factory_headoffice'){ $factory_headoffice_ck = "checked='checked'";}
			if($fieldname == 'factory_communication'){ $factory_communication_ck = "checked='checked'";}
			
			if($fieldname == 'telephone_no'){ $telephone_no_ck = "checked='checked'";}
			if($fieldname == 'mobile_no'){ $mobile_no_ck 	= "checked='checked'";}
			if($fieldname == 'fax_no'){ $fax_no_ck 	= "checked='checked'";}
			if($fieldname == 'email_no'){ $email_no_ck 	= "checked='checked'";}
			
			if($fieldname == 'owner_name'){ $owner_name_ck = "checked='checked'";}
			if($fieldname == 'premises_address'){ $premises_address_ck = "checked='checked'";}
			
			if($fieldname == 'wbpcb_id'){ $wbpcb_id_ck = "checked='checked'";}
			if($fieldname == 'wbpcb_reference_id'){ $wbpcb_reference_id_ck = "checked='checked'";}
			if($fieldname == 'wbpcb_reference_date'){ $wbpcb_reference_date_ck = "checked='checked'";}
			if($fieldname == 'intimation_id'){ $intimation_id_ck = "checked='checked'";}
			
			if($fieldname == 'date_of_amenability_id'){ $date_of_amenability_id_ck = "checked='checked'";}
			if($fieldname == 'period_for_application_id'){ $period_for_application_id_ck = "checked='checked'";}
			if($fieldname == 'previous_name_id'){ $previous_name_id_ck = "checked='checked'";}
			
			if($fieldname == 'worker_details'){ $worker_details_ck = "checked='checked'";}
			if($fieldname == 'power_details'){ $power_details_ck = "checked='checked'";}
			if($fieldname == 'manager_details'){ $manager_details_ck = "checked='checked'";}
			if($fieldname == 'occupier_details'){ $occupier_details_ck = "checked='checked'";}
			if($fieldname == 'director_details'){ $director_details_ck = "checked='checked'";}
			if($fieldname == 'nature_details'){ $nature_details_ck = "checked='checked'";}
			if($fieldname == 'document_details'){ $document_details_ck = "checked='checked'";}
			
			if($fieldname == 'previous_payment_id'){ $previous_payment_ck = "checked='checked'";}
			if($fieldname == 'payment_amount_id'){ $payment_amount_ck = "checked='checked'";}
			if($fieldname == 'payment_date_id'){ $payment_date_ck = "checked='checked'";}
			if($fieldname == 'applications_forms_id'){ $applications_forms_ck = "checked='checked'";}
			
			if($fieldname == 'applications_period_id'){ $applications_period_ck = "checked='checked'";}
			if($fieldname == 'applications_changes_name_id'){ $applications_changes_name_ck = "checked='checked'";}
		}
			
		if(!empty($get_all_data['enargy_no'])){ $meter = $get_all_data['enargy_no'];}else{$meter = 'NA';}
		if(!empty($get_all_data['cin_no'])){ $cin = $get_all_data['cin_no'].'   <a href="http://www.mca.gov.in/mcafoportal/findCIN.do" target="_blank" title="Ministry Of Corporate Affairs, About MCA, Ministry">(Verify CIN No.)</a>';}else{$cin = 'NA';}
		if(!empty($get_all_data['factory_previous_name'])){ $previous_name = $get_all_data['factory_previous_name'];}else{$previous_name = 'NA';}
		if(!empty($get_all_data['enargy_no'])){ $meter = $get_all_data['enargy_no'];}else{$meter = 'NA';}
		if(!empty($get_all_data['trade_license_no'])){ $trade_no = $get_all_data['trade_license_no'];}else{$trade_no = 'NA';}
	
	
	   $nature_details = get_manufacturing($application_id,$service_id,$factory_type_id,$reference_no);
		foreach($nature_details as $nature){
			$nature_work = $nature->nature_manufacturing;
		}	
		
		$power_generating_station 	= get_power_generating_station($application_id,$reference_no,$factory_type_id,$service_id);
		foreach($power_generating_station as $power){
			if(!empty($power->recommanded_installed_power) || ($power->recommanded_installed_power!=NULL) || ($power->recommanded_installed_power!=0)){
				$link_power = $power->installed_power.'('.$power->power_unit.').<br/><font color="red">Recommanded install power '.$power->recommanded_installed_power.'('.$power->recommanded_power_unit.')by AD</font>';
				
			}else{
				$link_power = $power->installed_power.'('.$power->power_unit.')';
			}
			
		}
				
		$output .= '<div class="box box-info">
						<div class="box-header with-border#"><center><h3 class="box-title">Application for Registration and Grant of Licence<br/>All inputs are provided by applicant only<br/>All inputs are to be verified by officials</h3></center><h5>'.$lic_down.'&nbsp;&nbsp;&nbsp;&nbsp;'.$reg_down.'&nbsp;&nbsp;&nbsp;&nbsp;'.$lic_register_file.' &nbsp;&nbsp;&nbsp;&nbsp;'.$link_t.'&nbsp;&nbsp;&nbsp;&nbsp;'.$remarks_ls.'</h5></div>
						<div class="box-body">
						<table cellpadding="0" cellspacing="0" border="0" width="100%" class="table table-bordered custom-table-view">
						<tr>
   							<th width="30%">Parameters</th>
   							<th>Inputs</th>
							<th width="8%" class="center">Check? <input type="checkbox" id="selectall_inspector"/></th>
						</tr>';
		$output .= '<tr><td colspan="3">A. Factory Information</td></tr>
					<tr>
						<td>(i) Name of the factory</td>
						<td>'.$get_all_data['factory_name'].'</td>
						<td class="center"><input type="checkbox" id="factory_name" class="inspector_verify_check" '.$factory_name_ck .' /></td>
					</tr>
					<tr>
						<td>(ii) Ownership Type</td>
						<td>'.$ownership_type.'</td>
						<td class="center"><input type="checkbox" id="ownership_type" class="inspector_verify_check" '.$ownership_type_ck.'/></td>
					</tr>
					<tr>
						<td>(iii) PAN of the Business Establishment / Factory / Company</td>
						<td>'.$get_all_data['factory_pan'].'</td>
						<td class="center"><input type="checkbox" id="factory_pan" class="inspector_verify_check" '.$factory_pan_ck.'/></td>
					</tr>
					<tr>
						<td>(iv) GSTIN No</td>
						<td>'.$get_all_data['gstin_no'].'</td>
						<td class="center"><input type="checkbox" id="gstin_no" class="inspector_verify_check" '.$gstin_no_ck.'/></td>
					</tr>
					<tr>
						<td>(v) Udyog Adhaar No</td>
						<td>'.$get_all_data['udyog_aadhaar'].'</td>
						<td class="center"><input type="checkbox" id="udyog_aadhaar" class="inspector_verify_check" '.$udyog_aadhaar_ck.'/></td>
					</tr>
					<tr>
						<td>(vi) Enargy Meter No</td>
						<td>'.$meter.'</td>
						<td class="center"><input type="checkbox" id="enargy_no" class="inspector_verify_check" '.$enargy_no_ck.'/></td>
					</tr>
					<tr>
						<td>(vii) CIN No</td>
						<td>'.$cin.'</td>
						<td class="center"><input type="checkbox" id="cin_no" class="inspector_verify_check" '.$cin_no_ck.'/></td>
					</tr>
					<tr>
						<td>(viii) Trade License No</td>
						<td>'.$trade_no.'</td>
						<td class="center"><input type="checkbox" id="trade_no" class="inspector_verify_check" '.$trade_no_ck.'/></td>
					</tr>';
					
					if($factory_type_id ==1 || $factory_type_id == 2){
						$output.='<tr><td>(ix) Plan Approval number</td>
						<td>'.$plan_approval_no.'</td>
						<td class="center"><input type="checkbox" id="plan_approval_no" class="inspector_verify_check"'.$plan_approval_ck.' /></td>
					</tr>
					<tr>
						<td>(x) Plan Approval Date</td>
						<td>'.$plan_approval_date.'</td>
						<td class="center"><input type="checkbox" id="plan_approval_date" class="inspector_verify_check" '.$plan_approval_date_ck.'/></td>
					</tr>';
					}if($factory_type_id ==3){
						$output.='<tr><td>(ix) Plan Approval number</td>
						<td>NA</td>
						<td class="center"></td>
					</tr>
					<tr>
						<td>(x) Plan Approval Date</td>
						<td>NA</td>
						<td class="center"></td>
					</tr>';
					}
						
					$output.='<tr><td colspan="3">B. Location of Factory</td></tr>
					<tr>
						<td>(i) Zone</td>
						<td>'.$factory_zone_date['zone_name'].'</td>
						<td class="center"><input type="checkbox" id="zone_name" class="inspector_verify_check" '.$zone_name_ck.'/></td>
					</tr>
					<tr>
						<td>(ii) Nearest Landmark</td>
						<td colspan="2">'.$get_all_data['nearest_landmark'].'</td>
					</tr>
					<tr>
						<td>(iii) Address</td>
						<td colspan="2">'.$factory_address_location.'<br/>JL No: '.$get_all_data['jl_no'].'<br/>Mouza Name: '.$get_all_data['mouza_name'].'</td>
					</tr>
					<tr>
						<td>(iv) Telephone No.</td>
						<td>'.$get_all_data['comm_telephone'].'</td>
						<td class="center"><input type="checkbox" id="telephone_no" class="inspector_verify_check" '.$telephone_no_ck.' /></td>
					</tr>
					<tr>
						<td>(v) Mobile No.</td>
						<td>'.$get_all_data['comm_mobile'].'</td>
						<td class="center"><input type="checkbox" id="mobile_no" class="inspector_verify_check" '.$mobile_no_ck.'/></td>
					</tr>
					<tr>
						<td>(vi) Fax No.</td>
						<td>'.$get_all_data['comm_fax'].'</td>
						<td class="center"><input type="checkbox" id="fax_no" class="inspector_verify_check" '.$fax_no_ck.'/></td>
					</tr>
					<tr>
						<td>(vii) Email Id</td>
						<td>'.$get_all_data['comm_email'].'</td>
						<td class="center"><input type="checkbox" id="email_no" class="inspector_verify_check" '.$email_no_ck.'/></td>
					</tr>
					<tr>
						<td colspan="3">C. Address of the Registered office / Head office</td></tr>
					<tr>
						<td>(i) Address</td>
						<td>'.$headoffice_address.'</td>
						<td class="center"><input type="checkbox" id="factory_headoffice" class="inspector_verify_check" '.$factory_headoffice_ck.'/></td>
					</tr>

					<tr>
						<td colspan="3">D. Address to which communications relating to the factory may be sent<br/><font color="#FF0000">(N.B:- This address will be treated as communication address as per Section 7 of Factories Act, 1948)</font> </td></tr>
					</tr>
					<tr>
						<td>(i) Communication address </td>
						<td>'.$communication_address.'</td>
						<td class="center"><input type="checkbox" id="factory_communication" class="inspector_verify_check" '.$factory_communication_ck.'/></td>
					</tr>
					
					<tr><td colspan="3">E. Details of owner of the premises occupied as a factory</td></tr>
					<tr>
						<td>(i) Details of the owner</td>
						<td>'.$link_owner.'</td>
						<td class="center"><input type="checkbox" id="owner_name" class="inspector_verify_check" '.$owner_name_ck.'/></td>
					</tr>
					
					<tr><td colspan="3">F. Factory Identification according to WBPCB</td></tr>
					<tr>
						<td>(i) Category</td>
						<td>'.$consent.'</td>
						<td class="center"><input type="checkbox" id="wbpcb_id" class="inspector_verify_check" '.$wbpcb_id_ck.'/></td>
					</tr>
					<tr>
						<td>(ii) Reference No.</td>
						<td>'.$wbpcb_reference_no.'</td>
						<td class="center"><input type="checkbox" id="wbpcb_reference_id" class="inspector_verify_check" '.$wbpcb_reference_id_ck.'/></td>
					</tr>
					<tr>
						<td>(iii) Reference Date</td>
						<td>'.$wbpcb_ref_date.'</td>
						<td class="center"><input type="checkbox" id="wbpcb_reference_date" class="inspector_verify_check" '.$wbpcb_reference_date_ck.'/></td>
					</tr>
					<tr>
						<td>(iv) Intimation Letter</td>
						<td>'.$file_url.'</td>
						<td class="center"><input type="checkbox" id="intimation_id" class="inspector_verify_check" '.$intimation_id_ck.'/></td>
					</tr>
					<tr><td colspan="3">G. State the period of licence</td></tr>
					<tr>
					<td>(i) Date from which the premises is occupied or been taken into use as factory</td>
					<td>'.date('dS M Y', strtotime($get_all_data['date_of_amenability'])).'</td>
					<td class="center"><input type="checkbox" id="date_of_amenability_id" class="inspector_verify_check" '.$date_of_amenability_id_ck.'/></td>
					</tr>
					<tr>
					<td>(ii) State the period of license required </td>
					<td>'.$get_all_data['period_for_application'].'year(s)</td>
					<td class="center"><input type="checkbox" id="period_for_application_id" class="inspector_verify_check" '.$period_for_application_id_ck.'/></td>
					</tr>
					<tr>
					<td>(iii) Whethere any changes name and ownership details of factory </td>
					<td>'.$is_previous.$view.'</td>
					<td class="center"><input type="checkbox" id="previous_name_id" class="inspector_verify_check" '.$previous_name_id_ck.'/></td>
					</tr>
					<tr><td colspan="3">H. Worker Details</td></tr>
					<tr>
					<td>(i) Maximum number of workers employed or to be employed in tha factory</td>
					<td>'.$link_worker.'</td>
					<td class="center"><input type="checkbox" id="worker_details" class="inspector_verify_check" '.$worker_details_ck.'/>
					</tr>
					<tr><td colspan="3">I. Power Details</td></tr>
					<tr>
					<td>(i) Installed Power or to be installed power</td>
					<td>'.$link_power.'</td>
					<td class="center"><input type="checkbox" id="power_details" class="inspector_verify_check" '.$power_details_ck.'/></td>
					</tr>
					<tr><td colspan="3">J. Manager Details</td></tr>
					<tr>
					<td>(i) Manager Details</td>
					<td>'.$link_manager.'</td>
					<td class="center"><input type="checkbox" id="manager_details" class="inspector_verify_check" '.$manager_details_ck.'/></td>
					</tr>
					<tr><td colspan="3">K. Occupier Details</td></tr>
					<tr>
					<td>(i) View occupier details</td>
					<td>'.$link_occuiper.'</td>
					<td class="center"><input type="checkbox" id="occupier_details" class="inspector_verify_check" '.$occupier_details_ck.'/></td>
					</tr>
					<tr><td colspan="3">L. Director Details</td></tr>
					<tr>
					<td>(i) View director details</td>
					<td>'.$link_director.'</td>
					<td class="center"><input type="checkbox" id="director_details" class="inspector_verify_check"'.$director_details_ck.'/></td>
					</tr>
					<tr><td colspan="3">M. Manufacturing process</td></tr>
					<tr>
					<td>(i) Carried/to be carried on the factory</td>
					<td>'.$nature_work.'</td>
					<td class="center"><input type="checkbox" id="nature_details" class="inspector_verify_check" '.$nature_details_ck.'/></td>
					</tr>
					
					
					
					</tr></table>';
				

		
		$output.='</div></div>';
	return $output;
}



function application_view_register_inspector_submit($form, &$form_state){
		global $user;
		$userid 			= 	$user->uid;
		$remark_by_name		= get_name($userid);
		$rid				= get_role_id($userid);
		$val    			= $form_state['values'];

		$service_id 		= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']); 
		$factorytype_id 	= 	encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
		$application_id 	= 	encryption_decryption_fun('decrypt',$val['application_id_hidden']);
		$reference_no		=  	encryption_decryption_fun('decrypt',$val['referance_no_hidden']);

		$verify_details  = $val['fieldname'];

		 $remark_details = get_remark_id($application_id,$reference_no,$userid,$rid);

		$remark_id		= $remark_details['id'];

		$doc_verify 	= $remark_details['doc_verify'];

		$identity_flag_all = NULL;
		$irregularities_obsevation_ref = fun_fetch_observations_ref($application_id,$reference_no,$factorytype_id,$service_id); 
		//print_r($irregularities_obsevation_ref);die;
 		//$remark_id = get_remark_id($application_id,$reference_no,$userid,$rid);
 		if(!empty($irregularities_obsevation_ref)){
			foreach($irregularities_obsevation_ref as $row_irregularities_ref){
				$remark_table_id = $row_irregularities_ref->remark_table_id;
				$checklist_observations_ref_id = $row_irregularities_ref->id;
			}

			if($remark_table_id == $remark_id){
				$cafa_remarks = array(
							'sending_time' 	  	 => date('Y-m-d h:i'),
							'remark_type'	  	 => 'n',
							'verify_details'	 => $verify_details,
					);
						$queryupdate_remarks		 =	db_update('fa_cafa_remarks');
						$queryupdate_remarks	 	->	fields($cafa_remarks);
						$queryupdate_remarks		 ->	condition('id',$remark_id,'=');	
						$queryupdate_remarks		 ->	execute();

			}else{
				if($rid==9){
					$cafa_remarks = array(
						'app_id'   	  		 => $application_id,
						'remark_by_uid'  	 => $userid,
						'remark_by_roleid' 	 => $rid,
						'remark_to_roleid' 	 => 10,
						'sending_time' 	  	 => date('Y-m-d h:i'),
						'app_reference_no' 	 => $reference_no,
						'remark_by_name'	 => $remark_by_name,
						'remark_type'	  	 => 'n',
						'verify_details'	 => $verify_details,
						'remarks'			 => 'Notesheet processed is not completed',
						'service_id'		 => $service_id
							
					);
				}if($rid==10){
					$cafa_remarks = array(
						'app_id'   	  		 => $application_id,
						'remark_by_uid'  	 => $userid,
						'remark_by_roleid' 	 => $rid,
						'remark_to_roleid' 	 => 11,
						'sending_time' 	  	 => date('Y-m-d h:i'),
						'app_reference_no' 	 => $reference_no,
						'remark_by_name'	 => $remark_by_name,
						'remark_type'	  	 => 'n',
						'verify_details'	 => $verify_details,
						'remarks'			 => 'Notesheet processed is not completed',
						
						'service_id'		 => $service_id
							
					);

				}
				if($rid==11){
					$cafa_remarks = array(
						'app_id'   	  		 => $application_id,
						'remark_by_uid'  	 => $userid,
						'remark_by_roleid' 	 => $rid,
						'sending_time' 	  	 => date('Y-m-d h:i'),
						'app_reference_no' 	 => $reference_no,
						'remark_by_name'	 => $remark_by_name,
						'remark_type'	  	 => 'n',
						'verify_details'	 => $verify_details,
						'remarks'			 => 'Notesheet processed is not completed',
						
						'service_id'		 => $service_id
							
					);

				}
		 		
					$remark_id = db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();
			
					$checklist_observations_ref = array(
						'remark_table_id'	 => $remark_id,	
					);
							
					$queryupdate_observations_ref		 =	db_update('fa_checklist_observations_ref');
					$queryupdate_observations_ref	 	->	fields($checklist_observations_ref);
					$queryupdate_observations_ref		 ->	condition('id',$checklist_observations_ref_id,'=');	
					$queryupdate_observations_ref		 ->	execute();
			}

		}
		else{

		
		if($rid==9){
				$cafa_remarks = array(
					'app_id'   	  		 => $application_id,
					'remark_by_uid'  	 => $userid,
					'remark_by_roleid' 	 => $rid,
					'remark_to_roleid' 	 => 10,
					'sending_time' 	  	 => date('Y-m-d h:i'),
					'app_reference_no' 	 => $reference_no,
					'remark_by_name'	 => $remark_by_name,
					'remark_type'	  	 => 'n',
					'verify_details'	 => $verify_details,
					'remarks'			 => 'Notesheet processed is not completed',
					
					'service_id'		 => $service_id
						
			);
		}if($rid==10){
			$cafa_remarks = array(
				'app_id'   	  		 => $application_id,
				'remark_by_uid'  	 => $userid,
				'remark_by_roleid' 	 => $rid,
				'remark_to_roleid' 	 => 11,
				'sending_time' 	  	 => date('Y-m-d h:i'),
				'app_reference_no' 	 => $reference_no,
				'remark_by_name'	 => $remark_by_name,
				'remark_type'	  	 => 'n',
				'verify_details'	 => $verify_details,
				'remarks'			 => 'Notesheet processed is not completed',
				
				'service_id'		 => $service_id	
			);
		}if($rid==11){
					$cafa_remarks = array(
						'app_id'   	  		 => $application_id,
						'remark_by_uid'  	 => $userid,
						'remark_by_roleid' 	 => $rid,
						'sending_time' 	  	 => date('Y-m-d h:i'),
						'app_reference_no' 	 => $reference_no,
						'remark_by_name'	 => $remark_by_name,
						'remark_type'	  	 => 'n',
						'verify_details'	 => $verify_details,
						'remarks'			 => 'Notesheet processed is not completed',
						
						'service_id'		 => $service_id
							
					);

				}

		$remark_id = db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();
		$checklist_observations_ref = array(
								'remark_table_id'	=> $remark_id,
								'application_id'	=> $application_id,
								'factory_type_id' 	=> $factorytype_id,
								'reference_number'  => $reference_no,
								'service_id'  		=> $service_id,
								'created_by'		=> $userid,
								'created_date'		=> date('Y-m-d')
								
							);
		$checklist_observations_ref_id 		 =	db_insert('fa_checklist_observations_ref')->fields($checklist_observations_ref) ->	execute();	


	}
	  
}

?>