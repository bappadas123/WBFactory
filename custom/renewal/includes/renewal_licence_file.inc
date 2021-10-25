<?php
global $base_path;
require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';
function renewal_licence_file($serviceid,$factory_typeid,$applicationid,$referenceid) {	
//echo  $serviceid.'<br/>'.$factory_typeid.'<br/>'.$applicationid.'<br/>'.$referenceid;die;
	global $base_root, $base_path, $user; 
	$service_id 		= encryption_decryption_fun('decrypt', $serviceid);
	$factorytype_id 	= encryption_decryption_fun('decrypt', $factory_typeid);
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	
	$get_all_data      	= 	get_fa_cafa($application_id);

	$max_license_no 	= $get_all_data['factory_license_no'];
	$max_reg_no 		= $get_all_data['factory_registrstion_no'];
	$application_no 	= $get_all_data['factory_reg_identification_number'];
	$application_date 	= date('dS M Y', strtotime($get_all_data['created_date']));
	$zonid 				= $get_all_data['factory_zone'];
	$zone 				= get_factory_zone_name($zonid);
	$payment_amount		= $get_all_data['payment_amount'];
	$district_code		= $get_all_data['district'];
	
		
	$name_of_factory 			= $get_all_data['factory_name']; //die;
	$amenability_date 			= $get_all_data['date_of_amenability'];
	$classification_no			= $get_all_data['classification_no'];
	$factory_owershiptype 		= $get_all_data['factory_owershiptype'];
	$date_of_amenability 		= date('dS M Y', strtotime($amenability_date));
	
	$getdata_factory_address 	= array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address 			= $get_all_data['addrline'].',&nbsp;'.get_full_address_certificates('fa_cafa','sub-table',$application_id,$getdata_factory_address);
	
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
	
			
		$get_all_nature_data 		= get_nature_manufacture_data($application_id);
		$get_all_power_data 		= get_power_data($application_id,$service_id,$factorytype_id,$reference_id);
		$worker_details 			= get_worker_details_service($service_id,$factorytype_id,$application_id,$reference_id);
	
		$get_licence_valid_to 		= get_licence_valid_to($service_id,$factorytype_id,$application_id,$reference_id);
		
		$get_licence_valid_from 	= get_licence_valid_from($service_id,$factorytype_id,$application_id,$reference_id);
			//echo  $service_id.'--'.$factorytype_id.'--'.$application_id.'--'.$reference_id;die($get_licence_valid_from);

		$maxWorker = 0;
		foreach($worker_details as $worker){$max_worker = $worker->worker_total;$maxWorker = max($max_worker, $maxWorker);}
		
		$maxHP = 0;
		foreach($get_all_power_data as $power){$max_hp = $power->installed_power_hp;$maxHP = max($max_hp, $maxHP);}	
		$all_licese_list  =  get_all_license_log($application_id);
		
		foreach($all_licese_list as $licese_list){
			$emp_id = $licese_list->fa_issue_by;
		}
		
		$valid_to  = get_fa_cafa_log($application_id);
		foreach($valid_to as $valid){
			$valid_date = $valid->fa_licence_valid_to;
			
			}
		//echo $get_licence_valid_to.'------'.$valid_date;exit;
		
		if($get_licence_valid_to != $valid_date){
			$data 	=  array(
				'fa_name'				=> $grand_to ,
				'fa_license_no'			=> $max_license_no,
				'fa_registartion_no' 	=> $max_reg_no,
				'fa_amenability_date' 	=> $get_all_data['date_of_amenability'],
				'fa_power' 				=> $maxHP,
				'fa_worker' 			=> $maxWorker,
				'fa_fees' 				=> $payment_amount,
				'fa_licence_valid_to' 	=> $get_licence_valid_to,
				'fa_issue_by'			=> 40,
				'fa_issue_date' 		=> date("Y-m-d"),
				'fa_payment_date' 		=> $payment_date,
				'fa_application_id'		=> $application_id ,
				'fa_service_id'			=> $service_id,
				'fa_active_inactive' 	=> 1,
				'is_genareate'			=> 1
			);
				
			$exist_data = db_insert('fa_registration_licence_log')->fields($data)->execute();
			
				if(!empty($exist_data)){
				$caf_update 	= 	array( 'license_valid_upto' => $get_licence_valid_to);
				$queryabc 		=	db_update('fa_cafa');
				$queryabc		->	fields($caf_update);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc	    ->	execute();
			}
		}
		
		$renewal_list = get_renewal_power_worker($application_id,$factorytype_id,$service_id,$reference_id);
		foreach($renewal_list as $valid){
			$validity_date 		= $valid->fa_licence_valid_to;
			$license_no 		= $valid->fa_license_no;
			$fa_registartion_no = $valid->fa_registartion_no;
			$fa_fees 			= $valid->fa_fees;
			$fa_power 			= $valid->fa_power;
			$fa_worker 			= $valid->fa_worker;
			$fa_payment_date	= $valid->fa_payment_date;
		}
	
	
	if($factorytype_id=='1'){
		$type= '2M(i)';
		}if($factorytype_id=='2'){
			$type= '2M(ii)';
			}if($factorytype_id=='3'){
				$type= '85';
				}
		
	//$max_license_no 			= $get_all_data['factory_license_no'];
	//$max_reg_no 				= $get_all_data['factory_registrstion_no'];

	//print_r($img_url);die();
	$marge_no			=   $max_reg_no.'/'.$max_license_no.'/'.$counter;
	$barcode 			=	'Inspector General';
	//$barcode 				=	get_role_name($emp_id);
	//echo $barcode;die($emp_id);
	$qr_code				='Granted to:-'.$grand_to.'&nbsp;Registration No:-'.$max_reg_no.'&nbsp;Licecne No:-'.$max_license_no.'&nbsp;Licence valid from:-'.$get_licence_valid_from.'&nbsp;Licence valid to:-'.$get_licence_valid_to.'&nbsp;Power:'.$maxHP.'&nbsp;Worker:-'.$maxWorker.'&nbsp;Fees:-'.$payment_amount.
	
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
	$content .= '<div style="padding:50px 60px 150px 50px;background:url('.$_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/themes/custom_dashboard/images/renewal_bg.png) no-repeat center center;">';	
	}else{
	
	$content .= '<div style="padding:50px 60px 60px 50px;background:url('.$_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/themes/custom_dashboard/images/renewal_bg.png) no-repeat center center;">';
	}
	
	$content .= '<table width="100%" border="0" >
                  <tbody>
                     <tr>
                        <td colspan="2">
                           <table width="100%" border="0">
                              <tr>
                                 <td align="right" valign="top" ><img src="'.$_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/themes/wbfactories/certificate/factories-logo.png" width="" height="" alt="" />
                                 </td>
                                 <td width="25%" align="right" valign="top" style="padding-top: 45px;"><barcode code="'.$qr_code.'" size="1.6" type="QR" error="M" class="barcode" /></td>
                              </tr>
                           </table>
                        </td>
                     </tr>
                     <tr>
                        <td colspan="2" align="center" class="address"><b>NEW SECRETARIAT BUILDINGS (8th floor)</b><br/> <span>1, KIRON SANKAR ROY ROAD, KOLKATA -700001<span></td>
                     </tr>
                     <tr>
                        <td colspan="2" align="center" style="font-size:22px;color:#0b3f88;"><strong>Renewal of Licence</strong></td>
                     </tr>
                     <tr>
                        <td colspan="2" align="center" id="two">&nbsp;</td>
                     </tr>
					 <tr>
                        <td colspan="2" align="center" id="two">&nbsp;</td>
                     </tr>
                     <tr>
                        <td id="three">No.: <strong>'.$marge_no.'</strong></td>
                        <td id="four" width="50%">Date: <strong>'.date('dS M Y', strtotime(date($get_all_data['modification_date']))).'</strong></td>
                     </tr>
					 <tr>
                        <td colspan="2" align="center" id="two">&nbsp;</td>
                     </tr>
                     <tr>
                        <td colspan="2" align="left" id="five">
                        
							    <p> <title>Registration and Licence certificate</title> is hereby granted to <strong>'.$grand_to.'</strong>   situated at <strong>'.$factory_address .'</strong> vide application reference no <strong>'.$application_no.'</strong> dated the <strong>'.$application_date.'</strong> to constitute a <strong>"FACTORY"</strong> as defined " <strong>Under Section '.$type.' </strong>" of the said Act. Consequently, the provisions of the following Acts and Rules are aplicable to your factory and must be adhered to:-</p><br/>
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
			   
			   ';
			   
			   
	 if(empty($all_licese_list)){			   
	$content .= ' <h3 style="color:#000;padding:0;margin:0;">Renewals</h3>
			   <table width="100%" border="0" cellspacing="0" cellpadding="5" style="border: 1px solid #767676;">
					<thead>
						<tr align="center" id="seven">
							<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #076641;"><strong>Date of amenability</strong></td>
							<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #076641;"><strong>Capacity (HP/KW)</strong></td>
							<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #076641;"><strong>Manpower</strong></td>
							<td style="border-bottom:1px solid #767676;border-right:1px solid #767676;font-size: 13px;color: #076641;"><strong>Amount (Rs)</strong></td>
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
               </table>';
			   }
	$content .= '<p>The licence shall remain in force from <strong>'.date('dS M Y', strtotime($get_licence_valid_from)).'</strong> till <strong>'.date('dS M Y', strtotime($get_licence_valid_to)).'</strong>.</p> ';
	
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0" style="padding-top: 20px">
                  <tr>
                     <td align="left"></td>
                     <td align="right" id="twelvs"></td>
                  </tr>
				  <tr>
                     <td align="left"></td>
                     <td align="right" id="twelvs" style="padding:0"><br/><barcode code="'.$barcode.'" type="C39" size="1.0" height="0.7" /></td>
                  </tr>
				 
               </table>
			   <p><br/><br/><strong>**</strong><i>This Renewal Certificate is system generated and does not require any Signature. For authenticity please Scan the QR Code<i/></p>
			   
			  </div>
         </div>
	  </fieldset>';
	 // echo get_role_id($user->rid);die;
	//return pdf_using_mpdf_api($content,'licecne_file'._.time());
	if($get_licence_valid_to == $valid_date){
						//$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 20, 10, 0, 0);
						//$mpdf->SetDisplayMode('fullpage');
						//$mpdf->SetHTMLHeader(' <div style="padding-top:50px; text-align: right; font-size:9px;">Page {PAGENO} of {nb}</div>');
						//$mpdf->SetWatermarkText('DRAFT COPY');
						//$mpdf->showWatermarkText = FALSE;
						//$mpdf->WriteHTML($content);
						//$mpdf->Output('LICENCE_RENEWAL_'.$max_license_no.'_'.time().'.pdf','D');
						return pdf_using_mpdf_api($content,'LICENCE_RENEWAL_CERT_'.$max_license_no._.time());
	}else{
		//return drupal
		
			if(get_role_id($user->rid)==13){
				drupal_set_message('Licence certificate has been successfully generated');
				
			}else{
				drupal_set_message('Licence certificate has been successfully generated');
				drupal_goto('applicant-dashboard');
			}

			
		}
	
	}
