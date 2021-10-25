<?php
function inspector_application_view($form, &$form_state,$serviceid ,$factorytype,$applicationid ,$referenceid){
	
	global $base_root,$base_path,$user,$_SESSION;
	
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/sky-forms.css');
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factorytype);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$reference_no 	= encryption_decryption_fun('decrypt',$referenceid);
	$form = array();
	
	$form['header'] = array(
		'#markup' 			=> t('<div class="content"><div class="sky-form"><h3 style="text-align: center;"><b>Application for Approval of Plan</b><p>All inputs are provided by applicant only</p><p>All inputs are to be verified by officials</p></h3>'),
	);
		
   $form['application_preview'] = array(
		'#type' 			=> 'fieldset',
		'#title' 			=> t('Factory Information'),
		'#collapsible' 		=> TRUE, // Added
		'#collapsed' 		=> FALSE,  // Added
  	);
	$form['application_preview']['markup_appplication'] = array(
		'#type' 			=> 'markup',
		'#markup' 			=> get_application_details($service_id,$factory_type_id,$application_id,$reference_no),
  	);	
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
		 '#default_value' 	=> encryption_decryption_fun('encrypt',$reference_no),
	);		  

	$form['application_worker'] = array(
		'#type' 			=> 'fieldset',
		'#title' 			=> t('Workers Information'),
		'#collapsible' 		=> TRUE, // Added
		'#collapsed' 		=> FALSE,  // Added
  	); 
          
    $form['application_worker']['markup_appplication'] = array(
		'#type' 			=> 'markup',
		'#markup' 			=> get_all_worker($service_id,$factory_type_id,$application_id,$reference_no),
		
  	);    
	$form['application_documents'] = array(
		'#type' 			=> 'fieldset',
		'#title' 			=> t('Related Documents'),
		'#collapsible' 		=> TRUE, // Added
		'#collapsed' 		=> FALSE,  // Added
  	); 
          
    $form['application_documents']['markup_appplication'] = array(
		'#type' 			=> 'markup',
		'#markup' 			=> get_uploaded_document_data($service_id,$factory_type_id,$application_id,$reference_no),
		
  	); 
	
	$get_fa_cafa          = 	get_fa_cafa($application_id);
	$plan_approve_status  = 	$get_fa_cafa['plan_approve_status'];
	
	if($plan_approve_status == 'App'){
		
	$get_factory_plan_doc          = 	get_factory_plan_doc($service_id,$factory_type_id,$application_id,$reference_no);

	// FOR APPROVED PLAN DSC
	
	$form['application_plan_pdf'] = array(
        '#type' => 'fieldset',
        '#title' => t('Download Approval of Plan & Upload with DSC'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );
	
	$application_plan_pdf = l('<i class="ace-icon fa fa-file-pdf-o bigger-130 text-red"></i>', 'plan-approval-certificate/'.encryption_decryption_fun('encrypt',$application_id).'/'.encryption_decryption_fun('encrypt',$reference_no), array('html' => TRUE,'attributes'=>array('title' => 'Download Plan Approval', 'class'=>array(''), 'target' => '_blank')));

	$form['application_plan_pdf']['download'] = array(
			'#prefix' => '<div class="col-md-12 col-xs-12" style="padding-bottom:15px;">Download Approval of Plan '.$application_plan_pdf,
			'#suffix' => '</div>',
  	);
	
	$form['application_plan_pdf']['doc_file_1'] = array(
	   '#type' => 'file',
	   //'#required' => TRUE,
	   '#title' => t('Upload documents (PDF only, Max size 5MB)'),
	   '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Upload documents'),
	   '#prefix' => '<div class="col-md-4">',
	   '#suffix' => '</div>'	
	);

	// FOR FACTORY PLAN DSC
	
	$form['factory_plan_pdf'] = array(
        '#type' => 'fieldset',
        '#title' => t('Download Factory Plan & Upload with DSC'),
        '#collapsible' => TRUE, // Added
        '#collapsed' => FALSE // Added
    );

	$factory_plan_pdf = l('<i class="ace-icon fa fa-file-pdf-o bigger-130 text-red"></i>',file_create_url($get_factory_plan_doc[0]->uri),array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_BLANK')));

	$form['factory_plan_pdf']['download'] = array(
			'#prefix' => '<div class="col-md-12 col-xs-12" style="padding-bottom:15px;">Download Factory Plan '.$factory_plan_pdf,
			'#suffix' => '</div>',
  	);

	$form['factory_plan_pdf']['doc_file_2'] = array(
	   '#type' => 'file',
	   //'#required' => TRUE,
	   '#title' => t('Upload documents (PDF only, Max size 5MB)'),
	   '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Upload documents'),
	   '#prefix' => '<div class="col-md-4">',
	   '#suffix' => '</div>'	
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
		
		}

    return $form;
   
   }
   
