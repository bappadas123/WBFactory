<?php
global $base_url,$base_root, $base_path, $user;
require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';
function pdf_form_registration($applicationid='' ,$referenceid ='' ,$serviceid='' ,$factorytypeid =''){
	global $base_url,$base_root, $base_path, $user;
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$service_id 		= encryption_decryption_fun('decrypt', $serviceid);
	$factorytype_id 	= encryption_decryption_fun('decrypt', $factorytypeid);
	$year_id 			= encryption_decryption_fun('decrypt', $yearid);
	
	$get_all_data 		= get_application_withid($application_id);
	$ending_year 		= fetch_year_asc($application_id,$service_id,$factorytype_id,$reference_id);
	foreach($ending_year as $row){
		$ending_year = $row->calculate_end_year;
	}
	
	$get_fa_occupier    		= get_all_occupier_data($application_id,$service_id,$factorytype_id,$reference_id); //print_r($get_fa_occupier);die('previous');
	
	$name_of_factory 			= !empty($get_all_data[0]->factory_name)? $get_all_data[0]->factory_name : ''; //die;
	$factory_previous_name  	= !empty($get_all_data[0]->factory_previous_name)? $get_all_data[0]->factory_previous_name : '';
	$nearest_landmark  			= !empty($get_all_data[0]->nearest_landmark)? $get_all_data[0]->nearest_landmark : '';
	$factory_zone_name 			= !empty($get_all_data[0]->zone_name)? $get_all_data[0]->zone_name : '';
	$factory_zone_details 		= !empty($get_all_data[0]->zone_details)? $get_all_data[0]->zone_details : '';
	$estate_type 	  			= get_estate_type($get_all_data[0]->estate_type);

	// FACTORY ADDRESS //
	$getdata_factory_address 	=  	array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address 			=	get_parts_address('fa_cafa','sub-table',$application_id,$getdata_factory_address);

	$address_line_factory    	= !empty($get_all_data[0]->addrline)? $get_all_data[0]->addrline : ''; 
	$post_office_factory     	= !empty($factory_address['po_name'])? $factory_address['po_name'] : ''; 
	$pin_code_factory        	= !empty($factory_address['pincode'])? $factory_address['pincode'] : ''; 
	$sub_division_factory    	= !empty($factory_address['sub_div_name'])? $factory_address['sub_div_name'] : ''; 
	$district_factory        	= !empty($factory_address['district_name'])? $factory_address['district_name'] : ''; 
	$police_station_factory  	= !empty($factory_address['name_of_police_station'])? $factory_address['name_of_police_station'] : ''; 
	
	// REGISTERED/HEAD OFFICE //
	$getdata_headoffice_address = array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
	$headoffice_address       	= get_full_address('fa_cafa','sub-table',$application_id,$getdata_headoffice_address);
	//$headoffice_address         = get_parts_address('fa_cafa','sub-table',$application_id,$getdata_headoffice_address);

	$address_line_headoffice    	= !empty($get_all_data[0]->addrline_off)? $get_all_data[0]->addrline_off : '';
	$post_office_headoffice     	= !empty($headoffice_address['po_name'])? $headoffice_address['po_name'] : ''; 
	$pin_code_headoffice        	= !empty($headoffice_address['pincodeoff'])? $headoffice_address['pincodeoff'] : ''; 
	$sub_division_headoffice    	= !empty($headoffice_address['sub_div_name'])? $headoffice_address['sub_div_name'] : ''; 
	$district_headoffice        	= !empty($headoffice_address['district_name'])? $headoffice_address['district_name'] : ''; 
	$police_station_headoffice  	= !empty($headoffice_address['name_of_police_station'])? $headoffice_address['name_of_police_station'] : ''; 

	// COMMUNICATION ADDRESS //
	$getdata_communication_address  = array('district_comm','subdivision_comm','areatype_comm','block_comm','panchayat_comm','policestation_comm','pincodecomm','state_comm','postoffice_comm');
	$communication_address          = get_full_address('fa_cafa','sub-table',$application_id,$getdata_communication_address);
	//$communication_address		= get_parts_address('fa_cafa','sub-table',$application_id,$getdata_communication_address);

	$address_line_communication    	= !empty($get_all_data[0]->addrline_comm)? $get_all_data[0]->addrline_comm : ''; 
	$post_office_communication     	= !empty($communication_address['po_name'])? $communication_address['po_name'] : ''; 
	$pin_code_communication        	= !empty($communication_address['pincodecomm'])? $communication_address['pincodecomm'] : ''; 
	$sub_division_communication   	= !empty($communication_address['sub_div_name'])? $communication_address['sub_div_name'] : ''; 
	$district_communication        	= !empty($communication_address['district_name'])? $communication_address['district_name'] : ''; 
	$police_station_communication 	= !empty($communication_address['name_of_police_station'])? $communication_address['name_of_police_station'] : ''; 

	// OCCUPIER PERMANENT ADDRESS
	$getdata_permanent_address 	= array('district_oprmntadr','subdivision_oprmntadr','areatype_oprmntadr','block_oprmntadr','panchayat_oprmntadr','policestation_oprmntadr','pincodeoprmntadr','state_oprmntadr','postoffice_oprmntadr');
	$permanent_address_part    	= get_parts_address('fa_occupier_details','sub-table',$get_fa_occupier[0]->id,$getdata_permanent_address);
	if($get_fa_occupier[0]->country_oprmntadr == 99) 
	 { 
	   $permanent_address        = get_full_address('fa_occupier_details','sub-table',$get_fa_occupier[0]->id,$getdata_permanent_address);
	   $police_station_permanent = !empty($permanent_address_part['name_of_police_station'])? $permanent_address_part['name_of_police_station'] : '';
	 } else { 
	   $permanent_address        = $get_fa_occupier[0]->street_name_oprmntadr.','.$get_fa_occupier[0]->house_no_oprmntadr;
	   $police_station_permanent = !empty($get_fa_occupier[0]->police_station_oprmntadr)? $get_fa_occupier[0]->police_station_oprmntadr : '';
	 }  
	$address_line_permanent    	 = !empty($get_fa_occupier[0]->addrline_oprmntadr)? $get_fa_occupier[0]->addrline_oprmntadr : '';
	
	
	// OCCUPIER PRESENT ADDRESS
	$getdata_present_address 	= array('district_oprsntadr','subdivision_oprsntadr','areatype_oprsntadr','block_oprsntadr','panchayat_oprsntadr','policestation_oprsntadr','pincodeoprsntadr','state_oprsntadr','postoffice_oprsntadr');
	$present_address_part    	= get_parts_address('fa_occupier_details','sub-table',$get_fa_occupier[0]->id,$getdata_present_address);
	if($get_fa_occupier[0]->country_oprsntadr == 99) 
	  {	
	    $present_address  		=  get_full_address('fa_occupier_details','sub-table',$get_fa_occupier[0]->id,$getdata_present_address);
	  	$police_station_present = !empty($present_address_part['name_of_police_station'])? $present_address_part['name_of_police_station'] : '';
	  } else { 
	    $present_address  		= $get_fa_occupier[0]->street_name_oprsntadr.','.$get_fa_occupier[0]->house_no_oprsntadr;
	  	$police_station_present = !empty($get_fa_occupier[0]->police_station_oprsntadr)? $get_fa_occupier[0]->police_station_oprsntadr : '';
	  }  
	$address_line_present 		= !empty($get_fa_occupier[0]->addrline_oprsntadr)? $get_fa_occupier[0]->addrline_oprsntadr : '';
	
	// PREMISES OWNER DETAILS
	$getdata_premises_address 	    = array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
	$premises_address  			    = get_parts_address('fa_cafa','sub-table',$application_id,$getdata_premises_address);

	$address_line_premises		= !empty($get_all_data[0]->addrline_premises)? $get_all_data[0]->addrline_premises : '';
	$post_office_premises     	= !empty($premises_address['po_name'])? $premises_address['po_name'] : '';
	$pin_code_premises       	= !empty($premises_address['pincodepremises'])? $premises_address['pincodepremises'] : ''; 
	$sub_division_premises   	= !empty($premises_address['sub_div_name'])? $premises_address['sub_div_name'] : ''; 
	$district_premises        	= !empty($premises_address['district_name'])? $premises_address['district_name'] : ''; 
	$police_station_premises 	= !empty($premises_address['name_of_police_station'])? $premises_address['name_of_police_station'] : ''; 
	$aadhaar_premises 		    = !empty($get_all_data[0]->aadhaar_premises)? $get_all_data[0]->aadhaar_premises : '';
	$passport_premises 		    = !empty($get_all_data[0]->passport_premises)? $get_all_data[0]->passport_premises : '';
	$passport_date_of_issue_premises  = !empty($get_all_data[0]->passport_date_of_issue_premises)? $get_all_data[0]->passport_date_of_issue_premises : '';
	$passport_date_of_expiry_premises = !empty($get_all_data[0]->passport_date_of_expiry_premises)? $get_all_data[0]->passport_date_of_expiry_premises : '';
	$mouza_name 				= !empty($get_all_data[0]->mouza_name)? $get_all_data[0]->mouza_name : '';
	$jl_no					 	= !empty($get_all_data[0]->jl_no)? $get_all_data[0]->jl_no : '';

	$factory_pan      			= !empty($get_all_data[0]->factory_pan)? $get_all_data[0]->factory_pan	 : '';
	$gstin_no					= !empty($get_all_data[0]->gstin_no)? $get_all_data[0]->gstin_no	 : '';
	$udyog_aadhaar			 	= !empty($get_all_data[0]->udyog_aadhaar)? $get_all_data[0]->udyog_aadhaar	 : '';			
	$trade_license_no			= !empty($get_all_data[0]->trade_license_no)? $get_all_data[0]->trade_license_no	 : '';
	$enargy_no					= !empty($get_all_data[0]->enargy_no)? $get_all_data[0]->enargy_no	 : '';
	$cin_no						= !empty($get_all_data[0]->cin_no)? $get_all_data[0]->cin_no	 : '';

	$comm_telephone   			= !empty($get_all_data[0]->comm_telephone)? $get_all_data[0]->comm_telephone	 : '';
	$comm_mobile      			= !empty($get_all_data[0]->comm_mobile)? $get_all_data[0]->comm_mobile	 : '';
	$comm_fax         			= !empty($get_all_data[0]->comm_fax)? $get_all_data[0]->comm_fax	 : '';
	$comm_email       			= !empty($get_all_data[0]->comm_email)? $get_all_data[0]->comm_email	 : '';
	
	$occupiername           	= $get_fa_occupier[0]->name_occupier.' '.$get_fa_occupier[0]->occupier_name_middle.' '.$get_fa_occupier[0]->occupier_name_last;
	$occupier_name          	= !empty($occupiername)? $occupiername : '';
	$occupier_mobile        	= !empty($get_fa_occupier[0]->occupier_mobile)? $get_fa_occupier[0]->occupier_mobile	 : '';
	$occupier_email_id      	= !empty($get_fa_occupier[0]->occupier_email_id)? $get_fa_occupier[0]->occupier_email_id	 : '';
	$occupier_age     			= !empty($get_fa_occupier[0]->age_occupier)? $get_fa_occupier[0]->age_occupier	 : '';
	$occupier_gurdian_name  	= !empty($get_fa_occupier[0]->father_husband_name_occupier)? $get_fa_occupier[0]->father_husband_name_occupier	 : '';
	$occupier_fax_no        	= !empty($get_fa_occupier[0]->occupier_fax_no)? $get_fa_occupier[0]->occupier_fax_no	 : '';
	$occupier_telephone     	= !empty($get_fa_occupier[0]->occupier_telephone)? $get_fa_occupier[0]->occupier_telephone	 : '';
	$occupier_type          	= !empty($get_fa_occupier[0]->type_occupier)? $get_fa_occupier[0]->type_occupier	 : ''; 
	$ownername 					= $get_all_data[0]->owner_name.' '.$get_all_data[0]->owner_mname.' '.$get_all_data[0]->owner_lname;
	$owner_name             	= !empty($ownername)? $ownername : '';
	
	
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
	//$worker_details = get_worker_detials($application_id);//,$reference_id
	
	//print_r($get_all_data);die();
	$is_backlog			= $get_all_data[0]->is_backlog;
	$previous_name		= $get_all_data[0]->factory_previous_name;
	$classification_no	= !empty($get_all_data[0]->classification_no)?$get_all_data[0]->classification_no:'N/A';
	$blacklog_registration_no = !empty($get_all_data[0]->backlog_registration_no)? $get_all_data[0]->backlog_registration_no:'N/A';
	$plan_registration_number	= !empty($get_all_data[0]->factory_registrstion_no)? $get_all_data[0]->factory_registrstion_no:$blacklog_registration_no;
	
	$blacklog_license_date = !empty($get_all_data[0]->backlog_license_date)? $get_all_data[0]->backlog_license_date:'N/A';
	$plan_license_date 		= !empty($get_all_data[0]->license_date)? $get_all_data[0]->license_date:$blacklog_license_date;
	if($plan_license_date !='N/A'){
		$plan_license_date = date('dS M Y', strtotime($plan_license_date));
	}else{
		$plan_license_date = 'N/A';
		}
	
	$blacklog_license_no = !empty($get_all_data[0]->backlog_license_number)? $get_all_data[0]->backlog_license_number:'N/A';
	$plan_licesne_number	= !empty($get_all_data[0]->factory_license_no)? $get_all_data[0]->factory_license_no:$blacklog_license_no;
	if($is_backlog == 1){
		$plan_approval_no 	= $get_all_data[0]->backlog_plan_approval_no;
		$plan_approval_date = date('dS M Y', strtotime($get_all_data[0]->backlog_plan_approval_date));
	}if($is_backlog != 1){
		$plan_approval_no 	= $get_all_data[0]->factory_plan_approval_number;
		$plan_approval_date = date('dS M Y', strtotime($get_all_data[0]->plan_approval_date));
	}
	if($get_all_data[0]->wbpcb_category_name==1){$consent ='Red';}
	if($get_all_data[0]->wbpcb_category_name==2){$consent ='Green';}
	if($get_all_data[0]->wbpcb_category_name==3){$consent ='Orange';}
	if($get_all_data[0]->wbpcb_category_name==4){$consent ='White';}
	if($get_all_data[0]->wbpcb_category_name==5){$consent ='Exempted';}
	
	//$previous_name				= fetch_previous_calid($application_id,$reference_id,$factorytype_id,$service_id);
	//print_r($previous_name);die();
	$getdata_factory_address  	= array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address 		    = get_parts_address('fa_cafa','sub-table',$application_id,$getdata_factory_address);
	
	$getdata_headoffice_address = array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
	$headoffice_address 		= $get_all_data[0]->addrline_off.',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data[0]->id,$getdata_headoffice_address);
	
	
	//$address_line_present='hfg';
	
	if( !empty($get_all_data[0]->country_premises)){
		$owner_address_details = $get_all_data[0]->factory_country_address.',<br/>'.country_name($get_all_data[0]->country_premises);
		$getdata_owner_address 	= array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
		$premises_address 			= $owner_address_details.',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data[0]->id,$getdata_owner_address);
		
		}elseif(!empty($get_all_data[0]->country_code)){
			
			$owner_address_details = $get_all_data[0]->factory_country_address.',<br/>'.country_name($get_all_data[0]->country_code);
			$getdata_owner_address 	= array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
			$premises_address 			= $owner_address_details.',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data[0]->id,$getdata_owner_address);
			

			}elseif(!empty($get_all_data[0]->owner_country)){
				
				$owner_address_details = $get_all_data[0]->factory_country_address.',<br/>'.country_name($get_all_data[0]->owner_country);
				$getdata_owner_address 	= array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
				$premises_address 			= $owner_address_details.',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data[0]->id,$getdata_owner_address);
				
				}else{
					$getdata_premises_address 	= array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
					$premises_address  			= $get_all_data[0]->addrline_premises.' '.get_full_address('fa_cafa','sub-table',$application_id,$getdata_premises_address);
				}
	
	
	$manufacturing_detials_year = nature_manufacturing_year($fetch_year_details[0]->calculate_year,$application_id,$reference_id,$factorytype_id,$service_id);
	$manager_details 			= get_all_manager_data($application_id,$service_id,$factorytype_id,$reference_id);
	//$power_detials_year 		= power_detials_year($year_id="",$application_id,$reference_id,$factorytype_id,$service_id);
	$power_detials_year 		= get_power_generating_station($application_id,$reference_id,$factorytype_id,$service_id);
	$worker_details 			= get_worker_details_service($service_id,$factorytype_id,$application_id,$reference_id);
	$director_details			= get_director_details_service($application_id,$service_id,$factorytype_id,$reference_id,$year_id="");
	$manual_payment 			= manual_payment_deatils($application_id,$service_id,$factorytype_id,$reference_id);
	//print_r($power_detials_year);die;
	
	if(!empty($power_detials_year)){
		foreach($power_detials_year as $row_power){
			$power_installed = $row_power->installed_power .'( '.$row_power->power_unit.')';
			$type_power_station = $row_power->type_power_station;
			
		}
	}else{
		$power_installed ='None';
	}

	$plant_installed      	= !empty($manufacturing_detials_year[0]->nature_manufacturing)? $manufacturing_detials_year[0]->nature_manufacturing : 'N/A';
	

	if($manager_details[0]->relationship_manager == '1'){
		$relationship = 'D/O';
	}if($manager_details[0]->relationship_manager == '2'){
		$relationship = 'S/O';
	}if($manager_details[0]->relationship_manager == '3'){
		$relationship = 'W/O';
	}
	$fieldArr_manager		=  array('district_manager','sub_division_manager','area_type_manager','block_mun_cor_sez_not_manager','grm_ward_sector_not_manager','police_station_manager','pincode_manager','state_manager','post_office_manager');
	$address_of_manager		= $manager_details[0]->adress_line1_manager.' '.get_full_address('fa_manager_details','sub-table',$manager_details[0]->id,$fieldArr_manager);
	$manager_details_view	= $manager_details[0]->name_manager.' ' .$relationship.'-'.$manager_details[0]->father_husband_name_manager.'<b>Age</b>:-'.$manager_details[0]->age_manager;
	
	if(!empty($director_details[0]->din_director)){$din = 'DIN:-'.$director_details[0]->din_director;}	
	$type = $director_details[0]->type_director;
	if($type=='ltd' || $type=='pv'){$director_type = 'Director';}
	if($type == 'par_firm'){$director_type 	= 'Partner';}
	if($type == 'pro_firm'){$director_type 	= 'Proprietor';}
	if($type == 'govt' || $type == 'psu' || $type == 'others'){$director_type 	= 'Nominated Occupier';}
	if(!empty($director_details[0]->age_director)){$age = 'Age- '.$director_details[0]->age_director;}
	$is_occupier = $director_details[0]->is_occupier;
	$relation = $director_details[0]->relationship_director;
	 if($relation == 1){$relationship = 'D/O';}
	 if($relation == 2){$relationship = 'S/O';}
	 if($relation == 3){$relationship = 'W/O';}
	 if($is_occupier == 1){$occupier = ' <br/>(Occupier)';}
	 else{$occupier = '';}
	
	$fieldArr_director	=  array('district_director','sub_division_director','area_type_director','block_mun_cor_sez_not_director','grm_ward_sector_not_director','police_station_director','pincode_director','state_director','post_office_director');
	$address_of_director =	$director_details[0]->adress_line1_director.' '.get_full_address('fa_director_details','sub-table',$director_details[0]->id,$fieldArr_director);
	
	if($service_id==2){
		$application_name = 'Registration & Grant of Licence';
	}elseif($service_id==3){
		$application_name = 'Renewal of Licence';
	}
	if($get_all_data[0]->application_status != 'In')
	{
		db_query("UPDATE {fa_cafa} SET download_status = 1 where id = ".$application_id);
	}
	$img_url  = $_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/themes/wbfactories/images/em.jpg';
	$content = '<style type="text/css">
				.watermark{
					 

					}
					table, td, th {
							font-size:12px;
							font-family:Times New Roman;
							height:15px;
							color:#000;
							
							
					}
					table, td, th {}
					
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
					.address{
						font-size:13px;
						color:#2d2d2d;
						font-family:Arial, Helvetica, sans-serif;
					}
					.address span{font-size:10px;}
					table td{ padding:3px; font-size:12px; colo}
					
			</style>';
	$content .= '
	<fieldset style="font-family: Arial, Open Sans; padding: 20px;">
         <div style="width:100%;">
	<table width="100%" border="0" cellspacing="0" cellpadding="5">				
					<tr><td colspan="3"></td></tr>
					<tr><td colspan="3" align="center"><img src="'.$_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/themes/wbfactories/certificate/factories-logo.png" width="" height="" alt="" /></td></tr>
					<tr><td colspan="3" align="center" class="address;"><b>NEW SECRETARIAT BUILDINGS (8th floor)</b><br/> <span>1, KIRON SANKAR ROY ROAD, KOLKATA -700001<span></td></tr>
					
					<tr><td colspan="3">&nbsp;</td></tr>				
					<tr><td colspan="3" align="center" style="font-size:22px;color:#0b3f88;"><strong>APPLICATION FOR<br/>'.$application_name.'</strong></td></tr>
					</table>';

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>A. Factory Information</td></h4></tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(i) Name of the factory </td>
					<td width="49%"><span class="data">: '.$name_of_factory.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%"  valign="top">&nbsp;</td>
					<td width="49%" valign="top">(ii) Previous Name of the Factory (if different from the present name) </td>
					<td width="49%"><span class="data">: '.$factory_previous_name.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(iii) PAN of Business Establishment/Factory/Company </td>
					<td width="49%"><span class="data">: '.$factory_pan.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(iv) GSTIN Number </td>
					<td width="49%"><span class="data">: '.$gstin_no.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(v) Udyog Aadhaar No </td>
					<td width="49%"><span class="data">: '.$udyog_aadhaar.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(vi) Trade License No </td>
					<td width="49%"><span class="data">: '.$trade_license_no.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(vii) Energy Meter No </td>
					<td width="49%"><span class="data">: '.$enargy_no.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(viii) CIN No </td>
					<td width="49%"><span class="data">: '.$cin_no.'</span></td>
				 </tr>
				 </table>';

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>B. Location of the factory</td></h4></tr>
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
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(viii) Estate Type </td>
					<td width="49%"><span class="data">: '.$estate_type[0]->estate_name.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(ix) Zone </td>
					<td width="49%">: '.$factory_zone_name.'</td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top" colspan="2"></td>
				</tr>

				</table>';
				
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>C. Address of the Registered office / Head office</td></h4></tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(i) Address</td>
					<td width="49%"><span class="data">: '.$headoffice_address.', '.$address_line_headoffice.'</span></td>
				</tr>
				</table>';
				
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(ii) Telephone No. </td>
					<td width="49%"><span class="data">: '.$comm_telephone.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(iii) Mobile No. </td>
					<td width="49%"><span class="data">: '.$comm_mobile.'</span></td>
				 </tr></span>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(iv) Fax No. </td>
					<td width="49%"><span class="data">: '.$comm_fax.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(v) E-mail ID </td>
					<td width="49%"><b>: '.$comm_email.'</b></td>
				 </tr>
				</table>';
				
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>D. Communication Address</td></h4></tr>
				<tr>					 				
					<td width="2%" valign="top"></td>
					<td width="49%" valign="top">(i) Address</td>
					<td width="49%"><span class="data">: '.$communication_address.', '.$address_line_communication.'</span></td>
				</tr>
				</table>';
				 
		$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>E. Details of Occupier</td></h4></tr>
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
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>F i). Occupier Permanent Address</td></h4></tr>
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
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>F ii). Occupier Present Address</td></h4></tr>
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

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>G. Nature of the manufacturing process/processes</td></h4></tr>
				<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(i)Carried or To be carried on in the factory </td>
					<td width="49%"><span class="data">: '.$plant_installed.'</span></td>
				</tr>
				</table>';

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>H. Factory Identification according to WBPCB</td></h4></tr>
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
					 <tr><td colspan="3"></td></tr><tr><td colspan="3" align="left" style="font-size:14px;"><h4>I. Worker Details</td></h4></tr>
					 </tr>
					</table>';

		$content .= '<table width="100%"  border="1" cellspacing="0" cellpadding="0" class="custom-table-view-dashboard renewal-table" style="border: 1px solid #767676;margin-top: 10px">
                      
					      <tr>
                            <th colspan="6">Permanent</th>
                            <th colspan="6">Contactual</th>
                          </tr>
                          <tr>
                            <th rowspan="2">Men</th>
                            <th rowspan="2">Women</th>
                            <th colspan="2">Adolescents</th>
                            <th colspan="2">Children </th>
                            <th rowspan="2">Men</th>
                            <th rowspan="2">Women</th>
                            <th colspan="2">Adolescents</th>
                            <th colspan="2">Children</th>
                          </tr>
                          <tr>
                            <th >Men</th>
                            <th >Women</th>
                            <th >Men</th>
                            <th >Women</th>
                            <th >Men</th>
                            <th >Women</th>
                            <th >Men</th>
                            <th >Women</th>
                          </tr>';


							foreach($worker_details as $worker){
							$permanent_worker_men 	 = $worker->permanent_worker_men;
							$permanent_worker_women 	 = $worker->permanent_worker_women;
							$permanent_adolescents_male 	= $worker->permanent_adolescents_male;
							$permanent_adolescents_female 	= $worker->permanent_adolescents_female;
							$permanent_children_male 	 = $worker->permanent_children_male;
							$permanent_children_female 	 = $worker->permanent_children_female;
							$contactual_worker_men 	 = $worker->contactual_worker_men;
							$contactual_worker_women 	 = $worker->contactual_worker_women;
							$contactual_adolescents_male 	= $worker->contactual_adolescents_male;
							$contactual_adolescents_female 	= $worker->contactual_adolescents_female;
							$contactual_children_male 	 = $worker->contactual_children_male;
							$contactual_children_female 	= $worker->contactual_children_female;
							$worker_total 	 = $worker->worker_total;
							}
							
							$content .='
                          <tr>
                            <td align="center" >'.$permanent_worker_men.'</td>
                            <td align="center">'.$permanent_worker_women.'</td>
                            <td align="center">'.$permanent_adolescents_male.'</td>
                            <td align="center">'.$permanent_adolescents_female.'</td>
                            <td align="center" >'.$permanent_children_male.'</td>
                            <td align="center" >'.$permanent_children_female.'</td>
                            <td align="center">'.$contactual_worker_men.'</td>
                            <td align="center">'.$contactual_worker_women.'</td>
                            <td align="center">'.$contactual_adolescents_male.'</td>
                            <td align="center">'.$contactual_adolescents_female.'</td>
                            <td align="center">'.$contactual_children_male.'</td>
                            <td align="center">'.$contactual_children_female.'</td>
                          </tr>
                          <tfoot>
                            <tr>
                              <td colspan="12">Total Worker(s) :-&nbsp;&nbsp;
                                <strong>'.$worker_total.'</strong>
                              </td>
                            </tr>
                          </tfoot>
                        </table>';
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tr><td colspan="3"></td></tr>
					<tr><td colspan="3" align="left" style="font-size:14px;"><h4>J. POWER DETAILS</td></h4></tr>';
					if($type_power_station == 'power_generating_station'){
						$content .= '		<tr>					 				
						<td width="2%" valign="top">&nbsp;</td>
						<td width="49%" valign="top">(i)  Nature and total amount of power installed or proposed to be installed (Total rated H. P. in all cases except
electricity generating station)  </td>
						<td width="49%"><span class="data">: '.$power_installed.'</span></td>
						</tr>';
					}else{
						$content .= '		<tr>					 				
						<td width="2%" valign="top">&nbsp;</td>
						<td width="49%" valign="top">(i) Total generating capacity in KW(In case of generating station) </td>
						<td width="49%"><span class="data">: '.$power_installed.'</span></td>
						</tr>';
					}
	
			$content .= '	</table>';			
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>K. Manager Details</td></h4></tr>
				<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Name of Manager </td>
					<td width="49%"><span class="data">: '.$manager_details[0]->name_manager.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Present Address</td>
					<td width="49%"><span class="data">: '.$manager_details_view.' '.$address_of_manager.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Permanent Address </td>
					<td width="49%"><span class="data">: '.$manager_details[0]->manager_present_address.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Telephone </td>
					<td width="49%"><span class="data">: '.$manager_details[0]->manager_telephone.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Mobile </td>
					<td width="49%"><span class="data">: '.$manager_details[0]->manager_phone.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">FAX </td>
					<td width="49%"><span class="data">: '.$manager_details[0]->manager_fax.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Email </td>
					<td width="49%"><span class="data">: '.$manager_details[0]->manager_email.'</span></td>
				</tr>
			</table>';
			
			
