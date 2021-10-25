<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function factory_parta($form, &$form_state, $licenseno, $validupto,$serviceid){

	global $base_root, $base_path, $user;
	
	$userid 			= $user->uid;
	$user_role 			= array_keys($user->roles);
    $urole  			= $user_role[1];
	$form            	= array();
	$form['#attributes']= array('enctype' => "multipart/form-data");
	$license_no     	= encryption_decryption_fun('decrypt', $licenseno);
	$valid_upto 		= encryption_decryption_fun('decrypt', 	$validupto);
	$service_id 		= encryption_decryption_fun('decrypt', $serviceid);

	
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
	$reg_adress_same_factory 			= 1;
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
		
        $reg_adress_same_factory       = $get_fa_cafa['reg_adress_same_factory'];
		
		$reg_adress_same_factory_comm	=$get_fa_cafa['reg_adress_same_factory_comm'];
      
    

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
		$plan_approval_no						= $get_fa_cafa['factory_plan_approval_number'];
		$plan_approval_date						= $get_fa_cafa['plan_approval_date'];
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
		$license_date	  						= $get_fa_cafa['license_date'];
 		$factory_typeid							= $get_fa_cafa['factory_typeid'];
		$backlog_registration_no				= $get_fa_cafa['backlog_registration_no'];
		$backlog_registration_date				= $get_fa_cafa['backlog_registration_date'];
		$date_of_amenability					= $get_fa_cafa['date_of_amenability'];
		$plant_installed						= $get_fa_cafa['plant_installed'];
		
    }
	
	if (empty($application_id)) {
		$factoy_status = NULL;
        $tm_fact_data           = fun_fetch_fact_tm($license_no,$valid_upto,$factoy_status);
    //print_r($tm_fact_data);die;
        $factory_name          = $tm_fact_data['unit_name'];
        $factory_previous_name = $tm_fact_data['unit_name_prev'];
        $nearest_landmark      = $tm_fact_data['unit_near_rail_station_steamer_ghat'];
        $factory_zone		   = !empty($tm_fact_data['new_zone_id'])?$tm_fact_data['new_zone_id']:$tm_fact_data['unit_zone_id'];
        
		$factory_typeid		   = $tm_fact_data['classification_type'];
		if($factory_typeid == 'X'){
			$factory_typeid = 1;
		}if($factory_typeid == 'Y'){
			$factory_typeid = 2;
		}if($factory_typeid =='Z'){
			$factory_typeid = 3;
        }
        $ownership_type		   = !empty($tm_fact_data['unit_type'])?$tm_fact_data['unit_type']:'others';

		if($ownership_type == "COMPANY"){
			$ownership_type = "pv";
        }
        if($ownership_type == "FIRM"){
			$ownership_type = "par_firm";
			
		}if($ownership_type == "PROPRIETOR"){
			$ownership_type = "pro_firm";
			
		}if($ownership_type == "PROPRIETOR"){
            $ownership_type = "pro_firm";
        }

        ////////////////MY CODE////////////////////

        /////////////////////////////////////

		$type_hazardous		   = $tm_fact_data['factory_nature_id'];
		
        $factory_pincode       = $tm_fact_data['unit_pin_code'];
        $factory_state         = $tm_fact_data['state'];
        $factory_district      = $tm_fact_data['unit_district_id'];
        $factory_subdivision   = $tm_fact_data['unit_sub_div_hq'];

        
        
		if(!empty($tm_fact_data['unit_po_id'])){
			$factory_postoffice_tm = fun_area_post_office_mst($tm_fact_data['unit_po_id']);
			$factory_postoffice    = $factory_postoffice_tm['fa_po_id'];
			$pincode_v			   = $factory_postoffice_tm['fa_pin_code'];
		}else{
			$factory_postoffice = NULL;
		}
		
		
        $factory_addrline      = $tm_fact_data['unit_address'];
		    
        $office_addrline_off    = $tm_fact_data['reg_office_address'];
       
        $comm_telephone     	  = $tm_fact_data['unit_comm_phone_no'];
		$comm_mobile     	      = $tm_fact_data['unit_comm_mobile_no'];
		$comm_fax     	          = $tm_fact_data['unit_comm_fax_no'];
		$comm_email     	      = $tm_fact_data['unit_comm_email'];
		$comm_alt_mobile 		  = $tm_fact_data['unit_comm_mobile_no'];
		$office_addrline_comm 	  = $tm_fact_data['loc_office_address'];
		$date_of_amenability      = $tm_fact_data['amenability_date'];
		$license_valid_upto		  = date('Y-m-d',strtotime($tm_fact_data['license_valid_upto_date']));
		$backlog_license_number	  = $tm_fact_data['license_no'];
		$license_date	  		  = !empty($tm_fact_data['last_license_date'])?$tm_fact_data['last_license_date']:$tm_fact_data['license_date'];
		if(!empty($license_date)){
			 $license_date =  substr($license_date,0,10);
			 $is_vaild_date	= validateDate($license_date, 'Y-m-d');
	 		if(!empty($is_vaild_date)){
				 $lic_date= date('d-m-Y',strtotime($license_date));
			 }else{
		  		 $lic_date=substr($license_date,0,4);
			 }
		}else{
			$lic_date = NULL;
		}
		$backlog_registration_no	= $tm_fact_data['registration_no'];
		$backlog_registration_date	= $tm_fact_data['registration_date'];
		$date_of_amenability		= $tm_fact_data['amenability_date'];
		$worker_total				= $tm_fact_data['worker_total'];
		$power_installed			= $tm_fact_data['power_installed'];
		$factory_id					= $tm_fact_data['factory_id'];
		
		$backlog_plan_approval_date = $tm_fact_data['plan_approval_date'];
		$backlog_plan_approval_no = $tm_fact_data['plan_approval_no'];
		$plant_installed			= $tm_fact_data['plant_install_particular'];
		
			/*$telmacregistration = fetch_telmacregistration_certificates(25878);
			print_r($telmacregistration);die;*/
		
		/*if(empty($$tm_fact_data['plan_approval_no'])){
			$telmacplan_approval 		= fetch_telmacplan_approval(25580);
		if(!empty($telmacplan_approval)){
			$approval_no = $telmacplan_approval[0][approval_no];
			$approval_no_correct = is_numeric($approval_no);
			$approval_date = $telmacplan_approval[0][approval_date];
			
			}
		}*/
		
		//$backlog_plan_approval_no	= !empty($tm_fact_data['plan_approval_no'])?$tm_fact_data['plan_approval_no']:$approval_no_correct;
		//  $backlog_plan_approval_date = !empty($tm_fact_data['plan_approval_date'])?$tm_fact_data['plan_approval_date']:$approval_date;
		
		//echo $is_vaild_date	= validateDate($backlog_plan_approval_date, 'Y-m-d');
		//print_r($telmacplan_approval);die;
		
        
    }
 $licens_number = !empty($factory_license_no)?$factory_license_no:(!empty($backlog_license_number)?$backlog_license_number:'');
 if($factory_typeid == 1){
	 $section = 'Section-2m(i)';
 }if($factory_typeid == 2){
	 $section = 'Section-2m(ii)';
 }if($factory_typeid == 3){
	 $section = 'Section-85';
 }

