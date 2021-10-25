<?php

function annual_report_step4( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;
	 
	
	   $filenumber=encryption_decryption_fun('decrypt',$filenumber);
	
	 
	
	      
	
	//print "ssss".$filenumber;
	
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
          '#title' => t('<b> Area:'.$area.' , From date: '.$report_from_date.' , To date: '.$report_to_date.'</b>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

		$form['step1Dfield']['inspectionid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $filenumber,
	   
	   );
     	
$form['step1Dfield']['col1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b>4. Details of order issued under various provisions of the Acts and Rules.</b></div>
			   <div class="table-responsive">
			   <table class="table table-striped table-bordered table-responsive">
			   <thead><tr><th  >', 
		       '#markup'=>'<b> Name  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );


                $form['step1Dfield']['col2'] = array
              (
		       '#prefix' => ' <th  >', 
		        '#markup'=>'<b> Address  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step1Dfield']['col3'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Act and Section/Rule under which the order was issued  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step1Dfield']['col4'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Time allowed </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

               $form['step1Dfield']['col5'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Brief description including result	 </b>',
           

		        '#suffix'=>'</th></tr></thead> ',
	   
	   
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
		       '#prefix' => '<td  >', 
		         '#type' => 'textarea',
		       
                '#rows' => 10,
                 '#cols' => 30,
		          '#suffix'=>'</td>',
	   
	   
           );

               $form['step1Dfield']['col3val'] = array
              (
		       '#prefix' => '<td  >', 
		         '#type' => 'textarea',
		       
                '#rows' => 10,
                 '#cols' => 30,
		          '#suffix'=>'</td>',
	   
	   
           );


               $form['step1Dfield']['col4val'] = array
              (
		       '#prefix' => '<td  >', 
		         '#type' => 'textarea',
		       
                '#rows' => 10,
                 '#cols' => 30,
		          '#suffix'=>'</td>',
	   
	   
           );


               $form['step1Dfield']['col5val'] = array
              (
		       '#prefix' => '<td  >', 
		         '#type' => 'textarea',
		       
                '#rows' => 10,
                 '#cols' => 30,
		          '#suffix'=>'</td></tr></table></div>',
	   
	   
           );
      
      
      

			$form['step1Dfield']['submit_button']					= array(
																 
                                                              '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
																	'#type' => 'button',
		                                                           '#event' => 'click',

																 '#default_value' => 'ADD  ',
                                                              '#ajax' => array(
                                                              'callback' => 'add_step4_data',
                                                              'wrapper' => 'pr_person_add',
                                                                'method' => 'html',
                                                                     'effect' => 'fade'
                                                               )
																);
		 
		 
	
	 	
		  $output1='';
      if(trim($filenumber)){
      $query_tab_1_c=db_query('select  *  from labour_factory_statcell_annual_report_t4 where  annual_inspection_id = :anid', array(':anid' => trim($filenumber) ));
      if($query_tab_1_c->rowCount() > 0) 
              { 
      $output1 = "<div class='table-responsive'><table class='table table-striped table-bordered table-responsive add-employee-table-view'>
	  <thead>
	    <tr > <th >SL.NO</th>
      
       <th > Name </th>
	    <th >Address </th>
       
		 <th >Act and Section/Rule under which the order was issued</th>

		 <th >Time allowed</th>
       
		 <th >Brief description including result	</th>
		 
		 <th >DELETE</th>
		</tr></thead>";  
			  $i=0;
		foreach($query_tab_1_c as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $annual_inspection_id = $squan->annual_inspection_id; 
	          $factory_name=$squan->factory_name;
			  $factory_address=$squan->factory_address;
			  $section_rule_issued=$squan->section_rule_issued;
              $time_allowed=$squan->time_allowed;
              $brief_description=$squan->brief_description;
            
              
			 //  $bb=$base_root.$base_path.'equalremuins/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id).'/presentperdel';

			   $bb=$base_root.$base_path.'admin/annual-report-tab4-del/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
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
                $output1.= "<td>".$section_rule_issued."</td>";
                $output1.= "<td>".$time_allowed."</td>";
                $output1.= "<td>".$brief_description."</td>";
			
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


function step4_del(  $filenumber = NULL , $rowid = NULL){
	  
	 global $base_root, $base_path;
	  //  $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));
	   
      //$tyinfg= encryption_decryption_fun('decrypt', trim($tyinfg));

	   $filenumber=  encryption_decryption_fun('decrypt',trim($filenumber));
	   
      $rowid=  encryption_decryption_fun('decrypt',trim($rowid));
	   
	$txn = db_transaction();
	  try {
		  
    db_delete('labour_factory_statcell_annual_report_t4')
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

      $aa=$base_root.$base_path.'admin/annual-report/step4/'.encryption_decryption_fun('encrypt',$filenumber);
     drupal_set_message(t($message));
		 
		  drupal_goto($aa);
		  
  }


function add_step4_data($form , $form_state) {	
       global $base_root, $base_path;
       $val=$form_state['values'];


    
 
      $inspectionid=trim($val['inspectionid']);
      $col1val=trim($val['col1val']);   
      $col2val=trim($val['col2val']);   
      $col3val=trim($val['col3val']);   
      $col4val=trim($val['col4val']);     
      $col5val=trim($val['col5val']);    
     


   if(!$col1val)
	 {
	  drupal_get_messages(error);
	  return "<font color='#FF3333'><b>please enter   name <b>    </font>";
	  exit;
	 } 

	  elseif(!$col2val)
	 {
	  drupal_get_messages(error);
	  return "<font color='#FF3333'><b>please enter  address   <b>    </font>";
	  exit;
	 } 
	    


     $txn = db_transaction();

        try {
     
	 
	  $ins_pr_person=db_query('select  max(row_id) ownermax from labour_factory_statcell_annual_report_t4 ');
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
			
	      
		   
		    $fieldsE = array('row_id' => $count_profile, 'annual_inspection_id' => $inspectionid,'factory_name' =>$col1val ,'factory_address' =>$col2val,'section_rule_issued' =>$col3val, 'time_allowed' => $col4val, 'brief_description' => $col5val);
		  
		   
           db_insert('labour_factory_statcell_annual_report_t4')->fields($fieldsE)->execute();	
	 
	 
	$query_tab_1_c=db_query('select  *  from labour_factory_statcell_annual_report_t4 where  annual_inspection_id = :anid', array(':anid' => trim($inspectionid) ));
    
      $output1 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
	    <tr > <th >SL.NO</th>
      
       <th > Name</th>
	    <th >Address </th>
       
		 <th >Act and Section/Rule under which the order was issued</th>

		 <th >Time allowed</th>
       
		 <th >Brief description including result</th>
		
		 <th >DELETE</th>
		</tr>";  
			  $i=0;
		foreach($query_tab_1_c as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $annual_inspection_id = $squan->annual_inspection_id; 
	          $factory_name=$squan->factory_name;
			  $factory_address=$squan->factory_address;
			  $section_rule_issued=$squan->section_rule_issued;
              $time_allowed=$squan->time_allowed;
              $brief_description=$squan->brief_description;


             
              
			 //  $bb=$base_root.$base_path.'equalremuins/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id).'/presentperdel';

			   $bb=$base_root.$base_path.'admin/annual-report-tab4-del/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
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
                $output1.= "<td>".$section_rule_issued."</td>";
                $output1.= "<td>".$time_allowed."</td>";
                $output1.= "<td>".$brief_description."</td>";
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



