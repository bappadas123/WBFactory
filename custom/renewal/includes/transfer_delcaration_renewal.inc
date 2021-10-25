<?php

    drupal_add_js(drupal_get_path('module', 'amendment') . '/js/formcheck.js');
    drupal_add_js(drupal_get_path('module', 'amendment') . '/js/myfunction.js');


function transfer_delcaration_renewal($form, &$form_state,$serviceid, $factorytypeid, $applicationid,$referenceno) {

	global $base_root, $base_path,$user;
    $userid = $user->uid;
  
    $form            	= array();
	$service_id      	= encryption_decryption_fun('decrypt', $serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt', $factorytypeid);
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
    $referance_number 	= encryption_decryption_fun('decrypt', $referenceno);
     
    $reg_applicant  	= get_details_applicant($userid);


    $lists = year_list($application_id,$factory_type_id,$referance_number,$userid);

    $previous_lists =  previous_year_list($application_id,$factory_type_id,$referance_number,$userid);
    
	//print_r($reg_applicant);die($date_of_expiry_reg);
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
        '#default_value' => $factorytypeid
    );
	$form['ref_number_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $referenceno
    );
	
    $factory_name          = '';
    $factory_previous_name = '';
    $nearest_landmark      = '';
    $factory_pan           = '';
	
    $factory_pincode       = '';
    $factory_state         = '';
    $factory_district      = '';
    $factory_subdivision   = '';
    $factory_areatype      = '';
    $factory_block         = '';
    $factory_panchayat     = '';
    $factory_policestation = '';
    $factory_postoffice    = '';
    $factory_addrline      = '';
    
    $office_pincode           = '';
    $office_state_off         = '';
    $office_district_off      = '';
    $office_subdivision_off   = '';
    $office_areatype_off      = '';
    $office_block_off         = '';
    $office_panchayat_off     = '';
    $office_policestation_off = '';
    $office_postoffice_off    = '';
    $office_addrline_off      = '';
    
	$comm_telephone     	  = '';
	$comm_mobile     	      = '';
	$comm_fax     	          = '';
	$comm_email     	      = '';
	$comm_alt_mobile		  = '';	
    
   
	//Communication Address //
	$office_pincode_comm		= '';
	$office_state_comm 			= '';
	$office_district_comm 		= '';
	$office_subdivision_comm 	= '';
	$office_areatype_comm 		= '';
	$office_block_comm 			= '';
	$office_panchayat_comm 		= ''; 
	$office_policestation_comm 	= ''; 
	$office_postoffice_comm 	= ''; 
	$office_addrline_comm 		= '';
	
    $owner_name                   = '';
	$owner_mname                  = '';
	$owner_lname                  = '';
    $owner_pincodepremises        = '';
    $owner_state_premises         = '';
    $owner_district_premises      = '';
    $owner_subdivision_premises   = '';
    $owner_areatype_premises      = '';
    $owner_block_premises         = '';
    $owner_panchayat_premises     = '';
    $owner_policestation_premises = '';
    $owner_postoffice_premises    = '';
    $owner_addrline_premises      = '';
	$reg_adress_same_factory_comm	= 1;
    //New field Added
    $trade_license_no 					= '';
    $date_of_amenability 				= '';
    $period_for_application  			= '';
    $plan_approve_identification_number	= '';
    $factory_plan_approval_number  		= '';
    $factory_reg_number 				= '';
    $factory_reg_identification_number  = '';
    $reference_number  					= '';
    $application_status  				= '';
    $is_backlog  						= '';
	$nearest_landmark 					= '';
	$gstin_no 							= '';
	$udyog_aadhaar 						= '';		
	$enargy_meter_no 					= '';		
	$cin_no 							= '';	
	$addrline_off_other					= '';	
	$country_code						= '';
	$country_owner						= '';
	$factory_country_address			= '';
	$mouza_name							= '';
	$jl_no								= '';
	$estate_type						= '';
	$factory_name_flag = 0;

    if (!empty($application_id)) {
        $get_fa_cafa           = get_fa_cafa($application_id);
        //print_r($get_fa_cafa);die();
        $factory_name          = $get_fa_cafa['factory_name'];
        $factory_previous_name = $get_fa_cafa['factory_previous_name'];
        $nearest_landmark      = $get_fa_cafa['nearest_landmark'];
		$factory_zone		   = $get_fa_cafa['factory_zone'];
		$factory_pan           = $get_fa_cafa['factory_pan'];
		$ownership_type=$ownership_type_caf		   = $get_fa_cafa['factory_owershiptype'];
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
       
        $comm_telephone     	  = $get_fa_cafa['comm_telephone'];
		$comm_mobile     	      = $get_fa_cafa['comm_mobile'];
		$comm_fax     	          = $get_fa_cafa['comm_fax'];
		$comm_email     	      = $get_fa_cafa['comm_email'];
		$comm_alt_mobile 		  = $get_fa_cafa['comm_alt_mobile'];
		
		$communication_adress_same_factory  = $get_fa_cafa['communication_adress_same_factory'];
		$reg_adress_same_factory_comm	  	= !empty($get_fa_cafa['reg_adress_same_factory_comm'])?$get_fa_cafa['reg_adress_same_factory_comm']:1;
		//Communication Address //
		$office_pincode_comm 		= $get_fa_cafa['pincodecomm'];
		$office_state_comm 			= $get_fa_cafa['state_comm'];
		$office_district_comm 		= $get_fa_cafa['district_comm'];
		$office_subdivision_comm 	= $get_fa_cafa['subdivision_comm'];
		$office_areatype_comm 		= $get_fa_cafa['areatype_comm'];
		$office_block_comm 			= $get_fa_cafa['block_comm'];
		$office_panchayat_comm 		= $get_fa_cafa['panchayat_comm']; 
		$office_policestation_comm 	= $get_fa_cafa['policestation_comm']; 
		$office_postoffice_comm 	= $get_fa_cafa['postoffice_comm']; 
		$office_addrline_comm 		= $get_fa_cafa['addrline_comm'];
		
       
	    $occupier_type 		      = $get_fa_cafa['occupier_type'];
        $occupier_nationality     = $get_fa_cafa['occupier_nationality'];
        $occupier_aadhaar         = $get_fa_cafa['occupier_aadhaar'];
        $occupier_passport        = $get_fa_cafa['occupier_passport'];
        $occupier_name            = $get_fa_cafa['occupier_name'];
        $occupier_mobile          = $get_fa_cafa['occupier_mobile'];
        $occupier_email_id        = $get_fa_cafa['occupier_email_id'];
        $occupier_age             = $get_fa_cafa['occupier_age'];
        $occupier_gurdian_name    = $get_fa_cafa['occupier_gurdian_name'];
        $occupier_fax_no          = $get_fa_cafa['occupier_fax_no'];
		$occupier_telephone       = $get_fa_cafa['occupier_telephone'];
        
        $occupier_pincodeoprmntadr        = $get_fa_cafa['pincodeoprmntadr'];
        $occupier_state_oprmntadr         = $get_fa_cafa['state_oprmntadr'];
        $occupier_district_oprmntadr      = $get_fa_cafa['district_oprmntadr'];
        $occupier_subdivision_oprmntadr   = $get_fa_cafa['subdivision_oprmntadr'];
        $occupier_areatype_oprmntadr      = $get_fa_cafa['areatype_oprmntadr'];
        $occupier_block_oprmntadr         = $get_fa_cafa['block_oprmntadr'];
        $occupier_panchayat_oprmntadr     = $get_fa_cafa['panchayat_oprmntadr'];
        $occupier_policestation_oprmntadr = $get_fa_cafa['policestation_oprmntadr'];
        $occupier_postoffice_oprmntadr    = $get_fa_cafa['postoffice_oprmntadr'];
        $occupier_addrline_oprmntadr      = $get_fa_cafa['addrline_oprmntadr'];
        
        $occupier_pincodeoprsntadr        = $get_fa_cafa['pincodeoprsntadr'];
        $occupier_state_oprsntadr         = $get_fa_cafa['state_oprsntadr'];
        $occupier_district_oprsntadr      = $get_fa_cafa['district_oprsntadr'];
        $occupier_subdivision_oprsntadr   = $get_fa_cafa['subdivision_oprsntadr'];
        $occupier_areatype_oprsntadr      = $get_fa_cafa['areatype_oprsntadr'];
        $occupier_block_oprsntadr         = $get_fa_cafa['block_oprsntadr'];
        $occupier_panchayat_oprsntadr     = $get_fa_cafa['panchayat_oprsntadr'];
        $occupier_policestation_oprsntadr = $get_fa_cafa['policestation_oprsntadr'];
        $occupier_postoffice_oprsntadr    = $get_fa_cafa['postoffice_oprsntadr'];
        $occupier_addrline_oprsntadr      = $get_fa_cafa['addrline_oprsntadr'];
		
       // $name						  = explode(" ",$get_fa_cafa['owner_name']);
        $owner_fname                  = $get_fa_cafa['owner_name'];
		$owner_mname                  = $get_fa_cafa['owner_mname'];
		$owner_lname                  = $get_fa_cafa['owner_lname'];
		
        $owner_pincodepremises        = $get_fa_cafa['pincodepremises'];
        $owner_state_premises         = $get_fa_cafa['state_premises'];
        $owner_district_premises      = $get_fa_cafa['district_premises'];
        $owner_subdivision_premises   = $get_fa_cafa['subdivision_premises'];
        $owner_areatype_premises      = $get_fa_cafa['areatype_premises'];
        $owner_block_premises         = $get_fa_cafa['block_premises'];
        $owner_panchayat_premises     = $get_fa_cafa['panchayat_premises'];
        $owner_policestation_premises = $get_fa_cafa['policestation_premises'];
        $owner_postoffice_premises    = $get_fa_cafa['postoffice_premises'];
        $owner_addrline_premises      = $get_fa_cafa['addrline_premises'];
		$owner_aadhaar_premises	  	  = $get_fa_cafa['aadhaar_premises'];
		$owner_passport_premises	  = $get_fa_cafa['passport_premises'];
		$passport_date_of_issue_premises		  = $get_fa_cafa['passport_date_of_issue_premises'];
		$date_of_expiry_premises	  = $get_fa_cafa['passport_date_of_expiry_premises'];
        
        $reg_adress_same_factory       = $get_fa_cafa['reg_adress_same_factory'];
      
        //$occupier_present_address_same = $get_fa_cafa['occupier_present_address_same'];

        //New Field Added

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
		$nearest_landmark    		      	= $get_fa_cafa['nearest_landmark'];
		$addrline_off_other					= $get_fa_cafa['addrline_off_other'];
		$country_code						= $get_fa_cafa['country_code'];
		$country_owner						= $get_fa_cafa['country_premises'];
		$country_premises_address			= $get_fa_cafa['addrline_premises'];
		$mouza_name							= $get_fa_cafa['mouza_name'];
		$jl_number							= $get_fa_cafa['jl_no'];			
    }
	
	if(empty($backlog_plan_approval_date)){
		$backlog_plan_approval_date = $link_date;
	}if(empty($backlog_plan_approval_no)){
		$backlog_plan_approval_no = $link_number;
	}
	$factoryzone = get_factory_zone();
	$default_zone 	= array(""=>"- Select Zone -");
	foreach($factoryzone as $val){
		$factzonefinal[$val->zone_id] = $val->zone_name;
		$factzonefinal1 = ($default_zone+$factzonefinal);
	}
	 $ownershiptype  = array(
        "pv" 			=> "Pvt Ltd Company",
        "ltd" 			=> "Ltd Company",
		"par_firm" 		=> "Partnership Firm",
		"pro_firm" 		=> "Proprietorship Firm",
		"llp" 	 		=> "Limited Liability Partnership",
		"cooperative" 	=> "Co-operative",
		"registered" 	=> "Registered Society under Society Register",
        "govt" 			=> "Govt.",
		"psu" 			=> "PSU",
		"localbody" 	=> "Local Body",
		"others" 		=> "Others",
 
    );
	
    $form['application_status_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => encryption_decryption_fun('encrypt', $application_status)
    );

	if ($get_fa_cafa['application_status']=='In') {
		
    $amendment_checking = get_amendment_checking($application_id,$service_id,$factory_type_id,$reference_number);
   //print_r($amendment_checking);die;
	$verify_details = !empty($amendment_checking['fieldname'])? $amendment_checking['fieldname'] : ''; 
	
	$str = "factory_name,ownership_type,factory_pan,gstin_no,udyog_aadhaar,enargy_no,cin_no,trade_no,plan_approval_no,plan_approval_date,zone_name,factory_headoffice,factory_communication,telephone_no,mobile_no,fax_no,email_no,owner_name,premises_address,wbpcb_id,wbpcb_reference_id,wbpcb_reference_date,intimation_id";
	$fields = removeFromString($str,$verify_details);
	
	$remark_field = explode(',',$fields);
	//print_r($remark_field);die;
    foreach ($remark_field as $fieldname){ //echo $fieldname;
        
			if($fieldname == 'factory_name'){$factory_name_ck = "readonly";}
			if($fieldname == 'ownership_type'){ $ownership_type_ck = "disabled";}
			if($fieldname == 'factory_pan'){ $factory_pan_ck = "readonly";}
			if($fieldname == 'gstin_no'){ $factory_gstin_ck = "readonly";}
			if($fieldname == 'udyog_aadhaar'){ $factory_udyog_ck = "readonly";}
			if($fieldname == 'enargy_no'){ $factory_enargy_ck = "readonly";}
			if($fieldname == 'cin_no'){ $factory_cin_ck = "readonly";}
			if($fieldname == 'trade_no'){ $factory_trade_ck = "readonly";}
			if($fieldname == 'plan_approval_no'){ $plan_approval_ck = "readonly";}
			if($fieldname == 'plan_approval_date'){ $plan_approval_date_ck = "readonly";}
			
            if($fieldname == 'zone_name'){ $zone_name_ck = "disabled";}
            if($fieldname == 'zone_name'){ $zone_name_ck2 = "disabled";}

	        if($fieldname == 'telephone_no'){ $telephone_no_ck = "readonly";}
			if($fieldname == 'mobile_no'){ $mobile_no_ck 	= "readonly";}
			if($fieldname == 'fax_no'){ $fax_no_ck 	= "readonly";}
			if($fieldname == 'email_no'){ $email_no_ck 	= "readonly";}
			
			if($fieldname == 'factory_headoffice'){ $headoffice_address_ck = "disabled";}
			if($fieldname == 'factory_headoffice'){ $headoffice_address_ck2 = "disabled";}
			
			if($fieldname == 'factory_communication'){ $factory_communication_ck = "readonly";}
			
			if($fieldname == 'wbpcb_id'){ $wbpcb_id_ck = "disabled";}
			if($fieldname == 'wbpcb_reference_id'){ $wbpcb_reference_id_ck = "readonly";}
			if($fieldname == 'wbpcb_reference_date'){ $wbpcb_reference_date_ck = "readonly";}
			if($fieldname == 'intimation_id'){ $intimation_id_ck = "readonly";}
			}
		
			
        if(in_array("factory_name", $remark_field)) { $factory_name_check_data = '<i class="fa fa-check text-green verified"></i>'; $factory_field_value= 'blank'; }
        else {  $factory_name_check_data = '<i class="fa fa-edit text-red verified"></i>'; $factory_field_value= "factory_name";}
        
        if(in_array("ownership_type", $remark_field)) { $factory_owner_check_data = '<i class="fa fa-check text-green verified"></i>'; $owner_field_value= 'blank'; }
        else {  $factory_owner_check_data = '<i class="fa fa-edit text-red verified"></i>'; $owner_field_value= "ownership_type";}
            
        if(in_array("factory_pan", $remark_field)) { $factory_pan_check_data = '<i class="fa fa-check text-green verified"></i>';  $pan_field_value= 'blank'; }
        else {  $factory_pan_check_data = '<i class="fa fa-edit text-red verified"></i>';$pan_field_value= "factory_pan"; }

        if(in_array("gstin_no", $remark_field)) { $gstin_no_check_data = '<i class="fa fa-check text-green verified"></i>';  $gstin_field_value= 'blank';}
        else {  $gstin_no_check_data = '<i class="fa fa-edit text-red verified"></i>'; $gstin_field_value= "gstin_no";}

        if(in_array("udyog_aadhaar", $remark_field)) { $udyog_aadhaar_check_data = '<i class="fa fa-check text-green verified"></i>';   $udyog_field_value= 'blank';}
        else {  $udyog_aadhaar_check_data = '<i class="fa fa-edit text-red verified"></i>'; $udyog_field_value= "udyog_aadhaar";}
        
        if(in_array("enargy_no", $remark_field)) { $enargy_no_check_data = '<i class="fa fa-check text-green verified"></i>';   $enargy_field_value= 'blank';}
        else {  $enargy_no_check_data = '<i class="fa fa-edit text-red verified"></i>'; $enargy_field_value= "enargy_no";}
        
        if(in_array("cin_no", $remark_field)) { $cin_no_check_data = '<i class="fa fa-check text-green verified"></i>';   $cin_field_value= 'blank';}
        else {  $cin_no_check_data = '<i class="fa fa-edit text-red verified"></i>'; $cin_field_value= "cin_no";}

        if(in_array("trade_no", $remark_field)) { $trade_license_no_check_data = '<i class="fa fa-check text-green verified"></i>';   $trade_field_value= 'blank';}
        else { $trade_license_no_check_data = '<i class="fa fa-edit text-red verified"></i>'; $trade_field_value= "trade_no";}
        
        if(in_array("zone_name", $remark_field)) { $factory_location_check_data = '<i class="fa fa-check text-green verified"></i>'; $location_field_value= 'blank'; }
        else {  $factory_location_check_data = '<i class="fa fa-edit text-red verified"></i>'; $location_field_value= 'zone_name';}
        
        if(in_array("factory_headoffice", $remark_field)) { $factory_headoffice_check_data = '<i class="fa fa-check text-green verified"></i>';  $register_field_value= 'blank'; }
        else {  $factory_headoffice_check_data = '<i class="fa fa-edit text-red verified"></i>'; $register_field_value= 'zone_name';}

        if(in_array("factory_communication", $remark_field)) { $factory_communication_check_data = '<i class="fa fa-check text-green verified"></i>';  $communication_field_value= 'blank';}
        else {  $factory_communication_check_data = '<i class="fa fa-edit text-red verified"></i>'; $communication_field_value= 'factory_communication';}
        
        if(in_array("owner_name", $remark_field)) { $owner_name_check_data = '<i class="fa fa-check text-green verified"></i>';  $owner_name_value= 'blank';}
        else {  $owner_name_check_data = '<i class="fa fa-edit text-red verified"></i>'; $owner_name_value= 'owner_name';}

        if(in_array("premises_address", $remark_field)) { $owner_address_check_data = '<i class="fa fa-check text-green verified"></i>'; $owner_address_field_value= 'blank'; }
        else {  $owner_address_check_data = '<i class="fa fa-edit text-red verified"></i>'; $owner_address_field_value= 'premises_address';}
        
        if(in_array("wbpcb_reference_id", $remark_field)) { $plant_installed_check_data = '<i class="fa fa-check text-green verified"></i>';  $plant_installed_field_value= 'blank';}
        else {  $plant_installed_check_data = '<i class="fa fa-edit text-red verified"></i>';  $plant_installed_field_value= 'wbpcb_reference_id';}
    
	}
    
    // echo $zone_name_ck; die;
	/********** Factory Information - Start **********/
	//echo $factory_name_flag;die;
    
    $form['header']            = array(
        '#markup' => t('<div class="content"><h3></h3>')
    );

    $previous_details =  get_previous_details_view($application_id,$reference_number,$factory_type_id,$service_id);
	//print_r($previous_details);die();
	foreach($previous_details as $pre_row){
		$is_previous		 	= $pre_row->conversation_ownership_type;
		$change_date 			= $pre_row->change_date;
		$ownership_type 		= $pre_row->ownership_type;
		$pervious_factory_name	= $pre_row->pervious_factory_name;
		$service_year			= $pre_row->service_year;
		$same_as_pre_details	= $pre_row->same_as_pre_details;
	}
    
   $type_change_factory =  !empty($ownership_type_caf)?$ownership_type_caf:$ownership_type_caf;

   //die($type_change_factory);

	if($type_change_factory == "pv"){

		$radios_options = array(
            's'             => "Select",
            'pv'            => "private to Private (Vise versa)",
            'ltd'           => "private to Public (Vise versa)",
            'par_firm'      => "private to Partnership Firm (Vise versa)",
            'pro_firm'      => "private to Proprietorship Firm (Vise versa)",

            'llp'           => "private to Limited Liability Partnership (Vise versa)",
            'cooperative'   => "private to Co-operative (Vise versa)",
            'registered'    => "private to Registered Society under Society Register (Vise versa)",
            'govt'          => "private to Govt (Vise versa)",
            'psu'           => "private to PSU (Vise versa)",
            'localbody'     => "private to Local Body (Vise versa)",
            "amal"          => "Amalgamation",
            "name"          => "Name change (ex:- XYZ ltd to YZX ltd)",
            "marge"         => "Marge",
        );
    }elseif($type_change_factory == "ltd"){

		$radios_options = array(
            's'             => "Select",
            'pv'            => "public to public (Vise versa)",
            'ltd'           => "public to Public (Vise versa)",
            'par_firm'      => "public to Partnership Firm (Vise versa)",
            'pro_firm'      => "public to Proprietorship Firm (Vise versa)",

            'llp'           => "public to Limited Liability Partnership (Vise versa)",
            'cooperative'   => "public to Co-operative (Vise versa)",
            'registered'    => "public to Registered Society under Society Register (Vise versa)",
            'govt'          => "public to Govt (Vise versa)",
            'psu'           => "public to PSU (Vise versa)",
            'localbody'     => "public to Local Body (Vise versa)",
            "amal"          => "Amalgamation",
            "name"          => "Name change (ex:- XYZ ltd to YZX ltd)",
            "marge"         => "Marge",
        );
    }
    elseif($type_change_factory== "pro_firm"){
		$radios_options = array(
           
            's'             => "Select",
            'pv'            => "Proprietorship to Private (Vise versa)",
            'ltd'           => "Proprietorship to Public (Vise versa)",
            'par_firm'      => "Proprietorship to Partnership Firm (Vise versa)",
            'pro_firm'      => "Proprietorship to Proprietorship Firm (Vise versa)",

            'llp'           => "Proprietorship to Limited Liability Partnership (Vise versa)",
            'cooperative'   => "Proprietorship to Co-operative (Vise versa)",
            'registered'    => "Proprietorship to Registered Society under Society Register (Vise versa)",
            'govt'          => "Proprietorship to Govt (Vise versa)",
            'psu'           => "Proprietorship to PSU (Vise versa)",
            'localbody'     => "Proprietorship to Local Body (Vise versa)",
            "amal"          => "Amalgamation",
            "name"          => "Name change (ex:- XYZ ltd to YZX ltd)",
            "marge"         => "Marge",
            "name"          => "Name change (ex:- XYZ ltd to YZX ltd)",
            "marge"         => "Marge",
        );
	}
	elseif($type_change_factory== "par_firm"){
        $radios_options = array(
           
            's'             => "Select",
            'pv'            => "Partnership Firm to Private (Vise versa)",
            'ltd'           => "Partnership Firm to Public (Vise versa)",
            'par_firm'      => "Partnership Firm to Partnership Firm (Vise versa)",
            'pro_firm'      => "Partnership Firm to Proprietorship Firm (Vise versa)",

            'llp'           => "Partnership Firm to Limited Liability Partnership (Vise versa)",
            'cooperative'   => "Partnership Firm to Co-operative (Vise versa)",
            'registered'    => "Partnership Firm to Registered Society under Society Register (Vise versa)",
            'govt'          => "Partnership Firm to Govt (Vise versa)",
            'psu'           => "Partnership Firm to PSU (Vise versa)",
            'localbody'     => "Partnership Firm to Local Body (Vise versa)",
            "amal"          => "Amalgamation",
            "name"          => "Name change (ex:- XYZ ltd to YZX ltd)",
            "marge"         => "Marge",
        );
		
    }elseif($type_change_factory== "llp"){
        $radios_options = array(
           
            's'             => "Select",
            'pv'            => "Limited Liability Partnership to Private (Vise versa)",
            'ltd'           => "Limited Liability Partnership to Public (Vise versa)",
            'par_firm'      => "Limited Liability Partnership to Partnership Firm (Vise versa)",
            'pro_firm'      => "Limited Liability Partnership to Proprietorship Firm (Vise versa)",

            'llp'           => "Limited Liability Partnership to Limited Liability Partnership (Vise versa)",
            'cooperative'   => "Limited Liability Partnership to Co-operative (Vise versa)",
            'registered'    => "Limited Liability Partnership to Registered Society under Society Register (Vise versa)",
            'govt'          => "Limited Liability Partnership to Govt (Vise versa)",
            'psu'           => "Limited Liability Partnership to PSU (Vise versa)",
            'localbody'     => "Limited Liability Partnership to Local Body (Vise versa)",
            "amal"          => "Amalgamation",
            "name"          => "Name change (ex:- XYZ ltd to YZX ltd)",
            "marge"         => "Marge",
        );

    }elseif($type_change_factory== "cooperative"){
        $radios_options = array(
           
            's'             => "Select",
            'pv'            => "Co-operative to Private (Vise versa)",
            'ltd'           => "Co-operative to Public (Vise versa)",
            'par_firm'      => "Co-operative to Partnership Firm (Vise versa)",
            'pro_firm'      => "Co-operative to Proprietorship Firm (Vise versa)",

            'llp'           => "Co-operative to Limited Liability Partnership (Vise versa)",
            'cooperative'   => "Co-operative to Co-operative (Vise versa)",
            'registered'    => "Co-operative to Registered Society under Society Register (Vise versa)",
            'govt'          => "Co-operative to Govt (Vise versa)",
            'psu'           => "Co-operative to PSU (Vise versa)",
            'localbody'     => "Co-operative to Local Body (Vise versa)",
            "amal"          => "Amalgamation",
            "name"          => "Name change (ex:- XYZ ltd to YZX ltd)",
            "marge"         => "Marge",
        );
    }elseif($type_change_factory== "registered"){
        $radios_options = array(
           
            's'             => "Select",
            'pv'            => "Registered Society to Private (Vise versa)",
            'ltd'           => "Registered Society to Public (Vise versa)",
            'par_firm'      => "Registered Society to Partnership Firm (Vise versa)",
            'pro_firm'      => "Registered Society to Proprietorship Firm (Vise versa)",

            'llp'           => "Registered Society to Limited Liability Partnership (Vise versa)",
            'cooperative'   => "Registered Society to Co-operative (Vise versa)",
            'registered'    => "Registered Society to Registered Society under Society Register (Vise versa)",
            'govt'          => "Registered Society to Govt (Vise versa)",
            'psu'           => "Registered Society to PSU (Vise versa)",
            'localbody'     => "Registered Society to Local Body (Vise versa)",
            "amal"          => "Amalgamation",
            "name"          => "Name change (ex:- XYZ ltd to YZX ltd)",
            "marge"         => "Marge",
        );
    }elseif($type_change_factory== "govt"){
        $radios_options = array(
           
            's'             => "Select",
            'pv'            => "Govt to Private (Vise versa)",
            'ltd'           => "Govt to Public (Vise versa)",
            'par_firm'      => "Govt to Partnership Firm (Vise versa)",
            'pro_firm'      => "Govt to Proprietorship Firm (Vise versa)",

            'llp'           => "Govt to Limited Liability Partnership (Vise versa)",
            'cooperative'   => "Govt to Co-operative (Vise versa)",
            'registered'    => "Govt to Registered Society under Society Register (Vise versa)",
            'govt'          => "Govt to Govt (Vise versa)",
            'psu'           => "Govt to PSU (Vise versa)",
            'localbody'     => "Govt to Local Body (Vise versa)",
            "amal"          => "Amalgamation",
            "name"          => "Name change (ex:- XYZ ltd to YZX ltd)",
            "marge"         => "Marge",
        );
    }elseif($type_change_factory== "psu"){
        $radios_options = array(
           
            's'             => "Select",
            'pv'            => "PSU to Private (Vise versa)",
            'ltd'           => "PSU to Public (Vise versa)",
            'par_firm'      => "PSU to Partnership Firm (Vise versa)",
            'pro_firm'      => "PSU to Proprietorship Firm (Vise versa)",

            'llp'           => "PSU to Limited Liability Partnership (Vise versa)",
            'cooperative'   => "PSU to Co-operative (Vise versa)",
            'registered'    => "PSU to Registered Society under Society Register (Vise versa)",
            'govt'          => "PSU to Govt (Vise versa)",
            'psu'           => "PSU to PSU (Vise versa)",
            'localbody'     => "PSU to Local Body (Vise versa)",
            "amal"          => "Amalgamation",
            "name"          => "Name change (ex:- XYZ ltd to YZX ltd)",
            "marge"         => "Marge",
        );
    }
    elseif($type_change_factory== "localbody"){
        $radios_options = array(
           
            's'             => "Select",
            'pv'            => "Local Body to Private (Vise versa)",
            'ltd'           => "Local Body to Public (Vise versa)",
            'par_firm'      => "Local Body to Partnership Firm (Vise versa)",
            'pro_firm'      => "Local Body to Proprietorship Firm (Vise versa)",

            'llp'           => "Local Body to Limited Liability Partnership (Vise versa)",
            'cooperative'   => "Local Body to Co-operative (Vise versa)",
            'registered'    => "Local Body to Registered Society under Society Register (Vise versa)",
            'govt'          => "Local Body to Govt (Vise versa)",
            'psu'           => "Local Body to PSU (Vise versa)",
            'localbody'     => "Local Body to Local Body (Vise versa)",
            "amal"          => "Amalgamation",
            "name"          => "Name change (ex:- XYZ ltd to YZX ltd)",
            "marge"         => "Marge",
        );
    }
    

	$owership_type_array  = array(
	
        "pv" 			=> "Pvt Ltd Company",
        "ltd" 			=> "Ltd Company",
		"par_firm" 		=> "Partnership Firm",
		"pro_firm" 		=> "Proprietorship Firm",
		"llp" 	 		=> "Limited Liability Partnership",
		"cooperative" 	=> "Co-operative",
		"registered" 	=> "Registered Society under Society Register",
        "govt" 			=> "Govt.",
		"psu" 			=> "PSU",
		"localbody" 	=> "Local Body",
        "others" 		=> "Others",
        "name"          => "Name change",
        "marge"         => "Marge",
	);
    

	$form['factory_part_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('Factory Information'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );

	$form['factory_part_info']['factory_checked_data'] = array(
        //'#type' 			=> 'textfield',
		'#type' 			=> 'hidden',
        '#value' 			=> $factory_field_value.','.$owner_field_value.','.$gstin_field_value.','.$udyog_field_value.','.$enargy_field_value.','.$cin_field_value.','.$trade_field_value.','.$pan_field_value,
		'#attributes' 		=> array('class' => array('')),
    );

	 $form['factory_part_info']['factory_name'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div>',
       	'#title' 			=> t($factory_name_check_data.'(i) Name of the factory'),
        '#type' 			=> 'textfield',
        '#required' 		=> TRUE,
        '#default_value' 	=> $factory_name,
        '#attributes' 		=> array('class' => array('form-control'),'readonly' => 'readonly' ),
        '#description'		=>'<font color="#FF0000">(According to license period name.)</font>'
    );
	 $form['factory_part_info']['pre_ownershiptype'] = array(
    '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
    '#suffix' 			=> '</div>',
    '#title' 			=> t($factory_name_check_data.'(ii). Ownership'/*.$is_previous.'---'.$ownership_type_app_reg*/),
    '#type' 			=> 'select',
    '#required' 		=> TRUE,
    '#options' 			=> $owership_type_array,
    '#default_value' 	=> !empty($ownership_type_caf)?$ownership_type_caf:$ownership_type_caf,
    '#attributes'		=> array('class' => array( ''),'disabled' => 'disabled'),
   
               
    );
	 $form['factory_part_info']['trade_license_no'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div></div>',
        '#title' 			=> t($factory_name_check_data.'(iii).Trade License No:'),
        '#type' 			=> 'textfield',
        '#default_value' 	=> !empty($trade_license_no)?$trade_license_no:'',
        '#attributes' 		=> array('class' => array( 'form-control'),'placeholder' => 'eg.00000000000' ),
        '#required' 		=> TRUE,
        '#description'		=>'<font color="#FF0000">minimun 10 lphanumeric no.</font>'
    );
    
    if(empty($factory_name_ck) ){

        $form['factory_part_info']['changing_details'] = array(
            '#prefix' 			=> '<div class="row"><div class="col-md-12 col-xs-12">',
            '#suffix' 			=> '</div></div>',
            '#type' 			=> 'markup',
        
            '#markup'		=>'<font color="#FF0000"><h3><b>Transfer Declaration</b></h3></font>'
        );
    }
        $form['factory_part_info']['row_st'] = array(
            '#prefix' 			=> '<div class="row">',
            '#suffix' 			=> '',
            '#type' 			=> 'markup',
        );
        if(empty($factory_name_ck) ){

        $form['factory_part_info']['application_period_section_a'] 	= array(
                '#prefix' 	 		=> '<div class="col-md-4 col-xs-4">',
                '#suffix' 	 		=> '</div>',
                '#type' 			=> 'select',
                '#title'			=>	t($factory_name_check_data.'(iv). Application Period'),
                '#attributes' 		=> 	array('class' => array('form-control')),
                '#required'			=> TRUE,
            
                '#id'				=> 'dates',
                '#default_value' 	=> $service_year,
                '#options' 	 		=> $previous_lists//($application_id,$service_id,$factory_type_id,$reference_number), 
        );
        

    
    $form['factory_part_info']['factory_ownershiptype'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t($factory_name_check_data.'(v). select transfer ownership'/*.$is_previous.'---'.$ownership_type_app_reg*/),
        '#type' 			=> 'select',
        '#required' 		=> TRUE,
        '#options'   		=> $radios_options,	
        '#default_value' 	=> !empty($is_previous)?$is_previous:$ownership_type,
        '#attributes'		=> array('class' => array( ''),$factory_name_ck => $factory_name_ck),
        '#ajax'				=> array(
                            'event' 	=> 'change',
                            'effect' 	=> 'fade',			
                            'callback' => 'get_ajax_owner_type',
                            'progress'	=>	array(
                            'type'		=> 'throbber',
                            'message'	=> t('loading'),
                            )
                        )
        );

    }
   
    $is_previous_value  = isset($form_state['values']['factory_ownershiptype']) ? $form_state['values']['factory_ownershiptype'] : $is_previous;

    $form['factory_part_info']['cin_no'] = array(
		'#prefix'	=> '<div id="cin_no_id">',
		'#suffix' 	=> '</div>',
    );

    if($ownership_type == 'pv' || $ownership_type == 'ltd'){
		$form['factory_part_info']['cin_no'] = array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-4" id="cin_no_id"><label class="input label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t($cin_no_check_data.'(viii-a). CIN No:'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			'#default_value' 	=> !empty($cin_no)?$cin_no:'',
			'#attributes' 		=> array('class' => array( ''),$factory_cin_ck => $factory_cin_ck ),
			'#description' 		=> '<a href="http://www.mca.gov.in/mcafoportal/findCIN.do" target="_blank" title="Ministry Of Corporate Affairs, About MCA, Ministry">**Find CIN No.</a>',
        );
    
	 }else{
		$form['factory_part_info']['cin_no'] = array(
			'#prefix'	=> '<div id="cin_no_id">',
		    '#suffix' 	=> '</div></div>',
		);
    }

  

    
            $form['factory_part_info']['start_vid'] = array(
                '#prefix'	=> ' <div class="row">',
                '#suffix' 	=> '',
                '#type'		=> 'markup',
            );
        
            $form['factory_part_info']['change_date'] = array(
                '#prefix' 		=> '<div id="change_date_div">',
                '#suffix' 		=> '</div>',   
            );
            $form['factory_part_info']['previous_name'] = array(
                '#prefix' 		=> '<div id="previous_name_div">',
                '#suffix' 		=> '</div>',
            );
            $form['factory_part_info']['previous_ownership'] = array(
                '#prefix' 		=> '<div id="previous_ownership_div">',
                '#suffix' 		=> '</div>',   
            );
            $form['factory_part_info']['conversation_name'] = array(
                '#prefix' 		=> '<div id="conversation_name_div">',
                '#suffix' 		=> '</div>',
            );
            $form['factory_part_info']['conversation_ownership'] = array(
                '#prefix' 			=> '<div id="conversation_ownership_div">',
                '#suffix' 			=> '</div>',
            );
            $form['factory_part_info']['addr_same'] = array(
                '#prefix' 			=> '<div id="addr_same_div">',
                '#suffix' 			=> '</div>',
            );
            $form['factory_part_info']['add_details'] = array(
                '#prefix' 			=> '<div id="add_details_div">',
                '#suffix' 			=> '</div>',
            );

            if($is_previous_value == 'pv' || $is_previous_value == 'ltd' || $is_previous_value == 'par_firm' || $is_previous_value == 'pro_firm' || $is_previous_value == 'llp' || $is_previous_value == 'govt' || $is_previous_value == 'co-opetative' || $is_previous_value == 'psu' || $is_previous_value == 'localbody' ||$is_previous_value == 'amal'  ||  $is_previous_value == 'name' ||  $is_previous_value == 'marge'){
                if($is_previous_value == 'pv'){
                    $ownershiptype  = array(
                    "pv" 			=> "Pvt Ltd Company",
                    "ltd" 			=> "Ltd Company",
                );
                }if($is_previous_value == 'ltd'){
                    $ownershiptype  = array(
                    "ltd" 			=> "Ltd Company",
                    "pv" 			=> "Pvt Ltd Company",
                );
                }
                if($is_previous_value == 'par_firm'){
                    $ownershiptype  = array(
                    "par_firm" 		=> "Partnership Firm",
                    "pro_firm" 		=> "Proprietorship Firm",
                );
                }if($is_previous_value == 'pv_par'){
                    $ownershiptype  = array(
                    "par_firm" 		=> "Partnership Firm",
                    "pv" 			=> "Pvt Ltd Company",
                );
                }if($is_previous_value == 'par_ltd'){
                    $ownershiptype  = array(
                    "par_firm" 		=> "Partnership Firm",
                    "ltd" 			=> "Ltd Company",
                );
                }if($is_previous_value == 'pv_pro'){
                    $ownershiptype  = array(
                    "pro_firm" 		=> "Proprietorship Firm",
                    "pv" 			=> "Pvt Ltd Company",
                );
                }if($is_previous_value == 'ltd_pro'){
                    $ownershiptype  = array(
                    "pro_firm" 		=> "Proprietorship Firm",
                    "ltd" 			=> "Ltd Company",
                );
            }
                

        $form['factory_part_info']['change_date'] 	= array(
                '#prefix' 	 	=> '<div id="change_date_div" class="col-md-4 col-sm-4 col-xs-4">',
                '#suffix' 	 	=> '</div>',
                '#type' 			=> 'textfield',
                '#required' 		=> TRUE, 
                '#default_value' => date('d-m-Y',strtotime($change_date)),
                '#title'			=>	t($factory_name_check_data.'(a). Change Date'),
                '#attributes' 	=> 	array('class' => array('calender_ajax'),'placeholder' => ''),
                    
                );
        
            $form['factory_part_info']['previous_name'] 	= array(
                '#prefix' 	 	=> '<div id="previous_name_div" class="col-lg-4 col-md-4 col-sm-4 col-xs-4">',
                '#suffix' 	 	=> '</div>',
                '#type' 	 		=> 'textfield',
                '#title'			=>	t($factory_name_check_data.'(b). Previous Name'),
                '#attributes' 	=> 	array('class' => array('form-control')),
                '#required'		=> TRUE,
                '#default_value' => !empty($pervious_factory_name)?$pervious_factory_name:$factory_name,
                        
                );
            $form['factory_part_info']['previous_ownership'] 	= array(
                '#prefix' 	 	=> '<div id="previous_ownership_div" class="col-lg-4 col-md-4 col-sm-4 col-xs-4">',
                '#suffix' 	 	=> '</div>',
                '#type' 	 		=> 'select',
                '#title'			=>	t($factory_name_check_data.'(c).Ownership type of previous name'),
                '#required'		=> TRUE,
                '#options' 			=> $owership_type_array,
                '#default_value' 	=> !empty($ownership_type_caf)?$ownership_type_caf:$ownership_type_caf,
                '#attributes'		=> array('class' => array( ''),'disabled' => 'disabled'),
                        
                );
        $form['factory_part_info']['conversation_name'] 	= array(
                '#prefix' 	 	=> '<div id="conversation_name_div" class="col-lg-4 col-md-4 col-sm-4 col-xs-4">',
                '#suffix' 	 	=> '</div>',
                '#type' 	 		=> 'textfield',
                '#title'			=>	t($factory_name_check_data.'(d). New Name'),
                '#attributes' 	=> 	array('class' => array('form-control')),
                '#required'		=> TRUE,
                '#default_value' => $pervious_factory_name,
                        
                );
        $form['factory_part_info']['conversation_ownership'] 	= array(
                '#prefix' 	 	    => '<div id="conversation_ownership_div" class="col-lg-4 col-md-4 col-sm-4 col-xs-4">',
                '#suffix' 	 	    => '</div>',
                '#type' 	 		=> 'select',
                '#title'			=>	t($factory_name_check_data.'(e).Ownership type after conversion'),
                '#attributes' 	    => 	array('class' => array('form-control'),'disabled' => 'disabled'),
                '#required'		    => TRUE,
                '#default_value' 	=> !empty($is_previous_value)?$is_previous_value:$ownership_type,
                '#options' 	 	    => $owership_type_array, 
            );
            $form['factory_part_info']['add_details'] 	= array(
                        '#type' 			=> 'submit',
                        '#submit'			=> array(),
                        '#ajax' 			=> array('callback'	=> 'add_pre_details',),
                        '#value' 			=> t('Add details'),
                        '#attributes' 		=> array('class' => array('btn btn-warning pull-right')),
                        '#prefix' 	 		=> '<div id="add_details_div" class="col-lg-12 col-md-12 col-sm-12 col-xs-12">',
                        '#suffix' 	 		=> '</div>',
                    ); 
        }
            elseif($is_previous_value == 'No'){
                
                $form['factory_part_info']['application_period_section_a'] = array(
                '#prefix' 			=> '<div id="year_deatils_div">',
                '#suffix' 			=> '</div>',
                );
                $form['factory_part_info']['change_date'] = array(
                '#prefix' 			=> '<div id="change_date_div">',
                '#suffix' 			=> '</div>',
                );
            
                $form['factory_part_info']['previous_name'] = array(
                '#prefix' 			=> '<div id="previous_name_div">',
                '#suffix' 			=> '</div>',
                );
                $form['factory_part_info']['addr_same'] = array(
                '#prefix' 			=> '<div id="addr_same_div">',
                '#suffix' 			=> '</div>',
                );
                $form['factory_part_info']['add_details'] = array(
                '#prefix' 			=> '<div id="add_details_div">',
                '#suffix' 			=> '</div>',
                );
            }

            
            $form['factory_part_info']['end_row'] 	= array(
                '#prefix' 			=> '',
                '#suffix' 			=> '</div>',
                '#type'				=> 'markup',
                );

            $form['factory_part_info']['view_previous_details'] 	= array(
                '#prefix' 			=> '<div class ="row"><div id ="view_previous_details_id">',
                '#suffix' 			=> '</div></div>',
                '#type'				=> 'markup',
                '#markup'			=> view_previous_details($application_id,$reference_number,$factory_type_id,$service_id)
            );
   





















  
    /////////////////ADD HERE///////////////////////////////////
    
        /********** Location of the factory - Start **********/
        $form['factory_part_a'] = array(
            '#type'			=> 'fieldset',
            '#title' 		=> t('B. Location of the factory'),
            '#collapsible' 	=> TRUE, // Added
            '#collapsed' 	=> FALSE // Added
        );
        

        if(empty($zone_name_ck) || empty($telephone_no_ck)|| empty($mobile_no_ck)|| empty($fax_no_ck)|| empty($email_no_ck)){

        $form['factory_part_a']['application_period_section_b'] = array(
                '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4"><label class="input label-block">',
                '#suffix' 			=> '</label></div></div>',
                '#title' 			=> t('(i). Application Period'),
                '#type' 			=> 'select',
                '#options' 			=> $lists,
                '#required' 		=> TRUE,
                '#attributes' 		=> array('class' => array( '')),
        );	
    }

        $form['factory_part_a']['firstRowStart'] = array(
            '#prefix' 		=> '<div class="row">',
        );
        $form['factory_part_a']['pincode']       = array(
            '#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' 			=> '</label></div>',
            '#attributes' 		=> array(
            'class' 			=> array(),
            'placeholder' 	=> 'Pincode',
            $zone_name_ck2 => $zone_name_ck2
            ),
            '#autocomplete_path' => 'pinautocomplete',
            '#id' 				 => 'pincode_autocomplete',
            '#maxlength' 		 => 6,
            '#title' 			 => t($factory_location_check_data.'(i) Pincode'),
            '#default_value' 	 => $factory_pincode,
            '#required' => TRUE,
            '#type' => 'textfield',
            '#ajax' => array(
                //'event'         => 'change',
                'effect' => 'fade',
                'callback' => 'get_ajax_load',
                'progress' => array(
                    'type' => 'throbber',
                    'message' => t('loading')
                )
            )
        );
        $value_pincode  = isset($form_state['values']['pincode']) ? $form_state['values']['pincode'] : $factory_pincode;
        if (!empty($value_pincode)) {
            
            $query = db_select('fa_all_india_pin_code', 'p')->fields('p', array(
                'districtname',
                'statename',
                'pincode',
                'district_code',
                'state_code',
                'po_name'
            ))->condition('p.pincode', trim($value_pincode), '=');
            
            $result = $query->execute();
            if ($result->rowcount() > 0) {
                $final       = $result->fetchAssoc();
                $pincode_v   = $value_pincode;
                $state_v     = $final['state_code'];
                $district_v  = $final['district_code'];
                $post_office = $final['po_name'];
            }
        }
        
        if (!empty($state_v)) {
            $form['factory_part_a']['state'] = array(
                '#title' => $factory_location_check_data.'(ii) State',
                '#type' => 'select',
                '#id' => 'state_name',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'State',
                    $zone_name_ck2 => $zone_name_ck2
                ),
                '#disabled' => TRUE,
                '#options' => get_all_state($state_v),
                '#value' => !empty($state_v) ? $state_v : $factory_state,
                '#required' => TRUE,
                '#prefix' => '<div id="ld_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',

                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_a']['state'] = array(
                '#title' => '(ii) State',
                '#type' => 'select',
                '#id' => 'state_name',
                '#disabled' => TRUE,
                '#attributes' => array(
                    'class' => array(''),
                    'placeholder' => 'State',
                    'readonly' => 'readonly'
                ),
                '#required' => TRUE,
                '#options' => array(
                    '' => t('Select State')
                ),
                '#prefix' => '<div id="ld_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        }
        $value_state = isset($form_state['values']['state']) ? $form_state['values']['state'] : $factory_state;
        
        if (!empty($state_v)) {
            $form['factory_part_a']['district'] = array(
                '#title' => $factory_location_check_data.'(iii) District',
                '#type' => 'select',
                '#id' => 'district_name',
                '#disabled' => TRUE,
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'District',
                    $zone_name_ck2 => $zone_name_ck2
                ),
                '#options' => get_district_by_id($state_v),
                '#value' => !empty($district_v) ? $district_v : $factory_district,
                '#required' => TRUE,
                '#prefix' => '<div id="ld_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_a']['district'] = array(
                '#title' => '(iii) District',
                '#type' => 'select',
                '#id' => 'district_name',
                '#disabled' => TRUE,
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'District'
                ),
                '#required' => TRUE,
                '#options' => array(
                    '' => t('Select District')
                ),
                '#prefix' => '<div id="ld_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        }
        $value_district = isset($form_state['values']['district']) ? $form_state['values']['district'] : $factory_district;
        
        if (!empty($district_v) && !empty($state_v)) {
            
            $form['factory_part_a']['subdivision'] = array(
                '#title' => $factory_location_check_data.'(iv) Sub-Division',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Sub Division',
                    $zone_name_ck2 => $zone_name_ck2
                ),
                '#options' => common_custom_user_subdivisionlist_list_new($district_v),
                '#required' => TRUE,
                '#default_value' => $factory_subdivision,
                '#prefix' => '<div id="ld_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
            
        } else {
            
            $form['factory_part_a']['subdivision'] = array(
                '#title' => '(iv) Sub-Division',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Sub Division'
                ),
                '#required' => TRUE,
                '#options' => array(
                    '' => t('Select Sub-Division')
                ),
                '#prefix' => '<div id="ld_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        }
        
        $value_subdivision = isset($form_state['values']['subdivision']) ? $form_state['values']['subdivision'] : $factory_subdivision;
        
        if ((!empty($district_v) && ($district_v == 2 || $district_v == 4 || $district_v == 6 || $district_v == 7 || $district_v == 8 || $district_v == 9 || $district_v == 10 || $district_v == 11 || $district_v == 15 || $district_v == 16 || $district_v == 17 || $district_v == 18 || $district_v == 21)) && (!empty($state_v) && ($state_v == 1)) && ($value_subdivision != '181005')) {//   /*&& (!empty($value_subdivision)/*)&& ($value_subdivision =!= '181005')*/
            
            //   /*&& (!empty($value_subdivision)/*)&& ($value_subdivision =!= '181005')*/
        $form['factory_part_a']['estate_type'] = array(
                '#title' => '(iv) Estate Type',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Estate Type',
                    $zone_name_ck2 => $zone_name_ck2
                ),
                '#options' => common_custom_user_estatelist_list_new($district_v),
                '#required' => TRUE,
                '#default_value' => !empty($estate_type)?$estate_type:'',
                '#prefix' => '<div id="estate_type_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_a']['estate_type'] = array(
                '#prefix' => '<div id="estate_type_replace">',
                '#suffix' => '</div>'
            );
        }
        
        if (!empty($value_district) && !empty($value_state) && !empty($value_subdivision)) {
            $form['factory_part_a']['areatype'] = array(
                '#title' =>'(v) Area Type',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Area Type',
                    $zone_name_ck2 => $zone_name_ck2
                ),
                '#options' => common_custom_user_areatype_list_new($value_district, $value_subdivision),
                '#required' => TRUE,
                '#default_value' => $factory_areatype,
                '#prefix' => '<div id="ld_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load',
                    'progress' => array(
                        'type' => 'throbber',


                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_a']['areatype'] = array(
                '#title' => '(v) Area Type',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),

                    'placeholder' => 'Area Type'
                ),
                '#options' => array(
                    '0' => t('Select Area Type')
                ),
                '#required' => TRUE,
                '#prefix' => '<div id="ld_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        }
        
        $value_areatype = isset($form_state['values']['areatype']) ? $form_state['values']['areatype'] : $factory_areatype;
        
        if (!empty($value_district) && !empty($value_state) && $value_subdivision != "" && !empty($value_areatype)) {
            
            if ($value_areatype == 'B') {
                $areatype_name = 'Block';
            } elseif ($value_areatype == 'M') {
                $areatype_name = 'Municipality';
            } elseif ($value_areatype == 'C') {
                $areatype_name = 'Corporation';
            } elseif ($value_areatype == 'S') {
                $areatype_name = 'SEZ';
            } elseif ($value_areatype == 'N') {
                $areatype_name = 'Notified Area';
            }
            
            $form['factory_part_a']['block'] = array(
                '#title' => $factory_location_check_data.'(vi) '. $areatype_name,
                '#type' => 'select',

                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'subdivision',
                    $zone_name_ck2 => $zone_name_ck2
                ),
                '#options' 		=> common_custom_user_block_list_new($value_subdivision, $value_areatype),
                '#required' 	=> TRUE,
                '#default_value' => $factory_block,
                '#prefix' 		=> '<div id="ld_empareatype_name_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 		=> '</label></div></div>',
                '#ajax' 		=> array(
                'event' 		=> 'change',
                'effect' 		=> 'fade',
                'callback' 		=> 'get_ajax_load',
                'progress' 		=> array(
                'type' 			=> 'throbber',
                'message' 		=> t('loading')
                    )
                )
            );
            
        } else {
            $form['factory_part_a']['block'] = array(
                '#title' => '(vi) Block / Municipality / Corporation / Notified Area / SEZ',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'subdivision'
                ),
                '#options' => array(
                    '0' => t('Select Block / Municipality / Corporation / Notified Area / SEZ ')
                ),
                '#required' => TRUE,
                '#prefix' => '<div id="ld_empareatype_name_replace"><div class="col-md-4"><label class="select label-block" title="Block / Municipality / Corporation / Notified Area / SEZ">',
                '#suffix' => '</label></div></div>'
            );
        }
        
        $value_block      = isset($form_state['values']['block']) ? $form_state['values']['block'] : $factory_block;
        
        if (!empty($value_district) && !empty($value_subdivision) && !empty($value_areatype) && !empty($value_block) && !empty($value_state)) {
            
            if ($value_areatype == 'B') {
                $area_name = 'Gram Panchayat';
                $area_code = 'V';
            } elseif ($value_areatype == 'M') {
                $area_name = 'Ward';
                $area_code = 'W';
            } elseif ($value_areatype == 'C') {
                $area_name = 'Ward';
                $area_code = 'C';
            } elseif ($value_areatype == 'S') {
                $area_name = 'Sector';
                $area_code = 'S';
            } elseif ($value_areatype == 'N') {
                $area_name = 'Notified Area';
                $area_code = 'N';
            }
            
            $form['factory_part_a']['panchayat'] = array(
                '#title' => $factory_location_check_data.'(vii) '.$area_name,
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'panchayat',
                    $zone_name_ck2 => $zone_name_ck2
                ),
                '#options' => common_custom_user_villward_list_new($value_block, $area_code),
                '#default_value' => $factory_panchayat,
                '#prefix' => '<div id="ld_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#required' => TRUE,
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_a']['panchayat'] = array(
                '#title' => '(vii) Gram Panchayat / Ward / Sector',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'panchayat'
                ),
                '#options' => array(
                    '0' => t('Select Gram Panchayat / Ward / Sector / Notified Area')
                ),
                '#required' => TRUE,
                '#prefix' => '<div id="ld_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        }
        $value_panchayat = isset($form_state['values']['panchayat']) ? $form_state['values']['panchayat'] : $factory_panchayat;
        
        if (!empty($value_district) && !empty($value_subdivision) && !empty($value_areatype) && !empty($value_block) && !empty($value_state) && !empty($value_panchayat)) {
            $form['factory_part_a']['policestation'] = array(
                '#title' => $factory_location_check_data.'(x) Police Station',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Police Station',
                    $zone_name_ck2 => $zone_name_ck2
                ),
                '#options' => common_custom_user_ps_list_new($value_district),
                '#required' => TRUE,
                '#default_value' => $factory_policestation,
                '#prefix' => '<div id="ld_empps_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        } else {
            $form['factory_part_a']['policestation'] = array(
                '#title' => '(viii) Police Station',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Police Station'
                ),
                '#options' => array(
                    '0' => t('Select Police Station')
                ),
                '#required' => TRUE,
                '#prefix' => '<div id="ld_empps_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        }
        
        if (!empty($pincode_v)) {
            $form['factory_part_a']['postoffice'] = array(
                '#title' => $factory_location_check_data.'(ix) Post Office',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Post Office',
                    $zone_name_ck2 => $zone_name_ck2
                ),
                '#options' => common_custom_post_office_list_new($pincode_v),
                '#default_value' => $factory_postoffice,
                '#required' => TRUE,
                '#prefix' => '<div id="ld_post_office_div"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        } else {
            $form['factory_part_a']['postoffice'] = array(
                '#title' => '(ix) Post Office',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Post Office'
                ),
                '#options' => array(
                    '0' => t('Select Post Office')
                ),
                '#required' => TRUE,
                '#prefix' => '<div id="ld_post_office_div"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        }
        $form['factory_part_a']['mouza_name'] = array(
            '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
            '#suffix' 			=> '</div>',
            '#title' 			=> $factory_location_check_data.'(x). Mouza Name',
            '#type' 			=> 'textfield',
        // '#attributes' 		=> array( 'class' => array(''),$zone_name_ck2 => $zone_name_ck2),	  	
            '#default_value' 	=> $mouza_name,
            
        ); 
        $form['factory_part_a']['jl_no'] = array(
            '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
            '#suffix' 			=> '</div>',  
            '#title' 			=> $factory_location_check_data.'(xi). JL Number',
            '#type' 			=> 'textfield',
            '#default_value'  	=> $jl_number,
        // '#attributes' 		=> array( 'class' => array(''),$zone_name_ck2 => $zone_name_ck2),
            
        );
        if (!empty($value_block) && !empty($value_panchayat)) {
            
            $factory_zone_name = get_zone_name($value_block,$value_panchayat);
            
            $form['factory_part_a']['factory_zone'] = array(
                '#value'   => $factory_zone_name[0]->zone_id,
                '#type' => 'hidden',
            );
            
            $form['factory_part_a']['factory_zone_name'] = array(
                '#prefix' => '<div id="factory_zone_div"><div class="col-md-4"><label class="input label-block">',
                '#suffix' => '</label></div></div>',
                '#type' => 'textfield',
                '#title'  => t($factory_location_check_data.'(xii) Factory Zone'),
                '#value'=> $factory_zone_name[0]->zone_name,
                '#type' => 'textfield',
                //'#default_value'        => !empty($factory_zone) ? $factory_zone :'',
                '#required' => TRUE,
                '#attributes'		=> array('class' => array( ''),'readonly' => 'readonly'),
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load',
                    'progress' => array('type' => 'throbber','message' => t('loading')))
            );
    } else {
            $form['factory_part_a']['factory_zone_name'] = array(
                '#prefix' => '<div id="factory_zone_div"><div class="col-md-4"><label class="input label-block">',
                '#suffix' => '</label></div></div>',
                '#title'  => t('(x) Factory Zone'),
                '#type' => 'textfield',
                '#required' => TRUE,
            );
        }
        
        $form['factory_part_a']['nearest_landmark'] = array(
            '#prefix' => '<div class="col-md-4"><label class="input label-block">',
            '#suffix' => '</label></div>',
            '#title' => t('(xiii) Nearest Landmark'),
            '#type' => 'textfield',
            '#default_value' => $nearest_landmark,
            '#attributes' => array('class' => array('charField'),$zone_name_ck2 => $zone_name_ck2 )
        );
        
        
        if (!empty($value_block) && !empty($value_panchayat)) {
            
            $factory_zone_name = get_zone_name($value_block,$value_panchayat);
            $form['factory_part_a']['zone_boundary'] = array(
                '#prefix' => '<div id="view_boundary"><div class="col-md-12"><label class="input label-block" style="color:green;">',
                '#suffix' => '</label></div></div>',
                '#type' => 'markup',
                //'#markup'   => $factory_zone_name[0]->zone_details,
            );
            
    } else {
            $form['factory_part_a']['zone_boundary'] = array(
                '#prefix' => '<div id="view_boundary">',
                '#suffix' => '</div>',
            );
        }
        
        
        
        $form['factory_part_a']['addrline'] = array(
            '#title' => $factory_location_check_data.'(xiv) Address',
            '#rows' => 3,
            '#type' => 'textarea',
            '#required' => TRUE,
            '#default_value' => $factory_addrline,
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Address Line',
                $zone_name_ck2 => $zone_name_ck2
            ),
            '#prefix' => '<div class="col-md-12"><label class="textarea label-block">',
            '#suffix' => '</label></div>'
        );
        $form['factory_part_a']['comm_telephone'] = array(
            '#prefix' 			=> '<div class="col-md-3"><label class="input label-block">',
            '#suffix' 			=> '</label></div>',
            '#title' 			=> t($factory_location_check_data.'(xv). Telephone No.'),
            '#type' 			=> 'textfield',
            '#default_value' 	=> $comm_telephone,
            '#attributes' 		=> array( 'class' => array(''),$telephone_no_ck => $telephone_no_ck)
        );
    $form['factory_part_a']['comm_mobile'] = array(
            '#prefix'		 	=> '<div class="col-md-3"><label class="input label-block">',
            '#suffix' 			=> '</label></div>',
            '#title' 			=> t($factory_location_check_data.'(xvi). Mobile No.'),
            '#type' 			=> 'textfield',
            '#default_value' 	=> $comm_mobile,
            '#required'         => TRUE,
            '#attributes' 		=> array( 'class' => array(''),$mobile_no_ck => $mobile_no_ck)
            );
    $form['factory_part_a']['comm_alt_mobile'] = array(
            '#prefix'		 	=> '<div class="col-md-3"><label class="input label-block">',
            '#suffix' 			=> '</label></div>',
            '#title' 			=> t($factory_location_check_data.'(xvii). Alternate Mobile No.'),
            '#type' 			=> 'textfield',
            '#default_value' 	=> $comm_alt_mobile,
            '#attributes' 		=> array( 'class' => array(''),$comm_alt_mobile_ck => $comm_alt_mobile_ck)
            );
    $form['factory_part_a']['comm_fax'] = array(
            '#prefix' 			=> '<div class="col-md-3"><label class="input label-block">',
            '#suffix' 			=> '</label></div>',
            '#title' 			=> t($factory_location_check_data.'(xviii). Fax No.'),
            '#type' 			=> 'textfield',
            '#default_value' 	=> $comm_fax,
            '#attributes' 		=> array( 'class' => array(''),$fax_no_ck => $fax_no_ck)
        );

        $form['factory_part_a']['comm_email'] = array(
            '#prefix' 			=> '<div class="col-md-3"><label class="input label-block">',
            '#suffix' 			=> '</label></div></div>',
            '#title' 			=> t($factory_location_check_data.'(xvix). Email Id.'),
            '#type' 			=> 'textfield',
            '#default_value' 	=> $comm_email,
            '#required'         => TRUE,
            '#attributes' 		=> array( 'class' => array(''),$email_no_ck => $email_no_ck)
            );


        $form['factory_part_a']['firstRowEnd'] = array(
            '#suffix' => '</div>'
        );

/********** Location of the factory - End **********/

	
/********** Address of the Registered office / Head office - Start **********/

    $form['factory_part_off']              = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('C. Address of the Registered office / Head office'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE ,
		//'#description' 		=> t('<font color="#FF0000">(N.B.:- This address will be treated as communication address as per Section 7 of Factories Act, 1948)</font>')
		
    );
	$form['factory_part_off']['register_checked_data'] = array(
        '#type' 			=> 'hidden',
        '#value' 			=> $register_field_value,
		'#attributes' 		=> array('class' => array('')),
    );
	if(empty($headoffice_address_ck)){

 
		$form['factory_part_off']['application_period_section_c'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4"><label class="input label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t('(i). Application Period'),
			'#type' 			=> 'select',
			'#options' 			=> $lists,
			'#required' 		=> TRUE,
			'#attributes' 		=> array('class' => array( '')), 
		);
    }

	 $form['factory_part_off']['firstRowStart'] = array(
        '#prefix' 			=> '<div class="row">',
        '#suffix' 			=> ''
    );
    $form['factory_part_off']['addr_same'] = array(
        '#type' 			=> 'checkbox',
        '#default_value' 	=> $reg_adress_same_factory,
        '#ajax' 			=> array(
            							'event' 	=> 'change',
            							'effect' 	=> 'fade',
            							'callback' 	=> 'get_ajax_factory_address',
            							'progress' 	=> array(
                						'type' 		=> 'throbber',
                						'message' 	=> t('loading')
           							 )
        ),
        '#title' 			=> t('(i). Same as Location of the factory'),
        '#prefix'			=> '<div class="col-md-12">',
        '#suffix' 			=> '</div>',
		
    );
	
	$checkbox = isset($form_state['values']['addr_same']) ? $form_state['values']['addr_same'] : $reg_adress_same_factory;
    if ($checkbox == 1) {
		$form['factory_part_off']['country']        = array(
            '#prefix' 		=> '<div id="country_replace">',
            '#suffix' 		=> '</div>'
        );
        $form['factory_part_off']['pincodeoff']        = array(
            '#prefix' 		=> '<div id="off_edit_emp_pincodeoff_replace">',
            '#suffix' 		=> '</div>'
        );
        $form['factory_part_off']['state_off']         = array(
            '#prefix' 		=> '<div id="off_edit_emp_state_replace">',
            '#suffix' 		=> '</div>'
        );
        $form['factory_part_off']['district_off']      = array(
            '#prefix' 		=> '<div id="off_edit_emp_district_replace">',
            '#suffix' 		=> '</div>'
        );
        $form['factory_part_off']['subdivision_off']   = array(
            '#prefix' 		=> '<div id="off_empsubdv_replace">',
            '#suffix' 		=> '</div>'
        );
        $form['factory_part_off']['areatype_off']      = array(
            '#prefix' 		=> '<div id="off_emp_areatype_replace">',
            '#suffix' 		=> '</div>'
        );
        $form['factory_part_off']['block_off']         = array(
            '#prefix' 		=> '<div id="off_empareatype_name_replace">',
            '#suffix' 		=> '</div>'
        );
        $form['factory_part_off']['panchayat_off']     = array(
            '#prefix' 		=> '<div id="off_emp_vill_ward_replace">',
            '#suffix' 		=> '</div>'
        );
        $form['factory_part_off']['policestation_off'] = array(
            '#prefix' 		=> '<div id="off_empps_replace">',
            '#suffix' 		=> '</div>'
        );
        $form['factory_part_off']['postoffice_off']    = array(
            '#prefix' 		=> '<div id="off_post_office_div">',
            '#suffix' 		=> '</div>'
        );
        $form['factory_part_off']['addrline_off']      = array(
            '#prefix' 		=> '<div id="off_addressline_div">',
            '#suffix' 		=> '</div>'
        );
		$form['factory_part_off']['other_country_address']      = array(
            '#prefix' 		=> '<div id="other_country_address_id">',
            '#suffix' 		=> '</div>'
        );
    }
    if ($checkbox == 0) {
		
		$form['factory_part_off']['country'] = array(
			'#prefix' 			=> '<div id="country_replace"><div class="col-md-4 col-xs-4"><label class="select label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t($factory_headoffice_check_data.'(i). Country'),
			'#type' 			=> 'select',
			'#required' 		=> TRUE,
			'#options' 			=> get_country_with_ph(),
			'#default_value' 	=> !empty($country_code)?$country_code:'',
			'#attributes'		=> array('class' => array( ''),),
			'#ajax'				=> array(
								 'event' 	=> 'change',
								 'effect' 	=> 'fade',			
								 'callback' => 'get_ajax_country_code',
								 'progress'	=>	array(
								 'type'		=> 'throbber',
								 'message'	=> t('loading'),
								)
						)
    	);
		
		$form['factory_part_off']['other_country_address']      = array(
            '#prefix' 		=> '<div id="other_country_address_id">',
            '#suffix' 		=> '</div>'
        );
		$form['factory_part_off']['pincodeoff']        = array(
            '#prefix' 		=> '<div id="off_edit_emp_pincodeoff_replace">',
            '#suffix' 		=> '</div>'
        );
        $form['factory_part_off']['state_off']         = array(
            '#prefix' 		=> '<div id="off_edit_emp_state_replace">',
            '#suffix' 		=> '</div>'
        );
        $form['factory_part_off']['district_off']      = array(
            '#prefix' 		=> '<div id="off_edit_emp_district_replace">',
            '#suffix' 		=> '</div>'
        );
        $form['factory_part_off']['subdivision_off']   = array(
            '#prefix' 		=> '<div id="off_empsubdv_replace">',
            '#suffix' 		=> '</div>'
        );
        $form['factory_part_off']['areatype_off']      = array(
            '#prefix' 		=> '<div id="off_emp_areatype_replace">',
            '#suffix' 		=> '</div>'
        );
        $form['factory_part_off']['block_off']         = array(
            '#prefix' 		=> '<div id="off_empareatype_name_replace">',
            '#suffix' 		=> '</div>'
        );
        $form['factory_part_off']['panchayat_off']     = array(
            '#prefix' 		=> '<div id="off_emp_vill_ward_replace">',
            '#suffix' 		=> '</div>'
        );
        $form['factory_part_off']['policestation_off'] = array(
            '#prefix' 		=> '<div id="off_empps_replace">',
            '#suffix' 		=> '</div>'
        );
        $form['factory_part_off']['postoffice_off']    = array(
            '#prefix' 		=> '<div id="off_post_office_div">',
            '#suffix' 		=> '</div>'
        );
        $form['factory_part_off']['addrline_off']      = array(
            '#prefix' 		=> '<div id="off_addressline_div">',
            '#suffix' 		=> '</div>'
        );
			
		$country_id = isset($form_state['values']['country']) ? $form_state['values']['country'] :$country_code;
	
		if($country_id == '99'){
			//echo'India';die;
		     $form['factory_part_off']['pincodeoff'] = array(
            '#prefix' 		=> '<div id="off_edit_emp_pincodeoff_replace"><div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' 		=> '</label></div></div>',
            '#attributes' 	=> array(
                					'class' 				=> array(''),
                					'placeholder' 			=> 'Pincode',
									$headoffice_address_ck 	=> $headoffice_address_ck,
           							 ),
            '#autocomplete_path'  => 'pinautocomplete',
            '#maxlength' 		  => 6,
            '#default_value' 	  => $office_pincode,
            '#title' 			  => t($factory_headoffice_check_data.'(ii). Pincode'),
            '#required' 		  => TRUE,
            '#type'				  => 'textfield',
            '#ajax' 			  => array(
                              				 'effect' 		=> 'fade',
                							 'callback' 	=> 'get_ajax_load_off',
                							 'progress' 	=> array(
                    						  'type' 		=> 'throbber',
                   							 'message' 		=> t('loading')
               					 			)
           							 )
        );
        $value_pincode_off  = isset($form_state['values']['pincodeoff']) ? $form_state['values']['pincodeoff'] : $office_pincode;
        if (!empty($value_pincode_off)) {
            
            $query_off = db_select('fa_all_india_pin_code', 'p')->fields('p', array(
                'districtname',
                'statename',
                'pincode',
                'district_code',
                'state_code',
                'po_name'
            ))->condition('p.pincode', trim($value_pincode_off), '=');
            
            $result_off = $query_off->execute();
            if ($result_off->rowcount() > 0) {
                $final_off       = $result_off->fetchAssoc();
                $pincode_v_off   = $value_pincode_off;
                $state_v_off     = $final_off['state_code'];
                $district_v_off  = $final_off['district_code'];
                $post_office_off = $final_off['po_name'];
            }
        }
        
        if (!empty($state_v_off)) {
            $form['factory_part_off']['state_off'] = array(
                '#title' 				=> $factory_headoffice_check_data.'(iii). State',
                '#type' 				=> 'select',
                '#id' 					=> 'state_name_off',
                '#attributes' 			=> array(
                    								'class' 		=> array(),
                    								'placeholder' 	=> 'State'
                								),
                '#disabled' 			=> TRUE,
				 '#required' 		  	=> TRUE,
                '#options' 				=> get_all_state($state_v_off),
                '#default_value' 		=> !empty($state_v_off) ? $state_v_off : $office_state_off,
                '#prefix' 				=> '<div id="off_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 				=> '</label></div></div>',
                '#ajax' 				=> array(
													'event' 	=> 'change',
													'effect' 	=> 'fade',
													'callback' 	=> 'get_ajax_load_off',
													'progress' 	=> array(
																		'type' 		=> 'throbber',
																		'message' 	=> t('loading')
													)
                )
            );
        } else {
			 $form['factory_part_off']['state_off'] = array(
                '#title' 				=> '(iii). State',
                '#type' 				=> 'select',
                '#id' 					=> 'state_name_off',
                '#attributes' 			=> array(
                    								'class' 		=> array(),
                    								'readonly' 		=> 'readonly'
                								),
                '#disabled' 			=> TRUE,
				'#required' 		  	=> TRUE,
                '#options' 				=> array('' => t('Select State')),
                '#prefix' 				=> '<div id="off_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 				=> '</label></div></div>',
              
             );
            
        }
        
        $value_state_off = isset($form_state['values']['state_off']) ? $form_state['values']['state_off'] : $office_state_off;
        
        if (!empty($state_v_off)) {
            $form['factory_part_off']['district_off'] = array(
                '#title' 			=> $factory_headoffice_check_data.'(iv). District',
                '#type' 			=> 'select',
                '#disabled' 		=> TRUE,
                '#attributes' 		=> array('class' => array('')),							
               	'#required' 		=> TRUE,						
                '#options' 			=> get_district_by_id($state_v_off),
                '#value' 			=> !empty($district_v_off) ? $district_v_off : $office_district_off,
                '#prefix' 			=> '<div id="off_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 			=> '</label></div></div>',
                '#ajax' 			=> array(
												'event' 		=> 'change',
												'effect' 		=> 'fade',
												'callback' 		=> 'get_ajax_load_off',
												'progress' 		=> array(
																			'type' 		=> 'throbber',
																			'message' 	=> t('loading')
												)
               						 )
            );
        } else {
			$form['factory_part_off']['district_off'] = array(
                '#title' 			=> '(iv). District',
                '#type' 			=> 'select',
                '#disabled' 		=> TRUE,
                '#attributes' 		=> array('class' => array('')),							
               	'#required' 		=> TRUE,						
                '#options' 			=> array('' => t('Select District')),
                 '#prefix' 			=> '<div id="off_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 			=> '</label></div></div>',
                
            );
            
        }
        
        $form['factory_part_off']['firstRowEnd'] = array(
           		 '#prefix' 		=> '',
           		 '#suffix'		=> '</div>'
        );
        
        $value_district_off = isset($form_state['values']['district_off']) ? $form_state['values']['district_off'] : $office_district_off;
        
        $form['factory_part_off']['secondRowStart'] = array(
            '#prefix' 			=> '<div class="row">',
            '#suffix' 			=> ''
        );
        
        if (!empty($district_v_off) && !empty($state_v_off) && $state_v_off == 1) {
            
            $form['factory_part_off']['subdivision_off'] = array(
                '#title' 			=> $factory_headoffice_check_data.'(v). Sub-Division',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' => array(''),
                								'placeholder' 			=> 'Sub Division',
												$headoffice_address_ck => $headoffice_address_ck,
               								 ),
                '#options' 			=> common_custom_user_subdivisionlist_list_new($district_v_off),
                '#default_value' 	=> $office_subdivision_off,
				'#required' 		=> TRUE,
                '#prefix' 			=> '<div id="off_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 			=> '</label></div></div>',
                '#ajax' 			=> array(
												'event' => 'change',
												'effect' => 'fade',
												'callback' => 'get_ajax_load_off',
												'progress' => array(
																	'type' 		=> 'throbber',
																	'message' 	=> t('loading')
																)
                							)
            );
        } else {
			$form['factory_part_off']['subdivision_off'] = array(
                
                '#prefix' 			=> '<div id="off_empsubdv_replace">',
                '#suffix' 			=> '</div>',
               
				
            );
            
            
        }
        
        
        $value_subdivision_off = isset($form_state['values']['subdivision_off']) ? $form_state['values']['subdivision_off'] : $office_subdivision_off;
        
        if (!empty($value_district_off) && !empty($value_state_off) && !empty($value_subdivision_off) && $state_v_off == 1) {
            
            $form['factory_part_off']['areatype_off'] = array(
                	'#title' 			=> $factory_headoffice_check_data.'(vi). Area Type',
                	'#type' 			=> 'select',
                	'#attributes' 		=> array('class' => array(''),
                    					 			$headoffice_address_ck => $headoffice_address_ck,
                							),
                	'#options' 			=> common_custom_user_areatype_list_new($value_district_off, $value_subdivision_off),
                	'#default_value' 	=> $office_areatype_off,
					'#required' 		=> TRUE,
                	'#prefix' 			=> '<div id="off_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
                	'#suffix' 			=> '</label></div></div>',
                	'#ajax' 			=> array(
													'event' 		=> 'change',
													'effect' 		=> 'fade',
													'callback' 		=> 'get_ajax_load_off',
													'progress' 		=> array(
																			'type' 		=> 'throbber',
																			'message' 	=> t('loading')
																		)
												)
            );
        } else {
			$form['factory_part_off']['areatype_off'] = array(
                	'#prefix' 			=> '<div id="off_emp_areatype_replace">',
                	'#suffix' 			=> '</div>',
            );
           
        }
        
        $value_areatype_off = isset($form_state['values']['areatype_off']) ? $form_state['values']['areatype_off'] : $office_areatype_off;
        
        if (!empty($value_district_off) && !empty($value_state_off) && $value_subdivision_off != "" && !empty($value_areatype_off)&& $state_v_off == 1) {
            
            if ($value_areatype_off == 'B') {
                $areatype_name_off = 'Block';
            } elseif ($value_areatype_off == 'M') {
                $areatype_name_off = 'Municipality';
            } elseif ($value_areatype_off == 'C') {
                $areatype_name_off = 'Corporation';
            } elseif ($value_areatype_off == 'S') {
                $areatype_name_off = 'SEZ';
            } elseif ($value_areatype_off == 'N') {
                $areatype_name_off = 'Notified Area';
            }
            
       $form['factory_part_off']['block_off'] = array(
                '#title' 			=> $factory_headoffice_check_data.'(vii). '.$areatype_name_off,
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' => array(''),
                    						'placeholder' 			=> 'subdivision',
											$headoffice_address_ck => $headoffice_address_ck,
               							 ),
                '#options' 			=> common_custom_user_block_list_new($value_subdivision_off, $value_areatype_off),
                '#default_value' 	=> $office_block_off,
				'#required' 		=> TRUE,
                '#prefix' 			=> '<div id="off_empareatype_name_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 			=> '</label></div></div>',
                '#ajax' 			=> array(
												'event' 	=> 'change',
												'effect' 	=> 'fade',
												'callback' 	=> 'get_ajax_load_off',
												'progress' 	=> array(
																		'type' 		=> 'throbber',
																		'message' 	=> t('loading')
																)
											)
            );
            
            
        } else {
			
			 $form['factory_part_off']['block_off'] = array(
                
                '#prefix' 			=> '<div id="off_empareatype_name_replace">',
                '#suffix' 			=> '</div>',
                
            );
            
        }
        
        $form['factory_part_off']['secondRowEnd'] = array(
            '#prefix' 	=> '',
            '#suffix' 	=> '</div>'
        );
        
        $form['factory_part_off']['thirdRowStart'] = array(
            '#prefix' 			=> '<div class="row">',
            '#suffix' 			=> ''
        );
        $value_block_off  = isset($form_state['values']['block_off']) ? $form_state['values']['block_off'] : $office_block_off;
        
        if (!empty($value_district_off) && !empty($value_subdivision_off) && !empty($value_areatype_off) && !empty($value_block_off) && !empty($value_state_off) && $state_v_off == 1) {
            
            if ($value_areatype_off == 'B') {
                $area_name_off = 'Gram Panchayat';
                $area_code_off = 'V';
            } elseif ($value_areatype_off == 'M') {
                $area_name_off = 'Ward';
                
                $area_code_off = 'W';
            } elseif ($value_areatype_off == 'C') {
                $area_name_off = 'Ward';
                $area_code_off = 'C';
            } elseif ($value_areatype_off == 'S') {
                $area_name_off = 'Sector';
                $area_code_off = 'S';
            } elseif ($value_areatype_off == 'N') {
                $area_name_off = 'Notified Area';
                $area_code_off = 'N';
            }
            
            $form['factory_part_off']['panchayat_off'] = array(
                '#title' 			=> $factory_headoffice_check_data.'(viii). '.$area_name_off,
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 				=> array(''),
                   						 'placeholder' 				=> 'panchayat',
										  $headoffice_address_ck 	=> $headoffice_address_ck,
               					 		),
                '#options' 			=> common_custom_user_villward_list_new($value_block_off, $area_code_off),
                '#default_value' 	=> $office_panchayat_off,
				'#required' 		=> TRUE,
                '#prefix' 			=> '<div id="off_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 			=> '</label></div></div>',
                '#ajax' 			=> array(
												'event' 	=> 'change',
												'effect' 	=> 'fade',
												'callback' 	=> 'get_ajax_load_off',
												'progress' 	=> array(
																	'type' 		=> 'throbber',
																	'message' 	=> t('loading')
																	)
											)
            );
        } else {
			
			$form['factory_part_off']['panchayat_off'] = array(
           
                '#prefix' 			=> '<div id="off_emp_vill_ward_replace">',
                '#suffix' 			=> '</div>',
                
            );
			
            
        }
        $value_panchayat_off = isset($form_state['values']['panchayat_off']) ? $form_state['values']['panchayat_off'] : $office_panchayat_off;
        
        if (!empty($value_district_off) && !empty($value_subdivision_off) && !empty($value_areatype_off) && !empty($value_block_off) && !empty($value_state_off) && !empty($value_panchayat_off) && $state_v_off == 1) {
            
			$form['factory_part_off']['policestation_off'] = array(
                '#title' 			=> $factory_headoffice_check_data.'(ix). Police Station',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 					=> array(''),
                   							  $headoffice_address_ck 	=> $headoffice_address_ck,
               					 		),
                 '#options' 		=> common_custom_user_ps_list_new($value_district_off),
                '#default_value' 	=> $office_policestation_off,
				'#required' 		=> TRUE,
                '#prefix' 			=> '<div id="off_empps_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 			=> '</label></div></div>',
                
            );
			
         
        } else {
			
			$form['factory_part_off']['policestation_off'] = array(
                '#prefix' 			=> '<div id="off_empps_replace">',
                '#suffix' 			=> '</div>',
            );
           
        }
        
        if (!empty($pincode_v_off)) {
			
			$form['factory_part_off']['postoffice_off'] = array(
                '#title' 			=> $factory_headoffice_check_data.'(x). Post Office',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 					=> array(''),
                   							  $headoffice_address_ck 	=> $headoffice_address_ck,
               					 		),
                '#options' 			=> common_custom_post_office_list_new($pincode_v_off),
				'#default_value' 	=> $office_postoffice_off,
                '#required' 		=> TRUE,
                '#prefix' 			=> '<div id="off_post_office_div"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 			=> '</label></div></div>',
                
            );
           
        } else {
			
			$form['factory_part_off']['postoffice_off'] = array(
                
                '#prefix' 			=> '<div id="off_post_office_div">',
                '#suffix' 			=> '</div>',
                
            );
            
            
        }
        $form['factory_part_off']['addrline_off'] = array(
                '#title' 			=> $factory_headoffice_check_data.'(xi). Address',
                '#type' 			=> 'textarea',
				'#rows' 			=> 3,
                '#attributes' 		=> array('class' 					=> array(''),
                   							  $headoffice_address_ck 	=> $headoffice_address_ck,
               					 		),
                '#required' 		=> TRUE,
				'#default_value' 	=> $office_addrline_off,
                '#prefix' 			=> '<div id="off_addressline_div"><div class="col-md-12"><label class="textarea label-block">',
                '#suffix' 			=> '</label></div></div>',
                
            );
		
		
			
		}elseif(!empty($country_id)){
			
			$form['factory_part_off']['other_country_address'] = array(
                '#title' 			=> $factory_headoffice_check_data.'(ii) Country Address',
                '#type' 			=> 'textarea',
				'#rows' 			=> 3,
                '#attributes' 		=> array('class' => array(''), $headoffice_address_ck2 	=> $headoffice_address_ck2),
                '#required' 		=> TRUE,
				'#default_value' 	=> $factory_country_address,
                '#prefix' 			=> '<div id="other_country_address_id"><div class="col-md-12"><label class="textarea label-block">',
                '#suffix' 			=> '</label></div></div>', 
            );
		}else{
			
        $form['factory_part_off']['pincodeoff'] = array(
            '#prefix' 		=> '<div id="off_edit_emp_pincodeoff_replace"><div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' 		=> '</label></div></div>',
            '#attributes' 	=> array(
                					'class' 				=> array(''),
                					'placeholder' 			=> 'Pincode',
									$headoffice_address_ck 	=> $headoffice_address_ck,
           							 ),
            '#autocomplete_path'  => 'pinautocomplete',
            '#maxlength' 		  => 6,
            '#default_value' 	  => $office_pincode,
            '#title' 			  => t($factory_headoffice_check_data.'(ii). Pincode'),
            '#required' 		  => TRUE,
            '#type'				  => 'textfield',
            '#ajax' 			  => array(
                              				 'effect' 		=> 'fade',
                							 'callback' 	=> 'get_ajax_load_off',
                							 'progress' 	=> array(
                    						  'type' 		=> 'throbber',
                   							 'message' 		=> t('loading')
               					 			)
           							 )
        );
        $value_pincode_off  = isset($form_state['values']['pincodeoff']) ? $form_state['values']['pincodeoff'] : $office_pincode;
        if (!empty($value_pincode_off)) {
            
            $query_off = db_select('fa_all_india_pin_code', 'p')->fields('p', array(
                'districtname',
                'statename',
                'pincode',
                'district_code',
                'state_code',
                'po_name'
            ))->condition('p.pincode', trim($value_pincode_off), '=');
            
            $result_off = $query_off->execute();
            if ($result_off->rowcount() > 0) {
                $final_off       = $result_off->fetchAssoc();
                $pincode_v_off   = $value_pincode_off;
                $state_v_off     = $final_off['state_code'];
                $district_v_off  = $final_off['district_code'];
                $post_office_off = $final_off['po_name'];
            }
        }
        
        if (!empty($state_v_off)) {
            $form['factory_part_off']['state_off'] = array(
                '#title' 				=> '(iii). State',
                '#type' 				=> 'select',
                '#id' 					=> 'state_name_off',
                '#attributes' 			=> array(
                    								'class' 		=> array(),
                    								'placeholder' 	=> 'State'
                								),
                '#disabled' 			=> TRUE,
				 '#required' 		  	=> TRUE,
                '#options' 				=> get_all_state($state_v_off),
                '#default_value' 		=> !empty($state_v_off) ? $state_v_off : $office_state_off,
                '#prefix' 				=> '<div id="off_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 				=> '</label></div></div>',
                '#ajax' 				=> array(
													'event' 	=> 'change',
													'effect' 	=> 'fade',
													'callback' 	=> 'get_ajax_load_off',
													'progress' 	=> array(
																		'type' 		=> 'throbber',
																		'message' 	=> t('loading')
													)
                )
            );
        } else {
			 $form['factory_part_off']['state_off'] = array(
                '#title' 				=> '(iii). State',
                '#type' 				=> 'select',
                '#id' 					=> 'state_name_off',
                '#attributes' 			=> array(
                    								'class' 		=> array(),
                    								'readonly' 		=> 'readonly'
                								),
                '#disabled' 			=> TRUE,
				'#required' 		  	=> TRUE,
                '#options' 				=> array('' => t('Select State')),
                '#prefix' 				=> '<div id="off_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 				=> '</label></div></div>',
              
             );
            
        }
        
        $value_state_off = isset($form_state['values']['state_off']) ? $form_state['values']['state_off'] : $office_state_off;
        
        if (!empty($state_v_off)) {
            $form['factory_part_off']['district_off'] = array(
                '#title' 			=> '(iv). District',
                '#type' 			=> 'select',
                '#disabled' 		=> TRUE,
                '#attributes' 		=> array('class' => array('')),							
               	'#required' 		=> TRUE,						
                '#options' 			=> get_district_by_id($state_v_off),
                '#value' 			=> !empty($district_v_off) ? $district_v_off : $office_district_off,
                '#prefix' 			=> '<div id="off_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 			=> '</label></div></div>',
                '#ajax' 			=> array(
												'event' 		=> 'change',
												'effect' 		=> 'fade',
												'callback' 		=> 'get_ajax_load_off',
												'progress' 		=> array(
																			'type' 		=> 'throbber',
																			'message' 	=> t('loading')
												)
               						 )
            );
        } else {
			$form['factory_part_off']['district_off'] = array(
                '#title' 			=> '(iv). District',
                '#type' 			=> 'select',
                '#disabled' 		=> TRUE,
                '#attributes' 		=> array('class' => array('')),							
               	'#required' 		=> TRUE,						
                '#options' 			=> array('' => t('Select District')),
                 '#prefix' 			=> '<div id="off_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 			=> '</label></div></div>',
                
            );
            
        }
        
        $form['factory_part_off']['firstRowEnd'] = array(
           		 '#prefix' 		=> '',
           		 '#suffix'		=> '</div>'
        );
        
        $value_district_off = isset($form_state['values']['district_off']) ? $form_state['values']['district_off'] : $office_district_off;
        
        $form['factory_part_off']['secondRowStart'] = array(
            '#prefix' 			=> '<div class="row">',
            '#suffix' 			=> ''
        );
        
        if (!empty($district_v_off) && !empty($state_v_off)) {
            
            $form['factory_part_off']['subdivision_off'] = array(
                '#title' 			=> '(v). Sub-Division',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' => array(''),
                								'placeholder' 			=> 'Sub Division',
												$headoffice_address_ck => $headoffice_address_ck,
               								 ),
                '#options' 			=> common_custom_user_subdivisionlist_list_new($district_v_off),
                '#default_value' 	=> $office_subdivision_off,
				'#required' 		=> TRUE,
                '#prefix' 			=> '<div id="off_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 			=> '</label></div></div>',
                '#ajax' 			=> array(
												'event' => 'change',
												'effect' => 'fade',
												'callback' => 'get_ajax_load_off',
												'progress' => array(
																	'type' 		=> 'throbber',
																	'message' 	=> t('loading')
																)
                							)
            );
        } else {
			$form['factory_part_off']['subdivision_off'] = array(
                '#title' 			=> '(v). Sub-Division',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' => array(''),
                								'placeholder' 			=> 'Sub Division',

												$headoffice_address_ck => $headoffice_address_ck,
               								 ),
               '#options' 			=> array('' => t('Select Sub-Division')),
               
				'#required' 		=> TRUE,
                '#prefix' 			=> '<div id="off_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 			=> '</label></div></div>',
               
				
            );
            
            
        }
        
        
        $value_subdivision_off = isset($form_state['values']['subdivision_off']) ? $form_state['values']['subdivision_off'] : $office_subdivision_off;
        
        if (!empty($value_district_off) && !empty($value_state_off) && !empty($value_subdivision_off)) {
            
            $form['factory_part_off']['areatype_off'] = array(
                	'#title' 			=> '(vi). Area Type',
                	'#type' 			=> 'select',
                	'#attributes' 		=> array('class' => array(''),
                    					 			$headoffice_address_ck => $headoffice_address_ck,
                							),
                	'#options' 			=> common_custom_user_areatype_list_new($value_district_off, $value_subdivision_off),
                	'#default_value' 	=> $office_areatype_off,
					'#required' 		=> TRUE,
                	'#prefix' 			=> '<div id="off_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
                	'#suffix' 			=> '</label></div></div>',
                	'#ajax' 			=> array(
													'event' 		=> 'change',
													'effect' 		=> 'fade',
													'callback' 		=> 'get_ajax_load_off',
													'progress' 		=> array(
																			'type' 		=> 'throbber',
																			'message' 	=> t('loading')
																		)
												)
            );
        } else {
			$form['factory_part_off']['areatype_off'] = array(
                	'#title' 			=> '(vi). Area Type',
                	'#type' 			=> 'select',
                	'#attributes' 		=> array('class' => array(''),
                    					 			$headoffice_address_ck => $headoffice_address_ck,
                							),
                 	'#options' 			=> array('0' => t('Select Area Type')),
                	'#required' 		=> TRUE,
                	'#prefix' 			=> '<div id="off_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
                	'#suffix' 			=> '</label></div></div>',
                	
            );
           
        }
        
        $value_areatype_off = isset($form_state['values']['areatype_off']) ? $form_state['values']['areatype_off'] : $office_areatype_off;
        
        if (!empty($value_district_off) && !empty($value_state_off) && $value_subdivision_off != "" && !empty($value_areatype_off)) {
            
            if ($value_areatype_off == 'B') {
                $areatype_name_off = 'Block';
            } elseif ($value_areatype_off == 'M') {
                $areatype_name_off = 'Municipality';
            } elseif ($value_areatype_off == 'C') {
                $areatype_name_off = 'Corporation';
            } elseif ($value_areatype_off == 'S') {
                $areatype_name_off = 'SEZ';
            } elseif ($value_areatype_off == 'N') {
                $areatype_name_off = 'Notified Area';
            }
            
       $form['factory_part_off']['block_off'] = array(
                '#title' 			=> '(vii). '.$areatype_name_off,
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' => array(''),
                    						'placeholder' 			=> 'subdivision',
											$headoffice_address_ck => $headoffice_address_ck,
               							 ),
                '#options' 			=> common_custom_user_block_list_new($value_subdivision_off, $value_areatype_off),
                '#default_value' 	=> $office_block_off,
				'#required' 		=> TRUE,
                '#prefix' 			=> '<div id="off_empareatype_name_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 			=> '</label></div></div>',
                '#ajax' 			=> array(
												'event' 	=> 'change',
												'effect' 	=> 'fade',
												'callback' 	=> 'get_ajax_load_off',
												'progress' 	=> array(
																		'type' 		=> 'throbber',
																		'message' 	=> t('loading')
																)
											)
            );
            
            
        } else {
			
			 $form['factory_part_off']['block_off'] = array(
                '#title' 			=> '(vii). Block / Municipality / Corporation / Notified Area / SEZ',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' => array(''),
                    						'placeholder' 			=> 'subdivision',
											$headoffice_address_ck => $headoffice_address_ck,
               							 ),
				'#required' 		=> TRUE,
              	'#options' 			=> array(
                    							'0' => t('Select Block / Municipality / Corporation / SEZ / Notified Area')
                							),
                '#prefix' 			=> '<div id="off_empareatype_name_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 			=> '</label></div></div>',
                
            );
            
        }
        
        $form['factory_part_off']['secondRowEnd'] = array(
            '#prefix' 	=> '',
            '#suffix' 	=> '</div>'
        );
        
        $form['factory_part_off']['thirdRowStart'] = array(
            '#prefix' 			=> '<div class="row">',
            '#suffix' 			=> ''
        );
        $value_block_off  = isset($form_state['values']['block_off']) ? $form_state['values']['block_off'] : $office_block_off;
        
        if (!empty($value_district_off) && !empty($value_subdivision_off) && !empty($value_areatype_off) && !empty($value_block_off) && !empty($value_state_off)) {
            
            if ($value_areatype_off == 'B') {
                $area_name_off = 'Gram Panchayat';
                $area_code_off = 'V';
            } elseif ($value_areatype_off == 'M') {
                $area_name_off = 'Ward';
                
                $area_code_off = 'W';
            } elseif ($value_areatype_off == 'C') {
                $area_name_off = 'Ward';
                $area_code_off = 'C';
            } elseif ($value_areatype_off == 'S') {
                $area_name_off = 'Sector';
                $area_code_off = 'S';
            } elseif ($value_areatype_off == 'N') {
                $area_name_off = 'Notified Area';
                $area_code_off = 'N';
            }
            
            $form['factory_part_off']['panchayat_off'] = array(
                '#title' 			=> '(viii). '.$area_name_off,
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 				=> array(''),
                   						 'placeholder' 				=> 'panchayat',
										  $headoffice_address_ck 	=> $headoffice_address_ck,
               					 		),
                '#options' 			=> common_custom_user_villward_list_new($value_block_off, $area_code_off),
                '#default_value' 	=> $office_panchayat_off,
				'#required' 		=> TRUE,
                '#prefix' 			=> '<div id="off_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 			=> '</label></div></div>',
                '#ajax' 			=> array(
												'event' 	=> 'change',
												'effect' 	=> 'fade',
												'callback' 	=> 'get_ajax_load_off',
												'progress' 	=> array(
																	'type' 		=> 'throbber',
																	'message' 	=> t('loading')
																	)
											)
            );
        } else {
			
			$form['factory_part_off']['panchayat_off'] = array(
                '#title' 			=> '(viii). Gram Panchayat / Ward / Sector',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 					=> array(''),
                   							  $headoffice_address_ck 	=> $headoffice_address_ck,
               					 		),
                '#options' 			=> array('0' => t('Select Gram Panchayat / Ward / Sector / Notified Area')),
                '#default_value' 	=> $office_panchayat_off,
				'#required' 		=> TRUE,
                '#prefix' 			=> '<div id="off_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 			=> '</label></div></div>',
                
            );
			
            
        }
        $value_panchayat_off = isset($form_state['values']['panchayat_off']) ? $form_state['values']['panchayat_off'] : $office_panchayat_off;
        
        if (!empty($value_district_off) && !empty($value_subdivision_off) && !empty($value_areatype_off) && !empty($value_block_off) && !empty($value_state_off) && !empty($value_panchayat_off)) {
            
			$form['factory_part_off']['policestation_off'] = array(
                '#title' 			=> '(ix). Police Station',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 					=> array(''),
                   							  $headoffice_address_ck 	=> $headoffice_address_ck,
               					 		),
                 '#options' 		=> common_custom_user_ps_list_new($value_district_off),
                '#default_value' 	=> $office_policestation_off,
				'#required' 		=> TRUE,
                '#prefix' 			=> '<div id="off_empps_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 			=> '</label></div></div>',
                
            );
			
         
        } else {
			
			$form['factory_part_off']['policestation_off'] = array(
                '#title' 			=> '(ix). Police Station',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 					=> array(''),
                   							  $headoffice_address_ck 	=> $headoffice_address_ck,
               					 		),
                '#options' 		=> array('0' => t('Select Police Station')),
                '#required' 		=> TRUE,
                '#prefix' 			=> '<div id="off_empps_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 			=> '</label></div></div>',
                
            );
           
        }
        
        if (!empty($pincode_v_off)) {
			
			$form['factory_part_off']['postoffice_off'] = array(
                '#title' 			=> '(x). Post Office',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 					=> array(''),
                   							  $headoffice_address_ck 	=> $headoffice_address_ck,
               					 		),
                '#options' 			=> common_custom_post_office_list_new($pincode_v_off),
				'#default_value' 	=> $office_postoffice_off,
                '#required' 		=> TRUE,
                '#prefix' 			=> '<div id="off_post_office_div"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 			=> '</label></div></div>',
                
            );
           
        } else {
			
			$form['factory_part_off']['postoffice_off'] = array(
                '#title' 			=> '(x). Post Office',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 					=> array(''),
                   							  $headoffice_address_ck 	=> $headoffice_address_ck,
               					 		),
                '#options' 			=>  array('0' => t('Select Post Office')
                ),
                '#required' 		=> TRUE,
                '#prefix' 			=> '<div id="off_post_office_div"><div class="col-md-4"><label class="select label-block">',
                '#suffix' 			=> '</label></div></div>',
                
            );
            
            
        }
            $form['factory_part_off']['addrline_off'] = array(
                '#title' 			=> $factory_headoffice_check_data.'(xi). Address',
                '#type' 			=> 'textarea',
				'#rows' 			=> 3,
                '#attributes' 		=> array('class' 					=> array(''),
                   							  $headoffice_address_ck2 	=> $headoffice_address_ck2,
               					 		),
                '#required' 		=> TRUE,
				'#default_value' 	=> $office_addrline_off,
                '#prefix' 			=> '<div id="off_addressline_div"><div class="col-md-12"><label class="textarea label-block">',
                '#suffix' 			=> '</label></div></div>',
                
            );

            /*$form['factory_part_off']['thirdRowEnd'] = array(
                '#prefix' => '',
                '#suffix' => '</div>'
            );*/

    	    }
	    }
	
	    /*$form['factory_part_off']['addres_defination'] = array(
            '#type' 			=> 'markup',
            '#prefix' 			=> '<div class="row"><div class="col-md-12"><label class="input">',
            '#suffix' 			=> '</label></div><div>',
            '#markup' 			=> t('<font color="#FF0000">(N.B:-This address will be treated as communication address as per Section 7 of Factories Act,1948 )</font>')
        );*/
	 
	
        /********** Address of the Registered office / Head office - End **********/

	
	/********** Communication Address - Start **********/
	
        $form['factory_part_comm']              = array(
            '#type' => 'fieldset',
            '#title' => t('D. Communication Address'),
            '#collapsible' => TRUE, // Added
            '#collapsed' => FALSE // Added
        );
        $form['factory_part_comm']['communication_checked_data'] = array(
            '#type' 			=> 'hidden',
            '#value' 			=> $communication_field_value,
            '#attributes' 		=> array('class' => array('')),
        );
        if(empty($factory_communication_ck)){

            $form['factory_part_comm']['application_period_section_d'] = array(
                    '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4"><label class="input label-block">',
                    '#suffix' 			=> '</label></div></div>',
                    '#title' 			=> t('(i). Application Period'),
                    '#type' 			=> 'select',
                    '#options' 			=> $lists,
                    '#required' 		=> TRUE,
                    '#attributes' 		=> array('class' => array( ''),),
                
            );
        }
        $form['factory_part_comm']['firstRowStart'] = array(
            '#prefix' 			=> '<div class="row">',
        );

        $option = array( "1" => "Default", "2" => "Same as Location of the factory","3" => "Same as Registered office / Head office");

	    $form['factory_part_comm']['addr_same_comm'] = array(
					'#prefix'		 	=> '<div id="is_comm_address_div"><div class="col-md-12 col-xs-12">',
					'#suffix' 			=> '</div></div>',
					'#options'			=> $option,
					'#type' 			=> 'radios',
					'#required' 		=> TRUE,
					'#default_value' 	=> $reg_adress_same_factory_comm,
					'#ajax' 			=> array(
												'event' => 'change',
												'effect' => 'fade',
												'callback' => 'get_ajax_comm_same_address',
												'progress' => array(
													'type' => 'throbber',
													'message' => t('loading')
												)
										)
				);
				
	    $checkbox_comm = isset($form_state['values']['addr_same_comm']) ? $form_state['values']['addr_same_comm'] : $reg_adress_same_factory_comm;
        if ($checkbox_comm == 2 || $checkbox_comm == 3) {
            $form['factory_part_comm']['pincodecomm']        = array(
                '#prefix' => '<div id="comm_edit_emp_pincodecomm_replace">',
                '#suffix' => '</div>'
            );
            $form['factory_part_comm']['state_comm']         = array(
                '#prefix' => '<div id="comm_edit_emp_state_replace">',
                '#suffix' => '</div>'
            );
            $form['factory_part_comm']['district_comm']      = array(
                '#prefix' => '<div id="comm_edit_emp_district_replace">',
                '#suffix' => '</div>'
            );
            $form['factory_part_comm']['subdivision_comm']   = array(
                '#prefix' => '<div id="comm_empsubdv_replace">',
                '#suffix' => '</div>'
            );
            $form['factory_part_comm']['areatype_comm']      = array(
                '#prefix' => '<div id="comm_emp_areatype_replace">',
                '#suffix' => '</div>'
            );
            $form['factory_part_comm']['block_comm']         = array(
                '#prefix' => '<div id="comm_empareatype_name_replace">',
                '#suffix' => '</div>'
            );
            $form['factory_part_comm']['panchayat_comm']     = array(
                '#prefix' => '<div id="comm_emp_vill_ward_replace">',
                '#suffix' => '</div>'
            );
            $form['factory_part_comm']['policestation_comm'] = array(
                '#prefix' => '<div id="comm_empps_replace">',
                '#suffix' => '</div>'
            );
            $form['factory_part_comm']['postoffice_comm']    = array(
                '#prefix' => '<div id="comm_post_office_div">',
                '#suffix' => '</div>'
            );
            $form['factory_part_comm']['addrline_comm']      = array(
                '#prefix' => '<div id="comm_addressline_div">',
                '#suffix' => '</div>'
            );
        }
        if ($checkbox_comm == 1) {
            $form['factory_part_comm']['pincodecomm'] = array(
                '#prefix' => '<div id="comm_edit_emp_pincodecomm_replace"><div class="col-md-4 col-xs-12"><label class="input label-block">',
                '#suffix' => '</label></div></div>',
                '#attributes' => array(
                    'class' => array(''),
                    'placeholder' => 'Pincode',
                    $factory_communication_ck => $factory_communication_ck
                ),
                '#autocomplete_path' => 'pinautocomplete',
                '#id' => 'pincode_autocomplete_comm',
                '#maxlength' => 6,
                '#default_value' => $office_pincode_comm,
                '#title' => t($factory_communication_check_data.'(i) Pincode'),
                '#required' => TRUE,
                '#type' => 'textfield',
                '#ajax' => array(
                    //'event'         => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_comm',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
            $value_pincode_comm                      = isset($form_state['values']['pincodecomm']) ? $form_state['values']['pincodecomm'] : $office_pincode_comm;
            if (!empty($value_pincode_comm)) {
                
                $query_comm = db_select('fa_all_india_pin_code', 'p')->fields('p', array(
                    'districtname',
                    'statename',
                    'pincode',
                    'district_code',
                    'state_code',
                    'po_name'
                ))->condition('p.pincode', trim($value_pincode_comm), '=');
                
                $result_comm = $query_comm->execute();
                

                if ($result_comm->rowcount() > 0) {
                    $final_comm       = $result_comm->fetchAssoc();
                    $pincode_v_comm   = $value_pincode_comm;
                    $state_v_comm     = $final_comm['state_code'];
                    $district_v_comm  = $final_comm['district_code'];
                    $post_commice_comm = $final_comm['po_name'];
                }
            }
            
            if (!empty($state_v_comm)) {
                $form['factory_part_comm']['state_comm'] = array(
                    '#title' => $factory_communication_check_data.'(ii) State',
                    '#type' => 'select',
                    '#id' => 'state_name_comm',
                    '#attributes' => array(
                        'class' => array(
                            ''
                        ),
                        'placeholder' => 'State',
                        $factory_communication_ck => $factory_communication_ck
                    ),
                    '#disabled' => TRUE,
                    '#options' => get_all_state($state_v_comm),
                    '#default_value' => !empty($state_v_comm) ? $state_v_comm : $office_state_comm,
                    '#required' => TRUE,
                    '#prefix' => '<div id="comm_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#ajax' => array(
                        'event' => 'change',
                        'effect' => 'fade',
                        'callback' => 'get_ajax_load_comm',
                        'progress' => array(
                            'type' => 'throbber',
                            'message' => t('loading')
                        )
                    )
                );
            } else {
                $form['factory_part_comm']['state_comm'] = array(
                    '#title' => '(ii) State',
                    '#type' => 'select',
                    '#id' => 'state_name_comm',
                    '#disabled' => TRUE,
                    '#attributes' => array(
                        'class' => array(
                            ''
                        ),
                        'placeholder' => 'State',
                        'readonly' => 'readonly'
                    ),
                    '#options' => array(
                        '' => t('Select State')
                    ),
                    '#required' => TRUE,
                    '#prefix' => '<div id="comm_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#ajax' => array(
                        'event' => 'change',
                        'effect' => 'fade',
                        'callback' => 'get_ajax_load_comm',
                        'progress' => array(
                            'type' => 'throbber',
                            'message' => t('loading')
                        )
                    )
                );
            }
        //echo $form_state['values']['state_comm']; 
        $value_state_comm = isset($form_state['values']['state_comm']) ? $form_state['values']['state_comm'] : $office_state_comm;
            
            if (!empty($state_v_comm)) {
                $form['factory_part_comm']['district_comm'] = array(
                    '#title' => $factory_communication_check_data.'(iii) District',
                    '#type' => 'select',
                    '#id' => 'district_name_comm',
                    '#disabled' => TRUE,
                    '#attributes' => array(

                        'class' => array(
                            ''
                        ),
                        'placeholder' => 'District',
                        $factory_communication_ck => $factory_communication_ck
                    ),
                    '#options' => get_district_by_id($state_v_comm),
                    '#value' => !empty($district_v_comm) ? $district_v_comm : $office_district_comm,
                    '#required' => TRUE,
                    '#prefix' => '<div id="comm_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#ajax' => array(
                        'event' => 'change',
                        'effect' => 'fade',

                        'callback' => 'get_ajax_load_comm',
                        'progress' => array(
                            'type' => 'throbber',
                            'message' => t('loading')
                        )
                    )
                );
            } else {
                $form['factory_part_comm']['district_comm'] = array(
                    '#title' => '(iii) District',
                    '#type' => 'select',
                    '#id' => 'district_name_comm',
                    '#disabled' => TRUE,
                    '#attributes' => array(
                        'class' => array(
                            ''
                        ),
                        'placeholder' => 'District'
                    ),
                    '#options' => array(

                        '' => t('Select District')
                    ),
                    '#required' => TRUE,
                    '#prefix' => '<div id="comm_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>'
                );
            }
            
            $form['factory_part_comm']['firstRowEnd'] = array(
                '#prefix' => '',
                '#suffix' => '</div>'
            );
            
            $value_district_comm = isset($form_state['values']['district_comm']) ? $form_state['values']['district_comm'] : $office_district_comm;
            
            $form['factory_part_comm']['secondRowStart'] = array(
                '#prefix' => '<div class="row">',
                '#suffix' => ''
            );
            
            if (!empty($district_v_comm) && !empty($state_v_comm)) {
                
                $form['factory_part_comm']['subdivision_comm'] = array(
                    '#title' => $factory_communication_check_data.'(iv) Sub-Division',
                    '#type' => 'select',
                    '#attributes' => array(
                        'class' => array(
                            ''
                        ),
                        'placeholder' => 'Sub Division',
                        $factory_communication_ck => $factory_communication_ck
                    ),
                    '#options' => common_custom_user_subdivisionlist_list_new($district_v_comm),
                    '#required' => TRUE,
                    '#default_value' => $office_subdivision_comm,
                    '#prefix' => '<div id="comm_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#ajax' => array(
                        'event' => 'change',
                        'effect' => 'fade',
                        'callback' => 'get_ajax_load_comm',
                        'progress' => array(
                            'type' => 'throbber',
                            'message' => t('loading')
                        )
                    )
                );
            } else {
                
                $form['factory_part_comm']['subdivision_comm'] = array(
                    '#title' => '(iv) Sub-Division',
                    '#type' => 'select',
                    '#attributes' => array(
                        'class' => array(
                            ''
                        ),
                        'placeholder' => 'Sub Division'
                    ),
                    '#options' => array(
                        '' => t('Select Sub-Division')
                    ),
                    '#required' => TRUE,
                    '#prefix' => '<div id="comm_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>'
                );
            }
            
            
            $value_subdivision_comm = isset($form_state['values']['subdivision_comm']) ? $form_state['values']['subdivision_comm'] : $office_subdivision_comm;
            
            if (!empty($value_district_comm) && !empty($value_state_comm) && !empty($value_subdivision_comm)) {
                
                $form['factory_part_comm']['areatype_comm'] = array(
                    '#title' => $factory_communication_check_data.'(v) Area Type COMM',
                    '#type' => 'select',
                    '#attributes' => array(
                        'class' => array(
                            ''
                        ),
                        'placeholder' => 'Area Type',
                        $factory_communication_ck => $factory_communication_ck
                    ),
                    '#options' => common_custom_user_areatype_list_new($value_district_comm, $value_subdivision_comm),
                    '#required' => TRUE,
                    '#default_value' => $office_areatype_comm,
                    '#prefix' => '<div id="comm_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#ajax' => array(
                        'event' => 'change',
                        'effect' => 'fade',
                        'callback' => 'get_ajax_load_comm',
                        'progress' => array(
                            'type' => 'throbber',
                            'message' => t('loading')
                        )
                    )
                );
            } else {
                $form['factory_part_comm']['areatype_comm'] = array(
                    '#title' => '(v) Area Type',
                    '#type' => 'select',
                    '#attributes' => array(
                        'class' => array(
                            ''
                        ),
                        'placeholder' => 'Area Type'
                    ),
                    '#options' => array(
                        '0' => t('Select Area Type')
                    ),
                    '#required' => TRUE,
                    '#prefix' => '<div id="comm_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>'
                );
            }
            
            $value_areatype_comm = isset($form_state['values']['areatype_comm']) ? $form_state['values']['areatype_comm'] : $office_areatype_comm;
            
            if (!empty($value_district_comm) && !empty($value_state_comm) && $value_subdivision_comm != "" && !empty($value_areatype_comm)) {
                
                if ($value_areatype_comm == 'B') {
                    $areatype_name_comm = 'Block';
                } elseif ($value_areatype_comm == 'M') {
                    $areatype_name_comm = 'Municipality';
                } elseif ($value_areatype_comm == 'C') {
                    $areatype_name_comm = 'Corporation';
                } elseif ($value_areatype_comm == 'S') {
                    $areatype_name_comm = 'SEZ';
                } elseif ($value_areatype_comm == 'N') {
                    $areatype_name_comm = 'Notified Area';
                }
                
                $form['factory_part_comm']['block_comm'] = array(
                    '#title' => $factory_communication_check_data.'(vi)'.$areatype_name_comm,
                    '#type' => 'select',
                    '#attributes' => array(
                        'class' => array(
                            ''
                        ),
                        'placeholder' => 'subdivision',
                        $factory_communication_ck => $factory_communication_ck
                    ),
                    '#options' => common_custom_user_block_list_new($value_subdivision_comm, $value_areatype_comm),
                    '#required' => TRUE,
                    '#default_value' => $office_block_comm,
                    '#prefix' => '<div id="comm_empareatype_name_replace" class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div>',
                    '#ajax' => array(
                        'event' => 'change',
                        'effect' => 'fade',
                        'callback' => 'get_ajax_load_comm',
                        'progress' => array(
                            'type' => 'throbber',
                            'message' => t('loading')
                        )
                    )
                );
                
            } else {
                $form['factory_part_comm']['block_comm'] = array(
                    '#title' => '(vi) Block / Municipality / Corporation / Notified Area / SEZ',
                    '#type' => 'select',
                    '#attributes' => array(
                        'class' => array(
                            ''
                        ),
                        'placeholder' => 'subdivision'
                    ),
                    '#options' => array(
                        '0' => t('Select Block / Municipality / Corporation / Notified Area / SEZ')
                    ),
                    '#required' => TRUE,
                    '#prefix' => '<div id="comm_empareatype_name_replace"><div class="col-md-4"><label class="select label-block" title="Block / Municipality / Corporation / Notified Area / SEZ">',
                    '#suffix' => '</label></div></div>'
                );
            }
            
            $form['factory_part_comm']['secondRowEnd'] = array(
                '#prefix' => '',
                '#suffix' => '</div>'
            );
            
            $form['factory_part_comm']['thirdRowStart'] = array(
                '#prefix' => '<div class="row">',
                '#suffix' => ''
            );
            $value_block_comm                           = isset($form_state['values']['block_comm']) ? $form_state['values']['block_comm'] : $office_block_comm;
            
            if (!empty($value_district_comm) && !empty($value_subdivision_comm) && !empty($value_areatype_comm) && !empty($value_block_comm) && !empty($value_state_comm)) {
                
                if ($value_areatype_comm == 'B') {
                    $area_name_comm = 'Gram Panchayat';
                    $area_code_comm = 'V';
                } elseif ($value_areatype_comm == 'M') {
                    $area_name_comm = 'Ward';
                    $area_code_comm = 'W';
                } elseif ($value_areatype_comm == 'C') {
                    $area_name_comm = 'Ward';
                    $area_code_comm = 'C';
                } elseif ($value_areatype_comm == 'S') {
                    $area_name_comm = 'Sector';
                    $area_code_comm = 'S';
                } elseif ($value_areatype_comm == 'N') {
                    $area_name_comm = 'Notified Area';
                    $area_code_comm = 'N';
                }
                
                $form['factory_part_comm']['panchayat_comm'] = array(
                    '#title' => $factory_communication_check_data.'(vii)'.$area_name_comm,
                    '#type' => 'select',
                    '#attributes' => array(
                        'class' => array(
                            ''
                        ),
                        'placeholder' => 'panchayat',
                        $factory_communication_ck => $factory_communication_ck
                    ),
                    '#options' => common_custom_user_villward_list_new($value_block_comm, $area_code_comm),
                    '#required' => TRUE,
                    '#default_value' => $office_panchayat_comm,
                    '#prefix' => '<div id="comm_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>',
                    '#ajax' => array(
                        'event' => 'change',
                        'effect' => 'fade',
                        'callback' => 'get_ajax_load_comm',
                        'progress' => array(
                            'type' => 'throbber',
                            'message' => t('loading')
                        )
                    )
                );
            } else {
                $form['factory_part_comm']['panchayat_comm'] = array(
                    '#title' => '(vii) Gram Panchayat / Ward / Sector',
                    '#type' => 'select',
                    '#attributes' => array(
                        'class' => array(
                            ''
                        ),
                        'placeholder' => 'panchayat'
                    ),
                    '#options' => array(
                        '0' => t('Select Gram Panchayat / Ward / Sector / Notified Area')
                    ),
                    '#required' => TRUE,
                    '#prefix' => '<div id="comm_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>'
                );
            }
            $value_panchayat_comm = isset($form_state['values']['panchayat_comm']) ? $form_state['values']['panchayat_comm'] : $office_panchayat_comm;
            
            if (!empty($value_district_comm) && !empty($value_subdivision_comm) && !empty($value_areatype_comm) && !empty($value_block_comm) && !empty($value_state_comm) && !empty($value_panchayat_comm)) {
                
                $form['factory_part_comm']['policestation_comm'] = array(
                    '#title' => $factory_communication_check_data.'(viii) Police Station',
                    '#type' => 'select',
                    '#attributes' => array(
                        'class' => array(
                            ''
                        ),
                        'placeholder' => 'Police Station',
                        $factory_communication_ck => $factory_communication_ck
                    ),
                    '#options' => common_custom_user_ps_list_new($value_district_comm),
                    '#required' => TRUE,
                    '#default_value' => $office_policestation_comm,
                    '#prefix' => '<div id="comm_empps_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>'
                );
            } else {
                $form['factory_part_comm']['policestation_comm'] = array(
                    '#title' => '(viii) Police Station',
                    '#type' => 'select',
                    '#attributes' => array(
                        'class' => array(
                            ''
                        ),
                        'placeholder' => 'Police Station'
                    ),
                    '#options' => array(
                        '0' => t('Select Police Station')
                    ),
                    '#required' => TRUE,
                    '#prefix' => '<div id="comm_empps_replace"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>'
                );
            }
            
            if (!empty($pincode_v_comm)) {
                $form['factory_part_comm']['postoffice_comm'] = array(
                    '#title' => $factory_communication_check_data.'(ix) Post Office',
                    '#type' => 'select',
                    '#attributes' => array(
                        'class' => array(
                            ''
                        ),
                        'placeholder' => 'Post Office',
                        $factory_communication_ck => $factory_communication_ck
                    ),
                    '#required' => TRUE,
                    '#options' => common_custom_post_office_list_new($pincode_v_comm),
                    '#default_value' => $office_postoffice_comm,
                    '#prefix' => '<div id="comm_post_office_div"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>'
                );
            } else {
                $form['factory_part_comm']['postoffice_comm'] = array(
                    '#title' => '(ix) Post Office',
                    '#type' => 'select',
                    '#attributes' => array(
                        'class' => array(
                            ''
                        ),
                        'placeholder' => 'Post Office'
                    ),
                    '#options' => array(
                        '0' => t('Select Post Office')
                    ),
                    '#required' => TRUE,
                    '#prefix' => '<div id="comm_post_office_div"><div class="col-md-4"><label class="select label-block">',
                    '#suffix' => '</label></div></div>'
                );
                
            }
            
            $form['factory_part_comm']['addrline_comm'] = array(
                '#title' => $factory_communication_check_data.'(x) Address',
                '#rows' => 3,
                '#type' => 'textarea',
                '#required' => TRUE,
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Address Line',
                    $factory_communication_ck => $factory_communication_ck
                ),
                '#default_value' => $office_addrline_comm,
                '#prefix' => '<div id="comm_addressline_div"><div class="col-md-12"><label class="textarea label-block">',
                '#suffix' => '</label></div></div>',
                );
            
                $form['factory_part_comm']['thirdRowEnd'] = array(
                    '#prefix' => '',
                    //'#suffix' => '</div>'
                );
        }
    
	/********** Communication Address - End **********/
	
	 
    $form['factory_catagory'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('F. Factory Identification according to WBPCB'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	$form['factory_part_info']['wbpcb_checked_data'] = array(
        '#type' 			=> 'hidden',
        '#value' 			=> $plant_installed_field_value,
		'#attributes' 		=> array('class' => array('')),
    );	

    if(empty($wbpcb_id_ck)){
    
	    $form['factory_catagory']['application_period_section_f'] = array(
		    '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4"><label class="input label-block">',
            '#suffix' 			=> '</label></div></div>',
            '#title' 			=> t('(i). Application Period'),
            '#type' 			=> 'select',
            '#options' 			=> $lists,
            '#required' 		=> TRUE,
            '#attributes' 		=> array('class' => array( ''),),  
        );
    }

    $form['factory_catagory']['markup_start'] = array(
	     	 '#prefix' =>'<div class="row">'	
	);
		
	$form['factory_catagory']['factory_pollution_type'] 	= array(
				'#prefix' 			=> '<div class="col-md-4 col-xs-12"><div id="pollution_type_id"><label class="select label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t($plant_installed_check_data.'(i). Categories of wbpcb'),
				'#type' 			=> 'select',
				'#options' 			=>  get_category_wbpcb(),
				'#required'			=> TRUE,
				'#default_value'	=> 	$wbpcb_category_name,
				'#attributes'		=> 	array('class'	=> array(''),
														$wbpcb_id_ck=>$wbpcb_id_ck,
											),
				'#ajax'				=>  array(
												'effect' 		=> 'fade',			
												'callback'		=> 'get_pollution_ajax_load',
												'progress'		=>	array(
												'type'			=>'throbber',
												'message'		=>t('loading'),
											),
										),
			
			);	
		
		$form['factory_catagory']['doc_file'] = array(
			   '#prefix' 		=> '<div id="edit-doc-file-ajax-wrapper">',
			   '#suffix' 		=> '</div>'	,
			   
	);
	$form['factory_catagory']['view_doc_file'] = array(
			   '#prefix' 		=> '<div id="view_doc_file_id">',
			   '#suffix' 		=> '</div>'	,
			   
	);
	  $form['factory_catagory']['reference_no_approval_arrangments'] = array(
				'#prefix' 			=> '<div id="reference_no_approval_id">',
				'#suffix' 			=> '</div>',
				
	  );
	  $form['factory_catagory']['date_approval_arrangments'] = array(
				'#prefix' 			=> '<div id="reference_date_approval_id">',
				'#suffix' 			=> '</div>',
				
	  );
	 
	$value_pollution_type  =   isset($form_state['values']['factory_pollution_type']) ? $form_state['values']['factory_pollution_type'] : $wbpcb_category_name;
	if($value_pollution_type == 4){
		if(!empty($wbpcb_intimation_letter)){
			$file_url = file_create_url(get_uploaded_document_url($wbpcb_intimation_letter));
			//echo $file_url;die();
			$form['factory_catagory']['view_doc_file'] = array(
                		'#markup' => l(t('view'),$file_url, array('html' => TRUE,))
   				 );
		}
	if(empty($wbpcb_id_ck)){

	$form['factory_catagory']['doc_file'] = array(
					'#type' 				 => 'managed_file',
					'#title'				 => $plant_installed_check_data.'(ii). letter of intimation :-',
					'#upload_validators' 	 => array('file_validate_extensions' => array('pdf'), 'file_validate_size' => array(50*1024*1024)),
					'#upload_location' 		 => 'public://upload/pollution_doc/',
					'#process' 				 => array('import_my_file_element_process'),
					'#attributes' 			 => array('id' => '','autocomplete' => 'off','class'=>array('form-control')),
					'#prefix' 				 => '<div id="edit-doc-file-ajax-wrapper" class="col-md-4 col-xs-12">',
			  		'#suffix' 				 => '</div>',
					'#required' 			 => TRUE
            );
        }
	 $form['factory_catagory']['reference_no_approval_arrangments'] = array(
				'#prefix' 			=> '<div id="reference_no_approval_id">',
				'#suffix' 			=> '</div>',
				
	  );
	  $form['factory_catagory']['date_approval_arrangments'] = array(
				'#prefix' 			=> '<div id="reference_date_approval_id">',
				'#suffix' 			=> '</div>',
				
	  );
	}
		
	 if($value_pollution_type == '1' || $value_pollution_type == '2' || $value_pollution_type == '3'){
		$form['factory_catagory']['reference_no_approval_arrangments'] = array(
				'#prefix' 			=> '<div id="reference_no_approval_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title'			=> $plant_installed_check_data.'(ii). Reference number of approval of arrangments',
				'#type' 			=> 'textfield',
				'#required'			=> TRUE,
				'#default_value'	=> 	$wbpcb_reference_no,
				'#description'		=> t('<font color="#FF0000">(N.B.:- If any, made fo disposal of trade waste and effluents.)</font>'),
				'#attributes'		=> 	array('class'	=> array(''),
														$wbpcb_reference_id_ck=>$wbpcb_reference_id_ck,
											),
			);	
		$form['factory_catagory']['date_approval_arrangments'] = array(
				'#prefix' 			=> '<div id="reference_date_approval_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t($plant_installed_check_data.'(iii). Date of approval of arrangments'),
			
				'#attributes' 		=> array('class'=>array('datepicker_cls'), $wbpcb_reference_date_ck=>$wbpcb_reference_date_ck,),
				'#type' 			=> 'textfield',
				'#required'			=> TRUE,
				'#default_value'	=> 	$wbpcb_ref_date,
				'#description'		=> t('<font color="#FF0000">(N.B.:- If any, made fo disposal of trade waste and effluents.)</font>'),
			);
			$form['factory_catagory']['doc_file'] = array(
			   '#prefix' 		=> '<div id="edit-doc-file-ajax-wrapper">',
			   '#suffix' 		=> '</div>'	
	  );
	  $form['factory_catagory']['view_doc_file'] = array(
			   '#prefix' 		=> '<div id="view_doc_file_id">',
			   '#suffix' 		=> '</div>'	,
			   
	);
	}	
			
	$form['factory_catagory']['markup_start1'] = array(
	     '#suffix' =>'</div>'	
	);






//////////////////////////////////ADD UP HERE////////////////

$form['back_link'] = array(
		'#prefix' => '<div class="row"><div class="col-md-1">',
		'#suffix' => '</div>',
		'#markup' => l(t('<i class="fa fa-angle-left" aria-hidden="true"></i> Back'), 'applicant/applicant-dasboard/', array('html' => TRUE,'attributes' => array('class' => array('btn btn-dark pull-left'))))
  	);
    if($application_status == 'I' || $application_status == 'B' || empty($application_status) || $application_status == 'In'){

        if(!empty($factor_name) || !empty($zone_name_ck) || !empty($telephone_no_ck)|| !empty($mobile_no_ck)|| !empty($fax_no_ck)|| !empty($email_no_ck) || !empty($headoffice_address_ck) || !empty($wbpcb_id_ck) || !empty($factory_communication_ck)){
            $form['submit'] = array(
                '#prefix' => '<div class="col-md-1">',
                '#suffix' => '</div>',
                '#attributes' => array('class' => array('btn btn-success')),
                '#type' => 'submit',
                '#value' => 'Save'
            );
        }


	if(!empty($application_id)){
	$form['preview_link'] = array(
		'#prefix' => '<div class="col-md-10">',
        '#suffix' => '</div>',
  	//'#markup' => l(t('Preview as PDF'), 'applicant/applicant-dasboard/', array('html' => TRUE,'attributes' => array('class' => array('btn btn-dark space-left') )))
		'#markup' => l('DRAFT COPY', 'regsection/preview-varse/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$get_fa_cafa['id']).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'Preview as PDF','class'=>array('btn btn-warning pull-right'))))
  		);
		}
	}else{
		
		$form['markup'] = array(
        '#suffix' => '</div></div>',
        '#type' => 'markup',
       
    );
	
	}
	if(empty($application_id)){
	$form['preview_link_blank'] = array(
		'#prefix' => '<div class="col-md-10">',
        '#suffix' => '</div>',
  	//'#markup' => l(t('Preview as PDF'), 'applicant/applicant-dasboard/', array('html' => TRUE,'attributes' => array('class' => array('btn btn-dark space-left') )))
		'#markup' => l('DRAFT COPY', 'regsection/preview-varse/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',1).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'Form as PDF','class'=>array('btn btn-warning pull-right'))))
  		);
	}
    return $form;
}

