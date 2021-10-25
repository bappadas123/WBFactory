<?php

	function payment_of_wages_pdf($form, &$form_state, $annual_returnID = '', $factoryID = '') {
		
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
		
		$getdata_address =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
		$factory_address =	get_full_address('fa_annual_return','sub-table',$get_factory_info->id,$getdata_address);
		
		$get_all_annual =  ar_common_application_data($annual_return_ID);
		
		$get_worker_details_mandays = get_worker_details_mandays($annual_return_ID);
		$get_worker_details_avg_daily = get_worker_details_avg_daily($annual_return_ID);
		
		$get_wages_paid_include_deduction = get_total_wages_paid_include_deduction($annual_return_ID);
		$get_disbursement_fine_funds = get_disbursement_fine_funds($annual_return_ID);
		
		if($get_all_annual['ar_id'] == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up the Factory Information first.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/annual-return-common/'.$annual_returnID.'/'.$factory_typeID.'/'.$factoryID) ;	
		}
		
		if($get_wages_paid_include_deduction->annual_return_id == NULL || $get_disbursement_fine_funds->annual_return_id == NULL) {
			drupal_set_message(('<h5><i class="icon fa fa-warning"></i> Please fill up this.</h5>'),'alert alert-danger alert-dismissible');
			drupal_goto('applicant/payment-of-wages/'.$annual_returnID.'/'.$factoryID) ;	
		}
		
		
		if(!empty($application_status) && $application_status == 'F') {
			
			//payment of wages
			if($get_factory_info->payment_wages_flag == 1 && $get_wages_paid_include_deduction->annual_return_id != NULL && $get_disbursement_fine_funds->annual_return_id != NULL) {
		
		
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
					<h1 align="center">Form IV</h1>
					<h4 align="center">(See Rule 19)</h4>
					<h5 align="center">ANNUAL RETURN UNDER THE WEST BENGAL PAYMENT OF WAGES RULES</h4>
					</div>
					
					<table width="100%" cellspacing="0" cellpadding="0"> 
						<tr>
							<td style="font-size: 16px" width="50%">Registration No.: '.$get_factory_info->registration_number.'</td>
							<td align="right" style="font-size: 16px" width="50%">Classification Code No.: '.$get_factory_info->classification_no.'</td>
						</tr>
						<tr>
							<td colspan="2"></td>
						</tr>
						<tr>
							<td colspan="2"></td>
						</tr>
						<tr>
							<td align="center" colspan="2"><u><h4>WAGES AND DEDUCTIONS FROM WAGES</h4></u></td>
						</tr>
						<tr>
							<td colspan="2"></td>
						</tr>
						<tr>
							<td colspan="2" style="font-size: 16px"><b>Return for the year ending 31st December, '.$get_factory_info->annual_return_year.'</b></td>
						</tr>
					</table>
					<table cellspacing="0" cellpadding="0" width="100%">
						<tr>
							<td style="font-size: 14px" width="50%">1. (a) Name of the Factory:</td>
							<td style="font-size: 14px" width="50%">'.$get_factory_info->factory_name.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Postal Address:</td>
							<td style="font-size: 14px">'.$factory_address.', '.$get_factory_info->addrline.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;(b) Nature of Industry:</td>
							<td style="font-size: 14px">'.$get_factory_info->industry_nature.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">2. Number of days worked during the year:</td>
							<td style="font-size: 14px">'.$get_factory_info->days_worked_year.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">3. (a) Number* of mandays worked during the year:</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">
							
								<table cellspacing="0" cellpadding="10" width="100%" border="1">
									<tr>
										<th style="font-size: 14px" colspan="2">Adults</th>  
										<th style="font-size: 14px" colspan="2">Adolescents</th>
										<th style="font-size: 14px" colspan="2">Children </th>
						
									</tr>
									<tr>
										<th style="font-size: 14px">Men</th>
										<th style="font-size: 14px">Women</th>  
										<th style="font-size: 14px">Male</th>
										<th style="font-size: 14px">Female</th>
										<th style="font-size: 14px">Boys</th>
										<th style="font-size: 14px">Girls</th>
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
										<td style="font-size: 14px" align="center">'.$mandays_worker_adult_men.'</td>
										<td style="font-size: 14px" align="center">'.$mandays_worker_adult_women.'</td>
										<td style="font-size: 14px" align="center">'.$mandays_worker_adot_male.'</td>
										<td style="font-size: 14px" align="center">'.$mandays_worker_adot_female.'</td>
										<td style="font-size: 14px" align="center">'.$mandays_worker_child_boys.'</td>
										<td style="font-size: 14px" align="center">'.$mandays_worker_child_girls.'</td>
									</tr>
									<tr>
										<td style="font-size: 14px" colspan="6" align="right">Total: '.$get_worker_details_mandays->mandays_worker_total.'</td>
									</tr>
								</table>
								
							</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">&nbsp;&nbsp;&nbsp;&nbsp;(b) **Average daily number of persons employed during the year:</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">
							
								<table cellspacing="0" cellpadding="10" width="100%" border="1">
									<tr>
										<th style="font-size: 14px" colspan="2">Adults</th>  
										<th style="font-size: 14px" colspan="2">Adolescents</th>
										<th style="font-size: 14px" colspan="2">Children </th>
						
									</tr>
									<tr>
										<th style="font-size: 14px">Men</th>
										<th style="font-size: 14px">Women</th>  
										<th style="font-size: 14px">Male</th>
										<th style="font-size: 14px">Female</th>  
										<th style="font-size: 14px">Boys</th>
										<th style="font-size: 14px">Girls</th>
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
										<td style="font-size: 14px" align="center">'.$avg_daily_worker_adult_men.'</td>
										<td style="font-size: 14px" align="center">'.$avg_daily_worker_adult_women.'</td>
										<td style="font-size: 14px" align="center">'.$avg_daily_worker_adot_male.'</td>
										<td style="font-size: 14px" align="center">'.$avg_daily_worker_adot_female.'</td>
										<td style="font-size: 14px" align="center">'.$avg_daily_worker_child_boys.'</td>
										<td style="font-size: 14px" align="center">'.$avg_daily_worker_child_girls.'</td>
									</tr>
									<tr>
										<td style="font-size: 14px" colspan="6" align="right">Total: '.$get_worker_details_avg_daily->avg_daily_worker_total.'</td>
									</tr>
								</table>
								
							</td>
						</tr>
					</table>
					<table cellspacing="8" cellpadding="2" width="100%">
						<tr>
							<td style="font-size: 14px" colspan="2">4. Total wages paid include deduction under Section 7(2) on the following accounts:</td>
						</tr>
						<tr>
							<td width="75%"></td>
							<td style="font-size: 14px" width="25%">Rs.</td>
						</tr>
						<tr>
							<td></td>
							<td><hr></td>
						</tr>
						<tr>
							<td style="font-size: 14px" width="75%">&nbsp;&nbsp;&nbsp;&nbsp;(a) Profit sharing bonus</td>
							<td style="font-size: 14px" width="25%">'.$get_wages_paid_include_deduction->total_wages_profit_bonus.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;***(b) Money value of concessions</td>
							<td style="font-size: 14px">'.$get_wages_paid_include_deduction->total_wages_money_value.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;(c) Basic wages including overtime and non-profit sharing bonus</td>
							<td style="font-size: 14px">'.$get_wages_paid_include_deduction->total_wages_basic_wages.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;(d) Dearness and other allowances(not in kind)</td>
							<td style="font-size: 14px">'.$get_wages_paid_include_deduction->total_wages_da.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;(e) Arrears of pay in respect of the previous years paid during the year</td>
							<td style="font-size: 14px">'.$get_wages_paid_include_deduction->total_wages_arrears_pay.'</td>
						</tr>
						<tr>
							<td colspan="2"><hr></td>
						</tr>
						<tr>
							<td align="right">Total:</td>
							<td style="font-size: 14px">'.$get_wages_paid_include_deduction->total_wages_total_amt.'</td>
						</tr>
					</table>
					<table cellspacing="8" cellpadding="2" width="100%">
						<tr>
							<td style="font-size: 14px" colspan="3">5. Deductions--Number of cases and amount realised:</td>
						</tr>
						<tr>
							<td width="60%"></td>
							<td style="font-size: 14px" width="20%">Number of cases</td>
							<td style="font-size: 14px" width="20%">Amount realised(Rs.)</td>
						</tr>
						<tr>
							<td></td>
							<td colspan="2"><hr></td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;(a) Fines</td>
							<td style="font-size: 14px" align="center">'.$get_wages_paid_include_deduction->deductions_fines_no_cases.'</td>
							<td style="font-size: 14px">'.$get_wages_paid_include_deduction->deductions_fines_amt_realised.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;(b) Money value of concessions</td>
							<td style="font-size: 14px" align="center">'.$get_wages_paid_include_deduction->deductions_damg_loss_no_cases.'</td>
							<td style="font-size: 14px">'.$get_wages_paid_include_deduction->deductions_damg_loss_amt_realised.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;(c) Basic wages including overtime and non-profit sharing bonus</td>
							<td style="font-size: 14px" align="center">'.$get_wages_paid_include_deduction->deductions_breach_contct_no_cases.'</td>
							<td style="font-size: 14px">'.$get_wages_paid_include_deduction->deductions_breach_contct_amt_realised.'</td>
						</tr>
						<tr>
							<td></td>
							<td colspan="2"><hr></td>
						</tr>
						<tr>
							<td></td>
							<td align="right">Total:</td>
							<td>'.$get_wages_paid_include_deduction->deductions_total_amt.'</td>
						</tr>
					</table>
					<table cellspacing="8" cellpadding="2" width="100%">
						<tr>
							<td style="font-size: 14px" colspan="3">6. Fines fund:</td>
						</tr>	
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;(i) Balance of fines fund in hand at the beginning of the year</td>
							<td style="font-size: 14px" align="center">Rs. '.$get_disbursement_fine_funds->balance_fines_fund_beginning_year.'</td>
						</tr>
						<tr>
							<td colspan="2" style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;(ii) Disbursement from fine funds:</td>
						</tr>
						<tr>
							<td colspan="2"><hr></td>
						</tr>
						<tr>
							<td width="65%" align="center" style="font-size: 14px">Purpose</td>
							<td width="35%" align="center" style="font-size: 14px">Amount</td>
						</tr>
						<tr>
							<td colspan="2"><hr></td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;(a) '.$get_disbursement_fine_funds->disbursement_a_purpose.'</td>
							<td align="center" style="font-size: 14px">'.$get_disbursement_fine_funds->disbursement_a_amt.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;(b) '.$get_disbursement_fine_funds->disbursement_b_purpose.'</td>
							<td align="center" style="font-size: 14px">'.$get_disbursement_fine_funds->disbursement_b_amt.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;(c) '.$get_disbursement_fine_funds->disbursement_c_purpose.'</td>
							<td align="center" style="font-size: 14px">'.$get_disbursement_fine_funds->disbursement_c_amt.'</td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;(d) '.$get_disbursement_fine_funds->disbursement_d_purpose.'</td>
							<td align="center" style="font-size: 14px">'.$get_disbursement_fine_funds->disbursement_d_amt.'</td>
						</tr>
						<tr>
							<td></td>
							<td><hr></td>
						</tr>
						<tr>
							<td align="right" style="font-size: 14px">Total:</td>
							<td align="center" style="font-size: 14px">'.$get_disbursement_fine_funds->disbursement_fines_fund_total_amt.'</td>
						</tr>
						<tr>
							<td colspan="2"><hr></td>
						</tr>
						<tr>
							<td style="font-size: 14px">&nbsp;&nbsp;&nbsp;&nbsp;(iii) Balance of fines fund in hand at the end of the year </td>
							<td style="font-size: 14px" align="center">Rs. '.$get_disbursement_fine_funds->balance_fines_fund_end_year.'</td>
						</tr>
						
					</table>	
					';
				
				$page_output.= '
					
					<table cellspacing="8" cellpadding="2" width="100%">
						<tr>
							<td colspan="2"><br><br><br><br><br></td>
						</tr>
						<tr>
							<td width="50%"></td>
							<td style="font-size: 14px" align="center" width="50%">Signature</td>
						</tr>
						<tr>
							<td colspan="2"><br><br></td>
						</tr>
						<tr>
							<td width="50%"></td>
							<td style="font-size: 14px" align="left" width="50%">Designation..........................................................</td>
						</tr>
						<tr>
							<td colspan="2"><br><br></td>
						</tr>
						<tr>
							<td style="font-size: 14px" width="50%">Dated: '.date("l\, jS F\, Y h:i:s A").'</td>
							<td width="50%"></td>
						</tr>
						<tr>
							<td colspan="2"><hr></td>
						</tr>
						
						<tr>
							<td style="font-size: 14px" colspan="2">*This is the aggregate number of attendances during the year.</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">**The average daily number of persons employed during the year is obtained by dividing the aggregate number of attendance during the year by the number of working days.</td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">***The money value of concessions should be obtained by taking the difference of the prince paid by the employer and the actual price paid by the employees for supply of essential commodities given free or at concessional rates.</td>
						</tr>
						<tr>
							<td colspan="2"><br></td>
						</tr>
						<tr>
							<td style="font-size: 14px" colspan="2">Note: <b>This return should be Digitally Signed and Uploaded into the Portal by 31st January of the succeeding year.</b></td>
						</tr>
					</table>
				
				';
				
				
				$pw_file_name = 'Payment_of_Wages_'.$annual_return_ID.'_'.$get_factory_info->annual_return_year.'_'.rand(1, 100000);
				
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