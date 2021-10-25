<?php
	
	function payment_wages_app_preview($form, &$form_state, $annual_returnID = '', $factoryID = '') {
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
		
		
		$application_status = $get_factory_info->full_application_status;
		
		$get_all_annual =  ar_common_application_data($annual_return_ID);
		
		$get_wages_paid_include_deduction = get_total_wages_paid_include_deduction($annual_return_ID);
		$get_disbursement_fine_funds = get_disbursement_fine_funds($annual_return_ID);
		/*$get_factory_act_all_data = get_factory_act_all_data($annual_return_ID);
		$get_maternity_benefit_all_data = get_maternity_benefit_all_data($annual_return_ID);*/
		
		if($get_all_annual['ar_id'] == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Factory Information first.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/annual-return-common/'.$annual_returnID.'/'.$factory_typeID.'/'.$factoryID) ;	
		}
		
		if($get_wages_paid_include_deduction->annual_return_id == NULL || $get_disbursement_fine_funds->annual_return_id == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/payment-of-wages/'.$annual_returnID.'/'.$factoryID) ;	
		}
		
		
		$form = array();
		
		$form['annual_return_id'] = array(
				'#type' 			=> 'hidden',
				'#default_value' 	=> $annual_return_ID,
		);
		
		$form['factory_id'] = array(
				'#type' 			=> 'hidden',
				'#default_value' 	=> $factory_id,
		);
		
		/*$common_section_edit = l('Annual Return Common Section Edit', 'applicant/annual-return-common-apply/default/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));*/
		
		if($get_factory_info->payment_wages_flag == 1 && $get_wages_paid_include_deduction->annual_return_id != NULL && $get_disbursement_fine_funds->annual_return_id != NULL) {
			$payment_wages_edit = l('Payment of Wages Edit', 'applicant/payment-of-wages/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		} else {
			$payment_wages_edit = '';
		}
		
		/*if($get_factory_info->factories_act_flag == 1 && $get_factory_act_all_data->ar_id != NULL) {
			$factories_act_edit = l('Factories Rules Edit', 'applicant/factories-act-apply/dangerous_operation/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		} else {
			$factories_act_edit = '';
		}
		
		if($get_factory_info->maternity_benefit_flag == 1 && $get_maternity_benefit_all_data->ar_id != NULL) {
			$maternity_benefit_edit = l('Maternity Benefit Edit', 'applicant/maternity-benefit-apply/medical_officer/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		} else {
			$maternity_benefit_edit = '';
		}*/
		
		$form['header'] = array(
  			'#type'		=> 'markup',
			'#markup'	=> pw_app_preview($annual_return_ID, $factory_id)	
		);
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'applicant/ar-application-preview/ar_common_app_preview/'.$annual_returnID.'/'.$factoryID, array(
				'html' => TRUE,
				'attributes' => array('class' => array('btn btn-outline-dark pull-left'))
			))
		);
		
		if(!empty($application_status) && $application_status == 'In') {
			$form['pw_app_link_markup'] = array(
					'#type'		=> 'markup',
					'#prefix'	=> '<div class="row">
										<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
										'.$common_section_edit.$payment_wages_edit.$factories_act_edit.$maternity_benefit_edit.'',
					'#suffix' => '		</div>
									</div>',
			);
		}
		
		return $form;
	}
	
	function payment_wages_app_preview_submit($form, &$form_state) {
		
	}
	
	function pw_app_preview($annual_return_ID = '', $factory_id = '') {
		global $base_root,$base_path,$user;
		
		$get_wages_paid_include_deduction = get_total_wages_paid_include_deduction($annual_return_ID);
		$get_disbursement_fine_funds = get_disbursement_fine_funds($annual_return_ID);
		
		$output = '';
		
		$output .='<div class="row"><div class="box box-info">
				<div class = "box-body"><div class="col-lg-12 col-md-12 col-sm-12">
				<table class="table table-bordered custom-table-view" width="100%"> 
					<tr>
   						<th>Parameters</th>
   						<th colspan="2">Inputs</th>
					</tr>';
		
		$output .= '<tr><td colspan="3" class="sub-title"><b>1. TOTAL WAGES PAID INFORMATION</b></td></tr>
					<tr><td width="65%"><b>(i). Total wages paid include deduction under Section 7(2) on the following accounts</b></td><td width="35%" colspan="2"><b>Rs.</b></td></tr>
					<tr><td>(a) Profit sharing bonus</td><td colspan="2">'.$get_wages_paid_include_deduction->total_wages_profit_bonus.'</td></tr>
					<tr><td>(b) Money value of concessions</td><td colspan="2">'.$get_wages_paid_include_deduction->total_wages_money_value.'</td></tr>
					<tr><td>(c) Basic wages including overtime and non-profit sharing bonus</td><td colspan="2">'.$get_wages_paid_include_deduction->total_wages_basic_wages.'</td></tr>
					<tr><td>(d) Dearness and other allowances(not in kind)</td><td colspan="2">'.$get_wages_paid_include_deduction->total_wages_da.'</td></tr>
					<tr><td>(e) Arrears of pay in respect of the previous years paid during the year</td><td colspan="2">'.$get_wages_paid_include_deduction->total_wages_arrears_pay.'</td></tr>
					<tr><td align="center"><b>Total</b></td><td colspan="2">'.$get_wages_paid_include_deduction->total_wages_total_amt.'</td></tr>
					
					<tr><td colspan="3" class="sub-title"><b>2. DEDUCTIONS INFORMATION</b></td></tr>
					<tr><td><b>(i). Deductions-Number of cases and amount realised</b></td><td width="15%"><b>Number of cases</b></td><td width="20%"><b>Amount realised(Rs.)</b></td></tr>
					<tr><td>(a) Fines</td><td>'.$get_wages_paid_include_deduction->deductions_fines_no_cases.'</td><td>'.$get_wages_paid_include_deduction->deductions_fines_amt_realised.'</td></tr>
					<tr><td>(b) Deductions for damage or loss</td><td>'.$get_wages_paid_include_deduction->deductions_damg_loss_no_cases.'</td><td>'.$get_wages_paid_include_deduction->deductions_damg_loss_amt_realised.'</td></tr>
					<tr><td>(c) Deduction for breach of contract</td><td>'.$get_wages_paid_include_deduction->deductions_breach_contct_no_cases.'</td><td>'.$get_wages_paid_include_deduction->deductions_breach_contct_amt_realised.'</td></tr>
					<tr><td align="center" colspan="2"><b>Total</b></td><td>'.$get_wages_paid_include_deduction->deductions_total_amt.'</td></tr>

					<tr><td colspan="3" class="sub-title"><b>3. FINES FUND INFORMATION</b></td></tr>
					<tr><td>(i) Balance of fines fund in hand at the beginning of the year Rs.</td><td colspan="2">'.$get_disbursement_fine_funds->balance_fines_fund_beginning_year.'</td></tr>
					<tr><td colspan="3"><b>(ii) Disbursement from fine funds</b></td></tr>
					<tr><td><b>Purpose</b></td><td colspan="2"><b>Amount</b></td></tr>
					<tr><td>(a) '.$get_disbursement_fine_funds->disbursement_a_purpose.'</td><td colspan="2">'.$get_disbursement_fine_funds->disbursement_a_amt.'</td></tr>
					<tr><td>(b) '.$get_disbursement_fine_funds->disbursement_b_purpose.'</td><td colspan="2">'.$get_disbursement_fine_funds->disbursement_b_amt.'</td></tr>
					<tr><td>(c) '.$get_disbursement_fine_funds->disbursement_c_purpose.'</td><td colspan="2">'.$get_disbursement_fine_funds->disbursement_c_amt.'</td></tr>
					<tr><td>(d) '.$get_disbursement_fine_funds->disbursement_d_purpose.'</td><td colspan="2">'.$get_disbursement_fine_funds->disbursement_d_amt.'</td></tr>
					<tr><td align="center"><b>Total</b></td><td colspan="2">'.$get_disbursement_fine_funds->disbursement_fines_fund_total_amt.'</td></tr>
					<tr><td>(iii) Balance of fines fund in hand at the end of the year Rs.</td><td colspan="2">'.$get_disbursement_fine_funds->balance_fines_fund_end_year.'</td></tr>
		';						
								
		$output .='</table>
				</div></div></div></div>'; 
		
		
		return $output;
		
	}