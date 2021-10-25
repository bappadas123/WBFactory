<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
function caf_form_registration_owner($form, &$form_state, $serviceid, $factory_typeid, $applicationid,$referencenumber)
{ 
    global $base_root, $base_path, $user;
    $form            			= array();

    $service_id      			= encryption_decryption_fun('decrypt', $serviceid);
    $factory_type_id 			= encryption_decryption_fun('decrypt', $factory_typeid);
    $application_id  			= encryption_decryption_fun('decrypt', $applicationid);
	$reference_no  				= encryption_decryption_fun('decrypt', $referencenumber);
    
	
	
	$get_user_data     			    	= 	get_details_applicant($user->uid);//echo "<pre>"; print_r($get_user_data);
	$get_fa_cafa 		            	= 	get_fa_cafa($application_id);
    $application_status             	= 	$get_fa_cafa['application_status'];
    $factory_identification_number		= 	$get_fa_cafa['factory_reg_identification_number'];
	$is_basic_information_tab    		=   $get_fa_cafa['is_year_calculation_tab'];
    
	
	
	
	 if(empty($is_basic_information_tab)){
		  	drupal_set_message(('Please fill up the second tab than fill up the basic information'),'warning');			
			drupal_goto('applicant/caf-reg/details-worker-registration/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$referencenumber) ;
	 } 
   

     $owner_name = $pincodepremises = $state_premises = $district_premises = $subdivision_premises = $areatype_premises = $block_premises = $panchayat_premises = $policestation_premises = $postoffice_premises = $addrline_premises = $mouza_name = $jl_no  = $owner_mname = $owner_lname = ''; 

    $form            			= array();
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
    $form['reference_no_hidden']       = array(
        '#type'          => 'hidden',
        '#default_value' => $referencenumber
	);
	

	$get_fa_owner            = get_all_owner_data($application_id,$service_id,$factory_type_id,$reference_no);
	
    if (!empty($get_fa_owner)) {
		
		// Details of owner of the premises occupied as a factory//
		$owner_name                   	    	= $get_fa_cafa['owner_name'];
        $owner_mname					    	= $get_fa_cafa['owner_mname'];
		$owner_lname					    	= $get_fa_cafa['owner_lname'];
        $country_premises   					= $get_fa_cafa['country_premises'];
		$pincodepremises       	   				= $get_fa_cafa['pincodepremises'];
        $state_premises         	    		= $get_fa_cafa['state_premises'];
        $district_premises      	    		= $get_fa_cafa['district_premises'];
        $subdivision_premises   	    		= $get_fa_cafa['subdivision_premises'];
        $areatype_premises      	    		= $get_fa_cafa['areatype_premises'];
        $block_premises         	    		= $get_fa_cafa['block_premises'];
        $panchayat_premises           			= $get_fa_cafa['panchayat_premises'];
        $policestation_premises 	    		= $get_fa_cafa['policestation_premises'];
        $postoffice_premises          			= $get_fa_cafa['postoffice_premises'];
        $aadhaar_premises       				= explode('-',$get_fa_cafa['aadhaar_premises']);
		$user_aadhar_1_premises					= $aadhaar_premises[0];
		$user_aadhar_2_premises					= $aadhaar_premises[1];
		$user_aadhar_3_premises					= $aadhaar_premises[2];
		$addrline_premises            			= $get_fa_cafa['addrline_premises'];
		$passport_premises						= $get_fa_cafa['passport_premises'];
		$passport_date_of_issue_premises 		= $get_fa_cafa['passport_date_of_issue_premises'];
		$passport_date_of_expiry_premises		= $get_fa_cafa['passport_date_of_expiry_premises'];
		$street_name_premises					= $get_fa_cafa['street_name_premises'];
		$house_no_premises		    			= $get_fa_cafa['house_no_premises'];
		$police_station_premises				= $get_fa_cafa['police_station_premises'];        
//		$mouza_name   							= $get_fa_cafa['mouza_name']; 
//		$jl_no 									= $get_fa_cafa['jl_no'];
		
    } else {
		
		$ownership_type_pre         	    = $get_user_data['ownership_type'];
		
		// DATA FROM USER DETAILS TABLE 
		if($get_user_data['user_type'] == 'owner') { 
			
			$ownership_type_pre         	        = $get_user_data['ownership_type'];

			$occupier_user_aadhar       		= explode('-',$get_user_data['user_aadhar']);
			$user_aadhar_1_premises 			= $occupier_user_aadhar[0];
			$user_aadhar_2_premises 			= $occupier_user_aadhar[1];
			$user_aadhar_3_premises 			= $occupier_user_aadhar[2];

			$country_premises	  		    	= $get_user_data['country'];
			$pincodepremises	    			= $get_user_data['pincode'];
			$state_premises	        			= $get_user_data['state'];
			$district_premises	    			= $get_user_data['district'];
			$subdivision_premises   			= $get_user_data['subdivision'];
			$areatype_premises      			= $get_user_data['areatype'];
			$block_premises		    			= $get_user_data['block'];
			$panchayat_premises    				= $get_user_data['panchayat'];
			$policestation_premises				= $get_user_data['policestation'];
			$postoffice_premises    			= $get_user_data['postoffice'];

			$passport_premises 				  	= $get_user_data['user_passport'];
			$passport_date_of_issue_premises  	= $get_user_data['passport_date_of_issue'];
			$passport_date_of_expiry_premises 	= $get_user_data['passport_date_of_expiry'];
			$street_name_premises         	  	= $get_user_data['street_name'];
			$house_no_premises            	  	= $get_user_data['house_no'];
			$police_station_premises     	  	= $get_user_data['police_station'];
			$addrline_premises     	  			= $get_user_data['addrline'];

			$owner_name					    	= $get_user_data['firstname'];
			$owner_mname                   	 	= $get_user_data['middlename'];
			$owner_lname                    	= $get_user_data['lastname'];
		} 
	}
	
    $form['application_status_hidden'] = array(
        '#type' 			=> 'hidden',
        '#default_value' 	=> encryption_decryption_fun('encrypt', $application_status)
    );

    /********** Owner checking data **********/
	if (!empty($application_id) && $get_fa_cafa['application_status']=='B') {
		$checked = get_checking($application_id,$service_id,$factory_type_id,$reference_no);
	
		$verify_details      = ($checked['verify_details'])? $checked['verify_details'] : ''; 
	
		$remark_field = explode(',', $checked['verify_details']);
			foreach ($remark_field as $fieldname){
		//echo  "<pre>"; print_r($fieldname);
				if($fieldname == 'owner_name'){ $owner_name_ck = "disabled";}
			}

		if(in_array("owner_name", $remark_field)) { $owner_name_check_data = '<i class="fa fa-check text-green verified"></i>';   $owner_field_value= 'blank';}
		else {  $owner_name_check_data = '<i class="fa fa-edit text-red verified"></i>'; $owner_field_value= "owner_name";}
	}	
	 
	/********** Factory Information - Start **********/
    
	$form['header']            = array(
        '#markup' => t('<div class="content"><h3>Owner Information</h3>')
    );
	
	/********** Details of owner of the premises occupied as a factory - Start **********/
    
	$form['factory_part_premises'] = array(
			'#type' 			=> 'fieldset',
			'#title' 			=> t('E. Details of owner/land lord/lessor of the premises occupied as a factory'),
			'#collapsible' 		=> TRUE, // Added
			'#collapsed' 		=> FALSE,  // Added
		);		
	
		$form['factory_part_premises']['thirdRowStart'] = array(
			'#prefix' =>'<div class="row">' ,
			'#suffix' => '',
		);
	
		$form['factory_part_premises']['owner_name']    = array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-4">',
			'#suffix' 			=> '</div>',
			'#title' 			=> $owner_name_check_data.t('(i)(a). First name'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> $owner_name,
			'#required' 		=> TRUE,
			'#attributes' 		=> array( 'class' => array('form-control'),$owner_name_ck => $owner_name_ck)
			
		);
		$form['factory_part_premises']['owner_mname']    = array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-4">',
			'#suffix' 			=> '</div>',
			'#title' 			=> $owner_name_check_data.t('(i)(b). Middle name'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> $owner_mname,
			'#attributes' 		=> array( 'class' => array('form-control'),$owner_name_ck => $owner_name_ck)
			
		);
		$form['factory_part_premises']['owner_lname']    = array(
			'#prefix' 			=> '<div class="col-md-4 col-xs-4">',
			'#suffix' 			=> '</div>',
			'#title' 			=> $owner_name_check_data.t('(i)(c). Last name'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> $owner_lname,
			'#attributes' 		=> array( 'class' => array('form-control'),$owner_name_ck => $owner_name_ck)
			
		);
	
		$form['factory_part_premises']['country_premises'] 	= array(
			  '#prefix' 			=> '<div id="country_premises_div"><div class="col-md-4 col-xs-12">',
			  '#suffix' 			=> '</div></div>',
			  '#maxlength' 			=> 6, 
			  '#options' 			=> get_country_with_ph(),
			  '#default_value'      => !empty($country_premises) ? $country_premises :'',
			  '#title' 				=> t($owner_name_check_data.'(ii) Nationality'),
			  '#attributes' 		=> array('class' => array( ''),$owner_name_ck => $owner_name_ck ),
			  '#required' 			=> TRUE,
			  '#type' 				=> 'select',
			  '#ajax'				=> array(
											'event' 		=> 'change',
											'effect' 		=> 'fade',			
											'callback'		=> 'get_ajax_load_premises',
											'progress'		=>	array(
												'type'		=>'throbber',
												'message'	=>t('loading'),
											),
									)
			);

	if((isset($form_state['values']['country_premises']) && trim($form_state['values']['country_premises']) != '99') || (!isset($form_state['values']['country_premises']) && !empty($country_premises) && ($country_premises != '99')))
	{ 
			
			$form['factory_part_premises']['passport_premises'] 	= array(
				'#prefix' 			=> '<div id="premises_passport_oprmntadr_div" class="col-md-4 col-xs-12">',
				'#suffix' 			=> '</div>',
				'#title'			=> $owner_name_check_data.t('Enter Passport No.'),
				'#type' 			=> 'textfield',
				'#default_value'    => !empty($passport_premises) ? $passport_premises :'',
				'#attributes' 		=> array( 'class' => array('form-control')),
				'#required' 		=> TRUE,
			);
			$form['factory_part_premises']['passport_date_of_issue_premises'] 	= array(
				'#prefix' 			=> '<div id="premises_doi_div" class="col-md-4 col-xs-12">',
				'#suffix' 			=> '</div>',
				'#title'			=>	$owner_name_check_data.t('Enter Date of Issue'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#default_value'    => !empty($passport_date_of_issue_premises) ? $passport_date_of_issue_premises :'',
				'#attributes' 		=> array('class'=>array('form-control datepicker_retify'),'title'=>'Enter Date of Issue of passport.'),
			);
			$form['factory_part_premises']['passport_date_of_expiry_premises'] 	= array(
				'#prefix' 			=> '<div id="premises_doe_div" class="col-md-4 col-xs-12">',
				'#suffix' 			=> '</div>',
				'#title'			=>	$owner_name_check_data.t('Enter Date of Expiry'),
				'#type' 			=> 'textfield',
				'#default_value'    => !empty($passport_date_of_expiry_premises) ? $passport_date_of_expiry_premises :'',
				'#required' 		=> TRUE,
				'#attributes' 		=> array('class'=>array('form-control datepicker_retify'),'title'=>'Enter Date of Expiry of passport.'),
			);
			
			$form['factory_part_premises']['street_name_premises'] 	= array(
				'#prefix' 			=> '<div id="premises_streetname_div" class="col-md-4 col-xs-12" >',
				'#suffix' 			=> '</div>',
				'#default_value'    => !empty($street_name_premises) ? $street_name_premises :'',
				'#title'			=>	$owner_name_check_data.t('Enter Your Street Name / Road Name'),
				'#type' 			=> 'textfield',
				'#attributes' 		=> array('class'=>array('form-control')),
				'#required' 		=> TRUE,
			);
			$form['factory_part_premises']['house_no_premises'] 	= array(
				'#prefix' 			=> '<div class="col-md-4 col-xs-12" id="premises_houseno_div">',
				'#suffix' 			=> '</div>',
				'#title'			=>	$owner_name_check_data.t('Enter Your House No.'),
				'#type' 			=> 'textfield',
				'#attributes' 		=> array('class'=>array('form-control')),
				'#default_value'    => !empty($house_no_premises) ? $house_no_premises :'',
			);
			$form['factory_part_premises']['police_station_premises'] 	= array(
				'#prefix' 			=> '<div class="col-md-4 col-xs-12" id="premises_policestation_div">',
				'#suffix' 			=> '</div>',
				'#title'			=>	t('Enter Local Police Station'),
				'#type' 			=> 'textfield',
				'#attributes' 		=> array('class'=>array('form-control')),
				'#default_value'    => !empty($police_station_premises) ? $police_station_premises :'',
				'#required' 		=> TRUE,
			);
		
	
	} else{ 
		
		$form['factory_part_premises']['pincodepremises'] 	= array(
		  '#prefix' 			=> '<div class="col-md-4 col-xs-12" id="pincodepremises_id" >',
		  '#suffix' 			=> '</div>',
		  '#autocomplete_path' 	=> 'pinautocomplete',
		  '#id'					=> 'pincode_autocomplete_premises',
		  '#maxlength' 			=> 6, 
		  '#title'				=>	t($owner_name_check_data.'(iii) Pincode'),
		  '#required' 			=> TRUE,
		 
		  '#type' 				=> 'textfield',
		  '#default_value'  => !empty($pincodepremises) ? $pincodepremises    :'',
		  '#attributes' => array(
                'class' => array(
                    'form-control'
                ),
                'placeholder' => 'Pincode',
			    $owner_name_ck => $owner_name_ck
            ),
		  '#ajax'				=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',			
										'callback'		=> 'get_ajax_load_premises',
										'progress'		=>	array(
											'type'		=>'throbber',
											'message'	=>t('loading'),
										),
								)
		);
		$value_pincode_premises				= isset($form_state['values']['pincodepremises'])? $form_state['values']['pincodepremises'] : $pincodepremises;
		
		if(!empty($value_pincode_premises)){
			
		   $query_premises = db_select('fa_all_india_pin_code', 'p')->fields('p', array(
                'districtname',
                'statename',
                'pincode',
                'district_code',
                'state_code',
                'po_name'
            ))->condition('p.pincode', trim($value_pincode_premises), '=');
		
			$result_premises = $query_premises->execute();
	
			if($result_premises->rowcount()>0){
				$final_premises = $result_premises->fetchAssoc();
				$pincode_v_premises 		 = $value_pincode_premises;
				$state_v_premises		 = $final_premises['state_code'];
				$district_v_premises		 = $final_premises['district_code'];
				$post_office_premises 	 = $final_premises['po_name'];
			}
		} 
		
		if(!empty($state_v_premises)){
			$form['factory_part_premises']['state_premises'] = array(
			   '#title'			=>	$owner_name_check_data.'(iv) State',
			   '#type' 			=> 'select',
			   '#id'			=>'state_name',
			   '#attributes' 	=> array('class'=>array('form-control'), 'placeholder'=>'State',$owner_name_ck => $owner_name_ck),
			   '#disabled' 		=> TRUE, 
			   '#required' 		=> TRUE,
			   '#options' 		=> get_all_state($state_v_premises),
			   '#value' 		=> !empty($state_v_premises) ? $state_v_premises : $state_premises,
			   '#prefix' 		=> '<div class="col-md-4" id="premises_edit_emp_state_replace" >',
			   '#suffix' 		=> '</div>',
			   '#ajax'			=> array(
									'event' 		=> 'change',
									'effect' 		=> 'fade',			
									'callback'		=> 'get_ajax_load_premises',
									'progress'		=>	array(
										'type'		=>'throbber',
										'message'	=>t('loading'),
									),
					)
			);
		}else{
			$form['factory_part_premises']['state_premises'] = array(
			   '#title'			=> t('(iv) State'),
			   '#type' 			=> 'select',
			   '#id'			=>'state_name',
			   '#disabled' 		=> TRUE,
			   '#required' 		=> TRUE,
			   '#attributes' 	=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),

			   '#options' 		=> array(''=>t('Select State')),
			   '#prefix' 		=> '<div class="col-md-4" id="premises_edit_emp_state_replace" >',
			   '#suffix' 		=> '</div>',
			   '#ajax'			=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',			
										'callback'		=> 'get_ajax_load_premises',
										'progress'		=>	array(
											'type'		=>'throbber',
											'message'	=>t('loading'),
										),
								)
			);
		}

		$value_state_premises = isset($form_state['values']['state_premises'])? $form_state['values']['state_premises'] : $state_premises;
		
		if(!empty($state_v_premises)){	
			$form['factory_part_premises']['district_premises'] = array(
			   '#title'=> $owner_name_check_data.'(v) District',
			   '#type' => 'select',
			   '#id'=>'district_name',
			   '#disabled' => TRUE,
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'District',$owner_name_ck => $owner_name_ck),
			   '#options' => get_district_by_id($state_v_premises),
			   '#value' => !empty($district_v_premises) ? $district_v_premises : $district_premises,
			   '#prefix' => '<div class="col-md-4 clear-left" id="premises_edit_emp_district_replace">',
			   '#suffix' => '</div>',
			   '#required' 		=> TRUE,
			   '#ajax'				=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',			
										'callback'		=> 'get_ajax_load_premises',
										'progress'		=>	array(
											'type'		=>'throbber',
											'message'	=>t('loading'),
										),
								)
			);
		}else{
			$form['factory_part_premises']['district_premises'] = array(
			   '#title'=>	t('(v) District'),
			   '#type' => 'select',
			   '#id'=>'district_name',
			   '#disabled' => TRUE,
			   '#attributes' => array('class'=>array('form-control'), 'placeholder'=>'District'),
			   '#options' => array(''=>t('Select District')),
			   '#prefix' => '<div class="col-md-4" id="premises_edit_emp_district_replace">',
			   '#suffix' => '</div>',
			   '#required' 		=> TRUE,
			);
		}
		
		$value_district_premises	=	isset($form_state['values']['district_premises']) ? $form_state['values']['district_premises'] : $district_premises;
		
		if(!empty($district_v_premises) && !empty($state_v_premises) && $state_v_premises == 1){
			
			$form['factory_part_premises']['subdivision_premises'] = array(
			   '#title'=>	$owner_name_check_data.'(vi) Sub-Division',
			   '#type' => 'select',
			   '#attributes' => array('class'=>array('form-control'), 'placeholder'=>'Sub Division', $owner_name_ck => $owner_name_ck ),
			   '#required' 	=> TRUE,
			   '#options' => common_custom_user_subdivisionlist_list_new($district_v_premises),
			   '#default_value' => $subdivision_premises,
			   '#prefix' => '<div class="col-md-4" id="premises_empsubdv_replace">',
			   '#suffix' => '</div>',
			   '#ajax'		=> array(
							'event' 		=> 'change',
							'effect' 		=> 'fade',			
							'callback'		=> 'get_ajax_load_premises',
							'progress'		=>	array(
								'type'		=>'throbber',
								'message'	=>t('loading'),
							),
					)
			);
		}else{ 
			
			$form['factory_part_premises']['subdivision_premises'] = array(
			   '#prefix' => '<div id="premises_empsubdv_replace">',
			   '#suffix' => '</div>',
			);
		}		
		$value_subdivision_premises	= isset($form_state['values']['subdivision_premises']) ? $form_state['values']['subdivision_premises'] : $subdivision_premises;
		
		if(!empty($value_district_premises) && !empty($value_state_premises) && !empty($value_subdivision_premises) && $state_v_premises == 1){
			$form['factory_part_premises']['areatype_premises'] = array(
			   '#title'=> $owner_name_check_data.'(vii) Area Type',
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'Area Type', $owner_name_ck => $owner_name_ck),
			   '#required' 		=> TRUE,
			   '#options' => common_custom_user_areatype_list_new($value_district_premises, $value_subdivision_premises),
			   '#default_value' => $areatype_premises,
			   '#prefix' => '<div class="col-md-4" id="premises_emp_areatype_replace">',
			   '#suffix' => '</div>',
			   '#ajax'	=> array(
							'event' 		=> 'change',
							'effect' 		=> 'fade',			
							'callback'		=> 'get_ajax_load_premises',
							'progress'		=>	array(
								'type'		=> 'throbber',
								'message'	=> t('loading'),
							),
					)
			);
		}else{
			
			$form['factory_part_premises']['areatype_premises'] = array(
			   '#prefix' => '<div id="premises_emp_areatype_replace">',
			   '#suffix' => '</div>',
			);
		}
		
		$value_areatype_premises	=	isset($form_state['values']['areatype_premises']) ? $form_state['values']['areatype_premises'] : $areatype_premises;
	
		if(!empty($value_district_premises) && !empty($value_state_premises) && !empty($value_subdivision_premises) && !empty($value_areatype_premises) && $state_v_premises == 1){
			
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
			   '#title'=> $owner_name_check_data.'(viii) '.$areatype_name_premises,
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'subdivision', $owner_name_ck => $owner_name_ck),
			   '#required' 		=> TRUE,
			   '#options' => common_custom_user_block_list_new($value_subdivision_premises,$value_areatype_premises),
			   '#default_value' => $block_premises,
			   '#prefix' => '<div class="col-md-4" id="premises_empareatype_name_replace">',
			   '#suffix' => '</div>',
			   '#ajax'	=> array(
							'event' 		=> 'change',
							'effect' 		=> 'fade',			
							'callback'		=> 'get_ajax_load_premises',
							'progress'		=>	array(
								'type'		=>'throbber',
								'message'	=>t('loading'),
							),
					)
			);
		}else{
			$form['factory_part_premises']['block_premises'] = array(
			   '#prefix' => '<div id="premises_empareatype_name_replace">',
			   '#suffix' => '</div>',
			);
		}
		
		$value_block_premises	= 	isset($form_state['values']['block_premises']) ? $form_state['values']['block_premises'] : $block_premises;
					
		if(!empty($value_district_premises) && !empty($value_subdivision_premises) && !empty($value_areatype_premises)  && !empty($value_block_premises) && !empty($value_state_premises) && $state_v_premises == 1){
			
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
		   '#title'=> $owner_name_check_data.'(ix) '.$area_name_premises,
		   '#type' => 'select',
		   '#attributes' => array('class'=>array(''), 'placeholder'=>'panchayat', $owner_name_ck => $owner_name_ck),
		   '#default_value' => $panchayat_premises,
		   '#required' 		=> TRUE,
		   '#options' => get_full_villward($value_block_premises, $area_code_premises),
		   '#prefix' => '<div class="col-md-4" id="premises_emp_vill_ward_replace">',
		   '#suffix' => '</div>',
		   '#ajax'=> array(
				'event' 		=> 'change',
				'effect' 		=> 'fade',			
				'callback'		=> 'get_ajax_load_premises',
				'progress'		=>	array(
					'type'		=>'throbber',
					'message'	=>t('loading'),
				),
				)
			);
		}else{


			
			$form['factory_part_premises']['panchayat_premises'] = array(
			   '#prefix' => '<div id="premises_emp_vill_ward_replace">',
			   '#suffix' => '</div>',
			);
		}
		
		$value_panchayat_premises 	= 	isset($form_state['values']['panchayat_premises']) ? $form_state['values']['panchayat_premises'] : $panchayat_premises;
		
		if(!empty($value_district_premises) && !empty($value_subdivision_premises) && !empty($value_areatype_premises)  && !empty($value_block_premises) && !empty($value_state_premises) && !empty($value_panchayat_premises) && $state_v_premises == 1){
			
			$form['factory_part_premises']['policestation_premises'] = array(
			   '#title'=> $owner_name_check_data.'(x) Police Station',
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'Police Station', $owner_name_ck => $owner_name_ck),
			   '#required' 		=> TRUE,
			   '#default_value' => $policestation_premises,
			   '#options' => common_custom_user_ps_list_new($value_district_premises),
			   '#prefix' => '<div id="premises_empps_replace"><div class="col-md-4">',
			   '#suffix' => '</div></div>',
			);
		}else{
			$form['factory_part_premises']['policestation_premises'] = array(
			   '#prefix' => '<div id="premises_empps_replace">',
			   '#suffix' => '</div>',
			);
		}

			$form['factory_part_premises']['postoffice_premises'] = array(
			   '#title'=> $owner_name_check_data.'(xi) Post Office',
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'Post Office',$owner_name_ck => $owner_name_ck),
			   '#options' => common_custom_post_office_list_new($pincode_v_premises),
			   '#prefix' => '<div class="col-md-4" id="premises_post_office_div">',
			   '#suffix' => '</div>',
			   '#default_value' => $postoffice_premises,
			   '#required' 		=> TRUE,
			);
			
		

			$form['factory_part_premises']['passport_premises'] 	= array(
				'#prefix' 			=> '<div id="premises_passport_oprmntadr_div">',
				'#suffix' 			=> '</div>',
			);
			$form['factory_part_premises']['passport_date_of_issue_premises'] 	= array(
				'#prefix' 			=> '<div id="premises_doi_div">',
				'#suffix' 			=> '</div>',
			);
			$form['factory_part_premises']['passport_date_of_expiry_premises'] 	= array(
				'#prefix' 			=> '<div id="premises_doe_div">',
				'#suffix' 			=> '</div>',
			);
			
			if(!empty($state_v_premises) && $state_v_premises == 1)
			{
				$form['factory_part_premises']['street_name_premises'] 	= array(
					'#prefix' 			=> '<div id="premises_streetname_div" class="col-md-4 col-xs-12" >',
					'#suffix' 			=> '</div>',
					'#title'			=>	$owner_name_check_data.t('Enter Your Street Name / Road Name'),
					'#type' 			=> 'textfield',
					'#default_value'  	=> $street_name_premises,
					'#required' 		=> TRUE,
					   '#attributes' => array('class'=>array('form-control'),  $owner_name_ck => $owner_name_ck ),
					
				);
				$form['factory_part_premises']['house_no_premises'] 	= array(
					'#prefix' 			=> '<div id="premises_houseno_div" class="col-md-4 col-xs-12">',
					'#suffix' 			=> '</div>',
					'#title'			=>	$owner_name_check_data.t('Enter Your House No.'),
					'#type' 			=> 'textfield',
					'#default_value'  	=> $house_no_premises,
					'#required' 		=> TRUE,
					'#attributes' 		=> array('class'=>array('form-control'), $owner_name_ck => $owner_name_ck),
				);
				$form['factory_part_premises']['police_station_premises'] 	= array(
					'#prefix' 			=> '<div id="premises_policestation_div">',
					'#suffix' 			=> '</div>',
				);

			} else {
				$form['factory_part_premises']['street_name_premises'] 	= array(
					'#prefix' 			=> '<div id="premises_streetname_div" class="col-md-4 col-xs-12">',
					'#suffix' 			=> '</div>',
					'#title'			=>	$owner_name_check_data.t('Enter Your Street Name / Road Name'),
					'#type' 			=> 'textfield',
					'#default_value'  	=> $street_name_premises,
					'#required' 		=> TRUE,
					'#attributes' 		=> array('class'=>array('form-control'),$owner_name_ck => $owner_name_ck),
				);
				$form['factory_part_premises']['house_no_premises'] 	= array(
					'#prefix' 			=> '<div id="premises_houseno_div" class="col-md-4 col-xs-12">',
					'#suffix' 			=> '</div>',
					'#title'			=>	$owner_name_check_data.t('Enter Your House No.'),
					'#type' 			=> 'textfield',
					'#default_value'  	=> $house_no_premises,
					'#required' 		=> TRUE,
					'#attributes' 		=> array('class'=>array('form-control'),$owner_name_ck => $owner_name_ck),
				);
				$form['factory_part_premises']['police_station_premises'] 	= array(
					'#prefix' 			=> '<div id="premises_policestation_div" class="col-md-4 col-xs-12">',
					'#suffix' 			=> '</div>',
					'#title'			=>	$owner_name_check_data.t('Enter Local Police Station'),
					'#type' 			=> 'textfield',
					'#default_value'  	=> $police_station_premises,
					'#required' 		=> TRUE,
					'#attributes' 		=> array('class'=>array('form-control'),$owner_name_ck => $owner_name_ck),
				);
			}
			
	 }
	 
		$form['factory_part_premises']['addrline_premises'] = array(
		   '#title'=>'',
		   '#rows'=> 3,
		   '#type' => 'textarea',
		   '#attributes' => array('class'=>array('form-control'), 'placeholder'=>'Address Line', $owner_name_ck => $owner_name_ck),
		   '#default_value'  	=> $addrline_premises,
		   '#required' 		=> TRUE,
		   '#prefix'=> '<div id="addrline_premises_id"><div class="col-md-12">'.$owner_name_check_data.' Address ',
	   	   '#suffix' =>'</div></div>',
		);
	
	
	 $form['factory_part_premises']['thirdRowEnd'] = array(
		'#prefix' => '',
		'#suffix' => '</div>'
	  );		
	
    /********** Details of owner of the premises occupied as a factory - End **********/
	
	$form['factory_part_premises']['add_owner'] = array(
		'#prefix' 			=> '<div class="row"><div class="col-md-12 col-xs-12">',
		'#suffix' 			=> '</div></div>',
		'#attributes'       => array('class' => array('btn btn-success'),'style'=>'float: right;'),
		'#type' 			=> 'submit',
		'#value' 			=> t("Save"),
	);	
		
	$form['factory_part_premises']['view_owner'] = array(
		'#prefix'			=> '<div class="row"><div id="view_owner_details_id"><div class="col-md-12">',
		'#suffix' 		    => '</div></div></div>',
		'#type' 			=> 'markup',
		'#markup' 			=> view_owner_details($application_id,$service_id,$factory_type_id,$reference_no),
	);				

	if($application_status != 'F')
	{
		$form['back_link'] = array(
			
			'#markup' => l(t('<i class="fa fa-fw fa-chevron-left"></i> Back'), 'applicant/caf-reg/details-of-occupier-registration/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$referencenumber, array(
				'html' => TRUE,
				'attributes' => array(
					'class' => array(
						'btn btn-outline-dark pull-left '
					)
				)
			))
		);
    
		
		
	}
	 
    return $form;
}


