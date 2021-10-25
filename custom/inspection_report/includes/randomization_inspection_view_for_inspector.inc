<?php
function randomization_inspection_view($form, &$form_state){
	 global $base_root, $base_path, $user;
	 $uid=$user->uid; 
	
	
	//print 'aaaa'.$uid;
	
	
		drupal_add_css(drupal_get_path('module', 'caf_form') . '/css/form-design.css');  
	   
	 $form['inspectionlistfields'] = array(
          '#title' => t(''),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          );   
   
	   $rows = array();
    $header = array();
  
  
   $header = array(
      
            array('data'=> 'Registration No', 'class' => array('')),
			array('data'=> 'Inspection Date', 'class' => array('')),
		    array('data'=> ' Name of the Factory', 'class' => array('')),
            array('data' => 'Factory Address', 'class' => array('')),
			array('data' => 'inspection Note', 'class' => array('')),
			
		   
	);
	 
	     $sort = 'DESC';
	     $order = 'schedule_date';
		 
		
         $ins_list_query = db_select('schedule_dates', 'a');
	     $ins_list_query->join('schedule_dates_allot_factory', 'b', 'a.schedule_date_id=b.schedule_date_id');
         $ins_list_query->join('schedule_dates_allot_factory_inspector', 'c', 'b.factory_allotment_id=c.factory_allotment_id');
		 $ins_list_query->join('schedule_factory_mst ', 'd', 'b.factory_id =d.factory_id ');
		
		 
         $ins_list_query->fields('a', array('schedule_date_id','schedule_date'));
         $ins_list_query->fields('b', array('factory_id')); 
		 $ins_list_query->fields('c', array('inspector_id')); 
		 $ins_list_query->fields('d', array('registration_no','factory_name','factory_address'));
         
		$ins_list_query->condition('inspector_id',trim($uid),'=');
		  
		 // print $ins_list_query;
		  //exit;
	     $ins_list_query = $ins_list_query->extend('TableSort')->extend('PagerDefault')->limit(15);
		
		
		
	     $ins_list_query->orderBy($order, $sort);
	     $ins_list_query_result = $ins_list_query->execute();
		  
		  
		    
		  
		  
	
	
		
	     $i=0;
		foreach($ins_list_query_result as $data) {
			$i++;
			
			
			
			global $base_root, $base_path;
			
			
			/*$owner_name=db_query('select  name_mt_worker from l_mt_worker_details where  ins_file_number=:filenumber limit 1', array(':filenumber' => trim($data->ins_file_number)) );
	   
	         $result_own=$owner_name->fetchAssoc();
	         $name_mt_worker= trim($result_own['name_mt_worker']);
			
			
			
			
			
		     $aa=$base_root.$base_path.'alcinspection/inspectionnoteview/'.encryption_decryption_fun('encrypt',$data->ins_file_number);
		     $link_s=l(t('View'), $aa);*/
			 
			 
	
	
	
	
	
	
    	
	        $link_s='add link';
	
	 
	
	  
	
	     
	 	
	
			 
	    
				 
			   $rows[] = array(
      						$data->registration_no,
							date('dS M, Y', strtotime($data->schedule_date)),
							$data->factory_name,
							$data->factory_address,
							$link_s,
							
							//$link_s,
							
							
			    
	  		   );   
}

 $variables = array(
	  		  'attributes' 	=> array('class' => array('table no-margin remove-odd-even# custom-table-view-dashboard')),
	  			'header' 			=> $header,
	  			'rows'				=> $rows,
	  			'empty' => t(' No data .'),
		);
	
	//$output = theme('datatable', $variables);

	$output = theme('table', $variables).theme("pager");
	
	
			  $form['inspectionlistfields']['addshowprin'] = array
              (
		   
		    '#markup'=>$output,
	   
	
              );
 
  // return $output;
 
  return $form; 
}
?>