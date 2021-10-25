<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function caf_form_registrstion_factory_information($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$referenceno)
{
	
    global $base_root, $base_path,$user;
    	$userid = $user->uid;
   		$rid= get_role_id($userid);
    	$form            	= array();
	 	$service_id      	= encryption_decryption_fun('decrypt', $serviceid);
		$factory_type_id 	= encryption_decryption_fun('decrypt', $factory_typeid);
		$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
		$reference_no 		= encryption_decryption_fun('decrypt', $referenceno);
		$license_period 	= licence_journal_detalis($application_id,$service_id,$factory_type_id,$reference_no);

foreach($license_period as $row_license_period){
	$service_year .= $row_license_period->service_year.',';
	$licence_fees +=  $row_license_period->schedule_fees+$row_license_period->late_fees;
}
	 
    $form['#attributes'] 	= array('enctype' => "multipart/form-data");
	
	$form['applicationid_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $applicationid
    );
	$form['serviceid_hidden']     = array(
        '#type' => 'hidden',
        '#default_value' => $serviceid
    );
    $form['factorytypeid_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $factory_typeid
    );
	$form['referenceno_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $referenceno
    );
	
  
        $get_fa_cafa           = get_fa_cafa($application_id);
       
        $factory_name          = $get_fa_cafa['factory_name'];
        $factory_previous_name = $get_fa_cafa['factory_previous_name'];
        $nearest_landmark      = $get_fa_cafa['nearest_landmark'];
		$factory_zone		   = $get_fa_cafa['factory_zone'];
		$factory_pan           = $get_fa_cafa['factory_pan'];
		$ownership_type		   = $get_fa_cafa['factory_owershiptype'];
		$gstin_no 			   = $get_fa_cafa['gstin_no'];
		$udyog_aadhaar         = $get_fa_cafa['udyog_aadhaar'];		
		$enargy_meter_no 	   = $get_fa_cafa['enargy_no'];		
		$cin_no 			   = $get_fa_cafa['cin_no'];	
		$trade_license_no	   = $get_fa_cafa['trade_license_no'];
		
        $factory_pincode       = $get_fa_cafa['pincode'];
        $factory_state         = $get_fa_cafa['state'];
        $factory_district      = $get_fa_cafa['district'];
        $factory_subdivision   = $get_fa_cafa['subdivision'];
        $factory_areatype      = $get_fa_cafa['areatype'];
        $factory_block         = $get_fa_cafa['block'];
        $factory_panchayat     = $get_fa_cafa['panchayat'];
        $factory_policestation = $get_fa_cafa['policestation'];
        $factory_postoffice    = $get_fa_cafa['postoffice'];
        $factory_addrline      = $get_fa_cafa['addrline'];
		$estate_type			= $get_fa_cafa['estate_type'];
        
        $office_pincode           = $get_fa_cafa['pincodeoff'];
        $office_state_off         = $get_fa_cafa['state_off'];
        $office_district_off      = $get_fa_cafa['district_off'];
        $office_subdivision_off   = $get_fa_cafa['subdivision_off'];
        $office_areatype_off      = $get_fa_cafa['areatype_off'];
        $office_block_off         = $get_fa_cafa['block_off'];
        $office_panchayat_off     = $get_fa_cafa['panchayat_off'];
        $office_policestation_off = $get_fa_cafa['policestation_off'];
        $office_postoffice_off    = $get_fa_cafa['postoffice_off'];
        $office_addrline_off      = $get_fa_cafa['addrline_off'];

        $factory_country_address = $get_fa_cafa['addrline_off_other'];
       
        $comm_telephone     	  = !empty($get_fa_cafa['comm_telephone'])?$get_fa_cafa['comm_telephone']:'Not Available';
		$comm_mobile     	      = !empty($get_fa_cafa['comm_mobile'])?$get_fa_cafa['comm_mobile']:'Not Available';
		$comm_fax     	          = !empty($get_fa_cafa['comm_fax'])?$get_fa_cafa['comm_fax']:'Not Available';
		$comm_email     	      =!empty($get_fa_cafa['comm_email'])?$get_fa_cafa['comm_email']:'Not Available'; 
		$comm_alt_mobile 		  =  !empty($get_fa_cafa['comm_alt_mobile'])?$get_fa_cafa['comm_alt_mobile']:'Not Available';
		
		$communication_adress_same_factory  = $get_fa_cafa['communication_adress_same_factory'];
		$reg_adress_same_factory_comm	  	= !empty($get_fa_cafa['reg_adress_same_factory_comm'])?$get_fa_cafa['reg_adress_same_factory_comm']:1;
		//Communication Address //
		$office_pincode_comm 				= $get_fa_cafa['pincodecomm'];
		$office_state_comm 					= $get_fa_cafa['state_comm'];
		$office_district_comm 				= $get_fa_cafa['district_comm'];
		$office_subdivision_comm 			= $get_fa_cafa['subdivision_comm'];
		$office_areatype_comm 				= $get_fa_cafa['areatype_comm'];
		$office_block_comm 					= $get_fa_cafa['block_comm'];
		$office_panchayat_comm 				= $get_fa_cafa['panchayat_comm']; 
		$office_policestation_comm 			= $get_fa_cafa['policestation_comm']; 
		$office_postoffice_comm 			= $get_fa_cafa['postoffice_comm']; 
		$office_addrline_comm 				= $get_fa_cafa['addrline_comm'];
		$reference_number					= $get_fa_cafa['reference_number'];
        $application_status					= $get_fa_cafa['application_status'];
        $is_backlog							= $get_fa_cafa['is_backlog'];
		$date_of_amenability                = $get_fa_cafa['date_of_amenability'];
		$period_for_application             = $get_fa_cafa['period_for_application'];
			
		$wbpcb_category_name 				= $get_fa_cafa['wbpcb_category_name'];
		$wbpcb_reference_no 				= $get_fa_cafa['wbpcb_reference_no'];
		$wbpcb_ref_date 					= $get_fa_cafa['wbpcb_ref_date'];
		$wbpcb_intimation_letter    		= $get_fa_cafa['wbpcb_intimation_letter'];
		$backlog_plan_approval_date			= $get_fa_cafa['backlog_plan_approval_date'];
		$backlog_plan_approval_no			= $get_fa_cafa['backlog_plan_approval_no'];
		$plan_approval_no					= $get_fa_cafa['factory_plan_approval_number'];
		$plan_approval_date					= $get_fa_cafa['plan_approval_date'];
		$nearest_landmark    		      	= !empty($get_fa_cafa['nearest_landmark'])?$get_fa_cafa['nearest_landmark']:'Not Available';
		$addrline_off_other					= $get_fa_cafa['addrline_off_other'];
		$country_code						= $get_fa_cafa['country_code'];
		$country_owner						= $get_fa_cafa['country_premises'];
		$country_premises_address			= $get_fa_cafa['addrline_premises'];
		$mouza_name							= !empty($get_fa_cafa['mouza_name'])?$get_fa_cafa['mouza_name']:'Not Available';
		$jl_number							= !empty($get_fa_cafa['jl_no'])?$get_fa_cafa['jl_no']:'Not Available';	
		$is_chemical						= !empty($get_fa_cafa['is_chemical'])?$get_fa_cafa['is_chemical']:'0';	
    	$application_status					= !empty($get_fa_cafa['application_status'])?$get_fa_cafa['application_status']:'';
		$recomended_date_of_amenability	= $get_fa_cafa['recomended_date_of_amenability'];

	$form['wbpcb_category_name_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $wbpcb_category_name
    );
	$form['is_chemical_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $is_chemical
    );
   
	$remark_fetch = get_checking($application_id,$service_id,$factory_type_id,$reference_no);
	$verify_details = $remark_fetch['verify_details'];
	$doc_verify 	= $remark_fetch['doc_verify'];
	
	if(!empty($verify_details)){
		$remark_field = explode(',', $verify_details);
		$doc_verify_field = explode(',', $doc_verify);
		//print_r($doc_verify_field);die;
		foreach ($remark_field as $fieldname){ 
			//echo $fieldname;
			if($fieldname == 'factory_name'){ $factory_name_ck = 1;}
			if($fieldname == 'factory_pan'){ $factory_pan_ck = 1;}
			if($fieldname == 'gstin_no'){ $gstin_no_ck = 1;}
			if($fieldname == 'udyog_aadhaar'){ $udyog_aadhaar_ck =1;}
			if($fieldname == 'enargy_no'){ $enargy_no_ck = 1;}
			if($fieldname == 'cin_no'){ $cin_no_ck = 1;}
			if($fieldname == 'trade_no'){ $trade_no_ck = 1;}
			if($fieldname == 'factory_previous_name'){ $factory_previous_name_ok = 1;}
			if($fieldname == 'plan_approval_no'){ $plan_approval_ck = 1;}
			
			if($fieldname == 'zone_name'){ $zone_name_ck =1;}
			
			if($fieldname == 'factory_headoffice'){ $factory_headoffice_ck = 1;}
			if($fieldname == 'factory_communication'){ $factory_communication_ck = 1;}
			
			if($fieldname == 'telephone_no'){ $telephone_no_ck = 1;}
			if($fieldname == 'mobile_no'){ $mobile_no_ck 	= 1;}
			if($fieldname == 'fax_no'){ $fax_no_ck 	= 1;}
			if($fieldname == 'email_no'){ $email_no_ck 	= 1;}
			if($fieldname == 'wbpcb_id'){ $wbpcb_id_ck = 1;}
			if($fieldname == 'date_of_amenability_id'){ $date_of_amenability_id_ck = 1;}
			if($fieldname == 'factory_previous_name'){ $previous_name_id_ck = 1;}
			if($fieldname == 'worker_details'){ $worker_details_ck = 1;}
			if($fieldname == 'power_details'){ $power_details_ck = 1;}
			if($fieldname == 'nature_details'){ $nature_details_ck = 1;}
			
			
			
		
		//print_r($remark_field);die;
	}
	    
	}
	

	/********** Factory Information - Start **********/
    
    $form['header']            = array(
        '#markup' => t('<div class="content"><h1><font color ="red">UNDER DEVELOPMENT</font></h1>
		<h3>Application for Registration and Grant of Licence.All inputs are provided by applicant only.
All inputs are to be verified by officials</h3>')
    );
	
	 $form['factory_part_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('A. Factory Information'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
    
	
	if($ownership_type == 'pv'){
		$ownership_type_name = "Pvt Ltd Company";
	}if($ownership_type == 'ltd'){
		$ownership_type_name = "Ltd Company";
	}if($ownership_type == 'par_firm'){
		$ownership_type_name = "Partnership Firm";
	}if($ownership_type == 'pro_firm'){
		$ownership_type_name = "Proprietorship Firm";
	}if($ownership_type == 'llp'){
		$ownership_type_name = "Limited Liability Partnership";
	}if($ownership_type == 'cooperative'){
		$ownership_type_name =  "Co-operative";
	}if($ownership_type == 'registered'){
		$ownership_type_name =  "Registered Society under Society Register";
	}if($ownership_type == 'govt'){
		$ownership_type_name =  "Govt.";
	}if($ownership_type == 'psu'){
		$ownership_type_name =  "PSU.";
	}if($ownership_type == 'localbody'){
		$ownership_type_name =  "Local Body.";
	}if($ownership_type == 'others'){
		$ownership_type_name =  "Others.";
	}
	
  $form['factory_part_info']['factory_name_show'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div>',
        '#type' 			=> 'markup',
        '#markup' 			=>'(i)Name of the factory -' .$factory_name.'('.$ownership_type_name.')',
		
    );
	 $form['factory_part_info']['factory_name'] = array(
	  	'#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'factory_name',
        '#default_value' 	=> $factory_name_ck ,
        '#title' 			=> t('Is Factory Name Correct?'),
    );
	
	$identity_flag = 'factory_name';
	$irregularities_details_name =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factory_type_id,$service_id);
			
		$form['factory_part_info']['factory_name_irregularities_table'] = array(
	   
	
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12"><div id="factory_name_chceking_id">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>Irregularities for Scrutiny of Applications about Name of the Factory </th>
								<th >Action</th>
								
							</tr>'
					);
	
		$irregularities_name = array('Agree'=>'Agree','NotAgree'=>'Not Agree');
		if(!empty($irregularities_details_name)){
		foreach($irregularities_details_name as $row_irregularities_details_name){
			$form['factory_part_info']['factory_name_irregularities_'.$row_irregularities_details_name->id] = array(
			'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12"><div id="factory_name_irregularities_'.$row_irregularities_details_name->id.'">',
       		'#suffix' 			=> '</td></div></div>',
			'#type' 			=> 'textarea',
			'#rows'				=> 2,
			'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=>$row_irregularities_details_name->irregularities,
		);
	          
		$form['factory_part_info']['factory_adchk_'.$row_irregularities_details_name->id] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12"><div id="factory_adchk_'.$row_irregularities_details_name->id.'">',
       		 '#suffix' 			=> '</div></tr></td></div>',
			 '#type' 			=> 'radios',
    		 '#options'         => $irregularities_name,
			 '#default_value' 	=>$row_irregularities_details_name->remark_by_ad,
  		);
		
	}
		
		
	}else{
		$form['factory_part_info']['factory_name_irregularities_1'] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			 '#type' 			=> 'textfield',
			'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=>'1.Appropriate documents in support of Change of Name of the Factory have not been uploaded with the application',
			
		);
	          
		$form['factory_part_info']['factory_name_chk_1'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></tr></td>',
			 '#type' 			=> 'radios',
    		 '#options'         => $irregularities_name,
			 '#default_value' 	=>'NotAgree',
			 
			
  		);
			
			
		$form['factory_part_info']['factory_name_irregularities_2'] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			 '#type' 			=> 'textarea',
			 '#rows'			=> 2,
			 '#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=>'2. The name of the Factory as mentioned in the Common Application Form does not match with that as per the supporting document– Memorandum & Articles of Association / Partnership Deed / Certificate of Proprietorship / Trade Licence* – uploaded with the application',
			
		);
	          
		$form['factory_part_info']['factory_name_chk_2'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></tr></td>',
			 '#type' 			=> 'radios',
    		 '#options'         => $irregularities_name,
			 '#default_value' 	=>'NotAgree',
			 
			
  		);	
		
	}
			
		$form['factory_part_info']['factory_name_irregularities_end'] 	= array(
			'#suffix' 	=> '</table><div></div>',
		);
		


    $form['factory_part_info']['factory_pan_show'] = array(
        '#prefix' 			=> '</div><div class="row"><div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t($factory_pan_check_data.'(ii). PAN of the Business Establishment / Factory / Company'),
        '#type'				=> 'markup',
        '#markup' 			=>'(ii). PAN of the Business Establishment -' .$factory_pan,
      	'#description'		=>'<font color="#FF0000">(N.B.- Under the Income Tax Act, 1961)</font>'
    );
	$form['factory_part_info']['factory_pan'] = array(
	  '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'factory_pan',
        '#default_value' 	=>$factory_pan_ck ,
        '#title' 			=> t('Is Pan number Correct?'),
		
       
		
    );
    $form['factory_part_info']['gstin_no_show'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t($gstin_no_check_data.'(iii). GSTIN Number:'),
		 '#type' 			=> 'markup',
        '#markup' 			=>'(iii). GSTIN Number -' .$gstin_no,
		
       );
	  $form['factory_part_info']['gstin_no'] = array(
	  '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'gstin_no',
        '#default_value' 	=> $gstin_no_ck,
        '#title' 			=> t('Is GSTIN Number Correct?'),
		
       
		
    );
    $form['factory_part_info']['udyog_aadhaar_show'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div>',
        '#markup' 			=> '(iv).Udyog Aadhaar No:-'.$udyog_aadhaar,
        '#type' 			=> 'markup',
           
      
    );
	 $form['factory_part_info']['udyog_aadhaar'] = array(
	 	 '#prefix'			=> '<div class="col-md-6 col-xs-6">',
       	 '#suffix' 			=> '</div></div>',
       	 '#type' 			=> 'checkbox',
		 '#id'				=> 'udyog_aadhaar',
         '#default_value' 	=> $udyog_aadhaar_ck,
         '#title' 			=> t('Is Udyog Aadhaar No Correct?'),
		 
       
		
    );
    $form['factory_part_info']['trade_license_no_show'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div>',
        '#markup' 			=> t('(v).Trade License No:-'.$trade_license_no),
        '#type' 			=> 'markup',
       
    );

