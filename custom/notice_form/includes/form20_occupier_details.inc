<?php
  drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
  drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
  
  function form20_occupier_details($form, &$form_state, $formid ,$referenceid, $factorytypeid, $serviceid){
	  
	  global $user;
	  $uid 						= $user->uid;
	  $form = array();
	  
	    $form_id 	 	= encryption_decryption_fun('decrypt', $formid);
	    $reference_id   = encryption_decryption_fun('decrypt', $referenceid);
	$factory_typeid 	= encryption_decryption_fun('decrypt', $factorytypeid);
	$service_id 	= encryption_decryption_fun('decrypt', $serviceid); //echo $form_id.'--'.$reference_id.'--'.$factory_typeid.'--'.$service_id;

	 //PREVIOUS TAB FILL REDIRECTION
	 if($form_id == 0 && $reference_id == 0 && $factory_id == 0){
	  drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Factory Information tab.</h5>'),'alert alert-danger alert-dismissible');
	  drupal_goto('applicant/form20/default/'.$formid.'/'.$referenceid.'/'.$factorytypeid.'/'.$serviceid) ;
	}
	 //PREVIOUS TAB FILL REDIRECTION
	 
		
		
		//


		$get_all_data 		= get_notice_poisoning_data($form_id,$reference_id,$factory_typeid,$service_id);//print_r($get_all_data);//die;
		
		if($get_all_data[0]->pincodeoprmntadr != '')
		{ 	
			$name_occupier 					    = $get_all_data[0]->name_occupier;
			$country_oprmntadr 					= $get_all_data[0]->country_oprmntadr;
			$passport_oprmntadr					= $get_all_data[0]->passport_oprmntadr;
			$passport_date_of_issue_oprmntadr	= $get_all_data[0]->passport_date_of_issue_oprmntadr;
			$passport_date_of_expiry_oprmntadr	= $get_all_data[0]->passport_date_of_expiry_oprmntadr;
			$street_name_oprmntadr				= $get_all_data[0]->street_name_oprmntadr;
			$house_no_oprmntadr					= $get_all_data[0]->house_no_oprmntadr;
			$police_station_oprmntadr			= $get_all_data[0]->police_station_oprmntadr;
			$pincodeoprmntadr					= $get_all_data[0]->pincodeoprmntadr;
			$state_oprmntadr         		    = $get_all_data[0]->state_oprmntadr;
			$district_oprmntadr       		    = $get_all_data[0]->district_oprmntadr;
			$subdivision_oprmntadr   		    = $get_all_data[0]->subdivision_oprmntadr;
			$areatype_oprmntadr       		    = $get_all_data[0]->areatype_oprmntadr;
			$block_oprmntadr          		    = $get_all_data[0]->block_oprmntadr;
			$panchayat_oprmntadr      		    = $get_all_data[0]->panchayat_oprmntadr;
			$policestation_oprmntadr  		    = $get_all_data[0]->policestation_oprmntadr;
			$postoffice_oprmntadr    		    = $get_all_data[0]->postoffice_oprmntadr;
			$addrline_oprmntadr       		    = $get_all_data[0]->addrline_oprmntadr;
			$aadhaar_oprmntadr                  = $get_all_data[0]->aadhaar_oprmntadr;
			$aadhar 					        = explode('-',$aadhaar_oprmntadr);
		} else {
		
			$ServFactId	=  db_query("SELECT factory_id FROM {fa_form20_notice_poisoning} WHERE id = '".$form_id."'")->fetchObject(); 
			$ServFactTypeId	=  db_query("SELECT service_id FROM {fa_cafa} WHERE id = '".$ServFactId->factory_id."'")->fetchObject(); 
			$occupier_details = get_all_occupier_data($ServFactId->factory_id,$ServFactTypeId->service_id,$factory_typeid,$reference_id);
			
			$name_occupier 					    = $occupier_details[0]->name_occupier;
			$country_oprmntadr 					= $occupier_details[0]->country_oprmntadr;
			$passport_oprmntadr					= $occupier_details[0]->passport_oprmntadr;
			$passport_date_of_issue_oprmntadr	= $occupier_details[0]->passport_date_of_issue_oprmntadr;
			$passport_date_of_expiry_oprmntadr	= $occupier_details[0]->passport_date_of_expiry_oprmntadr;
			$street_name_oprmntadr				= $occupier_details[0]->street_name_oprmntadr;
			$house_no_oprmntadr					= $occupier_details[0]->house_no_oprmntadr;
			$police_station_oprmntadr			= $occupier_details[0]->police_station_oprmntadr;
			$pincodeoprmntadr					= $occupier_details[0]->pincodeoprmntadr;
			$state_oprmntadr         		    = $occupier_details[0]->state_oprmntadr;
			$district_oprmntadr       		    = $occupier_details[0]->district_oprmntadr;
			$subdivision_oprmntadr   		    = $occupier_details[0]->subdivision_oprmntadr;
			$areatype_oprmntadr       		    = $occupier_details[0]->areatype_oprmntadr;
			$block_oprmntadr          		    = $occupier_details[0]->block_oprmntadr;
			$panchayat_oprmntadr      		    = $occupier_details[0]->panchayat_oprmntadr;
			$policestation_oprmntadr  		    = $occupier_details[0]->policestation_oprmntadr;
			$postoffice_oprmntadr    		    = $occupier_details[0]->postoffice_oprmntadr;
			$addrline_oprmntadr       		    = $occupier_details[0]->addrline_oprmntadr;
			$aadhaar_oprmntadr                  = $occupier_details[0]->aadhaar_oprmntadr;
			$aadhar 					        = explode('-',$aadhaar_oprmntadr);
			
		}
	 /* if($form_id != '')
	  { 
		
		//print_r($get_all_data); 
		$aadhar = explode('-',$get_all_data[0]->aadhaar_oprmntadr);
		$name_occupier = $get_all_data[0]->name_occupier;
	  }*/

	 	$form['formid_hidden'] 		= array(
			'#type' 				=> 'hidden',
			'#default_value' 		=> $formid
		);	
	  	$form['referenceid_hidden'] = array(
			'#type' 				=> 'hidden',
			'#default_value' 		=> $referenceid
		);	
	  	$form['factorytypeid_hidden'] 	= array(
			'#type' 				=> 'hidden',
			'#default_value' 		=> $factorytypeid
		);
			
		$form['serviceid_hidden'] 	= array(
			'#type' 				=> 'hidden',
			'#default_value' 		=> $serviceid
		);
	
		$form['notice_poisioning_occupier'] = array(
			'#type' 			=> 'fieldset',
			'#title' 			=> t('Address of Office or Private Residence of Occupier'),
			'#collapsible' 		=> TRUE, // Added
			'#collapsed' 		=> FALSE,  // Added
		);		

		$form['notice_poisioning_occupier']['name_occupier'] 	= array(
			'#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-12"><label class="input">',
			'#suffix' 			=> '</label></div>',
			'#title'			=>	t('Enter Occupier Name'),
			'#type' 			=> 'textfield',
			'#default_value'    => !empty($name_occupier) ? $name_occupier : '',
			'#required' 		=> TRUE,
		);
		$form['notice_poisioning_occupier']['country_oprmntadr'] 	= array(
			  '#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="select label-block">',
			  '#suffix' 			=> '</label></div>',
			  '#maxlength' 			=> 6, 
			  '#options' 			=> get_country_with_ph(),
			  '#default_value'      => !empty($country_oprmntadr) ? $country_oprmntadr : '',
			  '#title' 				=> t('(i) Nationality'),
			  '#attributes' 		=> array('class' => array( '')),
			  '#required' 			=> TRUE,
			  '#type' 				=> 'select',
			  '#ajax'				=> array(
											'event' 		=> 'change',
											'effect' 		=> 'fade',			
											'callback'		=> 'get_ajax_load_oprmntadr',
											'progress'		=>	array(
												'type'		=>'throbber',
												'message'	=>t('loading'),
											),
									)
			);
//echo $country_oprmntadr;
//echo $form_state['values']['country_oprmntadr'];

	if((isset($form_state['values']['country_oprmntadr']) && trim($form_state['values']['country_oprmntadr']) != '99') || (!isset($form_state['values']['country_oprmntadr']) && !empty($country_oprmntadr) && ($country_oprmntadr != '99')))
	{ 
			$form['notice_poisioning_occupier']['pincodeoprmntadr'] = array(
				'#prefix' 	=> '<div id="pincodeoprmntadr_id">',
				'#suffix' 	=> '</div>'
			);
			$form['notice_poisioning_occupier']['state_oprmntadr'] = array(
				'#prefix' 	=> '<div id="oprmntadr_edit_emp_state_replace">',
				'#suffix' 	=> '</div>'
			);
		    $form['notice_poisioning_occupier']['district_oprmntadr'] = array(
				'#prefix' 	=> '<div id="oprmntadr_edit_emp_district_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['notice_poisioning_occupier']['subdivision_oprmntadr'] = array(
				'#prefix' 	=> '<div id="oprmntadr_empsubdv_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['notice_poisioning_occupier']['areatype_oprmntadr'] = array(
				'#prefix' 	=> '<div id="oprmntadr_emp_areatype_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['notice_poisioning_occupier']['block_oprmntadr'] = array(
				'#prefix' 	=> '<div id="oprmntadr_empareatype_name_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['notice_poisioning_occupier']['panchayat_oprmntadr'] = array(
				'#prefix' 	=> '<div id="oprmntadr_emp_vill_ward_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['notice_poisioning_occupier']['policestation_oprmntadr'] = array(
				'#prefix' 	=> '<div id="oprmntadr_empps_replace">',
				'#suffix' 	=> '</div>'
			);
			$form['notice_poisioning_occupier']['postoffice_oprmntadr'] = array(
				'#prefix' 	=> '<div id="oprmntadr_post_office_div">',
				'#suffix' 	=> '</div>'
			);
			$form['notice_poisioning_occupier']['user_aadhar_1'] = array(
			   '#prefix' => '<div id="oprmntadr_user_aadhar_1_div">',
			   '#suffix' => '</div>',
			);
			$form['notice_poisioning_occupier']['user_aadhar_2'] = array(
			   '#prefix' => '<div id="oprmntadr_user_aadhar_2_div">',
			   '#suffix' => '</div>',
			);
			$form['notice_poisioning_occupier']['user_aadhar_3'] = array(
			   '#prefix' => '<div id="oprmntadr_user_aadhar_3_div">',
			   '#suffix' => '</div>',
			);
			$form['notice_poisioning_occupier']['passport_oprmntadr'] 	= array(
				'#prefix' 			=> '<div id="oprmntadr_passport_oprmntadr_div" class="col-md-4 col-xs-12"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Passport No.'),
				'#type' 			=> 'textfield',
				'#default_value'    => !empty($passport_oprmntadr) ? $passport_oprmntadr : '',
				'#required' 		=> TRUE,
			);
			$form['notice_poisioning_occupier']['passport_date_of_issue_oprmntadr'] 	= array(
				'#prefix' 			=> '<div id="oprmntadr_doi_div" class="col-md-4 col-xs-12"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Date of Issue'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#default_value'    => !empty($passport_date_of_issue_oprmntadr) ? $passport_date_of_issue_oprmntadr : '',
				'#attributes' 		=> array('class'=>array('form-control datepicker_retify'),'title'=>'Enter Date of Issue of passport.'),
			);
			$form['notice_poisioning_occupier']['passport_date_of_expiry_oprmntadr'] 	= array(
				'#prefix' 			=> '<div id="oprmntadr_doe_div" class="col-md-4 col-xs-12"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Date of Expiry'),
				'#type' 			=> 'textfield',
				'#required' 		=> TRUE,
				'#default_value'    => !empty($passport_date_of_expiry_oprmntadr) ? $passport_date_of_expiry_oprmntadr :'',
				'#attributes' 		=> array('class'=>array('form-control datepicker_retify'),'title'=>'Enter Date of Expiry of passport.'),
			);
			
			$form['notice_poisioning_occupier']['street_name_oprmntadr'] 	= array(
				'#prefix' 			=> '<div id="oprmntadr_streetname_div" class="col-md-4 col-xs-12" ><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Your Street Name / Road Name'),
				'#type' 			=> 'textfield',
				'#default_value'    => !empty($street_name_oprmntadr) ? $street_name_oprmntadr :'',
				'#required' 		=> TRUE,
			);
			$form['notice_poisioning_occupier']['house_no_oprmntadr'] 	= array(
				'#prefix' 			=> '<div class="col-md-4 col-xs-12" id="oprmntadr_houseno_div"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Your House No.'),
				'#type' 			=> 'textfield',
				'#default_value'    => !empty($house_no_oprmntadr) ? $house_no_oprmntadr :'',
				'#required' 		=> TRUE,
			);
			$form['notice_poisioning_occupier']['police_station_oprmntadr'] 	= array(
				'#prefix' 			=> '<div class="col-md-4 col-xs-12" id="oprmntadr_policestation_div"><label class="input">',
				'#suffix' 			=> '</label></div>',
				'#title'			=>	t('Enter Local Police Station'),
				'#type' 			=> 'textfield',
				'#default_value'    => !empty($police_station_oprmntadr) ? $police_station_oprmntadr : '',
				'#required' 		=> TRUE,
			);
			
	} else{ 
		
		$form['notice_poisioning_occupier']['pincodeoprmntadr'] 	= array(
		  '#prefix' 			=> '<div class="col-md-4 col-xs-12" id="pincodeoprmntadr_id" ><label class="input">',
		  '#suffix' 			=> '</label></div>',
		  '#autocomplete_path' 	=> 'pinautocomplete',
		  '#id'					=> 'pincode_autocomplete_oprmntadr',
		  '#maxlength' 			=> 6, 
		  '#title'				=>	t('(iii) Pincode'),
		  '#required' 			=> TRUE,
		  '#type' 				=> 'textfield',
		  '#default_value'  => !empty($pincodeoprmntadr) ? $pincodeoprmntadr : '',
		  '#attributes' => array(
                'class' => array(''),'placeholder' => 'Pincode' ),
		  '#ajax'				=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',			
										'callback'		=> 'get_ajax_load_oprmntadr',
										'progress'		=>	array(
											'type'		=>'throbber',
											'message'	=>t('loading'),
										),
								)
		);
		$value_pincode_oprmntadr				= isset($form_state['values']['pincodeoprmntadr'])? $form_state['values']['pincodeoprmntadr'] : $pincodeoprmntadr;
		
		if(!empty($value_pincode_oprmntadr)){
			
		   $query_oprmntadr = db_select('fa_all_india_pin_code', 'p')->fields('p', array(
                'districtname',
                'statename',
                'pincode',
                'district_code',
                'state_code',
                'po_name'
            ))->condition('p.pincode', trim($value_pincode_oprmntadr), '=');
		
			$result_oprmntadr = $query_oprmntadr->execute();
	
			if($result_oprmntadr->rowcount()>0){
				$final_oprmntadr         = $result_oprmntadr->fetchAssoc();
				$pincode_v_oprmntadr 	 = $value_pincode_oprmntadr;
				$state_v_oprmntadr		 = $final_oprmntadr['state_code'];
				$district_v_oprmntadr	 = $final_oprmntadr['district_code'];
				$post_office_oprmntadr 	 = $final_oprmntadr['po_name'];
			}
		} 
		
		if(!empty($state_v_oprmntadr)){
			$form['notice_poisioning_occupier']['state_oprmntadr'] = array(
			   '#title'			=>	'(iv) State',
			   '#type' 			=> 'select',
			   '#id'			=>'state_name',
			   '#attributes' 	=> array('class'=>array(''), 'placeholder'=>'State'),
			   '#disabled' 		=> TRUE, 
			   '#required' 		=> TRUE,
			   '#options' 		=> get_all_state($state_v_oprmntadr),
			   '#value' 		=> !empty($state_v_oprmntadr) ? $state_v_oprmntadr : '',
			   '#prefix' 		=> '<div class="col-md-4" id="oprmntadr_edit_emp_state_replace" ><label class="select label-block">',
			   '#suffix' 		=> '</label></div>',
			   '#ajax'			=> array(
									'event' 		=> 'change',
									'effect' 		=> 'fade',			
									'callback'		=> 'get_ajax_load_oprmntadr',
									'progress'		=>	array(
										'type'		=>'throbber',
										'message'	=>t('loading'),
									),
					)
			);
		}else{
			$form['notice_poisioning_occupier']['state_oprmntadr'] = array(
			   '#title'			=> t('(iv) State'),
			   '#type' 			=> 'select',
			   '#id'			=>'state_name',
			   '#disabled' 		=> TRUE,
			   '#required' 		=> TRUE,
			   '#attributes' 	=> array('class'=>array(''), 'placeholder'=>'State', 'readonly' => 'readonly'),

			   '#options' 		=> array(''=>t('Select State')),
			   '#prefix' 		=> '<div class="col-md-4" id="oprmntadr_edit_emp_state_replace" ><label class="select label-block">',
			   '#suffix' 		=> '</label></div>',
			   '#ajax'			=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',			
										'callback'		=> 'get_ajax_load_oprmntadr',
										'progress'		=>	array(

											'type'		=>'throbber',
											'message'	=>t('loading'),
										),
								)
			);
		}

		$value_state_oprmntadr = isset($form_state['values']['state_oprmntadr'])? $form_state['values']['state_oprmntadr'] : $state_oprmntadr;
		
		if(!empty($state_v_oprmntadr)){	
			$form['notice_poisioning_occupier']['district_oprmntadr'] = array(
			   '#title'=> '(v) District',
			   '#type' => 'select',
			   '#id'=>'district_name',
			   '#disabled' => TRUE,
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'District'),
			   '#options' => get_district_by_id($state_v_oprmntadr),
			   '#value' => !empty($district_v_oprmntadr) ? $district_v_oprmntadr : '',
			   '#prefix' => '<div class="col-md-4" id="oprmntadr_edit_emp_district_replace"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#required' 		=> TRUE,
			   '#ajax'				=> array(
										'event' 		=> 'change',
										'effect' 		=> 'fade',			
										'callback'		=> 'get_ajax_load_oprmntadr',
										'progress'		=>	array(
											'type'		=>'throbber',
											'message'	=>t('loading'),
										),
								)
			);
		}else{
			$form['notice_poisioning_occupier']['district_oprmntadr'] = array(
			   '#title'=>	t('(v) District'),
			   '#type' => 'select',
			   '#id'=>'district_name',
			   '#disabled' => TRUE,
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'District'),
			   '#options' => array(''=>t('Select District')),
			   '#prefix' => '<div class="col-md-4" id="oprmntadr_edit_emp_district_replace"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#required' 		=> TRUE,
			);
		}
		
		$value_district_oprmntadr	=	isset($form_state['values']['district_oprmntadr']) ? $form_state['values']['district_oprmntadr'] : $district_oprmntadr;
		
		if(!empty($district_v_oprmntadr) && !empty($state_v_oprmntadr) && $state_v_oprmntadr == 1){
			
			$form['notice_poisioning_occupier']['subdivision_oprmntadr'] = array(
			   '#title'=>	'(vi) Sub-Division',
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'Sub Division' ),
			   '#required' 	=> TRUE,
			   '#options' => common_custom_user_subdivisionlist_list_new($district_v_oprmntadr),
			   '#default_value'   => $subdivision_oprmntadr,
			   '#prefix' => '<div class="col-md-4" id="oprmntadr_empsubdv_replace"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#ajax'		=> array(
							'event' 		=> 'change',
							'effect' 		=> 'fade',			
							'callback'		=> 'get_ajax_load_oprmntadr',
							'progress'		=>	array(
								'type'		=>'throbber',
								'message'	=>t('loading'),
							),
					)
			);
		}else{ 
			
			$form['notice_poisioning_occupier']['subdivision_oprmntadr'] = array(
			   '#prefix' => '<div id="oprmntadr_empsubdv_replace">',
			   '#suffix' => '</div>',
			);
		}		
		$value_subdivision_oprmntadr	= isset($form_state['values']['subdivision_oprmntadr']) ? $form_state['values']['subdivision_oprmntadr'] : $subdivision_oprmntadr;
		
		if(!empty($value_district_oprmntadr) && !empty($value_state_oprmntadr) && !empty($value_subdivision_oprmntadr) && $state_v_oprmntadr == 1){
			$form['notice_poisioning_occupier']['areatype_oprmntadr'] = array(
			   '#title'=> '(vii) Area Type',
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'Area Type'),
			   '#required' 		=> TRUE,
			   '#options' => common_custom_user_areatype_list_new($value_district_oprmntadr, $value_subdivision_oprmntadr),
			   '#default_value' => $areatype_oprmntadr,
			   '#prefix' => '<div class="col-md-4" id="oprmntadr_emp_areatype_replace"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#ajax'	=> array(
							'event' 		=> 'change',
							'effect' 		=> 'fade',			
							'callback'		=> 'get_ajax_load_oprmntadr',
							'progress'		=>	array(
								'type'		=> 'throbber',
								'message'	=> t('loading'),
							),
					)
			);
		}else{
			
			$form['notice_poisioning_occupier']['areatype_oprmntadr'] = array(
			   '#prefix' => '<div id="oprmntadr_emp_areatype_replace">',
			   '#suffix' => '</div>',
			);
		}
		
		$value_areatype_oprmntadr	=	isset($form_state['values']['areatype_oprmntadr']) ? $form_state['values']['areatype_oprmntadr'] : $areatype_oprmntadr;
	
		if(!empty($value_district_oprmntadr) && !empty($value_state_oprmntadr) && !empty($value_subdivision_oprmntadr) && !empty($value_areatype_oprmntadr) && $state_v_oprmntadr == 1){
			
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
			
			$form['notice_poisioning_occupier']['block_oprmntadr'] = array(
			   '#title'=> '(viii) '.$areatype_name_oprmntadr,
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'subdivision'),
			   '#required' 		=> TRUE,
			   '#options' => common_custom_user_block_list_new($value_subdivision_oprmntadr,$value_areatype_oprmntadr),
			   '#default_value' => $block_oprmntadr,
			   '#prefix' => '<div class="col-md-4" id="oprmntadr_empareatype_name_replace"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#ajax'	=> array(
							'event' 		=> 'change',
							'effect' 		=> 'fade',			
							'callback'		=> 'get_ajax_load_oprmntadr',
							'progress'		=>	array(
								'type'		=>'throbber',
								'message'	=>t('loading'),
							),
					)
			);
		}else{
			$form['notice_poisioning_occupier']['block_oprmntadr'] = array(
			   '#prefix' => '<div id="oprmntadr_empareatype_name_replace">',
			   '#suffix' => '</div>',
			);
		}
		
		$value_block_oprmntadr	= 	isset($form_state['values']['block_oprmntadr']) ? $form_state['values']['block_oprmntadr'] : $block_oprmntadr;
					
		if(!empty($value_district_oprmntadr) && !empty($value_subdivision_oprmntadr) && !empty($value_areatype_oprmntadr)  && !empty($value_block_oprmntadr) && !empty($value_state_oprmntadr) && $state_v_oprmntadr == 1){
			
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
		$form['notice_poisioning_occupier']['panchayat_oprmntadr'] = array(
		   '#title'=> '(ix) '.$area_name_oprmntadr,
		   '#type' => 'select',
		   '#attributes' => array('class'=>array(''), 'placeholder'=>'panchayat'),
		   '#default_value' => $panchayat_oprmntadr,
		   '#required' 		=> TRUE,
		   '#options' => get_full_villward($value_block_oprmntadr, $area_code_oprmntadr),
		   '#prefix' => '<div id="oprmntadr_emp_vill_ward_replace"><div class="col-md-4"><label class="select label-block">',
		   '#suffix' => '</label></div></div>',
		   '#ajax'=> array(
				'event' 		=> 'change',
				'effect' 		=> 'fade',			
				'callback'		=> 'get_ajax_load_oprmntadr',
				'progress'		=>	array(
					'type'		=>'throbber',
					'message'	=>t('loading'),
				),
				)
			);
		}else{
			
			$form['notice_poisioning_occupier']['panchayat_oprmntadr'] = array(
			   '#prefix' => '<div id="oprmntadr_emp_vill_ward_replace">',
			   '#suffix' => '</div>',
			);
		}
		
		$value_panchayat_oprmntadr 	= 	isset($form_state['values']['panchayat_oprmntadr']) ? $form_state['values']['panchayat_oprmntadr'] : $panchayat_oprmntadr;

		if(!empty($value_district_oprmntadr) && !empty($value_subdivision_oprmntadr) && !empty($value_areatype_oprmntadr)  && !empty($value_block_oprmntadr) && !empty($value_state_oprmntadr) && !empty($value_panchayat_oprmntadr) && $state_v_oprmntadr == 1){
			
			$form['notice_poisioning_occupier']['policestation_oprmntadr'] = array(
			   '#title'=> '(x) Police Station',
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'Police Station'),
			   '#required' 		=> TRUE,
			   '#default_value' => $policestation_oprmntadr,
			   '#options' => common_custom_user_ps_list_new($value_district_oprmntadr),
			   '#prefix' => '<div id="oprmntadr_empps_replace"><div class="col-md-4"><label class="select label-block">',
			   '#suffix' => '</label></div></div>',
			);
		}else{
			$form['notice_poisioning_occupier']['policestation_oprmntadr'] = array(
			   '#prefix' => '<div id="oprmntadr_empps_replace">',
			   '#suffix' => '</div>',
			);
		}

			$form['notice_poisioning_occupier']['postoffice_oprmntadr'] = array(
			   '#title'=> '(xi) Post Office',
			   '#type' => 'select',
			   '#attributes' => array('class'=>array(''), 'placeholder'=>'Post Office'),
			   '#options' => common_custom_post_office_list_new($pincode_v_oprmntadr),
			   '#default_value' => $postoffice_oprmntadr,
			   '#prefix' => '<div class="col-md-4" id="oprmntadr_post_office_div"><label class="select label-block">',
			   '#suffix' => '</label></div>',
			   '#required' 		=> TRUE,
			);
			
			$form['notice_poisioning_occupier']['user_aadhar_1'] = array(
			   '#title'			=>	t('Aadhar No.'),
			   '#type' 			=> 'textfield',
			   '#prefix' 		=> '<div id="oprmntadr_user_aadhar_1_div" class="col-md-1 aadhar_no"><label class="input">',
			   '#suffix' 		=> '</label></div>',
			   '#default_value'  	=> $aadhar[0],
			   '#attributes' => array('class' => array('NoField'),'maxlength' => 4,'size' => '','id'=>'number1'),
			);
			$form['notice_poisioning_occupier']['user_aadhar_2'] = array(
			   '#title'			=> t('&nbsp;'),
			   '#type' 			=> 'textfield',
			   '#prefix' 		=> '<div id="oprmntadr_user_aadhar_2_div" class="col-md-1 aadhar_no"><label class="input">',
			   '#suffix' 		=> '</label></div>',
			   '#default_value'  	=> $aadhar[1],
			   '#attributes' => array('class' => array('NoField'),'maxlength' => 4,'size' => '','id'=>'number2'),
			);
			$form['notice_poisioning_occupier']['user_aadhar_3'] = array(
			   '#title'			=>	t('&nbsp;'),
			   '#type' 			=> 'textfield',
			   '#prefix' 		=> '<div id="oprmntadr_user_aadhar_3_div" class="col-md-1 aadhar_no"><label class="input">',
			   '#suffix' 		=> '</label></div>',
			   '#default_value'  	=> $aadhar[2],
			   '#attributes' => array('class' => array('NoField'),'maxlength' => 4,'size' => '','id'=>'number3'),
			);
			
			$form['notice_poisioning_occupier']['passport_oprmntadr'] 	= array(
				'#prefix' 			=> '<div id="oprmntadr_passport_oprmntadr_div">',
				'#suffix' 			=> '</div>',
			);
			$form['notice_poisioning_occupier']['passport_date_of_issue_oprmntadr'] 	= array(
				'#prefix' 			=> '<div id="oprmntadr_doi_div">',
				'#suffix' 			=> '</div>',
			);
			$form['notice_poisioning_occupier']['passport_date_of_expiry_oprmntadr'] 	= array(
				'#prefix' 			=> '<div id="oprmntadr_doe_div">',
				'#suffix' 			=> '</div>',
			);
			
			if(!empty($state_v_oprmntadr) && $state_v_oprmntadr == 1)
			{
				$form['notice_poisioning_occupier']['street_name_oprmntadr'] 	= array(
					'#prefix' 			=> '<div id="oprmntadr_streetname_div" class="col-md-4 col-xs-12"><label class="input">',
					'#suffix' 			=> '</label></div>',
					'#title'			=>	t('Enter Your Street Name / Road Name'),
					'#type' 			=> 'textfield',
					'#default_value'    => $street_name_oprmntadr,
					'#required' 		=> TRUE,
					//'#attributes' 		=> array($country_oprmntadr_ck => $country_oprmntadr_ck),
				);
				$form['notice_poisioning_occupier']['house_no_oprmntadr'] 	= array(
					'#prefix' 			=> '<div id="oprmntadr_houseno_div" class="col-md-4 col-xs-12"><label class="input">',
					'#suffix' 			=> '</label></div>',
					'#title'			=>	t('Enter Your House No.'),
					'#type' 			=> 'textfield',
					'#default_value'    => $house_no_oprmntadr,
					'#required' 		=> TRUE,
					//'#attributes' 		=> array($country_oprmntadr_ck => $country_oprmntadr_ck),
				);
				$form['notice_poisioning_occupier']['police_station_oprmntadr'] 	= array(
					'#prefix' 			=> '<div id="oprmntadr_policestation_div">',
					'#suffix' 			=> '</div>',
				);

			} else {
				$form['notice_poisioning_occupier']['street_name_oprmntadr'] 	= array(
					'#prefix' 			=> '<div id="oprmntadr_streetname_div" class="col-md-4 col-xs-12" ><label class="input">',
					'#suffix' 			=> '</label></div>',
					'#title'			=>	t('Enter Your Street Name / Road Name'),
					'#type' 			=> 'textfield',
					'#default_value'    => $street_name_oprmntadr,
					'#required' 		=> TRUE,
					//'#attributes' 		=> array($country_oprmntadr_ck => $country_oprmntadr_ck),
				);
				$form['notice_poisioning_occupier']['house_no_oprmntadr'] 	= array(
					'#prefix' 			=> '<div id="oprmntadr_houseno_div" class="col-md-4 col-xs-12"><label class="input">',
					'#suffix' 			=> '</label></div>',
					'#title'			=>	t('Enter Your House No.'),
					'#type' 			=> 'textfield',
					'#default_value'    => $house_no_oprmntadr,
					'#required' 		=> TRUE,
					//'#attributes' 		=> array($country_oprmntadr_ck => $country_oprmntadr_ck),
				);
				$form['notice_poisioning_occupier']['police_station_oprmntadr'] 	= array(
					'#prefix' 			=> '<div id="oprmntadr_policestation_div" class="col-md-4 col-xs-12"><label class="input">',
					'#suffix' 			=> '</label></div>',
					'#title'			=>	t('Enter Local Police Station'),
					'#type' 			=> 'textfield',
					'#default_value'    => $police_station_oprmntadr,
					'#required' 		=> TRUE,
					//'#attributes' 		=> array($country_oprmntadr_ck => $country_oprmntadr_ck),
				);
			}
			
	 }
	 
	$form['notice_poisioning_occupier']['addrline_oprmntadr'] = array(
		   '#title'=>'',
		   '#rows'=> 3,
		   '#type' => 'textarea',
		   '#attributes' => array('class'=>array(''), 'placeholder'=> 'Address Line'),
		   '#default_value'    => $addrline_oprmntadr,
		   '#prefix'=> '<div class="col-md-12"><label class="textarea label-block"> Address <span style="color:red;">*</span>',
	   	   '#suffix' =>'</label></div>',
	);	
	
	/********** Occupier Permanent Address - End **********/

		$form['notice_poisioning_occupier_end']['submit'] = array (
			'#attributes' 	=> array('class' => array('btn btn-success pull-right')),
			'#type' 		=> 'submit',
			'#value'		=> 'Save'
		);
		
		$form['notice_poisioning_occupier_end']['back_link'] = array(
			'#markup' => l(t('Back'), 'applicant/form20/default/'.$formid.'/'.$referenceid.'/'.$factorytypeid.'/'.$serviceid, array(
				'html' => TRUE,
				'attributes' => array(
					'class' => array('btn btn-outline-dark pull-left')
				)
			))
		);		
	
	  return $form;
  }
	
  /*function get_reg_lic_no($factory_id){ 
		$query_reg_lic 		= db_select('fa_cafa', 'cafa');
		$query_reg_lic		->fields('cafa',array('factory_name','factory_typeid','reference_number','factory_registrstion_no','backlog_registration_no','backlog_registration_date','registration_date','tm_factory_registration_no','backlog_license_number','factory_license_no','backlog_license_date','license_date','classification_no','service_id','nearest_landmark','factory_zone','pincode','state','district','subdivision','areatype','block','panchayat','policestation','postoffice','addrline'));
		$query_reg_lic		->condition('cafa.id',$factory_id,'=');
		$result_reg_lic 	= $query_reg_lic->execute()->fetchAssoc();
		return $result_reg_lic;
	}*/

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
		
		$commands[] = ajax_command_replace('#industry_name_id', drupal_render($form['notice_poisioning']['industry_name'])); 
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
  
 	function form20_occupier_details_submit($form, &$form_state){
		global $base_root,$base_path,$user,$_SESSION;
		
		$uid          = $user->uid;
		$val          = $form_state['values'];//print_r($val);die;
		
		$formid 	      = encryption_decryption_fun('decrypt', $val['formid_hidden']);
		$referenceid      = encryption_decryption_fun('decrypt', $val['referenceid_hidden']);
		$factorytypeid    = encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']);
		$serviceid        = encryption_decryption_fun('decrypt', $val['serviceid_hidden']);
		
		$notice_poisoning_occupier_details = array(	
		  'name_occupier'         		      => $val['name_occupier'],		
		  'pincodeoprmntadr'         		  => $val['pincodeoprmntadr'],
		  'state_oprmntadr'          		  => $val['state_oprmntadr'],
		  'district_oprmntadr'       		  => $val['district_oprmntadr'],
		  'subdivision_oprmntadr'    		  => $val['subdivision_oprmntadr'],
		  'areatype_oprmntadr'       		  => $val['areatype_oprmntadr'],
		  'block_oprmntadr'          		  => $val['block_oprmntadr'],
		  'panchayat_oprmntadr'      		  => $val['panchayat_oprmntadr'],
		  'policestation_oprmntadr'  		  => $val['policestation_oprmntadr'],
		  'postoffice_oprmntadr'    		  => $val['postoffice_oprmntadr'],
		  'addrline_oprmntadr'       		  => $val['addrline_oprmntadr'],
		  'country_oprmntadr'        		  => $val['country_oprmntadr'],
		  'aadhaar_oprmntadr'              	  => $val['user_aadhar_1'].'-'.$val['user_aadhar_2'].'-'.$val['user_aadhar_3'],
		  'passport_oprmntadr'       		  => $val['passport_oprmntadr'],
		  'passport_date_of_issue_oprmntadr'  => $val['passport_date_of_issue_oprmntadr'],
		  'passport_date_of_expiry_oprmntadr' => $val['passport_date_of_expiry_oprmntadr'],
		  'street_name_oprmntadr'             => $val['street_name_oprmntadr'],
		  'house_no_oprmntadr'                => $val['house_no_oprmntadr'],
		  'police_station_oprmntadr'          => $val['police_station_oprmntadr'],
		);			
//print_r($notice_poisoning_occupier_details); die;
		$query_occupier 	=	db_update('fa_form20_notice_poisoning');
		$query_occupier		->	fields($notice_poisoning_occupier_details);
		$query_occupier		->	condition('id',$formid,'=');
		$query_occupier		->	condition('reference_number',$referenceid,'=');
		$query_occupier		->	condition('factory_typeid',$factorytypeid,'=');
		$query_occupier		->	condition('service_id',$serviceid,'=');
		$query_occupier		->	execute();
		
		drupal_goto('applicant/form20/patient-details/'. $val['formid_hidden'].'/'.$val['referenceid_hidden'].'/'.$val['factorytypeid_hidden'].'/'.$val['serviceid_hidden']);
		
		$form_state['rebuild'] = true;
	} 
 
 function get_ajax_load_oprmntadr($form, $form_state)
{
	$commands = array();
	$commands[] = ajax_command_replace('#pincodeoprmntadr_id', drupal_render($form['notice_poisioning_occupier']['pincodeoprmntadr']));
	
	$commands[] = ajax_command_replace('#oprmntadr_edit_emp_state_replace', drupal_render($form['notice_poisioning_occupier']['state_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_edit_emp_district_replace', drupal_render($form['notice_poisioning_occupier']['district_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_empsubdv_replace', drupal_render($form['notice_poisioning_occupier']['subdivision_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_emp_areatype_replace', drupal_render($form['notice_poisioning_occupier']['areatype_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_empareatype_name_replace', drupal_render($form['notice_poisioning_occupier']['block_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_emp_vill_ward_replace', drupal_render($form['notice_poisioning_occupier']['panchayat_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_empps_replace', drupal_render($form['notice_poisioning_occupier']['policestation_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_post_office_div', drupal_render($form['notice_poisioning_occupier']['postoffice_oprmntadr']));
	
	$commands[] = ajax_command_replace('#oprmntadr_user_aadhar_1_div', drupal_render($form['notice_poisioning_occupier']['user_aadhar_1']));
	$commands[] = ajax_command_replace('#oprmntadr_user_aadhar_2_div', drupal_render($form['notice_poisioning_occupier']['user_aadhar_2']));
	$commands[] = ajax_command_replace('#oprmntadr_user_aadhar_3_div', drupal_render($form['notice_poisioning_occupier']['user_aadhar_3']));
	
	$commands[] = ajax_command_replace('#oprmntadr_streetname_div', drupal_render($form['notice_poisioning_occupier']['street_name_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_houseno_div', drupal_render($form['notice_poisioning_occupier']['house_no_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_policestation_div', drupal_render($form['notice_poisioning_occupier']['police_station_oprmntadr']));
	
	$commands[] = ajax_command_replace('#oprmntadr_passport_oprmntadr_div', drupal_render($form['notice_poisioning_occupier']['passport_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_doi_div', drupal_render($form['notice_poisioning_occupier']['passport_date_of_issue_oprmntadr']));
	$commands[] = ajax_command_replace('#oprmntadr_doe_div', drupal_render($form['notice_poisioning_occupier']['passport_date_of_expiry_oprmntadr']));
	
	return array('#type' => 'ajax', '#commands' => $commands);
}
