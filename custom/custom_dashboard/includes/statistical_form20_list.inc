<?php
function statistical_form20_list($form, &$form_state) {

	//global $base_root,$base_path,$user;
  	//drupal_add_css(drupal_get_path('module', 'notice_form') . '/css/form-design.css');
    //$form = array();
	
		global $base_root, $base_path, $user;
		
		$value_ar_year = isset($form_state['values']['ar_year']) ? $form_state['values']['ar_year'] : '';
		$value_ar_licence_no = isset($form_state['values']['ar_licence_no']) ? $form_state['values']['ar_licence_no'] : '';
		$value_ar_registration_no = isset($form_state['values']['ar_registration_no']) ? $form_state['values']['ar_registration_no'] : '';
		$value_ar_factory_name = isset($form_state['values']['ar_factory_name']) ? $form_state['values']['ar_factory_name'] : '';
		
		$form = array();
		
		/*$form['markup_ar_list_start'] = array(
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
		
		
		return $form;*/
	  	
	$form['applicant_applicantion']['markup_appplication'] = array(
		'#prefix' 	=> '<div class="row"><div class="box box-info"><div class="box-header with-border">
						<div class="col-lg-12 col-md-12 col-sm-12"><h3 class="box-title">Application List - Notice of Poisioning (FORM-20)</h3></div>
						</div>
						<div class="box-body"><div class="col-lg-12 col-md-12 col-sm-12"><div class="table-responsive">',
		'#suffix' 	=> '</div></div></div></div></div>',
		'#type' 	=> 'markup',
		'#markup' 	=> get_all_notice(),
  	);		  
	return $form;
  
}

function get_all_notice(){
	global $base_root,$base_path,$user;
	                                                                                                                                 
	$Wcounter				= 0;
	$per_page				= 2;
	
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
								//array('data'=> 'Status','width' => '21%'),
								array('data'=> 'Action','width' => '14%'),
							);
							
	if(!empty($get_all_data20)){
		foreach($chunks[$current_page20] as $details){ //echo "<pre>"; print_r($details);
			$Wcounter++;
			
			$get_uploaded_doc = get_uploaded_document_url($details->uploaded_pdf);
			$patientCount     = db_query("SELECT count(*) FROM {fa_form20_patient_details} where notice_poisoning_id = '$details->id'")->fetchObject()->count;
			
			$download_link	 = l('<i class="fa fa-download text-blue" aria-hidden="true"></i> Download', file_create_url($get_uploaded_doc), array('html' => TRUE,'attributes'=>array('title' => 'Download', 'class'=>array(''))));
			
			$view_link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> View', 'statistical-form20-view/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->factory_id), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''), 'target' => '_blank')));

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
							//array('data' =>$status ,'class' => array('')),
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
		
		 return $output20;
} 
  
function form20_data()                            // TO SHOW ALL DATA IN LIST
{									
	$fetch_details	= db_select('fa_form20_notice_poisoning', 'f20');
	$fetch_details	->fields('f20', array());
	$fetch_details	->orderBy('id', 'DESC');
 $fetch_details	->condition('f20.notice_status','SC','=');
	$details_result = $fetch_details->execute()->fetchAll(); 
	return $details_result;
}



?>