<?php

function registration_notesheet_file($serviceid, $factory_typeid,$applicationid,$referenceid) {	

	global $base_root, $base_path, $user; 
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$service_id 		= encryption_decryption_fun('decrypt', $serviceid);
	$factorytype_id 	= encryption_decryption_fun('decrypt', $factory_typeid);
	
	
	$get_all_data       = 	get_fa_cafa($application_id);
	//print_r($get_all_data);die;
	//echo $application_id;//die;
	if($get_all_data['tm_migrated_flag']!='N'){
		if($get_all_data['is_backlog']==1){
			$registration_no 	= $get_all_data['backlog_registration_no'];
			$reg_date 			= date('dS M Y', strtotime($get_all_data['backlog_registration_date']));
			$classification_no 	= $get_all_data['backlog_classification_no'];
			$license_no			= $get_all_data['backlog_license_number'];
		
		}else{
			$registration_no	 =!empty( $get_all_data['factory_registrstion_no'])?$get_all_data['factory_registrstion_no']:'N/A';
			$reg_date  =       !empty($get_all_data['registration_date'])?date('dS M Y', strtotime($get_all_data['registration_date'])):'N/A';
			$classification_no  = !empty($get_all_data['classification_no'])?$get_all_data['classification_no']:'N/A';
			$license_no			= !empty($get_all_data['factory_license_no'])?$get_all_data['factory_license_no']:'N/A';
		
		}
	}else{
			$registration_no	 =!empty( $get_all_data['factory_registrstion_no'])?$get_all_data['factory_registrstion_no']:'N/A';
			$reg_date  =       !empty($get_all_data['registration_date'])?date('dS M Y', strtotime($get_all_data['registration_date'])):'N/A';
			$classification_no  = !empty($get_all_data['classification_no'])?$get_all_data['classification_no']:'N/A';
			$license_no			= !empty($get_all_data['factory_license_no'])?$get_all_data['factory_license_no']:'N/A';
		
		}
	
	$get_all_power_data = get_power_data($application_id,$service_id,$factorytype_id,$reference_id);
	$service_fees 		= NULL;
	
	$get_comment_data		= get_comment_data($application_id,$service_id,$factorytype_id,$reference_id);
	
	$get_all_notesheet_data = get_notesheet_data($application_id,$service_id,$factorytype_id,$reference_id);
	
	$manual_payment_deatils	= manual_payment_deatils($application_id,$service_id,$factorytype_id,$reference_id);
	
	$name_of_factory 			= 	!empty($get_all_data['factory_name'])? $get_all_data['factory_name'] : 'Nil'; //die;
	$amenability_date 			= 	!empty($get_all_data['date_of_amenability'])? $get_all_data['date_of_amenability'] : 'Nil'; //die;
	$date_of_amenability 		= 	format_date(strtotime($amenability_date) ,'custom','j F, Y');
	$type_of_factory 			= 	!empty($get_all_data['factory_typeid'])? $get_all_data['factory_typeid'] : 'Nil'; //die;
	if($type_of_factory==1){ $type='2M(i)';}
	if($type_of_factory==2){ $type='2M(ii)';}
	if($type_of_factory==3){ $type='Sectin 85';}
	
	$getdata_factory_address 	=  	array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address 			=	$get_all_data['addrline'].get_full_address('fa_cafa','sub-table',$application_id,$getdata_factory_address);
	
	
	$fees_details				= 	fee_details_show($application_id,$service_id,$factorytype_id,$reference_id,$service_fees);
	
	
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
						
						border-top: 1px solid;
						border-bottom: 1px solid;
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
					.data{ text-transform: uppercase;text-decoration: underline;"}
			</style>';
			
			
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">				
					<tr><td align="center" colspan="5" style="font-size:15px; text-transform:uppercase;"><b>GOVERMENT OF WEST BENGAL</b></td></tr>
					<tr><td align="center" colspan="5" style="font-size:15px; text-transform:uppercase;">Directorate of Factories</td></tr>
					<tr><td align="center" colspan="5" style="font-size:12px;">(To be filled up after final Order)<br><br><br></td></tr>
				
					<tr>
						<td width="5%" style="font-size:12px;">(a)</td>
						<td width="30%" style="font-size:12px;">Registration No.</td>
						<td width="65%" style="font-size:12px;" colspan="2" ><span style="font-size:12px">'.$registration_no.'</span></td>
					</tr>
					<tr>
						<td width="5%" style="font-size:12px;" >(b)</td>
						<td width="30%" style="font-size:12px;">Date of Registration.</td>
						<td width="65%" style="font-size:12px;" colspan="2"><span style="font-size:12px">'.$reg_date.'</span></td>
					</tr>
					<tr>
						<td width="5%" style="font-size:12px;">(c)</td>
						<td width="30%" style="font-size:12px;" >Classification</td>
						<td width="65%" style="font-size:12px;" colspan="2"><span style="font-size:12px">'.$classification_no.'</span></td>
					</tr>
					<tr>
						<td width="5%" style="font-size:12px;">(d)</td>
						<td width="30%" style="font-size:12px;">Licence</td>
						<td width="65%" style="font-size:12px;" colspan="2"><span style="font-size:12px">'.$license_no.'</span></td>
					</tr>
					<tr>
						<td width="5%" style="font-size:12px;">(e)</td>
						<td width="30%" style="font-size:12px;">Jurisdiction Areas</td>
						<td width="65%" style="font-size:12px;" colspan="2"><span style="font-size:12px">'.zone_name($get_all_data['factory_zone']).'</span></td>
					</tr>
					<tr><td style="font-size:12px;" colspan="5"><br/><title>Note sheet</title> for Registration of a Factory</td></tr>
					<tr><td style="font-size:12px;" colspan="5" ><u>'.$type.'</u> of the Act. </td></tr>
					<tr>
						<td align="left" style="font-size:12px;" colspan="2"><br/>Name of the Factory: </td>
						<td  style="font-size:12px;"><br/><b>' .$name_of_factory.'</b></td>
					</tr>
					<tr>
						<td align="left" style="font-size:12px;" colspan="2">Address : </td>
						<td  style="font-size:12px;"><b>'.$factory_address.'</b></td>
					</tr>
					<tr>
						<td align="left" style="font-size:12px;" colspan="5"><br/>Perticulars of Form No. 2 and Challans, as received and recorded are furnised bellow and duplicate copy of Form No. 2 is out up for order please.</td>
					</tr>
					<tr>
						<th align="center" style="font-size:12px;">Year</th>
						<th align="center" style="font-size:12px;">GRN/BRN NO.</th>
						<th align="center" style="font-size:12px;">Date of Deposit</th>
						<th align="center" style="font-size:12px;">Amount</th>
						<th align="center" style="font-size:12px;">Remarks</th>
					</tr>';
					
						
			//print_r($year_data);die;
		foreach($manual_payment_deatils as $history){
					
			$content .= '<tr>					 				
							<td align="center">  </td>
							<td align="center">'.$history->brn_grn_challan_no.'</td>
							<td align="center"> '.date('dS M Y', strtotime($history->date_payment)).' </td>
							<td align="center">'.$history->payment_amount.' </td>
							<td align="center"> </td>
						</tr>';
			}
		
		
					
		$content .= '<tr><td align="right" style="font-size:12px;" colspan="5">____________________________________</td></tr>
					<tr><td align="right" style="font-size:12px;" colspan="5">Head Cleark/SIC/D.A. Regst. Section</td></tr>
					<tr><td align="right" style="font-size:12px;" colspan="5">Date: _____________________________<br><br><br></td></tr>';
					
		$content .= $fees_details;
		//print_r($get_comment_data);die;	
		foreach($get_comment_data as $notesheet){

		if($notesheet->remark_by_roleid == 9  && $notesheet->remark_to_roleid == 10 && $notesheet->status=="DC"){
				$note_details =  get_notesheet_data_details($notesheet->id);
				foreach($note_details as $data){
					
					$application_id 		= $data->application_no;
					$service_id 			= $data->service_id;
					$factory_type_id 		= $data->factory_type_id;
					$reference_no 			= $data->referance_no;
					$get_fa_cafa			= get_fa_cafa($application_id);
					$getdata_owner_address	= array('district_premises','subdivision_premises','areatype_premises','block_premises','panchayat_premises','policestation_premises','pincodepremises','state_premises','postoffice_premises');
					$owner_address			= $get_fa_cafa['addrline_premises'].'<br/>'.get_full_address('fa_cafa','sub-table',$get_fa_cafa['id'],$getdata_owner_address);
					
					if(!empty($data->close_reg_no)){$close_reg_no = $data->close_reg_no;}else{ $close_reg_no = 'Nil'; }
					if(!empty($data->date_restart)){$restart_date = date('dS M Y', strtotime($data->date_restart));}else{ $restart_date = 'Nil'; }
					if(!empty($data->date_cossed)){$date_cossed = date('dS M Y', strtotime($data->date_cossed));}else{ $date_cossed = 'Nil'; }
					if(!empty($data->date_shift_amenability)){$date_shift_amenability = date('dS M Y', strtotime($data->date_shift_amenability));}else{ $date_shift_amenability = 'Nil'; }
					
					$dates = explode(',', $data->dates);
		$content .= '<tr>
						<td align="left" style="font-size:12px;"  colspan="5">'.get_name($notesheet->remark_to_user).'<br><u>DY. Director / DY. CIF</u></td>
					</tr>
					<tr>
						<td width="5%"  align="left" valign="top" style="font-size:12px;">1. </td>
						<td width="30%" align="left" valign="top" style="font-size:12px;">Date of Visit: </td>
						<td width="65%" align="left" valign="top" style="font-size:12px;" colspan="2">'; foreach($dates as $date){ 
						$content .= '<b>'. date('dS M Y', strtotime($date)).',&nbsp;</b>';
						}
		$content .= '</td>
					</tr>
					<tr>
						<td width="5%"  align="left" valign="top" style="font-size:12px;">2. </td>
						<td width="95%"  align="left" valign="top" style="font-size:12px;" colspan="3">In case of new or existing factory coming under the purview of the Act:</td>
					</tr>
					<tr>
						<td width="5%"  align="left" valign="top" style="font-size:12px;"> </td>
						<td width="30%" align="left" valign="top" style="font-size:12px;">(a) Date of starting: <b>'.date('dS M Y', strtotime($data->factory_starting)).'</b></td>
						<td width="65%" align="left" valign="top" style="font-size:12px;" colspan="2">(b) Date of Amenability: <b>'.date('dS M Y', strtotime($data->factory_amenabity_date)).'</b></td>
					</tr>
					<tr>
						<td width="5%"  align="left" valign="top" style="font-size:12px;">3. </td>
						<td width="95%"  align="left" valign="top" style="font-size:12px;" colspan="3">In case of an old registered factory crossed/closed down /shifted- : </td>
					</tr>
					<tr>
						<td width="5%"  align="left" valign="top" style="font-size:12px;"> </td>
						<td width="30%" align="left" valign="top" style="font-size:12px;">(a) Registn No.: <b>'.$close_reg_no.'</b></td>
						<td width="65%" align="left" valign="top" style="font-size:12px;" colspan="2">(b) Date of Restarting: <b>'.$restart_date.'</b></td>
					</tr>
					<tr>
						<td width="5%"  align="left" valign="top" style="font-size:12px;"> </td>
						<td width="30%" align="left" valign="top" style="font-size:12px;">(c) Date of crossed off/ Closed down / shifting: <b>'.$date_cossed.'</b></td>
						<td width="65%" align="left" valign="top" style="font-size:12px;" colspan="2">(d) Date of Amenability: <b>'.$date_shift_amenability.'</b></td>
					</tr>
					<tr>
						<td width="5%" align="left" valign="top" style="font-size:12px;">4. </td>
						<td width="95%" style="font-size:12px;" colspan="3">Comments on information furnished relating to owner and occupier of promises / Factory: </td>
					</tr>
					<tr>
						<td width="5%" valign="top" style="font-size:12px;"> </td>
						<td width="30%" style="font-size:12px;">Name: </td>
						<td width="65%" style="font-size:12px;" colspan="2"> <b>'.$get_fa_cafa['owner_name'].' '.$get_fa_cafa['owner_mname'].' '.$get_fa_cafa['owner_lname'].'</b></td>
					<tr>
						<td width="5%" valign="top" style="font-size:12px;"> </td>
						<td width="30%" valign="top" style="font-size:12px;">Address: </td>
						<td width="65%" style="font-size:12px;" colspan="2"><b>'.$owner_address.'</b></td>
					</tr>';
					if(!empty($data->owner_comment)){
		$content .= '<tr>
						<td width="5%" valign="top" style="font-size:12px;"> </td>
						<td width="30%" valign="top" style="font-size:12px;">Comment: </td>
						<td width="65%" style="font-size:12px;" colspan="2"><b>'.$data->owner_comment.'</b></td>
					</tr>';
					}
					
		$content .= '<tr>
						<td width="5%"  align="left" valign="top" style="font-size:12px;">5. </td>
						<td width="98%"  align="left" style="font-size:12px;" colspan="3">Name / Names of major products in order of volume of production: </td>
					</tr>';
			$get_manufacturing = get_manufacturing($application_id,$service_id,$factorytype_id,$reference_id);
			$sl = 'a';
			foreach($get_manufacturing as $lst){
			$content .=	'<tr>
										<td width="5%" valign="top" style="font-size:12px;"> </td>
										<td width="95%" align="left" style="font-size:12px;" colspan="3"><u>('.$sl.') '.$lst->nature_manufacturing.'</u></td>
										
									</tr>';
									$sl++;
			}
			$content .=	'<tr>
							<td width="5%"  align="left" valign="top" style="font-size:12px;">6.</td>
							<td width="95%"  align="left" style="font-size:12px;" colspan="3">Nature and amount of installed power(KW/HP): <u><b>'.$data->power_install.'</b></u></td>
						</tr>
						<tr>
							<td width="5%"  align="left" valign="top" style="font-size:12px;">7.</td>
							<td width="95%" align="left" style="font-size:12px;" colspan="3">(a) Maximum No. of workers employed on any day during the years preceeding the year of registration:  <u><b>'.$data->worker.'</b></u></td>
						</tr>
						<tr>
							<td width="5%"  align="left" valign="top" style="font-size:12px;"></td>
							<td width="95%" align="left" style="font-size:12px;" colspan="3">(b) Number of workers on date of amenability: <u><b>'.$data->worker_at_amen.'</b></u></td>
						</tr>
						<tr>
							<td width="5%"  align="left" valign="top" style="font-size:12px;">8.</td>
							<td width="95%" align="left" style="font-size:12px;" colspan="3">Approval No. <u><b>'.$data->approval_no.'</b></u> Date <u><b>'.$data->approval_no_date.'</b></u> of site and plans if approved, otherwise comments on confirmity of the site & building to be Act. </td>
						</tr>';
			if(!empty($data->plans_comment)){			
			$content .=	'<tr>
							<td width="5%"  align="left" valign="top" style="font-size:12px;"></td>
							<td width="95%" align="left" style="font-size:12px;" colspan="3"><u>'.$data->plans_comment.'</u></td>
						</tr>';
			}
			$content .=	'<tr>
							<td width="5%" align="left" valign="top" style="font-size:12px;">9.</td>
							<td  width="95%" align="left" style="font-size:12px;" colspan="3">any other additional comment that the inspector may like to add relation to health hazards and safty, effluent disposal, approval of appropriate authority in respect of storage of inflammable liquids, gases etc. approval form environmental pollution department.</td>
						</tr>
						<tr>
							<td width="5%"  align="left" valign="top" style="font-size:12px;"></td>
							<td width="95%" align="left" style="font-size:12px;" colspan="3">Category &nbsp;&nbsp;<u><b>'.$data->category.'</b> </u>&nbsp;&nbsp; Reference Number &nbsp;&nbsp; <u><b>'.$data->category_ref.'</b></u>&nbsp;&nbsp; Approval date &nbsp;&nbsp; <u><b>'.date('dS M Y', strtotime($data->category_date)).'</b></u>
							</td>
						</tr>';
			if(!empty($data->category_comment)){			
			$content .=	'<tr>
							<td width="5%"  align="left" valign="top" style="font-size:12px;"></td>
							<td width="95%" align="left" style="font-size:12px;" colspan="3">Comment: '.$data->category_comment.'</td>
						</tr>';
			}
			$content .=	'<tr>
							<td width="5%"  align="left" valign="top" style="font-size:12px;">10.</td>
							<td width="95%" align="left" style="font-size:12px;" colspan="3">Recommended for registration under classification <u><b>'.$data->classification.'</b></u>  category <u><b>'.$data->classification_category.'</b></u>  '.$data->category_old_new.', w.e.f. <u><b>'.$data->amenability.'</b></u> as also grant and issue of licence after renewing if for upto H.P. <u><b>'.$data->hp.'</b></u> and worker upto <u><b>'.$data->worker_year.'</b></u> valid upto date <u><b>'.$data->last_year.'</b></u>.</td>
						</tr>
						<tr>
							<td align="left" style="font-size:12px;" colspan="5">E-NOTE:- &nbsp;&nbsp;'.$data->note.'</td>
						</tr>
						';
						}
					
			$content .=	'<tr><td align="right" style="font-size:12px;" colspan="5">'.get_name($notesheet->remark_by_uid).'<br><u>Asst. Director / Inspector of factory</u></td></tr>
						<tr><td align="right" style="font-size:12px;" colspan="5">Date: '.$notesheet->sending_time.'<br><br><br></td></tr>';
				}	
		if($notesheet->remark_by_roleid == 10 && $notesheet->remark_to_roleid == 11 && $notesheet->status=="JC"){
			$content .=	'<tr><td align="left" style="font-size:12px;"  colspan="5">'.get_name($notesheet->remark_to_user).'<br><u>Jt. Director / Jt. CIF</u></td></tr>
						<tr><td align="left" style="font-size:12px;" colspan="3">E-NOTE: '.$notesheet->remarks.'</td></tr>
			
						<tr><td align="right" style="font-size:12px;" colspan="5">'.get_name($notesheet->remark_by_uid).'<br><u>DY. Director / DY. CIF</u></td></tr>
						<tr><td align="right" style="font-size:12px;" colspan="5">Date: '.$notesheet->sending_time.'<br><br><br></td></tr>';
									
						}
		if($notesheet->remark_by_roleid == 11 && $notesheet->remark_to_roleid == 4 && $notesheet->status=="I"){
			//die('dfdf');
			$content .=	'<tr><td align="left" style="font-size:12px;"  colspan="5">'.get_name($notesheet->remark_to_user).'<br><u>Director / CIF</u></td></tr>
						<tr><td align="left" style="font-size:12px;" colspan="3">E-NOTE: '.$notesheet->remarks.'</td></tr>
			
						<tr><td align="right" style="font-size:12px;" colspan="5">'.get_name($notesheet->remark_by_uid).'<br><u>Jt. Director / Jt. CIF</u></td></tr>
						<tr><td align="right" style="font-size:12px;" colspan="5">Date: '.$notesheet->sending_time.'<br><br><br></td></tr>';
									
						}
		
		}
		
		$content .=	'<tr><td colspan="6"><div class="box-body">
						<div class="table">
							<table class="table" width="100%">
							<tr>
								<th>Conditions</th>
								<th>Assistant director (Remarks)</th>
								<th>Deputy Director (Remarks)</th>
								<th>Joint Director (Remarks)</th>
							</tr>';
				$checklist_data = content_checklist($application_id);
				foreach($checklist_data as $checklist){	
				
				if($checklist->observations_id){ 
				$condition_list = get_conditions_details($checklist->observations_id);
				}
				
				elseif(!empty($checklist->ad_extra_observation)){
					$condition_list = $checklist->ad_extra_observation;
					}
				elseif(!empty($checklist->dd_extra_observation)){
					$condition_list = $checklist->dd_extra_observation;
					}else{
						$condition_list = $checklist->jd_extra_observation;
						}
						
				$data = explode(',',$checklist->jd_details);		
				if($data[2]==1){
				$ad_data = explode(',',$checklist->ad_details);
				$username_ad ='Name:-'.$ad_data[1];
				$dd_data = explode(',',$checklist->dd_details);
				$username_dd ='Name:-'.$dd_data[1];
				$jd_data = explode(',',$checklist->jd_details);
				$username_jd ='Name:-'.$jd_data[1];
				$content .= '<tr>
								<td style="border-bottom:1px;">'.$condition_list.'</td>
								<td>'.$checklist->remark_by_ad.'<br/>'.$username_ad.'</td>
								<td>'.$checklist->remark_by_dd.'<br/>'.$username_dd.'</td>
								<td>'.$checklist->remark_by_jd.'<br/>'.$username_jd.'</td>
							</tr>';
				}
			}
			
			$content .= '</table></div></div></td></tr>';
										
	$content .= '</table>';
	//echo $content;die;
	return pdf_using_mpdf_api($content,'caf-notesheet-'._.time());
	
	}
	
