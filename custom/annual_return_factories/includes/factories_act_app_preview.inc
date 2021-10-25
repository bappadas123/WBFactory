<?php
	
	function factories_act_app_preview($form, &$form_state, $annual_returnID = '', $factoryID = '') {
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
		$get_disbursement_fine_funds = get_disbursement_fine_funds($annual_return_ID);*/
		$get_factory_act_all_data = get_factory_act_all_data($annual_return_ID);
		/*$get_maternity_benefit_all_data = get_maternity_benefit_all_data($annual_return_ID);*/
		
		if($get_all_annual['ar_id'] == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Factory Information first.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/annual-return-common/'.$annual_returnID.'/'.$factory_typeID.'/'.$factoryID) ;	
		}
		
		if($get_factory_act_all_data->ar_id == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/factories-act-apply/dangerous_operation/'.$annual_returnID.'/'.$factoryID) ;	
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
		}*/
		
		if($get_factory_info->factories_act_flag == 1 && $get_factory_act_all_data->ar_id != NULL) {
			$factories_act_edit = l('Factories Rules Edit', 'applicant/factories-act-apply/dangerous_operation/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		} else {
			$factories_act_edit = '';
		}
		
		/*if($get_factory_info->maternity_benefit_flag == 1 && $get_maternity_benefit_all_data->ar_id != NULL) {
			$maternity_benefit_edit = l('Maternity Benefit Edit', 'applicant/maternity-benefit-apply/medical_officer/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		} else {
			$maternity_benefit_edit = '';
		}*/
		
		$form['header'] = array(
  			'#type'		=> 'markup',
			'#markup'	=> fact_act_app_preview($annual_return_ID, $factory_id)	
		);
		
		$form['back_link'] = array(
			'#markup' => l(t('Back'), 'applicant/ar-application-preview/ar_common_app_preview/'.$annual_returnID.'/'.$factoryID, array(
				'html' => TRUE,
				'attributes' => array('class' => array('btn btn-outline-dark pull-left'))
			))
		);
		
		if(!empty($application_status) && $application_status == 'In') {
			$form['fact_act_app_link_markup'] = array(
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
	
	function factories_act_app_preview_submit($form, &$form_state) {
		
	}
	
	function fact_act_app_preview($annual_return_ID = '', $factory_id = '') {
		global $base_root,$base_path,$user;
		
		$get_factory_info = get_annual_return_factory_information($annual_return_ID);
		
		$get_dangerous_operation_details = get_dangerous_operation($annual_return_ID);
		$get_safety_officers_details = get_safety_officers($annual_return_ID);
		$get_welfare_officers_details = get_welfare_officers($annual_return_ID);
		$get_facilities_section_details = get_facilities_section($annual_return_ID);
		$get_accidents_details = get_accidents_details($annual_return_ID);
		$get_suggestion_scheme_details = get_suggestion_scheme($annual_return_ID);
		
		$output = '';
		
		$output .='<div class="row"><div class="box box-info">
				<div class = "box-body"><div class="col-lg-12 col-md-12 col-sm-12">
				<table class="table table-bordered custom-table-view" width="100%"> 
					<tr>
   						<th>Parameters</th>
   						<th colspan="2">Inputs</th>
					</tr>';
	
	//section for Dangerous Operation			
		$output .= '<tr><td colspan="2" class="sub-title"><b>1. DANGEROUS PROCESS OR OPERATION</b></td></tr>
					<tr><td width="65%">(i). (a) Does the factory carry on any process or operation declared as dangerous under Section 87?</td><td width="35%">'.$get_factory_info->dangerous_operation_process_in_factory.'</td></tr>
					<tr><td colspan="2"><b>(b) Dangerous Process or Operation List</b></td></tr>
		';
				if($get_factory_info->dangerous_operation_process_in_factory == 'Yes') {
					$output .= '<tr><td colspan="2">
								<table class="table table-bordered custom-table-view" width="100%">
									<tr><th width="5%"><b>Sl. No.</b></th><th width="65%"><b>Dangerous Process or Operation Name</b></th><th width="30%"><b>Avg Persons Employed Daily in Operation</b></th></tr>';
					$sl_no = 1;
					foreach($get_dangerous_operation_details as $dangerous_operation_details) {
						$output .= '<tr><td>'.$sl_no.'</td><td>'.$dangerous_operation_details->dangerous_operation_name.'</td><td>'.$dangerous_operation_details->avg_persons_employed_daily_in_operation.'</td></tr>';
						$sl_no++;		
					}
					$output .= '</table>
								</td></tr>
					';
				} else if($get_factory_info->dangerous_operation_process_in_factory == 'No') {
					$output .= '<tr><td colspan="2">
								<table class="table table-bordered custom-table-view" width="100%">
									<tr><th width="5%"><b>Sl. No.</b></th><th width="65%"><b>Dangerous Process or Operation Name</b></th><th width="30%"><b>Avg Persons Employed Daily in Operation</b></th></tr>
									<tr><td colspan="3" align="center"><b>Not Available</b></td></tr>
								</table>
								</td></tr>';	
					
				}
				
	//section for Safety Officers		
		$output .= '<tr><td colspan="2" class="sub-title"><b>2. SAFETY OFFICERS DETAILS</b></td></tr>
					<tr><td width="65%">(i). (a) Number of Safety Officers required to be appointed as per Notification under Section 40B</td><td width="35%">'.$get_factory_info->no_of_safety_officers.'</td></tr>
					<tr><td colspan="2"><b>(b) Safety Officers Details List</b></td></tr>
		';
				if($get_factory_info->no_of_safety_officers != NULL) {
					$output .= '<tr><td colspan="2">
								<table class="table table-bordered custom-table-view" width="100%">
									<tr>
										<th width="5%"><b>Sl. No.</b></th>
										<th width="25%"><b>Safety Officer Name</b></th>
										<th width="10%"><b>Date of Appoitment</b></th>
										<th width="10%"><b>Qualification</b></th>
										<th width="20%"><b>Name of the degree Institution</b></th>
										<th width="20%"><b>Name of the bengali knowledge Institution</b></th>
										<th width="10%"><b>Viva Voice passing date</b></th>
									</tr>';
					$sl_no = 1;
					foreach($get_safety_officers_details as $safety_officers_details) {
						$output .= '<tr>
										<td>'.$sl_no.'</td>
										<td>'.$safety_officers_details->safety_officers_name.'</td>
										<td>'.implode('/', array_reverse(explode('-', $safety_officers_details->safety_officers_date_of_appoitment))).'</td>
										<td>'.$safety_officers_details->safety_officers_qualification.'</td>
										<td>'.$safety_officers_details->safety_officers_degree_institute_name.'</td>
										<td>'.$safety_officers_details->safety_officers_bengali_knowledge_institute.'</td>
										<td>'.implode('/', array_reverse(explode('-', $safety_officers_details->safety_officers_dop_viva_test))).'</td>
									</tr>';
						$sl_no++;		
					}
					$output .= '</table>
								</td></tr>
					';
				} else {
					$output .= '<tr><td colspan="2">
								<table class="table table-bordered custom-table-view" width="100%">
									<tr>
										<th width="5%"><b>Sl. No.</b></th>
										<th width="25%"><b>Safety Officer Name</b></th>
										<th width="10%"><b>Date of Appoitment</b></th>
										<th width="10%"><b>Qualification</b></th>
										<th width="20%"><b>Name of the degree Institution</b></th>
										<th width="20%"><b>Name of the bengali knowledge Institution</b></th>
										<th width="10%"><b>Viva Voice passing date</b></th>
									</tr>
									<tr><td colspan="7" align="center"><b>Not Available</b></td></tr>
								</table>
								</td></tr>';	
					
				}
				
	//section for Welfare Officers
		$output .= '<tr><td colspan="2" class="sub-title"><b>3. WELFARE OFFICERS DETAILS</b></td></tr>
					<tr><td width="65%">(i). (a) Number of Welfare Officers to be appointed as required under Section 49</td><td width="35%">'.$get_factory_info->no_of_safety_officers.'</td></tr>
					<tr><td colspan="2"><b>(b) Welfare Officers Details List</b></td></tr>
		';
				if($get_factory_info->no_of_welfare_officers != NULL) {
					$output .= '<tr><td colspan="2">
								<table class="table table-bordered custom-table-view" width="100%">
									<tr>
										<th width="5%"><b>Sl. No.</b></th>
										<th width="25%"><b>Welfare Officer Name</b></th>
										<th width="10%"><b>Date of Appoitment</b></th>
										<th width="20%"><b>Name of the degree Institution</b></th>
										<th width="20%"><b>Name of the bengali knowledge Institution</b></th>
										<th width="10%"><b>Viva Voice passing date</b></th>
										<th width="10%"><b>Grade and Scale Pay</b></th>
									</tr>';
					$sl_no = 1;
					foreach($get_welfare_officers_details as $welfare_officers_details) {
						$output .= '<tr>
										<td>'.$sl_no.'</td>
										<td>'.$welfare_officers_details->welfare_officers_name.'</td>
										<td>'.implode('/', array_reverse(explode('-', $welfare_officers_details->welfare_officers_date_of_appoitment))).'</td>
										<td>'.$welfare_officers_details->welfare_officers_degree_institute_name.'</td>
										<td>'.$welfare_officers_details->welfare_officers_bengali_knowledge_institute.'</td>
										<td>'.implode('/', array_reverse(explode('-', $welfare_officers_details->welfare_officers_dop_viva_test))).'</td>
										<td>'.$welfare_officers_details->welfare_officers_grade_scale.'</td>
									</tr>';
						$sl_no++;		
					}
					$output .= '</table>
								</td></tr>
					';
				} else {
					$output .= '<tr><td colspan="2">
								<table class="table table-bordered custom-table-view" width="100%">
									<tr>
										<th width="5%"><b>Sl. No.</b></th>
										<th width="25%"><b>Welfare Officer Name</b></th>
										<th width="10%"><b>Date of Appoitment</b></th>
										<th width="20%"><b>Name of the degree Institution</b></th>
										<th width="20%"><b>Name of the bengali knowledge Institution</b></th>
										<th width="10%"><b>Viva Voice passing date</b></th>
										<th width="10%"><b>Grade and Scale Pay</b></th>
									</tr>
									<tr><td colspan="7" align="center"><b>Not Available</b></td></tr>
								</table>
								</td></tr>';	
					
				}
				
	//section for Facility Section
		if($get_facilities_section_details->canteen_provided_managed_run == 'department') {
			$canteen_managed_by = 'Departmentally';	
		} else if($get_facilities_section_details->canteen_provided_managed_run == 'contractor') {
			$canteen_managed_by = 'Through a Contractor';	
		}
		$output .= '<tr><td colspan="2" class="sub-title"><b>4. AMBULANCE ROOM</b></td></tr>
					<tr><td width="65%">(i). Is there an Ambulance Room provided in the factory as required under Section 45?</td><td width="35%">'.$get_facilities_section_details->ambulance_room_in_factory.'</td></tr>
					<tr><td colspan="2" class="sub-title"><b>5. CANTEEN</b></td></tr>
					<tr><td>(i). (a) No. of Canteens provided in the factory as required under Section 46</td><td>'.$get_facilities_section_details->no_canteen_in_factory.'</td></tr>
					<tr><td>(b) Canteen provided managed/run</td><td>'.$canteen_managed_by.'</td></tr>
					<tr><td colspan="2" class="sub-title"><b>6. SHELTERS OR REST ROOMS AND LUNCH ROOMS</b></td></tr>
					<tr><td>(i). (a) No. of Shelters or Rest Rooms provided in the factory as required under Section 47</td><td>'.$get_facilities_section_details->no_of_shelters_rest_room.'</td></tr>
					<tr><td>(b) No. of Lunch Rooms provided in the factory as required under Section 47</td><td>'.$get_facilities_section_details->no_of_lunch_room.'</td></tr>
					<tr><td colspan="2" class="sub-title"><b>7. CRECHES</b></td></tr>
					<tr><td>(i). (a) No. of Creches provided in the factory as required under Section 48</td><td>'.$get_facilities_section_details->no_of_creches_factory.'</td></tr>
					<tr><td>(b) No. of children utilizing the creche</td><td>'.$get_facilities_section_details->no_of_child_utilize_creche.'</td></tr>
		';
		
	//section for Accident Details
		$output .= '<tr><td colspan="2" class="sub-title"><b>8. ACCIDENT DETAILS</b></td></tr>
					<tr><td colspan="2"><b>(a) Total number of accidents</b></td></tr>
					<tr><td width="65%">(i) Fatal</td><td width="35%">'.$get_accidents_details->tot_no_accidents_fatals.'</td></tr>
					<tr><td>(ii) Non-Fatal</td><td>'.$get_accidents_details->tot_no_accidents_nonfatals.'</td></tr>
					<tr><td colspan="2"><b>(b) Accidents in which workers returned to work during the year to which this return relates</b></td></tr>
					<tr><td colspan="2"><b>(i) Accidents (workers injured) occurring during the year in which injured workers returned to work during the same year</b></td></tr>
					<tr><td>(aa) Number of accidents</td><td>'.$get_accidents_details->returnedtowork_during_year_no_of_accidents.'</td></tr>
					<tr><td>(bb) Mandays lost</td><td>'.$get_accidents_details->returnedtowork_during_year_mandays_lost.'</td></tr>
					<tr><td colspan="2"><b>(ii) Accidents (workers injured) occurring in the previous year in which injured workers returned to work during the year to which this return relates</b></td></tr>
					<tr><td>(aa) Number of accidents</td><td>'.$get_accidents_details->returnedtowork_previous_year_no_of_accidents.'</td></tr>
					<tr><td>(bb) Mandays lost</td><td>'.$get_accidents_details->returnedtowork_previous_year_mandays_lost.'</td></tr>
					<tr><td colspan="2"><b>(c) Accidents (workers injured) occurring during the year in which injured workers did not returned to work during the year to which this return relates</b></td></tr>
					<tr><td>(aa) Number of accidents</td><td>'.$get_accidents_details->didnot_returned_to_work_no_of_accidents.'</td></tr>
					<tr><td>(bb) Mandays lost</td><td>'.$get_accidents_details->didnot_returned_to_work_mandays_lost.'</td></tr>
		';
		
	//section for Suggestion Scheme			
		$output .= '<tr><td colspan="2" class="sub-title"><b>9. SUGGESTION SCHEME</b></td></tr>
					<tr><td width="65%">(i). (a) Suggestion Scheme in operation in the factory</td><td width="35%">'.$get_suggestion_scheme_details->suggestion_scheme_operation_in_factory.'</td></tr>
		';
				if($get_suggestion_scheme_details->suggestion_scheme_operation_in_factory == 'Yes') {
					$output .= '<tr><td colspan="2"><b>(b) The number of suggestion</b></td></tr>
								<tr><td>(aa) Received during the year</td><td>'.$get_suggestion_scheme_details->suggestion_scheme_received_during_year.'</td></tr>
								<tr><td>(bb) Accepted during the year</td><td>'.$get_suggestion_scheme_details->suggestion_scheme_accepted_during_year.'</td></tr>
								<tr><td colspan="2"><b>(c) Amount awared in cash prizes during the year</b></td></tr>
								<tr><td>(aa) Total amount awared</td><td>'.$get_suggestion_scheme_details->suggestion_scheme_tot_amt_awarded.'</td></tr>
								<tr><td>(bb) Value of the maximum cash prize awarded</td><td>'.$get_suggestion_scheme_details->suggestion_scheme_value_max_cash_prize.'</td></tr>
								<tr><td>(cc) Value of the minimum cash prize awarded</td><td>'.$get_suggestion_scheme_details->suggestion_scheme_value_min_cash_prize.'</td></tr>
					
					';
								
				} else if($get_suggestion_scheme_details->suggestion_scheme_operation_in_factory == 'No') {
					$output .= '<tr><td colspan="2"><b>(b) The number of suggestion</b></td></tr>
								<tr><td>(aa) Received during the year</td><td>Not Available</td></tr>
								<tr><td>(bb) Accepted during the year</td><td>Not Available</td></tr>
								<tr><td colspan="2"><b>(c) Amount awared in cash prizes during the year</b></td></tr>
								<tr><td>(aa) Total amount awared</td><td>Not Available</td></tr>
								<tr><td>(bb) Value of the maximum cash prize awarded</td><td>Not Available</td></tr>
								<tr><td>(cc) Value of the minimum cash prize awarded</td><td>Not Available</td></tr>
					';	
					
				}
						
		$output .='</table>
				</div></div></div></div>'; 
		
		
		return $output;
		
	}