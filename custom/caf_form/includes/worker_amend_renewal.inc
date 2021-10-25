<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function worker_amend_renewal($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$number,$datevalidity,$flagmapp)
{
	global $base_root, $base_path;
	
    $form	= array();
	$application_id = encryption_decryption_fun('decrypt', $applicationid);
			 	$get_fa_cafa = get_fa_cafa($application_id);
		 	$reference_number 			= $get_fa_cafa['reference_number'];
			$value_factory_profile_type	= $get_fa_cafa['ownership_type'];
			$date_of_amenability		= $get_fa_cafa['date_of_amenability'];
			$date_of_renewal			= $get_fa_cafa['date_of_renewal'];
			$is_year_calculation_tab	= $get_fa_cafa['is_year_calculation_tab'];
	
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
			'#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
											<h3>H. Do you have any amend in previous year</h3>'
			);
  
	
	$form['previous_worker']['start_markup'] 	= array(
		'#type'	=> 'markup',
		'#prefix' => '<div class="box-body">',
		'#suffix' => '</div>',
 	);
	
	$form['previous_worker']['workers_backlog'] 	= array(
		'#type'	=> 'markup',
		'#prefix' => '<div id="worker_id" class="col-lg-12 col-md-12 col-sm-12">',
		'#suffix' => '</div>',
 	);
	
	
	if (empty($form_state['worker_no'])) {
				$form_state['worker_no'] = 1;
			}
			for ($i = 0; $i < $form_state['worker_no']; $i++) {
		
				$form['previous_worker']['workers_backlog']['period_'.$i] = array(
					'#prefix' 		=> '<div class="col-md-3 col-xs-3">',
					'#suffix' 		=> '</div>',
					'#type' 		=> 'textfield',
					'#title'		=>	t('Licence Period'),
					'#size' 		=> 150,
					'#attributes' 	=> array('multiple' => 'multiple'),
				);
				$form['previous_worker']['workers_backlog']['year_'.$i] = array(
					'#prefix' 		=> '<div class="col-md-3 col-xs-3">',
					'#suffix' 		=> '</div>',
					'#type'			=> 'textfield',
					'#title' 		=>	t('Change Date'),
					'#size' 		=> 150,
					'#attributes' 	=> array('multiple' => 'multiple','class' => array('datepicker_cls')),
				);
				$form['previous_worker']['workers_backlog']['proposed_worker_'.$i] 	= array(
					 '#prefix' 			=> '<div class="col-md-3 col-xs-3">',
					 '#suffix' 			=> '</div>',
					 '#title'			=>	t('Propose Worker'),
					 '#default_value'	=> '',
					 '#type' 			=> 'textfield',
					 '#size' 			=> 150,
					'#attributes' 		=> array('multiple' => 'multiple'),
					 );
				$form['previous_worker']['workers_backlog']['total_worker_'.$i] 	= array(
					 '#prefix' 			=> '<div class="col-md-3 col-xs-3">',
					 '#suffix' 			=> '</div>',
					 '#title'			=>	t('Amendment Worker'),
					 '#default_value'	=> '',
					 '#type' 			=> 'textfield',
					 '#size' 			=> 150,
					'#attributes' 		=> array('multiple' => 'multiple'),
					 );
			}
				$form['previous_worker']['workers_backlog']['add_conditions'] = array(
				'#prefix' 		=> '<div class="col-md-12 col-xs-12">',
				'#suffix' 		=> '</div></div></div>',
				'#attributes' 	=> array('class' => array('btn btn-dark')),
				'#type' 		=> 'submit',
				'#value' 		=> t('Add More'),
				'#submit' 		=> array('workers_add_more_add_one'),
				'#ajax' 		=> array(
					'callback' 		=> 'workers_add_more_callback',
					'wrapper' 		=> 'worker_id',
				),
			 );	
	
	
		// ---------------  Add more text box ends ---------------------------------
		
	
	
    return $form; 
	
}

function workers_add_more_add_one($form, &$form_state) {
	
	if (!isset($form_state['worker_no'])) {
		$form_state['worker_no'] = 0;
		$form_state['worker_no']++;
	}

	$form_state['worker_no']++;
	$form_state['rebuild'] = TRUE;
}

function workers_add_more_callback($form, $form_state) {
	return $form['previous_worker']['workers_backlog'];
	
}



function caf_form_worker_renewal_submit($form, &$form_state){

	
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
						if($worker_total>=10){
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
												'worker_registration_status'   	 => 'RENEW',
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
						 drupal_set_message(('Total number workers must be more than 10. Please change the date from which the premises is occupied or been taken into use as factory, in previous tab'),'warning');
						  }
					}if($factory_type_id==2){
						if($worker_total>=19){
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
												'worker_registration_status'   	 => 'RENEW',
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
						 drupal_set_message(('Total number workers must be more than 19. Please change the date from which the premises is occupied or been taken into use as factory, in previous tab'),'warning');
				
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
												'worker_registration_status'   	 => 'RENEW',
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
					if($worker_total>=19){
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
												'worker_registration_status'   	 => 'RENEW',
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
							drupal_set_message(('Total number workers must be equal or more than 19'),'warning');
							break;
				}
			}
				
		}
		
	}
	if($val['op'] == "Save & Continue"){
		$year_data	= fetch_year($application_id,$service_id,$factory_type_id,$application_reference_no);
		del_worker($application_id,$service_id,$factory_type_id,$application_reference_no);
		
				$c = 0;
					while(!empty($val['period_'.$c]))
					{
						$cafa_wordker_old =  array(
						'app_id'   			=> $application_id,
						'app_reference_no' 	=> $reference_no,
						'period' 	   		=> $val['period_'.$c],
						'year' 	    		=> $val['year_'.$c],
						'proposed_worker'	=> $val['proposed_worker_'.$c],
						'total_worker' 	    => $val['total_worker_'.$c],
						'status' 			=> '0',
						);	
					
						db_insert('fa_cafa_workers')->fields($cafa_wordker_old)->execute();
						
						$c++;
				}
		
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
												'worker_registration_status'   	 => 'RENEW',
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
						drupal_set_message(('Total number workers must be equal or more than 10'),'warning');
						break;
						}
					}if($factory_type_id==2){
					if($worker_total>=19){
					
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
												'worker_registration_status'   	 => 'RENEW',
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
						drupal_set_message(('Total number workers must be equal or more than 19'),'warning');
						break;
					}
				}
			$i++;					
			}
		}
		
	}
	 
}
	