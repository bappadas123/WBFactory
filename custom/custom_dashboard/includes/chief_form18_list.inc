<?php
function chief_form18_list($form, &$form_state) {
	global $base_root,$base_path,$user;

  	drupal_add_css(drupal_get_path('module', 'notice_form') . '/css/sky-forms.css');
  	drupal_add_css(drupal_get_path('module', 'notice_form') . '/css/form-design.css');
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
		  <h3 class="box-title">Application List of Form-18</h3>
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
	
	$get_all_data =  get_notice_application($zoneUserMap,$tablename='fa_form18_notice_accident');//,$status='DC'

	$Wcounter		= 0;
	$per_page		= 10;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header 				= array(
								array('data'=> 'Sl. No.','width' => '6%'),
								array('data'=> 'Factory Details','width' => '20%'),
								array('data'=> 'Accident Date','width' => '18%'),
								array('data'=> 'Type of Accident','width' => '12%'),
								array('data'=> 'Status','width'  => '18%'),
								array('data'=> 'Action','width' => '16%'),
							);
							
	if(!empty($get_all_data)){
		foreach($chunks[$current_page] as $details){ //echo "<pre>"; print_r($details);
			$Wcounter++;
			
			$get_uploaded_doc = get_uploaded_document_url($details->uploaded_pdf);
			
			$download_link	 = l('<i class="fa fa-download text-blue" aria-hidden="true"></i> Download', file_create_url($get_uploaded_doc), array('html' => TRUE,'attributes'=>array('title' => 'Download', 'class'=>array(''))));
			
			$view_link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> View', 'chief-form18-view/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->factory_id), array('html' => TRUE,'attributes'=>array('title' => 'View', 'class'=>array(''), 'target' => '_blank')));
			
		     if($details->notice_status == 'RC')
			 { $status = '<b class="text-red">Receiving Cell</b>';}
			 elseif($details->notice_status == 'SC')
			 { $status = '<b class="text-blue">Forwarded to Statistical Cell</b>';}
			 elseif($details->notice_status == 'DC')
			 { $status = '<b class="text-blue">Forwarded to Deputy Chief</b>';}
			 elseif($details->notice_status == 'C')
			 { $status = '<b class="text-red">Pending</b>';}
			 elseif($details->notice_status == 'AI')
			 { $status = '<b class="text-blue">Forwarded to Inspector</b>';}	
			 
			if($details->accident_type == 'M')
				{	$accident_type = "Minor"; }	
			if($details->accident_type == 'S')
				{	$accident_type = "Serious"; }	
			if($details->accident_type == 'F')
				{	$accident_type = "Fatal"; }	

			$rows[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' =>'<b>Name:</b> '.$details->factory_name.'<br><b>Place:</b> '.$details->accident_place,'class' => array('')),
							array('data' =>'<b>Date:</b> '.$details->accident_date.'<br><b>Shift:</b> '.$details->accident_shift,'class' => array('')),
							array('data' =>$accident_type,'class' => array('')),
							array('data' =>$status,'class' => array()),
							array('data' =>$download_link.' '.$view_link,'class' => array()),
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
?>