$form['factory_part_info']['trade_no'] = array(
	    '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'trade_no',
        '#default_value' 	=> $trade_no_ck,
        '#title' 			=> t('Is Udyog Aadhaar No Correct?'),
		
       
		
    );
$plan_approval_no = !empty($backlog_plan_approval_no)?$backlog_plan_approval_no:$plan_approval_no;
$plan_approval_date = !empty($backlog_plan_approval_date)?date('d-m-Y',strtotime($backlog_plan_approval_date)):date('d-m-Y',strtotime($plan_approval_date));

    if($factory_type_id == 3){
       $form['factory_part_info']['plan_approval_no_show'] = array(
       '#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div>',
       '#markup' 			=> '(vi). Plan Approval number and approval Date:-Not Available',
       '#type' 				=> 'markup',
      
      
     
   );
   $form['factory_part_info']['plan_approval_no'] = array(
	  	'#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'plan_approval_no',
        '#default_value' 	=> $plan_approval_ck,
        '#title' 			=> t('Is Plan Approval number and date Correct?'),
		
       
		
    );
	}
  
   else{
       $form['factory_part_info']['plan_approval_no_show'] = array(
       '#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div>',
       '#markup' 			=> '(vi). Plan Approval number:-'.$plan_approval_no.',dated on'.$plan_approval_date,
       '#type' 				=> 'markup',
      
      
     
   );
   $form['factory_part_info']['plan_approval_no'] = array(
	    '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'plan_approval_no',
         '#default_value' 	=> $plan_approval_ck,
        '#title' 			=> t('Is Plan Approval number and date Correct?'),
		
       
		
    );
  
   }
   $factory_previous_name = !empty($factory_previous_name)?$factory_previous_name:'Not Available';
 $form['factory_part_info']['factory_previous_name_show'] = array(
            '#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
           '#markup' 			=> '(viii). Previous Name of factory:-'.$factory_previous_name,
          
          
          
       );

	$form['factory_part_info']['factory_previous_name'] = array(
	  	'#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'factory_previous_name',
        '#default_value' 	=> $previous_name_id_ck ,
        '#title' 			=> t('Is factory previous name Correct?'),
		
       
		
    );
	
	$form['factory_part_info']['cin_no_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
		   '#markup' 			=> '(viii). CIN number:-'.$cin_no,
			'#required' 		=> TRUE,
			
		);
	$form['factory_part_info']['cin_no'] = array(
	  	'#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'cin_no',
		'#default_value' 	=> $cin_no_ck ,
        '#title' 			=> t('Is CIN number Correct?'),
		
       
		
    );
	$form['factory_part_info']['enargy_no_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(x).Energy Meter No:-'.$enargy_meter_no,
			'#type' 			=> 'markup',
			
		);
	
	
	$form['factory_part_info']['enargy_no'] = array(
	  	'#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'enargy_no',
        '#default_value' 	=> $enargy_no_ck,
        '#title' 			=> t('Is Energy Meter No Correct?'),
		
       
		
    );
	
	$manufacturing_details = get_manufacturing($application_id,$service_id,$factory_type_id,$reference_no);
	foreach($manufacturing_details as $manufacturing){
		$nature_manufacturing = $manufacturing->nature_manufacturing;
		$manufacturing_id 	  = $manufacturing->id;
	}
	
	$form['nature_worker'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('B. Nature of Manufacturing process'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	$form['nature_worker']['nature_manufacturing'] 	= array(
							 '#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
							 '#suffix' 	 		=> '</div>',
							 '#title'			=>	t('Carried/to be carried on the factory'),
							 '#type' 	 		=> 'markup',
							 '#markup'	=> $nature_manufacturing,
							 
					 	); 
	$form['nature_worker']['nature_details'] = array(
	  	'#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'nature_details',
        '#default_value' 	=>$nature_details_ck,
        '#title' 			=> t('Is Carried/to be carried on the factory Correct?'),
		
       
		
    );
	$identity_flag = 'nature_details';
	$irregularities_details_nature_details =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factory_type_id,$service_id);
	
	$form['nature_worker']['factory_nature_details_irregularities_table'] 	= array(
	   		'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th >Irregularities for Scrutiny of Applications according to Manufacturing Process of the Factory </th>
								<th >Action</th>
								
							</tr>
							'
					);
	if(!empty($irregularities_details_nature_details)){
		foreach($irregularities_details_nature_details as $row_irregularities_details_nature_details){
			$form['nature_worker']['factory_nature_details_irregularities_'.$row_irregularities_details_nature_details->id] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=> $row_irregularities_details_nature_details->irregularities,
			
		);
	
		
	$form['nature_worker']['factory_adchk_'.$row_irregularities_details_nature_details->id] = array(
   			 '#prefix' 				=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 				=> '</div></td></tr>',
			 '#type' 				=> 'radios',
			  '#options'         	=>  $irregularities_name,
    		  '#default_value' 		=>	$row_irregularities_details_nature_details->remark_by_ad,
			  
			
  		);
	
	}
	}else{
		$form['nature_worker']['factory_nature_details_irregularities_1'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'1. The nature of business / manufacturing*activities as mentioned in the Common Application Form does not match with that as permitted as per the supporting document – Memorandum & Articles of Association / Partnership Deed / Certificate of Proprietorship / Trade Licence / Clearance from WBPCB* – uploadedwith the application.'
			
		);
	
		
	$form['nature_worker']['factory_nature_details_irregularities_chk_1'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td></tr>',
			 '#type' 			=> 'radios',
			  '#options'         => $irregularities_name,
			  '#default_value' 	=>'NotAgree',
    		 
			
  		);
		$form['nature_worker']['factory_nature_details_irregularities_2'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'2. The major / manufacturing process mentioned in the application does not match with that found being carried out in the premises, during inspection of the said premises by the respective Area Officer / Assistant Director / Inspector of Factories.'
			
		);
	
		
	$form['nature_worker']['factory_nature_details_irregularities_chk_2'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td></tr>',
			 '#type' 			=> 'radios',
			  '#options'         => $irregularities_name,
			  '#default_value' 	=>'NotAgree',
			  
    		 
			
  		);
		$form['nature_worker']['factory_nature_details_irregularities_3'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'3. The manufacturing processfound being carried out in the premises, during inspection of the said premises did not match with that for which the Approval of Plan was obtained from the Chief Inspector of Factories.'
			
		);
	
		
	$form['nature_worker']['factory_nature_details_irregularities_chk_3'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td></tr>',
			 '#type' 			=> 'radios',
			  '#options'         => $irregularities_name,
			  '#default_value' 	=>'NotAgree',
			  
    		 
			
  		);
		$form['nature_worker']['factory_nature_details_irregularities_4'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'4. Although the manufacturing process that has been mentioned in the application as ‘likely to be carried out’ in the period for which Licence is required, differs from the process which was carried out in the immediate preceding period, it appears that application for Approval of Plan (for the process to be carried out) has not been submitted / uploaded in the Official online Portal of this Directorate (along with this application or separately).'
			
		);
	
		
	$form['nature_worker']['factory_nature_details_irregularities_chk_4'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td></tr>',
			 '#type' 			=> 'radios',
			  '#options'         => $irregularities_name,
			  '#default_value' 	=>'NotAgree',
			  
    		 
			
  		);
		$form['nature_worker']['factory_nature_details_irregularities_5'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'5. Although the Factory was found supplying and / or selling power*,beyond the factory premises - to other Factories / to the Grid, from the standby / captive power plant, and the Licence Fee applicable for the corresponding capacity of Power Generation Unit is Rs '.$licence_fees.' /-;  yet the application has been made for a Non-Power Generating Station. Accordingly the application is to be revised and an additional fee amounting to Rs'.$licence_fees.'/- needs to be paid.'
			
		);
	
		
	$form['nature_worker']['factory_nature_details_irregularities_chk_5'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td></tr>',
			 '#type' 			=> 'radios',
			  '#options'         => $irregularities_name,
			  '#default_value' 	=>'NotAgree',
			  
    		 
			
  		);
	}
	
	
		$form['nature_worker']['factory_nature_details_irregularities_end'] 	= array(
		'#suffix' 	=> '</table><div>',
	);
	
	          
	
	
			
	
	
	 $form['factory_catagory'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('C. Factory Identification according to WBPCB'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	
	if($wbpcb_category_name == 1){
		$category_show = "RED";
		$form['factory_catagory']['category_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(i).Categories of wbpcb:-'.$category_show,
			'#type' 			=> 'markup',
			
		);
	$form['factory_catagory']['reference_no_approval_arrangments1'] = array(
				'#prefix' 			=> '<div class="col-md-6 col-xs-6">',
				'#suffix' 			=> '</div>',
				'#markup'			=> '(ii). Reference number of approval of arrangments and Reference Date:-'.$wbpcb_reference_no.',dated on '.$wbpcb_ref_date,
				'#type' 			=> 'markup',
				
				
				
			);
	$form['factory_catagory']['wbpcb_id'] = array(
	  	'#prefix'			=> '<div class="row"><div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'wbpcb_id',
        '#default_value' 	=>$wbpcb_id_ck ,
        '#title' 			=> t('Is Correct?'),
		
       
		
    );
	$caf_upload_doc_cat =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'DOC', $factory_type_id,$reference_no, 'wbpcb_id');
	}if($wbpcb_category_name == 2){
		$category_show = "GREEN";
		$form['factory_catagory']['category_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(i).Categories of wbpcb:-'.$category_show,
			'#type' 			=> 'markup',
			
		);
		$form['factory_catagory']['reference_no_approval_arrangments1'] = array(
				'#prefix' 			=> '<div class="col-md-6 col-xs-6">',
				'#suffix' 			=> '</div></div>',
				'#markup'			=> '(ii). Reference number of approval of arrangments and Reference Date:-'.$wbpcb_reference_no.',dated on '.$wbpcb_ref_date,
				'#type' 			=> 'markup',
				
				
				
				
			);
	$form['factory_catagory']['wbpcb_id'] = array(
	  	 	'#prefix'			=> '<div class="row"><div class="col-md-12 col-xs-12">',
        	'#suffix' 			=> '</div></div>',
       	 	'#type' 			=> 'checkbox',
			'#id'				=> 'wbpcb_id',
       		'#default_value' 	=> $wbpcb_id_ck ,
            '#title' 			=> t('Is Correct?'),
			
       
		
    );
	$caf_upload_doc_cat =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'DOC', $factory_type_id,$reference_no, 'wbpcb_id');
	}if($wbpcb_category_name == 3){
		$category_show = "ORANGE";
		$form['factory_catagory']['category_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div></div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(i).Categories of wbpcb:-'.$category_show,
			'#type' 			=> 'markup',
			
		);
		$form['factory_catagory']['reference_no_approval_arrangments1'] = array(
				'#prefix' 			=> '<div class="col-md-6 col-xs-6">',
				'#suffix' 			=> '</div></div>',
				'#markup'			=> '(ii). Reference number of approval of arrangments and Reference Date:-'.$wbpcb_reference_no.',dated on '.$wbpcb_ref_date,
				'#type' 			=> 'markup',
				
				
				
				
			);
	$form['factory_catagory']['wbpcb_id'] = array(
	  	'#prefix'			=> '<div class="row"><div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'wbpcb_id',
        '#default_value' 	=> $wbpcb_id_ck ,
        '#title' 			=> t('Is Correct?'),
		
       
		
    );
	$caf_upload_doc_cat =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'DOC', $factory_type_id,$reference_no, 'wbpcb_id');
	}if($wbpcb_category_name == 4){
		$category_show = "WHITE";
		$form['factory_catagory']['category_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(i).Categories of wbpcb:-'.$category_show,
			'#type' 			=> 'markup',
			
		);
		$form['factory_catagory']['wbpcb_id'] = array(
	  		'#prefix'			=> '<div class="col-md-6 col-xs-6">',
       		 '#suffix' 			=> '</div></div>',
       		 '#type' 			=> 'checkbox',
			'#id'				=> 'wbpcb_id',
         	'#default_value' 	=> $wbpcb_id_ck ,
      		 '#title' 			=> t('Is Correct?'),
			 
       
		
    );
	//$content_type = NULL;
	$caf_upload_doc_cat =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'INT', $factory_type_id,$reference_no, 'wbpcb_id');
	}if($wbpcb_category_name == 5){
		$category_show = "EXAMPTED";
		$form['factory_catagory']['category_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
          '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(i).Categories of wbpcb:-'.$category_show,
			'#type' 			=> 'markup',
			
		);
		$form['factory_catagory']['wbpcb_id'] = array(
	 	 	'#prefix'			=> '<div class="col-md-6 col-xs-6">',
        	'#suffix' 			=> '</div></div>',
        	'#type' 			=> 'checkbox',
			'#id'				=> 'wbpcb_id',
         	'#default_value' 	=> $wbpcb_id_ck ,
       		'#title' 			=> t('Is Correct?'),
			
       
		
    );
}
	
	
	
	
	
	
	$identity_flag = 'wbpcb_id';
	$irregularities_details_catagory =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factory_type_id,$service_id);

	$form['factory_catagory']['factory_catagory_irregularities_table'] 	= array(
	   
	
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>Irregularities for Scrutiny of Applications according to WBPCB of the Factory </th>
								<th >Action</th>
								
							</tr>
							'
					);
	
	if(!empty($irregularities_details_catagory)){
		foreach($irregularities_details_catagory as $row_irregularities_details_catagory){
			$form['factory_catagory']['factory_catagory_irregularities_'.$row_irregularities_details_catagory->id] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			 '#type' 			=> 'textarea',
			 '#rows'			=> 2,
			'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=> $row_irregularities_details_catagory->irregularities,
			
		);
	          
		$form['factory_catagory']['factory_adchk_'.$row_irregularities_details_catagory->id] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></tr></td>',
			 '#type' 			=> 'radios',
    		 '#options'         => $irregularities_name,
			 '#default_value' 	=> $row_irregularities_details_catagory->remark_by_ad,
			 
			
  		);
		
		}
	}else{
		
			
	///$category_show_name = '<font color="#FF0000">'.$category_show.'</font>';
	$form['factory_catagory']['factory_catagory_irregularities_1'] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			 '#type' 			=> 'textarea',
			 '#rows'			=> 2,
			'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=>'1. Although the manufacturing process has been claimed to be in the '.$category_show.' category of the West Bengal Pollution Control Board, yet, the said activities are found to be listed in the Red / Orange / Green/White/Exampted* category and for which appropriate documents pertaining to clearance (Consent to Establish / Consent to Operate) from the said Authority / Board permitting the said activities in the said premises, shall have to be uploaded with the application.',
			
		);
	          
		$form['factory_catagory']['factory_catagory_irregularities_chk_1'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></tr></td>',
			 '#type' 			=> 'radios',
    		 '#options'         => $irregularities_name,
			 '#default_value' 	=>'NotAgree',
			 
			
  		);
			
			
		$form['factory_catagory']['factory_catagory_irregularities_2'] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			 '#type' 			=> 'textarea',
			 '#rows'			=> 2,
			'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=>'2. Appropriate documents / Consent to Establish / Consent to Operate Certificate* regarding clearance from West Bengal Pollution Control Board / appropriate Authority have not been uploaded with the application.',
			
		);
	          
		$form['factory_catagory']['factory_catagory_irregularities_chk_2'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></tr></td>',
			 '#type' 			=> 'radios',
    		 '#options'         => $irregularities_name,
			 '#default_value' 	=>'NotAgree',
			 
			
  		);	
			
	}
	
			
			
	
		$form['factory_catagory']['factory_catagory_irregularities_end'] 	= array(
		'#suffix' 	=> '</table><div>',
	);
	
	
	//print_r($caf_upload_doc_prenission);die;
	
	
	
	
	
	
	 $form['factory_catagory_manudoc'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('D.The name of the Factory/Manufacturing Process/ Clearance from Pollution Control Board are  mentioned in supporting documents'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	$caf_upload_doc_all =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'DOC', $factory_type_id,$reference_no, 'factory_name');
		$form['factory_catagory_manudoc']['documents_list_factory_name'] 	= array(
	   
	
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12" id="worker_table_id">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>List of supported documents for above three section </th>
								<th >Action</th>
								
							</tr>
							'
					);
	
	
	
	

	
	
		foreach ($caf_upload_doc_all as $record) {
			
		$fetch_document = fun_fetch_document_listid($record->doc_master_id);
		$document_name = $fetch_document['document_name'];
		$displayLink = l('<i>'.$document_name.'</i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $record->id).'/'.encryption_decryption_fun('encrypt', 'DOC').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
		
		
		$form['factory_catagory_manudoc']['documents_list_factory_name'.$record->id] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			 '#type' 			=> 'markup',
		
			'#markup' 	=>$displayLink,
			
		);
		if(!empty($doc_verify_field)){
			if (in_array($record->id, $doc_verify_field)) {
    			$form['factory_catagory_manudoc']['documents_list_chk_'.$record->id] = array(
   			 		'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 		'#suffix' 			=> '</div></tr></td>',
			 		 '#type' 			=> 'checkbox',
    		 		'#default_value' 	=>'1',
			
  			);
		}else{
			$form['factory_catagory_manudoc']['documents_list_chk_'.$record->id] = array(
   			 	'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 	'#suffix' 			=> '</div></tr></td>',
			 	'#type' 			=> 'checkbox',
				
			
  			);
		}
	}else{
			$form['factory_catagory_manudoc']['documents_list_chk_'.$record->id] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></tr></td>',
			  '#type' 			=> 'checkbox',
    		 '#default_value' 	=>'1',
			 
			
  			);
		}
			
			
	
		}
		foreach ($caf_upload_doc_cat as $record) {
			
		$fetch_document = fun_fetch_document_listid($record->doc_master_id);
		$document_name = $fetch_document['document_name'];
		$displayLink = l('<i>'.$document_name.'</i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $record->id).'/'.encryption_decryption_fun('encrypt', $record->upload_doc_type).'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
		
		$output .= '<td>';
		$form['factory_catagory_manudoc']['documents_list_factory_cat'.$record->id] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			 '#type' 			=> 'markup',
		
			'#markup' 	=>$displayLink,
			
		);
		if(!empty($doc_verify_field)){
			if (in_array($record->id, $doc_verify_field)) {
			
				$form['factory_catagory_manudoc']['documents_list_factory_cat_chk_'.$record->id] = array(
				 		'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				 		'#suffix' 			=> '</div></tr></td>',
				 	 	'#type' 			=> 'checkbox',
				   		'#default_value' 	=>'1',
						
    		
			
  			);
		}else{
			$form['factory_catagory_manudoc']['documents_list_factory_cat_chk_'.$record->id] = array(
				 		'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				 		'#suffix' 			=> '</div></tr></td>',
				 	 	'#type' 			=> 'checkbox',
						
				   		
    		
			
  			);
		}
		
		}else{
			$form['factory_catagory_manudoc']['documents_list_factory_cat_chk_'.$record->id] = array(
				 		'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				 		'#suffix' 			=> '</div></tr></td>',
				 	 	'#type' 			=> 'checkbox',
				   		'#default_value' 	=>'1',
						
    		);
		}
	    
		
			
	
			
		}
	
	
	$form['factory_catagory_manudoc']['documents_list_factory_name_end'] 	= array(
		'#suffix' 	=> '</table></div>',
	);
	
	$factory_zone = get_factory_zone_name($get_fa_cafa['factory_zone']);
		$getdata_factory_location	 =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
		$factory_address_location 	 = $get_fa_cafa['addrline'].'<br/>Near by:- '.$nearest_landmark.',JL Number:-'.$jl_number.',Mouza Number:-'.$mouza_name.',<br/>'.get_full_address('fa_cafa','sub-table',$get_fa_cafa['id'],$getdata_factory_location);
		$getdata_headoffice_address  =  array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
		$headoffice_address 		 = $get_fa_cafa['addrline_off'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_fa_cafa['id'],$getdata_headoffice_address);
		
		$getdata_communication_address = array('district_comm','subdivision_comm','areatype_comm','block_comm','panchayat_comm','policestation_comm','pincodecomm','state_comm','postoffice_comm');
		$communication_address 		= $get_fa_cafa['addrline_comm'].',
		<br/>'.get_full_address('fa_cafa','sub-table',$get_fa_cafa['id'],$getdata_communication_address);
  
