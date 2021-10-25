<?php
	
	function annual_return_pdf_download($form, &$form_state, $annual_returnID = '', $factoryID = '') {
		global $user;
		$uid 						= $user->uid;
		
		$annual_return_ID = encryption_decryption_fun('decrypt', $annual_returnID);
		//$factory_type_id = encryption_decryption_fun('decrypt', $factory_typeID);
		$factory_id = encryption_decryption_fun('decrypt', $factoryID);


		$get_factory_info = get_annual_return_factory_information($annual_return_ID);

	//This section only for get factory_typeid for sending to annual-return-common
	
		$factory_typeID = encryption_decryption_fun('encrypt', $get_factory_info->factory_typeid);
	//end
		
		if(empty($annual_return_ID) || /*$factory_id == 0 ||*/ $annual_return_ID == '') {
            drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Factory Information first.</h5>'),'alert alert-danger alert-dismissible');
            drupal_goto('applicant/annual-return-common/'.$annual_returnID.'/'.$factory_typeID.'/'.$factoryID) ;
		}
		
		
		$application_status = $get_factory_info->full_application_status;
		
		$get_all_annual =  ar_common_application_data($annual_return_ID);
		
		$get_wages_paid_include_deduction = get_total_wages_paid_include_deduction($annual_return_ID);
		$get_disbursement_fine_funds = get_disbursement_fine_funds($annual_return_ID);
		$get_factory_act_all_data = get_factory_act_all_data($annual_return_ID);
		$get_maternity_benefit_all_data = get_maternity_benefit_all_data($annual_return_ID);
		
		if($get_all_annual['ar_id'] == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Factory Information first.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/annual-return-common/'.$annual_returnID.'/'.$factory_typeID.'/'.$factoryID) ;	
		}
		
		if($get_wages_paid_include_deduction->annual_return_id == NULL || $get_disbursement_fine_funds->annual_return_id == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/payment-of-wages/'.$annual_returnID.'/'.$factoryID) ;	
		}
		
		if($get_factory_act_all_data->ar_id == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/factories-act-apply/dangerous_operation/'.$annual_returnID.'/'.$factoryID) ;	
		}
		
		if($get_factory_info->maternity_benefit_flag == 1) {
			if($get_maternity_benefit_all_data->ar_id == NULL) {
				drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
				drupal_goto('applicant/maternity-benefit-apply/medical_officer/'.$annual_returnID.'/'.$factoryID) ;	
			}
		}
		
		
		if(empty($application_status) || $application_status == 'In' || $application_status == 'F'){
			  drupal_goto('applicant/annual-return-list') ;
		}
		
		$form = array();
		
		$form['annual_return_id'] = array(
				'#type' 			=> 'hidden',
				'#default_value' 	=> $annual_return_ID,
		);
		
		$form['factory_id'] = array(
				'#type' 			=> 'hidden',
				'#default_value' 	=> $factory_id,
		);
		
		
		$form['header'] = array(
			'#markup' => t('<div class="cus-page-outer-view"><div class="content"><center><h3><b>Annual Return Uploaded PDFs Download</b></h3></center><hr>'),
		);
	
		$form['#attributes']['class'][] = 'custom-form-main';
		
		$service_id = $get_factory_info->service_id;
		
		//payment of wages
		if($get_factory_info->payment_wages_flag == 1 && $get_wages_paid_include_deduction->annual_return_id != NULL && $get_disbursement_fine_funds->annual_return_id != NULL) {
			
			$get_caf_upload_doc = get_caf_upload_doc_details($annual_return_ID, $service_id, 'pw', NULL, NULL);
			
			$pw_up_pdf_link	= l('<i class="fa fa-download" aria-hidden="true"></i> Download Uploaded Payment of Wages Rules Pdf', 'applicant/download_uploaded_pw_doc/'.
								$annual_returnID.'/'.encryption_decryption_fun('encrypt', $service_id).'/'.encryption_decryption_fun('encrypt', 'pw'), array('html' => TRUE, 
								'attributes'=>array(/*'target' => '_blank'*/ 'download' => $get_caf_upload_doc->file_name, 'title' => 'Download Uploaded PW PDF','class'=>array(
								'btn btn-primary pull-left'))));
		
			$form['annual_return_pw_download'] 	= array(
				'#type' 					=> 	'fieldset',
				'#title' 					=> 	t('Download Uploaded Payment of Wages Rules PDF'),
				'#collapsible' 				=> 	TRUE, //Upload Pdf with DSCm  Added
				'#collapsed' 				=>  FALSE,  // Added
			);
				   
			$form['annual_return_pw_download']['uploaded_pw_pdf_download_section'] = array(
				'#prefix' 					=> '<div class="row"><div class="col-md-12 col-xs-12"><label class="select label-block">'.$pw_up_pdf_link.'<br><br>',
				'#suffix' 					=> '</label></div>',
			);
			
		}
		
		//factories rules
		if($get_factory_info->factories_act_flag == 1 && $get_factory_act_all_data->ar_id != NULL) {
			
			$get_caf_upload_doc = get_caf_upload_doc_details($annual_return_ID, $service_id, 'fact_act', NULL, NULL);
			
			$fa_up_act_pdf_link	= l('<i class="fa fa-download" aria-hidden="true"></i> Download Uploaded Factories Rules Pdf', 'applicant/download_uploaded_fact_act_doc/'.
									$annual_returnID.'/'.encryption_decryption_fun('encrypt', $service_id).'/'.encryption_decryption_fun('encrypt', 'fact_act'), array('html' => TRUE
									,'attributes'=>array(/*'target' => '_blank'*/ 'download' => $get_caf_upload_doc->file_name, 'title' => 'Download Uploaded Fact Act PDF',
									'class'=>array('btn btn-primary pull-left'))));
		
			$form['annual_return_fact_act_download'] 	= array(
				'#type' 					=> 	'fieldset',
				'#title' 					=> 	t('Upload Uploaded Factories Rules PDF'),
				'#collapsible' 				=> 	TRUE, //Upload Pdf with DSCm  Added
				'#collapsed' 				=>  FALSE,  // Added
			);
				   
			$form['annual_return_fact_act_download']['uploaded_fact_act_pdf_download_section'] = array(
				'#prefix' 					=> '<div class="row"><div class="col-md-12 col-xs-12"><label class="select label-block">'.$fa_up_act_pdf_link.'<br><br>',
				'#suffix' 					=> '</label></div>',
			);
			
		}
		
		//maternity benefit
		if($get_factory_info->maternity_benefit_flag == 1 && $get_maternity_benefit_all_data->ar_id != NULL) {
			
			$get_caf_upload_doc = get_caf_upload_doc_details($annual_return_ID, $service_id, 'mb', NULL, NULL);
			
			$mb_up_pdf_link	= l('<i class="fa fa-download" aria-hidden="true"></i> Download Uploaded Maternity Benefit Rules Pdf', 'applicant/download_uploaded_mb_doc/'.
								$annual_returnID.'/'.encryption_decryption_fun('encrypt', $service_id).'/'.encryption_decryption_fun('encrypt', 'mb'), array('html' => TRUE,
								'attributes'=>array(/*'target' => '_blank'*/ 'download' => $get_caf_upload_doc->file_name, 'title' => 'Download Uploaded MB PDF','class'=>array(
								'btn btn-primary pull-left'))));
		
			$form['annual_return_mb_download'] 	= array(
				'#type' 					=> 	'fieldset',
				'#title' 					=> 	t('Upload Uploaded Maternity Benefit Rules PDF'),
				'#collapsible' 				=> 	TRUE, //Upload Pdf with DSCm  Added
				'#collapsed' 				=>  FALSE,  // Added
			);
				   
			$form['annual_return_mb_download']['uploaded_mb_pdf_download_section'] = array(
				'#prefix' 					=> '<div class="row"><div class="col-md-12 col-xs-12"><label class="select label-block">'.$mb_up_pdf_link.'<br><br>',
				'#suffix' 					=> '</label></div>',
			);
			
		}
		
		$form['footer'] = array(
			'#markup' => t('</div></div>'),
		);
		
		return $form;
	
	}
	
	function annual_return_pdf_download_validate($form, &$form_state) {
		
	}
	
	function annual_return_pdf_download_submit($form, &$form_state) {
		
	}
	
	
	//functions for download uploaded pdfs
	function download_uploaded_doc($annual_returnID = '', $serviceID = '', $upload_docType = '') {
		
		global $base_root,$base_path,$user;
		$user_id = $user->uid;
		
		$annual_return_ID 	= encryption_decryption_fun('decrypt', $annual_returnID);
		$service_id 		= encryption_decryption_fun('decrypt', $serviceID);
		$upload_doc_type 	= encryption_decryption_fun('decrypt', $upload_docType);
		
		$filepathSave 	= 'sites/default/files/upload/download_pdf/'; // different folder for show uploaded file
		
		//data from the table where filename stored
		$get_caf_upload_doc = get_caf_upload_doc_details($annual_return_ID, $service_id, $upload_doc_type, NULL, NULL);
		
		// data from encrypted data table
		$query 			= db_select('fa_caf_upload_doc_content', 'cudc')->fields('cudc',array())->condition('id', $get_caf_upload_doc->upload_doc_content_id, '=');
		$query_result 	= $query->execute();
		
		if($query_result->rowCount() > 0){
			$data 		= $query_result->fetchObject() ;
			$content_pw	= base64_decode($data->upload_doc_content);
			
			if(!file_exists($filepathSave.$get_caf_upload_doc->file_name)){
				file_put_contents($filepathSave.$get_caf_upload_doc->file_name, $content_pw);	
				drupal_goto('sites/default/files/upload/download_pdf/' . $get_caf_upload_doc->file_name);
				
			}else if(file_exists($filepathSave.$get_caf_upload_doc->file_name)){
				drupal_goto('sites/default/files/upload/download_pdf/' . $get_caf_upload_doc->file_name);
				
			}else{
				drupal_set_message(t('File not found.'));
			}
		}
		
	}