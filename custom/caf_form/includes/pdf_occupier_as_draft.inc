<?php
global $base_root, $base_path, $user;
require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';

function pdf_occupier_as_draft($applicationid='' ,$referenceid ='' ,$serviceid ='' ,$factorytype =''){

	$application_id 	 		= encryption_decryption_fun('decrypt', $applicationid);
	$reference_id 		 		= encryption_decryption_fun('decrypt', $referenceid);
	$service_id 		 		= encryption_decryption_fun('decrypt', $serviceid);
	$factory_type_id 	 		= encryption_decryption_fun('decrypt', $factorytype);

	if(empty($reference_id)) {$reference_id = 0;}
	$get_all_data 				= get_application_withid($application_id);
	$get_fa_occupier    		= get_all_occupier_data($application_id,$service_id,$factory_type_id,$reference_id); //echo "<pre>";print_r($get_fa_occupier);exit;

	// OCCUPIER PERMANENT ADDRESS
	$getdata_permanent_address 	= array('district_oprmntadr','subdivision_oprmntadr','areatype_oprmntadr','block_oprmntadr','panchayat_oprmntadr','policestation_oprmntadr','pincodeoprmntadr','state_oprmntadr','postoffice_oprmntadr');
	$permanent_address_part    	= get_parts_address('fa_occupier_details','sub-table',$get_fa_occupier[0]->id,$getdata_permanent_address);
	if($get_fa_occupier[0]->country_oprmntadr == 99) 
	 { 
	   $permanent_address        = get_full_address('fa_occupier_details','sub-table',$get_fa_occupier[0]->id,$getdata_permanent_address);
	   $police_station_permanent = ($permanent_address_part['name_of_police_station'])? $permanent_address_part['name_of_police_station'] : '';
	 } else { 
	   $permanent_address        = $get_fa_occupier[0]->street_name_oprmntadr.','.$get_fa_occupier[0]->house_no_oprmntadr;
	   $police_station_permanent = ($get_fa_occupier[0]->police_station_oprmntadr)? $get_fa_occupier[0]->police_station_oprmntadr : '';
	 }  
	$address_line_permanent    	 = ($get_fa_occupier[0]->addrline_oprmntadr)? $get_fa_occupier[0]->addrline_oprmntadr : '';
	
	
	// OCCUPIER PRESENT ADDRESS
	$getdata_present_address 	= array('district_oprsntadr','subdivision_oprsntadr','areatype_oprsntadr','block_oprsntadr','panchayat_oprsntadr','policestation_oprsntadr','pincodeoprsntadr','state_oprsntadr','postoffice_oprsntadr');
	$present_address_part    	= get_parts_address('fa_occupier_details','sub-table',$get_fa_occupier[0]->id,$getdata_present_address);
	if($get_fa_occupier[0]->country_oprsntadr == 99) 
	  {	
	    $present_address  		=  get_full_address('fa_occupier_details','sub-table',$get_fa_occupier[0]->id,$getdata_present_address);
	  	$police_station_present = ($present_address_part['name_of_police_station'])? $present_address_part['name_of_police_station'] : '';
	  } else { 
	    $present_address  		= $get_fa_occupier[0]->street_name_oprsntadr.','.$get_fa_occupier[0]->house_no_oprsntadr;
	  	$police_station_present = ($get_fa_occupier[0]->police_station_oprsntadr)? $get_fa_occupier[0]->police_station_oprsntadr : '';
	  }  
	$address_line_present 		= ($get_fa_occupier[0]->addrline_oprsntadr)? $get_fa_occupier[0]->addrline_oprsntadr : '';
	
	$occupiername           	= $get_fa_occupier[0]->name_occupier.' '.$get_fa_occupier[0]->occupier_name_middle.' '.$get_fa_occupier[0]->occupier_name_last;
	$occupier_name          	= ($occupiername)? $occupiername : '';
	$occupier_mobile        	= ($get_fa_occupier[0]->occupier_mobile)? $get_fa_occupier[0]->occupier_mobile	 : '';
	$occupier_email_id      	= ($get_fa_occupier[0]->occupier_email_id)? $get_fa_occupier[0]->occupier_email_id	 : '';
	$occupier_age     			= ($get_fa_occupier[0]->age_occupier)? $get_fa_occupier[0]->age_occupier	 : '';
	$occupier_gurdian_name  	= ($get_fa_occupier[0]->father_husband_name_occupier)? $get_fa_occupier[0]->father_husband_name_occupier	 : '';
	$occupier_fax_no        	= ($get_fa_occupier[0]->occupier_fax_no)? $get_fa_occupier[0]->occupier_fax_no	 : '';
	$occupier_telephone     	= ($get_fa_occupier[0]->occupier_telephone)? $get_fa_occupier[0]->occupier_telephone	 : '';
	$occupier_type          	= ($get_fa_occupier[0]->type_occupier)? $get_fa_occupier[0]->type_occupier	 : ''; 

	$content = '<style type="text/css">
					table, td, th {
							font-size:12px;
							font-family:Times New Roman;
							height:15px;
							color:#000;
							margin-top:10px;
							background:#fff;
					}
					th {
						background-color: #008BD1;
						color: white;
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
					.data{ text-transform: uppercase;font-weight:bold;}
					
			</style>';
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">				
					<tr><td colspan="3"></td></tr>				
					<tr><td colspan="3" align="center" style="font-size:20px;text-transform:uppercase;"><h2> COMMON APPLICATION FORM - OCCUPIER INFORMATION</h2></td></tr>
					<tr><td colspan="3"></td></tr>
					<tr><td colspan="3"></td></tr></table>';

		$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>H. Details of Occupier</td></h4></tr>
				 <tr><td>&nbsp;</td></tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Director / Partner / Proptietor / Nominated</span></td>
					<td width="49%"><span class="data">: '.$occupier_type.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Name in full </td>
					<td width="49%"><span class="data">: '.$occupier_name.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Age </td>
					<td width="49%"><span class="data">: '.$occupier_age.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Father\'s/Husband\'s Name </td>
					<td width="49%"><span class="data">: '.$occupier_gurdian_name.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Telephone No </td>
					<td width="49%"><span class="data"><span class="data">: '.$occupier_telephone.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Mobile No </td>
					<td width="49%"><span class="data">: '.$occupier_mobile.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">E-mail ID </td>
					<td width="49%"><b>: '.$occupier_email_id.'</b></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Fax No </td>
					<td width="49%"><span class="data">: '.$occupier_fax_no.'</span></td>
				 </tr>
				 </table>';
				 
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>I i). Occupier Permanent Address</td></h4></tr>
				 <tr><td>&nbsp;</td></tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(i) Nationality</td>
					<td width="49%"><span class="data">: '.country_name($get_fa_occupier[0]->country_oprmntadr).'</span></td>
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
					<td width="49%"><span class="data">: '.$get_fa_occupier[0]->aadhaar_oprmntadr.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(v) Passport No. </td>
					<td width="49%"><span class="data">: '.$get_fa_occupier[0]->passport_oprmntadr.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top" style="padding-left: 15px;">(a) Date of Issue </td>
					<td width="49%"><span class="data">: '.$get_fa_occupier[0]->passport_date_of_issue_oprmntadr.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top" style="padding-left: 15px;">(b) Date of Expiry </td>
					<td width="49%"><span class="data">: '.$get_fa_occupier[0]->passport_date_of_expiry_oprmntadr.'</span></td>
				</tr>
				</table>';

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>I ii). Occupier Present Address</td></h4></tr>
				 <tr><td>&nbsp;</td></tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(i) Nationality</td>
					<td width="49%"><span class="data">: '.country_name($get_fa_occupier[0]->country_oprsntadr).'</span></td>
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
					<td width="49%"><span class="data">: '.$get_fa_occupier[0]->aadhaar_oprsntadr.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(v) Passport No. </td>
					<td width="49%"><span class="data">: '.$get_fa_occupier[0]->passport_oprsntadr.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top" style="padding-left: 15px;">(a) Date of Issue </td>
					<td width="49%"><span class="data">: '.$get_fa_occupier[0]->passport_date_of_issue_oprsntadr.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top" style="padding-left: 15px;">(b) Date of Expiry </td>
					<td width="49%"><span class="data">: '.$get_fa_occupier[0]->passport_date_of_expiry_oprsntadr.'</span></td>
				</tr>
				</table>';
	
	//echo $content; die;	
	$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 20, 10, 0, 0);
	$mpdf->SetDisplayMode('fullpage');
	$mpdf->SetHTMLHeader('
	<div style="padding-top:50px; text-align: right; font-size:9px;">
		Page {PAGENO} of {nb}
	</div>');
	$mpdf->SetWatermarkText('DRAFT COPY');
	$mpdf->showWatermarkText = true;
	$mpdf->WriteHTML($content);
	$mpdf->Output('Occupier-Information-'.time().'.pdf', 'D');
}
?>