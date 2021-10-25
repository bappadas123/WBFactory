<?php
global $base_root, $base_path, $user; 
require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';
//function registration_ack($applicationid='' ,$referenceid ='' ,$serviceid='' ,$factorytypeid =''){
	function registration_ack($applicationid='' ,$referenceid ='' ,$serviceid='' ,$factorytypeid =''){
	global $base_root, $base_path, $user; 
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$service_id 		= encryption_decryption_fun('decrypt', $serviceid);
	$factorytype_id 	= encryption_decryption_fun('decrypt', $factorytypeid);
	$get_all_data 		=  get_fa_cafa($application_id);
	
	$name_of_factory 	= 	$get_all_data['factory_name'];//die;
	$getdata_factory_location	 =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address_location 	 = $get_all_data['addrline'].',<br/>'.get_full_address_certificates('fa_cafa','sub-table',$get_all_data['id'],$getdata_factory_location);
	
	$application_date 	= 	date('dS M Y', strtotime($get_all_data['created_date']));
	$content = '';
	$content .= '<fieldset style="font-family: Arial, Open Sans; padding: 0;border: 20px solid #fff; font-size:13px; ">
	<div style="width:100%; background-image-resize:4;">
	
	<table width="100%" border="0" >
                  <tbody>
                     <tr>
                        <td colspan="2">
                           <table width="100%" border="0">
                              <tr>
                                 <td align="center" valign="top" ><img src="'.$_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/themes/wbfactories/certificate/factories-logo.png" width="" height="" alt="" />
                                 </td>
                              </tr>
                           </table>
                        </td>
                     </tr>
                     <tr>
                        <td colspan="2" align="center" class="address"><b>NEW SECRETARIAT BUILDINGS (8th floor)</b><br/> <span>1, KIRON SANKAR ROY ROAD, KOLKATA -700001<span></td>
                     </tr>
					 
                     <tr>
                        <td colspan="2" align="center" style="font-size:22px;color:#0b3f88;"><strong>Acknowledgement</strong></td>
                     </tr>
					  <tr>
                        <td colspan="2" align="center" style="font-size:12px;color:#0b3f88;">[see rule 4]</td>
                     </tr>
                  </tbody>
               </table>';
					
		$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
					 <tr><td colspan="3">&nbsp;</td></tr>
					 <tr><td width="100%" align="left">From,</td></tr>
					 <tr><td width="100%" align="left">Directorate of Factories</td></tr>
					 <tr><td width="100%" align="left">N.S. Buldings. (8th floor), Kol-1</td></tr>
					<tr><td colspan="3"></td></tr></table>';
				
					
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr><td colspan="3">&nbsp;</td></tr>
				<tr><td colspan="3" align="left">To,</td></tr>
				<tr><td colspan="3" align="left">The Occupier</td></tr>
				<tr><td colspan="3" align="left" style="text-transform:uppercase;">'.$name_of_factory.'</td></tr>
				<tr><td colspan="3" align="left" style="text-transform:uppercase;">'.$factory_address_location.'</td></tr>
				
				
				
				</table>';

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3"><b>Sub :- The West Bengal Right to Public Services Act,2013 - Acknowledgement of application</b></td></tr>
				 <tr><td colspan="3">Ref :- Your Application dated <b>'.$application_date.'</b></td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3" width="100%" valign="top">I hereby acknowledge your application cited Due data of service to be provided is working <strong>65</strong> days.</td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3" align="center"><b>OR</b></td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				  <tr><td colspan="3">The following defects in the application may be rectified, urgently:</td></tr>
				   <tr><td colspan="3">&nbsp;</td></tr>
				   <tr><td colspan="3" align="left">(Specify defects, if any)</td></tr>
				    <tr><td colspan="3">&nbsp;</td></tr>
					<tr>
					<td valign="top">1.</td>
				 	<td>&nbsp;</td>
					 <td width="100%" valign="top">Duly filled in Common Application Form in duplicate</td>
				 	</tr>
					<tr><td colspan="3">&nbsp;</td></tr>
					<tr>
					<td valign="top">2.</td>
				 	<td>&nbsp;</td>
					 <td width="100%" valign="top">Authenticated documents regarding deposition of fees</td>
				 	</tr>
					 <tr><td colspan="3">&nbsp;</td></tr>';
					$document_lists = get_plan_document_lists($service_id,$factorytype_id);
					$i=3;
					foreach($document_lists as $list){
						if($list->status == 1){
							$content .= ' <tr>
				 <td valign="top">'.$i.' </td>
				 <td>&nbsp;</td>
				 <td width="100%" valign="top">'.$list->document_name.'.</td>
				 </tr>
				 
				 <tr><td colspan="3">&nbsp;</td></tr>';
				$i++;
						}
						
				 
					}
				$content .='</table>';

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr><tr><td colspan="3"></td></tr><tr><td colspan="3"></td></tr>
				 <tr>					 				
					<td width="40%" align="left">Place : Kolkata</td>
					<td width="10%" align="right"></td>
					<td width="40%" align="right">Yours faithfully</td>
				 </tr>
				 <tr>					 				
					<td width="40%" align="left">Date : '.$application_date.'</b></td>
					<td width="10%" align="right"></td>
					<td width="40%" align="right">Inspector of Factories</td>
				 </tr>
				 <tr>					 				
					<td colspan="3" align="right">&nbsp;</td>
				 </tr>
				 <tr>					 				
					<td colspan="3" align="right">&nbsp;</td>
				 </tr>
				 <tr>					 				
					<td colspan="3" align="right">&nbsp;</td>
				 </tr>
				 <tr><td colspan="3" align="center"><b>** The application of Registration in under process by the Directorate of Factories . This Acknowledgement may be treated as a temporary Work Permit or grants the eligibility to participate in Tenders, etc till License Certificate is obtained</b></td></tr>
				<tr><td></td></tr></table></div></fieldset>';

    //echo $content; die;
				$mpdf = new mPDF('utf-8', 'A4', '11', '11', 10, 10, 20, 10, 0, 0);
				$mpdf->SetDisplayMode('fullpage');
				$mpdf->SetWatermarkImage($_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/themes/custom_dashboard/images/ACKNOWLEDGEMENT_bg.png');
				$mpdf->watermarkImageAlpha = 0.5;
				$mpdf->showWatermarkImage = true;
				$mpdf->WriteHTML($content);
				$mpdf->Output('ACK_Registartion_'.$max_license_no._.time().'.pdf','D');
	//return pdf_using_mpdf_api($content,'caf-'._.time());
	
	
}
?>