function get_ajax_load_premises($form, $form_state)
{
	$commands = array();
	$commands[] = ajax_command_replace('#pincodepremises_id', drupal_render($form['factory_part_premises']['pincodepremises']));
	
	$commands[] = ajax_command_replace('#premises_edit_emp_state_replace', drupal_render($form['factory_part_premises']['state_premises']));
	$commands[] = ajax_command_replace('#premises_edit_emp_district_replace', drupal_render($form['factory_part_premises']['district_premises']));
	$commands[] = ajax_command_replace('#premises_empsubdv_replace', drupal_render($form['factory_part_premises']['subdivision_premises']));
	$commands[] = ajax_command_replace('#premises_emp_areatype_replace', drupal_render($form['factory_part_premises']['areatype_premises']));
	$commands[] = ajax_command_replace('#premises_empareatype_name_replace', drupal_render($form['factory_part_premises']['block_premises']));
	$commands[] = ajax_command_replace('#premises_emp_vill_ward_replace', drupal_render($form['factory_part_premises']['panchayat_premises']));
	$commands[] = ajax_command_replace('#premises_empps_replace', drupal_render($form['factory_part_premises']['policestation_premises']));
	$commands[] = ajax_command_replace('#premises_post_office_div', drupal_render($form['factory_part_premises']['postoffice_premises']));
	
	$commands[] = ajax_command_replace('#premises_user_aadhar_7_div', drupal_render($form['factory_part_premises']['user_aadhar_7']));
	$commands[] = ajax_command_replace('#premises_user_aadhar_8_div', drupal_render($form['factory_part_premises']['user_aadhar_8']));
	$commands[] = ajax_command_replace('#premises_user_aadhar_9_div', drupal_render($form['factory_part_premises']['user_aadhar_9']));
	
	$commands[] = ajax_command_replace('#premises_streetname_div', drupal_render($form['factory_part_premises']['street_name_premises']));
	$commands[] = ajax_command_replace('#premises_houseno_div', drupal_render($form['factory_part_premises']['house_no_premises']));
	$commands[] = ajax_command_replace('#premises_policestation_div', drupal_render($form['factory_part_premises']['police_station_premises']));
	
	$commands[] = ajax_command_replace('#premises_passport_oprmntadr_div', drupal_render($form['factory_part_premises']['passport_premises']));
	$commands[] = ajax_command_replace('#premises_doi_div', drupal_render($form['factory_part_premises']['passport_date_of_issue_premises']));
	$commands[] = ajax_command_replace('#premises_doe_div', drupal_render($form['factory_part_premises']['passport_date_of_expiry_premises']));
	


	return array('#type' => 'ajax', '#commands' => $commands);
}

