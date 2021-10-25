<?php
//$applicationid
function inspector_chemical_application_verify($form, &$form_state,$serviceid, $factory_typeid,$applicationid,$referenceid) {

	global $base_root,$base_path,$user;
	
	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js'); 
	
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$reference_no 		= encryption_decryption_fun('decrypt',$referenceid);
	$value_app ='';
	 
	$form = array();
	
	if (!empty($application_id)) {
        $get_fa_cafa           				= 	get_fa_cafa($application_id);
       	
		$application_status      			= 	$get_fa_cafa['application_status'];
		$factory_plan_identification_number	= 	$get_fa_cafa['plan_approve_identification_number'];
		$factory_referance_number			= 	$get_fa_cafa['reference_number'];	
		$applicant_users					= 	$get_fa_cafa['created_by'];	
    }
	
	$user_id ='';
	$user_id = $user->uid;

	$query_check_applicant = db_select('fa_cafa_remarks','remarks');
	$query_check_applicant->fields('remarks', array());
	$query_check_applicant->condition('remarks.app_id', $application_id, '=');
	$query_check_applicant->condition('remarks.app_reference_no', $reference_no, '=');
	$query_check_applicant->condition('remarks.plan_status_chem', '', '!='); 
	$query_check_applicant->orderBy('remarks.id','DESC');
	$query_check_applicant->range(0, 1);
	$result = $query_check_applicant->execute();
	$content = $result->fetchAssoc();
	
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
			 '#default_value' 	=> empty($factory_plan_identification_number)?'':encryption_decryption_fun('encrypt',$factory_plan_identification_number)
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
	
	ctools_include('ajax');
	ctools_include('modal');
	ctools_modal_add_js();	 
	$tt=$base_root.$base_path.'notesheets/'.$application_id.'/'.$reference_no.'/nojs'; 	
	$link_t=ctools_modal_text_button(t('View Notesheet'), $tt ,t('View Notesheet')) ;

	$cc=$base_root.$base_path.'conditions/'.$application_id.'/'.$reference_no.'/nojs'; 	
	$link_c=ctools_modal_text_button(t('View Condition'), $cc ,t('View Condition')) ;

	$title = ($service_id=='4') ? 'Application for Approval of Plan' : 'Application for Extension of Existing Plan';
	
	$form['header'] = array(
		'#markup' 			=> t('<div class="cus-page-outer-view"><div class="content"><center class="verify-top-title-pad"><h3>'.$title.'</h3><p>All inputs are provided by applicant only</p><p>All inputs are to be verified by officials</p></center>'),
	);
	
	$form['application_verify']['link'] = array(
		'#markup' 			=> t('<h5 class="pull-right" style="margin:0;"><i class="ace-icon fa fa-file-text-o bigger-130 text-blue" style="padding: 10px;"></i>'.$link_t.'<i class="ace-icon fa fa-file-text-o bigger-130 text-blue" style="padding: 10px;"></i>'.$link_c.'</h5>'),
	);
	
	$form['application_verify']['markup_appplication'] = array(
		'#type' 			=> 'markup',
		'#markup' 			=> get_verifing_data($application_id,$service_id,$factory_type_id,$reference_no),
			);
	
	$form['application_verify']['fieldname']	= array(
		'#title'			=> 'Field Name',
		'#type'				=> 'hidden',
		'#attributes'		=> array('id' => 'inspectorchemical_verify'),
		'#default_value' 	=> !empty($content['verify_details']) ? $content['verify_details'] : '',
			);

	// DOC VERIFY ARRAY CREATION
	$doc_verify = explode(',',$content['doc_verify']);
	if(in_array('ok',$doc_verify)) {
		$a = 0;
		for($a = 0; $a < count($doc_verify); $a++)
		{ if($doc_verify[$a] == 'ok') { $test .= "document_details_".$a.','; } }

		$form['application_doc_verify']['doc_fieldname']	= array(
			'#title'				=> 'Field Name',
			'#type'					=> 'hidden',
			'#attributes'			=> array('id' => 'inspectorchemical_doc_verify'),
			'#default_value' 		=> rtrim($test,','),
			);
	 } else {
	 
		$form['application_doc_verify']['doc_fieldname']	= array(
			'#title'				=> 'Field Name',
			'#type'					=> 'hidden',
			'#attributes'			=> array('id' => 'inspectorchemical_doc_verify'),
			'#default_value' 		=> !empty($content['doc_verify']) ? $content['doc_verify'] : '',
			);
	  }

    // REMARKS/NOTESHEET
	$chem_status = find_chemical_status($get_fa_cafa['id']);
	$gen_status  = find_general_status($get_fa_cafa['id']);
	
	if(($chem_status=='AICh') || ($chem_status=='AIChBk'))
	{
		$form['application_forward'] = array(
			'#type' 				=> 'fieldset',
			'#title' 				=> t('Action'),
			'#collapsible' 			=> TRUE, // Added
			'#collapsed' 			=> FALSE // Added
		);
			
			//ZONE CHECK
			$get_zone = db_select('fa_cafa_remarks', 'remarks');
			$get_zone->fields('remarks', array('verify_details'));
			$get_zone->condition('remarks.app_id', trim($application_id));
			$get_zone->orderBy('remarks.id','DESC');
			$get_zone->range(0, 1);
			$get_zone_result = $get_zone->execute();		
			$zone_check = $get_zone_result->fetchAssoc();


		if($chem_status=='AICh')
			{
				$remark_field = explode(',', $zone_check['verify_details']);
				$zone_chk_value = in_array('factory_location', $remark_field);
				
				if($zone_chk_value == 1)
				{	
					$users_action= array(	
						'0'			=>'Select',
						//'1'			=>'Back to applicant',
						'2'			=>'Forward to Deputy Chief Chemical',
						//'3'			=>'Reject', 
						//'4'			=>'Send to specific zone Inspector Chemical'
					);
				} else {
										$users_action= array(	
						'0'			=>'Select',
						//'1'			=>'Back to applicant',
						'2'			=>'Forward to Deputy Chief Chemical',
						//'3'			=>'Reject', 
						'4'			=>'Send to specific zone Inspector Chemical'
					);
				}
				
			} else {
				$users_action= array(	
						'0'			=>'Select',
						//'1'			=>'Back to applicant',
						'2'			=>'Forward to Deputy Chief Chemical',
						//'3'			=>'Reject', 
					);
			}
		
		$form['application_forward']['forward_user'] 	= array(
			'#prefix' 			=> '<div class="row"><div class="col-md-4 col-xs-12"><label class="select label-block">Necessary action to be taken: &nbsp;<span id=\'star\' class="form-required">*</span>',
			'#suffix' 			=> '</label></div>',
			'#type' 			=> 'select',
			'#options' 			=> $users_action,
			'#default_value' 	=> $value_app,
			'#required' 		=> TRUE,
			'#ajax' 			=> array(
			'event' 			=> 'change',
			'effect' 			=> 'fade',
			'callback' 			=> 'get_ajax_note',
			'progress' 			=> array('type' => 'throbber','message' => t('loading')))
			);
				
		$form['application_forward']['application_remark'] = array(
			'#prefix' 			=> '<div id="remark_id">',
			'#suffix' 			=> '</div>',
		);
		$form['application_forward']['application_note'] = array(
			'#prefix' 			=> '<div id="notesheet_id">',
			'#suffix' 			=> '</div>',
		);
		$form['application_forward']['conditions'] = array(
			'#prefix' 			=> '<div id="condition_id">',
			'#suffix' 			=> '</div>',
		);
		$form['application_forward']['observations'] = array(
			'#prefix' 			=> '<div id="observation_id">',
			'#suffix' 			=> '</div>',
		);
		$form['application_forward']['pre_observations'] = array(
			'#prefix' 			=> '<div id="pre_observation_id">',
			'#suffix' 			=> '</div>',
		);
		$form['application_forward']['application_reject'] = array(
			'#prefix' 			=> '<div id="reject_id">',
			'#suffix' 			=> '</div>',
		);
		$form['application_forward']['application_zone_change'] = array(
			'#prefix' 			=> '<div id="zone_change_id">',
			'#suffix' 			=> '</div>',
		);
		$form['application_forward']['application_zone_change_note'] = array(
			'#prefix' 			=> '<div id="zone_remark">',
			'#suffix' 			=> '</div>',
		);
		$action   = isset($form_state['values']['forward_user']) ? $form_state['values']['forward_user'] : $value_app;
		
		if($action == 2){
			$form['application_forward']['application_note'] = array(
			'#prefix' 			=> '<div id="notesheet_id" class="col-md-8"><label class="input label-block">Notesheet to Deputy Chief Chemical: &nbsp;<span id=\'star\' class="form-required">*</span>',
			'#suffix' 			=> '</label></div>',
			'#type' 			=> 'text_format',
			'#required' 		=> TRUE,
			//'#default_value'  => !empty($content['remarks']) ? $content['remarks'] : '',
			);	
			
			// --------------- Add more text box starts  ------------------------------
	
		$form['application_forward']['conditions'] = array(
			'#type' 			=> 'fieldset',
			'#title' 			=> t('Enter Conditions <span style="font-size:15px;">'.$link_c.'</span>'),
			'#prefix' 			=> '<div id="condition_id" class="col-lg-12 col-md-12 col-sm-12">',
			'#suffix' 			=> '</div>',
		);
	
		if (empty($form_state['condition_no'])) {
			$form_state['condition_no'] = 1;
		}
	
		for ($i = 0; $i < $form_state['condition_no']; $i++) {
	
			$form['application_forward']['conditions']['condition_'.$i] = array(
				'#prefix' 		=> '<div class="col-md-12"><label class="input label-block">',
				'#suffix' 		=> '</label></div>',
				'#type' 		=> 'textfield',
				'#title' 		=> '',
				'#size' 		=> 150,
				'#description' 	=> t('Condition'),
				'#attributes' 	=> array('multiple' => 'multiple'),
			);
		}
	
		$form['application_forward']['conditions']['add_conditions'] = array(
			'#prefix' 			=> '<div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div>',
			'#attributes' 		=> array('class' => array('btn btn-dark')),
			'#type' 			=> 'submit',
			'#value' 			=> t('Add more Condition'),
			'#submit' 			=> array('conditions_add_more_add_one'),
			'#ajax' 			=> array(
				'callback' 		=> 'conditions_add_more_callback',
				'wrapper' 		=> 'condition_id',
				)
			);
			
		// Enter Observation //
		
		$form['application_forward']['observations'] = array(
			'#type' 			=> 'fieldset',
			'#title' 			=> t('Enter Observations'),
			'#prefix' 			=> '<div id="observation_id" class="col-lg-12 col-md-12 col-sm-12">',
			'#suffix' 			=> '</div>',
		);
	
		if (empty($form_state['observation_no'])) {
			$form_state['observation_no'] = 1;
		}
	
		for ($j = 0; $j < $form_state['observation_no']; $j++) {
	
			$form['application_forward']['observations']['observation_'.$j] = array(
				'#prefix' 		=> '<div class="col-md-4"><label class="input label-block">',
				'#suffix' 		=> '</label></div>',
				'#type' 		=> 'textfield',
				'#title' 		=> '',
				'#size' 		=> 150,
				'#description' 	=> t('Observation'),
				'#attributes' 	=> array('multiple' => 'multiple'),
			);
			
			$form['application_forward']['observations']['observation_comment_'.$j] = array(
				'#prefix' 		=> '<div class="col-md-8"><label class="input label-block">',
				'#suffix' 		=> '</label></div>',
				'#type' 		=> 'textfield',
				'#description' 	=> t('Comment'),
			);
		}
	
		$form['application_forward']['observations']['add_observations'] = array(
			'#prefix' 			=> '<div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div>',
			'#attributes' 		=> array('class' => array('btn btn-dark')),
			'#type' 			=> 'submit',
			'#value' 			=> t('Add more Observation'),
			'#submit' 			=> array('observations_add_more_add_one'),
			'#ajax' 			=> array(
				'callback' 		=> 'observations_add_more_callback',
				'wrapper' 		=> 'observation_id',
				)
			);	

		// Enter Observation //
		
		// Enter Predefined Observation //
		
		/*$form['application_forward']['pre_observations'] = array(
			'#type' 			=> 'fieldset',
			'#title' 			=> t('General Observations'),
			'#prefix' 			=> '<div id="pre_observation_id" class="col-lg-12 col-md-12 col-sm-12">',
			'#suffix' 			=> '</div>',
		);
		
		$observations_list 	= observation_list();
		//print_r($observations_list);
		for ($k = 0; $k < count($observations_list); $k++) {
	
			$form['application_forward']['pre_observations']['pre_observation_'.$k] = array(
				'#prefix' 		=> '<div class="col-md-4"><label class="input label-block">'.$observations_list[$k]->observations,
				'#suffix' 		=> '</label></div>',
				'#type' 		=> 'hidden',
				'#value'		=> $observations_list[$k]->id,
			);
			
			$form['application_forward']['pre_observations']['pre_observation_comment_'.$k] = array(
				'#prefix' 		=> '<div class="col-md-8"><label class="input label-block">',
				'#suffix' 		=> '</label></div>',
				'#type' 		=> 'textfield',
				'#description' 	=> t('Comment'),
			);
		}*/
	
		// END Predefined Observation //
		}
		
		if($action == 4){
			$factoryzone = get_factory_zone();
			$default_zone 	= array(""=>"- Select Zone -");
			foreach($factoryzone as $val){
				$factzonefinal[$val->zone_id] = $val->zone_name;
				$factzonefinal1 = ($default_zone+$factzonefinal);
				}
			$form['application_forward']['application_zone_change'] = array(
			'#prefix' 			=> '<div id="zone_change_id"><div class="col-md-4 col-xs-8"><label class="select label-block">Zone',
			'#suffix' 			=> '</label></div></div>',
			'#type' 			=> 'select',
			'#options' 			=> $factzonefinal1,
			'#default_value' 	=> $factory_zone,
			//'#description' => '<font color="#FF0000">Note:-As per Concents to establishment</font>'
			 );
			 $form['application_forward']['application_zone_change_note'] = array(
			'#prefix' 			=> '<div id="zone_remark"><div class="col-md-4"><label class="input label-block">Write A Remark About Zone Change:',
			'#suffix' 			=> '</label></div></div>',
			'#type' 			=> 'textfield',
			//'#default_value'  => !empty($content['remarks']) ? $content['remarks'] : '',
			);
		}
	
		// ---------------  Add more text box ends ---------------------------------
		
		
		$form['application_forward']['submit'] = array(
			'#prefix' 			=> '<div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div></div></div></div>',
			'#attributes' 		=> array('class' => array('btn btn-dark'), 'onclick' => 'if(!confirm("Are you sure to continue ?")){return false;}'),
			'#type' 			=> 'submit',
			'#value' 			=> 'Send'
		);
	} else { 
	
		
	/*$form['applicantion_verify']['start_list_1']	 = array(
		'#markup' 		=> '
		  <h2>Checklist</h2>
		  <p>Display all checklisted conditions and comments</p>                                                                                      
		  <div class="table-responsive">          
		  <table class="table">
			<thead>
			  <tr>
				<th width="20%">Conditions</th>
				<th width="20%">Assistant Director Chemical(Remarks)</th>
				<th width="20%">Deputy Director Chemical(Remarks)</th>
				<th width="20%">Joint Director Chemical(Remarks)</th>
			  </tr>
			</thead>
			<tbody> '
	);

	$is_chemical = 1;
	$checklist = get_checklist_data($application_id,$factory_type_id,$is_chemical);
	if(!empty($checklist))
	{
		$i=1;
			foreach($checklist as $row){
			if($row->observations_id){ 
					$observation_list = get_observations_details($row->observations_id);
				}
			elseif(!empty($row->ad_extra_observation)){
					$observation_list = $row->ad_extra_observation;
				}
			elseif(!empty($row->dd_extra_observation)){
					$observation_list = $row->dd_extra_observation;
				}else{
					$observation_list = $row->jd_extra_observation;
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
						'#markup'			=> '</br>'.$observation_list,
						'#id'				=> 'range',
						'#attributes' 		=> array('class'=>array('form-control'),'readonly' => 'readonly'),
						'#default_value'	=> '',
					);
			$split_value = explode(',',$row->ad_details);
			$username =!empty($split_value[1])?'<b>Name:-</b>'.$split_value[1]:'';
			$form['applicantion_verify']['data_details_ad_'.$i] 	= array(
						'#prefix' 			=> '<td>',
						'#suffix' 	 		=> '</td>',
						'#type' 			=> 'markup',
						'#markup'			=> '</br>'.$row->remark_by_ad.'</br>'.$username,
						'#attributes' 		=> array('class'=>array('form-control')),
						'#default_value'	=> '',
					);
			
			$options = array(1=> t('Yes'), 0 => t('No'),);
			$dd_split_value = explode(',',$row->dd_details);	
			$dd_username =!empty($dd_split_value[1])?'Name:-'.$dd_split_value[1]:'';
			if($dd_split_value[2]==1) { $v = $dd_split_value[2]; }else{$v =  0;}	
			//if(!empty($row->remark_table_id)){	
			if(empty($row->dd_extra_observation)){
				$form['applicantion_verify']['check_option_'.$i] = array(
					  '#prefix' 	=> '<td>',		 
					  '#type' 		=> 'radios',
					  '#options' 	=> $options,
					  '#title' 		=> t('Do you agree or not?'),
					  '#default_value' =>  $v,
					  '#attributes' 	=> array('class'=>array(''),'disabled' => 'disabled'),
					);
				}else{
					$form['applicantion_verify']['check_option_'.$i] = array(
					  '#prefix' 	=> '<td>',		 
					  '#type' 		=> 'markup',
					
					);
			}
			$data_dd = !empty($dd_split_value[1])? '</br>'.$row->remark_by_dd.'</br><b>Name:-</b>'.$dd_split_value[1].'</br>':'';
			$form['applicantion_verify']['data_list_dd_'.$i] 	= array(
					'#suffix' 	 		=> '</td>',
					'#type' 			=> 'markup',
					'#markup'			=> $data_dd,
					'#attributes' 		=> array('class'=>array('form-control')),
					'#default_value'	=> '',
			);
		
			$options = array(1=> t('Yes'), 0 => t('No'),);
			$jd_split_value = explode(',',$row->jd_details);
			$jd_username =!empty($jd_split_value[1])?'<b>Name:-</b>'.$jd_split_value[1]:'';	
			if($jd_split_value[2] == 1) { $view = $jd_split_value[2]; }else{$view =  0;}
			if(empty($row->jd_extra_observation)){	
			$form['applicantion_verify']['check_option_jd_'.$i] = array(
					  '#prefix' 		=> '<td>',
					  '#type' 			=> 'radios',
					  '#options' 		=> $options,
					  '#title' 			=> t('Do you agree or not?'),
					  '#default_value' 	=> $view ,
					  '#attributes' 	=> array('class'=>array(),),
					  '#attributes' 		=> array('class'=>array(''),'disabled' => 'disabled'),

			);
			}else{
			$form['applicantion_verify']['check_option_jd_'.$i] = array(
					  '#prefix' 		=> '<td>',
					  '#type' 			=> 'markup',	
				);
			}
			$form['applicantion_verify']['data_list_jd_'.$i] 	= array(
					'#suffix' 	 		=> '</td>',
					'#type' 			=> 'markup',
					'#attributes' 		=> array('class'=>array('form-control')),
					'#markup'			=> '</br>'.$row->remark_by_jd.'</br>'.$jd_username,
					'#default_value'	=> '',
				);
				
				$i++;
			}
	  
	  	$form['applicantion_verify']['end_list_1']	 = array(
			'#markup' 		=> '</tbody></table></div>',
		);
	  
	  } else {
		  
		$form['applicantion_verify']['end_list_1']	 = array(
			'#markup' 		=> '<tr>
				<th colspan="4">No data found</th>
			  </tr></tbody></table></div>',
		);
	  }*/
	}
 	return $form;
 }
 
