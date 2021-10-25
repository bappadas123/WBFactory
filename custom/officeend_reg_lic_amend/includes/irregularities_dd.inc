<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function irregularities_dd($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$referenceno)
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
	$irregularities_name = array('Agree'=>'Agree','NotAgree'=>'Not Agree');
	
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
        '#markup' => t('<div class="content">
		<h3>Application for Registration and Grant of Licence.All inputs are provided by applicant only.
All inputs are to be verified by officials</h3>')
    );
	
	 $form['factory_part_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('Irregularities for Scrutiny of Applications '),
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
	
  
	
	$identity_flag = 'factory_name';
	$irregularities_details_name =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factory_type_id,$service_id);
			
		$form['factory_part_info']['factory_name_irregularities_table'] = array(
	   
	
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12"><div id="factory_name_chceking_id">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>Irregularities for Scrutiny of Applications about Name of the Factory </th>
								<th>Irregularities by AD</th>
								<th>Action</th>
								<th>Irregularities by JD</th>
								
							</tr>'
					);
	
		
		if(!empty($irregularities_details_name)){
			foreach($irregularities_details_name as $row_irregularities_details_name){
				$remark_by_ad_chk = $row_irregularities_details_name->remark_by_ad;
				if($remark_by_ad_chk =='NotAgree'){
					$remark_by_ad = 0;
				}if($remark_by_ad_chk =='Agree'){
					$remark_by_ad = 1;
				}
				$form['factory_part_info']['factory_name_irregularities_'.$row_irregularities_details_name->id] = array(
				'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12"><div id="factory_name_irregularities_'.$row_irregularities_details_name->id.'">',
				'#suffix' 			=> '</td></div></div>',
				'#type' 			=> 'textarea',
				'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
				'#default_value' 	=>$row_irregularities_details_name->irregularities,
			);
				
			$form['factory_part_info']['factory_adchk_'.$row_irregularities_details_name->id] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				'#type' 			=> 'checkbox',
				'#attributes' 		=> array('disabled' => TRUE),
				'#default_value' 	=>$remark_by_ad
			);
			$form['factory_part_info']['factory_ddchk_'.$row_irregularities_details_name->id] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				
				'#default_value' 	=>$row_irregularities_details_name->remark_by_dd,
			);
			$form['factory_part_info']['factory_jdchk_'.$row_irregularities_details_name->id] = array(
					'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
					'#suffix' 			=> '</div></td></tr>',
					'#type' 			=> 'radios',
					'#options'         => $irregularities_name,
					'#attributes' 		=> array('disabled' => TRUE),
					'#default_value' 	=>$row_irregularities_details_name->remark_by_jd,
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
       		 '#suffix' 			=> '</div></td>',
			 '#type' 			=> 'checkbox',
    		  '#attributes' 	=> array('disabled' => TRUE),
			  );

			  $form['factory_part_info']['factory_name_ddchk_1'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 			=> 'radios',
    		 '#options'         => $irregularities_name,
			 '#default_value' 	=>'NotAgree',
			
			);

			$form['factory_part_info']['factory_name_jdchk_1'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td></tr>',
			 '#type' 			=> 'radios',
    		 '#options'         => $irregularities_name,
			 '#default_value' 	=>'NotAgree',
			 '#attributes' 	=> array('disabled' => TRUE),
			 
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
       		 '#suffix' 			=> '</div></td>',
			'#type' 			=> 'checkbox',
    		 '#attributes' 	=> array('disabled' => TRUE),
			
			 );	
			 $form['factory_part_info']['factory_name_ddchk_2'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 			=> 'radios',
    		 '#options'         => $irregularities_name,
			 '#default_value' 	=>'NotAgree',
			
			);	
	
			$form['factory_part_info']['factory_name_jdchk_2'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td></tr>',
			 '#type' 			=> 'radios',
    		 '#options'         => $irregularities_name,
			 '#default_value' 	=>'NotAgree',
			'#attributes' 	=> array('disabled' => TRUE),
			);	
		
		}
			
		$form['factory_part_info']['factory_name_irregularities_end'] 	= array(
			'#suffix' 	=> '</table><div></div>',
		);
		


    
	
	$manufacturing_details = get_manufacturing($application_id,$service_id,$factory_type_id,$reference_no);
	foreach($manufacturing_details as $manufacturing){
		$nature_manufacturing = $manufacturing->nature_manufacturing;
		$manufacturing_id 	  = $manufacturing->id;
	}
	
	
	$identity_flag = 'nature_details';
	$irregularities_details_nature_details =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factory_type_id,$service_id);
	
	$form['factory_part_info']['factory_nature_details_irregularities_table'] 	= array(
	   		'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th >Irregularities for Scrutiny of Applications according to Manufacturing Process of the Factory </th>
								<th>Irregularities by AD</th>
								<th>Action</th>
								<th>Irregularities by JD</th>
							</tr>'
					);
	if(!empty($irregularities_details_nature_details)){
		foreach($irregularities_details_nature_details as $row_irregularities_details_nature_details){
			$remark_by_ad_chk=$row_irregularities_details_nature_details->remark_by_ad;
				
				if($remark_by_ad_chk =='NotAgree'){
					$remark_by_ad = 0;
				}if($remark_by_ad_chk =='Agree'){
					$remark_by_ad = 1;
				}
			$form['factory_part_info']['factory_nature_details_irregularities_'.$row_irregularities_details_nature_details->id] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=> $row_irregularities_details_nature_details->irregularities,
			
		);
	
		
		$form['factory_part_info']['factory_adchk_'.$row_irregularities_details_nature_details->id] = array(
   			 '#prefix' 				=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 				=> '</div></td>',
			 '#type' 				=> 'checkbox',
			 '#default_value' 		=>	$remark_by_ad,
			  '#attributes' 	=> array('disabled' => TRUE),
		  );
		  
		$form['factory_part_info']['factory_ddchk_'.$row_irregularities_details_nature_details->id] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
		 	'#type' 			=> 'radios',
		 	'#options'         => $irregularities_name,
			 '#default_value' 	=>$row_irregularities_details_name->remark_by_dd,
			
		);
		$form['factory_part_info']['factory_jdchk_'.$row_irregularities_details_nature_details->id] = array(
			'#prefix' 				=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 				=> '</div></td></tr>',
		 	'#type' 				=> 'radios',
		  	'#options'         	=>  $irregularities_name,
		  	'#default_value' 		=>	$row_irregularities_details_nature_details->remark_by_jd,
		  	'#attributes' 		=> array('disabled' => TRUE),
		);
	
	}
	}else{
		$form['factory_part_info']['factory_nature_details_irregularities_1'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'1. The nature of business / manufacturing*activities as mentioned in the Common Application Form does not match with that as permitted as per the supporting document – Memorandum & Articles of Association / Partnership Deed / Certificate of Proprietorship / Trade Licence / Clearance from WBPCB* – uploadedwith the application.'
			
		);
	
		$form['factory_part_info']['factory_nature_details_irregularities_chk_1'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 				=> 'checkbox',
			 '#attributes' 		=> array('disabled' => TRUE),	
		  
		);
		$form['factory_part_info']['factory_nature_details_irregularities_ddchk_1'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
		 	'#type' 			=> 'radios',
		  	'#options'         => $irregularities_name,
			'#default_value' 	=>'NotAgree',
			
	  	);
		$form['factory_part_info']['factory_nature_details_irregularities_jdchk_1'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td></tr>',
		 	'#type' 			=> 'radios',
		  	'#options'         	=> $irregularities_name,
		  	'#default_value' 	=>'NotAgree',
		  	'#attributes' 		=> array('disabled' => TRUE),	
		
	  	);
		  


		$form['factory_part_info']['factory_nature_details_irregularities_2'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'2. The major / manufacturing process mentioned in the application does not match with that found being carried out in the premises, during inspection of the said premises by the respective Area Officer / Assistant Director / Inspector of Factories.'
			
		);
		$form['factory_part_info']['factory_nature_details_irregularities_chk_2'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 				=> 'checkbox',
			'#attributes' 		=> array('disabled' => TRUE),	 
		);
		$form['factory_part_info']['factory_nature_details_irregularities_ddchk_2'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
		 	'#type' 			=> 'radios',
		  	'#options'         => $irregularities_name,
			'#default_value' 	=>'NotAgree',
			
	  	);
		$form['factory_part_info']['factory_nature_details_irregularities_jdchk_2'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td></tr>',
		 	'#type' 			=> 'radios',
		  	'#options'         	=> $irregularities_name,
		  	'#default_value' 	=>'NotAgree',
		  	'#attributes' 		=> array('disabled' => TRUE),	
		
	  	);
		$form['factory_part_info']['factory_nature_details_irregularities_3'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'3. The manufacturing processfound being carried out in the premises, during inspection of the said premises did not match with that for which the Approval of Plan was obtained from the Chief Inspector of Factories.'
		);
		$form['factory_part_info']['factory_nature_details_irregularities_chk_3'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 				=> 'checkbox',
			'#attributes' 		=> array('disabled' => TRUE),	
		);
		$form['factory_part_info']['factory_nature_details_irregularities_ddchk_3'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
		 	'#type' 			=> 'radios',
		  	'#options'         => $irregularities_name,
			'#default_value' 	=>'NotAgree',
			
	  	);
		$form['factory_part_info']['factory_nature_details_irregularities_jdchk_3'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td></tr>',
		 	'#type' 			=> 'radios',
		  	'#options'         	=> $irregularities_name,
		  	'#default_value' 	=>'NotAgree',
		  	'#attributes' 		=> array('disabled' => TRUE),	
		
	  	);
		$form['factory_part_info']['factory_nature_details_irregularities_4'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'4. Although the manufacturing process that has been mentioned in the application as ‘likely to be carried out’ in the period for which Licence is required, differs from the process which was carried out in the immediate preceding period, it appears that application for Approval of Plan (for the process to be carried out) has not been submitted / uploaded in the Official online Portal of this Directorate (along with this application or separately).'
			
		);
	
		
		$form['factory_part_info']['factory_nature_details_irregularities_chk_4'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 				=> 'checkbox',
			 '#attributes' 		=> array('disabled' => TRUE),	
			  
		);
		$form['factory_part_info']['factory_nature_details_irregularities_ddchk_4'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
		 	'#type' 			=> 'radios',
		  	'#options'         => $irregularities_name,
			'#default_value' 	=>'NotAgree',
			
	  	);
		$form['factory_part_info']['factory_nature_details_irregularities_jdchk_4'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td></tr>',
		 	'#type' 			=> 'radios',
		  	'#options'         	=> $irregularities_name,
		  	'#default_value' 	=>'NotAgree',
		  	'#attributes' 		=> array('disabled' => TRUE),	
		
	  	);
		$form['factory_part_info']['factory_nature_details_irregularities_5'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'5. Although the Factory was found supplying and / or selling power*,beyond the factory premises - to other Factories / to the Grid, from the standby / captive power plant, and the Licence Fee applicable for the corresponding capacity of Power Generation Unit is Rs '.$licence_fees.' /-;  yet the application has been made for a Non-Power Generating Station. Accordingly the application is to be revised and an additional fee amounting to Rs'.$licence_fees.'/- needs to be paid.'
			
		);
	
		
		$form['factory_part_info']['factory_nature_details_irregularities_chk_5'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 				=> 'checkbox',
			  '#attributes' 		=> array('disabled' => TRUE),	
		);
		$form['factory_part_info']['factory_nature_details_irregularities_ddchk_5'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
		 	'#type' 			=> 'radios',
		  	'#options'         => $irregularities_name,
			'#default_value' 	=>'NotAgree',
			
	  	);
		$form['factory_part_info']['factory_nature_details_irregularities_jdchk_5'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td></tr>',
		 	'#type' 			=> 'radios',
		  	'#options'         	=> $irregularities_name,
		  	'#default_value' 	=>'NotAgree',
		  	'#attributes' 		=> array('disabled' => TRUE),	
		
	  	);
	}
	
	
		$form['factory_part_info']['factory_nature_details_irregularities_end'] 	= array(
		'#suffix' 	=> '</table><div>',
	);
	
	          
	
	
			
	
	
	
	
	
	
	$identity_flag = 'wbpcb_id';
	$irregularities_details_catagory =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factory_type_id,$service_id);

	$form['factory_part_info']['factory_catagory_irregularities_table'] 	= array(
	   
	
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>Irregularities for Scrutiny of Applications according to WBPCB of the Factory </th>
								<th>Irregularities by AD</th>
								<th>Action</th>
								<th>Irregularities by JD</th>
								
							</tr>
							'
					);
	
	if(!empty($irregularities_details_catagory)){
		foreach($irregularities_details_catagory as $row_irregularities_details_catagory){
		$remark_by_ad_chk=$row_irregularities_details_catagory->remark_by_ad;
				
				if($remark_by_ad_chk =='NotAgree'){
					$remark_by_ad = 0;
				}if($remark_by_ad_chk =='Agree'){
					$remark_by_ad = 1;
				}
			$form['factory_part_info']['factory_catagory_irregularities_'.$row_irregularities_details_catagory->id] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			 '#type' 			=> 'textarea',
			 '#rows'			=> 2,
			'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=> $row_irregularities_details_catagory->irregularities,
			
		);
	          
		$form['factory_part_info']['factory_adchk_'.$row_irregularities_details_catagory->id] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			  '#type' 				=> 'checkbox',
    		
			 '#default_value' 	=> $remark_by_ad,
			  '#attributes' 	=> array('disabled' => TRUE),
		  );
		  $form['factory_part_info']['factory_ddchk_'.$row_irregularities_details_catagory->id] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
		 	'#type' 			=> 'radios',
		 	'#options'         => $irregularities_name,
			 '#default_value' 	=> $row_irregularities_details_catagory->remark_by_dd,
			
		 	);
			$form['factory_part_info']['factory_jdchk_'.$row_irregularities_details_catagory->id] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td></tr>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=> $row_irregularities_details_catagory->remark_by_jd,
				'#attributes' 	=> array('disabled' => TRUE),
			
			);
		
		}
	}else{
		
			
	///$category_show_name = '<font color="#FF0000">'.$category_show.'</font>';
	$form['factory_part_info']['factory_catagory_irregularities_1'] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			 '#type' 			=> 'textarea',
			 '#rows'			=> 2,
			'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=>'1. Although the manufacturing process has been claimed to be in the '.$category_show.' category of the West Bengal Pollution Control Board, yet, the said activities are found to be listed in the Red / Orange / Green/White/Exampted* category and for which appropriate documents pertaining to clearance (Consent to Establish / Consent to Operate) from the said Authority / Board permitting the said activities in the said premises, shall have to be uploaded with the application.',
			
		);
	          
		$form['factory_part_info']['factory_catagory_irregularities_chk_1'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			  '#type' 				=> 'checkbox',
    		 '#attributes' 	=> array('disabled' => TRUE),
		  );
		  $form['factory_part_info']['factory_catagory_irregularities_ddchk_1'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
		 	'#type' 			=> 'radios',
		 	'#options'         	=> $irregularities_name,
			'#default_value' 	=>'NotAgree',
			
		);	
		$form['factory_part_info']['factory_catagory_irregularities_jdchk_1'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td></tr>',
			'#type' 			=> 'radios',
			'#options'         	=> $irregularities_name,
			'#default_value' 	=>'NotAgree',
			'#attributes' 		=> array('disabled' => TRUE),
		);	
				
			
		$form['factory_part_info']['factory_catagory_irregularities_2'] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			 '#type' 			=> 'textarea',
			 '#rows'			=> 2,
			'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=>'2. Appropriate documents / Consent to Establish / Consent to Operate Certificate* regarding clearance from West Bengal Pollution Control Board / appropriate Authority have not been uploaded with the application.',
			
		);
	          
		$form['factory_part_info']['factory_catagory_irregularities_chk_2'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 				=> 'checkbox',
    		 '#attributes' 	=> array('disabled' => TRUE),
		);
		$form['factory_part_info']['factory_catagory_irregularities_ddchk_2'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
		 	'#type' 			=> 'radios',
		 	'#options'         	=> $irregularities_name,
			'#default_value' 	=>'NotAgree',
			
		);	
		$form['factory_part_info']['factory_catagory_irregularities_jdchk_2'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td></tr>',
			'#type' 			=> 'radios',
			'#options'         	=> $irregularities_name,
			'#default_value' 	=>'NotAgree',
			'#attributes' 		=> array('disabled' => TRUE),
		);	
					
			
	}
	
			
			
	
		$form['factory_part_info']['factory_catagory_irregularities_end'] 	= array(
		'#suffix' 	=> '</table><div>',
	);
	
	
	//print_r($caf_upload_doc_prenission);die;
	
	
	
	
	
	
	
	
	$form['factory_part_info']['factory_addres_irregularities_table'] 	= array(
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>Irregularities for Scrutiny of Applications about Location of the Factory </th>
								<th>Irregularities by AD</th>
								<th>Action</th>
								<th>Irregularities by JD</th>
								
							</tr>
							'
					);
	
	
	
	
	$identity_flag = 'premises_address';
	$irregularities_details_location =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factory_type_id,$service_id);

	if(!empty($irregularities_details_location)){
		foreach($irregularities_details_location as $row_irregularities_details_location){
			$remark_by_ad_chk=$row_irregularities_details_location->remark_by_ad;
				
				if($remark_by_ad_chk =='NotAgree'){
					$remark_by_ad = 0;
				}if($remark_by_ad_chk =='Agree'){
					$remark_by_ad = 1;
				}
			$form['factory_part_info']['factory_addres_irregularities_'.$row_irregularities_details_location->id] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			  '#type' 			=> 'textarea',
			 '#rows'			=> 2,
			'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=> $row_irregularities_details_location->irregularities,
			
			);
	          
			$form['factory_part_info']['factory_adchk_'.$row_irregularities_details_location->id] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				 '#type' 			=> 'checkbox',
				'#default_value' 	=> $remark_by_ad,
				 '#attributes' 	=> array('disabled' => TRUE),
			);
			$form['factory_part_info']['factory_ddchk_'.$row_irregularities_details_location->id] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=> $row_irregularities_details_location->remark_by_dd,
				
			
  			);
			$form['factory_part_info']['factory_jdchk_'.$row_irregularities_details_location->id] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td></tr>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=> $row_irregularities_details_location->remark_by_jd,
				'#attributes' 	=> array('disabled' => TRUE),
				
			);

			
		
		}
	}else{
		$form['factory_part_info']['factory_addres_irregularities_1'] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			  '#type' 			=> 'textarea',
			 '#rows'			=> 2,
			'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=>'1. The address of the factory premises as mentioned in the Common Application Form does not match with that as per the supporting document – Ownership Deed / Lease Deed/ Rent Agreement / Trade Licence / Municipality Tax Bill / Clearance from WBPCB* – uploaded with the application'
			
		);
	          
		$form['factory_part_info']['factory_addres_chk_1'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 				=> 'checkbox',
    		 '#attributes' 	=> array('disabled' => TRUE),
		  );
		$form['factory_part_info']['factory_addres_ddchk_1'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
			'#type' 			=> 'radios',
			'#options'         	=> $irregularities_name,
			'#default_value' 	=>'NotAgree',
			
		);
		$form['factory_part_info']['factory_addres_jdchk_1'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td></tr>',
			'#type' 			=> 'radios',
			'#options'         	=> $irregularities_name,
			'#default_value' 	=>'NotAgree',
			'#attributes' 		=> array('disabled' => TRUE),
		);
			
			
		$form['factory_part_info']['factory_addres_irregularities_2'] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			  '#type' 			=> 'textarea',
			 '#rows'			=> 2,
		 	
			'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=>'2. Documents in support of valid, legal and bona-fide possession of the premises, in which the factory shall run, have not been uploaded with the application.'
			
		);
	          
		$form['factory_part_info']['factory_addres_chk_2'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 				=> 'checkbox',
			 '#attributes' 	=> array('disabled' => TRUE),
		  );	
		  $form['factory_part_info']['factory_addres_ddchk_2'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
			'#type' 			=> 'radios',
			'#options'         	=> $irregularities_name,
			'#default_value' 	=>'NotAgree',
			
		);
		$form['factory_part_info']['factory_addres_jdchk_2'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td></tr>',
			'#type' 			=> 'radios',
			'#options'         	=> $irregularities_name,
			'#default_value' 	=>'NotAgree',
			'#attributes' 		=> array('disabled' => TRUE),
		);
			
			
		$form['factory_part_info']['factory_addres_irregularities_3'] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			  '#type' 			=> 'textfield',
			 '#rows'			=> 2,
		 	
		'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=>'3. Details of the actual owner of the premises have not been provided.'
			
		);
	          
		$form['factory_part_info']['factory_addres_chk_3'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 			=> 'checkbox',
    		 '#attributes' 	=> array('disabled' => TRUE), 
			
		  );		
		  
		  $form['factory_part_info']['factory_addres_ddchk_3'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
			'#type' 			=> 'radios',
			'#options'         	=> $irregularities_name,
			'#default_value' 	=>'NotAgree',
			
		);
		$form['factory_part_info']['factory_addres_jdchk_3'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td></tr>',
			'#type' 			=> 'radios',
			'#options'         	=> $irregularities_name,
			'#default_value' 	=>'NotAgree',
			'#attributes' 		=> array('disabled' => TRUE),
		);


		$form['factory_part_info']['factory_addres_irregularities_4'] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			  '#type' 			=> 'textarea',
			 '#rows'			=> 2,
		 
			'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=>'4. Documents establishing valid, legal and bona-fide ownership of the premises, of the claimed actual owner of the premises with whom the Lease / Rent Agreement* has been entered upon, have not been uploaded with the application.'
			
		);
	          
		$form['factory_part_info']['factory_addres_chk_4'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 			=> 'checkbox',
    		  '#attributes' 	=> array('disabled' => TRUE),
		  );
		  
		  $form['factory_part_info']['factory_addres_ddchk_4'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
			'#type' 			=> 'radios',
			'#options'         	=> $irregularities_name,
			'#default_value' 	=>'NotAgree',
			
		);
		$form['factory_part_info']['factory_addres_jdchk_4'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td></tr>',
			'#type' 			=> 'radios',
			'#options'         	=> $irregularities_name,
			'#default_value' 	=>'NotAgree',
			'#attributes' 		=> array('disabled' => TRUE),
		);
		  
		  
		$form['factory_part_info']['factory_addres_irregularities_5'] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			  '#type' 			=> 'textarea',
			
			 '#rows'			=> 2,
		'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			'#default_value' 	=>'5. It appears that as the actual owner of the premises is a Government body, documents pertaining to permission from the said appropriate Authority (original Lessor) for sub-leasing / sub-letting* the premises by the actual Lessee to the present Lessee, have not been uploaded with the application.'
			
		);
	          
		$form['factory_part_info']['factory_addres_chk_5'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 				=> 'checkbox',
    		  '#attributes' 	=> array('disabled' => TRUE),
			
		  );	
		  $form['factory_part_info']['factory_addres_ddchk_5'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
			'#type' 			=> 'radios',
			'#options'         	=> $irregularities_name,
			'#default_value' 	=>'NotAgree',
			
		);
		$form['factory_part_info']['factory_addres_jdchk_5'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td></tr>',
			'#type' 			=> 'radios',
			'#options'         	=> $irregularities_name,
			'#default_value' 	=>'NotAgree',
			'#attributes' 		=> array('disabled' => TRUE),
		);	
	
	}
	
	$form['factory_part_info']['factory_addres_irregularities_end'] 	= array(
		'#suffix' 	=> '</table><div></div>',
	);

	$identity_flag = 'date_of_amenability_id';
