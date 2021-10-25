<?php

function pdf_form_19($formid='' ,$referenceid ='', $factorytypeid ='', $serviceid =''){ 
	global $base_root, $base_path, $user;

	require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';
	
	$form_id 	 		= encryption_decryption_fun('decrypt', $formid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$factory_typeid 	= encryption_decryption_fun('decrypt', $factorytypeid);
	$service_id 	    = encryption_decryption_fun('decrypt', $serviceid); //echo $form_id.'--'.$reference_id.'--'.$factory_typeid.'--'.$service_id;

	$get_all_data 		= get_dangerous_occurence_details($form_id,$reference_id,$factory_typeid,$service_id);
	$get_occurence_data = get_occurence_data($form_id);

	$content = '<style type="text/css">
					table, td, th {
							font-size:15px;
							font-family:Times New Roman, serif;
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
					<tr><td colspan="3" align="center" style="font-size:15px;text-transform:uppercase;"><h2> FORM NO. 19 </h2></td></tr>
					<tr><td colspan="3" align="center" style="font-size:11px;"> (See rule 99 and 106) </td></tr>
					<tr><td colspan="3" align="center" style="font-weight:bold;">Notice of dangerous occurrence which does not</td></tr>
					<tr><td colspan="3" align="center" style="font-weight:bold;">result in deatch or bodily injury</td></tr>
					<tr><td colspan="3"></td></tr></table>';

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr>
				 	<td width="50%" valign="top">To</td>
					<td width="50%" valign="top" align="right">Dated : '.date('d-m-Y').'</td>
				 </tr>
				 <tr><td colspan="3" width="100%" valign="top">Sir,</td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3" width="100%" valign="top">I hereby give notice under section 88 of the Factories Act, 1948, that a dangerous occurrence occured in the factory as detailed below :-</td></tr>
				 </table>';

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>
				 	<td width="7%" valign="top">1.</td>
					<td width="38%" valign="top">Date and hour of dangerous occurrence :</td>
					<td width="45%" valign="top">'.$get_all_data[0]->date_occurrence.' and '.$get_all_data[0]->time_occurrence.'</td>
				 </tr>
				 <tr>
				 	<td width="7%" valign="top">2.</td>
					<td width="38%" valign="top">Full account of dangerous occurrence :</td>
					<td width="45%" valign="top">'.$get_all_data[0]->full_account.'</td>
				 </tr>
				 <tr>
					 <td width="7%" valign="top">3.</td>
					 <td colspan="2">Names of person who saw the dangerous occurrence and can give important evidence :</td>
			     </tr>';
				 
			$i = 0;
			while($i < count($get_occurence_data))
			{ 
				$j = $i+1;
				$content .= '<tr>
								<td width="7%" valign="top">&nbsp;</td>
								<td width="38%" valign="top"> ('.integerToRoman($j).')</td>
								<td width="45%" valign="top">'.$get_occurence_data[$i]->persons_name.'</td>
							 </tr>';
				$i++;			 
			}
		
	$content .= '<tr>
					<td width="7%" valign="top">&nbsp;</td>
					<td width="38%" valign="top">Name of factory :</td>
					<td width="45%" valign="top">'.$get_all_data[0]->factory_name.'</td>
				 </tr>
				 <tr>
					<td width="7%" valign="top">&nbsp;</td>
					<td width="38%" valign="top">Nature of industry :</td>
					<td width="45%" valign="top">'.$get_all_data[0]->industry_nature.'</td>
				 </tr>
				 <tr>
					<td width="7%" valign="top">&nbsp;</td>
					<td width="38%" valign="top">Branch or department where the dangerous occurrence occurred:</td>
					<td width="45%" valign="top">'.$get_all_data[0]->branch_name.'</td>
				 </tr>
			</table>';

	$getdata_factory_address =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address         = get_full_address('fa_cafa','sub-table',$get_all_data[0]->factory_id,$getdata_factory_address);

		$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>
				 	<td width="50%" valign="top">Address</td>
					<td width="50%" valign="top" align="right">Signed</td>
				 </tr>
				 <tr>
				 	<td width="50%" valign="top">'.$factory_address.'<br> '.$get_all_data[0]->addrline.'</td>
					<td width="50%" valign="top" align="right">----------------</td>
				 </tr>
				 </table>';


$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr>
				 	<td width="7%" valign="top">Note : </td>
				 	<td width="93%"> Any additional information which the Manager may wish to give in order to let the inspector have a clear idea of the circumstances surrounding the dangerous occurrence, should be attched to this form.</td>
				 </tr>
				 </table>';
	
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
	$mpdf->Output('FORM-19'._.time().'.pdf', 'D');
	
	//drupal_goto('applicant/form19');
}


    function integerToRoman($integer)
    {
     // Convert the integer into an integer (just to make sure)
     $integer = intval($integer);
     $result = '';
     
     // Create a lookup array that contains all of the Roman numerals.
     $lookup = array('m' => 1000,
     'cm' => 900,
     'd' => 500,
     'cd' => 400,
     'c' => 100,
     'xc' => 90,
     'l' => 50,
     'xl' => 40,
     'x' => 10,
     'ix' => 9,
     'v' => 5,
     'iv' => 4,
     'i' => 1);
     
     foreach($lookup as $roman => $value){
      // Determine the number of matches
      $matches = intval($integer/$value);
      // Add the same number of characters to the string
      $result .= str_repeat($roman,$matches);
      // Set the integer to be the remainder of the integer and the value
      $integer = $integer % $value;
     }
     // The Roman numeral should be built, return it
     return $result;
    }?>
