<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function caf_form_renewal_parta($form, &$form_state, $appid, $serviceid,$date)
{
	global $base_root, $base_path;
	$form            	= array();
	$form['#attributes']= array('enctype' => "multipart/form-data");
	$application_id     = encryption_decryption_fun('decrypt', $appid);
	$service_id 		= encryption_decryption_fun('decrypt', $serviceid);
	$reg_lic_date 		= encryption_decryption_fun('decrypt', $date);

	$get_fa_cafa           = get_fa_cafa($application_id);
	
    $factory_name          = '';
    $factory_previous_name = '';
    $factory_location      = '';
    
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
    
    $factory_pan              = '';
	
    $owner_name                   = '';
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

    
    if (!empty($application_id)) {
        $get_fa_cafa           = get_fa_cafa($application_id);
        //print_r($get_fa_cafa);die();
        $factory_name          = $get_fa_cafa['factory_name'];
        $factory_previous_name = $get_fa_cafa['factory_previous_name'];
        $factory_location      = $get_fa_cafa['factory_location'];
		$factory_zone		   = $get_fa_cafa['factory_zone'];
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

		$factory_pan              = $get_fa_cafa['factory_pan'];
        $ownership_type	  		  = $get_fa_cafa['ownership_type'];
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
        
        $owner_name                   = $get_fa_cafa['owner_name'];
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
        
        $reg_adress_same_factory       = $get_fa_cafa['reg_adress_same_factory'];
        //$communication_adress_same_factory    = $get_fa_cafa['communication_adress_same_factory'];
        $occupier_present_address_same = $get_fa_cafa['occupier_present_address_same'];

        //New Field Added

        $trade_license_no                       = $get_fa_cafa['trade_license_no'];
       
        $reference_number                       = $get_fa_cafa['reference_number'];
        $application_status                     = $get_fa_cafa['application_status'];
        $is_backlog                             = $get_fa_cafa['is_backlog'];
		$is_backlog                             = $get_fa_cafa['is_backlog'];
		$date_of_amenability                    = $get_fa_cafa['date_of_amenability'];
		$period_for_application                 = $get_fa_cafa['period_for_application'];
		$owership_type							= $get_fa_cafa['factory_owershiptype'];
		$wbpcb_category_name 					= $get_fa_cafa['wbpcb_category_name'];
		$wbpcb_reference_no 					= $get_fa_cafa['wbpcb_reference_no'];
		$wbpcb_ref_date 						= $get_fa_cafa['wbpcb_ref_date'];
		$wbpcb_intimation_letter    			= $get_fa_cafa['wbpcb_intimation_letter'];
		$wbpcb_intimation_letter    			= $get_fa_cafa['wbpcb_intimation_letter'];
		$wbpcb_intimation_letter    			= $get_fa_cafa['wbpcb_intimation_letter'];
		$wbpcb_intimation_letter    			= $get_fa_cafa['wbpcb_intimation_letter'];
		$backlog_plan_approval_date				= $get_fa_cafa['backlog_plan_approval_date'];
		$backlog_plan_approval_no				= $get_fa_cafa['backlog_plan_approval_no'];
		$plan_approval_no						= $get_fa_cafa['factory_plan_approval_number'];
		$plan_approval_date						= $get_fa_cafa['plan_approval_date'];
        
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
        "govt" 			=> "Govt.",
		"psu" 			=> "PSU",
		"others" 		=> "Others",
 
    );
	
	$form['applicationid_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $appid
    );
	
	$form['serviceid_hidden']     = array(
        '#type' => 'hidden',
        '#default_value' => $serviceid
    );
    $form['factorytypeid_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => encryption_decryption_fun('decrypt',$get_fa_cafa['factory_type'])
    );
    $form['application_status_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => encryption_decryption_fun('encrypt', $application_status)
        
    );
	
	/********** Factory checking data **********/
	if (!empty($application_id) && $get_fa_cafa['application_status']=='B') {
	$checked =get_checking($application_id,$service_id,$factory_type_id,$reference_number);
	
	$verify_details      = ($checked['verify_details'])? $checked['verify_details'] : ''; 
	
	$remark_field = explode(',', $checked['verify_details']);
			foreach ($remark_field as $fieldname){
				if($fieldname == 'factory_name'){ $factory_name_ck = "readonly";}
				if($fieldname == 'ownership_type'){ $ownership_type_ck = "disabled";}
				if($fieldname == 'factory_pan'){ $factory_pan_ck = "readonly";}
				
				if($fieldname == 'plan_approval_no'){ $plan_approval_ck = "readonly";}
				if($fieldname == 'plan_approval_date'){ $plan_approval_date_ck = "readonly";}
				
				if($fieldname == 'zone_name'){ $zone_name_ck = "disabled";}
				if($fieldname == 'zone_name'){ $zone_name_ck2 = "readonly";}
				
				if($fieldname == 'factory_headoffice'){ $headoffice_address_ck = "disabled";}
				if($fieldname == 'factory_headoffice'){ $headoffice_address_ck2 = "readonly";}
				
				if($fieldname == 'telephone_no'){ $telephone_no_ck = "readonly";}
				if($fieldname == 'mobile_no'){ $mobile_no_ck 	= "readonly";}
				if($fieldname == 'fax_no'){ $fax_no_ck 	= "readonly";}
				if($fieldname == 'email_no'){ $email_no_ck 	= "readonly";}
				
				if($fieldname == 'owner_name'){ $owner_name_ck = "readonly";}
				if($fieldname == 'premises_address'){ $premises_address_ck = "disabled";}
				if($fieldname == 'premises_address'){ $premises_address_ck2 = "readonly";}
				
				
				if($fieldname == 'wbpcb_id'){ $wbpcb_id_ck = "disabled";}
				if($fieldname == 'wbpcb_reference_id'){ $wbpcb_reference_id_ck = "readonly";}
				if($fieldname == 'wbpcb_reference_date'){ $wbpcb_reference_date_ck = "readonly";}
				if($fieldname == 'intimation_id'){ $intimation_id_ck = "readonly";}
				
				

				
			}
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
        '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4"><label class="input label-block">',
        '#suffix' 			=> '</label></div>',
        '#title' 			=> t('(i). Name of the factory'),
        '#type' 			=> 'textfield',
        '#required' 		=> TRUE,
        '#default_value' 	=> $factory_name,
		'#attributes' 		=> array('class' => array( ''),$factory_name_ck => $factory_name_ck ),
      
    );
	$form['factory_part_info']['factory_owershiptype'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4"><label class="select label-block">',
        '#suffix' 			=> '</label></div>',
        '#title' 			=> t('(ii). Ownership Type'),
        '#type' 			=> 'select',
		'#required' 		=> TRUE,
		'#options' 			=> $ownershiptype,
        '#default_value' 	=> $owership_type,
		'#attributes'		=> array('class' => array( ''),$ownership_type_ck => $ownership_type_ck),
       
    );
	$form['factory_part_info']['factory_pan'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4"><label class="input label-block">',
        '#suffix' 			=> '</label></div></div>',
        '#title' 			=> t('(iii). PAN of the Business Establishment / Factory / Company'),
        '#type'				=> 'textfield',
        '#default_value' 	=> $factory_pan,
        '#required' 		=> TRUE,
		'#attributes' 		=> array( 'class' => array(''),$factory_pan_ck => $factory_pan_ck),
		'#description'		=>'<font color="#FF0000">(N.B.- Under the Income Tax Act, 1961)</font>'
    );
   $form['factory_part_info']['plan_approval_no'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4"><label class="input label-block">',
        '#suffix' 			=> '</label></div>',
        '#title' 			=> t('(iv). Plan Approval number'),
        '#type' 			=> 'textfield',
        '#required' 		=> TRUE,
        '#default_value' 	=> !empty($backlog_plan_approval_no)?$backlog_plan_approval_no:$plan_approval_no,
		'#attributes' 		=> array('class' => array( ''),'readonly' => 'readonly' ),
      
    );
	$form['factory_part_info']['plan_approval_date'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4"><label class="input label-block">',
        '#suffix' 			=> '</label></div></div>',
        '#title' 			=> t('(v). Plan Approval date'),
        '#type' 			=> 'textfield',
		'#required' 		=> TRUE,
		'#default_value' 	=> !empty($backlog_plan_approval_date)?$backlog_plan_approval_date:$plan_approval_date,
		'#attributes'		=> array('class' => array( ''),'readonly' => 'readonly'),
       
    );

   

    /********** Factory Information - End **********/
	
	/********** Location of the factory - Start **********/
	
	$form['factory_part_a'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('B. Location of the factory'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	
	$form['factory_part_a']['factory_zone'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4"><label class="select label-block">',
        '#suffix' 			=> '</label></div>',
        '#title' 			=> t('(i). Zone'),
        '#type' 			=> 'select',
		'#id'				=> 'factory_id',
		'#options' 			=> $factzonefinal1,
        '#required' 		=> TRUE,
        '#default_value' 	=> $factory_zone,
		'#attributes'		=> array('class' => array( ''),$zone_name_ck => $zone_name_ck),
		'#ajax' 			=> array(
                      					'effect' 	=> 'fade',
            							'callback' 	=> 'get_ajax_zone_name',
            							'progress' 	=> array(
                												'type' => 'throbber',
                												'message' => t('loading')
           													 )
        							)
        
    );
	
	$form['factory_part_a']['factory_zone_details'] = array(
        	'#prefix' 		=> '<div id="cb">',
			'#id'			=> 'test_id',
       		'#suffix' 		=> '</div>',
    );
	$zone_id   = isset($form_state['values']['factory_zone']) ? $form_state['values']['factory_zone'] : $factory_zone;
	if(!empty($zone_id)){
		$query 			= 	db_select('fa_zone', 'fz')
						->	fields('fz', array('zone_details'))
						->	condition('fz.zone_id', trim($zone_id), '=');
        $result 		= $query->execute();
		$final_boudary 	= $result->fetchAssoc();
        
		$form['factory_part_a']['factory_zone_details'] = array(
			'#prefix' 	=> '<div id="cb"><div class="col-md-12 col-xs-8"><label class="input label-block"><font color="green">',
			'#suffix' 	=> '</font></label></div></div>',
			'#type' 	=> 'markup',
			'#markup' 	=> t($final_boudary['zone_details']),
		);
	}
    
    $form['factory_part_a']['firstRowStart'] = array(
        '#prefix' 		=> '',
        '#suffix' 		=> '</div>'
    );
    $form['factory_part_a']['pincode']       = array(
        '#prefix' 				=> '<div class="row"><div class="col-md-4 col-xs-4"><label class="input label-block">',
        '#suffix' 				=> '</label></div>',
        '#attributes' 			=> array('class' => array(''),
        							'placeholder' 		=> 'Pincode',
		 							$zone_name_ck => $zone_name_ck
       							 ),
        '#autocomplete_path' 	=> 'pinautocomplete',
        '#maxlength' 			=> 6,
        '#title' 				=> t('(ii). Pincode'),
        '#default_value' 		=> $factory_pincode,
        '#required' 			=> TRUE,
        '#type' 				=> 'textfield',
        '#ajax' 				=> array(
                       						'effect' 	=> 'fade',
            								'callback' 	=> 'get_ajax_load',
            								'progress' 	=> array(
                									'type' 		=> 'throbber',
                									'message' 	=> t('loading')
            									)
        								)
    );
    $value_pincode = isset($form_state['values']['pincode']) ? $form_state['values']['pincode'] : $factory_pincode;
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
				'#title' 			=> '(iii). State',
				'#type' 			=> 'select',
				'#attributes' 		=> array(
											'class' 		=> array(''),
											'placeholder' 	=> 'State'
											),
				'#disabled' 		=> TRUE,
				'#options' 			=> get_all_state($state_v),
				'#value' 			=> !empty($state_v) ? $state_v : $factory_state,
				'#prefix' 			=> '<div id="ld_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#required' 	    => TRUE,
				'#ajax' 			=> array(
												'event' 	=> 'change',
												'effect' 	=> 'fade',
												'callback' 	=> 'get_ajax_load',
												'progress' 	=> array(
																		'type' 		=> 'throbber',
																		'message' 	=> t('loading')
																	)
												)
      		);
    	} else {
			$form['factory_part_a']['state'] = array(
				'#title' 		=> '(iii). State',
				'#type' 		=> 'select',
				'#disabled' 	=> TRUE,
				'#attributes' 	=> array(
										'class' 		=> array(''),
										'placeholder' 	=> 'State',
										'readonly' 		=> 'readonly'
										),
				'#options' 		=> array('' => t('Select State')),
				'#required' 	=> TRUE,
				'#prefix' 		=> '<div id="ld_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
				'#ajax' 		=> array(
										'event' 	=> 'change',
										'effect' 	=> 'fade',
										'callback' 	=> 'get_ajax_load',
										'progress' 	=> array(
										'type' 		=> 'throbber',
										'message' 	=> t('loading')
									)
								)
			);
    }
    
    $value_state = isset($form_state['values']['state']) ? $form_state['values']['state'] : $factory_state;
    
    if (!empty($state_v)) {
        $form['factory_part_a']['district'] = array(
            '#title' 		=> '(iv). District',
            '#type' 		=> 'select',
            '#disabled' 	=> TRUE,
            '#attributes' 	=> array('class' => array(''),
                						'placeholder' => 'District'
            						),
            '#options' 		=> get_district_by_id($state_v),
            '#value' 		=> !empty($district_v) ? $district_v : $factory_district,
			'#required' 	=> TRUE,
            '#prefix' 		=> '<div id="ld_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
            '#suffix' 		=> '</label></div></div>',
            '#ajax' 		=> array(
               						   	'event'   	=> 'change',
                						'effect' 	=> 'fade',
                						'callback' 	=> 'get_ajax_load',
                						'progress' 	=> array(
                    											'type' 		=> 'throbber',
                   												 'message' 	 => t('loading')
                											)
           							 )
        );
    } else {
        $form['factory_part_a']['district'] = array(
            '#title' 		=> '(iv). District',
            '#type' 		=> 'select',
            '#id' 			=> 'district_name',
            '#disabled' 	=> TRUE,
            '#attributes' 	=> array('class' => array(''),
                						'placeholder' => 'District'
            						),
            '#options' 		=> array('' => t('Select District')),
			'#required' 	=> TRUE,
            '#prefix' 		=> '<div id="ld_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
            '#suffix' 		=> '</label></div></div>'
        );
    }
    
    $form['factory_part_a']['firstRowEnd'] = array(
        '#prefix' 			=> '',
        '#suffix'			=> '</div>'
    );
    
    $value_district = isset($form_state['values']['district']) ? $form_state['values']['district'] : $factory_district;
    
    $form['factory_part_a']['secondRowStart'] = array(
        '#prefix' 		=> '<div class="row">',
        '#suffix' 		=> ''
    );
    
    if (!empty($district_v) && !empty($state_v)) {
        
        $form['factory_part_a']['subdivision'] = array(
            	'#title' 				=> '(v). Sub-Division',
            	'#type' 				=> 'select',
            	'#attributes' 			=> array('class' => array(''),
                							'placeholder' 			=> 'Sub Division',
											 $zone_name_ck => $zone_name_ck,
            								),
            	'#options' 				=> common_custom_user_subdivisionlist_list_new($district_v),
            	'#default_value' 		=> $factory_subdivision,
				'#required' 			=> TRUE,
            	'#prefix' 				=> '<div id="ld_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
           		'#suffix' 				=> '</label></div></div>',
            	'#ajax' 				=> array(
												'event' 	=> 'change',
												'effect' 	=> 'fade',
												'callback' 	=> 'get_ajax_load',
                								'progress' 	=> array(
                    												'type' 		=> 'throbber',
                    												'message' 	=> t('loading')
                												)
            								)
        );
    } else {
         $form['factory_part_a']['subdivision'] = array(
            		'#title'    	=> '(v). Sub-Division',
            		'#type'			=> 'select',
            		'#attributes' 	=> array('class' => array(''),
                						'placeholder' 			=> 'Sub Division',
										$zone_name_ck => $zone_name_ck,
            						),
            		'#options' 		=> array('' => t('Select Sub-Division')),
            		'#prefix' 		=> '<div id="ld_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
					'#required' 	=> TRUE,
            		'#suffix' 		=> '</label></div></div>'
        );
    }
    $value_subdivision = isset($form_state['values']['subdivision']) ? $form_state['values']['subdivision'] : $factory_subdivision;
    
    if (!empty($value_district) && !empty($value_state) && !empty($value_subdivision)) {
        $form['factory_part_a']['areatype'] = array(
           		'#title' 				=> '(vi). Area Type',
            	'#type' 				=> 'select',
           		'#attributes' 			=> array('class' => array(''),
                									'placeholder' 			=> 'Area Type',
													$zone_name_ck => $zone_name_ck,
            									),
            	'#options' 				=> common_custom_user_areatype_list_new($value_district, $value_subdivision),
            	'#default_value' 		=> $factory_areatype,
				'#required' 			=> TRUE,
            	'#prefix' 				=> '<div id="ld_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
            	'#suffix' 				=> '</label></div></div>',
            	'#ajax'					=> array(
												'event' 	=> 'change',
												'effect' 	=> 'fade',
												'callback' 	=> 'get_ajax_load',
												'progress' 	=> array(
																		'type' 		=> 'throbber',
																		'message' 	=> t('loading')
																	)
            								)
       	 );
    } else {
        $form['factory_part_a']['areatype'] = array(
            '#title' 				=> '(vi). Area Type',
            '#type' 				=> 'select',
            '#attributes' 			=> array('class' => array(''),
                								'placeholder' 			=> 'Area Type',
												$zone_name_ck 			=> $zone_name_ck,
           									 ),
            '#options' 				 => array('0' => t('Select Area Type')),
			'#required' 			 => TRUE,
            '#prefix' 				 => '<div id="ld_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
            '#suffix'				 => '</label></div></div>'
        );
    }
    
    $value_areatype = isset($form_state['values']['areatype']) ? $form_state['values']['areatype'] : $factory_areatype;
    
    if (!empty($value_district) && !empty($value_state) && $value_subdivision != "" && !empty($value_areatype)) {
        
        if ($value_areatype == 'B') {
            $areatype_name 		= 'Block';
        } elseif ($value_areatype == 'M') {
            $areatype_name 		= 'Municipality';
        } elseif ($value_areatype == 'C') {
            $areatype_name 		= 'Corporation';
        } elseif ($value_areatype == 'S') {
            $areatype_name 		= 'SEZ';
        } elseif ($value_areatype == 'N') {
            $areatype_name 		= 'Notified Area';
        }
        
        $form['factory_part_a']['block'] = array(
            	'#title' 				=> '(vii). '.$areatype_name,
            	'#type' 				=> 'select',
            	'#attributes' 			=> array('class' => array(''),
                									'placeholder' 			=> 'subdivision',
													$zone_name_ck 			=> $zone_name_ck,
            								),
            	'#options' 				=> common_custom_user_block_list_new($value_subdivision, $value_areatype),
            	'#default_value' 		=> $factory_block,
				'#required' 			=> TRUE,
            	'#prefix' 				=> '<div id="ld_empareatype_name_replace"><div class="col-md-4"><label class="select label-block">',
            	'#suffix' 				=> '</label></div></div>',
            	'#ajax' 				=> array(
													'event' 	=> 'change',
													'effect' 	=> 'fade',
													'callback' 	=> 'get_ajax_load',
													'progress' 	=> array(
																		'type' 		=> 'throbber',
																		'message' 	=> t('loading')
																		)
           										 )
        );
        
        
    } else {
        $form['factory_part_a']['block'] = array(
            '#title' 			=> '(vii). Block / Municipality / Corporation / Notified Area / SEZ',
            '#type' 			=> 'select',
            '#attributes' 		=> array(
                						'class' 				=> array(''),
                						'placeholder' 			=> 'subdivision',
										$zone_name_ck 			=> $zone_name_ck,
           							 ),
			'#required' 		=> TRUE,
           	'#options' 			=> array(
               								 '0' => t('Select Block / Municipality / Corporation / SEZ / Notified Area')
            							),
            '#prefix' 			=> '<div id="ld_empareatype_name_replace"><div class="col-md-4"><label class="select label-block">',
            '#suffix' 			=> '</label></div></div>'
        );
    }
    
    $form['factory_part_a']['secondRowEnd'] = array(
        	'#prefix' 	=> '',
        	'#suffix' 	=> '</div>'
    );
    
    $form['factory_part_a']['thirdRowStart'] = array(
        '#prefix' 	=> '<div class="row">',
        '#suffix' 	=> ''
    );
    $value_block   = isset($form_state['values']['block']) ? $form_state['values']['block'] : $factory_block;
    
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
            '#title' 			=> '(viii). '.$area_name,
            '#type' 			=> 'select',
            '#attributes' 		=> array(
										'class' 				=> array(''),
										'placeholder' 			=> 'panchayat',
										$zone_name_ck 			=> $zone_name_ck,
           							 ),
            '#options' 			=> common_custom_user_villward_list_new($value_block, $area_code),
            '#default_value' 	=> $factory_panchayat,
			'#required' 		=> TRUE,
            '#prefix' 			=> '<div id="ld_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
            '#suffix' 			=> '</label></div></div>',
            '#ajax' 			=> array(
											'event' 		=> 'change',
											'effect' 		=> 'fade',
											'callback' 		=> 'get_ajax_load',
											'progress' 		=> array(
																		'type' 		=> 'throbber',
																		'message' 	=> t('loading')
																	)
										)
        );
    } else {
        $form['factory_part_a']['panchayat'] = array(
           		 '#title' 					=> '(viii). Gram Panchayat/Ward/Sector',
            	 '#type' 					=> 'select',
            	 '#attributes' 				=> array('class' => array(''),
                 										'placeholder' 				=> 'panchayat',
														$zone_name_ck 				=> $zone_name_ck,
            										),
            	'#options' 					=> array('0' => t('Select Gram Panchayat / Ward / Sector / Notified Area')),
				'#required' 				=> TRUE,
            	'#prefix' 					=> '<div id="ld_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
            	'#suffix' 					=> '</label></div></div>'
        );
    }
    $value_panchayat = isset($form_state['values']['panchayat']) ? $form_state['values']['panchayat'] : $factory_panchayat;
    
    if (!empty($value_district) && !empty($value_subdivision) && !empty($value_areatype) && !empty($value_block) && !empty($value_state) && !empty($value_panchayat)) {
        $form['factory_part_a']['policestation'] = array(
            '#title' 			=> '(ix). Police Station',
            '#type' 			=> 'select',
            '#attributes' 		=> array('class' => array(''),
                							'placeholder' 			=> 'Police Station',
											$zone_name_ck 			=> $zone_name_ck,
           								 ),
            '#options' 			=> common_custom_user_ps_list_new($value_district),
            '#default_value' 	=> $factory_policestation,
			'#required' 		=> TRUE,
            '#prefix' 			=> '<div id="ld_empps_replace"><div class="col-md-4"><label class="select label-block">',
            '#suffix' 			=> '</label></div></div>'
        );
    } else {
        $form['factory_part_a']['policestation'] = array(
             '#title' 			=> '(ix). Police Station',
             '#type' 			=> 'select',
             '#attributes' 		=> array('class' => array(''),
                							'placeholder' 			=> 'Police Station',
											$zone_name_ck 			=> $zone_name_ck,
            							),
			 '#required' 		=> TRUE,
             '#options' 		=> array('0' => t('Select Police Station')),
             '#prefix' 			=> '<div id="ld_empps_replace"><div class="col-md-4"><label class="select label-block">',
             '#suffix' 			=> '</label></div></div>'
        );
    }
    
    if (!empty($pincode_v)) {
        $form['factory_part_a']['postoffice'] = array(
            '#title' 			=> '(x). Post Office',
            '#type' 			=> 'select',
            '#attributes' 		=> array('class' => array(''),
                						'placeholder' 			=> 'Post Office',
										$zone_name_ck 			=> $zone_name_ck,
           						 ),
            '#options' 			=> common_custom_post_office_list_new($pincode_v),
            '#default_value' 	=> $factory_postoffice,
			'#required' 		=> TRUE,
            '#prefix' 			=> '<div id="ld_post_office_div"><div class="col-md-4"><label class="select label-block">',
            '#suffix' 			=> '</label></div></div>'
        );
    } else {
        $form['factory_part_a']['postoffice'] = array(
            '#title' 			=> '(x). Post Office',
            '#type' 			=> 'select',
            '#attributes' 		=> array('class' => array(''),
                						'placeholder' 			=> 'Post Office',
										$zone_name_ck 			=> $zone_name_ck,
           						 ),
            '#options' 			=> common_custom_post_office_list_new($pincode_v),
           	'#required' 		=> TRUE,
            '#prefix' 			=> '<div id="ld_post_office_div"><div class="col-md-4"><label class="select label-block">',
            '#suffix' 			=> '</label></div></div>'
		);
    }
	$form['factory_part_a']['addrline'] = array(
            '#title' 			=> '(xi). Address',
            '#type' 			=> 'textarea',
            '#attributes' 		=> array('class' => array(''),
                						'placeholder' 			=> 'Post Office',
										$zone_name_ck2 			=> $zone_name_ck2,
           						 ),
            '#default_value' 	=> $factory_addrline,
           	'#required' 		=> TRUE,
            '#prefix' 			=> '<div class="col-md-12"><label class="textarea label-block">',
        	'#suffix' 			=> '</label></div>'
		);
    
    
    $form['factory_part_a']['thirdRowEnd'] = array(
        '#prefix' => '',
        '#suffix' => '</div>'
        
    );
    
    /********** Location of the factory - End **********/
	
	/********** Address of the Registered office / Head office - Start **********/
	
    $form['factory_part_off']              = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('C. Address of the Registered office / Head office'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE ,
		'#description' 		=> t('<font color="#FF0000">(N.B.:- This address will be treated as communication address as per Section 7 of Factories Act, 1948)</font>')
		
    );
	/*$form['factory_part_off']['addres_defination'] = array(
            '#type' 			=> 'markup',
            '#prefix' 			=> '<div class="row"><div class="col-md-12"><label class="input">',
            '#suffix' 			=> '</label></div><div>',
            '#markup' 			=> t('<font color="#FF0000">(N.B:-This address will be treated as communication address as per Section 7 of Factories Act,1948 )</font>')
        );*/
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
    }
    
    
    if ($checkbox == 0) {
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
            '#title' 			  => t('(ii). Pincode'),
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
                '#title' 			=> '(xi). Address',
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
	/*$form['factory_part_off']['addres_defination'] = array(
            '#type' 			=> 'markup',
            '#prefix' 			=> '<div class="row"><div class="col-md-12"><label class="input">',
            '#suffix' 			=> '</label></div><div>',
            '#markup' 			=> t('<font color="#FF0000">(N.B:-This address will be treated as communication address as per Section 7 of Factories Act,1948 )</font>')
        );*/
	  $form['factory_part_off']['comm_telephone'] = array(
			'#prefix' 			=> '<div class="col-md-3"><label class="input label-block">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t('(xii). Telephone No.'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> $comm_telephone,
			'#attributes' 		=> array( 'class' => array(''),$telephone_no_ck => $telephone_no_ck)
		 );
	 $form['factory_part_off']['comm_mobile'] = array(
			'#prefix'		 	=> '<div class="col-md-3"><label class="input label-block">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t('(xiii). Mobile No.'),
			'#type' 			=> 'textfield',
		 	'#default_value' 	=> $comm_mobile,
			'#attributes' 		=> array( 'class' => array(''),$mobile_no_ck => $mobile_no_ck)
   		 );
	$form['factory_part_off']['comm_fax'] = array(
			'#prefix' 			=> '<div class="col-md-3"><label class="input label-block">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t('(xiv). Fax No.'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> $comm_fax,
			'#attributes' 		=> array( 'class' => array(''),$fax_no_ck => $fax_no_ck)
    	);
    
	$form['factory_part_off']['comm_email'] = array(
			'#prefix' 			=> '<div class="col-md-3"><label class="input label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t('(xv). Email Id'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> $comm_email,
			'#attributes' 		=> array( 'class' => array(''),$email_no_ck => $email_no_ck)
   		 );
	
    /********** Address of the Registered office / Head office - End **********/
    
    /********** Details of owner of the premises occupied as a factory - Start **********/
    
    $form['factory_part_premises'] = array(
        	'#type' 		=> 'fieldset',
        	'#title' 		=> t('D. Details of owner of the premises occupied as a factory'),
        	'#collapsible' 	=> TRUE, // Added
        	'#collapsed' 	=> FALSE // Added
    );
    
    
    $form['factory_part_premises']['firstRowStart'] = array(
        '#prefix' 			=> '<div class="row">',
        '#suffix' 			=> ''
    );
    $form['factory_part_premises']['owner_name']    = array(
        '#prefix' 			=> '<div class="col-md-12 col-xs-12"><label class="input label-block">',
        '#suffix' 			=> '</label></div>',
        '#title' 			=> t('(i). Name of the owner'),
        '#type' 			=> 'textfield',
        '#default_value' 	=> $owner_name,
        '#required' 		=> TRUE,
		'#attributes' 		=> array( 'class' => array(''),$owner_name_ck => $owner_name_ck)
		
    );
    $form['factory_part_premises']['pincodepremises'] = array(
                '#title' 			=> '(ii). Pincode',
                '#type' 			=> 'textfield',
                '#attributes' 		=> array('class' 				=> array(''),
                   						 	  $premises_address_ck 	=> $premises_address_ck,
											  'placeholder' 		=> 'Pincode'
               					 		),
                '#default_value' 	=> $owner_pincodepremises,
				'#required' 		=> TRUE,
				'#maxlength' 		=> 6,
				'#autocomplete_path'=> 'pinautocomplete',
                '#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input label-block">',
        		'#suffix' 			=> '</label></div>',
                '#ajax' 			=> array(
            						           'effect' 	=> 'fade',
            								   'callback' 	=> 'get_ajax_load_premises',
            								   'progress' 	=> array(
                													'type' 		=> 'throbber',
                													'message' 	=> t('loading')
            														)
											),
            );
  
    
    
    $value_pincode_premises 	= isset($form_state['values']['pincodepremises']) ? $form_state['values']['pincodepremises'] : $owner_pincodepremises;
    if (!empty($value_pincode_premises)) {
        
        $query_premises = db_select('fa_all_india_pin_code', 'p')->fields('p', array(
            'districtname',
            'statename',
            'pincode',
            'district_code',
            'state_code',
            'po_name'
        ))->condition('p.pincode', trim($value_pincode_premises), '=');
        
        $result_premises = $query_premises->execute();
        if ($result_premises->rowcount() > 0) {
            $final_premises       = $result_premises->fetchAssoc();
            $pincode_v_premises   = $value_pincode_premises;
            $state_v_premises     = $final_premises['state_code'];
            $district_v_premises  = $final_premises['district_code'];
            $post_office_premises = $final_premises['po_name'];
        }
    }
    
    if (!empty($state_v_premises)) {
		
		 $form['factory_part_premises']['state_premises'] = array(
                '#title' 			=> '(iii). State',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 				=> array(''),
                   						 	  $premises_address_ck 	=> $premises_address_ck,
											  
               					 		),
                '#value' 			=> !empty($state_v_premises) ? $state_v_premises : $owner_state_premises,
				'#options' 			=> get_all_state($state_v_premises),
				'#required' 		=> TRUE,
				'#disabled' 		=> TRUE,
				'#prefix' 			=> '<div id="premises_edit_emp_state_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
        		'#suffix' 			=> '</label></div></div>',
                '#ajax' 			=> array(
            						           'effect' 	=> 'fade',
            								   'callback' 	=> 'get_ajax_load_premises',
            								   'progress' 	=> array(
                													'type' 		=> 'throbber',
                													'message' 	=> t('loading')
            														)
											),
            );
        
    } else {
		
		$form['factory_part_premises']['state_premises'] = array(
                '#title' 			=> '(iii). State',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 				=> array(''),
                   						 	  $premises_address_ck 	=> $premises_address_ck,
											  
               					 		),
               
				'#options' 			=> array('' => t('Select State')),
				'#required' 		=> TRUE,
				'#disabled' 		=> TRUE,
				'#prefix' 			=> '<div id="premises_edit_emp_state_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
        		'#suffix' 			=> '</label></div></div>',
               
            );
       
    }
    
    $value_state_premises = isset($form_state['values']['state']) ? $form_state['values']['state_premises'] : $owner_state_premises;
    
    if (!empty($state_v_premises)) {
		$form['factory_part_premises']['district_premises'] = array(
                '#title' 			=> '(iv). District',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 				=> array(''),
                   						 	  $premises_address_ck 	=> $premises_address_ck,
											  
               					 		),
                '#value' 			=> !empty($district_v_premises) ? $district_v_premises : $owner_district_premises,
				'#options' 			=> get_district_by_id($state_v_premises),
				'#required' 		=> TRUE,
				'#disabled' 		=> TRUE,
				'#prefix' 			=> '<div id="premises_edit_emp_district_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
        		'#suffix' 			=> '</label></div></div>',
                '#ajax' 			=> array(
            						           'effect' 	=> 'fade',
            								   'callback' 	=> 'get_ajax_load_premises',
            								   'progress' 	=> array(
                													'type' 		=> 'throbber',
                													'message' 	=> t('loading')
            														)
											),
            );
        
    } else {
		$form['factory_part_premises']['district_premises'] = array(
                '#title' 			=> '(iv). District',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 				=> array(''),
                   						 	  $premises_address_ck 	=> $premises_address_ck,
											  
               					 		),
               	'#options' 			=> array('' => t('Select District')),
				'#required' 		=> TRUE,
				'#disabled' 		=> TRUE,
				'#prefix' 			=> '<div id="premises_edit_emp_district_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
        		'#suffix' 			=> '</label></div></div>',
                
            );
       
    }
    
    $form['factory_part_premises']['firstRowEnd'] = array(
        '#prefix' => '',
        '#suffix' => '</div>'
    );
    
    $value_district_premises = isset($form_state['values']['district_premises']) ? $form_state['values']['district_premises'] : $owner_district_premises;
    
    $form['factory_part_premises']['secondRowStart'] = array(
        '#prefix' => '<div class="row">',
        '#suffix' => ''
    );
    
    if (!empty($district_v_premises) && !empty($state_v_premises)) {
        $form['factory_part_premises']['subdivision_premises'] = array(
                '#title' 			=> '(v). Sub Division',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 				=> array(''),
                   						 	  $premises_address_ck 	=> $premises_address_ck,
											  
               					 		),
                '#default_value' 	=> $owner_subdivision_premises,
				'#options' 			=> common_custom_user_subdivisionlist_list_new($district_v_premises),
				'#required' 		=> TRUE,
				'#prefix' 			=> '<div id="premises_empsubdv_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
        		'#suffix' 			=> '</label></div></div>',
                '#ajax' 			=> array(
            						           'effect' 	=> 'fade',
            								   'callback' 	=> 'get_ajax_load_premises',
            								   'progress' 	=> array(
                													'type' 		=> 'throbber',
                													'message' 	=> t('loading')
            														)
											),
            );
       
    } else {
        $form['factory_part_premises']['subdivision_premises'] = array(
                '#title' 			=> '(v). Sub Division',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 				=> array(''),
                   						 	  $premises_address_ck 	=> $premises_address_ck,
											  
               					 		),
               
				'#options' 			=>  array('' => t('Select Sub-Division')),
				'#required' 		=> TRUE,
				'#prefix' 			=> '<div id="premises_empsubdv_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
        		'#suffix' 			=> '</label></div></div>',
                
            );
       
    }
    $value_subdivision_premises 	= isset($form_state['values']['subdivision_premises']) ? $form_state['values']['subdivision_premises'] : $owner_subdivision_premises;
    
    if (!empty($value_district_premises) && !empty($value_state_premises) && !empty($value_subdivision_premises)) {
		$form['factory_part_premises']['areatype_premises'] = array(
                '#title' 			=> '(vi). Area Type',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 				=> array(''),
                   						 	  $premises_address_ck 	=> $premises_address_ck,
											  
               					 		),
                '#default_value' 	=> $owner_areatype_premises,
				'#options' 			=> common_custom_user_areatype_list_new($value_district_premises, $value_subdivision_premises),
				'#required' 		=> TRUE,
				'#prefix' 			=> '<div id="premises_emp_areatype_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
        		'#suffix' 			=> '</label></div></div>',
                '#ajax' 			=> array(
            						           'effect' 	=> 'fade',
            								   'callback' 	=> 'get_ajax_load_premises',
            								   'progress' 	=> array(
                													'type' 		=> 'throbber',
                													'message' 	=> t('loading')
            														)
											),
            );
        
    } else {
		$form['factory_part_premises']['areatype_premises'] = array(
                '#title' 			=> '(vi). Area Type',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 				=> array(''),
                   						 	  $premises_address_ck 	=> $premises_address_ck,
											  
               					 		),
                
				'#options' 			=> array('0' => t('Select Area Type')),
				'#required' 		=> TRUE,
				'#prefix' 			=> '<div id="premises_emp_areatype_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
        		'#suffix' 			=> '</label></div></div>',
              
            );
    
        $form['factory_part_premises']['block_premises']    = array(
                '#prefix' => '<div id="premises_empareatype_name_replace">',
            	'#suffix' => '</div>'
        	);
    }
    
    $value_areatype_premises = isset($form_state['values']['areatype_premises']) ? $form_state['values']['areatype_premises'] : $owner_areatype_premises;
    
    if (!empty($value_district_premises) && !empty($value_state_premises) && $value_subdivision_premises != "" && !empty($value_areatype_premises)) {
        
        if ($value_areatype_premises == 'B') {
            $areatype_name_premises = 'Block';
        } elseif ($value_areatype_premises == 'M') {
            $areatype_name_premises = 'Municipality';
        } elseif ($value_areatype_premises == 'C') {
            $areatype_name_premises = 'Corporation';
        } elseif ($value_areatype_premises == 'S') {
            $areatype_name_premises = 'SEZ';
        } elseif ($value_areatype_premises == 'N') {
            $areatype_name_premises = 'Notified Area';
        }
        $form['factory_part_premises']['block_premises'] = array(
                '#title' 			=> '(vii). '.$areatype_name_premises,
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 				=> array(''),
                   						 	  $premises_address_ck 	=> $premises_address_ck,
											  
               					 		),
                '#default_value' 	=> $owner_block_premises,
				'#options' 			=> common_custom_user_block_list_new($value_subdivision_premises, $value_areatype_premises),
				'#required' 		=> TRUE,
				'#prefix' 			=> '<div id="premises_empareatype_name_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
        		'#suffix' 			=> '</label></div></div>',
                '#ajax' 			=> array(
            						           'effect' 	=> 'fade',
            								   'callback' 	=> 'get_ajax_load_premises',
            								   'progress' 	=> array(
                													'type' 		=> 'throbber',
                													'message' 	=> t('loading')
            														)
											),
         );
        
        
        
    } else {
		
		$form['factory_part_premises']['block_premises'] = array(
                '#title' 			=> '(vii). Block / Municipality / Corporation / SEZ / Notified Area',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 				=> array(''),
                   						 	  $premises_address_ck 	=> $premises_address_ck,
											  
               					 		),
             	'#options'		 => array('0' => t('Select Block / Municipality / Corporation / SEZ / Notified Area')
            ),
				'#required' 		=> TRUE,
				'#prefix' 			=> '<div id="premises_empareatype_name_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
        		'#suffix' 			=> '</label></div></div>',
                
         );
        
    }
    
    $form['factory_part_premises']['secondRowEnd'] = array(
        	'#prefix' 	=> '',
        	'#suffix' 	=> '</div>'
    );
    
    $form['factory_part_premises']['thirdRowStart'] = array(
        	'#prefix' 	=> '<div class="row">',
        	'#suffix' 	=> ''
    );
    $value_block_premises  = isset($form_state['values']['block_premises']) ? $form_state['values']['block_premises'] : $owner_block_premises;
    
    if (!empty($value_district_premises) && !empty($value_subdivision_premises) && !empty($value_areatype_premises) && !empty($value_block_premises) && !empty($value_state_premises)) {
        
        if ($value_areatype_premises == 'B') {
            $area_name_premises = 'Gram Panchayat';
            $area_code_premises = 'V';
        } elseif ($value_areatype_premises == 'M') {
            $area_name_premises = 'Ward';
            $area_code_premises = 'W';
        } elseif ($value_areatype_premises == 'C') {
            $area_name_premises = 'Ward';
            $area_code_premises = 'C';
        } elseif ($value_areatype_premises == 'S') {
            $area_name_premises = 'Sector';
            $area_code_premises = 'S';
        } elseif ($value_areatype_premises == 'N') {
            $area_name_premises = 'Notified Area';
            $area_code_premises = 'N';
        }
        $form['factory_part_premises']['panchayat_premises'] = array(
                '#title' 			=> '(viii). '.$area_name_premises,
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 				=> array(''),
                   						 	  $premises_address_ck 	=> $premises_address_ck,
											  
               					 		),
                '#default_value' 	=> $owner_block_premises,
				'#options' 			=> common_custom_user_villward_list_new($value_block_premises, $area_code_premises),
				'#required' 		=> TRUE,
				'#default_value' 	=> $owner_panchayat_premises,
				'#prefix' 			=> '<div id="premises_emp_vill_ward_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
        		'#suffix' 			=> '</label></div></div>',
                '#ajax' 			=> array(
            						           'effect' 	=> 'fade',
            								   'callback' 	=> 'get_ajax_load_premises',
            								   'progress' 	=> array(
                													'type' 		=> 'throbber',
                													'message' 	=> t('loading')
            														)
											),
         );
        
       
    } else {
		$form['factory_part_premises']['panchayat_premises'] = array(
                '#title' 			=> '(viii). Gram Panchayat / Ward / Sector',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 				=> array(''),
                   						 	  $premises_address_ck 	=> $premises_address_ck,
											  
               					 		),
                '#default_value' 	=> $owner_block_premises,
				'#options' 			=> array('0' => t('Select Gram Panchayat / Ward / Sector / Notified Area')),
				'#required' 		=> TRUE,
				'#prefix' 			=> '<div id="premises_emp_vill_ward_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
        		'#suffix' 			=> '</label></div></div>',
               
         );
        
    }
    $value_panchayat_premises = isset($form_state['values']['panchayat_premises']) ? $form_state['values']['panchayat_premises'] : $owner_panchayat_premises;
    
    
    
    if (!empty($value_district_premises) && !empty($value_subdivision_premises) && !empty($value_areatype_premises) && !empty($value_block_premises) && !empty($value_state_premises) && !empty($value_panchayat_premises)) {
        $form['factory_part_premises']['policestation_premises'] = array(
                '#title' 			=> '(ix). Police Station',
                '#type' 			=> 'select',
                '#attributes' 		=> array(	'class' 				=> array(''),
												'placeholder' 			=> 'Post Office',
                   						 	  	$premises_address_ck 	=> $premises_address_ck,
											  
               					 		),
                '#default_value' 	=> $owner_policestation_premises,
				'#options' 			=> common_custom_user_ps_list_new($value_district_premises),
				'#required' 		=> TRUE,
				'#prefix' 			=> '<div id="premises_empps_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
        		'#suffix' 			=> '</label></div></div>',
                
         );
      
        
        
        
    } else {
		$form['factory_part_premises']['policestation_premises'] = array(
                '#title' 			=> '(ix). Police Station',
                '#type' 			=> 'select',
                '#attributes' 		=> array(	'class' 				=> array(''),
												'placeholder' 			=> 'Post Office',
                   						 	  	$premises_address_ck 	=> $premises_address_ck,
											  
               					 		),
               	'#options' 			=> array('0' => t('Select Police Station')),
				'#required' 		=> TRUE,
				'#prefix' 			=> '<div id="premises_empps_replace"><div class="col-md-4 col-xs-12"><label class="select label-block">',
        		'#suffix' 			=> '</label></div></div>',
                
         );
        
    }
    
    if (!empty($pincode_v_premises)) {
		$form['factory_part_premises']['postoffice_premises'] = array(
                '#title' 			=> '(x). Post Office',
                '#type' 			=> 'select',
                '#attributes' 		=> array(	'class' 				=> array(''),
												'placeholder' 			=> 'Post Office',
                   						 	  	$premises_address_ck 	=> $premises_address_ck,
											  
               					 		),
			  	'#options' 			=> common_custom_post_office_list_new($pincode_v_premises),
            	'#default_value' 	=> $owner_postoffice_premises,
                '#required' 		=> TRUE,
				'#prefix' 			=> '<div id="premises_post_office_div"><div class="col-md-4 col-xs-12"><label class="select label-block">',
        		'#suffix' 			=> '</label></div></div>',
                
         );
        
    } else {
		$form['factory_part_premises']['postoffice_premises'] = array(
                '#title' 			=> '(x). Post Office',
                '#type' 			=> 'select',
                '#attributes' 		=> array(	'class' 				=> array(''),
												'placeholder' 			=> 'Post Office',
                   						 	  	$premises_address_ck 	=> $premises_address_ck,
											  
               					 		),
			  	'#options' 			=> array('0' => t('Select Post Office')),
            	'#required' 		=> TRUE,
				'#prefix' 			=> '<div id="premises_post_office_div"><div class="col-md-4 col-xs-12"><label class="select label-block">',
        		'#suffix' 			=> '</label></div></div>',
                
         );
		
      
        
    }
	
    $form['factory_part_premises']['addrline_premises'] = array(
                '#title' 			=> '(xi). Address',
				'#rows' 			=> 3,
                '#type' 			=> 'textarea',
                '#attributes' 		=> array(	'class' 				=> array(''),
												'placeholder' 			=> 'Post Office',
                   						 	  	$premises_address_ck2 	=> $premises_address_ck2,
											  
               					 		),
			  	'#default_value' 	=> $owner_addrline_premises,
            	'#required' 		=> TRUE,
				'#prefix' 			=> '<div id="addrline_premises_div"><div class="col-md-12 col-xs-12"><label class="textarea label-block">',
        		'#suffix' 			=> '</label></div></div>',
                
         );
	
    
		$form['factory_part_premises']['thirdRowEnd'] = array(
			'#prefix' 	=> '',
			'#suffix' 	=> '</div>'
		);
	
    
	
  
	
    $form['factory_catagory'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('E. Factory Identification according to WBPCB'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
    $form['factory_catagory']['markup_start'] = array(
	     	 '#prefix' =>'<div class="row">'	
			);
		
	$form['factory_catagory']['factory_pollution_type'] 	= array(
				'#prefix' 			=> '<div id="pollution_type_id"><div class="col-md-4 col-xs-12"><label class="select label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(i). Categories of wbpcb'),
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
			$file_url = $base_root.$base_path .get_uploaded_document_url($wbpcb_intimation_letter);
			//echo $file_url;die();
			$form['factory_catagory']['view_doc_file'] = array(
                		'#markup' => l(t('Back'),$file_url, array('html' => TRUE,))
   				 );
		}
		
	$form['factory_catagory']['doc_file'] = array(
					'#type' 				 => 'managed_file',
					'#title'				 => '(ii). letter of intimation :-',
					'#upload_validators' 	 => array('file_validate_extensions' => array('pdf'), 'file_validate_size' => array(50*1024*1024)),
					'#upload_location' 		 => 'public://upload/pollution_doc/',
					'#process' 				 => array('import_my_file_element_process'),
					'#attributes' 			 => array('id' => '','autocomplete' => 'off','class'=>array('form-control')),
					'#prefix' 				 => '<div id="edit-doc-file-ajax-wrapper">',
			  		'#suffix' 				 => '</div>',
					'#required' 			 => TRUE
			);
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
				'#title'			=> '(ii). Reference number of approval of arrangments',
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
				'#title' 			=> t('(iii). Date of approval of arrangments'),
			
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
    $form['back_link'] = array(
        
        '#markup' => l(t('<i class="fa fa-angle-left" aria-hidden="true"></i> Back'), 'applicant/applicant-dasboard/', array(
            'html' => TRUE,
            'attributes' => array(
                'class' => array(
                    'btn btn-dark pull-left'
                )
            )
        ))
    );
    if($application_status == 'I' || $application_status == 'B' || empty($application_status) || $application_status == 'In'){
    $form['submit'] = array(
        '#prefix' => '<div class="row"><div class="col-md-4">',
        '#suffix' => '</div></div></div>',
        '#attributes' => array(
            'class' => array(
                'btn btn-dark'
            )
        ),
        '#type' => 'submit',
        '#value' => 'Save & Continue'
    );
	}else{
		$form['markup'] = array(
       
        '#suffix' => '</div>',
        
        '#type' => 'markup',
       
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
function caf_form_registrstion_parta_validate($form, &$form_state) {
  	 
  if (isset($form_state['values']['factory_zone']) && !$form_state['values']['factory_zone']) {
    form_set_error('factory_zone', 'Please select the zone the Factory located at!');    
  }
  if (isset($form_state['values']['factory_owershiptype']) && !$form_state['values']['factory_owershiptype']) {
    form_set_error('factory_owershiptype', 'Please select the ownership type!');    
  }
  if (isset($form_state['values']['pincode']) && !$form_state['values']['pincode']) {
    form_set_error('pincode', 'Please enter a valid Pincode for Factory!');    
  }
  if (isset($form_state['values']['subdivision']) && !$form_state['values']['subdivision']) {
    form_set_error('subdivision', 'Please select a Subdivision for Factory!');    
  }
  if (isset($form_state['values']['areatype']) && !$form_state['values']['areatype']) {
    form_set_error('areatype', 'Please select an Area Type for Factory!');    
  }
  if (isset($form_state['values']['block']) && !$form_state['values']['block']) {
    form_set_error('block', 'Please select a Block/Municipality/Corporation/Notified Area/SEZ for Factory!');    
  }
  if (isset($form_state['values']['panchayat']) && !$form_state['values']['panchayat']) {
    form_set_error('panchayat', 'Please select a Gram Panchayat/Ward/Sector for Factory!');    
  }
  if (isset($form_state['values']['policestation']) && !$form_state['values']['policestation']) {
    form_set_error('policestation', 'Please enter a Police Station for Factory!');    
  }
  if (isset($form_state['values']['postoffice']) && !$form_state['values']['postoffice']) {
    form_set_error('postoffice', 'Please enter a Post Office for Factory!');    
  }
  if (isset($form_state['values']['addrline']) && !$form_state['values']['addrline']) {
    form_set_error('addrline', 'Please enter a Address for Factory!');    
  }

  //Registered office / Head office
  if (isset($form_state['values']['pincodeoff']) && !$form_state['values']['pincodeoff']) {
    form_set_error('pincodeoff', 'Please enter a valid Pincode for Registered office / Head office!');    
  }
  if (isset($form_state['values']['subdivision_off']) && !$form_state['values']['subdivision_off']) {
    form_set_error('subdivision_off', 'Please select a Subdivision for Registered office / Head office!');    
  }
  if (isset($form_state['values']['areatype_off']) && !$form_state['values']['areatype_off']) {
    form_set_error('areatype_off', 'Please select an Area Type for Registered office / Head office!');    
  }
  if (isset($form_state['values']['block_off']) && !$form_state['values']['block_off']) {
    form_set_error('block_off', 'Please select a Block/Municipality/Corporation/Notified Area/SEZ for Registered office / Head office!');    
  }
  if (isset($form_state['values']['panchayat_off']) && !$form_state['values']['panchayat_off']) {
    form_set_error('panchayat_off', 'Please select a Gram Panchayat/Ward/Sector for Registered office / Head office!');    
  }
  if (isset($form_state['values']['policestation_off']) && !$form_state['values']['policestation_off']) {
    form_set_error('policestation_off', 'Please enter a Police Station for Registered office / Head office!');    
  }
  if (isset($form_state['values']['postoffice_off']) && !$form_state['values']['postoffice_off']) {
    form_set_error('postoffice_off', 'Please enter a Post Office for Registered office / Head office!');    
  }
  if (isset($form_state['values']['addrline_off']) && !$form_state['values']['addrline_off']) {
    form_set_error('addrline_off', 'Please enter a Address for Registered office / Head office!');    
  }

   //Occupier Permanent Address
  if (isset($form_state['values']['pincodeoprmntadr']) && !$form_state['values']['pincodeoprmntadr']) {
    form_set_error('pincodeoprmntadr', 'Please enter a valid Pincode for Occupier Permanent Address!');    
  }
  if (isset($form_state['values']['subdivision_oprmntadr']) && !$form_state['values']['subdivision_oprmntadr']) {
    form_set_error('subdivision_oprmntadr', 'Please select a Subdivision for Occupier Permanent Address!');    
  }
  if (isset($form_state['values']['areatype_oprmntadr']) && !$form_state['values']['areatype_oprmntadr']) {
    form_set_error('areatype_oprmntadr', 'Please select an Area Type for Occupier Permanent Address!');    
  }
  if (isset($form_state['values']['block_oprmntadr']) && !$form_state['values']['block_oprmntadr']) {
    form_set_error('block_oprmntadr', 'Please select a Block/Municipality/Corporation/Notified Area/SEZ for Occupier Permanent Address!');    
  }
  if (isset($form_state['values']['panchayat_oprmntadr']) && !$form_state['values']['panchayat_oprmntadr']) {
    form_set_error('panchayat_oprmntadr', 'Please select a Gram Panchayat/Ward/Sector for Occupier Permanent Address!');    
  }
  if (isset($form_state['values']['policestation_oprmntadr']) && !$form_state['values']['policestation_oprmntadr']) {
    form_set_error('policestation_oprmntadr', 'Please enter a Police Station for Occupier Permanent Address!');    
  }
  if (isset($form_state['values']['postoffice_oprmntadr']) && !$form_state['values']['postoffice_oprmntadr']) {
    form_set_error('postoffice_oprmntadr', 'Please enter a Post Office for Occupier Permanent Address!');    
  }
  if (isset($form_state['values']['addrline_oprmntadr']) && !$form_state['values']['addrline_oprmntadr']) {
    form_set_error('addrline_oprmntadr', 'Please enter a Address for Occupier Permanent Address!');    
  }

   //Occupier Present Address
  if (isset($form_state['values']['pincodeoprsntadr']) && !$form_state['values']['pincodeoprsntadr']) {
    form_set_error('pincodeoprsntadr', 'Please enter a valid Pincode for Occupier Present Address!');    
  }
  if (isset($form_state['values']['subdivision_oprsntadr']) && !$form_state['values']['subdivision_oprsntadr']) {
    form_set_error('subdivision_oprsntadr', 'Please select a Subdivision for Occupier Present Address!');    
  }
  if (isset($form_state['values']['areatype_oprsntadr']) && !$form_state['values']['areatype_oprsntadr']) {
    form_set_error('areatype_oprsntadr', 'Please select an Area Type for Occupier Present Address!');    
  }
  if (isset($form_state['values']['block_oprsntadr']) && !$form_state['values']['block_oprsntadr']) {
    form_set_error('block_oprsntadr', 'Please select a Block/Municipality/Corporation/Notified Area/SEZ for Occupier Present Address!');    
  }
  if (isset($form_state['values']['panchayat_oprsntadr']) && !$form_state['values']['panchayat_oprsntadr']) {
    form_set_error('panchayat_oprsntadr', 'Please select a Gram Panchayat/Ward/Sector for Occupier Present Address!');    
  }
  if (isset($form_state['values']['policestation_oprsntadr']) && !$form_state['values']['policestation_oprsntadr']) {
    form_set_error('policestation_oprsntadr', 'Please enter a Police Station for Occupier Present Address!');    
  }
  if (isset($form_state['values']['postoffice_oprsntadr']) && !$form_state['values']['postoffice_oprsntadr']) {
    form_set_error('postoffice_oprsntadr', 'Please enter a Post Office for Occupier Present Address!');    
  }
  if (isset($form_state['values']['addrline_oprsntadr']) && !$form_state['values']['addrline_oprsntadr']) {
    form_set_error('addrline_oprsntadr', 'Please enter a Address for Occupier Present Address!');    
  }

  //Owner Factory Address
  if (isset($form_state['values']['pincodepremises']) && !$form_state['values']['pincodepremises']) {
    form_set_error('pincodepremises', 'Please enter a valid Pincode for Owner Factory Address!');    
  }
  if (isset($form_state['values']['subdivision_premises']) && !$form_state['values']['subdivision_premises']) {
    form_set_error('subdivision_premises', 'Please select a Subdivision for Owner Factory Address!');    
  }
  if (isset($form_state['values']['areatype_premises']) && !$form_state['values']['areatype_premises']) {
    form_set_error('areatype_premises', 'Please select an Area Type for Owner Factory Address!');    
  }
  if (isset($form_state['values']['block_premises']) && !$form_state['values']['block_premises']) {
    form_set_error('block_premises', 'Please select a Block/Municipality/Corporation/Notified Area/SEZ for Owner Factory Address!');    
  }
  if (isset($form_state['values']['panchayat_premises']) && !$form_state['values']['panchayat_premises']) {
    form_set_error('panchayat_premises', 'Please select a Gram Panchayat/Ward/Sector for Owner Factory Address!');    
  }
  if (isset($form_state['values']['policestation_premises']) && !$form_state['values']['policestation_premises']) {
    form_set_error('policestation_premises', 'Please enter a Police Station for Owner Factory Address!');    
  }
  if (isset($form_state['values']['postoffice_premises']) && !$form_state['values']['postoffice_premises']) {
    form_set_error('postoffice_premises', 'Please enter a Post Office for Owner Factory Address!');    
  }
  if (isset($form_state['values']['addrline_premises']) && !$form_state['values']['addrline_premises']) {
    form_set_error('addrline_premises', 'Please enter a Address for Owner Factory Address!');    
  }

  $comm_telephone = $form_state['values']['comm_telephone'];
  if (!preg_match('/^[0-9]*$/', $comm_telephone)) {
    form_set_error('comm_telephone', t('Telephone should be numeric only!!'));
  }
  if ($form_state['values']['comm_telephone']!="" && (strlen($form_state['values']['comm_telephone'])<10 || strlen($form_state['values']['comm_telephone'])>10)) {
	form_set_error('comm_telephone', 'Telephone should be of 10 digit');    
  }

  $comm_mobile = $form_state['values']['comm_mobile'];
  if (!preg_match('/^[0-9]*$/', $comm_mobile)) {
    form_set_error('comm_mobile', t('Mobile should be numeric only!!'));
  }
 
  
  if ($form_state['values']['comm_mobile']!="" && (strlen($form_state['values']['comm_mobile'])<10 || strlen($form_state['values']['comm_mobile'])>10)) {
	form_set_error('comm_mobile', 'Mobile should be of 10 digit');    
  }

  $comm_fax = $form_state['values']['comm_fax'];
  if (!preg_match('/^[0-9]*$/', $comm_fax)) {
    form_set_error('comm_fax', t('Fax should be numeric only!!'));
  }
  
  $comm_email = $form_state['values']['comm_email'];
	if (!filter_var($comm_email, FILTER_VALIDATE_EMAIL)) {
	form_set_error('comm_email', t('Please enter a Valid Email Id!')); 
  }
  
  $factory_pan = $form_state['values']['factory_pan'];
	if (!preg_match('/^[a-zA-Z0-9]/', $factory_pan)) {  
    form_set_error('factory_pan', t('PAN should be alphanumeric only!!'));
  }
  if ($form_state['values']['factory_pan']!="" && (strlen($form_state['values']['factory_pan'])<10 || strlen($form_state['values']['factory_pan'])>10)) {
	form_set_error('factory_pan', 'PAN should be of 10 digit');    
   }
 
  if (isset($form_state['values']['occupier_nationality']) && !$form_state['values']['occupier_nationality']) {
    form_set_error('occupier_nationality', 'Please select an occupier Nationality!');    
  }	
 
  $owner_name = $form_state['values']['owner_name'];
	if (!preg_match('/[A-Za-z]+$/', $owner_name)) {  
    form_set_error('owner_name', t('Owner Name should be text only!!'));
  }	
  $occupier_telephone = $form_state['values']['occupier_telephone'];
  if (!preg_match('/^[0-9]*$/', $occupier_telephone)) {
    form_set_error('occupier_telephone', t('Occupier Telephone should be numeric only!!'));
  }
  if ($form_state['values']['occupier_telephone']!="" && (strlen($form_state['values']['occupier_telephone'])<10 || strlen($form_state['values']['occupier_telephone'])>10)) {
	form_set_error('occupier_telephone', 'Occupier Telephone should be of 10 digit');    
   }

  $occupier_fax_no = $form_state['values']['occupier_fax_no'];
  if (!preg_match('/^[0-9]*$/', $occupier_fax_no)) {
    form_set_error('occupier_fax_no', t('Occupier Fax should be numeric only!!'));
  }
  
  
  $occupier_mobile = $form_state['values']['occupier_mobile'];
  if (!preg_match('/^[0-9]*$/', $occupier_mobile)) {
    form_set_error('occupier_mobile', t('Occupier Mobile should be numeric only!!'));
  }
  if ($form_state['values']['occupier_mobile']!="" && (strlen($form_state['values']['occupier_mobile'])<10 || strlen($form_state['values']['occupier_mobile'])>10)) {
	form_set_error('occupier_mobile', 'Occupier Mobile should be of 10 digit');    
   }

	
   	  
}
function get_ajax_zone_name($form, $form_state)
{
    $commands   = array();
    $commands[] = ajax_command_replace('#cb', drupal_render($form['factory_part_a']['factory_zone_details']));
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
    
	if($factprofiletype == 'dir_firm' || $factprofiletype == 'govt' || $factprofiletype == 'psu' || $factprofiletype == 'others')
	{
		$commands[] = ajax_command_replace('#occupier_type_id', drupal_render($form['factory_part_c']['occupier_type']));
		$commands[] = ajax_command_replace('#din_director_id', drupal_render($form['factory_part_c']['din_director']));
	} else {
		$commands[] = ajax_command_replace('#occupier_type_id', drupal_render($form['factory_part_c']['occupier_type']));
		$commands[] = ajax_command_replace('#din_director_id', drupal_render($form['factory_part_c']['din_director_blank']));
	}
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}

function get_ajax_nationality($form, &$form_state)
{
    $commands   = array();
    //  $commands[] = ajax_command_replace('#occupier_nationality_id', drupal_render( $form['factory_part_c']['occupier_nationality']));
    $commands[] = ajax_command_replace('#ld_show_aadhaar', drupal_render($form['factory_part_c']['occupier_aadhaar']));
	$commands[] = ajax_command_replace('#ld_show_passport', drupal_render($form['factory_part_c']['occupier_passport']));
    $commands[] = ajax_command_replace('#occupier_name_id', drupal_render($form['factory_part_c']['occupier_name']));
    $commands[] = ajax_command_replace('#occupier_age_id', drupal_render($form['factory_part_c']['occupier_age']));
    $commands[] = ajax_command_replace('#occupier_gurdian_name_id', drupal_render($form['factory_part_c']['occupier_gurdian_name']));
    $commands[] = ajax_command_replace('#occupier_telephone_id', drupal_render($form['factory_part_c']['occupier_telephone']));
	$commands[] = ajax_command_replace('#occupier_mobile_id', drupal_render($form['factory_part_c']['occupier_mobile']));
   	$commands[] = ajax_command_replace('#occupier_fax_no_id', drupal_render($form['factory_part_c']['occupier_fax_no']));
	$commands[] = ajax_command_replace('#occupier_emailid', drupal_render($form['factory_part_c']['occupier_email_id']));
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



function caf_form_registrstion_parta_submit($form, &$form_state)
{
    global $user;
    $userid = $user->uid;
    $val    = $form_state['values'];
	
	$application_status = empty( $val['application_status_hidden'])?'':encryption_decryption_fun('decrypt', $val['application_status_hidden']);
  	$application_id = empty($val['applicationid_hidden'])?'':encryption_decryption_fun('decrypt', $val['applicationid_hidden']);
	$flagmapp= encryption_decryption_fun('decrypt', $val['flagmapp_hidden']); 
	
	$get_fa_cafa = get_fa_cafa($application_id);

	if($flagmapp == 'backlogplanapproval_no'){echo $backlog_plan_approval_date;
		$backlog_plan_approval_no =  encryption_decryption_fun('decrypt', $val['linknumber_hidden']);
		$backlog_plan_approval_date =  encryption_decryption_fun('decrypt', $val['linkdate_hidden']);
		$is_backlog = 1;
	}if($flagmapp == 'backlog_registrationno'){
		$backlog_registration_no =  encryption_decryption_fun('decrypt', $val['linknumber_hidden']);
		$is_backlog = 1;
	}if($flagmapp == 'planapproval_no'){
		$factory_plan_approval_number =  encryption_decryption_fun('decrypt', $val['linknumber_hidden']);
		
	}if($flagmapp == 'registration_number'){
		$factory_reg_number =  encryption_decryption_fun('decrypt', $val['linknumber_hidden']);
	}
   if($application_status == 'I' || $application_status == NULL || empty($application_status)){
	   $reference_no = created_referenceno();
   }else{
			$reference_no = $get_fa_cafa['reference_number'];
			}
	if($application_status=='B'){
		$status ='B';
		$date = $get_fa_cafa['created_date'];
	}else{
		$status ='In';
		$date = date('Y-m-d h:i:s');
		}
		
 $reference_no_approval_arrangments		= $val['reference_no_approval_arrangments'];
	 $date_approval_arrangments				= $val['date_approval_arrangments'];
	   
	 $factory_pollution_type				= $val['factory_pollution_type'];
	 if($factory_pollution_type== 4){
		$docmunt_white_category 	= file_load($val['doc_file']);
		if($docmunt_white_category != "" ){
			$docmunt_white_category->status = FILE_STATUS_PERMANENT;
			file_save($docmunt_white_category);
			$fid			=	$docmunt_white_category->fid;
		}
  } 
    $addr_same                = $form_state['values']['addr_same'];
    //$same_address_communication = $val['same_address_communication'];
   
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
  
    $cafa_Info = array(
        'factory_name' 			=> $val['factory_name'],
		'factory_previous_name' => $val['factory_previous_name'],
        'factory_location' 		=> $val['factory_location'],
        'factory_zone' 			=> $val['factory_zone'],
        
        //* factory address *//
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
        
        /* register office - if same as factory address */
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

		'comm_telephone'   	    => $val['comm_telephone'],
		'comm_mobile'     	    => $val['comm_mobile'],
		'comm_fax'     	        => $val['comm_fax'],
		'comm_email'     	    => $val['comm_email'],
        /* communication office - if same as factory address OR if same as register office */

        'factory_pan' 			    => $val['factory_pan'],
		
        /* owner premises address */
        'owner_name' 				=> $val['owner_name'],
        'pincodepremises' 			=> $val['pincodepremises'],
        'state_premises' 			=> $val['state_premises'],
        'district_premises' 		=> $val['district_premises'],
        'subdivision_premises' 		=> $val['subdivision_premises'],
        'areatype_premises' 		=> $val['areatype_premises'],
        'block_premises' 			=> $val['block_premises'],
        'panchayat_premises' 		=> $val['panchayat_premises'],
        'policestation_premises' 	=> $val['policestation_premises'],
        'postoffice_premises' 		=> $val['postoffice_premises'],
        'addrline_premises'		 	=> $val['addrline_premises'],
      
        'service_id' 				=> encryption_decryption_fun('decrypt', $val['serviceid_hidden']),
        'factory_typeid' 			=> encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']),
        'created_by' 				=> $userid,
		'created_date' 				=> $date,
        'reg_adress_same_factory' 	=> $addr_same,
        //'communication_adress_same_factory' => $same_address_communication,
        'occupier_present_address_same' => $same_as_address_occupier,
        //New field
        'reference_number'  			=> $reference_no,
        'is_backlog'  					=> $is_backlog,
		'application_status'  			=> $status,
	   	'backlog_plan_approval_no'  	=> $backlog_plan_approval_no,
		'backlog_registration_no'  		=> $backlog_registration_no,
		'factory_reg_number' 	    	=> $factory_reg_number,
		'factory_plan_approval_number' 	=> $factory_plan_approval_number,
		'backlog_plan_approval_date'	=>!empty($backlog_plan_approval_date)? $backlog_plan_approval_date:NULL,
		//'date_of_amenability'			=> $date_of_amenability,
		//'period_for_application'		=> $period_for_application,
		'factory_zone'					=> $val['factory_zone'],
		'factory_owershiptype'			=> $val['factory_owershiptype'],
		'wbpcb_intimation_letter' 		=> $fid,
			'wbpcb_reference_no' 		=> $reference_no_approval_arrangments,
			'wbpcb_ref_date' 			=> $date_approval_arrangments,
			'wbpcb_category_name'		=> $factory_pollution_type 
	    );


    if (empty($application_id)) {//echo encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']);die();
        $id = db_insert('fa_cafa')->fields($cafa_Info)->execute();
		drupal_goto('applicant/caf-reg/details-applyingyear-registration/' . $val['serviceid_hidden'] . '/' . $val['factorytypeid_hidden'].'/'.encryption_decryption_fun('encrypt', $id).'/'.$val['linknumber_hidden'].'/'.$val['linkdate_hidden'].'/'.$val['flagmapp_hidden']);
		 drupal_set_message('Factory Information has been saved successfully.');
    } else {
       
        $queryabc = db_update('fa_cafa');
        $queryabc->fields($cafa_Info);
        $queryabc->condition('id', $application_id, '=');
        $queryabc->execute();
		
		 drupal_set_message('Factory Information has been saved successfully.');
        
       // drupal_goto('applicant/caf-reg/details-worker-hp-yearly-registrtatoin/' . $val['serviceid_hidden'] . '/' . $val['factorytypeid_hidden'].'/'.$val['applicationid_hidden'].'/'.$val['linknumber_hidden'].'/'.$val['flagmapp_hidden']);
    }
    
    $form_state['rebuild'] = true;
}
?> 