$irregularities_details_amenability =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factory_type_id,$service_id);

		
	$form['factory_part_info']['factory_amenability_irregularities_table'] 	= array(
	   
	
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th >Irregularities for Scrutiny of Applications according to Date of Amenability  of the Factory </th>
								<th>Irregularities by AD</th>
								<th>Action</th>
								<th>Irregularities by JD</th>
								
							</tr>
							'
					);
if(!empty($irregularities_details_amenability)){
	foreach($irregularities_details_amenability as $row_irregularities_details_amenability){
		$remark_by_ad_chk=$row_irregularities_details_amenability->remark_by_ad;
				
				if($remark_by_ad_chk =='NotAgree'){
					$remark_by_ad = 0;
				}if($remark_by_ad_chk =='Agree'){
					$remark_by_ad = 1;
				}
		$form['factory_part_info']['factory_amenability_irregularities_'.$row_irregularities_details_amenability->id] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=> $row_irregularities_details_amenability->irregularities,
			
		);
	          
		$form['factory_part_info']['factory_adchk_'.$row_irregularities_details_amenability->id] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			  '#type' 				=> 'checkbox',
			  '#attributes' 	=> array('disabled' => TRUE),
			  '#default_value' 	=> $remark_by_ad,
    		 
			
		  );
			$form['factory_part_info']['factory_ddchk_'.$row_irregularities_details_amenability->id] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=> $row_irregularities_details_amenability->remark_by_dd,
				

			);
			$form['factory_part_info']['factory_jdchk_'.$row_irregularities_details_amenability->id] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td></tr>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=> $row_irregularities_details_amenability->remark_by_jd,
				'#attributes' 	=> array('disabled' => TRUE),
			);
		
			}
	}else{
			$form['factory_part_info']['factory_amenability_irregularities_1'] = array(
				'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				'#type' 			=> 'textarea',
				'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
				'#default_value' 	=>'1. Declaration by the Occupierregarding the date of Amenability of / Commencement of business in* the premises as a ‘Factory’, as under The Factories Act 1948, has not been uploaded / submitted with the application'

			);
	
		
	          
			$form['factory_part_info']['factory_amenability_irregularities_chk_1'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				 '#type' 				=> 'checkbox',
				
				 '#attributes' 	=> array('disabled' => TRUE),
				
			);
		  
			$form['factory_part_info']['factory_amenability_irregularities_ddchk_1'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				'#type' 			=> 'radios',
				'#options'         	=> $irregularities_name,
				'#default_value' 	=>'NotAgree',
				


			);
			$form['factory_part_info']['factory_amenability_irregularities_jdchk_1'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td></tr>',
				'#type' 			=> 'radios',
				'#options'         	=> $irregularities_name,
				'#default_value' 	=>'NotAgree',
				'#attributes' 		=> array('disabled' => TRUE),

			);
	
		
	
		$form['factory_part_info']['factory_amenability_irregularities_2'] = array(
					'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
					
					'#type' 			=> 'textarea',
					'#rows'				=> 2,
					'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
					'#default_value' 	=>'2. Copy of ESIC Registration Certificate or other appropriate documents in support of the declared date of Amenability of / Commencement of business - manufacturing process in* the premises as a ‘Factory’, as under The Factories Act 1948,as per the Application Form, has not been uploaded / submitted with the application '.$date_of_amenability_show.' yet it was ascertained during inspection of the said premises and / or during scrutiny of the documents uploaded with the application, that the premises constituted a Factory, as under the Act, from an earlier date'
				
			);
	
		
		$form['factory_part_info']['factory_amenability_irregularities_chk_2'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 				=> 'checkbox',
			  '#attributes' 	=> array('disabled' => TRUE),
		);
		$form['factory_part_info']['factory_amenability_irregularities_ddchk_2'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
			'#type' 			=> 'radios',
			'#options'         	=> $irregularities_name,
			'#default_value' 	=>'NotAgree',
			

		);
		$form['factory_part_info']['factory_amenability_irregularities_jdchk_2'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td></tr>',
			'#type' 			=> 'radios',
			'#options'         	=> $irregularities_name,
			'#default_value' 	=>'NotAgree',
			'#attributes' 		=> array('disabled' => TRUE),

		);	
			
		$form['factory_part_info']['factory_amenability_irregularities_3'] = array(
					'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
					'#suffix' 			=> '</div></td>',
					'#type' 			=> 'textarea',
					'#rows'				=> 2,
					'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
					'#default_value' 	=>'3. Although the declared date of Amenability of / Commencement of business in* the premises as a ‘Factory’, as under The Factories Act 1948,as per the Application Form is '.$date_of_amenability_show.' Hence Applicationsalong with Fees and supporting documents for the Years '.$amenability_year.' etc/ Period  '.$service_year.'are additionally required to be uploaded with the revised application.'
				
			);
	
	
	          
		$form['factory_part_info']['factory_amenability_irregularities_chk_3'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 				=> 'checkbox',
			 '#attributes' 	=> array('disabled' => TRUE), 
    		 
		  );
		  $form['factory_part_info']['factory_amenability_irregularities_ddchk_3'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
			'#type' 			=> 'radios',
			'#options'         	=> $irregularities_name,
			'#default_value' 	=>'NotAgree',
			


		);
		$form['factory_part_info']['factory_amenability_irregularities_jdchk_3'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td></tr>',
			'#type' 			=> 'radios',
			'#options'         	=> $irregularities_name,
			'#default_value' 	=>'NotAgree',
			'#attributes' 		=> array('disabled' => TRUE),

		);
					
			
		
	}
		
			
			
	
	$form['factory_part_info']['factory_amenability_irregularities_end'] 	= array(
		'#suffix' 	=> '</table><div>',
	);
	
	
	$identity_flag ='worker_details' ;
	$irregularities_details_worker_details =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factory_type_id,$service_id);
	
	$form['factory_part_info']['factory_worker_irregularities_table'] 	= array(
	   
	
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th >Irregularities for Scrutiny of Applications according to Nos. of Workers  of the Factory </th>
								<th>Irregularities by AD</th>
								<th>Action</th>
								<th>Irregularities by JD</th>
							</tr>
							'
					);

