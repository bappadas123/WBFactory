<?php
function download_content_file($serviceid, $applicationid, $factorytypeid, $referanceid, $flagtype) {

		global $user;
		$uid 	= $user->uid;
		
		$service_id = encryption_decryption_fun('decrypt', $serviceid);
		$application_id = encryption_decryption_fun('decrypt', $applicationid);
		$referance_id = encryption_decryption_fun('decrypt', $referanceid);
		$factorytype_id = encryption_decryption_fun('decrypt', $factorytypeid);
		$flag_type = encryption_decryption_fun('decrypt', $flagtype);
		
		$service_id.'/'.$application_id.'/'.$referance_id .'/'.$factorytype_id.'/'.$flag_type;die;

        $filepathSave 	= 'sites/default/files/upload/download_pdf/'; // different folder for show uploaded file
		
		//data from the table where filename stored
	
		$get_caf_upload_doc = get_caf_upload_doc_details($application_id,$service_id, $flag_type,$factorytype_id,$referance_id);
		
		//print_r($get_caf_upload_doc);die;
		// data from encrypted data table
		$query 			= db_select('fa_caf_upload_doc_content', 'cudc')->fields('cudc',array())->condition('id', $get_caf_upload_doc->upload_doc_content_id, '=');
		$query_result 	= $query->execute();
		if($query_result->rowCount() > 0){
			$data 		= $query_result->fetchObject() ;
			$content_file	= base64_decode($data->upload_doc_content);

			if(!file_exists($filepathSave.$get_caf_upload_doc->file_name)){
				file_put_contents($filepathSave.$get_caf_upload_doc->file_name, $content_file);	
				drupal_goto('sites/default/files/upload/download_pdf/' . $get_caf_upload_doc->file_name);
				
			}else if(file_exists($filepathSave.$get_caf_upload_doc->file_name)){
				drupal_goto('sites/default/files/upload/download_pdf/' . $get_caf_upload_doc->file_name);
				
			}else{
				drupal_set_message(t('File not found.'));
			}
		}     
}


function view_caf_doc_file($id, $flagtype){
	$doc_id = encryption_decryption_fun('decrypt', $id);//die($doc_id);
	$flag_type = encryption_decryption_fun('decrypt', $flagtype);
	
	$filepathSave 	= 'sites/default/files/upload/download_pdf/'; // different folder for show uploaded file
	$get_caf_upload_doc = db_query('SELECT *  FROM {fa_caf_upload_all_doc} where id ='.$doc_id)->fetchObject();
	$query 			= db_select('fa_caf_upload_doc_content', 'cudc')->fields('cudc',array())->condition('id', $get_caf_upload_doc->upload_doc_content_id, '=');
	$query_result 	= $query->execute();
	if($query_result->rowCount() > 0){
		$data 		= $query_result->fetchObject() ;
		$content_file	= base64_decode($data->upload_doc_content);

		if(!file_exists($filepathSave.$get_caf_upload_doc->file_name)){
			file_put_contents($filepathSave.$get_caf_upload_doc->file_name, $content_file);	
			drupal_goto('sites/default/files/upload/download_pdf/' . $get_caf_upload_doc->file_name);
			
		}else if(file_exists($filepathSave.$get_caf_upload_doc->file_name)){
			drupal_goto('sites/default/files/upload/download_pdf/' . $get_caf_upload_doc->file_name);
			
		}else{
			drupal_set_message(t('File not found.'));
		}
	}     

}

function head_application_file($serviceid, $applicationid, $factorytypeid, $referanceid, $flagtype,$id){
		global $user;
		$uid 	= $user->uid;
		
		$service_id = encryption_decryption_fun('decrypt', $serviceid);
		$application_id = encryption_decryption_fun('decrypt', $applicationid);
		$referance_id = encryption_decryption_fun('decrypt', $referanceid);
		$factorytype_id = encryption_decryption_fun('decrypt', $factorytypeid);
		$flag_type = encryption_decryption_fun('decrypt', $flagtype);
		$head = encryption_decryption_fun('decrypt', $id);
		
		//echo $service_id.'/'.$application_id.'/'.$referance_id .'/'.$factorytype_id.'/'.$flag_type.'/'.$head;die;

        $filepathSave 	= 'sites/default/files/upload/download_pdf/'; // different folder for show uploaded file
		
		//data from the table where filename stored
		if($service_id==8){
			$get_caf_upload_doc 	= get_caf_upload_doc_all($application_id, $service_id, $flag_type, $factorytype_id, $referance_id,$head);

		}else{
			$get_caf_upload_doc = get_caf_upload_doc_details($application_id,$service_id, $flag_type,$factorytype_id,$referance_id);
		}
		//echo $get_caf_upload_doc[0]->upload_doc_content_id;die;
		//print_r($get_caf_upload_doc);die;

		// data from encrypted data table
		$query 			= db_select('fa_caf_upload_doc_content', 'cudc')->fields('cudc',array())->condition('id', $get_caf_upload_doc[0]->upload_doc_content_id, '=');
		$query_result 	= $query->execute();
		if($query_result->rowCount() > 0){
			$data 		= $query_result->fetchObject() ;
			$content_file	= base64_decode($data->upload_doc_content);

			if(!file_exists($filepathSave.$get_caf_upload_doc[0]->file_name)){
				file_put_contents($filepathSave.$get_caf_upload_doc[0]->file_name, $content_file);	
				drupal_goto('sites/default/files/upload/download_pdf/' . $get_caf_upload_doc[0]->file_name);
				
			}else if(file_exists($filepathSave.$get_caf_upload_doc[0]->file_name)){
				drupal_goto('sites/default/files/upload/download_pdf/' . $get_caf_upload_doc[0]->file_name);
				
			}else{
				drupal_set_message(t('File not found.'));
			}
		}     

}
