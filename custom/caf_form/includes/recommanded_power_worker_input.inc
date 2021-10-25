<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function recommanded_input($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$referenceid) {	
	global $base_root, $base_path, $user;
 
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$reference_no 		= encryption_decryption_fun('decrypt',$referenceid);
	
	
	//////////////////////////////end occupier Type////////////////////////
	//echo $service_id;die();
    $form = array();
	$form['serviceid_hidden'] = array(
			'#type' 			=> 'hidden',
			'#default_value' 	=> $serviceid,
		);
	$form['factorytypeid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $factory_typeid
			 
		);
	
	$form['applicationid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $applicationid
	);	
	
	$form['reference_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $referenceid
	);
	$get_fa_cafa 			= get_fa_cafa($application_id);
	$date_of_amenability	= date('d-m-Y',strtotime($get_fa_cafa['date_of_amenability']));
	$recomended_date_of_amenability	= date('d-m-Y',strtotime($get_fa_cafa['recomended_date_of_amenability']));
    $application_status		= $get_fa_cafa['application_status'];
	$worker_details 		= get_worker_details_service($service_id,$factory_type_id,$application_id,$reference_no);
	$power_details 			= get_power_generating_station($application_id,$reference_no,$factory_type_id,$service_id);
	
	foreach($worker_details as $worker){
			$worker_total 	= $worker->worker_total;
			$worker_id 		= $worker->id;
			$recomended_worker 		= $worker->recomended_total_worker;
	}	
	foreach($power_details as $power){
			$power_total 		= $power->installed_power;
			$power_unit_name 	= $power->power_unit;
			$power_id 			= $power->id;
			$power_recomended	= $power->recommanded_installed_power;
			$power_unit_recomended =  $power->recommanded_power_unit;
	}	
	//print_r($power_details);die;

   $form['power_id_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$power_id)
	);
	$form['worker_id_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt',$worker_id)
	);
	
	$form['worker_observation_date'] = array(
        '#type' => 'fieldset',
        '#title' => t('A.Please be confirmed Date from which the premises is occupied or been taken into use as factory'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
	 
    $form['worker_observation_date']['amenibiltydate_givenvalue'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-12">',
			'#suffix' 			=> '</div>',
			'#title' 			=> t('(i)Date Declared by applicant'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> $date_of_amenability,
			'#attributes' 		=> array('class' => array('form-control datepicker_retify'),'readonly' => 'readonly')
    );
	
    $form['worker_observation_date']['amenibiltydate_actualvalue'] = array(
        '#prefix' => '<div class="col-md-6 col-xs-12">',
        '#suffix' => '</div></div>',
        '#title' => t('(ii)Actual date found after inspection'),
        '#type' => 'textfield',
        '#default_value' => !empty($recomended_date_of_amenability)?$recomended_date_of_amenability:$date_of_amenability,
		
		'#attributes' => array('class' => array('form-control datepicker_retify'),'readonly' => 'readonly' ),
		
        '#required' => TRUE,
		
    );

    $form['worker_observation'] = array(
        '#type' => 'fieldset',
        '#title' => t('B. Workers Information'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
    
    $form['worker_observation']['worker_givenvalue'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-12">',
			'#suffix' 			=> '</div>',
			'#title' 			=> t('(i)Declared values by applicant'),
			'#type' 			=> 'textfield',
			'#default_value' 	=> $worker_total,
			'#element_validate'	=>  array('DOUBLE_FIELD_VALIDATION'),
			'#attributes' 		=> array('class' => array('form-control'),'readonly' => 'readonly')
    );
	
    $form['worker_observation']['worker_actualvalue'] = array(
        '#prefix' => '<div class="col-md-6 col-xs-12">',
        '#suffix' => '</div></div>',
        '#title' => t('(ii)Actual value found after inspection'),
        '#type' => 'textfield',
        '#default_value' => !empty($recomended_worker)?$recomended_worker:$worker_total,
		'#element_validate'	=>  array('DOUBLE_FIELD_VALIDATION'),
		'#attributes' => array('class' => array('form-control') ),
		
        '#required' => TRUE,
		
    );
	
	if($factory_type_id == 1 || $factory_type_id == 3){
		//$type_employee = array( ''=>'--SELECT--','1'=>'Director','2'=>'Manager');
		 $form['power_observation'] = array(
        		'#type' 		=> 'fieldset',
        		'#title' 		=> t('C. Installed Power Information'),
        		'#collapsible' 	=> TRUE, // Added
        		'#collapsed' 	=> FALSE // Added
    );
    
    $form['power_observation']['power_givenvalue'] = array(
        	'#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-12">',
        	'#suffix' 			=> '</div>',
       	 	'#title' 			=> t('(i) Declared values by applicant'),
        	'#type' 			=> 'textfield',
        	'#default_value' 	=> $power_total,
			'#element_validate'	=>  array('DOUBLE_FIELD_VALIDATION'),
			'#attributes' 		=> array('class' => array('form-control'),'readonly' => 'readonly')
    );
	 $form['power_observation']['unit'] 	= array(
			'#prefix' 	 		=> '<div class="col-md-4 col-xs-12">',
			'#suffix' 	 		=> '</div>',
			'#title' 			=> t('(iii)Actual Unit'),
			'#type' 	 		=> 'select',
			'#options'	 		=> array('HP'=>'HP','KW'=>'KW'),
			'#attributes' 		=>  array('class'=>array('form-control')),
			'#default_value' 	=> !empty($power_unit_recomended)?$power_unit_recomended:$power_unit_name,
			'#required' 		=>  TRUE,
	);
	
    $form['power_observation']['power_actualvalue'] = array(
        	'#prefix' 			=> '<div class="col-md-4 col-xs-12">',
        	'#suffix' 			=> '</div></div>',
        	'#title' 			=> t('(ii) Actual value found after inspection'),
        	'#type' 			=> 'textfield',
        	'#default_value' 	=> !empty($power_recomended)?$power_recomended:$power_total,
			'#element_validate'	=>  array('DOUBLE_FIELD_VALIDATION'),
			'#attributes' 		=> array('class' => array('form-control') ),
			'#required' 		=> TRUE,
		
    );
	}
   
	if($application_status == 'U'){
		$form['submit'] = array (
			'#type' 		=> 'submit',
			'#attributes' 	=> array('class' => array('btn btn-success pull-right'),'onclick' => 'if(!confirm("Are you sure to continue ?")){return false;}'),
			'#value' 		=> 'Submit'
		); 
	}
	return $form; 
}
		 


function recommanded_input_submit($form, &$form_state){
	global $user;
	$val   						= $form_state['values'];
	$uid 			    		= $user->uid;
	$remark_by_name				= get_name($uid); 
   	$rid						= get_role_id($uid); 
	$service_id					= encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$factory_type_id			= encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$application_id				= encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$application_reference_no	= encryption_decryption_fun('decrypt',$val['reference_hidden']);
	$worker_id_hidden			= encryption_decryption_fun('decrypt',$val['worker_id_hidden']);
	$power_id_hidden			= encryption_decryption_fun('decrypt',$val['power_id_hidden']);

	$worker_total							= $val['worker_actualvalue'];
	$installed_power						= $val['power_actualvalue'];
	$recomended_date_of_amenability			= date('Y-m-d',strtotime($val['amenibiltydate_actualvalue']));
	
	$query_check_applicant = db_select('fa_cafa_remarks','remarks');
	$query_check_applicant->fields('remarks', array());
	$query_check_applicant->condition('remarks.app_id', $application_id, '=');
	$query_check_applicant->condition('remarks.app_reference_no', $application_reference_no, '=');
	$query_check_applicant->orderBy('remarks.id','DESC');
	$query_check_applicant->range(0, 1);
	$result = $query_check_applicant->execute();
	$remark_field = $result->fetchAssoc();
	 $data 			 =	 array(	'status' => 'RP','remarks' => 'Repayment request is successfully completed','sending_time' => date('Y-m-d h:i'),);		
	//print_r($remark_field);die();
	$remark_id = $remark_field['id'];
	if($factory_type_id  == 1){
		
		if($worker_total>=10 && $installed_power>0){
			
			$recommanded_power_unit = $val['unit'];
			if($recommanded_power_unit == 'HP'){
				$recommande_type_power_station = 'other';
				$recommanded_installed_power_hp = $val['power_actualvalue'];
				}
				else{
					$recommande_type_power_station = 'power_generating_station';
					$recommanded_installed_power_hp = $installed_power*1.34102;//(1Kw => 1.34102 Hp)
			}
			$power_details_yearly =array(
				'recommanded_power_unit'				=> $recommanded_power_unit,
				'recommanded_installed_power'			=> $installed_power,
				'recommanded_installed_power_hp'		=> $recommanded_installed_power_hp,
				'recommande_type_power_station'			=> $recommande_type_power_station,
				
				'recommanded_by_id' 					=> $uid,
				'recommanded_by_name' 					=> $remark_by_name,
				'recommanded_by_rid' 					=> $rid,
				'power_application_status' 				=> 'RP',
			);
		   
			//print_r($power_details_yearly);die;
			$query_power 		 =	db_update('fa_power_details');
			$query_power		 ->	fields($power_details_yearly);
			$query_power	     ->	condition('id',$power_id_hidden,'=');
			$query_power		 ->	execute();
			
			$worker_array =array(
				'recomended_total_worker'	=> $worker_total,				
				'recommanded_by_id' 		=> $uid,
				'recommanded_by_name' 		=> $remark_by_name,
				'recommanded_by_rid' 		=> $rid,
				'worker_registration_status'=> 'RP',	
		   	);
		  
			$query_worker 		 =	db_update('fa_worker_details');
			$query_worker		 ->	fields($worker_array);
			//$query_worker		 ->	condition('service_year',$row_power->service_year,'=');
			$query_worker	     ->	condition('id',$worker_id_hidden,'=');
			$query_worker		 ->	execute();

			//////////////////OTHER TABLE UPDATE/////////////////
			$approval_status = 	array('application_status' => 'RP','recomended_date_of_amenability' => $recomended_date_of_amenability,'modification_date'=>date('Y-m-d'));
			$queryabc 		 =	db_update('fa_cafa');
			$queryabc		 ->	fields($approval_status);
			$queryabc		 ->	condition('id',$application_id,'=');
			$queryabc		 ->	condition('service_id',$service_id,'=');
			$queryabc	     ->	condition('factory_typeid',$factory_type_id,'=');
			$queryabc		 ->	condition('reference_number',$application_reference_no,'=');
			$queryabc		 ->	execute();
	
			$doc_status 	= 	array('application_status' => 'RP');
			$queryabc 		=	db_update('fa_caf_upload_doc');
			$queryabc		->	fields($doc_status);
			$queryabc		->	condition('app_id',$application_id,'=');
			$queryabc		->	condition('upload_documents_service_id',$service_id,'=');
			$queryabc	    ->	condition('upload_doc_factory_type_id',$factory_type_id,'=');
			$queryabc		->	condition('application_reference_no',$application_reference_no,'=');
			$queryabc		->	execute();
			
		  $manufacturing_status 	= 	array('manufacturing_application_status' => 'RP');
		  $querymanufacturing 		 	=	db_update('fa_nature_manufacturing');
		  $querymanufacturing			->	fields($manufacturing_status);
		  $querymanufacturing		    ->	condition('application_id',$application_id,'=');
		  $querymanufacturing		    ->	condition('service_id',$service_id,'=');
		  $querymanufacturing			->	condition('factory_type',$factory_type_id,'=');
		  $querymanufacturing			->	condition('application_reference_no',$application_reference_no,'=');
		  $querymanufacturing			->	execute();
		  
		  $director_status 	= 	array('application_status' => 'RP');
		  $querydirector 		=	db_update('fa_director_details');
		  $querydirector			->	fields($director_status);
		  $querydirector		    ->	condition('application_director_id',$application_id,'=');
		  $querydirector		    ->	condition('director_service_id',$service_id,'=');
		  $querydirector			->	condition('factory_type_id',$factory_type_id,'=');
		  $querydirector			->	condition('application_reference_no',$application_reference_no,'=');
		  $querydirector			->	execute();
		  
		  $occupier_status 	= 	array('application_status' => 'RP');
		  $querydirector 		=	db_update('fa_occupier_details');
		  $querydirector			->	fields($occupier_status);
		  $querydirector		    ->	condition('application_occupier_id',$application_id,'=');
		  $querydirector		    ->	condition('occupier_service_id',$service_id,'=');
		  $querydirector			->	condition('factory_type_id',$factory_type_id,'=');
		  $querydirector			->	condition('application_reference_no',$application_reference_no,'=');
		  $querydirector			->	execute();
		  
		  $manager_status 	= 	array('application_status' => 'RP');
		  $querymanager 		=	db_update('fa_manager_details');
		  $querymanager			->	fields($manager_status);
		  $querymanager		    ->	condition('application_manager_id',$application_id,'=');
		  $querymanager		    ->	condition('manager_service_id',$service_id,'=');
		  $querymanager			->	condition('factory_type_id',$factory_type_id,'=');
		  $querymanager			->	condition('application_reference_no',$application_reference_no,'=');
		  $querymanager			->	execute();
		  
		  drupal_set_message('Application has been successfully back for Re-payment.');
		  drupal_goto('inspector-registration-list/') ;
		 		
		  $queryabc 		 =	db_update('fa_cafa_remarks');
		  $queryabc		 	->	fields($data);
		  $queryabc		 	->	condition('id',$remark_id,'=');	
		  $queryabc		 	->	execute();
		  
		  
		}else{
			
			drupal_set_message('This applicaion under Section 2m(i),Total no of worker will be more than equal to 10 and installed power unit will be more than 0' ,'warning');
		}
	}
	
	if($factory_type_id == 2){
		if($worker_total >=20 && $installed_power==0){
		$worker_array =array(
					'recomended_total_worker'	=> $worker_total,				
					'recommanded_by_id' 		=> $uid,
					'recommanded_by_name' 		=> $remark_by_name,
					'recommanded_by_rid' 		=> $rid,
					'worker_registration_status'	=> 'RP',	
		   		);
		
			$query_worker 		 =	db_update('fa_worker_details');
			$query_worker		 ->	fields($worker_array);
			//$query_worker		 ->	condition('service_year',$row_power->service_year,'=');
			$query_worker	     ->	condition('id',$worker_id_hidden,'=');
			
			$query_worker		 ->	execute();
			//	echo $worker_id_hidden;die();	
			//////////////////OTHER TABLE UPDATE///////////////////////
			$approval_status = 	array('application_status' => 'RP','recomended_date_of_amenability' => $recomended_date_of_amenability,'modification_date'=>date('Y-m-d'));
			$queryabc 		 =	db_update('fa_cafa');
			$queryabc		 ->	fields($approval_status);
			$queryabc		 ->	condition('id',$application_id,'=');
			$queryabc		 ->	condition('service_id',$service_id,'=');
			$queryabc	     ->	condition('factory_typeid',$factory_type_id,'=');
			$queryabc		 ->	condition('reference_number',$application_reference_no,'=');
			$queryabc		 ->	execute();
	
			$doc_status 	= 	array('application_status' => 'RP');
			$queryabc 		=	db_update('fa_caf_upload_doc');
			$queryabc		->	fields($doc_status);
			$queryabc		->	condition('app_id',$application_id,'=');
			$queryabc		->	condition('upload_documents_service_id',$service_id,'=');
			$queryabc	    ->	condition('upload_doc_factory_type_id',$factory_type_id,'=');
			$queryabc		->	condition('application_reference_no',$application_reference_no,'=');
			$queryabc		->	execute();
			
		  $manufacturing_status 	= 	array('manufacturing_application_status' => 'RP');
		  $querymanufacturing 		 		=	db_update('fa_nature_manufacturing');
		  $querymanufacturing			->	fields($manufacturing_status);
		  $querymanufacturing		    ->	condition('application_id',$application_id,'=');
		  $querymanufacturing		    ->	condition('service_id',$service_id,'=');
		  $querymanufacturing			->	condition('factory_type',$factory_type_id,'=');
		  $querymanufacturing			->	condition('application_reference_no',$application_reference_no,'=');
		  $querymanufacturing			->	execute();
		  
	
		  $director_status 	= 	array('application_status' => 'RP');
		  $querydirector 		=	db_update('fa_director_details');
		  $querydirector			->	fields($director_status);
		  $querydirector		    ->	condition('application_director_id',$application_id,'=');
		  $querydirector		    ->	condition('director_service_id',$service_id,'=');
		  $querydirector			->	condition('factory_type_id',$factory_type_id,'=');
		  $querydirector			->	condition('application_reference_no',$application_reference_no,'=');
		  $querydirector			->	execute();
		  
		  $occupier_status 	= 	array('application_status' => 'RP');
		  $querydirector 		=	db_update('fa_occupier_details');
		  $querydirector			->	fields($occupier_status);
		  $querydirector		    ->	condition('application_occupier_id',$application_id,'=');
		  $querydirector		    ->	condition('occupier_service_id',$service_id,'=');
		  $querydirector			->	condition('factory_type_id',$factory_type_id,'=');
		  $querydirector			->	condition('application_reference_no',$application_reference_no,'=');
		  $querydirector			->	execute();
		  
		  $manager_status 	= 	array('application_status' => 'RP');
		  $querymanager 		=	db_update('fa_manager_details');
		  $querymanager			->	fields($manager_status);
		  $querymanager		    ->	condition('application_manager_id',$application_id,'=');
		  $querymanager		    ->	condition('manager_service_id',$service_id,'=');
		  $querymanager			->	condition('factory_type_id',$factory_type_id,'=');
		  $querymanager			->	condition('application_reference_no',$application_reference_no,'=');
		  $querymanager			->	execute();
		  
		
		  $queryabc 		 =	db_update('fa_cafa_remarks');
		  $queryabc		 	->	fields($data);
		  $queryabc		 	->	condition('id',$remark_id,'=');	
		  $queryabc		 	->	execute();
		  
		  drupal_set_message('Application has been successfully back for Re-payment.');
	  	  drupal_goto('inspector-registration-list/') ;
		
		}else{
			drupal_set_message('This application under Section 2m(ii),Total no of worker will be more than equal to 20 and installed power unit will be 0' ,'warning');
		}
	}
	
	if($factory_type_id == 3){
		if($installed_power == 0 && $worker_total<=19){
			
	
			$recommanded_power_unit = $val['unit'];
			if($recommanded_power_unit == 'HP'){
					$recommande_type_power_station = 'other';
					$recommanded_installed_power_hp = $installed_power;
							
				}else{
					$recommande_type_power_station = 'power_generating_station';
					$recommanded_installed_power_hp = $installed_power*1.34102;//(1Kw => 1.34102 Hp)
				}
				$power_details_yearly =array(
					'recommanded_power_unit'				=> $recommanded_power_unit,
					'recommanded_installed_power'			=> $installed_power,				
					'recommanded_installed_power_hp'		=> $recommanded_installed_power_hp,
					'recommande_type_power_station'			=> $recommande_type_power_station,
					'recommanded_by_id' 					=> $uid,
					'recommanded_by_name' 					=> $remark_by_name,
					'recommanded_by_rid' 					=> $rid,
					'power_application_status' 				=> 'RP',
				);
		   
				//print_r($power_details_yearly);die;
				$query_power 		 =	db_update('fa_power_details');
				$query_power		 ->	fields($power_details_yearly);
				$query_power	     ->	condition('id',$power_id_hidden,'=');
				$query_power		 ->	execute();
			
				$worker_array =array(
					'recomended_total_worker'	=> $worker_total,				
					'recommanded_by_id' 		=> 	$uid,
					'recommanded_by_name' 		=> 	$remark_by_name,
					'recommanded_by_rid' 		=> 	$rid,
					'worker_registration_status'	=> 'RP',	
		   		);
		  
				$query_worker 		 =	db_update('fa_worker_details');
				$query_worker		 ->	fields($worker_array);
				//$query_worker		 ->	condition('service_year',$row_power->service_year,'=');
				$query_worker	     ->	condition('id',$worker_id_hidden,'=');
				$query_worker		 ->	execute();
				
				//////////////////OTHER TABLE UPDATE/////////////////
			$approval_status = 	array('application_status' => 'RP','recomended_date_of_amenability' => $recomended_date_of_amenability,'modification_date'=>date('Y-m-d'));
				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		 ->	fields($approval_status);
				$queryabc		 ->	condition('id',$application_id,'=');
				$queryabc		 ->	condition('service_id',$service_id,'=');
				$queryabc	     ->	condition('factory_typeid',$factory_type_id,'=');
				$queryabc		 ->	condition('reference_number',$application_reference_no,'=');
				$queryabc		 ->	execute();
		
				$doc_status 	= 	array('application_status' => 'RP');
				$queryabc 		=	db_update('fa_caf_upload_doc');
				$queryabc		->	fields($doc_status);
				$queryabc		->	condition('app_id',$application_id,'=');
				$queryabc		->	condition('upload_documents_service_id',$service_id,'=');
				$queryabc	    ->	condition('upload_doc_factory_type_id',$factory_type_id,'=');
				$queryabc		->	condition('application_reference_no',$application_reference_no,'=');
				$queryabc		->	execute();
				
			  $manufacturing_status 	= 	array('manufacturing_application_status' => 'RP');
			  $querymanufacturing 		 		=	db_update('fa_nature_manufacturing');
			  $querymanufacturing			->	fields($manufacturing_status);
			  $querymanufacturing		    ->	condition('application_id',$application_id,'=');
			  $querymanufacturing		    ->	condition('service_id',$service_id,'=');
			  $querymanufacturing			->	condition('factory_type',$factory_type_id,'=');
			  $querymanufacturing			->	condition('application_reference_no',$application_reference_no,'=');
			  $querymanufacturing			->	execute();
			  
			  $director_status 	= 	array('application_status' => 'RP');
			  $querydirector 		=	db_update('fa_director_details');
			  $querydirector			->	fields($director_status);
			  $querydirector		    ->	condition('application_director_id',$application_id,'=');
			  $querydirector		    ->	condition('director_service_id',$service_id,'=');
			  $querydirector			->	condition('factory_type_id',$factory_type_id,'=');
			  $querydirector			->	condition('application_reference_no',$application_reference_no,'=');
			  $querydirector			->	execute();
			  
			  $occupier_status 	= 	array('application_status' => 'RP');
			  $querydirector 		=	db_update('fa_occupier_details');
			  $querydirector			->	fields($occupier_status);
			  $querydirector		    ->	condition('application_occupier_id',$application_id,'=');
			  $querydirector		    ->	condition('occupier_service_id',$service_id,'=');
			  $querydirector			->	condition('factory_type_id',$factory_type_id,'=');
			  $querydirector			->	condition('application_reference_no',$application_reference_no,'=');
			  $querydirector			->	execute();
			  
			  $manager_status 	= 	array('application_status' => 'RP');
			  $querymanager 		=	db_update('fa_manager_details');
			  $querymanager			->	fields($manager_status);
			  $querymanager		    ->	condition('application_manager_id',$application_id,'=');
			  $querymanager		    ->	condition('manager_service_id',$service_id,'=');
			  $querymanager			->	condition('factory_type_id',$factory_type_id,'=');
			  $querymanager			->	condition('application_reference_no',$application_reference_no,'=');
			  $querymanager			->	execute();
			  
			    $queryabc 		 =	db_update('fa_cafa_remarks');
		  $queryabc		 	->	fields($data);
		  $queryabc		 	->	condition('id',$remark_id,'=');	
		  $queryabc		 	->	execute();
			  
			  drupal_set_message('Application has been successfully back for Re-payment.');
			  drupal_goto('inspector-registration-list/') ;
			
		
		}if($installed_power == 0 && $worker_total>19){
			drupal_set_message('This application under Section 85,Total no of worker will be less than equal to 19 and installed power unit will be  0' ,'warning');
		}if($installed_power != 0 && $worker_total<=9){
			
	
			$recommanded_power_unit = $val['unit'];
			if($recommanded_power_unit == 'HP'){
					$recommande_type_power_station = 'other';
					$recommanded_installed_power_hp = $installed_power;
							
				}else{
					$recommande_type_power_station = 'power_generating_station';
					$recommanded_installed_power_hp = $installed_power*1.34102;//(1Kw => 1.34102 Hp)
				}
				$power_details_yearly =array(
					'recommanded_power_unit'				=> $recommanded_power_unit,
					'recommanded_installed_power'			=> $installed_power,				
					'recommanded_installed_power_hp'		=> $recommanded_installed_power_hp,
					'recommande_type_power_station'			=> $recommande_type_power_station,
					'recommanded_by_id' 					=> $uid,
					'recommanded_by_name' 					=> $remark_by_name,
					'recommanded_by_rid' 					=> $rid,
					'power_application_status' 				=> 'RP',
				);
		   
				//print_r($power_details_yearly);die;
				$query_power 		 =	db_update('fa_power_details');
				$query_power		 ->	fields($power_details_yearly);
				$query_power	     ->	condition('id',$power_id_hidden,'=');
				$query_power		 ->	execute();
			
				$worker_array =array(
					'recomended_total_worker'	=> $worker_total,				
					'recommanded_by_id' 		=> 	$uid,
					'recommanded_by_name' 		=> 	$remark_by_name,
					'recommanded_by_rid' 		=> 	$rid,
					'worker_registration_status'	=> 'RP',	
		   		);
		  
				$query_worker 		 =	db_update('fa_worker_details');
				$query_worker		 ->	fields($worker_array);
				//$query_worker		 ->	condition('service_year',$row_power->service_year,'=');
				$query_worker	     ->	condition('id',$worker_id_hidden,'=');
				$query_worker		 ->	execute();
				
				//////////////////OTHER TABLE UPDATE/////////////////
				$approval_status = 	array('application_status' => 'RP','recomended_date_of_amenability' => $recomended_date_of_amenability,'modification_date'=>date('Y-m-d'));
				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		 ->	fields($approval_status);
				$queryabc		 ->	condition('id',$application_id,'=');
				$queryabc		 ->	condition('service_id',$service_id,'=');
				$queryabc	     ->	condition('factory_typeid',$factory_type_id,'=');
				$queryabc		 ->	condition('reference_number',$application_reference_no,'=');
				$queryabc		 ->	execute();
		
				$doc_status 	= 	array('application_status' => 'RP');
				$queryabc 		=	db_update('fa_caf_upload_doc');
				$queryabc		->	fields($doc_status);
				$queryabc		->	condition('app_id',$application_id,'=');
				$queryabc		->	condition('upload_documents_service_id',$service_id,'=');
				$queryabc	    ->	condition('upload_doc_factory_type_id',$factory_type_id,'=');
				$queryabc		->	condition('application_reference_no',$application_reference_no,'=');
				$queryabc		->	execute();
				
			  $manufacturing_status 	= 	array('manufacturing_application_status' => 'RP');
			  $querymanufacturing 		 		=	db_update('fa_nature_manufacturing');
			  $querymanufacturing			->	fields($manufacturing_status);
			  $querymanufacturing		    ->	condition('application_id',$application_id,'=');
			  $querymanufacturing		    ->	condition('service_id',$service_id,'=');
			  $querymanufacturing			->	condition('factory_type',$factory_type_id,'=');
			  $querymanufacturing			->	condition('application_reference_no',$application_reference_no,'=');
			  $querymanufacturing			->	execute();
			  
			  $director_status 	= 	array('application_status' => 'RP');
			  $querydirector 		=	db_update('fa_director_details');
			  $querydirector			->	fields($director_status);
			  $querydirector		    ->	condition('application_director_id',$application_id,'=');
			  $querydirector		    ->	condition('director_service_id',$service_id,'=');
			  $querydirector			->	condition('factory_type_id',$factory_type_id,'=');
			  $querydirector			->	condition('application_reference_no',$application_reference_no,'=');
			  $querydirector			->	execute();
			  
			  $occupier_status 	= 	array('application_status' => 'RP');
			  $querydirector 		=	db_update('fa_occupier_details');
			  $querydirector			->	fields($occupier_status);
			  $querydirector		    ->	condition('application_occupier_id',$application_id,'=');
			  $querydirector		    ->	condition('occupier_service_id',$service_id,'=');
			  $querydirector			->	condition('factory_type_id',$factory_type_id,'=');
			  $querydirector			->	condition('application_reference_no',$application_reference_no,'=');
			  $querydirector			->	execute();
			  
			  $manager_status 	= 	array('application_status' => 'RP');
			  $querymanager 		=	db_update('fa_manager_details');
			  $querymanager			->	fields($manager_status);
			  $querymanager		    ->	condition('application_manager_id',$application_id,'=');
			  $querymanager		    ->	condition('manager_service_id',$service_id,'=');
			  $querymanager			->	condition('factory_type_id',$factory_type_id,'=');
			  $querymanager			->	condition('application_reference_no',$application_reference_no,'=');
			  $querymanager			->	execute();
			
		  $queryabc 		 =	db_update('fa_cafa_remarks');
		  $queryabc		 	->	fields($data);
		  $queryabc		 	->	condition('id',$remark_id,'=');	
		  $queryabc		 	->	execute();
			  
			  drupal_set_message('Application has been successfully back for Re-payment.');
			  drupal_goto('inspector-registration-list/') ;
			
		
		}if($installed_power != 0 && $worker_total>9){
			drupal_set_message('This application under Section 85,Total no of worker will be less than equal to 9 and installed power unit will be more than 0' ,'warning');
		
		}
	}
}