if(!empty($irregularities_details_worker_details)){
	foreach($irregularities_details_worker_details as $row_irregularities_details_worker_details){
		$remark_by_ad_chk=$row_irregularities_details_worker_details->remark_by_ad;
				
				if($remark_by_ad_chk =='NotAgree'){
					$remark_by_ad = 0;
				}if($remark_by_ad_chk =='Agree'){
					$remark_by_ad = 1;
				}
		
		$form['factory_part_info']['factory_worker_irregularities_'.$row_irregularities_details_worker_details->id] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=> $row_irregularities_details_worker_details->irregularities,
			
		);
	
		
	          
		$form['factory_part_info']['factory_adchk_'.$row_irregularities_details_worker_details->id] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 				=> 'checkbox',
			 '#default_value' 	=> $remark_by_ad,
    		 '#attributes' 	=> array('disabled' => TRUE), 
			
		  );
		$form['factory_part_info']['factory_ddchk_'.$row_irregularities_details_worker_details->id] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
			'#type' 			=> 'radios',
			'#options'         => $irregularities_name,
			'#default_value' 	=> $row_irregularities_details_worker_details->remark_by_dd,
			

		);
		$form['factory_part_info']['factory_jdchk_'.$row_irregularities_details_worker_details->id] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td></tr>',
			'#type' 			=> 'radios',
			'#options'         => $irregularities_name,
			'#default_value' 	=> $row_irregularities_details_worker_details->remark_by_jd,
			'#attributes' 	=> array('disabled' => TRUE),

		);
		
	}
	
		
				
}else{
	$form['factory_part_info']['factory_worker_irregularities_1'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'1. Although the declared maximum nos. of Workers employed and/or likely to be employed* in the factory on any day during the period for which Licence is required, has been stated as '.$worker_total.' , yet during inspection of the Factory, it was not found that the nos of workers employed was '.$worker_total.' for the License Period  '.$service_year.'respectively*, which fall under highercategory / categories*.Accordingly the application is to be revised and an additional fee for the said higher category / categories*,including Amendment Fee and Late Fee, amounting to Rs______ needs to be paid'
			
		);
	
		
	          
		$form['factory_part_info']['factory_worker_irregularities_chk_1'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 				=> 'checkbox',
			  '#attributes' 	=> array('disabled' => TRUE),
		);
		$form['factory_part_info']['factory_worker_irregularities_ddchk_1'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
			'#type' 			=> 'radios',
			'#options'         => $irregularities_name,
			'#default_value' 	=>'NotAgree',
		

		);
		$form['factory_part_info']['factory_worker_irregularities_jdchk_1'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td></tr>',
			'#type' 			=> 'radios',
			'#options'         => $irregularities_name,
			'#default_value' 	=>'NotAgree',
			'#attributes' 	=> array('disabled' => TRUE), 

		);
		
			

}
			
		
	          
					
	
		$form['factory_part_info']['factory_worker_irregularities_end'] 	= array(
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
	
$identity_flag ='power_details' ;
$irregularities_details_power_details =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factory_type_id,$service_id);	
$form['factory_part_info']['factory_power_details_irregularities_table'] 	= array(
	   
	
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th >Irregularities for Scrutiny of Applications according to Power details of the Factory </th>
								<th>Irregularities by AD</th>
								<th>Action</th>
								<th>Irregularities by JD</th>
							</tr>
							'
					);

