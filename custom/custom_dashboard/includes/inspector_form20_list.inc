<?php
function inspector_form20_list($form, &$form_state) {
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
		  <h3 class="box-title">Application List of Form-20</h3>
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
	
	$get_all_data =  get_notice_application($zoneUserMap,$tablename='fa_form20_notice_poisoning',$status='AI');

	$Wcounter		= 0;
	$per_page		= 10;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	$header 				= array(
								array('data'=> 'Sl. No.','width' => '6%'),
								array('data'=> 'Factory Name','width' => '27%'),
								array('data'=> 'Nature of Industry','width' => '23%'),
								array('data'=> 'Factory Zone','width'  => '17%'),
								array('data'=> 'No. Patient','width'  => '12%'),
								array('data'=> 'Action','width' => '15%'),
							);
							
	if(!empty($get_all_data)){
		foreach($chunks[$current_page] as $details){ 
		
			$Wcounter++;
			
			$get_uploaded_doc = get_uploaded_document_url($details->uploaded_pdf);
			
			if($details->upload_status == 1)
			{ 
				$download_link		 = l('<i class="fa fa-download text-blue" aria-hidden="true"></i> Download', file_create_url($get_uploaded_doc), array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array(''))));
				
				$view_link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> View', 'applicant/form20-view/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->factory_id), array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array(''), 'target' => '_blank')));
				
				$link		 = $download_link.' '.$view_link;
			} else {
				$link		 = l('<i class="fa fa-edit text-blue" aria-hidden="true"></i> Edit', 'applicant/form20/default/'.encryption_decryption_fun('encrypt',$details->id).'/'.encryption_decryption_fun('encrypt',$details->reference_number).'/'.encryption_decryption_fun('encrypt',$details->factory_id), array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array(''), 'target' => '_blank')));
			}
			
	 $data_result = db_query("SELECT count(*) FROM {fa_form20_patient_details} where notice_poisoning_id = '$details->id'")->fetchObject()->count;

			$rows[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' =>$details->factory_name,'class' => array('')),
							array('data' =>ucfirst($details->industry_nature),'class' => array('')),
							array('data' =>$details->zone_name,'class' => array('')),
							array('data' =>$data_result,'class' => array('')),
							array('data' =>$link,'class' => array('')),
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