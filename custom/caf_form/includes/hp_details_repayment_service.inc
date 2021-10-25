<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');

function hp_details_repayment_service($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$referenccno){
		
	global $base_root, $base_path, $user;
	
 	$application_id = encryption_decryption_fun('decrypt', $applicationid);
	if(empty($application_id)){
		  	drupal_set_message(('At first you must be filled up the general information of factory then go to second tab'),'warning');
			drupal_goto('applicant/caf-reg/registrtatoin-license/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$linknumber.'/'.$linkdate.'/'.$flagmapp) ;
	 }else{
		 	$get_fa_cafa 				= get_fa_cafa($application_id);
		 	$reference_number 			= $get_fa_cafa['reference_number'];
			$value_factory_profile_type	= $get_fa_cafa['ownership_type'];
			$license_valid_upto			= $get_fa_cafa['license_valid_upto'];
			$is_year_calculation_tab	= $get_fa_cafa['is_year_calculation_tab'];
			$application_status			= $get_fa_cafa['application_status'];
			$period_for_application		= $get_fa_cafa['period_for_application'];
			 $date_of_amenability       = $get_fa_cafa['date_of_amenability'];
  
	 }
	 
	
	$service_id 	  = encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id  = encryption_decryption_fun('decrypt',$factory_typeid);
	//////////////////////////////occupier Type////////////////////////
	$get_fa_cafa 		= get_fa_cafa($application_id);
    $reference_no 		= $get_fa_cafa['reference_number'];
	$recomended_date_of_amenability	= $get_fa_cafa['recomended_date_of_amenability'];
	
	
	//////////////////////////////end occupier Type////////////////////////
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
		$recomended_total_worker 		= $worker->recomended_total_worker;
		$worker_total 					= $worker->worker_total;
		$worker_id 						= $worker->id;
		
	}
	$form['#attributes'] 	= array('enctype' => "multipart/form-data");
	
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
	$form['worker_id_hidden'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> encryption_decryption_fun('encrypt', $worker_id),
		);	
	$form['recomended_total_worker'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> encryption_decryption_fun('encrypt', $recomended_total_worker),
		);
   $form['recomended_date'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> encryption_decryption_fun('encrypt', $recomended_date_of_amenability),
		);
	 $form['period_for_application'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> encryption_decryption_fun('encrypt', $period_for_application),
		);	
	
	 $form['date_of_amenability_pre'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> encryption_decryption_fun('encrypt', $date_of_amenability),
		);	
		
	$form['amenabilitydate_confirm'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('Date from which the premises is occupied or been taken into use as factory'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	 $form['amenabilitydate_confirm']['amenability_date']= array(
			 '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4">',
			 '#suffix'    		=> '</div></div>',
			 '#type'		 	=> 'textfield',
			 '#title'			=>	t('Date provided by you'),
			 '#default_value' 	=> $date_of_amenability,
			
			'#attributes' => array('class' => array('form-control datepicker_cls'),'readonly' => 'readonly' ),
			 '#required' => TRUE,
	);
	if(!empty($recomended_date_of_amenability)){
		$form['amenabilitydate_confirm']['markup'] 	= array(
  				  
  				'#type'	  => 'markup',
				'#markup' => '<font color="#00498b">Actuall Date found after Inspection :-</font>&nbsp;&nbsp;<strong>'.date('d-m-Y',strtotime($recomended_date_of_amenability)).'</strong>',
				
				);
	}
	
		
	 $form['worker_deatils'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('Worker Details'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	
	$total_worker_plan_approval = view_total_worker($application_id, $user->uid);
	
	$form['worker_deatils']['previous_table'] 	= array(
  			
  			'#type'		=> 'markup',
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

  $form['worker_deatils']['per_worker_men'] = array(
				'#prefix' 			=> '<tr><td><div class="col-xs-12">',
			  	'#suffix' 	 		=> '</div></td>',
			  	'#title'			=>	t('Men'),
			  	'#type' 			=> 'textfield',
			 	'#default_value'	=> $permanent_worker_men, 
			  	'#attributes' 		=> array('class'=>array('form-control')),
			  	'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  	'#required' 		=> TRUE,
			);
  $form['worker_deatils']['per_worker_women'] = array(
				 '#prefix' 				=> '<td><div class="col-xs-12">',
				 '#suffix' 	 			=> '</div></td>',
				 '#title'				=>	t('Women'),
				 '#type' 				=> 'textfield',
				 '#default_value'		=> $permanent_worker_women, 
				 '#attributes' 			=> array('class'=>array('form-control')),
				 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				 '#required' 			=> TRUE,
			);
  $form['worker_deatils']['per_worker_adol_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $permanent_adolescents_male, 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
		);
  
  $form['worker_deatils']['per_worker_adol_women'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Women'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $permanent_adolescents_female, 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			);
  $form['worker_deatils']['per_worker_child_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $permanent_children_male, 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			);
  $form['worker_deatils']['per_worker_child_women'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Women'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $permanent_children_female, 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			);
  $form['worker_deatils']['con_worker_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $contactual_worker_men, 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			);
  $form['worker_deatils']['con_worker_women'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Women'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $contactual_worker_women, 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			);
  $form['worker_deatils']['con_worker_adol_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $contactual_adolescents_male, 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
		);
  $form['worker_deatils']['con_worker_adol_women'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Women'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> $contactual_adolescents_female, 
				  '#attributes' 		=> array('class'=>array('form-control')),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
			);
  $form['worker_deatils']['con_worker_child_men'] = array(
			 '#prefix' 				=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $contactual_children_male, 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
		);
  $form['worker_deatils']['con_worker_child_woman'] = array(
			 '#prefix' 				=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td></tr>',
			  '#title'				=>	t('Women'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $contactual_children_female, 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			);
	
  $form['worker_deatils']['previous_table_end'] 	= array(
  				  '#suffix' => '<tfoot>
				  					<tr><td colspan="12">
										<font color="#00498b">Declared Values by Applicant:-</font>&nbsp;&nbsp;<strong>'.$worker_total.'</strong><br/><font color="#00498b">Actuall Value found after Inspection  :- </font>&nbsp;&nbsp;<strong>'.$recomended_total_worker.'</strong></td>
     
    								</tr>
									<tr><td colspan="12"><font color ="red">*</font> Adolescents (over 15 but under 18 years of age)<br> <font color ="red">*</font> Children(over 14 but under 15 of age)</td></tr>
  								</tfoot>
								</table>
								</div>
								</div>
								</br>',
  				'#type'	  => 'markup',
				'#markup' => '',
				
						
				);
 if($factory_type_id == 3 || $factory_type_id == 1){//echo 'hi';
	$power_details = get_power_generating_station($application_id,$reference_no,$factory_type_id,$service_id);
	foreach($power_details as $power){
		$type_power_station 			= $power->type_power_station;
		$power_unit 					= $power->power_unit;
		$installed_power				= $power->installed_power;
		$power_id						= $power->id; 
		$recommanded_installed_power 	= $power->recommanded_installed_power;
		$recommanded_power_unit 		= $power->recommanded_power_unit;
		$recommande_type_power_station	= $power->recommande_type_power_station;
	}
	$form['powerid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt', $power_id) 
	);
	$form['recommanded_installed_power'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt', $recommanded_installed_power) 
	);
	$form['recommanded_power_unit'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt', $recommanded_power_unit) 
	);
	$form['recommande_type_power_station'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt', $recommande_type_power_station) 
	);
	//print_r($power_details);die();
	 $form['power_details'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('Power Details'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
  $radios_options 			= array('power_generating_station'=>"Power generating station",'other'=>"Other");
	 	
  $form['power_details']['is_generating']= array(
					 '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4">',
					 '#suffix'    		=> '</div>',
					 '#type'		 	=> 'radios',
					 '#title'			=>	t('Type of power generating station'),
					 '#options'   		=> $radios_options,	
					 '#default_value' 	=> $type_power_station,
					 '#required'		=> TRUE,
	);
$form['power_details']['power_type'] 	= array(
					 '#prefix' 				=> '<div class="col-md-4 col-xs-4">',
					 '#suffix' 				=> '</div>',
					 '#title'				=>	t('Unit of power'),
					 '#type' 		 		=> 'select',
					 '#default_value' 		=>  $power_unit,
					 '#options'	 			=>  array('HP'=>'HP','KW'=>'KW'),
					 '#attributes' 			=>  array('class'=>array('form-control')),
					 '#required' 			=>  TRUE,
				);
$form['power_details']['installed_power'] 	= array(
					 '#prefix' 				=> '<div class="col-md-4 col-xs-4">',
					 '#suffix' 				=> '</div></div>',
					  '#title'				=>	t('Power'),
					  '#type' 				=> 'textfield',
					  '#element_validate'	=>  array('DOUBLE_FIELD_VALIDATION'),
					  '#default_value' 		=>  $installed_power,
					  '#attributes' 		=>  array('class'=>array('form-control')),
					  '#required' 			=>  TRUE,
	
				);	
				
	$form['power_details']['markup'] 	= array(
  				  
  				'#type'	  => 'markup',
				'#markup' => '<font color="#00498b">Actuall Value found after Inspection :-</font>&nbsp;&nbsp;<strong>'.$recommanded_installed_power.'('.$recommanded_power_unit.')</strong>',
				);
	}
  
	
	
	
	$form['back_link'] = array(
		'#prefix' => '<div class="row"><div class="col-md-1">',
		'#suffix' => '</div>',
		'#markup' => l(t('<i class="fa fa-angle-left" aria-hidden="true"></i> Back'), 'applicant/applicant-dasboard/', array('html' => TRUE,'attributes' => array('class' => array('btn btn-dark pull-left'))))
  	);
  if($application_status == 'RP'){
	   $form['submit'] = array(
        '#prefix' => '<div class="col-md-1">',
        '#suffix' => '</div>',
        '#attributes' => array('class' => array('btn btn-success')),
        '#type' => 'submit',
        '#value' => 'Save & Continue'
    );
  }
   

	
    return $form; 
        
    
}

//-------------Add Director-------------------------------



function hp_details_repayment_service_submit($form, &$form_state){
	global $user;
	$val   						    =  $form_state['values'];
	$uid 			    			=  $user->uid;
	
	$service_id						=  encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$factory_type_id				=  encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	echo $application_id 				=  encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$application_reference_no		=  encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	$worker_id_hidden				=  encryption_decryption_fun('decrypt',$val['worker_id_hidden']);
	$powerid_hidden					=  encryption_decryption_fun('decrypt',$val['powerid_hidden']);
	$recomended_total_worker		=  encryption_decryption_fun('decrypt',$val['recomended_total_worker']);
	$recommanded_installed_power	=  encryption_decryption_fun('decrypt',$val['recommanded_installed_power']);
	$recommanded_power_unit			=  encryption_decryption_fun('decrypt',$val['recommanded_power_unit']);
	$recommande_type_power_station	=  encryption_decryption_fun('decrypt',$val['recommande_type_power_station']);
	$recomended_date				=  encryption_decryption_fun('decrypt',$val['recomended_date']);
	$period_for_application			=  encryption_decryption_fun('decrypt',$val['period_for_application']);
	$date_of_amenability_pre		=  encryption_decryption_fun('decrypt',$val['date_of_amenability_pre']);
	
	 $per_worker_men					=  $val['per_worker_men'];
	 $per_worker_women				=  $val['per_worker_women'];
	 $per_worker_adol_men			=  $val['per_worker_adol_men'];
	  $per_worker_adol_women			=  $val['per_worker_adol_women'];
	 $per_worker_children_men		=  $val['per_worker_child_men'];
	 $per_worker_children_women		=  $val['per_worker_child_women'];
	 $con_worker_men					=  $val['con_worker_men'];
	 $con_worker_women				=  $val['con_worker_women'];
	 $con_worker_adol_men			=  $val['con_worker_adol_men'];
	 $con_worker_adol_women			=  $val['con_worker_adol_women'];
	 $con_worker_child_men			=  $val['con_worker_child_men'];
	 $con_worker_child_woman			=  $val['con_worker_child_woman'];
	 $is_generating					=  $val['is_generating'];
	 $power_type						=  $val['power_type'];
	 $installed_power				=  $val['installed_power'];
	 $nature_manufacturing			=  $val['nature_manufacturing'];
	$amenability_date				=  $val['amenability_date'];
 	$worker_total					=  $per_worker_men+$per_worker_women+$per_worker_adol_men+$per_worker_adol_women+$per_worker_children_men+$per_worker_children_women+$con_worker_men+$con_worker_women+$con_worker_adol_men+$con_worker_adol_women+$con_worker_child_men+$con_worker_child_woman;
	
	$is_generating					=  $val['is_generating'];
	$how_many_year					=  $val['how_many_year'];
	$factor_amenablity_date			=  $val['factor_amenablity_date'];
	
	if(empty($recomended_date)){
		$recomended_date = $amenability_date;
	}//echo $recomended_date;die;
	//echo $recomended_total_worker.$worker_total;die;
	//echo $is_generating .'------------'.$recommande_type_power_station;die();
	if(($val['power_type'] == $recommanded_power_unit)&& ($recomended_total_worker == $worker_total) && ($installed_power == $recommanded_installed_power) && ($recommande_type_power_station == $is_generating) && $recomended_date==$amenability_date){//echo 'j';die;
		$flag = 1;
		
	}else{
			drupal_set_message('Declared Values by Applicant will be same with Actuall Value found after Inspection in both case.','error');
	}
	if($val['power_type'] == 'KW'){
			
			$installed_power_hp = $val['installed_power']*1.34102;//(1Kw => 1.34102 Hp)
	}
	if($val['power_type' ] == 'HP'){
			$installed_power_hp = $val['installed_power'];
	}
	
	if($flag == 1){
		if($factory_type_id == 1 || $factory_type_id==3){
			
			 $toatl_fees_breakup = toatl_fees_breakup($application_id,$service_id,$factory_type_id,$application_reference_no);
			//print_r($toatl_fees_breakup);die();
	foreach($toatl_fees_breakup as $row_fees){$row_fees_id=$row_fees->id;
				$fees_deatils = array('fees_status'=>0);

				$queryabc 		 =	db_update('fa_calculates_license_fees');
				$queryabc		->	fields($fees_deatils);
				$queryabc		->	condition('id',$row_fees_id,'=');
				$queryabc		->	execute();
	}
			
			$worker_details =array(
			'permanent_worker_men' 		          => $per_worker_men,
			'permanent_worker_women' 			  => $per_worker_women,
			'permanent_adolescents_male'          => $per_worker_adol_men,
			'permanent_adolescents_female' 		  => $per_worker_adol_men,
			'permanent_children_male'             => $per_worker_children_men,
			'permanent_children_female' 	      => $per_worker_children_women,
			'contactual_worker_men' 		      => $con_worker_men,
			'contactual_worker_women' 			  => $con_worker_women,
			'contactual_adolescents_male'         => $con_worker_adol_men,
			'contactual_adolescents_female' 	  => $con_worker_child_men,
			'contactual_children_male'            => $con_worker_child_men,
			'contactual_children_female' 	      => $con_worker_child_woman,
			//'worker_registration_status'   	      => 'RS',
			'worker_total'				     	  => $worker_total,
		);
		//print_r($worker_details);
		$queryapp 		 =	db_update('fa_worker_details');
		$queryapp		 ->	fields($worker_details);
		$queryapp		 ->	condition('id',$worker_id_hidden,'=');
		$queryapp		 ->	condition('service_id',$service_id,'=');
		$r				= $queryapp	 ->	execute();
		
		 $power_details_yearly =array(
		 			'power_unit' 				=> $val['power_type'],
		 			'installed_power'			=> $val['installed_power']	,				
		 			'installed_power_hp'		=> $installed_power_hp,
		 			'service_id'				=> $service_id,
		 			'type_power_station'		=> $is_generating,
		 			'power_application_status'	=> 'RS',
		 			'type_power_station'		=> $is_generating,
						
		 	);
		 	$queryapp 		 =	db_update('fa_power_details');
		 	$queryapp		 ->	fields($power_details_yearly);
		 	$queryapp		 ->	condition('id',$powerid_hidden,'=');
		 	$queryapp		 ->	condition('service_id',$service_id,'=');
		 	$r= $queryapp	 ->	execute();
			
			$approval_status = 	array('date_of_amenability' => $amenability_date,'modification_date'=>date('Y-m-d'));
			$queryabc 		 =	db_update('fa_cafa');
			$queryabc		 ->	fields($approval_status);
			$queryabc		 ->	condition('id',$application_id,'=');
			$queryabc		 ->	condition('service_id',$service_id,'=');
			$queryabc	     ->	condition('factory_typeid',$factory_type_id,'=');
			$queryabc		 ->	condition('reference_number',$application_reference_no,'=');
			$queryabc		 ->	execute();
			del_year($application_id,$service_id,$factory_type_id,$application_reference_no);
		year_calculation_for_license_period($amenability_date,$period_for_application,$service_id,$factory_type_id,$application_reference_no,$application_id);

		}if($factory_type_id == 2){
			
			$worker_details =array(
			'permanent_worker_men' 		          => $per_worker_men,
			'permanent_worker_women' 			  => $per_worker_women,
			'permanent_adolescents_male'          => $per_worker_adol_men,
			'permanent_adolescents_female' 		  => $per_worker_adol_men,
			'permanent_children_male'             => $per_worker_children_men,
			'permanent_children_female' 	      => $per_worker_children_women,
			'contactual_worker_men' 		      => $con_worker_men,
			'contactual_worker_women' 			  => $con_worker_women,
			'contactual_adolescents_male'         => $con_worker_adol_men,
			'contactual_adolescents_female' 	  => $con_worker_child_men,
			'contactual_children_male'            => $con_worker_child_men,
			'contactual_children_female' 	      => $con_worker_child_woman,
			//'worker_registration_status'   	      => 'RS',
			'worker_total'				     	  => $worker_total,
		);
		//print_r($worker_details);
		$queryapp 		 =	db_update('fa_worker_details');
		$queryapp		 ->	fields($worker_details);
		$queryapp		 ->	condition('id',$worker_id_hidden,'=');
		$queryapp		 ->	condition('service_id',$service_id,'=');
		$r				= $queryapp	 ->	execute();
		
		$approval_status = 	array('date_of_amenability' => $amenability_date,'modification_date'=>date('Y-m-d'));
			$queryabc 		 =	db_update('fa_cafa');
			$queryabc		 ->	fields($approval_status);
			$queryabc		 ->	condition('id',$application_id,'=');
			$queryabc		 ->	condition('service_id',$service_id,'=');
			$queryabc	     ->	condition('factory_typeid',$factory_type_id,'=');
			$queryabc		 ->	condition('reference_number',$application_reference_no,'=');
			$queryabc		 ->	execute();
			if($date_of_amenability_pre!=$amenability_date){
				del_year($application_id,$service_id,$factory_type_id,$application_reference_no);
				   year_calculation_for_license_period($amenability_date,$period_for_application,$service_id,$factory_type_id,$application_reference_no,$application_id);
			}
		 
		
		}
		
		
		
		   
	}
	
	
	}
//-------------Fetch director------------------------
