<?php
function statistical_list($form, &$form_state) {

	//global $base_root,$base_path,$user;
  	//drupal_add_css(drupal_get_path('module', 'notice_form') . '/css/form-design.css');
    //$form = array();
	
		global $base_root, $base_path, $user;
		
		$value_ar_year = isset($form_state['values']['ar_year']) ? $form_state['values']['ar_year'] : '';
		$value_ar_licence_no = isset($form_state['values']['ar_licence_no']) ? $form_state['values']['ar_licence_no'] : '';
		$value_ar_registration_no = isset($form_state['values']['ar_registration_no']) ? $form_state['values']['ar_registration_no'] : '';
		$value_ar_factory_name = isset($form_state['values']['ar_factory_name']) ? $form_state['values']['ar_factory_name'] : '';
		
		$form = array();
		
		$form['markup_ar_list_start'] = array(
			'#prefix' 	=> '<div class="row"><div class="box box-info">
							<div class="box-header with-border">
							<h3 class="box-title">Final Submitted Notice List</h3>
							<div class="box-tools pull-right">
							<button type="button" class="btn btn-box-tool" data-widget="collapse"><i class="fa fa-minus"></i> </button>
							<button type="button" class="btn btn-box-tool" data-widget="remove"><i class="fa fa-times"></i></button>
							</div>
							</div>
							<div class="box-body"><div class="table-responsive">',
			'#suffix' 	=> ''
		);
		
		$form['ar_year'] = array(
			'#type' 			=> 'select',
			'#prefix' 			=> '<div class="col-md-3 col-xs-3">',
			'#suffix' 			=> '</div>',
			'#title' 			=> t('1. Year'),
			'#attributes' 		=> array('class' => array('')),
			'#options' 			=> get_year_list(),
			'#required' 		=> TRUE,
		);
		
		$form['ar_licence_no'] = array(
			'#type' 				=> 'textfield',
			'#prefix' 				=> '<div class="col-md-4 col-xs-4">',
			'#suffix' 				=> '</div>',
			'#title' 				=> t('2. Licence No.'),
			'#attributes' 			=> array('class' => array('numeric_positive'), 'placeholder' => 'Licence No.'),
			'#autocomplete_path'	=> 'licenceno_autocomplete',
			'#element_validate' 	=> array('element_validate_numeric_positive'),
		);
		
		$form['ar_registration_no'] = array(
			'#type' 				=> 'textfield',
			'#prefix' 				=> '<div class="col-md-4 col-xs-4">',
			'#suffix' 				=> '</div>',
			'#title' 				=> t('3. Registration No.'),
			'#attributes' 			=> array('class' => array(''), 'placeholder' => 'Registration No.'),
			'#autocomplete_path'	=> 'registrationno_autocomplete',
			'#element_validate' 	=> array('element_validate_factory_reg_no'),
		);
		
		$form['ar_factory_name'] = array(
			'#type' 				=> 'textfield',
			'#prefix' 				=> '<div class="col-md-6 col-xs-6">',
			'#suffix' 				=> '</div>',
			'#title' 				=> t('4. Factory Name'),
			'#attributes' 			=> array('class' => array(''), 'placeholder' => 'Factory Name'),
			'#autocomplete_path'	=> 'factoryname_autocomplete',
			'#element_validate' 	=> array('element_validate_factory_name'),
		);
		
		$form['ar_list_search_submit'] = array (
			'#type' 		=> 'submit',
			'#value'		=> 'Search',
			'#prefix' 		=> '<div class="col-md-7 col-xs-7">',  
			'#suffix' 		=> '</div>',
			'#attributes' 	=> array('class' => array('btn btn-info')),
		);
		
		$form['reset'] = array(
			'#markup' => l(t('Reset'), 'statistical-list', array(
				'html' => TRUE,
				'attributes' => array('class' => array('btn btn-outline-dark pull-right'))
			)),
			'#prefix' 		=> '<div class="col-md-5 col-xs-5">',  
			'#suffix' 		=> '</div>',
		);
		
		if($value_ar_year != '') {
			$form['annual_return_list'] = array(
				'#prefix' 	=> '<div class="col-lg-12 col-md-12 col-sm-12">',
				'#suffix' 	=> '</div>',
				'#type' 	=> 'markup',
				'#markup' 	=> get_annual_return_statistical($value_ar_year, $value_ar_licence_no, $value_ar_registration_no, $value_ar_factory_name),
			);
		} else {
			$form['annual_return_list'] = array(
				'#prefix' 	=> '<div class="col-lg-12 col-md-12 col-sm-12">',
				'#suffix' 	=> '</div>',
				'#type' 	=> 'markup',
				'#markup' 	=> get_all_notice(),
			);	
		}
		
		$form['markup_ar_list_end'] = array(
			'#prefix' 	=> '',
			'#suffix' 	=> '</div></div></div></div>',
		);
		
		
		return $form;
	  

	
	
	
	
	
	//echo $user->uid;die();
	
	/*$add_link		 	= l('<i class="ace-icon fa fa-plus bigger-130 text-blue"></i> ADD NEW CASE', 'applicant/form19', array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));

	$form['applicant_applicantion']['markup_appplication'] = array(
		'#prefix' 	=> '<div class="row"><div class="box box-info"><div class="box-header with-border">
						<div class="col-lg-12 col-md-12 col-sm-12"><h3 class="box-title">Application List - Dangerous Occurance (FORM-19)</h3></div>
						<div class="box-tools pull-right">'.$add_link.'
						<button type="button" class="btn btn-box-tool" data-widget="collapse" title="Minimise"><i class="fa fa-minus"></i> </button>
						<button type="button" class="btn btn-box-tool" data-widget="remove" title="Close"><i class="fa fa-times"></i></button>
						</div>
						</div>
						<div class="box-body"><div class="col-lg-12 col-md-12 col-sm-12"><div class="table-responsive">',
		'#suffix' 	=> '</div></div></div></div></div>',
		'#type' 	=> 'markup',
		'#markup' 	=> get_all_notice(),
  	);		  
	return $form;*/
  
}

