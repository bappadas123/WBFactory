<script type="text/javascript">
function DownloadAndRedirect(servid,factid,appid,refid)
{  
   var RedirectURL = window.location.origin+window.location.pathname+"/applicant/application_upload_extn/"+servid+"/"+factid+"/"+appid+"/"+refid;

   var RedirectPauseSeconds = 7;
   
   setTimeout("DoTheRedirect('"+RedirectURL+"')",parseInt(RedirectPauseSeconds*1000));
}
function DoTheRedirect(url) { window.location=url; }
</script>

<?php

function application_upload_extn($form, &$form_state, $serviceid ,$factorytype,$applicationid ,$referenceno){
	
	global $base_root,$base_path,$user,$_SESSION;
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factorytype);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$reference_no 	    = encryption_decryption_fun('decrypt',$referenceno);

   	$get_fa_cafa           			= 	get_fa_cafa($application_id);
	$plan_approve_status      		= 	$get_fa_cafa['plan_approve_status'];
	$identification_number			= 	$get_fa_cafa['plan_approve_identification_number'];
	$is_chemical                    = 	$get_fa_cafa['is_chemical'];

	$form = array();
	$form['#attributes'] 	= array('enctype' => "multipart/form-data");

	$form['serviceid_hidden'] 		= array(
			 '#type' 				=> 'hidden',
			 '#default_value' 		=> $serviceid
	);	
	$form['factorytype_hidden'] 	= array(
			 '#type' 				=> 'hidden',
			 '#default_value' 		=> $factorytype
	);	
	$form['applicationid_hidden'] 	= array(
			 '#type' 				=> 'hidden',
			 '#default_value' 		=> $applicationid
	);	
	$form['reference_no_hidden'] 	= array(
			 '#type' 				=> 'hidden',
			 '#default_value' 		=> $referenceno,
	);		  
	$form['plan_approve_status_hidden']       = array(
        '#type'          			=> 'hidden',
        '#default_value' 			=> encryption_decryption_fun('encrypt', $plan_approve_status)
    );
	$form['identification_number_hidden']       = array(
        '#type'          			=> 'hidden',
        '#default_value' 			=> encryption_decryption_fun('encrypt', $identification_number)
    );
	$form['is_chemical_hidden']       = array(
        '#type'          			=> 'hidden',
        '#default_value' 			=> encryption_decryption_fun('encrypt', $is_chemical)
    );
	
		$applicationID = encryption_decryption_fun('encrypt',$application_id);
		$referenceNO = encryption_decryption_fun('encrypt',$reference_no);
		
		 $pdf_link	= l('<i class="fa fa-download" aria-hidden="true"></i> Download Application Form', 'download-pdf-new-plan/'.$applicationID.'/'.$referenceNO.'/'.$serviceid.'/'.$factorytype.'/'.encryption_decryption_fun('encrypt',$plan_approve_status), array('html' => TRUE,'attributes'=>array('onClick' => 'return DownloadAndRedirect("'.$serviceid.'","'.$factorytype.'","'.$applicationID.'","'.$referenceNO.'");','title' => 'View','class'=>array('btn btn-primary pull-right'))));//,'target' => 'blank'
	
	if(($plan_approve_status == 'F' || $plan_approve_status == 'RS') && ($get_fa_cafa['download_status']==0)){
		
	$form['header'] = array(
		'#markup' 					=> t('<div class="cus-page-outer-view"><div class="content"><center><h3><b>Application for Approval of Plan</b></h3><p style="overflow:hidden;">'.$pdf_link.' <span class="pull-left line-height-34"><b>STEP #1</b> &nbsp;&nbsp;</span><span class="blink pull-left line-height-34"> Download application for Digital Signature <i class="fa fa-hand-o-right"></i> &nbsp; </span></p></center><hr><b>STEP #2</b> &nbsp;&nbsp; Upload Pdf with DSC <br><br>[<span style="color: green"><b>NOTE : </b> After downloading the application Pdf, <b style="color:#000;">STEP #2 </b>will be activated.<br> To complete the Plan Approval process please do the signature and upload the pdf.]</span>'),
	);
	}// else { $pdf_link = ''; }
	
	if($get_fa_cafa['download_status']==1){
		
	$form['header'] = array(
		'#markup' 					=> t('<div class="cus-page-outer-view"><div class="content"><center><h3><b>Application for Approval of Plan</b></h3></center><hr>'),
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
	);*/
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
        'class' 					=> array( 'btn btn-dark' )),
        '#type' 					=> 'submit',
        '#value' 					=> 'Submit'
    								);
	}
	$form['note'] = array(
		'#markup' 					=> t('<br>[<span style="color: green"><b>NOTE : </b> After downloading the application Pdf, <b style="color:#000;">STEP #2 </b>will be activated.<br> To complete the Plan Approval process please do the signature and upload the pdf.]</span>'),
	);
	
 return $form;
	
        
   }
   