function get_pollution_ajax_load($form, $form_state){
	$commands 	= array();	
	$commands[] = ajax_command_replace('#reference_no_approval_id', drupal_render($form['factory_catagory']['reference_no_approval_arrangments']));
	$commands[] = ajax_command_replace('#reference_date_approval_id', drupal_render($form['factory_catagory']['date_approval_arrangments']));
	$commands[] = ajax_command_replace('#edit-doc-file-ajax-wrapper', drupal_render($form['factory_catagory']['doc_file']));	
	$commands[] = ajax_command_replace('#view_doc_file_id', drupal_render($form['factory_catagory']['view_doc_file']));	
	return array('#type' => 'ajax', '#commands' => $commands);	
}
function get_ajax_zone_name($form, $form_state){
    $commands   = array();
    $commands[] = ajax_command_replace('#cb', drupal_render($form['factory_part_a']['factory_zone_details']));
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}

function get_ajax_load($form, $form_state){
    $commands   = array();
    $commands[] = ajax_command_replace('#ld_edit_emp_state_replace', drupal_render($form['factory_part_a']['state']));
    $commands[] = ajax_command_replace('#ld_edit_emp_district_replace', drupal_render($form['factory_part_a']['district']));
    $commands[] = ajax_command_replace('#ld_empsubdv_replace', drupal_render($form['factory_part_a']['subdivision']));
	$commands[] = ajax_command_replace('#estate_type_replace', drupal_render($form['factory_part_a']['estate_type']));
    $commands[] = ajax_command_replace('#ld_emp_areatype_replace', drupal_render($form['factory_part_a']['areatype']));
    $commands[] = ajax_command_replace('#ld_empareatype_name_replace', drupal_render($form['factory_part_a']['block']));
    $commands[] = ajax_command_replace('#ld_emp_vill_ward_replace', drupal_render($form['factory_part_a']['panchayat']));
    $commands[] = ajax_command_replace('#ld_empps_replace', drupal_render($form['factory_part_a']['policestation']));
    $commands[] = ajax_command_replace('#ld_post_office_div', drupal_render($form['factory_part_a']['postoffice']));
	
	$commands[] = ajax_command_replace('#view_boundary', drupal_render($form['factory_part_a']['zone_boundary']));
    $commands[] = ajax_command_replace('#factory_zone_div', drupal_render($form['factory_part_a']['factory_zone_name']));
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}