function get_all_occurrence(){
	global $base_root,$base_path,$user;
	                                                                                                                                 
	$applicant_id 			= $user->uid;
	$get_all_data 			= array();
	$rows[] 				= array();

	$get_all_data 			= get_all_occurrence_data($applicant_id);
	
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
								array('data'=> 'Factory Name','width' => '16%'),
								array('data'=> 'Nature of Industry','width' => '16%'),
								array('data'=> 'Date of occurrence','width' => '14%'),
								array('data'=> 'Time of occurrence','width' => '14%'),
								array('data'=> 'Action','width' => '14%'),
							);
							
	if(!empty($get_all_data)){
		foreach($chunks[$current_page] as $details){ //echo "<pre>"; print_r($details);
			$Wcounter++;
			
			$get_uploaded_doc = get_uploaded_document_url($details->uploaded_pdf);
			
			 if($details->notice_status == 'In')
			 {
				$link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> Upload Form', 'applicant/form19-upload/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->factory_id), array('html' => TRUE,'attributes'=>array('title' => 'Upload Form', 'class'=>array(''))));//, 'target' => '_blank'
			 } elseif($details->notice_status == 'AI')
			 {
				$download_link		 = l('<i class="fa fa-download text-blue" aria-hidden="true"></i> Download', file_create_url($get_uploaded_doc), array('html' => TRUE,'attributes'=>array('title' => 'Download', 'class'=>array(''))));
				
				$view_link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> View', 'applicant/form19-view/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->factory_id), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''))));//, 'target' => '_blank'
				$link		 = $download_link.' '.$view_link;
				
			 }else{
				$link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> Edit', 'applicant/form19/default/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->factory_id), array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array(''))));//, 'target' => '_blank'
			 }

	$data_result = db_query("SELECT count(*) FROM {fa_form19_dangerous_occurrence_case_witness} where dangerous_occurrence_id = '$details->id'")->fetchObject()->count;

			$rows[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' =>$details->factory_name,'class' => array('')),
							array('data' =>ucfirst($details->industry_nature) ,'class' => array('')),
							array('data' =>$details->date_occurrence,'class' => array('')),
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






function get_all_notice(){
	global $base_root,$base_path,$user;
	                                                                                                                                 
	$Wcounter				= 0;
	$per_page				= 2;
	
	//********************** FORM 18
	
	$get_all_data18 		= array();
	$rows18[] 				= array();
	$get_all_data18 		= form18_data();
	
	$current_page18 		= pager_default_initialize(count($get_all_data18), $per_page);
	
	$chunks 				= array_chunk($get_all_data18, $per_page, TRUE);
	if($current_page18>0){
		$Wcounter 			= $current_page18*$per_page;
	}
	$header18 				= array(
								array('data'=> 'Sl. No.','width' => '6%'),
								array('data'=> 'Factory Details','width' => '20%'),
								array('data'=> 'Accident Date','width' => '18%'),
								array('data'=> 'Type of Accident','width' => '12%'),
								array('data'=> 'Status','width'  => '18%'),
								array('data'=> 'Action','width' => '16%'),
							);
							
	if(!empty($get_all_data18)){
		foreach($chunks[$current_page18] as $details){ //echo "<pre>"; print_r($details);
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
			 elseif($details->notice_status == 'AI')
			 { $status = '<b class="text-blue">Forwarded to Inspector</b>';}	
			 
			if($details->accident_type == 'M')
				{	$accident_type = "Minor"; }	
			if($details->accident_type == 'S')
				{	$accident_type = "Serious"; }	
			if($details->accident_type == 'F')
				{	$accident_type = "Fatal"; }	

			$rows18[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' =>'<b>Name:</b> '.$details->factory_name.'<br><b>Place:</b> '.$details->accident_place,'class' => array('')),
							array('data' =>'<b>Date:</b> '.$details->accident_date.'<br><b>Shift:</b> '.$details->accident_shift,'class' => array('')),
							array('data' =>$accident_type,'class' => array('')),
							array('data' =>$status,'class' => array()),
							array('data' =>$download_link.' '.$view_link,'class' => array()),
						);
		} 
	}
	
	$output18 = theme_table(
	array(
		  'header' 			=> $header18,
		  'rows' 			=> $rows18,
		  'attributes' 	=> array('class' => array('table no-margin remove-odd-even# custom-table-view-dashboard')),
		  //'attributes' 		=> array('class' => array('table table-bordered custom-table-view')),
	      'caption' 		=> '',
		  'colgroups' 		=> array(),
		  'empty' 			=> t("No data found!") 
		)
	).theme('pager');


	//********************** FORM 19
	
	$get_all_data19 		= array();
	$rows19[] 				= array();
	$get_all_data19 		= form19_data();
	
	$current_page19 		= pager_default_initialize(count($get_all_data19), $per_page);
	
	$chunks 				= array_chunk($get_all_data19, $per_page, TRUE);
	if($current_page19>0){
		$Wcounter 			= $current_page19*$per_page;
	}
	$header19 				= array(
								array('data'=> 'Sl. No.','width' => '6%'),
								array('data'=> 'Factory Name','width' => '16%'),
								array('data'=> 'Branch Name','width' => '16%'),
								array('data'=> 'Date of occurrence','width' => '14%'),
								array('data'=> 'Time of occurrence','width' => '14%'),
								array('data'=> 'Status','width' => '14%'),
								array('data'=> 'Action','width' => '14%'),
							);
							
	if(!empty($get_all_data19)){
		foreach($chunks[$current_page19] as $details){ //echo "<pre>"; print_r($details);
			$Wcounter++;
			
			$get_uploaded_doc = get_uploaded_document_url($details->uploaded_pdf);
			
			$download_link	 = l('<i class="fa fa-download text-blue" aria-hidden="true"></i> Download', file_create_url($get_uploaded_doc), array('html' => TRUE,'attributes'=>array('title' => 'Download', 'class'=>array(''))));
			
			$view_link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> View', 'receiving-form19-view/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->factory_id), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''), 'target' => '_blank')));

		     if($details->notice_status == 'RC')
			 { $status = '<b class="text-red">Pending</b>';}
			 elseif($details->notice_status == 'SC')
			 { $status = '<b class="text-blue">Forwarded to Statistical Cell</b>';}
			 elseif($details->notice_status == 'DC')
			 { $status = '<b class="text-blue">Forwarded to Dy CIF</b>';}
			 elseif($details->notice_status == 'AI')
			 { $status = '<b class="text-blue">Forwarded to Inspector</b>';}	

			$rows19[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' =>$details->factory_name,'class' => array('')),
							array('data' =>$details->branch_name ,'class' => array('')),
							array('data' =>$details->date_occurrence,'class' => array('')),
							array('data' =>$details->time_occurrence,'class' => array('')),
							array('data' =>$status,'class' => array('color','red')),
							array('data' =>$download_link.' '.$view_link,'class' => array('')),
						);
		} 
	}
	
	$output19 = theme_table(
	array(
		  'header' 			=> $header19,
		  'rows' 			=> $rows19,
		  'attributes' 	=> array('class' => array('table no-margin remove-odd-even# custom-table-view-dashboard')),
		  //'attributes' 		=> array('class' => array('table table-bordered custom-table-view')),
	      'caption' 		=> '',
		  'colgroups' 		=> array(),
		  'empty' 			=> t("No data found!") 
		)
	).theme('pager');
	
	
	//********************** FORM 20
	
	$get_all_data20 		= array();
	$rows20[] 				= array();
	$get_all_data20 		= form20_data();
	
	$current_page20 		= pager_default_initialize(count($get_all_data20), $per_page);
	
	$chunks 				= array_chunk($get_all_data20, $per_page, TRUE);
	if($current_page20>0){
		$Wcounter 			= $current_page20*$per_page;
	}
	$header20 				= array(
								array('data'=> 'Sl. No.','width' => '6%'),
								array('data'=> 'Factory Name','width' => '22%'),
								array('data'=> 'Nature of Industry','width' => '22%'),
								array('data'=> 'No. of Patient','width'  => '13%'),
								array('data'=> 'Status','width' => '21%'),
								array('data'=> 'Action','width' => '14%'),
							);
							
	if(!empty($get_all_data20)){
		foreach($chunks[$current_page20] as $details){ //echo "<pre>"; print_r($details);
			$Wcounter++;
			
			$get_uploaded_doc = get_uploaded_document_url($details->uploaded_pdf);
			$patientCount     = db_query("SELECT count(*) FROM {fa_form20_patient_details} where notice_poisoning_id = '$details->id'")->fetchObject()->count;
			
			$download_link	 = l('<i class="fa fa-download text-blue" aria-hidden="true"></i> Download', file_create_url($get_uploaded_doc), array('html' => TRUE,'attributes'=>array('title' => 'Download', 'class'=>array(''))));
			
			$view_link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> View', 'receiving-form20-view/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->factory_id), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''), 'target' => '_blank')));

		     if($details->notice_status == 'RC')
			 { $status = '<b class="text-red">Pending</b>';}
			 elseif($details->notice_status == 'SC')
			 { $status = '<b class="text-blue">Forwarded to Statistical Cell</b>';}
			 elseif($details->notice_status == 'DC')
			 { $status = '<b class="text-blue">Forwarded to Dy CIF</b>';}
			 elseif($details->notice_status == 'AI')
			 { $status = '<b class="text-blue">Forwarded to Inspector</b>';}	

			$rows20[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' =>$details->factory_name,'class' => array('')),
							array('data' =>ucfirst($details->industry_nature),'class' => array('')),
							array('data' =>$patientCount,'class' => array('')),
							array('data' =>$status ,'class' => array('')),
							array('data' =>$download_link.' '.$view_link,'class' => array('')),
						);
		} 
	}
	
	$output20 = theme_table(
	array(
		  'header' 			=> $header20,
		  'rows' 			=> $rows20,
		  'attributes' 	=> array('class' => array('table no-margin remove-odd-even# custom-table-view-dashboard')),
		  //'attributes' 		=> array('class' => array('table table-bordered custom-table-view')),
	      'caption' 		=> '',
		  'colgroups' 		=> array(),
		  'empty' 			=> t("No data found!") 
		)
	).theme('pager');
		
		 return $output18.$output19.$output20;
} 
  
function form18_data()								// TO SHOW ALL DATA IN LIST
{	
    $fetch_details	= db_select('fa_form18_notice_accident', 'f18');
	$fetch_details	->fields('f18', array());
	$fetch_details	->orderBy('id', 'DESC');
	echo $fetch_details	->condition('f18.notice_status','SC','=');
	$d_result = $fetch_details->execute()->fetchAll(); 
	return $d_result;
}
function form19_data()                            // TO SHOW ALL DATA IN LIST 
{									
	$fetch_details	= db_select('fa_form19_dangerous_occurrence', 'f19');
	$fetch_details	->fields('f19', array());
	$fetch_details	->orderBy('id', 'DESC');
	echo $fetch_details	->condition('f19.notice_status','SC','=');
	$details_result = $fetch_details->execute()->fetchAll(); 
	
	return $details_result;
}
function form20_data()                            // TO SHOW ALL DATA IN LIST
{									
	$fetch_details	= db_select('fa_form20_notice_poisoning', 'f20');
	$fetch_details	->fields('f20', array());
	$fetch_details	->orderBy('id', 'DESC');
	echo $fetch_details	->condition('f20.notice_status','SC','=');
	$details_result = $fetch_details->execute()->fetchAll(); 
	return $details_result;
}



?>