$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>L. Director Details</td></h4></tr>
				<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Name of Director </td>
					<td width="49%"><span class="data">:'.$director_details[0]->name_director.' '.$din.'<br>'.$relationship.'-'.$director_details[0]->father_husband_name_director.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Present Address</td>
					<td width="49%"><span class="data">: '.$address_of_director.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Permanent Address </td>
					<td width="49%"><span class="data">: '.$director_details[0]->addrline_oprsntadr.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Telephone </td>
					<td width="49%"><span class="data">: '.$director_details[0]->director_telephone.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Mobile </td>
					<td width="49%"><span class="data">: '.$director_details[0]->director_mobile.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">FAX </td>
					<td width="49%"><span class="data">: '.$director_details[0]->director_fax_no.'</span></td>
				</tr>
				<tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">Email </td>
					<td width="49%"><span class="data">: '.$director_details[0]->director_email_id.'</span></td>
				</tr>
			</table>';
				
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">				
					<tr><td colspan="3"></td>&nbsp;</tr>
				<tr>
				<td colspan="3">In case of a factory constructed or extended or taken into use after the date of commencement of the Rules - </td>	
				</tr>
				
				<tr>
					<td colspan="3">&nbsp;</td>
				</tr>
				<tr>
					<td colspan="3">(a).Refrence number <span class="data">: '.$plan_approval_no.'</span> and date <span class="data">: '.$plan_approval_date.'</span> of approval of plans by the State Goverment/Chief Inspector</td>
				</tr>
				<tr>
					<td colspan="3">(b). Apply for the licence upto: <span class="data">'.date('dS M Y', strtotime($ending_year)).'</span> </td></tr>
			</tr>
			<tr><td colspan="3">&nbsp;</td></tr>';
				$grip_input_fetch = fun_grip_input_fetch($application_id,$service_id,$reference_id,$factorytype_id);	
				/*if(!empty($manual_payment)){
					$content .=	'<tr><td colspan="3">17.Amount of fees/renewal fee Rs.(Rupees)<span class="data">:</span></td></tr>
					<tr><td colspan="3"><span class="data">  &#x20b9;&nbsp;'.$get_all_data[0]->payment_amount.'(Rupees)in Word <mark>'.getCurrencyFormat($get_all_data[0]->payment_amount).'</mark> Paid through ------------- date--------------- (enclosed) for the period from --------------------to---------------</span></td></tr>';
				foreach($manual_payment as $payment){
					$content .=	'<tr><td colspan="3"><span class="data">  &#x20b9;&nbsp;'.$payment->payment_amount.'(Rupees) in Word <mark>'.getCurrencyFormat($payment->payment_amount).'</mark> Paid through '.$payment->brn_grn_challan_no.' date '.$payment->date_payment.' (enclosed) for the period from --------------------to---------------</span></td>
						</tr>';
					}
		$content .=	'</table>';
				}else{*/
					$sl= 17;
					foreach($grip_input_fetch as $row_grips){echo $sl;
							$content .=	'<tr>
					<td>'.$sl.'.Amount of fees/renewal fee Rs.(Rupees)</td>
					<td colspan="2"><span class="data">:  &#x20b9;&nbsp;'.$row_grips->payment_amount.'(Rupees)in Word <mark>'.getCurrencyFormat($row_grips->payment_amount).'</mark> Paid through ------------- date--------------- (enclosed) for the period from --------------------to---------------</span></td>	
				 	</tr>';
					$sl = $sl+1;
				
					
					
				
					$content .=	'</table>';
				}

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">				
					<tr><td style="text-align:right">Signature of the Occupier</td></tr>
					<tr><td style="text-align:right;text-transform: uppercase;font-weight:bold;" >'.$occupier_name.'</td></tr>
					<tr colspan="2"><td>&nbsp;</td><tr colspan="2"><td>&nbsp;</td>
					<tr><td style="text-align:right">(Full name of the Occupier in <br>Block Letter should be stated)</td>
					<td style="text-align:right">&nbsp;</td></tr>
				</table></div></fieldset>';
				//return $content;				
	//echo $content; die;
	ob_end_clean();
    $mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 20, 10, 0, 0);
	$mpdf->SetDisplayMode('fullpage');
	$mpdf->SetHTMLFooter('<div style="padding-bottom:20px; text-align: center; font-size:9px;">Page {PAGENO} of {nb}</div>');
	if($service_id==2){
		$mpdf->SetWatermarkImage($_SERVER['DOCUMENT_ROOT'].$base_path.'sites/all/themes/custom_dashboard/images/registration_bg.jpg');
	}elseif($service_id==3){
		$mpdf->SetWatermarkImage($_SERVER['DOCUMENT_ROOT'].$base_path.'sites/all/themes/custom_dashboard/images/renewal_bg.jpg');
	}
	
	//$mpdf->watermarkImageAlpha = 1;
	$mpdf->showWatermarkImage = true;
	$mpdf->WriteHTML($content);
	$mpdf->Output('Common_applicantion_form_'.$plan_approval_no.'_'.time().'.pdf','D');
	//return pdf_using_mpdf_api($content,'caf-registration'._.time());
}
?>