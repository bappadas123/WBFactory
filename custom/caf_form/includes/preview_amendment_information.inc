		
<?php
		require_once $_SERVER['DOCUMENT_ROOT'].'/sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';
		function preview_amendment_information($serviceid, $factory_typeid,$applicationid,$linknumber){
		   global $base_root, $base_path;
			$service_id      	= encryption_decryption_fun('decrypt', $serviceid);
			$factory_type_id 	= encryption_decryption_fun('decrypt', $factory_typeid);
			$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
			$link_number 		= encryption_decryption_fun('decrypt', $linknumber);
			$link_date 			= encryption_decryption_fun('decrypt', $linkdate);
			$flag_mapp 			= encryption_decryption_fun('decrypt', $flagmapp);
			
			$get_all_data 		= get_fa_cafa($application_id);
			$reference_id		= $get_all_data['reference_number'];
			$value_factory_profile_type	= $get_fa_cafa['ownership_type'];
			$license_valid_upto			= $get_fa_cafa['license_valid_upto'];
			$is_year_calculation_tab	= $get_fa_cafa['is_year_calculation_tab'];
			$application_status			= $get_fa_cafa['application_status'];
			$period_for_application		= $get_fa_cafa['period_for_application'];
			$date_of_amenability       	= $get_fa_cafa['date_of_amenability'];
			
			$is_backlog			= $get_all_data['is_backlog'];
			if($is_backlog == 1){
				$plan_approval_no 	= $get_all_data['backlog_plan_approval_no'];
				$plan_approval_date = date('dS M Y', strtotime($get_all_data['backlog_plan_approval_date']));
			}if($is_backlog != 1){
				$plan_approval_no 	= $get_all_data['factory_plan_approval_number'];
				$plan_approval_date = date('dS M Y', strtotime($get_all_data['modification_date']));
			}
			if($get_all_data['wbpcb_category_name']==1){$consent ='Red';}
			if($get_all_data['wbpcb_category_name']==2){$consent ='Green';}
			if($get_all_data['wbpcb_category_name']==3){$consent ='Orange';}
			if($get_all_data['wbpcb_category_name']==4){$consent ='White';}
			if($get_all_data['wbpcb_category_name']==5){$consent ='Exempted';}
			
			if($get_all_data['factory_owershiptype']=="pv"){
   				$ownership_type = "Pvt Ltd Company";
			}if($get_all_data['factory_owershiptype']=="ltd"){
					$ownership_type = "Ltd Company";
			}if($get_all_data['factory_owershiptype']=="par_firm"){
					$ownership_type = "Partnership Firm";
			}if($get_all_data['factory_owershiptype']=="pro_firm"){
					$ownership_type = "Proprietorship Firm";
			}if($get_all_data['factory_owershiptype']=="govt"){
					$ownership_type = "Govt";
			}if($get_all_data['factory_owershiptype']=="psu"){
					$ownership_type = "PSU";
			}if($get_all_data['factory_owershiptype']=="others"){
					$ownership_type = "Others";
			};
			$energy_no = !empty($get_all_data['enargy_no'])?$get_all_data['enargy_no']:'n/a';
			$cin_no = !empty($get_all_data["cin_no"])?$get_all_data["cin_no"]:'n/a';
		
			$worker_details = fetch_old_data($application_id,$service_id,$factory_type_id,$reference_id);
			$content = '<style type="text/css">
							table, td, th {
								font-size:12px;
								font-family:Times New Roman;
								height:15px;
								color:#000;
								margin-top:10px;
							}
							td:hover {
								background-color:#d4e3e5;
							}
							h1 {
								font-size:11px;
								font-weight:normal;
							}
							h2,h3,h4 {
								font-size:12px;
							}
							.data{ 
								text-transform: uppercase;font-weight:bold;
							}
						</style>';
						$content .= '
							<html>
								<body style="background-color:#fff">';
			
						$content .= '
							<table width="100%" border="0" cellspacing="0" cellpadding="0">
								<tr>
									<td colspan="3" align="center" style="font-size:18px;"><strong>Directorate of factories <br> Govt. of West Bengal</strong></td>
								</tr>
								<tr>
									<td colspan="3"></td>
								</tr>
								<tr>
									<td colspan="3" align="left" style="font-size:14px;">
										<h4>A. BASIC INFORMATION</h4>
									</td>
								</tr>
								<tr>
									<td colspan="3">&nbsp;</td>
								</tr>
								<tr>
									<td width="2%"  valign="top">1. </td>
									<td width="49%" valign="top">(i). Date from which the premises is occupied(Amenabilty date)</td>
									<td width="49%"><span class="data">: '.date('dS M Y', strtotime($get_all_data['date_of_amenability'])).'</span></td>
								</tr>
								<tr>
									<td width="2%"  valign="top">&nbsp;</td>
									<td width="49%" valign="top">(ii). State the period of license required for date from application date</td>
									<td width="49%"><span class="data">: '.$get_all_data['period_for_application'].' year(s)</span></td>
								</tr>';
							if(!empty($previous_name))	{		 
							$content .= ' 
								<tr>
									<td colspan="3">&nbsp;</td>
								</tr>
								<tr>
									<td width="49%" valign="top" colspan="3">(b) Previous Name of the Factory (if different from the present name) </td>
								</tr>
								<tr>
									<td colspan="3">
									<table width="100%" border="0" cellspacing="0" cellpadding="0">
										<tr>
											<th align="center">Application Year</th>
											<th align="center">Change name</th>
											<th align="center">Description</th>
										</tr>
										<tr>
											<td colspan="3">&nbsp;</td>
										</tr>';
							foreach($previous_name as $previous){
							
							$content .='
								<tr>
									<td align="center">'.$previous->service_year.'</td>
									<td align="center">'.$previous->conversation_name.'</td>
									<td align="center">'.$previous->description_conversation.'</td>
								</tr>';
							}
				$content .='
							</table>
						</td>
					</tr>';
				}
			$content .= '
					<tr>
						<td colspan="3">&nbsp;</td>
					</tr>
					<tr>
						<td width="49%" valign="top" colspan="3">2. Amendment Details</td>
					</tr>
					<tr>
						<td colspan="3">';
					
				 $content .='<table width="100%"  border="1" cellspacing="0" cellpadding="0" class="custom-table-view-dashboard renewal-table">
							
					<tr>
						<th >Service Years</th>
						<th >Worker Men</th>
						<th >Worker Women</th>
						<th >Adolescents Male</th>  
						<th >Adolescents Female</th>
						<th >Children Male</th>  
						<th >Children Female</th>
						<th >Total Worker</th>  
						<th >Amendment Worker</th>
					</tr>';

	
	foreach($worker_details as $worker){
		$service_year 		= $worker->service_year;
		$worker_men 		= $worker->worker_men;
		$worker_women 		= $worker->worker_women;
		$adolescents_male 	= $worker->adolescents_male;
		$adolescents_female = $worker->adolescents_female;
		$children_male 		= $worker->children_male;
		$children_female 	= $worker->children_female;
		$worker_total 		= $worker->worker_total;
		$amendment_worker 	= $worker->amendment_worker;
		
	}
	
	$content .='<tr>
	<td>'.$service_year.'</td>
	<td>'.$permanent_worker_women.'</td>
	<td>'.$permanent_adolescents_male.'</td>
	<td>'.$permanent_adolescents_female.'</td>
	<td>'.$permanent_children_male.'</td>
	<td>'.$permanent_children_female.'</td>
	<td>'.$contactual_worker_men.'</td>
	<td>'.$contactual_worker_women.'</td>
	<td>'.$contactual_adolescents_male.'</td>
	<td>'.$contactual_adolescents_female.'</td>
	<td>'.$contactual_children_male.'</td>
	<td>'.$contactual_children_female.'</td>
	
	
	</tr>
	<tfoot>
    <tr>
      <td colspan="12">Total Worker(s)  :-&nbsp;&nbsp;<strong>60</strong></td>
     
    </tr>
  </tfoot>
	</table>';
				$content .='</table>
												</td>
											</tr>
										</table>
										<table>
									 <tr><td>&nbsp;</td></tr>
									 <tr>					 				
										<td width="2%"  valign="top">3.</td>
										<td colspan="2" width="98%" valign="middle">Power Details</td>
									 </tr>
									 <tr>					 				
										<td width="2%"  valign="top">&nbsp;</td>
										<td width="49%" valign="top">(i). Type of power generating station</td>
										<td width="49%"><span class="data">: Other</span></td>
									 </tr>
									 <tr>					 				
										<td width="2%"  valign="top">&nbsp;</td>
										<td width="49%" valign="top">(ii). Power to be Installed</td>
										<td width="49%"><span class="data">:HP</span></td>
									 </tr>
									  <tr><td>&nbsp;</td></tr>
									<tr>					 				
										<td width="2%"  valign="top">4.</td>
										<td colspan="2" width="98%" valign="middle">Nature of Manufacturing process</td>
									 </tr>
									 <tr>					 				
										<td width="2%"  valign="top">&nbsp;</td>
										<td width="49%" valign="top">(i). Carried/to be carried on the factory</td>
										<td width="49%"><span class="data">:Plastic</span></td>
									 </tr> 
									 </table>
									</body>
								</html>';
								
		$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 20, 10, 0, 0);
		$mpdf->SetDisplayMode('fullpage');
		$mpdf->SetHTMLHeader('<div style="padding-top:50px; text-align: right; font-size:9px;">Page {PAGENO} of {nb}</div>');
		$mpdf->SetWatermarkText('DRAFT COPY');
		$mpdf->showWatermarkText = true;
		$mpdf->WriteHTML($content);
		$mpdf->Output('preview_varse_'.$plan_approval_no.'_'.time().'.pdf','D');
		
}
function fetch_old_data($application_id,$service_id,$factory_type_id,$reference_number){
	$query_year		= 	db_select('fa_worker_details', 'worker')->DISTINCT();
	$query_year		->	JOIN('fa_power_details', 'power','power.application_id = worker.application_id');
	$query_year		->	fields('worker',array('id','service_year','application_id','service_id','factory_type','application_id','application_reference_no','service_year','permanent_worker_men','permanent_worker_women','permanent_adolescents_male','permanent_adolescents_female','permanent_children_male','permanent_children_female','worker_total','change_date','worker_registration_status','previous_worker','is_amendment'));
	$query_year		->	fields('power', array('application_id','amended_power','amended_power_unit','is_amended','installed_power_hp','installed_power','power_unit'));
	$query_year		-> 	condition('worker.application_id', $application_id);
	$query_year		-> 	condition('worker.service_id', $service_id);
	$query_year		-> 	condition('worker.factory_type', $factory_type_id);
	$query_year		-> 	condition('worker.application_reference_no', $reference_number);
	$query_year		->	condition('power.is_amended', 1);
	$query_year		->	condition('worker.is_amendment', 1);
	$result_year	= 	$query_year->execute()->fetchAll();
	return $result_year;
	}
