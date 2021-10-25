<?php
 drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
function caf_form_documents_registration($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$referenceno)
{
    global $base_root, $base_path,$user;
    /****************** Upload Part **********************/
   	$service_id         = encryption_decryption_fun('decrypt', $serviceid);
    $factory_type_id   	= encryption_decryption_fun('decrypt', $factory_typeid);
	$application_id   	= encryption_decryption_fun('decrypt', $applicationid);
	$reference_no   	= encryption_decryption_fun('decrypt', $referenceno);
	
   	$get_fa_cafa 		= get_fa_cafa($application_id);
   
	$is_basic_information_tab   =   $get_fa_cafa['is_year_calculation_tab'];
	$application_status   =   $get_fa_cafa['application_status'];
	
	$userid = $user->uid;

	$rid= get_role_id($userid);
	
	$remark_fetch = get_checking($application_id,$service_id,$factory_type_id,$reference_no);
	
	$verify_details = $remark_fetch['verify_details'];
	$doc_verify 	= $remark_fetch['doc_verify'];
	$doc_verify_field = explode(',', $doc_verify);
	
	
	$form 					= array();
	$form['#attributes'] 	= array('enctype' => "multipart/form-data");
	$form['serviceid_hidden'] 	= array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> $serviceid,
	);
	$form['factorytypeid_hidden'] = array(
		'#type'				=> 'hidden', 
		'#default_value' 	=> $factory_typeid		 
	);	
	$form['referenceno_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> encryption_decryption_fun('encrypt', $reference_no)	 
	);
	$form['applicationid_hidden'] = array(
		'#type' 			=> 'hidden',
		'#default_value' 	=> encryption_decryption_fun('encrypt', $application_id)	 
	);
	
  $form['header']            = array(
        '#markup' => t('<div class="content"><h3>Application for Registration and Grant of Licence.All inputs are provided by applicant only.
All inputs are to be verified by officials</h3>')
    );	
	$form['document_details']['documents_list_factory_document_details'] 	= array(
	   
	
		'#type'		=> 'markup',
	  '#prefix'	=> '<div class="row"><div class="col-lg-12 col-md-12 col-sm-12 col-xs-12" id="worker_table_id">
					  <table border="0" cellpadding="0" cellspacing="0" class="custom-table-view-dashboard renewal-table" width="100%">
					  <tr>							
						  <th width="90%" style="white-space: break-spaces;">Supportive Documents According to Application </th>
						  <th  width="10%" >Action</th>
						  
					  </tr>
					  '
			  );

$caf_upload_doc_document_details =  get_caf_upload_doc_all_according_observation($application_id,$service_id,NULL, $factory_type_id,$reference_no, NULL);
  foreach ($caf_upload_doc_document_details as $record) {
	  
  $fetch_document = fun_fetch_document_listid($record->doc_master_id);
  $document_name = $fetch_document['document_name'];
  $displayLink = l('<i>'.$document_name.'</i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $record->id).'/'.encryption_decryption_fun('encrypt', $record->upload_doc_type).'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
  
  
  $form['document_details']['documents_list_factory_document_details'.$record->id] = array(
	   '#prefix' 			=> '<tr><td width="90%" style="white-space: break-spaces;"><div class="col-md-12 col-xs-12">',
		'#suffix' 			=> '</td ></div>',
	   '#type' 			=> 'markup',
  
	  '#markup' 	=>$displayLink,
	  
  );
   if(!empty($doc_verify_field)){
	  if (in_array($record->id, $doc_verify_field)) {
			  $form['document_details']['documents_list_factory_document_details_chk_'.$record->id] = array(
					  '#prefix' 			=> '<td width="10%"><div class="col-md-12 col-xs-12">',
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
					
	  
	  
				);
   }
  
  }

$form['document_details']['documents_list_factory_document_details_end'] 	= array(
  '#suffix' 	=> '</table></div>',
);

if(($rid==9 && $application_status == 'U') || ($rid==10 && $application_status == 'DC') || ($rid==11 && $application_status == 'JC') ){
	   $form['submit'] = array(
        '#prefix' => '<div class="col-md-1">',
        '#suffix' => '</div>',
        '#attributes' => array('class' => array('btn btn-success')),
        '#type' => 'submit',
        '#value' => 'Save'
    );
  }
	
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
						<td width="50%" style="padding-left: 5px; " rowspan="'.$rowspan.'">'.file_name($documents->id).'</td>
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
function caf_form_documents_registration_submit($form, &$form_state){
	 global $user;
      $userid 			= 	$user->uid;
	  $remark_by_name											= get_name($userid);
	  $rid= get_role_id($userid);
	  $val    													= $form_state['values'];
	if($rid==9){
		$remark_to_roleid = 10;
	}if($rid==10){
		$remark_to_roleid = 11;
	}
	 $service_id												= encryption_decryption_fun('decrypt',$val['serviceid_hidden']); 
	  $factorytype_id											= encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	  $application_id											= encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	  $reference_no												= encryption_decryption_fun('decrypt',$val['referenceno_hidden']);
	 
	
	$caf_upload_doc_document_details =  get_caf_upload_doc_all_according_observation($application_id,$service_id,NULL, $factorytype_id,$reference_no, NULL);
	foreach ($caf_upload_doc_document_details as $record) {
		
		 $documents_list .= !empty($val['documents_list_factory_document_details_chk_'.$record->id])?$record->id.',':'';
	}
	

	 $remark_details 		= get_remark_id($application_id,$reference_no,$userid,$rid);
	  $remark_id				= $remark_details['id'];
	$identity_flag_all 		= NULL;
	$irregularities_details = fun_fetch_irregularities_details($identity_flag_all,$application_id,$reference_no,$factorytype_id,$service_id); 

	

 if(!empty($irregularities_details)){
	 foreach($irregularities_details as $row_irregularities_details){
		 $remark_table_id = $row_irregularities_details->remark_table_id;
		$checklist_observations_ref_id = $row_irregularities_details->checklist_observations_ref_id;
	
	 }
	 if($remark_table_id==$remark_id){
		 $cafa_remarks = array(
								
								'sending_time' 	  	 => date('Y-m-d h:i'),
								'remark_type'	  	 => 'n',
							
								'doc_verify'		 => $documents_list,
								
									
						);
					
				$queryupdate_remarks		 =	db_update('fa_cafa_remarks');
				$queryupdate_remarks	 	->	fields($cafa_remarks);
				$queryupdate_remarks		 ->	condition('id',$remark_id,'=');	
				
				$queryupdate_remarks		 ->	execute();
				
	 }else{
		 $cafa_remarks = array(
								'app_id'   	  		 => $application_id,
								'remark_by_uid'  	 => $userid,
								'remark_by_roleid' 	 => $rid,
								'remark_to_roleid' 	 => $remark_to_roleid,
								'sending_time' 	  	 => date('Y-m-d h:i'),
								'app_reference_no' 	 => $reference_no,
								'remark_by_name'	 => $remark_by_name,
								'remark_type'	  	 => 'n',
							
								'remarks'			 => 'Notesheet processed is not completed',
							
								'service_id'		 => $service_id
									
						);

	$remark_id = db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();
	
	 $checklist_observations_ref = array(
								'remark_table_id'	 => $remark_id,
								
						);
					
				$queryupdate_observations_ref		 =	db_update('fa_checklist_observations_ref');
				$queryupdate_observations_ref	 	->	fields($checklist_observations_ref);
				$queryupdate_observations_ref		 ->	condition('id',$checklist_observations_ref_id,'=');	
				$queryupdate_observations_ref		 ->	execute();
	
	
	 }
	}
else{
	
	$irregularities_obsevation_ref = fun_fetch_observations_ref($application_id,$reference_no,$factorytype_id,$service_id); 

	if(!empty($irregularities_obsevation_ref)){
		foreach($irregularities_obsevation_ref as $row_irregularities_obsevation_ref){
		 $remark_table_id = $row_irregularities_obsevation_ref->remark_table_id;
		
	
	 }
	 if($remark_table_id==$remark_id){
		 $cafa_remarks = array(
								
								'sending_time' 	  	 => date('Y-m-d h:i'),
								'remark_type'	  	 => 'n',
								
								'doc_verify'		 => $documents_list,
								
									
						);
					
				$queryupdate_remarks		 =	db_update('fa_cafa_remarks');
				$queryupdate_remarks	 	->	fields($cafa_remarks);
				$queryupdate_remarks		 ->	condition('id',$remark_id,'=');	
				
				$queryupdate_remarks		 ->	execute();
				
	 }else{
		 $cafa_remarks = array(
								'app_id'   	  		 => $application_id,
								'remark_by_uid'  	 => $userid,
								'remark_by_roleid' 	 => $rid,
								'remark_to_roleid' 	 => $remark_to_roleid,
								'sending_time' 	  	 => date('Y-m-d h:i'),
								'app_reference_no' 	 => $reference_no,
								'remark_by_name'	 => $remark_by_name,
								'remark_type'	  	 => 'n',
							
								'remarks'			 => 'Notesheet processed is not completed',
								'doc_verify'		 => $documents_list,
								'service_id'		 => $service_id
									
						);

	$remark_id = db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();
	
	 $checklist_observations_ref = array(
								'remark_table_id'	 => $remark_id,
								
						);
					
				$queryupdate_observations_ref		 =	db_update('fa_checklist_observations_ref');
				$queryupdate_observations_ref	 	->	fields($checklist_observations_ref);
				$queryupdate_observations_ref		 ->	condition('id',$checklist_observations_ref_id,'=');	
				$queryupdate_observations_ref		 ->	execute();
	
	
	 }
	}
	 

	 else{
		 $cafa_remarks = array(
								'app_id'   	  		 => $application_id,
								'remark_by_uid'  	 => $userid,
								'remark_to_roleid' 	 => $remark_to_roleid,
							'remark_by_roleid' 	 => $rid,
								'sending_time' 	  	 => date('Y-m-d h:i'),
								'app_reference_no' 	 => $reference_no,
								'remark_by_name'	 => $remark_by_name,
								'remark_type'	  	 => 'n',
								'remarks'			 => 'Notesheet processed is not completed',
								'doc_verify'		 => $documents_list,
								'service_id'		 => $service_id
									
						);

	$remark_id = db_insert('fa_cafa_remarks')->fields($cafa_remarks)->execute();
    $checklist_observations_ref = array(
	  										
											'remark_table_id'	=> $remark_id,
											'application_id'	=> $application_id,
											'factory_type_id' 	=> $factorytype_id,
											'reference_number'  => $reference_no,
											'service_id'  		=> $service_id,
											'created_by'		=> $userid,
											'created_date'		=> date('Y-m-d')
											
	  									);
	
						
	$checklist_observations_ref_id 		 =	db_insert('fa_checklist_observations_ref')->fields($checklist_observations_ref) ->	execute();
	}
}
	
}

