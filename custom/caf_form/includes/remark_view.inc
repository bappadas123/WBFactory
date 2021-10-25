<?php
function all_remark($application_id,$reference_no,$ajax){
	//die('KKK'.$application_id);
	 //return  drupal_get_form('ind_pensioner_display_pension_amount',$penid); 
	 if ($ajax) {
     // Required includes for ctools to work:
    ctools_include('ajax');
    ctools_include('modal');
	ctools_modal_add_js();
     $form_state = array(
       'ajax' => TRUE,
       'title' => t(''),
	   'app_id' => $application_id,
	   'ref_no' => $reference_no
     );
	 
	 $output = ctools_modal_form_wrapper('view_plan_remark', $form_state);
	  
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('view_plan_remark');
   }
}
   
function view_plan_remark($form, &$form_state) {	

	$query_rmrk		= 	db_select('fa_cafa_remarks', 'fcr');
	$query_rmrk     ->  InnerJoin('role', 'r', 'fcr.remark_by_roleid=r.rid');
	$query_rmrk     ->  InnerJoin('users', 'u', 'fcr.remark_by_uid=u.uid');
	$query_rmrk		->	fields('fcr',array('sending_time','remarks','remark_by_name'));
	$query_rmrk		->	fields('r',array('name'));
	$query_rmrk		->	fields('u',array('name'));
	$query_rmrk		-> 	condition('fcr.app_id', $form_state['app_id']);
	$query_rmrk		-> 	condition('fcr.app_reference_no', $form_state['ref_no']);
	$query_rmrk		-> 	condition('fcr.remarks','','!=');
	$query_rmrk		-> 	condition('fcr.remark_type', 'r');
	
	$result_remark	= $query_rmrk->execute()->fetchAll();
	
	$header = array(
						array('data' => 'Sl. No'),
						array('data'=> 'Designation'),
						array('data'=> 'Name'),
						array('data'=> 'Remarks'),
						array('data'=> 'Date'),
					);
	if(!empty($result_remark)){
		foreach($result_remark as $data){ 
			$i++;
			
			$date = date_create($data->sending_time); //die;
			$send_date = date_format($date,'F j, Y');
			
			if($data->u_name == 'inspector' ) {$designation = 'Inspector';}
			elseif($data->u_name == 'inspectorchemical' ) {$designation = 'Inspector';}
			elseif($data->u_name == 'deputychief' ) {$designation = 'Dy. CIF';}
			elseif($data->u_name == 'deputychiefchemical' ) {$designation = 'Dy. CIF Chemical';}
			elseif($data->u_name == 'jointchief' ) {$designation = 'Jt. CIF';}
			elseif($data->u_name == 'chief' ) {$designation = 'CIF';}
			
			$rows[] = array( 
						array('data' =>$i,'class' => array('')),
						array('data' =>$designation ,'class' => array('')),
						array('data' =>$data->name ,'class' => array('')),
						array('data' =>$data->remarks ,'class' => array('')),
						array('data' =>$send_date ,'class' => array('')),
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
	
	$form['remark_view']['show_act_div'] = array(
	   '#prefix' => '<div>'.$output,
        '#suffix' => '</div>',
     );
	 
	return $form;	
}

?>