function get_ajax_factory_address($form, &$form_state){
    $commands   = array();
	$commands[] = ajax_command_replace('#country_replace', drupal_render($form['factory_part_off']['country']));
    $commands[] = ajax_command_replace('#off_edit_emp_pincodeoff_replace', drupal_render($form['factory_part_off']['pincodeoff']));
    $commands[] = ajax_command_replace('#off_edit_emp_state_replace', drupal_render($form['factory_part_off']['state_off']));
    $commands[] = ajax_command_replace('#off_edit_emp_district_replace', drupal_render($form['factory_part_off']['district_off']));
    $commands[] = ajax_command_replace('#off_empsubdv_replace', drupal_render($form['factory_part_off']['subdivision_off']));
    $commands[] = ajax_command_replace('#off_emp_areatype_replace', drupal_render($form['factory_part_off']['areatype_off']));
    $commands[] = ajax_command_replace('#off_empareatype_name_replace', drupal_render($form['factory_part_off']['block_off']));
    $commands[] = ajax_command_replace('#off_emp_vill_ward_replace', drupal_render($form['factory_part_off']['panchayat_off']));
    $commands[] = ajax_command_replace('#off_empps_replace', drupal_render($form['factory_part_off']['policestation_off']));
    $commands[] = ajax_command_replace('#off_post_office_div', drupal_render($form['factory_part_off']['postoffice_off']));
    $commands[] = ajax_command_replace('#off_addressline_div', drupal_render($form['factory_part_off']['addrline_off']));
	$commands[] = ajax_command_replace('#other_country_address_id', drupal_render($form['factory_part_off']['other_country_address']));
	return array('#type' => 'ajax','#commands' => $commands);
}

