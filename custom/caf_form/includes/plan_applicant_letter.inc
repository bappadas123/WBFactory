<?php
function plan_applicant_letter($applicationid='' ,$referenceid ='' ,$serviceid='' ,$factorytypeid =''){
	
	global $base_root, $base_path, $user; 
	
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$service_id 		= encryption_decryption_fun('decrypt', $serviceid);
	$factorytype_id 	= encryption_decryption_fun('decrypt', $factorytypeid);
	$get_all_data 		= get_application_withid($application_id);
	
	$name_of_factory 			  = 	($get_all_data[0]->factory_name)? $get_all_data[0]->factory_name : 'Nil'; //die;
	$factory_plan_approval_number = 	($get_all_data[0]->factory_plan_approval_number)? $get_all_data[0]->factory_plan_approval_number : 'Nil'; //die;
	$modification_date            = 	 date_create($get_all_data[0]->modification_date); //die;
	$date_approval1 = date_format($modification_date,'d/m/Y');
	$date_approval2 = date_format($modification_date,'F j, Y'); //die;

	$created_date                 = 	 date_create($get_all_data[0]->created_date); //die;
	$date_created       		  =   date_format($created_date,'d/m/Y');

	$plan_approve_identification_number = 	($get_all_data[0]->plan_approve_identification_number)? $get_all_data[0]->plan_approve_identification_number : 'Nil'; //di
	$plan_conditional_letter_no         = 	($get_all_data[0]->plan_conditional_letter_no)? $get_all_data[0]->plan_conditional_letter_no : 'Nil'; //di
	
	$plan_remarks                    = 	get_remarks_to_applicant($application_id,$reference_id,'ABk');
	
	/* FACTORY ADDRESS */
	$getdata_factory_address 	=  	array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address 			=	get_parts_address('fa_cafa','sub-table',$application_id,$getdata_factory_address);

	$address_line_factory    	= ($get_all_data[0]->addrline)? $get_all_data[0]->addrline : ''; 
	$post_office_factory     	= ($factory_address['po_name'])? $factory_address['po_name'] : ''; 
	$pin_code_factory        	= ($factory_address['pincode'])? $factory_address['pincode'] : ''; 
	$district_factory        	= ($factory_address['district_name'])? $factory_address['district_name'] : ''; 
	$police_station_factory  	= ($factory_address['name_of_police_station'])? $factory_address['name_of_police_station'] : ''; 
	
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
					<tr><td colspan="3" align="center"><img src="https://wbfactories.gov.in/assets/images/ashoke_stambho.png"></td></tr>
					<tr><td colspan="3" align="center" style="font-size:15px;border-style:hidden hidden double hidden;">GOVERNMENT OF WEST BENGAL</td></tr>
					<tr><td colspan="3"></td></tr>				
					<tr><td colspan="3" align="center" style="font-size:15px;text-transform:uppercase;"><h2> DIRECTORATE OF FACTORIES </h2></td></tr>
					<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden;">NEW SECRETARIAT BUILDINGS (8th floor)</td></tr>
					<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden;">1, KIRON SANKAR ROY ROAD, KOLKATA -700001</td></tr>
					<tr><td colspan="3"></td></tr></table>';
					
		$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
					 <tr><td colspan="3"></td></tr>
					 <tr>					 				
						<td width="40%" align="left">&nbsp;</td>
						<td width="10%" align="right">&nbsp;</td>
						<td width="40%" align="right">Dated, The  <b>'.$date_approval2.'</b></td>
					 </tr>
					<tr><td colspan="3"></td></tr></table>';
				
					
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
	
				<tr><td colspan="3" align="left">To,</td></tr>
				<tr><td colspan="3" align="left">The Occupier</td></tr>
				<tr><td colspan="3" align="left" style="text-transform:uppercase;">'.$name_of_factory.'</td></tr>
				<tr><td colspan="3" align="left" style="text-transform:uppercase;">'.$address_line_factory.'</td></tr>
				<tr><td colspan="3" align="left" style="text-transform:uppercase;"><b>P.S : </b>'.$police_station_factory.'<b> District : </b>'.$district_factory.'</td></tr>
				<tr><td colspan="3" align="left" style="text-transform:uppercase;"><b>P.0 : </b>'.$post_office_factory.'<b> Pin : </b>'.$pin_code_factory.'</td></tr>
				
				</table>';

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3"><b>Sub :- Approval Of Plan : Irregularities Observed</b></td></tr>
				 <tr><td colspan="3">Ref :- Your Application No. <b>'.$plan_approve_identification_number.'</b> Dated <b>'.$date_created.'</b></td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3" width="100%" valign="top">Sir,</td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3" width="100%" valign="top">The plan submitted by you, were scrutinized and the undermentioned irregularities have been observed.Hence they can not be recommended for aproval.</td></tr>
				 </table>';
				 
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
					 <tr><td colspan="3">&nbsp;</td></tr>
					 <tr>
						 <td valign="top">'.$cnt.'. </td>
						 <td>&nbsp;</td>
						 <td width="100%" valign="top">'.$plan_remarks['remarks'].'.</td>
					 </tr>
				</table>';	
	
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td>&nbsp;</td></tr>
				 <tr><td width="100%" valign="top">You are therefore advised to submit the revised plan at an early date.</td></tr>

				 </table>';
				
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr><tr><td colspan="3"></td></tr><tr><td colspan="3"></td></tr>
				 <tr><td width="100%" align="right">Yours faithfully</td></tr>
				 <tr><td width="100%" align="right">&nbsp;</td></tr>
				 <tr><td width="100%" align="right">&nbsp;</td></tr>
				 <tr><td width="100%" align="right">(Assistant Director/Inspector of factories)</td></tr>
				 <tr><td width="100%" align="right">West Bengal</td></tr>

				<tr><td colspan="3"></td></tr></table>';

    //echo $content; die;
	return pdf_using_mpdf_api($content,'caf-'._.time());
}
?>