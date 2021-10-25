<?php
require_once $_SERVER['DOCUMENT_ROOT'].'/sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';
function application_registration_autogen($serviceid, $factory_typeid,$applicationid,$referenceid) {	
//echo 'check';die;
	global $base_root, $base_path, $user; 
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$service_id 		= encryption_decryption_fun('decrypt', $serviceid);
	$factorytype_id 	= encryption_decryption_fun('decrypt', $factory_typeid);
	
	$get_all_data 		= get_fa_cafa($application_id);
	$classification_no	= $get_all_data['classification_no'];
	$application_date 	= date('dS M Y', strtotime($get_all_data['created_date']));
	$application_no 	= $get_all_data['factory_reg_identification_number'];
	
	$max_license_no 	= $get_all_data['factory_license_no'];
	$max_reg_no 		= $get_all_data['factory_registrstion_no'];
	$zonid 				= $get_all_data['factory_zone'];
	$zone 				= get_factory_zone_name($zonid);
	$payment_amount		= $get_all_data['payment_amount'];
	$district_code		= $get_all_data['district'];
	$factory_owershiptype = $get_all_data['factory_owershiptype'];
	if($factory_owershiptype == "ltd" || $factory_owershiptype == "pv" || $factory_owershiptype == "others" || $factory_owershiptype == "psu" || $factory_owershiptype == "govt"){
		$grand_to = $get_all_data['factory_name'];
	}if($factory_owershiptype == "pro_firm"){
		$i=0;
		$get_all_data = get_all_occupier_data($application_id,$service_id,$factorytype_id,$reference_id);
		foreach($get_all_data as $occuiper){
			
			$i= $i+1;
		}
		if($i>1){
			$grand_to = $occuiper->name_occupier.'& Others';
		}else{
			$grand_to  = $occuiper->name_occupier;
		}
	}if($factory_owershiptype == "par_firm"){
		$i=0;
		$get_all_data = get_director_details_service($application_id,$service_id,$factorytype_id,$reference_id);
		foreach($get_all_data as $director){
			
			$i= $i+1;
		}
		if($i>1){
			$grand_to = $director->name_director.'& Others';
		}else{
			$grand_to  = $director->name_director;
		}
	}
	
	if(empty($max_license_no)){
			$factory_license_no  = create_license_no($factorytype_id,$district_code);
		 	$caf_update 	= 	array('factory_license_no' => $factory_license_no, 'license_date' => date('Y-m-d'));
	  		$queryabc 		=	db_update('fa_cafa');
	   		$queryabc		->	fields($caf_update);
	   		$queryabc		->	condition('id',$application_id,'=');
	   		$queryabc	    ->	execute();
			$max_license_no = $factory_license_no;
	   
	}
	
	if(empty($max_reg_no)){
			$registration_no = create_registration_no($factorytype_id,$district_code);
			$caf_update1 	= 	array('factory_registrstion_no' => $registration_no, 'registration_date' => date('Y-m-d'));
	  		$queryabc1 		=	db_update('fa_cafa');
	   		$queryabc1		->	fields($caf_update1);
	   		$queryabc1		->	condition('id',$application_id,'=');
	   		$queryabc1	    ->	execute();
			$max_reg_no = $registration_no;
	}
	
	
	$get_power_data = get_power_data($application_id,$service_id,$factorytype_id,$reference_id);
	$maxHP = 0;
	foreach($get_power_data as $power){
		$max_hp = $power->installed_power_hp;
		 $maxHP = max($max_hp, $maxHP);
		
		}
	$get_worker_data =  get_worker_details_service($service_id,$factorytype_id,$application_id,$reference_id);
	$maxWorker = 0;
	foreach($get_worker_data as $worker){
		$max_worker = $worker->worker_total;
		 $maxWorker = max($max_worker, $maxWorker);
		 
		}
		
		
	$name_of_factory 			= 	$get_all_data['factory_name'];
	$type_of_factory 			= 	$get_all_data['factory_typeid'];
	if($type_of_factory=='1'){
		$type= '2M(i)';
		}if($type_of_factory=='2'){
			$type= '2M(ii)';
			}if($type_of_factory=='3'){
				$type= '85';
				}
				
	//$factory_license 			= 	$get_all_data['factory_license_no'];
	//$factory_registrstion 		= 	$get_all_data['factory_registrstion_no'];
	$get_date 					= get_fa_cafa($application_id);
	$factory_registrstion_date 	= 	date('dS M Y', strtotime($get_date['registration_date']));

	$getdata_factory_address 	=  	array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address 			=	get_full_address('fa_cafa','sub-table',$application_id,$getdata_factory_address);
	
	$factory_address_line 	=  	array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_line 			=	get_full_address_certificates('fa_cafa','sub-table',$application_id,$factory_address_line);
	
	$memo_no				=	'WBF/OL/'.date('Y').'/'.$type.'/R';
	$memo_no2				=	'WBF/OL/'.date('Y').'/'.$type.'/R/4';
	
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
					.data{ text-transform: uppercase; font-weight: bold;"}
			</style>';
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">				
					<tr><td colspan="3"></td></tr>
					<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden; text-transform:uppercase;">GOVERMENT OF WEST BENGAL</td></tr>
					<tr><td colspan="3" align="center" style="font-size:14px;text-transform:uppercase;"><b> Directorate of Factories </b></td></tr>
					<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden; text-transform:uppercase;">NEW SECRETARIAT BUILDING(8th floor)</td></tr>
					<tr><td colspan="3"  align="center" style="font-size:10px;">1, KIRAN SANKAR ROY ROAD, KOLKATA -700001</td></tr>
					<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden; text-transform:uppercase;text-decoration: underline;">REGISTRATION CERTIFICATE</td></tr>
					</table>';
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">				
					<tr>
					<tr><td colspan="1"><br/></td></tr>
						<td colspan="2" align="left" style="font-size:12px;">No. <span class="data">'.$memo_no.'</span></td>
						<td colspan="2" align="right" style="font-size:12px;">Kolkata, <span class="data">'.date('dS M Y', strtotime(date("Y-m-d"))).'</span></td>
					</tr>
				</table>';
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">				
					<tr>
					<tr><td colspan="4"><br/></td></tr>
					<tr><td colspan="1" align="left" style="font-size:12px;"><i>Form: </i>The Chief Inspector of Factories, West Bengal,</td></tr>
					<tr><td colspan="1" align="left" style="font-size:12px;"><i>To: </i>The Occupier,</td></tr>
					<tr><td colspan="1" align="left" style="font-size:12px;"><span class="data">'.$name_of_factory.'</span></td></tr>
					<tr><td colspan="1" align="left" style="font-size:12px;"><span class="data">'.$factory_address.' </span></td></tr>
					<tr><td colspan="1" align="left" style="font-size:12px;"><br/></td></tr>
					<tr><td colspan="1" align="center" style="font-size:12px;">Factories Act, 1948: West Bengal Factories Rules 1958</td></tr>
				</table>';
				
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">				
					<tr>
					<tr><td colspan="4"><br/></td></tr>
					<tr><td colspan="1" align="left" style="font-size:12px;">Sir, </td></tr>
					<tr><td colspan="1" align="left" style="font-size:12px;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; I have the honour to acknoladge receipt of your letter No.&nbsp;&nbsp;<span class="data">'.$application_no.'</span>&nbsp;&nbsp;dated the <span class="data">'.$application_date.'</span> together with the application for registration and grant of licence in Common Application Form and to State that the premises known as <span class="data">'.$name_of_factory.'</span> situated at &nbsp;&nbsp;<span class="data">'.$factory_line.'</span>&nbsp;&nbsp; constitute a "factory" as defined &nbsp;&nbsp;"Under Section '.$type.'"&nbsp;&nbsp; of the said Act. Consequently, the provisions of the following Acts and Rules are aplicable to your factory and must be adhered to:- </tr>
					
					<tr><td align="left" style="font-size:12px; padding-left:15%;">1)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The Factories Act, 1948</td></tr>
					<tr><td align="left" style="font-size:12px; padding-left:15%;">2)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The West Bengal Factories Rules, 1958</td></tr>
					<tr><td align="left" style="font-size:12px; padding-left:15%;">3)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The Payment of Wages Act, 1936</td></tr>
					<tr><td align="left" style="font-size:12px; padding-left:15%;">4)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The West Bengal Payment of Wages Rules, 1958</td></tr>
					<tr><td align="left" style="font-size:12px; padding-left:15%;">5)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The Maternity Benifit Act, 1961</td></tr>
					<tr><td align="left" style="font-size:12px; padding-left:15%;">The registration number of the factory is <span class="data">'.$max_reg_no.'</span> Date <span class="data">'.$factory_registrstion_date.'</span></td></tr>
					<tr><td align="left" style="font-size:12px; padding-left:15%;">The classification no. of the factory is <span class="data">'.$classification_no.'</span></td></tr>
					<tr><td align="left" style="font-size:12px; padding-left:15%;">The Licence No. of the factory is <span class="data">'.$max_license_no.'</span></td></tr>
				</table>';
		$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tr><td align="right" style="font-size:12px;">Your faithfully<br><br><br><br><br></td></tr>
					<tr><td align="right" style="font-size:12px;">for <b>Chief Inspector of Factories, West Bengal</b><br></td></td></tr>
					<tr><td align="left" style="font-size:12px;">Memo No. '.$memo_no2.' </td></tr>
					<tr><td align="right" style="font-size:12px;">Date __________ <br><br><br><br><br></td></tr>
					<tr><td align="left" style="font-size:12px;">Copy forwared for information to the: </td></tr>
					<tr><td align="left" style="font-size:12px;">1) &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Director, National Sample Survay Organisation, FOD, CGO Complax, Salt Lake, 2nd floor, Kolkata-700064 </td></tr>
					<tr><td colspan="1" align="left" style="font-size:12px;">2) &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Regional Director,E.S.I., Corporation, 5/1, Grant Lane, Kolkata-700012</td></tr>
					<tr><td colspan="1" align="left" style="font-size:12px;">3) &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Providant Fund Commissionar, West Bengal, DK BLOCK, Sector-II, Salt Lake, Kolkata-700064 </td></tr>
					<tr><td colspan="1" align="left" style="font-size:12px;">4) &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Dy, C.I.F., Statistic, Extn. Office.</td></tr>
					<tr><td colspan="1" align="left" style="font-size:12px;">The name of the factory should be entered under the classification <span class="data">'.$classification_no.'</span><br>The total number of workers proposed to be employed in the factory is <span class="data">'.$maxWorker.'</span>, KW/HP- <span class="data">'.$maxHP.'</span></td></tr>
					<tr><td align="right" style="font-size:12px;"><br><br>for <b>Chief Inspector of Factories, West Bengal</b><br></td></td></tr>
					<tr><td align="right" style="font-size:12px;">Dated The___________ <br></td></tr>
					<tr><td align="left" style="font-size:12px;">Kolkata, </td></tr>
					<tr><td align="left" style="font-size:12px;">The, </td></tr>
					<tr><td align="left" style="font-size:12px;">Memo No. '.$memo_no.' </td></tr>
					<tr><td align="left" style="font-size:12px;">Copy along with Common Application Form(2) copy for the year________ forworded to the Dy. CIF & I.F. _________________ for Information with referance to his U.O. No. _____________dt._____________________ </td></tr>
					<tr><td align="right" style="font-size:12px;"><br><br>for <b>Chief Inspector of Factories, West Bengal</b><br></td></td></tr>
					
					
				</table>';
						$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 20, 10, 0, 0);
						$mpdf->SetDisplayMode('fullpage');
						//$mpdf->SetHTMLHeader(' <div style="padding-top:50px; text-align: right; font-size:9px;">Page {PAGENO} of {nb}</div>');
						//$mpdf->SetWatermarkText('DRAFT COPY');
						//$mpdf->showWatermarkText = FALSE;
						$mpdf->WriteHTML($content);
						$mpdf->Output('Registration_certificate_'.$memo_no.'_'.time().'.pdf','D');
	//return pdf_using_mpdf_api($content,'caf-reg'._.time());
	
	}