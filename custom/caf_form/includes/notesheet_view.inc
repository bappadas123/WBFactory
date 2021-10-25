<?php
function all_notesheet($application_id,$reference_no,$ajax){
//	die('KKK'.$id_m);
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
	 
	 $output = ctools_modal_form_wrapper('view_plan_notesheet', $form_state);
	  
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('view_plan_notesheet');
   }
}
   
function view_plan_notesheet($form, &$form_state) {	
	
	$query_note		= 	db_select('fa_cafa_remarks', 'fcr');
	$query_note     ->  InnerJoin('users', 'u', 'fcr.remark_by_uid=u.uid');
	$query_note		->	fields('fcr',array('sending_time','remarks','remark_by_name'));
	$query_note		->	fields('u',array('name'));
	$query_note		-> 	condition('fcr.app_id', $form_state['app_id']);
	$query_note		-> 	condition('fcr.app_reference_no', $form_state['ref_no']);
	$query_note		-> 	condition('fcr.remarks',' ','!=');
	$query_note		-> 	condition('fcr.remark_type', 'n');
	$query_note		-> 	orderBy('fcr.id', 'ASC');

	$result_note	= $query_note->execute()->fetchAll();
	$header = array(
						array('data' => 'Sl. No'),
						array('data'=> 'Designation'),
						array('data'=> 'Name'),
						array('data'=> 'Remarks'),
						array('data'=> 'Date'),
					);
	if(!empty($result_note)){
		foreach($result_note as $data){ //echo "<pre>"; print_r($data);
			$i++;
			
			$date = date_create($data->sending_time); //die;
			$send_date = date_format($date,'F j, Y');
			
			if($data->name == 'inspector' ) {$designation = 'Inspector';}
			elseif($data->name == 'inspectorchemical' ) {$designation = 'Inspector Chemical';}
			elseif($data->name == 'deputychief' ) {$designation = 'Dy. CIF';}
			elseif($data->name == 'deputychiefchemical' ) {$designation = 'Dy. CIF Chemical';}
			elseif($data->name == 'jointchief' ) {$designation = 'Jt. CIF';}
			elseif($data->name == 'jointchiefchemical' ) {$designation = 'Jt. CIF Chemical';}
			elseif($data->name == 'chief' ) {$designation = 'CIF';}
			
			$rows[] = array( 
						array('data' =>$i,'class' => array('')),
						array('data' =>$designation ,'class' => array('')),
						array('data' =>$data->remark_by_name ,'class' => array('')),
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
	
	$form['notesheet_view']['show_act_div'] = array(
	   '#prefix' => '<div>'.$output,
        '#suffix' => '</div>',
     );
	 
	return $form;	
}

?>