<?php
global $base_path;
require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';
function amendment_certificate($serviceid,$factory_typeid,$applicationid,$referenceid) {	
	//echo  $serviceid.'<br/>'.$factory_typeid.'<br/>'.$applicationid.'<br/>'.$referenceid;die;
	global $base_root, $base_path, $user; 
	$service_id 		= encryption_decryption_fun('decrypt', $serviceid);
	$factorytype_id 	= encryption_decryption_fun('decrypt', $factory_typeid);
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	
	$get_all_data      	= 	get_fa_cafa($application_id);
//print_r($get_all_data);die;
	$max_license_no 	= $get_all_data['factory_license_no'];
	$max_reg_no 		= $get_all_data['factory_registrstion_no'];
	
	$application_no 	= $get_all_data['factory_reg_identification_number'];
	$application_date 	= date('dS M Y', strtotime($get_all_data['created_date']));
	$zonid 				= $get_all_data['factory_zone'];
	$zone 				= get_factory_zone_name($zonid);
	$payment_amount		= $get_all_data['payment_amount'];
	$district_code		= $get_all_data['district'];
	
	$factory_registrstion_date 		= date('dS M Y', strtotime($get_all_data['registration_date']));
	
		
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
	
	$get_all_nature_data 		= get_nature_manufacture_service($application_id);
	 $get_all_power_data 		= get_power_amendment_service($application_id,$service_id,$factorytype_id,$reference_id);
	 $worker_details 			= get_worker_amendment_service($service_id,$factorytype_id,$application_id,$reference_id);
	
	// echo  $service_id.'--'.$factorytype_id.'--'.$application_id.'--'.$reference_id;die($get_licence_valid_from);
	
	
	$get_licence_valid_to 		= get_amendment_licence_valid_to($service_id,$factorytype_id,$application_id,$reference_id);
		
	$get_licence_valid_from 	= get_amendment_licence_valid_from($service_id,$factorytype_id,$application_id,$reference_id);
			

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
			//print_r($data);die;
			$exist_data = db_insert('fa_registration_licence_log')->fields($data)->execute();
				if(!empty($exist_data)){
				$caf_update 	= 	array( 'license_valid_upto' => $get_licence_valid_to);
				$queryabc 		=	db_update('fa_cafa');
				$queryabc		->	fields($caf_update);
				$queryabc		->	condition('id',$application_id,'=');
				$queryabc	    ->	execute();
			}
		}
		
	//$amendment_list = get_amendment_power_worker($application_id,$factorytype_id,$service_id,$reference_id);
	$amendment_list = fetch_old_data($application_id,$service_id,$factorytype_id,$reference_id);

	$pre_view	=	get_previous_details_view($application_id,$reference_id,$factorytype_id,$service_id);
	//print_r($amendment_list);die($application_id.'--'.$factorytype_id.'--'.$service_id.'--'.$reference_id);
	//print_r($amendment_list);die;
	foreach($amendment_list as $valid){
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
	}
	if($factorytype_id=='2'){
		$type= '2M(ii)';
	}
	if($factorytype_id=='3'){
		$type= '85';
	}
		
	//$max_license_no 			= $get_all_data['factory_license_no'];
	//$max_reg_no 				= $get_all_data['factory_registrstion_no'];

	$img_url					= $_SERVER['DOCUMENT_ROOT']. $base_path.'sites/all/themes/wbfactories/images/em.jpg';
	$marge_no			=   $max_reg_no.'/'.$max_license_no.'/'.$counter;
	//$barcode 			=	'Inspector Deputy';
	
	$barcode 				=	get_name($emp_id);
	//echo $barcode;die($emp_id);
	$qr_code				='Granted to:-'.$grand_to.'&nbsp;Registration No:-'.$max_reg_no.'&nbsp;Licecne No:-'.$max_license_no.'&nbsp;Licence valid from:-'.$get_licence_valid_from.'&nbsp;Licence valid to:-'.$get_licence_valid_to.'&nbsp;Power:'.$maxHP.'&nbsp;Worker:-'.$maxWorker.'&nbsp;Fees:-'.$payment_amount.
	

	//echo $get_licence_valid_to.'---'. $valid_date;die;
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
					</style>';
					$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">				
						<tr><td colspan="3"></td></tr>
						
						<tr><td colspan="3" align="center" style="font-size:15px;text-transform:uppercase;"><h2> FORM-3 </h2></td></tr>
						<tr><td colspan="3"  align="center" style="font-size:10px;">[See rules5(1),6(4),7(1) and 8(2)]</td></tr>
						<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden; text-transform:uppercase;">GOVERMENT OF WEST BENGAL</td></tr>
						<tr><td colspan="3" align="center"><img src="'.$img_url.'" width="40px"/></td></tr>
						
						<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden; text-transform:uppercase;">Directorate of Factories</td></tr>
						</table>';			
					$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tr><td colspan="3" align="center" style="font-size:18px;"><h3 style="border-bottom:0px solid;"><title>LICENCE TO WORK A FACTORY</title></h3></td></tr>
					<tr><td colspan="3"></td></tr>
					<tr><td colspan="3" align="left" >Licence No.&nbsp;<b>'.$max_license_no.'</b> Reg. No.&nbsp;<b>'.$max_reg_no.'</b> .&nbsp;Date of amenability  <span class="data">&nbsp;'.$date_of_amenability .'</span> &nbsp; H.P  <span class="data">'.$maxHP.'</span> &nbsp; Worker <span class="data"> '.$maxWorker.'&nbsp;</span> Fee Rs. '.$payment_amount.'/- &nbsp; 
					Licence is hereby granted to<span class="data"> '.$grand_to.', </span> valid only for the factory knowns as  <span class="data">&nbsp;'.$name_of_factory.'</span>&nbsp;&nbsp;situated at &nbsp;&nbsp;<span class="data">' .$factory_address.'</span>, subject provisions of the Factories Act, 1948, and the rules made thereunder.</td></tr>
					<tr><td>&nbsp;</td></tr>
					<tr><td colspan="3" align="left" style="font-size:12px;">The licence shall remain in force till <b>'.date('dS M Y', strtotime($get_licence_valid_to)).'</b></td></tr>
					<tr>
						<td colspan="2" align="left" style="font-size:12px;">The '.date('dS M Y', strtotime($lic_date)).'</td>

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
					
					foreach($renewal_amendment_list as $renew){
					if($renew->remark==NULL && $renew->service_id==3){
						$payment_date		= $get_all_data['payment_date'];

						$content .= '<tr>					 				
						<td width="14%"> '.$renew->service_year.'</td>
						<td width="10%"> '.$renew->power.'</td>
						<td width="14%">'.$renew->worker.' </td>
						<td width="14%">'.($renew->previous_paid_fees+$renew->due_fees).' </td>
						<td width="14%"> '.date('dS M Y', strtotime($payment_date)) .'</td>
						<td width="14%"> '.$renew->late_fees.'</td>
						<td width="18%"> </td>
						</tr>';
						}
					}

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
					if(!empty($pre_view)){
						foreach($pre_view as $view){
							if($view->is_previous == 'Yes'){
								$content .= '<tr>					 				
									<td width="25%">'.$view->conversation_name.'</td>
									<td width="25%"> '.$view->change_date.' </td>
									<td width="25%"> '.$view->change_date.'</td>
									<td width="25%"> </td>
								</tr>';
							}
					
						}

					}
				

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
				foreach($amendment_list as $amend){
					if($amend->is_amendment =="1"){
						$payment_date	= $get_all_data['payment_date'];
				$content .= '<tr>					 				
						<td width="14%"> '.$amend->service_year.'</td>
						<td width="10%"> '.$amend->installed_power_hp.' (HP)</td>
						<td width="14%">'.$amend->worker_total.' </td>
						<td width="14%">'.($amend->previous_paid_fees+$amend->due_fees).' </td>
						<td width="14%"> '.date('dS M Y', strtotime($payment_date)) .'</td>
						<td width="14%"> '.$amend->previous_paid_fees.'</td>
						</tr>';
						}
					}
				$content .= '</table>';
	 

	if($get_licence_valid_to == $valid_date){
		//die('cheking...');
		return pdf_using_mpdf_api($content,'LICENCE_RENEWAL_CERT_'.$get_licence_valid_from._.time());
						
	}else{
		//return drupal
			drupal_set_message('Amendment certificate has been successfully generated');
			drupal_goto('amendment-list-deputy') ;
		}
}

