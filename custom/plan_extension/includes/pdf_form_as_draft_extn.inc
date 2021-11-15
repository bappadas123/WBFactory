﻿<?php
global $base_root, $base_path, $user;
require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';

function pdf_form_as_draft_extn($applicationid='' ,$referenceid ='' ,$serviceid ='' ,$factorytype =''){

	$application_id 	 		= encryption_decryption_fun('decrypt', $applicationid);
	$reference_id 		 		= encryption_decryption_fun('decrypt', $referenceid);
	$service_id 		 		= encryption_decryption_fun('decrypt', $serviceid);
	$factory_type_id 	 		= encryption_decryption_fun('decrypt', $factorytype);
	$di = $pa = $pr = $no = '';

	if(empty($reference_id)) {$reference_id = 0;}
	$get_all_data 				= get_application_withid($application_id);
	$get_fa_occupier    		= get_all_occupier_data($application_id,$service_id,$factory_type_id,$reference_id); //echo "<pre>";print_r($get_fa_occupier);exit;
	
	$name_of_factory 			= ($get_all_data[0]->factory_name)? $get_all_data[0]->factory_name : ''; //die;
	$factory_previous_name  	= ($get_all_data[0]->factory_previous_name)? $get_all_data[0]->factory_previous_name : '';
	$nearest_landmark  			= ($get_all_data[0]->nearest_landmark)? $get_all_data[0]->nearest_landmark : '';

	// FACTORY ADDRESS //
	$getdata_factory_address 	=  	array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address 			=	get_parts_address('fa_cafa','sub-table',$application_id,$getdata_factory_address);

	$address_line_factory    	= ($get_all_data[0]->addrline)? $get_all_data[0]->addrline : ''; 
	$post_office_factory     	= ($factory_address['po_name'])? $factory_address['po_name'] : ''; 
	$pin_code_factory        	= ($factory_address['pincode'])? $factory_address['pincode'] : ''; 
	$sub_division_factory    	= ($factory_address['sub_div_name'])? $factory_address['sub_div_name'] : ''; 
	$district_factory        	= ($factory_address['district_name'])? $factory_address['district_name'] : ''; 
	$police_station_factory  	= ($factory_address['name_of_police_station'])? $factory_address['name_of_police_station'] : ''; 
	
	// REGISTERED/HEAD OFFICE //
	$getdata_headoffice_address = array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
	//$headoffice_address       = get_full_address('fa_cafa','sub-table',$application_id,$getdata_headoffice_address);
	$headoffice_address         = get_parts_address('fa_cafa','sub-table',$application_id,$getdata_headoffice_address);

	$address_line_headoffice    = ($get_all_data[0]->addrline_off)? $get_all_data[0]->addrline_off : '';
	$post_office_headoffice     	= ($headoffice_address['po_name'])? $headoffice_address['po_name'] : ''; 
	$pin_code_headoffice        	= ($headoffice_address['pincodeoff'])? $headoffice_address['pincodeoff'] : ''; 
	$sub_division_headoffice    	= ($headoffice_address['sub_div_name'])? $headoffice_address['sub_div_name'] : ''; 
	$district_headoffice        	= ($headoffice_address['district_name'])? $headoffice_address['district_name'] : ''; 
	$police_station_headoffice  	= ($headoffice_address['name_of_police_station'])? $headoffice_address['name_of_police_station'] : ''; 

	// COMMUNICATION ADDRESS //
	$getdata_communication_address  = array('district_comm','subdivision_comm','areatype_comm','block_comm','panchayat_comm','policestation_comm','pincodecomm','state_comm','postoffice_comm');
	$communication_address          = get_parts_address('fa_cafa','sub-table',$application_id,$getdata_communication_address);

	$address_line_communication    	= ($get_all_data[0]->addrline_comm)? $get_all_data[0]->addrline_comm : ''; 
	$post_office_communication     	= ($communication_address['po_name'])? $communication_address['po_name'] : ''; 
	$pin_code_communication        	= ($communication_address['pincodecomm'])? $communication_address['pincodecomm'] : ''; 
	$sub_division_communication   	= ($communication_address['sub_div_name'])? $communication_address['sub_div_name'] : ''; 
	$district_communication        	= ($communication_address['district_name'])? $communication_address['district_name'] : ''; 
	$police_station_communication 	= ($communication_address['name_of_police_station'])? $communication_address['name_of_police_station'] : ''; 

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
	
	// PREMISES OWNER DETAILS
	$getdata_premises_address 	    = array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
	$premises_address  			    = get_parts_address('fa_cafa','sub-table',$application_id,$getdata_premises_address);

	$address_line_premises 		    = ($get_all_data[0]->addrline_premises)? $get_all_data[0]->addrline_premises : '';
	$post_office_premises     	= ($premises_address['po_name'])? $premises_address['po_name'] : '';
	$pin_code_premises       	= ($premises_address['pincodepremises'])? $premises_address['pincodepremises'] : ''; 
	$sub_division_premises   	= ($premises_address['sub_div_name'])? $premises_address['sub_div_name'] : ''; 
	$district_premises        	= ($premises_address['district_name'])? $premises_address['district_name'] : ''; 
	$police_station_premises 	= ($premises_address['name_of_police_station'])? $premises_address['name_of_police_station'] : ''; 
	$aadhaar_premises 		    = ($get_all_data[0]->aadhaar_premises)? $get_all_data[0]->aadhaar_premises : '';
	$passport_premises 		    = ($get_all_data[0]->passport_premises)? $get_all_data[0]->passport_premises : '';
	$passport_date_of_issue_premises  = ($get_all_data[0]->passport_date_of_issue_premises)? $get_all_data[0]->passport_date_of_issue_premises : '';
	$passport_date_of_expiry_premises = ($get_all_data[0]->passport_date_of_expiry_premises)? $get_all_data[0]->passport_date_of_expiry_premises : '';
	$mouza_name 				= ($get_all_data[0]->mouza_name)? $get_all_data[0]->mouza_name : '';
	$jl_no					 	= ($get_all_data[0]->jl_no)? $get_all_data[0]->jl_no : '';

	$factory_pan      			= ($get_all_data[0]->factory_pan)? $get_all_data[0]->factory_pan	 : '';
	$gstin_no					= ($get_all_data[0]->gstin_no)? $get_all_data[0]->gstin_no	 : '';
	$udyog_aadhaar			 	= ($get_all_data[0]->udyog_aadhaar)? $get_all_data[0]->udyog_aadhaar	 : '';			
	$trade_license_no			= ($get_all_data[0]->trade_license_no)? $get_all_data[0]->trade_license_no	 : '';
	$enargy_no					= ($get_all_data[0]->enargy_no)? $get_all_data[0]->enargy_no	 : '';
	$cin_no						= ($get_all_data[0]->cin_no)? $get_all_data[0]->cin_no	 : '';

	$comm_telephone   			= ($get_all_data[0]->comm_telephone)? $get_all_data[0]->comm_telephone	 : '';
	$comm_mobile      			= ($get_all_data[0]->comm_mobile)? $get_all_data[0]->comm_mobile	 : '';
	$comm_alt_mobile      		= ($get_all_data[0]->comm_alt_mobile)? $get_all_data[0]->comm_alt_mobile	 : '';
	$comm_fax         			= ($get_all_data[0]->comm_fax)? $get_all_data[0]->comm_fax	 : '';
	$comm_email       			= ($get_all_data[0]->comm_email)? $get_all_data[0]->comm_email	 : '';
	
	$occupiername           	= $get_fa_occupier[0]->name_occupier.' '.$get_fa_occupier[0]->occupier_name_middle.' '.$get_fa_occupier[0]->occupier_name_last;
	$occupier_name          	= ($occupiername)? $occupiername : '';
	$occupier_mobile        	= ($get_fa_occupier[0]->occupier_mobile)? $get_fa_occupier[0]->occupier_mobile	 : '';
	$occupier_email_id      	= ($get_fa_occupier[0]->occupier_email_id)? $get_fa_occupier[0]->occupier_email_id	 : '';
	$occupier_age     			= ($get_fa_occupier[0]->age_occupier)? $get_fa_occupier[0]->age_occupier	 : '';
	$occupier_gurdian_name  	= ($get_fa_occupier[0]->father_husband_name_occupier)? $get_fa_occupier[0]->father_husband_name_occupier	 : '';
	$occupier_fax_no        	= ($get_fa_occupier[0]->occupier_fax_no)? $get_fa_occupier[0]->occupier_fax_no	 : '';
	$occupier_telephone     	= ($get_fa_occupier[0]->occupier_telephone)? $get_fa_occupier[0]->occupier_telephone	 : '';
	$occupier_type          	= ($get_fa_occupier[0]->type_occupier)? $get_fa_occupier[0]->type_occupier	 : ''; 
	$ownername 					= $get_all_data[0]->owner_name.' '.$get_all_data[0]->owner_mname.' '.$get_all_data[0]->owner_lname;
	$owner_name             	= ($ownername)? $ownername : '';
	
	$plant_installed        	= ($get_all_data[0]->plant_installed)? $get_all_data[0]->plant_installed	 : '';
	
	//$wbpcb_category_name        = ($get_all_data[0]->wbpcb_category_name)? $get_all_data[0]->wbpcb_category_name	 : '';
	
	if($get_all_data[0]->wbpcb_category_name ==1){$wbpcb_category_name ='Red';}
	if($get_all_data[0]->wbpcb_category_name ==2){$wbpcb_category_name ='Green';}
	if($get_all_data[0]->wbpcb_category_name ==3){$wbpcb_category_name ='Orange';}
	if($get_all_data[0]->wbpcb_category_name ==4){$wbpcb_category_name ='White';}	
	
	$wbpcb_reference_no        	= ($get_all_data[0]->wbpcb_reference_no)? $get_all_data[0]->wbpcb_reference_no	 : '';
	$wbpcb_ref_date        		= ($get_all_data[0]->wbpcb_ref_date)? $get_all_data[0]->wbpcb_ref_date	 : '';

	if($occupier_type == 'Director'){ $di = '&radic;'; } 
	elseif($occupier_type == 'Partner'){ $pa = '&radic;'; }
	elseif($occupier_type == 'Proptietor'){ $pr = '&radic;'; }
	elseif($occupier_type == 'Nominated'){ $no = '&radic;'; }
		 
	$attached_filename = get_attached_filename($application_id,$reference_id,$factory_type_id,$service_id);
	$worker_details = get_worker_detials($application_id);//,$reference_id

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
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>A. Factory Information</td></h4></tr>
				 <tr><td>&nbsp;</td></tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(i) Name of the factory </td>
					<td width="49%"><span class="data">: '.$name_of_factory.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(i) Previous Name of the factory </td>
					<td width="49%"><span class="data">: '.$factory_previous_name.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(ii) PAN of Business Establishment/Factory/Company </td>
					<td width="49%"><span class="data">: '.$factory_pan.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(iii) GSTIN Number </td>
					<td width="49%"><span class="data">: '.$gstin_no.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(iv) Udyog Aadhaar No </td>
					<td width="49%"><span class="data">: '.$udyog_aadhaar.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(v) Trade License No </td>
					<td width="49%"><span class="data">: '.$trade_license_no.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(vi) Energy Meter No </td>
					<td width="49%"><span class="data">: '.$enargy_no.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(vii) CIN No </td>
					<td width="49%"><span class="data">: '.$cin_no.'</span></td>
				 </tr>
				 </table>';

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>B. Location of the factory</td></h4></tr>
				 <tr><td>&nbsp;</td></tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(i) Address</td>
					<td width="49%"><span class="data">: '.$address_line_factory.'</span></td>
				</tr>

				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(ii) Post Office</td>
					<td width="49%"><span class="data">: '.$post_office_factory.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(iii) Pin Code</td>
					<td width="49%"><span class="data">: '.$pin_code_factory.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(iv) Sub Divisional Headquarter </td>
					<td width="25%"><span class="data">: '.$sub_division_factory.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(v) District </td>
					<td width="49%"><span class="data">: '.$district_factory.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(vi) Police Station </td>
					<td width="49%"><span class="data">: '.$police_station_factory.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(vii) Nearest Landmark </td>
					<td width="49%"><span class="data">: '.$nearest_landmark.'</span></td>
				</tr>
				</table>';
				
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>C. Address of the Registered office / Head office</td></h4></tr>
				 <tr><td>&nbsp;</td></tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(i) Address</td>
					<td width="49%"><span class="data">: '.$address_line_headoffice.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(ii) Post Office</td>
					<td width="49%"><span class="data">: '.$post_office_headoffice.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(iii) Pin Code</td>
					<td width="49%"><span class="data">: '.$pin_code_headoffice.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(iv) Sub Divisional Headquarter </td>
					<td width="25%"><span class="data">: '.$sub_division_headoffice.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(v) District </td>
					<td width="49%"><span class="data">: '.$district_headoffice.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(vi) Police Station </td>
					<td width="49%"><span class="data">: '.$police_station_headoffice.'</span></td>
				</tr>
				</table>';

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(vii) Telephone No. </td>
					<td width="49%"><span class="data">: '.$comm_telephone.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(viii) Mobile No. </td>
					<td width="49%"><span class="data">: '.$comm_mobile.'</span></td>
				 </tr></span>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(ix) Alternate Mobile No. </td>
					<td width="49%"><span class="data">: '.$comm_alt_mobile.'</span></td>
				 </tr></span>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(x) Fax No. </td>
					<td width="49%"><span class="data">: '.$comm_fax.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(xi) E-mail ID </td>
					<td width="49%"><b>: '.$comm_email.'</b></td>
				 </tr>
				</table>';

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>D. Communication Address</td></h4></tr>
				 <tr><td>&nbsp;</td></tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(i) Address</td>
					<td width="49%"><span class="data">: '.$address_line_communication.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(ii) Post Office</td>
					<td width="49%"><span class="data">: '.$post_office_communication.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(iii) Pin Code</td>
					<td width="49%"><span class="data">: '.$pin_code_communication.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(iv) Sub Divisional Headquarter </td>
					<td width="25%"><span class="data">: '.$sub_division_communication.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(v) District </td>
					<td width="49%"><span class="data">: '.$district_communication.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(vi) Police Station </td>
					<td width="49%"><span class="data">: '.$police_station_communication.'</span></td>
				</tr>
				</table>';
				 
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>E. Details of owner/land lord/lessor of the premises occupied as a factory</td></h4></tr>
				 <tr><td>&nbsp;</td></tr>
				<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(i) Name in full </td>
					<td width="49%"><span class="data">: '.$owner_name.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(ii) Nationality</td>
					<td width="49%"><span class="data">: '.country_name($get_all_data[0]->country_premises).'</span></td>
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
					<td width="49%" valign="top">(ix) Aadhar No. </td>
					<td width="49%"><span class="data">: '.$aadhaar_premises.'</span></td>
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
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(xi) Mouza Name </td>
					<td width="49%"><span class="data">: '.$mouza_name.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(xii) JL No. </td>
					<td width="49%"><span class="data">: '.$jl_no.'</span></td>
				</tr>
				</table>';

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>F. Particular of Plan to be installed</td></h4></tr>
				 <tr><td>&nbsp;</td></tr>
				<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(i) Plant To be Installed </td>
					<td width="49%"><span class="data">: '.$plant_installed.'</span></td>
				</tr>
				</table>';

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>G. Factory Identification according to WBPCB</td></h4></tr>
				 <tr><td>&nbsp;</td></tr>
				<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(i) Categories of wbpcb </td>
					<td width="49%"><span class="data">: '.$wbpcb_category_name.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(ii) Reference number of approval of arrangments</td>
					<td width="49%"><span class="data">: '.$wbpcb_reference_no.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(iii) Date of approval of arrangments </td>
					<td width="49%"><span class="data">: '.$wbpcb_ref_date.'</span></td>
				</tr>
				</table>';
	
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">				
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
	$mpdf->Output('General-Information-Extension-'.time().'.pdf', 'D');
}
?>