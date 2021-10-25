<?php

function applicant_notification($serviceid, $factory_typeid,$applicationid,$referenceid) {	

	global $base_root, $base_path, $user; 
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$service_id 		= encryption_decryption_fun('decrypt', $serviceid);
	$factorytype_id 	= encryption_decryption_fun('decrypt', $factory_typeid);
	
	$get_all_data       = 	get_fa_cafa($application_id);
	$factory_name 		=  $get_all_data['factory_name'];

	$userid 			= $user->uid;
	$remark_by_name		= get_name($userid);
	$rid				= get_role_id($userid);

	
	$identity_flag = NULL;
	$fun_fetch_irregularities_check = fun_fetch_irregularities_details($identity_flag,$application_id,$reference_id,$factorytype_id,$service_id);
$get_occupier_data = get_all_occupier_data($application_id,$service_id,$factorytype_id,$reference_id);
//print_r($get_occupier_data);die;
foreach($get_occupier_data as $details){ 
	$details_occupier = $details->name_occupier.' '.$details->occupier_name_middle.' '.$details->occupier_name_last;
}
$factory_zone_date = get_factory_zone_name($get_all_data['factory_zone']);
$getdata_factory_location	 =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
$factory_address_location 	 = $get_all_data['addrline'].',<br/>'.get_full_address('fa_cafa','sub-table',$get_all_data['id'],$getdata_factory_location);
$factory_address_location = $factory_zone_date['zone_name'].'<br/>'.$factory_address_location;
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
			
			//echo $get_all_data['created_date'];die;
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">				
					<tr><td align="center" colspan="2" style="font-size:15px;">Directorate of Factories, Govt. of West Bengal</td></tr>
					<br/><br/><br/>
					  <tr><td colspan="2" style="font-size:15px;">To,<br/>The Occupier -'.$details_occupier.'<br/>'.$factory_name.'<br/>'.$factory_address_location.'<br/>No:-'.time().' date:- '.date('d-m-Y').'</td></tr>
					<br/><br/><br/>
					  <tr><td colspan="2" style="font-size:15px;">Application No. '.$get_all_data['factory_reg_identification_number'].' dated '.date('d-m-Y',strtotime($get_all_data['created_date'])).'<br/><br/><br/>Sir,<br/>Your application for Service Namecould not be processedfor approval because of the under-mentioned irregularities observed in the same.ORAlthough the Licence number XXXXXX has been renewed automatically by the system, subsequent scrutiny of the afore-referred application and/or inspection of the afore-said premises has revealed the undermentioned irregularities. <br/><br/>

You are hereby advised to submit the revised and corrected application complete in all respects at the earliest /,the failure of which shall attract the penal provisions prescribed under The Factories Act 1948 for contravention of the provisions prescribed under Rule 9 of The West Bengal Factories Rules 1958 (running a factory without valid Licence), framed under the provisions of Section 6 of the said ACT. <br/><br/>

List of irregularities finalized by the highest Authority designated for the particular service.

					';
						$i=1;
					foreach($fun_fetch_irregularities_check as $not_recomended){
						 $jd_details1 = $not_recomended->jd_details;
						if($not_recomended->remark_by_jd == 'Agree'){
							$content .= '<tr>
							<td width="5%" align="left" valign="top" style="font-size:12px;"><br/><b>'.$i.'</b></td>
							<td width="95%" align="left" valign="top" style="font-size:12px;"><br/>'.$not_recomended->irregularities.'</td>
						
						</tr>';
						}
						$i++;
					
					}
					$jd_details = explode(',', $jd_details1);
					
					$jd_name =$jd_details[1];
				

				$content .= '	</table>';

				$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">		
					<tr><br/><br/><br/><br/>
						
						

						<td width="50%"  align="right" valign="top" style="font-size:12px;">
						'.$jd_name.'
						<br/>
						JD of Factories </td>
					</tr>
							
	            </table>';
				
				

				
			
	//echo $content;die;
	return pdf_using_mpdf_api($content,'not-recommded-notesheet-'._.time());
	
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