function get_amendment_licence_valid_to($service_id,$factorytype_id,$application_id,$reference_id){
	//echo $service_id.'-----'.$factorytype_id.'-----'.$application_id.'-----'.$reference_id;die;
	$sql_licecne_valid	=  db_query("SELECT calculate_end_year  FROM {fa_amendment_year_data} WHERE application_id = '".$application_id."' AND factory_type = '".$factorytype_id."'AND service_id = '".$service_id."'AND referance_id = '".$reference_id."' ORDER BY id DESC  LIMIT 1")->fetchObject()->calculate_end_year;
	//echo "SELECT calculate_end_year  FROM {fa_amendment_year_data} WHERE application_id = '".$application_id."' AND factory_type = '".$factorytype_id."'AND service_id = '".$service_id."'AND referance_id = '".$reference_id."' ORDER BY id DESC  LIMIT 1";die;
	return $sql_licecne_valid;
	
	}
function get_amendment_licence_valid_from($service_id,$factorytype_id,$application_id,$reference_id){
	$sql_licecne_valid_from	=  db_query("SELECT calculate_starting_year  FROM {fa_amendment_year_data} WHERE application_id = '".$application_id."' AND factory_type = '".$factorytype_id."'AND service_id = '".$service_id."'AND referance_id = '".$reference_id."' ORDER BY id ASC  LIMIT 1")->fetchObject()->calculate_starting_year;
	return $sql_licecne_valid_from;
	
	}


	
function get_amendment_power_worker($application_id,$factory_type_id,$service_id,$reference_no){
	$power_worker_current = db_query("select * from fa_registration_licence_log WHERE fa_application_id='".$application_id."' AND fa_service_id = 8 ORDER BY id DESC LIMIT 1")->fetchAll();
	return $power_worker_current;
	}
function get_fa_cafa_log($application_id){
	$cafa_log = db_query("select * from fa_registration_licence_log WHERE fa_application_id='".$application_id."' AND is_genareate = 1 AND fa_service_id = 8 ORDER BY id DESC LIMIT 1")->fetchAll();
	return $cafa_log;
	}
function get_all_license_log($application_id){
	$all_license_log = db_query("select * from fa_registration_licence_log WHERE fa_application_id='".$application_id."' AND is_genareate = 1 AND fa_service_id = 8 ORDER BY id DESC")->fetchAll();
	return $all_license_log;
	}