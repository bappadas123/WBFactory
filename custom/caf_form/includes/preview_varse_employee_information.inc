		<?php
		global $base_path;
		require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';
		function preview_varse_employee_information($serviceid, $factory_typeid,$applicationid,$linknumber){
		
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
			
			$is_backlog					= $get_all_data['is_backlog'];
			
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
			
			$get_all_manager = get_all_manager_data($application_id,$service_id,$factory_type_id,$reference_id);
			$get_all_director = get_director_details_service($application_id,$service_id,$factory_type_id,$reference_id);
		
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
		$sl=1;
	foreach($get_all_manager as $manager_details){
			if($manager_details->relationship_manager == '1'){
				$relationship = 'D/O';
			}if($manager_details->relationship_manager == '2'){
				$relationship = 'S/O';
			}if($manager_details->relationship_manager == '3'){
				$relationship = 'W/O';
			}
		
	$fieldArr_manager		=  array('district_manager','sub_division_manager','area_type_manager','block_mun_cor_sez_not_manager','grm_ward_sector_not_manager','police_station_manager','pincode_manager','state_manager','post_office_manager');
	$address_of_manager		= $manager_details->adress_line1_manager.'<br>'.get_full_address('fa_manager_details','sub-table',$manager_details->id,$fieldArr_manager);
	$manager_details_view	= $manager_details->name_manager.'<br/>' .$relationship.'-'.$manager_details->father_husband_name_manager.'<br/>Age:-'.$manager_details->age_manager;
	
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>'.$sl.' Manager Information</td></h4></tr>
				 <tr><td>&nbsp;</td></tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Type</span></td>
					<td width="49%"><span class="data">: Manager</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Name in full </td>
					<td width="49%"><span class="data">: '.$manager_details->name_manager.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Age </td>
					<td width="49%"><span class="data">: '.$manager_details->age_manager.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Father\'s/Husband\'s Name </td>
					<td width="49%"><span class="data">: '.$relationship.'-'.$manager_details->father_husband_name_manager.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Telephone No </td>
					<td width="49%"><span class="data"><span class="data">: '.$manager_details->manager_telephone.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Mobile No </td>
					<td width="49%"><span class="data">: '.$manager_details->manager_phone.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">E-mail ID </td>
					<td width="49%"><b>: '.$manager_details->manager_email.'</b></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Fax No </td>
					<td width="49%"><span class="data">: '.$manager_details->manager_fax.'</span></td>
				 </tr>
				 </table>';
				 
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>Manager Address Details</td></h4></tr>
				 <tr><td>&nbsp;</td></tr>
				 <tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(i) Details </td>
					<td width="49%"><span class="data">:'.$address_of_manager.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(ii) Other Details </td>
					<td width="49%"><span class="data">: .'.$manager_details->manager_present_address.'<br>'.'Telephone: '.$manager_details->manager_telephone.'<br>'.'Mobile: '.$manager_details->manager_phone.'<br>'.'FAX: '.$manager_details->manager_fax.'<br>'.'Email: '.$manager_details->manager_email.'</span></td>
				</tr>
			</table>';

}
	$sr=1;
	foreach($get_all_director as $details){
			if(!empty($details->din_director)){
				$din = 'DIN:-'.$details->din_director;
				}	
			$type =$details->type_director;
			if($type=='ltd' || $type=='pv'){$director_type = 'Director';}
			if($type == 'par_firm'){$director_type 	= 'Partner';}
			if($type == 'pro_firm'){$director_type 	= 'Proprietor';}
			if($type == 'govt' || $type == 'psu' || $type == 'others'){$director_type 	= 'Nominated Occupier';}
			if(!empty($details->age_director)){
				$age = 'Age- '.$details->age_director;
				}
			$is_occupier =$details->is_occupier;
			
			$relation =$details->relationship_director;
			 if($relation == 1){
				$relationship = 'D/O';
			}
			 if($relation == 2){
				$relationship = 'S/O';
			}
			 if($relation == 3){
				$relationship = 'W/O';
			}
			if($is_occupier == 1){
				$occupier = '<br/>(Occupier)';
			}else{$occupier = '';}
			
		
			$fieldArr_director	=  array('district_director','sub_division_director','area_type_director','block_mun_cor_sez_not_director','grm_ward_sector_not_director','police_station_director','pincode_director','state_director','post_office_director');
			$address_of_director =	$details->adress_line1_director.'<br>'.get_full_address('fa_director_details','sub-table',$details->id,$fieldArr_director);
	
				
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>'.$sr.' Direcror Information</td></h4></tr>
				 <tr><td>&nbsp;</td></tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Director / Partner / Proptietor / Nominated</span></td>
					<td width="49%"><span class="data">: '.$director_type.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Name in full </td>
					<td width="49%"><span class="data">: '.$details->name_director.'<br>'.$din.'<br>'.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Age </td>
					<td width="49%"><span class="data">: '.$age.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Father\'s/Husband\'s Name </td>
					<td width="49%"><span class="data">: '.$relationship.'-'.$details->father_husband_name_director.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Telephone No </td>
					<td width="49%"><span class="data"><span class="data">: '.$details->director_telephone.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Mobile No </td>
					<td width="49%"><span class="data">: '.$details->director_mobile.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">E-mail ID </td>
					<td width="49%"><b>: '.$details->director_email_id.'</b></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Fax No </td>
					<td width="49%"><span class="data">: '.$details->director_fax_no.'</span></td>
				 </tr>
				 </table>';
				 
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>Manager Address Details</td></h4></tr>
				 <tr><td>&nbsp;</td></tr>
				 <tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(i) Details </td>
					<td width="49%"><span class="data">:'.$address_of_director.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(ii) Other Details </td>
					<td width="49%"><span class="data">: .'.$details->addrline_oprsntadr.'<br>'.'Telephone: '.$details->director_telephone.'<br>'.'Mobile: '.$details->director_mobile.'<br>'.'FAX: '.$details->director_fax_no.'<br>'.'Email: '.$details->director_email_id.'</span></td>
				</tr>
			</table>';
			$sr++;
		}
	$content .='
			</body>
		</html>';
					//return pdf_using_mpdf_api($content,'licecne_file'._.time());	
						$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 20, 10, 0, 0);
						$mpdf->SetDisplayMode('fullpage');
						$mpdf->SetHTMLHeader('<div style="padding-top:50px; text-align: right; font-size:9px;">Page {PAGENO} of {nb}</div>');
						$mpdf->SetWatermarkText('DRAFT COPY');
						$mpdf->showWatermarkText = true;
						$mpdf->WriteHTML($content);
						$mpdf->Output('preview_varse_'.$plan_approval_no.'_'.time().'.pdf','D');
			
		
		}