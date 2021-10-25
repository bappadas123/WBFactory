<?php

function licecne_demo_preview($applicationid,$serviceid, $factory_typeid,$referenceid) {	

	global $base_root, $base_path, $user; 
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$service_id 		= encryption_decryption_fun('decrypt', $serviceid);
	$factorytype_id 	= encryption_decryption_fun('decrypt', $factory_typeid);
	
	$get_all_data      	= 	get_fa_cafa($application_id);
	//print_r($get_all_data);die;
	$max_license_no 	= $get_all_data['factory_license_no'];
	$max_reg_no 		= $get_all_data['factory_registrstion_no']; 
	$zonid 				= $get_all_data['factory_zone'];
	$zone 				= get_factory_zone_name($zonid);
	$payment_amount		= $get_all_data['payment_amount'];
	$payment_date		= $get_all_data['payment_date'];
	$district_code		= $get_all_data['district'];
	$factory_owershiptype = $get_all_data['factory_owershiptype'];
	$grand_to 				= '';
	if($factory_owershiptype == "ltd" || $factory_owershiptype == "pv" || $factory_owershiptype == "others" || $factory_owershiptype == "psu" || $factory_owershiptype == "govt"){
		
		$grand_to = $get_all_data['factory_name'];
	}
	if($factory_owershiptype == "pro_firm"){
		$i=0;
		$get_ocupier_data = get_all_occupier_data($application_id,$service_id,$factorytype_id,$reference_id);
		foreach($get_ocupier_data as $occuiper){
			$i= $i+1;
		}
		if($i>1){
			$grand_to = $occuiper->name_occupier.'& Others';
		}else{
			$grand_to  = $occuiper->name_occupier;
		}
	}if($factory_owershiptype == "par_firm"){
		$i=0;
		$get_director_data = get_director_details_service($application_id,$service_id,$factorytype_id,$reference_id);
		foreach($get_director_data as $director){
			
			$i= $i+1;
		}
		if($i>1){
			$grand_to = $director->name_director.'& Others';
		}else{
			$grand_to  = $director->name_director;
		}
	}


		
	//$max_license_no 			= $get_all_data['factory_license_no'];
	//$max_reg_no 				= $get_all_data['factory_registrstion_no'];
	$get_all_nature_data 		= get_nature_manufacture_data($application_id);
	$get_all_power_data 		= get_power_data($application_id,$service_id,$factorytype_id,$reference_id);
	$worker_details 			= get_worker_details_service($service_id,$factorytype_id,$application_id,$reference_id);
	$maxWorker = 0;
	foreach($worker_details as $worker){
		$max_worker = $worker->worker_total;
		$maxWorker = max($max_worker, $maxWorker);
		}
		
	$maxHP = 0;
	foreach($get_all_power_data as $power){
		$max_hp = $power->installed_power_hp;
		 $maxHP = max($max_hp, $maxHP);
		}

		
	$img_url					= $_SERVER['DOCUMENT_ROOT']. $base_path.'sites/all/themes/wbfactories/images/em.jpg';
	//print_r($img_url);die();

	$name_of_factory 			= 	$get_all_data['factory_name'];
	$amenability_date 			= 	$get_all_data['date_of_amenability'];
	$classification_no			= 	$get_all_data['classification_no'];
	$date_of_amenability 		= 	date('dS M Y', strtotime($amenability_date));
	
	$getdata_factory_address 	=  	array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address 			= 'Zone:-'.$zone['zone_name'].',&nbsp;'. $get_all_data['addrline'].',&nbsp;'.get_full_address_certificates('fa_cafa','sub-table',$application_id,$getdata_factory_address);
	
	$content = '<style type="text/css">
					table, td, th {
							font-size:12px;
							font-family:Times New Roman;
							height:15px;
							color:#000;
							margin-top:10px;
							background:#fff;
							line-hight: 25px;
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
						line-hight: 1px;
					}
					#tabular tr {
						padding-top: 12px;
						padding-bottom: 12px;
						text-align: left;
						background-color: #666;
						color: white;
						}
					.data{ text-transform: uppercase;font-weight:bold;}
			</style><title>SAMPLE Certificate</title>';
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">				
					<tr><td colspan="3"></td></tr>
					
					<tr><td colspan="3" align="center" style="font-size:15px;text-transform:uppercase;"><h2> FORM-3 </h2></td></tr>
					<tr><td colspan="3"  align="center" style="font-size:10px;">[See rules5(1),6(4),7(1) and 8(2)]</td></tr>
					<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden; text-transform:uppercase;">GOVERMENT OF WEST BENGAL</td></tr>
					<tr><td colspan="3" align="center"><img src="'.$img_url.'" width="40px"/></td></tr>
					
					<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden; text-transform:uppercase;">Directorate of Factories</td></tr>
					</table>';			
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3" align="center" style="font-size:18px;"><h3 style="border-bottom:0px solid;">LICENCE TO WORK A FACTORY</h3></td></tr>
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" >Licence No.&nbsp;<b>XXXXX</b> Reg. No.&nbsp;<b>XXXXXXXX</b> .&nbsp;Date of amenability  <span class="data">&nbsp;'.$date_of_amenability .'</span> &nbsp; H.P  <span class="data">'.$maxHP.'</span> &nbsp; Worker <span class="data"> '.$maxWorker.'&nbsp;</span> Fee Rs. 000000/- &nbsp; 
				 Licence is hereby granted to<span class="data"> '.$grand_to.', </span> valid only for the factory knowns as  <span class="data">&nbsp;'.$name_of_factory.'</span>&nbsp;&nbsp;situated at &nbsp;&nbsp;<span class="data">' .$factory_address.'</span>, subject provisions of the Factories Act, 1948, and the rules made thereunder.</td></tr>
				 <tr><td>&nbsp;</td></tr>
				 <tr><td colspan="3" align="left" style="font-size:12px;">The licence shall remain in force till <b>xx-xx-xxxx</b></td></tr>
				<tr>
					<td colspan="2" align="left" style="font-size:12px;">The xx-xx-xxxx</td>

					<td align="right" style="font-size:12px;">
					<br><br><br>
					Chief Inspector of Factories, West Bengal</td>
				</tr>
				 </table>';
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td align="center" style="font-size:18px;"><h3>RENEWALS</h3></td></tr>
				 </table>';
				 
	$content .= '<table id="tabular">
				<tr>					 				
				<td width="14%" style="font-size:12px;" align="center" valign="top"> Valid up to </td>
				<td width="10%" style="font-size:12px;" align="center" valign="top"> H.P </td>
				<td width="14%" style="font-size:12px;" align="center" valign="top"> Worker </td>
				<td width="14%" style="font-size:12px;" align="center" valign="top">Fee for renewal </td>
				<td width="14%" style="font-size:12px;" align="center" valign="top"> Date of payment </td>
				<td width="14%" style="font-size:12px;" align="center" valign="top"> Late fee for renewal </td>
				<td width="18%" style="font-size:12px;" align="center" valign="top"> Signature of Chief <br> Inspector of Factories, West Bengal</td>
				</tr>';
				 
			/*	foreach($get_all_power_data as $power){
	$content .= '<tr>					 				
				<td width="14%"> '.$power->service_year.'</td>
				<td width="10%"> '.$power->installed_power_hp.' H.P</td>
				<td width="14%"> </td>
				<td width="14%"> </td>
				<td width="14%"> </td>
				<td width="14%"> </td>
				<td width="18%"> </td>
				</tr>';
				 }*/
	$content .= '</table>';
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td align="center" style="font-size:18px;"><h3>TRANSFERS</h3></td></tr>
				 </table>';
				 
	$content .= '<table id="tabular">
				<tr>					 				
				<td width="25%" style="font-size:12px;" align="center" valign="top"> To whom transferred </td>
				<td width="25%" style="font-size:12px;" align="center" valign="top"> Date of Transfer </td>
				<td width="25%" style="font-size:12px;" align="center" valign="top"> Date of payment of transfer fee </td>
				<td width="25%" style="font-size:12px;" align="center" valign="top"> Signature of Chief <br> Inspector of Factories, West Bengal</td>
				</tr>';
				
				/* <tr>					 				
				
				<td width="25%"> </td>
				<td width="25%">  </td>
				<td width="25%"></td>
				<td width="25%"> </td>
				</tr> */
				
		$content .= '</table>';
		$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td align="center" style="font-size:18px;"><h3>AMENDMENTS</h3></td></tr>
				 </table>';
				 
	$content .= '<table id="tabular">
				<tr>					 				
				<td width="14%" style="font-size:12px;" align="center" valign="top"> Date of amendment </td>
				<td width="10%" style="font-size:12px;" align="center" valign="top"> Amended worker </td>
				<td width="14%" style="font-size:12px;" align="center" valign="top"> Amended H.P </td>
				<td width="14%" style="font-size:12px;" align="center" valign="top"> Date of payment of Amendment fee </td>
				<td width="14%" style="font-size:12px;" align="center" valign="top"> additional fee </td>
				<td width="18%" style="font-size:12px;" align="center" valign="top"> Signature of Chief <br> Inspector of Factories, West Bengal</td>
				</tr>';
				/*<tr>					 				
				<td width="14%">  </td>
				<td width="14%"> </td>
				<td width="14%"> </td>
				<td width="14%">  </td>
				<td width="14%"> </td>
				<td width="18%"> </td>
				</tr>
				*/
			$content .= '</table>';
	
	return pdf_using_mpdf_api($content,'licecne_file'._.time());
	}
