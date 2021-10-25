<?php

function applicant_dashboard($form, &$form_state) {

	global $base_root,$base_path,$user;
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
    $form = array();
	//echo $user->uid;die();


	$add_link = l('<i class="ace-icon fa fa-plus bigger-130 text-blue"></i> ADD REGISTERED FACTORY', 'add-new-factory', array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
	$apply_eservice = l('<i class="ace-icon fa fa-plus bigger-130 text-blue"></i> Apply for New e-Service.', 'applicant/decission', array('html' => TRUE,'attributes'=>array('class'=>array(''), 'style' => 'padding-right:43px;font-weight: bold;font-size: 17px;')));
	$form['applicant_applicantion']['markup_appplication1'] = array(
		'#prefix' 	=> '<div class="row">
						<div class="box-tools pull-left"><span  style="font-size: 18px;"><b>
						STEP-1 your project is New/ Proposed Factory/ Greenfield Project , you want to apply any service Approval of Plan , <br/>Extension of Plan or Registration please click here <i class="fa fa-hand-o-right"></i> '.$apply_eservice.
						'<br/>STEP-2 you have registered factory. you want to apply any service Renewal of the License , Amendment of the License etc or any NOTICE.<br/>
						First find your factory on the dashboard and apply for any services. 
						<br/>STEP-3  you are unable to find out this factory, please click on ADD REGISTERED FACTORY and add your factory profile.<br/>
Then You can then apply for any service or notice or annual return, etc. </b> <i class="fa fa-hand-o-right"></i> '.$add_link,

						 //click here <i class="fa fa-hand-o-right"></i> </b></span>'.$add_link,
											
						
		'#suffix' 	=> '</div></div>',
		'#type' 	=> 'markup',
		
  	);		 
	$form['applicant_applicantion']['markup_appplication'] = array(
		'#prefix' 	=> '<div class="row"><div class="box box-info"><div class="box-header with-border">
						<div class="col-lg-12 col-md-12 col-sm-12"><h3 class="box-title">Activity List</h3></div>
						<div class="box-tools pull-right">
						<button type="button" class="btn btn-box-tool" data-widget="collapse" title="Minimise"><i class="fa fa-minus"></i> </button>
						<button type="button" class="btn btn-box-tool" data-widget="remove" title="Close"><i class="fa fa-times"></i></button>
						</div>
						</div>
						<div class="box-body"><div class="col-lg-12 col-md-12 col-sm-12"><div class="table-responsive">',
		'#suffix' 	=> '</div></div></div></div></div>',
		'#type' 	=> 'markup',
		'#markup' 	=> get_all_type_application(),
  	);		  
	return $form; 
  }
		 
function get_all_type_application(){
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

	$get_all_data 			=  get_application($applicant_id);
	
//	echo "<pre>"; print_r($get_all_data); die($applicant_id);
	
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
								array('data'=> 'Status','width' => '15%'),
								array('data'=> 'Action','width' => '50%'),
							);						
							
	if(!empty($get_all_data)){
		foreach($chunks[$current_page] as $details){ 
			$Wcounter++;
			if($details->service_id == '4'){
			$view_link			= "";
			$license_validty 	= "";
				$apply_amendment 	= "";
   				$apply_renewal 		= "";
				$pay_now			= 	"Pay fees";
				$pdf_link			=	"";
				$view_link			=	"";
				$edit_link			= 	"";
				$upload_application = 	"Upload CAF";
				$ack_link			= 	"";
				$repayment			= "Repayment Request"; 
				$genare_status   	= $details->plan_approve_status;
				$dwnld_cert			= "Plan Approval Certificaties";
				$dwnld_plan			="Approved Plan";
				$reg_down			= "registration certificates";
				$lic_down			= "License";
				$apply_renewal		= "Apply Renewal of license";
				$apply_amendment	= "Apply Amendment of license";
				$apply_plan			= "Apply for Plan"; 		
				$pdf_link		 	= l(' Pdf', 'download-pdf-new-plan/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'Download PDF', 'class'=>array(''))));
				
				/*$edit_link		 	= l(' Edit', 'applicant/caf/default/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array(''))));
				$link	 	= l(' View', 'applicant/application_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));*/
				
				$view_dwnld_link	 = l('View & Donwload PDF', 'applicant/application_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				$upload_application	 	= l(' Upload CAF', 'applicant/application_upload/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				
				
				$view_log	 	= l('Application Log', 'view-application-log/'.encryption_decryption_fun('encrypt',$details->id), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));		
				
				
				

				

				if($details->plan_approve_status == 'In'){
						$status 			= '<b class="text-blue">Incomplete</b>';
						$link		 	= l(' Edit', 'applicant/caf/default/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array(''))));
						$ack_link			= "Acknowledgement";
                    	$apply_renewal 		= "";
						$pay_now			= 	"Pay fees";
						$upload_application = 	"Upload CAF";
						$apply_amendment    = "";
						//$reg_down 			= ""; 
						//$lic_down			= ""; 
						//$amend_certificate	= ""; 
						$repayment			= "Repayment Request"; 
						$apply_extension 	= "";
						$apply_registration	="Apply Registration";
						$payment_deatils	= "Payment details";
						//$dwnld_cert			= "Plan Approval Certificaties";
						//$dwnld_plan			="Approved Plan";
						$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
						//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$apply_renewal		= "Apply Renewal of license";
				$apply_amendment	= "Apply Amendment of license";
				$apply_plan			= "Apply for Plan"; 		
						$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if($details->plan_approve_status == 'F'){
					$status = '<b>Application Saved</b>';
					$link	 	= l(' View', 'applicant/application_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$upload_application	 	= l('Upload CAF', 'applicant/application_upload/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link			= "Acknowledgement";
					$edit_link			="";
                    $apply_renewal 		= "";
					$payment_deatils	= "Payment details";
					$upload_application = 	"Upload CAF";
					$pay_now			= 	"Pay fees";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_renewal		= "Apply Renewal of license";
				$apply_amendment	= "Apply Amendment of license";
				$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if($details->plan_approve_status == 'RS'){
					$status = '<b class="text-blue">Application Re-submittted</b>';
					$link	 	= l(' View', 'applicant/application_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$upload_application	 	= l('Upload CAF', 'applicant/application_upload/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link	="Acknowledgement";	

                    $apply_renewal 		= "";
					$payment_deatils	= "Payment details";
					$pay_now			= 	"Pay fees";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= "";
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_renewal		= "Apply Renewal of license";
					$apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if(($details->plan_approve_status == 'AI') && ($details->is_chemical == 0)){
					$status = '<b>Forwarded To Inspector General</b>';
					$link	 	= l(' View', 'applicant/application_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	

                	$apply_renewal 		= "";
					$payment_deatils	= "Payment details";
					$upload_application = 	"Upload CAF";
				$pay_now			= 	"Pay fees";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_renewal		= "Apply Renewal of license";
					$apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if(($details->plan_approve_status == 'AI') && ($details->is_chemical == 1)){
					$status = '<b>Forwarded To Inspector Chemical</b>';
					$link	 	= l(' View', 'applicant/application_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	

                    $apply_renewal 		= "";
					$payment_deatils	= "Payment details";
					$upload_application = 	"Upload CAF";
					$pay_now			= 	"Pay fees";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_renewal		= "Apply Renewal of license";
					$apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if($details->plan_approve_status == 'DC'){
					$status 			= '<b>Forwarded To Dy.CIF General</b>';
					$link	 	= l(' View', 'applicant/application_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	

                  	$apply_renewal 		= "";
					$payment_deatils	= "Payment details";
					$upload_application = 	"Upload CAF";
					$pay_now			= 	"Pay fees";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_renewal		= "Apply Renewal of license";
					$apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if($details->plan_approve_status == 'DCCh'){
					$status = '<b>Forwarded To Dy.CIF Chemical</b>';
					$link	 	= l(' View', 'applicant/application_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	


                   $apply_renewal 		= "";
					$payment_deatils	= "Payment details";
					$upload_application = 	"Upload CAF";
					$pay_now			= 	"Pay fees";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_renewal		= "Apply Renewal of license";
					$apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if(($details->plan_approve_status == 'JC') || ($details->plan_approve_status == 'JCF')){
					$status = '<b>Forwarded To Jt.CIF General</b>';
					$link	 	= l(' View', 'applicant/application_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	
	
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
                    $apply_renewal 		= "";
					$payment_deatils	= "Payment details";
					$upload_application = 	"Upload CAF";
					$pay_now			= 	"Pay fees";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_renewal		= "Apply Renewal of license";
					$apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
				}
				if($details->plan_approve_status == 'JCCh'){
					$status = '<b>Forwarded To Jt.CIF Chemical</b>';
					$link	 	= l(' View', 'applicant/application_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
					$apply_renewal 		= "";
					$payment_deatils	= "Payment details";
					$upload_application = 	"Upload CAF";
					$pay_now			= 	"Pay fees";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$apply_renewal		= "Apply Renewal of license";
					$apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
				}
				if($details->plan_approve_status == 'ABk'){
					$status = '<b class="text-red">Backed To Applicant</b>';
					$link	 	= l(' Edit', 'applicant/caf/default/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array(''))));/*l(' View', 'applicant/application_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));*/
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
                    $apply_renewal 		= "";
					$payment_deatils	= "Payment details";
					$upload_application = 	"Upload CAF";
					$pay_now			= 	"Pay fees";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
				}
				if($details->plan_approve_status == 'I'){
					$status = '<b class="text-green">Issued</b>';
					//$link = $preview_link.'<br>'.$dwnld_cert.'<br>'.$dwnld_plan.'<br>'.$view_remarks.'<br/>'.$apply_registration.'<br/>'.$apply_extension;
					$link	 	= l(' View', 'applicant/application_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				$registration_number = !empty($details->factory_registrstion_no)?$details->factory_registrstion_no:$details->backlog_registration_no;
				if(empty($registration_number)){
					  $apply_registration	= l(' Apply Registration', 'apply-eservice-registration/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}else{
					$apply_registration = "Apply Registration";
					if($details->tm_migrated_flag =='N'){
				$apply_renewal = l('Apply for Renewal', 'apply-eservice-registration-renewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				}else{
					$apply_renewal = l('Apply for Renewal', 'apply-eservice-backlogrenewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				}
					$apply_amendment    = l('Apply for amendment', 'applicant/change-list-amendment/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','amend'), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				
				}
				  

				$apply_extension	= l('Apply for Extension of Plan', 'apply-eservice-extension/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
                    $apply_renewal 		= "";
					$payment_deatils	= "Payment details";
					$upload_application = 	"Upload CAF";
					$pay_now			= 	"Pay fees";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= "";
					$repayment			= "Repayment Request"; 
					$reg_down			= "Registration certificates";
					$lic_down			= "Download License";
					$apply_renewal		= "Apply Renewal of license";
					$apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					/******** ADDED BY SUBHAMAY **************************************************************************************/
					if($details->tm_migrated_flag!='N')
					{
					//	echo 'LLLL'.$details->approve_dsc_reg_file;
				
					$dwnld_cert = l(' Plan Approval Cert.',$base_url.'/feesmigrate/display-file/'.$details->backlog_uploaded_letter,array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank','class'=>array('text-blue'))));
					$dwnld_plan = l(' Download Plan',$base_url.'/feesmigrate/display-file/'.$details->backlog_uploaded_plan,array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_BLANK')));	
				} 
				else
				{
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					
					//$get_dwnld_cert = get_uploaded_document_url($details->uploaded_letter);
					//$dwnld_cert = l('<i class="fa fa-download" aria-hidden="true"></i> Plan Approval Cert.',file_create_url($get_dwnld_cert),array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank','class'=>array('text-blue'))));
					
					//$dwnld_cert	= l(' Plan Approval Cert', 'document-list/download-plan-approval-certificate/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','APPROVAL LETTER'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					

					//$get_dwnld_plan = get_uploaded_document_url($details->uploaded_plan);
					//$dwnld_plan = l('<i class="fa fa-download" aria-hidden="true"></i> Download Plan',file_create_url($get_dwnld_plan),array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_BLANK')));
					//$dwnld_plan	= l('Download Plan', 'document-list/download-site-plan/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','FACTORY PLAN'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));

				}
				/******** ENDED BY SUBHAMAY *************************************************************************************/
				}
				$Identification = $details->plan_approve_identification_number;
					if(empty($Identification)){
						$Identification = 'Under Process';
					}
			}
			
			if($details->service_id == '5'){
				$view_link			= "";
			$license_validty 	= "";
				$apply_amendment 	= "";
   				$apply_renewal 		= "";
				$pay_now			= 	"Pay fees";
				$pdf_link			=	"";
				$view_link			=	"";
				$edit_link			= 	"";
				$upload_application = 	"Upload CAF";
				$ack_link			= 	"";
				$repayment			= "Repayment Request"; 
				$genare_status   	= $details->plan_approve_status;
				$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				//$dwnld_cert			= "Plan Approval Certificaties";
				//$dwnld_plan			="Approved Plan";
				//$reg_down			= "registration certificates";
				//$lic_down			= "License";
				$apply_renewal		= "Apply Renewal of license";
				$apply_amendment	= "Apply Amendment of license";
				$apply_plan			= "Apply for Plan"; 		
				$pdf_link		 = l('<i class="ace-icon fa fa-file-pdf-o bigger-130 text-blue"></i> Pdf', 'download-pdf-new-plan/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'Download PDF', 'class'=>array(''))));
				$edit_link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> Edit', 'applicant/caf_extn/plan_extension/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array(''))));
				$preview_link	 = l('<i class="fa fa-eye" aria-hidden="true"></i> View', 'applicant/application_view_extension/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				$view_dwnld_link	 = l('<i class="fa fa-eye" aria-hidden="true"></i> View & Donwload PDF', 'applicant/application_view_extension/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				$upload_link	 = l('<i class="fa fa-upload" aria-hidden="true"></i> Upload Form', 'applicant/application_upload_extension/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				
			
				$dwnld_cert	= l('<i class="fa fa-download" aria-hidden="true"></i> Plan Approval Cert', 'document-list/download-plan-approval-certificate/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','APPROVAL LETTER'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));

				
				
				$dwnld_plan	= l('<i class="fa fa-download" aria-hidden="true"></i> Download Plan', 'document-list/download-site-plan/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','FACTORY PLAN'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));

				$view_remarks	= l('<i class="fa fa-eye" aria-hidden="true"></i> View Remarks', 'applicant/remarks_view_extension/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				
				$view_log	 	= l('Application Log', 'view-application-log/'.encryption_decryption_fun('encrypt',$details->id), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));		

				if($details->plan_approve_status == 'In'){
					$status = '<b class="text-blue">Incomplete</b>';
					$link = $edit_link;
					$ack_link			= "Acknowledgement";
                    $apply_renewal 		= "";
					$pay_now			= 	"Pay fees";
					$upload_application = 	"Upload CAF";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					$payment_deatils	= "Payment details";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$apply_renewal		= "Apply Renewal of license";
				    $apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
						$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					
				}
				if($details->plan_approve_status == 'F'){
					$status = '<b>Application submitted</b>';
					$link = $preview_link;
					$ack_link			= "Acknowledgement";
                    $apply_renewal 		= "";
					$pay_now			= 	"Pay fees";
					$upload_application = 	$upload_link;
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					$payment_deatils	= "Payment details";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_renewal		= "Apply Renewal of license";
				    $apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
					
				}
				if($details->plan_approve_status == 'U'){
					$status = '<b>Application submitted</b>';
					$link = $preview_link;
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	
                    $apply_renewal 		= "";
					$pay_now			= 	"Pay fees";
					$upload_application = 	"Upload CAF";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					$payment_deatils	= "Payment details";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_renewal		= "Apply Renewal of license";
				    $apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				
				if($details->plan_approve_status == 'RS'){
					$status = '<b>Application submitted</b>';
					$link = $preview_link;
					$ack_link			= "Acknowledgement";
                    $apply_renewal 		= "";
					$pay_now			= 	"Pay fees";
					$upload_application = 	$upload_link;
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					$payment_deatils	= "Payment details";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					$lic_down			= "Download License";
					$apply_renewal		= "Apply Renewal of license";
				    $apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if($details->plan_approve_status == 'RSU'){
					$status = '<b>Application submitted</b>';
					$link = $preview_link;
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	
                    $apply_renewal 		= "";
					$pay_now			= 	"Pay fees";
					$upload_application = 	"Upload CAF";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					$payment_deatils	= "Payment details";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$apply_renewal		= "Apply Renewal of license";
				    $apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if($details->plan_approve_status == 'AI'){
					$status = '<b>Forwarded To Inspector</b>';
					$link = $preview_link;
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	
                    $apply_renewal 		= "";
					$pay_now			= 	"Pay fees";
					$upload_application = 	"Upload CAF";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					$payment_deatils	= "Payment details";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_renewal		= "Apply Renewal of license";
				    $apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if($details->plan_approve_status == 'AICh'){
					$status = '<b>Forwarded To Inspector Chemical</b>';
					$link = $preview_link;
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	
                    $apply_renewal 		= "";
					$pay_now			= 	"Pay fees";
					$upload_application = 	"Upload CAF";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					$payment_deatils	= "Payment details";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_renewal		= "Apply Renewal of license";
				    $apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if($details->plan_approve_status == 'DC'){
					$status = '<b>Forwarded To Dy.CIF</b>';
					$link = $preview_link;
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	
                    $apply_renewal 		= "";
					$pay_now			= 	"Pay fees";
					$upload_application = 	"Upload CAF";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					$payment_deatils	= "Payment details";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_renewal		= "Apply Renewal of license";
				    $apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if($details->plan_approve_status == 'DCCh'){
					$status = '<b>Forwarded To Dy.CIF Chemical</b>';
					$link = $preview_link;
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	
                    $apply_renewal 		= "";
					$pay_now			= 	"Pay fees";
					$upload_application = 	"Upload CAF";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					$payment_deatils	= "Payment details";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$apply_renewal		= "Apply Renewal of license";
				    $apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if($details->plan_approve_status == 'JC'){
					$status = '<b>Forwarded To Jt.CIF</b>';
					$link = $preview_link;
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	
                    $apply_renewal 		= "";
					$pay_now			= 	"Pay fees";
					$upload_application = 	"Upload CAF";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					$payment_deatils	= "Payment details";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_renewal		= "Apply Renewal of license";
				    $apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if($details->plan_approve_status == 'C'){
					$status = '<b>Forwarded To CIF</b>';
					$link = $preview_link;
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	
                    $apply_renewal 		= "";
					$pay_now			= 	"Pay fees";
					$upload_application = 	"Upload CAF";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					$payment_deatils	= "Payment details";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_renewal		= "Apply Renewal of license";
				    $apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if($details->plan_approve_status == 'JCBk'){
					$status = '<b>Backed To Jt.CIF</b>';
					$link = $preview_link;
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	
                    $apply_renewal 		= "";
					$pay_now			= 	"Pay fees";
					$upload_application = 	"Upload CAF";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					$payment_deatils	= "Payment details";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_renewal		= "Apply Renewal of license";
				    $apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if($details->plan_approve_status == 'DCBk'){
					$status = '<b>Backed To Dy.CIF</b>';
					$link = $preview_link;
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	
                    $apply_renewal 		= "";
					$pay_now			= 	"Pay fees";
					$upload_application = 	"Upload CAF";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					$payment_deatils	= "Payment details";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_renewal		= "Apply Renewal of license";
				    $apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if($details->plan_approve_status == 'DCChBk'){
					$status = '<b>Backed To Dy.CIF Chemical</b>';
					$link = $preview_link;
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	
                    $apply_renewal 		= "";
					$pay_now			= 	"Pay fees";
					$upload_application = 	"Upload CAF";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					$payment_deatils	= "Payment details";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$lic_down			= "Download License";
					$apply_renewal		= "Apply Renewal of license";
				    $apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if($details->plan_approve_status == 'AIBk'){
					$status = '<b>Pending</b>';
					$link = $preview_link;
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	
                    $apply_renewal 		= "";
					$pay_now			= 	"Pay fees";
					$upload_application = 	"Upload CAF";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					$payment_deatils	= "Payment details";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$lic_down			= "Download License";
					$apply_renewal		= "Apply Renewal of license";
				    $apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if($details->plan_approve_status == 'AIChBk'){
					$status = '<b>Backed To Inspector Chemical</b>';
					$link = $preview_link;
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	
                    $apply_renewal 		= "";
					$pay_now			= 	"Pay fees";
					$upload_application = 	"Upload CAF";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					$payment_deatils	= "Payment details";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_renewal		= "Apply Renewal of license";
				    $apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if($details->plan_approve_status == 'ABk'){
					$status = '<b class="text-red">Backed To Applicant</b>';
					$link = $edit_link;
					//$link = $preview_link;
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	
                    $apply_renewal 		= "";
					$pay_now			= 	"Pay fees";
					$upload_application = 	"Upload CAF";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					$payment_deatils	= "Payment details";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_renewal		= "Apply Renewal of license";
				    $apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if($details->plan_approve_status == 'App'){
					$status = '<b class="text-green">Application Approved</b>';
					$link = $preview_link;
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	
                    $apply_renewal 		= "";
					$pay_now			= 	"Pay fees";
					$upload_application = 	"Upload CAF";
					$apply_amendment    = "";
					$reg_down 			= ""; 
					$lic_down			= ""; 
					$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					$apply_registration	="Apply Registration";
					$payment_deatils	= "Payment details";
					//$dwnld_cert			= "Plan Approval Certificaties";
					//$dwnld_plan			="Approved Plan";
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_renewal		= "Apply Renewal of license";
				    $apply_amendment	= "Apply Amendment of license";
					$apply_plan			= "Apply for Plan"; 		
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				if($details->plan_approve_status == 'I'){
					$status = '<b class="text-green">Approval of Plan Issued</b>';
					$link = $preview_link;
					$ack_link	= l('Acknowledgement', 'plan-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array('text-blue'),'style'=> 'margin-left:15px;'))).'<br>';	
                    $apply_renewal 		= "";
					$pay_now			= 	"Pay fees";
					$upload_application = 	"Upload CAF";
					$apply_amendment    = "";
				//	$reg_down 			= ""; 
					//$lic_down			= ""; 
				//	$amend_certificate	= ""; 
					$repayment			= "Repayment Request"; 
					$apply_extension 	= "";
					
					$payment_deatils	= "Payment details";
					
					//$reg_down			= "Registration certificates";
					//$lic_down			= "Download License";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_plan			= "Apply for Plan"; 		
					$registration_number = !empty($details->factory_registrstion_no)?$details->factory_registrstion_no:$details->backlog_registration_no;
					if(empty($registration_number)){
					  $apply_registration	= l(' Apply Registration', 'apply-eservice-registration/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}else{
					$apply_registration = "Apply Registration";
					if($details->tm_migrated_flag =='N'){
				$apply_renewal = l('Apply for Renewal', 'apply-eservice-registration-renewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				}else{
					$apply_renewal = l('Apply for Renewal', 'apply-eservice-backlogrenewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				}
					$apply_amendment    = l('Apply for amendment', 'applicant/change-list-amendment/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','amend'), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				
				}
				    
					$status_details	= l('Application Status detials', 'applicant/remarks_view/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));/******** ADDED BY SUBHAMAY **************************************************************************************/
					if($details->tm_migrated_flag!='N')
					{
					//	echo 'LLLL'.$details->approve_dsc_reg_file;
				
					$dwnld_cert = l(' Plan Approval Cert.',$base_url.'/feesmigrate/display-file/'.$details->backlog_uploaded_letter,array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank','class'=>array('text-blue'))));
					$dwnld_plan = l(' Download Plan',$base_url.'/feesmigrate/display-file/'.$details->backlog_uploaded_plan,array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_BLANK')));	
				} 
				else
				{
					//$get_dwnld_cert = get_uploaded_document_url($details->uploaded_letter);
					//$dwnld_cert = l('<i class="fa fa-download" aria-hidden="true"></i> Plan Approval Cert.',file_create_url($get_dwnld_cert),array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_blank','class'=>array('text-blue'))));
					
					//$dwnld_cert	= l(' Plan Approval Cert', 'document-list/download-plan-approval-certificate/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','APPROVAL LETTER'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					

					//$get_dwnld_plan = get_uploaded_document_url($details->uploaded_plan);
					//$dwnld_plan = l('<i class="fa fa-download" aria-hidden="true"></i> Download Plan',file_create_url($get_dwnld_plan),array('html' => TRUE,'attributes'=>array('title' => 'View','target'=>'_BLANK')));
					//$dwnld_plan	= l('Download Plan', 'document-list/download-site-plan/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','FACTORY PLAN'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));

				}
				/******** ENDED BY SUBHAMAY *************************************************************************************/
					
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
				$view_remarks	= l('Application Status detials', 'applicant/remark-view-application/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));	
			
				$view_link		= l('<i class="fa fa-eye" aria-hidden="true"></i> View', 'applicant/application-display-registration/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''))));
				
				$view_log	 	= l('Application Log', 'view-application-log/'.encryption_decryption_fun('encrypt',$details->id), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));		
					
					$edit_link		= l('<i class="fa fa-edit" aria-hidden="true"></i> Edit','applicant/caf-reg/registration-license/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number),array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array('')))) ;
			
					
				$Identification = $details->factory_reg_identification_number;	
				if(empty($Identification)){
					$Identification = 'Under Process';
				}
				
				$approve_dsc_reg_file_id		= 	$details->approve_dsc_reg_file_id;
				$approve_dsc_licence_file_id	= 	$details->approve_dsc_licence_file_id;
				$dsc_licence_register_file		= 	$details->approve_dsc_reg_licence_file_id;
				$period_for_application 		=	$details->period_for_application;
			
				
				if($details->application_status == 'In'){
							$status 			= '<b style="color:#0D67A2;">Incomplete</b>';
							$link 				= $edit_link;
							$apply_renewal 		= 'Apply for Renewal';
							$payment_deatils	= 'Payment Details';
							$ack_link			= 'Ack';
							$upload_application = 'Upload CAF';
							$pay_now			= 'Pay now';
							$apply_amendment    = 'Amendment for License';
							//$reg_down 			= "Registration certificate"; 
						//	$lic_down			= "Licence Certificate"; 
							//$amend_certificate	= "Amendment Certificate"; 
							$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
							$status_details		= 'Application Status Details';
							$apply_registration	="Apply Registration";
							$apply_extension	 ="Apply for Extension of Plan";
							$apply_plan			= "Apply for Plan"; 
							$repayment			= 'Repayment request'	;
							$ack_link			= "Acknowledgement";
				}
				if($details->application_status == 'F'){
					$status 	= '<b style="color:#0D67A2;">Fees pending</b>';
					$link 		= $view_link;
					$pay_now 	= l('Pay Now', 'applicant/fees_registration/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
						$apply_renewal 		= 'Apply for Renewal';
						$payment_deatils	= 'Payment Details';
						$ack_link			= "Acknowledgement";
						$upload_application = "Upload CAF";
						$repayment			= 'Re-payment' ;
						//$reg_down			= 'Registration Certificate';
						//$lic_down			= 'Licence Certificate';
						$apply_amendment    = 'Amendment for License';
						//$amend_certificate	= "Amendment Certificate";
						$status_details		= $view_remarks; 
						$apply_registration	="Apply Registration";
						$apply_extension	 ="Apply for Extension of Plan";
						$apply_plan			= "Apply for Plan"; 		
						$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				 
				}
				if($details->application_status == 'P'){
					$status 			= '<b style="color:#0D67A2;">Fees paid</b>';
					$link 				= $view_link;
					$apply_renewal 		= 'Apply for Renewal';
					$payment_deatils	= 'Payment Details';
					$ack_link			= "Acknowledgement";
					$upload_application = "Upload CAF";
					$pay_now			= "Pay now";
					$repayment			= 'Re-payment' ;
					//$reg_down			= 'Registration Certificate';
					//$lic_down			= 'Licence Certificate';
					$apply_amendment    = 'Amendment for License';
					//$amend_certificate	= "Amendment Certificate"; 
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$apply_plan			= "Apply for Plan"; 
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));		
					$payment_deatils = l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$upload_application =l('Upload CAF', 'applicant/uplaod-application-from/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array('')))); 
				}
				if($details->application_status == 'RS'){
					$status 			= '<b style="color:#0D67A2;">Application Re-submitted</b>';
					$link 				= $view_link;
					$upload_application = l('Upload CAF', 'applicant/uplaod-application-from/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array('')))); 
					$apply_renewal 		= 'Apply for Renewal';
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link			= 'Ack';
					$repayment			= 'Re-payment' ;
					$pay_now			= "Pay now";
					//$reg_down			= 'Registration Certificate';
					//$lic_down			= 'Licence Certificate';
					$apply_amendment    = 'Amendment for License';
					//$amend_certificate	= "Amendment Certificate";
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$apply_plan			= "Apply for Plan"; 
					$ack_link			= "Acknowledgement";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));		
				} 
				if($details->application_status == 'U'){
					$status 			= '<b style="color:#0D67A2;">Application Submitted</b>';
					$link 				= $view_link;
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link 			= l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$apply_renewal 		= 'Apply for Renewal';
					$repayment			= 'Re-payment' ;
					$upload_application = "Upload CAF";
					$pay_now			= "Pay now";
					//$reg_down			= 'Registration Certificate';
					//$lic_down			= 'Licence Certificate';
					$apply_amendment    = 'Amendment for License';
					$amend_certificate	= "Amendment Certificate"; 
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$apply_plan			= "Apply for Plan"; 
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));		
				}
				 
				if($details->application_status == 'B'){
					$status 			= '<b style="color:#0D67A2;">Back for rectification</b>';
					$link 				= $edit_link;
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link			= "Acknowledgement";
					$repayment			= 'Re-payment' ;
					//$reg_down			= 'Registration Certificate';
					//$lic_down			= 'Licence Certificate';
					$apply_amendment    = 'Apply for Amendment';
					//$amend_certificate	= "Amendment Certificate"; 
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$apply_plan			= "Apply for Plan"; 
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));		
				}
				if($details->application_status == 'R'){
					$status 			= '<b style="color:red;">Application Rejected.</b>';
					$link 				= $view_link;
					$repayment			= 'Re-payment' ;
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link 			= l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$apply_renewal 		= 'Apply for Renewal';
					$upload_application = "Upload CAF";
					//$reg_down 			= "Registration certificate"; 
					//$lic_down			= "Licence Certificate"; 
					//$amend_certificate	= "Amendment Certificate"; 
					$pay_now			= "Pay now";
					$apply_amendment    = 'Amendment for License';
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$apply_plan			= "Apply for Plan"; 
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));		
				}
				if($details->application_status == 'DC'){
					$status 			= '<b style="color:#0D67A2;">Forwarded To Dy. CIF</b>';
					$link 				= $view_link;
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link 			= l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$apply_renewal 		= 'Apply for Renewal';
					$repayment			= 'Re-payment' ;
					$upload_application ="Upload CAF";
					$pay_now			="Pay now";
					//$reg_down			= 'Registration Certificate';
					//$lic_down			= 'Licence Certificate';
					$apply_amendment    = 'Amendment for License';
					//$amend_certificate	= "Amendment Certificate"; 
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$apply_plan			= "Apply for Plan";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array('')))); 		
				}
			if($details->application_status == 'JC'){
					$status 			= '<b style="color:#0D67A2;">Forwarded To Jt. CIF</b>';
					$link 				= $view_link;
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link = l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$apply_renewal 		= 'Apply for Renewal';
					$upload_application ="Upload CAF";
					$pay_now			="Pay now";
					$repayment			= 'Re-payment';
					//$reg_down			= 'Registration Certificate';
					//$lic_down			= 'Licence Certificate';
					$apply_amendment    = 'Amendment for License';
					//$amend_certificate	= "Amendment Certificate";
					$status_details		= $view_remarks; 
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$apply_plan			= "Apply for Plan"; 
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));		
					
				 }
				 
			 
				 
			if($details->application_status == 'JCBk'){
					$status = '<b style="color:#0D67A2;">Backed To Jt. CIF</b>';
					$link = $view_link;
					$reg_down			= 'Registration Certificate';
					$lic_down			= 'Licence Certificate';
					$payment_deatils = l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link = l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$apply_renewal 		= 'Apply for Renewal';
						
					$upload_application = "Upload CAF";
					$pay_now			= "Pay now";
					$repayment			= 'Re-payment' ;
					$apply_amendment    = 'Amendment for License'; 
					//$amend_certificate	= "Amendment Certificate"; 
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$apply_plan			= "Apply for Plan"; 
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));		
				}
			if($details->application_status == 'DCBk'){
					$status = '<b style="color:#0D67A2;">Backed To Dy. CIF</b>';
					$link = $view_link;
					//$reg_down			= 'Registration Certificate';
					//$lic_down			= 'Licence Certificate';
					
					$payment_deatils = l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link = l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$apply_renewal 		= 'Apply for Renewal';
					//$amend_certificate	= "Amendment Certificate"; 
					$upload_application ="Upload CAF";
					$pay_now			="Pay now";
					$repayment			= 'Re-payment' ;
					$apply_amendment    = 'Amendment for License';
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$apply_plan			= "Apply for Plan"; 
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));		
					
				}
			if($details->application_status == 'I'){
				$status 			= '<b style="color:Green;">Issued</b>';
				$link 				= $view_link;
				$upload_application = "Upload CAF";
				$pay_now			= "Pay now";
				$repayment			= 'Re-payment';
				$amend_certificate	= "Amendment Certificate";
				$status_details		= $view_remarks;
				$apply_registration	="Apply Registration";
				$ack_link			= "Acknowledgement";
				
				$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				$ack_link = l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				if($details->tm_migrated_flag =='N'){
				$apply_renewal = l('Apply for Renewal', 'apply-eservice-registration-renewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				}else{
					$apply_renewal = l('Apply for Renewal', 'apply-eservice-backlogrenewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				}
				
				
				
				$license_validty = !empty($details->license_valid_upto)?'<span style="color:red">Expire Date:-'.date('dS M Y', strtotime($details->license_valid_upto)).'</span>':"";
				$apply_amendment    = l('Apply for amendment', 'applicant/change-list-amendment/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','amend'), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				/*if($details->license_valid_upto > date('Y-m-d')){
					$apply_amendment    = l('Apply for amendment', 'applicant/change-list-amendment/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','amend'), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				}else{
					$apply_amendment	= 'Apply for amendment';
				}*/
				/******** ADDED BY SUBHAMAY **************************************************************************************/
				 if($details->tm_migrated_flag!='N')
				 	{
					// $reg_down	= l('Registration Certificate', $base_url.'/sites/default/files/uploads/factory_cert/'.$details->approve_dsc_reg_file, array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array(''))));
					//$lic_down	= l('Licence Certificate',$base_url.'/sites/default/files/uploads/factory_cert/'.$details->approve_dsc_licence_file, array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array(''))));
				
				    	$reg_down	= l('Registration Certificate', $base_url.'/feesmigrate/display-file/'.$details->approve_dsc_reg_file, array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array(''))));
						$lic_down	= l('Licence Certificate',$base_url.'/feesmigrate/display-file/'.$details->approve_dsc_licence_file, array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array(''))));
				
					}else{
						//$reg_down	= l('Registration Certificate', 'document-list/download-registration-file/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','REG'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
						//$lic_down	= l('Licence Certificate','document-list/download-license-file/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','lic_certificate'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));	
						
					}
				/******** ENDED BY SUBHAMAY *************************************************************************************/
				$plan_approval = !empty($details->factory_plan_approval_number)?$details->factory_plan_approval_number:$details->backlog_plan_approval_no;
				if(empty($plan_approval)){
					$apply_plan	= l(' Apply for Plan', 'apply-eservice-plan-extension-forall/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','4'), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}else{
					$apply_extension	= l(' Apply for Extension of Plan', 'apply-eservice-plan-extension-forall/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','5'), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
				
				
				}
				
			if($details->application_status == 'RP'){				
					$status 			= '<b style="color:Green;">Request for Re-payment</b>';
					$link 				= $view_link;
					$repayment			= l('<i class="fa fa-edit" aria-hidden="true"></i> Re-payment','applicant/re-payment/power-details/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number),array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array('')))) ;
					$upload_application ="Upload CAF";	
					$apply_renewal 		= 'Apply for Renewal';
					$upload_application = "Upload CAF";
					$pay_now			= "Pay now";
					$apply_amendment    = 'Apply for amendment';
					//$amend_certificate	= "Amendment Certificate"; 
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$apply_plan	= "Apply for Plan";
					$ack_link			= "Acknowledgement";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				}
			if($details->application_status == 'RT'){
					$status 		= '<b style="color:#0D67A2;">Repayment Successful</b>';
					$link 			= $view_link;
					$payment_deatils = l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$upload_application =l('Upload CAF', 'applicant/uplaod-application-from/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array('')))); 
					$apply_renewal 		= 'Apply for Renewal';
					$upload_application = "Upload CAF";
					$pay_now			= "Pay now";
					$repayment			= 'Re-payment' ;
					$apply_amendment    = 'Amendment for License';
					$amend_certificate	= "Amendment Certificate"; 
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$apply_plan	= "Apply for Plan";
					$ack_link			= "Acknowledgement";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					
				 }
			
			}
			
			if($details->service_id == '3'){//echo $details->application_status;die;
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
				$apply_registration	="Apply Registration";
				$apply_extension	 ="Apply for Extension of Plan";
				$apply_plan	= "Apply for Plan";
				$view_log	 		= l('Application Log', 'view-application-log/'.encryption_decryption_fun('encrypt',$details->id), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));		
				
					if($details->tm_migrated_flag =='S'){
					$edit_link = l('Edit','applicant/caf-online-backrenew/default/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number),array('html' => TRUE,'attributes'=>array('title' => 'Edit'))) ;
					
				//$payment_deatils = l('Payment Details', 'applicant/caf-online-backrenew/default/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));	
					
				}if($details->tm_migrated_flag =='N'){
					$edit_link = l('Edit','applicant/caf-online-renew/apply-online-renewal-service/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number),array('html' => TRUE,'attributes'=>array('title' => 'Edit'))) ;
				}
					
					
						$view_link		= l('<i class="fa fa-eye" aria-hidden="true"></i> View', 'applicant/application-display-registration/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''))));
					$view_remarks	= l('Application Status detials', 'applicant/remark-view-application/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));	
				
				if($details->application_status == 'I'){
					$status 			= '<b style="color:Green;">Issued</b>';
					$link 				= $view_link;
					$upload_application = 'Upload Application';
					$apply_amendment    = 'Apply for Amendment';
					$pay_now			= "Pay now";
					$repayment			= 'Re-payment';
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$ack_link			= "Acknowledgement";
					$apply_extension	= l(' Apply for Extension of Plan', 'apply-eservice-plan-extension-forall/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','5'), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
					if($details->tm_migrated_flag =='N'){
						$apply_renewal = l('Apply for Renewal', 'apply-eservice-registration-renewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					}else{
						$apply_renewal = l('Apply for Renewal', 'apply-eservice-backlogrenewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					}
					$plan_approval = !empty($details->factory_plan_approval_number)?$details->factory_plan_approval_number:$details->backlog_plan_approval_no;	
					if(empty($plan_approval)){
						$apply_plan	= l(' Apply for Plan', 'apply-eservice-plan-extension-forall/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','4'), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
					}else{
						$apply_extension	= l(' Apply for Extension of Plan', 'apply-eservice-plan-extension-forall/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','5'), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
					}
					
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview')));
					$ack_link 			= l('Acknowledgment', 'applicant/renewal-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					
					 if($details->tm_migrated_flag!='N')
				     {
					 $reg_down	= l('Registration Certificate', $base_url.'/feesmigrate/display-file/'.$details->approve_dsc_reg_file, array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array(''))));
					$lic_down	= l('Licence Certificate',$base_url.'/feesmigrate/display-file/'.$details->approve_dsc_licence_file, array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array(''))));
				     }
					 else
					 {
						//$reg_down	= l('Registration Certificate', 'document-list/download-registration-file/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','REG'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					//	$lic_down	= l('Licence Certificate','document-list/download-license-file/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','LIC'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					 }
					 
					//$amend_certificate	= l('Amendment cetificate', file_create_url(get_uploaded_document_url($details->approve_amendment_file_id)), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array(''))));
					
					
					$license_validty 	= !empty($details->license_valid_upto)?'<span style="color:red">Expire Date:-'.date('dS M Y', strtotime($details->license_valid_upto)).'</span>':"";
					if($details->license_valid_upto > date('Y-m-d')){
					$apply_amendment    = l('Apply for Amendment', 'applicant/change-list-amendment/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','amend'), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				}else{
						$apply_amendment	= 'Apply for Amendment';
					}
					
				}
				//echo $details->application_status.'---'.$details->renewal_dim_appoved;die;
				if($details->application_status == 'I' && $details->renewal_dim_appoved == 1){
					$status 			= '<b style="color:Green;">Issued</b>';
					$link 				= $view_link;
					$upload_application = 'Upload Application';
					$apply_amendment    = 'Apply for Amendment';
					$pay_now			= "Pay now";
					$repayment			= 'Re-payment';
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$ack_link			= "Acknowledgement";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					//$amend_certificate	= l('Amendment cetificate', file_create_url(get_uploaded_document_url($details->approve_amendment_file_id)), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array(''))));
					
					
					 if($details->tm_migrated_flag!='N')
				     {
					 $reg_down	= l('Registration Certificate', $base_url.'/feesmigrate/display-file/'.$details->approve_dsc_reg_file, array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array(''))));
					$lic_down	= l('Licence Certificate',$base_url.'/feesmigrate/display-file/'.$details->approve_dsc_licence_file, array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array(''))));
				     }else{
					
						//$reg_down	= l('Registration Certificate', 'document-list/download-registration-file/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','REG'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
						//$lic_down	= l('Licence Certificate','document-list/download-license-file/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','LIC'), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				
						
						//$lic_down	= l('Licence Certificate','regsection/registration-licence-genarate-file/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number),array('html' => TRUE,'attributes'=>array('target' => '_BLANK','title' => 'Download Licence Certificate')));
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));	
						
					 }
					$plan_approval = !empty($details->factory_plan_approval_number)?$details->factory_plan_approval_number:$details->backlog_plan_approval_no;
if(empty($plan_approval)){
					$apply_plan	= l(' Apply for Plan', 'apply-eservice-plan-extension-forall/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','4'), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}else{
					$apply_extension	= l(' Apply for Extension of Plan', 'apply-eservice-plan-extension-forall/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','5'), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
					 
					$license_validty = !empty($details->license_valid_upto)?'<span style="color:red">Expire Date:-'.date('dS M Y', strtotime($details->license_valid_upto)).'</span>':"";
					$apply_renewal 		= l('Apply for Renewal', 'apply-eservice-registration-renewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview')));
					$ack_link 			= l('Acknowledgment', 'applicant/renewal-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					
					if($details->license_valid_upto > date('Y-m-d')){
					$apply_amendment    = l('Apply for Amendment', 'applicant/change-list-amendment/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','amend'), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				}else{
						$apply_amendment	= 'Apply for Amendment';
					}
				}
		 	
				if($details->application_status == 'In' && $details->renewal_dim_appoved == 1){
					if($details->tm_migrated_flag =='N'){
						$edit_link		= l('<i class="fa fa-edit" aria-hidden="true"></i> Edit','applicant/change-list-amendment-dashboard/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number),array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array('')))) ;	
					}
					if($details->tm_migrated_flag =='S'){
						$edit_link = l('Edit','applicant/caf-online-renew/details-worker-renewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number),array('html' => TRUE,'attributes'=>array('title' => 'Edit'))) ;
					}
					
					$view_remarks	= l('Application Status detials', 'applicant/remark-view-application/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));	
					 $status 				= '<b style="color:#0D67A2;">Under Process</b>';
					 $status 				= '<b style="color:#0D67A2;">Under Process</b>';
					 $link 					= $edit_link;
					 $pay_now				= 'Pay now';
					 $ack_link  			= 'Acknowledgment';
					 $upload_application 	= 'Upload Application';
					 $payment_deatils 		= 'Payment details';
					 $apply_renewal 		= 'Apply for Renewal';
					 $repayment				= 'Re-payment' ;
					 $reg_down 				= '';
					 $lic_down				= '';
					 $apply_amendment    	= '';
					 $amend_certificate		= '';
					 $status_details		= $view_remarks;
					 $apply_registration	="Apply Registration";
					 $apply_extension	 ="Apply for Extension of Plan";
					 $plan_approval	 	="Apply for  Plan";
					 $download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				 }
				 if($details->application_status == 'In'   && $details->renewal_dim_appoved != 1){
					if($details->tm_migrated_flag =='N'){
						$edit_link		= l('<i class="fa fa-edit" aria-hidden="true"></i> Edit','applicant/change-list-amendment-dashboard/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number),array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array('')))) ;	
					}
					if($details->tm_migrated_flag =='S'){
						$edit_link = l('Edit','applicant/caf-online-backrenew/details-worker-renewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number),array('html' => TRUE,'attributes'=>array('title' => 'Edit'))) ;
					}

					
					 $view_remarks	= l('Application Status detials', 'applicant/remark-view-application/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));	
					 $status 				= '<b style="color:#0D67A2;">Under Process</b>';
					 $link 					= $edit_link;
					 $pay_now				= 'Pay now';
					 $ack_link  			= 'Acknowledgment';
					 $upload_application 	= 'Upload Application';
					 $payment_deatils 		= 'Payment details';
					 $apply_renewal 		= 'Apply for Renewal';
					 $repayment				= 'Re-payment' ;
					// $reg_down 				= '';
					// $lic_down				= '';
					 $apply_amendment    	= '';
					 //$amend_certificate		= '';
					 $status_details		= $view_remarks;
					 $apply_registration	="Apply Registration";
					 $apply_extension	 ="Apply for Extension of Plan";
					 $plan_approval	 	="Apply for  Plan";
					 $download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				 }
				if($details->application_status == 'F' && $details->renewal_dim_appoved == 1){
					$status 				= '<b style="color:#0D67A2;">Fees pending</b>';
					$link 					= $view_link;
					$ack_link  				= 'Acknowledgment';
					$upload_application 	= 'Upload Application';
					$payment_deatils 		= 'Payment details';
					$apply_amendment    	= 'Apply for Amendment';
					$apply_renewal 			= 'Apply for Renewal';
					$repayment				= 'Re-payment' ;
					//$reg_down 				= '';
					//$lic_down				= '';
					//$amend_certificate		= ''; 
					$status_details		= $view_remarks;
					$apply_extension	 ="Apply for Extension of Plan";
					$plan_approval	 	="Apply for  Plan";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$pay_now 				= l('Pay Now', 'applicant/fees-renewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));  
				}
				if($details->application_status == 'F' && $details->renewal_dim_appoved == 0){
					$status 				= '<b style="color:#0D67A2;">Fees pending</b>';
					$link 					= $view_link;
					$ack_link  				= 'Acknowledgment';
					$upload_application 	= 'Upload Application';
					$payment_deatils 		= 'Payment details';
					$apply_amendment    	= 'Apply for Amendment';
					$apply_renewal 			= 'Apply for Renewal';
					$repayment				= 'Re-payment' ;
					////$reg_down 				= '';
					//$lic_down				= '';
					//$amend_certificate		= '';
					$status_details		= $view_remarks; 
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$plan_approval	 	="Apply for  Plan";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$pay_now 				= l('Pay Now', 'applicant/fees-renewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));  
				}
				
				if($details->application_status == 'P' && $details->renewal_dim_appoved == 1){
					$status 			= '<b style="color:#0D67A2;">Fees paid</b>';
					$link 				= $view_link;
					$ack_link 	 		= 'Acknowledgment';
					$upload_application = 'Upload Application';
					$pay_now 			= 'Pay Now';
					//$lic_down			= 'Download License';
					$apply_renewal 		= 'Apply for Renewal';
					$repayment			= 'Re-payment' ;
					$apply_amendment    = 'Apply for Amendment';
					$amend_certificate	= 'Amendment cetificate'; 
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$plan_approval	 	="Apply for  Plan";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$upload_application = l('Upload CAF', 'applicant/upload-application-renewal-form/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview'))); 
				 }
				 if($details->application_status == 'P' && $details->renewal_dim_appoved == 0){
					$status 			= '<b style="color:#0D67A2;">Fees paid</b>';
					$link 				= $view_link;
					$ack_link 	 		= 'Acknowledgment';
					$upload_application = 'Upload Application';
					$pay_now 			= 'Pay Now';
					//$lic_down			= 'Download License';
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$apply_renewal 		= 'Apply for Renewal';
					$repayment			= 'Re-payment' ;
					$apply_amendment    = 'Apply for Amendment';
					//$amend_certificate	= 'Amendment cetificate'; 
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$plan_approval	 	="Apply for  Plan";
					$upload_application = l('Upload CAF', 'applicant/upload-application-renewal-form/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview'))); 
				 }
				if($details->application_status == 'RS'){
					$status 			= '<b style="color:#0D67A2;">Application Re-submitted</b>';
					$pay_now			= "";
					$link 				= $view_link;
					$upload_application = "";
					//$ack_link			= "";
					//$lic_down 	= "";
					$apply_amendment    = 'Apply for Amendment';
					//$amend_certificate	= 'Amendment cetificate'; 
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$plan_approval	 	="Apply for  Plan";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array('label label-info'))));
				 } 
				if($details->application_status == 'U'){
					$status 			= '<b style="color:#0D67A2;">Application Submitted</b>';
					$pay_now 			= "Pay now";
					$link 				= $view_link;
					$upload_application = "Upload Application from";
					//$lic_down 			= "License Certificates";
					$apply_amendment    = 'Apply for Amendment';
					$amend_certificate	= 'Amendment cetificate';
					$apply_renewal 		= 'Apply for Renewal';
					$repayment			= 'Re-payment' ;
					$reg_down			= 'Registration Certificate';
					$status_details		= $view_remarks; 
					$apply_extension	 ="Apply for Extension of Plan";
					$apply_registration	="Apply Registration";
					$plan_approval	 	="Apply for  Plan";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview')));
					$ack_link 			= l('Acknowledgment', 'applicant/renewal-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview')));
				}
				if($details->application_status == 'B'){
					$status 			= '<b style="color:#0D67A2;">Application Backed.</b>';
					$link 				= $edit_link;
					$pay_now 			= "";
					$ack_link 			= "";
					//$lic_down 	= "";
					$apply_amendment    = 'Apply for Amendment';
					$amend_certificate	= 'Amendment cetificate';
					$status_details		= $view_remarks; 
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$plan_approval	 	="Apply for  Plan";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array('label label-info'))));
				 }
				if($details->application_status == 'R'){
					$status 			= '<b style="color:red;">Application Rejected.</b>';
					$link 				= $view_link;
					$pay_now 			= "";
					$upload_application = "";
					$ack_link 			= "";
					//$lic_down 	= "";
					$apply_amendment    = 'Apply for Amendment';
					$amend_certificate	= 'Amendment cetificate';
					$status_details		= $view_remarks; 
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$plan_approval	 	="Apply for  Plan";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array('label label-info'))));
				}
				if($details->application_status == 'DC'){
					$status 			= '<b style="color:#0D67A2;">Forwarded to Deputy Director</b>';
					$link 				= $view_link.'<br/>';
					$pay_now 			= "";
				 	$ack_link 			= "";
					$lic_down 	= "";
					$apply_amendment    = 'Apply for Amendment';
					//$amend_certificate	= 'Amendment cetificate'; 
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$plan_approval	 	="Apply for  Plan";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array('label label-info'))));
				 }
				if($details->application_status == 'RP'){
					$status 			= '<b style="color:Green;">Re-payment</b>';
					$link 				= $view_link;
					$pay_now			= "";
					//$ack_link			= "";
					//$lic_down 	= "";
					$apply_amendment    = 'Apply for Amendment';
					$amend_certificate	= 'Amendment cetificate';
					$status_details		= $view_remarks; 
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$plan_approval	 	="Apply for  Plan";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$repayment			= l('<i class="fa fa-edit" aria-hidden="true"></i> Re-payment','applicant/re-payment/power-details/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number),array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array('label label-info')))) ;
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array('label label-info'))));
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
					
			$view_log	 	= l('Application Log', 'view-application-log/'.encryption_decryption_fun('encrypt',$details->id), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));		
				 	$view_link		= l('<i class="fa fa-eye" aria-hidden="true"></i> View', 'amendment/application-display-amendment/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''))));
				$view_remarks	= l('Application Status detials', 'applicant/remark-view-application/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));	
					
	
				
				
				$edit_link		= l('<i class="fa fa-edit" aria-hidden="true"></i> Edit','applicant/change-list-amendment-dashboard/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number),array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array('')))) ;	
			
			$approve_dsc_reg_file_id		= 	$details->approve_dsc_reg_file_id;
			$approve_dsc_licence_file_id	= 	$details->approve_dsc_licence_file_id;
			$dsc_licence_register_file		= 	$details->approve_dsc_reg_licence_file_id;
			$period_for_application 		=	$details->period_for_application;
			
			$license_validty = !empty($details->license_valid_upto)?'<span style="color:red">Expire Date:-'.date('dS M Y', strtotime($details->license_valid_upto)).'</span>':"";
			
			if($details->application_status == 'In'){
						
					 	$status 			= '<b style="color:#0D67A2;">Incomplete</b>';
					 	$link 				= $edit_link;
						$apply_renewal 		= 'Apply for Renewal';
						$payment_deatils	= 'Payment Details';
						$ack_link			= 'Ack';
						$upload_application = 'Upload CAF';
						$pay_now			= 'Pay now';
						//$reg_down			= 'Registration Certificate';
						//$lic_down			= 'Licence Certificate';
						$apply_amendment    = 'Amendment for License';
						$status_details		= 'Application Status Details';
						$apply_registration	="Apply Registration";
						$apply_extension	 ="Apply for Extension of Plan";
						$plan_approval	 	="Apply for  Plan";
						$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					
				 }
			if($details->application_status == 'F'){
					$status 	= '<b style="color:#0D67A2;">Fees pending</b>';
					$link 		= $view_link;
					$pay_now 	= l('Pay Now', 'amendment/fees-amendment/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
						$apply_renewal 		= 'Apply for Renewal';
						$payment_deatils	= 'Payment Details';
						$ack_link			= 'Ack';
						$upload_application = "Upload CAF";
						$repayment			= 'Re-payment' ;
						//$reg_down			= 'Registration Certificate';
						//$lic_down			= 'Licence Certificate';
						$apply_amendment    = 'Amendment for License';
						$status_details		= $view_remarks;
						$apply_registration	="Apply Registration";
						$apply_extension	 ="Apply for Extension of Plan";
						$plan_approval	 	="Apply for  Plan";
						$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
						
				 
				 }
			if($details->application_status == 'P'){
					$status = '<b style="color:#0D67A2;">Fees paid</b>';
					$link = $view_link;
						$apply_renewal 		= 'Apply for Renewal';
						$payment_deatils	= 'Payment Details';
						$ack_link			= 'Ack';
						$upload_application = "Upload CAF";
						$pay_now			= "Pay now";
						$repayment			= 'Re-payment' ;
						//$reg_down			= 'Registration Certificate';
						//$lic_down			= 'Licence Certificate';
						$apply_amendment    = 'Amendment for License';
						$status_details		= $view_remarks;
						$apply_registration	="Apply Registration";
						$apply_extension	 ="Apply for Extension of Plan";
						$plan_approval	 	="Apply for  Plan";
						$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$payment_deatils = l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$upload_application =l('Upload CAF', 'applicant/upload-amendment-from/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array('')))); 
			
			}
			
			if($details->application_status == 'RS'){
					$status = '<b style="color:#0D67A2;">Application Re-submitted</b>';
					$link = $view_link;
					$upload_application =l('Upload CAF', 'applicant/uplaod-application-from/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array('')))); 
						$apply_renewal 		= 'Apply for Renewal';
					$payment_deatils = l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
						$ack_link			= 'Ack';
						$repayment			= 'Re-payment' ;
						$pay_now			= "Pay now";
						//$reg_down			= 'Registration Certificate';
						//$lic_down			= 'Licence Certificate';
						$apply_amendment    = 'Amendment for License';
						$status_details		= $view_remarks;
						$apply_registration	="Apply Registration";
						$apply_extension	 ="Apply for Extension of Plan";
						$plan_approval	 	="Apply for  Plan";
						$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					
					
				 } 
			if($details->application_status == 'U'){
					$status = '<b style="color:#0D67A2;">Application Submitted</b>';
					$link = $view_link;
					$payment_deatils = l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link = l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
						$apply_renewal 		= 'Apply for Renewal';
						$repayment			= 'Re-payment' ;
						$upload_application = "Upload CAF";
						$pay_now			= "Pay now";
						//$reg_down			= 'Registration Certificate';
						//$lic_down			= 'Licence Certificate';
						$apply_amendment    = 'Amendment for License';
						$status_details		= $view_remarks;
						$apply_registration	="Apply Registration";
						$apply_extension	 ="Apply for Extension of Plan";
						$plan_approval	 	="Apply for  Plan";
						$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					
				 }
			if($details->application_status == 'APP'){
					$status = '<b style="color:#0D67A2;">Approved by Chief</b>';
					
					$link = $view_link;
					$payment_deatils = l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link = l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));	$apply_renewal 		= 'Apply for Renewal';
						
						$upload_application = "Upload CAF";
						$pay_now			= "Pay now";
						$repayment			= 'Re-payment' ;
						$apply_renewal 		= 'Apply for Renewal';
						$apply_amendment    = 'Amendment for License';
						$status_details		= $view_remarks;
						$apply_registration	="Apply Registration";
						$apply_extension	 ="Apply for Extension of Plan";
						$plan_approval	 	="Apply for  Plan";
						$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
						
				
					
			}
			if($details->application_status == 'APP-REG'){
						$status 			= '<b style="color:#0D67A2;">Registration Complet</b>';
						$pay_now			= "Pay now";
						$link 				= $view_link;
						
						$payment_deatils = l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link = l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link = l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));	$apply_renewal 		= 'Apply for Renewal';
						
					$upload_application ="Upload CAF";
					$pay_now			="Pay now";
					$apply_renewal 		= 'Apply for Renewal';
					$repayment			= 'Re-payment' ;
					$apply_amendment    = 'Amendment for License';
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$plan_approval	 	="Apply for  Plan";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				
				 }
			if($details->application_status == 'AI'){
					 $status 			= '<b style="color:#0D67A2;">Forwarded to Inspector</b>';
					 $link 				= $view_link;
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link 			= l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$apply_renewal 		= 'Apply for Renewal';
					$repayment			= 'Re-payment' ;
					$upload_application = "Upload CAF";
					$pay_now			= "Pay now";
					//$reg_down			= 'Registration Certificate';
					//$lic_down			= 'Licence Certificate';
					$apply_amendment    = 'Amendment for License';
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$plan_approval	 	="Apply for  Plan";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				 }
			if($details->application_status == 'ABk'){
					$status 			= '<b style="color:#0D67A2;">Backed to inspector</b>';
					$link 				= $view_link;
					$repayment			= 'Re-payment' ;
					$apply_renewal 		= 'Apply for Renewal';
					$upload_application = "Upload CAF";
					$pay_now			= "Pay now";
					//$reg_down			= 'Registration Certificate';
					//$lic_down			= 'Licence Certificate';
					$apply_amendment    = 'Amendment for License';
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$plan_approval	 	="Apply for  Plan";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link 			= l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''),'target' => '_blank')));
					$apply_extension	 ="Apply for Extension of Plan";
				 }
				 
			if($details->application_status == 'B'){
					$status = '<b style="color:#0D67A2;">Back for rectification</b>';
					$link = $edit_link;
					$payment_deatils = l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link = l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$repayment			= 'Re-payment' ;
					//$reg_down			= 'Registration Certificate';
					//$lic_down			= 'Licence Certificate';
					$apply_amendment    = 'Apply for Amendment';
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$plan_approval	 	="Apply for  Plan";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				 }
			if($details->application_status == 'R'){
					$status = '<b style="color:red;">Application Rejected.</b>';
					$link = $view_link;
					$repayment			= 'Re-payment' ;
					$payment_deatils = l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link = l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$apply_renewal 		= 'Apply for Renewal';
					$upload_application ="Upload CAF";
					$pay_now			="Pay now";
					$apply_amendment    = 'Amendment for License';
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$plan_approval	 	="Apply for  Plan";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				}
			if($details->application_status == 'DC'){
					$status = '<b style="color:#0D67A2;">Forwarded To Dy. CIF</b>';
					$link = $view_link;
					$payment_deatils = l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link = l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$apply_renewal 		= 'Apply for Renewal';
					$repayment			= 'Re-payment' ;
					$upload_application ="Upload CAF";
					$pay_now			="Pay now";
					//$reg_down			= 'Registration Certificate';
					//$lic_down			= 'Licence Certificate';
					$apply_amendment    = 'Amendment for License';
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$plan_approval	 	="Apply for  Plan";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				}
			if($details->application_status == 'JC'){
					$status = '<b style="color:#0D67A2;">Forwarded To Jt. CIF</b>';
					$link = $view_link;
					
					$payment_deatils = l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link = l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$apply_renewal 		= 'Apply for Renewal';
					$upload_application ="Upload CAF";
					$pay_now			="Pay now";
					$repayment			= 'Re-payment';
					//$reg_down			= 'Registration Certificate';
					//$lic_down			= 'Licence Certificate';
					$apply_amendment    = 'Amendment for License';
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$plan_approval	 	="Apply for  Plan";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					
				 }
				 
			if($details->application_status == 'JCBk'){
					$status = '<b style="color:#0D67A2;">Backed To Jt. CIF</b>';
					$link = $view_link;
					//$reg_down			= 'Registration Certificate';
					//$lic_down			= 'Licence Certificate';
					$payment_deatils = l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link = l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$apply_renewal 		= 'Apply for Renewal';
						
					$upload_application = "Upload CAF";
					$pay_now			= "Pay now";
					$repayment			= 'Re-payment' ;
					$apply_amendment    = 'Amendment for License'; 
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$plan_approval	 	="Apply for  Plan";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				}
			if($details->application_status == 'DCBk'){
					$status = '<b style="color:#0D67A2;">Backed To Dy. CIF</b>';
					$link = $view_link;
					//$reg_down			= 'Registration Certificate';
					//$lic_down			= 'Licence Certificate';
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					
					$payment_deatils = l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$ack_link = l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$apply_renewal 		= 'Apply for Renewal';
						
					$upload_application ="Upload CAF";
					$pay_now			="Pay now";
					$repayment			= 'Re-payment' ;
					$apply_amendment    = 'Amendment for License';
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					$plan_approval	 	="Apply for  Plan";
					
				}
			if($details->application_status == 'I'){
					$status 			= '<b style="color:Green;">Issued</b>';
					$link 				= $view_link;
					$upload_application = "Upload CAF";
					$pay_now			= "Pay now";
					$repayment			= 'Re-payment';
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
					
					
$plan_approval = !empty($details->factory_plan_approval_number)?$details->factory_plan_approval_number:$details->backlog_plan_approval_no;
if(empty($plan_approval)){
					$apply_plan	= l(' Apply for Plan', 'apply-eservice-plan-extension-forall/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','4'), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}else{
					$apply_extension	= l(' Apply for Extension of Plan', 'apply-eservice-plan-extension-forall/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','5'), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
					$payment_deatils 	= l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					
					$ack_link = l('Acknowledgment', 'registration-acknowledgement-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					
					
				if($details->tm_migrated_flag =='N'){
				$apply_renewal = l('Apply for Renewal', 'apply-eservice-registration-renewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				}else{
					$apply_renewal = l('Apply for Renewal', 'apply-eservice-backlogrenewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				}
					
					$license_validty = !empty($details->license_valid_upto)?'<span style="color:red">Expire Date:-'.date('dS M Y', strtotime($details->license_valid_upto)).'</span>':"";
					$apply_amendment    = l('Amendment for License', 'applicant/change-list-amendment/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','amend'), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					
					/******** ADDED BY SUBHAMAY **************************************************************************************/
				  if($details->tm_migrated_flag!='N')
					{
				//	echo 'LLLL'.$details->approve_dsc_reg_file;
				
					 $reg_down	= l('Registration Certificate', $base_url.'/feesmigrate/display-file/'.$details->approve_dsc_reg_file, array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array(''))));
					$lic_down	= l('Licence Certificate',$base_url.'/feesmigrate/display-file/'.$details->approve_dsc_licence_file, array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array(''))));	
					}else{
						$reg_down	= l('Registration Certificate', file_create_url(get_uploaded_document_url($details->approve_dsc_reg_file_id)), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array(''))));
					//	$lic_down	= l('Licence Certificate',file_create_url(get_uploaded_document_url($details->approve_dsc_licence_file_id)), array('html' => TRUE,'attributes'=>array('title' => 'View','class'=>array(''))));
						}
					/******** ENDED BY SUBHAMAY *************************************************************************************/
				}else{
					$download_certificates	= l('Download','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				}

			if($details->application_status == 'RP'){				
					$status 			= '<b style="color:Green;">Request for Re-payment</b>';
					$link 				= $view_link;
					$repayment			= l('<i class="fa fa-edit" aria-hidden="true"></i> Re-payment','applicant/re-payment/power-details/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number),array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array('')))) ;
					$upload_application ="Upload CAF";	
					$apply_renewal 		= 'Apply for Renewal';
					$upload_application = "Upload CAF";
					$pay_now			= "Pay now";
					$apply_amendment    = 'Amendment for License';
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
						$plan_approval	 	="Apply for  Plan";
						$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
				}
			if($details->application_status == 'RT'){
					$status = '<b style="color:#0D67A2;">Repayment Successful</b>';
					$link = $view_link;
					$payment_deatils = l('Payment Details', 'applicant/view-payment-breakup/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
					$upload_application =l('Upload CAF', 'applicant/uplaod-application-from/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array('')))); 
					$apply_renewal 		= 'Apply for Renewal';
					$upload_application ="Upload CAF";
					$pay_now			="Pay now";
					$repayment			= 'Re-payment' ;
					$apply_amendment    = 'Amendment for License';
					$status_details		= $view_remarks;
					$apply_registration	="Apply Registration";
					$apply_extension	 ="Apply for Extension of Plan";
						$plan_approval	 	="Apply for  Plan";
						$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					
				 }
				 
			$Identification = $details->factory_reg_identification_number;	
			if(empty($Identification)){
				  	$Identification = 'Under Process';
			 	}
		
				
			}
			
			if($details->service_id == '16'){
				if($details->application_status == 'In'){
						
					 $status 	= '<b style="color:#0D67A2;">Incomplete</b>';
					$edit_link = l('Edit','applicant/backlog-factory-add/default/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number),array('html' => TRUE,'attributes'=>array('title' => 'Edit'))) ;
					 	$link 				= $edit_link;
						$apply_renewal 		= 'Apply for Renewal';
						$payment_deatils	= 'Payment Details';
						$ack_link			= 'Acknowledgement';
						$upload_application = 'Upload CAF';
						$pay_now			= 'Pay now';
						$reg_down			= 'Registration Certificate';
						$lic_down			= 'Licence Certificate';
						$apply_amendment    = 'Amendment for License';
						$status_details		= 'Application Status Details';
						$apply_registration	="Apply Registration";
						$apply_extension	 ="Apply for Extension of Plan";
							$plan_approval	 	="Apply for  Plan";
					$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
					
				 }
				 if($details->application_status == 'A'){
						
					 $status 	= '<b style="color:#0D67A2;">Add new factory</b>';
					$view_link		= l('View', 'applicant/application-preview-renewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''))));
					
					if($details->tm_migrated_flag =='S'){
					$apply_renewal = l('Apply for Renewal', 'apply-eservice-backlogrenewal/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				}
					 	$link 				= $view_link;
						
						$payment_deatils	= 'Payment Details';
						$ack_link			= 'Acknowledgement';
						$upload_application = 'Upload CAF';
						$pay_now			= 'Pay now';
						$reg_down			= 'Registration Certificate';
						$lic_down			= 'Licence Certificate';
						$apply_amendment    = 'Amendment for License';
						$status_details		= 'Application Status Details';
						$apply_registration	="Apply Registration";
						$apply_extension	 ="Apply for Extension of Plan";
						$download_certificates	= l('Download Documents','certificates-document-list/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'target' => '_BLANK','class'=>array(''))));
						$plan_approval = !empty($details->factory_plan_approval_number)?$details->factory_plan_approval_number:$details->backlog_plan_approval_no;
if(empty($plan_approval)){
					$apply_plan	= l(' Apply for Plan', 'apply-eservice-plan-extension-forall/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','4'), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}else{
					$apply_extension	= l(' Apply for Extension of Plan', 'apply-eservice-plan-extension-forall/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt','5'), array('html' => TRUE,'attributes'=>array('title' => 'view', 'class'=>array(''))));
				}
					
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
					if($details->service_id == '16'){
						$plan_approval = 'Not Available';
					}else{
						$plan_approval = 'Not Available';
					}
					
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
			$license_date_exdate = !empty($details->license_valid_upto)?date('dS M Y', strtotime($details->license_valid_upto)):"";
			if(!empty($details->factory_license_no)){
				$license_number = $details->factory_license_no.'<b>,Dated on - </b>'.$license_date.'<br/><b><font color = "red">Expire Date:'.$license_date_exdate.'</font></b>';
			}else{
				if(!empty($details->backlog_license_number)){
					$license_date = !empty($details->backlog_license_date)?date('dS M Y', strtotime($details->backlog_license_date)):"";
						$license_number = $details->backlog_license_number.'<b>,Dated on - </b>'.$license_date.'<br/><b><font color = "red">Expire Date:'.$license_date_exdate.'</font></b>'; 
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
  $service_name = $details->service_name;
  if($details->service_id==16){
	  $service_name = 'Not Applicable';
	  $application_status = 'Not Applicable';
  }else{
	  $application_status = $Identification.'<br><b>Date - </b>'.$created_date;
  }		//die($details->license_valid_upto.'-----');
$modification_date = !empty($details->modification_date)?date('dS M Y', strtotime($details->modification_date)):'';

			
			$rows[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' =>$details_factor.'<br/><br/>'.$view_log,'class' => array('')),
							array('data' =>$service_name ,'class' => array('')),
							array('data' =>$application_status,'class' => array('')),
							array('data' =>$status.'<br/>'.$modification_date,'class' => array('')),
							array('data' =>$link.'('.$details->tm_factory_id.'---'.$details->tm_migrated_flag.')&nbsp;&nbsp;/'.$pay_now .'<br/>'.$upload_application.'&nbsp;&nbsp;/'.$payment_deatils.'<br/>'.$repayment.'&nbsp;&nbsp;/'.$ack_link.'<br/>'.$download_certificates.'&nbsp;&nbsp;/'.$apply_extension.'<br/>'.$apply_registration.'&nbsp;&nbsp;/'.$apply_renewal.'<br/>'.$apply_amendment.'&nbsp;&nbsp;/'.$status_details,'class' => array('')),
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