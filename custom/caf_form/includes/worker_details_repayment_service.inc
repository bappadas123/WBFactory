<?php
drupal_add_js("https://code.jquery.com/jquery-1.12.4.js");
drupal_add_js("https://code.jquery.com/ui/1.12.1/jquery-ui.js");
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function worker_details_repayment_service($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$referencenumber) {	
	global $base_root, $base_path, $user;
	
 	 $application_id = encryption_decryption_fun('decrypt', $applicationid);
	if(empty($application_id)){
		  
	 }else{
		 	$get_fa_cafa 						= get_fa_cafa($application_id);
		 	$reference_number 					= $get_fa_cafa['reference_number'];
			$value_factory_profile_type			= $get_fa_cafa['ownership_type'];
			$date_of_amenability				= $get_fa_cafa['date_of_amenability'];
			$is_year_calculation_tab			= $get_fa_cafa['is_year_calculation_tab'];
			$factory_reg_identification_number	= $get_fa_cafa['factory_reg_identification_number'];
			$application_status					= $get_fa_cafa['application_status'];
			
  
	 }
	//echo $application_status;die();
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	//////////////////////////////occupier Type////////////////////////
	$get_fa_cafa 		= get_fa_cafa($application_id);
    $reference_no 		= encryption_decryption_fun('decrypt',$referencenumber);
	
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
			'#default_value' 	=> $referencenumber
	);
	$form['applicationid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $applicationid
	);	
	$form['application_status'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> encryption_decryption_fun('encrypt', $application_status)
	);
	
	if($factory_type_id == 2){
	}
	$form['yearly_worker']['worker_year_table'] 	= array(
  				'#type'		=> 'markup',
				'#prefix'	=> '<div class="row"><div class="box box-info"><div class="box-header with-border">
              	<h3 class="box-title">Application Number:-'.$factory_reg_identification_number.'<br/>G.Worker Details</h3>
                </div><div class = "box-body">
				<table class="table table-bordered"> <tr>
   								<th>Application Period</th>
   								<th>Change date</th>
								<th>Men workers date</th>
    							<th>Women workers</th>
	 							<th colspan="2">Adolescents (over 15 but under 18 years of age)</th>
	 							<th colspan="2">Children (over 14 but under 15 years of age)</th>
								<!--<th>Same as Previous ?</th>-->
 								</tr>'
			
  
			);	
	$radios_options 			= array('Yes'=>"Yes",'No'=>"No");
	$year_data					= fetch_year($application_id,$service_id,$factory_type_id,$reference_number);
	$i 							= 1;
	foreach($year_data as $row){
		$form['yearly_worker']['worker_year1_'.$i] = array(
						'#type' 	 => 'markup',
						'#markup' 	 =>  '<tr><td>',
					);
	$worker_detials_year = worker_detials_year($row->calculate_year,$application_id,$reference_number,$factory_type_id,$service_id);
	$is_worker			 =	is_worker($application_id,$service_id,$factory_type_id,$row->calculate_year,$reference_number);
	$form['yearly_worker']['worker_year_'.$i] 	= array(
		  '#prefix' 			=> '<div class="col-xs-12">',
		  '#suffix' 	 		=> '</div></td><td>',
		  '#type' 				=> 'textfield',
		  '#title'				=>	t('Period ').$i,
		  '#attributes' 		=> array('class'=>array('form-control '),'readonly' => 'readonly'),
		  '#default_value'		=> $row->calculate_year,
		  '#required' 			=> TRUE,
		);
		
	foreach($worker_detials_year as $row_worker){
		$worker_application_status = $row_worker->worker_registration_status;
		if($row->is_active_year == 1){
				$form['yearly_worker']['worker_date_'.$i] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 	 		=> '</div></td><td>',
					  '#type' 				=> 'textfield',
					  '#title'				=>	t('Date'),
					  '#default_value'		=> $row_worker->change_date,
					  '#attributes' 		=> array('class'=>array('form-control daterange'),'readonly'=>'readonly'),
				);
				$form['yearly_worker']['worker_men_'.$i] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 	 		=> '</div></td><td>',
					  '#title'				=>	t('Men'),
					  '#type' 				=> 'textfield',
					  '#default_value'		=> $row_worker->worker_men, 
					  '#attributes' 		=> array('class'=>array('form-control')),
					  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				);
				$form['yearly_worker']['worker_women_'.$i] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 			=> '</div></td><td>',
					  '#title'				=>	t('Women'),
					  '#type' 				=> 'textfield',
					  '#default_value'		=> $row_worker->worker_women,
				      '#attributes' 		=> array('class'=>array('form-control')),
					  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				);	
				$form['yearly_worker']['adolescents_male_'.$i] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 			=> '</div></td><td>',
					  '#title'				=>	t('Male'),
					  '#type' 				=> 'textfield',
				      '#default_value'		=> $row_worker->adolescents_male,
					  '#attributes' 		=> array('class'=>array('form-control')),
					  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					  
				);
				$form['yearly_worker']['adolescents_female_'.$i] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 			=> '</div></td><td>',
					  '#title'				=>	t('Female'),
					  '#type' 				=> 'textfield',
					  '#default_value'		=> $row_worker->adolescents_female,
					  '#attributes' 		=> array('class'=>array('form-control')),
					  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				);
						
				$form['yearly_worker']['children_male_'.$i] 	= array(
						  '#prefix' 			=> '<div class="col-xs-12">',
						  '#suffix' 			=> '</div></td><td>',
						  '#title'				=>	t('Male'),
						  '#type' 				=> 'textfield',
						  '#default_value'		=> $row_worker->children_male,
						  '#attributes' 		=> array('class'=>array('form-control')),
						  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			  );
			 $form['yearly_worker']['children_female_'.$i] 	= array(
						  '#prefix' 			=> '<div class="col-xs-12">',
						  '#suffix' 	 		=> '</div></td></tr>',
						  '#title'				=>	t('Female'),
						  '#type' 				=> 'textfield',
						  '#default_value'		=> $row_worker->children_female,
						  '#attributes' 		=> array('class'=>array('form-control')),
						  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			 );
			/*	$form['yearly_worker']['is_previous_'.$i]= array(
						'#prefix' 			=> '<div class="col-xs-12">',
					  	'#suffix' 			=> '</div></td></tr>',
						'#type'		 		=> 'radios',
						'#title'			=>	t('worker'),
						'#options'   		=> $radios_options,	
						'#default_value' 	=> $is_previous,
						'#required' 		=> TRUE,
					 
				);*/
			}
		else{
		$form['yearly_worker']['worker_date_'.$i] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 	 		=> '</div></td><td>',
					  '#type' 				=> 'textfield',
					  '#title'				=>	t('Date'),
					  '#default_value'		=> $row_worker->change_date,
					  '#attributes' 		=> array('class'=>array('form-control daterange'),'readonly'=>'readonly' ),
					  '#required' 			=> TRUE,
				);
					
				$form['yearly_worker']['worker_men_'.$i] 	= array(
						'#prefix' 			=> '<div class="col-xs-12">',
						'#suffix' 	 		=> '</div></td><td>',
						'#title'			=>	t('Men'),
						'#type' 			=> 'textfield',
						'#attributes' 		=> array('class'=>array('form-control')),
						'#default_value'	=> $row_worker->worker_men, 
						'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
						'#required' 		=> TRUE,
						
			
				);
			
				$form['yearly_worker']['worker_women_'.$i] 	= array(
						'#prefix' 			  => '<div class="col-xs-12">',
						'#suffix' 	 		  => '</div></td><td>',
						'#title'			  =>	t('Women'),
						'#type' 			  => 'textfield',
						'#attributes' 		  => array('class'=>array('form-control')),
						'#default_value'	  => $row_worker->worker_women,
						'#element_validate'	  => array('QUANTITY_FIELD_VALIDATION'),
						'#required' 		  => TRUE,
						
						
				);	
				$form['yearly_worker']['adolescents_male_'.$i] 	= array(
						'#prefix' 			 => '<div class="col-xs-12">',
						'#suffix' 	 		 => '</div></td><td>',
						'#title'			 =>	t('Male'),
						'#type' 			 => 'textfield',
						'#default_value'	 => $row_worker->adolescents_male,
						'#attributes' 		 => array('class'=>array('form-control')),
						'#element_validate'	 => array('QUANTITY_FIELD_VALIDATION'),
						'#required' 		 => TRUE,
						
					);
				$form['yearly_worker']['adolescents_female_'.$i] 	= array(
						'#prefix' 			=> '<div class="col-xs-12">',
						'#suffix' 	 		=> '</div></td><td>',
						'#title'			=>	t('Female'),
						'#type' 			=> 'textfield',
						'#default_value'	=> $row_worker->adolescents_female,
						'#attributes' 		=> array('class'=>array('form-control')),
						'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
						'#required' 		=> TRUE,
						
			
				);
				$form['yearly_worker']['children_male_'.$i] 	= array(
						 '#prefix' 			=> '<div class="col-xs-12">',
						 '#suffix' 	 		=> '</div></td><td>',
						 '#title'			=>	t('Male'),
						 '#type' 			=> 'textfield',
						 '#default_value'	=> $row_worker->children_male,
						 '#attributes' 		=> array('class'=>array('form-control')),
						 '#element_validate'=> array('QUANTITY_FIELD_VALIDATION'),
						 '#required' 		=> TRUE,
						
					
				 );
				  $form['yearly_worker']['children_female_'.$i] 	= array(
						 '#prefix' 				=> '<div class="col-xs-12">',
						  '#suffix' 	 		=> '</div></td></tr>',
						  '#title'				=>	t('Female'),
						  '#type' 				=> 'textfield',
						  '#default_value'		=> $row_worker->children_female,
						  '#attributes' 		=> array('class'=>array('form-control')),
						  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
						  '#required' 			=> TRUE,
						  
					
						);
				
	 
	 			/*$form['yearly_worker']['is_previous_'.$i]= array(
						'#prefix' 			=> '<div class="col-xs-12">',
					  	'#suffix' 			=> '</div></td></tr>',
						
					 
				);*/
					
	}
				
				
		
	  $form['markup_note'] 	= array(
			 '#prefix' 			=> '<div class="col-xs-12">',
			 '#suffix' 	 		=> '</div>',
			 '#type' 			=> 'markup',
			 '#markup'			=> '<font color="#FF0000"><b>Please note:-Date of subsequrent years has been populated based on first input. However appliant may change the values in next year(s) manually if requried.</b></font>',
						
						
					
				 );	
		$form['submit'] = array (
	  		
	  		
	  		'#type' 		=> 'submit',
	   		'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
	  		'#value' 		=> 'save & Continue'
		); 
	}	
	if(empty($worker_detials_year)){
		 if($row->is_active_year != 1){
				$form['yearly_worker']['worker_date'] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 	 		=> '</div></td><td>',
					  '#type' 				=> 'textfield',
					  '#title'				=>	t('Date'),
					  '#default_value'		=> $row_details->change_date,
					  '#attributes' 		=> array('class'=>array('form-control datepicker'),'readonly'=>'readonly'),
					  '#required' 			=> TRUE,
				
					);
					$form['yearly_worker']['worker_men'] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 	 		=> '</div></td><td>',
					  '#title'				=>	t('Men'),
					  '#type' 				=> 'textfield',
					  '#default_value'		=> $row_worker->worker_men, 
					  '#attributes' 		=> array('class'=>array('form-control')),
					  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					  '#required' 			=> TRUE,
				
					);
				
					$form['yearly_worker']['worker_women'] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 			=> '</div></td><td>',
					  '#title'				=>	t('Women'),
					  '#type' 				=> 'textfield',
					  '#default_value'		=> $row_worker->worker_women,
				      '#attributes' 		=> array('class'=>array('form-control')),
					  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					  '#required' 			=> TRUE,
							
				);	
				$form['yearly_worker']['adolescents_male'] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 			=> '</div></td><td>',
					  '#title'				=>	t('Male'),
					  '#type' 				=> 'textfield',
				      '#default_value'		=> $row_worker->adolescents_male,
					  '#attributes' 		=> array('class'=>array('form-control')),
					  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					  '#required' 			=> TRUE,
					);
					$form['yearly_worker']['adolescents_female'] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 			=> '</div></td><td>',
					  '#title'				=>	t('Female'),
					  '#type' 				=> 'textfield',
					  '#default_value'		=> $row_worker->adolescents_female,
					  '#attributes' 		=> array('class'=>array('form-control')),
					  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					  '#required' 			=> TRUE,
				
					);
						
					$form['yearly_worker']['children_male'] 	= array(
						  '#prefix' 			=> '<div class="col-xs-12">',
						  '#suffix' 			=> '</div></td><td>',
						  '#title'				=>	t('Male'),
						  '#type' 				=> 'textfield',
						  '#default_value'		=> $row_worker->children_male,
						  '#attributes' 		=> array('class'=>array('form-control')),
						  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
						  '#required' 			=> TRUE,
			
					);
					$form['yearly_worker']['children_female'] 	= array(
						  '#prefix' 			=> '<div class="col-xs-12">',
						  '#suffix' 	 		=> '</div></td></tr>',
						  '#title'				=>	t('Female'),
						  '#type' 				=> 'textfield',
						  '#default_value'		=> $row_worker->children_female,
						  '#attributes' 		=> array('class'=>array('form-control')),
						  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
						  '#required' 			=> TRUE,
					);
			
			}
		$form['previous_data'] = array (
	  		
	  		
	  		'#type' 		=> 'submit',
	   		'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
	  		'#value' 		=> 'Save'
		); 
			break;		
				
		}
		$i=$i+1;  	
   }
 
	$form['yearly_worker']['worker_year_table_end'] 	= array(
					'#suffix' => '</table></div></div></div>',
					
			);	
	$form['worker_application_status'] = array(
				'#type' 			=> 'hidden',
				'#default_value' 	=> encryption_decryption_fun('encrypt', $worker_application_status)
			 
	);
	
	$form['back_link']	 = array(
					
				'#markup' 		=> l(t('<i class="fa fa-fw fa-chevron-left"></i> Back'),'applicant/decission/', array('html' => TRUE,'attributes'=> array('class'=>array('btn bg-navy margin')))),
		);
					
       return $form; 
        
    }

