<?php

	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	
	function statistical_annual_return_list_form($form, &$form_state) {
		
		global $base_root, $base_path, $user;
		
		$value_ar_year = isset($form_state['values']['ar_year']) ? $form_state['values']['ar_year'] : '';
		$value_ar_licence_no = isset($form_state['values']['ar_licence_no']) ? $form_state['values']['ar_licence_no'] : '';
		$value_ar_registration_no = isset($form_state['values']['ar_registration_no']) ? $form_state['values']['ar_registration_no'] : '';
		$value_ar_factory_name = isset($form_state['values']['ar_factory_name']) ? $form_state['values']['ar_factory_name'] : '';
		
		$form = array();
		
		$form['markup_ar_list_start'] = array(
			'#prefix' 	=> '<div class="row"><div class="box box-info">
							<div class="box-header with-border">
							<h3 class="box-title">Final Submitted Annual Return List</h3>
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
			'#markup' => l(t('Reset'), 'statistical-annual-return-list', array(
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
				'#markup' 	=> get_annual_return_statistical(),
			);	
		}
		
		$form['markup_ar_list_end'] = array(
			'#prefix' 	=> '',
			'#suffix' 	=> '</div></div></div></div>',
		);
		
		
		return $form; 
	  
	}
	
	function statistical_annual_return_list_form_submit($form, &$form_state) {
		$form_state['rebuild'] = TRUE;
	}


	function get_annual_return_statistical($ar_year = '', $ar_licence_no = '', $ar_registration_no = '', $ar_factory_name = ''){
		global $base_root, $base_path, $user;
		
		$year = $ar_year;
		$licence_no = $ar_licence_no;
		$registration_no = $ar_registration_no;
		$factory_name = $ar_factory_name;
		
		$get_all_data 			= array();
		$rows[] 				= array();
		
		$service_details 		= get_service_details();
		$service_id 			= $service_details->id;
		
		$get_all_data 			= get_all_annual_return_data_statistical($service_id, $year, $licence_no, $registration_no, $factory_name);
		
		$Wcounter				= 0;
		$per_page				= 10;
		$current_page 			= pager_default_initialize(count($get_all_data), $per_page);
		
		$chunks 				= array_chunk($get_all_data, $per_page, TRUE);
		if($current_page>0){
			$Wcounter 			= $current_page*$per_page;
		}
		$header 				= array(
									array('data'=> 'Sl. No.','width' => '5%'),
									array('data'=> 'Factory Details','width' => '30%'),
									array('data'=> 'Service','width' => '20%'),
									array('data'=> 'Application No. & Date','width'  => '30%'),
									array('data'=> 'Status','width'  => '15%'),
									//array('data'=> 'Action','width' => '25%'),
								);
								
		if(!empty($get_all_data)){
			foreach($chunks[$current_page] as $details) { //echo "<pre>"; print_r($details);
				$Wcounter++;
				
				$factory_id = $details->cafa_id;
				
				/*if($details->full_application_status == 'U') {
					$link		 = l('<i class="fa fa-eye text-blue" aria-hidden="true"></i> View', 'applicant/ar-application-preview/ar_common_app_preview/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt', $factory_id), array('html' => TRUE, 'attributes'=>array('title' => 'View', 'class'=>array(''))))
									.'&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'.
									l('<i class="fa fa-download text-blue" aria-hidden="true"></i> Download Uploaded PDF', 'applicant/annual_return_pdf_download/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$factory_id), array('html' => TRUE, 'attributes'=>array('title' => 'Download Uploaded PDF', 'class'=>array(''))));	
				}*/
				
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
				
				$rows[] = array( 
								array('data' => $Wcounter,'class' => array('')),
								array('data' => '<b>Factory Name - </b>'.$details->factory_name.'<br><b>Zone - </b>'.$get_zone_name['zone_name'].'<br><b>Reg. No. - </b>'.$details->registration_number.'<br><b>Licence No. - </b>'.$details->licence_number,'class' => array('')),
								array('data' => 'Annual Return','class' => array('')),
								array('data' => $annual_return_app_no.'<br><b>Date - </b>'.$modification_date,'class' => array('')),
								array('data' => $status,'class' => array('')),
								//array('data' =>$link,'class' => array('')),
							);
			} 
		} else {
			
			$rows[] = array(
							array('data' => 'No data found!', 'colspan' => 5, 'align' => 'center'),
						);	
		}
		
		$output = theme_table(
		array(
			  'header' 			=> $header,
			  'rows' 			=> $rows,
			  'attributes' 		=> array('class' => array('table no-margin remove-odd-even# custom-table-view-dashboard')),
			  //'attributes' 		=> array('class' => array('table table-bordered custom-table-view')),
			  'sticky' 			=> true,
			  'caption' 		=> '',
			  'colgroups' 		=> array(),
			  'empty' 			=> t("No data found!") 
			)
		).theme('pager');	
		
		return $output;
	}

