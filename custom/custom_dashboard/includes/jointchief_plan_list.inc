<?php
function jointchief_plan_list($form, &$form_state) {
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

			$gen_status  = find_general_status($details->id);
			//$final_status = find_final_status($details->id);

			$genare_status   = $details->plan_approve_status;
			if($genare_status!='F' && $genare_status!='In')
			{	
				$pdf_link		 = l('<i class="ace-icon fa fa-file-pdf-o bigger-130 text-red"></i> View', 'download-pdf-new-plan/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'Download PDF', 'class'=>array(''), 'target' => '_blank')));
				$preview_link	= l('<i class="fa fa-eye" aria-hidden="true"></i> View', 'jointchief/application-verify/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
				$verify_link	 = l('<i class="fa fa-eye" aria-hidden="true"></i> View', 'jointchief/application-verify/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'Verify Documents', 'class'=>array(''))));

				$get_dwnld_cert = get_caf_upload_doc_details($details->id, $details->service_id, 'APPROVAL LETTER', $details->factory_typeid, $details->reference_number);
				//print_r($get_uploaded_cert);
				$dwnld_cert = l('<i class="fa fa-download" aria-hidden="true"></i> Plan Approval Certificate','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $get_dwnld_cert->id).'/'.encryption_decryption_fun('encrypt', 'APPROVAL LETTER').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));
				
				$get_dwnld_plan = get_caf_upload_doc_details($details->id, $details->service_id, 'FACTORY PLAN', $details->factory_typeid, $details->reference_number);
				$dwnld_plan = l('<i class="fa fa-download" aria-hidden="true"></i> Download Plan','document-list/view-upload-doc/'.encryption_decryption_fun('encrypt', $get_dwnld_plan->id).'/'.encryption_decryption_fun('encrypt', 'FACTORY PLAN').'',array('html' => TRUE,'attributes'=>array('title' => 'Display file','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));

				$download_notesheet	= l('<i class="fa fa-eye" aria-hidden="true"></i> Download Notesheet', 'download-notesheet/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'Verify Documents','target'=>'_BLANK','onclick' => "popIt(this.href);return false;",'class'=>array('dispaly'))));

					if($gen_status == 'AI'){
						$status = '<b>Forwarded To Inspector General</b>';
						$link = $preview_link;
						$ack_link="";
					}
					if($gen_status == 'AIBk'){
						$status = '<b>Backed To Inspector General</b>';
						$link = $preview_link;
						$ack_link="";
					}
					if($gen_status == 'DC'){
						$status = '<b>Forwarded To Dy.CIF General</b>';
						$link = $preview_link;
						$ack_link="";
					}
					if($gen_status == 'DCBk'){
						$status = '<b>Backed To Dy.CIF General</b>';
						$link = $preview_link;
						$ack_link="";
					}
					if(($gen_status == 'JC') || ($gen_status == 'JCF')){
						$status = '<b class="text-red">Pending</b>';
						$link = $preview_link;
						$ack_link="";
					}
					if($gen_status == 'ABk'){
						$status = '<b>Backed To Applicant</b>';
						$link = $preview_link;
						$ack_link="";
					}
					if($gen_status == 'RS'){
						$status = '<b class="text-blue">Application Re-submittted</b>';
						$link = $preview_link.'<br>'.$upload_link;
						$ack_link="";
					}
					if($gen_status == 'I'){
						$status = '<b class="text-green">Approval of Plan Issued</b>';
						$link = $preview_link.'<br>'.$dwnld_cert.'<br>'.$dwnld_plan.'<br>'.$download_notesheet;
						$ack_link="";
					}
				
				// check final status for approval
				/*if($final_status !=0 && $gen_status != 'I'){
					$status = '<b class="text-red">Pending</b>';
					$link = $preview_link;
					$ack_link="";
				}*/

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