if(!empty($irregularities_details_power_details)){
	foreach($irregularities_details_power_details as $row_irregularities_details_power_details){
		$remark_by_ad_chk=$row_irregularities_details_power_details->remark_by_ad;
				
				if($remark_by_ad_chk =='NotAgree'){
					$remark_by_ad = 0;
				}if($remark_by_ad_chk =='Agree'){
					$remark_by_ad = 1;
				}
		$form['factory_part_info']['factory_power_details_irregularities_'.$row_irregularities_details_power_details->id] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 '#default_value' 	=> $row_irregularities_details_power_details->irregularities,
			
		);
		$form['factory_part_info']['factory_adchk_'.$row_irregularities_details_power_details->id] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 
			'#type' 				=> 'checkbox',
			  '#default_value' 	=> $remark_by_ad_chk,
			   '#attributes' 	=> array('disabled' => TRUE),
		  );
		  
		  
		$form['factory_part_info']['factory_ddchk_'.$row_irregularities_details_power_details->id] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
			'#type' 			=> 'radios',
			'#options'         => $irregularities_name,
			'#default_value' 	=> $row_irregularities_details_power_details->remark_by_dd,
			


		);
		$form['factory_part_info']['factory_jdchk_'.$row_irregularities_details_power_details->id] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td></tr>',
			'#type' 			=> 'radios',
			'#options'         => $irregularities_name,
			'#default_value' 	=> $row_irregularities_details_power_details->remark_by_jd,
			'#attributes' 	=> array('disabled' => TRUE),


		);
		

	}
}else{
	$form['factory_part_info']['factory_power_details_irregularities_1'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'1.Although the declared capacity of Machinery installed and / or likely to be installed has been stated as '.$installed_power.'('.$power_unit.')'.'yet during inspection of the Factory, it was found that the total capacity of Machinery installed in the premises was '.$installed_power.'('.$power_unit.')'.'for the License Period  '.$service_year.'respectively* which falls / fall*under  highercategory / categories*. Accordingly the application is to be revised and an additional fee for the said higher category / categories*,includingAmendment Feeand Late Fee, amounting to '.$licence_fees.'/-needs to be paid.'
			
		);
		$form['factory_part_info']['factory_power_details_irregularities_chk_1'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 			=> 'radios',
			  '#type' 				=> 'checkbox',
 		'#attributes' 	=> array('disabled' => TRUE),
		  );

		$form['factory_part_info']['factory_power_details_irregularities_ddchk_1'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=>'NotAgree',
			
		);
		$form['factory_part_info']['factory_power_details_irregularities_jdchk_1'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td></tr>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=>'NotAgree',
				'#attributes' 	=> array('disabled' => TRUE),

		);
		  
		$form['factory_part_info']['factory_power_details_irregularities_2'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'2. The List of Installed Machinery along with the respective individual and the total capacity in Horsepower (Kilowatts for Generating Station) has not been uploaded with the application. '
			
		);
  
		$form['factory_part_info']['factory_power_details_irregularities_chk_2'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 				=> 'checkbox',
			  '#attributes' 	=> array('disabled' => TRUE),
		);
		
		$form['factory_part_info']['factory_power_details_irregularities_ddchk_2'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
			'#type' 			=> 'radios',
			'#options'         => $irregularities_name,
			'#default_value' 	=>'NotAgree',
			
		);
		$form['factory_part_info']['factory_power_details_irregularities_jdchk_2'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td></tr>',
			'#type' 			=> 'radios',
			'#options'         => $irregularities_name,
			'#default_value' 	=>'NotAgree',
			'#attributes' 	=> array('disabled' => TRUE),

		);
		  
		
	          
		
		$form['factory_part_info']['factory_power_details_irregularities_3'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textfield',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'3. A copy of the current Electric Bill is required to be uploaded with the application.'
			
		);
	
		
	          
		$form['factory_part_info']['factory_power_details_irregularities_chk_3'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 				=> 'checkbox',
			  '#attributes' 	=> array('disabled' => TRUE),
		  );	
		  
		  $form['factory_part_info']['factory_power_details_irregularities_ddchk_3'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
			'#type' 			=> 'radios',
			'#options'         => $irregularities_name,
			'#default_value' 	=>'NotAgree',
			
		);
		$form['factory_part_info']['factory_power_details_irregularities_jdchk_3'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td></tr>',
			'#type' 			=> 'radios',
			'#options'         => $irregularities_name,
			'#default_value' 	=>'NotAgree',
			'#attributes' 	=> array('disabled' => TRUE),

		);
					
			
		$form['factory_part_info']['factory_power_details_irregularities_4'] = array(
			 	'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
       		 	'#type' 			=> 'textarea',
			 	'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
			 	'#default_value' 	=>'4. The Contract Demand mentioned in the Electric Bill, uploaded with the application, is much higher than the capacity of the sum-total capacity of machineryinstalled in the factory, declared in the application form and in the List of Machinery uploaded with the application.'
			
		);
	
		
	          
		$form['factory_part_info']['factory_power_details_irregularities_chk_4'] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></td>',
			 '#type' 				=> 'checkbox',
			  '#attributes' 	=> array('disabled' => TRUE),
		  );
		  
		  $form['factory_part_info']['factory_power_details_irregularities_ddchk_4'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td>',
			'#type' 			=> 'radios',
			'#options'         => $irregularities_name,
			'#default_value' 	=>'NotAgree',
			
		);
		$form['factory_part_info']['factory_power_details_irregularities_jdchk_4'] = array(
			'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></td></tr>',
			'#type' 			=> 'radios',
			'#options'         => $irregularities_name,
			'#default_value' 	=>'NotAgree',
			'#attributes' 	=> array('disabled' => TRUE),

		);
}
		
$form['factory_part_info']['factory_power_details_irregularities_end'] 	= array(
		'#suffix' 	=> '</table><div>',
);

