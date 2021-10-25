<?php

function application_log_list_applicant($form, &$form_state,$applicationid) {

	global $base_root,$base_path,$user;
	$application_id 	= encryption_decryption_fun('decrypt', $applicationid);
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
    $form = array();
	//echo $user->uid;die();
	$form['applicant_applicantion']['markup_appplication'] = array(
		'#prefix' 	=> '<div class="row"><div class="box box-info"><div class="box-header with-border">
						<div class="col-lg-12 col-md-12 col-sm-12"><h3 class="box-title">Application List</h3></div>
						<div class="box-tools pull-right">
						<button type="button" class="btn btn-box-tool" data-widget="collapse" title="Minimise"><i class="fa fa-minus"></i> </button>
						<button type="button" class="btn btn-box-tool" data-widget="remove" title="Close"><i class="fa fa-times"></i></button>
						</div>
						</div>
						<div class="box-body"><div class="col-lg-12 col-md-12 col-sm-12"><div class="table-responsive">',
		'#suffix' 	=> '</div></div></div></div></div>',
		'#type' 	=> 'markup',
		'#markup' 	=> application_log($application_id),
  	);		  
	return $form; 
  }
		 
function application_log($application_id){
	global $base_root,$base_path,$user;
	                                                                                                                                 
	$applicant_id 			= $user->uid;
	$get_all_data 			= array();
	$rows[] 				= array();
	$type					= '';
	$details				= '';
	$relationship			= '';
	$address_of_director	= '';
	$status 				= '';
	$link					= '';
	$pdf_link 				= '';
	$edit_link				= '';
	$preview_link			= '';
	$upload_link			= '';

	$get_all_data 			=  get_application_log($application_id);
	
	//echo "<pre>"; print_r($get_all_data); exit;
	
	$Wcounter				= 0;
	$per_page				= 10;
	$current_page 			= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 				= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 			= $current_page*$per_page;
	}
	$header 				= array(
								array('data'=> 'Sl. No.','width' => '6%'),
								array('data'=> 'Factory Details','width' => '25%'),
								array('data'=> 'e-Service','width' => '15%'),
								array('data'=> 'Application No. &amp; Date','width' => '17%'),
								array('data'=> 'Status &amp; Date','width' => '22%'),
								array('data'=> 'Action','width' => '15%'),
							);
	 						
	if(!empty($get_all_data)){
		foreach($chunks[$current_page] as $details){ 
			$Wcounter++;
			if($details->service_id == '4'){
				$pay_now			= 	"";
				$pdf_link			=	"";
				$view_link			=	"";
				$edit_link			= 	"";
				$upload_application = 	"";
				$ack_link			= 	"";
				$genare_status   	= $details->plan_approve_status;
				$pdf_link		 	= l('<i class="ace-icon fa fa-file-pdf-o bigger-130 text-blue"></i> Pdf', 'download-pdf-new-plan/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'Download PDF', 'class'=>array(''), 'target' => '_blank')));
				$edit_link		 	= l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> Edit', 'applicant/caf/default/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->previous_id), array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array(''), 'target' => '_blank')));
				$preview_link	 	= l('<i class="fa fa-eye" aria-hidden="true"></i> View', 'applicant/application_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
				$view_dwnld_link	 = l('<i class="fa fa-eye" aria-hidden="true"></i> View & Donwload PDF', 'applicant/application_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
				$upload_link	 	= l('<i class="fa fa-upload" aria-hidden="true"></i> Upload Form', 'applicant/application_upload/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
				
				$Identification = $details->plan_approve_identification_number;	
			if(empty($Identification)){
				  	$Identification = 'Under Process';
			 	}
				/******** ADDED BY SUBHAMAY **************************************************************************************/
					if($details->tm_migrated_flag!='N')
					{
					//	echo 'LLLL'.$details->approve_dsc_reg_file;
				
					$dwnld_cert = l('<i class="fa fa-download" aria-hidden="true"></i> Plan Approval Cert.',$base_url.'/feesmigrate/display-file/'.$details->backlog_uploaded_letter,array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank','class'=>array('text-blue'))));
					$dwnld_plan = l('<i class="fa fa-download" aria-hidden="true"></i> Download Plan',$base_url.'/feesmigrate/display-file/'.$details->backlog_uploaded_plan,array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_BLANK')));	
				} 
				else
				{
					//$get_dwnld_cert = get_uploaded_document_url($details->uploaded_letter);
						
					$get_dwnld_cert = get_uploaded_document_url($details->uploaded_letter);
					$dwnld_cert = l('<i class="fa fa-download" aria-hidden="true"></i> Plan Approval Cert.',file_create_url($get_dwnld_cert),array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank','class'=>array('text-blue'))));

					$get_dwnld_plan = get_uploaded_document_url($details->uploaded_plan);
					$dwnld_plan = l('<i class="fa fa-download" aria-hidden="true"></i> Download Plan',file_create_url($get_dwnld_plan),array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_BLANK')));
				}
				/******** ENDED BY SUBHAMAY *************************************************************************************/
				
				/*$get_dwnld_cert = get_uploaded_document_url($details->uploaded_letter);
				$dwnld_cert = l('<i class="fa fa-download" aria-hidden="true"></i> Plan Approval Cert.',file_create_url($get_dwnld_cert),array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank','class'=>array('text-blue'))));
				
				$get_dwnld_plan = get_uploaded_document_url($details->uploaded_plan);
				$dwnld_plan = l('<i class="fa fa-download" aria-hidden="true"></i> Download Plan',file_create_url($get_dwnld_plan),array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_BLANK'))); */

				$view_remarks	= l('<i class="fa fa-eye" aria-hidden="true"></i> View Remarks', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''), 'target' => '_blank')));

				//$apply_registration	= l('<i class="fa fa-registered" aria-hidden="true"></i> Apply Registration', 'apply-eservice-registration/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','2'), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''), 'target' => '_blank')));

				//$apply_extension	= l('<i class="fa fa-expand" aria-hidden="true"></i> Apply Extension', 'apply-eservice-extension/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','5'), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''), 'target' => '_blank')));

				if($details->plan_approve_status == 'I'){
					$status = '<b class="text-green">Issued</b>';
					$link = $preview_link.'<br>'.$dwnld_cert.'<br>'.$dwnld_plan.'<br>'.$view_remarks.'<br/>'.$apply_registration.'<br/>'.$apply_extension;
					$ack_link="";
				}
			
			}
			
			if($details->service_id == '5'){
				$pay_now			= "";
				$pdf_link			= "";
				$view_link			= "";
				$edit_link			= "";
				$upload_application = "";
				$apply_amendment    = '';
				$ack_link			= "";
				$genare_status   = $details->plan_approve_status;
				$pdf_link		 = l('<i class="ace-icon fa fa-file-pdf-o bigger-130 text-blue"></i> Pdf', 'download-pdf-new-plan/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'Download PDF', 'class'=>array(''), 'target' => '_blank')));
				$edit_link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> Edit', 'applicant/caf_extn/plan_extension/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->previous_id), array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array(''), 'target' => '_blank')));
				$preview_link	 = l('<i class="fa fa-eye" aria-hidden="true"></i> View', 'applicant/application_view_extension/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
				$view_dwnld_link	 = l('<i class="fa fa-eye" aria-hidden="true"></i> View & Donwload PDF', 'applicant/application_view_extension/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
				$upload_link	 = l('<i class="fa fa-upload" aria-hidden="true"></i> Upload Form', 'applicant/application_upload_extension/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
				
				$get_dwnld_cert = get_uploaded_document_url($details->uploaded_letter);
				$dwnld_cert = l('<i class="fa fa-download" aria-hidden="true"></i> Plan Approval Cert.',file_create_url($get_dwnld_cert),array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank','class'=>array('text-blue'))));
				
				$get_dwnld_plan = get_uploaded_document_url($details->uploaded_plan);
				$dwnld_plan = l('<i class="fa fa-download" aria-hidden="true"></i> Download Plan',file_create_url($get_dwnld_plan),array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_BLANK')));

				$view_remarks	= l('<i class="fa fa-eye" aria-hidden="true"></i> View Remarks', 'applicant/remarks_view_extension/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''), 'target' => '_blank')));

			
				if($details->plan_approve_status == 'I'){
					$status = '<b class="text-green">Approval of Plan Issued</b>';
					$link = $preview_link.'<br>'.$dwnld_cert.'<br>'.$dwnld_plan.'<br>'.$view_remarks;
					//$pay_now="Pay now";
					$upload_application ="Upload Application Form";
					$payment_deatils="";
					$ack_link="";
					$apply_amendment = "";
				}
				$Identification = $details->plan_approve_identification_number;
					if(empty($Identification)){
						$Identification = 'Under Process';
					}
			}
			
			if($details->service_id == '2'){
				$apply_amendment 	= "";
				 $pay_now			= "";
				$pdf_link			= "";
				$view_link			= "";
				$edit_link			= "";
				$upload_application = "";
				$license_validty 	= "";
					
			
				$view_link		= l('<i class="fa fa-eye" aria-hidden="true"></i> View', 'applicant/application-display-log/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''), 'target' => '_blank')));
					
			
				$Identification = $details->factory_reg_identification_number;	
				if(empty($Identification)){
					$Identification = 'Under Process';
				}
				
				$approve_dsc_reg_file_id		= 	$details->approve_dsc_reg_file_id;
				$approve_dsc_licence_file_id	= 	$details->approve_dsc_licence_file_id;
				$dsc_licence_register_file		= 	$details->approve_dsc_reg_licence_file_id;
				$period_for_application 		=	$details->period_for_application;
			
				
			
			if($details->application_status == 'I'){
				$status 			= '<b style="color:Green;">Issued</b>';
				$link 				= $view_link;
				$upload_application = "Upload Application Form";
				$pay_now			= "Pay now";
				$repayment			= 'Re-payment';
				$amend_certificate	= "Amendment Certificate";
				$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
				$ack_link = l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
				
				
				/******** ADDED BY SUBHAMAY **************************************************************************************/
				 if($details->tm_migrated_flag!='N')
				 {
					// $reg_down	= l('Registration Certificate', $base_url.'/sites/default/files/uploads/factory_cert/'.$details->approve_dsc_reg_file, array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					//$lic_down	= l('Licence Certificate',$base_url.'/sites/default/files/uploads/factory_cert/'.$details->approve_dsc_licence_file, array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				
				    $reg_down	= l('Registration Certificate', $base_url.'/feesmigrate/display-file/'.$details->approve_dsc_reg_file, array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$lic_down	= l('Licence Certificate',$base_url.'/feesmigrate/display-file/'.$details->approve_dsc_licence_file, array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				
				}else{
					$reg_down	= l('Registration Certificate', 'document-list/download-registration-file/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','REG'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$lic_down	= l('Licence Certificate','document-list/download-license-file/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','LIC'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				}
				/******** ENDED BY SUBHAMAY *************************************************************************************/
				}
				
		
			
			}
			
			if($details->service_id == '3'){
				$pay_now			= '';
				$pdf_link			= '';
				$view_link			= '';
				$edit_link			= '';
				$upload_application = '';
				$download_licence	= '';
				$reg_down			= '';
				$lic_down			= '';
				$license_validty 	= '';
				$apply_amendment    = '';
				$amend_certificate	= ''; 
				
				
				/*if($details->is_backlog==1){
			
		 				if(!empty($details->backlog_license_number)){
							$edit_link		= l(' Edit','applicant/caf-backlog-renew/apply-backlog-renewal-service/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->backlog_license_number).'/'.encryption_decryption_fun('encrypt',$details->backlog_license_date).'/'.encryption_decryption_fun('encrypt','lic_no'),array('html' => TRUE,'attributes'=>array('title' => 'Edit',  'target' => '_blank')));
						}
						if(!empty($details->backlog_registration_no)){
							$edit_link		= l(' Edit','applicant/caf-online-renew/apply-backlog-renewal-service/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->backlog_registration_no).'/'.encryption_decryption_fun('encrypt',$details->backlog_registration_date).'/'.encryption_decryption_fun('encrypt','reg_no'),array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'target' => '_blank'))) ;
						}
					}*/
					
				//if($details->is_backlog==NULL){
					//if(!empty($details->factory_registrstion_no)){
				
						$edit_link = l('Edit','applicant/caf-online-renew/apply-online-renewal-service/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number),array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'target' => '_blank'))) ;
						//}
					//}
						$view_link		= l('<i class="fa fa-eye" aria-hidden="true"></i> View', 'applicant/application-display-registration/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''), 'target' => '_blank')));
				
				if($details->application_status == 'I'){
					$status 			= '<b style="color:Green;">Issued</b>';
					$link 				= $view_link;
					$upload_application = 'Upload Application';
					$apply_amendment    = '';
					$pay_now			= "Pay now";
					$repayment			= 'Re-payment';
					
					//$apply_renewal 		= l('Apply for Renewal', 'apply-eservice-registration-renewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'target' => '_blank')));
					$ack_link 			= l('Acknowledgment', 'applicant/renewal-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
					
					 if($details->tm_migrated_flag!='N')
				     {
						 $reg_down	= l('Registration Certificate', $base_url.'/feesmigrate/display-file/'.$details->approve_dsc_reg_file, array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
						$lic_down	= l('Licence Certificate',$base_url.'/feesmigrate/display-file/'.$details->approve_dsc_licence_file, array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				     }
					 else
					 {
						$reg_down	= l('Registration Certificate', 'document-list/download-registration-file/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','REG'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
						$lic_down	= l('Licence Certificate','document-list/download-license-file/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','LIC'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
		 			}
					 
					$amend_certificate	= l('Amendment cetificate', file_create_url(get_uploaded_document_url($details->approve_amendment_file_id)), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					
					
					$license_validty 	= !empty($details->license_valid_upto)?'<span style="color:red">Expire Date:-'.date('dS M Y', strtotime($details->license_valid_upto)).'</span>':"";
					if($details->license_valid_upto > date('Y-m-d')){
					//$apply_amendment    = l('Apply for Amendment', 'applicant/change-list-amendment/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','amend'), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
				}else{
					//	$apply_amendment	= 'Apply for Amendment';
					}
				}
				//echo $details->application_status.'---'.$details->renewal_dim_appoved;die;
				if($details->application_status == 'I' && $details->renewal_dim_appoved == 1){
					$status 			= '<b style="color:Green;">Issued</b>';
					$link 				= $view_link;
					$upload_application = 'Upload Application';
					$apply_amendment    = '';
					$pay_now			= "Pay now";
					$repayment			= 'Re-payment';
					$amend_certificate	= l('Amendment cetificate', file_create_url(get_uploaded_document_url($details->approve_amendment_file_id)), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					//echo $details->renewal_dim_appoved;die('checking........');
					//$reg_down	= l('Registration Certificate','applicant/application-license-auto-renewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number),array('html' => TRUE,'attributes'=>array('title' => 'Download Registration Certificate')));
					
					 if($details->tm_migrated_flag!='N')
				     {
					 $reg_down	= l('Registration Certificate', $base_url.'/feesmigrate/display-file/'.$details->approve_dsc_reg_file, array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
						$lic_down	= l('Licence Certificate',$base_url.'/feesmigrate/display-file/'.$details->approve_dsc_licence_file, array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				     }else{
					
						$reg_down	= l('Registration Certificate', 'document-list/download-registration-file/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','REG'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
						$lic_down	= l('Licence Certificate','document-list/download-license-file/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','LIC'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				 	}
					 
					$license_validty = !empty($details->license_valid_upto)?'<span style="color:red">Expire Date:-'.date('dS M Y', strtotime($details->license_valid_upto)).'</span>':"";
					//$apply_renewal 		= l('Apply for Renewal', 'apply-eservice-registration-renewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'target' => '_blank')));
					$ack_link 			= l('Acknowledgment', 'applicant/renewal-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
					
					if($details->license_valid_upto > date('Y-m-d')){
				//	$apply_amendment    = l('Apply for Amendment', 'applicant/change-list-amendment/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','amend'), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
				}else{
						$apply_amendment	= '';
					}
				}
		 	
				
					
				$Identification = $details->factory_reg_identification_number;	
			 	if(empty($Identification)){
					$Identification = 'Under Process';
			 	}
			}
			
			if($details->service_id == '8'){
				
					$apply_amendment 	= "";
				    $pay_now			= "";
				 	$pdf_link			= "";
					$view_link			= "";
					$edit_link			= "";
					$upload_application = "";
					$license_validty 	= "";
					
			
				 	$view_link		= l('<i class="fa fa-eye" aria-hidden="true"></i> View', 'amendment/application-display-amendment/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''), 'target' => '_blank')));
					
			
			
			
			$approve_dsc_reg_file_id		= 	$details->approve_dsc_reg_file_id;
			$approve_dsc_licence_file_id	= 	$details->approve_dsc_licence_file_id;
			$dsc_licence_register_file		= 	$details->approve_dsc_reg_licence_file_id;
			$period_for_application 		=	$details->period_for_application;
			
			$license_validty = !empty($details->license_valid_upto)?'<span style="color:red">Expire Date:-'.date('dS M Y', strtotime($details->license_valid_upto)).'</span>':"";
			
			
			if($details->application_status == 'I'){
					$status 			= '<b style="color:Green;">Issued</b>';
					$link 				= $view_link;
					$upload_application = "";
					$pay_now			= "Pay now";
					$repayment			= 'Re-payment';
					
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
					
					$ack_link = l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
					
					
					//$apply_renewal = l('Apply for Renewal', 'apply-eservice-registration-renewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
					
					$license_validty = !empty($details->license_valid_upto)?'<span style="color:red">Expire Date:-'.date('dS M Y', strtotime($details->license_valid_upto)).'</span>':"";
					//$apply_amendment    = l('Amendment for License', 'applicant/change-list-amendment/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','amend'), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));
					
					/******** ADDED BY SUBHAMAY **************************************************************************************/
				  if($details->tm_migrated_flag!='N')
					{
				//	echo 'LLLL'.$details->approve_dsc_reg_file;
				
					 $reg_down	= l('Registration Certificate', $base_url.'/feesmigrate/display-file/'.$details->approve_dsc_reg_file, array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$lic_down	= l('Licence Certificate',$base_url.'/feesmigrate/display-file/'.$details->approve_dsc_licence_file, array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));	
					}else{
						$reg_down	= l('Registration Certificate', 'document-list/download-registration-file/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','REG'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$lic_down	= l('Licence Certificate','document-list/download-license-file/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->previous_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','LIC'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					}
					/******** ENDED BY SUBHAMAY *************************************************************************************/
				}

			
			$Identification = $details->factory_reg_identification_number;	
			if(empty($Identification)){
				  	$Identification = 'Under Process';
			 	}
		
				
			}
			
			
			//echo $details->factory_name.'-------------'.$details->factory_registrstion_no.'---------------'.$details->registration_date.'<br/>';
			if(!empty($details->created_date)){
				$created_date = date('dS M Y', strtotime($details->created_date));
			}else{
				$created_date = '';
			}

			if(($details->service_id == '2') && !empty($details->registration_date)){
				$modification_date = '<b>Date - </b>'.date('dS M Y', strtotime($details->registration_date));
			}else{
				$modification_date = '';
			}
			if(($details->service_id == '3') && !empty($details->registration_date)){
				$modification_date = '<b>Date - </b>'.date('dS M Y', strtotime($details->registration_date));
			}else{
				$modification_date = '';
			}
			if(($details->service_id == '4') && !empty($details->plan_approval_date)){
				$modification_date = '<b>Date - </b>'.date('dS M Y', strtotime($details->plan_approval_date));
			}else{
				$modification_date = '<b>Date - </b>'.date('dS M Y', strtotime($details->modification_date));
			}
			

			if(!empty($details->factory_plan_approval_number)){
				$plan_approval = $details->factory_plan_approval_number.'<b>,Dated on - </b>'.$modification_date;
			}else{
				if(!empty($details->backlog_plan_approval_no)){
					$plan_approval = $details->backlog_plan_approval_no.'<b>,Dated on - </b>'. date('dS M Y', strtotime($details->backlog_plan_approval_date));
				}else{
					$plan_approval = 'Under Process';
				}
			} 
			$regisration_date = !empty($details->registration_date)?date('dS M Y', strtotime($details->registration_date)):"";//die();
			
			if(!empty($details->factory_registrstion_no)){
				$registration_number = $details->factory_registrstion_no.'<b>,Dated on - </b>'.$regisration_date;
			}else{
				if(!empty($details->backlog_registration_no)){
					$regisration_date = !empty($details->backlog_registration_date)?date('dS M Y', strtotime($details->backlog_registration_date)):"";
					$registration_number = $details->backlog_registration_no.'<b>,Dated on - </b>'.$regisration_date ;
				}else{
					$registration_number = 'Under Process';
				}
			}
			
			$license_date = !empty($details->license_date)?date('dS M Y', strtotime($details->license_date)):"";
			if(!empty($details->factory_license_no)){
				$license_number = $details->factory_license_no.'<b>,Dated on - </b>'.$license_date;
			}else{
				if(!empty($details->backlog_license_number)){
					$license_date = !empty($details->backlog_license_date)?date('dS M Y', strtotime($details->backlog_registration_date)):"";
					$license_number = $details->backlog_license_number.'<b>,Dated on - </b>'.$license_date ;
				}else{
					$license_number = 'Under Process';
				}
			}
		
			$factory_type = explode(' ',$details->factory_type);
			
			if($details->service_id==4){
			
					$details_factor = $details->factory_name.' ['.$factory_type[1].']<br><b>Zone - </b>'.$details->zone_name.'<br/><b>Plan Approval No:-</b>'.$plan_approval;
			}else{//echo $registration_number;
					$details_factor = $details->factory_name.' ['.$factory_type[1].']<br><b>Zone - </b>'.$details->zone_name.'<br/><b>Plan Approval No:-</b>'.$plan_approval.'<br/><b>Reg. No.:-</b>'.$registration_number.'<br/><b>License. No.:-</b>'.$license_number.'<br/>';
			}
			//$factory_type = explode(' ',$details->factory_type);
			//die($details->license_valid_upto.'-----');

			
			$rows[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' =>$details_factor,'class' => array('')),
							array('data' =>$details->service_name ,'class' => array('')),
							array('data' =>$Identification.'<br><b>Date - </b>'.$created_date,'class' => array('')),
							array('data' =>$status.'<br>'.$modification_date.'<br>'.$license_validty,'class' => array('')),
							array('data' =>$link.'<br/>'.$payment_deatils.'<br>'.$ack_link.'<br/>'.$reg_down.'<br/>'.$lic_down,'class' => array('')),
						);
		} 
	}
	$output = theme_table(
	array(
		  'header' 			=> $header,
		  'rows' 			=> $rows,
		  'attributes' 	=> array('class' => array('table no-margin remove-odd-even# custom-table-view-dashboard')),
		  //'attributes' 		=> array('class' => array('table table-bordered custom-table-view')),
	      'caption' 		=> '',
		  'colgroups' 		=> array(),
		  'empty' 			=> t("No data found!") 
		)
	).theme('pager');	
		 return $output;
	
}


/*function applicant_details(){
	global $user;
	$applicant_id = $user->uid;
	$details_applicant = get_details_applicant($applicant_id);
	$details_applicant_string = 'Name :- '.$details_applicant['fullname'].' ('.$details_applicant['gender'].')
		<br/> Mobile No. :- '.$details_applicant['mobile'].'<br/>  Email:- '.$details_applicant['mobile'].'<br/> Dob:- '.date('dS M Y', strtotime($details_applicant['dob']));
	//print_r($details_applicant);die();
	
	$fieldArr_applicant		 =  array('district','subdivision','areatype','block','panchayat','policestation','pincode','state','postoffice');
    $address_of_applicant	 =	'Address :- '.$details_applicant['addrline'];//.'<br>'.get_full_address('fa_user_details','sub-table',$details_applicant['id'],$fieldArr_applicant);
					
	$header  = array(
						array('data' => 'Applicant Details'),
									
					);
	$rows[] 	= array( 
							array('data' =>$details_applicant_string.'<br/>'.$address_of_applicant ,'class' => array('')),
								
					);
	$output = theme_table(
	array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('class' => array('table', 'pretty', 'table-bordered table-hover')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") 
		)
	);
		 return $output;
}*/


?>