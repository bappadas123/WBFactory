<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function observation_list_admin($form, &$form_state,$serviceid, $factory_typeid,$applicationid,$referenceid) {
   
   	global $base_root,$base_path,$user;
	
  	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
   $factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
   $application_id 	= encryption_decryption_fun('decrypt',$applicationid);
 	$reference_no 		= encryption_decryption_fun('decrypt',$referenceid);
   	$value_app 			= '';
	$user_id 			= '';
   	$user_id 			= $user->uid;
   	
   	if (!empty($application_id)) {
           	$get_fa_cafa           			= 	get_fa_cafa($application_id);
          	$application_status      		= 	$get_fa_cafa['application_status'];
   			$factory_identification_number	= 	$get_fa_cafa['factory_reg_identification_number'];
   			$factory_referance_number		= 	$get_fa_cafa['reference_number'];	
   			$applicant_users				= 	$get_fa_cafa['created_by'];	
   			$previous_excess_paid			=   $get_fa_cafa['previous_excess_paid'];
   			$is_calculate					=   $get_fa_cafa['is_calculate'];
   			$service_fees					=   $get_fa_cafa['service_fees'];	
   			$period_for_application 		=   $get_fa_cafa['period_for_application'];
   			
       }

  
   	$form = array();
   	$form['#attributes'] = array('enctype' => "multipart/form-data");		
   	$form['serviceid_hidden'] = array(
   			 '#type' 			=> 'hidden',
   			 '#default_value' 	=> encryption_decryption_fun('encrypt',$service_id)
   			 
   	);	
   	$form['factorytype_hidden'] = array(
   			 '#type' 			=> 'hidden',
   			 '#default_value' 	=> encryption_decryption_fun('encrypt',$factory_type_id)
   			 
   	);		  
   	$form['factory_identification_number_hidden'] = array(
   			 '#type' 			=> 'hidden',
   			 '#default_value' 	=> empty($factory_identification_number)?'':encryption_decryption_fun('encrypt',$factory_identification_number)
   			 
   	);	   
   	$form['referance_no_hidden'] = array(
   			 '#type' 			=> 'hidden',
   			 '#default_value' 	=> encryption_decryption_fun('encrypt',$reference_no), 
   	);
   	
   	$form['application_id_hidden'] = array(
   			 '#type' 			=> 'hidden',
   			 '#default_value' 	=> encryption_decryption_fun('encrypt', $application_id), 
   	);
   	$form['applicant_id_hidden'] = array(
   			 '#type' 			=> 'hidden',
   			 '#default_value' 	=> encryption_decryption_fun('encrypt', $applicant_users), 
   	);
   	
   	$licence_journal	= l('Genarate Licence Register', 'regsection/registration-licence-journal-genarate-file/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('button'))));
   	
   	$form['applicantion_verify']['markup_appplication'] = array(
   			'#type' 			=> 'markup',
   			'#markup' 			=> get_verifing_data($application_id,$service_id,$factory_type_id,$reference_no),
   			);
   	
	
   	$form['applicantion_verify']['fieldname']	= array(
   												'#title'				=> 'Field Name',
   												'#type'					=> 'hidden',
   												'#attributes'			=> array('id' => 'deputychief_verify'),
   												'#default_value' 		=> !empty($content['verify_details']) ? $content['verify_details'] : '',
   												);
   	
   
 
 $form['applicantion_verify']['start_list_1']	 = array(
		'#markup' 		=> '<div class = "row">
								<div class="box box-info">
   									<div class="box-header with-border"><h3 class="box-title">Display all checklisted conditions and comments</h3></div>
											<div class="table-responsive">             
										  		<table class="table">
													<thead>
											  			<tr>
															<th>Conditions</th>
															<th>Assistant director (Remarks)</th>
															<th>Deputy Director (Remarks)</th>
															<th>Joint Director (Remarks)</th>
											  			</tr>
													</thead>
												<tbody>');

	$checklist = get_checklist_data($application_id,$factory_type_id,$is_chemical=0);	
	//print_r($checklist);die;
	$i=1;
	foreach($checklist as $row){
			if($row->observations_id){ 
				$condition_list = get_conditions_details($row->observations_id);
				}
			elseif(!empty($row->ad_extra_observation)){
				$condition_list = $row->ad_extra_observation;
				}
			elseif(!empty($row->dd_extra_observation)){
				$condition_list = $row->dd_extra_observation;
				}else{
					$condition_list = $row->jd_extra_observation;
					}		
					
	$form['applicantion_verify']['data_list_id'.$i] 	= array(
				'#type' 			=> 'hidden',
				'#attributes' 		=> array('class'=>array('form-control'),'readonly' => 'readonly'),
				'#default_value'	=> $row->checklist_id,
			);
						
 	$form['applicantion_verify']['data_list_'.$i] 	= array(
				'#prefix' 			=> '<tr><td>',
				'#suffix' 	 		=> '</td>',
				'#type' 			=> 'markup',
				'#markup'			=> $condition_list,
				'#id'				=> 'range',
				'#attributes' 		=> array('class'=>array('form-control'),'readonly' => 'readonly'),
				'#default_value'	=> '',
			);
	$split_value = explode(',',$row->ad_details);
	$data= !empty($split_value[1])?'Name:-'.$split_value[1].'</br>Remark:-'.$row->remark_by_ad:'';
	$form['applicantion_verify']['data_details_ad_'.$i] 	= array(
				'#prefix' 			=> '<td>',
				'#suffix' 	 		=> '</td>',
				'#type' 			=> 'markup',
				'#markup'			=> $data,
				'#attributes' 		=> array('class'=>array('form-control')),
				'#default_value'	=> '',
			);
	$options = array(1=> t('Yes'), 0 => t('No'),);
	$dd_split_value = explode(',',$row->dd_details);	
	if($dd_split_value[2]==1) { $v = $dd_split_value[2]; }else{$v =  0;}
	if($application_status == 'U' || $application_status == 'JC' ){
		$class =  array('class'=>array(''),'disabled'=>'disabled');
		}else{
			$class = array('class'=>array(''));
			}	
	if(!empty($row->remark_table_id)){	
		$form['applicantion_verify']['check_option_'.$i] = array(
				  '#prefix' 	=> '<td>',		 
				  '#type' 		=> 'radios',
				  '#options' 	=> $options,
				  '#title' 		=> t('Do you agree or not?'),
				  '#default_value' =>  $v,
				  '#attributes' =>$class,
				);
			}else{
				$form['applicantion_verify']['check_option_'.$i] = array(
				  '#prefix' 	=> '<td>',		 
				  '#type' 		=> 'markup',
				
				);
				}
	if($application_status == 'DC' || $application_status == 'DCBk' ){
		$form['applicantion_verify']['data_list_dd_'.$i] 	= array(
				'#suffix' 	 		=> '</td>',
				'#type' 			=> 'textfield',
				'#rows'				=> 3,
				'#attributes' 		=> array('class'=>array('form-control')),
				'#default_value'	=> $row->remark_by_dd,
			);	
		
	}else{
		$data_dd = !empty($dd_split_value[1])?'</br>Name:-'.$dd_split_value[1].'</br>Remark:-'.$row->remark_by_dd:'';
		$form['applicantion_verify']['data_list_dd_'.$i] 	= array(
				'#suffix' 	 		=> '</td>',
				'#type' 			=> 'markup',
				'#attributes' 		=> array('class'=>array('form-control')),
				'#markup'			=> $data_dd,
			);
			
		}
		
		$options = array(1=> t('Yes'), 0 => t('No'),);
		$jd_split_value = explode(',',$row->jd_details);	
		if($jd_split_value[2] == 1) { $view = $jd_split_value[2]; }else{$view =  0;}	
		$data_jd = !empty($jd_split_value[1])?'</br>'.$row->remark_by_jd.'</br><b>Name:-</b>'.$jd_split_value[1]:'';
		if(empty($row->jd_extra_observation)){
		$form['applicantion_verify']['check_option_jd_'.$i] = array(
				  '#prefix' 		=> '<td>',
				  '#type' 			=> 'radios',
				  '#options' 		=> $options,
				  '#title' 			=> t('Do you agree or not?'),
				  '#default_value' 	=> $view ,
				   '#attributes' 	=> array('class'=>array(''),'disabled' => 'disabled'),
				);
		}else{
		$form['applicantion_verify']['check_option_jd_'.$i] = array(
				'#prefix' 		=> '<td>',
				'#type' 		=> 'markup',
			);	
		}		
		$form['applicantion_verify']['data_list_jd_'.$i] 	= array(
				'#suffix' 	 		=> '</td>',
				'#type' 			=> 'markup',
				'#cols'				=> 5,
				'#rows'				=> 3,
				'#attributes' 		=> array('class'=>array('form-control'),'readonly'=>'readonly'),
				'#markup'			=> $data_jd,
			);
			$i++;
	}
		
 $form['applicantion_verify']['end_list_1']	 = array(
		'#markup' 		=> '</table></div>',
	);

	
   						
   	//echo $application_status;die;
   	if($application_status == 'DC' || $application_status == 'DCBk' ){	
		$form['applicantion_verify']['markup_condition'] = array(
        '#prefix' 	=> '<div class="box-header with-border"><h3 class="box-title">Add More conditions</h3></div>
							<div class = "box-body">',
		'#type' 	=> 'markup',

    	);
	
	
		$form['applicantion_verify']['condition_process'] 	= array(
			'#type'		=> 'markup',
			'#prefix'	=> '<div id="dd_process_id">',
			'#suffix'	=> '</div>',
		);
		if (empty($form_state['condition_process_no'])){
			$form_state['condition_process_no'] = 1;
		}
		for ($i = 1; $i <= $form_state['condition_process_no']; $i++) {
			$form['applicantion_verify']['condition_process']['cond_'.$i] = array(
				'#prefix' 		=> '<div class="col-md-4 col-xs-4">',
				'#suffix' 		=> '</div>',
				'#type' 		=> 'textfield',
				'#title'		=> t('Write condition'),
				'#size' 		=> 150,
				'#attributes' 	=> array('multiple' => 'multiple'),
				);
			$form['applicantion_verify']['condition_process']['comm_'.$i] = array(
				'#prefix' 		=> '<div class="col-md-8 col-xs-8">',
				'#suffix' 		=> '</div>',
				'#type'			=> 'textfield',
				'#title' 		=> t('Comments'),
				'#size' 		=> 150,
				'#attributes' 	=> array('multiple' => 'multiple'),
				);	
			}
				
			$form['applicantion_verify']['condition_process']['add_fields'] = array(
				'#prefix' 		=> '<div class="col-md-12 col-xs-12">',
				'#suffix' 		=> '</div>',
				'#attributes' 	=> array('class' => array('btn btn-dark ')),
				'#type' 		=> 'submit',
				'#value' 		=> t('Add condition'),
				'#submit' 		=> array('dd_processs_add_more_add_one'),
				'#ajax' 		=> array(
					'callback' 		=> 'dd_processs_add_more_callback',
					'wrapper' 		=> 'dd_process_id',
					),
				);	
				
	
  		$form['applicantion_verify']['markup_end11'] 	= array(
			'#suffix' => '</div></div></div>',
		);
		
	
   	/* REMARKS/NOTESHEET */
   		
  
   			$form['application_forword']['submit'] = array(
			   '#prefix' => '<div class="col-md-12 col-xs-12">',
			   '#suffix' => '</div>',
			   '#attributes' => array('class' => array('btn btn-info margin'), 'onclick' => 'if(!confirm("Are you sure to continue ?")){return false;}'),
			   '#type' => 'submit',
			   '#value' => 'Submit'
       		);
			$form['application_forword']['remark_end11'] 	= array(
				'#suffix' => '</div></div></div></div>',
			);
   		}
	
   	 return $form;
   }
   
function dd_processs_add_more_add_one($form, &$form_state){
	if (!isset($form_state['condition_process_no'])) {
		$form_state['condition_process_no'] = 0;
		$form_state['condition_process_no']++;
	}
	$form_state['condition_process_no']++;
	$form_state['rebuild'] = TRUE;
}

function dd_processs_add_more_callback($form, $form_state) {
	return $form['applicantion_verify']['condition_process'];	
}   
   
function get_ajax_note($form, &$form_state)
   {
		$commands   = array();
		$commands[] = ajax_command_replace('#remark_id', drupal_render($form['application_forword']['application_remark']));
		$commands[] = ajax_command_replace('#notesheet_id', drupal_render($form['application_forword']['application_note']));
		$commands[] = ajax_command_replace('#reject_id', drupal_render($form['application_forword']['application_reject']));
		$commands[] = ajax_command_replace('#zone_change_id', drupal_render($form['application_forword']['application_zone_change']));
		$commands[] = ajax_command_replace('#zone_remark', drupal_render($form['application_forword']['application_zone_change_note']));
		$commands[] = ajax_command_replace('#download_licence', drupal_render($form['application_forword']['download_licence']));
		$commands[] = ajax_command_replace('#view_journal', drupal_render($form['application_forword']['view_journal']));
		$commands[] = ajax_command_replace('#edit-doc-file-ajax-wrapper', drupal_render($form['application_forword']['doc_file']));
		$commands[] = ajax_command_replace('#download_registration', drupal_render($form['application_forword']['download_registration']));
		$commands[] = ajax_command_replace('#journal_notesheet_id', drupal_render($form['application_forword']['application_journal_notesheet']));
       return array('#type' => 'ajax', '#commands' => $commands);;
   }
   function get_verifing_data($application_id,$service_id,$factory_type_id,$reference_no){
   	//echo $reference_no;
   	global $base_root,$base_path,$user;		 
   	$user_id 				=  $user->uid;
	$get_all_data 			=  get_fa_cafa($application_id);
	$application_status     =  $get_all_data['application_status'];
   	
   						
   		$output = '<div class="row">
   					<div class="box box-info">
   						
   					<div class = "box-body">
   					<table cellpadding="0" cellspacing="0" border="0" width="100%" class="table table-bordered custom-table-view">
					<tr><td><h1><font color="#FF0000">This page is under testing donot submit any data from this page</font></h1></td>
					<td></td>
   				<tr><td> Uploaded Application Forms</td>';
				
		$application_from	= l('View Application From',file_create_url($upload_application_form), array('html' => TRUE,'attributes'=>array('title' => 'View', 'onclick' => "popIt(this.href);return false;", 'target' => '_BLANK','class'=>array(''))));
				$output .= '<td><b>'.$application_from.'</b></td>
			
				</tr>
				<tr><td> Submitted Application Forms</td>';
				
		$application_from	= l('View Application From',file_create_url($upload_application_form), array('html' => TRUE,'attributes'=>array('title' => 'View', 'onclick' => "popIt(this.href);return false;", 'target' => '_BLANK','class'=>array(''))));
				$output .= '<td><b>'.$application_from.'</b></td>
			
				</tr>
				</table>';
   				
   				
 		
		$output.='</div></div></div>';
   return $output;
   }
   
   function application_view_register_deputychief_submit($form, &$form_state){
   	  global $user;
   	  $uid = $user->uid;
   	  $val   					= 	$form_state['values'];
	  	  
   	  $service_id 				= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']); 
   	  $factorytype_id 			= 	encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
   	  $application_id 			= 	encryption_decryption_fun('decrypt',$val['application_id_hidden']);
   	  $reference_no				=  	encryption_decryption_fun('decrypt',$val['referance_no_hidden']);
   	  $applicant_id				=  	encryption_decryption_fun('decrypt',$val['applicant_id_hidden']);
   	  
   	  $remark_by_name= get_name($uid); 
   	  $rid= get_role_id($uid); 
			 if($val['forword_user']=='1'){ 
   					$status ='JC';
   					$type ='n';
   					$details = $val['application_note'];
   					
   				} 
				 if($val['forword_user']=='2'){ 
   					$status ='AIBk';
   					$type ='r';
   					$details = $val['application_remark'];
   				} 
				
   				
   					if(!empty($id)){
						
						$checklist = get_checklist_data($application_id,$factorytype_id,$is_chemical=0);	
							$i=1;
								foreach($checklist as $row){
   									$value =	 array('remark_by_dd'	=> $val['data_list_dd_'.$i],'dd_details'=> $rid.','.$remark_by_name.','.$val['check_option_'.$i],'app_id'			=> $application_id,'factory_type'=> $factorytype_id);		
   									$queryuser 		 =	db_update('fa_checklist_observations');
   									$queryuser		 ->	fields($value);
   									$queryuser		 ->	condition('checklist_id',$val['data_list_id'.$i],'=');
   									$queryuser		 ->	execute();

									$i++;
									}
									$c = 1;
									
									while(!empty($val['cond_'.$c])){
										$checked =1;
										$extra_condition = array(
											'dd_extra_observation' 	=> $val['cond_'.$c],
											'remark_by_dd'		=> $val['comm_'.$c],
											'dd_details'		=> $rid.','.get_name($uid).','.$checked,
											'remark_table_id'	=> $remark_no,
											'app_id'			=> $application_id,
											'factory_type'		=> $factorytype_id,
										);
										
										$id = db_insert('fa_checklist_observations')->fields($extra_condition)->execute();
										$c++;
									}
   								}
								
   								$cafa_remarks = array(
								'app_id'   			 => $application_id,
								'remark_by_uid' 	 => $uid,
								'remark_by_roleid' 	 => $rid,
								'remark_to_roleid' 	 => 11,
								'sending_time' 		 => date('Y-m-d h:i:s'),
								'app_reference_no' 	 => $reference_no,
								'remarks' 	         => $details,
								'remark_type'		 => $type,
								'verify_details'	 => $val['fieldname'],
								'status' 			 => $status,
								'remark_by_name'	 => $remark_by_name,
   							);
   					$id = db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();
   									
   							  //---------------- CAFA TABLE UPDATE -------------------
   								$data =	 array('application_status' => $status);		
   								$queryabc 		 =	db_update('fa_cafa');
   								$queryabc		 ->	fields($data);
   								$queryabc		 ->	condition('id',$application_id,'=');
   								$queryabc		 ->	condition('service_id',$service_id,'=');
   								$queryabc	     ->	condition('factory_typeid',$factorytype_id,'=');
   								$queryabc		 ->	condition('reference_number',$reference_no,'=');		
   								$queryabc		 ->	execute();
   						
   							  //-----------Worker table update---------------------------
   								$worker_status 	= 	array('worker_registration_status' => $status);
   								$queryabc 		=	db_update('fa_worker_details');
   								$queryabc			->	fields($worker_status);
   								$queryabc		    ->	condition('application_id',$application_id,'=');
   								$queryabc		    ->	condition('service_id',$service_id,'=');
   								$queryabc			->	condition('factory_type',$factorytype_id,'=');
   								$queryabc			->	condition('application_reference_no',$reference_no,'=');
   								$queryabc			->	execute();
   							  //----------------Documents Update-------------------
   								$doc_status 	= 	array('application_status' => $status);
   								$queryabc 		=	db_update('fa_caf_upload_doc');
   								$queryabc		->	fields($doc_status);
   								$queryabc		->	condition('app_id',$application_id,'=');
   								$queryabc		->	condition('upload_documents_service_id',$service_id,'=');
   								$queryabc	    ->	condition('upload_doc_factory_type_id',$factorytype_id,'=');
   								$queryabc		->	condition('application_reference_no',$reference_no,'=');
   								$queryabc		->	execute();
   								
   								//-----------Manufacturing table update---------------------------
   								  $manufacturing_status 	= 	array('manufacturing_application_status' => $status);
   								  $querymanufacturing 		 		=	db_update('fa_nature_manufacturing');
   								  $querymanufacturing			->	fields($manufacturing_status);
   								  $querymanufacturing		    ->	condition('application_id',$application_id,'=');
   								  $querymanufacturing		    ->	condition('service_id',$service_id,'=');
   								  $querymanufacturing			->	condition('factory_type',$factorytype_id,'=');
   								  $querymanufacturing			->	condition('application_reference_no',$reference_no,'=');
   								  $querymanufacturing			->	execute();
   								  
   								  //-----------Power table update---------------------------
   								  $power_status 	= 	array('power_application_status' => $status);
   								  $querypower 		=	db_update('fa_power_details');
   								  $querypower			->	fields($power_status);
   								  $querypower		    ->	condition('application_id',$application_id,'=');
   								  $querypower		    ->	condition('service_id',$service_id,'=');
   								  $querypower			->	condition('factory_type',$factorytype_id,'=');
   								  $querypower			->	condition('application_reference_no',$reference_no,'=');
   								  $querypower			->	execute();
   								  
   								  //-----------Director table update---------------------------
   								  $director_status 	= 	array('application_status' => $status);
   								  $querydirector 		=	db_update('fa_director_details');
   								  $querydirector			->	fields($director_status);
   								  $querydirector		    ->	condition('application_director_id',$application_id,'=');
   								  $querydirector		    ->	condition('director_service_id',$service_id,'=');
   								  $querydirector			->	condition('factory_type_id',$factorytype_id,'=');
   								  $querydirector			->	condition('application_reference_no',$reference_no,'=');
   								  $querydirector			->	execute();
   								  
   								  //-----------Manager table update---------------------------
   								  $manager_status 	= 	array('application_status' => $status);
   								  $querymanager 		=	db_update('fa_manager_details');
   								  $querymanager			->	fields($manager_status);
   								  $querymanager		    ->	condition('application_manager_id',$application_id,'=');
   								  $querymanager		    ->	condition('manager_service_id',$service_id,'=');
   								  $querymanager			->	condition('factory_type_id',$factorytype_id,'=');
   								  $querymanager			->	condition('application_reference_no',$reference_no,'=');
   								  $querymanager			->	execute();
   								
   								
   				if($status=='AIBk'){
   					drupal_set_message('Application has been successfully revart to Assistant Director of Factories');
				}elseif($status=='JC'){
   						drupal_set_message('Application has been successfully forwarded Jt. Chief of Factory.');
   					}
   				drupal_goto('deputychief-registration-list/');
   			}
//function get_checklist_data($app_id,$factory_type){
//	$fetch_condition	= db_select('fa_checklist_conditions ', 'checklist');
//	//$fetch_condition->InnerJoin('fa_cafa_remarks', 'remarks', 'checklist.remark_table_id = remarks.id');
//	$fetch_condition->fields('checklist', array('checklist_id','conditions_id','remark_by_ad','ad_details','remark_by_dd','dd_details','remark_by_jd','jd_details','ad_extra_condition','dd_extra_condition','jd_extra_condition','remark_table_id'));
//	$fetch_condition->condition('checklist.app_id', $app_id, '=');
//	$fetch_condition->condition('checklist.factory_type', $factory_type, '=');
//	$fetch_condition-> orderBy('checklist.checklist_id', 'ASC');
//	$condition_result = $fetch_condition->execute()->fetchAll(); 
//	
//	return $condition_result;
//}   
   
function get_conditions_details($id){
	$conditions_details	=  db_query("SELECT observations  FROM {fa_observations_mst} WHERE id = '".$id."'")->fetchObject()->observations;
	return $conditions_details;
	}

function display_document($application_id,$service_id,$factory_type_id,$reference_no){
	
	$query 	=  db_select('fa_caf_upload_doc', 'fcud');
				$query	-> InnerJoin('fa_file_managed_custom', 'file' ,'fcud.fid = file.id');
				$query 	-> fields('fcud', array());
				$query	-> fields('file', array('file_uri'));
				$query	-> condition('fcud.app_id', $application_id);
				$query	-> condition('fcud.application_reference_no', $reference_no);
				$query	-> condition('fcud.upload_documents_service_id', $service_id);
				$query	-> condition('fcud.upload_doc_factory_type_id', $factory_type_id);
				$result = $query->execute();
				//echo $query;die;
				$resultData = $result->fetchAll();
	
	$output.='<div class="row"><div class="box box-info">
				<div class="box-header with-border"><h3 class="box-title">Q. Uploaded Documents View</h3></div>
				<div class="box-body">
						<div class="col-md-3">
						 <h4 class="label-warning center">Document List</h4>';
							$i=1;
							foreach($resultData as $documents){
								$output.='<li class="btn btn-success" style="white-space: initial; margin: 7px;"><span class="link"  onclick="seeDoc(this);"  data-id="'.file_create_url($documents->file_uri).'"  data-myval='.file_create_url($documents->file_uri).'>'.file_name($documents->id_doc_master).'</span></li>';
							$i++;
							}
			$output.='</div>
						<div class="col-md-9">
							<h4 class="label-warning center">Preview</h4>
							
							<object type="application/pdf" id="doc" data="'.$GLOBALS['base_url'].'/sites/default/files/preview.pdf" width="100%" height="580" border="1px"></object>
							
					</div></div></div></div>';
					return $output;
				}
?>