/********** Location of the factory - Start **********/
	$form['factory_part_a'] = array(
        '#type'			=> 'fieldset',
        '#title' 		=> t('B. Location of the factory'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	
	
	$form['factory_part_a']['location_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(i).Factory situated at:-<br/>ZONE:-'.$factory_zone['zone_name'].'<br/>'.$factory_address_location,
			'#type' 			=> 'markup',
			
		);
	$form['factory_part_a']['zone_name'] = array(
	    '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'zone_name',
        '#default_value' 	=>$zone_name_ck ,
        '#title' 			=> t('Is Factory situated at Correct?'),
       
		
    );
	
	

	
	
	$form['factory_part_a']['factory_addres_irregularities_table'] 	= array(
	   
	
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>Irregularities for Scrutiny of Applications about Location of the Factory </th>
								<th >Action</th>
								
							</tr>
							'
					);
	
	
	
	
	$identity_flag = 'premises_address';
	$irregularities_details_location =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factory_type_id,$service_id);

	if(!empty($irregularities_details_location)){
		foreach($irregularities_details_location as $row_irregularities_details_location){
			$form['factory_part_a']['factory_addres_irregularities_'.$row_irregularities_details_location->id] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			  '#type' 			=> 'textarea',
			 '#rows'			=> 2,
			'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=> $row_irregularities_details_location->irregularities,
			
		);
	          
		$form['factory_part_a']['factory_adchk_'.$row_irregularities_details_location->id] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></tr></td>',
			 '#type' 			=> 'radios',
    		 '#options'         => $irregularities_name,
			 '#default_value' 	=> $row_irregularities_details_location->remark_by_ad,
			
  		);
		$l= $l+1;
		}
	}else{
		$form['factory_part_a']['factory_addres_irregularities_1'] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			  '#type' 			=> 'textarea',
			 '#rows'			=> 2,
			'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=>'1. The address of the factory premises as mentioned in the Common Application Form does not match with that as per the supporting document – Ownership Deed / Lease Deed/ Rent Agreement / Trade Licence / Municipality Tax Bill / Clearance from WBPCB* – uploaded with the application'
			
		);
	          
		$form['factory_part_a']['factory_addres_chk_1'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></tr></td>',
			 '#type' 			=> 'radios',
    		 '#options'         => $irregularities_name,
			'#default_value' 	=>'NotAgree',
  		);
			
			
		$form['factory_part_a']['factory_addres_irregularities_2'] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			  '#type' 			=> 'textarea',
			 '#rows'			=> 2,
		 	
		'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=>'2. Documents in support of valid, legal and bona-fide possession of the premises, in which the factory shall run, have not been uploaded with the application.'
			
		);
	          
		$form['factory_part_a']['factory_addres_chk_2'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></tr></td>',
			 '#type' 			=> 'radios',
    		 '#options'         => $irregularities_name,
			 '#default_value' 	=>'NotAgree',
			
  		);	
			
			
		$form['factory_part_a']['factory_addres_irregularities_3'] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			  '#type' 			=> 'textfield',
			 '#rows'			=> 2,
		 	
		'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=>'3. Details of the actual owner of the premises have not been provided.'
			
		);
	          
		$form['factory_part_a']['factory_addres_chk_3'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></tr></td>',
			 '#type' 			=> 'radios',
    		 '#options'         => $irregularities_name,
			 '#default_value' 	=>'NotAgree',
			
  		);		
		$form['factory_part_a']['factory_addres_irregularities_4'] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			  '#type' 			=> 'textarea',
			 '#rows'			=> 2,
		 
			'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=>'4. Documents establishing valid, legal and bona-fide ownership of the premises, of the claimed actual owner of the premises with whom the Lease / Rent Agreement* has been entered upon, have not been uploaded with the application.'
			
		);
	          
		$form['factory_part_a']['factory_addres_chk_4'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></tr></td>',
			 '#type' 			=> 'radios',
    		 '#options'         => $irregularities_name,
			 '#default_value' 	=>'NotAgree',
			
  		);		
		$form['factory_part_a']['factory_addres_irregularities_5'] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			  '#type' 			=> 'textarea',
			
			 '#rows'			=> 2,
		'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=>'5. It appears that as the actual owner of the premises is a Government body, documents pertaining to permission from the said appropriate Authority (original Lessor) for sub-leasing / sub-letting* the premises by the actual Lessee to the present Lessee, have not been uploaded with the application.'
			
		);
	          
		$form['factory_part_a']['factory_addres_chk_5'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></tr></td>',
			 '#type' 			=> 'radios',
    		 '#options'         => $irregularities_name,
			 '#default_value' 	=>'NotAgree',
			
  		);		
	
	}
	
	$form['factory_part_info']['factory_addres_irregularities_end'] 	= array(
		'#suffix' 	=> '</table><div></div>',
	);
	$form['factory_part_a']['documents_list_factory_adress'] 	= array(
	   
	
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12" id="worker_table_id">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>List of supported documents according to Location of factory </th>
								<th >Action</th>
								
							</tr>
							'
					);
	
	
	$caf_upload_doc_prenission =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'DOC', $factory_type_id,$reference_no, 'premises_address');
	//print_r($caf_upload_doc_all1);die;
	
		foreach ($caf_upload_doc_prenission as $record) {
			
		$fetch_document = fun_fetch_document_listid($record->doc_master_id);
		$document_name = $fetch_document['document_name'];
		$displayLink = l('<i>'.$document_name.'</i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $record->id).'/'.encryption_decryption_fun('encrypt', 'DOC').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
		
		
		$form['factory_part_a']['documents_list_factory_adress'.$record->id] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			 '#type' 			=> 'markup',
		
			'#markup' 	=>$displayLink,
			
		);
		
		if(!empty($doc_verify_field)){
			if (in_array($record->id, $doc_verify_field)) {
				$form['factory_part_a']['documents_list_factory_adress_chk_'.$record->id] = array(
   			 		'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 		'#suffix' 			=> '</div></tr></td>',
			 	 	'#type' 			=> 'checkbox',
			   		'#default_value' 	=>'1',
    		
			
  				);
			}else{
				 $form['factory_part_a']['documents_list_factory_adress_chk_'.$record->id] = array(
   			 		'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 		'#suffix' 			=> '</div></tr></td>',
			 	 	'#type' 			=> 'checkbox',
			   		
    		
			
  				);
			}
		}else{
			 $form['factory_part_a']['documents_list_factory_adress_chk_'.$record->id] = array(
   			 		'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 		'#suffix' 			=> '</div></tr></td>',
			 	 	'#type' 			=> 'checkbox',
			   		'#default_value' 	=>'1',
    		
			
  				);
		}
		
		
	   
		
			
	
		
		}
	$form['factory_part_a']['documents_list_factory_adress_end'] 	= array(
		'#suffix' 	=> '</table></div></div>',
	);
	
	
	$form['factory_part_a']['markup_no_show1'] = array(
			'#prefix' 			=> '<div class="row">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '<br/>'
			
		);
	
	$form['factory_part_a']['telephone_no_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(ii).Telephone No:-'.$comm_telephone,
			'#type' 			=> 'markup',
			
		
		);
	$form['factory_part_a']['telephone_no'] = array(
	  	'#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'telephone_no',
        '#default_value' 	=>$telephone_no_ck,
       '#title' 			=> t('Is Telephone No Correct?'),
       
		
    );
	$form['factory_part_a']['mobile_no_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(iii).Mobile No:-'.$comm_mobile,
			'#type' 			=> 'markup',
			
		
		);
		$form['factory_part_a']['mobile_no'] = array(
	 	 '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'mobile_no',
        '#default_value' 	=>$mobile_no_ck,
        
       
        '#title' 			=> t('Is Mobile No Correct?'),
       
		
    );
	$form['factory_part_a']['altmobile_no_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(iv).Alternet mobile number:-'.$comm_alt_mobile,
			'#type' 			=> 'markup',
			
		
		);
	$form['factory_part_a']['altmobile_no'] = array(
	  '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'mobile_no',
        '#default_value' 	=>$mobile_no_ck,
        
       
        '#title' 			=> t('Is Alternet mobile number Correct?'),
       
		
    );
	$form['factory_part_a']['email_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(v).Email Id:-'.$comm_email,
			'#type' 			=> 'markup',
			
		
		);
	$form['factory_part_a']['email_no'] = array(
	  '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'mobile_no',
        '#default_value' 	=>$email_no_ck,
        
       
        '#title' 			=> t('Is Email Id Correct?'),
       
		
    );
	$form['factory_part_a']['fax_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(vi).Fax Number:-'.$comm_fax,
			'#type' 			=> 'markup',
			
		
		);
	$form['factory_part_a']['fax_no'] = array(
	  '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'fax_no',
        '#default_value' 	=>$fax_no_ck,
        
       
        '#title' 			=> t('Is Fax Number Correct?'),
       
		
    );
	