function get_licence_valid_from($service_id,$factorytype_id,$application_id,$reference_id){
	$sql_licecne_valid_from	=  db_query("SELECT calculate_starting_year  FROM {fa_calculate_year} WHERE application_id = '".$application_id."' AND factory_id = '".$factorytype_id."'AND service_id = '".$service_id."'AND reference_no = '".$reference_id."' ORDER BY id ASC  LIMIT 1")->fetchObject()->calculate_starting_year;
	return $sql_licecne_valid_from;
	
	}
function get_renewal_power_worker($application_id,$factory_type_id,$service_id,$reference_no){
	$power_worker_current = db_query("select * from fa_registration_licence_log WHERE fa_application_id='".$application_id."' AND fa_service_id = 2 ORDER BY id DESC LIMIT 1")->fetchAll();
	return $power_worker_current;
	}
function get_fa_cafa_log($application_id){
	$cafa_log = db_query("select * from fa_registration_licence_log WHERE fa_application_id='".$application_id."' AND is_genareate = 1 ORDER BY id DESC LIMIT 1")->fetchAll();
	return $cafa_log;
	}
function get_all_license_log($application_id){
	$all_license_log = db_query("select * from fa_registration_licence_log WHERE fa_application_id='".$application_id."' AND is_genareate = 1 AND fa_service_id = 3 ORDER BY id DESC")->fetchAll();
	return $all_license_log;
	}