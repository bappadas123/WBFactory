<script type="text/javascript">
function DownloadAndRedirect(servid,factid,appid,refid)
{  
   //var RedirectURL = "/demofactories/applicant/uplaod_application_from/"+servid+"/"+factid+"/"+appid+"/"+refid;
   //var RedirectURL = "/factories/applicant/uplaod_application_from/"+servid+"/"+factid+"/"+appid+"/"+refid;
  var RedirectURL = 	window.location.origin+window.location.pathname+"/applicant/upload-changed-application-form/"+servid+"/"+factid+"/"+appid+"/"+refid;
  // var RedirectURL = "/wbfactories/applicant/uplaod_application_from/"+servid+"/"+factid+"/"+appid+"/"+refid;

   var RedirectPauseSeconds = 7;
   
   setTimeout("DoTheRedirect('"+RedirectURL+"')",parseInt(RedirectPauseSeconds*1000));
}
function DoTheRedirect(url) { window.location=url; }
</script>


<?php

function changed_renewal_application_from($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$referenceno) {	
 global $base_root, $base_path, $user;
 $application_id 	= encryption_decryption_fun('decrypt', $applicationid);
 $service_id 		= encryption_decryption_fun('decrypt',$serviceid);
 $factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
 $reference_no 		= encryption_decryption_fun('decrypt',$referenceno);
 $get_fa_cafa 				= get_fa_cafa($application_id);
 $application_status		= $get_fa_cafa['application_status'];
 $reg_identification_number	= $get_fa_cafa['factory_reg_identification_number'];
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
	$pdf_link_p	= l('<i class="fa fa-download" aria-hidden="true"></i> Download Application Form', 'download-pdf-registration/'.$applicationid.'/'.$referenceno.'/'.$serviceid.'/'.$factory_typeid.'/'.encryption_decryption_fun('encrypt',$application_status), array('html' => TRUE,'attributes'=>array('onClick' => 'return DownloadAndRedirect("'.$serviceid.'","'.$factory_typeid.'","'.$applicationid.'","'.$referenceno.'");','title' => 'View','class'=>array('btn btn-primary pull-right'))));//,'target' => 'blank'

	if(($application_status == 'P' || $application_status == 'RS') && ($get_fa_cafa['download_status']==0)){
	 
	   $form['header'] = array(
		 '#markup' 					=> t('<div class="cus-page-outer-view"><div class="content"><center><h3><b>Application for Factory Renewal of license<br/>'.$get_fa_cafa['factory_name'].'</b></h3><p style="overflow:hidden;">'.$pdf_link_p.' <span class="pull-left line-height-34"><b>STEP #1</b> &nbsp;&nbsp;</span><span class="blink pull-left line-height-34"> Download application for Digital Signature <i class="fa fa-hand-o-right"></i> &nbsp; </span></p></center><hr><b>STEP #2</b> &nbsp;&nbsp; Upload Pdf with DSC <br><br>[<span style="color: green"><b>NOTE : </b> After downloading the application Pdf, <b style="color:#000;">STEP #2 </b>will be activated.<br> To complete the Plan Approval process please do the signature and upload the pdf.]</span>'),
	   );
	   }// else { $pdf_link = ''; }
	   
	   if($get_fa_cafa['download_status']==1){
		 
	   $form['header'] = array(
		 '#markup' 					=> t('<div class="cus-page-outer-view"><div class="content"><center><h3><b>Application for Factory Renewal of license<br/>'.$get_fa_cafa['factory_name'].'</b></h3></center><hr>'),
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
	   $form['factory_part_upload']['application_pdf_upload'] = array(
		'#type' 						=> 'managed_file',
		'#title' 					=> t('(PDF only, Max size 5MB)'),
		'#attributes' 				=> array('class'=>array('form-control browse-height-auto'),'placeholder'=>'Upload documents'),
		'#required' 				=> TRUE,
			'#upload_validators' 	 => array('file_validate_extensions' => array('pdf'), 'file_validate_size' => array(50*1024*1024)),
		   '#upload_location' 		 => 'public://upload/application_form/',
		   '#process' 				 => array('import_my_file_element_process'),
		'#prefix' 					=> '<div id="replace_div_file"><div class="col-md-4">',
		'#suffix' 					=> '</div></div>'	
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
	   $form['note'] = array(
		 '#markup' 					=> t('<br>[<span style="color: green"><b>NOTE : </b> After downloading the application Pdf, <b style="color:#000;">STEP #2 </b>will be activated.<br> To complete the Plan Approval process please do the signature and upload the pdf.]</span>'),
	   );
	return $form; 	 
}


function changed_renewal_application_from_submit($form, &$form_state){
	
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
	
	$application_pdf	=  file_load($val['application_pdf_upload']);
	if($application_pdf != "" ){
		$application_pdf->status = FILE_STATUS_PERMANENT;
		file_save($application_pdf);
		$fid	= $application_pdf->fid;
	}
	
	$chk = isStringInFile($application_pdf->fid, 'adbe.pkcs7.detached');
	//die('--->'.$chk); 
	if($chk == 0){
	
	$upload_application =array(
		'filename'=> $application_pdf->filename,
		'file_uri'=> $application_pdf->uri,
		'created_by'=> $application_pdf->uid,
		//'id'=> $fid,	
	);
	$file_manage_id = db_insert('fa_file_managed_custom')->fields($upload_application)->execute();	
	/*if(empty($reg_identification)){
		$registration_application = create_registration_application(); 
	}else{
		$registration_application = $reg_identification;
	}*/
	// if($service_id == 3 && $renewal_dim_appoved == 1){
	// 	$status_update = array('application_status'=>'I','created_date'=>date("Y-m-d"),'factory_reg_identification_number'=>$registration_application,'uploaded_pdf'=>$file_manage_id);
	// 			$queryabc 		 =	db_update('fa_cafa');
	// 			$queryabc		->	fields($status_update);
	// 			$queryabc		->	condition('id',$application_id,'=');
	// 			$queryabc		->	execute();
	// $ack_link	= l('Acknowledgment', 'registration-acknowledgement-certificate/'.$val['applicationid_hidden'].'/'.$val['reference_no_hidden'].'/'.$val['serviceid_hidden'].'/'.$val['factorytypeid_hidden'], array('html' => TRUE,'target' => '_BLANK','attributes'=>array('title' => 'View', 'class'=>array('button'))));
	//  drupal_set_message('Your application is sucessfully submitted . Your application number is:- '.$registration_application. $ack_link); 
	 
	// 	}
	if($service_id == 3){
		$status_uodate = array('application_status'=>'U','created_date'=>date("Y-m-d"),'factory_reg_identification_number'=>$registration_application,'uploaded_pdf'=>$file_manage_id);
				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		->	fields($status_uodate);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc		->	execute();
	$ack_link	= l('Acknowledgment', 'registration-acknowledgement-certificate/'.$val['applicationid_hidden'].'/'.$val['reference_no_hidden'].'/'.$val['serviceid_hidden'].'/'.$val['factorytypeid_hidden'], array('html' => TRUE,'target' => '_BLANK','attributes'=>array('title' => 'View', 'class'=>array('button'))));
	 drupal_set_message('Your application is sucessfully submitted . Your application number is:- '.$registration_application. $ack_link); 
		
		}	
	else{
	$status_uodate = array('application_status'=>'U','created_date'=>date("Y-m-d"),'factory_reg_identification_number'=>$registration_application,'uploaded_pdf'=>$file_manage_id);
				$queryabc 		 =	db_update('fa_cafa');
				$queryabc		->	fields($status_uodate);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc		->	execute();
	$ack_link	= l('Acknowledgment', 'registration-acknowledgement-certificate/'.$val['applicationid_hidden'].'/'.$val['reference_no_hidden'].'/'.$val['serviceid_hidden'].'/'.$val['factorytypeid_hidden'], array('html' => TRUE,'target' => '_BLANK','attributes'=>array('title' => 'View', 'class'=>array('button'))));
	 drupal_set_message('Your application is sucessfully submitted . Your application number is:- '.$registration_application. $ack_link); 
	}
	drupal_goto('applicant-dashboard');
	
	}else{
		drupal_set_message('Please! Upload Digital signed application only.','error');
		drupal_goto('applicant/upload-changed-application-form/'.$val['serviceid_hidden'].'/'.$val['factorytypeid_hidden'].'/'.$val['applicationid_hidden'].'/'.$val['reference_no_hidden']);	
	}
   
}
