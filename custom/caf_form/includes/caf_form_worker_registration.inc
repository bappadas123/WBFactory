<?php
//$applicationid
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function caf_form_worker_registration($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$referencenumber) {	//die();
	global $base_root, $base_path, $user;
	
	$application_id = encryption_decryption_fun('decrypt', $applicationid);
	 
	if(empty($application_id)){
		drupal_set_message(('At first you must be filled up the Factory information of factory then go to second tab'),'warning');
	  	drupal_goto('applicant/caf-reg/registration-license/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$referencenumber) ;
	}else{
	
		$get_fa_cafa 				= get_fa_cafa($application_id);
		$reference_number 			= $get_fa_cafa['reference_number'];
		$value_factory_profile_type	= $get_fa_cafa['ownership_type'];
		$license_valid_upto			= $get_fa_cafa['license_valid_upto'];
		$is_year_calculation_tab	= $get_fa_cafa['is_year_calculation_tab'];
		$application_status			= $get_fa_cafa['application_status'];
		$period_for_application		= $get_fa_cafa['period_for_application'];
		$date_of_amenability       	= $get_fa_cafa['date_of_amenability'];

	}
	
	$service_id 	  = encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id  = encryption_decryption_fun('decrypt',$factory_typeid);
	$reference_no  = encryption_decryption_fun('decrypt',$referencenumber);

   
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


	if (!empty($application_id) && $get_fa_cafa['application_status']=='B') {
		$checked =get_checking($application_id,$service_id,$factory_type_id,$reference_no);
		//print_r( $checked);die;
		
		$verify_details      = ($checked['verify_details'])? $checked['verify_details'] : ''; 
		
		$remark_field = explode(',', $checked['verify_details']);
		foreach ($remark_field as $fieldname){
			if($fieldname == 'nature_details'){ $nature_details_ck = "readonly";}
			if($fieldname == 'power_details'){ $power_details_ck = "disabled";}
			if($fieldname == 'worker_details'){ $worker_details_ck = "readonly";}
			if($fieldname == 'date_of_amenability_id'){ $date_of_amenability_ck = "disabled";}
			if($fieldname == 'period_for_application_id'){ $period_for_application_ck = "disabled";}

		}
		
		if(in_array("nature_details", $remark_field)) { $nature_details_check_data = '<i class="fa fa-check text-green verified"></i>'; $nature_field_value= 'blank'; }
		else {  $nature_details_check_data = '<i class="fa fa-edit text-red verified"></i>'; $nature_field_value= "nature_details";}
			
		if(in_array("power_details", $remark_field)) { $power_details_check_data = '<i class="fa fa-check text-green verified"></i>'; $power_field_value= 'blank'; }
		else {  $power_details_check_data = '<i class="fa fa-edit text-red verified"></i>'; $power_field_value= "power_details";}
				
		if(in_array("worker_details", $remark_field)) { $worker_check_data = '<i class="fa fa-check text-green verified"></i>';  $worker_field_value= 'blank'; }
		else {  $worker_check_data = '<i class="fa fa-edit text-red verified"></i>';$worker_field_value= "worker_details"; }
	
		if(in_array("date_of_amenability_id", $remark_field)) { $date_of_amenability_check_data = '<i class="fa fa-check text-green verified"></i>';  $date_of_amenability_field_value= 'blank';}
		else {  $date_of_amenability_check_data = '<i class="fa fa-edit text-red verified"></i>'; $date_of_amenability_field_value= "date_of_amenability_id";}
	
		if(in_array("period_for_application_id", $remark_field)) { $period_for_application_check_data = '<i class="fa fa-check text-green verified"></i>';   $period_for_application_field_value= 'blank';}
		else {  $period_for_application_check_data = '<i class="fa fa-edit text-red verified"></i>'; $period_for_application_field_value= "period_for_application_id";}
	
	}


	$form            	= array();
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
			'#default_value' 	=> $referencenumber
			 
	);
	$form['applicationid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $applicationid
	);
	$form['worker_id_hidden'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> encryption_decryption_fun('encrypt', $worker_id),
		);	
	/*$form['header']            = array(
        '#markup' => t('<div class="content"><h3>Give all details of present year or proposed year</h3>')
    );*/
	$form['reg_year'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('F. State the period of license'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	 $form['reg_year']['factor_amenablity_date'] = array(
		'#prefix' 			=> 	'<div class="row"><div class="col-lg-6 col-md-6 col-sm-6 col-xs-6">',
		'#suffix' 			=> 	'</div>',
		'#type' 			=> 	'textfield',
		'#title'	    	=>	t($date_of_amenability_check_data.'(i). Date from which the premises is occupied or been taken into use as factory'),
		'#required' 		=>  TRUE,
		'#default_value' 	=>  !empty($date_of_amenability)?date('d-m-Y',strtotime($date_of_amenability)):NULL,
		'#attributes' 		=> 	array('class' => array('form-control datepicker_retify'),'placeholder' => '','readonly' => 'readonly',$date_of_amenability_ck  => $date_of_amenability_ck),
			
		);
		$form['reg_year']['how_many_year'] = array(
		'#prefix' 			=> 	'<div  class="col-lg-6 col-md-6 col-sm-6 col-xs-6">',
		'#suffix' 			=> 	'</div></div>',
		'#type' 			=> 	'textfield',
		'#title'	    	=>	t($period_for_application_check_data.'(ii). State the period of license required for date from application date'),
		'#required' 		=>  TRUE,
		'#element_validate'	=>  array('isnumaric_valiadtion'), 
		'#default_value' 	=>  $period_for_application,
		'#attributes' 		=> 	array('class' => array('form-control'),'placeholder' => '',$period_for_application_ck=>$period_for_application_ck),
			
		);
		
	
	 $form['worker_deatils'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t($worker_check_data.'G. Worker Details'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	
	
	
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
				 '#attributes' 			=> array('class'=>array('form-control'),$worker_details_ck=>$worker_details_ck),
				 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				 '#required' 			=> TRUE,
			);
  $form['worker_deatils']['per_worker_adol_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $permanent_adolescents_male, 
			  '#attributes' 		=> array('class'=>array('form-control'),$worker_details_ck=>$worker_details_ck),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
		);
  
  $form['worker_deatils']['per_worker_adol_women'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Women'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $permanent_adolescents_female, 
			  '#attributes' 		=> array('class'=>array('form-control'),$worker_details_ck=>$worker_details_ck),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			);
  $form['worker_deatils']['per_worker_child_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $permanent_children_male, 
			  '#attributes' 		=> array('class'=>array('form-control'),$worker_details_ck=>$worker_details_ck),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			);
  $form['worker_deatils']['per_worker_child_women'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Women'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $permanent_children_female, 
			  '#attributes' 		=> array('class'=>array('form-control'),$worker_details_ck=>$worker_details_ck),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			);
  $form['worker_deatils']['con_worker_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $contactual_worker_men, 
			  '#attributes' 		=> array('class'=>array('form-control'),$worker_details_ck=>$worker_details_ck),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			);
  $form['worker_deatils']['con_worker_women'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Women'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $contactual_worker_women, 
			  '#attributes' 		=> array('class'=>array('form-control'),$worker_details_ck=>$worker_details_ck),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			);
  $form['worker_deatils']['con_worker_adol_men'] = array(
			  '#prefix' 			=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $contactual_adolescents_male, 
			  '#attributes' 		=> array('class'=>array('form-control'),$worker_details_ck=>$worker_details_ck),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
		);
  $form['worker_deatils']['con_worker_adol_women'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Women'),
				  '#type' 				=> 'textfield',
				  '#default_value'		=> $contactual_adolescents_female, 
				  '#attributes' 		=> array('class'=>array('form-control'),$worker_details_ck=>$worker_details_ck),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
			);
  $form['worker_deatils']['con_worker_child_men'] = array(
			 '#prefix' 				=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td>',
			  '#title'				=>	t('Men'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $contactual_children_male, 
			  '#attributes' 		=> array('class'=>array('form-control'),$worker_details_ck=>$worker_details_ck),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
		);
  $form['worker_deatils']['con_worker_child_woman'] = array(
			 '#prefix' 				=> '<td><div class="col-xs-12">',
			  '#suffix' 	 		=> '</div></td></tr>',
			  '#title'				=>	t('Women'),
			  '#type' 				=> 'textfield',
			  '#default_value'		=> $contactual_children_female, 
			  '#attributes' 		=> array('class'=>array('form-control'),$worker_details_ck=>$worker_details_ck),
			  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  '#required' 			=> TRUE,
			);
	
  $form['worker_deatils']['previous_table_end'] 	= array(
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
	//print_r($power_details);die();
	 $form['power_details'] = array(
        '#type' 		=> 'fieldset',
        '#title' 		=> t('H. Power Details'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
  $radios_options 			= array('power_generating_station'=>"Power generating station",'other'=>"Other");
	 	
  $form['power_details']['is_generating']= array(
					 '#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-4">',
					 '#suffix'    		=> '</div>',
					 '#type'		 	=> 'radios',
					 '#title'			=>	t($power_details_check_data.'Type of power generating station'),
					 '#options'   		=> $radios_options,	
					 '#default_value' 	=> $type_power_station,
					 '#attributes' 		=>  array('class'=>array(''),$power_details_ck=> $power_details_ck),
					 '#required'		=> TRUE,
	);
$form['power_details']['power_type'] 	= array(
					 '#prefix' 				=> '<div class="col-md-4 col-xs-4">',
					 '#suffix' 				=> '</div>',
					 '#title'				=>	t($power_details_check_data.'Unit of power'),
					 '#type' 		 		=> 'select',
					 '#default_value' 		=>  $power_unit,
					 '#options'	 			=>  array('HP'=>'HP','KW'=>'KW'),
					 '#attributes' 			=>  array('class'=>array('form-control'),$power_details_ck=> $power_details_ck),
					 '#required' 			=>  TRUE,
				);
$form['power_details']['installed_power'] 	= array(
					 '#prefix' 				=> '<div class="col-md-4 col-xs-4">',
					 '#suffix' 				=> '</div></div>',
					  '#title'				=>	t($power_details_check_data.'Power'),
					  '#type' 				=> 'textfield',
					  '#element_validate'	=>  array('DOUBLE_FIELD_VALIDATION'),
					  '#default_value' 		=>  $installed_power,
					  '#attributes' 		=>  array('class'=>array('form-control'),$power_details_ck=> $power_details_ck),
					  '#required' 			=>  TRUE,
	
				);	
	}
   if($factory_type_id == 2){

	}
	
	$manufacturing_details = get_manufacturing($application_id,$service_id,$factory_type_id,$reference_no);
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
        '#title' 		=> t('I. Nature of Manufacturing process'),
        '#collapsible' 	=> TRUE, // Added
        '#collapsed' 	=> FALSE // Added
    );
	$form['nature_worker']['nature_manufacturing'] 	= array(
							 '#prefix' 			=> '<div class="row"><div class="col-xs-12">',
							 '#suffix' 	 		=> '</div></div>',
							 '#title'			=>	t($nature_details_check_data.'Carried/to be carried on the factory'),
							 '#type' 	 		=> 'textfield',
							 '#default_value'	=> $nature_manufacturing,
							 '#attributes' 		=> array('class'=>array('form-control'),$nature_details_ck=>$nature_details_ck),
							 '#required' 		=>  TRUE,
					 	); 
	$form['back_link'] = array(
		'#prefix' => '<div class="row"><div class="col-md-1">',
		'#suffix' => '</div>',
		'#markup' => l(t('<i class="fa fa-angle-left" aria-hidden="true"></i> Back'), 'applicant-dasboard', array('html' => TRUE,'attributes' => array('class' => array('btn btn-dark pull-left'))))
  	);
  
    $form['submit'] = array(
        '#prefix' => '<div class="col-md-1">',
        '#suffix' => '</div>',
        '#attributes' => array('class' => array('btn btn-success')),
        '#type' => 'submit',
        '#value' => 'Save'
    );
	$form['preview_link'] = array(
		'#prefix' => '<div class="col-md-10">',
        '#suffix' => '</div></div>',
  
		'#markup' => l('DRAFT COPY', 'regsection/preview-varse-basic-informaion/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$referencenumber, array('html' => TRUE,'attributes'=>array('title' => 'Preview as PDF','class'=>array('btn btn-warning pull-right'))))
  		);

	
    return $form; 
        
    }

function caf_form_worker_registration_submit($form, &$form_state){
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
	$how_many_year					=  $val['how_many_year'];
	$factor_amenablity_date			=  date('Y-m-d',strtotime($val['factor_amenablity_date']));
	
	//year_calculation_for_license_period($factor_amenablity_date,$how_many_year,$service_id,$factory_type_id,$application_reference_no,$application_id);
	//die();
		 
	if($is_generating == 'power_generating_station'){
		if($val['power_type'] == 'KW'){
			$flag = 1;
		}else{
			$flag = 0;
			drupal_set_message('Power unit must be in KW.','warning');
		}
	}
	if($is_generating == 'other'){
		if($val['power_type'] == 'HP'){
			$flag = 1;
		}else{	
			$flag = 0;
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
	}if($factory_type_id == 2){
		if($worker_total >=20 && $installed_power==0){
			$flag = 1;
		}else{
			$flag = 0;
			drupal_set_message('You are under Section 2m(ii),Total no of worker will be more than equal to 20 and installed power unit will be 0' ,'error');
		}
	}
	if($factory_type_id == 3){
		//echo $worker_total;die;
		if($installed_power == 0 && $worker_total<=19  && $worker_total != 0){
			$flag = 1;
		}if($installed_power == 0 && $worker_total>19){
			$flag = 0;
			drupal_set_message('You are under Section 85,Total no of worker will be less than equal to 19 and installed power unit will be  0' ,'error');
		
		}if($installed_power != 0 && $worker_total<=9 && $worker_total != 0){
				$flag = 1;
		}if($installed_power != 0 && $worker_total>9){
			$flag = 0;
			drupal_set_message('You are under Section 85,Total no of worker will be less than equal  1 to 9 and installed power unit will be more than0' ,'error');
		
		}
	}
	if($how_many_year!= 0 && ($how_many_year<=15) && $flag == 1){
		$flag = 1;
	}if($how_many_year>15 || $how_many_year==0){
		$flag = 0;
		drupal_set_message('The period of license should be in between 1 to 15 years','error');
	}

if($worker_total == 0){
	$flag = 0;
	drupal_set_message('Total no of worker will not be 0.','error');
}else{

	
	if($flag == 1){
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
				$id = db_insert('fa_worker_details')->fields($worker_details)->execute();
		
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
			$r= $queryapp	 ->	execute();
		}
		
		//print_r($worker_details);die();
		$power_details_yearly =array(
					'power_unit' 				=> $val['power_type'],
					'installed_power'			=> $val['installed_power']	,				
					'installed_power_hp'		=> $installed_power_hp,
					'service_id'				=> $service_id,
					'factory_type'				=> $factory_type_id,
					'created_by'				=> $uid,
					'application_id'			=> $application_id,
					'application_reference_no'	=> $application_reference_no,
					'power_application_status'	=> 'In',
					'type_power_station'		=> $is_generating,
						
			);
	if(empty($powerid_hidden)){
		$id = db_insert('fa_power_details')->fields($power_details_yearly)->execute(); 
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
			$r= $queryapp	 ->	execute();
	}
			
	
		
	$nature_work =array(
				'nature_manufacturing' 		          => $val['nature_manufacturing'],
				'service_id' 		             	  => $service_id,
				'application_id'              		  => $application_id,
				'manufacturing_application_status' 	  => 'In',
				'factory_type'				     	  => $factory_type_id,
				'created_by'				          => $uid,
				'application_reference_no'			  => $application_reference_no,
			);
			
	if(empty($manufacturing_id_hidden)){
		$id = db_insert('fa_nature_manufacturing')->fields($nature_work)->execute();
	}
	else{
		$nature_work =array(
				'nature_manufacturing' => $val['nature_manufacturing'],
				);
				
		$queryapp 		 =	db_update('fa_nature_manufacturing');
		$queryapp		 ->	fields($nature_work);
		$queryapp		 ->	condition('id',$manufacturing_id_hidden,'=');
		$queryapp		 ->	condition('service_id',$service_id,'=');
		$r= $queryapp	 ->	execute();
	}
	
	$cafa_Info = array(
       						'date_of_amenability'		=>  $factor_amenablity_date,
							'period_for_application'	=>  $how_many_year,
							'is_worker_tab'				=>  1,
							'is_year_calculation_tab'	=>	1,
							 'modification_date'		=>date('Y-m-d')

							
	    			);
					
		$queryabc 	= 	db_update('fa_cafa');
		$queryabc	->	fields($cafa_Info);
		$queryabc	->	condition('id', $application_id, '=');
		$queryabc	->	execute();
		
		del_year($application_id,$service_id,$factory_type_id,$application_reference_no);
		year_calculation_for_license_period($factor_amenablity_date,$how_many_year,$service_id,$factory_type_id,$application_reference_no,$application_id);
		remark_input($application_reference_no,$application_id,'In','Worker information is submited for Registration')	;
		drupal_set_message('Basic Information has been saved successfully.');
		//previous_calculation_for_license_period($factor_renewal_date,$previous_license_year,$service_id,$factory_type_id,$application_reference_no,$application_id);   
	}
}
	$form_state['rebuild'] = true;
		
}

