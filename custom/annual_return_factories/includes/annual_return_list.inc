<?php

function annual_return_list($form, &$from_state) {
	
	global $base_root, $base_path, $user;
	
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
    $form = array();
	//echo $user->uid;die();
	
	$annual_return_id = encryption_decryption_fun('encrypt', 0);
	$factory_type_id = encryption_decryption_fun('encrypt', 0);
	$factory_id = encryption_decryption_fun('encrypt', 0);
	
	$add_link = l('<i class="ace-icon fa fa-plus bigger-130 text-blue"></i> ADD NEW ANNUAL RETURN', 'applicant/annual-return-common/'.$annual_return_id.'/'.$factory_type_id.'/'.$factory_id, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));


	$form['annual_return']['markup_appplication'] = array(
		'#prefix' 	=> '<div class="row"><div class="box box-info"><div class="box-header with-border">
						<div class="col-lg-12 col-md-12 col-sm-12"><h3 class="box-title">Annual Return List</h3></div>
						<div class="box-tools pull-right">'.$add_link.'
						<button type="button" class="btn btn-box-tool" data-widget="collapse" title="Minimise"><i class="fa fa-minus"></i> </button>
						<button type="button" class="btn btn-box-tool" data-widget="remove" title="Close"><i class="fa fa-times"></i></button>
						</div>
						</div>
						<div class="box-body"><div class="col-lg-12 col-md-12 col-sm-12"><div class="table-responsive">',
		'#suffix' 	=> '</div></div></div></div></div>',
		'#type' 	=> 'markup',
		'#markup' 	=> get_all_annual_return(),
  	);		  
	return $form; 
  
}

function get_all_annual_return(){
	global $base_root,$base_path,$user;
	                                                                                                                                 
	$applicant_id 			= $user->uid;
	$get_all_data 			= array();
	$rows[] 				= array();

	$get_all_data 			= get_all_annual_return_data($applicant_id);
	
	$Wcounter				= 0;
	$per_page				= 10;
	$current_page 			= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 				= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 			= $current_page*$per_page;
	}
	$header 				= array(
								array('data'=> 'Sl. No.','width' => '8%'),
								array('data'=> 'Factory Details','width' => '30%'),
								array('data'=> 'Application No. & Date','width'  => '24%'),
								array('data'=> 'Status','width'  => '18%'),
								array('data'=> 'Action','width' => '20%','align' => 'center'),
							);
							
	if(!empty($get_all_data)){
		foreach($chunks[$current_page] as $details){ //echo "<pre>"; print_r($details);
			$Wcounter++;
			
			
			/*if($details->cafa_id != 0) {
				$get_registration_value = get_reg_lic_no($details->cafa_id);
				$factory_type_id = $get_registration_value['factory_typeid'];
				
			} else {
				$factory_type_id = 0;
				
			}*/
			
			//.'/'.encryption_decryption_fun('encrypt',$factory_type_id)
			
			$factory_id = $details->cafa_id;
			
			$get_zone_name = get_factory_zone_name($details->factory_zone);
							
			if(!empty($details->annual_return_app_no)) {
				$annual_return_app_no = $details->annual_return_app_no;	
			} else {
				$annual_return_app_no = 'Under Process';	
			}
			
			/*if(!empty($details->created_date)) {
				$created_date = date('dS M Y', strtotime($details->created_date));
			} else {
				$created_date = '';
			}*/
			
			if(!empty($details->modification_date)) {
				$modification_date = date('dS M Y', strtotime($details->modification_date));
			} else {
				$modification_date = '';
			}
			
			if($details->full_application_status == 'In') {
				$status = '<b style="color:#ff0000;">Incomplete</b>';
			} else if($details->full_application_status == 'F') {
				$status = '<b style="color:#009933;">PDFs Upload Pending</b>';		
			} else if($details->full_application_status == 'U') {
				$status = '<b style="color:#0D67A2;">Final Submitted</b>';	
			}
			
			if($details->full_application_status == 'In') {
				//, 'target' => '_blank'
				$link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> Edit', 'applicant/annual-return-common-apply/default/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt', $factory_id), array('html' => TRUE, 'attributes'=>array('title' => 'Edit', 'class'=>array(''))));
			} else if($details->full_application_status == 'F') {
				$link		 = l('<i class="fa fa-upload text-blue" aria-hidden="true"></i> Upload PDF', 'applicant/annual_return_pdf_upload/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt', $factory_id), array('html' => TRUE, 'attributes'=>array('title' => 'Upload PDF', 'class'=>array(''))));	
			} else if($details->full_application_status == 'U') {
				$link		 = l('<i class="fa fa-eye text-blue" aria-hidden="true"></i> View', 'applicant/ar-application-preview/ar_common_app_preview/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt', $factory_id), array('html' => TRUE, 'attributes'=>array('title' => 'View', 'class'=>array(''))))
								.'<br>'.
								l('<i class="fa fa-download text-blue" aria-hidden="true"></i> Download Uploaded PDF', 'applicant/annual_return_pdf_download/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$factory_id), array('html' => TRUE, 'attributes'=>array('title' => 'Download Uploaded PDF', 'class'=>array(''))));	
			}

			$rows[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' => '<b>Factory Name - </b>'.$details->factory_name.'<br><b>Zone - </b>'.$get_zone_name['zone_name'].'<br><b>Reg. No. - </b>'.$details->registration_number.'<br><b>Licence No. - </b>'.$details->licence_number,'class' => array('')),
							array('data' => $annual_return_app_no.'<br><b>Date - </b>'.$modification_date,'class' => array('')),
							array('data' => $status,'class' => array('')),
							array('data' =>$link,'class' => array('')),
						);
		} 
	} else {
			
		$rows[] = array(
						array('data' => 'No data found!', 'colspan' => 6, 'align' => 'center'),
					);	
	}
	$output = theme_table(
	array(
		  'header' 			=> $header,
		  'rows' 			=> $rows,
		  'attributes' 	=> array('class' => array('table no-margin remove-odd-even# custom-table-view-dashboard')),
		  //'attributes' 		=> array('class' => array('table table-bordered custom-table-view')),
	      'caption' 		=> '',
		  'colgroups' 		=> array(),
		  'empty' 			=> t("No data found!") 
		)
	).theme('pager');	
		 return $output;
}

