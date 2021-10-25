<?php

  	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
  	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
  
	function annual_return_worker_details($form, &$form_state, $annual_returnID = '', $factoryID = ''){
	  
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
		
		
		if($get_factory_info->id == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/annual-return-common-apply/default/'.$annual_returnID.'/'.$factoryID) ;
		}
		
		
		$get_worker_details_mandays = get_worker_details_mandays($annual_return_ID);
		$get_worker_details_avg_daily = get_worker_details_avg_daily($annual_return_ID);
		
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
		
		//die($annual_return_ID.' AND '.$factory_id);
		//echo '<pre>'; print_r($get_worker_details_mandays);  print_r($get_worker_details_avg_daily); die();
	  
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
	 	
		$form['annual_return_no_of_days'] = array(
			'#type' 		=> 'fieldset',
			'#title' 		=> t('2. Number of days worked during the year'),
			'#collapsible' 	=> TRUE, // Added
			'#collapsed' 	=> FALSE // Added
		);
		
		$form['annual_return_no_of_days']['no_days_worked_year'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t('Number of days worked during the year'),
			'#type' 			=> 'textfield',
			'#required' 		=> TRUE,
			//'#attributes' => array('class' => array(''),'placeholder' => 'Number of days worked during the year'),
			'#attributes' => array('class' => array('numeric_positive'),'placeholder' => 'Number of days worked during the year', 'id'=>'no_days_worked_year_id'),
			'#default_value' 	=> !empty($get_factory_info->days_worked_year) ? $get_factory_info->days_worked_year : '',
			'#element_validate' 	=> array('element_validate_numeric_positive'),
		);
		
		$form['no_of_mandays_worked'] = array(
			'#type' 		=> 'fieldset',
			'#title' 		=> t('3. Number of mandays worked during the year'),
			'#collapsible' 	=> TRUE, // Added
			'#collapsed' 	=> FALSE // Added
		);
		
		$form['no_of_mandays_worked']['previous_table'] 	= array(
				
				'#type'		=> 'markup',
				'#prefix'	=> '<div class="row">
				<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
								
					<table class="custom-table-view-dashboard renewal-table">
						<tr>
							<th colspan="6">Permanent</th>
							<th colspan="6">Contractual (Including daily wages)</th>
						</tr>
						<tr>
							<th colspan="2">Adults</th>  
							<th colspan="2">Adolescents</th>
							<th colspan="2">Children </th>
							
							<th colspan="2">Adults</th> 
							<th colspan="2">Adolescents</th>
							<th colspan="2">Children</th>
			
						</tr>
						<tr>
							<th >Men</th>
							<th >Women</th>  
							<th >Male</th>
							<th >Female</th>  
							<th >Boys</th>
							<th >Girls</th>  
							<th >Men</th>
							<th >Women</th>  
							<th >Male</th>
							<th >Female</th>  
							<th >Boys</th>
							<th >Girls</th>
						</tr>'
				
	  
		 );
		 
		$form['no_of_mandays_worked']['mandays_per_worker_adult_men'] = array(
					'#prefix' 			=> '<tr><td><div class="col-xs-12">',
					'#suffix' 	 		=> '</div></td>',
					'#title'			=>	t('Men'),
					'#type' 			=> 'textfield',
					'#default_value'	=> !empty($get_worker_details_mandays->mandays_per_worker_adult_men) ? $get_worker_details_mandays->mandays_per_worker_adult_men : '', 
					'#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'mandays_per_worker_adult_men_id'),
					'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					'#required' 		=> TRUE,
				);
		$form['no_of_mandays_worked']['mandays_per_worker_adult_women'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Women'),
					 '#type' 				=> 'textfield',
					'#default_value'	=> !empty($get_worker_details_mandays->mandays_per_worker_adult_women) ? $get_worker_details_mandays->mandays_per_worker_adult_women : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'mandays_per_worker_adult_women_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
				);
		$form['no_of_mandays_worked']['mandays_per_worker_adol_male'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Male'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_mandays->mandays_per_worker_adol_male) ? $get_worker_details_mandays->mandays_per_worker_adol_male : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'mandays_per_worker_adol_male_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
			);
	  
		$form['no_of_mandays_worked']['mandays_per_worker_adol_female'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Female'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_mandays->mandays_per_worker_adol_female) ? $get_worker_details_mandays->mandays_per_worker_adol_female : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'mandays_per_worker_adol_female_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				);
		$form['no_of_mandays_worked']['mandays_per_worker_child_boys'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Boys'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_mandays->mandays_per_worker_child_boys) ? $get_worker_details_mandays->mandays_per_worker_child_boys : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'mandays_per_worker_child_boys_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				);
		$form['no_of_mandays_worked']['mandays_per_worker_child_girls'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Girls'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_mandays->mandays_per_worker_child_girls) ? $get_worker_details_mandays->mandays_per_worker_child_girls : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'mandays_per_worker_child_girls_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				);
		$form['no_of_mandays_worked']['mandays_con_worker_adult_men'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Men'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_mandays->mandays_con_worker_adult_men) ? $get_worker_details_mandays->mandays_con_worker_adult_men : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'mandays_con_worker_adult_men_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				);
		$form['no_of_mandays_worked']['mandays_con_worker_adult_women'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Women'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_mandays->mandays_con_worker_adult_women) ? $get_worker_details_mandays->mandays_con_worker_adult_women : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'mandays_con_worker_adult_women_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				);
		$form['no_of_mandays_worked']['mandays_con_worker_adol_male'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Male'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_mandays->mandays_con_worker_adol_male) ? $get_worker_details_mandays->mandays_con_worker_adol_male : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'mandays_con_worker_adol_male_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
			);
		$form['no_of_mandays_worked']['mandays_con_worker_adol_female'] = array(
					  '#prefix' 			=> '<td><div class="col-xs-12">',
					  '#suffix' 	 		=> '</div></td>',
					  '#title'				=>	t('Female'),
					  '#type' 				=> 'textfield',
					  '#default_value'	=> !empty($get_worker_details_mandays->mandays_con_worker_adol_female) ? $get_worker_details_mandays->mandays_con_worker_adol_female : '',
					  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'mandays_con_worker_adol_female_id'),
					  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					  '#required' 			=> TRUE,
				);
		$form['no_of_mandays_worked']['mandays_con_worker_child_boys'] = array(
				 '#prefix' 				=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Boys'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_mandays->mandays_con_worker_child_boys) ? $get_worker_details_mandays->mandays_con_worker_child_boys : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'mandays_con_worker_child_boys_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
			);
		$form['no_of_mandays_worked']['mandays_con_worker_child_girls'] = array(
				 '#prefix' 				=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td></tr>',
				  '#title'				=>	t('Girls'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_mandays->mandays_con_worker_child_girls) ? $get_worker_details_mandays->mandays_con_worker_child_girls : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'mandays_con_worker_child_girls_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				);
				
		//$mandays_worker_total = !empty($get_worker_details_mandays->mandays_worker_total) ? $get_worker_details_mandays->mandays_worker_total : '';
		/*<tfoot>
			<tr><td colspan="12">
				<font color="#00498b">Total Worker(s)  :-</font>&nbsp;&nbsp;<strong>'.$mandays_worker_total.'</strong></td>
			</tr>
		</tfoot>*/
												
		
		$form['no_of_mandays_worked']['previous_table_end'] 	= array(
					  '#suffix' => '
									</table>
									</div>
									</div>
									</br><font color="#FF0000">**</font>N.B. Adolescents (over 15 but under 18 years of age)
									</br><font color="#FF0000">**</font>N.B. Children (over 14 but under 15 years of age)',
					'#type'	  => 'markup',
					'#markup' => '',	
		);
		
		$form['avg_daily_no_of_person'] = array(
			'#type' 		=> 'fieldset',
			'#title' 		=> t('4. Average daily number of persons employed during the year'),
			'#collapsible' 	=> TRUE, // Added
			'#collapsed' 	=> FALSE // Added
		);
		
		$form['avg_daily_no_of_person']['avg_daily_previous_table'] 	= array(
				
				'#type'		=> 'markup',
				'#prefix'	=> '<div class="row">
				<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
								
					<table class="custom-table-view-dashboard renewal-table">
						<tr>
							<th colspan="6">Permanent</th>
							<th colspan="6">Contractual (Including daily wages)</th>
						</tr>
						<tr>
							<th colspan="2">Adults</th>  
							<th colspan="2">Adolescents</th>
							<th colspan="2">Children </th>
							
							<th colspan="2">Adults</th> 
							<th colspan="2">Adolescents</th>
							<th colspan="2">Children</th>
			
						</tr>
						<tr>
							<th >Men</th>
							<th >Women</th>  
							<th >Male</th>
							<th >Female</th>  
							<th >Boys</th>
							<th >Girls</th>  
							<th >Men</th>
							<th >Women</th>  
							<th >Male</th>
							<th >Female</th>  
							<th >Boys</th>
							<th >Girls</th>	
						</tr>'
				
	  
		 );
		 
		$form['avg_daily_no_of_person']['avg_daily_per_worker_adult_men'] = array(
					'#prefix' 			=> '<tr><td><div class="col-xs-12">',
					'#suffix' 	 		=> '</div></td>',
					'#title'			=>	t('Men'),
					'#type' 			=> 'textfield',
					'#default_value'	=> !empty($get_worker_details_avg_daily->avg_daily_per_worker_adult_men) ? $get_worker_details_avg_daily->avg_daily_per_worker_adult_men : '',
					'#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'avg_daily_per_worker_adult_men_id', 'readonly' => 'readonly'),
					'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					'#required' 		=> TRUE,
				);
		$form['avg_daily_no_of_person']['avg_daily_per_worker_adult_women'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Women'),
					 '#type' 				=> 'textfield',
					 '#default_value'	=> !empty($get_worker_details_avg_daily->avg_daily_per_worker_adult_women) ? $get_worker_details_avg_daily->avg_daily_per_worker_adult_women : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'avg_daily_per_worker_adult_women_id', 'readonly' => 'readonly'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
				);
		$form['avg_daily_no_of_person']['avg_daily_per_worker_adol_male'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Male'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_avg_daily->avg_daily_per_worker_adol_male) ? $get_worker_details_avg_daily->avg_daily_per_worker_adol_male : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'avg_daily_per_worker_adol_male_id', 'readonly' => 'readonly'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
			);
	  
		$form['avg_daily_no_of_person']['avg_daily_per_worker_adol_female'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Female'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_avg_daily->avg_daily_per_worker_adol_female) ? $get_worker_details_avg_daily->avg_daily_per_worker_adol_female : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'avg_daily_per_worker_adol_female_id', 'readonly' => 'readonly'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				);
		$form['avg_daily_no_of_person']['avg_daily_per_worker_child_boys'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Boys'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_avg_daily->avg_daily_per_worker_child_boys) ? $get_worker_details_avg_daily->avg_daily_per_worker_child_boys : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'avg_daily_per_worker_child_boys_id', 'readonly' => 'readonly'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,

				);
		$form['avg_daily_no_of_person']['avg_daily_per_worker_child_girls'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Girls'),

				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_avg_daily->avg_daily_per_worker_child_girls) ? $get_worker_details_avg_daily->avg_daily_per_worker_child_girls : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'avg_daily_per_worker_child_girls_id', 'readonly' => 'readonly'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				);
		$form['avg_daily_no_of_person']['avg_daily_con_worker_adult_men'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Men'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_avg_daily->avg_daily_con_worker_adult_men) ? $get_worker_details_avg_daily->avg_daily_con_worker_adult_men : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'avg_daily_con_worker_adult_men_id', 'readonly' => 'readonly'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				);
		$form['avg_daily_no_of_person']['avg_daily_con_worker_adult_women'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Women'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_avg_daily->avg_daily_con_worker_adult_women) ? $get_worker_details_avg_daily->avg_daily_con_worker_adult_women : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'avg_daily_con_worker_adult_women_id', 'readonly' => 'readonly'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				);
		$form['avg_daily_no_of_person']['avg_daily_con_worker_adol_male'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Male'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_avg_daily->avg_daily_con_worker_adol_male) ? $get_worker_details_avg_daily->avg_daily_con_worker_adol_male : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'avg_daily_con_worker_adol_male_id', 'readonly' => 'readonly'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
			);
		$form['avg_daily_no_of_person']['avg_daily_con_worker_adol_female'] = array(
					  '#prefix' 			=> '<td><div class="col-xs-12">',
					  '#suffix' 	 		=> '</div></td>',
					  '#title'				=>	t('Female'),
					  '#type' 				=> 'textfield',
					  '#default_value'	=> !empty($get_worker_details_avg_daily->avg_daily_con_worker_adol_female) ? $get_worker_details_avg_daily->avg_daily_con_worker_adol_female : '',
					  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'avg_daily_con_worker_adol_female_id', 'readonly' => 'readonly'),
					  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					  '#required' 			=> TRUE,
				);
		$form['avg_daily_no_of_person']['avg_daily_con_worker_child_boys'] = array(
				 '#prefix' 				=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Boys'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_avg_daily->avg_daily_con_worker_child_boys) ? $get_worker_details_avg_daily->avg_daily_con_worker_child_boys : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'avg_daily_con_worker_child_boys_id', 'readonly' => 'readonly'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
			);
		$form['avg_daily_no_of_person']['avg_daily_con_worker_child_girls'] = array(
				 '#prefix' 				=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td></tr>',
				  '#title'				=>	t('Girls'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_avg_daily->avg_daily_con_worker_child_girls) ? $get_worker_details_avg_daily->avg_daily_con_worker_child_girls : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'avg_daily_con_worker_child_girls_id', 'readonly' => 'readonly'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
				);
		
		//$avg_daily_worker_total = !empty($get_worker_details_avg_daily->avg_daily_worker_total) ? $get_worker_details_avg_daily->avg_daily_worker_total : '';
		/*<tfoot>
			<tr><td colspan="12">
				<font color="#00498b">Total Worker(s)  :-</font>&nbsp;&nbsp;<strong>'.$avg_daily_worker_total.'</strong></td>
			</tr>
		</tfoot>*/
		
		
		$form['avg_daily_no_of_person']['avg_daily_previous_table_end'] 	= array(
					  '#suffix' => '
									</table>
									</div>
									</div>
									</br><font color="#FF0000">**</font>N.B. Adolescents (over 15 but under 18 years of age)
									</br><font color="#FF0000">**</font>N.B. Children (over 14 but under 15 years of age)',
					'#type'	  => 'markup',
					'#markup' => '',	
		);
		
		$form['tot_no_manhrs_worked_include_overtime'] = array(
			'#type' 		=> 'fieldset',
			'#title' 		=> t('5. Total number of manhours worked including overtime'),
			'#collapsible' 	=> TRUE, // Added
			'#collapsed' 	=> FALSE // Added
		);
		$form['tot_no_manhrs_worked_include_overtime']['tot_no_manhrs_previous_table'] 	= array(
				
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
		 
		$form['tot_no_manhrs_worked_include_overtime']['tot_no_manhrs_per_men'] = array(
					'#prefix' 			=> '<tr><td><div class="col-xs-12">',
					'#suffix' 	 		=> '</div></td>',
					'#title'			=>	t('Men'),
					'#type' 			=> 'textfield',
					'#default_value'	=> !empty($get_worker_details_mandays->tot_no_manhrs_per_men) ? $get_worker_details_mandays->tot_no_manhrs_per_men : '',
					'#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'tot_no_manhrs_per_men_id'),
					'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					'#required' 		=> TRUE,
				);
		$form['tot_no_manhrs_worked_include_overtime']['tot_no_manhrs_per_women'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Women'),
					 '#type' 				=> 'textfield',
					 '#default_value'	=> !empty($get_worker_details_mandays->tot_no_manhrs_per_women) ? $get_worker_details_mandays->tot_no_manhrs_per_women : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'tot_no_manhrs_per_women_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
				);
		$form['tot_no_manhrs_worked_include_overtime']['tot_no_manhrs_per_child'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Children'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_mandays->tot_no_manhrs_per_child) ? $get_worker_details_mandays->tot_no_manhrs_per_child : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'tot_no_manhrs_per_child_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
			);
		$form['tot_no_manhrs_worked_include_overtime']['tot_no_manhrs_con_men'] = array(
					'#prefix' 			=> '<td><div class="col-xs-12">',
					'#suffix' 	 		=> '</div></td>',
					'#title'			=>	t('Men'),
					'#type' 			=> 'textfield',
					'#default_value'	=> !empty($get_worker_details_mandays->tot_no_manhrs_con_men) ? $get_worker_details_mandays->tot_no_manhrs_con_men : '',
					'#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'tot_no_manhrs_con_men_id'),
					'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					'#required' 		=> TRUE,
				);
		$form['tot_no_manhrs_worked_include_overtime']['tot_no_manhrs_con_women'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Women'),
					 '#type' 				=> 'textfield',
					 '#default_value'	=> !empty($get_worker_details_mandays->tot_no_manhrs_con_women) ? $get_worker_details_mandays->tot_no_manhrs_con_women : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'tot_no_manhrs_con_women_id'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
				);
		$form['tot_no_manhrs_worked_include_overtime']['tot_no_manhrs_con_child'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td></tr>',
				  '#title'				=>	t('Children'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_mandays->tot_no_manhrs_con_child) ? $get_worker_details_mandays->tot_no_manhrs_con_child : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'tot_no_manhrs_con_child_id'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
			);
		$form['tot_no_manhrs_worked_include_overtime']['tot_no_manhrs_table_end'] 	= array(
					  '#suffix' => '
									</table>
									</div>
									</div>',
					'#type'	  => 'markup',
					'#markup' => '',	
		);
		
		$form['avg_no_hrs_worked_per_week'] = array(
			'#type' 		=> 'fieldset',
			'#title' 		=> t('6. Average number of hours worked per week'),
			'#collapsible' 	=> TRUE, // Added
			'#collapsed' 	=> FALSE // Added
		);
		$form['avg_no_hrs_worked_per_week']['avg_no_hrs_worked_week_previous_table'] 	= array(
				
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
		 
		$form['avg_no_hrs_worked_per_week']['avg_no_hrs_worked_week_per_men'] = array(
					'#prefix' 			=> '<tr><td><div class="col-xs-12">',
					'#suffix' 	 		=> '</div></td>',
					'#title'			=>	t('Men'),
					'#type' 			=> 'textfield',
					'#default_value'	=> !empty($get_worker_details_avg_daily->avg_no_hrs_worked_week_per_men) ? $get_worker_details_avg_daily->avg_no_hrs_worked_week_per_men : '',
					'#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'avg_no_hrs_worked_week_per_men_id', 'readonly' => 'readonly'),
					'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					'#required' 		=> TRUE,
				);
		$form['avg_no_hrs_worked_per_week']['avg_no_hrs_worked_week_per_women'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Women'),
					 '#type' 				=> 'textfield',
					 '#default_value'	=> !empty($get_worker_details_avg_daily->avg_no_hrs_worked_week_per_women) ? $get_worker_details_avg_daily->avg_no_hrs_worked_week_per_women : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'avg_no_hrs_worked_week_per_women_id', 'readonly' => 'readonly'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
				);
		$form['avg_no_hrs_worked_per_week']['avg_no_hrs_worked_week_per_child'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td>',
				  '#title'				=>	t('Children'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_avg_daily->avg_no_hrs_worked_week_per_child) ? $get_worker_details_avg_daily->avg_no_hrs_worked_week_per_child : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'avg_no_hrs_worked_week_per_child_id', 'readonly' => 'readonly'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
			);
		$form['avg_no_hrs_worked_per_week']['avg_no_hrs_worked_week_con_men'] = array(
					'#prefix' 			=> '<td><div class="col-xs-12">',
					'#suffix' 	 		=> '</div></td>',
					'#title'			=>	t('Men'),
					'#type' 			=> 'textfield',
					'#default_value'	=> !empty($get_worker_details_avg_daily->avg_no_hrs_worked_week_con_men) ? $get_worker_details_avg_daily->avg_no_hrs_worked_week_con_men : '',
					'#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'avg_no_hrs_worked_week_con_men_id', 'readonly' => 'readonly'),
					'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					'#required' 		=> TRUE,
				);
		$form['avg_no_hrs_worked_per_week']['avg_no_hrs_worked_week_con_women'] = array(
					 '#prefix' 				=> '<td><div class="col-xs-12">',
					 '#suffix' 	 			=> '</div></td>',
					 '#title'				=>	t('Women'),
					 '#type' 				=> 'textfield',
					 '#default_value'	=> !empty($get_worker_details_avg_daily->avg_no_hrs_worked_week_con_women) ? $get_worker_details_avg_daily->avg_no_hrs_worked_week_con_women : '',
					 '#attributes' 			=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'avg_no_hrs_worked_week_con_women_id', 'readonly' => 'readonly'),
					 '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
					 '#required' 			=> TRUE,
				);
		$form['avg_no_hrs_worked_per_week']['avg_no_hrs_worked_week_con_child'] = array(
				  '#prefix' 			=> '<td><div class="col-xs-12">',
				  '#suffix' 	 		=> '</div></td></tr>',
				  '#title'				=>	t('Children'),
				  '#type' 				=> 'textfield',
				  '#default_value'	=> !empty($get_worker_details_avg_daily->avg_no_hrs_worked_week_con_child) ? $get_worker_details_avg_daily->avg_no_hrs_worked_week_con_child : '',
				  '#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'avg_no_hrs_worked_week_con_child_id', 'readonly' => 'readonly'),
				  '#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
				  '#required' 			=> TRUE,
			);
		$form['avg_no_hrs_worked_per_week']['avg_no_hrs_worked_week_table_end'] 	= array(
					  '#suffix' => '
									</table>
									</div>
									</div>',
					'#type'	  => 'markup',
					'#markup' => '',	
		);
	 
		
		$form['#attributes'] = array('onsubmit' => 'return validate_workers_details_form()');								
		 
		$form['annual_return_workers']['submit'] = array (
			'#prefix' 		=> '',  
			'#suffix' 		=> '',
			'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
			'#type' 		=> 'submit',
			'#value'		=> 'Save & Continue'
		);
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'applicant/annual-return-common-apply/default/'.$annual_returnID.'/'.$factoryID, array(
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
	
  	
  
	function annual_return_worker_details_submit($form, &$form_state){
		//echo '<pre>'; print_r($form_state); die();
		
		global $base_root,$base_path,$user;
		$uid 							= $user->uid;
		
		$annual_return_ID = $form_state['values']['annual_return_id'];
		$factory_id = $form_state['values']['factory_id'];
		
		$val = $form_state['values'];
		
		$mandays_worker_total = $val['mandays_per_worker_adult_men'] + $val['mandays_per_worker_adult_women'] + $val['mandays_per_worker_adol_male'] + $val['mandays_per_worker_adol_female'] + $val['mandays_per_worker_child_boys'] + $val['mandays_per_worker_child_girls'] + $val['mandays_con_worker_adult_men'] + $val['mandays_con_worker_adult_women'] + $val['mandays_con_worker_adol_male'] + $val['mandays_con_worker_adol_female'] + $val['mandays_con_worker_child_boys'] + $val['mandays_con_worker_child_girls'];
		
		$avg_daily_worker_total = $val['avg_daily_per_worker_adult_men'] + $val['avg_daily_per_worker_adult_women'] + $val['avg_daily_per_worker_adol_male'] + $val['avg_daily_per_worker_adol_female'] + $val['avg_daily_per_worker_child_boys'] + $val['avg_daily_per_worker_child_girls'] + $val['avg_daily_con_worker_adult_men'] + $val['avg_daily_con_worker_adult_women'] + $val['avg_daily_con_worker_adol_male'] + $val['avg_daily_con_worker_adol_female'] + $val['avg_daily_con_worker_child_boys'] + $val['avg_daily_con_worker_child_girls'];
		
		//mandays worker details
		
		$no_worker_details_mandays = get_worker_details_mandays($annual_return_ID);
		if($no_worker_details_mandays != NULL && count($no_worker_details_mandays) > 0) {
			$mandays_worker_details = array(
				'annual_return_id' => $val['annual_return_id'],
				'mandays_per_worker_adult_men' => $val['mandays_per_worker_adult_men'],
				'mandays_per_worker_adult_women' => $val['mandays_per_worker_adult_women'],
				'mandays_per_worker_adol_male' => $val['mandays_per_worker_adol_male'],
				'mandays_per_worker_adol_female' => $val['mandays_per_worker_adol_female'],
				'mandays_per_worker_child_boys' => $val['mandays_per_worker_child_boys'],
				'mandays_per_worker_child_girls' => $val['mandays_per_worker_child_girls'],
				'mandays_con_worker_adult_men' => $val['mandays_con_worker_adult_men'],
				'mandays_con_worker_adult_women' => $val['mandays_con_worker_adult_women'],
				'mandays_con_worker_adol_male' => $val['mandays_con_worker_adol_male'],
				'mandays_con_worker_adol_female' => $val['mandays_con_worker_adol_female'],
				'mandays_con_worker_child_boys' => $val['mandays_con_worker_child_boys'],
				'mandays_con_worker_child_girls' => $val['mandays_con_worker_child_girls'],
				'uid' => $uid,
				'mandays_worker_total' => $mandays_worker_total,
				'modification_date'	   => date('Y-m-d H:i:s'),
				
				'tot_no_manhrs_per_men' => $val['tot_no_manhrs_per_men'],
				'tot_no_manhrs_per_women' => $val['tot_no_manhrs_per_women'],
				'tot_no_manhrs_per_child' => $val['tot_no_manhrs_per_child'],
				'tot_no_manhrs_con_men' => $val['tot_no_manhrs_con_men'],
				'tot_no_manhrs_con_women' => $val['tot_no_manhrs_con_women'],
				'tot_no_manhrs_con_child' => $val['tot_no_manhrs_con_child'],
			);
			db_update('fa_ar_worker_details_mandays')->fields($mandays_worker_details)->condition('annual_return_id', $annual_return_ID, '=')->execute();	
		} else {
			$mandays_worker_details = array(
				'annual_return_id' => $val['annual_return_id'],
				'mandays_per_worker_adult_men' => $val['mandays_per_worker_adult_men'],
				'mandays_per_worker_adult_women' => $val['mandays_per_worker_adult_women'],
				'mandays_per_worker_adol_male' => $val['mandays_per_worker_adol_male'],
				'mandays_per_worker_adol_female' => $val['mandays_per_worker_adol_female'],
				'mandays_per_worker_child_boys' => $val['mandays_per_worker_child_boys'],
				'mandays_per_worker_child_girls' => $val['mandays_per_worker_child_girls'],
				'mandays_con_worker_adult_men' => $val['mandays_con_worker_adult_men'],
				'mandays_con_worker_adult_women' => $val['mandays_con_worker_adult_women'],
				'mandays_con_worker_adol_male' => $val['mandays_con_worker_adol_male'],
				'mandays_con_worker_adol_female' => $val['mandays_con_worker_adol_female'],
				'mandays_con_worker_child_boys' => $val['mandays_con_worker_child_boys'],
				'mandays_con_worker_child_girls' => $val['mandays_con_worker_child_girls'],
				'uid' => $uid,
				'mandays_worker_total' => $mandays_worker_total,
				'created_date'		   => date('Y-m-d'),
				
				'tot_no_manhrs_per_men' => $val['tot_no_manhrs_per_men'],
				'tot_no_manhrs_per_women' => $val['tot_no_manhrs_per_women'],
				'tot_no_manhrs_per_child' => $val['tot_no_manhrs_per_child'],
				'tot_no_manhrs_con_men' => $val['tot_no_manhrs_con_men'],
				'tot_no_manhrs_con_women' => $val['tot_no_manhrs_con_women'],
				'tot_no_manhrs_con_child' => $val['tot_no_manhrs_con_child'],
			);
			$mandays_worker_details_id = db_insert('fa_ar_worker_details_mandays')->fields($mandays_worker_details)->execute();	
		}
		
		//average daily worker details
		
		$no_avg_daily_worker_details = get_worker_details_avg_daily($annual_return_ID);
		if($no_avg_daily_worker_details != NULL && count($no_avg_daily_worker_details) > 0) {
			$avg_daily_worker_details = array(
				'annual_return_id' => $val['annual_return_id'],
				'avg_daily_per_worker_adult_men' => $val['avg_daily_per_worker_adult_men'],
				'avg_daily_per_worker_adult_women' => $val['avg_daily_per_worker_adult_women'],
				'avg_daily_per_worker_adol_male' => $val['avg_daily_per_worker_adol_male'],
				'avg_daily_per_worker_adol_female' => $val['avg_daily_per_worker_adol_female'],
				'avg_daily_per_worker_child_boys' => $val['avg_daily_per_worker_child_boys'],
				'avg_daily_per_worker_child_girls' => $val['avg_daily_per_worker_child_girls'],
				'avg_daily_con_worker_adult_men' => $val['avg_daily_con_worker_adult_men'],
				'avg_daily_con_worker_adult_women' => $val['avg_daily_con_worker_adult_women'],
				'avg_daily_con_worker_adol_male' => $val['avg_daily_con_worker_adol_male'],
				'avg_daily_con_worker_adol_female' => $val['avg_daily_con_worker_adol_female'],
				'avg_daily_con_worker_child_boys' => $val['avg_daily_con_worker_child_boys'],
				'avg_daily_con_worker_child_girls' => $val['avg_daily_con_worker_child_girls'],
				'uid' => $uid,
				'avg_daily_worker_total' => $avg_daily_worker_total,
				'modification_date'	   => date('Y-m-d H:i:s'),
				
				'avg_no_hrs_worked_week_per_men' => $val['avg_no_hrs_worked_week_per_men'],
				'avg_no_hrs_worked_week_per_women' => $val['avg_no_hrs_worked_week_per_women'],
				'avg_no_hrs_worked_week_per_child' => $val['avg_no_hrs_worked_week_per_child'],
				'avg_no_hrs_worked_week_con_men' => $val['avg_no_hrs_worked_week_con_men'],
				'avg_no_hrs_worked_week_con_women' => $val['avg_no_hrs_worked_week_con_women'],
				'avg_no_hrs_worked_week_con_child' => $val['avg_no_hrs_worked_week_con_child'],
			);
			db_update('fa_ar_worker_details_avg_worker')->fields($avg_daily_worker_details)->condition('annual_return_id', $annual_return_ID, '=')->execute();	
		} else {
			$avg_daily_worker_details = array(
				'annual_return_id' => $val['annual_return_id'],
				'avg_daily_per_worker_adult_men' => $val['avg_daily_per_worker_adult_men'],
				'avg_daily_per_worker_adult_women' => $val['avg_daily_per_worker_adult_women'],
				'avg_daily_per_worker_adol_male' => $val['avg_daily_per_worker_adol_male'],
				'avg_daily_per_worker_adol_female' => $val['avg_daily_per_worker_adol_female'],
				'avg_daily_per_worker_child_boys' => $val['avg_daily_per_worker_child_boys'],
				'avg_daily_per_worker_child_girls' => $val['avg_daily_per_worker_child_girls'],
				'avg_daily_con_worker_adult_men' => $val['avg_daily_con_worker_adult_men'],
				'avg_daily_con_worker_adult_women' => $val['avg_daily_con_worker_adult_women'],
				'avg_daily_con_worker_adol_male' => $val['avg_daily_con_worker_adol_male'],
				'avg_daily_con_worker_adol_female' => $val['avg_daily_con_worker_adol_female'],
				'avg_daily_con_worker_child_boys' => $val['avg_daily_con_worker_child_boys'],
				'avg_daily_con_worker_child_girls' => $val['avg_daily_con_worker_child_girls'],
				'uid' => $uid,
				'avg_daily_worker_total' => $avg_daily_worker_total,
				'created_date'		   => date('Y-m-d'),
				
				'avg_no_hrs_worked_week_per_men' => $val['avg_no_hrs_worked_week_per_men'],
				'avg_no_hrs_worked_week_per_women' => $val['avg_no_hrs_worked_week_per_women'],
				'avg_no_hrs_worked_week_per_child' => $val['avg_no_hrs_worked_week_per_child'],
				'avg_no_hrs_worked_week_con_men' => $val['avg_no_hrs_worked_week_con_men'],
				'avg_no_hrs_worked_week_con_women' => $val['avg_no_hrs_worked_week_con_women'],
				'avg_no_hrs_worked_week_con_child' => $val['avg_no_hrs_worked_week_con_child'],
			);
			$avg_daily_worker_details_id = db_insert('fa_ar_worker_details_avg_worker')->fields($avg_daily_worker_details)->execute();
		}
		
		$annual_return = array(
			'days_worked_year' => $val['no_days_worked_year'],
		);
		db_update('fa_annual_return')->fields($annual_return)->condition('id', $annual_return_ID, '=')->execute();
		
		$get_emplm_dism_pay_bonus_women = get_emplm_dism_pay_bonus_women($annual_return_ID);
		if($get_emplm_dism_pay_bonus_women->annual_return_id != NULL) {
			$emplm_dism_pay_bonus_women = array(
				'avg_daily_no_women_emp' => $val['avg_daily_per_worker_adult_women'] + $val['avg_daily_con_worker_adult_women'],
			);
			
			db_update('fa_ar_emplm_dism_pay_bonus_women')->fields($emplm_dism_pay_bonus_women)->condition('annual_return_id', $annual_return_ID, '=')->execute();		
		}
		
		drupal_goto('applicant/annual-return-common-apply/leave_wages/'.encryption_decryption_fun('encrypt', $annual_return_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));
	
	}
 