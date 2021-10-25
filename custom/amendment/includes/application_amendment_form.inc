<script type="text/javascript">
function DownloadAndRedirect(servid,factid,appid,refid)
{  
   //var RedirectURL = "/demofactories/applicant/uplaod_application_from/"+servid+"/"+factid+"/"+appid+"/"+refid;
   //var RedirectURL = "/factories/applicant/uplaod_application_from/"+servid+"/"+factid+"/"+appid+"/"+refid;
  var RedirectURL = 	window.location.origin+window.location.pathname+"/applicant/upload-amendment-from/"+servid+"/"+factid+"/"+appid+"/"+refid;
  // var RedirectURL = "/wbfactories/applicant/uplaod_application_from/"+servid+"/"+factid+"/"+appid+"/"+refid;

   var RedirectPauseSeconds = 7;
   
   setTimeout("DoTheRedirect('"+RedirectURL+"')",parseInt(RedirectPauseSeconds*1000));
}
function DoTheRedirect(url) { window.location=url; }
</script>

<?php 
function application_amendment_form($form, &$form_state, $applicationid, $referenceno, $serviceid,$factory_typeid) {
 global $base_root, $base_path, $user;
 
 $application_id 	= encryption_decryption_fun('decrypt', $applicationid);
 $service_id 		= encryption_decryption_fun('decrypt',$serviceid);
 $factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
 $reference_no 		= encryption_decryption_fun('decrypt',$referenceno); 
 $get_fa_cafa 				= get_fa_cafa($application_id);

	$application_status		= $get_fa_cafa['application_status'];
	$factory_name			= $get_fa_cafa['factory_name'];
	$reg_identification_number	= $get_fa_cafa['factory_reg_identification_number'];
 	//echo $application_id.'--'.$factory_type_id.'--'.$reference_no.'--'.$service_id ;
 
	$form = array();
	$form['#attributes'] 	= array('enctype' => "multipart/form-data");
	
	$form['serviceid_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $serviceid,
		);
	$form['factorytypeid_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $factory_typeid
			);
	$form['reference_no_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $referenceno		 
		);
	$form['applicationid_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $applicationid
		);	
	$form['reg_identification_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> encryption_decryption_fun('encrypt',$reg_identification_number)
		);	
	$pdf_link_p	= l('<i class="fa fa-download" aria-hidden="true"></i> Download Application Form', 'download-pdf-application/'.$applicationid.'/'.$serviceid.'/'.$referenceno.'/'.$factory_typeid, array('html' => TRUE,'attributes'=>array('onClick' => 'return DownloadAndRedirect("'.$serviceid.'","'.$factory_typeid.'","'.$applicationid.'","'.$referenceno.'");','title' => 'View','class'=>array('btn btn-primary pull-right'))));//,'target' => 'blank'
	
	if($factory_type_id==1){
		$section = 'Section 2m(i)';
		}if($factory_type_id==2){
			$section = 'Section 2m(ii)';
		}if($factory_type_id==3){
			$section = 'Section 85';
		}
		$upload_details = 'Upload the Common Application form <br/>Under the Act. Factory Amendment of license<br/>Name:-'.$factory_name.'('.$section.')';
		if(($application_status == 'P' || $application_status == 'RT'|| $application_status == 'RS' ) && ($get_fa_cafa['download_status']==0)){
			$form['header'] = array(
				'#markup'	=> t('<div class="cus-page-outer-view"><div class="content"><center><h3><b>'.$upload_details.'</b></h3><p style="overflow:hidden;">'.$pdf_link_p.' <span class="pull-left line-height-34"><b>STEP #1</b> &nbsp;&nbsp;</span><span class="blink pull-left line-height-34"> Download application for Digital Signature <i class="fa fa-hand-o-right"></i> &nbsp; </span></p></center><hr><b>STEP #2</b> &nbsp;&nbsp; Upload Pdf with DSC <br><br>[<span style="color: green"><b>NOTE : </b> After downloading the application Pdf, <b style="color:#000;">STEP #2 </b>will be activated.<br> To complete the Amendment process please do the signature and upload the pdf.]</span>'),
			);
		}
		if($factory_type_id==1){
			$section = 'Section 2m(i)';
		}if($factory_type_id==2){
			$section = 'Section 2m(ii)';
		}if($factory_type_id==3){
			$section = 'Section 85';
		}
		$upload_details = 'Upload the Common Application form <br/>Under the Act. Factory Amendment of license<br/>Name:-'.$factory_name.'('.$section.')';

		if(($application_status == 'P' || $application_status == 'RS') && ($get_fa_cafa['download_status']==0)){

			$form['header'] = array(
				'#markup'	=> t('<div class="cus-page-outer-view"><div class="content"><center><h3><b>'.$upload_details.'</b></h3><p style="overflow:hidden;">'.$pdf_link_p.' <span class="pull-left line-height-34"><b>STEP #1</b> &nbsp;&nbsp;</span><span class="blink pull-left line-height-34"> Download application for Digital Signature <i class="fa fa-hand-o-right"></i> &nbsp; </span></p></center><hr><b>STEP #2</b> &nbsp;&nbsp; Upload Pdf with DSC <br><br>[<span style="color: green"><b>NOTE : </b> After downloading the application Pdf, <b style="color:#000;">STEP #2 </b>will be activated.<br> To complete the registration process please do the signature and upload the pdf.]</span>'),
			  );
		}
		if($get_fa_cafa['download_status']==1){
  
			$form['header'] = array(
			  '#markup' => t('<div class="cus-page-outer-view"><div class="content"><center><h3><b>'.$upload_details.'</b></h3></center><hr>'),
			);
			
			$form['#attributes']['class'][] = 'custom-form-main';
			$form['factory_part_upload'] 	= array(
			  '#type' 			=> 	'fieldset',
			  '#title' 			=> 	t('Upload document'),
			  '#collapsible' 	=> 	TRUE, //Upload Pdf with DSCm  Added
			  '#collapsed' 		=>  FALSE,  // Added
			  '#prefix' 		=> '<div class="" style="overflow:hidden;"><b>STEP #1</b>&nbsp;&nbsp; Download application for Digital Signature '.$pdf_link_p.'<br><br><b>STEP #2</b> <span class="blink"> &nbsp; Upload Pdf with DSC</span><br><br>',
			  '#suffix' 		=> '',
			
			);
				 
			$form['factory_part_upload']['start_upload_section'] = array(
			  '#prefix' 		=> '<div class="row">',
			  '#suffix' 		=> '',
			);  
			$form['factory_part_upload']['application_pdf_upload'] = array(
			 '#type' 				=> 'managed_file',
			 '#title' 				=> t('(PDF only, Max size 5MB)'),
			 '#attributes' 			=> array('class'=>array('form-control browse-height-auto'),'placeholder'=>'Upload documents'),
			 '#required' 			=> TRUE,
			'#upload_validators' 	=> array('file_validate_extensions' => array('pdf'), 'file_validate_size' => array(50*1024*1024)),
			'#upload_location' 		=> 'public://upload/upload_pdf/',
			'#process' 				=> array('import_my_file_element_process'),
			 '#prefix' 				=> '<div id="replace_div_file"><div class="col-md-4">',
			 '#suffix' 				=> '</div></div>'	
			);
			
			$form['submit'] = array(
			  '#prefix' 					=> '',
			  '#suffix' 					=> '</div></div>',
			  '#attributes' 				=> array(
			  'class' 					=> array( 'btn btn-success' )),
			  '#type' 					=> 'submit',
			  '#value' 					=> 'Final Submit'
			);
		}
		if($get_fa_cafa['download_status']==1){
			$form['note'] = array(
				'#markup' 		=> t('<br>[<span style="color: green"><b>NOTE : </b> After downloading the application Pdf, <b style="color:#000;">STEP #2 </b>will be activated.<br> To complete the amendment process please do the signature and upload the pdf.]</span>'),
			);
		}


	return $form;

}

