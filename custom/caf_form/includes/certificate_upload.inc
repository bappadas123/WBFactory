<?php
function certificate_upload($form, &$form_state, $serviceid ,$factorytype,$applicationid ,$referenceid){
	
	global $base_root,$base_path,$user,$_SESSION;
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/sky-forms.css');
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factorytype);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$reference_no 	    = encryption_decryption_fun('decrypt',$referenceid);
	$form = array();
	
   	$get_fa_cafa           			= 	get_fa_cafa($application_id);
	$identification_number			= 	$get_fa_cafa['plan_approve_identification_number'];
	
	$form['serviceid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $serviceid
	);	
	$form['factorytype_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $factorytype
	);	
	$form['applicationid_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $applicationid
	);	
	$form['reference_no_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $referenceid,
	);		  
	
	$form['header'] = array(
		'#markup' 			=> t('<div class="content"><div class="sky-form">'),
	);
	$form['#attributes']['class'][] = 'sky-form custom-form-main';
	$form['factory_part_upload'] = array(
		'#type' 		=> 	 'fieldset',
		'#title' 		=> 	  t('Upload Pdf with DSC'),
		'#collapsible' 	=> 	  TRUE, // Added
		'#collapsed' 	=>    FALSE,  // Added
	 );
		   
	$form['factory_part_upload']['start_upload_section'] = array(
		'#prefix' => '<div class="row">',
	    '#suffix' => '',
	 );  
	 
	$form['factory_part_upload']['doc_file'] = array(
	   '#type' => 'file',
	   '#title' => t('Upload documents (PDF only, Max size 5MB)'),
	   '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Upload documents'),
	   '#prefix' => '<div id="replace_div_file"><div class="col-md-4">',
	   '#suffix' => '</div></div>'	
	);
	
	$form['submit'] = array(
        '#prefix' => '<div class="col-md-4">',
        '#suffix' => '</div></div>',
        '#attributes' => array(
            'class' => array(
                'btn btn-info'
            )
        ),
        '#type' => 'submit',
        '#value' => 'Save & Continue'
    	);

 return $form;
        
   }
   
function certificate_upload_submit($form, &$form_state){
	
	global $user;
	$uid = $user->uid;
	$val   								= 	$form_state['input'];
	$commands   						= 	array();
	$current_application_status         =   '';
	
	$factory_type						= 	encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
	$service_id							= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$application_id						= 	encryption_decryption_fun('decrypt',$val['applicationid_hidden']);	
	$reference_no						= 	encryption_decryption_fun('decrypt',$val['reference_no_hidden']);	
	
	if(trim($_FILES['files']['name']['doc_file'])!=""){
		
		$file_name = trim($_FILES['files']['name']['doc_file']);
		$file_path = $_FILES['files']['tmp_name']['doc_file'];
	  	$file_size = $_FILES['files']['size']['doc_file'];
 		$file_ext = pathinfo($file_name, PATHINFO_EXTENSION);
		
		$directory_path	=	file_default_scheme().'://upload/applicationpdf/';
		
		$extensions = 'pdf' ; 

	    $validators = array(
		   'file_validate_extensions' => array($extensions),   
		   'file_validate_size' => array(1*1024*1024) // 5MB
		);
		
		$error_description = "";
		if(!$file = file_save_upload('doc_file', $validators, $directory_path, FILE_EXISTS_RENAME))
		{//die('not uploaded'); 
			
			if(strtolower(trim($file_ext)) != 'pdf'){
				$error_description = "Allow to upload PDF only";
			}else if($file_size >= (1*1024*1024)){
				$error_description = "File is too big";
			}else{
				$error_description = "Unable to upload file";
			}
		}else{
			$file->status = FILE_STATUS_PERMANENT; //ADDED
		    file_save($file);
			$upld_directory_path=file_create_url($file->uri); //NOT USED
			$Full_File_Path=$file->uri;
					  
		$current_application_status = 'U';
		if(empty($identificationnumber)){
			 $identification_number = created_identification($reference_no,$service_id);
			 $caf_update = 	array('plan_approve_identification_number' => $identification_number,'plan_approve_status' => $current_application_status,'uploaded_pdf' => $file_name);	
			 
		}else{
			 $identification_number = $identificationnumber;
			 $caf_update = 	array('plan_approve_identification_number' => $identification_number,'plan_approve_status' => $current_application_status,'uploaded_pdf' => $file_name);	
		}
		
	  //---------------- CAFA TABLE UPDATE -------------------
		
		$queryapp 		 =	db_update('fa_cafa');
		$queryapp		 ->	fields($caf_update);
		$queryapp		 ->	condition('id',$application_id,'=');
		$queryapp		 ->	condition('service_id',$service_id,'=');
		$queryapp	     ->	condition('factory_typeid',$factory_type,'=');
		$queryapp		 ->	condition('reference_number',$reference_no,'=');
		$queryapp		 ->	execute();

	  //----------- WORKER TABLE UPDATE ---------------------------
	  
		$worker_status 	= 	array('worker_plan_approval_status' => $current_application_status);
		$querywork 		=	db_update('fa_worker_details');
		$querywork		->	fields($worker_status);
		$querywork		->	condition('application_id',$application_id,'=');
		$querywork		->	condition('service_id',$service_id,'=');
		$querywork		->	condition('factory_type',$factory_type,'=');
		$querywork		->	condition('application_reference_no',$reference_no,'=');
		$querywork		->	execute();
	  
	  //----------------DOCUMENTS TABLE UPDATE-------------------
		$doc_status 	= 	array('plan_approval_status' => $current_application_status);
		$querydoc 		=	db_update('fa_caf_upload_doc');
		$querydoc		->	fields($doc_status);
		$querydoc		->	condition('app_id',$application_id,'=');
		$querydoc		->	condition('upload_documents_service_id',$service_id,'=');
		$querydoc	    ->	condition('upload_doc_factory_type_id',$factory_type,'=');
		$querydoc		->	condition('application_reference_no',$reference_no,'=');
		$querydoc		->	execute();
		
	  //----------------DIRECTOR DETAILS TABLE UPDATE-------------------
		$occupr_status 	= 	array('worker_plan_approval_status' => $current_application_status);
		$querydic 		=	db_update('fa_occupier_details');
		$querydic		->	fields($occupr_status);
		$querydic		->	condition('application_occupier_id',$application_id,'=');
		$querydic		->	condition('occupier_service_id',$service_id,'=');
		$querydic		->	condition('factory_type_id',$factory_type,'=');
		$querydic		->	condition('application_reference_no',$reference_no,'=');
		$querydic		->	execute();
			
	   //----------------Remarks Table Insert -------------------
	
		$cafa_remarks = array(
		'app_id'   			 => $application_id,
		'remark_by_uid' 	 => $uid,
		'sending_time' 		 => date('Y-m-d h:i:s'),
		'app_reference_no' 	 => $reference_no,
		'plan_status' 			 => $current_application_status,
		);	
		db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();
		}

	drupal_set_message('Your application along with your signature has been successfully uploaded. Application number is '.$identification_number);
	drupal_goto('applicant-dashboard');

	} else {
		drupal_goto('inspector/certificate_upload/'.$val['serviceid_hidden'].'/'.$val['factorytype_hidden'].'/'.$val['applicationid_hidden'].'/'.$val['reference_no_hidden']) ;
	}
	
}   