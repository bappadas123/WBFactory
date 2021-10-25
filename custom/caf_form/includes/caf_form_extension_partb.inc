<?php
function caf_form_extension_partb($form, &$form_state,$serviceid,$factory_typeid,$applicationid) {	
	global $base_root, $base_path;

/************************************************ Upload Part *****************************************************************/

	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	$application_id   	= encryption_decryption_fun('decrypt', $applicationid);
	
	$check_worker_tab 	= get_worker_tab_check($application_id);
	
	if(empty($check_worker_tab)){
		  //drupal_set_message(('Please! Filled up the general information of Worker Details tab'),'warning');
		 // drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the previous tab.</h5>'),'alert alert-danger alert-dismissible');
		  drupal_goto('applicant/caf_extn/details-worker-hp-extension/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid) ;
		  
	}else{
		$get_fa_cafa 		= get_fa_cafa($application_id);
		$reference_no 		= $get_fa_cafa['reference_number'];
		$plan_approve_status 		= $get_fa_cafa['plan_approve_status'];
		if($plan_approve_status == 'F'){
			 drupal_set_message(('You can only display of your application form preview'),'warning');
			  drupal_goto('applicant/caf_extn/application-preview-extension/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid) ;
		}
	}

	$form = array();
	$form['serviceid'] = array(
			'#type' => 'hidden',
			'#default_value' => $serviceid,
			);
	$form['factorytypeid'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $factory_typeid
	);
	$form['application_id_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $applicationid
	);
	$form['reference_no_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt', $reference_no)
	);
	$form['plan_approve_status_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> encryption_decryption_fun('encrypt', $plan_approve_status)
	);
	
	/********** Document Information - Start **********/

	$form['header'] = array(
		'#markup' 			=> t('<div class="content"><h3>Upload related documents of approval of plan</h3>'),
	);
	$form['#attributes']['class'][] = 'custom-form-main';
	$form['factory_part_upload'] = array(
		'#type' 		=> 	 'fieldset',
		'#title' 		=> 	  t('I. Upload Related Documents'),
		'#collapsible' 	=> 	  TRUE, // Added
		'#collapsed' 	=>    FALSE,  // Added
	 );
	$form['factory_part_upload']['start_upload_section'] = array(
		'#prefix' => '<table class="table table-bordered custom-table-view"> <tr>
						<th>Related Doucemts</th>
						<th>Upload Documents</th>
						<th class="center">Uploaded documents</th>
						</tr>',
		'#suffix' => '',
	 );  
	 
	/*$form['factory_part_upload']['conditions'] = array(
		'#prefix' => '<div id="condition_id">',
		'#suffix' => '</div>',
	);*/

	$i=0;
	$documents_master_details	= documents_master_details($service_id,$factory_type_id);
	//echo "<pre>"; print_r($documents_master_details);
	foreach($documents_master_details as $documents){
		
		$view_fid	= view_attached_filename($application_id,$reference_no,$factory_type_id,$documents->id,$service_id);
		$upoladed_doc = get_uploaded_document_url($view_fid['fid']);
		if(!empty($upoladed_doc)){ 
				$url 		= explode('//',$upoladed_doc);
				$doc_url	= $url[1];
				$view		='<a title = "Click here to view '.$documents->document_name.'" href="'.$GLOBALS['base_url'].'/sites/default/files/'.$doc_url.'" target="_blank"><i class="ace-icon fa fa-file-pdf-o bigger-130"></i></a>';
				
			
		}else{
			$view = "Not Found";
		}
			$form['factory_part_upload']['related_documents1_'.$documents->id] = array(
						
						'#type' 	 => 'markup',
						'#markup' 	 =>  '<tr><td>',
		  
					);
					
		if($documents->status == 1){
			$form['factory_part_upload']['related_documents_'.$documents->id] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 	 		=> '</div></td><td><div class="col-xs-12">',
					  '#type' 				=> 'textfield',
					  '#title'				=>	t('Documents Name'),
					  '#required' 			=> TRUE,
					  '#default_value'		=> $documents->document_name,
					  '#attributes' 		=> array('class'=>array('form-control'),'readonly'=>'readonly'),
					);
			$form['factory_part_upload']['uploade_file_'.$documents->id] 	= array(
					  '#prefix' 			=> '',
					  '#suffix' 	 		=> '',
					  '#type' 				 => 'managed_file',
					  '#title'				=>	t('Upload'),
					  '#required' 			=> (empty($upoladed_doc)) ? TRUE : FALSE,
					  '#upload_location' 	=> 'public://upload/cafdoc/',
					  '#upload_validators' 	 => array('file_validate_extensions' => array('pdf'), 'file_validate_size' => array(50*1024*1024)),
					  '#process' 			=> array('import_my_file_element_process'),
					   '#attributes' 		=> array('class'=>array('form-control'),'readonly'=>'readonly'),
					);

		}else{
			
			$form['factory_part_upload']['related_documents_'.$documents->id] 	= array(
					  '#prefix' 			=> '<div class="col-xs-12">',
					  '#suffix' 	 		=> '</div></td><td><div class="col-xs-12">',
					  '#type' 				=> 'textfield',
					  '#title'				=>	t('Documents Name'),
					  '#default_value'		=> $documents->document_name,
					  '#attributes' 		=> array('class'=>array('form-control'),'readonly'=>'readonly'),
					);
			$form['factory_part_upload']['uploade_file_'.$documents->id] 	= array(
					  '#prefix' 			=> '',
					  '#suffix' 	 		=> '',
					  '#type' 				 => 'managed_file',
					  '#title'				=>	t('Upload'),
					  
					  '#upload_location' 	=> 'public://upload/cafdoc/',
					  '#upload_validators' 	 => array('file_validate_extensions' => array('pdf'), 'file_validate_size' => array(50*1024*1024)),
					  '#process' 			=> array('import_my_file_element_process'),
					   '#attributes' 		=> array('class'=>array('form-control'),'readonly'=>'readonly'),
					);
			}
			
				$form['factory_part_upload']['uploded_doc_'.$documents->id] 	= array(
					  '#prefix' 			=> '</div></td><td valign="bottom"><div class="col-xs-12">',
					  '#suffix' 	 		=> '</div>',
					  '#type' 				=> 'markup',
					  '#markup'				=>	$view,
					  '#attributes' 		=> array('class'=>array('form-control')),
					);
	
			$form['factory_part_upload']['related_documents2_'.$documents->id] = array(
						
						'#type' 	 => 'markup',
						'#markup' 	 =>  '</td></tr>',
					);
		//$i=$i+1;  	
	}
	
	$form['factory_part_upload']['end_upload_section'] = array(
		'#prefix' => '',
		'#suffix' => '</table>',
	 );
	 
	$form['submit'] = array (
		  '#prefix' => '',  
		  '#suffix' => '</div>',
		  '#attributes' => array(
			'class' => array(
				'btn btn-dark pull-right'
			)
			),
		  '#type' => 'submit',
		  '#value' => 'Save & Continue'
	); 
	return $form; 
 }	

