<?php
global $base_path; 
require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';
function registration_genarate_file($serviceid, $factory_typeid,$applicationid,$referenceid) {	

	global $base_root, $base_path, $user; 
	
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$service_id 		= encryption_decryption_fun('decrypt', $serviceid);
	$factorytype_id 	= encryption_decryption_fun('decrypt', $factory_typeid);
	
	$get_all_data 		= get_fa_cafa($application_id);
	$classification_no	= $get_all_data['classification_no'];
	$application_date 	= date('dS M Y', strtotime($get_all_data['created_date']));
	$application_no 	= $get_all_data['factory_reg_identification_number'];
	$uid 				= $user->uid;
	$max_license_no 	= $get_all_data['factory_license_no'];
	$max_reg_no 		= $get_all_data['factory_registrstion_no'];
	$zonid 				= $get_all_data['factory_zone'];
	$zone 				= get_factory_zone_name($zonid);
	$payment_amount		= $get_all_data['payment_amount'];
	$district_code		= $get_all_data['district'];
	
	
	$factory_owershiptype 	= $get_all_data['factory_owershiptype'];
	$get_licence_valid_to	= get_licence_valid_to($service_id,$factorytype_id,$application_id,$reference_id);
	
	if(empty($get_all_data['registration_date'])){
    	$counter = date("d");
	}else{
		$counter = date('d', strtotime($get_all_data['created_date']));
	}
        
	if($factory_owershiptype == "ltd" || $factory_owershiptype == "pv" || $factory_owershiptype == "others" || $factory_owershiptype == "psu" || $factory_owershiptype == "govt" || $factory_owershiptype == "llp" || $factory_owershiptype == "psu" || $factory_owershiptype == "cooperative" || $factory_owershiptype == "registered" || $factory_owershiptype == "localbody" || $factory_owershiptype == "others"){
		$grand_to = $get_all_data['factory_name'];
	}if($factory_owershiptype == "pro_firm"){
		$i=0;
		$get_all_occupier_data = get_all_occupier_data($application_id,$service_id,$factorytype_id,$reference_id);
		foreach($get_all_occupier_data as $occuiper){
			
			$i= $i+1;
		}
		if($i>1){
			$grand_to = $occuiper->name_occupier.'& Others';
		}else{
			$grand_to  = $occuiper->name_occupier;
		}
	}if($factory_owershiptype == "par_firm"){
		$i=0;
		$get_all_director_data = get_director_details_service($application_id,$service_id,$factorytype_id,$reference_id);
		foreach($get_all_director_data as $director){
			
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
		
	$amenability_date 			= 	$get_all_data['date_of_amenability'];
	$date_of_amenability 		= 	date('dS M Y', strtotime($amenability_date));	
	$name_of_factory 			= 	$get_all_data['factory_name'];
	$type_of_factory 			= 	$get_all_data['factory_typeid'];
	if($type_of_factory=='1'){
		$type= '2M(i)';
		}if($type_of_factory=='2'){
			$type= '2M(ii)';
			}if($type_of_factory=='3'){
				$type= '85';
				}
	$img_url					= $_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/themes/wbfactories/images/certificate/em.jpg';			
	//$factory_license 			= 	$get_all_data['factory_license_no'];
	//$factory_registrstion 		= 	$get_all_data['factory_registrstion_no'];
	$get_date 					= get_fa_cafa($application_id);
	$factory_registrstion_date 	= 	date('dS M Y', strtotime($get_date['registration_date']));

	$getdata_factory_address 	=  	array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address 			=	get_full_address('fa_cafa','sub-table',$application_id,$getdata_factory_address);
	
	$factory_address_line 		=  	array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_line 				=	get_full_address_certificates('fa_cafa','sub-table',$application_id,$factory_address_line);
	

	$marge_no					=   $max_reg_no.'/'.$max_license_no.'/'.$counter;
	//$barcode 					=	get_name($uid).'Kolkata'.'joint chief of factories';
	$barcode 					=	get_name($uid);
	
	$valid_to  = get_fa_cafa_log($application_id);
	foreach($valid_to as $valid){
		$valid_date = $valid->fa_licence_valid_to;
	}
		
	if($get_licence_valid_to != $valid_to){
//		$data 	=  array(
//					'fa_name'			=>  $grand_to ,
//					'fa_license_no'	=> $max_license_no,
//					'fa_registartion_no' => $max_reg_no,
//					'fa_amenability_date' =>$get_all_data['date_of_amenability'],
//					'fa_power' =>$maxHP,
//					'fa_worker' =>$maxWorker,
//					'fa_fees' =>$payment_amount,
//					'fa_licence_valid_to' => $get_licence_valid_to,
//					'fa_issue_by'=> $user->uid,
//					'fa_issue_date' =>  date("Y-m-d"),
//					'fa_application_id'=> $application_id,
//					'fa_payment_date' => $payment_date,
//					'fa_service_id'=> $service_id,
//					'fa_active_inactive' =>1,
//					'is_genareate'		=>1
//				);
//				
//			$exist_data = db_insert('fa_registration_licence_log')->fields($data)->execute();
		}
		
	$qr_code				='Factory Name:-'.$grand_to.'&nbsp;Registration No:-'.$max_reg_no.'&nbsp;Licecne No:-'.$max_license_no.'&nbsp;Licence valid:-'.$get_licence_valid_to.'&nbsp;Power:'.$maxHP.'&nbsp;Worker:-'.$maxWorker.'&nbsp;Fees:-'.$payment_amount.
	
	$content = '<style type="text/css">
				
					.address{
						font-size:13px;
						color:#2d2d2d;
						font-family:Arial, Helvetica, sans-serif;
					}
					.address span{font-size:10px;}
					#two{
						font-size:13px; 
						font-weight: normal;
						color:#1f1200;
					}
					#three{
						font-size:13px;
						color:#0b4f4d;
					}
					#four{
						font-size:13px;
						color:#0b4f4d;
						text-align: right;		
					}
					#five{
						font-size:13px;
						color:#000;
					}
					#six{
						font-size:14px;
						color:#fff;
						background: #076641;
					}
					#seven{
						font-size:12px;
						color:#925e29;
						font-weight: 700;
						}
					#eight{
						font-size:12px;
						color:#925e29;
					}
					#nine{
						font-size:13px;
						color:#f5dfce;
						font-weight: 700;
						background: #88171c;
						}
					#ten{
						font-size:12px;
						color:#925e29;
						font-weight: 700;	
						}
						
					#eleven{
							font-size:12px;
							color:#925e29;
						}
					#twelvs{
							font-size:13px;
							padding-right: 20px;
						}
					
					
			  @page{
				margin-top: 0.1mm;
				margin-bottom:0.1mm;
				margin-left: 0.1mm;
				margin-right:0.1mm;
			 }		
			</style>';
	$content .= '<fieldset style="font-family: Arial, Open Sans; padding: 0;border: 20px solid #fff;">
         <div style="width:100%; background-image-resize:4; background:url('.$_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/themes/wbfactories/certificate/frame2.png) no-repeat center top;">';
		 
	if(!empty($get_all_power_data)){
	$content .= '<div style="padding:50px 50px 190px 50px;background:url('.$_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/themes/wbfactories/certificate/df_stamp2.png) no-repeat center center;">';	
	}else{
	
	$content .= '<div style="padding:50px 50px 110px 50px;background:url('.$_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/themes/wbfactories/certificate/df_stamp2.png) no-repeat center center;">';
	}
	
	$content .= '<table width="100%" border="0" >
                  <tbody>
                     <tr>
                        <td colspan="2">
                           <table width="100%" border="0">
                              <tr>
                                 <td align="right" valign="top" ><img src="'.$_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/themes/wbfactories/certificate/factories-logo.png" width="" height="" alt="" />
                                 </td>
                                 <td width="25%" align="right" valign="top" style="padding-top: 45px;"><barcode code="'.$qr_code.'" size="1.4" type="QR" error="M" class="barcode" /></td>
                              </tr>
                           </table>
                        </td>
                     </tr>
                     <tr>
                        <td colspan="2" align="center" class="address"><b>NEW SECRETARIAT BUILDINGS (8th floor)</b><br/> <span>1, KIRON SANKAR ROY ROAD, KOLKATA -700001<span></td>
                     </tr>
                     <tr>
                        <td colspan="2" align="center" style="font-size:22px;color:#0b3f88;"><strong>Registration and Licence <br/>Certificate</strong></td>
                     </tr>
                     <tr>
                        <td colspan="2" align="center" id="two">&nbsp;</td>
                     </tr>
					 <tr>
                        <td colspan="2" align="center" id="two">&nbsp;</td>
                     </tr>
                     <tr>
                        <td id="three">No.: <strong>'.$marge_no.'</strong></td>
                        <td id="four" width="50%">Date: <strong>'.date('dS M Y', strtotime(date("Y-m-d"))).'</strong></td>
                     </tr>
					 <tr>
                        <td colspan="2" align="center" id="two">&nbsp;</td>
                     </tr>
                     <tr>
                        <td colspan="2" align="left" id="five">
                        
							    <p> <title>Registration certificate</title> is hereby granted to <strong>'.$grand_to.'</strong>   situated at <strong>'.$factory_line.'</strong> vide application reference no <strong>'.$application_no.'</strong> dated the <strong>'.$application_date.'</strong> to constitute a <strong>"FACTORY"</strong> as defined " <strong>Under Section '.$type.' </strong>" of the said Act. Consequently, the provisions of the following Acts and Rules are aplicable to your factory and must be adhered to:-</p><br/>
								<p><strong>&nbsp;&nbsp;&nbsp;1)</strong> The Factories Act, 1948 </p>
								<p><strong>&nbsp;&nbsp;&nbsp;2)</strong> The West Bengal Factories Rules, 1958</p> 
								<p><strong>&nbsp;&nbsp;&nbsp;3)</strong> The Payment of Wages Act, 1936</p> 
								<p><strong>&nbsp;&nbsp;&nbsp;4)</strong> The West Bengal Payment of Wages Rules, 1958</p> 
								<p><strong>&nbsp;&nbsp;&nbsp;5)</strong> The Maternity Benifit Act, 1961</p>
								<br/>
								The Registration Number of the factory is <strong>'.$max_reg_no.'</strong>  Date <strong>'.$factory_registrstion_date.'</strong><br/>
								The Classification No. of the factory is  <strong>'.$classification_no.'</strong><br/>
								The Licence No. of the factory is <strong>'.$max_license_no.'</strong><br/>
                        </td>
                     </tr>
                  </tbody>
               </table>
			    <table width="100%" border="0" cellspacing="0" cellpadding="5" style="border: 1px solid #767676;margin-top: 10px">
					<thead>
						<tr align="center">
							<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #076641;"><strong>Date of Amenability</strong></td>
							<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #076641;"><strong>Capacity (HP/KW)</strong></td>
							<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #076641;"><strong>Manpower</strong></td>
							<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #076641;"><strong>Fees Paid (Rs)</strong></td>
							<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #076641;"><strong>Payment Date</strong></td>
						</tr>
					</thead>
					<tbody>
					<tr>
							<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #000;">'.$date_of_amenability.'</td>
							<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #000;">'.$maxHP.'(HP)</td>
							<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #000;">'.$maxWorker.'</td>
							<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #000;">'.$payment_amount.'<br/>('.getCurrencyFormat($payment_amount).')</td>
							<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #000;">'.$payment_date.'</td>
					</tr>
					</tbody>
               </table>
			   
			   <p>The licence shall remain in force till <strong>'.date('dS M Y', strtotime($get_licence_valid_to)).'</strong>.</p>
			   ';
	 		if(!empty($get_all_power_data)){			   
	$content .= ' <h3 style="color:#000;padding:0;margin:0;">Renewals</h3>
			   <table width="100%" border="0" cellspacing="0" cellpadding="5" style="border: 1px solid #767676;">
					<thead>
						<tr align="center" id="seven">
							<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #076641;"><strong>Date of amenability</strong></td>
							<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #076641;"><strong>Approved Installed Capacity ( HP/KW)</strong></td>
							<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #076641;"><strong>Approved Manpower</strong></td>
							<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #076641;"><strong>Fees</strong></td>
						</tr>
					</thead>
					<tbody>
					<tr>
						<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #000;">01st Jan 2019</td>
						<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #000;">346 H.P</td>
						<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #000;">824</td>
						<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #000;">141000 /-(One lakh forty one thousands Rupees )</td>
					</tr>
					</tbody>
               </table>';
	 		}
			if(!empty($get_all_power_data)){	
				$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="5" style="border: 1px solid #8b5e39;margin-top: 10px">
					<thead>
						<tr><td colspan="7" align="center" id="six">RENEWALS</td></tr>
						<tr align="center" id="seven2">
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;">Valid up to</td>
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;">H.P</td>
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;">Worker</td>
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;">Fee for Renewal</td>
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;">Date of Payment </td>
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;">Late Fee for Renewal</td>
							<td style="border-bottom:1px solid #8b5e39;">Signature of Chief Inspector</td>
						</tr>
					</thead>
					<tbody>
						<tr id="eight">';
				foreach($get_all_power_data as $power){		
				$content .= '<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;">'.$power->service_year.'</td>
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;">'.$power->installed_power_hp.' H.P</td>
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;"></td>
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;"></td>
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;"></td>
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;"></td>
							<td style="border-bottom:1px solid #8b5e39;"></td>';
				}
			$content .= '</tr>
					</tbody>
               </table>';
			   }
			if(!empty($get_all_power_data)){	
			$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="5" style="border: 1px solid #8b5e39;margin-top: 10px">
					<thead>
						<tr><td colspan="7" align="center" id="nine">AMENDMENTS</td></tr>
						<tr align="center" id="ten">
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;">Date of Amendment</td>
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;">Amended Worker</td>
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;">Amended H.P</td>
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;">Date of Payment of Amendment fee</td>
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;">Additional Fee</td>
							<td style="border-bottom:1px solid #8b5e39;">Signature of Chief Inspector</td>
						</tr>
					</thead>
					<tbody>
						<tr id="eleven">
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;">10/05/2019</td>
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;">100</td>
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;">3</td>
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;">12/05/2019</td>
							<td style="border-bottom:1px solid #8b5e39;border-right:1px solid #8b5e39;">500</td>
							<td style="border-bottom:1px solid #8b5e39;"><img src="'.$_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/themes/wbfactories/images/certificate/signature.png" width="80" height="" alt=""/></td>
						</tr>
					</tbody>
               </table>';
			   }

     $content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0" style="padding-top: 20px">
                  <tr>
                     <td align="left"></td>
                     <td align="right" id="twelvs"></td>
                  </tr>
				  <tr>
                     <td align="left"></td>
                     <td align="right" id="twelvs"><i></i><br/>
					 <img src="'.$_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/themes/wbfactories/certificate/signature.png" width="" height="" alt=""/>
					 <br/>
					 <strong style="color:#128784;">for Chief Inspector of Factories</strong> </td>
                  </tr>
				 
               </table>
			  </div>
         </div>
      </fieldset>';
	 // echo $content; die;
				
	
				//$mpdf = new mPDF('utf-8', 'A4', '11', '11', 10, 10, 20, 10, 0, 0);
				//$mpdf->SetDisplayMode('fullpage');
				//$mpdf->SetWatermarkImage($_SERVER['DOCUMENT_ROOT'].'/factories/sites/all/themes/wbfactories/images/certificate-borders.jpg');
				//$mpdf->watermarkImageAlpha = 0.5;
				///$mpdf->showWatermarkImage = true;
				//$mpdf->WriteHTML($content);
				//$mpdf->Output('CERTIFICATE_OF FACTORIES_'.$max_license_no._.time().'.pdf','D');
	
	return pdf_using_mpdf_api($content,'REGISTRATION_CERT_'.$max_license_no._.time());
	}



// function get_licence_valid_to($service_id,$factorytype_id,$application_id,$reference_id){
// 	$sql_licecne_valid	=  db_query("SELECT calculate_end_year  FROM {fa_calculate_year} WHERE application_id = '".$application_id."' AND factory_id = '".$factorytype_id."'AND service_id = '".$service_id."'AND reference_no = '".$reference_id."' ORDER BY id DESC  LIMIT 1")->fetchObject()->calculate_end_year;
// 	return $sql_licecne_valid;
// }
	
function get_fa_cafa_log($application_id){
	$cafa_log = db_query("select * from fa_registration_licence_log WHERE fa_application_id='".$application_id."' AND is_genareate = 1 ORDER BY id DESC LIMIT 1")->fetchAll();
	return $cafa_log;
	}
	
