<?php
function download_notesheet($serviceid, $factory_typeid,$applicationid,$referenceid){
	global $base_root, $base_path, $user; 
	
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
	$reference_id 		= encryption_decryption_fun('decrypt', $referenceid);
	$service_id 		= encryption_decryption_fun('decrypt', $serviceid);
	$factorytype_id 	= encryption_decryption_fun('decrypt', $factorytypeid);
	$get_all_data 		= get_application_withid($application_id);
	
	$name_of_factory 			  = 	($get_all_data[0]->factory_name)? $get_all_data[0]->factory_name : 'Nil'; //die;
	$factory_plan_approval_number = 	($get_all_data[0]->factory_plan_approval_number)? $get_all_data[0]->factory_plan_approval_number : 'Nil'; //die;
	$modification_date            = 	 date_create($get_all_data[0]->modification_date); //die;
	$date_approval1 = date_format($modification_date,'d/m/Y');
	$date_approval2 = date_format($modification_date,'F j, Y'); //die;

	$created_date                 =   date_create($get_all_data[0]->created_date); //die;
	$date_created       		  =   date_format($created_date,'d/m/Y');

	$plan_approve_identification_number = 	($get_all_data[0]->plan_approve_identification_number)? $get_all_data[0]->plan_approve_identification_number : 'Nil'; //di
	$plan_conditional_letter_no         = 	($get_all_data[0]->plan_conditional_letter_no)? $get_all_data[0]->plan_conditional_letter_no : 'Nil'; //di
	
	$plan_remarks                    = 	get_remarks_to_applicant($application_id,$reference_id,'ABk');
	
	/* FACTORY ADDRESS */
	$getdata_factory_address 	=  	array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address 			=	get_parts_address('fa_cafa','sub-table',$application_id,$getdata_factory_address);

	$address_line_factory    	= ($get_all_data[0]->addrline)? $get_all_data[0]->addrline : ''; 
	$post_office_factory     	= ($factory_address['po_name'])? $factory_address['po_name'] : ''; 
	$pin_code_factory        	= ($factory_address['pincode'])? $factory_address['pincode'] : ''; 
	$district_factory        	= ($factory_address['district_name'])? $factory_address['district_name'] : ''; 
	$police_station_factory  	= ($factory_address['name_of_police_station'])? $factory_address['name_of_police_station'] : ''; 
	
	$plan_notesheet 			=  get_plan_notesheet($application_id,$reference_id);
	//echo "<pre>"; print_r($plan_notesheet); die;
	
	//include("../mpdf.php");
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
					<tr><td colspan="3" align="center"><img src="https://wbfactories.gov.in/assets/images/ashoke_stambho.png"></td></tr>
					<tr><td colspan="3" align="center" style="font-size:15px;border-style:hidden hidden double hidden;"><h2>NOTE SHEET</h2></td></tr>
					<tr><td colspan="3" align="center" style="text-transform:uppercase;">DIRECTORATE OF FACTORIES</td></tr>
					<tr><td colspan="3"></td></tr>			
					<tr><td colspan="3" align="center" style="text-transform:uppercase;">GOVERNMENT OF WEST BENGAL</td></tr>			
					<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden;">NEW SECRETARIAT BUILDINGS (8th floor)</td></tr>
					<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden;">1, KIRON SANKAR ROY ROAD, KOLKATA -700001</td></tr>
					<tr><td colspan="3"></td></tr></table>';

	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3">&nbsp;</td></tr>
				 <tr><td colspan="3"><b>Sub :- Approval Of Plan</b></td></tr>
				 <tr><td colspan="3"><b>Ref :- <b>'.$name_of_factory.'</b></td></tr>
				 <tr><td colspan="3" align="left"><b style="text-transform:uppercase;">P.S : </b>'.$police_station_factory.'<b> Pin : </b>'.$district_factory.'</td></tr>
				 <tr><td colspan="3" align="left"><b style="text-transform:uppercase;">P.0 : </b>'.$post_office_factory.'<b> Pin : </b>'.$pin_code_factory.'</td></tr>
				 </table>';
				 
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">';
	
				 $i = 0;
				 while($i < count($plan_notesheet)) 
				 { 
					$from_date = date_format(date_create($plan_notesheet[$i]->sending_time),'jS M Y'); 
					
					if($plan_notesheet[$i]->u_name == 'inspector' ) {$designation = 'Inspector';}
					elseif($plan_notesheet[$i]->u_name == 'inspectorchemical' ) {$designation = 'Inspector';}
					elseif($plan_notesheet[$i]->u_name == 'deputychief' ) {$designation = 'Dy. CIF';}
					elseif($plan_notesheet[$i]->u_name == 'deputychiefchemical' ) {$designation = 'Dy. CIF Chemical';}
					elseif($plan_notesheet[$i]->u_name == 'jointchief' ) {$designation = 'Jt. CIF';}
					elseif($plan_notesheet[$i]->u_name == 'chief' ) {$designation = 'CIF';}

	$content .=  '<tr><td colspan="3">&nbsp;</td></tr>
				  <tr><td style="font-size:12px;"><b>Sent By : </b>'.$plan_notesheet[$i]->fname.' ['.$designation.'] on '.$from_date.'</td></tr>';	
				  
				  $j = $i+1;
				  
				  if($j!=count($plan_notesheet))
				  {
				  
					if($plan_notesheet[$j]->u_name == 'inspector' ) {$designation = 'Inspector';}
					elseif($plan_notesheet[$j]->u_name == 'inspectorchemical' ) {$designation = 'Inspector';}
					elseif($plan_notesheet[$j]->u_name == 'deputychief' ) {$designation = 'Dy. CIF';}
					elseif($plan_notesheet[$j]->u_name == 'deputychiefchemical' ) {$designation = 'Dy. CIF Chemical';}
					elseif($plan_notesheet[$j]->u_name == 'jointchief' ) {$designation = 'Jt. CIF';}
					elseif($plan_notesheet[$j]->u_name == 'chief' ) {$designation = 'CIF';}
					
	$content .=  	'<tr><td style="font-size:12px;"><b>Send To : </b>'.$plan_notesheet[$j]->fname.' ['.$designation.']</td></tr>';	
				  }
				  
				  
		$content .= '<tr><td style="font-size:12px;" colspan="3"></td></tr>
				  <tr><td width="100%" valign="top"><b>E-note : </b>'.$plan_notesheet[$i]->remarks.'.</td></tr>
				  <tr><td colspan="3">------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------</td></tr>';
				  

				 $i++;
				 }
	$content .= '</table>';	

				
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td colspan="3"></td></tr><tr><td colspan="3"></td></tr><tr><td colspan="3"></td></tr>
				 <tr><td width="100%" align="right">Yours faithfully</td></tr>
				 <tr><td width="100%" align="right">&nbsp;</td></tr>
				 <tr><td width="100%" align="right">&nbsp;</td></tr>
				 <tr><td width="100%" align="right">(Assistant Director/Inspector of factories)</td></tr>
				 <tr><td width="100%" align="right">West Bengal</td></tr>

				<tr><td colspan="3"></td></tr></table>';

    //echo $content; die;
	return pdf_using_mpdf_api($content,'caf-'._.time());
	//$content->Output('caf-'._.time().'.pdf', 'D');
	
		//return pdf_using_mpdf_api($output);
/*$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 20, 10, 0, 0);
//$mpdf = new mPDF('utf-8', 'A4', '', '', 0, 0, 0, 0, 0, 0);
$mpdf->SetDisplayMode('fullpage');
//$mpdf->list_indent_first_level = 1;
//$mpdf->setHeader($arr);
$mpdf->SetHTMLHeader('
<div style="padding-top:50px; text-align: right; font-size:9px;">
	Page {PAGENO} of {nb}
</div>');
//$mpdf->setFooter("Page {PAGENO} of {nb}";
//$mpdf->defaultfooterline=0;
//$mpdf->SetWatermarkText('Common Application Form',0.1);
$mpdf->showWatermarkText = true;
//$mpdf->SetWatermarkImage($base_root.$base_path.'sites/all/modules/custom/common_pdf_generator/logo.png');
//$mpdf->showWatermarkImage = true;

$mpdf->WriteHTML($content);
//$mpdf->AddPage('A4-L','','','','',20,20,20,20,0,0);
//$mpdf->WriteHTML($document);
$mpdf->Output('caf-'._.time().'.pdf', 'D');
*/
	
	
}
?>