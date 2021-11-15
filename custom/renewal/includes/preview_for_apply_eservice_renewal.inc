<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function preview_for_apply_eservice_renewal($form, &$form_state,$serviceid, $factory_type_id,$applicationid,$referenceid) {
	global $base_root,$base_path,$user;
	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	
	  $service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	  $factory_typeid 	= encryption_decryption_fun('decrypt',$factory_type_id);
	  $application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	  $reference_number = encryption_decryption_fun('decrypt',$referenceid);
	  
	//die($service_id.'---'.$factory_typeid.'---'.$application_id.'---'.$reference_number);
	
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
	
	
	$get_all_data 				=  get_fa_cafa($application_id);
	
	//echo "<pre>";print_r($get_all_data); exit;
	$plan_registration_date 	= !empty($get_all_data['registration_date'])? $get_all_data['registration_date']:$get_all_data['backlog_registration_date'];
	$plan_license_date 			= !empty($get_all_data['license_valid_upto'])? $get_all_data['license_valid_upto']:$get_all_data['backlog_license_date'];
	$period_for_renewal			= $get_all_data['period_for_renewal'];
	$telmak_migrated_flag		= $get_all_data['tm_migrated_flag'];
	
	$form['telmak_migrated_flag_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => encryption_decryption_fun('encrypt',$telmak_migrated_flag)
    );
	
	$form['application_preview'] 	= array(
  		'#type'		=> 'markup',
		'#markup'	=> view_deatils($application_id,$reference_number,$factory_typeid,$service_id),
	);	
	$ques  = array(
			"1" 	=> "Auto Renewal of the license",
			"0" 	=> "Renewal of the license with transfer declaration",
	);
				
	$form['renewal_ques'] = array(
			'#type' 			=> 'fieldset',
			'#title' 			=> t('Renewal Information'),
			'#collapsible' 		=> FALSE, // Added
			'#collapsed' 		=> FALSE,  // Added
	);	
	$form['renewal_ques']['ques_type'] 	= array(
			'#prefix' 			=> '<div class="row"><div class="box box-info"><div class="box-body">
										<div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div>',
			'#title'			=>	t('Please select any one'),
			'#type' 			=> 'radios',
			'#required' 		=> TRUE,
			'#options' 			=> $ques,
							
	);
		 
	
	
	
	
	$form['renewal_ques']['submit'] = array (
	  		'#prefix' 	=> '<div id="submit_div">',
		 	'#suffix' 	=> '</div>',
	  		'#attributes' => array('class' => array('btn btn-success pull-right'), 'onclick' => 'if(!confirm("Are you sure to continue ?")){return false;}'),
	  		'#type' 	=> 'submit',
	 		'#value'	=> 'Continue',
			
	);
	$form['renewal_ques']['markup_end'] = array(
           '#suffix' => '</div></div></div>',
           '#type' => 'markup',
		   '#markup'	=>  '<span style="color:red";>Changes that must be approved under auto-renewal are workers and installed or to be installed capacity and extended date of validity of your License instally, after sucecssfully complete your application process i.e. pay application fees and upload Common Application Form.<br/>You have to pay the application fees through GRIPS from our portal for any service<br/>
		   N.B.:- Externally the payment process is not a grant </span>',		
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
		
		$amaned_link=$base_root.$base_path.'view-amend_power_worker/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_amend=ctools_modal_text_button(t('Amendment Notice'), $amaned_link ,t('Amendment Notice)')) ;
		
		$occupier_details	=	$base_root.$base_path.'view-occuiper-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_occuiper		=	ctools_modal_text_button(t('View Occupier(s)'), $occupier_details ,t('View Details)')) ;	
		
		$director_details	=	$base_root.$base_path.'view-director-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_director		=	ctools_modal_text_button(t('View Director(s)'), $director_details ,t('View Details)')) ;	
		
			
		$documents_details	=	$base_root.$base_path.'view-documents-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_documents		=	ctools_modal_text_button(t('View Documents list'), $documents_details ,t('View Details)')) ;
		
		$manager_details	=	$base_root.$base_path.'view-manager-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_manager		=	ctools_modal_text_button(t('View Manager(s)'), $manager_details ,t('View Details)')) ;
		
		$owner_details=$base_root.$base_path.'view-owner-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_owner =ctools_modal_text_button(t('View owner Details'), $owner_details ,t('View Details')) ;
			

		$power_generating_station 	= get_power_generating_station($application_id,$reference_number,$factory_typeid,$service_id);
		foreach($power_generating_station as $power){
			$power_details = $power->installed_power.'('.$power->power_unit.')';
		}
		
		$nature_details = get_manufacturing($application_id,$service_id,$factory_typeid,$reference_number);
		foreach($nature_details as $nature){
			$nature_work = $nature->nature_manufacturing;
		}	
		$factory_zone_date = get_factory_zone_name($get_all_data['factory_zone']);
		$date_amenability = !empty($get_all_data['date_of_amenability'])?date('dS M Y', strtotime($get_all_data['date_of_amenability'])):'';
		$period_for_application	=!empty($get_all_data['period_for_application'])?$get_all_data['period_for_application'].'Year(s)':'';
		
		$pdfs_files = get_application_form_pdf($application_id,$reference_number,$factory_typeid,$service_id);
		//echo $service_id_pre_application;die();
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
		
		if($service_id_pre_application == 4 || $service_id_pre_application == 5){
			$type_of_application ='Plan Approval Number:-'.$plan_approval_number.' dated on '.date('dS M Y', strtotime($plan_approval_date)).'<br/>
			
			 <br/><h4>All inputs given by Applicants</h4>';
				$application_frm_id 	= 	$get_all_data['uploaded_pdf'];
				$application_form_url 	= 	get_uploaded_document_url($application_frm_id);
				
				if(!empty($application_form_url)){ 
						$url 						= explode('//',$application_form_url);
						$doc_url					= $url[1];
						$application_form_view		='<a title = "Click here to view" href="'.$GLOBALS['base_url'].'/sites/default/files/'.$doc_url.'" target="_blank"><i class="ace-icon fa fa-file-pdf-o bigger-130"></i></a>'; 
	
				}
		}
		if($service_id_pre_application == 2 ){ 
		
				$type_of_application =' Plan Approval Number:-'.$plan_approval_number.' dated on '.date('dS M Y', strtotime($plan_approval_date)).'<br/>Registration Number:-'.$plan_registration_number.' dated on '.date('dS M Y', strtotime($plan_registration_date)).'<br/>'.'License Number:- '.$plan_licesne_number.' dated on '.date('dS M Y', strtotime($plan_license_date)).'<br/><span style="color:red">License Expiring on dated:- '.date('dS M Y', strtotime($get_all_data['license_valid_upto'])).'</span><br/>
			 
			 <br/><h4>All inputs given by Applicants</h4>';
				 
		}
		if($service_id_pre_application >= 3 ){ 
		
				 $type_of_application =' Plan Approval Number:-'.$plan_approval_number.' dated on '.date('dS M Y', strtotime($plan_approval_date)).'<br/>Registration Number:-'.$plan_registration_number.' dated on '.date('dS M Y', strtotime($plan_registration_date)).'<br/>'.'License Number:- '.$plan_licesne_number.' dated on '.date('dS M Y', strtotime($plan_license_date)).'<br/><span style="color:red">License Expiring on dated:- '.date('dS M Y', strtotime($get_all_data['license_valid_upto'])).'</span><br/>
			 
			 <br/><h4>All inputs given by Applicants</h4>';
		}
		$application_from	= l('Common application form', 'document-list/view-appliction-form/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$factory_typeid).'/'.encryption_decryption_fun('encrypt',$reference_number).'/'.encryption_decryption_fun('encrypt','CAF'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
		
	if($get_all_data['wbpcb_category_name']==1){$consent ='Red'; $wbpcb_reference_no = !empty($get_all_data['wbpcb_reference_no'])?$get_all_data['wbpcb_reference_no']:'Nil';$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));}
			 if($get_all_data['wbpcb_category_name']==2){ $consent ='Green'; $wbpcb_reference_no = !empty($get_all_data['wbpcb_reference_no'])?$get_all_data['wbpcb_reference_no']:'Nil';$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));
			}
			 if($get_all_data['wbpcb_category_name']==3){
				 $consent ='Orange';$wbpcb_reference_no = !empty($get_all_data['wbpcb_reference_no'])?$get_all_data['wbpcb_reference_no']:'Nil';$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));
				}
			
			 if($get_all_data['wbpcb_category_name']== 4){
				$consent ='White'; 
				$wbpcb_reference_no = 'NA'; 
				$wbpcb_ref_date = 'NA';
				$file_url	= l('Intimation Letter', 'document-list/view-appliction-form/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$factory_typeid).'/'.encryption_decryption_fun('encrypt',$reference_number).'/'.encryption_decryption_fun('encrypt','INT'), array('html' => TRUE,'attributes'=>array('title' => 'Intimation Letter', 'target' => '_BLANK','class'=>array(''))));
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
				<tr><td colspan="2" class="sub-title">G. State the period of license</td></tr>
				<tr><td>(i). Date from which the premises is occupied or been taken into use as factory </td><td>'.$date_amenability.'</td>
				<tr><td>(ii). State the period of license required </td><td>'.$period_for_application.'</td></tr>
				<tr><td>(iii). Whethere any changes name and ownership details of factory </td><td>'.$is_previous.$view.'</td></tr>
				<tr><td colspan="2" class="sub-title">H. Worker Details</td></tr>
				<tr><td>(i). Maximum number of workers employed or to be employed in the factory</td><td>'.$link_t.'</td></tr>
				<tr><td colspan="2" class="sub-title">I. Power Details</td></tr>
				<tr><td>(i). Installed Power or to be installed power </td><td>'.$power_details.'</td></tr>
				<tr><td colspan="2">I.Amanded Worker and Power</td></tr>
				<tr><td>(i).Menpower and Installed Power or to be installed power </td><td>'.$link_amend.'</td></tr>
				<tr><td colspan="2" class="sub-title">J. Manager Details</td></tr>
				<tr><td>(i). Manager Details</td><td>'.$link_manager.'</td></tr>
				<tr><td colspan="2" class="sub-title">K. Occupier Details</td></tr>
				<tr><td>(i). View occupier details</td><td>'.$link_occuiper.'</td></tr>
				<tr><td colspan="2" class="sub-title">L. Director Details</td></tr>
				<tr><td>(i). View director details</td><td>'.$link_director.'</td></tr><tr>
				<td colspan="2" class="sub-title">M. Manufacturing process</td></tr>
				<tr><td>(i). Carried/to be carried on the factory</td><td>'.$nature_work.'</td></tr>
				<td colspan="2" class="sub-title">N. Uploaded Documents</td></tr>
				<tr><td>(i). View uploaded documetns</td><td>'.$link_documents.'</td></tr>
				<tr><td colspan="2" class="sub-title">O. Application Forms</td></tr>
				<tr><td>(i).Common Application Form</td><td>'.$application_from.'</td></tr>';
				
	$output .= '</table></div></div></div>';
	return $output;
}



function preview_for_apply_eservice_renewal_submit($form, &$form_state){
	global $user;
    $userid 						= $user->uid;
    $val    						= $form_state['values'];
	
	
	
	$application_id 				= encryption_decryption_fun('decrypt', $val['applicationid_hidden']); 
	$ans_ques_hidden 				= encryption_decryption_fun('decrypt', $val['ans_ques_hidden']);
	
	 $service_id 					= encryption_decryption_fun('decrypt', $val['serviceid_hidden']); 
	$factory_id 					= encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']); 
	$reference_id 					= encryption_decryption_fun('decrypt', $val['refnumber_hidden']);
	$renewal_for_period				= $val['renewal_for_period'];
	$ques_type						= $val['ques_type'];
	$renewal_date					= $val['renewal_date'];
	$telmak_migrated_flag_hidden	= encryption_decryption_fun('decrypt', $val['telmak_migrated_flag_hidden']);
	
	$date_current 					= new DateTime(date('Y-m-d'));
	$date_renew 					= new DateTime($val['renewal_date']);
	$fieldname						= 'worker_details,power_details';
	
	if($ques_type == 1 && $telmak_migrated_flag_hidden == 'N'){
		log_genaration_caf($application_id);
		$referenceno 		= created_referenceno();
		$serviceid 			= 3;
		$worker_details 	= get_worker_details_service($service_id,$factory_id,$application_id,$reference_id);
		foreach($worker_details as $worker){
					 $workerid = $worker->id;
		}
	    log_genaration_worker($workerid,$referenceno,$serviceid);
		 $power_details = get_power_generating_station($application_id,$reference_id,$factory_id,$service_id);
				
		foreach($power_details as $power){
			$powerid = $power->id;
		 }
		log_genaration_power($powerid, $referenceno, $serviceid);
				 
		$manager_details = get_all_manager_data($application_id,$service_id,$factory_id,$reference_id);
				 
		foreach($manager_details as $manager){
			 $managerid = $manager->id;
			log_genaration_manager($managerid, $referenceno, $serviceid);
		 }
		 $occupier_details = get_all_occupier_data($application_id,$service_id,$factory_id,$reference_id);
				
		 foreach($occupier_details as $occupier){
			$occupierid = $occupier->id;
			log_genaration_occupier($occupierid, $referenceno, $serviceid);
		 }
		$director_details = get_director_details_service($application_id,$service_id,$factory_id,$reference_id);
			
		foreach($director_details as $director){
			$directorid = $director->id;
			log_genaration_director($directorid, $referenceno, $serviceid);
		}
				 
		$manufacturing_details = get_manufacturing($application_id,$service_id,$factory_id,$reference_id);
			
		foreach($manufacturing_details as $manufacturing){
			$manufacturingid = $manufacturing->id;
		 }
		if(!empty($manufacturingid)){
		 log_genaration_manufacturing($manufacturingid, $referenceno, $serviceid);
				  
				 
			}
		 $owner_details = get_all_owner_data($application_id,$service_id,$factory_id,$reference_id);
		foreach($owner_details as $owner){
				$ownerid = $owner->id;
	  			log_genaration_owner($ownerid, $referenceno, $serviceid);
		}
		
		$doc_type= NULL;
		$doc_id = NULL;
	$all_doc_details = get_caf_upload_doc_all($application_id,$service_id,$doc_type,$factory_id,$reference_id,$doc_id);
	
	foreach($all_doc_details as $all_doc){
		$docid = $all_doc->id;
		$content_id = $all_doc->upload_doc_content_id;
		log_genaration_upload_doc($docid, $referenceno, $serviceid,$content_id);
	}

		
		 $year_update = array('is_previous'=>1);
				 
			$approval_status 	= 	array('application_status' => 'In','service_id' => $serviceid,'reference_number' => $referenceno,'renewal_dim_appoved' =>$ques_type);
		 		$queryapp	=	db_update('fa_cafa');
		 		 $queryapp	->	fields($approval_status);
		 		 $queryapp	->	condition('id',$application_id,'=');
		 		 $queryapp	->	condition('factory_typeid',$factory_id,'=');
		 		 $queryapp	->	condition('reference_number',$reference_id,'=');
		 		 $queryapp	->	execute();
				 
				 $previous_year	=	db_update('fa_calculate_year');
				 $previous_year	->	fields($year_update);
				 $previous_year	->	condition('application_id',$application_id,'=');
				 $previous_year	->	condition('reference_no',$reference_id,'=');
				 $previous_year	->	condition('factory_id',$factory_id,'=');
				 $previous_year	->	condition('service_id',$service_id,'=');
				 $previous_year	->	execute();
				 
		 	year_calculation_for_license_period($renewal_date,$renewal_for_period,$serviceid,$factory_id,$referenceno,$application_id);	 
			
		 	remark_input($referenceno,$application_id,'In','Auto renewal is started')	;
		 drupal_goto('applicant/caf-online-renew/details-worker-renewal/'.encryption_decryption_fun('encrypt',$serviceid).'/'.encryption_decryption_fun('encrypt',$factory_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$referenceno));
		
	}
	
	if($ques_type == 0 && $telmak_migrated_flag_hidden == 'N'){
			
		 drupal_goto('applicant/change-list/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_id));
		//drupal_set_message(t('UNDER PROCESS.PLEASE TEST AUTO RENEWAL.'), 'error');
		//drupal_goto('applicant/change-list/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_id));
	}
	
	/*if($telmak_migrated_flag_hidden != 'N' && $ques_type == 1){
		
			log_genaration_caf($application_id);
			$referenceno 		= created_referenceno();
			$serviceid 			= 3;
			
			$worker_details = get_worker_details_service($service_id,$factory_id,$application_id,$reference_id);
			foreach($worker_details as $worker){
				$workerid = $worker->id;
			}
			log_genaration_worker($workerid,$referenceno,$serviceid);
			
			//die('worker log');
			
			$power_details = get_power_generating_station($application_id,$reference_id,$factory_id,$service_id);
			foreach($power_details as $power){
				$powerid = $power->id;
			}
			log_genaration_power($powerid, $referenceno, $serviceid);
			
			$manager_details = get_all_manager_data($application_id,$service_id,$factory_id,$reference_id);
			foreach($manager_details as $manager){
				$managerid = $manager->id;
				log_genaration_manager($managerid, $referenceno, $serviceid);
			}
			$occupier_details = get_all_occupier_data($application_id,$service_id,$factory_id,$reference_id);
			
			foreach($occupier_details as $occupier){
				$occupierid = $occupier->id;
				log_genaration_occupier($occupierid, $referenceno, $serviceid);
			}
			
			$director_details = get_director_details_service($application_id,$service_id,$factory_id,$reference_id);
			foreach($director_details as $director){
				$directorid = $director->id;
				log_genaration_director($directorid, $referenceno, $serviceid);
			}
			
			$manufacturing_details = get_manufacturing($application_id,$service_id,$factory_id,$reference_id);
			
			foreach($manufacturing_details as $manufacturing){
				$manufacturingid = $manufacturing->id;
			}
			
			log_genaration_manufacturing($manufacturingid, $referenceno, $serviceid);
			
			$doc_details = get_attached_filename($application_id,$reference_id,$factory_id,$service_id);
			foreach($doc_details as $doc){
				$docid = $doc->id;
				log_genaration_doc($docid, $referenceno, $serviceid);
			}

			 ////ALL Upload document log///////////////
				
			 $all_doc_details = get_caf_upload_doc_all($service_id,$application_id,$factory_id,$reference_id);
			 foreach($all_doc_details as $all_doc){
				 $docid = $all_doc->id;
				 log_genaration_upload_doc($docid, $referenceno, $serviceid);
			 }
			
			
			$application_number = create_registration_application($serviceid);
			
			//$approval_status 	= 	array('application_status' => 'F','service_id' => $serviceid,'reference_number' => $referenceno,'renewal_dim_appoved' =>$ques_type,'period_for_renewal'=>$renewal_for_period,'factory_reg_identification_number'=>$application_number);
			$approval_status 	= 	array('application_status' => 'In','service_id' => $serviceid,'reference_number' => $referenceno,'renewal_dim_appoved' =>$ques_type,'period_for_renewal'=>$renewal_for_period);
			
			$queryapp	=	db_update('fa_cafa');
			$queryapp	->	fields($approval_status);
			$queryapp	->	condition('id',$application_id,'=');
			$queryapp	->	condition('factory_typeid',$factory_id,'=');
			$queryapp	->	condition('reference_number',$reference_id,'=');
			$queryapp	->	execute();
		
			year_calculation_for_license_period($renewal_date,$renewal_for_period,$serviceid,$factory_id,$referenceno,$application_id);
			
									//drupal_goto('applicant/application-display-registration/'.encryption_decryption_fun('encrypt',$serviceid).'/'.encryption_decryption_fun('encrypt',$factory_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$referenceno));
		//	drupal_goto('applicant/fees-license/'.encryption_decryption_fun('encrypt',$serviceid).'/'.encryption_decryption_fun('encrypt',$factory_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$referenceno));
		

		
		drupal_goto('applicant/caf-online-renew/apply-online-renewal-service/'.encryption_decryption_fun('encrypt',$serviceid).'/'.encryption_decryption_fun('encrypt',$factory_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$number).'/'.encryption_decryption_fun('encrypt',$number_date).'/'.encryption_decryption_fun('encrypt',$flag));
	}
	
	if($telmak_migrated_flag_hidden != 'N' && $ques_type == 0){
	
		log_genaration_caf($application_id);
		$referenceno 		= created_referenceno();
		$serviceid 			= 3;
			
		$worker_details = get_worker_details_service($service_id,$factory_id,$application_id,$reference_id);
		foreach($worker_details as $worker){
			$workerid = $worker->id;
		}
		log_genaration_worker($workerid,$referenceno,$serviceid);
	
			
		$power_details = get_power_generating_station($application_id,$reference_id,$factory_id,$service_id);
		foreach($power_details as $power){
			$powerid = $power->id;
		}
		log_genaration_power($powerid, $referenceno, $serviceid);
			
		$manager_details = get_all_manager_data($application_id,$service_id,$factory_id,$reference_id);
		foreach($manager_details as $manager){
			$managerid = $manager->id;
			log_genaration_manager($managerid, $referenceno, $serviceid);
		}
		$occupier_details = get_all_occupier_data($application_id,$service_id,$factory_id,$reference_id);
			
		foreach($occupier_details as $occupier){
			$occupierid = $occupier->id;
			log_genaration_occupier($occupierid, $referenceno, $serviceid);
		}
			
		$director_details = get_director_details_service($application_id,$service_id,$factory_id,$reference_id);
		foreach($director_details as $director){
			$directorid = $director->id;
			log_genaration_director($directorid, $referenceno, $serviceid);
		}
			
		$manufacturing_details = get_manufacturing($application_id,$service_id,$factory_id,$reference_id);
			
		foreach($manufacturing_details as $manufacturing){
			$manufacturingid = $manufacturing->id;
		}
		
		log_genaration_manufacturing($manufacturingid, $referenceno, $serviceid);
		
		$doc_details = get_attached_filename($application_id,$reference_id,$factory_id,$service_id);
		foreach($doc_details as $doc){
			$docid = $doc->id;
			log_genaration_doc($docid, $referenceno, $serviceid);
		}

		 ////ALL Upload document log///////////////
				
		 $all_doc_details = get_caf_upload_doc_all($service_id,$application_id,$factory_id,$reference_id);
		 //print_r($all_doc_details);die();
		 foreach($all_doc_details as $all_doc){
			 $docid = $all_doc->id;
			 log_genaration_upload_doc($docid, $referenceno, $serviceid);
		 }



		$application_number = create_registration_application($serviceid);
		
			$approval_status 	= 	array('application_status' => 'F','service_id' => $serviceid,'reference_number' => $referenceno,'renewal_dim_appoved' =>$ques_type,'period_for_renewal'=>$renewal_for_period,'factory_reg_identification_number'=>$application_number);
		
		$queryapp	=	db_update('fa_cafa');
		$queryapp	->	fields($approval_status);
		$queryapp	->	condition('id',$application_id,'=');
		$queryapp	->	condition('factory_typeid',$factory_id,'=');
		$queryapp	->	condition('reference_number',$reference_id,'=');
		$queryapp	->	execute();
	
		 $status 					=  'F';
	 	$array_field  				= "factory_name,"."ownership_type,"."factory_pan,"."gstin_no,"."udyog_aadhaar,"."enargy_no,"."cin_no,"."plan_approval_no,"."plan_approval_date,"."zone_name,"."factory_headoffice,"."telephone_no,"."mobile_no,"."fax_no,email_no,"."owner_name,"."premises_address,"."wbpcb_id,"."wbpcb_reference_id,"."wbpcb_reference_date,"."intimation_id,"."date_of_amenability_id,"."period_for_application_id,"."previous_name_id,"."worker_details,"."power_details,"."manager_details,"."occupier_details,"."director_details,"."nature_details,"."document_details";
		$cafa_field = array(
			'app_id'			=> $application_id,
			'factory_type' 		=> $factorytype_id,
			'reference_no' 	 	=> $referenceno,
			'service_id'		=> $serviceid,
			'fieldname'			=> $array_field,
			'application_status'=> $status
		);
		//print_r($cafa_field);die();
	db_insert('fa_caf_check_point')->fields($cafa_field)->execute();
	remark_input($referenceno,$application_id,'F','Application sucessfully completed but payment pocess is pending')	;
		
	drupal_goto('applicant/caf-online-renew/apply-online-renewal-service/'.encryption_decryption_fun('encrypt',$serviceid).'/'.encryption_decryption_fun('encrypt',$factory_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$referenceno));
	
	
	}*/
	
	//DONE//
}

?>