function get_ajax_load_off($form, $form_state){
    $commands   = array();
	$commands[] = ajax_command_replace('#country_replace', drupal_render($form['factory_part_off']['country']));
    $commands[] = ajax_command_replace('#off_edit_emp_state_replace', drupal_render($form['factory_part_off']['state_off']));
    $commands[] = ajax_command_replace('#off_edit_emp_district_replace', drupal_render($form['factory_part_off']['district_off']));
    $commands[] = ajax_command_replace('#off_empsubdv_replace', drupal_render($form['factory_part_off']['subdivision_off']));
    $commands[] = ajax_command_replace('#off_emp_areatype_replace', drupal_render($form['factory_part_off']['areatype_off']));
    $commands[] = ajax_command_replace('#off_empareatype_name_replace', drupal_render($form['factory_part_off']['block_off']));
    $commands[] = ajax_command_replace('#off_emp_vill_ward_replace', drupal_render($form['factory_part_off']['panchayat_off']));
    $commands[] = ajax_command_replace('#off_empps_replace', drupal_render($form['factory_part_off']['policestation_off']));
    $commands[] = ajax_command_replace('#off_post_office_div', drupal_render($form['factory_part_off']['postoffice_off']));
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}

function get_ajax_country_code($form, &$form_state){
	$commands   = array();
	 //$commands[] = ajax_command_replace('#country_replace', drupal_render($form['factory_part_off']['country']));
	$commands[] = ajax_command_replace('#other_country_address_id', drupal_render($form['factory_part_off']['other_country_address']));
	 
	$commands[] = ajax_command_replace('#off_edit_emp_pincodeoff_replace', drupal_render($form['factory_part_off']['pincodeoff']));
    $commands[] = ajax_command_replace('#off_edit_emp_state_replace', drupal_render($form['factory_part_off']['state_off']));
    $commands[] = ajax_command_replace('#off_edit_emp_district_replace', drupal_render($form['factory_part_off']['district_off']));
    $commands[] = ajax_command_replace('#off_empsubdv_replace', drupal_render($form['factory_part_off']['subdivision_off']));
    $commands[] = ajax_command_replace('#off_emp_areatype_replace', drupal_render($form['factory_part_off']['areatype_off']));
    $commands[] = ajax_command_replace('#off_empareatype_name_replace', drupal_render($form['factory_part_off']['block_off']));
    $commands[] = ajax_command_replace('#off_emp_vill_ward_replace', drupal_render($form['factory_part_off']['panchayat_off']));
    $commands[] = ajax_command_replace('#off_empps_replace', drupal_render($form['factory_part_off']['policestation_off']));
    $commands[] = ajax_command_replace('#off_post_office_div', drupal_render($form['factory_part_off']['postoffice_off']));
    $commands[] = ajax_command_replace('#off_addressline_div', drupal_render($form['factory_part_off']['addrline_off']));
	
	 return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}

