<?php
function preview_for_apply_eservice_extension($form, &$form_state,$serviceid, $factory_type_id,$applicationid,$referenceid) {
	
	global $base_root,$base_path,$user;
	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_typeid 	= encryption_decryption_fun('decrypt',$factory_type_id);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$reference_number 	= encryption_decryption_fun('decrypt',$referenceid);
	 //die;
	
	$form = array();
	  $form['serviceid_hidden']     = array(
        '#type' => 'hidden',
        '#default_value' => $serviceid
    );
    $form['factorytypeid_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $factory_type_id
    );
	$form['applicationid_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $applicationid
    );
	$form['refnumber_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $referenceid
    );
	
	$form['application_preview'] 	= array(
  				'#type'		=> 'markup',
				'#markup'	=> view_deatils($application_id,$reference_number,$factory_typeid,$service_id),
				
			);	
	$form['submit'] = array (
	  		'#prefix' 	=> '<div id="submit_div">',
		 	'#suffix' 	=> '</div></div>',
	  		'#attributes' => array('class' => array('btn btn-dark pull-right'), 'onclick' => 'if(!confirm("Are you sure to continue ?")){return false;}'),
	  		'#type' 	=> 'submit',
	 		'#value'	=> 'Apply'
	);
	
            return $form; 

	}

