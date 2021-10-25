<?php

function annual_report_step3( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;
	 
	
	  $filenumber=encryption_decryption_fun('decrypt',$filenumber);
	
	 
	
	      
	
	
	
		
	   $mr_istquery = db_select('labour_factory_statcell_annual_report', 'a');
       
        $mr_istquery->condition('a.annual_inspection_id',trim($filenumber),'=');
      
    
        $mr_istquery->fields('a',array('area','inspector_id', 'report_from_date','report_to_date'));
        $mr_istquery_result = $mr_istquery->execute(); 
    
       $result_mrist=$mr_istquery_result->fetchAssoc();
       $area=$result_mrist['area'];
       $inspector_id=$result_mrist['inspector_id'];
       $inspector_name=get_name($inspector_id);
       $report_from_date=date('d-m-Y', strtotime($result_mrist['report_from_date']));
      $report_to_date=date('d-m-Y', strtotime($result_mrist['report_to_date']));
	

		
    
	
	      
	
	
	// Part 4
		
	      $form['step1Dfield'] = array(
          '#title' => t('<b> Area:'.$area.' , From date: '.$report_from_date.' , To date: '.$report_to_date.''),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

	$form['step1Dfield']['inspectionid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $filenumber,
	   
	   );	
     	
$form['step1Dfield']['colD1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b>Chemical Factory.</b> </div>
			   <div class="table-responsive">
			   <table class="table table-striped table-bordered table-responsive admin-custom-table add-employee-table-view">
			   <thead><tr><th rowspan="2" >', 
		       '#markup'=>'<b> Name of the Factory  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );


                $form['step1Dfield']['colD2'] = array
              (
		       '#prefix' => ' <th rowspan="2"  >', 
		        '#markup'=>'<b> Address of the Factory  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step1Dfield']['colD3'] = array
              (
		       '#prefix' => ' <th rowspan="2"  >', 
		        '#markup'=>'<b> Products Manufactured  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step1Dfield']['colD4'] = array
              (
		       '#prefix' => ' <th colspan="3"  >', 
		        '#markup'=>'<b> Hazards arising from/out of </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

               $form['step1Dfield']['colD5'] = array
              (
		       '#prefix' => ' <th rowspan="2"  >', 
		        '#markup'=>'<b> Type of hazard </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step1Dfield']['colD6'] = array
              (
		       '#prefix' => ' <th rowspan="2"  >', 
		        '#markup'=>'<b> Action </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

                $form['step1Dfield']['colD7'] = array
              (
		       '#prefix' => ' <th rowspan="2"  >', 
		        '#markup'=>'<b> Maximum storage of hazardous substances </b>',
           

		        '#suffix'=>'</th></tr></thead>',
	   
	   
           ); 

             $form['step1Dfield']['colD8'] = array
              (
		       '#prefix' => ' <tr> <td  >', 
		        '#markup'=>'<b> Raw Material used </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


                $form['step1Dfield']['colD9'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b>Intermediaries by products formed</b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 
              $form['step1Dfield']['colD10'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> Finished Product </b>',
           

		        '#suffix'=>'</td></tr>',
	   
	   
           ); 

          



              
             

             

        




              $form['step1Dfield']['col1val'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		         '#type' => 'textarea',
		       
                '#rows' => 10,
                 '#cols' => 30,
		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Dfield']['col2val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textarea',
		       
                '#rows' => 10,
                 '#cols' => 30,
		          '#suffix'=>'</td>',
	   
	   
           );

         $form['step1Dfield']['col3val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		      '#type' => 'textarea',
		       
                '#rows' => 10,
                 '#cols' => 30,
		          '#suffix'=>'</td>',
	   
	   
           );

 $form['step1Dfield']['col4val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textarea',
		       
                '#rows' => 10,
                 '#cols' => 30,
		          '#suffix'=>'</td>',
	   
	   
           );
$form['step1Dfield']['col5val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		        '#type' => 'textarea',
		       
                '#rows' => 10,
                 '#cols' => 30,
		          '#suffix'=>'</td>',
	   
	   
           );

           $form['step1Dfield']['col6val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textarea',
		       
                '#rows' => 10,
                 '#cols' => 30,
		          '#suffix'=>'</td>',
	   
	   
           );

           $form['step1Dfield']['col7val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textarea',
		       
                '#rows' => 10,
                 '#cols' => 30,
		          '#suffix'=>'</td>',
	   
	   
           );
           $form['step1Dfield']['col8val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textarea',
		       
                '#rows' => 10,
                 '#cols' => 30,
		          '#suffix'=>'</td>',
	   
	   
           );

               $form['step1Dfield']['col9val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textarea',
		       
                '#rows' => 10,
                 '#cols' => 30,
		          '#suffix'=>'</td></tr></table>',
	   
	   
           );

           
               

			$form['step1Dfield']['submit_button']					= array(
																 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
																	'#type' => 'button',
		                                                           '#event' => 'click',

																 '#default_value' => 'ADD  ',
                                                              '#ajax' => array(
                                                              'callback' => 'add_step3_data',
                                                              'wrapper' => 'pr_person_add',
                                                                'method' => 'html',
                                                                     'effect' => 'fade'
                                                               )
																);
		 
		 
	
	 	
		
		
 $output1='';
      if(trim($filenumber)){
      $query_tab_1_c=db_query('select  *  from labour_factory_statcell_annual_report_t3 where  annual_inspection_id = :anid', array(':anid' => trim($filenumber) ));
      if($query_tab_1_c->rowCount() > 0) 
              { 
      $output1 = "<div class='table-responsive'><table class='table table-striped table-bordered table-responsive admin-custom-table add-employee-table-view'>
	  <thead>
	    <tr > <th >SL.NO</th>
      
       <th > Name of the Factory</th>
	    <th >Address of the Factory</th>
       
		 <th >Products Manufactured</th>

		 <th >Raw Material used</th>
       
		 <th >Intermediaries by products formed</th>
		  <th >Finished Product</th>
       
		 <th >Type of hazard</th>
		  <th >Action</th>
		   <th >Maximum storage of hazardous substances</th>
		 <th >DELETE</th>
		</tr></thead>";  
			  $i=0;
		foreach($query_tab_1_c as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $annual_inspection_id = $squan->annual_inspection_id; 
	          $factory_name=$squan->factory_name;
			  $factory_address=$squan->factory_address;
			  $products=$squan->products;
              $raw_material=$squan->raw_material;

              $intermediaries_products=$squan->intermediaries_products;

              $finished_product=$squan->finished_product;
              $hazard_type=$squan->hazard_type;
               $action=$squan->action;
              $maximum_storage=$squan->maximum_storage;
              
              
			 //  $bb=$base_root.$base_path.'equalremuins/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id).'/presentperdel';

			   $bb=$base_root.$base_path.'admin/annual-report-tab3-del/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
		      $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
		
		
		
		      $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
			  
			  
			  
              if($i%2==0){
		        $output1 .= "<tr bgcolor=\"#FCF6CF\">";
				 }
				else
				{
				$output1 .= "<tr bgcolor=\"#FEFEF2\">";
				}
				$output1.= "<td>".$i."</td>"; 
				$output1.= "<td>".$factory_name."</td>";
			    $output1.= "<td>".$factory_address."</td>";
                $output1.= "<td>".$products."</td>";
                $output1.= "<td>".$raw_material."</td>";
                $output1.= "<td>".$intermediaries_products."</td>";
                $output1.= "<td>".$finished_product."</td>";
                $output1.= "<td>".$hazard_type."</td>";
                $output1.= "<td >".$action."</td>";
                $output1.= "<td >".$maximum_storage."</td>";
			
				$output1.= "<td >".$del_preper."</td>";
			
              
			   $output1 .= "</tr>";
	          }
              $output1 .= "</table></div>"; 
			  
			

	
	   }
	}
	 $form['step1Dfield']['prpersonlist'] = array(
	 	'#prefix' => '<div align="left" id="pr_person_add">'.$output1,
		'#suffix' => '</div>',
       
	);


		
				
	
														
														  
	        return $form; 
  }



function step3_del(  $filenumber = NULL , $rowid = NULL){
	  
	 global $base_root, $base_path;
	  //  $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));
	   
      //$tyinfg= encryption_decryption_fun('decrypt', trim($tyinfg));

	   $filenumber=  encryption_decryption_fun('decrypt',trim($filenumber));
	   
      $rowid=  encryption_decryption_fun('decrypt',trim($rowid));
	   
	$txn = db_transaction();
	  try {
		  
    db_delete('labour_factory_statcell_annual_report_t3')
    ->condition('annual_inspection_id',trim($filenumber))
	->condition('row_id',trim($rowid))
    ->execute();
	
	
	$message = '   delete is successfull ';
	
}
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
	$message = '    row is not  delete ';
     }	
	
     //$aa=$base_root.$base_path.'equalremuins/equalinfringements/'.encryption_decryption_fun('encrypt', trim($filenumber));

      $aa=$base_root.$base_path.'admin/annual-report/step3/'.encryption_decryption_fun('encrypt',$filenumber);
     drupal_set_message(t($message));
		 
		  drupal_goto($aa);
		  
  }


function add_step3_data($form , $form_state) {	
       global $base_root, $base_path;
       $val=$form_state['values'];


    
 
      $inspectionid=trim($val['inspectionid']);
      $col1val=trim($val['col1val']); if(!$col1val) $col1val= NULL;  
      $col2val=trim($val['col2val']);   if(!$col2val)   $col2val= NULL;  
      $col3val=trim($val['col3val']);   if(!$col3val)   $col3val= NULL;  
      $col4val=trim($val['col4val']);   if(!$col4val)   $col4val= NULL;  
      $col5val=trim($val['col5val']);   if(!$col5val)   $col5val= NULL;  
      $col6val=trim($val['col6val']);   if(!$col6val)   $col6val= NULL;  
      $col7val=trim($val['col7val']);   if(!$col7val)   $col7val= NULL;  
      $col8val=trim($val['col8val']);   if(!$col8val)   $col8val= NULL; 
      $col9val=trim($val['col9val']);   if(!$col9val)   $col9val= NULL;    


   if(!$col1val)
	 {
	  drupal_get_messages(error);
	  return "<font color='#FF3333'><b>please enter factory  name <b>    </font>";
	  exit;
	 } 

	  elseif(!$col2val)
	 {
	  drupal_get_messages(error);
	  return "<font color='#FF3333'><b>please enter factory address   <b>    </font>";
	  exit;
	 } 
	    


     $txn = db_transaction();

        try {
     
	 
	  $ins_pr_person=db_query('select  max(row_id) ownermax from labour_factory_statcell_annual_report_t3  ');
	foreach($ins_pr_person as $energy) {
	
	    $ownermax = $energy->ownermax; 
        
		
	}
		
	 if($ins_pr_person->rowCount()==0) 
        { 
		$count_profile=1;
		}
		else
		{
		$count_profile=$ownermax+1;	
			
		}
			
	      
		   
		    $fieldsE = array('row_id' => $count_profile, 'annual_inspection_id' => $inspectionid,'factory_name' =>$col1val ,'factory_address' =>$col2val,'products' =>$col3val, 'raw_material' => $col4val, 'intermediaries_products' => $col5val, 'finished_product' => $col6val, 'hazard_type' => $col7val , 'action' => $col8val , 'maximum_storage' => $col9val);
		  
		   
           db_insert('labour_factory_statcell_annual_report_t3')->fields($fieldsE)->execute();	
	 
	 
	$query_tab_1_c=db_query('select  *  from labour_factory_statcell_annual_report_t3 where  annual_inspection_id = :anid', array(':anid' => trim($inspectionid) ));
    
      $output1 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
	    <tr > <th >SL.NO</th>
      
       <th > Name of the Factory</th>
	    <th >Address of the Factory</th>
       
		 <th >Products Manufactured</th>

		 <th >Raw Material used</th>
       
		 <th >Intermediaries by products formed</th>
		  <th >Finished Product</th>
       
		 <th >Type of hazard</th>
		  <th >Action</th>
		   <th >Maximum storage of hazardous substances</th>
		 <th >DELETE</th>
		</tr>";  
			  $i=0;
		foreach($query_tab_1_c as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $annual_inspection_id = $squan->annual_inspection_id; 
	          $factory_name=$squan->factory_name;
			  $factory_address=$squan->factory_address;
			  $products=$squan->products;
              $raw_material=$squan->raw_material;

              $intermediaries_products=$squan->intermediaries_products;

              $finished_product=$squan->finished_product;
              $hazard_type=$squan->hazard_type;
              $action=$squan->action;
              $maximum_storage=$squan->maximum_storage;
              
              
			 //  $bb=$base_root.$base_path.'equalremuins/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id).'/presentperdel';

			   $bb=$base_root.$base_path.'admin/annual-report-tab3-del/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
		      $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
		
		
		
		      $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
			  
			  
			  
              if($i%2==0){
		        $output1 .= "<tr bgcolor=\"#FCF6CF\">";
				 }
				else
				{
				$output1 .= "<tr bgcolor=\"#FEFEF2\">";
				}
				$output1.= "<td>".$i."</td>"; 
				$output1.= "<td>".$factory_name."</td>";
			    $output1.= "<td>".$factory_address."</td>";
                $output1.= "<td>".$products."</td>";
                $output1.= "<td>".$raw_material."</td>";
                $output1.= "<td>".$intermediaries_products."</td>";
                $output1.= "<td>".$finished_product."</td>";
                $output1.= "<td>".$hazard_type."</td>";
                $output1.= "<td >".$action."</td>";
				$output1.= "<td >".$maximum_storage."</td>";
				$output1.= "<td >".$del_preper."</td>";
			
              
			   $output1 .= "</tr>";
	          }
              $output1 .= "</table>";
			  
			

	
	   



	  }
  catch (Exception $e) {
    $form_state['rebuild'] = TRUE;
 
    $txn->rollback();
  
    watchdog_exception('type', $e);
	$output1 = ' DATA NOT INSERT';
  }  
	


                          drupal_get_messages(error);
		                  return $output1;
		                  exit;
                          
                          }