<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
function renewal_send_concern_inspector($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$referenceno)
{ 
    global $base_root, $base_path, $user;
	$form            	= array();
	
	$userid = $user->uid;
	$rid= get_role_id($userid);
	   
    $service_id      	= encryption_decryption_fun('decrypt', $serviceid);
    $factory_type_id 	= encryption_decryption_fun('decrypt', $factory_typeid);
    $application_id  	= encryption_decryption_fun('decrypt', $applicationid);
	$reference_no  		= encryption_decryption_fun('decrypt', $referenceno);

    $get_fa_cafa 				= get_fa_cafa($application_id);
   //$reference_no 				= $get_fa_cafa['reference_number'];
	$date_of_amenability 		= $get_fa_cafa['date_of_amenability'];
	$period_for_application 	= $get_fa_cafa['period_for_application'];
	$previous_excess_paid		= $get_fa_cafa['previous_excess_paid'];
	$is_calculate				= $get_fa_cafa['is_calculate'];
	$service_fees				= $get_fa_cafa['service_fees'];
	$previous_payment_amount	= $get_fa_cafa['payment_amount'];
	$application_status			= $get_fa_cafa['application_status'];
	$total_payment				= $previous_payment_amount+$previous_excess_paid;
	$factory_name				= $get_fa_cafa['factory_name'];
	
	$form['applicationid_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $applicationid
    );
	$form['serviceid_hidden']     = array(
        '#type' => 'hidden',
        '#default_value' => $serviceid
    );
    $form['factorytypeid_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $factory_typeid
    );
	$form['referenceno_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => $referenceno
	);
	
	ctools_include('ajax');
	ctools_include('modal');
	ctools_modal_add_js();


	
	if($application_status == 'I'){
		$view_notesheet_pdf = l('View Recomended Notesheet', 'regsection/registration-view-notesheet/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'View Notesheet', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));
		//$view_notesheet = l('View Notesheet', 'regsection/registration-view-notesheet/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'View Notesheet', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));
	}else{
		//$lnk=$base_root.$base_path.'regsection/deputy-note-list/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/nojs';
		//$view_notesheet = ctools_modal_text_button(t('Details Notesheet list View'), $lnk ,t('Details Notesheet list View')) ;

		//$view_notesheet_pdf = l('View Recomended Notesheet', 'regsection/registration-view-notesheet/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'View Notesheet', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));
		$not_notesheet_pdf = l('Not Recomended Notesheet', 'regsection/registration-not-view-notesheet/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'View Notesheet', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));
	}
	
	$form['header']            = array(
        '#markup' => t('<div class="content"><h3>Application for Renewal of Licence.All inputs are provided by applicant only.
						All inputs are to be verified by officials</h3>')
    );
	$form['other_comment_concern'] = array(
		'#type' 		=> 'fieldset',
		'#title' 		=> t('Send to Concerned authority'),
		'#collapsible' 	=> TRUE, // Added
		'#collapsed' 	=> FALSE,  // Added
	);
	$form['other_comment_concern']['form_start'] = array(
			'#prefix' 	=> '<div class = "row">',
	);
	$status = !empty($application_status ) ? $application_status  : '';
	$users_action= array(	
				'0'=>'Select',
				'1'=>'Forword to Deputy Chief',
	);
	if(($rid== 9 && $application_status == 'U') || ($rid==10 && $application_status == 'DC') || ($rid==11 && $application_status == 'JC') ){

	$identity_flag = 'Comments';
	$irregularities_other_comments =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factory_type_id,$service_id);
	if(!empty($irregularities_other_comments)){
		foreach($irregularities_other_comments as $row_irregularities_other_comments){
			$form['other_comment_concern']['comments_irregularities_other_'.$row_irregularities_other_comments->id] = array(
			'#prefix' 			=> '<div class="col-md-12 col-xs-12"><div id="comments_irregularities_other_'.$row_irregularities_other_comments->id.'">',
			'#suffix' 			=> '</div></div>',
			'#type' 			=> 'textarea',
			'#rows'				=> 2,
			'#attributes' 		=> array('class' => array( 'form-control'),),
			'#default_value' 	=>$row_irregularities_other_comments->irregularities,
			);
		}
	}else{
		$form['other_comment_concern']['comments_irregularities_other'] = array(
				'#prefix' 			=> '<div class="col-md-12 col-xs-12"><div id="comments_irregularities_other">',
				'#suffix' 			=> '</div></div>',
				'#type' 			=> 'textarea',
				'#rows'				=> 2,
				'#attributes' 		=> array('class' => array( 'form-control'),'placeholder'=>''),
				'#default_value' 	=>'',
			);
	}
	

	$form['other_comment_concern']['forword_user'] 	= array(
				'#prefix' 			=> '<div class="col-md-4 col-xs-12"><label class="select label-block">Necessary action to be taken:<span id=\'star\'>*</span>',
				'#suffix' 			=> '</label></div>',
				'#type' 			=> 'select',
				'#options' 			=> $users_action,
				'#default_value' 	=> $value_app,
				'#ajax' 			=> array(
					'event' 			=> 'change',
					'effect' 			=> 'fade',
					'callback' 			=> 'get_ajax_note',
					'progress' 			=> array('type' => 'throbber','message' => t('loading')))
	);
			
	$action   = isset($form_state['values']['forword_user']) ? $form_state['values']['forword_user'] : $value_app;		
			
	$form['other_comment_concern']['application_zone_change'] = array(
		'#prefix' 				=> '<div id="zone_change_id">',
		'#suffix' 				=> '</div>',
	);
	$form['other_comment_concern']['application_zone_change_note'] = array(
		'#prefix' 				=> '<div id="zone_remark">',
		'#suffix' 				=> '</div>',
	);
	$form['other_comment_concern']['application_repay'] = array(
		'#prefix' 				=> '<div id="repay_id">',
		'#suffix' 				=> '</div>',
	);
	
	$form['other_comment_concern']['application_remark'] = array(
		'#prefix' 				=> '<div id="remark_id">',
		'#suffix' 				=> '</div>',
	);
	
	// $form['other_comment_concern']['application_recomended'] = array(
	// 	'#prefix' 				=> '<div id="recomended">',
	// 	'#suffix' 				=> '</div>',
	// );
	
	$form['other_comment_concern']['application_not_recomended'] = array(
		'#prefix' 				=> '<div id="not_recomended">',
		'#suffix' 				=> '</div>',
	);
		
	if($action == 2){
		$factoryzone = get_factory_zone();
		$default_zone 	= array(""=>"- Select Zone -");
		foreach($factoryzone as $val){
			$factzonefinal[$val->zone_id] = $val->zone_name;
			$factzonefinal1 = ($default_zone+$factzonefinal);
		}
		$form['other_comment_concern']['application_zone_change'] = array(
		'#prefix' => '<div id="zone_change_id" class="col-md-4 col-xs-8"><label class="select label-block">Select Specific zone for this application',
		'#suffix' => '</label></div>',
		//'#title' => t('Zone'),
		'#type' => 'select',
		'#options' => $factzonefinal1,
		'#default_value' => $factory_zone,
		);
		$form['other_comment_concern']['application_remark'] = array(
			'#prefix' => '<div id="remark_id"><label class="input label-block">',
			'#suffix' => '</label></div>',
			'#title' => t('Notesheet to AD of respective zone :'),
			'#type' => 'textarea',
			'#required' 		=> TRUE,
			'#default_value'  => !empty($content['remarks']) ? '' : '',
			);
		}
		$remark_type='Agree';
		$value = fun_fetch_irregularities_check($application_id,$reference_no,$factory_type_id,$service_id,$remark_type,$rid);
		if($action == 1){

			
			if(!empty($value)) {
				$form['other_comment_concern']['application_not_recomended']	= array(
					'#prefix' 	=> '<div class="col-md-2"><div id="not_recomended"><label class="input label-block">'.$not_notesheet_pdf,
					'#suffix' 	=> '</label></div></div>',
				);
			}
	
		}
	
		$form['other_comment_concern']['submit'] = array(
			'#prefix' 			=> '<div class="col-md-12 col-xs-12">',
			'#suffix' 			=> '</div>',
			'#attributes' 		=> array('class' => array('btn btn-dark margin#'), 'onclick' => 'if(!confirm("Are you sure to continue ?")){return false;}'),
			'#type' 			=> 'submit',
			'#value' 			=> 'Continue'
		);
	}
	
	
	$form['other_comment_concern']['markup_end1'] 	= array(
		'#suffix' => '</div></div></div>',
	);


    return $form;
}

function get_ajax_note($form, &$form_state){
		
	$commands   = array();
	$commands[] = ajax_command_replace('#remark_id', drupal_render($form['other_comment_concern']['application_remark']));
	$commands[] = ajax_command_replace('#notesheet_id', drupal_render($form['other_comment_concern']['application_note']));
	$commands[] = ajax_command_replace('#reject_id', drupal_render($form['other_comment_concern']['application_reject']));
	$commands[] = ajax_command_replace('#register_id', drupal_render($form['other_comment_concern']['application_register']));
	$commands[] = ajax_command_replace('#zone_change_id', drupal_render($form['other_comment_concern']['application_zone_change']));
	$commands[] = ajax_command_replace('#not_recomended', drupal_render($form['other_comment_concern']['application_not_recomended']));
	$commands[] = ajax_command_replace('#recomended', drupal_render($form['other_comment_concern']['application_recomended']));
	$commands[] = ajax_command_replace('#zone_remark', drupal_render($form['other_comment_concern']['application_zone_change_note']));
	return array('#type' => 'ajax', '#commands' => $commands);
}


function renewal_send_concern_inspector_submit($form, &$form_state){
	
	
	global $user;

	$userid 			= $user->uid;
	$remark_by_name		= get_name($userid);
	$rid				= get_role_id($userid);
	$val    			= $form_state['values'];
	$service_id			= encryption_decryption_fun('decrypt',$val['serviceid_hidden']); 
	$factorytype_id		= encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$application_id		= encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$reference_no		= encryption_decryption_fun('decrypt',$val['referenceno_hidden']);
	//print_r($val);die;
	$remark_details 	= get_remark_id($application_id,$reference_no,$userid,$rid);
	$verify_details 	= $remark_details['verify_details'];

	$remark_id			= $remark_details['id'];

	$zone_field = explode(',', $verify_details);



	$remark_type='Agree';
	$value = fun_fetch_irregularities_check($application_id,$reference_no,$factory_type_id,$service_id,$remark_type,$rid);
	
 if($val['forword_user']=='1'){
	
				$cafa_remarks = array(
					'sending_time' 	  	 => date('Y-m-d h:i'),
					'remark_type'	  	 => 'n',
				);
				$queryupdate_remarks	=	db_update('fa_cafa_remarks');
				$queryupdate_remarks	->	fields($cafa_remarks);
				$queryupdate_remarks	->	condition('id',$remark_id,'=');	
				$queryupdate_remarks	->	execute();


				$identity_flag_all = NULL;
				$irregularities_details = fun_fetch_irregularities_details($identity_flag_all,$application_id,$reference_no,$factorytype_id,$service_id);
				if(!empty($irregularities_details)){

					foreach($irregularities_details as $row_irregularities_details){
						$remark_table_id 				= $row_irregularities_details->remark_table_id;
						$checklist_observations_ref_id 	= $row_irregularities_details->checklist_observations_ref_id;
					}
						$comments_irregularities_other 			= $val['comments_irregularities_other'];
						$identity_flag = 'Comments';
						$irregularities_details_name =fun_fetch_irregularities_details($identity_flag,$application_id,$reference_no,$factorytype_id,$service_id);
						if(!empty($irregularities_details_name)){
							foreach($irregularities_details_name as $row_irregularities_details_name){
								$irregularities_update = array(

														'irregularities'				=> $val['comments_irregularities_other_'.$row_irregularities_details_name->id],
														//'remark_by_ad'				=> $val['factory_adchk_'.$row_irregularities_details_name->id],
														'ad_details'					=> $userid.','.$remark_by_name ,
														'modification_by'				=> $userid,
														'modification_date'				=> date('Y-m-d'),
														
														
													);
								$queryupdate_irregularities		 =	db_update('fa_checklist_observations');
								$queryupdate_irregularities		 ->	fields($irregularities_update);
								$queryupdate_irregularities		 ->	condition('id',$row_irregularities_details_name->id,'=');	
								$queryupdate_irregularities		 ->	execute();
							}
							
						}else{

							$irregularities_1 = array(
								'irregularities'				=> $comments_irregularities_other,
								//'remark_by_ad'					=> $payment_irregularities_chk_1,
								'ad_details'					=> $userid.','.$remark_by_name ,
								'checklist_observations_ref_id' => $checklist_observations_ref_id,
								'modification_by'				=> $userid,
								'modification_date'				=> date('Y-m-d'),
								'is_extra_observation'			=> 1,
								'identity_flag'					=> 'Comments',

							);
					
							$irregularities_1_id 		 =	db_insert('fa_checklist_observations')->fields($irregularities_1) ->execute();
						}
					}
					
					if(empty($irregularities_details)){
						drupal_goto('ad_observation/part_1/default/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factorytype_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.encryption_decryption_fun('encrypt',$remark_id));
					 $checklist_observations_ref = array(
								'is_approval_notesheet'	 => 0
								
						);
					
				$queryupdate_observations_ref		 =	db_update('fa_checklist_observations_ref');
				$queryupdate_observations_ref	 	->	fields($checklist_observations_ref);
				$queryupdate_observations_ref		 ->	condition('id',$checklist_observations_ref_id,'=');	
				$queryupdate_observations_ref		 ->	execute();	
						
					}else{
						 $checklist_observations_ref = array(
								'is_approval_notesheet'	 => 1
								
						);
					
				$queryupdate_observations_ref		 =	db_update('fa_checklist_observations_ref');
				$queryupdate_observations_ref	 	->	fields($checklist_observations_ref);
				$queryupdate_observations_ref		 ->	condition('id',$checklist_observations_ref_id,'=');	
				$queryupdate_observations_ref		 ->	execute();	
						$data 			 =	 array(	'status' => 'DC','remarks' => 'Notesheet is sucessfully submitted form AD end','sending_time' => date('Y-m-d h:i'));
						$queryabc 		 =	db_update('fa_cafa_remarks');
						$queryabc		 ->	fields($data);
						$queryabc		 ->	condition('id',$remark_no,'=');	
						$queryabc		 ->	execute();



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

						drupal_goto('inspector-renewal-list');
						
					}

			  		
					drupal_set_message('Your application succefully send to concern auhtority.');
		  
	}
	 /* if($val['forword_user']=='2'){
				  
		if(in_array("zone_name", $zone_field)){
		  drupal_set_message('Please! do not check zone.','error');
		 // drupal_goto('regsection/view-register-inspector/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factorytype_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no));
	 	 }else{
		  
		  $zone_id 		= 	$val['application_zone_change'];
		  $data 			=	array('factory_zone' => $zone_id,'modification_date'=>date('Y-m-d'));
		  $queryabc 	  	=	db_update('fa_cafa');
		  $queryabc	 	->	fields($data);
		  $queryabc	  	->	condition('id',$application_id,'=');
		  $queryabc	 	->	condition('service_id',$service_id,'=');
		  $queryabc	    -> 	condition('factory_typeid',$factorytype_id,'=');
		  $queryabc	  	-> 	condition('reference_number',$reference_no,'=');	
		  $queryabc	  	->	execute();
		  drupal_set_message('Appliction forworded to specific zone.');
		  drupal_goto('inspector-registration-list/');
	  }
		  
	}*/
	
	
	//   if($val['forword_user']=='2'){
				  
		
		
		  
	// 	  $zone_id 		= 	$val['application_zone_change'];
	// 	  $data 			=	array('factory_zone' => $zone_id,'modification_date'=>date('Y-m-d'));
	// 	  $queryabc 	  	=	db_update('fa_cafa');
	// 	  $queryabc	 	->	fields($data);
	// 	  $queryabc	  	->	condition('id',$application_id,'=');
	// 	  $queryabc	 	->	condition('service_id',$service_id,'=');
	// 	  $queryabc	    -> 	condition('factory_typeid',$factorytype_id,'=');
	// 	  $queryabc	  	-> 	condition('reference_number',$reference_no,'=');	
	// 	  $queryabc	  	->	execute();
	// 	  drupal_set_message('Appliction forworded to specific zone.');
	
		  
	// }
	
	// if($val['forword_user']=='3'){
		
	// 		$cafa_remarks = array(
	// 			'sending_time' 	  	 => date('Y-m-d h:i'),
	// 			'remark_type'	  	 => 'r',
	// 			'status' 			 => 'RP',
	// 			'remarks'			 => 'RP payment request is not completed'
	// 		);
	// 		$queryupdate_remarks	=	db_update('fa_cafa_remarks');
	// 		$queryupdate_remarks	->	fields($cafa_remarks);
	// 		$queryupdate_remarks	->	condition('id',$remark_id,'=');	
	// 		$queryupdate_remarks	->	execute();

	// 		drupal_goto('repayment_observation/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factorytype_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no));
		
		
	// }
	/*if($val['forword_user']=='3'){
		if(in_array("zone_name", $zone_field)){
			$cafa_remarks = array(
				'sending_time' 	  	 => date('Y-m-d h:i'),
				'remark_type'	  	 => 'r',
				'status' 			 => 'RP',
				'remarks'			 => 'RP payment request is not completed'
			);
			$queryupdate_remarks	=	db_update('fa_cafa_remarks');
			$queryupdate_remarks	->	fields($cafa_remarks);
			$queryupdate_remarks	->	condition('id',$remark_id,'=');	
			$queryupdate_remarks	->	execute();

			drupal_goto('repayment_observation/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factorytype_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no));
		}else{
			drupal_set_message('First need to Confirm factory zone.','error');
		}
		
	}
*/
}


function fun_fetch_irregularities_check($application_id,$reference_number,$factory_type_id,$service_id,$remark_type,$role_id){
	//echo $remark_type.'--'.$application_id.'--'.$reference_number.'--'.$factory_type_id.'--'.$service_id.'<br/>';
	$query_irregularities = db_select('fa_checklist_observations', 'checklist_observations');
	$query_irregularities -> InnerJoin('fa_checklist_observations_ref', 'checklist_observations_ref','checklist_observations_ref.id = checklist_observations.checklist_observations_ref_id' );
	
	$query_irregularities ->fields('checklist_observations',array('id','irregularities','remark_by_ad','ad_details','remark_by_dd','dd_details','remark_by_jd','jd_details','is_extra_observation','checklist_observations_ref_id','identity_flag'));
	$query_irregularities ->fields('checklist_observations_ref',array('remark_table_id'));
	$query_irregularities ->condition('checklist_observations_ref.application_id', $application_id, '=');
	$query_irregularities ->condition('checklist_observations_ref.service_id', $service_id, '=');
	$query_irregularities ->condition('checklist_observations_ref.factory_type_id', $factory_type_id, '=');
	if($role_id==9){
	$query_irregularities ->condition('checklist_observations.remark_by_ad', $remark_type, '=');
	}if($role_id==10){
	$query_irregularities ->condition('checklist_observations.remark_by_dd', $remark_type, '=');
	}if($role_id==11){
	$query_irregularities ->condition('checklist_observations.remark_by_jd', $remark_type, '=');
	}
	
	//echo $query_irregularities;die;
	$query_irregularities ->orderBy('checklist_observations.id', 'asc');
	$irregularities = $query_irregularities->execute()->fetchAssoc();
	return $irregularities;
	
	
	
	}