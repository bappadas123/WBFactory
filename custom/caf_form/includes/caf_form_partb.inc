<?php
function caf_form_partb($form, &$form_state,$serviceid,$factory_typeid,$applicationid,$referenceno) {
	global $base_root, $base_path;

/************************************************ Upload Part *****************************************************************/

	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
	$application_id   	= encryption_decryption_fun('decrypt', $applicationid);
	$reference_no 		= encryption_decryption_fun('decrypt', $referenceno);
	
	if(empty($application_id) || $application_id==0 || $application_id == ''){
		  drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Worker Details tab.</h5>'),'alert alert-danger alert-dismissible');
		  drupal_goto('applicant/caf/details-worker-hp/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$referenceno) ;
	}
	
	$check_worker_tab 	= get_worker_tab_check($application_id);
	
	if(empty($check_worker_tab)){
		  //drupal_set_message(('Please! Filled up the general information of Worker Details tab'),'warning');
		 // drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the previous tab.</h5>'),'alert alert-danger alert-dismissible');
		  drupal_goto('applicant/caf/details-worker-hp/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$referenceno) ;
	}else{
		$get_fa_cafa 		= get_fa_cafa($application_id);
		//$reference_no 		= $get_fa_cafa['reference_number'];
		$plan_approve_status 		= $get_fa_cafa['plan_approve_status'];
		if($plan_approve_status == 'F'){
			 drupal_set_message(('You can only display of your application form preview'),'warning');
			  drupal_goto('applicant/caf/application-preview/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$referenceno) ;
		}
	}

	$form = array();
	$form['#attributes'] 	= array('enctype' => "multipart/form-data");
	
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
			 '#default_value' 	=> $referenceno
	);
	$form['plan_approve_status_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> encryption_decryption_fun('encrypt', $plan_approve_status)
	);
	
	$form['document_upload'] = array(
		'#type' 			=> 'vertical_tabs',
		'#prefix' 			=> '<span id="replace_div_file">',
	   	'#suffix' 			=> '</span>',
	);
	
	$i=0;
	//$docids = 0;
	$documents_master_details	= documents_master_list($service_id,$factory_type_id,'Applicant');
	
	foreach($documents_master_details as $documents){
		
		if($documents->doc_listid!='7') {$star = '<span class="text-red"> (*)</span>';} else {$star = '';}
		
		$form['document_upload_tab'.$documents->doc_listid]= array(
			'#type' 		=> 'fieldset',
			'#title' 		=> $documents->document_name.$star,
			'#collapsible'	=> TRUE,
			'#group'		=> 'document_upload',
			'#weight' 		=> $i,
			'#attributes' 	=> array('class'=>array()),
		);
		
		$form['document_upload_tab'.$documents->doc_listid]['file'] = array(
			'#type' 		=> 'file',
			'#name' 		=> 'files[]',
			'#title' 		=> $documents->document_name.$star,
			'#description' 	=> t("Maximum filesize: <strong>4 MB</strong> | Allowed extension: <strong>PDF</strong>"),
			'#attributes' 	=> array('multiple' => 'multiple'),
			'#group'		=> 'document_upload',
			'#upload_location' => 'public://upload/upload_pdf/',
		);
		
		$form['document_upload_tab'.$documents->doc_listid]['doc_id'.$i] = array(
			'#type' => 'hidden',
			'#value' => $documents->doc_listid,
		);

		$form['document_upload_tab'.$documents->doc_listid]['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Upload'),
			'#attributes' 	=> array('class' => array('btn btn-success pull-right')),
		);

		$i++;
	}
	/********** Document Information - Start **********/

	$form['nexte'] = array(
			'#type' => 'submit',
			'#prefix' => '<div class="col-xs-12" style="display:none">',
			'#suffix' => '</div>',
			'#ajax'			=> array(
							 'effect' 	=> 'fade',			
							 'callback' => 'ajax_add_nexte',
							 'progress'	=>	array('type' => 'throbber','message' => t('loading'))
						)
			
		);

		$form['next'] = array(
			'#prefix' => '<div id="load">',
			'#suffix' => '</div>',
		);

	$resultData = upload_document_data($application_id,$reference_no,$service_id,$factory_type_id);
	$a=0;
	$master = array();
	$upload = array();
	
	foreach($resultData as $res){
		$upload[$a] = $res->doc_master_id; 
		$a++;
	}
	
	$documents_master_details	= documents_master_data($service_id,$factory_type_id);
	$b=0;
	foreach($documents_master_details as $documents){
		if($documents->doc_listid!=7){
			$master[$b] = $documents->doc_listid;
		}
		$b++;
	}
	
	//$finalarr = array_intersect($master, array_unique($upload));//die;

		/*if (count($master)==count($finalarr)) {
		
			$form['next'] = array(
				'#prefix' => '<div id="load">',
				'#suffix' => '</div>',
				'#type' => 'submit',
				'#value' => t('Save'),
				'#attributes' 	=> array('class' => array('btn btn-success pull-right')),
				
			);
		}*/
		
		sort($master);

		if(!empty($upload)){
			
			sort($upload);
			
			if ($master == $upload) {
				//die('dd');
			$form['next'] = array(
				'#prefix' => '<div id="load">',
				'#suffix' => '</div>',
				'#type' => 'submit',
				'#value' => t('Next'),
				'#attributes' 	=> array('class' => array('btn btn-warning pull-right')),
				
			);
			
		}
	}
	
	
	/////////////////////////END///////////////////////////////


	$form['factory_part_upload']['doc_list2'] = array(
		'#prefix' => '<div class="col-md-12"><font color="#FF0000">(N.B.:- All Document need to upload for inspections. Except other document.)</font>',
		'#suffix' => '</div>',
	);
	
	$form['factory_part_upload']['doc_list'] = array(
			'#prefix' => '<div id="table_div_replace"><div class="col-md-12">'.get_uploaded_document_list($service_id,$factory_type_id,$application_id,$reference_no,$plan_approve_status),
			'#suffix' => '</div></div>'
	);	
	
	return $form; 
 }	

 function caf_form_partb_validate($form, &$form_state) {
	$file_name = $form_state['values']['file'][$i]->filename;
	if($file_name > 2097152) {
		form_set_error('file_doc_size', 'The file '.$form_state['values']['file'][$i]->filename.' could not be uploaded, because it exceeds 2 MB, the maximum allowed size for uploads.');	
	}
 }

 function caf_form_partb_submit($form, &$form_state){ 
	
	global $user;
	$uid = $user->uid;
	$val    				= $form_state['values'];

	$commands   					=  array();
	$service_year					=  $val['service_year'];
	$factory_type					=  encryption_decryption_fun('decrypt',$val['factorytypeid']);
	$service_id						=  encryption_decryption_fun('decrypt',$val['serviceid']);
	$application_id					=  encryption_decryption_fun('decrypt',$val['application_id_hidden']);
	$reference_no					=  encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
	$plan_approve_status 		 	=  encryption_decryption_fun('decrypt', $val['plan_approve_status_hidden']);
	//$documents_master_details		=  documents_master_details($service_id,$factory_type);



	$text 					= $val['document_upload__active_tab'];
	$end_id 				= explode('edit-document-upload-tab',$text);
	$master_doc_id 			= end($end_id);
	
	if($val['op']== "Next"){
		drupal_goto('applicant/caf/application-preview/'.$val['serviceid'].'/'.$val['factorytypeid'].'/'.$val['application_id_hidden'].'/'.$val['reference_no_hidden']) ;
	}
	else{
		//echo 're'.$application_id.'-'.$service_id.'-'.$factory_type.'-'.$reference_no.'-'.$master_doc_id; die;
		$get_id = get_checking_id($application_id,$service_id,$factory_type,$reference_no,$master_doc_id);

		if($get_id == $master_doc_id){
			drupal_set_message('Please delete previous files then upload with multi select.','error');
		}else{
			$document_list_details = fun_fetch_document_listid($master_doc_id);
			//print_r($document_list_details);die;
			
			$num_files = count($_FILES['files']['name']);

			for ($i = 0; $i < $num_files; $i++) {
				 $destination = 'public://upload/upload_pdf/';	
				$file = file_save_upload($i, array(
					'file_validate_extensions' => array('pdf'),
					FILE_EXISTS_RENAME,
					//FILE_STATUS_PERMANENT
				),$destination, $file = FILE_EXISTS_RENAME);
			
				if ($file){
					
					if(!empty($id)){
						$doc_id = $id;
					}else{
						$doc_id = $val['doc_id'.$i];
					}
	
					$form_state['values']['file'][$i] = $file;
					$path_parts_doc = pathinfo($form_state['values']['file'][$i]->filename);
					
					//$path_parts_doc = pathinfo($_FILES['files']['name'][$i]);
					//$new_filename_doc = str_replace(' ', '+', file_name($doc_id)).'_DOCUMENT_'.rand(1, 1000000).'.'.$path_parts_doc['extension'];
					//$new_filename_doc = 'DOCUMENTS_'.$doc_id.'_'.rand(1, 1000000).'.'.$path_parts_doc['extension'];
					$new_filename_doc = 'DOCUMENTS_'.date('d-m-yy').'_'.rand(1, 1000000).'.'.$path_parts_doc['extension'];
					//end
					$file_doc = $new_filename_doc;
					//file_save($file_doc);
					
					$filename_doc_arr = explode("/", $form_state['values']['file'][$i]->uri);
			
					$filepathSave_doc 	= file_get_contents(escapefile_url('public://upload/upload_pdf/'.$filename_doc_arr[4]));
					$content_doc 		= base64_encode($filepathSave_doc);
				
						$doc_content_arr = array(
							'upload_doc_content' => $content_doc,
						);
						$upload_doc_content_id = db_insert('fa_caf_upload_doc_content')->fields($doc_content_arr)->execute();
						
					if($master_doc_id == 3) {
						$get_fa_cafa           				    = get_fa_cafa($application_id);
						$wbpcb_category_name 			  		= $get_fa_cafa['wbpcb_category_name'];
						
						if($wbpcb_category_name == 4) {
							$upload_doc_type = 'INT';	
						} else {
							$upload_doc_type = 'DOC';
						}
					} else {
						$upload_doc_type = 'DOC';	
					}

						$caf_upload_doc_arr = array(
							'application_id' => $application_id,
							'application_reference_no' => $reference_no,
							'file_name' => $new_filename_doc,
							'doc_master_id' => $master_doc_id,
							'factory_typeid' => $factory_type,
							'service_id' => $service_id,
							'upload_doc_content_id' => $upload_doc_content_id,
							'upload_doc_type' => $upload_doc_type,
							'created_by'	=> $uid,
							'created_date' => date('Y-m-d h:i:s'),
							'identity_flag' =>$document_list_details['identity_flag']
							);
							
						db_insert('fa_caf_upload_all_doc')->fields($caf_upload_doc_arr)->execute();
	
					$id = $doc_id;
					
				}
	
			}
			drupal_set_message('Documents has been saved successfully.');
			remark_input($reference_no,$application_id,'In','Documents('.$i.') is sucessfully added');

		}		
		$form_state['rebuild'] = true;
	}	

 }

 /*function delete_uploaded_document_data($id,$doc_type,$service_id,$factory_type_id,$application_id,$reference_no){
	drupal_add_library('system', 'drupal.ajax');
	 if (trim(encryption_decryption_fun('decrypt', $id)) != 0) {

		$app_id 		= encryption_decryption_fun('decrypt', $application_id);
		$service_no 	= encryption_decryption_fun('decrypt', $service_id);
		$factory_type 	= encryption_decryption_fun('decrypt', $factory_type_id);
		$referance_id 	= encryption_decryption_fun('decrypt', $reference_no);
		$docid 			= encryption_decryption_fun('decrypt', $id);
		$doctype		= encryption_decryption_fun('decrypt', $doc_type);

		$results 	= get_caf_upload_doc_all($app_id, $service_no, $doctype, $factory_type, $referance_id,$docid);

		foreach($results as $val)
		{
	 		db_delete('fa_caf_upload_doc_content')->condition('id',$val->upload_doc_content_id)->execute();
		}

	//echo $app_id.'--'.$service_no.'--'.$doctype.'--'.$factory_type.'--'.$referance_id.'--'.$docid;
	
		$query = db_delete('fa_caf_upload_all_doc');
		$query->condition('doc_master_id',  $docid,'=');
		$query->condition('application_id', $app_id,'=');
		$query->condition('application_reference_no', $referance_id,'=');
		$query->condition('factory_typeid', $factory_type,'=');
		$query->condition('service_id',$service_no,'=');
		$query->execute();


		$commands = array();
		$commands[] = ajax_command_replace('#table_div_replace', "<div id='table_div_replace'><div class='col-md-12'>".get_uploaded_document_list(encryption_decryption_fun('decrypt',$service_id),encryption_decryption_fun('decrypt',$factory_type_id),encryption_decryption_fun('decrypt',$application_id),encryption_decryption_fun('decrypt',$reference_no))."</div></div>");
		$commands[] = ajax_command_replace('#load', drupal_render($form['next']));
		$page = array('#type' => 'ajax', '#commands' => $commands);
		 ajax_deliver($page);
		
	 }
 }*/
 
 function get_uploaded_document_list($service_id,$factory_type_id,$application_id,$reference_no){
	$output = '';
	
		$output .= '<table border="1" width="100%">
			<tr><td colspan="4">&nbsp;</td></tr>
			<tr align="center" style="font-weight:bold;font-size:16px;">
				<td width="5%">SL No</td>
				<td width="50%">DOCUMENT NAME</td>
				<td width="30%">UPLOADED DOCUMENT</td>
				<td width="15%">ACTION</td>
			</tr>';

	$documents_master_list	= documents_master_data($service_id,$factory_type_id);
    $sl = 1;
	foreach($documents_master_list as $documents){
		$documents_type = NULL;

		 //$resultData 	= get_caf_upload_doc_all($application_id, $service_id, 'DOC', $factory_type_id, $reference_no,$documents->id);
		  $resultData 	= get_caf_upload_doc_all($application_id, $service_id, $documents_type, $factory_type_id, $reference_no,$documents->doc_listid);
		  $rowspan = count($resultData)+1;
		  
		  if(!empty($resultData))
		  {
			$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','document-list/delete-upload-doc/'.encryption_decryption_fun('encrypt', $documents->id).'/'.encryption_decryption_fun('encrypt', 'DOC').'/'.encryption_decryption_fun('encrypt', $service_id).'/'.encryption_decryption_fun('encrypt', $factory_type_id).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt', $reference_no).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
			//$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','document-list/delete-doc-file/'.encryption_decryption_fun('encrypt', $service_id).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt', $factory_type_id).'/'.encryption_decryption_fun('encrypt', $reference_no).'/'.encryption_decryption_fun('encrypt', $documents->id).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete')));//,'class'=>array('red','use-ajax')
		  } else {
			  $delLink = '';
			}
			
		$output .= '<tr>
						<td width="5%" align="center" rowspan="'.$rowspan.'">'.$sl.'</td>
						<td width="50%" style="padding-left: 5px;" rowspan="'.$rowspan.'">'.file_name($documents->id).'</td>
						<td width="30%">&nbsp;</td>
						<td width="15%" align="center" rowspan="'.$rowspan.'">'.$delLink.'</td>
					</tr>';

        foreach($resultData as $val)
		{
			
			$displayLink = l('<i class="ace-icon fa fa-file-pdf-o bigger-130"></i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $val->id).'/'.encryption_decryption_fun('encrypt', 'DOC').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
			
			$output .= '<tr>
							<td width="30%" style="padding-left: 10px;">'.$displayLink.'&nbsp;'.$val->file_name.'</td>
						</tr>';

		}
		$output .= '<tr><td colspan="4">&nbsp;</td></tr>';			
		
      $sl++;
	}
				
	$output .= '</table>';

	return $output;	
 } 

function get_checking_id($application_id,$service_id,$factory_type,$reference_no,$master_doc_id){ //echo $application_id.'-'.$service_id.'-'.$factory_type_id.'-'.$reference_no.'-'.$master_doc_id; die;

	$id = db_query('SELECT  doc_master_id  FROM {fa_caf_upload_all_doc} WHERE application_id = :application_id and service_id= :service_id and factory_typeid =:factory_typeid and application_reference_no =:ref_id and doc_master_id =:doc_master_id',
	array(':application_id'=>$application_id,':service_id'=>$service_id,':factory_typeid'=> $factory_type,':ref_id'=>$reference_no, ':doc_master_id'=>$master_doc_id))->fetchObject()->doc_master_id;
	return $id;
}