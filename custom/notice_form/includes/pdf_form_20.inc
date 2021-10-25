<?php

function pdf_form_20($formid='' ,$referenceid ='', $factorytypeid ='', $serviceid =''){
	global $base_root, $base_path, $user;

	require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';
	
	$form_id 	 		= encryption_decryption_fun('decrypt', $formid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$factory_typeid 	= encryption_decryption_fun('decrypt', $factorytypeid);
	$service_id 	    = encryption_decryption_fun('decrypt', $serviceid); //echo $form_id.'--'.$reference_id.'--'.$factory_typeid.'--'.$service_id;

	$get_all_data 		= get_notice_poisoning_data($form_id,$reference_id,$factory_typeid,$service_id); 
	$get_patient_data   = get_notice_poisoning_patient_data($form_id);

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
		
		$getdata_factory_address =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
		$factory_address         = get_notice_full_address('fa_form20_notice_poisoning','sub-table',$get_all_data[0]->factory_id,$getdata_factory_address);
	
		$getdata_occpier_address =  array('district_oprmntadr','subdivision_oprmntadr','areatype_oprmntadr','block_oprmntadr','panchayat_oprmntadr','policestation_oprmntadr','pincodeoprmntadr','state_oprmntadr','postoffice_oprmntadr');
		$occpier_address         = get_notice_full_address('fa_form20_notice_poisoning','sub-table',$get_all_data[0]->factory_id,$getdata_occpier_address);


		$i = 0;
		while($i < count($get_patient_data))
		{ 

			$content .= '<div style="border: 1px solid; height:3500px; padding:0px 30px 0 30px;">
						 <table width="100%" border="0" cellspacing="0" cellpadding="0">
							<tr><td colspan="3" align="center" style="font-size:15px;text-transform:uppercase;"><h2> FORM NO. 20 </h2></td></tr>
							<tr><td colspan="3" align="center" style="font-size:11px;"> (See rule 100) </td></tr>
							<tr><td colspan="3" align="center" style="font-weight:bold;">Notice of Poisoning or Disease</td></tr>
							<tr><td colspan="3"></td></tr></table>';
		
			$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
						 <tr><td colspan="3">&nbsp;</td></tr>
						 <tr><td colspan="3">&nbsp;</td></tr>
						 <tr>
							<td width="7%" valign="top">1.</td>
							<td width="38%" valign="top">Name and Address of the Factory :</td>
							<td width="45%" valign="top">'.$get_all_data[0]->factory_name.'<br>'.$factory_address.','.$get_all_data[0]->addrline.'</td>
						 </tr>
						 <tr>
							<td width="7%" valign="top">2.</td>
							<td width="38%" valign="top">Address of office or private residence of occupier :</td>
							<td width="45%" valign="top">'.$get_all_data[0]->name_occupier.'<br>'.$occpier_address.','.$get_all_data[0]->addrline.'</td>
						 </tr>
						 <tr>
							<td width="7%" valign="top">3.</td>
							<td width="38%" valign="top">Nature of Industry :</td>
							<td width="45%" valign="top">'.ucfirst($get_all_data[0]->industry_nature).'</td>
						 </tr>
						<tr>
							<td width="7%" valign="top">4. </td>
							<td width="38%" valign="top">Name and Works Number of Patient :</td>
							<td width="45%" valign="top">'.$get_patient_data[$i]->patient_name.' ('.$get_patient_data[$i]->patient_works_no.')</td>
						 </tr>
						 <tr>
							<td width="7%" valign="top">5. </td>
							<td width="38%" valign="top">Address of Patient :</td>
							<td width="45%" valign="top">'.$get_patient_data[$i]->patient_address.'</td>
						 </tr>
						 <tr>
							<td width="7%" valign="top">6. </td>
							<td width="38%" valign="top">Sex and Age :</td>
							<td width="45%" valign="top">'.$get_patient_data[$i]->patient_gender.' ('.$get_patient_data[$i]->patient_age.' years)</td>
						 </tr>
						 <tr>
							<td width="7%" valign="top">7. </td>
							<td width="38%" valign="top">Precise occupation of Patient :</td>
							<td width="45%" valign="top">'.$get_patient_data[$i]->patient_occupation.'</td>
						 </tr>
						 <tr>
							<td width="7%" valign="top">8. </td>
							<td width="38%" valign="top">Nature of Poisoning or Disease from which Patient is suffering :</td>
							<td width="45%" valign="top">'.$get_patient_data[$i]->patient_disease.'</td>
						 </tr>
						 <tr>
							<td width="7%" valign="top">9. </td>
							<td width="38%" valign="top">Has the case been reported to the Certifying Surgeon :</td>
							<td width="45%" valign="top">'.$get_patient_data[$i]->patient_reported.'</td>
						 </tr>
					</table>
					<table width="100%" border="0" cellspacing="0" cellpadding="0">
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
					</table></div>';
					 
				$i++;			 
			}
	
	//echo $content; die;	
	
	$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 20, 10, 0, 0);
	$mpdf->SetDisplayMode('fullpage');
	$mpdf->SetHTMLHeader('
	<div style="padding-top:50px; text-align: right; font-size:9px;">
		Page {PAGENO} of {nb}
	</div>');
	//$mpdf->setWatermarkImage($_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/themes/wbfactories/certificate/plan_bg.jpg');
	$mpdf->showWatermarkImage = true;
	
	$mpdf->WriteHTML($content);
	$mpdf->Output('FORM-20'._.time().'.pdf', 'D');
	
	//drupal_goto('applicant/form20');
}

?>
