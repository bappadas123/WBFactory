<?php
		require_once '/var/www/html/factories/sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';
		//require_once 'C:\xampp\htdocs\factories\sites\all\modules\contrib\pdf_using_mpdf\mpdf\mpdf.php';
		function preview_plan_all_information($serviceid, $factory_typeid,$applicationid,$linknumber,$linkdate,$flagmapp){ echo "tset";
		    global $base_root, $base_path;
			$service_id      	= encryption_decryption_fun('decrypt', $serviceid);
			$factory_type_id 	= encryption_decryption_fun('decrypt', $factory_typeid);
			$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
			$link_number 		= encryption_decryption_fun('decrypt', $linknumber);
			$link_date 			= encryption_decryption_fun('decrypt', $linkdate);
			$flag_mapp 			= encryption_decryption_fun('decrypt', $flagmapp);
			$get_all_data 		= get_fa_cafa($application_id);
			$reference_id		= $get_all_data['reference_number'];
			$previous_name		= $get_all_data['factory_previous_name'];
			$is_backlog			= $get_all_data['is_backlog'];
			if($is_backlog == 1){
				$plan_approval_no 	= $get_all_data['backlog_plan_approval_no'];
				$plan_approval_date = date('dS M Y', strtotime($get_all_data['backlog_plan_approval_date']));
			}if($is_backlog != 1){
				$plan_approval_no 	= $get_all_data['factory_plan_approval_number'];
				$plan_approval_date = date('dS M Y', strtotime($get_all_data['modification_date']));
			}
			if($get_all_data['wbpcb_category_name']==1){$consent ='Red';}
			if($get_all_data['wbpcb_category_name']==2){$consent ='Green';}
			if($get_all_data['wbpcb_category_name']==3){$consent ='Orange';}
			if($get_all_data['wbpcb_category_name']==4){$consent ='White';}
			if($get_all_data['wbpcb_category_name']==5){$consent ='Exempted';}
			
			$getdata_factory_address  	= array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
			$factory_address 		    = get_parts_address('fa_cafa','sub-table',$application_id,$getdata_factory_address);
			
			$getdata_headoffice_address = array('district_off','subdivision_off','areatype_off','block_off','panchayat_off','policestation_off','pincodeoff','state_off','postoffice_off');
			$headoffice_address 		= $get_all_data['addrline_off'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_headoffice_address);
			
			$getdata_communication_address = array('district_comm','subdivision_comm','areatype_comm','block_comm','panchayat_comm','policestation_comm','pincodecomm','state_comm','postoffice_comm');
			$communication_address 		= $get_all_data['addrline_comm'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_communication_address);
			
			$getdata_owner_address 		= array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
			$owner_address_details = !empty($get_all_data['addrline_premises'])?$get_all_data['addrline_premises'].',':'';
			$owner_address_details.= $get_all_data['owner_country_address'].',
<br/>'.country_name($get_all_data['owner_country']);
			$owner_address 				=	$owner_address_details.'
<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_owner_address);

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
   		}if($get_all_data['factory_owershiptype']=="others"){
   				$ownership_type = "Others";
   		};
		$energy_no = !empty($get_all_data['enargy_no'])?$get_all_data['enargy_no']:'n/a';
		$cin_no = !empty($get_all_data["cin_no"])?$get_all_data["cin_no"]:'n/a';
		
		$worker_details 			= get_worker_details_service($service_id,$factory_type_id,$application_id,$reference_id);
		$power_generating_station 	= get_power_generating_station($application_id,$reference_id,$factory_type_id,$service_id);
		foreach($power_generating_station as $power){
			$power_details 	= $power->installed_power.'('.$power->power_unit.')';
			$power_station 	= $power->type_power_station;
		}
		$nature_details = get_manufacturing($application_id,$service_id,$factory_type_id,$reference_id);
		foreach($nature_details as $nature){
			$nature_work 	= $nature->nature_manufacturing;
		}
		$get_all_occupier 	= get_all_occupier_data($application_id,$service_id,$factory_type_id,$reference_id);
		$get_all_manager 	= get_all_manager_data($application_id,$service_id,$factory_type_id,$reference_id);
		$get_all_director 	= get_director_details_service($application_id,$service_id,$factory_type_id,$reference_id);
		
		$query 	=  db_select('fa_caf_upload_doc', 'fcud');
		$query	-> InnerJoin('fa_file_managed_custom', 'file' ,'fcud.fid = file.id');
		$query 	-> fields('fcud', array());
		$query	-> fields('file', array('file_uri'));
		$query	-> condition('fcud.app_id', $application_id);
		$query	-> condition('fcud.application_reference_no', $reference_id);
		$query	-> condition('fcud.upload_documents_service_id', $service_id);
		$query	-> condition('fcud.upload_doc_factory_type_id', $factory_type_id);
		$result = $query->execute();
		//echo $query;die;
		$resultData = $result->fetchAll();

		
		$content = '<style type="text/css">
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
  <body style="background-color:#fff">
    <table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr><td colspan="3"></td></tr>
					
					<tr><td colspan="3" align="center" style="font-size:15px;text-transform:uppercase;"><h2> DRAFT MODE </h2></td></tr>
					<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden; text-transform:uppercase;">GOVERMENT OF WEST BENGAL</td></tr>
					<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden; text-transform:uppercase;">Directorate of Factories</td></tr>
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
          <td width="49%">
            <span class="data">: '.$get_all_data['factory_name'].'</span>
          </td>
        </tr>
        <tr>
          <td width="2%"  valign="top">&nbsp;</td>
          <td width="49%" valign="top">(ii). GSTIN Number</td>
          <td width="49%">
            <span class="data">: '.$get_all_data['gstin_no'].'</span>
          </td>
        </tr>
        <tr>
          <td width="2%"  valign="top">&nbsp;</td>
          <td width="49%" valign="top">(iii). Udyog Aadhaar No</td>
          <td width="49%">
            <span class="data">: '.$get_all_data['udyog_aadhaar'].'</span>
          </td>
        </tr>
        <tr>					 				
			<td width="2%"  valign="top">&nbsp;</td>
			<td width="49%" valign="top">(iv). Trade License No</td>
			<td width="49%"><span class="data">: '.$get_all_data['trade_license_no'].'</span></td>
		 </tr>
	    <tr>
          <td width="2%"  valign="top">&nbsp;</td>
          <td width="49%" valign="top">(v). Energy Meter No</td>
          <td width="49%">
            <span class="data">: '.$energy_no.'</span>
          </td>
        </tr>
        <tr>
          <td width="2%"  valign="top">&nbsp;</td>
          <td width="49%" valign="top">(vi). CIN No</td>
          <td width="49%">
            <span class="data">: '.$cin_no.'</span>
          </td>
        </tr>';
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
          <td width="2%"  valign="top"></td>
          <td width="49%" valign="top" style="padding-left: 15px;">Address</td>
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
                <span class="data">: '.$get_all_data['railway_station'].'</span>
              </td>
              <tr>
				<tr>
              <td width="2%"  valign="top"></td>
              <td width="49%" valign="top" style="padding-left: 15px;">Zone</td>
              <td width="49%">
                <span class="data">: CA</span>
              </td>
              <tr>
                <tr>
                  <td width="2%"  valign="top"></td>
                  <td width="49%" valign="top">(b) Address of the Registered Office/Head Office </td>
                  <td width="49%">
                    <span class="data">: '.$headoffice_address.'</span>
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
                    <span class="data">: '.$headoffice_address.'</span>
                  </td>
                </tr>
				<tr>
				  <td colspan="3">&nbsp;</td>
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
				
				
                <table width="100%" border="0" cellspacing="0" cellpadding="0">
                  <tr>
                    <td colspan="3">
                      <table width="100%"  border="1" cellspacing="0" cellpadding="0" class="custom-table-view-dashboard renewal-table">
                        <tr>
                          <th width="40%">Occupier Information</th>
                          <th width="30%">Present Address</th>
                          <th width="30%">Permanent Address</th>
                        </tr>';
		
	$sl=1;
	foreach($get_all_occupier as $details){
	$fieldArr_occupier			 =  array('district_occupier','sub_division_occupier','area_type_occupier','block_mun_cor_sez_not_occupier','grm_ward_sector_not_occupier','police_station_occupier','pincode_occupier','state_occupier','post_office_occupier');

	$content .='
                        <tr>
                          <td>'.$details->name_occupier.'('.$details->type_occupier.')'.'
                            <br/>Father/Husband:-'.$details->father_husband_name_occupier.'
                            <br/>Age:-'.$details->age_occupier.'
                            <br/>Nationality:- INDIAN
                            <br/>Passport/Aadhaar Number:- 1111-4444-2525
                          </td>
                          <td align="center">'.$details->adress_line1_occupier.'
                            <br>'.get_full_address('fa_occupier_details','sub-table',$details->id,$fieldArr_occupier).'
                          </td>
                          <td align="center">'.$details->adress_line1_occupier.'
                            <br>'.get_full_address('fa_occupier_details','sub-table',$details->id,$fieldArr_occupier).'
                          </td>
                          </tr>';
	$sl++;
		}
	
	$content .='
                        </table>
                      </td>
                    </tr>
                  </table>
				
				
				<tr>
					<td colspan="3">&nbsp;</td>
				  </tr>
                <tr>
                  <td width="2%"  valign="top">5.</td>
                  <td colspan="2" width="98%" valign="middle" colspan="3">Details of owner of the premises occupied as a factory - </td>
                </tr>
                <tr>
                  <td colspan="3">
                    <table width="100%" border="0" cellspacing="0" cellpadding="0">
                      <tr>
                        <td width="2%"  valign="top"></td>
                        <td width="49%" valign="top">Name of the owner </td>
                        <td width="49%">
                          <span class="data">: '.$get_all_data['owner_name'].' '.$get_all_data['owner_mname'].' '.$get_all_data['owner_lname'].'</span>
                        </td>
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
                  </table>
                  <table>
				  <tr>
					  <td width="2%"  valign="top">6.</td>
					  <td width="49%" valign="top">Particular of Plan to be installed</td>
					  <td width="49%">
						<span class="data">: '.$get_all_data['plant_installed'].'</span>
					  </td>
					</tr>
					  <tr>
						<td colspan="3">&nbsp;</td>
					  </tr>
                    <tr>
                      <td width="2%"  valign="top">7.</td>
                      <td colspan="2" width="98%" valign="middle">Factory Identification according to wbpcb</td>
                    </tr>
                    <tr>
                      <td width="2%"  valign="top">&nbsp;</td>
                      <td width="49%" valign="top">(i). Categories of wbpcb</td>
                      <td width="49%">
                        <span class="data">: '.$consent.'</span>
                      </td>
                    </tr>
                    <tr>
                      <td width="2%"  valign="top">&nbsp;</td>
                      <td width="49%" valign="top">(ii). Reference number of approval of arrangments</td>
                      <td width="49%">
                        <span class="data">: '.$get_all_data['wbpcb_reference_no'].'</span>
                      </td>
                    </tr>
                    <tr>
                      <td width="2%"  valign="top">&nbsp;</td>
                      <td width="49%" valign="top">(iii). Date of approval of arrangments</td>
                      <td width="49%">
                        <span class="data">: '.date('dS M Y', strtotime($get_all_data['wbpcb_ref_date'])).'</span>
                      </td>
                    </tr>
					<tr>
                      <td colspan="3">&nbsp;</td>
                    </tr>
					<tr>
                      <td colspan="3">&nbsp;</td>
                    </tr>
					<tr>
                      <td colspan="3">&nbsp;</td>
                    </tr>
					<tr>
                      <td colspan="3">&nbsp;</td>
                    </tr>
					<tr>
                      <td colspan="3">&nbsp;</td>
                    </tr>
					<tr>
                      <td colspan="3">&nbsp;</td>
                    </tr>
                  </table>
                  <table width="100%" border="0" cellspacing="0" cellpadding="0">
                    <tr>
                      <td colspan="3" align="left" style="font-size:14px;">
                        <h4>B. WORKER DETAILS</h4>
                      </td>
                    </tr>';
			if(!empty($previous_name))	{		 
			$content .= ' 
					
                    <tr>
                      <td colspan="3">&nbsp;</td>
                    </tr>
                    <tr>
                      <td width="49%" valign="top" colspan="3">(b) Previous Name of the Factory (if different from the present name) </td>
                    </tr>
                    <tr>
                      <td colspan="3">
                        <table width="100%" border="0" cellspacing="0" cellpadding="0">
                          <tr>
                            <th align="center">Application Year</th>
                            <th align="center">Change name</th>
                            <th align="center">Description</th>
                          </tr>
                          <tr>
                            <td colspan="3">&nbsp;</td>
                          </tr>'
							;
							foreach($previous_name as $previous){
							
												$content .='
								
                          <tr>
                            <td align="center">'.$previous->service_year.'</td>
                            <td align="center">'.$previous->conversation_name.'</td>
                            <td align="center">'.$previous->description_conversation.'</td>
                          </tr>';
							}
				$content .='
							
                        </table>
                      </td>
                    </tr>';
				}
			$content .= '
					
                    <tr>
                      <td colspan="3">&nbsp;</td>
                    </tr>
                    <tr>
                      <td colspan="3">
                        <table width="100%"  border="1" cellspacing="0" cellpadding="0" class="custom-table-view-dashboard renewal-table">
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
				$permanent_worker_men 			= $worker->permanent_worker_men;
				$permanent_worker_women 		= $worker->permanent_worker_women;
				$permanent_adolescents_male 	= $worker->permanent_adolescents_male;
				$permanent_adolescents_female 	= $worker->permanent_adolescents_female;
				$permanent_children_male 		= $worker->permanent_children_male;
				$permanent_children_female 		= $worker->permanent_children_female;
				$contactual_worker_men 			= $worker->contactual_worker_men;
				$contactual_worker_women 		= $worker->contactual_worker_women;
				$contactual_adolescents_male 	= $worker->contactual_adolescents_male;
				$contactual_adolescents_female 	= $worker->contactual_adolescents_female;
				$contactual_children_male 		= $worker->contactual_children_male;
				$contactual_children_female 	= $worker->contactual_children_female;
				$worker_total 					= $worker->worker_total;
			}
	
	$content .='
                          <tr>
                            <td align="center">'.$permanent_worker_men.'</td>
                            <td align="center">'.$permanent_worker_women.'</td>
                            <td align="center">'.$permanent_adolescents_male.'</td>
                            <td align="center">'.$permanent_adolescents_female.'</td>
                            <td align="center">'.$permanent_children_male.'</td>
                            <td align="center">'.$permanent_children_female.'</td>
                            <td align="center">'.$contactual_worker_men.'</td>
                            <td align="center">'.$contactual_worker_women.'</td>
                            <td align="center">'.$contactual_adolescents_male.'</td>
                            <td align="center">'.$contactual_adolescents_female.'</td>
                            <td align="center">'.$contactual_children_male.'</td>
                            <td align="center">'.$contactual_children_female.'</td>
                          </tr>
                          <tfoot>
                            <tr>
                              <td colspan="12">Total Worker(s)  :-&nbsp;&nbsp;
                                <strong>'.$worker_total.'</strong>
                              </td>
                            </tr>
                          </tfoot>
                        </table>
                      </table>
                    </td>
                  </tr>
                </table>
                <table>
                  <tr>
                    <td>&nbsp;</td>
                  </tr>
                </table>
				<table width="100%" border="0" cellspacing="0" cellpadding="0">
                              <tr>
                                <td colspan="3" align="left" style="font-size:14px;">
                                  <h4>C. PLAN RELATED DOCUMNENTS</h4>
                                </td>
                              </tr>
                              <tr>
                                <td colspan="3">
                                  <table width="100%"  border="1" cellspacing="0" cellpadding="0" class="custom-table-view-dashboard renewal-table">
                                    <tr>
                                      <th>Serial No.</th>
                                      <th>Document Name</th>
                                    </tr>
									<tr>
										<td align="center">1</td>
										<td>Flow Chart Of Manufacturing Processes</td>
									</tr>
									<tr>
										<td align="center">2</td>
										<td>Site plan, Floor plan and Sectional elevation</td>
									</tr>
									<tr>
										<td align="center">3</td>
										<td>Consent to Establish</td>
									</tr>
									<tr>
										<td align="center">4</td>
										<td>Authenticated Copy of Purchase Deed/Lease Deed/Rent Receipt as the case may be in respect of the premises to be used as factory</td>
									</tr>';
										$content .='
                                                  </table>
                                                </td>
                                              </tr>
                                            </table>
                                          </body>
                                        </html>';
			
						$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 20, 10, 0, 0);
						$mpdf->SetDisplayMode('fullpage');
						$mpdf->SetHTMLHeader('
                                        <div style="padding-top:50px; text-align: right; font-size:9px;">Page {PAGENO} of {nb}</div>');
						$mpdf->SetWatermarkText('DRAFT COPY');
						$mpdf->showWatermarkText = false;
						$mpdf->WriteHTML($content);
						$mpdf->Output('preview_varse_'.$plan_approval_no.'_'.time().'.pdf','D');		
		}