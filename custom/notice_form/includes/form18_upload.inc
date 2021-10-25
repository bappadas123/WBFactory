<?php
function form18_upload($form, &$form_state, $formid='' ,$referenceid ='', $factorytypeid ='', $serviceid = ''){
	
	global $base_root,$base_path,$user,$_SESSION;
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	$form_id 	 		= encryption_decryption_fun('decrypt', $formid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$factory_typeid     = encryption_decryption_fun('decrypt', $factorytypeid);
	$service_id 	    = encryption_decryption_fun('decrypt', $serviceid);//echo $form_id.''.$reference_id.''.$factory_typeid.''.$service_id;

	$form = array();

   	//$get_fa_cafa        = 	get_fa_cafa($form_id);
	
	$form['formid_hidden'] 		= array(
			 '#type' 				=> 'hidden',
			 '#default_value' 		=> $formid
	);	
	$form['reference_no_hidden'] 	= array(
			 '#type' 				=> 'hidden',
			 '#default_value' 		=> $referenceid,
	);		  
	  	$form['factorytypeid_hidden'] 	= array(
			'#type' 				=> 'hidden',
			'#default_value' 		=> $factorytypeid
		);
			
		$form['serviceid_hidden'] 	= array(
			'#type' 				=> 'hidden',
			'#default_value' 		=> $serviceid
		);

		//$applicationID = encryption_decryption_fun('encrypt',$application_id);
		//$referenceNO = encryption_decryption_fun('encrypt',$reference_no);
		
		$pdf_link	= l('<i class="fa fa-download" aria-hidden="true"></i> Download Form18 Pdf', 'download-pdf-form-18/'.$formid.'/'.$referenceid.'/'.$factorytypeid.'/'.$serviceid, array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('btn btn-primary pull-right'))));	
	
		
	$form['header'] = array(
		'#markup' 					=> t('<div class="cus-page-outer-view"><div class="content"><center><h3><b>Notice of Accident</b></h3></center><hr>'),
	);

	$form['#attributes']['class'][] = 'custom-form-main';
	$form['factory_part_upload'] 	= array(
		'#type' 					=> 	'fieldset',
		'#title' 					=> 	t('Upload document'),
		'#collapsible' 				=> 	TRUE, //Upload Pdf with DSCm  Added
		'#collapsed' 				=>  FALSE,  // Added
		'#prefix' 					=> '<div class="" style="overflow:hidden;"><b>STEP #1</b>&nbsp;&nbsp; Download application for Digital Signature '.$pdf_link.'<br><br><b>STEP #2</b> <span class="blink"> &nbsp; Upload Pdf with DSC</span><br><br>',
	    '#suffix' 					=> '',

	 );
		   
	$form['factory_part_upload']['start_upload_section'] = array(
		'#prefix' 					=> '<div class="row">',
	    '#suffix' 					=> '',
	 );  
	/*$form['factory_part_upload']['doc_file'] = array(
	   '#type' 						=> 'file',
	   '#title' 					=> t('(PDF only, Max size 5MB)'),
	   '#attributes' 				=> array('class'=>array('form-control browse-height-auto'),'placeholder'=>'Upload documents'),
	   //'#required' 				=> TRUE,
	   '#prefix' 					=> '<div id="replace_div_file"><div class="col-md-4">',
	   '#suffix' 					=> '</div></div>'	
	);
*/
	$form['factory_part_upload']['doc_file'] = array(
	   '#type' 						=> 'managed_file',
	   '#title' 					=> t('(PDF only, Max size 5MB)'),
	   '#attributes' 				=> array('class'=>array('form-control browse-height-auto'),'placeholder'=>'Upload documents'),
	   '#required' 				    => TRUE,
	   '#upload_validators' 	 => array('file_validate_extensions' => array('pdf'), 'file_validate_size' => array(50*1024*1024)),
	   '#upload_location'           => 'public://upload/upload_pdf/',
	   '#process' 				 => array('import_my_file_element_process'),
	   '#prefix' 					=> '<div id="replace_div_file"><div class="col-md-4">',
	   '#suffix' 					=> '</div></div>',
	);

	$form['submit'] = array(
        '#prefix' 					=> '',
        '#suffix' 					=> '</div></div>',
        '#attributes' 				=> array(
        'class' 					=> array( 'btn btn-success' )),
        '#type' 					=> 'submit',
        '#value' 					=> 'Submit'
    				);
	
 return $form;
   }