function application_upload_extn_validate($form, &$form_state) {
	$file_caf_application = file_load($form_state['values']['doc_file']);

	if($file_caf_application->fid != '') {
		$chk = isStringInFile($file_caf_application->fid, 'adbe.pkcs7.detached');
		if($chk != 0)
		{
			form_set_error('caf', 'Common application form for Upload is not digitally signed!!! Please remove and upload again!!!');
		}
	}
}

   
function application_upload_extn_submit($form, &$form_state){
	
	global $user;
	$uid = $user->uid;
	$val   							= 	$form_state['input'];
	
	$commands   					= 	array();
	$current_application_status     =   '';
	
	$factory_type					= 	encryption_decryption_fun('decrypt',$val['factorytype_hidden']);
	$service_id						= 	encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$application_id					= 	encryption_decryption_fun('decrypt',$val['applicationid_hidden']);	
	$reference_no					= 	encryption_decryption_fun('decrypt',$val['reference_no_hidden']);	
	$plan_approve_status 			=   encryption_decryption_fun('decrypt',$val['plan_approve_status_hidden']);
	$identificationnumber           =   encryption_decryption_fun('decrypt',$val['identification_number_hidden']);
	$is_chemical           			=   encryption_decryption_fun('decrypt',$val['is_chemical_hidden']);
	    
		$file_caf = file_load($form_state['values']['doc_file']);

		if($file_caf != '') 		
		{
			$document_name = "CAF (For Extension)";
			$document_list_details =  fun_fetch_document_listid($document_name);//print_r($document_listid);die;

			$path_file_caf = pathinfo($file_caf->filename);
			//$new_filename_file_caf = 'Common_application_form_'.date('Y').'_'.$application_id.'_'.time().'.'.$path_file_caf['extension'];
			$new_filename_file_caf = 'COMMON_APPLICATION_FORM_'.date('d-m-yy').'_'.time().'.'.$path_file_caf['extension'];

			$file_caf->filename = $new_filename_file_caf; 
			file_save($file_caf);
	
			$filename_caf_arr     = explode("/", $file_caf->uri);
			$filepathSave_caf 	= file_get_contents(escapefile_url('public://upload/upload_pdf/'.$filename_caf_arr[4]));
	
			$content_caf		= base64_encode($filepathSave_caf);
	
			$doc_content_arr_caf = array(
				'upload_doc_content' => $content_caf,
			);
	
			$upload_doc_content_id = db_insert('fa_caf_upload_doc_content')->fields($doc_content_arr_caf)->execute();
	
			$upload_doc_arr_caf = array(
				'application_id' => $application_id,
				'application_reference_no' => $reference_no,
				'file_name' => $new_filename_file_caf,
				'factory_typeid' => $factory_type,
				'service_id' => $service_id,
				'upload_doc_content_id' => $upload_doc_content_id,
				'upload_doc_type' => 'CAF',
				'created_by'	=> $uid,
				'created_date' => date('Y-m-d h:i:s'),
				'doc_master_id'	=> $document_list_details['id'],
				'identity_flag' =>$document_list_details['identity_flag']
				);
			db_insert('fa_caf_upload_all_doc')->fields($upload_doc_arr_caf)->execute();
		}else{
			form_set_error('caf', 'Please Selct Your Application!!!');
		}
	       $current_application_status = 'AI'; 
	
	
				if(empty($identificationnumber)){
					$identification_number = created_identification($reference_no,$service_id);
					//$caf_update = 	array('plan_approve_identification_number' => $identification_number,'plan_approve_status' => $current_application_status,'uploaded_pdf' => $file_manage_id);
					$caf_update = 	array('plan_approve_identification_number' => $identification_number,'plan_approve_status' => $current_application_status);	
				}else{
					//if($plan_approve_status == 'RS')
//					{
//						$identification_number = created_identification($reference_no,$service_id);
//						$caf_update = 	array('plan_approve_identification_number' => $identification_number,'plan_approve_status' => $current_application_status,'uploaded_pdf' => $file_manage_id);
//					} else {
						$identification_number = $identificationnumber;
						//$caf_update = 	array('plan_approve_identification_number' => $identification_number,'plan_approve_status' => $current_application_status,'uploaded_pdf' => $file_manage_id);
						$caf_update = 	array('plan_approve_identification_number' => $identification_number,'plan_approve_status' => $current_application_status);	
					//}
				}
				
				//---------------- CAFA TABLE UPDATE -------------------
				//$caf_update 	= 	array('plan_approve_status' => $current_application_status);
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
				
				//----------------OCCUPIER DETAILS TABLE UPDATE-------------------
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
				
				if($is_chemical == 1)
				{			
				$cafa_remarks = array(
					'app_id'   			 => $application_id,
					'remark_by_uid' 	 => $uid,
					'sending_time' 		 => date('Y-m-d h:i:s'),
					'app_reference_no' 	 => $reference_no,
					'plan_status_chem' 		 => 'AICh',
				);	
				db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();
				}
				
				if($plan_approve_status == 'RS')
				{
					drupal_set_message('Your application along with your signature has been successfully Re-uploaded.');
				}
				else {
					drupal_set_message('Your application along with your signature has been successfully uploaded. Application number is '.$identification_number);
				}
				drupal_goto('applicant/application_view_extn/'.$val['serviceid_hidden'].'/'.$val['factorytype_hidden'].'/'.$val['applicationid_hidden'].'/'.$val['reference_no_hidden']) ;
	
	
}   

