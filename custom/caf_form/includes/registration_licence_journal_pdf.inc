<?php
global $base_path; 
//require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';
function registration_licence_journal_pdf($form, &$form_state,$serviceid, $factory_typeid,$applicationid,$referenceid) {
	global $base_root, $base_path, $user; 
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$service_id 		= encryption_decryption_fun('decrypt', $serviceid);
	$factorytype_id 	= encryption_decryption_fun('decrypt', $factory_typeid);
	
	$get_all_data       = 	get_fa_cafa($application_id);
	//echo $application_id.'--'.$reference_id.'-'.$service_id.'--'.$factorytype_id ;die;
	
	if($get_all_data['tm_migrated_flag']!='N'){
		if($get_all_data['is_backlog']==1){
			$license_no 		= $get_all_data['backlog_license_number'];
			$registration_no 			= $get_all_data['backlog_registration_no'];
			$registration_date 	= $get_all_data['backlog_registration_date'];
			$classification_no 	= $get_all_data['backlog_classification_no'];
		}else{
		//$get_all_power_data = get_power_data($application_id,$service_id,$factorytype_id,$reference_id);
			$license_no 		= $get_all_data['factory_license_no'];
			$registration_no 			= $get_all_data['factory_registrstion_no'];
			$registration_date 	= $get_all_data['registration_date'];
			$classification_no 	= $get_all_data['classification_no'];
		}
	}else{
		
		$registration_no 	= $get_all_data['factory_registrstion_no'];
		$registration_date  = date('dS M Y', strtotime($get_all_data['registration_date']));
		$classification_no 	= $get_all_data['classification_no'];
		$license_no			= $get_all_data['factory_license_no'];	
	}
	
	
	$schedule					= $get_all_data['period_for_application'];
	$name_of_factory 			= $get_all_data['factory_name'];
	$getdata_factory_address 	= array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address 			= $get_all_data['addrline']. get_full_address('fa_cafa','sub-table',$application_id,$getdata_factory_address);
	
	$get_occupier = get_current_occupier($application_id,$service_id,$factorytype_id,$reference_id);
	//$schedule_fees = schedule_fees($application_id,$service_id,$factorytype_id,$reference_id);
	//print_r($get_occupier);die;
	$get_occupier_address 	= array('district_oprmntadr','subdivision_oprmntadr','areatype_oprmntadr','block_oprmntadr','panchayat_oprmntadr','policestation_oprmntadr','pincodeoprmntadr','state_oprmntadr','postoffice_oprmntadr');
	$occupier_address 			= $get_occupier['addrline_oprmntadr'] .get_full_address('fa_occupier_details','sub-table',$get_occupier['id'],$get_occupier_address);

	if($factorytype_id==1){ $type='2M(i)';}
	if($factorytype_id==2){ $type='2M(ii)';}
	if($factorytype_id==3){ $type='Sectin 85';}
	//echo $get_occupier['name_occupier'];die;
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
					.data{ text-transform: uppercase;font-weight:bold;}
					@page bigger { sheet-size: 420mm 370mm; }
			</style>';
			
	$content .= '<table width="100%" border="0" cellspacing="5" cellpadding="0">				
					<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden; text-transform:uppercase;">GOVERMENT OF WEST BENGAL</td></tr>
					<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden; text-transform:uppercase;"><b>Directorate of Factories</b></td></tr>
					<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden; text-transform:uppercase;"><title>LICENCE REGISTER</title></td></tr>
					</table>';
					
	$content .= '<table width="100%" cellspacing="0" cellpadding="5" style="border-bottom: 1px solid #000; border-top:1px solid #000;">
				 	<tr>
						<td align="left" ><span style="font-size:12px;font-weight:bold;">Classification No.&nbsp;</span>'.$classification_no.'</td>
						<td align="left" ><span style="font-size:12px;font-weight:bold;">Registration No.&nbsp;</span>'.$registration_no.'</td>
						<td align="left" ><span style="font-size:12px;font-weight:bold;">Date.&nbsp;</span>'.date('dS M Y', strtotime($registration_date)).'</td>
						<td align="left" ><span style="font-size:12px;font-weight:bold;">Licence No.&nbsp;</span>'.$license_no.'</td>
					</tr>
				</table>';
				
	$content .= '<table width="100%" cellspacing="0" border="5" cellpadding="0">
				 	<tr>
						<td align="left" style="font-size:12px;"><h2>Name & Address of the Factory </h2>'.$name_of_factory.'<BR>' .$factory_address.'</td>
						<td align="left" style="font-size:12px;"><h2>Name of the Occupier</h2>'.$get_occupier['name_occupier'].' '.$get_occupier['occupier_name_middle'].' '.$get_occupier['occupier_name_last'].'<BR>'.$occupier_address.'</td>
					</tr>
				</table>';
	$content .= '<table id="tabular">
				<tr>					 				
                 	<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Year </td>
					<td width="10%" style="font-size:12px;" align="left" valign="top" colspan="2"> Licence Issued for<br/>Category: '.$type.'<br/>Schedule: '.$schedule.'years<br/> </td>
					<td width="10%" style="font-size:12px;" align="left" valign="top" rowspan="2"> Amount of fee paid<br/>
					
					(a) Schedule fee<br/>
					(b) Previous Paid fee<br/>
					(c) Due Fees<br/>
					(d) Late Fees<br/>
					(e) Excess Amount
					
					</td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Date of Deposit </td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Serial no. Challan reg. </td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Excess Amount paid</td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Excess Amount adjusted</td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Entered by</td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Checked by</td>
					<td width="10%" style="font-size:12px;" align="center" valign="top" rowspan="2"> Remarks</td>
				</tr>
				<tr>					 				
					<td width="10%" style="font-size:12px;" align="center" valign="top" > HP/KW </td>
					<td width="10%" style="font-size:12px;" align="center" valign="top"> Worker </td>
				</tr>';
			//$year_data = licence_journal_detalis($application_id,$service_id,$factorytype_id,$reference_id);
			$year_data = license_register($application_id,$service_id,$factorytype_id,$reference_id);
			//print_r($year_data)	;die;
			foreach($year_data as $row){	
			
			if($row->is_previous_payment=='No'){
					$get_data       	= 	get_fa_cafa($application_id);
					
					$schedule_fees		=  	$row->schedule_fees;
					$previous_paid_fees	=	$row->previous_paid_fees;
					$due_fees			=  	$row->due_fees;
					$late_fees  		=	$row->late_fees;
					$original_excess_amount = $row->original_excess_amount;
					$date  				=	$row->date_payment;
					
					$brn_grn_challan_no	=  '-';
					$previous_paid_fees	= '-';
				}
			if($row->is_previous_payment=='Yes'){
				
				$schedule_fees		=  	$row->schedule_fees;
				$previous_paid_fees	=	$row->previous_paid_fees;
				$due_fees			=  	$row->due_fees;
				$late_fees  		=	$row->late_fees;
				$original_excess_amount = $row->original_excess_amount;
				$date  				=	$row->date_payment;
				$brn_grn_challan_no	=	$row->brn_grn_challan_no;
				
			}
			if($row->is_previous_payment==NULL){
				
				$schedule_fees		=  	$row->schedule_fees;
				$previous_paid_fees	=	$row->previous_paid_fees;
				$due_fees			=  	$row->due_fees;
				$late_fees  		=	$row->late_fees;
				$original_excess_amount = $row->original_excess_amount;
				
				$date  				=	$row->date_payment;
				$brn_grn_challan_no	=	$row->brn_grn_challan_no;
				
				
			}
			
	$content .= '<tr>					 				
					<td width="10%" align="center"> '.$row->service_year.' </td>
					<td width="10%" align="center"> '.$row->power.' </td>
					<td width="10%" align="center"> '.$row->worker.' </td>
					<td width="10%" align="left">(a)'.$schedule_fees.'<br>(b)'.$previous_paid_fees.'<br>(c)'.$due_fees.' (d)'.$late_fees.'<br>(e)'.$original_excess_amount.'</td>
					<td width="10%" align="center"> '.date('dS M Y', strtotime($date)).' </td>
					<td width="10%" align="center"> '.$brn_grn_challan_no.'</td>
					<td width="10%" align="center"> '.$previous_paid_fees.'</td>
					<td width="10%" align="center"></td>
					<td width="10%" align="center"></td>
					<td width="10%" align="center"> </td>
					<td width="10%" align="center"></td>
				</tr>';
			}			
//	$year_data = license_register($application_id,$service_id,$factorytype_id,$reference_id);
//	//print_r($year_data);die;
//			$schedule_fees 	= 0;
//			$due_fees 		= 0;
//			$late_fees 		= 0;
//			$fees_to_paid 	= 0;
//			foreach($year_data as $row){
//			if($row->is_previous_payment=='No'){
//					$get_data       	= 	get_fa_cafa($application_id);
//					$service_fees  		=  $get_data['service_fees'];
//					$payment_amount  	=  $get_data['payment_amount'];
//					$date  				=  $get_data['payment_date'];
//					$excess  			=  $get_data['original_excess_amount'];
//					$brn_grn_challan_no	=	'-';
//					$previous_paid_fees	=	'-';
//				}
//			if($row->is_previous_payment=='Yes'){
//				$service_fees  		=	1000;
//				$due_fees			=  	$row->due_fees;
//				$payment_amount  	=	($row->schedule_fees+$row->late_fees);
//				$date  				=	$row->date_payment;
//				$brn_grn_challan_no	=	$row->brn_grn_challan_no;
//				$previous_paid_fees	=	$row->previous_paid_fees;
//			}
//			
//			$grn_brn_no = payment_dts($row->application_id);
//			foreach($grn_brn_no as $grn){
//				$numbers = $grn->brn_grn_challan_no;
//				$grn_date = $grn->date_payment;
//			}
//	$content .= '<tr>					 				
//					<td width="10%" align="center"> '.$row->service_year.'</td>
//					<td width="10%" align="center"> '.$row->power.' </td>
//					<td width="10%" align="center"> '.$row->worker.' </td>
//					<td width="10%" align="left">(a)'.$row->schedule_fees.'<br>(b)'.$total->previous_paid_fees.'<br>(c)'.$row->due_fees.'<br>(d)'.$total->late_fees.'</td>
//					<td width="10%" align="center"> '.$grn_date.' </td>
//					<td width="10%" align="center"> '.$numbers.'</td>
//					<td width="10%" align="center"> </td>
//					<td width="10%" align="center"></td>
//					<td width="10%" align="center"></td>
//					<td width="10%" align="center"> </td>
//					<td width="10%" align="center"></td>
//				</tr>';
//			}
				
	$content .= '</table>';
				// $mpdf = new mPDF('utf-8', 'A4-L', '11', '11', 10, 10, 20, 10, 0, 0,'L');
				// $mpdf->SetDisplayMode('fullpage');
				// $mpdf->WriteHTML($content);
				// $mpdf->Output('LICENCE_REGISTER_'._.time().'.pdf','D');
				
	return pdf_using_mpdf_api($content,'caf-journal'._.time());
}

function license_register($application_id,$service_id,$factory_typeid,$reference_number){
	$query_year		= 	db_select('fa_calculates_license_fees', 'year');
	$query_year		->	fields('year',array('id','service_year','worker','power','schedule_fees','late_fees','due_fees','application_id','application_reference_no','previous_paid_fees','factory_type','service_id','original_excess_amount'));	
	$query_year		->	InnerJoin('fa_cafa', 'cafa', 'cafa.id = year.application_id');
	//$query_year		->	leftJoin('fa_manual_payment_history', 'history', 'history.application_id = year.application_id');
	$query_year		->	fields('cafa', array('is_previous_payment'));
	//$query_year		->	fields('history', array('date_payment','brn_grn_challan_no'));
	$query_year		-> 	condition('year.application_id', $application_id);
	$query_year		-> 	condition('year.service_id', $service_id);
	$query_year		-> 	condition('year.factory_type', $factory_typeid);
	$query_year		-> 	condition('year.application_reference_no', $reference_number);
	//$query_year		-> 	condition('year.is_active_year', 1);
	$query_year		->	orderBy('year.id', 'ASC');
	//echo $query_year;die;
	$result_year	=   $query_year->execute()->fetchAll();
	return $result_year;
	

}

