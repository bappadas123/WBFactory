<?php
global $base_root, $base_path, $user;
require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';

function pdf_worker_as_draft_extn($applicationid='' ,$referenceid ='' ,$serviceid ='' ,$factorytype =''){

	$application_id 	 		= encryption_decryption_fun('decrypt', $applicationid);
	$reference_id 		 		= encryption_decryption_fun('decrypt', $referenceid);
	$service_id 		 		= encryption_decryption_fun('decrypt', $serviceid);
	$factory_type_id 	 		= encryption_decryption_fun('decrypt', $factorytype);

	$worker_details = worker_details_reference($application_id,$service_id,$factory_type_id,$reference_id);
		$permanent_worker_men 			= $worker_details['permanent_worker_men'];
		$permanent_worker_women 		= $worker_details['permanent_worker_women'];
		$permanent_adolescents_male     = $worker_details['permanent_adolescents_male'];
		$permanent_adolescents_female 	= $worker_details['permanent_adolescents_female'];
		$permanent_children_male 	    = $worker_details['permanent_children_male'];
		$permanent_children_female 		= $worker_details['permanent_children_female'];

		$contactual_worker_men 			= $worker_details['contactual_worker_men'];
		$contactual_worker_women 		= $worker_details['contactual_worker_women'];
		$contactual_adolescents_male    = $worker_details['contactual_adolescents_male'];
		$contactual_adolescents_female 	= $worker_details['contactual_adolescents_female'];
		$contactual_children_male 	    = $worker_details['contactual_children_male'];
		$contactual_children_female 	= $worker_details['contactual_children_female'];

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
					.data{ text-transform: uppercase;font-weight:bold;}
					
			</style>';
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">				
					<tr><td colspan="3"></td></tr>				
					<tr><td colspan="3" align="center" style="font-size:20px;text-transform:uppercase;"><h2> COMMON APPLICATION FORM - WORKER INFORMATION</h2></td></tr>
					<tr><td colspan="3"></td></tr>
					<tr><td colspan="3"></td></tr></table>';

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>J i). No.s Of Workers (Permanent)</td></h4></tr>
				 <tr><td>&nbsp;</td></tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(i) Men  </td>
					<td width="49%"><span class="data">: '.$permanent_worker_men.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(ii) Women </td>
					<td width="49%"><span class="data">: '.$permanent_worker_women.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(iii) Adolescents Male </td>
					<td width="49%"><span class="data">: '.$permanent_adolescents_male.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(iv) Adolescent Male </td>
					<td width="49%"><span class="data">: '.$permanent_adolescents_female.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(v) Children Male </td>
					<td width="49%"><span class="data">: '.$permanent_children_male.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(vi) Children Female </td>
					<td width="49%"><span class="data">: '.$permanent_children_female.'</span></td>
				 </tr>
				 </table>';

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr>
				 <tr><td colspan="3" align="left" style="font-size:14px;"><h4>J ii). No.s Of Workers (Contractual)</td></h4></tr>
				 <tr><td>&nbsp;</td></tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(i) Men  </td>
					<td width="49%"><span class="data">: '.$contactual_worker_men.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(ii) Women </td>
					<td width="49%"><span class="data">: '.$contactual_worker_women.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(iii) Adolescents Male </td>
					<td width="49%"><span class="data">: '.$contactual_adolescents_male.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(iv) Adolescent Male </td>
					<td width="49%"><span class="data">: '.$contactual_adolescents_female.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(v) Children Male </td>
					<td width="49%"><span class="data">: '.$contactual_children_male.'</span></td>
				 </tr>
				 <tr>					 				
					<td width="2%" valign="top">&nbsp;</td>
					<td width="49%" valign="top">(vi) Children Female </td>
					<td width="49%"><span class="data">: '.$contactual_children_female.'</span></td>
				 </tr>
				 </table>';

	//echo $content; die;	
	$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 20, 10, 0, 0);
	$mpdf->SetDisplayMode('fullpage');
	$mpdf->SetHTMLHeader('
	<div style="padding-top:50px; text-align: right; font-size:9px;">
		Page {PAGENO} of {nb}
	</div>');
	$mpdf->SetWatermarkText('DRAFT COPY');
	$mpdf->showWatermarkText = true;
	$mpdf->WriteHTML($content);
	$mpdf->Output('Worker-Information-Extension-'.time().'.pdf', 'D');
}
?>