/********** Location of the factory - End **********/
	
/********** Address of the Registered office / Head office - Start **********/
	
    $form['factory_part_off']              = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('E. Address of the Registered office / Head office'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE ,
		//'#description' 		=> t('<font color="#FF0000">(N.B.:- This address will be treated as communication address as per Section 7 of Factories Act, 1948)</font>')
		
    );
	$form['factory_part_off']['registered_office_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(i).Address of the Registered office / Head office:-<br/>'.$headoffice_address,
			'#type' 			=> 'markup',
			
		);
	$form['factory_part_off']['factory_headoffice'] = array(
	  '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'factory_headoffice',
        '#default_value' 	=>$factory_headoffice_ck,
        
       
        '#title' 			=> t('Is Factory situated at Correct?'),
       
		
    );
	
	 

    /********** Address of the Registered office / Head office - End **********/
	
	
	/********** Communication Address - Start **********/
	
	$form['factory_part_comm']              = array(
        '#type' => 'fieldset',
        '#title' => t('F. Communication Address'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
	
	$form['factory_part_comm']['registered_office_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(i).Address to which communications relating to the factory may be sent:-<br/>'.$communication_address,
			'#type' 			=> 'markup',
			
		);
	$form['factory_part_comm']['factory_communication'] = array(
	  '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'factory_communication',
        '#default_value' 	=>$factory_communication_ck,
        
       
        '#title' 			=> t('Is Factory situated at Correct?'),
       
		
    );
	
    

		
	/********** Communication Address - End **********/
	
    
    //////////////////////////////////
		 
   
	
	$worker_details = get_worker_details_service($service_id,$factory_type_id,$application_id,$reference_no);
	
	
	foreach($worker_details as $worker){
		$permanent_worker_men 			= $worker->permanent_worker_men;
		$permanent_worker_women 		= $worker->permanent_worker_women;
		$permanent_adolescents_male 	= $worker->permanent_adolescents_male;
		$permanent_adolescents_female 	= $worker->permanent_adolescents_female;
		$permanent_children_male 		= $worker->permanent_children_male;
		$permanent_children_female 		= $worker->permanent_children_female;
		$contactual_worker_men 			= $worker->contactual_worker_men;
		$contactual_worker_women 		= $worker->contactual_worker_women;
		$contactual_adolescents_male 	= $worker->contactual_adolescents_male;
		$contactual_adolescents_female 	= $worker->contactual_adolescents_female;
		$contactual_children_male 		= $worker->contactual_children_male;
		$contactual_children_female 	= $worker->contactual_children_female;
		$worker_total 					= $worker->worker_total;
		$worker_id 						= $worker->id;
		$recomended_worker 				= $worker->recomended_total_worker;
		
	}
	
	$form['worker_id_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$worker_id)
	);
	$date_of_amenability_show = date('d-m-Y',strtotime($date_of_amenability));
	$amenability_year = date('Y',strtotime($date_of_amenability));
	$form['reg_year'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('G. State the period of license'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	 $form['reg_year']['factor_amenablity_date'] = array(
		'#prefix' 			=> 	'<div class="row"><div class="col-md-6 col-xs-6">',
		'#suffix' 			=> 	'</div>',
		'#type' 			=> 	'markup',
		'#markup'	    	=>	'(i). Date from which the premises is occupied <br/>or been taken into use as factory:-'.$date_of_amenability_show,
		
			
		);
		$form['reg_year']['date_of_amenability_id'] = array(
	  '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'date_of_amenability_id',
        '#default_value' 	=>$date_of_amenability_id_ck,
        
       
        '#title' 			=> t('Is Correct?'),
       
		
    );
	$form['reg_year']['amenibiltydate_actualvalue'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
		'#suffix' 	 		=> '</div></div>',
        '#title' 			=> t('(ii)Actual date of Amenability of / Commencement of business found after inspection'),
        '#type' 			=> 'textfield',
        '#default_value' 	=> !empty($recomended_date_of_amenability)?date('d-m-Y',strtotime($recomended_date_of_amenability)):$date_of_amenability_show,
		'#attributes' 		=> array('class' => array('form-control datepicker_retify'),'readonly' => 'readonly' ),
		'#required' 		=> TRUE,
		
    );
	
	$identity_flag = 'date_of_amenability_id';
$irregularities_details_amenability =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factory_type_id,$service_id);

		
	$form['reg_year']['factory_amenability_irregularities_table'] 	= array(
	   
	
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th >Irregularities for Scrutiny of Applications according to Date of Amenability  of the Factory </th>
								<th >Action</th>
								
							</tr>
							'
					);
if(!empty($irregularities_details_amenability)){
	foreach($irregularities_details_amenability as $row_irregularities_details_amenability){
		$form['reg_year']['factory_amenability_irregularities_'.$row_irregularities_details_amenability->id] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=> $row_irregularities_details_amenability->irregularities,
			
		);
	
		
	          
		$form['reg_year']['factory_adchk_'.$row_irregularities_details_amenability->id] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td></tr>',
			 '#type' 			=> 'radios',
			  '#options'         => $irregularities_name,
			  '#default_value' 	=> $row_irregularities_details_amenability->remark_by_ad,
    		 
			
  		);
		
	}
}else{
	$form['reg_year']['factory_amenability_irregularities_1'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'1. Declaration by the Occupierregarding the date of Amenability of / Commencement of business in* the premises as a ‘Factory’, as under The Factories Act 1948, has not been uploaded / submitted with the application'
			
		);
	
		
	          
		$form['reg_year']['factory_amenability_irregularities_chk_1'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td></tr>',
			 '#type' 			=> 'radios',
			  '#options'         => $irregularities_name,
			  '#default_value' 	=>'NotAgree',
    		 
			
  		);
		
	
	$form['reg_year']['factory_amenability_irregularities_2'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'2. Copy of ESIC Registration Certificate or other appropriate documents in support of the declared date of Amenability of / Commencement of business - manufacturing process in* the premises as a ‘Factory’, as under The Factories Act 1948,as per the Application Form, has not been uploaded / submitted with the application '.$date_of_amenability_show.' yet it was ascertained during inspection of the said premises and / or during scrutiny of the documents uploaded with the application, that the premises constituted a Factory, as under the Act, from an earlier date'
			
		);
	
		
		$form['reg_year']['factory_amenability_irregularities_chk_2'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td></tr>',
			 '#type' 			=> 'radios',
			  '#options'         => $irregularities_name,
			  '#default_value' 	=>'NotAgree',
    		 
			
  		);	
			
	$form['reg_year']['factory_amenability_irregularities_3'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'3. Although the declared date of Amenability of / Commencement of business in* the premises as a ‘Factory’, as under The Factories Act 1948,as per the Application Form is '.$date_of_amenability_show.' Hence Applicationsalong with Fees and supporting documents for the Years '.$amenability_year.' etc/ Period  '.$service_year.'are additionally required to be uploaded with the revised application.'
			
		);
	
	
	          
		$form['reg_year']['factory_amenability_irregularities_chk_3'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td></tr>',
			 '#type' 			=> 'radios',
			  '#options'         => $irregularities_name,
			  '#default_value' 	=>'NotAgree',
    		 
			
  		);
					
			
		
}
		
			
			
	
		$form['reg_year']['factory_amenability_irregularities_end'] 	= array(
		'#suffix' 	=> '</table><div>',
	);
	$form['reg_year']['documents_list_factory_caf'] 	= array(
	   
	
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12" id="worker_table_id">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>Uploaded Common Application Form </th>
								<th >Action</th>
								
							</tr>
							'
					);
	
	$caf_upload_doc_caf =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'CAF', $factory_type_id,$reference_no, 'period_for_application_id');
	
	
		foreach ($caf_upload_doc_caf as $record) {
			
		$fetch_document = fun_fetch_document_listid($record->doc_master_id);
		$document_name = $fetch_document['document_name'];
		$displayLink = l('<i>'.$document_name.'</i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $record->id).'/'.encryption_decryption_fun('encrypt', $record->upload_doc_type).'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
		
		
		$form['reg_year']['documents_list_factory_caf'.$record->id] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			 '#type' 			=> 'markup',
		
			'#markup' 	=>$displayLink,
			
		);
	      if(!empty($doc_verify_field)){
			if (in_array($record->id, $doc_verify_field)){
				$form['reg_year']['documents_list_factory_caf_chk_'.$record->id] = array(
				 	'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				 	'#suffix' 			=> '</div></tr></td>',
				  	'#type' 			=> 'checkbox',
				 	'#default_value' 	=>'1',
			
  				);
		  }else{
			  $form['reg_year']['documents_list_factory_caf_chk_'.$record->id] = array(
				 	'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				 	'#suffix' 			=> '</div></tr></td>',
				  	'#type' 			=> 'checkbox',
				 	
			
  				);
		  }
		}else{
			  $form['reg_year']['documents_list_factory_caf_chk_'.$record->id] = array(
				 	'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				 	'#suffix' 			=> '</div></tr></td>',
				  	'#type' 			=> 'checkbox',
				 	'#default_value' 	=>'1',
			
  				);
		  }

		
			
	
			
		}
	$form['reg_year']['documents_list_factory_caf_end'] 	= array(
		'#suffix' 	=> '</table></div></div>',
	);
	
	$form['factory_part_a']['markup_no_show2'] = array(
			'#prefix' 			=> '<div class="row">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '<br/><br/>'
			
		);
	$form['reg_year']['previous_table'] 	= array(
  			
  			'#type'		=> 'markup',
			'#markup'   =>'<br/>(ii)Maximum number of workers employed or to be employed in tha factory',
			'#prefix'	=> '<div class="row">
			<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
							
							<table class="custom-table-view-dashboard renewal-table">
							<tr>
							<th   colspan="6">Permanent</th>
							<th   colspan="6">Contactual</th>
							</tr>
							<tr>
								<th rowspan="2">Men</th>
								<th rowspan="2">Women</th>  
								<th colspan="2">Adolescents</th>
								<th colspan="2">Children </th>
        
   						
								<th rowspan="2">Men</th>
								<th rowspan="2">Women</th>  
								<th colspan="2">Adolescents</th>
								<th colspan="2">Children</th>
        
   						 </tr>
						 <tr>
						 <th >Men</th>
						<th >Women</th>  
						<th >Men</th>
						<th >Women</th>  
						 <th >Men</th>
						<th >Women</th>  
						<th >Men</th>
						<th >Women</th>  
							
						 </tr>'
			
  
			);

  $form['reg_year']['per_worker_men'] = array(
				'#prefix' 			=> '<tr><td><div class="col-xs-12">',
			  	'#suffix' 	 		=> '</div></td>',
			   	'#type' 			=> 'markup',
			 	'#markup'			=> $permanent_worker_men, 
			  	
			);
  $form['reg_year']['per_worker_women'] = array(
				 '#prefix' 				=> '<td><div class="col-xs-12">',
				 '#suffix' 	 			=> '</div></td>',
				 '#type' 				=> 'markup',
				 '#markup'				=> $permanent_worker_women, 
				 
			);
  $form['reg_year']['per_worker_adol_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#type' 				=> 'markup',
			  '#markup'				=> $permanent_adolescents_male, 
			  
		);
  
  $form['reg_year']['per_worker_adol_women'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#type' 				=> 'markup',
			  '#markup'		=> $permanent_adolescents_female, 
			 
			);
  $form['reg_year']['per_worker_child_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#type' 				=> 'markup',
			  '#markup'				=> $permanent_children_male, 
			 
			);
  $form['reg_year']['per_worker_child_women'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#type' 				=> 'markup',
			  '#markup'				=> $permanent_children_female, 
			  
			);
  $form['reg_year']['con_worker_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#type' 				=> 'markup',
			  '#markup'				=> $contactual_worker_men, 
			  
			);
  $form['reg_year']['con_worker_women'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			   '#type' 				=> 'markup',
			 
			  '#markup'		=>$contactual_worker_women, 
			 
			);
  $form['reg_year']['con_worker_adol_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#type' 				=> 'markup',
			  '#markup'		=> $contactual_adolescents_male, 
			  
		);
  $form['reg_year']['con_worker_adol_women'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				   '#type' 				=> 'markup',
				  '#markup'		=> $contactual_adolescents_male, 
				
			);
  $form['reg_year']['con_worker_child_men'] = array(
			 '#prefix' 				=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#type' 				=> 'markup',
			  '#markup'				=> $contactual_adolescents_male, 
			
		);
  $form['reg_year']['con_worker_child_woman'] = array(
			 '#prefix' 				=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td></tr>',
			  '#type' 				=> 'markup',
			  '#markup'		=> $contactual_children_female, 
			  
			);
	
  $form['reg_year']['previous_table_end'] 	= array(
  				  '#suffix' => '<tfoot>
				  					<tr><td colspan="12">
										<font color="#00498b">Total Worker(s)  :-</font>&nbsp;&nbsp;<strong>'.$worker_total.'</strong></td>
    								</tr>
  								</tfoot>
								</table>
								</div>
								</div>
								</br><font color="#FF0000">**</font>N.B. Adolescents (over 15 but under 18 years of age)
								</br><font color="#FF0000">**</font>N.B. Children (over 14 but under 15 years of age)',
  				'#type'	  => 'markup',
				'#markup' => '',	
				);
		$form['reg_year']['worker_details'] = array(
	  '#prefix'			=> '<div class="row"><div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'worker_details',
         '#default_value' 	=>$worker_details_ck,
        
       
        '#title' 			=> t('Is Maximum number of workers employed or to be employed in tha factory Correct?'),
       
		
    );
	$form['reg_year']['worker_actualvalue'] = array(
			 	'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
				'#suffix' 			=> '</div></div>',
       		 	'#type' 			=> 'textfield',
			 	'#title'			=>	t('After inspection of the Factory, it was not found that the nos of workers employed was '),
				'#attributes' 		=> array('class' => array( 'form-control')),
			 	'#default_value' => !empty($recomended_worker)?$recomended_worker:$worker_total,
				'#element_validate'	=>  array('DOUBLE_FIELD_VALIDATION'),
				'#required' 		=> TRUE,
			
		);
	
	$identity_flag ='worker_details' ;
	$irregularities_details_worker_details =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factory_type_id,$service_id);
	
	$form['reg_year']['factory_worker_irregularities_table'] 	= array(
	   
	
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th >Irregularities for Scrutiny of Applications according to Nos. of Workers  of the Factory </th>
								<th >Action</th>
								
							</tr>
							'
					);

