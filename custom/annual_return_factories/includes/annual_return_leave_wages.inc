<?php

  	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
  	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
  
	function annual_return_leave_wages($form, &$form_state, $annual_returnID = '', $factoryID = ''){
	  
		global $user;
		$uid 						= $user->uid;
	  
	 	$annual_return_ID = encryption_decryption_fun('decrypt', $annual_returnID);
		//$factory_type_id = encryption_decryption_fun('decrypt', $factory_typeID);
    	$factory_id = encryption_decryption_fun('decrypt', $factoryID);
	
		$get_factory_info = get_annual_return_factory_information($annual_return_ID);

	//This section only for get factory_typeid for sending to annual-return-common
	
		$factory_typeID = encryption_decryption_fun('encrypt', $get_factory_info->factory_typeid);
	//end
		
		if(empty($annual_return_ID) || /*$factory_id == 0 ||*/ $annual_return_ID == '') {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Factory Information first.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/annual-return-common/'.$annual_returnID.'/'.$factory_typeID.'/'.$factoryID) ;
		}
		
		$get_worker_details_mandays = get_worker_details_mandays($annual_return_ID);
		$get_worker_details_avg_daily = get_worker_details_avg_daily($annual_return_ID);
		if($get_worker_details_mandays->annual_return_id == NULL && $get_worker_details_avg_daily->annual_return_id == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/annual-return-common-apply/workers_details/'.$annual_returnID.'/'.$factoryID) ;
		}
		
		
		$get_leave_wages_details = get_leave_wages_details($annual_return_ID);
		
		$get_wages_paid_include_deduction = get_total_wages_paid_include_deduction($annual_return_ID);
		$get_disbursement_fine_funds = get_disbursement_fine_funds($annual_return_ID);
		$get_factory_act_all_data = get_factory_act_all_data($annual_return_ID);
		$get_maternity_benefit_all_data = get_maternity_benefit_all_data($annual_return_ID);
		
		if($get_factory_info->payment_wages_flag == 1 && $get_wages_paid_include_deduction->annual_return_id != NULL && $get_disbursement_fine_funds->annual_return_id != NULL) {
			$payment_wages_edit = l('Payment of Wages Edit', 'applicant/payment-of-wages/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		} else {
			$payment_wages_edit = '';
		}
		
		if($get_factory_info->factories_act_flag == 1 && $get_factory_act_all_data->ar_id != NULL) {
			$factories_act_edit = l('Factories Rules Edit', 'applicant/factories-act-apply/dangerous_operation/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		} else {
			$factories_act_edit = '';
		}
		
		if($get_factory_info->maternity_benefit_flag == 1 && $get_maternity_benefit_all_data->ar_id != NULL) {
			$maternity_benefit_edit = l('Maternity Benefit Edit', 'applicant/maternity-benefit-apply/medical_officer/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		} else {
			$maternity_benefit_edit = '';
		}
		
		//echo '<pre>'; print_r($get_leave_wages_details); die();
	  
		$form = array();
  
		$form['annual_return_id'] = array(
				'#prefix' 			=> '<div id="annual_return_id"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#type' 			=> 'hidden',
				'#default_value' 	=> !empty($annual_return_ID) ? $annual_return_ID : '',
		);
		
		$form['factory_id'] = array(
				'#prefix' 			=> '<div id="factory_type_id"><label class="input label-block">',
				'#suffix' 			=> '</label></div>',
				'#type' 			=> 'hidden',
				'#default_value' 	=> $factory_id,
		);
		
		/*$form['leave_wages_markup'] = array(
				
				'#type'		=> 'markup',
				'#prefix'	=> '<div class="row">
									<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
										<font color="#FF0000">**</font>N.B. Please fill the fields if you submit the Factories Rules Return or Maternity Benefit Return or both else leave as 0 (Zero).',
				'#suffix' => '		</div>
								</div>',
		);*/
		
		$form['tot_no_workers_employed_year'] = array(
			'#type' 		=> 'fieldset',
			'#title' 		=> t('7. Total number of workers employed during the year'),
			'#collapsible' 	=> TRUE, // Added
			'#collapsed' 	=> FALSE // Added
		);
		$form['tot_no_workers_employed_year']['tot_no_workers_year_previous_table'] 	= array(
				
				'#type'		=> 'markup',
				'#prefix'	=> '<div class="row">
				<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
								
					<table class="custom-table-view-dashboard renewal-table">
						<tr>
							<th colspan="3">Permanent</th>
							<th colspan="3">Contractual (Including daily wages)</th>
						</tr>
						<tr>
							<th >Men</th>
							<th >Women</th> 
							<th >Children</th>
							<th >Men</th>
							<th >Women</th> 
							<th >Children</th>
						</tr>'
				
	  
		 );
		 
		$form['tot_no_workers_employed_year']['tot_no_workers_year_per_men'] = array(
					'#prefix' 			=> '<tr><td><div class="col-xs-12">',
					'#suffix' 	 		=> '</div></td>',
					'#title'			=>	t('Men'),
					'#type' 			=> 'textfield',
					'#default_value'	=> !empty($get_leave_wages_details->tot_no_workers_year_per_men) ? $get_leave_wages_details->tot_no_workers_year_per_men : '',
					'#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'tot_no_workers_year_per_men_id'),
					'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					'#required' 		=> TRUE,
				);
		$form['tot_no_workers_employed_year']['tot_no_workers_year_per_women'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Women'),
					 '#type' 				=> 'textfield',
					 '#default_value'	=> !empty($get_leave_wages_details->tot_no_workers_year_per_women) ? $get_leave_wages_details->tot_no_workers_year_per_women : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'tot_no_workers_year_per_women_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
				);
		$form['tot_no_workers_employed_year']['tot_no_workers_year_per_child'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Children'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_leave_wages_details->tot_no_workers_year_per_child) ? $get_leave_wages_details->tot_no_workers_year_per_child : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'tot_no_workers_year_per_child_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
			);
		$form['tot_no_workers_employed_year']['tot_no_workers_year_con_men'] = array(
					'#prefix' 			=> '<td><div class="col-xs-12">',
					'#suffix' 	 		=> '</div></td>',
					'#title'			=>	t('Men'),
					'#type' 			=> 'textfield',
					'#default_value'	=> !empty($get_leave_wages_details->tot_no_workers_year_con_men) ? $get_leave_wages_details->tot_no_workers_year_con_men : '',
					'#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'tot_no_workers_year_con_men_id'),
					'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					'#required' 		=> TRUE,
				);
		$form['tot_no_workers_employed_year']['tot_no_workers_year_con_women'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Women'),
					 '#type' 				=> 'textfield',
					 '#default_value'	=> !empty($get_leave_wages_details->tot_no_workers_year_con_women) ? $get_leave_wages_details->tot_no_workers_year_con_women : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'tot_no_workers_year_con_women_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
				);
		$form['tot_no_workers_employed_year']['tot_no_workers_year_con_child'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td></tr>',
				  '#title'				=>	t('Children'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_leave_wages_details->tot_no_workers_year_con_child) ? $get_leave_wages_details->tot_no_workers_year_con_child : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'tot_no_workers_year_con_child_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
			);
		$form['tot_no_workers_employed_year']['tot_no_workers_year_table_end'] 	= array(
					  '#suffix' => '
									</table>
									</div>
									</div>',
					'#type'	  => 'markup',
					'#markup' => '',	
		);
		
		
		$form['no_workers_annual_leave_year'] = array(
			'#type' 		=> 'fieldset',
			'#title' 		=> t('8. Number of workers who were entitled to annual leave with wages during the year'),
			'#collapsible' 	=> TRUE, // Added
			'#collapsed' 	=> FALSE // Added
		);
		$form['no_workers_annual_leave_year']['no_workers_annual_leave_previous_table'] 	= array(
				
				'#type'		=> 'markup',
				'#prefix'	=> '<div class="row">
				<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
								
					<table class="custom-table-view-dashboard renewal-table">
						<tr>
							<th colspan="3">Permanent</th>
							<th colspan="3">Contractual (Including daily wages)</th>
						</tr>
						<tr>
							<th >Men</th>
							<th >Women</th> 
							<th >Children</th>
							<th >Men</th>
							<th >Women</th> 
							<th >Children</th>
						</tr>'
				
	  
		 );
		 
		$form['no_workers_annual_leave_year']['no_workers_annual_leave_per_men'] = array(
					'#prefix' 			=> '<tr><td><div class="col-xs-12">',
					'#suffix' 	 		=> '</div></td>',
					'#title'			=>	t('Men'),
					'#type' 			=> 'textfield',
					'#default_value'	=> !empty($get_leave_wages_details->no_workers_annual_leave_per_men) ? $get_leave_wages_details->no_workers_annual_leave_per_men : '',
					'#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'no_workers_annual_leave_per_men_id'),
					'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					'#required' 		=> TRUE,
				);
		$form['no_workers_annual_leave_year']['no_workers_annual_leave_per_women'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Women'),
					 '#type' 				=> 'textfield',
					 '#default_value'	=> !empty($get_leave_wages_details->no_workers_annual_leave_per_women) ? $get_leave_wages_details->no_workers_annual_leave_per_women : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'no_workers_annual_leave_per_women_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
				);
		$form['no_workers_annual_leave_year']['no_workers_annual_leave_per_child'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Children'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_leave_wages_details->no_workers_annual_leave_per_child) ? $get_leave_wages_details->no_workers_annual_leave_per_child : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'no_workers_annual_leave_per_child_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
			);
		$form['no_workers_annual_leave_year']['no_workers_annual_leave_con_men'] = array(
					'#prefix' 			=> '<td><div class="col-xs-12">',
					'#suffix' 	 		=> '</div></td>',
					'#title'			=>	t('Men'),
					'#type' 			=> 'textfield',
					'#default_value'	=> !empty($get_leave_wages_details->no_workers_annual_leave_con_men) ? $get_leave_wages_details->no_workers_annual_leave_con_men : '',
					'#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'no_workers_annual_leave_con_men_id'),
					'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					'#required' 		=> TRUE,
				);
		$form['no_workers_annual_leave_year']['no_workers_annual_leave_con_women'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Women'),
					 '#type' 				=> 'textfield',
					 '#default_value'	=> !empty($get_leave_wages_details->no_workers_annual_leave_con_women) ? $get_leave_wages_details->no_workers_annual_leave_con_women : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'no_workers_annual_leave_con_women_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
				);
		$form['no_workers_annual_leave_year']['no_workers_annual_leave_con_child'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td></tr>',
				  '#title'				=>	t('Children'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_leave_wages_details->no_workers_annual_leave_con_child) ? $get_leave_wages_details->no_workers_annual_leave_con_child : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'no_workers_annual_leave_con_child_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
			);
		$form['no_workers_annual_leave_year']['no_workers_annual_leave_table_end'] 	= array(
					  '#suffix' => '
									</table>
									</div>
									</div>',
					'#type'	  => 'markup',
					'#markup' => '',	
		);
		
		
		$form['no_workers_granted_leave_year'] = array(
			'#type' 		=> 'fieldset',
			'#title' 		=> t('9. Number of workers who were granted leave during the year'),
			'#collapsible' 	=> TRUE, // Added
			'#collapsed' 	=> FALSE // Added
		);
		$form['no_workers_granted_leave_year']['no_workers_granted_leave_previous_table'] 	= array(
				
				'#type'		=> 'markup',
				'#prefix'	=> '<div class="row">
				<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
								
					<table class="custom-table-view-dashboard renewal-table">
						<tr>
							<th colspan="3">Permanent</th>
							<th colspan="3">Contractual (Including daily wages)</th>
						</tr>
						<tr>
							<th >Men</th>
							<th >Women</th> 
							<th >Children</th>
							<th >Men</th>
							<th >Women</th> 
							<th >Children</th>
						</tr>'
				
	  
		 );
		 
		$form['no_workers_granted_leave_year']['no_workers_granted_leave_per_men'] = array(
					'#prefix' 			=> '<tr><td><div class="col-xs-12">',
					'#suffix' 	 		=> '</div></td>',
					'#title'			=>	t('Men'),
					'#type' 			=> 'textfield',
					'#default_value'	=> !empty($get_leave_wages_details->no_workers_granted_leave_per_men) ? $get_leave_wages_details->no_workers_granted_leave_per_men : '',
					'#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'no_workers_granted_leave_per_men_id'),
					'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					'#required' 		=> TRUE,
				);
		$form['no_workers_granted_leave_year']['no_workers_granted_leave_per_women'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Women'),
					 '#type' 				=> 'textfield',
					 '#default_value'	=> !empty($get_leave_wages_details->no_workers_granted_leave_per_women) ? $get_leave_wages_details->no_workers_granted_leave_per_women : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'no_workers_granted_leave_per_women_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
				);
		$form['no_workers_granted_leave_year']['no_workers_granted_leave_per_child'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Children'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_leave_wages_details->no_workers_granted_leave_per_child) ? $get_leave_wages_details->no_workers_granted_leave_per_child : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'no_workers_granted_leave_per_child_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
			);
		$form['no_workers_granted_leave_year']['no_workers_granted_leave_con_men'] = array(
					'#prefix' 			=> '<td><div class="col-xs-12">',
					'#suffix' 	 		=> '</div></td>',
					'#title'			=>	t('Men'),
					'#type' 			=> 'textfield',
					'#default_value'	=> !empty($get_leave_wages_details->no_workers_granted_leave_con_men) ? $get_leave_wages_details->no_workers_granted_leave_con_men : '',
					'#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'no_workers_granted_leave_con_men_id'),
					'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					'#required' 		=> TRUE,
				);
		$form['no_workers_granted_leave_year']['no_workers_granted_leave_con_women'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Women'),
					 '#type' 				=> 'textfield',
					 '#default_value'	=> !empty($get_leave_wages_details->no_workers_granted_leave_con_women) ? $get_leave_wages_details->no_workers_granted_leave_con_women : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'no_workers_granted_leave_con_women_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
				);
		$form['no_workers_granted_leave_year']['no_workers_granted_leave_con_child'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td></tr>',
				  '#title'				=>	t('Children'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_leave_wages_details->no_workers_granted_leave_con_child) ? $get_leave_wages_details->no_workers_granted_leave_con_child : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'no_workers_granted_leave_con_child_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
			);
		$form['no_workers_granted_leave_year']['no_workers_granted_leave_table_end'] 	= array(
					  '#suffix' => '
									</table>
									</div>
									</div>',
					'#type'	  => 'markup',
					'#markup' => '',	
		);
		
		
		$form['no_workers_discharged_year'] = array(
			'#type' 		=> 'fieldset',
			'#title' 		=> t('10. (a) Number of workers who were discharged, or dismissed from the service, or quit emploment, or were superannuated, or who died while in service during the year'),
			'#collapsible' 	=> TRUE, // Added
			'#collapsed' 	=> FALSE // Added
		);
		$form['no_workers_discharged_year']['no_workers_discharged_previous_table'] 	= array(
				
				'#type'		=> 'markup',
				'#prefix'	=> '<div class="row">
				<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
								
					<table class="custom-table-view-dashboard renewal-table">
						<tr>
							<th>Permanent</th>
							<th>Contractual (Including daily wages)</th>
						</tr>'
				
	  
		 );
		 
		$form['no_workers_discharged_year']['no_workers_discharged_permanent'] = array(
					'#prefix' 			=> '<tr><td><div class="col-xs-12">',
					'#suffix' 	 		=> '</div></td>',
					'#title'			=>	t('No. of Workers'),
					'#type' 			=> 'textfield',
					'#default_value'	=> !empty($get_leave_wages_details->no_workers_discharged_permanent) ? $get_leave_wages_details->no_workers_discharged_permanent : '',
					'#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'no_workers_discharged_permanent_id'),
					'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					'#required' 		=> TRUE,
				);
		$form['no_workers_discharged_year']['no_workers_discharged_contractual'] = array(
					'#prefix' 			=> '<td><div class="col-xs-12">',
					'#suffix' 	 		=> '</div></td></tr>',
					'#title'			=>	t('No. of Workers'),
					'#type' 			=> 'textfield',
					'#default_value'	=> !empty($get_leave_wages_details->no_workers_discharged_contractual) ? $get_leave_wages_details->no_workers_discharged_contractual : '',
					'#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'no_workers_discharged_contractual_id'),
					'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					'#required' 		=> TRUE,
				);		
		$form['no_workers_discharged_year']['no_workers_discharged_table_end'] 	= array(
					  '#suffix' => '
									</table>
									</div>
									</div>',
					'#type'	  => 'markup',
					'#markup' => '',	
		);
		
		
		
		$form['no_workers_lieu_leave'] = array(
			'#type' 		=> 'fieldset',
			'#title' 		=> t('10. (b) Number of such workers in respect of whom wages in lieu of leave were paid'),
			'#collapsible' 	=> TRUE, // Added
			'#collapsed' 	=> FALSE // Added
		);
		$form['no_workers_lieu_leave']['no_workers_lieu_leave_previous_table'] 	= array(
				
				'#type'		=> 'markup',
				'#prefix'	=> '<div class="row">
				<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
								
					<table class="custom-table-view-dashboard renewal-table">
						<tr>
							<th>Permanent</th>
							<th>Contractual (Including daily wages)</th>
						</tr>'
				
	  
		 );
		 
		$form['no_workers_lieu_leave']['no_workers_lieu_leave_permanent'] = array(
					'#prefix' 			=> '<tr><td><div class="col-xs-12">',
					'#suffix' 	 		=> '</div></td>',
					'#title'			=>	t('No. of Workers'),
					'#type' 			=> 'textfield',
					'#default_value'	=> !empty($get_leave_wages_details->no_workers_lieu_leave_permanent) ? $get_leave_wages_details->no_workers_lieu_leave_permanent : '',
					'#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'no_workers_lieu_leave_permanent_id'),
					'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					'#required' 		=> TRUE,
				);
		$form['no_workers_lieu_leave']['no_workers_lieu_leave_contractual'] = array(
					'#prefix' 			=> '<td><div class="col-xs-12">',
					'#suffix' 	 		=> '</div></td></tr>',
					'#title'			=>	t('No. of Workers'),
					'#type' 			=> 'textfield',
					'#default_value'	=> !empty($get_leave_wages_details->no_workers_lieu_leave_contractual) ? $get_leave_wages_details->no_workers_lieu_leave_contractual : '',
					'#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'no_workers_lieu_leave_contractual_id'),
					'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					'#required' 		=> TRUE,
				);		
		$form['no_workers_lieu_leave']['no_workers_lieu_leave_table_end'] 	= array(
					  '#suffix' => '
									</table>
									</div>
									</div>',
					'#type'	  => 'markup',
					'#markup' => '',	
		);
		
		
		$form['#attributes'] = array('onsubmit' => 'return validate_leave_wages_form()');
		
		$form['leave_wages']['submit'] = array (
			'#prefix' 		=> '',  
			'#suffix' 		=> '',
			'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
			'#type' 		=> 'submit',
			'#value'		=> 'Save & Continue'
		);
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'applicant/annual-return-common-apply/workers_details/'.$annual_returnID.'/'.$factoryID, array(
				'html' => TRUE,
				'attributes' => array('class' => array('btn btn-outline-dark pull-left'))
			))
		);
		
		$form['ar_common_link_markup'] = array(
				
				'#type'		=> 'markup',
				'#prefix'	=> '<div class="row">
									<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
									'.$payment_wages_edit.$factories_act_edit.$maternity_benefit_edit.'',
				'#suffix' => '		</div>
								</div>',
		);
	
	  	return $form;
	}
	
	function annual_return_leave_wages_submit($form, &$form_state){
		//echo '<pre>'; print_r($form_state); die();
		
		global $base_root,$base_path,$user;
		$uid 							= $user->uid;
		
		$annual_return_ID = $form_state['values']['annual_return_id'];
		$factory_id = $form_state['values']['factory_id'];
		
		$val = $form_state['values'];
		
		//leave wages
		$get_leave_wages_details = get_leave_wages_details($annual_return_ID);
		if($get_leave_wages_details != NULL && count($get_leave_wages_details) > 0) {
			$leave_wages_details = array(
				'annual_return_id' => $val['annual_return_id'],
				'tot_no_workers_year_per_men' => $val['tot_no_workers_year_per_men'],
				'tot_no_workers_year_per_women' => $val['tot_no_workers_year_per_women'],
				'tot_no_workers_year_per_child' => $val['tot_no_workers_year_per_child'],
				'tot_no_workers_year_con_men' => $val['tot_no_workers_year_con_men'],
				'tot_no_workers_year_con_women' => $val['tot_no_workers_year_con_women'],
				'tot_no_workers_year_con_child' => $val['tot_no_workers_year_con_child'],
				
				'no_workers_annual_leave_per_men' => $val['no_workers_annual_leave_per_men'],
				'no_workers_annual_leave_per_women' => $val['no_workers_annual_leave_per_women'],
				'no_workers_annual_leave_per_child' => $val['no_workers_annual_leave_per_child'],
				'no_workers_annual_leave_con_men' => $val['no_workers_annual_leave_con_men'],
				'no_workers_annual_leave_con_women' => $val['no_workers_annual_leave_con_women'],
				'no_workers_annual_leave_con_child' => $val['no_workers_annual_leave_con_child'],
				
				'no_workers_granted_leave_per_men' => $val['no_workers_granted_leave_per_men'],
				'no_workers_granted_leave_per_women' => $val['no_workers_granted_leave_per_women'],
				'no_workers_granted_leave_per_child' => $val['no_workers_granted_leave_per_child'],
				'no_workers_granted_leave_con_men' => $val['no_workers_granted_leave_con_men'],
				'no_workers_granted_leave_con_women' => $val['no_workers_granted_leave_con_women'],
				'no_workers_granted_leave_con_child' => $val['no_workers_granted_leave_con_child'],
				
				'no_workers_discharged_permanent' => $val['no_workers_discharged_permanent'],
				'no_workers_discharged_contractual' => $val['no_workers_discharged_contractual'],
				'no_workers_lieu_leave_permanent' => $val['no_workers_lieu_leave_permanent'],
				'no_workers_lieu_leave_contractual' => $val['no_workers_lieu_leave_contractual'],
				
				'uid' => $uid,
				'modification_date'	   => date('Y-m-d H:i:s'),
			);
			db_update('fa_ar_leave_wages_details')->fields($leave_wages_details)->condition('annual_return_id', $annual_return_ID, '=')->execute();	
		} else {
			$leave_wages_details = array(
				'annual_return_id' => $val['annual_return_id'],
				'tot_no_workers_year_per_men' => $val['tot_no_workers_year_per_men'],
				'tot_no_workers_year_per_women' => $val['tot_no_workers_year_per_women'],
				'tot_no_workers_year_per_child' => $val['tot_no_workers_year_per_child'],
				'tot_no_workers_year_con_men' => $val['tot_no_workers_year_con_men'],
				'tot_no_workers_year_con_women' => $val['tot_no_workers_year_con_women'],
				'tot_no_workers_year_con_child' => $val['tot_no_workers_year_con_child'],
				
				'no_workers_annual_leave_per_men' => $val['no_workers_annual_leave_per_men'],
				'no_workers_annual_leave_per_women' => $val['no_workers_annual_leave_per_women'],
				'no_workers_annual_leave_per_child' => $val['no_workers_annual_leave_per_child'],
				'no_workers_annual_leave_con_men' => $val['no_workers_annual_leave_con_men'],
				'no_workers_annual_leave_con_women' => $val['no_workers_annual_leave_con_women'],
				'no_workers_annual_leave_con_child' => $val['no_workers_annual_leave_con_child'],
				
				'no_workers_granted_leave_per_men' => $val['no_workers_granted_leave_per_men'],
				'no_workers_granted_leave_per_women' => $val['no_workers_granted_leave_per_women'],
				'no_workers_granted_leave_per_child' => $val['no_workers_granted_leave_per_child'],
				'no_workers_granted_leave_con_men' => $val['no_workers_granted_leave_con_men'],
				'no_workers_granted_leave_con_women' => $val['no_workers_granted_leave_con_women'],
				'no_workers_granted_leave_con_child' => $val['no_workers_granted_leave_con_child'],
				
				'no_workers_discharged_permanent' => $val['no_workers_discharged_permanent'],
				'no_workers_discharged_contractual' => $val['no_workers_discharged_contractual'],
				'no_workers_lieu_leave_permanent' => $val['no_workers_lieu_leave_permanent'],
				'no_workers_lieu_leave_contractual' => $val['no_workers_lieu_leave_contractual'],
				
				'uid' => $uid,
				'created_date'		   => date('Y-m-d'),
			);
			$leave_wages_details_id = db_insert('fa_ar_leave_wages_details')->fields($leave_wages_details)->execute();	
		}
		
		$get_emplm_dism_pay_bonus_women = get_emplm_dism_pay_bonus_women($annual_return_ID);
		if($get_emplm_dism_pay_bonus_women->annual_return_id != NULL) {
			$emplm_dism_pay_bonus_women = array(
				'agg_no_women_per_temp_emp_year' => $val['tot_no_workers_year_per_women'] + $val['tot_no_workers_year_con_women'],
			);
			
			db_update('fa_ar_emplm_dism_pay_bonus_women')->fields($emplm_dism_pay_bonus_women)->condition('annual_return_id', $annual_return_ID, '=')->execute();		
		}
		
		drupal_goto('applicant/payment-of-wages/'.encryption_decryption_fun('encrypt', $annual_return_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));
		
	}