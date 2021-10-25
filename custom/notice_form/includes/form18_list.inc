<?php
function form18_list($form, &$form_state) { 

	global $base_root,$base_path,$user;
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
    $form = array();
	//echo $user->uid;die();
	$zeroparameter 	 	= encryption_decryption_fun('encrypt', 0);
	
	$add_link		 	= l('<i class="ace-icon fa fa-plus bigger-130 text-blue"></i> ADD NEW CASE', 'applicant/form18/default/'.$zeroparameter.'/'.$zeroparameter.'/'.$zeroparameter.'/'.$zeroparameter, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
//echo "sdsd"; die;

	$form['applicant_applicantion']['markup_appplication'] = array(
		'#prefix' 	=> '<div class="row"><div class="box box-info"><div class="box-header with-border">
						<div class="col-lg-12 col-md-12 col-sm-12"><h3 class="box-title">Application List - Notice of Accident (FORM-18)</h3></div>
						<div class="box-tools pull-right">'.$add_link.'
						<button type="button" class="btn btn-box-tool" data-widget="collapse" title="Minimise"><i class="fa fa-minus"></i> </button>
						<button type="button" class="btn btn-box-tool" data-widget="remove" title="Close"><i class="fa fa-times"></i></button>
						</div>
						</div>
						<div class="box-body"><div class="col-lg-12 col-md-12 col-sm-12"><div class="table-responsive">',
		'#suffix' 	=> '</div></div></div></div></div>',
		'#type' 	=> 'markup',
		'#markup' 	=> get_all_notice_accident(),
  	);		  
	return $form; 
  
}

function get_all_notice_accident(){
	global $base_root,$base_path,$user;
	                                                                                                                                 
	$applicant_id 			= $user->uid;
	$get_all_data 			= array();
	$rows[] 				= array();

	$get_all_data 			= get_all_notice_accident_data($applicant_id);
	//print_r($get_all_data);
	
	$Wcounter				= 0;
	$per_page				= 10;
	$current_page 			= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 				= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 			= $current_page*$per_page;
	}
	$header 				= array(
								array('data'=> 'Sl. No.','width' => '6%'),
								array('data'=> 'Factory Name','width' => '26%'),
								array('data'=> 'Nature of Industry','width' => '22%'),
								array('data'=> 'Case Identification No.','width' => '20%'),
								array('data'=> 'Accident Type','width'  => '12%'),
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
				$link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> Upload Form', 'applicant/form18-upload/'.encryption_decryption_fun('encrypt',$form_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$service_id), array('html' => TRUE,'attributes'=>array('title' => 'Upload Form', 'class'=>array(''), 'target' => '_blank')));
			 } elseif($details->notice_status == 'RC')
			 {
			
			$get_uploaded_doc = get_caf_upload_doc_details($form_id, $service_id, 'FORM18', $factory_type_id, $reference_no);
			
			 $download_link = l('<i class="fa fa-download" aria-hidden="true"></i> Download','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $get_uploaded_doc->id).'/'.encryption_decryption_fun('encrypt', 'FORM18').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
				
			 $view_link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> View', 'applicant/form18-view/'.encryption_decryption_fun('encrypt',$form_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$service_id), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''), 'target' => '_blank')));
				$link		 = $download_link.' '.$view_link;
				
			 }else{
			    $link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> Edit', 'applicant/form18/default/'.encryption_decryption_fun('encrypt',$form_id).'/'.encryption_decryption_fun('encrypt',$reference_no).'/'.encryption_decryption_fun('encrypt',$factory_type_id).'/'.encryption_decryption_fun('encrypt',$service_id), array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array(''), 'target' => '_blank')));
			 }
			
	 //$data_result = db_query("SELECT count(*) FROM {fa_dangerous_occurrence_form18} where dangerous_occurrence_id = '$details->id'")->fetchObject()->count; die;

				if($details->accident_type == 'F'){
					$accident_type = '<b class="text-blue">Fatal</b>';
				}else if($details->accident_type == 'M'){
					$accident_type = '<b class="text-blue">Minor</b>';
				}else if($details->accident_type == 'S'){
					$accident_type = '<b class="text-blue">Serious</b>';
				}

			$rows[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' =>$details->factory_name,'class' => array('')),
							array('data' =>$details->industry_nature ,'class' => array('')),
							array('data' =>$details->case_identification_number ,'class' => array('')),
							array('data' =>$accident_type,'class' => array('')),
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