function get_ajax_load_comm($form, $form_state){
    $commands   = array();
    $commands[] = ajax_command_replace('#comm_edit_emp_state_replace', drupal_render($form['factory_part_comm']['state_comm']));
    $commands[] = ajax_command_replace('#comm_edit_emp_district_replace', drupal_render($form['factory_part_comm']['district_comm']));
    $commands[] = ajax_command_replace('#comm_empsubdv_replace', drupal_render($form['factory_part_comm']['subdivision_comm']));
    $commands[] = ajax_command_replace('#comm_emp_areatype_replace', drupal_render($form['factory_part_comm']['areatype_comm']));
    $commands[] = ajax_command_replace('#comm_empareatype_name_replace', drupal_render($form['factory_part_comm']['block_comm']));
    $commands[] = ajax_command_replace('#comm_emp_vill_ward_replace', drupal_render($form['factory_part_comm']['panchayat_comm']));
    $commands[] = ajax_command_replace('#comm_empps_replace', drupal_render($form['factory_part_comm']['policestation_comm']));
    $commands[] = ajax_command_replace('#comm_post_office_div', drupal_render($form['factory_part_comm']['postoffice_comm']));
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}
function get_ajax_comm_same_address($form, &$form_state){
    $commands   = array();
    $commands[] = ajax_command_replace('#comm_edit_emp_pincodecomm_replace', drupal_render($form['factory_part_comm']['pincodecomm']));
    $commands[] = ajax_command_replace('#comm_edit_emp_state_replace', drupal_render($form['factory_part_comm']['state_comm']));
    $commands[] = ajax_command_replace('#comm_edit_emp_district_replace', drupal_render($form['factory_part_comm']['district_comm']));
    $commands[] = ajax_command_replace('#comm_empsubdv_replace', drupal_render($form['factory_part_comm']['subdivision_comm']));
    $commands[] = ajax_command_replace('#comm_emp_areatype_replace', drupal_render($form['factory_part_comm']['areatype_comm']));
    $commands[] = ajax_command_replace('#comm_empareatype_name_replace', drupal_render($form['factory_part_comm']['block_comm']));
    $commands[] = ajax_command_replace('#comm_emp_vill_ward_replace', drupal_render($form['factory_part_comm']['panchayat_comm']));
    $commands[] = ajax_command_replace('#comm_empps_replace', drupal_render($form['factory_part_comm']['policestation_comm']));
    $commands[] = ajax_command_replace('#comm_post_office_div', drupal_render($form['factory_part_comm']['postoffice_comm']));
    $commands[] = ajax_command_replace('#comm_addressline_div', drupal_render($form['factory_part_comm']['addrline_comm']));
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}

