<?php
function application_remarks($serviceid ,$factorytype,$applicationid ,$referenceid){	
	
	global $base_root,$base_path,$user,$_SESSION;
	
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/sky-forms.css');
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	$service_id 		= encryption_decryption_fun('decrypt',$serviceid);
	$factory_type_id 	= encryption_decryption_fun('decrypt',$factorytype);
	$application_id 	= encryption_decryption_fun('decrypt',$applicationid);
	$reference_no 	    = encryption_decryption_fun('decrypt',$referenceid);

	$get_fa_cafa        = 	get_fa_cafa($application_id);
	$application_no     = 'Application No. :: '.$get_fa_cafa['plan_approve_identification_number'];
	
	$form = array();

	/*$query_rmrk		= 	db_select('fa_cafa_remarks', 'fcr');
	$query_rmrk     ->  InnerJoin('role', 'r', 'fcr.remark_by_roleid=r.rid');
	$query_rmrk     ->  InnerJoin('users', 'u', 'fcr.remark_by_uid=u.uid');
	$query_rmrk		->	fields('fcr',array('sending_time','remarks','remark_by_name'));
	$query_rmrk		->	fields('r',array('name'));
	$query_rmrk		->	fields('u',array('name'));
	$query_rmrk		-> 	condition('fcr.app_id', $application_id);
	$query_rmrk		-> 	condition('fcr.app_reference_no', $reference_no);
	$query_rmrk		-> 	condition('fcr.remarks','','!=');
	$query_rmrk		-> 	condition('fcr.remark_type', 'r');*/

	$db_or = db_or();
	$db_or->condition('fcr.remark_type', 'n');
	$db_or->condition('fcr.remark_type', 'r');
	
	$query_rmrk		= 	db_select('fa_cafa_remarks', 'fcr');
	$query_rmrk     ->  LeftJoin('role', 'r', 'fcr.remark_by_roleid=r.rid');
	$query_rmrk     ->  LeftJoin('users', 'u', 'fcr.remark_by_uid=u.uid');
	$query_rmrk     ->  LeftJoin('fa_employee_details', 'fed', 'u.uid=fed.uid');
	$query_rmrk		->	fields('fcr',array('sending_time','remarks','remark_by_name','remark_type'));
	$query_rmrk		->	fields('r',array('name'));
	$query_rmrk		->	fields('u',array('name'));
	$query_rmrk		->	fields('fed',array('fname'));
	$query_rmrk		-> 	condition('fcr.app_id', $application_id);
	$query_rmrk		-> 	condition('fcr.app_reference_no', $reference_no);
	$query_rmrk		-> 	condition('fcr.remarks',' ','!=');
	$query_rmrk		-> 	condition($db_or);
	$query_rmrk		-> 	orderBy('fcr.sending_time', 'ASC');
	//echo  $application_id.'----'.$reference_no.'----->'. $query_rmrk;
	$result_remark	= $query_rmrk->execute()->fetchAll();
	//echo "<pre>";	print_r($result_remark); die;

	$form['header'] = array(
		'#markup' 			=> t('<div class="content"><div class="sky-form"><h3 style="text-align: center;"><b>Approval of Plan - Application Status</b><p style="font-size:15px;" class="text-green">'.$application_no.'</p></h3><br><br>'),
	);

	$header = array(
						array('data' => 'Sl. No'),
						array('data'=> 'Designation'),
						array('data'=> 'Name'),
						array('data'=> 'Remarks'),
						array('data'=> 'Date'),
					);
					
	if(!empty($result_remark)){
		foreach($result_remark as $data){ 
			$i++;
			
			$date = date_create($data->sending_time); //die;
			$send_date = date_format($date,'M j, Y');
			
			if($data->name == 'inspector' ) {$designation = 'Inspector';}
			elseif($data->name == 'inspectorchemical' ) {$designation = 'Inspector';}
			elseif($data->name == 'deputychief' ) {$designation = 'Dy. CIF';}
			elseif($data->name == 'deputychiefchemical' ) {$designation = 'Dy. CIF Chemical';}
			elseif($data->name == 'jointchief' ) {$designation = 'Jt. CIF';}
			elseif($data->name == 'chief' ) {$designation = 'CIF';}
			elseif(trim($data->name) == 'applicant' ) {$designation = 'Applicant';}
			
			
			if($data->remark_type == 'r' ) {$remarks = $data->remarks;}
			else{$remarks = '';}
			
			$rows[] = array( 
						array('data' =>$i,'class' => array('')),
						array('data' =>$designation ,'class' => array('')),
						array('data' =>$data->remark_by_name ,'class' => array('')),
						array('data' =>$remarks ,'class' => array('')),
						array('data' =>$send_date ,'class' => array('')),
					);
		} 
	}
	
		$output = theme_table(
		array(
			  'header' => $header,
			  'rows' => $rows,
			  'attributes' => array('class' => array('table no-margin remove-odd-even# custom-table-view-dashboard')),
			 // 'sticky' => true,
			  'caption' => '',
			  'colgroups' => array(),
			  'empty' => t("No data found!") 
			)
		).theme('pager');	
	
	$form['remark_view']['show_act_div'] = array(
	   '#prefix' => '<div>'.$output,
        '#suffix' => '</div>',
     );
	 
	return $form;

}

