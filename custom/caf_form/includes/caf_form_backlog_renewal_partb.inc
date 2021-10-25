 <?php
 drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function caf_form_backlog_renewal_partb($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$linknumber,$linkdate,$flagmapp)
{
    global $base_root, $base_path;
    /****************** Upload Part **********************/
   	$service_id         = encryption_decryption_fun('decrypt', $serviceid);
    $factory_type_id   	= encryption_decryption_fun('decrypt', $factory_typeid);
	$application_id   	= encryption_decryption_fun('decrypt', $applicationid);
	
   	$get_fa_cafa 				= get_fa_cafa($application_id);
    $reference_no 				= $get_fa_cafa['reference_number'];
	$is_basic_information_tab	= $get_fa_cafa['is_year_calculation_tab'];
	
	if(empty($application_id)){
		  	drupal_set_message(('At first you must be filled up the general information of factory then go to second tab'),'warning');
			drupal_goto('applicant/caf-backlog-renew/apply-backlog-renewal-service/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$linknumber.'/'.$linkdate.'/'.$flagmapp) ;
	 }
	  if(empty($is_basic_information_tab)){
		  	drupal_set_message(('Please fill up the second tab than fill up the basic information'),'warning');			
			drupal_goto('applicant/caf-backlog-renew/backlog-renewal-basic-service/'.$serviceid.'/'.$factory_typeid.'/'.$applicationid.'/'.$linknumber.'/'.$linkdate.'/'.$flagmapp) ;
	 } 
	$form 					= array();
	$form['#attributes'] 	= array('enctype' => "multipart/form-data");
	$form['serviceid'] 	= array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $serviceid,
	);
	$form['factorytypeid'] = array(
		'#type'				=> 'hidden', 
		'#default_value' 	=> $factory_typeid		 
	);	
	$form['reference_no_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> encryption_decryption_fun('encrypt', $reference_no)	 
	);
	$form['application_id_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> encryption_decryption_fun('encrypt', $application_id)	 
	);
	$form['linknumber_hidden']       = array(
		'#type' 			=> 'hidden',
		'#default_value'	=> $linknumber
    );
	$form['linknumber_hidden_date']       = array(
		'#type' 			=> 'hidden',
		'#default_value'	=> $linkdate
    );
	$form['flagmapp']	= array(
		'#type' 			=> 'hidden',
        '#default_value' 	=> $flagmapp
    );

	$form['document_upload'] = array(
		'#type' 			=> 'vertical_tabs',
		'#prefix' 			=> '<span id="replace_div_file">',
	   	'#suffix' 			=> '</span>',
	);
	
	$i=0;
	$documents_master_details	= documents_master_list($service_id,$factory_type_id);
	//print_r($documents_master_details);die;
	foreach($documents_master_details as $documents){
	if($documents->id!='42') {$star = "<span class='text-red'><b> (*)</b></span>";} else {$star = '';}
	$form['document_upload_tab'.$documents->id]= array(
		'#type' 		=> 'fieldset',
		'#title' 		=> $documents->document_name.'&nbsp;'.$star,
		'#collapsible'	=> TRUE,
		'#group'		=> 'document_upload',
		'#weight' 		=> $i,
		'#attributes' 	=> array('class'=>array()),
		
	);
	
	$form['document_upload_tab'.$documents->id]['file'] = array(
		'#type' 		=> 'file',
		'#name' 		=> 'files[]',
			//'#required'	=> TRUE,
		'#title' 		=> $documents->document_name.$star,
		'#description' 	=> t("Maximum filesize: <strong>4 MB</strong> | Allowed extension: <strong>PDF</strong>"),
		'#attributes' 	=> array('multiple' => 'multiple'),
		'#group'		=> 'document_upload',
	);
	$form['document_upload_tab'.$documents->id]['doc_id'.$i] = array(
		'#type' => 'hidden',
		'#value' => $documents->id,
	);	
	$form['document_upload_tab'.$documents->id]['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Upload'),
			'#attributes' 	=> array('class' => array('btn btn-success pull-right')),
	);	
	$i++;
	}
	
	////////////////////////////////////ADD///////////////////////////////////
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
	$resultData = upload_document_data($application_id,$reference_no,$service_id,$factory_type_id);
	$a=0;
	foreach($resultData as $res){
		$upload[$a] = $res->id_doc_master; 
		$a++;
	}
	$b=0;
	$documents_master_details	= documents_master_data($service_id,$factory_type_id);
	foreach($documents_master_details as $documents){
	$master[$b] = $documents->id; 
	$b++;
	}
	sort($master);
	sort($upload);
	if ($master == $upload) {
    	$form['next'] = array(
			'#type' => 'submit',
			'#value' => t('Save & Continue'),
			'#attributes' 	=> array('class' => array('btn btn-warning pull-right')),
			
		);
		 
	}
	
	/////////////////////////END//////////////////////////////
 
	$form['factory_part_upload']['doc_list2'] = array(
		'#prefix' => '<div class="col-md-12"><font color="#FF0000">(N.B.:- All Document need to upload for inspections. Except other document.)</font>',
		'#suffix' => '</div>',
	);
	

	$form['factory_part_upload']['doc_list'] = array(
			'#prefix' => '<div id="table_div_replace"><div class="col-md-12">'.get_uploaded_document_list($service_id,$factory_type_id,$application_id,$reference_no),
			'#suffix' => '</div></div>'
	);	
	
	
	
    return $form;		
	
	
	 }
 function caf_form_backlog_renewal_partb_validate($form, &$form_state) {
    //Save multiple files
   
}


