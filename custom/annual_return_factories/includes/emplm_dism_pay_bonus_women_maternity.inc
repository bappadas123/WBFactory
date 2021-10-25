<?php

	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
  	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	function emplm_dism_pay_bonus_women_maternity($form, &$form_state, $annual_returnID = '', $factoryID = '') {
	
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
		
		
		$get_wages_paid_include_deduction = get_total_wages_paid_include_deduction($annual_return_ID);
		$get_disbursement_fine_funds = get_disbursement_fine_funds($annual_return_ID);
		$get_factory_act_all_data = get_factory_act_all_data($annual_return_ID);
		
		$get_leave_wages_details = get_leave_wages_details($annual_return_ID);
		$get_worker_details_avg_daily = get_worker_details_avg_daily($annual_return_ID);
		
		$get_emplm_dism_pay_bonus_women = get_emplm_dism_pay_bonus_women($annual_return_ID);
		
		$get_hospital_details = get_hospital_details($annual_return_ID);
		if($get_factory_info->hospital_attached_factory == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/maternity-benefit-apply/hospital_details/'.$annual_returnID.'/'.$factoryID) ;
		} else {
			if($get_factory_info->hospital_attached_factory == 'Yes') {
				if($get_hospital_details[0]->annual_return_id == NULL) {
					drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
					drupal_goto('applicant/maternity-benefit-apply/hospital_details/'.$annual_returnID.'/'.$factoryID) ;
				}
			}
		}
		
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
		
		$common_section_edit = l('Annual Return Common Section Edit', 'applicant/annual-return-common-apply/default/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		
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
		
		$form['emplm_dism_women'] = array(
		'#type' => 'fieldset',
		'#title' => t('Employment, Dismissal, Payment of Bonus, etc. of Women'),
		'#collapsible' => TRUE, // Added
		'#collapsed' => FALSE // Added 
		);
		
		$agg_no_women_per_temp_emp_year = $get_leave_wages_details->tot_no_workers_year_per_women + $get_leave_wages_details->tot_no_workers_year_con_women;
		$form['emplm_dism_women']['agg_no_women_per_temp_emp_year']	=	array(
			'#title' 			=> t('<strong>1. Aggregate number of women permanently or temporarily employed during the year</strong>'),
			'#type'				=> 'textfield',
			'#prefix'			=> '<div class="row"><div id="agg_no_women_per_temp_emp_year_id"><div class="col-md-8 col-xs-8"><label class="select label-block">',
			'#suffix'			=> '</label></div></div>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->agg_no_women_per_temp_emp_year) ? $get_emplm_dism_pay_bonus_women->agg_no_women_per_temp_emp_year :$agg_no_women_per_temp_emp_year, 
			'#attributes' 		=> array('class'=>array(''), 'readonly' => 'readonly'),
			'#required' 		=> TRUE,
		);
		
		$avg_daily_no_women_emp = $get_worker_details_avg_daily->avg_daily_per_worker_adult_women + $get_worker_details_avg_daily->avg_daily_con_worker_adult_women;
		$form['emplm_dism_women']['avg_daily_no_women_emp']	=	array(
			'#title' 			=> t('<strong>2. Average daily number of women workers employed</strong>'),
			'#type'				=> 'textfield',
			'#prefix'			=> '<div id="avg_daily_no_women_emp_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=> '</label></div></div>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->avg_daily_no_women_emp) ? $get_emplm_dism_pay_bonus_women->avg_daily_no_women_emp : $avg_daily_no_women_emp, 
			'#attributes' 		=> array('class'=>array(''), 'readonly' => 'readonly'),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_women_worked_for_perd']	=	array(
			'#title' 			=> t('<strong>3. Number of women who worked for a period of not less than one hundred and sixty days in the twelve months immediately preceding the date of delivery</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="no_women_worked_for_perd_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_women_worked_for_perd) ? $get_emplm_dism_pay_bonus_women->no_women_worked_for_perd : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_women_gave_notice']	=	array(
			'#title' 			=> t('<strong>4. Number of women who gave notice under Section 6</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="no_women_gave_notice_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_women_gave_notice) ? $get_emplm_dism_pay_bonus_women->no_women_gave_notice : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['emplm_dism_women_table_start']	=	array(
			'#type'		=> 'markup',
			'#prefix'			=>	'<div id="emplm_dism_women_table_id"><div class="col-md-12 col-xs-12"><label class="select label-block">
									<br>
									<table class="custom-table-view-dashboard renewal-table" width="100%">
										<tr>
											<th colspan="2" width="50%"></th>
											<th width="25%">Undisposed from previous years and disposed during the year</th>
											<th width="25%">Current year</th>
										</tr>',
		);
		
		$form['emplm_dism_women']['no_women_grant_permi_absent'] = array(
			'#prefix'			=> '<tr><td colspan="2"><div id="no_women_grant_permi_absent_id"><div class="col-xs-12"><label class="select label-block"><strong>5. Number of women who were granted permission to absent on receipt of notice of confinement</strong>',
			'#suffix'			=> '</label></div></div></td>',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['grant_permi_abse_undisp_prev_year']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="grant_permi_abse_undisp_prev_year_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->grant_permi_abse_undisp_prev_year) ? $get_emplm_dism_pay_bonus_women->grant_permi_abse_undisp_prev_year : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['grant_permi_abse_curr_year']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="grant_permi_abse_curr_year_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td></tr>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->grant_permi_abse_curr_year) ? $get_emplm_dism_pay_bonus_women->grant_permi_abse_curr_year : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		//6
		$form['emplm_dism_women']['no_claims_mater_benefit'] = array(
			'#prefix'			=> '<tr><td rowspan="2"><div id="no_claims_mater_benefit_id"><div class="col-xs-12"><label class="select label-block"><strong>6. No of claims for maternity benefit</strong>',
			'#suffix'			=> '</label></div></div></td>',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_claims_mater_benefit_paid'] = array(
			'#prefix'			=> '<td><div id="no_claims_mater_benefit_paid_id"><div class="col-xs-12"><label class="select label-block"><strong>Paid</strong>',
			'#suffix'			=> '</label></div></div></td>',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_claims_mater_paid_undisp_prev_year']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="no_claims_mater_paid_undisp_prev_year_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_claims_mater_paid_undisp_prev_year) ? $get_emplm_dism_pay_bonus_women->no_claims_mater_paid_undisp_prev_year : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_claims_mater_paid_curr_year']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="no_claims_mater_paid_curr_year_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td></tr>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_claims_mater_paid_curr_year) ? $get_emplm_dism_pay_bonus_women->no_claims_mater_paid_curr_year : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_claims_mater_benefit_reject'] = array(
			'#prefix'			=> '<tr><td><div id="no_claims_mater_benefit_reject_id"><div class="col-xs-12"><label class="select label-block"><strong>Reject</strong>',
			'#suffix'			=> '</label></div></div></td>',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_claims_mater_reject_undisp_prev_year']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="no_claims_mater_reject_undisp_prev_year_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_claims_mater_reject_undisp_prev_year) ? $get_emplm_dism_pay_bonus_women->no_claims_mater_reject_undisp_prev_year : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_claims_mater_reject_curr_year']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="no_claims_mater_reject_curr_year_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td></tr>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_claims_mater_reject_curr_year) ? $get_emplm_dism_pay_bonus_women->no_claims_mater_reject_curr_year : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		//6
		
		//7
		$form['emplm_dism_women']['no_claims_medi_bonus'] = array(
			'#prefix'			=> '<tr><td rowspan="2"><div id="no_claims_medi_bonus_id"><div class="col-xs-12"><label class="select label-block"><strong>7. No of claims for medical bonus (under Section 8)</strong>',
			'#suffix'			=> '</label></div></div></td>',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_claims_medi_bonus_paid'] = array(
			'#prefix'			=> '<td><div id="no_claims_medi_bonus_paid_id"><div class="col-xs-12"><label class="select label-block"><strong>Paid</strong>',
			'#suffix'			=> '</label></div></div></td>',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_claims_medi_paid_undisp_prev_year']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="no_claims_medi_paid_undisp_prev_year_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_claims_medi_paid_undisp_prev_year) ? $get_emplm_dism_pay_bonus_women->no_claims_medi_paid_undisp_prev_year : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_claims_medi_paid_curr_year']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="no_claims_medi_paid_curr_year_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td></tr>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_claims_medi_paid_curr_year) ? $get_emplm_dism_pay_bonus_women->no_claims_medi_paid_curr_year : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_claims_medi_bonus_reject'] = array(
			'#prefix'			=> '<tr><td><div id="no_claims_medi_bonus_reject_id"><div class="col-xs-12"><label class="select label-block"><strong>Reject</strong>',
			'#suffix'			=> '</label></div></div></td>',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_claims_medi_reject_undisp_prev_year']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="no_claims_medi_reject_undisp_prev_year_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_claims_medi_reject_undisp_prev_year) ? $get_emplm_dism_pay_bonus_women->no_claims_medi_reject_undisp_prev_year : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_claims_medi_reject_curr_year']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="no_claims_medi_reject_curr_year_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td></tr>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_claims_medi_reject_curr_year) ? $get_emplm_dism_pay_bonus_women->no_claims_medi_reject_curr_year : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		//7
		
		//8
		$form['emplm_dism_women']['no_case_leave_miscarriage'] = array(
			'#prefix'			=> '<tr><td rowspan="2"><div id="no_case_leave_miscarriage_id"><div class="col-xs-12"><label class="select label-block"><strong>8. No of cases in which leave for miscarriage was applied for and was</strong>',
			'#suffix'			=> '</label></div></div></td>',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_case_leave_miscarriage_grant'] = array(
			'#prefix'			=> '<td><div id="no_case_leave_miscarriage_grant_id"><div class="col-xs-12"><label class="select label-block"><strong>Granted</strong>',
			'#suffix'			=> '</label></div></div></td>',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_case_miscarr_grant_undisp_prev_year']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="no_case_miscarr_grant_undisp_prev_year_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_case_miscarr_grant_undisp_prev_year) ? $get_emplm_dism_pay_bonus_women->no_case_miscarr_grant_undisp_prev_year : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_case_miscarr_grant_curr_year']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="no_case_miscarr_grant_curr_year_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td></tr>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_case_miscarr_grant_curr_year) ? $get_emplm_dism_pay_bonus_women->no_case_miscarr_grant_curr_year : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_case_leave_miscarriage_reject'] = array(
			'#prefix'			=> '<tr><td><div id="no_case_leave_miscarriage_reject_id"><div class="col-xs-12"><label class="select label-block"><strong>Reject</strong>',
			'#suffix'			=> '</label></div></div></td>',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_case_miscarr_reject_undisp_prev_year']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="no_case_miscarr_reject_undisp_prev_year_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_case_miscarr_reject_undisp_prev_year) ? $get_emplm_dism_pay_bonus_women->no_case_miscarr_reject_undisp_prev_year : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_case_miscarr_reject_curr_year']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="no_case_miscarr_reject_curr_year_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td></tr>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_case_miscarr_reject_curr_year) ? $get_emplm_dism_pay_bonus_women->no_case_miscarr_reject_curr_year : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		//8
		
		//9
		$form['emplm_dism_women']['no_case_addl_leave_illness'] = array(
			'#prefix'			=> '<tr><td rowspan="2"><div id="no_case_addl_leave_illness_id"><div class="col-xs-12"><label class="select label-block"><strong>9. No of cases in which additional leave for illness under sec. 10 was applied for and was</strong>',
			'#suffix'			=> '</label></div></div></td>',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_case_addl_leave_illness_grant'] = array(
			'#prefix'			=> '<td><div id="no_case_addl_leave_illness_grant_id"><div class="col-xs-12"><label class="select label-block"><strong>Granted</strong>',
			'#suffix'			=> '</label></div></div></td>',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_case_illness_grant_undisp_prev_year']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="no_case_illness_grant_undisp_prev_year_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_case_illness_grant_undisp_prev_year) ? $get_emplm_dism_pay_bonus_women->no_case_illness_grant_undisp_prev_year : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_case_illness_grant_curr_year']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="no_case_illness_grant_curr_year_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td></tr>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_case_illness_grant_curr_year) ? $get_emplm_dism_pay_bonus_women->no_case_illness_grant_curr_year : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_case_addl_leave_illness_reject'] = array(
			'#prefix'			=> '<tr><td><div id="no_case_addl_leave_illness_reject_id"><div class="col-xs-12"><label class="select label-block"><strong>Reject</strong>',
			'#suffix'			=> '</label></div></div></td>',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_case_illness_reject_undisp_prev_year']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="no_case_illness_reject_undisp_prev_year_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_case_illness_reject_undisp_prev_year) ? $get_emplm_dism_pay_bonus_women->no_case_illness_reject_undisp_prev_year : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_case_illness_reject_curr_year']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="no_case_illness_reject_curr_year_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td></tr>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_case_illness_reject_curr_year) ? $get_emplm_dism_pay_bonus_women->no_case_illness_reject_curr_year : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		//9
		
		$form['emplm_dism_women']['emplm_dism_women_table_end'] 	= array(
			'#suffix' => '</table>
							</label></div></div>',
			'#type'	  => 'markup',
			'#markup' => '',	
		);
		
		$form['emplm_dism_women']['no_case_natal_confine_care']	=	array(
			'#title' 			=> t('<strong>10. No. of cases where pre-natal confinement and post-natal care was provided by the management free of charge (Section 8)</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="no_case_natal_confine_care_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_case_natal_confine_care) ? $get_emplm_dism_pay_bonus_women->no_case_natal_confine_care : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_women_died'] = array(
			'#prefix'			=> '<tr><td><div id="no_women_died_id"><div class="col-xs-12"><label class="select label-block"><strong>11. No. of women who died:</strong>',
			'#suffix'			=> '</label></div></div></td>',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_women_died_before_dlvry']	=	array(
			'#title' 			=> t('<strong>(a) before delivery</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="no_women_died_before_dlvry_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_women_died_before_dlvry) ? $get_emplm_dism_pay_bonus_women->no_women_died_before_dlvry : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_women_died_after_dlvry']	=	array(
			'#title' 			=> t('<strong>(b) after delivery</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="no_women_died_after_dlvry_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_women_died_after_dlvry) ? $get_emplm_dism_pay_bonus_women->no_women_died_after_dlvry : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_infants_died'] = array(
			'#prefix'			=> '<tr><td><div id="no_infants_died_id"><div class="col-xs-12"><label class="select label-block"><strong>12. No. of infants who died:</strong>',
			'#suffix'			=> '</label></div></div></td>',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_infants_died_on_dob']	=	array(
			'#title' 			=> t('<strong>(a) on the day of their birth</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="no_infants_died_on_dob_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_infants_died_on_dob) ? $get_emplm_dism_pay_bonus_women->no_infants_died_on_dob : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_infants_died_during_six_weeks']	=	array(
			'#title' 			=> t('<strong>(b) during the six weeks following the date of birth</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="no_infants_died_during_six_weeks_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_infants_died_during_six_weeks) ? $get_emplm_dism_pay_bonus_women->no_infants_died_during_six_weeks : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_women_discharge_work']	=	array(
			'#title' 			=> t('<strong>13. No. of women discharge or dismissed while working</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="no_women_discharge_work_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_women_discharge_work) ? $get_emplm_dism_pay_bonus_women->no_women_discharge_work : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_women_deprived_mater']	=	array(
			'#title' 			=> t('<strong>14. No. of women deprived of maternity benefit and/or medical bonus under provission to sub-Section (2) of Section 12</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="no_women_deprived_mater_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_women_deprived_mater) ? $get_emplm_dism_pay_bonus_women->no_women_deprived_mater : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['no_case_claims_contested']	=	array(
			'#title' 			=> t('<strong>15. (a) No. of cases where claims were contested in a court of law</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="no_case_claims_contested_id"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->no_case_claims_contested) ? $get_emplm_dism_pay_bonus_women->no_case_claims_contested : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['emplm_dism_women']['result_case_claims_contested']	=	array(
			'#title' 			=> t('<strong>(b) Result of such cases</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="result_case_claims_contested_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_emplm_dism_pay_bonus_women->result_case_claims_contested) ? $get_emplm_dism_pay_bonus_women->result_case_claims_contested : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		
		$form['emplm_women_submit']['submit'] = array (
			'#prefix' 		=> '',  
			'#suffix' 		=> '',
			'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
			'#type' 		=> 'submit',
			'#value'		=> 'Save & Continue'
		);
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'applicant/maternity-benefit-apply/hospital_details/'.$annual_returnID.'/'.$factoryID, array(
				'html' => TRUE,
				'attributes' => array('class' => array('btn btn-outline-dark pull-left'))
			))
		);
		
		$form['maternity_benefit_link_markup'] = array(
				
				'#type'		=> 'markup',
				'#prefix'	=> '<div class="row">
									<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
									'.$common_section_edit.$payment_wages_edit.$factories_act_edit.'',
				'#suffix' => '		</div>
								</div>',
		);
		
		return $form;
	
	
	}
	
	function emplm_dism_pay_bonus_women_maternity_submit($form, &$form_state){
		//echo '<pre>'; print_r($form_state); die();
		
		global $base_root,$base_path,$user;
		$uid 							= $user->uid;
		
		$annual_return_ID = $form_state['values']['annual_return_id'];
		$factory_id = $form_state['values']['factory_id'];
		
		$val = $form_state['values'];
		
		$get_emplm_dism_pay_bonus_women = get_emplm_dism_pay_bonus_women($annual_return_ID);
		
		if($get_emplm_dism_pay_bonus_women->annual_return_id != NULL && count($get_emplm_dism_pay_bonus_women) > 0) {
			$emplm_dism_pay_bonus_women = array(
				'annual_return_id' => $val['annual_return_id'],
				
				'agg_no_women_per_temp_emp_year' => $val['agg_no_women_per_temp_emp_year'],
				'avg_daily_no_women_emp' => $val['avg_daily_no_women_emp'],
				'no_women_worked_for_perd' => $val['no_women_worked_for_perd'],
				'no_women_gave_notice' 	 => $val['no_women_gave_notice'],
				
				'grant_permi_abse_undisp_prev_year' => $val['grant_permi_abse_undisp_prev_year'],
				'grant_permi_abse_curr_year' => $val['grant_permi_abse_curr_year'],
				
				'no_claims_mater_paid_undisp_prev_year' => $val['no_claims_mater_paid_undisp_prev_year'],
				'no_claims_mater_paid_curr_year' 	 => $val['no_claims_mater_paid_curr_year'],
				'no_claims_mater_reject_undisp_prev_year' => $val['no_claims_mater_reject_undisp_prev_year'],
				'no_claims_mater_reject_curr_year' => $val['no_claims_mater_reject_curr_year'],
				
				'no_claims_medi_paid_undisp_prev_year' => $val['no_claims_medi_paid_undisp_prev_year'],
				'no_claims_medi_paid_curr_year' 	 => $val['no_claims_medi_paid_curr_year'],
				'no_claims_medi_reject_undisp_prev_year' => $val['no_claims_medi_reject_undisp_prev_year'],
				'no_claims_medi_reject_curr_year' => $val['no_claims_medi_reject_curr_year'],
				
				'no_case_miscarr_grant_undisp_prev_year' => $val['no_case_miscarr_grant_undisp_prev_year'],
				'no_case_miscarr_grant_curr_year' 	 => $val['no_case_miscarr_grant_curr_year'],
				'no_case_miscarr_reject_undisp_prev_year' => $val['no_case_miscarr_reject_undisp_prev_year'],
				'no_case_miscarr_reject_curr_year' => $val['no_case_miscarr_reject_curr_year'],
				
				'no_case_illness_grant_undisp_prev_year' => $val['no_case_illness_grant_undisp_prev_year'],
				'no_case_illness_grant_curr_year' 	 => $val['no_case_illness_grant_curr_year'],
				'no_case_illness_reject_undisp_prev_year' => $val['no_case_illness_reject_undisp_prev_year'],
				'no_case_illness_reject_curr_year' => $val['no_case_illness_reject_curr_year'],
				
				'no_case_natal_confine_care' => $val['no_case_natal_confine_care'],
				'no_women_died_before_dlvry' 	 => $val['no_women_died_before_dlvry'],
				'no_women_died_after_dlvry' => $val['no_women_died_after_dlvry'],
				'no_infants_died_on_dob' => $val['no_infants_died_on_dob'],
				'no_infants_died_during_six_weeks' => $val['no_infants_died_during_six_weeks'],
				'no_women_discharge_work' 	 => $val['no_women_discharge_work'],
				'no_women_deprived_mater' => $val['no_women_deprived_mater'],
				'no_case_claims_contested' => $val['no_case_claims_contested'],
				'result_case_claims_contested' => $val['result_case_claims_contested'],
				
				'uid' => $uid,
				'modification_date'	   => date('Y-m-d H:i:s'),
			);
			db_update('fa_ar_emplm_dism_pay_bonus_women')->fields($emplm_dism_pay_bonus_women)->condition('annual_return_id', $annual_return_ID, '=')->execute();	
		} else {
			$emplm_dism_pay_bonus_women = array(
				'annual_return_id' => $val['annual_return_id'],
				
				'agg_no_women_per_temp_emp_year' => $val['agg_no_women_per_temp_emp_year'],
				'avg_daily_no_women_emp' => $val['avg_daily_no_women_emp'],
				'no_women_worked_for_perd' => $val['no_women_worked_for_perd'],
				'no_women_gave_notice' 	 => $val['no_women_gave_notice'],
				
				'grant_permi_abse_undisp_prev_year' => $val['grant_permi_abse_undisp_prev_year'],
				'grant_permi_abse_curr_year' => $val['grant_permi_abse_curr_year'],
				
				'no_claims_mater_paid_undisp_prev_year' => $val['no_claims_mater_paid_undisp_prev_year'],
				'no_claims_mater_paid_curr_year' 	 => $val['no_claims_mater_paid_curr_year'],
				'no_claims_mater_reject_undisp_prev_year' => $val['no_claims_mater_reject_undisp_prev_year'],
				'no_claims_mater_reject_curr_year' => $val['no_claims_mater_reject_curr_year'],
				
				'no_claims_medi_paid_undisp_prev_year' => $val['no_claims_medi_paid_undisp_prev_year'],
				'no_claims_medi_paid_curr_year' 	 => $val['no_claims_medi_paid_curr_year'],
				'no_claims_medi_reject_undisp_prev_year' => $val['no_claims_medi_reject_undisp_prev_year'],
				'no_claims_medi_reject_curr_year' => $val['no_claims_medi_reject_curr_year'],
				
				'no_case_miscarr_grant_undisp_prev_year' => $val['no_case_miscarr_grant_undisp_prev_year'],
				'no_case_miscarr_grant_curr_year' 	 => $val['no_case_miscarr_grant_curr_year'],
				'no_case_miscarr_reject_undisp_prev_year' => $val['no_case_miscarr_reject_undisp_prev_year'],
				'no_case_miscarr_reject_curr_year' => $val['no_case_miscarr_reject_curr_year'],
				
				'no_case_illness_grant_undisp_prev_year' => $val['no_case_illness_grant_undisp_prev_year'],
				'no_case_illness_grant_curr_year' 	 => $val['no_case_illness_grant_curr_year'],
				'no_case_illness_reject_undisp_prev_year' => $val['no_case_illness_reject_undisp_prev_year'],
				'no_case_illness_reject_curr_year' => $val['no_case_illness_reject_curr_year'],
				
				'no_case_natal_confine_care' => $val['no_case_natal_confine_care'],
				'no_women_died_before_dlvry' 	 => $val['no_women_died_before_dlvry'],
				'no_women_died_after_dlvry' => $val['no_women_died_after_dlvry'],
				'no_infants_died_on_dob' => $val['no_infants_died_on_dob'],
				'no_infants_died_during_six_weeks' => $val['no_infants_died_during_six_weeks'],
				'no_women_discharge_work' 	 => $val['no_women_discharge_work'],
				'no_women_deprived_mater' => $val['no_women_deprived_mater'],
				'no_case_claims_contested' => $val['no_case_claims_contested'],
				'result_case_claims_contested' => $val['result_case_claims_contested'],
								
				'uid' => $uid,
				'created_date'		   => date('Y-m-d'),
			);
			$emplm_dism_pay_bonus_women_id = db_insert('fa_ar_emplm_dism_pay_bonus_women')->fields($emplm_dism_pay_bonus_women)->execute();	
		}
		
		
		drupal_goto('applicant/maternity-benefit-apply/details_of_payment/'.encryption_decryption_fun('encrypt', $annual_return_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));
		
		
		
		
	}