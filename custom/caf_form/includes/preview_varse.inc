		<?php 
		global $base_path;
		require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';
		function preview_varse($serviceid, $factory_typeid,$applicationid,$linknumber){
			global $base_root;
			
			

			$service_id      	= encryption_decryption_fun('decrypt', $serviceid);
			$factory_type_id 	= encryption_decryption_fun('decrypt', $factory_typeid);
			$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
			$link_number 		= encryption_decryption_fun('decrypt', $linknumber);
			$link_date 			= encryption_decryption_fun('decrypt', $linkdate);
			$flag_mapp 			= encryption_decryption_fun('decrypt', $flagmapp);
			$get_all_data 		= get_fa_cafa($application_id);

		

			
			$is_backlog			= $get_all_data['is_backlog'];
			$reference_id		= $get_all_data['reference_number'];
			if($is_backlog == 1){
				$plan_approval_no 	= $get_all_data['backlog_plan_approval_no'];
				$plan_approval_date = date('dS M Y', strtotime($get_all_data['backlog_plan_approval_date']));
			}if($is_backlog != 1){
				$plan_approval_no 	= $get_all_data['factory_plan_approval_number'];
				$plan_approval_date = date('dS M Y', strtotime($get_all_data['modification_date']));
			}
			if($get_all_data['wbpcb_category_name']==1){$consent ='Red'; $wbpcb_reference_no = $get_all_data['wbpcb_reference_no'];$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));}
			if($get_all_data['wbpcb_category_name']==2){$consent ='Green'; $wbpcb_reference_no = $get_all_data['wbpcb_reference_no'];$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));}
			if($get_all_data['wbpcb_category_name']==3){$consent ='Orange'; $wbpcb_reference_no = $get_all_data['wbpcb_reference_no'];$wbpcb_ref_date = date('dS M Y', strtotime($get_all_data['wbpcb_ref_date']));}
			if($get_all_data['wbpcb_category_name']==4){$consent ='White'; $wbpcb_reference_no = 'n/a';$wbpcb_ref_date = 'n/a';}
			if($get_all_data['wbpcb_category_name']==5){$consent ='Exempted'; $wbpcb_reference_no = 'n/a';$wbpcb_ref_date = 'n/a';}
			
			//$previous_name			= fetch_previous_calid($application_id,$reference_id,$factory_type_id,$service_id);
			$previous_name				= $get_all_data['factory_previous_name'];
			//print_r($previous_name);die();
			$getdata_factory_address  	= array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
			$factory_address 		    = get_parts_address('fa_cafa','sub-table',$application_id,$getdata_factory_address);
			
			
			$getdata_headoffice_address = array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
			$headoffice_address 		= $get_all_data['addrline_off'].',
		<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_headoffice_address);
		
		
			$getdata_communication_address = array('district_comm','subdivision_comm','areatype_comm','block_comm','panchayat_comm','policestation_comm','pincodecomm','state_comm','postoffice_comm');
			$communication_address 		= $get_all_data['addrline_comm'].',
		<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_communication_address);
			

			$getdata_owner_address 		= array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
			
			$owner_address_details = !empty($get_all_data['addrline_premises'])?$get_all_data['addrline_premises'].',':'';
			$mouza_jl = !empty($get_all_data['mouza_name'])?'<br/>Mouza Name-'.$get_all_data['mouza_name'].',<br/>JL No-'.$get_all_data['jl_no']:'';
			$passport_details = !empty($get_all_data['occupier_passport_premises'])?'Passport No-'.$get_all_data['occupier_passport_premises'].',<br/>Passport Issue Date-'.$get_all_data['date_of_issue_premises'].',<br/>Passport Expiry date-'.$get_all_data['date_of_expiry_premises']:'';
			
			$owner_address_details.= !empty($get_all_data['country_premises'])?country_name($get_all_data['country_premises']):'';
			$owner_address 				=	$owner_address_details.'<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_owner_address).'&nbsp;'.$mouza_jl.'&nbsp;'.$passport_details;	
				
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
   		}if($get_all_data['factory_owershiptype']=="llp"){
   				$ownership_type = "Limited Liability Partnership";
   		}if($get_all_data['factory_owershiptype']=="cooperative"){
   				$ownership_type = "Co-operative";
   		}if($get_all_data['factory_owershiptype']=="registered"){
   				$ownership_type = "Registered Society under Society Register";
   		}if($get_all_data['factory_owershiptype']=="localbody"){
   				$ownership_type = "Local Body";
   		}if($get_all_data['factory_owershiptype']=="others"){
   				$ownership_type = "Others";
   		}
		
		$energy_no = !empty($get_all_data['enargy_no'])?$get_all_data['enargy_no']:'n/a';
		$cin_no = !empty($get_all_data["cin_no"])?$get_all_data["cin_no"]:'n/a';
		if(!empty($get_all_data['trade_license_no'])){ $trade_no = $get_all_data['trade_license_no']; }else{$trade_no =  'Nil';}
		
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
							<h4>A. FACTORY INFORMATION</h4>
						</td>
					</tr>
					<tr>
						<td colspan="3">&nbsp;</td>
					</tr>
					<tr>
						<td width="2%"  valign="top">1. </td>
						<td width="49%" valign="top">(i). Full Name of the Factory</td>
						<td width="49%"><span class="data">: '.$get_all_data['factory_name'].'</span></td>
					</tr>
					<tr>
						<td width="2%"  valign="top">&nbsp;</td>
						<td width="49%" valign="top">(ii). Ownership Type</td>
						<td width="49%"><span class="data">: '.$ownership_type.'</span></td>
					</tr>
					<tr>
						<td width="2%"  valign="top">&nbsp;</td>
						<td width="49%" valign="top">(iii). GSTIN Number</td>
						<td width="49%"><span class="data">: '.$get_all_data['gstin_no'].'</span></td>
					</tr>
					<tr>
						<td width="2%"  valign="top">&nbsp;</td>
						<td width="49%" valign="top">(iv). Udyog Aadhaar No</td>
						<td width="49%"><span class="data">: '.$get_all_data['udyog_aadhaar'].'</span></td>
					</tr>
					<tr>
						<td width="2%"  valign="top">&nbsp;</td>
						<td width="49%" valign="top">(iv). Energy Meter No</td>
						<td width="49%"><span class="data">: '.$energy_no.'</span></td>
					</tr>
					<tr>
						<td width="2%"  valign="top">&nbsp;</td>
						<td width="49%" valign="top">(v). CIN No</td>
						<td width="49%"><span class="data">: '.$cin_no.'</span></td>
					</tr>
					<tr>
						<td width="2%"  valign="top">&nbsp;</td>
						<td width="49%" valign="top">(vi). Trade license No</td>
						<td width="49%"><span class="data">: '.$trade_no.'</span></td>
					</tr>
					';
					
			if(!empty($previous_name))	{		 
			$content .= ' 
					<tr>
						<td colspan="3">&nbsp;</td>
					</tr>
					<tr>
						<td width="100%" valign="top" colspan="3">(vi)Previous Name of the Factory (if different from the present name) </td>
					</tr>
						<tr><td width="2%"  valign="top"></td>
									<td width="49%" valign="top" style="padding-left: 15px;"> Previous Name</td>
									<td width="49%">
										<span class="data">: '.$previous_name.'</span>
									</td>
								</tr>';
				}
			
			$content .= '
					<tr>
						<td colspan="3">&nbsp;</td>
					</tr>
					<tr>
						<td width="49%" valign="top" colspan="3">2. (a) Situation of the Factory</td>
					</tr>
					<tr>
						<td colspan="3">&nbsp;</td>
					</tr>
					<tr>
						<td width="2%"  valign="top"></td>
						<td>Address</td>
						<td>
							<span class="data">: '.$get_all_data['addrline'].'</span>
						</td>
					</tr>
					<tr>
						<td width="2%"  valign="top"></td>
						<td width="49%" valign="top" style="padding-left: 15px;">Pin Code</td>
						<td width="49%">
							<span class="data">: '.$factory_address['pincode'].'</span>
						</td>
					</tr>
					<tr>
						<td width="2%"  valign="top"></td>
						<td width="49%" valign="top" style="padding-left: 15px;"> Post Office</td>
						<td width="49%">
							<span class="data">: '.$factory_address['po_name'].'</span>
						</td>
					</tr>
					<tr>
						<td width="2%"  valign="top"></td>
						<td width="49%" valign="top" style="padding-left: 15px;"> Sub Divisional Headquarter </td>
						<td width="25%">
							<span class="data">: '.$factory_address['sub_div_name'].'</span>
						</td>
					</tr>
					<tr>
						<td width="2%"  valign="top"></td>
						<td width="49%" style="padding-left: 15px;">District </td>
						<td width="49%">
							<span class="data">: '.$factory_address['district_name'].'</span>
						</td>
					</tr>
					<tr>
						<td width="2%"  valign="top"></td>
						<td width="49%" valign="top" style="padding-left: 15px;"> Police Station </td>
						<td width="49%">
							<span class="data">: '.$factory_address['name_of_police_station'].'</span>
						</td>
						<tr>
							<tr>
								<td width="2%"  valign="top"></td>
								<td width="49%" valign="top" style="padding-left: 15px;">Nearest Landmark</td>
								<td width="49%">
									<span class="data">: '.$get_all_data['factory_location'].'</span>
								</td>
								<tr>
									<tr>
										<td colspan="3">&nbsp;</td>
									</tr>
									<tr>
										<td width="2%"  valign="top"></td>
										<td width="49%" valign="top">(b) Address of the Registered Office/Head Office </td>
										<td width="49%">
											<span class="data">: '.$headoffice_address.'</span>
										</td>
									</tr>
									<tr>
										<td width="2%"  valign="top">&nbsp;</td>
										<td width="49%" valign="top">Telephone No. </td>
										<td width="49%">
											<span class="data">: '.$get_all_data['comm_telephone'].'</span>
										</td>
									</tr>
									<tr>
										<td width="2%"  valign="top">&nbsp;</td>
										<td width="49%" valign="top">Mobile No. </td>
										<td width="49%">
											<span class="data">: '.$get_all_data['comm_mobile'].'</span>
										</td>
									</tr>
									<tr>
										<td width="2%"  valign="top">&nbsp;</td>
										<td width="49%" valign="top">Alternate Mobile No. </td>
										<td width="49%">
											<span class="data">: '.$get_all_data['comm_alt_mobile'].'</span>
										</td>
									</tr>
									<tr>
										<td width="2%"  valign="top">&nbsp;</td>
										<td width="49%" valign="top">Fax No. </td>
										<td width="49%">
											<span class="data">: '.$get_all_data['comm_fax'].'</span>
										</td>
									</tr>
									<tr>
										<td width="2%"  valign="top">&nbsp;</td>
										<td width="49%" valign="top">E-mail ID </td>
										<td width="49%">
											<b>: '.$get_all_data['comm_email'].'</b>
										</td>
									</tr>
									<tr>
										<td colspan="3">&nbsp;</td>
									</tr>
									<tr>
										<td width="2%"  valign="top">3.</td>
										<td width="49%" valign="top">PAN Number of the factory under the Income Tax Act, 1961 </td>
										<td width="49%">
											<span class="data">: '.$get_all_data['factory_pan'].'</span>
										</td>
									</tr>
									<tr>
										<td colspan="3">&nbsp;</td>
									</tr>
									<tr>
										<td width="2%"  valign="top">4.</td>
										<td width="49%" valign="top"> Address to which communications relating to the factory may be sent </td>
										<td width="49%">
											<span class="data">: '.$communication_address.'</span>
										</td>
									</tr>
									
									
									<tr>
										<td colspan="3">&nbsp;</td>
									</tr>
									<tr>
										<td width="2%"  valign="top">5.</td>
										<td colspan="2" width="98%" valign="middle" colspan="3">Details of owner of the premises occupied as a factory - </td>
									</tr>
									<tr>
										<td colspan="3">
											<table width="100%" border="0" cellspacing="0" cellpadding="0">';
					
				 $content .='
												<tr>
													<td colspan="3">&nbsp;</td>
												</tr>
												<tr>
													<td width="2%"  valign="top"></td>
													<td width="49%" valign="top">Name of the owner </td>
													<td width="49%">
														<span class="data">: '.$get_all_data['owner_name'].'&nbsp;'.$get_all_data['owner_mname'].'&nbsp;'.$get_all_data['owner_lname'].'</span>
													</td>
													<tr>
														<tr>
															<td colspan="3">&nbsp;</td>
														</tr>
														<tr>
															<td width="2%"  valign="top"></td>
															<td width="49%" valign="top"> Address of owner of the premises occupied as a factory </td>
															<td width="49%">
																<span class="data">: '.$owner_address.'</span>
															</td>
														</tr>
													</table>
												</td>
											</tr>
										</table>';
							$content .='<table>
									 <tr><td>&nbsp;</td></tr>
									 <tr>					 				
										<td width="2%"  valign="top">6.</td>
										<td colspan="2" width="98%" valign="middle">Factory Identification according to wbpcb</td>
									 </tr>
									 <tr>					 				
										<td width="2%"  valign="top">&nbsp;</td>
										<td width="49%" valign="top">(i). Categories of wbpcb</td>
										<td width="49%"><span class="data">: '.$consent.'</span></td>
									 </tr>
									 <tr>					 				
										<td width="2%"  valign="top">&nbsp;</td>
										<td width="49%" valign="top">(ii). Reference number of approval of arrangments</td>
										<td width="49%"><span class="data">: '.$wbpcb_reference_no.'</span></td>
									 </tr>
									 <tr>					 				
										<td width="2%"  valign="top">&nbsp;</td>
										<td width="49%" valign="top">(iii). Date of approval of arrangments</td>
										<td width="49%"><span class="data">: '.$wbpcb_ref_date.'</span></td>
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