if(!empty($irregularities_details_worker_details)){
	foreach($irregularities_details_worker_details as $row_irregularities_details_worker_details){
		
		$form['reg_year']['factory_worker_irregularities_'.$row_irregularities_details_worker_details->id] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=> $row_irregularities_details_worker_details->irregularities,
			
		);
	
		
	          
		$form['reg_year']['factory_adchk_'.$row_irregularities_details_worker_details->id] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td></tr>',
			 '#type' 			=> 'radios',
			  '#options'         => $irregularities_name,
			 '#default_value' 	=> $row_irregularities_details_worker_details->remark_by_ad,
    		 
			
  		);
		
	}
	
		
				
}else{
	$form['reg_year']['factory_worker_irregularities_1'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'1. Although the declared maximum nos. of Workers employed and/or likely to be employed* in the factory on any day during the period for which Licence is required, has been stated as '.$worker_total.' , yet during inspection of the Factory, it was not found that the nos of workers employed was '.$worker_total.' for the License Period  '.$service_year.'respectively*, which fall under highercategory / categories*.Accordingly the application is to be revised and an additional fee for the said higher category / categories*,including Amendment Fee and Late Fee, amounting to Rs______ needs to be paid'
			
		);
	
		
	          
		$form['reg_year']['factory_worker_irregularities_chk_1'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td></tr>',
			 '#type' 			=> 'radios',
			  '#options'         => $irregularities_name,
			  '#default_value' 	=>'NotAgree',
    		 
			
  		);
		
			
}
			
		
	          
					
	
		$form['reg_year']['factory_worker_irregularities_end'] 	= array(
		'#suffix' 	=> '</table><div>',
	);
	
	
	
	if($factory_type_id == 3 || $factory_type_id == 1){//echo 'hi';
	$power_details = get_power_generating_station($application_id,$reference_no,$factory_type_id,$service_id);
	foreach($power_details as $power){
		$type_power_station 	= $power->type_power_station;
		$power_unit 			= $power->power_unit;
		$installed_power		= $power->installed_power;
		$power_id				= $power->id; 
		$power_recomended		= $power->recommanded_installed_power;
		$power_unit_recomended 	= $power->recommanded_power_unit;
	}
	$form['power_id_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$power_id)
	);
	
	 $form['power_details'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('I. Power Details'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	
	$form['power_details']['installed_power'] 	= array(
					 '#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
					  '#suffix' 	 		=> '</div>',
					  '#markup'				=>	t('Installed Power or to be installed power:-').$installed_power.'('.$power_unit.')',
					  '#type' 				=> 'markup',
					 
					 
	
				);	
  $radios_options 			= array('power_generating_station'=>"Power generating station",'other'=>"Other");
  if($type_power_station == 'power_generating_station'){
	  $type_power_station = "Power generating station";
  }if($type_power_station == 'other'){
	   $type_power_station = "Other";
  }
   
	 	
  $form['power_details']['is_generating']= array(
					 '#prefix' 			=> '<div class="col-md-6 col-xs-6">',
					 '#suffix'    		=> '</div></div>',
					 '#type'		 	=> 'markup',
					
					
					 '#markup' 	=> 'Type of power generating station:-'.$type_power_station,
					 
	);

$form['power_details']['power_details'] = array(
	  '#prefix'			=> '<div class="row"><div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'power_details',
         '#default_value' 	=>$power_details_ck,
        
       
        '#title' 			=> t('Is Installed Power or to be installed power Correct?'),
       
		
    );
$form['power_details']['power_actualvalue'] = array(
        	'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
        	'#suffix' 			=> '</div>',
        	'#title' 			=> t('(i) Actual value found after inspection'),
        	'#type' 			=> 'textfield',
        	'#default_value' 	=> !empty($power_recomended)?$power_recomended:$installed_power,
			'#element_validate'	=>  array('DOUBLE_FIELD_VALIDATION'),
			'#attributes' 		=> array('class' => array('form-control') ),
			'#required' 		=> TRUE,
		
    );
$form['power_details']['power_actual_unit'] 	= array(
			'#prefix' 	 		=> '<div class="col-md-6 col-xs-6">',
			'#suffix' 	 		=> '</div></div>',
			'#title' 			=> t('(ii)Actual Unit'),
			'#type' 	 		=> 'select',
			'#options'	 		=> array('HP'=>'HP','KW'=>'KW'),
			'#attributes' 		=>  array('class'=>array('form-control')),
			'#default_value' 	=> !empty($power_unit_recomended)?$power_unit_recomended:$power_unit,
			'#required' 		=>  TRUE,
	);
$identity_flag ='power_details' ;
$irregularities_details_power_details =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factory_type_id,$service_id);	
$form['power_details']['factory_power_details_irregularities_table'] 	= array(
	   
	
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th >Irregularities for Scrutiny of Applications according to Nos. of Workers  of the Factory </th>
								<th >Action</th>
								
							</tr>
							'
					);

if(!empty($irregularities_details_power_details)){
	foreach($irregularities_details_power_details as $row_irregularities_details_power_details){
		$form['power_details']['factory_power_details_irregularities_'.$row_irregularities_details_power_details->id] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 '#default_value' 	=> $row_irregularities_details_power_details->irregularities,
			
		);
	
		
	          
		$form['power_details']['factory_adchk_'.$row_irregularities_details_power_details->id] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td></tr>',
			 '#type' 			=> 'radios',
			  '#options'         => $irregularities_name,
			  '#default_value' 	=> $row_irregularities_details_power_details->remark_by_ad,
    		 
			
  		);
		
	}
}else{
	$form['power_details']['factory_power_details_irregularities_1'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'1.Although the declared capacity of Machinery installed and / or likely to be installed has been stated as '.$installed_power.'('.$power_unit.')'.'yet during inspection of the Factory, it was found that the total capacity of Machinery installed in the premises was '.$installed_power.'('.$power_unit.')'.'for the License Period  '.$service_year.'respectively* which falls / fall*under  highercategory / categories*. Accordingly the application is to be revised and an additional fee for the said higher category / categories*,includingAmendment Feeand Late Fee, amounting to '.$licence_fees.'/-needs to be paid.'
			
		);
	
		
	          
		$form['power_details']['factory_power_details_irregularities_chk_1'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td></tr>',
			 '#type' 			=> 'radios',
			  '#options'         => $irregularities_name,
			  '#default_value' 	=>'NotAgree',
    		 
			
  		);
		
		$form['power_details']['factory_power_details_irregularities_2'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'2. The List of Installed Machinery along with the respective individual and the total capacity in Horsepower (Kilowatts for Generating Station) has not been uploaded with the application. '
			
		);
	
		
	          
		$form['power_details']['factory_power_details_irregularities_chk_2'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td></tr>',
			 '#type' 			=> 'radios',
			  '#options'         => $irregularities_name,
			  '#default_value' 	=>'NotAgree',
    		 
			
  		);	
		
	          
		
	$form['power_details']['factory_power_details_irregularities_3'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textfield',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'3. A copy of the current Electric Bill is required to be uploaded with the application.'
			
		);
	
		
	          
		$form['power_details']['factory_power_details_irregularities_chk_3'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td></tr>',
			 '#type' 			=> 'radios',
			  '#options'         => $irregularities_name,
			  '#default_value' 	=>'NotAgree',
    		 
			
  		);	
					
			
		$form['power_details']['factory_power_details_irregularities_4'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'4. The Contract Demand mentioned in the Electric Bill, uploaded with the application, is much higher than the capacity of the sum-total capacity of machineryinstalled in the factory, declared in the application form and in the List of Machinery uploaded with the application.'
			
		);
	
		
	          
		$form['power_details']['factory_power_details_irregularities_chk_4'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td></tr>',
			 '#type' 			=> 'radios',
			  '#options'         => $irregularities_name,
			  '#default_value' 	=>'NotAgree',
    		 
			
  		);	
}
		
$form['power_details']['factory_power_details_irregularities_end'] 	= array(
		'#suffix' 	=> '</table><div>',
);


	$form['power_details']['documents_list_factory_power_details'] 	= array(
	   
	
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12" id="worker_table_id">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>Supportive Documents According to Power details </th>
								<th >Action</th>
								
							</tr>
							'
					);
	
	$caf_upload_doc_power_details =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'DOC', $factory_type_id,$reference_no, 'power_details');
	
	
		foreach ($caf_upload_doc_power_details as $record) {
			
		$fetch_document = fun_fetch_document_listid($record->doc_master_id);
		$document_name = $fetch_document['document_name'];
		$displayLink = l('<i>'.$document_name.'</i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $record->id).'/'.encryption_decryption_fun('encrypt', $record->upload_doc_type).'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
		
		
		$form['power_details']['documents_list_factory_power_details'.$record->id] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			 '#type' 			=> 'markup',
		
			'#markup' 	=>$displayLink,
			
		);
	     if(!empty($doc_verify_field)){
			if (in_array($record->id, $doc_verify_field)) {
					$form['power_details']['documents_list_factory_power_details_chk_'.$record->id] = array(
   			 			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 			'#suffix' 			=> '</div></tr></td>',
			  			'#type' 			=> 'checkbox',
			   			'#default_value' 	=>'1',
    		
			
  					);
				}else{
					$form['power_details']['documents_list_factory_power_details_chk_'.$record->id] = array(
   			 			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 			'#suffix' 			=> '</div></tr></td>',
			  			'#type' 			=> 'checkbox',
			   			
    		
			
  					);
				}
			
		 }else{
			 $form['power_details']['documents_list_factory_power_details_chk_'.$record->id] = array(
   			 			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 			'#suffix' 			=> '</div></tr></td>',
			  			'#type' 			=> 'checkbox',
			   			'#default_value' 	=>'1',
    		
			
  					);
		 }
		
			
	
			
		}
	$form['power_details']['documents_list_factory_power_details_end'] 	= array(
		'#suffix' 	=> '</table></div>',
	);
	}
 if($application_status == 'U'){
	   $form['submit'] = array(
        '#prefix' => '<div class="col-md-1">',
        '#suffix' => '</div>',
        '#attributes' => array('class' => array('btn btn-success')),
        '#type' => 'submit',
        '#value' => 'Save'
    );
  }
	 
    return $form;
}