function form18_upload_validate($form, &$form_state) {
		
		$file_18 = file_load($form_state['values']['doc_file']);
		
		if($file_18->filesize > 2097152) {
			form_set_error('file_18_size', 'The file '.$file_18->filename.' could not be uploaded, because it exceeds 2 MB, the maximum allowed size for uploads.');	
		}
		
		/*$fid_18 = $form_state['values']['doc_file'];
		
		//digital sign checking for pw
		if($fid_18 != '') {
			$chk = isStringInFile($fid_18, 'adbe.pkcs7.detached');
			if($chk != 1)
			{
				form_set_error('18', 'Form 18 PDF selected for Upload is not digitally signed!!! Please remove and upload again!!!');
			}
		}*/
}

function form18_upload_submit($form, &$form_state){
	
	global $user;
	$uid = $user->uid;
	$val   							= 	$form_state['input'];
	
	$commands   					= 	array();
	
	$form_id						= 	encryption_decryption_fun('decrypt',$val['formid_hidden']);	
	$reference_no					= 	encryption_decryption_fun('decrypt',$val['reference_no_hidden']);	
		$factorytypeid    = encryption_decryption_fun('decrypt', $val['factorytypeid_hidden']);
		$serviceid    = encryption_decryption_fun('decrypt', $val['serviceid_hidden']);

	$file_caf = file_load($form_state['values']['doc_file']);

		if($file_caf != '') 		
		{
			$document_name = "FORM-18";
			$document_listid =  fun_fetch_document_listid($document_name);//print_r($document_listid);die;

			$path_file_caf = pathinfo($file_caf->filename);
			$new_filename_file_caf = 'Form18_'.date('Y').'_'.$form_id.'_'.time().'.'.$path_file_caf['extension'];

			$file_caf->filename = $new_filename_file_caf; 
			file_save($file_caf);
	
			$filename_caf_arr     = explode("/", $file_caf->uri);
			$filepathSave_caf 	= file_get_contents(escapefile_url('public://upload/upload_pdf/'.$filename_caf_arr[4]));
	
			$content_caf		= base64_encode($filepathSave_caf);
	
			$doc_content_arr_caf = array(
				'upload_doc_content' => $content_caf,
			);
	
			db_insert('fa_caf_upload_doc_content')->fields($doc_content_arr_caf)->execute();
				
			$query_caf = db_select('fa_caf_upload_doc_content','cudc');
			$query_caf->addExpression('MAX(id)','max_id');
			$result_caf = $query_caf->execute();
			$data_caf = $result_caf->fetchObject();

			$upload_doc_arr_caf = array(
				'application_id' => $form_id,
				'application_reference_no' => $reference_no,
				'file_name' => $new_filename_file_caf,
				'factory_typeid' => $factorytypeid,
				'service_id' => $serviceid,
				'upload_doc_content_id' => $data_caf->max_id,
				'upload_doc_type' => 'FORM18',
				'created_by'	=> $uid,
				'created_date' => date('Y-m-d h:i:s'),
				'doc_master_id'	=> $document_listid,
				);
			db_insert('fa_caf_upload_all_doc')->fields($upload_doc_arr_caf)->execute();

				$case_identification_number = created_identification($reference_no,$serviceid);

				$notice_accident_update = 	array(/*'upload_status' => 1,'uploaded_pdf' => $file_manage_id,*/'notice_status' => 'RC','case_identification_number'  => $case_identification_number,);	
	
			  //---------------- NOTICE ACCIDENT TABLE UPDATE -------------------
				
				$queryapp 		 =	db_update('fa_form18_notice_accident');
				$queryapp		 ->	fields($notice_accident_update);
				$queryapp		 ->	condition('id',$form_id,'=');
				$queryapp	     ->	condition('factory_typeid',$factorytypeid,'=');
				$queryapp		 ->	condition('reference_number',$reference_no,'=');
				$queryapp		 ->	condition('service_id',$serviceid,'=');
				$queryapp		 ->	execute();
				
			drupal_set_message('Application saved & Pdf uploaded successfully!!!');
			drupal_goto('applicant/form18-list');

		}else{
			form_set_error('caf', 'Please Selct Your Application!!!');
		}
		
} 