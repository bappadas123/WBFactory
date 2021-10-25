<?php
//$applicationid
//drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/sky-forms.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
function details_hp($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$linknumber,$linkdate,$flagmapp) {	
	global $base_root, $base_path, $user;
 
	$application_id = encryption_decryption_fun('decrypt', $applicationid);
	if(empty($application_id)){
		  	drupal_set_message(('At first you must be filled up the general information of factory then go to second tab'),'warning');
			drupal_goto('applicant/caf-reg/registrtatoin-license/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$linknumber.'/'.$linkdate.'/'.$flagmapp) ;
	 }else{
		 	$get_fa_cafa 				= get_fa_cafa($application_id);
		 	$reference_number 			= $get_fa_cafa['reference_number'];
			$value_factory_profile_type	= $get_fa_cafa['ownership_type'];
			$date_of_amenability		= $get_fa_cafa['date_of_amenability'];
			$is_worker_tab				= $get_fa_cafa['is_worker_tab'];
			$is_year_calculation_tab	= $get_fa_cafa['is_year_calculation_tab'];
	 }
	
	 if(empty($is_year_calculation_tab)){
		  	drupal_set_message(('Please fill up the second tab than fill up the power information'),'warning');
			
			drupal_goto('applicant/caf-reg/details-applyingyear-registration/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$linknumber.'/'.$linkdate.'/'.$flagmapp) ;
	 }  if(empty($is_worker_tab)){
		  	drupal_set_message(('Please fill up the second tab than fill up the power information'),'warning');
			
			drupal_goto('applicant/caf-reg/details-worker-registration/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$linknumber.'/'.$linkdate.'/'.$flagmapp) ;
	 }   
	
	$service_id 				= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 			= encryption_decryption_fun('decrypt',$factory_typeid);
	//////////////////////////////occupier Type////////////////////////
	$get_fa_cafa 				= get_fa_cafa($application_id);
    $reference_no 				= $get_fa_cafa['reference_number'];
	
	//////////////////////////////end occupier Type////////////////////////
	
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
	
	

	$form['power_details'] 	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row"><div class="box box-info"><div class="box-header with-border">
              				<h3 class="box-title">Details of Power to be installed</h3>
			    			</div><div class = "box-body">',
  					
		);
	if($factory_type_id ==1){
		
	 $year_data 				= fetch_year($application_id,$service_id,$factory_type_id,$reference_number);
	
	 $power_generating_station 	= get_power_generating_station($application_id,$reference_number,$factory_type_id,$service_id);
	 foreach($power_generating_station as $row_station){
		 $type_power_station 	= $row_station->type_power_station;
	 }
	 $radios_options 			= array('power_generating_station'=>"Power generating station",'other'=>"Other");
	 
	 $form['power_details']['is_generating']= array(
					'#prefix'	 		=> '<div class="col-xs-12">',
					'#suffix'    		=> '</div><table class="table table-bordered"> 
											<tr>
   											<th>Application Period</th>
											<th>Date of change</th>
     										<th>Unit of power installed or proposed to be installed</th>
	 										<th>Nature and total amount of power installed or proposed to be installed</th>
	 										</tr>',
					 '#type'		 	=> 'radios',
					 '#title'			=>	t('Type of power generating station'),
					 '#options'   		=> $radios_options,	
					 '#default_value' 	=> $type_power_station,
					 '#required'		=> TRUE,
	);
	 $i 			= 1;
	
	foreach($year_data as $row){
	
		$form['power_details']['hp_year1_'.$i] = array(
			'#type' 	 => 'markup',
			'#markup' 	 => '<tr><td>',
		);
		
		
		$power_detials_year = power_detials_year($row->calculate_year,$application_id,$reference_number,$factory_type_id,$service_id);
		$is_power 			= is_power($application_id,$service_id,$factory_type_id,$row->calculate_year,$reference_number);
		
		$form['power_details']['hp_year_'.$i] 	= array(
		  	'#prefix' 			=> '<div class="col-xs-12">',
		  	'#suffix' 	 		=> '</div></td><td>',
			'#type' 			=> 'textfield',
			'#id'				=> 'range',
			'#title'			=>	t('Period-'.$i),
			'#default_value'	=> $row->calculate_year,
			'#attributes' 		=> array('class'=>array('form-control'),'readonly' => 'readonly'),
			'#required' 		=> TRUE,
			);
				
		$form['power_details']['hp_start_year'.$i] 	= array(
			'#prefix' 			=> '<div style="display:none">',
			'#suffix' 	 		=> '</div>',
			'#type' 			=> 'textfield',
			'#id'				=> 'hpstart'.$row->id,
			'#default_value'	=> $row->calculate_starting_year,
			);
							
		$form['power_details']['hp_end_year'.$i] 	= array(
			'#prefix' 			=> '<div style="display:none">',
			'#suffix' 	 		=> '</div>',
			'#type' 			=> 'textfield',
			'#id'				=> 'hpend'.$row->id,
			'#default_value'	=> $row->calculate_end_year,
		);
		
		foreach($power_detials_year as $row_power){
			if($row_power->power_active_inactive ==1){
				$form['power_details']['hp_change_date_'.$i] 	= array(
							  '#prefix' 			=> '<div class="col-xs-12">',
							  '#suffix' 	 		=> '</div></td><td>',
							  '#type' 				=> 'textfield',
							  '#title'				=>	t('Date'),
							  '#id'					=> $row->id,
							  '#default_value'		=> $row_power->change_date,
							  '#attributes' 		=> array('class'=>array('form-control hp2 hprange'),'readonly'=>'readonly'),
							//  '#required' 			=> TRUE,
						);

						$form['power_details']['power_type_'.$i] 	= array(
								 '#prefix' 				=> '<div id="power_div"><div class="col-xs-12">',
								 '#suffix' 				=> '</div></div></td><td>',
								 '#title'				=>	t('Unit of power'),
								 '#type' 		 		=> 'select',
								 '#default_value' 		=>  $row_power->power_unit,
								 '#options'	 			=> array('HP'=>'HP','KW'=>'KW'),
								 '#attributes' 			=> array('class'=>array('form-control')),
								 '#required' 			=> TRUE,
					 	);	
					
						$form['power_details']['installed_power_'.$i] 	= array(
								  '#prefix' 			=> '<div class="col-xs-12">',
								  '#suffix' 	 		=> '</div></td></tr>',
								  '#title'				=>	t('Power'),
								  '#type' 				=> 'textfield',
								  '#element_validate'	=> array('DOUBLE_FIELD_VALIDATION'),
								  '#default_value' 		=>  $row_power->installed_power,
								  '#attributes' 		=> array('class'=>array('form-control')),
								  '#required' 			=> TRUE,
			
					);
				}	
			else{
			//print_r($power_detials_year);die;
				$form['power_details']['hp_change_date_'.$i] 	= array(
							  '#prefix' 			=> '<div class="col-xs-12">',
							  '#suffix' 	 		=> '</div></td><td>',
							  '#type' 				=> 'textfield',
							  '#title'				=>	t('Date'),
							  '#id'					=> $row->id,
							  '#default_value'		=> $row_power->change_date,
							  '#attributes' 		=> array('class'=>array('form-control hp2 hprange'),'readonly'=>'readonly'),
							 // '#required' 			=> TRUE,
						);
				$form['power_details']['power_type_'.$i] 	= array(
								 '#prefix' 				=> '<div class="col-xs-12">',
								 '#suffix' 				=> '</div></td><td>',
								 '#title'				=>	t('Unit of power'),
								 '#type' 		 		=> 'select',
								 '#default_value' 		=>  $row_power->power_unit,
								//'#default_value' 	=> 'KW',
								 '#options'	 			=> array('HP'=>'HP','KW'=>'KW'),
								 '#attributes' 			=> array('class'=>array('form-control')),
								 '#required' 			=> TRUE,
						  
			 	);	
			
				$form['power_details']['installed_power_'.$i] 	= array(
							  '#prefix' 			=> '<div class="col-xs-12">',
							  '#suffix' 	 		=> '</div></td></tr>',
							  '#title'				=>	t('Power'),
							  '#default_value' 		=>  $row_power->installed_power,
							// '#default_value' 	=> '10',
							  '#type' 				=> 'textfield',
							  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
							  '#attributes' 		=> array('class'=>array('form-control')),
							  '#required' 			=> TRUE,
			
					);
		
			}
			
				$form['submit'] = array (
						'#type' 		=> 'submit',
						'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
						'#value' 		=> 'save & Continue'
					); 
				
			}
			
		if(empty($power_detials_year)){
				if($row->is_active_year !=1){

				$form['power_details']['hp_change_date'] 	= array(
							  '#prefix' 			=> '<div class="col-xs-12">',
							  '#suffix' 	 		=> '</div></td><td>',
							  '#type' 				=> 'textfield',
							  '#title'				=>	t('Date'),
							  '#id'					=> $row->id,
							  '#default_value'		=> $row_details->change_date,
							  '#attributes' 		=> array('class'=>array('form-control hp2 hprange'),'readonly'=>'readonly'),
							  //'#required' 			=> TRUE,
						);
				$form['power_details']['power_type'] 	= array(
								 '#prefix' 				=> '<div id="power_div"><div class="col-xs-12">',
								 '#suffix' 				=> '</div></div></td><td>',
								 '#title'				=>	t('Unit of power'),
								 '#type' 		 		=> 'select',
								 '#default_value' 		=>  $row_power->power_unit,
								 '#options'	 			=> array('HP'=>'HP','KW'=>'KW'),
								 '#attributes' 			=> array('class'=>array('form-control')),
								 '#required' 			=> TRUE,
				);	
					
				$form['power_details']['installed_power'] 	= array(
							  '#prefix' 			=> '<div class="col-xs-12">',
							  '#suffix' 	 		=> '</div></td></tr>',
							  '#title'				=>	t('Power'),
							  '#type' 				=> 'textfield',
							  '#element_validate'	=> array('DOUBLE_FIELD_VALIDATION'),
							  '#default_value' 		=>  $row_power->installed_power,
							  '#attributes' 		=> array('class'=>array('form-control')),
							  '#required' 			=> TRUE,
			
						);
				 		$form['submit'] = array (
								'#prefix' 		=> '',  
								'#suffix' 		=> '',
								'#type' 		=> 'submit',
								'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
								'#value' 		=> 'Save'
							); 	
				}
				break;	
				}
				
				$i++;
			}
			
			
		
	$form['power_details']['power_year_table_end'] 	= array(
					'#suffix' => '</table></div></div></div>',
					
			);
			$form['back_link']	 = array(
			'#markup' 		=> l(t('<i class="fa fa-fw fa-chevron-left"></i> Back'),'applicant/decission/', array('html' => TRUE,'attributes'=> array('class'=>array('btn bg-navy margin')))),
		);			
		}
	if($factory_type_id ==3){
		
	 $year_data 				= fetch_year($application_id,$service_id,$factory_type_id,$reference_number);
	
	 $power_generating_station 	= get_power_generating_station($application_id,$reference_number,$factory_type_id,$service_id);
	 foreach($power_generating_station as $row_station){
		 $type_power_station 	= $row_station->type_power_station;
	 }
	 $radios_options 			= array('power_generating_station'=>"Power generating station",'other'=>"Other");
	 
	 $form['power_details']['is_generating']= array(
					'#prefix'	 		=> '<div class="col-xs-12">',
					'#suffix'    		=> '</div><table class="table table-bordered"> 
											<tr>
   											<th>Application Period</th>
											<th>Date of change</th>
     										<th>Unit of power installed or proposed to be installed</th>
	 										<th>Nature and total amount of power installed or proposed to be installed</th>
	 										</tr>',
					 '#type'		 	=> 'radios',
					 '#title'			=>	t('Type of power generating station'),
					 '#options'   		=> $radios_options,	
					 '#default_value' 	=> $type_power_station,
					 '#required'		=> TRUE,
	);
	 $i 			= 1;
	
	foreach($year_data as $row){
	
		$form['power_details']['hp_year1_'.$i] = array(
			'#type' 	 => 'markup',
			'#markup' 	 => '<tr><td>',
		);
		
		
		$power_detials_year = power_detials_year($row->calculate_year,$application_id,$reference_number,$factory_type_id,$service_id);
		$is_power 			= is_power($application_id,$service_id,$factory_type_id,$row->calculate_year,$reference_number);
		
		$form['power_details']['hp_year_'.$i] 	= array(
		  	'#prefix' 			=> '<div class="col-xs-12">',
		  	'#suffix' 	 		=> '</div></td><td>',
			'#type' 			=> 'textfield',
			'#id'				=> 'range',
			'#title'			=>	t('Period-'.$i),
			'#default_value'	=> $row->calculate_year,
			'#attributes' 		=> array('class'=>array('form-control'),'readonly' => 'readonly'),
			'#required' 		=> TRUE,
			);
				
		$form['power_details']['hp_start_year'.$i] 	= array(
			'#prefix' 			=> '<div style="display:none">',
			'#suffix' 	 		=> '</div>',
			'#type' 			=> 'textfield',
			'#id'				=> 'hpstart'.$row->id,
			'#default_value'	=> $row->calculate_starting_year,
			);
							
		$form['power_details']['hp_end_year'.$i] 	= array(
			'#prefix' 			=> '<div style="display:none">',
			'#suffix' 	 		=> '</div>',
			'#type' 			=> 'textfield',
			'#id'				=> 'hpend'.$row->id,
			'#default_value'	=> $row->calculate_end_year,
		);
		
		foreach($power_detials_year as $row_power){
			if($row_power->power_active_inactive ==1){
				$form['power_details']['hp_change_date_'.$i] 	= array(
							  '#prefix' 			=> '<div class="col-xs-12">',
							  '#suffix' 	 		=> '</div></td><td>',
							  '#type' 				=> 'textfield',
							  '#title'				=>	t('Date'),
							  '#id'					=> $row->id,
							  '#default_value'		=> $row_power->change_date,
							  '#attributes' 		=> array('class'=>array('form-control hp2 hprange'),'readonly'=>'readonly'),
							//  '#required' 			=> TRUE,
						);

						$form['power_details']['power_type_'.$i] 	= array(
								 '#prefix' 				=> '<div id="power_div"><div class="col-xs-12">',
								 '#suffix' 				=> '</div></div></td><td>',
								 '#title'				=>	t('Unit of power'),
								 '#type' 		 		=> 'select',
								 '#default_value' 		=>  $row_power->power_unit,
								 '#options'	 			=> array('HP'=>'HP','KW'=>'KW'),
								 '#attributes' 			=> array('class'=>array('form-control')),
								 '#required' 			=> TRUE,
					 	);	
					
						$form['power_details']['installed_power_'.$i] 	= array(
								  '#prefix' 			=> '<div class="col-xs-12">',
								  '#suffix' 	 		=> '</div></td></tr>',
								  '#title'				=>	t('Power'),
								  '#type' 				=> 'textfield',
								  '#element_validate'	=> array('DOUBLE_FIELD_VALIDATION'),
								  '#default_value' 		=>  $row_power->installed_power,
								  '#attributes' 		=> array('class'=>array('form-control')),
								  '#required' 			=> TRUE,
			
					);
				}	
			else{
			//print_r($power_detials_year);die;
				$form['power_details']['hp_change_date_'.$i] 	= array(
							  '#prefix' 			=> '<div class="col-xs-12">',
							  '#suffix' 	 		=> '</div></td><td>',
							  '#type' 				=> 'textfield',
							  '#title'				=>	t('Date'),
							  '#id'					=> $row->id,
							  '#default_value'		=> $row_power->change_date,
							  '#attributes' 		=> array('class'=>array('form-control hp2 hprange'),'readonly'=>'readonly'),
							 // '#required' 			=> TRUE,
						);
				$form['power_details']['power_type_'.$i] 	= array(
								 '#prefix' 				=> '<div class="col-xs-12">',
								 '#suffix' 				=> '</div></td><td>',
								 '#title'				=>	t('Unit of power'),
								 '#type' 		 		=> 'select',
								 '#default_value' 		=>  $row_power->power_unit,
								//'#default_value' 	=> 'KW',
								 '#options'	 			=> array('HP'=>'HP','KW'=>'KW'),
								 '#attributes' 			=> array('class'=>array('form-control')),
								 '#required' 			=> TRUE,
						  
			 	);	
			
				$form['power_details']['installed_power_'.$i] 	= array(
							  '#prefix' 			=> '<div class="col-xs-12">',
							  '#suffix' 	 		=> '</div></td></tr>',
							  '#title'				=>	t('Power'),
							  '#default_value' 		=>  $row_power->installed_power,
							// '#default_value' 	=> '10',
							  '#type' 				=> 'textfield',
							  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
							  '#attributes' 		=> array('class'=>array('form-control')),
							  '#required' 			=> TRUE,
			
					);
		
			}
			
				$form['submit'] = array (
						'#type' 		=> 'submit',
						'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
						'#value' 		=> 'save & Continue'
					); 
				
			}
			
		if(empty($power_detials_year)){
				if($row->is_active_year !=1){

				$form['power_details']['hp_change_date'] 	= array(
							  '#prefix' 			=> '<div class="col-xs-12">',
							  '#suffix' 	 		=> '</div></td><td>',
							  '#type' 				=> 'textfield',
							  '#title'				=>	t('Date'),
							  '#id'					=> $row->id,
							  '#default_value'		=> $row_details->change_date,
							  '#attributes' 		=> array('class'=>array('form-control hp2 hprange'),'readonly'=>'readonly'),
							  //'#required' 			=> TRUE,
						);
				$form['power_details']['power_type'] 	= array(
								 '#prefix' 				=> '<div id="power_div"><div class="col-xs-12">',
								 '#suffix' 				=> '</div></div></td><td>',
								 '#title'				=>	t('Unit of power'),
								 '#type' 		 		=> 'select',
								 '#default_value' 		=>  $row_power->power_unit,
								 '#options'	 			=> array('HP'=>'HP','KW'=>'KW'),
								 '#attributes' 			=> array('class'=>array('form-control')),
								 '#required' 			=> TRUE,
				);	
					
				$form['power_details']['installed_power'] 	= array(
							  '#prefix' 			=> '<div class="col-xs-12">',
							  '#suffix' 	 		=> '</div></td></tr>',
							  '#title'				=>	t('Power'),
							  '#type' 				=> 'textfield',
							  '#element_validate'	=> array('DOUBLE_FIELD_VALIDATION'),
							  '#default_value' 		=>  $row_power->installed_power,
							  '#attributes' 		=> array('class'=>array('form-control')),
							  '#required' 			=> TRUE,
			
						);
				 		$form['submit'] = array (
								'#prefix' 		=> '',  
								'#suffix' 		=> '',
								'#type' 		=> 'submit',
								'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
								'#value' 		=> 'Save'
							); 	
				}
				break;	
				}
				
				$i++;
			}
			
			
		
	$form['power_details']['power_year_table_end'] 	= array(
					'#suffix' => '</table></div></div></div>',
					
			);
	$form['apply_markup'] 	= array(
  			'#type'		=> 'markup',
			'#markup'	=> '<font color="#FF0000">N.B. 0</font>'
		);	
	$form['back_link']	 = array(
			'#markup' 		=> l(t('<i class="fa fa-fw fa-chevron-left"></i> Back'),'applicant/decission/', array('html' => TRUE,'attributes'=> array('class'=>array('btn bg-navy margin')))),
		);			
		}
	if($factory_type_id ==2){
		$form['power_details']['Power_Note'] 	= array(
  				'#markup' => '<div class="row"><div class="col-xs-12"> <font color="#FF0000">N.B. Not Applicable for Factory Type 2m(ii)</font></div></div>',
  			
  			);
	}
		



            return $form; 
        
         }
		 

//-------------Add Director-------------------------------



function details_hp_submit($form, &$form_state){
	$val   					= 	$form_state['values'];
	 global $user;
	 $uid 			    			= $user->uid;
	
	
	$service_id					= encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$service_year				= $val['power_year'];
	$factory_type				= encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$application_id				= encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$application_reference_no	= encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	$is_generating				= $val['is_generating'];
	
	
$year_data = fetch_year($application_id,$service_id,$factory_type,$application_reference_no);
//print_r($year_data);die();
$i = 1;
del_power($application_id,$service_id,$factory_type,$application_reference_no);

foreach($year_data as $row){
	if($val['op'] == "Save"){
		if($is_generating == "power_generating_station"){
		if($val['power_type'] == 'KW'){
			if($val['power_type'] == 'KW'){
			$installed_power_hp = $val['installed_power']*1.34102;//(1Kw => 1.34102 Hp)
		}
		if($val['power_type'] == 'HP'){
			$installed_power_hp = $val['installed_power'];
		}
		
		$power_details_yearly =array(
		
						'power_unit' 				=> $val['power_type'],
						'installed_power'			=> $val['installed_power']	,				
						'installed_power_hp'		=> $installed_power_hp,
						'service_id'				=> $service_id,
						'factory_type'				=> $factory_type,
						'created_by'				=> $uid,
						'application_id'			=> $application_id,
						'application_reference_no'	=> $application_reference_no,
						'power_application_status'	=> 'In',
						'service_year'				=> $row->calculate_year,
						'type_power_station'		=> $is_generating,
						'power_active_inactive'		=> $row->is_active_year,
						'valid_year'				=> $row->calculate_end_year,
					    'valid_time_period'		 	=> $row->valid_time_period,
						'starting_year'				=> $row->calculate_starting_year,
						'change_date'				=> !empty($val['hp_change_date'])?$val['hp_change_date']:NULL,
			);	
		$id = db_insert('fa_power_details')->fields($power_details_yearly)->execute();
		}if($val['power_type'] == 'HP'){
			drupal_set_message('All power unit must be in KW.','warning');
			
			break;
			
		}
	}else{
		if($val['power_type'] == 'KW'){
			$installed_power_hp = $val['installed_power']*1.34102;//(1Kw => 1.34102 Hp)
		}
		if($val['power_type'] == 'HP'){
			$installed_power_hp = $val['installed_power'];
		}
		$power_details_yearly =array(
		
						'power_unit' 				=> $val['power_type'],
						'installed_power'			=> $val['installed_power']	,				
						'installed_power_hp'		=> $installed_power_hp,
						'service_id'				=> $service_id,
						'factory_type'				=> $factory_type,
						'created_by'				=> $uid,
						'application_id'			=> $application_id,
						'application_reference_no'	=> $application_reference_no,
						'power_application_status'	=> 'In',
						'service_year'				=> $row->calculate_year,
						'type_power_station'		=> $is_generating,
						'power_active_inactive'		=> $row->is_active_year,
						'valid_year'				=> $row->calculate_end_year,
					    'valid_time_period'		 	=> $row->valid_time_period,
						'starting_year'				=> $row->calculate_starting_year,
						'change_date'				=> !empty($val['hp_change_date'])?$val['hp_change_date']:NULL,
			
			
		);
		
		$id = db_insert('fa_power_details')->fields($power_details_yearly)->execute();
	}
	}else{
		if($is_generating == "power_generating_station"){
		if($val['power_type_'.$i] == 'KW'){
			if($val['power_type_'.$i] == 'KW'){
			$installed_power_hp = $val['installed_power_'.$i]*1.34102;//(1Kw => 1.34102 Hp)
		}
		if($val['power_type_'.$i] == 'HP'){
			$installed_power_hp = $val['installed_power_'.$i];
		}
		
		$power_details_yearly =array(
		
						'power_unit' 				=> $val['power_type_'.$i],
						'installed_power'			=> $val['installed_power_'.$i]	,				
						'installed_power_hp'		=> $installed_power_hp,
						'service_id'				=> $service_id,
						'factory_type'				=> $factory_type,
						'created_by'				=> $uid,
						'application_id'			=> $application_id,
						'application_reference_no'	=> $application_reference_no,
						'power_application_status'	=> 'In',
						'service_year'				=> $val['hp_year_'.$i],
						'type_power_station'		=> $is_generating,
						'power_active_inactive'		=> $row->is_active_year,
						'valid_year'				=> $row->calculate_end_year,
					    'valid_time_period'		 	=> $row->valid_time_period,
						'starting_year'				=> $row->calculate_starting_year,
						'change_date' 				=>!empty($val['hp_change_date_'.$i])?$val['hp_change_date_'.$i]:NULL,
			
		);
		$id = db_insert('fa_power_details')->fields($power_details_yearly)->execute();
		}if($val['power_type_'.$i] == 'HP'){
			drupal_set_message('All power unit must be in KW.','warning');
			
			break;
			
		}
	}else{
		if($val['power_type_'.$i] == 'KW'){
			$installed_power_hp = $val['installed_power_'.$i]*1.34102;//(1Kw => 1.34102 Hp)
		}
		if($val['power_type_'.$i] == 'HP'){
			$installed_power_hp = $val['installed_power_'.$i];
		}
		$power_details_yearly =array(
		
						'power_unit' 				=> $val['power_type_'.$i],
						'installed_power'			=> $val['installed_power_'.$i]	,				
						'installed_power_hp'		=> $installed_power_hp,
						'service_id'				=> $service_id,
						'factory_type'				=> $factory_type,
						'created_by'				=> $uid,
						'application_id'			=> $application_id,
						'application_reference_no'	=> $application_reference_no,
						'power_application_status'	=> 'In',
						'service_year'				=> $val['hp_year_'.$i],
						'type_power_station'		=> $is_generating,
						'power_active_inactive'		=> $row->is_active_year,
						'valid_year'				=> $row->calculate_end_year,
					    'valid_time_period'		 	=> $row->valid_time_period,
						'starting_year'				=> $row->calculate_starting_year,
						'change_date' 				=>!empty($val['hp_change_date_'.$i])?$val['hp_change_date_'.$i]:NULL,
			
			
		);
		$id = db_insert('fa_power_details')->fields($power_details_yearly)->execute();
	}
	}
	
	
	$i= $i+1;
}

	
}
//-------------Fetch director------------------------