function delete_uploaded_document_data($id,$fid,$service_id,$factory_type_id,$application_id,$reference_no){
	
	drupal_add_library('system', 'drupal.ajax');
	
	 if (trim(encryption_decryption_fun('decrypt', $fid)) != 0) {
		 //die(encryption_decryption_fun('decrypt', $id));
		 $query = db_delete('fa_caf_upload_doc');
		 $query->condition('id', trim(encryption_decryption_fun('decrypt', $id)),'=');
		 $query->condition('app_id',trim(encryption_decryption_fun('decrypt', $application_id)),'=');
		 $query->condition('application_reference_no',trim(encryption_decryption_fun('decrypt', $reference_no)),'=');
		 $query->execute();
		 
		 $query = db_select('fa_file_managed_custom', 'fm');
		 $query ->fields('fm', array('file_uri'));
		 $query->condition('fm.id',trim(encryption_decryption_fun('decrypt', $fid)),'=');
		 $result = $query->execute();
		 $resultData = $result->fetchAssoc();
		 
		 db_delete('fa_file_managed_custom')->condition('id',encryption_decryption_fun('decrypt', $fid))->execute();
		 
		 drupal_unlink($resultData['uri']);
		
		 $commands = array();
		 $commands[] = ajax_command_replace('#table_div_replace', "<div id='table_div_replace'><div class='col-md-12'>".get_uploaded_document_list(encryption_decryption_fun('decrypt',$service_id),encryption_decryption_fun('decrypt',$factory_type_id),encryption_decryption_fun('decrypt',$application_id),encryption_decryption_fun('decrypt',$reference_no))."</div></div>");
		 $page = array('#type' => 'ajax', '#commands' => $commands);
		 ajax_deliver($page);
		
	 }
}


