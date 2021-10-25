<?php

   
function download_all_certificates($serviceid,$applicationid,$factory_typeid,$referenceno) {	
	$service_id         = encryption_decryption_fun('decrypt', $serviceid);
    $factory_type_id   	= encryption_decryption_fun('decrypt', $factory_typeid);
	$application_id   	= encryption_decryption_fun('decrypt', $applicationid);
	$reference_no   	= encryption_decryption_fun('decrypt', $referenceno);

	$identity_flag   	= encryption_decryption_fun('decrypt', $identityflag);
	
	$output = '';
	
		$output .= '<table border="1" width="100%">
			<tr><td colspan="4">&nbsp;</td></tr>
			<tr align="center" style="font-weight:bold;font-size:16px;">
				<td width="5%">SL No</td>
				<td width="50%">DOCUMENT NAME</td>

				<td width="15%">Download</td>
			</tr>';
	$content_type = NULL;
	$sl = 1;
			
	$get_lic_certificate = get_caf_upload_doc_all_according_observation($application_id,$service_id,'LIC', $factory_type_id,$reference_no, 'lic_certificate');
	$get_site_plan_jd = get_caf_upload_doc_all_according_observation($application_id,$service_id,'FACTORY PLAN', $factory_type_id,$reference_no, 'site_plan_jd');
	//print_r($get_lic_certificate);die;
	$get_reg_certifacate = get_caf_upload_doc_all_according_observation($application_id,$service_id,'REG', $factory_type_id,$reference_no, 'reg_certifacate');
	$get_plan_approval_no = get_caf_upload_doc_all_according_observation($application_id,$service_id,'APPROVAL LETTER', $factory_type_id,$reference_no, 'plan_approval_no');
	if(!empty($get_lic_certificate)){
		foreach($get_lic_certificate as $row_get_lic_certificate){
		
		
		$displayLink = l('<i class="ace-icon fa fa-file-pdf-o bigger-130"></i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $row_get_lic_certificate->id).'/'.encryption_decryption_fun('encrypt', $row_get_lic_certificate->upload_doc_type).'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
		
		$output .= '<tr>
						<td width="5%" align="center" rowspan="'.$rowspan.'">'.$sl.'</td>
						<td width="50%" style="padding-left: 5px;" rowspan="'.$rowspan.'">'.$row_get_lic_certificate->file_name.'</td>
						<td width="15%" align="center" rowspan="'.$rowspan.'">'.$displayLink.'</td>
					</tr>';
					
					
		$sl = $sl+1;			
	}
	}
	if(!empty($get_site_plan_jd)){
		foreach($get_site_plan_jd as $row_get_site_plan_jd){
		
		
		$displayLink = l('<i class="ace-icon fa fa-file-pdf-o bigger-130"></i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $row_get_site_plan_jd->id).'/'.encryption_decryption_fun('encrypt', $row_get_site_plan_jd->upload_doc_type).'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
		
		$output .= '<tr>
						<td width="5%" align="center" rowspan="'.$rowspan.'">'.$sl.'</td>
						<td width="50%" style="padding-left: 5px;" rowspan="'.$rowspan.'">'.$row_get_site_plan_jd->file_name.'</td>
						<td width="15%" align="center" rowspan="'.$rowspan.'">'.$displayLink.'</td>
					</tr>';
					
					
		$sl = $sl+1;			
	}
	}
	
	if(!empty($get_plan_approval_no)){
		foreach($get_plan_approval_no as $row_get_plan_approval_no){
		
		
		$displayLink = l('<i class="ace-icon fa fa-file-pdf-o bigger-130"></i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $row_get_plan_approval_no->id).'/'.encryption_decryption_fun('encrypt', $row_get_plan_approval_no->upload_doc_type).'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
		
		$output .= '<tr>
						<td width="5%" align="center" rowspan="'.$rowspan.'">'.$sl.'</td>
						<td width="50%" style="padding-left: 5px;" rowspan="'.$rowspan.'">'.$row_get_plan_approval_no->file_name.'</td>
						<td width="15%" align="center" rowspan="'.$rowspan.'">'.$displayLink.'</td>
					</tr>';
					
					
		$sl = $sl+1;			
	}
	}
	if(!empty($get_reg_certifacate)){
		foreach($get_reg_certifacate as $row_get_reg_certifacate){
		
		
		$displayLink = l('<i class="ace-icon fa fa-file-pdf-o bigger-130"></i>','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $row_get_reg_certifacate->id).'/'.encryption_decryption_fun('encrypt', $row_get_reg_certifacate->upload_doc_type).'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
		
		$output .= '<tr>
						<td width="5%" align="center" rowspan="'.$rowspan.'">'.$sl.'</td>
						<td width="50%" style="padding-left: 5px;" rowspan="'.$rowspan.'">'.$row_get_reg_certifacate->file_name.'</td>
						<td width="15%" align="center" rowspan="'.$rowspan.'">'.$displayLink.'</td>
					</tr>';
					
					
		$sl = $sl+1;			
	}
	}
	
	$output .= '</table>';

	return $output;	

	

	

	 
	
}
