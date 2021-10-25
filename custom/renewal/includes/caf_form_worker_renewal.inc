<?php
//$applicationid
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');

function caf_form_worker_renewal($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$referenceno) {	//die();
	global $base_root, $base_path, $user;
		
 	$application_id = encryption_decryption_fun('decrypt', $applicationid);
	
		 	$get_fa_cafa = get_fa_cafa($application_id);
			
		 	$reference_number 			= $get_fa_cafa['reference_number'];
			$value_factory_profile_type	= $get_fa_cafa['ownership_type'];
			$license_valid_upto			= $get_fa_cafa['license_valid_upto'];
			$is_year_calculation_tab	= $get_fa_cafa['is_year_calculation_tab'];
			$application_status			= $get_fa_cafa['application_status'];
			$period_for_renewal			= $get_fa_cafa['period_for_renewal'];
			$application_period			= $get_fa_cafa['period_for_application'];
			$previous_license_year		= $get_fa_cafa['previous_license_year'];
		//	$worker_total				= $get_fa_cafa['worker_total']; 
			
			$plan_registration_date 	= !empty($get_fa_cafa['registration_date'])? $get_fa_cafa['registration_date']:$get_fa_cafa['backlog_registration_date'];
			$plan_license_date 			= !empty($get_fa_cafa['license_valid_upto'])? $get_fa_cafa['license_valid_upto']:$get_fa_cafa['backlog_license_date'];
			$previous_license_year 		= !empty($previous_license_year)? $previous_license_year:$application_period;
	
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	//////////////////////////////occupier Type////////////////////////
	$get_fa_cafa 		= get_fa_cafa($application_id);
 	$reference_no 		= $get_fa_cafa['reference_number'];
	
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
	$form['worker_total_hidden'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> encryption_decryption_fun('encrypt', $worker_total),
		);

	/*$form['header']            = array(
        '#markup' => t('<div class="content"><h3>Give all details of present year or proposed year</h3>')
    );*/
	$form['renewal_year'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('A. State the period of renewal of a license'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	 $form['renewal_year']['factor_renewal_date'] = array(
		'#prefix' 			=> 	'<div class="row"><div class="col-lg-4 col-md-4 col-sm-4 col-xs-4">',
		'#suffix' 			=> 	'</div>',
		'#type' 			=> 	'textfield',
		'#title'	    	=>	t('(i). Registration date/Vaild upto last license date'),
		'#required' 		=>  TRUE,
		'#default_value' 	=>  !empty($plan_license_date)?date('d-m-Y',strtotime($plan_license_date)):date('d-m-Y',strtotime($plan_registration_date)),
		'#attributes' 		=> 	array('class' => array('form-control'),'placeholder' => '','readonly' => 'readonly'),
			
		);
		$form['renewal_year']['previous_license_year'] = array(
		'#prefix' 			=> 	'<div class="col-lg-4 col-md-4 col-sm-4 col-xs-4">',
		'#suffix' 			=> 	'</div>',
		'#type' 			=> 	'textfield',
		'#title'	    	=>	t('(ii).Previous License was valided for how many years?'),
		'#required' 		=>  TRUE,
		'#default_value' 	=>  $previous_license_year,
		'#attributes' 		=> 	array('class' => array('form-control'),'placeholder' => '','readonly' => 'readonly'),
			
		);
		$form['renewal_year']['how_many_year'] 	= array(
		'#prefix' 			=> '<div class="col-lg-4 col-md-4 col-sm-4 col-xs-4">',
		'#suffix' 			=> '</div></div>',
		'#type' 			=> 'textfield',
		'#maxlength' 		=> 2,
		'#required' 		=> TRUE,
		'#element_validate'	=> array('isnumaric_valiadtion'),  
		'#title'			=>	t('(iii). State the period of license required for date from application date'),
		'#description'		=> t('<font color="#FF0000">(N.B.:- Maximun 15 years)</font>'),
		'#attributes' 		=> 	array('class' => array('form-control'),'placeholder' => ''),
		'#default_value' 	=> $period_for_renewal
	  );
	
	 $form['previous_worker'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('B. Worker Details'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	
	$total_worker_plan_approval = view_total_worker($application_id, $user->uid);
	
	$form['previous_worker']['previous_table'] 	= array(
  			
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

  $form['previous_worker']['per_worker_men'] = array(
				'#prefix' 			=> '<tr><td><div class="col-xs-12">',
			  	'#suffix' 	 		=> '</div></td>',
			  	'#title'			=>	t('Men'),
			  	'#type' 			=> 'textfield',
			 	'#default_value'	=> !empty($permanent_worker_men)?$permanent_worker_men:0, 
			  	'#attributes' 		=> array('class'=>array('form-control')),
			  	'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  	'#required' 		=> TRUE,
			);
  $form['previous_worker']['per_worker_women'] = array(
				 '#prefix' 				=> '<td><div class="col-xs-12">',
				 '#suffix' 	 			=> '</div></td>',
				 '#title'				=>	t('Women'),
				 '#type' 				=> 'textfield',
				 '#default_value'		=> !empty($permanent_worker_women)?$permanent_worker_women:0, 
				 '#attributes' 			=> array('class'=>array('form-control')),
				 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				 '#required' 			=> TRUE,
			);
  $form['previous_worker']['per_worker_adol_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> !empty($permanent_adolescents_male)?$permanent_adolescents_male:0, 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
		);
  
  $form['previous_worker']['per_worker_adol_women'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Women'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> !empty($permanent_adolescents_female)?$permanent_adolescents_female:0, 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			);
  $form['previous_worker']['per_worker_child_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> !empty($permanent_children_male)?$permanent_children_male:0, 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			);
  $form['previous_worker']['per_worker_child_women'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Women'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> !empty($permanent_children_female)?$permanent_children_female:0, 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			);
  $form['previous_worker']['con_worker_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> !empty($contactual_worker_men)?$permanent_children_female:0, 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			);
  $form['previous_worker']['con_worker_women'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Women'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> !empty($contactual_worker_women)?$contactual_worker_women:0, 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			);
  $form['previous_worker']['con_worker_adol_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> !empty($contactual_adolescents_male)?$contactual_adolescents_male:0, 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
		);
  $form['previous_worker']['con_worker_adol_women'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Women'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> !empty($contactual_adolescents_female)?$contactual_adolescents_female:0, 
				  '#attributes' 		=> array('class'=>array('form-control')),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
			);
  $form['previous_worker']['con_worker_child_men'] = array(
			 '#prefix' 				=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> !empty($contactual_children_male)?$contactual_children_male:0, 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
		);
  $form['previous_worker']['con_worker_child_woman'] = array(
			 '#prefix' 				=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td></tr>',
			  '#title'				=>	t('Women'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> !empty($contactual_children_female)?$contactual_children_male:0, 
			  '#attributes' 		=> array('class'=>array('form-control')),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			);
 $form['previous_worker']['previous_table_end'] 	= array(
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
 if($factory_type_id == 3 || $factory_type_id == 1){//echo 'hi';
	$power_details = get_power_generating_station($application_id,$reference_no,$factory_type_id,$service_id);
	
	foreach($power_details as $power){
		$type_power_station = $power->type_power_station;
		$power_unit 		= $power->power_unit;
		$installed_power	= $power->installed_power;
		$power_id			= $power->id; 
	}
	$form['powerid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt', $power_id) 
	);
	$form['installed_power_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt', $installed_power) 
	);
	$form['type_power_station_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt', $type_power_station) 
	);

	 $form['power_details'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('C. Power Details'),
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
					 '#default_value' 	=> !empty($type_power_station)?$type_power_station:'other',
					 '#attributes' 		=> array('class'=>array('')),
					 '#required'		=> TRUE,
	);
$form['power_details']['power_type'] 	= array(
					 '#prefix' 				=> '<div class="col-md-4 col-xs-4">',
					 '#suffix' 				=> '</div>',
					 '#title'				=>	t('Unit of power'),
					 '#type' 		 		=> 'select',
					 '#default_value' 		=> !empty($power_unit)?$power_unit:'HP',
					 '#options'	 			=>  array('HP'=>'HP','KW'=>'KW'),
					 '#attributes' 			=>  array('class'=>array('form-control'),),
					 '#required' 			=>  TRUE,
				);
$form['power_details']['installed_power'] 	= array(
					 '#prefix' 				=> '<div class="col-md-4 col-xs-4">',
					 '#suffix' 				=> '</div></div>',
					  '#title'				=>	t('Power'),
					  '#type' 				=> 'textfield',
					  '#element_validate'	=>  array('DOUBLE_FIELD_VALIDATION'),
					  '#default_value' 		=>  !empty($installed_power)?$installed_power:0,
					  '#attributes' 		=>  array('class'=>array('form-control'),),
					  '#required' 			=>  TRUE,
	
				);	
	}
 
	
	$manufacturing_details = get_manufacturing($application_id,$service_id,$factory_type_id,$reference_no);
	//print_r($manufacturing_details);die($application_id.'--'.$service_id.'--'.$factory_type_id.'--'.$reference_no);
	foreach($manufacturing_details as $manufacturing){
		$nature_manufacturing = $manufacturing->nature_manufacturing;
		$manufacturing_id 	  = $manufacturing->id;
	}
	$form['manufacturing_id_hidden'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> encryption_decryption_fun('encrypt', $manufacturing_id)
			 
	);
	$form['nature_worker'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('D. Nature of Manufacturing process'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	$form['nature_worker']['nature_manufacturing'] 	= array(
		'#prefix' 			=> '<div class="row"><div class="col-xs-12">',
		'#suffix' 	 		=> '</div></div>',
		'#title'			=>	t('Carried/to be carried on the factory'),
		'#type' 	 		=> 'textfield',
		'#default_value'	=> !empty($nature_manufacturing)?$nature_manufacturing:'xyz',
		'#attributes' 		=> array('class'=>array('form-control'),'readonly'=>'readonly'),
		'#required' 		=>  TRUE,
	); 
						
	$form['submit'] = array (
		'#prefix' => '<div class="row"><div class="col-md-1">',
		 '#suffix' => '</div>',
		'#type' 			=> 'submit',
		'#attributes' 		=> array('class' => array('btn btn-success')),
		'#value' 			=> 'Save'
	);
	$form['preview_link'] = array(
		'#prefix' => '<div class="col-md-11">',
		 '#suffix' => '</div></div>',
		
  	//'#markup' => l(t('Preview as PDF'), 'applicant/applicant-dasboard/', array('html' => TRUE,'attributes' => array('class' => array('btn btn-dark space-left') )))
		'#markup' => l('DRAFT COPY', 'regsection/preview-varse-basic-informaion/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'Preview as PDF','class'=>array('btn btn-warning pull-right'))))
  		);
	
    return $form; 
        
    }

function caf_form_worker_renewal_submit($form, &$form_state){
	global $user;
	$val   						    =  $form_state['values'];
	$uid 			    			=  $user->uid;
	$service_id						=  encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$factory_type_id				=  encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$application_id 				=  encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$application_reference_no		=  encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	$worker_id_hidden				=  encryption_decryption_fun('decrypt',$val['worker_id_hidden']);
	$powerid_hidden					=  encryption_decryption_fun('decrypt',$val['powerid_hidden']);
	$manufacturing_id_hidden		=  encryption_decryption_fun('decrypt',$val['manufacturing_id_hidden']);
	$worker_total_hidden			=  encryption_decryption_fun('decrypt',$val['worker_total_hidden']);
	$installed_power_hidden			=  encryption_decryption_fun('decrypt',$val['installed_power_hidden']);
	$type_power_station_hidden		=  encryption_decryption_fun('decrypt',$val['type_power_station_hidden']);
	 
	 
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
     $worker_total					=  $per_worker_men+$per_worker_women+$per_worker_adol_men+$per_worker_children_men+$per_worker_children_women+$con_worker_men+$con_worker_women+$con_worker_adol_men+$con_worker_child_men+$con_worker_child_woman;
	
	$is_generating					=  $val['is_generating'];
	$how_many_year					=	$val['how_many_year'];
	$factor_renewal_date			=	$val['factor_renewal_date'];
	$previous_license_year			=   $val['previous_license_year'];
	$worker_details_flag			=   'NO';	
	$power_details_flag				=   'NO';
	//previous_calculation_for_license_period($factor_renewal_date,$previous_license_year,$service_id,$factory_type_id,$application_reference_no,$application_id);    
	 
	if($is_generating == 'power_generating_station'){
		if($val['power_type'] == 'KW'){
			$flag_unit = 1;
		}else{
			$flag_unit = 0;
			drupal_set_message('Power unit must be in KW.','warning');
		}
	}if($is_generating == 'other'){
		if($val['power_type'] == 'HP'){
			$flag_unit = 1;
		}else{	
			$flag_unit = 0;
			drupal_set_message('Power unit must be in HP.','warning');
		}
	}
	   
		if($val['power_type'] == 'KW'){
			
			$installed_power_hp = $val['installed_power']*1.34102;//(1Kw => 1.34102 Hp)
		}
		if($val['power_type' ] == 'HP'){
			$installed_power_hp = $val['installed_power'];
		}
	if($factory_type_id  == 1){
		if($worker_total>=10 && $installed_power>0){
			$flag = 1;
		}else{
			$flag = 0;
			drupal_set_message('You are under Section 2m(i),Total no of worker will be more than equal to 10 and installed power unit will be more than 0' ,'error');
		}
	}
	if($factory_type_id == 2){
		if($worker_total >=20 && $installed_power==0){
			$flag = 1;
		}else{
			$flag = 0;
			drupal_set_message('You are under Section 2m(ii),Total no of worker will be more than equal to 20 and installed power unit will be 0' ,'error');
		}
	}if($factory_type_id == 3){
		if($installed_power == 0 && $worker_total<=19){
			$flag = 1;
		}if($installed_power == 0 && $worker_total>19){
			$flag = 0;
			drupal_set_message('You are under Section 85,Total no of worker will be less than equal to 19 and installed power unit will be  0' ,'error');
		
		}if($installed_power != 0 && $worker_total<=9){
				$flag = 1;
		}if($installed_power != 0 && $worker_total>9){
			$flag = 0;
			drupal_set_message('You are under Section 85,Total no of worker will be less than equal to 9 and installed power unit will be more than0' ,'error');
		
		}
	}
	if($how_many_year!= 0 && ($how_many_year<=15)){
		$flag_year = 1;
	}if($how_many_year>15 || $how_many_year==0){
		$flag_year = 0;
		drupal_set_message('The period of license should be in between 1 to 15 years','error');
	}
	
	
	if($flag == 1 && $flag_year == 1 && $flag_unit == 1){
		
		
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
					
					'worker_total'				     	  => $worker_total,
					'service_id'				     	  => $service_id,
					'factory_type'				          => $factory_type_id,
					'created_by'				     	  => $uid,
					'application_id'			          => $application_id,
					'worker_registration_status'   	      => 'In',
					'application_reference_no'   	      => $application_reference_no,
					
			
			);
			if(empty($worker_id_hidden)){
				$id_worker 	= db_insert('fa_worker_details')->fields($worker_details)->execute();
		
			}else{
		
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
						
						'worker_total'				     	  => $worker_total,
					);
					
					$queryapp 		 =	db_update('fa_worker_details');
					$queryapp		 ->	fields($worker_details);
					$queryapp		 ->	condition('id',$worker_id_hidden,'=');
					$queryapp		 ->	condition('service_id',$service_id,'=');
					$id_worker= $queryapp	 ->	execute();
				}
			
		
			$power_details_yearly =array(
					'power_unit' 				=> $val['power_type'],
					'installed_power'			=> $val['installed_power']	,				
					'installed_power_hp'		=> $installed_power_hp,
					'service_id'				=> $service_id,
					'factory_type'				=> $factory_type_id,
					'created_by'				=> $uid,
					'application_id'			=> $application_id,
					'application_reference_no'	=> $application_reference_no,
					'power_application_status'	=> 'RENEW',
					'type_power_station'		=> $is_generating,
						
			);
			if(empty($powerid_hidden)){
				$id_power = db_insert('fa_power_details')->fields($power_details_yearly)->execute(); 
			}else{
					$power_details_yearly =array(
					'power_unit' 				=> $val['power_type'],
					'installed_power'			=> $val['installed_power']	,				
					'installed_power_hp'		=> $installed_power_hp,
					'service_id'				=> $service_id,
					'type_power_station'		=> $is_generating,
						
			);
			$queryapp 		 =	db_update('fa_power_details');
			$queryapp		 ->	fields($power_details_yearly);
			$queryapp		 ->	condition('id',$powerid_hidden,'=');
			$queryapp		 ->	condition('service_id',$service_id,'=');
			$id_power= $queryapp	 ->	execute();
		}
	
		
		$cafa_Info = array(
       						
							'period_for_renewal'		=> 	$how_many_year,
							'is_worker_tab'				=>	1,
							'previous_license_year'		=> 	$previous_license_year,
							'modification_date'			=> date('Y-m-d')
	    			);
					
		$queryabc 	= 	db_update('fa_cafa');
		$queryabc	->	fields($cafa_Info);
		$queryabc	->	condition('id', $application_id, '=');
		$queryabc	->	execute();
		
		del_year($application_id,$service_id,$factory_type_id,$application_reference_no);
		year_calculation_for_license_period($factor_renewal_date,$how_many_year,$service_id,$factory_type_id,$application_reference_no,$application_id);
		
		drupal_set_message('Your declaration for Renewal of the License is sucessfully Save');
		remark_input($application_reference_no,$application_id,'In','1st part of renewal is sucessfully save')	;	//previous_calculation_for_license_period($factor_renewal_date,$previous_license_year,$service_id,$factory_type_id,$application_reference_no,$application_id);
	
		
		
	}
}
//-------------Fetch director------------------------
