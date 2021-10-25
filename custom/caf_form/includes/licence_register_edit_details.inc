<?php 
function licence_register_edit_details($form, &$form_state,$id){
	drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');
	$register_id = encryption_decryption_fun('decrypt',$id);
	
	
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
		'#markup' => get_all_register_details_list($register_id),
		'#prefix' => '<div class="col-md-12" id="table_app_replace_div">',
		'#suffix' => '</div>'
  	);
	$form['licsection_dashboard']['register_id'] = array(
		'#type'   => 'hidden',
		'#default_value' 	=> !empty($register_id)? $register_id : '',
  	);
	$form['licsection_dashboard']['submit'] = array(
		'#type'   => 'submit',
		'#prefix' => '<div class="col-md-12">',
		'#suffix' => '</div>',
		'#attributes' 		=> array('class'=>array('btn bg-navy margin'),'title'=>''),
		'#default_value' 	=> 'Add More',
  	);		
	$form['regsection_dashboard']['end'] = array(
		'#suffix' => '</div></div>
						<div class="box-footer clearfix"> 
							<a href="javascript:void(0)" class="btn btn-sm btn-default btn-flat# pull-right">View All</a> 
						</div>
					</div>
				</div>
			</div>'
	);	  		  
	return $form; 
  }
  
  function get_all_register_details_list($register_id){
	global $base_root,$base_path,$user;
	$applicant_id = $user->uid;
	$get_id =$register_id ;
	$rows[] = array();

	$get_all_data =  db_query("select * from {fa_licence_register_amount}  WHERE register_id =".$get_id."ORDER BY fa_licence_register_amount.id DESC ")->fetchAll();
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
								array('data'=> 'Year'),
								array('data'=> 'power'),
								array('data'=> 'worker'),
								array('data'=> 'chalan'),
								array('data'=> 'remark'),
								array('data'=> 'Action'),
							);
	if(!empty($get_all_data)){
		foreach($chunks[$current_page] as $details){ 
		$Wcounter++;
		
		$edit	 = l('<i class="fa fa-pencil" aria-hidden="true"></i> Edit', 'edit-licence-register-page2/'.encryption_decryption_fun('encrypt',$details->id), array('html' => TRUE,'attributes'=>array('title' => 'Edit', 'class'=>array(''))));
					$rows[] = array( 
							array('data' =>$Wcounter,'class' => array('')),
							array('data' =>$details->licence_period,'class' => array('')),
							array('data' =>$details->power.'&nbsp;'.$details->power_type,'class' => array('')),
							array('data' =>$details->worker,'class' => array('')),
							array('data' =>$details->challan_no,'class' => array('')),
							array('data' =>$details->register_remarks,'class' => array('')),
							array('data' =>$edit,'class' => array('')),
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

function licence_register_edit_details_submit($form, &$form_state){
	global $user;
	$val   			=  $form_state['values'];
	$register_id	=  $val['register_id'];
	
	drupal_goto('add-licence-register-page2/'.encryption_decryption_fun('encrypt',$register_id));
	
	}