function caf_form_registrstion_factory_information_submit($form, &$form_state)
{
	//die;
	  global $user;
      $userid 			= 	$user->uid;
	  $remark_by_name											= get_name($userid);
	  $rid= get_role_id($userid);
	  $val    													= $form_state['values'];
	
	 //print_r($val);die;
	   //-------------Irregularities-----------------------------------------------------
	  $factory_name_irregularities_1 							= $val['factory_name_irregularities_1'];
	  $factory_name_chk_1 										= $val['factory_name_chk_1'];
	  $factory_name_irregularities_2 							= $val['factory_name_irregularities_2'];
	  $factory_name_chk_2 										= $val['factory_name_chk_2'];
	  $factory_nature_details_irregularities_1 					= $val['factory_nature_details_irregularities_1'];
	  $factory_nature_details_irregularities_chk_1 				= $val['factory_nature_details_irregularities_chk_1'];
	  $factory_nature_details_irregularities_2 					= $val['factory_nature_details_irregularities_2'];
	  $factory_nature_details_irregularities_chk_2 				= $val['factory_nature_details_irregularities_chk_2'];
	  $factory_nature_details_irregularities_3 					= $val['factory_nature_details_irregularities_3'];
	  $factory_nature_details_irregularities_chk_3 				= $val['factory_nature_details_irregularities_chk_3'];
	  $factory_nature_details_irregularities_4 					= $val['factory_nature_details_irregularities_4'];
	  $factory_nature_details_irregularities_chk_4 				= $val['factory_nature_details_irregularities_chk_4'];
	  $factory_nature_details_irregularities_5 					= $val['factory_nature_details_irregularities_5'];
	  $factory_nature_details_irregularities_chk_5 				= $val['factory_nature_details_irregularities_chk_5'];
	  $factory_catagory_irregularities_1 						= $val['factory_catagory_irregularities_1'];
	  $factory_catagory_irregularities_chk_1 					= $val['factory_catagory_irregularities_chk_1'];
	  $factory_catagory_irregularities_2 						= $val['factory_catagory_irregularities_2'];
	  $factory_catagory_irregularities_chk_2 					= $val['factory_catagory_irregularities_chk_2'];
	  $factory_addres_irregularities_1 							= $val['factory_addres_irregularities_1'];
	  $factory_addres_chk_1 									= $val['factory_addres_chk_1'];
	  
	  $factory_addres_irregularities_2 							= $val['factory_addres_irregularities_2'];
	  $factory_addres_chk_2 									= $val['factory_addres_chk_2'];
	   
	  $factory_addres_irregularities_3 							= $val['factory_addres_irregularities_3'];
	  $factory_addres_chk_3 									= $val['factory_addres_chk_3'];
	  
	  $factory_addres_irregularities_4 							= $val['factory_addres_irregularities_4'];
	  $factory_addres_chk_4 									= $val['factory_addres_chk_4'];
	 
	  $factory_addres_irregularities_5 							= $val['factory_addres_irregularities_5'];
	  $factory_addres_chk_5 									= $val['factory_addres_chk_5'];
	   
	  $factory_amenability_irregularities_1 					= $val['factory_amenability_irregularities_1'];
	  $factory_amenability_irregularities_chk_1 				= $val['factory_amenability_irregularities_chk_1'];
	   
	  $factory_amenability_irregularities_2 					= $val['factory_amenability_irregularities_2'];
	  $factory_amenability_irregularities_chk_2 				= $val['factory_amenability_irregularities_chk_2'];
	 
	  $factory_amenability_irregularities_3 					= $val['factory_amenability_irregularities_3'];
	  $factory_amenability_irregularities_chk_3 				= $val['factory_amenability_irregularities_chk_3'];
	
	  $factory_worker_irregularities_1 							= $val['factory_worker_irregularities_1'];
	  $factory_worker_irregularities_chk_1 						= $val['factory_worker_irregularities_chk_1'];
	  $factory_power_details_irregularities_1 					= $val['factory_power_details_irregularities_1'];
	  $factory_power_details_irregularities_chk_1 				= $val['factory_power_details_irregularities_chk_1'];
	  $factory_power_details_irregularities_2 					= $val['factory_power_details_irregularities_2'];
	  $factory_power_details_irregularities_chk_2 				= $val['factory_power_details_irregularities_chk_2'];
	  $factory_power_details_irregularities_3 					= $val['factory_power_details_irregularities_3'];
	  $factory_power_details_irregularities_chk_3 				= $val['factory_power_details_irregularities_chk_3'];
	  $factory_power_details_irregularities_4 					= $val['factory_power_details_irregularities_4'];
	  $factory_power_details_irregularities_chk_4 				= $val['factory_power_details_irregularities_chk_4'];
	  //--------------------------------END Irregularities-----------------------------------------------------
	  
	  
	  $service_id												= encryption_decryption_fun('decrypt',$val['serviceid_hidden']); 
	  $factorytype_id											= encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	  $application_id											= encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	  $reference_no												= encryption_decryption_fun('decrypt',$val['referenceno_hidden']);
	  $power_id													= encryption_decryption_fun('decrypt',$val['power_id_hidden']);
	  $worker_id												= encryption_decryption_fun('decrypt',$val['worker_id_hidden']);
	  $wbpcb_category_name										= $val['wbpcb_category_name_hidden'];
	  $is_chemical												= $val['is_chemical_hidden'];
	  $recomended_date_of_amenability							= date('Y-m-d',strtotime($val['amenibiltydate_actualvalue']));
	  $recomended_power											= $val['power_actualvalue'];
	  $recomended_worker_total									= $val['worker_actualvalue'];
	  $recomended_power_actual_unit								= $val['power_actual_unit'];
	  //--------------------------------Remark------------------------------
	  $factory_name	 				=!empty($val['factory_name'])?'factory_name,':NULL;
	  $factory_pan	 				=!empty($val['factory_pan'])?'factory_pan,':NULL;
	  $gstin_no	 	 				=!empty($val['gstin_no'])?'gstin_no,':NULL;
	  $udyog_aadhaar	 			=!empty($val['udyog_aadhaar'])?'udyog_aadhaar,':NULL;
	  $trade_no	 					=!empty($val['trade_no'])?'trade_no,':NULL;
	  $plan_approval_no	 			=!empty($val['plan_approval_no'])?'plan_approval_no,':NULL;
	  $factory_previous_name		=!empty($val['factory_previous_name'])?'factory_previous_name,':NULL;
	  $cin_no						=!empty($val['cin_no'])?'cin_no,':NULL;
	  $enargy_no					=!empty($val['enargy_no'])?'enargy_no,':NULL;
	  $wbpcb_id						=!empty($val['wbpcb_id'])?'wbpcb_id,':NULL;
	  $zone_name					=!empty($val['zone_name'])?'zone_name,':NULL;
	  $telephone_no					=!empty($val['telephone_no'])?'telephone_no,':NULL;
	  $mobile_no					=!empty($val['mobile_no'])?'mobile_no,':NULL;
	  $altmobile_no					=!empty($val['altmobile_no'])?'fax_no,':NULL;
	  $email_no						=!empty($val['email_no'])?'email_no,':NULL;
	  $fax_no						=!empty($val['fax_no'])?'fax_no,':NULL;
	  $factory_headoffice			=!empty($val['factory_headoffice'])?'factory_headoffice,':NULL;
	  $factory_communication		=!empty($val['factory_communication'])?'factory_communication,':NULL;
	  $date_of_amenability_id		=!empty($val['date_of_amenability_id'])?'date_of_amenability_id,':NULL;
	  $worker_details				=!empty($val['worker_details'])?'worker_details,':NULL;
	  $power_details				=!empty($val['power_details'])?'power_details,':NULL;
	  $nature_details				=!empty($val['nature_details'])?'nature_details,':NULL;

	 
	
	  $remark_details 	= get_remark_id($application_id,$reference_no,$userid,$rid);
	 $verify_details 	= $remark_details['verify_details'];
	 $remark_id			= $remark_details['id'];
	 $doc_verify 		= $remark_details['doc_verify'];
		//$doc_verify 	= $remark_fetch['doc_verify'];
		
		if(!empty($verify_details)){
			$remark_field = explode(',', $verify_details);
			//$doc_verify_field = explode(',', $doc_verify);
			//print_r($doc_verify_field);die;

			if(in_array("factory_name", $remark_field)) {
				if(empty($factory_name)){
					$verify_details = str_replace('factory_name,', '' ,$verify_details); 
				}
			}
			if(in_array("factory_pan", $remark_field)) {
				if(empty($factory_pan)){
					$verify_details = str_replace('factory_pan,', '' ,$verify_details); 
				}
			}
			if(in_array("gstin_no", $remark_field)) {
				if(empty($gstin_no)){
					$verify_details = str_replace('gstin_no,', '' ,$verify_details); 
				}
			}
			if(in_array("udyog_aadhaar", $remark_field)) {
				if(empty($udyog_aadhaar)){
					$verify_details = str_replace('udyog_aadhaar,', '' ,$verify_details); 
				}
			}
			if(in_array("trade_no", $remark_field)) {
				if(empty($trade_no)){
					$verify_details = str_replace('trade_no,', '' ,$verify_details); 
				}
			}
			if(in_array("plan_approval_no", $remark_field)) {
				if(empty($plan_approval_no)){
					$verify_details = str_replace('plan_approval_no,', '' ,$verify_details); 
				}
			}
			if(in_array("factory_previous_name", $remark_field)) {
				if(empty($factory_previous_name)){
					$verify_details = str_replace('factory_previous_name,', '' ,$verify_details); 
				}
			}
			if(in_array("cin_no", $remark_field)) {
				if(empty($cin_no)){
					$verify_details = str_replace('cin_no,', '' ,$verify_details); 
				}
			}
			if(in_array("enargy_no", $remark_field)) {
				if(empty($enargy_no)){
					$verify_details = str_replace('enargy_no,', '' ,$verify_details); 
				}
			}
			if(in_array("wbpcb_id", $remark_field)) {
				if(empty($wbpcb_id)){
					$verify_details = str_replace('wbpcb_id,', '' ,$verify_details); 
				}
			}
			if(in_array("zone_name", $remark_field)) {
				if(empty($zone_name)){
					$verify_details = str_replace('zone_name,', '' ,$verify_details); 
				}
			}
			if(in_array("telephone_no", $remark_field)) {
				if(empty($telephone_no)){
					$verify_details = str_replace('telephone_no,', '' ,$verify_details); 
				}
			}
			if(in_array("mobile_no", $remark_field)) {
				if(empty($mobile_no)){
					$verify_details = str_replace('mobile_no,', '' ,$verify_details); 
				}
			}
			if(in_array("altmobile_no", $remark_field)) {
				if(empty($altmobile_no)){
					$verify_details = str_replace('altmobile_no,', '' ,$verify_details); 
				}
			}
			if(in_array("email_no", $remark_field)) {
				if(empty($email_no)){
					$verify_details = str_replace('email_no,', '' ,$verify_details); 
				}
			}
			if(in_array("fax_no", $remark_field)) {
				if(empty($fax_no)){
					$verify_details = str_replace('fax_no,', '' ,$verify_details); 
				}
			}
			if(in_array("factory_headoffice", $remark_field)) {
				if(empty($factory_headoffice)){
					$verify_details = str_replace('factory_headoffice,', '' ,$verify_details); 
				}
			}
			if(in_array("factory_communication", $remark_field)) {
				if(empty($factory_communication)){
					$verify_details = str_replace('factory_communication,', '' ,$verify_details); 
				}
			}
			if(in_array("date_of_amenability_id", $remark_field)) {
				if(empty($date_of_amenability_id)){
					$verify_details = str_replace('date_of_amenability_id,', '' ,$verify_details); 
				}
			}
			if(in_array("worker_details", $remark_field)) {
				if(empty($worker_details)){
					$verify_details = str_replace('worker_details,', '' ,$verify_details); 
				}
			}
			if(in_array("power_details", $remark_field)) {
				if(empty($power_details)){
					$verify_details = str_replace('power_details,', '' ,$verify_details); 
				}
			}
			if(in_array("nature_details", $remark_field)) {
				if(empty($nature_details)){
					$verify_details = str_replace('nature_details,', '' ,$verify_details); 
				}
			}
		}
		$verify_duplicate = $verify_details. $factory_name.$factory_pan.$gstin_no.$udyog_aadhaar.$trade_no.$plan_approval_no.$factory_previous_name.$cin_no.$enargy_no.$wbpcb_id.$zone_name.$telephone_no.$mobile_no.$altmobile_no.$email_no.$fax_no.$factory_headoffice.$factory_communication.$date_of_amenability_id.$worker_details.$power_details.$nature_details;
		
		
		$verify_details = implode(',', array_unique(explode(',', $verify_duplicate)));



	  
	  //-------------Document-------------------------------
	if($wbpcb_category_name == 1){
			$caf_upload_doc_cat =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'DOC', $factorytype_id,$reference_no, 'wbpcb_id');
	}if($wbpcb_category_name == 2){
			$caf_upload_doc_cat =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'DOC', $factorytype_id,$reference_no, 'wbpcb_id');
	}if($wbpcb_category_name == 3){
			$caf_upload_doc_cat =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'DOC', $factorytype_id,$reference_no, 'wbpcb_id');
	}if($wbpcb_category_name == 4){
			$caf_upload_doc_cat =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'INT', $factorytype_id,$reference_no, 'wbpcb_id');
	}
	
