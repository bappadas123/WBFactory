<?php
	
	function maternity_benefit_app_preview($form, &$form_state, $annual_returnID = '', $factoryID = '') {
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
		
		/*$get_wages_paid_include_deduction = get_total_wages_paid_include_deduction($annual_return_ID);
		$get_disbursement_fine_funds = get_disbursement_fine_funds($annual_return_ID);
		$get_factory_act_all_data = get_factory_act_all_data($annual_return_ID);*/
		$get_maternity_benefit_all_data = get_maternity_benefit_all_data($annual_return_ID);
		
		if($get_all_annual['ar_id'] == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Factory Information first.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/annual-return-common/'.$annual_returnID.'/'.$factory_typeID.'/'.$factoryID) ;	
		}
		
		if($get_maternity_benefit_all_data->ar_id == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/maternity-benefit-apply/medical_officer/'.$annual_returnID.'/'.$factoryID) ;	
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
		
		/*$common_section_edit = l('Annual Return Common Section Edit', 'applicant/annual-return-common-apply/default/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		
		if($get_factory_info->payment_wages_flag == 1 && $get_wages_paid_include_deduction->annual_return_id != NULL && $get_disbursement_fine_funds->annual_return_id != NULL) {
			$payment_wages_edit = l('Payment of Wages Edit', 'applicant/payment-of-wages/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		} else {
			$payment_wages_edit = '';
		}
		
		if($get_factory_info->factories_act_flag == 1 && $get_factory_act_all_data->ar_id != NULL) {
			$factories_act_edit = l('Factories Rules Edit', 'applicant/factories-act-apply/dangerous_operation/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		} else {
			$factories_act_edit = '';
		}*/
		
		if($get_factory_info->maternity_benefit_flag == 1 && $get_maternity_benefit_all_data->ar_id != NULL) {
			$maternity_benefit_edit = l('Maternity Benefit Edit', 'applicant/maternity-benefit-apply/medical_officer/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		} else {
			$maternity_benefit_edit = '';
		}
		
		$form['header'] = array(
  			'#type'		=> 'markup',
			'#markup'	=> mb_app_preview($annual_return_ID, $factory_id)	
		);
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'applicant/ar-application-preview/ar_common_app_preview/'.$annual_returnID.'/'.$factoryID, array(
				'html' => TRUE,
				'attributes' => array('class' => array('btn btn-outline-dark pull-left'))
			))
		);
		
		if(!empty($application_status) && $application_status == 'In') {
			$form['mb_app_link_markup'] = array(
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
	
	function maternity_benefit_app_preview_submit($form, &$form_state) {
		
	}
	
	function mb_app_preview($annual_return_ID = '', $factory_id = '') {
		global $base_root,$base_path,$user;
		
		$get_factory_info = get_annual_return_factory_information($annual_return_ID);
		
		$get_leave_wages_details = get_leave_wages_details($annual_return_ID);
		$get_worker_details_avg_daily = get_worker_details_avg_daily($annual_return_ID);
		
		$get_medical_officer = get_medical_officer($annual_return_ID);
		$get_hospital_details = get_hospital_details($annual_return_ID);
		$get_emplm_dism_pay_bonus_women = get_emplm_dism_pay_bonus_women($annual_return_ID);
		$get_details_payment = get_details_of_payment($annual_return_ID);		
		
		$output = '';
		
		$output .='<div class="row"><div class="box box-info">
				<div class = "box-body"><div class="col-lg-12 col-md-12 col-sm-12">
				<table class="table table-bordered custom-table-view" width="100%"> 
					<tr>
   						<th>Parameters</th>
   						<th colspan="2">Inputs</th>
					</tr>';
					
		//section for Medical Officer Details			
		$output .= '<tr><td colspan="2" class="sub-title"><b>1. MEDICAL OFFICER DETAILS</b></td></tr>
					<tr><td width="65%">(i). Medical Officer, if any, attached to the factory</td><td width="35%">'.$get_factory_info->medical_officer_attached_factory.'</td></tr>
					<tr><td colspan="2"><b>Medical Officer List</b></td></tr>
		';
				if($get_factory_info->medical_officer_attached_factory == 'Yes') {
					
					$output .= '<tr><td colspan="2">
								<table class="table table-bordered custom-table-view" width="100%">
									<tr>
										<th width="5%"><b>Sl. No.</b></th>
										<th width="25%"><b>Medical Officer Name</b></th>
										<th width="20%"><b>Medical Officer Qualification</b></th>
										<th width="15%"><b>Resident Doctor</b></th>
										<th width="35%"><b>Pay visits to the factory of part-time Medical Officer</b></th>
									</tr>';
					$sl_no = 1;
					foreach($get_medical_officer as $medical_officer) {
						if($medical_officer->medical_officer_resident_doctor == 'Yes') {
							$medical_officer_parttime_pay = 'Not Available';	
						} else if($medical_officer->medical_officer_resident_doctor == 'No') {
							$medical_officer_parttime_pay = $medical_officer->medical_officer_parttime_pay;	
						}
						
						$output .= '<tr>
										<td>'.$sl_no.'</td>
										<td>'.$medical_officer->medical_officer_name.'</td>
										<td>'.$medical_officer->medical_officer_qualification.'</td>
										<td>'.$medical_officer->medical_officer_resident_doctor.'</td>
										<td>'.$medical_officer_parttime_pay.'</td>
									</tr>';
						$sl_no++;		
					}
					$output .= '</table>
								</td></tr>
					';
				} else if($get_factory_info->medical_officer_attached_factory == 'No') {
					$output .= '<tr><td colspan="2">
								<table class="table table-bordered custom-table-view" width="100%">
									<tr>
										<th width="5%"><b>Sl. No.</b></th>
										<th width="25%"><b>Medical Officer Name</b></th>
										<th width="20%"><b>Medical Officer Qualification</b></th>
										<th width="15%"><b>Resident Doctor</b></th>
										<th width="35%"><b>Pay visits to the factory of part-time Medical Officer</b></th>
									</tr>
									<tr><td colspan="5" align="center"><b>Not Available</b></td></tr>
								</table>
								</td></tr>';	
					
				}
				
		//section for HOSPITAL DETAILS			
		$output .= '<tr><td colspan="2" class="sub-title"><b>2. HOSPITAL DETAILS</b></td></tr>
					<tr><td width="65%">(i). (a) Is there any hospital attached to the factory?</td><td width="35%">'.$get_factory_info->hospital_attached_factory.'</td></tr>
					<tr><td colspan="2"><b>Hospital Details List</b></td></tr>
		';
				if($get_factory_info->hospital_attached_factory == 'Yes') {
					
					$output .= '<tr><td colspan="2">
								<table class="table table-bordered custom-table-view" width="100%">
									<tr>
										<th width="5%"><b>Sl. No.</b></th>
										<th width="25%"><b>How many beds are provided for women employees</b></th>
										<th width="20%"><b>Lady Doctor</b></th>
										<th width="15%"><b>Qualification of Lady Doctor</b></th>
										<th width="35%"><b>Qualified Midwife</b></th>
									</tr>';
					$sl_no = 1;
					foreach($get_hospital_details as $hospital_details) {
						if($hospital_details->hospital_lady_doctor == 'Yes') {
							$hospital_lady_doc_qualif = $hospital_details->hospital_lady_doc_qualif;	
						} else if($hospital_details->hospital_lady_doctor == 'No') {
							$hospital_lady_doc_qualif = 'Not Available';	
						}
						
						$output .= '<tr>
										<td>'.$sl_no.'</td>
										<td>'.$hospital_details->hospital_bed_for_women_emp.'</td>
										<td>'.$hospital_details->hospital_lady_doctor.'</td>
										<td>'.$hospital_lady_doc_qualif.'</td>
										<td>'.$hospital_details->hospital_qualif_midwife.'</td>
									</tr>';
						$sl_no++;		
					}
					$output .= '</table>
								</td></tr>
					';
				} else if($get_factory_info->hospital_attached_factory == 'No') {
					$output .= '<tr><td colspan="2">
								<table class="table table-bordered custom-table-view" width="100%">
									<tr>
										<th width="5%"><b>Sl. No.</b></th>
										<th width="25%"><b>How many beds are provided for women employees</b></th>
										<th width="20%"><b>Lady Doctor</b></th>
										<th width="15%"><b>Qualification of Lady Doctor</b></th>
										<th width="35%"><b>Qualified Midwife</b></th>
									</tr>
									<tr><td colspan="5" align="center"><b>Not Available</b></td></tr>
								</table>
								</td></tr>';	
					
				}
				
		//section for EMPLOYMENT, DISMISSAL, PAYMENT OF BONUS, ETC. OF WOMEN
		$agg_no_women_per_temp_emp_year = $get_leave_wages_details->tot_no_workers_year_per_women + $get_leave_wages_details->tot_no_workers_year_con_women;
		$avg_daily_no_women_emp = $get_worker_details_avg_daily->avg_daily_per_worker_adult_women + $get_worker_details_avg_daily->avg_daily_con_worker_adult_women;
		
		$output .= '<tr><td colspan="2" class="sub-title"><b>3. EMPLOYMENT, DISMISSAL, PAYMENT OF BONUS, ETC. OF WOMEN</b></td></tr>
					<tr><td width="65%">(i). Aggregate number of women permanently or temporarily employed during the year</td><td width="35%">'.$agg_no_women_per_temp_emp_year.'</td></tr>
					<tr><td>(ii). Aggregate number of women permanently or temporarily employed during the year</td><td>'.$avg_daily_no_women_emp.'</td></tr>
					<tr><td>(iii). Number of women who worked for a period of not less than one hundred and sixty days in the twelve months immediately preceding the date of delivery</td><td>'.$get_emplm_dism_pay_bonus_women->no_women_worked_for_perd.'</td></tr>
					<tr><td>(iv). Number of women who gave notice under Section 6</td><td>'.$get_emplm_dism_pay_bonus_women->no_women_gave_notice.'</td></tr>
					<tr><td colspan="2">
						<table class="table table-bordered custom-table-view" width="100%">
							<tr>
								<th width="55%" colspan="2"></th>
								<th width="30%"><b>Undisposed from previous years and disposed during the year</b></th>
								<th width="15%"><b>Current year</b></th>
							</tr>
							<tr>
								<td colspan="2"><b>(v) Number of women who were granted permission to absent on receipt of notice of confinement</b></td>
								<td>'.$get_emplm_dism_pay_bonus_women->grant_permi_abse_undisp_prev_year.'</td>
								<td>'.$get_emplm_dism_pay_bonus_women->grant_permi_abse_curr_year.'</td>
							</tr>
							
							<tr>
								<td rowspan="2"><b>(vi) No of claims for maternity benefit</b></td>
								<td><b>Paid</b></td>
								<td>'.$get_emplm_dism_pay_bonus_women->no_claims_mater_paid_undisp_prev_year.'</td>
								<td>'.$get_emplm_dism_pay_bonus_women->no_claims_mater_paid_curr_year.'</td>
							</tr>
							<tr>
								<td><b>Reject</b></td>
								<td>'.$get_emplm_dism_pay_bonus_women->no_claims_mater_reject_undisp_prev_year.'</td>
								<td>'.$get_emplm_dism_pay_bonus_women->no_claims_mater_reject_curr_year.'</td>
							</tr>
							
							<tr>
								<td rowspan="2"><b>(vii) No of claims for medical bonus (under Section 8)</b></td>
								<td><b>Paid</b></td>
								<td>'.$get_emplm_dism_pay_bonus_women->no_claims_medi_paid_undisp_prev_year.'</td>
								<td>'.$get_emplm_dism_pay_bonus_women->no_claims_medi_paid_curr_year.'</td>
							</tr>
							<tr>
								<td><b>Reject</b></td>
								<td>'.$get_emplm_dism_pay_bonus_women->no_claims_medi_reject_undisp_prev_year.'</td>
								<td>'.$get_emplm_dism_pay_bonus_women->no_claims_medi_reject_curr_year.'</td>
							</tr>
							
							<tr>
								<td rowspan="2"><b>(viii) No of cases in which leave for miscarriage was applied for and was</b></td>
								<td><b>Paid</b></td>
								<td>'.$get_emplm_dism_pay_bonus_women->no_case_miscarr_grant_undisp_prev_year.'</td>
								<td>'.$get_emplm_dism_pay_bonus_women->no_case_miscarr_grant_curr_year.'</td>
							</tr>
							<tr>
								<td><b>Reject</b></td>
								<td>'.$get_emplm_dism_pay_bonus_women->no_case_miscarr_reject_undisp_prev_year.'</td>
								<td>'.$get_emplm_dism_pay_bonus_women->no_case_miscarr_reject_curr_year.'</td>
							</tr>
							
							<tr>
								<td rowspan="2"><b>(ix) No of cases in which additional leave for illness under sec. 10 was applied for and was</b></td>
								<td><b>Paid</b></td>
								<td>'.$get_emplm_dism_pay_bonus_women->no_case_illness_grant_undisp_prev_year.'</td>
								<td>'.$get_emplm_dism_pay_bonus_women->no_case_illness_grant_curr_year.'</td>
							</tr>
							<tr>
								<td><b>Reject</b></td>
								<td>'.$get_emplm_dism_pay_bonus_women->no_case_illness_reject_undisp_prev_year.'</td>
								<td>'.$get_emplm_dism_pay_bonus_women->no_case_illness_reject_curr_year.'</td>
							</tr>
						</table>
					</td></tr>
					<tr><td>(x). No. of cases where pre-natal confinement and post-natal care was provided by the management free of charge (Section 8)</td><td>'.$get_emplm_dism_pay_bonus_women->no_case_natal_confine_care.'</td></tr>
					<tr><td colspan="2"><b>(xi). No. of women who died</b></td></tr>
					<tr><td>(a) before delivery</td><td>'.$get_emplm_dism_pay_bonus_women->no_women_died_before_dlvry.'</td></tr>
					<tr><td>(b) after delivery</td><td>'.$get_emplm_dism_pay_bonus_women->no_women_died_after_dlvry.'</td></tr>
					<tr><td colspan="2"><b>(xii). No. of infants who died</b></td></tr>
					<tr><td>(a) on the day of their birth</td><td>'.$get_emplm_dism_pay_bonus_women->no_infants_died_on_dob.'</td></tr>
					<tr><td>(b) during the six weeks following the date of birth</td><td>'.$get_emplm_dism_pay_bonus_women->no_infants_died_during_six_weeks.'</td></tr>
					<tr><td>(xiii) No. of women discharge or dismissed while working</td><td>'.$get_emplm_dism_pay_bonus_women->no_women_discharge_work.'</td></tr>
					<tr><td>(xiv) No. of women deprived of maternity benefit and/or medical bonus under provission to sub-Section (2) of Section 12</td><td>'.$get_emplm_dism_pay_bonus_women->no_women_deprived_mater.'</td></tr>
					<tr><td>(xv). (a) No. of cases where claims were contested in a court of law</td><td>'.$get_emplm_dism_pay_bonus_women->no_case_claims_contested.'</td></tr>
					<tr><td>(b) Result of such cases</td><td>'.$get_emplm_dism_pay_bonus_women->result_case_claims_contested.'</td></tr>
					
		';
		
		//section for DETAILS OF PAYMENT
		$output .= '<tr><td colspan="2" class="sub-title"><b>4. DETAILS OF PAYMENT</b></td></tr>
					<tr><td width="65%">(i). Total amount of Maternity Benefit, Maternity Bonus and Wages for additional leave paid during the year</td><td width="35%">'.$get_details_payment->tot_amt_addl_leave_paid_year.'</td></tr>
					<tr><td>Rs.</td><td>'.$get_details_payment->tot_amt_addl_leave_paid_rs.'</td></tr>
					<tr><td colspan="2"><b>(ii). Details of Payment</b></td></tr>
					<tr><td colspan="2">
						<table class="table table-bordered custom-table-view" width="100%">
							<tr>
								<th width="20%"></th>
								<th width="5%"><b>No. of cases</b></th>
								<th width="15%"><b>Amount of Maternity Benefits for the period preceding the date of expected delivery</b></th>
								<th width="15%"><b>Amount of Maternity Benefits for the subsequent period</b></th>
								<th width="15%"><b>Payment of medical bonus under Section 8</b></th>
								<th width="15%"><b>Payment of leave with wages under Section 9</b></th>
								<th width="15%"><b>Payment of leave for illness under Section 10</b></th>
							</tr>
							<tr>
								<td><b>Women employed</b></td>
								<td>'.$get_details_payment->women_employed_no_cases.'</td>
								<td>'.$get_details_payment->women_employed_amt_exptd_delivery.'</td>
								<td>'.$get_details_payment->women_employed_amt_subseq_perd.'</td>
								<td>'.$get_details_payment->women_employed_pymt_med_bonus.'</td>
								<td>'.$get_details_payment->women_employed_pymt_leave_wages.'</td>
								<td>'.$get_details_payment->women_employed_pymt_leave_illness.'</td>	
							</tr>
							
							<tr>
								<td><b>Nominee of the women</b></td>
								<td>'.$get_details_payment->nominee_women_no_cases.'</td>
								<td>'.$get_details_payment->nominee_women_amt_exptd_delivery.'</td>
								<td>'.$get_details_payment->nominee_women_amt_subseq_perd.'</td>
								<td>'.$get_details_payment->nominee_women_pymt_med_bonus.'</td>
								<td>'.$get_details_payment->nominee_women_pymt_leave_wages.'</td>
								<td>'.$get_details_payment->nominee_women_pymt_leave_illness.'</td>	
							</tr>
							
							<tr>
								<td><b>Legal representative of the women</b></td>
								<td>'.$get_details_payment->legal_repr_women_no_cases.'</td>
								<td>'.$get_details_payment->legal_repr_women_amt_exptd_delivery.'</td>
								<td>'.$get_details_payment->legal_repr_women_amt_subseq_perd.'</td>
								<td>'.$get_details_payment->legal_repr_women_pymt_med_bonus.'</td>
								<td>'.$get_details_payment->legal_repr_women_pymt_leave_wages.'</td>
								<td>'.$get_details_payment->legal_repr_women_pymt_leave_illness.'</td>	
							</tr>	
						</table>		
					</td></tr>
					<tr><td>(iii). No. of cases in which payment was made on the order of competent Authority or Inspector</td><td>'.$get_details_payment->no_cases_pymt_order_insp.'</td></tr>
					<tr><td>(iv). Number of women workers who absconded after receiving the first installment of maternity benefits</td><td>'.$get_details_payment->no_women_worker_recv_first_instal.'</td></tr>
					<tr><td>(v). Remarks</td><td>'.$get_details_payment->details_payment_remarks.'</td></tr>		
		';
					
		$output .='</table>
				</div></div></div></div>'; 
		
		
		return $output;
		
	}