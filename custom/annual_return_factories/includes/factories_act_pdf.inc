<?php

	function factories_act_pdf($form, &$form_state, $annual_returnID = '', $factoryID = '') {
		
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
		
		$getdata_address =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
		$factory_address =	get_full_address('fa_annual_return','sub-table',$get_factory_info->id,$getdata_address);
		
		$get_all_annual =  ar_common_application_data($annual_return_ID);
		
		$get_worker_details_mandays = get_worker_details_mandays($annual_return_ID);
		$get_worker_details_avg_daily = get_worker_details_avg_daily($annual_return_ID);
		
		$get_leave_wages_details = get_leave_wages_details($annual_return_ID);
		
		$get_dangerous_operation_details = get_dangerous_operation($annual_return_ID);
		$get_safety_officers_details = get_safety_officers($annual_return_ID);
		$get_welfare_officers_details = get_welfare_officers($annual_return_ID);
		$get_facilities_section_details = get_facilities_section($annual_return_ID);
		$get_accidents_details = get_accidents_details($annual_return_ID);
		$get_suggestion_scheme_details = get_suggestion_scheme($annual_return_ID);
		
		$get_factory_act_all_data = get_factory_act_all_data($annual_return_ID);
		
		if($get_all_annual['ar_id'] == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Factory Information first.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/annual-return-common/'.$annual_returnID.'/'.$factory_typeID.'/'.$factoryID) ;	
		}
		
		if($get_factory_act_all_data->ar_id == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/factories-act-apply/dangerous_operation/'.$annual_returnID.'/'.$factoryID) ;	
		}
		
		
		if(!empty($application_status) && $application_status == 'F') {
		
			//factories rules
			if($get_factory_info->factories_act_flag == 1 && $get_factory_act_all_data->ar_id != NULL) {
			
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
					<div>
					<h1 align="center">Form 22</h1>
					<h4 align="center">[See Clause (1) of Rule 103]</h4>
					<h5 align="center">ANNUAL RETURN UNDER THE WEST BENGAL FACTORIES RULES</h4>
					</div>
					<table width="100%" cellspacing="0" cellpadding="5">
						<tr>
							<td style="font-size: 16px" width="50%">Year ending 31st December, '.$get_factory_info->annual_return_year.'</td>
							<td align="right" style="font-size: 16px" width="50%">Classification Code No.: '.$get_factory_info->classification_no.'</td>
						</tr> 
					</table>
					<table width="100%" cellspacing="0" cellpadding="5"> 
					
						<tr>
							<td style="font-size: 14px" width="60%">1. Registration Number of Factory</td>
							<td style="font-size: 14px" width="40%">'.$get_factory_info->registration_number.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">2. Name of the Factory</td>
							<td style="font-size: 14px">'.$get_factory_info->factory_name.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">3. Name of the Occupier</td>
							<td style="font-size: 14px">'.$get_factory_info->name_occupier.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">4. Name of the Manager</td>
							<td style="font-size: 14px">'.$get_factory_info->name_manager.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">5. District</td>
							<td style="font-size: 14px">'.$get_district_details->district_name.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">6. Full Postal Address of Factory</td>
							<td style="font-size: 14px">'.$factory_address.', '.$get_factory_info->addrline.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">7. Nature of Industry</td>
							<td style="font-size: 14px">'.$get_factory_info->industry_nature.'</td>
						</tr>
						
						<tr>
							<td style="font-size: 14px" colspan="2" align="center"><b>Number of workers and particulars of employment</b></td>
						</tr>
						<tr>
							<td style="font-size: 14px">8. Number of days worked in the year</td>
							<td style="font-size: 14px">'.$get_factory_info->days_worked_year.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">9. Number of mandays worked during the year:</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">
							
								<table cellspacing="0" cellpadding="8" width="100%" border="1">
									<tr>
										<th colspan="2">Adults</th>  
										<th colspan="2">Adolescents</th>
										<th colspan="2">Children </th>
						
									</tr>
									<tr>
										<th >Men</th>
										<th >Women</th>  
										<th >Male</th>
										<th >Female</th>  
										<th >Boys</th>
										<th >Girls</th>
									</tr>
									';
					$mandays_worker_adult_men = $get_worker_details_mandays->mandays_per_worker_adult_men + $get_worker_details_mandays->mandays_con_worker_adult_men;
					$mandays_worker_adult_women = $get_worker_details_mandays->mandays_per_worker_adult_women + $get_worker_details_mandays->mandays_con_worker_adult_women;
					$mandays_worker_adot_male = $get_worker_details_mandays->mandays_per_worker_adol_male + $get_worker_details_mandays->mandays_con_worker_adol_male;
					$mandays_worker_adot_female = $get_worker_details_mandays->mandays_per_worker_adol_female + $get_worker_details_mandays->mandays_con_worker_adol_female;
					$mandays_worker_child_boys = $get_worker_details_mandays->mandays_per_worker_child_boys + $get_worker_details_mandays->mandays_con_worker_child_boys;
					$mandays_worker_child_girls = $get_worker_details_mandays->mandays_per_worker_child_girls + $get_worker_details_mandays->mandays_con_worker_child_girls;
				
					$page_output.= '
									<tr>
										<td align="center">'.$mandays_worker_adult_men.'</td>
										<td align="center">'.$mandays_worker_adult_women.'</td>
										<td align="center">'.$mandays_worker_adot_male.'</td>
										<td align="center">'.$mandays_worker_adot_female.'</td>
										<td align="center">'.$mandays_worker_child_boys.'</td>
										<td align="center">'.$mandays_worker_child_girls.'</td>
									</tr>
									<tr>
										<td colspan="6" align="right">Total: '.$get_worker_details_mandays->mandays_worker_total.'</td>
									</tr>
								</table>
								
							</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">10. Average number of workers employed daily (See explanatory note):</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">
							
								<table cellspacing="0" cellpadding="9" width="100%" border="1">
									<tr>
										<th colspan="2">Adults</th>  
										<th colspan="2">Adolescents</th>
										<th colspan="2">Children </th>
						
									</tr>
									<tr>
										<th >Men</th>
										<th >Women</th>  
										<th >Male</th>
										<th >Female</th>  
										<th >Boys</th>
										<th >Girls</th>
									</tr>
									';
					$avg_daily_worker_adult_men = $get_worker_details_avg_daily->avg_daily_per_worker_adult_men + $get_worker_details_avg_daily->avg_daily_con_worker_adult_men;
					$avg_daily_worker_adult_women = $get_worker_details_avg_daily->avg_daily_per_worker_adult_women + $get_worker_details_avg_daily->avg_daily_con_worker_adult_women;
					$avg_daily_worker_adot_male = $get_worker_details_avg_daily->avg_daily_per_worker_adol_male + $get_worker_details_avg_daily->avg_daily_con_worker_adol_male;
					$avg_daily_worker_adot_female = $get_worker_details_avg_daily->avg_daily_per_worker_adol_female + $get_worker_details_avg_daily->avg_daily_con_worker_adol_female;
					$avg_daily_worker_child_boys = $get_worker_details_avg_daily->avg_daily_per_worker_child_boys + $get_worker_details_avg_daily->avg_daily_con_worker_child_boys;
					$avg_daily_worker_child_girls = $get_worker_details_avg_daily->avg_daily_per_worker_child_girls + $get_worker_details_avg_daily->avg_daily_con_worker_child_girls;
				
					$page_output.= '
									<tr>
										<td align="center">'.$avg_daily_worker_adult_men.'</td>
										<td align="center">'.$avg_daily_worker_adult_women.'</td>
										<td align="center">'.$avg_daily_worker_adot_male.'</td>
										<td align="center">'.$avg_daily_worker_adot_female.'</td>
										<td align="center">'.$avg_daily_worker_child_boys.'</td>
										<td align="center">'.$avg_daily_worker_child_girls.'</td>
									</tr>
									<tr>
										<td colspan="6" align="right">Total: '.$get_worker_details_avg_daily->avg_daily_worker_total.'</td>
									</tr>
								</table>
								
							</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">11. Total number of manhours worked including overtime:</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">
							
								<table cellspacing="0" cellpadding="10" width="100%" border="1">
									<tr>
										<th>Men</th>  
										<th>Women</th>
										<th>Children</th>
						
									</tr>
									';
					$tot_no_manhrs_men = $get_worker_details_mandays->tot_no_manhrs_per_men + $get_worker_details_mandays->tot_no_manhrs_con_men;
					$tot_no_manhrs_women = $get_worker_details_mandays->tot_no_manhrs_per_women + $get_worker_details_mandays->tot_no_manhrs_con_women;
					$tot_no_manhrs_child = $get_worker_details_mandays->tot_no_manhrs_per_child + $get_worker_details_mandays->tot_no_manhrs_con_child;
				
					$page_output.= '
									<tr>
										<td align="center">'.$tot_no_manhrs_men.'</td>
										<td align="center">'.$tot_no_manhrs_women.'</td>
										<td align="center">'.$tot_no_manhrs_child.'</td>
									</tr>
								</table>
								
							</td>
						</tr>
						<tr>
							<td colspan="2"><br><br><br><br></td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">12. Average number of hours worked per :</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">
							
								<table cellspacing="0" cellpadding="10" width="100%" border="1">
									<tr>
										<th>Men</th>  
										<th>Women</th>
										<th>Children</th>
						
									</tr>
									';
					$avg_no_hrs_worked_week_men = $get_worker_details_avg_daily->avg_no_hrs_worked_week_per_men + $get_worker_details_avg_daily->avg_no_hrs_worked_week_con_men;
					$avg_no_hrs_worked_week_women = $get_worker_details_avg_daily->avg_no_hrs_worked_week_per_women + $get_worker_details_avg_daily->avg_no_hrs_worked_week_con_women;
					$avg_no_hrs_worked_week_child = $get_worker_details_avg_daily->avg_no_hrs_worked_week_per_child + $get_worker_details_avg_daily->avg_no_hrs_worked_week_con_child;
				
					$page_output.= '
									<tr>
										<td align="center">'.$avg_no_hrs_worked_week_men.'</td>
										<td align="center">'.$avg_no_hrs_worked_week_women.'</td>
										<td align="center">'.$avg_no_hrs_worked_week_child.'</td>
									</tr>
								</table>
								
							</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">
								<table cellspacing="0" cellpadding="0" width="100%">
									<tr>
										<td style="font-size: 14px" width="90%">13. (a) Does the factory carry on any process or operation declared as dangerous under &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Section 87? (See Rule 94)</td>
										<td style="font-size: 14px" width="10%">'.$get_factory_info->dangerous_operation_process_in_factory.'</td>
									</tr>
									<tr>
										<td style="font-size: 14px" colspan="2">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(b) If so, give the following information:</td>
									</tr>
									<tr>
										<td style="font-size: 14px" colspan="2">
											';
											if($get_factory_info->dangerous_operation_process_in_factory == 'Yes') {
					$page_output .= '
											<table cellspacing="0" cellpadding="10" width="100%" border="1">
												<tr>
													<th style="font-size: 14px" width="55%"><b>Name of the dangerous process or operations carried on</b></th>
													<th style="font-size: 14px" width="45%"><b>Average number of persons employed daily in each of the processes or operations given in column 1</b></th>
												</tr>
												<tr>
													<td style="font-size: 14px" align="center"><b>1</td>
													<td style="font-size: 14px" align="center"><b>2</td>
												</tr>
												';
												$sl_no = 1;
												foreach($get_dangerous_operation_details as $dangerous_operation_details) {
					$page_output .= '
												<tr>
													<td>('.numberToRoman($sl_no).')&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'.$dangerous_operation_details->dangerous_operation_name.'</td>
													<td>'.$dangerous_operation_details->avg_persons_employed_daily_in_operation.'</td>
												</tr>';
													$sl_no++;		
												}
					$page_output .= '		</table>
												';
											} else if($get_factory_info->dangerous_operation_process_in_factory == 'No') {
					$page_output .= '
											<table cellspacing="0" cellpadding="10" width="100%" border="1">
												<tr>
													<th style="font-size: 14px" width="55%"><b>Name of the dangerous process or operations carried on</b></th>
													<th style="font-size: 14px" width="45%"><b>Average number of persons employed daily in each of the processes or operations given in column 1</b></th>
												</tr>
												<tr>
													<td style="font-size: 14px" align="center"><b>1</th>
													<td style="font-size: 14px" align="center"><b>2</th>
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
							</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2" align="center"><b>Leave with wages</b></td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">14. Total number of workers employed during the year:</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">
							
								<table cellspacing="0" cellpadding="10" width="100%" border="1">
									<tr>
										<th>Men</th>  
										<th>Women</th>
										<th>Children</th>
						
									</tr>
									';
					$tot_no_workers_year_men = $get_leave_wages_details->tot_no_workers_year_per_men + $get_leave_wages_details->tot_no_workers_year_con_men;
					$tot_no_workers_year_women = $get_leave_wages_details->tot_no_workers_year_per_women + $get_leave_wages_details->tot_no_workers_year_con_women;
					$tot_no_workers_year_child = $get_leave_wages_details->tot_no_workers_year_per_child + $get_leave_wages_details->tot_no_workers_year_con_child;
				
					$page_output.= '
									<tr>
										<td align="center">'.$tot_no_workers_year_men.'</td>
										<td align="center">'.$tot_no_workers_year_women.'</td>
										<td align="center">'.$tot_no_workers_year_child.'</td>
									</tr>
								</table>
								
							</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">15. Number of workers who were entitled to annual leave with wages during the year:</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">
							
								<table cellspacing="0" cellpadding="10" width="100%" border="1">
									<tr>
										<th>Men</th>  
										<th>Women</th>
										<th>Children</th>
						
									</tr>
									';
					$no_workers_annual_leave_men = $get_leave_wages_details->no_workers_annual_leave_per_men + $get_leave_wages_details->no_workers_annual_leave_con_men;
					$no_workers_annual_leave_women = $get_leave_wages_details->no_workers_annual_leave_per_women + $get_leave_wages_details->no_workers_annual_leave_con_women;
					$no_workers_annual_leave_child = $get_leave_wages_details->no_workers_annual_leave_per_child + $get_leave_wages_details->no_workers_annual_leave_con_child;
				
					$page_output.= '
									<tr>
										<td align="center">'.$no_workers_annual_leave_men.'</td>
										<td align="center">'.$no_workers_annual_leave_women.'</td>
										<td align="center">'.$no_workers_annual_leave_child.'</td>
									</tr>
								</table>
								
							</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">16. Number of workers who were granted leave during the year:</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">
							
								<table cellspacing="0" cellpadding="10" width="100%" border="1">
									<tr>
										<th>Men</th>  
										<th>Women</th>
										<th>Children</th>
						
									</tr>
									';
					$no_workers_granted_leave_men = $get_leave_wages_details->no_workers_granted_leave_per_men + $get_leave_wages_details->no_workers_granted_leave_con_men;
					$no_workers_granted_leave_women = $get_leave_wages_details->no_workers_granted_leave_per_women + $get_leave_wages_details->no_workers_granted_leave_con_women;
					$no_workers_granted_leave_child = $get_leave_wages_details->no_workers_granted_leave_per_child + $get_leave_wages_details->no_workers_granted_leave_con_child;
				
					$page_output.= '
									<tr>
										<td align="center">'.$no_workers_granted_leave_men.'</td>
										<td align="center">'.$no_workers_granted_leave_women.'</td>
										<td align="center">'.$no_workers_granted_leave_child.'</td>
									</tr>
								</table>
								
							</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">
							';
					$no_workers_discharged = $get_leave_wages_details->no_workers_discharged_permanent + $get_leave_wages_details->no_workers_discharged_contractual;
					$no_workers_lieu_leave = $get_leave_wages_details->no_workers_lieu_leave_permanent + $get_leave_wages_details->no_workers_lieu_leave_contractual;
					$page_output.= '		
								<table cellspacing="0" cellpadding="0" width="100%">
									<tr>
										<td style="font-size: 14px" width="90%">17. (a) Number of workers who were discharged, or dismissed from the service, or quit &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;emploment, or were superannuated, or who died while in service during the year</td>
										<td style="font-size: 14px" width="10%">'.$no_workers_discharged.'</td>
									</tr>
									<tr>
										<td style="font-size: 14px" width="90%">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(b) Number of such workers in respect of whom wages in lieu of leave were paid</td>
										<td style="font-size: 14px" width="10%">'.$no_workers_lieu_leave.'</td>
									</tr>
								</table>
							</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">
								<table cellspacing="0" cellpadding="0" width="100%">
									<tr>
										<td style="font-size: 14px" colspan="2" align="center"><b>Safety Officers</b></td>
									</tr>
									<tr>
										<td style="font-size: 14px" width="90%">18. (a) Number of Safety Officers required to be appointed as per Notification <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;under Section 40B</td>
										<td style="font-size: 14px" width="10%">'.$get_factory_info->no_of_safety_officers.'</td>
									</tr>
									<tr>
										<td style="font-size: 14px" colspan="2">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(b) Details of Safety Officers appointed:</td>
									</tr>
									<tr>
										<td style="font-size: 14px" colspan="2">
											';
									if($get_factory_info->no_of_safety_officers != NULL) {
					$page_output .= '
											<table cellspacing="0" cellpadding="5" width="100%" border="1">
												<tr>
													<th style="font-size: 14px" width="25%"><b>Name of Safety Officer</b></th>
													<th style="font-size: 14px" width="7%"><b>Date of Appoitment</b></th>
													<th style="font-size: 14px"  width="10%"><b>Qualification</b></th>
													<th style="font-size: 14px" width="22%"><b>Name of the Institution from which he obtained a degree or diploma or a certificate in Industrical Safety</b></th>
													<th style="font-size: 14px" width="22%"><b>**Name of the Institution from which thorough knowledge in Bengali was acquired and the examination passed</b></th>
													<th style="font-size: 14px" width="14%"><b>Date of passing the Viva Voice Test under Clause (d) of Rule 4 of the West Bengal Factories (Safety Officers) Rules</b></th>
												</tr>
												<tr>
													<td style="font-size: 14px" align="center"><b>1</td>
													<td style="font-size: 14px" align="center"><b>2</b></td>
													<td style="font-size: 14px" align="center"><b>3</b></td>
													<td style="font-size: 14px" align="center"><b>4</b></td>
													<td style="font-size: 14px" align="center"><b>5</b></td>
													<td style="font-size: 14px" align="center"><b>6</b></td>
												</tr>
												';
										$sl_no = 1;
										foreach($get_safety_officers_details as $safety_officers_details) {
					$page_output .= '
												<tr>
													<td style="font-size: 14px">('.numberToRoman($sl_no).')&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'.$safety_officers_details->safety_officers_name.'</td>
													<td style="font-size: 14px">'.implode('/', array_reverse(explode('-', $safety_officers_details->safety_officers_date_of_appoitment))).'</td>
													<td style="font-size: 14px">'.$safety_officers_details->safety_officers_qualification.'</td>
													<td style="font-size: 14px">'.$safety_officers_details->safety_officers_degree_institute_name.'</td>
													<td style="font-size: 14px">'.$safety_officers_details->safety_officers_bengali_knowledge_institute.'</td>
													<td style="font-size: 14px">'.implode('/', array_reverse(explode('-', $safety_officers_details->safety_officers_dop_viva_test))).'</td>
												</tr>';
											$sl_no++;		
										}
									}
					$page_output .= '
											</table>
										</td>
									</tr>
								</table>
							</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">
								<table cellspacing="0" cellpadding="0" width="100%">
									<tr>
										<td style="font-size: 14px" colspan="2" align="center"><b>Ambulance Room</b></td>
									</tr>
									<tr>
										<td style="font-size: 14px" width="90%">19. Is there an Ambulance Room provided in the factory as required under Section 45?</td>
										<td style="font-size: 14px" width="10%">'.$get_facilities_section_details->ambulance_room_in_factory.'</td>
									</tr>
									<tr>
										<td style="font-size: 14px" colspan="2" align="center"><b>Canteen</b></td>
									</tr>
									<tr>
										<td style="font-size: 14px">20. (a) No. of Canteens provided in the factory as required under Section 46</td>
										<td style="font-size: 14px">'.$get_facilities_section_details->no_canteen_in_factory.'</td>
									</tr>
								';
						if($get_facilities_section_details->canteen_provided_managed_run == 'department') {
							$canteen_managed_by = 'Departmentally';	
						} else if($get_facilities_section_details->canteen_provided_managed_run == 'contractor') {
							$canteen_managed_by = 'Through a Contractor';	
						}
					$page_output .= '<tr>
										<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(b) Is the Canteen provided managed/run:</td>
										<td style="font-size: 14px">'.$canteen_managed_by.'</td>
									</tr>
									<tr>
										<td style="font-size: 14px" colspan="2" align="center"><b>Shelters or Rest Rooms and Lunch Rooms</b></td>
									</tr>
									<tr>
										<td style="font-size: 14px">21. (a) No. of Shelters or Rest Rooms provided in the factory as required <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;under Section 47</td>
										<td style="font-size: 14px">'.$get_facilities_section_details->no_of_shelters_rest_room.'</td>
									</tr>
									<tr>
										<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(b) No. of Lunch Rooms provided in the factory as required under Section 47</td>
										<td style="font-size: 14px">'.$get_facilities_section_details->no_of_lunch_room.'</td>
									</tr>
									<tr>
										<td style="font-size: 14px" colspan="2" align="center"><b>Creches</b></td>
									</tr>
									<tr>
										<td style="font-size: 14px">22. (a) No. of Creches provided in the factory as required under Section 48</td>
										<td style="font-size: 14px">'.$get_facilities_section_details->no_of_creches_factory.'</td>
									</tr>
									<tr>
										<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(b) No. of children utilizing the creche</td>
										<td style="font-size: 14px">'.$get_facilities_section_details->no_of_child_utilize_creche.'</td>
									</tr>
								</table>
							</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">
								<table cellspacing="0" cellpadding="0" width="100%">
									<tr>
										<td style="font-size: 14px" colspan="2" align="center"><b>Welfare Officers</b></td>
									</tr>
									<tr>
										<td style="font-size: 14px" width="90%">23. (a) Number of Welfare Officers to be appointed as required<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;under Section 49</td>
										<td style="font-size: 14px" width="10%">'.$get_factory_info->no_of_welfare_officers.'</td>
									</tr>
									<tr>
										<td style="font-size: 14px" colspan="2">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(b) Details of Welfare Officers appointed:</td>
									</tr>
									<tr>
										<td style="font-size: 14px" colspan="2">
											';
									if($get_factory_info->no_of_welfare_officers != NULL) {
					$page_output .= '
											<table cellspacing="0" cellpadding="5" width="100%" border="1">
												<tr>
													<th style="font-size: 14px" width="25%"><b>Name of Welfare Officer</b></th>
													<th style="font-size: 14px" width="7%"><b>Date of Appoitment</b></th>
													<th style="font-size: 14px" width="22%"><b>Name of the Institution from which he obtained a degree or diploma in Labour and Social Welfare or when he passed the L.W.O. Training Course of the Govt. of West Bengal*</b></th>
													<th style="font-size: 14px" width="22%"><b>**Name of the Institution from which thorough knowledge in Bengali was acquired and the examination passed</b></th>
													<th style="font-size: 14px" width="14%"><b>Date of passing the Viva Voice Test under Clause (d) of Rule 5 of the West Bengal Factories (Welfare Officers) Rules</b></th>
													<th style="font-size: 14px"  width="10%"><b>Grade and scale of pay</b></th>
												</tr>
												<tr>
													<td style="font-size: 14px" align="center"><b>1</td>
													<td style="font-size: 14px" align="center"><b>2</b></td>
													<td style="font-size: 14px" align="center"><b>3</b></td>
													<td style="font-size: 14px" align="center"><b>4</b></td>
													<td style="font-size: 14px" align="center"><b>5</b></td>
													<td style="font-size: 14px" align="center"><b>6</b></td>
												</tr>
												';
										$sl_no = 1;
										foreach($get_welfare_officers_details as $welfare_officers_details) {
					$page_output .= '
												<tr>
													<td style="font-size: 14px">('.numberToRoman($sl_no).')&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'.$welfare_officers_details->welfare_officers_name.'</td>
													<td style="font-size: 14px">'.implode('/', array_reverse(explode('-', $welfare_officers_details->welfare_officers_date_of_appoitment))).'</td>
													<td style="font-size: 14px">'.$welfare_officers_details->welfare_officers_degree_institute_name.'</td>
													<td style="font-size: 14px">'.$welfare_officers_details->welfare_officers_bengali_knowledge_institute.'</td>
													<td style="font-size: 14px">'.implode('/', array_reverse(explode('-', $welfare_officers_details->welfare_officers_dop_viva_test))).'</td>
													<td style="font-size: 14px">'.$welfare_officers_details->welfare_officers_grade_scale.'</td>
												</tr>';
											$sl_no++;		
										}
									}
					$page_output .= '
											</table>
										</td>
									</tr>
									<tr>
										<td style="font-size: 14px" colspan="2">*If he was exempted under Rule 6 of the West Bengal Factories (Welfare Officers) Rule, please quote the number and date of Govtment order.</td>
									</tr>
									<tr>
										<td style="font-size: 14px" colspan="2">**To be furnished for officers whose mother-tongue is not Bengali.</td>
									</tr>
								</table>
							</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2" align="center"><b>Accidents</b></td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">24. (a) Total number of accidents<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(See explanatory note) :</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(i) Fatal</td>
							<td style="font-size: 14px">'.$get_accidents_details->tot_no_accidents_fatals.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(ii) Non-Fatal</td>
							<td style="font-size: 14px">'.$get_accidents_details->tot_no_accidents_nonfatals.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(b) Accidents in which workers returned to work during the year to which this return relates:</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(i) Accidents (workers injured) occurring during the year in which injured workers returned to work during the same year</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(aa) Number of accidents</td>
							<td style="font-size: 14px">'.$get_accidents_details->returnedtowork_during_year_no_of_accidents.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(bb) Mandays lost</td>
							<td style="font-size: 14px">'.$get_accidents_details->returnedtowork_during_year_mandays_lost.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(ii) Accidents (workers injured) occurring in the previous year in which injured workers returned to work during the year to which this return relates</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(aa) Number of accidents</td>
							<td style="font-size: 14px">'.$get_accidents_details->returnedtowork_previous_year_no_of_accidents.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(bb) Mandays lost</td>
							<td style="font-size: 14px">'.$get_accidents_details->returnedtowork_previous_year_mandays_lost.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(c) Accidents (workers injured) occurring during the year in which injured workers did not returned to work during the year to which this return relates:</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(aa) Number of accidents</td>
							<td style="font-size: 14px">'.$get_accidents_details->didnot_returned_to_work_no_of_accidents.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(bb) Mandays lost</td>
							<td style="font-size: 14px">'.$get_accidents_details->didnot_returned_to_work_mandays_lost.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2" align="center"><b>Suggestion Scheme</b></td>
						</tr>
						<tr>
							<td style="font-size: 14px">25. (a) Is a Suggestion Scheme in operation in the factory?</td>
							<td style="font-size: 14px">'.$get_suggestion_scheme_details->suggestion_scheme_operation_in_factory.'</td>
						</tr>
						';
					if($get_suggestion_scheme_details->suggestion_scheme_operation_in_factory == 'Yes') {
					$page_output .= '
						<tr>
							<td style="font-size: 14px" colspan="2">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(b) If so, the number of suggestion:</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(i) Received during the year</td>
							<td style="font-size: 14px">'.$get_suggestion_scheme_details->suggestion_scheme_received_during_year.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(ii) Accepted during the year</td>
							<td style="font-size: 14px">'.$get_suggestion_scheme_details->suggestion_scheme_accepted_during_year.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(c) Amount awared in cash prizes during the year</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(i) Total amount awared</td>
							<td style="font-size: 14px">'.$get_suggestion_scheme_details->suggestion_scheme_tot_amt_awarded.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(ii) Value of the maximum cash prize awarded</td>
							<td style="font-size: 14px">'.$get_suggestion_scheme_details->suggestion_scheme_value_max_cash_prize.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(iii) Value of the minimum cash prize awarded</td>
							<td style="font-size: 14px">'.$get_suggestion_scheme_details->suggestion_scheme_value_min_cash_prize.'</td>
						</tr>
						
						';
									
					} else if($get_suggestion_scheme_details->suggestion_scheme_operation_in_factory == 'No') {
					$page_output .= '
						<tr>
							<td style="font-size: 14px" colspan="2">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(b) If so, the number of suggestion:</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(i) Received during the year</td>
							<td style="font-size: 14px">Not Available</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(ii) Accepted during the year</td>
							<td style="font-size: 14px">Not Available</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(c) Amount awared in cash prizes during the year</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(i) Total amount awared</td>
							<td style="font-size: 14px">Not Available</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(ii) Value of the maximum cash prize awarded</td>
							<td style="font-size: 14px">Not Available</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(iii) Value of the minimum cash prize awarded</td>
							<td style="font-size: 14px">Not Available</td>
						</tr>
						
						';	
						
					}
					$page_output .='
						<tr>
							<td style="font-size: 14px" colspan="2">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Certified that the information furnished above is, to the best of my knowledge and belief, correct.</td>
						</tr>
						<tr>
							<td colspan="2"><br><br><br><br><br></td>
						</tr>
						<tr>
							<td style="font-size: 14px">Dated: '.date("l\, jS F\, Y h:i:s A").'</td>
							<td style="font-size: 14px" align="center">Signature of the Manager</td>
						</tr>
					</table>
					
					<table cellspacing="0" cellpadding="2" width="100%">
						<tr>
							<td><br><br><br><br><br></td>
						</tr>
						<tr>
							<td><hr></td>
						</tr>
						<tr>
							<td style="font-size: 14px" align="center"><b>THIS RETURN SHOULD BE SENT TO THE CHIEF INSPECTOR OF FACTORIES
							<br>
							BY 31ST JANUARY OF THE SUCCEEDING YEAR
							</b></td>
						</tr>
						<tr>
							<td style="font-size: 12px">Explanatory Notes:<br>
							1. The average number of workers employed daily should be calculated by dividing the aggregate number of attendance on working days (that is, mandays worked) by the number of working days in the year. In reckoning attendance, attendance by temporary as well as permanent employees should be counted, and all employees (including apprentices) should be included, whether they are employed directly or under contractors. Attendance on separate shifts (e.g. night and day shifts) should be counted separately. Days on which the factory was closed for whatever cause, and days on which the manufacturing processes were not carried on should not be treated as working days. However, if more than 50% of workers employed (on the previous day) attend to repair, maintenance or other such work on closed days, such days should be treated as working days. Partial attendance for less than half a shift on a working day should be ignored, while attendance for half a shift or more on such day should be treated as full attendance.
							
							</td>
						</tr>
						<tr>
							<td><br></td>
						</tr>
						<tr>
							<td style="font-size: 12px">
							2. For seasonal factories, the average number of workers employed during the working season and the off season should be given separately. Similarly the number of days worked and average number of manhours worked per week during the working and off season should be given separately.
							
							</td>
						</tr>
						<tr>
							<td><br></td>
						</tr>
						<tr>
							<td style="font-size: 12px">
							3. The average number of hours worked per week means the total actual hours worked by all workers during the year excluding the rest intervals but including overtime work divided by the product of average number of workers employed daily in the factory during the year and 52. In case the factory has not worked for the whole year, the number of weeks during which the factory worked should be used in place of the figure 52.
							
							</td>
						</tr>
						<tr>
							<td><br></td>
						</tr>
						<tr>
							<td style="font-size: 12px">
							4. Every person killed or injured should be treated as one separate accident. If in one occurrence, six persons were injured or killed it should be counted as six accidents.
							
							</td>
						</tr>
						<tr>
							<td><br></td>
						</tr>
						<tr>
							<td style="font-size: 12px">
							5. In item 24 (a) the number of accidents which took place during the year shouldbe given. In case of non-fatal accident, only those accidents which prevented workers from working for 48 hours or more, immediately following the accident should be indicated.
							
							</td>
						</tr>
					</table>
					
				';	
					
					
				$pw_file_name = 'Factories_Rules_'.$annual_return_ID.'_'.$get_factory_info->annual_return_year.'_'.rand(1, 100000);
				
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