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
			"1" 	=> "Renew the license without any change",
			"0" 	=> "Renew the license with any change",
	);
				
	$form['renewal_ques'] = array(
			'#type' 			=> 'fieldset',
			'#title' 			=> t('Renewal Information'),
			'#collapsible' 		=> FALSE, // Added
			'#collapsed' 		=> FALSE,  // Added
	);	
	$form['renewal_ques']['ques_type'] 	= array(
			'#prefix' 			=> '<div class="row"><div class="box box-info"><div class="box-body">
										<div class="col-md-12 col-xs-12"><label class="select label-block">',
			'#suffix' 			=> '</label></div>',
			'#title'			=>	t('Please'),
			'#type' 			=> 'radios',
			'#required' 		=> TRUE,
			'#options' 			=> $ques,
			'#ajax'				=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',			
										'callback'		=> 'get_ajax_load_ques',
										'progress'		=>	array(
											'type'		=>'throbber',
											'message'	=>t('loading'),
										),
								)
	);
		 
	$form['renewal_ques']['renewal_date'] 	= array(
		'#prefix' 			=> '<div id ="renewal_from_date_id">',
		'#suffix' 	 		=> '</div>',		
	);
	
	$form['renewal_ques']['renewal_for_period'] 	= array(
		'#prefix' 			=> '<div id ="renewal_for_period_id">',
		 '#suffix' 	 		=> '</div>',
	);
	

		 
	$value_ques_type = isset($form_state['values']['ques_type'])? $form_state['values']['ques_type'] : '';
	$form['ans_ques_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => encryption_decryption_fun('encrypt',$value_ques_type)
    );
	
	if($value_ques_type == 1){
		$form['renewal_ques']['renewal_date'] 	= array(
		  	'#prefix' 			=> '<div class="col-md-6 col-xs-6" id ="renewal_from_date_id">',
		  	'#suffix' 	 		=> '</div>',
			'#type' 			=> 'textfield',
			'#title'			=>	t('Last Renewal Date/ Registration Date'),
			'#default_value'	=> !empty($plan_license_date)?$plan_license_date:$plan_registration_date,
			'#attributes' 		=> array('class'=>array('form-control')),
			'#required' 		=> TRUE,
			);
				
		$form['renewal_ques']['renewal_for_period'] 	= array(
			'#prefix' 			=> '<div class="col-md-6 col-xs-6" id ="renewal_for_period_id">',
		  	'#suffix' 	 		=> '</div>',
			'#type' 			=> 'textfield',
			'#title'			=>	t('Renewal for how many years'),
			'#default_value'	=> $period_for_renewal,
			'#required' 		=> TRUE,
			'#description'		=> '<span style="color:red";>(N.B.:- Maximun 15 years)</span>',
			);	
	}
	
	$form['renewal_ques']['submit'] = array (
	  		'#prefix' 	=> '<div id="submit_div">',
		 	'#suffix' 	=> '</div>',
	  		'#attributes' => array('class' => array('btn btn-success pull-right'), 'onclick' => 'if(!confirm("Are you sure to continue ?")){return false;}'),
	  		'#type' 	=> 'submit',
	 		'#value'	=> 'Apply'
	);
	$form['renewal_ques']['markup_end'] = array(
           '#suffix' => '</div></div></div>',
           '#type' => 'markup',
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
	$factory_address_location	= $get_all_data['addrline'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_factory_location);
	$getdata_headoffice_address	= array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
	$headoffice_address			= $get_all_data['addrline_off'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_headoffice_address);
	$getdata_owner_address		= array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
	$owner_address_details		= !empty($get_all_data['addrline_premises'])?$get_all_data['addrline_premises'].',':'';
	if($get_all_data['owner_country']==NULL)
	{
		$get_all_data['owner_country']=99;
	}
	
	$getdata_communication_address = array('district_comm','subdivision_comm','areatype_comm','block_comm','panchayat_comm','policestation_comm','pincodecomm','state_comm','postoffice_comm');
	$communication_address 		= $get_all_data['addrline_comm'].',
		<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_communication_address);
		
	$owner_address_details.= $get_all_data['owner_country_address'].',<br/>'.country_name($get_all_data['owner_country']);
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
		
		$director_details	=	$base_root.$base_path.'view-director-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_director		=	ctools_modal_text_button(t('View Director(s)'), $director_details ,t('View Details)')) ;	
		
			
		$documents_details	=	$base_root.$base_path.'view-documents-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_documents		=	ctools_modal_text_button(t('View Documents list'), $documents_details ,t('View Details)')) ;
		
		$manager_details	=	$base_root.$base_path.'view-manager-applicant/nojs/'.$service_id.'/'.$factory_typeid.'/'.$application_id.'/'.$reference_number; 	
		$link_manager		=	ctools_modal_text_button(t('View Manager(s)'), $manager_details ,t('View Details)')) ;
		
		
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
			$type_of_application ='Plan Approval Number:-'.$plan_approval_number.' dated on '.date('dS M Y', strtotime($plan_approval_date));
				$application_frm_id 	= 	$get_all_data['uploaded_pdf'];
				$application_form_url 	= 	get_uploaded_document_url($application_frm_id);
				
				if(!empty($application_form_url)){ 
						$url 						= explode('//',$application_form_url);
						$doc_url					= $url[1];
						$application_form_view		='<a title = "Click here to view" href="'.$GLOBALS['base_url'].'/sites/default/files/'.$doc_url.'" target="_blank"><i class="ace-icon fa fa-file-pdf-o bigger-130"></i></a>'; 
	
				}
		}
		if($service_id_pre_application == 2 ){ 
		
				$type_of_application =' Plan Approval Number:-'.$plan_approval_number.' dated on '.date('dS M Y', strtotime($plan_approval_date)).'<br/>Registration Number:-'.$plan_registration_number.' dated on '.date('dS M Y', strtotime($plan_registration_date)).'<br/>'.'Renewal Number:- '.$plan_licesne_number.' dated on '.date('dS M Y', strtotime($plan_license_date)).'<br/><span style="color:red">License Expiring on dated:- '.date('dS M Y', strtotime($get_all_data['license_valid_upto'])).'</span>';
				 
		}
		if($service_id_pre_application >= 3 ){ 
		
				 $type_of_application =' Plan Approval Number:-'.$plan_approval_number.' dated on '.date('dS M Y', strtotime($plan_approval_date)).'<br/>Registration Number:-'.$plan_registration_number.' dated on '.date('dS M Y', strtotime($plan_registration_date)).'<br/>'.'Last Renewal Number:- '.$plan_licesne_number.' dated on '.date('dS M Y', strtotime($plan_license_date)).'<br/><span style="color:red">License Expiring on dated:- '.date('dS M Y', strtotime($get_all_data['license_valid_upto'])).'</span>';
		}
	$application_from = '<a href='.file_create_url(get_uploaded_document_url($get_all_data['uploaded_pdf'])).' target= "_BLANK" onclick = "popIt(this.href);return false;">Click to View</a>';

	if($get_all_data['wbpcb_category_name']==1){$consent ='Red'; $wbpcb_reference_no = !empty($get_all_data['wbpcb_reference_no'])?$get_all_data['wbpcb_reference_no']:'Nil';$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));}
			 if($get_all_data['wbpcb_category_name']==2){ $consent ='Green'; $wbpcb_reference_no = !empty($get_all_data['wbpcb_reference_no'])?$get_all_data['wbpcb_reference_no']:'Nil';$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));
			}
			 if($get_all_data['wbpcb_category_name']==3){$consent ='Orange';$wbpcb_reference_no = !empty($get_all_data['wbpcb_reference_no'])?$get_all_data['wbpcb_reference_no']:'Nil';$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));}
			
			 if($get_all_data['wbpcb_category_name']== 4){
				$consent ='White'; 
				$wbpcb_reference_no = 'N/A'; 
				$wbpcb_ref_date = 'N/A';
				$file = $get_all_data['wbpcb_intimation_letter'];
				$file_url = '<a href='.file_create_url(get_uploaded_document_url($file)).' target= "_BLANK" onclick = "popIt(this.href);return false;">View</a>';
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
				<tr><td>(ix). CIN No</td><td>'.$cin_no.'</td></tr>
				<tr><td>(x). Plan Approval number </td><td>'.$plan_approval_no.'</td></tr>
				<tr><td>(xi). Plan Approval Date </td><td>'.$plan_approval_date.'</td></tr>
				
				<tr><td colspan="2" class="sub-title">B. Location of Factory </td></tr>
				<tr><td>(i). Zone</td><td>'.$factory_zone_date['zone_name'].'</td></tr>
				<tr><td>(ii). Address</td><td>'.$factory_address_location.'</td></tr>
				
				<tr><td colspan="2" class="sub-title">C. Address of the Registered office / Head office</td></tr>
				<tr><td>(i). Address</td><td>'.$headoffice_address.'</td></tr>
				<tr><td>(ii). Telephone No</td><td>'.$get_all_data['comm_telephone'].'</td></tr>
				<tr><td>(iii). Mobile No</td><td>'.$get_all_data['comm_mobile'].'</td></tr>
				<tr><td>(iv). Fax No</td><td>'.$comm_fax.'</td></tr>
				<tr><td>(iv). Email Id</td><td>'.$get_all_data['comm_email'].'</td></tr>
				
				<tr><td colspan="2">D. Address to which communications relating to the factory may be sent</td></tr>
				<tr><td>(i).Address</td><td>'.$communication_address.'</td></tr>
				
				<tr><td colspan="2" class="sub-title">E. Details of owner of the premises occupied as a factory</td></tr>
				<tr><td>(i). Name of the owner</td><td>'.$owner_name.'</td></tr>
				<tr><td>(ii). Address</td><td>'.$owner_address.'</td></tr>
				<tr><td  class="sub-title">F. Factory Identification according to WBPCB</td><td>'.$details.'</td></tr>
				<tr><td colspan="2" class="sub-title">G. State the period of license</td></tr>
				<tr><td>(i). Date from which the premises is occupied or been taken into use as factory </td><td>'.$date_amenability.'</td>
				<tr><td>(ii). State the period of license required </td><td>'.$period_for_application.'</td></tr>
				<tr><td>(iii). Whethere any changes name and ownership details of factory </td><td>'.$is_previous.$view.'</td></tr>
				<tr><td colspan="2" class="sub-title">H. Worker Details</td></tr>
				<tr><td>(i). Maximum number of workers employed or to be employed in the factory</td><td>'.$link_t.'</td></tr>
				<tr><td colspan="2" class="sub-title">I. Power Details</td></tr>
				<tr><td>(i). Installed Power or to be installed power </td><td>'.$power_details.'</td></tr>
				<tr><td colspan="2" class="sub-title">J. Manager Details</td></tr>
				<tr><td>(i). Manager Details</td><td>'.$link_manager.'</td></tr>
				<tr><td colspan="2" class="sub-title">K. Occupier Details</td></tr>
				<tr><td>(i). View occupier details</td><td>'.$link_occuiper.'</td></tr>
				<tr><td colspan="2" class="sub-title">L. Director Details</td></tr>
				<tr><td>(i). View director details</td><td>'.$link_director.'</td></tr><tr>
				<td colspan="2" class="sub-title">M. Manufacturing process</td></tr>
				<tr><td>(i). Carried/to be carried on the factory</td><td>'.$nature_work.'</td></tr>
				<td colspan="2" class="sub-title">N. Uploaded Documents</td></tr>
				<tr><td>(i). View uploaded documetns</td><td>'.$link_documents.'</td></tr>';
		$output .= '<tr>
					<td colspan="2" class="sub-title">O. Application Forms</td>
				</tr>
				  <tr><td>(i). View uploaded documetns</td><td>'.$application_from.'</td></tr>';
			
				$i=1;
				foreach($pdfs_files as $pdfs){
				$output.='
				<tr>
						<td>('.$i.').'.$pdfs->application_period_year.'</td>
						<td>'.$pdfs->type_of_application_from.' --- '.l('View', file_create_url(get_uploaded_document_url($pdfs->pdf_id)), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('button')))).'</td>
						
					</tr>';
					$i++;
					}
				
	$output .= '</table></div></div></div>';
	return $output;
}

