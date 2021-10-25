
<script type="text/javascript">
function DownloadAndRedirect(servid,factid,appid,refid)
{  
   //var RedirectURL = "/demofactories/applicant/uplaod_application_from/"+servid+"/"+factid+"/"+appid+"/"+refid;
   //var RedirectURL = "/factories/applicant/uplaod_application_from/"+servid+"/"+factid+"/"+appid+"/"+refid;
  var RedirectURL = 	window.location.origin+window.location.pathname+"/applicant/upload-application-renewal-form/"+servid+"/"+factid+"/"+appid+"/"+refid;
  // var RedirectURL = "/wbfactories/applicant/uplaod_application_from/"+servid+"/"+factid+"/"+appid+"/"+refid;

   var RedirectPauseSeconds = 7;
   
   setTimeout("DoTheRedirect('"+RedirectURL+"')",parseInt(RedirectPauseSeconds*1000));
}
function DoTheRedirect(url) { window.location=url; }
</script>

<?php
global $base_url,$base_root,$base_path;
require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';

function upload_application_renewal_form($form, &$form_state, $serviceid, $factory_typeid,$applicationid,$referenceno) {	
 global $base_root, $base_path, $user;
 $application_id 	= encryption_decryption_fun('decrypt', $applicationid);
 $service_id 		= encryption_decryption_fun('decrypt',$serviceid);
 $factory_type_id 	= encryption_decryption_fun('decrypt',$factory_typeid);
 $reference_no 		= encryption_decryption_fun('decrypt',$referenceno);
 $get_fa_cafa 				= get_fa_cafa($application_id);
 $application_status		= $get_fa_cafa['application_status'];
 $reg_identification_number	= $get_fa_cafa['factory_reg_identification_number'];
 $period_for_application	= $get_fa_cafa['period_for_application'];
 //echo $period_for_application;die;
 $form = array();
 $form['#attributes'] 	= array('enctype' => "multipart/form-data");
 $form['serviceid_hidden'] = array(
 	'#type' 			=> 'hidden',
	'#default_value' 	=> $serviceid,
	);
 $form['factorytypeid_hidden'] = array(
	'#type' 			=> 'hidden',
	'#default_value' 	=> $factory_typeid
		);
  $form['reference_no_hidden'] = array(
	'#type' 			=> 'hidden',
	'#default_value' 	=> $referenceno		 
	);
 $form['applicationid_hidden'] = array(
	'#type' 			=> 'hidden',
	'#default_value' 	=> $applicationid
	);	
 $form['reg_identification_hidden'] = array(
	'#type' 			=> 'hidden',
	'#default_value' 	=> encryption_decryption_fun('encrypt',$reg_identification_number)
	);	
	$form['period_for_application_hidden'] = array(
	'#type' 			=> 'hidden',
	'#default_value' 	=> encryption_decryption_fun('encrypt',$period_for_application)
	);	
	$pdf_link_p	= l('<i class="fa fa-download" aria-hidden="true"></i> Download Application Form', 'download-pdf-registration/'.$applicationid.'/'.$referenceno.'/'.$serviceid.'/'.$factory_typeid.'/'.encryption_decryption_fun('encrypt',$application_status), array('html' => TRUE,'attributes'=>array('onClick' => 'return DownloadAndRedirect("'.$serviceid.'","'.$factory_typeid.'","'.$applicationid.'","'.$referenceno.'");','title' => 'View','class'=>array('btn btn-primary pull-right'))));//,'target' => 'blank'

	if(($application_status == 'P' || $application_status == 'RS') && ($get_fa_cafa['download_status']==0)){
	 
		$form['header'] = array(
			'#markup' 					=> t('<div class="cus-page-outer-view"><div class="content"><center><h3><b>Application for Factory Renewal of license<br/>'.$get_fa_cafa['factory_name'].'</b></h3><p style="overflow:hidden;">'.$pdf_link_p.' <span class="pull-left line-height-34"><b>STEP #1</b> &nbsp;&nbsp;</span><span class="blink pull-left line-height-34"> Download application for Digital Signature <i class="fa fa-hand-o-right"></i> &nbsp; </span></p></center><hr><b>STEP #2</b> &nbsp;&nbsp; Upload Pdf with DSC <br><br>[<span style="color: green"><b>NOTE : </b> After downloading the application Pdf, <b style="color:#000;">STEP #2 </b>will be activated.<br> To complete the renewal process please do the signature and upload the pdf.]</span>'),
		);
	   }// else { $pdf_link = ''; }
	   
	   if($get_fa_cafa['download_status']==1){
		 
	   $form['header'] = array(
		 '#markup' 					=> t('<div class="cus-page-outer-view"><div class="content"><center><h3><b>Application for Factory Renewal of license<br/>'.$get_fa_cafa['factory_name'].'</b></h3></center><hr>'),
	   );
	   
	   $form['#attributes']['class'][] = 'custom-form-main';
	   $form['factory_part_upload'] 	= array(
		 '#type' 					=> 	'fieldset',
		 '#title' 					=> 	t('Upload document'),
		 '#collapsible' 				=> 	TRUE, //Upload Pdf with DSCm  Added
		 '#collapsed' 				=>  FALSE,  // Added
		 '#prefix' 					=> '<div class="" style="overflow:hidden;"><b>STEP #1</b>&nbsp;&nbsp; Download application for Digital Signature '.$pdf_link_p.'<br><br><b>STEP #2</b> <span class="blink"> &nbsp; Upload Pdf with DSC</span><br><br>',
		 '#suffix' 					=> '',
	   
	   );
			
	   $form['factory_part_upload']['start_upload_section'] = array(
		 '#prefix' 					=> '<div class="row">',
		 '#suffix' 					=> '',
	   );  
	   $form['factory_part_upload']['application_pdf_upload'] = array(
		'#type' 						=> 'managed_file',
		'#title' 					=> t('(PDF only, Max size 5MB)'),
		'#attributes' 				=> array('class'=>array('form-control browse-height-auto'),'placeholder'=>'Upload documents'),
		'#required' 				=> TRUE,
			'#upload_validators' 	 => array('file_validate_extensions' => array('pdf'), 'file_validate_size' => array(50*1024*1024)),
		   '#upload_location' 		 => 'public://upload/upload_pdf/',
		   '#process' 				 => array('import_my_file_element_process'),
		'#prefix' 					=> '<div id="replace_div_file"><div class="col-md-4">',
		'#suffix' 					=> '</div></div>'	
	   );
	   
	   $form['submit'] = array(
		 '#prefix' 					=> '',
		 '#suffix' 					=> '</div></div>',
		 '#attributes' 				=> array(
		 'class' 					=> array( 'btn btn-success' )),
		 '#type' 					=> 'submit',
		 '#value' 					=> 'Final Submit'
									 );
	   }
	   if($get_fa_cafa['download_status']==1){
		$form['note'] = array(
			'#markup' 					=> t('<br>[<span style="color: green"><b>NOTE : </b> After downloading the application Pdf, <b style="color:#000;">STEP #2 </b>will be activated.<br> To complete the renewal process please do the signature and upload the pdf.]</span>'),
		);
	}
	return $form; 	 
}