function get_ajax_owner_type($form, $form_state){
    $commands   = array();
	
	$commands[] = ajax_command_replace('#previous_ownership_div', drupal_render($form['factory_part_info']['previous_ownership']));
	$commands[] = ajax_command_replace('#conversation_ownership_div', drupal_render($form['factory_part_info']['conversation_ownership']));
	$commands[] = ajax_command_replace('#change_date_div', drupal_render($form['factory_part_info']['change_date']));
	//$commands[] = ajax_command_replace('#ownership_type_div', drupal_render($form['factory_part_info']['ownership_type']));
	$commands[] = ajax_command_replace('#previous_name_div', drupal_render($form['factory_part_info']['previous_name']));
	$commands[] = ajax_command_replace('#add_details_div', drupal_render($form['factory_part_info']['add_details']));
	$commands[] = ajax_command_replace('#addr_same_div', drupal_render($form['factory_part_info']['addr_same']));
	$commands[] = ajax_command_replace('#conversation_name_div', drupal_render($form['factory_part_info']['conversation_name']));
	
	$commands[] = ajax_command_replace('#cin_no_id', drupal_render($form['factory_part_info']['cin_no']));
    return array( '#type' => 'ajax', '#commands' => $commands);
}

function get_ajax_load_premises($form, $form_state){
    $commands   = array();
	$commands[] = ajax_command_replace('#passport_premises_div', drupal_render($form['factory_part_premises']['passport_premises']));
	$commands[] = ajax_command_replace('#passport_issue_premises_div', drupal_render($form['factory_part_premises']['passport_issue_date']));
	
	$commands[] = ajax_command_replace('#aadhar_number_id', drupal_render($form['factory_part_premises']['aadhar_number']));
	$commands[] = ajax_command_replace('#passport_exp_premises_div', drupal_render($form['factory_part_premises']['passport_exp_date']));
	$commands[] = ajax_command_replace('#owner_country_address_id', drupal_render($form['factory_part_premises']['owner_country_address']));
	
	$commands[] = ajax_command_replace('#pincode_premises_id', drupal_render($form['factory_part_premises']['pincode_premises']));
	$commands[] = ajax_command_replace('#state_premises_owner_id', drupal_render($form['factory_part_premises']['state_premises_owner']));
	$commands[] = ajax_command_replace('#district_premises_owner_id', drupal_render($form['factory_part_premises']['district_premises_owner']));
	$commands[] = ajax_command_replace('#subdivision_premises_owner_id', drupal_render($form['factory_part_premises']['subdivision_premises_owner']));
    $commands[] = ajax_command_replace('#areatype_premises_owner_id', drupal_render($form['factory_part_premises']['areatype_premises_owner']));
    $commands[] = ajax_command_replace('#block_premises_owner_id', drupal_render($form['factory_part_premises']['block_premises_owner']));
	$commands[] = ajax_command_replace('#panchayat_premises_owner_id', drupal_render($form['factory_part_premises']['panchayat_premises_owner']));
    $commands[] = ajax_command_replace('#policestation_premises_owner_id', drupal_render($form['factory_part_premises']['policestation_premises_owner']));
    $commands[] = ajax_command_replace('#postoffice_premises_owner_id', drupal_render($form['factory_part_premises']['postoffice_premises_owner']));
	$commands[] = ajax_command_replace('#addrline_premises_owner_id', drupal_render($form['factory_part_off']['addrline_premises_owner']));
	
	$commands[] = ajax_command_replace('#pincodepremises_id', drupal_render($form['factory_part_premises']['pincodepremises']));
    $commands[] = ajax_command_replace('#premises_edit_emp_state_replace', drupal_render($form['factory_part_premises']['state_premises']));
    $commands[] = ajax_command_replace('#premises_edit_emp_district_replace', drupal_render($form['factory_part_premises']['district_premises']));
    $commands[] = ajax_command_replace('#premises_empsubdv_replace', drupal_render($form['factory_part_premises']['subdivision_premises']));
    $commands[] = ajax_command_replace('#premises_emp_areatype_replace', drupal_render($form['factory_part_premises']['areatype_premises']));
    $commands[] = ajax_command_replace('#premises_empareatype_name_replace', drupal_render($form['factory_part_premises']['block_premises']));
    $commands[] = ajax_command_replace('#premises_emp_vill_ward_replace', drupal_render($form['factory_part_premises']['panchayat_premises']));
    $commands[] = ajax_command_replace('#premises_empps_replace', drupal_render($form['factory_part_premises']['policestation_premises']));
    $commands[] = ajax_command_replace('#premises_post_office_div', drupal_render($form['factory_part_premises']['postoffice_premises']));
	$commands[] = ajax_command_replace('#addrline_premises_div', drupal_render($form['factory_part_premises']['addrline_premises']));
	$commands[] = ajax_command_replace('#mouza_premises_div', drupal_render($form['factory_part_premises']['mouza_name']));
	$commands[] = ajax_command_replace('#jl_no_premises_div', drupal_render($form['factory_part_premises']['jl_no']));
	
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}