$form['applicationid_hidden'] = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> $applicationid
    );
	$form['serviceid_hidden']     = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> $serviceid
    );
	$form['factory_typeid_hidden']     = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> encryption_decryption_fun('encrypt', $factory_typeid),
    );
	
	
	$form['lic_issued_date_hidden']     = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> encryption_decryption_fun('encrypt', $license_date),
    );
	
	$form['backlog_reg_number_hidden']  = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> encryption_decryption_fun('encrypt', $backlog_registration_no),
    );
	$form['backlog_reg_date_hidden']     = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> encryption_decryption_fun('encrypt', $backlog_registration_date),
    );
	$form['date_of_amenability_hidden']     = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> encryption_decryption_fun('encrypt', $date_of_amenability),
    );
    
	$form['reference_number_hidden']     = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> encryption_decryption_fun('encrypt', $reference_number),
    );

	$form['worker_total_hidden']     = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> encryption_decryption_fun('encrypt', $worker_total),
    );
$form['power_installed_hidden']     = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> encryption_decryption_fun('encrypt', $power_installed),
    );
	
	$form['factory_id_hidden']     = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> encryption_decryption_fun('encrypt', $factory_id),
    );
	
	
	$form['factory_id_hidden']     = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> encryption_decryption_fun('encrypt', $factory_id),
    );
	$form['license_no_hidden']     = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> $licenseno
    );
	$form['license_no_validdate_hidden']     = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> $validupto);
	

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
	

	//$displayLink =	'<a href='.$base_path.'telmac_registration-genarate-file/'.encryption_decryption_fun('encrypt', $factory_id).' target= "_BLANK">Registration Certificate</a>';
			
	/********** Factory Information - Start **********/
	 $backlog_registration_date =  substr($backlog_registration_date,0,10);
	 $is_vaild_date	= validateDate($backlog_registration_date, 'Y-m-d');
	 if(!empty($is_vaild_date)){
		 $reg_date= date('d-m-Y',strtotime($backlog_registration_date));
	 }else{
		   $reg_date=substr($backlog_registration_date,0,4);
	 }
    
    $form['header']            = array(
        '#markup' => t('<div class="content"><h3>Add the details of the factory <br/>Name:-'.$factory_name.' ('.$section.')&nbsp;&nbsp;&nbsp;&nbsp;'.$displayLink.'
		<br/>Registration No:-'.$backlog_registration_no.' ,dated on:-'.$reg_date.'
		<br/>License No:-'.$licens_number.',dated on :-'.$lic_date.' Validupto Date:-'.date('d-m-Y',strtotime($license_valid_upto)).'</h3>')
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
        '#attributes' 		=> array('class' => array( 'form-control'),'placeholder' => 'eg.WB00X0000000'),
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
	  if(!empty($date_of_amenability)){
		 $is_vaild_date	= validateDate($date_of_amenability, 'Y-m-d');
		 if(!empty($is_vaild_date)){
			 $date_of_amenability =  substr($date_of_amenability,0,4);
			$date_of_amenability = '00-00-'.$date_of_amenability;
			 $form['factory_part_info']['date_of_amenability'] = array(
					'#prefix' 			=> '<div class="col-md-4 col-xs-4">',
					'#suffix' 			=> '</div></div>',
					'#title' 			=> t('(vi).Amenability Date:'),
					'#type' 			=> 'textfield',
					'#default_value' 	=> !empty($date_of_amenability)?$date_of_amenability:'',
					'#attributes' 		=> array( 'class' => array('form-control datepicker_retify'),'readonly' => 'readonly'),
					'#required' 		=> TRUE,
			);
		 }else{
			  $form['factory_part_info']['date_of_amenability'] = array(
					'#prefix' 			=> '<div class="col-md-4 col-xs-4">',
					'#suffix' 			=> '</div></div>',
					'#title' 			=> t('(vi).Amenability Date:'),
					'#type' 			=> 'textfield',
					'#default_value' 	=> !empty($date_of_amenability)?$date_of_amenability:'',
					'#attributes' 		=> array( 'class' => array('form-control datepicker_retify')),
					'#required' 		=> TRUE,
					 '#description'		=>'<font color="#FF0000">(N.B.:-The Amenabilty date is not in the correct format.
				 							<br/> Correct it according to the date of registration certificate <br/>
											or contact to the office)</font>'
			);
		 }
		
	}else{
		$form['factory_part_info']['date_of_amenability'] = array(
		'#prefix' 			=> '<div class="col-md-4 col-xs-4">',
		'#suffix' 			=> '</div></div>',
		'#title' 			=> t('(vi).Amenability Date:'),
		'#type' 			=> 'textfield',
		'#default_value' 	=> '',
		'#attributes' 		=> array( 'class' => array('form-control datepicker_retify'),'readonly' => 'readonly'),
		'#required' 		=> TRUE,
		
	);
	}
	if(!empty($backlog_plan_approval_no)){
        $form['factory_part_info']['plan_approval_no'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div>',
        '#title' 			=> t('(vii). Plan Approval number'),
        '#type' 			=> 'textfield',
        '#required' 		=> TRUE,
        '#default_value' 	=> !empty($backlog_plan_approval_no)?$backlog_plan_approval_no:'',
        '#attributes' 		=> array('class' => array( 'form-control'),'readonly' => 'readonly' ),
        );
   }else{
			$form['factory_part_info']['plan_approval_no'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4">',
			'#suffix' 			=> '</div>',
			'#title' 			=> t('(vii). Plan Approval number'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> '',
			'#attributes' 		=> array('class' => array( '') ),
			);
   }if(!empty($backlog_plan_approval_date)){
	  $backlog_plan_approval_date =  substr($backlog_plan_approval_date,0,10);
       $is_vaild_date	= validateDate($backlog_plan_approval_date, 'Y-m-d');
        if(empty($is_vaild_date)){
			$backlog_plan_approval_date =  substr($backlog_plan_approval_date,0,4);
			$backlog_plan_approval_date = '00-00-'.$backlog_plan_approval_date;
            $form['factory_part_info']['plan_approval_date'] = array(
                '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
                '#suffix' 			=> '</div>',
                '#title' 			=> t('(viii). Plan Approval date'),
                '#type' 			=> 'textfield',
                '#required' 		=> TRUE,
                '#default_value' 	=> !empty($backlog_plan_approval_date)?$backlog_plan_approval_date:'',
                '#attributes' 		=> array( 'class' => array('form-control datepicker_retify'),'readonly' => 'readonly'),
                 '#description'		=>'<font color="#FF0000">(N.B.:-The plan approval date is not in the correct format.
				 							<br/> Correct it according to the date of plan approval certificate <br/>
											or contact to the office)</font>'
            );
        }
        if($is_vaild_date==1){
            $form['factory_part_info']['plan_approval_date'] = array(
                '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
                '#suffix' 			=> '</div>',
                '#title' 			=> t('(viii). Plan Approval date'),
                '#type' 			=> 'textfield',
                '#required' 		=> TRUE,
                '#default_value' 	=> !empty($backlog_plan_approval_date)?date('d-m-Y',strtotime($backlog_plan_approval_date)):'',
                '#attributes'		=> array('class' => array( 'form-control'),'readonly' => 'readonly'),
            );
        }
   
    }else{
        $form['factory_part_info']['plan_approval_date'] = array(
            '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
            '#suffix' 			=> '</div>',
            '#title' 			=> t('(viii). Plan Approval date'),
            '#type' 			=> 'textfield',
            '#default_value' 	=> '',
            '#attributes' 		=> array( 'class' => array('form-control datepicker_retify'),'readonly' => 'readonly'),
        );
    }
	 if(!empty($backlog_registration_no)){
        $form['factory_part_info']['registration_no'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div></div>',
        '#title' 			=> t('(ix). Registration number'),
        '#type' 			=> 'textfield',
        '#required' 		=> TRUE,
        '#default_value' 	=> !empty($backlog_registration_no)?$backlog_registration_no:'',
        '#attributes' 		=> array('class' => array( 'form-control'),'readonly' => 'readonly' ),
        );
   }else{
        $form['factory_part_info']['registration_no'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div></div>',
        '#title' 			=> t('(ix). Registration number'),
        '#type' 			=> 'textfield',
        '#required' 		=> TRUE,
        '#default_value' 	=> '',
        '#attributes' 		=> array('class' => array( '') ),
        );
   }if(!empty($backlog_registration_date)){
	  $backlog_registration_date =  substr($backlog_registration_date,0,10);
       $is_vaild_date	= validateDate($backlog_registration_date, 'Y-m-d');
	   
        if(empty($is_vaild_date)){
			  $backlog_registration_date =  substr($backlog_registration_date,0,4);
			$backlog_registration_date = '00-00-'.$backlog_registration_date;
            $form['factory_part_info']['registration_date'] = array(
                '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4">',
                '#suffix' 			=> '</div>',
                '#title' 			=> t('(x). Registration date'),
                '#type' 			=> 'textfield',
                '#required' 		=> TRUE,
                '#default_value' 	=> !empty($backlog_registration_date)?$backlog_registration_date:'',
                '#attributes'		=> array('class' => array( 'form-control datepicker_retify'),'readonly' => 'readonly'),
                 '#description'		=>'<font color="#FF0000">(N.B.:-The registration date is not in the correct format.
				 							<br/> Correct it according to the date of registration certificate <br/>
											or contact to the office)</font>'
            );
        }
        if($is_vaild_date==1){
            $form['factory_part_info']['registration_date'] = array(
                '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4">',
                '#suffix' 			=> '</div>',
                '#title' 			=> t('(x). Registration date'),
                '#type' 			=> 'textfield',
                '#required' 		=> TRUE,
                '#default_value' 	=> !empty($backlog_registration_date)?date('d-m-Y',strtotime($backlog_registration_date)):'',
                '#attributes'		=> array('class' => array( 'form-control'),'readonly' => 'readonly'),
            );
        }
   
    }else{
        $form['factory_part_info']['registration_date'] = array(
            '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4">',
            '#suffix' 			=> '</div>',
            '#title' 			=> t('(x). Registration date'),
            '#type' 			=> 'textfield',
            '#required' 		=> TRUE,
            '#default_value' 	=> '',
           '#attributes' 		=> array( 'class' => array('form-control datepicker_retify'),'readonly' => 'readonly'),
        );
    }if(!empty($licens_number)){
        $form['factory_part_info']['license_no'] = array(
            '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
            '#suffix' 			=> '</div>',
            '#title' 			=> t('(xi). License number'),
            '#type' 			=> 'textfield',
            '#required' 		=> TRUE,
            '#default_value' 	=> !empty($licens_number)?$licens_number:'',
            '#attributes' 		=> array('class' => array( 'form-control'),'readonly' => 'readonly' ),
        );
    }else{
       $form['factory_part_info']['license_no'] = array(
            '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
            '#suffix' 			=> '</div>',
            '#title' 			=> t('(xi). License number'),
            '#type' 			=> 'textfield',
            '#required' 		=> TRUE,
            '#default_value' 	=> !empty($licens_number)?$licens_number:'',
            '#attributes' 		=> array('class' => array( 'form-control') ),
        );
    }
	  if(!empty($license_date)){
        $is_vaild_date	= validateDate($license_date, 'Y-m-d');
        if($is_vaild_date!=1){
			$license_date =  substr($license_date,0,4);
			$license_date = '00-00-'.$license_date;
            $form['factory_part_info']['license_issued'] = array(
               '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
               '#suffix' 			=> '</div></div>',
               '#title' 			=> t('(xii). License issued date'),
               '#type' 			=> 'textfield',
               '#required' 		=> TRUE,
               '#default_value' 	=> !empty($license_date)?$license_date:'',
			    '#attributes'		=> array('class' => array( 'form-control datepicker_retify'),'readonly' => 'readonly'),
              '#description'		=>'<font color="#FF0000">(N.B.:-The license_issued date is not in the correct format.
				 							<br/> Correct it according to the date of License certificate <br/>
											or contact to the office)</font>'
            );
        }
        if($is_vaild_date==1){
            $form['factory_part_info']['license_issued'] = array(
               '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
               '#suffix' 			=> '</div></div>',
               '#title' 			=> t('(xii).  License issued date'),
               '#type' 				=> 'textfield',
               '#required' 			=> TRUE,
               '#default_value' 	=> !empty($license_date)?date('d-m-Y',strtotime($license_date)):'',
               '#attributes'		=> array('class' => array( 'form-control'),'readonly' => 'readonly'),
            );
        }
    }else{
       $form['factory_part_info']['license_issued'] = array(
            '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
            '#suffix' 			=> '</div></div>',
            '#title' 			=> t('(xii).  License issued date'),
            '#type' 			=> 'textfield',
            '#required' 		=> TRUE,
            '#default_value' 	=> !empty($license_date)?$license_date:'',
           '#attributes' 		=> array( 'class' => array('form-control datepicker_retify'),'readonly' => 'readonly'),
        );
    }