$identity_flag = 'occupier_details';
	$irregularities_details_occupier =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factory_type_id,$service_id);
	//print_r($irregularities_details_occupier);die;	
		$form['factory_part_info']['occupier_irregularities_table'] 	= array(
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12"><div id="occupier_chceking_id">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>Irregularities for Scrutiny of Applications about Occupier of the Factory </th>
								<th>Irregularities by AD</th>
								<th>Action</th>
								<th>Irregularities by JD</th>
							</tr>'
		);
	
		
		if(!empty($irregularities_details_occupier)){
			foreach($irregularities_details_occupier as $row_irregularities_details_occupier){
				$remark_by_ad_chk=$row_irregularities_details_occupier->remark_by_ad;
				
				if($remark_by_ad_chk =='NotAgree'){
					$remark_by_ad = 0;
				}if($remark_by_ad_chk =='Agree'){
					$remark_by_ad = 1;
				}
				$form['factory_part_info']['occupier_irregularities_'.$row_irregularities_details_occupier->id] = array(
				'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</td></div>',
				'#type' 			=> 'textarea',
				'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
				'#default_value' 	=> $row_irregularities_details_occupier->irregularities,
				);
				
				$form['factory_part_info']['factory_adchk_'.$row_irregularities_details_occupier->id] = array(
					'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
					'#suffix' 			=> '</div></td>',
					'#type' 				=> 'checkbox',
					 '#attributes' 	=> array('disabled' => TRUE),
					
					'#default_value' 	=>$remark_by_ad,	
				);
				$form['factory_part_info']['factory_ddchk_'.$row_irregularities_details_occupier->id] = array(
					'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
					'#suffix' 			=> '</div></td>',
					'#type' 			=> 'radios',
					'#options'         => $irregularities_name,
					
					'#default_value' 	=>$row_irregularities_details_occupier->remark_by_dd,	
				);
				$form['factory_part_info']['factory_jdchk_'.$row_irregularities_details_occupier->id] = array(
					'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
					'#suffix' 			=> '</div></td></tr>',
					'#type' 			=> 'radios',
					'#options'         => $irregularities_name,
					
					'#default_value' 	=>$row_irregularities_details_occupier->remark_by_jd,	
				);
			}
		
		}else{

			$form['factory_part_info']['occupier_irregularities_1'] = array(
				'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</td></div>',
				'#type' 			=> 'textfield',
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
				'#default_value' 	=>'1.The particulars of the Occupier mentioned in the Common Application Form, does not match with the supporting documents.',
			);
				
			$form['factory_part_info']['occupier_chk_1'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				'#type' 			=> 'radios',
				'#type' 				=> 'checkbox',
				 '#attributes' 	=> array('disabled' => TRUE),
			);
			$form['factory_part_info']['occupier_ddchk_1'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=>'NotAgree',
				
			);
			
			$form['factory_part_info']['occupier_jdchk_1'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td></tr>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=>'NotAgree',
				'#attributes' 		=> array('disabled' => TRUE),
				
			);
			
			$form['factory_part_info']['occupier_irregularities_2'] = array(
				'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</td></div>',
				'#type' 			=> 'textarea',
				'#rows'			=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
				'#default_value' 	=>'2.The name / particulars of the Directors / Partners / Proprietor mentioned in the Common Application Form, does not match with the supporting documents uploaded with the application',
				
			);
				
			$form['factory_part_info']['occupier_chk_2'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				'#type' 			=> 'radios',
				'#type' 				=> 'checkbox',
				 '#attributes' 	=> array('disabled' => TRUE),
			);
			$form['factory_part_info']['occupier_ddchk_2'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=>'NotAgree',
				
			);
			$form['factory_part_info']['occupier_jdchk_2'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td></tr>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=>'NotAgree',
				'#attributes' 		=> array('disabled' => TRUE),
				
			);
			$form['factory_part_info']['occupier_irregularities_3'] = array(
				'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</td></div>',
				'#type' 			=> 'textarea',
				'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
				'#default_value' 	=>'3.Documents in support of change of Partners / change of Partnership status have not been uploaded with the application',
				
			);
				
			$form['factory_part_info']['occupier_chk_3'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				'#type' 				=> 'checkbox',
				 '#attributes' 	=> array('disabled' => TRUE),
			);
			$form['factory_part_info']['occupier_ddchk_3'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=>'NotAgree',
			
			);
			$form['factory_part_info']['occupier_jdchk_3'] = array(
				'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 			=> '</div></td></tr>',
				'#type' 			=> 'radios',
				'#options'         => $irregularities_name,
				'#default_value' 	=>'NotAgree',
				'#attributes' 		=> array('disabled' => TRUE),
			
			);
		}
			
		$form['factory_part_info']['occupier_irregularities_end'] 	= array(
			'#suffix' 	=> '</table><div></div>',
		);
	
	}
	
	
	$identity_flag = 'payment_details';
			$irregularities_details_payment =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factory_type_id,$service_id);
			//print_r($irregularities_details_payment);die;	
				$form['factory_part_info']['payment_irregularities_table'] 	= array(
					  '#type'		=> 'markup',
					'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12"><div id="payment_chceking_id">
									<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
									<tr>							
								<th>Irregularities for Scrutiny of Applications about Payment Related </th>
								<th >Irregularities by AD</th>
								<th >Action</th>
								<th >Irregularities by JD</th>
							</tr>'
				);
			
			
				if(!empty($irregularities_details_payment)){
					foreach($irregularities_details_payment as $row_irregularities_details_payment){
						$remark_by_ad_chk=$row_irregularities_details_payment->remark_by_ad;
						if($remark_by_ad_chk =='NotAgree'){
							$remark_by_ad = 0;
						}if($remark_by_ad_chk =='Agree'){
							$remark_by_ad = 1;
						}
						$form['factory_part_info']['payment_irregularities_'.$row_irregularities_details_payment->id] = array(
						'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</td></div></div>',
						'#type' 			=> 'textarea',
						'#rows'			=> 2,
						'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
						'#default_value' 	=>$row_irregularities_details_payment->irregularities,
						);
						
						$form['factory_part_info']['factory_adchk_'.$row_irregularities_details_payment->id] = array(
							'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
							'#suffix' 			=> '</div></td>',
							
							'#type' 				=> 'checkbox',
							'#default_value' 	=>$remark_by_ad,
							 '#attributes' 	=> array('disabled' => TRUE),
							 
						);
						$form['factory_part_info']['factory_ddchk_'.$row_irregularities_details_payment->id] = array(
							'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
							'#suffix' 			=> '</div></td>',
							'#type' 			=> 'radios',
							'#options'         => $irregularities_name,
							'#default_value' 	=>$row_irregularities_details_name->remark_by_dd,
						);
						$form['factory_part_info']['factory_jdchk_'.$row_irregularities_details_payment->id] = array(
							'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
							'#suffix' 			=> '</div></td></tr>',
							'#type' 			=> 'radios',
							'#options'         => $irregularities_name,
							 '#attributes' 		=> array('disabled' => TRUE),
						 '#default_value' 	=>$row_irregularities_details_name->remark_by_jd,
						 '#attributes' 		=> array('disabled' => TRUE),
						);
					}
				
				}else{
		
					$form['factory_part_info']['payment_irregularities_1'] = array(
						'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</td></div>',
						'#type' 			=> 'textarea',
						'#rows'				=> 3,
						'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
						'#default_value' 	=>'1. The Licence Fees paid with the application do not match with the category (max. nos. of Workers likely to be employed on any day and total installed Machinery capacity) of Licence for which the application has been made.',
					);
						
					$form['factory_part_info']['payment_chk_1'] = array(
						'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</div></td>',
						
						'#type' 				=> 'checkbox',
						 '#attributes' 	=> array('disabled' => TRUE),
						);
					$form['factory_part_info']['payment_ddchk_1'] = array(
						'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</div></td>',
						'#type' 			=> 'radios',
						'#options'         => $irregularities_name,
						'#default_value' 	=>'NotAgree',
							
					);
					$form['factory_part_info']['payment_jdchk_1'] = array(
						'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</div></td></tr>',
						'#type' 			=> 'radios',
						'#options'         => $irregularities_name,
						'#default_value' 	=>'NotAgree',
						 '#attributes' 		=> array('disabled' => TRUE),	
					);
					
					$form['factory_part_info']['payment_irregularities_2'] = array(
						'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</td></div>',
						'#type' 			=> 'textarea',
						'#rows'				=> 5,
						'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
						'#default_value' 	=>'2. As the application for Registration & Grant of Licence was not submitted prior to the declared date of Amenability of / Commencement of business in* the premises as a ‘Factory’, as under The Factories Act 1948, additional Licence Fee @ 100% of the Scheduled Fees for the Year(s) '.$fees_details[0]->feesyear.', '.$fees_details[0]->schedule_fees.'-/ for the period from dd1/mm1/yyyy1 to dd1/mm1/yyyy1, for which the premises constituted a Factory as under the said Act (but for which Licence was neither obtained nor applied for), will be required to be paid.',
						
					);

						
					$form['factory_part_info']['payment_chk_2'] = array(
						'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</div></td>',
						
						'#type' 				=> 'checkbox',
						 '#attributes' 	=> array('disabled' => TRUE),
					);
					$form['factory_part_info']['payment_ddchk_2'] = array(
						'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</div></td>',
						'#type' 			=> 'radios',
						'#options'         => $irregularities_name,
						'#default_value' 	=>'NotAgree',
						
					);
					$form['factory_part_info']['payment_jdchk_2'] = array(
						'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</div></td></tr>',
						'#type' 			=> 'radios',
						'#options'         => $irregularities_name,
						'#default_value' 	=>'NotAgree',
						'#attributes' 		=> array('disabled' => TRUE),	
					);
					
					$form['factory_part_info']['payment_irregularities_3'] = array(
						'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</td></div>',
						'#type' 			=> 'textarea',
						'#rows'				=> 3,
						'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
						'#default_value' 	=>'3. As the application for Renewal of Licence was not submitted before the expiry of validity, but within ninety days after the said expiry – Late fee @ 50% is required to be paid.',
						
					);
					
						
					$form['factory_part_info']['payment_chk_3'] = array(
						'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</div></td>',
						
						'#type' 				=> 'checkbox',
						 '#attributes' 	=> array('disabled' => TRUE),
					);
					$form['factory_part_info']['payment_ddchk_3'] = array(
						'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</div></td>',
						'#type' 			=> 'radios',
						'#options'         => $irregularities_name,
						'#default_value' 	=>'NotAgree',
						
					);
					$form['factory_part_info']['payment_jdchk_3'] = array(
						'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</div></td></tr>',
						'#type' 			=> 'radios',
						'#options'         => $irregularities_name,
						'#default_value' 	=>'NotAgree',
						'#attributes' 		=> array('disabled' => TRUE),	
					);

					$form['factory_part_info']['payment_irregularities_4'] = array(
						'#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</td></div>',
						'#type' 			=> 'textarea',
						'#rows'				=> 3,
						'#attributes' 		=> array('class' => array( 'form-control'),'readonly'=>'readonly'),
						'#default_value' 	=>'4. As the application for Renewal of Licence was not submitted before the expiry of validity, but beyond ninety days after the said expiry – Late fee @ 100% is required to be paid.',
						
					);

					$form['factory_part_info']['payment_chk_4'] = array(
						'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</div></td>',
						
						'#type' 				=> 'checkbox',	
						 '#attributes' 	=> array('disabled' => TRUE),
					);
					$form['factory_part_info']['payment_ddchk_4'] = array(
						'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</div></td>',
						'#type' 			=> 'radios',
						'#options'         => $irregularities_name,
						'#default_value' 	=>'NotAgree',
						
					);
					$form['factory_part_info']['payment_jdchk_4'] = array(
						'#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
						'#suffix' 			=> '</div></td></tr>',
						'#type' 			=> 'radios',
						'#options'         => $irregularities_name,
						'#default_value' 	=>'NotAgree',
						'#attributes' 		=> array('disabled' => TRUE),	
					);
					
				}
					
				$form['factory_part_info']['payment_irregularities_end'] 	= array(
					'#suffix' 	=> '</table><div></div>',
				);
				
	