function add_pre_details($form, &$form_state){
	
	global $user;
	
	$val   								= 	$form_state['values'];
	$factory_type						= 	encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$service_id							= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$application_id						= 	encryption_decryption_fun('decrypt',$val['applicationid_hidden']);	
	$reference_no						= 	encryption_decryption_fun('decrypt',$val['ref_number_hidden']);
	//die($factory_type.'--'.$service_id.'--'.$application_id.'--'.$reference_no);
	$factory_name_hidden				= 	encryption_decryption_fun('decrypt',$val['factory_name_hidden']);
	$owership_type_hidden				= 	encryption_decryption_fun('decrypt',$val['owership_type_hidden']);
	$created_date_hidden				= 	encryption_decryption_fun('decrypt',$val['created_date_hidden']);
	$is_previous						= 	$val['is_previous'];
	$service_year						= 	$val['application_period_section_a'];
	$change_date						= 	date('Y-m-d',strtotime($val['change_date']));
	$conversation_ownership				= 	$val['conversation_ownership'];
	$previous_ownership					= 	$val['previous_ownership'];
	$pervious_factory_name				= 	$val['previous_name'];
	$conversation_name_name				= 	$val['conversation_name'];
	$same_as_pre_details				= 	$val['addr_same'];
	$current_date 						=   date('Y-m-d');
	$transfer_fees 						= 	1000;
	 if($is_previous == 'pv'){
		 $description_conversation			=	"Public to Private (Vise versa)";
	 }if($is_previous == 'par_firm'){
		 $description_conversation			=	"Partnership to Proprietorship Firm (Vise versa)";
	 }if($is_previous == 'pv_par'){
		 $description_conversation			=	"Partnership to Private (Vise versa)";
	 }if($is_previous == 'par_ltd'){
		 $description_conversation			=	"Partnership to Public (Vise versa)";
	 }if($is_previous == 'pv_pro'){
		 $description_conversation			=	"Proprietorship to Private (Vise versa)";
	 }if($is_previous == 'ltd_pro'){
		 $description_conversation			=	"Proprietorship to Public (Vise versa)";
	 }if($is_previous == 'amal'){
		 $description_conversation			=	"Amalgamation";
	 }if($is_previous == 'name'){
		 $description_conversation			=	"Name change (ex:- XYZ ltd to YZX ltd)";
		 $transfer_fees = 0;
	 }
	
	$year_id							= 	fetch_year_details_withid($service_year);
	
	$previos_name =array(
						'pervious_factory_name' 		      => $pervious_factory_name,
						'change_date'						  => $change_date ,
						'conversation_ownership_type'		  => $conversation_ownership,
						'service_id' 		             	  => $service_id,
						'application_id'              		  => $application_id,
						'name_application_status' 	  		  => 'In',
						'factory_type'				     	  => $factory_type,
						'created_by'				          => $user->uid,
						'service_year'				          => $year_id['calculate_year'],
						'application_reference_no'			  => $reference_no,
						'name_active_inactive'				  => $year_id['is_active_year'],
						'is_change'							  => 1,
						'transfer_fees'						  =>  $transfer_fees,
						'valid_time_period'					  =>  $year_id['valid_time_period'], 
						'is_previous'						  =>  'No',
						'valid_year'						  =>  $year_id['calculate_end_year'],	
						'starting_year'						  =>  $year_id['calculate_starting_year'],
						'calculate_year_id'					  =>  $service_year,
						'created_date'						  =>  date('Y-m-d'),
						'conversation_name'					  => $conversation_name_name,
						'previous_ownership'				  =>  $previous_ownership,
						'type_of_conversation'				  =>  $is_previous,
						'description_conversation'			 => $description_conversation,
						
				
			);
			//print_r($previos_name);die;
			$id = db_insert('fa_factory_previous_name')->fields($previos_name)->execute();
	
	if($id){
		$commands[] = ajax_command_replace('#view_previous_details_id', '<div id="view_previous_details_id" class="col-lg-12 col-md-12 col-sm-12 col-xs-12">'.view_previous_details($application_id,$reference_no,$factory_type,$service_id).'</div>');
		
		return array('#type' => 'ajax', '#commands' => $commands);
	}
}