function get_pollution_ajax_load($form, $form_state)
{
	$commands 	= array();	
	$commands[] = ajax_command_replace('#reference_no_approval_id', drupal_render($form['factory_catagory']['reference_no_approval_arrangments']));
	$commands[] = ajax_command_replace('#reference_date_approval_id', drupal_render($form['factory_catagory']['date_approval_arrangments']));
	$commands[] = ajax_command_replace('#edit-doc-file-ajax-wrapper', drupal_render($form['factory_catagory']['doc_file']));	
	$commands[] = ajax_command_replace('#view_doc_file_id', drupal_render($form['factory_catagory']['view_doc_file']));	
	return array('#type' => 'ajax', '#commands' => $commands);	
}


function caf_form_registration_owner_submit($form, &$form_state)
{
    global $user;
    $userid 			= $user->uid;
    $val    			= $form_state['values'];
	$service_id 		= encryption_decryption_fun('decrypt', $val['serviceid_hidden']);
	$application_id 	= encryption_decryption_fun('decrypt', $val['applicationid_hidden']);
	$factory_type_id	= encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$reference_no		= encryption_decryption_fun('decrypt',$val['reference_no_hidden']);

	

  	$app_status 	= encryption_decryption_fun('decrypt', $val['application_status_hidden']);
    $owner_details = array(

        // owner premises address //
		'owner_name' 				=> $val['owner_name'],
        'owner_mname'				=> $val['owner_mname'],
		'owner_lname'				=> $val['owner_lname'],
		'country_premises' 			=> $val['country_premises'],
		'aadhaar_premises' 			=> $val['aadhaar_premises'],
		'passport_premises'			=> $val['passport_premises'],
		'pincodepremises' 			=> $val['pincodepremises'],
        'state_premises'		 	=> $val['state_premises'],
        'district_premises' 		=> $val['district_premises'],
        'subdivision_premises' 		=> $val['subdivision_premises'],
        'areatype_premises' 		=> $val['areatype_premises'],
        'block_premises' 			=> $val['block_premises'],
        'panchayat_premises' 		=> $val['panchayat_premises'],
        'policestation_premises' 	=> $val['policestation_premises'],
        'postoffice_premises' 		=> $val['postoffice_premises'],
        'aadhaar_premises' 			=> $val['user_aadhar_7'].'-'.$val['user_aadhar_8'].'-'.$val['user_aadhar_9'],
		'addrline_premises' 		=> $val['addrline_premises'],
		'passport_date_of_issue_premises'    => $val['passport_date_of_issue_premises'],
		'passport_date_of_expiry_premises'   => $val['passport_date_of_expiry_premises'],
		'street_name_premises'      => $val['street_name_premises'],
		'house_no_premises'         => $val['house_no_premises'],
		'police_station_premises'   => $val['police_station_premises'],
		
		//Factory Identification according to WBPCB//
		'application_status' 		=> $app_status,

        'service_id' 				=> $service_id,
        'factory_type_id' 			=> $factory_type_id,
        'created_by' 				=> $userid,
		'application_id'  		    => $application_id,
        'application_reference_no'  => $reference_no,
		'created_date' 				=> date('Y-m-d H:i:s'),
    );
		
	if($val['op'] == "Save")
	{ 
		$queryabc = db_insert('fa_owner_details')->fields($owner_details)->execute();
		$cafa_Info = array(
       						
							'is_owner_tab'	=>  1,
							'modification_date'	=> date('Y-m-d')

							
	    			);
		$queryabc 	= 	db_update('fa_cafa');
		$queryabc	->	fields($cafa_Info);
		$queryabc	->	condition('id', $application_id, '=');
		$queryabc	->	execute();
		remark_input($reference_no,$application_id,'In','Owner information is submited for Registration')	;
		drupal_set_message('Owner Information has been saved successfully');
	}

		
    $form_state['rebuild'] = true;
}