function fee_details_show($application_id,$service_id,$factory_typeid,$reference_number,$service_fees){
	$get_fa_cafa 	= get_fa_cafa($application_id);
	$payment_date 	= date("dS M Y",strtotime($get_fa_cafa['payment_date']));
	$output = '<div class="box-header with-border">
               </div>
			<div class="box-body"><div class="table-responsive">
			<table class="table table-bordered" width="100%">
			<thead>
			
			<tr>
				<th>SL</th>
  				<th>Application Period</th>
   				<th>Category(KW/HP)</th>
   				<th>Total Workers</th>
    			<th>Schedule Fees(Rs)</th>
				<th>Late Fees(Rs)</th>
  				<th>Previous Excess Paid(Rs.)</th>
				<th>Balance(Rs)</th>
				<th>Due Amount(Rs)</th>
 			</tr>';

	$toatl_fees_breakup = toatl_fees_breakup($application_id,$service_id,$factory_typeid,$reference_number);
	$sl						= 0;
	$total_schedule_fees 	= 0;
	$total_due_fees 		= 0;
	$total_late_fees 		= 0;
	$total_fees_to_paid 	= 0;
	foreach($toatl_fees_breakup as $total){
		$sl = $sl+1;
		$output.='<tr>
						<td>'.$sl.'</td>
		             	<td>'.$total->service_year.'</td>
						<td>'.$total->power.'</td>
						<td>'.$total->worker.'</td>
						<td>'.$total->schedule_fees.'</td>
						<td>'.$total->late_fees.'</td>
						<td>'.$total->previous_paid_fees.'</td>
						<td>'.$total->balance_amount.'</td>
						<td>'.$total->due_fees.'</td>';
						
										
			$total_schedule_fees = $total_schedule_fees+$total->schedule_fees	;
			$total_due_fees = $total_due_fees+$total->due_fees	;
			$total_late_fees = $total_late_fees+$total->late_fees	;
			
		$output.='</tr>';
	
	}
/*$total_fees_to_paid = $total_fees_to_paid+$total_due_fees+$service_fees;
$output .=' 	<tr><td colspan="4">Total Schedule Fees</td><td colspan="5">'.$total_schedule_fees.'</td></tr>
				<tr><td colspan="5">Total Late Fees</td><td colspan="4">'.$total_late_fees.'</td></tr>
				<tr><td colspan="8">Total Due Amount</td><td>'.$total_due_fees.'</td></tr>
				*/
				
	$output.='</table>
				<strong><font color="#FF0000">Paid Fees(Due fees + Registration Fees):-'.$total_fees_to_paid.' </font></strong>
				</div></div>';
		return $output;
		
		}

function content_checklist($application_id){
	
		$fetch_comment	= db_select('fa_checklist_observations_ref','observation');
		$fetch_comment->fields('observation', array());
		$fetch_comment->condition('observation.application_id ',$application_id,'=');
		$fetch_comment-> orderBy('observation.id', 'ASC');
		$result_comment = $fetch_comment->execute()->fetchAll();
		return $result_comment;
	}
function get_conditions_details($id){
	$conditions_details	=  db_query("SELECT observations  FROM {fa_observations_mst} WHERE id = '".$id."'")->fetchObject()->observations;
	return $conditions_details;
	}