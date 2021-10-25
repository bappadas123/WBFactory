<?php
function form19_list($form, &$form_state) {

	global $base_root,$base_path,$user;
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
    $form = array();
	//echo $user->uid;die();
		  
	$zeroparameter 	 	= encryption_decryption_fun('encrypt', 0);

	$add_link		 	= l('<i class="ace-icon fa fa-plus bigger-130 text-blue"></i> ADD NEW CASE', 'applicant/form19/default/'.$zeroparameter.'/'.$zeroparameter.'/'.$zeroparameter.'/'.$zeroparameter, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));


	$form['applicant_applicantion']['markup_appplication'] = array(
		'#prefix' 	=> '<div class="row"><div class="box box-info"><div class="box-header with-border">
						<div class="col-lg-12 col-md-12 col-sm-12"><h3 class="box-title">Application List - Dangerous Occurrence (FORM-19)</h3></div>
						<div class="box-tools pull-right">'.$add_link.'
						<button type="button" class="btn btn-box-tool" data-widget="collapse" title="Minimise"><i class="fa fa-minus"></i> </button>
						<button type="button" class="btn btn-box-tool" data-widget="remove" title="Close"><i class="fa fa-times"></i></button>
						</div>
						</div>
						<div class="box-body"><div class="col-lg-12 col-md-12 col-sm-12"><div class="table-responsive">',
		'#suffix' 	=> '</div></div></div></div></div>',
		'#type' 	=> 'markup',
		'#markup' 	=> get_all_occurrence(),
  	);		  
	return $form; 
  
}

function get_all_occurrence(){
	global $base_root,$base_path,$user;
	                                                                                                                                 
	$applicant_id 			= $user->uid;
	$get_all_data 			= array();
	$rows[] 				= array();

	$get_all_data 			= get_all_occurrence_data($applicant_id);
	
	$Wcounter				= 0;
	$per_page				= 10;
	$current_page 			= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 				= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 			= $current_page*$per_page;
	}
	$header 				= array(
								array('data'=> 'Sl. No.','width' => '6%'),
								array('data'=> 'Factory Name','width' => '21%'),
								array('data'=> 'Nature of Industry','width' => '16%'),
								array('data'=> 'Case Identification No.','width' => '15%'),
								array('data'=> 'Date of occurrence','width' => '14%'),
								array('data'=> 'Time of occurrence','width' => '14%'),
								array('data'=> 'Action','width' => '14%'),
							);
							
	if(!empty($get_all_data)){
		foreach($chunks[$current_page] as $details){ //echo "<pre>"; print_r($details);
			$Wcounter++;
				
				$form_id   = $details->id;
				$service_id       = $details->service_id;
				$factory_type_id  = $details->factory_typeid;
				$reference_no     = $details->reference_number;

			
			$get_uploaded_doc = get_uploaded_document_url($details->uploaded_pdf);
			
			 if($details->notice_status == 'In')
			 {
				$link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> Upload Form', 'applicant/form19-upload/'.encryption_decryption_fun('encrypt',$form_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$service_id), array('html' => TRUE,'attributes'=>array('title' => 'Upload Form', 'class'=>array(''), 'target' => '_blank')));
			 } elseif($details->notice_status == 'RC')
			 {
			
			$get_uploaded_doc = get_caf_upload_doc_details($form_id, $service_id, 'FORM19', $factory_type_id, $reference_no);
			
			 $download_link = l('<i class="fa fa-download" aria-hidden="true"></i> Download','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $get_uploaded_doc->id).'/'.encryption_decryption_fun('encrypt', 'FORM18').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
				
			 $view_link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> View', 'applicant/form19-view/'.encryption_decryption_fun('encrypt',$form_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$service_id), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''), 'target' => '_blank')));
				$link		 = $download_link.' '.$view_link;
				
			 }else{
			    $link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> Edit', 'applicant/form19/default/'.encryption_decryption_fun('encrypt',$form_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$service_id), array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array(''), 'target' => '_blank')));
			 }

	//$data_result = db_query("SELECT count(*) FROM {fa_form19_dangerous_occurrence_case_witness} where dangerous_occurrence_id = '$details->id'")->fetchObject()->count;

			$rows[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' =>$details->factory_name,'class' => array('')),
							array('data' =>ucfirst($details->industry_nature) ,'class' => array('')),
							array('data' =>$details->case_identification_number ,'class' => array('')),
							array('data' =>date('d-m-Y',strtotime($details->date_occurrence)),'class' => array('')),
							array('data' =>$details->time_occurrence,'class' => array('')),
							array('data' =>$link,'class' => array('')),
						);
		} 
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


?>