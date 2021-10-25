<?php
function all_chemical($ajax){
	//die('KKK'.$id_m);
	 //return  drupal_get_form('ind_pensioner_display_pension_amount',$penid); 
	 if ($ajax) {
     // Required includes for ctools to work:
    ctools_include('ajax');
    ctools_include('modal');
	ctools_modal_add_js();
     $form_state = array(
       'ajax' => TRUE,
       'title' => t(''),
     );
	 
	 $output = ctools_modal_form_wrapper('view_chemical_product', $form_state);
	  
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('view_product_section85');
   }
}
   
function view_chemical_product($form, &$form_state) {	
	
	$query_nature_work 	=  db_select('fa_section85_nature_work', 'nature_work');
	$query_nature_work	-> fields('nature_work',array('id','work_nature'));
	$query_nature_work	-> orderBy('nature_work.id', 'ASC');
	
	$result_note	= $query_nature_work->execute()->fetchAll();
	//print_r($result_note); die;
	
	$header = array(
						array('data' => 'Sl. No'),
						array('data'=> 'Chemical Processes List'),
					);
					
	if(!empty($result_note)){
		
		foreach($result_note as $data){ 
			$i++;
			$rows[] = array( 
						array('data' =>$i,'class' => array('')),
						array('data' => 'Chemical Product'.$i ,'class' => array('')),
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
	
	$form['section85_view']['show_act_div'] = array(
	   '#prefix' => '<div>'.$output,
        '#suffix' => '</div>',
     );
	 
	return $form;	
}

?>