if(!empty($license_valid_upto)){
        $is_vaild_date	= validateDate($license_valid_upto, 'Y-m-d');
        if($is_vaild_date!=1){
			$license_valid_upto =  substr($license_valid_upto,0,4);
			$license_valid_upto = '00-00-'.$license_valid_upto;
            $form['factory_part_info']['license_valid_upto'] = array(
                '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4">',
                '#suffix' 			=> '</div>',
                '#title' 			=> t('(xiii). License valid date'),
                '#type' 			=> 'textfield',
                '#required' 		=> TRUE,
                '#default_value' 	=> !empty($license_valid_upto)?$license_valid_upto:'',
				 '#attributes'		=> array('class' => array( 'form-control datepicker_retify'),'readonly' => 'readonly'),
                '#description'		=>'<font color="#FF0000">(N.B.:-The License vaild upto date is not in the correct format.
				 							<br/> Correct it according to the date of License certificate <br/>
											or contact to the office)</font>'
            );
        }
        if($is_vaild_date==1){
            $form['factory_part_info']['license_valid_upto'] = array(
                '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4">',
                '#suffix' 			=> '</div>',
                '#title' 			=> t('(xiii). License valid date'),
                '#type' 			=> 'textfield',
                '#required' 		=> TRUE,
                '#default_value' 	=> !empty($license_valid_upto)?date('d-m-Y',strtotime($license_valid_upto)):'',
                '#attributes'		=> array('class' => array( 'form-control'),'readonly' => 'readonly'),
           );
        }
    }else{
        $form['factory_part_info']['license_valid_upto'] = array(
            '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4">',
            '#suffix' 			=> '</div>',
            '#title' 			=> t('(xiii). License valid date'),
            '#type' 			=> 'textfield',
            '#required' 		=> TRUE,
            '#default_value' 	=> '',
            '#attributes'		=> array('class' => array( 'form-control datepicker_retify')),
        );
    }
 $form['factory_part_info']['factory_previous_name'] = array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-4">',
			'#suffix' 			=> '</div>',
			'#title' 			=> t('(xiv). Previous Name of factory'),
			'#type' 			=> 'textfield',
			//'#required' 		=> TRUE,
			'#default_value' 	=> !empty($factory_previous_name)?$factory_previous_name:'',
            '#attributes'		=> array('class' => array( 'form-control')),
    );
	$form['factory_part_info']['factory_ownershiptype'] = array(
        '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
        '#suffix' 			=> '</div></div><div class="row">',
        '#title' 			=> t('(xv). Ownership Type'),
        '#type' 			=> 'select',
		'#required' 		=> TRUE,
        '#options' 			=> $ownershiptype,
        
        '#default_value' 	=> !empty($ownership_type)?$ownership_type:$ownership_type_app_reg,
		'#attributes'		=> array('class' => array( ''),disabled),
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
   
	
	
	if($factory_typeid == 1){
		$form['factory_part_info']['enargy_no'] = array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-4">',
			'#suffix' 			=> '</div></div>',
			'#title' 			=> t('(xvi).Energy Meter No:'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> !empty($enargy_meter_no)?$enargy_meter_no:'',
            '#attributes' 		=> array('class' => array( 'form-control'),'placeholder' => 'eg.00000000',$factory_enargy_ck => $factory_enargy_ck ),
            '#description'		=>'<font color="#FF0000">8 digit number only</font>'
		);
		}else{
			$form['factory_part_info']['enargy_no'] = array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-4">',
			'#suffix' 			=> '</div></div>',
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
		   $factory_location_ck => $factory_location_ck
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
            '#title' => $factory_location_check_data.'(ii) State',
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
            '#title' => '(ii) State',
            '#type' => 'select',
            '#id' => 'state_name',
            '#disabled' => TRUE,
            '#attributes' => array(
                'class' => array(''),
                'placeholder' => 'State',
                $factory_location_ck => $factory_location_ck
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
            '#title' => $factory_location_check_data.'(iv) Estate Type',
            '#type' => 'select',
            '#attributes' => array(
                'class' => array(
                    ''
                ),
                'placeholder' => 'Estate Type',
				$factory_location_ck => $factory_location_ck
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
				$factory_location_ck => $factory_location_ck
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
			 '#options' => common_custom_user_ps_list_new($value_district),
			'#default_value' => $factory_policestation,
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
            '#title' => '(ix) Post Office'.$factory_postoffice,
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
			 '#options' => common_custom_post_office_list_new($pincode_v),
            '#default_value' => $factory_postoffice,
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
        '#attributes' 		=> array( 'class' => array('form-control'),$factory_location_ck => $factory_location_ck),	  	
        '#default_value' 	=> $mouza_name,
    );
    $form['factory_part_a']['jl_no'] = array(
            '#prefix' 			=> '<div class="col-md-4 col-xs-4">',
            '#suffix' 			=> '</div>',  
            '#title' 			=> $factory_location_check_data.'(xi). JL Number',
            '#type' 			=> 'textfield',
            '#default_value'  	=> $jl_number,
            '#attributes' 		=> array( 'class' => array('form-control'),$factory_location_ck => $factory_location_ck),
            
    );
	
	if (!empty($value_block) && !empty($value_panchayat)) {
		
		$factory_zone_name = get_zone_name($value_block,$value_panchayat);
		
		$form['factory_part_a']['factory_zone'] = array(
			'#value'   => $factory_zone_name[0]->zone_id,
			'#type' => 'hidden',
			'#required' => TRUE,
		);
		
			$form['factory_part_a']['factory_zone_name'] = array(
			'#prefix' 		=> '<div id="factory_zone_div"><div class="col-md-4"><label class="input label-block">',
            '#suffix' 		=> '</label></div></div>',
            '#type' 		=> 'textfield',
			
            '#title' 		=> t($factory_location_check_data.'(xii) Factory Zone'),
				'#value'		=> $factory_zone_name[0]->zone_name,
			
			'#required' 	=> TRUE,
			'#attributes'	=> array('class' => array( ''),'readonly' => 'readonly'),
			'#ajax' 		=> array(
									'event' => 'change',
									'effect' => 'fade',
									'callback' => 'get_ajax_load',
									'progress' => array('type' => 'throbber','message' => t('loading')))
							);
   } else {
	   $zone_name =  get_factory_zone_name($factory_zone);
		$form['factory_part_a']['factory_zone_name'] = array(
			'#prefix'				=> '<div id="factory_zone_div"><div class="col-md-4">',
			'#suffix' 				=> '</div></div>',
			'#type' 				=> 'textfield',
			'#rows'					=> 2,
			'#default_value'  	 	=> !empty($factory_zone) ?  $zone_name['zone_name'] :NULL,
			'#title'  				=> t('(x) Factory Zone'),
			
			'#attributes'			=> array('class' => array( ''),'readonly' => 'readonly'),
			'#required' 			=> TRUE,
		);
    }


	
	$form['factory_part_a']['nearest_landmark'] = array(
		'#prefix' => '<div class="col-md-4"><label class="input label-block">',
		'#suffix' => '</label></div>',
		'#title' => t($factory_location_check_data.'(xi) Nearest Landmark'),
		'#type' => 'textfield',
		'#default_value' => $factory_location,
		'#attributes' => array('class' => array('charField'),$factory_location_ck => $factory_location_ck )
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
	 $form['factory_part_a']['comm_telephone'] = array(
			'#prefix' 			=> '<div class="col-md-3"><label class="input label-block">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t($factory_location_check_data.'(xiii). Telephone No.'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> $comm_telephone,
			'#attributes' 		=> array( 'class' => array(''),$factory_location_ck => $factory_location_ck)
		 );
	 $form['factory_part_a']['comm_mobile'] = array(
			'#prefix'		 	=> '<div class="col-md-3"><label class="input label-block">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t($factory_location_check_data.'(xiv). Mobile No.'),
			'#type' 			=> 'textfield',
		 	'#default_value' 	=> $comm_mobile,
			'#attributes' 		=> array( 'class' => array(''),$factory_location_ck => $factory_location_ck)
   		 );
	 $form['factory_part_a']['comm_alt_mobile'] = array(
			'#prefix'		 	=> '<div class="col-md-3"><label class="input label-block">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t($factory_location_check_data.'(xv). Alternate Mobile No.'),
			'#type' 			=> 'textfield',
		 	'#default_value' 	=> $comm_alt_mobile,
			'#attributes' 		=> array( 'class' => array(''),$factory_location_ck => $factory_location_ck)
   		 );
	$form['factory_part_a']['comm_fax'] = array(
			'#prefix' 			=> '<div class="col-md-3"><label class="input label-block">',
			'#suffix' 			=> '</label></div>',
			'#title' 			=> t($factory_location_check_data.'(xvi). Fax No.'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> $comm_fax,
			'#attributes' 		=> array( 'class' => array(''),$factory_location_ck => $factory_location_ck)
    	);
    
	$form['factory_part_a']['comm_email'] = array(
			'#prefix' 			=> '<div class="col-md-3"><label class="input label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t($factory_location_check_data.'(xvii). Email Id.'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> $comm_email,
			'#attributes' 		=> array( 'class' => array(''),$factory_location_ck => $factory_location_ck)
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
    
    if (!empty($district_v_off) && !empty($state_v_off) && $state_v_off == 1) {
        
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
            '#prefix' 			=> '<div id="off_empps_replace">',
            '#suffix' 			=> '</div>',
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
            
            '#prefix' 			=> '<div id="off_post_office_div">',
            '#suffix' 			=> '</div>',
            
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
    
    
        
    }elseif(!empty($country_id)){
        
        $form['factory_part_off']['other_country_address'] = array(
            '#title' 			=> '(ii) Country Address',
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
            '#title' => $factory_communication_check_data.'(v) Area Type',
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
        
            '#attributes' 		=> array('class'=>array('datepicker_retify'), $wbpcb_reference_date_ck=>$wbpcb_reference_date_ck,),
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
	
    if($application_status == 'I' || $application_status == 'B' || empty($application_status) || $application_status == 'In'){
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
 
  $owner_name = $form_state['values']['owner_fname'];
	if (!preg_match('/[A-Za-z]+$/', $owner_name)) {  
    form_set_error('owner_fname', t('Owner Name should be text only!!'));
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



function factory_parta_submit($form, &$form_state){
  	global $base_root, $base_path, $user;
    $userid = $user->uid;
    $val    = $form_state['values'];
	 $user_role = array_keys($user->roles);
      $urole  = $user_role[1];
	
	$application_no 			= empty( $val['applicationid_hidden'])?'':encryption_decryption_fun('decrypt', $val['applicationid_hidden']);
	$service_id 				= empty($val['serviceid_hidden'])?'':encryption_decryption_fun('decrypt', $val['serviceid_hidden']);
	$factory_type_id 			= empty($val['factory_typeid_hidden'])?'':encryption_decryption_fun('decrypt', $val['factory_typeid_hidden']);
	$lic_issued_date_hidden		= empty($val['lic_issued_date_hidden'])?'':encryption_decryption_fun('decrypt', $val['lic_issued_date_hidden']);
  	$reference_number 			= empty( $val['reference_number_hidden'])?'':encryption_decryption_fun('decrypt', $val['reference_number_hidden']);
	$power_installed 			= empty( $val['power_installed_hidden'])?'':encryption_decryption_fun('decrypt', $val['power_installed_hidden']);
	$worker_total 				= empty( $val['worker_total_hidden'])?'':encryption_decryption_fun('decrypt', $val['worker_total_hidden']);
	$factory_id_hidden			= empty( $val['factory_id_hidden'])?'':encryption_decryption_fun('decrypt', $val['factory_id_hidden']);
	
	$license_no					= $val['license_no'];
	$license_no_validdate		= $val['license_valid_upto'];
	$date_of_amenability 		= $val['date_of_amenability'];
	$backlog_registration_no 	= $val['registration_no'];
	$backlog_registration_date	= $val['registration_date']; 
	$backlog_approval_date		=!empty($val['plan_approval_date'])?date('Y-m-d',strtotime($val['plan_approval_date'])):'' ; 
	$backlog_approval_no		= $val['plan_approval_no']; 
	
	
	
	
	$is_vaild_date_liccense	= validateDate($license_no_validdate, 'd-m-Y');
	$is_vaild_date_reg		= validateDate($backlog_registration_date, 'd-m-Y');
	$is_vaild_date_amana	= validateDate($date_of_amenability, 'd-m-Y');
	$is_vaild_date_plan	= !empty($val['plan_approval_date'])? validateDate($val['plan_approval_date'], 'd-m-Y'):1;
	if($is_vaild_date_amana == 1 && $is_vaild_date_reg==1 && $is_vaild_date_liccense==1 && $is_vaild_date_plan== 1){
		$factoy_status = NULL;
		$license_no_validdate 		=!empty($license_no_validdate)?date('Y-m-d',strtotime($license_no_validdate)):NULL; 
		$tm_fact_data           	= fun_fetch_fact_tm($license_no,$license_no_validdate,$factoy_status);
 	$nic_code_id_tm 			= $tm_fact_data['nic_code_id'];
	$nic_tm 					= fun_nic_code_mst_tm($nic_code_id_tm);
    $nic_code_tm 				= $nic_tm['nic_code'];
	$nic_code_dec 				= $nic_tm['nic_code_desc'];
	$registration_no			= $tm_fact_data['registration_no'];
	$registration_date			= $tm_fact_data['registration_date'];
	$license_no					= $tm_fact_data['license_no'];
	$license_valid_upto_date	= $tm_fact_data['license_valid_upto_date'];
	
	if(empty($reference_number))
  			$reference_no = created_referenceno();
	else
			$reference_no = $reference_number;
	
 	$reference_no_approval_arrangments	= $val['reference_no_approval_arrangments'];
	$date_approval_arrangments			= $val['date_approval_arrangments'];
	   
	$factory_pollution_type				= $val['factory_pollution_type'];
	 
	
	
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
	
    if($urole == 4){
		 $created_by 			= $userid;
		 $factor_add_inspector 	= NULL;
	}else{
		 $created_by = NULL;
		 $factor_add_inspector_id	= $userid;
		 $factor_add_inspector		= 1;
	}
 
  
    	$cafa_Info = array(
        'factory_name' 					=> $val['factory_name'],
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
		
        'service_id' 					=> $service_id,
        'factory_typeid' 				=> $factory_type_id,
        'created_by' 					=> $created_by,
		'created_date' 					=> date('Y-m-d'),
        'reg_adress_same_factory' 		=> $addr_same,
       
        'reference_number'  			=> $reference_no,
       
		'application_status'  			=> 'In',
	   
		'backlog_registration_no'  		=> $registration_no,
		'backlog_registration_date'  	=> !empty($backlog_registration_date)? date('Y-m-d',strtotime($backlog_registration_date)):NULL,
		
		'backlog_license_number'  		=> $license_no,
		'license_valid_upto'  			=> !empty($license_valid_upto_date)?date('Y-m-d',strtotime($license_valid_upto_date)):NULL,
		
		
		'factory_zone'					=> $val['factory_zone'],
		'factory_owershiptype'			=> $val['factory_ownershiptype'],
		'wbpcb_intimation_letter' 		=> $file_white_category_id,
		'wbpcb_reference_no' 			=> $reference_no_approval_arrangments,
		'wbpcb_ref_date' 				=> !empty($date_approval_arrangments)?$date_approval_arrangments:NULL,
		'wbpcb_category_name'			=> $factory_pollution_type,
		'estate_type'					=> $val['estate_type'],
		'tm_migrated_flag'				=> 'S',
		'modification_date'				=> date('Y-m-d'),
		'date_of_amenability'			=> !empty($date_of_amenability)?date('Y-m-d',strtotime($date_of_amenability)):NULL,
		'backlog_plan_approval_no'		=> $backlog_approval_no,
		'backlog_plan_approval_date'	=> !empty($backlog_approval_date)?$backlog_approval_date:NULL, 
		'tm_factory_id'					=> $factory_id_hidden,
		'tm_nic_code'					=> $nic_code_tm,
		'tm_nic_code_decribtion'		=> $nic_code_dec,
		'backlog_license_date'			=>!empty($tm_fact_data['license_date'])?date('Y-m-d',strtotime( $tm_fact_data['license_date'])):NULL, 
		'factor_add_inspector'			=> $factor_add_inspector,
		'factor_add_inspector_id'		=> $factor_add_inspector_id,
		'plant_installed'				=> $tm_fact_data['plant_install_particular'],
		
	);
	  
	//print_r($cafa_Info);die;
	
	if(!empty($factory_ownershiptype)){
	 if($ownership_type == 'pv' || $factory_ownershiptype == 'ltd'){
		 $ownership_type_occupier 	= 'Director';
	 }elseif($factory_ownershiptype == 'par_firm'  || $factory_ownershiptype=='llp'){
		 $ownership_type_occupier 	= 'Partner';
	 }elseif($factory_ownershiptype == 'pro_firm'){
		 $ownership_type_occupier 	= 'Proprietor';
	 }elseif($factory_ownershiptype=='cooperative'|| $factory_ownershiptype=='registered'){
		 $ownership_type_occupier	= 'Nominated Occupier';
	 }elseif($factory_ownershiptype == 'govt' || $factory_ownershiptype == 'psu' || $factory_ownershiptype == 'others' || $factory_ownershiptype =='localbody' ){
		 $ownership_type_occupier	= 'Nominated ';
	 }
	
	}
	//-----------------	CERTIFICATES upload not working , it will be worked after completed the migration
		/*$worker_details =array(
		
			'application_id' 			=>	$id,
			'application_reference_no' 	=>	$reference_no,
  			'factory_typeid'			=>  $factory_type_id,
  		    'service_id'				=>  $service_id,
  			'upload_doc_type'			=> 
  			upload_doc_content_id bigint,
  			 character varying(15),
  			
  			created_by integer,
  			created_date timestamp without time zone,
);	*/
if(!empty($backlog_approval_date) || $backlog_approval_date!=NULL){
	$plan_approval_no_chk = get_plan_approval_no($backlog_approval_no, $backlog_approval_date);
}
	

if(empty($application_no)){
	if (empty($plan_approval_no_chk)) {
	
        $caf_id = db_insert('fa_cafa')->fields($cafa_Info)->execute();
		
		
		
			$telmacregistration = fetch_telmacregistration_certificates($factory_id_hidden);
		if(!empty($tm_fact_data['occupier_name']) || !empty($telmacregistration[0]['occupier_name'])){
			$occupier_details = array(
		'type_occupier'   					=> $ownership_type_occupier, 
		'name_occupier'   					=> !empty($tm_fact_data['occupier_name'])?$tm_fact_data['occupier_name']:$telmacregistration[0]['occupier_name'], 
		'age_occupier' 						=> $tm_fact_data['occupier_age'],
		'father_husband_name_occupier' 		=> $tm_fact_data['occupier_f_or_h_name'],
		'occupier_mobile' 		    		=> $tm_fact_data['occupier_mobile_no'],
		'occupier_email_id' 	    		=> $tm_fact_data['occupier_email'],
		'occupier_fax_no'        			=> $tm_fact_data['occupier_fax_no'],
		'occupier_telephone'     			=> $tm_fact_data['occupier_phone_no'],
					
		'created_by'						=> $created_by,
		'application_occupier_id'			=> $caf_id,
		'application_status'				=> 'In',
		'factory_type_id'					=> $factory_type_id,
		'occupier_service_id'				=> $service_id,
		'application_reference_no'			=> $reference_no,
		
		//prement
		
		'policestation_oprmntadr'			=> $tm_fact_data['occupier_present_ps'],
		'addrline_oprmntadr'				=> !empty($tm_fact_data['occupier_present_address'])?$tm_fact_data['occupier_present_address']:$telmacregistration[0]['occupier_address'],
		
		
		//Present
				
  		
		'police_station_oprsntadr'			=> $tm_fact_data['occupier_present_ps'],
		'created_date'						=> date('Y-m-d')
		
	
		
	);
	$id = db_insert('fa_occupier_details')->fields($occupier_details)->execute();
		}
		if((!empty($tm_fact_data['worker_prev_total']) && $tm_fact_data['worker_prev_total'] !=0 && $tm_fact_data['worker_prev_total']!=NULL) || ($telmacregistration[0]['worker']!=0 && $telmacregistration[0]['worker']!=NULL && !empty($telmacregistration[0]['worker']))){
			$worker_details =array(
			'permanent_worker_men' 		          => $tm_fact_data['worker_men'],
			'permanent_worker_women' 			  => !empty($tm_fact_data['worker_women'])?$tm_fact_data['worker_women']:$telmacregistration[0]['female_employed'],
			'permanent_adolescents_male'          => $tm_fact_data['worker_male'],
			'permanent_adolescents_female' 		  => $tm_fact_data['worker_female'],
			'permanent_children_male'             => $tm_fact_data['worker_male_child'],
			'permanent_children_female' 	      => $tm_fact_data['worker_female_child'],
			'previous_worker'					  => !empty($tm_fact_data['worker_prev_total'])?$tm_fact_data['worker_prev_total']:0,
			'worker_total'				     	  => !empty($worker_total)?$worker_total:$telmacregistration[0]['worker'],
			'service_id'				     	  => $service_id,
			'factory_type'				          => $factory_type_id,
			'created_by'				     	  => $created_by,
			'application_id'			          => $caf_id,
			'application_reference_no'   	      => $reference_no,
			'change_date'						 => date('Y-m-d',strtotime($tm_fact_data['worker_female_child']))
			
			
			
			
		);
		$id = db_insert('fa_worker_details')->fields($worker_details)->execute();
		}if((!empty($power_installed) && $power_installed !=0 && $power_installed!=NULL)||(!empty($telmacregistration[0]['power_consume'])&&$telmacregistration[0]['power_consume']!=0 && $telmacregistration[0]['power_consume']!=NULL) ){
			$power_details_yearly =array(
					'power_unit' 				=> 'Hp',
					'installed_power'			=> !empty($power_installed)?$power_installed:$telmacregistration[0]['power_consume']	,				
					'service_id'				=> $service_id,
					'factory_type'				=> $factory_type_id,
					'created_by'				=> $created_by,
					'application_id'			=> $caf_id,
					'application_reference_no'	=> $reference_no,
					'type_power_station'		=>'other',
					'created_date'				=> date('Y-m-d'),
					
						
			);
			$id = db_insert('fa_power_details')->fields($power_details_yearly)->execute(); 
		}
		
	if(!empty($tm_fact_data['director_name'])){
		$director_propieter_details = array(
								'type_director'   					=> $factory_ownershiptype, 
								'name_director'   					=> $tm_fact_data['director_name'], 
								'father_husband_name_director' 		=> $tm_fact_data['director_f_or_h_name'],
								'adress_line1_director'				=> $tm_fact_data['director_present_address'],
								'created_by'						=> $created_by,
								'application_director_id'			=> $caf_id,
								'factory_type_id'					=> $factory_type_id,
								'director_service_id'				=> $service_id,
								'application_reference_no'			=> $reference_no,
								'valid_year'					 	=> NULL,
								'valid_time_period'					=> NULL,
								'starting_year'	     			 	=> NULL,
								'calculate_year_id'				 	=> NULL,
								'application_status'				=> 'In',
								'active_inactive_manager'			=> 1,
								'created_date'						=> date('Y-m-d')
								
							);
		
		
			$id = db_insert('fa_director_details')->fields($director_propieter_details)->execute();	
	}
	
		if(!empty($tm_fact_data['manager_name'])){
			$manager_details = array(
								'name_manager'   	 				=> $tm_fact_data['manager_name'], 
								'age_manager' 	 					=> $tm_fact_data['manager_age'],
								'father_husband_name_manager' 		=> $tm_fact_data['manager_f_or_h_name'],
								'police_station_manager'			=> $tm_fact_data['manager_present_ps'],
								'adress_line1_manager'				=> $tm_fact_data['manager_present_address'],
								'created_by'						=> $created_by,
								'application_manager_id'			=> $caf_id,
								'factory_type_id'					=> $factory_type_id,
								'add_year_manager'					=> '',
								'manager_service_id'				=> $service_id,
								'active_inactive_manager'			=> 1,
								'application_status'				=> 'In',
								'application_reference_no'          => $reference_no,
								'manager_telephone'					=>  $tm_fact_data['manager_phone_no'],
								'manager_phone'						=> $tm_fact_data['manager_mobile_no'],
								'manager_fax'						=> $tm_fact_data['manager_fax_no'],
								'manager_email'						=> $tm_fact_data['manager_email'],
								'valid_year'					 	=> NULL,
								'valid_time_period'					=> NULL,
								'starting_year'	     			 	=> NULL,
								'calculate_year_id'				 	=> NULL,
								'created_date'						=> date('Y-m-d')
							);
		
		}
		
		if(!empty($tm_fact_data['owner_name'])){
			$owner_details = array(

            // owner premises address //
            'owner_name' 							=> $tm_fact_data['owner_name'],
            'addrline_premises' 					=> $tm_fact_data['addrline_premises'],
            'application_status' 					=> 'In',
            'service_id' 							=> $service_id,
            'factory_type_id' 						=> $factory_type_id,
            'created_by' 							=> $created_by,
            'application_id'  		    			=> $caf_id,
            'application_reference_no'  			=> $reference_no,
            'created_date' 							=> date('Y-m-d'),
                );
			$queryabc = db_insert('fa_owner_details')->fields($owner_details)->execute();
		}
		if($telmacregistration[0]['manufacturing_process']!= NULL){
			$nature_work =array(
				'nature_manufacturing' 		          => $telmacregistration[0]['manufacturing_process'],
				'service_id' 		             	  => $service_id,
				'application_id'              		  => $caf_id,
				'manufacturing_application_status' 	  => 'In',
				'factory_type'				     	  => $factory_type_id,
				'created_by'				          => $created_by,
				'application_reference_no'			  => $reference_no,
			);
			$id = db_insert('fa_nature_manufacturing')->fields($nature_work)->execute();
		}
		
		
		
		 if($factory_pollution_type== 4){
			 $document_name = "Authentication Copy of Consent to operate issued by WBPCB for the factories having a hazardous process a defined under section 2(Cb) read with schedule I of factories Act,1948 as amended or a declaration for exempted category industries as notified by the West Bengal Pollution Contril Board";
			$document_listid =  fun_fetch_document_listid($document_name);
		$document_white_category 	= file_load($val['doc_file']);
		if($document_white_category != "" ){
		    $path_category = pathinfo($document_white_category->filename);
				
			
            $new_filename_cat = 'Document_category_'.date('Y').'_'.$factory_typeid.'_'.time().'.'.$path_category['extension'];
            $document_white_category->filename = $new_filename_cat;
            file_save($document_white_category);

            $filename_cat_arr = explode("/", $document_white_category->uri);

            $filepathSave_cat 	= file_get_contents(escapefile_url('public://upload/upload_pdf/'.$filename_cat_arr[4]));
        
               $content_cat		= base64_encode($filepathSave_cat);

            $cat_doc_content_arr = array(
                'upload_doc_content' => $content_cat,
            );
          
					
			$get_int_letter = get_caf_upload_doc_details($caf_id, $service_id, 'INT', $factory_type_id, $reference_no);
			
			
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
					'application_id' 				=> $caf_id,
					'application_reference_no' 		=> $reference_no,
					'file_name' 					=> $new_filename_cat,
					'factory_typeid' 				=> $factory_type_id,
					'service_id' 					=> $service_id,
					'upload_doc_content_id' 		=> $id_doc,
					'upload_doc_type' 				=> 'INT',
					'created_by'					=> $created_by,
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
		
		$tm_factory_info = array('is_active'=>0);
		$queryabc = db_update('tm_factory_mst');
        $queryabc->fields($tm_factory_info);
        $queryabc->condition('factory_id', $factory_id_hidden, '=');
        $queryabc->execute();
		 if($urole == 4){
			 remark_input($reference_no,$caf_id,'In','Add Backlog registarted process is started')	;
		
		 drupal_set_message('Your factory information('.$val['factory_name'].') has been partially submitted.
Please go to the dashboard and click on the edit option according to this factory and complete this process.After the completion process this factory will be active to receive any service from our portal ','waring');
		 drupal_goto('applicant-dashboard');	
		  }else{
			   remark_input($reference_no,$caf_id,'In','This factory is added by AD')	;
		
		 drupal_set_message('Information of this factory ('.$val['factory_name'].') has been partially submitted.
Please go to the LIST OF Factories1 and click on the Add/Edit for Inspection option  and complete this process.After the completion process You can submit inspection report of this factory ','waring');
		 drupal_goto('factory-list-admin/ACTIVE');	
		  }
		
		// drupal_set_message('Factory Information has been saved successfully.');
    } 
	else{
	 		drupal_set_message('Plan Approval number and  Plan Approval date are exists ','error');
		  	$form_state['rebuild'] = true;
		}
}else{
			$cafa_Info = array(
								'modification_date' 		=> date('Y-m-d'),
								'created_by'				=> $created_by,
								'factor_add_inspector'		=> $factor_add_inspector,
								'factor_add_inspector_id'	=> $factor_add_inspector_id
							);
			$queryabc = db_update('fa_cafa');
       	 	$queryabc->fields($cafa_Info);
        	$queryabc->condition('id', $application_no, '=');
       	 	$queryabc->execute();
			 if($urole == 4){
			 remark_input($reference_no,$application_no,'In','Add Backlog registarted process is started')	;
		
		 drupal_set_message('Your factory information('.$val['factory_name'].') has been partially submitted.
Please go to the dashboard and click on the edit option according to this factory and complete this process.After the completion process this factory will be active to receive any service from our portal ','waring');
		 drupal_goto('applicant-dashboard');	
		  }else{
			   remark_input($reference_no,$application_no,'In','This factory is added by AD')	;
		
		 drupal_set_message('Information of this factory ('.$val['factory_name'].') has been partially submitted.
Please go to the LIST OF Factories1 and click on the Add/Edit for Inspection option  and complete this process.After the completion process You can submit inspection report of this factory ','waring');
		 drupal_goto('factory-list-admin/ACTIVE');	
		  }
     
    }
    $form_state['rebuild'] = true;
		

    
		
	}
	else{
		 drupal_set_message('Liccese valid date or registration date or Amenability or Plan Approval date is not in proper date formate.Correct it according to the date of the certificate or Contcat to the office','error');
		  $form_state['rebuild'] = true;
	}
		
	
	
}
?> 