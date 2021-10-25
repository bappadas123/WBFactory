<?php
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
function renewal_concern_dd($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$referenceno)
{ 
    global $base_root, $base_path, $user;
	$form            	= array();
	
	$userid = $user->uid;
	$rid= get_role_id($userid);
	   
    $service_id      	= encryption_decryption_fun('decrypt', $serviceid);
    $factory_type_id 	= encryption_decryption_fun('decrypt', $factory_typeid);
    $application_id  	= encryption_decryption_fun('decrypt', $applicationid);
	$reference_no  		= encryption_decryption_fun('decrypt', $referenceno);


	//echo  $application_id.'--'.$reference_no.'--'.$service_id.'--'.$factory_type_id;die;
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


	
	$irregularities_details = fun_fetch_irregularities_details($identity_flag_all,$application_id,$reference_no,$factorytype_id,$service_id);
	if(!empty($irregularities_details)){

		foreach($irregularities_details as $row_irregularities_details){
			$noteshotsheet_type 				= $row_irregularities_details->is_approval_notesheet;
			$checklist_observations_ref_id 	= $row_irregularities_details->checklist_observations_ref_id;
		}
	}
	if($noteshotsheet_type == '1'){
		$view_notesheet_pdf = l('View Recomended Notesheet', 'regsection/registration-view-notesheet/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'View Notesheet', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));
		//$view_notesheet = l('View Notesheet', 'regsection/registration-view-notesheet/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'View Notesheet', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));
	}else{
		//$lnk=$base_root.$base_path.'regsection/deputy-note-list/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/nojs';
		//$view_notesheet = ctools_modal_text_button(t('Details Notesheet list View'), $lnk ,t('Details Notesheet list View')) ;

		//$view_notesheet_pdf = l('View Recomended Notesheet', 'regsection/registration-view-notesheet/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'View Notesheet', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));
		$not_notesheet_pdf = l('Not Recomended Notesheet', 'regsection/registration-not-view-notesheet/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'View Notesheet', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));
	}
	$notification= l('Notification to Applicant', 'applicant_notification/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));
	if($service_id==3){
		$lic_link	= l('Download Licence Certificate', 'regsection/registration-licence-genarate-file/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));

		//$lic_link	= l('Renewal Licence Certificate', 'deputy-renewal/renewal-licence-file/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));
	}
	if($service_id==8){
		$lic_link	= l('Amendment Certificate', 'amendment-section/amendment-licence-file/'.encryption_decryption_fun('encrypt',$service_id).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('btn bg-navy margin'))));
	
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
		'1'=>'Approve',
		//'2'=>'Back to Assistance Director',
   		'3'=>'Back to Applicant',
   		'4'=>'Reject',
	);
	if(($rid== 9 && $application_status == 'U') || ($rid==10 && $application_status == 'DC') ){

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

	$form['other_comment_concern']['download_licence'] = array(
		'#prefix' => '<div id="download_licence">',
		'#suffix' => '</div>',
	);
	$form['other_comment_concern']['lic_doc_file'] = array(
		'#prefix' => '<div id="edit-lic-doc-file-ajax-wrapper">',
		'#suffix' => '</div>',
	);

	$form['other_comment_concern']['download_registration'] = array(
		'#prefix' => '<div id="download_registration">',
		'#suffix' => '</div>',
	);
	$form['other_comment_concern']['reg_doc_file'] = array(
		'#prefix' => '<div id="edit-reg-doc-file-ajax-wrapper">',
		'#suffix' => '</div>',
	);
	$form['other_comment_concern']['application_notification']	= array(
		'#prefix' 	=> '<div id="notification">',
		'#suffix' 	=> '</div>',
	);
	
	if($action == 1){
		$form['other_comment_concern']['download_licence'] = array(
			'#prefix' => '<div  class="col-md-3 col-xs-3" id="download_licence">'.$lic_link,
			'#suffix' => '</div>',
			);
		
		$form['other_comment_concern']['lic_doc_file'] = array(
			'#prefix' => '<div class="col-md-3 col-xs-3" id="edit-lic-doc-file-ajax-wrapper">',
			'#suffix' => '</div>',
			'#title' => 'Upload Licence Certificate.',
			'#type' => 'managed_file',
			'#required' => TRUE,
			'#attributes' => array('id' => '','autocomplete' => 'off','class'=>array('form-group')),
			'#process' 	  => array('import_my_file_element_process'),
			'#upload_location' 	  => 'public://upload/upload_pdf/',
			'#upload_validators' 	 => array('file_validate_extensions' => array('pdf'), 'file_validate_size' => array(50*1024*1024))
			);
	
		}
		
		if($action == 3){
			$remark_type='Agree';
			$value = fun_fetch_irregularities_check($application_id,$reference_no,$factory_type_id,$service_id,$remark_type,$rid);
			//print_r($value);die($application_id.'--'.$reference_no.'--'.$factory_type_id.'--'.$service_id.'--'.$remark_type.'--'.$rid);
			if(!empty($value)) {
				$form['other_comment_concern']['application_not_recomended']	= array(
					'#prefix' 	=> '<div class="col-md-2"><div id="not_recomended"><label class="input label-block">'.$not_notesheet_pdf,
					'#suffix' 	=> '</label></div></div>',
				);
			}
			$form['other_comment_concern']['application_notification']	= array(
				'#prefix' 	=> '<div class="col-md-2"><div id="notification"><label class="input label-block">'.$notification,
				'#suffix' 	=> '</label></div></div>',
			);
	
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
	$commands[] = ajax_command_replace('#notification', drupal_render($form['other_comment_concern']['application_notification']));
	$commands[] = ajax_command_replace('#zone_remark', drupal_render($form['other_comment_concern']['application_zone_change_note']));
	$commands[] = ajax_command_replace('#download_licence', drupal_render($form['other_comment_concern']['download_licence']));
	$commands[] = ajax_command_replace('#edit-lic-doc-file-ajax-wrapper', drupal_render($form['other_comment_concern']['lic_doc_file']));
		
	return array('#type' => 'ajax', '#commands' => $commands);
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
	}
	//echo $query_irregularities;die;
	$query_irregularities ->orderBy('checklist_observations.id', 'asc');
	$irregularities = $query_irregularities->execute()->fetchAssoc();
	//print_r($irregularities);die;
	return $irregularities;
	
	
	
}

function renewal_concern_dd_submit($form, &$form_state){
	global $user;
	$uid 			= 	$user->uid;
	$val 			= 	$form_state['values'];
	$service_id 	= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']); 
   	$factorytype_id = 	encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
   	$application_id = 	encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$reference_no	=  	encryption_decryption_fun('decrypt',$val['referenceno_hidden']);
	   
	$applicant_id	=  	encryption_decryption_fun('decrypt',$val['applicant_id_hidden']);
	$get_licence_valid_to 	= get_licence_valid_to($service_id,$factorytype_id,$application_id,$reference_no);

	// echo 	$application_id.'--'.$service_id .'--'.$factorytype_id.'--'.$application_id.'--'.$reference_no;die;

	$remark_details 	= get_remark_id($application_id,$reference_no,$userid,$rid);

	$verify_details 	= $remark_details['verify_details'];
	$remark_id			= $remark_details['id'];

	$zone_field = explode(',', $verify_details);

	$remark_type='Agree';
	$value = fun_fetch_irregularities_check($application_id,$reference_no,$factorytype_id,$service_id,$remark_type,$rid);

	if($val['forword_user']=='1'){
		$application_pdf =  file_load($val['lic_doc_file']);
			if($application_pdf != "" ){
				if(service_id==3){
					$document_name = "License Certificates";
				}if(service_id==8){
					$document_name = "License Certificates";
				}

				$document_listid =  fun_fetch_document_listid($document_name);

				$path_category = pathinfo($application_pdf->filename);
					
				$new_filename_cat = 'LIC_CERTIFICATE'.date('Y').'_'.$factory_type_id.'_'.time().'.'.$path_category['extension'];
				$application_pdf->filename = $new_filename_cat;
			   // file_save($application_pdf);
		
				$filename_cat_arr = explode("/", $application_pdf->uri);
		
				$filepathSave_cat 	= file_get_contents(escapefile_url('public://upload/upload_pdf/'.$filename_cat_arr[4]));
				
				$content_cat		= base64_encode($filepathSave_cat);
		
					$cat_doc_content_arr = array(
						'upload_doc_content' => $content_cat,
					);		
				$get_CAF = get_caf_upload_doc_details($application_id, $service_id, 'LIC', $factorytype_id, $reference_no);
		
				if(!empty($get_CAF)){
					
					$content_id = $get_CAF->upload_doc_content_id;
		
					$queryabc = db_update('fa_caf_upload_doc_content');
						$queryabc->fields($cat_doc_content_arr);
						$queryabc->condition('id', $content_id, '=');
						$queryabc->execute();
							
						$cat_upload_doc = array(
							'file_name' 		=> $new_filename_cat,
							'created_date'		=> date('Y-m-d h:i:s'),
						
						);
						$queryabc = db_update('fa_caf_upload_all_doc');
						$queryabc->fields($cat_upload_doc);
						$queryabc->condition('upload_doc_content_id', $content_id, '=');
						$queryabc->execute();
							
							 
					}else{
		
						$id_doc =  db_insert('fa_caf_upload_doc_content')->fields($cat_doc_content_arr)->execute();
						$cat_upload_doc_arr = array(
							'application_id' 				=> $application_id,
							'application_reference_no' 		=> $reference_no,
							'file_name' 					=> $new_filename_cat,
							'factory_typeid' 				=> $factorytype_id,
							'service_id' 					=> $service_id,
							'upload_doc_content_id' 		=> $id_doc,
							'upload_doc_type' 				=> 'LIC',
							'created_by'					=> $uid,
							'created_date'				 	=> date('Y-m-d h:i:s'),
							'doc_master_id'					=> $document_listid['id'],
							'identity_flag'					=> $document_listid['identity_flag']

						);
						db_insert('fa_caf_upload_all_doc')->fields($cat_upload_doc_arr)->execute();
					}
				}
				$status ='I';
				//---------------- CAFA TABLE UPDATE -------------------
				$data =	 array('application_status' => $status,'approve_dsc_licence_file_id'=>$licence_file_id,'license_valid_upto' => $get_licence_valid_to);		
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
				
				drupal_set_message('Application has been successfully approved.');


	}






	if($val['forword_user']=='2'){
		$status 	= 'DCBk';
		$type 		= 'r';
		$details	= $val['application_remark'];
		
		$cafa_remarks = array(
			'app_id'   			 => $application_id,
			'remark_by_uid' 	 => $uid,
			'remark_by_roleid' 	 => $rid,
			'remark_to_roleid' 	 => 10,
			'sending_time' 		 => date('Y-m-d h:i:s'),
			'app_reference_no' 	 => $reference_no,
			'remarks' 	         => $details,
			'remark_type'		 => 'n',
			'remark_by_name'	 => $remark_by_name,
			'verify_details'	 => $val['fieldname'],
			'status' 			 => 'DCBk',
		);
		db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();	
		
		$data =	 array('application_status' => $status);		
		$queryabc	=	db_update('fa_cafa');
		$queryabc	->	fields($data);
		$queryabc	->	condition('id',$application_id,'=');
		$queryabc	->	condition('service_id',$service_id,'=');
		$queryabc	->	condition('factory_typeid',$factorytype_id,'=');
		$queryabc	->	condition('reference_number',$reference_no,'=');		
		$queryabc	->	execute();		
		//-----------Worker table update---------------------------
		$worker_status 	= 	array('worker_registration_status' => $status);
		$queryabc 		=	db_update('fa_worker_details');
		$queryabc		->	fields($worker_status);
		$queryabc		->	condition('application_id',$application_id,'=');
		$queryabc		->	condition('service_id',$service_id,'=');
		$queryabc		->	condition('factory_type',$factorytype_id,'=');
		$queryabc		->	condition('application_reference_no',$reference_no,'=');
		$queryabc		->	execute();
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
		$querymanufacturing 	=	db_update('fa_nature_manufacturing');
		$querymanufacturing		->	fields($manufacturing_status);
		$querymanufacturing		->	condition('application_id',$application_id,'=');
		$querymanufacturing		->	condition('service_id',$service_id,'=');
		$querymanufacturing		->	condition('factory_type',$factorytype_id,'=');
		$querymanufacturing		->	condition('application_reference_no',$reference_no,'=');
		$querymanufacturing		->	execute();
		 //-----------Power table update---------------------------
		$power_status = array('power_application_status' => $status);
		$querypower	  =	db_update('fa_power_details');
		$querypower	->	fields($power_status);
		$querypower	->	condition('application_id',$application_id,'=');
		$querypower	->	condition('service_id',$service_id,'=');
		$querypower	->	condition('factory_type',$factorytype_id,'=');
		$querypower	->	condition('application_reference_no',$reference_no,'=');
		$querypower	->	execute();
		 //-----------Director table update---------------------------
		$director_status = 	array('application_status' => $status);
		$querydirector 	=	db_update('fa_director_details');
		$querydirector	->	fields($director_status);
		$querydirector	->	condition('application_director_id',$application_id,'=');
		$querydirector	->	condition('director_service_id',$service_id,'=');
		$querydirector	->	condition('factory_type_id',$factorytype_id,'=');
		$querydirector	->	condition('application_reference_no',$reference_no,'=');
		$querydirector	->	execute();
		//-----------Manager table update---------------------------
		$manager_status = 	array('application_status' => $status);
		$querymanager 	=	db_update('fa_manager_details');
		$querymanager	->	fields($manager_status);
		$querymanager	->	condition('application_manager_id',$application_id,'=');
		$querymanager	->	condition('manager_service_id',$service_id,'=');
		$querymanager	->	condition('factory_type_id',$factorytype_id,'=');
		$querymanager	->	condition('application_reference_no',$reference_no,'=');
		$querymanager	->	execute();
		
		drupal_set_message('Application has been successfully revart to assistance director');
	} 
	if($val['forword_user']=='3'){
		$status 	= 'B';
		$details 	= $val['application_remark'];
		
		$cafa_remarks = array(
			'app_id'   			 => $application_id,
			'remark_by_uid' 	 => $uid,
			'remark_by_roleid' 	 => $rid,
			'remark_to_roleid' 	 => NULL,
			'sending_time' 		 => date('Y-m-d h:i:s'),
			'app_reference_no' 	 => $reference_no,
			'remarks' 	         => $details,
			'remark_type'		 => 'n',
			'remark_by_name'	 => $remark_by_name,
			'verify_details'	 => $val['fieldname'],
			'status' 			 => 'B',
		);
		db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();	
		
		$data =	 array('application_status' => $status, 'download_status'=>NULL);		
		$queryabc	=	db_update('fa_cafa');
		$queryabc	->	fields($data);
		$queryabc	->	condition('id',$application_id,'=');
		$queryabc	->	condition('service_id',$service_id,'=');
		$queryabc	->	condition('factory_typeid',$factorytype_id,'=');
		$queryabc	->	condition('reference_number',$reference_no,'=');		
		$queryabc	->	execute();		
		//-----------Worker table update---------------------------
		$worker_status 	= 	array('worker_registration_status' => $status);
		$queryabc 		=	db_update('fa_worker_details');
		$queryabc		->	fields($worker_status);
		$queryabc		->	condition('application_id',$application_id,'=');
		$queryabc		->	condition('service_id',$service_id,'=');
		$queryabc		->	condition('factory_type',$factorytype_id,'=');
		$queryabc		->	condition('application_reference_no',$reference_no,'=');
		$queryabc		->	execute();
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
		$querymanufacturing 	=	db_update('fa_nature_manufacturing');
		$querymanufacturing		->	fields($manufacturing_status);
		$querymanufacturing		->	condition('application_id',$application_id,'=');
		$querymanufacturing		->	condition('service_id',$service_id,'=');
		$querymanufacturing		->	condition('factory_type',$factorytype_id,'=');
		$querymanufacturing		->	condition('application_reference_no',$reference_no,'=');
		$querymanufacturing		->	execute();
		 //-----------Power table update---------------------------
		$power_status = array('power_application_status' => $status);
		$querypower	  =	db_update('fa_power_details');
		$querypower	->	fields($power_status);
		$querypower	->	condition('application_id',$application_id,'=');
		$querypower	->	condition('service_id',$service_id,'=');
		$querypower	->	condition('factory_type',$factorytype_id,'=');
		$querypower	->	condition('application_reference_no',$reference_no,'=');
		$querypower	->	execute();
		 //-----------Director table update---------------------------
		$director_status = 	array('application_status' => $status);
		$querydirector 	=	db_update('fa_director_details');
		$querydirector	->	fields($director_status);
		$querydirector	->	condition('application_director_id',$application_id,'=');
		$querydirector	->	condition('director_service_id',$service_id,'=');
		$querydirector	->	condition('factory_type_id',$factorytype_id,'=');
		$querydirector	->	condition('application_reference_no',$reference_no,'=');
		$querydirector	->	execute();
		//-----------Manager table update---------------------------
		$manager_status = 	array('application_status' => $status);
		$querymanager 	=	db_update('fa_manager_details');
		$querymanager	->	fields($manager_status);
		$querymanager	->	condition('application_manager_id',$application_id,'=');
		$querymanager	->	condition('manager_service_id',$service_id,'=');
		$querymanager	->	condition('factory_type_id',$factorytype_id,'=');
		$querymanager	->	condition('application_reference_no',$reference_no,'=');
		$querymanager	->	execute();
	
		drupal_set_message('Application has been successfully revart to applicant.');
	}
	if($val['forword_user']=='4'){
		$status 	= 'R';
		$type		= 'r';
		$details 	= $val['application_reject'];
		$cafa_remarks = array(
			'app_id'   			 => $application_id,
			'remark_by_uid' 	 => $uid,
			'remark_by_roleid' 	 => $rid,
			'remark_to_roleid' 	 => 10,
			'sending_time' 		 => date('Y-m-d h:i:s'),
			'app_reference_no' 	 => $reference_no,
			'remarks' 	         => $details,
			'remark_type'		 => 'n',
			'remark_by_name'	 => $remark_by_name,
			'verify_details'	 => $val['fieldname'],
			'status' 			 => 'R',
		);
		//print_r($cafa_remarks);die;
		db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();	
		
		$data =	 array('application_status' => $status);		
		$queryabc	=	db_update('fa_cafa');
		$queryabc	->	fields($data);
		$queryabc	->	condition('id',$application_id,'=');
		$queryabc	->	condition('service_id',$service_id,'=');
		$queryabc	->	condition('factory_typeid',$factorytype_id,'=');
		$queryabc	->	condition('reference_number',$reference_no,'=');		
		$queryabc	->	execute();		
		//-----------Worker table update---------------------------
		$worker_status 	= 	array('worker_registration_status' => $status);
		$queryabc 		=	db_update('fa_worker_details');
		$queryabc		->	fields($worker_status);
		$queryabc		->	condition('application_id',$application_id,'=');
		$queryabc		->	condition('service_id',$service_id,'=');
		$queryabc		->	condition('factory_type',$factorytype_id,'=');
		$queryabc		->	condition('application_reference_no',$reference_no,'=');
		$queryabc		->	execute();
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
		$querymanufacturing 	=	db_update('fa_nature_manufacturing');
		$querymanufacturing		->	fields($manufacturing_status);
		$querymanufacturing		->	condition('application_id',$application_id,'=');
		$querymanufacturing		->	condition('service_id',$service_id,'=');
		$querymanufacturing		->	condition('factory_type',$factorytype_id,'=');
		$querymanufacturing		->	condition('application_reference_no',$reference_no,'=');
		$querymanufacturing		->	execute();
		 //-----------Power table update---------------------------
		$power_status = array('power_application_status' => $status);
		$querypower	  =	db_update('fa_power_details');
		$querypower	->	fields($power_status);
		$querypower	->	condition('application_id',$application_id,'=');
		$querypower	->	condition('service_id',$service_id,'=');
		$querypower	->	condition('factory_type',$factorytype_id,'=');
		$querypower	->	condition('application_reference_no',$reference_no,'=');
		$querypower	->	execute();
		 //-----------Director table update---------------------------
		$director_status = 	array('application_status' => $status);
		$querydirector 	=	db_update('fa_director_details');
		$querydirector	->	fields($director_status);
		$querydirector	->	condition('application_director_id',$application_id,'=');
		$querydirector	->	condition('director_service_id',$service_id,'=');
		$querydirector	->	condition('factory_type_id',$factorytype_id,'=');
		$querydirector	->	condition('application_reference_no',$reference_no,'=');
		$querydirector	->	execute();
		//-----------Manager table update---------------------------
		$manager_status = 	array('application_status' => $status);
		$querymanager 	=	db_update('fa_manager_details');
		$querymanager	->	fields($manager_status);
		$querymanager	->	condition('application_manager_id',$application_id,'=');
		$querymanager	->	condition('manager_service_id',$service_id,'=');
		$querymanager	->	condition('factory_type_id',$factorytype_id,'=');
		$querymanager	->	condition('application_reference_no',$reference_no,'=');
		$querymanager	->	execute();
		drupal_set_message('Appliction has been Rejected.');	
	}




















}

?>
