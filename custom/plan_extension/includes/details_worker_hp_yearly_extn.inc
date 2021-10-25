 <?php
//$applicationid
drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
function details_worker_hp_yearly_extn($form, &$form_state, $serviceid, $factory_type_id,$applicationid,$referenceno)
{
    global $base_root, $base_path, $user;
   
    $factory_typeid     = encryption_decryption_fun('decrypt', $factory_type_id);
    $application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	$service_id 		= encryption_decryption_fun('decrypt', $serviceid);
	$reference_no 		= encryption_decryption_fun('decrypt', $referenceno);
	
	if(empty($application_id) || $application_id==0 || $application_id == ''){
		  drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Occupier Details tab.</h5>'),'alert alert-danger alert-dismissible');
		  drupal_goto('applicant/caf_extn/caf-form-occupier-extension/'.$serviceid.'/'.$factory_type_id.'/'.$applicationid.'/'.$referenceno) ;
	}
	
	$get_fa_cafa 		   = get_fa_cafa($application_id);
    //$reference_no 		   = $get_fa_cafa['reference_number'];
	$plan_approve_status   = $get_fa_cafa['plan_approve_status'];
    $permanent_worker_men  = $permanent_worker_women = $permanent_adolescents_male = $permanent_adolescents_female = $permanent_children_male = $permanent_children_female = '0';
   
    $form                  = array();
    $form['serviceid']     = array(
			'#type'          => 'hidden',
			'#default_value' => $serviceid
		);
    $form['factorytypeid'] = array(
        '#type' 		 => 'hidden',
        '#default_value' => $factory_type_id
    );
	$form['applicationid_hidden']       = array(
        '#type'          => 'hidden',
        '#default_value' => $applicationid
    );
	$form['reference_no_hidden']       = array(
        '#type'          => 'hidden',
        '#default_value' => $referenceno
    );
	$form['plan_approve_status_hidden']       = array(
        '#type'          => 'hidden',
        '#default_value' => encryption_decryption_fun('encrypt', $plan_approve_status)
    );

     if(!empty($application_id)){
			$worker_details = worker_details_reference($application_id,$service_id,$factory_typeid,$reference_no);
			
	 $form['workerdetailsid'] = array(
				 '#type' 	 		=> 'hidden',
				 '#default_value' 	=> encryption_decryption_fun('encrypt',$worker_details['id']),
		);
		
		$permanent_worker_men 			= $worker_details['permanent_worker_men'];
		$permanent_worker_women 		= $worker_details['permanent_worker_women'];
		$permanent_adolescents_male     = $worker_details['permanent_adolescents_male'];
		$permanent_adolescents_female 	= $worker_details['permanent_adolescents_female'];
		$permanent_children_male 	    = $worker_details['permanent_children_male'];
		$permanent_children_female 		= $worker_details['permanent_children_female'];

		$contactual_worker_men 			= $worker_details['contactual_worker_men'];
		$contactual_worker_women 		= $worker_details['contactual_worker_women'];
		$contactual_adolescents_male    = $worker_details['contactual_adolescents_male'];
		$contactual_adolescents_female 	= $worker_details['contactual_adolescents_female'];
		$contactual_children_male 	    = $worker_details['contactual_children_male'];
		$contactual_children_female 	= $worker_details['contactual_children_female'];
	}
	
	/********** Factory checking data **********/
	
	if($plan_approve_status == 'ABk') {
	$checked = get_verified_field($application_id, $reference_no, $plan_approve_status);
	
	$verify_details      = ($checked['verify_details'])? $checked['verify_details'] : ''; 
	$remark_field = explode(',', $checked['verify_details']);
	
		foreach ($remark_field as $fieldname)
		{
			if($fieldname == 'permanent_worker_men'){ $permanent_worker_men_ck = "disabled";}
			if($fieldname == 'permanent_worker_women'){ $permanent_worker_women_ck = "disabled";}
			if($fieldname == 'permanent_adolescents_male'){ $permanent_adolescents_male_ck = "disabled";}
			if($fieldname == 'permanent_adolescents_female'){ $permanent_adolescents_female_ck = "disabled";}
			if($fieldname == 'permanent_children_male'){ $permanent_children_male_ck = "disabled";}
			if($fieldname == 'permanent_children_female'){ $permanent_children_female_ck = "disabled";}

			if($fieldname == 'contactual_worker_men'){ $contactual_worker_men_ck = "disabled";}
			if($fieldname == 'contactual_worker_women'){ $contactual_worker_women_ck = "disabled";}
			if($fieldname == 'contactual_adolescents_male'){ $contactual_adolescents_male_ck = "disabled";}
			if($fieldname == 'contactual_adolescents_female'){ $contactual_adolescents_female_ck = "disabled";}
			if($fieldname == 'contactual_children_male'){ $contactual_children_male_ck = "disabled";}
			if($fieldname == 'contactual_children_female'){ $contactual_children_female_ck = "disabled";}
		}

		if(in_array("permanent_worker_men", $remark_field)) { $permanent_worker_men_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $permanent_worker_men_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("permanent_worker_women", $remark_field)) { $permanent_worker_women_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $permanent_worker_women_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("permanent_adolescents_male", $remark_field)) { $permanent_adolescents_male_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $permanent_adolescents_male_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("permanent_adolescents_female", $remark_field)) { $permanent_adolescents_female_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $permanent_adolescents_female_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("permanent_children_male", $remark_field)) { $permanent_children_male_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $permanent_children_male_check_data = '<i class="fa fa-close text-red verified"></i>'; }
		
        if(in_array("permanent_children_female", $remark_field)) { $permanent_children_female_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $permanent_children_female_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("contactual_worker_men", $remark_field)) { $contactual_worker_men_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $contactual_worker_men_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("contactual_worker_women", $remark_field)) { $contactual_worker_women_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $contactual_worker_women_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("contactual_adolescents_male", $remark_field)) { $contactual_adolescents_male_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $contactual_adolescents_male_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("contactual_adolescents_female", $remark_field)) { $contactual_adolescents_female_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $contactual_adolescents_female_check_data = '<i class="fa fa-close text-red verified"></i>'; }

		if(in_array("contactual_children_male", $remark_field)) { $contactual_children_male_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $contactual_children_male_check_data = '<i class="fa fa-close text-red verified"></i>'; }
		
        if(in_array("contactual_children_female", $remark_field)) { $contactual_children_female_check_data = '<i class="fa fa-check text-green verified"></i>';  }
		else {  $contactual_children_female_check_data = '<i class="fa fa-close text-red verified"></i>'; }
	 }	
	 
	/********** Factory Information - Start **********/

	$form['header'] = array(
				'#markup' 	 => t('<div class="content"><h3>Numbers Of Workers</h3>'),
	);
	
	$form['permanent_yearly_worker'] = array(
		'#type' => 'fieldset',
		'#title' => t('J(i). No.s Of Workers (Permanent)'),
		'#collapsible' => TRUE, // Added
		'#collapsed' => FALSE,  // Added
	);	

	$form['permanent_yearly_worker']['permanent_worker_men'] 	= array(
			  '#prefix' 			=> '<div class="row"><div class="col-md-2 col-xs-12"><label class="input label-block">',
			  '#suffix' 			=> '</label></div>',
			  '#title'				=>	t($permanent_worker_men_check_data.'(i) Men'),
			  '#type' 				=> 'textfield',
			  '#element_validate'	=> array('isnumaric_valiadtion'),
			  '#required' 			=> TRUE,
			  '#default_value'  	=> isset($permanent_worker_men) ? $permanent_worker_men : '0',
			  '#attributes'         => array('class' => array('NoField'),$permanent_worker_men_ck => $permanent_worker_men_ck )
			);
	$form['permanent_yearly_worker']['permanent_worker_women'] 	= array(
			  '#prefix' 			=> '<div class="col-md-2 col-xs-12"><label class="input label-block">',
			  '#suffix' 			=> '</label></div>',
			  '#title'				=>	t($permanent_worker_women_check_data.'(ii) Women'),
			  '#type' 				=> 'textfield',
			  '#element_validate'	=> array('isnumaric_valiadtion'),
			  '#required' 			=> TRUE,
			  '#default_value'  	=> isset($permanent_worker_women) ? $permanent_worker_women : '0',
			  '#attributes'         => array('class' => array('NoField'),$permanent_worker_women_ck => $permanent_worker_women_ck )
			);
	/*$form['permanent_yearly_worker']['sub_header_11'] = array(
				'#markup' 			=> t('<h6><b>Adolescents (over 15 but under 18 years of age)</b></h6>'),
			);*/	
	$form['permanent_yearly_worker']['permanent_adolescents_male'] 	= array(
			  '#prefix' 			=> '<div class="col-md-2 col-xs-12"><label class="input label-block">',
			  '#suffix' 			=> '</label></div>',
			  '#title'				=>	t($permanent_adolescents_male_check_data.'(iii) Adolescents Male'),
			  '#type' 				=> 'textfield',
			  '#element_validate'	=> array('isnumaric_valiadtion'),
			  '#required' 			=> TRUE,
			  '#default_value'  	=> isset($permanent_adolescents_male) ? $permanent_adolescents_male : '0',
			  '#attributes'         => array('class' => array('NoField'),$permanent_adolescents_male_ck => $permanent_adolescents_male_ck )
			);
	$form['permanent_yearly_worker']['permanent_adolescents_female'] 	= array(
			  '#prefix' 			=> '<div class="col-md-2 col-xs-12"><label class="input label-block">',
			  '#suffix' 			=> '</label></div>',
			  '#title'				=>	t($permanent_adolescents_female_check_data.'(iv) Adolescent Male'),
			  '#type' 				=> 'textfield',
			  '#element_validate'	=> array('isnumaric_valiadtion'),
			  '#required' 			=> TRUE,
			  '#default_value'  	=> isset($permanent_adolescents_female) ? $permanent_adolescents_female : '0',
			  '#attributes'         => array('class' => array('NoField'),$permanent_adolescents_female_ck => $permanent_adolescents_female_ck )
			);
	/*$form['permanent_yearly_worker']['sub_header_12'] = array(
				'#markup' 			=> t('<h6><b>Children (over 14 but under 15 years of age)</b></h6>'),
			)*/;	
	$form['permanent_yearly_worker']['permanent_children_male'] 	= array(
			  '#prefix' 			=> '<div class="col-md-2 col-xs-12"><label class="input label-block">',
			  '#suffix' 			=> '</label></div>',
			  '#title'				=>	t($permanent_children_male_check_data.'(v) Children Male'),
			  '#type' 				=> 'textfield',
			  '#element_validate'	=> array('isnumaric_valiadtion'),
			  '#required' 			=> TRUE,
			  '#default_value'  	=> isset($permanent_children_male) ? $permanent_children_male : '0',
			  '#attributes'         => array('class' => array('NoField'),$permanent_children_male_ck => $permanent_children_male_ck )
			);
	$form['permanent_yearly_worker']['permanent_children_female'] 	= array(
			  '#prefix' 			=> '<div class="col-md-2 col-xs-12"><label class="input label-block">',
			  '#suffix' 			=> '</label></div></div>',
			  '#title'				=>	t($permanent_children_female_check_data.'(vi) Children Female'),
			  '#type' 				=> 'textfield',
			  '#element_validate'	=> array('isnumaric_valiadtion'),
			  '#required' 			=> TRUE,
		      '#default_value'  	=> isset($permanent_children_female) ? $permanent_children_female : '0',
			  '#attributes'         => array('class' => array('NoField'),$permanent_children_female_ck => $permanent_children_female_ck )
			);	
	$form['permanent_yearly_worker']['worker_error'] = array(
		  
		   '#prefix' => '<div class="row"><div id="ajax_error_replace_div" class="col-md-12 col-xs-12">',
		   '#suffix' => '</div></div>'	
		);
		
	// TEMPORARY WORKERS
	
	$form['contactual_yearly_worker'] = array(
		'#type' => 'fieldset',
		'#title' => t('J(ii). No.s Of Workers (Contractual)'),
		'#collapsible' => TRUE, // Added
		'#collapsed' => FALSE,  // Added
	);	

	$form['contactual_yearly_worker']['contactual_worker_men'] 	= array(
			  '#prefix' 			=> '<div class="row"><div class="col-md-2 col-xs-12"><label class="input label-block">',
			  '#suffix' 			=> '</label></div>',
			  '#title'				=>	t($contactual_worker_men_check_data.'(i) Men'),
			  '#type' 				=> 'textfield',
			  '#element_validate'	=> array('isnumaric_valiadtion'),
			  '#required' 			=> TRUE,
			  '#default_value'  	=> isset($contactual_worker_men) ? $contactual_worker_men : '0',
			  '#attributes'         => array('class' => array('NoField'),$contactual_worker_men_ck => $contactual_worker_men_ck )
			);
	$form['contactual_yearly_worker']['contactual_worker_women'] 	= array(
			  '#prefix' 			=> '<div class="col-md-2 col-xs-12"><label class="input label-block">',
			  '#suffix' 			=> '</label></div>',
			  '#title'				=>	t($contactual_worker_women_check_data.'(ii) Women'),
			  '#type' 				=> 'textfield',
			  '#element_validate'	=> array('isnumaric_valiadtion'),
			  '#required' 			=> TRUE,
			  '#default_value'  	=> isset($contactual_worker_women) ? $contactual_worker_women : '0',
			  '#attributes'         => array('class' => array('NoField'),$contactual_worker_women_ck => $contactual_worker_women_ck )
			);
	/*$form['contactual_yearly_worker']['sub_header_11'] = array(
				'#markup' 			=> t('<h6><b>Adolescents (over 15 but under 18 years of age)</b></h6>'),
			);*/	
	$form['contactual_yearly_worker']['contactual_adolescents_male'] 	= array(
			  '#prefix' 			=> '<div class="col-md-2 col-xs-12"><label class="input label-block">',
			  '#suffix' 			=> '</label></div>',
			  '#title'				=>	t($contactual_adolescents_male_check_data.'(iii) Adolescents Male'),
			  '#type' 				=> 'textfield',
			  '#element_validate'	=> array('isnumaric_valiadtion'),
			  '#required' 			=> TRUE,
			  '#default_value'  	=> isset($contactual_adolescents_male) ? $contactual_adolescents_male : '0',
			  '#attributes'         => array('class' => array( ''),$contactual_adolescents_male_ck => $contactual_adolescents_male_ck )
			);
	$form['contactual_yearly_worker']['contactual_adolescents_female'] 	= array(
			  '#prefix' 			=> '<div class="col-md-2 col-xs-12"><label class="input label-block">',
			  '#suffix' 			=> '</label></div>',
			  '#title'				=>	t($contactual_adolescents_female_check_data.'(iv) Adolescent Male'),
			  '#type' 				=> 'textfield',
			  '#element_validate'	=> array('isnumaric_valiadtion'),
			  '#required' 			=> TRUE,
			  '#default_value'  	=> isset($contactual_adolescents_female) ? $contactual_adolescents_female : '0',
			  '#attributes'         => array('class' => array('NoField'),$contactual_adolescents_female_ck => $contactual_adolescents_female_ck )
			);
	/*$form['contactual_yearly_worker']['sub_header_12'] = array(
				'#markup' 			=> t('<h6><b>Children (over 14 but under 15 years of age)</b></h6>'),
			);*/	
	$form['contactual_yearly_worker']['contactual_children_male'] 	= array(
			  '#prefix' 			=> '<div class="col-md-2 col-xs-12"><label class="input label-block">',
			  '#suffix' 			=> '</label></div>',
			  '#title'				=>	t($contactual_children_male_check_data.'(v) Children Male'),
			  '#type' 				=> 'textfield',
			  '#element_validate'	=> array('isnumaric_valiadtion'),
			  '#required' 			=> TRUE,
			  '#default_value'  	=> isset($contactual_children_male) ? $contactual_children_male : '0',
			  '#attributes'         => array('class' => array('NoField'),$contactual_children_male_ck => $contactual_children_male_ck )
			);
	$form['contactual_yearly_worker']['contactual_children_female'] 	= array(
			  '#prefix' 			=> '<div class="col-md-2 col-xs-12"><label class="input label-block">',
			  '#suffix' 			=> '</label></div></div>',
			  '#title'				=>	t($contactual_children_female_check_data.'(vi) Children Female'),
			  '#type' 				=> 'textfield',
			  '#element_validate'	=> array('isnumaric_valiadtion'),
			  '#required' 			=> TRUE,
		      '#default_value'  	=> isset($contactual_children_female) ? $contactual_children_female : '0',
			  '#attributes'         => array('class' => array('NoField'),$contactual_children_female_ck => $contactual_children_female_ck )
			);	
	$form['contactual_yearly_worker']['worker_error'] = array(
		  
		   '#prefix' => '<div class="row"><div id="ajax_error_replace_div" class="col-md-12 col-xs-12">',
		   '#suffix' => '</div></div>'	
		);
	
	if($plan_approve_status != 'F'){
		
		$form['back_link'] = array(
			
			'#markup' => l(t('<i class="fa fa-fw fa-chevron-left"></i> Back'), 'applicant/caf_extn/caf-form-occupier-extension/'.$serviceid.'/'.$factory_type_id.'/'.$applicationid.'/'.$referenceno, array(
				'html' => TRUE,
				'attributes' => array(
					'class' => array('btn btn-dark pull-left')
				)
			))
		);
		$form['submit'] = array (
		  '#prefix' 	=> '</div><div>',  
		  '#suffix' 	=> '</div>',
		  '#attributes' => array(
            'class' => array(
                'btn btn-success pull-right'
            )
        ),
		  '#type' 		=> 'submit',
		  '#value' 		=> 'Save'
		);
		
		$form['pdf_link'] = array(
				'#markup' => l(t('Print Draft Copy'), 'download-pdf-worker-as-draft/'.$applicationid.'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.$serviceid.'/'.$factory_type_id, array(
					'html' => TRUE,
					'attributes' => array(
						'class' => array('btn btn-warning pull-left '), 'style'=> 'margin-left: 10px'
					)
				))
			);
	
	}
 
     return $form; 
}
		 
