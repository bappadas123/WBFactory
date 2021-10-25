<?php
function application_preview_data_renewal($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$linknumber) {	

	global $base_root,$base_path,$user;

	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
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
	
	if ($master != $upload) {
    	sort($master);
		sort($upload);
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
			'#markup'	=> renewal_application_preview($application_id,$service_id,$factory_type_id,$referance_number)	
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
    if($application_status == 'B' || empty($application_status) || $application_status == 'In'){
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

function renewal_application_preview($application_id,$service_id,$factory_typeid,$reference_number){
	global $base_root,$base_path,$user;
	$output = "";
	$get_all_data =  get_fa_cafa($application_id);
	
	$renewal_dim_appoved = $get_all_data['renewal_dim_appoved'];
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
	$factory_address_location 	= $get_all_data['addrline'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_factory_location).'<br/>JL No: '.$get_all_data['jl_no'].'<br/>Mouza Nane: '.$get_all_data['mouza_name'];
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
		
		$amaned_link=$base_root.$base_path.'view-amend_power_worker/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_amend=ctools_modal_text_button(t('Amendment Notice'), $amaned_link ,t('Amendment Notice)')) ;
		
		$occupier_details=$base_root.$base_path.'view-occuiper-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_occuiper=ctools_modal_text_button(t('View Occupier(s)'), $occupier_details ,t('View Details)')) ;	
		
		$director_details=$base_root.$base_path.'view-director-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_director=ctools_modal_text_button(t('View Director(s)'), $director_details ,t('View Details)')) ;	
		
		
		$documents_details=$base_root.$base_path.'view-documents-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_documents=ctools_modal_text_button(t('View Documents list'), $documents_details ,t('View Details)')) ;
		
		$manager_details=$base_root.$base_path.'view-manager-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_manager=ctools_modal_text_button(t('View Manager(s)'), $manager_details ,t('View Details)')) ;
		
		
		$owner_details=$base_root.$base_path.'view-owner-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_owner =ctools_modal_text_button(t('View owner Details'), $owner_details ,t('View Details')) ;

		$transfer_details=$base_root.$base_path.'view-transfer-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_transfer =ctools_modal_text_button(t('View transfer Details'), $transfer_details ,t('View Transfer Details')) ;
		
		
		$factory_zone_date = get_factory_zone_name($get_all_data['factory_zone']);
		
		if(!empty($get_all_data['enargy_no'])){ $enargy_no = $get_all_data['enargy_no']; }else{$enargy_no =  'NA';}
			if(!empty($get_all_data['cin_no'])){ $cin_no = $get_all_data['cin_no']; }else{$cin_no =  'NA';}
			
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
			
				
				$file_url =	'<a href='.$base_path.'document-list/view-appliction-form/'.encryption_decryption_fun('encrypt', $service_id).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt', $factory_typeid).'/'.encryption_decryption_fun('encrypt', $reference_number).'/'.encryption_decryption_fun('encrypt','INT').' target= "_BLANK" onclick = "popIt(this.href);return false;">Intimation Letter</a>';
				}
			if($get_all_data['wbpcb_category_name']==5){$consent ='Exempted'; $wbpcb_reference_no = 'n/a';$wbpcb_ref_date = 'n/a';}
		
		$details = $consent.'<br>WBPCB referance no. = '.$wbpcb_reference_no.'<br>WBPCB referance no = '.$wbpcb_ref_date.'<br>'.$file_url;
		
		$displayLink =	'<a href='.$base_path.'applicant/display-demo-licence/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt', $service_id).'/'.encryption_decryption_fun('encrypt', $factory_typeid).'/'.encryption_decryption_fun('encrypt', $reference_number).' target= "_BLANK" onclick = "popIt(this.href);return false;">Sample Licence Certificate</a>';
		

	 $reg_no  = !empty($get_all_data['factory_registrstion_no'])?$get_all_data['factory_registrstion_no']:(!empty($get_all_data['backlog_registration_no'])?$get_all_data['backlog_registration_no']:'NA');
	$registration_date  = !empty($get_all_data['registration_date'])?date('dS M Y', strtotime($get_all_data['registration_date'])):(!empty($get_all_data['backlog_registration_date'])?date('dS M Y', strtotime($get_all_data['backlog_registration_date'])):'NA');
	
	if($reg_no!= 'NA'){
		
		$reg_details = $reg_no .' ,dated on '.$registration_date;
	}else{
		$reg_details ='NA' ;
	}
	 $plan_approval_no = !empty($get_all_data['factory_plan_approval_number'])?$get_all_data['factory_plan_approval_number']:( !empty($get_all_data['backlog_plan_approval_no'])?$get_all_data['backlog_plan_approval_no']:'NA');
	 $plan_approval_date = !empty($get_all_data['plan_approval_date'])?date('dS M Y', strtotime($get_all_data['plan_approval_date'])):(!empty($get_all_data['backlog_plan_approval_date'])?date('dS M Y', strtotime($get_all_data['backlog_plan_approval_date'])):'NA');
	 
	 
	$license_number  = !empty($get_all_data['factory_license_no'])?$get_all_data['factory_license_no']:(!empty($get_all_data['backlog_license_number'])?$get_all_data['backlog_license_number']:'NA');
	$valid_upto  = !empty($get_all_data['license_valid_upto'])?date('dS M Y', strtotime($get_all_data['license_valid_upto'])):'NA';
	$license_date  = !empty($get_all_data['license_date'])?date('dS M Y', strtotime($get_all_data['license_date'])):(!empty($get_all_data['backlog_license_date'])?date('dS M Y', strtotime($get_all_data['backlog_license_date'])):'NA');
	
	if($license_number!= 'NA'){
		
		$license_details = $license_number .' ,dated on '.$license_date.' and validup to date '.$valid_upto;
	}else{
		$license_details ='NA' ;
	}
		if($plan_approval_no != 'NA'){
			$plan_details = $plan_approval_no.' dated on '.$plan_approval_date;
		}else{
			$plan_details = 'Not Avaliable';
		}

	$transfer_view	=	get_previous_details_view($application_id,$reference_number,$factory_typeid,$service_id);
	
	//print_r($transfer_view);die;
	if(!empty($transfer_view)){

		foreach($transfer_view as $pre_row){
			$conversation_ownership	= $pre_row->conversation_ownership_type;
			$change_date 			= $pre_row->change_date;
			$ownership 				= $pre_row->ownership_type;
			$pervious_factory_name	= $pre_row->pervious_factory_name;
			$service_year			= $pre_row->service_year;
			$same_as_pre_details	= $pre_row->same_as_pre_details;
		}
		if($conversation_ownership =="pv"){
			$owner_change = "Pvt Ltd Company";
		}if($conversation_ownership =="ltd"){
				$owner_change = "Ltd Company";
		}if($conversation_ownership =="par_firm"){
				$owner_change = "Partnership Firm";
		}if($conversation_ownership =="pro_firm"){
				$owner_change = "Proprietorship Firm";
		}if($conversation_ownership =="govt"){
				$owner_change = "Govt";
		}if($conversation_ownership =="psu"){
				$owner_change = "PSU";
		}if($conversation_ownership =="llp"){
				$owner_change = "Limited Liability Partnership";
		}if($conversation_ownership =="cooperative"){
				$owner_change = "Co-operative";
		}if($conversation_ownership =="registered"){
				$owner_change = "Registered Society under Society Register";
		}if($conversation_ownership =="localbody"){
				$owner_change = "Local Body";
		}if($conversation_ownership =="others"){
				$owner_change = "Others";
		}

	}
		
	$output .='<div class="row"><div class="box box-info"><div class="box-header with-border">
              	<h2 class="box-title"><b>Application Preview</b></h2><br/><h3>
				Our certificates will be generated based on the information provided by you .'.$displayLink;
				if($renewal_dim_appoved == 1){
					$output .='<br/>You are in the process of auto renewal.<br/>
				Please check and verify your application properly before submitting your application.
				<br/>You will not receive any chance to modify any information after you submit your application';
				}else{
					$output .='Please check and verify your application properly before submitting your application.
				<br/>After receiving a request for correction from the office, you will have the opportunity to retify your application, not otherwise';
			}
				
			$output .='<br/>You have to pay the application fees through GRIPS from our portal
				<br/>N.B.:- Externally the payment process is not a grant.</h3>
              
            </div><div class = "box-body">
				<table class="table table-bordered"> <tr>
   								<th>Parameters</th>
   								<th>Inputs</th>
								</tr>';
	$output .='<tr><td colspan="2">A.Factory Information</td></tr>
				<tr><td>(i). Name of the factory</td><td>'.$get_all_data['factory_name'].' ('.$owner_change.')</td></tr>
				<tr><td>(ii). Ownership Type</td><td>'.$ownership_type.'</td></tr>
				<tr><td>(iii). PAN of the Business Establishment / Factory / Company </td><td>'.$get_all_data['factory_pan'].'</td></tr>
				<tr><td>(iv). Plan Approval number and Date</td><td>'.$plan_details.'</td></tr>
				
				<tr><td>(v). GSTIN No. </td><td>'.$get_all_data['gstin_no'].'</td></tr>
				<tr><td>(vi). Udyog Aadhaar No.</td><td>'.$get_all_data['udyog_aadhaar'].'</td></tr>
				<tr><td>(vii). Enargy Meter No. </td><td>'.$enargy_no.'</td></tr>
				<tr><td>(viii). CIN No. </td><td>'.$cin_no.'</td></tr>
				<tr><td colspan="2">B.Location of Factory </td></tr>
				<tr><td>(i).Zone</td><td>'.$factory_zone_date['zone_name'].'<br/>('.$factory_zone_date['zone_details'].')</td></tr>
				<tr><td>(ii).Address</td><td>'.$factory_address_location.'</td></tr>
				<tr><td>(iii).Telephone No</td><td>'.$get_all_data['comm_telephone'].'</td></tr>
				<tr><td>(i).Mobile No</td><td>'.$get_all_data['comm_mobile'].'</td></tr>
				<tr><td>(v).Fax No</td><td>'.$get_all_data['comm_fax'].'</td></tr>
				<tr><td>(vi)..Email Id</td><td>'.$get_all_data['comm_email'].'</td></tr>
				<tr><td colspan="2">C.Address of the Registered office / Head office<br/><font color="#FF0000">(N.B:-This address will be treated as communication address as per Section 7 of Factories Act,1948 )</font> </td></tr>
				<tr><td>(i).Address</td><td>'.$headoffice_address.'</td></tr>

				<tr><td colspan="2">D.Details of owner of the premises occupied as a factory</td></tr>
				<tr><td>(i).Details of the owner</td><td>'.$link_owner.'</td></tr>
				<tr><td>E.Factory Identification according to WBPCB</td><td>'.$details.'</td></tr>
				<tr><td colspan="2">F.State the period of license</td></tr>
				<tr><td>(i).Date from which the premises is occupied or been taken into use as factory </td><td>'.date('dS M Y', strtotime($get_all_data['date_of_amenability'])).'</td>
				<tr><td>(ii)Registration Number and date</td><td>'.$reg_details.'</td>
				<tr><td>(iii). License number and validupto Date </td><td>'.$license_details.'</td></tr>
				<tr><td>(iv).State the period of license required </td><td>'.$get_all_data['period_for_renewal'].'year(s)</td></tr>
				<tr><td colspan="2">G.Worker Details</td></tr>
				<tr><td>(i).Maximum number of workers employed or to be employed in tha factory</td><td>'.$link_t.'</td></tr>
				<tr><td colspan="2">H.Power Details</td></tr>
				<tr><td>(i).Installed Power or to be installed power </td><td>'.$power_details.'</td></tr>
				
				<tr><td colspan="2">I.Amanded Worker and Power</td></tr>
				<tr><td>(i).Menpower and Installed Power or to be installed power </td><td>'.$link_amend.'</td></tr>
			
				<tr><td colspan="2">J.Manager Details</td></tr>
				<tr><td>(i).Manager Details</td><td>'.$link_manager.'</td></tr>
				<tr><td colspan="2">K.Occupier Details</td></tr>
				<tr><td>(i).View occupier details</td><td>'.$link_occuiper.'</td></tr>
				<tr><td colspan="2">L.Director Details</td></tr>
				<tr><td>(i).View director details</td><td>'.$link_director.'</td></tr><tr>
				<td colspan="2">M.Manufacturing process</td></tr>
				<tr><td>(i).Carried/to be carried on the factory</td><td>'.$nature_work.'</td></tr>
				<td colspan="2">N.Uploaded Documents</td></tr>
				<tr><td>(i).View uploaded documetns</td><td>'.$link_documents.'</td></tr>';
				if(!empty($transfer_view)){
					$output .= '<td colspan="2">O.Uploaded Documents</td></tr>
							<tr><td>(i)Transfer details List</td><td>'.$link_transfer.'</td></tr>';
				}
	$output .= '</table></div></div></div>';
	return $output;
	
}
function application_preview_data_renewal_submit($form, &$form_state){
	$val   						    =  $form_state['values'];
	$uid 			    			=  $user->uid;
	
	
	$service_id						=  encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$factorytype_id					=  encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$application_no 				=  encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$referance_no					=  encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	
	
	
	$get_fa_cafa 					= get_fa_cafa($application_no);
	
	
	 $ownership_type 			= $get_fa_cafa['factory_owershiptype'];
	if(!empty($ownership_type)){
	 if($ownership_type == 'pv' || $ownership_type == 'ltd'){
		 $ownership_type_occupier 	= 'Director';
	 }elseif($ownership_type == 'par_firm'  || $ownership_type=='llp'){
		 $ownership_type_occupier 	= 'Partner';
	 }elseif($ownership_type == 'pro_firm'){
		 $ownership_type_occupier 	= 'Proprietor';
	 }elseif($ownership_type=='cooperative'|| $ownership_type=='registered'){
		 $ownership_type_occupier	= 'Nominated Occupier';
	 }elseif($ownership_type == 'govt' || $ownership_type == 'psu' || $ownership_type == 'others' || $ownership_type=='localbody' ){
		 $ownership_type_occupier	= 'Nominated ';
	 }
	}
	
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
	  $director_status 			= 	array('application_status' => 'RS','type_director'=>$ownership_type);
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
	  $occupier_status 			= 	array('application_status' => 'RS','type_occupier' =>$ownership_type_occupier );
	  $querymanager 			=	db_update('fa_occupier_details');
	  $querymanager				->	fields($occupier_status);
	  $querymanager		    	->	condition('application_occupier_id',$application_no,'=');
	  $querymanager		   		 ->	condition('occupier_service_id',$service_id,'=');
	  $querymanager				->	condition('factory_type_id',$factorytype_id,'=');
	  $querymanager				->	condition('application_reference_no',$referance_no,'=');
	  $querymanager				->	execute();
	 //----------------Documents Update-------------------
	  
	
	  $caf_update = 	array('application_status' => 'RS','modification_date'=>date('Y-m-d'));
	  $queryabc 		=	db_update('fa_cafa');
	  $queryabc		    ->	fields($caf_update);
	  $queryabc			->	condition('id',$application_no,'=');
	  $queryabc	        ->	execute();
	  drupal_set_message('Your application has been successfully saved.');
	   remark_input($referance_no,$application_no,'RS',' Renewal application sucessfully re-save')	;	
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
	   $director_status 			= 	array('application_status' => 'F','type_director'=>$ownership_type);
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
	  $occupier_status 			= 	array('application_status' => 'F','type_occupier' =>$ownership_type_occupier );
	  $querymanager 			=	db_update('fa_occupier_details');
	  $querymanager				->	fields($occupier_status);
	  $querymanager		    	->	condition('application_occupier_id',$application_no,'=');
	  $querymanager		   		 ->	condition('occupier_service_id',$service_id,'=');
	  $querymanager				->	condition('factory_type_id',$factorytype_id,'=');
	  $querymanager				->	condition('application_reference_no',$referance_no,'=');
	  $querymanager				->	execute();
	 //----------------Documents Update-------------------
	  
	
	  
	  $caf_update = 	array('application_status' => 'F','modification_date'=>date('Y-m-d'));
	  $queryabc 		=	db_update('fa_cafa');
	  $queryabc		    ->	fields($caf_update);
	  $queryabc			->	condition('id',$application_no,'=');
	  $queryabc	        ->	execute();
	   remark_input($referance_no,$application_no,'F',' Renewal application sucessfully save')	;	
	  drupal_set_message('Your application has been successfully saved.');
	  
	  drupal_goto('applicant/fees-renewal/'.$val['serviceid_hidden'].'/'.$val['factorytypeid_hidden'].'/'.$val['applicationid_hidden'].'/'.$val['reference_no_hidden']) ;
	} 
}



?>