function get_ajax_load_ques($form, $form_state){
	$commands = array();
	$commands[] = ajax_command_replace('#renewal_from_date_id', drupal_render($form['renewal_ques']['renewal_date']));
	$commands[] = ajax_command_replace('#renewal_for_period_id', drupal_render($form['renewal_ques']['renewal_for_period']));
	
	return array('#type' => 'ajax', '#commands' => $commands);
}

function preview_for_apply_eservice_renewal_submit($form, &$form_state){
	global $user;
    $userid 			= $user->uid;
    $val    			= $form_state['values'];
	//print_r($val);die;
	$application_id 	= encryption_decryption_fun('decrypt', $val['applicationid_hidden']); 
	$ans_ques_hidden 	= encryption_decryption_fun('decrypt', $val['ans_ques_hidden']);
	
	$service_id 		= encryption_decryption_fun('decrypt', $val['serviceid_hidden']); 
	$factory_id 		= encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']); 
	$reference_id 		= encryption_decryption_fun('decrypt', $val['refnumber_hidden']);
	$renewal_for_period	= $val['renewal_for_period'];
	$ques_type			= $val['ques_type'];
	$renewal_date		= $val['renewal_date'];
	$telmak_migrated_flag_hidden	= encryption_decryption_fun('decrypt', $val['telmak_migrated_flag_hidden']);
	$apply_service		= 3;
	$date_current 		= new DateTime(date('Y-m-d'));
	$date_renew 		= new DateTime($val['renewal_date']);
	
	//echo $ques_type; echo  $telmak_migrated_flag_hidden;
	//die('fjd');
		
	if($ques_type == 1 && $telmak_migrated_flag_hidden == 'N'){
		if($date_current > $date_renew ){
			drupal_goto('applicant/change_list/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_id).'/'.encryption_decryption_fun('encrypt',$apply_service));
		}else{
			
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
			
			
			$application_number = create_registration_application($serviceid);
			
			//$approval_status 	= 	array('application_status' => 'F','service_id' => $serviceid,'reference_number' => $referenceno,'renewal_dim_appoved' =>$ques_type,'period_for_renewal'=>$renewal_for_period,'factory_reg_identification_number'=>$application_number);
			$approval_status 	= 	array('application_status' => 'F','service_id' => $serviceid,'reference_number' => $referenceno,'renewal_dim_appoved' =>$ques_type,'period_for_renewal'=>$renewal_for_period);
			
			$queryapp	=	db_update('fa_cafa');
			$queryapp	->	fields($approval_status);
			$queryapp	->	condition('id',$application_id,'=');
			$queryapp	->	condition('factory_typeid',$factory_id,'=');
			$queryapp	->	condition('reference_number',$reference_id,'=');
			$queryapp	->	execute();
		
			year_calculation_for_license_period($renewal_date,$renewal_for_period,$serviceid,$factory_id,$referenceno,$application_id);
			
									//drupal_goto('applicant/application-display-registration/'.encryption_decryption_fun('encrypt',$serviceid).'/'.encryption_decryption_fun('encrypt',$factory_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$referenceno));
			drupal_goto('applicant/fees-license/'.encryption_decryption_fun('encrypt',$serviceid).'/'.encryption_decryption_fun('encrypt',$factory_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$referenceno));
		}
	}
	
	if($ques_type == 0 && $telmak_migrated_flag_hidden == 'N'){
		
		drupal_goto('applicant/change_list/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_id).'/'.encryption_decryption_fun('encrypt',$apply_service));
			//drupal_goto('applicant/application-display-registration/'.encryption_decryption_fun('encrypt',$serviceid).'/'.encryption_decryption_fun('encrypt',$factory_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$referenceno));
		
		//$approval_status 	= 	array('application_status' => 'In','service_id' => $serviceid,'reference_number' => $referenceno,'renewal_dim_appoved' =>$ques_type,'period_for_renewal'=>$renewal_for_period,'factory_reg_identification_number'=>$application_number);
	}
	
	if($telmak_migrated_flag_hidden != 'N' && $ques_type == 1){
		//die('Telmac data');	//drupal_goto('applicant/change_list/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_id).'/'.encryption_decryption_fun('encrypt',$apply_service));

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
		$application_number = create_registration_application($serviceid);
		
		//$approval_status 	= 	array('application_status' => 'In','service_id' => $serviceid,'reference_number' => $referenceno,'renewal_dim_appoved' =>0,'factory_reg_identification_number'=>$application_number);
		$approval_status 	= 	array('application_status' => 'In','service_id' => $serviceid,'reference_number' => $referenceno,'renewal_dim_appoved' =>0);
		
		$queryapp	=	db_update('fa_cafa');
		$queryapp	->	fields($approval_status);
		$queryapp	->	condition('id',$application_id,'=');
		$queryapp	->	condition('factory_typeid',$factorytype_id,'=');
		$queryapp	->	condition('reference_number',$reference_no,'=');
		$queryapp	->	execute();
		
		
		$status 			=  'In';
	 	$array_field  		= "factory_name,"."ownership_type,"."factory_pan,"."gstin_no,"."udyog_aadhaar,"."enargy_no,"."cin_no,"."plan_approval_no,"."plan_approval_date,"."zone_name,"."factory_headoffice,"."telephone_no,"."mobile_no,"."fax_no,email_no,"."owner_name,"."premises_address,"."wbpcb_id,"."wbpcb_reference_id,"."wbpcb_reference_date,"."intimation_id,"."date_of_amenability_id,"."period_for_application_id,"."previous_name_id,"."worker_details,"."power_details,"."manager_details,"."occupier_details,"."director_details,"."nature_details,"."document_details";
		$data_field = array(
			'app_id'			=> $application_id,
			'factory_type' 		=> $factory_id,
			'reference_no' 	 	=> $referenceno,
			'service_id'		=> $serviceid,
			'fieldname'			=> $array_field,
			'application_status'=> $status
		);
		//print_r($cafa_field);die();
		db_insert('fa_caf_check_point')->fields($data_field)->execute();
	
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
		$application_number = create_registration_application($serviceid);
		
			$approval_status 	= 	array('application_status' => 'In','service_id' => $serviceid,'reference_number' => $referenceno,'renewal_dim_appoved' =>$ques_type,'period_for_renewal'=>$renewal_for_period,'factory_reg_identification_number'=>$application_number);
		
			$queryapp	=	db_update('fa_cafa');
			$queryapp	->	fields($approval_status);
			$queryapp	->	condition('id',$application_id,'=');
			$queryapp	->	condition('factory_typeid',$factory_id,'=');
			$queryapp	->	condition('reference_number',$reference_id,'=');
			$queryapp	->	execute();
	
			$status 					=  'In';
			$array_field  				= "factory_name,"."ownership_type,"."factory_pan,"."gstin_no,"."udyog_aadhaar,"."enargy_no,"."cin_no,"."plan_approval_no,"."plan_approval_date,"."zone_name,"."factory_headoffice,"."telephone_no,"."mobile_no,"."fax_no,email_no,"."owner_name,"."premises_address,"."wbpcb_id,"."wbpcb_reference_id,"."wbpcb_reference_date,"."intimation_id,"."date_of_amenability_id,"."period_for_application_id,"."previous_name_id,"."worker_details,"."power_details,"."manager_details,"."occupier_details,"."director_details,"."nature_details,"."document_details";
			$data_field = array(
			'app_id'			=> $application_id,
			'factory_type' 		=> $factorytype_id,
			'reference_no' 	 	=> $referenceno,
			'service_id'		=> $serviceid,
			'fieldname'			=> $array_field,
			'application_status'=> $status
			);
		//print_r($cafa_field);die();
		db_insert('fa_caf_check_point')->fields($data_field)->execute();
		
		drupal_goto('applicant/caf-online-renew/apply-online-renewal-service/'.encryption_decryption_fun('encrypt',$serviceid).'/'.encryption_decryption_fun('encrypt',$factory_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$referenceno));
	
	}
	
	//DONE//
}

?>