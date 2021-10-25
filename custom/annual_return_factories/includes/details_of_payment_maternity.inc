<?php

	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
  	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	
	function details_of_payment_maternity($form, &$form_state, $annual_returnID = '', $factoryID = '') {
	
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
		
		$get_emplm_dism_pay_bonus_women = get_emplm_dism_pay_bonus_women($annual_return_ID);
		if($get_emplm_dism_pay_bonus_women->annual_return_id == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/maternity-benefit-apply/emplm_dism_pay_bonus_women/'.$annual_returnID.'/'.$factoryID) ;
		}
		
		
		$get_wages_paid_include_deduction = get_total_wages_paid_include_deduction($annual_return_ID);
		$get_disbursement_fine_funds = get_disbursement_fine_funds($annual_return_ID);
		$get_factory_act_all_data = get_factory_act_all_data($annual_return_ID);
		
		$get_details_payment = get_details_of_payment($annual_return_ID);
		
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
		
		$form['details_payment'] = array(
			'#type' => 'fieldset',
			'#title' => t('Details of Payment'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => FALSE // Added 
		);
		
		$form['details_payment']['tot_amt_addl_leave_paid_year']	=	array(
			'#title' 			=> t('<strong>1. Total amount of Maternity Benefit, Maternity Bonus and Wages for additional leave paid during the year</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div class="row"><div id="tot_amt_addl_leave_paid_year_id"><div class="col-md-9 col-xs-9"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			//'#default_value'	=> !empty($get_details_payment->tot_amt_addl_leave_paid_year) ? $get_details_payment->tot_amt_addl_leave_paid_year : '',
			'#default_value'	=> $get_factory_info->annual_return_year, 
			'#attributes' 		=> array('class'=>array(''), 'placeholder' => 'Enter Year', 'readonly' => 'readonly'),
			'#maxlength' 		=> 4,
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['tot_amt_addl_leave_paid_rs']	=	array(
			'#title' 			=> t('<strong>Rs.</strong>'),
			'#type'				=>	'textfield',
			'#prefix'			=>	'<div id="tot_amt_addl_leave_paid_rs_id"><div class="col-md-3 col-xs-3"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_details_payment->tot_amt_addl_leave_paid_rs) ? $get_details_payment->tot_amt_addl_leave_paid_rs : '', 
			'#attributes' 		=> array('class'=>array(''), 'placeholder' => 'Enter Amount'),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['details_payment_table_start']	=	array(
			'#type'		=> 'markup',
			'#prefix'			=>	'<div id="details_payment_table_id"><div class="col-md-12 col-xs-12"><label class="select label-block"><strong>2. Details of Payment</strong>
									<br>
									<table class="custom-table-view-dashboard renewal-table" width="100%">
										<tr>
											<th width="15%"></th>
											<th width="10%">No. of cases</th>
											<th width="15%">Amount of Maternity Benefits for the period preceding the date of expected delivery</th>
											<th width="15%">Amount of Maternity Benefits for the subsequent period</th>
											<th width="15%">Payment of medical bonus under Section 8</th>
											<th width="15%">Payment of leave with wages under Section 9</th>
											<th width="15%">Payment of leave for illness under Section 10</th>
										</tr>',
		);
		
		$form['details_payment']['details_payment_women_employed'] = array(
			'#prefix'			=> '<tr><td><div id="details_payment_women_employed_id"><div class="col-xs-12"><label class="select label-block"><strong>Women employed</strong>',
			'#suffix'			=> '</label></div></div></td>',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['women_employed_no_cases']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="women_employed_no_cases_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_details_payment->women_employed_no_cases) ? $get_details_payment->women_employed_no_cases : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['women_employed_amt_exptd_delivery']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="women_employed_amt_expected_delivery_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_details_payment->women_employed_amt_exptd_delivery) ? $get_details_payment->women_employed_amt_exptd_delivery : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['women_employed_amt_subseq_perd']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="women_employed_amt_subseq_perd_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_details_payment->women_employed_amt_subseq_perd) ? $get_details_payment->women_employed_amt_subseq_perd : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['women_employed_pymt_med_bonus']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="women_employed_pymt_med_bonus_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_details_payment->women_employed_pymt_med_bonus) ? $get_details_payment->women_employed_pymt_med_bonus : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['women_employed_pymt_leave_wages']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="women_employed_pymt_leave_wages_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_details_payment->women_employed_pymt_leave_wages) ? $get_details_payment->women_employed_pymt_leave_wages : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['women_employed_pymt_leave_illness']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="women_employed_pymt_leave_illness_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td></tr>',
			'#default_value'	=> !empty($get_details_payment->women_employed_pymt_leave_illness) ? $get_details_payment->women_employed_pymt_leave_illness : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		//
		$form['details_payment']['details_payment_nominee_women'] = array(
			'#prefix'			=> '<tr><td><div id="details_payment_nominee_women_id"><div class="col-xs-12"><label class="select label-block"><strong>Nominee of the women</strong>',
			'#suffix'			=> '</label></div></div></td>',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['nominee_women_no_cases']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="nominee_women_no_cases_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_details_payment->nominee_women_no_cases) ? $get_details_payment->nominee_women_no_cases : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['nominee_women_amt_exptd_delivery']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="nominee_women_amt_exptd_delivery_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_details_payment->nominee_women_amt_exptd_delivery) ? $get_details_payment->nominee_women_amt_exptd_delivery : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['nominee_women_amt_subseq_perd']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="nominee_women_amt_subseq_perd_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_details_payment->nominee_women_amt_subseq_perd) ? $get_details_payment->nominee_women_amt_subseq_perd : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['nominee_women_pymt_med_bonus']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="nominee_women_pymt_med_bonus_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_details_payment->nominee_women_pymt_med_bonus) ? $get_details_payment->nominee_women_pymt_med_bonus : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['nominee_women_pymt_leave_wages']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="nominee_women_pymt_leave_wages_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_details_payment->nominee_women_pymt_leave_wages) ? $get_details_payment->nominee_women_pymt_leave_wages : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['nominee_women_pymt_leave_illness']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="nominee_women_pymt_leave_illness_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td></tr>',
			'#default_value'	=> !empty($get_details_payment->nominee_women_pymt_leave_illness) ? $get_details_payment->nominee_women_pymt_leave_illness : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		//
		$form['details_payment']['details_payment_legal_repr_women'] = array(
			'#prefix'			=> '<tr><td><div id="details_payment_legal_represent_women_id"><div class="col-xs-12"><label class="select label-block"><strong>Legal representative of the women</strong>',
			'#suffix'			=> '</label></div></div></td>',
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['legal_repr_women_no_cases']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="legal_repr_women_no_cases_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_details_payment->legal_repr_women_no_cases) ? $get_details_payment->legal_repr_women_no_cases : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['legal_repr_women_amt_exptd_delivery']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="legal_repr_women_amt_exptd_delivery_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_details_payment->legal_repr_women_amt_exptd_delivery) ? $get_details_payment->legal_repr_women_amt_exptd_delivery : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['legal_repr_women_amt_subseq_perd']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="legal_repr_women_amt_subseq_perd_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_details_payment->legal_repr_women_amt_subseq_perd) ? $get_details_payment->legal_repr_women_amt_subseq_perd : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['legal_repr_women_pymt_med_bonus']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="legal_repr_women_pymt_med_bonus_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_details_payment->legal_repr_women_pymt_med_bonus) ? $get_details_payment->legal_repr_women_pymt_med_bonus : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['legal_repr_women_pymt_leave_wages']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="legal_repr_women_pymt_leave_wages_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td>',
			'#default_value'	=> !empty($get_details_payment->legal_repr_women_pymt_leave_wages) ? $get_details_payment->legal_repr_women_pymt_leave_wages : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['legal_repr_women_pymt_leave_illness']	=	array(
			'#type'				=> 'textfield',
			'#prefix'			=> '<td><div id="legal_repr_women_pymt_leave_illness_id"><div class="col-xs-12"><label class="select label-block">',
			'#suffix'			=> '</label></div></div></td></tr>',
			'#default_value'	=> !empty($get_details_payment->legal_repr_women_pymt_leave_illness) ? $get_details_payment->legal_repr_women_pymt_leave_illness : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['details_payment_table_end'] 	= array(
			'#suffix' => '</table>
							</label></div></div>',
			'#type'	  => 'markup',
			'#markup' => '',	
		);
		
		$form['details_payment']['no_cases_pymt_order_insp']	=	array(
			'#title' 			=> t('<strong>3. No. of cases in which payment was made on the order of competent Authority or Inspector</strong>'),
			'#type'				=> 'textfield',
			'#prefix'			=>	'<div id="no_cases_pymt_order_insp_id"><div class="col-md-8 col-xs-8"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_details_payment->no_cases_pymt_order_insp) ? $get_details_payment->no_cases_pymt_order_insp : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['no_women_worker_recv_first_instal']	=	array(
			'#title' 			=> t('<strong>4. Number of women workers who absconded after receiving the first installment of maternity benefits</strong>'),
			'#type'				=> 'textfield',
			'#prefix'			=>	'<div id="no_women_worker_recv_first_instal_id"><div class="col-md-8 col-xs-8"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div>',
			'#default_value'	=> !empty($get_details_payment->no_women_worker_recv_first_instal) ? $get_details_payment->no_women_worker_recv_first_instal : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		$form['details_payment']['details_payment_remarks']	=	array(
			'#title' 			=> t('<strong>5. Remarks</strong>'),
			'#type'				=> 'textfield',
			'#prefix'			=>	'<div id="details_payment_remarks_id"><div class="col-md-12 col-xs-12"><label class="select label-block">',
			'#suffix'			=>	'</label></div></div></div>',
			'#default_value'	=> !empty($get_details_payment->details_payment_remarks) ? $get_details_payment->details_payment_remarks : '', 
			'#attributes' 		=> array('class'=>array('')),
			'#required' 		=> TRUE,
		);
		
		
		$form['details_payment_submit']['submit'] = array (
			'#prefix' 		=> '',  
			'#suffix' 		=> '',
			'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
			'#type' 		=> 'submit',
			'#value'		=> 'Save & Continue'
		);
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'applicant/maternity-benefit-apply/emplm_dism_pay_bonus_women/'.$annual_returnID.'/'.$factoryID, array(
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
	
	function details_of_payment_maternity_submit($form, &$form_state){
		//echo '<pre>'; print_r($form_state); die();
		
		global $base_root,$base_path,$user;
		$uid 							= $user->uid;
		
		$annual_return_ID = $form_state['values']['annual_return_id'];
		$factory_id = $form_state['values']['factory_id'];
		
		$val = $form_state['values'];
		
		$get_details_payment = get_details_of_payment($annual_return_ID);
		
		if($get_details_payment->annual_return_id != NULL && count($get_details_payment) > 0) {
			$details_payment = array(
				'annual_return_id' => $val['annual_return_id'],
				
				'tot_amt_addl_leave_paid_year' => $val['tot_amt_addl_leave_paid_year'],
				'tot_amt_addl_leave_paid_rs' => $val['tot_amt_addl_leave_paid_rs'],
				
				'women_employed_no_cases' => $val['women_employed_no_cases'],
				'women_employed_amt_exptd_delivery' 	 => $val['women_employed_amt_exptd_delivery'],
				'women_employed_amt_subseq_perd' => $val['women_employed_amt_subseq_perd'],
				'women_employed_pymt_med_bonus' => $val['women_employed_pymt_med_bonus'],
				'women_employed_pymt_leave_wages' => $val['women_employed_pymt_leave_wages'],
				'women_employed_pymt_leave_illness' 	 => $val['women_employed_pymt_leave_illness'],
				
				'nominee_women_no_cases' => $val['nominee_women_no_cases'],
				'nominee_women_amt_exptd_delivery' => $val['nominee_women_amt_exptd_delivery'],
				'nominee_women_amt_subseq_perd' => $val['nominee_women_amt_subseq_perd'],
				'nominee_women_pymt_med_bonus' 	 => $val['nominee_women_pymt_med_bonus'],
				'nominee_women_pymt_leave_wages' => $val['nominee_women_pymt_leave_wages'],
				'nominee_women_pymt_leave_illness' => $val['nominee_women_pymt_leave_illness'],
				
				'legal_repr_women_no_cases' => $val['legal_repr_women_no_cases'],
				'legal_repr_women_amt_exptd_delivery' 	 => $val['legal_repr_women_amt_exptd_delivery'],
				'legal_repr_women_amt_subseq_perd' => $val['legal_repr_women_amt_subseq_perd'],
				'legal_repr_women_pymt_med_bonus' => $val['legal_repr_women_pymt_med_bonus'],
				'legal_repr_women_pymt_leave_wages' => $val['legal_repr_women_pymt_leave_wages'],
				'legal_repr_women_pymt_leave_illness' 	 => $val['legal_repr_women_pymt_leave_illness'],
				
				'no_cases_pymt_order_insp' => $val['no_cases_pymt_order_insp'],
				'no_women_worker_recv_first_instal' => $val['no_women_worker_recv_first_instal'],
				'details_payment_remarks' => $val['details_payment_remarks'],
				
				'uid' => $uid,
				'modification_date'	   => date('Y-m-d H:i:s'),
			);
			db_update('fa_ar_details_payment')->fields($details_payment)->condition('annual_return_id', $annual_return_ID, '=')->execute();	
		} else {
			$details_payment = array(
				'annual_return_id' => $val['annual_return_id'],
				
				'tot_amt_addl_leave_paid_year' => $val['tot_amt_addl_leave_paid_year'],
				'tot_amt_addl_leave_paid_rs' => $val['tot_amt_addl_leave_paid_rs'],
				
				'women_employed_no_cases' => $val['women_employed_no_cases'],
				'women_employed_amt_exptd_delivery' 	 => $val['women_employed_amt_exptd_delivery'],
				'women_employed_amt_subseq_perd' => $val['women_employed_amt_subseq_perd'],
				'women_employed_pymt_med_bonus' => $val['women_employed_pymt_med_bonus'],
				'women_employed_pymt_leave_wages' => $val['women_employed_pymt_leave_wages'],
				'women_employed_pymt_leave_illness' 	 => $val['women_employed_pymt_leave_illness'],
				
				'nominee_women_no_cases' => $val['nominee_women_no_cases'],
				'nominee_women_amt_exptd_delivery' => $val['nominee_women_amt_exptd_delivery'],
				'nominee_women_amt_subseq_perd' => $val['nominee_women_amt_subseq_perd'],
				'nominee_women_pymt_med_bonus' 	 => $val['nominee_women_pymt_med_bonus'],
				'nominee_women_pymt_leave_wages' => $val['nominee_women_pymt_leave_wages'],
				'nominee_women_pymt_leave_illness' => $val['nominee_women_pymt_leave_illness'],
				
				'legal_repr_women_no_cases' => $val['legal_repr_women_no_cases'],
				'legal_repr_women_amt_exptd_delivery' 	 => $val['legal_repr_women_amt_exptd_delivery'],
				'legal_repr_women_amt_subseq_perd' => $val['legal_repr_women_amt_subseq_perd'],
				'legal_repr_women_pymt_med_bonus' => $val['legal_repr_women_pymt_med_bonus'],
				'legal_repr_women_pymt_leave_wages' => $val['legal_repr_women_pymt_leave_wages'],
				'legal_repr_women_pymt_leave_illness' 	 => $val['legal_repr_women_pymt_leave_illness'],
				
				'no_cases_pymt_order_insp' => $val['no_cases_pymt_order_insp'],
				'no_women_worker_recv_first_instal' => $val['no_women_worker_recv_first_instal'],
				'details_payment_remarks' => $val['details_payment_remarks'],
								
				'uid' => $uid,
				'created_date'		   => date('Y-m-d'),
			);
			$details_payment_id = db_insert('fa_ar_details_payment')->fields($details_payment)->execute();	
		}
		
		drupal_goto('applicant/ar-application-preview/ar_common_app_preview/'.encryption_decryption_fun('encrypt', $annual_return_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));
		
	}