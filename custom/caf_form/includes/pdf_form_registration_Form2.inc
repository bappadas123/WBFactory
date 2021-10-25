<?php
require_once '/var/www/html/factories/sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';

function pdf_form_registration_Form2($applicationid='' ,$referenceid ='' ,$serviceid='' ,$factorytypeid ='' ,$yearid=""){
	global $base_root, $base_path, $user; 
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$service_id 		= encryption_decryption_fun('decrypt', $serviceid);
	$factorytype_id 	= encryption_decryption_fun('decrypt', $factorytypeid);
	$year_id 			= encryption_decryption_fun('decrypt', $yearid);
	//echo $application_id;die;
	$get_all_data 			=  get_fa_cafa($application_id);
	$is_backlog				= $get_all_data['is_backlog'];
	if($is_backlog == 1){
		$plan_approval_no 	= $get_all_data['backlog_plan_approval_no'];
		$plan_approval_date = date('dS M Y', strtotime($get_all_data['backlog_plan_approval_date']));
	}if($is_backlog != 1){
		$plan_approval_no 	= $get_all_data['factory_plan_approval_number'];
		$plan_approval_date = date('dS M Y', strtotime($get_all_data['modification_date']));
	}
	$fetch_year_details		= fetch_year_details_withid($year_id);
	$previous_name			= fetch_previous_calid($year_id);
	
	$getdata_factory_address  	=  	array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address 		    =	get_parts_address('fa_cafa','sub-table',$application_id,$getdata_factory_address);
	
	$getdata_headoffice_address	=  array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
	$headoffice_address 		= $get_all_data['addrline_off'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_headoffice_address);
	
	$getdata_owner_address		=  array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
	$owner_address				= $get_all_data['addrline_premises'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_owner_address);
	
	$manager_details 			= get_form2_manager_data($application_id,$service_id,$factorytype_id,$reference_id,$year_id);
	$occupier_details			= get_all_occupier_data($application_id,$service_id,$factorytype_id,$reference_id,$year_id);
	$director_details 			= get_director_details_service($application_id,$service_id,$factorytype_id,$reference_id,$year_id);
	//$manufacturing_detials_year 		= nature_manufacturing_year($fetch_year_details['calculate_year'],$application_id,$reference_id,$factorytype_id,$service_id);
	$previous_year_nature_manufacturing = get_form2_nature_manufacturing_previous_year($application_id,$reference_id,$factorytype_id,$service_id);
	$manufacturing_detials_year 		= get_form2_nature_manufacturing_year($fetch_year_details['calculate_year'],$application_id,$reference_id,$factorytype_id,$service_id);
	$previous_year_worker 				= get_form2_worker_previous_year($application_id,$reference_id,$factorytype_id,$service_id);

	$power_detials_year		= power_detials_year($fetch_year_details['calculate_year'],$application_id,$reference_id,$factorytype_id,$service_id);
	$worker_detials_year 	= worker_detials_year($fetch_year_details['calculate_year'],$application_id,$reference_id,$factorytype_id,$service_id);
	
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
					<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden;"><h1>Unregistered/Registered(Strike out whichver is not applicable)</h1></td></tr>
					<tr>
					<td align="left" style="border-style:hidden hidden double hidden;"><h1>Classification No. .....................</h1></td>
					<td colspan="2" align="right" style="border-style:hidden hidden double hidden;"><h1>Registration No. .....................</h1></td>
					</tr>
					<tr><td colspan="3"></td></tr>
					<tr><td colspan="3" align="center" style="font-size:15px;text-transform:uppercase;"><h2> "FORM No. 2" </h2><br/>
					<h2>(See Rule 3,4,6,7,8,13)</h2>
					</td></tr>
					<tr><td colspan="3"></td></tr>
					
					<tr><td colspan="3" align="center"><strong>Application for Registration and Grant or Renewal of licence and notice of occupation specified in <br>section 6 &7of the Factories Act, 1948<br>(To be submitted in duplicate)</strong></td></tr>
					<tr><td colspan="3"></td></tr>
					<tr><td colspan="3"  align="center">Application for the year ending '.date('dS M Y', strtotime($fetch_year_details['calculate_end_year'])).' </td></tr>
					</table>';
					
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr>					 				
					<td width="2%" valign="top">1.(a)</td>
					<td width="49%" valign="top">Full Name of the Factory </td>
					<td width="49%" ><span class="data">: '.$get_all_data['factory_name'].'</span></td>
				 </tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>					 				
					<td width="49%" valign="top" colspan="2">(b) Previous Name of the Factory (if different from the present name) </td>
					<td width="49%"><span class="data" valign="top">: '.$previous_name.'</span></td>
				 </tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 </table>';
				 
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>					 				
					<td width="2%"  valign="top">2</td>
					<td width="49%" valign="top">(a) Situation of the Factory</td>
					<td width="49%"></td>
				</tr>
				<tr><td colspan="3">&nbsp;</td></tr>
				<tr>					 				
					<td width="2%"  valign="top"></td>
					<td width="49%" valign="top" style="padding-left: 15px;">Address</td>
					<td width="49%"><span class="data">: '.$get_all_data['addrline'].'</span></td>
				</tr>
				<tr><td colspan="3">&nbsp;</td></tr>
				<tr>					 				
					<td width="2%"  valign="top"></td>
					<td width="49%" valign="top" style="padding-left: 15px;"> Post Office</td>
					<td width="49%"><span class="data">: '.$factory_address['po_name'].'</span></td>
				</tr>
				<tr><td colspan="3">&nbsp;</td></tr>
				<tr>					 				
					<td width="2%"  valign="top"></td>
					<td width="49%" valign="top" style="padding-left: 15px;">Pin Code</td>
					<td width="49%"><span class="data">: '.$factory_address['pincode'].'</span></td>
				</tr>
				<tr><td colspan="3">&nbsp;</td></tr>
				<tr>					 				
					<td width="2%"  valign="top"></td>
					<td width="49%" valign="top" style="padding-left: 15px;"> Sub Divisional Headquarter </td>
					<td width="25%"><span class="data">: '.$factory_address['sub_div_name'].'</span></td>
				</tr>
				<tr><td colspan="3">&nbsp;</td></tr>
				<tr>					 				
					<td width="2%"  valign="top"></td>
					<td width="49%" style="padding-left: 15px;">District </td>
					<td width="49%"><span class="data">: '.$factory_address['district_name'].'</span></td>
				</tr>
				<tr><td colspan="3">&nbsp;</td></tr>
				<tr>					 				
					<td width="2%"  valign="top"></td>
					<td width="49%" valign="top" style="padding-left: 15px;"> Police Station </td>
					<td width="49%"><span class="data">: '.$factory_address['name_of_police_station'].'</span></td>
					<tr><td colspan="3">&nbsp;</td></tr></tr>
					<tr><td colspan="3">&nbsp;</td></tr>
				<tr>					 				
					<td width="2%"  valign="top"></td>
					<td width="49%" valign="top">(b) Address of the Registered Office/Head Office </td>
					<td width="49%"><span class="data">: '.$headoffice_address.'</span></td>
				</tr>
				</table>';
				 
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr>					 				
					<td width="2%"  valign="top">3.</td>
					<td width="49%" valign="top"> Address to which communications relating to the factory may be sent </td>
					<td width="49%"><span class="data">: '.$headoffice_address.'</span></td>
				 </tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>					 				
					<td width="2%"  valign="top">4.</td>
					<td width="49%" valign="top"> Name and residental address of the owner of the premises occupied as a factory</td>
					<td width="49%"><span class="data">: '.$get_all_data['owner_name'].'<br/>'.$owner_address.'</span></td>
				 </tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>					 				
					<td width="2%"  valign="top">5.</td>
					<td width="49%" valign="top">Nature of the manufacturing process/processes</td>
					<td width="49%"><span class="data">:</span></td>
				 </tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>					 				
					<td width="2%"  valign="top">&nbsp;</td>
					<td width="49%" valign="top">(a)&nbsp; Carried on in the factory during the preceding twelve months (if the factory was then in existance)</td>
					<td width="49%"><span class="data">:'.$previous_year_nature_manufacturing['nature_manufacturing'].'</span></td>
				 </tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>					 				
					<td width="2%"  valign="top">&nbsp;</td>
					<td width="49%" valign="top">(b)&nbsp; To be Carried on in the factory during the next twelve months</td>
					<td width="49%"><span class="data">:'.$manufacturing_detials_year['nature_manufacturing'].'</span></td>
				 </tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>					 				
					<td width="2%"  valign="top">6.</td>
					<td width="49%" valign="top">Name, age, father\'s/Husband\'s name and present residential address and P.S. of the manager for the purpose of the Factories Act: </td>
					<td width="49%" valign="button"><span class="data"></span></td>
				 </tr>';
				foreach($manager_details as $manager){
		 				$fieldArr_manager	=  array('district_manager','sub_division_manager','area_type_manager','block_mun_cor_sez_not_manager','grm_ward_sector_not_manager','police_station_manager','pincode_manager','state_manager','post_office_manager');
   						$address_of_manager	 =	$manager->adress_line1_manager.'<br>'.get_full_address('fa_manager_details','sub-table',$manager->id,$fieldArr_manager);
	$content .='<tr><td colspan="3">&nbsp;</td></tr>
				  <tr>
				  	<td width="2%" valign="top"></td>
					<td width="49%" valign="top" >Name</td>
					<td width="49%" ><span class="data">:'.$manager->name_manager.'</span></td>
				  </tr>
				  <tr><td colspan="3">&nbsp;</td></tr>
				  <tr>
				    <td width="2%" valign="top"></td>
					<td width="49%" valign="top">Age</td>
					<td width="49%"><span class="data">:'.$manager->age_manager.'</span></td>
				  </tr>
				  <tr><td colspan="3">&nbsp;</td></tr>
				  <tr>
				    <td width="2%" valign="top"></td>
					<td  width="49%" valign="top">Father\'s/Husband\'s name</td>
					<td width="49%"><span class="data">:'.$manager->father_husband_name_manager.'</span></td>
				  </tr>
				  <tr><td colspan="3">&nbsp;</td></tr>
				  <tr>
				    <td width="2%" valign="top"></td>
					<td width="49%" valign="top">Present Address</td>
					<td width="49%"><span class="data">:'.$manager->manager_present_address.'</span></td>
				  </tr>
				  <tr><td colspan="3">&nbsp;</td></tr>
				  <tr>
				    <td width="2%" valign="top"></td>
					<td  width="49%" valign="top">Permanent Address</td>
					<td width="49%"><span class="data">:'.$address_of_manager.'</span></td>
				  </tr>';
				  
	 		}
	$content .= '<tr><td colspan="3">&nbsp;</td></tr>';
	$content .= ' <tr>					 				
					<td width="2%"  valign="top">7.</td>
					<td width="49%" valign="middle" colspan="2">Name, Father\'s/Husband\'s name and residential address of Director/Partners/Proprietor :</td>
				 </tr>
				 <tr><td colspan="3">&nbsp;</td></tr>';
				 foreach($director_details as $dircetor){
			if($dircetor->type_director == "Director"){
				$fieldArr_director	=  array('district_director','sub_division_director','area_type_director','block_mun_cor_sez_not_director','grm_ward_sector_not_director','police_station_director','pincode_director','state_director','post_office_director');
    $address_of_director =	$dircetor->adress_line1_director.'<br>'.get_full_address('fa_director_details','sub-table',$dircetor->id,$fieldArr_director);
	$content .= ' <tr>					 				
					<td width="2%"  valign="top">&nbsp;</td>
					<td width="49%" valign="top">(a)&nbsp; Directors in case of company</td>
					<td width="49%"><span class="data">'.$dircetor->type_director.'<br/>'.$dircetor->name_director.'<br/>'.$dircetor->father_husband_name_director.'<br>'.$address_of_director.'</span></td>
				 </tr>';
			}
	$content .= ' <tr><td colspan="3">&nbsp;</td></tr>';
			if($dircetor->type_director != "Director"){//echo 'hi';die();
				$fieldArr_director	=  array('district_director','sub_division_director','area_type_director','block_mun_cor_sez_not_director','grm_ward_sector_not_director','police_station_director','pincode_director','state_director','post_office_director');
    $address_of_director =	$dircetor->adress_line1_director.'<br>'.get_full_address('fa_director_details','sub-table',$dircetor->id,$fieldArr_director);
	
	$content .= ' <tr>					 				
					<td width="2%"  valign="top">&nbsp;</td>
					<td width="49%" valign="top">(b)&nbsp; Partners/Proprietor</td>
					<td width="49%"><span class="data">'.$dircetor->type_director.'<br/>'.$dircetor->name_director.'<br/>'.$dircetor->father_husband_name_director.'<br>'.$address_of_director.'</span></td>
				 </tr>';
				}
		}
	$content .= ' <tr><td colspan="3">&nbsp;</td></tr>		
				<tr><td colspan="3" ></td></tr>
				<tr><td colspan="3" align="center"><i>( Enclose separate sheet if necessary )</i></td></tr>
				<tr><td colspan="3">&nbsp;</td></tr>
				<tr>
					<td width="2%"  valign="top">8.</td>
					<td width="49%" valign="top">Name, Father\'s/Husband\'s name present and permanent Residential address P.S. with of the occupier as per provisions of section 2(n) of the Act (a) Director in case of a company. (b) Partner in case of him or (c) Proprietor - </td>
					<td  width="49%"><span class="data"></span></td>
				 </tr>';
				  foreach($occupier_details as $occupier){
				$fieldArr_occupier		=  array('district_occupier','sub_division_occupier','area_type_occupier','block_mun_cor_sez_not_occupier','grm_ward_sector_not_occupier','police_station_occupier','pincode_occupier','state_occupier','post_office_occupier');
    $address_of_occupier	 =	$occupier->adress_line1_occupier.'<br>'.get_full_address('fa_occupier_details','sub-table',$occupier->id,$fieldArr_occupier);
	$occupier_address 		 = get_parts_address('fa_occupier_details','sub-table',$occupier->id,$fieldArr_occupier);
		
		$content .= ' <tr><td colspan="3">&nbsp;</td></tr>
				  <tr>
				  	<td width="2%" valign="top"></td>
					<td width="49%" valign="top" >Name in full </td>
					<td width="49%"><span  class="data">:'.$occupier->name_occupier.'</span></td>
				 </tr>
				  <tr><td colspan="3">&nbsp;</td></tr>
				  <tr>
				  	<td width="2%" valign="top"></td>
					<td width="49%" valign="top" >Age</td>
					<td width="49%"><span class="data">:'.$occupier->age_occupier.'</span></td>
				 </tr>
				  <tr><td colspan="3">&nbsp;</td></tr>
				  <tr>
				    <td width="2%" valign="top"></td>
					<td width="49%" valign="top">Father\'s/Husband\'s name</td>
					<td width="49%"><span class="data">:'.$occupier->father_husband_name_occupier.'</span></td>
				 </tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>
				    <td width="2%" valign="top"></td>
					<td width="49%" valign="top">Present Address</td>
					<td><span class="data">:'.$occupier->present_address.'</span></td>
				 </tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>
				    <td width="2%" valign="top"></td>
					<td width="49%" valign="top">P.S</td>
					<td><span class="data">:'.$occupier_address['name_of_police_station'].'</span></td>
				 </tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>
				    <td width="2%" valign="top"></td>
					<td width="49%" valign="top">Permanent Address</td>
					<td><span class="data">:'.$address_of_occupier.'</span></td>
				 </tr>
				  <tr><td colspan="3">&nbsp;</td></tr>
				  <tr>
				    <td width="2%" valign="top"></td>
					<td width="49%" valign="top">P.S</td>
					<td><span class="data">:'.$occupier_address['name_of_police_station'].'</span></td>
				 </tr>
				 <tr><td colspan="3">&nbsp;</td></tr>';
				  
			}
			
			foreach($power_detials_year as $power){
				$type_power = $power->type_power_station;
				$installed_power = $power->installed_power.'('.$power->power_unit.')';
				$changedate = date('dS M Y', strtotime($power->change_date));
				$installed_power_kw = $power->installed_power;
				}
			if($type_power == "other"){
	$content .= '<tr>
				    <td width="2%" valign="top">9.</td>
					<td width="49%" valign="top">(a) Nature and total amount of power installed or proposed to be installed (Total rated H. P. In all cases except electricity generating station) - </td>
					<td><span class="data">:'.$installed_power.'</span></td>
				 </tr>
				  <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>
				    <td width="2%" valign="top"></td>
					<td width="49%" valign="top">(b) In case of change in power installed state the date of change- </td>
					<td><span class="data">:'.$changedate.'</span></td>
				 </tr>
				  <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>
				    <td width="2%" valign="top"></td>
					<td width="49%" valign="top">(c) Total generating capacity in KW(In case of generating station)</td>
					<td><span class="data">:'.$installed_power_kw.'KW </span></td>
				 </tr> <tr><td colspan="3">&nbsp;</td></tr>';
				 }else{
	$content .= '<tr>
				    <td width="2%" valign="top">9.</td>
					<td width="49%" valign="top">(a) Nature and total amount of power installed or proposed to be installed (Total rated H. P. In all cases except electricity generating station) - </td>
					<td><span class="data">:'.$installed_power.'</span></td>
				 </tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>
				    <td width="2%" valign="top"></td>
					<td width="49%" valign="top">(b) In case of change in power installed state the date of change- </td>
					<td><span class="data">:'.$changedate.'</span></td>
				 </tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>
				    <td width="2%" valign="top"></td>
					<td width="49%" valign="top">(c) Total generating capacity in KW(In case of generating station)</td>
					<td><span class="data">:'.$installed_power_kw.'KW </span></td>
				 </tr>';
				 }
				 
	$content .='<tr><td colspan="3">&nbsp;</td></tr>
				<tr>
				    <td width="3%" valign="top">10</td>
					<td width="49%" valign="top">.Maximum number of workers(including staff, officers,contract labour etc.)likely to be employed in the factory on any day during the period of next twelve months</td>
					<td><span class="data">:</span></td>
				 </tr>';
				 foreach($worker_detials_year as $worker){
	$content .= '<tr>	
				    <td width="2%" valign="top"></td>
					<td width="49%" valign="top">(i) Men: '.$worker->worker_men.'</td>
					<td width="49%" valign="top">(ii) Women: '.$worker->worker_women.'</td>
				 </tr>
				  <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>	
				    <td width="2%" valign="top"></td>
					<td width="49%" valign="top">(iii) Adolescents (over 15 but 18 years of age):</td>
					<td width="49%" valign="top"></td>
				 </tr>
				  <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>	
				    <td width="2%" valign="top"></td>
					<td width="49%" valign="top">(a) Male: '.$worker->adolescents_male.'</td>
					<td width="49%" valign="top">(b) Female: '.$worker->adolescents_female.'</td>
				 </tr>
				  <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>	
				    <td width="2%" valign="top"></td>
					<td width="49%" valign="top">(iii).Children (over 14 but 15 years of age):</td>
					<td width="49%" valign="top"></td>
				 </tr>
				  <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>	
				    <td width="2%" valign="top"></td>
					<td width="49%" valign="top">(a) Male: '.$worker->children_male.'</td>
					<td width="49%" valign="top">(b) Female: '.$worker->children_female.'</td>
				 </tr>
				 <tr>	
				    <td width="2%" valign="top"></td>
					<td width="49%" valign="top"></td>
					<td width="49%" valign="top">Total: '.$worker->worker_total.'</td>
				 </tr>';
				 }
	$content .= '<tr><td colspan="3">&nbsp;</td></tr>
				 <tr>	
				    <td width="3%" valign="top">11</td>
					<td width="49%" valign="top">(a) Maximum number of workers(including staff, officers,contract labour etc.)likely to be employed in the factory on any day during the period of previous twelve months</td>
					<td width="48%" valign="top"><span class="data">: '. $previous_year_worker['worker_total'].'</span></td>
				 </tr>
				  <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>	
				    <td width="3%" valign="top"></td>
					<td width="49%" valign="top">(b) In case of change in number of workers, state the date of change</td>
					<td width="48%" valign="top"><span class="data">: '.date('dS M Y', strtotime($previous_year_worker['change_date'])).'</span></td>
				 </tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>	
				    <td width="3%" valign="top">12</td>
					<td width="49%" valign="top"> In case of a factory constructed or extended or taken into use after the date of commencement of the Rules - </td>
					<td width="48%" valign="top"></td>
				 </tr>
				  <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>	
				    <td width="3%" valign="top"></td>
					<td width="49%" valign="top">(a).Refrence number and date of approval of plans by the State Goverment/Chief Inspector</td>
					<td width="48%" valign="top">Refrence number: <span class="data">'.$plan_approval_no.'</span><br/>Date of approval: <span class="data">'.$plan_approval_date.'</span></td>
				 </tr>
				  <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>	
				    <td width="3%" valign="top"></td>
					<td width="49%" valign="top">(b).Reference number and date of approval of the arrangements, if any, made for disposal of trade waste and effluents</td>
					<td width="48%" valign="top">Reference number: <span class="data">'.$get_all_data['wbpcb_reference_no'].'</span><br/>Date of approval: <span class="data">'.date('dS M Y', strtotime($get_all_data['wbpcb_ref_date'])).'<span></td>
				 </tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>	
				    <td width="3%" valign="top">13 </td>
					<td width="97%" valign="top" colspan="2"> Amount of fee/renewal fee <span class="data">:  &#x20b9;&nbsp;'.$get_all_data['payment_amount'].'</span> (Rupees...................... Treasury/Bank on ..................(Vide Challan No......................... Date..................... enclosed) for the year/years ending on '.date('dS M Y', strtotime($fetch_year_details['calculate_end_year'])).'</td>
					
				 </tr>
				  <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>	
				    <td width="3%" valign="top">14 </td>
					<td width="97%" valign="top" colspan="2">In Case of registered factories, number and date of issue of original licence:</td>
				 </tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>	
				    <td width="3%" valign="top"></td>
					<td width="49%" valign="top">(a) Licence No: </td>
					<td width="48%" valign="top">(b) Date of issue: </td>
				 </tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>	
				    <td align="left" valign="top" colspan="2">..................................................</td>
					<td align="right" valign="top">........................................................</td>
				 </tr>
				 <tr>	
				    <td align ="left" valign="top" colspan="2">Signature of Manager</td>
					<td align ="right" valign="top">Signature of occupier</td>
				 </tr>
				 <tr>	
				    <td align ="left" valign="top" colspan="2">(Full name of manager in <br/>Block letters should be started)</td>
					<td align ="right" valign="top">(Full name of occupier in <br/>Block letters should be started)</td>
				 </tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3"><hr></td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 </table>';
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr>	
				    <td width="8%" valign="top">NOTE:</td>
					<td width="92%" valign="top" colspan="2">(i) `Occupier` of a factory means the person who has ultimate control over the affairs of the factory as defined under the provisions of the section 2(n) of the Factories Act, 1948 as amended by the Factories (Amendment) Act, 1987.</td>
				 </tr>
				 <tr>	
				    <td width="8%" valign="top"></td>
					<td width="92%" valign="top" colspan="2">(ii) Information not included above may be submitted in separate sheets, if nessary.</td>
				 </tr>
				</table>';	
			 
   // echo $content; die;
	
	
/*	$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 20, 10, 0, 0);
	//$mpdf = new mPDF('utf-8', 'A4', '', '', 0, 0, 0, 0, 0, 0);
	$mpdf->SetDisplayMode('fullpage');
	//$mpdf->list_indent_first_level = 1;
	//$mpdf->setHeader($arr);
	$mpdf->SetHTMLHeader('
	<div style="padding-top:50px; text-align: right; font-size:9px;">
		Page {PAGENO} of {nb}
	</div>');
	//$mpdf->setFooter("Page {PAGENO} of {nb}";
	//$mpdf->defaultfooterline=0;
	//$mpdf->SetWatermarkText('Common Application Form',0.1);
	$mpdf->showWatermarkText = true;
	//$mpdf->SetWatermarkImage($base_root.$base_path.'sites/all/modules/custom/common_pdf_generator/logo.png');
	//$mpdf->showWatermarkImage = true;
	
	$mpdf->WriteHTML($content);
	//$mpdf->AddPage('A4-L','','','','',20,20,20,20,0,0);
	//$mpdf->WriteHTML($document);
	$mpdf->Output('Form-2-'._.time().'.pdf', 'D');
	//db_query("UPDATE fa_cafa SET download_status = 1 where id = ".$application_id);*/
	
	return pdf_using_mpdf_api($content,$fetch_year_details['calculate_end_year']._.time(),'d');
}


?>