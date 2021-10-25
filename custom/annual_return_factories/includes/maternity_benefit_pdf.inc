<?php

	function maternity_benefit_pdf($form, &$form_state, $annual_returnID = '', $factoryID = '') {
		
		global $user, $base_path;
		$uid 						= $user->uid;
		
		require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';
		
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
		
		$get_district_details = fetch_district_details($get_factory_info->district);
		$get_postoffice_details = fetch_postoffice_details($get_factory_info->postoffice);
		
		$getdata_address =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
		$factory_address =	get_full_address('fa_annual_return','sub-table',$get_factory_info->id,$getdata_address);
		
		$getdata_manager_address =  array('district_manager','sub_division_manager','area_type_manager','block_mun_cor_sez_not_manager','grm_ward_sector_not_manager','police_station_manager','pincode_manager','state_manager','post_office_manager');
		$address_of_manager = get_full_address('fa_annual_return','sub-table',$get_factory_info->id,$getdata_manager_address);
		
		$getdata_occupier_permanent_address =  array('district_oprmntadr','subdivision_oprmntadr','areatype_oprmntadr','block_oprmntadr','panchayat_oprmntadr','policestation_oprmntadr','pincodeoprmntadr','state_oprmntadr','postoffice_oprmntadr');
		$address_of_occupier = get_full_address('fa_annual_return','sub-table',$get_factory_info->id,$getdata_occupier_permanent_address);
		
		$get_all_annual =  ar_common_application_data($annual_return_ID);
		
		$get_worker_details_mandays = get_worker_details_mandays($annual_return_ID);
		$get_worker_details_avg_daily = get_worker_details_avg_daily($annual_return_ID);
		
		$get_leave_wages_details = get_leave_wages_details($annual_return_ID);
		
		$get_maternity_benefit_all_data = get_maternity_benefit_all_data($annual_return_ID);
		
		$get_medical_officer = get_medical_officer($annual_return_ID);
		$get_hospital_details = get_hospital_details($annual_return_ID);
		$get_emplm_dism_pay_bonus_women = get_emplm_dism_pay_bonus_women($annual_return_ID);
		$get_details_payment = get_details_of_payment($annual_return_ID);
		
		$agg_no_women_per_temp_emp_year = $get_leave_wages_details->tot_no_workers_year_per_women + $get_leave_wages_details->tot_no_workers_year_con_women;
		$avg_daily_no_women_emp = $get_worker_details_avg_daily->avg_daily_per_worker_adult_women + $get_worker_details_avg_daily->avg_daily_con_worker_adult_women;
		
		if($get_all_annual['ar_id'] == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Factory Information first.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/annual-return-common/'.$annual_returnID.'/'.$factory_typeID.'/'.$factoryID) ;	
		}
		
		if($get_maternity_benefit_all_data->ar_id == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/maternity-benefit-apply/medical_officer/'.$annual_returnID.'/'.$factoryID) ;	
		}
		
		
		if(!empty($application_status) && $application_status == 'F') {
			if($get_factory_info->maternity_benefit_flag == 1 && $get_maternity_benefit_all_data->ar_id != NULL) {
				/*margin-top:10px;*/
				$page_output = '';
				$page_output .='<style type="text/css">
							table, td, th {
									font-size:14px;
									font-family:Times New Roman, serif;
									height:30px;
									color:#000;
									background:#fff;
							}
							th {
								background-color: #a6a6a6;
								color: white;
							}
							h1 {
								font-size:24px;
								font-weight:bold;
							}
							h2,h3,h4 {
								font-size:16px;
								font-weight:bold;
							}
							h5,h6 {
								font-size:12px;
								font-weight:bold;
							}
							.data{ text-transform: uppercase;font-weight:bold;}
							
					</style>';
					
					$page_output .='
					<div style="font-size: 16px" align="center">Annual Return - The Maternity Benefit Act, 1961</div>
					<div style="font-size: 16px" align="center">(Rule 16 of the West Bengal Maternity Benefit Rules, 1965)</div>
					<div style="font-size: 16px" align="right">Year ending 31<sup>st</sup> December, '.$get_factory_info->annual_return_year.'</div>
					<br>
					<div style="font-size: 14px">From ....................../ L
					<br>
					Particular relating to Factory
					</div>
					<table width="100%" cellspacing="0" cellpadding="5"> 
					
						<tr>
							<td style="font-size: 14px" width="60%">1. (a) Name of the Factory</td>
							<td style="font-size: 14px" width="40%">'.$get_factory_info->factory_name.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
							and
							</td>
						</tr>
						<tr>
							<td style="font-size: 14px" width="60%">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Registration Number of Factory</td>
							<td style="font-size: 14px" width="40%">'.$get_factory_info->registration_number.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">2. Address</td>
							<td style="font-size: 14px">'.$factory_address.', '.$get_factory_info->addrline.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Post Office</td>
							<td style="font-size: 14px">'.$get_postoffice_details->po_name.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;District</td>
							<td style="font-size: 14px">'.$get_district_details->district_name.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">3. (a) Date of closing, if closed</td>
							<td style="font-size: 14px">'.implode('/', array_reverse(explode('-', $get_factory_info->closing_date))).'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;(b) Date of opening</td>
							<td style="font-size: 14px">'.implode('/', array_reverse(explode('-', $get_factory_info->date_of_amenability))).'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">4. Name of Manager</td>
							<td style="font-size: 14px">'.$get_factory_info->name_manager.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;Postal addresses of Manager</td>
							<td style="font-size: 14px">'.$address_of_manager.', '.$get_factory_info->adress_line1_manager.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">5. Name of Occupier</td>
							<td style="font-size: 14px">'.$get_factory_info->name_occupier.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;Postal addresses of Occupier</td>
							<td style="font-size: 14px">'.$address_of_occupier.', '.$get_factory_info->addrline_oprmntadr.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">6. Medical Officer, if any, attached to the factory:</td>
							<td style="font-size: 14px">'.$get_factory_info->medical_officer_attached_factory.'</td>
						</tr>
						<tr><td style="font-size: 14px" colspan="2"><b>Medical Officer List:</b></td></tr>
						<tr>
							<td style="font-size: 14px" colspan="2">
								';
								if($get_factory_info->medical_officer_attached_factory == 'Yes') {
					$page_output .= '
								<table cellspacing="0" cellpadding="8" width="100%" border="1">
									<tr>
										<th style="font-size: 14px" width="5%"><b>Sl. No.</b></th>
										<th style="font-size: 14px" width="25%"><b>(a) Name</b></th>
										<th style="font-size: 14px" width="20%"><b>(b) Qualification</b></th>
										<th style="font-size: 14px" width="15%"><b>(c) Is he a resident doctor?</b></th>
										<th style="font-size: 14px" width="35%"><b>(d) If a part-time employee, how often does he pay visits to the factory</b></th>
									</tr>
									';
									$sl_no = 1;
									foreach($get_medical_officer as $medical_officer) {
										if($medical_officer->medical_officer_resident_doctor == 'Yes') {
											$medical_officer_parttime_pay = 'Not Available';	
										} else if($medical_officer->medical_officer_resident_doctor == 'No') {
											$medical_officer_parttime_pay = $medical_officer->medical_officer_parttime_pay;	
										}
					$page_output .= '
									<tr>
										<td>'.$sl_no.'</td>
										<td>'.$medical_officer->medical_officer_name.'</td>
										<td>'.$medical_officer->medical_officer_qualification.'</td>
										<td>'.$medical_officer->medical_officer_resident_doctor.'</td>
										<td>'.$medical_officer_parttime_pay.'</td>
									</tr>';
										$sl_no++;		
									}
					$page_output .= '		
								</table>
								';
								} else if($get_factory_info->medical_officer_resident_doctor == 'No') {
					$page_output .= '
								<table cellspacing="0" cellpadding="8" width="100%" border="1">
									<tr>
										<th style="font-size: 14px" width="5%"><b>Sl. No.</b></th>
										<th style="font-size: 14px" width="25%"><b>(a) Name</b></th>
										<th style="font-size: 14px" width="20%"><b>(b) Qualification</b></th>
										<th style="font-size: 14px" width="15%"><b>(c) Is he a resident doctor?</b></th>
										<th style="font-size: 14px" width="35%"><b>(d) If a part-time employee, how often does he pay visits to the factory</b></th>
									</tr>
									<tr>
										<td colspan="2" align="center"><b>Not Available</b></td>
									</tr>
								</table>
								';
								}
					$page_output.= '
							</td>
						</tr>
						<tr>
							<td style="font-size: 14px">7. (a) Is there any hospital attached to the factory?</td>
							<td style="font-size: 14px">'.$get_factory_info->hospital_attached_factory.'</td>
						</tr>
						<tr><td style="font-size: 14px" colspan="2"><b>Hospital List:</b></td></tr>
						<tr>
							<td style="font-size: 14px" colspan="2">
								';
								if($get_factory_info->hospital_attached_factory == 'Yes') {
					$page_output .= '
								<table cellspacing="0" cellpadding="9" width="100%" border="1">
									<tr>
										<th style="font-size: 14px" width="5%"><b>Sl. No.</b></th>
										<th style="font-size: 14px" width="25%"><b>(b) If so, how many beds are provided for women employees?</b></th>
										<th style="font-size: 14px" width="20%"><b>(c) Is there a lady doctor?</b></th>
										<th style="font-size: 14px" width="15%"><b>(d) If so, what are her qualifications?</b></th>
										<th style="font-size: 14px" width="35%"><b>(e) Is there a qualified midwife?</b></th>
									</tr>
									';
									$sl_no = 1;
									foreach($get_hospital_details as $hospital_details) {
										if($hospital_details->hospital_lady_doctor == 'Yes') {
											$hospital_lady_doc_qualif = $hospital_details->hospital_lady_doc_qualif;	
										} else if($hospital_details->hospital_lady_doctor == 'No') {
											$hospital_lady_doc_qualif = 'Not Available';	
										}
					$page_output .= '
									<tr>
										<td>'.$sl_no.'</td>
										<td>'.$hospital_details->hospital_bed_for_women_emp.'</td>
										<td>'.$hospital_details->hospital_lady_doctor.'</td>
										<td>'.$hospital_lady_doc_qualif.'</td>
										<td>'.$hospital_details->hospital_qualif_midwife.'</td>
									</tr>';
										$sl_no++;		
									}
					$page_output .= '		
								</table>
								';
								} else if($get_factory_info->hospital_attached_factory == 'No') {
					$page_output .= '
								<table cellspacing="0" cellpadding="9" width="100%" border="1">
									<tr>
										<th style="font-size: 14px" width="5%"><b>Sl. No.</b></th>
										<th style="font-size: 14px" width="25%"><b>(b) If so, how many beds are provided for women employees?</b></th>
										<th style="font-size: 14px" width="20%"><b>(c) Is there a lady doctor?</b></th>
										<th style="font-size: 14px" width="15%"><b>(d) If so, what are her qualifications?</b></th>
										<th style="font-size: 14px" width="35%"><b>(e) Is there a qualified midwife?</b></th>
									</tr>
									<tr>
										<td colspan="2" align="center"><b>Not Available</b></td>
									</tr>
								</table>
								';
								}
					$page_output.= '
							</td>
						</tr>
					</table>
					<table width="100%" cellspacing="0" cellpadding="5">
						<tr><td style="font-size: 14px" colspan="2"><b>Employment, Dismissal, Payment of Bonus, etc. of Women</b></td></tr>
						<tr><td style="font-size: 14px" colspan="2">From ....................../ M</td></tr>
						<tr>
							<td style="font-size: 14px" width="85%">1. Aggregate number of women permanently or temporarily employed during the year</td>
							<td style="font-size: 14px" width="15%">'.$agg_no_women_per_temp_emp_year.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">2. Aggregate number of women permanently or temporarily employed during the year</td>
							<td style="font-size: 14px">'.$avg_daily_no_women_emp.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">3. Number of women who worked for a period of not less than one hundred and sixty &nbsp;&nbsp;&nbsp;&nbsp;days in the twelve months immediately preceding the date of delivery</td>
							<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_women_worked_for_perd.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">4. Number of women who gave notice under Section 6</td>
							<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_women_gave_notice.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">
								<table cellspacing="0" cellpadding="10" width="100%" border="1">
									<tr>
										<th style="font-size: 14px" width="55%" colspan="2"></th>
										<th style="font-size: 14px" width="30%"><b>Undisposed from previous years and disposed during the year</b></th>
										<th style="font-size: 14px" width="15%"><b>Current year</b></th>
									</tr>
									<tr>
										<td style="font-size: 14px" colspan="2"><b>5. Number of women who were granted permission to absent on receipt of notice of confinement</b></td>
										<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->grant_permi_abse_undisp_prev_year.'</td>
										<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->grant_permi_abse_curr_year.'</td>
									</tr>
									
									<tr>
										<td style="font-size: 14px" rowspan="2"><b>6. No of claims for maternity benefit</b></td>
										<td style="font-size: 14px"><b>Paid</b></td>
										<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_claims_mater_paid_undisp_prev_year.'</td>
										<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_claims_mater_paid_curr_year.'</td>
									</tr>
									<tr>
										<td style="font-size: 14px"><b>Reject</b></td>
										<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_claims_mater_reject_undisp_prev_year.'</td>
										<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_claims_mater_reject_curr_year.'</td>
									</tr>
									
									<tr>
										<td style="font-size: 14px" rowspan="2"><b>7. No of claims for medical bonus (under Section 8)</b></td>
										<td style="font-size: 14px"><b>Paid</b></td>
										<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_claims_medi_paid_undisp_prev_year.'</td>
										<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_claims_medi_paid_curr_year.'</td>
									</tr>
									<tr>
										<td style="font-size: 14px"><b>Reject</b></td>
										<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_claims_medi_reject_undisp_prev_year.'</td>
										<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_claims_medi_reject_curr_year.'</td>
									</tr>
									
									<tr>
										<td style="font-size: 14px" rowspan="2"><b>8. No of cases in which leave for miscarriage was applied for and was</b></td>
										<td style="font-size: 14px"><b>Paid</b></td>
										<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_case_miscarr_grant_undisp_prev_year.'</td>
										<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_case_miscarr_grant_curr_year.'</td>
									</tr>
									<tr>
										<td style="font-size: 14px"><b>Reject</b></td>
										<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_case_miscarr_reject_undisp_prev_year.'</td>
										<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_case_miscarr_reject_curr_year.'</td>
									</tr>
									
									<tr>
										<td style="font-size: 14px" rowspan="2"><b>9. No of cases in which additional leave for illness under sec. 10 was applied for and was</b></td>
										<td style="font-size: 14px"><b>Paid</b></td>
										<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_case_illness_grant_undisp_prev_year.'</td>
										<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_case_illness_grant_curr_year.'</td>
									</tr>
									<tr>
										<td style="font-size: 14px"><b>Reject</b></td>
										<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_case_illness_reject_undisp_prev_year.'</td>
										<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_case_illness_reject_curr_year.'</td>
									</tr>
								</table>
							</td>
						</tr>
						<tr>
							<td style="font-size: 14px">10. No. of cases where pre-natal confinement and post-natal care was provided by the &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;management free of charge (Section 8)</td>
							<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_case_natal_confine_care.'</td>
						</tr>
						<tr><td style="font-size: 14px" colspan="2">11. No. of women who died:</td></tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(a) before delivery</td>
							<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_women_died_before_dlvry.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(b) after delivery</td>
							<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_women_died_after_dlvry.'</td>
						</tr>
						<tr><td style="font-size: 14px" colspan="2">12. No. of infants who died</td></tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(a) on the day of their birth</td>
							<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_infants_died_on_dob.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(b) during the six weeks following the date of birth</td>
							<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_infants_died_during_six_weeks.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">13. No. of women discharge or dismissed while working</td>
							<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_women_discharge_work.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">14. No. of women deprived of maternity benefit and/or medical bonus under provission to sub-Section (2) of Section 12</td>
							<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_women_deprived_mater.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">15. (a) No. of cases where claims were contested in a court of law</td>
							<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->no_case_claims_contested.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(b) Result of such cases</td>
							<td style="font-size: 14px">'.$get_emplm_dism_pay_bonus_women->result_case_claims_contested.'</td>
						</tr>
						<tr><td style="font-size: 14px" colspan="2"><b>Details of Payments</b></td></tr>
						<tr><td style="font-size: 14px" colspan="2">From ....................../ N</td></tr>
						<tr>
							<td style="font-size: 14px">1. Total amount of Maternity Benefit, Maternity Bonus and Wages for additional leave &nbsp;&nbsp;&nbsp;&nbsp;paid during the year</td>
							<td style="font-size: 14px">'.$get_details_payment->tot_amt_addl_leave_paid_year.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">Rs.</td>
							<td style="font-size: 14px">'.$get_details_payment->tot_amt_addl_leave_paid_rs.'</td>
						</tr>
						<tr><td style="font-size: 14px" colspan="2"><b>2. Details of Payments :-</b></td></tr>
						<tr>
							<td style="font-size: 14px" colspan="2">
								<table cellspacing="0" cellpadding="8" width="100%" border="1">
									<tr>
										<th style="font-size: 14px" width="20%"></th>
										<th style="font-size: 14px" width="5%"><b>No. of cases</b></th>
										<th style="font-size: 14px" width="15%"><b>Amount of Maternity Benefits for the period preceding the date of expected delivery</b></th>
										<th style="font-size: 14px" width="15%"><b>Amount of Maternity Benefits for the subsequent period</b></th>
										<th style="font-size: 14px" width="15%"><b>Payment of medical bonus under Section 8</b></th>
										<th style="font-size: 14px" width="15%"><b>Payment of leave with wages under Section 9</b></th>
										<th style="font-size: 14px" width="15%"><b>Payment of leave for illness under Section 10</b></th>
									</tr>
									<tr>
										<th style="font-size: 14px" width="20%"></th>
										<th style="font-size: 14px" width="5%"></th>
										<th style="font-size: 14px" width="15%"><b>Rs.</b></th>
										<th style="font-size: 14px" width="15%"><b>Rs.</b></th>
										<th style="font-size: 14px" width="15%"><b>Rs.</b></th>
										<th style="font-size: 14px" width="15%"><b>Rs.</b></th>
										<th style="font-size: 14px" width="15%"><b>Rs.</b></th>
									</tr>
									<tr>
										<td style="font-size: 14px"><b>Women employed</b></td>
										<td style="font-size: 14px">'.$get_details_payment->women_employed_no_cases.'</td>
										<td style="font-size: 14px">'.$get_details_payment->women_employed_amt_exptd_delivery.'</td>
										<td style="font-size: 14px">'.$get_details_payment->women_employed_amt_subseq_perd.'</td>
										<td style="font-size: 14px">'.$get_details_payment->women_employed_pymt_med_bonus.'</td>
										<td style="font-size: 14px">'.$get_details_payment->women_employed_pymt_leave_wages.'</td>
										<td style="font-size: 14px">'.$get_details_payment->women_employed_pymt_leave_illness.'</td>	
									</tr>
									
									<tr>
										<td style="font-size: 14px"><b>Nominee of the women</b></td>
										<td style="font-size: 14px">'.$get_details_payment->nominee_women_no_cases.'</td>
										<td style="font-size: 14px">'.$get_details_payment->nominee_women_amt_exptd_delivery.'</td>
										<td style="font-size: 14px">'.$get_details_payment->nominee_women_amt_subseq_perd.'</td>
										<td style="font-size: 14px">'.$get_details_payment->nominee_women_pymt_med_bonus.'</td>
										<td style="font-size: 14px">'.$get_details_payment->nominee_women_pymt_leave_wages.'</td>
										<td style="font-size: 14px">'.$get_details_payment->nominee_women_pymt_leave_illness.'</td>	
									</tr>
									
									<tr>
										<td style="font-size: 14px"><b>Legal representative of the women</b></td>
										<td style="font-size: 14px">'.$get_details_payment->legal_repr_women_no_cases.'</td>
										<td style="font-size: 14px">'.$get_details_payment->legal_repr_women_amt_exptd_delivery.'</td>
										<td style="font-size: 14px">'.$get_details_payment->legal_repr_women_amt_subseq_perd.'</td>
										<td style="font-size: 14px">'.$get_details_payment->legal_repr_women_pymt_med_bonus.'</td>
										<td style="font-size: 14px">'.$get_details_payment->legal_repr_women_pymt_leave_wages.'</td>
										<td style="font-size: 14px">'.$get_details_payment->legal_repr_women_pymt_leave_illness.'</td>	
									</tr>	
								</table>		
							</td>
						</tr>
						<tr>
							<td style="font-size: 14px">3. No. of cases in which payment was made on the order of competent Authority or &nbsp;&nbsp;&nbsp;&nbsp;Inspector</td>
							<td style="font-size: 14px">'.$get_details_payment->no_cases_pymt_order_insp.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">4. Number of women workers who absconded after receiving the first installment of &nbsp;&nbsp;&nbsp;&nbsp;maternity benefits</td>
							<td style="font-size: 14px">'.$get_details_payment->no_women_worker_recv_first_instal.'</td>
						</tr>
					</table>
					<table cellspacing="0" cellpadding="5" width="100%">
						<tr>
							<td style="font-size: 14px" width="40%">5. Remarks</td>
							<td style="font-size: 14px" width="60%">'.$get_details_payment->details_payment_remarks.'</td>
						</tr>
						<tr>
							<td colspan="2"><br><br><br><br></td>
						</tr>
						<tr>
							<td></td>
							<td align="center">.........................................................................</td>
						</tr>
						<tr>
							<td></td>
							<td style="font-size: 14px" align="center">Signature of the Employer</td>
						</tr>
						<tr>
							<td></td>
							<td style="font-size: 14px" align="center">Dated: '.date("l\, jS F\, Y h:i:s A").'</td>
						</tr>
					</table>
					';	
					
					
				$pw_file_name = 'Maternity_Benefit_'.$annual_return_ID.'_'.$get_factory_info->annual_return_year.'_'.rand(1, 100000);
				
				ob_end_clean();
				
				/*$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 20, 10, 0, 0);
				$mpdf->SetDisplayMode('fullpage');
				$mpdf->SetHTMLHeader('
				<div style="padding-top:50px; text-align: right; font-size:10px;">
					Page {PAGENO} of {nb}
				</div>');
				$mpdf->showWatermarkImage = true;
				$mpdf->WriteHTML($page_output);
				$mpdf->Output($pw_file_name.'.pdf', 'D');*/
				
				return pdf_using_mpdf_api($page_output, $pw_file_name);
			
			}
				
		}
	}