<?php
function inspector_view_chemical_registration_list($form, &$form_state) {
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
	
	$get_all_data =  get_reg_application_list($zoneUserMap);
	
	//echo "<pre>"; print_r($get_all_data); die;
	
	$Wcounter		= 0;
	$per_page		= 10;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header 		= array(
								array('data'=> 'Sl. No'),
								array('data'=> 'Factory Details'),
								array('data'=> 'Plan Approval No./License No & Date'),
								array('data'=> 'e-Service'),
								array('data'=> 'Application Number & Date'),
								array('data'=> 'Status & Date'),
								array('data'=> 'Action'),
							);
	if(!empty($get_all_data)){
		
		foreach($chunks[$current_page] as $details){ 
			$Wcounter++;
				 if($details->application_status == 'F'){
					 	$status = '<b style="color:#0D67A2;">Final submitted</b>';
					 }
					 elseif($details->application_status == 'R'){
						$status = '<b style="color:#000000">Application Rejected.</b>';
					 }
					 elseif($details->application_status == 'RS'){
						$status = '<b style="color:#0D67A2;">Application Re-submitted</b>';
					 }
					 elseif($details->application_status == 'AI'){
					 	$status = '<b style="color:#0D67A2;">Forword to Inspector</b>';
					 }
					  elseif($details->application_status == 'AIBk'){
						$status = '<b style="color:#0D67A2;">Backed to Inspector</b>';
					 }
					  elseif($details->application_status == 'CHE'){
					 	$status = '<b style="color:red;">Pending</b>';
					 }
					 elseif($details->application_status == 'B'){
					 	$status = '<b style="color:#0008ff">Backed to Applicant</b>';
					 }
					 elseif($details->application_status == 'DC'){
						$status = '<b style="color:green">Forward to DY. CIF</b>';
					 }
					 elseif($details->application_status == 'DCBk'){
						$status = '<b style="color:#0D67A2;">Back to DY. CIF</b>';
					 }                                            
					 elseif($details->application_status == 'JC'){
					 	$status = '<b style="color:green;">Forward to Jt. Chief</b>';
					 }
					 elseif($details->application_status == 'CH'){
					 	$status = '<b style="color:green">Forward to CIF</b>';
					 }
					 
					 $preview_link	= l('<i class="fa fa-eye" aria-hidden="true"></i> View', 'regsection/view-register-inspector-chemical/'.encryption_decryption_fun('encrypt',$details->service_id).'/'.encryption_decryption_fun('encrypt',$details->factory_typeid).'/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''))));
				 
			 $Identification = $details->factory_reg_identification_number;
			if(!empty($details->created_date)){
				$created_date = date('dS M Y', strtotime($details->created_date));
			}else{
				$created_date = '';
			}
			if(!empty($details->modification_date)){
				$modification_date = date('dS M Y', strtotime($details->modification_date));
				}else{
					$modification_date = '';
					}
		
			if(!empty($details->factory_plan_approval_number)){
				$plan_approval = $details->factory_plan_approval_number.'<br><b>Date - </b>'.$modification_date;
				}else{
					$plan_approval = '--';
				}
			
			$factory_type = explode(' ',$details->factory_type);
					
					$rows[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' =>$details->factory_name.' ['.$factory_type[1].']<br><b>Zone - </b>'.$details->zone_name,'class' => array('')),
							array('data' =>$plan_approval,$details->zone_name,'class' => array('')),
							array('data' =>$details->service_name ,'class' => array('')),
							array('data' =>$Identification.'<br><b>Date - </b>'.$created_date,'class' => array('')),
							array('data' =>$status.'<br><b>Date - </b>'.$modification_date,'class' => array('')),
							array('data' =>$preview_link.'<br/>','class' => array('')),
						);
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