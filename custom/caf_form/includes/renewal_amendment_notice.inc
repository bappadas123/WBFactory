<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function renewal_amendment_notice($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$number){

	global $base_root, $base_path;
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	
	//die('Service--'.$service_id.'factory--'.$factory_type_id.'Application--'.$application_id);
	$get_fa_cafa 					= get_fa_cafa($application_id);
	$reference_number 				= $get_fa_cafa['reference_number'];
	$value_factory_profile_type		= $get_fa_cafa['ownership_type'];
	$license_valid_upto				= $get_fa_cafa['license_valid_upto'];
	$date_of_renewal				= $get_fa_cafa['date_of_renewal'];
	$is_year_calculation_tab		= $get_fa_cafa['is_year_calculation_tab'];
	
	
	$form = array();
	$form['serviceid_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $serviceid,
	);
	$form['factorytypeid_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $factory_typeid	 
	);
	$form['reference_no_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> encryption_decryption_fun('encrypt', $reference_number) 
	);
	$form['applicationid_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $applicationid
	); 
	$form['amend_worker'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('Amended Notice of Workers and Installed Power'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	
	
	$period= fetch_amand_year($application_id,$service_id,$factory_type_id,$reference_number);
	//print_r($period);die;

	$power_worker = array('1'=>'Worker','2'=>'Power','3'=>'Both');	
	
	$form['amend_worker']['amend_power_worker'] 	= array(
		'#prefix' 			=> '<div class="row"><div class="col-md-6 div class="col-xs-12">',
		'#suffix' 	 		=> '</div></div>',
		'#type' 			=> 'radios',
		'#title'			=>	t('Do you amend in worker or install power'),
		'#required' 		=> TRUE,
		'#options'			=> $power_worker,
		'#ajax' 			=> array(
				'effect' 	=> 'fade',
				'callback' 	=> 'get_ajax_load_worker',
				'progress' 	=> array(
					'type' 		=> 'throbber',
					'message' 	=> t('loading')
				)
			)
	);
	
	$form['amend_worker']['license_period']= array(
		'#prefix' 			=> '<div class="row"><div class="col-md-4 div class="col-xs-12">',
		'#suffix' 	 		=> '</div></div><div class="row">',
		'#type' 			=> 'select',
		'#title'			=>	t('License Period'),
		'#required' 		=> TRUE,
		'#options'			=> $period,
		'#attributes' 		=> array('class'=>array('form-control')),
	);
	
	$value_power_worker 	= 	isset($form_state['values']['amend_power_worker']) ? $form_state['values']['amend_power_worker'] : '';
	
	$form['amend_worker']['previous_table'] 	= array(
		'#prefix' => '<div id="worker_table_id">',
		'#suffix' => '</div>'
	);
	$form['amend_worker']['per_worker_men'] = array(
		'#prefix'	=> '<div id="id_per_worker_men">',
		'#suffix' 	 => '</div>',
	);
	$form['amend_worker']['per_worker_women'] = array(
		'#prefix'	=> '<div id="id_per_worker_women">',
		'#suffix' 	 => '</div>',
	);
	$form['amend_worker']['per_worker_adol_men'] = array(
		'#prefix'	=> '<div id="id_per_worker_adol_men">',
		'#suffix' 	 => '</div>',
	);
	$form['amend_worker']['per_worker_adol_women'] = array(
		'#prefix'	=> '<span id="id_per_worker_adol_women">',
		'#suffix' 	 => '</span>',
	);
	$form['amend_worker']['per_worker_child_men'] = array(
		'#prefix'	=> '<div id="id_per_worker_child_men">',
		'#suffix' 	 => '</div>',
	);
	$form['amend_worker']['per_worker_child_women'] = array(
		'#prefix'	=> '<div id="id_per_worker_child_women">',
		'#suffix' 	 => '</div>',
	);
	$form['amend_worker']['con_worker_men'] = array(
		'#prefix'	=> '<div id="id_con_worker_men">',
		'#suffix' 	 => '</div>',
	);
	$form['amend_worker']['con_worker_women'] = array(
		'#prefix'	=> '<div id="id_con_worker_women">',
		'#suffix' 	 => '</div>',
	);
	$form['amend_worker']['con_worker_adol_men'] = array(
		'#prefix'	=> '<div id="id_con_worker_adol_men">',
		'#suffix' 	=> '</div>',
	);
	$form['amend_worker']['con_worker_adol_women'] = array(
		'#prefix'	=> '<div id="id_con_worker_adol_women">',
		'#suffix' 	 => '</div>',
	);
	
	$form['amend_worker']['con_worker_child_men'] = array(
		'#prefix'	=> '<div id="id_con_worker_child_men">',
		'#suffix' 	=> '</div>',
	);
	$form['amend_worker']['con_worker_child_woman'] = array(
		'#prefix'	=> '<div id="id_con_worker_child_woman">',
		'#suffix' 	=> '</div>',
	);
	$form['amend_worker']['amend_total_worker'] = array(
		'#prefix' 	=> '<div id="id_amend_total_worker">',
		'#suffix' 	=> '</div>',
	);
	 $form['amend_worker']['previous_table_end'] 	= array(
		'#prefix'	=> '<div id="worker_end_table_id">',
		'#suffix' 	=> '</div>',
	);
	$form['amend_worker']['previous_total_worker'] = array(
		'#prefix' 	=> '<div id="id_previous_worker">',
		'#suffix'	=> '</div>',
	);
		
	$form['amend_worker']['is_generating']= array(
		'#prefix' 	=> '<div id="id_is_generating">',
		'#suffix'   => '</div>',
	);
	$form['amend_worker']['power_type'] 	= array(
		'#prefix' 	=> '<div id="id_power_type">',
		'#suffix' 	=> '</div>',
	);	
	
	$form['amend_worker']['installed_power'] 	= array(
		'#prefix' 	=> '<div id="id_installed_power">',
		'#suffix' 	=> '</div>',
	);	
	$form['amend_worker']['previous_installed_unit'] 	= array(
		'#prefix' 	=> '<div id="id_previous_installed_unit">',
		'#suffix' 	=> '</div>',
	);
	$form['amend_worker']['previous_installed_power'] 	= array(
		'#prefix' 	=> '<div id="id_previous_installed_power">',
		'#suffix' 	=> '</div>',
	);

	if($value_power_worker == 1){
		$form['amend_worker']['previous_table'] 	= array(
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12" id="worker_table_id">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th  colspan="6">Permanent</th>
								<th  colspan="6">Contactual</th>
								<th width="12%">Previous Total workers<br/>(According to license)</th>
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
        						<th colspan="2" rowspan="2">&nbsp;</th>
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

	
	$form['amend_worker']['per_worker_men'] = array(
				'#prefix' 			=> '<td><div class="col-xs-12" id="id_per_worker_men">',
			  	'#suffix' 	 		=> '</div></td>',
			  	//'#title'			=>	t('Men'),
			  	'#type' 			=> 'textfield',
			 	'#default_value'	=> $permanent_worker_men, 
			  	//'#attributes' 		=> array('class'=>array('form-control')),
			  	'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  	'#required' 		=> TRUE,
				'#size' 			=> 3,
			);
  $form['amend_worker']['per_worker_women'] = array(
				 '#prefix' 				=> '<td><div class="col-xs-12" id="id_per_worker_women">',
				 '#suffix' 	 			=> '</div></td>',
				 //'#title'				=>	t('Women'),
				 '#type' 				=> 'textfield',
				 '#default_value'		=> $permanent_worker_women, 
				 //'#attributes' 			=> array('class'=>array('form-control')),
				 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				 '#required' 			=> TRUE,
				 '#size' 				=> 3,
			);
  $form['amend_worker']['per_worker_adol_men'] = array(
			  '#prefix' 			=> '<td ><div class="col-xs-12" id="id_per_worker_adol_men">',
			  '#suffix' 	 		=> '</div></td>',
			 // '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $permanent_adolescents_male, 
			  //'#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#size' 			=> 3,
		);
  
  $form['amend_worker']['per_worker_adol_women'] = array(
			  '#prefix' 			=> '<td ><div class="col-xs-12" id="id_per_worker_adol_women">',
			  '#suffix' 	 		=> '</div></td>',
			  //'#title'				=>	t('Women'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $permanent_adolescents_female, 
			  //'#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#size' 			=> 3,
			);
  $form['amend_worker']['per_worker_child_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12" id="id_per_worker_child_men">',
			  '#suffix' 	 		=> '</div></td>',
			 // '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $permanent_children_male, 
			  //'#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#size' 			=> 3,
			);
  $form['amend_worker']['per_worker_child_women'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12" id="id_per_worker_child_women">',
			  '#suffix' 	 		=> '</div></td>',
			 // '#title'				=>	t('Women'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $permanent_children_female, 
			 // '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#size' 			=> 3,
			);
  $form['amend_worker']['con_worker_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12" id="id_con_worker_men">',
			  '#suffix' 	 		=> '</div></td>',
			 // '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $contactual_worker_men, 
			 // '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#size' 			=> 3,
			);
  $form['amend_worker']['con_worker_women'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12" id="id_con_worker_women">',
			  '#suffix' 	 		=> '</div></td>',
			  //'#title'				=>	t('Women'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $contactual_worker_women, 
			  //'#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#size' 			=> 3,
			);
  $form['amend_worker']['con_worker_adol_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12" id="id_con_worker_adol_men">',
			  '#suffix' 	 		=> '</div></td>',
			 // '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $contactual_adolescents_male, 
			  //'#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#size' 			=> 3,
		);
  $form['amend_worker']['con_worker_adol_women'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12" id="id_con_worker_adol_women">',
				  '#suffix' 	 		=> '</div></td>',
				//  '#title'				=>	t('Women'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> $contactual_adolescents_female, 
				 // '#attributes' 		=> array('class'=>array('form-control')),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				  '#size' 			=> 3,
			);
  $form['amend_worker']['con_worker_child_men'] = array(
			 '#prefix' 				=> '<td><div class="col-xs-12" id="id_con_worker_child_men">',
			  '#suffix' 	 		=> '</div></td>',
			 // '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $contactual_children_male, 
			 // '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#size' 			=> 3,
		);
	
  $form['amend_worker']['con_worker_child_woman'] = array(
			 '#prefix' 				=> '<td><div class="col-xs-12" id="id_con_worker_child_woman">',
			  '#suffix' 	 		=> '</div></td>',
			  //'#title'				=>	t('Women'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $contactual_children_female, 
			  //'#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#size' 			=> 3,
			);
			
	$form['amend_worker']['amend_total_worker'] = array(
			 '#prefix' 				=> '<td><div class="col-xs-12" id="id_amend_total_worker">',
			  '#suffix' 	 		=> '</div></td></tr>',
			  '#title'				=>	t('Total Workers'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> '', 
			  //'#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#size' 				=> 3,
	);
  	$form['amend_worker']['previous_table_end'] 	= array(
		'#prefix'	=> '<div id="worker_end_table_id">',
  		'#suffix'	=> '</table></br></div>',
  		'#type'		=> 'markup',
		'#markup' => '<font color="#FF0000">N.B. Adolescents (over 15 but under 18 years of age) & Children (over 14 but under 15 years of age)</font>',	
		);
		$radios_options = array('power_generating_station'=>"Power generating station",'other'=>"Other");	
		$form['amend_worker']['is_generating']= array(
					 '#prefix' 			=> '<div class="col-md-12 col-xs-4" id="id_is_generating">',
					 '#suffix'    		=> '</div>',
					 '#type'		 	=> 'radios',
					 '#title'			=>	t('Type of power generating station'),
					 '#options'   		=> $radios_options,	
					 '#default_value' 	=> $type_power_station,
					 '#required'		=> TRUE,
		);
		$form['amend_worker']['previous_installed_unit'] 	= array(
					 '#prefix' 				=> '<div class="col-md-3 col-xs-3" id="id_previous_installed_unit">',
					 '#suffix' 				=> '</div>',
					  '#title'				=>	t('Previous Unit of power'),
					 '#type' 		 		=> 'select',
					 '#default_value' 		=>  $power_unit,
					 '#options'	 			=>  array('HP'=>'HP','KW'=>'KW'),
					 '#attributes' 			=>  array('class'=>array('form-control')),
					 '#required' 			=>  TRUE,
	
		);
		$form['amend_worker']['previous_installed_power'] 	= array(
					 '#prefix' 				=> '<div class="col-md-4 col-xs-4" id="id_previous_installed_power">',
					 '#suffix' 				=> '</div>',
					  '#title'				=>	t('Previous Installed Power'),
					  '#type' 				=> 'textfield',
					  '#element_validate'	=>  array('DOUBLE_FIELD_VALIDATION'),
					  '#default_value' 		=>  $installed_power,
					  '#attributes' 		=>  array('class'=>array('form-control')),
					  '#required' 			=>  TRUE,
	
		);
	
	}	

	$form['amend_worker']['end_worker_table'] 	= array(
		'#suffix' 	=> '</div>',
	);
	
	
	$form['amend_worker']['start_total_table'] 	= array(
		'#prefix' 	=> '<div class="row">',
	);
	if($value_power_worker==2){
		$form['amend_worker']['previous_total_worker'] = array(
			  '#prefix' 			=> '<div class="col-xs-4" id="id_previous_worker">',
			  '#suffix' 	 		=> '</div>',
			  '#title'				=>	t('Total Worker'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> '', 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#description'		=> '<span style="color:red;">(During the licence period)</span>'
		);
		
	}
	$form['amend_worker']['end_total_table'] 	= array(
		'#suffix' 	=> '</div>',
	);

	
	$form['amend_worker']['start_power_table'] 	= array(
		'#prefix' 	=> '<div class="row"> ',
	);
	if($value_power_worker==2){	
		$radios_options = array('power_generating_station'=>"Power generating station",'other'=>"Other");	
		$form['amend_worker']['is_generating']= array(
					 '#prefix' 			=> '<div class="col-md-12 col-xs-12" id="id_is_generating">',
					 '#suffix'    		=> '</div>',
					 '#type'		 	=> 'radios',
					 '#title'			=>	t('Type of power generating station'),
					 '#options'   		=> $radios_options,	
					 '#default_value' 	=> $type_power_station,
					 '#required'		=> TRUE,
		);
		$form['amend_worker']['power_type'] 	= array(
					 '#prefix' 				=> '<div class="col-md-3 col-xs-3" id="id_power_type">',
					 '#suffix' 				=> '</div>',
					 '#title'				=>	t('Unit of power'),
					 '#type' 		 		=> 'select',
					 '#default_value' 		=>  $power_unit,
					 '#options'	 			=>  array('HP'=>'HP','KW'=>'KW'),
					 '#attributes' 			=>  array('class'=>array('form-control')),
					 '#required' 			=>  TRUE,
		);
		$form['amend_worker']['installed_power'] 	= array(
					 '#prefix' 				=> '<div class="col-md-3 col-xs-3" id="id_installed_power">',
					 '#suffix' 				=> '</div>',
					  '#title'				=>	t('Amended Power'),
					  '#type' 				=> 'textfield',
					  '#element_validate'	=>  array('DOUBLE_FIELD_VALIDATION'),
					  '#default_value' 		=>  $installed_power,
					  '#attributes' 		=>  array('class'=>array('form-control')),
					  '#required' 			=>  TRUE,
	
		);		
		$form['amend_worker']['previous_installed_unit'] 	= array(
					 '#prefix' 				=> '<div class="col-md-3 col-xs-3" id="id_previous_installed_unit">',
					 '#suffix' 				=> '</div>',
					  '#title'				=>	t('Previous Unit of power'),
					 '#type' 		 		=> 'select',
					 '#default_value' 		=>  $power_unit,
					 '#options'	 			=>  array('HP'=>'HP','KW'=>'KW'),
					 '#attributes' 			=>  array('class'=>array('form-control')),
					 '#required' 			=>  TRUE,
	
		);
		$form['amend_worker']['previous_installed_power'] 	= array(
					 '#prefix' 				=> '<div class="col-md-3 col-xs-3" id="id_previous_installed_power">',
					 '#suffix' 				=> '</div>',
					  '#title'				=>	t('Previous Installed Power'),
					  '#type' 				=> 'textfield',
					  '#element_validate'	=>  array('DOUBLE_FIELD_VALIDATION'),
					  '#default_value' 		=>  $installed_power,
					  '#attributes' 		=>  array('class'=>array('form-control')),
					  '#required' 			=>  TRUE,
	
		);

	}

	$form['amend_worker']['end_power_table'] 	= array(
		'#suffix' 	=> '</div>',
	);
	
	if($value_power_worker==3){
	$form['amend_worker']['previous_table'] 	= array(
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12" id="worker_table_id">
							<table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
							<tr>							
								<th  colspan="6">Permanent</th>
								<th  colspan="6">Contactual</th>
								<th width="12%">Previous Total workers<br/>(According to license)</th>
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
        						<th colspan="2" rowspan="2">&nbsp;</th>
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

	
	$form['amend_worker']['per_worker_men'] = array(
				'#prefix' 			=> '<td><div class="col-xs-12" id="id_per_worker_men">',
			  	'#suffix' 	 		=> '</div></td>',
			  	//'#title'			=>	t('Men'),
			  	'#type' 			=> 'textfield',
			 	'#default_value'	=> $permanent_worker_men, 
			  	//'#attributes' 		=> array('class'=>array('form-control')),
			  	'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  	'#required' 		=> TRUE,
				'#size' 			=> 3,
			);
  	$form['amend_worker']['per_worker_women'] = array(
				 '#prefix' 				=> '<td><div class="col-xs-12" id="id_per_worker_women">',
				 '#suffix' 	 			=> '</div></td>',
				 //'#title'				=>	t('Women'),
				 '#type' 				=> 'textfield',
				 '#default_value'		=> $permanent_worker_women, 
				 //'#attributes' 			=> array('class'=>array('form-control')),
				 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				 '#required' 			=> TRUE,
				 '#size' 				=> 3,
			);
  	$form['amend_worker']['per_worker_adol_men'] = array(
			  '#prefix' 			=> '<td ><div class="col-xs-12" id="id_per_worker_adol_men">',
			  '#suffix' 	 		=> '</div></td>',
			 // '#title'			=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $permanent_adolescents_male, 
			  //'#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#size' 				=> 3,
		);
  
  	$form['amend_worker']['per_worker_adol_women'] = array(
			  '#prefix' 			=> '<td ><div class="col-xs-12" id="id_per_worker_adol_women">',
			  '#suffix' 	 		=> '</div></td>',
			  //'#title'			=>	t('Women'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $permanent_adolescents_female, 
			  //'#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#size' 				=> 3,
			);
  	$form['amend_worker']['per_worker_child_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12" id="id_per_worker_child_men">',
			  '#suffix' 	 		=> '</div></td>',
			 // '#title'			=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $permanent_children_male, 
			  //'#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#size' 				=> 3,
			);
  	$form['amend_worker']['per_worker_child_women'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12" id="id_per_worker_child_women">',
			  '#suffix' 	 		=> '</div></td>',
			 // '#title'			=>	t('Women'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $permanent_children_female, 
			 // '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#size' 				=> 3,
			);
  	$form['amend_worker']['con_worker_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12" id="id_con_worker_men">',
			  '#suffix' 	 		=> '</div></td>',
			 // '#title'			=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $contactual_worker_men, 
			 // '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#size' 			=> 3,
			);
  	$form['amend_worker']['con_worker_women'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12" id="id_con_worker_women">',
			  '#suffix' 	 		=> '</div></td>',
			  //'#title'				=>	t('Women'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $contactual_worker_women, 
			  //'#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#size' 			=> 3,
			);
  	$form['amend_worker']['con_worker_adol_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12" id="id_con_worker_adol_men">',
			  '#suffix' 	 		=> '</div></td>',
			 // '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $contactual_adolescents_male, 
			  //'#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#size' 			=> 3,
		);
  	$form['amend_worker']['con_worker_adol_women'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12" id="id_con_worker_adol_women">',
				  '#suffix' 	 		=> '</div></td>',
				//  '#title'				=>	t('Women'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> $contactual_adolescents_female, 
				 // '#attributes' 		=> array('class'=>array('form-control')),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				  '#size' 			=> 3,
			);
  	$form['amend_worker']['con_worker_child_men'] = array(
			 '#prefix' 				=> '<td><div class="col-xs-12" id="id_con_worker_child_men">',
			  '#suffix' 	 		=> '</div></td>',
			 // '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $contactual_children_male, 
			 // '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#size' 			=> 3,
		);
	
  	$form['amend_worker']['con_worker_child_woman'] = array(
			 '#prefix' 				=> '<td><div class="col-xs-12" id="id_con_worker_child_woman">',
			  '#suffix' 	 		=> '</div></td>',
			  //'#title'				=>	t('Women'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $contactual_children_female, 
			  //'#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#size' 			=> 3,
			);
			
	$form['amend_worker']['amend_total_worker'] = array(
			 '#prefix' 				=> '<td><div class="col-xs-12" id="id_amend_total_worker">',
			  '#suffix' 	 		=> '</div></td></tr>',
			  '#title'				=>	t('Total Workers'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> '', 
			  //'#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			  '#size' 				=> 3,
	);
  	$form['amend_worker']['previous_table_end'] 	= array(
		'#prefix'	=> '<div id="worker_end_table_id">',
  		'#suffix'	=> '</table></br></div>',
  		'#type'		=> 'markup',
		'#markup' => '<font color="#FF0000">N.B. Adolescents (over 15 but under 18 years of age) & Children (over 14 but under 15 years of age)</font>',	
		);
	$radios_options = array('power_generating_station'=>"Power generating station",'other'=>"Other");	
		$form['amend_worker']['is_generating']= array(
					 '#prefix' 			=> '<div class="col-md-12 col-xs-12" id="id_is_generating">',
					 '#suffix'    		=> '</div>',
					 '#type'		 	=> 'radios',
					 '#title'			=>	t('Type of power generating station'),
					 '#options'   		=> $radios_options,	
					 '#default_value' 	=> $type_power_station,
					 '#required'		=> TRUE,
		);
		$form['amend_worker']['power_type'] 	= array(
					 '#prefix' 				=> '<div class="col-md-3 col-xs-3" id="id_power_type">',
					 '#suffix' 				=> '</div>',
					 '#title'				=>	t('Unit of power'),
					 '#type' 		 		=> 'select',
					 '#default_value' 		=>  $power_unit,
					 '#options'	 			=>  array('HP'=>'HP','KW'=>'KW'),
					 '#attributes' 			=>  array('class'=>array('form-control')),
					 '#required' 			=>  TRUE,
		);
		$form['amend_worker']['installed_power'] 	= array(
					 '#prefix' 				=> '<div class="col-md-3 col-xs-3" id="id_installed_power">',
					 '#suffix' 				=> '</div>',
					  '#title'				=>	t('Amended Power'),
					  '#type' 				=> 'textfield',
					  '#element_validate'	=>  array('DOUBLE_FIELD_VALIDATION'),
					  '#default_value' 		=>  $installed_power,
					  '#attributes' 		=>  array('class'=>array('form-control')),
					  '#required' 			=>  TRUE,
	
		);		
		$form['amend_worker']['previous_installed_unit'] 	= array(
					 '#prefix' 				=> '<div class="col-md-3 col-xs-3" id="id_previous_installed_unit">',
					 '#suffix' 				=> '</div>',
					  '#title'				=>	t('Previous Unit of power'),
					 '#type' 		 		=> 'select',
					 '#default_value' 		=>  $power_unit,
					 '#options'	 			=>  array('HP'=>'HP','KW'=>'KW'),
					 '#attributes' 			=>  array('class'=>array('form-control')),
					 '#required' 			=>  TRUE,
	
		);
		$form['amend_worker']['previous_installed_power'] 	= array(
					 '#prefix' 				=> '<div class="col-md-3 col-xs-3" id="id_previous_installed_power">',
					 '#suffix' 				=> '</div>',
					  '#title'				=>	t('Previous Installed Power'),
					  '#type' 				=> 'textfield',
					  '#element_validate'	=>  array('DOUBLE_FIELD_VALIDATION'),
					  '#default_value' 		=>  $installed_power,
					  '#attributes' 		=>  array('class'=>array('form-control')),
					  '#required' 			=>  TRUE,
	
		);	
		
		
	}	
	
	
			
	
	$form['amend_power_worker']['submit'] = array (
		'#prefix' 		=> '<div class="row"><div class="col-md-12">',
		'#suffix'		=> '</div></div><br>',
		'#type' 		=> 'submit',
		'#attributes' 	=> array('class' => array('btn btn-success pull-right')),
		'#value' 		=> 'Submit',
		//'#ajax' 		=> array(
//				'callback' 	=> 'workers_add_more_add_one',
//        		'wrapper' 	=> 'wrapper',
//         		'method' 	=> 'replace',
//         		'effect' 	=> 'fade',
//      			),
	);
	
	$form['amend_data_display'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('Amendeded Data'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	$form['amend_data_display']['start']= array(
		'#prefix' 			=> '<div class="row">',
		'#type' 			=> 'markup',
	);
	$form['amend_data_display']['view_amend_year_data'] = array(
		'#prefix' => '<div class="col-md-12" id="table_div_replace">'.view_amend_year_details($application_id,$service_id,$factory_type_id,$reference_number),
		'#suffix' => '</div>'
	);
	$form['preview_link'] = array(
		'#prefix' => '<div class="col-md-12">',
        '#suffix' => '</div></div>',
  	//'#markup' => l(t('Preview as PDF'), 'applicant/applicant-dasboard/', array('html' => TRUE,'attributes' => array('class' => array('btn btn-dark space-left') )))
		'#markup' => l('DRAFT COPY', 'section/preview-amendment-informaion/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',		$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_number), array('html' => TRUE,'attributes'=>array('title' => 'Preview as PDF','class'=>array('btn btn-warning pull-right'))))
  		);
	return $form; 	
}


function get_ajax_load_worker($form, $form_state){
	$commands = array();
	$commands[] = ajax_command_replace('#worker_table_id', drupal_render($form['amend_worker']['previous_table']));
	$commands[] = ajax_command_replace('#id_per_worker_men', drupal_render($form['amend_worker']['per_worker_men']));
	$commands[] = ajax_command_replace('#id_per_worker_women', drupal_render($form['amend_worker']['per_worker_women']));
	$commands[] = ajax_command_replace('#id_per_worker_adol_men', drupal_render($form['amend_worker']['per_worker_adol_men']));
	$commands[] = ajax_command_replace('#id_per_worker_adol_women', drupal_render($form['amend_worker']['per_worker_adol_women']));
	$commands[] = ajax_command_replace('#id_per_worker_child_men', drupal_render($form['amend_worker']['per_worker_child_men']));
	$commands[] = ajax_command_replace('#id_per_worker_child_women', drupal_render($form['amend_worker']['per_worker_child_women']));
	$commands[] = ajax_command_replace('#id_con_worker_men', drupal_render($form['amend_worker']['con_worker_men']));
	$commands[] = ajax_command_replace('#id_con_worker_women', drupal_render($form['amend_worker']['con_worker_women']));
	$commands[] = ajax_command_replace('#id_con_worker_adol_men', drupal_render($form['amend_worker']['con_worker_adol_men']));
	$commands[] = ajax_command_replace('#id_con_worker_adol_women', drupal_render($form['amend_worker']['con_worker_adol_women']));
	$commands[] = ajax_command_replace('#id_con_worker_child_men', drupal_render($form['amend_worker']['con_worker_child_men']));
	$commands[] = ajax_command_replace('#id_con_worker_child_woman', drupal_render($form['amend_worker']['con_worker_child_woman']));
	$commands[] = ajax_command_replace('#id_amend_total_worker', drupal_render($form['amend_worker']['amend_total_worker']));
	$commands[] = ajax_command_replace('#worker_end_table_id', drupal_render($form['amend_worker']['previous_table_end']));
	$commands[] = ajax_command_replace('#id_previous_worker', drupal_render($form['amend_worker']['previous_total_worker']));
	
	$commands[] = ajax_command_replace('#id_is_generating', drupal_render($form['amend_worker']['is_generating']));
	$commands[] = ajax_command_replace('#id_power_type', drupal_render($form['amend_worker']['power_type']));
	$commands[] = ajax_command_replace('#id_installed_power', drupal_render($form['amend_worker']['installed_power']));
	
	$commands[] = ajax_command_replace('#id_previous_installed_unit', drupal_render($form['amend_worker']['previous_installed_unit']));
	$commands[] = ajax_command_replace('#id_previous_installed_power', drupal_render($form['amend_worker']['previous_installed_power']));
	return array('#type' => 'ajax', '#commands' => $commands);
}

function view_amend_year_details($application_id,$service_id,$factory_type_id,$reference_number){
	$get_all_data 			= array();
	$type					= '';
	$details				= '';
	$relationship			= '';
	$address_of_manager		= '';
	
	$get_all_data = fetch_old_data($application_id,$service_id,$factory_type_id,$reference_number);
	//print_r($get_all_data);die;
	//$get_all_data = amend_power_worker_data($application_id,$factory_type_id,$service_id,$reference_number);

	$Wcounter		= 0;
	$per_page		= 6;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page);
	
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header = array(
					array('data'=> 'Licence Period'),
					array('data'=> 'Previous Total Worker'),
					array('data'=> 'Amendment Worker'),
					array('data'=> 'Total power'),
					array('data'=> 'Amendment Power'),
					array('data'=> 'Action'),	
				);
	if(!empty($get_all_data)){
		
		foreach($chunks[$current_page] as $data_details){ 
			$Wcounter++;
			if($data_details->amend_renewal_flag  == 1){
				$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/caf-online-renew/del-amend-worker/'.encryption_decryption_fun('encrypt', $data_details->id).'/'.encryption_decryption_fun('encrypt', $data_details->application_id).'/'.encryption_decryption_fun('encrypt', $data_details->service_id).'/'.encryption_decryption_fun('encrypt', $data_details->factory_type).'/'.encryption_decryption_fun('encrypt', $data_details->application_reference_no).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
				}
				else{
					$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
				}
				
				if($data_details->power_unit=='HP'){
					$power = $data_details->installed_power_hp.' '.$data_details->power_unit;
				}else{
					$power = $data_details->installed_power.' '.$data_details->power_unit;
				}
			$rows[] = array( 
						array('data' =>$data_details->service_year,'class' => array('')),
						array('data' =>$data_details->previous_worker,'class' => array('')),
						array('data' =>$data_details->worker_total,'class' => array('')),
						array('data' =>$power,'class' => array('')),
						array('data' =>$data_details->amended_power.' '.$data_details->amended_power_unit,'class' => array('')),	
						array('data' =>$delLink,'class' => array('')),
					);
			} 
		
		}
		$output = theme_table(
			array(
				  'header' => $header,
				  'rows' => $rows,
				  'attributes' => array('id'=>'view_old_data_id', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
				  'sticky' => true,
				  'caption' => '',
				  'colgroups' => array(),
				  'empty' => t("No data found!") // The message to be displayed if table is empty
				)
			).theme('pager');	
		 	return $output;	
	}
function delete_uploaded_previous_data($id,$application_id,$service_id,$factory_type_id,$reference_number){

	drupal_add_library('system', 'drupal.ajax');
	if (trim(encryption_decryption_fun('decrypt', $id)) != 0) {
				$query = db_delete('fa_worker_details');
		 		$query->condition('id', trim(encryption_decryption_fun('decrypt', $id)),'=');
		 		$query->condition('application_reference_no',trim(encryption_decryption_fun('decrypt', $reference_number)),'=');
		 		$query->execute();
			}
		 	$commands = array();
			$commands[] = ajax_command_replace('#view_old_data_id', "<div id ='view_old_data_id'><div class='col-md-12 col-xs-12'>".view_amend_year_details(encryption_decryption_fun('decrypt', $application_id),encryption_decryption_fun('decrypt', $service_id),encryption_decryption_fun('decrypt', $factory_type_id),encryption_decryption_fun('decrypt', $reference_number)).'</div></div>');
		 	$page = array('#type' => 'ajax', '#commands' => $commands);
		 	ajax_deliver($page);
		}



function fetch_old_data($application_id,$service_id,$factory_type_id,$reference_number){
	$query_year		= 	db_select('fa_worker_details', 'worker')->DISTINCT();
	$query_year		->	JOIN('fa_power_details', 'power','power.application_id = worker.application_id');
	$query_year		->	fields('worker',array('id','service_year','application_id','service_id','factory_type','application_id','application_reference_no','service_year','permanent_worker_men','permanent_worker_women','permanent_adolescents_male','permanent_adolescents_female','permanent_children_male','permanent_children_female','worker_total','change_date','worker_registration_status','previous_worker','is_amendment'));
	$query_year		->	fields('power', array('application_id','amended_power','amended_power_unit','is_amended','installed_power_hp','installed_power','power_unit'));
	$query_year		-> 	condition('worker.application_id', $application_id);
	$query_year		-> 	condition('worker.service_id', $service_id);
	$query_year		-> 	condition('worker.factory_type', $factory_type_id);
	$query_year		-> 	condition('worker.application_reference_no', $reference_number);
	$query_year		->	condition('power.is_amended', 1);
	$query_year		->	condition('worker.is_amendment', 1);
	$result_year	= 	$query_year->execute()->fetchAll();
	return $result_year;
	}


	
function renewal_amendment_notice_submit($form, &$form_state){
	global $user;
	$uid 			    		=  $user->uid;
	$val  						= $form_state['input'];
	$amanded_date_from 			= $val['amanded_date_from'];
	$amanded_date_to 			= $val['amanded_date_to'];
	$per_worker_men				= $val['per_worker_men'];
	$per_worker_women			= $val['per_worker_women'];
	$per_worker_adol_men 		= $val['per_worker_adol_men'];
	$per_worker_adol_women 		= $val['per_worker_adol_women'];
	$per_worker_child_men		= $val['per_worker_child_men'];
	$per_worker_child_women		= $val['per_worker_child_women'];
	$con_worker_men				= $val['con_worker_men'];
	$con_worker_women			= $val['con_worker_women'];
	$con_worker_adol_men		= $val['con_worker_adol_men'];
	$con_worker_adol_women		= $val['con_worker_adol_women'];
	$con_worker_child_men		= $val['con_worker_child_men'];
	$con_worker_child_woman		= $val['con_worker_child_woman'];
	$previous_total_worker		= $val['previous_total_worker'];
	
	$is_generating				= $val['is_generating'];
	$power_type					= $val['power_type'];
	$installed_power			= $val['installed_power'];
	$previous_installed_power	= $val['previous_installed_power'];
	$previous_installed_unit	= $val['previous_installed_unit'];
	
	$license_period 			= $val['license_period'];
	$service_id					=  encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$factory_type_id			=  encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$application_id 			=  encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$app_reference_no			=  encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	
	$get_calculate_date = db_query("Select * from {fa_calculate_year} WHERE id=".$val['license_period'])->fetchObject();
	
	//print_r($get_calculate_date);die;
	//print_r($val);die;
	if($val['amend_power_worker']==1){
		$worker_total = $val['per_worker_men']+$val['per_worker_women']+ $val['per_worker_adol_men']+$val['per_worker_adol_women']+$val['apply_children_male']+$val['per_worker_child_women']+$val['con_worker_men']+$val['con_worker_women']+$val['con_worker_adol_men']+$val['con_worker_adol_women']+$val['con_worker_child_men']+$val['con_worker_child_woman'];
		
		if($factory_type_id==1){
			if($worker_total>=10){
				if($val['is_generating'] == "power_generating_station"){
					if($val['previous_installed_unit'] == 'KW'){
						if($val['previous_installed_unit'] == 'KW'){
							$installed_power_hp = $val['previous_installed_power']*1.34102;//(1Kw => 1.34102 Hp)
						}
						if($val['previous_installed_unit'] == 'HP'){
							$installed_power_hp = $val['previous_installed_power'];
						}
						$worker_details_yearly =array(
							'permanent_worker_men'				=> $val['per_worker_men'],
							'permanent_worker_women' 		    => $val['per_worker_women'],
							'permanent_adolescents_male'        => $val['per_worker_adol_men'],
							'permanent_adolescents_female' 		=> $val['per_worker_adol_women'],
							'permanent_children_male'           => $val['per_worker_child_men'],
							'permanent_children_female' 	    => $val['per_worker_child_women'],
											
							'contactual_worker_men'				=> $val['con_worker_men'],
							'contactual_worker_women' 		    => $val['con_worker_women'],
							'contactual_adolescents_male'       => $val['con_worker_adol_men'],
							'contactual_adolescents_female' 	=> $val['con_worker_adol_women'],
							'contactual_children_male'          => $val['con_worker_child_men'],
							'contactual_children_female' 	    => $val['con_worker_child_woman'],
											
							'worker_total'				    => $worker_total,
							'service_id'				    => $service_id,
							'service_year'				    => $get_calculate_date->calculate_year,
							'factory_type'				    => $factory_type_id,
							'created_by'				    => $uid,
							'application_id'			    => $application_id,
							'worker_registration_status'   	=> 'In',
							'application_reference_no'   	=> $app_reference_no,
							'worker_active_inactive'		=> 1,
							'valid_year'					=> $get_calculate_date->showing_year,
							'valid_time_period'				=> $get_calculate_date->valid_time_period,
							'starting_year'					=> $get_calculate_date->calculate_starting_year,
							'calculate_year_id'				=> $get_calculate_date->id,
							'change_date'					=> !empty($val['application_date'])?$val['application_date']:NULL,
							'is_amendment'					=> 1,
						);
						db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
						$power_details_yearly =array(
							'power_unit' 				=> $val['previous_installed_unit'],
							'installed_power'			=> $val['previous_installed_power']	,				
							'installed_power_hp'		=> $installed_power_hp,
							'service_id'				=> $service_id,
							'factory_type'				=> $factory_type_id,
							'created_by'				=> $uid,
							'application_id'			=> $application_id,
							'application_reference_no'	=> $app_reference_no,
							'power_application_status'	=> 'In',
							'service_year'				=> $get_calculate_date->calculate_year,
							'type_power_station'		=> $is_generating,
							'power_active_inactive'		=> $get_calculate_date->is_active_year,
							'valid_year'				=> $get_calculate_date->calculate_end_year,
							'valid_time_period'		 	=> $get_calculate_date->valid_time_period,
							'starting_year'				=> $get_calculate_date->calculate_starting_year,
							'change_date'				=> !empty($val['hp_change_date'])?$val['hp_change_date']:NULL,
							'is_amended'				=> 1,
						);	
						db_insert('fa_power_details')->fields($power_details_yearly)->execute();
					}else{
						drupal_set_message('All power unit must be in KW.','warning');
					}
				}
				if($val['is_generating'] == "other"){
						if($val['previous_installed_unit'] == 'HP'){
							$installed_power_hp = $val['previous_installed_power'];
							}
							$worker_details_yearly =array(
							'permanent_worker_men'				=> $val['per_worker_men'],
							'permanent_worker_women' 		    => $val['per_worker_women'],
							'permanent_adolescents_male'        => $val['per_worker_adol_men'],
							'permanent_adolescents_female' 		=> $val['per_worker_adol_women'],
							'permanent_children_male'           => $val['per_worker_child_men'],
							'permanent_children_female' 	    => $val['per_worker_child_women'],
											
							'contactual_worker_men'				=> $val['con_worker_men'],
							'contactual_worker_women' 		    => $val['con_worker_women'],
							'contactual_adolescents_male'       => $val['con_worker_adol_men'],
							'contactual_adolescents_female' 	=> $val['con_worker_adol_women'],
							'contactual_children_male'          => $val['con_worker_child_men'],
							'contactual_children_female' 	    => $val['con_worker_child_woman'],
											
							'worker_total'				    => $worker_total,
							'service_id'				    => $service_id,
							'service_year'				    => $get_calculate_date->calculate_year,
							'factory_type'				    => $factory_type_id,
							'created_by'				    => $uid,
							'application_id'			    => $application_id,
							'worker_registration_status'   	=> 'In',
							'application_reference_no'   	=> $app_reference_no,
							'worker_active_inactive'		=> 1,
							'valid_year'					=> $get_calculate_date->showing_year,
							'valid_time_period'				=> $get_calculate_date->valid_time_period,
							'starting_year'					=> $get_calculate_date->calculate_starting_year,
							'calculate_year_id'				=> $get_calculate_date->id,
							'change_date'					=> !empty($val['application_date'])?$val['application_date']:NULL,
							'is_amendment'					=> 1,
						);
						db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
						$power_details_yearly =array(
							'power_unit' 				=> $val['previous_installed_unit'],
							'installed_power'			=> $val['previous_installed_power']	,				
							'installed_power_hp'		=> $installed_power_hp,
							'service_id'				=> $service_id,
							'factory_type'				=> $factory_type_id,
							'created_by'				=> $uid,
							'application_id'			=> $application_id,
							'application_reference_no'	=> $app_reference_no,
							'power_application_status'	=> 'In',
							'service_year'				=> $get_calculate_date->calculate_year,
							'type_power_station'		=> $is_generating,
							'power_active_inactive'		=> $get_calculate_date->is_active_year,
							'valid_year'				=> $get_calculate_date->calculate_end_year,
							'valid_time_period'		 	=> $get_calculate_date->valid_time_period,
							'starting_year'				=> $get_calculate_date->calculate_starting_year,
							'change_date'				=> !empty($val['hp_change_date'])?$val['hp_change_date']:NULL,
							'is_amended'				=> 1,
						);	
						$id = db_insert('fa_power_details')->fields($power_details_yearly)->execute();
					}
			}else{
				drupal_set_message(('Total number workers must be equal or more than 10'),'warning');
			}
		}
		if($factory_type_id==2){
			if($worker_total>=20){
			if($val['is_generating'] == "power_generating_station"){
					if($val['previous_installed_unit'] == 'KW'){
						if($val['previous_installed_unit'] == 'KW'){
							$installed_power_hp = $val['previous_installed_power']*1.34102;//(1Kw => 1.34102 Hp)
						}
						if($val['previous_installed_unit'] == 'HP'){
							$installed_power_hp = $val['previous_installed_power'];
						}
						$worker_details_yearly =array(
							'permanent_worker_men'				=> $val['per_worker_men'],
							'permanent_worker_women' 		    => $val['per_worker_women'],
							'permanent_adolescents_male'        => $val['per_worker_adol_men'],
							'permanent_adolescents_female' 		=> $val['per_worker_adol_women'],
							'permanent_children_male'           => $val['per_worker_child_men'],
							'permanent_children_female' 	    => $val['per_worker_child_women'],
											
							'contactual_worker_men'				=> $val['con_worker_men'],
							'contactual_worker_women' 		    => $val['con_worker_women'],
							'contactual_adolescents_male'       => $val['con_worker_adol_men'],
							'contactual_adolescents_female' 	=> $val['con_worker_adol_women'],
							'contactual_children_male'          => $val['con_worker_child_men'],
							'contactual_children_female' 	    => $val['con_worker_child_woman'],
											
							'worker_total'				    => $worker_total,
							'service_id'				    => $service_id,
							'service_year'				    => $get_calculate_date->calculate_year,
							'factory_type'				    => $factory_type_id,
							'created_by'				    => $uid,
							'application_id'			    => $application_id,
							'worker_registration_status'   	=> 'In',
							'application_reference_no'   	=> $app_reference_no,
							'worker_active_inactive'		=> 1,
							'valid_year'					=> $get_calculate_date->showing_year,
							'valid_time_period'				=> $get_calculate_date->valid_time_period,
							'starting_year'					=> $get_calculate_date->calculate_starting_year,
							'calculate_year_id'				=> $get_calculate_date->id,
							'change_date'					=> !empty($val['application_date'])?$val['application_date']:NULL,
							'is_amendment'					=> 1,
						);
						$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
						$power_details_yearly =array(
		
							'power_unit' 				=> $val['previous_installed_unit'],
							'installed_power'			=> $val['previous_installed_power']	,				
							'installed_power_hp'		=> $installed_power_hp,
							'service_id'				=> $service_id,
							'factory_type'				=> $factory_type_id,
							'created_by'				=> $uid,
							'application_id'			=> $application_id,
							'application_reference_no'	=> $app_reference_no,
							'power_application_status'	=> 'In',
							'service_year'				=> $get_calculate_date->calculate_year,
							'type_power_station'		=> $is_generating,
							'power_active_inactive'		=> $get_calculate_date->is_active_year,
							'valid_year'				=> $get_calculate_date->calculate_end_year,
							'valid_time_period'		 	=> $get_calculate_date->valid_time_period,
							'starting_year'				=> $get_calculate_date->calculate_starting_year,
							'change_date'				=> !empty($val['hp_change_date'])?$val['hp_change_date']:NULL,
							'is_amended'				=> 1,
						);	
						$id = db_insert('fa_power_details')->fields($power_details_yearly)->execute();
					}
				}else{
						drupal_set_message('Power generation station must be HP.','warning');
					}
			}
			else{
				drupal_set_message(('Total number workers must be equal or more than 20'),'warning');
			}
	  	}
	}
	if($val['amend_power_worker']==2){
		$worker_total = $val['per_worker_men']+$val['per_worker_women']+ $val['per_worker_adol_men']+$val['per_worker_adol_women']+$val['apply_children_male']+$val['per_worker_child_women']+$val['con_worker_men']+$val['con_worker_women']+$val['con_worker_adol_men']+$val['con_worker_adol_women']+$val['con_worker_child_men']+$val['con_worker_child_woman'];
		if($factory_type_id==1){
			if($previous_total_worker>=10){
				if($val['is_generating'] == "power_generating_station"){
						if($val['previous_installed_unit'] == 'KW'){
							if($val['previous_installed_unit'] == 'KW'){
								$installed_power_hp = $val['previous_installed_power']*1.34102;//(1Kw => 1.34102 Hp)
								$amended_power_hp 	= $val['installed_power']*1.34102;//(1Kw => 1.34102 Hp)
							}
							if($val['previous_installed_unit'] == 'HP'){
								$installed_power_hp = $val['previous_installed_power'];
								$amended_power_hp 	= $val['installed_power'];
							}
							$worker_details_yearly =array(
								//'permanent_worker_men'				=> $val['per_worker_men'],
				//				'permanent_worker_women' 		    => $val['per_worker_women'],
				//				'permanent_adolescents_male'        => $val['per_worker_adol_men'],
				//				'permanent_adolescents_female' 		=> $val['per_worker_adol_women'],
				//				'permanent_children_male'           => $val['per_worker_child_men'],
				//				'permanent_children_female' 	    => $val['per_worker_child_women'],
				//								
				//				'contactual_worker_men'				=> $val['con_worker_men'],
				//				'contactual_worker_women' 		    => $val['con_worker_women'],
				//				'contactual_adolescents_male'       => $val['con_worker_adol_men'],
				//				'contactual_adolescents_female' 	=> $val['con_worker_adol_women'],
				//				'contactual_children_male'          => $val['con_worker_child_men'],
				//				'contactual_children_female' 	    => $val['con_worker_child_woman'],
												
								'previous_worker'			 	=> $previous_total_worker,
								'total_worker'			 		=> $total_worker,
								'service_id'				    => $service_id,
								'service_year'				    => $get_calculate_date->calculate_year,
								'factory_type'				    => $factory_type_id,
								'created_by'				    => $uid,
								'application_id'			    => $application_id,
								'worker_registration_status'   	=> 'In',
								'application_reference_no'   	=> $app_reference_no,
								'worker_active_inactive'		=> 1,
								'valid_year'					=> $get_calculate_date->showing_year,
								'valid_time_period'				=> $get_calculate_date->valid_time_period,
								'starting_year'					=> $get_calculate_date->calculate_starting_year,
								'calculate_year_id'				=> $get_calculate_date->id,
								'change_date'					=> !empty($val['application_date'])?$val['application_date']:NULL,
								'is_amendment'					=> 1,
							);
							$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
							$power_details_yearly =array(
		
								'power_unit' 				=> $val['previous_installed_unit'],
								'installed_power'			=> $val['previous_installed_power'],				
								'installed_power_hp'		=> $installed_power_hp,
								
								'is_amended'				=> 1, 
								'amended_power'				=> $amended_power_hp,
								'amended_power_unit'		=> $val['power_type'],
								
								'service_id'				=> $service_id,
								'factory_type'				=> $factory_type_id,
								'created_by'				=> $uid,
								'application_id'			=> $application_id,
								'application_reference_no'	=> $app_reference_no,
								'power_application_status'	=> 'In',
								'service_year'				=> $get_calculate_date->calculate_year,
								'type_power_station'		=> $is_generating,
								'power_active_inactive'		=> $get_calculate_date->is_active_year,
								'valid_year'				=> $get_calculate_date->calculate_end_year,
								'valid_time_period'		 	=> $get_calculate_date->valid_time_period,
								'starting_year'				=> $get_calculate_date->calculate_starting_year,
								'change_date'				=> !empty($val['hp_change_date'])?$val['hp_change_date']:NULL,
							);	
							$id = db_insert('fa_power_details')->fields($power_details_yearly)->execute();
						}
						else{
							drupal_set_message(('Power unit must be HP.'),'warning');	
						}
					}
				if($val['is_generating'] == "other"){
						if($val['previous_installed_unit'] == 'KW'){
							$installed_power_hp = $val['previous_installed_power']*1.34102;//(1Kw => 1.34102 Hp)
							$amended_power_hp 	= $val['installed_power']*1.34102;//(1Kw => 1.34102 Hp)
						}
						if($val['previous_installed_unit'] == 'HP'){
							$installed_power_hp = $val['previous_installed_power'];
							$amended_power_hp 	= $val['installed_power'];
						}
						$worker_details_yearly =array(
							//'permanent_worker_men'				=> $val['per_worker_men'],
								'permanent_worker_women' 		    => $val['per_worker_women'],
								'permanent_adolescents_male'        => $val['per_worker_adol_men'],
								'permanent_adolescents_female' 		=> $val['per_worker_adol_women'],
								'permanent_children_male'           => $val['per_worker_child_men'],
								'permanent_children_female' 	    => $val['per_worker_child_women'],
											
								'contactual_worker_men'				=> $val['con_worker_men'],
								'contactual_worker_women' 		    => $val['con_worker_women'],
								'contactual_adolescents_male'       => $val['con_worker_adol_men'],
								'contactual_adolescents_female' 	=> $val['con_worker_adol_women'],
								'contactual_children_male'          => $val['con_worker_child_men'],
								'contactual_children_female' 	    => $val['con_worker_child_woman'],
												
								'previous_worker'				=> $previous_total_worker,
								'service_id'				    => $service_id,
								'service_year'				    => $get_calculate_date->calculate_year,
								'factory_type'				    => $factory_type_id,
								'created_by'				    => $uid,
								'application_id'			    => $application_id,
								'worker_registration_status'   	=> 'In',
								'application_reference_no'   	=> $app_reference_no,
								'worker_active_inactive'		=> 1,
								'valid_year'					=> $get_calculate_date->showing_year,
								'valid_time_period'				=> $get_calculate_date->valid_time_period,
								'starting_year'					=> $get_calculate_date->calculate_starting_year,
								'calculate_year_id'				=> $get_calculate_date->id,
								'change_date'					=> !empty($val['application_date'])?$val['application_date']:NULL,
								'is_amendment'					=> 1,
							);
							$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
							
						$power_details_yearly =array(
							'power_unit' 				=> $val['previous_installed_unit'],
							'installed_power'			=> $val['previous_installed_power'],				
							'installed_power_hp'		=> $installed_power_hp,
							
							'is_amended'				=> 1, 
							'amended_power'				=> $amended_power_hp,
							'amended_power_unit'		=> $val['power_type'],
							
							'service_id'				=> $service_id,
							'factory_type'				=> $factory_type_id,
							'created_by'				=> $uid,
							'application_id'			=> $application_id,
							'application_reference_no'	=> $app_reference_no,
							'power_application_status'	=> 'In',
							'service_year'				=> $get_calculate_date->calculate_year,
							'type_power_station'		=> $is_generating,
							'power_active_inactive'		=> $get_calculate_date->is_active_year,
							'valid_year'				=> $get_calculate_date->calculate_end_year,
							'valid_time_period'		 	=> $get_calculate_date->valid_time_period,
							'starting_year'				=> $get_calculate_date->calculate_starting_year,
							'change_date'				=> !empty($val['hp_change_date'])?$val['hp_change_date']:NULL,
						);	
						$id = db_insert('fa_power_details')->fields($power_details_yearly)->execute();
					}
			}
			else{
				drupal_set_message(('Total number workers must be equal or more than 10'),'warning');
			}
		}
		if($factory_type_id==2){
			if($$previous_total_worker>=20){
				if($val['is_generating'] == "power_generating_station"){
						if($val['previous_installed_unit'] == 'KW'){
							if($val['previous_installed_unit'] == 'KW'){
								$installed_power_hp = $val['previous_installed_power']*1.34102;//(1Kw => 1.34102 Hp)
								$amended_power_hp 	= $val['installed_power']*1.34102;//(1Kw => 1.34102 Hp)
							}
							if($val['previous_installed_unit'] == 'HP'){
								$installed_power_hp = $val['previous_installed_power'];
								$amended_power_hp 	= $val['installed_power'];
							}
							$worker_details_yearly =array(
								//'permanent_worker_men'				=> $val['per_worker_men'],
				//				'permanent_worker_women' 		    => $val['per_worker_women'],
				//				'permanent_adolescents_male'        => $val['per_worker_adol_men'],
				//				'permanent_adolescents_female' 		=> $val['per_worker_adol_women'],
				//				'permanent_children_male'           => $val['per_worker_child_men'],
				//				'permanent_children_female' 	    => $val['per_worker_child_women'],
				//								
				//				'contactual_worker_men'				=> $val['con_worker_men'],
				//				'contactual_worker_women' 		    => $val['con_worker_women'],
				//				'contactual_adolescents_male'       => $val['con_worker_adol_men'],
				//				'contactual_adolescents_female' 	=> $val['con_worker_adol_women'],
				//				'contactual_children_male'          => $val['con_worker_child_men'],
				//				'contactual_children_female' 	    => $val['con_worker_child_woman'],
												
								'worker_total'				    => $previous_total_worker,
								'service_id'				    => $service_id,
								'service_year'				    => $val['license_period'],
								'factory_type'				    => $factory_type_id,
								'created_by'				    => $uid,
								'application_id'			    => $application_id,
								'worker_registration_status'   	=> 'In',
								'application_reference_no'   	=> $app_reference_no,
								'worker_active_inactive'		=> 1,
								'valid_year'					=> $get_calculate_date->showing_year,
								'valid_time_period'				=> $get_calculate_date->valid_time_period,
								'starting_year'					=> $get_calculate_date->calculate_starting_year,
								'calculate_year_id'				=> $get_calculate_date->id,
								'change_date'					=> !empty($val['application_date'])?$val['application_date']:NULL,
								'is_amendment'					=> 1,
							);
							db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
							$power_details_yearly =array(
		
								'power_unit' 				=> $val['previous_installed_unit'],
								'installed_power'			=> $val['previous_installed_power'],				
								'installed_power_hp'		=> $installed_power_hp,
								
								'is_amended'				=> 1, 
								'amended_power'				=> $amended_power_hp,
								'amended_power_unit'		=> $val['power_type'],
								
								'service_id'				=> $service_id,
								'factory_type'				=> $factory_type_id,
								'created_by'				=> $uid,
								'application_id'			=> $application_id,
								'application_reference_no'	=> $app_reference_no,
								'power_application_status'	=> 'In',
								'service_year'				=> $get_calculate_date->calculate_year,
								'type_power_station'		=> $is_generating,
								'power_active_inactive'		=> $get_calculate_date->is_active_year,
								'valid_year'				=> $get_calculate_date->calculate_end_year,
								'valid_time_period'		 	=> $get_calculate_date->valid_time_period,
								'starting_year'				=> $get_calculate_date->calculate_starting_year,
								'change_date'				=> !empty($val['hp_change_date'])?$val['hp_change_date']:NULL,
							);	
							$id = db_insert('fa_power_details')->fields($power_details_yearly)->execute();
						}
						else{
							drupal_set_message(('Power unit must be HP.'),'warning');	
						}
					}
				if($val['is_generating'] == "other"){
						if($val['previous_installed_unit'] == 'KW'){
							$installed_power_hp = $val['previous_installed_power']*1.34102;//(1Kw => 1.34102 Hp)
							$amended_power_hp 	= $val['installed_power']*1.34102;//(1Kw => 1.34102 Hp)
						}
						if($val['previous_installed_unit'] == 'HP'){
							$installed_power_hp = $val['previous_installed_power'];
							$amended_power_hp 	= $val['installed_power'];
						}
						$worker_details_yearly =array(
								//'permanent_worker_men'				=> $val['per_worker_men'],
				//				'permanent_worker_women' 		    => $val['per_worker_women'],
				//				'permanent_adolescents_male'        => $val['per_worker_adol_men'],
				//				'permanent_adolescents_female' 		=> $val['per_worker_adol_women'],
				//				'permanent_children_male'           => $val['per_worker_child_men'],
				//				'permanent_children_female' 	    => $val['per_worker_child_women'],
				//								
				//				'contactual_worker_men'				=> $val['con_worker_men'],
				//				'contactual_worker_women' 		    => $val['con_worker_women'],
				//				'contactual_adolescents_male'       => $val['con_worker_adol_men'],
				//				'contactual_adolescents_female' 	=> $val['con_worker_adol_women'],
				//				'contactual_children_male'          => $val['con_worker_child_men'],
				//				'contactual_children_female' 	    => $val['con_worker_child_woman'],
												
								'worker_total'				    => $previous_total_worker,
								'service_id'				    => $service_id,
								'service_year'				    => $val['license_period'],
								'factory_type'				    => $factory_type_id,
								'created_by'				    => $uid,
								'application_id'			    => $application_id,
								'worker_registration_status'   	=> 'In',
								'application_reference_no'   	=> $app_reference_no,
								'worker_active_inactive'		=> 1,
								'valid_year'					=> $get_calculate_date->showing_year,
								'valid_time_period'				=> $get_calculate_date->valid_time_period,
								'starting_year'					=> $get_calculate_date->calculate_starting_year,
								'calculate_year_id'				=> $get_calculate_date->id,
								'change_date'					=> !empty($val['application_date'])?$val['application_date']:NULL,
								'is_amendment'					=> 1,
							);
						db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
						$power_details_yearly =array(
		
						'power_unit' 				=> $val['previous_installed_unit'],
						'installed_power'			=> $val['previous_installed_power'],				
						'installed_power_hp'		=> $installed_power_hp,
						
						'is_amended'				=> 1, 
  						'amended_power'				=> $amended_power_hp,
  						'amended_power_unit'		=> $val['power_type'],
						
						'service_id'				=> $service_id,
						'factory_type'				=> $factory_type_id,
						'created_by'				=> $uid,
						'application_id'			=> $application_id,
						'application_reference_no'	=> $app_reference_no,
						'power_application_status'	=> 'In',
						'service_year'				=> $get_calculate_date->calculate_year,
						'type_power_station'		=> $is_generating,
						'power_active_inactive'		=> $get_calculate_date->is_active_year,
						'valid_year'				=> $get_calculate_date->calculate_end_year,
					    'valid_time_period'		 	=> $get_calculate_date->valid_time_period,
						'starting_year'				=> $get_calculate_date->calculate_starting_year,
						'change_date'				=> !empty($val['hp_change_date'])?$val['hp_change_date']:NULL,
						);	
						$id = db_insert('fa_power_details')->fields($power_details_yearly)->execute();
					}
			}
			else{
				drupal_set_message(('Total number workers must be equal or more than 20'),'warning');
			}
		}
	}
	if($val['amend_power_worker']==3){
		$worker_total = $val['per_worker_men']+$val['per_worker_women']+ $val['per_worker_adol_men']+$val['per_worker_adol_women']+$val['apply_children_male']+$val['per_worker_child_women']+$val['con_worker_men']+$val['con_worker_women']+$val['con_worker_adol_men']+$val['con_worker_adol_women']+$val['con_worker_child_men']+$val['con_worker_child_woman'];
		if($factory_type_id==1){
		
			if($worker_total>=10){
				if($val['is_generating'] == "power_generating_station"){
					if($val['previous_installed_unit'] == 'KW'){
						if($val['previous_installed_unit'] == 'KW'){
							$installed_power_hp = $val['previous_installed_power']*1.34102;//(1Kw => 1.34102 Hp)
							$amended_power_hp 	= $val['installed_power']*1.34102;//(1Kw => 1.34102 Hp)
						}
						if($val['previous_installed_unit'] == 'HP'){
							$installed_power_hp = $val['previous_installed_power'];
							$amended_power_hp 	= $val['installed_power'];
						}
						$worker_details_yearly =array(
							'permanent_worker_men'			=> $val['per_worker_men'],
							'permanent_worker_women'		=> $val['per_worker_women'],
							'permanent_adolescents_male'	=> $val['per_worker_adol_men'],
							'permanent_adolescents_female'	=> $val['per_worker_adol_women'],
							'permanent_children_male'		=> $val['per_worker_child_men'],
							'permanent_children_female'		=> $val['per_worker_child_women'],
											
							'contactual_worker_men'			=> $val['con_worker_men'],
							'contactual_worker_women'		=> $val['con_worker_women'],
							'contactual_adolescents_male'	=> $val['con_worker_adol_men'],
							'contactual_adolescents_female'	=> $val['con_worker_adol_women'],
							'contactual_children_male'		=> $val['con_worker_child_men'],
							'contactual_children_female'	=> $val['con_worker_child_woman'],
											
							'previous_worker'				=> $previous_total_worker,
							'worker_total'				    => $worker_total,
							'service_id'				    => $service_id,
							'service_year'				    => $get_calculate_date->calculate_year,
							'factory_type'				    => $factory_type_id,
							'created_by'				    => $uid,
							'application_id'			    => $application_id,
							'worker_registration_status'   	=> 'In',
							'application_reference_no'   	=> $app_reference_no,
							'worker_active_inactive'		=> 1,
							'valid_year'					=> $get_calculate_date->showing_year,
							'valid_time_period'				=> $get_calculate_date->valid_time_period,
							'starting_year'					=> $get_calculate_date->calculate_starting_year,
							'calculate_year_id'				=> $get_calculate_date->id,
							'change_date'					=> !empty($val['application_date'])?$val['application_date']:NULL,
							'is_amendment'					=> 1,
						);
						db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
						$power_details_yearly =array(
							'power_unit' 				=> $val['previous_installed_unit'],
							'installed_power'			=> $val['previous_installed_power'],				
							'installed_power_hp'		=> $installed_power_hp,
							
							'is_amended'				=> 1, 
							'amended_power'				=> $amended_power_hp,
							'amended_power_unit'		=> $val['power_type'],
							
							'service_id'				=> $service_id,
							'factory_type'				=> $factory_type_id,
							'created_by'				=> $uid,
							'application_id'			=> $application_id,
							'application_reference_no'	=> $app_reference_no,
							'power_application_status'	=> 'In',
							'service_year'				=> $get_calculate_date->calculate_year,
							'type_power_station'		=> $is_generating,
							'power_active_inactive'		=> $get_calculate_date->is_active_year,
							'valid_year'				=> $get_calculate_date->calculate_end_year,
							'valid_time_period'		 	=> $get_calculate_date->valid_time_period,
							'starting_year'				=> $get_calculate_date->calculate_starting_year,
							'change_date'				=> !empty($val['hp_change_date'])?$val['hp_change_date']:NULL,
						);	
						db_insert('fa_power_details')->fields($power_details_yearly)->execute();
						}
						else{
							drupal_set_message(('Power unit must be KW.'),'warning');	
						}
					}
				if($val['is_generating'] == "other"){
						if($val['previous_installed_unit'] == 'KW'){
							$installed_power_hp = $val['previous_installed_power']*1.34102;//(1Kw => 1.34102 Hp)
							$amended_power_hp 	= $val['installed_power']*1.34102;//(1Kw => 1.34102 Hp)
						}
						if($val['previous_installed_unit'] == 'HP'){
							$installed_power_hp = $val['previous_installed_power'];
							$amended_power_hp 	= $val['installed_power'];
						}
						
						$worker_details_yearly =array(
							'permanent_worker_men'			=> $val['per_worker_men'],
							'permanent_worker_women'		=> $val['per_worker_women'],
							'permanent_adolescents_male'	=> $val['per_worker_adol_men'],
							'permanent_adolescents_female'	=> $val['per_worker_adol_women'],
							'permanent_children_male'		=> $val['per_worker_child_men'],
							'permanent_children_female'		=> $val['per_worker_child_women'],
											
							'contactual_worker_men'			=> $val['con_worker_men'],
							'contactual_worker_women'		=> $val['con_worker_women'],
							'contactual_adolescents_male'	=> $val['con_worker_adol_men'],
							'contactual_adolescents_female'	=> $val['con_worker_adol_women'],
							'contactual_children_male'		=> $val['con_worker_child_men'],
							'contactual_children_female'	=> $val['con_worker_child_woman'],
											
							'worker_total'				    => $worker_total,
							'previous_worker'				=> $previous_total_worker,
							'service_id'				    => $service_id,
							'service_year'				    => $get_calculate_date->calculate_year,
							'factory_type'				    => $factory_type_id,
							'created_by'				    => $uid,
							'application_id'			    => $application_id,
							'worker_registration_status'   	=> 'In',
							'application_reference_no'   	=> $app_reference_no,
							'worker_active_inactive'		=> 1,
							'valid_year'					=> $get_calculate_date->showing_year,
							'valid_time_period'				=> $get_calculate_date->valid_time_period,
							'starting_year'					=> $get_calculate_date->calculate_starting_year,
							'calculate_year_id'				=> $get_calculate_date->id,
							'change_date'					=> !empty($val['application_date'])?$val['application_date']:NULL,
							'is_amendment'					=> 1,
						);
						//print_r($worker_details_yearly);die;
						$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
						$power_details_yearly = array(
						'power_unit' 				=> $val['previous_installed_unit'],
						'installed_power'			=> $val['previous_installed_power'],				
						'installed_power_hp'		=> $installed_power_hp,
			
  						'amended_power'				=> $amended_power_hp,
  						'amended_power_unit'		=> $val['power_type'],
						
						'service_id'				=> $service_id,
						'factory_type'				=> $factory_type_id,
						'created_by'				=> $uid,
						'application_id'			=> $application_id,
						'application_reference_no'	=> $app_reference_no,
						'power_application_status'	=> 'In',
						'service_year'				=> $get_calculate_date->calculate_year,
						'type_power_station'		=> $is_generating,
						'power_active_inactive'		=> $get_calculate_date->is_active_year,
						'valid_year'				=> $get_calculate_date->calculate_end_year,
					    'valid_time_period'		 	=> $get_calculate_date->valid_time_period,
						'starting_year'				=> $get_calculate_date->calculate_starting_year,
						'change_date'				=> !empty($val['hp_change_date'])?$val['hp_change_date']:NULL,
						'is_amended'				=> 1, 
						);
						//print_r($power_details_yearly);die;	
						$id = db_insert('fa_power_details')->fields($power_details_yearly)->execute();
					}
				drupal_set_message('Amendment data successfully inserted.');
				}
				else{
					drupal_set_message(('Total number workers must be equal or more than 10'),'warning');
				}
			}
		if($factory_type_id==2){
			if($worker_total>=20){
				if($val['is_generating'] == "power_generating_station"){
					if($val['previous_installed_unit'] == 'KW'){
						if($val['previous_installed_unit'] == 'KW'){
							$installed_power_hp = $val['previous_installed_power']*1.34102;//(1Kw => 1.34102 Hp)
							$amended_power_hp 	= $val['installed_power']*1.34102;//(1Kw => 1.34102 Hp)
						}
						if($val['previous_installed_unit'] == 'HP'){
							$installed_power_hp = $val['previous_installed_power'];
							$amended_power_hp 	= $val['installed_power'];
						}
						$worker_details_yearly =array(
							'permanent_worker_men'				=> $val['per_worker_men'],
							'permanent_worker_women' 		    => $val['per_worker_women'],
							'permanent_adolescents_male'        => $val['per_worker_adol_men'],
							'permanent_adolescents_female' 		=> $val['per_worker_adol_women'],
							'permanent_children_male'           => $val['per_worker_child_men'],
							'permanent_children_female' 	    => $val['per_worker_child_women'],
											
							'contactual_worker_men'				=> $val['con_worker_men'],
							'contactual_worker_women' 		    => $val['con_worker_women'],
							'contactual_adolescents_male'       => $val['con_worker_adol_men'],
							'contactual_adolescents_female' 	=> $val['con_worker_adol_women'],
							'contactual_children_male'          => $val['con_worker_child_men'],
							'contactual_children_female' 	    => $val['con_worker_child_woman'],
											
							'worker_total'				    => $previous_total_worker,
							'service_id'				    => $service_id,
							'service_year'				    => $get_calculate_date->calculate_year,
							'factory_type'				    => $factory_type_id,
							'created_by'				    => $uid,
							'application_id'			    => $application_id,
							'worker_registration_status'   	=> 'In',
							'application_reference_no'   	=> $app_reference_no,
							'worker_active_inactive'		=> 1,
							'valid_year'					=> $get_calculate_date->showing_year,
							'valid_time_period'				=> $get_calculate_date->valid_time_period,
							'starting_year'					=> $get_calculate_date->calculate_starting_year,
							'calculate_year_id'				=> $get_calculate_date->id,
							'change_date'					=> !empty($val['application_date'])?$val['application_date']:NULL,
							'is_amendment'					=> 1,
							
						);
						db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();	
						$power_details_yearly =array(
								'power_unit' 				=> $val['previous_installed_unit'],
								'installed_power'			=> $val['previous_installed_power'],				
								'installed_power_hp'		=> $installed_power_hp,
								
								'is_amended'				=> 1, 
								'amended_power'				=> $amended_power_hp,
								'amended_power_unit'		=> $val['power_type'],
								
								'service_id'				=> $service_id,
								'factory_type'				=> $factory_type_id,
								'created_by'				=> $uid,
								'application_id'			=> $application_id,
								'application_reference_no'	=> $app_reference_no,
								'power_application_status'	=> 'In',
								'service_year'				=> $get_calculate_date->calculate_year,
								'type_power_station'		=> $is_generating,
								'power_active_inactive'		=> $get_calculate_date->is_active_year,
								'valid_year'				=> $get_calculate_date->calculate_end_year,
								'valid_time_period'		 	=> $get_calculate_date->valid_time_period,
								'starting_year'				=> $get_calculate_date->calculate_starting_year,
								'change_date'				=> !empty($val['hp_change_date'])?$val['hp_change_date']:NULL,
							);	
							db_insert('fa_power_details')->fields($power_details_yearly)->execute();
						}else{
							drupal_set_message(('Power unit must be KW.'),'warning');	
						}
					}
				if($val['is_generating'] == "other"){
						if($val['previous_installed_unit'] == 'KW'){
							$installed_power_hp = $val['previous_installed_power']*1.34102;//(1Kw => 1.34102 Hp)
							$amended_power_hp 	= $val['installed_power']*1.34102;//(1Kw => 1.34102 Hp)
						}
						if($val['previous_installed_unit'] == 'HP'){
							$installed_power_hp = $val['previous_installed_power'];
							$amended_power_hp 	= $val['installed_power'];
						}
						$worker_details_yearly =array(
							'permanent_worker_men'				=> $val['per_worker_men'],
							'permanent_worker_women' 		    => $val['per_worker_women'],
							'permanent_adolescents_male'        => $val['per_worker_adol_men'],
							'permanent_adolescents_female' 		=> $val['per_worker_adol_women'],
							'permanent_children_male'           => $val['per_worker_child_men'],
							'permanent_children_female' 	    => $val['per_worker_child_women'],
											
							'contactual_worker_men'				=> $val['con_worker_men'],
							'contactual_worker_women' 		    => $val['con_worker_women'],
							'contactual_adolescents_male'       => $val['con_worker_adol_men'],
							'contactual_adolescents_female' 	=> $val['con_worker_adol_women'],
							'contactual_children_male'          => $val['con_worker_child_men'],
							'contactual_children_female' 	    => $val['con_worker_child_woman'],
											
							'worker_total'				    => $previous_total_worker,
							'service_id'				    => $service_id,
							'service_year'				    => $get_calculate_date->calculate_year,
							'factory_type'				    => $factory_type_id,
							'created_by'				    => $uid,
							'application_id'			    => $application_id,
							'worker_registration_status'   	=> 'In',
							'application_reference_no'   	=> $app_reference_no,
							'worker_active_inactive'		=> 1,
							'valid_year'					=> $get_calculate_date->showing_year,
							'valid_time_period'				=> $get_calculate_date->valid_time_period,
							'starting_year'					=> $get_calculate_date->calculate_starting_year,
							'calculate_year_id'				=> $get_calculate_date->id,
							'change_date'					=> !empty($val['application_date'])?$val['application_date']:NULL,
							'is_amendment'					=> 1,
						);
						$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
						$power_details_yearly =array(
		
						'power_unit' 				=> $val['previous_installed_unit'],
						'installed_power'			=> $val['previous_installed_power'],				
						'installed_power_hp'		=> $installed_power_hp,
						
						'is_amended'				=> 1, 
  						'amended_power'				=> $amended_power_hp,
  						'amended_power_unit'		=> $val['power_type'],
						
						'service_id'				=> $service_id,
						'factory_type'				=> $factory_type_id,
						'created_by'				=> $uid,
						'application_id'			=> $application_id,
						'application_reference_no'	=> $app_reference_no,
						'power_application_status'	=> 'In',
						'service_year'				=> $get_calculate_date->calculate_year,
						'type_power_station'		=> $is_generating,
						'power_active_inactive'		=> $get_calculate_date->is_active_year,
						'valid_year'				=> $get_calculate_date->calculate_end_year,
					    'valid_time_period'		 	=> $get_calculate_date->valid_time_period,
						'starting_year'				=> $get_calculate_date->calculate_starting_year,
						'change_date'				=> !empty($val['hp_change_date'])?$val['hp_change_date']:NULL,
						);	
						$id = db_insert('fa_power_details')->fields($power_details_yearly)->execute();
					}
				drupal_set_message('Amendment data successfully inserted.');
				}else{
					drupal_set_message(('Total number workers must be equal or more than 20'),'warning');
			}
		}
	}
	$form_state['rebuild'] = TRUE;
}