//---------------End Documents--------------------------------	
foreach ($caf_upload_doc_cat as $record) {
	
		 $documents_list .= !empty($val['documents_list_factory_cat_chk_'.$record->id])?$record->id.',':'';
	}

$caf_upload_doc_all =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'DOC', $factorytype_id,$reference_no, 'factory_name');
foreach ($caf_upload_doc_all as $record) {
	
	 $documents_list .= !empty($val['documents_list_chk_'.$record->id])?$record->id.',':'';
}
$caf_upload_doc_premission =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'DOC', $factorytype_id,$reference_no, 'premises_address');
foreach ($caf_upload_doc_premission as $record) {
	
	 $documents_list .= !empty($val['documents_list_factory_adress_chk_'.$record->id])?$record->id.',':'';
}
$caf_upload_doc_caf =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'CAF', $factorytype_id,$reference_no, 'period_for_application_id');
foreach ($caf_upload_doc_caf as $record) {
	 $documents_list .= !empty($val['documents_list_factory_caf_chk_'.$record->id])?$record->id.',':'';
	
}
$caf_upload_doc_power_details =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'DOC', $factorytype_id,$reference_no, 'power_details');

foreach ($caf_upload_doc_power_details as $record) {
	
	$documents_list .= !empty($val['documents_list_factory_power_details_chk_'.$record->id])?$record->id.',':'';		
}

	$identity_flag_all = NULL;
	$irregularities_details = fun_fetch_irregularities_details($identity_flag_all,$application_id,$reference_no,$factorytype_id,$service_id); 
 	//$remark_id = get_remark_id($application_id,$reference_no,$userid,$rid);


 	if(!empty($irregularities_details)){
		foreach($irregularities_details as $row_irregularities_details){
			$remark_table_id = $row_irregularities_details->remark_table_id;
			$checklist_observations_ref_id = $row_irregularities_details->checklist_observations_ref_id;
		}

	  if($remark_table_id==$remark_id){
		 $cafa_remarks = array(
								
								'sending_time' 	  	 => date('Y-m-d h:i'),
								'remark_type'	  	 => 'n',
								'verify_details'	 => $verify_details,
								'doc_verify'		 => $documents_list,
								
									
						);
					
				$queryupdate_remarks		 =	db_update('fa_cafa_remarks');
				$queryupdate_remarks	 	->	fields($cafa_remarks);
				$queryupdate_remarks		 ->	condition('id',$remark_id,'=');	
				
				$queryupdate_remarks		 ->	execute();
				
	 }else{
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
								'doc_verify'		 => $documents_list,
								'service_id'		 => $service_id
									
						);

	$remark_id = db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();
	
	 $checklist_observations_ref = array(
								'remark_table_id'	 => $remark_id,
								
						);
					
				$queryupdate_observations_ref		 =	db_update('fa_checklist_observations_ref');
				$queryupdate_observations_ref	 	->	fields($checklist_observations_ref);
				$queryupdate_observations_ref		 ->	condition('id',$checklist_observations_ref_id,'=');	
				$queryupdate_observations_ref		 ->	execute();
	
	
	 }
	$identity_flag = 'factory_name';
	$irregularities_details_name =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factorytype_id,$service_id);
	if(!empty($irregularities_details_name)){
		foreach($irregularities_details_name as $row_irregularities_details_name){
			$irregularities_update = array(
	  										
											'remark_by_ad'					=> $val['factory_adchk_'.$row_irregularities_details_name->id],
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											
											
	  									);
				$queryupdate_irregularities		 =	db_update('fa_checklist_observations');
				$queryupdate_irregularities		 ->	fields($irregularities_update);
				$queryupdate_irregularities		 ->	condition('id',$row_irregularities_details_name->id,'=');	
				$queryupdate_irregularities		 ->	execute();
		}
		
	}else{
		
		 $irregularities_1 = array(
	  										'irregularities'				=> $factory_name_irregularities_1,
											'remark_by_ad'					=> $factory_name_chk_1,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'factory_name',
											
	  									);
	 $irregularities_2 = array(
	  										'irregularities'				=> $factory_name_irregularities_2,
											'remark_by_ad'					=> $factory_name_chk_2,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'factory_name',
											
	  									);
	$irregularities_1_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_1) ->	execute();
	$irregularities_2_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_2) ->	execute(); 
	}
	
	$identity_flag = 'nature_details';
	$irregularities_details_nature_details =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factorytype_id,$service_id);	

	if(!empty($irregularities_details_nature_details)){
		foreach($irregularities_details_nature_details as $row_irregularities_details_nature_details){
			$irregularities_update = array(
	  										
											'remark_by_ad'					=> $val['factory_adchk_'.$row_irregularities_details_nature_details->id],
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											
											
	  									);
				$queryupdate_irregularities		 =	db_update('fa_checklist_observations');
				$queryupdate_irregularities		 ->	fields($irregularities_update);
				$queryupdate_irregularities		 ->	condition('id',$row_irregularities_details_nature_details->id,'=');	
				$queryupdate_irregularities		 ->	execute();
		}
		
	}else{
		$irregularities_3 = array(
	  										'irregularities'				=> $factory_nature_details_irregularities_1,
											'remark_by_ad'					=> $factory_nature_details_irregularities_chk_1,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'nature_details',
											
	  									);
	
	 $irregularities_4 = array(
	  										'irregularities'				=> $factory_nature_details_irregularities_2,
											'remark_by_ad'					=> $factory_nature_details_irregularities_chk_2,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'nature_details',
											
	  									);
										
	  $irregularities_5 = array(
	  										'irregularities'				=> $factory_nature_details_irregularities_3,
											'remark_by_ad'					=> $factory_nature_details_irregularities_chk_3,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'nature_details',
											
	  									);
										
	 $irregularities_6 = array(
	  										'irregularities'				=> $factory_nature_details_irregularities_4,
											'remark_by_ad'					=> $factory_nature_details_irregularities_chk_4,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'nature_details',
											
	  									);
										
	$irregularities_7= array(
	  										'irregularities'				=> $factory_nature_details_irregularities_5,
											'remark_by_ad'					=> $factory_nature_details_irregularities_chk_5,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'nature_details',
										  
	  									);
	$irregularities_3_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_3) ->	execute(); 
	$irregularities_4_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_4) ->	execute();
	$irregularities_5id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_5) ->	execute();
	$irregularities_6_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_6) ->	execute();
	$irregularities_7_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_7) ->	execute();
	}
	$identity_flag = 'wbpcb_id';
	$irregularities_details_catagory =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factorytype_id,$service_id);
	if(!empty($irregularities_details_catagory)){
		foreach($irregularities_details_catagory as $row_irregularities_details_catagory){
			$irregularities_update = array(
	  										
											'remark_by_ad'					=> $val['factory_adchk_'.$row_irregularities_details_catagory->id],
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											
											
	  									);
				$queryupdate_irregularities		 =	db_update('fa_checklist_observations');
				$queryupdate_irregularities		 ->	fields($irregularities_update);
				$queryupdate_irregularities		 ->	condition('id',$row_irregularities_details_catagory->id,'=');	
				$queryupdate_irregularities		 ->	execute();
		}
		
	}else{ 
	$irregularities_8 = array(
	  										'irregularities'				=> $factory_catagory_irregularities_1,
											'remark_by_ad'					=> $factory_catagory_irregularities_chk_1,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'wbpcb_id',
											
	  									);
										
	  $irregularities_9 = array(
	  										'irregularities'				=> $factory_catagory_irregularities_2,
											'remark_by_ad'					=> $factory_catagory_irregularities_chk_2,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'wbpcb_id',
											
	  									);
	$irregularities_8_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_8) ->	execute();
	$irregularities_9_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_9) ->	execute();
	}
	$identity_flag = 'premises_address';
	$irregularities_details_location =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factorytype_id,$service_id); 
	if(!empty($irregularities_details_location)){
		foreach($irregularities_details_location as $row_irregularities_details_location){
			$irregularities_update = array(
	  										
											'remark_by_ad'					=> $val['factory_adchk_'.$row_irregularities_details_location->id],
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											
											
	  									);
				$queryupdate_irregularities		 =	db_update('fa_checklist_observations');
				$queryupdate_irregularities		 ->	fields($irregularities_update);
				$queryupdate_irregularities		 ->	condition('id',$row_irregularities_details_location->id,'=');	
				$queryupdate_irregularities		 ->	execute();
		}
		
	}else{
	$irregularities_10 = array(
	  										'irregularities'				=> $factory_addres_irregularities_1,
											'remark_by_ad'					=> $factory_addres_chk_1,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'premises_address',
											
	  									); 
										
	 $irregularities_11= array(
	  										'irregularities'				=> $factory_addres_irregularities_2,
											'remark_by_ad'					=> $factory_addres_chk_2,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'premises_address',
											
	  									); 

	 $irregularities_12 = array(
	  										'irregularities'				=> $factory_addres_irregularities_3,
											'remark_by_ad'					=> $factory_addres_chk_3,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'premises_address',
											
	  									); 
											
	 $irregularities_13 = array(
	  										'irregularities'				=> $factory_addres_irregularities_4,
											'remark_by_ad'					=> $factory_addres_chk_4,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'premises_address',
											
	  									);
										
	$irregularities_14 = array(
	  										'irregularities'				=> $factory_addres_irregularities_5,
											'remark_by_ad'					=> $factory_addres_chk_5,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'premises_address',
											
	  									);  
		$irregularities_10_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_10) ->	execute();
		$irregularities_11_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_11) ->	execute();
		$irregularities_12_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_12) ->	execute();
		$irregularities_13_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_13) ->	execute(); 
		$irregularities_14_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_14) ->	execute(); 
	}
	$identity_flag = 'date_of_amenability_id';
	$irregularities_details_amenability =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factorytype_id,$service_id);
   if(!empty($irregularities_details_amenability)){
		foreach($irregularities_details_amenability as $row_irregularities_details_amenability){
			$irregularities_update = array(
	  										
											'remark_by_ad'					=> $val['factory_adchk_'.$row_irregularities_details_amenability->id],
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											
											
	  									);
				$queryupdate_irregularities		 =	db_update('fa_checklist_observations');
				$queryupdate_irregularities		 ->	fields($irregularities_update);
				$queryupdate_irregularities		 ->	condition('id',$row_irregularities_details_amenability->id,'=');	
				$queryupdate_irregularities		 ->	execute();
		}
		
	}else{
		$irregularities_15 = array(
	  										'irregularities'				=> $factory_amenability_irregularities_1,
											'remark_by_ad'					=> $factory_amenability_irregularities_chk_1,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'date_of_amenability_id',
											
	  									); 
		 $irregularities_16 = array(
	  										'irregularities'				=> $factory_amenability_irregularities_2,
											'remark_by_ad'					=> $factory_amenability_irregularities_chk_2,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'date_of_amenability_id',
											
	  									); 
	 $irregularities_17 = array(
	  										'irregularities'				=> $factory_amenability_irregularities_3,
											'remark_by_ad'					=> $factory_amenability_irregularities_chk_3,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'date_of_amenability_id',
											
	  									); 
	
	$irregularities_15_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_15) ->	execute(); 
	$irregularities_16_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_16) ->	execute(); 
	$irregularities_17_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_17) ->	execute(); 
	
	}
	$identity_flag ='worker_details' ;
	$irregularities_details_worker_details =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factorytype_id,$service_id);
	if(!empty($irregularities_details_worker_details)){
		foreach($irregularities_details_worker_details as $row_irregularities_details_worker_details){
			$irregularities_update = array(
	  										
											'remark_by_ad'					=> $val['factory_adchk_'.$row_irregularities_details_worker_details->id],
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											
											
	  									);
				$queryupdate_irregularities		 =	db_update('fa_checklist_observations');
				$queryupdate_irregularities		 ->	fields($irregularities_update);
				$queryupdate_irregularities		 ->	condition('id',$row_irregularities_details_worker_details->id,'=');	
				$queryupdate_irregularities		 ->	execute();
		}
		
	}else{
		 $irregularities_18 = array(
	  										'irregularities'				=> $factory_worker_irregularities_1,
											'remark_by_ad'					=> $factory_worker_irregularities_chk_1,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'worker_details',
											
	  									); 
	$irregularities_18_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_18) ->	execute(); 
	}
	$identity_flag ='power_details' ;
	$irregularities_details_power_details =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factorytype_id,$service_id);
	if(!empty($irregularities_details_power_details)){
		foreach($irregularities_details_power_details as $row_irregularities_details_power_details){
			$irregularities_update = array(
	  										
											'remark_by_ad'					=> $val['factory_adchk_'.$row_irregularities_details_power_details->id],
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											
											
	  									);
				$queryupdate_irregularities		 =	db_update('fa_checklist_observations');
				$queryupdate_irregularities		 ->	fields($irregularities_update);
				$queryupdate_irregularities		 ->	condition('id',$row_irregularities_details_power_details->id,'=');	
				$queryupdate_irregularities		 ->	execute();
		}
		
	}else{
		  $irregularities_19 = array(
	  										'irregularities'				=> $factory_power_details_irregularities_1,
											'remark_by_ad'					=> $factory_power_details_irregularities_chk_1,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'power_details',
											
	  									); 
	   $irregularities_20 = array(
	  										'irregularities'				=> $factory_power_details_irregularities_2,
											'remark_by_ad'					=> $factory_power_details_irregularities_chk_2,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'power_details',
											
	  									); 
	  $irregularities_21 = array(
	  										'irregularities'				=> $factory_power_details_irregularities_3,
											'remark_by_ad'					=> $factory_power_details_irregularities_chk_3,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'power_details',
											
	  									); 
	  $irregularities_22 = array(
	  										'irregularities'				=> $factory_power_details_irregularities_4,
											'remark_by_ad'					=> $factory_power_details_irregularities_chk_4,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'power_details',
											
	  									);
	$irregularities_19_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_19) ->	execute(); 
	$irregularities_20_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_20) ->	execute(); 
	$irregularities_21_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_21) ->	execute(); 
	$irregularities_22_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_22) ->	execute(); 
	}
 }else{


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
								'doc_verify'		 => $documents_list,
								'service_id'		 => $service_id
									
						);

	$remark_id = db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();
    $checklist_observations_ref = array(
	  										'is_chemical'		=> $is_chemical,
											'remark_table_id'	=> $remark_id,
											'application_id'	=> $application_id,
											'factory_type_id' 	=> $factorytype_id,
											'reference_number'  => $reference_no,
											'service_id'  		=> $service_id,
											'created_by'		=> $userid,
											'created_date'		=> date('Y-m-d')
											
	  									);
	
						
	$checklist_observations_ref_id 		 =	db_insert('fa_checklist_observations_ref')->fields($checklist_observations_ref) ->	execute();					
	  
	  $irregularities_1 = array(
	  										'irregularities'				=> $factory_name_irregularities_1,
											'remark_by_ad'					=> $factory_name_chk_1,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'factory_name',
											
	  									);
	 $irregularities_2 = array(
	  										'irregularities'				=> $factory_name_irregularities_2,
											'remark_by_ad'					=> $factory_name_chk_2,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'factory_name',
											
	  									);
	$irregularities_3 = array(
	  										'irregularities'				=> $factory_nature_details_irregularities_1,
											'remark_by_ad'					=> $factory_nature_details_irregularities_chk_1,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'nature_details',
											
	  									);
	
	 $irregularities_4 = array(
	  										'irregularities'				=> $factory_nature_details_irregularities_2,
											'remark_by_ad'					=> $factory_nature_details_irregularities_chk_2,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'nature_details',
											
	  									);
										
	  $irregularities_5 = array(
	  										'irregularities'				=> $factory_nature_details_irregularities_3,
											'remark_by_ad'					=> $factory_nature_details_irregularities_chk_3,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'nature_details',
											
	  									);
										
	 $irregularities_6 = array(
	  										'irregularities'				=> $factory_nature_details_irregularities_4,
											'remark_by_ad'					=> $factory_nature_details_irregularities_chk_4,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'nature_details',
											
	  									);
										
	$irregularities_7 = array(
	  										'irregularities'				=> $factory_nature_details_irregularities_5,
											'remark_by_ad'					=> $factory_nature_details_irregularities_chk_5,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'nature_details',
										  
	  									);
										
										
	 $irregularities_8 = array(
	  										'irregularities'				=> $factory_catagory_irregularities_1,
											'remark_by_ad'					=> $factory_catagory_irregularities_chk_1,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'wbpcb_id',
											
	  									);
										
	  $irregularities_9= array(
	  										'irregularities'				=> $factory_catagory_irregularities_2,
											'remark_by_ad'					=> $factory_catagory_irregularities_chk_2,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'wbpcb_id',
											
	  									);
										
		$irregularities_10 = array(
	  										'irregularities'				=> $factory_addres_irregularities_1,
											'remark_by_ad'					=> $factory_addres_chk_1,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'premises_address',
											
	  									); 
										
	 $irregularities_11= array(
	  										'irregularities'				=> $factory_addres_irregularities_2,
											'remark_by_ad'					=> $factory_addres_chk_2,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'premises_address',
											
	  									); 

	 $irregularities_12 = array(
	  										'irregularities'				=> $factory_addres_irregularities_3,
											'remark_by_ad'					=> $factory_addres_chk_3,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'premises_address',
											
	  									); 
											
	 $irregularities_13 = array(
	  										'irregularities'				=> $factory_addres_irregularities_4,
											'remark_by_ad'					=> $factory_addres_chk_4,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'premises_address',
											
	  									);
										
	$irregularities_14 = array(
	  										'irregularities'				=> $factory_addres_irregularities_5,
											'remark_by_ad'					=> $factory_addres_chk_5,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'premises_address',
											
	  									);  
	$irregularities_15 = array(
	  										'irregularities'				=> $factory_amenability_irregularities_1,
											'remark_by_ad'					=> $factory_amenability_irregularities_chk_1,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'date_of_amenability_id',
											
	  									); 
	  $irregularities_16 = array(
	  										'irregularities'				=> $factory_amenability_irregularities_2,
											'remark_by_ad'					=> $factory_amenability_irregularities_chk_2,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'date_of_amenability_id',
											
	  									); 
	 $irregularities_17 = array(
	  										'irregularities'				=> $factory_amenability_irregularities_3,
											'remark_by_ad'					=> $factory_amenability_irregularities_chk_3,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'date_of_amenability_id',
											
	  									); 
	
	 $irregularities_18 = array(
	  										'irregularities'				=> $factory_worker_irregularities_1,
											'remark_by_ad'					=> $factory_worker_irregularities_chk_1,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'worker_details',
											
	  									); 
	  $irregularities_19 = array(
	  										'irregularities'				=> $factory_power_details_irregularities_1,
											'remark_by_ad'					=> $factory_power_details_irregularities_chk_1,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'power_details',
											
	  									); 
	   $irregularities_20 = array(
	  										'irregularities'				=> $factory_power_details_irregularities_2,
											'remark_by_ad'					=> $factory_power_details_irregularities_chk_2,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'power_details',
											
	  									); 
	  $irregularities_21 = array(
	  										'irregularities'				=> $factory_power_details_irregularities_3,
											'remark_by_ad'					=> $factory_power_details_irregularities_chk_3,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'power_details',
											
	  									); 
	  $irregularities_22 = array(
	  										'irregularities'				=> $factory_power_details_irregularities_4,
											'remark_by_ad'					=> $factory_power_details_irregularities_chk_4,
											'ad_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'power_details',
											
	  									); 
	$irregularities_1_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_1) ->	execute();
	$irregularities_2_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_2) ->	execute(); 
	$irregularities_3_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_3) ->	execute(); 
	$irregularities_4_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_4) ->	execute();
	$irregularities_5_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_5) ->	execute();
	$irregularities_6_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_6) ->	execute();
	$irregularities_7_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_7) ->	execute();
	$irregularities_8_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_8) ->	execute();
	$irregularities_9_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_9) ->	execute();
	$irregularities_10_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_10) ->	execute();
	$irregularities_11_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_11) ->	execute();
	$irregularities_12_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_12) ->	execute();
	$irregularities_13_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_13) ->	execute(); 
	$irregularities_14_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_14) ->	execute(); 
	$irregularities_15_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_15) ->	execute(); 
	$irregularities_16_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_16) ->	execute(); 
	$irregularities_17_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_17) ->	execute(); 
	$irregularities_18_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_18) ->	execute(); 
	$irregularities_19_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_19) ->	execute(); 
	$irregularities_20_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_20) ->	execute(); 
	$irregularities_21_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_21) ->	execute(); 
	$irregularities_22_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_22) ->	execute(); 
	
	
 }

