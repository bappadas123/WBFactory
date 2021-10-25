<?php
global $base_root, $base_path, $user;
require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';

function pdf_owner_as_draft($applicationid='' ,$referenceid ='' ,$serviceid ='' ,$factorytype =''){

	$application_id 	 		= encryption_decryption_fun('decrypt', $applicationid);
	$reference_id 		 		= encryption_decryption_fun('decrypt', $referenceid);
	$service_id 		 		= encryption_decryption_fun('decrypt', $serviceid);
	$factory_type_id 	 		= encryption_decryption_fun('decrypt', $factorytype);

	if(empty($reference_id)) {$reference_id = 0;}
	$get_all_data 				= get_all_owner_data($application_id,$service_id,$factory_type_id,$reference_id);
	
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
					<tr><td colspan="3" align="center" style="font-size:20px;text-transform:uppercase;"><h2> COMMON APPLICATION FORM - GENERAL INFORMATION</h2></td></tr>
					<tr><td colspan="3"></td></tr>
					<tr><td colspan="3"></td></tr></table>';
				 
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>G. Details of owner/land lord/lessor of the premises occupied as a factory</td></h4></tr>
				 <tr><td>&nbsp;</td></tr>';
				 
				for($i=0; $i < count($get_all_data); $i++)
				{ 
					// PREMISES OWNER DETAILS
					$getdata_premises_address 	    = array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
					$premises_address  			    = get_parts_address('fa_owner_details','sub-table',$get_all_data[$i]->id,$getdata_premises_address);
				
					$address_line_premises 		    = ($get_all_data[$i]->addrline_premises)? $get_all_data[$i]->addrline_premises : '';
					$post_office_premises     	= ($premises_address['po_name'])? $premises_address['po_name'] : '';
					$pin_code_premises       	= ($premises_address['pincodepremises'])? $premises_address['pincodepremises'] : ''; 
					$sub_division_premises   	= ($premises_address['sub_div_name'])? $premises_address['sub_div_name'] : ''; 
					$district_premises        	= ($premises_address['district_name'])? $premises_address['district_name'] : ''; 
					$police_station_premises 	= ($premises_address['name_of_police_station'])? $premises_address['name_of_police_station'] : ''; 
					$aadhaar_premises 		    = ($get_all_data[$i]->aadhaar_premises)? $get_all_data[$i]->aadhaar_premises : '';
					$passport_premises 		    = ($get_all_data[$i]->passport_premises)? $get_all_data[$i]->passport_premises : '';
					$passport_date_of_issue_premises  = ($get_all_data[$i]->passport_date_of_issue_premises)? $get_all_data[$i]->passport_date_of_issue_premises : '';
					$passport_date_of_expiry_premises = ($get_all_data[$i]->passport_date_of_expiry_premises)? $get_all_data[$i]->passport_date_of_expiry_premises : '';

	$content .= '<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(i) Name in full </td>
					<td width="49%"><span class="data">: '.$get_all_data[$i]->owner_name.' '.$get_all_data[$i]->owner_mname.' '.$get_all_data[$i]->owner_lname.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(ii) Nationality</td>
					<td width="49%"><span class="data">: '.country_name($get_all_data[$i]->country_premises).'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(iii) Address</td>
					<td width="49%"><span class="data">: '.$address_line_premises.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(iv) Post Office</td>
					<td width="49%"><span class="data">: '.$post_office_premises.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(v) Pin Code</td>
					<td width="49%"><span class="data">: '.$pin_code_premises.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(vi) Sub Divisional Headquarter </td>
					<td width="25%"><span class="data">: '.$sub_division_premises.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(vii) District </td>
					<td width="49%"><span class="data">: '.$district_premises.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(viii) Police Station </td>
					<td width="49%"><span class="data">: '.$police_station_premises.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(x) Passport No. </td>
					<td width="49%"><span class="data">: '.$passport_premises.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top" style="padding-left: 15px;">(a) Date of Issue </td>
					<td width="49%"><span class="data">: '.$passport_date_of_issue_premises.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top" style="padding-left: 15px;">(b) Date of Expiry </td>
					<td width="49%"><span class="data">: '.$passport_date_of_expiry_premises.'</span></td>
				</tr>';
	$content .= '<tr><td colspan="3" align="center">.................................................................................................................................................................................................................</td></tr>					
				<tr><td colspan="3"></td>&nbsp;</tr>';
	}			
	
	$content .= '</table><table width="100%" border="0" cellspacing="0" cellpadding="0">				
					<tr><td colspan="3"></td>&nbsp;</tr>
					<tr><td colspan="3" align="center"><h3 style="border-bottom:1px solid;">&nbsp;</h3></td></tr>
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
	$mpdf->Output('Owner-Information-'.time().'.pdf', 'D');
}
?>