function details_worker_hp_yearly_extn_validate($form, &$form_state) {

  $permanent_worker_men = $form_state['values']['permanent_worker_men'];
	if (isset($form_state['values']['permanent_worker_men']) && !preg_match('/^([1-9][0-9]*)|([0])$/', $permanent_worker_men)) {  
    form_set_error('permanent_worker_men', t('Please enter proper number of men!!'));
  }
  $permanent_worker_women = $form_state['values']['permanent_worker_women'];
	if (isset($form_state['values']['permanent_worker_women']) && !preg_match('/^([1-9][0-9]*)|([0])$/', $permanent_worker_women)) {  
    form_set_error('permanent_worker_women', t('Please enter proper number of women!!'));
  }
  $permanent_adolescents_male = $form_state['values']['permanent_adolescents_male'];
	if (isset($form_state['values']['permanent_adolescents_male']) && !preg_match('/^([1-9][0-9]*)|([0])$/', $permanent_adolescents_male)) {  
    form_set_error('permanent_adolescents_male', t('Please enter proper number of adolescents male!!'));
  }
  $permanent_adolescents_female = $form_state['values']['permanent_adolescents_female'];
	if (isset($form_state['values']['permanent_adolescents_female']) && !preg_match('/^([1-9][0-9]*)|([0])$/', $permanent_adolescents_female)) {  
    form_set_error('permanent_adolescents_female', t('Please enter proper number of Adolescent Male!!'));
  }
  $permanent_children_male = $form_state['values']['permanent_children_male'];
	if (isset($form_state['values']['permanent_children_male']) && !preg_match('/^([1-9][0-9]*)|([0])$/', $permanent_children_male)) {  
    form_set_error('permanent_children_male', t('Please enter proper number of children male!!'));
  }
  $permanent_children_female = $form_state['values']['permanent_children_female'];
	if (isset($form_state['values']['permanent_children_female']) && !preg_match('/^([1-9][0-9]*)|([0])$/', $permanent_children_female)) {  
    form_set_error('permanent_children_female', t('Please enter proper number of children female!!'));
  }
  
  $contactual_worker_men = $form_state['values']['contactual_worker_men'];
	if (isset($form_state['values']['contactual_worker_men']) && !preg_match('/^([1-9][0-9]*)|([0])$/', $contactual_worker_men)) {  
    form_set_error('contactual_worker_men', t('Please enter proper number of men!!'));
  }
  $contactual_worker_women = $form_state['values']['contactual_worker_women'];
	if (isset($form_state['values']['contactual_worker_women']) && !preg_match('/^([1-9][0-9]*)|([0])$/', $contactual_worker_women)) {  
    form_set_error('contactual_worker_women', t('Please enter proper number of women!!'));
  }
  $contactual_adolescents_male = $form_state['values']['contactual_adolescents_male'];
	if (isset($form_state['values']['contactual_adolescents_male']) && !preg_match('/^([1-9][0-9]*)|([0])$/', $contactual_adolescents_male)) {  
    form_set_error('contactual_adolescents_male', t('Please enter proper number of adolescents male!!'));
  }
  $contactual_adolescents_female = $form_state['values']['contactual_adolescents_female'];
	if (isset($form_state['values']['contactual_adolescents_female']) && !preg_match('/^([1-9][0-9]*)|([0])$/', $contactual_adolescents_female)) {  
    form_set_error('contactual_adolescents_female', t('Please enter proper number of Adolescent Male!!'));
  }
  $contactual_children_male = $form_state['values']['contactual_children_male'];
	if (isset($form_state['values']['contactual_children_male']) && !preg_match('/^([1-9][0-9]*)|([0])$/', $contactual_children_male)) {  
    form_set_error('contactual_children_male', t('Please enter proper number of children male!!'));
  }
  $contactual_children_female = $form_state['values']['contactual_children_female'];
	if (isset($form_state['values']['contactual_children_female']) && !preg_match('/^([1-9][0-9]*)|([0])$/', $contactual_children_female)) {  
    form_set_error('contactual_children_female', t('Please enter proper number of children female!!'));
  }
}

