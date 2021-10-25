<?php
	
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
  	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
		
  	function payment_wages_return($form, &$form_state, $annual_returnID = '', $factoryID = ''){
		
  		//drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
		
		//drupal_add_js(drupal_get_path('module', 'annual_return_factories') .'/js/annual_return_factories.js', 'file');
	  
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
		
		$get_leave_wages_details = get_leave_wages_details($annual_return_ID);
		if($get_leave_wages_details->annual_return_id == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/annual-return-common-apply/leave_wages/'.$annual_returnID.'/'.$factoryID) ;
		}
		
		//die($annual_return_ID.' AND '.$factory_id);
		
		
		$get_wages_paid_include_deduction = get_total_wages_paid_include_deduction($annual_return_ID);
		$get_disbursement_fine_funds = get_disbursement_fine_funds($annual_return_ID);
		
		$get_factory_act_all_data = get_factory_act_all_data($annual_return_ID);
		$get_maternity_benefit_all_data = get_maternity_benefit_all_data($annual_return_ID);
		
		$form = array();
		
		/*$form['header']            = array(
        	'#markup' => t('<div class="content"><h3>ANNUAL RETURN UNDER THE WEST BENGAL PAYMENT OF WAGES RULES</h3>')
    	);*/
		
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
		
		
		$form['payment_wages_total_wages'] = array(
		'#type' => 'fieldset',
		'#title' => t('1. Total wages paid'),
		'#collapsible' => TRUE, // Added
		'#collapsed' => FALSE // Added 
		);
		
		$form['payment_wages_total_wages']['payment_wages_total_wages_table_start']	=	array( '#prefix' => '<div class="row">
														<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
															<div class="">
																				<table width="100%" cellspacing="0" cellpadding="0" class="">
																					  <tr>
																						<th width="82%"><b>1. Total wages paid include deduction under Section 7(2) on the following accounts:</b> <span class="form-required">*</span></th>
																						<th width=""18%">Rs.</th>
																						
																					  </tr>'																					
												);
		
		
		$form['payment_wages_total_wages']['total_wages_profit_bonus']	=	array(	'#prefix'		=>	'<tr><td><strong>(a) Profit sharing bonus-</strong></td><td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td></tr>',
			'#default_value'	=> !empty($get_wages_paid_include_deduction->total_wages_profit_bonus) ? $get_wages_paid_include_deduction->total_wages_profit_bonus : '', 
			'#attributes' 		=> array('class'=>array('form-control', 'rs_amount'), 'id'=>'total_wages_profit_bonus_id'),
			'#element_validate'	=> array('element_validate_rs_amount_nontitle'),
			'#required' 		=> TRUE,
		);
		
		$form['payment_wages_total_wages']['total_wages_money_value']	=	array(	'#prefix'		=>	'<tr><td><strong>***(b) Money value of concessions-</strong></td><td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td></tr>',
			'#default_value'	=> !empty($get_wages_paid_include_deduction->total_wages_money_value) ? $get_wages_paid_include_deduction->total_wages_money_value : '', 
			'#attributes' 		=> array('class'=>array('form-control', 'rs_amount'), 'id'=>'total_wages_money_value_id'),
			'#element_validate'	=> array('element_validate_rs_amount_nontitle'),
			'#required' 		=> TRUE,
		);
		
		$form['payment_wages_total_wages']['total_wages_basic_wages']	=	array(	'#prefix'		=>	'<tr><td><strong>(c) Basic wages including overtime and non-profit sharing bonus-</strong></td><td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td></tr>',
			'#default_value'	=> !empty($get_wages_paid_include_deduction->total_wages_basic_wages) ? $get_wages_paid_include_deduction->total_wages_basic_wages : '', 
			'#attributes' 		=> array('class'=>array('form-control', 'rs_amount'), 'id'=>'total_wages_basic_wages_id'),
			'#element_validate'	=> array('element_validate_rs_amount_nontitle'),
			'#required' 		=> TRUE,
		);
																						
		$form['payment_wages_total_wages']['total_wages_da'] =	array(	'#prefix'		=>	'<tr><td><strong>(d) Dearness and other allowances(not in kind)-</strong></td><td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td></tr>',
			'#default_value'	=> !empty($get_wages_paid_include_deduction->total_wages_da) ? $get_wages_paid_include_deduction->total_wages_da : '', 
			'#attributes' 		=> array('class'=>array('form-control', 'rs_amount'), 'id'=>'total_wages_da_id'),
			'#element_validate'	=> array('element_validate_rs_amount_nontitle'),
			'#required' 		=> TRUE,
		);										
												
		$form['payment_wages_total_wages']['total_wages_arrears_pay']	=	array(	'#prefix'		=>	'<tr><td><strong>(e) Arrears of pay in respect of the previous years paid during the year-</strong></td><td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td></tr>',
			'#default_value'	=> !empty($get_wages_paid_include_deduction->total_wages_arrears_pay) ? $get_wages_paid_include_deduction->total_wages_arrears_pay : '', 
			'#attributes' 		=> array('class'=>array('form-control', 'rs_amount'), 'id'=>'total_wages_arrears_pay_id'),
			'#element_validate'	=> array('element_validate_rs_amount_nontitle'),
			'#required' 		=> TRUE,
		);
												
		$form['payment_wages_total_wages']['total_wages_total_amt']			=	array(	'#prefix'		=>	'<tr><td align="right"><strong>Total:</strong></td><td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td></tr>',
			'#default_value'	=> !empty($get_wages_paid_include_deduction->total_wages_total_amt) ? $get_wages_paid_include_deduction->total_wages_total_amt : '', 
			'#attributes' 		=> array('class'=>array('form-control', 'rs_amount'), 'readonly' => 'readonly', 'id'=>'total_wages_total_amt_id'),
			'#element_validate'	=> array('element_validate_rs_amount_nontitle'),
			//'#required' 		=> TRUE,
		);
																				
		
		$form['payment_wages_total_wages']['payment_wages_total_wages_table_end']					=	array( 	'#suffix' 		=>	'
																			</table>
																			</div></div></div>'
		);
		
		
		 $form['payment_wages_deductions'] = array(
			'#type' => 'fieldset',
			'#title' => t('2. Deductions'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => FALSE // Added 
		 );
		 
		 $form['payment_wages_deductions']['payment_wages_deductions_start_table']	=	array( '#prefix' => '<div class="row">
															<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
																<div class="">
																					<table width="100%" cellspacing="0" cellpadding="0" class="">
																						  <tr>
																							<th width="64%"><b>2. Deductions-Number of cases and amount realised</b> <span class="form-required">*</span></th>
																							<th width="18%">Number of cases</th>
																							<th width="18%">Amount realised(Rs.)</th>
																							
																						  </tr>'																					
													);
													
		$form['payment_wages_deductions']['deductions_fines_no_cases']	=	array(	'#prefix'		=>	'<tr><td><strong>(a) Fines</strong></td><td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td>',
			'#default_value'	=> !empty($get_wages_paid_include_deduction->deductions_fines_no_cases) ? $get_wages_paid_include_deduction->deductions_fines_no_cases : '', 
			'#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'deductions_fines_no_cases_id'),
			'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			'#required' 		=> TRUE,
		);
		
		$form['payment_wages_deductions']['deductions_fines_amt_realised']	=	array(	'#prefix'		=>	'<td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td></tr>',
			'#default_value'	=> !empty($get_wages_paid_include_deduction->deductions_fines_amt_realised) ? $get_wages_paid_include_deduction->deductions_fines_amt_realised : '', 
			'#attributes' 		=> array('class'=>array('form-control', 'rs_amount'), 'id'=>'deductions_fines_amt_realised_id'),
			'#element_validate'	=> array('element_validate_rs_amount_nontitle'),
			'#required' 		=> TRUE,
														
		);
		
		$form['payment_wages_deductions']['deductions_damg_loss_no_cases']	=	array(	'#prefix'		=>	'<tr><td><strong>(b) Deductions for damage or loss</strong></td><td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td>',
			'#default_value'	=> !empty($get_wages_paid_include_deduction->deductions_damg_loss_no_cases) ? $get_wages_paid_include_deduction->deductions_damg_loss_no_cases : '', 
			'#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'deductions_damg_loss_no_cases_id'),
			'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			'#required' 		=> TRUE,
		);
		
		$form['payment_wages_deductions']['deductions_damg_loss_amt_realised']	=	array(	'#prefix'		=>	'<td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td></tr>',
			'#default_value'	=> !empty($get_wages_paid_include_deduction->deductions_damg_loss_amt_realised) ? $get_wages_paid_include_deduction->deductions_damg_loss_amt_realised : '', 
			'#attributes' 		=> array('class'=>array('form-control', 'rs_amount'), 'id'=>'deductions_damg_loss_amt_realised_id'),
			'#element_validate'	=> array('element_validate_rs_amount_nontitle'),
			'#required' 		=> TRUE,
														
		);
		
		$form['payment_wages_deductions']['deductions_breach_contct_no_cases']	=	array(	'#prefix'		=>	'<tr><td><strong>(c) Deduction for breach of contract</strong></td><td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td>',
			'#default_value'	=> !empty($get_wages_paid_include_deduction->deductions_breach_contct_no_cases) ? $get_wages_paid_include_deduction->deductions_breach_contct_no_cases : '', 
			'#attributes' 		=> array('class'=>array('form-control', 'numeric_positive'), 'id'=>'deductions_breach_contct_no_cases_id'),
			'#element_validate'	=> array('QUANTITY_FIELD_VALIDATION'),
			'#required' 		=> TRUE,
		);
		
		$form['payment_wages_deductions']['deductions_breach_contct_amt_realised']	=	array(	'#prefix'		=>	'<td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td></tr>',
			'#default_value'	=> !empty($get_wages_paid_include_deduction->deductions_breach_contct_amt_realised) ? $get_wages_paid_include_deduction->deductions_breach_contct_amt_realised : '', 
			'#attributes' 		=> array('class'=>array('form-control', 'rs_amount'), 'id'=>'deductions_breach_contct_amt_realised_id'),
			'#element_validate'	=> array('element_validate_rs_amount_nontitle'),
			'#required' 		=> TRUE,
														
		);
		
		$form['payment_wages_deductions']['deductions_total_amt']			=	array(	'#prefix'		=>	'<tr><td></td><td><strong>Total:</strong></td><td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td></tr>',
			'#default_value'	=> !empty($get_wages_paid_include_deduction->deductions_total_amt) ? $get_wages_paid_include_deduction->deductions_total_amt : '', 
			'#attributes' 		=> array('class'=>array('form-control', 'rs_amount'), 'readonly'=>'readonly', 'id'=>'deductions_total_amt_id'),
			'#element_validate'	=> array('element_validate_rs_amount_nontitle'),
			//'#required' 		=> TRUE,
		);
													
		$form['payment_wages_deductions']['payment_wages_deductions_end_table']					=	array( 	'#suffix' 		=>	'
																				</table>
																				</div></div></div>'
		);
													
		 $form['payment_wages_fines_fund'] = array(
			'#type' => 'fieldset',
			'#title' => t('3. Fines fund'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => FALSE // Added 
		 );
		 
		$form['payment_wages_fines_fund']['balance_fines_fund_beginning_year'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t('(i) Balance of fines fund in hand at the beginning of the year Rs.'),
			'#type' 			=> 'textfield',
			'#default_value'	=> !empty($get_disbursement_fine_funds->balance_fines_fund_beginning_year) ? $get_disbursement_fine_funds->balance_fines_fund_beginning_year : '', 
			'#attributes' 		=> array('class'=>array('form-control', 'rs_amount'), 'id'=>'balance_fines_fund_beginning_year_id'),
			'#element_validate'	=> array('element_validate_rs_amount_nontitle'),
			'#required' 		=> TRUE,
		);
		
		$form['payment_wages_fines_fund']['payment_wages_fines_fund_start_table']					=	array( '#prefix' => '<div class="row">
																			<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
																				<div class="">
																				<table width="100%" cellspacing="0" cellpadding="0" class="">
																					  <tr>
																						<th colspan="3">(ii) Disbursement from fine funds<span class="form-required">*</span></th>
																					   </tr>
																					   <tr>
																					   	<th width="5%"></th>
																						<th width="77%">Purpose</th>
																						<th width="18%">Amount</th>
																						
																					  </tr>'																					
												);
		
		
		
		
		$form['payment_wages_fines_fund']['disbursement_a_purpose']					=	array(	'#prefix'		=>	'<tr><td><strong>(a)</strong></td><td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td>',
			'#default_value'	=> !empty($get_disbursement_fine_funds->disbursement_a_purpose) ? $get_disbursement_fine_funds->disbursement_a_purpose : '', 
			'#attributes' 		=> array('class'=>array('form-control'), 'id'=>'disbursement_a_purpose_id'),
			'#element_validate'	=> array('element_validate_alphabatic_fullstop_nontitle'),
			'#required' 		=> TRUE,
		);
		
		$form['payment_wages_fines_fund']['disbursement_a_amt']					=	array(	'#prefix'		=>	'<td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td></tr>',
			'#default_value'	=> !empty($get_disbursement_fine_funds->disbursement_a_amt) ? $get_disbursement_fine_funds->disbursement_a_amt : '', 
			'#attributes' 		=> array('class'=>array('form-control', 'rs_amount'), 'id'=>'disbursement_a_amt_id'),
			'#element_validate'	=> array('element_validate_rs_amount_nontitle'),
			'#required' 		=> TRUE,	
		);
												
		$form['payment_wages_fines_fund']['disbursement_b_purpose']					=	array(	'#prefix'		=>	'<tr><td><strong>(b)</strong></td><td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td>',
			'#default_value'	=> !empty($get_disbursement_fine_funds->disbursement_b_purpose) ? $get_disbursement_fine_funds->disbursement_b_purpose : '', 
			'#attributes' 		=> array('class'=>array('form-control'), 'id'=>'disbursement_b_purpose_id'),
			'#element_validate'	=> array('element_validate_alphabatic_fullstop_nontitle'),
			'#required' 		=> TRUE,
		);
		
		$form['payment_wages_fines_fund']['disbursement_b_amt']					=	array(	'#prefix'		=>	'<td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td></tr>',
			'#default_value'	=> !empty($get_disbursement_fine_funds->disbursement_b_amt) ? $get_disbursement_fine_funds->disbursement_b_amt : '', 
			'#attributes' 		=> array('class'=>array('form-control', 'rs_amount'), 'id'=>'disbursement_b_amt_id'),
			'#element_validate'	=> array('element_validate_rs_amount_nontitle'),
			'#required' 		=> TRUE,	
		);
												
		$form['payment_wages_fines_fund']['disbursement_c_purpose']					=	array(	'#prefix'		=>	'<tr><td><strong>(c)</strong></td><td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td>',
			'#default_value'	=> !empty($get_disbursement_fine_funds->disbursement_c_purpose) ? $get_disbursement_fine_funds->disbursement_c_purpose : '', 
			'#attributes' 		=> array('class'=>array('form-control'), 'id'=>'disbursement_c_purpose_id'),
			'#element_validate'	=> array('element_validate_alphabatic_fullstop_nontitle'),
			'#required' 		=> TRUE,
		);
		
		$form['payment_wages_fines_fund']['disbursement_c_amt']					=	array(	'#prefix'		=>	'<td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td></tr>',
			'#default_value'	=> !empty($get_disbursement_fine_funds->disbursement_c_amt) ? $get_disbursement_fine_funds->disbursement_c_amt : '', 
			'#attributes' 		=> array('class'=>array('form-control', 'rs_amount'), 'id'=>'disbursement_c_amt_id'),
			'#element_validate'	=> array('element_validate_rs_amount_nontitle'),
			'#required' 		=> TRUE,	
		);																							
												
		$form['payment_wages_fines_fund']['disbursement_d_purpose']					=	array(	'#prefix'		=>	'<tr><td><strong>(d)</strong></td><td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td>',
			'#default_value'	=> !empty($get_disbursement_fine_funds->disbursement_d_purpose) ? $get_disbursement_fine_funds->disbursement_d_purpose : '', 
			'#attributes' 		=> array('class'=>array('form-control'), 'id'=>'disbursement_d_purpose_id'),
			'#element_validate'	=> array('element_validate_alphabatic_fullstop_nontitle'),
			'#required' 		=> TRUE,
		);
		
		$form['payment_wages_fines_fund']['disbursement_d_amt']					=	array(	'#prefix'		=>	'<td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td></tr>',
			'#default_value'	=> !empty($get_disbursement_fine_funds->disbursement_d_amt) ? $get_disbursement_fine_funds->disbursement_d_amt : '', 
			'#attributes' 		=> array('class'=>array('form-control', 'rs_amount'), 'id'=>'disbursement_d_amt_id'),
			'#element_validate'	=> array('element_validate_rs_amount_nontitle'),
			'#required' 		=> TRUE,	
		);	
												
		$form['payment_wages_fines_fund']['disbursement_fines_fund_total_amt']			=	array(	'#prefix'		=>	'<tr><td></td><td align="right"><strong>Total:</strong></td><td>',
			'#type'			=>	'textfield',
			'#suffix'		=>	'</td></tr>',
			'#default_value'	=> !empty($get_disbursement_fine_funds->disbursement_fines_fund_total_amt) ? $get_disbursement_fine_funds->disbursement_fines_fund_total_amt : '', 
			'#attributes' 		=> array('class'=>array('form-control', 'rs_amount'), 'readonly'=>'readonly', 'id'=>'disbursement_fines_fund_total_amt_id'),
			'#element_validate'	=> array('element_validate_rs_amount_nontitle'),
			//'#required' 		=> TRUE,
		);	
							
		
		$form['payment_wages_fines_fund']['payment_wages_fines_fund_end_table']					=	array( 	'#suffix' 		=>	'
																			</table>
																			</div>
																			</div>
																			</div>'
																			
																			
												);
												
		$form['payment_wages_fines_fund']['balance_fines_fund_end_year'] = array(
			'#prefix' 			=> '<div class="row"><div class="col-md-6 col-xs-6"><label class="select label-block">',
			'#suffix' 			=> '</label></div></div>',
			'#title' 			=> t('(iii) Balance of fines fund in hand at the end of the year Rs.'),
			'#type' 			=> 'textfield',
			'#default_value'	=> !empty($get_disbursement_fine_funds->balance_fines_fund_end_year) ? $get_disbursement_fine_funds->balance_fines_fund_end_year : '', 
			'#attributes' 		=> array('class'=>array('form-control', 'rs_amount'), 'id'=>'balance_fines_fund_end_year_id'),
			'#element_validate'	=> array('element_validate_rs_amount_nontitle'),
			'#required' 		=> TRUE,
		);	
													
		
		$form['#attributes'] = array('onsubmit' => 'return validate_payment_wages_return_form()');
		 
		$form['payment_wages']['submit'] = array (
			'#prefix' 		=> '',  
			'#suffix' 		=> '',
			'#attributes' 	=> array('class' => array('btn btn-info pull-right')),
			'#type' 		=> 'submit',
			'#value'		=> 'Save & Continue'
		);
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'applicant/annual-return-common-apply/leave_wages/'.$annual_returnID.'/'.$factoryID, array(
				'html' => TRUE,
				'attributes' => array('class' => array('btn btn-outline-dark pull-left'))
			))
		);
		
		$form['payment_wages_link_markup'] = array(
				
				'#type'		=> 'markup',
				'#prefix'	=> '<div class="row">
									<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
									'.$common_section_edit.$factories_act_edit.$maternity_benefit_edit.'',
				'#suffix' => '		</div>
								</div>',
		);
		
		return $form;
	}

  
  
	function payment_wages_return_submit($form, &$form_state){
		//echo '<pre>'; print_r($form_state); die();
		
		global $base_root,$base_path,$user;
		$uid 							= $user->uid;
		
		$annual_return_ID = $form_state['values']['annual_return_id'];
		$factory_id = $form_state['values']['factory_id'];
		
		$val = $form_state['values'];
		
		$total_wages_total_amt = $val['total_wages_profit_bonus'] + $val['total_wages_money_value'] + $val['total_wages_basic_wages'] + $val['total_wages_da'] + 
		$val['total_wages_arrears_pay'];
		
		$deductions_total_amt = $val['deductions_fines_amt_realised'] + $val['deductions_damg_loss_amt_realised'] + $val['deductions_breach_contct_amt_realised'];
		
		$disbursement_fines_fund_total_amt = $val['disbursement_a_amt'] + $val['disbursement_b_amt'] + $val['disbursement_c_amt'] + $val['disbursement_d_amt'];
		
		
		//Total wages paid include deduction under Section 7(2) on the following accounts
		
		$total_wages_paid_include_deduction = get_total_wages_paid_include_deduction($annual_return_ID);
		if($total_wages_paid_include_deduction != NULL && count($total_wages_paid_include_deduction) > 0) {
			$wages_paid_deduction = array(
				'annual_return_id' => $val['annual_return_id'],
				'total_wages_profit_bonus' => $val['total_wages_profit_bonus'],
				'total_wages_money_value' => $val['total_wages_money_value'],
				'total_wages_basic_wages' => $val['total_wages_basic_wages'],
				'total_wages_da' => $val['total_wages_da'],
				'total_wages_arrears_pay' => $val['total_wages_arrears_pay'],
				'total_wages_total_amt' => $total_wages_total_amt,
				
				'deductions_fines_no_cases' => $val['deductions_fines_no_cases'],
				'deductions_fines_amt_realised' => $val['deductions_fines_amt_realised'],
				'deductions_damg_loss_no_cases' => $val['deductions_damg_loss_no_cases'],
				'deductions_damg_loss_amt_realised' => $val['deductions_damg_loss_amt_realised'],
				'deductions_breach_contct_no_cases' => $val['deductions_breach_contct_no_cases'],
				'deductions_breach_contct_amt_realised' => $val['deductions_breach_contct_amt_realised'],
				'deductions_total_amt' => $deductions_total_amt,
				
				'uid' => $uid,
				'modification_date'	   => date('Y-m-d H:i:s'),
			);
			db_update('fa_ar_wages_paid_deduction')->fields($wages_paid_deduction)->condition('annual_return_id', $annual_return_ID, '=')->execute();	
		} else {
			$wages_paid_deduction = array(
				'annual_return_id' => $val['annual_return_id'],
				'total_wages_profit_bonus' => $val['total_wages_profit_bonus'],
				'total_wages_money_value' => $val['total_wages_money_value'],
				'total_wages_basic_wages' => $val['total_wages_basic_wages'],
				'total_wages_da' => $val['total_wages_da'],
				'total_wages_arrears_pay' => $val['total_wages_arrears_pay'],
				'total_wages_total_amt' => $total_wages_total_amt,
				
				'deductions_fines_no_cases' => $val['deductions_fines_no_cases'],
				'deductions_fines_amt_realised' => $val['deductions_fines_amt_realised'],
				'deductions_damg_loss_no_cases' => $val['deductions_damg_loss_no_cases'],
				'deductions_damg_loss_amt_realised' => $val['deductions_damg_loss_amt_realised'],
				'deductions_breach_contct_no_cases' => $val['deductions_breach_contct_no_cases'],
				'deductions_breach_contct_amt_realised' => $val['deductions_breach_contct_amt_realised'],
				'deductions_total_amt' => $deductions_total_amt,
								
				'uid' => $uid,
				'created_date'		   => date('Y-m-d'),
			);
			$wages_paid_deduction_id = db_insert('fa_ar_wages_paid_deduction')->fields($wages_paid_deduction)->execute();	
		}
		
		
		//Disbursement from fine funds
		
		$disbursement_from_fine_funds = get_disbursement_fine_funds($annual_return_ID);
		if($disbursement_from_fine_funds != NULL && count($disbursement_from_fine_funds) > 0) {
			$disbursement_fine_funds = array(
				'annual_return_id' => $val['annual_return_id'],
				'disbursement_a_purpose' => $val['disbursement_a_purpose'],
				'disbursement_a_amt' => $val['disbursement_a_amt'],
				'disbursement_b_purpose' => $val['disbursement_b_purpose'],
				'disbursement_b_amt' => $val['disbursement_b_amt'],
				'disbursement_c_purpose' => $val['disbursement_c_purpose'],
				'disbursement_c_amt' => $val['disbursement_c_amt'],
				'disbursement_d_purpose' => $val['disbursement_d_purpose'],
				'disbursement_d_amt' => $val['disbursement_d_amt'],
				'disbursement_fines_fund_total_amt' => $disbursement_fines_fund_total_amt,
				
				'uid' => $uid,
				'modification_date'	   => date('Y-m-d H:i:s'),
				
				'balance_fines_fund_beginning_year'        => $val['balance_fines_fund_beginning_year'],
				'balance_fines_fund_end_year'              => $val['balance_fines_fund_end_year'],
			);
			db_update('fa_ar_disbursement_fine_funds')->fields($disbursement_fine_funds)->condition('annual_return_id', $annual_return_ID, '=')->execute();	
		} else {
			$disbursement_fine_funds = array(
				'annual_return_id' => $val['annual_return_id'],
				'disbursement_a_purpose' => $val['disbursement_a_purpose'],
				'disbursement_a_amt' => $val['disbursement_a_amt'],
				'disbursement_b_purpose' => $val['disbursement_b_purpose'],
				'disbursement_b_amt' => $val['disbursement_b_amt'],
				'disbursement_c_purpose' => $val['disbursement_c_purpose'],
				'disbursement_c_amt' => $val['disbursement_c_amt'],
				'disbursement_d_purpose' => $val['disbursement_d_purpose'],
				'disbursement_d_amt' => $val['disbursement_d_amt'],
				'disbursement_fines_fund_total_amt' => $disbursement_fines_fund_total_amt,
				
				'uid' => $uid,
				'created_date'		   => date('Y-m-d'),
				
				'balance_fines_fund_beginning_year'        => $val['balance_fines_fund_beginning_year'],
				'balance_fines_fund_end_year'              => $val['balance_fines_fund_end_year'],
			);
			$disbursement_fine_funds_id = db_insert('fa_ar_disbursement_fine_funds')->fields($disbursement_fine_funds)->execute();
		}
		
		drupal_goto('applicant/factories-act-apply/dangerous_operation/'.encryption_decryption_fun('encrypt', $annual_return_ID).'/'.encryption_decryption_fun('encrypt', $factory_id));
	
	}
 