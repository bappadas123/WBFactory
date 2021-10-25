<?php
function all_condition($application_id,$reference_no,$ajax){

	//	die('KKK'.$application_id);
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
	 
	 $output = ctools_modal_form_wrapper('view_plan_condition', $form_state);
	  
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('view_plan_condition');
   }
}
   
function view_plan_condition($form, &$form_state) {	

	$query_cond		= 	db_select('fa_cafa_conditions', 'fcc');
	$query_cond     ->  InnerJoin('users', 'u', 'fcc.added_by_uid=u.uid');
	$query_cond		->	fields('fcc',array('sending_time','conditions','added_by_name'));
	$query_cond		->	fields('u',array('name'));
	$query_cond		-> 	condition('fcc.app_id', $form_state['app_id']);
	$query_cond		-> 	condition('fcc.app_reference_no', $form_state['ref_no']);
	$query_cond		-> 	orderBy('fcc.id', 'ASC');
	$result_cond	= $query_cond->execute()->fetchAll();
	
	$header_1 = array(array('data' => 'The plans will be approved subject to the following conditions ::', 'colspan' => 5));
	$rows_1[] = array(array('data' =>'1. Approval of the design and the site or situation of the septic tank. latrines shall be obtained from the Chief Engineer, Public Health Engineering, Government of West Bengal.'));
	$output_1 = theme_table(
		array('header' => $header_1, 'rows' => $rows_1,'attributes' => array('class' => array('table no-margin custom-table-view-dashboard'))));

	$header_2 = array(array('data' => '', 'colspan' => 5));
	$rows_2[] = array(array('data' =>'2. Approval shall be obtained from the West Bengal Pollution Control Board and the Public Health ENgineering Directorate, Government of West Bengal in respect of the arrangement for disposal of trade waste and effluents (including atmospheric emission).'));
	$output_2 = theme_table(
		array('header' => $header_2, 'rows' => $rows_2,'attributes' => array('class' => array('table no-margin custom-table-view-dashboard'))));

	$header_3 = array(array('data' => '', 'colspan' => 5));
	$rows_3[] = array(array('data' =>'3. Approval shall be obtained from Local authority (Municipal Corporation / Municipality, Notified Area, Authority / Anchal Panchayat etc.) in respect of safe design and construction of the buildings/sheds/structures etc.'));
	$output_3 = theme_table(
		array('header' => $header_3, 'rows' => $rows_3,'attributes' => array('class' => array('table no-margin custom-table-view-dashboard'))));

	$header_4 = array(array('data' => '', 'colspan' => 5));
	$rows_4[] = array(array('data' =>'4. Adequate ventilation by circulation of the fresh air, adequate means of escape in case of fire, safe means of access to every place of work, adequate fire fighting arrangement, effective arrangement to prevent escape of dust/fumesmoke shall be provided.'));
	$output_4 = theme_table(
		array('header' => $header_4, 'rows' => $rows_4,'attributes' => array('class' => array('table no-margin custom-table-view-dashboard'))));
						
	$header = array(
					array('data'=> 'Sl. No.','width' => '6%'),
					array('data'=> 'Designation'),
					array('data'=> 'Name','width' => '25%'),
					array('data'=> 'Conditions','width' => '25%'),
					array('data'=> 'Date','width' => '14%'),
				);
					
	if(!empty($result_cond)){
		foreach($result_cond as $data){ 
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
						array('data' =>$i,'class' => array('center')),
						array('data' =>$designation ,'class' => array('')),
						array('data' =>$data->added_by_name ,'class' => array('')),
						array('data' =>$data->conditions ,'class' => array('')),
						array('data' =>$send_date ,'class' => array('')),
					);
		} 
	}
	
		$output = theme_table(
		array(
			  'header' => $header,
			  'rows' => $rows,
			  'attributes' => array('class' => array('table no-margin custom-table-view-dashboard')),
			 // 'sticky' => true,
			  'caption' => '',
			  'colgroups' => array(),
			  'empty' => t("No data found!") 
			)
		).theme('pager');
		
	$form['condition_view']['show_act_div'] = array(
	   '#prefix' => '<div>'.$output_1.$output_2.$output_3.$output_4.$output,
       '#suffix' => '</div>',
     );
	 
	return $form;	
}

?>