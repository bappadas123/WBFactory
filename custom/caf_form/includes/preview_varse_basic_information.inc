		<?php
		global $base_path;
		require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';
		function preview_varse_basic_information($serviceid, $factory_typeid,$applicationid,$linknumber){
		
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
			
			
			$getdata_factory_address  	= array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
			$factory_address 		    = get_parts_address('fa_cafa','sub-table',$application_id,$getdata_factory_address);
			$getdata_headoffice_address = array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
			$headoffice_address 		= $get_all_data['addrline_off'].',
		<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_headoffice_address);
			$getdata_owner_address 		= array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
			$owner_address_details = !empty($get_all_data['addrline_premises'])?$get_all_data['addrline_premises'].',':'';
			$owner_address_details.= $get_all_data['owner_country_address'].',<br/>'.country_name($get_all_data['owner_country']);
			$owner_address 				=	$owner_address_details.'<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_owner_address);
		
			$worker_details 			= get_worker_details_service($service_id,$factory_type_id,$application_id,$reference_id);
			$power_generating_station 	= get_power_generating_station($application_id,$reference_id,$factory_type_id,$service_id);
			foreach($power_generating_station as $power){
				$power_details = $power->installed_power.'('.$power->power_unit.')';
				$power_station = $power->type_power_station;
			}
			$nature_details = get_manufacturing($application_id,$service_id,$factory_type_id,$reference_id);
			foreach($nature_details as $nature){
				$nature_work = $nature->nature_manufacturing;
			}
		
		
		$content = '
		<style type="text/css">
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
								</tr>'
							;
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
						<td width="49%" valign="top" colspan="3">2. Worker Details</td>
					</tr>
					<tr>
						<td colspan="3">';
					
				 $content .='<table width="100%"  border="1" cellspacing="0" cellpadding="0" class="custom-table-view-dashboard renewal-table">
							
							<tr>
							<th   colspan="6">Permanent</th>
							<th   colspan="6">Contactual</th>
							
							</tr>
							<tr>
								<th rowspan="2">Men</th>
								<th rowspan="2">Women</th>  
								<th colspan="2">Adolescents</th>
								<th colspan="2">Children </th>
        
   						
								<th rowspan="2">Men</th>
								<th rowspan="2">Women</th>  
								<th colspan="2">Adolescents</th>
								<th colspan="2">Children</th>
        
   						 </tr>
						 <tr>
						 <th >Men</th>
						<th >Women</th>  
						<th >Men</th>
						<th >Women</th>  
						 <th >Men</th>
						<th >Women</th>  
						<th >Men</th>
						<th >Women</th>  
							
						 </tr>
						 '
						 ;
		
	
	foreach($worker_details as $worker){
		$permanent_worker_men 			= $worker->permanent_worker_men;
		$permanent_worker_women 		= $worker->permanent_worker_women;
		$permanent_adolescents_male 	= $worker->permanent_adolescents_male;
		$permanent_adolescents_female 	= $worker->permanent_adolescents_female;
		$permanent_children_male 		= $worker->permanent_children_male;
		$permanent_children_female 		= $worker->permanent_children_female;
		$contactual_worker_men 			= $worker->contactual_worker_men;
		$contactual_worker_women 		= $worker->contactual_worker_women;
		$contactual_adolescents_male 	= $worker->contactual_adolescents_male;
		$contactual_adolescents_female 	= $worker->contactual_adolescents_female;
		$contactual_children_male 		= $worker->contactual_children_male;
		$contactual_children_female 	= $worker->contactual_children_female;
		$worker_total 					= $worker->worker_total;
		
	}
	
	$content .='<tr>
	<td>'.$permanent_worker_men.'</td>
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
      <td colspan="12">Total Worker(s)  :-&nbsp;&nbsp;<strong>'.$worker_total.'</strong></td>
     
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
										<td width="49%"><span class="data">: '.$power_station.'</span></td>
									 </tr>
									 <tr>					 				
										<td width="2%"  valign="top">&nbsp;</td>
										<td width="49%" valign="top">(ii). Power to be Installed</td>
										<td width="49%"><span class="data">: '.$power_details.'</span></td>
									 </tr>
									  <tr><td>&nbsp;</td></tr>
									<tr>					 				
										<td width="2%"  valign="top">4.</td>
										<td colspan="2" width="98%" valign="middle">Nature of Manufacturing process</td>
									 </tr>
									 <tr>					 				
										<td width="2%"  valign="top">&nbsp;</td>
										<td width="49%" valign="top">(i). Carried/to be carried on the factory</td>
										<td width="49%"><span class="data">: '.$nature_work.'</span></td>
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