function view_owner_details($application_id,$service_id,$factory_typeid,$reference_number){// echo 'A-'.$application_id.' B-'.$reference_number.' C-'.$service_id; die;
	$get_all_data 			= array();
	$type					= '';
	$details				= '';

	$get_all_data 			= get_all_owner_data($application_id,$service_id,$factory_typeid,$reference_number);
	
	$Wcounter		= 0;
	$per_page		= 10;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	$chunks 		= array_chunk($get_all_data, $per_page);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header			= array(
						array('data' => 'Sl. No','width' => '6%'),
						array('data'=> 'Owner Name','width' => '24%'),
						array('data'=> 'Address','width' => '60'),
						array('data'=> 'Action','width' => '10%'),	
					);
	if(!empty($get_all_data)){
		
		foreach($chunks[$current_page] as $owner_details){ 
			$Wcounter++;
			
			$getdata_owner_address =  array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
			$owner_address    = $owner_details->addrline_premises. '<br/>'.get_full_address('fa_owner_details','sub-table',$owner_details->id,$getdata_owner_address).'<br/>'.country_name($owner_details->country_premises);


			$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/del-owner-details/'.encryption_decryption_fun('encrypt', $owner_details->id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_typeid).'/'.encryption_decryption_fun('encrypt',$reference_number),array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));


	$owner_full_name = $owner_details->owner_name.' '.$owner_details->owner_mname.' '.$owner_details->owner_lname;

			$rows[] 	= array( 
								array('data' =>$Wcounter,'class' => array('')),
								array('data' =>$owner_full_name ,'class' => array('')),
								array('data' =>$owner_address,'class' => array('')),
								array('data' =>$delLink ,'class' => array('')),
								);
				} 
		}
		$output = theme_table(
			array(
				  'header' => $header,
				  'rows' => $rows,
				  'attributes' => array('id'=>'view_owner_details_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
				  'sticky' => true,
				  'caption' => 'All owner List',
				  'colgroups' => array(),
				  'empty' => t("No data found!") // The message to be displayed if table is empty
				)
			).theme('pager');	
		 	return $output;	
}

function del_owner_details($owner_id,$application_id,$service_id,$factory_typeid,$reference_number){


    drupal_add_library('system', 'drupal.ajax');
	if (trim(encryption_decryption_fun('decrypt', $owner_id)) != 0) {
				$query = db_delete('fa_owner_details');
		 		$query->condition('id', trim(encryption_decryption_fun('decrypt', $owner_id)),'=');
		 		//$query->condition('application_reference_no',trim(encryption_decryption_fun('decrypt', $reference_no)),'=');
		 		$query->execute();
			}
		 	$commands = array();
			$commands[] = ajax_command_replace('#view_owner_details_id', "<div id ='view_owner_details_id'><div class='col-md-12 col-xs-12'>".view_owner_details(encryption_decryption_fun('decrypt',$application_id),encryption_decryption_fun('decrypt',$service_id),encryption_decryption_fun('decrypt',$factory_typeid),encryption_decryption_fun('decrypt',$reference_number)).'</div></div>');
		 	$page = array('#type' => 'ajax', '#commands' => $commands);
		 	ajax_deliver($page);

	
	}

?> 