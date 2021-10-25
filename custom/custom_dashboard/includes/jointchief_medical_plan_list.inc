<?php
function jointchief_medical_plan_list($form, &$form_state) {
	global $base_root,$base_path,$user;

  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/sky-forms.css');
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	//drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	$form = array();
	
	$zoneUserMap = array();
	$zoneUserMapResult = getZoneUserMap($user->uid);
	if(!empty($zoneUserMapResult)){
		foreach($zoneUserMapResult as $v){
			$zoneUserMap[] = $v->zone_id;
		}
	}
	$zoneDropDown = array();
	$zoneDropDown[] = '-Select-';
	if(!empty($zoneUserMapResult)){
		foreach($zoneUserMapResult as $v){
			$zoneDropDown[$v->zone_id] = $v->zone_name;
		}
	}
	 
	$form['begin'] = array(
		'#prefix' => '<div class="row"><div class="box box-info"><div class="box-header with-border">
              <h3 class="box-title">Final Submitted Application List</h3>
              <div class="box-tools pull-right">
                <button type="button" class="btn btn-box-tool" data-widget="collapse"><i class="fa fa-minus"></i> </button>
                <button type="button" class="btn btn-box-tool" data-widget="remove"><i class="fa fa-times"></i></button>
              </div>
            </div>
			<div class="box-body"><div class="table-responsive">',
		'#suffix' => ''
	);
	
	$form['zone_id'] = array(
		'#title' => t('Zone'),	
		'#type' => 'select',
		'#ajax' => array(
				'callback' => 'ajax_zone_callback',
			),
		 
		//'#required' => TRUE,
		'#options' => $zoneDropDown,
		//'#default_value' => !empty($resultData)? $resultData['pid'] : '',
		'#attributes' => array('class'=>array('form-control')),
		'#prefix' => '<div class="col-md-4">',
		'#suffix' => '</div>'
	);
	
	$form['all_app'] = array(
		'#type'   => 'markup',
		'#markup' => get_all_application($zoneUserMap),
		'#prefix' => '<div id="table_app_replace_div"><div class="col-md-12">',
		'#suffix' => '</div></div>'
  	);	
	$form['end'] = array(
		'#prefix' => '',
		'#suffix' => '</div></div></div></div>'
	);	  
	return $form; 
  
}