function get_ajax_note($form, &$form_state)
{
    $commands   = array();
	$commands[] = ajax_command_replace('#remark_id', drupal_render($form['application_forward']['application_remark']));
	$commands[] = ajax_command_replace('#notesheet_id', drupal_render($form['application_forward']['application_note']));
	$commands[] = ajax_command_replace('#condition_id', drupal_render($form['application_forward']['conditions']));
	$commands[] = ajax_command_replace('#observation_id', drupal_render($form['application_forward']['observations']));
	$commands[] = ajax_command_replace('#pre_observation_id', drupal_render($form['application_forward']['pre_observations']));
	$commands[] = ajax_command_replace('#reject_id', drupal_render($form['application_forward']['application_reject']));
	$commands[] = ajax_command_replace('#zone_change_id', drupal_render($form['application_forward']['application_zone_change']));


	$commands[] = ajax_command_replace('#zone_remark', drupal_render($form['application_forward']['application_zone_change_note']));
    return array('#type' => 'ajax', '#commands' => $commands);
}

// ---------------  AJAX CALLBACK FUNCTIONS FOR TEXT FIELD-----------------

function conditions_add_more_add_one($form, &$form_state) {
	//echo "TEST"; die;
	
	if (!isset($form_state['condition_no'])) {
		$form_state['condition_no'] = 0;
		$form_state['condition_no']++;
	}

	$form_state['condition_no']++;
	$form_state['rebuild'] = TRUE;
}