if($application_status == 'DC'){
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








function irregularities_dd_submit($form, &$form_state)
{
	//die;
	  global $user;
      $userid 			= 	$user->uid;
	  $remark_by_name											= get_name($userid);
	  $rid= get_role_id($userid);
	  $val    													= $form_state['values'];
	
	// print_r($val);die;
	   //-------------Irregularities-----------------------------------------------------
	  $factory_name_irregularities_1 							= $val['factory_name_irregularities_1'];
	  $factory_name_chk_1 										= $val['factory_name_ddchk_1'];
	  $factory_name_irregularities_2 							= $val['factory_name_irregularities_2'];
	  $factory_name_chk_2 										= $val['factory_name_ddchk_2'];
	  $factory_nature_details_irregularities_1 					= $val['factory_nature_details_irregularities_1'];
	  $factory_nature_details_irregularities_chk_1 				= $val['factory_nature_details_irregularities_ddchk_1'];
	  $factory_nature_details_irregularities_2 					= $val['factory_nature_details_irregularities_2'];
	  $factory_nature_details_irregularities_chk_2 				= $val['factory_nature_details_irregularities_ddchk_2'];
	  $factory_nature_details_irregularities_3 					= $val['factory_nature_details_irregularities_3'];
	  $factory_nature_details_irregularities_chk_3 				= $val['factory_nature_details_irregularities_ddchk_3'];
	  $factory_nature_details_irregularities_4 					= $val['factory_nature_details_irregularities_4'];
	  $factory_nature_details_irregularities_chk_4 				= $val['factory_nature_details_irregularities_ddchk_4'];
	  $factory_nature_details_irregularities_5 					= $val['factory_nature_details_irregularities_5'];
	  $factory_nature_details_irregularities_chk_5 				= $val['factory_nature_details_irregularities_ddchk_5'];
	  $factory_catagory_irregularities_1 						= $val['factory_catagory_irregularities_1'];
	  $factory_catagory_irregularities_chk_1 					= $val['factory_catagory_irregularities_ddchk_1'];
	  $factory_catagory_irregularities_2 						= $val['factory_catagory_irregularities_2'];
	  $factory_catagory_irregularities_chk_2 					= $val['factory_catagory_irregularities_ddchk_2'];
	  $factory_addres_irregularities_1 							= $val['factory_addres_irregularities_1'];
	  $factory_addres_chk_1 									= $val['factory_addres_ddchk_1'];
	  
	  $factory_addres_irregularities_2 							= $val['factory_addres_irregularities_2'];
	  $factory_addres_chk_2 									= $val['factory_addres_ddchk_2'];
	   
	  $factory_addres_irregularities_3 							= $val['factory_addres_irregularities_3'];
	  $factory_addres_chk_3 									= $val['factory_addres_ddchk_3'];
	  
	  $factory_addres_irregularities_4 							=$val['factory_addres_irregularities_4'];
	  $factory_addres_chk_4 									= $val['factory_addres_ddchk_4'];
	 
	  $factory_addres_irregularities_5 							= $val['factory_addres_irregularities_5'];
	  $factory_addres_chk_5 									= $val['factory_addres_chk_5'];
	   
	  $factory_amenability_irregularities_1 					= $val['factory_amenability_irregularities_1'];
	  $factory_amenability_irregularities_chk_1 				= $val['factory_amenability_irregularities_ddchk_1'];
	   
	  $factory_amenability_irregularities_2 					= $val['factory_amenability_irregularities_2'];
	  $factory_amenability_irregularities_chk_2 				= $val['factory_amenability_irregularities_ddchk_2'];
	 
	  $factory_amenability_irregularities_3 					= $val['factory_amenability_irregularities_3'];
	  $factory_amenability_irregularities_chk_3 				= $val['factory_amenability_irregularities_ddchk_3'];
	
	  $factory_worker_irregularities_1 							= $val['factory_worker_irregularities_1'];
	  $factory_worker_irregularities_chk_1 						= $val['factory_worker_irregularities_ddchk_1'];
	  $factory_power_details_irregularities_1 					= $val['factory_power_details_irregularities_1'];
	  $factory_power_details_irregularities_chk_1 				= $val['factory_power_details_irregularities_ddchk_1'];
	  $factory_power_details_irregularities_2 					= $val['factory_power_details_irregularities_2'];
	  $factory_power_details_irregularities_chk_2 				= $val['factory_power_details_irregularities_ddchk_2'];
	  $factory_power_details_irregularities_3 					= $val['factory_power_details_irregularities_3'];
	  $factory_power_details_irregularities_chk_3 				= $val['factory_power_details_irregularities_ddchk_3'];
	  $factory_power_details_irregularities_4 					= $val['factory_power_details_irregularities_4'];
	  $factory_power_details_irregularities_chk_4 				= $val['factory_power_details_irregularities_ddchk_4'];
	  
	  $occupier_irregularities_1 								= $val['occupier_irregularities_1'];
	  $occupier_chk_1 											= $val['occupier_ddchk_1'];
	  $occupier_irregularities_2 								= $val['occupier_irregularities_2'];
	  $occupier_chk_2 											= $val['occupier_ddchk_2'];
	  $occupier_irregularities_3 								= $val['occupier_irregularities_3'];
	  $occupier_chk_3 											= $val['occupier_ddchk_3'];
	  
	  $payment_irregularities_1 								= $val['payment_irregularities_1'];
	  $payment_chk_1 											= $val['payment_ddchk_1'];
	  $payment_irregularities_2 								= $val['payment_irregularities_2'];
	  $payment_chk_2 											= $val['payment_ddchk_2'];
	  $payment_irregularities_3 								= $val['payment_irregularities_3'];
	  $payment_chk_3 											= $val['payment_ddchk_3'];
	  $payment_irregularities_4									= $val['payment_irregularities_4'];
	  $payment_chk_4											= $val['payment_ddchk_4'];
	

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
	 

	 
	
	  $remark_details 	= get_remark_id($application_id,$reference_no,$userid,$rid);
	
		 $remark_id				= $remark_details['id'];
		


	  
	

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
								'remark_to_roleid' 	 => 11,
								'sending_time' 	  	 => date('Y-m-d h:i'),
								'app_reference_no' 	 => $reference_no,
								'remark_by_name'	 => $remark_by_name,
								'remark_type'	  	 => 'n',
								
								'remarks'			 => 'Notesheet processed is not completed',
								
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
	  										
											'remark_by_dd'		=> $val['factory_ddchk_'.$row_irregularities_details_name->id],
											'modification_by'	=> $userid,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'modification_date'	 => date('Y-m-d'),
											
											
	  									);
				$queryupdate_irregularities		 =	db_update('fa_checklist_observations');
				$queryupdate_irregularities		 ->	fields($irregularities_update);
				$queryupdate_irregularities		 ->	condition('id',$row_irregularities_details_name->id,'=');	
				$queryupdate_irregularities		 ->	execute();
		}
		
	}else{
		
		 $irregularities_1 = array(
	  										'irregularities'				=> $factory_name_irregularities_1,
											'remark_by_dd'					=> $factory_name_chk_1,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'factory_name',
											
	  									);
	 $irregularities_2 = array(
	  										'irregularities'				=> $factory_name_irregularities_2,
											'remark_by_dd'					=> $factory_name_chk_2,
											'dd_details'					=> $userid.','.$remark_by_name ,
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
	  										
											'remark_by_dd'			=> $val['factory_ddchk_'.$row_irregularities_details_nature_details->id],
											'modification_by'		=> $userid,
											'dd_details'			=> $userid.','.$remark_by_name ,
											'modification_date'		=> date('Y-m-d'),
											
											
	  									);
				$queryupdate_irregularities		 =	db_update('fa_checklist_observations');
				$queryupdate_irregularities		 ->	fields($irregularities_update);
				$queryupdate_irregularities		 ->	condition('id',$row_irregularities_details_nature_details->id,'=');	
				$queryupdate_irregularities		 ->	execute();
		}
		
	}else{
		$irregularities_3 = array(
	  										'irregularities'				=> $factory_nature_details_irregularities_1,
											'remark_by_dd'					=> $factory_nature_details_irregularities_chk_1,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'nature_details',
											
	  									);
	
	 $irregularities_4 = array(
	  										'irregularities'				=> $factory_nature_details_irregularities_2,
											'remark_by_dd'					=> $factory_nature_details_irregularities_chk_2,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'nature_details',
											
	  									);
										
	  $irregularities_5 = array(
	  										'irregularities'				=> $factory_nature_details_irregularities_3,
											'remark_by_dd'					=> $factory_nature_details_irregularities_chk_3,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'nature_details',
											
	  									);
										
	 $irregularities_6 = array(
	  										'irregularities'				=> $factory_nature_details_irregularities_4,
											'remark_by_dd'					=> $factory_nature_details_irregularities_chk_4,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'nature_details',
											
	  									);
										
	$irregularities_7= array(
	  										'irregularities'				=> $factory_nature_details_irregularities_5,
											'remark_by_dd'					=> $factory_nature_details_irregularities_chk_5,
											'dd_details'					=> $userid.','.$remark_by_name ,
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
	  										
											'remark_by_dd'			=> $val['factory_ddchk_'.$row_irregularities_details_catagory->id],
											'dd_details'					=> $userid.','.$remark_by_name ,
											'modification_by'		=> $userid,
											'modification_date'		=> date('Y-m-d'),
											
											
	  									);
				$queryupdate_irregularities		 =	db_update('fa_checklist_observations');
				$queryupdate_irregularities		 ->	fields($irregularities_update);
				$queryupdate_irregularities		 ->	condition('id',$row_irregularities_details_catagory->id,'=');	
				$queryupdate_irregularities		 ->	execute();
		}
		
	}else{ 
	$irregularities_8 = array(
	  										'irregularities'				=> $factory_catagory_irregularities_1,
											'remark_by_dd'					=> $factory_catagory_irregularities_chk_1,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'wbpcb_id',
											
	  									);
										
	  $irregularities_9 = array(
	  										'irregularities'				=> $factory_catagory_irregularities_2,
											'remark_by_dd'					=> $factory_catagory_irregularities_chk_2,
											'dd_details'					=> $userid.','.$remark_by_name ,
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
	  										
											'remark_by_dd'		=> $val['factory_ddchk_'.$row_irregularities_details_location->id],
											'modification_by'	=> $userid,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'modification_date'	 => date('Y-m-d'),
											
											
	  									);
				$queryupdate_irregularities		 =	db_update('fa_checklist_observations');
				$queryupdate_irregularities		 ->	fields($irregularities_update);
				$queryupdate_irregularities		 ->	condition('id',$row_irregularities_details_location->id,'=');	
				$queryupdate_irregularities		 ->	execute();
		}
		
	}else{
	$irregularities_10 = array(
	  										'irregularities'				=> $factory_addres_irregularities_1,
											'remark_by_dd'					=> $factory_addres_chk_1,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'premises_address',
											
	  									); 
										
	 $irregularities_11= array(
	  										'irregularities'				=> $factory_addres_irregularities_2,
											'remark_by_dd'					=> $factory_addres_chk_2,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'premises_address',
											
	  									); 

	 $irregularities_12 = array(
	  										'irregularities'				=> $factory_addres_irregularities_3,
											'remark_by_dd'					=> $factory_addres_chk_3,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'premises_address',
											
	  									); 
											
	 $irregularities_13 = array(
	  										'irregularities'				=> $factory_addres_irregularities_4,
											'remark_by_dd'					=> $factory_addres_chk_4,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'premises_address',
											
	  									);
										
	$irregularities_14 = array(
	  										'irregularities'				=> $factory_addres_irregularities_5,
											'remark_by_dd'					=> $factory_addres_chk_5,
											'dd_details'					=> $userid.','.$remark_by_name ,
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
	  										
											'remark_by_dd'		=> $val['factory_ddchk_'.$row_irregularities_details_amenability->id],
											'modification_by'	=> $userid,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'modification_date'	=> date('Y-m-d'),
											
											
	  									);
				$queryupdate_irregularities		 =	db_update('fa_checklist_observations');
				$queryupdate_irregularities		 ->	fields($irregularities_update);
				$queryupdate_irregularities		 ->	condition('id',$row_irregularities_details_amenability->id,'=');	
				$queryupdate_irregularities		 ->	execute();
		}
		
	}else{
		$irregularities_15 = array(
	  										'irregularities'				=> $factory_amenability_irregularities_1,
											'remark_by_dd'					=> $factory_amenability_irregularities_chk_1,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'date_of_amenability_id',
											
	  									); 
		 $irregularities_16 = array(
	  										'irregularities'				=> $factory_amenability_irregularities_2,
											'remark_by_dd'					=> $factory_amenability_irregularities_chk_2,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'date_of_amenability_id',
											
	  									); 
	 $irregularities_17 = array(
	  										'irregularities'				=> $factory_amenability_irregularities_3,
											'remark_by_dd'					=> $factory_amenability_irregularities_chk_3,
											'dd_details'					=> $userid.','.$remark_by_name ,
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
	  										
											'remark_by_dd'		=> $val['factory_ddchk_'.$row_irregularities_details_worker_details->id],
											'modification_by'	=> $userid,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'modification_date'	=> date('Y-m-d'),
											
											
	  									);
				$queryupdate_irregularities		 =	db_update('fa_checklist_observations');
				$queryupdate_irregularities		 ->	fields($irregularities_update);
				$queryupdate_irregularities		 ->	condition('id',$row_irregularities_details_worker_details->id,'=');	
				$queryupdate_irregularities		 ->	execute();
		}
		
	}else{
		 $irregularities_18 = array(
	  										'irregularities'				=> $factory_worker_irregularities_1,
											'remark_by_dd'					=> $factory_worker_irregularities_chk_1,
											'dd_details'					=> $userid.','.$remark_by_name ,
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
	  										
											'remark_by_dd'		=> $val['factory_ddchk_'.$row_irregularities_details_power_details->id],
											'dd_details'					=> $userid.','.$remark_by_name ,
											'modification_by'	=> $userid,
											'modification_date'	=> date('Y-m-d'),
											
											
	  									);
				$queryupdate_irregularities		 =	db_update('fa_checklist_observations');
				$queryupdate_irregularities		 ->	fields($irregularities_update);
				$queryupdate_irregularities		 ->	condition('id',$row_irregularities_details_power_details->id,'=');	
				$queryupdate_irregularities		 ->	execute();
		}
		
	}else{
		  $irregularities_19 = array(
	  										'irregularities'				=> $factory_power_details_irregularities_1,
											'remark_by_dd'					=> $factory_power_details_irregularities_chk_1,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'power_details',
											
	  									); 
	   $irregularities_20 = array(
	  										'irregularities'				=> $factory_power_details_irregularities_2,
											'remark_by_dd'					=> $factory_power_details_irregularities_chk_2,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'power_details',
											
	  									); 
	  $irregularities_21 = array(
	  										'irregularities'				=> $factory_power_details_irregularities_3,
											'remark_by_dd'					=> $factory_power_details_irregularities_chk_3,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'power_details',
											
	  									); 
	  $irregularities_22 = array(
	  										'irregularities'				=> $factory_power_details_irregularities_4,
											'remark_by_dd'					=> $factory_power_details_irregularities_chk_4,
											'dd_details'					=> $userid.','.$remark_by_name ,
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
	$identity_flag ='occupier_details' ;
	$irregularities_details_occupier_details =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factorytype_id,$service_id);
	if(!empty($irregularities_details_occupier_details)){
		foreach($irregularities_details_occupier_details as $row_irregularities_details_occupier_details){
			$irregularities_update = array(
	  										
											'remark_by_dd'		=> $val['factory_ddchk_'.$row_irregularities_details_occupier_details->id],
											'modification_by'	=> $userid,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'modification_date'	=> date('Y-m-d'),
											
											
	  									);
				$queryupdate_irregularities		 =	db_update('fa_checklist_observations');
				$queryupdate_irregularities		 ->	fields($irregularities_update);
				$queryupdate_irregularities		 ->	condition('id',$row_irregularities_details_occupier_details->id,'=');	
				$queryupdate_irregularities		 ->	execute();
		}
		
	}else{
		 $irregularities_23 = array(
									'irregularities'				=> $occupier_irregularities_1,
									'remark_by_dd'					=> $occupier_chk_1,
									'dd_details'					=> $userid.','.$remark_by_name ,
									'checklist_observations_ref_id' => $checklist_observations_ref_id,
									'modification_by'				=> $userid,
									'modification_date'				=> date('Y-m-d'),
									'identity_flag'					=> 'occupier_details',
								);

	  $irregularities_24 = array(
									'irregularities'				=> $occupier_irregularities_2,
									'remark_by_dd'					=> $occupier_chk_2,
									'dd_details'					=> $userid.','.$remark_by_name ,
									'checklist_observations_ref_id' => $checklist_observations_ref_id,
									'modification_by'				=> $userid,
									'modification_date'				=> date('Y-m-d'),
									'identity_flag'					=> 'occupier_details',
					);

	$irregularities_25 = array(
								'irregularities'				=> $occupier_irregularities_3,
								'remark_by_dd'					=> $occupier_chk_3,
								'dd_details'					=> $userid.','.$remark_by_name ,
								'checklist_observations_ref_id' => $checklist_observations_ref_id,
								'modification_by'				=> $userid,
								'modification_date'				=> date('Y-m-d'),
								'identity_flag'					=> 'occupier_details',
			);
	$irregularities_23_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_23) ->	execute();
  	$irregularities_24_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_24) ->	execute(); 
	$irregularities_25_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_25) ->	execute(); 
	}
	$identity_flag ='payment_details' ;
	$irregularities_details_payment_details =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factorytype_id,$service_id);
	if(!empty($irregularities_details_payment_details)){
		foreach($irregularities_details_payment_details as $row_irregularities_details_payment_details){
			$irregularities_update = array(
	  										
											'remark_by_dd'		=> $val['factory_ddchk_'.$row_irregularities_details_payment_details->id],
											'modification_by'	=> $userid,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'modification_date'	=> date('Y-m-d'),
											
											
	  									);
				$queryupdate_irregularities		 =	db_update('fa_checklist_observations');
				$queryupdate_irregularities		 ->	fields($irregularities_update);
				$queryupdate_irregularities		 ->	condition('id',$row_irregularities_details_payment_details->id,'=');	
				$queryupdate_irregularities		 ->	execute();
		}
	}else{
		
		 $irregularities_26 = array(
	  										'irregularities'				=> $payment_irregularities_1,
											'remark_by_dd'					=> $payment_chk_1,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'payment_details',
											
	  									);
	 $irregularities_27 = array(
	  										'irregularities'				=> $factory_name_irregularities_2,
											'remark_by_dd'					=> $factory_name_chk_2,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'payment_details',
											
	  									);
	$irregularities_28= array(
	  										'irregularities'				=> $factory_nature_details_irregularities_1,
											'remark_by_dd'					=> $factory_nature_details_irregularities_chk_1,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'payment_details',
											
	  									);
	
	
	$irregularities_26_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_26) ->	execute();
	$irregularities_27_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_27) ->	execute(); 
	$irregularities_28_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_28) ->	execute(); 

	}
 }else{

$irregularities_obsevation_ref = fun_fetch_observations_ref($application_id,$reference_no,$factorytype_id,$service_id); 

	if(!empty($irregularities_obsevation_ref)){
		foreach($irregularities_obsevation_ref as $row_irregularities_obsevation_ref){
		 $remark_table_id = $row_irregularities_obsevation_ref->remark_table_id;
		 $checklist_observations_ref_id = $row_irregularities_obsevation_ref->id;
		
	
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
								'remark_to_roleid' 	 => 11,
								'sending_time' 	  	 => date('Y-m-d h:i'),
								'app_reference_no' 	 => $reference_no,
								'remark_by_name'	 => $remark_by_name,
								'remark_type'	  	 => 'n',
								
								'remarks'			 => 'Notesheet processed is not completed',
								
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
	}
	 

	 else{
		$cafa_remarks = array(
								'app_id'   	  		 => $application_id,
								'remark_by_uid'  	 => $userid,
								'remark_by_roleid' 	 => $rid,
								'remark_to_roleid' 	 => 11,
								'sending_time' 	  	 => date('Y-m-d h:i'),
								'app_reference_no' 	 => $reference_no,
								'remark_by_name'	 => $remark_by_name,
								'remark_type'	  	 => 'n',
								
								'remarks'			 => 'Notesheet processed is not completed',
								
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
	}
					
	  
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
											'remark_by_dd'					=> $factory_name_chk_2,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'factory_name',
											
	  									);
	$irregularities_3 = array(
	  										'irregularities'				=> $factory_nature_details_irregularities_1,
											'remark_by_dd'					=> $factory_nature_details_irregularities_chk_1,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'nature_details',
											
	  									);
	
	 $irregularities_4 = array(
	  										'irregularities'				=> $factory_nature_details_irregularities_2,
											'remark_by_dd'					=> $factory_nature_details_irregularities_chk_2,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'nature_details',
											
	  									);
										
	  $irregularities_5 = array(
	  										'irregularities'				=> $factory_nature_details_irregularities_3,
											'remark_by_dd'					=> $factory_nature_details_irregularities_chk_3,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'nature_details',
											
	  									);
										
	 $irregularities_6 = array(
	  										'irregularities'				=> $factory_nature_details_irregularities_4,
											'remark_by_dd'					=> $factory_nature_details_irregularities_chk_4,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'nature_details',
											
	  									);
										
	$irregularities_7 = array(
	  										'irregularities'				=> $factory_nature_details_irregularities_5,
											'remark_by_dd'					=> $factory_nature_details_irregularities_chk_5,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'nature_details',
										  
	  									);
										
										
	 $irregularities_8 = array(
	  										'irregularities'				=> $factory_catagory_irregularities_1,
											'remark_by_dd'					=> $factory_catagory_irregularities_chk_1,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'wbpcb_id',
											
	  									);
										
	  $irregularities_9= array(
	  										'irregularities'				=> $factory_catagory_irregularities_2,
											'remark_by_dd'					=> $factory_catagory_irregularities_chk_2,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'wbpcb_id',
											
	  									);
										
		$irregularities_10 = array(
	  										'irregularities'				=> $factory_addres_irregularities_1,
											'remark_by_dd'					=> $factory_addres_chk_1,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'premises_address',
											
	  									); 
										
	 $irregularities_11= array(
	  										'irregularities'				=> $factory_addres_irregularities_2,
											'remark_by_dd'					=> $factory_addres_chk_2,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'premises_address',
											
	  									); 

	 $irregularities_12 = array(
	  										'irregularities'				=> $factory_addres_irregularities_3,
											'remark_by_dd'					=> $factory_addres_chk_3,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'premises_address',
											
	  									); 
											
	 $irregularities_13 = array(
	  										'irregularities'				=> $factory_addres_irregularities_4,
											'remark_by_dd'					=> $factory_addres_chk_4,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'premises_address',
											
	  									);
										
	$irregularities_14 = array(
	  										'irregularities'				=> $factory_addres_irregularities_5,
											'remark_by_dd'					=> $factory_addres_chk_5,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'premises_address',
											
	  									);  
	$irregularities_15 = array(
	  										'irregularities'				=> $factory_amenability_irregularities_1,
											'remark_by_dd'					=> $factory_amenability_irregularities_chk_1,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'date_of_amenability_id',
											
	  									); 
	  $irregularities_16 = array(
	  										'irregularities'				=> $factory_amenability_irregularities_2,
											'remark_by_dd'					=> $factory_amenability_irregularities_chk_2,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'date_of_amenability_id',
											
	  									); 
	 $irregularities_17 = array(
	  										'irregularities'				=> $factory_amenability_irregularities_3,
											'remark_by_dd'					=> $factory_amenability_irregularities_chk_3,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'date_of_amenability_id',
											
	  									); 
	
	 $irregularities_18 = array(
	  										'irregularities'				=> $factory_worker_irregularities_1,
											'remark_by_dd'					=> $factory_worker_irregularities_chk_1,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'worker_details',
											
	  									); 
	  $irregularities_19 = array(
	  										'irregularities'				=> $factory_power_details_irregularities_1,
											'remark_by_dd'					=> $factory_power_details_irregularities_chk_1,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'power_details',
											
	  									); 
	   $irregularities_20 = array(
	  										'irregularities'				=> $factory_power_details_irregularities_2,
											'remark_by_dd'					=> $factory_power_details_irregularities_chk_2,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'power_details',
											
	  									); 
	  $irregularities_21 = array(
	  										'irregularities'				=> $factory_power_details_irregularities_3,
											'remark_by_dd'					=> $factory_power_details_irregularities_chk_3,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'power_details',
											
	  									); 
	  $irregularities_22 = array(
	  										'irregularities'				=> $factory_power_details_irregularities_4,
											'remark_by_dd'					=> $factory_power_details_irregularities_chk_4,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'power_details',
											
	  									); 
	
		
		$irregularities_23 = array(
									'irregularities'				=> $occupier_irregularities_1,
									'remark_by_dd'					=> $occupier_chk_1,
									'dd_details'					=> $userid.','.$remark_by_name ,
									'checklist_observations_ref_id' => $checklist_observations_ref_id,
									'modification_by'				=> $userid,
									'modification_date'				=> date('Y-m-d'),
									'identity_flag'					=> 'occupier_details',
								);

	  $irregularities_24 = array(
									'irregularities'				=> $occupier_irregularities_2,
									'remark_by_dd'					=> $occupier_chk_2,
									'dd_details'					=> $userid.','.$remark_by_name ,
									'checklist_observations_ref_id' => $checklist_observations_ref_id,
									'modification_by'				=> $userid,
									'modification_date'				=> date('Y-m-d'),
									'identity_flag'					=> 'occupier_details',
					);

	$irregularities_25 = array(
								'irregularities'				=> $occupier_irregularities_3,
								'remark_by_dd'					=> $occupier_chk_3,
								'dd_details'					=> $userid.','.$remark_by_name ,
								'checklist_observations_ref_id' => $checklist_observations_ref_id,
								'modification_by'				=> $userid,
								'modification_date'				=> date('Y-m-d'),
								'identity_flag'					=> 'occupier_details',
			);
			
	$irregularities_26 = array(
	  										'irregularities'				=> $payment_irregularities_1,
											'remark_by_dd'					=> $payment_chk_1,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'payment_details',
											
	  									);
	 $irregularities_27 = array(
	  										'irregularities'				=> $factory_name_irregularities_2,
											'remark_by_dd'					=> $factory_name_chk_2,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'payment_details',
											
	  									);
	$irregularities_28= array(
	  										'irregularities'				=> $factory_nature_details_irregularities_1,
											'remark_by_dd'					=> $factory_nature_details_irregularities_chk_1,
											'dd_details'					=> $userid.','.$remark_by_name ,
											'checklist_observations_ref_id' => $checklist_observations_ref_id,
											'modification_by'				=> $userid,
											'modification_date'				=> date('Y-m-d'),
											'identity_flag'					=> 'payment_details',
											
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
	$irregularities_23_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_23) ->	execute();
  	$irregularities_24_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_24) ->	execute(); 
	$irregularities_25_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_25) ->	execute(); 
	$irregularities_26_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_26) ->	execute();
	$irregularities_27_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_27) ->	execute(); 
	$irregularities_28_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_28) ->	execute(); 
	
	
 }

}


?> 