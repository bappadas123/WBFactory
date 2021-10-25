<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function plan_factory_information_old($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$referenceno)
{
    global $base_root, $base_path,$user;
    	$userid = $user->uid;
  
    	$form            	= array();
	 	$service_id      	= encryption_decryption_fun('decrypt', $serviceid);
		$factory_type_id 	= encryption_decryption_fun('decrypt', $factory_typeid);
		$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
		$reference_no 		= encryption_decryption_fun('decrypt', $referenceno); //echo $service_id.'--'.$factory_type_id.'--'.$application_id.'--'.$reference_no;
		
    // $irregularities_details =fun_fetch_irregularities_details();
	 //print_r($irregularities_details);
	
	//$caf_upload_doc_prenission =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'DOC', $factory_type_id,$reference_no, 'premises_address');
	 //print_r($caf_upload_doc_prenission);die;
	 
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
		$get_fa_occupier       = get_all_occupier_data($application_id,$service_id,$factory_type_id,$reference_no);
		$get_fa_owner          = get_all_owner_data($application_id,$service_id,$factory_type_id,$reference_no);
		
		//print_r($get_fa_cafa);die();
        //print_r($get_fa_occupier);die();
		//print_r($get_fa_owner);die();
		
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
		$comm_email     	      = !empty($get_fa_cafa['comm_email'])?$get_fa_cafa['comm_email']:'Not Available'; 
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
    
    
    $form['header']            = array(
        '#markup' => t('<div class="content"><h1><font color ="red">UNDER DEVELOPMENT</font></h1>
		<h3>Application for Approval of Plan.All inputs are provided by applicant only.
All inputs are to be verified by officials</h3>')
    );
	
	 /******************************************** PART FACTORY NAME START ********************************************/

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
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is Factory Name Correct?'),
    );
	
	$value_factory_name     = isset($form_state['values']['factory_name']) ? $form_state['values']['factory_name'] : '';
	$caf_upload_doc_all =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'DOC', $factory_type_id,$reference_no, 'factory_name');
	
	//$j = 1;

	$form['factory_part_info']['factory_name_irregularities_table'] 	= array(
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>Irregularities for Scrutiny of Applications about Name of the Factory </th>
								<th >Action</th>
							</tr>'
			);
	$k = 1;
	
	$identity_flag = 'factory_name';
	$irregularities_details =fun_fetch_irregularities_details($identity_flag);
	
		foreach($irregularities_details as $row_irregularities){
				
		$output .= '<td>';
		$form['factory_part_info']['factory_name_irregularities_'.$k] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			// '#type' 			=> 'textfield',
			'#markup' 	=>!empty($row_irregularities->irregularities_details)? $k.'. '.$row_irregularities->irregularities_details:'',
		);
	          
		$form['factory_part_info']['factory_name_chk_'.$k] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></tr></td>',
			 '#type' 			=> 'checkbox',
    		 '#options'         => $documents_list_check,
  		);
			
		$k=$k+1;
	}
	
	$form['factory_part_info']['factory_name_irregularities_end'] 	= array(
		'#suffix' 	=> '</table><div>',
	);
	
	
	$form['factory_part_info']['documents_list_factory_name'] 	= array(
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12" id="worker_table_id">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>List of supported documents according to Name of factory </th>
								<th >Action</th>
							</tr>'
					);
	$l = 1;
	
		foreach ($caf_upload_doc_all as $record) { 
			
			$fetch_document = fun_fetch_document_listid($record->doc_master_id);
			$document_name = $fetch_document['document_name'];
			$displayLink = l('<i>'.$document_name.'</i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $record->id).'/'.encryption_decryption_fun('encrypt', 'DOC').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
			
			$output .= '<td>';
			$form['factory_part_info']['documents_list_factory_name'.$l] = array(
				 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				 '#suffix' 			=> '</td></div>',
				 '#type' 			=> 'markup',
				 '#markup' 	=>$displayLink,
				
			);
				  
			$form['factory_part_info']['documents_list_chk_'.$l] = array(
				 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				 '#suffix' 			=> '</div></tr></td>',
				 '#type' 			=> 'checkbox',
				 '#options'         => $documents_list_check,
			);
	
			$l=$l+1;
		}
	$form['factory_part_info']['documents_list_factory_name_end'] 	= array(
		'#suffix' 	=> '</table></div>',
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
        '#default_value' 	=> $reg_adress_same_factory,
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
        '#default_value' 	=> $reg_adress_same_factory,
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
        '#default_value' 	=> $reg_adress_same_factory,
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
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is Udyog Aadhaar No Correct?'),
    );
	
/*$plan_approval_no = !empty($backlog_plan_approval_no)?$backlog_plan_approval_no:$plan_approval_no;
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
        '#default_value' 	=> $reg_adress_same_factory,
        
       
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
        '#default_value' 	=> $reg_adress_same_factory,
        
       
        '#title' 			=> t('Is Plan Approval number and date Correct?'),
       
		
    );
  
   }*/
   
   $factory_previous_name = !empty($factory_previous_name)?$factory_previous_name:'Not Available';
   $form['factory_part_info']['factory_previous_name_show'] = array(
            '#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
           '#markup' 			=> '(vi). Previous Name of factory:-'.$factory_previous_name,
       );

	$form['factory_part_info']['factory_previous_name'] = array(
	  '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'factory_previous_name',
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is factory previous name Correct?'),
    );
	
	$form['factory_part_info']['cin_no_show'] = array(
		   '#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
		   '#markup' 			=> '(vii). CIN number:-'.$cin_no,
		   '#required' 		=> TRUE,
		);
	$form['factory_part_info']['cin_no'] = array(
	    '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'cin_no',
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is CIN number Correct?'),
    );
	$form['factory_part_info']['enargy_no_show'] = array(
		'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
		'#suffix' 			=> '</div>',
		'#type' 				=> 'markup',
		'#markup' 			=> '(viii).Energy Meter No:-'.$enargy_meter_no,
		'#type' 			=> 'markup',
	);
	$form['factory_part_info']['enargy_no'] = array(
	  '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'enargy_no',
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is Energy Meter No Correct?'),
    );
	
	/******************************************** PART FACTORY NAME END ********************************************/	
	
	
	/******************************************** LOCATION OF THE FACTORY START ********************************************/
	
	$factory_zone = get_factory_zone_name($get_fa_cafa['factory_zone']);
		$getdata_factory_location	 =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
		$factory_address_location 	 = $get_fa_cafa['addrline'].'<br/>Near by:- '.$nearest_landmark.',JL Number:-'.$jl_number.',Mouza Number:-'.$mouza_name.',<br/>'.get_full_address('fa_cafa','sub-table',$get_fa_cafa['id'],$getdata_factory_location);
		$getdata_headoffice_address  =  array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
		$headoffice_address 		 = $get_fa_cafa['addrline_off'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_fa_cafa['id'],$getdata_headoffice_address);
		
		$getdata_communication_address = array('district_comm','subdivision_comm','areatype_comm','block_comm','panchayat_comm','policestation_comm','pincodecomm','state_comm','postoffice_comm');
		$communication_address 		= $get_fa_cafa['addrline_comm'].',
		<br/>'.get_full_address('fa_cafa','sub-table',$get_fa_cafa['id'],$getdata_communication_address);
		
		
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
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is Factory situated at Correct?'),
    );
	
	$form['factory_part_a']['factory_addres_irregularities_table'] 	= array(
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>Irregularities for Scrutiny of Applications about Location of the Factory </th>
								<th >Action</th>
							</tr>'
					);
	
	$m = 1;
	
	$identity_flag = 'premises_address';
		$irregularities_details =fun_fetch_irregularities_details($identity_flag);
	
		foreach($irregularities_details as $row_irregularities){
			
		$output .= '<td>';
		$form['factory_part_a']['factory_addres_irregularities_'.$m] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			// '#type' 			=> 'textfield',
			'#markup' 	=>!empty($row_irregularities->irregularities_details)? $m.'. '.$row_irregularities->irregularities_details:'',
		);
	          
		$form['factory_part_a']['factory_addres_chk_'.$m] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></tr></td>',
			 '#type' 			=> 'checkbox',
    		 '#options'         => $documents_list_check,
  		);
			
		$m=$m+1;
	}
	
	$form['factory_part_info']['factory_addres_irregularities_end'] 	= array(
		'#suffix' 	=> '</table><div>',
	);
	$form['factory_part_a']['documents_list_factory_adress'] 	= array(
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12" id="worker_table_id">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>List of supported documents according to Location of factory </th>
								<th >Action</th>
							</tr>'
					);
	
	$n = 1;
	
	$caf_upload_doc_prenission =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'DOC', $factory_type_id,$reference_no, 'premises_address');
	//print_r($caf_upload_doc_all1);die;
	
		foreach ($caf_upload_doc_prenission as $record) {
			
		$fetch_document = fun_fetch_document_listid($record->doc_master_id);
		$document_name = $fetch_document['document_name'];
		$displayLink = l('<i>'.$document_name.'</i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $record->id).'/'.encryption_decryption_fun('encrypt', 'DOC').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
		
		$output .= '<td>';
		$form['factory_part_a']['documents_list_factory_adress'.$n] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			 '#type' 			=> 'markup',
			'#markup' 	=>$displayLink,
		);
	          
		$form['factory_part_a']['documents_list_factory_adress_chk_'.$n] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></tr></td>',
			 '#type' 			=> 'checkbox',
    		 '#options'         => $documents_list_check,
  		);
		
		$n=$n+1;
	}
	$form['factory_part_a']['documents_list_factory_adress_end'] 	= array(
		'#suffix' 	=> '</table></div>',
	);
	
	
	$form['factory_part_a']['markup_no_show1'] = array(
			'#prefix' 			=> '<div class="row">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '<br/>'
		);
	
	$form['factory_part_a']['telephone_no_show'] = array(
			'#prefix' 			=> '</div><div class="row"><div class="col-md-6 col-xs-6">',
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
        '#default_value' 	=> $reg_adress_same_factory,
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
        '#default_value' 	=> $reg_adress_same_factory,
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
        '#default_value' 	=> $reg_adress_same_factory,
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
        '#default_value' 	=> $reg_adress_same_factory,
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
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is Fax Number Correct?'),
    );
	
	/******************************************** LOCATION OF THE FACTORY END ********************************************/

	
	/******************************************** ADDRESS OF REGISTERED OFFICE/HEAD OFFICE START ********************************************/
	
    $form['factory_part_off']              = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('C. Address of the Registered office / Head office'),
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
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is Factory situated at Correct?'),
    );
	
	/******************************************** ADDRESS OF REGISTERED OFFICE/HEAD OFFICE END ********************************************/
	
	
	/******************************************** COMMUNICATION ADDRESS START ********************************************/
	
	$form['factory_part_comm']              = array(
        '#type' => 'fieldset',
        '#title' => t('D. Communication Address'),
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
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is Factory situated at Correct?'),
    );

	/******************************************** COMMUNICATION ADDRESS END ********************************************/
	

	/******************************************** OCCUPIER PERMANENT ADDRESS START ********************************************/
	
		
		$getdata_permanent_address = array('district_oprmntadr','subdivision_oprmntadr','areatype_oprmntadr','block_oprmntadr','panchayat_oprmntadr','policestation_oprmntadr','pincodeoprmntadr','state_oprmntadr','postoffice_oprmntadr');
		$permanent_address 		= $get_fa_cafa['addrline_oprmntadr'].',
		<br/>'.get_full_address('fa_occupier_details','sub-table',$get_fa_occupier[0]->id,$getdata_permanent_address);
		
		$getdata_present_address = array('district_oprsntadr','subdivision_oprsntadr','areatype_oprsntadr','block_oprsntadr','panchayat_oprsntadr','policestation_oprsntadr','pincodeoprsntadr','state_oprsntadr','postoffice_oprsntadr');
		$present_address 		= $get_fa_cafa['addrline_oprsntadr'].',
		<br/>'.get_full_address('fa_occupier_details','sub-table',$get_fa_occupier[0]->id,$getdata_present_address);
		
		
		
	$form['factory_occupier'] = array(
        '#type'			=> 'fieldset',
        '#title' 		=> t('B. Occupier Details'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	
	$form['factory_occupier']['permanent_address_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(i).Permanent Address:-<br/>'.$permanent_address,
			'#type' 			=> 'markup',
		);
	$form['factory_occupier']['permanent_address'] = array(
	  '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'permanent_address',
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is Permanent address Correct?'),
    );

	$form['factory_occupier']['present_address_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(i).Permanent Address:-<br/>'.$present_address,
			'#type' 			=> 'markup',
		);
	$form['factory_occupier']['present_address'] = array(
	  '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'present_address',
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is Present address Correct?'),
    );

	$form['factory_occupier']['permanent_addres_irregularities_table'] 	= array(
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>Irregularities for Scrutiny of Applications about Location of the Factory </th>
								<th >Action</th>
							</tr>'
					);
	
		$output .= '<td>';
		$form['factory_occupier']['permanent_address_irregularities_1'] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			// '#type' 			=> 'textfield',
			'#markup' 	=>!empty($row_irregularities->irregularities_details)? $m.'. '.$row_irregularities->irregularities_details:'',
		);
	          
		$form['factory_occupier']['permanent_addres__chk_'.$m] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></tr></td>',
			 '#type' 			=> 'checkbox',
    		 '#options'         => $documents_list_check,
  		);
	
	$form['factory_occupier']['permanent_addres_irregularities_end'] 	= array(
		'#suffix' 	=> '</table><div>',
	);
	
	
	$form['factory_oprmntadr']['markup_no_show1'] = array(
			'#prefix' 			=> '<div class="row">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '<br/>'
		);
	
	$form['factory_occupier']['name_occupier_show'] = array(
			'#prefix' 			=> '</div><div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(ii).Name:-'.$get_fa_occupier[0]->name_occupier.' (Age :'.$get_fa_occupier[0]->age_occupier.'),
			'#type' 			=> 'markup',
		);
	$form['factory_occupier']['name_occupier'] = array(
	  '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'name_occupier',
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is Name Correct?'),
    );
	
	$form['factory_occupier']['father_husband_name_occupier_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(iii).Father/Husband name:-'.$get_fa_occupier[0]->father_husband_name_occupier,
			'#type' 			=> 'markup',
	);
	
	$form['factory_occupier']['father_husband_name_occupier'] = array(
	    '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'father_husband_name_occupier',
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is Gurdian name Correct?'),
    );
	
	$form['factory_occupier']['occupier_telephone_show'] = array(
		'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
		'#suffix' 			=> '</div>',
		'#type' 				=> 'markup',
		'#markup' 			=> '(iv).Telephone Number :-'.$get_fa_occupier[0]->occupier_telephone,
		'#type' 			=> 'markup',
	);
	$form['factory_occupier']['occupier_telephone'] = array(
	  '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'occupier_telephone',
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is Telephone number Correct?'),
    );
	
	
	$form['factory_occupier']['occupier_mobile_show'] = array(
		'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
		'#suffix' 			=> '</div>',
		'#type' 				=> 'markup',
		'#markup' 			=> '(iv).Registered Mobile Number :-'.$get_fa_occupier[0]->occupier_mobile,
		'#type' 			=> 'markup',
	);
	$form['factory_occupier']['occupier_mobile'] = array(
	  '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'occupier_mobile',
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is mobile number Correct?'),
    );
	
	$form['factory_occupier']['occupier_email_id_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(v).Email Id:-'.$get_fa_occupier[0]->occupier_email_id,
			'#type' 			=> 'markup',
		);
		
	$form['factory_occupier']['occupier_email_id'] = array(
	  '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'occupier_email_id',
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is Email Id Correct?'),
    );
	
	$form['factory_occupier']['occupier_fax_no_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(vi).Fax Number:-'.$get_fa_occupier[0]->occupier_fax_no,
			'#type' 			=> 'markup',
		);
		
	$form['factory_occupier']['occupier_fax_no'] = array(
	  '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'occupier_fax_no',
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is Fax Number Correct?'),
    );
	

	/******************************************** OCCUPIER PERMANENT ADDRESS END ********************************************/


	/******************************************** OWNER ADDRESS START ********************************************/

		$getdata_owner_address = array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
		$owner_address 		= $get_fa_cafa['addrline_premises'].',
		<br/>'.get_full_address('fa_owner_details','sub-table',$get_fa_owner[0]->id,$getdata_owner_address);

	$form['factory_owner']              = array(
        '#type' => 'fieldset',
        '#title' => t('D. OWNER details'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
	
	$form['factory_owner']['name_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(i).Name:- '.$get_fa_owner[0]->owner_name.' '.$get_fa_owner[0]->owner_mname.' '.$get_fa_owner[0]->owner_lname,
			'#type' 			=> 'markup',
		);
	$form['factory_owner']['name'] = array(
	  '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'name',
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is Name Correct?'),
    );


	$form['factory_owner']['address_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(i).Address :- '.$owner_address,
			'#type' 			=> 'markup',
		);
	$form['factory_owner']['address'] = array(
	  '#prefix'			=> '<div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'address',
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is Address Correct?'),
    );
	/******************************************** OWNER END ********************************************/


	/******************************************** WBPCB CATEGORY START ********************************************/
		 
    $form['factory_catagory'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('F. Factory Identification according to WBPCB'),
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
	}
	
	if($wbpcb_category_name == 2){
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
	}
	
	if($wbpcb_category_name == 3){
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
	}
	
	if($wbpcb_category_name == 4){
		$category_show = "WHITE";
		$form['factory_catagory']['category_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
          '#suffix' 			=> '</div></div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(i).Categories of wbpcb:-'.$category_show,
			'#type' 			=> 'markup',
			
		);
	}if($wbpcb_category_name == 5){
		$category_show = "EXAMPTED";
		$form['factory_catagory']['category_show'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6">',
          '#suffix' 			=> '</div></div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '(i).Categories of wbpcb:-'.$category_show,
			'#type' 			=> 'markup',
			
		);
	}
	
	$value_wbpcd_id     = isset($form_state['values']['factory_name']) ? $form_state['values']['factory_name'] : '';
	$caf_upload_doc_all =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'DOC', $factory_type_id,$reference_no, 'wbpcb_id');
	
	$form['factory_catagory']['wbpcd_id_irregularities_table'] 	= array(
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>Irregularities for Scrutiny of Applications about Clearance from Pollution Control Board  </th>
								<th >Action</th>
							</tr>'
			);
	$p = 1;
	
	$identity_flag = 'wbpcb_id';
	$irregularities_details =fun_fetch_irregularities_details($identity_flag);
	
		foreach($irregularities_details as $row_irregularities){
				
		$output .= '<td>';
		$form['factory_catagory']['wbpcd_id_irregularities_'.$p] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			// '#type' 			=> 'textfield',
			'#markup' 	=>!empty($row_irregularities->irregularities_details)? $p.'. '.$row_irregularities->irregularities_details:'',
		);
	          
		$form['factory_catagory']['wbpcd_id_chk_'.$p] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></tr></td>',
			 '#type' 			=> 'checkbox',
    		 '#options'         => $documents_list_check,
  		);
			
		$p=$p+1;
	}
	
	$form['factory_catagory']['wbpcd_id_irregularities_end'] 	= array(
		'#suffix' 	=> '</table><div>',
	);
	
	
	$form['factory_catagory']['documents_list_wbpcd_id'] 	= array(
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12" id="worker_table_id">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>List of supported documents according to Clearance from Pollution Control Board  </th>
								<th >Action</th>
							</tr>'
					);
	$l = 1;
	
		foreach ($caf_upload_doc_all as $record) { 
			
			$fetch_document = fun_fetch_document_listid($record->doc_master_id);
			$document_name = $fetch_document['document_name'];
			$displayLink = l('<i>'.$document_name.'</i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $record->id).'/'.encryption_decryption_fun('encrypt', 'DOC').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
			
			$output .= '<td>';
			$form['factory_catagory']['documents_list_factory_name'.$l] = array(
				 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
				 '#suffix' 			=> '</td></div>',
				 '#type' 			=> 'markup',
				 '#markup' 	=>$displayLink,
				
			);
				  
			$form['factory_catagory']['documents_list_chk_'.$l] = array(
				 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
				 '#suffix' 			=> '</div></tr></td>',
				 '#type' 			=> 'checkbox',
				 '#options'         => $documents_list_check,
			);
	
			$l=$l+1;
		}
	$form['factory_catagory']['documents_list_wbpcd_id_end'] 	= array(
		'#suffix' 	=> '</table></div>',
	);

	$form['factory_catagory']['wbpcb_id'] = array(
	  '#prefix'			=> '</div><div class="row"><div class="col-md-6 col-xs-6">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'wbpcb_id',
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is Correct?'),
   );

	/******************************************** WBPCB CATEGORY END ********************************************/

	/******************************************** PLAN RELATED START ********************************************/
	
		
	$form['plan_related'] = array(
        '#type'			=> 'fieldset',
        '#title' 		=> t('B. Plan Related'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	
	$form['plan_related']['plan_related_irregularities_table'] 	= array(
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>Irregularities for Scrutiny of Applications about Plan Related </th>
								<th >Action</th>
							</tr>'
					);
	
	$r = 1;
	
	$identity_flag = 'plan_related';
		$irregularities_details =fun_fetch_irregularities_details($identity_flag);
	
		foreach($irregularities_details as $row_irregularities){
			
		$output .= '<td>';
		$form['plan_related']['factory_addres_irregularities_'.$r] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			// '#type' 			=> 'textfield',
			'#markup' 	=>!empty($row_irregularities->irregularities_details)? $r.'. '.$row_irregularities->irregularities_details:'',
		);
	          
		$form['plan_related']['factory_addres_chk_'.$m] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></tr></td>',
			 '#type' 			=> 'checkbox',
    		 '#options'         => $documents_list_check,
  		);
			
		$r=$r+1;
	}
	
	$form['plan_related']['factory_addres_irregularities_end'] 	= array(
		'#suffix' 	=> '</table><div>',
	);
	$form['plan_related']['documents_list_factory_adress'] 	= array(
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12" id="worker_table_id">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th>List of supported documents according to Location of factory </th>
								<th >Action</th>
							</tr>'
					);
	
	$s = 1;
	
	$caf_upload_doc_prenission =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'DOC', $factory_type_id,$reference_no, 'plan_related');
	//print_r($caf_upload_doc_all1);die;
	
		foreach ($caf_upload_doc_prenission as $record) {
			
		$fetch_document = fun_fetch_document_listid($record->doc_master_id);
		$document_name = $fetch_document['document_name'];
		$displayLink = l('<i>'.$document_name.'</i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $record->id).'/'.encryption_decryption_fun('encrypt', 'DOC').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
		
		$output .= '<td>';
		$form['plan_related']['documents_list_factory_adress'.$s] = array(
			 '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</td></div>',
			 '#type' 			=> 'markup',
			'#markup' 	=>$displayLink,
		);
	          
		$form['plan_related']['documents_list_factory_adress_chk_'.$s] = array(
   			 '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
       		 '#suffix' 			=> '</div></tr></td>',
			 '#type' 			=> 'checkbox',
    		 '#options'         => $documents_list_check,
  		);
		
		$s=$s+1;
	}
	$form['plan_related']['documents_list_factory_adress_end'] 	= array(
		'#suffix' 	=> '</table></div>',
	);
	
	
	$form['factory_part_a']['markup_no_show1'] = array(
			'#prefix' 			=> '<div class="row">',
           '#suffix' 			=> '</div>',
		   '#type' 				=> 'markup',
			'#markup' 			=> '<br/>'
		);
	
	$form['factory_part_a']['telephone_no_show'] = array(
			'#prefix' 			=> '</div><div class="row"><div class="col-md-6 col-xs-6">',
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
        '#default_value' 	=> $reg_adress_same_factory,
        '#title' 			=> t('Is Telephone No Correct?'),
    );
	
	
	/******************************************** LOCATION OF THE FACTORY END ********************************************/







	
	
	
	
	
	
	
	
	
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
		
	}
	$form['worker_number'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('G. No. Of Workers'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	$form['worker_number']['previous_table'] 	= array(
  			
  			'#type'		=> 'markup',
			'#markup'   =>'Maximum number of workers employed or to be employed in tha factory',
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

  $form['worker_number']['per_worker_men'] = array(
				'#prefix' 			=> '<tr><td><div class="col-xs-12">',
			  	'#suffix' 	 		=> '</div></td>',
			   	'#type' 			=> 'markup',
			 	'#markup'			=> $permanent_worker_men, 
			  	
			);
  $form['worker_number']['per_worker_women'] = array(
				 '#prefix' 				=> '<td><div class="col-xs-12">',
				 '#suffix' 	 			=> '</div></td>',
				 '#type' 				=> 'markup',
				 '#markup'				=> $permanent_worker_women, 
				 
			);
  $form['worker_number']['per_worker_adol_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#type' 				=> 'markup',
			  '#markup'				=> $permanent_adolescents_male, 
			  
		);
  
  $form['worker_number']['per_worker_adol_women'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#type' 				=> 'markup',
			  '#markup'		=> $permanent_adolescents_female, 
			 
			);
  $form['worker_number']['per_worker_child_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#type' 				=> 'markup',
			  '#markup'				=> $permanent_children_male, 
			 
			);
  $form['worker_number']['per_worker_child_women'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#type' 				=> 'markup',
			  '#markup'				=> $permanent_children_female, 
			  
			);
  $form['worker_number']['con_worker_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#type' 				=> 'markup',
			  '#markup'				=> $contactual_worker_men, 
			  
			);
  $form['worker_number']['con_worker_women'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			   '#type' 				=> 'markup',
			 
			  '#markup'		=>$contactual_worker_women, 
			 
			);
  $form['worker_number']['con_worker_adol_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#type' 				=> 'markup',
			  '#markup'		=> $contactual_adolescents_male, 
			  
		);
  $form['worker_number']['con_worker_adol_women'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				   '#type' 				=> 'markup',
				  '#markup'		=> $contactual_adolescents_male, 
				
			);
  $form['worker_number']['con_worker_child_men'] = array(
			 '#prefix' 				=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#type' 				=> 'markup',
			  '#markup'				=> $contactual_adolescents_male, 
			
		);
  $form['worker_number']['con_worker_child_woman'] = array(
			 '#prefix' 				=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td></tr>',
			  '#type' 				=> 'markup',
			  '#markup'		=> $contactual_children_female, 
			  
			);
	
  $form['worker_number']['previous_table_end'] 	= array(
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
		$form['worker_number']['worker_details'] = array(
	  '#prefix'			=> '<div class="row"><div class="col-md-12 col-xs-12">',
        '#suffix' 			=> '</div></div>',
        '#type' 			=> 'checkbox',
		'#id'				=> 'worker_details',
        '#default_value' 	=> $reg_adress_same_factory,
        
       
        '#title' 			=> t('Is Maximum number of workers employed or to be employed in the factory Correct?'),
       
		
    );

   
	  $form['submit'] = array(
        '#prefix' => '<div class="col-md-1">',
        '#suffix' => '</div>',
        '#attributes' => array('class' => array('btn btn-success')),
        '#type' => 'submit',
        '#value' => 'Save'
    );
    return $form;
}




function get_irregularities($form, $form_state){
    $commands   = array();
	
	$commands[] = ajax_command_replace('#factory_name_irregularities_id', drupal_render($form['factory_part_info']['factory_name_irregularities']));
	$commands[] = ajax_command_replace('#documents_list_factory_name_id', drupal_render($form['factory_part_info']['documents_list_factory_name']));
    return array( '#type' => 'ajax', '#commands' => $commands);
}





function plan_factory_information_old_submit($form, &$form_state)
{
	
	 global $user;
	  $uid = $user->uid;
	  $remark_by_name			= get_name($uid);
	  $val   					= 	$form_state['values'];
	  //print_r($val);die;
}
?> 