function get_factory_plan_doc($service_id,$factory_type_id,$application_id,$reference_no){

	$db_or = db_or();
	$db_or ->condition('fcud.doc_id', '2');
	$db_or ->condition('fcud.doc_id', '5');

	$query 	=  db_select('fa_caf_upload_doc', 'fcud');
	$query	-> InnerJoin('file_managed', 'file' ,'file.fid = fcud.fid');
	$query 	-> fields('fcud', array( 'id', 'app_id', 'uid', 'fid', 'doc_name', 'file_name','application_reference_no','doc_id'));
	$query	-> fields('file', array('uri'));
	$query	-> condition('fcud.app_id', $application_id);
	$query	-> condition('fcud.application_reference_no', $reference_no);
	$query	-> condition('fcud.upload_documents_service_id', $service_id);
	$query	-> condition('fcud.upload_doc_factory_type_id', $factory_type_id);
	$query	-> condition($db_or);
	
	$result = $query->execute();
	$resultData = $result->fetchAll();
	
	return $resultData;
}

function inspector_application_view_submit($form, &$form_state){
	
	  global $user;
	  $uid = $user->uid;
	  $uname = $user->name;
	  $user_role = array_keys($user->roles);
	  $urole  = $user_role[1];
	  $current_application_status =   '';
	  $val   					= 	$form_state['values'];
	  echo "<pre>"; print_r($val); die;
  
	  $service_id 				= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']); 
	  $factorytype_id 			= 	encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
	  $application_id 			= 	encryption_decryption_fun('decrypt',$val['application_id_hidden']);
	  $reference_no				=  	encryption_decryption_fun('decrypt',$val['referance_no_hidden']);
	  $applicant_id				=  	encryption_decryption_fun('decrypt',$val['applicant_id_hidden']);
	  
	if((trim($_FILES['files']['name']['doc_file_1'])!="") && (trim($_FILES['files']['name']['doc_file_2'])!="")){
		
		// FILE ONE
		$file_name_1 = trim($_FILES['files']['name']['doc_file_1']);
		$file_path_1 = $_FILES['files']['tmp_name']['doc_file_1'];
	  	$file_size_1 = $_FILES['files']['size']['doc_file_1'];
 		$file_ext_1 = pathinfo($file_name_1, PATHINFO_EXTENSION);
		
		$directory_path_1	=	file_default_scheme().'://upload/applicationpdf/';
		$extensions_1 = 'pdf' ; 

	    $validators_1 = array(
		   'file_validate_extensions' => array($extensions_1),   
		   'file_validate_size' => array(1*1024*1024) // 5MB
		);
		
		// FILE TWO
		$file_name_2 = trim($_FILES['files']['name']['doc_file_2']);
		$file_path_2 = $_FILES['files']['tmp_name']['doc_file_2'];
	  	$file_size_2 = $_FILES['files']['size']['doc_file_2'];
 		$file_ext_2 = pathinfo($file_name_2, PATHINFO_EXTENSION);
		
		$directory_path_2	=	file_default_scheme().'://upload/applicationpdf/';
		$extensions_2 = 'pdf' ; 

	    $validators_2 = array(
		   'file_validate_extensions' => array($extensions_2),   
		   'file_validate_size' => array(1*1024*1024) // 5MB
		);
		
		$error_description_1 = "";
		$error_description_2 = "";
		
		$file_1 = file_save_upload('doc_file_1', $validators_1, $directory_path_1, FILE_EXISTS_RENAME);
		$file_2 = file_save_upload('doc_file_2', $validators_2, $directory_path_2, FILE_EXISTS_RENAME);
		
		if(!$file_1 || !$file_2)
		{//die('not uploaded'); 
			
			if((strtolower(trim($file_ext_1)) != 'pdf') || (strtolower(trim($file_ext_2)) != 'pdf')){
				$error_description_1 = $error_description_2 = "Allow to upload PDF only";
			}else if($file_size_1 >= (1*1024*1024)){
				$error_description_1 = $error_description_2 = "File is too big";
			}else{
				$error_description_1 = $error_description_2 = "Unable to upload file";
			}
		}else{
			
			$file_1->status = FILE_STATUS_PERMANENT; //ADDED
		    file_save($file_1);
			$upld_directory_path_1=file_create_url($file_1->uri); //NOT USED
			$Full_File_Path_1=$file_1->uri;

			$file_2->status = FILE_STATUS_PERMANENT; //ADDED
		    file_save($file_2);
			$upld_directory_path_2=file_create_url($file_2->uri); //NOT USED
			$Full_File_Path_2=$file_2->uri;

		$current_application_status = 'I';
		$caf_update = 	array('plan_approve_status' => $current_application_status,'uploaded_letter' => $file_name_1,'uploaded_plan' => $file_name_2);	
		
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
		$dirc_status 	= 	array('worker_plan_approval_status' => $current_application_status);
		$querydic 		=	db_update('fa_director_details');
		$querydic		->	fields($dirc_status);
		$querydic		->	condition('application_director_id',$application_id,'=');
		$querydic		->	condition('director_service_id',$service_id,'=');
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
		drupal_set_message('Application along with your signature has been successfully uploaded.');
		drupal_goto('inspector-plan-list');

	} else {
		drupal_set_message('File not uploaded','error');
	}



}

   
?>