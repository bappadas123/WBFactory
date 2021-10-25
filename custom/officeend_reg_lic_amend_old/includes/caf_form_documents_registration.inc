<?php
 drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function caf_form_documents_registration($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$referenceno)
{
    global $base_root, $base_path;
    /****************** Upload Part **********************/
   	$service_id         = encryption_decryption_fun('decrypt', $serviceid);
    $factory_type_id   	= encryption_decryption_fun('decrypt', $factory_typeid);
	$application_id   	= encryption_decryption_fun('decrypt', $applicationid);
	$reference_no   	= encryption_decryption_fun('decrypt', $referenceno);
	
   	$get_fa_cafa 		= get_fa_cafa($application_id);
   
	$is_basic_information_tab    		=   $get_fa_cafa['is_year_calculation_tab'];
	
	
	
	
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
	
  $form['header']            = array(
        '#markup' => t('<div class="content"><h1><font color ="red">UNDER DEVELOPMENT</font></h1><h3>Application for Registration and Grant of Licence.All inputs are provided by applicant only.
All inputs are to be verified by officials</h3>')
    );	
	$form['document_details']['documents_list_factory_document_details'] 	= array(
	   
	
		'#type'		=> 'markup',
	  '#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12" id="worker_table_id">
					  <table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
					  <tr>							
						  <th>Supportive Documents According to Application </th>
						  <th >Action</th>
						  
					  </tr>
					  '
			  );

$caf_upload_doc_document_details =  get_caf_upload_doc_all_according_observation($application_id,$service_id,'DOC', $factory_type_id,$reference_no, 'power_details');


  foreach ($caf_upload_doc_document_details as $record) {
	  
  $fetch_document = fun_fetch_document_listid($record->doc_master_id);
  $document_name = $fetch_document['document_name'];
  $displayLink = l('<i>'.$document_name.'</i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $record->id).'/'.encryption_decryption_fun('encrypt', $record->upload_doc_type).'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
  
  
  $form['document_details']['documents_list_factory_document_details'.$record->id] = array(
	   '#prefix' 			=> '<tr><td><div class="col-md-12 col-xs-12">',
		  '#suffix' 			=> '</td></div>',
	   '#type' 			=> 'markup',
  
	  '#markup' 	=>$displayLink,
	  
  );
   if(!empty($doc_verify_field)){
	  if (in_array($record->id, $doc_verify_field)) {
			  $form['document_details']['documents_list_factory_document_details_chk_'.$record->id] = array(
					  '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
					  '#suffix' 			=> '</div></tr></td>',
					'#type' 			=> 'checkbox',
					 '#default_value' 	=>'1',
	  
	  
				);
		  }else{
			  $form['document_details']['documents_list_factory_document_details_chk_'.$record->id] = array(
					  '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
					  '#suffix' 			=> '</div></tr></td>',
					'#type' 			=> 'checkbox',
					 
	  
	  
				);
		  }
	  
   }else{
	   $form['document_details']['documents_list_factory_document_details_chk_'.$record->id] = array(
					  '#prefix' 			=> '<td><div class="col-md-12 col-xs-12">',
					  '#suffix' 			=> '</div></tr></td>',
					'#type' 			=> 'checkbox',
					 '#default_value' 	=>'1',
	  
	  
				);
   }
  
  }

$form['document_details']['documents_list_factory_document_details_end'] 	= array(
  '#suffix' 	=> '</table></div>',
);
	//if($application_status == 'U'){
	   $form['submit'] = array(
        '#prefix' => '<div class="col-md-1">',
        '#suffix' => '</div>',
        '#attributes' => array('class' => array('btn btn-success')),
        '#type' => 'submit',
        '#value' => 'Save'
    );
  //}
	
    return $form;
}

 


function delete_uploaded_document_data($id,$doc_type,$service_id,$factory_type_id,$application_id,$reference_no){
	drupal_add_library('system', 'drupal.ajax');
	 if (trim(encryption_decryption_fun('decrypt', $id)) != 0) {

		$app_id 		= encryption_decryption_fun('decrypt', $application_id);
		$service_no 	= encryption_decryption_fun('decrypt', $service_id);
		$factory_type 	= encryption_decryption_fun('decrypt', $factory_type_id);
		$referance_id 	= encryption_decryption_fun('decrypt', $reference_no);
		$docid 			= encryption_decryption_fun('decrypt', $id);
		$doctype		= encryption_decryption_fun('decrypt', $doc_type);

		//echo $app_id.'--'.$service_no.'--'.$doctype.'--'.$factory_type.'--'.$referance_id.'--'.$docid;die;

		$results 	= get_caf_upload_doc_all($app_id, $service_no, $doctype, $factory_type, $referance_id,$docid);

		foreach($results as $val)
		{
	 		db_delete('fa_caf_upload_doc_content')->condition('id',$val->upload_doc_content_id)->execute();
		}

	
	
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
}


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
		  $resultData 	= get_caf_upload_doc_all($application_id, $service_id, $documents_type, $factory_type_id, $reference_no,$documents->doc_listid);

		  $rowspan = count($resultData)+1;
		  
		  if(!empty($resultData))
		  {
			//$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','document-list/delete-upload-doc/'.encryption_decryption_fun('encrypt', $documents->doc_listid).'/'.encryption_decryption_fun('encrypt', $documents_type).'/'.encryption_decryption_fun('encrypt', $service_id).'/'.encryption_decryption_fun('encrypt', $factory_type_id).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt', $reference_no).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete','class'=>array('red','use-ajax'))));
			//$delLink = l('<i class="ace-icon fa fa-trash-o bigger-130"></i>','document-list/delete-doc-file/'.encryption_decryption_fun('encrypt', $service_id).'/'.encryption_decryption_fun('encrypt', $application_id).'/'.encryption_decryption_fun('encrypt', $factory_type_id).'/'.encryption_decryption_fun('encrypt', $reference_no).'/'.encryption_decryption_fun('encrypt', $documents->id).'',array('html' => TRUE,'attributes'=>array('title' => 'Delete')));//,'class'=>array('red','use-ajax')
		  } else {
			  //$delLink = '';
			}
			
		$output .= '<tr>
						<td width="5%" align="center" rowspan="'.$rowspan.'">'.$sl.'</td>
						<td width="50%" style="padding-left: 5px;" rowspan="'.$rowspan.'">'.file_name($documents->id).'</td>
						<td width="30%">&nbsp;</td>
						<td width="15%" align="center" rowspan="'.$rowspan.'"><input type="checkbox" id="ownership_type'.$documents->id.'" class="inspector_verify_check" '.$ownership_type_ck.'/></td>
					</tr>';

        foreach($resultData as $val)
		{
			
			
			
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
/******************************************** Upload Part End *****************************************************************/
function caf_form_documents_registration_submit($form, &$form_state){}


function get_checking_id($application_id,$service_id,$factory_type,$reference_no,$master_doc_id){

	$id = db_query('SELECT  doc_master_id  FROM {fa_caf_upload_all_doc} WHERE application_id = :application_id and service_id= :service_id and factory_typeid =:factory_typeid and application_reference_no =:ref_id and doc_master_id =:doc_master_id',
	array(':application_id'=>$application_id,':service_id'=>$service_id,':factory_typeid'=> $factory_type,':ref_id'=>$reference_no, ':doc_master_id'=>$master_doc_id))->fetchObject()->doc_master_id;
	return $id;
}