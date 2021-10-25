<?php
	
	function annual_return_pdf_upload($form, &$form_state, $annual_returnID = '', $factoryID = '') {
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
		
		
		if(empty($application_status) || $application_status == 'U'){
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
			'#markup' => t('<div class="cus-page-outer-view"><div class="content"><center><h3><b>Annual Return PDF Upload</b></h3></center><hr>'),
		);
	
		$form['#attributes']['class'][] = 'custom-form-main';
		
		$form['annual_return_upload_info'] 	= array(
			'#prefix' 					=> '<div class="" style="overflow:hidden;"><b>STEP #1</b>&nbsp;&nbsp; Download PDF for Digital Signature <br><br>
											<b>STEP #2</b> <span class=""> &nbsp; Upload Pdf with DSC</span><br><br>',
			'#suffix' 					=> '</div>',
		);
		
		
		//payment of wages
		if($get_factory_info->payment_wages_flag == 1 && $get_wages_paid_include_deduction->annual_return_id != NULL && $get_disbursement_fine_funds->annual_return_id != NULL) {
			
			$pw_pdf_link	= l('<i class="fa fa-download" aria-hidden="true"></i> Download Payment of Wages Rules Pdf', 'applicant/payment_of_wages_pdf/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array(/*'target' => '_blank'*/ 'download' => 'download', 'title' => 'Download PW PDF','class'=>array('btn btn-primary pull-left'))));
		
			$form['annual_return_pw_upload'] 	= array(
				'#type' 					=> 	'fieldset',
				'#title' 					=> 	t('Upload Payment of Wages Rules PDF'),
				'#collapsible' 				=> 	TRUE, //Upload Pdf with DSCm  Added
				'#collapsed' 				=>  FALSE,  // Added
			);
				   
			$form['annual_return_pw_upload']['pw_pdf_download_section'] = array(
				'#prefix' 					=> '<div class="row"><div class="col-md-12 col-xs-12"><label class="select label-block">'.$pw_pdf_link.'<br><br>',
				'#suffix' 					=> '</label></div>',
			);
			 
			$form['annual_return_pw_upload']['payment_wages_file'] = array(
			   '#type' 						=> 'managed_file',
			   '#title' 					=> t('1. Upload Payment of Wages Rules PDF File'),
			   '#description' 				=> t('<b>Allowed Extension: pdf<br>Maximum File Size: 2 MB</b>'),
			   '#attributes' 				=> array('class'=>array('form-control browse-height-auto'),'placeholder'=>'Upload documents'),
			   '#required' 					=> TRUE,
			   '#upload_validators' 		=> array('file_validate_extensions' => array("pdf"),),
			   '#upload_location' 			=> 'public://upload/upload_pdf/',
			   '#prefix' 					=> '<div id="replace_payment_wages_file"><div class="col-md-7 col-xs-7"><label class="select label-block">',
			   '#suffix' 					=> '</label></div></div>',
			   '#process'					=> array('annual_return_upload_element_process'),
			   '#file_check' 				=> TRUE,
			);
			
			if(isset($form) > 0 && $form['annual_return_pw_upload']['payment_wages_file']["#type"] == "managed_file") {
				$form['annual_return_pw_upload']['payment_wages_file']["#upload_validators"]["file_upload_validation"] = array($form['annual_return_pw_upload']['payment_wages_file']["#upload_validators"]["file_validate_extensions"][0]);
			}
			
		}
		
		
		//factories rules
		if($get_factory_info->factories_act_flag == 1 && $get_factory_act_all_data->ar_id != NULL) {
			
			$fa_act_pdf_link	= l('<i class="fa fa-download" aria-hidden="true"></i> Download Factories Rules Pdf', 'applicant/factories_act_pdf/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array(/*'target' => '_blank'*/ 'download' => 'download', 'title' => 'Download Fact Act PDF','class'=>array('btn btn-primary pull-left'))));
		
			$form['annual_return_fact_act_upload'] 	= array(
				'#type' 					=> 	'fieldset',
				'#title' 					=> 	t('Upload Factories Rules PDF'),
				'#collapsible' 				=> 	TRUE, //Upload Pdf with DSCm  Added
				'#collapsed' 				=>  FALSE,  // Added
			);
				   
			$form['annual_return_fact_act_upload']['fact_act_pdf_download_section'] = array(
				'#prefix' 					=> '<div class="row"><div class="col-md-12 col-xs-12"><label class="select label-block">'.$fa_act_pdf_link.'<br><br>',
				'#suffix' 					=> '</label></div>',
			);
			
			$form['annual_return_fact_act_upload']['factories_act_file'] = array(
			   '#type' 						=> 'managed_file',
			   '#title' 					=> t('2. Upload Factories Rules PDF File'),
			   '#description' 				=> t('<b>Allowed Extension: pdf<br>Maximum File Size: 2 MB</b>'),
			   '#attributes' 				=> array('class'=>array('form-control browse-height-auto'),'placeholder'=>'Upload documents'),
			   '#required' 					=> TRUE,
			   '#upload_validators' 		=> array('file_validate_extensions' => array("pdf"),),
			   '#upload_location' 			=> 'public://upload/upload_pdf/',
			   '#prefix' 					=> '<div id="replace_factories_act_file"><div class="col-md-7 col-xs-7"><label class="select label-block">',
			   '#suffix' 					=> '</label></div></div>',
			   '#process'					=> array('annual_return_upload_element_process'),
			   '#file_check' 				=> TRUE,		
			);
			
			if(isset($form) > 0 && $form['annual_return_fact_act_upload']['factories_act_file']["#type"] == "managed_file") {
				$form['annual_return_fact_act_upload']['factories_act_file']["#upload_validators"]["file_upload_validation"] = array($form['annual_return_fact_act_upload']['factories_act_file']["#upload_validators"]["file_validate_extensions"][0]);
			}
			
		}
		
		
		//maternity benefit
		if($get_factory_info->maternity_benefit_flag == 1 && $get_maternity_benefit_all_data->ar_id != NULL) {
			
			$mb_pdf_link	= l('<i class="fa fa-download" aria-hidden="true"></i> Download Maternity Benefit Rules Pdf', 'applicant/maternity_benefit_pdf/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array(/*'target' => '_blank'*/ 'download' => 'download', 'title' => 'Download MB PDF','class'=>array('btn btn-primary pull-left'))));
		
			$form['annual_return_mb_upload'] 	= array(
				'#type' 					=> 	'fieldset',
				'#title' 					=> 	t('Upload Maternity Benefit Rules PDF'),
				'#collapsible' 				=> 	TRUE, //Upload Pdf with DSCm  Added
				'#collapsed' 				=>  FALSE,  // Added
			);
				   
			$form['annual_return_mb_upload']['mb_pdf_download_section'] = array(
				'#prefix' 					=> '<div class="row"><div class="col-md-12 col-xs-12"><label class="select label-block">'.$mb_pdf_link.'<br><br>',
				'#suffix' 					=> '</label></div>',
			);
			
			$form['annual_return_mb_upload']['maternity_benefit_file'] = array(
			   '#type' 						=> 'managed_file',
			   '#title' 					=> t('3. Upload Maternity Benefit Rules PDF File'),
			   '#description' 				=> t('<b>Allowed Extension: pdf<br>Maximum File Size: 2 MB</b>'),
			   '#attributes' 				=> array('class'=>array('form-control browse-height-auto'),'placeholder'=>'Upload documents'),
			   '#required' 					=> TRUE,
			   '#upload_validators' 		=> array('file_validate_extensions' => array("pdf"),),
			   '#upload_location' 			=> 'public://upload/upload_pdf/',
			   '#prefix' 					=> '<div id="replace_maternity_benefit_file"><div class="col-md-7 col-xs-7"><label class="select label-block">',
			   '#suffix' 					=> '</label></div></div></div>'	,
			   '#process'					=> array('annual_return_upload_element_process'),
			   '#file_check' 				=> TRUE,	
			);
			
			if(isset($form) > 0 && $form['annual_return_mb_upload']['maternity_benefit_file']["#type"] == "managed_file") {
				$form['annual_return_mb_upload']['maternity_benefit_file']["#upload_validators"]["file_upload_validation"] = array($form['annual_return_mb_upload']['maternity_benefit_file']["#upload_validators"]["file_validate_extensions"][0]);
			}
			
		}
		
		$form['submit'] = array(
			'#prefix' 					=> '',
			'#suffix' 					=> '',
			'#attributes' 				=> array(
			'class' 					=> array( 'btn btn-dark' )),
			'#type' 					=> 'submit',
			'#value' 					=> 'Upload'
		);
		
		$form['footer'] = array(
			'#markup' => t('</div></div>'),
		);
		
		return $form;
	
	}
	
	function annual_return_upload_element_process($element, &$form_state, $form) {
		$element = file_managed_file_process($element, $form_state, $form);
		$element['upload_button']['#access'] = FALSE;
		//$element['remove_button']['#access'] = FALSE;
		return $element;
	}
	
	function annual_return_pdf_upload_validate($form, &$form_state) {
		
		/*$file_pw = file_load($form['annual_return_pw_upload']['payment_wages_file']['#value']['fid']);
		$file_fact_act = file_load($form['annual_return_fact_act_upload']['factories_act_file']['#value']['fid']);
		$file_mb = file_load($form['annual_return_mb_upload']['maternity_benefit_file']['#value']['fid']);*/
		
		$file_pw = file_load($form_state['values']['payment_wages_file']);
		$file_fact_act = file_load($form_state['values']['factories_act_file']);
		$file_mb = file_load($form_state['values']['maternity_benefit_file']);
		
		
		if($file_pw->filesize > 2097152) {
			form_set_error('file_pw_size', 'The file '.$file_pw->filename.' could not be uploaded, because it exceeds 2 MB, the maximum allowed size for uploads.');	
		}
		if($file_fact_act->filesize > 2097152) {
			form_set_error('file_fact_act_size', 'The file '.$file_fact_act->filename.' could not be uploaded, because it exceeds 2 MB, the maximum allowed size for uploads.');	
		}
		if($file_mb->filesize > 2097152) {
			form_set_error('file_mb_size', 'The file '.$file_mb->filename.' could not be uploaded, because it exceeds 2 MB, the maximum allowed size for uploads.');	
		}
		
		$fid_pw = $form_state['values']['payment_wages_file'];
		$fid_fact_act = $form_state['values']['factories_act_file'];
		$fid_mb = $form_state['values']['maternity_benefit_file'];

		//digital sign checking for pw
		if($fid_pw != '') {
			$chk = isStringInFile($fid_pw, 'adbe.pkcs7.detached');
			if($chk != 1)
			{
				form_set_error('pw', 'Payment of Wages Rules PDF selected for Upload is not digitally signed!!! Please remove and upload again!!!');
			}
		}
		
		//digital sign checking for fact act
		if($fid_fact_act != '') {
			$chk = isStringInFile($fid_fact_act, 'adbe.pkcs7.detached');
			if($chk != 1)
			{
				form_set_error('fact_act', 'Factories Rules PDF selected for Upload is not digitally signed!!! Please remove and upload again!!!');
			}
		}
		
		//digital sign checking for mb
		if($fid_mb != '') {
			$chk = isStringInFile($fid_mb, 'adbe.pkcs7.detached');
			if($chk != 1)
			{
				form_set_error('mb', 'Maternity Benefit Rules PDF selected for Upload is not digitally signed!!! Please remove and upload again!!!');
			}
		}
		
	}
	
	function annual_return_pdf_upload_submit($form, &$form_state) {
		//echo '<pre>'; print_r($form_state); die();
		global $base_root, $base_path, $user;
		
		$uid = $user->uid;
		
		$file_pw = file_load($form_state['values']['payment_wages_file']);
		$file_fact_act = file_load($form_state['values']['factories_act_file']);
		$file_mb = file_load($form_state['values']['maternity_benefit_file']);
		
		$fid_pw = $form_state['values']['payment_wages_file'];
		$fid_fact_act = $form_state['values']['factories_act_file'];
		$fid_mb = $form_state['values']['maternity_benefit_file'];
		
		$annual_return_ID = $form_state['values']['annual_return_id'];
		
		$get_factory_info = get_annual_return_factory_information($annual_return_ID);
		
		
		//for payment of wages
		if($fid_pw != '') {
			
			//code for filename change
				$path_parts_pw = pathinfo($file_pw->filename);
				
				//code for making new filename
				$new_filename_pw = 'Payment_of_Wages_'.$annual_return_ID.'_'.$get_factory_info->annual_return_year.'_'.rand(1, 100000).'.'.$path_parts_pw['extension'];
				//end
				
				$file_pw->filename = $new_filename_pw;
				
				file_save($file_pw);
			//code end
			
			//code for fetch id from table fa_documents_masterlist which will be inserted as doc_master_id in table fa_caf_upload_all_doc
				
				$document_name_pw = "Payment of Wages Rules(For Annual Return)";
				$document_listid_pw = fun_fetch_document_listid($document_name_pw);
				
			//end
			
			$filename_pw_arr = explode("/", $file_pw->uri);
		
			$filepathSave_pw 	= file_get_contents(escapefile_url('public://upload/upload_pdf/'.$filename_pw_arr[4]));
			$content_pw 		= base64_encode($filepathSave_pw);
			
			$pw_doc_content_arr = array(
				'upload_doc_content' => $content_pw,
				
			);
			
			$upd_doc_content_id_pw = db_insert('fa_caf_upload_doc_content')->fields($pw_doc_content_arr)->execute();
			
			/*$query_pw = db_select('fa_caf_upload_doc_content','cudc');
			$query_pw->addExpression('MAX(id)','max_id');
			$result_pw = $query_pw->execute();
			$data_pw = $result_pw->fetchObject();*/
			
			$pw_caf_upload_doc_arr = array(
				'application_id' 			=> $annual_return_ID,
				'application_reference_no' 	=> $get_factory_info->reference_number,
				'factory_typeid' 			=> $get_factory_info->factory_typeid,
				'service_id' 				=> $get_factory_info->service_id,
				'file_name' 				=> $new_filename_pw,
				//'upload_doc_content_id' 	=> $data_pw->max_id,
				'upload_doc_content_id' 	=> $upd_doc_content_id_pw,
				'upload_doc_type' 			=> 'pw',
				'created_by' 				=> $uid,
				'created_date'		   		=> date('Y-m-d H:i:s'),
				'doc_master_id'				=> $document_listid_pw['id']
			);
			
			db_insert('fa_caf_upload_all_doc')->fields($pw_caf_upload_doc_arr)->execute();
			
		}
	
		//for fact act
		if($fid_fact_act != '') {
			
			//code for filename change
				$path_parts_fact_act = pathinfo($file_fact_act->filename);
				
				//code for making new filename
				$new_filename_fact_act = 'Factories_Rules_'.$annual_return_ID.'_'.$get_factory_info->annual_return_year.'_'.rand(1, 100000).'.'.$path_parts_fact_act['extension'];
				//end
				
				$file_fact_act->filename = $new_filename_fact_act;
				
				file_save($file_fact_act);
			//code end
			
			//code for fetch id from table fa_documents_masterlist which will be inserted as doc_master_id in table fa_caf_upload_all_doc
				
				$document_name_fact_act = "Factories Rules(For Annual Return)";
				$document_listid_fact_act = fun_fetch_document_listid($document_name_fact_act);
				
			//end
			
			$filename_fact_act_arr = explode("/", $file_fact_act->uri);
		
			$filepathSave_fact_act 	= file_get_contents(escapefile_url('public://upload/upload_pdf/'.$filename_fact_act_arr[4]));
			$content_fact_act 		= base64_encode($filepathSave_fact_act);
			
			$fact_act_doc_content_arr = array(
				'upload_doc_content' => $content_fact_act,
				
			);
			
			$upd_doc_content_id_fact_act = db_insert('fa_caf_upload_doc_content')->fields($fact_act_doc_content_arr)->execute();
			
			/*$query_fact_act = db_select('fa_caf_upload_doc_content','cudc');
			$query_fact_act->addExpression('MAX(id)','max_id');
			$result_fact_act = $query_fact_act->execute();
			$data_fact_act = $result_fact_act->fetchObject();*/
			
			$fact_act_caf_upload_doc_arr = array(
				'application_id' 			=> $annual_return_ID,
				'application_reference_no' 	=> $get_factory_info->reference_number,
				'factory_typeid' 			=> $get_factory_info->factory_typeid,
				'service_id' 				=> $get_factory_info->service_id,
				'file_name' 				=> $new_filename_fact_act,
				//'upload_doc_content_id' 	=> $data_fact_act->max_id,
				'upload_doc_content_id' 	=> $upd_doc_content_id_fact_act,
				'upload_doc_type' 			=> 'fact_act',
				'created_by' 				=> $uid,
				'created_date'		   		=> date('Y-m-d H:i:s'),
				'doc_master_id'				=> $document_listid_fact_act['id']
			);
			
			db_insert('fa_caf_upload_all_doc')->fields($fact_act_caf_upload_doc_arr)->execute();	
			
		}
		
		//for mb
		if($fid_mb != '') {
			
			//code for filename change
				$path_parts_mb = pathinfo($file_mb->filename);
				
				//code for making new filename
				$new_filename_mb = 'Maternity_Benefit_'.$annual_return_ID.'_'.$get_factory_info->annual_return_year.'_'.rand(1, 100000).'.'.$path_parts_mb['extension'];
				//end
				
				$file_mb->filename = $new_filename_mb;
				
				file_save($file_mb);
			//code end
			
			//code for fetch id from table fa_documents_masterlist which will be inserted as doc_master_id in table fa_caf_upload_all_doc
				
				$document_name_mb = "Maternity Benefit Rules(For Annual Return)";
				$document_listid_mb = fun_fetch_document_listid($document_name_mb);
				
			//end
			
			$filename_mb_arr = explode("/", $file_mb->uri);
		
			$filepathSave_mb 	= file_get_contents(escapefile_url('public://upload/upload_pdf/'.$filename_mb_arr[4]));
			$content_mb 		= base64_encode($filepathSave_mb);
			
			$mb_doc_content_arr = array(
				'upload_doc_content' => $content_mb,
				
			);
			
			$upd_doc_content_id_mb = db_insert('fa_caf_upload_doc_content')->fields($mb_doc_content_arr)->execute();
			
			/*$query_mb = db_select('fa_caf_upload_doc_content','cudc');
			$query_mb->addExpression('MAX(id)','max_id');
			$result_mb = $query_mb->execute();
			$data_mb = $result_mb->fetchObject();*/
			
			$mb_caf_upload_doc_arr = array(
				'application_id' 			=> $annual_return_ID,
				'application_reference_no' 	=> $get_factory_info->reference_number,
				'factory_typeid' 			=> $get_factory_info->factory_typeid,
				'service_id' 				=> $get_factory_info->service_id,
				'file_name' 				=> $new_filename_mb,
				//'upload_doc_content_id' 	=> $data_mb->max_id,
				'upload_doc_content_id' 	=> $upd_doc_content_id_mb,
				'upload_doc_type' 			=> 'mb',
				'created_by' 				=> $uid,
				'created_date'		   		=> date('Y-m-d H:i:s'),
				'doc_master_id'				=> $document_listid_mb['id']
			);
			
			db_insert('fa_caf_upload_all_doc')->fields($mb_caf_upload_doc_arr)->execute();	
			
		}
		
	//code for annual return application no generate
	
		$result  = db_query("select annual_return_app_no from {fa_annual_return} WHERE service_id = :service_id AND 
							annual_return_app_no IS NOT :annual_return_app_no ORDER BY id DESC LIMIT 1", array(':service_id' => $get_factory_info->service_id, 
							':annual_return_app_no' => NULL));
		
		$data = $result->fetchObject();										
		$max_annual_return_app_no = $data->annual_return_app_no;
		
		if($max_annual_return_app_no == NULL || empty($max_annual_return_app_no)){
			
			$annual_return_app_no = 'AR'.date('dmY').'0001';
			
		}else{
			
			$max_ar_appno = substr($max_annual_return_app_no,9); echo "<br>";
			
			$next_no = $max_ar_appno+1; 
			
			$ar_appno_first     =   'AR'.date('dmY');
			$ar_appno_second    =   str_pad($next_no, 4, "0", STR_PAD_LEFT);
			
			$annual_return_app_no = $ar_appno_first.$ar_appno_second;
			
		}	
	
	//end
		
		db_update('fa_annual_return')
		->fields(array(
			'full_application_status' 	=> 'U',
			'modification_date'	   	  	=> date('Y-m-d H:i:s'),
			'annual_return_app_no'		=> $annual_return_app_no,
		))
		->condition('id', $annual_return_ID, '=')
		->execute();
		
		drupal_set_message(t('All Documents uploaded and Your Application submitted successfully!!! Your Application No. - '.$annual_return_app_no.'.'));
		drupal_goto('applicant/annual-return-list') ;
	}