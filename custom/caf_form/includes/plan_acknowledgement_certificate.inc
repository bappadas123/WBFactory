<?php
function plan_acknowledgement_certificate($applicationid='' ,$referenceid ='' ,$serviceid='' ,$factorytypeid =''){
	global $base_root, $base_path, $user; 
	
	
	 $application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	 $reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	 $service_id 		= encryption_decryption_fun('decrypt', $serviceid);
	 $factorytype_id 	= encryption_decryption_fun('decrypt', $factorytypeid);
	 $get_all_data 		= get_application_withid($application_id); //echo $application_id;
	
	//echo "<pre>"; print_r($get_all_data); die;
	$name_of_factory 			  = 	($get_all_data[0]->factory_name)? $get_all_data[0]->factory_name : 'Nil'; //die;
	$factory_plan_approval_number = 	($get_all_data[0]->factory_plan_approval_number)? $get_all_data[0]->factory_plan_approval_number : 'Nil'; //die;
	$modification_date            = 	 date_create($get_all_data[0]->modification_date); //die;
	$date_approval1 = date_format($modification_date,'d/m/Y');
	$date_approval2 = date_format($modification_date,'F j, Y'); //die;

	$created_date            = 	 date_create($get_all_data[0]->created_date); //die;
	$date_created       =   date_format($created_date,'d/m/Y');

	$plan_approve_identification_number = 	($get_all_data[0]->plan_approve_identification_number)? $get_all_data[0]->plan_approve_identification_number : 'Nil'; //di
	$plan_conditional_letter_no         = 	($get_all_data[0]->plan_conditional_letter_no)? $get_all_data[0]->plan_conditional_letter_no : 'Nil'; //di
	$plan_conditions         = 	get_plan_additional_conditions($application_id,$reference_id);
	
	/* FACTORY ADDRESS */
	$getdata_factory_address 	=  	array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address 			=	get_parts_address('fa_cafa','sub-table',$application_id,$getdata_factory_address);

	$address_line_factory    	= ($get_all_data[0]->addrline)? $get_all_data[0]->addrline : ''; 
	$post_office_factory     	= ($factory_address['po_name'])? $factory_address['po_name'] : ''; 
	$pin_code_factory        	= ($factory_address['pincode'])? $factory_address['pincode'] : ''; 
	$district_factory        	= ($factory_address['district_name'])? $factory_address['district_name'] : ''; 
	$police_station_factory  	= ($factory_address['name_of_police_station'])? $factory_address['name_of_police_station'] : ''; 
	
	$get_total_docs 			=  	get_attached_filename($application_id ,$reference_id,$factorytype_id,$service_id);
	$get_total_docs_count     	=   count($get_total_docs); 
	$total_process_days_count   =   ($get_total_docs_count >= 4) ? '50' : '_';
	
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
					<tr><td colspan="3" align="center">Form-I</td></tr>
					<tr><td colspan="3"></td></tr>
					<tr><td colspan="3" align="center" style="font-size:15px;text-transform:uppercase;"><h2> ACKNOWLEDGEMENT </h2></td></tr>
					<tr><td colspan="3"></td></tr></table>';
					
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
					 <tr><td colspan="3"></td></tr>
					 <tr><td width="100%" align="left">From,</td></tr>
					 <tr><td width="100%" align="left">Directorate of Factories</td></tr>
					 <tr><td width="100%" align="left">N.S. Buldings. (8th floor), Kol-1</td></tr>
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
				 <tr><td colspan="3"><b>Sub :- The West Bengal Right to Public Services Act,2013 - Acknowledgement of application</b></td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3">Ref :- Your Application No. <b>'.$plan_approve_identification_number.'</b> dated <b>'.$date_created.'</b></td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3" width="100%" valign="top">I hereby acknowledge your application cited Due data of service to be provided is '.$total_process_days_count.' working days.</td></tr>';
				 
				if($total_process_days_count != '50') {
				 
	$content .= '<tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3" align="center"><b>OR</b></td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>
				 <td valign="top">1. </td>
				 <td>&nbsp;</td>
				 <td width="100%" valign="top">Duly filled in Common Application form (Part-A & B).</td>
				 </tr>
				 
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>
				 <td valign="top">2. </td>
				 <td>&nbsp;</td>
				 <td width="100%" valign="top">Flow Chart of the manufacturing process along with brief description.</td>
				 </tr>

				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>
				 <td valign="top">3. </td>
				 <td>&nbsp;</td>
				 <td width="100%" valign="top">Authenticated copy of Consent to established from WBPCB.</td>
				 </tr>

				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>
				 <td valign="top">4. </td>
				 <td>&nbsp;</td>
				 <td width="100%" valign="top">Factory plan in duplicate for Kolkata/Howrah and three copies for regional offices.</td>
				 </tr>

				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>
				 <td valign="top">5. </td>
				 <td>&nbsp;</td>
				 <td width="100%" valign="top">Declaration , duly signed by the Occupier, stating whether any process or activities of the factories is a hazardous process as defined under section 2(cb) read with scheduled I of the Factories Act. 1948 as amended.</td>
				 </tr>';
		}
		
	$content .= '</table>';
				 
				

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr><tr><td colspan="3"></td></tr><tr><td colspan="3"></td></tr>
				 <tr>					 				
					<td width="40%" align="left">Place : Kolkata</td>
					<td width="10%" align="right"></td>
					<td width="40%" align="right">Yours faithfully</td>
				 </tr>
				 <tr>					 				
					<td width="40%" align="left">Date : '.$date_created.'</b></td>
					<td width="10%" align="right"></td>
					<td width="40%" align="right">Inspector of Factories</td>
				 </tr>
				 <tr>					 				
					<td colspan="3" align="right">West Bengal</td>
				 </tr>
				 <tr><td colspan="3"></td></tr><tr><td colspan="3"></td></tr><tr><td colspan="3"></td></tr>
				 <tr><td colspan="3"><b>N:B: This is a computer generated acknowledgement does not required signature.</b></td></tr>
				<tr><td></td></tr></table>';

    //echo $content; die;
	return pdf_using_mpdf_api($content,'caf-'._.time());
	
}
?>