function get_uploaded_document_list($service_id,$factory_type_id,$application_id,$reference_no){
	$output = '';
	$sl = 0;
	$header = array(
		array('data'=> 'SL No'),
		array('data'=> 'Document Name'),
		array('data'=> 'Uploaded Document Of'),
		array('data'=> 'Action')
	);

	$rows = array();
	
	$query 	=  db_select('fa_caf_upload_doc', 'fcud');
	$query	-> InnerJoin('fa_file_managed_custom', 'file' ,'fcud.fid = file.id');
	$query 	-> fields('fcud', array());
	$query	-> fields('file', array('file_uri'));
	$query	-> condition('fcud.app_id', $application_id);
	$query	-> condition('fcud.application_reference_no', $reference_no);
	$query	-> condition('fcud.upload_documents_service_id', $service_id);
	$query	-> condition('fcud.upload_doc_factory_type_id', $factory_type_id);
	$result = $query->execute();
	//echo $query;die;
	$resultData = $result->fetchAll();
	foreach($resultData as $val)
	{		
	$sl= $sl+1;		
		if($val->application_status == 'F'){
		$delLink = t('<i class="ace-icon fa fa-ban bigger-130"></i>');
		}else{
			$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','applicant/del-doc-backlog-renew/'.encryption_decryption_fun('encrypt', $val->id).'/'.encryption_decryption_fun('encrypt', $val->fid).'/'.encryption_decryption_fun('encrypt', $service_id).'/'.encryption_decryption_fun('encrypt', $factory_type_id).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt', $reference_no).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
			}
		$displayLink = l('<i class="ace-icon fa fa-file-pdf-o bigger-130"></i>',file_create_url($val->file_uri),array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
		
		$displayName = l(t($displayLink .'&nbsp;'. $val->file_name),'',array('html' => TRUE,'attributes'=>array('title' => 'Display PDF', 'class'=>array('display'))));
		//<a  class =" label label-info" href="'.file_create_url($val->file_uri).'" target="ref" onclick="popIt(this.href);return false;">View Application</a>
		$rows [] = array(  
			array('data' => $sl), 
			array('data' => t(file_name($val->id_doc_master))),	
			array('data' => t($displayName)), 
			array('data' => $delLink),	
		);
	$i++;	
	}
	
	$output = theme_table(
	array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('id'=>'table_div_replace1', 'class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	).theme('pager');	
	  
	return $output;	
} 

function ajax_add_more_callback($form, &$form_state){
	
}

/******************************************** Upload Part End *****************************************************************/
function caf_form_backlog_renewal_partb_submit($form, &$form_state){
	
	global $user;
	$val   								= 	$form_state['values'];
	$commands   						= 	array();
	$factory_type						= 	encryption_decryption_fun('decrypt', $val['factorytypeid']);
	$service_id							= 	encryption_decryption_fun('decrypt', $val['serviceid']);
	$application_id						= 	encryption_decryption_fun('decrypt', $val['application_id_hidden']);	
	$reference_no						= 	encryption_decryption_fun('decrypt', $val['reference_no_hidden']);
	$number_reg_lic						= 	encryption_decryption_fun('decrypt', $val['linknumber_hidden']);
	$reg_lic_date						= 	encryption_decryption_fun('decrypt', $val['linknumber_hidden_date']);
	$flagmapp							= 	encryption_decryption_fun('decrypt', $val['flagmapp']);
	
	
	if($val['op']== "Save & Continue"){
		
	drupal_goto('applicant/caf-backlog-renew/application-renewal-preview-backlog/'.$val['serviceid'].'/'.$val['factorytypeid'].'/'.$val['application_id_hidden'].'/'.$val['linknumber_hidden'].'/'.$val['linknumber_hidden_date'].'/'.$val['flagmapp']) ;
	}
	else{
	
		$num_files = count($_FILES['files']['name']);
    	for ($i = 0; $i < $num_files; $i++) {
		$destination = 'public://upload/cafdoc/';	
        $file = file_save_upload($i, array(
            'file_validate_extensions' => array('pdf'),
			'file_validate_size' => array(1*1024*1024*1024),
			FILE_EXISTS_RENAME,
			FILE_STATUS_PERMANENT
        ),$destination, $replace = FILE_EXISTS_RENAME);
			
        if ($file){
			//file_set_status($file, FILE_STATUS_PERMANENT);	
            if ($file = file_move($file, 'public://upload/cafdoc/')) {
				//file_set_status($file, FILE_STATUS_PERMANENT);
				$file->status = FILE_STATUS_PERMANENT;
				file_save($file);
                $form_state['values']['file'][$i] = $file;
				
				$upload_application =array(
					'filename'	=> $form_state['values']['file'][$i]->filename,
					'file_uri'	=> $form_state['values']['file'][$i]->uri,
					'created_by'=> $form_state['values']['file'][$i]->uid,
					'fid'		=> $form_state['values']['file'][$i]->fid,
				);
				$file_manage_id = db_insert('fa_file_managed_custom')->fields($upload_application)->execute();
				if(!empty($id)){
						$doc_id = $id;
					}else{
						$doc_id = $val['doc_id'.$i];
					}
				
				$upload_doc_application =array(
					'app_id'	=> $application_id,
					'uid'		=> $form_state['values']['file'][$i]->uid,
					'fid'		=> $file_manage_id,
					'doc_name' 	=> file_name($doc_id),
					'file_name'	=> $form_state['values']['file'][$i]->filename,
					'application_status' 			=> 'In',
					'application_reference_no' 		=> $reference_no,
					'upload_doc_factory_type_id'  	=> $factory_type,
					'upload_documents_service_id' 	=> $service_id,
					'id_doc_master' 				=> $doc_id,
					
				);
				
				db_insert('fa_caf_upload_doc')->fields($upload_doc_application)->execute();
				
				$id = $doc_id;
            }
            else {
                form_set_error('file', t('Failed to write the uploaded file the site\'s file folder.'));
            }
		
			//die('RRRR--'.$i.'--'.$val['doc_id'.$i]);
			//$id = $val['doc_id'.$i];
			//$commands[] = ajax_command_replace('#replace_div_file', drupal_render($form['document_upload']));
			
        }
		
 }
 
	//return array('#type' => 'ajax', '#commands' => $commands);	
	drupal_set_message('Documents has been saved successfully.');
	drupal_goto('applicant/caf-backlog-renew/cafb_renewal-backlog/'.$val['serviceid'].'/'.$val['factorytypeid'].'/'.$val['application_id_hidden'].'/'.$val['linknumber_hidden'].'/'.$val['linknumber_hidden_date'].'/'.$val['flagmapp']) ;
	}
	
	
}
function documents_master_data($service_id,$factory_type_id){
	$query_factory_documents 	=  db_select('fa_documents_master', 'documents');
	$query_factory_documents	-> fields('documents',array('id'));
	$query_factory_documents	-> condition('documents.document_service_id', $service_id, '=');
	$query_factory_documents	-> condition('documents.document_factory_id', $factory_type_id, '=');
	$query_factory_documents	-> condition('documents.id',array(44), 'NOT IN');
	$query_factory_documents	-> orderBy('documents.id', 'ASC');
	$result_factory_documents 	= $query_factory_documents->execute()->fetchAll(); 
	return $result_factory_documents;
}


function upload_document_data($application_id,$referance_number,$service_id,$factory_type_id){
		$query 	=  db_select('fa_caf_upload_doc', 'fcud')->distinct();
		$query 	-> fields('fcud', array('id_doc_master'));
		$query	-> condition('fcud.app_id', $application_id);
		$query	-> condition('fcud.application_reference_no', $referance_number);
		$query	-> condition('fcud.upload_documents_service_id', $service_id);
		$query	-> condition('fcud.upload_doc_factory_type_id', $factory_type_id);
		$query	-> condition('fcud.id_doc_master',array(44), 'NOT IN');
		$resultData = $query->execute()->fetchAll();
		return $resultData;
	}