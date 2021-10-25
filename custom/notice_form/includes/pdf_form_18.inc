<?php

function pdf_form_18($formid='' ,$referenceid ='', $factorytypeid ='', $serviceid =''){
	global $base_root, $base_path, $user;

	require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';
	
	$form_id 	 		= encryption_decryption_fun('decrypt', $formid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$factory_typeid 	= encryption_decryption_fun('decrypt', $factorytypeid);
	$service_id 	    = encryption_decryption_fun('decrypt', $serviceid); //echo $form_id.'--'.$reference_id.'--'.$factory_typeid.'--'.$service_id;

	$get_all_data 	    = get_notice_accident_data($form_id,$reference_id,$factory_typeid,$service_id);
	$get_witness_data   = get_accident_witness_data($form_id);
	$get_injured_data   = get_accident_injured_person_data($form_id);// echo "<pre>".print_r($get_injured_data);

	$content = '<style type="text/css">
					table, td, th {
							font-size:15px;
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
						font-size:15px;
					}
					.data{ text-transform: uppercase;font-weight:bold;}
					
			</style>';
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tr><td colspan="3" align="center" style="font-size:15px;text-transform:uppercase;"><h2> FORM NO. 18 </h2></td></tr>
					<tr><td colspan="3" align="center" style="font-size:11px;"> (See rule 95 and 96) </td></tr>
					<tr><td colspan="3" align="center" style="font-weight:bold;">Notice of Accident</td></tr>
					<tr><td colspan="3"></td></tr></table>';

	$getdata_factory_address =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address         = get_notice_full_address('fa_form18_notice_accident','sub-table',$get_all_data[0]->factory_id,$getdata_factory_address);

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>
				 	<td width="7%" valign="top">1.</td>
					<td width="43%" valign="top">Name of occupier (or Factory) Employer :</td>
					<td width="40%" valign="top">'.ucfirst($get_all_data[0]->name_occupier).' ('.$get_all_data[0]->factory_name.')</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">&nbsp;</td>
					<td width="43%" valign="top">E.S.I Employer Code No. :</td>
					<td width="40%" valign="top">'.$get_all_data[0]->esi_code.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">2.</td>
					<td width="43%" valign="top">Address of factory/premises where accident took place :</td>
					<td width="40%" valign="top">'.$factory_address.','.$get_all_data[0]->addrline.'<br>Landmark : '.$get_all_data[0]->nearest_landmark.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">3.</td>
					<td width="43%" valign="top">Nature of industry :</td>
					<td width="40%" valign="top">'.$get_all_data[0]->industry_nature.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">4.</td>
					<td width="43%" valign="top">Branch or department and exact place where the accident took place :</td>
					<td width="40%" valign="top">'.$get_all_data[0]->branch_name.'<br>'.$get_all_data[0]->accident_place.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">5. </td>
					<td width="43%" valign="top">Name and address of the injured :</td>
					<td width="40%" valign="top">'.$get_injured_data[0]->accident_person_name.'<br>'.$get_injured_data[0]->accident_person_address.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">&nbsp;</td>
					<td width="43%" valign="top">E.S.I Insurance No :</td>
					<td width="40%" valign="top">'.$get_injured_data[0]->insurance_number.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">6.</td>
					<td width="43%" valign="top">(a) Sex :</td>
					<td width="40%" valign="top">'.$get_injured_data[0]->gender.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">&nbsp;</td>
					<td width="43%" valign="top">(b) Age (last birthday) :</td>
					<td width="40%" valign="top">'.$get_injured_data[0]->age.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">&nbsp;</td>
					<td width="43%" valign="top">(c) Occupation of the injured person :</td>
					<td width="40%" valign="top">'.$get_injured_data[0]->accident_person_occupation.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">7.</td>
					<td width="43%" valign="top">Local E.S.I. Office to which the injured person is attached :</td>
					<td width="40%" valign="top">'.$get_injured_data[0]->local_esi_office.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">8.	</td>
					<td width="43%" valign="top">Date shift and hour of accident :</td>
					<td width="40%" valign="top">'.$get_all_data[0]->accident_date.' in '.$get_all_data[0]->accident_shift.' at '.$get_all_data[0]->accident_time.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">9.</td>
					<td width="43%" valign="top">(a) Hour at which the injured person started work on the day of accident :</td>
					<td width="40%" valign="top">'.$get_injured_data[0]->local_esi_office.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top"></td>
					<td width="43%" valign="top">(b) Whether wages in full Or part are payable to him for the day of the accident :</td>
					<td width="40%" valign="top">'.$get_injured_data[0]->wages_payable.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">10.</td>
					<td width="43%" valign="top">Cause of accident :</td>
					<td width="40%" valign="top"></td>
				 </tr>';
				 
		if($get_all_data[0]->is_machinery_accident == 'Yes')
		{
			$is_machinery_accident = 'Yes';
			
			$content .= '<tr>
							<td width="7%" valign="top">&nbsp;</td>
							<td width="43%" valign="top">(a) If caused by machinery :</td>
							<td width="40%" valign="top"></td>
						 </tr>
						 <tr>
							<td width="7%" valign="top">&nbsp;</td>
							<td width="43%" valign="top" style="padding-left: 15px;">(i) Give name of the machine and the part causing the accident</td>
							<td width="40%" valign="top">'.$get_all_data[0]->machine_name.'</td>
						 </tr>
						 <tr>
							<td width="7%" valign="top">&nbsp;</td>
							<td width="43%" valign="top" style="padding-left: 15px;">(ii) State whether it was moved by mechanical power at that time</td>
							<td width="40%" valign="top">'.$get_all_data[0]->is_machinery_accident.'</td>
						 </tr>';
		} else {
			
			$content .= '<tr>
							<td width="7%" valign="top">&nbsp;</td>
							<td width="43%" valign="top">(a) If caused by machinery :</td>
							<td width="40%" valign="top">'.$get_all_data[0]->is_machinery_accident.'</td>
						 </tr>';
		}
		
	$content .= '<tr>
				 	<td width="7%" valign="top">&nbsp;</td>
					<td width="43%" valign="top">(b) State exactly what the injured person was doing at that time :</td>
					<td width="40%" valign="top">'.$get_injured_data[0]->accident_person_activity.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">&nbsp;</td>
					<td width="43%" valign="top">(c) In your opinion, was the injured person at the time of accident :</td>
					<td width="40%" valign="top"></td>
				 </tr>';
	
	$your_opnion_1 = ($get_injured_data[0]->your_opnion == 0) ? 'Yes' : 'No';
	$your_opnion_2 = ($get_injured_data[0]->your_opnion == 1) ? 'Yes' : 'No';
	
	$content .= '<tr>
				 	<td width="7%" valign="top">&nbsp;</td>
					<td width="43%" valign="top" style="padding-left: 15px;">(i) acting in contravention of provisions of any law applicable to him</td>
					<td width="40%" valign="top">'.$your_opnion_1.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">&nbsp;</td>
					<td width="43%" valign="top" style="padding-left: 15px;">(ii) acting in contravention of any orders given by or on behalf of his employer</td>
					<td width="40%" valign="top">'.$your_opnion_2.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">&nbsp;</td>
					<td width="43%" valign="top">(d) In case reply to (c) (i), (ii) or (iii) is in (he affirmative state whether the act was done for the purpose of and in connection with the employer s trade or business :</td>
					<td width="40%" valign="top">'.$get_injured_data[0]->state_act_done.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">11.</td>
					<td width="43%" valign="top">In case the accident happened while travelling in the employers transport, state whether </td>
					<td width="40%" valign="top"></td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">&nbsp;</td>
					<td width="43%" valign="top">(i). The injured person was travelling as a passenger to or from his place work </td>
					<td width="40%" valign="top">'.$get_injured_data[0]->is_travelling_for_work.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">&nbsp;</td>
					<td width="43%" valign="top">(ii). The injured person was travelling with the express or implied permission of his employer </td>
					<td width="40%" valign="top">'.$get_injured_data[0]->is_travelling_express_impiled.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">&nbsp;</td>
					<td width="43%" valign="top">(iii). The transport is being operated by/on behalf of the employer/some other person by whom it is provided in pursuance of arrangements made with the employer </td>
					<td width="40%" valign="top">'.$get_injured_data[0]->is_transport_provided.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">&nbsp;</td>
					<td width="43%" valign="top">(iv). The vehicle was being/not being operated in the ordinary course of public transport vehicle </td>
					<td width="40%" valign="top">'.$get_injured_data[0]->is_course_of_transport_provided.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">12.</td>
					<td width="43%" valign="top">In case the accident happened while meeting mergency, state</td>
					<td width="40%" valign="top"></td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">&nbsp;</td>
					<td width="43%" valign="top">(i). Its nature</td>
					<td width="40%" valign="top">'.$get_injured_data[0]->accident.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">&nbsp;</td>
					<td width="43%" valign="top">(ii). Whether the injured person at the time of accident was employed for the purpose of his employers trade/business in/about the permises at which the accident took place</td>
					<td width="40%" valign="top">'.$get_injured_data[0]->accident_person_employed.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">13.</td>
					<td width="43%" valign="top">State how the accident occured</td>
					<td width="40%" valign="top">'.$get_all_data[0]->accident_description.'</td>
				 </tr>';
				 
			$i = 0;
			while($i < count($get_witness_data))
			{ 
				$j = $i+6;
				$content .= '<tr><td colspan="3">&nbsp;</td></tr>
							<tr>
								<td width="7%" valign="top">14. '.$j.'.i)</td>
								<td width="43%" valign="top">Name and Address of the witness :</td>
								<td width="40%" valign="top">'.$get_witness_data[$i]->witness_name.' <br>'.$get_witness_data[$i]->witness_address.'</td>
							 </tr>';
				$i++;			 
			}
		
		$content .= '<tr>
						<td width="7%" valign="top">15.</td>
						<td width="43%" valign="top">(a). Nature and extent of injury (e.g. fatal, loss of finger, fracture of leg, scale of scratch and followed by sepsis)</td>
						<td width="40%" valign="top">'.$get_injured_data[0]->nature_of_injury.'</td>
					 </tr>
					 <tr>
						<td width="7%" valign="top">&nbsp;</td>
						<td width="43%" valign="top">(b). Location of injury (right leg, left hand or left eye etc.)</td>
						<td width="40%" valign="top">'.$get_injured_data[0]->location_of_injury.'</td>
					 </tr>';
		
		if($get_injured_data[0]->fatal_accident == 'Yes')
		{			 
			$content .= '<tr> 
							<td width="7%" valign="top">16.</td>
							<td width="43%" valign="top">(a). If the accident is not fatal, state whether the injured person was disabled for 48 hours or more</td>
							<td width="40%" valign="top">'.$get_injured_data[0]->disabled_48hrs.'</td>
						 </tr>
						 <tr>
							<td width="7%" valign="top">&nbsp;</td>
							<td width="43%" valign="top">(b). Date and hour of return to work</td>
							<td width="40%" valign="top">'.$get_injured_data[0]->return_to_work_date.' at '.$get_injured_data[0]->return_to_work_time.'</td>
						 </tr>';
		} else {
			$content .= '<tr> 
							<td width="7%" valign="top">16.</td>
							<td width="43%" valign="top">(a). If the accident is not fatal, state whether the injured person was disabled for 48 hours or more</td>
							<td width="40%" valign="top">Non-fatal accident</td>
						 </tr>';
		}
		
		$content .= '<tr>
						<td width="7%" valign="top">17.</td>
						<td width="43%" valign="top">(a). Physician, dispensary or hospital from whom or in which the injured person received or is receiving treatment  </td>
						<td width="40%" valign="top">'.$get_injured_data[0]->treatment_location.'</td>
					 </tr>
					 <tr>
						<td width="7%" valign="top">&nbsp;</td>
						<td width="43%" valign="top">(b). Name of dispensary/panel doctor selected by the injured person </td>
						<td width="40%" valign="top">'.$get_injured_data[0]->doctor_name.'</td>
					 </tr>
					 <tr>
						<td width="7%" valign="top">18.</td>
						<td width="43%" valign="top">(i). Has the injured person died</td>
						<td width="40%" valign="top">'.$get_injured_data[0]->is_accident_person_died.'</td>
					 </tr>';
		
		if($get_injured_data[0]->is_accident_person_died == 'Yes')
		{
			$content .= '<tr>
							<td width="7%" valign="top">&nbsp;</td>
							<td width="43%" valign="top">(ii) Date of death</td>
							<td width="40%" valign="top">'.$get_injured_data[0]->date_of_death.'</td>
						 </tr>';
		}
		
		$content .= '<tr>
						<td width="7%" valign="top">&nbsp;</td>
						<td colspan="2" width="7%" valign="top">I certify that to the best of my knowledge and belief the above particulars are correct in every respect.</td>
					 </tr>
					 </table>';

		$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
					 <tr><td colspan="3">&nbsp;</td></tr>
					 <tr><td colspan="3">&nbsp;</td></tr>
					 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>
				 	<td width="100%" valign="top" align="right">Signature of Manager --------------------------------</td>
				 </tr>
				 <tr><td width="100%" >&nbsp;</td></tr>
				 <tr>
				 	<td width="100%" valign="top" align="right">Dated --------------------------------</td>
				 </tr>
				 </table>';
	
	//echo $content; die;	
	
	$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 18, 10, 0, 0);
	$mpdf->SetDisplayMode('fullpage');
	$mpdf->SetHTMLHeader('
	<div style="padding-top:50px; text-align: right; font-size:9px;">
		Page {PAGENO} of {nb}
	</div>');
	$mpdf->setWatermarkImage($_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/themes/wbfactories/certificate/plan_bg.jpg');
	$mpdf->showWatermarkImage = true;
	
	$mpdf->WriteHTML($content);
	$mpdf->Output('FORM-18'._.time().'.pdf', 'D');
	
	//drupal_goto('applicant/form18');
}

?>