function conditions_add_more_callback($form, $form_state) {
	return $form['application_forward']['conditions'];
}

function observations_add_more_add_one($form, &$form_state) {
	//echo "TEST"; die;
	
	if (!isset($form_state['observation_no'])) {
		$form_state['observation_no'] = 0;
		$form_state['observation_no']++;
	}

	$form_state['observation_no']++;
	$form_state['rebuild'] = TRUE;
}

function observations_add_more_callback($form, $form_state) {
	return $form['application_forward']['observations'];
}	
// ---------------  AJAX CALLBACK  FUNCTIONS FOR TEXT FIELD-----------------
	
function get_verifing_data($application_id,$service_id,$factory_type_id,$reference_no){
	//echo $reference_no;
	global $base_root,$base_path,$user;		 
	$user_id = $user->uid;
		
	$veryfing_details 	= array();
	$veryfing_details 	= get_application_withid($application_id);
	$occupier_details   = get_all_occupier_data($application_id,$service_id,$factory_type_id,$reference_no);
	$owner_details 		= get_all_owner_data($application_id,$service_id,$factory_type_id,$reference_no);
	$worker_details 	= get_worker_details_service($service_id,$factory_type_id,$application_id,$reference_no);
	
	//$plan_approve_status  =   $veryfing_details[0]->plan_approve_status;
	$plan_approve_status  = find_chemical_status($application_id);
	//$plan_approve_status2  = find_general_status($application_id);
	
	$chem_status = find_chemical_status($application_id);
	$gen_status  = find_general_status($application_id);

	$getdata_director_paddress =  array('district_director','sub_division_director','area_type_director','block_mun_cor_sez_not_director','grm_ward_sector_not_director','police_station_director','pincode_director','state_director','post_office_director');

	/* FACTORY ADDRESS PART */
	$getdata_factory_address 	=  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$getdata_headoffice_address =  array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
	$getdata_communication_address = array('district_comm','subdivision_comm','areatype_comm','block_comm','panchayat_comm','policestation_comm','pincodecomm','state_comm','postoffice_comm');
	$getdata_owner_premises_address 	=  array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
	$getdata_occupier_permanent_address =  array('district_oprmntadr','subdivision_oprmntadr','areatype_oprmntadr','block_oprmntadr','panchayat_oprmntadr','policestation_oprmntadr','pincodeoprmntadr','state_oprmntadr','postoffice_oprmntadr');
	$getdata_occupier_present_address =  array('district_oprsntadr','subdivision_oprsntadr','areatype_oprsntadr','block_oprsntadr','panchayat_oprsntadr','policestation_oprsntadr','pincodeoprsntadr','state_oprsntadr','postoffice_oprsntadr');
	$estate_type 		       = get_estate_type($veryfing_details[0]->estate_type);
	if($veryfing_details[0]->tm_appliction_id==NULL)
	{
		$country_name 		       = country_name($occupier_details[0]->country_oprmntadr);
		$country_name_oprsntadr    = country_name($occupier_details[0]->country_oprsntadr);
		$country_premises 		   = country_name($veryfing_details[0]->country_premises);
	}
	else
	{
		$country_name='INDIA'; $country_name_oprsntadr='INDIA'; $country_premises ='INDIA';
	}
$country_name='INDIA'; $country_name_oprsntadr='INDIA'; $country_premises ='INDIA';
	foreach($veryfing_details as $details_address_info){
		$factory_address 			= get_full_address('fa_cafa','sub-table',$details_address_info->id,$getdata_factory_address);
		$headoffice_address 		= get_full_address('fa_cafa','sub-table',$details_address_info->id,$getdata_headoffice_address);
		$communication_address 		= get_full_address('fa_cafa','sub-table',$details_address_info->id,$getdata_communication_address);
		$permanent_address        	= get_full_address('fa_occupier_details','sub-table',$details_address_info->id,$getdata_occupier_permanent_address);
		$present_address          	= get_full_address('fa_occupier_details','sub-table',$details_address_info->id,$getdata_occupier_present_address);
		$owner_premises_address 	= get_full_address('fa_cafa','sub-table',$details_address_info->id,$getdata_owner_premises_address);		
		}
			$get_remark = db_select('fa_cafa_remarks', 'remarks');
			$get_remark->fields('remarks', array('verify_details'));
			$get_remark->condition('remarks.app_id', trim($application_id));
			//$get_remark->condition('remarks.remark_by_uid', trim($user_id), '=');
			$get_remark->condition('remarks.plan_status_chem', '', '!='); 
			$get_remark->orderBy('remarks.id','DESC');
			$get_remark->range(0, 1);
			$get_remark_result = $get_remark->execute();		
			$content = $get_remark_result->fetchAssoc();
			
			$remark_field = explode(',', $content['verify_details']);
			
			// CHECK STATUS AND BLOCK THE CHECKBOX ACCORDINGLY
			if($plan_approve_status != 'AICh' && $plan_approve_status != 'AIChBk')
			{ $disable = "disabled";} else { $disable = "";}

			foreach ($remark_field as $fieldname){ 
				if($fieldname == 'factory_name'){ $factory_name_ck = "checked='checked'";}
				if($fieldname == 'gstin_no'){ $gstin_no_ck = "checked='checked'";}
				if($fieldname == 'udyog_aadhaar'){ $udyog_aadhaar_ck = "checked='checked'";}
				if($fieldname == 'trade_license_no'){ $trade_license_no_ck = "checked='checked'";}
				if($fieldname == 'enargy_no'){ $enargy_no_ck = "checked='checked'";}
				if($fieldname == 'cin_no'){ $cin_no_ck = "checked='checked'";}
				if($fieldname == 'factory_previous_name'){ $factory_previous_name_ck = "checked='checked'";}
				if($fieldname == 'factory_location'){ $zone_name_ck = "checked='checked'";}
				if($fieldname == 'factory_headoffice'){ $factory_headoffice_ck = "checked='checked'";}
				if($fieldname == 'factory_communication'){ $factory_communication_ck = "checked='checked'";}
				if($fieldname == 'factory_pan'){ $factory_pan_ck = "checked='checked'";}
				if($fieldname == 'name_occupier'){ $occupier_name_ck = "checked='checked'";}
				if($fieldname == 'age_occupier'){ $occupier_age_ck = "checked='checked'";}
				if($fieldname == 'father_husband_name_occupier'){ $occupier_gurdian_name_ck = "checked='checked'";}
				if($fieldname == 'occupier_telephone'){ $occupier_telephone_ck = "checked='checked'";}
				if($fieldname == 'occupier_fax_no'){ $occupier_fax_no_ck = "checked='checked'";}
				if($fieldname == 'occupier_mobile'){ $occupier_mobile_ck = "checked='checked'";}
				if($fieldname == 'occupier_email_id'){ $occupier_email_id_ck = "checked='checked'";}
				if($fieldname == 'occupier_type'){ $occupier_type_ck = "checked='checked'";}
				if($fieldname == 'country_oprmntadr'){ $country_oprmntadr_ck = "checked='checked'";}
				if($fieldname == 'occupier_present_address'){ $occupier_present_address_ck = "checked='checked'";}
				if($fieldname == 'owner_name'){ $owner_name_ck = "checked='checked'";}
				if($fieldname == 'owner_address'){ $owner_address_ck = "checked='checked'";}
				if($fieldname == 'plant_installed'){ $plant_installed_ck = "checked='checked'";}
				if($fieldname == 'wbpcb_category_name'){ $wbpcb_category_name_ck = "checked='checked'";}

				if($fieldname == 'contactual_worker_men'){ $contactual_worker_men_ck = "checked='checked'";}
				if($fieldname == 'contactual_worker_women'){ $contactual_worker_women_ck = "checked='checked'";}
				if($fieldname == 'contactual_adolescents_male'){ $contactual_adolescents_male_ck = "checked='checked'";}
				if($fieldname == 'contactual_adolescents_female'){ $contactual_adolescents_female_ck = "checked='checked'";}
				if($fieldname == 'contactual_children_male'){ $contactual_children_male_ck = "checked='checked'";}
				if($fieldname == 'contactual_children_female'){ $contactual_children_female_ck = "checked='checked'";}
				if($fieldname == 'permanent_worker_men'){ $permanent_worker_men_ck = "checked='checked'";}
				if($fieldname == 'permanent_worker_women'){ $permanent_worker_women_ck = "checked='checked'";}
				if($fieldname == 'permanent_adolescents_male'){ $permanent_adolescents_male_ck = "checked='checked'";}
				if($fieldname == 'permanent_adolescents_female'){ $permanent_adolescents_female_ck = "checked='checked'";}
				if($fieldname == 'permanent_children_male'){ $permanent_children_male_ck = "checked='checked'";}
				if($fieldname == 'permanent_children_female'){ $permanent_children_female_ck = "checked='checked'";}	
			}

		if($service_id == '5')
		{
			$previous_factory_name = '<tr><td>Previous Factory Name</td><td>'.$veryfing_details[0]->factory_previous_name.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="factory_previous_name" class="inspectorchemical_verify_check" '.$factory_previous_name_ck .'/><label for="factory_previous_name"></label></div></td></tr>';
		} else {$previous_factory_name = '';}

		$addrline = !empty($factory_address) ? '<br>'.$veryfing_details[0]->addrline : $veryfing_details[0]->addrline;
		$addrline_off = !empty($headoffice_address) ? '<br>'.$veryfing_details[0]->addrline_off : $veryfing_details[0]->addrline_off;
		$addrline_oprmntadr = !empty($permanent_address) ? '<br>'.$veryfing_details[0]->addrline_oprmntadr : $veryfing_details[0]->addrline_oprmntadr;
		$addrline_oprsntadr = !empty($present_address) ? '<br>'.$veryfing_details[0]->addrline_oprsntadr : $veryfing_details[0]->addrline_oprsntadr;
		$addrline_premises = !empty($owner_premises_address) ? '<br>'.$veryfing_details[0]->addrline_premises : $veryfing_details[0]->addrline_premises;
			
		$output .= '<table cellpadding="0" cellspacing="0" border="0" width="100%" class="table no-margin# remove-odd-even# custom-table-view-dashboard">';
		
		$output .= '<tr><th width="25%">Parameter</th><th>Input</th><th width="11%" class="center"><div class="checkbox"> <input type="checkbox" '.$disable.' id="selectall_inspectorchemical"/><label for="selectall_inspectorchemical" style="color:#fff;">Check </label></div></th></tr>
					<tr><td colspan="3"><b>FACTORY INFORMATION</b></td></tr>
					<tr><td>Factory Name</td><td>'.$veryfing_details[0]->factory_name.'</td>
					<td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="factory_name" class="inspectorchemical_verify_check" '.$factory_name_ck .'/><label for="factory_name"></label></div></td>
					</tr>'.$previous_factory_name.'
					<tr><td>GSTIN Number</td><td>'.$veryfing_details[0]->gstin_no.'</td>
						<td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="gstin_no" class="inspectorchemical_verify_check" '.$gstin_no_ck .'/><label for="gstin_no"></label></div></td>
					</tr>
					<tr><td>Udyog Aadhaar No</td><td>'.$veryfing_details[0]->udyog_aadhaar.'</td>
						<td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="udyog_aadhaar" class="inspectorchemical_verify_check" '.$udyog_aadhaar_ck .'/><label for="udyog_aadhaar"></label></div></td>
					</tr>
					<tr><td>Trade License No</td><td>'.$veryfing_details[0]->trade_license_no.'</td>
						<td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="trade_license_no" class="inspectorchemical_verify_check" '.$trade_license_no_ck .'/><label for="trade_license_no"></label></div></td>
					</tr>
					<tr><td>Energy Meter No</td><td>'.$veryfing_details[0]->enargy_no.'</td>
						<td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="enargy_no" class="inspectorchemical_verify_check" '.$enargy_no_ck .'/><label for="enargy_no"></label></div></td>
					</tr>
					<tr><td>CIN No</td><td>'.$veryfing_details[0]->cin_no.'</td>
						<td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="cin_no" class="inspectorchemical_verify_check" '.$cin_no_ck .'/><label for="cin_no"></label></div></td>
					</tr>';

		$output .= '<tr><td colspan="3"><b>LOCATION OF FACTORY</b></td></tr>
					<tr><td>Factory Zone</td><td>'.$veryfing_details[0]->zone_name.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="factory_location" class="inspectorchemical_verify_check" '.$zone_name_ck.'/><label for="factory_location"></label></div></td></tr>
					<tr><td>Factory Address</td><td colspan="2">'.$factory_address.''.$addrline.'</td></tr>
					<tr><td>Nearest Landmark</td><td colspan="2">'.$veryfing_details[0]->nearest_landmark.'</td></tr>
					<tr><td>Estate Type</td><td colspan="2">'.$estate_type[0]->estate_name.'</td></tr>';

		$output .= '<tr><td colspan="3"><b>ADDRESS OF THE REGISTERED / HEAD OFFICE </b></td></tr>
					<tr><td>Registered / Head office Address</td><td>'.$headoffice_address.''.$addrline_off.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="factory_headoffice" class="inspectorchemical_verify_check" '.$factory_headoffice_ck.'/><label for="factory_headoffice"></label></div></td></tr>
					<tr><td>Mobile</td><td colspan="2">'.$veryfing_details[0]->comm_mobile.'</td></tr>
					<tr><td>Alternate Mobile</td><td colspan="2">'.$veryfing_details[0]->comm_alt_mobile.'</td></tr>
					<tr><td>Telephone</td><td colspan="2">'.$veryfing_details[0]->comm_telephone.'</td></tr>
					<tr><td>Fax</td><td colspan="2">'.$veryfing_details[0]->comm_fax.'</td></tr>
					<tr><td>Email</td><td colspan="2">'.$veryfing_details[0]->comm_email.'</td></tr>';

		$output .= '<tr><td colspan="3"><b>COMMUNICATION ADDRESS</b></td></tr>
					<tr><td>Address</td><td>'.$communication_address.''.$addrline_comm.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="factory_communication" class="inspectorchemical_verify_check" '.$factory_communication_ck.'/><label for="factory_communication"></label></div></td></tr>';

		$output .= '<tr><td colspan="3"><b>PAN OF BUSINESS ESTABLISHMENT / FACTORY / COMPANY</b></td></tr>
					<tr><td>PAN</td><td>'.$veryfing_details[0]->factory_pan.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="factory_pan" class="inspectorchemical_verify_check" '.$factory_pan_ck.'/><label for="factory_pan"></label></div></td></tr>';

		$output .= '<tr><td colspan="3"><b>DETAILS OF OCCUPIER</b></td></tr>
					<tr><td>Name</td><td>'.$occupier_details[0]->name_occupier.' '.$occupier_details[0]->occupier_name_middle.' '.$occupier_details[0]->occupier_name_last.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="name_occupier" class="inspectorchemical_verify_check" '.$occupier_name_ck.'/><label for="name_occupier"></label></div></td></tr>
					<tr><td>Age</td><td>'.$occupier_details[0]->age_occupier.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="age_occupier" class="inspectorchemical_verify_check" '.$occupier_age_ck.'/><label for="age_occupier"></label></div></td></tr>
					<tr><td>Father\'s/Husband\'s name</td><td>'.$occupier_details[0]->father_husband_name_occupier.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="father_husband_name_occupier" class="inspectorchemical_verify_check" '.$occupier_gurdian_name_ck.'/><label for="father_husband_name_occupier"></label></div></td></tr>
					<tr><td>Telephone Number</td><td>'.$occupier_details[0]->occupier_telephone.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="occupier_telephone" class="inspectorchemical_verify_check" '.$occupier_telephone_ck.'/><label for="occupier_telephone"></label></div></td></tr>
					<tr><td>Fax No.</td><td>'.$occupier_details[0]->occupier_fax_no.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="occupier_fax_no" class="inspectorchemical_verify_check" '.$occupier_fax_no_ck.'/><label for="occupier_fax_no"></label></div></td></tr>
					<tr><td>Registered Mobile Number</td><td>'.$occupier_details[0]->occupier_mobile.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="occupier_mobile" class="inspectorchemical_verify_check" '.$occupier_mobile_ck.'/><label for="occupier_mobile"></label></div></td></tr>
					<tr><td>Email Id</td><td>'.$occupier_details[0]->occupier_email_id.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="occupier_email_id" class="inspectorchemical_verify_check" '.$occupier_email_id_ck.'/><label for="occupier_email_id"></label></div></td></tr>
					<tr><td>Occupier Type</td><td>'.$occupier_details[0]->type_occupier.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="occupier_type" class="inspectorchemical_verify_check" '.$occupier_type_ck.'/><label for="occupier_type"></label></div></td></tr>';
					
	  if($occupier_details[0]->country_oprmntadr == 99) 
	  {	   
	  	$Occupier_Permanent_Address = '<tr><td> Aadhaar No</td><td colspan="2">'.$occupier_details[0]->aadhaar_oprmntadr.'</td></tr>
									  <tr><td> Address </td><td colspan="2">'.$permanent_address.''.$addrline_oprmntadr.'</td></tr>
									  <tr><td> Street Name</td><td colspan="2">'.$occupier_details[0]->street_name_oprmntadr.'</td></tr>
									  <tr><td> House No.</td><td colspan="2">'.$occupier_details[0]->house_no_oprmntadr.'</td></tr>';
	  }
	  else{	  	
	  	$Occupier_Permanent_Address = '<tr><td> Passport No</td><td colspan="2">'.$occupier_details[0]->passport_oprmntadr.' <b>(DOI):</b>'.$occupier_details[0]->passport_date_of_issue_oprmntadr.' <b>(DOE):</b>'.$occupier_details[0]->passport_date_of_expiry_oprmntadr.'</td></tr>
									  <tr><td> Street Name</td><td colspan="2">'.$occupier_details[0]->street_name_oprmntadr.'</td></tr>
									  <tr><td> House No.</td><td colspan="2">'.$occupier_details[0]->house_no_oprmntadr.'</td></tr>
									  <tr><td> Police Station</td><td colspan="2">'.$occupier_details[0]->police_station_oprmntadr.'</td></tr>';
	  }

	  if($occupier_details[0]->country_oprsntadr == 99) 
	  {	  
	  	$Occupier_Present_Address = '<tr><td> Aadhaar No</td><td colspan="2">'.$occupier_details[0]->aadhaar_oprsntadr.'</td></tr>
								     <tr><td> Address</td><td colspan="2">'.$present_address.''.$addrline_oprsntadr.'</td></tr>
									 <tr><td> Street Name</td><td colspan="2">'.$occupier_details[0]->street_name_oprsntadr.'</td></tr>
									 <tr><td> House No.</td><td colspan="2">'.$occupier_details[0]->house_no_oprsntadr.'</td></tr>';
	  }
	  else{	  	
	  	$Occupier_Present_Address = '<tr><td> Passport No</td><td colspan="2">'.$occupier_details[0]->passport_oprsntadr.' <b>(DOI):</b>'.$occupier_details[0]->passport_date_of_issue_oprsntadr.' <b>(DOE):</b>'.$occupier_details[0]->passport_date_of_expiry_oprsntadr.'</td></tr>
									  <tr><td> Street Name</td><td colspan="2">'.$occupier_details[0]->street_name_oprsntadr.'</td></tr>
									  <tr><td> House No.</td><td colspan="2">'.$occupier_details[0]->house_no_oprsntadr.'</td></tr>
									  <tr><td> Police Station</td><td colspan="2">'.$occupier_details[0]->police_station_oprsntadr.'</td></tr>';
	  }

	  if($veryfing_details[0]->country_premises == 99) 
	  {	  
	  	$Owner_Address = '<tr><td> Aadhaar No</td><td colspan="2">'.$veryfing_details[0]->aadhaar_premises.'</td></tr>
						  <tr><td> Address</td><td colspan="2">'.$owner_premises_address.''.$addrline_premises.'</td></tr>
						  <tr><td> Street Name</td><td colspan="2">'.$veryfing_details[0]->street_name_premises.'</td></tr>
						  <tr><td> House No.</td><td colspan="2">'.$veryfing_details[0]->house_no_premises.'</td></tr>';
	  }
	  else{	  	
	  	$Owner_Address = '<tr><td> Passport No</td><td colspan="2">'.$veryfing_details[0]->passport_premises.' <b>(DOI):</b>'.$veryfing_details[0]->passport_date_of_issue_premises.' <b>(DOE):</b>'.$veryfing_details[0]->passport_date_of_expiry_premises.'</td></tr>
						  <tr><td> Street Name</td><td colspan="2">'.$veryfing_details[0]->street_name_premises.'</td></tr>
						  <tr><td> House No.</td><td colspan="2">'.$veryfing_details[0]->house_no_premises.'</td></tr>
						  <tr><td> Police Station</td><td colspan="2">'.$veryfing_details[0]->police_station_premises.'</td></tr>';
	  }

		$output .= '<tr><td colspan="3"><b>OCCUPIER PERMANENT ADDRESS</b></td></tr>
					<tr><td>Nationality</td><td>'.$country_name.'</td>
						<td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="country_oprmntadr" class="inspectorchemical_verify_check" '.$country_oprmntadr_ck.'/><label for="country_oprmntadr"></label></div></td>
					</tr>'.$Occupier_Permanent_Address;
					
		$output .= '<tr><td colspan="3"><b>OCCUPIER PRESENT ADDRESS</b></td></tr>
					<tr><td>Nationality</td><td>'.$country_name_oprsntadr.'</td>
						<td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="occupier_present_address" class="inspectorchemical_verify_check" '.$occupier_present_address_ck.'/><label for="occupier_present_address"></label></div></td>
					</tr>'.$Occupier_Present_Address;
		
		$output .= '<tr><td colspan="3"><b>DETAILS OF OWNER/LAND LORD/LESSOR OF THE PREMISES OCCUPIED AS A FACTORY</b></td></tr>
					<tr><td>Owner Name</td><td>'.$owner_details[0]->owner_name.' '.$owner_details[0]->owner_mname.' '.$owner_details[0]->owner_lname.'</td>
						<td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="owner_name" class="inspectorchemical_verify_check" '.$owner_name_ck.'/><label for="owner_name"></label></div></td></tr>
					<tr><td>Nationality</td><td>'.$country_premises.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="owner_address" class="inspectorchemical_verify_check" '.$owner_address_ck.'/><label for="owner_address"></label></div></td></tr>'.$Owner_Address;

		$output .= '<tr><td colspan="3"><b>PARTICULAR OF PLAN TO BE INSTALLED</b></td></tr>
					<tr><td>Plant To be Installed</td><td>'.$veryfing_details[0]->plant_installed.'</td>
						<td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="plant_installed" class="inspectorchemical_verify_check" '.$plant_installed_ck.'/><label for="plant_installed"></label></div></td></tr>';
					
				if($veryfing_details[0]->wbpcb_category_name ==1){$consent ='Red'; $wbpcb_reference_no = $veryfing_details[0]->wbpcb_reference_no;$wbpcb_ref_date = date('dS M Y', strtotime($veryfing_details[0]->wbpcb_ref_date));}
				if($veryfing_details[0]->wbpcb_category_name ==2){$consent ='Green'; $wbpcb_reference_no = $veryfing_details[0]->wbpcb_reference_no;$wbpcb_ref_date = date('dS M Y', strtotime($veryfing_details[0]->wbpcb_ref_date));}
				if($veryfing_details[0]->wbpcb_category_name ==3){$consent ='Orange'; $wbpcb_reference_no = $veryfing_details[0]->wbpcb_reference_no;$wbpcb_ref_date = date('dS M Y', strtotime($veryfing_details[0]->wbpcb_ref_date));}
				
				if($veryfing_details[0]->wbpcb_category_name == 4){
				$consent ='White'; 
				$wbpcb_reference_no = 'n/a'; 
				$wbpcb_ref_date = 'n/a';
				$file = $veryfing_details[0]->wbpcb_intimation_letter;
				$file_url = '<a href='.file_create_url(get_uploaded_document_url($file)).' target= "_BLANK" onclick = "popIt(this.href);return false;">View</a>';
				}
				if($veryfing_details[0]->wbpcb_category_name==5){$consent ='Exempted'; $wbpcb_reference_no = 'n/a';$wbpcb_ref_date = 'n/a';}
		

	$output .= '<tr><td colspan="3"><b>FACTORY IDENTIFICATION ACCORDING TO WBPCB</td></tr>
				<tr><td>(i) Categories of wbpcb</td><td>'.$consent.'</td>
					<td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="wbpcb_category_name" class="inspectorchemical_verify_check" '.$wbpcb_category_name_ck.'/><label for="wbpcb_category_name"></label></div></td></tr>
				<tr><td>(ii) Reference number of approval of arrangments</td><td colspan="2">'.$wbpcb_reference_no.'</td></tr>
				<tr><td>(iii) Date of approval of arrangments</td><td colspan="2">'.$wbpcb_ref_date.'</td></tr>';

		$output .= '<tr><td colspan="3"><b>WORKER DETAILS (PERMANENT)</b></td></tr>
					<tr><td>No. of Male Worker</td><td>'.$worker_details[0]->permanent_worker_men.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="permanent_worker_men" class="inspectorchemical_verify_check" '.$permanent_worker_men_ck.'/><label for="permanent_worker_men"></label></div></td></tr>
					<tr><td>No. of Female Worker</td><td>'.$worker_details[0]->permanent_worker_women.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="permanent_worker_women" class="inspectorchemical_verify_check" '.$permanent_worker_women_ck.'/><label for="permanent_worker_women"></label></div></td></tr>			
					<tr><td>No. of Male Adolescents Worker <br><span class="text-red" style="font-size:10px;">(over 15 but under 18 years of age)</span></td><td>'.$worker_details[0]->permanent_adolescents_male.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="permanent_adolescents_male" class="inspectorchemical_verify_check" '.$permanent_adolescents_male_ck.'/><label for="permanent_adolescents_male"></label></div></td></tr>
					<tr><td>No. of Female Adolescents Worker</td><td>'.$worker_details[0]->permanent_adolescents_female.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="permanent_adolescents_female" class="inspectorchemical_verify_check" '.$permanent_adolescents_female_ck.'/><label for="permanent_adolescents_female"></label></div></td></tr>			
					<tr><td>No. of Male Children Worker <br><span class="text-red" style="font-size:10px;">(over 14 but under 15 years of age)</span></td><td>'.$worker_details[0]->permanent_children_male.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="permanent_children_male" class="inspectorchemical_verify_check" '.$permanent_children_male_ck.'/><label for="permanent_children_male"></label></div></td></tr>
					<tr><td>No. of Female Children Worker</td><td>'.$worker_details[0]->permanent_children_female.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="permanent_children_female" class="inspectorchemical_verify_check" '.$permanent_children_female_ck.'/><label for="permanent_children_female"></label></div></td></tr>';

		$output .= '<tr><td colspan="3"><b>WORKER DETAILS (CONTRACTUAL)</b></td></tr>
					<tr><td>No. of Male Worker</td><td>'.$worker_details[0]->contactual_worker_men.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="contactual_worker_men" class="inspectorchemical_verify_check" '.$contactual_worker_men_ck.'/><label for="contactual_worker_men"></label></div></td></tr>
					<tr><td>No. of Female Worker</td><td>'.$worker_details[0]->contactual_worker_women.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="contactual_worker_women" class="inspectorchemical_verify_check" '.$contactual_worker_women_ck.'/><label for="contactual_worker_women"></label></div></td></tr>			
					<tr><td>No. of Male Adolescents Worker <br><span class="text-red" style="font-size:10px;">(over 15 but under 18 years of age)</span></td><td>'.$worker_details[0]->contactual_adolescents_male.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="contactual_adolescents_male" class="inspectorchemical_verify_check" '.$contactual_adolescents_male_ck.'/><label for="contactual_adolescents_male"></label></div></td></tr>
					<tr><td>No. of Female Adolescents Worker</td><td>'.$worker_details[0]->contactual_adolescents_female.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="contactual_adolescents_female" class="inspectorchemical_verify_check" '.$contactual_adolescents_female_ck.'/><label for="contactual_adolescents_female"></label></div></td></tr>			
					<tr><td>No. of Male Children Worker <br><span class="text-red" style="font-size:10px;">(over 14 but under 15 years of age)</span></td><td>'.$worker_details[0]->contactual_children_male.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="contactual_children_male" class="inspectorchemical_verify_check" '.$contactual_children_male_ck.'/><label for="contactual_children_male"></label></div></td></tr>
					<tr><td>No. of Female Children Worker</td><td>'.$worker_details[0]->contactual_children_female.'</td><td class="center"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="contactual_children_female" class="inspectorchemical_verify_check" '.$contactual_children_female_ck.'/><label for="contactual_children_female"></label></div></td></tr>';
				
	$documentList =  get_plan_document_lists($service_id,$factory_type_id);
	//echo '<pre>'; print_r($documentList);
	//$get_uploaded_doc = get_uploaded_document_url($veryfing_details[0]->uploaded_pdf);
	
	$get_uploaded_doc = get_caf_upload_doc_details($application_id, $service_id, 'CAF', $factory_type_id, $reference_no);
	$uploaded_pdf_link = l('<i class="fa fa-download" aria-hidden="true"></i> View CAF','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $get_uploaded_doc->id).'/'.encryption_decryption_fun('encrypt', 'CAF').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));

	$output .= '<tr><td colspan="3"><b>DOCUMENT DETAILS</b></td></tr>
  					<tr>
						<td colspan="3"> 
							<table cellpadding="0" cellspacing="0" border="0" width="100%" class="table no-margin# remove-odd-even# custom-table-view-dashboard">
								<tr>
									<td width="60%"><b>Common Application Form</b></td>
									<td width="30%" style="cursor:pointer; color:#1ca9d2">'.$uploaded_pdf_link.'</td>
									<td>&nbsp;</td>
								</tr>
								<tr>
									<td width="45%" colspan="3">&nbsp;</td>
								</tr>
								<tr>
									<th width="90%">List of Documents</th>
									<th width="10%">Action</th>
								</tr>'; 
								    /*if($plan_approve_status == 'RSU') { $plan_approve_status = 'ABk';}*/
									
									$checked = get_verified_field_chem($application_id, $reference_no, $plan_approve_status);
									$verify_details      = ($checked['doc_verify'])? $checked['doc_verify'] : ''; 
									$remark_field        = explode(',', trim($checked['doc_verify'],","));

								for($i=0; $i< count($documentList); $i++)
								{
									$identity_flag = $documentList[$i]->identity_flag;
									
									if($documentList[$i]->document_name == 'Authentication Copy of Consent to operate issued by WBPCB for the factories having a hazardous process a defined under section 2(Cb) read with schedule I of factories Act,1948 as amended or a declaration for exempted category industries as notified by the West Bengal Pollution Contril Board') {
										if($veryfing_details[0]->wbpcb_category_name == 4) {
											$upload_doc_type = 'INT';
										} else {
											$upload_doc_type = 'DOC';
										}
									} else {
										$upload_doc_type = 'DOC';
									}
									$caf_upload_doc_prenission = get_caf_upload_doc_all_according_observation($application_id, $service_id, $upload_doc_type, $factory_type_id, $reference_no, $identity_flag);
									//echo '<pre>'; print_r($caf_upload_doc_prenission);die;
									foreach ($caf_upload_doc_prenission as $record) {	
										$fetch_document = fun_fetch_document_listid($record->doc_master_id);
										$document_name = $fetch_document['document_name'];
										
										if($documentList[$i]->document_name == $document_name) {
										$displayLink = l('<i>'.$document_name.'</i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $record->id).'/'.encryption_decryption_fun('encrypt', $upload_doc_type).'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
										
										if (in_array('document_details_'.$i, $remark_field)) { $verify_status ='checked="checked"';}
										else { $verify_status ='';}

										$output.= '<tr>
												   <td width="90%">'.$displayLink.'</td>
												   <td class="center" width="10%"><div class="checkbox checkbox-theme"><input type="checkbox" '.$disable.' id="document_details_'.$i.'"class="inspector_doc_verify_check" '.$document_details_ck.' '.$verify_status.'/><label for="document_details_'.$i.'"></label></div></td>
						</tr>';
										}
									}
								}
								$output.='</table>';
				
				//$output.='<object type="application/pdf" id="doc" data="'.$GLOBALS['base_url'].'/sites/default/files/preview.pdf" width="100%" height="580" border="1px"></object>';
				
				$output.='</td>
						</tr>';
					
			 $output .= '</table>';		
		 return $output;
}

/*function inspector_application_verify_validate($form, &$form_state) {
  	 
  if (isset($form_state['values']['application_note']) && !$form_state['values']['application_note']) {
    form_set_error('application_note', 'Please enter your note!');    
  }

  if (isset($form_state['values']['application_remark']) && !$form_state['values']['application_remark']) {
    form_set_error('application_remark', 'Please select an remarks!');    
  }

  if (isset($form_state['values']['application_reject']) && !$form_state['values']['application_reject']) {
    form_set_error('application_reject', 'Please enter the cause of rejection!');    
  }
}*/

function inspector_chemical_application_verify_submit($form, &$form_state){
	
	  global $user;
	  $uid = $user->uid;
	  $uname = get_name($uid);
	  $user_role = array_keys($user->roles);
	  $urole  = $user_role[1];
	  $current_application_status =   '';
	  $val   					= 	$form_state['values'];
  
	  $service_id 				= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']); 
	  $factorytype_id 			= 	encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
	  $application_id 			= 	encryption_decryption_fun('decrypt',$val['application_id_hidden']);
	  $reference_no				=  	encryption_decryption_fun('decrypt',$val['referance_no_hidden']);
	  $applicant_id				=  	encryption_decryption_fun('decrypt',$val['applicant_id_hidden']);
	  
	  $cafa_remarks_data = get_checking($application_id,$service_id,$factory_type_id,$reference_no);
	  $plan_status = $cafa_remarks_data['plan_status'];
	  
	  //----------------Remarks Table Insert -------------------
	   
		$value_fields = $val['fieldname'];
		$zone_field = explode(',', $value_fields);
			
			if($val['forward_user']=='0')
			{
				drupal_set_message('Please select an action','error');
			}
			elseif(!in_array("factory_location", $zone_field) && ($val['forward_user']=='2'))
			{
				drupal_set_message('Please confirm the zone first','error');
			}
			/*elseif(in_array("factory_location", $zone_field) && ($val['forward_user']=='4'))
			{
				drupal_set_message('Please uncheck the zone!!','error');
			}*/
			elseif($val['forward_user']=='2')
			{
				$current_application_status ='DCCh';
				$type ='n';
				$details = $val['application_note']['value'];

				$cafa_remarks = array(
					'app_id'   			 => $application_id,
					'remark_by_uid' 	 => $uid,
					'remark_by_roleid' 	 => $urole,
					'remark_by_name' 	 => $uname,
					'sending_time' 		 => date('Y-m-d h:i:s'),
					'app_reference_no' 	 => $reference_no,
					'remarks' 	         => $details,
					'remark_type'		 => $type,
					'verify_details'	 => trim($val['fieldname'], ","),
					'doc_verify'	     => trim($val['doc_fieldname'], ","),							
					'plan_status_chem' 	 => $current_application_status,
					'plan_status'	 	 => $plan_status,
					'service_id'		 => $service_id
					);
				db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();
	
				//---------------- CAFA TABLE UPDATE -------------------
					if($current_application_status =='ABk'){
						$approval_status = 	array('plan_approve_status' => $current_application_status,'remark_by_user_id' => $uid,'remark_by_role_id' => $urole,'created_date' 				=> date('Y-m-d H:i:s'));
					} else {
						$approval_status = 	array('plan_approve_status' => $current_application_status,'remark_by_user_id' => $uid,'remark_by_role_id' => $urole);
					}
					$queryapp 		 =	db_update('fa_cafa');
					$queryapp		 ->	fields($approval_status);
					$queryapp		 ->	condition('id',$application_id,'=');
					$queryapp		 ->	condition('service_id',$service_id,'=');
					$queryapp	     ->	condition('factory_typeid',$factorytype_id,'=');
					$queryapp		 ->	condition('reference_number',$reference_no,'=');
					$queryapp		 ->	execute();
		
				//----------- WORKER TABLE UPDATE ---------------------------
			  
					$worker_status 	= 	array('worker_plan_approval_status' => $current_application_status);
					$querywork 		=	db_update('fa_worker_details');
					$querywork		->	fields($worker_status);
					$querywork		->	condition('application_id',$application_id,'=');
					$querywork		->	condition('service_id',$service_id,'=');
					$querywork		->	condition('factory_type',$factorytype_id,'=');
					$querywork		->	condition('application_reference_no',$reference_no,'=');
					$querywork		->	execute();
				
				//----------------DOCUMENTS TABLE UPDATE-------------------
					/*$doc_status 	= 	array('plan_approval_status' => $current_application_status);
					$querydoc 		=	db_update('fa_caf_upload_doc');
					$querydoc		->	fields($doc_status);
					$querydoc		->	condition('app_id',$application_id,'=');
					$querydoc		->	condition('upload_documents_service_id',$service_id,'=');
					$querydoc	    ->	condition('upload_doc_factory_type_id',$factorytype_id,'=');
					$querydoc		->	condition('application_reference_no',$reference_no,'=');
					$querydoc		->	execute();*/
				  
				//----------------OCCUPIER DETAILS TABLE UPDATE-------------------
					$occupr_status 	= 	array('worker_plan_approval_status' => $current_application_status);
					$querydic 		=	db_update('fa_occupier_details');
					$querydic		->	fields($occupr_status);
					$querydic		->	condition('application_occupier_id',$application_id,'=');
					$querydic		->	condition('occupier_service_id',$service_id,'=');
					$querydic		->	condition('factory_type_id',$factorytype_id,'=');
					$querydic		->	condition('application_reference_no',$reference_no,'=');
					$querydic		->	execute();
				
				//---------------- CONDITIONS TABLE INSERT -------------------
			
					$c = 0;
					while(!empty($val['condition_'.$c]))
					{
						$cafa_conditions =  array(
						'app_id'   			=> $application_id,
						'added_by_uid' 	    => $uid,
						'added_by_roleid'   => $urole,
						'added_by_name' 	=> $uname,
						'sending_time' 		=> date('Y-m-d h:i:s'),
						'app_reference_no' 	=> $reference_no,
						'conditions' 	    => $val['condition_'.$c],
						'status' 			=> 'active',
						);	
					db_insert('fa_cafa_conditions')->fields($cafa_conditions)->execute();
					
						$c++;
					}
					
					//---------------- OBSERVATIONS TABLE INSERT -------------------
					
							$d = 0;
							while(!empty($val['pre_observation_'.$d])){
							$checklist_data =	 array(
								'observations_id' 	=> $val['pre_observation_'.$d],
								'remark_by_ad' 		=> $val['pre_observation_comment_'.$d],
								'ad_details'		=> $uid.','.$uname,
								'remark_table_id'	=> '0',
								'app_id'			=> $application_id,
								'factory_type'		=> $factorytype_id,
								'is_chemical'		=> 1,
							);
								//print_r($checklist_data);die;
								$queryabc 		 =	db_insert('fa_checklist_observations_old');
								$queryabc		 ->	fields($checklist_data);
								$queryabc		 ->	execute();
								$d++;
							}
							
							$e = 0;
							while(!empty($val['observation_'.$e])){
								
								$extra_observation = array(
									'ad_extra_observation' => $val['observation_'.$e],
									'remark_by_ad'		 => $val['observation_comment_'.$e],
									'ad_details'		 => $uid.','.$uname,
									'remark_table_id'	 => '0',
									'app_id'			 => $application_id,
									'factory_type'		 => $factorytype_id,
									'is_chemical'		 => 1,
								);
								$id = db_insert('fa_checklist_observations_old')->fields($extra_observation)->execute();
								$e++;
							}
	
					if($current_application_status=='ABk'){
						drupal_goto('http://factories.nic.in/plan-applicant-letter/'.$val['application_id_hidden'].'/'.$val['referance_no_hidden'].'/'.$val['serviceid_hidden'].'/'.$val['factorytype_hidden']);
						//drupal_set_message('Application has been successfully backed to Applicant');
						}
					elseif($current_application_status=='DCCh'){
						drupal_set_message('Application has been successfully forwarded to Deputy Chief Chemical.');}
					else{
						drupal_set_message('Application not send.','error');
						}
	
						if($service_id == '4') { 
							drupal_goto('inspector-chemical-plan-list/');
						} else {
							drupal_goto('inspector-extension-list/');
						}
					//drupal_goto('inspector-chemical-plan-list/');
				}
			elseif($val['forward_user']=='4')
			{
				$current_application_status ='AICh';
				$type ='n';
				$details = $val['application_zone_change_note'];
				
				$cafa_remarks = array(
							'app_id'   			 => $application_id,
							'remark_by_uid' 	 => $uid,
							'remark_by_roleid' 	 => $urole,
							'remark_by_name' 	 => $uname,
							'sending_time' 		 => date('Y-m-d h:i:s'),
							'app_reference_no' 	 => $reference_no,
							'remarks' 	         => $details,
							'remark_type'		 => $type,
							'verify_details'	 => $val['fieldname'],
							'doc_verify'	     => $val['doc_fieldname'],							
							'plan_status_chem' 	 => $current_application_status,
							'plan_status'	 	 => $plan_status,
							'service_id'		 => $service_id
							);
					db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();
						
				$zone_id = $val['application_zone_change'];
				$data =	 array('factory_zone' => $zone_id);	

					$queryabc 		 =	db_update('fa_cafa');
					$queryabc		 ->	fields($data);
					$queryabc		 ->	condition('id',$application_id,'=');
					$queryabc		 ->	condition('service_id',$service_id,'=');
					$queryabc	     ->	condition('factory_typeid',$factorytype_id,'=');
					$queryabc		 ->	condition('reference_number',$reference_no,'=');		
					$queryabc		 ->	execute();
					
					drupal_set_message('Application forwarded to specific zone.');
					if($service_id == '4') { 
						drupal_goto('inspector-chemical-plan-list/');
					} else {
						drupal_goto('inspector-extension-list/');
					}
					//drupal_goto('inspector-chemical-plan-list/');
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

?>