function application_amendment_form_validate($form, &$form_state) {

	$file_caf_application = file_load($form_state['values']['application_pdf_upload']);


	if($file_caf_application->fid != '') {
		$chk = isStringInFile($file_caf_application->fid, 'adbe.pkcs7.detached');
		if($chk != 0)
		{
			form_set_error('caf', 'Common application form for Upload is not digitally signed!!! Please remove and upload again!!!');
		}
	}

}

function application_amendment_form_submit($form, &$form_state){
	
	global $user;
	$val   						    =  $form_state['values'];
	$uid 			    			=  $user->uid;
	$service_id						=  encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$factory_type_id				=  encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$application_id 				=  encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$application_reference_no		=  encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
 	$reg_identification				=  encryption_decryption_fun('decrypt',$val['reg_identification_hidden']);	
	
	$renewal_dim_appoved = db_query("SELECT renewal_dim_appoved  FROM {fa_cafa} WHERE id = '".$application_id."' AND service_id = '".$service_id."' AND factory_typeid = '".$factory_type_id."' AND reference_number = '".$application_reference_no."'")->fetchObject()->renewal_dim_appoved;
	
	if($service_id==2){
		$registration_application = create_registration_application($service_id);
	}elseif($service_id==3){
		$registration_application = $reg_identification;
		}
	
	$application_pdf 				=  file_load($val['application_pdf_upload']);
	if($application_pdf != "" ){
		$document_name = "CAF(For Amendment of License)";
		$document_listid =  fun_fetch_document_listid($document_name);

		$path_caf_form = pathinfo($application_pdf->filename);
		$new_filename_caf = 'Common_application_form_'.date('Y').'_'.$application_id.'_'.time().'.'.$path_caf_form['extension'];
		$application_pdf->filename = $new_filename_caf;
		file_save($application_pdf);

		$filename_caf_arr = explode("/", $application_pdf->uri);
		$filepathSave_caf 	= file_get_contents(escapefile_url('public://upload/upload_pdf/'.$filename_caf_arr[4]));

		$content_caf		= base64_encode($filepathSave_caf);

		$caf_doc_content_arr = array(
			'upload_doc_content' => $content_caf,
		);

		db_insert('fa_caf_upload_doc_content')->fields($caf_doc_content_arr)->execute();
		$query_caf = db_select('fa_caf_upload_doc_content','cudc');
		$query_caf->addExpression('MAX(id)','max_id');
		$result_caf = $query_caf->execute();
		$data_caf = $result_caf->fetchObject();

		$caf_upload_doc_arr = array(
			'application_id' => $application_id,
			'application_reference_no' => $application_reference_no,
			'file_name' => $new_filename_caf,
			'factory_typeid' => $factory_type_id,
			'service_id' => $service_id,
			'upload_doc_content_id' => $data_caf->max_id,
			'upload_doc_type' => 'CAF',
			'created_by'	=> $uid,
			'created_date' => date('Y-m-d h:i:s'),
			'doc_master_id'					=> $document_listid['id'],
			'identity_flag'					=> $document_listid['identity_flag']
			
			);
			db_insert('fa_caf_upload_all_doc')->fields($caf_upload_doc_arr)->execute();
		}else{
			form_set_error('caf', 'Please Selct Your Application!!!');
		}
		

	if(empty($reg_identification)){
		$registration_application = create_registration_application($service_id); 
	}else{
		$registration_application = $reg_identification;
	}
	
	if($service_id == 3 && $renewal_dim_appoved == 1){
		$status_update = array('application_status'=>'I','created_date'=>date("Y-m-d"),'factory_reg_identification_number'=>$registration_application);
				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		->	fields($status_update);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc		->	execute();
	$ack_link	= l('Acknowledgment', 'registration-acknowledgement-certificate/'.$val['applicationid_hidden'].'/'.$val['reference_no_hidden'].'/'.$val['serviceid_hidden'].'/'.$val['factorytypeid_hidden'], array('html' => TRUE,'target' => '_BLANK','attributes'=>array('title' => 'View', 'class'=>array('button'))));
	 drupal_set_message('Your application is sucessfully submitted . Your application number is:- '.$registration_application. $ack_link); 
	 
		}
		
	elseif($service_id == 3){
		$status_uodate = array('application_status'=>'U','created_date'=>date("Y-m-d"),'factory_reg_identification_number'=>$registration_application);
				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		->	fields($status_uodate);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc		->	execute();
	$ack_link	= l('Acknowledgment', 'registration-acknowledgement-certificate/'.$val['applicationid_hidden'].'/'.$val['reference_no_hidden'].'/'.$val['serviceid_hidden'].'/'.$val['factorytypeid_hidden'], array('html' => TRUE,'target' => '_BLANK','attributes'=>array('title' => 'View', 'class'=>array('button'))));
	 drupal_set_message('Your application is sucessfully submitted . Your application number is:- '.$registration_application. $ack_link); 
		
		}	
		else{
	$status_uodate = array('application_status'=>'U','created_date'=>date("Y-m-d"),'factory_reg_identification_number'=>$registration_application);
				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		->	fields($status_uodate);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc		->	execute();
	$ack_link	= l('Acknowledgment', 'registration-acknowledgement-certificate/'.$val['applicationid_hidden'].'/'.$val['reference_no_hidden'].'/'.$val['serviceid_hidden'].'/'.$val['factorytypeid_hidden'], array('html' => TRUE,'target' => '_BLANK','attributes'=>array('title' => 'View', 'class'=>array('button'))));
	 drupal_set_message('Your application is sucessfully submitted . Your application number is:- '.$registration_application. $ack_link); 
	}
	
	 drupal_goto('applicant-dashboard');
   
}
