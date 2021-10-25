<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function application_view_register_deputychief($form, &$form_state,$serviceid, $factory_typeid,$applicationid,$referenceid) {
   
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

   	$query_check_applicant = db_select('fa_cafa_remarks','remarks'); 
   	$query_check_applicant->fields('remarks', array());
   	$query_check_applicant->condition('remarks.app_id', $application_id, '=');
   	$query_check_applicant->condition('remarks.app_reference_no', $reference_no, '=');
   	$query_check_applicant->orderBy('remarks.id','DESC');
   	$query_check_applicant->range(0, 1);
   	$result = $query_check_applicant->execute();
   	$content = $result->fetchAssoc();
   			
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
   	
   	$form['applicantion_verify']['view_payment_breakup']	 = array(
   		'#markup' 		=> l(t('View Payment Details'),'applicant/view-payment-breakup/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$referenceid, array('html' => TRUE,'attributes'=> array('class'=>array('btn bg-navy margin')))),
   );	
   	
 $form['applicantion_verify']['Registration_list']	 = array(
		'#markup' 		=> l(t('Back to list'),'deputychief-registration-list/', array('html' => TRUE,'attributes'=> array('class'=>array('btn bg-navy margin')))),
);

$form['applicantion_verify']['document_list_1'] = array(
			'#type' 		=> 'markup',
			'#markup' 		=> display_document($application_id,$service_id,$factory_type_id,$reference_no),
		);
//$serviceid, $factory_typeid,$applicationid,$referenceid
$observation_link	= l('Click here', 'oservation_list_admin/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$referenceid, array('html' => TRUE,'attributes'=>array('title' => 'Click here', 'class'=>array(''), 'target' => '_blank')));

 $form['applicantion_verify']['start_list_1']	 = array(
		'#markup' 		=> '<div class = "row">
								<div class="box box-info">
   									<div class="box-header with-border"><h3 class="box-title">Display all checklisted conditions and comments'.$observation_link.'</h3></div>
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
   		$form['application_forword']['markup']	= array(
   			'#type'		=> 'markup',
     		'#prefix'	=> '<div class="row">
								<div class = "col-md-12 col-xs-12">
   									<div class="box box-info">
   										<div class="box-header with-border"><h3 class="box-title"><b>Send to Concerned authority:</b></h3></div>
   											<div class = "box-body">',
   		);
   	//echo $option ; die('d');
   		$users_action= array(	
   					'0'=>'Select',
					'1'=>'Forword to  Joint Director',
					//'2'=>'Back to Assistant Director',
   		);
   					
   	
   		$form['application_forword']['forword_user'] 	= array(
   			  '#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="select label-block">Necessary action to be taken:<span id=\'star\'>*</span>',
   			  '#suffix' 			=> '</label></div>',
   			  '#type' 				=> 'select',
   			  '#options' 			=> $users_action,
   			  '#default_value' 		=> $value_app,
   			  '#ajax' => array(
   				'event' => 'change',
   				'effect' => 'fade',
   				'callback' => 'get_ajax_note',
   				'progress' => array('type' => 'throbber','message' => t('loading')))
   			);
   			
   		$form['application_forword']['application_remark'] = array(
           	'#prefix' => '<div id="remark_id">',
           	'#suffix' => '</div>',
       	);
   		$form['application_forword']['application_note'] = array(
   			'#prefix' => '<div id="notesheet_id">',
   			'#suffix' => '</div>',
   		);
   		$form['application_forword']['application_reject'] = array(
   			'#prefix' => '<div id="reject_id">',
           	'#suffix' => '</div>',
   		);
   
   		$form['application_forword']['download_licence'] = array(
   	   		'#prefix' => '<div id="download_licence">',
           	'#suffix' => '</div>',
   		);
    	$form['application_forword']['download_registration'] = array(
   	   		'#prefix' => '<div id="download_registration">',
           	'#suffix' => '</div>',
   		);
   
   		$action   = isset($form_state['values']['forword_user']) ? $form_state['values']['forword_user'] : $value_app;
   		if($action == 2){
   		$form['application_forword']['application_remark'] = array(
           	'#prefix' => '<div id="remark_id" class="col-md-8"><label class="input label-block">Notesheet for back to Assistant Director:',
           	'#suffix' => '</label></div>',
           	'#type' => 'textarea',
   			'#default_value'  => !empty($content['remarks']) ? '' : '',
   		);
   		}
  
   		if($action == 1){
   			$form['application_forword']['application_note'] = array(
           		'#prefix' => '<div id="notesheet_id" class="col-md-8"><label class="input label-block">Notesheet to Joint Chief:',
           		'#suffix' => '</label></div>',
           		'#type' => 'textarea',
   				'#default_value'  => !empty($content['remarks']) ? '' : '',
   			);
   		}
  
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
   	ctools_include('ajax');
   	ctools_include('modal');
   	ctools_modal_add_js();
   	$worker_details=$base_root.$base_path.'view-worker-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
   		$link_worker=ctools_modal_text_button(t('View Worker(s)'), $worker_details ,t('View Details)')) ;
		
		$recommanded_worker_link	=	$base_root.$base_path.'view-worker-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
		$recommanded_link_worker	=	ctools_modal_text_button(t('Worker(s)list recommanded by AD'), $recommanded_worker_link ,t('View Details)')) ;
		
   	//$power_details=$base_root.$base_path.'view-power-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
   		//$link_power=ctools_modal_text_button(t('View Power Details'), $power_details ,t('View Details)')) ;
   	$occupier_details=$base_root.$base_path.'view-occuiper-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
   		$link_occuiper=ctools_modal_text_button(t('View Occupier(s)'), $occupier_details ,t('View Details)')) ;	
   	$director_details=$base_root.$base_path.'view-director-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
   		$link_director=ctools_modal_text_button(t('View Director(s)'), $director_details ,t('View Details)')) ;		
   	//$manufacturing_details=$base_root.$base_path.'view-manufacturing-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
   		//$link_manufacturing=ctools_modal_text_button(t('View Manufacturing Process(s)'), $manufacturing_details ,t('View Details)')) ;		
   	$documents_details=$base_root.$base_path.'view-documents-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
   		$link_documents=ctools_modal_text_button(t('View Documents list'), $documents_details ,t('View Details)')) ;	
   	$manager_details=$base_root.$base_path.'view-manager-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
   		$link_manager=ctools_modal_text_button(t('View Manager(s)'), $manager_details ,t('View Details)')) ;	
   	$pre_payment_details=$base_root.$base_path.'view-prepaymnet-history/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
   		$link_pre_payment=ctools_modal_text_button(t('View Previous Payment'), $pre_payment_details ,t('View Details)')) ;
   		
  // 	$tt=$base_root.$base_path.'regsection/deputy-note-list/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/nojs'; 	
  // 	$link_t=ctools_modal_text_button(t('Details Notesheet list View'), $tt ,t('Details Notesheet list View')) ;
  $owner_details=$base_root.$base_path.'view-owner-applicant/nojs/'.$service_id.'/'.$factory_type_id.'/'.$application_id.'/'.$reference_no; 	
  $link_owner =ctools_modal_text_button(t('View owner Details'), $owner_details ,t('View Details')) ;
  
   	$remarks=$base_root.$base_path.'regsection/remarks-list/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/nojs'; 	
   	$remarks_ls=ctools_modal_text_button(t('Details Remarks list View'), $remarks ,t('Details Remarks list View')) ;
	
		if($application_status == 'I'){
		$link_t	= l('View Notesheet', 'regsection/registration-view-notesheet/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'View Notesheet', 'target' => '_BLANK','class'=>array(''))));
	}else{
		$lnk=$base_root.$base_path.'regsection/deputy-note-list/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/nojs';
		$link_t=ctools_modal_text_button(t('Details Notesheet list View'), $lnk ,t('Details Notesheet list View')) ;
	}
	
	
   
   	$approve_dsc_reg_file_id			= 	$get_all_data['approve_dsc_reg_file_id'];
   	$approve_dsc_licence_file_id		= 	$get_all_data['approve_dsc_licence_file_id'];
   	$dsc_licence_register_file			= 	$get_all_data['approve_dsc_reg_licence_file_id'];
	$upload_application_form_id			= 	$get_all_data['uploaded_pdf'];
   	
   	$dsc_reg_file = get_uploaded_document_url($approve_dsc_reg_file_id);
   	$dsc_lic_file = get_uploaded_document_url($approve_dsc_licence_file_id);
   	$dsc_lic_reg_file = get_uploaded_document_url($dsc_licence_register_file);
	$upload_application_form = get_uploaded_document_url($upload_application_form_id);
   	
   	if(!empty($approve_dsc_reg_file_id)){
   	$reg_down	= l('Download Registration Certificate', file_create_url($dsc_reg_file), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('button'))));
   	}
   	if(!empty($approve_dsc_licence_file_id)){
   	$lic_down	= l('Download Licence Certificate',file_create_url($dsc_lic_file), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('button'))));}
   	if(!empty($dsc_licence_register_file)){
   	$lic_register_file	= l('Download Licence Register',file_create_url($dsc_lic_reg_file), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('button'))));}
   	
   	
   		if($get_all_data['factory_owershiptype']=="pv"){
   			$ownership_type = "Pvt Ltd Company";
   		}if($get_all_data['factory_owershiptype']=="ltd"){
   				$ownership_type = "Ltd Company";
   		}if($get_all_data['factory_owershiptype']=="par_firm"){
   				$ownership_type = "Partnership Firm";
   		}if($get_all_data['factory_owershiptype']=="pro_firm"){
   				$ownership_type = "Proprietorship Firm";
   		}if($get_all_data['factory_owershiptype']=="govt"){
   				$ownership_type = "Govt";
   		}if($get_all_data['factory_owershiptype']=="psu"){
   				$ownership_type = "PSU";
   		}if($get_all_data['factory_owershiptype']=="llp"){
   				$ownership_type = "Limited Liability Partnership";
   		}if($get_all_data['factory_owershiptype']=="cooperative"){
   				$ownership_type = "Co-operative";
   		}if($get_all_data['factory_owershiptype']=="registered"){
   				$ownership_type = "Registered Society under Society Register";
   		}if($get_all_data['factory_owershiptype']=="localbody"){
   				$ownership_type = "Local Body";
   		}if($get_all_data['factory_owershiptype']=="others"){
   				$ownership_type = "Others";
   		}
		
   		$is_backlog = $get_all_data['is_backlog'];
   		if($is_backlog == 1){
   			$plan_approval_no = $get_all_data['backlog_plan_approval_no'];
   			$plan_approval_date =date('dS M Y', strtotime($get_all_data['backlog_plan_approval_date']));
   		}else{
   			$plan_approval_no = $get_all_data['factory_plan_approval_number'];
   			$plan_approval_date = date('dS M Y', strtotime($get_all_data['plan_approval_date']));
   		}
   		$factory_zone_date = get_factory_zone_name($get_all_data['factory_zone']);
   		$getdata_factory_location	 =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
   		$factory_address_location 	 = $get_all_data['addrline'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_factory_location);
   		$getdata_headoffice_address  =  array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
   		$headoffice_address 		 = $get_all_data['addrline_off'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_headoffice_address);
		$passport_details = !empty($get_all_data['occupier_passport_premises'])?'Passport No-'.$get_all_data['occupier_passport_premises'].',<br/>Passport Issue Date-'.$get_all_data['date_of_issue_premises'].',<br/>Passport Expiry date-'.$get_all_data['date_of_expiry_premises']:'';
   		
		$owner_address_details = !empty($get_all_data['addrline_premises'])?$get_all_data['addrline_premises'].',':'';
		$owner_address_details.= $get_all_data['owner_country_address'].',<br/>'.country_name($get_all_data['country_premises']);
		$getdata_owner_address 		=  array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
		
		$owner_address 				=	$owner_address_details.'<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_owner_address);
		
		$getdata_communication_address = array('district_comm','subdivision_comm','areatype_comm','block_comm','panchayat_comm','policestation_comm','pincodecomm','state_comm','postoffice_comm');
		$communication_address 		= $get_all_data['addrline_comm'].',
		<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_communication_address);
		
		if($get_all_data['wbpcb_category_name']== 4){
			$consent ='White'; 
			$wbpcb_reference_no = 'NA'; 
			$wbpcb_ref_date = 'NA';
			$file = $get_all_data['wbpcb_intimation_letter'];
			$file_url	= l('View', 'document-list/view-appliction-form/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.encryption_decryption_fun('encrypt','CAT'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
			}
		elseif($get_all_data['wbpcb_category_name']==5){
			$consent ='Exempted'; 
			$wbpcb_reference_no = 'NA';
			$wbpcb_ref_date = 'NA';
		}
		else{
			$consent= $get_all_data['wbpcb_category_name'];
			$file_url	= 'Not Applicable for above mention category';
			$wbpcb_reference_no = !empty($wbpcb_reference_no)?$wbpcb_reference_no:'Nil';
			$wbpcb_ref_date = !empty($wbpcb_ref_date)?date('dS M Y', strtotime($wbpcb_ref_date)):'Nil';
		}
   			$previous_details 			=  get_previous_details_view($application_id,$reference_no,$factory_type_id,$service_id);
   				foreach($previous_details as $pre_row){
   					$is_previous		 	= $pre_row->is_previous;
   					if($is_previous == "Yes"){
   						$view = "";
   					}if($is_previous == "No"){
   						$view = "";
   					}
   				}
   
   		
   			$pdfs_files = get_application_form_pdf($application_id,$reference_no,$factory_type_id,$service_id);
   			$fetch_year	= fetch_year($application_id,$service_id,$factory_type_id,$reference_no);
   			$pre_view	= get_previous_details_view($application_id,$reference_no,$factory_type_id,$service_id);
   	
   			$query_check_applicant = db_select('fa_cafa_remarks','remarks');
   			$query_check_applicant->leftJoin('fa_cafa','ca', 'ca.remark_by_user_id = remarks.remark_by_uid');  
   			$query_check_applicant->fields('remarks', array());
   			$query_check_applicant->condition('remarks.app_id', $application_id, '=');
   			$query_check_applicant->condition('remarks.app_reference_no', $reference_no, '=');
   			$query_check_applicant->orderBy('remarks.id','DESC');
   			$query_check_applicant->range(0, 1);
   			$result = $query_check_applicant->execute();
   			$data = $result->fetchAssoc();
   			
   			$remark_field = explode(',', $data['verify_details']);
   	
   			foreach ($remark_field as $fieldname){ 
   			//echo $fieldname;
   				if($fieldname == 'factory_name'){ $factory_name_ck = "checked='checked'";}
   				if($fieldname == 'ownership_type'){ $ownership_type_ck = "checked='checked'";}
   				if($fieldname == 'factory_pan'){ $factory_pan_ck = "checked='checked'";}
				if($fieldname == 'gstin_no'){ $gstin_no_ck = "checked='checked'";}
				if($fieldname == 'udyog_aadhaar'){ $udyog_aadhaar_ck = "checked='checked'";}
				if($fieldname == 'enargy_no'){ $enargy_no_ck = "checked='checked'";}
				if($fieldname == 'cin_no'){ $cin_no_ck = "checked='checked'";}
				if($fieldname == 'trade_no'){ $trade_no_ck = "checked='checked'";}
   				
   				if($fieldname == 'plan_approval_no'){ $plan_approval_ck = "checked='checked'";}
   				if($fieldname == 'plan_approval_date'){ $plan_approval_date_ck = "checked='checked'";}
   				
   				if($fieldname == 'zone_name'){ $zone_name_ck = "checked='checked'";}
   				
   				if($fieldname == 'factory_headoffice'){ $factory_headoffice_ck = "checked='checked'";}
				if($fieldname == 'factory_communication'){ $factory_communication_ck = "checked='checked'";}
   				
   				if($fieldname == 'telephone_no'){ $telephone_no_ck = "checked='checked'";}
   				if($fieldname == 'mobile_no'){ $mobile_no_ck 	= "checked='checked'";}
   				if($fieldname == 'fax_no'){ $fax_no_ck 	= "checked='checked'";}
   				if($fieldname == 'email_no'){ $email_no_ck 	= "checked='checked'";}
   				
   				if($fieldname == 'owner_name'){ $owner_name_ck = "checked='checked'";}
   				if($fieldname == 'premises_address'){ $premises_address_ck = "checked='checked'";}
   				
   				if($fieldname == 'wbpcb_id'){ $wbpcb_id_ck = "checked='checked'";}
   				if($fieldname == 'wbpcb_reference_id'){ $wbpcb_reference_id_ck = "checked='checked'";}
   				if($fieldname == 'wbpcb_reference_date'){ $wbpcb_reference_date_ck = "checked='checked'";}
   				if($fieldname == 'intimation_id'){ $intimation_id_ck = "checked='checked'";}
   				
   				if($fieldname == 'date_of_amenability_id'){ $date_of_amenability_id_ck = "checked='checked'";}
   				if($fieldname == 'period_for_application_id'){ $period_for_application_id_ck = "checked='checked'";}
   				if($fieldname == 'previous_name_id'){ $previous_name_id_ck = "checked='checked'";}
   				
   				if($fieldname == 'worker_details'){ $worker_details_ck = "checked='checked'";}
   				if($fieldname == 'power_details'){ $power_details_ck = "checked='checked'";}
   				if($fieldname == 'manager_details'){ $manager_details_ck = "checked='checked'";}
   				if($fieldname == 'occupier_details'){ $occupier_details_ck = "checked='checked'";}
   				if($fieldname == 'director_details'){ $director_details_ck = "checked='checked'";}
   				if($fieldname == 'nature_details'){ $nature_details_ck = "checked='checked'";}
   				if($fieldname == 'document_details'){ $document_details_ck = "checked='checked'";}
   				
   				if($fieldname == 'previous_payment_id'){ $previous_payment_ck = "checked='checked'";}
   				if($fieldname == 'payment_amount_id'){ $payment_amount_ck = "checked='checked'";}
   				if($fieldname == 'payment_date_id'){ $payment_date_ck = "checked='checked'";}
   				if($fieldname == 'applications_forms_id'){ $applications_forms_ck = "checked='checked'";}
   			}
   			if(!empty($get_all_data['enargy_no'])){ $meter = $get_all_data['enargy_no'];}else{$meter = 'NA';}
			if(!empty($get_all_data['cin_no'])){ $cin = $get_all_data['cin_no'].'   <a href="http://www.mca.gov.in/mcafoportal/findCIN.do" target="_blank" title="Ministry Of Corporate Affairs, About MCA, Ministry">(Verify CIN No.)</a>';}else{$cin = 'NA';}
			if(!empty($get_all_data['factory_previous_name'])){ $previous_name = $get_all_data['factory_previous_name'];}else{$previous_name = 'NA';}
			if(!empty($get_all_data['enargy_no'])){ $meter = $get_all_data['enargy_no'];}else{$meter = 'NA';}
			if(!empty($get_all_data['trade_license_no'])){ $trade_no = $get_all_data['trade_license_no'];}else{$trade_no = 'NA';}
	$power_generating_station 	= get_power_generating_station($application_id,$reference_no,$factory_type_id,$service_id);
	// print_r($power_generating_station);die;
		foreach($power_generating_station as $power){
			if(!empty($power->recommanded_installed_power) || ($power->recommanded_installed_power!=NULL) || ($power->recommanded_installed_power!=0)){
				$link_power = $power->installed_power.'('.$power->power_unit.').<br/><font color="red">Recommanded install power '.$power->recommanded_installed_power.'('.$power->recommanded_power_unit.')by AD</font>';
				
			}else{
				$link_power = $power->installed_power.'('.$power->power_unit.')';
			}
			
		}
		
		$nature_details = get_manufacturing($application_id,$service_id,$factory_type_id,$reference_no);
		
		foreach($nature_details as $nature){
			$nature_work = $nature->nature_manufacturing;
		}	
			
   						
   		$output = '<div class="row">
   					<div class="box box-info">
   						<div class="box-header with-border">
                 				<h3 class="box-title">Application for Registration and Grant of Licence<br/>All inputs are provided by applicant only<br/>All inputs are to be verified by officials</h3><br>'.$lic_down.'&nbsp;&nbsp;&nbsp;&nbsp;'.$reg_down.'&nbsp;&nbsp;&nbsp;&nbsp;'.$lic_register_file.' &nbsp;&nbsp;&nbsp;&nbsp;'.$link_t.'&nbsp;&nbsp;&nbsp;&nbsp;'.$remarks_ls.'
   						</div>
   					<div class = "box-body">
   					<table cellpadding="0" cellspacing="0" border="0" width="100%" class="table table-bordered custom-table-view"><tr>
   						<th width="30%">Parameters</th>
   						<th>Inputs</th>
   						<th width="8%" class="center">Check <input type="checkbox" id="select_all"/></th>
   					</tr>';
   		$output .= '<tr><td colspan="3">A.Factory Information</td></tr>
   					<tr>
   						<td>(i).Name of the factory</td>
   						<td>'.$get_all_data['factory_name'].'</td>
   						<td class="center"><input type="checkbox" id="factory_name" class="deputychief_verify_check" '.$factory_name_ck .' /></td>
   					</tr>
   					<tr>
   						<td>(ii).Ownership Type</td>
   						<td>'.$ownership_type.'</td>
   						<td class="center"><input type="checkbox" id="ownership_type" class="deputychief_verify_check" '.$ownership_type_ck.'/></td>
   					</tr>
   					<tr>
   						<td>(iii).PAN of the Business Establishment / Factory / Company </td>
   						<td>'.$get_all_data['factory_pan'].'</td>
   						<td class="center"><input type="checkbox" id="factory_pan" class="deputychief_verify_check" '.$factory_pan_ck.'/></td>
   					</tr>
					<tr>
						<td>GSTIN No</td>
						<td>'.$get_all_data['gstin_no'].'</td>
						<td class="center"><input type="checkbox" id="gstin_no" class="deputychief_verify_check" '.$gstin_no_ck.'/></td>
					</tr>
					<tr>
						<td>Udyog Adhaar No</td>
						<td>'.$get_all_data['udyog_aadhaar'].'</td>
						<td class="center"><input type="checkbox" id="udyog_aadhaar" class="deputychief_verify_check" '.$udyog_aadhaar_ck.'/></td>
					</tr>
					<tr>
						<td>Enargy Meter No</td>
						<td>'.$meter.'</td>
						<td class="center"><input type="checkbox" id="enargy_no" class="deputychief_verify_check" '.$enargy_no_ck.'/></td>
					</tr>
					<tr>
						<td>CIN No</td>
						<td>'.$cin.'</td>
						<td class="center"><input type="checkbox" id="cin_no" class="deputychief_verify_check" '.$cin_no_ck.'/></td>
					</tr>
					<tr>
						<td>Trade License No</td>
						<td>'.$trade_no.'</td>
						<td class="center"><input type="checkbox" id="trade_no" class="deputychief_verify_check" '.$trade_no_ck.'/></td>
					</tr>';
   					if($factory_type_id ==1 || $factory_type_id == 2){
						$output.='<tr><td>(ix) Plan Approval number</td>
						<td>'.$plan_approval_no.'</td>
						<td class="center"><input type="checkbox" id="plan_approval_no" class="inspector_verify_check"'.$plan_approval_ck.' /></td>
					</tr>
					<tr>
						<td>(x) Plan Approval Date</td>
						<td>'.$plan_approval_date.'</td>
						<td class="center"><input type="checkbox" id="plan_approval_date" class="inspector_verify_check" '.$plan_approval_date_ck.'/></td>
					</tr>';
					}if($factory_type_id ==3){
						$output.='<tr><td>(ix) Plan Approval number</td>
						<td>NA</td>
						<td class="center"></td>
					</tr>
					<tr>
						<td>(x) Plan Approval Date</td>
						<td>NA</td>
						<td class="center"></td>
					</tr>';
					}
   				$output .= '<tr><td colspan="3">B.Location of Factory </td></tr>
   					<tr>
   						<td>(i).Zone</td>
   						<td>'.$factory_zone_date['zone_name'].'</td>
   						<td rowspan="2" class="center"><input type="checkbox" id="zone_name" class="deputychief_verify_check" '.$zone_name_ck.' disabled/></td>
   						</tr>
					<tr>
						<td>(ii) Nearest Landmark</td>
						<td colspan="2">'.$get_all_data['factory_location'].'</td>
					</tr>
   					<tr>
   						<td>(iii).Address</td>
   						<td>'.$factory_address_location.'<br/>JL No: '.$get_all_data['jl_no'].'<br/>Mouza Name: '.$get_all_data['mouza_name'].'</td>
					</tr>
					<tr>
   						<td>(iv).Telephone No</td>
   						<td>'.$get_all_data['comm_telephone'].'</td>
   						<td class="center"><input type="checkbox" id="telephone_no" class="deputychief_verify_check" '.$telephone_no_ck.' /></td>
   					</tr>
   					<tr>
   						<td>(v).Mobile No</td>
   						<td>'.$get_all_data['comm_mobile'].'</td>
   						<td class="center"><input type="checkbox" id="mobile_no" class="deputychief_verify_check" '.$mobile_no_ck.'/></td>
   					</tr>
   					<tr>
   						<td>(vi).Fax No</td>
   						<td>'.$get_all_data['comm_fax'].'</td>
   						<td class="center"> <input type="checkbox" id="fax_no" class="deputychief_verify_check" '.$fax_no_ck.'/></td>
   					</tr>
   					<tr>
   						<td>(vii).Email Id</td>
   						<td>'.$get_all_data['comm_email'].'</td>
   						<td class="center"><input type="checkbox" id="email_no" class="deputychief_verify_check" '.$email_no_ck.'/></td>
   					</tr>
   					<tr>
   						<td colspan="3">C.Address of the Registered office / Head office</td>
   					</tr>
   					<tr>
   						<td>(i).Address</td>
   						<td>'.$headoffice_address.'</td>
   						<td class="center"><input type="checkbox" id="factory_headoffice" class="deputychief_verify_check" '.$factory_headoffice_ck.'/></td>
   					</tr>
   					<tr>
   						<td>(ii).Telephone No</td>
   						<td>'.$get_all_data['comm_telephone'].'</td>
   						<td class="center"><input type="checkbox" id="telephone_no" class="deputychief_verify_check" '.$telephone_no_ck.' /></td>
   					</tr>
   					<tr>
   						<td>(iii).Mobile No</td>
   						<td>'.$get_all_data['comm_mobile'].'</td>
   						<td class="center"><input type="checkbox" id="mobile_no" class="deputychief_verify_check" '.$mobile_no_ck.'/></td>
   					</tr>
   					<tr>
   						<td>(iv).Fax No</td>
   						<td>'.$get_all_data['comm_fax'].'</td>
   						<td class="center"> <input type="checkbox" id="fax_no" class="deputychief_verify_check" '.$fax_no_ck.'/></td>
   					</tr>
   					<tr>
   						<td>(iv).Email Id</td>
   						<td>'.$get_all_data['comm_email'].'</td>
   						<td class="center"><input type="checkbox" id="email_no" class="deputychief_verify_check" '.$email_no_ck.'/></td>
   					</tr>
					<tr>
						<td colspan="3">D. Address to which communications relating to the factory may be sent<br/><font color="#FF0000">(N.B:- This address will be treated as communication address as per Section 7 of Factories Act, 1948)</font> </td></tr>
					</tr>
					<tr>
						<td>(i) Communication address </td>
						<td>'.$communication_address.'</td>
						<td class="center"><input type="checkbox" id="factory_communication" class="deputychief_verify_check" '.$factory_communication_ck.'/></td>
					</tr> 
   					<tr>
   						<td colspan="3">E.Details of owner of the premises occupied as a factory</td>
   					</tr>
   					<tr>
					   <td>(i).Name of the owner</td>
					   <td>'.$link_owner.'</td>
					   <td class="center"><input type="checkbox" id="owner_name" class="deputychief_verify_check" '.$owner_name_ck.'/></td>
   					</tr>
   					
   					<tr>
   						<td colspan="3">F.Factory Identification according to WBPCB</td>
   					</tr>
   					<tr>
   						<td>(i).Category</td>
   						<td>'.$consent.'</td>
   						<td class="center"><input type="checkbox" id="wbpcb_id" class="deputychief_verify_check" '.$wbpcb_id_ck.'/></td>
   					</tr>
   					<tr>
   						<td>(ii).Reference number</td>
   						<td>'.$wbpcb_reference_no.'</td>
   						<td class="center"><input type="checkbox" id="wbpcb_reference_id" class="deputychief_verify_check" '.$wbpcb_reference_id_ck.'/></td>
   					</tr>
   					<tr>
   						<td>(iii).Reference Date</td>
   						<td>'.$wbpcb_ref_date.'</td>
   						<td class="center"><input type="checkbox" id="wbpcb_reference_date" class="deputychief_verify_check" '.$wbpcb_reference_date_ck.'/></td>
   					</tr>
   					<tr>
   						<td>(iv).Intimation Letter</td>
   						<td>'.$file_url.'</td>
   						<td class="center"><input type="checkbox" id="intimation_id" class="deputychief_verify_check" '.$intimation_id_ck.'/></td>
   					</tr>
   					<tr><td colspan="3">G.State the period of licence</td></tr>
   					<tr>
   						<td>(i).Date from which the premises is occupied or been taken into use as factory </td>
   						<td>'.date('dS M Y', strtotime($get_all_data['date_of_amenability'])).'</td>
   						<td class="center"><input type="checkbox" id="date_of_amenability_id" class="deputychief_verify_check" '.$date_of_amenability_id_ck.' disabled/></td>
   					<tr>
   						<td>(ii).State the period of license required </td>
   						<td>'.$get_all_data['period_for_application'].'year(s)</td>
   						<td class="center"><input type="checkbox" id="period_for_application_id" class="deputychief_verify_check" '.$period_for_application_id_ck.'/></td>
   					</tr>
   					<tr>
   						<td>(iii).Whethere any changes name and ownership details of factory </td>
   						<td>'.$is_previous.$view.'</td>
   						<td class="center"><input type="checkbox" id="previous_name_id" class="deputychief_verify_check" '.$previous_name_id_ck.'/></td>
   					</tr>
   					<tr>
   						<td colspan="3">H.Worker Details</td></tr>
   					<tr>
   						<td>(i).Maximum number of workers employed or to be employed in tha factory</td>
   						<td>'.$link_worker.'</td>
   						<td class="center"><input type="checkbox" id="worker_details" class="deputychief_verify_check" '.$worker_details_ck.'/>
   					</tr>
   					<tr>
   						<td colspan="3">I.Power Details</td>
   					</tr>
   					<tr>
   						<td>(i).Installed Power or to be installed power </td>
   						<td>'.$link_power.'</td>
   						<td class="center"><input type="checkbox" id="power_details" class="deputychief_verify_check" '.$power_details_ck.'/></td>
   					</tr>
   					<tr>
   						<td colspan="3">J.Manager Details</td>
   					</tr>
   					<tr>
   						<td>(i).Manager Details</td>
   						<td>'.$link_manager.'</td>
   						<td class="center"><input type="checkbox" id="manager_details" class="deputychief_verify_check" '.$manager_details_ck.'/></td>
   					</tr>
   					<tr>
   						<td colspan="3">K.Occupier Details</td>
   					</tr>
   					<tr>
   						<td>(i).View occupier details</td>
   						<td>'.$link_occuiper.'</td>
   						<td class="center"><input type="checkbox" id="occupier_details" class="deputychief_verify_check" '.$occupier_details_ck.'/></td>
   					</tr>
   					<tr>
   						<td colspan="3">L.Director Details</td>
   					</tr>
   					<tr>
   						<td>(i).View director details</td>
   						<td>'.$link_director.'</td>
   						<td class="center"><input type="checkbox" id="director_details" class="deputychief_verify_check"'.$director_details_ck.'/></td>
   				   </tr>
   				  <tr>
   						<td colspan="3">M.Manufacturing process</td>
   				</tr>
   				<tr>
   					<td>(i).Carried/to be carried on the factory</td>
   					<td>'.$nature_work.'</td>
   					<td class="center"><input type="checkbox" id="nature_details" class="deputychief_verify_check" '.$nature_details_ck.'/></td>
   				</tr>
   				<tr>
   					<td colspan="3">N.Uploaded Documents</td>
   				</tr>
   				<tr>
   					<td>(i).View uploaded documetns</td>
   					<td>'.$link_documents.'</td>
   					<td class="center"><input type="checkbox" id="document_details" class="deputychief_verify_check" '.$document_details_ck.' /></td>
   				</tr>
   				<tr>
   					<td colspan="3">O.Payment History</td>
   				</tr>
   				<tr>
   					<td>(i).Previous Payment</td>
   					<td>'.$link_pre_payment.'</td>
   					<td class="center"><input type="checkbox" id="previous_payment_id" class="deputychief_verify_check" '.$previous_payment_ck.' /></td>
   				</tr>
   				<tr>
   					<td>(ii).Paid fees</td>
   					<td>'.$get_all_data['payment_amount'].'</td>
   					<td class="center"><input type="checkbox" id="payment_amount_id" class="deputychief_verify_check" '.$payment_amount_ck.' /></td>
   				</tr>
   				<tr>
   					<td>(ii).Payment date</td>
   					<td>'.date('dS M Y', strtotime($get_all_data['payment_date'])).'</td>
   					<td class="center"><input type="checkbox" id="payment_date_id" class="deputychief_verify_check" '.$payment_date_ck.' /></td>
   				</tr>
   				<tr><td>P. Application Forms</td>';
				   if($get_all_data['tm_migrated_flag']=='N'){
					$application_from	= l('Common application form', 'document-list/view-appliction-form/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.encryption_decryption_fun('encrypt','CAF'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				}
				$output .= '<td><b>'.$application_from.'</b></td>
				<td class="center"><input type="checkbox" id="applications_forms_id" class="deputychief_verify_check" '.$applications_forms_ck.'/></td>
				</tr></table>';
   				
   				
//   		$output.='<table class="table table-bordered custom-table-view">
//   			<tr>
//   				<td colspan="6">P.Whethere any changes name and ownership details of factory</td>
//   			</tr>
//   			<tr>
//   				<td><b>SL No.</b></td>
//   				<td><b>Application Period</b></td>
//   				<td><b>Change Date</b></td>
//   				<td><b>Name</b></td>
//   				<td><b>Ownership</b></td>
//   				<td><input type="checkbox" id="applications_changes_name_id" class="deputychief_verify_check" '.$applications_changes_name_ck.'/></td>
//   			</tr>';
//   			
//   		foreach($pre_view as $view){
//   		$sl= $sl+1;	
//   		if($view->ownership_type=="pv"){
//   			$ownership_type = "Pvt Ltd Company";
//   		}if($view->ownership_type=="ltd"){
//   			$ownership_type = "Ltd Company";
//   		}if($view->ownership_type=="par_firm"){
//   			$ownership_type = "Partnership Firm";
//   		}if($view->ownership_type=="pro_firm"){
//   			$ownership_type = "Proprietorship Firm";
//   		}if($view->ownership_type=="govt"){
//   			$ownership_type = "Govt";
//   		}if($view->ownership_type=="psu"){
//   			$ownership_type = "PSU";
//   		}if($view->ownership_type=="others"){
//   			$ownership_type = "Others";
//   		}
//   		$change_date =  date('dS M Y', strtotime($view->change_date));
//   		
//   		$output.='<tr>
//   					<td>'.$sl.'</td>
//   					<td>'.$view->service_year.'</td>
//   					<td>'.$change_date.'</td>
//   					<td>'.$view->pervious_factory_name.'</td>
//   					<td>'.$ownership_type.'</td>
//   					<td>&nbsp;</td>
//   				</tr>';
//   		}
//   		
//   		$output.='</table>';
		
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
								
   								
   									
   							  //---------------- CAFA TABLE UPDATE -------------------
   								$data =	 array('application_status' => $status,'modification_date'=>date('Y-m-d'));		
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
  
   
function get_conditions_details($id){
	$conditions_details	=  db_query("SELECT observations  FROM {fa_observations_mst} WHERE id = '".$id."'")->fetchObject()->observations;
	return $conditions_details;
	}

function display_document($application_id,$service_id,$factory_type_id,$reference_no){
	$documents_type = NULL;
	$resultData = get_caf_upload_doc_all($application_id,$service_id,$documents_type,$factory_type_id,$reference_no,$id);
	$output.='<div class="row"><div class="box box-info">
				<div class="box-header with-border"><h3 class="box-title">Q. Uploaded Documents View</h3></div>
				<div class="box-body">
						<div class="col-md-3">
						 <h4 class="label-warning center">Document List</h4>';
						 $i=1;
						foreach($resultData as $documents){
							if($documents->upload_doc_type =='DOC' || $documents->upload_doc_type =='INT'){
								$displayLink = file_create_url('document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $documents->id).'/'.encryption_decryption_fun('encrypt', $documents_type));
								$output.='<li class="btn btn-warning" style="white-space: initial; margin: 7px;"><span class="link"  onclick="seeDoc(this);"  data-id="'.$displayLink.'"  data-myval='.$displayLink.'>'.file_head_name($documents->doc_master_id).'</span></li>';
							}
						}
			$output.='</div>
						<div class="col-md-9">
							<h4 class="label-warning center">Preview</h4>
							
							<object type="application/pdf" id="doc" data="'.$GLOBALS['base_url'].'/sites/default/files/preview.pdf" width="100%" height="580" border="1px"></object>
							
					</div></div></div></div>';
					return $output;
				}
?>