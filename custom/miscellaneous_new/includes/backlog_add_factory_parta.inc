<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function backlog_add_factory_parta($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$referenceno)
{//echo 'hi';die();
	global $base_root, $base_path,$user;
	$userid 			= $user->uid;
	$form            	= array();
	$form['#attributes']= array('enctype' => "multipart/form-data");
	$user_role 			= array_keys($user->roles);
    $urole  			= $user_role[1];
	 $application_id     = encryption_decryption_fun('decrypt', $applicationid);
	$service_id 		= encryption_decryption_fun('decrypt', $serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt', $factory_typeid);
	$reference_number   = encryption_decryption_fun('decrypt', $referenceno);
	
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
    $factory_addrline	   = '';
    
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
	$reg_adress_same_factory_comm		= 1;
	
	if (!empty($application_id)) {
        $get_fa_cafa           = get_fa_cafa($application_id);
       //print_r($get_fa_cafa);die();
        $factory_name          = $get_fa_cafa['factory_name'];
        $factory_previous_name = $get_fa_cafa['factory_previous_name'];
        $factory_location      = $get_fa_cafa['nearest_landmark'];
		$factory_zone		   = $get_fa_cafa['factory_zone'];
		$factory_pan           = $get_fa_cafa['factory_pan'];
		$ownership_type		   = $get_fa_cafa['factory_owershiptype'];
		$gstin_no 			   = $get_fa_cafa['gstin_no'];
		$udyog_aadhaar         = $get_fa_cafa['udyog_aadhaar'];		
		$enargy_meter_no 	   = $get_fa_cafa['enargy_no'];		
		$cin_no 			   = $get_fa_cafa['cin_no'];		
		
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
		
		$reg_adress_same_factory_comm	  	= $get_fa_cafa['reg_adress_same_factory_comm'];
	
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
		$reg_adress_same_factory    = $get_fa_cafa['reg_adress_same_factory'];
       
        $occupier_present_address_same = $get_fa_cafa['occupier_present_address_same'];

        $trade_license_no                       = $get_fa_cafa['trade_license_no'];
       
        $reference_number                       = $get_fa_cafa['reference_number'];
        $application_status                     = $get_fa_cafa['application_status'];
        $is_backlog                             = $get_fa_cafa['is_backlog'];
		$date_of_amenability                    = $get_fa_cafa['date_of_amenability'];
		$period_for_application                 = $get_fa_cafa['period_for_application'];
			
		$wbpcb_category_name 					= $get_fa_cafa['wbpcb_category_name'];
		$wbpcb_reference_no 					= $get_fa_cafa['wbpcb_reference_no'];
		$wbpcb_ref_date 						= $get_fa_cafa['wbpcb_ref_date'];
		$wbpcb_intimation_letter    			= $get_fa_cafa['wbpcb_intimation_letter'];
		$backlog_plan_approval_date				= $get_fa_cafa['backlog_plan_approval_date'];
		$backlog_plan_approval_no				= $get_fa_cafa['backlog_plan_approval_no'];
		$factory_location    		      		= $get_fa_cafa['nearest_landmark'];
		$addrline_off_other						= $get_fa_cafa['addrline_off_other'];
		$country_code							= $get_fa_cafa['country_code'];
		$country_owner							= $get_fa_cafa['country_premises'];
		$factory_country_address				= $get_fa_cafa['factory_country_address'];
		$mouza_name								= $get_fa_cafa['mouza_name'];
		$jl_number								= $get_fa_cafa['jl_no'];			
		$license_valid_upto						= $get_fa_cafa['license_valid_upto'];
		$factory_license_no						= $get_fa_cafa['factory_license_no'];
		$backlog_license_number					= $get_fa_cafa['backlog_license_number'];
 		$backlog_registration_no				= $get_fa_cafa['backlog_registration_no'];
		$backlog_registration_date				= $get_fa_cafa['backlog_registration_date'];
		$date_of_amenability					= $get_fa_cafa['date_of_amenability'];
		$backlog_license_date					= $get_fa_cafa['backlog_license_date'];
		$license_valid_upto						= $get_fa_cafa['license_valid_upto'];
		$factor_add_inspector					= $get_fa_cafa['factor_add_inspector'];
		$created_by								= $get_fa_cafa['created_by'];
    }

   
  
	 $licens_number = !empty($factory_license_no)?$factory_license_no:(!empty($backlog_license_number)?$backlog_license_number:'');
	
	
	$factoryzone = get_factory_zone();
	$default_zone 	= array(""=>"- Select Zone -");
	foreach($factoryzone as $val){
		$factzonefinal[$val->zone_id] = $val->zone_name;
		$factzonefinal1 = ($default_zone+$factzonefinal);
	}
	$ownershiptype  = array(
	    "s" 			=> "- Select -",
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

	$form['applicationid_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $applicationid
    );
	$form['serviceid_hidden']     = array(
        '#type' => 'hidden',
        '#default_value' => $serviceid
    );
	$form['factory_typeid_hidden']     = array(
        '#type' => 'hidden',
        '#default_value' => $factory_typeid
    );
	
	
	$form['valid_date_hidden']     = array(
        '#type' => 'hidden',
        '#default_value' => $licregdate
    );
	
	$form['flag_hidden']     = array(
        '#type' => 'hidden',
        '#default_value' => $flagmapp
    );
    $form['application_status_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => encryption_decryption_fun('encrypt', $application_status) 
    );
	$form['referenceno_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $referenceno 
    );	
			
	/********** Factory Information - Start **********/
    
    $form['header']            = array(
        '#markup' => t('<div class="content"><h3>Add Factory Information</h3>')
    );
	
	 $form['factory_part_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('A. Factory Information'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
   
   $form['factory_part_info']['factory_name'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(i). Name of the factory'),
        '#type' 			=> 'textfield',
        '#required' 		=> TRUE,
        '#default_value' 	=> $factory_name,
		'#attributes' 		=> array('class'=>array('form-control'),'readonly'=>'readonly'),
      
    );
	$form['factory_part_info']['factory_pan'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(ii). PAN of the Business Establishment / Factory / Company'),
        '#type'				=> 'textfield',
        '#default_value' 	=> $factory_pan,
        '#required' 		=> TRUE,
		'#attributes' 		=> array( 'class' => array('form-control'),'placeholder' => 'eg.XXXXX0000X'),
		'#description'		=>'<font color="#FF0000">(N.B.- Under the Income Tax Act, 1961)</font>'
    );
	$form['factory_part_info']['gstin_no'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div></div>',
        '#title' 			=> t('(iii). GSTIN Number:'),
        '#type' 			=> 'textfield',
        '#required' 		=> TRUE,
        '#default_value' 	=> !empty($gstin_no)?$gstin_no:'',
        '#attributes' 		=> array('class' => array( 'form-control'),'placeholder' => 'eg.00XXXX0000X0XX' ),
        '#description'		=>'<font color="#FF0000">GSTIN should be alphanumeric</font>'
    );
	$form['factory_part_info']['udyog_aadhaar'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(iv).Udyog Aadhaar No'),
        '#type' 			=> 'textfield',
        //'#required' 		=> TRUE,
        '#default_value' 	=> !empty($udyog_aadhaar)?$udyog_aadhaar:'',
        '#attributes' 		=> array('class' => array( 'form-control'),'placeholder' => 'eg.WB00X0000000' ),
        '#description'		=>'<font color="#FF0000">12 digit number only</font>'
      
    );
	$form['factory_part_info']['trade_license_no'] = array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-4">',
			'#suffix' 			=> '</div>',
			'#title' 			=> t('(v).Trade License No:'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> !empty($trade_license_no)?$trade_license_no:'',
			'#attributes' 		=> array('class' => array( 'form-control'),'placeholder' => 'eg.00000000000'),
            '#required' 		=> TRUE,
            '#description'		=>'<font color="#FF0000">minimun 10 lphanumeric no.</font>'
		);
	
	$form['factory_part_info']['ammanabilty_date'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div></div>',
        '#title' 			=> t('(vi).Amenability Date'),
        '#type' 			=> 'textfield',
        '#required' 		=> TRUE,
        '#default_value' 	=> !empty($date_of_amenability)?date('d-m-Y',strtotime($date_of_amenability)):'',
        '#attributes' 		=> array('class' => array( 'form-control'),'readonly' => 'readonly' ),
        );
	 $form['factory_part_info']['plan_approval_no'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(vii). Plan Approval number'),
        '#type' 			=> 'textfield',
       
        '#default_value' 	=> !empty($backlog_plan_approval_no)?$backlog_plan_approval_no:'',
        '#attributes' 		=> array('class' => array( 'form-control'),'readonly' => 'readonly' ),
        );
		 $form['factory_part_info']['plan_approval_date'] = array(
                '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
                '#suffix' 			=> '</div>',
                '#title' 			=> t('(viii). Plan Approval date'),
                '#type' 			=> 'textfield',
            
                '#default_value' 	=> !empty($backlog_plan_approval_date)?date('d-m-Y',strtotime($backlog_plan_approval_date)):'',
                '#attributes'		=> array('class' => array( 'form-control'),'readonly' => 'readonly'),
      );
	$form['factory_part_info']['registration_no'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div></div>',
        '#title' 			=> t('(ix). Registration number'),
        '#type' 			=> 'textfield',
        '#required' 		=> TRUE,
        '#default_value' 	=> !empty($backlog_registration_no)?$backlog_registration_no:'',
        '#attributes' 		=> array('class' => array( 'form-control'),'readonly' => 'readonly' ),
        );
		$form['factory_part_info']['registration_date'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(x). Date of Registration'),
        '#type' 			=> 'textfield',
        '#required' 		=> TRUE,
        '#default_value' 	=> !empty($backlog_registration_date)?date('d-m-Y',strtotime($backlog_registration_date)):'',
        '#attributes' 		=> array('class' => array( 'form-control'),'readonly' => 'readonly' ),
        );
	
		 $form['factory_part_info']['license_no'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(xi). License number'),
        '#type' 			=> 'textfield',
		'#required' 		=> TRUE,
        '#default_value' 	=> !empty($licens_number)?$licens_number:'',
		'#attributes' 		=> array('class' => array( 'form-control'),'readonly' => 'readonly' ),
      
    );
	 $form['factory_part_info']['license_date'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div></div>',
        '#title' 			=> t('(xii). License Issued Date'),
        '#type' 			=> 'textfield',
		'#required' 		=> TRUE,
        '#default_value' 	=> !empty($backlog_license_date)?date('d-m-Y',strtotime($backlog_license_date)):'',
		'#attributes' 		=> array('class' => array( 'form-control'),'readonly' => 'readonly' ),
      
    );
	$form['factory_part_info']['license_valid'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(xiii). License Validupto'),
        '#type' 			=> 'textfield',
		'#required' 		=> TRUE,
        '#default_value' 	=> !empty($license_valid_upto)?$license_valid_upto:'',
		'#attributes' 		=> array('class' => array( 'form-control'),'readonly' => 'readonly' ),
      
    );
	$form['factory_part_info']['factory_previous_name'] = array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-4">',
			'#suffix' 			=> '</div>',
			'#title' 			=> t('(xiv). Previous Name of factory'),
			'#type' 			=> 'textfield',
		
			'#default_value' 	=> !empty($factory_previous_name)?$factory_previous_name:'',
			'#attributes' 		=> array('class' => array( 'form-control')),
		   
		);
	$form['factory_part_info']['factory_ownershiptype'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div></div> ',
        '#title' 			=> t('(xv). Ownership Type'),
        '#type' 			=> 'select',
		'#required' 		=> TRUE,
		'#options' 			=> $ownershiptype,
        '#default_value' 	=> !empty($ownership_type)?$ownership_type:$ownership_type_app_reg,
		'#attributes'		=> array('class' => array( 'select'),disabled),
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
    
	$ownership  = isset($form_state['values']['factory_ownershiptype']) ? $form_state['values']['factory_ownershiptype'] : $ownership_type;
    if(empty($ownership)){$ownership = $ownership_type_app_reg;}
    
	
	
    $form['factory_part_info']['row_start'] = array(
        '#prefix'	=> '<div class="row">',
        '#suffix' 	=> '',
        );
		$form['factory_part_info']['cin_no'] = array(
			'#prefix'	=> '<div id="cin_no_id">',
			'#suffix' 	=> '</div>',
    );
	if($ownership == 'pv' || $ownership == 'ltd'){
		$form['factory_part_info']['cin_no'] = array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-4" id="cin_no_id">',
			'#suffix' 			=> '</div>',
			'#title' 			=> t('(xv)(a). CIN No:'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			'#default_value' 	=> !empty($cin_no)?$cin_no:'',
			'#attributes' 		=> array('class' => array( 'form-control'),'placeholder' => 'eg.X00000WB0000XXX000000',$factory_cin_ck => $factory_cin_ck ),
			'#description' 		=> '<a href="http://www.mca.gov.in/mcafoportal/findCIN.do" target="_blank" title="Ministry Of Corporate Affairs, About MCA, Ministry">**Find CIN No.</a>',
		);
	 }else{
		 
		$form['factory_part_info']['cin_no'] = array(
			'#prefix'	=> '<div id="cin_no_id">',
			'#suffix' 	=> '</div>',
    );
		 }
	
	
	
	if($factory_type_id == 1){
		$form['factory_part_info']['enargy_no'] = array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-4">',
			'#suffix' 			=> '</div></div>',
			'#title' 			=> t('(xvi).Energy Meter No:'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> !empty($enargy_meter_no)?$enargy_meter_no:'',
			'#attributes' 		=> array('class' => array( 'form-control'),'placeholder' => 'Optional' ),
		);
		}else{
			$form['factory_part_info']['enargy_no'] = array(
			'#prefix' 			=> '',
			'#suffix' 			=> '</div>',
		);

	}
	  
	
	
	

  
/********** Location of the factory - Start **********/
	$form['factory_part_a'] = array(
        '#type'			=> 'fieldset',
        '#title' 		=> t('B. Location of the factory'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	
	$form['factory_part_a']['firstRowStart'] = array(
        '#prefix' 		=> '<div class="row">',
    );
	
	$form['factory_part_a']['pincode']       = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="input label-block">',
        '#suffix' 			=> '</label></div>',
        '#attributes' 		=> array(
           'class' 			=> array(),
           'placeholder' 	=> 'Pincode',
		 
        ),
        '#autocomplete_path' => 'pinautocomplete',
        '#id' 				 => 'pincode_autocomplete',
        '#maxlength' 		 => 6,
        '#title' 			 => t('(i) Pincode'),
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
            '#title' => '(ii) State',
            '#type' => 'select',
            '#id' => 'state_name',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'State',
				
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
            '#title' => '(iii) District',
            '#type' => 'select',
            '#id' => 'district_name',
            '#disabled' => TRUE,
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'District',
				
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
            '#title' => '(iv) Sub-Division',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Sub Division',
				
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
		
		$form['factory_part_a']['estate_type'] = array(
            '#title' => '(iv) Estate Type',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Estate Type',
				
            ),
            '#options' => common_custom_user_estatelist_list_new($district_v),
			'#required' => TRUE,
            '#default_value' => $estate_type,
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
            '#title' => '(vi) '. $areatype_name,
            '#type' => 'select',

            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'subdivision',
				
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
            '#title' => '(vii) '.$area_name,
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'panchayat',
				
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
            '#title' => '(x) Police Station',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Police Station',
				
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
            '#title' => '(ix) Post Office',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Post Office',
				
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
        '#title' 			=> '(x). Mouza Name',
        '#type' 			=> 'textfield',
        '#attributes' 		=> array( 'class' => array('form-control'),),	  	
        '#default_value' 	=> $mouza_name,
    );
    $form['factory_part_a']['jl_no'] = array(
            '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
            '#suffix' 			=> '</div>',  
            '#title' 			=> '(xi). JL Number',
            '#type' 			=> 'textfield',
            '#default_value'  	=> $jl_number,
            '#attributes' 		=> array( 'class' => array('form-control')),
            
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
			'#title'  => t('(x) Factory Zone'),
			'#value'   => $factory_zone_name[0]->zone_name,
			'#type' => 'textfield',
			'#default_value'        => !empty($factory_zone) ? $factory_zone :'',
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
		'#title' => t('(xi) Nearest Landmark'),
		'#type' => 'textfield',
		'#default_value' => $factory_location,
		'#attributes' => array('class' => array('charField') )
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
        '#title' => '(xii) Address',
        '#rows' => 3,
        '#type' => 'textarea',
		'#required' => TRUE,
        '#default_value' => $factory_addrline,
        '#attributes' => array(
            'class' => array(
                ''
            ),
            'placeholder' => 'Address Line',
			
        ),
        '#prefix' => '<div class="col-md-12"><label class="textarea label-block">',
        '#suffix' => '</label></div>'
    );
	 $form['factory_part_a']['comm_telephone'] = array(
			'#prefix' 			=> '<div class="col-md-3"><label class="input label-block">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t('(xiii). Telephone No.'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> $comm_telephone,
			'#attributes' 		=> array( 'class' => array(''))
		 );
	 $form['factory_part_a']['comm_mobile'] = array(
			'#prefix'		 	=> '<div class="col-md-3"><label class="input label-block">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t('(xiv). Mobile No.'),
			'#type' 			=> 'textfield',
		 	'#default_value' 	=> $comm_mobile,
			'#attributes' 		=> array( 'class' => array(''))
   		 );
	 $form['factory_part_a']['comm_alt_mobile'] = array(
			'#prefix'		 	=> '<div class="col-md-3"><label class="input label-block">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t('(xv). Alternate Mobile No.'),
			'#type' 			=> 'textfield',
		 	'#default_value' 	=> $comm_alt_mobile,
			'#attributes' 		=> array( 'class' => array(''))
   		 );
	$form['factory_part_a']['comm_fax'] = array(
			'#prefix' 			=> '<div class="col-md-3"><label class="input label-block">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t('(xvi). Fax No.'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> $comm_fax,
			'#attributes' 		=> array( 'class' => array(''))
    	);
    
	$form['factory_part_a']['comm_email'] = array(
			'#prefix' 			=> '<div class="col-md-3"><label class="input label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t('(xvii). Email Id.'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> $comm_email,
			'#attributes' 		=> array( 'class' => array(''))
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
		
		
    );
	
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
			'#title' 			=> t('(i). Country'),
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
        
        if (!empty($district_v_off) && !empty($state_v_off) && $state_v_off == 1) {
            
            $form['factory_part_off']['subdivision_off'] = array(
                '#title' 			=> '(v). Sub-Division',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' => array(''),
                								'placeholder' 			=> 'Sub Division',
												
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
                	'#title' 			=> '(vi). Area Type',
                	'#type' 			=> 'select',
                	'#attributes' 		=> array('class' => array(''),
                    					 			
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
                '#title' 			=> '(vii). '.$areatype_name_off,
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' => array(''),
                    						'placeholder' 			=> 'subdivision',
											
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
                '#title' 			=> '(viii). '.$area_name_off,
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 				=> array(''),
                   						 'placeholder' 				=> 'panchayat',
										 
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
                '#title' 			=> '(ix). Police Station',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 					=> array(''),
                   							 
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
                '#title' 			=> '(x). Post Office',
                '#type' 			=> 'select',
                '#attributes' 		=> array('class' 					=> array(''),
                   							  
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
                '#title' 			=> '(xi). Address',
                '#type' 			=> 'textarea',
				'#rows' 			=> 3,
                '#attributes' 		=> array('class' 					=> array(''),
                   							  
               					 		),
                '#required' 		=> TRUE,
				'#default_value' 	=> $office_addrline_off,
                '#prefix' 			=> '<div id="off_addressline_div"><div class="col-md-12"><label class="textarea label-block">',
                '#suffix' 			=> '</label></div></div>',
                
            );
		
		
			
		}elseif(!empty($country_id)){
			
			$form['factory_part_off']['other_country_address'] = array(
                '#title' 			=> '(ii) Country Address',
                '#type' 			=> 'textarea',
				'#rows' 			=> 3,
                '#attributes' 		=> array('class' => array('')),
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
    $reg_adress_same_factory_comm = !empty($reg_adress_same_factory_comm)?$reg_adress_same_factory_comm:1;
	$form['factory_part_comm']['firstRowStart'] = array(
        '#prefix' 			=> '<div class="row">',
        '#suffix' 			=> ''
    );

    $option = array("2" => "Same as Location of the factory","3" => "Same as Registered office / Head office" , "1" => "Other");

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
                'class' => array(
                    ''
                ),
                'placeholder' => 'Pincode',
				
            ),
            '#autocomplete_path' => 'pinautocomplete',
            '#id' => 'pincode_autocomplete_comm',
            '#maxlength' => 6,
            '#default_value' => $office_pincode_comm,
            '#title' => t('(i) Pincode'),
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
                '#title' => '(iii) District',
                '#type' => 'select',
                '#id' => 'district_name_comm',
                '#disabled' => TRUE,
                '#attributes' => array(

                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'District',
				   
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
                '#title' => '(iv) Sub-Division',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Sub Division',
				   
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
                '#title' => '(v) Area Type',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Area Type',
				    
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
                '#title' => '(vi)'.$areatype_name_comm,
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'subdivision',
				    
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
                '#title' => '(vii)'.$area_name_comm,
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'panchayat',
				   
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
                '#title' => '(viii) Police Station',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Police Station',
				    
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
                '#title' => '(ix) Post Office',
                '#type' => 'select',
                '#attributes' => array(
                    'class' => array(
                        ''
                    ),
                    'placeholder' => 'Post Office',
				   
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
            '#title' => '(x) Address',
            '#rows' => 3,
            '#type' => 'textarea',
			'#required' => TRUE,
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Address Line',
				
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
	if($urole==4){
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
        $file_url	= l('View', 'document-list/view-appliction-form/'.$serviceid.'/'.$applicationid.'/'.$factory_typeid.'/'.$referenceno.'/'.encryption_decryption_fun('encrypt','INT'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));

	$form['factory_catagory']['doc_file'] = array(
					'#type' 				 => 'managed_file',
					'#title'				 => '(ii). letter of intimation :-'.$file_url,
					'#upload_validators' 	 => array('file_validate_extensions' => array('pdf'), 'file_validate_size' => array(50*1024*1024)),
					'#upload_location' 		 => 'public://upload/upload_pdf/',
					'#process' 				 => array('import_my_file_element_process'),
					'#attributes' 			 => array('id' => '','autocomplete' => 'off','class'=>array('form-control')),
					'#prefix' 				 => '<div id="edit-doc-file-ajax-wrapper" class="col-md-4>',
			  		'#suffix' 				 => '</div>',
					'#required' 			 => TRUE,
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
	}
	else{
		 $form['factory_catagory'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('E. Factory Identification according to WBPCB'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	}

   
    
	$form['back_link'] = array(
		'#prefix' => '<div class="row"><div class="col-md-1">',
		'#suffix' => '</div>',
		'#markup' => l(t('<i class="fa fa-angle-left" aria-hidden="true"></i> Back'), 'applicant/applicant-dasboard/', array('html' => TRUE,'attributes' => array('class' => array('btn btn-dark pull-left'))))
  	);
	
    if(($application_status == 'In'|| $created_by==NULL) ){
		$form['submit'] = array(
			'#prefix' => '<div class="col-md-1">',
			'#suffix' => '</div>',
			'#attributes' => array('class' => array('btn btn-success')),
			'#type' => 'submit',
			'#value' => 'Save'
		);
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
    return $form;
}

function caf_form_online_renewal_parta_validate($form, &$form_state) {
  	 
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
    $commands[] = ajax_command_replace('#ld_emp_areatype_replace', drupal_render($form['factory_part_a']['areatype']));
    $commands[] = ajax_command_replace('#ld_empareatype_name_replace', drupal_render($form['factory_part_a']['block']));
    $commands[] = ajax_command_replace('#ld_emp_vill_ward_replace', drupal_render($form['factory_part_a']['panchayat']));
    $commands[] = ajax_command_replace('#ld_empps_replace', drupal_render($form['factory_part_a']['policestation']));
    $commands[] = ajax_command_replace('#ld_post_office_div', drupal_render($form['factory_part_a']['postoffice']));
	$commands[] = ajax_command_replace('#view_boundary', drupal_render($form['factory_part_a']['zone_boundary']));
    $commands[] = ajax_command_replace('#factory_zone_div', drupal_render($form['factory_part_a']['factory_zone_name']));
	  $commands[] = ajax_command_replace('#estate_type_replace', drupal_render($form['factory_part_a']['estate_type']));
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

function get_ajax_country_owner($form, &$form_state){
	
	$commands   = array();
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
	$commands[] = ajax_command_replace('#addrline_premises_div', drupal_render($form['factory_part_off']['addrline_premises']));
	//$commands[] = ajax_command_replace('#mouza_premises_div', drupal_render($form['factory_part_off']['mouza_name']));
	//$commands[] = ajax_command_replace('#jl_no_premises_div', drupal_render($form['factory_part_off']['jl_no']));
	return array('#type' => 'ajax','#commands' => $commands);
	
}

function get_ajax_owner_type($form, $form_state){
    $commands   = array();
	$commands[] = ajax_command_replace('#cin_no_id', drupal_render($form['factory_part_info']['cin_no']));
    return array( '#type' => 'ajax', '#commands' => $commands);
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

function get_ajax_load_premises($form, $form_state){
    $commands   = array();
	
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



function backlog_add_factory_parta_submit($form, &$form_state){
  	global $base_root, $base_path, $user;
    $userid = $user->uid;
    $val    = $form_state['values'];
	$user_role = array_keys($user->roles);
    $urole  = $user_role[1];
	
	$application_no 	= empty( $val['applicationid_hidden'])?'':encryption_decryption_fun('decrypt', $val['applicationid_hidden']);
	$service_id 		= empty($val['serviceid_hidden'])?'':encryption_decryption_fun('decrypt', $val['serviceid_hidden']);
	$factory_type_id 	= empty($val['factory_typeid_hidden'])?'':encryption_decryption_fun('decrypt', $val['factory_typeid_hidden']);
	$backlog_number		= empty($val['backlog_number_hidden'])?'':encryption_decryption_fun('decrypt', $val['backlog_number_hidden']);
  	$valid_date 		= empty($val['valid_date_hidden'])?'':encryption_decryption_fun('decrypt', $val['valid_date_hidden']);
	$flag_type			= empty($val['flag_hidden'])?'':encryption_decryption_fun('decrypt', $val['flag_hidden']); 
	$application_status = empty( $val['application_status_hidden'])?'':encryption_decryption_fun('decrypt', $val['application_status_hidden']);
	$referenceno_hidden	=  empty( $val['referenceno_hidden'])?'':encryption_decryption_fun('decrypt', $val['referenceno_hidden']);
	
	//$get_fa_cafa 		= get_fa_cafa($application_no);
	
	if($urole == 4){
		 $created_by 			= $userid;
		 $factor_add_inspector 	= NULL;
	}else{
		 $created_by = NULL;
		 $factor_add_inspector_id	= $userid;
		 $factor_add_inspector		= 1;
	}
	$reference_no = $referenceno_hidden;

  /* if($application_status == 'I' || $application_status == NULL || empty($application_status)){
	   $reference_no = created_referenceno();
	   $date = date('Y-m-d h:i:s');
   }else{
		$reference_no = $referenceno_hidden;
		$date = date('Y-m-d h:i:s');
	}*/
	
 	$reference_no_approval_arrangments	= $val['reference_no_approval_arrangments'];
	$date_approval_arrangments			= $val['date_approval_arrangments'];
	   
	$factory_pollution_type				= $val['factory_pollution_type'];
	 
	 if($factory_pollution_type== 4){
		$document_name = "Authentication Copy of Consent to operate issued by WBPCB for the factories having a hazardous process a defined under section 2(Cb) read with schedule I of factories Act,1948 as amended or a declaration for exempted category industries as notified by the West Bengal Pollution Contril Board";
		$document_listid =  fun_fetch_document_listid($document_name);
		$document_white_category 	= file_load($val['doc_file']);
		if($document_white_category != "" ){
            $path_category = pathinfo($document_white_category->filename);
				
			
            $new_filename_cat = 'Document_category_'.date('Y').'_'.$factory_type_id.'_'.time().'.'.$path_category['extension'];
            $document_white_category->filename = $new_filename_cat;
            file_save($document_white_category);

            $filename_cat_arr = explode("/", $document_white_category->uri);

            $filepathSave_cat 	= file_get_contents(escapefile_url('public://upload/upload_pdf/'.$filename_cat_arr[4]));
        
               $content_cat		= base64_encode($filepathSave_cat);

            $cat_doc_content_arr = array(
                'upload_doc_content' => $content_cat,
            );
          
					
			$get_int_letter = get_caf_upload_doc_details($application_no, $service_id, 'INT', $factory_type_id, $reference_no);
			
			
			if(!empty($get_int_letter)){
			
					 $content_id = $get_int_letter->upload_doc_content_id;
				
				
				
					$queryabc = db_update('fa_caf_upload_doc_content');
        			$queryabc->fields($cat_doc_content_arr);
       				$queryabc->condition('id', $content_id, '=');
		        	$queryabc->execute();
					
					$cat_upload_doc = array(
					
					'file_name' 					=> $new_filename_cat,
					'created_date'				 	=> date('Y-m-d h:i:s'),
                
            	);
					$queryabc = db_update('fa_caf_upload_all_doc');
        			$queryabc->fields($cat_upload_doc);
       				$queryabc->condition('upload_doc_content_id', $content_id, '=');
		        	$queryabc->execute();
					
				 	
			}else{
				$id_doc =  db_insert('fa_caf_upload_doc_content')->fields($cat_doc_content_arr)->execute();
                $cat_upload_doc_arr = array(
					'application_id' 				=> $application_no,
					'application_reference_no' 		=> $reference_no,
					'file_name' 					=> $new_filename_cat,
					'factory_typeid' 				=> $factory_type_id,
					'service_id' 					=> $service_id,
					'upload_doc_content_id' 		=> $id_doc,
					'upload_doc_type' 				=> 'INT',
					'created_by'					=> $userid,
					'created_date'				 	=> date('Y-m-d h:i:s'),
					'doc_master_id'					=> $document_listid['id'],
                	'identity_flag'					=> $document_listid['identity_flag']
                
            	);
            	db_insert('fa_caf_upload_all_doc')->fields($cat_upload_doc_arr)->execute();
			}
			
           
        }else{
            form_set_error('cat', 'Please Select Category file!!!');
        }
	} 
	
    $addr_same				= $form_state['values']['addr_same'];
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

  
	}  elseif (!empty($val['addr_same_comm']) && ($val['addr_same_comm'] == 1)) {
		
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
	
    

    	$cafa_Info = array(
        
		'factory_pan' 			    	=> $val['factory_pan'],
		'factory_previous_name' 		=> $val['factory_previous_name'],
        'nearest_landmark' 				=> $val['nearest_landmark'],
        'factory_zone' 					=> $val['factory_zone'],
		'gstin_no' 						=> $val['gstin_no'],
		'udyog_aadhaar' 				=> $val['udyog_aadhaar'],
		'trade_license_no'				=> $val['trade_license_no'],
		'enargy_no' 					=> $val['enargy_no'],
		'cin_no' 						=> !empty($val['cin_no'])? $val['cin_no']: NULL,
        'pincode' 						=> $val['pincode'],
        'state' 						=> $val['state'],
        'district' 						=> $val['district'],
        'subdivision' 					=> $val['subdivision'],
        'areatype' 						=> $val['areatype'],
        'block' 						=> $val['block'],
        'panchayat' 					=> $val['panchayat'],
        'policestation' 				=> $val['policestation'],
        'postoffice' 					=> $val['postoffice'],
        'addrline' 						=> $val['addrline'],
        'pincodeoff' 					=> $pincodeoff,
        'state_off' 					=> $state_off,
        'district_off' 					=> $district_off,
        'subdivision_off' 				=> $subdivision_off,
        'areatype_off' 					=> $areatype_off,
        'block_off' 					=> $block_off,
        'panchayat_off' 				=> $panchayat_off,
        'policestation_off' 			=> $policestation_off,
        'postoffice_off' 				=> $postoffice_off,
        'addrline_off' 					=> $addrline_off,
		'addrline_off_other'			=> $val['addrline_off_other'],
		'comm_telephone'   	    		=> $val['comm_telephone'],
		'comm_mobile'     	    		=> $val['comm_mobile'],
		'comm_fax'     	        		=> $val['comm_fax'],
		'comm_email'     	    		=> $val['comm_email'],
		'comm_alt_mobile'				=> $val['comm_alt_mobile'],
		
		'reg_adress_same_factory_comm'	=> $addr_same_comm,
// communication address - if same as factory address or register office address //
		'pincodecomm' 					=> $pincodecomm,
        'state_comm' 					=> $state_comm,
        'district_comm' 				=> $district_comm,
        'subdivision_comm' 				=> $subdivision_comm,
        'areatype_comm' 				=> $areatype_comm,
        'block_comm' 					=> $block_comm,
        'panchayat_comm' 				=> $panchayat_comm,
        'policestation_comm' 			=> $policestation_comm,
        'postoffice_comm' 				=> $postoffice_comm,
        'addrline_comm' 				=> $addrline_comm,
		
		'mouza_name'		 			=> $val['mouza_name'],
		'jl_no'		 					=> $val['jl_no'],
		'country_code'					=> $val['country'],
		
        'service_id' 					=> encryption_decryption_fun('decrypt', $val['serviceid_hidden']),
        'factory_typeid' 				=> encryption_decryption_fun('decrypt',	$val['factory_typeid_hidden']),
        'created_by' 					=> $created_by,
		'created_date' 					=> $date,
        'reg_adress_same_factory' 		=> $addr_same,
     
        'reference_number'  			=> $reference_no,
        'is_backlog'  					=> 1,
		'application_status'  			=> 'In',
	  	
		
		'factory_zone'						=> $val['factory_zone'],
		'factory_owershiptype'				=> $val['factory_ownershiptype'],
		'wbpcb_intimation_letter' 			=> $file_white_category_id,
		'wbpcb_reference_no' 				=> $reference_no_approval_arrangments,
		'wbpcb_ref_date' 					=> !empty($date_approval_arrangments)?$date_approval_arrangments:NULL,
		'wbpcb_category_name'				=> $factory_pollution_type,
		'estate_type'						=> $val['estate_type'],
		'modification_date'					=> date('Y-m-d'),
		
		
	);
       $queryabc = db_update('fa_cafa');
        $queryabc->fields($cafa_Info);
        $queryabc->condition('id', $application_no, '=');
        $queryabc->execute();
		
		if($urole != 4){
			remark_input($reference_no,$application_no,'In','factory information edit from Applicant')	;	
		}else{
			remark_input($reference_no,$application_no,'In','factory information edit from AD')	;	
		}
		
		 drupal_set_message('Factory Information has been saved successfully.');
        
      
    
    $form_state['rebuild'] = true;
}
?> 