function upload_application_renewal_form_validate($form, &$form_state) {

	$file_caf_application = file_load($form_state['values']['application_pdf_upload']);


	if($file_caf_application->fid != '') {
		$chk = isStringInFile($file_caf_application->fid, 'adbe.pkcs7.detached');
		if($chk != 0)
		{
			form_set_error('caf', 'Common application form for Upload is not digitally signed!!! Please remove and upload again!!!');
		}
	}

}

function upload_application_renewal_form_submit($form, &$form_state){
	
	global $user,$base_path;
	$val   						    =  $form_state['values'];
	$uid 			    			=  $user->uid;
	$service_id						=  encryption_decryption_fun('decrypt',$val['serviceid_hidden']);
	$factory_type_id				=  encryption_decryption_fun('decrypt',$val['factorytypeid_hidden']);
	$application_id 				=  encryption_decryption_fun('decrypt',$val['applicationid_hidden']);
	$application_reference_no		=  encryption_decryption_fun('decrypt',$val['reference_no_hidden']);
 	$reg_identification				=  encryption_decryption_fun('decrypt',$val['reg_identification_hidden']);	
	$period_for_application	= encryption_decryption_fun('decrypt',$val['period_for_application_hidden']);	
	
	$renewal_dim_appoved = db_query("SELECT renewal_dim_appoved  FROM {fa_cafa} WHERE id = '".$application_id."' AND service_id = '".$service_id."' AND factory_typeid = '".$factory_type_id."' AND reference_number = '".$application_reference_no."'")->fetchObject()->renewal_dim_appoved;
	
	if($service_id==2){
		$registration_application = create_registration_application($service_id);
		$document_name = "CAF (For Registration)";
	}elseif($service_id==3){
		$registration_application = create_registration_application($service_id);
		$document_name = "CAF (For Renewal of License)";
	}

	$document_listid =  fun_fetch_document_listid($document_name);
	$application_pdf =  file_load($val['application_pdf_upload']);
		
	if($application_pdf != "" ){
		$path_category = pathinfo($application_pdf->filename);
			
        $new_filename_cat = 'CAF'.date('Y').'_'.$factory_type_id.'_'.time().'.'.$path_category['extension'];
        $application_pdf->filename = $new_filename_cat;
       // file_save($application_pdf);

        $filename_cat_arr = explode("/", $application_pdf->uri);

        $filepathSave_cat 	= file_get_contents(escapefile_url('public://upload/upload_pdf/'.$filename_cat_arr[4]));
        
        $content_cat		= base64_encode($filepathSave_cat);

            $cat_doc_content_arr = array(
                'upload_doc_content' => $content_cat,
            );		
		$get_CAF = get_caf_upload_doc_details($application_id, $service_id, 'CAF', $factory_type_id, $application_reference_no);

		if(!empty($get_CAF)){
			
			$content_id = $get_CAF->upload_doc_content_id;

			$queryabc = db_update('fa_caf_upload_doc_content');
        		$queryabc->fields($cat_doc_content_arr);
       			$queryabc->condition('id', $content_id, '=');
		        $queryabc->execute();
					
				$cat_upload_doc = array(
					'file_name' 		=> $new_filename_cat,
					'created_date'		=> date('Y-m-d h:i:s'),
                
            	);
				$queryabc = db_update('fa_caf_upload_all_doc');
        		$queryabc->fields($cat_upload_doc);
       			$queryabc->condition('upload_doc_content_id', $content_id, '=');
		        $queryabc->execute();
					
				 	
			}else{

				$id_doc =  db_insert('fa_caf_upload_doc_content')->fields($cat_doc_content_arr)->execute();
                $cat_upload_doc_arr = array(
					'application_id' 				=> $application_id,
					'application_reference_no' 		=> $application_reference_no,
					'file_name' 					=> $new_filename_cat,
					'factory_typeid' 				=> $factory_type_id,
					'service_id' 					=> $service_id,
					'upload_doc_content_id' 		=> $id_doc,
					'upload_doc_type' 				=> 'CAF',
					'created_by'					=> $uid,
					'created_date'				 	=> date('Y-m-d h:i:s'),
					'doc_master_id'					=> $document_listid['id'],
					'identity_flag'					=> $document_listid['identity_flag']
                
            	);
            	db_insert('fa_caf_upload_all_doc')->fields($cat_upload_doc_arr)->execute();
			}
			
           
        }else{
            form_set_error('CAF', 'Please Select application form file!!!');
        }

	


	
	if($service_id == 3 && $renewal_dim_appoved == 1){


		$get_licence_valid_to 		= get_licence_valid_to($service_id,$factory_type_id,$application_id,$application_reference_no);
		$status_update = array('application_status'=>'I','created_date'=>date("Y-m-d"),'factory_reg_identification_number'=>$registration_application,'license_valid_upto'=>$get_licence_valid_to,'period_for_renewal'=>$period_for_application,'license_date'=>date("Y-m-d"));
		
		$queryabc 		 =	db_update('fa_cafa');
		$queryabc		->	fields($status_update);
		$queryabc		->	condition('id',$application_id,'=');
		$queryabc		->	execute();

		///////////////////AUTO LICENCE UPDATE CODE/////////////////////

		$get_LIC = get_caf_upload_doc_details($application_id, $service_id, 'LIC', $factory_type_id, $application_reference_no);
		if(empty($get_LIC)){
			

			///////////////////PDF GENERATE HERE/////////////////////
			$get_all_data      	= 	get_fa_cafa($application_id);
			//print_r($get_all_data);die;
			$max_license_no 	= $get_all_data['factory_license_no'];
			$max_reg_no 		= $get_all_data['factory_registrstion_no'];
			$zonid 				= $get_all_data['factory_zone'];
			$zone 				= get_factory_zone_name($zonid);
			$payment_amount		= $get_all_data['payment_amount'];
			$payment_date		= $get_all_data['payment_date'];
			$district_code		= $get_all_data['district'];
			$auto_renew 		= $get_all_data['renewal_dim_appoved'];
			$factory_owershiptype = $get_all_data['factory_owershiptype'];
			$status 				= $get_all_data['application_Status'];
		
		
		
			$lic_validity    		= $get_all_data['license_valid_upto'];
			$lic_date    			= !empty($get_all_data['license_date'])?$get_all_data['license_date']:date('Y-m-d');
		
			$get_licence_valid_to 	= get_licence_valid_to($service_id,$factory_type_id,$application_id,$application_reference_no);
		
			$grand_to 				= '';
			if($factory_owershiptype == "ltd" || $factory_owershiptype == "pv" || $factory_owershiptype == "others" || $factory_owershiptype == "psu" || $factory_owershiptype == "govt"){
				
				$grand_to = $get_all_data['factory_name'];
			}
			if($factory_owershiptype == "pro_firm"){
				$i=0;
				$get_ocupier_data = get_all_occupier_data($application_id,$service_id,$factory_type_id,$application_reference_no);
				foreach($get_ocupier_data as $occuiper){
					$i= $i+1;
				}
				if($i>1){
					$grand_to = $occuiper->name_occupier.'& Others';
				}else{
					$grand_to  = $occuiper->name_occupier;
				}
			}if($factory_owershiptype == "par_firm"){
				$i=0;
				$get_director_data = get_director_details_service($application_id,$service_id,$factory_type_id,$application_reference_no);
				foreach($get_director_data as $director){
					
					$i= $i+1;
				}
				if($i>1){
					$grand_to = $director->name_director.'& Others';
				}else{
					$grand_to  = $director->name_director;
				}
			}
			
			if(empty($max_license_no)){
					$factory_license_no  = create_license_no($factory_type_id,$district_code);
					 $caf_update 	= 	array('factory_license_no' => $factory_license_no, 'license_date' => date('Y-m-d'));
					  $queryabc 		=	db_update('fa_cafa');
					   $queryabc		->	fields($caf_update);
					   $queryabc		->	condition('id',$application_id,'=');
					   $queryabc	    ->	execute();
					$max_license_no = $factory_license_no;
			   
			}
			//echo $get_licence_valid_to.'---'.$lic_validity;die;
			if(($lic_validity != $get_licence_valid_to )&&  ($status!= 'I')){
		
					$caf_update_date 	= 	array('license_date' => date('Y-m-d'));
					  $queryabc 		=	db_update('fa_cafa');
					   $queryabc		->	fields($caf_update_date);
					   $queryabc		->	condition('id',$application_id,'=');
					   $queryabc	    ->	execute();
		
			}
			
			if(empty($max_reg_no)){
					$registration_no = create_registration_no($factory_type_id,$district_code);
					$caf_update1 	= 	array('factory_registrstion_no' => $registration_no, 'registration_date' => date('Y-m-d'));
					  $queryabc1 		=	db_update('fa_cafa');
					   $queryabc1		->	fields($caf_update1);
					   $queryabc1		->	condition('id',$application_id,'=');
					   $queryabc1	    ->	execute();
					$max_reg_no = $registration_no;
			}
				
			//$max_license_no 			= $get_all_data['factory_license_no'];
			//$max_reg_no 				= $get_all_data['factory_registrstion_no'];
			$get_all_nature_data 		= get_nature_manufacture_data($application_id);
			$get_all_power_data 		= get_power_data($application_id,$service_id,$factory_type_id,$application_reference_no);
			$worker_details 			= get_worker_details_service($service_id,$factory_type_id,$application_id,$application_reference_no);
			$renewal_amendment_list 	= 	toatl_fees_breakup($application_id,$service_id,$factory_type_id,$application_reference_no);
		
		
		
		//print_r($get_all_power_data);
		//print_r($worker_details);die;
		
			$maxWorker = 0;
			foreach($worker_details as $worker){
				$max_worker = $worker->worker_total;
				$maxWorker = max($max_worker, $maxWorker);
				}
				
			$maxHP = 0;
			foreach($get_all_power_data as $power){
				$max_hp = $power->installed_power_hp;
				 $maxHP = max($max_hp, $maxHP);
				}
		
				
			$img_url					= $_SERVER['DOCUMENT_ROOT']. $base_path.'sites/all/themes/wbfactories/images/em.jpg';
			//print_r($img_url);die();
		
			$name_of_factory 			= 	$get_all_data['factory_name'];
			$amenability_date 			= 	$get_all_data['date_of_amenability'];
			$classification_no			= 	$get_all_data['classification_no'];
			$date_of_amenability 		= 	date('dS M Y', strtotime($amenability_date));
			
			$getdata_factory_address 	=  	array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
			$factory_address 			= 'Zone:-'.$zone['zone_name'].',&nbsp;'. $get_all_data['addrline'].',&nbsp;'.get_full_address_certificates('fa_cafa','sub-table',$application_id,$getdata_factory_address);
			
				$valid_to  = get_fa_cafa_log($application_id);
				foreach($valid_to as $valid){
					$valid_date = $valid->fa_licence_valid_to;
					}
				
				if($get_licence_valid_to != $valid_to){
					$data 	=  array(
							  'fa_name'=>  $name_of_factory ,
							  'fa_license_no'=> $max_license_no,
							  'fa_registartion_no' => $max_reg_no,
							  'fa_amenability_date' =>$get_all_data['date_of_amenability'],
							  'fa_power' =>$maxHP,
							  'fa_worker' =>$maxWorker,
							  'fa_fees' =>$payment_amount,
							  'fa_licence_valid_to' => $get_licence_valid_to,
							  'fa_issue_by'=> $user->uid,
							  'fa_issue_date' =>  date("Y-m-d"),
							  'fa_application_id'=> $application_id,
							  'fa_payment_date' => $payment_date,
							  'fa_service_id'=> $service_id,
							  'fa_active_inactive' =>1,
							  'is_genareate'		=>1
						);
						
					$exist_data = db_insert('fa_registration_licence_log')->fields($data)->execute();
				}
		
			
				
			$content = '<style type="text/css">
							table, td, th {
									font-size:12px;
									font-family:Times New Roman;
									height:15px;
									color:#000;
									margin-top:10px;
									background:#fff;
									line-hight: 25px;
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
								line-hight: 1px;
							}
							#tabular tr {
								padding-top: 12px;
								padding-bottom: 12px;
								text-align: left;
								background-color: #666;
								color: white;
								}
							.data{ text-transform: uppercase;font-weight:bold;}
					</style>';
			$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">				
							<tr><td colspan="3"></td></tr>
							
							<tr><td colspan="3" align="center" style="font-size:15px;text-transform:uppercase;"><h2> FORM-3 </h2></td></tr>
							<tr><td colspan="3"  align="center" style="font-size:10px;">[See rules5(1),6(4),7(1) and 8(2)]</td></tr>
							<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden; text-transform:uppercase;">GOVERMENT OF WEST BENGAL</td></tr>
							<tr><td colspan="3" align="center"><img src="'.$img_url.'" width="40px"/></td></tr>
							
							<tr><td colspan="3" align="center" style="border-style:hidden hidden double hidden; text-transform:uppercase;">Directorate of Factories</td></tr>
							</table>';			
			$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
						 <tr><td colspan="3" align="center" style="font-size:18px;"><h3 style="border-bottom:0px solid;"><title>LICENCE TO WORK A FACTORY</title></h3></td></tr>
						 <tr><td colspan="3"></td></tr>
						 <tr><td colspan="3" align="left" >Licence No.&nbsp;<b>'.$max_license_no.'</b> Reg. No.&nbsp;<b>'.$max_reg_no.'</b> .&nbsp;Date of amenability  <span class="data">&nbsp;'.$date_of_amenability .'</span> &nbsp; H.P  <span class="data">'.$maxHP.'</span> &nbsp; Worker <span class="data"> '.$maxWorker.'&nbsp;</span> Fee Rs. '.$payment_amount.'/- &nbsp; 
						 Licence is hereby granted to<span class="data"> '.$grand_to.', </span> valid only for the factory knowns as  <span class="data">&nbsp;'.$name_of_factory.'</span>&nbsp;&nbsp;situated at &nbsp;&nbsp;<span class="data">' .$factory_address.'</span>, subject provisions of the Factories Act, 1948, and the rules made thereunder.</td></tr>
						 <tr><td>&nbsp;</td></tr>
						 <tr><td colspan="3" align="left" style="font-size:12px;">The licence shall remain in force till <b>'.date('dS M Y', strtotime($get_licence_valid_to)).'</b></td></tr>
						<tr>
							<td colspan="2" align="left" style="font-size:12px;">The '.date('dS M Y', strtotime($lic_date)).'</td>
		
							<td align="right" style="font-size:12px;">
							<br><br><br>
							Chief Inspector of Factories, West Bengal</td>
						</tr>
						 </table>';
			$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
						 <tr><td align="center" style="font-size:18px;"><h3>RENEWALS</h3></td></tr>
						 </table>';
						 
			$content .= '<table id="tabular">
						<tr>					 				
						<td width="14%" style="font-size:12px;" align="center" valign="top"> Valid up to </td>
						<td width="10%" style="font-size:12px;" align="center" valign="top"> H.P </td>
						<td width="14%" style="font-size:12px;" align="center" valign="top"> Worker </td>
						<td width="14%" style="font-size:12px;" align="center" valign="top">Fee for renewal </td>
						<td width="14%" style="font-size:12px;" align="center" valign="top"> Date of payment </td>
						<td width="14%" style="font-size:12px;" align="center" valign="top"> Late fee for renewal </td>
						<td width="18%" style="font-size:12px;" align="center" valign="top"> Signature of Chief <br> Inspector of Factories, West Bengal</td>
						</tr>';
						 
				foreach($renewal_amendment_list as $renew){
					if($renew->remark==NULL && $renew->service_id==3){
						$payment_date		= $get_all_data['payment_date'];
		
			$content .= '<tr>					 				
						<td width="14%"> '.$renew->service_year.'</td>
						<td width="10%"> '.$renew->power.'</td>
						<td width="14%">'.$renew->worker.' </td>
						<td width="14%">'.($renew->previous_paid_fees+$renew->due_fees).' </td>
						<td width="14%"> '.date('dS M Y', strtotime($payment_date)) .'</td>
						<td width="14%"> '.$renew->late_fees.'</td>
						<td width="18%"> </td>
						</tr>';
						 }
					}
		
			$content .= '</table>';
			$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
						 <tr><td align="center" style="font-size:18px;"><h3>TRANSFERS</h3></td></tr>
						 </table>';
						 
			$content .= '<table id="tabular">
						<tr>					 				
						<td width="25%" style="font-size:12px;" align="center" valign="top"> To whom transferred </td>
						<td width="25%" style="font-size:12px;" align="center" valign="top"> Date of Transfer </td>
						<td width="25%" style="font-size:12px;" align="center" valign="top"> Date of payment of transfer fee </td>
						<td width="25%" style="font-size:12px;" align="center" valign="top"> Signature of Chief <br> Inspector of Factories, West Bengal</td>
						</tr>';
						
						/* <tr>					 				
						
						<td width="25%"> </td>
						<td width="25%">  </td>
						<td width="25%"></td>
						<td width="25%"> </td>
						</tr> */
						
				$content .= '</table>';
				$content .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
						 <tr><td align="center" style="font-size:18px;"><h3>AMENDMENTS</h3></td></tr>
						 </table>';
						 
			$content .= '<table id="tabular">
						<tr>					 				
						<td width="14%" style="font-size:12px;" align="center" valign="top"> Date of amendment </td>
						<td width="10%" style="font-size:12px;" align="center" valign="top"> Amended worker </td>
						<td width="14%" style="font-size:12px;" align="center" valign="top"> Amended H.P </td>
						<td width="14%" style="font-size:12px;" align="center" valign="top"> Date of payment of Amendment fee </td>
						<td width="14%" style="font-size:12px;" align="center" valign="top"> additional fee </td>
						<td width="18%" style="font-size:12px;" align="center" valign="top"> Signature of Chief <br> Inspector of Factories, West Bengal</td>
						</tr>';
						foreach($renewal_amendment_list as $amend){
							if($amend->remark =="Amendment"){
								$payment_date		= $get_all_data['payment_date'];
					$content .= '<tr>					 				
								<td width="14%"> '.$amend->service_year.'</td>
								<td width="10%">'.$amend->worker.' </td>
								<td width="14%"> '.$amend->power.'</td>
								<td width="14%"> '.date('dS M Y', strtotime($payment_date)) .'</td>
								<td width="14%">'.($amend->previous_paid_fees+$amend->due_fees).' </td>
								<td width="18%"> '.$amend->previous_paid_fees.'</td>
								</tr>';
								 }
							}
					$content .= '</table>';
				//echo $content;
				if($auto_renew==1){
					$content .= '<br/><br/><br/><br/>This License Certificate is computer generated and therefore does not require any signature.';
				}		
			
			///////////////////PDF GENERATE HERE/////////////////////

			ob_end_clean();
			$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 20, 10, 0, 0);
			$mpdf->SetDisplayMode('fullpage');
			//$mpdf->watermarkImageAlpha = 1;
			$mpdf->WriteHTML($content);
	
			$mpdf->Output('public://upload/upload_pdf/Licence_file_'.$application_id.'_'.time().'.pdf','F');
			$file_name = 'Licence_file_'.$application_id.'_'.time().'.pdf';

			$filepathSave_cat 	= file_get_contents(escapefile_url('public://upload/upload_pdf/'.$file_name));

			$document_name 		= "License Certificates";
			$document_listid =  fun_fetch_document_listid($document_name);

			$content_cat		= base64_encode($filepathSave_cat);

            $cat_doc_content_arr = array(
                'upload_doc_content' => $content_cat,
			);		
			//print_r($cat_doc_content_arr);die;

			$id_doc =  db_insert('fa_caf_upload_doc_content')->fields($cat_doc_content_arr)->execute();
                $cat_upload_doc_arr = array(
					'application_id' 				=> $application_id,
					'application_reference_no' 		=> $application_reference_no,
					'file_name' 					=> $file_name,
					'factory_typeid' 				=> $factory_type_id,
					'service_id' 					=> $service_id,
					'upload_doc_content_id' 		=> $id_doc,
					'upload_doc_type' 				=> 'LIC',
					'created_by'					=> $uid,
					'created_date'				 	=> date('Y-m-d h:i:s'),
					'doc_master_id'					=> $document_listid['id'],
					'identity_flag'					=> $document_listid['identity_flag']
                
            	);
            	db_insert('fa_caf_upload_all_doc')->fields($cat_upload_doc_arr)->execute();



			// $content_id = $get_LIC->upload_doc_content_id;

			// $queryabc = db_update('fa_caf_upload_doc_content');
        	// 	$queryabc->fields($cat_doc_content_arr);
       		// 	$queryabc->condition('id', $content_id, '=');
		    //     $queryabc->execute();
					
			// 	$cat_upload_doc = array(
			// 		'file_name' 		=> $file_name,
			// 		'created_date'		=> date('Y-m-d h:i:s'),
                
            // 	);
			// 	$queryabc = db_update('fa_caf_upload_all_doc');
        	// 	$queryabc->fields($cat_upload_doc);
       		// 	$queryabc->condition('upload_doc_content_id', $content_id, '=');
			// 	$queryabc->execute();
				

			//echo $file;die;


		}else{
			//echo 'entry';die;
			drupal_set_message('License has been Already renewed.'); 
			drupal_goto('applicant-dashboard');
		}

		///////////////////END AUTO LICENCE UPDATE CODE/////////////////////
			 
		remark_input($application_reference_no,$application_id,'I','License has been successfully renewed. It is system genarated')	;
		
		drupal_set_message('License has been successfully renewed . Your application number is:- '.$registration_application); 
		drupal_goto('applicant-dashboard');

	}else{
	
		$status_uodate = array('application_status'=>'U','created_date'=>date("Y-m-d"),'factory_reg_identification_number'=>$registration_application,'download_status'=>NULL);
			$queryabc 		 =	db_update('fa_cafa');
			$queryabc		->	fields($status_uodate);
			$queryabc		->	condition('id',$application_id,'=');
			$queryabc		->	execute();

		$ack_link	= l('Acknowledgment', 'registration-acknowledgement-certificate/'.$val['applicationid_hidden'].'/'.$val['reference_no_hidden'].'/'.$val['serviceid_hidden'].'/'.$val['factorytypeid_hidden'], array('html' => TRUE,'target' => '_BLANK','attributes'=>array('title' => 'View', 'class'=>array('button'))));
		remark_input($application_reference_no,$application_id,'U','Application from successfully uploaded and renewal application sucessfully submitted')	;
		drupal_set_message('Your application is sucessfully submitted . Your application number is:- '.$registration_application. $ack_link); 
	}

	drupal_goto('applicant-dashboard');
   
}

function get_fa_cafa_log($application_id){
	$cafa_log = db_query("select * from fa_registration_licence_log WHERE fa_application_id='".$application_id."' AND is_genareate = 1 ORDER BY id DESC LIMIT 1")->fetchAll();
	return $cafa_log;
	}
