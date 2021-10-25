<?php
function all_licence_register($form, &$form_state) {
	global $base_root,$base_path,$user;
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/sky-forms.css');
  	drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');
	
	$form['licsection_dashboard']['begin'] = array(
		'#prefix' => '<div class="col-md-12">
		<div class="box box-info">
            <div class="box-header with-border">
              <h3 class="box-title">All Register</h3>
              <div class="box-tools pull-right">
                <button type="button" class="btn btn-box-tool" data-widget="collapse"><i class="fa fa-minus"></i> </button>
                <button type="button" class="btn btn-box-tool" data-widget="remove"><i class="fa fa-times"></i></button>
              </div>
            </div>
            <div class="box-body">
              <div class="table-responsive">',
	);
	
	$form['licsection_dashboard']['all_app'] = array(
		'#type'   => 'markup',
		'#markup' => get_all_application(),
		'#prefix' => '<div class="col-md-12" id="table_app_replace_div">',
		'#suffix' => '</div>'
  	);	
	$form['regsection_dashboard']['end'] = array(
		'#suffix' => '</div></div><div class="box-footer clearfix"> <a href="javascript:void(0)" class="btn btn-sm btn-default btn-flat# pull-right">View All</a> </div></div></div></div>'
	);	  		  
	return $form; 
  }
 		 
function get_all_application(){
	global $base_root,$base_path,$user;
	$applicant_id = $user->uid;
	$rows[] = array();

	
	$get_all_data =  db_query("select * from {fa_licence_register}  WHERE is_active =1 ORDER BY fa_licence_register.id ASC ")->fetchAll();
	$total = count($get_all_data);
	
	$Wcounter		= 0;
	$per_page		= 10;
	$current_page 	= pager_default_initialize(count($get_all_data), $per_page);
	
	$chunks 		= array_chunk($get_all_data, $per_page, TRUE);
	if($current_page>0){
		$Wcounter 	= $current_page*$per_page;
	}
	
	$header 		= array(
								array('data'=> 'Sl. No'),
								array('data'=> 'Name & address of the factory'),
								array('data'=> 'Name of the occupier'),
								array('data'=> 'Classification No'),
								array('data'=> 'Registration No'),
								array('data'=> 'Licence No'),
								array('data'=> 'Action'),
							);
	if(!empty($get_all_data)){
		foreach($chunks[$current_page] as $details){ 
		$Wcounter++;
		$view	 = l('<i class="fa fa-eye" aria-hidden="true"></i> View', 'licence-register-view/'.encryption_decryption_fun('encrypt',$details->id), array('html' => TRUE,'attributes'=>array('title' => 'preview', 'class'=>array(''))));
		$edit	 = l('<i class="fa fa-pencil" aria-hidden="true"></i> Edit', 'licence-register-edit/'.encryption_decryption_fun('encrypt',$details->id), array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array(''))));
					$rows[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' =>$details->factory_name_address,'class' => array('')),
							array('data' =>$details->occupier_name,'class' => array('')),
							array('data' =>$details->classification_no,'class' => array('')),
							array('data' =>$details->registration_no,'class' => array('')),
							array('data' =>$details->licence_no,'class' => array('')),
							array('data' =>$view.'&nbsp;&nbsp;'.$edit,'class' => array('')),
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