function details_worker_hp_yearly_extn_submit($form, &$form_state){
	
	 global $user;
	 $val   						= $form_state['values'];
	 $uid 			    			= $user->uid;
	 $commands   					= array();
	$permanent_worker_men 		    = $val['permanent_worker_men']; 
	$permanent_worker_women 		= $val['permanent_worker_women'];
	$permanent_adolescents_male     = $val['permanent_adolescents_male'];
	$permanent_adolescents_female 	= $val['permanent_adolescents_female'];
	$permanent_children_male 	    = $val['permanent_children_male'];
	$permanent_children_female      = $val['permanent_children_female'];

	$contactual_worker_men 		    = $val['contactual_worker_men']; 
	$contactual_worker_women 		= $val['contactual_worker_women'];
	$contactual_adolescents_male    = $val['contactual_adolescents_male'];
	$contactual_adolescents_female 	= $val['contactual_adolescents_female'];
	$contactual_children_male 	    = $val['contactual_children_male'];
	$contactual_children_female     = $val['contactual_children_female'];

	$worker_total					= $permanent_worker_men+$permanent_worker_women+$permanent_adolescents_male+$permanent_adolescents_female+$permanent_children_male+$permanent_children_female+$contactual_worker_men+$contactual_worker_women+$contactual_adolescents_male+$contactual_adolescents_female+$contactual_children_male+$contactual_children_female;
			
	$service_id						= encryption_decryption_fun('decrypt',$val['serviceid']);
	$service_year					= $val['service_year'];
	$factory_type_id				= encryption_decryption_fun('decrypt',$val['factorytypeid']);
	$application_id 				= encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$workerdetails_id				= encryption_decryption_fun('decrypt',$val['workerdetailsid']);
	$application_reference_no		= encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	$plan_approve_status 			= encryption_decryption_fun('decrypt',$val['plan_approve_status_hidden']);
	
	//*******----------------start For plan approval-----------------------------------------------------
	
		
		if((filter_var($permanent_worker_men, FILTER_VALIDATE_INT)== true || ($permanent_worker_men == '0')) && (filter_var($permanent_worker_women, FILTER_VALIDATE_INT)== true || ($permanent_worker_women == '0')) && (filter_var($permanent_adolescents_male, FILTER_VALIDATE_INT)== true || ($permanent_adolescents_male == '0')) && (filter_var($permanent_adolescents_female, FILTER_VALIDATE_INT)==true || ($permanent_adolescents_female == '0')) && (filter_var($permanent_children_male, FILTER_VALIDATE_INT)== true || ($permanent_children_male == '0')) &&  (filter_var($permanent_children_female, FILTER_VALIDATE_INT)== true || ($permanent_children_female == '0')) && (filter_var($contactual_worker_men, FILTER_VALIDATE_INT)== true || ($contactual_worker_men == '0')) && (filter_var($contactual_worker_women, FILTER_VALIDATE_INT)== true || ($contactual_worker_women == '0')) && (filter_var($contactual_adolescents_male, FILTER_VALIDATE_INT)== true || ($contactual_adolescents_male == '0')) && (filter_var($contactual_adolescents_female, FILTER_VALIDATE_INT)==true || ($contactual_adolescents_female == '0')) && (filter_var($contactual_children_male, FILTER_VALIDATE_INT)== true || ($contactual_children_male == '0')) &&  (filter_var($contactual_children_female, FILTER_VALIDATE_INT)== true || ($contactual_children_female == '0'))){


	if(($factory_type_id == 1 && $worker_total>9) ||($factory_type_id == 2 && $worker_total>19))
	{
		if($plan_approve_status == 'ABk') { $planstatus = 'ABk';}
		else { $planstatus = 'In';}

		$worker_details_yearly = array(
			'permanent_worker_men' 		     => $permanent_worker_men,
			'permanent_worker_women' 		 => $permanent_worker_women,
			'permanent_adolescents_male'     => $permanent_adolescents_male,
			'permanent_adolescents_female' 	 => $permanent_adolescents_female,
			'permanent_children_male'        => $permanent_children_male,
			'permanent_children_female' 	 => $permanent_children_female,
			'contactual_worker_men' 		 => $contactual_worker_men,
			'contactual_worker_women' 		 => $contactual_worker_women,
			'contactual_adolescents_male'    => $contactual_adolescents_male,
			'contactual_adolescents_female'  => $contactual_adolescents_female,
			'contactual_children_male'       => $contactual_children_male,
			'contactual_children_female' 	 => $contactual_children_female,
			'worker_total'				     => $worker_total,
			'service_id'				     => $service_id,
			'service_year'				     => date("Y"),
			'factory_type'				     => $factory_type_id,
			'created_by'				     => $uid,
			'application_id'			     => $application_id,
			'worker_plan_approval_status'    => $planstatus,
			'application_reference_no'   	 => $application_reference_no
		);
//print_r($worker_details_yearly); die;
			if(empty($workerdetails_id)){	
					
				$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
					if($id){
						drupal_set_message('Worker Details has been saved successfully.');
					drupal_goto('applicant/caf_extn/cafb-extension/'.$val['serviceid'].'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.$val['applicationid_hidden'].'/'.$val['reference_no_hidden']) ;
					}
			}else{
				$queryabc 		 =	db_update('fa_worker_details');
				$queryabc		->	fields($worker_details_yearly);
				$queryabc		->	condition('id',$workerdetails_id,'=');
				$queryabc		->	execute();
				drupal_set_message('Worker Details has been saved successfully.');
			drupal_goto('applicant/caf_extn/cafb-extension/'.$val['serviceid'].'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.$val['applicationid_hidden'].'/'.$val['reference_no_hidden']) ;
			}

	}else{
		if ($factory_type_id == 1){
			$factory_type = "Your factory is 2m(i) type category. So workers shoud be more than 9 workres with aid power ";
			
		}else if ($factory_type_id == 2){
			$factory_type = "Your factory is 2m(iI) type category. So workers shoud be more than 19 workres";
			
		}
		drupal_set_message($factory_type,'error');
		}
	}		
	else{
	
		drupal_set_message("All feilds under workers details shoud be integer",'error');
	}
	$form_state['rebuild']= true;
	
	//-----------****************end plan aproval-------------------------------------	
	
}
?>