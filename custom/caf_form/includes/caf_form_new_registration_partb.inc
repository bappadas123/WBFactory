 <?php
//,$applicationid
drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/sky-forms.css');
function caf_form_new_registration_partb($form, &$form_state, $serviceid, $factory_typeid,$applicationid, $linknumber,$flagmapp)
{
    global $base_root, $base_path;
    /************************************************ Upload Part *****************************************************************/
   
  
   $service_id         = encryption_decryption_fun('decrypt', $serviceid);
    $factory_type_id   = encryption_decryption_fun('decrypt', $factory_typeid);
$application_id   = encryption_decryption_fun('decrypt', $applicationid);
   
   $get_fa_cafa = get_fa_cafa($application_id);
    $reference_no = $get_fa_cafa['reference_number'];
	
	$form = array();
	$form['serviceid'] = array(
			'#type' => 'hidden',
			'#default_value' => $serviceid,
			);
	$form['factorytypeid'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> $factory_typeid
			 
	);	
	$form['reference_no_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt', $reference_no)
			 
	);
	$form['application_id_hidden'] = array(
			 '#type' 			=> 'hidden',
			 '#default_value' 	=> encryption_decryption_fun('encrypt', $applicationid)
			 
	);
	
	$form['header'] = array(
		'#markup' 			=> t('<div class="content"><div class="sky-form"><h3><b>Upload related documents of Registration</b></h3>'),
	);
	$form['#attributes']['class'][] = 'sky-form custom-form-main';
	$form['factory_part_upload'] = array(
		'#type' => 'fieldset',
		'#title' => t('Upload related documents'),
		'#collapsible' => TRUE, // Added
		'#collapsed' => FALSE,  // Added
	 );
	$form['factory_part_upload']['start_upload_section'] = array(
		'#prefix' => '<div class="row">',
	    '#suffix' => '',
	 );  
	$form['factory_part_upload']['ajax_error_div'] = array(
		'#prefix' => '<div id="ajax_error_replace_div">',
		'#suffix' => '</div>'
	 );
	
	
	$documents_master = documents_master($service_id,$factory_type_id);
	$form['factory_part_upload']['document_name'] = array(
	   '#title'=>'',
	   '#type' => 'select',
	   //'#required'=>TRUE,
	   '#attributes' => array('class'=>array(''), 'placeholder'=>'Select Document' ),
	   '#options' => $documents_master,
	   '#prefix' => '<div id="replace_div_select"><div class="col-md-4"><label class="select">Select Document<span id=\'star\'>*</span>',
	   '#suffix' => '</label></div>',
	);
	$form['factory_part_upload']['doc_file'] = array(
	   '#type' => 'file',
	   '#title' => t('Upload documents (PDF only, Max size 5MB)'),
	   '#attributes' => array('class'=>array('form-control'),'placeholder'=>'Upload documents'),
	   '#prefix' => '<div id="replace_div_file"><div class="col-md-4">',
	   '#suffix' => '</div></div>'	
	);
	$form['factory_part_upload']['add_more_btn'] 	= array(
	  '#type' => 'submit',
		//'#process' => array('ajax_process_form'),
		'#submit'=> array(),
		'#ajax' => array(
				'callback' => 'ajax_add_more_callback',
				//'wrapper' => 'table_div_replace',
			),
		'#limit_validation_errors' => array(),	
		'#value' => t('Add'),
		'#attributes' => array('class'=>array('btn btn-info')),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	);
	$form['factory_part_upload']['end_upload_section'] = array(
		'#prefix' => '',
	    '#suffix' => '</div>',
	 );
	$form['factory_part_upload']['doc_list'] = array(
			'#prefix' => '<div id="table_div_replace"><div class="col-md-12">'.get_uploaded_document_data($service_id,$factory_type_id,$application_id,$reference_no),
			'#suffix' => '</div></div>'
		);
	$form['submit'] = array (
		  '#prefix' => '</div></div><div align="right">',  
		  '#suffix' => '</div>',
		  '#type' => 'submit',
		  '#value' => 'Save & Continue'
	); 
	return $form; 
 }
 
 function get_uploaded_document_data($service_id,$factory_type,$application_id,$reference_no){
	
	$output = '';
	$sl = 0;
	$header = array(
		array('data'=> 'SL No'),
		array('data'=> 'Uploaded Document Of'),
		array('data'=> 'Document Name'),
		array('data'=> 'Action')
	);

	$rows = array();
	
	$query = db_select('fa_caf_upload_doc', 'fcud');
	$query ->fields('fcud', array( 'id', 'app_id', 'uid', 'fid', 'doc_name', 'file_name'));
	$query	-> condition('fcud.app_id', $application_id);
	$query	-> condition('fcud.upload_documents_service_id', $service_id);
	$query	-> condition('fcud.upload_doc_factory_type_id', $factory_type);
	$query	-> condition('fcud.application_reference_no', $reference_no);
	$result = $query->execute();
	$resultData = $result->fetchAll();

	$i=1;
	foreach($resultData as $val)
	{		
	$sl= $sl+1;		
		
		$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/del-plan-registration/'.$val->id.'/'.$val->fid,array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
		
		$rows [] = array(  
			array('data' => $sl), 	
			array('data' => t($val->doc_name)), 
			array('data' => t($val->file_name)),
			array('data' => $delLink),	
		);
	$i++;	
	}
	
	$output = theme_table(
	array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'table_div_replace', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
	  
	return $output;	
} 
 
function delete_uploaded_document_data($id,$fid){
	
	//global $user;
	drupal_add_library('system', 'drupal.ajax');
	
	 if (trim($fid) != 0) {
		 
		 $query = db_delete('fa_caf_upload_doc');
		 $query->condition('id', trim($id));
		 $query->execute();
		 
		 $query = db_select('file_managed', 'fm');
		 $query ->fields('fm', array('uri'));
		 $query->condition('fm.fid',trim($fid),'=');
		 $result = $query->execute();
		 $resultData = $result->fetchAssoc();
		 
		 db_delete('file_managed')->condition('fid',$fid)->execute();
		 
		 drupal_unlink($resultData['uri']);
		 
		 $commands = array();
		 $commands[] = ajax_command_replace('#table_div_replace', "<div id='table_div_replace'><div class='col-md-12'>".get_uploaded_document_data()."</div></div>");
		 $page = array('#type' => 'ajax', '#commands' => $commands);
		 ajax_deliver($page);
		
	 }else{
		  return array(
		  '#markup' => 'TTTTT',
		);
	 }
}

 
function ajax_add_more_callback($form, &$form_state){
	
	global $user;
	$commands   = array();
	
	
	 $factorytypeid						=	$form_state['input']['factorytypeid'];
	 $serviceid						=	$form_state['input']['serviceid'];
	$factory_type						= 	encryption_decryption_fun('decrypt',$factorytypeid);
	$service_id							= 	encryption_decryption_fun('decrypt',$serviceid);
	$application_id						= 	encryption_decryption_fun('decrypt',$val['application_id_hidden']);	
	echo $reference_no						= 	encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	if(trim($form_state['input']['document_name'])!="" && trim($_FILES['files']['name']['doc_file'])!=""){
		
		
		$document_name = trim($form_state['input']['document_name']);
		$file_name = trim($_FILES['files']['name']['doc_file']);
		$file_path = $_FILES['files']['tmp_name']['doc_file'];
	  	$file_size = $_FILES['files']['size']['doc_file'];
		$file_ext = pathinfo($file_name, PATHINFO_EXTENSION);
		
		$directory_path	=	file_default_scheme().'://upload/cafdoc/';
		
		$extensions = 'pdf' ; 

	    $validators = array(
		   'file_validate_extensions' => array($extensions),   
		   'file_validate_size' => array(1*1024*1024) // 5MB
		);
		
		$error_description = "";
		if(!$file = file_save_upload('doc_file', $validators, $directory_path, FILE_EXISTS_RENAME)){
			//die('not uploaded');
			
			if(strtolower(trim($file_ext)) != 'pdf'){
				$error_description = "Allow to upload PDF only";
			}else if($file_size >= (1*1024*1024)){
				$error_description = "File is too big";
			}else{
				$error_description = "Unable to upload file";
			}
			$commands[] = ajax_command_replace('#ajax_error_replace_div', '<div id="ajax_error_replace_div" style="color:#F00"><div class="col-md-12">'.$error_description.'</div></div>');
		}else{
			
			
			$file->status = FILE_STATUS_PERMANENT; //ADDED
		    file_save($file);
			$upld_directory_path=file_create_url($file->uri); //NOT USED
			$Full_File_Path=$file->uri;
			
			$doc_file_details = array(
							'app_id' 						=> $application_id,
							'fid' 							=> $file->fid,
							'uid'							=> $user->uid,
							'doc_name' 						=> trim($form_state['input']['document_name']),
							'file_name' 					=> trim($_FILES['files']['name']['doc_file']),
							'upload_documents_service_id' 	=> $service_id,
							'upload_doc_factory_type_id' 	=> $factory_type,
						    'application_reference_no'   	 => $reference_no,
							'plan_approval_status'    		=> 'In',
							
						);
						print_r($doc_file_details);die();
					
				
			$id = db_insert('fa_caf_upload_doc')->fields($doc_file_details)->execute();
			if($id){
				
				$commands[] = ajax_command_replace('#replace_div_file', drupal_render($form['factory_part_upload']['doc_file']));
				$commands[] = ajax_command_replace('#table_div_replace', '<div id="table_div_replace"><div class="col-md-12">'.get_uploaded_document_data($service_id,$factory_type,$application_id,$reference_no).'</div></div>');
				$commands[] = ajax_command_replace('#ajax_error_replace_div', '<div id="ajax_error_replace_div" style="color:#F00"><div class="col-md-12">'.$error_description.'</div></div>');
				
			}
			
		}
		
	}else{
		$commands[] = ajax_command_replace('#ajax_error_replace_div', '<div id="ajax_error_replace_div" style="color:#F00"><div class="col-md-12">Please Enter Document Name and Select File</div></div>');
	}
	
	return array('#type' => 'ajax', '#commands' => $commands);
	
} 	
/******************************************** Upload Part End *****************************************************************/
function caf_form_extension_partb_submit($form, &$form_state){
	$val   							= $form_state['values'];
    drupal_goto('applicant/caf/application-preview-extension/' . $val['serviceid'] . '/' . $val['factorytypeid']. '/' . encryption_decryption_fun('encrypt',$plan_extenid));
} 