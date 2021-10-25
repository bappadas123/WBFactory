<?php
function licence_registration_download_file($id) {
	global $base_root, $base_path, $user; 	
	
	if($factorytype_id==1){ $type='2M(i)';}
	if($factorytype_id==2){ $type='2M(ii)';}
	if($factorytype_id==3){ $type='Sectin 85';}
	
	$e_id = encryption_decryption_fun('decrypt',$id);
		
	$all_data = get_licence_register($e_id);
	//print_r($all_data);die;
	foreach($all_data as $data){
	$license_no 				= $data->licence_no;
	$reg_no 					= $data->registration_no;
	$registration_date 			= $data->amenability_date;
	$classification_no 			= $data->classification_no;
	$factory_name_address		= $data->factory_name_address;
	$ocupier_name				= $data->occupier_name;
	$change						= $data->change_name;
	$ocupier_transfer			= $data->occupier_transfer;
	}
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
					#tabular {
						border-collapse: collapse;
						
						}
					#tabular td {
						border: 1px solid;
						padding: 2px;
					}
					#tabular tr {
						padding-top: 12px;
						padding-bottom: 12px;
						text-align: left;
						background-color: #666;
						color: white;
						}
					.data{ text-transform: uppercase;font-weight:bold;}
			</style>';
	$content .= '<table width="100%" border="0" cellspacing="5" cellpadding="0">				
					<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden; text-transform:uppercase;">GOVERMENT OF WEST BENGAL</td></tr>
					<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden; text-transform:uppercase;"><b>Directorate of Factories</b></td></tr>
					<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden; text-transform:uppercase;">LICENCE REGISTER</td></tr>
					</table>';
					
	$content .= '<table width="100%" cellspacing="0" cellpadding="5" style="border-bottom: 1px solid #000; border-top:1px solid #000;">
				 	<tr>
						<td align="left" ><span style="font-size:12px;font-weight:bold;">Classification No.&nbsp;</span>'.$classification_no.'</td>
						<td align="left" ><span style="font-size:12px;font-weight:bold;">Registration No.&nbsp;</span>'.$reg_no.'</td>
						<td align="left" ><span style="font-size:12px;font-weight:bold;">Date.&nbsp;</span>'.date('dS M Y', strtotime($registration_date)).'</td>
						<td align="left" ><span style="font-size:12px;font-weight:bold;">Licence No.&nbsp;</span>'.$license_no.'</td>
					</tr>
				</table>';
				
	$content .= '<table width="100%" cellspacing="0" border="5" cellpadding="0">
				 	<tr>
						<td align="left" style="font-size:12px;"><h2>Name & Address of the Factory </h2>'.$factory_name_address.'</td>
						<td align="left" style="font-size:12px;"><h2>Name of the Occupier</h2>'.$ocupier_name.'</td>
					</tr>
					<tr>
						<td align="left" style="font-size:12px;"><h2>Change If Any...</h2>'.$change.'</td>
						<td align="left" style="font-size:12px;"><h2>Transferred to..</h2>'.$ocupier_transfer.'</td>
					</tr>
					
				</table>';
				 
	$content .= '<table id="tabular">
				<tr>					 				
                 	<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Year </td>
					<td width="10%" style="font-size:12px;" align="left" valign="top" colspan="2"> Licence Issued for<br/>Category: <br/>Schedule: '.$s.'<br/> </td>
					<td width="10%" style="font-size:12px;" align="left" valign="top" rowspan="2"> Amount of fee paid<br/>(a)Registration<br/>(b)Licence<br/>(c)Amendment<br/>(d)Transfer<br/>(e)Late<br/>(f)Loss </td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Date of Deposit </td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Serial no. Challan reg. </td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Excess Amount paid</td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Excess Amount adjusted</td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Entered by</td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Checked by</td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Remarks</td>
				</tr>
				<tr>					 				
					<td width="10%" style="font-size:12px;" align="center" valign="top" > HP/KW </td>
					<td width="10%" style="font-size:12px;" align="center" valign="top"> Worker </td>
				</tr>';
			
	$year_data = get_licence_register_list($e_id);
			
			foreach($year_data as $row){
			$dates = explode(',', $row->deposit_date);	
			
	$content .= '<tr>					 				
					<td width="10%" align="center"> '.$row->licence_period.' </td>
					<td width="10%" align="center"> '.$row->power.''.$row->power_type.' </td>
					<td width="10%" align="center"> '.$row->worker.' </td>
					<td width="10%" align="left">(a)'.$row->register_fee.'<br/>(b)'.$row->renewal_fee.'<br/>(c)'.$row->amendment_fee.'<br/>(d)'.$row->transfer_fee.'<br/>(e)'.$row->late_pay_fee.'<br/>(f)'.$row->loss_fee.'</td>
					<td width="10%"  style="font-size:12px;"align="center">';
					foreach($dates as $date){
		$content .= date('dS M Y', strtotime($date)).'<br/>';
					}
	    $content .= '</td>
					<td width="10%" align="center"> '.$row->power.'</td>
					<td width="10%" align="center"> '.$row->excees_fees.'</td>
					<td width="10%" align="center">'.$row->adjusted_fees.'</td>
					<td width="10%" align="center">'.get_name($row->uid).'</td>
					<td width="10%" align="center"> '.get_name($row->uid).'</td>
					<td width="10%" align="center">'.$row->register_remarks.'</td>
				</tr>';
			}
				
	$content .= '</table>';
	return pdf_using_mpdf_api($content,'caf-journal'._.time());
}

