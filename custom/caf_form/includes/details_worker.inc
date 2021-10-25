<?php
//$applicationid
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');

function details_worker($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$linknumber,$linkdate,$flagmapp) {	
	global $base_root, $base_path, $user;
	
 	$application_id = encryption_decryption_fun('decrypt', $applicationid);
	if(empty($application_id)){
		  	drupal_set_message(('At first you must be filled up the general information of factory then go to second tab'),'warning');
			drupal_goto('applicant/caf-reg/registrtatoin-license/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$linknumber.'/'.$linkdate.'/'.$flagmapp) ;
	 }else{
		 	$get_fa_cafa = get_fa_cafa($application_id);
		 	$reference_number 			= $get_fa_cafa['reference_number'];
			$value_factory_profile_type	= $get_fa_cafa['ownership_type'];
			$date_of_amenability		= $get_fa_cafa['date_of_amenability'];
			$is_year_calculation_tab	= $get_fa_cafa['is_year_calculation_tab'];
			$application_status			= $get_fa_cafa['application_status'];
  
	 }
	 
	if(empty($is_year_calculation_tab)){
		  	drupal_set_message(('Please fill up the second tab than fill up the worker information'),'warning');
			
			drupal_goto('applicant/caf-reg/details-applyingyear-registration/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$linknumber.'/'.$linkdate.'/'.$flagmapp) ;
	 }  
	
	$service_id 	= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id = encryption_decryption_fun('decrypt',$factory_typeid);
	//////////////////////////////occupier Type////////////////////////
	$get_fa_cafa 		= get_fa_cafa($application_id);
    $reference_no 		= $get_fa_cafa['reference_number'];
	
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
	
	$total_worker_plan_approval = view_total_worker($application_id, $user->uid);
	
	$form['previous_worker']['previous_table'] 	= array(
  			
  			'#type'		=> 'markup',
			'#prefix'	=> '<div class="row">
			<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
							<h3>G. Worker Details</h3>
							<h4>Total number of worker during the application of Plan Approval:-'.$total_worker_plan_approval.'</h4>
							<table cellpadding="0" cellspacing="0" border="0" class="table no-margin custom-table-view-dashboard">
							<tr>
							<th width="20%">Application Period</th>
							<th width="10%">Change date</th>
							<th width="10%">Men workers date</th>
							<th>Women workers</th>
							<th colspan="2">Adolescents (over 15 but under 18 years of age)</th>
							<th colspan="2">Children (over 14 but under 15 years of age)</th>
							<!--<th>Same as Previous ?</th>-->
							</tr>'
			
  
			);
  $is_worker =  is_worker($application_id,$service_id,$factory_type_id,$reference_number);
 
  $year_data	= fetch_year($application_id,$service_id,$factory_type_id,$reference_number);
	$i= 1;
	//echo $is_worker;die;
	foreach($year_data as $row){
		/*$form['previous_worker']['worker_year1'] = array(
					'#type' 	 => 'markup',
					'#prefix' 	 =>  '<tr><td>',
			);*/
			
		if($is_worker==1){
			if($row->is_active_year == 1){	
				
			$form['previous_worker']['application_year'] 	= array(
				'#prefix' 			=> '<tr><td><div class="col-xs-12">',
				'#suffix' 	 		=> '</div></td><td>',
				'#type' 			=> 'textfield',
				'#title'			=>	t('Period ').$i,
				'#id'				=> 'range',
				'#attributes' 		=> array('class'=>array('form-control'),'readonly' => 'readonly'),
				'#default_value'	=> $row->calculate_year,
				'#required' 		=> TRUE,
			);
			$form['previous_worker']['worker_start_'.$i] 	= array(
				'#prefix' 			=> '<div style="display:none">',
				'#suffix' 	 		=> '</div>',
				'#title'			=>	t('ccc ').$i,
				'#type' 			=> 'textfield',
				'#id'				=> 'start'.$row->id,
				'#default_value'	=> $row->calculate_starting_year,
			);
			$form['previous_worker']['worker_end_'.$i] 	= array(
				'#prefix' 			=> '<div style="display:none">',
				'#suffix' 	 		=> '</div>',
				'#type' 			=> 'textfield',
				'#id'				=> 'end'.$row->id,
				'#default_value'	=> $row->calculate_end_year,
			);
			$form['previous_worker']['application_date'] 	= array(
						'#prefix' 			=> '<div class="col-xs-12" >',
						'#suffix' 	 		=> '</div></td><td>',
						'#type' 			=> 'textfield',
						'#title'			=>	t('Date'),
						'#attributes' 		=> array('class'=>array('form-control show2 daterange'),'readonly' => 'readonly'),
						'#id'				=> $row->id,
						'#default_value'	=> $row_details->change_date,
			);
			$form['previous_worker']['apply_men'] 	= array(
						  '#prefix' 			=> '<div class="col-xs-12">',
						  '#suffix' 	 		=> '</div></td><td>',
						  '#title'				=>	t('Men'),
						  '#type' 				=> 'textfield',
						 // '#default_value'		=> $row_worker->worker_men, 
						  '#attributes' 		=> array('class'=>array('form-control')),
						  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
						  '#required' 			=> TRUE,
					
			);
					
			$form['previous_worker']['apply_women'] 	= array(
						  '#prefix' 			=> '<div class="col-xs-12">',
						  '#suffix' 			=> '</div></td><td>',
						  '#title'				=>	t('Women'),
						  '#type' 				=> 'textfield',
						 // '#default_value'		=> $row_worker->worker_women,
						  '#attributes' 		=> array('class'=>array('form-control')),
						  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
						  '#required' 			=> TRUE,
								
			);	
			$form['previous_worker']['apply_adolescents_male'] 	= array(
						  '#prefix' 			=> '<div class="col-xs-12">',
						  '#suffix' 			=> '</div></td><td>',
						  '#title'				=>	t('Male'),
						  '#type' 				=> 'textfield',
						  //'#default_value'		=> $row_worker->adolescents_male,
						  '#attributes' 		=> array('class'=>array('form-control')),
						  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
						  '#required' 			=> TRUE,
						);
		  $form['previous_worker']['apply_adolescents_female'] 	= array(
						  '#prefix' 			=> '<div class="col-xs-12">',
						  '#suffix' 			=> '</div></td><td>',
						  '#title'				=>	t('Female'),
						  '#type' 				=> 'textfield',
						  //'#default_value'		=> $row_worker->adolescents_female,
						  '#attributes' 		=> array('class'=>array('form-control')),
						  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
						  '#required' 			=> TRUE,
					
						);
							
		$form['previous_worker']['apply_children_male'] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 			=> '</div></td><td>',
					  '#title'				=>	t('Male'),
					  '#type' 				=> 'textfield',
					 // '#default_value'		=> $row_worker->children_male,
					  '#attributes' 		=> array('class'=>array('form-control')),
					  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					  '#required' 			=> TRUE,
		
				);
	  $form['previous_worker']['apply_children_female'] 	= array(
							  '#prefix' 			=> '<div class="col-xs-12">',
							  '#suffix' 	 		=> '</div></td></tr>',
							  '#title'				=>	t('Female'),
							  '#type' 				=> 'textfield',
							  //'#default_value'		=> $row_worker->children_female,
							  '#attributes' 		=> array('class'=>array('form-control')),
							  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
							  '#required' 			=> TRUE,
					);
				
	  	
	
				
		/*	*/
		break;		
		$i++;			
			
		}
		$form['previous_data'] = array (
				
				'#type' 		=> 'submit',
				'#attributes' 	=> array('class' => array('btn btn-dark pull-right')),
				'#value' 		=> 'Save'
			);
		$form['apply_markup'] 	= array(
  			
  			'#type'		=> 'markup',
			'#markup'	=> '<font color="#FF0000">N.B. Please give the workers details of date from which the premises is occupied or been taken into use as factory</font>'
			
  
			);	 
		}
		
		if($is_worker<1){
			
			if($row->is_active_year != 1){	
			$form['previous_worker']['previous_year'] 	= array(
				'#prefix' 			=> '<tr><td><div class="col-xs-12">',
				'#suffix' 	 		=> '</div></td><td>',
				'#type' 			=> 'textfield',
				'#title'			=>	t('Period ').$i,
				'#id'				=> 'range',
				'#attributes' 		=> array('class'=>array('form-control'),'readonly' => 'readonly'),
				'#default_value'	=> $row->calculate_year,
				'#required' 		=> TRUE,
			);
			$form['previous_worker']['worker_start_'.$i] 	= array(
				'#prefix' 			=> '<div style="display:none">',
				'#suffix' 	 		=> '</div>',
				'#title'			=>	t('ccc ').$i,
				'#type' 			=> 'textfield',
				'#id'				=> 'start'.$row->id,
				'#default_value'	=> $row->calculate_starting_year,
			);
			$form['previous_worker']['worker_end_'.$i] 	= array(
				'#prefix' 			=> '<div style="display:none">',
				'#suffix' 	 		=> '</div>',
				'#type' 			=> 'textfield',
				'#id'				=> 'end'.$row->id,
				'#default_value'	=> $row->calculate_end_year,
			);
			$form['previous_worker']['previous_date'] 	= array(
						'#prefix' 			=> '<div class="col-xs-12" >',
						'#suffix' 	 		=> '</div></td><td>',
						'#type' 			=> 'textfield',
						'#title'			=>	t('Date'),
						'#attributes' 		=> array('class'=>array('form-control show2 daterange'),'readonly' => 'readonly'),
						'#id'				=> $row->id,
						'#default_value'	=> $row_details->change_date,
			);
			$form['previous_worker']['previous_men'] 	= array(
						  '#prefix' 			=> '<div class="col-xs-12">',
						  '#suffix' 	 		=> '</div></td><td>',
						  '#title'				=>	t('Men'),
						  '#type' 				=> 'textfield',
						  '#default_value'		=> $row_worker->worker_men, 
						  '#attributes' 		=> array('class'=>array('form-control')),
						  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
						  '#required' 			=> TRUE,
					
			);
					
			$form['previous_worker']['previous_women'] 	= array(
						  '#prefix' 			=> '<div class="col-xs-12">',
						  '#suffix' 			=> '</div></td><td>',
						  '#title'				=>	t('Women'),
						  '#type' 				=> 'textfield',
						  '#default_value'		=> $row_worker->worker_women,
						  '#attributes' 		=> array('class'=>array('form-control')),
						  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
						  '#required' 			=> TRUE,
								
			);	
			$form['previous_worker']['previous_adolescents_male'] 	= array(
						  '#prefix' 			=> '<div class="col-xs-12">',
						  '#suffix' 			=> '</div></td><td>',
						  '#title'				=>	t('Male'),
						  '#type' 				=> 'textfield',
						  '#default_value'		=> $row_worker->adolescents_male,
						  '#attributes' 		=> array('class'=>array('form-control')),
						  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
						  '#required' 			=> TRUE,
						);
		  $form['previous_worker']['previous_adolescents_female'] 	= array(
						  '#prefix' 			=> '<div class="col-xs-12">',
						  '#suffix' 			=> '</div></td><td>',
						  '#title'				=>	t('Female'),
						  '#type' 				=> 'textfield',
						  '#default_value'		=> $row_worker->adolescents_female,
						  '#attributes' 		=> array('class'=>array('form-control')),
						  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
						  '#required' 			=> TRUE,
					
						);
							
		$form['previous_worker']['previous_children_male'] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 			=> '</div></td><td>',
					  '#title'				=>	t('Male'),
					  '#type' 				=> 'textfield',
					  '#default_value'		=> $row_worker->children_male,
					  '#attributes' 		=> array('class'=>array('form-control')),
					  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					  '#required' 			=> TRUE,
		
				);
	  $form['previous_worker']['previous_children_female'] 	= array(
							  '#prefix' 			=> '<div class="col-xs-12">',
							  '#suffix' 	 		=> '</div></td></tr>',
							  '#title'				=>	t('Female'),
							  '#type' 				=> 'textfield',
							  '#default_value'		=> $row_worker->children_female,
							  '#attributes' 		=> array('class'=>array('form-control')),
							  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
							  '#required' 			=> TRUE,
					);
				
	  $form['previous_service_year'] = array(
					'#type' 			=> 'hidden',
					'#default_value' 	=> $row->calculate_year,
				);
		
	 $form['previous_valid_year'] = array(
			 	'#type' 				=> 'hidden',
			 	'#default_value' 		=> $row->calculate_end_year
			 
			);
	$form['previous_starting_year'] = array(
			'#type' 				=> 'hidden',
			'#default_value' 		=> $row->calculate_starting_year
			 
			);
	$form['previous_calculate_year_id'] = array(
			 '#type' 				=> 'hidden',
			 '#default_value' 		=> $row->id
		);	

				
			$form['previous_data'] = array (
				
				
				'#type' 		=> 'submit',
				'#attributes' 	=> array('class' => array('btn btn-dark pull-right')),
				'#value' 		=> 'Add'
			);
			$form['previous_markup'] 	= array(
  			
  			'#type'		=> 'markup',
			'#markup'	=> '<font color="#FF0000">N.B. Please give the workers details of previous 12 months from which the premises is occupied or been taken into use as factory</font>'
			
  
			);	 
				break;
			}
		}
		
		if($is_worker>1){
			if($row->is_active_year == 1){
				$worker_details = worker_detials_year($row->calculate_year,$application_id,$reference_number,$factory_type_id,$service_id);
				foreach($worker_details as $worker_details){
			$form['previous_worker']['application_year_'.$i] 	= array(
				'#prefix' 			=> '<tr><td><div class="col-xs-12">',
				'#suffix' 	 		=> '</div></td><td>',
				'#type' 			=> 'textfield',
				'#title'			=>	t('Period ').$i,
				'#id'				=> 'range',
				'#attributes' 		=> array('class'=>array('form-control'),'readonly' => 'readonly'),
				'#default_value'	=> $row->calculate_year,
				//'#default_value'	=> $worker_details->service_year,
				'#required' 		=> TRUE,
			);
			$form['previous_worker']['worker_start_'.$i] 	= array(
				'#prefix' 			=> '<div style="display:none">',
				'#suffix' 	 		=> '</div>',
				'#title'			=>	t('ccc ').$i,
				'#type' 			=> 'textfield',
				'#id'				=> 'start'.$row->id,
				'#default_value'	=> $row->calculate_starting_year,
			);
			$form['previous_worker']['worker_end_'.$i] 	= array(
				'#prefix' 			=> '<div style="display:none">',
				'#suffix' 	 		=> '</div>',
				'#type' 			=> 'textfield',
				'#id'				=> 'end'.$row->id,
				'#default_value'	=> $row->calculate_end_year,
			);
			$form['previous_worker']['application_date_'.$i] 	= array(
						'#prefix' 			=> '<div class="col-xs-12" >',
						'#suffix' 	 		=> '</div></td><td>',
						'#type' 			=> 'textfield',
						'#title'			=>	t('Date'),
						'#attributes' 		=> array('class'=>array('form-control show2 daterange'),'readonly' => 'readonly'),
						'#id'				=> $row->id,
						'#default_value'	=> $worker_details->change_date,
			);
			$form['previous_worker']['apply_men_'.$i] 	= array(
						  '#prefix' 			=> '<div class="col-xs-12">',
						  '#suffix' 	 		=> '</div></td><td>',
						  '#title'				=>	t('Men'),
						  '#type' 				=> 'textfield',
						 '#default_value'		=> $worker_details->worker_men, 
						  '#attributes' 		=> array('class'=>array('form-control')),
						  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
						  '#required' 			=> TRUE,
					
			);
					
			$form['previous_worker']['apply_women_'.$i] 	= array(
						  '#prefix' 			=> '<div class="col-xs-12">',
						  '#suffix' 			=> '</div></td><td>',
						  '#title'				=>	t('Women'),
						  '#type' 				=> 'textfield',
						  '#default_value'		=> $worker_details->worker_women,
						  '#attributes' 		=> array('class'=>array('form-control')),
						  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
						  '#required' 			=> TRUE,
								
			);	
			$form['previous_worker']['apply_adolescents_male_'.$i] 	= array(
						  '#prefix' 			=> '<div class="col-xs-12">',
						  '#suffix' 			=> '</div></td><td>',
						  '#title'				=>	t('Male'),
						  '#type' 				=> 'textfield',
						  '#default_value'		=> $worker_details->adolescents_male,
						  '#attributes' 		=> array('class'=>array('form-control')),
						  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
						  '#required' 			=> TRUE,
						);
		  $form['previous_worker']['apply_adolescents_female_'.$i] 	= array(
						  '#prefix' 			=> '<div class="col-xs-12">',
						  '#suffix' 			=> '</div></td><td>',
						  '#title'				=>	t('Female'),
						  '#type' 				=> 'textfield',
						  '#default_value'		=> $worker_details->adolescents_female,
						  '#attributes' 		=> array('class'=>array('form-control')),
						  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
						  '#required' 			=> TRUE,
					
						);
							
		$form['previous_worker']['apply_children_male_'.$i] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 			=> '</div></td><td>',
					  '#title'				=>	t('Male'),
					  '#type' 				=> 'textfield',
					 '#default_value'		=> $worker_details->children_male,
					  '#attributes' 		=> array('class'=>array('form-control')),
					  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					  '#required' 			=> TRUE,
		
				);
	  $form['previous_worker']['apply_children_female_'.$i] 	= array(
							  '#prefix' 			=> '<div class="col-xs-12">',
							  '#suffix' 	 		=> '</div></td></tr>',
							  '#title'				=>	t('Female'),
							  '#type' 				=> 'textfield',
							  '#default_value'		=> $worker_details->children_female,
							  '#attributes' 		=> array('class'=>array('form-control')),
							  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
							  '#required' 			=> TRUE,
					);
				}	
			
				
	  	
	
				
		/*	*/
		//break;		
		$i++;			
			
		}
		if($application_status == 'In'){
			$form['previous_data'] = array (
				
				
				'#type' 		=> 'submit',
				'#attributes' 	=> array('class' => array('btn btn-dark pull-right')),
				'#value' 		=> 'Save & Continue'
			);
		}
		
		$form['apply_markup'] 	= array(
  			
  			'#type'		=> 'markup',
			'#markup'	=> '<font color="#FF0000">N.B. State the workers details of all the periods of license required for date from application date</font>'
			
  
			);	 
		}
		
	}
	$form['previous_worker']['previous_table_end'] 	= array(
				'#suffix' => '</table></div></div></br>',
						
				);	
	
    return $form; 
        
    }
		 



