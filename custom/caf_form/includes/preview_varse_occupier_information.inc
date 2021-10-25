		<?php
		global $base_path;
		require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';
		function preview_varse_occupier_information($serviceid, $factory_typeid,$applicationid,$reference_id){
		
		    global $base_root, $base_path;
			$service_id      	= encryption_decryption_fun('decrypt', $serviceid);
			$factory_type_id 	= encryption_decryption_fun('decrypt', $factory_typeid);
			$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
			$reference_id 		= encryption_decryption_fun('decrypt', $reference_id);
			//$link_date 			= encryption_decryption_fun('decrypt', $linkdate);
			//$flag_mapp 			= encryption_decryption_fun('decrypt', $flagmapp);
			
			$get_all_data 		= get_fa_cafa($application_id);
			//$reference_id		= $get_all_data['reference_number'];
			$value_factory_profile_type	= $get_fa_cafa['ownership_type'];
			$license_valid_upto			= $get_fa_cafa['license_valid_upto'];
			$is_year_calculation_tab	= $get_fa_cafa['is_year_calculation_tab'];
			$application_status			= $get_fa_cafa['application_status'];
			$period_for_application		= $get_fa_cafa['period_for_application'];
			$date_of_amenability       	= $get_fa_cafa['date_of_amenability'];
			$ownership_type 			= $get_all_data['factory_owershiptype'];
			
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
			
		
			if($ownership_type == 'pv' || $ownership_type == 'ltd'){
				 $ownership_type 	= 'Director';
			 }elseif($ownership_type == 'par_firm'  || $ownership_type=='llp'){
				 $ownership_type 	= 'Partner';
			 }elseif($ownership_type == 'pro_firm'){
				 $ownership_type 	= 'Proprietor';
			 }elseif($ownership_type=='cooperative'|| $ownership_type=='registered'){
				 $ownership_type	= 'Nominated Occupier';
			 }elseif($ownership_type == 'govt' || $ownership_type == 'psu' || $ownership_type == 'others' || $ownership_type=='localbody' ){
				 $ownership_type	= 'Nominated ';
			 }
	 
			$energy_no	= !empty($get_all_data['enargy_no'])?$get_all_data['enargy_no']:'n/a';
			$cin_no 	= !empty($get_all_data["cin_no"])?$get_all_data["cin_no"]:'n/a';
			
			$get_all_occupier = get_all_occupier_data($application_id,$service_id,$factory_type_id,$reference_id);
			
			
			
			$getdata_permanent_address 	= array('district_oprmntadr','subdivision_oprmntadr','areatype_oprmntadr','block_oprmntadr','panchayat_oprmntadr','policestation_oprmntadr','pincodeoprmntadr','state_oprmntadr','postoffice_oprmntadr');
			$permanent_address_part    	= get_parts_address('fa_occupier_details','sub-table',$get_all_occupier[0]->id,$getdata_permanent_address);
			if($get_all_occupier[0]->country_oprmntadr == 99) 
			 { 
			   $permanent_address        = get_full_address('fa_occupier_details','sub-table',$get_all_occupier[0]->id,$getdata_permanent_address);
			   $police_station_permanent = ($permanent_address_part['name_of_police_station'])? $permanent_address_part['name_of_police_station'] : '';
			 } else { 
			   $permanent_address        = $get_all_occupier[0]->street_name_oprmntadr.','.$get_all_occupier[0]->house_no_oprmntadr;
			   $police_station_permanent = ($get_all_occupier[0]->police_station_oprmntadr)? $get_all_occupier[0]->police_station_oprmntadr : '';
			 }  
			$address_line_permanent    	 = ($get_all_occupier[0]->addrline_oprmntadr)? $get_all_occupier[0]->addrline_oprmntadr : '';
			
			
			// OCCUPIER PRESENT ADDRESS
			$getdata_present_address 	= array('district_oprsntadr','subdivision_oprsntadr','areatype_oprsntadr','block_oprsntadr','panchayat_oprsntadr','policestation_oprsntadr','pincodeoprsntadr','state_oprsntadr','postoffice_oprsntadr');
			$present_address_part    	= get_parts_address('fa_occupier_details','sub-table',$get_all_occupier[0]->id,$getdata_present_address);
			if($get_all_occupier[0]->country_oprsntadr == 99) 
			  {	
				$present_address  		=  get_full_address('fa_occupier_details','sub-table',$get_all_occupier[0]->id,$getdata_present_address);
				$police_station_present = ($present_address_part['name_of_police_station'])? $present_address_part['name_of_police_station'] : '';
			  } else { 
				$present_address  		= $get_all_occupier[0]->street_name_oprsntadr.','.$get_all_occupier[0]->house_no_oprsntadr;
				$police_station_present = ($get_all_occupier[0]->police_station_oprsntadr)? $get_all_occupier[0]->police_station_oprsntadr : '';
			  }  
			$address_line_present 		= ($get_all_occupier[0]->addrline_oprsntadr)? $get_all_occupier[0]->addrline_oprsntadr : '';
			
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
							<h4>A. OCCUPIER INFORMATION</h4>
						</td>
					</tr>
					
					<tr><td colspan="3">';
				foreach($get_all_occupier as $details){
					
					$fieldpermanent_occupier =  array('district_oprmntadr','subdivision_oprmntadr','areatype_oprmntadr','block_oprmntadr','panchayat_oprmntadr','policestation_oprmntadr','pincodeoprmntadr','state_oprmntadr','postoffice_oprmntadr');
					
	
		$fieldpresent_occupier =  array('district_oprsntadr','subdivision_oprsntadr','areatype_oprsntadr','block_oprsntadr','panchayat_oprsntadr','policestation_oprsntadr','pincodeoprsntadr','state_oprsntadr','postoffice_oprsntadr');
		
			$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>E. Details of Occupier</td></h4></tr>
				 <tr><td>&nbsp;</td></tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Director / Partner / Proptietor / Nominated</span></td>
					<td width="49%"><span class="data">: '.$details->type_occupier.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Name in full </td>
					<td width="49%"><span class="data">: '.$details->name_occupier.' '.$details->occupier_name_middle.' '.$details->occupier_name_last.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Age </td>
					<td width="49%"><span class="data">: '.$details->age_occupier.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Father\'s/Husband\'s Name </td>
					<td width="49%"><span class="data">: '.$details->father_husband_name_occupier.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Telephone No </td>
					<td width="49%"><span class="data"><span class="data">: '.$details->occupier_telephone.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Mobile No </td>
					<td width="49%"><span class="data">: '.$details->occupier_mobile.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">E-mail ID </td>
					<td width="49%"><b>: '.$details->occupier_email_id.'</b></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Fax No </td>
					<td width="49%"><span class="data">: '.$details->occupier_fax_no.'</span></td>
				 </tr>
				 </table>';
				 
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>F i). Occupier Permanent Address</td></h4></tr>
				 <tr><td>&nbsp;</td></tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(i) Nationality</td>
					<td width="49%"><span class="data">: '.country_name($details->country_oprmntadr).'</span></td>
				</tr>
				 <tr>					 				
					<td width="2%"  valign="top">&nbsp;</td>
					<td width="49%" valign="top">(ii) Permanent Address </td>
					<td width="49%"><span class="data">: '.$address_line_permanent.', '.strip_tags($permanent_address).'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%"  valign="top">&nbsp;</td>
					<td width="49%" valign="top">(iii) P.S of Permanent Address </td>
					<td width="49%"><span class="data">: '.$police_station_permanent.'</span></td>
				 </tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(iv) Aadhar No. </td>
					<td width="49%"><span class="data">: '.$get_all_occupier[0]->aadhaar_oprmntadr.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(v) Passport No. </td>
					<td width="49%"><span class="data">: '.$get_all_occupier[0]->passport_oprmntadr.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top" style="padding-left: 15px;">(a) Date of Issue </td>
					<td width="49%"><span class="data">: '.$get_all_occupier[0]->passport_date_of_issue_oprmntadr.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top" style="padding-left: 15px;">(b) Date of Expiry </td>
					<td width="49%"><span class="data">: '.$get_all_occupier[0]->passport_date_of_expiry_oprmntadr.'</span></td>
				</tr>
				</table>';

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>F ii). Occupier Present Address</td></h4></tr>
				 <tr><td>&nbsp;</td></tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(i) Nationality</td>
					<td width="49%"><span class="data">: '.country_name($details->country_oprsntadr).'</span></td>
				</tr>
				<tr>					 				
					<td width="2%"  valign="top">&nbsp;</td>
					<td width="49%" valign="top">(ii) Present Address </td>
					<td width="49%"><span class="data">: '.$address_line_present.', '.strip_tags($present_address).'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%"  valign="top">&nbsp;</td>
					<td width="49%" valign="top">(iii) P.S of Present Address </td>
					<td width="49%"><span class="data">: '.$police_station_present.'</span></td>
				 </tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(iv) Aadhar No. </td>
					<td width="49%"><span class="data">: '.$get_all_occupier[0]->aadhaar_oprsntadr.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(v) Passport No. </td>
					<td width="49%"><span class="data">: '.$get_all_occupier[0]->passport_oprsntadr.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top" style="padding-left: 15px;">(a) Date of Issue </td>
					<td width="49%"><span class="data">: '.$get_all_occupier[0]->passport_date_of_issue_oprsntadr.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top" style="padding-left: 15px;">(b) Date of Expiry </td>
					<td width="49%"><span class="data">: '.$get_all_occupier[0]->passport_date_of_expiry_oprsntadr.'</span></td>
				</tr>
				</table>';
				}
				
	
	$content .='</td>
					</tr>
				</table>
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