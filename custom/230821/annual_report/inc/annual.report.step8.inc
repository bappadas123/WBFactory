<?php

function annual_report_step8( $form, &$form_state, $filenumber= NULL   ){
	
	
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
		
	      $form['step8field'] = array(
          '#title' => t('<b> Area:'.$area.' , From date: '.$report_from_date.' , To date: '.$report_to_date.'</b>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 


        $form['step5field']['inspectionid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $filenumber,
	   
	   );   


	   $step8_query = db_select('labour_factory_statcell_annual_report_t8', 'b');
       
        $step8_query->condition('b.annual_inspection_id',trim($filenumber),'=');
      
		
        $step8_query->fields('b',array('reg_recv_no' ,'reg_investigated' ,'reg_violation' ,'reg_action' ,'reg_remarks' ,'unreg_recv_no' ,'unreg_investigated' ,'unreg_violation' , 'unreg_action','unreg_remarks'  ));
        $step8_result = $step8_query->execute(); 
		
		$result_8=$step8_result->fetchAssoc();
		$reg_recv_no=$result_8['reg_recv_no'];
		//print "aaaa".$reg_recv_no;
		
        $reg_investigated=$result_8['reg_investigated'];

        $reg_violation=$result_8['reg_violation'];
        $reg_action=$result_8['reg_action'];

        $reg_remarks=$result_8['reg_remarks'];




        $unreg_recv_no=$result_8['unreg_recv_no'];

         $unreg_recv_no=$result_8['unreg_recv_no'];
         $unreg_investigated=$result_8['unreg_investigated'];

         $unreg_violation=$result_8['unreg_violation'];
         $unreg_action=$result_8['unreg_action'];

         $unreg_remarks=$result_8['unreg_remarks'];

		
     	
$form['step8field']['col1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b>8.Complaints.</b></div><div class="table-responsive"><table class="table table-striped table-bordered table-responsive"><thead><tr><th>', 
		       '#markup'=>'<b>   </b>',

		          '#suffix'=>'</th>',
	   
	   
           );


                $form['step8field']['col2'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Number  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step8field']['col3'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Investigated  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step8field']['col4'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Violation observed </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

               $form['step8field']['col5'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Action taken </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step8field']['col6'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Remarks </b>',
           

		        '#suffix'=>'</th></tr></thead>',
	   
	   
           ); 

            

               $form['step8field']['col1val'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		        '#markup'=>'<b> Registered factories </b>',
             

		        '#suffix'=>'</td>',
	   
	   
           ); 

      $form['step8field']['col2val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		          '#default_value' =>$reg_recv_no
	   
	   
           ); 


              $form['step8field']['col3val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	           '#default_value' =>$reg_investigated
	   
           );

              $form['step8field']['col4val'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#type' => 'textarea',
		       
                '#rows' => 10,
                 '#cols' => 30,


		        '#suffix'=>'</td>',
		         '#default_value' =>$reg_violation
	   
	   
           );

               $form['step8field']['col5val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 10,
                 '#cols' => 30,


		        '#suffix'=>'</td>',
		         '#default_value' =>$reg_action
	   
	   
           );

                $form['step8field']['col6val'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#type' => 'textarea',
		       
                '#rows' => 10,
                 '#cols' => 30,


		        '#suffix'=>'</td></tr>',
		          '#default_value' =>$reg_remarks
	   
	   
           );


               $form['step8field']['col11val'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		        '#markup'=>'<b> Unregister factories </b>',
             

		        '#suffix'=>'</td>',
	   
	   
           ); 

      $form['step8field']['col21val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>', 
		         '#default_value' =>$unreg_recv_no
	   
	   
           ); 


              $form['step8field']['col31val'] = array
              (
		       '#prefix' => ' <td  >', 
		     '#type' => 'textfield',
                '#size' => 5,
		        '#suffix'=>'</td>',
		          '#default_value' =>$unreg_investigated
	   
	   
           );

              $form['step8field']['col41val'] = array
              (
		       '#prefix' => ' <td  >', 
		      '#type' => 'textarea',
		       
                '#rows' => 10,
                 '#cols' => 30,

		        '#suffix'=>'</td>',

		         '#default_value' =>$unreg_violation
	   
	   
           );

               $form['step8field']['col51val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 10,
                 '#cols' => 30,

		        '#suffix'=>'</td>',
	           '#default_value' =>$unreg_action
	   
           );

                $form['step8field']['col61val'] = array
              (
		       '#prefix' => ' <td  >', 
		      '#type' => 'textarea',
		       
                '#rows' => 10,
                 '#cols' => 30,
		        '#suffix'=>'</td></tr></table></div>',
		         '#default_value' =>$unreg_remarks
	   
	   
           );

                
             
              


 

              

         

			$form['submit_button']					= array(
																 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
																'#type'					=>'submit',
																'#value'				=>t(' Save ')
																);
		 
		 
	
	 	
		
		
 
		
				
	
														
														  
	        return $form; 
  }



function annual_report_step8_submit($form , $form_state) {	

                global $base_root, $base_path,$full_base;

$full_base='';


$val=$form_state['values'];
//print_r($val);
//exit;


    $inspectionid=trim($val['inspectionid']);
    //part A
	$col2val=trim($val['col2val']); if(!$col2val)  $col2val= NULL;   
	$col3val=trim($val['col3val']); if(!$col3val)  $col3val= NULL;   
	$col4val=trim($val['col4val']); 
	$col5val=trim($val['col5val']); 
    $col6val=trim($val['col6val']); 
	
	$col21val=trim($val['col21val']); if(!$col21val) $col21val= NULL;   
	$col31val=trim($val['col31val']); if(!$col31val) $col31val= NULL;   
	$col41val=trim($val['col41val']); 

	$col51val=trim($val['col51val']); 
    $col61val=trim($val['col61val']);  


     $txn = db_transaction();
	  try {


              $query_update_a_yes=db_query('select  * from labour_factory_statcell_annual_report_t8 where  annual_inspection_id = :filenumber', array(':filenumber' => $inspectionid));

             

             
		
	     if($query_update_a_yes->rowCount() > 0 ) {
       
         $query_update_B = db_update('labour_factory_statcell_annual_report_t8');
      $query_update_B->fields(array(
		   'reg_recv_no' =>$col2val, 'reg_investigated' => $col3val, 'reg_violation' => $col4val, 'reg_action' => $col5val, 'reg_remarks' => $col6val, 'unreg_recv_no' => $col21val, 'unreg_investigated' => $col31val
                         , 'unreg_violation' => $col41val, 'unreg_action' => $col51val, 'unreg_remarks' => $col61val ));
										
										
										
       $query_update_B->condition('annual_inspection_id',$inspectionid);
       $query_update_B->execute(); 
        $full_base=$base_root.$base_path.'admin/annual-report/step8/'.encryption_decryption_fun('encrypt',$inspectionid);

	      }
	      else
	      {

            $maxresult=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t8');	
	        $result=$maxresult->fetchAssoc();
	        $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1;	}else{ $querystring=$max_sl_number+1; }
		    $autoGENNO=$querystring;
    


  $fieldsE = array('row_id' => $autoGENNO, 'annual_inspection_id' =>$inspectionid,'reg_recv_no' =>$col2val, 'reg_investigated' => $col3val, 'reg_violation' => $col4val, 'reg_action' => $col5val, 'reg_remarks' => $col6val, 'unreg_recv_no' => $col21val, 'unreg_investigated' => $col31val
                         , 'unreg_violation' => $col41val, 'unreg_action' => $col51val, 'unreg_remarks' => $col61val);
		  
		   
                      db_insert('labour_factory_statcell_annual_report_t8')->fields($fieldsE)->execute();

                       $full_base=$base_root.$base_path.'admin/annual-report/step8/'.encryption_decryption_fun('encrypt',$inspectionid);
}

             $message = 'DATA  SAVED  SUCCESSFULLY  . ';
                      
				 
	           
	              drupal_set_message(t($message));
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
				 
	           
	             drupal_goto($full_base);

	             }
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/annual-report/step8/'.encryption_decryption_fun('encrypt',$inspectionid);

             $message = 'DATA  NOT SAVED  . ';
                      
		   
                      drupal_set_message(t($message));
	           
	             drupal_goto($full_base);
	
     }	
     
     }         