function details_worker_submit($form, &$form_state){

	
	global $user;
	$val   						    =  $form_state['values'];
	$uid 			    			=  $user->uid;
	$service_id						=  encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$factory_type_id				=  encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$application_id 				=  encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$application_reference_no		=  encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	$i=1;
	$year_data = fetch_year($application_id,$service_id,$factory_type_id,$application_reference_no);
	//print_r($year_data);die();
	$i = 1;
	//del_worker($application_id,$service_id,$factory_type_id,$application_reference_no);
	
	
	if($val['op'] == "Add"){
		$worker_total = $val['previous_men']+$val['previous_women']+ $val['previous_adolescents_male']+$val['previous_adolescents_female']+$val['previous_children_male']+$val['previous_children_female'];
					if($factory_type_id==1){
						if($worker_total<10){
								$worker_details_yearly =array(
												'worker_men' 		             => $val['previous_men'],
												'worker_women' 		             => $val['previous_women'],
												'adolescents_male'               => $val['previous_adolescents_male'],
												'adolescents_female' 		     => $val['previous_adolescents_female'],
												'children_male'                  => $val['previous_children_male'],
												'children_female' 	             => $val['previous_children_female'],
												'worker_total'				     => $worker_total,
												'service_id'				     => $service_id,
												'service_year'				     => $val['previous_service_year'],
												'factory_type'				     => $factory_type_id,
												'created_by'				     => $uid,
												'application_id'			     => $application_id,
												'worker_registration_status'   	 => 'In',
												'application_reference_no'   	 => $application_reference_no,
												'worker_active_inactive'		 => 0,
												'valid_year'					 => $val['previous_valid_year'],
												'valid_time_period'				 => 1,
												'starting_year'					 => $val['previous_starting_year'],
												'calculate_year_id'				 => $val['previous_calculate_year_id'],
												'change_date'					 => !empty($val['previous_date'])?$val['previous_date']:NULL,
										
											);
											$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();	

					 }else{
						 drupal_set_message(('Total number workers must be less than 10. Please change the date from which the premises is occupied or been taken into use as factory, in previous tab'),'warning');
				
					 }
				}if($factory_type_id==2){
						if($worker_total<=19){
								$worker_details_yearly =array(
												'worker_men' 		             => $val['previous_men'],
												'worker_women' 		             => $val['previous_women'],
												'adolescents_male'               => $val['previous_adolescents_male'],
												'adolescents_female' 		     => $val['previous_adolescents_female'],
												'children_male'                  => $val['previous_children_male'],
												'children_female' 	             => $val['previous_children_female'],
												'worker_total'				     => $worker_total,
												'service_id'				     => $service_id,
												'service_year'				     => $val['previous_service_year'],
												'factory_type'				     => $factory_type_id,
												'created_by'				     => $uid,
												'application_id'			     => $application_id,
												'worker_registration_status'   	 => 'In',
												'application_reference_no'   	 => $application_reference_no,
												'worker_active_inactive'		 => 0,
												'valid_year'					 => $val['previous_valid_year'],
												'valid_time_period'				 => 1,
												'starting_year'					 => $val['previous_starting_year'],
												'calculate_year_id'				 => $val['previous_calculate_year_id'],
												'change_date'					 => !empty($val['previous_date'])?$val['previous_date']:NULL,
										
											);
											$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();	

					 }else{
						 drupal_set_message(('Total number workers must be less than or equal to 19. Please change the date from which the premises is occupied or been taken into use as factory, in previous tab'),'warning');
				
					 }
				}
				///-------------adding by labani--------------------------
				if($factory_type_id==3){
						if($worker_total<=0){
								$worker_details_yearly =array(
												'worker_men' 		             => $val['previous_men'],
												'worker_women' 		             => $val['previous_women'],
												'adolescents_male'               => $val['previous_adolescents_male'],
												'adolescents_female' 		     => $val['previous_adolescents_female'],
												'children_male'                  => $val['previous_children_male'],
												'children_female' 	             => $val['previous_children_female'],
												'worker_total'				     => $worker_total,
												'service_id'				     => $service_id,
												'service_year'				     => $val['previous_service_year'],
												'factory_type'				     => $factory_type_id,
												'created_by'				     => $uid,
												'application_id'			     => $application_id,
												'worker_registration_status'    => 'In',
												'application_reference_no'   	 => $application_reference_no,
												'worker_active_inactive'		 => 0,
												'valid_year'					 => $val['previous_valid_year'],
												'valid_time_period'				 => 1,
												'starting_year'					 => $val['previous_starting_year'],
												'calculate_year_id'				 => $val['previous_calculate_year_id'],
												'change_date'					 => !empty($val['previous_date'])?$val['previous_date']:NULL,
										
											);
											$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();	

					 }else{
						 drupal_set_message(('Total number workers must be less than 0. Please change the date from which the premises is occupied or been taken into use as factory, in previous tab'),'warning');
				
					 }
				}
		
	}
	if($val['op'] == "Save"){
		$year_data	= fetch_year($application_id,$service_id,$factory_type_id,$application_reference_no);
		foreach($year_data as $year){
				$worker_total = $val['apply_men']+$val['apply_women']+ $val['apply_adolescents_male']+$val['apply_adolescents_female']+$val['apply_children_male']+$val['apply_children_female'];
				if($factory_type_id==1){
					if($worker_total>=10){
					if($year->is_active_year == 1){
								$worker_details_yearly =array(
												'worker_men' 		             => $val['apply_men'],
												'worker_women' 		             => $val['apply_women'],
												'adolescents_male'               => $val['apply_adolescents_male'],
												'adolescents_female' 		     => $val['apply_adolescents_female'],
												'children_male'                  => $val['apply_children_male'],
												'children_female' 	             => $val['apply_children_female'],
												'worker_total'				     => $worker_total,
												'service_id'				     => $service_id,
												'service_year'				     => $year->calculate_year,
												'factory_type'				     => $factory_type_id,
												'created_by'				     => $uid,
												'application_id'			     => $application_id,
												'worker_registration_status'   	 => 'In',
												'application_reference_no'   	 => $application_reference_no,
												'worker_active_inactive'		 => 1,
												'valid_year'					 => $year->calculate_end_year,
												'valid_time_period'				 => $year->valid_time_period,
												'starting_year'					 => $year->calculate_starting_year,
												'calculate_year_id'				 => $year->id,
												'change_date'					 => !empty($val['application_date'])?$val['application_date']:NULL,
										
											);
											$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
					}
								

			}else{
				drupal_set_message(('Total number workers must be equal or more than 10'),'warning');
				break;
			}
				}
				if($factory_type_id==2){
					if($worker_total>19){
					if($year->is_active_year == 1){
								$worker_details_yearly =array(
												'worker_men' 		             => $val['apply_men'],
												'worker_women' 		             => $val['apply_women'],
												'adolescents_male'               => $val['apply_adolescents_male'],
												'adolescents_female' 		     => $val['apply_adolescents_female'],
												'children_male'                  => $val['apply_children_male'],
												'children_female' 	             => $val['apply_children_female'],
												'worker_total'				     => $worker_total,
												'service_id'				     => $service_id,
												'service_year'				     => $year->calculate_year,
												'factory_type'				     => $factory_type_id,
												'created_by'				     => $uid,
												'application_id'			     => $application_id,
												'worker_registration_status'   	 => 'In',
												'application_reference_no'   	 => $application_reference_no,
												'worker_active_inactive'		 => 1,
												'valid_year'					 => $year->calculate_end_year,
												'valid_time_period'				 => $year->valid_time_period,
												'starting_year'					 => $year->calculate_starting_year,
												'calculate_year_id'				 => $year->id,
												'change_date'					 => !empty($val['application_date'])?$val['application_date']:NULL,
										
											);
											$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
					}
								

			}
					else{
							drupal_set_message(('Total number workers must be more than 19'),'warning');
							break;
				}
			}
			///-------------adding by labani--------------------------
			    if($factory_type_id==3){
						$worker_details_yearly =array(
												'worker_men' 		             => $val['apply_men'],
												'worker_women' 		             => $val['apply_women'],
												'adolescents_male'               => $val['apply_adolescents_male'],
												'adolescents_female' 		     => $val['apply_adolescents_female'],
												'children_male'                  => $val['apply_children_male'],
												'children_female' 	             => $val['apply_children_female'],
												'worker_total'				     => $worker_total,
												'service_id'				     => $service_id,
												'service_year'				     => $year->calculate_year,
												'factory_type'				     => $factory_type_id,
												'created_by'				     => $uid,
												'application_id'			     => $application_id,
												'worker_registration_status'   	 => 'In',
												'application_reference_no'   	 => $application_reference_no,
												'worker_active_inactive'		 => 1,
												'valid_year'					 => $year->calculate_end_year,
												'valid_time_period'				 => $year->valid_time_period,
												'starting_year'					 => $year->calculate_starting_year,
												'calculate_year_id'				 => $year->id,
												'change_date'					 => !empty($val['application_date'])?$val['application_date']:NULL,
										
											);
											$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
				
								

					}
				}
				
		}
		
	
	if($val['op'] == "Save & Continue"){
	
		$year_data	= fetch_year($application_id,$service_id,$factory_type_id,$application_reference_no);
		del_worker($application_id,$service_id,$factory_type_id,$application_reference_no);
		foreach($year_data as $year){
			 if($year->is_active_year == 1){
				
				 $worker_total = $val['apply_men_'.$i]+$val['apply_women_'.$i]+ $val['apply_adolescents_male_'.$i]+$val['apply_adolescents_female_'.$i]+$val['apply_children_male_'.$i]+$val['apply_children_female_'.$i];
				if($factory_type_id==1){
				if($worker_total>=10){
				
					$worker_details_yearly =array(
												'worker_men' 		             => $val['apply_men_'.$i],
												'worker_women' 		             => $val['apply_women_'.$i],
												'adolescents_male'               => $val['apply_adolescents_male_'.$i],
												'adolescents_female' 		     => $val['apply_adolescents_female_'.$i],
												'children_male'                  => $val['apply_children_male_'.$i],
												'children_female' 	             => $val['apply_children_female_'.$i],
												'worker_total'				     => $worker_total,
												'service_id'				     => $service_id,
												'service_year'				     => $year->calculate_year,
												'factory_type'				     => $factory_type_id,
												'created_by'				     => $uid,
												'application_id'			     => $application_id,
												'worker_registration_status'   	 => 'In',
												'application_reference_no'   	 => $application_reference_no,
												'worker_active_inactive'		 => 1,
												'valid_year'					 => $year->calculate_end_year,
												'valid_time_period'				 => $year->valid_time_period,
												'starting_year'					 => $year->calculate_starting_year,
												'calculate_year_id'				 => $year->id,
												'change_date'					 => !empty($val['application_date_'.$i])?$val['application_date_'.$i]:NULL,
										
											);
											$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
											$cafa_Info = array('is_worker_tab'	=>1);
									$queryabc = db_update('fa_cafa');
									$queryabc->fields($cafa_Info);
									$queryabc->condition('id', $application_id, '=');
									$queryabc->execute();
		
											
					
			 }else{
				 	del_worker($application_id,$service_id,$factory_type_id,$application_reference_no);
					drupal_set_message(('Total number workers must be equal or more than 10'),'warning');
					break;
					}
				}
				if($factory_type_id==2){
					if($worker_total>19){
						$worker_details_yearly =array(
												'worker_men' 		             => $val['apply_men_'.$i],
												'worker_women' 		             => $val['apply_women_'.$i],
												'adolescents_male'               => $val['apply_adolescents_male_'.$i],
												'adolescents_female' 		     => $val['apply_adolescents_female_'.$i],
												'children_male'                  => $val['apply_children_male_'.$i],
												'children_female' 	             => $val['apply_children_female_'.$i],
												'worker_total'				     => $worker_total,
												'service_id'				     => $service_id,
												'service_year'				     => $year->calculate_year,
												'factory_type'				     => $factory_type_id,
												'created_by'				     => $uid,
												'application_id'			     => $application_id,
												'worker_registration_status'   	 => 'In',
												'application_reference_no'   	 => $application_reference_no,
												'worker_active_inactive'		 => 1,
												'valid_year'					 => $year->calculate_end_year,
												'valid_time_period'				 => $year->valid_time_period,
												'starting_year'					 => $year->calculate_starting_year,
												'calculate_year_id'				 => $year->id,
												'change_date'					 => !empty($val['application_date_'.$i])?$val['application_date_'.$i]:NULL,
										
											);
											$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
											$cafa_Info = array('is_worker_tab'	=>1);
											$queryabc = db_update('fa_cafa');
											$queryabc->fields($cafa_Info);
											$queryabc->condition('id', $application_id, '=');
											$queryabc->execute();
		
											
					
			 		}else{
						del_worker($application_id,$service_id,$factory_type_id,$application_reference_no);
						drupal_set_message(('Total number workers must be more than 19'),'warning');
						break;
					}
				}
				if($factory_type_id==3){
					
					
								$worker_details_yearly =array(
												'worker_men' 		             => $val['apply_men_'.$i],
												'worker_women' 		             => $val['apply_women_'.$i],
												'adolescents_male'               => $val['apply_adolescents_male_'.$i],
												'adolescents_female' 		     => $val['apply_adolescents_female_'.$i],
												'children_male'                  => $val['apply_children_male_'.$i],
												'children_female' 	             => $val['apply_children_female_'.$i],
												'worker_total'				     => $worker_total,
												'service_id'				     => $service_id,
												'service_year'				     => $year->calculate_year,
												'factory_type'				     => $factory_type_id,
												'created_by'				     => $uid,
												'application_id'			     => $application_id,
												'worker_registration_status'   	 => 'In',
												'application_reference_no'   	 => $application_reference_no,
												'worker_active_inactive'		 => 1,
												'valid_year'					 => $year->calculate_end_year,
												'valid_time_period'				 => $year->valid_time_period,
												'starting_year'					 => $year->calculate_starting_year,
												'calculate_year_id'				 => $year->id,
												'change_date'					 => !empty($val['application_date_'.$i])?$val['application_date_'.$i]:NULL,
										
											);
											$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
											$cafa_Info = array('is_worker_tab'	=>1,'is_year_calculation_tab'		=> 1,);
											$queryabc = db_update('fa_cafa');
											$queryabc->fields($cafa_Info);
											$queryabc->condition('id', $application_id, '=');
											$queryabc->execute();
					}
				
			$i++;					

			}
			
			
		}
		
		
	}

}

