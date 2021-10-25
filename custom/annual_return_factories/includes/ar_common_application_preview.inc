<?php
	
	function ar_common_application_preview($form, &$form_state, $annual_returnID = '', $factoryID = '') {
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
		$get_factory_act_all_data = get_factory_act_all_data($annual_return_ID);
		$get_maternity_benefit_all_data = get_maternity_benefit_all_data($annual_return_ID);
		
		if($get_all_annual['ar_id'] == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Factory Information first.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/annual-return-common/'.$annual_returnID.'/'.$factory_typeID.'/'.$factoryID) ;	
		}
		
		if($get_wages_paid_include_deduction->annual_return_id == NULL || $get_disbursement_fine_funds->annual_return_id == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/payment-of-wages/'.$annual_returnID.'/'.$factoryID) ;	
		}
		
		if($get_factory_act_all_data->ar_id == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/factories-act-apply/dangerous_operation/'.$annual_returnID.'/'.$factoryID) ;	
		}
		
		if($get_factory_info->maternity_benefit_flag == 1) {
			if($get_maternity_benefit_all_data->ar_id == NULL) {
				drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this tab.</h5>'),'alert alert-danger alert-dismissible');
				drupal_goto('applicant/maternity-benefit-apply/medical_officer/'.$annual_returnID.'/'.$factoryID) ;	
			}
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
		
		
		$common_section_edit = l('Annual Return Common Section Edit', 'applicant/annual-return-common-apply/default/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		
		if($get_factory_info->payment_wages_flag == 1 && $get_wages_paid_include_deduction->annual_return_id != NULL && $get_disbursement_fine_funds->annual_return_id != NULL) {
			if(!empty($application_status) && $application_status == 'In') {
				$pw_app_preview	= l('<i class="" aria-hidden="true"></i> Payment of Wages Rules Application Preview', 'applicant/pw-application-preview/payment_wages_app_preview/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('title' => 'Payment of Wages Application Preview','class'=>array('btn btn-primary pull-left'))));
			} else {
				$pw_app_preview	= l('<i class="" aria-hidden="true"></i> Payment of Wages Rules Application View', 'applicant/pw-application-preview/payment_wages_app_preview/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('title' => 'Payment of Wages Application View','class'=>array('btn btn-primary pull-left'))));	
			}
			
			$payment_wages_edit = l('Payment of Wages Edit', 'applicant/payment-of-wages/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		} else {
			$pw_app_preview	= '';
			$payment_wages_edit = '';
		}
		
		if($get_factory_info->factories_act_flag == 1 && $get_factory_act_all_data->ar_id != NULL) {
			if(!empty($application_status) && $application_status == 'In') {
				$fa_app_preview	= l('<i class="" aria-hidden="true"></i> Factories Rules Application Preview', 'applicant/fact-act-application-preview/factories_act_app_preview/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('title' => 'Factories Rules Application Preview','class'=>array('btn btn-primary'))));
			} else {
				$fa_app_preview	= l('<i class="" aria-hidden="true"></i> Factories Rules Application View', 'applicant/fact-act-application-preview/factories_act_app_preview/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('title' => 'Factories Rules Application View','class'=>array('btn btn-primary'))));
			}
			
			$factories_act_edit = l('Factories Rules Edit', 'applicant/factories-act-apply/dangerous_operation/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		} else {
			$fa_app_preview	= '';
			$factories_act_edit = '';
		}
		
		if($get_factory_info->maternity_benefit_flag == 1 && $get_maternity_benefit_all_data->ar_id != NULL) {
			if(!empty($application_status) && $application_status == 'In') {
				$mb_app_preview	= l('<i class="" aria-hidden="true"></i> Maternity Benefit Rules Application Preview', 'applicant/mb-application-preview/maternity_benefit_app_preview/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('title' => 'Maternity Benefit Application Preview','class'=>array('btn btn-primary pull-right'))));
			} else {
				$mb_app_preview	= l('<i class="" aria-hidden="true"></i> Maternity Benefit Rules Application View', 'applicant/mb-application-preview/maternity_benefit_app_preview/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('title' => 'Maternity Benefit Application View','class'=>array('btn btn-primary pull-right'))));	
			}
			
			$maternity_benefit_edit = l('Maternity Benefit Edit', 'applicant/maternity-benefit-apply/medical_officer/'.$annual_returnID.'/'.$factoryID, array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
		} else {
			$mb_app_preview	= '';
			$maternity_benefit_edit = '';
		}
		
		
		$form['header'] = array(
  			'#type'		=> 'markup',
			'#markup'	=> ar_common_app_preview($annual_return_ID, $factory_id)	
		);
		
		$form['application_preview']['app_preview_section'] = array(
			'#prefix' 					=> '<div class="col-md-4 col-xs-4">'.$pw_app_preview.'</div><div class="col-md-4 col-xs-4" align="center">'.$fa_app_preview.'</div><div class="col-md-4 col-xs-4">'.$mb_app_preview.'</div><br><br>',
			'#suffix' 					=> '',
		);
		
		if(!empty($application_status) && $application_status == 'In') {	
			$form['application_preview']['finalAgree'] 	= array(
					'#prefix' 		=> '<div class="col-lg-12 col-md-12 col-sm-12">',	
					'#suffix' 		=> '</div>',
					'#type' 		=> 'checkbox',
					'#title' 		=> 'I hereby declare that the particulars given above are true the best of my knowledge and belief.',
					'#attributes'	=> array('id' => 'finalAgreeId','onchange' => 'return checkFinalAppCheckBox()'),
					'#required' 	=> TRUE,
			);
		}
		
		if(!empty($application_status) && $application_status == 'In') {
			if($get_factory_info->maternity_benefit_flag == 1) {
				$form['back_link'] = array(
					'#markup' => l(t('Back'), 'applicant/maternity-benefit-apply/details_of_payment/'.$annual_returnID.'/'.$factoryID, array(
						'html' => TRUE,
						'attributes' => array('class' => array('btn btn-outline-dark pull-left'))
					))
				);
			} else {
				$form['back_link'] = array(
					'#markup' => l(t('Back'), 'applicant/factories-act-apply/suggestion_scheme/'.$annual_returnID.'/'.$factoryID, array(
						'html' => TRUE,
						'attributes' => array('class' => array('btn btn-outline-dark pull-left'))
					))
				);
			}
		} else if(!empty($application_status) && $application_status == 'F') {
			$form['back_link'] = array(
				'#markup' => l(t('Back'), 'applicant/annual-return-list', array(
					'html' => TRUE,
					'attributes' => array('class' => array('btn btn-outline-dark pull-left'))
				))
			);
		} else if(!empty($application_status) && $application_status == 'U') {
			$form['back_link'] = array(
				'#markup' => l(t('Back'), 'applicant/annual-return-list', array(
					'html' => TRUE,
					'attributes' => array('class' => array('btn btn-outline-dark pull-left'))
				))
			);
		}
		
		if(!empty($application_status) && $application_status == 'In') {
   		
			$form['submit'] = array(
				'#prefix' => '',
				'#suffix' => '',
				'#attributes' => array('class' => array('btn btn-success pull-right')),
				'#type' => 'submit',
				'#value' => 'Final Submit & Continue'
			);
		} 
		else{
			$form['markup'] = array(
				'#type' => 'markup',
			   	'#prefix' => '',
				'#suffix' => '',
			);
		
		}
		
		if(!empty($application_status) && $application_status == 'In') {
			$form['ar_common_app_link_markup'] = array(
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
	
	function ar_common_application_preview_submit($form, &$form_state){
		$annual_return_ID = $form_state['values']['annual_return_id'];
		$factory_id = $form_state['values']['factory_id'];
		
		db_update('fa_annual_return')
		->fields(array(
			'full_application_status' => 'F',
			'modification_date'	   	  => date('Y-m-d H:i:s'),
		))
		->condition('id', $annual_return_ID, '=')
		->execute();
		
		drupal_goto('applicant/annual_return_pdf_upload/'.encryption_decryption_fun('encrypt', $annual_return_ID).'/'.encryption_decryption_fun('encrypt', $factory_id)) ;
	}
	
	function ar_common_app_preview($annual_return_ID = '', $factory_id = '') {
		global $base_root,$base_path,$user;
		
		$get_all_annual =  ar_common_application_data($annual_return_ID);
		
		//echo $get_all_annual[0]->cafa_id;
		//echo '<pre>';print_r($get_all_annual);die;
		
		$getdata_address =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
		$factory_address =	get_full_address('fa_annual_return','sub-table',$get_all_annual['ar_id'],$getdata_address);
		
		$get_zone_name = get_factory_zone_name($get_all_annual['factory_zone']);
		
		$output = '';
		
		$output .='<div class="row"><div class="box box-info">
				<div class = "box-body"><div class="col-lg-12 col-md-12 col-sm-12">
				<table class="table table-bordered custom-table-view"> <tr>
   								<th>Parameters</th>
   								<th>Inputs</th>
								</tr>';
		$output .= '<tr><td colspan="2" class="sub-title"><b>1. FACTORY INFORMATION</b></td></tr>
					<tr><td>(i). Name of the Factory</td><td>'.$get_all_annual['factory_name'].'</td></tr>
					<tr><td>(ii). Address of Factory</td><td>'.$factory_address.', '.$get_all_annual['addrline'].'</td></tr>
					<tr><td>(iii). Post Office</td><td>'.$get_all_annual['postoffice'].'</td></tr>
					<tr><td>(iv). Factory Zone</td><td>'.$get_zone_name['zone_name'].'</td></tr>
					<tr><td>(v). Nearest Landmark</td><td>'.$get_all_annual['nearest_landmark'].'</td></tr>
					<tr><td>(vi). Nature of Industry</td><td>'.$get_all_annual['industry_nature'].'</td></tr>
					<tr><td>(vii). Registration No.</td><td>'.$get_all_annual['registration_number'].'</td></tr>
					<tr><td>(viii). Registration Date</td><td>'.$get_all_annual['registration_date'].'</td></tr>
					<tr><td>(ix). Licence No.</td><td>'.$get_all_annual['licence_number'].'</td></tr>
					<tr><td>(x). Licence Date</td><td>'.$get_all_annual['licence_date'].'</td></tr>
					<tr><td>(xi). Classification No</td><td>'.$get_all_annual['classification_no'].'</td></tr>
					<tr><td>(xii). Occupier Name</td><td>'.$get_all_annual['name_occupier'].'</td></tr>
					<tr><td>(xiii). Manager Name</td><td>'.$get_all_annual['name_manager'].'</td></tr>
				</table>
				<table class="table table-bordered custom-table-view">
					<tr><td colspan="12" class="sub-title"><b>2. NUMBER OF DAYS WORKED DURING THE YEAR</b></td></tr>
					<tr><td colspan="6"> Number of days worked during the year</td><td colspan="6">'.$get_all_annual['days_worked_year'].'</td></tr>
				
					<tr><td colspan="12" class="sub-title"><b>3. NUMBER OF MANDAYS WORKED DURING THE YEAR</b></td></tr>
					<tr>
						<th colspan="6">Permanent</th>
						<th colspan="6">Contactual (Including daily wages)</th>
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
					</tr>
					<tr>
						<td>'.$get_all_annual['mandays_per_worker_adult_men'].'</td>
						<td>'.$get_all_annual['mandays_per_worker_adult_women'].'</td>
						<td>'.$get_all_annual['mandays_per_worker_adol_male'].'</td>
						<td>'.$get_all_annual['mandays_per_worker_adol_female'].'</td>
						<td>'.$get_all_annual['mandays_per_worker_child_boys'].'</td>
						<td>'.$get_all_annual['mandays_per_worker_child_girls'].'</td>
						<td>'.$get_all_annual['mandays_con_worker_adult_men'].'</td>
						<td>'.$get_all_annual['mandays_con_worker_adult_women'].'</td>
						<td>'.$get_all_annual['mandays_con_worker_adol_male'].'</td>
						<td>'.$get_all_annual['mandays_con_worker_adol_female'].'</td>
						<td>'.$get_all_annual['mandays_con_worker_child_boys'].'</td>
						<td>'.$get_all_annual['mandays_con_worker_child_girls'].'</td>
					</tr>
					
				</table>	
				<table class="table table-bordered custom-table-view">
					<tr><td colspan="12" class="sub-title"><b>4. AVERAGE DAILY NUMBER OF PERSONS EMPLOYED DURING THE YEAR</b></td></tr>
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
					</tr>
					<tr>
						<td>'.$get_all_annual['avg_daily_per_worker_adult_men'].'</td>
						<td>'.$get_all_annual['avg_daily_per_worker_adult_women'].'</td>
						<td>'.$get_all_annual['avg_daily_per_worker_adol_male'].'</td>
						<td>'.$get_all_annual['avg_daily_per_worker_adol_female'].'</td>
						<td>'.$get_all_annual['avg_daily_per_worker_child_boys'].'</td>
						<td>'.$get_all_annual['avg_daily_per_worker_child_girls'].'</td>
						<td>'.$get_all_annual['avg_daily_con_worker_adult_men'].'</td>
						<td>'.$get_all_annual['avg_daily_con_worker_adult_women'].'</td>
						<td>'.$get_all_annual['avg_daily_con_worker_adol_male'].'</td>
						<td>'.$get_all_annual['avg_daily_con_worker_adol_female'].'</td>
						<td>'.$get_all_annual['avg_daily_con_worker_child_boys'].'</td>
						<td>'.$get_all_annual['avg_daily_con_worker_child_girls'].'</td>
					</tr>
					
				</table>
				<table class="table table-bordered custom-table-view">
					<tr><td colspan="12" class="sub-title"><b>5. TOTAL NUMBER OF MANHOURS WORKED INCLUDING OVERTIME</b></td></tr>
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
					</tr>
					<tr>
						<td>'.$get_all_annual['tot_no_manhrs_per_men'].'</td>
						<td>'.$get_all_annual['tot_no_manhrs_per_women'].'</td>
						<td>'.$get_all_annual['tot_no_manhrs_per_child'].'</td>
						<td>'.$get_all_annual['tot_no_manhrs_con_men'].'</td>
						<td>'.$get_all_annual['tot_no_manhrs_con_women'].'</td>
						<td>'.$get_all_annual['tot_no_manhrs_con_child'].'</td>
					</tr>
				</table>
				<table class="table table-bordered custom-table-view">
					<tr><td colspan="12" class="sub-title"><b>6. AVERAGE NUMBER OF HOURS WORKED PER WEEK</b></td></tr>
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
					</tr>
					<tr>
						<td>'.$get_all_annual['avg_no_hrs_worked_week_per_men'].'</td>
						<td>'.$get_all_annual['avg_no_hrs_worked_week_per_women'].'</td>
						<td>'.$get_all_annual['avg_no_hrs_worked_week_per_child'].'</td>
						<td>'.$get_all_annual['avg_no_hrs_worked_week_con_men'].'</td>
						<td>'.$get_all_annual['avg_no_hrs_worked_week_con_women'].'</td>
						<td>'.$get_all_annual['avg_no_hrs_worked_week_con_child'].'</td>
					</tr>
				</table>
				<table class="table table-bordered custom-table-view">
					<tr><td colspan="12" class="sub-title"><b>7. TOTAL NUMBER OF WORKERS EMPLOYED DURING THE YEAR</b></td></tr>
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
					</tr>
					<tr>
						<td>'.$get_all_annual['tot_no_workers_year_per_men'].'</td>
						<td>'.$get_all_annual['tot_no_workers_year_per_women'].'</td>
						<td>'.$get_all_annual['tot_no_workers_year_per_child'].'</td>
						<td>'.$get_all_annual['tot_no_workers_year_con_men'].'</td>
						<td>'.$get_all_annual['tot_no_workers_year_con_women'].'</td>
						<td>'.$get_all_annual['tot_no_workers_year_con_child'].'</td>
					</tr>
				</table>
				<table class="table table-bordered custom-table-view">
					<tr><td colspan="12" class="sub-title"><b>8. NUMBER OF WORKERS WHO WERE ENTITLED TO ANNUAL LEAVE WITH WAGES DURING THE YEAR</b></td></tr>
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
					</tr>
					<tr>
						<td>'.$get_all_annual['no_workers_annual_leave_per_men'].'</td>
						<td>'.$get_all_annual['no_workers_annual_leave_per_women'].'</td>
						<td>'.$get_all_annual['no_workers_annual_leave_per_child'].'</td>
						<td>'.$get_all_annual['no_workers_annual_leave_con_men'].'</td>
						<td>'.$get_all_annual['no_workers_annual_leave_con_women'].'</td>
						<td>'.$get_all_annual['no_workers_annual_leave_con_child'].'</td>
					</tr>
				</table>
				<table class="table table-bordered custom-table-view">
					<tr><td colspan="12" class="sub-title"><b>9. NUMBER OF WORKERS WHO WERE GRANTED LEAVE DURING THE YEAR</b></td></tr>
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
					</tr>
					<tr>
						<td>'.$get_all_annual['no_workers_granted_leave_per_men'].'</td>
						<td>'.$get_all_annual['no_workers_granted_leave_per_women'].'</td>
						<td>'.$get_all_annual['no_workers_granted_leave_per_child'].'</td>
						<td>'.$get_all_annual['no_workers_granted_leave_con_men'].'</td>
						<td>'.$get_all_annual['no_workers_granted_leave_con_women'].'</td>
						<td>'.$get_all_annual['no_workers_granted_leave_con_child'].'</td>
					</tr>
				</table>
				<table class="table table-bordered custom-table-view">
					<tr><td colspan="12" class="sub-title"><b>10. (A) NUMBER OF WORKERS WHO WERE DISCHARGED, OR DISMISSED FROM THE SERVICE, OR QUIT EMPLOMENT, OR WERE SUPERANNUATED, OR WHO DIED WHILE IN SERVICE DURING THE YEAR</b></td></tr>
					<tr>
						<td width="50%">Permanent</th>
						<td>'.$get_all_annual['no_workers_discharged_permanent'].'</td>
					</tr>
					<tr>
						<td width="50%">Contractual (Including daily wages)</th>
						<td>'.$get_all_annual['no_workers_discharged_contractual'].'</td>
					</tr>
				</table>
				<table class="table table-bordered custom-table-view">
					<tr><td colspan="12" class="sub-title"><b>10. (B) NUMBER OF SUCH WORKERS IN RESPECT OF WHOM WAGES IN LIEU OF LEAVE WERE PAID</b></td></tr>
					<tr>
						<td width="50%">Permanent</th>
						<td>'.$get_all_annual['no_workers_lieu_leave_permanent'].'</td>
					</tr>
					<tr>
						<td width="50%">Contractual (Including daily wages)</th>
						<td>'.$get_all_annual['no_workers_lieu_leave_contractual'].'</td>
					</tr>
				</table>
				</div></div></div></div>';
								
		return $output;	
	}
	
	


	
//point 3 and point 4 total calculation code

//3. NUMBER OF MANDAYS WORKED DURING THE YEAR
/*<tr>
	<td colspan="12"><b>Total Worker(s) :- '.$get_all_annual['mandays_worker_total'].'</b></td>
</tr>*/

//4. AVERAGE DAILY NUMBER OF PERSONS EMPLOYED DURING THE YEAR
/*<tr>
	<td colspan="12"><b>Total Worker(s) :- '.$get_all_annual['avg_daily_worker_total'].'</b></td>
</tr>*/