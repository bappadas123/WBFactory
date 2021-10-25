<?php
//require_once '/var/www/html/factories/sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';
//require_once 'C:\xampp\htdocs\factories\sites\all\modules\contrib\pdf_using_mpdf\mpdf\mpdf.php';

function plan_approval_certificate($applicationid='' ,$referenceid =''){
	global $base_root, $base_path, $user;
	require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';
	
	$application_id 	    = encryption_decryption_fun('decrypt', $applicationid);
	$reference_id 		    = encryption_decryption_fun('decrypt', $referenceid);
	
	// CREATE & UPDATE APPROVAL NO.
	$lastapprovalno = plan_count();
	$last_approval_no = $lastapprovalno +1;
	$conditional_letter_no = 'WBF/OL/'.date('Y').'/'.$last_approval_no.'/C/P';
	
	$caf_update      = 	array('factory_plan_approval_number' => $last_approval_no, 'plan_conditional_letter_no' => $conditional_letter_no);
	$queryapp 		 =	db_update('fa_cafa');
	$queryapp		 ->	fields($caf_update);
	$queryapp		 ->	condition('id',$application_id,'=');
	$queryapp	     ->	condition('reference_number',$reference_id,'=');
	$queryapp	     ->	condition('factory_plan_approval_number',NULL,'IS');
	$queryapp	     ->	condition('plan_conditional_letter_no',NULL,'IS');
	$queryapp		 ->	execute();

	$get_all_data 		= get_application_withid($application_id);
	$name_of_factory 			  = 	($get_all_data[0]->factory_name)? $get_all_data[0]->factory_name : 'Nil'; //die;
	$factory_plan_approval_number = 	($get_all_data[0]->factory_plan_approval_number)? $get_all_data[0]->factory_plan_approval_number : 'Nil'; //die;
	$modification_date            = 	 date_create($get_all_data[0]->modification_date); //die;
	$date_approval1 = date_format($modification_date,'d/m/Y');
	$date_approval2 = date_format($modification_date,'F j, Y'); //die;

	$created_date       = 	date_create($get_all_data[0]->created_date); //die;
	$date_created       =   date_format($created_date,'d/m/Y');

	$plan_approve_identification_number = 	($get_all_data[0]->plan_approve_identification_number)? $get_all_data[0]->plan_approve_identification_number : 'Nil'; //di
	$plan_conditional_letter_no         = 	($get_all_data[0]->plan_conditional_letter_no)? $get_all_data[0]->plan_conditional_letter_no : 'Nil'; //di
	$plan_conditions         = 	get_plan_additional_conditions($application_id,$reference_id);
	
	/* FACTORY ADDRESS */
	$getdata_factory_address 	=  	array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
	$factory_address 			=	get_parts_address('fa_cafa','sub-table',$application_id,$getdata_factory_address);

	$address_line_factory    	= ($get_all_data[0]->addrline)? $get_all_data[0]->addrline : ''; 
	$post_office_factory     	= ($factory_address['po_name'])? $factory_address['po_name'] : ''; 
	$pin_code_factory        	= ($factory_address['pincode'])? $factory_address['pincode'] : ''; 
	$district_factory        	= ($factory_address['district_name'])? $factory_address['district_name'] : ''; 
	$police_station_factory  	= ($factory_address['name_of_police_station'])? $factory_address['name_of_police_station'] : ''; 
    $uid 				        =  $user->uid;
	$code 					    =  get_name($uid);//.' APPROVAL DATE'.$date_approval2; die
	
	$content = '
	<style type="text/css">
				
					.address{
						font-size:13px;
						color:#2d2d2d;
						font-family:Arial, Helvetica, sans-serif;
					}
					.address span{font-size:10px;}
					#two{
						font-size:13px; 
						font-weight: normal;
						color:#1f1200;
					}
					#three{
						font-size:13px;
						color:#0b4f4d;
					}
					#four{
						font-size:13px;
						color:#0b4f4d;
						text-align: right;		
					}
					#five{
						font-size:13px;
						color:#000;
					}
					#six{
						font-size:14px;
						color:#fff;
						background: #076641;
					}
					#seven{
						font-size:12px;
						color:#925e29;
						font-weight: 700;
						}
					#eight{
						font-size:12px;
						color:#925e29;
					}
					#nine{
						font-size:13px;
						color:#f5dfce;
						font-weight: 700;
						background: #88171c;
						}
					#ten{
						font-size:12px;
						color:#925e29;
						font-weight: 700;	
						}
						
					#eleven{
							font-size:12px;
							color:#925e29;
						}
					#twelvs{
							font-size:13px;
							padding-right: 20px;
						}
						
					
			  @page{
				margin-top: 0.1mm;
				margin-bottom:0.1mm;
				margin-left: 0.1mm;
				margin-right:0.1mm;
				background-image-resize: 3;
			 }	
			</style>
	';
			
			
	$content = '
   		<fieldset style="font-family:Arial, Helvetica, sans-serif; padding: 0;padding:20px;background-image-resize:4;">
				<table width="100%" border="0">
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
                        <td colspan="2" align="center" id="two">&nbsp;</td>
                     </tr>
                     <tr>
                        <td>No.: <strong>'.$plan_conditional_letter_no.'</strong></td>
                        <td align="right">Date: <strong>'.$date_approval2.'</strong></td>
                     </tr>
					  <tr>
                        <td colspan="2" align="center" id="two">&nbsp;</td>
                     </tr>
					  <tr>
                        <td colspan="2" align="center" id="two">
						<table width="100%" border="0" cellspacing="0" cellpadding="0">

				<tr><td colspan="3" align="left">To,</td>
				    <td rowspan="6" align="right"><barcode code="Factory Name:: '.$name_of_factory.' Approval No:: '.$factory_plan_approval_number.' Conditional Letter No:: '.$conditional_letter_no.' Application No:: '.$plan_approve_identification_number.' Approval Date:: '.$date_approval1.'" size="1" type="QR" error="M" class="barcode" /></td>
				</tr>
				<tr><td colspan="3" align="left">The Occupier</td></tr>
				<tr><td colspan="3" align="left" style="text-transform:uppercase;">'.$name_of_factory.'</td></tr>
				<tr><td colspan="3" align="left" style="text-transform:uppercase;">'.$address_line_factory.'</td></tr>
				<tr><td colspan="3" align="left" style="text-transform:uppercase;"><b>P.S : </b>'.$police_station_factory.'<b> District : </b>'.$district_factory.'</td></tr>
				<tr><td colspan="3" align="left" style="text-transform:uppercase;"><b>P.0 : </b>'.$post_office_factory.'<b> Pin : </b>'.$pin_code_factory.'</td></tr>
				
				</table>
						</td>
                     </tr>
                  </tbody>
               </table>
			   <table width="100%" border="0" cellspacing="0" cellpadding="0">
				 <tr><td>&nbsp;</td></tr>
				 <tr><td><b>Sub :- Approval Of Factory Plan</b></td></tr>
				 <tr><td>Your Application No. <b>'.$plan_approve_identification_number.'</b>/ Application in the Form of CAF Dated <b>'.$date_created.'</b></td></tr>
				 <tr><td>&nbsp;</td></tr>
				 <tr><td width="100%" valign="top">Sir,</td></tr>
				 <tr><td>&nbsp;</td></tr>
				 <tr><td width="100%" valign="top">The plans are being approved subject to the following conditions : </td></tr>
				 <tr><td>&nbsp;</td></tr>
				 <tr>
				 <td width="100%" valign="top">1. Approval of the design and the site or situation of the septic tank. latrines shall be obtained from the Chief Engineer, Public Health Engineering, Government of West Bengal.</td>
				 </tr>
				 <tr><td>&nbsp;</td></tr>
				 <tr>
				 <td width="100%" valign="top">2. Approval shall be obtained from the West Bengal Pollution Control Board and the Public Health ENgineering Directorate, Government of West Bengal in respect of the arrangement for disposal of trade waste and effluents (including atmospheric emission).</td>
				 </tr>
				 <tr><td>&nbsp;</td></tr>
				 <tr>
				 <td width="100%" valign="top">3. Approval shall be obtained from Local authority (Municipal Corporation / Municipality, Notified Area, Authority / Anchal Panchayat etc.) in respect of safe design and construction of the buildings/sheds/structures etc.</td>
				 </tr>
				 <tr><td>&nbsp;</td></tr>
				 <tr>
				 <td>4. Adequate ventilation by circulation of the fresh air, adequate means of escape in case of fire, safe means of access to every place of work, adequate fire fighting arrangement, effective arrangement to prevent escape of dust/fumesmoke shall be provided.</td>
				 </tr>
				 <tr><td>&nbsp;</td></tr>
				  ';
			   
	$content .= '';
	
				 $i = 0;
				 while($i < count($plan_conditions)) 
				 { 
				 	$cnt = $i+5;
	$content .=  '<tr>
				  <td align="left">'.$cnt.'. '.$plan_conditions[$i]->conditions.'.</td>
				  </tr>
				   <tr><td>&nbsp;</td></tr>
				  ';	
				 $i++;
				 }

	$content .= '
	<tr><td colspan="3">&nbsp;</td></tr>
	<tr>
	<td colspan="3">Further to this Directorate Condition Letter No. <strong>'.$plan_conditional_letter_no.'</strong> Dated <strong>'.$date_approval1.'</strong>.The plan(s) is connection with the Application No. <strong>'.$plan_approve_identification_number.'</strong> Dated <strong>'.$date_created.'</strong> is/are approved vide Approval No. <strong>'.$factory_plan_approval_number.'</strong> Dated <strong>'.$date_approval1.'</strong></td>
	</tr>
	</table>';	
			   
	$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0" style="padding-top: 20px">
                  <tr>
                     <td align="left"></td>
                     <td align="right" id="twelvs"></td>
                  </tr>
				  <tr>
                     <td align="left"></td>
                     <td align="right" id="twelvs"><i>Yours faithfully</i><br/>
					 <img src="'.$_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/themes/wbfactories/certificate/signature.png" width="" height="" alt=""/>
					 <br/>
					 <strong>for Inspector of Factories</strong> </td>
                  </tr>
				  <tr>
                     <td align="left"></td>
                     <td align="right" id="twelvs"><br/><barcode code="" type="C39" size="1.0" height="0.7" /></td>
                  </tr>
               </table>
		</fieldset>';		
	
	//'.$code.'
    //echo $content; die;
	// return pdf_using_mpdf_api($content,'caf-'._.time());
	
	$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 20, 10, 0, 0);
	$mpdf->SetDisplayMode('fullpage');
	$mpdf->SetHTMLHeader('
	<div style="padding-top:50px; text-align: right; font-size:9px;">
		Page {PAGENO} of {nb}
	</div>');
	$mpdf->setWatermarkImage($_SERVER['DOCUMENT_ROOT'].$base_path.'/sites/all/themes/wbfactories/certificate/plan_bg.jpg');
	$mpdf->showWatermarkImage = true;
	
	$mpdf->WriteHTML($content);
	$mpdf->Output('plan_approval_certificate-'._.time().'.pdf', 'D');

}

 function plan_count(){
		
		$fetch_application = db_query("SELECT max(factory_plan_approval_number) as cnt from fa_cafa WHERE service_id = '4' AND date_part('year', modification_date) = ".date('Y'))->fetchObject()->cnt;
		return $fetch_application;
 }

?>