<?php
function receiving_form18_list($form, &$form_state) { 

	global $base_root,$base_path,$user;
  	drupal_add_css(drupal_get_path('module', 'notice_form') . '/css/form-design.css');
    $form = array();
	//echo $user->uid;die();
	
	$add_link		 	= l('<i class="ace-icon fa fa-plus bigger-130 text-blue"></i> ADD NEW CASE', 'applicant/form18', array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
//echo "sdsd"; die;

	$form['applicant_applicantion']['markup_appplication'] = array(
		'#prefix' 	=> '<div class="row"><div class="box box-info"><div class="box-header with-border">
						<div class="col-lg-12 col-md-12 col-sm-12"><h3 class="box-title">Application List - Notice of Accident (FORM-18)</h3></div>
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

	$get_all_data 			= get_form18_data();
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
								array('data'=> 'Factory Details','width' => '20%'),
								array('data'=> 'Accident Date','width' => '18%'),
								array('data'=> 'Type of Accident','width' => '12%'),
								array('data'=> 'Status','width'  => '18%'),
								array('data'=> 'Action','width' => '16%'),
							);
							
	if(!empty($get_all_data)){
		foreach($chunks[$current_page] as $details){ 
		
			$Wcounter++;
			
			$get_uploaded_doc = get_uploaded_document_url($details->uploaded_pdf);
			
			$download_link	 = l('<i class="fa fa-download text-blue" aria-hidden="true"></i> Download', file_create_url($get_uploaded_doc), array('html' => TRUE,'attributes'=>array('title' => 'Download', 'class'=>array(''))));
			
			$view_link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> View', 'receiving-form18-view/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->factory_id), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''), 'target' => '_blank')));
			
		     if($details->notice_status == 'RC')
			 { $status = '<b class="text-red">Pending</b>';}
			 elseif($details->notice_status == 'SC')
			 { $status = '<b class="text-blue">Forwarded to Statistical Cell</b>';}
			 elseif($details->notice_status == 'DC')
			 { $status = '<b class="text-blue">Forwarded to Dy CIF</b>';}
			 elseif($details->notice_status == 'C')
			 { $status = '<b class="text-blue">Forwarded to CIF</b>';}
			 elseif($details->notice_status == 'AI')
			 { $status = '<b class="text-blue">Forwarded to Inspector</b>';}	
			 
			if($details->accident_type == 'M')
				{	$accident_type = "Minor"; }	
			if($details->accident_type == 'S')
				{	$accident_type = "Serious"; }	
			if($details->accident_type == 'F')
				{	$accident_type = "Fatal"; }	

			$rows[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' =>'<b>Name:</b> '.$details->factory_name.'<br><b>Place:</b> '.$details->accident_place,'class' => array('')),
							array('data' =>'<b>Date:</b> '.$details->accident_date.'<br><b>Shift:</b> '.$details->accident_shift,'class' => array('')),
							array('data' =>$accident_type,'class' => array('')),
							array('data' =>$status,'class' => array()),
							array('data' =>$download_link.' '.$view_link,'class' => array()),
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