<?php
function application_register_inspector_checklist($form, &$form_state,$serviceid,$factory_typeid,$applicationid,$referenceid,$id){
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	$reference_no 		= encryption_decryption_fun('decrypt',$referenceid);	
	$remark_id 			= encryption_decryption_fun('decrypt',$id);
	
	$check_tab = get_remark_tab_id($remark_id);
	if(empty($check_tab)){
		  	drupal_set_message(('At first you must be filled up the Part-1 then go to second tab'),'warning');
			drupal_goto('ad_observation/part_1/default/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$referenceid.'/'.$id) ;
	 }
  
	$form = array();
	$form['serviceid_hidden'] = array(
		 '#type' 	 		=> 'hidden',
		 '#default_value' 	=> $serviceid
	);	
	$form['factorytype_hidden'] = array(
	 		'#type' 	 		=> 'hidden',
	 		'#default_value' 	=> $factory_typeid
	);	   
	$form['referance_no_hidden'] = array(
			 '#type' 	 		=> 'hidden',
			 '#default_value' 	=> $referenceid
	);

	$form['application_id_hidden'] = array(
				'#type' 	 		=> 'hidden',
				'#default_value' 	=> $applicationid
	);
	$form['remark_id_hidden'] = array(
				'#type' 	 		=> 'hidden',
				'#default_value' 	=> $id,
	);
	
	$form['application_notesheet']['markup12']	= array(
			'#type'		=> 'markup',
  			'#prefix'	=> '<div class="row">
								<div class="box box-info">
									<div class="box-header with-border">
              							<h3 class="box-title">1.Pre-observation add:</h3>
			    					</div>
									<div class = "box-body">',
	);
	
	$conditions_list 	= observation_list();
   	$form['application_notesheet']['is_condition']= array(
		'#prefix'	=> '<div class="row"><div class="col-xs-12">
							<table class="table table-bordered"> 
								<tr>
									<th>Conditions</th>
									<th>Comments</th>
	 							</tr>',
					'#suffix'   => '',
					'#type'		=> 'markup'
				);
	$i=1;
	foreach ($conditions_list  as $data_conditions)	{		 
	$form['application_notesheet']['con1_'.$data_conditions->id] = array(
				'#type' 	=> 'markup',
				'#markup' 	=>  '<tr>'
		);
						
	 $form['application_notesheet']['check_conditions_'.$data_conditions->id] = array(
			'#type' 	=> 'markup',
			'#prefix' 	=> '<td><div class="col-md-10 col-xs-10">',
			'#suffix' 	=> '</div></td>',
			'#default_value' 	=> $data_conditions->id,
			'#markup' 	=> t($i.'. '.$data_conditions->observations),
       );
     
	//$checkbox = isset($form_state['values']['check_conditions'.$data_conditions->id]) ? $form_state['values']['check_conditions_'.$i] : '';
	
	$form['application_notesheet']['condition_comment_'.$data_conditions->id] = array(
				'#type' 	=> 'textfield',
				'#prefix' 	=> '<td><div class="col-md-12 col-xs-12">',
				'#suffix' 	=> '</div></td>',
				'#attributes' 	=> array('class' => array( '')),
        );
	
	
	$form['application_notesheet']['condition_id_'.$data_conditions->id] = array(
				'#type' 	=> 'hidden',
				'#prefix' 	=> '<td><div class="col-md-1 col-xs-1">',
				'#suffix' 	=> '</div></td>',
				'#attributes' 	=> array('class' => array( ''),),
				'#default_value' 	=> $data_conditions->id,
        );
	
	
	$form['application_notesheet']['end_con1_'.$data_conditions->id] = array(
		'#type' 	 	=> 'markup',
		'#markup' 	 	=>  '</tr>'
	);	
	$i++;
	}
	
  	$form['application_notesheet']['conditions_table_end'] 	= array(
		'#suffix' => '</table></div></div>',		
	);	
	
	$form['application_notesheet']['markup_condition'] = array(
        '#prefix' 	=> '<div class="row"><div class="box-body col-md-12"><h3>Add some conditions.</h3>',
		'#suffix' 	=> '</div>',
		'#type' 		=> 'markup',
	
		//'#required' 	=> TRUE,
    );
	
	
	$form['application_notesheet']['condition_process'] 	= array(
		'#type'		=> 'markup',
		'#prefix'	=> '<div id="ad_process_id">',
		'#suffix'	=> '</div>',
		);
		if (empty($form_state['condition_process_no'])){
			$form_state['condition_process_no'] = 1;
		}
		for ($i = 1; $i <= $form_state['condition_process_no']; $i++) {
			$form['application_notesheet']['condition_process']['cond_'.$i] = array(
				'#prefix' 		=> '<div class="col-md-4 col-xs-4">',
				'#suffix' 		=> '</div>',
				'#type' 		=> 'textfield',
				'#title'		=> t('write condition'),
				'#size' 		=> 150,
				'#attributes' 	=> array('multiple' => 'multiple'),
				);
			$form['application_notesheet']['condition_process']['comm_'.$i] = array(
				'#prefix' 		=> '<div class="col-md-8 col-xs-8">',
				'#suffix' 		=> '</div>',
				'#type'			=> 'textfield',
				'#title' 		=>	t('Comments'),
				'#size' 		=> 150,
				'#attributes' 	=> array('multiple' => 'multiple'),
				);	
			}
				
			$form['application_notesheet']['condition_process']['add_fields'] = array(
				'#prefix' 		=> '<div class="col-md-12 col-xs-12">',
				'#suffix' 		=> '</div></div></div>',
				'#attributes' 	=> array('class' => array('btn btn-dark ')),
				'#type' 		=> 'submit',
				'#value' 		=> t('Add condition'),
				'#submit' 		=> array('ad_processs_add_more_add_one'),
				'#ajax' 		=> array(
					'callback' 		=> 'ad_processs_add_more_callback',
					'wrapper' 		=> 'ad_process_id',
					),
				);	
				
	
  	$form['application_notesheet']['markup_end11'] 	= array(
			'#suffix' => '</div></div></div>',
	);
	
	$form['submit'] = array(
        '#prefix' 		=> '<div class="row"><div class="col-md-1">',
        '#suffix' 		=> '</div>',
        '#attributes' 	=> array('class' => array('btn btn-success')),
        '#type' 		=> 'submit',
        '#value' 		=> 'Send'
	);

	return $form;
}
function ad_processs_add_more_add_one($form, &$form_state){
	if (!isset($form_state['condition_process_no'])) {
		$form_state['condition_process_no'] = 0;
		$form_state['condition_process_no']++;
	}
	$form_state['condition_process_no']++;
	$form_state['rebuild'] = TRUE;
}

function ad_processs_add_more_callback($form, $form_state) {
	return $form['application_notesheet']['condition_process'];	
}
function application_register_inspector_checklist_submit($form, &$form_state){
    global $user;
    $userid 			= 	$user->uid;
    $val    			= 	$form_state['values'];
	
	$service_id			= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']); 
	$factorytype_id		= 	encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
	$application_id		= 	encryption_decryption_fun('decrypt',$val['application_id_hidden']);
	$reference_no		=  	encryption_decryption_fun('decrypt',$val['referance_no_hidden']);
	$remark_no			=  	encryption_decryption_fun('decrypt',$val['remark_id_hidden']);

		 $data 			 =	 array(	'status' => 'DC','remarks' => 'Notesheet is sucessfully submitted form AD end','sending_time' => date('Y-m-d h:i'));
						$queryabc 		 =	db_update('fa_cafa_remarks');
						$queryabc		 ->	fields($data);
						$queryabc		 ->	condition('id',$remark_no,'=');	
						$queryabc		 ->	execute();

						// 	$conditions_list 	= observation_list();
						// 	$i = 1;
						// 	foreach ($conditions_list  as $data_id)	{
						// 	$checklist_data =	 array(
						// 		'observations_id' 	=> $val['condition_id_'.$data_id->id],
						// 		'remark_by_ad' 		=> $val['condition_comment_'.$data_id->id],
						// 		'ad_details'		=> $userid.','.get_name($userid),
						// 		'remark_table_id'	=> $remark_no,
						// 		'app_id'			=> $application_id,
						// 		'factory_type'		=> $factorytype_id,
						// 	);
						// 	//if(!empty($val['condition_comment_'.$data_id->id])){
						// 	//print_r($checklist_data);die;
						// 	$queryabc 		 =	db_insert('fa_checklist_observations');
						// 	$queryabc		 ->	fields($checklist_data);
						// 	$queryabc		 ->	execute();
						// 	$i++;
						// 	//}
						// }
						// 	$c = 1;
						// 	foreach ($conditions_list  as $data_id)	{	
								
						// 		$extra_condition = array(
						// 			'ad_extra_observation' 	=> $val['cond_'.$data_id->id],
						// 			'remark_by_ad'		=> $val['comm_'.$data_id->id],
						// 			'ad_details'		=> $userid.','.get_name($userid),
						// 			'remark_table_id'	=> $remark_no,
						// 			'app_id'			=> $application_id,
						// 			'factory_type'		=> $factorytype_id,
						// 		);
						// 		if(!empty($val['comm_'.$data_id->id])){
						// 		$id = db_insert('fa_checklist_observations')->fields($extra_condition)->execute();
						// 		//$c++;
						// 		}
						// 	}
						
						$data =	 array('application_status' => 'DC');		
						$queryabc 		 =	db_update('fa_cafa');
						$queryabc		 ->	fields($data);
						$queryabc		 ->	condition('id',$application_id,'=');
						$queryabc		 ->	condition('service_id',$service_id,'=');
						$queryabc	     ->	condition('factory_typeid',$factorytype_id,'=');
						$queryabc		 ->	condition('reference_number',$reference_no,'=');		
						$queryabc		 ->	execute();
						
						//-----------Worker table update---------------------------
						$worker_status 	= 	array('worker_registration_status' => 'DC');
						$queryabc 		=	db_update('fa_worker_details');
						$queryabc			->	fields($worker_status);
						$queryabc		    ->	condition('application_id',$application_id,'=');
						$queryabc		    ->	condition('service_id',$service_id,'=');
						$queryabc			->	condition('factory_type',$factorytype_id,'=');
						$queryabc			->	condition('application_reference_no',$reference_no,'=');
						$queryabc			->	execute();
					  //----------------Documents Update-------------------
						$doc_status 	= 	array('application_status' => 'DC');
						$queryabc 		=	db_update('fa_caf_upload_doc');
						$queryabc		->	fields($doc_status);
						$queryabc		->	condition('app_id',$application_id,'=');
						$queryabc		->	condition('upload_documents_service_id',$service_id,'=');
						$queryabc	    ->	condition('upload_doc_factory_type_id',$factorytype_id,'=');
						$queryabc		->	condition('application_reference_no',$reference_no,'=');
						$queryabc		->	execute();
						
					//-----------Manufacturing table update---------------------------
					  $manufacturing_status 	= 	array('manufacturing_application_status' => 'DC');
					  $querymanufacturing 		=	db_update('fa_nature_manufacturing');
					  $querymanufacturing			->	fields($manufacturing_status);
					  $querymanufacturing		    ->	condition('application_id',$application_id,'=');
					  $querymanufacturing		    ->	condition('service_id',$service_id,'=');
					  $querymanufacturing			->	condition('factory_type',$factorytype_id,'=');
					  $querymanufacturing			->	condition('application_reference_no',$reference_no,'=');
					  $querymanufacturing			->	execute();
					  
					  //-----------Power table update---------------------------
					  $power_status 	= 	array('power_application_status' => 'DC');
					  $querypower 		=	db_update('fa_power_details');
					  $querypower			->	fields($power_status);
					  $querypower		    ->	condition('application_id',$application_id,'=');
					  $querypower		    ->	condition('service_id',$service_id,'=');
					  $querypower			->	condition('factory_type',$factorytype_id,'=');
					  $querypower			->	condition('application_reference_no',$reference_no,'=');
					  $querypower			->	execute();
					  
					  //-----------Director table update---------------------------
					  $director_status 	= 	array('application_status' => 'DC');
					  $querydirector 		=	db_update('fa_director_details');
					  $querydirector			->	fields($director_status);
					  $querydirector		    ->	condition('application_director_id',$application_id,'=');
					  $querydirector		    ->	condition('director_service_id',$service_id,'=');
					  $querydirector			->	condition('factory_type_id',$factorytype_id,'=');
					  $querydirector			->	condition('application_reference_no',$reference_no,'=');
					  $querydirector			->	execute();
					  
					  //-----------Manager table update---------------------------
					  $manager_status 	= 	array('application_status' => 'DC');
					  $querymanager 		=	db_update('fa_manager_details');
					  $querymanager			->	fields($manager_status);
					  $querymanager		    ->	condition('application_manager_id',$application_id,'=');
					  $querymanager		    ->	condition('manager_service_id',$service_id,'=');
					  $querymanager			->	condition('factory_type_id',$factorytype_id,'=');
					  $querymanager			->	condition('application_reference_no',$reference_no,'=');
					  $querymanager			->	execute();
	if($val['back']= 'Continue'){				
	drupal_set_message('Your notesheet has been successfully created and forwarded Deputy Chief.');
	if($service_id==3){
		drupal_goto('inspector-renewal/view-renewal-details/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factorytype_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.encryption_decryption_fun('encrypt',$remark_no));
		}elseif($service_id==2){
		drupal_goto('regsection/view-register-inspector/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factorytype_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.encryption_decryption_fun('encrypt',$remark_no));
		}elseif($service_id==8){
			drupal_goto('amendment-section/view-amendment-inspector/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factorytype_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.encryption_decryption_fun('encrypt',$remark_no));
			}
	}
}
   
function get_conditions_details($id){
	$conditions_details	=  db_query("SELECT observations  FROM {fa_observations_mst} WHERE id = '".$id."'")->fetchObject()->observations;
	return $conditions_details;
	}
function  get_remark_tab_id($remark_id){
	$conditions_details	=  db_query("SELECT remark_id  FROM {fa_cafa_notesheet} WHERE remark_id = '".$remark_id."'")->fetchObject()->remark_id;
	 if(!empty($conditions_details)){
		 return TRUE;
		 }else{
			return FALSE;
		}
	}	
	function observation_list(){
		$fetch_data	= db_select('fa_observations_mst ', 'con');
		$fetch_data->fields('con', array());
		$fetch_data->condition('con.status ',1,'=');
		$fetch_data	-> orderBy('con.id', 'asc');
		$all_data = $fetch_data->execute();
		$data  = $all_data->fetchAll();
		return $data;
	}