function get_all_application($zoneUserMap){
	global $base_root,$base_path,$user;
	$applicant_id = $user->uid;
	$get_all_data = array();
	$rows[] = array();
	$type					='';
	$details				='';
	$relationship			='';
	$address_of_director	='';
	 
	//$current_status = array('AI','AIBk');
	$serviceid = 4;
	$get_all_data =  get_final_application($zoneUserMap,$serviceid);/*,$current_status*/

	$Wcounter		= 0;
	$per_page		= 10;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header 		= array(
								array('data' => 'Sl. No'),
								array('data'=> 'Factory Name'),
								array('data'=> 'Factory Type'),
								array('data'=> 'Zone'),
								array('data'=> 'Service'),
								array('data'=> 'Application Number'),
								array('data'=> 'Status'),
								array('data'=> 'Date'),
								array('data'=> 'Action'),
							);
	if(!empty($get_all_data)){
		
		foreach($chunks[$current_page] as $details){ 
			$Wcounter++;
			$pdf_link	='';
			$preview_link	='';
			$status	='';

			$genare_status   = $details->plan_approve_status;
			if($genare_status!='F' && $genare_status!='In')
			{	
				$pdf_link		 = l('<i class="ace-icon fa fa-file-pdf-o bigger-130 text-red"></i> View', 'download-pdf-new-plan/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'Download PDF', 'class'=>array(''), 'target' => '_blank')));
				/*$edit_link	= l('<i class="fa fa-edit" aria-hidden="true"></i> Edit', 'applicant/caf/default/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id), array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array(''))));*/
				$preview_link	= l('<i class="fa fa-eye" aria-hidden="true"></i> View', 'jointchief-medical/application-verify/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				$verify_link	 = l('<i class="fa fa-eye" aria-hidden="true"></i> View', 'jointchief-medical/application-verify/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'Verify Documents', 'class'=>array(''))));
				/*$re_verify_link	 = l('<i class="fa fa-eye" aria-hidden="true"></i> View', 'inspector/application-verify/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'Verify Documents', 'class'=>array(''))));*/
				/*$certificate_link = l('<i class="fa fa-download" aria-hidden="true"></i> Download Plan Approval Cert.', 'plan-approval-certificate/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'Download Plan Approval', 'class'=>array(''), 'target' => '_blank')));
				$upload_link	 = l('<i class="fa fa-upload" aria-hidden="true"></i> Upload Ceritificate with DSC', 'inspector/certificate_upload/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''), 'target' => '_blank')));*/

				if($details->plan_approve_status == 'U'){
					$status = '<b>Application Submitted</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'R'){
					$status = '<b class="text-red">Application Rejected</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'RS'){
					$status = '<b class="text-blue">Application Re-submittted</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'RSU'){
					$status = '<b class="text-blue">Application Re-submittted</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'AI'){
					$status = '<b>Forwarded To Inspector</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'AICh'){
					$status = '<b>Forwarded To Inspector Chemical</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'DC'){
					$status = '<b>Forwarded To Dy.CIF</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'DCCh'){
					$status = '<b>Forwarded To Dy.CIF Chemical</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'JC'){
					$status = '<b>Forwarded To Jt.CIF</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'C'){
					$status = '<b>Forwarded To CIF</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'JCBk'){
					$status = '<b>Backed To Jt.CIF</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'DCBk'){
					$status = '<b>Backed To Dy.CIF</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'DCChBk'){
					$status = '<b>Backed To Dy.CIF Chemical</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'AIBk'){
					$status = '<b>Backed To Inspector</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'AIChBk'){
					$status = '<b>Backed To Inspector Chemical</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'ABk'){
					$status = '<b>Backed To Applicant</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'App'){
					$status = '<b class="text-green">Application Approved</b>';
					$link = $preview_link;
				}
				
								/* RIMA HOME 25-09-2018 */
				
				if($details->plan_approve_status == 'AIMd'){
					$status = '<b>Forwarded To Inspector Medical</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'AIMdBk'){
					$status = '<b>Backed To Inspector Medical</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'DCMd'){
					$status = '<b>Forwarded To Dy.CIF Medical</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'DCMdBk'){
					$status = '<b>Backed To Dy.CIF Medical</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'JCCh'){
					$status = '<b>Forwarded To Jt.CIF Chemical</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'JCChBk'){
					$status = '<b>Backed To Jt.CIF Chemical</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'JCMd'){
					$status = '<b class="text-red">Pending</b>';
					$link = $preview_link;
				}
				if($details->plan_approve_status == 'JCMdBk'){
					$status = '<b class="text-red">Pending</b>';
					$link = $preview_link;
				}
				/* RIMA HOME 25-09-2018 */
				
				if($details->plan_approve_status == 'I'){
					$status = '<b class="text-green">Approval of Plan Issued</b>';
					$link = $preview_link;
				}
				$Identification = $details->plan_approve_identification_number;
					if(empty($Identification)){
						$Identification = 'Under Process';
				}		

			if(!empty($details->created_date)){
				$created_date = date('dS M Y', strtotime($details->created_date));
			}else{
				$created_date = '';
			}
			
				$rows[] 	= array( 
								    array('data' =>$Wcounter,'class' => array('')),
									array('data' =>$details->factory_name ,'class' => array('')),
									array('data' =>$details->factory_type ,'class' => array('')),
									array('data' =>$details->zone_name ,'class' => array('')),
									array('data' =>$details->service_name ,'class' => array('')),
									array('data' =>$Identification ,'class' => array('')),
									array('data' =>$status ,'class' => array('')),
									array('data' =>$created_date ,'class' => array('')),
									array('data' =>$link,'class' => array('')),
								);
			}
		}
	}
	
	$output = theme_table(
	array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('class' => array('table no-margin remove-odd-even# custom-table-view-dashboard')),
		 // 'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") 
		)
	).theme('pager');	
		 return $output;
	
}
?>