<?php
  drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
  drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
  
  function form20_form($form, &$form_state,$formid ,$referenceid, $factorytypeid, $serviceid){
	  
	  global $user;
	  $uid 						= $user->uid;
	  
	$form_id 	 	= encryption_decryption_fun('decrypt', $formid);
	$reference_id   = encryption_decryption_fun('decrypt', $referenceid);
	$factory_typeid 	= encryption_decryption_fun('decrypt', $factorytypeid);
	$service_id 	= encryption_decryption_fun('decrypt', $serviceid); //echo $form_id.'--'.$reference_id.'--'.$factory_typeid.'--'.$service_id;

	if($form_id != '')
	  { 
		$get_all_data 		= get_notice_poisoning_data($form_id,$reference_id,$factory_typeid,$service_id);
	  } 

	$form['notice_poisioning'] = array(
			'#type' 			=> 'fieldset',
			'#title' 			=> t('Notice of Poisoning or Disease'),
			'#collapsible' 		=> TRUE, // Added
			'#collapsed' 		=> FALSE,  // Added
		);		
	$form['formid_hidden'] 		= array(
		'#type' 				=> 'hidden',
		'#default_value' 		=> $formid
	);	
	$form['serviceid_hidden'] 		= array(
		'#type' 				=> 'hidden',
		'#default_value' 		=> $serviceid
	);

	$option = array( "Yes" => "Yes", "No" => "No");
	$form['notice_poisioning']['is_registered'] = array(
        '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-6"><label class="select label-block">',
        '#suffix' 			=> '</label></div>',
		'#title' 			=> t('(i) Is it a registered factory ?'),
		'#options'			=> $option,
		'#type' 			=> 'radios',
		'#required' 		=> TRUE,
		'#default_value' 	=> !empty($get_all_data[0]->is_registered) ? $get_all_data[0]->is_registered : '',
		'#ajax' 			=> array(
								'event' 		=> 'change',
								'effect' 		=> 'fade',
								'callback' 		=> 'get_ajax_name_factory',
								'progress' 		=> array(
								'type' 			=> 'throbber',
								'message' 		=> t('loading')
							)
			 )
	);
	 $value_is_registered = isset($form_state['values']['is_registered']) ? $form_state['values']['is_registered'] : $get_all_data[0]->is_registered;
	 
	 if($value_is_registered =='Yes')
	 {
		$form['notice_poisioning']['factory_id'] = array(
        '#prefix' 			=> '<div id="factory_id_id"><div class="col-md-4 col-xs-6"><label class="select label-block">',
        '#suffix' 			=> '</label></div></div>',
        '#title' 			=> t('(i) Choose Factory Registration & License No.'),
        '#options' 			=> get_factory_LIC_REG_NO($uid),
        //'#options' 			=> get_factory_name($uid),
        '#type' 			=> 'select',
        '#default_value'    => $get_all_data[0]->factory_id,
        '#required' 		=> TRUE,
		'#ajax' 			=> array(
									'event' 		=> 'change',
									'effect' 		=> 'fade',
									'callback' 		=> 'get_ajax_name_factory',
									'progress' 		=> array(
									'type' 			=> 'throbber',
									'message' 		=> t('loading')
								)
       			 )
    );

	$value_factory_id = (isset($form_state['values']['factory_id'])) ? $form_state['values']['factory_id'] : $get_all_data[0]->factory_id;	
	
	
	if(!empty($value_factory_id)){
		
		$getdata_factory_address = array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
		$factory_address = get_full_address('fa_cafa','sub-table',$value_factory_id,$getdata_factory_address);
		$full_factory_address = trim($factory_address);
		//echo "<pre>"; print_r($factory_address);
		
		$get_registration_value = get_reg_lic_no_form20($value_factory_id);
		//echo "SM<pre>"; print_r($get_registration_value); die;
		//echo $get_registration_value['factory_name'];
	}
	
	$service_id     = $get_registration_value['service_id'];
	$application_id = $value_factory_id;
	
	/****************************** REGISTRATION NUMBER ******************************/
	if((!empty($get_registration_value['factory_registrstion_no'])) && (empty($get_registration_value['backlog_registration_no'])) && (empty($get_registration_value['tm_factory_registration_no'])))
	{
		$RegistrationNo = $get_registration_value['factory_registrstion_no'];
	} 
	elseif((empty($get_registration_value['factory_registrstion_no'])) && (!empty($get_registration_value['backlog_registration_no'])) && (empty($get_registration_value['tm_factory_registration_no'])))
	{
		$RegistrationNo = $get_registration_value['backlog_registration_no'];
	}
	elseif((empty($get_registration_value['factory_registrstion_no'])) && (empty($get_registration_value['backlog_registration_no'])) && (!empty($get_registration_value['tm_factory_registration_no'])))
	{
		$RegistrationNo = $get_registration_value['tm_factory_registration_no'];
	}

	/****************************** REGISTRATION DATE ******************************/
	if((!empty($get_registration_value['registration_date'])) && (empty($get_registration_value['backlog_registration_date'])))
	{
		$RegistrationDate = trim(implode('-', array_reverse(explode('-',$get_registration_value['registration_date']))));
	} 
	elseif((empty($get_registration_value['registration_date'])) && (!empty($get_registration_value['backlog_registration_date'])))
	{
		$RegistrationDate = trim(implode('-', array_reverse(explode('-',$get_registration_value['backlog_registration_date']))));
	}

	/****************************** LICENCE NUMBER ******************************/
	if((!empty($get_registration_value['factory_license_no'])) && (empty($get_registration_value['backlog_license_number'])))
	{
		$LicenceNo = $get_registration_value['factory_license_no'];
	} 
	elseif((empty($get_registration_value['factory_license_no'])) && (!empty($get_registration_value['backlog_license_number'])))
	{
		$LicenceNo = $get_registration_value['backlog_license_number'];
	}

	/****************************** LICENCE DATE ******************************/
	if((!empty($get_registration_value['license_date'])) && (empty($get_registration_value['backlog_license_date'])))
	{
		$LicenceDate = trim(implode('-', array_reverse(explode('-',$get_registration_value['license_date']))));
	} 
	elseif((empty($get_registration_value['license_date'])) && (!empty($get_registration_value['backlog_license_date'])))
	{
		$LicenceDate = trim(implode('-', array_reverse(explode('-',$get_registration_value['backlog_license_date']))));
	}
	
	/*****************************Classification No****************************/
	if(!empty($get_registration_value['classification_no']))
	{
		$ClassificationNo = $get_registration_value['classification_no'];
	}
	
	
	$FactoryTypeid          = $get_registration_value['factory_typeid'];
	$ReferenceNumber        = $get_registration_value['reference_number'];
	$FactoryName            = $get_registration_value['factory_name'];
	$factory_pincode        = $get_registration_value['pincode'];
	$factory_state          = $get_registration_value['state'];
	$factory_district 	    = $get_registration_value['district'];
	$factory_subdivision    = $get_registration_value['subdivision'];
	$factory_areatype       = $get_registration_value['areatype'];
	$factory_block          = $get_registration_value['block'];
	$factory_panchayat      = $get_registration_value['panchayat'];
	$factory_policestation  = $get_registration_value['policestation'];
	$factory_postoffice     = $get_registration_value['postoffice'];
	$nearest_landmark       = $get_registration_value['nearest_landmark'];
	$factory_addrline		= $get_registration_value['addrline'];
	$IndustryNature		    = $get_registration_value['nature_manufacturing'];
		
		if(!empty($value_factory_id))
		{ 
			$form['notice_poisioning']['factory_typeid'] = array(
				'#prefix' 			=> '<div id="factory_typeid_id"><label class="select label-block">',
				'#suffix' 			=> '</label></div>',
				'#title' 			=> t('(i)a. Enter factory_typeid'),
				'#type' 			=> 'hidden',
				'#value' 			=> !empty($FactoryTypeid) ? $FactoryTypeid : '',
			);
			$form['notice_poisioning']['reference_number'] = array(
				'#prefix' 			=> '<div id="reference_number_id"><label class="select label-block">',
				'#suffix' 			=> '</label></div>',
				'#title' 			=> t('(i)a. Enter reference_number'),
				'#type' 			=> 'hidden',
				'#value' 			=> !empty($ReferenceNumber) ? $ReferenceNumber : '',
			);
			$form['notice_poisioning']['factory_name'] = array(
				'#prefix' 			=> '<div id="factory_name_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(i)a. Enter Registered Factory Name'),
				'#type' 			=> 'textfield',
				'#value' 			=> !empty($FactoryName) ? $FactoryName : '',
			);
		
		//factory address section
	
	   $form['notice_poisioning']['pincode']       = array(
			'#prefix' 				=> '<div id="pincode_id"><div class="col-md-4 col-xs-12"><label class="select label-block">',
			'#suffix' 				=> '</label></div></div>',
			'#attributes' 			=> array('class' => array(),'placeholder' => 'Pincode','readonly' => 'readonly'),
			'#maxlength' 		 	=> 6,
			'#title' 			 	=> t('(ii) Pincode'),
			'#value' 	 	        => !empty($factory_pincode) ? $factory_pincode : '',
			'#required' 			=> TRUE,
			'#type' 				=> 'textfield',
		);
		
		$form['notice_poisioning']['state'] = array(
			'#title' 		=> '(iii) State',
			'#type' 		=> 'select',
			'#id' 			=> 'state_name',
			'#attributes' 	=> array('placeholder' => 'State','readonly' => 'readonly'),
			'#options' 		=> get_all_state($factory_state),
			'#value' 	 	=> !empty($factory_state) ? $factory_state : '',
			'#required' 	=> TRUE,
			'#prefix' 		=> '<div id="ld_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
			'#suffix' 		=> '</label></div></div>',
		);
	
		$form['notice_poisioning']['district'] = array(
			'#title' => '(iv) District',
			'#type' => 'select',
			'#id' => 'district_name',
			'#attributes' => array('placeholder' => 'District','readonly' => 'readonly'),
			'#options' => get_district_by_id($factory_state),
			'#value' 	=> !empty($factory_district) ? $factory_district : '',
			'#required' => TRUE,
			'#prefix' => '<div id="ld_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
			'#suffix' => '</label></div></div>',
		);
			
		$form['notice_poisioning']['subdivision'] = array(
			'#title' => '(v) Sub-Division',
			'#type' => 'select',
			'#attributes' => array('placeholder' => 'Sub Division','readonly' => 'readonly'),
			'#options' => common_custom_user_subdivisionlist_list_new($factory_district),
			'#required' => TRUE,
			'#value' 	=> !empty($factory_subdivision) ? $factory_subdivision : '',
			'#prefix' => '<div id="ld_empsubdv_replace"><div class="col-md-4"><label class="select label-block">',
			'#suffix' => '</label></div></div>',
		);
		
		$form['notice_poisioning']['areatype'] = array(
			'#title' => '(vi) Area Type',
			'#type' => 'select',
			'#attributes' => array('placeholder' => 'Area Type','readonly' => 'readonly'),
			'#options' => common_custom_user_areatype_list_new($factory_district, $factory_subdivision),
			'#required' => TRUE,
			'#value' 	=> !empty($factory_areatype) ? $factory_areatype : '',
			'#prefix' => '<div id="ld_emp_areatype_replace"><div class="col-md-4"><label class="select label-block">',
			'#suffix' => '</label></div></div>',
		);
		
			if ($factory_areatype == 'B') {
				$areatype_name = 'Block';
			} elseif ($factory_areatype == 'M') {
				$areatype_name = 'Municipality';
			} elseif ($factory_areatype == 'C') {
				$areatype_name = 'Corporation';
			} elseif ($factory_areatype == 'S') {
				$areatype_name = 'SEZ';
			} elseif ($factory_areatype == 'N') {
				$areatype_name = 'Notified Area';
			}
			
		$form['notice_poisioning']['block'] = array(
			'#title' 		=> '(vii) '. $areatype_name,
			'#type'         => 'select',
			'#attributes'   => array('placeholder' => 'subdivision','readonly' => 'readonly'),
			'#options' 		=> common_custom_user_block_list_new($factory_subdivision, $factory_areatype),
			'#required' 	=> TRUE,
			'#value' 	    => !empty($factory_block) ? $factory_block : '',
			'#prefix' 		=> '<div id="ld_empareatype_name_replace"><div class="col-md-4"><label class="select label-block">',
			'#suffix' 		=> '</label></div></div>',
		);
	
			if ($factory_areatype == 'B') {
				$area_name = 'Gram Panchayat';
				$area_code = 'V';
			} elseif ($factory_areatype == 'M') {
				$area_name = 'Ward';
				$area_code = 'W';
			} elseif ($factory_areatype == 'C') {
				$area_name = 'Ward';
				$area_code = 'C';
			} elseif ($factory_areatype == 'S') {
				$area_name = 'Sector';
				$area_code = 'S';
			} elseif ($factory_areatype == 'N') {
				$area_name = 'Notified Area';
				$area_code = 'N';
			}
			
		$form['notice_poisioning']['panchayat'] = array(
			'#title' => '(viii) '.$area_name,
			'#type' => 'select',
			'#attributes' => array('placeholder' => 'panchayat','readonly' => 'readonly'),
			'#options' => common_custom_user_villward_list_new($factory_block, $area_code),
			'#value' 	    => !empty($factory_panchayat) ? $factory_panchayat : '',
			'#prefix' => '<div id="ld_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
			'#suffix' => '</label></div></div>',
			'#required' => TRUE,
		);
		
		$form['notice_poisioning']['policestation'] = array(
			'#title' => '(ix) Police Station',
			'#type' => 'select',
			'#attributes' => array('placeholder' => 'Police Station','readonly' => 'readonly'),
			'#options' => common_custom_user_ps_list_new($factory_district),
			'#required' => TRUE,
			'#value' 	    => !empty($factory_policestation) ? $factory_policestation : '',
			'#prefix' => '<div id="ld_empps_replace"><div class="col-md-4"><label class="select label-block">',
			'#suffix' => '</label></div></div>'
		);
	
		$form['notice_poisioning']['postoffice'] = array(
			'#title' => '(x) Post Office',
			'#type' => 'select',
			'#attributes' => array('placeholder' => 'Post Office','readonly' => 'readonly'),
			'#options' => common_custom_post_office_list_new($factory_pincode),
			'#value' 	    => !empty($factory_postoffice) ? $factory_postoffice : '',
			'#required' => TRUE,
			'#prefix' => '<div id="ld_post_office_div"><div class="col-md-4"><label class="select label-block">',
			'#suffix' => '</label></div></div>'
		);
	
		$factory_zone_name = get_zone_name($factory_block,$factory_panchayat);
		
			$form['notice_poisioning']['factory_zone'] = array(
				'#value'   => $factory_zone_name[0]->zone_id,
				'#type' => 'hidden',
			);
			
			$form['notice_poisioning']['factory_zone_name'] = array(
				'#prefix' => '<div id="factory_zone_div"><div class="col-md-4"><label class="input label-block">',
				'#suffix' => '</label></div></div>',
				'#title'  => t('(xi) Factory Zone'),
				'#value' 	    => !empty($factory_zone_name[0]->zone_name) ? $factory_zone_name[0]->zone_name : '',
				'#type' => 'textfield',
				'#required' => TRUE,
				'#attributes'		=> array('readonly' => 'readonly'),
			);
		
			$form['notice_poisioning']['nearest_landmark'] = array(
				'#prefix' => '<div id="nearest_landmark_id"><div class="col-md-4"><label class="input label-block">',
				'#suffix' => '</label></div></div>',
				'#title' => t('(xii) Nearest Landmark'),
				'#type' => 'textfield',
				'#value' 	    => !empty($nearest_landmark) ? $nearest_landmark : '',
				'#attributes' => array('class' => array('charField'),'readonly' => 'readonly')
			);
		
			$form['notice_poisioning']['addrline'] = array(
				'#prefix' => '<div id="addrline_id"><div class="col-md-12"><label class="textarea label-block">',
				'#suffix' => '</label></div></div>',
				'#title' => '(xiii) Address',
				'#rows' => 3,
				'#type' => 'textarea',
				'#required' => TRUE,
				'#value' 	    => !empty($factory_addrline) ? $factory_addrline : '',
				'#attributes' => array('placeholder' => 'Address Line','readonly' => 'readonly'),
			);
		
			$form['notice_poisioning']['industry_nature'] = array(
				'#prefix' 			=> '<div id="industry_nature_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xiv) Nature of Industry'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#value' 	        => !empty($IndustryNature) ? $IndustryNature : '',
				'#attributes'       => array('readonly' => 'readonly'),
			);
			$form['notice_poisioning']['registration_number'] = array(
				'#prefix' 			=> '<div id="registration_number_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',//
				'#suffix' 			=> '</label></div></div>',//
				'#title' 			=> t('(xv) Registration No.:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#value' 			=> !empty($RegistrationNo) ? $RegistrationNo : '',
			);
			$form['notice_poisioning']['registration_date'] = array(
				'#prefix' 			=> '<div id="registration_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xv) Registration Date:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('readonly' => 'readonly'),
				'#value' 			=> !empty($RegistrationDate) ? $RegistrationDate : '',
			);
			$form['notice_poisioning']['licence_number'] = array(
				'#prefix' 			=> '<div id="licence_number_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',//
				'#suffix' 			=> '</label></div></div>',//
				'#title' 			=> t('(xvii) Licence No.:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#value' 			=> !empty($LicenceNo) ? $LicenceNo : '',
			);
			$form['notice_poisioning']['licence_date'] = array(
				'#prefix' 			=> '<div id="licence_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xvi) Licence Date:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('readonly' => 'readonly'),
				'#value' 			=> !empty($LicenceDate) ? $LicenceDate : '',
			);
			
		} 
		
		else
		 {
			$form['notice_poisioning']['factory_typeid'] = array(
				'#prefix' 			=> '<div id="factory_typeid_id">',
				'#suffix' 			=> '</div>',
				'#type' 			=> 'hidden',
				'#value' 			=> !empty($FactoryTypeid) ? $FactoryTypeid : $get_all_data[0]->factory_typeid,
				//'#value' 			=> '',
			);
			$form['notice_poisioning']['reference_number'] = array(
				'#prefix' 			=> '<div id="reference_number_id">',
				'#suffix' 			=> '</div>',
				'#type' 			=> 'hidden',
				'#value' 			=> !empty($ReferenceNumber) ? $ReferenceNumber : $get_all_data[0]->reference_number,
			);
			
			$form['notice_poisioning']['factory_name'] = array(
				'#prefix' 			=> '<div id="factory_name_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(i)a. Enter Registered Factory Name'),
				'#type' 			=> 'textfield',
				'#value' 			=> !empty($FactoryName) ? $FactoryName : $get_all_data[0]->factory_name,
			);
	
		//factory address section
			
		$form['notice_poisioning']['pincode']       = array(
			'#prefix' 				=> '<div id="pincode_id"><div class="col-md-4 col-xs-12"><label class="select label-block">',
			'#suffix' 				=> '</label></div></div>',
			'#attributes' 			=> array('class' => array(),'placeholder' => 'Pincode'),
			'#autocomplete_path' 	=> 'pinautocomplete',
			'#id' 				 	=> 'pincode_autocomplete',
			'#maxlength' 		 	=> 6,
			'#title' 			 	=> t('(ii) Pincode'),
			'#default_value' 	 	=> !empty($factory_pincode) ? $factory_pincode : $get_all_data[0]->pincode,
			'#required' 			=> TRUE,
			'#type' 				=> 'textfield',
			'#ajax' 				=> array(
												'effect' 	=> 'fade',
												'callback' 	=> 'get_ajax_load',
												'progress' 	=> array(
												 'type' 	=> 'throbber',
												'message' 	=> t('loading')
				)
			)
		);
		$value_pincode     = isset($form_state['values']['pincode']) ? $form_state['values']['pincode'] : $get_all_data[0]->pincode;
		if (!empty($value_pincode)) {
			$query = db_select('fa_all_india_pin_code', 'p')->fields('p', array(
						'districtname','statename',  'pincode','district_code', 'state_code', 'po_name'  ))
					->condition('p.pincode', trim($value_pincode), '=');
			
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
			$form['notice_poisioning']['state'] = array(
				'#title' 		=> '(iii) State',
				'#type' 		=> 'select',
				'#id' 			=> 'state_name',
				'#attributes' 	=> array('placeholder' => 'State','readonly' => 'readonly'),
				'#options' 		=> get_all_state($state_v),
				'#value' 		=> !empty($state_v) ? $state_v : $get_all_data[0]->state,
				'#required' 	=> TRUE,
				'#prefix' 		=> '<div id="ld_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
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
			$form['notice_poisioning']['state'] = array(
				'#title' => '(iii) State',
				'#type' => 'select',
				'#id' => 'state_name',
				'#attributes' => array('placeholder' => 'State','readonly' => 'readonly'),
				'#value' 		=> '',
				'#required' => TRUE,
				'#options' => array('' => t('Select State')),
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
		
		$value_state = isset($form_state['values']['state']) ? $form_state['values']['state'] : $get_all_data[0]->state;
		 if (!empty($state_v)) {
			$form['notice_poisioning']['district'] = array(
				'#title' => '(iv) District',
				'#type' => 'select',
				'#id' => 'district_name',
				'#attributes' => array('placeholder' => 'District','readonly' => 'readonly'),
				'#options' => get_district_by_id($state_v),
				'#value' => !empty($district_v) ? $district_v : $get_all_data[0]->district,
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
			$form['notice_poisioning']['district'] = array(
				'#title' => '(iv) District',
				'#type' => 'select',
				'#id' => 'district_name',
				'#attributes' => array('placeholder' => 'District','readonly' => 'readonly'),
				'#required' => TRUE,
				'#options' => array(
					'' => t('Select District')
				),
				'#prefix' => '<div id="ld_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
		}
		
		$value_district = isset($form_state['values']['district']) ? $form_state['values']['district'] : $get_all_data[0]->district;
		
		 if (!empty($district_v) && !empty($state_v)) {
			
			$form['notice_poisioning']['subdivision'] = array(
				'#title' => '(v) Sub-Division',
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Sub Division',
				),
				'#options' => common_custom_user_subdivisionlist_list_new($district_v),
				'#required' => TRUE,
				'#default_value' => $get_all_data[0]->subdivision,
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
			
			$form['notice_poisioning']['subdivision'] = array(
				'#title' => '(v) Sub-Division',
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
		
		 $value_subdivision = isset($form_state['values']['subdivision']) ? $form_state['values']['subdivision'] : $get_all_data[0]->subdivision;
		 
		if (!empty($value_district) && !empty($value_state) && !empty($value_subdivision)) {
			$form['notice_poisioning']['areatype'] = array(
				'#title' => '(vi) Area Type',
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Area Type',
				),
				'#options' => common_custom_user_areatype_list_new($value_district, $value_subdivision),
				'#required' => TRUE,
				'#default_value' => $get_all_data[0]->areatype,
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
			$form['notice_poisioning']['areatype'] = array(
				'#title' => '(vi) Area Type',
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
		
		$value_areatype = isset($form_state['values']['areatype']) ? $form_state['values']['areatype'] : $get_all_data[0]->areatype;
		
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
			
			$form['notice_poisioning']['block'] = array(
				'#title' => '(vii) '. $areatype_name,
				'#type' => 'select',
	
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'subdivision',
				),
				'#options' 		=> common_custom_user_block_list_new($value_subdivision, $value_areatype),
				'#required' 	=> TRUE,
				'#default_value' => $get_all_data[0]->block,
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
			$form['notice_poisioning']['block'] = array(
				'#title' => '(vii) Block / Municipality / Corporation / Notified Area / SEZ',
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
				'#prefix' => '<div id="ld_empareatype_name_replace"><div class="col-md-4"><label class="select label-block" title="Block / Municipality / Corporation / Notified Area / SEZ">',
				'#suffix' => '</label></div></div>'
			);
		}
	
	   $value_block      = isset($form_state['values']['block']) ? $form_state['values']['block'] : $get_all_data[0]->block;
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
			
			$form['notice_poisioning']['panchayat'] = array(
				'#title' => '(viii) '.$area_name,
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'panchayat',
					
				),
				'#options' => common_custom_user_villward_list_new($value_block, $area_code),
				'#default_value' => $get_all_data[0]->panchayat,
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
			$form['notice_poisioning']['panchayat'] = array(
				'#title' => '(viii) Gram Panchayat / Ward / Sector',
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
		
		$value_panchayat = isset($form_state['values']['panchayat']) ? $form_state['values']['panchayat'] : $get_all_data[0]->panchayat;
		
		if (!empty($value_district) && !empty($value_subdivision) && !empty($value_areatype) && !empty($value_block) && !empty($value_state) && !empty($value_panchayat)) {
			$form['notice_poisioning']['policestation'] = array(
				'#title' => '(ix) Police Station',
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Police Station',
				),
				'#options' => common_custom_user_ps_list_new($value_district),
				'#required' => TRUE,
				'#default_value' => $get_all_data[0]->policestation,
				'#prefix' => '<div id="ld_empps_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
		} else {
			$form['notice_poisioning']['policestation'] = array(
				'#title' => '(ix) Police Station',
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
			$form['notice_poisioning']['postoffice'] = array(
				'#title' => '(x) Post Office',
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Post Office',
				),
				'#options' => common_custom_post_office_list_new($pincode_v),
				'#default_value' => $get_all_data[0]->postoffice,
				'#required' => TRUE,
				'#prefix' => '<div id="ld_post_office_div"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
		} else {
			$form['notice_poisioning']['postoffice'] = array(
				'#title' => '(x) Post Office',
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
		
		if (!empty($value_block) && !empty($value_panchayat)) {
			
			$factory_zone_name = get_zone_name($value_block,$value_panchayat);
			
			$form['notice_poisioning']['factory_zone'] = array(
				'#value'   => $factory_zone_name[0]->zone_id,
				'#type' => 'hidden',
			);
			
			$form['notice_poisioning']['factory_zone_name'] = array(
				'#prefix' => '<div id="factory_zone_div"><div class="col-md-4"><label class="input label-block">',
				'#suffix' => '</label></div></div>',
				'#title'  => t('(xi) Factory Zone'),
				'#value'   => $factory_zone_name[0]->zone_name,
				'#type' => 'textfield',
				'#required' => TRUE,
				'#attributes'		=> array('readonly' => 'readonly'),
				'#ajax' => array(
					'event' => 'change',
					'effect' => 'fade',
					'callback' => 'get_ajax_load',
					'progress' => array('type' => 'throbber','message' => t('loading')))
			);
	   } else {
			$form['notice_poisioning']['factory_zone_name'] = array(
				'#prefix' => '<div id="factory_zone_div"><div class="col-md-4"><label class="input label-block">',
				'#suffix' => '</label></div></div>',
				'#title'  => t('(xi) Factory Zone'),
				'#type'   => 'textfield',
				'#required' => TRUE,
				'#attributes' 		=> array('readonly' => 'readonly'),
			);
		}
		
			$form['notice_poisioning']['nearest_landmark'] = array(
				'#prefix' => '<div id="nearest_landmark_id"><div class="col-md-4"><label class="input label-block">',
				'#suffix' => '</label></div></div>',
				'#title' => t('(xii) Nearest Landmark'),
				'#type' => 'textfield',
				'#value' => $get_all_data[0]->nearest_landmark,
				'#attributes' => array('class' => array('charField'))
			);		
		
			$form['notice_poisioning']['addrline'] = array(
				'#title' => '(xiii) Address',
				'#rows' => 3,
				'#type' => 'textarea',
				'#required' => TRUE,
				'#value' => $get_all_data[0]->addrline,
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Address Line',
				),
				'#prefix' => '<div id="addrline_id"><div class="col-md-12"><label class="textarea label-block">',
				'#suffix' => '</label></div></div>'
			);
		
		
	   //factory address end
			
			$form['notice_poisioning']['industry_nature'] = array(
				'#prefix' 			=> '<div id="industry_nature_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xiv) Nature of Industry'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#value' 	        => !empty($IndustryNature) ? $IndustryNature : $get_all_data[0]->industry_nature,
			);
			$form['notice_poisioning']['registration_number'] = array(
				'#prefix' 			=> '<div id="registration_number_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',//
				'#suffix' 			=> '</div></label></div>',//
				'#title' 			=> t('(xv) Registration No.:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#value' 			=> !empty($RegistrationNo) ? $RegistrationNo : $get_all_data[0]->registration_number,
			);
			$form['notice_poisioning']['registration_date'] = array(
				'#prefix' 			=> '<div id="registration_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xv) Registration Date:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#value' 			=> !empty($RegistrationDate) ? $RegistrationDate : trim(implode('-', array_reverse(explode('-',$get_all_data[0]->registration_date)))),
				'#attributes' 		=> array('class'=>array('datepicker_retify'),'title'=>'Enter Registration Date.'),//
	
			);
			$form['notice_poisioning']['licence_number'] = array(
				'#prefix' 			=> '<div id="licence_number_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',//
				'#suffix' 			=> '</label></div></div>',//
				'#title' 			=> t('(xvii) Licence No.:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#value' 			=> !empty($LicenceNo) ? $LicenceNo : $get_all_data[0]->licence_number,
			);
			$form['notice_poisioning']['licence_date'] = array(
				'#prefix' 			=> '<div id="licence_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xvi) Licence Date:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#value' 			=> !empty($LicenceDate) ? $LicenceDate : trim(implode('-', array_reverse(explode('-',$get_all_data[0]->licence_date)))),
				'#attributes' 		=> array('class'=>array('datepicker_retify'),'title'=>'Enter Licence Date.'),
			);
		 }
	 }
	 else {
			$form['notice_poisioning']['factory_id'] = array(
				'#prefix' 			=> '<div id="factory_id_id">',
				'#suffix' 			=> '</div>',
				'#type' 			=> 'hidden',
				'#value' 			=> !empty($get_all_data[0]->factory_id) ? $get_all_data[0]->factory_id : 0,
			);
			$form['notice_poisioning']['factory_typeid'] = array(
				'#prefix' 			=> '<div id="factory_typeid_id">',
				'#suffix' 			=> '</div>',
				'#type' 			=> 'hidden',
				'#value' 			=> !empty($FactoryTypeid) ? $FactoryTypeid : $get_all_data[0]->factory_typeid,
				//'#value' 			=> '',
			);
			$form['notice_poisioning']['reference_number'] = array(
				'#prefix' 			=> '<div id="reference_number_id">',
				'#suffix' 			=> '</div>',
				'#type' 			=> 'hidden',
				'#value' 			=> !empty($ReferenceNumber) ? $ReferenceNumber : $get_all_data[0]->reference_number,
			);
			
			$form['notice_poisioning']['factory_name'] = array(
				'#prefix' 			=> '<div id="factory_name_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(i)a. Enter Registered Factory Name'),
				'#type' 			=> 'textfield',
				'#value' 			=> !empty($FactoryName) ? $FactoryName : $get_all_data[0]->factory_name,
			);
	
		//factory address section
			
		$form['notice_poisioning']['pincode']       = array(
			'#prefix' 				=> '<div id="pincode_id"><div class="col-md-4 col-xs-12"><label class="select label-block">',
			'#suffix' 				=> '</label></div></div>',
			'#attributes' 			=> array('class' => array(),'placeholder' => 'Pincode'),
			'#autocomplete_path' 	=> 'pinautocomplete',
			'#id' 				 	=> 'pincode_autocomplete',
			'#maxlength' 		 	=> 6,
			'#title' 			 	=> t('(ii) Pincode'),
			'#default_value' 	 	=> !empty($factory_pincode) ? $factory_pincode : $get_all_data[0]->pincode,
			'#required' 			=> TRUE,
			'#type' 				=> 'textfield',
			'#ajax' 				=> array(
												'effect' 	=> 'fade',
												'callback' 	=> 'get_ajax_load',
												'progress' 	=> array(
												 'type' 	=> 'throbber',
												'message' 	=> t('loading')
				)
			)
		);
		$value_pincode     = isset($form_state['values']['pincode']) ? $form_state['values']['pincode'] : $get_all_data[0]->pincode;
		if (!empty($value_pincode)) {
			$query = db_select('fa_all_india_pin_code', 'p')->fields('p', array(
						'districtname','statename',  'pincode','district_code', 'state_code', 'po_name'  ))
					->condition('p.pincode', trim($value_pincode), '=');
			
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
			$form['notice_poisioning']['state'] = array(
				'#title' 		=> '(iii) State',
				'#type' 		=> 'select',
				'#id' 			=> 'state_name',
				'#attributes' 	=> array('placeholder' => 'State','readonly' => 'readonly'),
				'#options' 		=> get_all_state($state_v),
				'#value' 		=> !empty($state_v) ? $state_v : $get_all_data[0]->state,
				'#required' 	=> TRUE,
				'#prefix' 		=> '<div id="ld_edit_emp_state_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' 		=> '</label></div></div>',
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
			$form['notice_poisioning']['state'] = array(
				'#title' => '(iii) State',
				'#type' => 'select',
				'#id' => 'state_name',
				'#attributes' => array('placeholder' => 'State','readonly' => 'readonly'),
				'#value' 		=> '',
				'#required' => TRUE,
				'#options' => array('' => t('Select State')),
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
		
		$value_state = isset($form_state['values']['state']) ? $form_state['values']['state'] : $get_all_data[0]->state;
		 if (!empty($state_v)) {
			$form['notice_poisioning']['district'] = array(
				'#title' => '(iv) District',
				'#type' => 'select',
				'#id' => 'district_name',
				'#attributes' => array('placeholder' => 'District','readonly' => 'readonly'),
				'#options' => get_district_by_id($state_v),
				'#value' => !empty($district_v) ? $district_v : $get_all_data[0]->district,
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
			$form['notice_poisioning']['district'] = array(
				'#title' => '(iv) District',
				'#type' => 'select',
				'#id' => 'district_name',
				'#attributes' => array('placeholder' => 'District','readonly' => 'readonly'),
				'#required' => TRUE,
				'#options' => array(
					'' => t('Select District')
				),
				'#prefix' => '<div id="ld_edit_emp_district_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
		}
		
		$value_district = isset($form_state['values']['district']) ? $form_state['values']['district'] : $get_all_data[0]->district;
		
		 if (!empty($district_v) && !empty($state_v)) {
			
			$form['notice_poisioning']['subdivision'] = array(
				'#title' => '(v) Sub-Division',
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Sub Division',
				),
				'#options' => common_custom_user_subdivisionlist_list_new($district_v),
				'#required' => TRUE,
				'#default_value' => $get_all_data[0]->subdivision,
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
			
			$form['notice_poisioning']['subdivision'] = array(
				'#title' => '(v) Sub-Division',
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
		
		 $value_subdivision = isset($form_state['values']['subdivision']) ? $form_state['values']['subdivision'] : $get_all_data[0]->subdivision;
		 
		if (!empty($value_district) && !empty($value_state) && !empty($value_subdivision)) {
			$form['notice_poisioning']['areatype'] = array(
				'#title' => '(vi) Area Type',
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Area Type',
				),
				'#options' => common_custom_user_areatype_list_new($value_district, $value_subdivision),
				'#required' => TRUE,
				'#default_value' => $get_all_data[0]->areatype,
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
			$form['notice_poisioning']['areatype'] = array(
				'#title' => '(vi) Area Type',
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
		
		$value_areatype = isset($form_state['values']['areatype']) ? $form_state['values']['areatype'] : $get_all_data[0]->areatype;
		
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
			
			$form['notice_poisioning']['block'] = array(
				'#title' => '(vii) '. $areatype_name,
				'#type' => 'select',
	
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'subdivision',
				),
				'#options' 		=> common_custom_user_block_list_new($value_subdivision, $value_areatype),
				'#required' 	=> TRUE,
				'#default_value' => $get_all_data[0]->block,
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
			$form['notice_poisioning']['block'] = array(
				'#title' => '(vii) Block / Municipality / Corporation / Notified Area / SEZ',
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
				'#prefix' => '<div id="ld_empareatype_name_replace"><div class="col-md-4"><label class="select label-block" title="Block / Municipality / Corporation / Notified Area / SEZ">',
				'#suffix' => '</label></div></div>'
			);
		}
	
	   $value_block      = isset($form_state['values']['block']) ? $form_state['values']['block'] : $get_all_data[0]->block;
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
			
			$form['notice_poisioning']['panchayat'] = array(
				'#title' => '(viii) '.$area_name,
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'panchayat',
					
				),
				'#options' => common_custom_user_villward_list_new($value_block, $area_code),
				'#default_value' => $get_all_data[0]->panchayat,
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
			$form['notice_poisioning']['panchayat'] = array(
				'#title' => '(viii) Gram Panchayat / Ward / Sector',
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
		
		$value_panchayat = isset($form_state['values']['panchayat']) ? $form_state['values']['panchayat'] : $get_all_data[0]->panchayat;
		
		if (!empty($value_district) && !empty($value_subdivision) && !empty($value_areatype) && !empty($value_block) && !empty($value_state) && !empty($value_panchayat)) {
			$form['notice_poisioning']['policestation'] = array(
				'#title' => '(ix) Police Station',
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Police Station',
				),
				'#options' => common_custom_user_ps_list_new($value_district),
				'#required' => TRUE,
				'#default_value' => $get_all_data[0]->policestation,
				'#prefix' => '<div id="ld_empps_replace"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
		} else {
			$form['notice_poisioning']['policestation'] = array(
				'#title' => '(ix) Police Station',
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
			$form['notice_poisioning']['postoffice'] = array(
				'#title' => '(x) Post Office',
				'#type' => 'select',
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Post Office',
				),
				'#options' => common_custom_post_office_list_new($pincode_v),
				'#default_value' => $get_all_data[0]->postoffice,
				'#required' => TRUE,
				'#prefix' => '<div id="ld_post_office_div"><div class="col-md-4"><label class="select label-block">',
				'#suffix' => '</label></div></div>'
			);
		} else {
			$form['notice_poisioning']['postoffice'] = array(
				'#title' => '(x) Post Office',
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
		
		if (!empty($value_block) && !empty($value_panchayat)) {
			
			$factory_zone_name = get_zone_name($value_block,$value_panchayat);
			
			$form['notice_poisioning']['factory_zone'] = array(
				'#value'   => $factory_zone_name[0]->zone_id,
				'#type' => 'hidden',
			);
			
			$form['notice_poisioning']['factory_zone_name'] = array(
				'#prefix' => '<div id="factory_zone_div"><div class="col-md-4"><label class="input label-block">',
				'#suffix' => '</label></div></div>',
				'#title'  => t('(xi) Factory Zone'),
				'#value'   => $factory_zone_name[0]->zone_name,
				'#type' => 'textfield',
				'#required' => TRUE,
				'#attributes'		=> array('readonly' => 'readonly'),
				'#ajax' => array(
					'event' => 'change',
					'effect' => 'fade',
					'callback' => 'get_ajax_load',
					'progress' => array('type' => 'throbber','message' => t('loading')))
			);
	   } else {
			$form['notice_poisioning']['factory_zone_name'] = array(
				'#prefix' => '<div id="factory_zone_div"><div class="col-md-4"><label class="input label-block">',
				'#suffix' => '</label></div></div>',
				'#title'  => t('(xi) Factory Zone'),
				'#type'   => 'textfield',
				'#required' => TRUE,
				'#attributes' 		=> array('readonly' => 'readonly'),
			);
		}
		
			$form['notice_poisioning']['nearest_landmark'] = array(
				'#prefix' => '<div id="nearest_landmark_id"><div class="col-md-4"><label class="input label-block">',
				'#suffix' => '</label></div></div>',
				'#title' => t('(xii) Nearest Landmark'),
				'#type' => 'textfield',
				'#value' => $get_all_data[0]->nearest_landmark,
				'#attributes' => array('class' => array('charField'))
			);		
		
			$form['notice_poisioning']['addrline'] = array(
				'#title' => '(xiii) Address',
				'#rows' => 3,
				'#type' => 'textarea',
				'#required' => TRUE,
				'#value' => $get_all_data[0]->addrline,
				'#attributes' => array(
					'class' => array(
						''
					),
					'placeholder' => 'Address Line',
				),
				'#prefix' => '<div id="addrline_id"><div class="col-md-12"><label class="textarea label-block">',
				'#suffix' => '</label></div></div>'
			);
		
		
	   //factory address end
			
			$form['notice_poisioning']['industry_nature'] = array(
				'#prefix' 			=> '<div id="industry_nature_id"><div class="col-md-4 col-xs-12"><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xiv) Nature of Industry'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#value' 	        => !empty($IndustryNature) ? $IndustryNature : $get_all_data[0]->industry_nature,
			);
			$form['notice_poisioning']['registration_number'] = array(
				'#prefix' 			=> '<div id="registration_number_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',//
				'#suffix' 			=> '</div></label></div>',//
				'#title' 			=> t('(xv) Registration No.:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#value' 			=> !empty($RegistrationNo) ? $RegistrationNo : $get_all_data[0]->registration_number,
			);
			$form['notice_poisioning']['registration_date'] = array(
				'#prefix' 			=> '<div id="registration_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xv) Registration Date:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#value' 			=> !empty($RegistrationDate) ? $RegistrationDate : trim(implode('-', array_reverse(explode('-',$get_all_data[0]->registration_date)))),
				'#attributes' 		=> array('class'=>array('datepicker_retify'),'title'=>'Enter Registration Date.'),
	
			);
			$form['notice_poisioning']['licence_number'] = array(
				'#prefix' 			=> '<div id="licence_number_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',//
				'#suffix' 			=> '</label></div></div>',//
				'#title' 			=> t('(xvii) Licence No.:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#value' 			=> !empty($LicenceNo) ? $LicenceNo : $get_all_data[0]->licence_number,
			);
			$form['notice_poisioning']['licence_date'] = array(
				'#prefix' 			=> '<div id="licence_date_id"><div class="col-md-4 col-xs-12" ><label class="input label-block">',
				'#suffix' 			=> '</label></div></div>',
				'#title' 			=> t('(xvi) Licence Date:'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#value' 			=> !empty($LicenceDate) ? $LicenceDate : trim(implode('-', array_reverse(explode('-',$get_all_data[0]->licence_date)))),
				'#attributes' 		=> array('class'=>array('datepicker_retify'),'title'=>'Enter Licence Date.'),
			);
		 }
 
 	$form['notice_poisioning_end']['submit'] = array (
		'#attributes' 	=> array('class' => array('btn btn-success pull-right')),
		'#type' 		=> 'submit',
		'#value'		=> 'Save'
	);	  
	return $form;
  }
	
  function get_reg_lic_no_form20($factory_id){ 
		$query_reg_lic 		= db_select('fa_cafa', 'cafa');
		$query_reg_lic      ->leftjoin('fa_nature_manufacturing', 'fnm', 'fnm.application_id=cafa.id');
		$query_reg_lic      ->fields('fnm', array('nature_manufacturing'));
		$query_reg_lic		->fields('cafa',array('factory_name','factory_typeid','reference_number','factory_registrstion_no','backlog_registration_no','backlog_registration_date','registration_date','tm_factory_registration_no','backlog_license_number','factory_license_no','backlog_license_date','license_date','classification_no','service_id','nearest_landmark','factory_zone','pincode','state','district','subdivision','areatype','block','panchayat','policestation','postoffice','addrline'));
		$query_reg_lic		->condition('cafa.id',$factory_id,'=');
		$result_reg_lic 	= $query_reg_lic->execute()->fetchAssoc();
		return $result_reg_lic;
	}

  /*function get_factory_name($uid){
		$default_select 	= array(""=>"--Select--");
		$result 	 = db_query("SELECT id,factory_name FROM {fa_cafa} WHERE ((factory_registrstion_no !='') OR (backlog_registration_no !='')) AND created_by ='".$uid."'");
		$list 	 = array();
		foreach ($result as $record) {
			$list[$record->id] = t('@factoryname', array(
			'@factoryname' => $record->factory_name,
			));
		}
		$last_select 	= array(0=>"Other");
		return ($default_select+$list+$last_select);
	}*/

  function get_ajax_name_factory($form, $form_state){
	  
		$commands[] = ajax_command_replace('#factory_id_id', drupal_render($form['notice_poisioning']['factory_id']));
		$commands[] = ajax_command_replace('#factory_typeid_id', drupal_render($form['notice_poisioning']['factory_typeid']));
		$commands[] = ajax_command_replace('#reference_number_id', drupal_render($form['notice_poisioning']['reference_number']));
		$commands[] = ajax_command_replace('#factory_name_id', drupal_render($form['notice_poisioning']['factory_name']));
		
		$commands[] = ajax_command_replace('#pincode_id', drupal_render($form['notice_poisioning']['pincode']));
		$commands[] = ajax_command_replace('#ld_edit_emp_state_replace', drupal_render($form['notice_poisioning']['state']));
		$commands[] = ajax_command_replace('#ld_edit_emp_district_replace', drupal_render($form['notice_poisioning']['district']));
		$commands[] = ajax_command_replace('#ld_empsubdv_replace', drupal_render($form['notice_poisioning']['subdivision']));
		$commands[] = ajax_command_replace('#ld_emp_areatype_replace', drupal_render($form['notice_poisioning']['areatype']));
		$commands[] = ajax_command_replace('#ld_empareatype_name_replace', drupal_render($form['notice_poisioning']['block']));
		$commands[] = ajax_command_replace('#ld_emp_vill_ward_replace', drupal_render($form['notice_poisioning']['panchayat']));
		$commands[] = ajax_command_replace('#ld_empps_replace', drupal_render($form['notice_poisioning']['policestation']));
		$commands[] = ajax_command_replace('#ld_post_office_div', drupal_render($form['notice_poisioning']['postoffice']));
		$commands[] = ajax_command_replace('#factory_zone_div', drupal_render($form['notice_poisioning']['factory_zone_name']));
		$commands[] = ajax_command_replace('#nearest_landmark_id', drupal_render($form['notice_poisioning']['nearest_landmark']));
		$commands[] = ajax_command_replace('#addrline_id', drupal_render($form['notice_poisioning']['addrline']));
		
		$commands[] = ajax_command_replace('#industry_nature_id', drupal_render($form['notice_poisioning']['industry_nature'])); 
		$commands[] = ajax_command_replace('#registration_number_id', drupal_render($form['notice_poisioning']['registration_number']));
		$commands[] = ajax_command_replace('#registration_date_id', drupal_render($form['notice_poisioning']['registration_date']));
		$commands[] = ajax_command_replace('#licence_number_id', drupal_render($form['notice_poisioning']['licence_number']));
		$commands[] = ajax_command_replace('#licence_date_id', drupal_render($form['notice_poisioning']['licence_date']));
		$commands[] = ajax_command_replace('#classification_no_id', drupal_render($form['notice_poisioning']['classification_no']));
	  
	  return array('#type' => 'ajax', '#commands' => $commands);
  }
  
	function get_ajax_load($form, $form_state)
	{
		$commands   = array();
		$commands[] = ajax_command_replace('#ld_edit_emp_state_replace', drupal_render($form['notice_poisioning']['state']));
		$commands[] = ajax_command_replace('#ld_edit_emp_district_replace', drupal_render($form['notice_poisioning']['district']));
		$commands[] = ajax_command_replace('#ld_empsubdv_replace', drupal_render($form['notice_poisioning']['subdivision']));
		$commands[] = ajax_command_replace('#ld_emp_areatype_replace', drupal_render($form['notice_poisioning']['areatype']));
		$commands[] = ajax_command_replace('#ld_empareatype_name_replace', drupal_render($form['notice_poisioning']['block']));
		$commands[] = ajax_command_replace('#ld_emp_vill_ward_replace', drupal_render($form['notice_poisioning']['panchayat']));
		$commands[] = ajax_command_replace('#ld_empps_replace', drupal_render($form['notice_poisioning']['policestation']));
		$commands[] = ajax_command_replace('#ld_post_office_div', drupal_render($form['notice_poisioning']['postoffice']));
		$commands[] = ajax_command_replace('#factory_zone_div', drupal_render($form['notice_poisioning']['factory_zone_name']));
		return array(
			'#type' => 'ajax',
			'#commands' => $commands
		);
	} 
  
 function form20_form_submit($form, &$form_state){
		
		global $base_root,$base_path,$user;
		$val    = $form_state['values'];
		$uid 	= $user->uid;

	$ServiceId = encryption_decryption_fun('decrypt', $val['serviceid_hidden']);
	$service_id = ($ServiceId==0)? 14 :$ServiceId;

		if($val['factory_id']!='0')
		{			
			$factoryid = $val['factory_id'];
			$factorytypeid = $val['factory_typeid'];
		} else {
			$factoryid = 0;
			$factorytypeid = 0;
		}
		if($val['reference_number']!='')
		{			
			$referencenumber = $val['reference_number'];
		} else {
			$referencenumber = 0;
		}

		$formid 	  = encryption_decryption_fun('decrypt', $val['formid_hidden']);
	
		if($formid != 0)
		{
			$notice_poisoning = array(
				'factory_id'           => $factoryid,
				'factory_typeid'       => $factorytypeid,
				'reference_number'     => $referencenumber,
				'factory_name'         => ($val['factory_id']!= 0) ? $val['factory_name'] : $form_state['input']['factory_name'],
				'pincode'              => $val['pincode'],
				'state'                => $val['state'],
				'district'             => $val['district'],
				'subdivision'          => $val['subdivision'],
				'areatype'             => $val['areatype'],
				'block'                => $val['block'],
				'panchayat'            => $val['panchayat'],
				'policestation'        => $val['policestation'],
				'postoffice'           => $val['postoffice'],
				'factory_zone'         => $val['factory_zone'],
				'nearest_landmark'     => ($val['factory_id']!= 0) ? $val['nearest_landmark'] : $form_state['input']['nearest_landmark'],
				'addrline' 			   => ($val['factory_id']!= 0) ? $val['addrline'] : $form_state['input']['addrline'],
				'industry_nature'      => ($val['factory_id']!= 0) ? $val['industry_nature'] : $form_state['input']['industry_nature'],
				'registration_number'  => ($val['factory_id']!= 0) ? $val['registration_number'] : $form_state['input']['registration_number'],
				'registration_date'    => ($val['factory_id']!= 0) ? trim(implode('-', array_reverse(explode('-',$val['registration_date'])))) : trim(implode('-', array_reverse(explode('-',$form_state['input']['registration_date'])))),
				'licence_number'       => ($val['factory_id']!= 0) ? $val['licence_number'] : $form_state['input']['licence_number'],
				'licence_date'         => ($val['factory_id']!= 0) ? trim(implode('-', array_reverse(explode('-',$val['licence_date'])))) :trim(implode('-', array_reverse(explode('-',$form_state['input']['licence_date'])))),
				'is_registered'        => $val['is_registered'],
			);
			
			$queryapp 		 =	db_update('fa_form20_notice_poisoning');
			$queryapp		 ->	fields($notice_poisoning);
			$queryapp		 ->	condition('id',$formid,'=');
			$queryapp		 ->	execute();
		
		$notice_poisoning_ID = $formid;

		} else {
		
			$notice_poisoning = array(
				'factory_id'           => $factoryid,
				'factory_typeid'       => $factorytypeid,
				'reference_number'     => $referencenumber,
				'factory_name'         => ($val['factory_id']!= 0) ? $val['factory_name'] : $form_state['input']['factory_name'],
				'pincode'              => $val['pincode'],
				'state'                => $val['state'],
				'district'             => $val['district'],
				'subdivision'          => $val['subdivision'],
				'areatype'             => $val['areatype'],
				'block'                => $val['block'],
				'panchayat'            => $val['panchayat'],
				'policestation'        => $val['policestation'],
				'postoffice'           => $val['postoffice'],
				'factory_zone'         => $val['factory_zone'],
				'nearest_landmark'     => ($val['factory_id']!= 0) ? $val['nearest_landmark'] : $form_state['input']['nearest_landmark'],
				'addrline' 			   => ($val['factory_id']!= 0) ? $val['addrline'] : $form_state['input']['addrline'],
				'industry_nature'      => ($val['factory_id']!= 0) ? $val['industry_nature'] : $form_state['input']['industry_nature'],
				'registration_number'  => ($val['factory_id']!= 0) ? $val['registration_number'] : $form_state['input']['registration_number'],
				'registration_date'    => ($val['factory_id']!= 0) ? trim(implode('-', array_reverse(explode('-',$val['registration_date'])))) : trim(implode('-', array_reverse(explode('-',$form_state['input']['registration_date'])))),
				'licence_number'       => ($val['factory_id']!= 0) ? $val['licence_number'] : $form_state['input']['licence_number'],
				'licence_date'         => ($val['factory_id']!= 0) ? trim(implode('-', array_reverse(explode('-',$val['licence_date'])))) :trim(implode('-', array_reverse(explode('-',$form_state['input']['licence_date'])))),
				'is_registered'        => $val['is_registered'],
				'created_by'		   => $uid,
				'created_date' 		   => date('Y-m-d H:i:s'),
			    'service_id' 		   => $service_id,
			);
	
			$notice_poisoning_ID = db_insert('fa_form20_notice_poisoning')->fields($notice_poisoning)->execute();
		}	

			drupal_goto('applicant/form20/occupier-details/'.encryption_decryption_fun('encrypt',$notice_poisoning_ID).'/'.encryption_decryption_fun('encrypt',$referencenumber).'/'.encryption_decryption_fun('encrypt',$factorytypeid).'/'.encryption_decryption_fun('encrypt',$service_id));
		
		$form_state['rebuild'] = true;
	} 				