function view_deatils($application_id,$reference_number,$factory_typeid,$service_id){
	$output ="";
	$get_all_data =  get_fa_cafa($application_id);
	
	
	$service_id_pre_application = $get_all_data['service_id'];
	
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
	}if($get_all_data['factory_owershiptype']=="llp"){
			$ownership_type = "Limited Liability Partnership";
	}if($get_all_data['factory_owershiptype']=="cooperative"){
			$ownership_type = "Co-operative";
	}if($get_all_data['factory_owershiptype']=="registered"){
			$ownership_type = "Registered Society under Society Register";
	}if($get_all_data['factory_owershiptype']=="localbody"){
			$ownership_type = "Local Body";
	}
	

	$is_backlog = $get_all_data['is_backlog'];
	
	if($is_backlog == 1){
		$plan_approval_no = !empty($get_all_data['backlog_plan_approval_no'])?$get_all_data['backlog_plan_approval_no']:'Nil';
		$plan_approval_date =date('dS M Y', strtotime($get_all_data['backlog_plan_approval_date']));
	}else{
		$plan_approval_no = !empty($get_all_data['factory_plan_approval_number'])?$get_all_data['factory_plan_approval_number']:'Nil';
		$plan_approval_date = date('dS M Y', strtotime($get_all_data['plan_approval_date']));
	}
	$getdata_factory_location	= array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address_location	= $get_all_data['addrline'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_factory_location).'<br/>JL No: '.$get_all_data['jl_no'].'<br/>Mouza Nane: '.$get_all_data['mouza_name'];
	$getdata_headoffice_address	= array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
	$headoffice_address			= $get_all_data['addrline_off'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_headoffice_address);
	$getdata_owner_address		= array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
	$owner_address_details = !empty($get_all_data['addrline_premises'])?$get_all_data['addrline_premises'].',':'';
		$owner_address_details.= $get_all_data['owner_country_address'].'<br/>'.country_name($get_all_data['country_premises']);
	
	$getdata_communication_address = array('district_comm','subdivision_comm','areatype_comm','block_comm','panchayat_comm','policestation_comm','pincodecomm','state_comm','postoffice_comm');
	$communication_address 		= $get_all_data['addrline_comm'].',
		<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_communication_address);
		
	//$owner_address_details.= $get_all_data['owner_country_address'].',<br/>'.country_name($get_all_data['owner_country']);
	$owner_name = !empty($get_all_data['owner_name'])?$get_all_data['owner_name']:'Nil';
	$owner_address 				 =$owner_address_details.'<br/>'.$get_all_data['addrline_premises'].'<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_owner_address);
	
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
		$worker_link		=	$base_root.$base_path.'view-worker-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number;
		$link_t				=	ctools_modal_text_button(t('View Worker(s)'), $worker_link ,t('View Details)')) ;
		
		$occupier_details	=	$base_root.$base_path.'view-occuiper-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_occuiper		=	ctools_modal_text_button(t('View Occupier(s)'), $occupier_details ,t('View Details)')) ;	
		
		
			
		$documents_details	=	$base_root.$base_path.'view-documents-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_documents		=	ctools_modal_text_button(t('View Documents list'), $documents_details ,t('View Details)')) ;
		
		
		
		$owner_details=$base_root.$base_path.'view-owner-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_owner =ctools_modal_text_button(t('View owner Details'), $owner_details ,t('View Details')) ;
			

		
		
			
		$factory_zone_date = get_factory_zone_name($get_all_data['factory_zone']);
		
		$plan_approval_number	= !empty($get_all_data['factory_plan_approval_number'])? $get_all_data['factory_plan_approval_number']:$get_all_data['backlog_plan_approval_no'];
		$plan_approval_date 	= !empty($get_all_data['plan_approval_date'])? $get_all_data['plan_approval_date']:$get_all_data['backlog_plan_approval_date'];
		
		$plan_registration_number	= !empty($get_all_data['factory_registrstion_no'])? $get_all_data['factory_registrstion_no']:$get_all_data['backlog_registration_no'];
		$plan_registration_date 	= !empty($get_all_data['registration_date'])? $get_all_data['registration_date']:$get_all_data['backlog_registration_date'];
		
		
		$plan_licesne_number	= !empty($get_all_data['factory_license_no'])? $get_all_data['factory_license_no']:$get_all_data['backlog_license_number'];
		$plan_license_date 		= !empty($get_all_data['license_date'])? $get_all_data['license_date']:$get_all_data['backlog_license_date'];
		$comm_fax				= !empty($get_all_data['comm_fax'])?$get_all_data['comm_fax']:'Nil';
		if(!empty($get_all_data['enargy_no'])){ $enargy_no = $get_all_data['enargy_no']; }else{$enargy_no =  'Nil';}
		if(!empty($get_all_data['cin_no'])){ $cin_no = $get_all_data['cin_no']; }else{$cin_no =  'Nil';}
		if(!empty($get_all_data['trade_license_no'])){ $trade_no = $get_all_data['trade_license_no']; }else{$trade_no =  'Nil';}
		$previous_name = !empty($get_all_data['factory_previous_name'])?$get_all_data['factory_previous_name']:'Nil';
		if($factory_typeid==1){
			$section = "Section-2m(i)";
		}if($factory_typeid==2){
			$section = "Section-2m(ii)";
		}if($factory_typeid==3){
			$section = "Section-85";
		}
		$type_of_application ='Name :-'.$get_all_data['factory_name'].'('.$section.')<br/>Plan Approval Number:-'.$plan_approval_number.' dated on '.date('dS M Y', strtotime($plan_approval_date)).
			
			 '<br/><h4>All inputs given by Applicants</h4>';
		
		$application_from	= l('Common application form', 'document-list/view-appliction-form/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$factory_typeid).'/'.encryption_decryption_fun('encrypt',$reference_number).'/'.encryption_decryption_fun('encrypt','CAF'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
		
	if($get_all_data['wbpcb_category_name']==1){$consent ='Red'; $wbpcb_reference_no = !empty($get_all_data['wbpcb_reference_no'])?$get_all_data['wbpcb_reference_no']:'Nil';$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));}
			 if($get_all_data['wbpcb_category_name']==2){ $consent ='Green'; $wbpcb_reference_no = !empty($get_all_data['wbpcb_reference_no'])?$get_all_data['wbpcb_reference_no']:'Nil';$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));
			}
			 if($get_all_data['wbpcb_category_name']==3){
				 $consent ='Orange';$wbpcb_reference_no = !empty($get_all_data['wbpcb_reference_no'])?$get_all_data['wbpcb_reference_no']:'Nil';$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));
				}
			
			 if($get_all_data['wbpcb_category_name']== 4){
				$consent ='White'; 
				$wbpcb_reference_no = 'N/A'; 
				$wbpcb_ref_date = 'N/A';
				$file_url	= l('View', 'document-list/view-appliction-form/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$factory_typeid).'/'.encryption_decryption_fun('encrypt',$reference_number).'/'.encryption_decryption_fun('encrypt','CAT'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				}
			 if($get_all_data['wbpcb_category_name']==5){$consent ='Exempted'; $wbpcb_reference_no = 'N/A';$wbpcb_ref_date = 'N/A';}
			 if(!empty($get_all_data['factory_reg_identification_number'])){
			$identification_number = '(Application Number:-'.$get_all_data['factory_reg_identification_number'].')';
			}if(empty($get_all_data['wbpcb_category_name'])){
				$consent = '';$wbpcb_reference_no = 'Nil';$wbpcb_ref_date = 'Nil';
			}
			
			
		 $details = $consent.'<br>WBPCB referance no. = '.$wbpcb_reference_no.'<br>WBPCB referance date = '.$wbpcb_ref_date.'<br>'.$file_url; 
		//echo $wbpcb_reference_no;
		
		
	$output .='<div class="row">
				<div class="box box-info">
					<div class="box-header with-border"><center><h3 class="box-title">Application Preview<br/>'.$type_of_application.'</h3></center></div>
					<div class="box-body">
						<table class="table table-bordered"> <tr>
   								<th width="44%">Parameters</th>
   								<th>Inputs</th>
								</tr>';
	$output .='<tr><td colspan="2" class="sub-title">A. Factory Information</td></tr>
				<tr><td>(i). Name of the factory</td><td>'.$get_all_data['factory_name'].'</td></tr>
				<tr><td>(ii). Name of the previous factory</td><td>'.$previous_name.'</td></tr>
				<tr><td>(iii). Ownership Type</td><td>'.$ownership_type.'</td></tr>
				<tr><td>(iv). PAN of the Business Establishment / Factory / Company </td><td>'.$get_all_data['factory_pan'].'</td></tr>
				<tr><td>(v). GSTIN Number</td><td>'.$get_all_data['gstin_no'].'</td></tr>
				<tr><td>(vi). Udyog Aadhaar No</td><td>'.$get_all_data['udyog_aadhaar'].'</td></tr>
				<tr><td>(vii). Trade License No</td><td>'.$trade_no.'</td></tr>
				<tr><td>(viii). Energy Meter No</td><td>'.$enargy_no.'</td></tr>
				<tr><td>(ix). CIN No</td><td>'.$cin_no.'</td></tr>';
				
				if($factory_typeid==1 || $factory_typeid==2){
					$output .='<tr><td>(x). Plan Approval number </td><td>'.$plan_approval_no.'</td></tr>
				<tr><td>(xi). Plan Approval Date </td><td>'.$plan_approval_date.'</td></tr>';
				}else{
					$output .='<tr><td>(x). Plan Approval number </td><td>NA</td></tr>
				<tr><td>(xi). Plan Approval Date </td><td>NA</td></tr>';
				}
				
				
				$output .='<tr><td colspan="2" class="sub-title">B. Location of Factory </td></tr>
				<tr><td>(i). Zone</td><td>'.$factory_zone_date['zone_name'].'</td></tr>
				<tr><td>(ii). Address</td><td>'.$factory_address_location.'</td></tr>
				<tr><td>(iii). Telephone No</td><td>'.$get_all_data['comm_telephone'].'</td></tr>
				<tr><td>(iv). Mobile No</td><td>'.$get_all_data['comm_mobile'].'</td></tr>
				<tr><td>(v). Fax No</td><td>'.$comm_fax.'</td></tr>
				<tr><td>(vi). Email Id</td><td>'.$get_all_data['comm_email'].'</td></tr>
				
				<tr><td colspan="2" class="sub-title">C. Address of the Registered office / Head office</td></tr>
				<tr><td>(i). Address</td><td>'.$headoffice_address.'</td></tr>
				
				
				<tr><td colspan="2">D. Address to which communications relating to the factory may be sent</td></tr>
				<tr><td>(i).Address</td><td>'.$communication_address.'</td></tr>
				
				<tr><td colspan="2" class="sub-title">E. Details of owner of the premises occupied as a factory</td></tr>
				<tr><td>(i). Details of the owner</td><td>'.$link_owner.'</td></tr>
				<tr><td  class="sub-title">F. Factory Identification according to WBPCB</td><td>'.$details.'</td></tr>
				<tr><td colspan="2" class="sub-title">G. PARTICULAR OF PLAN TO BE INSTALLED</td></tr>
				
				<tr><td>(i). Plant To be Installed</td><td>'.$get_all_data['plant_installed'].'</td></tr>
				
				<tr><td colspan="2" class="sub-title">H. Worker Details</td></tr>
				<tr><td>(i). Maximum number of workers employed or to be employed in the factory</td><td>'.$link_t.'</td></tr>
				<tr><td>(i). View occupier details</td><td>'.$link_occuiper.'</td></tr>
				
				<td colspan="2" class="sub-title">I. Uploaded Documents</td></tr>
				<tr><td>(i). View uploaded documetns</td><td>'.$link_documents.'</td></tr>
				<tr><td colspan="2" class="sub-title">J. Application Forms</td></tr>
				<tr><td>(i).Common Application Form</td><td>'.$application_from.'</td></tr>';
				
	$output .= '</table></div></div></div>';
	return $output;
}
function preview_for_apply_eservice_extension_submit($form, &$form_state){
	
	global $user;
    $userid 			= $user->uid;
    $val    			= $form_state['values'];
	
	$application_id 	= encryption_decryption_fun('decrypt', $val['applicationid_hidden']); 
	$service_id 		= encryption_decryption_fun('decrypt', $val['serviceid_hidden']); 
	$factory_id 		= encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']); 
	$reference_id 		= encryption_decryption_fun('decrypt', $val['refnumber_hidden']);
	
	log_genaration_caf($application_id);
	$referenceno 		= created_referenceno();
	$serviceid 			= 5;
    $worker_details 	= get_worker_details_service($service_id,$factory_id,$application_id,$reference_id);
	foreach($worker_details as $worker){
		$workerid = $worker->id;
	}
	log_genaration_worker($workerid,$referenceno,$serviceid);
	
	
	$occupier_details = get_all_occupier_data($application_id,$service_id,$factory_id,$reference_id);
	foreach($occupier_details as $occupier){
			$occupierid = $occupier->id;
			
	}
	log_genaration_occupier($occupierid, $referenceno, $serviceid);
	
	 $owner_details = get_all_owner_data($application_id,$service_id,$factory_id,$reference_id);
	 foreach($owner_details as $owner){
			$ownerid = $owner->id;
	  		log_genaration_owner($ownerid, $referenceno, $serviceid);
	}
	$doc_type		= NULL;
	$doc_id 		= NULL;
	$all_doc_details = get_caf_upload_doc_all($application_id,$service_id,$doc_type,$factory_id,$reference_id,$doc_id);
	
	foreach($all_doc_details as $all_doc){
		$docid = $all_doc->id;
		$content_id = $all_doc->upload_doc_content_id;
		log_genaration_upload_doc($docid, $referenceno, $serviceid,$content_id);
	}
	
	$application_number = create_registration_application($serviceid);
	
	$approval_status 	= 	array('plan_approve_status' => 'In','service_id' => $serviceid,'reference_number' => $referenceno);
				 
	$queryapp	=	db_update('fa_cafa');
	$queryapp	->	fields($approval_status);
	$queryapp	->	condition('id',$application_id,'=');
	$queryapp	->	condition('factory_typeid',$factory_id,'=');
	$queryapp	->	condition('reference_number',$reference_id,'=');
	$queryapp	->	execute();
	
 drupal_goto('applicant/caf_extn/plan_extension/'.encryption_decryption_fun('encrypt',$serviceid).'/'.encryption_decryption_fun('encrypt',$factory_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$referenceno));



	
}

?>