<?php
//drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/sky-forms.css');
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function caf_form_extension_parta($form, &$form_state, $serviceid, $factory_typeid, $applicationid)
{ 

    global $base_root, $base_path;
    $form            		= array();
    $service_id      	= encryption_decryption_fun('decrypt', $serviceid);
    $factory_type_id 	= encryption_decryption_fun('decrypt', $factory_typeid);
	$application_id  	= encryption_decryption_fun('decrypt', $applicationid);
	
    $form['serviceid_hidden']     = array(
        '#type' => 'hidden',
        '#default_value' => $serviceid
    );
    $form['factorytypeid_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $factory_typeid
    );
	$form['applicationid_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $applicationid
    );

    $factory_name = $factory_zone = $factory_previous_name = $factory_location = $factory_pincode = $factory_state = $factory_district = $factory_subdivision = $factory_areatype = $factory_block = $factory_panchayat = $factory_policestation = $factory_postoffice = $factory_addrline = $office_pincode =  $office_state_off = $office_district_off = $office_subdivision_off = $office_areatype_off = $office_block_off = $office_panchayat_off = $office_policestation_off = $office_postoffice_off = $office_addrline_off = $comm_telephone = $comm_mobile = $comm_fax = $comm_email = $factory_pan = $ownership_type = $occupier_type = $occupier_nationality =  $occupier_aadhaar = $occupier_passport =  $occupier_name =  $occupier_mobile =  $occupier_email_id = $occupier_age =  $occupier_gurdian_name =  $occupier_fax_no =  $occupier_telephone = $occupier_pincodeoprmntadr = $occupier_state_oprmntadr = $occupier_district_oprmntadr = $occupier_subdivision_oprmntadr = $occupier_areatype_oprmntadr = $occupier_block_oprmntadr = $occupier_panchayat_oprmntadr = $occupier_policestation_oprmntadr = $occupier_postoffice_oprmntadr = $occupier_addrline_oprmntadr = $occupier_pincodeoprsntadr = $occupier_state_oprsntadr = $occupier_district_oprsntadr = $occupier_subdivision_oprsntadr = $occupier_areatype_oprsntadr = $occupier_block_oprsntadr = $occupier_panchayat_oprsntadr = $occupier_policestation_oprsntadr = $occupier_postoffice_oprsntadr = $occupier_addrline_oprsntadr = $owner_name = $owner_pincodepremises = $owner_state_premises = $owner_district_premises = $owner_subdivision_premises = $owner_areatype_premises = $owner_block_premises = $owner_panchayat_premises = $owner_policestation_premises = $owner_postoffice_premises = $owner_addrline_premises = $application_status = $plan_approve_status = $reg_adress_same_factory = $occupier_present_address_same = $classification_no = $factory_registrstion_no = $registration_date = $factory_license_no = $license_date = $plant_installed = $railway_station = '';      

    $extract_data 				=  explode('/', $application_id); 
		  
    if (!empty($application_id) && count($extract_data) == 1) {
        $get_fa_cafa           = get_fa_cafa($application_id);
        //print_r($get_fa_cafa);die();
        $factory_name          		= $get_fa_cafa['factory_name'];
		$factory_zone          		= $get_fa_cafa['factory_zone'];
        $factory_previous_name 		= $get_fa_cafa['factory_previous_name'];
        $factory_location      		= $get_fa_cafa['factory_location'];
        $factory_pincode       		= $get_fa_cafa['pincode'];
        $factory_state         		= $get_fa_cafa['state'];
        $factory_district      		= $get_fa_cafa['district'];
        $factory_subdivision   		= $get_fa_cafa['subdivision'];
        $factory_areatype      		= $get_fa_cafa['areatype'];
        $factory_block        		= $get_fa_cafa['block'];
        $factory_panchayat     	    = $get_fa_cafa['panchayat'];
        $factory_policestation 		= $get_fa_cafa['policestation'];
        $factory_postoffice    		= $get_fa_cafa['postoffice'];
        $factory_addrline      		= $get_fa_cafa['addrline'];
        
        $office_pincode           	= $get_fa_cafa['pincodeoff'];
        $office_state_off         	= $get_fa_cafa['state_off'];
        $office_district_off      	= $get_fa_cafa['district_off'];
        $office_subdivision_off   	= $get_fa_cafa['subdivision_off'];
        $office_areatype_off      	= $get_fa_cafa['areatype_off'];
        $office_block_off        	= $get_fa_cafa['block_off'];
        $office_panchayat_off     	= $get_fa_cafa['panchayat_off'];
        $office_policestation_off 	= $get_fa_cafa['policestation_off'];
        $office_postoffice_off    	= $get_fa_cafa['postoffice_off'];
        $office_addrline_off      	= $get_fa_cafa['addrline_off'];
        
		$comm_telephone     	    = $get_fa_cafa['comm_telephone'];
		$comm_mobile     	        = $get_fa_cafa['comm_mobile'];
		$comm_fax     	            = $get_fa_cafa['comm_fax'];
		$comm_email     	        = $get_fa_cafa['comm_email'];
        
        $factory_pan         		= $get_fa_cafa['factory_pan'];
        $ownership_type				= $get_fa_cafa['factory_owershiptype'];
	    $occupier_type 		        = $get_fa_cafa['occupier_type'];
		$occupier_nationality 		= $get_fa_cafa['occupier_nationality'];
        $occupier_aadhaar     		= $get_fa_cafa['occupier_aadhaar'];
        $occupier_passport    		= $get_fa_cafa['occupier_passport'];
        $occupier_name        		= $get_fa_cafa['occupier_name'];
        $occupier_mobile      		= $get_fa_cafa['occupier_mobile'];
        $occupier_email_id    		= $get_fa_cafa['occupier_email_id'];
        $occupier_age           	= $get_fa_cafa['occupier_age'];
        $occupier_gurdian_name  	= $get_fa_cafa['occupier_gurdian_name'];
        $occupier_fax_no        	= $get_fa_cafa['occupier_fax_no'];
		$occupier_telephone     	= $get_fa_cafa['occupier_telephone'];
        
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
        
        $owner_name                   	  = $get_fa_cafa['owner_name'];
        $owner_pincodepremises       	  = $get_fa_cafa['pincodepremises'];
        $owner_state_premises         	  = $get_fa_cafa['state_premises'];
        $owner_district_premises      	  = $get_fa_cafa['district_premises'];
        $owner_subdivision_premises   	  = $get_fa_cafa['subdivision_premises'];
        $owner_areatype_premises      	  = $get_fa_cafa['areatype_premises'];
        $owner_block_premises         	  = $get_fa_cafa['block_premises'];
        $owner_panchayat_premises         = $get_fa_cafa['panchayat_premises'];
        $owner_policestation_premises 	  = $get_fa_cafa['policestation_premises'];
        $owner_postoffice_premises        = $get_fa_cafa['postoffice_premises'];
        $owner_addrline_premises          = $get_fa_cafa['addrline_premises'];
        
        //$classification_no 				  = $get_fa_cafa['classification_no'];
		//$factory_registrstion_no		  = $get_fa_cafa['factory_registrstion_no'];
		//$registration_date				  = $get_fa_cafa['registration_date'];
		//$factory_license_no				  = $get_fa_cafa['factory_license_no'];
		


 	$classification_no       = !empty($get_fa_cafa['classification_no']) ? $get_fa_cafa['classification_no'] : $get_fa_cafa['backlog_classification_no'];	
	$factory_registrstion_no = !empty($get_fa_cafa['factory_registrstion_no']) ? $get_fa_cafa['factory_registrstion_no'] : $get_fa_cafa['backlog_registration_no'];	
	$factory_license_no      = !empty($get_fa_cafa['factory_license_no']) ? $get_fa_cafa['factory_license_no'] : $get_fa_cafa['backlog_license_number'];	
	$registration_date       = !empty($get_fa_cafa['registration_date']) ? $get_fa_cafa['registration_date'] : $get_fa_cafa['backlog_registration_date'];	
	$license_date		     = !empty($get_fa_cafa['license_date']) ? $get_fa_cafa['license_date'] : $get_fa_cafa['backlog_license_date'];


		$backlog_plan_approval_no         = $get_fa_cafa['backlog_plan_approval_no'];
		$backlog_plan_approval_date 	  = $get_fa_cafa['backlog_plan_approval_date'];

		$reg_adress_same_factory          = $get_fa_cafa['reg_adress_same_factory'];
        //$communication_adress_same_factory    = $get_fa_cafa['communication_adress_same_factory'];
        $occupier_present_address_same    = $get_fa_cafa['occupier_present_address_same'];
		$plan_approve_status    		  = $get_fa_cafa['plan_approve_status'];
		$plant_installed    		      = $get_fa_cafa['plant_installed'];
		$railway_station    		      = $get_fa_cafa['railway_station'];
		
		$form['backlog_plan_approval_no_hidden'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> encryption_decryption_fun('encrypt', $backlog_plan_approval_no)
		);
		$form['backlog_plan_approval_date_hidden'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> encryption_decryption_fun('encrypt', $backlog_plan_approval_date)
		);
	}
	
	$form['plan_approve_status_hidden'] = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> encryption_decryption_fun('encrypt', $plan_approve_status)
    );

    /********** Factory checking data **********/
	
	if($plan_approve_status == 'ABk') {
	
	$reference_number = $get_fa_cafa['reference_number'];
	$checked = get_verified_field($application_id, $reference_number, $plan_approve_status);
	
	$verify_details      = ($checked['verify_details'])? $checked['verify_details'] : ''; 
	
	$remark_field = explode(',', $checked['verify_details']);
			foreach ($remark_field as $fieldname){
				
				if($fieldname == 'factory_name'){ $factory_name_ck = "disabled";}
				if($fieldname == 'factory_location'){ $factory_location_ck = "disabled";}
				if($fieldname == 'factory_headoffice'){ $factory_headoffice_ck = "disabled"; $factory_headoffice_check_ck = "readonly";}
				if($fieldname == 'factory_pan'){ $factory_pan_ck = "disabled";}
				if($fieldname == 'occupier_name'){ $occupier_name_ck = "disabled";}
				if($fieldname == 'occupier_age'){ $occupier_age_ck = "disabled";}
				if($fieldname == 'occupier_gurdian_name'){ $occupier_gurdian_name_ck = "disabled";}
				if($fieldname == 'occupier_telephone'){ $occupier_telephone_ck = "disabled";}
				if($fieldname == 'occupier_fax_no'){ $occupier_fax_no_ck = "disabled";}
				if($fieldname == 'occupier_mobile'){ $occupier_mobile_ck = "disabled";}
				if($fieldname == 'occupier_email_id'){ $occupier_email_id_ck = "disabled";}
				if($fieldname == 'occupier_type'){ $occupier_type_ck = "disabled";}
				if($fieldname == 'occupier_nationality'){ $occupier_nationality_ck = "disabled";}
				if($fieldname == 'occupier_present_address'){ $occupier_present_address_ck = "disabled"; $occupier_present_address_check_ck = "readonly";}
				if($fieldname == 'owner_name'){ $owner_name_ck = "disabled";}
				if($fieldname == 'owner_address'){ $owner_address_ck = "disabled";}
				if($fieldname == 'worker_men'){ $worker_men_ck = "disabled";}
				if($fieldname == 'worker_women'){ $worker_women_ck = "disabled";}
				if($fieldname == 'adolescents_male'){ $adolescents_male_ck = "disabled";}
				if($fieldname == 'adolescents_female'){ $adolescents_female_ck = "disabled";}
				if($fieldname == 'children_male'){ $children_male_ck = "disabled";}
				if($fieldname == 'children_female'){ $children_female_ck = "disabled";}
			}

		if(in_array("factory_name", $remark_field)) { $factory_name_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $factory_name_check_data = '<i class="fa fa-close text-red verified"></i>'; }
		
		if(in_array("factory_location", $remark_field)) { $factory_location_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $factory_location_check_data = '<i class="fa fa-close text-red verified"></i>'; }
		
		if(in_array("factory_headoffice", $remark_field)) { $factory_headoffice_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $factory_headoffice_check_data = '<i class="fa fa-close text-red verified"></i>'; }
		
		if(in_array("factory_pan", $remark_field)) { $factory_pan_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $factory_pan_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("occupier_name", $remark_field)) { $occupier_name_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $occupier_name_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("occupier_age", $remark_field)) { $occupier_age_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $occupier_age_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("occupier_gurdian_name", $remark_field)) { $occupier_gurdian_name_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $occupier_gurdian_name_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("occupier_telephone", $remark_field)) { $occupier_telephone_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $occupier_telephone_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("occupier_fax_no", $remark_field)) { $occupier_fax_no_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $occupier_fax_no_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("occupier_mobile", $remark_field)) { $occupier_mobile_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $occupier_mobile_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("occupier_email_id", $remark_field)) { $occupier_email_id_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $occupier_email_id_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("occupier_type", $remark_field)) { $occupier_type_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $occupier_type_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("occupier_nationality", $remark_field)) { $occupier_nationality_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $occupier_nationality_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("occupier_present_address", $remark_field)) { $occupier_present_address_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $occupier_present_address_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("owner_name", $remark_field)) { $owner_name_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $owner_name_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("owner_address", $remark_field)) { $owner_address_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $owner_address_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("worker_men", $remark_field)) { $worker_men_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $worker_men_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("worker_women", $remark_field)) { $worker_women_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $worker_women_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("adolescents_male", $remark_field)) { $adolescents_male_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $adolescents_male_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("adolescents_female", $remark_field)) { $adolescents_female_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $adolescents_female_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("children_male", $remark_field)) { $children_male_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $children_male_check_data = '<i class="fa fa-close text-red verified"></i>'; }
		
        if(in_array("children_female", $remark_field)) { $children_female_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $children_female_check_data = '<i class="fa fa-close text-red verified"></i>'; }
	 }	
	 
	/********** Factory Information - Start **********/
    
    $form['header']            = array(
        '#markup' => t('<div class="content"><h3>General Information</h3>')
    );
    $form['factory_part_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('A. Factory Information'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
    
    $form['factory_part_info']['factory_name'] = array(
        '#prefix' => '<div class="row"><div class="col-md-6"><label class="input label-block">',
        '#suffix' => '</label></div>',
        '#title' => t($factory_name_check_data.'(i) Name of the factory'),
        '#type' => 'textfield',
        '#default_value' => $factory_name,
		'#attributes' => array('class' => array('charField'),$factory_name_ck => $factory_name_ck )
    );
	
	$form['factory_part_info']['factory_previous_name'] = array(
        '#prefix' => '<div class="col-md-6"><label class="input label-block">',
        '#suffix' => '</label></div></div>',
        '#title' => t($factory_name_check_data.'(ii) Previous Name of the factory (if different from the present name)'),
        '#type' => 'textfield',
        '#default_value' => $factory_previous_name,
		'#attributes' => array('class' => array('charField'),$factory_name_ck => $factory_name_ck )
    );
	
	/********** PAN of Business Establishment / Factory / Company - Start **********/
	
    $form['factory_part_info']['factory_pan'] = array(
        '#prefix' => '<div class="row"><div class="col-md-6 col-xs-12"><label class="input label-block">',
        '#suffix' => '</label></div></div>',
        '#title' => t($factory_pan_check_data.'(iii) PAN of the Business Establishment / Factory / Company'),
        '#type' => 'textfield',
        '#default_value' => $factory_pan,
		'#attributes' => array('class' => array('charNoField'),$factory_pan_ck => $factory_pan_ck ),
		'#description' => t('<font color="#FF0000">(N.B:- Under the Income Tax Act, 1961)</font>'),
        '#required' => TRUE,
		'#maxlength' => 10,
    );

    /********** Factory Information - End **********/
	
	/********** Location of the factory - Start **********/
	
	$form['factory_part_a'] = array(
        '#type'			=> 'fieldset',
        '#title' 		=> t('B. Location of the factory'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	
	// 
	
	$factoryzone = get_factory_zone();
	$default_zone 	= array(""=>"- Select Zone -");

	foreach($factoryzone as $val){
		$factzonefinal[$val->zone_id] = $val->zone_name;
		$factzonefinal1 = ($default_zone+$factzonefinal);
	}
	
	$form['factory_part_a']['factory_zone'] = array(
			'#prefix' => '<div class="row"><div class="col-md-4 col-xs-12"><label class="select label-block">',
			'#suffix' => '</label></div>',
			'#title' => t($factory_location_check_data.'(i) Factory Zone'),
			'#options' => $factzonefinal1,
			'#type' => 'select',
			'#default_value'        => !empty($factory_zone) ? $factory_zone :'',
			'#required' => TRUE,
			'#attributes'		=> array('class' => array( ''),$factory_location_ck => $factory_location_ck),
			'#ajax' => array(
				'event' => 'change',
				'effect' => 'fade',
				'callback' => 'get_ajax_boundary',
				'progress' => array('type' => 'throbber','message' => t('loading')))
		);
		
	$form['factory_part_a']['railway_station'] = array(
        '#prefix' => '<div class="col-md-4"><label class="input label-block">',
        '#suffix' => '</label></div>',
        '#title' => t($factory_location_check_data.'(ii) Nearest Railway Station'),
        '#type' => 'textfield',
        '#default_value' => $railway_station,
		'#attributes' => array('class' => array('charField'),$factory_location_ck => $factory_location_ck )
    );
	
	$form['factory_part_a']['zone_boundary']  = array(
		'#prefix' => '<div id="view_boundary">',
		'#suffix' => '</div>'
	);
	$value_boundary = isset($form_state['values']['factory_zone']) ? $form_state['values']['factory_zone'] : $factory_zone;	
		
	if(!empty($value_boundary))
	{
		$query = db_select('fa_zone', 'fz')
		->fields('fz', array('zone_details'))
		->condition('fz.zone_id', trim($value_boundary), '=');
        $result = $query->execute();
		$final_boudary = $result->fetchAssoc();
		
		$form['factory_part_a']['zone_boundary']  = array(
            '#prefix' => '<div id="view_boundary" style="color:#319A31;"><div class="col-md-12 col-xs-12">',
            '#suffix' => '</div></div>',
            '#markup' => t('<b>'.$final_boudary['zone_details'].'</b>'),
			'#type' => 'markup',
        );
	}	
		
	$form['factory_part_a']['firstRowStart'] = array(
        '#prefix' 		=> '',
        '#suffix' 		=> '</div>'
    );	
    
	// ADREESS PART 	
    $form['factory_part_a']['pincode']       = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-12"><label class="input label-block">',
        '#suffix' 			=> '</label></div>',
        '#attributes' 		=> array(
           'class' 			=> array(),
           'placeholder' 	=> 'Pincode',
		   $factory_location_ck => $factory_location_ck
        ),
        '#autocomplete_path' => 'pinautocomplete',
        '#id' 				 => 'pincode_autocomplete',
        '#maxlength' 		 => 6,
        '#title' 			 => t($factory_location_check_data.'(iii) Pincode'),
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
    $value_pincode                           = isset($form_state['values']['pincode']) ? $form_state['values']['pincode'] : $factory_pincode;
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
            '#title' => $factory_location_check_data.'(iv) State',
            '#type' => 'select',
            '#id' => 'state_name',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'State',
				$factory_location_ck => $factory_location_ck
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
            '#title' => '(iv) State',
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
            '#title' => $factory_location_check_data.'(v) District',
            '#type' => 'select',
            '#id' => 'district_name',
            '#disabled' => TRUE,
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'District',
				$factory_location_ck => $factory_location_ck
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
            '#title' => '(v) District',
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
    
    $form['factory_part_a']['firstRowEnd'] = array(
        '#prefix' => '',
        '#suffix' => '</div>'
    );
    
    $value_district = isset($form_state['values']['district']) ? $form_state['values']['district'] : $factory_district;
    
    $form['factory_part_a']['secondRowStart'] = array(
        '#prefix' => '<div class="row">',
        '#suffix' => ''
    );
    
    if (!empty($district_v) && !empty($state_v)) {
        
        $form['factory_part_a']['subdivision'] = array(
            '#title' => $factory_location_check_data.'(vi) Sub-Division',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Sub Division',
				$factory_location_ck => $factory_location_ck
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
            '#title' => '(vi) Sub-Division',
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
    
    if (!empty($value_district) && !empty($value_state) && !empty($value_subdivision)) {
        $form['factory_part_a']['areatype'] = array(
            '#title' => $factory_location_check_data.'(vii) Area Type',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Area Type',
				$factory_location_ck => $factory_location_ck
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
            '#title' => '(vii) Area Type',
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
            '#title' => $factory_location_check_data.'(viii) '. $areatype_name,
            '#type' => 'select',

            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'subdivision',
				$factory_location_ck => $factory_location_ck
            ),
            '#options' 		=> common_custom_user_block_list_new($value_subdivision, $value_areatype),
			'#required' => TRUE,
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
            '#title' => '(viii) Block / Municipality / Corporation / Notified Area / SEZ',
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
    
    $form['factory_part_a']['secondRowEnd'] = array(
        '#prefix' => '',
        '#suffix' => '</div>'
    );
    
    $form['factory_part_a']['thirdRowStart'] = array(
        '#prefix' => '<div class="row">',
        '#suffix' => ''
    );
    $value_block                             = isset($form_state['values']['block']) ? $form_state['values']['block'] : $factory_block;
    
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
            '#title' => $factory_location_check_data.'(ix) '.$area_name,
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'panchayat',
				$factory_location_ck => $factory_location_ck
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
            '#title' => '(ix) Gram Panchayat / Ward / Sector',
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
				$factory_location_ck => $factory_location_ck
            ),
            '#options' => common_custom_user_ps_list_new($value_district),
            '#required' => TRUE,
			'#default_value' => $factory_policestation,
            '#prefix' => '<div id="ld_empps_replace"><div class="col-md-4"><label class="select label-block">',
            '#suffix' => '</label></div></div>'
        );
    } else {
        $form['factory_part_a']['policestation'] = array(
            '#title' => '(x) Police Station',
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
            '#title' => $factory_location_check_data.'(xi) Post Office',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Post Office',
				$factory_location_ck => $factory_location_ck
            ),
            '#options' => common_custom_post_office_list_new($pincode_v),
            '#default_value' => $factory_postoffice,
			'#required' => TRUE,
            '#prefix' => '<div id="ld_post_office_div"><div class="col-md-4"><label class="select label-block">',
            '#suffix' => '</label></div></div>'
        );
    } else {
        $form['factory_part_a']['postoffice'] = array(
            '#title' => '(xi) Post Office',
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
    $form['factory_part_a']['addrline'] = array(
        '#title' => $factory_location_check_data.'(xii) Address',
        '#rows' => 3,
        '#type' => 'textarea',
		'#required' => TRUE,
        '#default_value' => $factory_addrline,
        '#attributes' => array(
            'class' => array(
                ''
            ),
            'placeholder' => 'Address Line',
			$factory_location_ck => $factory_location_ck
        ),
        '#prefix' => '<div class="col-md-12"><label class="textarea label-block">',
        '#suffix' => '</label></div>'
    );
    
    $form['factory_part_a']['thirdRowEnd'] = array(
        '#prefix' => '',
        '#suffix' => '</div>'
        
    );
    
    /********** Location of the factory - End **********/
	
	/********** Address of the Registered office / Head office - Start **********/
	
    $form['factory_part_off']              = array(
        '#type' => 'fieldset',
        '#title' => t('C. Address of the Registered office / Head office'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
    
	$form['factory_part_off']['firstRowStart'] = array(
        '#prefix' 			=> '<div class="row">',
        '#suffix' 			=> ''
    );

	$form['factory_part_off']['addr_same'] = array(
        '#type' => 'checkbox',
        '#id' => 'same_factory_addr',
        '#default_value' => $reg_adress_same_factory,
		'#attributes' => array('class' => array( ''),$factory_headoffice_check_ck => $factory_headoffice_check_ck ),
        '#ajax' => array(
            'event' => 'change',
            'effect' => 'fade',
            'callback' => 'get_ajax_factory_address',
            'progress' => array(
                'type' => 'throbber',
                'message' => t('loading')
            )
        ),
        '#title' => t('Same as Location of the factory'),
        '#prefix' => '<div class="col-md-12">',
        '#suffix' => '</div>'
    );
    
	$checkbox = isset($form_state['values']['addr_same']) ? $form_state['values']['addr_same'] : $reg_adress_same_factory;
    if ($checkbox == 1) {
        $form['factory_part_off']['pincodeoff']        = array(
            '#prefix' => '<div id="off_edit_emp_pincodeoff_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_off']['state_off']         = array(
            '#prefix' => '<div id="off_edit_emp_state_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_off']['district_off']      = array(

            '#prefix' => '<div id="off_edit_emp_district_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_off']['subdivision_off']   = array(
            '#prefix' => '<div id="off_empsubdv_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_off']['areatype_off']      = array(
            '#prefix' => '<div id="off_emp_areatype_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_off']['block_off']         = array(
            '#prefix' => '<div id="off_empareatype_name_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_off']['panchayat_off']     = array(
            '#prefix' => '<div id="off_emp_vill_ward_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_off']['policestation_off'] = array(
            '#prefix' => '<div id="off_empps_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_off']['postoffice_off']    = array(
            '#prefix' => '<div id="off_post_office_div">',
            '#suffix' => '</div>'
        );
        $form['factory_part_off']['addrline_off']      = array(
            '#prefix' => '<div id="off_addressline_div">',
            '#suffix' => '</div>'
        );
    }
    
    
    if ($checkbox == 0) {
        $form['factory_part_off']['pincodeoff'] = array(
            '#prefix' => '<div id="off_edit_emp_pincodeoff_replace"><div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div></div>',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Pincode',
				$factory_headoffice_ck => $factory_headoffice_ck
            ),
            '#autocomplete_path' => 'pinautocomplete',
            '#id' => 'pincode_autocomplete_off',
            '#maxlength' => 6,
            '#default_value' => $office_pincode,
            '#title' => t($factory_headoffice_check_data.'(i) Pincode'),
            '#required' => TRUE,
            '#type' => 'textfield',
            '#ajax' => array(
                //'event'         => 'change',
                'effect' => 'fade',
                'callback' => 'get_ajax_load_off',
                'progress' => array(
                    'type' => 'throbber',
                    'message' => t('loading')
                )
            )
        );
        $value_pincode_off                      = isset($form_state['values']['pincodeoff']) ? $form_state['values']['pincodeoff'] : $office_pincode;
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
                '#title' => $factory_headoffice_check_data.'(ii) State',
                '#type' => 'select',
                '#id' => 'state_name_off',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'State',
				    $factory_headoffice_ck => $factory_headoffice_ck
                ),
                '#disabled' => TRUE,
                '#options' => get_all_state($state_v_off),
                '#default_value' => !empty($state_v_off) ? $state_v_off : $office_state_off,
				'#required' => TRUE,
                '#prefix' => '<div id="off_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_off',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_off']['state_off'] = array(
                '#title' => '(ii) State',
                '#type' => 'select',
                '#id' => 'state_name_off',
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
                '#prefix' => '<div id="off_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_off',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        }
        
        $value_state_off = isset($form_state['values']['state_off']) ? $form_state['values']['state_off'] : $office_state_off;
        
        if (!empty($state_v_off)) {
            $form['factory_part_off']['district_off'] = array(
                '#title' => $factory_headoffice_check_data.'(iii) District',
                '#type' => 'select',
                '#id' => 'district_name_off',
                '#disabled' => TRUE,
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'District',
				    $factory_headoffice_ck => $factory_headoffice_ck
                ),
                '#options' => get_district_by_id($state_v_off),
                '#value' => !empty($district_v_off) ? $district_v_off : $office_district_off,
				'#required' => TRUE,
                '#prefix' => '<div id="off_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',

                    'callback' => 'get_ajax_load_off',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_off']['district_off'] = array(
                '#title' => '(iii) District',
                '#type' => 'select',
                '#id' => 'district_name_off',
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
                '#prefix' => '<div id="off_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        }
        
        $form['factory_part_off']['firstRowEnd'] = array(
            '#prefix' => '',
            '#suffix' => '</div>'
        );
        
        $value_district_off = isset($form_state['values']['district_off']) ? $form_state['values']['district_off'] : $office_district_off;
        
        $form['factory_part_off']['secondRowStart'] = array(
            '#prefix' => '<div class="row">',
            '#suffix' => ''
        );
        
        if (!empty($district_v_off) && !empty($state_v_off)) {
            
            $form['factory_part_off']['subdivision_off'] = array(
                '#title' => $factory_headoffice_check_data.'(iv) Sub-Division',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Sub Division',
				    $factory_headoffice_ck => $factory_headoffice_ck
                ),
                '#options' => common_custom_user_subdivisionlist_list_new($district_v_off),
				'#required' => TRUE,
                '#default_value' => $office_subdivision_off,
                '#prefix' => '<div id="off_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_off',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            
            $form['factory_part_off']['subdivision_off'] = array(
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
                '#prefix' => '<div id="off_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        }
        
        
        $value_subdivision_off = isset($form_state['values']['subdivision_off']) ? $form_state['values']['subdivision_off'] : $office_subdivision_off;
        
        if (!empty($value_district_off) && !empty($value_state_off) && !empty($value_subdivision_off)) {
            
            $form['factory_part_off']['areatype_off'] = array(
                '#title' => $factory_headoffice_check_data.'(v) Area Type',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Area Type',
				    $factory_headoffice_ck => $factory_headoffice_ck
                ),
                '#options' => common_custom_user_areatype_list_new($value_district_off, $value_subdivision_off),
				'#required' => TRUE,
                '#default_value' => $office_areatype_off,
                '#prefix' => '<div id="off_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_off',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_off']['areatype_off'] = array(
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
                '#prefix' => '<div id="off_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
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
                '#title' => $factory_headoffice_check_data.'(vi) '.$areatype_name_off,
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'subdivision',
				    $factory_headoffice_ck => $factory_headoffice_ck
                ),
                '#options' => common_custom_user_block_list_new($value_subdivision_off, $value_areatype_off),
				'#required' => TRUE,
                '#default_value' => $office_block_off,
                '#prefix' => '<div id="off_empareatype_name_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_off',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
            
            
        } else {
            $form['factory_part_off']['block_off'] = array(
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
                '#prefix' => '<div id="off_empareatype_name_replace"><div class="col-md-4"><label class="select label-block" title="Block / Municipality / Corporation / Notified Area / SEZ">',
                '#suffix' => '</label></div></div>'
            );
        }
        
        $form['factory_part_off']['secondRowEnd'] = array(
            '#prefix' => '',
            '#suffix' => '</div>'
        );
        
        $form['factory_part_off']['thirdRowStart'] = array(
            '#prefix' => '<div class="row">',
            '#suffix' => ''
        );
        $value_block_off                           = isset($form_state['values']['block_off']) ? $form_state['values']['block_off'] : $office_block_off;
        
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
                '#title' => $factory_headoffice_check_data.'(vii) '.$area_name_off,
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'panchayat',
				    $factory_headoffice_ck => $factory_headoffice_ck
                ),
                '#options' => common_custom_user_villward_list_new($value_block_off, $area_code_off),
				'#required' => TRUE,
                '#default_value' => $office_panchayat_off,
                '#prefix' => '<div id="off_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_off',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_off']['panchayat_off'] = array(
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
                '#prefix' => '<div id="off_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        }
        $value_panchayat_off = isset($form_state['values']['panchayat_off']) ? $form_state['values']['panchayat_off'] : $office_panchayat_off;
        
        if (!empty($value_district_off) && !empty($value_subdivision_off) && !empty($value_areatype_off) && !empty($value_block_off) && !empty($value_state_off) && !empty($value_panchayat_off)) {
            
            $form['factory_part_off']['policestation_off'] = array(
                '#title' => $factory_headoffice_check_data.'(viii) Police Station',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Police Station',
				    $factory_headoffice_ck => $factory_headoffice_ck
                ),
                '#options' => common_custom_user_ps_list_new($value_district_off),
				'#required' => TRUE,
                '#default_value' => $office_policestation_off,
                '#prefix' => '<div id="off_empps_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        } else {
            $form['factory_part_off']['policestation_off'] = array(
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
                '#prefix' => '<div id="off_empps_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        }
        
        if (!empty($pincode_v_off)) {
            $form['factory_part_off']['postoffice_off'] = array(
                '#title' => $factory_headoffice_check_data.'(ix) Post Office',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Post Office',
				    $factory_headoffice_ck => $factory_headoffice_ck
                ),
				'#required' => TRUE,
                '#options' => common_custom_post_office_list_new($pincode_v_off),
                '#default_value' => $office_postoffice_off,
                '#prefix' => '<div id="off_post_office_div"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        } else {
            $form['factory_part_off']['postoffice_off'] = array(
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
                '#prefix' => '<div id="off_post_office_div"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
            
        }
        
        $form['factory_part_off']['addrline_off'] = array(
            '#title' => $factory_headoffice_check_data.'(x) Address',
            '#rows' => 3,
            '#type' => 'textarea',
			'#required' => TRUE,
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Address Line',
				$factory_headoffice_ck => $factory_headoffice_ck
            ),
            '#default_value' => $office_addrline_off,
            '#prefix' => '<div id="off_addressline_div"><div class="col-md-12"><label class="textarea label-block">',
            '#suffix' => '</label></div></div>',
        );
        
        $form['factory_part_off']['thirdRowEnd'] = array(
            '#prefix' => '',
            //'#suffix' => '</div>'
        );
		
	}
	$form['factory_part_off']['fourthRowStart'] = array(
        '#prefix' 			=> '',
        '#suffix' 			=> '</div>'
     );
				
		$form['factory_part_off']['comm_telephone'] = array(
			'#prefix' => '<div class="row"><div class="col-md-3"><label class="input label-block">',
			'#suffix' => '</label></div>',
			'#title' => t($factory_headoffice_check_data.'(xi) Telephone No.'),
			'#type' => 'textfield',
			'#default_value' => $comm_telephone,
			'#attributes' => array('class' => array('NoField'),$factory_headoffice_ck => $factory_headoffice_ck ),
			'#maxlength' => 10,
		);
		
		$form['factory_part_off']['comm_mobile'] = array(
			'#prefix' => '<div class="col-md-3"><label class="input label-block">',
			'#suffix' => '</label></div>',
			'#title' => t($factory_headoffice_check_data.'(xii) Mobile No.'),
			'#type' => 'textfield',
			'#default_value' => $comm_mobile,
			'#attributes' => array('class' => array('NoField'),$factory_headoffice_ck => $factory_headoffice_ck ),
			'#maxlength' => 10,
		);
		$form['factory_part_off']['comm_fax'] = array(
			'#prefix' => '<div class="col-md-3"><label class="input label-block">',
			'#suffix' => '</label></div>',
			'#title' => t($factory_headoffice_check_data.'(xiii) Fax No.'),
			'#type' => 'textfield',
			'#default_value' => $comm_fax,
			'#attributes' => array('class' => array('NoField'),$factory_headoffice_ck => $factory_headoffice_ck )
		);
		
		$form['factory_part_off']['comm_email'] = array(
			'#prefix' => '<div class="col-md-3"><label class="input label-block">',
			'#suffix' => '</label></div></div>',
			'#title' => t($factory_headoffice_check_data.'(xiv) Email Id'),
			'#type' => 'textfield',
			'#default_value' => $comm_email,
			'#attributes' => array('class' => array('emailField'),$factory_headoffice_ck => $factory_headoffice_ck ),
			'#required' => TRUE,
    	);
		
		$form['factory_part_off']['addres_defination'] = array(
            '#type' 			=> 'markup',
            '#prefix' 			=> '<div class="row"><div class="col-md-12"><label class="input label-block">',
            '#suffix' 			=> '</label></div><div>',
            '#markup' 			=> t('<font color="#FF0000">(You must enter Telephone No. / Mobile)<br>(N.B:- This address will be treated as communication address as per Section 7 of Factories Act, 1948 )</font>')
        );
		
    /********** Address of the Registered office / Head office - End **********/
	
	/********** Details of Occupier - Start **********/
	
	    $form['factory_part_d']                         = array(
        '#type' => 'fieldset',
        '#title' => t('D. Details of Occupier'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
	
	$ownershiptype  = array(
		"0" => "Select",
        "pv" 			=> "Pvt Ltd Company",
        "ltd" 			=> "Ltd Company",
		"par_firm" 		=> "Partnership Firm",
		"pro_firm" 		=> "Proprietorship Firm",
		"govt" 			=> "Govt.",
		"psu" 			=> "PSU",
		"others" 		=> "Others",
    );
	
    $form['factory_part_d']['ownership_type'] = array(
        '#prefix' => '<div class="row"><div class="col-md-4 col-xs-12"><label class="select label-block">',
        '#suffix' => '</label></div>',
        '#title' => t($occupier_type_check_data.'(i) Type of Ownership'),
		'#attributes' => array('class' => array( ''),$occupier_type_ck => $occupier_type_ck ),
        '#options' => $ownershiptype,
        '#type' => 'select',
        '#default_value'        => !empty($ownership_type) ? $ownership_type :'',
        '#required' => TRUE,
		'#ajax' => array(
            'event' => 'change',
            'effect' => 'fade',
            'callback' => 'get_ajax_occupier_type',
            'progress' => array(
                'type' => 'throbber',
                'message' => t('loading')
            )
        )
    );
	
	$form['factory_part_d']['occupier_type'] = array(
		'#prefix' => '<div id="occupier_type_id">',
		'#suffix' => '</div>',
	);

	$value_ownership_type   = isset($form_state['values']['ownership_type']) ? $form_state['values']['ownership_type'] : $ownership_type;

	if($value_ownership_type == 'par_firm')
	{
		$form['factory_part_d']['occupier_type'] = array(
			'#prefix' => '<div id="occupier_type_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
			'#suffix' => '</label></div></div>',
			'#title' => t($occupier_type_check_data.'(ia) Occupier Type'),
			'#type' => 'textfield',
			'#value'        => 'Partner',
			'#attributes' 		=> array(
			   'readonly' => 'readonly'
			),
		);

	} elseif($value_ownership_type == 'pro_firm')
	{
		$form['factory_part_d']['occupier_type'] = array(
			'#prefix' => '<div id="occupier_type_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
			'#suffix' => '</label></div></div>',
			'#title' => t($occupier_type_check_data.'(ia) Occupier Type'),
			'#type' => 'textfield',
			'#value'        => 'Proprietor',
			'#attributes' 		=> array(
			   'readonly' => 'readonly'
			),
		);

	} elseif($value_ownership_type == 'govt' || $value_ownership_type == 'psu' || $value_ownership_type == 'others')
	{
		$form['factory_part_d']['occupier_type'] = array(
			'#prefix' => '<div id="occupier_type_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
			'#suffix' => '</label></div></div>',
			'#title' => t($occupier_type_check_data.'(ia) Occupier Type'),
			'#type' => 'textfield',
			'#value'        => 'Nominated',
			'#attributes' 		=> array(
			   'readonly' => 'readonly'
			),
		);

	}elseif($value_ownership_type == 'ltd' || $value_ownership_type == 'pv')
	{
		$form['factory_part_d']['occupier_type'] = array(
			'#prefix' => '<div id="occupier_type_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
			'#suffix' => '</label></div></div>',
			'#title' => t($occupier_type_check_data.'(ia) Occupier Type'),
			'#type' => 'textfield',
			'#value'        => 'Director',
			'#attributes' 		=> array(
			   'readonly' => 'readonly'
			),
		);
	}
		
	    $form['factory_part_d']['occupier_name']           = array(
            '#prefix' => '<div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div>',
            '#title' => t($occupier_name_check_data.'(ii) Name'),
            '#type' => 'textfield',
            '#default_value'  => !empty($occupier_name) ? $occupier_name :'',
			'#attributes' => array('class' => array('charField'),$occupier_name_ck => $occupier_name_ck ),
            '#required' => TRUE,
        );
		$form['factory_part_d']['occupier_age']    = array(
            '#prefix' => '<div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div>',
            '#title' => t($occupier_age_check_data.'(iii) Age'),
            '#type' => 'textfield',
            '#default_value' => !empty($occupier_age) ? $occupier_age :'',
			'#attributes' => array('class' => array('NoField'),$occupier_age_ck => $occupier_age_ck ),
			'#maxlength' => 2,
			'#required' => TRUE,
        );
        $form['factory_part_d']['occupier_gurdian_name']  = array(
            '#prefix' => '<div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div>',
            '#title' => t($occupier_gurdian_name_check_data.'(iv) Father\'s / Husband\'s name'),
            '#type' => 'textfield',
            '#default_value' => !empty($occupier_gurdian_name) ? $occupier_gurdian_name :'',
			'#attributes' => array('class' => array('charField'),$occupier_gurdian_name_ck => $occupier_gurdian_name_ck ),
			'#required' => TRUE,
        );
        $form['factory_part_d']['occupier_telephone']  = array(
            '#prefix' => '<div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div>',
            '#title' => t($occupier_telephone_check_data.'(v) Telephone Number'),
            '#type' => 'textfield',
            '#default_value' => !empty($occupier_telephone) ? $occupier_telephone :'',
			'#attributes' => array('class' => array('NoField'),$occupier_telephone_ck => $occupier_telephone_ck ),
			'#maxlength' => 10,
			'#required' => TRUE,
        );
        $form['factory_part_d']['occupier_mobile']         = array(
            '#prefix' => '<div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div>',
            '#title' => t($occupier_mobile_check_data.'(vi) Mobile Number'),
            '#type' => 'textfield',
            '#default_value'  => !empty($occupier_mobile) ? $occupier_mobile :'',
			'#attributes' => array('class' => array('NoField'),$occupier_mobile_ck => $occupier_mobile_ck ),
            '#required' => TRUE,
			'#maxlength' => 10,
        );
        $form['factory_part_d']['occupier_email_id']       = array(
            '#prefix' => '<div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div>',
            '#title' => t($occupier_email_id_check_data.'(vii) Email id'),
            '#type' => 'textfield',
            '#default_value'  => !empty($occupier_email_id) ? $occupier_email_id :'',
			'#attributes' => array('class' => array('emailField'),$occupier_email_id_ck => $occupier_email_id_ck ),
            '#required' => TRUE,
        );
		$form['factory_part_d']['occupier_fax_no']    = array(
            '#prefix' => '<div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div>',
            '#title' => t($occupier_fax_no_check_data.'(viii) Fax No.'),
            '#type' => 'textfield',
            '#default_value' => !empty($occupier_fax_no) ? $occupier_fax_no :'',
			'#attributes' => array('class' => array('NoField'),$occupier_fax_no_ck => $occupier_fax_no_ck )
        );	
		$form['factory_part_d']['firstRowEnd'] = array(
			'#prefix' => '',
			'#suffix' => '</div>'
		);

	/********** Details of Occupier - End **********/
	
	/********** Occupier Permanemt Address - Start **********/
    
    $form['factory_part_c']                         = array(
        '#type' => 'fieldset',
        '#title' => t('D i). Occupier Permanent Address'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
	
    $nationality_list     = array(
		"Indian" => "Indian",
        "Other" => "Other"
    );
    $form['factory_part_c']['occupier_nationality'] = array(
        '#prefix' => '<div class="row"><div class="col-md-4 col-xs-12"><label class="select label-block">',
        '#suffix' => '</label></div>',
        '#title' => t($occupier_nationality_check_data.'(i) Nationality'),
        '#options' => $nationality_list,
		'#attributes' => array('class' => array( ''),$occupier_nationality_ck => $occupier_nationality_ck ),
        '#type' => 'select',
        '#default_value'        => !empty($occupier_nationality) ? $occupier_nationality :'',
        '#required' => TRUE,
        '#ajax' => array(
            'event' => 'change',
            'effect' => 'fade',
            'callback' => 'get_ajax_nationality',
            'progress' => array(
                'type' => 'throbber',
                'message' => t('loading')
            )
        )
    );
    $form['factory_part_c']['occupier_aadhaar']     = array(
        '#prefix' => '<div id="ld_show_aadhaar">',
        '#suffix' => '</div>'
    );
	$form['factory_part_c']['occupier_passport']     = array(
        '#prefix' => '<div id="ld_show_passport">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['pincodeoprmntadr']        = array(
        '#prefix' => '<div id="pincodeoprmntadr_id">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['state_oprmntadr']       = array(
        '#prefix' => '<div id="oprmntadr_edit_emp_state_replace">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['district_oprmntadr']    = array(
        '#prefix' => '<div id="oprmntadr_edit_emp_district_replace">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['subdivision_oprmntadr'] = array(
        '#prefix' => '<div id="oprmntadr_empsubdv_replace">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['areatype_oprmntadr']    = array(
        '#prefix' => '<div id="oprmntadr_emp_areatype_replace">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['block_oprmntadr'] = array(
        '#prefix' => '<div id="oprmntadr_empareatype_name_replace">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['panchayat_oprmntadr']     = array(
        '#prefix' => '<div id="oprmntadr_emp_vill_ward_replace">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['policestation_oprmntadr'] = array(
        '#prefix' => '<div id="oprmntadr_empps_replace">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['postoffice_oprmntadr']    = array(
        '#prefix' => '<div id="oprmntadr_post_office_div">',
        '#suffix' => '</div>'
    );
    $form['factory_part_c']['addrline_oprmntadr']      = array(
        '#prefix' => '<div id="addrline_oprmntadr_div">',
        '#suffix' => '</div>'
    );
    $value_nationality   = isset($form_state['values']['occupier_nationality']) ? $form_state['values']['occupier_nationality'] : $occupier_nationality;

        $form['factory_part_c']['occupier_aadhaar']   = array(
            '#prefix' => '<div id="ld_show_aadhaar"><div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div></div>',
            '#title' => t($occupier_nationality_check_data.'(ii) Aadhaar Number'),
            '#type' => 'textfield',
            '#default_value' => !empty($occupier_aadhaar) ? $occupier_aadhaar :'',
			'#attributes' => array('class' => array('NoField'),$occupier_nationality_ck => $occupier_nationality_ck ),
			'#maxlength' => 12,
        );

        $form['factory_part_c']['addrline_oprmntadr'] = array(
            '#prefix' => '<div id = "addrline_oprmntadr_div"><div class="col-md-12 col-xs-12"><label class="textarea label-block">',
            '#suffix' => '</label></div></div>',
            '#title' => $occupier_nationality_check_data.'(xii) Address',
            '#rows' => 3,
            '#type' => 'textarea',
			'#required' => TRUE,
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Address Line',
				$occupier_nationality_ck => $occupier_nationality_ck
            ),
            '#default_value' => $occupier_addrline_oprmntadr
        );
        $form['factory_part_c']['pincodeoprmntadr']     = array(
            '#prefix' => '<div id="pincodeoprmntadr_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div></div>',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Pincode',
			    $occupier_nationality_ck => $occupier_nationality_ck
            ),
            '#autocomplete_path' => 'pinautocomplete',
            '#id' => 'pincode_autocomplete_oprmntadr',
            '#maxlength' => 6,
            '#title' => t($occupier_nationality_check_data.'(iii) Pincode'),
			'#default_value'  => !empty($occupier_pincodeoprmntadr) ? $occupier_pincodeoprmntadr    :'',
            '#required' => TRUE,
            '#type' => 'textfield',
            '#ajax' => array(
                //'event'         => 'change',
                'effect' => 'fade',
                'callback' => 'get_ajax_load_oprmntadr',
                'progress' => array(
                    'type' => 'throbber',
                    'message' => t('loading')
                )
            )
        );
        
        $value_pincode_oprmntadr = isset($form_state['values']['pincodeoprmntadr']) ? $form_state['values']['pincodeoprmntadr'] : $occupier_pincodeoprmntadr;
        if (!empty($value_pincode_oprmntadr)) {
            
            $query_oprmntadr = db_select('fa_all_india_pin_code', 'p')->fields('p', array(
                'districtname',
                'statename',
                'pincode',
                'district_code',
                'state_code',
                'po_name'
            ))->condition('p.pincode', trim($value_pincode_oprmntadr), '=');
            
            $result_oprmntadr = $query_oprmntadr->execute();
            if ($result_oprmntadr->rowcount() > 0) {
                $final_oprmntadr       = $result_oprmntadr->fetchAssoc();
                $pincode_v_oprmntadr   = $value_pincode_oprmntadr;
                $state_v_oprmntadr     = $final_oprmntadr['state_code'];
                $district_v_oprmntadr  = $final_oprmntadr['district_code'];
                $post_office_oprmntadr = $final_oprmntadr['po_name'];
            }
        }
        if (!empty($state_v_oprmntadr)) {
            $form['factory_part_c']['state_oprmntadr'] = array(
                '#title' => $occupier_nationality_check_data.'(iv) State',
                '#type' => 'select',
                '#id' => 'state_name_oprmntadr',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'State',
					$occupier_nationality_ck => $occupier_nationality_ck
                ),
                '#disabled' => TRUE,
                '#options' => get_all_state($state_v_oprmntadr),
                '#value' => !empty($state_v_oprmntadr) ? $state_v_oprmntadr : $occupier_state_oprmntadr,
				'#required' => TRUE,
                '#prefix' => '<div id="oprmntadr_edit_emp_state_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprmntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_c']['state_oprmntadr'] = array(
                '#title' => '(iv) State',
                '#type' => 'select',
                '#id' => 'state_name_oprmntadr',
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
                '#prefix' => '<div id="oprmntadr_edit_emp_state_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprmntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        }
        $value_state_oprmntadr = isset($form_state['values']['state']) ? $form_state['values']['state_oprmntadr'] : $occupier_state_oprmntadr;
        if (!empty($state_v_oprmntadr)) {
            $form['factory_part_c']['district_oprmntadr'] = array(
                '#title' => $occupier_nationality_check_data.'(v) District',
                '#type' => 'select',
                '#id' => 'district_name_oprmntadr',
                '#disabled' => TRUE,
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'District',
					$occupier_nationality_ck => $occupier_nationality_ck
                ),
                '#options' => get_district_by_id($state_v_oprmntadr),
                '#value' => !empty($district_v_oprmntadr) ? $district_v_oprmntadr : $occupier_district_oprmntadr,
				'#required' => TRUE,
                '#prefix' => '<div id="oprmntadr_edit_emp_district_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprmntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
            
            
        } else {
            $form['factory_part_c']['district_oprmntadr'] = array(
                '#title' => '(v) District',
                '#type' => 'select',
                '#id' => 'district_name_oprmntadr',
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
                '#prefix' => '<div id="oprmntadr_edit_emp_district_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        }
        $value_district_oprmntadr = isset($form_state['values']['district_oprmntadr']) ? $form_state['values']['district_oprmntadr'] : $occupier_district_oprmntadr;
        
        if (!empty($district_v_oprmntadr) && !empty($state_v_oprmntadr)) {
            
            $form['factory_part_c']['subdivision_oprmntadr'] = array(
                '#title' => $occupier_nationality_check_data.'(vi) Sub-Division',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Sub Division',
					$occupier_nationality_ck => $occupier_nationality_ck
                ),
                '#options' => common_custom_user_subdivisionlist_list_new($district_v_oprmntadr),
				'#required' => TRUE,
                '#default_value' => $occupier_subdivision_oprmntadr,
                '#prefix' => '<div id="oprmntadr_empsubdv_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprmntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            
            $form['factory_part_c']['subdivision_oprmntadr'] = array(
                '#title' => '(vi) Sub-Division',
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
                '#prefix' => '<div id="oprmntadr_empsubdv_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        }
        $value_subdivision_oprmntadr = isset($form_state['values']['subdivision_oprmntadr']) ? $form_state['values']['subdivision_oprmntadr'] : $occupier_subdivision_oprmntadr;
        if (!empty($value_district_oprmntadr) && !empty($value_state_oprmntadr) && !empty($value_subdivision_oprmntadr)) {
            $form['factory_part_c']['areatype_oprmntadr'] = array(
                '#title' => $occupier_nationality_check_data.'(vii) Area Type',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Area Type',
					$occupier_nationality_ck => $occupier_nationality_ck
                ),
                '#options' => common_custom_user_areatype_list_new($value_district_oprmntadr, $value_subdivision_oprmntadr),
				'#required' => TRUE,
                '#default_value' => $occupier_areatype_oprmntadr,
                '#prefix' => '<div id="oprmntadr_emp_areatype_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprmntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_c']['areatype_oprmntadr'] = array(
                '#title' => '(vii) Area Type',
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
                '#prefix' => '<div id="oprmntadr_emp_areatype_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
            
        }
        $value_areatype_oprmntadr = isset($form_state['values']['areatype_oprmntadr']) ? $form_state['values']['areatype_oprmntadr'] : $occupier_areatype_oprmntadr;
        
        if (!empty($value_district_oprmntadr) && !empty($value_state_oprmntadr) && $value_subdivision_oprmntadr != "" && !empty($value_areatype_oprmntadr)) {
            
            if ($value_areatype_oprmntadr == 'B') {
                $areatype_name_oprmntadr = 'Block';
            } elseif ($value_areatype_oprmntadr == 'M') {
                $areatype_name_oprmntadr = 'Municipality';
            } elseif ($value_areatype_oprmntadr == 'C') {
                $areatype_name_oprmntadr = 'Corporation';
            } elseif ($value_areatype_oprmntadr == 'S') {
                $areatype_name_oprmntadr = 'SEZ';
            } elseif ($value_areatype_oprmntadr == 'N') {
                $areatype_name_oprmntadr = 'Notified Area';
            }
            
            $form['factory_part_c']['block_oprmntadr'] = array(
                '#title' => $occupier_nationality_check_data.'(viii) '.$areatype_name_oprmntadr,
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Block/Municipality/Corporation/Notified Area/SEZ',
					$occupier_nationality_ck => $occupier_nationality_ck
                ),
                '#options' => common_custom_user_block_list_new($value_subdivision_oprmntadr, $value_areatype_oprmntadr),
				'#required' => TRUE,
                '#default_value' => $occupier_block_oprmntadr,
                '#prefix' => '<div id="oprmntadr_empareatype_name_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprmntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
            
            
        } else {
            
            $form['factory_part_c']['block_oprmntadr'] = array(
                '#title' => '(viii) Block / Municipality / Corporation / Notified Area / SEZ',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Block / Municipality / Corporation / Notified Area / SEZ'
                ),
                '#options' => array(
                    '0' => t('select Block / Municipality / Corporation / Notified Area / SEZ')
                ),
				'#required' => TRUE,
                '#prefix' => '<div id="oprmntadr_empareatype_name_replace"><div class="col-md-4 col-xs-12"><label class="select label-block" title="Block / Municipality / Corporation / Notified Area / SEZ">',
                '#suffix' => '</label></div></div>'
            );
            
            
        }
        $value_block_oprmntadr = isset($form_state['values']['block_oprmntadr']) ? $form_state['values']['block_oprmntadr'] : $occupier_block_oprmntadr;
        
        if (!empty($value_district_oprmntadr) && !empty($value_subdivision_oprmntadr) && !empty($value_areatype_oprmntadr) && !empty($value_block_oprmntadr) && !empty($value_state_oprmntadr)) {
            
            if ($value_areatype_oprmntadr == 'B') {
                $area_name_oprmntadr = 'Gram Panchayat';
                $area_code_oprmntadr = 'V';
            } elseif ($value_areatype_oprmntadr == 'M') {
                $area_name_oprmntadr = 'Ward';
                $area_code_oprmntadr = 'W';
            } elseif ($value_areatype_oprmntadr == 'C') {
                $area_name_oprmntadr = 'Ward';
                $area_code_oprmntadr = 'C';
            } elseif ($value_areatype_oprmntadr == 'S') {
                $area_name_oprmntadr = 'Sector';
                $area_code_oprmntadr = 'S';
            } elseif ($value_areatype_oprmntadr == 'N') {
                $area_name_oprmntadr = 'Notified Area';
                $area_code_oprmntadr = 'N';
            }
            
            $form['factory_part_c']['panchayat_oprmntadr'] = array(
                '#title' => $occupier_nationality_check_data.'(ix) '.$area_name_oprmntadr,
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'panchayat',
					$occupier_nationality_ck => $occupier_nationality_ck
                ),
                '#options' => get_full_villward($value_block_oprmntadr, $area_code_oprmntadr),
				'#required' => TRUE,
                '#default_value' => $occupier_panchayat_oprmntadr,
                '#prefix' => '<div id="oprmntadr_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprmntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_c']['panchayat_oprmntadr'] = array(
                '#title' => '(ix) Gram Panchayat / Ward / Sector',
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
                '#prefix' => '<div id="oprmntadr_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        }
        $value_panchayat_oprmntadr1 = isset($form_state['values']['panchayat_oprmntadr']) ? $form_state['values']['panchayat_oprmntadr'] : '';
        
        if (!empty($value_district_oprmntadr)) {
            
            $form['factory_part_c']['policestation_oprmntadr'] = array(
                '#title' => $occupier_nationality_check_data.'(x) Police Station',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Police Station',
					$occupier_nationality_ck => $occupier_nationality_ck
                ),
                '#options' => common_custom_user_ps_list_new($value_district_oprmntadr),
				'#required' => TRUE,
                '#default_value' => $occupier_policestation_oprmntadr,
                '#prefix' => '<div id="oprmntadr_empps_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        } else {
            $form['factory_part_c']['policestation_oprmntadr'] = array(
                '#title' => '(x) Police Station',
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
                '#prefix' => '<div id="oprmntadr_empps_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        }
        if (!empty($value_pincode_oprmntadr)) {
            $form['factory_part_c']['postoffice_oprmntadr'] = array(
                '#title' => $occupier_nationality_check_data.'(xi) Post Office',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Post Office',
					$occupier_nationality_ck => $occupier_nationality_ck
					
                ),
                '#options' => common_custom_post_office_list_new($value_pincode_oprmntadr),
				'#required' => TRUE,
                '#default_value' => $occupier_postoffice_oprmntadr,
                '#prefix' => '<div id="oprmntadr_post_office_div"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        } else {
            $form['factory_part_c']['postoffice_oprmntadr'] = array(
                '#title' => '(xi) Post Office',
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
                '#prefix' => '<div id="oprmntadr_post_office_div"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        }

    if ($value_nationality == "Other") {
		
        $form['factory_part_c']['occupier_passport'] = array(
            '#prefix' => '<div id="ld_show_passport"><div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div></div>',
            '#title' => t($occupier_nationality_check_data.'(ii) Passport Number'),
            '#type' => 'textfield',
            '#default_value'  => !empty($occupier_passport) ? $occupier_passport :'',
			'#attributes' => array('class' => array( ''),$occupier_nationality_ck => $occupier_nationality_ck ),
        );
        
        $form['factory_part_c']['addrline_oprmntadr']      = array(
            '#prefix' => '<div id = "addrline_oprmntadr_div"><div class="col-md-12 col-xs-12"><label class="textarea label-block">',
            '#suffix' => '</label></div></div>',
            '#title' => $occupier_nationality_check_data.'(iii) Address',
            '#rows' => 3,
            '#type' => 'textarea',
			'#required' => TRUE,
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Address Line',
				$occupier_nationality_ck => $occupier_nationality_ck
            ),
            '#default_value' => $occupier_addrline_oprmntadr
        );
		
		$form['factory_part_c']['occupier_aadhaar']     = array(
			'#prefix' => '<div id="ld_show_aadhaar">',
			'#suffix' => '</div>'
		);
		$form['factory_part_c']['pincodeoprmntadr']          = array(
            '#prefix' => '<div id="pincodeoprmntadr_id">',
            '#suffix' => '</div>'
        );
        $form['factory_part_c']['state_oprmntadr']         = array(
            '#prefix' => '<div id="oprmntadr_edit_emp_state_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_c']['district_oprmntadr']      = array(
            '#prefix' => '<div id="oprmntadr_edit_emp_district_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_c']['subdivision_oprmntadr']   = array(
            '#prefix' => '<div id="oprmntadr_empsubdv_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_c']['areatype_oprmntadr']      = array(
            '#prefix' => '<div id="oprmntadr_emp_areatype_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_c']['block_oprmntadr']         = array(
            '#prefix' => '<div id="oprmntadr_empareatype_name_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_c']['panchayat_oprmntadr']     = array(
            '#prefix' => '<div id="oprmntadr_emp_vill_ward_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_c']['panchayat_oprmntadr']     = array(
            '#prefix' => '<div id="oprmntadr_emp_vill_ward_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_c']['policestation_oprmntadr'] = array(
            '#prefix' => '<div id="oprmntadr_empps_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_c']['postoffice_oprmntadr']    = array(
            '#prefix' => '<div id="oprmntadr_post_office_div">',
            '#suffix' => '</div>'
        );
        
    }
    $form['factory_part_c']['thirdRowEnd'] = array(
        '#prefix' => '',
        '#suffix' => '</div>'
    );
    
	 /********** Occupier Permanent Address - End **********/
	 
    /********** Occupier Present Address - Start **********/
	
    $form['factory_part_oprsntadr'] = array(
        '#type' => 'fieldset',
        '#title' => t('D ii). Occupier Present Address'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
	$form['factory_part_oprsntadr']['markup_div'] = array(
        '#prefix' =>'<div class="row">' ,
		'#suffix' => '',
       
    );
	 $form['factory_part_oprsntadr']['same_as_address_occupier'] = array(
        '#type' => 'checkbox',
        '#default_value' => !empty($occupier_present_address_same)?$occupier_present_address_same:0,
		'#attributes' => array('class' => array( ''),$occupier_present_address_check_ck => $occupier_present_address_check_ck ),
        '#ajax' => array(
            'event' => 'change',
            'effect' => 'fade',
            'callback' => 'get_ajax_same_address_permanent_occupier',
            'progress' => array(
                'type' => 'throbber',
                'message' => t('loading')
            )
        ),
        '#title' => t('Same as occupier permanent address'),
        '#prefix' => '<div class="col-md-12 col-xs-12">',
        '#suffix' => '</div>'
    );
	$checkbox_premanent_occupier = isset($form_state['values']['same_as_address_occupier']) ? $form_state['values']['same_as_address_occupier'] :$occupier_present_address_same;
	 
	 if($checkbox_premanent_occupier == 1) {
        $form['factory_part_oprsntadr']['pincodeoprsntadr']      = array(
            '#prefix' => '<div id ="pincodeoprsntadr_id">',
            '#suffix' => '</div>'
        );
		
        $form['factory_part_oprsntadr']['state_oprsntadr']       = array(
            
            '#prefix' => '<div id="oprsntadr_edit_emp_state_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_oprsntadr']['district_oprsntadr']    = array(
            
            '#prefix' => '<div id="oprsntadr_edit_emp_district_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_oprsntadr']['subdivision_oprsntadr'] = array(
            
            '#prefix' => '<div id="oprsntadr_empsubdv_replace">',
            '#suffix' => '</div>'
            
        );
        $form['factory_part_oprsntadr']['areatype_oprsntadr']    = array(
            
            '#prefix' => '<div id="oprsntadr_emp_areatype_replace">',
            '#suffix' => '</div>'
        );
        
        $form['factory_part_oprsntadr']['block_oprsntadr']         = array(
            
            '#prefix' => '<div id="oprsntadr_empareatype_name_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_oprsntadr']['panchayat_oprsntadr']     = array(
            
            '#prefix' => '<div id="oprsntadr_emp_vill_ward_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_oprsntadr']['policestation_oprsntadr'] = array(
            
            '#prefix' => '<div id="oprsntadr_empps_replace">',
            '#suffix' => '</div>'
        );
        $form['factory_part_oprsntadr']['postoffice_oprsntadr']    = array(
            
            '#prefix' => '<div id="oprsntadr_post_office_div">',
            '#suffix' => '</div>'
        );
        $form['factory_part_oprsntadr']['addrline_oprsntadr']      = array(
            
            '#prefix' => '<div id = "addrline_oprsntadr_id">',
            '#suffix' => '</div>'
        );
    }
	 if($checkbox_premanent_occupier == 0) {
		 
		  $form['factory_part_oprsntadr']['pincodeoprsntadr'] = array(
            '#prefix' => '<div id="pincodeoprsntadr_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
            '#suffix' => '</label></div></div>',
            '#default_value'  => !empty($occupier_pincodeoprsntadr) ? $occupier_pincodeoprsntadr :'',
			'#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Pincode',
				$occupier_present_address_ck => $occupier_present_address_ck
            ),
            '#autocomplete_path' => 'pinautocomplete',
            '#id' => 'pincode_autocomplete_oprsntadr',
            '#maxlength' => 6,
            '#title' => t($occupier_present_address_check_data.'(i) Pincode'),
            '#required' => TRUE,
            '#type' => 'textfield',
            '#ajax' => array(
                //'event'         => 'change',
                'effect' => 'fade',
                'callback' => 'get_ajax_load_oprsntadr',
                'progress' => array(
                    'type' => 'throbber',
                    'message' => t('loading')
                )
            )
        );
		$value_pincode_oprsntadr   = isset($form_state['values']['pincodeoprsntadr']) ? $form_state['values']['pincodeoprsntadr'] : $occupier_pincodeoprsntadr;
        if (!empty($value_pincode_oprsntadr)) {
            
            $query_oprsntadr = db_select('fa_all_india_pin_code', 'p')->fields('p', array(
                'districtname',
                'statename',
                'pincode',
                'district_code',
                'state_code',
                'po_name'
            ))->condition('p.pincode', trim($value_pincode_oprsntadr), '=');
            
            $result_oprsntadr = $query_oprsntadr->execute();
            if ($result_oprsntadr->rowcount() > 0) {
                $final_oprsntadr       = $result_oprsntadr->fetchAssoc();
                $pincode_v_oprsntadr   = $value_pincode_oprsntadr;
                $state_v_oprsntadr     = $final_oprsntadr['state_code'];
                $district_v_oprsntadr  = $final_oprsntadr['district_code'];
                $post_office_oprsntadr = $final_oprsntadr['po_name'];
            }
        }
		
		if (!empty($state_v_oprsntadr)) {
            $form['factory_part_oprsntadr']['state_oprsntadr'] = array(
                '#title' => $occupier_present_address_check_data.'(ii) State',
                '#type' => 'select',
                '#id' => 'state_name_oprsntadr',
				'#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'State',
					$occupier_present_address_ck => $occupier_present_address_ck
                ),
                '#disabled' => TRUE,
                '#options' => get_all_state($state_v_oprsntadr),
                '#value' => !empty($state_v_oprsntadr) ? $state_v_oprsntadr : $occupier_state_oprsntadr,
				'#required' => TRUE,
                '#prefix' => '<div id="oprsntadr_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprsntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_oprsntadr']['state_oprsntadr'] = array(
                '#title' => '(ii) State',
                '#type' => 'select',
                '#id' => 'state_name_oprsntadr',
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
                '#prefix' => '<div id="oprsntadr_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprsntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        }
        
        $value_state_oprsntadr = isset($form_state['values']['state_oprsntadr']) ? $form_state['values']['state_oprsntadr'] : $occupier_state_oprsntadr;
		
		if (!empty($state_v_oprsntadr)) {
            $form['factory_part_oprsntadr']['district_oprsntadr'] = array(
                '#title' => $occupier_present_address_check_data.'(iii) District',
                '#type' => 'select',
                '#id' => 'district_name_oprsntadr',
                '#disabled' => TRUE,
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'District',
					$occupier_present_address_ck => $occupier_present_address_ck
                ),
                '#options' => get_district_by_id($state_v_oprsntadr),
                '#value' => !empty($district_v_oprsntadr) ? $district_v_oprsntadr : $occupier_district_oprsntadr,
				'#required' => TRUE,
                '#prefix' => '<div id="oprsntadr_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprsntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_oprsntadr']['district_oprsntadr'] = array(
                '#title' => '(iii) District',
                '#type' => 'select',
                '#id' => 'district_name_oprsntadr',
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
                '#prefix' => '<div id="oprsntadr_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        }
		
		$form['factory_part_oprsntadr']['firstRowEnd'] = array(
            '#prefix' => '',
            '#suffix' => '</div>'
        );
        
        $value_district_oprsntadr = isset($form_state['values']['district_oprsntadr']) ? $form_state['values']['district_oprsntadr'] : $occupier_district_oprsntadr;
		
		$form['factory_part_oprsntadr']['secondRowStart'] = array(
            '#prefix' => '<div class="row">',
            '#suffix' => ''
        );
		
		if (!empty($district_v_oprsntadr) && !empty($state_v_oprsntadr)) {
            
            $form['factory_part_oprsntadr']['subdivision_oprsntadr'] = array(
                '#title' => $occupier_present_address_check_data.'(iv) Sub-Division',
                '#type' => 'select',
                '#default_value'  => $occupier_subdivision_oprsntadr,
				'#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Sub Division',
					$occupier_present_address_ck => $occupier_present_address_ck
                ),
                '#options' => common_custom_user_subdivisionlist_list_new($district_v_oprsntadr),
				'#required' => TRUE,
                '#prefix' => '<div id="oprsntadr_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprsntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            
            $form['factory_part_oprsntadr']['subdivision_oprsntadr'] = array(
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
                '#prefix' => '<div id="oprsntadr_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        }
        
		$value_subdivision_oprsntadr = isset($form_state['values']['subdivision_oprsntadr']) ? $form_state['values']['subdivision_oprsntadr'] : $occupier_subdivision_oprsntadr;
		if (!empty($value_district_oprsntadr) && !empty($value_state_oprsntadr) && !empty($value_subdivision_oprsntadr)) {
            $form['factory_part_oprsntadr']['areatype_oprsntadr'] = array(
                '#title' => $occupier_present_address_check_data.'(v) Area Type',
                '#type' => 'select',
                '#default_value'  => $occupier_areatype_oprsntadr,
				'#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Area Type',
					$occupier_present_address_ck => $occupier_present_address_ck
                ),
                '#options' => common_custom_user_areatype_list_new($value_district_oprsntadr, $value_subdivision_oprsntadr),
                '#required' => TRUE,
				'#prefix' => '<div id="oprsntadr_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprsntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_oprsntadr']['areatype_oprsntadr'] = array(
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
                '#prefix' => '<div id="oprsntadr_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        }
        
        $value_areatype_oprsntadr = isset($form_state['values']['areatype_oprsntadr']) ? $form_state['values']['areatype_oprsntadr'] : $occupier_areatype_oprsntadr;
		
		if (!empty($value_district_oprsntadr) && !empty($value_state_oprsntadr) && $value_subdivision_oprsntadr != "" && !empty($value_areatype_oprsntadr)) {
            
            if ($value_areatype_oprsntadr == 'B') {
                $areatype_name_oprsntadr = 'Block';
            } elseif ($value_areatype_oprsntadr == 'M') {
                $areatype_name_oprsntadr = 'Municipality';
            } elseif ($value_areatype_oprsntadr == 'C') {
                $areatype_name_oprsntadr = 'Corporation';
            } elseif ($value_areatype_oprsntadr == 'S') {
                $areatype_name_oprsntadr = 'SEZ';
            } elseif ($value_areatype_oprsntadr == 'N') {
                $areatype_name_oprsntadr = 'Notified Area';
            }
            
			$form['factory_part_oprsntadr']['block_oprsntadr'] = array(
                '#title' => $occupier_present_address_check_data.'(vi) '.$areatype_name_oprsntadr,
                '#type' => 'select',
				'#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'block',
					$occupier_present_address_ck => $occupier_present_address_ck
                ),
                '#options' => common_custom_user_block_list_new($value_subdivision_oprsntadr, $value_areatype_oprsntadr),
				'#required' => TRUE,
                '#default_value'  => $occupier_block_oprsntadr,
				'#prefix' => '<div id="oprsntadr_empareatype_name_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprsntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
            
        } else {
            $form['factory_part_oprsntadr']['block_oprsntadr'] = array(
                '#title' => '(vi) Block / Municipality / Corporation / Notified Area / SEZ',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'block'
                ),
                '#options' => array(
                    '0' => t('Select Block / Municipality / Corporation / Notified Area / SEZ ')
                ),
				'#required' => TRUE,
                '#prefix' => '<div id="oprsntadr_empareatype_name_replace"><div class="col-md-4"><label class="select label-block" title="Block / Municipality / Corporation / Notified Area / SEZ">',
                '#suffix' => '</label></div></div>'
            );
        }
        
        $form['factory_part_oprsntadr']['secondRowEnd'] = array(
            '#prefix' => '',
            '#suffix' => '</div>'
        );
        
        $form['factory_part_oprsntadr']['thirdRowStart'] = array(
            '#prefix' => '<div class="row">',
            '#suffix' => ''
        );
        $value_block_oprsntadr    = isset($form_state['values']['block_oprsntadr']) ? $form_state['values']['block_oprsntadr'] : $occupier_block_oprsntadr;
        
        if (!empty($value_district_oprsntadr) && !empty($value_subdivision_oprsntadr) && !empty($value_areatype_oprsntadr) && !empty($value_block_oprsntadr) && !empty($value_state_oprsntadr)) {
            
            if ($value_areatype_oprsntadr == 'B') {
                $area_name_oprsntadr = 'Gram Panchayat';
                $area_code_oprsntadr = 'V';
            } elseif ($value_areatype_oprsntadr == 'M') {
                $area_name_oprsntadr = 'Ward';
                $area_code_oprsntadr = 'W';
            } elseif ($value_areatype_oprsntadr == 'C') {
                $area_name_oprsntadr = 'Ward';
                $area_code_oprsntadr = 'C';
            } elseif ($value_areatype_oprsntadr == 'S') {
                $area_name_oprsntadr = 'Sector';
                $area_code_oprsntadr = 'S';
            } elseif ($value_areatype_oprsntadr == 'N') {
                $area_name_oprsntadr = 'Notified Area';
                $area_code_oprsntadr = 'N';
            }
            
            $form['factory_part_oprsntadr']['panchayat_oprsntadr'] = array(
                '#title' => $occupier_present_address_check_data.'(vii) '.$area_name_oprsntadr,
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'panchayat',
					$occupier_present_address_ck => $occupier_present_address_ck
                ),
                '#options' => common_custom_user_villward_list_new($value_block_oprsntadr, $area_code_oprsntadr),
				'#required' => TRUE,
                '#default_value'  => $occupier_panchayat_oprsntadr,
				'#prefix' => '<div id="oprsntadr_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>',
                '#ajax' => array(
                    'event' => 'change',
                    'effect' => 'fade',
                    'callback' => 'get_ajax_load_oprsntadr',
                    'progress' => array(
                        'type' => 'throbber',
                        'message' => t('loading')
                    )
                )
            );
        } else {
            $form['factory_part_oprsntadr']['panchayat_oprsntadr'] = array(
                '#title' => '(vii) Gram Panchayat / Ward / Sector',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'panchayat'
                ),
                '#options' => array(
                    '0' => t('Select Gram Panchayat/Ward/Sector/Notified Area')
                ),
				'#required' => TRUE,
                '#prefix' => '<div id="oprsntadr_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        }
        $value_panchayat_oprsntadr = isset($form_state['values']['panchayat_oprsntadr']) ? $form_state['values']['panchayat_oprsntadr'] : $occupier_panchayat_oprsntadr;
        
        if (!empty($value_district_oprsntadr) && !empty($value_subdivision_oprsntadr) && !empty($value_areatype_oprsntadr) && !empty($value_block_oprsntadr) && !empty($value_state_oprsntadr) && !empty($value_panchayat_oprsntadr)) {
            $form['factory_part_oprsntadr']['policestation_oprsntadr'] = array(
                '#title' => $occupier_present_address_check_data.'(viii) Police Station',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Police Station',
					$occupier_present_address_ck => $occupier_present_address_ck
                ),
                '#options' => common_custom_user_ps_list_new($value_district_oprsntadr),
                '#required' => TRUE,
				'#default_value'  => $occupier_policestation_oprsntadr,
				'#prefix' => '<div id="oprsntadr_empps_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        } else {
            $form['factory_part_oprsntadr']['policestation_oprsntadr'] = array(
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
                '#prefix' => '<div id="oprsntadr_empps_replace"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
        }
        
        if (!empty($pincode_v_oprsntadr)) {
            $form['factory_part_oprsntadr']['postoffice_oprsntadr'] = array(
                '#title' => $occupier_present_address_check_data.'(ix) Post Office',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Post Office',
					$occupier_present_address_ck => $occupier_present_address_ck
                ),
                '#options' => common_custom_post_office_list_new($pincode_v_oprsntadr),
				'#required' => TRUE,
                '#default_value'  => $occupier_postoffice_oprsntadr,
				'#prefix' => '<div id="oprsntadr_post_office_div"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
			
        } else {
            $form['factory_part_oprsntadr']['postoffice_oprsntadr'] = array(
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
                '#prefix' => '<div id="oprsntadr_post_office_div"><div class="col-md-4"><label class="select label-block">',
                '#suffix' => '</label></div></div>'
            );
            
        }
        
        $form['factory_part_oprsntadr']['addrline_oprsntadr'] = array(
            '#title' => $occupier_present_address_check_data.'(x) Address',
            '#rows' => 3,
            '#type' => 'textarea',
			'#required' => TRUE,
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Address Line',
				$occupier_present_address_ck => $occupier_present_address_ck
            ),
            '#default_value' => $occupier_addrline_oprsntadr,
			'#prefix' => '<div id="addrline_oprsntadr_id"><div class="col-md-12"><label class="textarea label-block">',
            '#suffix' => '</label></div></div>'
        );
	 }
   
    $form['factory_part_oprsntadr']['thirdRowEnd'] = array(
        '#prefix' => '',
        '#suffix' => '</div>'
    );
   
	/********** Occupier Present Address - End **********/    
    
    /********** Details of owner of the premises occupied as a factory - Start **********/
    
    $form['factory_part_premises'] = array(
        '#type' => 'fieldset',
        '#title' => t('E. Details of owner/land lord/lessor of the premises occupied as a factory'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
    
    $form['factory_part_premises']['firstRowStart'] = array(
        '#prefix' => '<div class="row">',
        '#suffix' => ''
    );
    $form['factory_part_premises']['owner_name']    = array(
        '#prefix' => '<div class="col-md-6 col-xs-12"><label class="input label-block">',
        '#suffix' => '</label></div>',
        '#title' => t($owner_name_check_data.'(i) Name of the Owner / Land Lord / Lessor of the premises'),
        '#type' => 'textfield',
        '#default_value' => $owner_name,
		'#attributes' => array('class' => array('charField'),$owner_name_ck => $owner_name_ck ),
        '#required' => TRUE,
    );
    
    $form['factory_part_premises']['addrline_premises'] = array(
        '#title' => $owner_address_check_data.'(ii) Address',
        '#rows' => 3,
        '#type' => 'textarea',
		'#required' => TRUE,
        '#attributes' => array(
            'class' => array(
                ''
            ),
            'placeholder' => 'Address Line',
		    $owner_address_ck => $owner_address_ck
			
        ),
        '#default_value' => $owner_addrline_premises,
        '#prefix' => '<div id="addrline_premises_div"><div class="col-md-12"><label class="textarea label-block">',
        '#suffix' => '</label></div></div>'
    );
    
		$form['factory_part_premises']['thirdRowEnd'] = array(
			'#prefix' => '',
			'#suffix' => '</div>'
		);
	
    /********** Details of owner of the premises occupied as a factory - End **********/
	
    /********** Particular of Plant to be installed - Start **********/
	 
	 $form['factory_plant_installed'] = array(
        '#type' => 'fieldset',
        '#title' => t('F. Particular of Plan to be installed'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
    
    $form['factory_plant_installed']['firstRowStart'] = array(
        '#prefix' => '<div class="row">',
        '#suffix' => ''
    );
    $form['factory_plant_installed']['plant_installed'] = array(
        '#title' => $owner_address_check_data.'(i) Plant To be Installed',
        '#rows' => 3,
        '#type' => 'textarea',
		'#required' => TRUE,
        '#attributes' => array(
            'class' => array(
                ''
            ),
		    $owner_address_ck => $owner_address_ck
        ),
        '#default_value' => $plant_installed,
        '#prefix' => '<div id="addrline_premises_div"><div class="col-md-12"><label class="textarea label-block">',
        '#suffix' => '</label></div></div>'
    );
    
		$form['factory_plant_installed']['thirdRowEnd'] = array(
			'#prefix' => '',
			'#suffix' => '</div>'
		);

    /********** Particular of Plant to be installed - End **********/

    /********** In case of registered actory - Start **********/
	
	    $form['factory_part_if_reg'] = array(
			'#type' => 'fieldset',
			'#title' => t('G. Details of Registered Factory'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => FALSE // Added
		);
		$form['factory_part_if_reg']['firstRowStart'] = array(
			'#prefix' => '<div class="row">',
			'#suffix' => ''
		);
		$radios_options = array('Y'=>"Yes",'N'=>"No");	
		 $form['factory_part_if_reg']['is_fact_reg']= array(
			'#prefix'	 		=> '<div id="is_fact_reg_div"><div class="col-xs-12">Do you have a Registered factory ?',
			 '#suffix'    		=> '</div></div>',
			 '#type'		 	=> 'radios',
			 //'#attributes' 		=> array('class'=>array('radio')),
			 '#options'   		=> $radios_options,	
			 '#ajax'			=> array(
										 'event' 		=> 'change',
										 'effect' 		=> 'fade',			
										 'callback'		=> 'get_ajax_reg',
										 'progress'		=>	array(
										 'type'			=> 'throbber',
										 'message'		=> t('loading'),
									 )
							 ),
			 '#default_value' 	=> !empty($classification_no)? 'Y' : 'N',
			 '#required' => TRUE,
	    );
	 
	 	$form['factory_part_if_reg']['classification_no'] = array(
			'#prefix' => '<div id="classification_no_div">',
			'#suffix' => '</div>',
		);
		$form['factory_part_if_reg']['factory_registrstion_no'] = array(
			'#prefix' => '<div id="factory_registrstion_no_div">',
			'#suffix' => '</div>',
		);
		$form['factory_part_if_reg']['registration_date'] = array(
			'#prefix' => '<div id="registration_date_div">',
			'#suffix' => '</div>',
		);
		$form['factory_part_if_reg']['factory_license_no'] = array(
			'#prefix' => '<div id="factory_license_no_div">',
			'#suffix' => '</div>',
		);
		$form['factory_part_if_reg']['license_date'] = array(
			'#prefix' => '<div id="license_date_div">',
			'#suffix' => '</div>',
		);
	 
	$value_is_fact_reg	= isset($form_state['values']['is_fact_reg'])? $form_state['values']['is_fact_reg'] : '';
	
	if(($value_is_fact_reg == 'Y') || !empty($classification_no))
	{ 
	 	$form['factory_part_if_reg']['classification_no'] = array(
			'#prefix' => '<div id="classification_no_div"><div class="col-md-2"><label class="input label-block">',
			'#suffix' => '</label></div></div>',
			'#title' => t($factory_headoffice_check_data.'(i) Classification No.'),
			'#type' => 'textfield',
			'#default_value' => $classification_no,
			'#attributes' => array('class' => array(''),$factory_headoffice_ck => $factory_headoffice_ck ),
			'#maxlength' => 10,
			'#required' => TRUE
		);
		$form['factory_part_if_reg']['factory_registrstion_no'] = array(
			'#prefix' => '<div id="factory_registrstion_no_div"><div class="col-md-2"><label class="input label-block">',
			'#suffix' => '</label></div></div>',
			'#title' => t($factory_headoffice_check_data.'(ii) Registration No.'),
			'#type' => 'textfield',
			'#default_value' => $factory_registrstion_no,
			'#attributes' => array('class' => array(''),$factory_headoffice_ck => $factory_headoffice_ck ),
			'#maxlength' => 10,
			'#required' => TRUE
		);
				
		$form['factory_part_if_reg']['registration_date'] = array(
			'#prefix' => '<div id="registration_date_div"><div class="col-md-3"><label class="input label-block">',
			'#suffix' => '</label></div></div>',
			'#title' => t($factory_headoffice_check_data.'(iv) Date of Registration'),
			'#type' => 'textfield',
			'#default_value' => $registration_date,
			'#attributes' => array('class' => array('datepicker_cls'),$factory_headoffice_ck => $factory_headoffice_ck ),
			'#required' => TRUE
		);

		$form['factory_part_if_reg']['factory_license_no'] = array(
			'#prefix' => '<div id="factory_license_no_div"><div class="col-md-2"><label class="input label-block">',
			'#suffix' => '</label></div></div>',
			'#title' => t($factory_headoffice_check_data.'(iii) Licence No.'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#default_value' => $factory_license_no,
			'#attributes' => array('class' => array(''),$factory_headoffice_ck => $factory_headoffice_ck )
		);
		
		$form['factory_part_if_reg']['license_date'] = array(
			'#prefix' => '<div id="license_date_div"><div class="col-md-3"><label class="input label-block">',
			'#suffix' => '</label></div></div>',
			'#title' => t($factory_headoffice_check_data.'(iv) Date of Issue of Licence'),
			'#type' => 'textfield',
			'#default_value' => $license_date,
			'#attributes' => array('class' => array('datepicker_cls'),$factory_headoffice_ck => $factory_headoffice_ck ),
			'#required' => TRUE
		);
	}

		$form['factory_part_if_reg']['firstRowEnd'] = array(
			'#prefix' => '',
			'#suffix' => '</div>'
		);

	/********** In case of registered actory - End ************/

	if($plan_approve_status != 'F')
	{
		$form['back_link'] = array(
			
			'#markup' => l(t('<i class="fa fa-fw fa-chevron-left"></i> Back'), 'applicant_dashboard/', array(
				'html' => TRUE,
				'attributes' => array(
					'class' => array(
						'btn btn-outline-dark pull-left '
					)
				)
			))
		);
    
		$form['submit'] = array(
        '#prefix' => '',
        '#suffix' => '</div>',
        '#attributes' => array(
            'class' => array(
                'btn btn-dark pull-right'
            )
        ),
        '#type' => 'submit',
        '#value' => 'Save & Continue'
    	);
	}
    return $form;
	
}

function get_ajax_boundary($form, &$form_state)
{
    $commands   = array();
    $commands[] = ajax_command_replace('#view_boundary', drupal_render($form['factory_part_a']['zone_boundary']));
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}
function get_ajax_reg($form, $form_state)
{
    $commands   = array();
	$commands[] = ajax_command_replace('#is_fact_reg_div', drupal_render($form['factory_part_if_reg']['is_fact_reg']));
	$commands[] = ajax_command_replace('#classification_no_div', drupal_render($form['factory_part_if_reg']['classification_no']));
	$commands[] = ajax_command_replace('#factory_registrstion_no_div', drupal_render($form['factory_part_if_reg']['factory_registrstion_no']));
	$commands[] = ajax_command_replace('#registration_date_div', drupal_render($form['factory_part_if_reg']['registration_date']));
	$commands[] = ajax_command_replace('#factory_license_no_div', drupal_render($form['factory_part_if_reg']['factory_license_no']));
	$commands[] = ajax_command_replace('#license_date_div', drupal_render($form['factory_part_if_reg']['license_date']));
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}
function get_ajax_load($form, $form_state)
{
    $commands   = array();
    $commands[] = ajax_command_replace('#ld_edit_emp_state_replace', drupal_render($form['factory_part_a']['state']));
    $commands[] = ajax_command_replace('#ld_edit_emp_district_replace', drupal_render($form['factory_part_a']['district']));
    $commands[] = ajax_command_replace('#ld_empsubdv_replace', drupal_render($form['factory_part_a']['subdivision']));
    $commands[] = ajax_command_replace('#ld_emp_areatype_replace', drupal_render($form['factory_part_a']['areatype']));
    $commands[] = ajax_command_replace('#ld_empareatype_name_replace', drupal_render($form['factory_part_a']['block']));
    $commands[] = ajax_command_replace('#ld_emp_vill_ward_replace', drupal_render($form['factory_part_a']['panchayat']));
    $commands[] = ajax_command_replace('#ld_empps_replace', drupal_render($form['factory_part_a']['policestation']));
    $commands[] = ajax_command_replace('#ld_post_office_div', drupal_render($form['factory_part_a']['postoffice']));
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}
function get_ajax_factory_address($form, &$form_state)
{
    $commands   = array();
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
function get_ajax_load_off($form, $form_state)
{
    $commands   = array();
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
function get_ajax_occupier_type($form, &$form_state)
{
    $commands   = array();
	$factprofiletype = $form_state['values']['ownership_type'];
    $commands[] = ajax_command_replace('#occupier_type_id', drupal_render($form['factory_part_d']['occupier_type']));
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}

function get_ajax_nationality($form, &$form_state)
{
    $commands   = array();
    $commands[] = ajax_command_replace('#ld_show_aadhaar', drupal_render($form['factory_part_c']['occupier_aadhaar']));
	$commands[] = ajax_command_replace('#ld_show_passport', drupal_render($form['factory_part_c']['occupier_passport']));
    $commands[] = ajax_command_replace('#addrline_oprmntadr_div', drupal_render($form['factory_part_c']['addrline_oprmntadr']));
    $commands[] = ajax_command_replace('#pincodeoprmntadr_id', drupal_render($form['factory_part_c']['pincodeoprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_edit_emp_state_replace', drupal_render($form['factory_part_c']['state_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_edit_emp_district_replace', drupal_render($form['factory_part_c']['district_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_empsubdv_replace', drupal_render($form['factory_part_c']['subdivision_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_emp_areatype_replace', drupal_render($form['factory_part_c']['areatype_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_empareatype_name_replace', drupal_render($form['factory_part_c']['block_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_emp_vill_ward_replace', drupal_render($form['factory_part_c']['panchayat_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_empps_replace', drupal_render($form['factory_part_c']['policestation_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_post_office_div', drupal_render($form['factory_part_c']['postoffice_oprmntadr']));
    
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}

function get_ajax_load_oprmntadr($form, $form_state)
{
    $commands   = array();
    $commands[] = ajax_command_replace('#oprmntadr_edit_emp_state_replace', drupal_render($form['factory_part_d']['state_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_edit_emp_district_replace', drupal_render($form['factory_part_c']['district_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_empsubdv_replace', drupal_render($form['factory_part_c']['subdivision_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_emp_areatype_replace', drupal_render($form['factory_part_c']['areatype_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_empareatype_name_replace', drupal_render($form['factory_part_c']['block_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_emp_vill_ward_replace', drupal_render($form['factory_part_c']['panchayat_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_empps_replace', drupal_render($form['factory_part_c']['policestation_oprmntadr']));
    $commands[] = ajax_command_replace('#oprmntadr_post_office_div', drupal_render($form['factory_part_c']['postoffice_oprmntadr']));
    
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}

function get_ajax_same_address_permanent_occupier($form, &$form_state)
{
	$commands = array();
	$commands[] = ajax_command_replace('#pincodeoprsntadr_id', drupal_render($form['factory_part_oprsntadr']['pincodeoprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_edit_emp_state_replace', drupal_render($form['factory_part_oprsntadr']['state_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_edit_emp_district_replace', drupal_render($form['factory_part_oprsntadr']['district_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_empsubdv_replace', drupal_render($form['factory_part_oprsntadr']['subdivision_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_emp_areatype_replace', drupal_render($form['factory_part_oprsntadr']['areatype_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_empareatype_name_replace', drupal_render($form['factory_part_oprsntadr']['block_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_emp_vill_ward_replace', drupal_render($form['factory_part_oprsntadr']['panchayat_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_empps_replace', drupal_render($form['factory_part_oprsntadr']['policestation_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_post_office_div', drupal_render($form['factory_part_oprsntadr']['postoffice_oprsntadr']));
	$commands[] = ajax_command_replace('#addrline_oprsntadr_id', drupal_render($form['factory_part_oprsntadr']['addrline_oprsntadr']));
	return array('#type' => 'ajax', '#commands' => $commands);
}

function get_ajax_load_oprsntadr($form, $form_state)
{
	$commands = array();
	$commands[] = ajax_command_replace('#oprsntadr_edit_emp_state_replace', drupal_render($form['factory_part_oprsntadr']['state_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_edit_emp_district_replace', drupal_render($form['factory_part_oprsntadr']['district_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_empsubdv_replace', drupal_render($form['factory_part_oprsntadr']['subdivision_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_emp_areatype_replace', drupal_render($form['factory_part_oprsntadr']['areatype_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_empareatype_name_replace', drupal_render($form['factory_part_oprsntadr']['block_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_emp_vill_ward_replace', drupal_render($form['factory_part_oprsntadr']['panchayat_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_empps_replace', drupal_render($form['factory_part_oprsntadr']['policestation_oprsntadr']));
	$commands[] = ajax_command_replace('#oprsntadr_post_office_div', drupal_render($form['factory_part_oprsntadr']['postoffice_oprsntadr']));
	return array('#type' => 'ajax', '#commands' => $commands);
}

function get_ajax_load_premises($form, $form_state)
{
    $commands   = array();
    $commands[] = ajax_command_replace('#premises_edit_emp_state_replace', drupal_render($form['factory_part_premises']['state_premises']));
    $commands[] = ajax_command_replace('#premises_edit_emp_district_replace', drupal_render($form['factory_part_premises']['district_premises']));
    $commands[] = ajax_command_replace('#premises_empsubdv_replace', drupal_render($form['factory_part_premises']['subdivision_premises']));
    $commands[] = ajax_command_replace('#premises_emp_areatype_replace', drupal_render($form['factory_part_premises']['areatype_premises']));
    $commands[] = ajax_command_replace('#premises_empareatype_name_replace', drupal_render($form['factory_part_premises']['block_premises']));
    $commands[] = ajax_command_replace('#premises_emp_vill_ward_replace', drupal_render($form['factory_part_premises']['panchayat_premises']));
    $commands[] = ajax_command_replace('#premises_empps_replace', drupal_render($form['factory_part_premises']['policestation_premises']));
    $commands[] = ajax_command_replace('#premises_post_office_div', drupal_render($form['factory_part_premises']['postoffice_premises']));
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}

function caf_form_extension_parta_validate($form, &$form_state)
{
  $comm_telephone = $form_state['values']['comm_telephone'];
  $comm_mobile = $form_state['values']['comm_mobile'];
  
  if ($form_state['values']['comm_telephone']=="" && $form_state['values']['comm_mobile']=="") {
    form_set_error('comm_telephone', t('You must enter either Telephone No. or Mobile!!'));
  }
}

function caf_form_extension_parta_submit($form, &$form_state)
{
    global $user;
    $userid 				= $user->uid;
    $val    				= $form_state['values'];

    $service_id 			   = encryption_decryption_fun('decrypt', $val['serviceid_hidden']);
	$factory_type_id    	   = encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']);
	$application_id 		   = encryption_decryption_fun('decrypt', $val['applicationid_hidden']);
	$backlogplanapproval_no    = encryption_decryption_fun('decrypt', $val['backlog_plan_approval_no_hidden']);
	$backlogplanapproval_date  = encryption_decryption_fun('decrypt', $val['backlog_plan_approval_date_hidden']);
	
	//for first time visit to this page from decission page - START
		$extract_data 				=  explode('/', $application_id);
		$plan_approval_number_exten =  $extract_data[0];
		$plan_approval_date_exten   =  $extract_data[1];
	
	//for first time visit to this page from decission page - END
	
  	$plan_approve_status 	= encryption_decryption_fun('decrypt', $val['plan_approve_status_hidden']);
 
    if(empty($plan_approve_status)||  $plan_approve_status == '' || $plan_approve_status == NULL){
				$reference_no = created_referenceno();
	}else{
			$get_fa_cafa = get_fa_cafa($application_id);
            $reference_no = $get_fa_cafa['reference_number'];
	}
    
    /* register office - if same as factory address */
    $addr_same                = $form_state['values']['addr_same'];
    //$same_address_communication = $val['same_address_communication'];
    $same_as_address_occupier = $val['same_as_address_occupier'];
    
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
    } else {
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
    
    /* occupier present address - if same as occupier permanent address */
    if (!empty($val['same_as_address_occupier']) && ($val['same_as_address_occupier'] == 1)) {
        $pincodeoprsntadr        = $val['pincodeoprmntadr'];
        $state_oprsntadr         = $val['state_oprmntadr'];
        $district_oprsntadr      = $val['district_oprmntadr'];
        $subdivision_oprsntadr   = $val['subdivision_oprmntadr'];
        $areatype_oprsntadr      = $val['areatype_oprmntadr'];
        $block_oprsntadr         = $val['block_oprmntadr'];
        $panchayat_oprsntadr     = $val['panchayat_oprmntadr'];
        $policestation_oprsntadr = $val['policestation_oprmntadr'];
        $postoffice_oprsntadr    = $val['postoffice_oprmntadr'];
        $addrline_oprsntadr      = $val['addrline_oprmntadr'];
    } else {
        $pincodeoprsntadr        = $val['pincodeoprsntadr'];
        $state_oprsntadr         = $val['state_oprsntadr'];
        $district_oprsntadr      = $val['district_oprsntadr'];
        $subdivision_oprsntadr   = $val['subdivision_oprsntadr'];
        $areatype_oprsntadr      = $val['areatype_oprsntadr'];
        $block_oprsntadr         = $val['block_oprsntadr'];
        $panchayat_oprsntadr     = $val['panchayat_oprsntadr'];
        $policestation_oprsntadr = $val['policestation_oprsntadr'];
        $postoffice_oprsntadr    = $val['postoffice_oprsntadr'];
        $addrline_oprsntadr      = $val['addrline_oprsntadr'];
    }
	
	if($plan_approve_status == 'ABk') { $planstatus = 'ABk';}
	else { $planstatus = 'In';}
   
    $cafa_Info = array(
        'factory_name' 				=> $val['factory_name'],
        'factory_previous_name' 	=> $val['factory_previous_name'],
        'factory_location' 			=> $val['factory_location'],
        'factory_zone' 				=> $val['factory_zone'],
        
        // factory address
        'pincode' 					=> $val['pincode'],
        'state' 					=> $val['state'],
        'district' 					=> $val['district'],
        'subdivision' 				=> $val['subdivision'],
        'areatype' 					=> $val['areatype'],
        'block' 					=> $val['block'],
        'panchayat' 				=> $val['panchayat'],
        'policestation' 			=> $val['policestation'],
        'postoffice' 				=> $val['postoffice'],
        'addrline' 					=> $val['addrline'],
        
        // register office - if same as factory address
        'pincodeoff' 				=> $pincodeoff,
        'state_off' 				=> $state_off,
        'district_off' 				=> $district_off,
        'subdivision_off' 			=> $subdivision_off,
        'areatype_off' 				=> $areatype_off,
        'block_off' 				=> $block_off,
        'panchayat_off' 			=> $panchayat_off,
        'policestation_off' 		=> $policestation_off,
        'postoffice_off' 			=> $postoffice_off,
        'addrline_off' 				=> $addrline_off,

		'comm_telephone'   	    	=> $val['comm_telephone'],
		'comm_mobile'     	    	=> $val['comm_mobile'],
		'comm_fax'     	        	=> $val['comm_fax'],
		'comm_email'     	    	=> $val['comm_email'],
        
        'factory_pan' 				=> $val['factory_pan'],
		'factory_owershiptype'		=> $val['ownership_type'],
	    'occupier_type '		    => $val['occupier_type'],
        'occupier_nationality' 		=> $val['occupier_nationality'],
        'occupier_aadhaar' 			=> $val['occupier_aadhaar'],
		'occupier_passport' 		=> $val['occupier_passport'],
        'occupier_name' 			=> $val['occupier_name'],
        'occupier_mobile' 			=> $val['occupier_mobile'],
        'occupier_email_id' 		=> $val['occupier_email_id'],
		'occupier_age'   		    => $val['occupier_age'],
		'occupier_gurdian_name'  	=> $val['occupier_gurdian_name'],
		'occupier_fax_no'        	=> $val['occupier_fax_no'],
		'occupier_telephone'     	=> $val['occupier_telephone'],
		
        // occupier present address
        'pincodeoprmntadr' 			=> $val['pincodeoprmntadr'],
        'state_oprmntadr' 			=> $val['state_oprmntadr'],
        'district_oprmntadr' 		=> $val['district_oprmntadr'],
        'subdivision_oprmntadr' 	=> $val['subdivision_oprmntadr'],
        'areatype_oprmntadr' 		=> $val['areatype_oprmntadr'],
        'block_oprmntadr' 			=> $val['block_oprmntadr'],
        'panchayat_oprmntadr' 		=> $val['panchayat_oprmntadr'],
        'policestation_oprmntadr' 	=> $val['policestation_oprmntadr'],
        'postoffice_oprmntadr' 		=> $val['postoffice_oprmntadr'],
        'addrline_oprmntadr' 		=> $val['addrline_oprmntadr'],
        
        // occupier present address - if same as occupier permanent address
        'pincodeoprsntadr' 			=> $pincodeoprsntadr,
        'state_oprsntadr' 			=> $state_oprsntadr,
        'district_oprsntadr' 		=> $district_oprsntadr,
        'subdivision_oprsntadr' 	=> $subdivision_oprsntadr,
        'areatype_oprsntadr' 		=> $areatype_oprsntadr,
        'block_oprsntadr' 			=> $block_oprsntadr,
        'panchayat_oprsntadr'		=> $panchayat_oprsntadr,
        'policestation_oprsntadr' 	=> $policestation_oprsntadr,
        'postoffice_oprsntadr' 		=> $postoffice_oprsntadr,
        'addrline_oprsntadr' 		=> $addrline_oprsntadr,
        
        // owner premises address
        'owner_name' 				=> $val['owner_name'],
        'pincodepremises' 			=> $val['pincodepremises'],
        'state_premises'		 	=> $val['state_premises'],
        'district_premises' 		=> $val['district_premises'],
        'subdivision_premises' 		=> $val['subdivision_premises'],
        'areatype_premises' 		=> $val['areatype_premises'],
        'block_premises' 			=> $val['block_premises'],
        'panchayat_premises' 		=> $val['panchayat_premises'],
        'policestation_premises' 	=> $val['policestation_premises'],
        'postoffice_premises' 		=> $val['postoffice_premises'],
        'addrline_premises' 		=> $val['addrline_premises'],
        
		'plan_approve_status' 		=> $planstatus,
		'plant_installed'		    => $val['plant_installed'],
        //'final_status' => 'F', //plan_approve_
		
		'backlog_registration_no'   => $val['factory_registrstion_no'],
		'backlog_registration_date' => $val['registration_date'],
		'backlog_license_number'    => $val['factory_license_no'],
		'backlog_license_date'      => $val['license_date'],
		'backlog_classification_no' => $val['classification_no'],
		
        'service_id' 				=> $service_id,
        'factory_typeid' 			=> $factory_type_id,
        'created_by' 				=> $userid,
        'reg_adress_same_factory' 	=> $addr_same,
        'occupier_present_address_same' => $same_as_address_occupier,
        'reference_number'  		=> $reference_no,
		
		'is_backlog' 				 => 1,
		'backlog_plan_approval_no'   => !empty($backlogplanapproval_no) ? $backlogplanapproval_no : $plan_approval_number_exten,
		'backlog_plan_approval_date' => !empty($backlogplanapproval_date) ? $backlogplanapproval_date : $plan_approval_date_exten,
		'created_date' 			     => date('Y-m-d H:i:s'),
		'railway_station'  			=> $val['railway_station']
    );

	if (count($extract_data) == '2') {
		$id = db_insert('fa_cafa')->fields($cafa_Info)->execute();

    	if ($id) {
			
		$occupier_details = array(
		  'type_occupier' 					=> $val['occupier_type'],
		  'name_occupier' 					=> $val['occupier_name'],
		  'age_occupier'					=> $val['occupier_age'],
		  'father_husband_name_occupier'	=> $val['occupier_gurdian_name'],
		  'pincode_occupier'				=> $val['pincodeoprmntadr'],
		  'state_occupier'				    => $val['state_oprmntadr'],
		  'district_occupier'				=> $val['district_oprmntadr'],
		  'sub_division_occupier'			=> $val['subdivision_oprmntadr'],
		  'area_type_occupier'				=> $val['areatype_oprmntadr'],
		  'block_mun_cor_sez_not_occupier'	=> $val['block_oprmntadr'],
		  'grm_ward_sector_not_occupier'	=> $val['panchayat_oprmntadr'],
		  'police_station_occupier'			=> $val['policestation_oprmntadr'],
		  'post_office_occupier'			=> $val['postoffice_oprmntadr'],
		  'adress_line1_occupier'			=> $val['addrline_oprmntadr'],
		  'add_year_occupier'				=> date('Y'),
		  'occupier_service_id'				=> $service_id,
		  'application_occupier_id'			=> $id,
		  'factory_type_id'					=> $factory_type_id,
		  'application_reference_no'		=> $reference_no,
		  'worker_plan_approval_status'		=> 'In',
		  
		  'created_by'						=> $uid,
		  'created_date'					=> date('Y-m-d H:i:s'),
		  'active_inactive_occupier'		=> 1,
		  'occupier_nationality'			=> $val['occupier_nationality'],
		  'occupier_aadhaar'				=> $val['occupier_aadhaar'],
		  'occupier_passport'				=> $val['occupier_passport'],
		  'occupier_mobile'					=> $val['occupier_mobile'],
		  'occupier_email_id'				=> $val['occupier_email_id'],
		  'occupier_fax_no'					=> $val['occupier_fax_no'],
		  'occupier_telephone'				=> $val['occupier_telephone'],
		  
		  'pincode_occupier_present'				=> $val['pincodeoprsntadr'],
		  'state_occupier_present'				    => $val['state_oprsntadr'],
		  'district_occupier_present'				=> $val['district_oprsntadr'],
		  'sub_division_occupier_present'			=> $val['subdivision_oprsntadr'],
		  'area_type_occupier_present'				=> $val['areatype_oprsntadr'],
		  'block_mun_cor_sez_not_occupier_present'	=> $val['block_oprsntadr'],
		  'grm_ward_sector_not_occupier_present'	=> $val['panchayat_oprsntadr'],
		  'police_station_occupier_present'			=> $val['policestation_oprsntadr'],
		  'post_office_occupier_present'			=> $val['postoffice_oprsntadr'],
		  'adress_line1_occupier_present'			=> $val['addrline_oprsntadr'],
		);				
		
		db_insert('fa_occupier_details')->fields($occupier_details)->execute();
		
		drupal_set_message('Factory Information has been saved successfully.');
		drupal_goto('applicant/caf_extn/details-worker-hp-extension/' . $val['serviceid_hidden'] . '/' . $val['factorytypeid_hidden'].'/'.encryption_decryption_fun('encrypt',$id));
   
    	}
	} else {
		
		$queryabc = db_update('fa_cafa');
        $queryabc->fields($cafa_Info);
        $queryabc->condition('id', $application_id, '=');
        $queryabc->execute();

		$occupier_details = array(
			  'type_occupier' 					=> $val['occupier_type'],
			  'name_occupier' 					=> $val['occupier_name'],
			  'age_occupier'					=> $val['occupier_age'],
			  'father_husband_name_occupier'	=> $val['occupier_gurdian_name'],
			  'pincode_occupier'				=> $val['pincodeoprmntadr'],
			  'state_occupier'				    => $val['state_oprmntadr'],
			  'district_occupier'				=> $val['district_oprmntadr'],
			  'sub_division_occupier'			=> $val['subdivision_oprmntadr'],
			  'area_type_occupier'				=> $val['areatype_oprmntadr'],
			  'block_mun_cor_sez_not_occupier'	=> $val['block_oprmntadr'],
			  'grm_ward_sector_not_occupier'	=> $val['panchayat_oprmntadr'],
			  'police_station_occupier'			=> $val['policestation_oprmntadr'],
			  'post_office_occupier'			=> $val['postoffice_oprmntadr'],
			  'adress_line1_occupier'			=> $val['addrline_oprmntadr'],
			  'add_year_occupier'				=> date('Y'),
			  'occupier_service_id'				=> encryption_decryption_fun('decrypt', $val['serviceid_hidden']),
			  'application_occupier_id'			=> $application_id,
			  'factory_type_id'					=> encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']),
			  'application_reference_no'		=> $reference_no,
			  'worker_plan_approval_status'		=> 'AI',
			  
			  'created_by'						=> $uid,
			  'active_inactive_occupier'		=> 1,
			  'occupier_nationality'			=> $val['occupier_nationality'],
			  'occupier_aadhaar'				=> $val['occupier_aadhaar'],
			  'occupier_passport'				=> $val['occupier_passport'],
			  'occupier_mobile'					=> $val['occupier_mobile'],
			  'occupier_email_id'				=> $val['occupier_email_id'],
			  'occupier_fax_no'					=> $val['occupier_fax_no'],
			  'occupier_telephone'				=> $val['occupier_telephone'],
			  
			  'pincode_occupier_present'				=> $val['pincodeoprsntadr'],
			  'state_occupier_present'				    => $val['state_oprsntadr'],
			  'district_occupier_present'				=> $val['district_oprsntadr'],
			  'sub_division_occupier_present'			=> $val['subdivision_oprsntadr'],
			  'area_type_occupier_present'				=> $val['areatype_oprsntadr'],
			  'block_mun_cor_sez_not_occupier_present'	=> $val['block_oprsntadr'],
			  'grm_ward_sector_not_occupier_present'	=> $val['panchayat_oprsntadr'],
			  'police_station_occupier_present'			=> $val['policestation_oprsntadr'],
			  'post_office_occupier_present'			=> $val['postoffice_oprsntadr'],
			  'adress_line1_occupier_present'			=> $val['addrline_oprsntadr'],
			);		
						
		$queryabc = db_update('fa_occupier_details');
        $queryabc->fields($occupier_details);
        $queryabc->condition('application_occupier_id', $application_id, '=');
		$queryabc->condition('application_reference_no', $reference_no, '=');
        $queryabc->execute();
		
		drupal_goto('applicant/caf_extn/details-worker-hp-extension/'.$val['serviceid_hidden'].'/'.$val['factorytypeid_hidden'].'/'.$val['applicationid_hidden']);
    }
    $form_state['rebuild'] = true;
}


?> 