function worker_details_repayment_service_submit($form, &$form_state){
	
	global $user;
	$val   						    =  $form_state['values'];
	$uid 			    			=  $user->uid;
    $service_id						=  encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$factory_type_id				=  encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$application_id 				=  encryption_decryption_fun('decrypt',$val['applicationid_hidden']);;
	$application_reference_no		=  encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	$worker_application_status		=  encryption_decryption_fun('decrypt',$val['application_status']);
	if($worker_application_status == "RP"){
		$worker_details	= get_worker_details_service($service_id,$factory_type_id,$application_id,$application_reference_no);
	 	foreach($worker_details as $worker){
				worker_details_log($worker->id);
			}
		del_worker($application_id,$service_id,$factory_type_id,$application_reference_no);
	
   	 }if($worker_application_status == "RS"){
	    	del_worker($application_id,$service_id,$factory_type_id,$application_reference_no);
	}
	$year_data = fetch_year($application_id,$service_id,$factory_type_id,$application_reference_no);
	
	$i = 1;
	/*foreach($year_data as $row){
			$worker_total 	= $val['worker_men']+$val['worker_women']+ $val['adolescents_male']+$val['adolescents_female']+$val['children_male']+$val['children_female'];
			if($factory_type_id==1){
				if($worker_total>=10){
				$worker_details_yearly =array(
			
					'worker_men' 		             => $val['worker_men'],
					'worker_women' 		             => $val['worker_women'],
					'adolescents_male'               => $val['adolescents_male'],
					'adolescents_female' 		     => $val['adolescents_female'],
					'children_male'                  => $val['children_male'],
					'children_female' 	             => $val['children_female'],
					'worker_total'				     => $worker_total,
					'service_id'				     => $service_id,
					'service_year'				     => $row->calculate_year,
					'factory_type'				     => $factory_type_id,
					'created_by'				     => $uid,
					'application_id'			     => $application_id,
					'worker_registration_status'   	 => 'RS',
					'application_reference_no'   	 => $application_reference_no,
				    'worker_active_inactive'		 => $row->is_active_year,
					'valid_year'					 => $row->calculate_end_year,
					'valid_time_period'				 => $row->valid_time_period,
					'starting_year'					 => $row->calculate_starting_year,
					'calculate_year_id'				 =>  $row->id,
					'change_date'					 => $val['worker_date'],
						
				);
				
				
		
			$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
			$cafa_Info 		= array('is_worker_tab'	=>1);
		    		$queryabc 		= db_update('fa_cafa');
       				$queryabc		->fields($cafa_Info);
        			$queryabc		->condition('id', $application_id, '=');
        			$queryabc		->execute();
			} else{
				 drupal_set_message('Factory type is 2m(i).Total workers will be 10 or more than 10','error');
				
			}
			}/*if($factory_type_id==2){
				if($worker_total>19){
				$worker_details_yearly =array(
			
					'worker_men' 		             => $val['worker_men'],
					'worker_women' 		             => $val['worker_women'],
					'adolescents_male'               => $val['adolescents_male'],
					'adolescents_female' 		     => $val['adolescents_female'],
					'children_male'                  => $val['children_male'],
					'children_female' 	             => $val['children_female'],
					'worker_total'				     => $worker_total,
					'service_id'				     => $service_id,
					'service_year'				     => $row->calculate_year,
					'factory_type'				     => $factory_type_id,
					'created_by'				     => $uid,
					'application_id'			     => $application_id,
					'worker_registration_status'   	 => 'In',
					'application_reference_no'   	 => $application_reference_no,
				    'worker_active_inactive'		 => $row->is_active_year,
					'valid_year'					 => $row->calculate_end_year,
					'valid_time_period'				 => $row->valid_time_period,
					'starting_year'			 		 => $row->calculate_starting_year,
					'calculate_year_id'				 =>  $row->id,
					'change_date'					 => $val['worker_date'],
					
				);
				
		
			$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
			$cafa_Info 		= array('is_worker_tab'	=>1);
		    		$queryabc 		= db_update('fa_cafa');
       				$queryabc		->fields($cafa_Info);
        			$queryabc		->condition('id', $application_id, '=');
        			$queryabc		->execute();
			} else{
				  drupal_set_message('Factory type is 2m(ii).Total workers will be more than 19','error');
				 
				}
			}if($factory_type_id==3){
				if($worker_total<=10){
				$worker_details_yearly =array(
			
					'worker_men' 		             => $val['worker_men'],
					'worker_women' 		             => $val['worker_women'],
					'adolescents_male'               => $val['adolescents_male'],
					'adolescents_female' 		     => $val['adolescents_female'],
					'children_male'                  => $val['children_male'],
					'children_female' 	             => $val['children_female'],
					'worker_total'				     => $worker_total,
					'service_id'				     => $service_id,
					'service_year'				     => $row->calculate_year,
					'factory_type'				     => $factory_type_id,
					'created_by'				     => $uid,
					'application_id'			     => $application_id,
					'worker_registration_status'   	 => 'In',
					'application_reference_no'   	 => $application_reference_no,
				    'worker_active_inactive'		 => $row->is_active_year,
					'valid_year'					 => $row->calculate_end_year,
					'valid_time_period'				 => $row->valid_time_period,
					'starting_year'	     			 => $row->calculate_starting_year,
					'calculate_year_id'				 =>  $row->id,
					'change_date'					 =>  $val['worker_date'],
						
				);
				
			
					$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
					$cafa_Info 		= array('is_worker_tab'	=>1);
		    		$queryabc 		= db_update('fa_cafa');
       				$queryabc		->fields($cafa_Info);
        			$queryabc		->condition('id', $application_id, '=');
        			$queryabc		->execute();
			} else{
				   drupal_set_message('Factory type is section 85.Total workers will be more than 9 or less than 9','error');
				   
				}
			}
			$i= $i+1;
	}*/
	if($val['op'] == "Save"){
		foreach($year_data as $row){
			$worker_total 	= $val['worker_men']+$val['worker_women']+ $val['adolescents_male']+$val['adolescents_female']+$val['children_male']+$val['children_female'];
			if($factory_type_id==1){
				if($worker_total>=10){
				$worker_details_yearly =array(
			
					'worker_men' 		             => $val['worker_men'],
					'worker_women' 		             => $val['worker_women'],
					'adolescents_male'               => $val['adolescents_male'],
					'adolescents_female' 		     => $val['adolescents_female'],
					'children_male'                  => $val['children_male'],
					'children_female' 	             => $val['children_female'],
					'worker_total'				     => $worker_total,
					'service_id'				     => $service_id,
					'service_year'				     => $row->calculate_year,
					'factory_type'				     => $factory_type_id,
					'created_by'				     => $uid,
					'application_id'			     => $application_id,
					'worker_registration_status'   	 => 'RP',
					'application_reference_no'   	 => $application_reference_no,
				    'worker_active_inactive'		 => $row->is_active_year,
					'valid_year'					 => $row->calculate_end_year,
					'valid_time_period'				 => $row->valid_time_period,
					'starting_year'					 => $row->calculate_starting_year,
					'calculate_year_id'				 =>  $row->id,
					'change_date'					 => $val['worker_date'],
						
				);
				
				
		
			$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
			$cafa_Info 		= array('is_worker_tab'	=>1);
		    		$queryabc 		= db_update('fa_cafa');
       				$queryabc		->fields($cafa_Info);
        			$queryabc		->condition('id', $application_id, '=');
        			$queryabc		->execute();
			} else{
				 drupal_set_message('Factory type is 2m(i).Total workers will be 10 or more than 10','error');
				
			}
			}if($factory_type_id==2){
				if($worker_total>19){
				$worker_details_yearly =array(
			
					'worker_men' 		             => $val['worker_men'],
					'worker_women' 		             => $val['worker_women'],
					'adolescents_male'               => $val['adolescents_male'],
					'adolescents_female' 		     => $val['adolescents_female'],
					'children_male'                  => $val['children_male'],
					'children_female' 	             => $val['children_female'],
					'worker_total'				     => $worker_total,
					'service_id'				     => $service_id,
					'service_year'				     => $row->calculate_year,
					'factory_type'				     => $factory_type_id,
					'created_by'				     => $uid,
					'application_id'			     => $application_id,
					'worker_registration_status'   	 => 'RS',
					'application_reference_no'   	 => $application_reference_no,
				    'worker_active_inactive'		 => $row->is_active_year,
					'valid_year'					 => $row->calculate_end_year,
					'valid_time_period'				 => $row->valid_time_period,
					'starting_year'			 		 => $row->calculate_starting_year,
					'calculate_year_id'				 =>  $row->id,
					'change_date'					 => $val['worker_date'],
					
				);
				
		
			$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
			$cafa_Info 		= array('is_worker_tab'	=>1);
		    		$queryabc 		= db_update('fa_cafa');
       				$queryabc		->fields($cafa_Info);
        			$queryabc		->condition('id', $application_id, '=');
        			$queryabc		->execute();
			} else{
				  drupal_set_message('Factory type is 2m(ii).Total workers will be more than 19','error');
				 
				}
			}if($factory_type_id==3){
				if($worker_total<=10){
				$worker_details_yearly =array(
			
					'worker_men' 		             => $val['worker_men'],
					'worker_women' 		             => $val['worker_women'],
					'adolescents_male'               => $val['adolescents_male'],
					'adolescents_female' 		     => $val['adolescents_female'],
					'children_male'                  => $val['children_male'],
					'children_female' 	             => $val['children_female'],
					'worker_total'				     => $worker_total,
					'service_id'				     => $service_id,
					'service_year'				     => $row->calculate_year,
					'factory_type'				     => $factory_type_id,
					'created_by'				     => $uid,
					'application_id'			     => $application_id,
					'worker_registration_status'   	 => 'RS',
					'application_reference_no'   	 => $application_reference_no,
				    'worker_active_inactive'		 => $row->is_active_year,
					'valid_year'					 => $row->calculate_end_year,
					'valid_time_period'				 => $row->valid_time_period,
					'starting_year'	     			 => $row->calculate_starting_year,
					'calculate_year_id'				 =>  $row->id,
					'change_date'					 =>  $val['worker_date'],
						
				);
				
			
					$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
					$cafa_Info 		= array('is_worker_tab'	=>1);
		    		$queryabc 		= db_update('fa_cafa');
       				$queryabc		->fields($cafa_Info);
        			$queryabc		->condition('id', $application_id, '=');
        			$queryabc		->execute();
			} else{
				   drupal_set_message('Factory type is section 85.Total workers will be more than 9 or less than 9','error');
				   
				}
			}
			$i= $i+1;
	}
	}else{
		foreach($year_data as $row){
			$worker_total = $val['worker_men_'.$i]+$val['worker_women_'.$i]+ $val['adolescents_male_'.$i]+$val['adolescents_female_'.$i]+$val['children_male_'.$i]+$val['children_female_'.$i];
			if($factory_type_id==1){
				if($worker_total>=10){
				$worker_details_yearly =array(
			
					'worker_men' 		             => $val['worker_men_'.$i],
					'worker_women' 		             => $val['worker_women_'.$i],
					'adolescents_male'               => $val['adolescents_male_'.$i],
					'adolescents_female' 		     => $val['adolescents_female_'.$i],
					'children_male'                  => $val['children_male_'.$i],
					'children_female' 	             => $val['children_female_'.$i],
					'change_date'					 => $val['worker_date_'.$i],
					'worker_total'				     => $worker_total,
					'service_id'				     => $service_id,
					'service_year'				     => $val['worker_year_'.$i],
					'factory_type'				     => $factory_type_id,
					'created_by'				     => $uid,
					'application_id'			     => $application_id,
					'worker_registration_status'   	 => 'RS',
					'application_reference_no'   	 => $application_reference_no,
				    'worker_active_inactive'		 => $row->is_active_year,
					'valid_year'					 => $row->calculate_end_year,
					'valid_time_period'				 => $row->valid_time_period,
					'starting_year'					 => $row->calculate_starting_year,
					'calculate_year_id'				 =>  $row->id,
					
				);
				
				
		
			$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
			$cafa_Info 		= array('is_worker_tab'	=>1);
		    		$queryabc 		= db_update('fa_cafa');
       				$queryabc		->fields($cafa_Info);
        			$queryabc		->condition('id', $application_id, '=');
        			$queryabc		->execute();
			} else{
				 drupal_set_message('Factory type is 2m(i).Total workers will be 10 or more than 10','error');
				
			}
			}if($factory_type_id==2){
				if($worker_total>19){
				$worker_details_yearly =array(
			
					'worker_men' 		             => $val['worker_men_'.$i],
					'worker_women' 		             => $val['worker_women_'.$i],
					'adolescents_male'               => $val['adolescents_male_'.$i],
					'adolescents_female' 		     => $val['adolescents_female_'.$i],
					'children_male'                  => $val['children_male_'.$i],
					'children_female' 	             => $val['children_female_'.$i],
					'change_date'					 => $val['worker_date_'.$i],
					'worker_total'				     => $worker_total,
					'service_id'				     => $service_id,
					'service_year'				     => $val['worker_year_'.$i],
					'factory_type'				     => $factory_type_id,
					'created_by'				     => $uid,
					'application_id'			     => $application_id,
					'worker_registration_status'   	 => 'RS',
					'application_reference_no'   	 => $application_reference_no,
				    'worker_active_inactive'		 => $row->is_active_year,
					'valid_year'					 => $row->calculate_end_year,
					'valid_time_period'				 => $row->valid_time_period,
					'starting_year'			 		 => $row->calculate_starting_year,
					'calculate_year_id'				 =>  $row->id,
					
				);
				
		
			$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
					$cafa_Info 		= array('is_worker_tab'	=>1);
		    		$queryabc 		= db_update('fa_cafa');
       				$queryabc		->fields($cafa_Info);
        			$queryabc		->condition('id', $application_id, '=');
        			$queryabc		->execute();
			} else{
				  drupal_set_message('Factory type is 2m(ii).Total workers will be more than 19','error');
				 
				}
			}if($factory_type_id==3){
				if($worker_total<=10){
				$worker_details_yearly =array(
			
					'worker_men' 		             => $val['worker_men_'.$i],
					'worker_women' 		             => $val['worker_women_'.$i],
					'adolescents_male'               => $val['adolescents_male_'.$i],
					'adolescents_female' 		     => $val['adolescents_female_'.$i],
					'children_male'                  => $val['children_male_'.$i],
					'children_female' 	             => $val['children_female_'.$i],
					'change_date'					 => $val['worker_date_'.$i],
					'worker_total'				     => $worker_total,
					'service_id'				     => $service_id,
					'service_year'				     => $row->calculate_year,
					'factory_type'				     => $factory_type_id,
					'created_by'				     => $uid,
					'application_id'			     => $application_id,
					'worker_registration_status'   	 => 'RS',
					'application_reference_no'   	 => $application_reference_no,
				    'worker_active_inactive'		 => $row->is_active_year,
					'valid_year'					 => $row->calculate_end_year,
					'valid_time_period'				 => $row->valid_time_period,
					'starting_year'	     			 => $row->calculate_starting_year,
					'calculate_year_id'				 =>  $row->id,
					
					
				);
				
			
					$id = db_insert('fa_worker_details')->fields($worker_details_yearly)->execute();
					$cafa_Info 		= array('is_worker_tab'	=>1);
		    		$queryabc 		= db_update('fa_cafa');
       				$queryabc		->fields($cafa_Info);
        			$queryabc		->condition('id', $application_id, '=');
        			$queryabc		->execute();
			} else{
				   drupal_set_message('Factory type is section 85.Total workers will be more than 9 or less than 9','error');
				   
				}
			}
			
			
		$i= $i+1;
	}
	}
	
	
	 
   
}
//-------------Fetch director------------------------