if($factorytype_id  == 1){
		
		if($recomended_worker_total>=10 && $recomended_power>0){
			
			
			if($recomended_power_actual_unit == 'HP'){
				$recommande_type_power_station = 'other';
				$recommanded_installed_power_hp = $recomended_power_actual_unit;
				}
				else{
					$recommande_type_power_station = 'power_generating_station';
					$recommanded_installed_power_hp = $recomended_power*1.34102;//(1Kw => 1.34102 Hp)
			}
			$power_details_yearly =array(
				'recommanded_power_unit'				=> $recomended_power_actual_unit,
				'recommanded_installed_power'			=> $recomended_power,
				'recommanded_installed_power_hp'		=> $recommanded_installed_power_hp,
				'recommande_type_power_station'			=> $recommande_type_power_station,
				
				'recommanded_by_id' 					=> $userid,
				'recommanded_by_name' 					=> $remark_by_name,
				'recommanded_by_rid' 					=> $rid,
				
			);
		   
		
			$query_power 		 =	db_update('fa_power_details');
			$query_power		 ->	fields($power_details_yearly);
			$query_power	     ->	condition('id',$power_id,'=');
			$query_power		 ->	execute();
			
			$worker_array =array(
				'recomended_total_worker'	=> $recomended_worker_total,				
				'recommanded_by_id' 		=> $userid,
				'recommanded_by_name' 		=> $remark_by_name,
				'recommanded_by_rid' 		=> $rid,
				
		   	);
		  
			$query_worker 		 =	db_update('fa_worker_details');
			$query_worker		 ->	fields($worker_array);
			$query_worker	     ->	condition('id',$worker_id,'=');
			$query_worker		 ->	execute();

			//////////////////OTHER TABLE UPDATE/////////////////
			
	
			
		  
		}else{
			
			drupal_set_message('This applicaion under Section 2m(i),Total no of worker will be more than equal to 10 and installed power unit will be more than 0' ,'warning');
		}
	}
if($factorytype_id == 2){
		if($worker_total >=20){
		$worker_array =array(
				'recomended_total_worker'	=> $recomended_worker_total,				
				'recommanded_by_id' 		=> $userid,
				'recommanded_by_name' 		=> $remark_by_name,
				'recommanded_by_rid' 		=> $rid,
				
		   	);
		
			$query_worker 		 =	db_update('fa_worker_details');
			$query_worker		 ->	fields($worker_array);
			$query_worker	     ->	condition('id',$worker_id,'=');
			$query_worker		 ->	execute();

			
		
		}else{
			drupal_set_message('This application under Section 2m(ii),Total no of worker will be more than equal to 20 and installed power unit will be 0' ,'warning');
		}
	}
if($factorytype_id == 3){
	if($recomended_power == 0 && $recomended_worker_total<=19){
			
	
			if($recomended_power_actual_unit == 'HP'){
				$recommande_type_power_station = 'other';
				$recommanded_installed_power_hp = $recomended_power_actual_unit;
				}
				else{
					$recommande_type_power_station = 'power_generating_station';
					$recommanded_installed_power_hp = $recomended_power*1.34102;//(1Kw => 1.34102 Hp)
			}
			$power_details_yearly =array(
				'recommanded_power_unit'				=> $recomended_power_actual_unit,
				'recommanded_installed_power'			=> $recomended_power,
				'recommanded_installed_power_hp'		=> $recommanded_installed_power_hp,
				'recommande_type_power_station'			=> $recommande_type_power_station,
				'recommanded_by_id' 					=> $userid,
				'recommanded_by_name' 					=> $remark_by_name,
				'recommanded_by_rid' 					=> $rid,
				
			);
		   
		
			$query_power 		 =	db_update('fa_power_details');
			$query_power		 ->	fields($power_details_yearly);
			$query_power	     ->	condition('id',$power_id,'=');
			$query_power		 ->	execute();
				
			$worker_array =array(
				'recomended_total_worker'	=> $recomended_worker_total,				
				'recommanded_by_id' 		=> $userid,
				'recommanded_by_name' 		=> $remark_by_name,
				'recommanded_by_rid' 		=> $rid,
				
		   	);
		  
			$query_worker 		 =	db_update('fa_worker_details');
			$query_worker		 ->	fields($worker_array);
			$query_worker	     ->	condition('id',$worker_id,'=');
			$query_worker		 ->	execute();

			
		
		}if($recomended_power == 0 && $recomended_worker_total>19){
			drupal_set_message('This application under Section 85,Total no of worker will be less than equal to 19 and installed power unit will be  0' ,'warning');
		}if($recomended_power != 0 && $recomended_worker_total<=9){
			
	
			if($recomended_power_actual_unit == 'HP'){
				$recommande_type_power_station = 'other';
				$recommanded_installed_power_hp = $recomended_power_actual_unit;
				}
				else{
					$recommande_type_power_station = 'power_generating_station';
					$recommanded_installed_power_hp = $recomended_power*1.34102;//(1Kw => 1.34102 Hp)
			}
			$power_details_yearly =array(
				'recommanded_power_unit'				=> $recomended_power_actual_unit,
				'recommanded_installed_power'			=> $recomended_power,
				'recommanded_installed_power_hp'		=> $recommanded_installed_power_hp,
				'recommande_type_power_station'			=> $recommande_type_power_station,
				'recommanded_by_id' 					=> $userid,
				'recommanded_by_name' 					=> $remark_by_name,
				'recommanded_by_rid' 					=> $rid,
				
			);
		   
		
			$query_power 		 =	db_update('fa_power_details');
			$query_power		 ->	fields($power_details_yearly);
			$query_power	     ->	condition('id',$power_id,'=');
			$query_power		 ->	execute();
				
			$worker_array =array(
				'recomended_total_worker'	=> $recomended_worker_total,				
				'recommanded_by_id' 		=> $userid,
				'recommanded_by_name' 		=> $remark_by_name,
				'recommanded_by_rid' 		=> $rid,
				
		   	);
		  
			$query_worker 		 =	db_update('fa_worker_details');
			$query_worker		 ->	fields($worker_array);
			$query_worker	     ->	condition('id',$worker_id,'=');
			$query_worker		 ->	execute();

			
		
		}if($recomended_power != 0 && $recomended_worker_total>9){
			drupal_set_message('This application under Section 85,Total no of worker will be less than equal to 9 and installed power unit will be more than 0' ,'warning');
		
		}
	}
	
$approval_status = 	array('recomended_date_of_amenability' => $recomended_date_of_amenability,'modification_date'=>date('Y-m-d'));
$queryabc 		 =	db_update('fa_cafa');
$queryabc		 ->	fields($approval_status);
$queryabc		 ->	condition('id',$application_id,'=');
$queryabc		 ->	condition('service_id',$service_id,'=');
$queryabc	     ->	condition('factory_typeid',$factorytype_id,'=');
$queryabc		 ->	condition('reference_number',$reference_no,'=');
$queryabc		 ->	execute();

drupal_set_message('Your observation of application is successfully submitted');
	  
}


?> 