/******************************************** Upload Part End *****************************************************************/

function caf_form_extension_partb_submit($form, &$form_state){
	global $user;
	$val   							= 	$form_state['values'];
	$commands   					= 	array();
	
	$service_year					=  $val['service_year'];
	$factory_type					=  encryption_decryption_fun('decrypt',$val['factorytypeid']);
	$service_id						=  encryption_decryption_fun('decrypt',$val['serviceid']);
	$application_id					=  encryption_decryption_fun('decrypt',$val['application_id_hidden']);	
	$reference_no					=  encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	$plan_approve_status 		 	=  encryption_decryption_fun('decrypt', $val['plan_approve_status_hidden']);	
	//del_doc($application_id,$service_id,$factory_type,$reference_no);
	$documents_master_details		= documents_master_details($service_id,$factory_type);
	
	foreach($documents_master_details as $documents){
		
		$uploaded_doc 	= fileupload($val['uploade_file_'.$documents->id]);
		if(!empty($uploaded_doc))
		{
			$doc_file_details = array(
							'app_id' 						=> $application_id,
							'uid'							=> $user->uid,
							'fid' 							=> $uploaded_doc->fid,
							'doc_name' 						=> $uploaded_doc->filename,
							'file_name' 					=> $documents->document_name,
							'upload_documents_service_id' 	=> $service_id,
							'upload_doc_factory_type_id' 	=> $factory_type,
							'application_reference_no'   	=> $reference_no,
							'plan_approval_status'    		=> 'In',
							'doc_id'					    => $documents->id 
						);
						
			//echo "<pre>"; print_r($doc_file_details); //die;
			$id = db_insert('fa_caf_upload_doc')->fields($doc_file_details)->execute();
		} 
	}
			if($id){ 
				drupal_set_message('Dcocument has been uploaded successfully.');
				drupal_goto('applicant/caf_extn/application-preview-extension/'.$val['serviceid'].'/'.$val['factorytypeid'].'/'.$val['application_id_hidden']) ;
			}
	} 