function view_previous_details($application_id,$reference_number,$factory_type_id,$service_id){
	$output = '';
	$sl = 0;

	$pre_view	=	get_previous_details_view($application_id,$reference_number,$factory_type_id,$service_id);
	//print_r($pre_view);die($pre_view[0]->id);
	$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/transfer-delete-year-renew/'.encryption_decryption_fun('encrypt', $pre_view[0]->id).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt', $reference_number).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$service_id),array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
	
	if(!empty($pre_view)){
	//print_r($pre_view);die();
		$header = array(
		array('data'=> 'Sl. No.','width'=> '8%'),
		array('data'=> 'Application Period','width'=> '20%'),
		array('data'=> 'Change Date','width'=> '20%'),
		array('data'=> 'Previous Name','width'=> '34%'),
		array('data'=> 'Conversion Name','width'=> '34%'),
		array('data'=> 'Transfer Fees','width'=> '20%'),
		array('data'=> 'Action','width'=> '10%'),
		
	);
	foreach($pre_view as $view){
		$sl= $sl+1;	
		if($view->conversation_ownership_type=="pv"){
			$conversation_ownership_type = "Pvt Ltd Company";
		}if($view->conversation_ownership_type=="ltd"){
			$conversation_ownership_type = "Ltd Company";
		}if($view->conversation_ownership_type=="par_firm"){
			$conversation_ownership_type = "Partnership Firm";
		}if($view->conversation_ownership_type=="pro_firm"){
			$conversation_ownership_type = "Proprietorship Firm";
			
		}if($view->previous_ownership=="pv"){
			$previous_ownership_type = "Pvt Ltd Company";
		}if($view->previous_ownership=="ltd"){
			$previous_ownership_type = "Ltd Company";
		}if($view->previous_ownership=="par_firm"){
			$previous_ownership_type = "Partnership Firm";
		}if($view->previous_ownership=="pro_firm"){
			$previous_ownership_type = "Proprietorship Firm";
		}
		$change_date =  date('dS M Y', strtotime($view->change_date));
		
		$rows [] = array(  
			array('data' => $sl), 	
			array('data' => t($view->service_year)),
			array('data' =>	$change_date),
			array('data' => t($view->pervious_factory_name)),
			array('data' => t($view->conversation_name)),
			array('data' => t($view->transfer_fees)),
			array('data' => $delLink),	
		);
		
	}
	$output = theme_table(
	array(
		  'header' 		=> $header,
		  'rows' 		=> $rows,
		  'attributes' 	=> array('id'=>'table_div_replace', 'class' => array('table', 'no-margin', 'custom-table-view-dashboard')),
		  'sticky' 		=> true,
		  'caption' 	=> '',
		  'colgroups' 	=> array(),
		  'empty' 		=> t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
	  
	return $output;	
	}
}

function delete_transfer_data($id,$application_id,$reference_no,$factory_type,$service_id){
	
	drupal_add_library('system', 'drupal.ajax');

	$app_id= encryption_decryption_fun('decrypt',$application_id);
	$ref_id= encryption_decryption_fun('decrypt',$reference_no);
	$fac_id= encryption_decryption_fun('decrypt',$factory_type);
    $ser_id= encryption_decryption_fun('decrypt',$service_id);
    
   // die($id.'---'.$app_id.'--'.$ref_id.'--'.$fac_id.'--'.$ser_id);
    
	if (trim(encryption_decryption_fun('decrypt', $id)) != 0) {
		$query 	= db_delete('fa_factory_previous_name');
		$query	->condition('id', trim(encryption_decryption_fun('decrypt', $id)),'=');
		$query	->execute();
	}
	
	$commands 	= array();
	$commands[] = ajax_command_replace('#view_previous_details_id', '<div id="view_previous_details_id" class="col-lg-12 col-md-12 col-sm-12 col-xs-12">'.view_previous_details($app_id,$ref_id,$fac_id,$ser_id).'</div>');
	$page = array('#type' => 'ajax', '#commands' => $commands);
	ajax_deliver($page);
	//return array('#type' => 'ajax','#commands' => $commands);
			
	}
function transfer_delcaration_renewal_submit($form, &$form_state) {
	global $user;
    $userid 			= $user->uid;
	$val   				= 	$form_state['values'];
	//print_r($val);
	$application_id 	= 	encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$factorytype_id 	= 	encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$service_id 		= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$reference_no		=  	encryption_decryption_fun('decrypt',$val['ref_number_hidden']);
	
	$get_fa_cafa 		= get_fa_cafa($application_id);
	$reference_no		= $get_fa_cafa['reference_number'];
	
	if($application_status=='B'){
		$status ='B';
		$date = $get_fa_cafa['created_date'];
	}
	else{
		$status ='In';
		$date = date('Y-m-d h:i:s');
	}	
	
	$reference_no_approval_arrangments	= $val['reference_no_approval_arrangments'];
	$date_approval_arrangments			= $val['date_approval_arrangments'];
	$factory_pollution_type				= $val['factory_pollution_type'];
	if($factory_pollution_type== 4){
		$docmunt_white_category 		= file_load($val['doc_file']);
		if($docmunt_white_category != "" ){
			$docmunt_white_category->status = FILE_STATUS_PERMANENT;
			file_save($docmunt_white_category);
			$fid					=	$docmunt_white_category->fid;
			$upload_application 	= array(
										'filename'	=> $docmunt_white_category->filename,
										'file_uri'	=> $docmunt_white_category->uri,
										'created_by'=> $docmunt_white_category->uid,
										//'id'		=> $fid,
										);
									$file_manage_id = db_insert('fa_file_managed_custom')->fields($upload_application)->execute();
			}
  	} 
	
    $addr_same	= $form_state['values']['addr_same'];
	
    if (!empty($val['addr_same']) && ($val['addr_same'] == 1)) {
        $pincodeoff        = $val['pincode'];
        $state_off         = $val['state'];
        $district_off      = $val['district'];
        $subdivision_off   = $val['subdivision'];
        $areatype_off      = $val['areatype'];
        $block_off         = $val['block'];
        $panchayat_off     = $val['panchayat'];
        $policestation_off = $val['policestation'];
        $postoffice_off    = $val['postoffice'];
        $addrline_off      = $val['addrline'];
    }else{
        $pincodeoff        = $val['pincodeoff'];
        $state_off         = $val['state_off'];
        $district_off      = $val['district_off'];
        $subdivision_off   = $val['subdivision_off'];
        $areatype_off      = $val['areatype_off'];
        $block_off         = $val['block_off'];
        $panchayat_off     = $val['panchayat_off'];
        $policestation_off = $val['policestation_off'];
        $postoffice_off    = $val['postoffice_off'];
        $addrline_off      = $val['addrline_off'];
    }
	$addr_same_comm        = $form_state['values']['addr_same_comm'];
    
    if (!empty($val['addr_same_comm']) && ($val['addr_same_comm'] == 2)) {
        
		//die($val['addr_same_comm']);
		$pincodecomm        = $val['pincode'];
        $state_comm         = $val['state'];
        $district_comm      = $val['district'];
        $subdivision_comm   = $val['subdivision'];
        $areatype_comm      = $val['areatype'];
        $block_comm         = $val['block'];
        $panchayat_comm     = $val['panchayat'];
        $policestation_comm = $val['policestation'];
        $postoffice_comm    = $val['postoffice'];
        $addrline_comm      = $val['addrline'];
    
	}	elseif (!empty($val['addr_same_comm']) && ($val['addr_same_comm'] == 3)) {

     
		
		$pincodecomm        = !empty($val['pincodeoff']) ? $val['pincodeoff'] : $pincodeoff;
		$state_comm         = !empty($val['state_off']) ? $val['state_off'] : $state_off;
		$district_comm      = !empty($val['district_off']) ? $val['district_off'] : $district_off;
		$subdivision_comm   = !empty($val['subdivision_off']) ? $val['subdivision_off'] : $subdivision_off;
		$areatype_comm      = !empty($val['areatype_off']) ? $val['areatype_off'] : $areatype_off;
		$block_comm         = !empty($val['block_off']) ? $val['block_off'] : $block_off;
		$panchayat_comm     = !empty($val['panchayat_off']) ? $val['panchayat_off'] : $panchayat_off;
		$policestation_comm = !empty($val['policestation_off']) ? $val['policestation_off'] : $policestation_off;
		$postoffice_comm    = !empty($val['postoffice_off']) ? $val['postoffice_off'] : $postoffice_off;
		$addrline_comm      = !empty($val['addrline_off']) ? $val['addrline_off'] : $addrline_off;

    //die($val['addr_same_comm']);
	}  elseif (!empty($val['addr_same_comm']) && ($val['addr_same_comm'] == 1)) {
		//die($val['addr_same_comm']);
		$pincodecomm        = $val['pincodecomm'];
        $state_comm         = $val['state_comm'];
        $district_comm      = $val['district_comm'];
        $subdivision_comm   = $val['subdivision_comm'];
        $areatype_comm      = $val['areatype_comm'];
        $block_comm         = $val['block_comm'];
        $panchayat_comm     = $val['panchayat_comm'];
        $policestation_comm = $val['policestation_comm'];
        $postoffice_comm    = $val['postoffice_comm'];
        $addrline_comm      = $val['addrline_comm'];
    
	}
	
    if($val['factory_ownershiptype']=='name') {
	
        $cafa_Info = array(
            'factory_name' 			=> $val['factory_name'],
            'factory_previous_name' => $val['factory_previous_name'],
            'nearest_landmark' 		=> $val['nearest_landmark'],
            'factory_zone' 			=> $val['factory_zone'],
            'gstin_no' 				=> $val['gstin_no'],
            'udyog_aadhaar' 		=> $val['udyog_aadhaar'],
            'enargy_no' 			=> $val['enargy_no'],
            'cin_no' 				=> !empty($val['cin_no'])? $val['cin_no']: NULL,
            'trade_license_no'		=> $val['trade_license_no'],
            
            'pincode' 				=> $val['pincode'],
            'state' 				=> $val['state'],
            'district' 				=> $val['district'],
            'subdivision' 			=> $val['subdivision'],
            'areatype' 				=> $val['areatype'],
            'block' 				=> $val['block'],
            'panchayat' 			=> $val['panchayat'],
            'policestation' 		=> $val['policestation'],
            'postoffice' 			=> $val['postoffice'],
            'addrline' 				=> $val['addrline'],
            
            
            'reg_adress_same_factory' 	=> $addr_same,
            
            'pincodeoff' 			=> $pincodeoff,
            'state_off' 			=> $state_off,
            'district_off' 			=> $district_off,
            'subdivision_off' 		=> $subdivision_off,
            'areatype_off' 			=> $areatype_off,
            'block_off' 			=> $block_off,
            'panchayat_off' 		=> $panchayat_off,
            'policestation_off' 	=> $policestation_off,
            'postoffice_off' 		=> $postoffice_off,
            'addrline_off' 			=> $addrline_off,
            
            'addrline_off_other'	=> $val['addrline_off_other'],
            
            'comm_telephone'   	    => $val['comm_telephone'],
            'comm_mobile'     	    => $val['comm_mobile'],
            'comm_fax'     	        => $val['comm_fax'],
            'comm_email'     	    => $val['comm_email'],
            'comm_alt_mobile'		=> $val['comm_alt_mobile'],
            
            
            'factory_pan' 			    => $val['factory_pan'],
            'owner_name' 				=> $val['owner_fname'],
            'owner_mname'				=>$val['owner_mname'],
            'owner_lname'				=>$val['owner_lname'],
            'pincodepremises' 			=> $val['pincodepremises'],
            'state_premises' 			=> $val['state_premises'],
            'district_premises' 		=> $val['district_premises'],
            'subdivision_premises' 		=> $val['subdivision_premises'],
            'areatype_premises' 		=> $val['areatype_premises'],
            'block_premises' 			=> $val['block_premises'],
            'panchayat_premises' 		=> $val['panchayat_premises'],
            'policestation_premises' 	=> $val['policestation_premises'],
            'postoffice_premises' 		=> $val['postoffice_premises'],
            'addrline_premises'		 	=> $val['owner_country_address'],
            'mouza_name'		 		=> $val['mouza_name'],
            'jl_no'		 				=> $val['jl_no'],
            'country_code'				=> $val['country'],
            'country_premises'			=> $val['country_premises'],
            'factory_country_address'	=> $val['other_country_address'],
            'service_id' 				=> encryption_decryption_fun('decrypt', $val['serviceid_hidden']),
            'factory_typeid' 			=> encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']),
            'created_by' 				=> $userid,
            'created_date' 				=> $date,
            
     
            'reg_adress_same_factory_comm'=> $addr_same_comm,
            // communication address - if same as factory address or register office address //
            'pincodecomm' 				=> $pincodecomm,
            'state_comm' 				=> $state_comm,
            'district_comm' 			=> $district_comm,
            'subdivision_comm' 			=> $subdivision_comm,
            'areatype_comm' 			=> $areatype_comm,
            'block_comm' 				=> $block_comm,
            'panchayat_comm' 			=> $panchayat_comm,
            'policestation_comm' 		=> $policestation_comm,
            'postoffice_comm' 			=> $postoffice_comm,
            'addrline_comm' 			=> $addrline_comm,
              
              
            'reference_number'  			=> $reference_no,
          
            'application_status'  			=> $status,
             
            
            //'date_of_amenability'			=> $date_of_amenability,
            //'period_for_application'		=> $period_for_application,
            'factory_zone'					=> $val['factory_zone'],
            'wbpcb_intimation_letter' 		=> $file_manage_id,
            'wbpcb_reference_no' 			=> $reference_no_approval_arrangments,
            'wbpcb_ref_date' 				=> $date_approval_arrangments,
            'wbpcb_category_name'			=> $factory_pollution_type,
            
            'estate_type'					=> $val['estate_type'],
           
            );
        }else{
    
            $cafa_Info = array(
                'factory_name' 			=> $val['factory_name'],
                'factory_previous_name' => $val['factory_previous_name'],
                'nearest_landmark' 		=> $val['nearest_landmark'],
                'factory_zone' 			=> $val['factory_zone'],
                'gstin_no' 				=> $val['gstin_no'],
                'udyog_aadhaar' 		=> $val['udyog_aadhaar'],
                'enargy_no' 			=> $val['enargy_no'],
                'cin_no' 				=> !empty($val['cin_no'])? $val['cin_no']: NULL,
                'trade_license_no'		=> $val['trade_license_no'],
                
                'pincode' 				=> $val['pincode'],
                'state' 				=> $val['state'],
                'district' 				=> $val['district'],
                'subdivision' 			=> $val['subdivision'],
                'areatype' 				=> $val['areatype'],
                'block' 				=> $val['block'],
                'panchayat' 			=> $val['panchayat'],
                'policestation' 		=> $val['policestation'],
                'postoffice' 			=> $val['postoffice'],
                'addrline' 				=> $val['addrline'],
                
                
                'reg_adress_same_factory' 	=> $addr_same,
                
                'pincodeoff' 			=> $pincodeoff,
                'state_off' 			=> $state_off,
                'district_off' 			=> $district_off,
                'subdivision_off' 		=> $subdivision_off,
                'areatype_off' 			=> $areatype_off,
                'block_off' 			=> $block_off,
                'panchayat_off' 		=> $panchayat_off,
                'policestation_off' 	=> $policestation_off,
                'postoffice_off' 		=> $postoffice_off,
                'addrline_off' 			=> $addrline_off,
                
                'addrline_off_other'	=> $val['addrline_off_other'],
                
                'comm_telephone'   	    => $val['comm_telephone'],
                'comm_mobile'     	    => $val['comm_mobile'],
                'comm_fax'     	        => $val['comm_fax'],
                'comm_email'     	    => $val['comm_email'],
                'comm_alt_mobile'		=> $val['comm_alt_mobile'],
                
                
                'factory_pan' 			    => $val['factory_pan'],
                'owner_name' 				=> $val['owner_fname'],
                'owner_mname'				=>$val['owner_mname'],
                'owner_lname'				=>$val['owner_lname'],
                'pincodepremises' 			=> $val['pincodepremises'],
                'state_premises' 			=> $val['state_premises'],
                'district_premises' 		=> $val['district_premises'],
                'subdivision_premises' 		=> $val['subdivision_premises'],
                'areatype_premises' 		=> $val['areatype_premises'],
                'block_premises' 			=> $val['block_premises'],
                'panchayat_premises' 		=> $val['panchayat_premises'],
                'policestation_premises' 	=> $val['policestation_premises'],
                'postoffice_premises' 		=> $val['postoffice_premises'],
                'addrline_premises'		 	=> $val['owner_country_address'],
                'mouza_name'		 		=> $val['mouza_name'],
                'jl_no'		 				=> $val['jl_no'],
                'country_code'				=> $val['country'],
                'country_premises'			=> $val['country_premises'],
                'factory_country_address'	=> $val['other_country_address'],
                'service_id' 				=> encryption_decryption_fun('decrypt', $val['serviceid_hidden']),
                'factory_typeid' 			=> encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']),
                'created_by' 				=> $userid,
                'created_date' 				=> $date,
                
         
                'reg_adress_same_factory_comm'=> $addr_same_comm,
                // communication address - if same as factory address or register office address //
                'pincodecomm' 				=> $pincodecomm,
                'state_comm' 				=> $state_comm,
                'district_comm' 			=> $district_comm,
                'subdivision_comm' 			=> $subdivision_comm,
                'areatype_comm' 			=> $areatype_comm,
                'block_comm' 				=> $block_comm,
                'panchayat_comm' 			=> $panchayat_comm,
                'policestation_comm' 		=> $policestation_comm,
                'postoffice_comm' 			=> $postoffice_comm,
                'addrline_comm' 			=> $addrline_comm,
                  
                  
                'reference_number'  			=> $reference_no,
               
                'application_status'  			=> $status,
                  
                
              
                'factory_zone'					=> $val['factory_zone'],
                'factory_owershiptype'			=> $val['factory_ownershiptype'],
                'wbpcb_intimation_letter' 		=> $file_manage_id,
                'wbpcb_reference_no' 			=> $reference_no_approval_arrangments,
                'wbpcb_ref_date' 				=> $date_approval_arrangments,
                'wbpcb_category_name'			=> $factory_pollution_type,
                
                'estate_type'					=> $val['estate_type'],
              
                );
        }
	if(!empty($cafa_Info)) {
		$queryabc = db_update('fa_cafa');
        $queryabc->fields($cafa_Info);
        $queryabc->condition('id', $application_id, '=');
        $queryabc->execute();
		
		if(!empty($val['application_period_section_a'])){
			$year_data = array(
				'year_id'		=> $val['application_period_section_a'],
				'application_id'=> $application_id,
				'change_field'	=> $val['factory_checked_data'],
			);
			$is_factor = get_period_id($application_id,$val['factory_checked_data'],$val['application_period_section_a']);
			if(empty($is_factor)){
				db_insert('fa_amendment_mapping')->fields($year_data)->execute();
			}else{
				$querya = db_update('fa_amendment_mapping');
				$querya->fields($year_data);
				$querya->condition('id', $is_factor, '=');
				$querya->execute();
			}
		}
		
		if(!empty($val['application_period_section_b'])){
			$year_data1 = array(
				'year_id'		=> $val['application_period_section_b'],
				'application_id'=> $application_id,
				'change_field'	=> $val['location_checked_data'],
			);
			$is_location = get_period_id($application_id,$val['location_checked_data'],$val['application_period_section_b']);
			if(empty($is_location)){
				db_insert('fa_amendment_mapping')->fields($year_data1)->execute();
			}else{
				$queryb = db_update('fa_amendment_mapping');
				$queryb->fields($year_data1);
				$queryb->condition('id', $is_location, '=');
				$queryb->execute();	
			}
		}
		
		if(!empty($val['application_period_section_c'])){
			$year_data2 = array(
				'year_id'		=> $val['application_period_section_c'],
				'application_id'=> $application_id,
				'change_field'	=> $val['register_checked_data'],
			);
			$is_register = get_period_id($application_id,$val['register_checked_data'],$val['application_period_section_c']);
			if(empty($is_register)){
				db_insert('fa_amendment_mapping')->fields($year_data2)->execute();
			}else{
				$queryc = db_update('fa_amendment_mapping');
				$queryc->fields($year_data2);
				$queryc->condition('id', $is_register, '=');
				$queryc->execute();	
			}
		}
		
		if(!empty($val['application_period_section_d'])){
			$year_data3 = array(
				'year_id'		=> $val['application_period_section_d'],
				'application_id'=> $application_id,
				'change_field'	=> $val['communication_checked_data'],
			);
			$is_communication = get_period_id($application_id,$val['communication_checked_data'],$val['application_period_section_d']);
			if(empty($is_communication)){
				db_insert('fa_amendment_mapping')->fields($year_data3)->execute();
			}else{
				$queryd = db_update('fa_amendment_mapping');
				$queryd->fields($year_data3);
				$queryd->condition('id', $is_communication, '=');
				$queryd->execute();	
			}
		}
		
		if(!empty($val['application_period_section_e'])){
			$year_data4 = array(
				'year_id'		=> $val['application_period_section_e'],
				'application_id'=> $application_id,
				'change_field'	=> $val['owner_checked_data'],
			);
			$is_premises = get_period_id($application_id,$val['owner_checked_data'],$val['application_period_section_e']);
			if(empty($is_premises)){
				db_insert('fa_amendment_mapping')->fields($year_data4)->execute();
			}else{
				$querye = db_update('fa_amendment_mapping');
				$querye->fields($year_data4);
				$querye->condition('id', $is_premises, '=');
				$querye->execute();	
			}
		}
		
		if(!empty($val['application_period_section_f'])){
			$year_data5 = array(
				'year_id'		=> $val['application_period_section_f'],
				'application_id'=> $application_id,
				'change_field'	=> $val['wbpcb_checked_data'],
			);
			$is_wbpcb = get_period_id($application_id,$val['wbpcb_checked_data'],$val['application_period_section_f']);
			if(empty($is_wbpcb)){
				db_insert('fa_amendment_mapping')->fields($year_data5)->execute();
			}else{
				$queryf = db_update('fa_amendment_mapping');
				$queryf->fields($year_data5);
				$queryf->condition('id', $is_wbpcb, '=');
				$queryf->execute();	
			}
		}
		
		drupal_set_message('Factory Information has been saved successfully.');
		
    	}
		
	$form_state['rebuild'] = true;
}

